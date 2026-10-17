#include "port/game_heap.h"

#include <sys/mman.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <new>

#include <execinfo.h>
#include <cstring>
#include <deque>

extern "C" {
void* dlmemalign(size_t alignment, size_t bytes);
void* dlmalloc(size_t bytes);
void dlfree(void* mem);
size_t dlmalloc_usable_size(void* mem);
}

// Heap debug mode (MSSB_HEAP_DEBUG=1): freed blocks are filled with 0xDD
// and held in a quarantine before being reused; writes to quarantined memory
// are reported when the block leaves quarantine, and the free-time backtrace is
// kept so port_heap_report_freed() can say who freed a block.
namespace {
struct Quarantined
{
    void* ptr;
    size_t size;
    void* frames[16];
    int numFrames;
};
constexpr size_t kQuarantineBytes = 256u << 20;
std::mutex s_debugMutex;
std::deque<Quarantined>* s_quarantine = nullptr;
size_t s_quarantinedBytes = 0;
int s_heapDebug = -1;
thread_local bool t_inQuarantine = false;

bool heap_debug()
{
    if (s_heapDebug < 0)
    {
        const char* env = getenv("MSSB_HEAP_DEBUG");
        s_heapDebug = (env != nullptr && env[0] != '0') ? 1 : 0;
    }
    return s_heapDebug == 1;
}

void check_released(const Quarantined& q)
{
    const unsigned char* p = (const unsigned char*)q.ptr;
    for (size_t i = 0; i < q.size; i++)
    {
        if (p[i] != 0xDD)
        {
            fprintf(stderr, "[heap] write after free: block %p (size %zu) modified at +0x%zx; freed at:\n", q.ptr, q.size, i);
            backtrace_symbols_fd((void* const*)q.frames, q.numFrames, 2);
            return;
        }
    }
}

void quarantine_free(void* p)
{
    Quarantined q;
    q.ptr = p;
    q.size = dlmalloc_usable_size(p);
    memset(p, 0xDD, q.size);
    q.numFrames = backtrace(q.frames, 16);
    std::lock_guard lk(s_debugMutex);
    t_inQuarantine = true;
    if (s_quarantine == nullptr)
        s_quarantine = new (dlmalloc(sizeof(std::deque<Quarantined>))) std::deque<Quarantined>();
    s_quarantine->push_back(q);
    s_quarantinedBytes += q.size;
    while (s_quarantinedBytes > kQuarantineBytes && !s_quarantine->empty())
    {
        Quarantined old = s_quarantine->front();
        s_quarantine->pop_front();
        s_quarantinedBytes -= old.size;
        check_released(old);
        dlfree(old.ptr);
    }
    t_inQuarantine = false;
}
} // namespace

namespace {
constexpr size_t kReserveSize = 4ull << 30;
// Offset 0 is reserved so a 32-bit offset of 0 can mean null. The heap stops
// below PORT_PTR32_EXT_BASE: 32-bit values from there up name pointers outside
// the heap (static data), see port/include/port/ptr32.h.
constexpr size_t kUsableSize = 0xE0000000u;
constexpr size_t kGuardSize = 1 << 20;

uintptr_t s_base = 0;
size_t s_reserved = kReserveSize; // smaller on Apple TV (see init_region)
size_t s_usable = kUsableSize;
uintptr_t s_top = 0;       // current break
uintptr_t s_committed = 0; // end of the read/write mapped part

void init_region()
{
    // Reserve twice the size and keep the 4GB-aligned part, so the low 32 bits
    // of any game pointer equal its offset from the heap base. Code that
    // truncates pointers to 32-bit "physical addresses" (MusyX, DSP command
    // lists) can then be translated back with port_heap_base() + offset.
    void* p = mmap(nullptr, kReserveSize * 2, PROT_NONE, MAP_PRIVATE | MAP_ANON | MAP_NORESERVE, -1, 0);
    if (p == MAP_FAILED)
    {
        // A small address space (Apple TV: no extended-virtual-addressing entitlement). The
        // base only has to be 4 GB-aligned (low 32 bits = offset); the heap itself can be
        // smaller. Try 4 GB-aligned addresses with smaller and smaller sizes.
        static const size_t kSizes[] = {kReserveSize, 2ull << 30, 1ull << 30, 512ull << 20};
        for (size_t size : kSizes)
        {
            for (uintptr_t hint = kReserveSize; hint <= 64 * kReserveSize; hint += kReserveSize)
            {
                void* q = mmap((void*)hint, size, PROT_NONE, MAP_PRIVATE | MAP_ANON | MAP_NORESERVE, -1, 0);
                if (q == MAP_FAILED)
                    continue;
                if ((uintptr_t)q == hint)
                {
                    s_base = hint;
                    s_reserved = size;
                    s_usable = size < kUsableSize ? size : kUsableSize;
                    s_top = s_base + kGuardSize;
                    s_committed = s_top;
                    fprintf(stderr, "[heap] reserved %zu MB at %#lx\n", size >> 20, (unsigned long)hint);
                    return;
                }
                munmap(q, size);
            }
        }
        fprintf(stderr, "FATAL: couldn't reserve the game heap\n");
        abort();
    }
    uintptr_t start = (uintptr_t)p;
    uintptr_t aligned = (start + kReserveSize - 1) & ~(uintptr_t)(kReserveSize - 1);
    if (aligned > start)
        munmap(p, aligned - start);
    uintptr_t end = start + kReserveSize * 2;
    if (end > aligned + kReserveSize)
        munmap((void*)(aligned + kReserveSize), end - (aligned + kReserveSize));
    s_base = aligned;
    s_top = s_base + kGuardSize;
    s_committed = s_top;
}

void ensure_init()
{
    static std::once_flag once;
    std::call_once(once, init_region);
}
} // namespace

// Guard-page mode (MSSB_HEAP_GUARD=1): every allocation gets its own pages,
// placed so it ends right before an inaccessible guard page (overruns fault at
// the faulting write). Freed pages become inaccessible and are only reused
// after a quarantine, so use-after-free faults too. Uses lots of memory.
namespace {
struct GuardBlock
{
    uintptr_t run;  // start of the page run (accessible part)
    size_t pages;   // accessible pages (guard page follows)
};
struct MallocAlloc
{
    using value_type = std::pair<const uintptr_t, GuardBlock>;
};
std::mutex s_guardMutex;
int s_heapGuard = -1;
size_t s_pageSize = 0;

// Simple open-addressing table mallocated with the system allocator so it
// never recurses into the game heap.
struct GuardTable
{
    struct Entry
    {
        uintptr_t key;
        GuardBlock val;
    };
    Entry* entries = nullptr;
    size_t capacity = 0;
    size_t count = 0;

    static size_t hash(uintptr_t k) { return (k >> 4) * 0x9E3779B97F4A7C15ull; }
    void grow()
    {
        size_t newCap = capacity ? capacity * 2 : (1 << 16);
        Entry* old = entries;
        size_t oldCap = capacity;
        entries = (Entry*)calloc(newCap, sizeof(Entry));
        capacity = newCap;
        count = 0;
        for (size_t i = 0; i < oldCap; i++)
            if (old[i].key > 1)
                insert(old[i].key, old[i].val);
        free(old);
    }
    void insert(uintptr_t key, GuardBlock val)
    {
        if ((count + 1) * 2 > capacity)
            grow();
        size_t i = hash(key) & (capacity - 1);
        while (entries[i].key > 1)
            i = (i + 1) & (capacity - 1);
        entries[i] = {key, val};
        count++;
    }
    bool take(uintptr_t key, GuardBlock* out)
    {
        if (capacity == 0)
            return false;
        size_t i = hash(key) & (capacity - 1);
        while (entries[i].key != 0)
        {
            if (entries[i].key == key)
            {
                *out = entries[i].val;
                entries[i].key = 1; // tombstone
                return true;
            }
            i = (i + 1) & (capacity - 1);
        }
        return false;
    }
};
GuardTable s_guardTable;

struct FreedRun
{
    uintptr_t run;
    size_t pages;
};
FreedRun* s_freedRuns = nullptr; // FIFO ring
size_t s_freedHead = 0, s_freedTail = 0, s_freedCap = 0, s_freedPages = 0;
constexpr size_t kGuardQuarantinePages = 16384; // 256MB of 16K pages


bool heap_guard()
{
    if (s_heapGuard < 0)
    {
        const char* env = getenv("MSSB_HEAP_GUARD");
        s_heapGuard = (env != nullptr && env[0] != '0') ? 1 : 0;
        s_pageSize = (size_t)getpagesize();
    }
    return s_heapGuard == 1;
}

uintptr_t s_guardTop = 0; // bump pointer for page runs, from the top of the region down

void* guard_alloc(size_t size, size_t alignment)
{
    std::lock_guard lk(s_guardMutex);
    if (alignment < 16)
        alignment = 16;
    size_t rounded = (size + alignment - 1) & ~(alignment - 1);
    size_t pages = (rounded + s_pageSize - 1) / s_pageSize;
    if (pages == 0)
        pages = 1;
    uintptr_t run = 0;
    // Reuse the oldest freed run once the quarantine is full, if it fits.
    if (s_freedPages > kGuardQuarantinePages && s_freedHead != s_freedTail)
    {
        FreedRun fr = s_freedRuns[s_freedHead];
        if (fr.pages >= pages)
        {
            s_freedHead = (s_freedHead + 1) % s_freedCap;
            s_freedPages -= fr.pages;
            run = fr.run;
            pages = fr.pages;
        }
    }
    if (run == 0)
    {
        uintptr_t need = (pages + 1) * s_pageSize;
        if (s_guardTop == 0)
            s_guardTop = s_base + s_reserved;
        if (s_guardTop - need < s_top + (64u << 20))
        {
            fprintf(stderr, "[heap] guard mode out of address space\n");
            abort();
        }
        s_guardTop -= need;
        run = s_guardTop;
    }
    mprotect((void*)run, pages * s_pageSize, PROT_READ | PROT_WRITE);
    // The page after the run stays PROT_NONE (reserved region default).
    uintptr_t end = run + pages * s_pageSize;
    uintptr_t user = (end - rounded) & ~(alignment - 1);
    s_guardTable.insert(user, {run, pages});
    return (void*)user;
}

bool guard_free(void* p)
{
    std::lock_guard lk(s_guardMutex);
    GuardBlock b;
    if (!s_guardTable.take((uintptr_t)p, &b))
        return false;
    mprotect((void*)b.run, b.pages * s_pageSize, PROT_NONE);
    if (s_freedCap == 0)
    {
        s_freedCap = 1 << 20;
        s_freedRuns = (FreedRun*)malloc(s_freedCap * sizeof(FreedRun));
    }
    s_freedRuns[s_freedTail] = {b.run, b.pages};
    s_freedTail = (s_freedTail + 1) % s_freedCap;
    s_freedPages += b.pages;
    return true;
}
} // namespace

extern "C" {

// Called by dlmalloc with its own lock held.
void* port_heap_sbrk(ptrdiff_t increment)
{
    ensure_init();
    uintptr_t old = s_top;
    if (increment <= 0)
        return (void*)old;
    uintptr_t newTop = old + (uintptr_t)increment;
    if (newTop > s_base + s_usable)
        return (void*)~(uintptr_t)0; // MFAIL
    if (newTop > s_committed)
    {
        const uintptr_t page = (uintptr_t)getpagesize();
        uintptr_t newCommitted = (newTop + page - 1) & ~(page - 1);
        if (mprotect((void*)s_committed, newCommitted - s_committed, PROT_READ | PROT_WRITE) != 0)
            return (void*)~(uintptr_t)0;
        s_committed = newCommitted;
    }
    s_top = newTop;
    return (void*)old;
}

void* port_heap_alloc(size_t size, size_t alignment)
{
    ensure_init();
    if (size == 0)
        size = 1;
    if (heap_guard())
        return guard_alloc(size, alignment);
    if (alignment <= 16)
        return dlmalloc(size);
    return dlmemalign(alignment, size);
}

void port_heap_free(void* p)
{
    if (p == nullptr)
        return;
    if (!port_heap_contains(p))
    {
        // Allocated by the system allocator (shouldn't happen for game memory).
        free(p);
        return;
    }
    if (heap_guard() && guard_free(p))
        return;
    if (heap_debug() && !t_inQuarantine)
    {
        quarantine_free(p);
        return;
    }
    dlfree(p);
}

// Debug helper: if p is inside a quarantined (freed) block, print who freed it.
void port_heap_report_freed(const void* p)
{
    if (!heap_debug())
        return;
    std::lock_guard lk(s_debugMutex);
    if (s_quarantine == nullptr)
        return;
    for (auto it = s_quarantine->rbegin(); it != s_quarantine->rend(); ++it)
    {
        if ((const char*)p >= (const char*)it->ptr && (const char*)p < (const char*)it->ptr + it->size)
        {
            fprintf(stderr, "[heap] %p is inside freed block %p (size %zu), freed at:\n", p, it->ptr, it->size);
            backtrace_symbols_fd((void* const*)it->frames, it->numFrames, 2);
            return;
        }
    }
    fprintf(stderr, "[heap] %p is not in a quarantined block\n", p);
}

int port_heap_pointer_like(uintptr_t v)
{
    return v > 0xFFFFFFFFu && port_heap_contains((const void*)v);
}

uintptr_t port_heap_base(void)
{
    ensure_init();
    return s_base;
}

int port_heap_contains(const void* p)
{
    uintptr_t v = (uintptr_t)p;
    return s_base != 0 && v >= s_base && v < s_base + s_reserved;
}

} // extern "C"
