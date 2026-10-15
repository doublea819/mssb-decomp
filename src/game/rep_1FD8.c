#include "game/rep_1FD8.h"
#define REP_HEADER_FN repHeader_1FD8
#include "header_rep_inline.h"

#include "static/UnknownHomes_Static.h"
#include "game/UnknownHomes_Game.h"
#include "main/scene_task.h"    // SceneTask
#include "main/screenfx.h"      // ScreenFx lbl_803C5090
#include "main/file_8000F150.h" // LayoutSlot lbl_80371C30
#include "main/file_80011640.h" // CharMgr lbl_8036E548
#include "main/file_80022DAC.h" // StadiumLight, fn_80023B90
#include "C3/geoPalette.h"      // DODisplayObj, DisplayStateList
#include "Dolphin/vec.h"
#include "Dolphin/mtxext.h"
#include "Dolphin/GX/GXFifo.h"
#include "main/file_80024184.h"
#include "main/file_800BD8C4.h"
#include "C3/control.h"
#include "game/rep_D0.h"
typedef struct C4724P {
    struct C4724P* next;
    f32 x, y, z;
    f32 vx, vy, vz;
    f32 f1C, f20, f24;
    u8 pad28[0x38 - 0x28];
    f32 f38, f3C;
    u8 a40, a41, a42;
    u8 a43;
    u8 pad44[4];
    s16 s48;
    s16 s4A;
    u8 pad4C[1];
    u8 f4D;
    u8 f4E;
    u8 f4F;
    u8 f50;
} C4724P;
// Particle emitter (Emitter in main/file_800263FC.h), the fields these effects use.
typedef struct C4724Hdr { void* prev; void* next; void* update; C4724P* head; void* tex; u16 f14; u8 pad16[2]; Vec* f18; u8 pad1C[4]; void* f20; s32 f24; } C4724Hdr;
extern const u8 lbl_3_rodata_2028[];
extern const f32 lbl_3_rodata_20FC;
extern const f64 lbl_3_rodata_2100;
extern const f64 lbl_3_rodata_2110;
extern const f64 lbl_3_rodata_2120;
extern const f32 lbl_3_rodata_2108;
extern const f32 lbl_3_rodata_20D4;
extern const f32 lbl_3_rodata_2158;
extern const f32 lbl_3_rodata_215C;
extern const f32 lbl_3_rodata_2160[];
extern const f32 lbl_3_rodata_2164;
extern const f32 lbl_3_rodata_2128;
extern f64 sin(f64);
extern f64 cos(f64);
extern const f64 lbl_3_rodata_2118;
extern const f64 lbl_3_rodata_2130;
extern const f64 lbl_3_rodata_2140;
extern const f32 lbl_3_rodata_2138;
extern void fn_3_C2644(void);
extern const f32 lbl_3_rodata_213C;
// lbl_3_bss_9D80: this unit's state block (9D81/9D82/9DE0/9DE4/9F0C are views into it).
typedef struct {
    u8 pad0;
    u8 f1; // 9D81
    u8 f2; // 9D82: stop fn_3_C5DDC
    u8 pad3[0x60 - 3];
    u8 cStart;     // 9DE0: first object of group C (lbl_3_data_17704)
    u8 cCount;     // 9DE1
    u8 sprayStart; // 9DE2: first object fn_3_C5DDC watches (group B, lbl_3_data_175FC)
    u8 sprayCount; // 9DE3
    u8 aStart;     // 9DE4: first object of group A (lbl_3_data_17514)
    u8 aCount;     // 9DE5
    u8 pad66;
    u8 f67;
    Vec pos[8];
    u8 state[8];
    SceneTask* fD0; // layout task of the markers
    ShapeAnimPlayer animD4;  // anim player (fn_80025FFC)
    ShapeAnimPlayer anim130; // anim player of the group B objects
    void* tex; // 9F0C
} C3C2CBss;
extern C3C2CBss lbl_3_bss_9D80;
#ifdef TARGET_PC
// The 9D8x-9F0C symbols are fields of lbl_3_bss_9D80: the same bytes on GameCube,
// separate objects on PC.
#define lbl_3_bss_9D81 (lbl_3_bss_9D80.f1)
#define lbl_3_bss_9D82 (lbl_3_bss_9D80.f2)
#define lbl_3_bss_9DE0 (&lbl_3_bss_9D80.cStart)
#define lbl_3_bss_9DE4 (&lbl_3_bss_9D80.aStart)
#define lbl_3_bss_9DE7 (lbl_3_bss_9D80.f67)
#define lbl_3_bss_9DE8 (lbl_3_bss_9D80.pos)
#define lbl_3_bss_9E48 (lbl_3_bss_9D80.state)
#define lbl_3_bss_9E50 (&lbl_3_bss_9D80.fD0)
#define lbl_3_bss_9F0C (lbl_3_bss_9D80.tex)
#endif

#ifndef TARGET_PC
extern u8 lbl_3_bss_9D81;
#endif
extern u32 lbl_3_bss_9D8C;
extern const f32 lbl_3_rodata_214C;
extern void fn_800528B4(void);
extern int rand(void);
extern TexImage* lbl_3_bss_9D98; // 3 textures of the fn_3_C1C18 effect
extern C42A4Bss lbl_3_common_bss_350E4;
extern void fn_3_B8184(void* pp, void* cam);
extern void fn_3_B828C(void*);
extern void fn_800BF058(void*);
extern void fn_800BDF70(void*);
extern u32 lbl_3_bss_9D84;
extern void* fn_80033A24(void*, int, int, int, int, u8); // Emitter* (update, priority, unk14, n, strict, type)

extern u32 lbl_3_bss_9D9C;
extern u8 lbl_3_data_8404[];
extern u8 lbl_3_data_84B8[];
extern u16 lbl_3_data_81DC[];
extern u32 sndFXStartEx(int, u8, u8, u8);
extern u32 sndFXCtrl(int, int, u8);
extern const f32 lbl_3_rodata_20F4;
extern const f32 lbl_3_rodata_20F8;
extern u32 fn_8005268C(void);
// Current camera's matrices (fn_80052734(fn_8005268C()), main/file_8004C5F8).
typedef struct CamMtx {
    Mtx44 proj;
    Mtx view;
} CamMtx;
extern CamMtx* fn_80052734(s32 index);
extern Vec lbl_3_rodata_2080;
extern f32 lbl_3_rodata_2178;
extern void* memset(void*, int, size_t);
extern void fn_3_25844(u32, int);
extern SceneTask* lbl_803CC1B8;
extern Control* lbl_3_bss_9D94;
typedef struct DspObj2 DspObj2;
struct DspObj2 {
    u8 pad0[0x14];
    void* w14;
    u8 pad18[0x4C];
    void* w64;
    void* w68;
    u8 pad6C[8];
    DspObj2* child;
    u8 pad78[4];
    void* w7C;
    u8 pad80[0x6C];
    void* wEC;
    u8 padF0[0x10];
    DspObj2* next;
};
extern void fn_8003A8A0(void* model, Mtx viewMtx, s32 unused);
extern u32 lbl_3_bss_9D88;
extern u16 lbl_3_data_177F0;
typedef struct Rep1FD8Ent {
    void* next;                           // draw-list link
    void (*draw)(struct Rep1FD8Ent* ent); // fn_3_C1C18
    Mtx m;
    void* w38;
} Rep1FD8Ent;
extern Rep1FD8Ent lbl_3_data_17804[];
extern u8 lbl_803CBBC0; // current frame buffer (0/1)
#ifndef TARGET_PC
extern Vec lbl_3_bss_9DE8[];
#endif
#ifndef TARGET_PC
extern u8 lbl_3_bss_9E48[];
#endif
#ifndef TARGET_PC
extern SceneTask* lbl_3_bss_9E50[];
#endif
extern void fn_800528C0(s16* sx, s16* sy, f32 x, f32 y, f32 z);
// A few matched callers evaluate the floats before the out pointers. On PPC the
// argument order makes no difference to the call, so the matching build calls
// through a float-first cast there; the port uses the real prototype.
#if NONMATCHING
#define fn_800528C0_xyz(x, y, z, sx, sy) fn_800528C0(sx, sy, x, y, z)
#else
#define fn_800528C0_xyz(x, y, z, sx, sy) ((void (*)(f32, f32, f32, s16*, s16*))fn_800528C0)(x, y, z, sx, sy)
#endif

// fn_3_C2244's task (queue node; data starts at 0x14)
typedef struct C2244Task {
#ifdef TARGET_PC
    SCENE_TASK_VIEW_HEAD // SceneTask head (main/scene_task.h)
    f32 pos[3];
#else
    /*0x00*/ u8 hdr[0x14];
    /*0x14*/ f32 pos[3];
#endif
    /*0x20*/ s16 f20[2]; // spin angle of the two extra quads
    /*0x24*/ u8 f24;
    /*0x25*/ u8 f25[2];
    /*0x27*/ u8 f27[2];
    /*0x29*/ u8 f29;
    /*0x2A*/ u8 f2A;
} C2244Task;
extern C2244Task* lbl_3_bss_9D90;
extern f32 lbl_3_data_1787C; // alpha scale of the first quad
extern void fn_800A7D4C(int, Rep1FD8Ent*);
#include "main/menu_globals.h" // SavedSettings
extern SavedSettings lbl_800E8754;
extern StadiumLightPos lbl_80367318;
// Per-stadium light row (lbl_800F7478, 0x2C bytes; same as main/file_800263FC.c).
typedef struct StadiumLightRow {
    StadiumLight light;
    u8 pad[0x2C - sizeof(StadiumLight)];
} StadiumLightRow;
extern StadiumLightRow lbl_800F7478[];
typedef struct PaddedStadiumLight {
    StadiumLight light;
    u8 pad[2];
} PaddedStadiumLight;
extern PaddedStadiumLight lbl_3_data_177F8;
extern s32 lbl_3_data_177F4;
extern ScreenFx lbl_803C5090;
extern void fn_800BEBCC(u8 index, Vec dir);
extern const f32 lbl_3_rodata_20F0;
extern void fn_3_CB7E8(f32, f32, f32);
extern f32 lbl_3_rodata_2150;
#ifndef TARGET_PC
extern void* lbl_3_bss_9F0C; // TexArchive*
#endif
extern void fn_80033620(void* emitter); // sets up drawing for the emitter

void fn_3_C1964(void) {
    lbl_3_bss_9D9C = 1;
}

void fn_3_C1974(u8* a) {
    SceneTask* p = fn_800B0A5C_insertQueue(fn_3_C2644, 4);
    p->_10 = 0;
    // TODO port: a is a loaded stadium file; its textures start at byte 0x3C4 (32-bit file layout).
    lbl_3_bss_9D98 = (TexImage*)(a + 0x3C4);
    lbl_3_bss_9D9C = 0;
}

// .text:0x000C19C8 size:0x250 mapped:0x80700A5C
extern s32 fn_3_B7FC8(s32 id, s32 kind);
extern s16 lbl_3_data_17880[];
// .data 0x00017508..0x00017898
f32 lbl_3_data_17508[3] = {1.0f, 3.0f, 5.0f};
StadPlace14 lbl_3_data_17514[11] = { // group A spots
    {-51.592f, -18.0f, 68.051f, 306.0f, 2, 1, 1, 2},
    {-43.569f, -18.0f, 76.869f, 314.0f, 2, 1, 1, 2},
    {-33.845f, -18.0f, 84.008f, 330.0f, 2, 1, 1, 2},
    {51.592f, -18.0f, 68.051f, 52.0f, 2, 1, 2, 2},
    {43.569f, -18.0f, 76.869f, 44.0f, 2, 1, 2, 2},
    {33.845f, -18.0f, 84.008f, 28.0f, 2, 1, 2, 2},
    {0.0f, 0.0f, 0.0f, 0.0f, 7, 0, 255, 7},
    {0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0},
    {0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0},
    {0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0},
    {0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0},
};
f32 lbl_3_data_175F0[3] = {0.06f, 0.07f, 0.08f};
StadPlace18 lbl_3_data_175FC[11] = { // group B spots
    {-48.0f, 5.5f, 25.0f, 0.0f, 3, 1, 1, 3, 295, 1},
    {-43.0f, 5.5f, 56.0f, 0.0f, 3, 1, 1, 3, 315, 90},
    {-10.0f, 5.5f, 77.0f, 0.0f, 3, 1, 2, 3, 180, 90},
    {10.0f, 5.5f, 77.0f, 0.0f, 3, 1, 2, 3, 270, 90},
    {45.0f, 5.5f, 23.0f, 0.0f, 3, 1, 3, 3, 245, 1},
    {43.0f, 5.5f, 56.0f, 0.0f, 3, 1, 3, 3, 135, 90},
    {0.0f, 0.0f, 0.0f, 0.0f, 7, 0, 255, 7, 0, 0},
    {0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0},
    {0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0},
    {0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0},
    {0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0},
};
StadPlaceGroupC lbl_3_data_17704 = { // group C spots
    {
        {-12.891f, -5.93f, 87.961f, 348.0f, 4, 1, 1, 6},
        {12.891f, -5.93f, 87.961f, 12.0f, 4, 1, 1, 6},
        {-23.0f, -0.02f, 72.0f, 0.0f, 5, 1, 2, 6},
        {-22.0f, -0.02f, 45.0f, 0.0f, 5, 1, 2, 6},
        {-50.0f, -0.02f, 38.0f, 0.0f, 5, 1, 2, 6},
        {23.0f, -0.02f, 72.0f, 0.0f, 5, 1, 3, 6},
        {22.0f, -0.02f, 45.0f, 0.0f, 5, 1, 3, 6},
        {50.0f, -0.02f, 38.0f, 0.0f, 5, 1, 3, 6},
        {0.0f, 0.0f, 0.0f, 0.0f, 7, 0, 255, 7},
        {0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0},
        {0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0},
    },
    {1, 2, 2, 2, 2, 2, 2, 6, 6, 6, 8, 9, 8, 9, 0, 0},
};
u16 lbl_3_data_177F0 = 4;
s32 lbl_3_data_177F4 = 2;
PaddedStadiumLight lbl_3_data_177F8 = {{200, 1426, 2152, 255, 255, 255}}; // light during the flash
Rep1FD8Ent lbl_3_data_17804[2] = {{NULL, fn_3_C1C18}, {NULL, fn_3_C1C18}};
f32 lbl_3_data_1787C = 0.7f;
s16 lbl_3_data_17880[12] = {106, -98, 220, 94, -87, 230, 120, -80, 212, 0, 0, 0};

void fn_3_C19C8(void) {
    s32 i;
    s32 a;
    s32 r;
    s32 t;
    C2244Task* o;
    if (lbl_3_bss_9D90 == NULL) {
        lbl_3_bss_9D90 = fn_800B0A5C_insertQueue(fn_3_C2244, 5);
    }
    if (lbl_803CC1B8->_10 != 0x136) {
        fn_3_B7FC8(lbl_3_data_81DC[g_d_GameSettings.StadiumID] + 6, 8);
    }
    lbl_3_bss_9D90->f2A = 0xFF;
    lbl_3_bss_9D90->f29 = 2;
    r = rand() % 3;
    lbl_3_bss_9D90->pos[0] = lbl_3_data_17880[r * 3];
    lbl_3_bss_9D90->pos[1] = lbl_3_data_17880[r * 3 + 1];
    lbl_3_bss_9D90->pos[2] = lbl_3_data_17880[r * 3 + 2];
    lbl_3_bss_9D90->f24 = 10 - rand() % 20;
    i = 2;
    while (i-- != 0) {
        a = ((0x1FFF - rand() * 0x3FFF / 0x7FFF) >> (1 - i)) + 0x1FFF;
        t = rand();
        t = t * a / 0x7FFF;
        o = lbl_3_bss_9D90;
        o->f20[i] = t;
        o = lbl_3_bss_9D90;
        o->f25[i] = o->f24 + 2 - rand() % 2;
        t = rand() % 2 + 1;
        o = lbl_3_bss_9D90;
        o->f27[i] = t;
    }
}

// .text:0x000C1C18 size:0x62C mapped:0x80700CAC
typedef struct { Mtx m; } C1C18Mtx;
extern const C1C18Mtx lbl_3_rodata_208C; // identity
extern const f32 lbl_3_rodata_20C8; // 512.0f
extern const f32 lbl_3_rodata_20CC; // 100.0f
extern const f32 lbl_3_rodata_20D0; // 1280.0f
extern const f32 lbl_3_rodata_20D8; // 256.0f
extern const f32 lbl_3_rodata_20DC; // 0.25f
extern const f32 lbl_3_rodata_20E0; // 0.75f
extern const f32 lbl_3_rodata_20E4; // 2pi / 65536
// Draw callback of the fn_3_C2244 task: a camera-facing quad at the task's
// position, then two spinning quads that walk along their diagonal.
// NONMATCHING ~93%: 398 vs 395 insns, constant-load scheduling and f-reg allocation only
#if NONMATCHING
void fn_3_C1C18(Rep1FD8Ent* ent) {
    Mtx m;
    Vec v;
    C2244Task* t;
    s32 i;
    u32 color;
    f32 scale;
    f32 w;
    f32 h;
    f32 c;
    f32 sn;

    *(C1C18Mtx*)m = lbl_3_rodata_208C;
    t = ent->w38;
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    for (i = 0; i <= 2; i++) {
        SetDisplayStateTexture(&lbl_3_bss_9D98[i], i, i);
    }
    color = (s32)(t->f2A * lbl_3_data_1787C) | 0xFFFFFF00;
    PSMTXMultVec(ent->m, (Vec*)t->pos, &v);
    scale = (lbl_3_rodata_20CC + (s8)t->f24) / lbl_3_rodata_20CC;
    w = (lbl_3_rodata_20C8 * scale * -v.z) / lbl_3_rodata_20D0;
    h = (lbl_3_rodata_20D8 * scale * -v.z) / lbl_3_rodata_20D0;
    w *= lbl_3_rodata_20D4;
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(v.x - w, v.y - lbl_3_rodata_20DC * h, v.z);
    GXColor1u32(color);
    GXTexCoord2s16(0, 0);
    GXPosition3f32(v.x - w, v.y + lbl_3_rodata_20E0 * h, v.z);
    GXColor1u32(color);
    GXTexCoord2s16(0, 1);
    GXPosition3f32(v.x + w, v.y + lbl_3_rodata_20E0 * h, v.z);
    GXColor1u32(color);
    GXTexCoord2s16(1, 1);
    GXPosition3f32(v.x + w, v.y - lbl_3_rodata_20DC * h, v.z);
    GXColor1u32(color);
    GXTexCoord2s16(1, 0);
    GXEnd();

    h = (lbl_3_rodata_20D8 * -v.z) / lbl_3_rodata_20D0;
    color = t->f2A | 0xFFFFFF00;
    for (i = t->f29; i < 2; i++) {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, t->f27[i], GX_COLOR0A0);
        SetDisplayStateTexture(&lbl_3_bss_9D98[t->f27[i]], 0, 0);
        c = (lbl_3_rodata_20CC + (s8)t->f25[i]) / lbl_3_rodata_20CC * h * cos(lbl_3_rodata_20E4 * t->f20[i]);
        sn = (lbl_3_rodata_20CC + (s8)t->f25[i]) / lbl_3_rodata_20CC * h * sin(lbl_3_rodata_20E4 * t->f20[i]);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(v.x, v.y, v.z);
        GXColor1u32(color);
        GXTexCoord2s16(0, 0);
        GXPosition3f32(v.x - sn, v.y + c, v.z);
        GXColor1u32(color);
        GXTexCoord2s16(0, 1);
        GXPosition3f32(v.x + c - sn, sn + (v.y + c), v.z);
        GXColor1u32(color);
        GXTexCoord2s16(1, 1);
        GXPosition3f32(v.x + c, v.y + sn, v.z);
        GXColor1u32(color);
        GXTexCoord2s16(1, 0);
        GXEnd();
        v.x += (c - sn) * lbl_3_rodata_20D4;
        v.y += (c + sn) * lbl_3_rodata_20D4;
    }
    t->f29 -= (t->f29 != 0);
    i = t->f2A - (t->f29 == 0) * 42;
    t->f2A = i * (i > 0);
}
#endif

// .text:0x000C2244 size:0xCC mapped:0x807012D8
void fn_3_C2244(void) {
    C2244Task* p = (C2244Task*)lbl_803CC1B8;
    if (*(s32*)&lbl_3_bss_9D9C != 0) {
        lbl_3_bss_9D90 = NULL;
        REMOVE_QUEUE_NOARG();
        return;
    }
    if (p->f2A != 0) {
        fn_800A7D4C(1, &lbl_3_data_17804[lbl_803CBBC0]);
        PSMTXCopy(fn_80052768_getCamera(0)->view, lbl_3_data_17804[lbl_803CBBC0].m);
        lbl_3_data_17804[lbl_803CBBC0].w38 = p;
    }
}

#ifdef TARGET_PC
// The actor and its bones (main/file_80063028.h); DspObj's offsets are the
// GameCube ones.
static void port_draw_actor_dlists(void* pp, Mtx m2) {
    GameActor* a = *(GameActor**)pp;
    GameBone* b = (GameBone*)a->drawPriorityList.Head;
    if (a->skinObject != NULL) {
        if (a->skHeader != NULL) {
            fn_8003A8A0((void*)a->skinObject, m2, 1);
        } else {
            DOVARenderSkin((void*)a->skinObject, m2, (void*)a->skinMtxArray, (void*)a->skinInvTransposeMtxArray, 0, NULL);
        }
    }
    for (; b != NULL; b = (GameBone*)b->drawPriorityLink.Next) {
        if (b->dispObj != NULL) {
            DOSetWorldMatrix((void*)b->dispObj, b->forwardMtx);
            fn_8003A8A0((void*)b->dispObj, m2, 0);
        }
    }
}
#endif

// .text:0x000C2310 size:0xD0 mapped:0x807013A4
void fn_3_C2310(void* pp, void* cam) {
    Mtx m2;
    Mtx m;
    DspObj2* o;
    DspObj2* n;
    CTRLBuildMatrix(lbl_3_bss_9D94, m);
    PSMTXConcat((f32 (*)[4])cam, m, m2);
#ifdef TARGET_PC
    port_draw_actor_dlists(pp, m2);
#else
    o = *(DspObj2**)pp;
    n = o->child;
    if (o->w14 != 0) {
        if (o->w7C != 0) {
            fn_8003A8A0(o->w14, m2, 1);
        } else {
            DOVARenderSkin(o->w14, m2, o->w64, o->w68, 0, NULL);
        }
    }
    while (n != 0) {
        if (n->w14 != 0) {
            DOSetWorldMatrix(n->w14, n->wEC);
            fn_8003A8A0(n->w14, m2, 0);
        }
        n = n->next;
    }
#endif
}

// .text:0x000C23E0 size:0xC0 mapped:0x80701474
void fn_3_C23E0(void) {
    StadObj1FD8* c;
    int i;
    C42A4Bss* base;
    fn_800BF058(fn_3_B8184);
    base = &lbl_3_common_bss_350E4;
    for (i = 0; i < base->count; i++) {
        c = &base->arr[i];
        fn_3_B828C(c);
        if (i >= 1 && i < 11) {
            if (c->visible) {
                if (c->model != 0) {
                    c->model->actor->flags = c->pad93 | 6;
                    fn_800BDF70(c->model);
                }
            }
        }
    }
}

// .text:0x000C24A0 size:0x1A4 mapped:0x80701534
void fn_3_C24A0(void) {
    Vec n;
    u8 a;
    u8* q;
    lbl_803CC1B8->_10 -= 1;
    if (lbl_803CC1B8->_10 == 0) {
        REMOVE_QUEUE_NOARG();
        fn_80023B90(&lbl_800F7478[g_d_GameSettings._54].light, &lbl_80367318);
        q = lbl_8036E548._0004[0];
        if (q != NULL) {
            // TODO port: q is a loaded file; its word at 0x14 is an in-file offset (32-bit layout).
            *(u16*)(q + *(u32*)(q + 0x14) + 0x60) = 2;
        }
    } else {
        s16 t = lbl_803CC1B8->_10;
        if (t < 12) {
            a = (t << 7) / 12;
        } else {
            a = 0x80;
        }
        fn_80023B90(&lbl_3_data_177F8.light, &lbl_80367318);
        q = lbl_8036E548._0004[0];
        if (q != NULL) {
            // TODO port: see above.
            *(u16*)(q + *(u32*)(q + 0x14) + 0x60) = 3;
        }
        lbl_803C5090.flags = 0xB;
        lbl_803C5090.scale = lbl_3_rodata_20F0;
        lbl_803C5090.lines = 0x1C0;
        lbl_803C5090.alpha = a;
        lbl_803C5090.repeat = lbl_3_data_177F4;
        lbl_803C5090.unk18 = 1;
    }
    n.x = -lbl_80367318.x;
    n.y = -lbl_80367318.y;
    n.z = -lbl_80367318.z;
    PSVECNormalize(&n, &n);
    fn_800BEBCC(0, n);
}

// .text:0x000C2644 size:0x330 mapped:0x807016D8
// Stadium ambient task: every 1800 frames it fires the event at ticks 300, 310
// and 1200 (fn_3_C24A0 fade + fn_3_C19C8).
// NONMATCHING ~90% (192 of 204 insns, rest regalloc): inlines fn_3_C19C8 (itself 99%); the original keeps an empty-bodied minigamesEnabled/g_GameLogic.gameStatus in 0x1B..0x29 test that CW drops for us
#if NONMATCHING
void fn_3_C2644(void) {
    s16 tick;
    if (g_GameLogic.gameStatus == 0x17) {
        lbl_3_bss_9D9C = 1;
    }
    if (*(s32*)&lbl_3_bss_9D9C != 0) {
        REMOVE_QUEUE_NOARG();
        return;
    }
    tick = (lbl_803CC1B8->_10 + 1) % 1800;
    lbl_803CC1B8->_10 = tick;
    switch (tick) {
    case 300:
    case 310:
    case 1200:
        ((SceneTask*)fn_800B0A5C_insertQueue(fn_3_C24A0, 5))->_10 = 0x10;
        fn_3_C19C8();
        break;
    }
}
#endif

// .text:0x000C2974 size:0x18 mapped:0x80701A08
#ifndef TARGET_PC
extern u8 lbl_3_bss_9DE7;
#endif
#ifndef TARGET_PC
extern u8 lbl_3_bss_9D82;
#endif

void fn_3_C2974(void) {
    lbl_3_bss_9DE7 = 1;
    lbl_3_bss_9D82 = 1;
}

// .text:0x000C298C size:0x114 mapped:0x80701A20
// Emitter (main/file_800263FC.h Emitter) of the smoke effect, the fields used here.
typedef struct C366CHdr {
    void* prev;
    void* next;
    void* update;
    C4724P* head;
    void* tex;
    u8 pad14[4];
    Vec pos;
    u8 idx;
} C366CHdr;
// Smoke task: keeps six emitters (fn_3_C30F0) alive.
typedef struct C298CTask {
#ifdef TARGET_PC
    SCENE_TASK_VIEW_HEAD // SceneTask head (main/scene_task.h)
    struct C366CHdr* emitters[6];
#else
    /*0x00*/ u8 hdr[0x14];
    /*0x14*/ struct C366CHdr* emitters[6];
#endif
} C298CTask;
void fn_3_C298C(void) {
    C298CTask* e = (C298CTask*)lbl_803CC1B8;
    u32 i;
    if (g_d_GameSettings.GameModeSelected == 7) {
        if (g_GameLogic.gameStatus == 0xB || g_GameLogic.gameStatus >= 0x22) {
            if (g_Minigame._1A40 != 0 && g_Minigame._1A38 == 0) {
                REMOVE_QUEUE_NOARG();
            }
        }
    } else if (g_GameLogic._128 != 0 || g_d_GameSettings._13 != 0) {
        REMOVE_QUEUE_NOARG();
    }
    i = 0;
    do {
        struct C366CHdr* o = e->emitters[i];
        if (o == NULL || o->update == NULL) {
            void* r = fn_80033A24(fn_3_C30F0, 0x80, 0, 0x15, 1, 0);
            e->emitters[i] = r;
            r = e->emitters[i];
            if (r != NULL) {
                fn_3_C366C(r, i);
            }
        }
        i++;
    } while (i < 6);
}

// .text:0x000C2AA0 size:0x1E0 mapped:0x80701B34
// NONMATCHING 94%: all f-reg numbering (orig: w=f29 lo=f30 h/hi=f31; ours w=f30 h=f29 lo=f31)
#if NONMATCHING
u8 fn_3_C2AA0(Vec* pos, f32 w, f32 h) {
    Vec out;
    f32 hw;
    f32 hh;
    Vec v[4];
    CamMtx* m;
    u32 i;
    u32 t;
    f32 z;
    f32 x;
    f32 y;
    u8 acc;
    u8 f;
    acc = 0;
    m = fn_80052734(fn_8005268C());
    PSMTXMultVec(m->view, pos, pos);
    z = pos->z;
    if (z > lbl_3_rodata_20F4 || z < lbl_3_rodata_20F8) {
        return 0;
    }
    x = pos->x;
    y = pos->y;
    hw = w * lbl_3_rodata_20D4;
    hh = h * lbl_3_rodata_20D4;
    v[0].z = v[1].z = v[2].z = v[3].z = z;
    v[0].x = v[3].x = x - hw;
    v[1].x = v[2].x = x + hw;
    v[0].y = v[1].y = y - hh;
    v[2].y = v[3].y = y + hh;
    for (i = 0; i < 4; i++) {
        PSMTX44MultVec(m->proj, &v[i], &out);
        f = (out.x < lbl_3_rodata_20F4);
        f |= (out.x > lbl_3_rodata_20F0) << 1;
        f |= (out.y < lbl_3_rodata_20F4) << 2;
        f |= (out.y > lbl_3_rodata_20F0) << 3;
        if (f == 0) {
            return 1;
        }
        acc &= f;
    }
    t = acc & 3;
    if (t == 1 || t == 2) {
        return 0;
    }
    t = acc & 0xC;
    if (t == 4 || t == 8) {
        return 0;
    }
    return 1;
}
#endif

// .text:0x000C2C80 size:0x25C mapped:0x80701D14
void fn_3_C2C80(void* pv, C366CHdr* h) {
    C4724P* p = pv;
    f32 a;
    s16 t;
    a = lbl_3_rodata_20FC * (f32)(rand() % 360);
    p->vx = lbl_3_rodata_2100 * (f32)cos(a);
    p->vz = lbl_3_rodata_2100 * (f32)sin(a);
    p->vy = lbl_3_rodata_2108;
    p->f1C = lbl_3_rodata_20D4;
    p->f1C = p->f1C + (f64)((u32)rand() % 2500) / lbl_3_rodata_2110;
    p->f38 = p->f1C;
    p->f3C = lbl_3_rodata_2118 * p->f1C;
    p->f20 = (f64)(rand() % 101) / lbl_3_rodata_2120;
    t = rand() % 24 + 0x48;
    p->s4A = t;
    p->f4F = t;
    p->x = h->pos.x;
    p->y = h->pos.y;
    p->z = h->pos.z;
    p->a40 = lbl_3_rodata_2028[0];
    p->a41 = lbl_3_rodata_2028[1];
    p->a42 = lbl_3_rodata_2028[2];
    p->f24 = lbl_3_rodata_2128;
    p->a43 = lbl_3_rodata_2128;
    p->s4A = p->f4F;
    p->s48 = 0;
}

// .text:0x000C2EDC size:0x214 mapped:0x80701F70
// NONMATCHING 96%: orig hoists the 2118/2138/213C const loads up into the first fmadd; ours loads them later (f-reg numbering shifts)
#if NONMATCHING
void fn_3_C2EDC(void* pv) {
    C4724P* p = pv;
    p->f38 = p->f20 * (lbl_3_rodata_2130 * p->f1C / p->f4F) + p->f38;
    p->f3C = p->f20 * (lbl_3_rodata_2118 * p->f1C / p->f4F) + p->f3C;
    p->f24 = p->f24 + (lbl_3_rodata_2138 / p->f4F);
    if (p->f24 < lbl_3_rodata_213C) {
        p->f24 = lbl_3_rodata_213C;
    }
    p->a43 = p->f24;
    p->a40 = lbl_3_rodata_2028[0] * (p->a43 / lbl_3_rodata_2140);
    p->a41 = lbl_3_rodata_2028[1] * (p->a43 / lbl_3_rodata_2140);
    p->a42 = lbl_3_rodata_2028[2] * (p->a43 / lbl_3_rodata_2140);
    p->x += p->vx;
    p->y -= p->vy;
    p->z += p->vz;
    p->s4A -= 1;
}
#endif

// Emitter view used by the fn_3_C30F0 smoke effects: spawn point and slot.
// .text:0x000C30F0 size:0x57C mapped:0x80702184
extern const f32 lbl_3_rodata_2148;
extern void fn_8003403C(f32, f32);
extern void fn_80033CC8(void*, void*);
// Update/draw of a smoke emitter (started by fn_3_C366C): grows and fades the
// puffs and respawns dead ones at the emitter position.
// NONMATCHING ~97% (with fn_3_C2EDC enabled: same 351 insns, only the f-reg/scheduling of the inlined fn_3_C2EDC, which is itself 96%); inlines fn_3_C2EDC and fn_3_C2C80
#if NONMATCHING
s32 fn_3_C30F0(C366CHdr* h) {
    C4724P* p = h->head;
    Vec pos;
    if (g_GameLogic.gameStatus >= 0x1B && g_GameLogic.gameStatus <= 0x21) {
        return 0;
    }
    if (g_GameLogic.gameStatus == 2 || g_GameLogic.gameStatus == 1) {
        pos = h->pos;
        if (!fn_3_C2AA0(&pos, lbl_3_rodata_2148, lbl_3_rodata_2148)) {
            return 0;
        }
    }
    fn_80033620(h);
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 1, 1, 0);
    do {
        if (p->s48 <= 0 && p->s4A != 0) {
            fn_8003403C(p->f38, p->f3C);
            fn_80033CC8(p, h->tex);
            if (fn_8005268C() == 0) {
                fn_3_C2EDC(p);
            }
        }
        p->s48 -= (fn_8005268C() == 0);
        if (p->s4A == 0) {
            fn_3_C2C80(p, h);
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}
#endif

// .text:0x000C366C size:0x35C mapped:0x80702700
extern const Vec lbl_3_rodata_202C[6];
// Starts smoke emitter `idx` at its fixed spawn point (lbl_3_rodata_202C).
void fn_3_C366C(void* hv, u8 idx) {
    C366CHdr* h = hv;
    s16 delay;
    C4724P* p = h->head;
    s16 t;
    f32 a;
    h->tex = lbl_3_bss_9F0C;
    h->pos = lbl_3_rodata_202C[idx];
    h->idx = idx;
    delay = 0;
    while (p != NULL) {
        a = lbl_3_rodata_20FC * (f32)(rand() % 360);
        p->vx = lbl_3_rodata_2100 * (f32)cos(a);
        p->vz = lbl_3_rodata_2100 * (f32)sin(a);
        p->vy = lbl_3_rodata_2108;
        p->s48 = delay;
        p->f1C = lbl_3_rodata_20D4;
        p->f1C = p->f1C + (f64)((u32)rand() % 2500) / lbl_3_rodata_2110;
        p->f38 = p->f1C;
        p->f3C = lbl_3_rodata_2118 * p->f1C;
        p->f20 = (f64)(rand() % 101) / lbl_3_rodata_2120;
        p->x = h->pos.x;
        p->y = h->pos.y;
        p->z = h->pos.z;
        p->a40 = lbl_3_rodata_2028[0];
        p->a41 = lbl_3_rodata_2028[1];
        p->a42 = lbl_3_rodata_2028[2];
        p->f24 = lbl_3_rodata_2128;
        p->a43 = lbl_3_rodata_2128;
        t = rand() % 24 + 0x48;
        delay += 4;
        p->s4A = t;
        p->f4F = t;
        p->f4D = 0x1D;
        p->f4E = 0;
        p = p->next;
    }
}

// .text:0x000C39C8 size:0x70 mapped:0x80702A5C
void fn_3_C39C8(void) {
    u32 i = 0;
    do {
        void* r = fn_80033A24(fn_3_C30F0, 0x80, 0, 0x15, 1, 0);
        if (r != NULL) {
            fn_3_C366C(r, i);
        }
        i++;
    } while (i < 6);
}

// .text:0x000C3A38 size:0x1F4 mapped:0x80702ACC
void fn_3_C3A38(camera_803c639c_s* obj) {
    Vec v;
    Mtx m;
    if (g_GameLogic.gameStatus != 2 || obj == NULL) {
        lbl_3_bss_9D8C = 0;
        lbl_3_bss_9D81 = 0;
        fn_800528B4();
        return;
    }
    if (lbl_3_bss_9D81 != 0) {
        lbl_3_bss_9D8C = 0x3C;
        lbl_3_bss_9D81 = 0;
    }
    if (lbl_3_bss_9D8C != 0) {
        v.x = (f32)(rand() % 20 - 10) / lbl_3_rodata_214C;
        v.y = (f32)(rand() % 20 - 10) / lbl_3_rodata_214C;
        v.z = lbl_3_rodata_213C;
        PSMTXInverse(fn_80052768_getCamera(0)->view, m);
        PSMTXMultVecSR(m, &v, &v);
        obj->eye.x += v.x;
        obj->eye.y += v.y;
        obj->eye.z += v.z;
        obj->target.x += v.x;
        obj->target.y += v.y;
        obj->target.z += v.z;
        lbl_3_bss_9D8C -= 1;
    }
}

// .text:0x000C3C2C size:0x268 mapped:0x80702CC0
#define C3C2C_SLOT(o, i) (lbl_80371C30[(o)->u14.objIdx + (i)].obj)
void fn_3_C3C2C(void) {
    C3C2CBss* g = &lbl_3_bss_9D80;
    u8* st = g->state;
    Vec* pv = g->pos;
    SceneTask* e = lbl_803CC1B8;
    s32 i;
    for (i = 0; i < 8; i++, st++, pv++) {
        switch (*st) {
        case 1: {
            s16 y1, x1;
            fn_800528C0(&x1, &y1, pv->x, pv->y, pv->z);
            C3C2C_SLOT(g->fD0, i)->x = x1;
            C3C2C_SLOT(g->fD0, i)->y = y1;
            C3C2C_SLOT(g->fD0, i)->z = 0.0f;
            C3C2C_SLOT(e, i)->_5C = 0;
            C3C2C_SLOT(e, i)->flags |= 2;
            *st = 2;
            break;
        }
        case 2: {
            s16 y2, x2;
            fn_800528C0(&x2, &y2, pv->x, pv->y, pv->z);
            C3C2C_SLOT(g->fD0, i)->x = x2;
            C3C2C_SLOT(g->fD0, i)->y = y2;
            C3C2C_SLOT(g->fD0, i)->z = 0.0f;
            if ((C3C2C_SLOT(e, i)->_69 == 2) ? 1 : 0) {
                C3C2C_SLOT(e, i)->flags &= ~2;
                *st = 0;
            }
            break;
        }
        }
    }
    if (g->f67 != 0) {
        REMOVE_QUEUE_NOARG();
        fn_80034CEC(g->fD0);
        g->f67 = 0;
    }
}

// .text:0x000C3E94 size:0xDC mapped:0x80702F28
void fn_3_C3E94(f32* pos, s32 idx) {
    s16 x;
    s16 y;
    fn_800528C0_xyz(pos[0], pos[1], pos[2], &x, &y);
    lbl_80371C30[lbl_3_bss_9E50[0]->u14.objIdx + idx].obj->x = x;
    lbl_80371C30[lbl_3_bss_9E50[0]->u14.objIdx + idx].obj->y = y;
    lbl_80371C30[lbl_3_bss_9E50[0]->u14.objIdx + idx].obj->z = 0.0f;
}

// .text:0x000C3F70 size:0xF8 mapped:0x80703004
void fn_3_C3F70(StadObj1FD8* a) {
    GameActor* t = a->model->actor;
    DisplayStateList* q;
    u32 i;
    u32 j;
    void* e; // bone, then its display object
    if (lbl_3_bss_9D88++ > 4) {
        if (++lbl_3_data_177F0 > 0x13) {
            lbl_3_data_177F0 = 4;
        }
        lbl_3_bss_9D88 = 0;
    }
    if (lbl_3_bss_9D88 != 0) {
        return;
    }
    for (i = 0; i < t->totalBones; i++) {
        e = t->boneArray[i];
        e = ((GameBone*)e)->dispObj;
        if (e != NULL) {
            q = PTR32_GET(DisplayStateList, ((struct DODisplayObj*)e)->displayData->displayStateList);
            for (j = 0; j < ((struct DODisplayObj*)e)->displayData->numStateEntries; j++) {
                if (q->id == 1) {
                    q->setting = q->setting & ~0x1FFF;
                    q->setting = q->setting | lbl_3_data_177F0;
                }
                q++;
            }
        }
    }
}

// .text:0x000C4068 size:0x84 mapped:0x807030FC
void fn_3_C4068(StadObj1FD8* a) {
    void* p = a->model->actor; // walked down to the first display state of bone 1
    u32 n;
    u32 v;
    u16 t;
    p = ((GameActor*)p)->boneArray;
    p = ((GameBone**)p)[1];
    p = ((GameBone*)p)->dispObj;
    p = ((struct DODisplayObj*)p)->displayData;
    p = PTR32_GET(DisplayStateList, ((DisplayData*)p)->displayStateList);
    n = lbl_3_bss_9D84;
    t = ((DisplayStateList*)p)->setting & 0x1FFF;
    lbl_3_bss_9D84 = n + 1;
    v = t;
    if (n > 4) {
        v = t + 1;
        if ((u16)v > 0x13) {
            v = 4;
        }
        lbl_3_bss_9D84 = 0;
    }
    ((DisplayStateList*)p)->setting = ((DisplayStateList*)p)->setting & ~0x1FFF;
    ((DisplayStateList*)p)->setting = ((DisplayStateList*)p)->setting | (u16)v;
}

// .text:0x000C40EC size:0x60 mapped:0x80703180
void fn_3_C40EC(StadObj1FD8* a) {
    DisplayStateList* p = PTR32_GET(DisplayStateList, a->model->actor->boneArray[1]->dispObj->displayData->displayStateList);
    if (a->type != 6) {
        p->setting = p->setting & ~0x1FFF;
        p->setting = p->setting | 0x19;
    } else {
        p->setting = p->setting & ~0x1FFF;
        p->setting = p->setting | 0x1A;
    }
}

// .text:0x000C414C size:0x158 mapped:0x807031E0
void fn_3_C414C(int idx) {
    u8 hit = 0;
    Vec t;
    StadObj1FD8* c = &lbl_3_common_bss_350E4.arr[idx];
    CTRLGetTranslation(&c->u.ctrl, &t.x, &t.y, &t.z);
    if (g_Ball.AtBat_ContactResult != 2) {
        if (c->type == 5 && lbl_800E8754._04 != 0) {
            fn_3_CB7E8(t.x, t.y - lbl_3_rodata_2150, t.z);
            hit = 1;
            c->type = 6;
        } else if (c->type == 4 && lbl_800E8754._04 != 0) {
            fn_3_CB7E8(t.x, t.y, t.z - lbl_3_rodata_2150);
            hit = 1;
            c->type = 6;
        }
    }
    if (hit) {
        int i = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy ? 7 : 6;
        lbl_3_bss_9E48[i] = 1;
        lbl_3_bss_9DE8[i].x = g_Ball.AtBat_Contact_BallPos.x;
        lbl_3_bss_9DE8[i].y = -g_Ball.AtBat_Contact_BallPos.y;
        lbl_3_bss_9DE8[i].z = g_Ball.AtBat_Contact_BallPos.z;
    }
}

// .text:0x000C42A4 size:0x1A8 mapped:0x80703338
#ifndef TARGET_PC
extern u8 lbl_3_bss_9DE0[];
#endif
extern StadPlaceGroupC lbl_3_data_17704;
extern f32 lbl_3_rodata_2154;
extern void fn_3_B8414(void*, void*);
extern void fn_3_B8464(void*, void*);
extern void fn_3_B8574(void);
void fn_3_C42A4(s32* a, s32* b) {
    Mtx m;
    C42A4Bss* g;
    StadPlace14* e;
    s32 off;
    s32 k;
    s32 j;
    u32 v;
    StadObj1FD8* c;
    s32 idx;
    g = &lbl_3_common_bss_350E4;
    for (k = 0; k < 5; k++) {
        v = (u16)(g->p40[*a - 1] + g->p3C[*a - 1]);
        g->p40[*a] = v;
        ((void (*)(void))fn_3_B8574)();
        e = lbl_3_data_17704.place;
        off = v * 4;
        for (j = 0; j < 10; e++, j++) {
            if (k == e->f12 && e->type != 7) {
                if (lbl_3_common_bss_350E4.arr[j + lbl_3_bss_9DE0[0]].animated) {
                    idx = j + lbl_3_bss_9DE0[0];
                    *(s32*)((u8*)g->p44 + off) = idx;
                    off += 4;
                    g->p3C[*a] += 1;
                    c = &lbl_3_common_bss_350E4.arr[j + lbl_3_bss_9DE0[0]];
                    CTRLBuildMatrix(&c->u.ctrl, m);
                    fn_3_B8464(m, c->anim);
                    m[1][3] = m[1][3] * lbl_3_rodata_2154;
                    fn_3_B8464(m, c->anim);
                    *b += 1;
                }
            }
        }
        if (g->p3C[*a] != 0) {
            fn_3_B8414(g->p48 + *a * 0x18, g->p48 + (*a * 2 + 1) * 0xC);
            *a += 1;
        }
    }
}

// .text:0x000C444C size:0x2D8 mapped:0x807034E0
void fn_3_C444C(void* hv, StadObj1FD8* b) {
    C4724Hdr* h = hv;
    C4724P* p = h->head;
    f32 px = b->pos.x;
    f32 py = b->pos.y;
    f32 pz = b->pos.z;
    u32 i = 0;
    f32 a;
    f32 c;
    f32 k;
    while (p != NULL) {
        p->x = px;
        p->y = py;
        p->z = pz;
        a = lbl_3_rodata_2158 * (f32)(rand() % 360) / lbl_3_rodata_215C;
        c = lbl_3_rodata_2158 * (f32)(rand() % 360) / lbl_3_rodata_215C;
        k = lbl_3_rodata_20D4 - (f32)(rand() % 3) / lbl_3_rodata_2160[0];
        p->vx = k * cos(a) * cos(c);
        p->vy = -k * sin(a);
        p->vz = k * sin(a) * cos(c);
        p->f38 = p->f3C = lbl_3_rodata_2164;
        p->s48 = i / 6;
        i++;
        p->f4D = 0x1B;
        p->f4E = 0;
        p->a43 = 0xFF;
        p->a42 = 0xFF;
        p->a41 = 0xFF;
        p->a40 = 0xFF;
        p->s4A = 1;
        p = p->next;
    }
}

extern u8 lbl_80366158[];
#ifdef TARGET_PC // the struct holds pointers: reach the byte through it (port/game/views.c)
u8* port_80366158_byte(u32 gcOffset);
#define LBL_80366158_U8(off) (*port_80366158_byte(off))
#else
#define LBL_80366158_U8(off) lbl_80366158[off]
#endif
extern void fn_8003403C(f32, f32);
extern void fn_80033CC8(void*, void*);
extern const f32 lbl_3_rodata_2168[];
extern const f32 lbl_3_rodata_21A4;
extern const f32 lbl_3_rodata_21AC;
extern StadPlace14 lbl_3_data_17514[11];
extern const f32 lbl_3_rodata_21A8;
extern f64 pow(f64, f64);
// .text:0x000C4724 size:0x1AC mapped:0x807037B8
// NONMATCHING 97%: only f-reg numbering of hoisted consts (213C should be f1, loaded after first fadds)
#if NONMATCHING
u32 fn_3_C4724(void* hv) {
    C4724Hdr* h = hv;
    C4724P* p = h->head;
    u32 n = 0;
    f32 k;
    f32 c;
    fn_80033620(h);
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    do {
        if (p->s48 != 0) {
            p->s48 -= (LBL_80366158_U8(0x28) == 0);
        } else if (p->s4A != 0) {
            fn_8003403C(p->f38, p->f3C);
            fn_80033CC8(p, h->tex);
            if (LBL_80366158_U8(0x28) == 0) {
                k = lbl_3_rodata_2168[0];
                c = lbl_3_rodata_213C;
                p->x += p->vx;
                p->y += p->vy;
                p->z += p->vz;
                p->f38 -= k;
                p->f3C -= k;
                p->a43 -= 0xF;
                if (p->f38 <= c || p->f3C <= c) {
                    p->s4A = 0;
                }
            }
            n++;
        }
        p = p->next;
    } while (p != NULL && n < (h->f14 & 0xFFF));
    h->f24 -= (LBL_80366158_U8(0x28) == 0);
    if (h->f24 == 0) {
        return 1;
    }
    return 0;
}
#endif

// 99%: only the x/y load order of the src->pos copy (we load y before x)
// .text:0x000C48D0 size:0x2B0 mapped:0x80703964
void fn_3_C48D0(void* hv, Vec* src) {
    C4724Hdr* h;
    C4724P* p;
    u32 i;
    f32 a;
    f32 c;
    f32 k;
    f32 x;
    f32 y;
    f32 z;
    h = hv;
    p = h->head;
    i = 0;
    while (p != NULL) {
        x = ((volatile f32*)src)[0];
        y = ((volatile f32*)src)[1];
        p->x = x;
        z = ((volatile f32*)src)[2];
        p->y = y;
        p->z = z;
        a = lbl_3_rodata_2158 * (f32)(rand() % 181) / lbl_3_rodata_215C;
        c = lbl_3_rodata_2158 * (f32)(rand() % 360) / lbl_3_rodata_215C;
        k = lbl_3_rodata_20D4 - (f32)(rand() % 3) / lbl_3_rodata_2160[0];
        p->vx = k * cos(a) * cos(c);
        p->vy = -k * sin(a);
        p->vz = k * sin(a) * cos(c);
        p->f38 = p->f3C = lbl_3_rodata_2164;
        p->s48 = i / 6;
        i++;
        p->f4D = 0x1B;
        p->f4E = 0;
        p->a43 = 0xFF;
        p->a42 = 0xFF;
        p->a41 = 0xFF;
        p->a40 = 0xFF;
        p->s4A = 1;
        p = p->next;
    }
}

// .text:0x000C4B80 size:0x174 mapped:0x80703C14
void fn_3_C4B80(void) {
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(0);
    GXSetTevColorIn(0, 0xF, 0xA, 8, 0xF);
    GXSetTevAlphaIn(0, 7, 5, 4, 7);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXSetProjection(fn_80052734(fn_8005268C())->proj, GX_PERSPECTIVE);
    GXLoadPosMtxImm(fn_80052734(fn_8005268C())->view, GX_PNMTX0);
    GXSetCurrentMtx(0);
}

// .text:0x000C4CF4 size:0x20C mapped:0x80703D88
void fn_3_C4CF4(void* hv, u8 type) {
    C4724Hdr* h = hv;
    C4724P* p = h->head;
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(0);
    GXSetTevColorIn(0, 0xF, 0xA, 8, 0xF);
    GXSetTevAlphaIn(0, 7, 5, 4, 7);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXSetProjection(fn_80052734(fn_8005268C())->proj, GX_PERSPECTIVE);
    GXLoadPosMtxImm(fn_80052734(fn_8005268C())->view, GX_PNMTX0);
    GXSetCurrentMtx(0);
    while (p != NULL) {
        if (p->s48 <= 0 && p->s4A > 0 && type == p->f50) {
            fn_8003403C(p->f38, p->f3C);
            fn_80033CC8(p, h->tex);
        }
        p = p->next;
    }
}

extern int rand(void);
extern const f32 lbl_3_rodata_2160[];
extern const f32 lbl_3_rodata_216C;
extern f64 sin(f64);
extern f64 cos(f64);
extern const f32 lbl_3_rodata_2158;
extern const f32 lbl_3_rodata_215C;
extern const f32 lbl_3_rodata_2170[];
extern const f32 lbl_3_rodata_2174;
typedef struct { u8 pad0[0x20]; void* f20; } C4F00H;
#define C4F00_SPAWN() \
    do { \
        r = (f32)(15 - rand() % 31) / lbl_3_rodata_2160[0]; \
        a = lbl_3_rodata_2158 * (f32)(rand() % 361) / lbl_3_rodata_215C; \
        t.x = r * cos(a); \
        t.z = r * sin(a); \
        t.y = lbl_3_rodata_216C; \
        CTRLBuildMatrix((Control*)h->f20, m); \
        PSMTXMultVec(m, &t, (Vec*)&p->x); \
    } while (0)
// .text:0x000C4F00 size:0x404 mapped:0x80703F94
s32 fn_3_C4F00(void* hv) {
    C4724Hdr* h = hv;
    C4724P* p;
    Vec t;
    Mtx m;
    f32 a;
    f32 k;
    f32 c;
    f32 r;
    fn_80033620(h);
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    p = h->head;
    do {
        if (p->s48 != 0) {
            p->s48 -= (LBL_80366158_U8(0x28) == 0);
            if (p->s48 == 0) {
                C4F00_SPAWN();
            }
        } else if (p->s4A != 0 && LBL_80366158_U8(0x28) == 0) {
            if (p->f4F == 0) {
                p->a43 += 0xF;
                k = lbl_3_rodata_2170[0];
                p->f38 += k;
                p->f3C += k;
                if (p->f38 >= lbl_3_rodata_2174 || p->f3C >= lbl_3_rodata_2174) {
                    p->f4F = 1;
                }
            } else {
                p->a43 -= 0xF;
                k = lbl_3_rodata_2170[0];
                p->f38 -= k;
                p->f3C -= k;
                if (p->f38 <= lbl_3_rodata_213C || p->f3C <= lbl_3_rodata_213C) {
                    p->s4A = 0;
                }
            }
        }
        if (p->s4A == 0) {
            p->f38 = p->f3C = lbl_3_rodata_213C;
            p->s4A = 1;
            p->f4F = 0;
            p->s48 = 0;
            C4F00_SPAWN();
            p->a43 = 0;
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}

// .text:0x000C5304 size:0x1CC mapped:0x80704398
void fn_3_C5304(void* hv, StadObj1FD8* b) {
    C4724Hdr* h = hv;
    C4724P* p = h->head;
    s16 i = 0;
    h->f18 = &b->pos;
    h->f20 = b;
    while (p != NULL) {
        p->f38 = p->f3C = lbl_3_rodata_213C;
        p->s48 = i;
        i += 4;
        p->f4D = 0x15;
        p->f4E = 0;
        p->a42 = 0xFF;
        p->a41 = 0xFF;
        p->a40 = 0xFF;
        p->a43 = 0;
        p->s4A = 1;
        p->f4F = 0;
        if (p->s48 == 0) {
            p->x = h->f18->x + (f32)(15 - rand() % 31) / lbl_3_rodata_2160[0];
            p->y = lbl_3_rodata_216C + h->f18->y;
            p->z = h->f18->z + (f32)(15 - rand() % 31) / lbl_3_rodata_2160[0];
        } else {
            p->x = p->y = p->z = lbl_3_rodata_213C;
        }
        p = p->next;
    }
}

// .text:0x000C54D0 size:0x218 mapped:0x80704564
void fn_3_C54D0(StadObj1FD8* a) {
    C4724Hdr* h = fn_800339F0(0, (u8)(a->idx + 0x2A));
    C4724P* p;
    if (h == NULL) {
        return;
    }
    p = h->head;
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(0);
    GXSetTevColorIn(0, 0xF, 0xA, 8, 0xF);
    GXSetTevAlphaIn(0, 7, 5, 4, 7);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXSetProjection(fn_80052734(fn_8005268C())->proj, GX_PERSPECTIVE);
    GXLoadPosMtxImm(fn_80052734(fn_8005268C())->view, GX_PNMTX0);
    GXSetCurrentMtx(0);
    while (p != NULL) {
        if (p->s48 <= 0 && p->s4A > 0 && p->f50 == 1) {
            fn_8003403C(p->f38, p->f3C);
            fn_80033CC8(p, h->tex);
        }
        p = p->next;
    }
}

// .text:0x000C56E8 size:0x294 mapped:0x8070477C
void fn_3_C56E8(StadObj1FD8* a) {
    Vec v1;
    Vec v2;
    C4724Hdr* h;
    C4724P* p;
    PSMTXMultVec(fn_80052734(fn_8005268C())->view, &a->pos, &v1);
    h = fn_800339F0(0, (u8)(a->idx + 0x2A));
    if (h == NULL) {
        return;
    }
    for (p = h->head; p != NULL; p = p->next) {
        PSMTXMultVec(fn_80052734(fn_8005268C())->view, (Vec*)&p->x, &v2);
        if (v1.z >= v2.z) {
            p->f50 = 0;
        } else {
            p->f50 = 1;
        }
    }
    p = h->head;
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(0);
    GXSetTevColorIn(0, 0xF, 0xA, 8, 0xF);
    GXSetTevAlphaIn(0, 7, 5, 4, 7);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXSetProjection(fn_80052734(fn_8005268C())->proj, GX_PERSPECTIVE);
    GXLoadPosMtxImm(fn_80052734(fn_8005268C())->view, GX_PNMTX0);
    GXSetCurrentMtx(0);
    while (p != NULL) {
        if (p->s48 <= 0 && p->s4A > 0 && p->f50 == 0) {
            fn_8003403C(p->f38, p->f3C);
            fn_80033CC8(p, h->tex);
        }
        p = p->next;
    }
}

// .text:0x000C597C size:0x364 mapped:0x80704A10
void fn_3_C597C(s32 idx) {
    f32 k;
    u32 i;
    f32 px;
    C4724Hdr* h;
    f32 py;
    C4724P* p;
    f32 pz;
    f32 a;
    f32 c;
    StadObj1FD8* e;
    e = &lbl_3_common_bss_350E4.arr[idx];
    pitchingMachinePitching((u8)(e->idx + 0x2A));
    h = fn_80033A24(fn_3_C4724, 0x80, 0, 0x18, 1, (u8)(e->idx + 0x34));
    if (h != NULL) {
        p = h->head;
        px = e->pos.x;
        py = e->pos.y;
        pz = e->pos.z;
        i = 0;
        while (p != NULL) {
            p->x = px;
            p->y = py;
            p->z = pz;
            a = lbl_3_rodata_2158 * (f32)(rand() % 360) / lbl_3_rodata_215C;
            c = lbl_3_rodata_2158 * (f32)(rand() % 360) / lbl_3_rodata_215C;
            k = lbl_3_rodata_20D4 - (f32)(rand() % 3) / lbl_3_rodata_2160[0];
            p->vx = k * cos(a) * cos(c);
            p->vy = -k * sin(a);
            p->vz = k * sin(a) * cos(c);
            p->f38 = p->f3C = lbl_3_rodata_2164;
            p->s48 = i / 6;
            i++;
            p->f4D = 0x1B;
            p->f4E = 0;
            p->a43 = 0xFF;
            p->a42 = 0xFF;
            p->a41 = 0xFF;
            p->a40 = 0xFF;
            p->s4A = 1;
            p = p->next;
        }
        h->tex = lbl_3_bss_9F0C;
        h->f24 = 0x1E;
    }
    e->x.b.bd = 2;
    e->visible = 0;
    e->pos.y = lbl_3_rodata_2160[0];
}

// .text:0x000C5CE0 size:0xFC mapped:0x80704D74
u8 fn_3_C5CE0(StadObj1FD8* a) {
    Vec pos = lbl_3_rodata_2080;
    Vec d;
    u32 i;
    f32 lim;
    if (g_GameLogic.gameStatus == 2 && g_GameLogic.playOver != 0) {
        return 0;
    }
    i = 0;
    lim = lbl_3_rodata_2178;
    do {
        memset(&pos, 0, 0xC);
        fn_8001B728(i, 4, &pos);
        PSVECSubtract(&pos, &a->pos, &d);
        if (PSVECMag(&d) <= lim) {
            fn_3_25844(i, 1);
            return 1;
        }
        i++;
    } while (i < 9);
    return 0;
}

// .text:0x000C5DDC size:0x480 mapped:0x80704E70
// Task: for each object of group lbl_3_bss_9DE0[2..] still in state 1, once a
// runner comes near it (fn_3_C5CE0) bursts it into a particle spray.
// NONMATCHING ~90%: inlines fn_3_C5CE0 and fn_3_C48D0 like the original, but fn_3_C48D0's volatile src reads (needed for its own match) stop the x/y/z loads being hoisted out of the loop, so 3 fewer saved FPRs
#if NONMATCHING
void fn_3_C5DDC(void) {
    C3C2CBss* g = &lbl_3_bss_9D80;
    u32 i;
    StadObj1FD8* e;
    C4724Hdr* h;
    Vec pos;
    if (g->f2 != 0) {
        g->f2 = 0;
        REMOVE_QUEUE_NOARG();
        return;
    }
    for (i = 0; i < g->sprayCount; i++) {
        e = &lbl_3_common_bss_350E4.arr[g->sprayStart + i];
        if (e->x.b.bd == 1 && fn_3_C5CE0(e)) {
            h = fn_80033A24(fn_3_C4724, 0x80, 0, 0x18, 1, (u8)(e->idx + 0x34));
            if (h != NULL) {
                pos = *(Vec*)&e->pos.x;
                fn_3_C48D0(h, &pos);
                h->tex = g->tex;
                h->f24 = 30;
            }
            e->x.b.bd = 2;
            e->visible = 0;
            e->pos.y = lbl_3_rodata_2160[0];
        }
    }
}
#endif

// .text:0x000C625C size:0x174 mapped:0x807052F0
u8 fn_3_C625C(StadObj1FD8* a) {
    Vec pos = *&a->pos;
    Vec d;
    u32 stad;
    u8 v;
    u32 h;
    if (g_Ball.ballState == 1) {
        return 0;
    }
    if ((g_Ball.currentStarSwing2 == 0xB) | (g_Ball.currentStarSwing2 == 0xC)) {
        return 0;
    }
    pos.y *= lbl_3_rodata_20F4;
    PSVECSubtract(&g_Ball.AtBat_Contact_BallPos, &pos, &d);
    if (PSVECMag(&d) <= lbl_3_rodata_2178) {
        stad = g_d_GameSettings.StadiumID;
        if (g_d_GameSettings.GameModeSelected == 6) {
            v = lbl_3_data_84B8[4];
        } else {
            v = lbl_3_data_8404[stad * 0x1E + 4];
        }
        h = sndFXStartEx((u16)(lbl_3_data_81DC[stad] + 2), v, 0x3F, 0);
        if (g_d_GameSettings.GameModeSelected == 6) {
            v = lbl_3_data_84B8[5];
        } else {
            v = lbl_3_data_8404[stad * 0x1E + 5];
        }
        sndFXCtrl(h, 0x5B, v);
        return 1;
    }
    return 0;
}

extern StadPlace18 lbl_3_data_175FC[11];
// .text:0x000C63D0 size:0xDFC mapped:0x80705464
extern const Vec lbl_3_rodata_2074; // (0, 1, 0)
extern const f64 lbl_3_rodata_2180; // 5.0
extern const f32 lbl_3_rodata_2188; // 0.37f
extern const f32 lbl_3_rodata_218C; // 0.0044f
extern f32 lbl_3_data_175F0[];
extern f64 acos(f64);
extern f64 sqrt(f64);
extern s16 fn_3_B7F70(s16 range);
extern s32 fn_80033928(u8 type);
#define GAME_ACTOR(i) (lbl_8036E548.active[i])
// Group B object (set up by fn_3_C8650): waits at its spot until no fielder
// (actors 6..8) is within 5 units, then hops off in a random direction; on
// landing (collision) or when it reaches the ball it bursts (fn_3_C48D0 /
// fn_3_C444C spray) and respawns.
// NONMATCHING ~90%: 890 vs 895 insns, register allocation and switch-tree compare order; inlines fn_3_C5304, fn_3_C48D0, fn_3_C444C and fn_3_C625C like the original
#if NONMATCHING
void fn_3_C63D0(StadObj1FD8* o) {
    Vec up = lbl_3_rodata_2074;
    Vec dir;
    Vec axis;
    Quaternion q;
    VecSrcDst seg;
    CollisionStruct col;
    Vec pos;
    StadPlace18* pb = lbl_3_data_175FC;
    C4724Hdr* h;
    u8 hit = 0;
    u32 i;
    f64 d;
    f32 ang;
    f32 spd;
    u32 stad;
    u8 v;
    u32 snd;

    if (g_GameLogic.gameStatus != 2) {
        if (o->placed == 0) {
            o->pos.x = pb[o->idx].x;
            o->pos.y = pb[o->idx].y;
            o->pos.z = pb[o->idx].z;
            o->x.b.bd = 0;
            CTRLSetTranslation(&o->u.ctrl, o->pos.x, o->pos.y, o->pos.z);
            o->visible = 0;
            pitchingMachinePitching((u8)(o->idx + 0x2A));
            pitchingMachinePitching((u8)(o->idx + 0x34));
            o->placed = 1;
        }
        return;
    }
    o->placed = 0;
    switch (o->x.b.bd) {
    case 0:
        if (o->x.b.bc != 0) {
            o->x.b.bc--;
            break;
        }
        for (i = 6; i < 9; i++) {
            d = pow(GAME_ACTOR(i)->pos.z - o->pos.z, lbl_3_rodata_2118);
            if ((f32)sqrt(pow(GAME_ACTOR(i)->pos.x - o->pos.x, lbl_3_rodata_2118) + d) < lbl_3_rodata_2180) {
                o->pos.x = pb[o->idx].x;
                o->pos.y = pb[o->idx].y;
                o->pos.z = pb[o->idx].z;
                CTRLSetTranslation(&o->u.ctrl, o->pos.x, o->pos.y, o->pos.z);
                return;
            }
        }
        o->x.b.bd = 1;
        o->visible = 1;
        ang = lbl_3_rodata_2158 * (f32)(o->x.b.b8 + fn_3_B7F70((s16)o->x.b.ba)) / lbl_3_rodata_215C;
        spd = lbl_3_data_175F0[fn_3_B7F70(3)];
        o->x.b.v[0] = spd * cos(ang);
        o->x.b.v[1] = lbl_3_rodata_2188;
        o->x.b.v[2] = spd * sin(ang);
        h = fn_80033A24(fn_3_C4F00, 0x80, 0, 7, 1, (u8)(o->idx + 0x2A));
        if (h != NULL) {
            fn_3_C5304(h, o);
            h->tex = lbl_3_bss_9F0C;
        }
        o->x.b.bc = fn_3_B7F70(0xF0) + 1;
        stad = g_d_GameSettings.StadiumID;
        if (g_d_GameSettings.GameModeSelected == 6) {
            v = lbl_3_data_84B8[6];
        } else {
            v = lbl_3_data_8404[stad * 0x1E + 6];
        }
        snd = sndFXStartEx((u16)(lbl_3_data_81DC[stad] + 3), v, 0x3F, 0);
        if (g_d_GameSettings.GameModeSelected == 6) {
            v = lbl_3_data_84B8[7];
        } else {
            v = lbl_3_data_8404[stad * 0x1E + 7];
        }
        sndFXCtrl(snd, 0x5B, v);
        break;
    case 1:
        seg.src = o->pos;
        o->pos.x += o->x.b.v[0];
        o->pos.y -= o->x.b.v[1];
        o->pos.z += o->x.b.v[2];
        seg.dst = o->pos;
        o->x.b.v[1] = o->x.b.v[1] - lbl_3_rodata_218C;
        PSVECNormalize((Vec*)o->x.b.v, &dir);
        PSVECCrossProduct(&dir, &up, &axis);
        C_QUATRotAxisRad(&q, &axis, acos(PSVECDotProduct(&dir, &up)));
        CTRLSetQuat(&o->u.ctrl, q.x, q.y, q.z, q.w);
        if (o->x.b.v[1] < lbl_3_rodata_213C && checkCollision(&seg, &col, 0, 0) != 0) {
            hit = 1;
        }
        if (fn_3_C625C(o)) {
            hit = 2;
        }
        if (hit) {
            pitchingMachinePitching((u8)(o->idx + 0x2A));
            if (hit == 1) {
                h = fn_80033A24(fn_3_C4724, 0x80, 0, 0x18, 1, (u8)(o->idx + 0x34));
                if (h != NULL) {
                    pos = o->pos;
                    fn_3_C48D0(h, &pos);
                    h->tex = lbl_3_bss_9F0C;
                    h->f24 = 30;
                }
            } else if (hit == 2) {
                h = fn_80033A24(fn_3_C4724, 0x80, 0, 0x18, 1, (u8)(o->idx + 0x34));
                if (h != NULL) {
                    fn_3_C444C(h, o);
                    h->tex = lbl_3_bss_9F0C;
                    h->f24 = 30;
                }
            }
            o->x.b.bd = 3;
            o->visible = 0;
            o->pos.y = lbl_3_rodata_2160[0];
        }
        break;
    case 2:
        if (fn_80033928((u8)(o->idx + 0x34)) == 0) {
            o->x.b.bd = 3;
        }
        break;
    case 3:
        o->x.b.bd = 0;
        o->pos.x = pb[o->idx].x;
        o->pos.y = pb[o->idx].y;
        o->pos.z = pb[o->idx].z;
        o->x.b.v[1] = lbl_3_rodata_2188;
        o->visible = 0;
        o->x.b.bc = fn_3_B7F70(0xF0) + 1;
        CTRLSetRotation(&o->u.ctrl, lbl_3_rodata_213C, pb[o->idx].rotY, lbl_3_rodata_213C);
        break;
    }
    CTRLSetTranslation(&o->u.ctrl, o->pos.x, o->pos.y, o->pos.z);
}
#endif

// .text:0x000C71CC size:0x278 mapped:0x80706260
extern f32 lbl_3_data_175F0[];
extern const f64 lbl_3_rodata_2190;
extern const f32 lbl_3_rodata_2198;
extern const f32 lbl_3_rodata_219C;
extern const f32 lbl_3_rodata_21A0;
void fn_3_C71CC(s32* a, s32* b) {
    u32 v;
    StadPlace18* e;
    f64 D;
    C42A4Bss* g;
    f32 y;
    s32 off;
    Mtx m;
    f32 d;
    StadObj1FD8* c;
    s32 k;
    s32 j;
    GameControl t;
    g = &lbl_3_common_bss_350E4;
    D = lbl_3_rodata_2190 * lbl_3_rodata_2198 + lbl_3_rodata_219C;
    for (k = 0; k < 5; k++) {
        v = (u16)(g->p40[*a - 1] + g->p3C[*a - 1]);
        g->p40[*a] = v;
        ((void (*)(void))fn_3_B8574)();
        e = lbl_3_data_175FC;
        off = v * 4;
        for (j = 0; j < 10; e++, j++) {
            if (k == e->f12 && e->type != 7) {
                if (lbl_3_common_bss_350E4.arr[*b].animated) {
                    *(s32*)((u8*)g->p44 + off) = *b;
                    g->p3C[*a] += 1;
                    c = &lbl_3_common_bss_350E4.arr[*b];
                    off += 4;
                    t = c->u.gctrl;
                    CTRLBuildMatrix(&c->u.ctrl, m);
                    fn_3_B8464(m, c->anim);
                    y = (f32)D;
                    d = lbl_3_data_175F0[2] * lbl_3_rodata_21A0;
                    CTRLSetTranslation(&t.base, d + e->x, y + e->y, d + e->z);
                    CTRLBuildMatrix(&t.base, m);
                    fn_3_B8464(m, c->anim);
                    CTRLSetTranslation(&t.base, e->x - d, y + e->y, e->z - d);
                    CTRLBuildMatrix(&t.base, m);
                    fn_3_B8464(m, c->anim);
                    *b += 1;
                }
            }
        }
        if (g->p3C[*a] != 0) {
            fn_3_B8414(g->p48 + *a * 0x18, g->p48 + (*a * 2 + 1) * 0xC);
            *a += 1;
        }
    }
}

// .text:0x000C7444 size:0x58 mapped:0x807064D8
void fn_3_C7444(StadObj1FD8* a) {
    DisplayStateList* p = PTR32_GET(DisplayStateList, a->model->actor->boneArray[13]->dispObj->displayData->displayStateList);
    switch ((s8)a->x.a.state) {
    case 0:
        p->setting = p->setting & ~0x1FFF;
        p->setting = p->setting | 2;
        break;
    default:
        p->setting = p->setting & ~0x1FFF;
        break;
    }
}

// .text:0x000C749C size:0x11C mapped:0x80706530
void fn_3_C749C(void) {
    s32 i;
    s32 stad;
    u8 v;
    u32 h;
    i = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy ? 3 : 2;
    lbl_3_bss_9E48[i] = 1;
    lbl_3_bss_9DE8[i].x = g_Ball.AtBat_Contact_BallPos.x;
    lbl_3_bss_9DE8[i].y = -g_Ball.AtBat_Contact_BallPos.y;
    lbl_3_bss_9DE8[i].z = g_Ball.AtBat_Contact_BallPos.z;
    stad = g_d_GameSettings.StadiumID;
    if (g_d_GameSettings.GameModeSelected == 6) {
        v = lbl_3_data_84B8[8];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + 8];
    }
    h = sndFXStartEx((u16)(lbl_3_data_81DC[stad] + 4), v, 0x3F, 0);
    if (g_d_GameSettings.GameModeSelected == 6) {
        v = lbl_3_data_84B8[9];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + 9];
    }
    sndFXCtrl(h, 0x5B, v);
}

// .text:0x000C75B8 size:0x1F4 mapped:0x8070664C
u32 fn_3_C75B8(void* hv) {
    C4724Hdr* h = hv;
    C4724P* p;
    s32 n = -h->f24;
    fn_80033620(h);
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    p = h->head;
    do {
        if (p->s48 != 0) {
            p->s48 -= (LBL_80366158_U8(0x28) == 0);
        } else if (p->s4A != 0) {
            fn_8003403C(p->f38, p->f3C);
            fn_80033CC8(p, h->tex);
            if (LBL_80366158_U8(0x28) == 0) {
                if (p->f38 < p->f1C) {
                    p->f38 += p->f1C / lbl_3_rodata_21A4;
                    p->f3C += p->f1C / lbl_3_rodata_21A4;
                }
                p->x += p->vx;
                p->z += p->vz;
                p->y = (p->vy + h->f18->y) - 5.0 * pow(2.0, (f64)n);
                if (30 - h->f24 >= 16) {
                    p->a43 = (f32)p->a43 - lbl_3_rodata_21A8;
                }
            }
        }
        p = p->next;
    } while (p != NULL);
    h->f24 -= (LBL_80366158_U8(0x28) == 0);
    return !h->f24;
}

// .text:0x000C77AC size:0x260 mapped:0x80706840
// NONMATCHING 99%: one 'fmuls f0,f25,f0' operand order (we emit f0,f25); const-left source order changes the hoisted-const layout instead
#if NONMATCHING
void fn_3_C77AC(void* hv, StadObj1FD8* b) {
    u32 ang;
    C4724P* p;
    C4724Hdr* h = hv;
    f32 a, fa;
    u32 i;
    p = h->head;
    h->f18 = &b->pos;
    h->f20 = b;
    h->tex = lbl_3_bss_9F0C;
    h->f24 = 30;
    i = 0;
    ang = 0;
    while (p != NULL) {
        p->f38 = p->f3C = lbl_3_rodata_213C;
        p->f1C = lbl_3_rodata_21AC - (f32)(rand() % 3);
        fa = (f32)ang + lbl_3_data_17514[b->idx].rotY;
        a = (fa * lbl_3_rodata_2158) / lbl_3_rodata_215C;
        p->vx = 0.3499999940395355 * cos(a);
        p->vy = (f32)-(rand() % 3);
        p->vz = 0.3499999940395355 * sin(a);
        ang += 30;
        p->x = h->f18->x;
        p->z = h->f18->z;
        p->s48 = i >> 2;
        i++;
        p->f4D = 0x1C;
        p->f4E = 0;
        p->a42 = 0x7F;
        p->a41 = 0x7F;
        p->a40 = 0x7F;
        p->a43 = 0x99;
        p->s4A = 1;
        p = p->next;
    }
}
#endif

// .text:0x000C7A0C size:0x650 mapped:0x80706AA0
// Rising/falling obstacle (state machine in e->state): rests at its table
// height, rises when a ball is about to hit it, drops with a splash + sound,
// waits, then rises back.
extern f32 lbl_3_data_17508[];
extern s16 fn_3_B7F70(s16 range);
extern s32 fn_3_8BBC4(s32 id, f32* pos, f32* dir, s32 type);
extern void* memcpy(void*, const void*, size_t);
extern f64 sqrt(f64);
extern void pitchingMachinePitching(u8);
extern const f32 lbl_3_rodata_21B8; // 25.0f
extern const f32 lbl_3_rodata_21BC; // 23.0f
extern const f32 lbl_3_rodata_21C0; // 3.0f
extern const f64 lbl_3_rodata_21C8; // 2.5
extern const f64 lbl_3_rodata_21D0; // 0.25
extern const f64 lbl_3_rodata_21D8; // -5.0
extern const f64 lbl_3_rodata_21E8; // 0.2
extern f32 lbl_3_rodata_21E0;        // -5.0f
// The original expands fn_3_C77AC into fn_3_C7A0C. CW only does that with a larger inline size
// limit (with -inline deferred, the value in effect at the end of the file counts) and only from a
// copy that is always visible (fn_3_C77AC itself is NONMATCHING).
#pragma inline_max_size(100000)
// Inline copy of fn_3_C77AC.
static inline void fn_3_C77AC_inline(void* hv, StadObj1FD8* b) {
    u32 ang;
    C4724P* p;
    C4724Hdr* h = hv;
    f32 a, fa;
    u32 i;
    p = h->head;
    h->f18 = &b->pos;
    h->f20 = b;
    h->tex = lbl_3_bss_9F0C;
    h->f24 = 30;
    i = 0;
    ang = 0;
    while (p != NULL) {
        p->f38 = p->f3C = lbl_3_rodata_213C;
        p->f1C = lbl_3_rodata_21AC - (f32)(rand() % 3);
        fa = (f32)ang + lbl_3_data_17514[b->idx].rotY;
        a = (fa * lbl_3_rodata_2158) / lbl_3_rodata_215C;
        p->vx = 0.3499999940395355 * cos(a);
        p->vy = (f32)-(rand() % 3);
        p->vz = 0.3499999940395355 * sin(a);
        ang += 30;
        p->x = h->f18->x;
        p->z = h->f18->z;
        p->s48 = i >> 2;
        i++;
        p->f4D = 0x1C;
        p->f4E = 0;
        p->a42 = 0x7F;
        p->a41 = 0x7F;
        p->a40 = 0x7F;
        p->a43 = 0x99;
        p->s4A = 1;
        p = p->next;
    }
}

// NONMATCHING 98%: register numbering; the inlined fn_3_C77AC copy carries its fmuls operand-order difference
#if NONMATCHING
void fn_3_C7A0C(StadObj1FD8* e) {
    Vec pos;
    f64 d;
    f32 x;
    C4724Hdr* h;
    if (g_GameLogic.gameStatus != 2) {
        if (e->placed == 0) {
            e->pos.y = lbl_3_data_17514[e->idx].y;
            e->x.a.state = 0;
            e->x.a.armed = 1;
            CTRLSetTranslation(&e->u.ctrl, e->pos.x, e->pos.y, e->pos.z);
            pitchingMachinePitching((u8)(e->idx + 0x3E));
            e->placed = 1;
        }
        if (g_GameLogic.gameStatus == 0) {
            e->x.a.speed = lbl_3_data_17508[fn_3_B7F70(3)];
        }
        return;
    }
    e->placed = 0;
    switch (e->x.a.state) {
    case 0:
        if (e->x.a.armed != 0) {
            if (g_Ball.ballState != 0) {
                e->x.a.armed = 0;
            } else if (g_Ball.physicsSubstruct.velocity.z < lbl_3_rodata_213C) {
                e->x.a.armed = 0;
            } else if (g_Ball.deadBallReason != 0) {
                e->x.a.armed = 0;
            } else {
                x = g_Ball.physicsSubstruct.velocity.x / g_Ball.physicsSubstruct.velocity.z * (e->pos.z - g_Ball.AtBat_Contact_BallPos.z) + g_Ball.AtBat_Contact_BallPos.x;
                if (x < e->pos.x - lbl_3_rodata_21B8 || x > lbl_3_rodata_21B8 + e->pos.x) {
                    e->x.a.armed = 0;
                } else {
                    d = pow(e->pos.y + g_Ball.AtBat_Contact_BallPos.y, lbl_3_rodata_2118);
                    d = pow(e->pos.x - g_Ball.AtBat_Contact_BallPos.x, lbl_3_rodata_2118) + d;
                    if ((f32)sqrt(pow(e->pos.z - g_Ball.AtBat_Contact_BallPos.z, lbl_3_rodata_2118) + d) < lbl_3_rodata_21BC &&
                        g_Ball.AtBat_Contact_BallPos.y < lbl_3_rodata_21C0 - e->pos.y) {
                        e->x.a.state = 1;
                    }
                }
            }
        }
        break;
    case 1:
        d = lbl_3_data_17514[e->idx].y - lbl_3_rodata_21C8;
        if (e->pos.y <= d) {
            e->pos.y = d;
            e->x.a.state = 2;
        } else {
            e->pos.y = e->pos.y - lbl_3_rodata_21D0;
        }
        break;
    case 2:
        e->pos.y += e->x.a.speed;
        if (e->pos.y >= lbl_3_rodata_21D8) {
            e->pos.y = lbl_3_rodata_21E0;
            memcpy(&pos, &e->pos, sizeof(Vec));
            e->x.a.state = 3;
            e->x.a.timer = 0;
            lbl_3_bss_9D81 = 1;
            fn_800528AC(fn_3_C3A38);
            fn_3_8BBC4(lbl_3_data_81DC[g_d_GameSettings.StadiumID] + 5, (f32*)&pos, NULL, 9);
        }
        if (lbl_3_rodata_2148 * e->x.a.speed + e->pos.y >= lbl_3_rodata_21D8) {
            h = fn_80033A24(fn_3_C75B8, 0x80, 0, 0xC, 1, (u8)(e->idx + 0x3E));
            if (h != NULL) {
                fn_3_C77AC_inline(h, e);
            }
        }
        break;
    case 3:
        if (e->x.a.timer++ > 40) {
            e->x.a.state = 4;
            e->x.a.timer = 0;
        }
        break;
    case 4:
        if (e->pos.y <= lbl_3_data_17514[e->idx].y) {
            e->pos.y = lbl_3_data_17514[e->idx].y;
            e->x.a.state = 0;
        } else {
            e->pos.y = e->pos.y - lbl_3_rodata_21E8;
        }
        break;
    }
    CTRLSetTranslation(&e->u.ctrl, e->pos.x, e->pos.y, e->pos.z);
}
#endif

typedef struct { u32 w[17]; } C42A4Cpy;
#ifndef TARGET_PC
extern u8 lbl_3_bss_9DE4[];
#endif
extern StadPlace14 lbl_3_data_17514[11];
extern f32 lbl_3_rodata_21E0;
// .text:0x000C805C size:0x1E0 mapped:0x807070F0
void fn_3_C805C(s32* a, s32* b) {
    Mtx m;
    C42A4Cpy cpy;
    C42A4Bss* g;
    StadPlace14* e;
    s32 off;
    s32 k;
    s32 j;
    u32 v;
    StadObj1FD8* c;
    s32 idx;
    g = &lbl_3_common_bss_350E4;
    for (k = 0; k < 5; k++) {
        v = (u16)(g->p40[*a - 1] + g->p3C[*a - 1]);
        g->p40[*a] = v;
        ((void (*)(void))fn_3_B8574)();
        e = lbl_3_data_17514;
        off = v * 4;
        for (j = 0; j < 10; e++, j++) {
            if (k == e->f12 && e->type != 7) {
                if (lbl_3_common_bss_350E4.arr[j + lbl_3_bss_9DE4[0]].animated) {
                    idx = j + lbl_3_bss_9DE4[0];
                    *(s32*)((u8*)g->p44 + off) = idx;
                    g->p3C[*a] += 1;
                    c = &lbl_3_common_bss_350E4.arr[j + lbl_3_bss_9DE4[0]];
                    off += 4;
                    cpy = *(C42A4Cpy*)c;
                    CTRLBuildMatrix(&c->u.ctrl, m);
                    fn_3_B8464(m, c->anim);
                    CTRLSetTranslation((Control*)&cpy, ((f32*)e)[0], lbl_3_rodata_21E0, ((f32*)e)[2]);
                    CTRLBuildMatrix((Control*)&cpy, m);
                    fn_3_B8464(m, c->anim);
                    *b += 1;
                }
            }
        }
        if (g->p3C[*a] != 0) {
            fn_3_B8414(g->p48 + *a * 0x18, g->p48 + (*a * 2 + 1) * 0xC);
            *a += 1;
        }
    }
}

// .text:0x000C823C size:0x78 mapped:0x807072D0
// Builds object idx's matrix into out (dropping it slightly while in state 5)
// and returns its model.
void* fn_3_C823C(s32 idx, Mtx out) {
    StadObj1FD8* p = &lbl_3_common_bss_350E4.arr[idx];
    CTRLBuildMatrix(&p->u.ctrl, out);
    if (p->type == 5) {
        out[1][3] = -0.002f;
    }
    return lbl_3_common_bss_350E4.arr[idx].anim;
}

// Inline copies of fn_3_C42A4 and fn_3_C805C (the original expands both in fn_3_C82B4).
static inline void fn_3_C42A4_inline(s32* a, s32* b) {
    Mtx m;
    C42A4Bss* g;
    StadPlace14* e;
    s32 off;
    s32 k;
    s32 j;
    u32 v;
    StadObj1FD8* c;
    s32 idx;
    g = &lbl_3_common_bss_350E4;
    for (k = 0; k < 5; k++) {
        v = (u16)(g->p40[*a - 1] + g->p3C[*a - 1]);
        g->p40[*a] = v;
        ((void (*)(void))fn_3_B8574)();
        e = lbl_3_data_17704.place;
        off = v * 4;
        for (j = 0; j < 10; e++, j++) {
            if (k == e->f12 && e->type != 7) {
                if (lbl_3_common_bss_350E4.arr[j + lbl_3_bss_9DE0[0]].animated) {
                    idx = j + lbl_3_bss_9DE0[0];
                    *(s32*)((u8*)g->p44 + off) = idx;
                    off += 4;
                    g->p3C[*a] += 1;
                    c = &lbl_3_common_bss_350E4.arr[j + lbl_3_bss_9DE0[0]];
                    CTRLBuildMatrix(&c->u.ctrl, m);
                    fn_3_B8464(m, c->anim);
                    m[1][3] = m[1][3] * lbl_3_rodata_2154;
                    fn_3_B8464(m, c->anim);
                    *b += 1;
                }
            }
        }
        if (g->p3C[*a] != 0) {
            fn_3_B8414(g->p48 + *a * 0x18, g->p48 + (*a * 2 + 1) * 0xC);
            *a += 1;
        }
    }
}

static inline void fn_3_C805C_inline(s32* a, s32* b) {
    Mtx m;
    C42A4Cpy cpy;
    C42A4Bss* g;
    StadPlace14* e;
    s32 off;
    s32 k;
    s32 j;
    u32 v;
    StadObj1FD8* c;
    s32 idx;
    g = &lbl_3_common_bss_350E4;
    for (k = 0; k < 5; k++) {
        v = (u16)(g->p40[*a - 1] + g->p3C[*a - 1]);
        g->p40[*a] = v;
        ((void (*)(void))fn_3_B8574)();
        e = lbl_3_data_17514;
        off = v * 4;
        for (j = 0; j < 10; e++, j++) {
            if (k == e->f12 && e->type != 7) {
                if (lbl_3_common_bss_350E4.arr[j + lbl_3_bss_9DE4[0]].animated) {
                    idx = j + lbl_3_bss_9DE4[0];
                    *(s32*)((u8*)g->p44 + off) = idx;
                    g->p3C[*a] += 1;
                    c = &lbl_3_common_bss_350E4.arr[j + lbl_3_bss_9DE4[0]];
                    off += 4;
                    cpy = *(C42A4Cpy*)c;
                    CTRLBuildMatrix(&c->u.ctrl, m);
                    fn_3_B8464(m, c->anim);
                    CTRLSetTranslation((Control*)&cpy, ((f32*)e)[0], lbl_3_rodata_21E0, ((f32*)e)[2]);
                    CTRLBuildMatrix((Control*)&cpy, m);
                    fn_3_B8464(m, c->anim);
                    *b += 1;
                }
            }
        }
        if (g->p3C[*a] != 0) {
            fn_3_B8414(g->p48 + *a * 0x18, g->p48 + (*a * 2 + 1) * 0xC);
            *a += 1;
        }
    }
}

// .text:0x000C82B4 size:0x39C mapped:0x80707348
extern void* _OSAllocFromHeap(s32 heap, s32 size);
// Builds the object groups: allocates the batch buffers once, then lets
// fn_3_C805C and fn_3_C42A4 fill one group per pass.
// NONMATCHING 95%: register allocation and a 0x10 smaller frame (the inlined copies' locals share slots)
#if NONMATCHING
void fn_3_C82B4(void) {
    C42A4Bss* g = &lbl_3_common_bss_350E4;
    s32 n;
    s32 size;
    s32 groups;
    s32 objs;
    size = g->count * 2 + g->count * 4 + g->count * 0x18 + g->count * 4;
    if (g->p48 == NULL) {
        g->p48 = _OSAllocFromHeap(4, size);
        n = g->count;
        lbl_3_common_bss_350E4.p3C = (u32*)(g->p48 + n * 0x18);
        lbl_3_common_bss_350E4.p44 = lbl_3_common_bss_350E4.p3C + n;
        lbl_3_common_bss_350E4.p40 = (u16*)(lbl_3_common_bss_350E4.p44 + n);
    }
    memset(g->p48, 0, size);
    groups = 0;
    objs = 0;
    fn_3_C805C_inline(&groups, &objs);
    fn_3_C42A4_inline(&groups, &objs);
    lbl_3_common_bss_350E4.groups = groups;
}
#endif

// .text:0x000C8650 size:0xD2C mapped:0x807076E4
#define ACTOR_TABLE (lbl_8036E548.slots6C)
extern void fn_3_B939C(void);
extern void fn_3_B9D68(u8* ids, s32 n, void** files, s32* out);
extern void fn_3_B97C8(void* fn);
extern void fn_800BD548(ActorObject* obj, u8 numLights, ...);
extern void fn_80035750(void* data, void* tex, s16 id);
extern void fn_80034E20(void* group, void* descs);
extern u8 lbl_3_data_10C1C[];
// Stadium setup: loads the actors/animations from `files`, lays out the object
// slots (2 fixed ones, then groups A, B and C from the placement tables) and
// starts the stadium tasks.
// NONMATCHING ~90%: 834 vs 843 insns, mostly register allocation; the original reaches the placement tables and 9D98/9D9C through the lbl_3_data_17508 / lbl_3_bss_9D80 bases
#if NONMATCHING
void fn_3_C8650(void** files) {
    C42A4Bss* g = &lbl_3_common_bss_350E4;
    C3C2CBss* bss = &lbl_3_bss_9D80;
    StadPlace14* pa = lbl_3_data_17514;
    StadPlace18* pb = lbl_3_data_175FC;
    StadPlace14* pc = lbl_3_data_17704.place;
    StadObj1FD8* o;
    s32* idx;
    u32 nB;
    u32 nActors;
    u32 i;
    s32 j;
    s32 m;
    u32 k;
    u32 k2;
    s32 used;
    u8 stop;

    g->f18 = fn_3_B939C;
    idx = _OSAllocFromHeap(4, 0x40);
    g->fileIdx = idx;
    fn_3_B9D68(lbl_3_data_17704.fileIdx, 16, files, idx);
    bss->tex = STADIUM_FILE(files, 0);

    for (nB = 0; nB < 10; nB++) {
        if (pb[nB].type == 7) {
            break;
        }
    }
    nActors = nB + 5;
    g->nActors = nActors;
    ACTOR_TABLE = ActorObjectInitTable((u16)nActors);
    fn_800BDC88(ACTOR_TABLE, 0, 0, STADIUM_FILE(files, idx[1]), NULL, NULL);
    fn_800BDC88(ACTOR_TABLE, 1, 1, STADIUM_FILE(files, idx[2]), NULL, NULL);
    fn_800BDC88(ACTOR_TABLE, 2, 2, STADIUM_FILE(files, idx[3]), NULL, NULL);
    k = 3;
    for (i = 0; i < nB; i++, k++) {
        fn_800BDC88(ACTOR_TABLE, (u16)k, (u16)k, STADIUM_FILE(files, idx[4]), NULL, NULL);
    }
    fn_800BDC88(ACTOR_TABLE, (u16)k, (u16)k, STADIUM_FILE(files, idx[5]), NULL, NULL);
    k2 = k + 1;
    fn_800BDC88(ACTOR_TABLE, (u16)k2, (u16)k2, STADIUM_FILE(files, idx[6]), NULL, NULL);
    for (i = 0; i < nActors; i++) {
        fn_800BD548(&ACTOR_TABLE->objects[i], 4, g->lights[0], g->lights[1], g->lights[2], g->lights[3]);
    }
    fn_80025DDC(STADIUM_FILE(files, idx[10]));
    for (i = 0; i < nB; i++) {
        fn_80025C58(STADIUM_FILE(files, idx[10]), (ShapeModel**)&ACTOR_TABLE->objects[i + 3].actor);
    }
    bss->anim130.set = STADIUM_FILE(files, idx[11]);
    fn_80025FFC(STADIUM_FILE(files, idx[10]), &bss->anim130);
    fn_80025EEC(&bss->anim130, 0, 0);
    fn_80025DDC(STADIUM_FILE(files, idx[12]));
    fn_80025C58(STADIUM_FILE(files, idx[12]), (ShapeModel**)&ACTOR_TABLE->objects[1].actor);
    bss->animD4.set = STADIUM_FILE(files, idx[13]);
    fn_80025FFC(STADIUM_FILE(files, idx[12]), &bss->animD4);
    fn_80025EEC(&bss->animD4, 0, 0);
    fn_80035750(STADIUM_FILE(files, idx[15]), STADIUM_FILE(files, idx[14]), 5);
    bss->fD0 = fn_800B0A5C_insertQueue(fn_3_C3C2C, 2);
    fn_80034E20(bss->fD0, lbl_3_data_10C1C);

    g->count = 32;
#ifdef PORT_LP64
    /* 32 stadium objects (0x1D00 = 32 * 0xE8 on GameCube) at the PC stride */
    g->arr = _OSAllocFromHeap(0x20, 32 * STADIUM_OBJ_SIZE);
    memset(g->arr, 0, 32 * STADIUM_OBJ_SIZE);
    g->arr2 = _OSAllocFromHeap(0x20, 32 * STADIUM_OBJ_SIZE);
    memset(g->arr2, 0, 32 * STADIUM_OBJ_SIZE);
#else
    g->arr = _OSAllocFromHeap(0x20, 0x1D00);
    memset(g->arr, 0, 0x1D00);
    g->arr2 = _OSAllocFromHeap(0x20, 0x1D00);
    memset(g->arr2, 0, 0x1D00);
#endif

    // slot 0: fn_3_C4068
    o = (StadObj1FD8*)g->arr;
    o[0].type = 0;
    o[0].model = &ACTOR_TABLE->objects[0];
    o[0].anim = NULL;
    o[0].update = fn_3_C4068;
    o[0].hit = NULL;
    o[0].visible = 1;
    o[0].animated = (o[0].visible && o[0].anim != NULL);
    o[0].u.ctrl.type = 0;
    CTRLSetTranslation(&o[0].u.ctrl, 0.0f, 0.0f, 0.0f);
    CTRLSetRotation(&o[0].u.ctrl, 0.0f, 0.0f, 0.0f);
    o[0].b5 = 0;
    o[0].alpha = 0xFF;
    o[0].animPlayer = NULL;
    o[0].draw = NULL;
    o[0].f94 = 0;
    o[0].f96 = -1;
    o[0].f98 = 0;
    // slot 1: fn_3_C3F70
    o[1].type = 1;
    o[1].model = &ACTOR_TABLE->objects[1];
    o[1].anim = NULL;
    o[1].update = fn_3_C3F70;
    o[1].hit = NULL;
    o[1].visible = 1;
    o[1].animated = (o[1].visible && o[1].anim != NULL);
    o[1].u.ctrl.type = 0;
    CTRLSetTranslation(&o[1].u.ctrl, 0.0f, 0.0f, 0.0f);
    CTRLSetRotation(&o[1].u.ctrl, 0.0f, 0.0f, 0.0f);
    o[1].b5 = 0;
    o[1].alpha = 0xFF;
    o[1].animPlayer = &bss->animD4;
    o[1].draw = NULL;
    o[1].f94 = 0;
    o[1].f96 = -1;
    o[1].f98 = 1;
    o += 2;
    used = 2;

    if (g_d_GameSettings.GameModeSelected != 7) {
        // group A: fn_3_C7A0C obstacles
        bss->aCount = 0;
        bss->aStart = used;
        stop = 0;
        for (j = 0; j < 10; j++) {
            if (pa[j].type == 7) {
                stop = 1;
            }
            if (stop) {
                for (m = j; m < 11; m++) {
                    pa[m].type = 7;
                }
                break;
            }
            o->idx = j;
            o->type = pa[j].type;
            o->model = &ACTOR_TABLE->objects[2];
            o->anim = STADIUM_FILE(files, idx[7]);
            o->update = fn_3_C7A0C;
            o->hit = fn_3_C749C;
            o->visible = pa[j].visible;
            o->animated = (o->visible && o->anim != NULL);
            o->u.ctrl.type = 0;
            CTRLSetTranslation(&o->u.ctrl, pa[j].x, pa[j].y, pa[j].z);
            CTRLSetRotation(&o->u.ctrl, 0.0f, pa[j].rotY, 0.0f);
            o->pos.x = pa[j].x;
            o->pos.y = pa[j].y;
            o->pos.z = pa[j].z;
            o->x.a.speed = 0.0f;
            o->x.a.state = 0;
            o->x.a.timer = 0;
            o->x.a.armed = 1;
            o->b5 = 0;
            o->alpha = 0xFF;
            o->draw = fn_3_C7444;
            o->animPlayer = NULL;
            o->f94 = 0;
            o->f96 = -1;
            o->f98 = 1;
            o->f9A = 1;
            o++;
            used++;
            bss->aCount++;
        }
        // group B: fn_3_C63D0 objects that burst into spray (fn_3_C5DDC)
        stop = 0;
        bss->sprayCount = 0;
        bss->sprayStart = used;
        for (j = 0; j < 10; j++) {
            if (pb[j].type == 7) {
                stop = 1;
            }
            if (stop) {
                for (m = j; m < 11; m++) {
                    pb[m].type = 7;
                }
                break;
            }
            o->idx = j;
            o->type = pb[j].type;
            o->model = &ACTOR_TABLE->objects[j + 3];
            o->anim = NULL;
            o->update = fn_3_C63D0;
            o->hit = NULL;
            o->visible = pb[j].visible;
            o->animated = (o->visible && o->anim != NULL);
            o->x.b.bc = fn_3_B7F70(0xF0) + 1;
            o->x.b.bd = 0;
            o->x.b.v[2] = o->x.b.v[1] = o->x.b.v[0] = 0.0f;
            o->x.b.b8 = pb[j].f14;
            o->x.b.ba = pb[j].f16;
            o->u.ctrl.type = 0;
            CTRLSetTranslation(&o->u.ctrl, pb[j].x, pb[j].y, pb[j].z);
            CTRLSetRotation(&o->u.ctrl, 0.0f, pb[j].rotY, 0.0f);
            o->pos.x = pb[j].x;
            o->pos.y = pb[j].y;
            o->pos.z = pb[j].z;
            o->b5 = 1;
            o->alpha = 0xFF;
            o->animPlayer = &bss->anim130;
            o->draw = fn_3_C56E8;
            o->draw2 = fn_3_C54D0;
            o->f94 = 1;
            o->f96 = 4;
            o->f98 = 1;
            o->f9A = 1;
            o++;
            used++;
            bss->sprayCount++;
        }
        bss->f2 = 0;
        fn_800B0A5C_insertQueue(fn_3_C5DDC, 0x6001);
        // group C: fn_3_C414C targets
        stop = 0;
        bss->cCount = 0;
        bss->cStart = used;
        for (j = 0; j < 10; j++) {
            if (pc[j].type == 7) {
                stop = 1;
            }
            if (stop) {
                for (m = j; m < 11; m++) {
                    pc[m].type = 7;
                }
                break;
            }
            o->idx = j;
            o->type = pc[j].type;
            if (o->type == 4) {
                o->model = &ACTOR_TABLE->objects[k];
                o->anim = STADIUM_FILE(files, idx[8]);
            } else {
                o->model = &ACTOR_TABLE->objects[k2];
                o->anim = STADIUM_FILE(files, idx[9]);
            }
            o->update = NULL;
            o->hit = fn_3_C414C;
            o->visible = pc[j].visible;
            o->animated = (o->visible && o->anim != NULL);
            o->u.ctrl.type = 0;
            CTRLSetTranslation(&o->u.ctrl, pc[j].x, pc[j].y, pc[j].z);
            CTRLSetRotation(&o->u.ctrl, 0.0f, pc[j].rotY, 0.0f);
            o->b5 = 1;
            o->alpha = 0xFF;
            o->animPlayer = NULL;
            o->draw = fn_3_C40EC;
            o->f94 = 0;
            o->f96 = -1;
            o->f98 = 1;
            o++;
            used++;
            bss->cCount++;
        }
    }
    // clear the remaining slots
    for (m = used; m < g->count; m++, o++) {
        o->type = 0;
        o->model = NULL;
        o->anim = NULL;
        o->update = NULL;
        o->hit = NULL;
        o->visible = 0;
        o->animated = 0;
        o->b5 = 0;
        o->u.ctrl.type = 0;
        CTRLSetTranslation(&o->u.ctrl, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(&o->u.ctrl, 0.0f, 0.0f, 0.0f);
        o->alpha = 0;
        o->animPlayer = NULL;
        o->f94 = 0;
        o->f96 = -1;
    }
    g->p48 = NULL;
    if (g_d_GameSettings.GameModeSelected != 7) {
        fn_3_C82B4();
    }
    fn_800528AC(fn_3_C3A38);
    fn_3_C39C8();
    fn_3_C1974(STADIUM_FILE(files, idx[0]));
    fn_3_B97C8(fn_3_C2974);
}
#endif


