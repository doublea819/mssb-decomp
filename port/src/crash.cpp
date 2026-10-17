#ifdef __APPLE__
#include <TargetConditionals.h>
#endif
// Crash and hang handling.
//
// A crash (bad access, abort, failed assertion, ...) writes a backtrace to
// stderr and to crash.log in the user data folder, then exits immediately, so
// the window never sits frozen waiting to be force-quit.
//
// A watchdog thread exits the same way if the game stops presenting frames for
// too long (MSSB_WATCHDOG_SECS, default 30; 0 disables it). Before exiting
// it signals the main thread so the log shows where it was stuck.

#include <execinfo.h>
#include <sys/ucontext.h>
#include <fcntl.h>
#include <mach-o/dyld.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <thread>

namespace {
char s_logPath[1024] = "";
uintptr_t s_faultPc = 0;
uintptr_t s_faultLr = 0;
pthread_t s_mainThread;
std::atomic<int64_t> s_lastFrameMs{0};
std::atomic<bool> s_handling{false};
constexpr int kWatchdogSignal = SIGUSR1;

int64_t now_ms()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

// Async-signal-safe helpers.
void write_str(int fd, const char* s)
{
    if (fd >= 0)
        write(fd, s, strlen(s));
}

void write_hex(int fd, uintptr_t v)
{
    char buf[19] = "0x";
    for (int i = 0; i < 16; i++)
        buf[2 + i] = "0123456789abcdef"[(v >> (60 - i * 4)) & 0xF];
    buf[18] = '\0';
    write_str(fd, buf);
}

void dump(int fd, const char* reason, void* faultAddr)
{
    write_str(fd, "\n==== Mario Superstar Baseball crashed: ");
    write_str(fd, reason);
    if (faultAddr != nullptr)
    {
        write_str(fd, " at address ");
        write_hex(fd, (uintptr_t)faultAddr);
    }
    write_str(fd, " ====\nfault pc: ");
    write_hex(fd, s_faultPc);
    write_str(fd, " lr: ");
    write_hex(fd, s_faultLr);
    write_str(fd, "\nimage slide: ");
    write_hex(fd, (uintptr_t)_dyld_get_image_vmaddr_slide(0));
    write_str(fd, "\n");
    void* frames[64];
    int n = backtrace(frames, 64);
    backtrace_symbols_fd(frames, n, fd);
    write_str(fd, "====\n");
}

[[noreturn]] void die(const char* reason, void* faultAddr)
{
    // Only the first crashing thread reports; others just wait to be killed.
    if (s_handling.exchange(true))
    {
        for (;;)
            pause();
    }
    dump(STDERR_FILENO, reason, faultAddr);
    if (s_logPath[0] != '\0')
    {
        int fd = open(s_logPath, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd >= 0)
        {
            dump(fd, reason, faultAddr);
            close(fd);
        }
        write_str(STDERR_FILENO, "Crash log written to ");
        write_str(STDERR_FILENO, s_logPath);
        write_str(STDERR_FILENO, "\n");
    }
    _exit(1);
}

void crash_handler(int sig, siginfo_t* info, void* ctx)
{
    if (ctx != nullptr)
    {
        ucontext_t* uc = (ucontext_t*)ctx;
        s_faultPc = (uintptr_t)uc->uc_mcontext->__ss.__pc;
        s_faultLr = (uintptr_t)uc->uc_mcontext->__ss.__lr;
    }
    const char* name = "signal";
    switch (sig)
    {
    case SIGSEGV: name = "SIGSEGV (bad memory access)"; break;
    case SIGBUS: name = "SIGBUS (bad memory access)"; break;
    case SIGILL: name = "SIGILL (illegal instruction)"; break;
    case SIGFPE: name = "SIGFPE (arithmetic error)"; break;
    case SIGABRT: name = "SIGABRT (abort / fatal error)"; break;
    case SIGTRAP: name = "SIGTRAP (trap / assertion)"; break;
    case kWatchdogSignal: name = "hang: no frame presented within the watchdog timeout (main thread stack below)"; break;
    }
    void* addr = (sig == SIGSEGV || sig == SIGBUS) && info != nullptr ? info->si_addr : nullptr;
    die(name, addr);
}

void watchdog(int timeoutSecs)
{
    const int64_t timeoutMs = (int64_t)timeoutSecs * 1000;
    for (;;)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        int64_t last = s_lastFrameMs.load();
        if (last != 0 && now_ms() - last > timeoutMs)
        {
#if defined(__APPLE__) && !TARGET_OS_IPHONE
            // MSSB_HANG_SAMPLE=<file>: every thread's stack (macOS `sample`).
            if (const char* out = getenv("MSSB_HANG_SAMPLE"))
            {
                char cmd[1200];
                snprintf(cmd, sizeof(cmd), "sample %d 1 -mayDie -file '%s' >/dev/null 2>&1", (int)getpid(), out);
                system(cmd);
            }
#endif
            // Have the main thread dump its own stack, then make sure we exit.
            pthread_kill(s_mainThread, kWatchdogSignal);
            std::this_thread::sleep_for(std::chrono::seconds(2));
            die("hang: main thread unresponsive", nullptr);
        }
    }
}
} // namespace

extern "C" {

void port_crash_init(const char* userPath)
{
    s_mainThread = pthread_self();
    if (userPath != nullptr && userPath[0] != '\0')
        snprintf(s_logPath, sizeof(s_logPath), "%s/crash.log", userPath);

#if !TARGET_OS_TV // tvOS has no sigaltstack
    // Alternate stack so stack overflows can still be reported.
    static char altStack[256 * 1024];
    stack_t ss{};
    ss.ss_sp = altStack;
    ss.ss_size = sizeof(altStack);
    sigaltstack(&ss, nullptr);
#endif

    struct sigaction sa{};
    sa.sa_sigaction = crash_handler;
    sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
    sigemptyset(&sa.sa_mask);
    for (int sig : {SIGSEGV, SIGBUS, SIGILL, SIGFPE, SIGABRT, SIGTRAP, kWatchdogSignal})
        sigaction(sig, &sa, nullptr);

#if TARGET_OS_IPHONE
    // iOS freezes the app in the background: a frame gap there isn't a hang.
    int timeoutSecs = 0;
#else
    int timeoutSecs = 30;
#endif
    if (const char* env = getenv("MSSB_WATCHDOG_SECS"))
        timeoutSecs = atoi(env);
    if (timeoutSecs > 0)
        std::thread(watchdog, timeoutSecs).detach();
}

// Called every presented frame (and while waiting on a minimized window).
void port_crash_heartbeat(void)
{
    s_lastFrameMs.store(now_ms());
}
}
