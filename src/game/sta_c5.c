#include "game/sta_c5.h"
#include "game/rep_2998.h"
#include "game/rep_D0.h"
#include "game/m_sound.h"
#include "header_rep_data.h"
#include "Dolphin/os.h"
#include "main/file_80024D2C.h"
#include "game/UnknownHomes_Game.h"
#include "main/file_800263FC.h"
#include "main/file_80011640.h"
#include "static/Camera.h"
#include "C3/unktypes.h"
#include "static/GameSettings.h"
extern u8 lbl_3_data_81DC[];
extern u8 lbl_3_data_8404[];
extern u8 lbl_3_data_84B8[];
extern u32 sndFXStartEx(int, u8, u8, u8);
extern u32 sndFXCtrl(int, int, u8);
extern void fn_3_65A8(void);
extern void fn_3_27648(void);
extern char lbl_3_rodata_2DB8[];
extern char lbl_3_rodata_2F10[];
static inline u32 binomIn(u32 n, u32 k) {
    u32 r = 1;
    u32 i;
    for (i = 1; i <= k; i++) {
        r = r * (n - i + 1) / i;
    }
    return r;
}
#pragma dont_inline on
#include "C3/control.h"
#include "Dolphin/vec.h"
#include "C3/geoPalette.h"
typedef struct { Vec v; f32 pad[2]; } V14;
extern V14 lbl_3_data_1B884[];
typedef struct { f32 a, b, c, d, e; u8 f; u8 pad15[3]; } T18;
extern T18 lbl_3_data_1B9A4[];
extern const f32 lbl_3_rodata_2D5C;
extern const f32 lbl_3_rodata_2D68;
extern char lbl_3_rodata_2DC4[];
extern s32 fn_800247E4(s32, s32, s32, s32);
extern void* fn_3_B9534(u32, u32, void*);
extern int rand(void);
extern s8 lbl_3_bss_AF18[];
extern u8* lbl_3_bss_B118[];
extern void* memset(void*, int, size_t);
extern void* memcpy(void*, const void*, size_t);
extern const f32 lbl_3_rodata_2D50;
extern const f32 lbl_3_rodata_2EE8;
extern const f32 lbl_3_rodata_2DEC;
extern const f32 lbl_3_rodata_2DDC;
extern const f32 lbl_3_rodata_2E88;
extern f64 sin(f64);
extern f32 lbl_3_bss_AF04[];
extern const f32 lbl_3_rodata_2D58;
extern u8 lbl_3_data_1BA70[];
extern u8 lbl_3_data_1B824[];
extern f64 __fabs(f64);
extern camera_803c639c_s* fn_80052768_getCamera(int);
extern char lbl_3_rodata_2D44[];
extern const f32 lbl_3_rodata_2D50;
extern const f32 lbl_3_rodata_2DA0;
extern const f32 lbl_3_rodata_2DA4;
extern const f64 lbl_3_rodata_2DA8;
extern const f32 lbl_3_rodata_2DB0;
extern const f32 lbl_3_rodata_2DB4;
extern void DCFlushRange(void*, u32);
extern const f32 lbl_3_rodata_2D74;
extern const f32 lbl_3_rodata_2DF0;
extern u8 lbl_800E8754[];
extern void fn_3_CB7E8(f32, f32, f32);
extern char lbl_3_rodata_2D38[];
extern const f64 lbl_3_rodata_2DD0;
extern const f32 lbl_3_rodata_2D54;
extern const f32 lbl_3_rodata_2DD8;
extern u8 fn_800527C4(void*);
extern void fn_80064430(Vec* pos, u8 count, f32 scale2, f32 scale); // main/file_800639BC.h
extern f64 acos(f64);
extern const f64 lbl_3_rodata_2DE0;
extern const f32 lbl_3_rodata_2D70;
extern const f32 lbl_3_rodata_2DE8;
extern f64 cos(f64);
extern u8 lbl_803C5090[];
extern void fn_8003A144(void);
extern void* fn_80039AB4(void);
extern s32 fn_8005268C(void);
extern u8* fn_80052734(s32);
extern u8 lbl_3_bss_B219[];
extern ActorObject* lbl_3_bss_B55C;
extern u8 lbl_3_bss_B218[];
extern u8 lbl_3_bss_B21A;
extern void fn_3_B8414(void* a, void* b);
extern void fn_3_B8464(void* mtx, void* obj);
extern void fn_3_B8574(void);
extern void fn_800B4CA0(void*, f32);
extern void AnimateActorBones(void*);
extern u8 lbl_803CBBC0[];
extern u8 lbl_3_data_1BA5C[];

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

extern void fn_800A7D4C(s32 list, void* node);
typedef struct { f32 a, b, c; } V3w;
extern void* lbl_3_bss_B154[]; /* actor anim banks */
extern void fn_3_B97DC(void* obj, void* animBank);
extern const f32 lbl_3_rodata_2E14;
extern f64 pow(f64, f64);
extern f64 sqrt(f64);
extern s16 fn_3_B7F70(s16 range);
struct StadCtlA {
    STADIUM_OBJ_BEGIN
    Control c;
    u8 pad34[0x74 - 0x3C];
    ActorObject* obj;
#ifdef PORT_LP64
    void* pad78[6]; /* six header pointers, 0x78-0x8C */
#else
    u8 pad78[0x90 - 0x78];
#endif
#ifdef TARGET_PC // bitfields in MWCC (big-endian) bit order
    u8 fl90_lo : 7;
    u8 fl90_hi : 1;
#else
    u8 fl90_hi : 1;
    u8 fl90_lo : 7;
#endif
    u8 pad91[8];
    u8 f99;
    u8 pad9A[2];
    u8 idx;
    u8 pad9D[3];
    f32 xa0, ya4, za8, xac, zb0, rb4;
    f32 fb8; /* 0xB8 */
#ifdef PORT_LP64
    /* 0xBC holds yawSrc on GameCube; the other views of these objects use the bytes
       right after it (0xC0..), so the 8-byte PC pointer lives past the GameCube tail. */
    u32 yawSrcSlot; /* 0xBC */
#else
    f32* yawSrc; /* 0xBC */
#endif
    u8 fc0;
    s8 fc1;
    s8 fc2;
    u8 fc3;
    u8 fc4;
    u8 fc5;
    u8 fc6;
    u8 fc7;
#ifdef PORT_LP64
    u8 padC8[0xE8 - 0xC8];
    f32* yawSrc;
#endif
    STADIUM_OBJ_END
};
typedef struct StadCtlA StadCtlA;
extern Vec lbl_3_bss_B260[]; /* bezier control points */
/* Draw-order entry of the stadium object list (same layout as rep_1D58's). */
struct SortEnt {
    f32 z;
    s32 idx;
};
/* Common header of a 0xE8-byte stadium object (lbl_3_common_bss_350E4 objs). */
typedef struct StadObjHdr {
    STADIUM_OBJ_BEGIN
    Control c;                 /* 0x00 */
    u8 pad3C[0x74 - 0x3C];
    ActorObject* actorObj;     /* 0x74 */
    void* shadow;              /* 0x78: passed to fn_3_B8464 */
    void (*update)(void* p);   /* 0x7C */
    void (*onHit)(s32 idx, s32 hitType, struct _CollisionStruct* hit); /* 0x80, called by processStadiumObjectFunction */
    void (*preDraw)(void* p);  /* 0x84 */
    void* f88;                 /* 0x88 */
    void* drawArg;             /* 0x8C */
#ifdef TARGET_PC // bitfields in MWCC (big-endian) bit order
    u8 flag01 : 1;
    u8 zUpdate : 1;
    u8 zAlways : 1;
    u8 zCompare : 1;
    u8 customZ : 1;
    u8 depthSort : 1;
    u8 hasShadow : 1;
    u8 visible : 1;            /* 0x90 */
#else
    u8 visible : 1;            /* 0x90 */
    u8 hasShadow : 1;
    u8 depthSort : 1;
    u8 customZ : 1;
    u8 zCompare : 1;
    u8 zAlways : 1;
    u8 zUpdate : 1;
    u8 flag01 : 1;
#endif
    u8 pad91;
    u8 alpha;                  /* 0x92 */
    u8 pad93;
    s16 attached;              /* 0x94 */
    s16 attachJoint;           /* 0x96 */
    u8 layer;                  /* 0x98 */
    u8 f99;                    /* 0x99 */
    u8 castShadow;             /* 0x9A */
    u8 pad9B;
    u8 idx;                    /* 0x9C */
    u8 kind;                   /* 0x9D */
    u8 pad9E[2];
    struct StadObjHdr* link;   /* 0xA0: paired object (kind-specific) */
#ifdef PORT_LP64
    /* 0xC5 holds the id on GameCube, but the carts' 8-byte pointers push their velocity over
       that byte on PC, so the id lives past the GameCube tail (written by the group setup). */
    u8 padA8[0xE8 - 0xA0 - sizeof(struct StadObjHdr*) + 0x18]; /* past StadCtlA.yawSrc too */
    u8 id;
#else
    u8 padA4[0xC5 - 0xA0 - sizeof(struct StadObjHdr*)];
    u8 id;                     /* 0xC5 */
    u8 padC6[0xE8 - 0xC6];
#endif
    STADIUM_OBJ_END
} StadObjHdr;
/* One 0xE8-byte stadium object of this stadium (lbl_3_common_bss_350E4.objs): the common
   header (as StadObjHdr) and the per-kind state at 0xA0. */
typedef struct StaC5Obj {
    STADIUM_OBJ_BEGIN
    /*0x00*/ Control c;
    /*0x3C*/ u8 pad3C[0x74 - 0x3C];
    /*0x74*/ ActorObject* actorObj;
    /*0x78*/ void* shadow;
    /*0x7C*/ void (*update)(void* p);
    /*0x80*/ void (*onHit)(s32 idx, s32 hitType, struct _CollisionStruct* hit); // called by processStadiumObjectFunction
    /*0x84*/ void (*preDraw)(void* p);
    /*0x88*/ void* f88;
    /*0x8C*/ void* drawArg;
    /*0x90*/ u8 flags; /* StadObjHdr bitfields */
    /*0x91*/ u8 pad91;
    /*0x92*/ u8 alpha;
    /*0x93*/ u8 pad93;
    /*0x94*/ s16 attached;
    /*0x96*/ s16 attachJoint;
    /*0x98*/ u8 layer;
    /*0x99*/ u8 f99;
    /*0x9A*/ u8 castShadow;
    /*0x9B*/ u8 pad9B;
    /*0x9C*/ u8 idx;
    /*0x9D*/ u8 kind;
    /*0x9E*/ u8 pad9E[2];
    /*0xA0*/ union {
        struct { /* walkers (fn_3_EF408 .. fn_3_EF930) */
            /*0xA0*/ Vec pos;
            /*0xAC*/ f32 yaw;    /* degrees */
            /*0xB0*/ f32 _B0;
            /*0xB4*/ f32 turn;   /* degrees left to turn */
            /*0xB8*/ f32 heading; /* radians */
            /*0xBC*/ f32 vy;
            /*0xC0*/ u8 _C0[4];
            /*0xC4*/ s8 turnDir;
            /*0xC5*/ u8 _C5;
            /*0xC6*/ u8 state;
            /*0xC7*/ u8 timer;
            /*0xC8*/ u8 _C8;
        } walk;
        struct { /* placed props (fn_3_F1448, fn_3_F3BB0 ..) */
            /*0xA0*/ Vec pos;
            /*0xAC*/ f32 _AC;
            /*0xB0*/ f32 _B0;
            /*0xB4*/ f32 rotY;
            /*0xB8*/ u8 _B8[0xC1 - 0xB8];
            /*0xC1*/ u8 _C1;
            /*0xC2*/ u8 _C2[2];
            /*0xC4*/ u8 state;
            /*0xC5*/ u8 _C5;
            /*0xC6*/ u8 _C6;
        } prop;
        struct { /* carts carrying a StadCtlA (StadObjB) */
            /*0xA0*/ struct StadCtlA* link;
            /*0xA4*/ struct Emitter* emitter;
            /*0xA8*/ Vec pos;
            /*0xB4*/ Vec vel;
            /*0xC0*/ f32 yaw;
            /*0xC4*/ u8 state;
        } cart;
    } u;
    /*0xCC*/ u8 padCC[0xE8 - 0xCC];
    STADIUM_OBJ_END
} StaC5Obj; // size: 0xE8 (PC: STADIUM_OBJ_SIZE)
/* Stadium object that carries a linked StadCtlA (fn_3_F46A0 / fn_3_F5C30). */
typedef struct StadObjB {
    STADIUM_OBJ_BEGIN
    Control c;                         /* 0x00 */
#ifdef PORT_LP64
    u8 pad3C[0x74 - 0x3C];
    void* p74[2];                      /* 0x74, 0x78 */
#else
    u8 pad3C[0x7C - 0x3C];
#endif
    void (*update)(struct StadObjB* p); /* 0x7C */
#ifdef PORT_LP64
    void* p80[4];                      /* 0x80-0x8C */
    u8 pad90[0x99 - 0x90];
#else
    u8 pad80[0x99 - 0x80];
#endif
    u8 f99;                            /* 0x99 */
    u8 pad9A[2];
    u8 idx;                            /* 0x9C */
    u8 pad9D[3];
    struct StadCtlA* link;             /* 0xA0 */
    struct Emitter* emitter;           /* 0xA4 */
    Vec pos;                           /* 0xA8 */
    Vec vel;                           /* 0xB4 */
    f32 yaw;                           /* 0xC0 */
    u8 state;                          /* 0xC4 */
    u8 padC5[0xE8 - 0xC5];
    STADIUM_OBJ_END
} StadObjB;
/* View of this file's pooled .bss starting at lbl_3_bss_AEE0 (several labelled objects). */
#ifdef PORT_LP64
_Static_assert(sizeof(StaC5Obj) == STADIUM_OBJ_SIZE, "StaC5Obj stride");
_Static_assert(sizeof(StadObjHdr) == STADIUM_OBJ_SIZE, "StadObjHdr stride");
_Static_assert(sizeof(StadObjB) == STADIUM_OBJ_SIZE, "StadObjB stride");
_Static_assert(sizeof(StadCtlA) == STADIUM_OBJ_SIZE, "StadCtlA stride");
_Static_assert(__builtin_offsetof(StaC5Obj, update) == 0x88, "StaC5Obj.update");
_Static_assert(__builtin_offsetof(StaC5Obj, idx) == STADIUM_OBJ_PAD(0x9C), "StaC5Obj.idx");
_Static_assert(__builtin_offsetof(StaC5Obj, u) == STADIUM_OBJ_PAD(0xA0), "StaC5Obj.u");
_Static_assert(__builtin_offsetof(StadObjB, update) == 0x88, "StadObjB.update");
_Static_assert(__builtin_offsetof(StadObjB, link) == __builtin_offsetof(StaC5Obj, u.cart.link), "StadObjB.link");
_Static_assert(__builtin_offsetof(StadObjB, state) == __builtin_offsetof(StaC5Obj, u.cart.state), "StadObjB.state");
_Static_assert(__builtin_offsetof(StadObjHdr, link) == STADIUM_OBJ_PAD(0xA0), "StadObjHdr.link");
_Static_assert(__builtin_offsetof(StadObjHdr, id) >= sizeof(((StaC5Obj*)0)->u) + __builtin_offsetof(StaC5Obj, u), "StadObjHdr.id past the tails");
_Static_assert(__builtin_offsetof(StadObjHdr, id) >= __builtin_offsetof(StadCtlA, yawSrc) + sizeof(void*), "StadObjHdr.id past StadCtlA.yawSrc");
_Static_assert(__builtin_offsetof(StadCtlA, idx) == STADIUM_OBJ_PAD(0x9C), "StadCtlA.idx");
_Static_assert(__builtin_offsetof(StadCtlA, xa0) == STADIUM_OBJ_PAD(0xA0), "StadCtlA.xa0");
_Static_assert(__builtin_offsetof(StadCtlA, fc0) == STADIUM_OBJ_PAD(0xC0), "StadCtlA.fc0");
_Static_assert(__builtin_offsetof(StadCtlA, fc6) == __builtin_offsetof(StaC5Obj, u.walk.state), "StadCtlA.fc6");
#endif
typedef struct StaC5Work {
    /*0x000*/ u8 pad0;
    /*0x001*/ u8 cartBusy;
    /*0x002*/ u8 flag2;
    /*0x003*/ u8 pad3;
    /*0x004*/ u32 pathStep;
    /*0x008*/ u8 _008;
    /*0x009*/ u8 pad9[0xC - 0x9];
    /*0x00C*/ f32 targetX;
    /*0x010*/ u8 pad10[0x14 - 0x10];
    /*0x014*/ u32 _014;
    /*0x018*/ s32 sfx18; /* fn_3_8BBC4 handles */
    /*0x01C*/ s32 sfx1C;
    /*0x020*/ f32 wobVel;
    /*0x024*/ f32 wob;
    /*0x028*/ f32 wobAmp;
    /*0x02C*/ Vec wind;
    /*0x038*/ u8 indTex[0x200]; /* indirect-texture image (fn_3_EECF4) */
    /*0x238*/ u8* indTexImage; /* 16x16 IA8 noise, fn_3_B9534 */
    /*0x23C*/ f32 indTexMtx[2][3];
    /*0x254*/ GXTexObj indTexObj;
    /*0x274*/ u8 pad274[0x27C - 0x274];
    /*0x27C*/ u8 sfxStopped; /* lbl_3_bss_B15C */
    /*0x27D*/ u8 pad27D[3];
    /*0x280*/ ShapeAnimPlayer anim280; /* lbl_3_bss_B160 */
    /*0x2DC*/ ShapeAnimPlayer anim2DC; /* lbl_3_bss_B1BC */
    /*0x338*/ u8 b218; /* lbl_3_bss_B218.. */
    /*0x339*/ u8 b219;
    /*0x33A*/ u8 b21A;
    /*0x33B*/ u8 b21B;
    /*0x33C*/ u8 b21C;
    /*0x33D*/ u8 b21D;
    /*0x33E*/ u8 b21E;
    /*0x33F*/ u8 b21F;
    /*0x340*/ u8 b220;
    /*0x341*/ u8 pad341[3];
    /*0x344*/ f32 pathSpeed;
    /*0x348*/ f32 bezW[7]; /* bernstein weights of lbl_3_bss_B260 */
    /*0x364*/ u8 pad364[0x67C - 0x364];
    /*0x67C*/ ActorObject* actor67C; /* lbl_3_bss_B55C */
    /*0x680*/ void* file680;         /* lbl_3_bss_B560 */
} StaC5Work;
typedef struct StaPlace14 {
    Vec pos;
    f32 rotY;
    u8 type;
    u8 pad11[3];
} StaPlace14;
typedef struct StaPlace18 {
    Vec pos;
    f32 rotY;
    u8 type;
    u8 pad11;
    u8 f12;
    u8 pad13;
    u8 box;
    u8 pad15[3];
} StaPlace18;
/* View of this file's pooled .data starting at lbl_3_data_1B820. */
typedef struct StaC5Data {
    /*0x000*/ s32 _000;
    /*0x004*/ u8 pad4[0x64 - 0x4];
    /*0x064*/ StaPlace14 placesA[6];
    /*0x0DC*/ StaPlace14 placesC[6];
    /*0x154*/ s32 dustEvery[3];  /* frames between dust puffs, per walker state */
    /*0x160*/ f32 dustSize[3];
    /*0x16C*/ u8 pad16C[0x174 - 0x16C];
    /*0x174*/ f32 _174;
    /*0x178*/ s32 dustRate;
    /*0x17C*/ f32 dustScale;
    /*0x180*/ u8 pad180[0x184 - 0x180];
    /*0x184*/ StaPlace18 placesB[6];
    /*0x214*/ u8 pad214[0x228 - 0x214];
    /*0x228*/ f32 targetZ;
    /*0x22C*/ f32 footprint[2][2]; /* (x, z) offsets of two ground probes */
    /*0x23C*/ u8 pad23C[0x24D - 0x23C];
    /*0x24D*/ u8 windReset;
    /*0x24E*/ u8 wobReset;
    /*0x24F*/ u8 pad24F;
    /*0x250*/ Vec windPos;
    /*0x25C*/ Vec windVel;
} StaC5Data;
extern StaC5Work lbl_3_bss_AEE0;
#ifdef TARGET_PC
/* These labels are fields of lbl_3_bss_AEE0 on GameCube. On PC the struct has its own
   layout and the gen file gives each label separate storage, so route them through the struct. */
#define lbl_3_bss_AEE8 (lbl_3_bss_AEE0._008)
#define lbl_3_bss_AF04 (&lbl_3_bss_AEE0.wobAmp)
#define lbl_3_bss_AF18 ((s8*)lbl_3_bss_AEE0.indTex)
#define lbl_3_bss_B118 (&lbl_3_bss_AEE0.indTexImage)
#define lbl_3_bss_B218 (&lbl_3_bss_AEE0.b218)
#define lbl_3_bss_B219 (&lbl_3_bss_AEE0.b219)
#define lbl_3_bss_B21A (lbl_3_bss_AEE0.b21A)
#define lbl_3_bss_B21B (lbl_3_bss_AEE0.b21B)
#define lbl_3_bss_B21C (lbl_3_bss_AEE0.b21C)
#define lbl_3_bss_B21D (&lbl_3_bss_AEE0.b21D)
#define lbl_3_bss_B21E (&lbl_3_bss_AEE0.b21E)
#define lbl_3_bss_B21F (lbl_3_bss_AEE0.b21F)
#define lbl_3_bss_B220 (&lbl_3_bss_AEE0.b220)
#define lbl_3_bss_B55C (lbl_3_bss_AEE0.actor67C)
#endif
extern StaC5Data lbl_3_data_1B820;
extern StadiumObjList lbl_3_common_bss_350E4;
extern InMemFielderType g_Fielders[9];
extern const f32 lbl_3_rodata_2D60;
extern const f32 lbl_3_rodata_2D64;
extern const f32 lbl_3_rodata_2D6C;
extern const f64 lbl_3_rodata_2D78;
extern const f64 lbl_3_rodata_2D80;
extern const f64 lbl_3_rodata_2D88;
extern const f64 lbl_3_rodata_2D90;

void fn_3_EDFAC(void) {
    StaC5Work* st = &lbl_3_bss_AEE0;
    if (g_GameLogic.gameStatus != 0x21) {
        if (g_GameLogic.gameStatus == 0xB) {
            if (st->sfxStopped == 0) {
                fn_3_8B890(st->sfx1C);
                fn_3_8B890(st->sfx18);
                st->sfxStopped = 1;
            }
        } else {
            if (st->sfxStopped != 0) {
                st->sfx1C = fn_3_8BBC4(((u16*)lbl_3_data_81DC)[g_d_GameSettings.StadiumID] + 6, 0, 0, 4);
                st->sfx18 = fn_3_8BBC4(((u16*)lbl_3_data_81DC)[g_d_GameSettings.StadiumID] + 7, 0, 0, 5);
                st->sfxStopped = 0;
                return;
            }
            fn_3_8BA60(st->sfx1C, 0, 0);
            fn_3_8BA60(st->sfx18, 0, 0);
        }
    }
}

s32 fn_3_EE0BC(u32 v) {
    switch ((v >> 4) & 0xF) {
    case 0:
    case 1:
        return 1;
    case 2:
    case 3:
        return 2;
    case 4:
        return 4;
    default:
        return 0;
    }
}
#include "Dolphin/GX/GXPixel.h"

// .text:0x000EE100 size:0x288 mapped:0x8072D194
// NONMATCHING 93%: matrix setup is right; scheduling of the first PSMTXCopy/scale block and const load forms differ
#if NONMATCHING
void fn_3_EE100(struct DODisplayObj* obj, f32 (*mtx)[4]) {
    Mtx b;
    Mtx a;
    Mtx c;
    Mtx44 d;
    GXColor col;
    f32 f31;
    f32 f9;
    col.r = 0xFF;
    col.g = 0xFF;
    col.b = 0xFF;
    col.a = 0xFF;
    GXSetChanMatColor(GX_COLOR0A0, col);
    GXSetNumChans(1);
    f31 = lbl_3_bss_AF04[0];
    PSMTXCopy(obj->worldMatrix, a);
    PSMTXCopy(mtx, b);
    f9 = 1.0f + f31;
    b[0][3] += ((f32*)lbl_3_data_1BA70)[0];
    b[0][0] *= f9;
    b[0][1] *= f9;
    b[1][3] += ((f32*)lbl_3_data_1BA70)[1];
    b[0][2] *= f9;
    b[1][0] *= f9;
    b[1][1] *= f9;
    b[1][2] *= f9;
    PSMTXConcat(b, a, a);
    PSMTXIdentity(c);
    PSMTX44Copy((f32(*)[4])fn_80052734(fn_8005268C()), d);
    c[0][0] = d[0][0];
    c[0][2] = d[0][2];
    c[1][1] = d[1][1];
    c[1][2] = d[1][2];
    c[2][2] = d[3][2];
    PSMTXConcat(c, a, a);
    PSMTXIdentity(c);
    c[0][0] = lbl_3_rodata_2D54;
    c[0][2] = lbl_3_rodata_2D54;
    c[1][1] = lbl_3_rodata_2D58;
    c[1][2] = lbl_3_rodata_2D54;
    c[2][2] = lbl_3_rodata_2D50;
    c[2][3] = lbl_3_rodata_2D5C;
    c[1][3] = lbl_3_rodata_2D5C;
    c[0][3] = lbl_3_rodata_2D5C;
    PSMTXConcat(c, a, a);
    GXLoadTexMtxImm(a, 0x1E, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3X4, GX_TG_POS, 0x1E, 0, 0x7D);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
}
#endif

// .text:0x000EE388 size:0x2F4 mapped:0x8072D41C
// NONMATCHING 86%: original reaches windVel.y/windPos.y/wind.z through a second addi'd pointer reg (separate static Vecs); float reg order differs
#if NONMATCHING
void fn_3_EE388(void) {
    StaC5Data* d = (StaC5Data*)&lbl_3_data_1B820;
    StaC5Work* w = (StaC5Work*)&lbl_3_bss_AEE0;
    f32 ang;
    f32 mag;
    f32 a;
    f32 amp;
    if (d->windReset != 0) {
        rand();
        ang = lbl_3_rodata_2D60 * ((f32)rand() / lbl_3_rodata_2D64);
        w->wind.x = lbl_3_rodata_2D68 * (f32)cos(ang);
        w->wind.y = lbl_3_rodata_2D68 * (f32)sin(ang);
        w->wind.z = lbl_3_rodata_2D5C;
        PSVECSubtract(&w->wind, &d->windPos, &d->windVel);
        if (PSVECMag(&d->windVel) != lbl_3_rodata_2D5C) {
            PSVECNormalize(&d->windVel, &d->windVel);
        }
        PSVECScale(&d->windVel, lbl_3_rodata_2D6C, &d->windVel);
        d->windReset = 0;
    }
    PSVECAdd(&d->windPos, &d->windVel, &d->windPos);
    mag = PSVECMag(&w->wind);
    if (PSVECMag(&d->windPos) > mag) {
        d->windVel.x *= lbl_3_rodata_2D70;
        d->windVel.y *= lbl_3_rodata_2D70;
        PSVECScale(&w->wind, lbl_3_rodata_2D74, &w->wind);
    } else if (PSVECDotProduct(&d->windPos, &w->wind) <= lbl_3_rodata_2D5C) {
        d->windPos.y = lbl_3_rodata_2D5C;
        d->windPos.x = lbl_3_rodata_2D5C;
        d->windReset = 1;
    }
    if (d->wobReset != 0) {
        a = (f32)rand() / lbl_3_rodata_2D64;
        d->wobReset = 0;
        w->wob = lbl_3_rodata_2D5C;
        amp = lbl_3_rodata_2D78 * (lbl_3_rodata_2D80 * (a - lbl_3_rodata_2D88));
        w->wobAmp = amp;
        w->wobVel = lbl_3_rodata_2D90 * (__fabs(amp) / amp);
    }
    w->wob += w->wobVel;
    if (__fabs(w->wob) >= __fabs(w->wobAmp)) {
        w->wobVel *= lbl_3_rodata_2D70;
    } else if ((s32)(__fabs(w->wob) / w->wob) != (s32)(__fabs(w->wobAmp) / w->wobAmp)) {
        d->wobReset = 1;
    }
}
#endif

// .text:0x000EE67C size:0x2F0 mapped:0x8072D710
void fn_3_EE67C(struct DODisplayObj* a, f32 (*m)[4]) {
    Mtx mtx;
    GXVtxDescList list[27];
    DisplayStateList* node;
    PositionData* h;
    s32 sz;
    s32 i;
    s32 n;
    s32 k;
    s32 attr;
    s32 v;
    PSMTXConcat(m, (f32(*)[4])(&a->worldMatrix[0][0]), mtx);
    GXLoadPosMtxImm(mtx, 0);
    GXSetCurrentMtx(0);
    h = a->positionData;
    switch ((u8)(h->quantizeInfo >> 4)) {
    case 0:
    case 1:
        sz = 1;
        break;
    case 2:
    case 3:
        sz = 2;
        break;
    case 4:
        sz = 4;
        break;
    default:
        sz = 0;
        break;
    }
#ifdef TARGET_PC
    (GXSetArray)(GX_VA_POS, PTR32_GET(char, h->positionArray), (u32)h->numPositions * h->compCount * sz,
                 (u8)(h->compCount * sz), TRUE);
#else
    GXSetArray(GX_VA_POS, ((void*)h->positionArray), (u8)(h->compCount * sz));
#endif
    h = a->positionData;
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, h->quantizeInfo >> 4, h->quantizeInfo & 0xF);
    GXSetNumTexGens(1);
    node = PTR32_GET(DisplayStateList, a->displayData->displayStateList);
    for (i = 0; i < a->displayData->numStateEntries; i++) {
        switch (node->id) {
        case 1:
            break;
        case 2:
            GXClearVtxDesc();
            n = 0;
            v = node->setting & 3;
            if (v != 0) {
                list[0].attr = 0;
                list[0].type = v;
                n = 1;
            }
            attr = 9;
            for (k = 2; k < 26; k += 2) {
                v = (node->setting >> k) & 3;
                if (v != 0) {
                    list[n].attr = attr;
                    list[n].type = v;
                    n++;
                }
                attr++;
            }
            v = (node->setting >> 26) & 3;
            if (v != 0) {
                list[n].attr = attr;
                list[n].type = v;
                n++;
            }
            list[n].attr = 0xFF;
            GXSetVtxDescv(list);
            break;
        case 3:
            GXSetChanCtrl(GX_COLOR0A0, 0, 0, 0, 0, 0, 2);
            fn_3_EE100(a, m);
            break;
        case 4:
            break;
        }
        if (((void*)PTR32_GET(char, node->primitiveList)) != NULL) {
            GXCallDisplayList(((void*)PTR32_GET(char, node->primitiveList)), node->listSize);
        }
        node++;
    }
}

// .text:0x000EE96C size:0x228 mapped:0x8072DA00
// NONMATCHING 96%: the original stores the ind-tex matrix through base+0x23c and a separate pointer reg (separate static in the pooled .bss); const load order differs
#if NONMATCHING
void fn_3_EE96C(u8* pos) {
    Mtx m;
    Vec t;
    StaC5Work* st = &lbl_3_bss_AEE0;
    Vec ref = *(Vec*)lbl_3_rodata_2D44;
    f32* mp;
    camera_803c639c_s* cam;
    f32 mag;
    f32 clamp;
    f32 dist;
    f32 sc;
    s32 s0;
    s32 s1;
    cam = fn_80052768_getCamera(fn_8005268C());
    PSVECSubtract(&cam->eye, &cam->target, &t);
    mag = PSVECMag(&t);
    if (mag != lbl_3_rodata_2D5C) {
        PSVECNormalize(&t, &t);
    } else {
        t.y = lbl_3_rodata_2D5C;
        t.x = lbl_3_rodata_2D5C;
        t.z = lbl_3_rodata_2D50;
    }
    acos(PSVECDotProduct(&t, &ref));
    PSVECSubtract(&cam->eye, (Vec*)pos, &t);
    clamp = PSVECMag(&t);
    dist = clamp;
    if (clamp < lbl_3_rodata_2DA0) {
        clamp = lbl_3_rodata_2DA0;
    }
    PSMTXCopy(cam->view, m);
    sc = lbl_3_rodata_2DA4 / clamp;
    st->indTexMtx[0][0] = sc;
    st->indTexMtx[1][1] = sc * (f32)(lbl_3_rodata_2DA8 - __fabs(lbl_3_rodata_2D54 * (ref.y * m[1][1])));
    if (dist < lbl_3_rodata_2DB0) {
        s0 = 4;
        s1 = 4;
    } else if (dist < lbl_3_rodata_2DB4) {
        s0 = 3;
        s1 = 3;
    } else {
        s0 = 2;
        s1 = 2;
    }
    st->_014 = 0;
    DCFlushRange(((void*)st->indTexImage), 0x200);
    GXSetIndTexMtx(GX_ITM_0, (f32(*)[3])(&st->indTexMtx[0][0]), 2);
    GXLoadTexObj(&st->indTexObj, GX_TEXMAP7);
    GXSetIndTexOrder(GX_IND_TEX_STAGE_0, GX_TEXCOORD0, GX_TEXMAP7);
    GXSetNumIndStages(1);
    GXSetIndTexCoordScale(GX_IND_TEX_STAGE_0, s0, s1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_IND_TEX_STAGE_0, 1, 0, GX_ITM_0);
}
#endif

// .text:0x000EEB94 size:0x160 mapped:0x8072DC28
void fn_3_EEB94(void) {
    u32 i, j;
    for (i = 0; i < 0x10; i++) {
        for (j = 0; j < 0x10; j++) {
            s32 idx = fn_800247E4(j, i, 0x10, 2);
            s32 a = lbl_3_bss_B118[0][idx];
            s32 b = lbl_3_bss_B118[0][idx + 1];
            a += lbl_3_bss_AF18[idx] * (rand() % 14 + 8);
            b += lbl_3_bss_AF18[idx + 1] * (rand() % 14 + 8);
            if (a >= 0xE3) {
                a--;
                lbl_3_bss_AF18[idx] = -1;
            } else if (a <= 0x1B) {
                a++;
                lbl_3_bss_AF18[idx] = 1;
            }
            if (b >= 0xE3) {
                b--;
                lbl_3_bss_AF18[idx + 1] = -1;
            } else if (b <= 0x1B) {
                b++;
                lbl_3_bss_AF18[idx + 1] = 1;
            }
            lbl_3_bss_B118[0][idx] = a;
            lbl_3_bss_B118[0][idx + 1] = b;
        }
    }
}

#pragma dont_inline off
// .text:0x000EECF4 size:0x148 mapped:0x8072DD88
// NONMATCHING 99.6%: only the GXSetIndTexMtx matrix stores differ (orig: first store via r30+0x23c, rest via pointer r4+4..0x14: separate static in the pooled .bss)
#if NONMATCHING
void fn_3_EECF4(void) {
    StaC5Work* s = &lbl_3_bss_AEE0;
    u32 i, j;
    f32 (*m)[3] = lbl_3_bss_AEE0.indTexMtx;
    s->indTexMtx[0][0] = lbl_3_rodata_2D68;
    m[0][1] = lbl_3_rodata_2D5C;
    m[0][2] = lbl_3_rodata_2D5C;
    m[1][0] = lbl_3_rodata_2D5C;
    m[1][1] = lbl_3_rodata_2D68;
    m[1][2] = lbl_3_rodata_2D5C;
    GXSetIndTexMtx(GX_ITM_0, m, 2);
    s->indTexImage = (u8*)fn_3_B9534(0x10, 0x10, &s->indTexObj);
    if (s->indTexImage == NULL) {
        OSPanic(lbl_3_rodata_2DB8, 0x1028, lbl_3_rodata_2DC4);
    }
    for (i = 0; i < 0x10; i++) {
        for (j = 0; j < 0x10; j++) {
            s32 idx = fn_800247E4(j, i, 0x10, 2);
            s->indTexImage[idx] = (u8)(rand() % 200) + 0x1B;
            s->indTexImage[idx + 1] = (u8)(rand() % 200) + 0x1B;
        }
    }
    memset(s->indTex, 1, 0x200);
}
#endif

#pragma dont_inline on
// .text:0x000EEE3C size:0xE8 mapped:0x8072DED0
void fn_3_EEE3C(void) {
    ActorObject* b = lbl_3_bss_B55C;
    GameBone* o = (GameBone*)b->actor;
    Vec v;
    lbl_803C5090[0x1D] = 1;
    fn_8003A144();
    SetDisplayStateTexture(fn_80039AB4(), 0, 0);
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    o = (GameBone*)((GameActor*)o)->drawPriorityList.Head;
    while (o != NULL) {
        v.x = o->forwardMtx[0][3];
        v.y = o->forwardMtx[1][3];
        v.z = o->forwardMtx[2][3];
        ((void (*)(Vec*))fn_3_EE96C)(&v);
        if (o->dispObj != NULL) {
            DOSetWorldMatrix(o->dispObj, o->forwardMtx);
            fn_3_EE67C(o->dispObj, ((camera_803c639c_s*)fn_80052734(fn_8005268C()))->view);
        }
        o = (GameBone*)o->drawPriorityLink.Next;
        GXSetTevDirect(0);
    }
}

// .text:0x000EEF24 size:0x80 mapped:0x8072DFB8
void fn_3_EEF24(void) {
    if (lbl_8036E548._3088 == 0) {
        fn_800B0A14_removeQueue(&lbl_8036E548);
        return;
    }
    if (lbl_8036E548._307E != 0) {
        fn_800BDA24(lbl_3_bss_B55C);
        fn_3_EE388();
        fn_3_EEB94();
#ifdef TARGET_PC
        {
            /* lbl_3_data_1BA5C holds two 8-byte draw nodes {next, func = fn_3_EEE3C} (the func
               is a REL relocation, so the generated bytes are 0). The PC node is pointer-sized
               (DrawCallbackNode, main/video_system.h), so keep real nodes here. */
            typedef struct { uintptr_t next; void (*func)(void* node); } StaC5DrawNode;
            static StaC5DrawNode sDrawNodes[2] = {
                {0, (void (*)(void*))fn_3_EEE3C}, {0, (void (*)(void*))fn_3_EEE3C}};
            fn_800A7D4C(1, &sDrawNodes[lbl_803CBBC0[0]]);
        }
#else
        fn_800A7D4C(1, lbl_3_data_1BA5C + lbl_803CBBC0[0] * 8);
#endif
    }
}

// .text:0x000EEFA4 size:0x2C mapped:0x8072E038
void fn_3_EEFA4(void* arg) {
    GXSetZMode(1, 3, 0);
}

// .text:0x000EEFD0 size:0x4 mapped:0x8072E064
void fn_3_EEFD0(void) {
    return;
}

// .text:0x000F13F8 size:0x50 mapped:0x8073048C
#pragma dont_inline off
void fn_3_F13F8(StaC5Obj* p) {
    GameActor* o = p->actorObj->actor;
    u32 i;
    for (i = 0; i < o->totalBones; i++) {
        GameBone* e = o->boneArray[i];
        e->animCtrl.type = 0;
        e->blendCtrl.type = 0;
    }
    p->actorObj->setAnimation = 0;
}
#pragma dont_inline on

// .text:0x000EEFD4 size:0x244 mapped:0x8072E068
void fn_3_EEFD4(s32 idx, s32 hitType, struct _CollisionStruct* hit) {
    Vec d;
    Vec ref;
    StaC5Obj* e = (StaC5Obj*)lbl_3_common_bss_350E4.objs + idx;
    ref = *(Vec*)lbl_3_rodata_2D38;
    if (e->u.walk.state < 3) {
        f32 t;
        f32 ang;
        u32 stad;
        u32 h;
        u8 v;
        d.x = g_Ball.physicsSubstruct.velocity.x;
        d.y = lbl_3_rodata_2D5C;
        d.z = g_Ball.physicsSubstruct.velocity.z;
        PSVECNormalize(&d, &d);
        t = (f32)acos(PSVECDotProduct(&ref, &d));
        ang = t;
        if (d.z < lbl_3_rodata_2D5C) {
            ang = lbl_3_rodata_2DD0 - t;
        }
        {
            f32 half = lbl_3_rodata_2D54;
            e->u.walk.heading = ang;
            e->u.walk.vy = half;
        }
        e->u.walk.state = 4;
        fn_3_F13F8(e);
        if (g_Ball.AtBat_ContactResult != 2 && lbl_800E8754[4] != 0) {
            Vec t;
            CTRLGetTranslation((Control*)e, &t.x, &t.y, &t.z);
            fn_3_CB7E8(t.x, t.y - lbl_3_rodata_2DD8, t.z);
            e->u.walk._C8 = 1;
        }
        stad = g_d_GameSettings.StadiumID;
        if (g_d_GameSettings.GameModeSelected == 6) {
            v = lbl_3_data_84B8[0x12];
        } else {
            v = lbl_3_data_8404[stad * 0x1E + 0x12];
        }
        h = sndFXStartEx((u16)(((u16*)lbl_3_data_81DC)[stad] + 9), v, 0x3F, 0);
        if (g_d_GameSettings.GameModeSelected == 6) {
            v = lbl_3_data_84B8[0x13];
        } else {
            v = lbl_3_data_8404[stad * 0x1E + 0x13];
        }
        sndFXCtrl(h, 0x5B, v);
        fn_3_27648();
        g_FieldingLogic._13B = 1;
    }
}

// .text:0x000EF218 size:0x4 mapped:0x8072E2AC
void fn_3_EF218(void) {
    return;
}

#pragma dont_inline off
// .text:0x000EF21C size:0x1B8 mapped:0x8072E2B0
void fn_3_EF21C(StaC5Obj* p) {
    StaC5Data* d = &lbl_3_data_1B820;
    if (g_GameLogic.gameStatus == 2 && fn_800527C4(&p->u) != 0) {
        switch (p->u.walk.state) {
        case 0:
            if (p->u.walk.timer % d->dustEvery[0] == 0) {
                fn_80064430(&p->u.walk.pos, 0, d->dustSize[0], lbl_3_rodata_2D5C);
                return;
            }
            break;
        case 1:
            if (p->u.walk.timer % d->dustEvery[1] == 0) {
                fn_80064430(&p->u.walk.pos, 0, d->dustSize[1], lbl_3_rodata_2D5C);
                return;
            }
            break;
        case 2:
            if (p->u.walk.timer % d->dustEvery[2] == 0) {
                u32 stad;
                u32 h;
                u8 v;
                fn_80064430(&p->u.walk.pos, 1, d->dustSize[2], d->_174);
                stad = g_d_GameSettings.StadiumID;
                if (g_d_GameSettings.GameModeSelected == 6) {
                    v = lbl_3_data_84B8[0x10];
                } else {
                    v = lbl_3_data_8404[stad * 0x1E + 0x10];
                }
                h = sndFXStartEx((u16)(((u16*)lbl_3_data_81DC)[stad] + 8), v, 0x3F, 0);
                if (g_d_GameSettings.GameModeSelected == 6) {
                    v = lbl_3_data_84B8[0x11];
                } else {
                    v = lbl_3_data_8404[stad * 0x1E + 0x11];
                }
                sndFXCtrl(h, 0x5B, v);
            }
            break;
        }
    }
}

// .text:0x000EF3D4 size:0x34 mapped:0x8072E468
void fn_3_EF3D4(StaC5Obj* p, u8 idx) {
    fn_3_B97DC(((void*)p->actorObj), lbl_3_bss_B154[idx]);
}

// .text:0x000EF408 size:0x154 mapped:0x8072E49C
void fn_3_EF408(StaC5Obj* p) {
    Vec a;
    Vec b;
    Vec c;
    f32 ang;
    f32 d;
    a.x = lbl_3_data_1B9A4[p->idx].a - p->u.walk.pos.x;
    a.y = lbl_3_rodata_2D5C;
    a.z = lbl_3_data_1B9A4[p->idx].c - p->u.walk.pos.z;
    PSVECNormalize(&a, &a);
    ang = -(lbl_3_rodata_2DDC * p->u.walk.yaw);
    b.x = (f32)cos(ang);
    b.y = lbl_3_rodata_2D5C;
    b.z = (f32)sin(ang);
    PSVECNormalize(&b, &b);
    d = PSVECDotProduct(&a, &b);
    if (d < lbl_3_rodata_2DE0) {
        d = lbl_3_rodata_2D70;
    }
    p->u.walk.turn = lbl_3_rodata_2DE8 * (f32)acos(d);
    PSVECCrossProduct(&a, &b, &c);
    if (c.y < lbl_3_rodata_2D5C) {
        p->u.walk.turnDir = 1;
    } else {
        p->u.walk.turnDir = -1;
    }
    p->u.walk.state = 0;
}

#pragma dont_inline on
// .text:0x000EF55C size:0x258 mapped:0x8072E5F0
// NONMATCHING 92%: two box-edge loops; lfsx/addi index pattern and per-loop register numbering differ
#if NONMATCHING
u32 fn_3_EF55C(Vec p, u8 idx) {
    u8 a[4] = {1, 3, 0, 2};
    u8 b[4] = {0, 1, 2, 3};
    Vec v28;
    Vec v1c;
    Vec v10;
    u8* t;
    u32 i;
    u8* q;
    s8 sgn;
    f32 z = lbl_3_rodata_2D5C;
    if (p.y > z) {
        return 1;
    }
    t = lbl_3_data_1B824 + idx * 32;
    q = a;
    for (i = 0, sgn = -1; i < 2; i++, q += 2, sgn += 2) {
        u32 c0 = q[0] * 8;
        u32 c1 = q[1] * 8;
        f32 x0 = *(f32*)(t + c0);
        f32 x1 = *(f32*)(t + c1);
        f32 z0 = *(f32*)(t + (c0 + 4));
        f32 z1 = *(f32*)(t + (c1 + 4));
        v1c.y = z;
        v28.x = p.x - x0;
        v28.z = p.z - z0;
        v1c.x = x1 - x0;
        v1c.z = z1 - z0;
        v28.y = z;
        PSVECNormalize(&v28, &v28);
        PSVECNormalize(&v1c, &v1c);
        PSVECCrossProduct(&v1c, &v28, &v10);
        if (v10.y * (f32)sgn < z) {
            return 1;
        }
    }
    z = z;
    q = b;
    for (i = 0, sgn = -1; i < 2; i++, q += 2, sgn += 2) {
        u32 c0 = q[0] * 8;
        u32 c1 = q[1] * 8;
        f32 x0 = *(f32*)(t + c0);
        f32 x1 = *(f32*)(t + c1);
        f32 z0 = *(f32*)(t + (c0 + 4));
        f32 z1 = *(f32*)(t + (c1 + 4));
        v1c.y = z;
        v28.x = p.x - x0;
        v28.z = p.z - z0;
        v1c.x = x1 - x0;
        v1c.z = z1 - z0;
        v28.y = z;
        PSVECNormalize(&v28, &v28);
        PSVECNormalize(&v1c, &v1c);
        PSVECCrossProduct(&v1c, &v28, &v10);
        if (v10.y * (f32)sgn < z) {
            return 1;
        }
    }
    return 0;
}
#endif

// .text:0x000EF7B4 size:0x4C mapped:0x8072E848
u32 fn_3_EF7B4(V3i v, s32 x) {
#ifdef TARGET_PC
    // The original passes the V3i's bits as the Vec (wasm traps on a call
    // through a mismatched prototype) and tests the low byte of the result.
    Vec p;
    memcpy(&p, &v, sizeof(p));
    return (u8)fn_3_EF55C(p, (u8)x) != 0;
#else
    return ((u8 (*)(V3i, s32))fn_3_EF55C)(v, x) != 0;
#endif
}

#pragma dont_inline off
// .text:0x000EF800 size:0x90 mapped:0x8072E894
void fn_3_EF800(StaC5Obj* p) {
#ifdef TARGET_PC // MWCC bit order: f is the top bit (StadiumObj.visible)
    typedef struct { u8 pad[STADIUM_OBJ_PAD(0x90)]; u8 rest : 7; u8 f : 1; } FObj;
#else
    typedef struct { u8 pad[0x90]; u8 f : 1; u8 rest : 7; } FObj;
#endif
    if (p->u.walk.timer == 0) {
        CTRLSetTranslation((Control*)p, p->u.walk.pos.x, lbl_3_rodata_2DEC, p->u.walk.pos.z);
        return;
    }
    if (p->u.walk.timer % 6 == 0) {
        ((FObj*)p)->f = 0;
    } else {
        ((FObj*)p)->f = 1;
    }
    p->u.walk.timer--;
}

// .text:0x000EF890 size:0xA0 mapped:0x8072E924
void fn_3_EF890(StaC5Obj* p) {
    fn_3_F13F8(p);
    CTRLSetScale((Control*)p, lbl_3_rodata_2D74, lbl_3_rodata_2DF0, lbl_3_rodata_2D74);
    p->u.walk.state = 6;
    p->u.walk.timer = 0x4B;
}

#pragma dont_inline on
// .text:0x000EF930 size:0x224 mapped:0x8072E9C4
extern char lbl_3_rodata_2D24[];
extern const f64 lbl_3_rodata_2DF8;
extern const f64 lbl_3_rodata_2E00;
void fn_3_EF930(StaC5Obj* p) {
    Quaternion q2;
    Quaternion q1;
    Vec c;
    Vec e;
    Vec w;
    Vec axis;
    f32 ang;
    axis = *(Vec*)lbl_3_rodata_2D24;
    e.x = lbl_3_rodata_2DF8 * (f32)cos(p->u.walk.heading);
    e.y = p->u.walk.vy;
    e.z = lbl_3_rodata_2DF8 * (f32)sin(p->u.walk.heading);
    PSVECAdd(&p->u.walk.pos, &e, &p->u.walk.pos);
    if (p->u.walk.vy < 0.0f && p->u.walk.pos.y - 1.0f < 0.0f) {
        p->u.walk.pos.x = p->u.walk.pos.x - e.x;
        p->u.walk.pos.y = 1.0f;
        p->u.walk.pos.z = p->u.walk.pos.z - e.z;
        p->u.walk.state = 6;
        p->u.walk.timer = 0x4B;
    } else {
        p->u.walk.vy -= lbl_3_rodata_2E00;
    }
    C_QUATRotAxisRad(&q1, &axis, -(lbl_3_rodata_2DDC * p->u.walk.yaw));
    e.y = -e.y;
    w.x = -e.x;
    w.y = lbl_3_rodata_2D58;
    w.z = -e.z;
    PSVECNormalize(&e, &e);
    PSVECNormalize(&w, &w);
    PSVECCrossProduct(&w, &e, &c);
    ang = (f32)acos(PSVECDotProduct(&e, &w));
    if (lbl_3_rodata_2D50 != ang && lbl_3_rodata_2D70 != ang) {
        C_QUATRotAxisRad(&q2, &c, ang);
        PSQUATMultiply(&q2, &q1, &q2);
        PSQUATNormalize(&q2, &q2);
        CTRLSetQuat((Control*)p, q2.x, q2.y, q2.z, q2.w);
    }
    CTRLSetTranslation((Control*)p, p->u.walk.pos.x, -p->u.walk.pos.y, p->u.walk.pos.z);
}

// .text:0x000EFB54 size:0x630 mapped:0x8072EBE8
extern char lbl_3_rodata_2D0C[];
extern char lbl_3_rodata_2D18[];
extern const f32 lbl_3_rodata_2E08;
extern const f32 lbl_3_rodata_2E0C;
extern const f32 lbl_3_rodata_2E10;
/* Held in a fielder's hand: follow the actor's hand joint and face along the arm. */
// NONMATCHING 82-86%: stack frame 0x10 larger and float regalloc/scheduling differ; the original leaves the yaw uninitialized when fc0 >= 3 (initialized to 0 here)
#if NONMATCHING
void fn_3_EFB54(StadCtlA* p) {
    Vec pos;
    Vec off;
    Vec ref;
    Vec flat;
    Vec tilt;
    Vec axis;
    Quaternion q;
    Quaternion qYaw;
    Quaternion qPitch;
    CharActor* a;
    u32 i;
    s32 dir;
    f32 yaw;
    f32 h;
    f32 r;
    pos = *(Vec*)lbl_3_rodata_2D0C;
    ref = *(Vec*)lbl_3_rodata_2D18;
    a = lbl_8036E548.active[p->fc1];
    if (a == NULL) {
        return;
    }
    if ((s8)(u8)a->modelIndex != (s8)p->fc3) {
        /* the fielder changed; find the actor that still has our id (a ends as the last one checked) */
        for (i = 0; i < 9; i++) {
            a = lbl_8036E548.active[i];
            if (a != NULL && (s8)p->fc3 == (s8)(u8)a->modelIndex) {
                p->fc1 = a->index;
                break;
            }
        }
    }
    if (a == NULL) {
        return;
    }
    memset(&pos, 0, 0xC);
    if (a->_25A == 0) {
        fn_8001B728((s8)(u8)a->index, 0x22, &pos);
        dir = -1;
    } else {
        fn_8001B728((s8)(u8)a->index, 0x1E, &pos);
        dir = 1;
    }
    yaw = 0.0f; /* uninitialized in the original for fc0 >= 3 */
    switch (p->fc0) {
    case 0:
        yaw = -a->rot.y - lbl_3_rodata_2DDC * (f32)(dir * 30 + 90);
        break;
    case 1:
        yaw = -a->rot.y - lbl_3_rodata_2DDC * (f32)(dir * 30 + 60);
        break;
    case 2:
        yaw = -a->rot.y - lbl_3_rodata_2DDC * (f32)(dir * 30 + 120);
        break;
    }
    if (pos.y < lbl_3_rodata_2D5C) {
        h = pos.y;
        if (h < lbl_3_rodata_2E08) {
            h = lbl_3_rodata_2E08;
        }
        r = sqrt(lbl_3_rodata_2E0C - h * h);
    } else {
        h = lbl_3_rodata_2D5C;
        r = lbl_3_rodata_2E10;
    }
    off.x = -r * (f32)cos(yaw);
    off.y = -h;
    off.z = -r * (f32)sin(yaw);
    pos.x += off.x * lbl_3_rodata_2D54;
    pos.y += off.y * lbl_3_rodata_2D54;
    pos.z += off.z * lbl_3_rodata_2D54;
    off.x *= lbl_3_rodata_2D70;
    off.y *= lbl_3_rodata_2D70;
    off.z *= lbl_3_rodata_2D70;
    pos.y *= lbl_3_rodata_2D70;
    p->xa0 = pos.x;
    p->ya4 = pos.y;
    p->za8 = pos.z;
    tilt.x = off.x;
    tilt.y = off.y;
    tilt.z = off.z;
    flat.x = off.x;
    flat.y = off.y;
    flat.z = off.z;
    tilt.z = lbl_3_rodata_2D5C;
    flat.y = lbl_3_rodata_2D5C;
    tilt.x = sqrt(pow(off.x, lbl_3_rodata_2D80) + pow(off.z, lbl_3_rodata_2D80));
    if (r != lbl_3_rodata_2D5C) {
        PSVECNormalize(&flat, &flat);
    }
    PSVECNormalize(&tilt, &tilt);
    p->xac = lbl_3_rodata_2DE8 * -(f32)acos(PSVECDotProduct(&flat, &ref));
    if (flat.z < lbl_3_rodata_2D5C) {
        p->xac = lbl_3_rodata_2E14 - p->xac;
    }
    axis.x = lbl_3_rodata_2D5C;
    axis.y = lbl_3_rodata_2D50;
    axis.z = lbl_3_rodata_2D5C;
    C_QUATRotAxisRad(&qYaw, &axis, lbl_3_rodata_2DDC * p->xac);
    /* zb0 holds the pitch (degrees) for this object kind */
    p->zb0 = lbl_3_rodata_2DE8 * (f32)acos(PSVECDotProduct(&tilt, &ref));
    if (tilt.y < lbl_3_rodata_2D5C) {
        p->zb0 = lbl_3_rodata_2E14 - p->zb0;
    }
    axis.x = lbl_3_rodata_2D5C;
    axis.y = lbl_3_rodata_2D5C;
    axis.z = lbl_3_rodata_2D50;
    C_QUATRotAxisRad(&qPitch, &axis, lbl_3_rodata_2DDC * p->zb0);
    PSQUATMultiply(&qYaw, &qPitch, &q);
    PSQUATNormalize(&q, &q);
    if (PSQUATDotProduct(&q, &q) == lbl_3_rodata_2D5C) {
        axis.x = lbl_3_rodata_2D5C;
        axis.y = lbl_3_rodata_2D50;
        axis.z = lbl_3_rodata_2D5C;
        C_QUATRotAxisRad(&q, &axis, lbl_3_rodata_2D5C);
    }
    if (a->mode[0] != 1) {
        p->fl90_hi = 0;
    } else {
        p->fl90_hi = 1;
    }
    CTRLSetTranslation(&p->c, p->xa0, -p->ya4, p->za8);
    CTRLSetQuat(&p->c, q.x, q.y, q.z, q.w);
}
#endif

// .text:0x000F0184 size:0xA0 mapped:0x8072F218
void fn_3_F0184(void) {
    u32 i;
    if (lbl_3_bss_AEE0._008 != 0) {
        REMOVE_QUEUE_NOARG();
        lbl_3_bss_AEE0._008 = 0;
        return;
    }
    for (i = 0; i < lbl_3_bss_AEE0.b21C; i++) {
        StaC5Obj* e = (StaC5Obj*)lbl_3_common_bss_350E4.objs + (i + lbl_3_bss_AEE0.b21B);
        if (e != NULL && e->u.walk.state == 3) {
            fn_3_EFB54((StadCtlA*)e);
        }
    }
}

// .text:0x000F0224 size:0x608 mapped:0x8072F2B8
extern char lbl_3_rodata_2D00[];
#ifndef TARGET_PC
extern u8 lbl_3_bss_B21B;
#endif
#ifndef TARGET_PC
extern u8 lbl_3_bss_B21C;
#endif
extern const f64 lbl_3_rodata_2E18;
extern const f32 lbl_3_rodata_2E20;
/* Chases the fielder p->fc1; bites when close enough. */
// NONMATCHING 90%: inlines fn_3_F13F8 and fn_3_EF21C (first fn_3_EF55C test is the inlined fn_3_EF7B4 in the original: clrlwi.); original reaches lbl_3_bss_B154/B21B/B21C via the lbl_3_bss_AEE0 pooled base (nmverify flag expected); regalloc differs
#if NONMATCHING
void fn_3_F0224(StadCtlA* p) {
    Vec np;
    Vec d;
    Vec n;
    Vec ref;
    Vec fpos;
    InMemFielderType* f;
    CharActor* actor;
    f32 dist;
    f32 ang;
    u32 i;
    ref = *(Vec*)lbl_3_rodata_2D00;
    f = &g_Fielders[p->fc1];
    fpos = *(Vec*)f;
    actor = lbl_8036E548.active[p->fc1];
    if (fn_3_EF55C(fpos, p->fc5) != 0) {
        p->fc6 = 1;
        p->fc1 = -1;
        fn_3_B97DC(p->obj, lbl_3_bss_B154[0]);
        p->fc7 = 0;
        return;
    }
    d.x = ((Vec*)f)->x - p->xa0;
    d.y = lbl_3_rodata_2D5C;
    d.z = ((Vec*)f)->z - p->za8;
    PSVECNormalize(&d, &n);
    np.x = lbl_3_rodata_2E18 * n.x + p->xa0;
    np.y = p->ya4;
    np.z = lbl_3_rodata_2E18 * n.z + p->za8;
    if (fn_3_EF55C(np, p->fc5) == 0) {
        p->xa0 = np.x;
        p->ya4 = np.y;
        p->za8 = np.z;
    }
    PSVECNormalize(&ref, &ref);
    ang = lbl_3_rodata_2DE8 * (f32)acos(PSVECDotProduct(&n, &ref));
    if (d.z < lbl_3_rodata_2D5C) {
        ang = lbl_3_rodata_2E14 - ang;
    }
    p->xac = -ang;
    memset(&d, 0, 0xC);
    fn_8001B728(p->fc1, 0x23, &d);
    d.y *= lbl_3_rodata_2D70;
    dist = sqrt(pow(((Vec*)f)->x - p->xa0, lbl_3_rodata_2D80) + pow(((Vec*)f)->z - p->za8, lbl_3_rodata_2D80));
    if (dist < lbl_3_rodata_2E20 && __fabs(d.y) <= lbl_3_rodata_2D88) {
        fn_3_F13F8((StaC5Obj*)p);
        for (i = 0; i < lbl_3_bss_B21C; i++) {
            if (i != p->idx) {
                StadCtlA* e = (StadCtlA*)((StaC5Obj*)lbl_3_common_bss_350E4.objs + (i + lbl_3_bss_B21B));
                if (e->fc6 == 3 && e->fc1 == p->fc1) {
                    p->fc0++;
                }
            }
        }
        p->fc7 = 0;
        p->fc6 = 3;
        if (fn_800527C4(f) != 0) {
            u32 stad;
            u8 v;
            u32 h;
            stad = g_d_GameSettings.StadiumID;
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[0x14];
            } else {
                v = lbl_3_data_8404[stad * 0x1E + 0x14];
            }
            h = sndFXStartEx((u16)(((u16*)lbl_3_data_81DC)[stad] + 0xA), v, 0x3F, 0);
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[0x15];
            } else {
                v = lbl_3_data_8404[stad * 0x1E + 0x15];
            }
            sndFXCtrl(h, 0x5B, v);
        }
        g_Fielders[p->fc1]._216[1]++;
        p->fc2 = (s8)(f->charID >> 8); /* the high byte of charID, as the original reads it */
        p->fc3 = actor->modelIndex;
    }
    CTRLSetTranslation(&p->c, p->xa0, -p->ya4, p->za8);
    CTRLSetRotation(&p->c, lbl_3_rodata_2D5C, p->xac, lbl_3_rodata_2D5C);
    fn_3_EF21C((StaC5Obj*)p);
    p->fc7++;
}
#endif

// .text:0x000F082C size:0x778 mapped:0x8072F8C0
extern const f64 lbl_3_rodata_2E28;
/* Wanders inside its box; latches onto a fielder that walks in. */
// NONMATCHING 92%: inlines fn_3_EF21C x2 and fn_3_EF408 (the box tests are the inlined fn_3_EF7B4 in the original: clrlwi); original reaches lbl_3_data_1B9A4 via the lbl_3_data_1B820 pooled base (nmverify flag expected); regalloc differs
#if NONMATCHING
void fn_3_F082C(StadCtlA* p) {
    Vec np;
    InMemFielderType* f;
    u32 i;
    f32 a;
    f32 c;
    f32 s;
    for (i = 0, f = g_Fielders; i < 9; i++, f++) {
        if (f == NULL) {
            break;
        }
        if (fn_3_EF55C(*(Vec*)f, p->fc5) == 0 && f->_15C <= lbl_3_rodata_2D5C) {
            p->fc1 = i;
            p->fc6 = 2;
            fn_3_B97DC(p->obj, lbl_3_bss_B154[1]);
            return;
        }
    }
    switch (p->fc6) {
    case 0:
        fn_3_EF21C((StaC5Obj*)p);
        if (p->rb4 > lbl_3_rodata_2D5C) {
            if (p->rb4 < lbl_3_rodata_2D88) {
                p->xac = (s8)p->fc4 * p->rb4 + p->xac;
                p->rb4 = lbl_3_rodata_2D5C;
            } else {
                p->xac = lbl_3_rodata_2D88 * (s8)p->fc4 + p->xac;
                p->rb4 = p->rb4 - lbl_3_rodata_2D88;
            }
            p->fc7++;
        } else {
            p->fc7 = 0;
            p->fc6 = 1;
        }
        break;
    case 1:
        if (p->fc7 < 20) {
            p->fc7++;
            a = lbl_3_rodata_2DDC * -p->xac;
            c = cos(a);
            s = sin(a);
            np.x = p->xa0 + (f32)(lbl_3_rodata_2E28 * c);
            np.y = p->ya4 + lbl_3_rodata_2D5C;
            np.z = p->za8 + (f32)(lbl_3_rodata_2E28 * s);
            if (fn_3_EF55C(np, p->fc5) != 0) {
                fn_3_EF408((StaC5Obj*)p);
            } else {
                p->xa0 = np.x;
                p->ya4 = np.y;
                p->za8 = np.z;
            }
        } else {
            if (fn_3_B7F70(10) < 8) {
                p->fc6 = 0;
                p->rb4 = fn_3_B7F70(60) + 1;
                p->fc4 = fn_3_B7F70(2) * -1 + 1;
            }
            p->fc7 = 0;
        }
        fn_3_EF21C((StaC5Obj*)p);
        break;
    }
    CTRLSetTranslation(&p->c, p->xa0, -p->ya4, p->za8);
    CTRLSetRotation(&p->c, lbl_3_rodata_2D5C, p->xac, lbl_3_rodata_2D5C);
}
#endif

// .text:0x000F0FA4 size:0x454 mapped:0x80730038
// NONMATCHING 98.5%: inlines fn_3_F1518/fn_3_EF890/fn_3_EF800; only the p->obj load is scheduled later (orig loads it into r3 right after mr r31,r3, g_GameLogic base in r4)
#if NONMATCHING
void fn_3_F0FA4(StadCtlA* p) {
    if (g_GameLogic.gameStatus == 0xB) {
        return;
    }
    if (g_GameLogic.gameStatus == 3) {
        if (p->f99 == 0) {
            fn_3_F1518(p);
        }
        return;
    }
    if (p->f99 != 0) {
        p->f99 = 0;
    }
    if (g_GameLogic.gameStatus == 0) {
        if (p->fc6 >= 4) {
            fn_3_F1518(p);
        }
        return;
    }
    if (p->obj->setAnimation != 0) {
        AnimateActorBones(p->obj->actor);
    }
    switch (p->fc6) {
    case 0:
    case 1:
        fn_3_F082C(p);
        break;
    case 2:
        fn_3_F0224(p);
        break;
    case 4:
        fn_3_EF930((StaC5Obj*)p);
        break;
    case 5:
        fn_3_EF890((StaC5Obj*)p);
        break;
    case 6:
        fn_3_EF800((StaC5Obj*)p);
        break;
    }
}
#endif


// .text:0x000F1448 size:0xD0 mapped:0x807304DC
void fn_3_F1448(StaC5Obj* p) {
    p->u.prop.pos.x = lbl_3_data_1B9A4[p->idx].a;
    p->u.prop.pos.y = lbl_3_data_1B9A4[p->idx].b;
    p->u.prop.pos.z = lbl_3_data_1B9A4[p->idx].c;
    p->u.prop._AC = -lbl_3_data_1B9A4[p->idx].d;
    p->c.type = 0;
    CTRLSetTranslation((Control*)p, p->u.prop.pos.x, -p->u.prop.pos.y, p->u.prop.pos.z);
    CTRLSetRotation((Control*)p, 0.0f, p->u.prop._AC, 0.0f);
    CTRLSetScale((Control*)p, lbl_3_rodata_2D50, lbl_3_rodata_2D50, lbl_3_rodata_2D50);
}


#pragma dont_inline off
// .text:0x000F1518 size:0x15C mapped:0x807305AC
void fn_3_F1518(StadCtlA* p) {
    p->fc5 = lbl_3_data_1B9A4[p->idx].f;
    p->fc6 = 1;
    p->fc7 = 0;
    p->fc1 = -1;
    if (!p->fl90_hi) {
        p->fl90_hi = 1;
    }
    p->f99 = 1;
    p->zb0 = lbl_3_rodata_2D5C;
    p->xa0 = lbl_3_data_1B9A4[p->idx].a;
    p->ya4 = lbl_3_data_1B9A4[p->idx].b;
    p->za8 = lbl_3_data_1B9A4[p->idx].c;
    p->xac = -lbl_3_data_1B9A4[p->idx].d;
    p->c.type = 0;
    CTRLSetTranslation(&p->c, p->xa0, -p->ya4, p->za8);
    CTRLSetRotation(&p->c, 0.0f, p->xac, 0.0f);
    CTRLSetScale(&p->c, lbl_3_rodata_2D50, lbl_3_rodata_2D50, lbl_3_rodata_2D50);
    fn_3_B97DC(p->obj, lbl_3_bss_B154[0]);
    p->obj->setAnimation = 1;
    p->fc0 = 0;
}

#pragma dont_inline on
// .text:0x000F1674 size:0xDC mapped:0x80730708
void fn_3_F1674(s32 arg, s32 hitType, struct _CollisionStruct* hit) {
    u32 stad = g_d_GameSettings.StadiumID;
    u8 v;
    u32 h;
    if (g_d_GameSettings.GameModeSelected == 6) {
        v = lbl_3_data_84B8[10];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + 10];
    }
    h = sndFXStartEx((u16)(((u16*)lbl_3_data_81DC)[stad] + 5), v, 0x3F, 0);
    if (g_d_GameSettings.GameModeSelected == 6) {
        v = lbl_3_data_84B8[11];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + 11];
    }
    sndFXCtrl(h, 0x5B, v);
    fn_3_65A8();
    fn_3_27648();
    g_FieldingLogic._13B = 1;
}

#pragma dont_inline off
// .text:0x000F1750 size:0x154 mapped:0x807307E4
extern f32 fn_800B4A94(void*);
extern const f32 lbl_3_rodata_2E30;
void fn_3_F1750(StadCtlA* p) {
    ActorObject* o = p->obj;
    f32 r;
    f32 x;
    f32 z;
    if (!fn_800B4A94(o->actor)) {
        p->xac = lbl_3_data_1B884[p->idx].v.x;
        p->zb0 = lbl_3_data_1B884[p->idx].v.z;
        z = p->zb0;
        x = p->xac;
        r = -lbl_3_data_1B884[p->idx].pad[0];
        p->xa0 = x;
        p->ya4 = lbl_3_rodata_2E30;
        p->za8 = z;
        p->rb4 = r;
        p->c.type = 0;
        CTRLSetTranslation(&p->c, p->xa0, -p->ya4, p->za8);
        CTRLSetRotation(&p->c, 0.0f, r, 0.0f);
        p->fc1 = 0;
        p->fl90_hi = 1;
        p->obj = (&lbl_8036E548.slots6C->objects[lbl_3_bss_B219[0] + p->idx]);
        p->fc4 = 0;
        p->f99 = 1;
        return;
    }
    AnimateActorBones(o->actor);
}


// .text:0x000F18A4 size:0x98 mapped:0x80730938
void fn_3_F18A4(StaC5Obj* p) {
    ActorObject* o = &lbl_8036E548.slots6C->objects[lbl_3_bss_B218[0]];
    p->actorObj = o;
    o->time = 0.0f;
    o->setTime = 1;
    fn_800B4CA0(((void*)o->actor), o->time);
    p->u.prop.rotY += 180.0;
    AnimateActorBones(((void*)o->actor));
}

#pragma dont_inline on
// .text:0x000F193C size:0x4F0 mapped:0x807309D0
// NONMATCHING 88%: inlines fn_3_F1750, fn_3_F18A4, fn_3_F3A04, fn_3_F22FC; original reaches lbl_3_bss_B218..B21C through the lbl_3_bss_AEE0 pooled base (nmverify flag expected); saved-reg allocation differs
#if NONMATCHING
void fn_3_F193C(StadCtlA* p) {
    VecSrcDst seg;
    CollisionStruct col;
    ActorObject* o = p->obj;
    f32 yaw;
    s8 id;
    u32 r;
    switch ((u8)p->fc1) {
    case 0:
        yaw = *p->yawSrc;
        p->rb4 = yaw;
        p->c.type = 0;
        CTRLSetTranslation(&p->c, p->xa0, -p->ya4, p->za8);
        CTRLSetRotation(&p->c, 0.0f, yaw, 0.0f);
        break;
    case 1:
        if (!p->fl90_hi) {
            p->fl90_hi = 1;
        }
        memcpy(&seg.src, &p->xa0, 0xC);
        seg.src.y *= lbl_3_rodata_2D70;
        fn_3_F2938(p);
        memcpy(&seg.dst, &p->xa0, 0xC);
        seg.dst.y *= lbl_3_rodata_2D70;
        AnimateActorBones(o->actor);
        r = checkCollision(&seg, &col, 0, 0) & 0xF;
        if (r == 2 || r == 5) {
            u32 stad;
            u8 v;
            u32 h;
            p->fc1 = 2;
            fn_3_8B890(lbl_3_data_1B820._000);
            lbl_3_data_1B820._000 = -1;
            stad = g_d_GameSettings.StadiumID;
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[6];
            } else {
                v = lbl_3_data_8404[stad * 0x1E + 6];
            }
            h = sndFXStartEx((u16)(((u16*)lbl_3_data_81DC)[stad] + 3), v, 0x3F, 0);
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[7];
            } else {
                v = lbl_3_data_8404[stad * 0x1E + 7];
            }
            sndFXCtrl(h, 0x5B, v);
            fn_3_F3A04((StaC5Obj*)p);
            fn_3_F18A4((StaC5Obj*)p);
        } else if (g_GameLogic.gameStatus == 2) {
            id = fn_3_F2448((StaC5Obj*)p);
            if (id > -1) {
                fn_3_F22FC((StaC5Obj*)p, id);
            }
        }
        break;
    case 2:
        fn_3_F1750(p);
        break;
    }
}
#endif

// .text:0x000F1E2C size:0x4D0 mapped:0x80730EC0
extern char lbl_3_rodata_2CF4[];
extern const f64 lbl_3_rodata_2E48;
// NONMATCHING 98.8%: saved-register numbering (d/r0/r1/r2, f29/f30) rotated; original reads footprint[0][1]/[1][*] through an addi'd pointer (separate static array)
#if NONMATCHING
void fn_3_F1E2C(StadCtlA* p) {
    VecSrcDst seg;
    CollisionStruct col;
    Vec mid1;
    Vec mid2;
    Vec center;
    Vec k;
    f32 a;
    f32 s;
    f32 c;
    u32 r0;
    u32 r1;
    u32 r2;
    StaC5Data* d;
    d = (StaC5Data*)&lbl_3_data_1B820;
    k = *(Vec*)lbl_3_rodata_2CF4;
    if (p->ya4 > lbl_3_rodata_2D5C) {
        return;
    }
    a = -(lbl_3_rodata_2DDC * p->rb4);
    s = sin(a);
    c = cos(a);
    center.x = lbl_3_rodata_2E48 * (k.x * c + k.z * -s);
    c = cos(a);
    s = sin(a);
    center.z = lbl_3_rodata_2E48 * (k.x * s + k.z * c);
    PSVECAdd(&center, (Vec*)&p->xa0, &center);
    center.y = lbl_3_rodata_2D5C;
    seg.src.x = seg.dst.x = center.x;
    seg.src.z = seg.dst.z = center.z;
    seg.src.y = lbl_3_rodata_2D70;
    seg.dst.y = lbl_3_rodata_2D50;
    r0 = checkCollision(&seg, &col, 0, 0) & 0x7F;
    if (r0 == 10) {
        if (p->fc4 % d->dustRate != 0) {
            p->fc4++;
            return;
        }
        fn_80064430(&seg.src, 1, lbl_3_rodata_2D5C, d->dustScale);
    }
    s = sin(a);
    c = cos(a);
    seg.src.x = d->footprint[0][0] * c + d->footprint[0][1] * -s;
    c = cos(a);
    s = sin(a);
    seg.src.z = d->footprint[0][0] * s + d->footprint[0][1] * c;
    PSVECAdd(&center, &seg.src, &seg.src);
    seg.dst.x = seg.src.x;
    seg.dst.z = seg.src.z;
    seg.src.y = lbl_3_rodata_2D70;
    seg.dst.y = lbl_3_rodata_2D50;
    r1 = checkCollision(&seg, &col, 0, 0) & 0x7F;
    if (r1 == 10) {
        if (p->fc4 % d->dustRate != 0) {
            p->fc4++;
            return;
        }
        fn_80064430(&seg.src, 1, lbl_3_rodata_2D5C, d->dustScale);
    }
    s = sin(a);
    c = cos(a);
    seg.src.x = d->footprint[1][0] * c + d->footprint[1][1] * -s;
    c = cos(a);
    s = sin(a);
    seg.src.z = d->footprint[1][0] * s + d->footprint[1][1] * c;
    PSVECAdd(&center, &seg.src, &seg.src);
    seg.dst.x = seg.src.x;
    seg.dst.z = seg.src.z;
    seg.src.y = lbl_3_rodata_2D70;
    seg.dst.y = lbl_3_rodata_2D50;
    r2 = checkCollision(&seg, &col, 0, 0) & 0x7F;
    if (r2 == 10) {
        if (p->fc4 % d->dustRate != 0) {
            p->fc4++;
            return;
        }
        fn_80064430(&seg.src, 1, lbl_3_rodata_2D5C, d->dustScale);
    }
    if (r0 == 10) {
        /* both use the last probe position still held in seg.src */
        if (r1 == 10) {
            PSVECSubtract(&seg.src, &center, &mid1);
            mid1.x *= lbl_3_rodata_2D54;
            mid1.z *= lbl_3_rodata_2D54;
            PSVECAdd(&mid1, &center, &mid1);
            fn_80064430(&mid1, 1, lbl_3_rodata_2D5C, d->dustScale);
        }
        if (r2 == 10) {
            PSVECSubtract(&seg.src, &center, &mid2);
            mid2.x *= lbl_3_rodata_2D54;
            mid2.z *= lbl_3_rodata_2D54;
            PSVECAdd(&mid2, &center, &mid2);
            fn_80064430(&mid2, 1, lbl_3_rodata_2D5C, d->dustScale);
        }
    }
    p->fc4 += ((r0 | r1 | r2) & 0xA) != 0;
}
#endif

#pragma dont_inline off
// .text:0x000F22FC size:0x14C mapped:0x80731390
extern int fn_3_253A4(s8, s16);
extern s16 fn_3_9FB8C(f32, f32);
#ifndef TARGET_PC
extern u8 lbl_3_bss_B21B;
#endif
#ifndef TARGET_PC
extern u8 lbl_3_bss_B21C;
#endif
extern const f32 lbl_3_rodata_2E40;
extern const f32 lbl_3_rodata_2D54;
typedef struct {
    STADIUM_OBJ_BEGIN
    u8 p0[STADIUM_OBJ_PAD(0xAC)];
    f32 a;
    f32 p1[2];
    f32 b8;
    f32 bc;
    u8 p2;
    s8 c1;
    u8 p3[4];
    u8 c6;
    u8 p4[0xE8 - 0xC7];
    STADIUM_OBJ_END
} StObjE8;
void fn_3_F22FC(StaC5Obj* p, s32 idx) {
    Vec d;
    s8 id = idx;
    InMemFielderType* f = &g_Fielders[id];
    u8* cnt;
    StObjE8* o;
    u32 i;
    PSVECSubtract((Vec*)f, &p->u.walk.pos, &d);
    d.y = lbl_3_rodata_2D5C;
    PSVECNormalize(&d, &d);
    fn_3_253A4(id, (s16)fn_3_9FB8C(d.x, d.z));
    fn_800527C4(&p->u);
    cnt = &f->_216[1];
    for (i = 0; i < lbl_3_bss_B21C; i++) {
        o = (StObjE8*)lbl_3_common_bss_350E4.objs + (lbl_3_bss_B21B + i);
        if (o->c6 == 3 && o->c1 == (s8)idx) {
            o->b8 = lbl_3_rodata_2DDC * (-o->a - lbl_3_rodata_2E40);
            o->c6 = 4;
            o->bc = lbl_3_rodata_2D54;
            (*cnt)--;
        }
    }
}


#pragma dont_inline on
// .text:0x000F2448 size:0x2DC mapped:0x807314DC
extern char lbl_3_rodata_2CEC[];
extern f64 __fabs(f64);
extern const f64 lbl_3_rodata_2E58;
extern const f64 lbl_3_rodata_2E60;
extern const f32 lbl_3_rodata_2D70;
extern const f32 lbl_3_rodata_2E50;
extern void* memset(void*, int, size_t);
typedef struct { u8 b[7]; } Ids7;
s32 fn_3_F2448(StaC5Obj* p) {
    Ids7 ids;
    Vec d;
    Vec buf;
    f32 c;
    f32 s;
    f32 s2;
    f32 k;
    f64 ta;
    f64 tb;
    f32 ax;
    f32 az;
    f32 lim;
    InMemFielderType* f;
    InMemFielderType* fb;
    u32 i;
    ids = *(Ids7*)lbl_3_rodata_2CEC;
    sin(-(lbl_3_rodata_2DDC * p->u.walk.turn));
    cos(-(lbl_3_rodata_2DDC * p->u.walk.turn));
    fb = g_Fielders;
    k = lbl_3_rodata_2D70;
    for (i = 0; i < 7; i++) {
        f = fb + ids.b[i];
        memset(&buf, 0, 0xC);
        fn_8001B728(ids.b[i], 4, &buf);
        buf.y = buf.y * k;
        if (buf.y < p->u.walk.pos.y) {
            lim = f->_16C;
        } else {
            lim = lbl_3_rodata_2E50;
        }
        if (!(lim < __fabs(buf.y - p->u.walk.pos.y)) && f != NULL && f->knockback == 0) {
            u32 stad;
            u8 v;
            u32 h;
            PSVECSubtract((Vec*)f, &p->u.walk.pos, &d);
            c = (f32)cos(-(lbl_3_rodata_2DDC * p->u.walk.turn));
            s = (f32)sin(-(lbl_3_rodata_2DDC * p->u.walk.turn));
            s2 = (f32)sin(-(lbl_3_rodata_2DDC * p->u.walk.turn));
            {
            f32 c2 = (f32)cos(-(lbl_3_rodata_2DDC * p->u.walk.turn));
            ta = __fabs(d.x * c + d.z * s);
            tb = __fabs(d.x * -s2 + d.z * c2);
            }
            ax = ta;
            az = tb;
            if (ax <= lbl_3_rodata_2E58 && az <= lbl_3_rodata_2E60) {
                stad = g_d_GameSettings.StadiumID;
                if (g_d_GameSettings.GameModeSelected == 6) {
                    v = lbl_3_data_84B8[8];
                } else {
                    v = lbl_3_data_8404[stad * 0x1E + 8];
                }
                h = sndFXStartEx((u16)(((u16*)lbl_3_data_81DC)[stad] + 4), v, 0x3F, 0);
                if (g_d_GameSettings.GameModeSelected == 6) {
                    v = lbl_3_data_84B8[9];
                } else {
                    v = lbl_3_data_8404[stad * 0x1E + 9];
                }
                sndFXCtrl(h, 0x5B, v);
                return (s8)ids.b[i];
            }
        }
    }
    return -1;
}

#pragma dont_inline off
// .text:0x000F2724 size:0x214 mapped:0x807317B8
extern f64 __fabs(f64);
extern const f64 lbl_3_rodata_2E58;
extern const f64 lbl_3_rodata_2E60;
void fn_3_F2724(StaC5Obj* p, StaC5Obj* q) {
    Vec d;
    f32 c;
    f32 s;
    f32 s2;
    f32 c2;
    f32 az;
    f32 ax;
    f64 ta;
    f64 tb;
    sin(-(lbl_3_rodata_2DDC * p->u.walk.turn));
    cos(-(lbl_3_rodata_2DDC * p->u.walk.turn));
    PSVECSubtract(&q->u.walk.pos, &p->u.walk.pos, &d);
    d.y = lbl_3_rodata_2D5C;
    c = (f32)cos(-(lbl_3_rodata_2DDC * p->u.walk.turn));
    s = (f32)sin(-(lbl_3_rodata_2DDC * p->u.walk.turn));
    s2 = (f32)sin(-(lbl_3_rodata_2DDC * p->u.walk.turn));
    c2 = (f32)cos(-(lbl_3_rodata_2DDC * p->u.walk.turn));
    ta = __fabs(d.x * c + d.z * s);
    tb = __fabs(d.x * -s2 + d.z * c2);
    ax = ta;
    az = tb;
    if (ax <= lbl_3_rodata_2E58 && az <= lbl_3_rodata_2E60) {
        u32 stad;
        u8 v;
        u32 h;
        q->u.walk.state = 5;
        stad = g_d_GameSettings.StadiumID;
        if (g_d_GameSettings.GameModeSelected == 6) {
            v = lbl_3_data_84B8[0x16];
        } else {
            v = lbl_3_data_8404[stad * 0x1E + 0x16];
        }
        h = sndFXStartEx((u16)(((u16*)lbl_3_data_81DC)[stad] + 0xB), v, 0x3F, 0);
        if (g_d_GameSettings.GameModeSelected == 6) {
            v = lbl_3_data_84B8[0x17];
        } else {
            v = lbl_3_data_8404[stad * 0x1E + 0x17];
        }
        sndFXCtrl(h, 0x5B, v);
    }
}


#pragma dont_inline on
// .text:0x000F2938 size:0x6C4 mapped:0x807319CC
extern f64 pow(f64, f64);
extern char lbl_3_rodata_2CE0[];
extern const f32 lbl_3_rodata_2E68;
extern const f32 lbl_3_rodata_2E6C;
extern const f32 lbl_3_rodata_2E70;
static u32 lbl_3_bss_B244[7];
/* Moves p along the 6th-degree bezier lbl_3_bss_B260 (set up by fn_3_F31E0). */
// NONMATCHING 90%: inlines fn_3_F3A5C and fn_3_F2724; the original reaches lbl_3_bss_B21B/B21C/B244/B260 via the lbl_3_bss_AEE0 pooled base (nmverify flag expected); regalloc differs
#if NONMATCHING
void fn_3_F2938(StadCtlA* p) {
    StaC5Work* w = (StaC5Work*)&lbl_3_bss_AEE0;
    Vec pos;
    Vec d;
    Vec ref;
    StadCtlA* e;
    f32 t;
    f32 u;
    f64 a;
    f64 b;
    f32 ang;
    u32 i;
    t = lbl_3_rodata_2E68 * w->pathSpeed * (f32)w->pathStep;
    ref = *(Vec*)lbl_3_rodata_2CE0;
    u = lbl_3_rodata_2D50 - t;
    for (i = 0; i < 7; i++) {
        b = pow(u, 6 - i);
        a = pow(t, i);
        w->bezW[i] = lbl_3_bss_B244[i] * a * b;
    }
    pos = *(Vec*)&p->xa0;
    pos.x = lbl_3_rodata_2D5C;
    pos.z = lbl_3_rodata_2D5C;
    for (i = 0; i < 7; i++) {
        pos.x += w->bezW[i] * lbl_3_bss_B260[i].x;
        pos.z += w->bezW[i] * lbl_3_bss_B260[i].z;
    }
    pos.y += p->fb8;
    PSVECSubtract(&pos, (Vec*)&p->xa0, &d);
    if (pos.y < lbl_3_rodata_2D5C) {
        pos.y = lbl_3_rodata_2D5C;
        p->fb8 = lbl_3_rodata_2D54 * -p->fb8;
        if (p->fb8 > lbl_3_rodata_2E6C) {
            u32 stad;
            u8 v;
            u32 h;
            stad = g_d_GameSettings.StadiumID;
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[2];
            } else {
                v = lbl_3_data_8404[stad * 0x1E + 2];
            }
            h = sndFXStartEx((u16)(((u16*)lbl_3_data_81DC)[stad] + 1), v, 0x3F, 0);
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[3];
            } else {
                v = lbl_3_data_8404[stad * 0x1E + 3];
            }
            sndFXCtrl(h, 0x5B, v);
        } else if (lbl_3_data_1B820._000 == -1) {
            lbl_3_data_1B820._000 = fn_3_8BBC4(((u16*)lbl_3_data_81DC)[g_d_GameSettings.StadiumID] + 2, &pos.x, &d.x, 3);
        } else {
            fn_3_8BA60(lbl_3_data_1B820._000, &pos.x, &d.x);
        }
    }
    p->fb8 -= lbl_3_rodata_2E70;
    d.y = lbl_3_rodata_2D5C;
    if (PSVECMag(&d) != lbl_3_rodata_2D5C) {
        PSVECNormalize(&d, &d);
        PSVECNormalize(&ref, &ref);
        ang = lbl_3_rodata_2DE8 * (f32)acos(PSVECDotProduct(&d, &ref));
        if (d.x < lbl_3_rodata_2D5C) {
            ang = lbl_3_rodata_2E14 - ang;
        }
    } else {
        ang = -p->rb4;
    }
    fn_3_F3A5C((StaC5Obj*)p, pos.x, pos.y, pos.z, -ang);
    if (p->ya4 < lbl_3_rodata_2D88 && p->fb8 <= lbl_3_rodata_2D5C) {
        for (i = 0; i < lbl_3_bss_B21C; i++) {
            e = (StadCtlA*)((StaC5Obj*)lbl_3_common_bss_350E4.objs + (lbl_3_bss_B21B + i));
            if (e->fc6 < 3) {
                fn_3_F2724((StaC5Obj*)p, (StaC5Obj*)e);
            }
        }
    }
    fn_3_F1E2C(p);
    w->pathStep++;
}
#endif

extern const f32 lbl_3_rodata_2E80;
extern const f32 lbl_3_rodata_2E84;
extern const f32 lbl_3_rodata_2E30;
// .text:0x000F2FFC size:0x1E4 mapped:0x80732090
// NONMATCHING 75%: float scheduling/register order of the bezier control-point stores differs
#if NONMATCHING
void fn_3_F2FFC(StadCtlA* p, f32 x, f32 z) {
    Vec dir;
    s8 side;
    s32 end;
    f32 d = x - p->xac;
    side = d / __fabs(d);
    if (side == 0) {
        d = p->xac;
        side = -(d / __fabs(d));
    }
    dir.x = x - p->xac;
    dir.y = lbl_3_rodata_2D5C;
    dir.z = z - p->zb0;
    PSVECNormalize(&dir, &dir);
    end = side * 80;
    lbl_3_bss_B260[0].x = lbl_3_rodata_2E30 * dir.x + p->xac;
    lbl_3_bss_B260[0].y = lbl_3_rodata_2D5C;
    lbl_3_bss_B260[0].z = lbl_3_rodata_2E30 * dir.z + p->zb0;
    lbl_3_bss_B260[1].x = lbl_3_rodata_2E80 * (x - p->xac) + p->xac;
    lbl_3_bss_B260[1].y = lbl_3_rodata_2D5C;
    lbl_3_bss_B260[1].z = lbl_3_rodata_2E80 * (z - p->zb0) + p->zb0;
    lbl_3_bss_B260[2].x = lbl_3_rodata_2E84 * (x - p->xac) + p->xac;
    lbl_3_bss_B260[2].y = lbl_3_rodata_2D5C;
    lbl_3_bss_B260[2].z = lbl_3_rodata_2E84 * (z - p->zb0) + p->zb0;
    lbl_3_bss_B260[3].x = x;
    lbl_3_bss_B260[3].y = lbl_3_rodata_2D5C;
    lbl_3_bss_B260[3].z = z;
    lbl_3_bss_B260[4].x = x + (end - x) / lbl_3_rodata_2E88;
    lbl_3_bss_B260[4].y = lbl_3_rodata_2D5C;
    lbl_3_bss_B260[4].z = z;
    lbl_3_bss_B260[5].x = x + lbl_3_rodata_2D74 * (end - x) / lbl_3_rodata_2E88;
    lbl_3_bss_B260[5].y = lbl_3_rodata_2D5C;
    lbl_3_bss_B260[5].z = z;
    lbl_3_bss_B260[6].x = end;
    lbl_3_bss_B260[6].y = lbl_3_rodata_2D5C;
    lbl_3_bss_B260[6].z = z;
}
#endif

#pragma dont_inline off
// .text:0x000F31E0 size:0x5DC mapped:0x80732274
extern const f32 lbl_3_rodata_2E8C;
extern const f32 lbl_3_rodata_2EB8;
// NONMATCHING 87%: fn_3_F2FFC (an inline copy, as it is NONMATCHING), fn_3_F42A0 and fn_3_F3A5C are inlined as
// in the original; the inlined code reaches lbl_3_bss_B260/B560 via the lbl_3_bss_AEE0 pooled base there
// (nmverify flag expected), and registers differ
#if NONMATCHING
static inline void fn_3_F2FFC_inline(StadCtlA* p, f32 x, f32 z) {
    Vec dir;
    s8 side;
    s32 end;
    f32 d = x - p->xac;
    side = d / __fabs(d);
    if (side == 0) {
        d = p->xac;
        side = -(d / __fabs(d));
    }
    dir.x = x - p->xac;
    dir.y = lbl_3_rodata_2D5C;
    dir.z = z - p->zb0;
    PSVECNormalize(&dir, &dir);
    end = side * 80;
    lbl_3_bss_B260[0].x = lbl_3_rodata_2E30 * dir.x + p->xac;
    lbl_3_bss_B260[0].y = lbl_3_rodata_2D5C;
    lbl_3_bss_B260[0].z = lbl_3_rodata_2E30 * dir.z + p->zb0;
    lbl_3_bss_B260[1].x = lbl_3_rodata_2E80 * (x - p->xac) + p->xac;
    lbl_3_bss_B260[1].y = lbl_3_rodata_2D5C;
    lbl_3_bss_B260[1].z = lbl_3_rodata_2E80 * (z - p->zb0) + p->zb0;
    lbl_3_bss_B260[2].x = lbl_3_rodata_2E84 * (x - p->xac) + p->xac;
    lbl_3_bss_B260[2].y = lbl_3_rodata_2D5C;
    lbl_3_bss_B260[2].z = lbl_3_rodata_2E84 * (z - p->zb0) + p->zb0;
    lbl_3_bss_B260[3].x = x;
    lbl_3_bss_B260[3].y = lbl_3_rodata_2D5C;
    lbl_3_bss_B260[3].z = z;
    lbl_3_bss_B260[4].x = x + (end - x) / lbl_3_rodata_2E88;
    lbl_3_bss_B260[4].y = lbl_3_rodata_2D5C;
    lbl_3_bss_B260[4].z = z;
    lbl_3_bss_B260[5].x = x + lbl_3_rodata_2D74 * (end - x) / lbl_3_rodata_2E88;
    lbl_3_bss_B260[5].y = lbl_3_rodata_2D5C;
    lbl_3_bss_B260[5].z = z;
    lbl_3_bss_B260[6].x = end;
    lbl_3_bss_B260[6].y = lbl_3_rodata_2D5C;
    lbl_3_bss_B260[6].z = z;
}

void fn_3_F31E0(StadCtlA* p, f32 x, f32 z) {
    StaC5Work* w = (StaC5Work*)&lbl_3_bss_AEE0;
    w->pathSpeed = lbl_3_rodata_2D68;
    p->fb8 = lbl_3_rodata_2E8C;
    fn_3_F2FFC_inline(p, x, z);
    fn_3_F42A0();
    fn_3_F3A5C((StaC5Obj*)p, lbl_3_bss_B260[0].x, lbl_3_rodata_2EB8, lbl_3_bss_B260[0].z, *p->yawSrc);
    w->pathStep = 0;
}
#endif
#pragma dont_inline on

// .text:0x000F37BC size:0x118 mapped:0x80732850
u32 fn_3_F37BC(u32 n, u32 k) {
    u32 r = 1;
    u32 i;
    for (i = 1; i <= k; i++) {
        r = r * (n - i + 1) / i;
    }
    return r;
}

#pragma dont_inline off
// .text:0x000F38D4 size:0x130 mapped:0x80732968
void fn_3_F38D4(void) {
    u32 i;
    for (i = 0; i < 7; i++) {
        lbl_3_bss_B244[i] = binomIn(6, i);
    }
}

// .text:0x000F3A04 size:0x58 mapped:0x80732A98
void fn_3_F3A04(StaC5Obj* p) {
    u32 i;
    u16 n = p->actorObj->actor->totalBones;
    for (i = 0; i < n; i++) {
    }
}

// .text:0x000F3A5C size:0x84 mapped:0x80732AF0
void fn_3_F3A5C(StaC5Obj* p, f32 x, f32 y, f32 z, f32 r) {
    p->u.prop.pos.x = x;
    p->u.prop.pos.y = y;
    p->u.prop.pos.z = z;
    p->u.prop.rotY = r;
    p->c.type = 0;
    CTRLSetTranslation((Control*)p, p->u.prop.pos.x, -p->u.prop.pos.y, p->u.prop.pos.z);
    CTRLSetRotation((Control*)p, 0.0f, r, 0.0f);
}

#pragma dont_inline on
// .text:0x000F3AE0 size:0xD0 mapped:0x80732B74
void fn_3_F3AE0(StaC5Obj* p) {
    f32 rot, x, z;
    p->u.prop._AC = lbl_3_data_1B884[p->idx].v.x;
    p->u.prop._B0 = lbl_3_data_1B884[p->idx].v.z;
    z = p->u.prop._B0;
    x = p->u.prop._AC;
    rot = -lbl_3_data_1B884[p->idx].pad[0];
    p->u.prop.pos.x = x;
    p->u.prop.pos.y = 10.0f;
    p->u.prop.pos.z = z;
    p->u.prop.rotY = rot;
    p->c.type = 0;
    CTRLSetTranslation((Control*)p, p->u.prop.pos.x, -p->u.prop.pos.y, p->u.prop.pos.z);
    CTRLSetRotation((Control*)p, 0.0f, rot, 0.0f);
}

#pragma dont_inline off
// .text:0x000F3BB0 size:0x120 mapped:0x80732C44
void fn_3_F3BB0(StaC5Obj* p) {
#ifdef TARGET_PC // MWCC bit order: f is the top bit (StadiumObj.visible)
    typedef struct { u8 pad[STADIUM_OBJ_PAD(0x90)]; u8 rest : 7; u8 f : 1; } FObj;
#else
    typedef struct { u8 pad[0x90]; u8 f : 1; u8 rest : 7; } FObj;
#endif
    f32 rot, x, z;
    p->u.prop._AC = lbl_3_data_1B884[p->idx].v.x;
    p->u.prop._B0 = lbl_3_data_1B884[p->idx].v.z;
    z = p->u.prop._B0;
    x = p->u.prop._AC;
    rot = -lbl_3_data_1B884[p->idx].pad[0];
    p->u.prop.pos.x = x;
    p->u.prop.pos.y = lbl_3_rodata_2E30;
    p->u.prop.pos.z = z;
    p->u.prop.rotY = rot;
    p->c.type = 0;
    CTRLSetTranslation((Control*)p, p->u.prop.pos.x, -p->u.prop.pos.y, p->u.prop.pos.z);
    CTRLSetRotation((Control*)p, 0.0f, rot, 0.0f);
    p->u.prop._C1 = 0;
    ((FObj*)p)->f = 1;
    p->actorObj = &lbl_8036E548.slots6C->objects[lbl_3_bss_B219[0] + p->idx];
    p->u.prop.state = 0;
    p->f99 = 1;
}

#pragma dont_inline on
// .text:0x000F3CD0 size:0x22C mapped:0x80732D64
extern void fn_80033620(struct Emitter* em);
extern void fn_80033F64(f32, f32, f32);
extern const f64 lbl_3_rodata_2EC0;
extern const f64 lbl_3_rodata_2EC8;
extern const f64 lbl_3_rodata_2ED0;
extern const f32 lbl_3_rodata_2ED8;
extern const f64 lbl_3_rodata_2EE0;
s32 fn_3_F3CD0(struct Emitter* em) {
    Emitter* a = (Emitter*)em;
    Particle* e = a->particles;
    u32 cnt = 0;
    fn_80033620(em);
    do {
        if (e->delay <= 0 && e->life != 0) {
            fn_80033F64(e->sizeX, e->sizeY, e->u.phys.accel.y);
            fn_80033CC8(e, ((void*)a->tex));
            if (-e->delay < 5) {
                e->sizeX = e->sizeX + (e->u.phys.force.x - lbl_3_rodata_2EC0) / lbl_3_rodata_2EC8;
                e->sizeY = e->sizeX;
                e->color.c.a = (s32)(e->color.c.a + lbl_3_rodata_2ED0);
            } else {
                e->sizeX = e->sizeX + (e->u.phys.force.y - e->u.phys.force.x) / lbl_3_rodata_2ED8;
                e->sizeY = e->sizeX;
                e->color.c.a = (s32)(e->color.c.a + lbl_3_rodata_2EE0 / (f64)(0x1EF - e->uvOrder));
                if (e->color.c.a >= 0x3C) {
                    e->color.c.a = 0;
                }
            }
            e->pos.x = e->pos.x + e->u.phys.vel.x;
            e->pos.y = e->pos.y + e->u.phys.vel.y;
            e->pos.z = e->pos.z + e->u.phys.vel.z;
            e->u.phys.accel.y = e->u.phys.accel.x * e->u.phys.accel.z + e->u.phys.accel.y;
            e->life = e->life - 1;
        }
        e->delay = e->delay - 1;
        if (e->life != 0) {
            cnt++;
        }
        e = e->next;
    } while (e != NULL);
    return cnt == 0;
}

#pragma dont_inline off
// .text:0x000F3EFC size:0x3A4 mapped:0x80732F90
#ifndef TARGET_PC
extern u32 lbl_3_bss_B560[];
#endif
extern const f32 lbl_3_rodata_2E90;
extern const f32 lbl_3_rodata_2DEC;
extern const f64 lbl_3_rodata_2DF8;
extern const f64 lbl_3_rodata_2E98;
extern const f64 lbl_3_rodata_2EA0;
extern const f64 lbl_3_rodata_2EA8;
extern const f64 lbl_3_rodata_2EB0;
void fn_3_F3EFC(struct Emitter* em) {
    Emitter* a = (Emitter*)em;
    Particle* e;
    u8 i;
    e = a->particles;
#ifdef TARGET_PC
    a->tex = (TexArchive*)lbl_3_bss_AEE0.file680;
#else
    *(u32*)(&a->tex) = lbl_3_bss_B560[0];
#endif
    i = 0;
    for (; e != NULL; e = e->next) {
        e->sizeX = e->sizeY = lbl_3_rodata_2E30;
        e->u.phys.vel.x = e->u.phys.vel.z = lbl_3_rodata_2D5C;
        e->u.phys.vel.y = lbl_3_rodata_2E90;
        e->pos.x = lbl_3_bss_B260[0].x + (rand() % 600 - 300) / lbl_3_rodata_2E98;
        e->pos.y = lbl_3_rodata_2EA0 + (rand() % 600 - 300) / lbl_3_rodata_2E98;
        e->pos.z = lbl_3_bss_B260[0].z + (rand() % 600 - 300) / lbl_3_rodata_2E98;
        e->u.phys.force.x = lbl_3_rodata_2EA8 + (rand() % 300 - 150) / lbl_3_rodata_2E30;
        e->u.phys.force.y = lbl_3_rodata_2EB0 + (rand() % 300 - 150) / lbl_3_rodata_2E30;
        e->uvOrder = i;
        e->delay = i;
        e->color.c.b = 0xFF;
        e->color.c.g = 0xFF;
        e->color.c.r = 0xFF;
        e->color.c.a = 0;
        e->life = 0x1F4 - e->uvOrder;
        e->u.phys.accel.x = lbl_3_rodata_2DF8 + (rand() % 50) / lbl_3_rodata_2DEC;
        e->u.phys.accel.y = lbl_3_rodata_2D5C;
        e->u.phys.accel.z = 1 - (rand() % 2) * 2;
        e->texIndex = 0xF;
        e->uvFrame = 0;
        i++;
    }
}

// .text:0x000F42A0 size:0x3CC mapped:0x80733334
struct Emitter* fn_80033A24(s32 (*update)(struct Emitter* e), u8 priority, s32 unk14, s32 n, s32 strict, u8 type);
void fn_3_F42A0(void) {
    struct Emitter* e = fn_80033A24(fn_3_F3CD0, 0x80, 0, 8, 1, 0);
    if (e != NULL) {
        fn_3_F3EFC(e);
    }
}

#pragma dont_inline on
// .text:0x000F466C size:0x30 mapped:0x80733700
extern void fn_3_27648(void);

void fn_3_F466C(s32 arg, s32 hitType, struct _CollisionStruct* hit) {
    fn_3_27648();
    g_FieldingLogic._13B = 1;
}

// .text:0x000F469C size:0x4 mapped:0x80733730
void fn_3_F469C(void* arg) {
    return;
}

extern char lbl_3_rodata_2CC8[];
// .text:0x000F46A0 size:0x500 mapped:0x80733734
// NONMATCHING 83%: inlines fn_3_F5C30 (which now inlines fn_3_F3BB0), fn_3_F4C4C, fn_3_F4D00; our float literals from those get pooled through ...rodata.0 and the original reaches lbl_3_data_1B884/lbl_3_bss_B219 via pooled bases (nmverify flag expected); regalloc differs
#if NONMATCHING
void fn_3_F46A0(StadObjB* p) {
    StaC5Data* d = (StaC5Data*)&lbl_3_data_1B820;
    StaC5Work* w = (StaC5Work*)&lbl_3_bss_AEE0;
    Vec dir;
    Vec ref;
    f32 ang;
    ref = *(Vec*)lbl_3_rodata_2CC8;
    dir.x = w->targetX - p->pos.x;
    dir.y = lbl_3_rodata_2D5C;
    dir.z = d->targetZ - p->pos.z;
    PSVECNormalize(&dir, &dir);
    ang = lbl_3_rodata_2DE8 * (f32)acos(PSVECDotProduct(&dir, &ref));
    if (dir.x < lbl_3_rodata_2D5C) {
        ang = lbl_3_rodata_2E14 - ang;
    }
    p->yaw = -ang;
    CTRLSetRotation(&p->c, lbl_3_rodata_2D5C, p->yaw, lbl_3_rodata_2D5C);
    if (g_GameLogic.gameStatus != 3) {
        fn_3_F5C30((StaC5Obj*)p);
        p->update = fn_3_F56CC;
        return;
    }
    fn_3_F193C(p->link);
    switch (p->state) {
    case 0:
        if (w->cartBusy == 0) {
            u32 stad;
            u8 v;
            u32 h;
            fn_3_F31E0(p->link, w->targetX, d->targetZ);
            fn_3_F4C4C((StaC5Obj*)p);
            p->link->fc1 = 1;
            p->state = 3;
            w->cartBusy = 1;
            stad = g_d_GameSettings.StadiumID;
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[0];
            } else {
                v = lbl_3_data_8404[stad * 0x1E + 0];
            }
            h = sndFXStartEx(((u16*)lbl_3_data_81DC)[stad], v, 0x3F, 0);
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[1];
            } else {
                v = lbl_3_data_8404[stad * 0x1E + 1];
            }
            sndFXCtrl(h, 0x5B, v);
        }
        break;
    case 3:
        fn_3_F4D00((StaC5Obj*)p);
        if ((u8)p->link->fc1 == 0) {
            w->cartBusy = 0;
        }
        break;
    }
}
#endif

// .text:0x000F4BA0 size:0xAC mapped:0x80733C34
void fn_3_F4BA0(StaC5Obj* p) {
    Vec tgt;
    Vec d;
    PSVECAdd(&p->u.cart.pos, &p->u.cart.vel, &p->u.cart.pos);
    CTRLSetTranslation((Control*)p, p->u.cart.pos.x, -p->u.cart.pos.y, p->u.cart.pos.z);
    tgt.x = lbl_3_data_1B884[p->idx].v.x;
    tgt.y = lbl_3_data_1B884[p->idx].v.y;
    tgt.z = lbl_3_data_1B884[p->idx].v.z;
    PSVECSubtract(&tgt, &p->u.cart.pos, &d);
    p->u.cart.vel.x = 0.2f * d.x;
    p->u.cart.vel.z = 0.2f * d.z;
}

#pragma dont_inline off
// .text:0x000F4C4C size:0xB4 mapped:0x80733CE0
void fn_3_F4C4C(StaC5Obj* p) {
    f32 a = -p->u.cart.yaw;
    f32 c;
    a = lbl_3_rodata_2DDC * a;
    p->u.cart.vel.x = lbl_3_rodata_2E88 * (f32)sin(a);
    p->u.cart.vel.y = 0.0f;
    c = cos(a);
    p->u.cart.vel.z = lbl_3_rodata_2E88 * -c;
    PSVECScale(&p->u.cart.vel, -1.0f, &p->u.cart.vel);
}

// .text:0x000F4D00 size:0xAC mapped:0x80733D94
void fn_3_F4D00(StaC5Obj* p) {
    Vec d;
    Vec tgt;
    PSVECAdd(&p->u.cart.pos, &p->u.cart.vel, &p->u.cart.pos);
    CTRLSetTranslation((Control*)p, p->u.cart.pos.x, -p->u.cart.pos.y, p->u.cart.pos.z);
    tgt.x = lbl_3_data_1B884[p->idx].v.x;
    tgt.y = lbl_3_data_1B884[p->idx].v.y;
    tgt.z = lbl_3_data_1B884[p->idx].v.z;
    PSVECSubtract(&tgt, &p->u.cart.pos, &d);
    p->u.cart.vel.x = lbl_3_rodata_2EE8 * d.x;
    p->u.cart.vel.z = lbl_3_rodata_2EE8 * d.z;
}

// .text:0x000F4DAC size:0x210 mapped:0x80733E40
extern char lbl_3_rodata_2CBC[];
extern const f32 lbl_3_rodata_2EEC;
extern const f32 lbl_3_rodata_2EF0;
extern const f64 lbl_3_rodata_2EF8;
extern const f32 lbl_3_rodata_2F00;
extern const f32 lbl_3_rodata_2F04;
#ifndef TARGET_PC
extern u8 lbl_3_bss_B21F;
#endif
#ifndef TARGET_PC
extern u8 lbl_3_bss_B220[];
#endif
void fn_3_F4DAC(void) {
    Vec v;
    Vec n;
    Vec ref;
    u8 acc;
    u8 cnt;
    u8 r;
    StaC5Obj* e;
    f32 mag;
    f32 ang;
    f32 t;
    cnt = 0;
    ref = *(Vec*)lbl_3_rodata_2CBC;
    acc = 100 / lbl_3_bss_B220[0];
    v.x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    v.y = lbl_3_rodata_2D5C;
    v.z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
    PSVECNormalize(&v, &n);
    mag = PSVECMag(&v);
    ang = lbl_3_rodata_2DE8 * (f32)acos(PSVECDotProduct(&n, &ref));
    if (ang < lbl_3_rodata_2EEC) {
        r = fn_3_B7F70(100);
        while (r / acc != 0) {
            cnt++;
            acc += 100 / lbl_3_bss_B220[0];
        }
        e = (StaC5Obj*)lbl_3_common_bss_350E4.objs + (cnt + lbl_3_bss_B21F);
    } else if (n.x < lbl_3_rodata_2D5C) {
        e = (StaC5Obj*)lbl_3_common_bss_350E4.objs + lbl_3_bss_B21F;
    } else {
        e = (StaC5Obj*)lbl_3_common_bss_350E4.objs + (lbl_3_bss_B21F + 1);
    }
    t = ang / lbl_3_rodata_2EF0;
    if (!(mag > lbl_3_rodata_2EF8 * (lbl_3_rodata_2DA8 - t) + lbl_3_rodata_2F00 * t)) {
        if (mag > lbl_3_rodata_2F04) {
            e->u.cart.state = 1;
        } else {
            e->u.cart.state = 2;
        }
    }
}

// .text:0x000F4FBC size:0x710 mapped:0x80734050
#pragma dont_inline on
extern char lbl_3_rodata_2CB0[];
extern const f32 lbl_3_rodata_2F08;
extern const f32 lbl_3_rodata_2F0C;
// NONMATCHING 89%: inlines fn_3_F4DAC and fn_3_F4C4C; the original reaches lbl_3_bss_B21F/B220 via the lbl_3_bss_AEE0 pooled base (nmverify flag expected); float/gpr allocation differs
#if NONMATCHING
void fn_3_F4FBC(StadObjB* p) {
    StaC5Work* w = (StaC5Work*)&lbl_3_bss_AEE0;
    Vec d;
    Vec n;
    Vec ref;
    f32 c;
    f32 ang;
    f32 mag;
    ref = *(Vec*)lbl_3_rodata_2CB0;
    if (g_Ball.deadBallReason == 0) {
        d.x = g_Ball.AtBat_Contact_BallPos.x - p->pos.x;
        d.y = lbl_3_rodata_2D5C;
        d.z = g_Ball.AtBat_Contact_BallPos.z - p->pos.z;
        PSVECNormalize(&d, &d);
        c = PSVECDotProduct(&d, &ref);
        if (c > lbl_3_rodata_2D50) {
            c = lbl_3_rodata_2D50;
        } else if (c < lbl_3_rodata_2D70) {
            c = lbl_3_rodata_2D70;
        }
        ang = lbl_3_rodata_2DE8 * (f32)acos(c);
        if (ang > lbl_3_rodata_2F08) {
            ang = lbl_3_rodata_2F08;
        }
        if (d.x < lbl_3_rodata_2D5C) {
            ang = lbl_3_rodata_2E14 - ang;
        }
        p->yaw = -ang;
        CTRLSetRotation(&p->c, lbl_3_rodata_2D5C, p->yaw, lbl_3_rodata_2D5C);
    }
    switch (p->state) {
    case 0:
        if (g_Ball.AtBat_ContactResult < 2) {
            if (w->flag2 == 0) {
                w->flag2 = 1;
                if ((s32)(fn_3_B7F70(100) + 1) > 0x3F) {
                    w->cartBusy = 1;
                }
            }
            if (w->cartBusy == 0) {
                fn_3_F4DAC();
                w->cartBusy = 1;
            }
        }
        break;
    case 1:
        if (g_Ball.physicsSubstruct.velocity.y < lbl_3_rodata_2D5C) {
            u32 stad;
            u8 v;
            u32 h;
            p->link->fc1 = 1;
            fn_3_F4C4C((StaC5Obj*)p);
            p->state = 3;
            d.x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            d.y = lbl_3_rodata_2D5C;
            d.z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
            mag = PSVECMag(&d);
            if (mag > lbl_3_rodata_2F0C) {
                PSVECNormalize(&d, &n);
                PSVECScale(&n, lbl_3_rodata_2F0C, &d);
            }
            if (mag < lbl_3_rodata_2F04) {
                PSVECNormalize(&d, &n);
                PSVECScale(&n, lbl_3_rodata_2F04, &d);
            }
            fn_3_F31E0(p->link, d.x, d.z);
            stad = g_d_GameSettings.StadiumID;
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[0];
            } else {
                v = lbl_3_data_8404[stad * 0x1E + 0];
            }
            h = sndFXStartEx(((u16*)lbl_3_data_81DC)[stad], v, 0x3F, 0);
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[1];
            } else {
                v = lbl_3_data_8404[stad * 0x1E + 1];
            }
            sndFXCtrl(h, 0x5B, v);
        }
        break;
    case 2:
        d.x = g_Ball.AtBat_Contact_BallPos.x;
        d.y = lbl_3_rodata_2D5C;
        d.z = g_Ball.AtBat_Contact_BallPos.z;
        if (g_Ball.AtBat_ContactResult >= 2) {
            p->state = 0;
            break;
        }
        if (PSVECMag(&d) > lbl_3_rodata_2F04) {
            u32 stad;
            u8 v;
            u32 h;
            if (d.z < lbl_3_rodata_2EF0) {
                d.z = lbl_3_rodata_2EF0;
            }
            fn_3_F31E0(p->link, d.x, d.z);
            fn_3_F4C4C((StaC5Obj*)p);
            p->link->fc1 = 1;
            p->state = 3;
            stad = g_d_GameSettings.StadiumID;
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[0];
            } else {
                v = lbl_3_data_8404[stad * 0x1E + 0];
            }
            h = sndFXStartEx(((u16*)lbl_3_data_81DC)[stad], v, 0x3F, 0);
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[1];
            } else {
                v = lbl_3_data_8404[stad * 0x1E + 1];
            }
            sndFXCtrl(h, 0x5B, v);
        }
        break;
    }
}
#endif

// .text:0x000F56CC size:0x564 mapped:0x80734760
// NONMATCHING 97%: inlines fn_3_F5C30 (+fn_3_F3BB0) twice and fn_3_F4D00; saved-register numbering of the two table-column pointers differs; original reaches lbl_3_bss_B219 via the lbl_3_bss_AEE0 pooled base (nmverify flag expected)
#if NONMATCHING
void fn_3_F56CC(StadObjB* p) {
    StaC5Work* w = (StaC5Work*)&lbl_3_bss_AEE0;
    if (g_d_GameSettings.GameModeSelected == 7) {
        return;
    }
    if (g_GameLogic.gameStatus == 3) {
        fn_3_F5C30((StaC5Obj*)p);
        p->update = fn_3_F46A0;
    } else if (g_GameLogic.gameStatus != 2) {
        if (g_GameLogic.gameStatus == 0) {
            fn_3_F5C30((StaC5Obj*)p);
        }
        if (w->cartBusy != 0) {
            w->cartBusy = 0;
        }
        if (w->flag2 != 0) {
            w->flag2 = 0;
        }
    } else {
        if (p->f99 != 0) {
            p->f99 = 0;
        }
        if (p->link != NULL) {
            fn_3_F193C(p->link);
        }
        switch (p->state) {
        case 0:
        case 1:
        case 2:
            fn_3_F4FBC(p);
            break;
        case 3:
            fn_3_F4D00((StaC5Obj*)p);
            break;
        }
    }
}
#endif

#pragma dont_inline off
// .text:0x000F5C30 size:0x248 mapped:0x80734CC4
void fn_3_F5C30(StaC5Obj* p) {
    p->u.cart.pos.x = lbl_3_data_1B884[p->idx].v.x;
    p->u.cart.pos.y = lbl_3_data_1B884[p->idx].v.y;
    p->u.cart.pos.z = lbl_3_data_1B884[p->idx].v.z;
    p->u.cart.yaw = -lbl_3_data_1B884[p->idx].pad[0];
    p->c.type = 0;
    CTRLSetTranslation((Control*)p, p->u.cart.pos.x, -p->u.cart.pos.y, p->u.cart.pos.z);
    CTRLSetRotation((Control*)p, 0.0f, p->u.cart.yaw, 0.0f);
    p->u.cart.vel.z = lbl_3_rodata_2D5C;
    p->u.cart.vel.y = lbl_3_rodata_2D5C;
    p->u.cart.vel.x = lbl_3_rodata_2D5C;
    if (p->u.cart.emitter != NULL) {
        if (p->u.cart.emitter->update != NULL) {
            fn_80033964(p->u.cart.emitter);
            p->u.cart.emitter = NULL;
        } else {
            p->u.cart.emitter = NULL;
        }
    }
    if (p->u.cart.link != NULL) {
        fn_3_F3BB0((StaC5Obj*)p->u.cart.link);
    }
    p->f99 = 1;
    p->u.cart.state = 0;
    if (lbl_3_data_1B820._000 != -1) {
        fn_3_8B890(lbl_3_data_1B820._000);
        lbl_3_data_1B820._000 = -1;
    }
}

#pragma dont_inline off
// .text:0x000F5E78 size:0x84 mapped:0x80734F0C
s32 fn_3_F5E78(u8 id) {
    u32 n = (u32)lbl_3_common_bss_350E4.count;
    struct SortEnt* e = lbl_3_common_bss_350E4.sort + n;
    for (; n != 0; e--, n--) {
        if (id == e[-1].idx) {
            return n - 1;
        }
    }
    OSPanic(lbl_3_rodata_2DB8, 0x637, lbl_3_rodata_2F10);
    return 0;
}

// .text:0x000F5EFC size:0x2C mapped:0x80734F90
s32 fn_3_F5EFC(u32* a, u32* b) {
    if (*a < *b) {
        return -1;
    }
    return *a > *b;
}

// .text:0x000F5F28 size:0x24 mapped:0x80734FBC
s32 fn_3_F5F28(f32* a, f32* b) {
    f32 x = *a;
    f32 y = *b;
    if (x < y) {
        return -1;
    }
    return x > y;
}

// .text:0x000F5F4C size:0x138 mapped:0x80734FE0
void fn_3_F5F4C(Mtx m) {
    extern const f32 lbl_3_rodata_2E30, lbl_3_rodata_2F2C, lbl_3_rodata_2F30, lbl_3_rodata_2F34;
    Vec v;
    StadiumObjList* g;
    s32 off;
    u32 i;
    memcpy(&v, &g_Ball, 0xC);
    PSMTXMultVec(m, &v, &v);
    g = &lbl_3_common_bss_350E4;
    for (i = 0, off = 0; i < (u32)g->count; off += sizeof(struct SortEnt), i++) {
        struct SortEnt* e = (struct SortEnt*)((u8*)g->sort + off);
        StaC5Obj* o = (StaC5Obj*)g->objs + e->idx;
        if ((o->flags >> 7) & 1) {
            if (o->kind == 1) {
                e->z = lbl_3_rodata_2D50;
            } else {
                f32 d = e->z;
                f32 lo = lbl_3_rodata_2D74 + v.z;
                if (d < lo) {
                    e->z = lbl_3_rodata_2D50;
                } else if (d > lbl_3_rodata_2E30 + v.z) {
                    e->z = lbl_3_rodata_2F2C;
                } else {
                    { f32 t = d - lo; e->z = lbl_3_rodata_2DA8 - lbl_3_rodata_2F30 * (t * lbl_3_rodata_2F34); }
                }
            }
        }
    }
}

// .text:0x000F6084 size:0x480 mapped:0x80735118
extern const f32 lbl_3_rodata_2F38;
extern void* fn_800ACF34(s32 align, s32 size);
extern void fn_800ACF14(void* block);
extern void fn_800C07BC(void* base, void* tmp, u32 count, u32 size, s32 (*compare)(const void*, const void*)); // main/file_800BDEA0.h
// NONMATCHING 91%: inlines fn_3_F5E78 x2 and fn_3_F5F4C; register allocation differs. The original checks kind==4 through a stale register (the Mtx argument on the first iteration); this reads it from the current object
#if NONMATCHING
void fn_3_F6084(MtxPtr view, struct SortEnt* out) {
    StadiumObjList* list = (StadiumObjList*)&lbl_3_common_bss_350E4;
    StadObjHdr* objs;
    StadObjHdr* e;
    struct SortEnt* front;
    struct SortEnt* back;
    struct SortEnt* o;
    struct SortEnt t;
    Vec v;
    s32 i;
    s32 n;
    s32 start;
    u32 a;
    u32 b;
    void* tmp;
    if (list->depthSort != 0) {
        /* hidden objects first */
        o = out;
        n = 0;
        i = list->count - 1;
        e = (StadObjHdr*)list->objs + i;
        do {
            if (!e->visible) {
                o->z = lbl_3_rodata_2F38;
                n++;
                o->idx = i;
                o++;
            }
            e--;
        } while (i-- != 0);
        /* then unsorted visible ones, depth-sorted ones fill from the back */
        i = list->count - 1;
        front = out + n;
        start = i;
        back = out + i;
        e = (StadObjHdr*)list->objs + i;
        do {
            if (e->visible) {
                /* the original reads kind through a stale pointer on the first iteration */
                if (e->kind == 4) {
                    out[list->count - 1].z = lbl_3_rodata_2D70;
                    out[list->count - 1].idx = i;
                } else if (e->depthSort) {
                    CTRLGetTranslation(&e->c, &v.x, &v.y, &v.z);
                    PSMTXMultVec(view, &v, &v);
                    start--;
                    back[-1].z = v.z;
                    back[-1].idx = i;
                    back--;
                } else {
                    front->z = lbl_3_rodata_2F38;
                    front->idx = i;
                    front++;
                }
            }
            e--;
        } while (i-- != 0);
        tmp = fn_800ACF34(0x20, (list->count - start) * 8);
        fn_800C07BC(out + start, tmp, list->count - start, 8, (s32 (*)(const void*, const void*))fn_3_F5F28);
        fn_800ACF14(tmp);
        /* keep each paired object drawn before its partner */
        for (i = 0; i < lbl_3_bss_B220[0]; i++) {
            e = (StadObjHdr*)list->objs + (lbl_3_bss_B21F + i);
            a = fn_3_F5E78(e->id);
            b = fn_3_F5E78(e->link->id);
            if (a > b) {
                t = out[a];
                out[a] = out[b];
                out[b] = t;
            }
        }
        fn_3_F5F4C(view);
    } else {
        objs = (StadObjHdr*)list->objs;
        o = out;
        for (i = 0; i < list->count; i++) {
            /* the original never advances objs here */
            CTRLGetTranslation(&objs->c, &v.x, &v.y, &v.z);
            o->z = lbl_3_rodata_2D50;
            o->idx = i;
            o++;
        }
    }
}
#endif

#pragma dont_inline on
// .text:0x000F6504 size:0xC4 mapped:0x80735598
void* fn_3_F6504(s32 idx, Mtx arg) {
    StaC5Obj* c = (StaC5Obj*)lbl_3_common_bss_350E4.objs + idx;
    u8 t = c->kind;
    void* m = arg;
    if (t == 2) {
        if (c->u.walk.state < 3 && g_Ball.ballState != 1) {
            CTRLBuildMatrix((Control*)c, m);
        } else {
            return 0;
        }
    } else if (t == 0) {
        if (c->u.prop._C1 == 2) return 0;
        if (g_Ball.AtBat_ContactResult >= 2) return 0;
        CTRLBuildMatrix((Control*)c, m);
    } else {
        CTRLBuildMatrix((Control*)c, m);
    }
    return lbl_3_common_bss_350E4.objs[idx].shadow /* common header */;
}

// .text:0x000F65C8 size:0x100 mapped:0x8073565C
void fn_3_F65C8(s32* n) {
    struct { Control c; u8 pad[0x14]; } c;
    Mtx m;
    u16 k;
    StaC5Obj* so = &((StaC5Obj*)lbl_3_common_bss_350E4.objs)[lbl_3_bss_B21A];
    void* o;
    k = lbl_3_common_bss_350E4.groupStart[*n - 1] + lbl_3_common_bss_350E4.groupCount[*n - 1];
    lbl_3_common_bss_350E4.groupStart[*n] = k;
    lbl_3_common_bss_350E4.groupObjs[k] = lbl_3_bss_B21A;
    lbl_3_common_bss_350E4.groupCount[*n]++;
    o = so->shadow;
    c.c.type = 0;
    CTRLBuildMatrix(&c.c, m);
    fn_3_B8464(m, o);
    fn_3_B8414(&lbl_3_common_bss_350E4.groupBounds[*n * 2], &lbl_3_common_bss_350E4.groupBounds[*n * 2 + 1]);
    (*n)++;
}

// .text:0x000F66C8 size:0x270 mapped:0x8073575C
// 97.9%: points 2/3 of the bounding-box scan use lfsu (pt++); original does `addi r4,r3,8k` + `lfs 8k(r3)` and keeps e in r3
typedef struct { f32 x, z; } P2;
void fn_3_F66C8(s32* n) {
    struct { Control c; u8 pad[0x14]; } c;
    Mtx m;
    s32 i;
    u16 k;
    s32 idx;
    void* o;
    f32* e;
    P2* pt;
    s32 j;
    StaC5Obj* oe;
    f32 xmin;
    f32 zmin;
    f32 xmax;
    f32 zmax;
    f32 t;
    extern f32 lbl_3_rodata_2F3C[];
    fn_3_B8574();
    for (i = 0; i < lbl_3_bss_B21C; i++) {
        k = lbl_3_common_bss_350E4.groupStart[*n - 1] + lbl_3_common_bss_350E4.groupCount[*n - 1];
        lbl_3_common_bss_350E4.groupStart[*n] = k;
        idx = lbl_3_bss_B21B + i;
        lbl_3_common_bss_350E4.groupObjs[k] = idx;
        lbl_3_common_bss_350E4.groupCount[*n]++;
        oe = (StaC5Obj*)lbl_3_common_bss_350E4.objs;
        oe += idx;
        e = (f32*)(lbl_3_data_1B824 + oe->idx * 32);
        xmin = xmax = e[0];
        zmin = zmax = e[1];
        pt = (P2*)e;
        for (j = 1; j < 4; j++) {
            pt = (P2*)e;
            pt += j;
            t = pt->x;
            if (xmin > t) xmin = t; else if (xmax < t) xmax = t;
            t = pt->z;
            if (zmin > t) zmin = t; else if (zmax < t) zmax = t;
        }
        o = lbl_3_common_bss_350E4.objs[lbl_3_bss_B21B].shadow /* common header */;
        CTRLSetTranslation(&c.c, xmin, ((f32*)&lbl_3_rodata_2D5C)[0], zmax);
        CTRLBuildMatrix(&c.c, m);
        fn_3_B8464(m, o);
        CTRLSetTranslation(&c.c, xmax, lbl_3_rodata_2F3C[0], zmin);
        CTRLBuildMatrix(&c.c, m);
        fn_3_B8464(m, o);
        fn_3_B8414(&lbl_3_common_bss_350E4.groupBounds[*n * 2], &lbl_3_common_bss_350E4.groupBounds[*n * 2 + 1]);
        (*n)++;
        fn_3_B8574();
    }
}

// .text:0x000F6938 size:0x15C mapped:0x807359CC
#pragma dont_inline off
void fn_3_F6938(s32* n) {
    struct { Control c; u8 pad[0x8]; } c;
    Mtx m;
    s32 i;
    s32 idx;
    u16 k;
    StaC5Obj* e;
    void* o;
#ifndef TARGET_PC
    extern u8 lbl_3_bss_B21F;
#endif
#ifndef TARGET_PC
    extern u8 lbl_3_bss_B220[];
#endif
    extern f32 lbl_3_rodata_2F40[];
    for (i = 0; i < lbl_3_bss_B220[0]; i++) {
        k = lbl_3_common_bss_350E4.groupStart[*n - 1] + lbl_3_common_bss_350E4.groupCount[*n - 1];
        lbl_3_common_bss_350E4.groupStart[*n] = k;
        idx = lbl_3_bss_B21F + i;
        lbl_3_common_bss_350E4.groupObjs[k] = idx;
        lbl_3_common_bss_350E4.groupCount[*n]++;
        e = (StaC5Obj*)lbl_3_common_bss_350E4.objs + idx;
        o = e->shadow;
        c.c.type = 0;
        CTRLSetTranslation(&c.c, lbl_3_data_1B884[e->idx].v.x, -lbl_3_data_1B884[e->idx].v.y, lbl_3_data_1B884[e->idx].v.z);
        CTRLSetScale(&c.c, lbl_3_rodata_2F40[0], lbl_3_rodata_2F40[0], lbl_3_rodata_2F40[0]);
        CTRLBuildMatrix(&c.c, m);
        fn_3_B8574();
        fn_3_B8464(m, o);
        fn_3_B8414(&lbl_3_common_bss_350E4.groupBounds[*n * 2], &lbl_3_common_bss_350E4.groupBounds[*n * 2 + 1]);
        (*n)++;
    }
}

// .text:0x000F6A94 size:0x1CC mapped:0x80735B28
void fn_3_F6A94(s32* n) {
    struct { Control c; u8 pad[4]; } c;
    Mtx m;
    s32 i;
    u16 k;
    u32 off;
    void* o;
#ifndef TARGET_PC
    extern u8 lbl_3_bss_B21D[];
#endif
#ifndef TARGET_PC
    extern u8 lbl_3_bss_B21E[];
#endif
    extern f32 lbl_3_rodata_2F44[];
    extern f32 lbl_3_rodata_2F48[];
    extern f32 lbl_3_rodata_2F4C[];
    extern f32 lbl_3_rodata_2F50[];
    extern f32 lbl_3_rodata_2F54[];
    k = lbl_3_common_bss_350E4.groupStart[*n - 1] + lbl_3_common_bss_350E4.groupCount[*n - 1];
    lbl_3_common_bss_350E4.groupStart[*n] = k;
    off = k * 4;
    for (i = 0; i < lbl_3_bss_B21E[0]; i++) {
        *(s32*)((u8*)lbl_3_common_bss_350E4.groupObjs + off) = lbl_3_bss_B21D[0] + i;
        off += sizeof(s32);
        lbl_3_common_bss_350E4.groupCount[*n]++;
    }
    fn_3_B8574();
    o = lbl_3_common_bss_350E4.objs[lbl_3_bss_B21D[0]].shadow /* common header */;
    c.c.type = 0;
    CTRLSetTranslation(&c.c, lbl_3_rodata_2F44[0], ((f32*)&lbl_3_rodata_2D5C)[0], lbl_3_rodata_2F48[0]);
    CTRLBuildMatrix(&c.c, m);
    fn_3_B8464(m, o);
    c.c.type = 0;
    CTRLSetTranslation(&c.c, lbl_3_rodata_2F4C[0], lbl_3_rodata_2F50[0], lbl_3_rodata_2F54[0]);
    CTRLBuildMatrix(&c.c, m);
    fn_3_B8464(m, o);
    if (lbl_3_common_bss_350E4.groupCount[*n] != 0) {
        fn_3_B8414(&lbl_3_common_bss_350E4.groupBounds[*n * 2], &lbl_3_common_bss_350E4.groupBounds[*n * 2 + 1]);
        (*n)++;
    }
}

#pragma dont_inline on
// .text:0x000F6C60 size:0x36C mapped:0x80735CF4
extern void* _OSAllocFromHeap(s32 align, s32 size);
// NONMATCHING 78%: fn_3_F6A94/fn_3_F6938 are inlined; the original reaches lbl_3_bss_B21C..B220 through the lbl_3_bss_AEE0 pooled base (nmverify flag expected), regalloc differs
#if NONMATCHING
void fn_3_F6C60(void) {
    StadiumObjList* list = (StadiumObjList*)&lbl_3_common_bss_350E4;
    s32 n;
    s32 size;
    size = list->count * 2 + list->count * 4 + list->count * 0x18 + list->count * 4;
    if (list->groupBounds == NULL) {
        list->groupBounds = _OSAllocFromHeap(4, size);
        list->groupCount = (u32*)(list->groupBounds + list->count * 2);
        list->groupObjs = (s32*)(list->groupCount + list->count);
        list->groupStart = (u16*)(list->groupObjs + list->count);
    }
    memset(list->groupBounds, 0, size);
    n = 0;
    if (lbl_3_bss_AEE0.b21E != 0) {
        fn_3_F6A94(&n);
    }
    if (lbl_3_bss_AEE0.b220 != 0) {
        fn_3_F6938(&n);
    }
    if (lbl_3_bss_AEE0.b21C != 0) {
        fn_3_F66C8(&n);
    }
    list->numGroups = n;
}
#endif

// .text:0x000F6FCC size:0x10 mapped:0x80736060
#ifndef TARGET_PC
extern u8 lbl_3_bss_AEE8;
#endif

void fn_3_F6FCC(void) {
    lbl_3_bss_AEE8 = 1;
}

// .text:0x000F6FDC size:0x1468 mapped:0x80736070
/* Placement tables (lbl_3_data_1B884 / lbl_3_data_1B9A4); type 6 ends a list. */
#define STA_ACTORS (lbl_8036E548.slots6C)
extern void fn_3_B939C(void);
extern void fn_3_B9D68(u8* ids, s32 n, void** files, s32* out);
extern void fn_3_B97C8(void* fn);
extern void fn_3_B98E8(void* p);
extern void fn_800B4AFC(GameActor* actor, u8 loop);
extern void fn_800BD548(ActorObject* obj, u8 numLights, ...);
extern void* fn_800B0A5C_insertQueue(void* draw, s32 priority); // main/file_800B0724.h has u16 priority; this unit's callers were compiled with s32
extern const f32 lbl_3_rodata_2F58;
extern const f32 lbl_3_rodata_2F5C;
extern const f32 lbl_3_rodata_2F60;
extern const f32 lbl_3_rodata_2F64;
// Stadium setup: loads the actors/animations from `files`, lays out the object
// slots (group A, B and C from the placement tables, then 3 fixed ones) and
// starts the stadium tasks.
// NONMATCHING 81%: inlines fn_3_F3BB0, fn_3_F38D4, fn_3_F5C30, fn_3_F1518 and fn_3_EECF4; the original reaches the placement tables, lbl_3_bss_B154/B219/B244 via the lbl_3_data_1B820 / lbl_3_bss_AEE0 pooled bases (nmverify flag expected); regalloc and scheduling differ
#if NONMATCHING
void fn_3_F6FDC(void** files) {
    StadiumObjList* list = (StadiumObjList*)&lbl_3_common_bss_350E4;
    StaC5Data* d = (StaC5Data*)&lbl_3_data_1B820;
    StaC5Work* w = &lbl_3_bss_AEE0;
    StaPlace14* pa = (StaPlace14*)(&lbl_3_data_1B820.placesA[0]);
    StaPlace14* pc = (StaPlace14*)(&lbl_3_data_1B820.placesC[0]);
    StaPlace18* pb = (StaPlace18*)(&lbl_3_data_1B820.placesB[0]);
    StadObjHdr* o;
    s32* idx;
    s32 nA;
    s32 nB;
    u8 nActors;
    s32 i;
    s32 j;
    s32 k;
    u8 kA;   /* first group-A actor after the per-group ones */
    u8 kBall;
    u8 kB;
    u8 kEnd;
    u8 stop;
    u8 n;
    list->draw = fn_3_B939C;
    list->update = fn_3_EDFAC;
    n = 0;
    stop = 0;
    w->sfxStopped = 1;
    if (g_d_GameSettings.GameModeSelected != 7) {
        fn_3_B97C8(fn_3_F6FCC);
    }
    w->_008 = 0;
    idx = _OSAllocFromHeap(4, 0x48);
    list->fileIdx = (u32*)idx;
    fn_3_B9D68(&lbl_3_data_1B820.pad214[0], 0x12, files, idx);
    w->file680 = STADIUM_FILE(files, 0);

    for (nA = 0; nA < 5; nA++) {
        if (pc[nA].type == 6) {
            break;
        }
    }
    for (nB = 0; nB < 5; nB++) {
        if (pb[nB].type == 6) {
            break;
        }
    }
    nActors = (u8)(nA + 2 + nB) + 4;
    STA_ACTORS = ActorObjectInitTable(nActors);
    list->numActorObjs = nActors;
    w->b219 = 0;
    k = 0;
    for (i = 0; i < (u8)nA; i++, k++) {
        fn_800BDC88(STA_ACTORS, (u8)k, (u8)k, STADIUM_FILE(files, idx[1]), NULL, NULL);
        fn_3_B97DC(&STA_ACTORS->objects[(u8)k], STADIUM_FILE(files, idx[1] + 2));
    }
    w->b218 = k;
    kA = k;
    fn_800BDC88(STA_ACTORS, (u8)k, (u8)k, STADIUM_FILE(files, idx[2]), NULL, NULL);
    fn_3_B97DC(&STA_ACTORS->objects[(u8)k], STADIUM_FILE(files, idx[2] + 2));
    STA_ACTORS->objects[(u8)k].visFlags = 2;
    fn_800B4AFC(STA_ACTORS->objects[(u8)k].actor, STA_ACTORS->objects[(u8)k].visFlags & 1);
    kBall = k + 1;
    fn_800BDC88(STA_ACTORS, kBall, kBall, STADIUM_FILE(files, idx[3]), NULL, NULL);
    k += 2;
    kB = k;
    for (i = 0; i < (u8)nB; i++, k++) {
        fn_800BDC88(STA_ACTORS, (u8)k, (u8)k, STADIUM_FILE(files, idx[4]), NULL, STADIUM_FILE(files, idx[4] + 2));
        fn_3_B98E8(&STA_ACTORS->objects[(u8)k]);
    }
    kEnd = k;
    fn_800BDC88(STA_ACTORS, kEnd, kEnd, STADIUM_FILE(files, idx[5]), NULL, NULL);
    fn_800BDC88(STA_ACTORS, (u8)(kEnd + 1), (u8)(kEnd + 1), STADIUM_FILE(files, idx[6]), NULL, NULL);
    fn_800BDC88(STA_ACTORS, (u8)(kEnd + 2), (u8)(kEnd + 2), STADIUM_FILE(files, idx[7]), NULL, NULL);
    w->actor67C = &STA_ACTORS->objects[(u8)(kEnd + 2)];
    fn_800BDC88(STA_ACTORS, (u8)(kEnd + 3), (u8)(kEnd + 3), STADIUM_FILE(files, idx[8]), NULL, NULL);
    lbl_3_bss_B154[0] = STADIUM_FILE(files, idx[0x10]);
    lbl_3_bss_B154[1] = STADIUM_FILE(files, idx[0x11]);
    for (i = 0; i < nActors; i++) {
        fn_800BD548(&STA_ACTORS->objects[i], 4, list->lights[0], list->lights[1], list->lights[2], list->lights[3]);
    }
    fn_80025DDC(STADIUM_FILE(files, idx[14]));
    fn_80025C58(STADIUM_FILE(files, idx[14]), (ShapeModel**)&STA_ACTORS->objects[(u8)(kEnd + 1)]);
    w->anim2DC.set = STADIUM_FILE(files, idx[15]);
    fn_80025FFC(STADIUM_FILE(files, idx[14]), &w->anim2DC);
    fn_80025EEC(&w->anim2DC, 0, 0);
    w->anim2DC.state.speed = lbl_3_rodata_2F58;
    fn_80025DDC(STADIUM_FILE(files, idx[12]));
    fn_80025C58(STADIUM_FILE(files, idx[12]), (ShapeModel**)&STA_ACTORS->objects[kEnd]);
    w->anim280.set = STADIUM_FILE(files, idx[13]);
    fn_80025FFC(STADIUM_FILE(files, idx[12]), &w->anim280);
    fn_80025EEC(&w->anim280, 0, 0);

    list->count = 0x19;
#ifdef PORT_LP64
    /* 25 stadium objects (0x16A8 = 25 * 0xE8 on GameCube) at the PC stride */
    list->objs = _OSAllocFromHeap(0x20, 25 * STADIUM_OBJ_SIZE);
    memset(list->objs, 0, 25 * STADIUM_OBJ_SIZE);
    list->objsBackup = _OSAllocFromHeap(0x20, 25 * STADIUM_OBJ_SIZE);
    memset(list->objsBackup, 0, 25 * STADIUM_OBJ_SIZE);
#else
    list->objs = _OSAllocFromHeap(0x20, 0x16A8);
    memset(list->objs, 0, 0x16A8);
    list->objsBackup = _OSAllocFromHeap(0x20, 0x16A8);
    memset(list->objsBackup, 0, 0x16A8);
#endif
    o = (StadObjHdr*)list->objs;

    /* group A: StadCtlA objects waiting at their spot */
    if (g_d_GameSettings.GameModeSelected != 7) {
        w->b21D = 0;
        for (j = 0; j < 5; j++) {
            StadCtlA* p = (StadCtlA*)o;
            if (pa[j].type == 6 || pc[j].type != 0) {
                break;
            }
            o->kind = 0;
            o->actorObj = &STA_ACTORS->objects[j];
            p->fc2 = j;
            p->fc3 = kA;
            o->shadow = STADIUM_FILE(files, idx[9]);
            o->update = NULL;
            o->onHit = fn_3_F1674;
            o->hasShadow = (o->visible && o->shadow != NULL) ? 1 : 0;
            p->idx = j;
            p->fc5 = n;
#ifdef PORT_LP64
            ((StadObjHdr*)p)->id = n; /* StadObjHdr.id is not fc5 on PC */
#endif
            fn_3_F3BB0((StaC5Obj*)p);
            n++;
            o->depthSort = 1;
            o->alpha = 0xFF;
            o->drawArg = NULL;
            o->preDraw = NULL;
            o->attached = 0;
            o->attachJoint = -1;
            o->layer = 1;
            o->castShadow = 1;
            o++;
            w->b21E++;
        }
        fn_3_F38D4();
    }

    /* group B: StadObjB objects, each carrying the matching group-A object */
    w->b21F = n;
    for (j = 0; j < 5; j++) {
        StadObjB* b = (StadObjB*)o;
        if (pa[j].type == 6) {
            stop = 1;
        }
        if (stop) {
            for (; j < 5; j++) {
                pa[j].type = 6;
            }
            break;
        }
        o->kind = 1;
        b->idx = j;
        o->id = n;
        if (g_d_GameSettings.GameModeSelected == 7) {
            b->link = NULL;
        } else {
            b->link = (StadCtlA*)((StadObjHdr*)list->objs + (w->b21D + j));
            b->link->yawSrc = &b->yaw;
        }
        b->state = 0;
        o->actorObj = &STA_ACTORS->objects[kBall];
        o->shadow = STADIUM_FILE(files, idx[10]);
        o->update = (void (*)(void*))fn_3_F56CC;
        o->onHit = fn_3_F466C;
        o->visible = 1;
        o->hasShadow = (o->visible && o->shadow != NULL) ? 1 : 0;
        fn_3_F5C30((StaC5Obj*)b);
        n++;
        o->depthSort = 1;
        o->alpha = 0xFF;
        o->drawArg = NULL;
        o->preDraw = (void (*)(void*))fn_3_F469C;
        o->attached = 0;
        o->attachJoint = -1;
        o->layer = 1;
        o++;
        w->b220++;
    }

    /* group C: StadCtlA objects roaming their box */
    stop = 0;
    if (g_d_GameSettings.GameModeSelected != 7) {
        w->b21B = n;
        for (j = 0; j < 5; j++) {
            StadCtlA* p = (StadCtlA*)o;
            if (pb[j].type == 6) {
                stop = 1;
            }
            if (stop) {
                for (; j < 6; j++) {
                    pb[j].type = 6;
                    pb[j].f12 = 0xFF;
                }
                break;
            }
            o->kind = 2;
            o->actorObj = &STA_ACTORS->objects[kB + j];
            o->shadow = STADIUM_FILE(files, idx[11]);
            o->update = (void (*)(void*))fn_3_F0FA4;
            o->onHit = fn_3_EEFD4;
            o->visible = 1;
            o->hasShadow = (o->visible && o->shadow != NULL) ? 1 : 0;
            p->idx = j;
            fn_3_F1518(p);
            n++;
            o->depthSort = 1;
            o->alpha = 0xFF;
            o->drawArg = NULL;
            o->preDraw = NULL;
            o->attached = 0;
            o->attachJoint = -1;
            o->layer = 1;
            o++;
            w->b21C++;
        }
        fn_800B0A5C_insertQueue(fn_3_F0184, 0x6001);
    }

    /* fixed objects */
    o[0].kind = 3;
    o[0].actorObj = &STA_ACTORS->objects[kEnd];
    o[0].shadow = NULL;
    o[0].update = NULL;
    o[0].onHit = NULL;
    o[0].visible = 1;
    o[0].hasShadow = (o[0].visible && o[0].shadow != NULL) ? 1 : 0;
    o[0].c.type = 0;
    CTRLSetTranslation(&o[0].c, lbl_3_rodata_2D5C, lbl_3_rodata_2F5C, lbl_3_rodata_2D5C);
    CTRLSetRotation(&o[0].c, lbl_3_rodata_2D5C, lbl_3_rodata_2D5C, lbl_3_rodata_2D5C);
    o[0].depthSort = 1;
    o[0].alpha = 0xFF;
    o[0].drawArg = &w->anim280;
    o[0].preDraw = NULL;
    o[0].attached = 0;
    o[0].attachJoint = -1;
    o[0].layer = 1;
    w->b21A = n + 1;

    o[1].kind = 4;
    o[1].actorObj = &STA_ACTORS->objects[(u8)(kEnd + 1)];
    o[1].shadow = NULL;
    o[1].update = NULL;
    o[1].onHit = NULL;
    o[1].visible = 1;
    o[1].hasShadow = (o[1].visible && o[1].shadow != NULL) ? 1 : 0;
    o[1].c.type = 0;
    CTRLSetTranslation(&o[1].c, lbl_3_rodata_2D5C, lbl_3_rodata_2F60, lbl_3_rodata_2D5C);
    CTRLSetRotation(&o[1].c, lbl_3_rodata_2D5C, lbl_3_rodata_2D5C, lbl_3_rodata_2D5C);
    o[1].depthSort = 1;
    o[1].alpha = 0xFF;
    o[1].drawArg = &w->anim2DC;
    o[1].preDraw = (void (*)(void*))fn_3_EEFA4;
    o[1].f88 = NULL;
    o[1].attached = 0;
    o[1].attachJoint = -1;
    o[1].layer = 1;
    fn_800B0A5C_insertQueue(fn_3_EEF24, 5);

    o[2].kind = 5;
    o[2].actorObj = &STA_ACTORS->objects[(u8)(kEnd + 3)];
    o[2].shadow = NULL;
    o[2].update = NULL;
    o[2].onHit = NULL;
    o[2].visible = 1;
    o[2].hasShadow = (o[2].visible && o[2].shadow != NULL) ? 1 : 0;
    o[2].c.type = 0;
    CTRLSetTranslation(&o[2].c, lbl_3_rodata_2D5C, lbl_3_rodata_2F64, lbl_3_rodata_2D5C);
    CTRLSetRotation(&o[2].c, lbl_3_rodata_2D5C, lbl_3_rodata_2D5C, lbl_3_rodata_2D5C);
    o[2].depthSort = 1;
    o[2].alpha = 0xFF;
    o[2].drawArg = NULL;
    o[2].preDraw = NULL;
    o[2].attached = 0;
    o[2].attachJoint = -1;
    o[2].layer = 1;
    o[2].customZ = 1;
    o[2].zCompare = 1;
    o[2].zAlways = 0;
    o[2].zUpdate = 0;

    /* unused slots */
    o += 3;
    for (k = n + 3; k < list->count; k++, o++) {
        o->kind = 0;
        o->actorObj = NULL;
        o->shadow = NULL;
        o->update = NULL;
        o->onHit = NULL;
        o->visible = 0;
        o->hasShadow = 0;
        o->depthSort = 0;
        o->c.type = 0;
        CTRLSetTranslation(&o->c, lbl_3_rodata_2D5C, lbl_3_rodata_2D5C, lbl_3_rodata_2D5C);
        CTRLSetRotation(&o->c, lbl_3_rodata_2D5C, lbl_3_rodata_2D5C, lbl_3_rodata_2D5C);
        o->alpha = 0;
        o->drawArg = NULL;
        o->attached = 0;
        o->attachJoint = -1;
    }

    list->groupBounds = NULL;
    if (g_d_GameSettings.GameModeSelected != 7) {
        fn_3_F6C60();
    }
    fn_3_EECF4();
}
#endif


#pragma dont_inline off
