#include "main/file_800A7C08.h"
#include "static/Pad.h"
extern PadState lbl_803C77B8[4];
#include "main/file_800A6870.h"
#include "Dolphin/os.h"
#include "Dolphin/gx.h"
#include "Dolphin/vi.h"
#include "Dolphin/card.h"
#include "Dolphin/dvd.h"
#include "Dolphin/ai.h"
#include "Dolphin/pad.h"
#include "stl/mem.h"
#include "stl/string.h"
#include "charPipeline/texPalette.h"
#include "main/file_800B0724.h"

extern OSThread* GXSetCurrentGXThread(void);
extern s32 OSSignalSemaphore(OSSemaphore* sem);

// .text:0x800A7C08 size:0x144
// NONMATCHING 99.6%: int->float magic constant and 0.0f/1.0f live in unsplit .sdata2 (reloc names differ); r3/r4 swapped in the callback loop
#if NONMATCHING
void* fn_800A7C08(void* arg) {
    GXRenderModeObj* rmode;
    DrawCallbackNode* node;
    uintptr_t next;

    lbl_803C7420.field = 0;
    while (TRUE) {
        OSSleepThread(&lbl_803C7420.drawQueue);
        GXSetCurrentGXThread();
        rmode = lbl_803C7420.renderMode;
        lbl_803C7420.drawing = TRUE;
        if (rmode->field_rendering) {
            GXSetViewportJitter(0.0f, 0.0f, rmode->fbWidth, rmode->efbHeight, 0.0f, 1.0f, VIGetNextField());
        } else {
            GXSetViewport(0.0f, 0.0f, rmode->fbWidth, rmode->efbHeight, 0.0f, 1.0f);
        }
        GXInvalidateVtxCache();
        node = (DrawCallbackNode*)lbl_803C7420.drawList;
#ifdef TARGET_PC
        {
            extern void port_trace_draw(void** funcs, int count);
            void* funcs[128];
            int n = 0;
            DrawCallbackNode* q = node;
            while (q->next.raw != 0 && n < 128) {
                if (!(q->next.raw & 1) && (q->next.raw & 2) == lbl_803C7420.field && q->func != NULL) {
                    funcs[n++] = (void*)q->func;
                }
                q = (DrawCallbackNode*)(q->next.raw & ~(uintptr_t)3);
            }
            port_trace_draw(funcs, n);
        }
#endif
        while (TRUE) {
            next = node->next.raw;
            if (next == 0) {
                break;
            }
            if (!(next & 1) && (next & 2) == lbl_803C7420.field) {
                if (node->func != NULL) {
                    // The callbacks get their node in r3 (SpriteDrawCmd etc.).
                    ((void (*)(DrawCallbackNode*))node->func)(node);
                }
            }
            node = (DrawCallbackNode*)(next & ~3);
        }
#ifdef TARGET_PC
        {
            // aurora reads vertex arrays, textures and TLUTs from game memory
            // when its FIFO thread processes a draw, which can lag far behind
            // (texture hashing, pipeline compiles). Finish this pass's draws
            // before the main thread's update rewrites that memory.
            extern void port_draw_pass_done(void);
            port_draw_pass_done();
        }
#endif
        lbl_803C7420.drawing = FALSE;
        OSSignalSemaphore(&lbl_803C7420.drawDone);
    }
}
#endif

// .text:0x800A7D4C size:0x30
void fn_800A7D4C(s32 index, DrawCallbackNode* node) {
#ifdef TARGET_PC
    // Linking the node that already heads this list would point it at itself and the draw thread
    // would loop on it forever (seen with a doubled effect task). Skip the duplicate.
    if ((lbl_803C7420.drawList[index].raw & ~(uintptr_t)3) == (uintptr_t)node) {
        return;
    }
    node->next.raw = (lbl_803C7420.drawList[index].raw & ~(uintptr_t)3) | (node->next.raw & 3);
#else
    node->next.bits.addr = lbl_803C7420.drawList[index].bits.addr;
#endif
    lbl_803C7420.drawList[index].raw = (uintptr_t)node | 1;
}

// .text:0x800A7D7C size:0x34
void fn_800A7D7C(DrawLink* list, s32 count) {
    lbl_803C7420.drawList = list;
    count--;
    do {
        list->raw = (uintptr_t)(list + 1) | 1;
        list++;
    } while (--count != 0);
    list->raw = 0;
}

// .text:0x800A7DB0 size:0x50
void fn_800A7DB0(void) {
#ifdef TARGET_PC
    // Both draw passes are done: the next retrace may present this frame
    // (aurora presents the live EFB, so earlier retraces must not).
    extern void port_vi_frame_done(void);
    port_vi_frame_done();
#endif
    OSSleepThread(&lbl_803C7420.retraceQueue);
    GXSetColorUpdate(GX_TRUE);
    VIFlush();
    GXDrawDone();
    GXCopyDisp(lbl_803C7420.xfb, GX_TRUE);
}

// .text:0x800A7E00 size:0x110
void fn_800A7E00(void) {
    GXBool filterOn;
    GXRenderModeObj* rmode = &lbl_803C7420.renderModeCopy;

    GXAdjustForOverscan(&GXNtsc480Int, rmode, 0, 16);
    lbl_803C7420.renderMode = &lbl_803C7420.renderModeCopy;
    VIConfigure(&lbl_803C7420.renderModeCopy);
    VIFlush();
    VIWaitForRetrace();
    VIWaitForRetrace();
    GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    GXSetDispCopySrc(0, 0, lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->efbHeight);
    GXSetDispCopyDst(lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->xfbHeight);
    GXSetDispCopyYScale((f32)lbl_803C7420.renderMode->xfbHeight / (f32)lbl_803C7420.renderMode->efbHeight);
    GXSetScissor(0, 0, lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->efbHeight);
    filterOn = GX_TRUE;
    GXSetCopyFilter(lbl_803C7420.renderMode->aa, lbl_803C7420.renderMode->sample_pattern, filterOn,
                    lbl_803C7420.renderMode->vfilter);
}

// .text:0x800A7F10 size:0x1D8
void fn_800A7F10(BOOL reset) {
    if (reset) {
        GXAdjustForOverscan(&GXNtsc480Int, &lbl_803C7420.renderModeCopy, 0, 16);
        lbl_803C7420.renderMode = &lbl_803C7420.renderModeCopy;
        VIConfigure(&lbl_803C7420.renderModeCopy);
        VIFlush();
        VIWaitForRetrace();
        VIWaitForRetrace();
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
        GXSetDispCopySrc(0, 0, lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->efbHeight);
        GXSetDispCopyDst(lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->xfbHeight);
        GXSetDispCopyYScale((f32)lbl_803C7420.renderMode->xfbHeight / (f32)lbl_803C7420.renderMode->efbHeight);
        GXSetScissor(0, 0, lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->efbHeight);
        GXSetCopyFilter(lbl_803C7420.renderMode->aa, lbl_803C7420.renderMode->sample_pattern, GX_TRUE,
                        lbl_803C7420.renderMode->vfilter);
    } else {
        VIConfigure(lbl_803C7420.renderMode);
        VIFlush();
        VIWaitForRetrace();
        VIWaitForRetrace();
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
        GXSetDispCopySrc(0, 0, lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->efbHeight);
        GXSetDispCopyDst(lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->xfbHeight);
        GXSetDispCopyYScale((f32)lbl_803C7420.renderMode->xfbHeight / (f32)lbl_803C7420.renderMode->efbHeight);
        GXSetScissor(0, 0, lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->efbHeight);
        GXSetCopyFilter(lbl_803C7420.renderMode->aa, lbl_803C7420.renderMode->sample_pattern, GX_TRUE,
                        lbl_803C7420.renderMode->vfilter);
    }
}

extern u8 lbl_802ED140[0x2000];       // draw thread stack
extern GXColor lbl_803CBAD0;          // EFB clear color
extern char lbl_800E77C8[];
extern char lbl_800E77D4[];

// .text:0x800A80E8 size:0x3DC
void initRenderMode(GXRenderModeObj* rmode, u32 fifoSize, u32 overscan) {
    OSThread* thread = &lbl_803C7420.drawThread;
    u8* arenaLo;
    int xfbSize;
    u8* arenaHi;
    u8* fifoBase;
    u8* heapLo;
    GXColor clearColor;

    lbl_803C7420.retraceInterval = 0;
    lbl_803C7420.retraceCounter = 0;
    OSCreateThread(thread, fn_800A7C08, NULL, lbl_802ED140 + sizeof(lbl_802ED140), sizeof(lbl_802ED140), 12, 1);
    OSInitThreadQueue(&lbl_803C7420.drawQueue);
    OSInitSemaphore(&lbl_803C7420.drawDone, 0);
    OSResumeThread(thread);
    OSInitThreadQueue(&lbl_803C7420.retraceQueue);
    VIInit();
    if (rmode != NULL) {
        lbl_803C7420.renderMode = rmode;
    } else {
        switch (VIGetTvFormat()) {
        case VI_NTSC:
            lbl_803C7420.renderMode = &GXNtsc480IntDf;
            break;
        case VI_PAL:
            lbl_803C7420.renderMode = &GXPal528IntDf;
            break;
        case VI_MPAL:
            lbl_803C7420.renderMode = &GXMpal480IntDf;
            break;
        default:
            OSPanic(lbl_800E77C8, 0x60, lbl_800E77D4);
            break;
        }
        GXAdjustForOverscan(lbl_803C7420.renderMode, &lbl_803C7420.renderModeCopy, 0, overscan);
        lbl_803C7420.renderMode = &lbl_803C7420.renderModeCopy;
    }

    arenaLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();
    xfbSize = (u16)((lbl_803C7420.renderMode->fbWidth + 15) & ~15) * lbl_803C7420.renderMode->xfbHeight;
    lbl_803C7420.xfb = (void*)OSRoundUp32B(arenaLo);
    fifoBase = (u8*)OSRoundUp32B((u8*)lbl_803C7420.xfb + xfbSize * 2);
    lbl_803C7420.fifoBase = fifoBase;
    lbl_803C7420.fifo = GXInit(fifoBase, fifoSize);
#ifdef TARGET_PC
    {
        // GXInit on the GameCube leaves every texcoord generator at
        // (MTX2x4, TEXn, IDENTITY); aurora leaves them unset, and some
        // draws rely on the defaults.
        s32 i;
        for (i = 0; i < 8; i++) {
            GXSetTexCoordGen2((GXTexCoordID)i, GX_TG_MTX2x4, (GXTexGenSrc)(GX_TG_TEX0 + i), GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        }
    }
#endif
    heapLo = fifoBase + fifoSize;
    fn_800AD054(heapLo, arenaHi);
    lbl_803C7420.heapLo = heapLo;
    lbl_803C7420.heapHi = arenaHi;
    lbl_803C7420.heapSize = (u32)OSRoundUp32B(arenaHi - heapLo);
    OSSetArenaLo(arenaHi);

    VIConfigure(lbl_803C7420.renderMode);
    VISetPreRetraceCallback(fn_800A84C4);
    if (lbl_803C7420.renderMode->aa) {
        GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
    } else {
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    }
    GXSetDispCopySrc(0, 0, lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->efbHeight);
    GXSetDispCopyDst(lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->xfbHeight);
    GXSetDispCopyYScale((f32)lbl_803C7420.renderMode->xfbHeight / (f32)lbl_803C7420.renderMode->efbHeight);
    GXSetCopyFilter(lbl_803C7420.renderMode->aa, lbl_803C7420.renderMode->sample_pattern, GX_TRUE,
                    lbl_803C7420.renderMode->vfilter);
    GXSetDispCopyGamma(GX_GM_1_0);
    GXCopyDisp(lbl_803C7420.xfb, GX_TRUE);
    VISetNextFrameBuffer(lbl_803C7420.xfb);
    VIFlush();
    VIWaitForRetrace();
    if (lbl_803C7420.renderMode->viTVmode & 1) {
        VIWaitForRetrace();
    }
    GXSetScissorBoxOffset(0, 0);
    GXSetScissor(0, 0, lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->efbHeight);
    GXSetViewport(0.0f, 0.0f, lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->xfbHeight, 0.0f, 1.0f);
    clearColor = lbl_803CBAD0;
    GXSetCopyClear(clearColor, 0xFFFFFF);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    VISetBlack(FALSE);
}

// .text:0x800A84C4 size:0x54
void fn_800A84C4(u32 retraceCount) {
    if (!lbl_803C7420.drawing) {
        if (--lbl_803C7420.retraceCounter < 0) {
            lbl_803C7420.retraceCounter = lbl_803C7420.retraceInterval;
            OSWakeupThread(&lbl_803C7420.retraceQueue);
        }
    }
}

extern void (*lbl_803CC128)(void); // called once the stream has been shut down
extern volatile u32 lbl_803CC12C;           // stream error reported; skip the next play-address poll
extern volatile u32 lbl_803CC130;
extern volatile u8 lbl_803CC134;            // right volume
extern volatile u8 lbl_803CC135;            // left volume
extern volatile u32 lbl_803CC138;           // AI stream trigger interval
extern volatile u32 lbl_803CC13C;           // last stream play address
extern volatile u32 lbl_803CC140;           // playlist mode (STREAM_MODE_*)
extern volatile u32 lbl_803CC144;           // state saved while skipping tracks
extern volatile u32 lbl_803CC148;           // STREAM_STATE_*
extern StreamTrack* lbl_803CC14C;  // playlist tail
extern StreamTrack* lbl_803CC150;  // playlist head
extern StreamTrack* lbl_803CC154;  // current track

extern DVDCommandBlock lbl_802EF140;
extern DVDCommandBlock lbl_802EF170;
extern DVDCommandBlock lbl_802EF1A0;
extern DVDCommandBlock lbl_802EF1D0;
extern DVDCommandBlock lbl_802EF200;
extern DVDCommandBlock lbl_802EF230;
extern DVDCommandBlock lbl_802EF260;
extern DVDCommandBlock lbl_802EF290;


extern s32 ConvertPathToEntryNum(void* file);
extern BOOL fn_800A750C(void* file, DVDFileInfo* fileInfo);
extern BOOL DVDPrepareStreamAsync(DVDFileInfo* fileInfo, u32 length, u32 offset, DVDCallback callback);
extern BOOL DVDStopStreamAtEndAsync(DVDCommandBlock* block, DVDCBCallback callback);
extern BOOL DVDGetStreamErrorStatusAsync(DVDCommandBlock* block, DVDCBCallback callback);
extern BOOL DVDGetStreamPlayAddrAsync(DVDCommandBlock* block, DVDCBCallback callback);

// Shared by fn_800A8518 and fn_800A86B4 (inlined into both).
static inline s32 StreamCommand(s32 cmd) {
    StreamTrack* track;
    BOOL enabled;

    if (lbl_803CC154 != NULL) {
        if (lbl_803CC148 == STREAM_STATE_BUSY) {
            return 0;
        }
        switch (cmd) {
        case 1:
            fn_800A88D8(STREAM_STATE_PLAY);
            break;
        case 2:
            fn_800A88D8(STREAM_STATE_PAUSE);
            break;
        case 3:
            fn_800A88D8(STREAM_STATE_STOP);
            break;
        case 4:
            if (lbl_803CC148 != STREAM_STATE_BUSY && lbl_803CC154 != NULL) {
                lbl_803CC144 = lbl_803CC148;
                lbl_803CC148 = STREAM_STATE_BUSY;
                if (lbl_803CC144 == STREAM_STATE_PLAY) {
                    AISetStreamVolLeft(0);
                    AISetStreamVolRight(0);
                    DVDCancelStreamAsync(&lbl_802EF170, fn_800A9034);
                } else {
                    enabled = OSDisableInterrupts();
                    if (lbl_803CC154 != NULL && (track = lbl_803CC154->next) != NULL) {
                        lbl_803CC154 = track;
                    }
                    OSRestoreInterrupts(enabled);
                    lbl_803CC148 = lbl_803CC144;
                }
            }
            break;
        case 5:
            if (lbl_803CC148 != STREAM_STATE_BUSY && lbl_803CC154 != NULL) {
                lbl_803CC144 = lbl_803CC148;
                lbl_803CC148 = STREAM_STATE_BUSY;
                if (lbl_803CC144 == STREAM_STATE_PLAY) {
                    AISetStreamVolLeft(0);
                    AISetStreamVolRight(0);
                    DVDCancelStreamAsync(&lbl_802EF140, fn_800A8FDC);
                } else {
                    enabled = OSDisableInterrupts();
                    if (lbl_803CC154 != NULL && (track = lbl_803CC154->prev) != NULL) {
                        lbl_803CC154 = track;
                    }
                    OSRestoreInterrupts(enabled);
                    lbl_803CC148 = lbl_803CC144;
                }
            }
            break;
        }
    }
    return 1;
}

// .text:0x800A8518 size:0x19C
s32 fn_800A8518(s32 cmd) {
    return StreamCommand(cmd);
}

// .text:0x800A86B4 size:0x1B0
void fn_800A86B4(s32 cmd) {
    while (StreamCommand(cmd) == 0) {
    }
}

// fn_800A8864, size:0x14
u16 fn_800A8864(void) {
    u16 value = lbl_803CC135;
    value = (value << 8) | lbl_803CC134;
    return value;
}

// .text:0x800A8878 size:0x48
void fn_800A8878(u8 left, u8 right) {
    lbl_803CC135 = left;
    lbl_803CC134 = right;
    if (lbl_803CC148 == STREAM_STATE_PLAY) {
        AISetStreamVolLeft(left);
        AISetStreamVolRight(right);
    }
}

// fn_800A88C0, size:0x8
StreamTrack* fn_800A88C0(void) {
    return lbl_803CC154;
}

// fn_800A88C8, size:0x8
u32 fn_800A88C8(void) {
    return lbl_803CC148;
}

// fn_800A88D0, size:0x8
u32 fn_800A88D0(void) {
    return lbl_803CC140;
}

// .text:0x800A88D8 size:0x1D8
void fn_800A88D8(u32 state) {
    StreamTrack* track;

    if (lbl_803CC148 == state || lbl_803CC148 == STREAM_STATE_BUSY) {
        return;
    }
    switch (state) {
    case STREAM_STATE_STOP:
        if (lbl_803CC154 != NULL) {
            lbl_803CC148 = STREAM_STATE_BUSY;
            AISetStreamVolLeft(0);
            AISetStreamVolRight(0);
            DVDCancelStreamAsync(&lbl_802EF1A0, fn_800A908C);
        }
        break;
    case STREAM_STATE_PLAY:
        if (lbl_803CC148 == STREAM_STATE_PAUSE) {
            AISetStreamVolLeft(lbl_803CC135);
            AISetStreamVolRight(lbl_803CC134);
            AIResetStreamSampleCount();
            AISetStreamTrigger(lbl_803CC138);
            AISetStreamPlayState(1);
            track = lbl_803CC154;
            lbl_803CC148 = STREAM_STATE_PLAY;
            if (track != NULL) {
                STREAM_NOTIFY(track, STREAM_EVENT_PLAY);
            }
        } else if (lbl_803CC154 != NULL) {
            lbl_803CC148 = STREAM_STATE_BUSY;
            DVDPrepareStreamAsync(&lbl_803CC154->fileInfo, 0, 0, fn_800A9424);
        } else {
            lbl_803CC148 = STREAM_STATE_PLAY;
        }
        lbl_803CC12C = 0;
        break;
    case 4:
        if (lbl_803CC148 == STREAM_STATE_STOP) {
            if (lbl_803CC154 != NULL) {
                lbl_803CC148 = STREAM_STATE_BUSY;
                DVDPrepareStreamAsync(&lbl_803CC154->fileInfo, 0, 0, fn_800A93AC);
            }
            lbl_803CC12C = 0;
        }
        break;
    case STREAM_STATE_PAUSE:
        AISetStreamPlayState(0);
        if (lbl_803CC148 == STREAM_STATE_PLAY) {
            lbl_803CC148 = STREAM_STATE_PAUSE;
        }
        track = lbl_803CC154;
        STREAM_NOTIFY(track, STREAM_EVENT_PAUSE);
        break;
    }
}

// fn_800A8AB0, size:0x8
void fn_800A8AB0(u32 value) {
    lbl_803CC140 = value;
}

// .text:0x800A8AB8 size:0xC0
void fn_800A8AB8(void (*onShutdown)(void)) {
    StreamTrack* track;
    u32 prev;

    if (lbl_803CC148 == STREAM_STATE_BUSY) {
        return;
    }
    prev = lbl_803CC148;
    lbl_803CC128 = onShutdown;
    lbl_803CC148 = STREAM_STATE_BUSY;
    if (prev == STREAM_STATE_PLAY) {
        DVDCancelStreamAsync(&lbl_802EF1D0, fn_800A90E4);
        return;
    }
    AISetStreamPlayState(0);
    for (track = lbl_803CC150; track != NULL; track = track->next) {
        DVDClose(&track->fileInfo);
    }
    lbl_803CC150 = NULL;
    lbl_803CC14C = NULL;
    lbl_803CC154 = NULL;
    lbl_803CC148 = STREAM_STATE_STOP;
    if (lbl_803CC128 != NULL) {
        lbl_803CC128();
        lbl_803CC128 = NULL;
    }
    lbl_803CC148 = STREAM_STATE_STOP;
    lbl_803CC130 = 0;
}

// .text:0x800A8B78 size:0x144
s32 fn_800A8B78(StreamTrack* track) {
    BOOL enabled;

    if (track == lbl_803CC154) {
        return 2;
    }
    enabled = OSDisableInterrupts();
    DVDClose(&track->fileInfo);
    if (track == lbl_803CC150 && track == lbl_803CC14C) {
        lbl_803CC150 = NULL;
        lbl_803CC14C = NULL;
        OSRestoreInterrupts(enabled);
        return 0;
    }
    if (track == lbl_803CC150) {
        lbl_803CC150 = track->next;
        lbl_803CC150->prev = NULL;
        if (lbl_803CC140 == STREAM_MODE_LOOP) {
            lbl_803CC14C->next = lbl_803CC150;
        }
        OSRestoreInterrupts(enabled);
        return 0;
    }
    if (track == lbl_803CC14C) {
        lbl_803CC14C = track->prev;
        lbl_803CC14C->next = NULL;
        if (lbl_803CC140 == STREAM_MODE_LOOP) {
            lbl_803CC14C->next = lbl_803CC150;
        }
        OSRestoreInterrupts(enabled);
        return 0;
    }
    if (track->prev != NULL && track->next != NULL) {
        track->prev->next = track->next;
        track->next->prev = track->prev;
    }
    OSRestoreInterrupts(enabled);
    return 0;
}

// .text:0x800A8CBC size:0x174
s32 LoadFile(void* file, StreamTrack* track, u32 flags, void (*callback)(u32 event), u32 options) {
    StreamTrack* it;
    s32 savedEntry;
    BOOL startPlaying;
    BOOL enabled;

    if ((options & 1) && lbl_803CC150 != NULL) {
        for (it = lbl_803CC150; it != NULL; it = it->next) {
            if (it == track) {
                return 0x100;
            }
        }
    }
    startPlaying = FALSE;
    savedEntry = lbl_803C6CF8.entryNum;
    lbl_803C6CF8.entryNum = ConvertPathToEntryNum(file);
    if (fn_800A750C(file, &track->fileInfo) == FALSE) {
        return 1;
    }
    lbl_803C6CF8.entryNum = savedEntry;
    enabled = OSDisableInterrupts();
    track->file = file;
    track->flags = flags;
    track->callback = callback;
    if (lbl_803CC150 == NULL) {
        lbl_803CC150 = track;
        lbl_803CC14C = track;
        track->prev = NULL;
        track->next = NULL;
        if (lbl_803CC148 == STREAM_STATE_PLAY) {
            startPlaying = TRUE;
        }
    } else {
        lbl_803CC14C->next = track;
        track->prev = lbl_803CC14C;
        lbl_803CC154 = track;
        track->next = NULL;
    }
    if (lbl_803CC154 == NULL) {
        lbl_803CC154 = track;
    }
    OSRestoreInterrupts(enabled);
    STREAM_NOTIFY(track, STREAM_EVENT_LOADED);
    if (startPlaying) {
        lbl_803CC148 = STREAM_STATE_BUSY;
        DVDPrepareStreamAsync(&lbl_803CC154->fileInfo, 0, 0, fn_800A9424);
    }
    return 0;
}

// .text:0x800A8E30 size:0x138
s32 fn_800A8E30(void* file, StreamTrack* track, u32 flags, void (*callback)(u32 event)) {
    BOOL startPlaying;
    s32 savedEntry;
    BOOL enabled;

    startPlaying = FALSE;
    savedEntry = lbl_803C6CF8.entryNum;
    lbl_803C6CF8.entryNum = ConvertPathToEntryNum(file);
    if (fn_800A750C(file, &track->fileInfo) == FALSE) {
        return 1;
    }
    lbl_803C6CF8.entryNum = savedEntry;
    enabled = OSDisableInterrupts();
    track->file = file;
    track->flags = flags;
    track->callback = callback;
    if (lbl_803CC150 == NULL) {
        lbl_803CC150 = track;
        lbl_803CC14C = track;
        track->prev = NULL;
        track->next = NULL;
        if (lbl_803CC148 == STREAM_STATE_PLAY) {
            startPlaying = TRUE;
        }
    } else {
        lbl_803CC14C->next = track;
        track->prev = lbl_803CC14C;
        lbl_803CC154 = track;
        track->next = NULL;
    }
    if (lbl_803CC154 == NULL) {
        lbl_803CC154 = track;
    }
    OSRestoreInterrupts(enabled);
    STREAM_NOTIFY(track, STREAM_EVENT_LOADED);
    if (startPlaying) {
        lbl_803CC148 = STREAM_STATE_BUSY;
        DVDPrepareStreamAsync(&lbl_803CC154->fileInfo, 0, 0, fn_800A9424);
    }
    return 0;
}

// .text:0x800A8F68 size:0x74
void fn_800A8F68(void) {
    lbl_803CC148 = STREAM_STATE_STOP;
    lbl_803CC140 = STREAM_MODE_ONCE;
    lbl_803CC13C = 0;
    lbl_803CC138 = 12000;
    lbl_803CC135 = 255;
    lbl_803CC154 = NULL;
    lbl_803CC150 = NULL;
    lbl_803CC14C = NULL;
    lbl_803CC134 = 255;
    AISetStreamVolLeft(0);
    AISetStreamVolRight(0);
    AIRegisterStreamCallback(fn_800A9168);
    AIResetStreamSampleCount();
    AISetStreamPlayState(0);
}

// .text:0x800A8FDC size:0x58
void fn_800A8FDC(s32 result, DVDCommandBlock* block) {
    StreamTrack* track;
    BOOL enabled;

    AISetStreamPlayState(0);
    enabled = OSDisableInterrupts();
    if (lbl_803CC154 != NULL && (track = lbl_803CC154->prev) != NULL) {
        lbl_803CC154 = track;
    }
    OSRestoreInterrupts(enabled);
    lbl_803CC148 = STREAM_STATE_STOP;
    fn_800A88D8(lbl_803CC144);
}

// .text:0x800A9034 size:0x58
void fn_800A9034(s32 result, DVDCommandBlock* block) {
    StreamTrack* track;
    BOOL enabled;

    AISetStreamPlayState(0);
    enabled = OSDisableInterrupts();
    if (lbl_803CC154 != NULL && (track = lbl_803CC154->next) != NULL) {
        lbl_803CC154 = track;
    }
    OSRestoreInterrupts(enabled);
    lbl_803CC148 = STREAM_STATE_STOP;
    fn_800A88D8(lbl_803CC144);
}

// .text:0x800A908C size:0x58
void fn_800A908C(s32 result, DVDCommandBlock* block) {
    StreamTrack* track;

    AISetStreamPlayState(0);
    track = lbl_803CC154;
    STREAM_NOTIFY(track, STREAM_EVENT_STOP);
    lbl_803CC148 = STREAM_STATE_STOP;
}

// .text:0x800A90E4 size:0x84
void fn_800A90E4(s32 result, DVDCommandBlock* block) {
    StreamTrack* track;

    AISetStreamPlayState(0);
    for (track = lbl_803CC150; track != NULL; track = track->next) {
        DVDClose(&track->fileInfo);
    }
    lbl_803CC150 = NULL;
    lbl_803CC14C = NULL;
    lbl_803CC154 = NULL;
    lbl_803CC148 = STREAM_STATE_STOP;
    if (lbl_803CC128 != NULL) {
        lbl_803CC128();
        lbl_803CC128 = NULL;
    }
    lbl_803CC148 = STREAM_STATE_STOP;
    lbl_803CC130 = 0;
}

// .text:0x800A9168 size:0x48
void fn_800A9168(u32 count) {
    AISetStreamTrigger(count + lbl_803CC138);
    if (lbl_803CC154 != NULL) {
        DVDGetStreamPlayAddrAsync(&lbl_802EF200, fn_800A91B0);
    }
}

// .text:0x800A91B0 size:0x1FC
// NONMATCHING 91%: the two STREAM_MODE_ONCE branches are laid out in the opposite order
#if NONMATCHING
void fn_800A91B0(s32 result, DVDCommandBlock* block) {
    StreamTrack* track;

    lbl_803CC13C = result;
    if (lbl_803CC12C != 0) {
        track = lbl_803CC154;
        lbl_803CC12C = 0;
        STREAM_NOTIFY(track, STREAM_EVENT_END);
        lbl_803CC148 = STREAM_STATE_BUSY;
        switch (lbl_803CC140) {
        case STREAM_MODE_LOOP:
            if (lbl_803CC154 != NULL) {
                if (lbl_803CC154->next != NULL) {
                    lbl_803CC154 = lbl_803CC154->next;
                    AISetStreamVolLeft(0);
                    AISetStreamVolRight(0);
                    AISetStreamPlayState(0);
                    DVDPrepareStreamAsync(&lbl_803CC154->fileInfo, 0, 0, fn_800A9424);
                } else {
                    lbl_803CC154 = lbl_803CC150;
                    AISetStreamVolLeft(0);
                    AISetStreamVolRight(0);
                    AISetStreamPlayState(0);
                    DVDPrepareStreamAsync(&lbl_803CC154->fileInfo, 0, 0, fn_800A9424);
                }
            }
            break;
        case STREAM_MODE_ONCE:
            if (lbl_803CC154 != NULL) {
                if (lbl_803CC154->next != NULL) {
                    lbl_803CC154 = lbl_803CC154->next;
                    AISetStreamVolLeft(0);
                    AISetStreamVolRight(0);
                    AISetStreamPlayState(0);
                    DVDPrepareStreamAsync(&lbl_803CC154->fileInfo, 0, 0, fn_800A9424);
                } else {
                    lbl_803CC154 = lbl_803CC150;
                    AISetStreamVolLeft(0);
                    AISetStreamVolRight(0);
                    AISetStreamPlayState(0);
                    lbl_803CC148 = STREAM_STATE_STOP;
                }
            }
            break;
        case STREAM_MODE_REPEAT:
            if (lbl_803CC154 != NULL) {
                AISetStreamVolLeft(0);
                AISetStreamVolRight(0);
                AISetStreamPlayState(0);
                DVDPrepareStreamAsync(&lbl_803CC154->fileInfo, 0, 0, fn_800A9424);
            }
            break;
        }
    } else {
        DVDGetStreamErrorStatusAsync(&lbl_802EF230, fn_800A94A8);
    }
}
#endif

// .text:0x800A93AC size:0x78
void fn_800A93AC(s32 result, DVDFileInfo* fileInfo) {
    StreamTrack* track;

    AISetStreamVolLeft(0);
    AISetStreamVolRight(0);
    AISetStreamPlayState(0);
    DVDStopStreamAtEndAsync(&lbl_802EF260, NULL);
    track = lbl_803CC154;
    lbl_803CC148 = STREAM_STATE_PAUSE;
    STREAM_NOTIFY(track, STREAM_EVENT_PREPARED);
}

// .text:0x800A9424 size:0x84
void fn_800A9424(s32 result, DVDFileInfo* fileInfo) {
    StreamTrack* track;

    AISetStreamVolLeft(lbl_803CC135);
    AISetStreamVolRight(lbl_803CC134);
    AIResetStreamSampleCount();
    AISetStreamTrigger(lbl_803CC138);
    AISetStreamPlayState(1);
    DVDStopStreamAtEndAsync(&lbl_802EF290, NULL);
    track = lbl_803CC154;
    lbl_803CC148 = STREAM_STATE_PLAY;
    STREAM_NOTIFY(track, STREAM_EVENT_PLAY);
}

// fn_800A94A8, size:0x1C
void fn_800A94A8(s32 result, DVDCommandBlock* block) {
    if ((u8)result == 0) {
        lbl_803CC12C = 1;
        lbl_803CC13C = 0;
    }
}

extern void SISetSamplingRate(u32 msec);
extern PadConfig lbl_80110080;

// .text:0x800A94C4 size:0x5C
void fn_800A94C4(void) {
    u32 mask = 0;
    PadState* pad = lbl_803C77B8;
    s32 i = 0;

    do {
        if (pad->err == PAD_ERR_NONE) {
            mask |= PAD_CHAN0_BIT >> i;
        }
        i++;
        pad++;
    } while (i < PAD_MAX_CONTROLLERS);
    PADRecalibrate(mask);
}

// .text:0x800A9520 size:0x2B0
// NONMATCHING 73%: the stick-direction bits are merged with rlwimi instead of the original's rlwinm/or chain, so more saved registers and a larger frame
#if NONMATCHING
void fn_800A9520(void) {
    PADStatus status[PAD_MAX_CONTROLLERS];
    PADStatus* st;
    PadState* pad;
    u32 i;
    PadConfig* cfg;
    u32 dirs;
    u16 prev;

    lbl_80110080.readMask = PADRead(status);
#ifdef TARGET_PC
    {
        // Scripted presses (MSSB_INPUT="frame:BUTTON,..."), see port/src/input.cpp.
        extern void port_pad_apply_script(PADStatus* status);
        port_pad_apply_script(status);
        if (status[0].err == PAD_ERR_NONE) {
            lbl_80110080.readMask |= PAD_CHAN0_BIT;
        }
    }
#endif
    PADClamp(status);
    st = status;
    pad = lbl_803C77B8;
    cfg = &lbl_80110080;
    for (i = 0; i < PAD_MAX_CONTROLLERS; i++, st++, pad++) {
        pad->err = st->err;
        if (pad->err == PAD_ERR_NO_CONTROLLER) {
            PADReset(PAD_CHAN0_BIT >> i);
        }
        if (pad->rumbleCmd == 1) {
            pad->rumbleCmd = 0;
            if (pad->rumbleMode == 0) {
                PADControlMotor(i, PAD_MOTOR_STOP_HARD);
            } else {
                PADControlMotor(i, PAD_MOTOR_RUMBLE);
                pad->rumbleCmd = 2;
            }
        } else if (pad->rumbleCmd == 2) {
            if (--pad->rumbleTimer == 0) {
                pad->rumbleCmd = 0;
                PADControlMotor(i, pad->rumbleMode & ~1);
            }
        }
        pad->analog = *(PadAnalog*)&st->triggerLeft;
        pad->sticks = *(PadSticks*)&st->stickX;
        dirs = ((pad->sticks.stickY > cfg->stickPos) << 19) | ((pad->sticks.stickY < cfg->stickNeg) << 18) |
               ((pad->sticks.stickX < cfg->stickNeg) << 16) | ((pad->sticks.stickX > cfg->stickPos) << 17) |
               ((pad->sticks.substickY < cfg->stickNeg) << 2) | ((pad->sticks.substickY > cfg->stickPos) << 3) |
               (pad->sticks.substickX < cfg->stickNeg) | ((pad->sticks.substickX > cfg->stickPos) << 1);
        pad->stickDirs = dirs;
        prev = pad->prev;
        pad->held = st->button | (dirs >> cfg->stickShift);
        pad->prev = pad->held;
        pad->down = pad->held & ~prev;
        pad->repeat = pad->down;
        if (pad->prev == prev) {
            if (pad->repeatDelay < 0) {
                if (--pad->repeatTimer <= 0) {
                    pad->repeat = pad->prev;
                    pad->repeatTimer = cfg->repeatRate;
                }
            } else if (--pad->repeatDelay < 0) {
                pad->repeat = pad->prev;
                pad->repeatTimer = cfg->repeatRate;
            }
        } else {
            pad->repeatDelay = cfg->repeatDelay;
        }
    }
}
#endif

// fn_800A97EC, size:0x50
void fn_800A97EC(s32 index, u32 duration, u8 mode) {
    PadState* pad = &lbl_803C77B8[index];
    if (!(lbl_80110080.rumbleLockMask & (1 << index))) {
        pad->rumbleTimer = duration;
        pad->rumbleMode = 0;
        if (duration != 0) {
            pad->rumbleMode = mode;
        }
        pad->rumbleCmd = 1;
    }
}

// fn_800A97D0, size:0x1C
void fn_800A97D0(u8 shift, s32 threshold) {
    lbl_80110080.stickShift = shift;
    lbl_80110080.stickNeg = -threshold;
    lbl_80110080.stickPos = threshold;
}

// .text:0x800A983C size:0x28
void fn_800A983C(void) {
    PADInit();
    SISetSamplingRate(0);
}

extern CardSystem lbl_803C7838;
extern Task* lbl_803CC1B8;            // currently running task
extern u64 lbl_802EF2C0[2];           // expected serial number per slot
extern CARDMemoryCard lbl_802EF3A0;   // CARD work area
extern CARDStat lbl_802EF330;
extern u16 lbl_800E7800[256];         // CRC-16 table
extern char lbl_803CCEE0[8];          // OSPanic file name
extern char lbl_800E7B28[];           // OSPanic message
extern const char lbl_800E7A00[];     // "MemoryCard FileName Error!!"
extern const char lbl_800E7A1C[];     // "MemoryCard LoadSize Error!!"
extern const char lbl_800E7A38[];     // "MemoryCard SaveSize Error!!" and further messages
extern char lbl_802EF2D0[CARD_FILENAME_MAX]; // file name of the current card task
extern CardSaveHeader lbl_802EF2F0;   // header copied to the start of every save
extern u32 lbl_803CC158;              // verify callback argument
extern u8 (*lbl_803CC15C)(void* buffer, s32 length, u32 arg);
extern u32 lbl_803CC160;              // CardRequest.flags
extern u8* lbl_803CC164;              // end of the save data in the save buffer
extern s32 lbl_803CC168;              // CARDGetXferredBytes at the start of a transfer
extern u8* lbl_803CC16C;              // save buffer
extern s32 CARDSetAttributes(s32 chan, s32 fileNo, u8 attr);
extern s32 CARDSetAttributesAsync(s32 chan, s32 fileNo, u8 attr, CARDCallback callback);

extern s32 CARDGetResultCode(s32 chan);
extern s32 CARDGetXferredBytes(s32 chan);
extern s32 CARDCheckAsync(s32 chan, CARDCallback callback);
extern s32 CARDFormatAsync(s32 chan, CARDCallback callback);
extern s32 CARDDeleteAsync(s32 chan, const char* fileName, CARDCallback callback);
#ifdef TARGET_PC
// symbols.txt names 0x80088698 CARDFastDelete, but it takes a file name: it
// is the SDK's CARDDelete. aurora's CARDInit takes the game and maker codes.
#define CARDFastDelete CARDDelete
#define CARDInit() CARDInit("GYQE", "01")
#else
extern s32 CARDFastDelete(s32 chan, char* fileName);
extern void CARDInit(void);
#endif

// Classifies lbl_803C7838.status: 0 = still busy, 1 = ready, 2 = error.
static inline s32 CardStatusClass(void) {
    u8 status = lbl_803C7838.status;
    if (status == CARD_STATUS_BUSY) {
        return 0;
    }
    if (status == CARD_STATUS_READY) {
        return 1;
    }
    return 2;
}

// Steps 0-3 shared by the memory card tasks: probe the slot, mount it and check it.
static inline void CardMountSteps(s32* step, u8 chan, u8 mode, s32 errorStep) {
    s32 res;
    s32 cls;
    BOOL busy;

    switch (*step) {
    case 0:
        fn_800ACD64(CARDUnmount(chan));
        fn_800ACD64(lbl_803C7838.slots[chan].probeResult);
        cls = CardStatusClass();
        if (cls == 1) {
            fn_800ACD64(lbl_803C7838.slots[chan].sectorSize == 0x2000 ? CARD_RESULT_READY
                                                                     : CARD_RESULT_BAD_SECTOR_SIZE);
            cls = CardStatusClass();
        }
        switch (cls) {
        case 1:
            *step = 1;
            break;
        case 2:
            *step = errorStep;
            break;
        }
        break;
    case 1:
        if (mode == 1) {
            res = CARDMountAsync(chan, &lbl_802EF3A0, NULL, NULL);
            if (res == CARD_RESULT_BUSY) {
                busy = TRUE;
            } else {
                fn_800ACD64(res);
                busy = FALSE;
            }
        } else {
            fn_800ACD64(CARDMount(chan, &lbl_802EF3A0, NULL));
            busy = FALSE;
        }
        if (!busy) {
            *step = 2;
        }
        break;
    case 2:
        fn_800ACD64(CARDGetResultCode(chan));
        switch (lbl_803C7838.status) {
        case CARD_STATUS_BUSY:
            break;
        case 1:
        case 2:
        case CARD_STATUS_READY:
            *step = 3;
            break;
        default:
            *step = errorStep;
            break;
        }
        break;
    case 3:
        if (mode == 1) {
            res = CARDCheckAsync(chan, NULL);
            if (res == CARD_RESULT_BUSY) {
                busy = TRUE;
            } else {
                fn_800ACD64(res);
                busy = FALSE;
            }
        } else {
            fn_800ACD64(CARDCheck(chan));
            busy = FALSE;
        }
        if (!busy) {
            *step = 4;
        }
        break;
    }
}

// Step 4: wait for CARDCheck; ready goes to step 5, failure to errorStep.
static inline void CardCheckResultStep(s32* step, u8 chan, s32 errorStep) {
    fn_800ACD64(CARDGetResultCode(chan));
    switch (lbl_803C7838.status) {
    case CARD_STATUS_BUSY:
        break;
    case CARD_STATUS_READY:
        *step = 5;
        break;
    default:
        *step = errorStep;
        break;
    }
}

// Step 5: the card in the slot must carry the expected (nonzero) serial number.
static inline void CardSerialStep(s32* step, u8 chan, s32 errorStep) {
    u64 serial;
    s32 res;

    if (lbl_803C7838.status == CARD_STATUS_READY) {
        serial = 0;
        res = CARDGetSerialNo(chan, &serial);
        lbl_803C7838.slots[chan].serial = serial;
        if (res != CARD_RESULT_BUSY) {
            if (lbl_803C7838.slots[chan].serial != 0 && lbl_803C7838.slots[chan].serial == lbl_802EF2C0[chan]) {
                *step = 6;
            } else {
                lbl_803C7838.status = CARD_STATUS_SERIAL_MISMATCH;
                *step = errorStep;
            }
        }
    } else {
        *step = errorStep;
    }
}

// Opens and closes `fileName` to see whether it exists. Returns 0 if it does (status 8),
// 1 if it does not, 2 on error.
static inline s32 CardFileExists(u8 chan, char* fileName) {
    char name[CARD_FILENAME_MAX + 1];
    CARDFileInfo fileInfo;
    s32 res;

    strncpy(name, fileName, CARD_FILENAME_MAX);
    name[CARD_FILENAME_MAX] = '\0';
    if (strlen(name) >= CARD_FILENAME_MAX) {
        OSPanic(lbl_803CCEE0, 0x1FE, lbl_800E7A00);
    }
    res = CARDOpen(chan, fileName, &fileInfo);
#ifdef TARGET_PC
    if (getenv("MSSB_DEBUG_CARD") != NULL) {
        fprintf(stderr, "[card] open '%s' -> %d\n", fileName, res);
    }
#endif
    switch (res) {
    case CARD_RESULT_READY:
        lbl_803C7838.status = 8;
        CARDClose(&fileInfo);
        return 0;
    case CARD_RESULT_NOFILE:
        return 1;
    default:
        fn_800ACD64(res);
        return 2;
    }
}

// Final step of a task: report to the parent task and remove this one.
static inline void CardTaskFinish(s16 result) {
    Task* parent = lbl_803CC1B8->parent;
    parent->result = result;
    fn_800B0A14_removeQueue(parent);
}

// Turns the file offsets inside a TPL loaded into memory into pointers.
#ifdef TARGET_PC
// The TPL keeps its disc layout (PTR32 fields); its headers are byte-swapped
// first (port/src/formats_tex.c). Texel and CLUT data stay big-endian.
static inline void UnpackTexPalette(TEXPalette* pal) {
    u16 i;
    TEXDescriptor* desc;
    TEXHeader* tex;
    CLUTHeader* clut;

    port_swap_tex_palette(pal);
    if (pal->versionNumber != 2142000) {
        OSPanic(lbl_803CCEE0, 0x52F, lbl_800E7A38 + 0x2C);
    }
    PTR32_SET(pal->descriptorArray, (u8*)pal + pal->descriptorArray);
    desc = PTR32_GET(TEXDescriptor, pal->descriptorArray);
    for (i = 0; i < pal->numDescriptors; i++) {
        if (desc[i].textureHeader != 0) {
            PTR32_SET(desc[i].textureHeader, (u8*)pal + desc[i].textureHeader);
            tex = PTR32_GET(TEXHeader, desc[i].textureHeader);
            if (tex->unpacked != TRUE) {
                PTR32_SET(tex->data, (u8*)pal + tex->data);
                tex->unpacked = TRUE;
            }
        }
        if (desc[i].CLUTHeader != 0) {
            PTR32_SET(desc[i].CLUTHeader, (u8*)pal + desc[i].CLUTHeader);
            clut = PTR32_GET(CLUTHeader, desc[i].CLUTHeader);
            if (clut->unpacked != TRUE) {
                PTR32_SET(clut->data, (u8*)pal + clut->data);
                clut->unpacked = TRUE;
            }
        }
    }
}
#else
static inline void UnpackTexPalette(TEXPalette* pal) {
    u16 i;

    if (pal->versionNumber != 2142000) {
        OSPanic(lbl_803CCEE0, 0x52F, lbl_800E7A38 + 0x2C);
    }
    pal->descriptorArray = (TEXDescriptor*)((uintptr_t)pal->descriptorArray + (uintptr_t)pal);
    for (i = 0; i < pal->numDescriptors; i++) {
        if (pal->descriptorArray[i].textureHeader != NULL) {
            pal->descriptorArray[i].textureHeader =
                (TEXHeader*)((uintptr_t)pal + (uintptr_t)pal->descriptorArray[i].textureHeader);
            if (!pal->descriptorArray[i].textureHeader->unpacked) {
                pal->descriptorArray[i].textureHeader->data =
                    (Ptr)((uintptr_t)pal + (uintptr_t)pal->descriptorArray[i].textureHeader->data);
                pal->descriptorArray[i].textureHeader->unpacked = TRUE;
            }
        }
        if (pal->descriptorArray[i].CLUTHeader != NULL) {
            pal->descriptorArray[i].CLUTHeader =
                (CLUTHeader*)((uintptr_t)pal + (uintptr_t)pal->descriptorArray[i].CLUTHeader);
            if (!pal->descriptorArray[i].CLUTHeader->unpacked) {
                pal->descriptorArray[i].CLUTHeader->data =
                    (Ptr)((uintptr_t)pal + (uintptr_t)pal->descriptorArray[i].CLUTHeader->data);
                pal->descriptorArray[i].CLUTHeader->unpacked = TRUE;
            }
        }
    }
}

#endif

// Loads the default banner file ("/opening.bnr") into `buf`.
static inline BOOL LoadDefaultBanner(void* buf) {
    DVDFileInfo fileInfo;

    if (!DVDOpen((char*)lbl_800E7A38 + 0x1C, &fileInfo)) {
        return FALSE;
    }
    if (OSRoundUp32B(fileInfo.length) < 0x1960) {
        return FALSE;
    }
    if (DVDReadPrio(&fileInfo, buf, 0x1960, 0, 2) == 0) {
        return FALSE;
    }
    if (*(u32*)buf != 'BNR1') {
        return FALSE;
    }
    return TRUE;
}

// .text:0x800A9864 size:0x98
void fn_800A9864(u8 chan, u8 mode, u64 serial) {
    CardMountTask* task;

    lbl_803C7838.op = 6;
    task = fn_800B0A5C_insertQueue(fn_800A98FC, 0xFF);
    memset(&task->step, 0, sizeof(Task) - OFFSET_OF(Task, data));
    task->chan = chan;
    task->mode = mode;
    lbl_802EF2C0[chan] = serial;
    lbl_803CC1B8->result = 0;
}

// .text:0x800A98FC size:0x3FC
// NONMATCHING 89%: switch jump table lives in unsplit .data (reloc names differ); status classification compiled into a different branch layout
// nmverify: fn_800ACD64 inlined on one side (calls match once expanded)
#if NONMATCHING
void fn_800A98FC(void) {
    CardMountTask* task = (CardMountTask*)lbl_803CC1B8;
    u8 chan;
    s32 res;
    s32 cls;
    BOOL busy;
    u64 serial;

    switch (task->step) {
    case 0:
        chan = task->chan;
        fn_800ACD64(CARDUnmount(chan));
        fn_800ACD64(lbl_803C7838.slots[chan].probeResult);
        cls = CardStatusClass();
        if (cls == 1) {
            fn_800ACD64(lbl_803C7838.slots[chan].sectorSize == 0x2000 ? CARD_RESULT_READY
                                                                     : CARD_RESULT_BAD_SECTOR_SIZE);
            cls = CardStatusClass();
        }
        switch (cls) {
        case 1:
            task->step = 1;
            break;
        case 2:
            task->step = 9;
            break;
        }
        break;
    case 1:
        if (task->mode == 1) {
            res = CARDMountAsync(task->chan, &lbl_802EF3A0, NULL, NULL);
            if (res == CARD_RESULT_BUSY) {
                busy = TRUE;
            } else {
                fn_800ACD64(res);
                busy = FALSE;
            }
        } else {
            fn_800ACD64(CARDMount(task->chan, &lbl_802EF3A0, NULL));
            busy = FALSE;
        }
        if (!busy) {
            task->step = 2;
        }
        break;
    case 2:
        fn_800ACD64(CARDGetResultCode(task->chan));
        switch (lbl_803C7838.status) {
        case CARD_STATUS_BUSY:
            break;
        case 1:
        case 2:
        case CARD_STATUS_READY:
            task->step = 3;
            break;
        default:
            task->step = 9;
            break;
        }
        break;
    case 3:
        if (task->mode == 1) {
            res = CARDCheckAsync(task->chan, NULL);
            if (res == CARD_RESULT_BUSY) {
                busy = TRUE;
            } else {
                fn_800ACD64(res);
                busy = FALSE;
            }
        } else {
            fn_800ACD64(CARDCheck(task->chan));
            busy = FALSE;
        }
        if (!busy) {
            task->step = 4;
        }
        break;
    case 4:
        fn_800ACD64(CARDGetResultCode(task->chan));
        if (lbl_803C7838.status != CARD_STATUS_BUSY) {
            task->step = 5;
        }
        break;
    case 5:
        if (lbl_803C7838.status == CARD_STATUS_READY) {
            chan = task->chan;
            serial = 0;
            res = CARDGetSerialNo(chan, &serial);
            lbl_803C7838.slots[chan].serial = serial;
            if (res != CARD_RESULT_BUSY) {
                if (lbl_803C7838.slots[task->chan].serial == lbl_802EF2C0[task->chan]) {
                    task->step = 6;
                } else {
                    lbl_803C7838.status = CARD_STATUS_SERIAL_MISMATCH;
                    task->step = 9;
                }
            }
        } else {
            task->step = 6;
        }
        break;
    case 6:
        memset(((Task*)fn_800B0A5C_insertQueue(fn_800A9CF8, 0xFF))->data, 0, sizeof(((Task*)0)->data));
        lbl_803CC1B8->result = 0;
        task->step = 7;
        break;
    case 7:
        switch (task->result) {
        case 1:
            task->step = 8;
            break;
        case 2:
            task->step = 9;
            break;
        }
        break;
    case 8:
        fn_800ACD64(CARDUnmount(task->chan));
        switch (lbl_803C7838.status) {
        case CARD_STATUS_BUSY:
            break;
        case CARD_STATUS_READY:
            task->step = 10;
            break;
        default:
            task->step = 9;
            break;
        }
        break;
    case 9:
        task->step = 10;
        break;
    case 10:
        task->parent->result = 1;
        fn_800B0A14_removeQueue(task->parent);
        break;
    }
}
#endif

// .text:0x800A9CF8 size:0x13C
void fn_800A9CF8(void) {
    char* fileName = lbl_802EF330.fileName;
    CardMountTask* task = (CardMountTask*)lbl_803CC1B8;
    CardMountTask* parent = (CardMountTask*)task->parent;
    s32 res;

    switch (task->step) {
    case 0:
        if (parent->mode == 1) {
            res = CARDDeleteAsync(parent->chan, fileName, NULL);
            if (res < 0) {
                fn_800ACD64(res);
                task->step = 3;
            } else {
                task->step++;
            }
        } else {
            res = CARDFastDelete(parent->chan, fileName);
            if (res < 0) {
                fn_800ACD64(res);
                task->step = 3;
            } else {
                task->step += 2;
            }
        }
        break;
    case 1:
        fn_800ACD64(CARDGetResultCode(parent->chan));
        switch (lbl_803CC1B8->result) {
        case CARD_STATUS_BUSY:
            break;
        case CARD_STATUS_READY:
            task->step++;
            break;
        default:
            task->step = 3;
            break;
        }
        break;
    case 2:
        parent->result = 1;
        fn_800B0A14_removeQueue(parent);
        break;
    case 3:
        parent->result = 2;
        fn_800B0A14_removeQueue(parent);
        break;
    }
}

// .text:0x800A9E34 size:0x98
void fn_800A9E34(u8 chan, u8 mode, u64 serial) {
    CardMountTask* task;

    lbl_803C7838.op = 4;
    task = fn_800B0A5C_insertQueue(fn_800A9ECC, 0xFF);
    memset(&task->step, 0, sizeof(Task) - OFFSET_OF(Task, data));
    task->chan = chan;
    task->mode = mode;
    lbl_802EF2C0[chan] = serial;
    lbl_803CC1B8->result = 0;
}

// .text:0x800A9ECC size:0x480
// NONMATCHING 84%: switch jump table lives in unsplit .data (reloc names differ); steps 0-5 are written as shared inline helpers, which lay out differently
// jtcheck: steps 0-3 share one arm (the CardMountSteps helper switches on them itself)
// nmverify: fn_800ACD64 inlined on one side (calls match once expanded)
#if NONMATCHING
void fn_800A9ECC(void) {
    CardMountTask* task = (CardMountTask*)lbl_803CC1B8;
    u8 chan;
    s32 res;
    BOOL busy;
    u64 serial;
    u64 newSerial;

    switch (task->step) {
    case 0:
    case 1:
    case 2:
    case 3:
        CardMountSteps(&task->step, task->chan, task->mode, 9);
        break;
    case 4:
        fn_800ACD64(CARDGetResultCode(task->chan));
        if (lbl_803C7838.status != CARD_STATUS_BUSY) {
            task->step = 5;
        }
        break;
    case 5:
        if (lbl_803C7838.status == CARD_STATUS_READY) {
            chan = task->chan;
            serial = 0;
            res = CARDGetSerialNo(chan, &serial);
            lbl_803C7838.slots[chan].serial = serial;
            if (res != CARD_RESULT_BUSY) {
                if (lbl_803C7838.slots[task->chan].serial == lbl_802EF2C0[task->chan]) {
                    task->step = 6;
                } else {
                    lbl_803C7838.status = CARD_STATUS_SERIAL_MISMATCH;
                    task->step = 9;
                }
            }
        } else {
            task->step = 6;
        }
        break;
    case 6:
        if (task->mode == 1) {
            res = CARDFormatAsync(task->chan, NULL);
            if (res == CARD_RESULT_BUSY) {
                busy = TRUE;
            } else {
                fn_800ACD64(res);
                busy = FALSE;
            }
        } else {
            fn_800ACD64(CARDFormat(task->chan));
            busy = FALSE;
        }
        if (!busy) {
            task->step = 7;
        }
        break;
    case 7:
        fn_800ACD64(CARDGetResultCode(task->chan));
        switch (lbl_803C7838.status) {
        case CARD_STATUS_BUSY:
            break;
        case CARD_STATUS_READY:
            chan = task->chan;
            newSerial = 0;
            CARDGetSerialNo(chan, &newSerial);
            lbl_803C7838.slots[chan].serial = newSerial;
            task->step = 8;
            break;
        case 3:
            lbl_803C7838.status = 0xD;
            task->step = 9;
            break;
        default:
            lbl_803C7838.status = 0xC;
            task->step = 9;
            break;
        }
        break;
    case 8:
        fn_800ACD64(CARDUnmount(task->chan));
        switch (lbl_803C7838.status) {
        case CARD_STATUS_BUSY:
            break;
        case CARD_STATUS_READY:
            task->step = 10;
            break;
        default:
            task->step = 9;
            break;
        }
        break;
    case 9:
        task->step = 10;
        break;
    case 10:
        task->parent->result = 1;
        fn_800B0A14_removeQueue(task->parent);
        break;
    }
}
#endif

// .text:0x800AA34C size:0x100
void fn_800AA34C(u8 chan, u8 mode, char* fileName, u64 serial, u8 setSerial) {
    char name[CARD_FILENAME_MAX + 1];
    CardNameTask* task;

    lbl_803C7838.op = 5;
    strncpy(name, fileName, CARD_FILENAME_MAX);
    name[CARD_FILENAME_MAX] = '\0';
    if (strlen(name) >= CARD_FILENAME_MAX) {
        OSPanic(lbl_803CCEE0, 0xA6A, lbl_800E7A00);
    }
    task = fn_800B0A5C_insertQueue(fn_800AA44C, 0xFF);
    memset(&task->step, 0, sizeof(((Task*)0)->data));
    task->chan = chan;
    task->mode = mode;
    task->fileName = lbl_802EF2D0;
    memcpy(task->fileName, fileName, CARD_FILENAME_MAX);
    if (setSerial) {
        lbl_802EF2C0[chan] = serial;
    }
    lbl_803CC1B8->result = 0;
}

// .text:0x800AA44C size:0x4E4
// NONMATCHING 80%: switch jump table lives in unsplit .data (reloc names differ); steps 0-5 are written as shared inline helpers, which lay out differently
// jtcheck: all steps 0-8 present; with 0-3 sharing the CardMountSteps arm mwcc picks compares, not a table
// nmverify: fn_800ACD64 inlined on one side (calls match once expanded)
#if NONMATCHING
void fn_800AA44C(void) {
    CardNameTask* task = (CardNameTask*)lbl_803CC1B8;
    u64 serial;
    s32 res;

    switch (task->step) {
    case 0:
    case 1:
    case 2:
    case 3:
        CardMountSteps(&task->step, task->chan, task->mode, 8);
        break;
    case 4:
        CardCheckResultStep(&task->step, task->chan, 8);
        break;
    case 5:
        // A card is accepted if no serial is expected or the serials agree.
        if (lbl_803C7838.status == CARD_STATUS_READY) {
            serial = 0;
            res = CARDGetSerialNo(task->chan, &serial);
            lbl_803C7838.slots[task->chan].serial = serial;
            if (res != CARD_RESULT_BUSY) {
                if (lbl_803C7838.slots[task->chan].serial != 0) {
                    if (lbl_802EF2C0[task->chan] == 0) {
                        task->step = 6;
                    } else if (lbl_803C7838.slots[task->chan].serial == lbl_802EF2C0[task->chan]) {
                        task->step = 6;
                    } else {
                        lbl_803C7838.status = CARD_STATUS_SERIAL_MISMATCH;
                        task->step = 8;
                    }
                } else {
                    task->step = 8;
                }
            }
        } else {
            task->step = 8;
        }
        break;
    case 6:
        switch (CardFileExists(task->chan, task->fileName)) {
        case 0:
            task->arg = 1;
            task->step = 7;
            break;
        case 1:
            task->step = 7;
            break;
        case 2:
            task->step = 8;
            break;
        }
        break;
    case 7:
        fn_800ACD64(CARDUnmount(task->chan));
        switch (lbl_803C7838.status) {
        case CARD_STATUS_BUSY:
            break;
        case CARD_STATUS_READY:
            if ((u16)task->arg == 1) {
                lbl_803C7838.status = 8;
            }
            task->step = 8;
            break;
        default:
            task->step = 8;
            break;
        }
        break;
    case 8:
        task->parent->result = 1;
        fn_800B0A14_removeQueue(task->parent);
        break;
    }
}
#endif

// .text:0x800AA930 size:0x140
void fn_800AA930(CardRequest* req, u64 serial) {
    char name[CARD_FILENAME_MAX + 1];
    CardFileTask* task;

    if (req->length % CARD_READ_SIZE != 0) {
        OSPanic(lbl_803CCEE0, 0x970, lbl_800E7A1C);
    }
    strncpy(name, req->fileName, CARD_FILENAME_MAX);
    name[CARD_FILENAME_MAX] = '\0';
    if (strlen(name) >= CARD_FILENAME_MAX) {
        OSPanic(lbl_803CCEE0, 0x979, lbl_800E7A00);
    }
    task = fn_800B0A5C_insertQueue(fn_800AAA70, 0xFF);
    task->chan = req->chan;
    task->mode = req->mode;
    task->buffer = req->buffer;
    task->length = req->length;
    task->fileName = lbl_802EF2D0;
    memcpy(task->fileName, req->fileName, CARD_FILENAME_MAX);
    lbl_802EF2C0[req->chan] = serial;
    lbl_803CC15C = req->verify;
    lbl_803CC158 = req->verifyArg;
    lbl_803CC160 = req->flags;
    lbl_803CC1B8->result = 0;
}

// .text:0x800AAA70 size:0x474
// NONMATCHING 76%: switch jump table lives in unsplit .data (reloc names differ); steps 0-5 are written as shared inline helpers, which lay out differently
// jtcheck: steps 0-3 share one arm (the CardMountSteps helper switches on them itself)
// nmverify: fn_800ACD64 inlined on one side (calls match once expanded)
#if NONMATCHING
void fn_800AAA70(void) {
    CardFileTask* task = (CardFileTask*)lbl_803CC1B8;
    u8 status;

    switch (task->step) {
    case 0:
    case 1:
    case 2:
    case 3:
        CardMountSteps(&task->step, task->chan, task->mode, 9);
        break;
    case 4:
        CardCheckResultStep(&task->step, task->chan, 9);
        break;
    case 5:
        CardSerialStep(&task->step, task->chan, 9);
        break;
    case 6:
        memset(((Task*)fn_800B0A5C_insertQueue(fn_800ABBD0, 0xFF))->data, 0, sizeof(((Task*)0)->data));
        task->step = 7;
        lbl_803CC1B8->result = 0;
        break;
    case 7:
        switch (task->result) {
        case 1:
            if (lbl_803CC15C != NULL) {
                status = lbl_803CC15C(task->buffer, task->length, lbl_803CC158);
                if (status != CARD_STATUS_READY) {
                    lbl_803C7838.status = status;
                    task->step = 9;
                    break;
                }
            }
            task->step = 8;
            break;
        case 2:
            task->step = 9;
            break;
        }
        break;
    case 8:
        fn_800ACD64(CARDUnmount(task->chan));
        switch (lbl_803C7838.status) {
        case CARD_STATUS_BUSY:
            break;
        default:
            task->step = 9;
            break;
        }
        break;
    case 9:
        task->parent->result = 1;
        fn_800B0A14_removeQueue(task->parent);
        break;
    }
}
#endif

// .text:0x800AAEE4 size:0x108
void fn_800AAEE4(CardRequest* req, u64 serial) {
    CardWriteTask* task;
    u8 permissions;

    if (req->length % CARD_READ_SIZE != 0) {
        OSPanic(lbl_803CCEE0, 0x822, lbl_800E7A38);
    }
    lbl_803C7838.op = 1;
    task = fn_800B0A5C_insertQueue(fn_800AAFEC, 0xFF);
    task->chan = req->chan;
    task->mode = req->mode;
    task->buffer = req->buffer;
    task->length = req->length;
    permissions = req->permissions;
    if (permissions == 0) {
        permissions = CARD_ATTR_PUBLIC;
    }
    task->permissions = permissions;
    lbl_802EF2C0[task->chan] = serial;
    lbl_803CC15C = req->verify;
    lbl_803CC158 = req->verifyArg;
    lbl_803CC160 = req->flags;
    lbl_803CC1B8->result = 0;
}

// .text:0x800AAFEC size:0x488
// NONMATCHING 78%: switch jump table lives in unsplit .data (reloc names differ); steps 0-5 are written as shared inline helpers, which lay out differently
// jtcheck: steps 0-3 share one arm (the CardMountSteps helper switches on them itself)
// nmverify: fn_800ACD64 inlined on one side (calls match once expanded)
#if NONMATCHING
void fn_800AAFEC(void) {
    CardWriteTask* task = (CardWriteTask*)lbl_803CC1B8;
    u8 status;

    switch (task->step) {
    case 0:
    case 1:
    case 2:
    case 3:
        CardMountSteps(&task->step, task->chan, task->mode, 9);
        break;
    case 4:
        CardCheckResultStep(&task->step, task->chan, 9);
        break;
    case 5:
        CardSerialStep(&task->step, task->chan, 9);
        break;
    case 6:
        if (lbl_803CC15C != NULL) {
            status = lbl_803CC15C(task->buffer, task->length, lbl_803CC158);
            if (status != CARD_STATUS_READY) {
                lbl_803C7838.status = status;
                task->step = 9;
                break;
            }
        }
        memset(((Task*)fn_800B0A5C_insertQueue(fn_800ABF44, 0xFF))->data, 0, sizeof(((Task*)0)->data));
        task->step = 7;
        lbl_803CC1B8->result = 0;
        break;
    case 7:
        switch (task->result) {
        case 1:
            task->step = 8;
            break;
        case 2:
            task->step = 9;
            break;
        }
        break;
    case 8:
        fn_800ACD64(CARDUnmount(task->chan));
        switch (lbl_803C7838.status) {
        case CARD_STATUS_BUSY:
            break;
        default:
            task->step = 9;
            break;
        }
        break;
    case 9:
        fn_800ACFB0(lbl_803CC16C);
        CardTaskFinish(1);
        break;
    }
}
#endif

// .text:0x800AB474 size:0xC0
void fn_800AB474(u8 chan, u8 mode, s16 blocks, char* fileName, u64 serial) {
    CardNameTask* task;

    lbl_803C7838.op = 3;
    task = fn_800B0A5C_insertQueue(fn_800AB534, 0xFF);
    memset(&task->step, 0, sizeof(((Task*)0)->data));
    task->chan = chan;
    task->mode = mode;
    task->arg = blocks;
    task->fileName = lbl_802EF2D0;
    memcpy(task->fileName, fileName, CARD_FILENAME_MAX);
    lbl_802EF2C0[chan] = serial;
    lbl_803CC1B8->result = 0;
}

// .text:0x800AB534 size:0x5E0
// NONMATCHING 84%: switch jump table lives in unsplit .data (reloc names differ); steps 0-5 are written as shared inline helpers, which lay out differently
// jtcheck: steps 0-3 share one arm (the CardMountSteps helper switches on them itself)
// nmverify: fn_800ACD64 inlined on one side (calls match once expanded)
#if NONMATCHING
void fn_800AB534(void) {
    CardNameTask* task = (CardNameTask*)lbl_803CC1B8;
    CardSlot* slot;
    s32 res;

    switch (task->step) {
    case 0:
    case 1:
    case 2:
    case 3:
        CardMountSteps(&task->step, task->chan, task->mode, 9);
        break;
    case 4:
        CardCheckResultStep(&task->step, task->chan, 9);
        break;
    case 5:
        CardSerialStep(&task->step, task->chan, 9);
        break;
    case 6:
        switch (CardFileExists(task->chan, task->fileName)) {
        case 0:
            task->outcome = 0;
            task->step = 8;
            break;
        case 1:
            task->step = 7;
            break;
        case 2:
            task->step = 9;
            break;
        }
        break;
    case 7:
        slot = &lbl_803C7838.slots[task->chan];
        res = CARDFreeBlocks(task->chan, &slot->bytesFree, &slot->filesFree);
        if (res >= 0) {
            slot = &lbl_803C7838.slots[task->chan];
            slot->blocksFree = slot->bytesFree / slot->sectorSize;
            slot->blocksTotal = ((slot->memSize << 20) / 8) / slot->sectorSize - 5;
        }
#ifdef TARGET_PC
        if (getenv("MSSB_DEBUG_CARD") != NULL) {
            fprintf(stderr, "[card] free: res %d bytes %d files %d sector %d mem %d -> blocks %d/%d need %d\n", res,
                    (int)slot->bytesFree, (int)slot->filesFree, (int)slot->sectorSize, (int)slot->memSize,
                    (int)slot->blocksFree, (int)slot->blocksTotal, (int)task->arg);
        }
#endif
        fn_800ACD64(res);
        switch (lbl_803C7838.status) {
        case CARD_STATUS_BUSY:
            break;
        case CARD_STATUS_READY:
            slot = &lbl_803C7838.slots[task->chan];
            if (slot->filesFree == 0) {
                task->outcome = 1;
            } else if (task->arg > slot->blocksFree) {
                task->outcome = 2;
            } else {
                task->outcome = 0;
            }
            task->step = 8;
            break;
        default:
            task->step = 9;
            break;
        }
        break;
    case 8:
        fn_800ACD64(CARDUnmount(task->chan));
        switch (lbl_803C7838.status) {
        case CARD_STATUS_BUSY:
            break;
        case CARD_STATUS_READY:
            switch (task->outcome) {
            case 1:
                lbl_803C7838.status = 5;
                break;
            case 2:
                lbl_803C7838.status = 6;
                break;
            }
            task->step = 9;
            break;
        default:
            task->step = 9;
            break;
        }
        break;
    case 9:
        task->parent->result = 1;
        fn_800B0A14_removeQueue(task->parent);
        break;
    }
}
#endif

// .text:0x800ABB14 size:0x4C
u16 fn_800ABB14(u8* data, s32 len) {
    u16 crc = 0xFFFF;
    while (--len >= 0) {
        crc = (crc << 8) ^ lbl_800E7800[(u8)(crc >> 8) ^ *data++];
    }
    return ~crc;
}

// .text:0x800ABB60 size:0x70
// NONMATCHING 94.1%: removeQueue is called with whatever r3 holds; our call passes &lbl_803C7838 explicitly
#if NONMATCHING
void fn_800ABB60(void) {
    CardSlot* slot = lbl_803C7838.slots;
    s32 chan;

    if (lbl_803C7838.op == 7) {
        fn_800B0A14_removeQueue(slot);
        return;
    }
    for (chan = 0; chan < 2; chan++, slot++) {
        slot->probeResult = CARDProbeEx(chan, &slot->memSize, &slot->sectorSize);
    }
}
#endif

// fn_800ABB14 as inlined into fn_800ABBD0 (the length argument is evaluated first).
static inline u16 cardCrcInline(s32 len, u8* data) {
    u16 crc = 0xFFFF;
    while (--len >= 0) {
        crc = (crc << 8) ^ lbl_800E7800[(u8)(crc >> 8) ^ *data++];
    }
    return ~crc;
}

// .text:0x800ABBD0 size:0x374
void fn_800ABBD0(void) {
    CARDStat* stat = &lbl_802EF330;
    CardMountTask* task = (CardMountTask*)lbl_803CC1B8;
    CardFileTask* file = (CardFileTask*)task->parent;
    s32 res;
    s32 length;
    s32 xferred;
    CardSaveHeader* header;

    switch (task->step) {
    case 0:
        res = CARDOpen(file->chan, file->fileName, &file->fileInfo);
        if (res == CARD_RESULT_READY) {
            file->fileNo = file->fileInfo.fileNo;
        } else {
            fn_800ACD64(res);
            CardTaskFinish(2);
            break;
        }
        res = CARDGetStatus(file->chan, file->fileNo, stat);
#ifdef TARGET_PC
        if (getenv("MSSB_DEBUG_CARD") != NULL) {
            fprintf(stderr, "[card] status: len 0x%x banner %d iconAddr 0x%x commentAddr 0x%x offsetData 0x%x iconFmt 0x%x\n",
                    (int)stat->length, stat->bannerFormat, (int)stat->iconAddr, (int)stat->commentAddr, (int)stat->offsetData,
                    stat->iconFormat);
        }
#endif
        if (res == CARD_RESULT_READY) {
            if (stat->iconAddr == 0xFFFFFFFF || stat->commentAddr == 0xFFFFFFFF) {
                fn_800ACD64(CARD_RESULT_CANCELED);
                lbl_803C7838.status = 0xB;
                CardTaskFinish(2);
                break;
            }
        } else {
            fn_800ACD64(res);
            CardTaskFinish(2);
            break;
        }
        task->step++;
        break;
    case 1:
        lbl_803CC168 = CARDGetXferredBytes(file->chan);
        if (file->mode == 1) {
            res = CARDReadAsync(&file->fileInfo, file->buffer, file->length, stat->offsetData, NULL);
            if (res < 0) {
                fn_800ACD64(res);
                CARDClose(&file->fileInfo);
                CardTaskFinish(2);
                break;
            }
            task->step++;
        } else {
            res = CARDRead(&file->fileInfo, file->buffer, file->length, stat->offsetData);
            CARDClose(&file->fileInfo);
            if (res < 0) {
                fn_800ACD64(res);
                CardTaskFinish(2);
                break;
            }
            task->step += 2;
        }
        break;
    case 2:
        length = file->length;
        xferred = CARDGetXferredBytes(file->chan) - lbl_803CC168;
        lbl_803C7838.xferred = xferred;
        lbl_803C7838.progress = (xferred * 100) / length;
        if ((u8)lbl_803C7838.progress > 100) {
            lbl_803C7838.progress = 100;
        }
        fn_800ACD64(CARDGetResultCode(file->chan));
        switch (lbl_803C7838.status) {
        case CARD_STATUS_BUSY:
            break;
        case CARD_STATUS_READY:
            CARDClose(&file->fileInfo);
            task->step++;
            break;
        default:
            CARDClose(&file->fileInfo);
            CardTaskFinish(2);
            break;
        }
        break;
    case 3:
        if (!(lbl_803CC160 & 1)) {
            header = file->buffer;
            if (header->crc != cardCrcInline(file->length - sizeof(CardSaveHeader), (u8*)(header + 1))) {
                Task* parent;
                lbl_803C7838.status = 0xB;
                parent = task->parent;
                parent->result = 2;
                fn_800B0A14_removeQueue(parent);
                break;
            }
        }
        task->step++;
    case 4:
        CardTaskFinish(1);
        break;
    }
}

// .text:0x800ABF44 size:0x5C4
// NONMATCHING 92%: switch jump table lives in unsplit .data (reloc names differ); register allocation differs
// nmverify: fn_800ACD64 inlined on one side (calls match once expanded)
#if NONMATCHING
void fn_800ABF44(void) {
    CARDStat* stat = &lbl_802EF330;
    CardMountTask* task = (CardMountTask*)lbl_803CC1B8;
    CardWriteTask* file = (CardWriteTask*)task->parent;
    CardSaveHeader* header;
    char name[CARD_FILENAME_MAX + 1];
    s32 res;
    s32 length;
    s32 xferred;
    BOOL busy;

    if (lbl_803C7838.slots[file->chan].probeResult == CARD_RESULT_NOCARD) {
        task->step = 10;
    }
    switch (task->step) {
    case 0:
        header = file->buffer;
        memcpy(header, &lbl_802EF2F0, 0x40);
        if (!(lbl_803CC160 & 1)) {
            header->crc = fn_800ABB14((u8*)(header + 1), file->length - sizeof(CardSaveHeader));
        }
        memcpy(lbl_803CC164, file->buffer, file->length);
        if (stat->commentAddr + file->length > stat->length) {
            OSPanic(lbl_803CCEE0, 0x3A4, lbl_800E7A38 + 0x58);
        }
        strncpy(name, stat->fileName, CARD_FILENAME_MAX);
        name[CARD_FILENAME_MAX] = '\0';
        if (strlen(name) >= CARD_FILENAME_MAX) {
            OSPanic(lbl_803CCEE0, 0x3AA, lbl_800E7A00);
        }
        res = CARDOpen(file->chan, stat->fileName, &file->fileInfo);
        switch (res) {
        case CARD_RESULT_NOFILE:
            task->step++;
            break;
        case CARD_RESULT_READY:
            task->step += 3;
            break;
        default:
            fn_800ACD64(res);
            task->step = 10;
            break;
        }
        break;
    case 1:
        if (file->mode == 1) {
            res = CARDCreateAsync(file->chan, stat->fileName, stat->length, &file->fileInfo, NULL);
            if (res < 0) {
                fn_800ACD64(res);
                CARDClose(&file->fileInfo);
                task->step = 10;
            } else {
                task->step++;
            }
        } else {
            res = CARDCreate(file->chan, stat->fileName, stat->length, &file->fileInfo);
            if (res < 0) {
                fn_800ACD64(res);
                CARDClose(&file->fileInfo);
                task->step = 10;
            } else {
                task->step += 2;
            }
        }
        break;
    case 2:
        fn_800ACD64(CARDGetResultCode(file->chan));
        switch (lbl_803C7838.status) {
        case CARD_STATUS_BUSY:
            break;
        case CARD_STATUS_READY:
            task->step++;
            break;
        default:
            CARDClose(&file->fileInfo);
            task->step = 10;
            break;
        }
        break;
    case 3:
        lbl_803CC168 = CARDGetXferredBytes(file->chan);
        file->fileNo = file->fileInfo.fileNo;
        if (file->mode == 1) {
            res = CARDWriteAsync(&file->fileInfo, lbl_803CC16C, stat->length, 0, NULL);
            if (res < 0) {
                fn_800ACD64(res);
                CARDClose(&file->fileInfo);
                task->step = 10;
            } else {
                task->step++;
            }
        } else {
            res = CARDWrite(&file->fileInfo, lbl_803CC16C, stat->length, 0);
            CARDClose(&file->fileInfo);
            if (res < 0) {
                fn_800ACD64(res);
                task->step = 10;
            } else {
                task->step += 2;
            }
        }
        break;
    case 4:
        length = stat->length;
        xferred = CARDGetXferredBytes(file->chan) - lbl_803CC168;
        lbl_803C7838.xferred = xferred;
        lbl_803C7838.progress = (xferred * 100) / length;
        if ((u8)lbl_803C7838.progress > 100) {
            lbl_803C7838.progress = 100;
        }
        fn_800ACD64(CARDGetResultCode(file->chan));
        switch (lbl_803C7838.status) {
        case CARD_STATUS_BUSY:
            break;
        case CARD_STATUS_READY:
            CARDClose(&file->fileInfo);
            task->step++;
            break;
        default:
            CARDClose(&file->fileInfo);
            task->step = 10;
            break;
        }
        break;
    case 5:
        if (file->mode == 1) {
            res = CARDSetStatusAsync(file->chan, file->fileNo, stat, NULL);
            if (res < 0) {
                fn_800ACD64(res);
                task->step = 10;
            } else {
                task->step++;
            }
        } else {
            res = CARDSetStatus(file->chan, file->fileNo, stat);
            if (res < 0) {
                fn_800ACD64(res);
                task->step = 10;
            } else {
                task->step += 2;
            }
        }
        break;
    case 6:
        fn_800ACD64(CARDGetResultCode(file->chan));
        switch (lbl_803C7838.status) {
        case CARD_STATUS_BUSY:
            break;
        case CARD_STATUS_READY:
            task->step++;
            break;
        default:
            task->step = 10;
            break;
        }
        break;
    case 7:
        if (file->mode == 1) {
            res = CARDSetAttributesAsync(file->chan, file->fileNo, file->permissions, NULL);
            if (res == CARD_RESULT_BUSY) {
                busy = TRUE;
            } else {
                fn_800ACD64(res);
                busy = FALSE;
            }
        } else {
            fn_800ACD64(CARDSetAttributes(file->chan, file->fileNo, file->permissions));
            busy = FALSE;
        }
        if (!busy) {
            task->step++;
        }
        break;
    case 8:
        fn_800ACD64(CARDGetResultCode(file->chan));
        switch (lbl_803C7838.status) {
        case CARD_STATUS_BUSY:
            break;
        case CARD_STATUS_READY:
            task->step = 9;
            break;
        default:
            task->step = 10;
            break;
        }
        break;
    case 9:
        CardTaskFinish(1);
        break;
    case 10:
        CardTaskFinish(2);
        break;
    }
}
#endif

// .text:0x800AC508 size:0x764
// NONMATCHING 91%: register allocation differs throughout (the inlined TPL unpacking keeps different values in saved registers)
#if NONMATCHING
void fn_800AC508(char* fileName, void* bannerTpl, s32 bannerSize, void* iconTpl, s32 iconSize, u32 iconSpeed,
                 u32 bannerFlags, char* comment, char* subComment, s32 blocks) {
    CARDStat* stat;
    u8* defaultBanner = NULL;
    u8* cursor;
    TEXPalette* pal;
    TEXDescriptor* desc;
    s16 hasClut;
    s32 i;
    s32 shift;

    memset(&lbl_802EF330, 0, sizeof(CARDStat) - 4);
    stat = &lbl_802EF330;
    stat->length = blocks << 13;
    lbl_803CC16C = _OSAllocFromHeap(0x20, stat->length);
    memset(lbl_803CC16C, 0, stat->length);
    strncpy(lbl_802EF330.fileName, fileName, CARD_FILENAME_MAX);

    if ((bannerTpl == NULL && bannerSize == 0) || comment == NULL) {
        defaultBanner = _OSAllocFromHeap(0x20, 0x1960);
        if (!LoadDefaultBanner(defaultBanner)) {
            OSPanic(lbl_803CCEE0, 0x2F4, lbl_800E7A38 + 0x74);
        }
    }

    memset(lbl_802EF2F0.comment[0], 0, 4);
    if (comment == NULL) {
        strncpy(lbl_802EF2F0.comment[0], (char*)defaultBanner + 0x1820, 0x1F);
    } else {
        strncpy(lbl_802EF2F0.comment[0], comment, 0x1F);
    }
    memset(lbl_802EF2F0.comment[1], 0, 4);
    strncpy(lbl_802EF2F0.comment[1], subComment, 0x1F);

    lbl_802EF330.iconAddr = 0;
    cursor = lbl_803CC16C;
    if (bannerTpl == NULL) {
        if (bannerSize == 0) {
            lbl_802EF330.bannerFormat = CARD_STAT_BANNER_RGB5A3;
            memcpy(cursor, defaultBanner + 0x20, 0x1800);
            cursor += 0x1800;
            lbl_803C7838.hasBanner = 1;
        }
    } else {
        pal = _OSAllocFromHeap(0x20, bannerSize);
        memcpy(pal, bannerTpl, bannerSize);
        UnpackTexPalette(pal);
        desc = TEXGet(pal, 0);
        switch (PTR32_GET(TEXHeader, desc->textureHeader)->format) {
        case GX_TF_RGB5A3:
            lbl_802EF330.bannerFormat = CARD_STAT_BANNER_RGB5A3;
            memcpy(cursor, PTR32_GET(char, PTR32_GET(TEXHeader, desc->textureHeader)->data), 0x1800);
            cursor += 0x1800;
            break;
        case GX_TF_C8:
            lbl_802EF330.bannerFormat = CARD_STAT_BANNER_C8;
            memcpy(cursor, PTR32_GET(char, PTR32_GET(TEXHeader, desc->textureHeader)->data), 0xC00);
            memcpy(cursor + 0xC00, PTR32_GET(char, PTR32_GET(CLUTHeader, desc->CLUTHeader)->data), 0x200);
            cursor += 0xE00;
            break;
        default:
            OSPanic(lbl_803CCEE0, 0x32E, lbl_800E7A38 + 0xA8);
            break;
        }
        fn_800ACFB0(pal);
        lbl_803C7838.hasBanner = 1;
    }

    if (iconTpl != NULL) {
        hasClut = 0;
        pal = _OSAllocFromHeap(0x20, iconSize);
        memcpy(pal, iconTpl, iconSize);
        UnpackTexPalette(pal);
        for (i = 0, shift = 0; (u32)i < pal->numDescriptors && i < CARD_ICON_MAX; i++, shift += 2) {
            desc = TEXGet(pal, i);
            switch (PTR32_GET(TEXHeader, desc->textureHeader)->format) {
            case GX_TF_RGB5A3:
                stat->iconFormat = (stat->iconFormat & ~(CARD_STAT_ICON_MASK << shift)) |
                                   (CARD_STAT_ICON_RGB5A3 << shift);
                memcpy(cursor, PTR32_GET(char, PTR32_GET(TEXHeader, desc->textureHeader)->data), 0x800);
                cursor += 0x800;
                break;
            case GX_TF_C8:
                stat->iconFormat = (stat->iconFormat & ~(CARD_STAT_ICON_MASK << shift)) |
                                   (CARD_STAT_ICON_C8 << shift);
                memcpy(cursor, PTR32_GET(char, PTR32_GET(TEXHeader, desc->textureHeader)->data), 0x400);
                hasClut = 1;
                cursor += 0x400;
                break;
            default:
                OSPanic(lbl_803CCEE0, 0x351, lbl_800E7A38 + 0xCC);
                break;
            }
            stat->iconSpeed = (stat->iconSpeed & ~(CARD_STAT_SPEED_MASK << shift)) | ((iconSpeed & 3) << shift);
        }
        for (; i < CARD_ICON_MAX; i++) {
            stat->iconFormat &= ~(CARD_STAT_ICON_MASK << (i * 2));
            stat->iconSpeed &= ~(CARD_STAT_SPEED_MASK << (i * 2));
        }
        lbl_803C7838.iconCount = i;
        if (hasClut == 1) {
            memcpy(cursor, PTR32_GET(char, PTR32_GET(CLUTHeader, desc->CLUTHeader)->data), 0x200);
            cursor += 0x200;
        }
        lbl_802EF330.bannerFormat |= bannerFlags & CARD_STAT_ANIM_BOUNCE;
        fn_800ACFB0(pal);
    }
    if (defaultBanner != NULL) {
        fn_800ACFB0(defaultBanner);
    }
    lbl_803CC164 = cursor;
    lbl_802EF330.commentAddr = (u32)(cursor - lbl_803CC16C);
}
#endif

// fn_800ACCD4, size:0x14
void fn_800ACCD4(void) {
    lbl_803C7838.op = 7;
}

// fn_800ACC6C, size:0x68
s32 fn_800ACC6C(s32 mode, s32 a, s32 b) {
    s32 base = mode;
    s32 total;
    s32 q;
    switch (mode) {
    case 0:
        base = 0;
        break;
    case 1:
        base = 0x1800;
        break;
    case 2:
        base = 0xE00;
        break;
    }
    total = base + a + b;
    q = total / 0x2000;
    if (total % 0x2000 != 0) {
        q++;
    }
    return q;
}

// .text:0x800ACCE8 size:0x5C
void fn_800ACCE8(void) {
    s32 i;
    memset(&lbl_803C7838, 0, sizeof(CardSystem));
    lbl_803C7838.status = CARD_STATUS_BUSY;
    for (i = 0; i < 2; i++) {
        lbl_803C7838.slots[i].probeResult = CARD_RESULT_BUSY;
    }
    fn_800B0A5C_insertQueue(fn_800ABB60, 0xF0);
}

// .text:0x800ACD44 size:0x20
void fn_800ACD44(void) {
    CARDInit();
}

// .text:0x800ACD64 size:0x1B0
void fn_800ACD64(s32 result) {
#ifdef TARGET_PC
    {
        static int s_trace = -1;
        if (s_trace < 0) {
            s_trace = getenv("MSSB_DEBUG_CARD") != NULL;
        }
        if (s_trace && result != CARD_RESULT_BUSY) {
            extern const char* port_symbol_name(void* p);
            fprintf(stderr, "[card] result %d in %s\n", result, port_symbol_name(__builtin_return_address(0)));
        }
    }
#endif
    lbl_803C7838.lastResult = result;
    switch (result) {
    case CARD_RESULT_READY:
        lbl_803C7838.status = CARD_STATUS_READY;
        break;
    case CARD_RESULT_BUSY:
        lbl_803C7838.status = CARD_STATUS_BUSY;
        break;
    case CARD_RESULT_NOCARD:
        lbl_803C7838.status = 0;
        break;
    case CARD_RESULT_BROKEN:
        lbl_803C7838.status = 1;
        break;
    case CARD_RESULT_ENCODING:
        lbl_803C7838.status = 2;
        break;
    case CARD_RESULT_IOERROR:
    case CARD_RESULT_FATAL_ERROR:
        lbl_803C7838.status = 3;
        break;
    case CARD_RESULT_WRONGDEVICE:
        lbl_803C7838.status = 4;
        break;
    case CARD_RESULT_NOENT:
        lbl_803C7838.status = 5;
        break;
    case CARD_RESULT_INSSPACE:
        lbl_803C7838.status = 6;
        break;
    case CARD_RESULT_EXIST:
        lbl_803C7838.status = 8;
        break;
    case CARD_RESULT_CANCELED:
    case CARD_RESULT_NOPERM:
    case CARD_RESULT_LIMIT:
        if (lbl_803C7838.op == 1) {
            lbl_803C7838.status = 9;
        } else if (lbl_803C7838.op == 2) {
            lbl_803C7838.status = 10;
        }
        break;
    case CARD_RESULT_NOFILE:
        if (lbl_803C7838.op == 1) {
            lbl_803C7838.status = 9;
        } else if (lbl_803C7838.op == 2) {
            lbl_803C7838.status = 14;
        }
        break;
    case CARD_RESULT_NAMETOOLONG:
        OSPanic(lbl_803CCEE0, 0xEC, lbl_800E7B28);
        break;
    case CARD_RESULT_BAD_SECTOR_SIZE:
        lbl_803C7838.status = 7;
        break;
    }
}

// Header placed just before every block handed out by the arena.
typedef struct HeapBlockHeader {
    /*0x0*/ u8* prev; // arena end (lo or hi) before this allocation
    /*0x4*/ s32 size;
} HeapBlockHeader;

// The arena never checks for overflow; on PC, stop at the allocation that
// overruns it rather than at some later write past its end.
#ifdef TARGET_PC
#define PORT_HEAP_CHECK(size)                                                                    \
    do {                                                                                         \
        if (lbl_803C7898.freeSize < 0) {                                                         \
            OSReport("heap overrun: %d bytes requested, %d free\n", (s32)(size), lbl_803C7898.freeSize); \
            __builtin_trap();                                                                    \
        }                                                                                        \
    } while (0)
#else
#define PORT_HEAP_CHECK(size)
#endif

// .text:0x800ACF14 size:0x20
void fn_800ACF14(void* block) {
    u8* hi = ((HeapBlockHeader*)block)[-1].prev;
    lbl_803C7898.hi = hi;
    lbl_803C7898.freeSize = (s32)(hi - lbl_803C7898.lo);
}

// .text:0x800ACF34 size:0x44
// NONMATCHING 97.3%: register allocation (heap pointer in r4 instead of r5, lo/result regs differ)
#if NONMATCHING
void* fn_800ACF34(s32 align, s32 size) {
    HeapArena* heap = &lbl_803C7898;
    u8* lo;
    u8* oldHi;
    u8* block;
    u8* newHi;
    size = (size + 3) & ~3;
    oldHi = heap->hi;
    lo = heap->lo;
    block = (u8*)(-align & (uintptr_t)(oldHi - size));
    newHi = block - sizeof(HeapBlockHeader);
    ((HeapBlockHeader*)block)[-1].prev = oldHi;
    ((HeapBlockHeader*)block)[-1].size = (s32)(oldHi - newHi);
    heap->freeSize = (s32)(newHi - lo);
    heap->hi = newHi;
    PORT_HEAP_CHECK(size);
    return block;
}
#endif

// .text:0x800ACF78 size:0x38
// NONMATCHING 96.4%: register allocation (base/total/diff registers rotated)
#if NONMATCHING
void fn_800ACF78(void* block, s32 size) {
    HeapArena* heap;
    u8* base = ((HeapBlockHeader*)block)[-1].prev;
    s32 total;
    heap = &lbl_803C7898;
    total = ((size + 3) & ~3) + (s32)((u8*)block - base);
    heap->lo = base + total;
    heap->freeSize = (s32)(heap->hi - heap->lo);
    ((HeapBlockHeader*)block)[-1].size = total;
    PORT_HEAP_CHECK(size);
}
#endif

// .text:0x800ACFB0 size:0x20
void fn_800ACFB0(void* block) {
    u8* lo = ((HeapBlockHeader*)block)[-1].prev;
    lbl_803C7898.lo = lo;
    lbl_803C7898.freeSize = (s32)(lbl_803C7898.hi - lo);
}

// .text:0x800ACFD0 size:0x4C
// NONMATCHING 72%: original computes (align + 7) before adding lo; ours reassociates to (lo + align) + 7
#if NONMATCHING
void* _OSAllocFromHeap(s32 align, s32 size) {
    u8* lo = lbl_803C7898.lo;
    u8* hi = lbl_803C7898.hi;
    u8* block;
    size = (size + 3) & ~3;
    block = (u8*)(-align & (uintptr_t)(lo + (align + (s32)sizeof(HeapBlockHeader) - 1))); // room for the header
    ((HeapBlockHeader*)block)[-1].prev = lo;
    ((HeapBlockHeader*)block)[-1].size = (s32)(block - lo) + size;
    lo = size + block;
    lbl_803C7898.freeSize = (s32)(hi - lo);
    lbl_803C7898.lo = lo;
    PORT_HEAP_CHECK(size);
    return block;
}
#endif

// .text:0x800AD01C size:0x1C
void fn_800AD01C(void* hi) {
    lbl_803C7898.hi = hi;
    lbl_803C7898.freeSize = (s32)((u8*)hi - lbl_803C7898.lo);
}

// .text:0x800AD038 size:0x1C
void fn_800AD038(void* lo) {
    lbl_803C7898.lo = lo;
    lbl_803C7898.freeSize = (s32)(lbl_803C7898.hi - (u8*)lo);
}

// .text:0x800AD054 size:0x1C
void fn_800AD054(void* lo, void* hi) {
    lbl_803C7898.lo = lo;
    lbl_803C7898.hi = hi;
    lbl_803C7898.freeSize = (s32)((u8*)hi - (u8*)lo);
}

extern u8 lbl_803CC17C;               // stop requested
extern u8 lbl_803CC17D;               // movie busy
extern u8 lbl_803CC17E;               // movie thread running
extern u8 lbl_803CC17F;               // movie system initialised
extern u8 lbl_803CC181;
extern u8 lbl_803CC182;               // a new frame was decoded this tick
extern ThpPlayer* lbl_803CC170;       // active movie
extern void (*lbl_803CC190)(u32 frame); // per-frame callback; when NULL the frame is queued for drawing
extern u32 lbl_803CC198;              // which of lbl_801112E0 is queued next
extern u32 lbl_803CC1A4;
extern u32 lbl_803CC1AC;
extern OSMessageQueue lbl_802FB870;   // movie thread commands
extern OSThread lbl_802FB220;         // movie thread
extern DrawCallbackNode lbl_801112E0[2];
extern GXTexObj lbl_803C78A4;         // texture of the current frame
extern GXTexFmt lbl_803CBAD8[2];      // texture format per ThpPlayer.format
extern void (*lbl_803CBB08[2])(void* src, void* dst, u16 width, u16 height); // frame converters
extern u16 lbl_803CBAE4;              // audio block size
extern ThpBufferInfo lbl_803C7A00;

extern void fn_800E4B90(ThpVideoInfo* video, void* work);
extern u32 fn_800E4B1C(ThpVideoInfo* video);

// Playback state of a movie: 0 stopped, 1 playing, 2/0x12 paused, 4 finished, 0xA0000000 no disc
// status, 0x80000000 | n DVD drive status n, 0xC0000000 no movie.
static inline u32 ThpGetState(ThpPlayer* p) {
    u8 state;

    if (p == NULL) {
        return 0xC0000000;
    }
    state = p->state;
    if (state & 4) {
        return 4;
    }
    switch (lbl_803C6CF8.driveStatus) {
    case -1:
        return 0xA0000000;
    default:
        return lbl_803C6CF8.driveStatus | 0x80000000;
    case 0:
        if (state & 2) {
            return state & 0x12;
        }
        if (state & 1) {
            return 1;
        }
        return 0;
    }
}

static inline BOOL ThpIsIdle(ThpPlayer* p) {
    u32 state = ThpGetState(p);
    if (state == 0) {
        return TRUE;
    }
    if (state == 4 && lbl_803CC170 == NULL) {
        return TRUE;
    }
    return FALSE;
}

static inline void ThpStop(ThpPlayer* p) {
    if (!ThpIsIdle(p)) {
        OSSendMessage(&lbl_802FB870, (OSMessage)2, OS_MESSAGE_NOBLOCK);
    }
}

static inline void ThpPause(ThpPlayer* p) {
    if (p->state & 1) {
        p->state = 2;
        p->pauseStart = OSGetTime();
    }
}

static inline void ThpResume(ThpPlayer* p, u8 flags) {
    u8 state;

    if (p != NULL) {
        state = p->state;
        if (state == 0 || state == 4) {
            p->flags = flags;
            OSSendMessage(&lbl_802FB870, (OSMessage)1, OS_MESSAGE_NOBLOCK);
        } else if (state & 2) {
            p->state = 1;
            p->startTime += OSGetTime() - p->pauseStart;
        }
    }
}

// .text:0x800AD070 size:0x420
// NONMATCHING 81%: register allocation and block layout differ
// nmverify: fn_800A7D4C inlined on one side (calls match once expanded)
#if NONMATCHING
void fn_800AD070(void) {
    ThpPlayer* p;
    u32 state;
    u8 i;
    ThpFrame* frame;
    OSTime elapsed;
    u64 base;
    u16 width;
    u16 height;
    void* tex;

    if (!lbl_803CC17F || (p = lbl_803CC170) == NULL) {
        return;
    }
    if (!(p->flags & 1)) {
        if (!(p->state & 0x10) && lbl_803C6CF8.driveStatus == 5) {
            ThpPause(p);
            p->state |= 0x10;
        }
    }
    state = ThpGetState(p);
    if ((state == 0x12 || state == 0x80000003) && p != NULL) {
        ThpResume(p, p->flags);
    }
    if (p->state & 1) {
        if (p->state & 8) {
            for (i = 0; i < 6; i++) {
                if (p->frames[i].state != 1) {
                    goto queue;
                }
            }
            if (p->flags & 1) {
                p->startFrameTime = 0;
            } else {
                p->startTime = OSGetTime();
            }
            p->state = 1;
        }
        elapsed = OSGetTime() - p->startTime;
        if (p->flags & 1) {
            base = p->startFrameTime * 1000000 / (p->audioRate * 4);
            p->currentFrame = (u32)((base + OSTicksToMicroseconds(elapsed)) / p->frameTime);
        } else {
            p->currentFrame = (u32)(OSTicksToMicroseconds(elapsed) / p->frameTime);
        }
        for (i = 0, frame = p->frames; i < 6; i++, frame++) {
            if (frame->state == 1 && p->currentFrame == frame->frameNo) {
                frame->state = 2;
                width = p->video.width;
                height = p->video.height;
                p->texIndex ^= 1;
                tex = p->texBuf[p->texIndex];
                lbl_803CBB08[p->format](frame->data, tex, width, height);
                GXInitTexObj(&lbl_803C78A4, tex, width, height, lbl_803CBAD8[p->format], GX_CLAMP, GX_CLAMP,
                             GX_FALSE);
                lbl_803CC182 = TRUE;
            }
        }
    }
queue:
    if (lbl_803CC182) {
        if (lbl_803CC190 != NULL) {
            lbl_803CC190(p->currentFrame);
            return;
        }
        fn_800A7D4C(0, &lbl_801112E0[lbl_803CC198]);
        lbl_803CC198 ^= 1;
    }
}
#endif

// .text:0x800AD490 size:0x70
// NONMATCHING 87%: the 'state & 2' branch is folded into beqlr with a speculative clrlwi; the original keeps two returns
#if NONMATCHING
u32 fn_800AD490(ThpPlayer* p) {
    u8 state;

    if (p == NULL) {
        return 0xC0000000;
    }
    state = p->state;
    if (state & 4) {
        return 4;
    }
    switch (lbl_803C6CF8.driveStatus) {
    case -1:
        return 0xA0000000;
    default:
        return lbl_803C6CF8.driveStatus | 0x80000000;
    case 0:
        if (state & 2) {
            return state & 0x12;
        } else {
            return state & 1;
        }
    }
}
#endif

// .text:0x800AD500 size:0x1BC
// NONMATCHING 85%: register allocation and the order of the size computations differ
#if NONMATCHING
void fn_800AD500(ThpPlayer* p, u8* work) {
    u16 width = p->video.width;
    u16 height = p->video.height;
    u8 mcuX = p->video.mcuX;
    u8 mcuY = p->video.mcuY;
    u32 audioBlocks = lbl_803CBAE4 * (((u32)OSRoundUp32B(p->audioBufSize) + (lbl_803CBAE4 - 1)) / lbl_803CBAE4);
    u32 pixels = width * height;
    u32 audioSize = audioBlocks * 0x1C;
    u32 texSize = pixels << (p->format + 1);
    u32 mcus;
    u32 frameSize;

    fn_800E4B90(&p->video, work);
    texSize = (u32)OSRoundUp32B(texSize);
    p->texBuf[0] = work + OSRoundUp32B(fn_800E4B1C(&p->video));
    p->texBuf[1] = p->texBuf[0] + texSize;
    memset(p->texBuf[0], 0, texSize * 2);
    GXInitTexObj(&lbl_803C78A4, p->texBuf[0], width, height, lbl_803CBAD8[p->format], GX_CLAMP, GX_CLAMP, GX_FALSE);
    p->texIndex = 0;
    p->readBuf = p->texBuf[1] + texSize;
    p->audioBuf = p->readBuf + OSRoundUp32B(p->readBufSize);
    memset(p->audioBuf, 0, audioSize);
    mcus = mcuX * mcuY;
#ifdef TARGET_PC
    p->_154 = p->chans[1].bufStart = p->chans[0].bufStart = p->audioBuf + OSRoundUp32B(p->audioBufSize);
#else
    p->_154 = p->_E8 = p->_D0 = p->audioBuf + OSRoundUp32B(p->audioBufSize);
#endif
    p->_158 = p->_160 = p->_154;
#ifdef TARGET_PC
    p->frames[0].data = p->_15C = p->chans[1].bufEnd = p->chans[0].bufEnd = p->_154 + audioSize;
#else
    p->frames[0].data = p->_15C = p->_EC = p->_D4 = p->_154 + audioSize;
#endif
    frameSize = (u32)OSRoundUp32B(pixels * (mcus + 2) / mcus);
    p->frames[1].data = p->frames[0].data + frameSize;
    p->frames[2].data = p->frames[1].data + frameSize;
    p->frames[3].data = p->frames[2].data + frameSize;
    p->frames[4].data = p->frames[3].data + frameSize;
    p->frames[5].data = p->frames[4].data + frameSize;
}
#endif

// .text:0x800AD6BC size:0xC4
// NONMATCHING 78%: the size terms are computed and summed in a different order
#if NONMATCHING
u32 fn_800AD6BC(ThpPlayer* p) {
    u32 mcus = p->video.mcuX * p->video.mcuY;
    u32 readBufSize = p->readBufSize;
    u32 pixels = p->video.width * p->video.height;
    u32 audioBufSize = (u32)OSRoundUp32B(p->audioBufSize);
    u32 texSize = pixels << (p->format + 1);
    u32 audioBlocks = lbl_803CBAE4 * ((audioBufSize + (lbl_803CBAE4 - 1)) / lbl_803CBAE4);
    u32 audioSize = audioBlocks * 0x1C;
    u32 total = (u32)OSRoundUp32B(readBufSize) + (u32)OSRoundUp32B(texSize) * 2 + audioBufSize + audioSize +
                (u32)OSRoundUp32B(pixels * (mcus + 2) / mcus) * 6;
    return total + (u32)OSRoundUp32B(fn_800E4B1C(&p->video));
}
#endif

// .text:0x800AD780 size:0xB0
BOOL fn_800AD780(ThpPlayer* p) {
    return ThpIsIdle(p);
}

// .text:0x800AD830 size:0xE4
void fn_800AD830(ThpPlayer* p) {
    ThpStop(p);
}

// .text:0x800AD914 size:0x48
void fn_800AD914(ThpPlayer* p) {
    ThpPause(p);
}

// .text:0x800AD95C size:0x98
void fn_800AD95C(ThpPlayer* p, u8 flags) {
    ThpResume(p, flags);
}

// .text:0x800AD9F4 size:0x108
void fn_800AD9F4(ThpPlayer* p) {
    if (p != NULL) {
        if (p->state & 3) {
            ThpStop(p);
        }
        OSSendMessage(&lbl_802FB870, (OSMessage)3, OS_MESSAGE_NOBLOCK);
    }
}

// fn_800ADAFC, size:0x8
BOOL fn_800ADAFC(void) {
    return lbl_803CC17D;
}

// .text:0x800ADB04 size:0xF8
#pragma push
#pragma dont_inline on // the heap functions live in another file in the original
BOOL fn_800ADB04(ThpMovie* movie, ThpPlayer* p, u8 format, u8 freeBuffer) {
    if ((s32)lbl_803CC17D != 0) {
        return FALSE;
    }
    lbl_803CC181 = freeBuffer;
    lbl_803CC170 = p;
    p->movie = movie;
    lbl_803CC1A4 = movie->_0C;
    if (lbl_803CC181) {
        lbl_803CC1AC = lbl_803CC1A4;
        if (lbl_803C7A00.buffer != NULL) {
            fn_800ACFB0(lbl_803C7A00.buffer);
        }
    }
    lbl_803CC170->framePtrs[0] = &lbl_803CC170->frames[0];
    lbl_803CC170->framePtrs[1] = &lbl_803CC170->frames[1];
    lbl_803CC170->framePtrs[2] = &lbl_803CC170->frames[2];
    lbl_803CC170->framePtrs[3] = &lbl_803CC170->frames[3];
    lbl_803CC170->framePtrs[4] = &lbl_803CC170->frames[4];
    lbl_803CC170->framePtrs[5] = &lbl_803CC170->frames[5];
    lbl_803CC170->format = format;
    if (!lbl_803CC17E) {
        OSResumeThread(&lbl_802FB220);
    }
    OSSendMessage(&lbl_802FB870, (OSMessage)0, OS_MESSAGE_NOBLOCK);
    return TRUE;
}
#pragma pop

// .text:0x800ADBFC size:0x44
void fn_800ADBFC(void) {
    if (lbl_803CC17F) {
        lbl_803CC17C = TRUE;
        OSSendMessage(&lbl_802FB870, (OSMessage)4, OS_MESSAGE_NOBLOCK);
    }
}

// ---- Data (initialisers generated from the original DOL) ----

// .data 0x80110080..0x801101B0
PadConfig lbl_80110080 = {0, 12, 2, 0, 32, -50, 50}; // NOTE: type size 0xC != symbol size 0x10

// .bss 0x802ED140..0x802F93A0 (MWCC lays these out in reverse definition order)
CARDMemoryCard lbl_802EF3A0;
CARDStat lbl_802EF330;
CardSaveHeader lbl_802EF2F0;
char lbl_802EF2D0[(32)];
u64 lbl_802EF2C0[2];
DVDCommandBlock lbl_802EF290;
DVDCommandBlock lbl_802EF260;
DVDCommandBlock lbl_802EF230;
DVDCommandBlock lbl_802EF200;
DVDCommandBlock lbl_802EF1D0;
DVDCommandBlock lbl_802EF1A0;
DVDCommandBlock lbl_802EF170;
DVDCommandBlock lbl_802EF140;
u8 lbl_802ED140[0x2000];

// .sdata 0x803CBAD0..0x803CBAE0
GXColor lbl_803CBAD0 = {0, 0, 0, 255}; // NOTE: type size 0x4 != symbol size 0x8
GXTexFmt lbl_803CBAD8[2] = {4, 6};

// .sbss 0x803CC128..0x803CC170 (MWCC lays these out in reverse definition order)
u8* lbl_803CC16C;
s32 lbl_803CC168;
u8* lbl_803CC164;
u32 lbl_803CC160;
u8 (*lbl_803CC15C)(void* buffer, s32 length, u32 arg);
u32 lbl_803CC158;
StreamTrack* lbl_803CC154;
StreamTrack* lbl_803CC150;
StreamTrack* lbl_803CC14C;
volatile u32 lbl_803CC148;
volatile u32 lbl_803CC144;
volatile u32 lbl_803CC140;
volatile u32 lbl_803CC13C;
volatile u32 lbl_803CC138;
volatile u8 lbl_803CC135;
volatile u8 lbl_803CC134;
volatile u32 lbl_803CC130;
volatile u32 lbl_803CC12C;
void (*lbl_803CC128)(void);

