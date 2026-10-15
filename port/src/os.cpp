// PC implementations of the GameCube OS services the game uses that aurora
// doesn't provide: interrupts, threads, thread queues, semaphores and message
// queues, the OS arena, reset/console queries.
//
// Interrupts: on the GameCube DVD, VI and audio callbacks run in interrupt
// context. On PC they arrive on other host threads, so "interrupts disabled"
// is one global lock (from strikers). Each thread tracks whether it holds it.
//
// Threads: every OSThread runs on its own host thread, but only one game
// thread runs at a time (the "run token"), like the GameCube's single CPU.
// A thread gives the token up when it blocks (sleep, semaphore, message,
// suspend, exit); the highest-priority ready thread gets it next. Waking a
// higher-priority thread from a game thread switches to it at once
// (preemption); waking from an interrupt callback takes effect at the next
// switch. While the main thread is blocked it also drives the VI retrace:
// at each 60 Hz deadline it presents the frame and runs the retrace
// callbacks (which is what wakes the game's frame loop).

#include <dolphin/os.h>

#include "port/game_heap.h"
#include "port/os.h"
#include "port_internal.h"

#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <unordered_map>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/fiber.h>
#include <functional>
#include <vector>
#else
#include <thread>
#endif

namespace {
#ifndef __EMSCRIPTEN__
// ---------------------------------------------------------------- interrupts
std::mutex g_irqMutex;
thread_local bool t_irqDisabled = false;

void irq_lock()
{
    g_irqMutex.lock();
    t_irqDisabled = true;
}

void irq_unlock()
{
    t_irqDisabled = false;
    g_irqMutex.unlock();
}

// ---------------------------------------------------------------- scheduler
struct PortThread
{
    OSThread* os = nullptr;
    void* (*func)(void*) = nullptr;
    void* param = nullptr;
    bool started = false;
    bool blocked = false;   // waiting on a queue
    bool finished = false;
    // Resumes from interrupt context that arrived while the thread was still
    // running (see OSResumeThread).
    int pendingResume = 0;
    // OSSleepThread queue this thread is waiting on (nullptr otherwise); OSWakeupThread makes such
    // threads runnable at once so a higher-priority one preempts the waker, as on the GameCube.
    const void* sleepQueue = nullptr;
};

std::mutex g_sched;
std::condition_variable g_cv;
std::unordered_map<OSThread*, PortThread*> g_threads;
std::unordered_map<const void*, unsigned long long> g_queueGen;
OSThread* g_running = nullptr; // holder of the run token
OSThread g_mainThread;
std::thread::id g_mainHostThread;
bool g_presenting = false;
thread_local OSThread* t_self = nullptr;

PortThread* pt_of(OSThread* t)
{
    auto it = g_threads.find(t);
    return it == g_threads.end() ? nullptr : it->second;
}

bool runnable(OSThread* t)
{
    PortThread* pt = pt_of(t);
    return pt != nullptr && pt->started && !pt->blocked && !pt->finished && t->suspend <= 0;
}

// Highest-priority (lowest number) runnable thread.
OSThread* best_ready()
{
    OSThread* best = nullptr;
    for (auto& [t, pt] : g_threads)
    {
        if (runnable(t) && (best == nullptr || t->priority < best->priority))
            best = t;
    }
    return best;
}

// Waits (g_sched held) until this thread is the one to run, then takes the token.
void acquire(std::unique_lock<std::mutex>& lk, OSThread* self)
{
    g_cv.wait(lk, [&] { return g_running == nullptr && !g_presenting && best_ready() == self; });
    g_running = self;
    self->state = OS_THREAD_STATE_RUNNING;
}

void release(OSThread* self)
{
    if (g_running == self)
        g_running = nullptr;
    if (self->state == OS_THREAD_STATE_RUNNING)
        self->state = OS_THREAD_STATE_READY;
    g_cv.notify_all();
}

// The running game thread lets a higher-priority ready thread run first.
void maybe_preempt(std::unique_lock<std::mutex>& lk)
{
    OSThread* self = t_self;
    if (self == nullptr || g_running != self)
        return;
    // Not with interrupts disabled: waiting for the token while holding the
    // interrupt lock deadlocks with the main thread presenting a frame (it
    // takes the interrupt lock, and nobody gets the token meanwhile). The
    // switch happens at the thread's next scheduling point instead.
    if (t_irqDisabled)
        return;
    OSThread* best = best_ready();
    if (best != nullptr && best != self && best->priority < self->priority)
    {
        release(self);
        acquire(lk, self);
    }
}

// Retrace emulation by the blocked main thread (g_sched held, token free).
void present_from_wait(std::unique_lock<std::mutex>& lk)
{
    g_presenting = true;
    lk.unlock();
    port_present_frame();
    lk.lock();
    g_presenting = false;
    g_cv.notify_all();
}

// Takes the run token back, then the interrupt lock if the thread held it.
// Always in this order (token, then interrupts): a thread that held the
// interrupt lock while queueing for the token could deadlock with the
// token's next owner (or the main thread presenting a frame), which needs
// the interrupt lock to run.
void reacquire(std::unique_lock<std::mutex>& lk, OSThread* self, bool hadIrq)
{
    acquire(lk, self);
    if (hadIrq)
    {
        lk.unlock();
        irq_lock();
        lk.lock();
    }
}

// Blocks the calling game thread until `done()` holds (checked with g_sched
// held). Gives up the interrupt lock and the run token meanwhile.
template <typename Pred>
void block_until(std::unique_lock<std::mutex>& lk, Pred done)
{
    OSThread* self = t_self;
    if (self == nullptr)
    {
        // Not a game thread (interrupt context): just wait.
        while (!done())
            g_cv.wait_for(lk, std::chrono::milliseconds(1));
        return;
    }
    if (done())
        return;
    bool hadIrq = t_irqDisabled;
    PortThread* pt = pt_of(self);
    pt->blocked = true;
    self->state = OS_THREAD_STATE_WAITING;
    release(self);
    if (hadIrq)
        irq_unlock();
    bool isMain = std::this_thread::get_id() == g_mainHostThread;
    while (!done())
    {
        if (isMain)
        {
            if (g_cv.wait_until(lk, port_retrace_deadline()) == std::cv_status::timeout && !done())
            {
                g_cv.wait(lk, [&] { return g_running == nullptr || done(); });
                if (!done())
                    present_from_wait(lk);
            }
        }
        else
        {
            g_cv.wait(lk);
        }
    }
    pt->blocked = false;
    self->state = OS_THREAD_STATE_READY;
    reacquire(lk, self, hadIrq);
}

unsigned long long& gen(const void* q)
{
    return g_queueGen[q];
}

void wake(const void* q)
{
    gen(q)++;
    g_cv.notify_all();
}

void thread_entry(OSThread* t)
{
    t_self = t;
    PortThread* pt;
    {
        std::unique_lock lk(g_sched);
        pt = pt_of(t);
        acquire(lk, t);
    }
    void* val = pt->func(pt->param);
    std::unique_lock lk(g_sched);
    t->val = val;
    t->state = OS_THREAD_STATE_MORIBUND;
    pt->finished = true;
    if (t_irqDisabled)
        irq_unlock();
    release(t);
    wake(&t->queueJoin);
}

#endif // !__EMSCRIPTEN__

// ---------------------------------------------------------------- OS arena
// The game carves its xfb, GX FIFO and heaps out of the arena. It lives in
// the game heap so pointers into it fit PTR_TO_U32. Larger than MEM1's 24MB:
// structs with pointers are bigger on PC.
constexpr size_t kArenaSize = 128u << 20;
void* s_arenaLo = nullptr;
void* s_arenaHi = nullptr;
} // namespace

extern "C" {

#ifdef __EMSCRIPTEN__
// Web builds have one host thread: the game's threads are fibers.
#include "../web/src/os_threads_web.inc"
#else
// ---------------------------------------------------------------- interrupts
BOOL OSDisableInterrupts(void)
{
    if (t_irqDisabled)
        return FALSE;
    irq_lock();
    return TRUE;
}

BOOL OSEnableInterrupts(void)
{
    if (!t_irqDisabled)
        return TRUE;
    irq_unlock();
    return FALSE;
}

BOOL OSRestoreInterrupts(BOOL level)
{
    if (level)
        return OSEnableInterrupts();
    return OSDisableInterrupts();
}

void port_interrupt_enter(void)
{
    OSDisableInterrupts();
}

void port_interrupt_leave(void)
{
    OSEnableInterrupts();
}

// ---------------------------------------------------------------- threads
void port_threads_init(void)
{
    std::unique_lock lk(g_sched);
    g_mainHostThread = std::this_thread::get_id();
    OSThread* t = &g_mainThread;
    t->state = OS_THREAD_STATE_RUNNING;
    t->suspend = 0;
    t->priority = t->base = 16;
    auto* pt = new PortThread();
    pt->os = t;
    pt->started = true;
    g_threads[t] = pt;
    t_self = t;
    g_running = t;
}

BOOL OSCreateThread(OSThread* thread, void* (*func)(void*), void* param, void* stack, u32 stackSize,
                    OSPriority priority, u16 attr)
{
    std::unique_lock lk(g_sched);
    thread->state = OS_THREAD_STATE_READY;
    thread->attr = attr;
    thread->suspend = 1;
    thread->priority = thread->base = priority;
    thread->val = nullptr;
    thread->queue = nullptr;
    thread->queueJoin.head = thread->queueJoin.tail = nullptr;
    thread->stackBase = (u8*)stack;
    thread->stackEnd = (u8*)stack - stackSize;
    thread->error = 0;
    PortThread* pt = pt_of(thread);
    if (pt == nullptr)
    {
        pt = new PortThread();
        g_threads[thread] = pt;
    }
    *pt = PortThread{};
    pt->os = thread;
    pt->func = func;
    pt->param = param;
    return TRUE;
}

s32 OSResumeThread(OSThread* thread)
{
    std::unique_lock lk(g_sched);
    s32 prev = thread->suspend;
    if (prev <= 0 && t_self == nullptr)
    {
        // An interrupt callback (DVD, ARQ, ...) resumes a thread that hasn't
        // suspended itself yet: on PC the "interrupt" can arrive before the
        // thread reaches OSSuspendThread, which on the GameCube's single CPU
        // it can't. Keep the resume for that OSSuspendThread.
        PortThread* pt = pt_of(thread);
        if (pt != nullptr && pt->started && !pt->finished)
            pt->pendingResume++;
        return prev;
    }
    if (prev > 0 && --thread->suspend == 0)
    {
        PortThread* pt = pt_of(thread);
        if (pt != nullptr && !pt->started)
        {
            pt->started = true;
            std::thread(thread_entry, thread).detach();
        }
        g_cv.notify_all();
        maybe_preempt(lk);
    }
    return prev;
}

s32 OSSuspendThread(OSThread* thread)
{
    std::unique_lock lk(g_sched);
    if (thread == t_self)
    {
        PortThread* pt = pt_of(thread);
        if (pt != nullptr && pt->pendingResume > 0)
        {
            pt->pendingResume--;
            return thread->suspend;
        }
    }
    s32 prev = thread->suspend++;
    if (thread == t_self && g_running == thread)
    {
        // Give the CPU away (and the interrupt lock) until someone resumes us.
        bool hadIrq = t_irqDisabled;
        release(thread);
        if (hadIrq)
        {
            lk.unlock();
            irq_unlock();
            lk.lock();
        }
        reacquire(lk, thread, hadIrq);
    }
    return prev;
}

BOOL OSIsThreadSuspended(OSThread* thread)
{
    return thread->suspend > 0;
}

BOOL OSIsThreadTerminated(OSThread* thread)
{
    return thread->state == OS_THREAD_STATE_MORIBUND || thread->state == 0;
}

OSThread* OSGetCurrentThread(void)
{
    return t_self != nullptr ? t_self : g_running;
}

void OSCancelThread(OSThread* thread)
{
    std::unique_lock lk(g_sched);
    PortThread* pt = pt_of(thread);
    if (pt == nullptr)
        return;
    pt->finished = true;
    thread->state = 0;
    if (thread == t_self)
    {
        // There's no portable way to stop a host thread from the inside:
        // give up the CPU for good.
        release(thread);
        if (t_irqDisabled)
            irq_unlock();
        g_cv.wait(lk, [] { return false; });
    }
    g_cv.notify_all();
}

void OSExitThread(void* val)
{
    std::unique_lock lk(g_sched);
    OSThread* self = t_self;
    if (self == nullptr)
        return;
    self->val = val;
    self->state = OS_THREAD_STATE_MORIBUND;
    pt_of(self)->finished = true;
    release(self);
    wake(&self->queueJoin);
    if (t_irqDisabled)
        irq_unlock();
    g_cv.wait(lk, [] { return false; });
}

void OSYieldThread(void)
{
    std::unique_lock lk(g_sched);
    OSThread* self = t_self;
    if (self == nullptr || g_running != self)
        return;
    bool hadIrq = t_irqDisabled;
    release(self);
    if (hadIrq)
    {
        lk.unlock();
        irq_unlock();
        lk.lock();
    }
    // A busy-waiting thread would otherwise take the token straight back: if
    // the blocked main thread owes a retrace, let it present first.
    if (std::chrono::steady_clock::now() >= port_retrace_deadline())
        g_cv.wait_for(lk, std::chrono::milliseconds(2), [] { return std::chrono::steady_clock::now() < port_retrace_deadline(); });
    lk.unlock();
    std::this_thread::yield();
    lk.lock();
    reacquire(lk, self, hadIrq);
}

void OSInitThreadQueue(OSThreadQueue* queue)
{
    queue->head = nullptr;
    queue->tail = nullptr;
}

// Returns after the next OSWakeupThread on the queue (callers re-check their
// condition, as on the GameCube).
void OSSleepThread(OSThreadQueue* queue)
{
    std::unique_lock lk(g_sched);
    unsigned long long start = gen(queue);
    PortThread* pt = t_self != nullptr ? pt_of(t_self) : nullptr;
    if (pt != nullptr)
        pt->sleepQueue = queue;
    block_until(lk, [&] { return gen(queue) != start; });
    if (pt != nullptr)
        pt->sleepQueue = nullptr;
}

void OSWakeupThread(OSThreadQueue* queue)
{
    std::unique_lock lk(g_sched);
    wake(queue);
    // The sleepers are runnable from now on. Without this they only counted as ready once their host
    // thread got around to re-checking, so a woken higher-priority thread never preempted the waker:
    // the draw thread (priority 12) then ran whenever the main thread next blocked, e.g. in the middle
    // of building the next frame's draw list while a character model loads (half-drawn frames: the
    // character select's banner/grid/bottom bar flickered out on alternate frames).
    for (auto& [t, pt] : g_threads)
    {
        if (pt->sleepQueue == queue && pt->blocked)
        {
            pt->sleepQueue = nullptr;
            pt->blocked = false;
            t->state = OS_THREAD_STATE_READY;
        }
    }
    maybe_preempt(lk);
}

// ---------------------------------------------------------------- semaphores
void OSInitSemaphore(OSSemaphore* sem, s32 count)
{
    std::unique_lock lk(g_sched);
    sem->count = count;
    OSInitThreadQueue(&sem->queue);
}

s32 OSWaitSemaphore(OSSemaphore* sem)
{
    std::unique_lock lk(g_sched);
    block_until(lk, [&] { return sem->count > 0; });
    return sem->count--;
}

s32 OSTryWaitSemaphore(OSSemaphore* sem)
{
    std::unique_lock lk(g_sched);
    s32 count = sem->count;
    if (count > 0)
        sem->count--;
    return count;
}

s32 OSSignalSemaphore(OSSemaphore* sem)
{
    std::unique_lock lk(g_sched);
    s32 count = sem->count++;
    wake(&sem->queue);
    maybe_preempt(lk);
    return count;
}

s32 OSGetSemaphoreCount(OSSemaphore* sem)
{
    return sem->count;
}

// ---------------------------------------------------------------- messages
void OSInitMessageQueue(OSMessageQueue* mq, OSMessage* msgArray, s32 msgCount)
{
    std::unique_lock lk(g_sched);
    OSInitThreadQueue(&mq->queueSend);
    OSInitThreadQueue(&mq->queueReceive);
    mq->msgArray = msgArray;
    mq->msgCount = msgCount;
    mq->firstIndex = 0;
    mq->usedCount = 0;
}

BOOL OSSendMessage(OSMessageQueue* mq, OSMessage msg, s32 flags)
{
    std::unique_lock lk(g_sched);
    if (mq->usedCount >= mq->msgCount)
    {
        if (!(flags & OS_MESSAGE_BLOCK))
            return FALSE;
        block_until(lk, [&] { return mq->usedCount < mq->msgCount; });
    }
    mq->msgArray[(mq->firstIndex + mq->usedCount) % mq->msgCount] = msg;
    mq->usedCount++;
    wake(&mq->queueReceive);
    maybe_preempt(lk);
    return TRUE;
}

BOOL OSJamMessage(OSMessageQueue* mq, OSMessage msg, s32 flags)
{
    std::unique_lock lk(g_sched);
    if (mq->usedCount >= mq->msgCount)
    {
        if (!(flags & OS_MESSAGE_BLOCK))
            return FALSE;
        block_until(lk, [&] { return mq->usedCount < mq->msgCount; });
    }
    mq->firstIndex = (mq->firstIndex + mq->msgCount - 1) % mq->msgCount;
    mq->msgArray[mq->firstIndex] = msg;
    mq->usedCount++;
    wake(&mq->queueReceive);
    maybe_preempt(lk);
    return TRUE;
}

BOOL OSReceiveMessage(OSMessageQueue* mq, OSMessage* msg, s32 flags)
{
    std::unique_lock lk(g_sched);
    if (mq->usedCount == 0)
    {
        if (!(flags & OS_MESSAGE_BLOCK))
            return FALSE;
        block_until(lk, [&] { return mq->usedCount != 0; });
    }
    if (msg != nullptr)
        *msg = mq->msgArray[mq->firstIndex];
    mq->firstIndex = (mq->firstIndex + 1) % mq->msgCount;
    mq->usedCount--;
    wake(&mq->queueSend);
    maybe_preempt(lk);
    return TRUE;
}

// Blocks a non-main thread until the next presented frame (VIWaitForRetrace
// off the main thread).
void port_wait_retrace(unsigned int count)
{
    std::unique_lock lk(g_sched);
    block_until(lk, [&] { return port_retrace_count() != count; });
}

void port_retrace_notify(void)
{
    std::unique_lock lk(g_sched);
    g_cv.notify_all();
}

#endif // __EMSCRIPTEN__

// ---------------------------------------------------------------- misc OS
void OSClearStack(u8 val)
{
    (void)val;
}

u32 OSGetConsoleType(void)
{
    return 0x10000002; // OS_CONSOLE_RETAIL2
}

static u32 s_progressiveMode = 0;
u32 OSGetProgressiveMode(void) { return s_progressiveMode; }
void OSSetProgressiveMode(u32 on) { s_progressiveMode = on; }

static u32 s_soundMode = 1; // stereo
u32 OSGetSoundMode(void) { return s_soundMode; }
void OSSetSoundMode(u32 mode) { s_soundMode = mode; }

u8 OSGetLanguage(void) { return 0; } // English

u32 OSGetResetCode(void) { return 0; }
BOOL OSGetResetButtonState(void) { return FALSE; }

void OSResetSystem(int reset, u32 resetCode, BOOL forceMenu)
{
    (void)reset;
    (void)resetCode;
    (void)forceMenu;
    fprintf(stderr, "[os] OSResetSystem: exiting\n");
#ifdef __EMSCRIPTEN__
    emscripten_force_exit(0);
#endif
    std::exit(0);
}

OSErrorHandler OSSetErrorHandler(OSError error, OSErrorHandler handler)
{
    (void)error;
    (void)handler;
    return nullptr;
}

// ---------------------------------------------------------------- OS arena
// Replaces aurora's OSArena.cpp (all of its symbols are defined here).
void* OSGetArenaHi(void) { return s_arenaHi; }
void* OSGetArenaLo(void) { return s_arenaLo; }
void OSSetArenaHi(void* newHi) { s_arenaHi = newHi; }
void OSSetArenaLo(void* newLo) { s_arenaLo = newLo; }

void* OSAllocFromArenaLo(u32 size, u32 align)
{
    uintptr_t p = ((uintptr_t)s_arenaLo + align - 1) & ~(uintptr_t)(align - 1);
    s_arenaLo = (void*)((p + size + align - 1) & ~(uintptr_t)(align - 1));
    return (void*)p;
}

void* OSAllocFromArenaHi(u32 size, u32 align)
{
    uintptr_t p = (uintptr_t)s_arenaHi & ~(uintptr_t)(align - 1);
    p = (p - size) & ~(uintptr_t)(align - 1);
    s_arenaHi = (void*)p;
    return (void*)p;
}

// The SDK reads a few boot globals from low MEM1 (__OSBusClock at 0x800000F8,
// __OSCoreClock, ...) through OSBaseAddress. Back it with a zeroed block
// holding the values the boot ROM provides, and set up the arena.
void port_os_init(void)
{
    static u32 s_lowMem[0x3100 / sizeof(u32)];
    if (OSBaseAddress == 0)
        OSBaseAddress = (uintptr_t)s_lowMem;
    __OSBusClock = OS_BUS_CLOCK;
    __OSCoreClock = 486000000; // Gekko
    if (s_arenaLo == nullptr)
    {
        s_arenaLo = port_heap_alloc(kArenaSize, 32);
        if (s_arenaLo == nullptr)
        {
            fprintf(stderr, "FATAL: couldn't allocate the OS arena\n");
            std::abort();
        }
        s_arenaHi = (u8*)s_arenaLo + kArenaSize;
    }
    port_threads_init();
}

} // extern "C"

// aurora's OSInit calls this (internal, C++ linkage); the arena is ours.
void AuroraInitArena() { }
