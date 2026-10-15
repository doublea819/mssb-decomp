#include "game/sta_c2.h"
#define REP_HEADER_FN repHeader_sta_c2
#include "header_rep_inline.h"
#include "Dolphin/os.h"
#include "Dolphin/stl.h"
#include "Dolphin/vec.h"
#include "C3/control.h"
#include "game/rep_2998.h"
#include "game/UnknownHomes_Game.h"
#include "static/GameSettings.h"
#include "main/file_80008E00.h"
#include "main/file_80011640.h"
#include "Dolphin/GX.h"
#include "C3/geoPalette.h"
#include "main/file_8000F150.h"
#include "main/file_80069BDC.h"
#include "C3/unktypes.h"

extern InMemFielderType g_Fielders[9];
extern StadiumObjList lbl_3_common_bss_350E4;
extern char lbl_3_rodata_286C[];
extern char lbl_3_rodata_2878[];
#include "Dolphin/mtx.h"
#include "Dolphin/mtxext.h"
#pragma dont_inline on
extern const f64 lbl_3_rodata_2800;
extern const f32 lbl_3_rodata_2664;
extern const f32 lbl_3_rodata_280C[];
extern f64 lbl_3_rodata_2668;
extern void fn_8004C094(void*);
extern Vec lbl_3_rodata_2580;
extern Vec lbl_3_rodata_258C;
extern f32 lbl_3_rodata_265C;
extern f32 lbl_3_rodata_2670;
extern f32 lbl_3_rodata_2660;
extern f32 lbl_3_rodata_269C;
extern f32 lbl_3_rodata_26A4;
extern f32 lbl_3_rodata_26A8;
extern f32 lbl_3_rodata_26AC;
extern f32 lbl_3_rodata_26B0;
extern f32 lbl_3_rodata_26B8;
// .bss (laid out last-defined-first)
static void* lbl_3_bss_ADD0[0xC];
static RopeNode lbl_3_bss_A8D0[20];
static CC438Cfg lbl_3_bss_A8A8;
static SpaniGroup* lbl_3_bss_A8A4;
static u8 lbl_3_bss_A898[0xC];
static Vec lbl_3_bss_A820[0xA];
static u8 lbl_3_bss_A81C;
static ShapeAnimPlayer lbl_3_bss_A034[22];
static f32 lbl_3_bss_A030;
static u8 lbl_3_bss_A02D;
static u8 lbl_3_bss_A02C;
static u8 lbl_3_bss_A02B;
static u8 lbl_3_bss_A02A;
static u8 lbl_3_bss_A029; // unused (alignment gap in the original)
static u8 lbl_3_bss_A028; // unused (alignment gap in the original)
static u8 lbl_3_bss_A027;
static u8 lbl_3_bss_A026;
static u8 lbl_3_bss_A025;
static u8 lbl_3_bss_A024;
static u8 lbl_3_bss_A023;
static u8 lbl_3_bss_A022;
static u8 lbl_3_bss_A021; // unused (alignment gap in the original)
static u8 lbl_3_bss_A020;
static u8* lbl_3_bss_A01C;
static u8 lbl_3_bss_A01B; // unused (alignment gap in the original)
static u8 lbl_3_bss_A01A; // unused (alignment gap in the original)
static u8 lbl_3_bss_A019; // unused (alignment gap in the original)
static u8 lbl_3_bss_A018[0x1];
// Some functions reach the .bss block above from its base lbl_3_bss_A018 (one address
// for all of it). The matching build keeps that; the port uses the objects themselves.
#if NONMATCHING
#define C2_BSS(T, sym, base, off) ((T*)&(sym))
#else
#define C2_BSS(T, sym, base, off) ((T*)((base) + (off)))
#endif
extern void fn_3_8B890(s32);
extern s32 lbl_3_data_182C4;
extern f32 lbl_3_rodata_269C;
extern f32 lbl_3_rodata_26A4;
extern f32 lbl_3_rodata_26A8;
extern f32 lbl_3_rodata_26AC;
extern f32 lbl_3_rodata_26B0;
extern f32 lbl_3_rodata_26B8;
extern f32 shortAngleToRad(s16);
extern f32 lbl_3_rodata_26B4;
extern f32 lbl_3_rodata_27F8;
extern f64 acos(f64);
extern const Vec lbl_3_rodata_2604;
extern const f64 lbl_3_rodata_27C0;
extern const f64 lbl_3_rodata_27D0;
extern const f64 lbl_3_rodata_27D8;
extern const f32 lbl_3_rodata_27E4;
extern f32 lbl_3_rodata_27E0;
extern void fn_3_6620(void);
extern const Vec lbl_3_rodata_2520;
extern const f32 lbl_3_rodata_27C8;
extern const Vec lbl_3_rodata_252C;
extern const f64 lbl_3_rodata_2818;
extern const f64 lbl_3_rodata_2820;
extern void fn_3_6530(void);
extern const Vec lbl_3_rodata_24D0;
extern const Vec lbl_3_rodata_24DC;
extern const f32 lbl_3_rodata_2848;
extern const f32 lbl_3_rodata_2864;
extern const f32 lbl_3_rodata_2868;
extern const Vec lbl_3_rodata_2514;
extern const f64 lbl_3_rodata_2830;
extern const f64 lbl_3_rodata_2840;
extern const f32 lbl_3_rodata_2838;
extern const f32 lbl_3_rodata_2808;
extern const f32 lbl_3_rodata_2828;
extern const char lbl_3_rodata_249C[];
extern const u8 lbl_3_rodata_2498[];
extern const f32 lbl_3_rodata_2734;
extern const f32 lbl_3_rodata_2750;
extern const f32 lbl_3_rodata_2754;
extern const f32 lbl_3_rodata_2758;
extern const f32 lbl_3_rodata_275C;
extern const f32 lbl_3_rodata_2760;
extern const f64 lbl_3_rodata_2768;
extern const Vec lbl_3_rodata_24A0[];
extern const f32 lbl_3_rodata_2730;
extern const f64 lbl_3_rodata_2788;
extern const f64 lbl_3_rodata_2790;
extern const f32 lbl_3_rodata_2798;
extern const f32 lbl_3_rodata_279C;
extern s32 lbl_3_data_182C0;
extern const f32 lbl_3_rodata_27B8;
extern void fn_3_65F4(void);
extern s32 sndFXKeyOff(u32);
extern f64 pow(f64, f64);
extern f64 sqrt(f64);
extern const Vec lbl_3_rodata_25C8;
extern const Vec lbl_3_rodata_25D4;
extern const Vec lbl_3_rodata_25E0;
extern const f32 lbl_3_rodata_27EC;
extern Vec lbl_3_rodata_2640;
extern Vec lbl_3_rodata_264C;
extern void fn_800528C0(s16* sx, s16* sy, f32 x, f32 y, f32 z);
// Matched callers evaluate the floats first; the matching build calls through a
// float-first cast (same PPC registers), the port uses the real prototype.
#if NONMATCHING
#define fn_800528C0_xyz(x, y, z, sx, sy) fn_800528C0(sx, sy, x, y, z)
#else
#define fn_800528C0_xyz(x, y, z, sx, sy) ((void (*)(f32, f32, f32, s16*, s16*))fn_800528C0)(x, y, z, sx, sy)
#endif

extern void fn_800B0A14_removeQueue(void* unused);
// fn_800B0A14_removeQueue ignores its argument. Some callers pass nothing: r3 is
// whatever the previous call left (e.g. right after fn_80034CEC). The matching
// build calls it through a (void) cast there; the port passes NULL.
#ifndef REMOVE_QUEUE_NOARG
#if NONMATCHING
#define REMOVE_QUEUE_NOARG() fn_800B0A14_removeQueue(NULL)
#else
#define REMOVE_QUEUE_NOARG() ((void (*)(void))fn_800B0A14_removeQueue)()
#endif
#endif

extern const f64 lbl_3_rodata_2728;
extern const f64 lbl_3_rodata_2770;
extern const f64 lbl_3_rodata_2780;
extern u8 lbl_800E8754[];
typedef struct { u8 a, b, b2, b3; u8 pad[0x1A]; } S1E;
extern S1E lbl_3_data_8404[];
typedef struct { u8 a, b, b2, b3; } S2;
extern S2 lbl_3_data_84B8;
extern f32 lbl_3_rodata_2778;
extern void fn_3_CB7E8(f32, f32, f32);
extern u32 sndFXStartEx(int, u8, u8, u8);
extern u32 sndFXCtrl(int, int, u8);
extern f64 lbl_3_rodata_27A8;
extern f64 lbl_3_rodata_27B0;
extern int rand(void);
#ifdef PORT_LP64
typedef struct { u8 pad[STADIUM_OBJ_PAD(0x90)]; u8 rest : 7; u8 f : 1; } BF90_c2; // f: visible (MWCC bit order)
#else
typedef struct { u8 pad[0x90]; u8 f : 1; } BF90_c2;
#endif
extern const f32 lbl_3_rodata_27A0;
extern const f32 lbl_3_rodata_27A4;
typedef struct { f32 x, y, z; u8 type; u8 _0D[3]; } T16; // type 0xD ends a list
extern T16 lbl_3_data_18730[];
extern const f32 lbl_3_rodata_2700;
extern f32 lbl_3_rodata_2778;
extern const f32 lbl_3_rodata_26A0;
extern f32 lbl_3_rodata_27E8;
extern const f32 lbl_3_rodata_27F4;
extern const f32 lbl_3_rodata_2698;
extern const f32 lbl_3_rodata_26C8;
extern const f32 lbl_3_rodata_2678;
extern u8 lbl_3_data_81DC[];
extern void fn_3_65A8(void);
extern void fn_3_27648(void);
extern s32 fn_3_8BBC4(s32, f32*, f32*, s32);
extern Vec lbl_3_rodata_25B0;
extern Vec lbl_3_rodata_25BC;
extern Vec lbl_3_rodata_24E8[];
typedef struct { u8 b[9]; } B9;
extern B9 lbl_3_rodata_2544;
extern B9 lbl_3_rodata_255C;
extern B9 lbl_3_rodata_2568;
extern f64 lbl_3_rodata_2668;
extern B9 lbl_3_rodata_2550;
extern s32 fn_8005268C(void);
extern void* fn_80052734(s32 index);
#include "static/Camera.h"
extern f64 cos(f64);
extern f64 sin(f64);
extern const f32 lbl_3_rodata_27F0;
extern Vec lbl_3_rodata_25F8;
extern const f32 lbl_3_rodata_2658[];
typedef struct { f32 x, y, z; u8 type; u8 _0D[3]; f32 r; f32 scale[3]; f32 a, b, c, d; f32 spin; } T34;
extern T34 lbl_3_data_18364[];
typedef struct { f32 x, y, z; u8 type; u8 _0D[3]; f32 b, c, d, e, f, g; f32 _28, _2C; u8 chain; u8 _31[3]; } T52;
extern T52 lbl_3_data_182C8[];
extern s16 fn_3_B7F70(s32);
extern f32 lbl_3_data_188E0;
extern f32 lbl_3_rodata_2694;
extern const f32 lbl_3_rodata_2698;
extern s32 fn_3_9FB8C(f32, f32);
extern int fn_3_253A4(s8, s16);
extern void AnimateActorBones(void*);
extern const f64 lbl_3_rodata_2738;
extern const f64 lbl_3_rodata_2740;
extern const f64 lbl_3_rodata_2748;
extern void fn_800B4CA0(void*, f32);

static inline void CC1D4_inl(void) {
    Mtx m;
    Vec v;
    u32 i;
    u32 n;
    C2Obj* e;
    C2ObjComp* o;
    u32 k;
    ActorObject* r;
    f32 a;
    a = shortAngleToRad(g_Minigame._1AF8);
    PSMTXRotRad(m, 0x59, lbl_3_rodata_2658[0] * -a);
    v.x = lbl_3_rodata_265C;
    v.y = lbl_3_rodata_2660;
    v.z = lbl_3_rodata_2664;
    PSMTXMultVec(m, &v, &v);
    i = 0;
    e = (C2Obj*)lbl_3_common_bss_350E4.objs;
    n = lbl_3_common_bss_350E4.count;
    for (; i < n; i++) {
        if (e->kind == 1) break;
        e++;
    }
    for (k = i; k < i + 3; k++) {
        o = (C2ObjComp*)((C2Obj*)lbl_3_common_bss_350E4.objs + k);
        CTRLSetTranslation((Control*)o, g_Minigame._1AE0 + v.x, g_Minigame._1AE4 - v.y, g_Minigame._1AE8 + v.z);
        r = o->actorObj;
        o->delay = (k % 3) * 0x1E;
        o->time = 0.0f;
        r->time = o->time;
        r->setTime = 1;
        fn_800B4CA0(r->actor, r->time);
    }
}

// .text:0x000CB8A8 size:0x1F4 mapped:0x8070A93C
void fn_3_CB8A8(C2ObjMain* p) {
    switch (p->_CA) {
    case 0:
        fn_80025EEC(p->_8C, 0, 2);
        CC1D4_inl();
        break;
    case 3:
        fn_80025EEC(p->_8C, 0, 4);
        break;
    case 1:
        fn_80025EEC(p->_8C, 0, 3);
        break;
    case 2:
    default:
        fn_80025EEC(p->_8C, 0, 1);
        break;
    }
}

// .text:0x000CBA9C size:0x60 mapped:0x8070AB30
void fn_3_CBA9C(C2ObjMain* p) {
    DisplayStateList* q;
    q = PTR32_GET(DisplayStateList, p->actorObj->actor->boneArray[0]->dispObj->displayData->displayStateList);
    if (p->_CA == 0) {
        q[7].setting = q[7].setting & 0xFFFFE000;
        q[7].setting = q[7].setting | 3;
    } else {
        q[7].setting = q[7].setting & 0xFFFFE000;
        q[7].setting = q[7].setting | 2;
    }
}

// .text:0x000CBAFC size:0x11C mapped:0x8070AB90
void fn_3_CBAFC(C2ObjMain* p) {
    RopeNode* c = p->nodes;
    Mtx m;
    Vec axis = lbl_3_rodata_2640;
    Vec dir = lbl_3_rodata_264C;
    Vec v;
    PSMTXRotAxisRad(m, &axis, 0.017453292f * p->_C0);
    PSMTXMultVec(m, lbl_3_rodata_24E8, &v);
    PSVECAdd(&v, &p->pos, &v);
    v.y += 4.5;
    c[3].pos = v;
    c[3].prev = c[3].pos;
    fn_3_D1F2C(&lbl_3_bss_A8A8, p->nodes, 4, &dir, p);
}

// .text:0x000CBC18 size:0x368 mapped:0x8070ACAC
// NONMATCHING 97%: r30/r31 swapped (g_Minigame base vs chain nodes); fn_3_CBAFC and fn_3_CB8A8 are inlined copies
#if NONMATCHING
#pragma dont_inline off
static inline void CB8A8_inl(C2ObjMain* p) {
    switch (p->_CA) {
    case 0:
        fn_80025EEC(p->_8C, 0, 2);
        CC1D4_inl();
        break;
    case 3:
        fn_80025EEC(p->_8C, 0, 4);
        break;
    case 1:
        fn_80025EEC(p->_8C, 0, 3);
        break;
    case 2:
    default:
        fn_80025EEC(p->_8C, 0, 1);
        break;
    }
}

static inline void CBAFC_inl(C2ObjMain* p) {
    RopeNode* c;
    Mtx m;
    Vec axis;
    Vec dir;
    Vec v;
    c = p->nodes;
    axis = lbl_3_rodata_2640;
    dir = lbl_3_rodata_264C;
    PSMTXRotAxisRad(m, &axis, lbl_3_rodata_2658[0] * p->_C0);
    PSMTXMultVec(m, lbl_3_rodata_24E8, &v);
    PSVECAdd(&v, &p->pos, &v);
    v.y += lbl_3_rodata_2668;
    c[3].pos = v;
    c[3].prev = c[3].pos;
    fn_3_D1F2C(&lbl_3_bss_A8A8, p->nodes, 4, &dir, p);
}
#pragma dont_inline on

// Per-frame update: follows the minigame position/yaw, steps the chain, and reapplies
// the model state when g_Minigame[0x1B19] changes.
void fn_3_CBC18(C2ObjMain* p) {
    p->pos.x = g_Minigame._1AE0;
    p->pos.y = g_Minigame._1AE4;
    p->pos.z = g_Minigame._1AE8;
    p->_C0 = -(lbl_3_rodata_2670 * shortAngleToRad(g_Minigame._1AF8));
    CTRLSetTranslation((Control*)p, p->pos.x, -p->pos.y, p->pos.z);
    CTRLSetRotation((Control*)p, lbl_3_rodata_2664, p->_C0, lbl_3_rodata_2664);
    CBAFC_inl(p);
    if (g_Minigame._1B19 != p->_CA) {
        p->_CA = g_Minigame._1B19;
        CB8A8_inl(p);
        fn_3_CBF80(p);
    }
}
#endif

// .text:0x000CBF80 size:0x254 mapped:0x8070B014
extern const f32 lbl_3_rodata_2674;
extern const f32 lbl_3_rodata_267C;
extern const f64 lbl_3_rodata_2680;
extern const f64 lbl_3_rodata_2688;
extern const f32 lbl_3_rodata_2690;
// Lays the 4-node chain out hanging from the object (p+0xA0 pos, p+0xC0 yaw, p+0xC4 nodes),
// folding it along +z where it would go below the ground.
// NONMATCHING 97%: target reloads the 0.15/2.4 constants inside the fold branch; f30/f31 swapped
#if NONMATCHING
void fn_3_CBF80(C2ObjMain* p) {
    GameControl ctrl;
    Mtx m;
    Vec v;
    Vec cur;
    s32 n;
    u32 i;
    v = lbl_3_rodata_24E8[0];
    v.y = lbl_3_rodata_2674;
    ctrl.base.type = 0;
    CTRLSetRotation(&ctrl.base, lbl_3_rodata_2664, p->_C0, lbl_3_rodata_2664);
    CTRLBuildMatrix(&ctrl.base, m);
    PSMTXMultVec(m, &v, &v);
    v.y = v.y * lbl_3_rodata_2678;
    v.x += p->pos.x;
    v.y += p->pos.y;
    v.z += p->pos.z;
    cur = v;
    for (n = 4; n != 0; n--) {
        p->nodes[n - 1].pos.x = cur.x;
        p->nodes[n - 1].pos.y = cur.y;
        p->nodes[n - 1].pos.z = cur.z;
        cur.y -= lbl_3_rodata_267C;
        if (cur.y - lbl_3_rodata_2680 < lbl_3_rodata_2688) {
            f32 dz = lbl_3_rodata_267C * (f32)cos((f32)acos((f32)(lbl_3_rodata_2680 - cur.y) / lbl_3_rodata_267C));
            cur.y = lbl_3_rodata_2690;
            cur.z += dz;
        }
    }
    for (i = 0; i < 4; i++) {
        p->nodes[i].prev = p->nodes[i].pos;
        memset(&p->nodes[i].vel, 0, sizeof(Vec));
        memset(&p->nodes[i].force, 0, sizeof(Vec));
    }
}
#endif

// .text:0x000CC1D4 size:0x180 mapped:0x8070B268
void fn_3_CC1D4(void) {
    Mtx m;
    Vec v;
    u32 i;
    u32 n;
    C2Obj* e;
    C2ObjComp* o;
    u32 k;
    ActorObject* r;
    f32 a;
    a = shortAngleToRad(g_Minigame._1AF8);
    PSMTXRotRad(m, 0x59, lbl_3_rodata_2658[0] * -a);
    v.x = lbl_3_rodata_265C;
    v.y = lbl_3_rodata_2660;
    v.z = lbl_3_rodata_2664;
    PSMTXMultVec(m, &v, &v);
    i = 0;
    e = (C2Obj*)lbl_3_common_bss_350E4.objs;
    n = lbl_3_common_bss_350E4.count;
    for (; i < n; i++) {
        if (e->kind == 1) break;
        e++;
    }
    for (k = i; k < i + 3; k++) {
        o = (C2ObjComp*)((C2Obj*)lbl_3_common_bss_350E4.objs + k);
        CTRLSetTranslation((Control*)o, g_Minigame._1AE0 + v.x, g_Minigame._1AE4 - v.y, g_Minigame._1AE8 + v.z);
        r = o->actorObj;
        o->delay = (k % 3) * 0x1E;
        o->time = 0.0f;
        r->time = o->time;
        r->setTime = 1;
        fn_800B4CA0(r->actor, r->time);
    }
}

// .text:0x000CCC24 size:0xD34 mapped:0x8070BCB8
// One static prop of this stadium (lbl_3_data_185D0, type 0xD ends the list).
typedef struct C2Prop {
    /*0x00*/ Vec pos;
    /*0x0C*/ u8 type;
    /*0x0D*/ u8 _0D[3];
    /*0x10*/ Vec scale;
    /*0x1C*/ f32 rotY; // degrees
} C2Prop; // size 0x20
// .text:0x000D5E80 size:0x240 mapped:0x80714F14
typedef struct { f32 x, y, z; u8 fC; u8 padD; u8 fE; u8 padF; u8 pad[0xC]; } D5E80Ent;
// .data 0x000182C0..0x000188E8
s32 lbl_3_data_182C0 = -1;
s32 lbl_3_data_182C4 = -1;
T52 lbl_3_data_182C8[3] = {
    {55.0f, 0.0f, 40.0f, 0, {1, 1, 0}, 0.0f, 180.0f, 0.0f, 0.0f, 180.0f, 0.0f, 160.0f, 120.0f, 1, {0, 0, 0}},
    {-55.0f, 0.0f, 40.0f, 0, {1, 2, 0}, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 290.0f, 100.0f, 0, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 13, {0, 0, 0}, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, {0, 0, 0}},
};
T34 lbl_3_data_18364[6] = {
    {28.5f, 7.0f, 37.5f, 3, {1, 1, 0}, 30.0f, {1.0f, 1.0f, 1.0f}, -60.0f, 45.0f, 60.0f, 10.0f, 4.0f},
    {-28.5f, 7.0f, 37.5f, 3, {1, 3, 0}, 330.0f, {1.0f, 1.0f, 1.0f}, -60.0f, -10.0f, 60.0f, -45.0f, 4.0f},
    {0.0f, 0.0f, 0.0f, 13, {0, 0, 0}, 0.0f, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}, 0.0f, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}, 0.0f, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}, 0.0f, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
};
D5E80Ent lbl_3_data_1849C[11] = {
    {0.0f, -5.0f, 40.0f, 6, 1, 1, 0, {65, 32, 0, 0, 0, 0, 0, 0, 67, 180, 0, 0}},
    {20.0f, -5.0f, 40.0f, 6, 1, 2, 0, {65, 32, 0, 0, 0, 0, 0, 0, 67, 180, 0, 0}},
    {-20.0f, -5.0f, 40.0f, 6, 1, 3, 0, {65, 32, 0, 0, 0, 0, 0, 0, 67, 180, 0, 0}},
    {0.0f, 0.0f, 0.0f, 13, 0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
};
C2Prop lbl_3_data_185D0[11] = {
    {{37.4f, 0.0f, 8.0f}, 7, {1, 1, 0}, {1.0f, 1.0f, 1.0f}, -35.0f},
    {{22.5f, 0.0f, -7.3f}, 7, {1, 1, 0}, {1.0f, 1.0f, 1.0f}, -25.0f},
    {{-22.5f, 0.0f, -7.3f}, 7, {1, 1, 0}, {1.0f, 1.0f, 1.0f}, 20.0f},
    {{-37.4f, 0.0f, 8.0f}, 7, {1, 1, 0}, {1.0f, 1.0f, 1.0f}, 0.0f},
    {{-43.34f, -3.6f, 87.797f}, 7, {1, 1, 0}, {1.0f, 0.85f, 1.0f}, -25.0f},
    {{-32.055f, -3.6f, 101.771f}, 7, {1, 1, 0}, {1.0f, 0.8f, 1.0f}, -15.0f},
    {{31.884f, -3.6f, 101.246f}, 7, {1, 1, 0}, {1.0f, 0.8f, 1.0f}, 20.0f},
    {{43.626f, -3.6f, 87.915f}, 7, {1, 1, 0}, {1.0f, 0.88f, 1.0f}, 25.0f},
    {{0.0f, 0.0f, 0.0f}, 13, {0, 0, 0}, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 0, {0, 0, 0}, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 0, {0, 0, 0}, {0.0f, 0.0f, 0.0f}, 0.0f},
};
T16 lbl_3_data_18730[27] = {
    {0.0f, 0.15f, 60.0f, 8, {1, 1, 0}},
    {20.0f, 0.15f, 60.0f, 8, {1, 2, 0}},
    {-20.0f, 0.15f, 60.0f, 8, {1, 3, 0}},
    {0.0f, 0.0f, 0.0f, 13, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 11, {1, 1, 0}},
    {0.0f, 0.0f, 0.0f, 13, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}},
    {0.0f, 0.0f, 0.0f, 0, {0, 0, 0}},
    {0.0f, 0.0f, 10.0f, 0, {1, 1, 0}},
    {0.0f, -90.0f, 0.0f, 65, {240, 0, 0}},
    {-120.0f, 0.0f, 0.0f, 67, {180, 0, 0}},
    {0.0f, 2.3878675e-38f, 9.551468e-38f, 4, {2, 2, 2}},
    {9.846496e-38f, 4.1236383e-34f, 4.0935457e-34f, 0, {0, 0, 0}},
};
#ifdef TARGET_PC
// The stadium file kinds (bytes, fn_3_B9D68) at lbl_3_data_182C0 + 0x604, the
// tail of lbl_3_data_18730 spelled as floats above: the same bytes only on
// big-endian, and the two arrays aren't contiguous on PC.
static u8 sStaC2FileKinds[26] = {1, 2, 2, 4, 2, 2, 2, 2, 4, 2, 2, 2, 2, 6, 6, 8, 8, 9, 8, 9, 8, 8, 8, 9, 0, 0};
#endif
f32 lbl_3_data_188E0 = 0.1f; // NOTE: type size 0x4 != symbol size 0x8

// .text:0x000CC354 size:0xE4 mapped:0x8070B3E8
void fn_3_CC354(RopeNode* p) {
    RopeNode* q;
    f32 one;
    u32 i;
    if (p != NULL) {
        one = lbl_3_rodata_2698;
        q = p;
        for (i = 0; i < 4; i++, q++) {
            if (i == 3) {
                q->mass = lbl_3_data_188E0;
                q->radius = 0.504375f;
                q->pinned = 1;
            } else {
                q->mass = lbl_3_data_188E0;
                q->radius = 0.504375f;
            }
            q->invMass = one / q->mass;
            memset(&q->pos, 0, sizeof(Vec) * 2); // pos and prev
            memset(&q->vel, 0, sizeof(Vec));
            memset(&q->force, 0, sizeof(Vec));
        }
    }
}

static inline void CC354_inl(RopeNode* p) {
    RopeNode* q;
    f32 one;
    u32 i;
    if (p != NULL) {
        one = lbl_3_rodata_2698;
        q = p;
        for (i = 0; i < 4; i++, q++) {
            if (i == 3) {
                q->mass = lbl_3_data_188E0;
                q->radius = 0.504375f;
                q->pinned = 1;
            } else {
                q->mass = lbl_3_data_188E0;
                q->radius = 0.504375f;
            }
            q->invMass = one / q->mass;
            memset(&q->pos, 0, sizeof(Vec) * 2); // pos and prev
            memset(&q->vel, 0, sizeof(Vec));
            memset(&q->force, 0, sizeof(Vec));
        }
    }
}

// .text:0x000CC438 size:0x18C mapped:0x8070B4CC
void fn_3_CC438(void) {
    f32 one;
    CC438Cfg* g = &lbl_3_bss_A8A8;
    g->a = lbl_3_rodata_269C;
    g->b = lbl_3_rodata_26A0;
    g->c = lbl_3_rodata_26A4;
    g->d = lbl_3_rodata_26A8;
    g->e = lbl_3_rodata_26AC;
    g->f = lbl_3_rodata_26B0;
    g->n = 8;
    one = lbl_3_rodata_2698;
    g->h = one / (f32)g->n / lbl_3_rodata_26B4;
    g->hh = g->h * g->h;
    g->inv = one / (lbl_3_rodata_26B8 * g->h);
    CC354_inl(lbl_3_bss_A8D0);
}

#pragma dont_inline off
static inline void CC438_inl(void) {
    f32 one;
    CC438Cfg* g = &lbl_3_bss_A8A8;
    g->a = lbl_3_rodata_269C;
    g->b = lbl_3_rodata_26A0;
    g->c = lbl_3_rodata_26A4;
    g->d = lbl_3_rodata_26A8;
    g->e = lbl_3_rodata_26AC;
    g->f = lbl_3_rodata_26B0;
    g->n = 8;
    one = lbl_3_rodata_2698;
    g->h = one / (f32)g->n / lbl_3_rodata_26B4;
    g->hh = g->h * g->h;
    g->inv = one / (lbl_3_rodata_26B8 * g->h);
    CC354_inl(lbl_3_bss_A8D0);
}
#pragma dont_inline on

// .text:0x000CC5C4 size:0x258 mapped:0x8070B658
void fn_3_CC5C4(C2ObjMain* p) {
    p->_CA = g_Minigame._1B19;
    fn_80025EEC(p->_8C, 0, 2);
    p->_CB = p->_CA;
    ((BF90_c2*)p)->f = 1;
    p->ctrl.base.type = 0;
    CTRLSetScale((Control*)p, lbl_3_rodata_26C8, lbl_3_rodata_26C8, lbl_3_rodata_26C8);
    p->pos.x = g_Minigame._1AE0;
    p->pos.y = g_Minigame._1AE4;
    p->pos.z = g_Minigame._1AE8;
    p->_C0 = shortAngleToRad(g_Minigame._1AF8);
    CTRLSetRotation((Control*)p, 0.0f, p->_C0, 0.0f);
    CTRLSetTranslation((Control*)p, p->pos.x, -p->pos.y, p->pos.z);
    CC438_inl();
    fn_3_CBF80(p);
}

// .text:0x000CC81C size:0x408 mapped:0x8070B8B0
// NONMATCHING 95%: register assignment of the found object (target copies it to the inlined fn_3_CC5C4 param); fn_3_CC5C4/fn_3_CE8E4 are inlined copies
#if NONMATCHING
#pragma dont_inline off
static inline void CC5C4_inl(C2ObjMain* p) {
    p->_CA = g_Minigame._1B19;
    fn_80025EEC(p->_8C, 0, 2);
    p->_CB = p->_CA;
    ((BF90_c2*)p)->f = 1;
    p->ctrl.base.type = 0;
    CTRLSetScale((Control*)p, lbl_3_rodata_26C8, lbl_3_rodata_26C8, lbl_3_rodata_26C8);
    p->pos.x = g_Minigame._1AE0;
    p->pos.y = g_Minigame._1AE4;
    p->pos.z = g_Minigame._1AE8;
    p->_C0 = shortAngleToRad(g_Minigame._1AF8);
    CTRLSetRotation((Control*)p, lbl_3_rodata_2664, p->_C0, lbl_3_rodata_2664);
    CTRLSetTranslation((Control*)p, p->pos.x, -p->pos.y, p->pos.z);
    CC438_inl();
    fn_3_CBF80(p);
}

static inline void CE8E4_inl(void) {
    u8 i = 0;
    do {
        Emitter* r = fn_80033A24(fn_3_CDFA4, 0x80, 0, 0x15, 1, 0);
        if (r != NULL) {
            fn_3_CE56C(r, i);
        }
        i++;
    } while (i < 4);
}
#pragma dont_inline on

// Stadium setup: initialises the first real (non-dummy) object, places the three
// companion objects and starts the four smoke emitters.
void fn_3_CC81C(void) {
    StadiumObjList* g = (StadiumObjList*)&lbl_3_common_bss_350E4;
    u32 i = 0;
    PiranhaPlant* o = g->objs;
    for (; i < g->count; i++, o++) {
        if (o->isDummy == 0) {
            CC5C4_inl((C2ObjMain*)o);
            break;
        }
    }
    CC1D4_inl();
    CE8E4_inl();
}
#endif


extern C2Prop lbl_3_data_185D0[];
extern SpaniDesc lbl_3_data_10D3C[];
extern void fn_3_B97C8(void* fn);
extern void fn_3_B97DC(ActorObject* obj, void* f);
extern void fn_800BD548(ActorObject* obj, u8 numLights, ...);
extern void* fn_800B0A5C_insertQueue(void* draw, s32 priority);
extern void* _OSAllocFromHeap(s32 align, u32 size);

#define C2_SLOTS (lbl_8036E548.slots6C)
#define C2_OBJ(i) (&C2_SLOTS->objects[i])

// NONMATCHING ~90% (with fn_3_CC5C4/fn_3_D511C pasted inline): written with calls; register numbering, loop shapes
// nmverify: fn_3_CC5C4 fn_3_D511C are inlined in the original
#if NONMATCHING
// Stadium setup: builds the actor table (main object, three companions, the chain
// model and one model per prop), the shared animation player (lbl_3_bss_A018+0x74C),
// both 8-node chains, and the object list: the main object (0), three companions
// (type 1), three chain links (type 2) and the props.
void fn_3_CCC24(void** files, u32* idx) {
    StadiumObjList* g = (StadiumObjList*)&lbl_3_common_bss_350E4;
    C2Prop* prop = lbl_3_data_185D0;
    C2ObjAny* p;
    C2ObjAny* q;
    u8 done = 0;
    u32 nProps = 0;
    u32 nObjs;
    s32 j;
    s32 propBase;
    s32 chainIdx;
    u32 i;
    u32 used;
    s32 phase;
    u8 sh;
    void* task;
    f32 one;
    for (nProps = 0; nProps < 10; nProps++) {
        if (lbl_3_data_185D0[nProps].type == 0xD) {
            break;
        }
    }
    nObjs = nProps + 5;
    g->numActorObjs = nObjs;
    C2_SLOTS = ActorObjectInitTable(nObjs);
    fn_800BDC88(C2_SLOTS, 0, 0, STADIUM_FILE(files, idx[1]), NULL, NULL);
    for (j = 1, i = 0; i < 3; i++, j++) {
        fn_800BDC88(C2_SLOTS, j, j, STADIUM_FILE(files, idx[3]), NULL, NULL);
        fn_3_B97DC(C2_OBJ(j), STADIUM_FILE(files, idx[3] + 2));
    }
    fn_800BDC88(C2_SLOTS, j, j, STADIUM_FILE(files, idx[4]), NULL, NULL);
    chainIdx = j;
    propBase = j + 1;
    for (i = 0, j = propBase; i < nProps; i++, j++) {
        fn_800BDC88(C2_SLOTS, j, j, STADIUM_FILE(files, idx[8]), NULL, NULL);
        fn_3_B97DC(C2_OBJ(j), STADIUM_FILE(files, idx[8] + 2));
    }
    for (i = 0; i < nObjs; i++) {
        fn_800BD548(C2_OBJ(i), 4, g->lights[0], g->lights[1], g->lights[2], g->lights[3]);
    }
    if (STADIUM_FILE(files, idx[15]) != NULL && STADIUM_FILE(files, idx[17]) != NULL) {
        fn_80025DDC(STADIUM_FILE(files, idx[15]));
        fn_80025C58(STADIUM_FILE(files, idx[15]), (ShapeModel**)&C2_OBJ(0)->actor);
        lbl_3_bss_A034[20].set = STADIUM_FILE(files, idx[17]);
        fn_80025FFC(STADIUM_FILE(files, idx[15]), &lbl_3_bss_A034[20]);
        fn_80025EEC(&lbl_3_bss_A034[20], 0, 1);
    }
    fn_80035750(STADIUM_FILE(files, idx[25]), STADIUM_FILE(files, idx[24]), 5);
    task = fn_800B0A5C_insertQueue(fn_3_CE954, 2);
    lbl_3_bss_A8A4 = task;
    fn_80034E20(task, lbl_3_data_10D3C);
    fn_3_D511C();

    g->count = 0x43;
    g->objs = _OSAllocFromHeap(0x20, 0x43 * sizeof(C2Obj));
    p = (C2ObjAny*)g->objs;
    g->objsBackup = _OSAllocFromHeap(0x20, 0x43 * sizeof(C2Obj));
    memset(p, 0, 0x2D * sizeof(C2Obj));
    lbl_3_bss_A02C = 0;

    // object 0: the main object with the 4-node chain
    p->main.nodes = lbl_3_bss_A8D0;
    p->base.actorObj = C2_OBJ(0);
    p->base.shadow = STADIUM_FILE(files, idx[13]);
    p->base.update = (C2ObjFn)fn_3_CBC18;
    p->base.onHit = NULL;
    p->base.hasShadow = 0;
    p->base.bit5 = 1;
    p->base.idx = 0;
    p->base.alpha = 0xFF;
    p->base.preDraw = (C2ObjFn)fn_3_CBA9C;
    p->base._8C = &lbl_3_bss_A034[20];
    p->base._94 = 0;
    p->base._96 = -1;
    p->base._98 = 1;
    fn_3_CC5C4(&p->main);
    p->base.ctrl.base.type = 0;
    p->main._CA = 0xFF;
    lbl_3_bss_A02D++;
    used = 1;

    // objects 1-3: the companions (fn_3_D1848)
    q = p + 1;
    for (i = 0; i < 3; i++, q++) {
        q->base.kind = 1;
        q->base.actorObj = C2_OBJ(i + 1);
        q->base.shadow = NULL;
        q->base.update = (C2ObjFn)fn_3_D1848;
        q->base.onHit = NULL;
        q->base.visible = 0;
        q->base.hasShadow = 0;
        q->comp.speed = C2_OBJ(i + 1)->unk54;
        q->base.bit5 = 0;
        q->base.ctrl.base.type = 0;
        CTRLSetScale((Control*)q, lbl_3_rodata_26C8, lbl_3_rodata_26C8, lbl_3_rodata_26C8);
        q->base.alpha = 0xFF;
        q->base.preDraw = (C2ObjFn)fn_3_D173C;
        q->base._8C = NULL;
        q->base._94 = 0;
        used++;
        q->base._96 = -1;
        q->base._98 = 1;
        q->comp.mainFlag = &p->main._CA;
        q->base.idx = i;
        q->comp.delay = (i % 3) * 30;
        q->comp._AD = 0;
    }

    // objects 4-6: the chain links, each between two nodes of the main object's chain
    for (i = 0; i < 3; i++, q++) {
        q->link.a = &lbl_3_bss_A8D0[i];
        q->link.b = &lbl_3_bss_A8D0[i + 1];
        q->base.kind = 2;
        q->base.actorObj = C2_OBJ(chainIdx);
        q->base.shadow = NULL;
        q->base.update = (C2ObjFn)fn_3_D1280;
        q->base.onHit = NULL;
        q->base.visible = 1;
        q->base.hasShadow = 0;
        q->base.bit5 = 1;
        q->base.ctrl.base.type = 0;
        memset(&q->link.pos, 0, sizeof(Vec));
        q->base.alpha = 0xFF;
        used++;
        q->base.preDraw = (C2ObjFn)fn_3_D127C;
        q->base._8C = NULL;
        q->base._94 = 0;
        q->base._96 = -1;
        q->base._98 = 1;
        q->base.idx = i;
    }

    // the props
    phase = 0;
    for (i = 0; i < 10; i++, prop++) {
        if (prop->type == 0xD) {
            done = 1;
        }
        if (done) {
            for (; i < 11; i++) {
                lbl_3_data_185D0[i].type = 0xD;
            }
            break;
        }
        q->base.kind = prop->type;
        q->prop.phase = phase;
        q->base.actorObj = C2_OBJ(propBase + i);
        q->base.shadow = NULL;
        q->base.update = (C2ObjFn)fn_3_CFA8C;
        q->base.onHit = NULL;
        q->base.visible = 1;
        sh = 0;
        if (q->base.visible && q->base.shadow != NULL) {
            sh = 1;
        }
        q->base.hasShadow = sh;
        q->base.ctrl.base.type = 0;
        CTRLSetScale((Control*)q, prop->scale.x, prop->scale.y, prop->scale.z);
        CTRLSetTranslation((Control*)q, prop->pos.x, prop->pos.y, prop->pos.z);
        CTRLSetRotation((Control*)q, lbl_3_rodata_2664, -prop->rotY, lbl_3_rodata_2664);
        q->base.bit5 = 0;
        q->base.alpha = 0xFF;
        done = 0;
        q->base._8C = NULL;
        phase += 30;
        used++;
        q->base.preDraw = (C2ObjFn)fn_3_CFA88;
        q->base._94 = 0;
        q->base._96 = -1;
        q->base._98 = 1;
        q++;
    }

    // the rest are unused
    for (; used < (u32)g->count; used++, q++) {
        q->base.kind = 0xFF;
        q->base.actorObj = NULL;
        q->base.shadow = NULL;
        q->base.update = NULL;
        q->base.onHit = NULL;
        q->base.visible = 0;
        q->base.hasShadow = 0;
        q->base.bit5 = 0;
        q->base.ctrl.base.type = 0;
        CTRLSetTranslation((Control*)q, lbl_3_rodata_2664, lbl_3_rodata_2664, lbl_3_rodata_2664);
        CTRLSetRotation((Control*)q, lbl_3_rodata_2664, lbl_3_rodata_2664, lbl_3_rodata_2664);
        q->base.alpha = 0;
        q->base._8C = NULL;
        q->base._94 = 0;
        q->base._96 = -1;
    }
    g->groupBounds = NULL;
    fn_3_B97C8(fn_3_CD958);
}
#endif

// .text:0x000CD958 size:0x10 mapped:0x8070C9EC

void fn_3_CD958(void) {
    lbl_3_bss_A81C = 1;
}

// .text:0x000CD968 size:0x1E0 mapped:0x8070C9FC
extern const f32 lbl_3_rodata_26CC;
// NONMATCHING 97%: float constant regs (f30/f31) and corner store scheduling differ
// Returns whether a w*h rect centred on v (world space; v is overwritten with view space) is on screen.
#if NONMATCHING
u8 fn_3_CD968(Vec* v, f32 w, f32 h) {
    Vec out;
    Vec c[4];
    Vec* cp;
    u32 i;
    camera_803c639c_s* cam;
    u8 all;
    u8 fl;
    f32 z, hw, hh, x0, x1, y0, y1;
    all = 0;
    cam = fn_80052734(fn_8005268C());
    PSMTXMultVec(cam->view, v, v);
    z = v->z;
    if (z > lbl_3_rodata_2678 || z < lbl_3_rodata_26CC) {
        return 0;
    }
    x0 = v->x;
    y0 = v->y;
    hw = w * lbl_3_rodata_26A0;
    hh = h * lbl_3_rodata_26A0;
    cp = c;
    c[3].z = z;
    c[2].z = z;
    c[1].z = z;
    c[0].z = z;
    x1 = x0 - hw;
    y1 = y0 - hh;
    x0 = x0 + hw;
    y0 = y0 + hh;
    c[3].x = x1;
    c[0].x = x1;
    c[2].x = x0;
    c[1].x = x0;
    c[1].y = y1;
    c[0].y = y1;
    c[2].y = y0;
    c[3].y = y0;
    for (i = 0; i < 4; i++, cp++) {
        PSMTX44MultVec(cam->proj, cp, &out);
        fl = (out.x < lbl_3_rodata_2678);
        fl |= (out.x > lbl_3_rodata_2698) << 1;
        fl |= (out.y < lbl_3_rodata_2678) << 2;
        fl |= (out.y > lbl_3_rodata_2698) << 3;
        if (fl == 0) {
            return 1;
        }
        all &= fl;
    }
    if ((all & 3u) == 1 || (all & 3u) == 2) {
        return 0;
    }
    if ((all & 0xCu) == 4 || (all & 0xCu) == 8) {
        return 0;
    }
    return 1;
}
#endif

// .text:0x000CDB48 size:0x248 mapped:0x8070CBDC
extern const f64 lbl_3_rodata_26D0;
extern const f32 lbl_3_rodata_26D8;
extern const f64 lbl_3_rodata_26E0;
extern const f64 lbl_3_rodata_26E8;
extern const f64 lbl_3_rodata_26F0;
extern const f64 lbl_3_rodata_26F8;
void fn_3_CDB48(void* pv, Emitter* h) {
    Particle* p = pv;
    f32 a;
    s16 t;
    a = lbl_3_rodata_2658[0] * (f32)(rand() % 360);
    p->u.phys.vel.x = lbl_3_rodata_26D0 * (f32)cos(a);
    p->u.phys.vel.z = lbl_3_rodata_26D0 * (f32)sin(a);
    p->u.phys.vel.y = lbl_3_rodata_26D8;
    p->u.phys.accel.x = lbl_3_rodata_26A0;
    p->u.phys.accel.x = p->u.phys.accel.x + (f64)((u32)rand() % 2500) / lbl_3_rodata_26E0;
    p->sizeX = lbl_3_rodata_26E8 * p->u.phys.accel.x;
    p->sizeY = lbl_3_rodata_26F0 * p->u.phys.accel.x;
    p->u.phys.accel.y = (f64)(rand() % 101) / lbl_3_rodata_26F8;
    t = rand() % 24 + 0x48;
    p->life = t;
    p->uvOrder = t;
    p->pos.x = h->u.t1.pos.x;
    p->pos.y = h->u.t1.pos.y;
    p->pos.z = h->u.t1.pos.z;
    p->color.c.a = p->u.phys.accel.z = 255.0f;
    p->life = p->uvOrder;
    p->delay = 0;
}

// .text:0x000CDD90 size:0x214 mapped:0x8070CE24
extern const f64 lbl_3_rodata_2710;
extern const f64 lbl_3_rodata_2718;
extern const f32 lbl_3_rodata_2720;
void fn_3_CDD90(Particle* p) {
    p->sizeX = p->u.phys.accel.y * (lbl_3_rodata_2710 * p->u.phys.accel.x / p->uvOrder) + p->sizeX;
    p->sizeY = p->u.phys.accel.y * (lbl_3_rodata_2718 * p->u.phys.accel.x / p->uvOrder) + p->sizeY;
    p->u.phys.accel.z = p->u.phys.accel.z + (lbl_3_rodata_2720 / p->uvOrder);
    if (p->u.phys.accel.z < 0.0f) {
        p->u.phys.accel.z = 0.0f;
    }
    p->color.c.a = p->u.phys.accel.z;
    p->color.c.r = lbl_3_bss_A01C[0] * (p->color.c.a / lbl_3_rodata_2728);
    p->color.c.g = lbl_3_bss_A01C[1] * (p->color.c.a / lbl_3_rodata_2728);
    p->color.c.b = lbl_3_bss_A01C[2] * (p->color.c.a / lbl_3_rodata_2728);
    p->pos.x = p->pos.x + p->u.phys.vel.x;
    p->pos.y = p->pos.y - p->u.phys.vel.y;
    p->pos.z = p->pos.z + p->u.phys.vel.z;
    p->life = p->life - 1;
}

// .text:0x000CDFA4 size:0x5C8 mapped:0x8070D038
#pragma dont_inline off
static inline void CDB48_inl(void* pv, Emitter* h) {
    Particle* p = pv;
    f32 a;
    s16 t;
    a = lbl_3_rodata_2658[0] * (f32)(rand() % 360);
    p->u.phys.vel.x = lbl_3_rodata_26D0 * (f32)cos(a);
    p->u.phys.vel.z = lbl_3_rodata_26D0 * (f32)sin(a);
    p->u.phys.vel.y = lbl_3_rodata_26D8;
    p->u.phys.accel.x = lbl_3_rodata_26A0;
    p->u.phys.accel.x = p->u.phys.accel.x + (f64)((u32)rand() % 2500) / lbl_3_rodata_26E0;
    p->sizeX = lbl_3_rodata_26E8 * p->u.phys.accel.x;
    p->sizeY = lbl_3_rodata_26F0 * p->u.phys.accel.x;
    p->u.phys.accel.y = (f64)(rand() % 101) / lbl_3_rodata_26F8;
    t = rand() % 24 + 0x48;
    p->life = t;
    p->uvOrder = t;
    p->pos.x = h->u.t1.pos.x;
    p->pos.y = h->u.t1.pos.y;
    p->pos.z = h->u.t1.pos.z;
    p->color.c.a = p->u.phys.accel.z = 255.0f;
    p->life = p->uvOrder;
    p->delay = 0;
}

static inline void CDD90_inl(Particle* p) {
    p->sizeX = p->u.phys.accel.y * (lbl_3_rodata_2710 * p->u.phys.accel.x / p->uvOrder) + p->sizeX;
    p->sizeY = p->u.phys.accel.y * (lbl_3_rodata_2718 * p->u.phys.accel.x / p->uvOrder) + p->sizeY;
    p->u.phys.accel.z = p->u.phys.accel.z + (lbl_3_rodata_2720 / p->uvOrder);
    if (p->u.phys.accel.z < 0.0f) {
        p->u.phys.accel.z = 0.0f;
    }
    p->color.c.a = p->u.phys.accel.z;
    p->color.c.r = lbl_3_bss_A01C[0] * (p->color.c.a / lbl_3_rodata_2728);
    p->color.c.g = lbl_3_bss_A01C[1] * (p->color.c.a / lbl_3_rodata_2728);
    p->color.c.b = lbl_3_bss_A01C[2] * (p->color.c.a / lbl_3_rodata_2728);
    p->pos.x = p->pos.x + p->u.phys.vel.x;
    p->pos.y = p->pos.y - p->u.phys.vel.y;
    p->pos.z = p->pos.z + p->u.phys.vel.z;
    p->life = p->life - 1;
}
#pragma dont_inline on

// Emitter update for the four stadium smoke plumes (fn_3_CE56C). Skipped (returns 0)
// during game states 0x1B-0x21 and, in states 1/2, while the plume is off screen.
// Each live particle grows, fades and drifts (fn_3_CDD90); finished ones respawn (fn_3_CDB48).
s32 fn_3_CDFA4(Emitter* h) {
    Particle* e = h->particles;
    u8 st = g_GameLogic.gameStatus;
    Vec pos;
    if (st >= 0x1B && st <= 0x21) {
        return 0;
    }
    if (st == 2 || st == 1) {
        pos = *(Vec*)(&h->u);
        if (!fn_3_CD968(&pos, lbl_3_rodata_2730, lbl_3_rodata_2734)) {
            return 0;
        }
    }
    fn_80033620(h);
    GXSetZMode(1, 3, 0);
    do {
        if (e->delay <= 0 && e->life != 0) {
            if (e->unk4C % 3 == 0) {
                GXSetBlendMode(3, 1, 1, 0);
                lbl_3_bss_A01C = (u8*)lbl_3_rodata_249C;
            } else {
                GXSetBlendMode(1, 1, 1, 0);
                lbl_3_bss_A01C = (u8*)lbl_3_rodata_2498;
            }
            fn_8003403C(e->sizeX, e->sizeY);
            fn_80033CC8(e, h->tex);
            if ((u32)fn_8005268C() == 0) {
                CDD90_inl(e);
            }
        }
        e->delay -= (fn_8005268C() == 0);
        if (e->life == 0) {
            CDB48_inl(e, h);
        }
        e = e->next;
    } while (e != NULL);
    h->u.game.drawn = 1;
    return 0;
}

// .text:0x000CE56C size:0x378 mapped:0x8070D600
// Seeds smoke emitter h (from fn_3_CE8E4) at spot idx of lbl_3_rodata_24A0: each particle
// gets a random heading, size and fade, and starts 4 frames after the previous one.
void fn_3_CE56C(Emitter* h, u8 idx) {
    s16 delay;
    Particle* e = h->particles;
    s8 n;
    f32 a;
    s16 t;
    h->tex = lbl_3_bss_ADD0[0];
    *(Vec*)(&h->u) = lbl_3_rodata_24A0[idx];
    h->u.game._24 = idx;
    h->u.game.drawn = 1;
    n = 0;
    delay = 0;
    for (; e != NULL; e = e->next) {
        a = lbl_3_rodata_2658[0] * (f32)(rand() % 360);
        e->u.phys.vel.x = lbl_3_rodata_26D0 * (f32)cos(a);
        e->u.phys.vel.z = lbl_3_rodata_26D0 * (f32)sin(a);
        e->u.phys.vel.y = lbl_3_rodata_26D8;
        e->delay = delay;
        e->u.phys.accel.x = lbl_3_rodata_26A0;
        e->u.phys.accel.x = e->u.phys.accel.x + (f64)((u32)rand() % 2500) / lbl_3_rodata_26E0;
        e->sizeX = lbl_3_rodata_26E8 * e->u.phys.accel.x;
        e->sizeY = lbl_3_rodata_26F0 * e->u.phys.accel.x;
        e->u.phys.accel.y = (f64)(rand() % 101) / lbl_3_rodata_26F8;
        e->pos.x = h->u.t1.pos.x;
        e->pos.y = h->u.t1.pos.y;
        e->pos.z = h->u.t1.pos.z;
        e->color.c.a = e->u.phys.accel.z = lbl_3_rodata_2700;
        t = rand() % 24 + 0x48;
        delay += 4;
        e->life = t;
        e->uvOrder = t;
        e->texIndex = 0x15;
        e->uvFrame = 0;
        e->unk4C = n;
        n++;
    }
}

// .text:0x000CE8E4 size:0x70 mapped:0x8070D978
void fn_3_CE8E4(void) {
    u32 i = 0;
    do {
        Emitter* r = fn_80033A24(fn_3_CDFA4, 0x80, 0, 0x15, 1, 0);
        if (r != 0) {
            fn_3_CE56C(r, (u8)i);
        }
        i++;
    } while (i < 4);
}

// .text:0x000CE954 size:0x268 mapped:0x8070D9E8
void fn_3_CE954(void) {
    u8* b;
    u8* st;
    f32* v;
    SceneTask* g;
    s32 i;
    s32 f;
    b = lbl_3_bss_A018;
    i = 0;
    st = C2_BSS(u8, lbl_3_bss_A898, b, 0x880);
    v = C2_BSS(f32, lbl_3_bss_A820, b, 0x808);
    g = lbl_803CC1B8;
    do {
        switch (*st) {
        case 1: {
            s16 b1;
            s16 a1;
            fn_800528C0_xyz(v[0], v[1], v[2], &a1, &b1);
            lbl_80371C30[(*C2_BSS(SpaniGroup*, lbl_3_bss_A8A4, b, 0x88C))->u14.objIdx + i].obj->x = a1;
            lbl_80371C30[(*C2_BSS(SpaniGroup*, lbl_3_bss_A8A4, b, 0x88C))->u14.objIdx + i].obj->y = b1;
            lbl_80371C30[(*C2_BSS(SpaniGroup*, lbl_3_bss_A8A4, b, 0x88C))->u14.objIdx + i].obj->z = 0.0f;
            lbl_80371C30[g->u14.objIdx + i].obj->_5C = 0;
            lbl_80371C30[g->u14.objIdx + i].obj->flags |= 2;
            *st = 2;
            break;
        }
        case 2: {
            s16 b2;
            s16 a2;
            LayoutObj* t;
            fn_800528C0_xyz(v[0], v[1], v[2], &a2, &b2);
            lbl_80371C30[(*C2_BSS(SpaniGroup*, lbl_3_bss_A8A4, b, 0x88C))->u14.objIdx + i].obj->x = a2;
            lbl_80371C30[(*C2_BSS(SpaniGroup*, lbl_3_bss_A8A4, b, 0x88C))->u14.objIdx + i].obj->y = b2;
            lbl_80371C30[(*C2_BSS(SpaniGroup*, lbl_3_bss_A8A4, b, 0x88C))->u14.objIdx + i].obj->z = 0.0f;
            t = lbl_80371C30[g->u14.objIdx + i].obj;
            f = (t->_69 == 2);
            if (f != 0) {
                t->flags &= ~2;
                *st = 0;
            }
            break;
        }
        }
        i++;
        st++;
        v += 3;
    } while (i < 10);
    if (*C2_BSS(u8, lbl_3_bss_A81C, b, 0x804) != 0) {
        REMOVE_QUEUE_NOARG();
        fn_80034CEC(*C2_BSS(SpaniGroup*, lbl_3_bss_A8A4, b, 0x88C));
        *C2_BSS(u8, lbl_3_bss_A81C, b, 0x804) = 0;
    }
}

// .text:0x000CEBBC size:0xDC mapped:0x8070DC50
void fn_3_CEBBC(f32* v, s32 k) {
    s16 a;
    s16 b;
    fn_800528C0_xyz(v[0], v[1], v[2], &a, &b);
    lbl_80371C30[lbl_3_bss_A8A4->u14.objIdx + k].obj->x = a;
    lbl_80371C30[lbl_3_bss_A8A4->u14.objIdx + k].obj->y = b;
    lbl_80371C30[lbl_3_bss_A8A4->u14.objIdx + k].obj->z = 0.0f;
}

// .text:0x000CEC98 size:0x98 mapped:0x8070DD2C
void fn_3_CEC98(void) {
    s32 k = (g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0) + 8;
    lbl_3_bss_A898[k] = 1;
    lbl_80371C30[lbl_3_bss_A8A4->u14.objIdx + k].obj->x = g_Ball.AtBat_Contact_BallPos.x;
    lbl_80371C30[lbl_3_bss_A8A4->u14.objIdx + k].obj->y = -g_Ball.AtBat_Contact_BallPos.y;
    lbl_80371C30[lbl_3_bss_A8A4->u14.objIdx + k].obj->z = g_Ball.AtBat_Contact_BallPos.z;
}

// .text:0x000CED30 size:0x4 mapped:0x8070DDC4
void fn_3_CED30(void) {
    return;
}

// .text:0x000CED34 size:0x4 mapped:0x8070DDC8
void fn_3_CED34(void) {
    return;
}

// .text:0x000CED38 size:0x4 mapped:0x8070DDCC
void fn_3_CED38(C2Obj* p) {
    return;
}

// .text:0x000CED3C size:0x4 mapped:0x8070DDD0
void fn_3_CED3C(C2Obj* p) {
    return;
}

// .text:0x000CED40 size:0x11C mapped:0x8070DDD4
void fn_3_CED40(Particle* p, void* a) {
    fn_8003403C(p->sizeX, p->sizeY);
    fn_80033CC8(p, a);
    if (lbl_80366158._28 == 0) {
        if (-p->delay < 5) {
            p->sizeX = p->sizeX + lbl_3_rodata_2738;
            p->sizeY = p->sizeY + lbl_3_rodata_2738;
            p->color.c.a = p->color.c.a + lbl_3_rodata_2740;
        } else {
            p->color.c.a = p->color.c.a - 4;
        }
        p->pos.x = p->pos.x + p->u.phys.vel.x;
        p->pos.y = p->pos.y + p->u.phys.vel.y;
        p->pos.z = p->pos.z + p->u.phys.vel.z;
    }
}

// .text:0x000CEE5C size:0x14C mapped:0x8070DEF0
void fn_3_CEE5C(Particle* p, void* a) {
    fn_8003403C(p->sizeX, p->sizeY);
    fn_80033CC8(p, a);
    if (lbl_80366158._28 == 0) {
        if (-p->delay < 5) {
            p->sizeX = p->sizeX + lbl_3_rodata_2738;
            p->sizeY = p->sizeY + lbl_3_rodata_2738;
            p->color.c.a = p->color.c.a + lbl_3_rodata_2740;
        } else {
            p->color.c.a = p->color.c.a + lbl_3_rodata_2748;
        }
        p->pos.x = p->pos.x + p->u.phys.vel.x;
        p->pos.y = p->pos.y + p->u.phys.vel.y;
        p->pos.z = p->pos.z + p->u.phys.vel.z;
    }
}

#pragma dont_inline off
static inline void CED40_inl(Particle* p, void* a) {
    fn_8003403C(p->sizeX, p->sizeY);
    fn_80033CC8(p, a);
    if (lbl_80366158._28 == 0) {
        if (-p->delay < 5) {
            p->sizeX = p->sizeX + lbl_3_rodata_2738;
            p->sizeY = p->sizeY + lbl_3_rodata_2738;
            p->color.c.a = p->color.c.a + lbl_3_rodata_2740;
        } else {
            p->color.c.a = p->color.c.a - 4;
        }
        p->pos.x = p->pos.x + p->u.phys.vel.x;
        p->pos.y = p->pos.y + p->u.phys.vel.y;
        p->pos.z = p->pos.z + p->u.phys.vel.z;
    }
}

static inline void CEE5C_inl(Particle* p, void* a) {
    fn_8003403C(p->sizeX, p->sizeY);
    fn_80033CC8(p, a);
    if (lbl_80366158._28 == 0) {
        if (-p->delay < 5) {
            p->sizeX = p->sizeX + lbl_3_rodata_2738;
            p->sizeY = p->sizeY + lbl_3_rodata_2738;
            p->color.c.a = p->color.c.a + lbl_3_rodata_2740;
        } else {
            p->color.c.a = p->color.c.a + lbl_3_rodata_2748;
        }
        p->pos.x = p->pos.x + p->u.phys.vel.x;
        p->pos.y = p->pos.y + p->u.phys.vel.y;
        p->pos.z = p->pos.z + p->u.phys.vel.z;
    }
}
#pragma dont_inline on

// .text:0x000CEFA8 size:0x2D0 mapped:0x8070E03C
s32 fn_3_CEFA8(Emitter* h) {
    Particle* p = h->particles;
    fn_80033620(h);
    do {
        if (p->delay <= 0 && p->life != 0) {
            if (p->uvOrder == 0) {
                CEE5C_inl(p, h->tex);
            } else {
                CED40_inl(p, h->tex);
            }
            p->life -= (lbl_80366158._28 == 0);
        }
        p->delay -= (lbl_80366158._28 == 0);
        p = p->next;
    } while (p != NULL);
    h->u.game._18 -= (lbl_80366158._28 == 0);
    if (h->u.game._18 == 0) {
        return 1;
    }
    return 0;
}

// .text:0x000CF278 size:0x4B4 mapped:0x8070E30C
// NONMATCHING 97%: f30/f31 swapped between the angle and cos/sin temp; pos->y load scheduled later
#if NONMATCHING
// Seeds p's splash emitter (p+0xA0): 10 drops spraying from pos, then a ring of
// drops around p's spot in lbl_3_data_18730 that start 15 frames later.
void fn_3_CF278(C2ObjHit* p, Vec* pos) {
    Emitter* h = p->emitter;
    Particle* e = h->particles;
    u32 k;
    u32 i;
    f32 c;
    f32 a;
    i = 0;
    k = 0;
    h->tex = lbl_3_bss_ADD0[0];
    h->u.game._18 = 100;
    h->u.game.owner = p;
    for (; e != NULL; e = e->next) {
        if (i < 10) {
            e->sizeX = e->sizeY = lbl_3_rodata_2750;
            a = lbl_3_rodata_2658[0] * (f32)(rand() % 360);
            e->u.phys.vel.x = lbl_3_rodata_26D0 * (f32)cos(a);
            e->u.phys.vel.z = lbl_3_rodata_26D0 * (f32)sin(a);
            e->u.phys.vel.y = lbl_3_rodata_2754;
            e->pos.x = pos->x + (f32)(rand() % 200 - 100) / lbl_3_rodata_2758;
            e->pos.y = -pos->y;
            e->pos.z = pos->z + (f32)(rand() % 200 - 100) / lbl_3_rodata_2758;
            e->delay = 0;
            e->color.c.b = 0xFF;
            e->color.c.g = 0xFF;
            e->color.c.r = 0xFF;
            e->color.c.a = 0;
            e->uvOrder = 0;
            e->life = 30;
        } else {
            e->sizeX = e->sizeY = lbl_3_rodata_2750;
            a = lbl_3_rodata_2658[0] * (lbl_3_rodata_275C * k + (f32)(rand() % 33) - lbl_3_rodata_2760);
            e->u.phys.vel.x = lbl_3_rodata_2768 * (f32)cos(a);
            e->u.phys.vel.z = lbl_3_rodata_2768 * (f32)sin(a);
            e->u.phys.vel.y = lbl_3_rodata_2754;
            c = cos(a);
            e->pos.x = lbl_3_data_18730[p->idx].x + (f32)(lbl_3_rodata_2770 * c + (f32)(rand() % 100 - 50) / lbl_3_rodata_2758);
            e->pos.y = -lbl_3_data_18730[p->idx].y;
            c = sin(a);
            e->pos.z = lbl_3_data_18730[p->idx].z + (f32)(lbl_3_rodata_2770 * c + (f32)(rand() % 100 - 50) / lbl_3_rodata_2758);
            e->delay = 15;
            e->color.c.b = 0xFF;
            e->color.c.g = 0xFF;
            e->color.c.r = 0xFF;
            e->color.c.a = 0;
            e->uvOrder = 1;
            e->life = 45;
            k++;
        }
        e->texIndex = 9;
        i++;
        e->uvFrame = 0;
    }
}
#endif

// .text:0x000CF72C size:0x200 mapped:0x8070E7C0
void fn_3_CF72C(s32 idx, s32 hitType, struct _CollisionStruct* hit) {
    C2ObjHit* p = (C2ObjHit*)((C2Obj*)lbl_3_common_bss_350E4.objs + idx);
    Vec t;
    Vec a;
    Vec b;
    s32 stad;
    u8 v;
    u32 h;
    if (g_Ball.AtBat_ContactResult < 2 && p->_A4 != 1) {
        if (lbl_800E8754[4] != 0) {
            CTRLGetTranslation((Control*)p, &t.x, &t.y, &t.z);
            fn_3_CB7E8(t.x, t.y - lbl_3_rodata_2778, t.z);
            p->_A4 = 1;
        }
        if (p->emitter != NULL) {
            fn_80033964(p->emitter);
            p->emitter = NULL;
        }
        p->emitter = fn_80033A24(fn_3_CEFA8, 0x80, 0, 0x1E, 1, 0);
        if (p->emitter != NULL) {
            a.x = g_Ball.AtBat_Contact_BallPos.x;
            a.y = g_Ball.AtBat_Contact_BallPos.y;
            a.z = g_Ball.AtBat_Contact_BallPos.z;
            b = a;
            fn_3_CF278(p, &b);
        }
        p->_8C = &lbl_3_bss_A034[p->idx];
        fn_80025EEC(p->_8C, 0, 0);
        ((ShapeAnimPlayer*)p->_8C)->state.loops = 1;
        ((ShapeAnimPlayer*)p->_8C)->curIdx = -1;
        stad = g_d_GameSettings.StadiumID;
        if (g_d_GameSettings.GameModeSelected == 6) {
            v = lbl_3_data_84B8.a;
        } else {
            v = lbl_3_data_8404[stad].a;
        }
        h = sndFXStartEx(((u16*)lbl_3_data_81DC)[stad], v, 0x3F, 0);
        if (g_d_GameSettings.GameModeSelected == 6) {
            v = lbl_3_data_84B8.b;
        } else {
            v = lbl_3_data_8404[stad].b;
        }
        sndFXCtrl(h, 0x5B, v);
    }
}

// .text:0x000CF92C size:0x4 mapped:0x8070E9C0
void fn_3_CF92C(C2Obj* p) {
    return;
}

// .text:0x000CF930 size:0x158 mapped:0x8070E9C4
void fn_3_CF930(C2ObjHit* p) {
    ShapeAnimPlayer* a = p->_8C;
    u16 n;
    f32 d;
    Emitter* q;
    if (a != NULL) {
        f32 t;
        f32 fn;
        n = a->state.seqs[0].hdr.length;
        d = a->state.speed;
        if (a->state.frame == (f32)n) {
            CTRLSetTranslation((Control*)p, lbl_3_data_18730[p->idx].x, lbl_3_rodata_2778, lbl_3_data_18730[p->idx].z);
            p->_8C = NULL;
            ((BF90_c2*)p)->f = 0;
        }
        fn = n;
        t = lbl_3_rodata_2700 / (fn / d);
        if (p->alpha <= t) {
            p->alpha = 0;
        } else {
            p->alpha -= t;
        }
    }
    q = p->emitter;
    if (q != NULL && q->update == NULL) {
        p->emitter = NULL;
    }
}

// .text:0x000CFA88 size:0x4 mapped:0x8070EB1C
void fn_3_CFA88(C2Obj* p) {
    return;
}

// .text:0x000CFA8C size:0x28 mapped:0x8070EB20
void fn_3_CFA8C(C2ObjProp* p) {
    AnimateActorBones(p->actorObj->actor);
}

// .text:0x000CFAB4 size:0x90 mapped:0x8070EB48
void fn_3_CFAB4(Particle* p, Emitter* q) {
    C2ObjD0284* r = ((C2ObjFx*)q->u.game.owner)->marker;
    f32 t;
    p->pos.x = p->u.phys.accel.x;
    p->pos.y = p->u.phys.accel.y;
    p->pos.z = p->u.phys.accel.z;
    t = 3.0 * r->_BC;
    p->sizeY = t;
    p->sizeX = t;
    p->color.c.b = 0xFF;
    p->color.c.g = 0xFF;
    p->color.c.r = 0xFF;
    p->color.c.a = 255.0 * r->_BC;
    p->life = 0x1E;
    p->delay = 0;
}

// .text:0x000CFB44 size:0x214 mapped:0x8070EBD8
s32 fn_3_CFB44(Emitter* a) {
    Particle* e = a->particles;
    C2ObjFx* o = a->u.game.owner;
    s32 k;
    f32 sc;
    C2ObjD0284* t;
    fn_80033620(a);
    GXSetBlendMode(1, 4, 5, 0);
    GXSetZMode(1, 3, 1);
    do {
        if (e->delay <= 0 && e->life != 0) {
            fn_8003403C(e->sizeX, e->sizeY);
            fn_80033CC8(e, a->tex);
            e->sizeX = e->sizeX + lbl_3_rodata_2780;
            if (e->sizeX < 0.0f) {
                e->sizeX = 0.0f;
            }
            e->sizeY = e->sizeY + lbl_3_rodata_2780;
            if (e->sizeY < 0.0f) {
                e->sizeY = 0.0f;
            }
            k = e->color.c.a;
            k = k - 8;
            if (k < 0) {
                k = 0;
            }
            e->color.c.a = k;
            e->pos.x = e->pos.x + e->u.phys.vel.x;
            e->pos.y = e->pos.y - e->u.phys.vel.y;
            e->pos.z = e->pos.z + e->u.phys.vel.z;
            e->life = e->life - 1;
        }
        e->delay = e->delay - 1;
        if (e->life == 0) {
            t = ((C2ObjFx*)a->u.game.owner)->marker;
            e->pos.x = e->u.phys.accel.x;
            e->pos.y = e->u.phys.accel.y;
            e->pos.z = e->u.phys.accel.z;
            sc = lbl_3_rodata_2770 * t->_BC;
            e->sizeY = sc;
            e->sizeX = sc;
            e->color.c.b = 0xFF;
            e->color.c.g = 0xFF;
            e->color.c.r = 0xFF;
            e->color.c.a = (u8)(lbl_3_rodata_2728 * t->_BC);
            e->life = 0x1E;
            e->delay = 0;
        }
        e = e->next;
    } while (e != NULL);
    if (o->target->_D1 == 0) {
        o->emitter = NULL;
        return 1;
    }
    return 0;
}

// .text:0x000CFD58 size:0x374 mapped:0x8070EDEC
// Seeds the ring particles of p's emitter (p+0xA8): 5 per ring around the owner
// (p+0xA0), each ring 10 degrees further round and 5 frames later.
// NONMATCHING 97%: hoisted float constants land in a different f21-f31 order
#if NONMATCHING
void fn_3_CFD58(C2ObjFx* p) {
    Emitter* h = p->emitter;
    Particle* e = h->particles;
    s32 i;
    s32 ring;
    s32 a;
    f32 ang;
    h->u.game.owner = p;
    h->tex = lbl_3_bss_ADD0[0];
    for (i = 0; e != NULL; e = e->next) {
        ang = lbl_3_rodata_2658[0] * ((f32)(lbl_3_rodata_2788 * (i % 5) / lbl_3_rodata_2790) + (f32)(-(s8)p->target->_D0 * (ring = i / 5) * 10));
        e->u.phys.accel.x = e->pos.x = lbl_3_rodata_2730 * (f32)cos(ang) + p->target->pos.x;
        e->u.phys.accel.y = e->pos.y = lbl_3_rodata_2664;
        e->u.phys.accel.z = e->pos.z = lbl_3_rodata_2730 * (f32)sin(ang) + p->target->pos.z;
        rand();
        e->u.phys.vel.x = lbl_3_rodata_2664;
        e->u.phys.vel.y = lbl_3_rodata_2798;
        e->u.phys.vel.z = lbl_3_rodata_2664;
        e->life = (ring + 1) * 5;
        e->pos.x = e->u.phys.vel.x * (f32)(30 - e->life) + e->pos.x;
        e->pos.y = e->u.phys.vel.y * (f32)(30 - e->life) + e->pos.y;
        e->pos.z = e->u.phys.vel.z * (f32)(30 - e->life) + e->pos.z;
        e->sizeX = e->sizeY = lbl_3_rodata_2770 * ((f32)(30 - e->life) / lbl_3_rodata_279C) + lbl_3_rodata_2770;
        e->color.c.b = 0xFF;
        e->color.c.g = 0xFF;
        e->color.c.r = 0xFF;
        a = lbl_3_rodata_2720 * ((f32)(30 - e->life) / lbl_3_rodata_279C) + lbl_3_rodata_2700;
        if (a < 0) {
            a = 0;
        }
        e->color.c.a = a;
        i++;
        e->delay = 0;
        e->texIndex = 9;
        e->uvFrame = 0;
    }
}
#endif

// .text:0x000D00CC size:0x4 mapped:0x8070F160
void fn_3_D00CC(C2Obj* p) {
    return;
}

// .text:0x000D00D0 size:0x1B0 mapped:0x8070F164
// NONMATCHING 93%: p/c saved regs swapped (r30/r31); int->float const regs differ
#if NONMATCHING
void fn_3_D00D0(C2ObjFx* p) {
    C2ObjSpin* o = p->target;
    Control* c;
    u8 st;
    f32 z, y, x;
    c = &p->marker->ctrl.base;
    st = o->_D1;
    if (st == 0) {
        if (((BF90_c2*)p)->f) {
            ((BF90_c2*)p)->f = 0;
        }
        if (p->alpha != 0xFF) {
            p->alpha = 0xFF;
        }
        if (p->emitter != NULL) {
            fn_80033964(p->emitter);
            p->emitter = NULL;
        }
    } else {
        if (!((BF90_c2*)p)->f) {
            ((BF90_c2*)p)->f = 1;
        }
        if (p->emitter == NULL) {
            p->emitter = fn_80033A24(fn_3_CFB44, 0x80, 0, 0x1E, 0, 1);
            if (p->emitter != NULL) {
                fn_3_CFD58(p);
            }
        }
        CTRLSetRotation((Control*)p, lbl_3_rodata_2664, p->target->_C0, lbl_3_rodata_2664);
        if (st == 3) {
            p->alpha = (u8)(p->alpha - lbl_3_rodata_27A0);
            if (p->alpha > lbl_3_rodata_27A4) {
                p->alpha = 0;
            }
        }
    }
    CTRLGetTranslation(c, &x, &y, &z);
    CTRLSetTranslation((Control*)p, x, y, z);
}
#endif

// .text:0x000D0280 size:0x4 mapped:0x8070F314
void fn_3_D0280(C2Obj* p) {
    return;
}

// .text:0x000D0284 size:0x20C mapped:0x8070F318
// NONMATCHING 92%: p/st saved regs swapped (r30/r31)
#if NONMATCHING
void fn_3_D0284(C2ObjD0284* p) {
    u8 st = p->target->_D1;
    f32 ang;
    s32 r;
    s32 v;
    if (st == 0) {
        if (((BF90_c2*)p)->f) {
            ((BF90_c2*)p)->f = 0;
        }
        if (p->alpha != 0xFF) {
            p->alpha = 0xFF;
        }
        if (lbl_3_rodata_27A8 != p->_BC) {
            p->_BC = lbl_3_rodata_2698;
        }
    } else {
        if (!((BF90_c2*)p)->f) {
            ((BF90_c2*)p)->f = 1;
        }
        CTRLSetRotation((Control*)p, lbl_3_rodata_2664, p->target->_C0, lbl_3_rodata_2664);
        r = rand();
        ang = lbl_3_rodata_2658[0] * (f32)(r % 360);
        p->_B0 = p->_BC * (f32)cos(ang);
        p->_B8 = p->_BC * (f32)sin(ang);
        CTRLSetTranslation((Control*)p, p->_A4 + p->_B0, lbl_3_rodata_2664, p->_AC + p->_B8);
        if (st == 3) {
            v = p->alpha;
            v = (s32)((f32)v - lbl_3_rodata_27A0);
            if (v < 0) {
                v = 0;
            }
            p->alpha = v;
            p->_BC = (f32)((f64)p->_BC - lbl_3_rodata_27B0);
            if (p->_BC < lbl_3_rodata_2664) {
                p->_BC = lbl_3_rodata_2664;
            }
        }
    }
}
#endif

// .text:0x000D0490 size:0x98 mapped:0x8070F524
void fn_3_D0490(void) {
    s32 k = (g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0) + 2;
    lbl_3_bss_A898[k] = 1;
    lbl_80371C30[lbl_3_bss_A8A4->u14.objIdx + k].obj->x = g_Ball.AtBat_Contact_BallPos.x;
    lbl_80371C30[lbl_3_bss_A8A4->u14.objIdx + k].obj->y = -g_Ball.AtBat_Contact_BallPos.y;
    lbl_80371C30[lbl_3_bss_A8A4->u14.objIdx + k].obj->z = g_Ball.AtBat_Contact_BallPos.z;
}

// .text:0x000D0528 size:0x4 mapped:0x8070F5BC
void fn_3_D0528(C2Obj* p) {
    return;
}

// .text:0x000D052C size:0x8 mapped:0x8070F5C0
s32 fn_3_D052C(void) {
    return 0;
}

// .text:0x000D0534 size:0x320 mapped:0x8070F5C8
// Carries the ball around p (p+0xA0 centre, p+0xBC deg/frame, (s8)p[0xD0] direction).
// After a full turn it releases the ball along the p+0xCC heading once that is reached.
void fn_3_D0534(C2ObjSpin* p) {
    Vec ball;
    Vec rel;
    Mtx m;
    Vec perpA;
    Vec perpB;
    Vec rel0;
    Vec out;
    f32 ang;
    f32 mag;
    Vec* bp = (Vec*)&g_Ball;
    lbl_3_bss_A030 += p->_BC;
    ball.x = bp->x;
    ball.y = bp->y;
    ball.z = bp->z;
    PSVECSubtract(&ball, &p->pos, &rel);
    rel.y = lbl_3_rodata_2664;
    rel0 = rel;
    PSMTXRotRad(m, 'Y', lbl_3_rodata_2658[0] * ((s8)p->_D0 * p->_BC));
    PSMTXMultVec(m, &rel, &rel);
    if (lbl_3_bss_A030 / lbl_3_rodata_27B8 >= lbl_3_rodata_2698) {
        perpB.y = lbl_3_rodata_2664;
        perpA.y = lbl_3_rodata_2664;
        if ((s8)p->_D0 > 0) {
            perpA.x = rel0.z;
            perpA.z = -rel0.x;
        } else {
            perpA.x = -rel0.z;
            perpA.z = rel0.x;
        }
        if ((s8)p->_D0 > 0) {
            perpB.x = rel.z;
            perpB.z = -rel.x;
        } else {
            perpB.x = -rel.z;
            perpB.z = rel.x;
        }
        PSVECNormalize(&perpA, &perpA);
        PSVECNormalize(&perpB, &perpB);
        ang = acos(PSVECDotProduct(&perpA, &perpB));
        out.x = sin(lbl_3_rodata_2658[0] * p->_CC);
        out.y = lbl_3_rodata_2664;
        out.z = cos(lbl_3_rodata_2658[0] * p->_CC);
        if ((f32)acos(PSVECDotProduct(&perpA, &out)) <= ang) {
            PSVECSubtract(&rel, &rel0, &rel);
            mag = PSVECMag(&rel);
            g_Ball.physicsSubstruct.velocity.x = out.x * mag;
            g_Ball.physicsSubstruct.velocity.y = lbl_3_rodata_2664;
            g_Ball.physicsSubstruct.velocity.z = out.z * mag;
            p->_D1 = 3;
            fn_3_65F4();
            ((StadiumObjList*)&lbl_3_common_bss_350E4)->_66[5] = 0;
            lbl_3_bss_A030 = lbl_3_rodata_2664;
            sndFXKeyOff(lbl_3_data_182C0);
            sndFXCtrl(lbl_3_data_182C0, 7, 0);
            lbl_3_data_182C0 = -1;
            return;
        }
    }
    {
        f32 z = rel.z + p->pos.z;
        f32 x = rel.x + p->pos.x;
        bp->y = ball.y;
        g_Ball.AtBat_Contact_BallPos.x = x;
        bp->z = z;
    }
}

// .text:0x000D0854 size:0xC4 mapped:0x8070F8E8
f32 fn_3_D0854(C2ObjSpin* p) {
    f32 a;
    f32 b;
    if ((s8)p->_D0 > 0) {
        T34* t = lbl_3_data_18364;
        t += p->idx;
        a = t->a;
        b = t->b;
    } else {
        T34* t = lbl_3_data_18364;
        t += p->idx;
        a = t->c;
        b = t->d;
    }
    return a + b * (fn_3_B7F70(0x3E8) / 1000.0);
}

// .text:0x000D0918 size:0x6EC mapped:0x8070F9AC
// NONMATCHING 93%: saved-register numbering (p in r28 vs r30); random direction computed via extsh; fn_3_D0854 is an inlined copy
#if NONMATCHING
#pragma dont_inline off
static inline f32 D0854_inl(C2ObjSpin* p) {
    f32 a;
    f32 b;
    if ((s8)p->_D0 > 0) {
        T34* t = lbl_3_data_18364;
        t += p->idx;
        a = t->a;
        b = t->b;
    } else {
        T34* t = lbl_3_data_18364;
        t += p->idx;
        a = t->c;
        b = t->d;
    }
    return a + b * (fn_3_B7F70(0x3E8) / 1000.0);
}
#pragma dont_inline on

// Spinning-platform update: bobs p up and down, and runs its ball state (p[0xD1]):
// 0 idle, waits for a low ball close by; 1 spinning up (random direction p[0xD0]),
// grabs the ball when it touches; 2 carrying it round (fn_3_D0534); 3 spinning down.
void fn_3_D0918(C2ObjSpin* p) {
    Vec axis;
    Vec ball;
    Vec d;
    Quaternion q;
    GameBone* model = p->actorObj->actor->boneArray[3];
    f32 dist;
    f32 a;
    f32 b;
    u8 stad;
    s32 h;
    u8 v;
    axis = lbl_3_rodata_2604;
    p->_C4 = p->_C4 + lbl_3_rodata_27C0;
    if (p->_C4 >= lbl_3_rodata_27C8) {
        p->_C4 = lbl_3_rodata_2664;
    }
    p->pos.y = lbl_3_rodata_27D0 * (f32)sin(p->_C4) + p->_C8;
    if (g_GameLogic.gameStatus != 2) {
        if (p->_D1 != 0) {
            if (p->_D1 == 2) {
                fn_3_65F4();
                ((StadiumObjList*)&lbl_3_common_bss_350E4)->_66[5] = 0;
                lbl_3_bss_A030 = lbl_3_rodata_2664;
                sndFXKeyOff(lbl_3_data_182C0);
                sndFXCtrl(lbl_3_data_182C0, 7, 0);
            }
            p->_D1 = 0;
        }
        if ((u32)lbl_3_data_182C0 != 0xFFFFFFFF) {
            sndFXKeyOff(lbl_3_data_182C0);
            sndFXCtrl(lbl_3_data_182C0, 7, 0);
        }
    }
    switch (p->_D1) {
    case 0:
        ball.x = g_Ball.AtBat_Contact_BallPos.x;
        ball.y = g_Ball.AtBat_Contact_BallPos.y;
        ball.z = g_Ball.AtBat_Contact_BallPos.z;
        PSVECSubtract(&ball, &p->pos, &d);
        d.y = lbl_3_rodata_2664;
        if (!((g_Ball.currentStarSwing2 == 3 | g_Ball.currentStarSwing2 == 4) | g_Ball.currentStarSwing2 == 0xB | g_Ball.currentStarSwing2 == 0xC) &&
            PSVECMag(&d) < lbl_3_rodata_2778 && ball.y > lbl_3_rodata_27D8 && ball.y < lbl_3_rodata_27E0 &&
            g_Ball.AtBat_ContactResult < 2) {
            p->_D1 = 1;
            {
                s8 dir = -(fn_3_B7F70(2) * 2) + 1;
                p->_D0 = dir;
                p->_D0 = dir;
            }
            p->_BC = lbl_3_data_18364[p->idx].spin;
        }
        break;
    case 1:
        p->_C0 = (s8)p->_D0 * p->_BC + p->_C0;
        ball.x = g_Ball.AtBat_Contact_BallPos.x;
        ball.y = lbl_3_rodata_2664;
        ball.z = g_Ball.AtBat_Contact_BallPos.z;
        PSVECSubtract(&ball, &p->pos, &d);
        d.y = lbl_3_rodata_2664;
        dist = PSVECMag(&d);
        if (dist < lbl_3_rodata_2778) {
            PSVECNormalize(&d, &d);
            PSVECScale(&d, lbl_3_rodata_2778, &d);
            g_Ball.AtBat_Contact_BallPos.x = p->pos.x + d.x;
            g_Ball.AtBat_Contact_BallPos.z = p->pos.z + d.z;
            p->_D1 = 2;
            fn_3_6620();
            ((StadiumObjList*)&lbl_3_common_bss_350E4)->_66[5] = 1;
            p->_CC = D0854_inl(p);
            if (p->_CC < lbl_3_rodata_2664) {
                p->_CC = lbl_3_rodata_2788 + p->_CC;
            }
            stad = g_d_GameSettings.StadiumID;
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8.b2;
            } else {
                v = lbl_3_data_8404[stad].b2;
            }
            h = sndFXStartEx((u16)(((u16*)lbl_3_data_81DC)[stad] + 1), v, 0x3F, 0);
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8.b3;
            } else {
                v = lbl_3_data_8404[stad].b3;
            }
            sndFXCtrl(h, 0x5B, v);
            lbl_3_data_182C0 = h;
        } else {
            ball.x = g_Ball.pastCoordinates[0].x;
            ball.y = lbl_3_rodata_2664;
            ball.z = g_Ball.pastCoordinates[0].z;
            PSVECSubtract(&ball, &p->pos, &d);
            d.y = lbl_3_rodata_2664;
            if (dist > PSVECMag(&d)) {
                p->_D1 = 3;
            }
        }
        break;
    case 2:
        p->_C0 = (s8)p->_D0 * p->_BC + p->_C0;
        fn_3_D0534(p);
        break;
    case 3:
        p->_BC = p->_BC - lbl_3_data_18364[p->idx].spin / lbl_3_rodata_27E4;
        p->_C0 = (s8)p->_D0 * p->_BC + p->_C0;
        if (p->_BC <= lbl_3_rodata_2664) {
            p->_D1 = 0;
        }
        break;
    }
    C_QUATRotAxisRad(&q, &axis, lbl_3_rodata_2658[0] * p->_C0);
    PSQUATMultiply((Quaternion*)(&p->rot), &q, &q);
    PSQUATNormalize(&q, &q);
    CTRLSetTranslation((Control*)p, p->pos.x, -p->pos.y, p->pos.z);
    CTRLSetQuat(&model->orientCtrl.base, q.x, q.y, q.z, q.w);
}
#endif

// .text:0x000D1004 size:0x10C mapped:0x80710098
void fn_3_D1004(C2ObjSpin* p, f32 x, f32 y, f32 z, f32 r, f32 sc) {
    GameBone* c = p->actorObj->actor->boneArray[3];
    Vec axis = lbl_3_rodata_25F8;
    Quaternion q;
    p->pos.x = x;
    p->pos.y = y;
    p->pos.z = z;
    p->_C0 = sc;
    p->ctrl.base.type = 0;
    CTRLSetTranslation((Control*)p, p->pos.x, -p->pos.y, p->pos.z);
    CTRLSetRotation((Control*)p, 0.0f, r, 0.0f);
    C_QUATRotAxisRad(&q, &axis, lbl_3_rodata_2658[0] * p->_C0);
    PSQUATMultiply(&q, (Quaternion*)(&p->rot), &q);
    PSQUATNormalize(&q, &q);
    CTRLSetQuat(&c->orientCtrl.base, q.x, q.y, q.z, q.w);
}

#pragma dont_inline off
static inline void D1004_inl(C2ObjSpin* p, f32 x, f32 y, f32 z, f32 r, f32 sc) {
    GameBone* c = p->actorObj->actor->boneArray[3];
    Vec axis = lbl_3_rodata_25F8;
    Quaternion q;
    p->pos.x = x;
    p->pos.y = y;
    p->pos.z = z;
    p->_C0 = sc;
    p->ctrl.base.type = 0;
    CTRLSetTranslation((Control*)p, p->pos.x, -p->pos.y, p->pos.z);
    CTRLSetRotation((Control*)p, 0.0f, r, 0.0f);
    C_QUATRotAxisRad(&q, &axis, lbl_3_rodata_2658[0] * p->_C0);
    PSQUATMultiply(&q, (Quaternion*)(&p->rot), &q);
    PSQUATNormalize(&q, &q);
    CTRLSetQuat(&c->orientCtrl.base, q.x, q.y, q.z, q.w);
}
#pragma dont_inline on

// .text:0x000D1110 size:0x16C mapped:0x807101A4
void fn_3_D1110(C2ObjSpin* p) {
    D1004_inl(p, lbl_3_data_18364[p->idx].x, lbl_3_data_18364[p->idx].y, lbl_3_data_18364[p->idx].z, lbl_3_data_18364[p->idx].r, 0.0f);
    p->_C8 = lbl_3_data_18364[p->idx].y;
    p->_BC = 0.0f;
    p->_C4 = 0.0f;
    p->_D1 = 0;
}

// .text:0x000D127C size:0x4 mapped:0x80710310
void fn_3_D127C(C2Obj* p) {
    return;
}

// .text:0x000D1280 size:0x19C mapped:0x80710314
void fn_3_D1280(C2ObjLink* p) {
    Vec s;
    Vec d;
    Vec v;
    f32 m;
    s32 n;
    if (g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 0) {
        p->ctrl.base.type = 0;
    }
    fn_3_D141C(p);
    PSVECAdd(&p->b->pos, &p->a->pos, &s);
    PSVECScale(&s, lbl_3_rodata_26A0, &s);
    if (g_GameLogic.gameStatus == 2 && g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        PSVECSubtract(&s, &p->pos, &d);
        m = PSVECMag(&d);
        n = p->_B4 + 1;
        if (n < 0x100) {
            p->_B4 = n;
        }
        if (m >= lbl_3_rodata_27E8 && p->_B4 > 10) {
            memcpy(&v, &p->pos, 0xC);
            v.y = v.y * lbl_3_rodata_2678;
            fn_3_8BBC4(((u16*)lbl_3_data_81DC)[g_d_GameSettings.StadiumID] + 6, (f32*)&v, 0, 0xE);
            p->_B4 = 0;
        }
    }
    PSVECScale(&s, lbl_3_rodata_2698, &p->pos);
    CTRLSetTranslation((Control*)p, p->pos.x, -p->pos.y, p->pos.z);
    CTRLSetScale((Control*)p, lbl_3_rodata_26C8, lbl_3_rodata_26C8, lbl_3_rodata_26C8);
}

// .text:0x000D141C size:0x320 mapped:0x807104B0
// Orients p (a Control) along the segment between its two chain nodes (p+0xAC -> p+0xB0):
// yaw about axis 25D4, pitch about axis 25E0, plus a quarter roll about 25C8 for even p+0x9C.
// NONMATCHING 98%: f0/f1 swapped for the 0.0f constant vs PSVECMag results
#if NONMATCHING
void fn_3_D141C(C2ObjLink* p) {
    Vec d;
    Vec flatY;
    Vec flatXZ;
    Quaternion q;
    Quaternion qRoll;
    Quaternion qYaw;
    Quaternion qPitch;
    Vec axRoll;
    Vec axYaw;
    Vec axPitch;
    f32 roll, yaw, pitch, a;
    roll = yaw = pitch = lbl_3_rodata_2664;
    axRoll = lbl_3_rodata_25C8;
    axYaw = lbl_3_rodata_25D4;
    axPitch = lbl_3_rodata_25E0;
    PSVECSubtract(&(p->b)->pos, &(p->a)->pos, &d);
    flatY = flatXZ = d;
    flatXZ.x = sqrt(pow(flatXZ.x, lbl_3_rodata_26E8) + pow(flatXZ.z, lbl_3_rodata_26E8));
    flatXZ.z = lbl_3_rodata_2664;
    flatY.y = lbl_3_rodata_2664;
    PSVECNormalize(&d, &d);
    if (PSVECMag(&flatY) != lbl_3_rodata_2664) {
        PSVECNormalize(&flatY, &flatY);
        a = acos(PSVECDotProduct(&axRoll, &flatY));
        yaw = a;
        if (flatY.z > lbl_3_rodata_2664) {
            yaw = a * lbl_3_rodata_2678;
        }
    }
    if (PSVECMag(&flatXZ) != lbl_3_rodata_2664) {
        PSVECNormalize(&flatXZ, &flatXZ);
        a = acos(PSVECDotProduct(&axRoll, &flatXZ));
        pitch = a;
        if (flatXZ.y > lbl_3_rodata_2664) {
            pitch = a * lbl_3_rodata_2678;
        }
    }
    if (roll != lbl_3_rodata_2664 || yaw != lbl_3_rodata_2664 || pitch != lbl_3_rodata_2664) {
        C_QUATRotAxisRad(&qYaw, &axYaw, yaw);
        C_QUATRotAxisRad(&qPitch, &axPitch, pitch);
        if (p->idx % 2 == 0) {
            roll = lbl_3_rodata_27EC;
        }
        C_QUATRotAxisRad(&qRoll, &axRoll, roll);
        q = qYaw;
        PSQUATMultiply(&q, &qPitch, &q);
        PSQUATMultiply(&q, &qRoll, &q);
        PSQUATNormalize(&q, &q);
        if (PSQUATDotProduct(&q, &q) == lbl_3_rodata_2664) {
            C_QUATRotAxisRad(&q, &axRoll, lbl_3_rodata_2664);
        }
        CTRLSetQuat((Control*)p, q.x, q.y, q.z, q.w);
    }
}
#endif

// .text:0x000D173C size:0x10C mapped:0x807107D0
void fn_3_D173C(C2ObjComp* p) {
    Mtx b;
    Mtx a;
    s32 off;
    u32 i;
    PSMTXInverse(((camera_803c639c_s*)fn_80052734(fn_8005268C()))->view, b);
    PSMTXIdentity(a);
    a[0][0] = cos(lbl_3_rodata_27F0);
    a[0][2] = -(f32)sin(lbl_3_rodata_27F0);
    a[2][0] = sin(lbl_3_rodata_27F0);
    a[2][2] = cos(lbl_3_rodata_27F0);
    PSMTXConcat(b, a, b);
    i = 0;
    off = 0;
    b[2][3] = 0.0f;
    b[1][3] = 0.0f;
    b[0][3] = 0.0f;
    while (i < p->actorObj->actor->totalBones) {
        GameBone* o = *(GameBone**)((u8*)p->actorObj->actor->boneArray + off); // off = i * sizeof(GameBone*)
        f32 (*m)[4] = o->forwardMtx;
        PSMTXConcat(b, m, m);
        off += 4;
        i++;
    }
}

// .text:0x000D1848 size:0x124 mapped:0x807108DC
void fn_3_D1848(C2ObjComp* s) {
    ActorObject* act = s->actorObj;
    if (*s->mainFlag != 0) {
        if (s->visible) {
            s->visible = 0;
            s->delay = (s->idx % 3) * 30;
            s->time = 0.0f;
            act->time = s->time;
            act->setTime = 1;
            fn_800B4CA0(act->actor, act->time);
        }
        return;
    }
    if (s->delay != 0) {
        if (s->visible) {
            s->visible = 0;
        }
        s->delay--;
        return;
    }
    if (!s->visible) {
        s->visible = 1;
    }
    s->time = s->time + s->speed;
    if (s->time > 100.0f) {
        s->time = s->time - 100.0f;
        s->delay = 90;
    }
    AnimateActorBones(act->actor);
}

// .text:0x000D196C size:0x158 mapped:0x80710A00
void fn_3_D196C(s32 idx, s32 hitType, struct _CollisionStruct* hit) {
    C2ObjMain* e = (C2ObjMain*)((C2Obj*)lbl_3_common_bss_350E4.objs + idx);
    Vec v;
    s32 k;
    if (g_Ball.ballState != 1) {
        if (e->_CA == 0) {
            e->_99 = e->_99 & 0xFB;
            e->_CC = 5;
            e->_CB = e->_CA;
            e->_CA = 2;
            e->_AC.y = 0.5f;
            fn_80025EEC(e->_8C, 0, 3);
        }
        memcpy(&v, &g_Ball.AtBat_Contact_BallPos, sizeof(Vec));
        v.y = v.y * lbl_3_rodata_2678;
        fn_3_8BBC4(((u16*)lbl_3_data_81DC)[g_d_GameSettings.StadiumID] + 5, (f32*)&v, 0, 0xD);
        k = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0;
        lbl_3_bss_A898[k] = 1;
        lbl_3_bss_A820[k].x = g_Ball.AtBat_Contact_BallPos.x;
        lbl_3_bss_A820[k].y = -g_Ball.AtBat_Contact_BallPos.y;
        lbl_3_bss_A820[k].z = g_Ball.AtBat_Contact_BallPos.z;
        fn_3_65A8();
        fn_3_27648();
        g_FieldingLogic._13B = 1;
    }
}

// .text:0x000D1AC4 size:0x60 mapped:0x80710B58
void fn_3_D1AC4(C2ObjMain* p) {
    DisplayStateList* q;
    q = PTR32_GET(DisplayStateList, p->actorObj->actor->boneArray[0]->dispObj->displayData->displayStateList);
    if (p->_CA == 0) {
        q[7].setting = q[7].setting & 0xFFFFE000;
        q[7].setting = q[7].setting | 3;
    } else {
        q[7].setting = q[7].setting & 0xFFFFE000;
        q[7].setting = q[7].setting | 2;
    }
}

// .text:0x000D1B24 size:0x408 mapped:0x80710BB8
// Accumulates the forces on each chain node: gravity (the last node gets grav instead),
// damped springs between neighbours, air drag and ground friction.
// NONMATCHING 95%: saved-register assignment differs; target reloads 0.0f in the drag/friction loop
#if NONMATCHING
void fn_3_D1B24(CC438Cfg* cfg, RopeNode* nodes, s32 n, Vec* grav) {
    Vec dv;
    Vec d;
    Vec extra;
    RopeNode* r;
    RopeNode* prev;
    s32 i;
    f32 zero, len, spring, fs, mag, fric, side;
    for (r = nodes, i = 0; i < n; r++, i++) {
        memset(&r->force, 0, sizeof(Vec));
        if (r->pinned == 0 && i != n - 1) {
            r->force.y = lbl_3_rodata_27F4 * r->mass;
        }
        if (i == n - 1) {
            PSVECAdd(&r->force, grav, &r->force);
        }
    }
    zero = lbl_3_rodata_2664;
    for (i = n, r = &nodes[n]; --r, --i != 0;) {
        prev = &nodes[i - 1];
        PSVECSubtract(&r->pos, &prev->pos, &d);
        PSVECSubtract(&r->vel, &prev->vel, &dv);
        len = PSVECMag(&d);
        spring = cfg->c * (len - cfg->a);
        fs = cfg->d * (PSVECDotProduct(&dv, &d) / len);
        fs = -(spring + fs);
        if (PSVECMag(&d) == zero) {
            d.z = zero;
            d.x = zero;
            d.y = lbl_3_rodata_2678;
        }
        PSVECNormalize(&d, &d);
        PSVECScale(&d, fs, &d);
        if (r->pinned == 0) {
            PSVECAdd(&r->force, &d, &r->force);
        }
        PSVECScale(&d, lbl_3_rodata_2678, &d);
        if (prev->pinned == 0) {
            PSVECAdd(&prev->force, &d, &prev->force);
        }
    }
    for (r = nodes, i = 0; i < n; r++, i++) {
        if (r->pinned == 0) {
            memcpy(&dv, &r->vel, sizeof(Vec));
            memcpy(&d, &r->force, sizeof(Vec));
            PSVECScale(&d, r->invMass, &d);
            PSVECScale(&d, cfg->h, &d);
            PSVECAdd(&dv, &d, &dv);
            memset(&extra, 0, sizeof(Vec));
            mag = PSVECMag(&dv);
            if (mag != lbl_3_rodata_2664) {
                PSVECScale(&dv, lbl_3_rodata_2678, &d);
                PSVECNormalize(&d, &d);
                PSVECScale(&d, cfg->f * (mag * mag), &d);
                PSVECAdd(&extra, &d, &extra);
            }
            if (r->pos.y <= r->radius && r->force.y < lbl_3_rodata_2664) {
                fric = r->force.y * cfg->e;
                if (fric < lbl_3_rodata_2664) {
                    fric = -fric;
                }
                memcpy(&d, &r->force, sizeof(Vec));
                d.y = lbl_3_rodata_2664;
                side = PSVECMag(&d);
                dv.y = lbl_3_rodata_2664;
                mag = PSVECMag(&dv);
                if (mag != lbl_3_rodata_2664 || side > fric) {
                    if (mag != lbl_3_rodata_2664) {
                        PSVECNormalize(&dv, &d);
                    } else {
                        PSVECNormalize(&d, &d);
                    }
                    PSVECScale(&d, -fric, &d);
                    PSVECAdd(&extra, &d, &extra);
                } else {
                    PSVECScale(&r->force, lbl_3_rodata_2678, &d);
                    PSVECAdd(&extra, &d, &extra);
                }
            }
            PSVECAdd(&r->force, &extra, &r->force);
        }
    }
}
#endif

// .text:0x000D1F2C size:0x2F4 mapped:0x80710FC0
// Verlet-integrates the chain cfg->n substeps: gravity dir*cfg->h, ground bounce,
// and pushes nodes out of the sphere (radius 4.5) around the owner p (p+0xA0, raised 4.5).
void fn_3_D1F2C(CC438Cfg* cfg, RopeNode* nodes, s32 n, Vec* dir, C2ObjMain* p) {
    Vec acc;
    Vec grav;
    Vec center;
    Vec d;
    Vec nd;
    Vec push;
    Vec ah;
    Vec next;
    RopeNode* r;
    s32 i;
    f32 hh, inv, mag, dy;
    s32 step;
    center = *(Vec*)(&p->pos);
    center.y = center.y + lbl_3_rodata_2668;
    PSVECScale(dir, cfg->h, &grav);
    for (step = 0; step < cfg->n; step++) {
        fn_3_D1B24(cfg, nodes, n, &grav);
        for (r = nodes, i = 0; i < n; r++, i++) {
            PSVECScale(&r->force, r->invMass, &acc);
            inv = cfg->inv;
            hh = cfg->hh;
            PSVECScale(&r->pos, lbl_3_rodata_26B8, &next);
            PSVECSubtract(&next, &r->prev, &next);
            PSVECScale(&acc, hh, &ah);
            PSVECAdd(&next, &ah, &next);
            PSVECSubtract(&next, &r->prev, &r->vel);
            PSVECScale(&r->vel, inv, &r->vel);
            memcpy(&r->prev, &r->pos, sizeof(Vec));
            memcpy(&r->pos, &next, sizeof(Vec));
            if (r->pinned == 0) {
                dy = r->pos.y - r->radius;
                if (dy < lbl_3_rodata_2664) {
                    r->pos.y = r->pos.y - dy * cfg->b;
                    dy = r->prev.y - r->radius;
                    r->prev.y = r->prev.y - dy * cfg->b;
                }
                PSVECSubtract(&r->pos, &center, &d);
                mag = PSVECMag(&d);
                if (lbl_3_rodata_2668 + r->radius > mag) {
                    PSVECNormalize(&d, &nd);
                    PSVECScale(&nd, lbl_3_rodata_2668 + r->radius - mag, &push);
                    r->pos.x = push.x * cfg->b + r->pos.x;
                    r->pos.y = push.y * cfg->b + r->pos.y;
                    r->pos.z = push.z * cfg->b + r->pos.z;
                    PSVECSubtract(&r->prev, &center, &d);
                    mag = PSVECMag(&d);
                    PSVECNormalize(&d, &nd);
                    PSVECScale(&nd, lbl_3_rodata_2668 + r->radius - mag, &push);
                    r->prev.x = push.x * cfg->b + r->prev.x;
                    r->prev.y = push.y * cfg->b + r->prev.y;
                    r->prev.z = push.z * cfg->b + r->prev.z;
                }
            }
        }
    }
}

// .text:0x000D2220 size:0x11C mapped:0x807112B4
void fn_3_D2220(C2ObjMain* p) {
    RopeNode* c = p->nodes;
    Mtx m;
    Vec axis = lbl_3_rodata_25B0;
    Vec dir = lbl_3_rodata_25BC;
    Vec v;
    PSMTXRotAxisRad(m, &axis, 0.017453292f * p->_C0);
    PSMTXMultVec(m, lbl_3_rodata_24E8, &v);
    PSVECAdd(&v, &p->pos, &v);
    v.y += 4.5;
    c[7].pos = v;
    c[7].prev = c[7].pos;
    fn_3_D1F2C(&lbl_3_bss_A8A8, p->nodes, 8, &dir, p);
}

// .text:0x000D233C size:0x160 mapped:0x807113D0
u8* fn_3_D233C(C2ObjMain* p) {
    Mtx m;
    Vec diff;
    Vec rot;
    Vec dir = lbl_3_rodata_2580;
    Vec axis = lbl_3_rodata_258C;
    Vec pos = *(Vec*)(&p->pos);
    if (g_Ball.AtBat_ContactResult >= 2) {
        return 0;
    }
    pos.y = lbl_3_rodata_265C;
    PSVECSubtract(&g_Ball.AtBat_Contact_BallPos, &pos, &diff);
    diff.y = lbl_3_rodata_2664;
    if (PSVECMag(&diff) < lbl_3_rodata_27F8) {
        PSVECNormalize(&diff, &diff);
        PSMTXRotAxisRad(m, &axis, lbl_3_rodata_2658[0] * p->_C0);
        PSMTXMultVec(m, &dir, &rot);
        if (lbl_3_rodata_2670 * (f32)acos(PSVECDotProduct(&diff, &rot)) <= lbl_3_rodata_26B4) {
            return (u8*)&g_Ball.AtBat_Contact_BallPos;
        }
    }
    return 0;
}

// .text:0x000D249C size:0x4C mapped:0x80711530
s32 fn_3_D249C(C2ObjMain* p) {
    Vec v;
    RopeNode* o = p->nodes;
    PSVECSubtract(&o[7].pos, &o[0].pos, &v);
    return PSVECMag(&v) > lbl_3_rodata_2800;
}

// .text:0x000D24E8 size:0x74 mapped:0x8071157C
void fn_3_D24E8(C2ObjMain* p, s32 idx0) {
    s8 idx = idx0;
    Vec v;
    PSVECSubtract(&g_Fielders[idx].pos, &p->pos, &v);
    v.y = lbl_3_rodata_2664;
    PSVECNormalize(&v, &v);
    fn_3_253A4(idx, fn_3_9FB8C(v.x, v.z));
}

// .text:0x000D255C size:0x128 mapped:0x807115F0
s32 fn_3_D255C(C2ObjMain* p) {
    Vec d;
    B9 a = lbl_3_rodata_255C;
    B9 b = lbl_3_rodata_2568;
    u32 i;
    u8* t;
    f64 lim;
    InMemFielderType* fl;
    if (p->pos.y > lbl_3_rodata_2770) {
        return -1;
    }
    if (p->pos.x > lbl_3_rodata_2664) {
        t = a.b;
    } else {
        t = b.b;
    }
    fl = g_Fielders;
    lim = lbl_3_rodata_2668;
    for (i = 0; i < 9; i++) {
        InMemFielderType* o = fl + t[i];
        if (o != NULL && o->knockback == 0) {
            PSVECSubtract(&p->pos, &o->pos, &d);
            if (PSVECMag(&d) <= lim) {
                return (s8)t[i];
            }
        }
    }
    return -1;
}

// .text:0x000D2684 size:0x108 mapped:0x80711718
u8* fn_3_D2684(C2ObjMain* p) {
    Vec d;
    B9 a = lbl_3_rodata_2544;
    B9 b = lbl_3_rodata_2550;
    u8* t;
    u32 i;
    if (p->pos.x > 0.0f) {
        t = a.b;
    } else {
        t = b.b;
    }
        for (i = 0; i < 4; i++) {
        CharActor* o = lbl_8036E548.active[t[i]];
        if (o != NULL) {
            PSVECSubtract(&p->pos, &o->pos, &d);
            if (PSVECMag(&d) <= 12.5f) {
                return (u8*)&o->pos;
            }
        }
    }
    return 0;
}

// .text:0x000D278C size:0x280 mapped:0x80711820
extern f32 lbl_3_rodata_2810;
extern f32 lbl_3_rodata_2814;
#ifdef PORT_LP64
typedef struct { u8 pad[STADIUM_OBJ_PAD(0xA0)]; f32 a0, a4, a8, ac, b0, b4; } D278F;
#else
typedef struct { u8 pad[0xA0]; f32 a0, a4, a8, ac, b0, b4; } D278F;
#endif
void fn_3_D278C(C2ObjMain* p) {
    RopeNode* c;
    Mtx m;
    Vec d;
    Vec w;
    Vec v;
    Vec dir;
    Vec axis;
    p->pos.x = p->pos.x + p->_AC.x;
    p->pos.y = p->pos.y + p->_AC.y;
    p->pos.z = p->pos.z + p->_AC.z;
    p->_AC.y = p->_AC.y - lbl_3_rodata_280C[0];
    if (p->pos.y < 0.0f) {
        p->pos.y = 0.0f;
        PSVECSubtract(p->_B8, &p->pos, &d);
        if (lbl_3_rodata_2778 >= PSVECMag(&d)) {
            p->_CA = 1;
            if ((p->_B8)->x < 0.0f) {
                p->_C0 = 0.0f;
            } else {
                p->_C0 = lbl_3_rodata_2810;
            }
        } else {
            p->_AC.y = lbl_3_rodata_2814;
        }
        memcpy(&w, &p->pos, 0xC);
        w.y = w.y * lbl_3_rodata_2678;
        fn_3_8BBC4(((u16*)lbl_3_data_81DC)[g_d_GameSettings.StadiumID] + 2, (f32*)&w, 0, 0xA);
        fn_8004C094(&p->pos);
    }
    CTRLSetTranslation((Control*)p, p->pos.x, -p->pos.y, p->pos.z);
    CTRLSetRotation((Control*)p, 0.0f, p->_C0, 0.0f);
    c = p->nodes;
    axis = lbl_3_rodata_25B0;
    dir = lbl_3_rodata_25BC;
    PSMTXRotAxisRad(m, &axis, lbl_3_rodata_2658[0] * p->_C0);
    PSMTXMultVec(m, lbl_3_rodata_24E8, &v);
    PSVECAdd(&v, &p->pos, &v);
    v.y += lbl_3_rodata_2668;
    c[7].pos = v;
    c[7].prev = c[7].pos;
    fn_3_D1F2C(&lbl_3_bss_A8A8, p->nodes, 8, &dir, p);
}

// .text:0x000D2A0C size:0x6C4 mapped:0x80711AA0
// NONMATCHING ~88%: frame/saved-register layout differs (target keeps a float in f31); same calls and stores
#if NONMATCHING
#pragma dont_inline off
// Inlined copies of fn_3_D2220 / fn_3_D249C / fn_3_D255C / fn_3_D24E8.
static inline void D2220_inl(C2ObjMain* p) {
    RopeNode* c;
    Mtx m;
    Vec v;
    Vec dir;
    Vec axis;
    c = p->nodes;
    axis = lbl_3_rodata_25B0;
    dir = lbl_3_rodata_25BC;
    PSMTXRotAxisRad(m, &axis, lbl_3_rodata_2658[0] * p->_C0);
    PSMTXMultVec(m, lbl_3_rodata_24E8, &v);
    PSVECAdd(&v, &p->pos, &v);
    v.y += lbl_3_rodata_2668;
    c[7].pos = v;
    c[7].prev = c[7].pos;
    fn_3_D1F2C(C2_BSS(CC438Cfg, lbl_3_bss_A8A8, lbl_3_bss_A018, 0x890), p->nodes, 8, &dir, p);
}

static inline s32 D249C_inl(C2ObjMain* p) {
    Vec v;
    RopeNode* o = p->nodes;
    PSVECSubtract(&o[7].pos, &o[0].pos, &v);
    return PSVECMag(&v) > lbl_3_rodata_2800;
}

static inline s32 D255C_inl(C2ObjMain* p) {
    Vec d;
    B9 a = lbl_3_rodata_255C;
    B9 b = lbl_3_rodata_2568;
    u32 i;
    u8* t;
    if (p->pos.y > lbl_3_rodata_2770) {
        return -1;
    }
    if (p->pos.x > lbl_3_rodata_2664) {
        t = a.b;
    } else {
        t = b.b;
    }
    for (i = 0; i < 9; i++) {
        InMemFielderType* o = &g_Fielders[t[i]];
        if (o != NULL && o->knockback == 0) {
            PSVECSubtract(&p->pos, &o->pos, &d);
            if (PSVECMag(&d) <= lbl_3_rodata_2668) {
                return (s8)t[i];
            }
        }
    }
    return -1;
}

static inline void D24E8_inl(C2ObjMain* p, s32 idx0) {
    s8 idx = idx0;
    Vec v;
    PSVECSubtract(&g_Fielders[idx].pos, &p->pos, &v);
    v.y = lbl_3_rodata_2664;
    PSVECNormalize(&v, &v);
    fn_3_253A4(idx, fn_3_9FB8C(v.x, v.z));
}
#pragma dont_inline on

// Flying state of a stadium object knocked into the air: integrates p+0xAC velocity
// with gravity, plays the apex/landing sounds, bats the ball away if it touches it,
// and bounces off (state 5) when the chain over-stretches or a fielder is hit.
void fn_3_D2A0C(C2ObjMain* p) {
    Vec x;
    Vec w;
    Vec c;
    Vec d;
    Vec n;
    Vec bw;
    s32 idx;
    f32 vy;
    f32 ang;
    x = lbl_3_rodata_252C;
    vy = p->_AC.y;
    p->pos.x += p->_AC.x;
    p->pos.y += p->_AC.y;
    p->pos.z += p->_AC.z;
    p->_AC.y -= lbl_3_rodata_280C[0];
    if (vy > lbl_3_rodata_2664 && p->_AC.y <= lbl_3_rodata_2664) {
        memcpy(&w, &p->pos, sizeof(Vec));
        w.y = w.y * lbl_3_rodata_2678;
        fn_3_8BBC4(((u16*)lbl_3_data_81DC)[g_d_GameSettings.StadiumID] + 3, (f32*)&w, 0, 0xB);
    }
    if (p->pos.y < lbl_3_rodata_2664) {
        p->pos.y = lbl_3_rodata_2664;
        p->_AC.y = lbl_3_rodata_27E8;
        memcpy(&w, &p->pos, sizeof(Vec));
        w.y = w.y * lbl_3_rodata_2678;
        fn_3_8BBC4(((u16*)lbl_3_data_81DC)[g_d_GameSettings.StadiumID] + 2, (f32*)&w, 0, 0xA);
        fn_8004C094(&p->pos);
    }
    CTRLSetTranslation((Control*)p, p->pos.x, -p->pos.y, p->pos.z);
    CTRLSetRotation((Control*)p, lbl_3_rodata_2664, p->_C0, lbl_3_rodata_2664);
    D2220_inl(p);
    if (g_Ball.AtBat_ContactResult < 2) {
        c.x = p->pos.x;
        c.y = p->pos.y;
        c.z = p->pos.z;
        c.y += lbl_3_rodata_2668;
        PSVECSubtract(&g_Ball.AtBat_Contact_BallPos, &c, &d);
        if (g_Ball.AtBat_Contact_BallPos.y < c.y) {
            d.y = lbl_3_rodata_2664;
        }
        if (PSVECMag(&d) < lbl_3_rodata_2668) {
            PSVECNormalize(&d, &n);
            g_Ball.AtBat_Contact_BallPos.x = lbl_3_rodata_2668 * n.x + c.x;
            g_Ball.AtBat_Contact_BallPos.z = lbl_3_rodata_2668 * n.z + c.z;
            g_Ball.physicsSubstruct.velocity.x = lbl_3_rodata_2818 * n.x;
            g_Ball.physicsSubstruct.velocity.y = lbl_3_rodata_2818 * n.y;
            g_Ball.physicsSubstruct.velocity.z = lbl_3_rodata_2818 * n.z;
            p->_CA = 5;
            memcpy(&bw, &g_Ball, sizeof(Vec));
            bw.y = bw.y * lbl_3_rodata_2678;
            fn_3_8BBC4(((u16*)lbl_3_data_81DC)[g_d_GameSettings.StadiumID] + 5, (f32*)&bw, 0, 0xD);
            fn_3_27648();
            g_FieldingLogic._13B = 1;
            fn_3_6530();
            C2_BSS(Vec, lbl_3_bss_A820, lbl_3_bss_A018, 0x808)[1].z = g_Ball.AtBat_Contact_BallPos.z;
            C2_BSS(u8, lbl_3_bss_A898, lbl_3_bss_A018, 0x880)[1] = 1;
            C2_BSS(Vec, lbl_3_bss_A820, lbl_3_bss_A018, 0x808)[1].x = g_Ball.AtBat_Contact_BallPos.x;
            C2_BSS(Vec, lbl_3_bss_A820, lbl_3_bss_A018, 0x808)[1].y = -g_Ball.AtBat_Contact_BallPos.y;
        }
    }
    if (D249C_inl(p)) {
        p->_CA = 5;
    }
    idx = D255C_inl(p);
    if (idx >= 0) {
        D24E8_inl(p, idx);
        p->_CA = 5;
    }
    if (p->_CA == 5) {
        PSVECNormalize(&p->_AC, &n);
        n.x = n.x * lbl_3_rodata_2678;
        n.z = n.z * lbl_3_rodata_2678;
        p->_AC.x = lbl_3_rodata_2820 * n.x;
        p->_AC.y = lbl_3_rodata_2814;
        p->_AC.z = lbl_3_rodata_2820 * n.z;
        ang = -(lbl_3_rodata_2670 * (f32)acos(PSVECDotProduct(&x, &n)));
        if (n.z < lbl_3_rodata_2664) {
            ang *= lbl_3_rodata_2678;
        }
        p->_C0 = ang;
        fn_80025EEC(p->_8C, 0, 1);
    }
}
#endif

// .text:0x000D30D0 size:0x5E0 mapped:0x80712164
// NONMATCHING ~90%: the inlined fielder search (fn_3_D255C) is structured differently; register numbering
#if NONMATCHING
// Hopping state: bounces p up and down (p+0xB0 vertical speed); on each landing it turns
// towards the ball and lunges (state 4) when the ball is near and low, or gives up
// (state 1) when it is far. Then steps the chain and knocks back a fielder it lands on.
void fn_3_D30D0(C2ObjMain* p) {
    Vec x;
    Vec from;
    Vec to;
    Vec d;
    Vec n;
    Vec w;
    Vec v;
    Vec dir;
    Vec axis;
    Mtx m;
    Vec fd;
    Vec kd;
    B9 a;
    B9 b;
    u8* t;
    RopeNode* c;
    u32 i;
    s32 idx;
    f32 vy;
    f32 dot;
    f32 ang;
    x = lbl_3_rodata_2520;
    vy = p->_AC.y;
    p->pos.y += vy;
    p->_AC.y -= lbl_3_rodata_280C[0];
    if (vy > lbl_3_rodata_2664 && p->_AC.y <= lbl_3_rodata_2664) {
        memcpy(&w, &p->pos, sizeof(Vec));
        w.y = w.y * lbl_3_rodata_2678;
        fn_3_8BBC4(((u16*)lbl_3_data_81DC)[g_d_GameSettings.StadiumID] + 3, (f32*)&w, 0, 0xB);
    }
    if (p->pos.y < lbl_3_rodata_2664) {
        p->pos.y = lbl_3_rodata_2664;
        p->_AC.y = lbl_3_rodata_2828;
        from.x = p->pos.x;
        from.y = lbl_3_rodata_2664;
        from.z = p->pos.z;
        to.x = g_Ball.AtBat_Contact_BallPos.x;
        to.y = lbl_3_rodata_2664;
        to.z = g_Ball.AtBat_Contact_BallPos.z;
        PSVECSubtract(&to, &from, &d);
        if (PSVECMag(&d) == lbl_3_rodata_2664) {
            d.z = lbl_3_rodata_2664;
            d.y = lbl_3_rodata_2664;
            d.x = lbl_3_rodata_2698;
        }
        PSVECNormalize(&d, &n);
        dot = PSVECDotProduct(&x, &n);
        if (dot > lbl_3_rodata_2698) {
            dot = lbl_3_rodata_2698;
        } else if (dot < lbl_3_rodata_2678) {
            dot = lbl_3_rodata_2678;
        }
        ang = acos(dot);
        if (n.z < lbl_3_rodata_2664) {
            ang = lbl_3_rodata_27C8 - ang;
        }
        ang = lbl_3_rodata_2670 * ang;
        if ((PSVECMag(&d) <= lbl_3_rodata_2808 || g_Ball.ballState == 1) && p->_C8 > 0 &&
            g_Ball.AtBat_Contact_BallPos.y <= lbl_3_rodata_2830) {
            p->_CA = 4;
            p->_BC = ang;
            p->_AC.x = lbl_3_rodata_2838 * (f32)cos(lbl_3_rodata_2658[0] * p->_BC);
            p->_AC.y = lbl_3_rodata_2664;
            p->_AC.z = lbl_3_rodata_2838 * (f32)sin(lbl_3_rodata_2658[0] * p->_BC);
            p->_C8 -= 1;
        } else if (PSVECMag(&d) > lbl_3_rodata_2840) {
            p->_CA = 1;
            p->_AC.y = lbl_3_rodata_2664;
            fn_80025EEC(p->_8C, 0, 1);
        }
        memcpy(&w, &p->pos, sizeof(Vec));
        w.y = w.y * lbl_3_rodata_2678;
        fn_3_8BBC4(((u16*)lbl_3_data_81DC)[g_d_GameSettings.StadiumID] + 2, (f32*)&w, 0, 0xA);
        p->_C0 = -ang;
        fn_8004C094(&p->pos);
    }
    CTRLSetTranslation((Control*)p, p->pos.x, -p->pos.y, p->pos.z);
    CTRLSetRotation((Control*)p, lbl_3_rodata_2664, p->_C0, lbl_3_rodata_2664);
    // fn_3_D2220, inlined
    c = p->nodes;
    axis = lbl_3_rodata_25B0;
    dir = lbl_3_rodata_25BC;
    PSMTXRotAxisRad(m, &axis, lbl_3_rodata_2658[0] * p->_C0);
    PSMTXMultVec(m, lbl_3_rodata_24E8, &v);
    PSVECAdd(&v, &p->pos, &v);
    v.y += lbl_3_rodata_2668;
    c[7].pos = v;
    c[7].prev = c[7].pos;
    fn_3_D1F2C(&lbl_3_bss_A8A8, p->nodes, 8, &dir, p);
    // fn_3_D255C, inlined
    a = lbl_3_rodata_255C;
    b = lbl_3_rodata_2568;
    idx = -1;
    if (!(p->pos.y > lbl_3_rodata_2770)) {
        if (p->pos.x > lbl_3_rodata_2664) {
            t = a.b;
        } else {
            t = b.b;
        }
        for (i = 0; i < 9; i++) {
            InMemFielderType* o = &g_Fielders[t[i]];
            if (o != NULL && o->knockback == 0) {
                PSVECSubtract(&p->pos, &o->pos, &fd);
                if (PSVECMag(&fd) <= lbl_3_rodata_2668) {
                    idx = (s8)t[i];
                    break;
                }
            }
        }
    }
    // fn_3_D24E8, inlined
    if (idx >= 0) {
        PSVECSubtract(&g_Fielders[idx].pos, &p->pos, &kd);
        kd.y = lbl_3_rodata_2664;
        PSVECNormalize(&kd, &kd);
        fn_3_253A4(idx, fn_3_9FB8C(kd.x, kd.z));
    }
}
#endif

// .text:0x000D36B0 size:0x1D0 mapped:0x80712744
void fn_3_D36B0(C2ObjMain* p) {
    RopeNode* c;
    Mtx m;
    Vec v;
    Vec dir;
    Vec axis;
    p->pos.y = p->pos.y + p->_AC.y;
    p->_AC.y = p->_AC.y - lbl_3_rodata_280C[0];
    if (p->pos.y < 0.0f) {
        p->pos.y = 0.0f;
        if (!(p->_99 & 4)) {
            p->_CB = p->_CA;
            p->_CA = 1;
            fn_80025EEC(p->_8C, 0, 1);
        }
        p->_99 = p->_99 & 0xFB;
        fn_8004C094(&p->pos);
    }
    c = p->nodes;
    axis = lbl_3_rodata_25B0;
    dir = lbl_3_rodata_25BC;
    PSMTXRotAxisRad(m, &axis, lbl_3_rodata_2658[0] * p->_C0);
    PSMTXMultVec(m, lbl_3_rodata_24E8, &v);
    PSVECAdd(&v, &p->pos, &v);
    v.y += lbl_3_rodata_2668;
    c[7].pos = v;
    c[7].prev = c[7].pos;
    fn_3_D1F2C(&lbl_3_bss_A8A8, p->nodes, 8, &dir, p);
    CTRLSetRotation((Control*)p, 0.0f, p->_C0, 0.0f);
    CTRLSetTranslation((Control*)p, p->pos.x, -p->pos.y, p->pos.z);
}

// .text:0x000D3880 size:0x45C mapped:0x80712914
// NONMATCHING 97%: the zero-length test compiles to a plain branch (target goes through cntlzw); cos/0.26 scheduling
#if NONMATCHING
// Turns p to face the ball while it is low and in front (within 60 degrees) during game
// state 2; when it gets close (21.25) it swings (state 4 if within 12.5 or g_Ball[0x1BC9]==1,
// else 3) and plays the stadium sound. Then steps the 8-node chain.
void fn_3_D3880(C2ObjMain* p) {
    Mtx m;
    Vec d;
    Vec flat;
    Vec c;
    Vec x;
    Vec fwd;
    Vec s1;
    Vec s2;
    Vec v;
    Vec dir;
    Vec axis;
    f32 dot;
    f32 ang;
    f32 dist;
    RopeNode* n;
    x = lbl_3_rodata_2514;
    memcpy(&c, &p->pos, sizeof(Vec));
    c.y += lbl_3_rodata_2668;
    if (g_GameLogic.gameStatus == 2 && !(g_Ball.AtBat_Contact_BallPos.y > lbl_3_rodata_2830)) {
        PSVECSubtract(&g_Ball.AtBat_Contact_BallPos, &c, &d);
        memcpy(&flat, &d, sizeof(Vec));
        flat.y = lbl_3_rodata_2664;
        if (PSVECMag(&flat) == lbl_3_rodata_2664) {
            flat.x = lbl_3_rodata_2698;
        }
        PSVECNormalize(&flat, &flat);
        memset(&fwd, 0, sizeof(Vec));
        fwd.x = cos(lbl_3_rodata_2658[0] * -p->_C0);
        fwd.z = sin(lbl_3_rodata_2658[0] * -p->_C0);
        PSVECNormalize(&fwd, &fwd);
        if (lbl_3_rodata_2670 * (f32)acos(PSVECDotProduct(&flat, &fwd)) <= lbl_3_rodata_26B4) {
            PSVECNormalize(&x, &x);
            dot = PSVECDotProduct(&flat, &x);
            if (dot > lbl_3_rodata_2698) {
                dot = lbl_3_rodata_2698;
            } else if (dot < lbl_3_rodata_2678) {
                dot = lbl_3_rodata_2678;
            }
            ang = lbl_3_rodata_2670 * (f32)acos(dot);
            if (flat.z < lbl_3_rodata_2664) {
                ang *= lbl_3_rodata_2678;
            }
            p->_C0 = -ang;
            dist = PSVECMag(&d);
            if (dist <= lbl_3_rodata_2840 && p->_C8 > 0) {
                p->_BC = ang;
                if (dist <= lbl_3_rodata_2808 || g_Ball.ballState == 1) {
                    p->_CA = 4;
                    p->_AC.x = lbl_3_rodata_2838 * (f32)cos(lbl_3_rodata_2658[0] * p->_BC);
                    p->_AC.y = lbl_3_rodata_27E8;
                    p->_AC.z = lbl_3_rodata_2838 * (f32)sin(lbl_3_rodata_2658[0] * p->_BC);
                    p->_C8 -= 1;
                } else {
                    p->_CA = 3;
                    p->_AC.y = lbl_3_rodata_2828;
                }
                fn_80025EEC(p->_8C, 0, 4);
                // s1/s2 are passed uninitialised, as in the original.
                fn_3_8BBC4(((u16*)lbl_3_data_81DC)[g_d_GameSettings.StadiumID] + 4, (f32*)&s1, (f32*)&s2, 0xC);
            }
        }
    }
    CTRLSetRotation((Control*)p, lbl_3_rodata_2664, p->_C0, lbl_3_rodata_2664);
    n = p->nodes;
    axis = lbl_3_rodata_25B0;
    dir = lbl_3_rodata_25BC;
    PSMTXRotAxisRad(m, &axis, lbl_3_rodata_2658[0] * p->_C0);
    PSMTXMultVec(m, lbl_3_rodata_24E8, &v);
    PSVECAdd(&v, &p->pos, &v);
    v.y += lbl_3_rodata_2668;
    n[7].pos = v;
    n[7].prev = n[7].pos;
    fn_3_D1F2C(&lbl_3_bss_A8A8, p->nodes, 8, &dir, p);
}
#endif

typedef struct { u8 b[4]; } B4;
extern B4 lbl_3_rodata_250C;
extern B4 lbl_3_rodata_2510;
extern const f32 lbl_3_rodata_2808;
// .text:0x000D3CDC size:0x278 mapped:0x80712D70
void fn_3_D3CDC(C2ObjMain* p) {
    RopeNode* c;
    Mtx m;
    Vec d;
    Vec v;
    Vec dir;
    Vec axis;
    B4 a = lbl_3_rodata_250C;
    B4 b = lbl_3_rodata_2510;
    u8* t;
    u32 i;
    if (g_GameLogic.gameStatus != 2) {
        if (p->_99 & 2) {
            p->_99 &= 0xFD;
        }
    } else if (!(p->_99 & 2)) {
        if (p->pos.x > lbl_3_rodata_2664) {
            t = a.b;
        } else {
            t = b.b;
        }
        for (i = 0; i < 4; i++) {
            CharActor* o = lbl_8036E548.active[t[i]];
            if (o != NULL) {
                PSVECSubtract(&p->pos, &o->pos, &d);
                if (PSVECMag(&d) <= lbl_3_rodata_2808) {
                    p->_99 |= 2;
                    if (fn_3_B7F70(10) < 4) {
                        p->_99 &= 0xFB;
                        p->_CC = 5;
                        p->_CB = p->_CA;
                        p->_CA = 2;
                        p->_AC.y = lbl_3_rodata_26A0;
                        fn_80025EEC(p->_8C, 0, 3);
                    }
                    break;
                }
            }
        }
    }
    c = p->nodes;
    axis = lbl_3_rodata_25B0;
    dir = lbl_3_rodata_25BC;
    PSMTXRotAxisRad(m, &axis, lbl_3_rodata_2658[0] * p->_C0);
    PSMTXMultVec(m, lbl_3_rodata_24E8, &v);
    PSVECAdd(&v, &p->pos, &v);
    v.y += lbl_3_rodata_2668;
    c[7].pos = v;
    c[7].prev = c[7].pos;
    fn_3_D1F2C(&lbl_3_bss_A8A8, p->nodes, 8, &dir, p);
}

// .text:0x000D3F54 size:0x82C mapped:0x80712FE8
// NONMATCHING 95% (with the four helpers pasted inline): written with calls instead; register numbering
// nmverify: fn_3_D4E00 fn_3_D4CA4 fn_3_D36B0 fn_3_D278C are inlined in the original
#if NONMATCHING
// Per-frame update of a chained stadium object (8-node chain). In game state 3 it is
// re-placed once (fn_3_D4E00); otherwise it is reset in state 0 and runs its behaviour
// p[0xCA]: 0 fn_3_D3CDC, 1 fn_3_D3880, 2 fn_3_D36B0, 3 fn_3_D30D0, 4 fn_3_D2A0C, 5 fn_3_D278C.
// The original inlines fn_3_D4E00, fn_3_D4CA4, fn_3_D36B0 and fn_3_D278C.
void fn_3_D3F54(C2ObjMain* p) {
    if (g_GameLogic.gameStatus == 3) {
        if (p->_CD == 0) {
            fn_3_D4E00(p);
        }
        return;
    }
    if (p->_CD != 0) {
        p->_CD = 0;
    }
    if (g_GameLogic.gameStatus == 0) {
        if (p->_CA != 0) {
            p->_CA = 1;
            fn_80025EEC(p->_8C, 0, 1);
        }
        fn_3_D4CA4(p);
        p->_C8 = 1;
    }
    if (g_GameLogic.gameStatus == 2) {
        ((BF90_c2*)p)->f = 1;
    }
    switch (p->_CA) {
    case 0:
        fn_3_D3CDC(p);
        break;
    case 1:
        fn_3_D3880(p);
        break;
    case 2:
        fn_3_D36B0(p);
        break;
    case 3:
        fn_3_D30D0(p);
        break;
    case 4:
        fn_3_D2A0C(p);
        break;
    case 5:
        fn_3_D278C(p);
        break;
    }
}
#endif

// .text:0x000D4780 size:0x524 mapped:0x80713814
// NONMATCHING 93%: the folded i/7 constants come from a pooled base register in our build; saved-register numbering
#pragma pool_data off // each float constant is its own .rodata symbol in the original
#if NONMATCHING
// Lays the 8-node chain from its anchor (lbl_3_rodata_24D0/24DC by the spot's side flag)
// to p's hook, sagging by 7.125 - len/2 along a half sine, and clears its motion.
void fn_3_D4780(C2ObjMain* p) {
    Vec anchor;
    Vec top;
    Vec d;
    Mtx m;
    GameControl ctrl;
    T52* t;
    f32 len;
    f32 sag;
    u32 i;
    top = lbl_3_rodata_24E8[0];
    memcpy(&top, &lbl_3_rodata_24E8[0], sizeof(Vec));
    if (((u8*)&lbl_3_data_182C8[p->idx])[0x30] == 0) {
        memcpy(&anchor, &lbl_3_rodata_24DC, sizeof(Vec));
    } else {
        memcpy(&anchor, &lbl_3_rodata_24D0, sizeof(Vec));
    }
    anchor.y = lbl_3_rodata_26A0;
    top.y = lbl_3_rodata_2848;
    ctrl.base.type = 0;
    if (p->_CA == 0) {
        t = &lbl_3_data_182C8[p->idx];
        CTRLSetRotation(&ctrl.base, t->e, -t->f, t->g);
    } else {
        t = &lbl_3_data_182C8[p->idx];
        CTRLSetRotation(&ctrl.base, t->b, -t->c, t->d);
    }
    CTRLBuildMatrix(&ctrl.base, m);
    PSMTXMultVec(m, &top, &top);
    top.y = top.y * lbl_3_rodata_2678;
    top.x += p->pos.x;
    top.y += p->pos.y;
    top.z += p->pos.z;
    PSVECSubtract(&top, &anchor, &d);
    len = PSVECMag(&d);
    for (i = 0; i < 8; i++) {
        f32 k = (f32)i / 7.0f;
        p->nodes[i].pos.x = k * d.x + anchor.x;
        p->nodes[i].pos.y = k * d.y + anchor.y;
        p->nodes[i].pos.z = k * d.z + anchor.z;
    }
    sag = lbl_3_rodata_2868 - len * lbl_3_rodata_26A0;
    for (i = 0; i < 8; i++) {
        p->nodes[i].pos.y -= sag * (f32)sin(lbl_3_rodata_27F0 * ((f32)i / lbl_3_rodata_2864));
        if (p->nodes[i].pos.y < p->nodes[i].radius) {
            p->nodes[i].pos.y = p->nodes[i].radius;
        }
    }
    for (i = 0; i < 8; i++) {
        memcpy(&p->nodes[i].prev, &p->nodes[i].pos, sizeof(Vec));
        memset(&p->nodes[i].vel, 0, sizeof(Vec));
        memset(&p->nodes[i].force, 0, sizeof(Vec));
    }
}
#endif
#pragma pool_data reset

// .text:0x000D4CA4 size:0x15C mapped:0x80713D38
void fn_3_D4CA4(C2ObjMain* p) {
    T52* t;
    f32* yb;
    f32* zb;
    p->ctrl.base.type = 0;
    CTRLSetScale((Control*)p, lbl_3_rodata_26C8, lbl_3_rodata_26C8, lbl_3_rodata_26C8);
    if (p->_CA == 0) {
        yb = (f32*)lbl_3_data_182C8 + 8;
        t = lbl_3_data_182C8 + p->idx;
        CTRLSetRotation((Control*)p, t->e, -yb[p->idx * 13], t->g);
        p->_C0 = -yb[p->idx * 13];
    } else {
        yb = (f32*)lbl_3_data_182C8 + 5;
        t = lbl_3_data_182C8 + p->idx;
        CTRLSetRotation((Control*)p, t->b, -yb[p->idx * 13], t->d);
        p->_C0 = -yb[p->idx * 13];
    }
    yb = (f32*)lbl_3_data_182C8 + 1;
    zb = (f32*)lbl_3_data_182C8 + 2;
    CTRLSetTranslation((Control*)p, ((f32*)lbl_3_data_182C8)[p->idx * 13], yb[p->idx * 13], zb[p->idx * 13]);
    p->pos.x = ((f32*)lbl_3_data_182C8)[p->idx * 13];
    p->pos.y = -yb[p->idx * 13];
    p->pos.z = zb[p->idx * 13];
    fn_3_D4780(p);
}

// .text:0x000D4E00 size:0x21C mapped:0x80713E94
void fn_3_D4E00(C2ObjMain* p) {
    T52* t;
    f32* yb;
    f32* zb;
    p->_CA = rand() % 10;
    if (p->_CA < 3) {
        p->_CA = 0;
        fn_80025EEC(p->_8C, 0, 2);
    } else {
        p->_CA = 1;
        fn_80025EEC(p->_8C, 0, 1);
    }
    p->_CB = p->_CA;
    ((BF90_c2*)p)->f = 1;
    p->ctrl.base.type = 0;
    CTRLSetScale((Control*)p, lbl_3_rodata_26C8, lbl_3_rodata_26C8, lbl_3_rodata_26C8);
    if (p->_CA == 0) {
        yb = (f32*)lbl_3_data_182C8 + 8;
        t = lbl_3_data_182C8 + p->idx;
        CTRLSetRotation((Control*)p, t->e, -yb[p->idx * 13], t->g);
        p->_C0 = -yb[p->idx * 13];
    } else {
        yb = (f32*)lbl_3_data_182C8 + 5;
        t = lbl_3_data_182C8 + p->idx;
        CTRLSetRotation((Control*)p, t->b, -yb[p->idx * 13], t->d);
        p->_C0 = -yb[p->idx * 13];
    }
    yb = (f32*)lbl_3_data_182C8 + 1;
    zb = (f32*)lbl_3_data_182C8 + 2;
    CTRLSetTranslation((Control*)p, ((f32*)lbl_3_data_182C8)[p->idx * 13], yb[p->idx * 13], zb[p->idx * 13]);
    p->pos.x = ((f32*)lbl_3_data_182C8)[p->idx * 13];
    p->pos.y = -yb[p->idx * 13];
    p->pos.z = zb[p->idx * 13];
    fn_3_D4780(p);
    p->_99 = 0;
    p->_C8 = 1;
    if (lbl_3_data_182C4 != -1) {
        fn_3_8B890(lbl_3_data_182C4);
        lbl_3_data_182C4 = -1;
    }
    p->_CD = 1;
}

// .text:0x000D501C size:0x100 mapped:0x807140B0
void fn_3_D501C(RopeNode* p) {
    RopeNode* q;
    f32 one;
    u32 i;
    if (p != NULL) {
        memset(p, 0, sizeof(RopeNode));
        one = lbl_3_rodata_2698;
        q = p;
        for (i = 0; i < 8; i++, q++) {
            if (i == 7) {
                q->mass = lbl_3_data_188E0;
                q->radius = 0.504375f;
                q->pinned = 1;
            } else {
                if (i == 0) {
                    q->pinned = 1;
                }
                q->mass = lbl_3_data_188E0;
                q->radius = 0.504375f;
            }
            q->invMass = one / q->mass;
            memset(&q->pos, 0, sizeof(Vec) * 2); // pos and prev
            memset(&q->vel, 0, sizeof(Vec));
            memset(&q->force, 0, sizeof(Vec));
        }
    }
}

// .text:0x000D511C size:0x2A4 mapped:0x807141B0
// Resets an 8-node chain hanging between two pinned ends (nodes 0 and 7).
static inline void D511C_initChain(RopeNode* r) {
    f32 one;
    u32 i;
    if (r != NULL) {
        memset(r, 0, sizeof(RopeNode));
        one = lbl_3_rodata_2698;
        for (i = 0; i < 8; i++, r++) {
            if (i == 7) {
                r->mass = lbl_3_data_188E0;
                r->radius = lbl_3_rodata_2694;
                r->pinned = 1;
            } else {
                if (i == 0) {
                    r->pinned = 1;
                }
                r->mass = lbl_3_data_188E0;
                r->radius = lbl_3_rodata_2694;
            }
            r->invMass = one / r->mass;
            memset(&r->pos, 0, sizeof(Vec) * 2);
            memset(&r->vel, 0, sizeof(Vec));
            memset(&r->force, 0, sizeof(Vec));
        }
    }
}

static inline void D511C_initCfg(CC438Cfg* g) {
    f32 one;
    g->a = lbl_3_rodata_269C;
    g->b = lbl_3_rodata_26A0;
    g->c = lbl_3_rodata_26A4;
    g->d = lbl_3_rodata_26A8;
    g->e = lbl_3_rodata_26AC;
    g->f = lbl_3_rodata_26B0;
    g->n = 8;
    one = lbl_3_rodata_2698;
    g->h = one / (f32)g->n / lbl_3_rodata_26B4;
    g->hh = g->h * g->h;
    g->inv = one / (lbl_3_rodata_26B8 * g->h);
}

// NONMATCHING ~90%: same code, but register choice/scheduling around the cfg base pointer differs
#if NONMATCHING
void fn_3_D511C(void) {
    u8* b = lbl_3_bss_A018;
    memset(C2_BSS(CC438Cfg, lbl_3_bss_A8A8, b, 0x890), 0, sizeof(CC438Cfg));
    D511C_initCfg(C2_BSS(CC438Cfg, lbl_3_bss_A8A8, b, 0x890));
    D511C_initChain(C2_BSS(RopeNode, lbl_3_bss_A8D0[12], b, 0xBB8));
    D511C_initChain(C2_BSS(RopeNode, lbl_3_bss_A8D0[4], b, 0x9B8));
}
#endif

// .text:0x000D53C0 size:0x84 mapped:0x80714454
s32 fn_3_D53C0(u8 id) {
    u32 n = (u32)lbl_3_common_bss_350E4.count;
    C2SortEnt* e = (C2SortEnt*)lbl_3_common_bss_350E4.sort + n;
    for (; n != 0; e--, n--) {
        if (id == e[-1].idx) {
            return n - 1;
        }
    }
    OSPanic(lbl_3_rodata_286C, 0x863, lbl_3_rodata_2878);
    return 0;
}

// .text:0x000D5444 size:0x2C mapped:0x807144D8
s32 fn_3_D5444(u32* a, u32* b) {
    if (*a < *b) {
        return -1;
    }
    return *a > *b;
}

// .text:0x000D5470 size:0x24 mapped:0x80714504
s32 fn_3_D5470(f32* a, f32* b) {
    f32 x = *a;
    f32 y = *b;
    if (x < y) {
        return -1;
    }
    return x > y;
}

// .text:0x000D5494 size:0x158 mapped:0x80714528
typedef struct { f32 f0; s32 f4; } D5494E;
#ifdef PORT_LP64
typedef union { struct { u8 pad[STADIUM_OBJ_PAD(0x90)]; u8 rest : 7; u8 f : 1; u8 pad91[0x9D - 0x91]; u8 f9D; }; u8 _size[STADIUM_OBJ_SIZE]; } D5494C;
#else
typedef struct { u8 pad[0x90]; u8 f : 1; u8 pad91[0x9D - 0x91]; u8 f9D; u8 pad2[0xE8 - 0x9E]; } D5494C;
#endif
#ifdef PORT_LP64
typedef union { struct { D5494C* arr; }; struct { u8 _at_p14[0x28]; D5494E* p14; }; struct { u8 _at_count[0x60]; u32 count; }; } D5494B;
#else
typedef struct { D5494C* arr; u8 pad0[0x14 - 4]; D5494E* p14; u8 pad1[0x30 - 0x18]; u32 count; } D5494B;
#endif
extern f32 lbl_3_rodata_26B8;
extern f32 lbl_3_rodata_27E0;
extern f32 lbl_3_rodata_289C;
extern f32 lbl_3_rodata_28A0;
void fn_3_D5494(f32 (*m)[4]) {
    Vec v;
    D5494B* g;
    D5494C* c;
    s32 off;
    D5494E* e;
    u32 i;
    f32 x, hi;
    u8 t;
    memcpy(&v, &g_Ball.AtBat_Contact_BallPos, sizeof(Vec));
    PSMTXMultVec(m, &v, &v);
    i = 0;
    g = (D5494B*)&lbl_3_common_bss_350E4;
    off = 0;
    for (; i < g->count; off += 8, i++) {
        e = (D5494E*)((u8*)g->p14 + off);
        c = &g->arr[e->f4];
        if (c->f) {
            t = c->f9D;
            if (t == 0 || (u8)(t - 4) <= 1 || (t > 7 && t < 0xB)) {
                e->f0 = lbl_3_rodata_2698;
            } else {
                x = e->f0;
                hi = lbl_3_rodata_26B8 + v.z;
                if (x < hi) {
                    e->f0 = lbl_3_rodata_2698;
                } else if (x > lbl_3_rodata_27E0 + v.z) {
                    e->f0 = lbl_3_rodata_289C;
                } else {
                    { f32 d = x - hi; e->f0 = lbl_3_rodata_27A8 - lbl_3_rodata_26C8 * (d * lbl_3_rodata_28A0); }
                }
            }
        }
    }
}

// .text:0x000D55EC size:0x580 mapped:0x80714680
// The extra fields of the stadium object list (lbl_3_common_bss_350E4) used by the sort.
#ifdef PORT_LP64
typedef union C2SortMgr { struct { PiranhaPlant* objs; }; struct { u8 _at_sorted[0x28]; C2SortEnt* sorted; }; struct { u8 _at_count[0x60]; s32 count; }; struct { u8 _at_sbd[0xB8]; u8 sortByDepth; }; } C2SortMgr;
#else
typedef struct C2SortMgr {
    /*0x00*/ PiranhaPlant* objs;
    /*0x04*/ u8 _04[0x14 - 0x04];
    /*0x14*/ C2SortEnt* sorted;
    /*0x18*/ u8 _18[0x30 - 0x18];
    /*0x30*/ s32 count;
    /*0x34*/ u8 _34[0x6C - 0x34];
    /*0x6C*/ u8 sortByDepth;
} C2SortMgr;
#endif


extern void* fn_800ACF34(s32 align, s32 size);
extern void fn_800ACF14(void* block);
extern void fn_800C07BC(void* base, void* tmp, u32 count, u32 size, s32 (*compare)(const void*, const void*));

static inline s32 D55EC_findSorted(s32 idx) {
    C2SortMgr* g = (C2SortMgr*)&lbl_3_common_bss_350E4;
    s32 n;
    for (n = g->count; n != 0; n--) {
        if (idx == g->sorted[n - 1].idx) {
            return n - 1;
        }
    }
    OSPanic("sta_c2.c", 0x863, lbl_3_rodata_2878);
    return 0;
}

// NONMATCHING 90%: the index search loops (inlined assert helper) compile to a different loop shape; register numbering
#if NONMATCHING
// Builds the stadium draw order in out[] (back to front by view depth; hidden objects
// first at -512), keeps each of the lbl_3_bss_A026.. groups (obj, its +0xA0->D2 and
// +0xA4->C0 partners) in index order, then turns depth into a fade alpha behind the ball.
void fn_3_D55EC(MtxPtr view, C2SortEnt* out) {
    C2SortMgr* g = (C2SortMgr*)&lbl_3_common_bss_350E4;
    PiranhaPlant* obj;
    Vec v;
    Vec ball;
    s32 pos[3];
    C2SortEnt save[3];
    void* tmp;
    s32 i;
    s32 k;
    s32 n;
    u32 j;
    C2ObjFx* o;
    C2SortEnt* e;
    u8 type;
    f32 near;
    if (g->sortByDepth != 0) {
        n = 0;
        i = g->count - 1;
        obj = &g->objs[i];
        do {
            if (!obj->visible) {
                out[n].z = lbl_3_rodata_26CC;
                out[n].idx = i;
                n++;
            }
            obj--;
        } while (i-- != 0);
        k = g->count;
        i = g->count - 1;
        obj = &((C2SortMgr*)&lbl_3_common_bss_350E4)->objs[i];
        do {
            if (obj->visible) {
                if (obj->bit5) {
                    CTRLGetTranslation(&obj->ctrl.base, &v.x, &v.y, &v.z);
                    PSMTXMultVec(view, &v, &v);
                    k--;
                    out[k].z = v.z;
                    out[k].idx = i;
                } else {
                    out[n].z = lbl_3_rodata_26CC;
                    out[n].idx = i;
                    n++;
                }
            }
            obj--;
        } while (i-- != 0);
        tmp = fn_800ACF34(0x20, (g->count - k) * 8);
        fn_800C07BC(out + k, tmp, g->count - k, 8, (s32 (*)(const void*, const void*))fn_3_D5470);
        fn_800ACF14(tmp);
        tmp = fn_800ACF34(0x20, (g->count - k) * 8);
        for (i = 0; i < lbl_3_bss_A027; i++) {
            o = (C2ObjFx*)&((C2SortMgr*)&lbl_3_common_bss_350E4)->objs[lbl_3_bss_A026 + i];
            if (o->target->_D1 != 0) {
                pos[0] = D55EC_findSorted(o->_AC);
                pos[1] = D55EC_findSorted(o->target->_D2);
                pos[2] = D55EC_findSorted(o->marker->_C0);
                save[0] = out[pos[0]];
                save[1] = out[pos[1]];
                save[2] = out[pos[2]];
                fn_800C07BC(pos, tmp, 3, 4, (s32 (*)(const void*, const void*))fn_3_D5444);
                out[pos[0]] = save[0];
                out[pos[1]] = save[1];
                out[pos[2]] = save[2];
            }
        }
        fn_800ACF14(tmp);
        memcpy(&ball, &g_Ball, sizeof(Vec));
        PSMTXMultVec(view, &ball, &ball);
        for (j = 0; j < g->count; j++) {
            e = &((C2SortMgr*)&lbl_3_common_bss_350E4)->sorted[j];
            obj = &g->objs[e->idx];
            if (obj->visible) {
                type = obj->isDummy;
                if (type == 0 || (u8)(type - 4) <= 1 || (type > 7 && type < 11)) {
                    e->z = lbl_3_rodata_2698;
                } else {
                    near = lbl_3_rodata_26B8 + ball.z;
                    if (e->z < near) {
                        e->z = lbl_3_rodata_2698;
                    } else if (e->z > lbl_3_rodata_27E0 + ball.z) {
                        e->z = lbl_3_rodata_289C;
                    } else {
                        e->z = lbl_3_rodata_27A8 - lbl_3_rodata_26C8 * ((e->z - near) * lbl_3_rodata_28A0);
                    }
                }
            }
        }
    } else {
        obj = g->objs;
        for (i = 0; i < g->count; i++) {
            CTRLGetTranslation(&obj->ctrl.base, &v.x, &v.y, &v.z);
            out[i].z = lbl_3_rodata_2698;
            out[i].idx = i;
        }
    }
}
#endif

// .text:0x000D5B6C size:0x120 mapped:0x80714C00
// TODO(port): pad-offset view of the 0xE8-byte stadium object (GameCube layout)
#ifdef PORT_LP64
typedef union { struct { u8 pad[0x80]; void* f78; }; u8 _size[STADIUM_OBJ_SIZE]; } D5B6CCtl;
#else
typedef struct { u8 pad[0x78]; void* f78; u8 pad2[0xE8 - 0x7C]; } D5B6CCtl;
#endif
#ifdef PORT_LP64
typedef union { struct { D5B6CCtl* arr; }; struct { u8 _at_p3C[0x78]; u32* p3C; }; struct { u8 _at_p40[0x80]; u16* p40; }; struct { u8 _at_p44[0x88]; u32* p44; }; struct { u8 _at_p48[0x90]; u8* p48; }; } D5B6CBss;
#else
typedef struct { D5B6CCtl* arr; u8 pad0[0x3C - 4]; u32* p3C; u16* p40; u32* p44; u8* p48; } D5B6CBss;
#endif
typedef struct { u32 w[17]; } D5B6CCpy;
extern void fn_3_B8414(void*, void*);
extern void fn_3_B8464(void*, void*);
void fn_3_D5B6C(s32* a) {
    D5B6CBss* g = (D5B6CBss*)&lbl_3_common_bss_350E4;
    D5B6CCpy sp34;
    Mtx sp8;
    D5B6CCtl* c;
    u16 v;
    v = g->p40[*a - 1] + g->p3C[*a - 1];
    g->p40[*a] = v;
    g->p44[v] = lbl_3_bss_A020;
    g->p3C[*a] += 1;
    c = &g->arr[lbl_3_bss_A020];
    sp34 = *(D5B6CCpy*)c;
    CTRLBuildMatrix((Control*)&sp34, sp8);
    fn_3_B8464(sp8, c->f78);
    fn_3_B8414(((D5B6CBss*)&lbl_3_common_bss_350E4)->p48 + *a * 0x18, ((D5B6CBss*)&lbl_3_common_bss_350E4)->p48 + (*a * 2 + 1) * 0xC);
    *a += 1;
}

// .text:0x000D5C8C size:0x1F4 mapped:0x80714D20
typedef struct { u8 pad[0xC]; u8 fC; u8 padD; u8 fE; u8 padF; } D5C8CEnt;
// TODO(port): pad-offset view of the 0xE8-byte stadium object (GameCube layout)
#ifdef PORT_LP64
typedef union { struct { u8 pad[0x80]; void* f78; }; u8 _size[STADIUM_OBJ_SIZE]; } D5C8CCtl;
#else
typedef struct { u8 pad[0x78]; void* f78; u8 pad2[0xE8 - 0x7C]; } D5C8CCtl;
#endif
#ifdef PORT_LP64
typedef union { struct { D5C8CCtl* arr; }; struct { u8 _at_p3C[0x78]; u32* p3C; }; struct { u8 _at_p40[0x80]; u16* p40; }; struct { u8 _at_p44[0x88]; u32* p44; }; struct { u8 _at_p48[0x90]; u8* p48; }; } D5C8CBss;
#else
typedef struct { D5C8CCtl* arr; u8 pad0[0x3C - 4]; u32* p3C; u16* p40; u32* p44; u8* p48; } D5C8CBss;
#endif
extern const f32 lbl_3_rodata_2758;
extern void fn_3_B8574(void);
void fn_3_D5C8C(s32* a) {
    Mtx m2;
    Mtx m;
    D5B6CCpy cpy;
    D5C8CBss* g;
    D5C8CEnt* e;
    s32 off;
    s32 k;
    s32 j;
    u32 v;
    D5C8CCtl* c;
    s32 idx;
    PSMTXIdentity(m);
    PSMTXScale(m, lbl_3_rodata_26B8, lbl_3_rodata_26B8, lbl_3_rodata_26B8);
    g = (D5C8CBss*)&lbl_3_common_bss_350E4;
    for (k = 0; k < 5; k++) {
        v = (u16)(g->p40[*a - 1] + g->p3C[*a - 1]);
        g->p40[*a] = v;
        ((void (*)(void))fn_3_B8574)();
        e = (D5C8CEnt*)lbl_3_data_18730;
        off = v * 4;
        for (j = 0; j < lbl_3_bss_A023; e++, j++) {
            if (k == e->fE && e->fC != 0xD) {
                idx = j + lbl_3_bss_A022;
                if ((((u8*)((D5C8CBss*)&lbl_3_common_bss_350E4)->arr)[idx * STADIUM_OBJ_SIZE + STADIUM_OBJ_PAD(0x90)] >> 6) & 1) {
                    *(s32*)((u8*)g->p44 + off) = idx;
                    g->p3C[*a] += 1;
                    c = &((D5C8CBss*)&lbl_3_common_bss_350E4)->arr[idx];
                    off += 4;
                    cpy = *(D5B6CCpy*)c;
                    CTRLBuildMatrix((Control*)&cpy, m2);
                    PSMTXConcat(m2, m, m2);
                    fn_3_B8464(m2, c->f78);
                    m2[1][3] = m2[1][3] * lbl_3_rodata_2758;
                    fn_3_B8464(m2, c->f78);
                }
            }
        }
        if (g->p3C[*a] != 0) {
            fn_3_B8414(g->p48 + *a * 0x18, g->p48 + (*a * 2 + 1) * 0xC);
            *a += 1;
        }
    }
}

extern D5E80Ent lbl_3_data_1849C[];
extern const f32 lbl_3_rodata_2664;
void fn_3_D5E80(s32* a) {
    Mtx m2;
    D5B6CCpy cpy;
    D5C8CBss* g;
    D5E80Ent* e;
    s32 off;
    u32 v;
    D5C8CCtl* c;
    s32 k;
    s32 j;
    s32 idx;
    g = (D5C8CBss*)&lbl_3_common_bss_350E4;
    for (k = 0; k < 5; k++) {
        v = (u16)(g->p40[*a - 1] + g->p3C[*a - 1]);
        g->p40[*a] = v;
        ((void (*)(void))fn_3_B8574)();
        e = lbl_3_data_1849C;
        off = v * 4;
        for (j = 0; j < lbl_3_bss_A025; e++, j++) {
            if (k == e->fE && e->fC != 0xD) {
                idx = j + lbl_3_bss_A024;
                if ((((u8*)((D5C8CBss*)&lbl_3_common_bss_350E4)->arr)[idx * STADIUM_OBJ_SIZE + STADIUM_OBJ_PAD(0x90)] >> 6) & 1) {
                    *(s32*)((u8*)g->p44 + off) = idx;
                    g->p3C[*a] += 1;
                    c = &((D5C8CBss*)&lbl_3_common_bss_350E4)->arr[idx];
                    off += 4;
                    cpy = *(D5B6CCpy*)c;
                    CTRLBuildMatrix((Control*)&cpy, m2);
                    fn_3_B8464(m2, c->f78);
                    CTRLSetTranslation((Control*)&cpy, *(f32*)((u8*)c + STADIUM_OBJ_PAD(0xAC)) + lbl_3_data_1849C[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].x, lbl_3_rodata_2664, *(f32*)((u8*)c + STADIUM_OBJ_PAD(0xAC)) + lbl_3_data_1849C[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].z);
                    CTRLBuildMatrix((Control*)&cpy, m2);
                    fn_3_B8464(m2, c->f78);
                    CTRLSetTranslation((Control*)&cpy, lbl_3_data_1849C[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].x - *(f32*)((u8*)c + STADIUM_OBJ_PAD(0xAC)), lbl_3_rodata_2664, lbl_3_data_1849C[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].z - *(f32*)((u8*)c + STADIUM_OBJ_PAD(0xAC)));
                    CTRLBuildMatrix((Control*)&cpy, m2);
                    fn_3_B8464(m2, c->f78);
                }
            }
        }
        if (g->p3C[*a] != 0) {
            fn_3_B8414(g->p48 + *a * 0x18, g->p48 + (*a * 2 + 1) * 0xC);
            *a += 1;
        }
    }
}

// .text:0x000D60C0 size:0x230 mapped:0x80715154
extern const f64 lbl_3_rodata_27D0;
void fn_3_D60C0(s32* a) {
    Mtx m2;
    D5B6CCpy cpy;
    D5C8CBss* g;
    T34* e;
    s32 off;
    u32 v;
    D5C8CCtl* c;
    s32 k;
    s32 j;
    s32 idx;
    g = (D5C8CBss*)&lbl_3_common_bss_350E4;
    for (k = 0; k < 3; k++) {
        v = (u16)(g->p40[*a - 1] + g->p3C[*a - 1]);
        g->p40[*a] = v;
        ((void (*)(void))fn_3_B8574)();
        e = lbl_3_data_18364;
        off = v * 4;
        for (j = 0; j < lbl_3_bss_A02B; e++, j++) {
            if (k == ((u8*)e)[0xE] && ((u8*)e)[0xC] != 0xD) {
                if ((((u8*)((D5C8CBss*)&lbl_3_common_bss_350E4)->arr)[(idx = j + lbl_3_bss_A02A) * STADIUM_OBJ_SIZE + STADIUM_OBJ_PAD(0x90)] >> 6) & 1) {
                    *(s32*)((u8*)g->p44 + off) = idx;
                    g->p3C[*a] += 1;
                    c = &((D5C8CBss*)&lbl_3_common_bss_350E4)->arr[idx];
                    off += 4;
                    cpy = *(D5B6CCpy*)c;
                    CTRLSetTranslation((Control*)&cpy, lbl_3_data_18364[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].x, -(lbl_3_data_18364[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].y - lbl_3_rodata_27D0), lbl_3_data_18364[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].z);
                    CTRLBuildMatrix((Control*)&cpy, m2);
                    fn_3_B8464(m2, c->f78);
                    CTRLSetTranslation((Control*)&cpy, lbl_3_data_18364[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].x, -(lbl_3_rodata_27D0 + lbl_3_data_18364[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].y), lbl_3_data_18364[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].z);
                    CTRLBuildMatrix((Control*)&cpy, m2);
                    fn_3_B8464(m2, c->f78);
                }
            }
        }
        if (g->p3C[*a] != 0) {
            fn_3_B8414(g->p48 + *a * 0x18, g->p48 + (*a * 2 + 1) * 0xC);
            *a += 1;
        }
    }
}

// .text:0x000D62F0 size:0x224 mapped:0x80715384
extern const f32 lbl_3_rodata_28A4;
#pragma dont_inline off
// Adds one draw group (with its shadow at +-14.25) per object lbl_3_bss_A02C..+A02D.
static inline void D62F0_addGroups(s32* a) {
    Mtx m2;
    D5B6CCpy cpy;
    D5C8CBss* g;
    D5C8CCtl* c;
    u32 v;
    s32 j;
    s32 idx;
    g = (D5C8CBss*)&lbl_3_common_bss_350E4;
    for (j = 0; j < lbl_3_bss_A02D; j++) {
        v = (u16)(g->p40[*a - 1] + g->p3C[*a - 1]);
        g->p40[*a] = v;
        idx = lbl_3_bss_A02C + j;
        g->p44[v] = idx;
        g->p3C[*a] += 1;
        c = &g->arr[idx];
        cpy = *(D5B6CCpy*)c;
        CTRLBuildMatrix((Control*)&cpy, m2);
        fn_3_B8464(m2, c->f78);
        CTRLSetTranslation((Control*)&cpy, lbl_3_rodata_2800 + lbl_3_data_182C8[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].x, -(lbl_3_rodata_28A4 + lbl_3_data_182C8[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].y), lbl_3_rodata_2800 + lbl_3_data_182C8[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].z);
        CTRLBuildMatrix((Control*)&cpy, m2);
        fn_3_B8464(m2, c->f78);
        CTRLSetTranslation((Control*)&cpy, lbl_3_data_182C8[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].x - lbl_3_rodata_2800, -(lbl_3_rodata_28A4 + lbl_3_data_182C8[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].y), lbl_3_data_182C8[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].z - lbl_3_rodata_2800);
        CTRLBuildMatrix((Control*)&cpy, m2);
        fn_3_B8464(m2, c->f78);
        if (g->p3C[*a] != 0) {
            fn_3_B8414(g->p48 + *a * 0x18, g->p48 + (*a * 2 + 1) * 0xC);
            *a += 1;
        }
    }
}
#pragma dont_inline on

void fn_3_D62F0(s32* a) {
    Mtx m2;
    D5B6CCpy cpy;
    D5C8CBss* g;
    D5C8CCtl* c;
    u32 v;
    s32 j;
    s32 idx;
    g = (D5C8CBss*)&lbl_3_common_bss_350E4;
    for (j = 0; j < lbl_3_bss_A02D; j++) {
        v = (u16)(g->p40[*a - 1] + g->p3C[*a - 1]);
        g->p40[*a] = v;
        idx = lbl_3_bss_A02C + j;
        g->p44[v] = idx;
        g->p3C[*a] += 1;
        c = &g->arr[idx];
        cpy = *(D5B6CCpy*)c;
        CTRLBuildMatrix((Control*)&cpy, m2);
        fn_3_B8464(m2, c->f78);
        CTRLSetTranslation((Control*)&cpy, lbl_3_rodata_2800 + lbl_3_data_182C8[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].x, -(lbl_3_rodata_28A4 + lbl_3_data_182C8[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].y), lbl_3_rodata_2800 + lbl_3_data_182C8[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].z);
        CTRLBuildMatrix((Control*)&cpy, m2);
        fn_3_B8464(m2, c->f78);
        CTRLSetTranslation((Control*)&cpy, lbl_3_data_182C8[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].x - lbl_3_rodata_2800, -(lbl_3_rodata_28A4 + lbl_3_data_182C8[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].y), lbl_3_data_182C8[((u8*)c)[STADIUM_OBJ_PAD(0x9C)]].z - lbl_3_rodata_2800);
        CTRLBuildMatrix((Control*)&cpy, m2);
        fn_3_B8464(m2, c->f78);
        if (g->p3C[*a] != 0) {
            fn_3_B8414(g->p48 + *a * 0x18, g->p48 + (*a * 2 + 1) * 0xC);
            *a += 1;
        }
    }
}


// .text:0x000D6514 size:0x2B8 mapped:0x807155A8
#ifdef PORT_LP64
typedef union { struct { D5C8CCtl* arr; }; struct { u8 _at_count[0x60]; u32 count; }; struct { u8 _at_p3C[0x78]; u32* p3C; }; struct { u8 _at_p40[0x80]; u16* p40; }; struct { u8 _at_p44[0x88]; u32* p44; }; struct { u8 _at_p48[0x90]; u8* p48; }; struct { u8 _at_f64[0xB0]; s16 f64; }; } D6514Bss;
#else
typedef struct { D5C8CCtl* arr; u8 pad0[0x30 - 4]; u32 count; u8 pad1[0x3C - 0x34]; u32* p3C; u16* p40; u32* p44; u8* p48; u8 pad2[0x64 - 0x4C]; s16 f64; } D6514Bss;
#endif
extern void* _OSAllocFromHeap(s32, u32);
// NONMATCHING 95%: buffer size sum order and saved-register numbering (r25 vs r26) differ
#if NONMATCHING
void fn_3_D6514(void) {
    D6514Bss* g = (D6514Bss*)&lbl_3_common_bss_350E4;
    s32 grp;
    u32 size = g->count * 0x18 + g->count * 4 + (g->count * 4 + g->count * 2);
    if (g->p48 == NULL) {
        g->p48 = _OSAllocFromHeap(4, size);
        ((D6514Bss*)&lbl_3_common_bss_350E4)->p3C = (u32*)(g->p48 + g->count * 0x18);
        ((D6514Bss*)&lbl_3_common_bss_350E4)->p44 = ((D6514Bss*)&lbl_3_common_bss_350E4)->p3C + g->count;
        ((D6514Bss*)&lbl_3_common_bss_350E4)->p40 = (u16*)(((D6514Bss*)&lbl_3_common_bss_350E4)->p44 + g->count);
    }
    memset(g->p48, 0, size);
    grp = 0;
    D62F0_addGroups(&grp);
    fn_3_D5C8C(&grp);
    ((D6514Bss*)&lbl_3_common_bss_350E4)->f64 = grp;
}
#endif

// .text:0x000D67CC size:0x2244 mapped:0x80715860
// NONMATCHING ~85% (with the helpers pasted inline; the list-counting loops are unrolled in the original)
// nmverify: fn_3_D4E00 fn_3_D511C fn_3_D6514 fn_3_CE8E4 are inlined in the original
#if NONMATCHING
extern void fn_3_B939C(void);
extern void fn_3_B9D68(u8* kinds, s32 count, u8* table, s32* outIdx);

// Stadium objects of this file, in lbl_3_data_182C0 (lists end at type 0xD):
//   +0x008 T52 mains[2]     (chained creatures)        +0x0A4 T34 spinners[5]
//   +0x310 C2Prop props[10]                            +0x470 T16 posts[10]
//   +0x520 T16 lamps[10]                               +0x604 file kinds (26)
// lbl_3_bss_A018: +0x1C/+0x3B4/+0x74C anim players (posts, lamps, mains; 0x5C each),
// +0x9B8/+0xBB8 the two 8-node chains, +0x890 their config, +0xDB8 files[0].
//
// Stadium setup (mode 7 uses fn_3_CCC24 instead): loads the actor models and their
// animations, then fills the object list: the mains with their 3 companions each,
// 14 chain links, the spinners with their shadow/marker objects (types 4 and 5),
// the props, posts and lamps; then builds the shadow draw groups and the smoke plumes.
// The original inlines fn_3_D4E00, fn_3_D511C, fn_3_D6514 and fn_3_CE8E4.
void fn_3_D67CC(void** files) {
    StadiumObjList* g = (StadiumObjList*)&lbl_3_common_bss_350E4;
    u32* idx;
    T52* mains = lbl_3_data_182C8;
    T34* spin = lbl_3_data_18364;
    C2Prop* prop = lbl_3_data_185D0;
    T16* post = lbl_3_data_18730;
    T16* lamp = &lbl_3_data_18730[11];
    C2ObjAny* o;
    C2Obj* m;
    RopeNode* chain;
    GameBone* model;
    Quaternion q;
    Vec axis;
    Vec off;
    Mtx mtx;
    u8 done;
    u8 sh;
    s32 count;
    u32 nMain, nSpin, nProp, nPost, nLamp, nObjs, nComp;
    u32 i;
    s32 k;
    s32 j;
    s32 compBase, chainIdx, spinBase, markerIdx, ringIdx, propBase, postBase, lampBase;
    s32 phase;
    ShapeAnimPlayer* player;

    g->draw = fn_3_B939C;
    done = 0;
    count = 0;
    idx = _OSAllocFromHeap(4, 0x68);
    g->fileIdx = idx;
#ifdef TARGET_PC
    fn_3_B9D68(sStaC2FileKinds, 26, (u8*)files, (s32*)idx);
#else
    fn_3_B9D68((u8*)&lbl_3_data_182C0 + 0x604, 26, (u8*)files, (s32*)idx);
#endif
    lbl_3_bss_ADD0[0] = STADIUM_FILE(files, 0);
    lbl_3_data_182C0 = -1;
    lbl_3_data_182C4 = -1;
    if (g_d_GameSettings.GameModeSelected == 7) {
        fn_3_CCC24(files, idx);
        return;
    }

    // count the entries of each list
    for (nMain = 0; nMain < 2 && mains[nMain].type != 0xD; nMain++) {
    }
    nComp = nMain * 3;
    nObjs = nComp + nMain + 1;
    for (nSpin = 0; nSpin < 5 && spin[nSpin].type != 0xD; nSpin++) {
    }
    nObjs += nSpin;
    nObjs += 3;
    for (nProp = 0; nProp < 10 && prop[nProp].type != 0xD; nProp++) {
    }
    nObjs += nProp;
    for (nPost = 0; nPost < 10 && post[nPost].type != 0xD; nPost++) {
    }
    nObjs += nPost;
    for (nLamp = 0; nLamp < 10 && lamp[nLamp].type != 0xD; nLamp++) {
    }
    nObjs += nLamp;
    g->numActorObjs = nObjs;

    // actor models
    C2_SLOTS = ActorObjectInitTable(nObjs);
    j = 0;
    for (i = 0; i < nMain; i++, j++) {
        fn_800BDC88(C2_SLOTS, j, j, STADIUM_FILE(files, idx[1 + i]), NULL, NULL);
    }
    compBase = j;
    for (i = 0; i < nComp; i++, j++) {
        fn_800BDC88(C2_SLOTS, j, j, STADIUM_FILE(files, idx[3]), NULL, NULL);
        fn_3_B97DC(C2_OBJ(j), STADIUM_FILE(files, idx[3] + 2));
    }
    chainIdx = j;
    fn_800BDC88(C2_SLOTS, j, j, STADIUM_FILE(files, idx[4]), NULL, NULL);
    j++;
    spinBase = j;
    for (i = 0; i < nSpin; i++, j++) {
        fn_800BDC88(C2_SLOTS, j, j, STADIUM_FILE(files, idx[5]), NULL, NULL);
    }
    markerIdx = j;
    fn_800BDC88(C2_SLOTS, j, j, STADIUM_FILE(files, idx[6]), NULL, NULL);
    ringIdx = j + 1;
    fn_800BDC88(C2_SLOTS, j + 1, j + 1, STADIUM_FILE(files, idx[7]), NULL, NULL);
    j += 2;
    propBase = j;
    for (i = 0; i < nProp; i++, j++) {
        fn_800BDC88(C2_SLOTS, j, j, STADIUM_FILE(files, idx[8]), NULL, NULL);
        fn_3_B97DC(C2_OBJ(j), STADIUM_FILE(files, idx[8] + 2));
    }
    postBase = j;
    for (i = 0; i < nPost; i++, j++) {
        fn_800BDC88(C2_SLOTS, j, j, STADIUM_FILE(files, idx[9 + i]), NULL, NULL);
    }
    lampBase = j;
    for (i = 0; i < nLamp; i++, j++) {
        fn_800BDC88(C2_SLOTS, j, j, STADIUM_FILE(files, idx[12]), NULL, NULL);
    }
    for (i = 0; i < nObjs; i++) {
        fn_800BD548(C2_OBJ(i), 4, g->lights[0], g->lights[1], g->lights[2], g->lights[3]);
    }

    // animations: one player per object, the first set up from the file, the rest copied
    if (STADIUM_FILE(files, idx[15]) != NULL && STADIUM_FILE(files, idx[16]) != NULL && STADIUM_FILE(files, idx[17]) != NULL) {
        fn_80025DDC(STADIUM_FILE(files, idx[15]));
        fn_80025DDC(STADIUM_FILE(files, idx[16]));
        for (i = 0; i < nMain; i++) {
            fn_80025C58(STADIUM_FILE(files, idx[15 + i]), (ShapeModel**)&C2_OBJ(i)->actor);
        }
        for (i = 0, player = &lbl_3_bss_A034[20]; i < nMain; i++, player++) {
            if (i == 0) {
                player->set = STADIUM_FILE(files, idx[17]);
                fn_80025FFC(STADIUM_FILE(files, idx[15]), player);
            } else {
                memcpy(player, &lbl_3_bss_A034[20 + i - 1], sizeof(ShapeAnimPlayer));
                player->model = STADIUM_FILE(files, idx[15 + i]);
            }
            fn_80025EEC(player, 0, 1);
        }
    }
    if (STADIUM_FILE(files, idx[18]) != NULL && STADIUM_FILE(files, idx[19]) != NULL) {
        fn_80025DDC(STADIUM_FILE(files, idx[18]));
        for (i = 0; i < nLamp; i++) {
            fn_80025C58(STADIUM_FILE(files, idx[18 + i]), (ShapeModel**)&C2_OBJ(lampBase + i)->actor);
        }
        for (i = 0, player = &lbl_3_bss_A034[10]; i < nLamp; i++, player++) {
            if (i == 0) {
                player->set = STADIUM_FILE(files, idx[19]);
                fn_80025FFC(STADIUM_FILE(files, idx[18]), player);
            } else {
                memcpy(player, &lbl_3_bss_A034[10 + i - 1], sizeof(ShapeAnimPlayer));
                player->model = STADIUM_FILE(files, idx[18 + i]);
            }
            fn_80025EEC(player, 0, 0);
        }
    }
    if (STADIUM_FILE(files, idx[20]) != NULL && STADIUM_FILE(files, idx[21]) != NULL && STADIUM_FILE(files, idx[22]) != NULL && STADIUM_FILE(files, idx[23]) != NULL) {
        fn_80025DDC(STADIUM_FILE(files, idx[20]));
        fn_80025DDC(STADIUM_FILE(files, idx[21]));
        fn_80025DDC(STADIUM_FILE(files, idx[22]));
        for (i = 0; i < nPost; i++) {
            fn_80025C58(STADIUM_FILE(files, idx[20 + i]), (ShapeModel**)&C2_OBJ(postBase + i)->actor);
        }
        for (i = 0, player = &lbl_3_bss_A034[0]; i < nPost; i++, player++) {
            if (i == 0) {
                player->set = STADIUM_FILE(files, idx[23]);
                fn_80025FFC(STADIUM_FILE(files, idx[20]), player);
            } else {
                memcpy(player, &lbl_3_bss_A034[0 + i - 1], sizeof(ShapeAnimPlayer));
                player->model = STADIUM_FILE(files, idx[20 + i]);
            }
            fn_80025EEC(player, 0, 0);
        }
    }
    fn_80035750(STADIUM_FILE(files, idx[25]), STADIUM_FILE(files, idx[24]), 5);
    lbl_3_bss_A8A4 = fn_800B0A5C_insertQueue(fn_3_CE954, 2);
    fn_80034E20(lbl_3_bss_A8A4, lbl_3_data_10D3C);
    fn_3_D511C();

    // the object list
    g->count = 0x43;
    g->objs = _OSAllocFromHeap(0x20, 0x43 * sizeof(C2Obj));
    memset(g->objs, 0, 0x43 * sizeof(C2Obj));
    g->objsBackup = _OSAllocFromHeap(0x20, 0x43 * sizeof(C2Obj));
    memset(g->objsBackup, 0, 0x43 * sizeof(C2Obj));
    o = (C2ObjAny*)g->objs;
    player = &lbl_3_bss_A034[20];
    lbl_3_bss_A02C = 0;

    // the mains
    for (i = 0; i < 2; i++, mains++) {
        if (mains->type == 0xD) {
            done = 1;
        }
        if (done) {
            for (; i < 2; i++) {
                lbl_3_data_182C8[i].type = 0xD;
            }
            break;
        }
        o->base.kind = mains->type;
        if (mains->chain == 0) {
            o->main._B8 = &lbl_3_rodata_24DC;
        } else {
            o->main._B8 = &lbl_3_rodata_24D0;
        }
        o->base.actorObj = C2_OBJ(i);
        o->base.shadow = STADIUM_FILE(files, idx[13]);
        o->base.update = (C2ObjFn)fn_3_D3F54;
        o->base.onHit = fn_3_D196C;
        o->base.hasShadow = 1;
        o->base.bit5 = 1;
        o->base.idx = i;
        o->base.alpha = 0xFF;
        o->base.preDraw = (C2ObjFn)fn_3_D1AC4;
        o->base._8C = player;
        o->base._94 = 0;
        o->base._96 = -1;
        o->base._98 = 1;
        if (mains->chain == 0) {
            o->main.nodes = &lbl_3_bss_A8D0[12];
        } else {
            o->main.nodes = &lbl_3_bss_A8D0[4];
        }
        fn_3_D4E00(&o->main);
        o++;
        count++;
        player++;
        lbl_3_bss_A02D++;
    }

    // three companions per main, standing next to it
    done = 0;
    for (i = 0; i < 6; i++) {
        T52* mn = &lbl_3_data_182C8[i / 3];
        if (mn->type == 0xD) {
            done = 1;
        }
        if (done) {
            break;
        }
        o->base.kind = 1;
        m = (C2Obj*)g->objs + i / 3;
        o->base.actorObj = C2_OBJ(compBase + i);
        o->base.shadow = NULL;
        o->base.update = (C2ObjFn)fn_3_D1848;
        o->base.onHit = NULL;
        o->base.visible = 0;
        o->base.hasShadow = 0;
        o->comp.speed = o->base.actorObj->unk54;
        o->base.bit5 = 0;
        o->base.ctrl.base.type = 0;
        PSMTXRotRad(mtx, 'Y', lbl_3_rodata_2658[0] * -mn->f);
        off.x = lbl_3_rodata_265C;
        off.y = lbl_3_rodata_2660;
        off.z = lbl_3_rodata_2664;
        PSMTXMultVec(mtx, &off, &off);
        CTRLSetTranslation((Control*)o, off.x + mn->x, mn->y - off.y, off.z + mn->z);
        CTRLSetScale((Control*)o, lbl_3_rodata_26C8, lbl_3_rodata_26C8, lbl_3_rodata_26C8);
        o->base.alpha = 0xFF;
        o->base.preDraw = (C2ObjFn)fn_3_D173C;
        o->base._8C = NULL;
        count++;
        o->base._94 = 0;
        o->base._96 = -1;
        o->base._98 = 1;
        o->comp.mainFlag = &((C2ObjMain*)m)->_CA;
        o->base.idx = i;
        o->comp.delay = (i % 3) * 30;
        o->comp._AD = 0;
        o++;
    }

    // 14 chain links, 7 on each chain
    for (i = 0; i < 14; i++, o++) {
        chain = (i / 7 == 0) ? &lbl_3_bss_A8D0[12] : &lbl_3_bss_A8D0[4];
        o->link.a = chain + i % 7;
        o->link.b = chain + (i % 7 + 1);
        o->base.kind = 2;
        o->base.actorObj = C2_OBJ(chainIdx);
        o->base.shadow = NULL;
        o->base.update = (C2ObjFn)fn_3_D1280;
        o->base.onHit = NULL;
        o->base.visible = 1;
        o->base.hasShadow = 0;
        o->base.bit5 = 1;
        fn_3_D141C(&o->link);
        PSVECAdd(&o->link.b->pos, &o->link.a->pos, &o->link.pos);
        PSVECScale(&o->link.pos, lbl_3_rodata_26A0, &o->link.pos);
        CTRLSetTranslation((Control*)o, o->link.pos.x, -o->link.pos.y, o->link.pos.z);
        CTRLSetScale((Control*)o, lbl_3_rodata_26C8, lbl_3_rodata_26C8, lbl_3_rodata_26C8);
        o->base.alpha = 0xFF;
        count++;
        o->base.preDraw = (C2ObjFn)fn_3_D127C;
        o->base._8C = NULL;
        o->base._94 = 0;
        o->base._96 = -1;
        o->base._98 = 1;
        o->base.idx = i;
    }
    lbl_3_bss_A02A = count;

    // the spinners
    done = 0;
    axis = lbl_3_rodata_25F8;
    for (i = 0; i < 5; i++, spin++) {
        if (spin->type == 0xD) {
            done = 1;
        }
        if (done) {
            // (sic) the original re-marks only entry i
            for (k = i; k < 6; k++) {
                lbl_3_data_18364[i].type = 0xD;
            }
            break;
        }
        o->base.kind = spin->type;
        o->base.idx = i;
        o->spin._D2 = count;
        o->base.actorObj = C2_OBJ(spinBase + i);
        o->base.shadow = NULL;
        o->base.update = (C2ObjFn)fn_3_D0918;
        o->base.onHit = NULL;
        o->base.visible = 1;
        sh = 0;
        if (o->base.visible && o->base.shadow != NULL) {
            sh = 1;
        }
        o->base.hasShadow = sh;
        model = o->base.actorObj->actor->boneArray[3];
        CTRLGetQuat(&model->orientCtrl.base, &o->spin.rot.x, &o->spin.rot.y, &o->spin.rot.z, &o->spin.rot.w);
        o->spin.pos.x = lbl_3_data_18364[o->base.idx].x;
        o->spin.pos.y = lbl_3_data_18364[o->base.idx].y;
        o->spin.pos.z = lbl_3_data_18364[o->base.idx].z;
        o->spin._C0 = lbl_3_rodata_2664;
        o->base.ctrl.base.type = 0;
        CTRLSetTranslation((Control*)o, o->spin.pos.x, -o->spin.pos.y, o->spin.pos.z);
        CTRLSetRotation((Control*)o, lbl_3_rodata_2664, lbl_3_data_18364[o->base.idx].r, lbl_3_rodata_2664);
        C_QUATRotAxisRad(&q, &axis, lbl_3_rodata_2658[0] * o->spin._C0);
        PSQUATMultiply(&q, &o->spin.rot, &q);
        PSQUATNormalize(&q, &q);
        CTRLSetQuat(&model->orientCtrl.base, q.x, q.y, q.z, q.w);
        count++;
        o->spin._C8 = lbl_3_data_18364[o->base.idx].y;
        o->spin._BC = lbl_3_rodata_2664;
        o->spin._C4 = lbl_3_rodata_2664;
        o->spin._D1 = 0;
        o->base.bit5 = 1;
        o->base.alpha = 0xFF;
        o->base._8C = NULL;
        o->base.preDraw = (C2ObjFn)fn_3_D0528;
        o->base._94 = 0;
        o->base._96 = -1;
        o->base._98 = 1;
        o->base._9A = 1;
        o++;
        lbl_3_bss_A02B++;
    }
    lbl_3_bss_A028 = count;

    // a marker under each spinner (fn_3_D0284)
    for (k = 0; k < lbl_3_bss_A02B; k++, o++) {
        m = (C2Obj*)g->objs + (lbl_3_bss_A02A + k);
        o->base.kind = 4;
        o->base.idx = k;
        o->d0284.target = (C2ObjSpin*)m;
        o->d0284._C0 = count;
        o->d0284._BC = lbl_3_rodata_2698;
        o->base.actorObj = C2_OBJ(markerIdx);
        o->base.shadow = NULL;
        o->base.update = (C2ObjFn)fn_3_D0284;
        o->base.onHit = NULL;
        o->base.visible = 1;
        sh = 0;
        if (o->base.visible && o->base.shadow != NULL) {
            sh = 1;
        }
        o->base.hasShadow = sh;
        o->base.ctrl.base.type = 0;
        CTRLSetTranslation((Control*)o, ((C2ObjSpin*)m)->pos.x, lbl_3_rodata_2664, ((C2ObjSpin*)m)->pos.z);
        count++;
        o->d0284._A4 = ((C2ObjSpin*)m)->pos.x;
        o->d0284._A8 = ((C2ObjSpin*)m)->pos.y;
        o->d0284._AC = ((C2ObjSpin*)m)->pos.z;
        o->d0284._A8 = lbl_3_rodata_2664;
        o->base.bit5 = m->bit5;
        o->base.alpha = 0xFF;
        o->base._8C = NULL;
        o->base.preDraw = (C2ObjFn)fn_3_D0280;
        o->base._94 = 0;
        o->base._96 = -1;
        o->base._98 = m->_98;
        lbl_3_bss_A029++;
    }
    lbl_3_bss_A026 = count;

    // the ring around each spinner that carries the ball (fn_3_D00D0)
    for (k = 0; k < lbl_3_bss_A02B; k++, o++) {
        m = (C2Obj*)g->objs + (lbl_3_bss_A02A + k);
        o->base.kind = 5;
        o->base.idx = k;
        o->fx.target = (C2ObjSpin*)m;
        o->fx.marker = (C2ObjD0284*)((C2Obj*)g->objs + (lbl_3_bss_A028 + k));
        o->fx._AC = count;
        o->base.actorObj = C2_OBJ(ringIdx);
        o->base.shadow = NULL;
        o->base.update = (C2ObjFn)fn_3_D00D0;
        o->base.onHit = NULL;
        o->base.visible = 1;
        o->base.hasShadow = 0;
        o->base.ctrl.base.type = 0;
        CTRLSetTranslation((Control*)o, ((C2ObjSpin*)m)->pos.x, lbl_3_rodata_2664, ((C2ObjSpin*)m)->pos.z);
        count++;
        o->base.bit5 = m->bit5;
        o->base.alpha = 0xFF;
        o->base._8C = NULL;
        o->base.preDraw = (C2ObjFn)fn_3_D00CC;
        o->base._94 = 0;
        o->base._96 = -1;
        o->base._98 = m->bit5;
        lbl_3_bss_A027++;
    }

    // the props
    done = 0;
    phase = 0;
    for (i = 0; i < 10; i++, prop++) {
        if (prop->type == 0xD) {
            done = 1;
        }
        if (done) {
            for (; i < 11; i++) {
                lbl_3_data_185D0[i].type = 0xD;
            }
            break;
        }
        o->base.kind = prop->type;
        o->prop.phase = phase;
        o->base.actorObj = C2_OBJ(propBase + i);
        o->base.shadow = NULL;
        o->base.update = (C2ObjFn)fn_3_CFA8C;
        o->base.onHit = NULL;
        o->base.visible = 1;
        sh = 0;
        if (o->base.visible && o->base.shadow != NULL) {
            sh = 1;
        }
        o->base.hasShadow = sh;
        o->base.ctrl.base.type = 0;
        CTRLSetScale((Control*)o, prop->scale.x, prop->scale.y, prop->scale.z);
        CTRLSetTranslation((Control*)o, prop->pos.x, prop->pos.y, prop->pos.z);
        CTRLSetRotation((Control*)o, lbl_3_rodata_2664, -prop->rotY, lbl_3_rodata_2664);
        o->base.bit5 = 0;
        o->base.alpha = 0xFF;
        count++;
        o->base._8C = NULL;
        phase += 30;
        o->base.preDraw = (C2ObjFn)fn_3_CFA88;
        o->base._94 = 0;
        o->base._96 = -1;
        o->base._98 = 1;
        o++;
    }
    lbl_3_bss_A022 = count;

    // the posts (fn_3_CF930; hit by the ball: fn_3_CF72C)
    done = 0;
    for (i = 0; i < 10; i++, post++) {
        if (post->type == 0xD) {
            done = 1;
        }
        if (done) {
            for (; i < 11; i++) {
                memset(&lbl_3_data_18730[i], 0, sizeof(T16));
                lbl_3_data_18730[i].type = 0xD;
            }
            break;
        }
        o->base.kind = i + 8;
        o->base.idx = i;
        o->hit._A4 = 0;
        o->hit.emitter = NULL;
        o->base.actorObj = C2_OBJ(postBase + i);
        o->base.shadow = STADIUM_FILE(files, idx[14]);
        o->base.update = (C2ObjFn)fn_3_CF930;
        o->base.onHit = fn_3_CF72C;
        o->base.visible = 1;
        sh = 0;
        if (o->base.visible && o->base.shadow != NULL) {
            sh = 1;
        }
        o->base.hasShadow = sh;
        o->base.ctrl.base.type = 0;
        CTRLSetTranslation((Control*)o, post->x, -post->y, post->z);
        o->base.bit5 = 1;
        o->base.alpha = 0xFF;
        count++;
        o->base._8C = NULL;
        o->base.preDraw = (C2ObjFn)fn_3_CF92C;
        o->base._94 = 0;
        o->base._96 = -1;
        o->base._98 = 1;
        o++;
        lbl_3_bss_A023++;
    }

    // the lamps (animated, fn_3_CED3C)
    done = 0;
    player = &lbl_3_bss_A034[10];
    for (i = 0; i < 10; i++, lamp++) {
        if (lamp->type == 0xD) {
            done = 1;
        }
        if (done) {
            // (sic) the original marks the end of the prop list here
            for (; i < 11; i++) {
                lbl_3_data_185D0[i].type = 0xD;
            }
            break;
        }
        o->base.kind = lamp->type;
        o->base.actorObj = C2_OBJ(lampBase + i);
        o->base.shadow = NULL;
        o->base.update = (C2ObjFn)fn_3_CED3C;
        o->base.onHit = NULL;
        o->base.visible = 1;
        sh = 0;
        if (o->base.visible && o->base.shadow != NULL) {
            sh = 1;
        }
        o->base.hasShadow = sh;
        o->base.ctrl.base.type = 0;
        CTRLSetTranslation((Control*)o, lamp->x, lamp->y, lamp->z);
        o->base.bit5 = 1;
        o->base.alpha = 0xFF;
        o->base._8C = player;
        player++;
        o->base.preDraw = (C2ObjFn)fn_3_CED38;
        o->base._94 = 0;
        o->base._96 = -1;
        o->base._98 = 1;
        o->base.bits |= 0x10;
        o->base.bits |= 0x08;
        o->base.bits |= 0x04;
        o->base.bits &= ~0x02;
        o++;
    }

    g->groupBounds = NULL;
    fn_3_D6514();
    fn_3_CE8E4();
    fn_3_B97C8(fn_3_CD958);
}
#endif
#pragma dont_inline off

