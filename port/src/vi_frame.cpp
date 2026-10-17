// VI retrace emulation and frame pacing.
//
// The game presents by calling VIWaitForRetrace after GXCopyDisp. On PC that
// call is the frame boundary: finish aurora's frame (which presents and waits
// for vsync), pump window events, run the retrace callbacks the game installed,
// and begin the next frame.
//
// Retraces also happen while the main thread is blocked elsewhere (os.cpp
// presents from a blocked main thread at each 60 Hz deadline). aurora presents
// the live EFB (GXCopyDisp is a no-op), so ending aurora's frame there would
// show a half-drawn frame and push the rest of its draws into the next one.
// Such a retrace only runs the callbacks (a "tick"); the frame is presented
// once the game finishes it (port_vi_frame_done, from fn_800A7DB0), as the
// GameCube's VI keeps scanning out the last copied XFB.
// MSSB_PRESENT_ANYTIME=1 restores presenting at every retrace;
// MSSB_FRAME_STATS=1 prints pacing stats once a second.

#include <aurora/aurora.h>
#include <aurora/event.h>
#include <aurora/gfx.h>
#include <dolphin/gx.h>
#include <dolphin/vi.h>

#include "port/os.h"
#include "port_internal.h"

#ifndef __EMSCRIPTEN__
#include <SDL3/SDL_events.h>
#endif

#include <algorithm>
#include <atomic>
#include <cmath>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <thread>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include "port/web_stats.h"
extern "C" void port_web_frame_tick(void);
extern "C" int port_is_main_os_thread(void);
#endif

#ifdef __EMSCRIPTEN__
WebFrameStats g_webStats; // ?stats (port_web_frame_tick prints and resets it)
#endif

extern "C" void port_touch_event(const SDL_Event* e);
extern "C" void port_touch_draw(SDL_Window* win);

namespace {
std::atomic<u32> s_retraceCount{0};
VIRetraceCallback s_preCb = nullptr;
VIRetraceCallback s_postCb = nullptr;
void* s_nextFb = nullptr;
void* s_currentFb = nullptr;
bool s_inFrame = false;
bool s_quitRequested = false;
std::thread::id s_mainThread;

// Frame-boundary presents (see the top of the file).
std::atomic<bool> s_frameDone{true};
int s_ticksSincePresent = 0;

// Retraces in a row that may skip the present before one is forced anyway
// (keeps the window alive if a mode never reaches fn_800A7DB0). 0 = always present.
int max_skipped_presents()
{
    static const int s_max = [] {
        const char* any = getenv("MSSB_PRESENT_ANYTIME");
        if (any != nullptr && any[0] != '\0' && any[0] != '0')
            return 0;
        const char* env = getenv("MSSB_MAX_SKIPPED_PRESENTS");
        return env != nullptr ? atoi(env) : 30;
    }();
    return s_max;
}

// MSSB_FRAME_STATS=1: once a second, retraces / presents / ticks without a
// present (and how many were forced), the worst lateness of a retrace against
// its 59.94 Hz slot and the worst aurora end/begin frame times.
struct FrameStats
{
    bool enabled = [] {
        const char* env = getenv("MSSB_FRAME_STATS");
        return env != nullptr && env[0] != '\0' && env[0] != '0';
    }();
    std::chrono::steady_clock::time_point windowStart = std::chrono::steady_clock::now();
    unsigned ticks = 0, presents = 0, skipped = 0, forced = 0, resyncs = 0;
    double maxLateMs = 0, maxEndMs = 0, maxBeginMs = 0;

    void report()
    {
        if (!enabled)
            return;
        auto now = std::chrono::steady_clock::now();
        if (now - windowStart < std::chrono::seconds(1))
            return;
        double secs = std::chrono::duration<double>(now - windowStart).count();
        fprintf(stderr,
                "[frame] %.1f retraces/s, %.1f presents/s, %u mid-frame retraces (%u forced presents), "
                "%u resyncs, worst late %.1f ms, end_frame %.1f ms, begin_frame %.1f ms\n",
                ticks / secs, presents / secs, skipped, forced, resyncs, maxLateMs, maxEndMs, maxBeginMs);
        *this = FrameStats{};
        enabled = true;
    }
} s_stats;

double ms_since(std::chrono::steady_clock::time_point t)
{
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t).count();
}

void handle_events()
{
    port_crash_heartbeat();
    const AuroraEvent* event = aurora_update();
    while (event != nullptr && event->type != AURORA_NONE)
    {
        if (event->type == AURORA_EXIT)
            s_quitRequested = true;
        else if (event->type == AURORA_SDL_EVENT)
            port_touch_event(&event->sdl);
        ++event;
    }
}

#ifdef __EMSCRIPTEN__
// Resolves with the rAF timestamp: the start of the display refresh this
// callback belongs to, free of the jitter of when the callback actually runs.
// Hidden tabs get no animation frames; online play must keep going there.
EM_ASYNC_JS(double, web_wait_animation_frame, (), {
    if (document.hidden && Module.mssbNet)
        return await new Promise((resolve) => setTimeout(() => resolve(performance.now()), 4));
    return await new Promise((resolve) => requestAnimationFrame(resolve));
});


// The browser presents the canvas when control returns to its event loop, so
// each frame ends by yielding (Asyncify) until a display refresh. When the
// display runs at a multiple of ~60 Hz (60, 120 Hz ProMotion, 240) every k-th
// refresh is one game frame (the game runs at 60.0 instead of 59.94 Hz, as on
// a TV); otherwise (144 Hz, ...) the frame goes out on the first refresh within
// half a refresh of its 59.94 Hz slot. Audio is topped up while waiting.
void pace_frame()
{
    constexpr double kPeriodMs = 1001.0 / 60.0;
    static double s_next = 0;     // this frame's slot (rAF time base)
    static double s_lastVsync = 0;
    static double s_lastPresent = 0;
    static double s_deltas[32];   // recent refresh-to-refresh times
    static unsigned s_deltaIdx = 0;
    static double s_workStart = 0;

    double work = s_workStart != 0 ? emscripten_get_now() - s_workStart : 0;
    double t;
    for (;;)
    {
        double a0 = emscripten_get_now();
        port_audio_pump();
        g_webStats.audioMs += emscripten_get_now() - a0;
        t = web_wait_animation_frame();
        a0 = emscripten_get_now();
        port_audio_pump();
        g_webStats.audioMs += emscripten_get_now() - a0;
        if (s_lastVsync != 0)
            s_deltas[s_deltaIdx++ % 32] = t - s_lastVsync;
        s_lastVsync = t;
        // The display's refresh period: the median of recent deltas (rAF
        // timestamps jitter by a millisecond or so).
        double sorted[32];
        unsigned n = 0;
        for (double d : s_deltas)
            if (d > 3.0 && d < 50.0)
                sorted[n++] = d;
        std::sort(sorted, sorted + n);
        double refresh = n != 0 ? sorted[n / 2] : kPeriodMs;
        if (s_lastPresent == 0 || t - s_lastPresent > 100.0)
        {
            s_next = t; // first frame, or fell behind (slow frame, tab hidden): don't catch up
            break;
        }
        double k = std::max(1.0, std::round(kPeriodMs / refresh));
        if (std::fabs(k * refresh - kPeriodMs) < kPeriodMs * 0.03)
        {
            if (t - s_lastPresent >= (k - 0.5) * refresh)
            {
                s_next = t;
                break;
            }
        }
        else if (t >= s_next - refresh * 0.5)
            break;
    }
    s_next += kPeriodMs;

    double interval = s_lastPresent != 0 ? t - s_lastPresent : kPeriodMs;
    s_lastPresent = t;
    g_webStats.frames++;
    if (interval > kPeriodMs * 1.5)
        g_webStats.late++;
    {
        // ?stats: each late frame, with what might explain it (a long game
        // frame, or GPU pipelines compiled just before: aurora's pipeline cache).
        static unsigned s_frameNo = 0;
        static u32 s_created[3];
        const AuroraStats* st = aurora_get_stats();
        ++s_frameNo;
        s_created[s_frameNo % 3] = st->createdPipelines;
        u32 recent = st->createdPipelines - s_created[(s_frameNo + 1) % 3];
        if (interval > kPeriodMs * 1.5)
            EM_ASM({
                if (Module.mssbStats)
                    console.log(`[late] frame ${$0}: ${$1.toFixed(1)} ms since the last one (game ${$2.toFixed(1)} ms, ` +
                                `${$3} pipelines built in the last 3 frames, ${$4} queued)`);
            }, s_frameNo, interval, work, recent, st->queuedPipelines);
    }
    if (interval > g_webStats.maxIntervalMs)
        g_webStats.maxIntervalMs = interval;
    if (work > g_webStats.maxWorkMs)
        g_webStats.maxWorkMs = work;
    g_webStats.workMs += work;
    port_web_frame_tick();
    s_workStart = emscripten_get_now();
}

void port_sleep_ms(int ms)
{
    emscripten_sleep(ms);
}
#else
// The game runs one tick per NTSC field (59.94 Hz). aurora presents with vsync,
// which runs at the display's rate (120 Hz on ProMotion Macs), so hold each
// frame until its slot comes up.
using clock = std::chrono::steady_clock;
const clock::duration kPeriod =
    std::chrono::duration_cast<clock::duration>(std::chrono::nanoseconds(1001000000LL / 60));
clock::time_point s_next = clock::now() + kPeriod;

void pace_frame()
{
    clock::time_point now = clock::now();
    if (now < s_next)
    {
        std::this_thread::sleep_until(s_next);
        s_next += kPeriod;
    }
    else if (now - s_next < kPeriod)
    {
        // A little late. This is the normal case when the blocked main thread
        // presents (os.cpp): it wakes at the deadline, waits for the run token
        // and ends aurora's frame (FIFO drain) before getting here. Restarting
        // the schedule from `now` would add that delay to every frame and run
        // the game below 59.94 Hz; keep the cadence instead.
        s_stats.maxLateMs = std::max(s_stats.maxLateMs, std::chrono::duration<double, std::milli>(now - s_next).count());
        s_next += kPeriod;
    }
    else
    {
        // Running behind by a frame or more (slow frame, window hidden): don't
        // try to catch up.
        s_stats.maxLateMs = std::max(s_stats.maxLateMs, std::chrono::duration<double, std::milli>(now - s_next).count());
        ++s_stats.resyncs;
        s_next = now + kPeriod;
    }
}

void port_sleep_ms(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

#endif

void quit_now()
{
    port_audio_shutdown();
    aurora_shutdown();
    std::exit(0);
}
} // namespace

// MSSB_FRAME_DUMP=<dir>: write presented frames to <dir>/f<game frame>.ppm while the game asks for
// them (g_port_frame_dump_until, set by the minigame character select) or always with
// MSSB_FRAME_DUMP_ALL=1. At most MSSB_FRAME_DUMP_MAX frames (default 1800).
extern "C" unsigned int port_spani_trace_frame;
extern "C" unsigned int g_port_frame_dump_until;
unsigned int g_port_frame_dump_until = 0;
namespace {
void port_frame_dump_mark()
{
    static const bool s_on = [] {
        const char* e = getenv("MSSB_FRAME_DUMP");
        return e != nullptr && e[0] != '\0';
    }();
    if (!s_on)
        return;
    static const bool s_all = [] {
        const char* e = getenv("MSSB_FRAME_DUMP_ALL");
        return e != nullptr && e[0] != '\0' && e[0] != '0';
    }();
    static const int s_max = [] {
        const char* e = getenv("MSSB_FRAME_DUMP_MAX");
        return e != nullptr ? atoi(e) : 1800;
    }();
    static int s_count = 0;
    static unsigned int s_last = ~0u;
    const unsigned int frame = port_spani_trace_frame;
    if (s_count >= s_max || frame == s_last)
        return;
    if (!s_all && frame > g_port_frame_dump_until)
        return;
    s_last = frame;
    ++s_count;
    aurora_set_frame_dump_id((int)frame);
}
} // namespace

extern "C" void port_pad_sample(void);
extern "C" void port_freeze_frames_check(void);
extern "C" void port_pad_assign(void);

extern "C" {

void port_begin_first_frame(void)
{
    s_mainThread = std::this_thread::get_id();
    handle_events();
    while (!aurora_begin_frame())
    {
        if (s_quitRequested)
            quit_now();
        port_sleep_ms(16);
        handle_events();
    }
    s_inFrame = true;
}

// The game finished a frame (fn_800A7DB0, right before it waits for the
// retrace that shows it): the next retrace presents.
void port_vi_frame_done(void)
{
    s_frameDone.store(true, std::memory_order_release);
}

// End of a draw-thread pass (fn_800A7C08). On the GameCube the GPU consumes
// the FIFO about as fast as the CPU fills it, so by the time the main thread
// updates sprites, palettes and vertex buffers for the next frame the GPU has
// read them. aurora's FIFO thread reads that memory only when it processes each
// draw, and can be many draws behind; an update landing first changes what the
// earlier draws show (flicker on 2D elements whose data is rewritten each
// frame). Draining here restores the GameCube ordering.
void port_draw_pass_done(void)
{
    static const bool s_async = [] {
        const char* env = getenv("MSSB_ASYNC_DRAW");
        return env != nullptr && env[0] != '\0' && env[0] != '0';
    }();
    if (!s_async)
        GXDrawDone();
}

void port_present_frame(void)
{
    // Present at the frame boundary only; other retraces just tick.
    const int maxSkipped = max_skipped_presents();
    bool present = s_frameDone.exchange(false, std::memory_order_acq_rel) || maxSkipped <= 0;
    if (!present && ++s_ticksSincePresent > maxSkipped)
    {
        present = true;
        ++s_stats.forced;
    }
    ++s_stats.ticks;
    if (present)
    {
        s_ticksSincePresent = 0;
        ++s_stats.presents;
    }
    else
    {
        ++s_stats.skipped;
    }

    if (present && s_inFrame)
    {
        port_frame_dump_mark();
        const auto t0 = std::chrono::steady_clock::now();
#ifdef __EMSCRIPTEN__
        double w0 = emscripten_get_now();
        port_touch_draw(aurora_get_window());
        aurora_end_frame();
        g_webStats.endFrameMs += emscripten_get_now() - w0;
#else
        port_touch_draw(aurora_get_window());
        aurora_end_frame();
#endif
        s_stats.maxEndMs = std::max(s_stats.maxEndMs, ms_since(t0));
        s_inFrame = false;
    }
    pace_frame();

    if (present)
    {
        port_freeze_frames_check(); // MSSB_FREEZE_FRAMES (freeze_frames.cpp)
#ifdef __EMSCRIPTEN__
        double e0 = emscripten_get_now();
        handle_events();
        g_webStats.eventsMs += emscripten_get_now() - e0;
#else
        handle_events();
#endif
    }
    else
    {
        // Mid-frame: aurora_update could reconfigure the surface under the
        // frame being recorded. Keep the OS event loop (and the hang
        // watchdog) alive; events are handled at the next present.
        port_crash_heartbeat();
#ifndef __EMSCRIPTEN__
        SDL_PumpEvents();
#endif
    }
    if (s_quitRequested)
        quit_now();
    port_pad_assign();

    // Online play: wait for this frame's inputs from every peer.
    port_net_frame();

    // Retrace "interrupt".
    u32 count = ++s_retraceCount;
    port_interrupt_enter();
    if (s_preCb)
        s_preCb(count);
    s_currentFb = s_nextFb;
    if (s_postCb)
        s_postCb(count);
    port_pad_sample(); // PADSetSamplingCallback (the game polls pads here)
    port_interrupt_leave();
    port_retrace_notify();

    if (present)
    {
        // aurora_begin_frame returns false while the window is minimized or
        // otherwise can't present; block the game until it can.
        const auto t0 = std::chrono::steady_clock::now();
        while (!aurora_begin_frame())
        {
            port_sleep_ms(16);
            handle_events();
            if (s_quitRequested)
                quit_now();
        }
        s_stats.maxBeginMs = std::max(s_stats.maxBeginMs, ms_since(t0));
        s_inFrame = true;
    }
    s_stats.report();
}

void port_request_quit(void)
{
    s_quitRequested = true;
}

// The main thread presents; other game threads wait for the next frame.
void VIWaitForRetrace(void)
{
#ifdef __EMSCRIPTEN__
    if (port_is_main_os_thread())
#else
    if (std::this_thread::get_id() == s_mainThread)
#endif
    {
        // Called between frames (init, mode changes, the scene loader's
        // VISetBlack waits): always a frame boundary.
        port_vi_frame_done();
        port_present_frame();
    }
    else
        port_wait_retrace(s_retraceCount.load());
}

u32 VIGetRetraceCount(void)
{
    return s_retraceCount.load();
}

u32 VIGetNextField(void)
{
    return 0;
}

u32 VIGetDTVStatus(void)
{
    return 1; // progressive scan capable
}

void* VIGetCurrentFrameBuffer(void)
{
    return s_currentFb;
}

void* VIGetNextFrameBuffer(void)
{
    return s_nextFb;
}

void VISetNextFrameBuffer(void* fb)
{
    s_nextFb = fb;
}

void VISetBlack(BOOL black)
{
    (void)black;
}

VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback cb)
{
    VIRetraceCallback old = s_preCb;
    s_preCb = cb;
    return old;
}

VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback cb)
{
    VIRetraceCallback old = s_postCb;
    s_postCb = cb;
    return old;
}

} // extern "C"

#ifndef __EMSCRIPTEN__
std::chrono::steady_clock::time_point port_retrace_deadline() { return s_next; }
#endif
unsigned int port_retrace_count() { return s_retraceCount.load(); }
