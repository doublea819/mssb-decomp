#ifndef __GAME_sta_c2_H_
#define __GAME_sta_c2_H_

#include "mssbTypes.h"
#include "Dolphin/vec.h"
#include "Dolphin/mtx.h"
#include "main/file_80063028.h" // GameControl
#include "main/file_800BD8C4.h" // ActorObject
#include "main/file_800263FC.h" // Emitter, Particle

struct _CollisionStruct; // CollisionStruct (game/rep_D0.h): stadium objects' onHit argument

// One node of the verlet chain simulated by fn_3_D1F2C (4 or 8 nodes per object, 0x40 bytes each).
typedef struct RopeNode {
    /*0x00*/ f32 mass;
    /*0x04*/ f32 invMass;
    /*0x08*/ f32 radius;
    /*0x0C*/ Vec pos;
    /*0x18*/ Vec prev;
    /*0x24*/ Vec vel;
    /*0x30*/ Vec force;
    /*0x3C*/ u32 pinned;
} RopeNode;

// Chain simulation parameters (lbl_3_bss_A8A8, lbl_3_bss_A018+0x890).
typedef struct CC438Cfg {
    /*0x00*/ f32 a;
    /*0x04*/ f32 b;     // ground/sphere restitution factor
    /*0x08*/ f32 c, d, e, f;
    /*0x18*/ f32 h;     // substep time
    /*0x1C*/ f32 hh;    // h * h
    /*0x20*/ s32 n;     // substeps per frame
    /*0x24*/ f32 inv;   // 1 / (2 * h)
} CC438Cfg;

struct C2Obj;
typedef void (*C2ObjFn)(struct C2Obj* p);

// Flag byte 0x90 (declared in MWCC's big-endian bit order on PC).
#ifdef TARGET_PC
#define C2OBJ_BITS90 u8 bits : 5; u8 bit5 : 1; u8 hasShadow : 1; u8 visible : 1;
#else
#define C2OBJ_BITS90 u8 visible : 1; u8 hasShadow : 1; u8 bit5 : 1; u8 bits : 5;
#endif

// 0x88: a header pointer on PC (StadiumObj.postDraw), unused by these views.
#ifdef PORT_LP64
#define C2OBJ_88 /*0x88*/ void* _88;
#else
#define C2OBJ_88 /*0x88*/ u8 _88[4];
#endif

// Common head of the 0xE8-byte stadium objects (lbl_3_common_bss_350E4.objs; as PiranhaPlant in game/rep_2998.h).
#define C2OBJ_HEAD \
    /*0x00*/ GameControl ctrl; \
    /*0x44*/ u8 _44[0x74 - 0x44]; \
    /*0x74*/ ActorObject* actorObj; \
    /*0x78*/ void* shadow; \
    /*0x7C*/ C2ObjFn update; \
    /*0x80*/ void (*onHit)(s32 idx, s32 hitType, struct _CollisionStruct* hit); \
    /*0x84*/ C2ObjFn preDraw; \
    C2OBJ_88 \
    /*0x8C*/ void* _8C; \
    C2OBJ_BITS90 \
    /*0x91*/ u8 _91; \
    /*0x92*/ u8 alpha; \
    /*0x93*/ u8 _93; \
    /*0x94*/ s16 _94; \
    /*0x96*/ s16 _96; \
    /*0x98*/ u8 _98; \
    /*0x99*/ u8 _99; \
    /*0x9A*/ u8 _9A; \
    /*0x9B*/ u8 _9B; \
    /*0x9C*/ u8 idx; \
    /*0x9D*/ u8 kind; \
    /*0x9E*/ u8 _9E; \
    /*0x9F*/ u8 _9F;

// Any stadium object; the 0xA0.. tail depends on the kind (C2Obj* below).
typedef struct C2Obj {
    STADIUM_OBJ_BEGIN
    C2OBJ_HEAD
    /*0xA0*/ u8 _A0[0xE8 - 0xA0];
    STADIUM_OBJ_END
} C2Obj; // size: 0xE8

// The object with the rope (fn_3_CBC18 / fn_3_D3F54 and their helpers).
typedef struct C2ObjMain {
    STADIUM_OBJ_BEGIN
    C2OBJ_HEAD
    /*0xA0*/ Vec pos;
    /*0xAC*/ Vec _AC;
    /*0xB8*/ const Vec* _B8;
    /*0xBC*/ f32 _BC;
    /*0xC0*/ f32 _C0;
    /*0xC4*/ RopeNode* nodes;
    /*0xC8*/ s16 _C8;
    /*0xCA*/ u8 _CA;
    /*0xCB*/ u8 _CB;
    /*0xCC*/ u8 _CC;
    /*0xCD*/ u8 _CD;
    /*0xCE*/ u8 _CE[0xE8 - 0xCE];
    STADIUM_OBJ_END
} C2ObjMain;

// The companions animated by fn_3_D1848.
typedef struct C2ObjComp {
    STADIUM_OBJ_BEGIN
    C2OBJ_HEAD
    /*0xA0*/ f32 time;
    /*0xA4*/ f32 speed;
    /*0xA8*/ u8* mainFlag; // C2ObjMain._CA of the main object
    /*0xAC*/ u8 delay;
    /*0xAD*/ u8 _AD;
    /*0xAE*/ u8 _AE[0xE8 - 0xAE];
    STADIUM_OBJ_END
} C2ObjComp;

// A rope link drawn between two chain nodes (fn_3_D1280).
typedef struct C2ObjLink {
    STADIUM_OBJ_BEGIN
    C2OBJ_HEAD
    /*0xA0*/ Vec pos;
    /*0xAC*/ RopeNode* a;
    /*0xB0*/ RopeNode* b;
    /*0xB4*/ u8 _B4;
    /*0xB5*/ u8 _B5[0xE8 - 0xB5];
    STADIUM_OBJ_END
} C2ObjLink;

// The spinning object (fn_3_D0918).
typedef struct C2ObjSpin {
    STADIUM_OBJ_BEGIN
    C2OBJ_HEAD
    /*0xA0*/ Vec pos;
    /*0xAC*/ Quaternion rot;
    /*0xBC*/ f32 _BC;
    /*0xC0*/ f32 _C0;
    /*0xC4*/ f32 _C4;
    /*0xC8*/ f32 _C8;
    /*0xCC*/ f32 _CC;
    /*0xD0*/ u8 _D0;
    /*0xD1*/ u8 _D1;
    /*0xD2*/ u8 _D2; // object index count when set up
    /*0xD3*/ u8 _D3[0xE8 - 0xD3];
    STADIUM_OBJ_END
} C2ObjSpin;

// fn_3_D0284's object: the marker under a spinner.
typedef struct C2ObjD0284 {
    STADIUM_OBJ_BEGIN
    C2OBJ_HEAD
    /*0xA0*/ C2ObjSpin* target;
    /*0xA4*/ f32 _A4;
    /*0xA8*/ f32 _A8;
    /*0xAC*/ f32 _AC;
    /*0xB0*/ f32 _B0;
    /*0xB4*/ f32 _B4;
    /*0xB8*/ f32 _B8;
    /*0xBC*/ f32 _BC;
    /*0xC0*/ u8 _C0;
    /*0xC1*/ u8 _C1[0xE8 - 0xC1];
    STADIUM_OBJ_END
} C2ObjD0284;

// fn_3_D00D0's object: an effect attached to a C2ObjSpin.
typedef struct C2ObjFx {
    STADIUM_OBJ_BEGIN
    C2OBJ_HEAD
    /*0xA0*/ C2ObjSpin* target;
    /*0xA4*/ C2ObjD0284* marker;
    /*0xA8*/ Emitter* emitter;
    /*0xAC*/ u8 _AC;
    /*0xAD*/ u8 _AD[0xE8 - 0xAD];
    STADIUM_OBJ_END
} C2ObjFx;

// The props (fn_3_CFA8C).
typedef struct C2ObjProp {
    STADIUM_OBJ_BEGIN
    C2OBJ_HEAD
    /*0xA0*/ s32 phase;
    /*0xA4*/ u8 _A4[0xE8 - 0xA4];
    STADIUM_OBJ_END
} C2ObjProp;

// fn_3_CF930's object (hit reaction with a particle burst).
typedef struct C2ObjHit {
    STADIUM_OBJ_BEGIN
    C2OBJ_HEAD
    /*0xA0*/ Emitter* emitter;
    /*0xA4*/ u8 _A4;
    /*0xA5*/ u8 _A5[0xE8 - 0xA5];
    STADIUM_OBJ_END
} C2ObjHit;

// Any of the above.
typedef union C2ObjAny {
    C2Obj base;
    C2ObjMain main;
    C2ObjComp comp;
    C2ObjLink link;
    C2ObjSpin spin;
    C2ObjD0284 d0284;
    C2ObjFx fx;
    C2ObjProp prop;
    C2ObjHit hit;
} C2ObjAny;

#ifdef PORT_LP64
// Every view indexes the object array at the generic StadiumObj stride.
_Static_assert(sizeof(C2ObjAny) == STADIUM_OBJ_SIZE, "C2Obj stride");
_Static_assert(__builtin_offsetof(C2Obj, idx) == STADIUM_OBJ_PAD(0x9C), "C2Obj.idx");
#endif

// One entry of the stadium draw order built by fn_3_D55EC.
typedef struct C2SortEnt {
    f32 z;   // view-space depth while sorting, then the draw alpha
    s32 idx; // object index
} C2SortEnt;

void fn_3_CB8A8(C2ObjMain* p);
void fn_3_CBA9C(C2ObjMain* p);
void fn_3_CBAFC(C2ObjMain* p);
void fn_3_CBC18(C2ObjMain* p);
void fn_3_CBF80(C2ObjMain* p);
void fn_3_CC1D4(void);
void fn_3_CC354(RopeNode* p);
void fn_3_CC438(void);
void fn_3_CC5C4(C2ObjMain* p);
void fn_3_CC81C(void);
void fn_3_CCC24(void** files, u32* idx);
void fn_3_CD958(void);
u8 fn_3_CD968(Vec* v, f32 w, f32 h);
void fn_3_CDB48(void* pv, Emitter* h);
void fn_3_CDD90(Particle* p);
s32 fn_3_CDFA4(Emitter* h);
void fn_3_CE56C(Emitter* h, u8 idx);
void fn_3_CE8E4(void);
void fn_3_CE954(void);
void fn_3_CEBBC(f32* v, s32 k);
void fn_3_CEC98(void);
void fn_3_CED30(void);
void fn_3_CED34(void);
void fn_3_CED38(C2Obj* p);
void fn_3_CED3C(C2Obj* p);
void fn_3_CED40(Particle* p, void* a);
void fn_3_CEE5C(Particle* p, void* a);
s32 fn_3_CEFA8(Emitter* h);
void fn_3_CF278(C2ObjHit* p, Vec* pos);
void fn_3_CF72C(s32 idx, s32 hitType, struct _CollisionStruct* hit);
void fn_3_CF92C(C2Obj* p);
void fn_3_CF930(C2ObjHit* p);
void fn_3_CFA88(C2Obj* p);
void fn_3_CFA8C(C2ObjProp* p);
void fn_3_CFAB4(Particle* p, Emitter* q);
s32 fn_3_CFB44(Emitter* a);
void fn_3_CFD58(C2ObjFx* p);
void fn_3_D00CC(C2Obj* p);
void fn_3_D00D0(C2ObjFx* p);
void fn_3_D0280(C2Obj* p);
void fn_3_D0284(C2ObjD0284* p);
void fn_3_D0490(void);
void fn_3_D0528(C2Obj* p);
s32 fn_3_D052C(void);
void fn_3_D0534(C2ObjSpin* p);
f32 fn_3_D0854(C2ObjSpin* p);
void fn_3_D0918(C2ObjSpin* p);
void fn_3_D1004(C2ObjSpin* p, f32 x, f32 y, f32 z, f32 r, f32 sc);
void fn_3_D1110(C2ObjSpin* p);
void fn_3_D127C(C2Obj* p);
void fn_3_D1280(C2ObjLink* p);
void fn_3_D141C(C2ObjLink* p);
void fn_3_D173C(C2ObjComp* p);
void fn_3_D1848(C2ObjComp* s);
void fn_3_D196C(s32 idx, s32 hitType, struct _CollisionStruct* hit);
void fn_3_D1AC4(C2ObjMain* p);
void fn_3_D1B24(CC438Cfg* cfg, RopeNode* nodes, s32 n, Vec* grav);
void fn_3_D1F2C(CC438Cfg* cfg, RopeNode* nodes, s32 n, Vec* dir, C2ObjMain* p);
void fn_3_D2220(C2ObjMain* p);
u8* fn_3_D233C(C2ObjMain* p);
s32 fn_3_D249C(C2ObjMain* p);
void fn_3_D24E8(C2ObjMain* p, s32 idx0);
s32 fn_3_D255C(C2ObjMain* p);
u8* fn_3_D2684(C2ObjMain* p);
void fn_3_D278C(C2ObjMain* p);
void fn_3_D2A0C(C2ObjMain* p);
void fn_3_D30D0(C2ObjMain* p);
void fn_3_D36B0(C2ObjMain* p);
void fn_3_D3880(C2ObjMain* p);
void fn_3_D3CDC(C2ObjMain* p);
void fn_3_D3F54(C2ObjMain* p);
void fn_3_D4780(C2ObjMain* p);
void fn_3_D4CA4(C2ObjMain* p);
void fn_3_D4E00(C2ObjMain* p);
void fn_3_D501C(RopeNode* p);
void fn_3_D511C(void);
s32 fn_3_D53C0(u8 id);
s32 fn_3_D5444(u32* a, u32* b);
s32 fn_3_D5470(f32* a, f32* b);
void fn_3_D5494(f32 (*m)[4]);
void fn_3_D55EC(f32 (*view)[4], C2SortEnt* out);
void fn_3_D5B6C(s32* a);
void fn_3_D5C8C(s32* a);
void fn_3_D5E80(s32* a);
void fn_3_D60C0(s32* a);
void fn_3_D62F0(s32* a);
void fn_3_D6514(void);
void fn_3_D67CC(void** files);

#endif // !__GAME_sta_c2_H_
