#include "main/file_800ADC40.h"
#include "main/file_800A6870.h"
#include "main/file_80008E00.h"
#include "static/GameSettings.h"
#include "static/Camera.h"
#include "static/Pad.h"
#include "Dolphin/os.h"
#include "Dolphin/ai.h"
#include "Dolphin/ar.h"
#include "Dolphin/gx.h"
#include "Dolphin/mtx.h"
#include "Dolphin/stl.h"
#include "string.h"
#include "Unknown/File_0x800a6304.h"
#include "main/file_800DFDD4.h"

void* _OSAllocFromHeap(s32 align, u32 size);

// movie.c: HVQM4 movie player.

typedef struct MovThreads {
    /*0x000*/ OSThread decodeThread;
    /*0x318*/ OSThread streamThread;
    /*0x630*/ OSMessage msgs[8];
} MovThreads; // lbl_802FB220, size: 0x650

typedef struct MovQueue {
    /*0x0000*/ OSMessageQueue queue;
    /*0x0020*/ u8 _20[0x10];
    /*0x0030*/ u8 streamStack[0x1000];
    /*0x1030*/ u8 decodeStack[0x2000];
} MovQueue; // lbl_802FB870, size: 0x3030

// YUV->RGB lookup tables; the s16 tables hold byte offsets into clamp.
typedef struct YuvTable {
    /*0x000*/ s16 y[256];
    /*0x200*/ s16 vR[256];
    /*0x400*/ s16 vG[256];
    /*0x600*/ s16 uG[256];
    /*0x800*/ s16 uB[256];
    /*0xA00*/ u8 clamp[0x600];
} YuvTable;

#ifdef TARGET_PC
// lbl_803C7420 is the VideoSystem (its retrace queue); use the real layout.
#include "main/video_system.h"
#define sleepQueue retraceQueue
#else
typedef struct MovSync {
    /*0x00*/ u8 _00[0x5C];
    /*0x5C*/ OSThreadQueue sleepQueue;
} MovSync; // lbl_803C7420
#endif

// movie.c bss (not split into this unit yet)
extern s16 lbl_802F93A0[16];       // quad vertices, buffer 0
extern s16 lbl_802F93C0[16];       // quad vertices, buffer 1
extern s16 lbl_802F93E0[2][0x780]; // AI DMA double buffer
extern Mtx44 lbl_802FB1E0;         // ortho projection
extern MovThreads lbl_802FB220;
extern MovQueue lbl_802FB870;

extern GXTexObj lbl_803C78A4;
extern ARQRequest lbl_803C78C4[2]; // ARAM -> MRAM
extern ARQRequest lbl_803C7994[2]; // MRAM -> ARAM
extern MovAramRing lbl_803C79D4;
extern MovMramRing lbl_803C7A00;
#ifndef TARGET_PC
extern MovSync lbl_803C7420;
#endif

extern u16 lbl_801101C0[128]; // volume table
extern YuvTable lbl_801102C0;
extern u8 lbl_801112C0[0x20]; // quad display list

extern u8 lbl_803CBAE0;   // audio volume (0-127)
extern u16 lbl_803CBAE2;
extern u16 lbl_803CBAE4;  // AI DMA length in bytes
extern u8** lbl_803CBAE8[2]; // stream read pointer (DVD, MRAM)
extern u8** lbl_803CBAF0[2]; // stream write pointer (DVD, MRAM)
extern u32* lbl_803CBAF8[2]; // stream bytes available (DVD, MRAM)
extern s16* lbl_803CBB00[2]; // quad vertex buffers

extern MovPlayer* lbl_803CC170; // movie being played
extern u8* lbl_803CC174;        // stream buffer
extern u32 lbl_803CC178;        // stream buffer size
extern u8 lbl_803CC17C;         // quit request
extern u8 lbl_803CC17D;
extern u8 lbl_803CC17E;         // decode thread running
extern u8 lbl_803CC17F;         // initialised
extern u8 lbl_803CC180;         // decode step
extern u8 lbl_803CC181;         // movie is cached in ARAM
extern u8 lbl_803CC182;
extern f32 lbl_803CC184;        // quad depth
extern const GXColor lbl_803CCEE8; // white
extern u32 lbl_803CC188;        // AI DMA buffer index
extern AIDCallback lbl_803CC18C; // previous AI DMA callback
extern void (*lbl_803CC190)(u32 frame); // per-frame callback (file_800A7C08.c)
extern u8 lbl_803CC194;         // vertex buffer index
extern s32 lbl_803CC19C;        // last decode result
extern u32 lbl_803CC1A0;        // stream bytes consumed
extern u32 lbl_803CC1A4;        // stream length
extern u8 lbl_803CC1A8;         // ARAM write counter
extern u32 lbl_803CC1AC;        // movie file size

// movie.c strings (rodata not split into this unit)
extern char lbl_800E7B50[]; // "YUV->RGB Conv SrcAddr is NULL!!\n", followed by the strings below
#ifdef TARGET_PC
// The code reaches the strings that follow by offset (MOVSTR); on PC they are
// separate objects, so keep the whole pool here (bytes from main.dol).
static char s_movStrings[352] = "YUV->RGB Conv SrcAddr is NULL!!\x0a" "\x00" "\x00" "\x00" "\x00" "YUV->RGB Conv DstAddr is NULL!!\x0a" "\x00" "\x00" "\x00" "\x00" "sNp_MovDecodeThread()::ERR!! broken file.\x0a" "\x00" "\x00" "sNp_MovStreamThread()::ERR!! broken file.\x0a" "\x00" "\x00" "HVQM4 1.3\x00" "\x00" "\x00" "sNp_MovStreamThread()::ERR!! Invalid version.\x0a" "\x00" "\x00" "sNp_MovStreamThread()::ERR!! Invalid audio samples per second \x0a" "\x00" "sNp_MovStreamThread()::ERR!! failed to allocate the working buffer\x0a" "\x00" "";
#define lbl_800E7B50 s_movStrings
#endif
extern char lbl_800E7B74[]; // "YUV->RGB Conv DstAddr is NULL!!\n"
extern char lbl_800E7B98[];
extern char lbl_803CCF00[8]; // lbl_803CCF00
#define MOV_STR_DECODE_BROKEN (lbl_800E7B98)
#define MOVSTR(base, off) ((base) + (off)) // string at offset off from lbl_800E7B50       // MOV_STR_DECODE_BROKEN
#define MOV_STR_STREAM_BROKEN 0x74 // MOV_STR_STREAM_BROKEN
#define MOV_STR_HVQM4 0xA0         // "HVQM4 1.3"
#define MOV_STR_BAD_VERSION 0xAC   // MOV_STR_BAD_VERSION
#define MOV_STR_BAD_RATE 0xDC      // "...Invalid audio samples per second \n"
#define MOV_STR_NO_BUFFER 0x11C    // "...failed to allocate the working buffer\n"

#define MOV_STATE_STOP 4
#define MOV_DVD_DONE() ((s32)*(volatile u8*)&lbl_803C6CF8.idle)

#ifdef TARGET_PC
static int port_skip_movies(void) {
    static int s_skip = -1;
    if (s_skip < 0) {
        const char* env = getenv("MSSB_SKIP_MOVIES");
#ifdef __EMSCRIPTEN__
        // The web build always skips them (decoding is too slow there);
        // MSSB_SKIP_MOVIES=0 (?movies) plays them.
        s_skip = env == NULL || env[0] != '0';
#else
        s_skip = env != NULL && env[0] != '\0' && env[0] != '0';
#endif
    }
    return s_skip;
}

// MSSB_MOVIE_STATS=1: once a second, how the movie keeps up. "clock" is the
// audio clock (samplesPlayed) against wall time: below 1.00 the movie plays in
// slow motion. "underruns" are AI periods MovMixAudio skipped because the
// decoder had not produced the audio yet; "late" frames were dropped by the
// decoder (and every P/B frame after one until the next I frame).
static struct {
    s32 on;
    OSTime windowStart;
    u64 samplesStart;
    vu32 underruns;
    u32 decoded, late, noSlot;
} s_movStats = {-1};

static void port_mov_stats(MovPlayer* mov) {
    OSTime now;
    u32 ms;

    if (s_movStats.on < 0) {
        const char* env = getenv("MSSB_MOVIE_STATS");
        s_movStats.on = env != NULL && env[0] != '\0' && env[0] != '0';
    }
    if (!s_movStats.on || mov == NULL) {
        return;
    }
    now = OSGetTime();
    if (s_movStats.windowStart == 0) {
        s_movStats.windowStart = now;
        s_movStats.samplesStart = mov->samplesPlayed;
        return;
    }
    ms = (u32)OSTicksToMilliseconds(now - s_movStats.windowStart);
    if (ms < 1000) {
        return;
    }
    OSReport("[movie] frame %u/%u clock %.2fx decoded %u late %u slot-waits %u underruns %u (avg decode %u us, %u us/frame)\n",
             mov->curFrame, mov->numFrames,
             mov->sampleRate != 0 && mov->samplesPlayed >= s_movStats.samplesStart
                 ? (double)(mov->samplesPlayed - s_movStats.samplesStart) / (mov->sampleRate * 4.0) / (ms / 1000.0)
                 : 0.0,
             s_movStats.decoded, s_movStats.late, s_movStats.noSlot, s_movStats.underruns,
             mov->decodedFrames != 0 ? mov->decodeTime / mov->decodedFrames : 0, mov->usecPerFrame);
    s_movStats.windowStart = now;
    s_movStats.samplesStart = mov->samplesPlayed;
    s_movStats.underruns = 0;
    s_movStats.decoded = s_movStats.late = s_movStats.noSlot = 0;
}
#define MOV_STAT(field) (s_movStats.field++)
#endif

// The HVQM4 stream is big-endian: on PC the headers are swapped into native
// fields as they are read (exactly once each).
#ifdef TARGET_PC
static inline void MOV_SWAP_HEADER(MovPlayer* mov) {
    swap32_array(&mov->numBlocks - 1, 8); // 0x14..0x34; videoInfo is read bytewise
    swap32_inplace(&mov->sampleRate);
}
#define MOV_SWAP_BLOCK(mov) swap32_array(&(mov)->_060, 5)
static inline void MOV_SWAP_RECORD(MovPlayer* mov) {
    mov->recType = be16(mov->recType);
    mov->recFormat = be16(mov->recFormat);
    mov->recSize = be32(mov->recSize);
}
#define MOV_READ_U32(p) read_be32(p)
// Busy waits must give the CPU up on PC (no preemption by interrupts).
#define MOV_YIELD() OSYieldThread()
#else
#define MOV_YIELD()
#define MOV_SWAP_HEADER(mov)
#define MOV_SWAP_BLOCK(mov)
#define MOV_SWAP_RECORD(mov)
#define MOV_READ_U32(p) (*(u32*)(p))
#endif

// NONMATCHING 73%: the movie.c bss is not split into this unit; the original addresses all of it relative to lbl_802F93A0 (also float rodata names)
#if NONMATCHING
// .text:0x800ADC40 size:0x130
void fn_800ADC40(u8* streamBuf, u32 streamBufSize) {
    if (lbl_803CC17F == 0) {
        lbl_803CC174 = streamBuf;
        lbl_803CC178 = streamBufSize;
        if (AIGetDSPSampleRate() == 1) {
            lbl_803CBAE2 = 0xF0;
            lbl_803CBAE4 = 0x3C0;
        } else {
            lbl_803CBAE2 = 0xA0;
            lbl_803CBAE4 = 0x280;
        }
        fn_800E4AC8();
        lbl_803CC170 = NULL;
        lbl_803CC17C = 0;
        lbl_803CC190 = 0;
        lbl_803CC180 = 0;
        lbl_803CC18C = AIRegisterDMACallback(fn_800AE5B8);
        C_MTXOrtho(lbl_802FB1E0, 0.0f, 480.0f, 0.0f, 640.0f, -0.0f, -16777216.0f);
        OSInitMessageQueue(&lbl_802FB870.queue, lbl_802FB220.msgs, 8);
        OSCreateThread(&lbl_802FB220.streamThread, fn_800AE8B8, NULL, lbl_802FB870.streamStack + sizeof(lbl_802FB870.streamStack),
                       sizeof(lbl_802FB870.streamStack), 20, 1);
        OSCreateThread(&lbl_802FB220.decodeThread, MovDecodeThread, NULL, lbl_802FB870.decodeStack + sizeof(lbl_802FB870.decodeStack),
                       sizeof(lbl_802FB870.decodeStack), 31, 1);
        OSResumeThread(&lbl_802FB220.streamThread);
        OSResumeThread(&lbl_802FB220.decodeThread);
        lbl_803CC17F = 1;
    }
}
#endif

// .text:0x800ADD70 size:0x1F0
void fn_800ADD70(void* node) {
    MovPlayer* mov = lbl_803CC170;
    f32 proj[7];
    Mtx mtx;
    GXColor color;
    s16* v;
    s16 z;

    if (mov != NULL) {
        GXGetProjectionv(proj);
        GXSetProjection(lbl_802FB1E0, GX_ORTHOGRAPHIC);
        GXInvalidateTexAll();
        GXLoadTexObj(&lbl_803C78A4, GX_TEXMAP0);
        GXInvalidateVtxCache();
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
        lbl_803CC194 ^= 1;
        v = lbl_803CBB00[lbl_803CC194];
        v[0] = v[9] = mov->posX;
        v[1] = v[4] = mov->posY;
        v[3] = v[6] = mov->posX + mov->width - 1;
        v[7] = v[10] = mov->posY + mov->height - 1;
        z = lbl_803CC184;
        v[2] = v[5] = v[8] = v[11] = z;
        DCFlushRange(v, 0x18);
#ifdef TARGET_PC
        (GXSetArray)(GX_VA_POS, v, 0x18, 6, true); // native s16 positions
#else
        GXSetArray(GX_VA_POS, v, 6);
#endif
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetNumChans(1);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        color = lbl_803CCEE8;
        GXSetChanMatColor(GX_COLOR0A0, color);
        GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        PSMTXIdentity(mtx);
        GXLoadPosMtxImm(mtx, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        GXCallDisplayList(lbl_801112C0, 0x20);
        GXSetProjectionv(proj);
    }
}

// GX texture data is big-endian (aurora reads it as the GameCube does).
#ifdef TARGET_PC
#define YUV_TEXEL(x) be32((u32)(x))
#else
#define YUV_TEXEL(x) (x)
#endif
#define YUV_CLAMP(t, y, c) (((y) + (c))[0xA00]) // y: table base + luma offset; 0xA00 = clamp

// NONMATCHING 58%: the compiler folds the 0xA00 clamp offset into the shared chroma terms (lbzx) where the
// original adds y+c and loads lbz 0xa00(r); NULL checks use cmplw against r0 in the original
#if NONMATCHING
// .text:0x800ADF60 size:0x338
// Converts a planar YUV 4:2:0 image to GX RGBA8 tiles.
void YUV2RGB(u8* src, u8* dst, s32 width, s32 height) {
    YuvTable* t = &lbl_801102C0;
    u8* y0;
    u8* y1;
    u8* u;
    u8* v;
    u8* tileRow;
    u32* out;
    u8 row;
    s32 x;
    s32 vR, g, uB;
    s32 ya;
    s32 yb;
    u8 cu;
    u8 cv;

    if (src == NULL) {
        OSReport(lbl_800E7B50);
        for (;;) {}
    }
    if (dst == NULL) {
        OSReport(lbl_800E7B74);
        for (;;) {}
    }
    y0 = src;
    x = width;
    y1 = src + width;
    u = src + width * height;
    v = u + (width >> 1) * (height >> 1);
    do {
        tileRow = dst;
        row = 0;
        do {
            dst = tileRow;
            do {
                out = (u32*)(dst + row * 4);
                cv = v[0];
                cu = u[0];
                vR = t->vR[cv];
                g = t->vG[cv] + t->uG[cu];
                uB = t->uB[cu];
                ya = t->y[y0[0]];
                yb = t->y[y0[1]];
                out[0] = YUV_TEXEL((t->clamp[ya + vR] << 16) | 0xFF00FF00 | t->clamp[yb + vR]);
                out[8] = YUV_TEXEL((t->clamp[ya + g] << 24) | (t->clamp[ya + uB] << 16) | (t->clamp[yb + g] << 8) | t->clamp[yb + uB]);
                ya = t->y[y1[0]];
                yb = t->y[y1[1]];
                out[2] = YUV_TEXEL((t->clamp[ya + vR] << 16) | 0xFF00FF00 | t->clamp[yb + vR]);
                out[10] = YUV_TEXEL((t->clamp[ya + g] << 24) | (t->clamp[ya + uB] << 16) | (t->clamp[yb + g] << 8) | t->clamp[yb + uB]);

                cv = v[1];
                cu = u[1];
                vR = t->vR[cv];
                g = t->vG[cv] + t->uG[cu];
                uB = t->uB[cu];
                ya = t->y[y0[2]];
                yb = t->y[y0[3]];
                out[1] = YUV_TEXEL((t->clamp[ya + vR] << 16) | 0xFF00FF00 | t->clamp[yb + vR]);
                out[9] = YUV_TEXEL((t->clamp[ya + g] << 24) | (t->clamp[ya + uB] << 16) | (t->clamp[yb + g] << 8) | t->clamp[yb + uB]);
                ya = t->y[y1[2]];
                yb = t->y[y1[3]];
                out[3] = YUV_TEXEL((t->clamp[ya + vR] << 16) | 0xFF00FF00 | t->clamp[yb + vR]);
                out[11] = YUV_TEXEL((t->clamp[ya + g] << 24) | (t->clamp[ya + uB] << 16) | (t->clamp[yb + g] << 8) | t->clamp[yb + uB]);

                v += 2;
                u += 2;
                y0 += 4;
                y1 += 4;
                if (row == 4) {
                    __dcbf(dst, 0);
                    __dcbf(dst + 0x20, 0);
                }
                dst += 0x40;
            } while ((x -= 4) > 0);
            y0 = y1;
            x = width;
            y1 += width;
            row += 4;
        } while (row <= 4);
    } while ((height -= 4) > 0);
    PPCSync();
}
#endif

#define RGB565(r, g, b) ((((r) << 8) & 0xF800) | (((g) << 3) & 0x7E0) | (((b) & 0xF8) >> 3))

// NONMATCHING 48%: same issues as YUV2RGB
#if NONMATCHING
// .text:0x800AE298 size:0x320
// Converts a planar YUV 4:2:0 image to GX RGB565 tiles.
void YUV2RGB_(u8* src, u8* dst, s32 width, s32 height) {
    YuvTable* t = &lbl_801102C0;
    u8* y0;
    u8* y1;
    u8* u;
    u8* v;
    u8* tileRow;
    u32* out;
    u8 row;
    s32 x;
    s32 vR, g, uB;
    u8* ya;
    u8* yb;

    if (src == NULL) {
        OSReport(lbl_800E7B50);
        for (;;) {}
    }
    if (dst == NULL) {
        OSReport(lbl_800E7B74);
        for (;;) {}
    }
    y0 = src;
    x = width;
    y1 = src + width;
    u = src + width * height;
    v = u + (width >> 1) * (height >> 1);
    do {
        tileRow = dst;
        for (row = 0; row <= 4; row += 4) {
            dst = tileRow;
            do {
                out = (u32*)(dst + row * 4);
                vR = t->vR[v[0]];
                g = t->vG[v[0]] + t->uG[u[0]];
                uB = t->uB[u[0]];
                ya = (u8*)t + t->y[y0[0]];
                yb = (u8*)t + t->y[y0[1]];
                out[0] = YUV_TEXEL((RGB565(YUV_CLAMP(t, ya, vR), YUV_CLAMP(t, ya, g), YUV_CLAMP(t, ya, uB)) << 16) |
                         RGB565(YUV_CLAMP(t, yb, vR), YUV_CLAMP(t, yb, g), YUV_CLAMP(t, yb, uB)));
                ya = (u8*)t + t->y[y1[0]];
                yb = (u8*)t + t->y[y1[1]];
                out[2] = YUV_TEXEL((RGB565(YUV_CLAMP(t, ya, vR), YUV_CLAMP(t, ya, g), YUV_CLAMP(t, ya, uB)) << 16) |
                         RGB565(YUV_CLAMP(t, yb, vR), YUV_CLAMP(t, yb, g), YUV_CLAMP(t, yb, uB)));

                vR = t->vR[v[1]];
                g = t->vG[v[1]] + t->uG[u[1]];
                uB = t->uB[u[1]];
                ya = (u8*)t + t->y[y0[2]];
                yb = (u8*)t + t->y[y0[3]];
                out[1] = YUV_TEXEL((RGB565(YUV_CLAMP(t, ya, vR), YUV_CLAMP(t, ya, g), YUV_CLAMP(t, ya, uB)) << 16) |
                         RGB565(YUV_CLAMP(t, yb, vR), YUV_CLAMP(t, yb, g), YUV_CLAMP(t, yb, uB)));
                ya = (u8*)t + t->y[y1[2]];
                yb = (u8*)t + t->y[y1[3]];
                out[3] = YUV_TEXEL((RGB565(YUV_CLAMP(t, ya, vR), YUV_CLAMP(t, ya, g), YUV_CLAMP(t, ya, uB)) << 16) |
                         RGB565(YUV_CLAMP(t, yb, vR), YUV_CLAMP(t, yb, g), YUV_CLAMP(t, yb, uB)));

                v += 2;
                u += 2;
                y0 += 4;
                y1 += 4;
                if (row == 4) {
                    __dcbf(dst, 0);
                }
                dst += 0x20;
            } while ((x -= 4) > 0);
            y0 = y1;
            x = width;
            y1 += width;
        }
    } while ((height -= 4) > 0);
    PPCSync();
}
#endif

// NONMATCHING 99%: volatile-register numbering only (volume r5 vs mov->state r4) in fn_800AE5B8
#if NONMATCHING
// Mixes the movie's decoded audio into an AI DMA buffer.
static inline void MovMixAudio(s16* buf) {
    MovPlayer* mov = lbl_803CC170;
    u8 volume = lbl_803CBAE0;
    u32 len = lbl_803CBAE4;
    s16 sample;
    u8* read;
    s16* dst;
    u32 off;
    u32 i;

    if (mov == NULL || !(mov->state & 1) || (mov->state & 8) || !(mov->flags & 1)) {
        return;
    }
    read = mov->audioRead;
    if (read < mov->audioWrite && (read + len > mov->audioWrite || (mov->state & 2))) {
#ifdef TARGET_PC
        MOV_STAT(underruns);
#endif
        return;
    }
    off = 0;
    dst = buf;
    for (i = 0; i < len / 2; i++) {
        if (read + off > mov->audioEnd) {
            read = mov->audioStart - off;
        }
        sample = *(s16*)(read + off);
        off += 2;
        *dst += (s16)((sample & 0x8000) + (((u32)(sample * lbl_801101C0[volume & 0x7F]) >> 15) & 0x7FFF));
        dst++;
    }
    mov->audioRead += len;
    mov->samplesPlayed += len;
    mov->startTime = OSGetTime();
    if (mov->audioRead >= mov->audioEnd) {
        mov->audioRead = mov->audioStart + (mov->audioRead - mov->audioEnd);
    }
}

// .text:0x800AE5B8 size:0x300
// AI DMA callback: queues the next buffer and mixes movie audio into it.
void fn_800AE5B8(void) {
    s16* buf;
    s16* cur;
    BOOL intr;

    lbl_803CC18C();
    lbl_803CC188 ^= 1;
    buf = lbl_802F93E0[lbl_803CC188];
    cur = (s16*)OSPhysicalToCached(AIGetDMAStartAddr());
    if (cur != NULL) {
        intr = OSEnableInterrupts();
        DCInvalidateRange(cur, lbl_803CBAE4);
        MovMixAudio(cur);
        DCFlushRange(cur, lbl_803CBAE4);
        OSRestoreInterrupts(intr);
    } else {
        AIInitDMA((uintptr_t)buf, lbl_803CBAE4);
        intr = OSEnableInterrupts();
        memset(buf, 0, lbl_803CBAE4);
        MovMixAudio(buf);
        DCFlushRange(buf, lbl_803CBAE4);
        OSRestoreInterrupts(intr);
    }
}
#endif

// Reads the next block header and restarts playback timing.
static inline BOOL MovStartBlock(MovPlayer* mov) {
    BOOL intr;

    if (!fn_800AF9B4(&mov->_060, 0x14)) {
        OSPanic(lbl_803CCF00, 0x355, MOV_STR_DECODE_BROKEN);
        return FALSE;
    }
    MOV_SWAP_BLOCK(mov);
    if ((mov->flags & 1) && mov->rateMode == 0xFF) {
        mov->flags &= ~1;
    }
    intr = OSDisableInterrupts();
    mov->samplesPlayed = 0;
    mov->startTime = 0;
    mov->decodedFrames = 0;
    mov->decodeTime = 0;
    mov->blockAudioDone = 0;
    mov->blockVideoDone = 0;
    mov->frameBase = 0;
    mov->blockIndex = 0;
    mov->audioRead = mov->audioWrite = mov->audioStart;
    mov->state = 9;
    lbl_803CC180 = 0;
    OSRestoreInterrupts(intr);
    return TRUE;
}

static inline void MovResetFrames(MovPlayer* mov) {
    mov->frames[0].ready = 0;
    mov->frames[1].ready = 0;
    mov->frames[2].ready = 0;
    mov->frames[3].ready = 0;
    mov->frames[4].ready = 0;
    mov->frames[5].ready = 0;
}

// .text:0x800AE8B8 size:0x260
// Stream thread: handles play / restart / stop / pause / quit messages.
void* fn_800AE8B8(void* arg) {
    OSMessage msg;
    MovPlayer* mov;

    for (;;) {
        OSReceiveMessage(&lbl_802FB870.queue, &msg, OS_MESSAGE_BLOCK);
        mov = lbl_803CC170;
        switch ((s32)(intptr_t)msg) {
        case 0:
            if (MovStreamThread(mov) == FALSE) {
                OSSendMessage(&lbl_802FB870.queue, (OSMessage)0, OS_MESSAGE_BLOCK);
            } else {
                lbl_803CC17D = 1;
            }
            break;
        case 1:
            MovStartBlock(mov);
            break;
        case 2:
            mov->state = MOV_STATE_STOP;
            while (mov->decoding) {
                OSSleepThread(&lbl_803C7420.sleepQueue);
            }
            if (!lbl_803CC181) {
                fn_800A6C80();
                while (MOV_DVD_DONE() != 1) {}
            }
            MovResetFrames(mov);
            mov->samplesPlayed = 0;
            mov->startTime = 0;
            mov->decodedFrames = 0;
            mov->decodeTime = 0;
            mov->blockAudioDone = 0;
            mov->blockVideoDone = 0;
            mov->frameBase = 0;
            mov->blockIndex = 0;
            mov->audioRead = mov->audioWrite = mov->audioStart;
            lbl_803CC170 = NULL;
            if (lbl_803CC181) {
                fn_800AFBF0();
            }
            break;
        case 3:
            lbl_803CC182 = 0;
            lbl_803CC17D = 0;
            break;
        case 4:
            lbl_803CC182 = 0;
            AIRegisterDMACallback(lbl_803CC18C);
            lbl_803CC18C = NULL;
            while (lbl_803CC17E) {
                OSSleepThread(&lbl_803C7420.sleepQueue);
            }
            lbl_803CC17F = 0;
            return NULL;
        }
    }
}

// .text:0x800AEB18 size:0x20C
// Opens the movie stream and parses the HVQM4 header.
BOOL MovStreamThread(MovPlayer* mov) {
    char* str = lbl_800E7B50;
    u32 i;

    lbl_803CC1A0 = 0;
    fn_800A6E24(mov->file, lbl_803CC174, lbl_803CC178);
    if (lbl_803CC181) {
        fn_800B05E4(-1, 0x10000);
        lbl_803CC174 = lbl_803C7A00.start;
        lbl_803CC178 = lbl_803C7A00.size;
    }
    if (!fn_800AF9B4(mov, 0x44)) {
        OSPanic(lbl_803CCF00, 0x2ED, MOVSTR(str, MOV_STR_STREAM_BROKEN));
        return FALSE;
    }
    MOV_SWAP_HEADER(mov);
    if (strncmp(MOVSTR(str, MOV_STR_HVQM4), mov->magic, strlen(MOVSTR(str, MOV_STR_HVQM4))) != 0) {
        for (i = 0x44; i != 0; i--) {}
        OSPanic(lbl_803CCF00, 0x300, MOVSTR(str, MOV_STR_BAD_VERSION));
        return FALSE;
    }
    mov->rateMode = 0xFF;
    if (mov->sampleRate != 0) {
        if (mov->sampleRate == 0xBBAA) {
            if (AIGetDSPSampleRate() != 1) {
                OSPanic(lbl_803CCF00, 0x30B, MOVSTR(str, MOV_STR_BAD_RATE));
                return FALSE;
            }
            mov->rateMode = 1;
        } else if (mov->sampleRate == 0x7D1C) {
            if (AIGetDSPSampleRate() != 0) {
                OSPanic(lbl_803CCF00, 0x313, MOVSTR(str, MOV_STR_BAD_RATE));
                return FALSE;
            }
            mov->rateMode = 0;
        } else {
            OSPanic(lbl_803CCF00, 0x31A, MOVSTR(str, MOV_STR_BAD_RATE));
            return FALSE;
        }
    }
    fn_800E4AE8(&mov->video, mov->videoInfo);
    if (fn_800E4B1C(&mov->video) == 0) {
        OSPanic(lbl_803CCF00, 0x324, MOVSTR(str, MOV_STR_NO_BUFFER));
        return FALSE;
    }
    mov->width = mov->video.width;
    mov->height = mov->video.height;
    mov->posY = (480 - mov->height) >> 1;
    mov->posX = (640 - mov->width) >> 1;
    return TRUE;
}

// fn_800AED24, size:0x10
s32 fn_800AED24(void) {
    return !lbl_803CC19C;
}

// Frame the playback clock is at: wall time since the last audio DMA,
// plus the audio already played when syncing to audio.
static inline void MovUpdateFrame(MovPlayer* mov) {
    if (mov->flags & 1) {
        mov->curFrame = (u32)((OSTicksToMicroseconds(OSGetTime() - mov->startTime) +
                         mov->samplesPlayed * 1000000 / (mov->sampleRate * 4)) /
                        mov->usecPerFrame);
    } else {
        mov->curFrame = (u32)(OSTicksToMicroseconds(OSGetTime() - mov->startTime) / mov->usecPerFrame);
    }
}

// .text:0x800AED34 size:0x474
// Decode thread: runs the decoder and handles end of movie / looping.
void* MovDecodeThread(void* arg) {
    MovPlayer* mov;
    BOOL ok;

    OSSuspendThread(&lbl_802FB220.decodeThread);
    lbl_803CC17E = 1;
    for (;;) {
        if (lbl_803CC17C) {
            break;
        }
        if ((mov = lbl_803CC170) == NULL || !(mov->state & 1)) {
#ifdef TARGET_PC
            // Busy wait: on the GameCube the retrace interrupt preempts this
            // thread; on PC it must give the CPU up.
            OSYieldThread();
#endif
            continue;
        }
        mov->decoding = 1;
#ifdef TARGET_PC
        // MSSB_SKIP_MOVIES=1: one-shot movies end at once, through the
        // normal end-of-movie path (looping ones keep playing).
        if (port_skip_movies() && !(mov->flags & 2)) {
            mov->numFrames = 0;
            lbl_803CC19C = 3;
        } else
#endif
        lbl_803CC19C = fn_800AF1A8(mov);
#ifdef TARGET_PC
        port_mov_stats(mov);
#endif
        switch (lbl_803CC19C) {
#ifdef TARGET_PC
        case 0:
            // One record decoded. On the GameCube the retrace interrupt
            // preempts this lowest-priority thread as soon as it wakes the
            // game's threads; on PC a thread only switches at scheduling
            // points, and this loop has none while frame slots are free, so it
            // could hold the CPU for several frame decodes and make the main
            // thread miss retraces (movie display and audio clock both stall).
            OSYieldThread();
            break;
#endif
        case 1: // waiting for data
            MOV_YIELD();
            break;
        case 2:
            OSPanic(lbl_803CCF00, 0x27D, MOV_STR_DECODE_BROKEN);
            mov->state = MOV_STATE_STOP;
            mov->decoding = 0;
            break;
        case 3:
            if (mov->flags & 2) {
                do {
                    MovUpdateFrame(mov);
                    if (lbl_803CC17C) {
                        goto exit;
                    }
                    MOV_YIELD();
                } while (mov->curFrame < mov->numFrames);
                MovResetFrames(mov);
                lbl_803CC1A0 = 0;
                if (!lbl_803CC181) {
                    fn_800A6E24(mov->file, lbl_803CC174, lbl_803CC178);
                } else {
                    fn_800AFC10();
                    lbl_803CC174 = lbl_803C7A00.start;
                }
                if (!fn_800AF9B4(mov, 0x44)) {
                    ok = FALSE;
                } else {
                    MOV_SWAP_HEADER(mov);
                    ok = MovStartBlock(mov);
                }
                if (!ok) {
                    mov->state = MOV_STATE_STOP;
                    lbl_803CC170 = NULL;
                }
            } else {
                do {
                    MovUpdateFrame(mov);
                    if (lbl_803CC17C) {
                        goto exit;
                    }
                    MOV_YIELD();
                } while (mov->curFrame < mov->numFrames);
                lbl_803CC170 = NULL;
                mov->state = MOV_STATE_STOP;
            }
            break;
        }
        mov->decoding = 0;
    }
exit:
    lbl_803CC17E = 0;
    return NULL;
}

#define MOV_AVAIL() (*lbl_803CBAF8[lbl_803CC181])

// .text:0x800AF1A8 size:0x454
// One decode step. Returns 0 = done/continue, 1 = waiting for data, 2 = error, 3 = end of movie.
s32 fn_800AF1A8(MovPlayer* mov) {
    u32 size;
    u16 type;
    u32 format;

    switch (lbl_803CC180) {
    case 0:
        if (mov->blockVideoDone == mov->blockVideoFrames && mov->blockAudioDone == mov->blockAudioFrames) {
            mov->frameBase += mov->blockVideoFrames;
            mov->blockIndex++;
            if (mov->blockIndex < mov->numBlocks) {
                if (mov->state == MOV_STATE_STOP) {
                    return 0;
                }
                if (MOV_AVAIL() < 0x14) {
                    mov->frameBase -= mov->blockVideoFrames;
                    mov->blockIndex--;
                    return 2;
                }
                if (!fn_800AF9B4(&mov->_060, 0x14)) {
                    return 2;
                }
                MOV_SWAP_BLOCK(mov);
                if (mov->state == MOV_STATE_STOP) {
                    return 0;
                }
                mov->blockAudioDone = 0;
                mov->blockVideoDone = 0;
            } else {
                return 3;
            }
        }
        lbl_803CC180++;
    case 1:
        if (MOV_AVAIL() < 8) {
            return 1;
        }
        if (!fn_800AF9B4(&mov->recType, 8)) {
            return 2;
        }
        MOV_SWAP_RECORD(mov);
        if (mov->state == MOV_STATE_STOP) {
            return 0;
        }
        lbl_803CC180++;
    case 2:
        size = mov->recSize;
        type = mov->recType;
        format = mov->recFormat;
        if (MOV_AVAIL() < size) {
            return 1;
        }
        switch (type) {
        case 1: {
            u32 count;

            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            if (!fn_800AF9B4(mov->videoBuf, 4)) {
                return 2;
            }
            count = MOV_READ_U32(mov->videoBuf);
            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            if (!fn_800AF9B4(mov->videoBuf, size - 4)) {
                return 2;
            }
            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            for (;;) {
                OSTime start = OSGetTime();

                if (mov->state == MOV_STATE_STOP) {
                    return 0;
                }
                switch (fn_800AF5FC(mov, format, count)) {
                case 2:
#ifdef TARGET_PC
                    MOV_STAT(noSlot);
                    OSYieldThread(); // waiting for a frame slot to be shown
#endif
                    continue;
                case 0:
                    if (mov->state == MOV_STATE_STOP) {
                        return 0;
                    }
                    mov->decodeTime += OSTicksToMicroseconds(OSGetTime() - start);
                    mov->decodedFrames++;
#ifdef TARGET_PC
                    MOV_STAT(decoded);
#endif
                    break;
                case 1:
                    return 1;
                case 3:
#ifdef TARGET_PC
                    MOV_STAT(late);
#endif
                    break;
                }
                break;
            }
            mov->blockVideoDone++;
            break;
        }
        case 0: {
            u32 count;
            u8* end;

            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            if (!fn_800AF9B4(mov->audioBuf, 4)) {
                return 2;
            }
            count = MOV_READ_U32(mov->audioBuf);
            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            if (!fn_800AF9B4(mov->audioBuf, size - 4)) {
                return 2;
            }
            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            end = mov->audioWrite + count * 4;
            do {
                if (end >= mov->audioEnd) {
                    end -= mov->audioEnd - mov->audioRead;
                }
                MOV_YIELD(); // waits for the audio interrupt to consume (and reload audioRead)
            } while (mov->audioWrite < mov->audioRead && end >= mov->audioRead);
            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            fn_800DFDD4(mov->audioBuf, mov->audioWrite, mov->numChannels, format, count, mov->chans);
            end = mov->chans[mov->numChannels - 1].outPtr;
            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            mov->audioWrite = end;
            mov->blockAudioDone++;
            break;
        }
        default:
            return 2;
        }
        break;
    }
    lbl_803CC180 = 0;
    return 0;
}

// .text:0x800AF5FC size:0x3B8
// Decodes one video frame into a free slot of the frame queue.
// Returns 0 = decoded, 1 = unknown format, 2 = no free slot, 3 = frame is late / refs missing.
s32 fn_800AF5FC(MovPlayer* mov, u32 format, u32 frame) {
    u32 decodeFrames;
    u32 now;
    u32 margin;
    u8 i;
    u8 found;
    MovFrame* tmp;

    if (mov->decodedFrames != 0) {
        decodeFrames = mov->decodeTime / mov->decodedFrames / mov->usecPerFrame;
    } else {
        decodeFrames = 0;
    }
    if (mov->flags & 1) {
        now = mov->samplesPlayed != 0 ? (u32)(mov->samplesPlayed * 1000000 / (mov->sampleRate * 4) / mov->usecPerFrame) : 0;
    } else {
        now = mov->startTime != 0 ? (u32)(OSTicksToMicroseconds(OSGetTime() - mov->startTime) / mov->usecPerFrame) : 0;
    }
    margin = (now != 0) ? decodeFrames + 1 : 0;

    switch ((s32)format) {
    case 0x10:
    case 0x20:
        found = FALSE;
        for (i = 2; i < 6; i++) {
            if (mov->frameQueue[i]->ready != 1 || now > mov->frameQueue[i]->frame) {
                tmp = mov->frameQueue[i];
                mov->frameQueue[i] = mov->frameQueue[0];
                mov->frameQueue[0] = mov->frameQueue[1];
                mov->frameQueue[1] = tmp;
                found = TRUE;
                break;
            }
        }
        if (!found) {
            return 2;
        }
        mov->frameQueue[1]->ready = 0;
        if (now + margin > frame + mov->frameBase) {
            return 3;
        }
        if (format == 0x10) {
            fn_800E4FF4(&mov->video, mov->videoBuf, mov->frameQueue[1]->buf);
        } else {
            if (!mov->frameQueue[0]->ready) {
                return 3;
            }
            fn_800E591C(&mov->video, mov->videoBuf, mov->frameQueue[1]->buf, mov->frameQueue[0]->buf);
        }
        mov->frameQueue[1]->frame = frame + mov->frameBase;
        if (mov->state == MOV_STATE_STOP) {
            return 0;
        }
        mov->frameQueue[1]->ready = 1;
        break;
    case 0x30:
        if (!mov->frameQueue[0]->ready) {
            return 3;
        }
        if (!mov->frameQueue[1]->ready) {
            return 3;
        }
        if (now + margin > frame + mov->frameBase) {
            return 3;
        }
        for (i = 2; i < 6; i++) {
            if (mov->frameQueue[i]->ready != 1 || now > mov->frameQueue[i]->frame) {
                mov->frameQueue[i]->ready = 0;
                fn_800E5940(&mov->video, mov->videoBuf, mov->frameQueue[i]->buf, mov->frameQueue[0]->buf, mov->frameQueue[1]->buf);
                mov->frameQueue[i]->frame = frame + mov->frameBase;
                if (mov->state == MOV_STATE_STOP) {
                    return 0;
                }
                mov->frameQueue[i]->ready = 1;
                return 0;
            }
        }
        return 2;
    default:
        return 1;
    }
    return 0;
}

// .text:0x800AF9B4 size:0x23C
// Reads len bytes from the movie stream (DVD ring or ARAM-backed MRAM ring).
BOOL fn_800AF9B4(void* dst, u32 len) {
    u32 count; // bytes before the wrap, then whole 32-byte blocks consumed
    u8* src;
    u8* wrap;
    u8* read;
    u8* write;
    u32 off;
    s32 room;
    s32 left;
    BOOL intr;

    if (lbl_803CC1A0 + len > lbl_803CC1A4) {
        return FALSE;
    }
    while (MOV_AVAIL() < len) {
        if (!fn_800AFFB0() && lbl_803CC181) {
            fn_800AFD4C();
        } else if (!lbl_803CC181) {
            OSSleepThread(&lbl_803C7420.sleepQueue);
        }
        if (lbl_803CC17C) {
            return FALSE;
        }
        if (lbl_803CC170 != NULL && lbl_803CC170->state == MOV_STATE_STOP) {
            return FALSE;
        }
    }
    intr = OSDisableInterrupts();
    off = lbl_803CC1A0 & 0x1F;
    read = *lbl_803CBAE8[lbl_803CC181];
    write = *lbl_803CBAF0[lbl_803CC181];
    if (read < write) {
        src = read + off;
        wrap = NULL;
        count = (u32)(write - src);
    } else {
        src = read + off;
        wrap = lbl_803CC174;
        count = (u32)(lbl_803CC174 + lbl_803CC178 - src);
    }
    OSRestoreInterrupts(intr);
    if (len < count) {
        memcpy(dst, src, len);
    } else {
        memcpy(dst, src, count);
        memcpy((u8*)dst + count, wrap, len - count);
    }
    count = ((lbl_803CC1A0 + len) & ~0x1F) - (lbl_803CC1A0 & ~0x1F);
    if (count != 0) {
        if (lbl_803CC181) {
            fn_800AFFC0(count);
        } else {
            fn_800A6D10(count);
        }
        if (lbl_803CC181) {
            room = lbl_803C7A00.size - lbl_803C7A00.filled;
            left = lbl_803CC1AC - lbl_803C79D4.totalOut;
            if (room > 0) {
                if (left > room) {
                    fn_800B0008(room & ~0x1F);
                } else if (lbl_803CC1AC > lbl_803C79D4.totalOut) {
                    fn_800B0008(left);
                }
            }
            if (lbl_803C79D4.totalIn < lbl_803CC1AC) {
                fn_800B0134(count);
            }
        }
    }
    lbl_803CC1A0 += len;
    return TRUE;
}

// .text:0x800AFBF0 size:0x20
void fn_800AFBF0(void) {
    fn_800A63C8();
}

// Copies len bytes from the ARAM ring into the MRAM ring.
static inline BOOL MovFillFromAram(u32 len) {
    MovMramRing* mram = &lbl_803C7A00;
    u32 first;
    u32 second;
    u8* wrap;

    len = (u32)OSRoundUp32B(len);
    if (mram->filled >= mram->size) {
        return TRUE;
    }
    if (mram->writePtr + len > mram->end) {
        first = (u32)(mram->end - mram->writePtr);
        wrap = mram->start;
        second = len - first;
    } else {
        first = len;
        wrap = NULL;
        second = 0;
    }
    fn_800B0230(mram->writePtr, first);
    while (lbl_803C79D4.busy) {}
    if (second != 0) {
        fn_800B0230(wrap, second);
        while (lbl_803C79D4.busy) {}
    }
    if (mram->writePtr + len < mram->end) {
        mram->writePtr += first;
    } else {
        mram->writePtr = mram->start + second;
    }
    mram->filled += len;
    if (lbl_803C79D4.totalOut > lbl_803CC1AC) {
        memset(mram->writePtr - (lbl_803C79D4.totalOut - lbl_803CC1AC), 0, lbl_803C79D4.totalOut - lbl_803CC1AC);
    }
    return TRUE;
}

// Copies len bytes from the DVD stream buffer into the ARAM ring.
static inline BOOL MovStoreToAram(u32 len) {
    u32 first;
    u32 second;
    u8* src;
    u8* wrap;
    BOOL intr;

    while (lbl_803C6CF8.buffered < len) {}
    intr = OSDisableInterrupts();
    src = lbl_803C6CF8.readPos;
    if (src + len < lbl_803C7A00.dvdBufStart + lbl_803C7A00.dvdBufSize) {
        wrap = NULL;
        first = len;
        second = 0;
    } else {
        first = (u32)(lbl_803C7A00.dvdBufStart + lbl_803C7A00.dvdBufSize - src);
        wrap = lbl_803C7A00.dvdBufStart;
        second = len - first;
    }
    OSRestoreInterrupts(intr);
    if (len >= first) {
        fn_800B03F4(src, len);
    } else {
        fn_800B03F4(src, first);
        while (lbl_803C79D4.busy) {}
        fn_800B03F4(wrap, second);
    }
    while (lbl_803C79D4.busy) {}
    if (len != 0) {
        fn_800A6D10(len);
    }
    return TRUE;
}

// .text:0x800AFC10 size:0x13C
// Rewinds both rings to the start of the ARAM copy and refills MRAM.
void fn_800AFC10(void) {
    MovAramRing* aram = &lbl_803C79D4;
    MovMramRing* mram = &lbl_803C7A00;

    aram->readPos = aram->writePos = aram->start;
    aram->totalOut = 0;
    mram->readPtr = mram->writePtr = mram->start;
    mram->filled = 0;
    mram->consumed = 0;
    MovFillFromAram(mram->size);
}

// .text:0x800AFD4C size:0x264
// Moves the next DVD chunk into ARAM; once the whole file is there, primes MRAM.
BOOL fn_800AFD4C(void) {
    MovAramRing* aram = &lbl_803C79D4;
    u32 len;

    if (aram->full) {
        return TRUE;
    }
    if (aram->size > aram->totalIn + 0x4000) {
        len = 0x4000;
    } else {
        len = aram->size - aram->totalIn;
    }
    MovStoreToAram(len);
    if (lbl_803C79D4.totalIn >= aram->size) {
        MovFillFromAram(lbl_803C7A00.size);
        (void)lbl_803C79D4.totalIn; // leftover read (debug print compiled out?)
        fn_800A6C80();
        while (MOV_DVD_DONE() != 1) {}
        aram->full = TRUE;
        return TRUE;
    }
    return TRUE;
}

// fn_800AFFB0, size:0x10
BOOL fn_800AFFB0(void) {
    return lbl_803C79D4.full;
}

// fn_800AFFC0, size:0x48
void fn_800AFFC0(u32 count) {
    MovMramRing* ring = &lbl_803C7A00;
    u8* position = ring->readPtr + count;
    ring->readPtr = position;
    if (position >= ring->end) {
        ring->readPtr = position - ring->size;
    }
    ring->filled -= count;
    ring->consumed += count;
}

// .text:0x800B0008 size:0x12C
BOOL fn_800B0008(u32 len) {
    MovMramRing* mram = &lbl_803C7A00;
    u32 first;
    u32 second;
    u8* wrap;

    len = (u32)OSRoundUp32B(len);
    if (mram->filled >= mram->size) {
        return TRUE;
    }
    if (mram->writePtr + len > mram->end) {
        first = (u32)(mram->end - mram->writePtr);
        wrap = mram->start;
        second = len - first;
    } else {
        first = len;
        wrap = NULL;
        second = 0;
    }
    fn_800B0230(mram->writePtr, first);
    while (lbl_803C79D4.busy) {}
    if (second != 0) {
        fn_800B0230(wrap, second);
        while (lbl_803C79D4.busy) {}
    }
    if (mram->writePtr + len < mram->end) {
        mram->writePtr += first;
    } else {
        mram->writePtr = mram->start + second;
    }
    mram->filled += len;
    if (lbl_803C79D4.totalOut > lbl_803CC1AC) {
        memset(mram->writePtr - (lbl_803C79D4.totalOut - lbl_803CC1AC), 0, lbl_803C79D4.totalOut - lbl_803CC1AC);
    }
    return TRUE;
}

// .text:0x800B0134 size:0xFC
BOOL fn_800B0134(u32 len) {
    u8* cur;
    u32 first;
    u32 second;
    u8* src;
    u8* wrap;
    BOOL intr;

    while (lbl_803C6CF8.buffered < len) {}
    intr = OSDisableInterrupts();
    cur = lbl_803C6CF8.readPos;
    if (cur + len < lbl_803C7A00.dvdBufStart + lbl_803C7A00.dvdBufSize) {
        src = cur;
        first = len;
        wrap = NULL;
        second = 0;
    } else {
        first = (u32)(lbl_803C7A00.dvdBufStart + lbl_803C7A00.dvdBufSize - cur);
        src = cur;
        wrap = lbl_803C7A00.dvdBufStart;
        second = len - first;
    }
    OSRestoreInterrupts(intr);
    if (len >= first) {
        fn_800B03F4(src, len);
    } else {
        fn_800B03F4(src, first);
        while (lbl_803C79D4.busy) {}
        fn_800B03F4(wrap, second);
    }
    while (lbl_803C79D4.busy) {}
    if (len != 0) {
        fn_800A6D10(len);
    }
    return TRUE;
}

// NONMATCHING 87%: register allocation (original keeps dst+first in its own saved reg, r27..r31 stmw)
#if NONMATCHING
// .text:0x800B0230 size:0x160
// Starts an ARAM -> MRAM transfer of len bytes from the ARAM read position.
void fn_800B0230(u8* dst, u32 len) {
    MovAramRing* aram = &lbl_803C79D4;
    u32 first;
    u32 second;
    u32 endPos;

    if (len == 0) {
        return;
    }
    endPos = aram->readPos + len;
    if (endPos > aram->end) {
        first = aram->end - aram->readPos;
        second = len - first;
    } else {
        first = len;
        second = 0;
    }
    if (second != 0) {
        endPos = aram->start + second;
    }
    if ((aram->writePos > aram->readPos && endPos > aram->writePos) ||
        (aram->writePos < aram->readPos && endPos > aram->writePos && second != 0)) {
        aram->busy = 3;
        return;
    }
    aram->readLen = len;
    aram->busy = 2;
    DCInvalidateRange(dst, first);
    ARQPostRequest(&lbl_803C78C4[0], 0, ARQ_TYPE_ARAM_TO_MRAM, ARQ_PRIORITY_HIGH, aram->readPos, (uintptr_t)dst, first, fn_800B0390);
    DCInvalidateRange(dst, first);
    if (second != 0) {
        while (aram->busy) {}
        aram->busy = 2;
        DCInvalidateRange(dst + first, second);
        ARQPostRequest(&lbl_803C78C4[1], 0, ARQ_TYPE_ARAM_TO_MRAM, ARQ_PRIORITY_HIGH, aram->start, (uintptr_t)(dst + first), second, fn_800B0390);
        DCInvalidateRange(dst + first, second);
    }
}
#endif

// .text:0x800B0390 size:0x64
void fn_800B0390(uintptr_t request) { // ARQCallback
    MovAramRing* aram = &lbl_803C79D4;
    u32 pos = aram->readPos + aram->readLen;
    aram->readPos = pos;
    if (pos >= aram->end) {
        aram->readPos = pos - aram->size;
    }
    {
        MovAramRing* r = &lbl_803C79D4;
        r->used -= aram->readLen;
        r->totalOut += aram->readLen;
        r->busy = 0;
    }
}

// .text:0x800B03F4 size:0x18C
// Starts an MRAM -> ARAM transfer of len bytes to the ARAM write position.
void fn_800B03F4(u8* src, u32 len) {
    MovAramRing* aram = &lbl_803C79D4;
    u32 first;
    u32 second;
    u32 endPos;

    if (aram->writePos + len > aram->end) {
        first = aram->end - aram->writePos;
        second = len - first;
    } else {
        first = len;
        second = 0;
    }
    if (second != 0) {
        endPos = aram->start + second;
    } else {
        endPos = aram->writePos + len;
    }
    if ((aram->writePos > aram->readPos && endPos > aram->readPos && second != 0) ||
        (aram->writePos < aram->readPos && endPos > aram->readPos)) {
        aram->busy = 3;
        return;
    }
    if (lbl_803C79D4.used > lbl_803C79D4.size) {
        for (;;) {}
    }
    lbl_803CC1A8++;
    aram->writeLen = len;
    aram->busy = 1;
    DCFlushRangeNoSync(src, first);
    ARQPostRequest(&lbl_803C7994[0], 0, ARQ_TYPE_MRAM_TO_ARAM, ARQ_PRIORITY_HIGH, (uintptr_t)src, aram->writePos, first, fn_800B0580);
    if (second != 0) {
        while (aram->busy) {}
        aram->busy = 1;
        DCFlushRangeNoSync(src + first, second);
        ARQPostRequest(&lbl_803C7994[1], 0, ARQ_TYPE_MRAM_TO_ARAM, ARQ_PRIORITY_HIGH, (uintptr_t)src + first, aram->start, second, fn_800B0580);
    }
}

// .text:0x800B0580 size:0x64
void fn_800B0580(uintptr_t request) { // ARQCallback
    MovAramRing* aram = &lbl_803C79D4;
    u32 pos = aram->writePos + aram->writeLen;
    aram->writePos = pos;
    if (pos >= aram->end) {
        aram->writePos = pos - aram->size;
    }
    {
        MovAramRing* r = &lbl_803C79D4;
        r->totalIn += aram->writeLen;
        r->used += aram->writeLen;
        r->busy = 0;
    }
}

// .text:0x800B05E4 size:0x140
// Sets up the ARAM ring (aramSize, or all free ARAM when -1) and an MRAM ring of mramSize.
void fn_800B05E4(s32 aramSize, u32 mramSize) {
    MovAramRing* aram = &lbl_803C79D4;
    MovMramRing* mram = &lbl_803C7A00;

    lbl_803CC1A8 = 0;
    memset(aram, 0, sizeof(MovAramRing));
    if (aramSize == -1) {
        aram->size = (lbl_803CC1AC < data_803C6780.tempValue) ? lbl_803CC1AC : data_803C6780.tempValue;
    } else {
        aram->size = (lbl_803CC1AC < (u32)aramSize) ? lbl_803CC1AC : (u32)aramSize;
    }
    aram->size = (u32)OSRoundUp32B(aram->size);
    aram->start = fn_800A6418(aram->size);
    aram->readPos = aram->writePos = aram->start;
    aram->end = aram->start + aram->size;
    ARQSetChunkSize(0x1000);
    ARQFlushQueue();
    mramSize = (u32)OSRoundUp32B(mramSize);
    mram->dvdBufSize = lbl_803C6CF8.ringSize;
    mram->dvdBufStart = lbl_803C6CF8.bufEnd - lbl_803C6CF8.ringSize;
    mram->dvdBufSize = lbl_803C6CF8.ringSize;
    mram->start = _OSAllocFromHeap(0x20, mramSize);
    mram->end = mram->start + mramSize;
    mram->readPtr = mram->writePtr = mram->start;
    mram->size = mramSize;
    mram->filled = 0;
    mram->consumed = 0;
}

// ---- Data (initialisers generated from the original DOL) ----

// .data 0x801101C0..0x801112E0
u16 lbl_801101C0[128] = {
    0, 2, 8, 18, 32, 50, 73, 99,
    130, 164, 203, 245, 292, 343, 398, 457,
    520, 587, 658, 733, 812, 895, 983, 1074,
    1170, 1269, 1373, 1481, 1592, 1708, 1828, 1952,
    2080, 2212, 2348, 2488, 2632, 2781, 2933, 3090,
    3250, 3415, 3583, 3756, 3933, 4114, 4298, 4487,
    4680, 4877, 5079, 5284, 5493, 5706, 5924, 6145,
    6371, 6600, 6834, 7072, 7313, 7559, 7809, 8063,
    8321, 8583, 8849, 9119, 9394, 9672, 9954, 10241,
    10531, 10826, 11125, 11427, 11734, 12045, 12360, 12679,
    13002, 13329, 13660, 13995, 14335, 14678, 15025, 15377,
    15732, 16092, 16456, 16823, 17195, 17571, 17951, 18335,
    18723, 19115, 19511, 19911, 20316, 20724, 21136, 21553,
    21974, 22398, 22827, 23260, 23696, 24137, 24582, 25031,
    25484, 25941, 26402, 26868, 27337, 27810, 28288, 28769,
    29255, 29744, 30238, 30736, 31238, 31744, 32254, 32768,
};
YuvTable lbl_801102C0 = {
    {
        182, 186, 191, 195, 200, 205, 209, 214,
        219, 223, 228, 233, 237, 242, 247, 251,
        256, 261, 265, 270, 275, 279, 284, 289,
        293, 298, 303, 307, 312, 317, 321, 326,
        330, 335, 340, 344, 349, 354, 358, 363,
        368, 372, 377, 382, 386, 391, 396, 400,
        405, 410, 414, 419, 424, 428, 433, 438,
        442, 447, 452, 456, 461, 466, 470, 475,
        479, 484, 489, 493, 498, 503, 507, 512,
        517, 521, 526, 531, 535, 540, 545, 549,
        554, 559, 563, 568, 573, 577, 582, 587,
        591, 596, 601, 605, 610, 615, 619, 624,
        628, 633, 638, 642, 647, 652, 656, 661,
        666, 670, 675, 680, 684, 689, 694, 698,
        703, 708, 712, 717, 722, 726, 731, 736,
        740, 745, 750, 754, 759, 764, 768, 773,
        777, 782, 787, 791, 796, 801, 805, 810,
        815, 819, 824, 829, 833, 838, 843, 847,
        852, 857, 861, 866, 871, 875, 880, 885,
        889, 894, 899, 903, 908, 912, 917, 922,
        926, 931, 936, 940, 945, 950, 954, 959,
        964, 968, 973, 978, 982, 987, 992, 996,
        1001, 1006, 1010, 1015, 1020, 1024, 1029, 1034,
        1038, 1043, 1048, 1052, 1057, 1061, 1066, 1071,
        1075, 1080, 1085, 1089, 1094, 1099, 1103, 1108,
        1113, 1117, 1122, 1127, 1131, 1136, 1141, 1145,
        1150, 1155, 1159, 1164, 1169, 1173, 1178, 1183,
        1187, 1192, 1197, 1201, 1206, 1210, 1215, 1220,
        1224, 1229, 1234, 1238, 1243, 1248, 1252, 1257,
        1262, 1266, 1271, 1276, 1280, 1285, 1290, 1294,
        1299, 1304, 1308, 1313, 1318, 1322, 1327, 1332,
        1336, 1341, 1346, 1350, 1355, 1359, 1364, 1369,
    },
    {
        -817, -811, -804, -798, -792, -785, -779, -772,
        -766, -760, -753, -747, -741, -734, -728, -721,
        -715, -709, -702, -696, -689, -683, -677, -670,
        -664, -658, -651, -645, -638, -632, -626, -619,
        -613, -606, -600, -594, -587, -581, -575, -568,
        -562, -555, -549, -543, -536, -530, -523, -517,
        -511, -504, -498, -492, -485, -479, -472, -466,
        -460, -453, -447, -440, -434, -428, -421, -415,
        -409, -402, -396, -389, -383, -377, -370, -364,
        -358, -351, -345, -338, -332, -326, -319, -313,
        -306, -300, -294, -287, -281, -275, -268, -262,
        -255, -249, -243, -236, -230, -223, -217, -211,
        -204, -198, -192, -185, -179, -172, -166, -160,
        -153, -147, -140, -134, -128, -121, -115, -109,
        -102, -96, -89, -83, -77, -70, -64, -57,
        -51, -45, -38, -32, -26, -19, -13, -6,
        0, 6, 13, 19, 26, 32, 38, 45,
        51, 57, 64, 70, 77, 83, 89, 96,
        102, 109, 115, 121, 128, 134, 140, 147,
        153, 160, 166, 172, 179, 185, 192, 198,
        204, 211, 217, 223, 230, 236, 243, 249,
        255, 262, 268, 275, 281, 287, 294, 300,
        306, 313, 319, 326, 332, 338, 345, 351,
        358, 364, 370, 377, 383, 389, 396, 402,
        409, 415, 421, 428, 434, 440, 447, 453,
        460, 466, 472, 479, 485, 492, 498, 504,
        511, 517, 523, 530, 536, 543, 549, 555,
        562, 568, 575, 581, 587, 594, 600, 606,
        613, 619, 626, 632, 638, 645, 651, 658,
        664, 670, 677, 683, 689, 696, 702, 709,
        715, 721, 728, 734, 741, 747, 753, 760,
        766, 772, 779, 785, 792, 798, 804, 811,
    },
    {
        416, 413, 410, 407, 403, 400, 397, 393,
        390, 387, 384, 380, 377, 374, 371, 367,
        364, 361, 358, 354, 351, 348, 345, 341,
        338, 335, 332, 328, 325, 322, 319, 315,
        312, 309, 306, 302, 299, 296, 293, 289,
        286, 283, 280, 276, 273, 270, 267, 263,
        260, 257, 254, 250, 247, 244, 241, 237,
        234, 231, 228, 224, 221, 218, 215, 211,
        208, 205, 202, 198, 195, 192, 189, 185,
        182, 179, 176, 172, 169, 166, 163, 159,
        156, 153, 150, 146, 143, 140, 137, 133,
        130, 127, 124, 120, 117, 114, 111, 107,
        104, 101, 98, 94, 91, 88, 85, 81,
        78, 75, 72, 68, 65, 62, 59, 55,
        52, 49, 46, 42, 39, 36, 33, 29,
        26, 23, 20, 16, 13, 10, 7, 3,
        0, -3, -7, -10, -13, -16, -20, -23,
        -26, -29, -33, -36, -39, -42, -46, -49,
        -52, -55, -59, -62, -65, -68, -72, -75,
        -78, -81, -85, -88, -91, -94, -98, -101,
        -104, -107, -111, -114, -117, -120, -124, -127,
        -130, -133, -137, -140, -143, -146, -150, -153,
        -156, -159, -163, -166, -169, -172, -176, -179,
        -182, -185, -189, -192, -195, -198, -202, -205,
        -208, -211, -215, -218, -221, -224, -228, -231,
        -234, -237, -241, -244, -247, -250, -254, -257,
        -260, -263, -267, -270, -273, -276, -280, -283,
        -286, -289, -293, -296, -299, -302, -306, -309,
        -312, -315, -319, -322, -325, -328, -332, -335,
        -338, -341, -345, -348, -351, -354, -358, -361,
        -364, -367, -371, -374, -377, -380, -384, -387,
        -390, -393, -397, -400, -403, -407, -410, -413,
    },
    {
        200, 199, 197, 196, 194, 192, 191, 189,
        188, 186, 185, 183, 181, 180, 178, 177,
        175, 174, 172, 170, 169, 167, 166, 164,
        163, 161, 160, 158, 156, 155, 153, 152,
        150, 149, 147, 145, 144, 142, 141, 139,
        138, 136, 135, 133, 131, 130, 128, 127,
        125, 124, 122, 120, 119, 117, 116, 114,
        113, 111, 109, 108, 106, 105, 103, 102,
        100, 99, 97, 95, 94, 92, 91, 89,
        88, 86, 84, 83, 81, 80, 78, 77,
        75, 74, 72, 70, 69, 67, 66, 64,
        63, 61, 59, 58, 56, 55, 53, 52,
        50, 48, 47, 45, 44, 42, 41, 39,
        38, 36, 34, 33, 31, 30, 28, 27,
        25, 23, 22, 20, 19, 17, 16, 14,
        13, 11, 9, 8, 6, 5, 3, 2,
        0, -2, -3, -5, -6, -8, -9, -11,
        -13, -14, -16, -17, -19, -20, -22, -23,
        -25, -27, -28, -30, -31, -33, -34, -36,
        -38, -39, -41, -42, -44, -45, -47, -48,
        -50, -52, -53, -55, -56, -58, -59, -61,
        -63, -64, -66, -67, -69, -70, -72, -74,
        -75, -77, -78, -80, -81, -83, -84, -86,
        -88, -89, -91, -92, -94, -95, -97, -99,
        -100, -102, -103, -105, -106, -108, -109, -111,
        -113, -114, -116, -117, -119, -120, -122, -124,
        -125, -127, -128, -130, -131, -133, -135, -136,
        -138, -139, -141, -142, -144, -145, -147, -149,
        -150, -152, -153, -155, -156, -158, -160, -161,
        -163, -164, -166, -167, -169, -170, -172, -174,
        -175, -177, -178, -180, -181, -183, -185, -186,
        -188, -189, -191, -192, -194, -196, -197, -199,
    },
    {
        -1033, -1025, -1017, -1009, -1001, -993, -985, -977,
        -969, -961, -952, -944, -936, -928, -920, -912,
        -904, -896, -888, -880, -872, -864, -856, -848,
        -839, -831, -823, -815, -807, -799, -791, -783,
        -775, -767, -759, -751, -743, -735, -726, -718,
        -710, -702, -694, -686, -678, -670, -662, -654,
        -646, -638, -630, -622, -613, -605, -597, -589,
        -581, -573, -565, -557, -549, -541, -533, -525,
        -517, -509, -500, -492, -484, -476, -468, -460,
        -452, -444, -436, -428, -420, -412, -404, -396,
        -387, -379, -371, -363, -355, -347, -339, -331,
        -323, -315, -307, -299, -291, -283, -274, -266,
        -258, -250, -242, -234, -226, -218, -210, -202,
        -194, -186, -178, -170, -161, -153, -145, -137,
        -129, -121, -113, -105, -97, -89, -81, -73,
        -65, -57, -48, -40, -32, -24, -16, -8,
        0, 8, 16, 24, 32, 40, 48, 57,
        65, 73, 81, 89, 97, 105, 113, 121,
        129, 137, 145, 153, 161, 170, 178, 186,
        194, 202, 210, 218, 226, 234, 242, 250,
        258, 266, 274, 283, 291, 299, 307, 315,
        323, 331, 339, 347, 355, 363, 371, 379,
        387, 396, 404, 412, 420, 428, 436, 444,
        452, 460, 468, 476, 484, 492, 500, 509,
        517, 525, 533, 541, 549, 557, 565, 573,
        581, 589, 597, 605, 613, 622, 630, 638,
        646, 654, 662, 670, 678, 686, 694, 702,
        710, 718, 726, 735, 743, 751, 759, 767,
        775, 783, 791, 799, 807, 815, 823, 831,
        839, 848, 856, 864, 872, 880, 888, 896,
        904, 912, 920, 928, 936, 944, 952, 961,
        969, 977, 985, 993, 1001, 1009, 1017, 1025,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4,
        4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8,
        8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12,
        12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 16, 16,
        16, 16, 17, 17, 17, 17, 18, 18, 18, 18, 19, 19, 19, 19, 20, 20,
        20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 23, 23, 24, 24,
        24, 24, 25, 25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 27, 28, 28,
        28, 28, 29, 29, 29, 29, 30, 30, 30, 30, 31, 31, 31, 31, 32, 32,
        32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35, 35, 35, 36, 36,
        36, 36, 37, 37, 37, 37, 38, 38, 38, 38, 39, 39, 39, 39, 40, 40,
        40, 40, 41, 41, 41, 41, 42, 42, 42, 42, 43, 43, 43, 43, 44, 44,
        44, 44, 45, 45, 45, 45, 46, 46, 46, 46, 47, 47, 47, 47, 48, 48,
        48, 48, 49, 49, 49, 49, 50, 50, 50, 50, 51, 51, 51, 51, 52, 52,
        52, 52, 53, 53, 53, 53, 54, 54, 54, 54, 55, 55, 55, 55, 56, 56,
        56, 56, 57, 57, 57, 57, 58, 58, 58, 58, 59, 59, 59, 59, 60, 60,
        60, 60, 61, 61, 61, 61, 62, 62, 62, 62, 63, 63, 63, 63, 64, 64,
        64, 64, 65, 65, 65, 65, 66, 66, 66, 66, 67, 67, 67, 67, 68, 68,
        68, 68, 69, 69, 69, 69, 70, 70, 70, 70, 71, 71, 71, 71, 72, 72,
        72, 72, 73, 73, 73, 73, 74, 74, 74, 74, 75, 75, 75, 75, 76, 76,
        76, 76, 77, 77, 77, 77, 78, 78, 78, 78, 79, 79, 79, 79, 80, 80,
        80, 80, 81, 81, 81, 81, 82, 82, 82, 82, 83, 83, 83, 83, 84, 84,
        84, 84, 85, 85, 85, 85, 86, 86, 86, 86, 87, 87, 87, 87, 88, 88,
        88, 88, 89, 89, 89, 89, 90, 90, 90, 90, 91, 91, 91, 91, 92, 92,
        92, 92, 93, 93, 93, 93, 94, 94, 94, 94, 95, 95, 95, 95, 96, 96,
        96, 96, 97, 97, 97, 97, 98, 98, 98, 98, 99, 99, 99, 99, 100, 100,
        100, 100, 101, 101, 101, 101, 102, 102, 102, 102, 103, 103, 103, 103, 104, 104,
        104, 104, 105, 105, 105, 105, 106, 106, 106, 106, 107, 107, 107, 107, 108, 108,
        108, 108, 109, 109, 109, 109, 110, 110, 110, 110, 111, 111, 111, 111, 112, 112,
        112, 112, 113, 113, 113, 113, 114, 114, 114, 114, 115, 115, 115, 115, 116, 116,
        116, 116, 117, 117, 117, 117, 118, 118, 118, 118, 119, 119, 119, 119, 120, 120,
        120, 120, 121, 121, 121, 121, 122, 122, 122, 122, 123, 123, 123, 123, 124, 124,
        124, 124, 125, 125, 125, 125, 126, 126, 126, 126, 127, 127, 127, 127, 128, 128,
        128, 128, 129, 129, 129, 129, 130, 130, 130, 130, 131, 131, 131, 131, 132, 132,
        132, 132, 133, 133, 133, 133, 134, 134, 134, 134, 135, 135, 135, 135, 136, 136,
        136, 136, 137, 137, 137, 137, 138, 138, 138, 138, 139, 139, 139, 139, 140, 140,
        140, 140, 141, 141, 141, 141, 142, 142, 142, 142, 143, 143, 143, 143, 144, 144,
        144, 144, 145, 145, 145, 145, 146, 146, 146, 146, 147, 147, 147, 147, 148, 148,
        148, 148, 149, 149, 149, 149, 150, 150, 150, 150, 151, 151, 151, 151, 152, 152,
        152, 152, 153, 153, 153, 153, 154, 154, 154, 154, 155, 155, 155, 155, 156, 156,
        156, 156, 157, 157, 157, 157, 158, 158, 158, 158, 159, 159, 159, 159, 160, 160,
        160, 160, 161, 161, 161, 161, 162, 162, 162, 162, 163, 163, 163, 163, 164, 164,
        164, 164, 165, 165, 165, 165, 166, 166, 166, 166, 167, 167, 167, 167, 168, 168,
        168, 168, 169, 169, 169, 169, 170, 170, 170, 170, 171, 171, 171, 171, 172, 172,
        172, 172, 173, 173, 173, 173, 174, 174, 174, 174, 175, 175, 175, 175, 176, 176,
        176, 176, 177, 177, 177, 177, 178, 178, 178, 178, 179, 179, 179, 179, 180, 180,
        180, 180, 181, 181, 181, 181, 182, 182, 182, 182, 183, 183, 183, 183, 184, 184,
        184, 184, 185, 185, 185, 185, 186, 186, 186, 186, 187, 187, 187, 187, 188, 188,
        188, 188, 189, 189, 189, 189, 190, 190, 190, 190, 191, 191, 191, 191, 192, 192,
        192, 192, 193, 193, 193, 193, 194, 194, 194, 194, 195, 195, 195, 195, 196, 196,
        196, 196, 197, 197, 197, 197, 198, 198, 198, 198, 199, 199, 199, 199, 200, 200,
        200, 200, 201, 201, 201, 201, 202, 202, 202, 202, 203, 203, 203, 203, 204, 204,
        204, 204, 205, 205, 205, 205, 206, 206, 206, 206, 207, 207, 207, 207, 208, 208,
        208, 208, 209, 209, 209, 209, 210, 210, 210, 210, 211, 211, 211, 211, 212, 212,
        212, 212, 213, 213, 213, 213, 214, 214, 214, 214, 215, 215, 215, 215, 216, 216,
        216, 216, 217, 217, 217, 217, 218, 218, 218, 218, 219, 219, 219, 219, 220, 220,
        220, 220, 221, 221, 221, 221, 222, 222, 222, 222, 223, 223, 223, 223, 224, 224,
        224, 224, 225, 225, 225, 225, 226, 226, 226, 226, 227, 227, 227, 227, 228, 228,
        228, 228, 229, 229, 229, 229, 230, 230, 230, 230, 231, 231, 231, 231, 232, 232,
        232, 232, 233, 233, 233, 233, 234, 234, 234, 234, 235, 235, 235, 235, 236, 236,
        236, 236, 237, 237, 237, 237, 238, 238, 238, 238, 239, 239, 239, 239, 240, 240,
        240, 240, 241, 241, 241, 241, 242, 242, 242, 242, 243, 243, 243, 243, 244, 244,
        244, 244, 245, 245, 245, 245, 246, 246, 246, 246, 247, 247, 247, 247, 248, 248,
        248, 248, 249, 249, 249, 249, 250, 250, 250, 250, 251, 251, 251, 251, 252, 252,
        252, 252, 253, 253, 253, 253, 254, 254, 254, 254, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    },
};
u8 lbl_801112C0[0x20] = {128, 0, 4, 0, 0, 0, 1, 1, 0, 2, 1, 1, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// .bss 0x802F93A0..0x802FE8A0 (MWCC lays these out in reverse definition order)
MovQueue lbl_802FB870;
MovThreads lbl_802FB220;
Mtx44 lbl_802FB1E0;
s16 lbl_802F93E0[2][0x780];
s16 lbl_802F93C0[16];
s16 lbl_802F93A0[16];

// .sdata 0x803CBAE0..0x803CBB08
u8 lbl_803CBAE0 = 100;
u16 lbl_803CBAE2 = 160;
u16 lbl_803CBAE4 = 640;
#ifdef TARGET_PC // the same fields, by name (the structs hold pointers)
u8 **lbl_803CBAE8[2] = {&lbl_803C6CF8.readPos, &lbl_803C7A00.readPtr};
u8 **lbl_803CBAF0[2] = {&lbl_803C6CF8.readPos, &lbl_803C7A00.writePtr};
u32 *lbl_803CBAF8[2] = {(u32*)&lbl_803C6CF8.buffered, &lbl_803C7A00.filled};
#else
u8 **lbl_803CBAE8[2] = {(void*)((u8*)&lbl_803C6CF8 + 0x708), (void*)((u8*)&lbl_803C7A00 + 0x10)};
u8 **lbl_803CBAF0[2] = {(void*)((u8*)&lbl_803C6CF8 + 0x708), (void*)((u8*)&lbl_803C7A00 + 0x14)};
u32 *lbl_803CBAF8[2] = {(void*)((u8*)&lbl_803C6CF8 + 0x710), (void*)((u8*)&lbl_803C7A00 + 0x1C)};
#endif
s16 *lbl_803CBB00[2] = {lbl_802F93C0, lbl_802F93A0};

// .sbss 0x803CC174..0x803CC1B0 (MWCC lays these out in reverse definition order)
u32 lbl_803CC1AC;
u8 lbl_803CC1A8;
u32 lbl_803CC1A4;
u32 lbl_803CC1A0;
s32 lbl_803CC19C;
u32 lbl_803CC198; // type from another unit
u8 lbl_803CC194;
void (*lbl_803CC190)(u32 frame);
AIDCallback lbl_803CC18C;
u32 lbl_803CC188;
f32 lbl_803CC184;
u8 lbl_803CC182;
u8 lbl_803CC181;
u8 lbl_803CC180;
u8 lbl_803CC17F;
// lbl_803CC17E is defined above
u8 lbl_803CC17D;
u8 lbl_803CC17C;
u32 lbl_803CC178;
u8* lbl_803CC174;

// ---- Data ----

// .data 0x801112E0: the two alternating frame-draw callbacks queued by file_800A7C08
// (DrawCallbackNode in main/file_800A7C08.h: a link word, then the function).
typedef struct MovDrawNode {
    /*0x0*/ uintptr_t link; // pointer-sized on PC, like DrawLink
    /*0x4*/ void (*func)(void* node);
} MovDrawNode;
MovDrawNode lbl_801112E0[2] = {
    {0, fn_800ADD70},
    {0, fn_800ADD70},
};

// .sdata 0x803CBB08: frame converters, indexed by the movie's pixel format.
void (*lbl_803CBB08[2])(u8* src, u8* dst, s32 width, s32 height) = {YUV2RGB_, YUV2RGB};
