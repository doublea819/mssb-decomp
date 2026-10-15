// Debug tracing for the boot loop: MSSB_TRACE_TASKS=1 prints the scene task
// list and MSSB_TRACE_DRAW=1 the draw callbacks of a frame whenever they
// change, with symbol names.
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* sym_name(void* p)
{
    Dl_info info;
    if (p != NULL && dladdr(p, &info) && info.dli_sname != NULL)
        return info.dli_sname;
    return "?";
}

const char* port_sym_name(void* p) { return sym_name(p); }

// funcs: the root task's function followed by the list's (count entries).
void port_trace_tasks(void** funcs, int count)
{
    static int enabled = -1;
    static void* last[64];
    static int lastCount = -1;
    if (enabled < 0)
        enabled = getenv("MSSB_TRACE_TASKS") != NULL;
    if (!enabled)
        return;
    if (count > 64)
        count = 64;
    if (count == lastCount && memcmp(last, funcs, (size_t)count * sizeof(void*)) == 0)
        return;
    memcpy(last, funcs, (size_t)count * sizeof(void*));
    lastCount = count;
    fprintf(stderr, "[tasks]");
    for (int i = 0; i < count; i++)
        fprintf(stderr, " %s", sym_name(funcs[i]));
    fprintf(stderr, "\n");
}

// funcs: the enabled draw-list callbacks of one frame, in order.
void port_trace_draw(void** funcs, int count)
{
    static int enabled = -1;
    static void* last[128];
    static int lastCount = -1;
    if (enabled < 0)
        enabled = getenv("MSSB_TRACE_DRAW") != NULL;
    if (!enabled)
        return;
    if (count > 128)
        count = 128;
    if (count == lastCount && memcmp(last, funcs, (size_t)count * sizeof(void*)) == 0)
        return;
    memcpy(last, funcs, (size_t)count * sizeof(void*));
    lastCount = count;
    {
        extern unsigned int port_spani_trace_frame;
        fprintf(stderr, "[draw] f=%u", port_spani_trace_frame);
    }
    for (int i = 0; i < count; i++)
        fprintf(stderr, " %s", sym_name(funcs[i]));
    fprintf(stderr, "\n");
}

// MSSB_TRACE_GAME=1: print a tagged state value whenever it changes
// (loader state machines). Up to 16 tags.
void port_trace_value(const char* tag, int value)
{
    static int enabled = -1;
    static const char* tags[48];
    static int values[48];
    if (enabled < 0)
        enabled = getenv("MSSB_TRACE_GAME") != NULL;
    if (!enabled)
        return;
    for (int i = 0; i < 48; i++)
    {
        if (tags[i] == NULL)
        {
            tags[i] = tag;
            values[i] = value;
            fprintf(stderr, "[state] %s %d\n", tag, value);
            return;
        }
        if (tags[i] == tag)
        {
            if (values[i] != value)
            {
                values[i] = value;
                fprintf(stderr, "[state] %s %d\n", tag, value);
            }
            return;
        }
    }
}

// Symbol name of a code address (debug traces).
const char* port_symbol_name(void* p)
{
    return sym_name(p);
}

// MSSB_TRACE_MAP=1: every 30 calls, the challenge map's walkers
// (MenuCtx.entries): node (locationIndex>targetLocation) and x/z position.
// nodeOffset: targetLocation, followed by locationIndex (s16 each).
void port_trace_map(const void* entries, int stride, int count, int mode, int nodeOffset)
{
    static int enabled = -1;
    static int n;
    if (enabled < 0)
        enabled = getenv("MSSB_TRACE_MAP") != NULL;
    if (!enabled || n++ % 30 != 0)
        return;
    fprintf(stderr, "[map] %d mode %d", n - 1, mode);
    for (int i = 0; i < count; i++)
    {
        const char* e = (const char*)entries + i * stride;
        const float* pos = (const float*)e;
        const short* node = (const short*)(e + nodeOffset);
        fprintf(stderr, " %d:%d>%d(%.0f,%.0f)", i, node[1], node[0], pos[0], pos[2]);
    }
    fprintf(stderr, "\n");
}
