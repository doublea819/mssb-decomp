// AI (audio interface) emulation.
//
// On the GameCube the AI streams a DMA buffer of 16-bit stereo samples to the
// DAC and raises an interrupt when it has consumed it; the handler then queues
// the next buffer with AIInitDMA. Here a thread plays the DMA engine: it copies
// the current buffer into an SDL audio stream and runs the game's DMA callback in
// "interrupt context". Buffers are written by the CPU on PC, so samples are
// native-endian.

#include <dolphin/types.h>
#include <dolphin/ai.h>

#include "port/game_heap.h"
#include "port/os.h"

#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_init.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <vector>

extern "C" void port_dtk_mix(s16* out, int frames, int rate);

namespace {
AIDCallback s_dmaCallback = nullptr;
std::atomic<uintptr_t> s_dmaStart{0};
std::atomic<u32> s_dmaLength{0};
std::atomic<bool> s_dmaRunning{false};
u32 s_dspSampleRate = 0; // AI_SAMPLERATE_32KHZ
SDL_AudioStream* s_stream = nullptr;
std::vector<u8> s_period;

int sample_rate_hz()
{
    return s_dspSampleRate == 0 ? 32000 : 48000;
}

// The game expects the DMA interrupt every period (160 samples, 5 ms): MusyX
// advances voices, starts emitters and updates their state there, and game code
// checks that state the next frame (e.g. "is the movement loop playing yet?").
// SDL pulls audio in large, irregular chunks, so instead a thread runs one
// period whenever SDL's queue drops below a small target, keeping the interrupt
// close to the hardware cadence.
constexpr int kTargetQueueMs = 30;

// MSSB_AI_STATS=1: once a second, DMA periods run, the longest run of periods
// less than 1 ms apart (a burst) and the device queue level.
void ai_stats(int queuedBytes)
{
    static const bool s_on = [] {
        const char* env = getenv("MSSB_AI_STATS");
        return env != nullptr && env[0] != '\0' && env[0] != '0';
    }();
    if (!s_on)
        return;
    using clock = std::chrono::steady_clock;
    static clock::time_point s_window = clock::now(), s_last;
    static int s_periods = 0, s_run = 0, s_maxRun = 0, s_minQ = 1 << 30, s_maxQ = 0;
    const auto now = clock::now();
    s_run = now - s_last < std::chrono::milliseconds(1) ? s_run + 1 : 1;
    s_maxRun = std::max(s_maxRun, s_run);
    s_last = now;
    ++s_periods;
    s_minQ = std::min(s_minQ, queuedBytes);
    s_maxQ = std::max(s_maxQ, queuedBytes);
    if (now - s_window >= std::chrono::seconds(1))
    {
        const int bytesPerMs = sample_rate_hz() * 4 / 1000;
        fprintf(stderr, "[ai] %d periods/s, longest burst %d, queue %d-%d ms\n", s_periods, s_maxRun,
                s_minQ / bytesPerMs, s_maxQ / bytesPerMs);
        s_window = now;
        s_periods = 0;
        s_maxRun = 0;
        s_minQ = 1 << 30;
        s_maxQ = 0;
    }
}

void run_period()
{
    if (s_stream != nullptr)
        ai_stats(SDL_GetAudioStreamQueued(s_stream));
    u32 len = s_dmaLength.load();
    uintptr_t start = s_dmaStart.load();
    s_period.resize(len);
    port_interrupt_enter();
    memcpy(s_period.data(), (const void*)start, len);
    // The AI mixes the DVD audio stream (music) into the DSP output.
    port_dtk_mix((s16*)s_period.data(), (int)(len / 4), sample_rate_hz());
    if (s_dmaCallback)
        s_dmaCallback();
    port_interrupt_leave();
    if (s_stream != nullptr)
        SDL_PutAudioStreamData(s_stream, s_period.data(), (int)len);
    // MSSB_AI_DUMP=path: raw s16 stereo of everything sent to the device.
    static FILE* s_dump = [] {
        const char* path = getenv("MSSB_AI_DUMP");
        return path != nullptr ? fopen(path, "wb") : nullptr;
    }();
    if (s_dump != nullptr)
    {
        fwrite(s_period.data(), 1, len, s_dump);
        fflush(s_dump);
    }
}

#ifdef __EMSCRIPTEN__
// Web builds have no audio thread: the main thread tops up SDL's queue at
// frame boundaries and whenever the game waits or re-enables interrupts
// (port_audio_pump). The queue target is larger to cover a frame plus jitter.
constexpr int kWebTargetQueueMs = 70;
#endif

std::atomic<bool> s_quit{false};
std::thread s_thread;

void stop_audio_thread()
{
    s_quit.store(true);
    if (s_thread.joinable())
        s_thread.join();
}

// Periods are run on a wall-clock cadence (one per period length, 5 ms), not
// whenever SDL's queue runs low: the device pulls audio in large chunks (10-20
// ms on built-in speakers, far more on Bluetooth), so a queue-driven loop ran
// the DMA callback in bursts of several periods back to back. Game code that
// produces audio between interrupts can't keep up with that: the movie player
// (MovMixAudio, file_800ADC40.c) skips every period of a burst whose audio the
// decoder hasn't written yet, and since its clock counts only mixed periods,
// the movie ran at ~0.36x. The queue level only trims the cadence to the
// device's real rate. MSSB_AI_BURST=1 restores the queue-driven loop.
// The queue is filled to kPrefillMs once (at start, or after it ran dry), then
// topped up one period per period; it swings by one device chunk around that.
constexpr int kPrefillMs = 40;
constexpr int kDryMs = 3;       // below this the device is starving: refill at once
constexpr int kMaxQueueMs = 120; // above this, hold off (device slower than the wall clock)

bool dma_ready()
{
    return s_dmaRunning.load() && s_dmaLength.load() != 0 && s_dmaStart.load() != 0;
}

void audio_thread_burst()
{
    while (!s_quit.load())
    {
        const int targetBytes = sample_rate_hz() * 4 * kTargetQueueMs / 1000;
        if (dma_ready() && SDL_GetAudioStreamQueued(s_stream) < targetBytes)
        {
            run_period();
            continue;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void audio_thread()
{
    if (const char* env = getenv("MSSB_AI_BURST"); env != nullptr && env[0] != '\0' && env[0] != '0')
    {
        audio_thread_burst();
        return;
    }
    using clock = std::chrono::steady_clock;
    clock::time_point next = clock::now();
    bool refill = true;
    while (!s_quit.load())
    {
        if (!dma_ready())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            next = clock::now();
            refill = true;
            continue;
        }
        const int bytesPerMs = sample_rate_hz() * 4 / 1000;
        const int queued = SDL_GetAudioStreamQueued(s_stream);
        const clock::time_point now = clock::now();
        if (queued < kDryMs * bytesPerMs)
            refill = true;
        else if (queued >= kPrefillMs * bytesPerMs)
            refill = false;
        if (refill || (now >= next && queued < kMaxQueueMs * bytesPerMs))
        {
            if (refill)
                next = now; // the cadence restarts once the queue is primed
            run_period();
            const auto period = std::chrono::microseconds(1000000LL * (s_dmaLength.load() / 4) / sample_rate_hz());
            next += period;
            if (next < now - std::chrono::milliseconds(50))
                next = now + period; // stalled (debugger, hidden app): don't burst to catch up
            continue;
        }
        if (now >= next)
            next = now; // queue full: wait for the device to drain it
        std::this_thread::sleep_until(std::min(next, now + std::chrono::milliseconds(1)));
    }
}

void ensure_stream()
{
    if (s_stream != nullptr)
        return;
    if (!SDL_WasInit(SDL_INIT_AUDIO) && !SDL_InitSubSystem(SDL_INIT_AUDIO))
        return;
    SDL_AudioSpec spec{};
    spec.format = SDL_AUDIO_S16;
    spec.channels = 2;
    spec.freq = sample_rate_hz();
    s_stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, nullptr, nullptr);
    if (s_stream == nullptr)
        return;
    SDL_ResumeAudioStreamDevice(s_stream);
#ifndef __EMSCRIPTEN__
    s_thread = std::thread(audio_thread);
#endif
}
} // namespace

extern "C" {
#ifdef __EMSCRIPTEN__
void port_audio_pump(void)
{
    static bool s_pumping = false;
    // Online play runs the periods from port_audio_net_frame instead.
    if (s_stream == nullptr || s_pumping || port_net_active())
        return;
    s_pumping = true;
    const int targetBytes = sample_rate_hz() * 4 * kWebTargetQueueMs / 1000;
    // Bounded so a stalled device (tab hidden, autoplay blocked) can't spin.
    for (int i = 0; i < 64; i++)
    {
        if (!s_dmaRunning.load() || s_dmaLength.load() == 0 || s_dmaStart.load() == 0 ||
            SDL_GetAudioStreamQueued(s_stream) >= targetBytes)
            break;
        run_period();
    }
    s_pumping = false;
}

// Online play: the DMA callback advances MusyX, whose state the game reads
// (has a voice finished?), so both peers must run the same number of periods
// per game frame. Each frame runs the periods that 1/60 s of samples fill, by
// integer arithmetic, whether or not this browser's audio device is open; the
// device just plays what it gets. Called at each lockstep frame boundary.
void port_audio_net_frame(void)
{
    static u64 s_acc = 0; // bytes of samples owed, times 60
    const u32 len = s_dmaLength.load();
    if (!s_dmaRunning.load() || len == 0 || s_dmaStart.load() == 0)
        return;
    s_acc += (u64)sample_rate_hz() * 4;
    while (s_acc >= (u64)len * 60)
    {
        s_acc -= (u64)len * 60;
        run_period();
    }
    // Keep latency bounded if the device plays slower than the game runs.
    if (s_stream != nullptr && SDL_GetAudioStreamQueued(s_stream) > sample_rate_hz() * 4 / 4)
        SDL_ClearAudioStream(s_stream);
}
#endif

// Milliseconds of audio queued for the device (web stats).
int port_audio_queued_ms(void)
{
    if (s_stream == nullptr)
        return -1;
    return SDL_GetAudioStreamQueued(s_stream) * 1000 / (sample_rate_hz() * 4);
}

// Called before aurora/SDL shut down, which destroys the stream.
void port_audio_shutdown(void)
{
    stop_audio_thread();
}

AIDCallback AIRegisterDMACallback(AIDCallback callback)
{
    AIDCallback old = s_dmaCallback;
    s_dmaCallback = callback;
    return old;
}

void AIInitDMA(uintptr_t start_addr, u32 length)
{
    // Either a real pointer or a 32-bit physical address (game-heap offset)
    // from OSCachedToPhysical.
    if (start_addr != 0 && start_addr <= 0xFFFFFFFFu)
        start_addr = (uintptr_t)port_heap_virt((u32)start_addr);
    s_dmaStart.store(start_addr);
    s_dmaLength.store(length);
}

void AIStartDMA(void)
{
    ensure_stream();
    s_dmaRunning.store(true);
}

void AIStopDMA(void)
{
    s_dmaRunning.store(false);
}

u32 AIGetDMAStartAddr(void)
{
    return (u32)s_dmaStart.load();
}

u32 AIGetDSPSampleRate(void)
{
    return s_dspSampleRate;
}

void AISetDSPSampleRate(u32 rate)
{
    if (rate == s_dspSampleRate)
        return;
    s_dspSampleRate = rate;
    if (s_stream != nullptr)
    {
        SDL_AudioSpec spec{SDL_AUDIO_S16, 2, sample_rate_hz()};
        SDL_SetAudioStreamFormat(s_stream, &spec, nullptr);
    }
}

void AIInit(u8* stack)
{
    (void)stack;
    ensure_stream();
}

void AIReset(void)
{
    s_dmaRunning.store(false);
}
}
