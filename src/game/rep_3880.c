#ifdef TARGET_PC
#define FOLLOW_OBJ(e) PTR32_GET(struct ActorObject, (e)->u.follow.obj)
#else
#define FOLLOW_OBJ(e) ((e)->u.follow.obj)
#endif
#include "game/rep_3880.h"
#include "game/UnknownHomes_Game.h"
#include "main/file_800263FC.h"
#include "main/file_80008E00.h"
#include "main/file_80011640.h"
#include "main/file_800BD8C4.h"
#include "main/file_800B0724.h"
#include "main/file_8004C5F8.h"
#include "static/GameSettings.h"

// lbl_3_common_bss_32724 (GameHudFlags in game/auto_00_00097144_text.h), only the fields used here.
typedef struct EffectBss32724 {
    /*0x00*/ u8 _00[0x64];
    /*0x64*/ TexArchive* textures[3];
    /*0x70*/ u8 _70[0x124 - 0x70];
} EffectBss32724; // size: 0x124

// lbl_3_common_bss_35154 (0x480), only the fields used here.
typedef struct EffectBss35154 {
    /*0x000*/ u8 _000[0x4];
    /*0x004*/ TexArchive* tex;
    /*0x008*/ u8 _008[0x480 - 0x8];
} EffectBss35154; // size: 0x480

typedef struct V3I {
    s32 x, y, z;
} V3I;

// lbl_3_data_266A8 (0x14C): spark/trail parameters for the minigame-5 ring effect (fn_3_15767C).
#ifdef PORT_LP64
// PC: lbl_3_data_266A8 (3 floats) and lbl_3_data_266B4 (80 words) are separate objects here, and the
// parameter structs hold 8-byte TexArchive pointers, so the GameCube block can't be overlaid. A
// PC-layout copy is built from the original words on first use (port_effect266A8, end of file).
typedef struct EffectData266A8 {
    f32 scale[2];
    ParticleParams5 sparks[3];
    union {
        ParticleParams8 trail;
        u8 trailRaw[0x60]; // trail + trail.texIndex2 continuing into the 7 extra indices
    };
    s16 sparkTex[4][2];
} EffectData266A8;
static EffectData266A8* port_effect266A8(void);
#else
typedef struct EffectData266A8 {
    /*0x000*/ f32 scale[2];
    /*0x008*/ ParticleParams5 sparks[3];
    /*0x0F8*/ ParticleParams8 trail;
    /*0x120*/ s32 trailTex[7]; // continues trail.texIndex2
    /*0x13C*/ s16 sparkTex[4][2];
} EffectData266A8; // size: 0x14C
#endif

// lbl_3_data_26894 (0x308), only the fields used here.
typedef struct EffectData26894 {
    /*0x000*/ u8 _000[0x50];
    /*0x050*/ ParticleParams5* sparks[3];
    /*0x05C*/ u8 _05C[0x68 - 0x5C];
    /*0x068*/ V3I offsets[54]; // per character kind, fixed point (x100000)
    /*0x2F0*/ u32 colors[4];
    /*0x300*/ f32 trailScale[2];
} EffectData26894; // size: 0x308

// A particle of the fn_3_157588 emitter used as storage for seven positions (fn_3_15730C).
typedef struct VecSlotParticle {
    /*0x00*/ struct Particle* next;
    /*0x04*/ Vec v[7];
} VecSlotParticle;

#define REP_HEADER_FN repHeader_3880
#include "header_rep_inline.h"

extern s32 lbl_3_data_26C94[];
extern const f32 lbl_3_rodata_39F8;
extern const f32 lbl_3_rodata_39F4;
extern const f32 lbl_3_rodata_39FC;
extern const f32 lbl_3_rodata_39BC;
extern const f64 lbl_3_rodata_39E8;
extern s32 lbl_3_data_26D00[];
extern void fn_8003403C(f32, f32);
extern EffectBss32724 lbl_3_common_bss_32724;
#ifdef PORT_LP64
// textures[] live in the minigame asset block's own storage on PC (game/auto_00_0011D3AC_text.h).
typedef struct { void* model; ShapeAnimPlayer anim; void* skin; TexArchive* textures[3]; void* animBanks[3]; } MinigameAssetPtrs3880;
extern MinigameAssetPtrs3880 g_port_mgAssets;
#define MG_ASSETS g_port_mgAssets
#else
#define MG_ASSETS lbl_3_common_bss_32724
#endif
extern s32 lbl_3_data_26D5C[];
extern f32 lbl_3_data_21770[];
extern s32 lbl_3_data_26E9C[];
extern s8 lbl_3_bss_B85C[];
extern s32 lbl_3_data_26BDC[];
extern s32 lbl_3_data_26BEC[];
extern f32 lbl_3_rodata_3A18;
extern f32 fn_3_119854(u8 i);

extern const f32 lbl_3_rodata_3A34;
extern const f32 lbl_3_rodata_3A38;
extern const f32 lbl_3_rodata_3A3C;
extern const f32 lbl_3_rodata_3A40;
extern const f32 lbl_3_rodata_3A44;
#include "Dolphin/GX.h"
#include "Dolphin/mtx.h"
#include "C3/control.h"
#include "main/file_80024184.h"


extern Vec lbl_3_data_26E00[];
extern const Vec lbl_3_rodata_3908;
extern f32 lbl_3_data_266A8[];
// lbl_3_data_266A8 and the tables after it, read through one pooled view (the original does the same).
#ifdef PORT_LP64
#define EFFECT266A8 (port_effect266A8())
#else
#define EFFECT266A8 ((EffectData266A8*)lbl_3_data_266A8)
#endif
extern s32* lbl_3_data_268E4[]; // spark parameter sets, then (from [6]) per-character V3I offsets
extern u32 lbl_3_data_26B84[];
extern f32 lbl_3_data_26B94[];
extern Vec lbl_3_data_26BB4;
extern f64 __fabs(f64);
extern f32 __fabsf(f32);
extern s32 lbl_3_data_26BC0[];
extern const f32 lbl_3_rodata_3950;
extern const f64 lbl_3_rodata_3A08;
extern const Vec lbl_3_rodata_38D0;
extern f32 fn_3_119D28(void);
extern u8 lbl_3_data_26CB8[];
extern int rand(void);
extern s32 lbl_3_data_26E24[];
extern s32 lbl_3_data_26C3C[];
extern u8 lbl_3_bss_B894[];
extern const f32 lbl_3_rodata_3930;
extern const f32 lbl_3_rodata_39B8;
extern const f32 lbl_3_rodata_39AC;
extern const f64 lbl_3_rodata_39C8;
extern s32 lbl_3_data_26E40[];
extern void fn_80033F64(f32, f32, f32);
extern Vec lbl_3_data_26D50[];
extern s32 lbl_3_data_26CD0[];
extern const f32 lbl_3_rodata_39E0;
extern const f32 lbl_3_rodata_39C0;
extern const f32 lbl_3_rodata_39F0;
extern f32 shortAngleToRad(s16);
extern s32 lbl_3_data_26E7C[];
extern s32 lbl_3_data_26D88[];
extern s32 lbl_3_data_26DC4[];
extern void fn_8003403C(f32, f32);
extern const f32 lbl_3_rodata_3970;
extern const f32 lbl_3_rodata_39C4;
extern const f64 lbl_3_rodata_3990;
extern const f64 lbl_3_rodata_3968;
extern const f64 lbl_3_rodata_39D8;
extern const f64 lbl_3_rodata_3978;
extern f64 cos(f64);
extern f64 sin(f64);
extern f32 lbl_3_bss_B860[];
extern const f32 lbl_3_rodata_39A8;
extern f32 lbl_3_rodata_392C;
extern f32 lbl_3_rodata_3A00;
extern const Vec lbl_3_rodata_38DC;
extern const f32 lbl_3_rodata_3A04;
extern f32 lbl_3_rodata_3948;
extern s32 fn_8005268C(void);
extern f64 acos(f64);
extern const Vec lbl_3_rodata_3914;
extern s32 lbl_3_data_26BFC[];
extern void* memcpy(void*, const void*, size_t);
extern void fn_3_11F4B4(s32 idx, s32 flag);
extern f32 lbl_3_data_26C1C[];
extern const f32 lbl_3_rodata_3934[];
typedef struct { f32 x, y, z; } V3B;
extern Emitter* lbl_3_bss_B850;
extern void* memset(void*, int, size_t);
extern s32 lbl_3_data_26C0C[];
extern const f32 lbl_3_rodata_3938;
extern EffectBss35154 lbl_3_common_bss_35154;
extern TexImage* lbl_3_bss_B854;
extern u32 lbl_3_data_26B9C[];
extern u8 lbl_3_bss_B858;
extern const Vec lbl_3_rodata_3920;
extern const f64 lbl_3_rodata_39B0;
extern const f32 lbl_3_rodata_3A1C;
extern const f64 lbl_3_rodata_3A10;
extern void PSMTX44MultVec(const Mtx44 mtx, const Vec* src, Vec* dst);
extern const f64 lbl_3_rodata_39D0;
extern const f32 lbl_3_rodata_394C;
extern const f64 lbl_3_rodata_3958;
extern const f64 lbl_3_rodata_3960;
extern const f32 lbl_3_rodata_3980;
extern const f64 lbl_3_rodata_3988;
extern const f32 lbl_3_rodata_3998;
extern f32 lbl_3_data_26BAC;
extern f32 lbl_3_data_26BB0;
extern const f32 lbl_3_rodata_3A20;
extern const f32 lbl_3_rodata_3A24;
extern const f32 lbl_3_rodata_3A28;
extern const f32 lbl_3_rodata_3A2C;
extern const f32 lbl_3_rodata_3A30;
extern void fn_800B1468(Vec* pos, u32 color, TexImage* tex);
extern void fn_800B27DC(Mtx44 m, s32 type);
extern void fn_800B2160(u8 value);

#pragma dont_inline on

// g_Minigame + 0xA8: 0x28 tracked objects of the minigame-5 ring effect (fn_3_15767C), 0x28 bytes each.
typedef struct EffectMgObj {
    /*0x00*/ Vec pos;
    /*0x0C*/ u8 _0C[0x1C - 0xC];
    /*0x1C*/ s32 colorIdx;
    /*0x20*/ u8 _20[0x26 - 0x20];
    /*0x26*/ u8 active;
    /*0x27*/ u8 _27;
} EffectMgObj; // size: 0x28
#define EFFECT_MG_OBJS ((EffectMgObj*)&g_Minigame._A8)


// NONMATCHING 83%: table index (p[0x4C]==1 ? 0 : 10) is recomputed per access in the orig with a different load order
// .text:0x0014737C size:0x3FC mapped:0x80786410
#pragma dont_inline off
static inline s32 k737c(Particle* p) { s32 k = 10; if (p->unk4C == 1) k = 0; return k; }
#if NONMATCHING
u32 fn_3_14737C(Emitter* o) {
    s32 n;
    Particle* p;
    Particle** pp;
    Particle* prev;
    s32* d;
    s32 t30;
    s32 t29;
    s32 a;
    s32 s;
    s32 delta;
    f32 sc;
    f32 df;
    n = 0;
    p = fn_80031F34(o->particles, o->count);
    o->particles = p;
    pp = &o->particles;
    prev = NULL;
    GXSetZMode(1, 7, 0);
    d = lbl_3_data_26E9C;
    do {
        if (p->life != 0) {
            if (p->delay <= 0) {
                t30 = (p->unk4C == 1) ? d[3] : d[13];
                t29 = (p->unk4C == 1) ? d[1] : d[11];
                if (p->unk4C == 1) {
                    GXSetBlendMode(1, 4, 6, 0);
                } else {
                    GXSetBlendMode(1, 4, 5, 0);
                }
                fn_8003403C(p->sizeX, p->sizeY);
                fn_80033CC8(p, o->tex);
                a = p->color.c.a;
                sc = (p->unk4C == 1) ? p->u.phys.vel.x : lbl_3_rodata_392C;
                if (t30 > t29 - p->life) {
                    df = sc * (((f32)lbl_3_data_26E9C[(k737c(p)) + 5] / lbl_3_rodata_3930 - (f32)lbl_3_data_26E9C[(k737c(p)) + 4] / lbl_3_rodata_3930) / (f32)t30);
                    delta = (lbl_3_data_26E9C[(k737c(p)) + 8] - lbl_3_data_26E9C[(k737c(p)) + 7]) / t30;
                } else {
                    s = t29 - t30;
                    df = sc * (((f32)lbl_3_data_26E9C[(k737c(p)) + 6] / lbl_3_rodata_3930 - (f32)lbl_3_data_26E9C[(k737c(p)) + 5] / lbl_3_rodata_3930) / (f32)s);
                    delta = (lbl_3_data_26E9C[(k737c(p)) + 9] - lbl_3_data_26E9C[(k737c(p)) + 8]) / s;
                }
                a += delta;
                if (a < 0) {
                    a = 0;
                } else if (a > 0xFF) {
                    a = 0xFF;
                }
                p->sizeY = p->sizeX = p->sizeX + df;
                p->color.c.a = a;
                p->pos.y -= (p->unk4C == 1) ? lbl_3_rodata_3934[0] : lbl_3_rodata_3938;
                p->life -= 1;
                if (p->life == 0) {
                    *pp = p->next;
                    if (prev != NULL) {
                        prev->next = p;
                    }
                    prev = p;
                    p->next = NULL;
                    o->count--;
                } else {
                    pp = &p->next;
                    n++;
                }
            } else {
                p->delay -= 1;
                pp = &p->next;
                n++;
            }
        }
        p = *pp;
    } while (p != NULL);
    return n == 0;
}
#endif
#pragma dont_inline on

// NONMATCHING 98%: only the ring-angle int->double conversions in the first branch are scheduled in the other order
// .text:0x00147778 size:0x488 mapped:0x8078680C
#if NONMATCHING
void fn_3_147778(Emitter* e, Vec* pos) {
    s16 delay;
    Particle* p;
    u32 i;
    u8 nA;
    u8 nB;
    f64 ang;
    f32 size;
    i = 0;
    nA = lbl_3_data_26E9C[2];
    nB = lbl_3_data_26E9C[12];
    if (pos->y > lbl_3_rodata_3934[0]) {
        pos->y *= lbl_3_rodata_3948;
    }
    delay = 0;
    e->tex = MG_ASSETS.textures[2];
    p = e->particles;
    do {
        if (i < nA) {
            p->unk4C = 1;
            p->u.phys.vel.x = (i == 0) ? lbl_3_rodata_394C : lbl_3_rodata_3950;
            p->life = lbl_3_data_26E9C[1];
            size = (f32)lbl_3_data_26E9C[4] / lbl_3_rodata_3930 * p->u.phys.vel.x;
            p->sizeX = p->sizeY = size;
            p->color.c.a = lbl_3_data_26E9C[7];
            memcpy(&p->pos, pos, sizeof(Vec));
            if (i != 0) {
                ang = lbl_3_rodata_3958 * (lbl_3_rodata_3960 / (f64)nA) * (f64)(i - 1);
                p->pos.x = lbl_3_rodata_3950 * (f32)cos((f32)ang) + p->pos.x;
                p->pos.y = lbl_3_rodata_3950 * (f32)sin((f32)ang) + p->pos.y;
                p->pos.x = lbl_3_rodata_3968 * ((f64)((f32)rand() / lbl_3_rodata_3970) - lbl_3_rodata_3978) + p->pos.x;
                p->pos.y = lbl_3_rodata_3968 * ((f64)((f32)rand() / lbl_3_rodata_3970) - lbl_3_rodata_3978) + p->pos.y;
            }
            p->texIndex = lbl_3_data_26E9C[0];
            p->delay = delay;
        } else {
            p->unk4C = 2;
            p->life = lbl_3_data_26E9C[11];
            size = (f32)lbl_3_data_26E9C[14] / lbl_3_rodata_3930;
            p->sizeX = p->sizeY = size;
            p->color.c.a = lbl_3_data_26E9C[17];
            memcpy(&p->pos, pos, sizeof(Vec));
            ang = lbl_3_rodata_3958 * (lbl_3_rodata_3960 / (f64)nB) * (f64)(u8)(i - nA);
            p->pos.x = lbl_3_rodata_3980 * (f32)cos((f32)ang) + p->pos.x;
            p->pos.y = lbl_3_rodata_3980 * (f32)sin((f32)ang) + p->pos.y;
            p->pos.x = lbl_3_rodata_3988 * (lbl_3_rodata_3990 * ((f64)((f32)rand() / lbl_3_rodata_3970) - lbl_3_rodata_3968)) + p->pos.x;
            p->pos.y = lbl_3_rodata_3998 * (lbl_3_rodata_3948 * ((f32)rand() / lbl_3_rodata_3970)) + p->pos.y;
            p->texIndex = lbl_3_data_26E9C[10];
            p->delay = 5;
        }
        p->color.c.b = 0xFF;
        delay += 2;
        i++;
        p->color.c.g = 0xFF;
        p->color.c.r = 0xFF;
        p->uvFrame = 0;
        p = p->next;
    } while (p != NULL);
}
#endif

// .text:0x00147C00 size:0xFC mapped:0x80786C94
void fn_3_147C00(void* arg) {
    Emitter buf; // only its particle list is filled in
    Emitter* h = fn_800339F0(0, 0x26);
    Emitter* n;
    Particle* p;
    Emitter* hh;
    if (h != NULL) {
        n = fn_800337CC(&buf, lbl_3_data_26E9C[2] + lbl_3_data_26E9C[12], 1);
        if (n != NULL) {
            fn_3_147778(n, arg);
            p = h->particles;
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = n->particles;
            h->count += n->count;
        }
    } else {
        n = fn_80033A24((EmitterUpdateFn)fn_3_14737C, 0x80, 0, lbl_3_data_26E9C[2] + lbl_3_data_26E9C[12], 1, 0x26);
        if (n != NULL) {
            fn_3_147778(n, arg);
        }
    }
}

// .text:0x00147CFC size:0x100 mapped:0x80786D90
void fn_3_147CFC(void* arg) {
    Emitter buf; // only its particle list is filled in
    Emitter* h;
    Emitter* n;
    Particle* p;
    if (arg == NULL) {
        return;
    }
    h = fn_800339F0(0, 0x26);
    if (h != NULL) {
        n = fn_800337CC(&buf, lbl_3_data_26E9C[2] + lbl_3_data_26E9C[12], 1);
        if (n != NULL) {
            fn_3_147778(n, arg);
            p = h->particles;
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = n->particles;
            h->count += n->count;
        }
    } else {
        n = fn_80033A24((EmitterUpdateFn)fn_3_14737C, 0x80, 0, lbl_3_data_26E9C[2] + lbl_3_data_26E9C[12], 1, 0x26);
        if (n != NULL) {
            fn_3_147778(n, arg);
        }
    }
}

// .text:0x00147DFC size:0x24 mapped:0x80786E90
void fn_3_147DFC(void) {
    pitchingMachinePitching(0x25);
}

#pragma dont_inline off
// .text:0x00147E20 size:0x174 mapped:0x80786EB4
void fn_3_147E20(void) {
    GXSetZMode(1, 3, 1);
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
    GXLoadPosMtxImm(fn_80052768_getCamera(0)->view, 0);
    GXSetCurrentMtx(0);
}

// .text:0x00147F94 size:0x14C mapped:0x80787028
void fn_3_147F94(void) {
    GXSetZMode(1, 7, 1);
    GXSetBlendMode(1, 4, 5, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorIn(0, 0xF, 0xF, 0xF, 0xA);
    GXSetTevAlphaIn(0, 7, 7, 7, 5);
    GXSetTevOrder(0, 0xFF, 0xFF, 4);
    GXSetTevOp(0, 4);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
}

// NONMATCHING 96%: orig reads vertices 2-3 of the 2nd quad via lfsu (r4 = base+0xc); we fold to base-relative lfs; also li r3,1 scheduling
// .text:0x001480E0 size:0x174 mapped:0x80787174
#if NONMATCHING
void fn_3_1480E0(Particle* o) {
    f32* v;
    GXSetCullMode(2);
    GXBegin(0x80, 0, 4);
    v = (f32*)lbl_3_bss_B860;
    GXWGFIFO_F32(v[0]);
    GXWGFIFO_F32(v[1]);
    GXWGFIFO_F32(v[2]);
    GXWGFIFO_U32(PCOLOR_GET(o->color));
    GXWGFIFO_F32(v[3]);
    GXWGFIFO_F32(v[4]);
    GXWGFIFO_F32(v[5]);
    GXWGFIFO_U32(PCOLOR_GET(o->color));
    GXWGFIFO_F32(v[6]);
    GXWGFIFO_F32(v[7]);
    GXWGFIFO_F32(v[8]);
    GXWGFIFO_U32(PCOLOR_GET(o->color));
    GXWGFIFO_F32(v[9]);
    GXWGFIFO_F32(v[10]);
    GXWGFIFO_F32(v[11]);
    GXWGFIFO_U32(PCOLOR_GET(o->color));
    GXSetCullMode(1);
    GXBegin(0x80, 0, 4);
    {
    f32* p = v + 3;
    GXWGFIFO_F32(v[0]);
    GXWGFIFO_F32(v[1]);
    GXWGFIFO_F32(v[2]);
    GXWGFIFO_U32(PCOLOR_WORD(o->colorStep, all));
    GXWGFIFO_F32(v[3]);
    GXWGFIFO_F32(v[4]);
    GXWGFIFO_F32(v[5]);
    GXWGFIFO_U32(PCOLOR_WORD(o->colorStep, all));
    GXWGFIFO_F32(p[3]);
    GXWGFIFO_F32(p[4]);
    GXWGFIFO_F32(p[5]);
    GXWGFIFO_U32(PCOLOR_WORD(o->colorStep, all));
    GXWGFIFO_F32(p[6]);
    GXWGFIFO_F32(p[7]);
    GXWGFIFO_F32(p[8]);
    GXWGFIFO_U32(PCOLOR_WORD(o->colorStep, all));
    }
}
#endif

// .text:0x00148254 size:0x180 mapped:0x807872E8
void fn_3_148254(Emitter* a, Particle* b) {
    Control c;
    Mtx m;
    Vec v;
    f32 hx;
    f32 hy;
    CharActor* t;
    f32 h = b->sizeY;
    hx = b->sizeX;
    hx *= lbl_3_rodata_39A8;
    hy = h * lbl_3_rodata_39A8;
    t = lbl_8036E548.active[((s8)a->u.t5.unk18)];
    lbl_3_bss_B860[3] = hx;
    lbl_3_bss_B860[0] = -hx;
    lbl_3_bss_B860[1] = -hy;
    lbl_3_bss_B860[4] = -hy;
    lbl_3_bss_B860[6] = hx;
    lbl_3_bss_B860[7] = hy;
    lbl_3_bss_B860[9] = -hx;
    lbl_3_bss_B860[10] = hy;
    PSMTXInverse(fn_80052768_getCamera(0)->view, m);
    m[2][1] = lbl_3_rodata_3934[0];
    m[1][2] = lbl_3_rodata_3934[0];
    m[1][0] = lbl_3_rodata_3934[0];
    m[0][1] = lbl_3_rodata_3934[0];
    m[1][1] = lbl_3_rodata_392C;
    v.x = b->pos.x;
    v.y = b->pos.y;
    v.z = b->pos.z;
    PSMTXMultVecSR(m, &v, &v);
    c.type = 0;
    CTRLSetRotation(&c, b->u.phys.accel.x, b->u.phys.accel.y, b->u.phys.accel.z);
    CTRLSetTranslation(&c, t->pos.x + v.x, -t->pos.y + v.y, t->pos.z + v.z);
    CTRLBuildMatrix(&c, m);
    PSMTXConcat(fn_80052768_getCamera(0)->view, m, m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
}

// .text:0x001483D4 size:0x48 mapped:0x80787468
u8 fn_3_1483D4(void) {
    return rand() % 5 == 0;
}

// NONMATCHING 72%: the original inlines 147F94/148254/1480E0/1483D4/148EF0/148FD0/147E20; CW won't auto-inline 148254/1480E0 (Control/fifo bodies), so those stay calls. With explicit static-inline copies of those two it reaches 93% (register numbering), which checks the structure
// .text:0x0014841C size:0xAD4 mapped:0x807874B0
#if NONMATCHING
u32 fn_3_14841C(Emitter* o) {
    Vec up;
    Vec dir;
    Particle* p;
    CharActor* t;
    f32 ang;
    f32 r;
    p = o->particles;
    t = lbl_8036E548.active[((s8)o->u.t5.unk18)];
    fn_3_147F94();
    do {
        if (p->delay <= 0) {
            fn_3_148254(o, p);
            fn_3_1480E0(p);
            PSVECAdd(&p->u.phys.vel, &p->pos, &p->pos);
            PSVECAdd(&p->u.phys.force, &p->u.phys.accel, &p->u.phys.accel);
            if (fn_3_1483D4()) {
                up = lbl_3_rodata_3920;
                memcpy(&dir, &p->u, sizeof(Vec));
                PSVECNormalize(&dir, &dir);
                ang = lbl_3_rodata_39AC * (f32)acos(PSVECDotProduct(&up, &dir));
                if (dir.x < lbl_3_rodata_3934[0]) {
                    ang *= lbl_3_rodata_3948;
                }
                r = lbl_3_rodata_39B0 * (lbl_3_rodata_3990 * ((f64)((f32)rand() / lbl_3_rodata_3970) - lbl_3_rodata_3968));
                if (__fabs(ang + r) > lbl_3_rodata_39B0) {
                    ang = lbl_3_rodata_39B0 * (__fabs(ang) / ang);
                } else {
                    ang = ang + r;
                }
                fn_3_148EF0(p, ang);
                p->unk4C++;
            }
            if (-p->pos.y - p->sizeY < t->pos.y) {
                fn_3_148FD0(o, p);
            }
        } else {
            p->delay -= 1;
        }
        p = p->next;
    } while (p != NULL);
    fn_3_147E20();
    return 0;
}
#endif

#pragma dont_inline off
// .text:0x00148EF0 size:0xE0 mapped:0x80787F84
void fn_3_148EF0(Particle* o, f32 ang) {
    f32 s;
    f32 a;
    f32 c;
    a = lbl_3_rodata_39B8 * ang;
    s = (f32)sin(a);
    c = (f32)cos(a);
    o->u.phys.vel.x = s * (f32)lbl_3_data_26E7C[1] / lbl_3_rodata_3930;
    o->u.phys.vel.y = c * (f32)lbl_3_data_26E7C[1] / lbl_3_rodata_3930;
    o->u.phys.vel.z = 0.0f;
}
#pragma dont_inline on

// The original inlines 148FD0 into 149340 into 14975C into 149BA8; CW only inlines bodies that big with a raised limit
// (600 is enough; 1000 also inlines fn_3_14E234 into fn_3_14E7C0, which the original does not).
#pragma inline_max_size(600)
static inline void Inl148FD0(Emitter* a, Particle* p) {
    s32 base = lbl_3_data_26E7C[6];
    CharActor* t = lbl_8036E548.active[((s8)a->u.t5.unk18)];
    u8 lo;
    u8 range;
    s32 r;
    lo = base;
    p->pos.x = lbl_3_rodata_3934[0];
    p->pos.y = -((f32)lbl_3_data_26E7C[5] / lbl_3_rodata_3930 + t->pos.y);
    p->pos.z = lbl_3_rodata_3934[0];
    fn_3_148EF0(p, lbl_3_rodata_39BC * ((f32)(lbl_3_data_26E7C[0] / 2 - p->life) / ((f32)lbl_3_data_26E7C[0] * lbl_3_rodata_39A8)));
    p->u.phys.accel.x = p->u.phys.accel.y = p->u.phys.accel.z = 0.0f;
    r = lbl_3_rodata_39C0 * ((f32)lbl_3_data_26E7C[2] / lbl_3_rodata_3930);
    p->u.phys.force.x = (f32)(rand() % r) / lbl_3_rodata_39C0;
    p->u.phys.force.y = (f32)(rand() % r) / lbl_3_rodata_39C0;
    p->u.phys.force.z = (f32)(rand() % r) / lbl_3_rodata_39C0;
    p->colorStep.v[3] = 0xFF;
    p->color.c.a = 0xFF;
    range = 0xFF - base;
    p->color.c.g = lo + rand() % range;
    p->color.c.b = lo + rand() % range;
    p->colorStep.v[0] = lo + rand() % range;
    p->colorStep.v[1] = lo + rand() % range;
    p->colorStep.v[2] = lo + rand() % range;
    p->unk4C = 0;
}

static inline void Inl149340(Emitter* o) {
    Particle* p;
    u32 i;
    s32 q;
    p = o->particles;
    i = 0;
    do {
        p->life = i;
        p->sizeX = (f32)lbl_3_data_26E7C[3] / lbl_3_rodata_3930;
        p->sizeY = (f32)lbl_3_data_26E7C[4] / lbl_3_rodata_3930;
        Inl148FD0(o, p);
        q = lbl_3_data_26E7C[0] / 5;
        p->delay = ((i % 5) * q + rand() % q) * 2;
        i++;
        p = p->next;
    } while (p != NULL);
}

static inline void Inl14975C(s8 a) {
    Emitter* e = fn_80033A24((EmitterUpdateFn)fn_3_14841C, 0x80, 0, lbl_3_data_26E7C[0], 1, 0x25);
    if (e != NULL) {
        e->u.t5.unk18 = a;
        Inl149340(e);
    }
}

// NONMATCHING 89%: 148EF0 inlined; orig computes the clrlwi copy of the colour base early in its own saved reg (r30), ours sinks it to the end, shifting saved regs. Body shared with the inlined copies via Inl148FD0
// .text:0x00148FD0 size:0x370 mapped:0x80788064
#pragma dont_inline off
#if NONMATCHING
void fn_3_148FD0(Emitter* a, Particle* p) {
    Inl148FD0(a, p);
}
#endif
#pragma dont_inline on

// NONMATCHING 92%: 148FD0 inlined (via Inl148FD0); the hoisted float constants use one more saved FPR (f22) and the saved GPRs are shifted by one
// .text:0x00149340 size:0x41C mapped:0x807883D4
#pragma dont_inline off
#if NONMATCHING
void fn_3_149340(Emitter* o) {
    Inl149340(o);
}
#endif
#pragma dont_inline on

// NONMATCHING 92%: 149340/148FD0 inlined via the Inl* helpers; differences are the 148FD0 register shifts
// .text:0x0014975C size:0x44C mapped:0x807887F0
#pragma dont_inline off
#if NONMATCHING
void fn_3_14975C(s8 a) {
    Inl14975C(a);
}
#endif
#pragma dont_inline on

// NONMATCHING 92%: 14975C/149340/148FD0 inlined via the Inl* helpers; differences are the 148FD0 register shifts
// .text:0x00149BA8 size:0x4C8 mapped:0x80788C3C
#pragma dont_inline off
#if NONMATCHING
void fn_3_149BA8(void) {
    u32 i;
    if (g_d_GameSettings.GameModeSelected != 7 && g_d_GameSettings.GameModeSelected != 6) {
        lbl_3_data_26E7C[5] = 930000;
    } else {
        lbl_3_data_26E7C[5] = 750000;
    }
    for (i = 0; i < 4; i++) {
        if (lbl_3_bss_B85C[i] > -1) {
            Inl14975C(lbl_3_bss_B85C[i]);
        }
    }
}
#endif
#pragma dont_inline on

// .text:0x0014A070 size:0xF4 mapped:0x80789104
void fn_3_14A070(s32* src, s32 n) {
    u32 i;
    lbl_3_bss_B85C[0] = -1;
    lbl_3_bss_B85C[1] = -1;
    lbl_3_bss_B85C[2] = -1;
    lbl_3_bss_B85C[3] = -1;
    if (n > 4 || n == 0 || src == NULL) { return; }
    for (i = 0; i < (u32)n; i++) { lbl_3_bss_B85C[i] = src[i]; }
}

// .text:0x0014A164 size:0x24 mapped:0x807891F8
void fn_3_14A164(void) {
    pitchingMachinePitching(0x24);
}

// NONMATCHING 99%: only the flag base addr is addi r3 (orig: lis/addi r4 before stmw); computing delta after df in the else branch fixed the float regs
// .text:0x0014A188 size:0x1F4 mapped:0x8078921C
u32 fn_3_14A188(Emitter* o) {
    Particle* p;
    s32* d;
    s32 a;
    s32 alive = 0;
    s32 delta;
    f32 df;
    f32 q;
    s32 s;
    if (lbl_80366158._28 != 0) {
        return 0;
    }
    fn_80033620(o);
    p = o->particles;
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    d = lbl_3_data_26E40;
    do {
        if (p->life != 0) {
            a = p->color.c.a;
            fn_80033F64(p->sizeX, p->sizeY, p->u.phys.vel.x);
            fn_80033CC8(p, o->tex);
            if (d[2] - p->life < d[4]) {
                df = (p->u.phys.vel.z - (f32)d[5] / lbl_3_rodata_3930) / (f32)d[4];
                delta = (d[10] - d[9]) / d[4];
            } else {
                s = d[2] - d[4];
                q = (f32)d[8] / lbl_3_rodata_3930;
                df = q + p->u.phys.vel.z;
                df /= (f32)s;
                delta = (d[11] - d[10]) / s;
            }
            a += delta;
            if (a < 0) {
                a = 0;
            }
            if (a > 0xFF) {
                a = 0xFF;
            }
            p->color.c.a = a;
            p->sizeX = p->sizeX + df;
            p->sizeY = p->sizeX;
            p->u.phys.vel.x = p->u.phys.vel.x + p->u.phys.vel.y;
            if ((p->life = p->life - 1) != 0) {
                alive++;
            }
        }
        p = p->next;
    } while (p != NULL);
    return alive == 0;
}

// .text:0x0014A37C size:0x2B0 mapped:0x80789410
void fn_3_14A37C(Emitter* o, f32* v) {
    Particle* p;
    s32* d;
    s32 i;
    f32 ang;
    f32 c;
    o->tex = MG_ASSETS.textures[2];
    p = o->particles;
    d = lbl_3_data_26E40;
    i = 0;
    do {
        p->texIndex = *d;
        p->uvFrame = 0;
        p->life = d[2];
        p->delay = 0;
        p->pos.x = v[0];
        p->pos.y = -v[1];
        p->pos.z = v[2];
        ang = (f32)(u32)(0x168 / d[1] * i);
        ang = lbl_3_rodata_39B8 * ang;
        c = (f32)cos(ang);
        p->pos.x = p->pos.x + (f32)d[3] * c / lbl_3_rodata_3930;
        c = (f32)sin(ang);
        p->pos.y = p->pos.y + (f32)d[3] * c / lbl_3_rodata_3930;
        p->sizeX = p->sizeY = (f32)d[5] / lbl_3_rodata_3930;
        p->color.c.b = 0xFF;
        p->color.c.g = 0xFF;
        p->color.c.r = 0xFF;
        p->color.c.a = d[9];
        p->u.phys.vel.x = lbl_3_rodata_3934[0];
        p->u.phys.vel.y = (f32)(d[12] - rand() % d[13]);
        p->u.phys.vel.y = p->u.phys.vel.y / lbl_3_rodata_3930;
        p->u.phys.vel.y = p->u.phys.vel.y * (f32)(-(rand() % 2 * 2) + 1);
        p->u.phys.vel.z = (f32)(d[6] - rand() % d[7]);
        p->u.phys.vel.z = p->u.phys.vel.z / lbl_3_rodata_3930;
        i++;
        p = p->next;
    } while (p != NULL);
}

// .text:0x0014A62C size:0x2E0 mapped:0x807896C0
void fn_3_14A62C(f32* v) {
    Emitter* o;
    s32* d;
    s32 i;
    Particle* p;
    f32 ang;
    f32 c;
    o = fn_80033A24((EmitterUpdateFn)fn_3_14A188, 0x80, 0, lbl_3_data_26E40[1], 1, 0x24);
    if (o != NULL) {
        o->tex = MG_ASSETS.textures[2];
        p = o->particles;
        d = lbl_3_data_26E40;
        i = 0;
        do {
            p->texIndex = *d;
            p->uvFrame = 0;
            p->life = d[2];
            p->delay = 0;
            p->pos.x = v[0];
            p->pos.y = -v[1];
            p->pos.z = v[2];
            ang = (f32)(u32)(0x168 / lbl_3_data_26E40[1] * i);
            ang = lbl_3_rodata_39B8 * ang;
            c = (f32)cos(ang);
            p->pos.x = p->pos.x + (f32)d[3] * c / lbl_3_rodata_3930;
            c = (f32)sin(ang);
            p->pos.y = p->pos.y + (f32)d[3] * c / lbl_3_rodata_3930;
            p->sizeX = p->sizeY = (f32)d[5] / lbl_3_rodata_3930;
            p->color.c.b = 0xFF;
            p->color.c.g = 0xFF;
            p->color.c.r = 0xFF;
            p->color.c.a = d[9];
            p->u.phys.vel.x = lbl_3_rodata_3934[0];
            p->u.phys.vel.y = (f32)(d[12] - rand() % d[13]);
            p->u.phys.vel.y = p->u.phys.vel.y / lbl_3_rodata_3930;
            p->u.phys.vel.y = p->u.phys.vel.y * (f32)(-(rand() % 2 * 2) + 1);
            p->u.phys.vel.z = (f32)(d[6] - rand() % d[7]);
            p->u.phys.vel.z = p->u.phys.vel.z / lbl_3_rodata_3930;
            i++;
            p = p->next;
        } while (p != NULL);
    }
}

// .text:0x0014A90C size:0x310 mapped:0x807899A0
void fn_3_14A90C(f32* v) {
    Emitter* o;
    s32* d;
    s32 i;
    Particle* p;
    f32 ang;
    f32 c;
    if (g_d_GameSettings.GameModeSelected == 7 && g_Minigame.GameMode_MiniGame == 3 && v != NULL) {
    o = fn_80033A24((EmitterUpdateFn)fn_3_14A188, 0x80, 0, lbl_3_data_26E40[1], 1, 0x24);
    if (o != NULL) {
        o->tex = MG_ASSETS.textures[2];
        p = o->particles;
        d = lbl_3_data_26E40;
        i = 0;
        do {
            p->texIndex = *d;
            p->uvFrame = 0;
            p->life = d[2];
            p->delay = 0;
            p->pos.x = v[0];
            p->pos.y = -v[1];
            p->pos.z = v[2];
            ang = (f32)(u32)(0x168 / lbl_3_data_26E40[1] * i);
            ang = lbl_3_rodata_39B8 * ang;
            c = (f32)cos(ang);
            p->pos.x = p->pos.x + (f32)d[3] * c / lbl_3_rodata_3930;
            c = (f32)sin(ang);
            p->pos.y = p->pos.y + (f32)d[3] * c / lbl_3_rodata_3930;
            p->sizeX = p->sizeY = (f32)d[5] / lbl_3_rodata_3930;
            p->color.c.b = 0xFF;
            p->color.c.g = 0xFF;
            p->color.c.r = 0xFF;
            p->color.c.a = d[9];
            p->u.phys.vel.x = lbl_3_rodata_3934[0];
            p->u.phys.vel.y = (f32)(d[12] - rand() % d[13]);
            p->u.phys.vel.y = p->u.phys.vel.y / lbl_3_rodata_3930;
            p->u.phys.vel.y = p->u.phys.vel.y * (f32)(-(rand() % 2 * 2) + 1);
            p->u.phys.vel.z = (f32)(d[6] - rand() % d[7]);
            p->u.phys.vel.z = p->u.phys.vel.z / lbl_3_rodata_3930;
            i++;
            p = p->next;
        } while (p != NULL);
    }
    }
}

// .text:0x0014AC1C size:0x24 mapped:0x80789CB0
void fn_3_14AC1C(void) {
    pitchingMachinePitching(0x23);
}

// NONMATCHING 99%: 14B3F4/14B248 inlined; only FPR numbering of the inlined 14B248 angle/radius temps differs
// .text:0x0014AC40 size:0x608 mapped:0x80789CD4
#if NONMATCHING
u32 fn_3_14AC40(Emitter* o) {
    Particle* p;
    s32 da;
    f32 ds;
    s32 a;
    if (lbl_80366158._28 != 0) {
        return 0;
    }
    fn_80033620(o);
    p = o->particles;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
    if (lbl_80366158._28 == 0) {
        fn_3_14B3F4(o);
        o->u.sweep.left -= 1;
    }
    da = (lbl_3_data_26E24[6] - lbl_3_data_26E24[5]) / lbl_3_data_26E24[1] * 2;
    ds = lbl_3_rodata_39C4 * ((f32)(lbl_3_data_26E24[4] - lbl_3_data_26E24[3]) / lbl_3_rodata_3930 /
                              (f32)lbl_3_data_26E24[1]);
    do {
        if (p->life != 0) {
            if (p->delay > 0) {
                p->delay -= 1;
                if (p->delay == 0) {
                    fn_3_14B248(o, p);
                }
            } else {
                fn_8003403C(p->sizeX, p->sizeY);
                fn_80033CC8(p, o->tex);
                a = p->color.c.a;
                if (lbl_3_data_26E24[1] / p->life < 2) {
                    ds = __fabs(ds);
                    da = __fabs(da);
                } else {
                    ds = lbl_3_rodata_39D0 * __fabs(ds);
                    da = lbl_3_rodata_39D0 * __fabs(da);
                }
                a += da;
                if (a > 0xFF) {
                    a = 0xFF;
                }
                if (a < 0) {
                    a = 0;
                }
                p->sizeX += ds;
                p->sizeY = p->sizeX;
                p->color.c.a = a;
                p->life -= 1;
                if (p->life == 0) {
                    fn_3_14B248(o, p);
                }
            }
        }
        p = p->next;
    } while (p != NULL);
    return o->u.sweep.left == 0;
}
#endif

#pragma dont_inline off
// .text:0x0014B248 size:0x1AC mapped:0x8078A2DC
void fn_3_14B248(Emitter* a, Particle* b) {
    f32 c;
    f32 sn;
    f32 ang;
    f32 r;
    f32 d;
    f32 px;
    f32 py;
    d = (f32)lbl_3_data_26E24[3] / lbl_3_rodata_3930;
    b->sizeY = d;
    b->sizeX = d;
    b->color.c.a = lbl_3_data_26E24[5];
    ang = lbl_3_rodata_39B8 * (f32)(rand() % 360);
    r = (f32)((f64)((u32)rand() % 200) / lbl_3_rodata_39C8);
    c = (f32)cos(ang);
    px = r * c;
    sn = (f32)sin(ang);
    py = r * sn;
    b->pos.x = a->u.t1.dir.x + px;
    b->pos.y = a->u.t1.dir.y + py;
    b->pos.z = a->u.t1.dir.z + lbl_3_rodata_3934[0];
    b->life = lbl_3_data_26E24[1];
}

// .text:0x0014B3F4 size:0x148 mapped:0x8078A488
void fn_3_14B3F4(Emitter* a) {
    f32* p;
    f32* q;
    f32 t;
    f32 s;
    s32 d = a->u.sweep.total - a->u.sweep.left;
    f32 len = a->u.sweep.len;
    if ((f32)d < len) {
        p = &lbl_3_data_26E00[0].x;
        q = &lbl_3_data_26E00[1].x;
        t = (f32)d / len;
    } else {
        p = &lbl_3_data_26E00[1].x;
        q = &lbl_3_data_26E00[2].x;
        t = (f32)d / ((f32)a->u.sweep.total - len);
    }
    s = fn_3_119D28();
    a->u.sweep.pos.x = s * (p[0] * (1.0f - t) + q[0] * t) + a->u.sweep.origin.x;
    a->u.sweep.pos.y = s * (p[1] * (1.0f - t) + q[1] * t) + a->u.sweep.origin.y;
    a->u.sweep.pos.z = s * (p[2] * (1.0f - t) + q[2] * t) + a->u.sweep.origin.z;
}
#pragma dont_inline on

// NONMATCHING 99%: 14B3F4/14B248 inlined; only f28/f29 swapped for the angle and cos() result of the inlined 14B248
// .text:0x0014B53C size:0x3F0 mapped:0x8078A5D0
#pragma dont_inline off
#if NONMATCHING
void fn_3_14B53C(Emitter* o, u32 n, Vec* pos) {
    Vec d;
    f32 len;
    f32 len2;
    Particle* p;
    s32 i;
    o->u.sweep.origin = *pos;
    i = 0;
    o->tex = MG_ASSETS.textures[2];
    o->u.sweep.total = n;
    o->u.sweep.left = n;
    PSVECSubtract((Vec*)lbl_3_data_26E00, &lbl_3_data_26E00[1], &d);
    len = PSVECMag(&d);
    PSVECSubtract(&lbl_3_data_26E00[1], &lbl_3_data_26E00[2], &d);
    len2 = PSVECMag(&d);
    o->u.sweep.len = len / ((len2 + len) / (f32)n);
    fn_3_14B3F4(o);
    p = o->particles;
    do {
        p->texIndex = lbl_3_data_26E24[0];
        p->uvFrame = 0;
        p->delay = (f32)i * ((f32)o->u.sweep.total / (f32)lbl_3_data_26E24[2]);
        p->color.c.b = 0xFF;
        p->color.c.g = 0xFF;
        p->color.c.r = 0xFF;
        p->life = lbl_3_data_26E24[1];
        if (p->delay == 0) {
            fn_3_14B248(o, p);
        }
        p = p->next;
        i++;
    } while (p != NULL);
}
#endif
#pragma dont_inline on

// .text:0x0014B92C size:0x74 mapped:0x8078A9C0
void fn_3_14B92C(u32 a, Vec* b) {
    Emitter* p = fn_80033A24((EmitterUpdateFn)fn_3_14AC40, 0x80, 0, lbl_3_data_26E24[2], 1, 0x23);
    if (p != 0) {
        fn_3_14B53C(p, a, b);
    }
}

// .text:0x0014B9A0 size:0x50 mapped:0x8078AA34
void fn_3_14B9A0(u32 a, Vec* b) {
    if (g_d_GameSettings.GameModeSelected == 7 && g_Minigame.GameMode_MiniGame == 3 && b != NULL) {
        fn_3_14B92C(a, b);
    }
}

// .text:0x0014B9F0 size:0x50 mapped:0x8078AA84
void fn_3_14B9F0(void) {
    Emitter* e = fn_800339F0(0, 0x22);
    Particle* p;
    if (e != NULL) {
        p = e->particles;
        do {
            p->life = 0;
            p = p->next;
        } while (p != NULL);
    }
    pitchingMachinePitching(0x22);
}

// .text:0x0014BA40 size:0x270 mapped:0x8078AAD4
u32 fn_3_14BA40(Emitter* o) {
    s32 s;
    s32* d;
    Particle* p;
    Particle** pp;
    Particle* first;
    Particle* prev;
    s32 t26;
    s32 n;
    s32 a;
    s32 t23;
    Particle* q;
    Particle* t;
    s32 delta;
    f32 df;
    n = 0;
    if (lbl_80366158._28 != 0) {
        return 0;
    }
    t = fn_80031F34(o->particles, o->count);
    o->particles = t;
    p = t;
    pp = &o->particles;
    prev = NULL;
    first = NULL;
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    do {
        if (p->life != 0) {
            if (p->uvOrder == 0) {
                d = lbl_3_data_26D88;
            } else {
                d = lbl_3_data_26DC4;
            }
            t23 = d[2];
            t26 = d[3];
            fn_8003403C(p->sizeX, p->sizeY);
            fn_80033CC8(p, o->tex);
            a = p->color.c.a;
            if (t23 - p->life < t26) {
                df = (f32)((d[5] - d[4]) / t26) / lbl_3_rodata_3930;
                delta = (d[11] - d[10]) / t26;
            } else {
                s = t23 - t26;
                df = (f32)((d[6] - d[5]) / s) / lbl_3_rodata_3930;
                delta = (d[12] - d[11]) / s;
            }
            a += delta;
            if (a > 0xFF) {
                a = 0xFF;
            }
            if (a < 0) {
                a = 0;
            }
            p->color.c.a = a;
            p->sizeX = p->sizeX + df;
            p->sizeY = p->sizeX;
            p->life -= 1;
            if (p->life == 0) {
                *pp = p->next;
                if (prev != NULL) {
                    prev->next = p;
                } else {
                    first = p;
                }
                prev = p;
                p->next = NULL;
                o->count--;
            } else {
                pp = &p->next;
                n++;
            }
        }
        p = *pp;
    } while (p != NULL);
    if (first != NULL) {
        q = first;
        do {
            q->unk4C = 0;
            q->delay = 0;
            q = q->next;
        } while (q != NULL);
        fn_80033794(first);
    }
    return n == 0;
}

#pragma dont_inline off
// .text:0x0014BCB0 size:0x21C mapped:0x8078AD44
void fn_3_14BCB0(Emitter* o, f32* v, u8 flag) {
    Particle* p;
    s32* d;
    u32 n;
    f32 t;
    f32 ang;
    f32 s;
    f32 c;
    f32 r;
    f64 u;
    o->tex = MG_ASSETS.textures[2];
    n = 0;
    p = o->particles;
    d = (flag != 0) ? lbl_3_data_26DC4 : lbl_3_data_26D88;
    do {
        if (p->life == 0) {
            p->texIndex = *d;
            p->uvFrame = 0;
            p->life = d[2];
            p->sizeX = p->sizeY = (f32)d[4] / lbl_3_rodata_3930;
            p->color.c.a = d[10];
            p->color.c.r = d[7];
            p->color.c.g = d[8];
            p->color.c.b = d[9];
            t = (f32)rand() / lbl_3_rodata_3970;
            u = (f64)t - lbl_3_rodata_3968;
            u = lbl_3_rodata_3990 * u;
            r = lbl_3_rodata_39C4 * u;
            ang = lbl_3_rodata_39B8 * (f32)(180.0 / (f64)d[1] * (f64)n);
            c = (f32)cos(ang);
            p->pos.x = r * c + v[0];
            s = (f32)sin(ang);
            n++;
            p->pos.y = (f32)((f64)(v[1] - r * s) - lbl_3_rodata_3978);
            p->pos.z = v[2];
            p->uvOrder = flag;
        }
        p = p->next;
    } while (p != NULL && n < (u32)lbl_3_data_26D88[1]);
}
#pragma dont_inline on

// NONMATCHING 99%: 14BCB0 inlined twice; only f30/f31 (radius/angle) swapped in the first copy
// .text:0x0014BECC size:0x47C mapped:0x8078AF60
#pragma dont_inline off
#if NONMATCHING
void fn_3_14BECC(f32* v, u8 flag) {
    Emitter buf; // only its particle list is filled in
    Emitter* h;
    Emitter* n;
    Particle* p;
    h = fn_800339F0(NULL, 0x22);
    if (h != NULL) {
        n = fn_800337CC(&buf, lbl_3_data_26D88[1], 1);
        fn_3_14BCB0(n, v, flag);
        p = h->particles;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = n->particles;
        h->count += n->count;
    } else {
        n = fn_80033A24((EmitterUpdateFn)fn_3_14BA40, 0x80, 0, lbl_3_data_26D88[1], 1, 0x22);
        if (n != NULL) {
            fn_3_14BCB0(n, v, flag);
        }
    }
}
#endif
#pragma dont_inline on

// .text:0x0014C348 size:0x50 mapped:0x8078B3DC
void fn_3_14C348(f32* a, u8 b) {
    if (g_d_GameSettings.GameModeSelected == 7 && g_Minigame.GameMode_MiniGame == 2 && a != NULL) {
        fn_3_14BECC(a, b);
    }
}

// .text:0x0014C398 size:0x24 mapped:0x8078B42C
void fn_3_14C398(void) {
    pitchingMachinePitching(0x21);
}

// .text:0x0014C3BC size:0x10C mapped:0x8078B450
void fn_3_14C3BC(Particle* o) {
    Vec v;
    Mtx m;
    PSVECScale((Vec*)lbl_3_data_26D50, lbl_3_rodata_39E0, &v);
    PSMTXRotRad(m, 'Y', shortAngleToRad(g_Minigame._1AF8));
    PSMTXMultVec(m, &v, &v);
    o->pos.x = g_Minigame._1AE0 + v.x + (f32)lbl_3_data_26D5C[5] / 100000.0f * lbl_3_rodata_39A8;
    o->pos.y = v.y - ((f32)lbl_3_data_26D5C[5] / 100000.0f * lbl_3_rodata_39A8 + g_Minigame._1AE4);
    o->pos.z = g_Minigame._1AE8 + v.z;
}

// .text:0x0014C4C8 size:0x2D4 mapped:0x8078B55C
u32 fn_3_14C4C8(Emitter* o) {
    Mtx m;
    Vec dir;
    Particle* p;
    s32* d;
    s32 a;
    s32 s;
    s32 delta;
    f32 df;
    if (lbl_80366158._28 != 0) {
        return 0;
    }
    p = o->particles;
    if (p->life != 0) {
        GXSetZMode(1, 3, 0);
        GXSetBlendMode(1, 1, 1, 0);
        PSVECScale((Vec*)lbl_3_data_26D50, lbl_3_rodata_39E0, &dir);
        PSMTXRotRad(m, 'Y', shortAngleToRad(g_Minigame._1AF8));
        PSMTXMultVec(m, &dir, &dir);
        d = lbl_3_data_26D5C;
        p->pos.x = (f32)d[5] / 100000.0f * lbl_3_rodata_39A8 + (g_Minigame._1AE0 + dir.x);
        p->pos.y = dir.y - ((f32)d[5] / 100000.0f * lbl_3_rodata_39A8 + g_Minigame._1AE4);
        p->pos.z = g_Minigame._1AE8 + dir.z;
        fn_8003403C(p->sizeX, p->sizeY);
        fn_80033CC8(p, o->tex);
        a = p->color.c.a;
        s = lbl_3_data_26D5C[2] - lbl_3_data_26D5C[3];
        if (s < p->life) {
            df = (f32)(d[5] - lbl_3_data_26D5C[4]) / 100000.0f / (f32)lbl_3_data_26D5C[3];
            delta = (lbl_3_data_26D5C[8] - lbl_3_data_26D5C[7]) / lbl_3_data_26D5C[3];
        } else {
            df = (f32)(lbl_3_data_26D5C[6] - d[5]) / 100000.0f / (f32)s;
            delta = (lbl_3_data_26D5C[9] - lbl_3_data_26D5C[8]) / s;
        }
        a += delta;
        if (a < 0) {
            a = 0;
        }
        if (a > 0xFF) {
            a = 0xFF;
        }
        p->sizeX = p->sizeX + df;
        p->sizeY = p->sizeX;
        p->color.c.a = a;
        a = p->color.c.a;
        p->color.c.b = a;
        p->color.c.g = a;
        p->color.c.r = a;
        p->life = p->life - 1;
    } else {
        return 1;
    }
    return 0;
}

// .text:0x0014C79C size:0x94 mapped:0x8078B830
void fn_3_14C79C(Emitter* a) {
    Particle* p;
    f32 f;
    a->tex = MG_ASSETS.textures[2];
    p = a->particles;
    p->texIndex = lbl_3_data_26D5C[0];
    p->uvFrame = 0;
    p->life = lbl_3_data_26D5C[2];
    f = lbl_3_data_26D5C[4] / 100000.0f;
    p->sizeY = f;
    p->sizeX = f;
    p->color.c.a = lbl_3_data_26D5C[7];
    p->color.c.b = 0xFF;
    p->color.c.g = 0xFF;
    p->color.c.r = 0xFF;
}

// .text:0x0014C830 size:0xD4 mapped:0x8078B8C4
void fn_3_14C830(void) {
    Emitter* a = fn_80033A24((EmitterUpdateFn)fn_3_14C4C8, 0x80, 0, lbl_3_data_26D5C[1], 1, 0xA);
    Particle* p;
    f32 f;
    if (a != NULL) {
        a->tex = MG_ASSETS.textures[2];
        p = a->particles;
        p->texIndex = lbl_3_data_26D5C[0];
        p->uvFrame = 0;
        p->life = lbl_3_data_26D5C[2];
        f = lbl_3_data_26D5C[4] / 100000.0f;
        p->sizeY = f;
        p->sizeX = f;
        p->color.c.a = lbl_3_data_26D5C[7];
        p->color.c.b = 0xFF;
        p->color.c.g = 0xFF;
        p->color.c.r = 0xFF;
    }
}

// .text:0x0014C904 size:0xFC mapped:0x8078B998
void fn_3_14C904(void) {
    Emitter* a;
    Particle* p;
    f32 f;
    if (g_d_GameSettings.GameModeSelected == 7 && g_Minigame.GameMode_MiniGame == 4) {
        a = fn_80033A24((EmitterUpdateFn)fn_3_14C4C8, 0x80, 0, lbl_3_data_26D5C[1], 1, 0xA);
        if (a != NULL) {
            a->tex = MG_ASSETS.textures[2];
            p = a->particles;
            p->texIndex = lbl_3_data_26D5C[0];
            p->uvFrame = 0;
            p->life = lbl_3_data_26D5C[2];
            f = lbl_3_data_26D5C[4] / 100000.0f;
            p->sizeY = f;
            p->sizeX = f;
            p->color.c.a = lbl_3_data_26D5C[7];
            p->color.c.b = 0xFF;
            p->color.c.g = 0xFF;
            p->color.c.r = 0xFF;
        }
    }
}

// .text:0x0014CA00 size:0x98 mapped:0x8078BA94
void fn_3_14CA00(void) {
    u32 i = 0;
    do {
        Emitter* h = fn_800339F0(0, 0x20);
        if (h != 0) {
            Particle* n = h->particles;
            do {
                if (n->colorStep.v[1] == (s8)i) {
                    n->colorStep.v[0] = 0;
                    n->colorStep.v[1] = 0xFF;
                    n->life = 0;
                    n->unk4C = 0;
                }
                n = n->next;
            } while (n != 0);
        }
        i++;
    } while (i < 0xF);
    pitchingMachinePitching(0x20);
}

// .text:0x0014CA98 size:0x1C mapped:0x8078BB2C
void fn_3_14CA98(Particle* p) {
    p->colorStep.v[0] = 0;
    p->colorStep.v[1] = 0xFF;
    p->life = 0;
    p->unk4C = 0;
}

// .text:0x0014CAB4 size:0x74 mapped:0x8078BB48
void fn_3_14CAB4(s8 a) {
    Emitter* p = fn_800339F0(0, 0x20);
    if (p != NULL) {
        Particle* q = p->particles;
        do {
            if (q->colorStep.v[1] == a) {
                q->colorStep.v[0] = 0;
                q->colorStep.v[1] = 0xFF;
                q->life = 0;
                q->unk4C = 0;
            }
            q = q->next;
        } while (q != NULL);
    }
}

// .text:0x0014CB28 size:0x8C mapped:0x8078BBBC
void fn_3_14CB28(s8 a) {
    Emitter* e; Particle* p; s32 id;
    if (a >= 0xF || a < 0) {
        return;
    }
    e = fn_800339F0(0, 0x20);
    if (e != NULL) {
        p = e->particles;
        id = a;
        do {
            if (p->colorStep.v[1] == id) {
                p->colorStep.v[0] = 0;
                p->colorStep.v[1] = 0xFF;
                p->life = 0;
                p->unk4C = 0;
            }
            p = p->next;
        } while (p != NULL);
    }
}

// .text:0x0014CBB4 size:0x18C mapped:0x8078BC48
#pragma dont_inline off
void fn_3_14CBB4(Emitter* a, Particle* o) {
    s32 delta;
    f32 df;
    s32 c;
    GXSetBlendMode(1, 4, 5, 0);
    fn_8003403C(o->sizeX, o->sizeY);
    fn_80033CC8(o, a->tex);
    c = o->color.c.a;
    if (-o->delay < lbl_3_data_26D00[10]) {
        df = ((f32)lbl_3_data_26D00[12] / lbl_3_rodata_3930) / (f32)lbl_3_data_26D00[10];
        delta = lbl_3_data_26D00[15] / lbl_3_data_26D00[10];
    } else {
        df = ((f32)(lbl_3_data_26D00[13] - lbl_3_data_26D00[12]) / lbl_3_rodata_3930) / (f32)(lbl_3_data_26D00[18] - lbl_3_data_26D00[10]);
        delta = (lbl_3_data_26D00[16] - lbl_3_data_26D00[15]) / (lbl_3_data_26D00[18] - lbl_3_data_26D00[10]);
    }
    c += delta;
    if (c > 0xFF) {
        c = 0xFF;
    } else if (c < 0) {
        c = 0;
    }
    o->color.c.a = c;
    o->color.c.r = o->color.c.g = o->color.c.b = o->color.c.a;
    o->sizeX = o->sizeX + df;
    o->sizeY = o->sizeX;
}
#pragma dont_inline on

// .text:0x0014CD40 size:0x18C mapped:0x8078BDD4
#pragma dont_inline off
void fn_3_14CD40(Emitter* a, Particle* o) {
    s32 delta;
    f32 df;
    s32 c;
    GXSetBlendMode(1, 1, 1, 0);
    fn_8003403C(o->sizeX, o->sizeY);
    fn_80033CC8(o, a->tex);
    c = o->color.c.a;
    if (-o->delay < lbl_3_data_26D00[3]) {
        df = ((f32)lbl_3_data_26D00[5] / lbl_3_rodata_3930) / (f32)lbl_3_data_26D00[3];
        delta = lbl_3_data_26D00[8] / lbl_3_data_26D00[3];
    } else {
        df = ((f32)(lbl_3_data_26D00[6] - lbl_3_data_26D00[5]) / lbl_3_rodata_3930) / (f32)(lbl_3_data_26D00[17] - lbl_3_data_26D00[3]);
        delta = (lbl_3_data_26D00[9] - lbl_3_data_26D00[8]) / (lbl_3_data_26D00[17] - lbl_3_data_26D00[3]);
    }
    c += delta;
    if (c > 0xFF) {
        c = 0xFF;
    } else if (c < 0) {
        c = 0;
    }
    o->color.c.a = c;
    o->color.c.r = o->color.c.g = o->color.c.b = o->color.c.a;
    o->sizeX = o->sizeX + df;
    o->sizeY = o->sizeX;
}
#pragma dont_inline on

// NONMATCHING 99%: only the lbl_80366158 flag address (orig lis/addi r4 scheduled before the reg saves, ours addi r3 after mr), same as fn_3_14A188; 14CD40/14CBB4/14D2C0 are inlined via dont_inline off
// .text:0x0014CECC size:0x3F4 mapped:0x8078BF60
#pragma dont_inline off
u32 fn_3_14CECC(Emitter* o) {
    Particle* p;
    if (lbl_80366158._28 != 0) {
        return 0;
    }
    fn_80033620(o);
    p = o->particles;
    GXSetZMode(1, 3, 0);
    do {
        if (p->colorStep.v[0] != 0 && p->life != 0) {
            if (p->delay <= 0) {
                if (p->colorStep.v[0] == 1) {
                    fn_3_14CD40(o, p);
                } else {
                    if (p->delay == 0) {
                        fn_3_14D2C0(p);
                    }
                    fn_3_14CBB4(o, p);
                }
                p->life -= 1;
                if (p->life == 0) {
                    p->colorStep.v[0] = 0;
                    p->colorStep.v[1] = 0xFF;
                    p->life = 0;
                    p->unk4C = 0;
                }
            }
            p->delay -= 1;
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}
#pragma dont_inline on

// .text:0x0014D2C0 size:0x58 mapped:0x8078C354
#pragma dont_inline off
void fn_3_14D2C0(Particle* p) {
    // objects[p->colorStep.v[1] + 0x10].actor, indexed by bytes as the original does
    GameBone** arr = *(GameBone***)((u8*)lbl_8036E548.slots68 + (p->colorStep.v[1] + 0x10) * sizeof(ActorObject) +
                                   OFFSET_OF(ActorObjectTable, objects));
    GameBone* e;
    arr = ((GameActor*)arr)->boneArray;
    e = arr[p->colorStep.v[2]];
    p->pos.x = e->forwardMtx[0][3];
    p->pos.y = e->forwardMtx[1][3];
    p->pos.z = e->forwardMtx[2][3];
}
#pragma dont_inline on

// .text:0x0014D318 size:0x134 mapped:0x8078C3AC
void fn_3_14D318(Particle* a) {
    f32* q = &g_Minigame.barrels[a->colorStep.v[1]].currentPos.x;
    f32* d = lbl_3_data_21770; f32 h = 0.5f;
    a->pos.x = q[0];
    a->pos.y = -(d[3] * h + q[1]);
    a->pos.z = q[2];
    a->pos.x = a->pos.x + (rand() % 100 - 50) / 100.0;
    a->pos.y = a->pos.y + (rand() % 100 - 50) / 100.0;
}

// fn_3_14D44C body for fn_3_14D710, which inlines it twice (CW will not auto-inline the real one)
static inline void Inl14D44C(Emitter* a, u8 kind) {
    Particle* p = a->particles;
    s32 n = 0;
    do {
        if (p->colorStep.v[0] == 0 && p->life == 0) {
            if (n < 3) {
                f32* d = lbl_3_data_21770;
                f32* q;
                f32 h = 0.5f;
                p->colorStep.v[0] = 1;
                p->colorStep.v[1] = kind;
                p->colorStep.v[2] = 0xFF;
                p->texIndex = lbl_3_data_26D00[0];
                p->sizeX = p->sizeY = (f32)lbl_3_data_26D00[4];
                p->color.c.a = lbl_3_data_26D00[7];
                q = &g_Minigame.barrels[p->colorStep.v[1]].currentPos.x;
                p->pos.x = q[0];
                p->pos.y = -(d[3] * h + q[1]);
                p->pos.z = q[2];
                p->pos.x = p->pos.x + (rand() % 100 - 50) / 100.0;
                p->pos.y = p->pos.y + (rand() % 100 - 50) / 100.0;
                p->life = lbl_3_data_26D00[17];
                p->delay = 0;
            } else {
                p->colorStep.v[0] = 2;
                p->colorStep.v[1] = kind;
                p->colorStep.v[2] = (n - 3) / 5;
                p->texIndex = lbl_3_data_26D00[1];
                p->sizeX = p->sizeY = (f32)lbl_3_data_26D00[11];
                p->color.c.a = lbl_3_data_26D00[14];
                p->delay = (n - 3) % 5 * 4 + 1;
                p->life = lbl_3_data_26D00[18];
            }
            n++;
            p->color.c.r = p->color.c.g = p->color.c.b = 0xFF;
        }
        p = p->next;
    } while (p != NULL && n < 0x2B);
}

#pragma dont_inline off
// .text:0x0014D44C size:0x288 mapped:0x8078C4E0
void fn_3_14D44C(Emitter* a, u32 kind0) {
    u8 kind = kind0;
    Particle* p = a->particles;
    s32 n = 0;
    do {
        if (p->colorStep.v[0] == 0 && p->life == 0) {
            if (n < 3) {
                f32* d = lbl_3_data_21770;
                f32* q;
                f32 h = 0.5f;
                p->colorStep.v[0] = 1;
                p->colorStep.v[1] = kind;
                p->colorStep.v[2] = 0xFF;
                p->texIndex = lbl_3_data_26D00[0];
                p->sizeX = p->sizeY = (f32)lbl_3_data_26D00[4];
                p->color.c.a = lbl_3_data_26D00[7];
                q = &g_Minigame.barrels[p->colorStep.v[1]].currentPos.x;
                p->pos.x = q[0];
                p->pos.y = -(d[3] * h + q[1]);
                p->pos.z = q[2];
                p->pos.x = p->pos.x + (rand() % 100 - 50) / 100.0;
                p->pos.y = p->pos.y + (rand() % 100 - 50) / 100.0;
                p->life = lbl_3_data_26D00[17];
                p->delay = 0;
            } else {
                p->colorStep.v[0] = 2;
                p->colorStep.v[1] = kind;
                p->colorStep.v[2] = (n - 3) / 5;
                p->texIndex = lbl_3_data_26D00[1];
                p->sizeX = p->sizeY = (f32)lbl_3_data_26D00[11];
                p->color.c.a = lbl_3_data_26D00[14];
                p->delay = (n - 3) % 5 * 4 + 1;
                p->life = lbl_3_data_26D00[18];
            }
            n++;
            p->color.c.r = p->color.c.g = p->color.c.b = 0xFF;
        }
        p = p->next;
    } while (p != NULL && n < 0x2B);
}

// .text:0x0014D6D4 size:0x3C mapped:0x8078C768

void fn_3_14D6D4(Emitter* e) {
    Particle* p;
    e->tex = MG_ASSETS.textures[2];
    p = e->particles;
    do {
        p->colorStep.v[2] = 0;
        p->colorStep.v[1] = 0;
        p->colorStep.v[0] = 0;
        p->life = 0;
        p->uvFrame = 0;
        p = p->next;
    } while (p != NULL);
}

// .text:0x0014D710 size:0x570 mapped:0x8078C7A4
void fn_3_14D710(s8 a) {
    Emitter* e = fn_800339F0(NULL, 0x20);
    if (e != NULL) {
        Inl14D44C(e, a);
    } else {
        e = fn_80033A24((EmitterUpdateFn)fn_3_14CECC, 0xF0, 0, lbl_3_data_26D00[2], 1, 0x20);
        if (e != NULL) {
            fn_3_14D6D4(e);
            Inl14D44C(e, a);
        }
    }
}
#pragma dont_inline on

// .text:0x0014DC80 size:0x60 mapped:0x8078CD14
void fn_3_14DC80(s8 a) {
    if (g_d_GameSettings.GameModeSelected != 7 || g_Minigame.GameMode_MiniGame != 3 || a >= 0xF || a < 0) {
        return;
    }
    fn_3_14D710(a);
}

// .text:0x0014DCE0 size:0x24 mapped:0x8078CD74
void fn_3_14DCE0(void) {
    pitchingMachinePitching(0x1F);
}

// .text:0x0014DD04 size:0x268 mapped:0x8078CD98
u32 fn_3_14DD04(Emitter* o) {
    Particle* t;
    s32* d;
    Particle* p;
    Particle** pp;
    Particle* prev;
    s32 n;
    s32 a;
    s32 t8;
    s32 delta;
    f32 df;
    n = 0;
    t = fn_80031F34(o->particles, o->count);
    o->particles = t;
    p = t;
    pp = &o->particles;
    prev = NULL;
    GXSetZMode(1, 3, 1);
    GXSetBlendMode(1, 4, 6, 0);
    d = lbl_3_data_26CD0;
    do {
        if (p->life != 0) {
            fn_8003403C(p->sizeX, p->sizeY);
            fn_80033CC8(p, o->tex);
            p->pos.y = p->pos.y - p->u.phys.vel.y;
            p->u.phys.vel.y = p->u.phys.vel.y - (f32)d[10] / lbl_3_rodata_3930;
            a = p->color.c.a;
            t8 = d[2];
            if (t8 / p->life < 2) {
                df = p->u.phys.accel.x * ((f32)(d[4] - d[3]) / lbl_3_rodata_3930 / (f32)(t8 / 2));
                delta = (d[7] - d[6]) / (t8 / 2);
            } else {
                df = p->u.phys.accel.x * ((f32)(d[5] - d[4]) / lbl_3_rodata_3930 / (f32)(t8 / 2));
                delta = (d[8] - d[7]) / (t8 / 2);
            }
            a += delta;
            p->sizeX = p->sizeX + df;
            p->sizeY = p->sizeX;
            if (a < 0) {
                a = 0;
            } else if (a > 0xFF) {
                a = 0xFF;
            }
            p->color.c.a = a;
            p->life -= 1;
            if (p->life == 0) {
                *pp = p->next;
                if (prev != NULL) {
                    prev->next = p;
                }
                prev = p;
                p->next = NULL;
                o->count--;
            } else {
                pp = &p->next;
                n++;
            }
        }
        p = *pp;
    } while (p != NULL);
    return n == 0;
}

#pragma dont_inline off
// .text:0x0014DF6C size:0x2C8 mapped:0x8078D000
void fn_3_14DF6C(Emitter* o, f32* v) {
    Particle* p;
    s32* d;
    f32 h;
    f32 t;
    s32 n;
    s32 r;
    p = o->particles;
    o->tex = MG_ASSETS.textures[2];
    d = lbl_3_data_26CD0;
    do {
        p->texIndex = *d;
        p->uvFrame = 0;
        p->pos.x = v[0] + (f32)(rand() % 1000 - 500) / lbl_3_rodata_39C0;
        p->pos.y = -(lbl_3_rodata_39E0 + v[1]);
        p->pos.z = v[2] + (f32)(rand() % 1000 - 500) / lbl_3_rodata_39C0;
        p->u.phys.vel.z = lbl_3_rodata_3934[0];
        p->u.phys.vel.x = lbl_3_rodata_3934[0];
        p->u.phys.vel.y = (f32)d[9] / lbl_3_rodata_3930;
        h = p->u.phys.vel.y;
        t = -(lbl_3_rodata_39C0 * (h * lbl_3_rodata_39F0) - (f32)(rand() % (s32)(lbl_3_rodata_39C0 * (h * lbl_3_rodata_39A8)))) / lbl_3_rodata_39C0;
        p->u.phys.vel.y = p->u.phys.vel.y + t;
        p->color.c.b = 0xFF;
        p->color.c.g = 0xFF;
        p->color.c.r = 0xFF;
        p->color.c.a = d[6];
        p->u.phys.accel.x = (f32)(rand() % 1000 + 500) / lbl_3_rodata_39C0;
        h = (f32)d[3] / lbl_3_rodata_3930;
        p->sizeX = p->sizeY = h * p->u.phys.accel.x;
        p->life = d[2];
        p->delay = 0;
        p = p->next;
    } while (p != NULL);
}

// .text:0x0014E234 size:0x58C mapped:0x8078D2C8
void fn_3_14E234(f32* v) {
    Emitter buf; // only its particle list is filled in
    Emitter* h;
    Emitter* n;
    Particle* p;
    h = fn_800339F0(NULL, 0x1F);
    if (h != NULL) {
        n = fn_800337CC(&buf, lbl_3_data_26CD0[1], 1);
        if (n != NULL) {
            fn_3_14DF6C(n, v);
            p = h->particles;
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = n->particles;
            h->count += n->count;
        }
    } else {
        n = fn_80033A24((EmitterUpdateFn)fn_3_14DD04, 0x80, 0, lbl_3_data_26CD0[1], 1, 0x1F);
        if (n != NULL) {
            fn_3_14DF6C(n, v);
        }
    }
}
#pragma dont_inline on

// .text:0x0014E7C0 size:0x50 mapped:0x8078D854
void fn_3_14E7C0(f32* a) {
    if (g_d_GameSettings.GameModeSelected == 7 && g_Minigame.GameMode_MiniGame == 6 && a != NULL) {
        fn_3_14E234(a);
    }
}

// .text:0x0014E810 size:0x84 mapped:0x8078D8A4
void fn_3_14E810(void) {
    u32 i = 0;
    do {
        Emitter* p = fn_800339F0(0, 0x1E);
        if (p != NULL) {
            Particle* q = p->particles;
            s32 v = (s8)i + 1;
            do {
                if (q->unk4C == v) {
                    q->life = 0;
                }
                q = q->next;
            } while (q != NULL);
        }
        i++;
    } while (i < 4);
    pitchingMachinePitching(0x1E);
}

// NONMATCHING 94%: orig has `li r30,0; mr r31,r30` for the zero store reg (ours li r31)
// .text:0x0014E894 size:0x8C mapped:0x8078D928
#if NONMATCHING
void fn_3_14E894(void) {
    u32 i = 0;
    s16 z = 0;
    do {
        s8 k = i;
        Emitter* p = fn_800339F0(0, 0x1E);
        if (p != NULL) {
            Particle* q = p->particles;
            s32 v = k + 1;
            do {
                if (q->unk4C == v) {
                    q->life = z;
                }
                q = q->next;
            } while (q != NULL);
        }
        i++;
    } while (i < 4);
    pitchingMachinePitching(0x1E);
}
#endif

// .text:0x0014E920 size:0x68 mapped:0x8078D9B4
void fn_3_14E920(s8 a) {
    Emitter* p = fn_800339F0(0, 0x1E);
    if (p != NULL) {
        Particle* q = p->particles;
        s32 v = a + 1;
        do {
            if (q->unk4C == v) {
                q->life = 0;
            }
            q = q->next;
        } while (q != NULL);
    }
}

// .text:0x0014E988 size:0x68 mapped:0x8078DA1C
void fn_3_14E988(s8 a) {
    Emitter* p = fn_800339F0(0, 0x1E);
    if (p != NULL) {
        Particle* q = p->particles;
        s32 v = a + 1;
        do {
            if (q->unk4C == v) {
                q->life = 0;
            }
            q = q->next;
        } while (q != NULL);
    }
}

// .text:0x0014E9F0 size:0x104 mapped:0x8078DA84
void fn_3_14E9F0(Particle* a) {
    Vec v;
    if (a->unk4C < 5) {
        u8 k = lbl_3_data_26CB8[(u32)rand() % 23];
        v.z = 0.0f;
        v.y = 0.0f;
        v.x = 0.0f;
        if (fn_8001B728(a->unk4C - 1, k, &v) == 0) {
            memset(&v, 0, 0xC);
            fn_8001B728(a->unk4C - 1, 4, &v);
        }
    } else {
        v.x = g_Minigame._6E8;
        v.y = -g_Minigame._6EC;
        v.z = g_Minigame._6F0;
    }
    a->pos.x += v.x;
    a->pos.y += v.y;
    a->pos.z += v.z;
}

#pragma dont_inline off
// .text:0x0014EAF4 size:0x230 mapped:0x8078DB88
void fn_3_14EAF4(Particle* o) {
    Vec v = lbl_3_rodata_3914;
    Vec w;
    if (o->unk4C == 5) {
        v.x += (f32)(rand() % 10000 - 5000) / lbl_3_rodata_39F4;
        v.y += (f32)(rand() % 10000 - 5000) / lbl_3_rodata_39F4;
        o->pos.x = v.x;
        o->pos.y = v.y - lbl_3_rodata_39A8;
        o->pos.z = v.z;
    } else {
        o->pos.z = lbl_3_rodata_3934[0];
        o->pos.y = lbl_3_rodata_3934[0];
        o->pos.x = lbl_3_rodata_3934[0];
    }
    if (o->unk4C < 5) {
        u8 k = lbl_3_data_26CB8[(u32)rand() % 23];
        w.z = 0.0f;
        w.y = 0.0f;
        w.x = 0.0f;
        if (fn_8001B728(o->unk4C - 1, k, &w) == 0) {
            memset(&w, 0, 0xC);
            fn_8001B728(o->unk4C - 1, 4, &w);
        }
    } else {
        w.x = g_Minigame._6E8;
        w.y = -g_Minigame._6EC;
        w.z = g_Minigame._6F0;
    }
    o->pos.x += w.x;
    o->pos.y += w.y;
    o->pos.z += w.z;
}
#pragma dont_inline on

// NONMATCHING 93%: 14F544/14EAF4 inlined; the original keeps the lbl_3_data_26C94 base in a saved reg across the loop (pooled TU data), so register use and scheduling differ
// .text:0x0014ED24 size:0x6A8 mapped:0x8078DDB8
#pragma dont_inline off
#if NONMATCHING
u32 fn_3_14ED24(Emitter* o) {
    Particle* p;
    s32* d;
    s32 a;
    fn_80033620(o);
    p = o->particles;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    do {
        if (p->life != 0) {
            if (p->delay <= 0) {
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
                fn_8003403C(p->sizeX, p->sizeY);
                fn_80033CC8(p, o->tex);
                d = (s32*)lbl_3_data_26C94;
                if (d[7] / p->life < 2) {
                    a = p->color.c.a + d[6] / (d[7] / 2);
                    if (a > d[6]) {
                        a = d[6];
                    }
                    p->color.c.a = a;
                    p->sizeX += (f32)(d[3] - d[2]) / lbl_3_rodata_3930 / (f32)(d[7] / 2);
                    p->sizeY = p->sizeX;
                } else {
                    a = p->color.c.a - d[6] / (d[7] / 2);
                    if (a < d[5]) {
                        a = d[5];
                    }
                    p->color.c.a = a;
                    p->sizeX += (f32)(d[4] - d[3]) / lbl_3_rodata_3930 / (f32)(d[7] / 2);
                    p->sizeY = p->sizeX;
                }
                p->life -= 1;
                if (p->life == 0) {
                    fn_3_14F544(p);
                    fn_3_14EAF4(p);
                }
            } else {
                p->delay -= 1;
                if (p->delay == 0) {
                    fn_3_14EAF4(p);
                }
            }
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}
#endif
#pragma dont_inline on

// .text:0x0014F3CC size:0x178 mapped:0x8078E460
void fn_3_14F3CC(Particle* o) {
    Vec v = lbl_3_rodata_3908;
    f32 off;
    s16 r1, r2;
    if (o->unk4C < 5) {
        off = lbl_3_rodata_39F8;
    } else {
        off = lbl_3_rodata_39A8;
    }
    r1 = o->unk4C < 5 ? 20000 : 10000;
    r2 = o->unk4C < 5 ? 20000 : 10000;
    v.x += (f32)(rand() % r1 - r1 / 2) / lbl_3_rodata_39F4;
    v.y += (f32)(rand() % r2 - r2 / 2) / lbl_3_rodata_39F4;
    o->pos.x = v.x;
    o->pos.y = v.y - off;
    o->pos.z = v.z;
}

#pragma dont_inline off
// .text:0x0014F544 size:0x60 mapped:0x8078E5D8
void fn_3_14F544(Particle* a) {
    f32 f;
    a->life = lbl_3_data_26C94[7];
    a->color.c.a = lbl_3_data_26C94[5];
    f = lbl_3_data_26C94[2] / 100000.0f;
    a->sizeY = f;
    a->sizeX = f;
}
#pragma dont_inline on

// NONMATCHING 99%: 14F544/14EAF4 inlined; the two Vec temps get swapped stack slots and the life/i int->float conversions are scheduled in the other order
// .text:0x0014F5A4 size:0x32C mapped:0x8078E638
#pragma dont_inline off
#if NONMATCHING
void fn_3_14F5A4(Emitter* o, s8 a) {
    Particle* p;
    u32 i = 0;
    p = o->particles;
    do {
        if (p->unk4C == a + 1) {
            fn_3_14F544(p);
            p->delay = (f32)p->life / lbl_3_rodata_39FC * (f32)i;
            if (p->delay == 0) {
                fn_3_14EAF4(p);
            }
            p->color.c.b = 0xFF;
            i++;
            p->color.c.g = 0xFF;
            p->color.c.r = 0xFF;
            p->u.phys.mass = 0.0f;
        }
        p = p->next;
    } while (p != NULL);
}
#endif
#pragma dont_inline on

#pragma dont_inline off
// .text:0x0014F8D0 size:0x60 mapped:0x8078E964
void fn_3_14F8D0(Emitter* a) {
    Particle* p;
    u32 i = 0;
    a->tex = MG_ASSETS.textures[2];
    p = a->particles;
    do {
        p->uvOrder = 0;
        p->texIndex = lbl_3_data_26C94[0];
        p->uvFrame = 0;
        p->unk4C = i / 18 + 1;
        i++;
        p = p->next;
    } while (p != NULL);
}

// NONMATCHING 99% (with 14F5A4 unwrapped): 14F8D0/14F5A4 inlined; only the inherited 14F5A4 differences (Vec stack slots, int->float order)
// .text:0x0014F930 size:0x6E0 mapped:0x8078E9C4
#if NONMATCHING
void fn_3_14F930(s8 a) {
    Emitter* e = fn_800339F0(NULL, 0x1E);
    if (e != NULL) {
        fn_3_14F5A4(e, a);
    } else {
        e = fn_80033A24((EmitterUpdateFn)fn_3_14ED24, 0x80, 0, lbl_3_data_26C94[1], 1, 0x1E);
        if (e != NULL) {
            fn_3_14F8D0(e);
            fn_3_14F5A4(e, a);
        }
    }
}
#endif
#pragma dont_inline on

// .text:0x00150010 size:0x60 mapped:0x8078F0A4
void fn_3_150010(s8 a) {
    if (g_d_GameSettings.GameModeSelected != 7 || g_Minigame.GameMode_MiniGame != 6 || a > 4 || a < 0) { return; }
    fn_3_14F930(a);
}

// .text:0x00150070 size:0x58 mapped:0x8078F104
void fn_3_150070(void) {
    Emitter* e = fn_800339F0(0, 0x1D);
    Particle* p;
    if (e != NULL) {
        p = e->particles;
        do {
            p->life = 0;
            p->delay = 0;
            p->unk4C = 0;
            p = p->next;
        } while (p != NULL);
    }
    pitchingMachinePitching(0x1D);
}

// .text:0x001500C8 size:0x58 mapped:0x8078F15C
void fn_3_1500C8(void) {
    Emitter* e = fn_800339F0(0, 0x1D);
    Particle* p;
    if (e != NULL) {
        p = e->particles;
        do {
            p->life = 0;
            p->delay = 0;
            p->unk4C = 0;
            p = p->next;
        } while (p != NULL);
    }
    pitchingMachinePitching(0x1D);
}

static inline s32 rnd_range(s32* r) {
    s32 lo = r[0];
    return lo + rand() % (r[1] - lo);
}

#pragma dont_inline off
// NONMATCHING 99%: only the last rnd_range block schedules the 57.29578f/100000 constant loads in the other order
// .text:0x00150120 size:0x3CC mapped:0x8078F1B4
#if NONMATCHING
void fn_3_150120(Emitter* o, Particle* p) {
    f32 speed;
    f32 ang;
    if (p->delay != 0) {
        p->delay -= 1;
        return;
    }
    fn_80033F64(p->sizeX, p->sizeY, p->u.phys.accel.x);
    fn_80033CC8(p, o->tex);
    p->pos.x += p->u.phys.vel.x;
    p->pos.y -= p->u.phys.vel.y;
    p->pos.z += p->u.phys.vel.z;
    if (p->pos.y > 0.0f) {
        p->pos.y = 0.0f;
        p->u.phys.vel.y = -p->u.phys.vel.y * ((f32)lbl_3_data_26C3C[15] / lbl_3_rodata_3930);
    }
    if (--p->life == 0) {
        p->life = lbl_3_data_26C3C[20];
        p->pos.x = o->u.t1.pos.y;
        p->pos.y = -o->u.t1.pos.z;
        p->pos.z = o->u.t1.dir.x;
                p->sizeX = p->sizeY =
            (f32)rnd_range(&lbl_3_data_26C3C[10]) / lbl_3_rodata_3930;
                p->u.phys.vel.y = (f32)rnd_range(&lbl_3_data_26C3C[12]) / lbl_3_rodata_3930;
        ang = lbl_3_rodata_39B8 * (f32)((f64)(rand() % 36000) / lbl_3_rodata_39E8);
        speed = (f32)rnd_range(&lbl_3_data_26C3C[16]) / lbl_3_rodata_3930;
        p->u.phys.vel.x = speed * (f32)cos(ang);
        p->u.phys.vel.z = speed * (f32)sin(ang);
                p->u.phys.accel.x = lbl_3_rodata_39AC * ((f32)rnd_range(&lbl_3_data_26C3C[18]) / lbl_3_rodata_3930);
        p->u.phys.accel.x *= (f32)(-((rand() % 2) * 2) + 1);
        p->color.c.a = 0xFF;
        p->color.c.b = 0xFF;
        p->color.c.g = 0xFF;
        p->color.c.r = 0xFF;
    }
}
#endif
#pragma dont_inline on

// NONMATCHING 92%: respawn block (inlined twice) gets f29/f31 swapped for x/z, and the half-life divide is scheduled later in the fade branch
// .text:0x001504EC size:0x454 mapped:0x8078F580
#if NONMATCHING
static inline void respawn_1504EC(Emitter* o, Particle* p) {
    Mtx m;
    GameBone* obj;
    f32* src;
    f32 x;
    f32 y;
    f32 z;
    p->life = lbl_3_data_26C3C[6];
    obj = FOLLOW_OBJ(o)->actor->boneArray[lbl_3_data_26C3C[7]];
    PSMTXIdentity(m);
    src = (f32*)obj->forwardMtx;
    x = src[3];
    y = src[7];
    z = src[11];
    x += (rand() % 100 - 50) / lbl_3_rodata_39E8;
    y += (rand() % 150 - 75) / lbl_3_rodata_39E8;
    p->pos.x = x;
    p->pos.y = y;
    p->pos.z = z;
    p->sizeY = p->sizeX = lbl_3_data_26C3C[2];
    p->color.c.a = lbl_3_data_26C3C[4];
}

void fn_3_1504EC(Emitter* o, Particle* p) {
    s32 half;
    s32 da;
    f32 ds;
    s32 a;
    if (p->delay != 0) {
        p->delay -= 1;
        if (p->delay == 0) {
            respawn_1504EC(o, p);
        }
    } else {
        fn_8003403C(p->sizeX, p->sizeY);
        fn_80033CC8(p, o->tex);
        a = p->color.c.a;
        if (lbl_3_data_26C3C[6] / p->life < 2) {
            half = lbl_3_data_26C3C[6] / 2;
            da = lbl_3_data_26C3C[5] / half;
            ds = ((f32)lbl_3_data_26C3C[3] / lbl_3_rodata_3930) / (f32)half;
        } else {
            half = lbl_3_data_26C3C[6] / 2;
            da = -lbl_3_data_26C3C[5] / half;
            ds = -((f32)lbl_3_data_26C3C[3] / lbl_3_rodata_3930) / (f32)half;
        }
        a += da;
        if (a > 0xFF) {
            a = 0xFF;
        } else if (a < 0) {
            a = 0;
        }
        p->color.c.a = a;
        p->sizeX += ds;
        p->sizeY = p->sizeX;
        p->life -= 1;
        if (p->life == 0) {
            respawn_1504EC(o, p);
        }
    }
}
#endif

// NONMATCHING 98% (measured with 150120 unwrapped and inlined): o/p saved regs r28/r29 swapped, plus 150120's constant-load order
// .text:0x00150940 size:0x444 mapped:0x8078F9D4
#if NONMATCHING
u32 fn_3_150940(Emitter* o) {
    Particle* p;
    if (lbl_80366158._28 != 0) {
        return 0;
    }
    if (FOLLOW_OBJ(o)->animateBones == 0) {
        return 0;
    }
    fn_80033620(o);
    p = o->particles;
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 6, 0);
    do {
        if (p->life != 0) {
            if (p->unk4C == 1) {
                fn_3_1504EC(o, p);
            } else if (p->unk4C == 2) {
                fn_3_150120(o, p);
            }
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}
#endif

// .text:0x00150D84 size:0x2E4 mapped:0x8078FE18
void fn_3_150D84(Emitter* a, Particle* o) {
    s32* d;
    f32 ang;
    f32 s;
    d = (s32*)lbl_3_data_26C3C;
    o->life = d[20];
    o->pos.x = a->u.t1.pos.y;
    o->pos.y = -a->u.t1.pos.z;
    o->pos.z = a->u.t1.dir.x;
    o->sizeX = o->sizeY = (f32)(d[10] + rand() % (d[11] - d[10])) / lbl_3_rodata_3930;
    d = (s32*)lbl_3_data_26C3C;
    o->u.phys.vel.y = (f32)(d[12] + rand() % (d[13] - d[12])) / lbl_3_rodata_3930;
    d = (s32*)lbl_3_data_26C3C;
    ang = lbl_3_rodata_39B8 * (f32)((f64)(rand() % 36000) / lbl_3_rodata_39E8);
    d = (s32*)lbl_3_data_26C3C;
    s = (f32)(d[16] + rand() % (d[17] - d[16])) / lbl_3_rodata_3930;
    o->u.phys.vel.x = s * (f32)cos(ang);
    o->u.phys.vel.z = s * (f32)sin(ang);
    d = (s32*)lbl_3_data_26C3C;
    o->u.phys.accel.x = lbl_3_rodata_39AC * ((f32)(d[18] + rand() % (d[19] - d[18])) / lbl_3_rodata_3930);
    o->u.phys.accel.x = o->u.phys.accel.x * (f32)(-(rand() % 2 * 2) + 1);
    o->color.c.a = 0xFF;
    o->color.c.b = 0xFF;
    o->color.c.g = 0xFF;
    o->color.c.r = 0xFF;
}

// .text:0x00151068 size:0x19C mapped:0x807900FC
void fn_3_151068(Emitter* a, Particle* o) {
    Mtx m;
    GameBone* obj;
    MtxPtr mp;
    f32 x, y, z;
    s32* d = (s32*)lbl_3_data_26C3C;
    o->life = d[6];
    obj = FOLLOW_OBJ(a)->actor->boneArray[d[7]];
    PSMTXIdentity(m);
    mp = obj->forwardMtx;
    x = mp[0][3];
    y = mp[1][3];
    z = mp[2][3];
    x += (f64)(rand() % 100 - 50) / lbl_3_rodata_39E8;
    y += (f64)(rand() % 150 - 75) / lbl_3_rodata_39E8;
    o->pos.x = x;
    o->pos.y = y;
    o->pos.z = z;
    o->sizeY = o->sizeX = lbl_3_data_26C3C[2];
    o->color.c.a = lbl_3_data_26C3C[4];
}

// NONMATCHING 97% (with respawn_1504EC visible): CW hoists the rnd_range table addresses (d+0x2C, ...) into extra saved regs; otherwise only register numbering
// .text:0x00151204 size:0x490 mapped:0x80790298
#if NONMATCHING
void fn_3_151204(Emitter* o, void* owner, Vec* pos) {
    Particle* p;
    s32 i;
    s32 j;
    f32 ang;
    f32 speed;
    i = 0;
    j = 0;
    o->tex = MG_ASSETS.textures[2];
#ifdef TARGET_PC
    PTR32_SET(o->u.follow.obj, owner);
#else
    o->u.follow.obj = owner;
#endif
    memcpy(&o->u.t1.pos.y, pos, sizeof(Vec));
    p = o->particles;
    do {
        if (i < (u32)lbl_3_data_26C3C[1]) {
            p->delay = ++i;
            p->texIndex = lbl_3_data_26C3C[0];
            p->unk4C = 1;
            p->life = lbl_3_data_26C3C[6];
            if (p->delay == 0) {
                respawn_1504EC(o, p);
            }
        } else {
            p->delay = j++;
            p->texIndex = lbl_3_data_26C3C[8];
            p->unk4C = 2;
            p->life = lbl_3_data_26C3C[20];
            p->pos.x = o->u.t1.pos.y;
            p->pos.y = -o->u.t1.pos.z;
            p->pos.z = o->u.t1.dir.x;
            p->sizeX = p->sizeY =
                (f32)rnd_range(&lbl_3_data_26C3C[10]) / lbl_3_rodata_3930;
            p->u.phys.vel.y = (f32)rnd_range(&lbl_3_data_26C3C[12]) / lbl_3_rodata_3930;
            ang = lbl_3_rodata_39B8 * (f32)((f64)(rand() % 36000) / lbl_3_rodata_39E8);
            speed = (f32)rnd_range(&lbl_3_data_26C3C[16]) / lbl_3_rodata_3930;
            p->u.phys.vel.x = speed * (f32)cos(ang);
            p->u.phys.vel.z = speed * (f32)sin(ang);
            p->u.phys.accel.x = lbl_3_rodata_39AC * ((f32)rnd_range(&lbl_3_data_26C3C[18]) / lbl_3_rodata_3930);
            p->u.phys.accel.x *= (f32)(-((rand() % 2) * 2) + 1);
            p->color.c.a = 0xFF;
            p->color.c.b = 0xFF;
            p->color.c.g = 0xFF;
            p->color.c.r = 0xFF;
        }
        p->uvFrame = 0;
        p = p->next;
    } while (p != NULL);
}
#endif

// .text:0x00151694 size:0x7C mapped:0x80790728
void fn_3_151694(void* a, Vec* b) {
    Emitter* p = fn_80033A24((EmitterUpdateFn)fn_3_150940, 0x80, 0, lbl_3_data_26C3C[1] + lbl_3_data_26C3C[9], 1, 0x1D);
    if (p != 0) {
        fn_3_151204(p, a, b);
    }
}

// .text:0x00151710 size:0x50 mapped:0x807907A4
void fn_3_151710(void* a, Vec* b) {
    if (g_d_GameSettings.GameModeSelected == 7 && g_Minigame.GameMode_MiniGame == 2 && a != NULL) {
        fn_3_151694(a, b);
    }
}

// .text:0x00151760 size:0x38 mapped:0x807907F4
void fn_3_151760(void) {
    memset(lbl_3_bss_B894, 0, 0xF);
    pitchingMachinePitching(0x1C);
}

// .text:0x00151798 size:0x38 mapped:0x8079082C
void fn_3_151798(void) {
    memset(lbl_3_bss_B894, 0, 0xF);
    pitchingMachinePitching(0x1C);
}

// NONMATCHING 98%: only schedule order of the first lwz of the tx struct copy vs the hx/hy loads differs
// .text:0x001517D0 size:0x228 mapped:0x80790864
typedef struct { f32 f[8]; } Tex8;
extern const Tex8 lbl_3_rodata_38E8;

typedef struct { f32 u, v; } UV;
#if NONMATCHING
void fn_3_1517D0(Particle* a, Emitter* o) {
    Mtx m;
    Mtx44 m44;
    Vec vt[4];
    Tex8 tx;
    f32 hx;
    f32 hy;
    f32* p;
    UV* uv;
    s32 i;
    hx = a->sizeX * lbl_3_rodata_39A8;
    hy = a->sizeY * lbl_3_rodata_39A8;
    ((s32*)&tx)[0] = ((const s32*)&lbl_3_rodata_38E8)[0];
    ((s32*)&tx)[1] = ((const s32*)&lbl_3_rodata_38E8)[1];
    ((s32*)&tx)[2] = ((const s32*)&lbl_3_rodata_38E8)[2];
    ((s32*)&tx)[3] = ((const s32*)&lbl_3_rodata_38E8)[3];
    ((s32*)&tx)[4] = ((const s32*)&lbl_3_rodata_38E8)[4];
    ((s32*)&tx)[5] = ((const s32*)&lbl_3_rodata_38E8)[5];
    ((s32*)&tx)[6] = ((const s32*)&lbl_3_rodata_38E8)[6];
    ((s32*)&tx)[7] = ((const s32*)&lbl_3_rodata_38E8)[7];
    vt[0].x = -hx;
    vt[0].y = -hy;
    vt[1].x = hx;
    vt[1].y = -hy;
    vt[2].x = hx;
    vt[2].y = hy;
    vt[3].x = -hx;
    vt[3].y = hy;
    vt[3].z = 0.0f;
    vt[2].z = 0.0f;
    vt[1].z = 0.0f;
    vt[0].z = 0.0f;
    PSMTXIdentity(m);
    PSMTX44Identity(m44);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
    GXSetProjection(m44, 0);
    fn_80033B58(o->tex, a->texIndex, 0, 0);
    GXBegin(0x80, 0, 4);
    p = &vt[0].x;
    for (i = 0; i < 4; i++, p += 3) {
        GXPosition3f32(a->pos.x + p[0], a->pos.y + p[1], -1.0f);
        GXColor1u32(a->color.rgba);
        uv = &((UV*)&tx)[a->uvFrame + i];
        GXTexCoord2f32(uv->u, uv->v);
    }
    GXLoadPosMtxImm(fn_80052768_getCamera(0)->view, 0);
    GXSetCurrentMtx(0);
    GXSetProjection((void*)fn_80052768_getCamera(0), 0);
}
#endif

#pragma dont_inline off
// .text:0x001519F8 size:0x1B4 mapped:0x80790A8C
void fn_3_1519F8(Emitter* a, Particle* o) {
    Vec v;
    Vec dir;
    Vec ref;
    f32 mag;
    f32* tbl;
    fn_3_1517D0(o, a);
    if (lbl_80366158._28 != 0) {
        return;
    }
    PSVECAdd(&o->pos, &o->u.phys.vel, &o->pos);
    memcpy(&v, &o->pos, 0xC);
    tbl = &lbl_3_data_26C1C[1];
    v.x = lbl_3_data_26C1C[2 * o->colorStep.v[0]] - v.x;
    v.y = tbl[o->colorStep.v[0] * 2] - v.y;
    v.z = lbl_3_rodata_3934[0];
    PSVECNormalize(&v, &dir);
    mag = PSVECMag(&v);
    PSVECScale(&dir, lbl_3_rodata_3A00 * (lbl_3_rodata_392C / (mag * mag)), &v);
    PSVECAdd(&o->u.phys.vel, &v, &o->u.phys.vel);
    ref.x = lbl_3_data_26C1C[2 * o->colorStep.v[0]];
    ref.y = tbl[o->colorStep.v[0] * 2];
    ref.z = lbl_3_rodata_3934[0];
    PSVECNormalize(&ref, &ref);
    if (PSVECDotProduct(&dir, &ref) < lbl_3_rodata_3934[0] || mag == lbl_3_rodata_3934[0]) {
        o->life = 0;
    }
    if (o->life == 0 && o->colorStep.v[1] != 0) {
        fn_3_11F4B4(o->colorStep.v[0], o->texIndex == 1);
        o->colorStep.v[1] = 0;
    }
}

// .text:0x00151BAC size:0x1C0 mapped:0x80790C40
void fn_3_151BAC(Emitter* a, Particle* o) {
    s32 c;
    s32 delta;
    s32 half;
    f32 df;
    f32 r;
    fn_8003403C(o->sizeX, o->sizeY);
    fn_80033CC8(o, a->tex);
    if (o->texIndex != 0) {
        r = fn_3_119854(2);
    } else {
        r = fn_3_119854(0);
    }
    c = o->color.c.a;
    if (lbl_3_data_26BFC[3] / o->life < 2) {
        half = lbl_3_data_26BFC[3] / 2;
        delta = lbl_3_data_26BDC[2] / half;
        df = (f32)lbl_3_data_26BFC[1] * r / lbl_3_rodata_3930 / (f32)half;
    } else {
        half = lbl_3_data_26BFC[3] / 2;
        delta = -lbl_3_data_26BDC[2] / half;
        df = -((f32)lbl_3_data_26BFC[1] * r / lbl_3_rodata_3930) / (f32)half;
    }
    c += delta;
    if (c < 0) {
        c = 0;
    } else if (c > 0xFF) {
        c = 0xFF;
    }
    o->color.c.a = c;
    o->sizeX = o->sizeX + df;
    o->sizeY = o->sizeX;
    PSVECAdd(&o->pos, &o->u.phys.vel, &o->pos);
    o->life -= 1;
}

// .text:0x00151D6C size:0x1C0 mapped:0x80790E00
void fn_3_151D6C(Emitter* a, Particle* o) {
    s32 c;
    s32 delta;
    s32 half;
    f32 df;
    f32 r;
    fn_8003403C(o->sizeX, o->sizeY);
    fn_80033CC8(o, a->tex);
    if (o->texIndex != 0) {
        r = fn_3_119854(2);
    } else {
        r = fn_3_119854(0);
    }
    c = o->color.c.a;
    if (lbl_3_data_26BEC[3] / o->life < 2) {
        half = lbl_3_data_26BEC[3] / 2;
        delta = lbl_3_data_26BDC[2] / half;
        df = (f32)lbl_3_data_26BEC[1] * r / lbl_3_rodata_3930 / (f32)half;
    } else {
        half = lbl_3_data_26BEC[3] / 2;
        delta = -lbl_3_data_26BDC[2] / half;
        df = -((f32)lbl_3_data_26BEC[1] * r / lbl_3_rodata_3930) / (f32)half;
    }
    c += delta;
    if (c < 0) {
        c = 0;
    } else if (c > 0xFF) {
        c = 0xFF;
    }
    o->color.c.a = c;
    o->sizeX = o->sizeX + df;
    o->sizeY = o->sizeX;
    PSVECAdd(&o->pos, &o->u.phys.vel, &o->pos);
    o->life -= 1;
}

// NONMATCHING 95%: 151D6C/151BAC/1519F8 inlined; the original reaches 26BDC/26BEC/26BFC/26C1C through one pooled lbl_3_data_266A8 base (this TU's .data), we use the separate symbols
// .text:0x00151F2C size:0x5BC mapped:0x80790FC0
#if NONMATCHING
u32 fn_3_151F2C(Emitter* e) {
    Particle* p;
    s16 delay;
    if (lbl_80366158._28 != 0) {
        return 0;
    }
    fn_80033620(e);
    p = e->particles;
    if (p->unk4C != 3) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    } else {
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    }
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
    do {
        delay = p->delay;
        if (delay <= 0 && p->life != 0) {
            if (p->texIndex != 0) {
                fn_3_119854(2);
            } else {
                fn_3_119854(0);
            }
            switch (p->unk4C) {
            case 1:
                fn_3_151D6C(e, p);
                break;
            case 2:
                fn_3_151BAC(e, p);
                break;
            case 3:
                fn_3_1519F8(e, p);
                break;
            }
        } else if (delay != 0) {
            p->delay -= 1;
        }
        if (p->life == 0 && (p->unk4C == 1 || p->unk4C == 2)) {
            fn_3_1536A8(p, 2);
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}
#endif
#pragma dont_inline on

#pragma dont_inline off
// .text:0x001524E8 size:0x2AC mapped:0x8079157C
void fn_3_1524E8(Particle* o, u8 flag) {
    Mtx m;
    Vec off;
    Vec dir;
    Vec axis;
    Vec up;
    f32 ang;
    f32 r;
    camera_803c639c_s* cam;
    cam = fn_80052734(fn_8005268C());
    if (o->texIndex != 0) {
        r = fn_3_119854(2);
    } else {
        r = fn_3_119854(0);
    }
    up = lbl_3_rodata_38DC;
    off.x = lbl_3_rodata_3934[0];
    off.y = lbl_3_rodata_3934[0];
    off.z = lbl_3_rodata_3A04 * r;
    if (flag) {
        off.x += r * ((f64)(rand() % 50 - 25) / lbl_3_rodata_39E8);
        off.y += r * ((f64)(rand() % 50 - 25) / lbl_3_rodata_39E8);
        off.z += r * ((f64)(rand() % 50 - 25) / lbl_3_rodata_39E8);
    }
    PSVECSubtract(&cam->eye, &o->u.phys.accel, &dir);
    PSVECNormalize(&dir, &dir);
    ang = (f32)acos(PSVECDotProduct(&up, &dir));
    PSVECCrossProduct(&up, &dir, &axis);
    if (lbl_3_rodata_3934[0] == PSVECMag(&axis)) {
        axis.x = lbl_3_rodata_3934[0];
        axis.z = lbl_3_rodata_3934[0];
        axis.y = lbl_3_rodata_3948;
    }
    PSMTXRotAxisRad(m, &axis, ang);
    PSMTXMultVec(m, &off, &off);
    o->pos.x = o->u.phys.accel.x + off.x;
    o->pos.y = o->u.phys.accel.y + off.y;
    o->pos.z = o->u.phys.accel.z + off.z;
}

#pragma dont_inline off
// .text:0x00152794 size:0x320 mapped:0x80791828
void fn_3_152794(Particle* o) {
    Mtx m;
    Vec up;
    Vec axis;
    Vec dir;
    Vec off;
    f32 ang;
    f32 r;
    camera_803c639c_s* cam;
    cam = fn_80052734(fn_8005268C());
    if (o->texIndex != 0) {
        r = fn_3_119854(2);
    } else {
        r = fn_3_119854(0);
    }
    up = lbl_3_rodata_38DC;
    off.x = lbl_3_rodata_3934[0];
    off.y = lbl_3_rodata_3934[0];
    off.z = lbl_3_rodata_3A04 * r;
    off.x += r * ((f64)(rand() % 50 - 25) / lbl_3_rodata_39E8);
    off.y += r * ((f64)(rand() % 50 - 25) / lbl_3_rodata_39E8);
    off.z += r * ((f64)(rand() % 50 - 25) / lbl_3_rodata_39E8);
    PSVECSubtract(&cam->eye, &o->u.phys.accel, &dir);
    PSVECNormalize(&dir, &dir);
    ang = (f32)acos(PSVECDotProduct(&up, &dir));
    PSVECCrossProduct(&up, &dir, &axis);
    if (lbl_3_rodata_3934[0] == PSVECMag(&axis)) {
        axis.x = lbl_3_rodata_3934[0];
        axis.z = lbl_3_rodata_3934[0];
        axis.y = lbl_3_rodata_3948;
    }
    PSMTXRotAxisRad(m, &axis, ang);
    PSMTXMultVec(m, &off, &off);
    o->pos.x = o->u.phys.accel.x + off.x;
    o->pos.y = o->u.phys.accel.y + off.y;
    o->pos.z = o->u.phys.accel.z + off.z;
    o->sizeX = o->sizeY = (f32)lbl_3_data_26C0C[0];
    o->unk4C = 3;
    o->life = lbl_3_data_26C0C[3];
    o->u.phys.vel.x = o->u.phys.vel.z = lbl_3_rodata_3934[0];
    o->u.phys.vel.y = -((f32)lbl_3_data_26C0C[2] / lbl_3_rodata_3930);
}

// NONMATCHING 94%: 1524E8 inlined; the original keeps tgt+4 in its own saved reg (one more stmw reg) and FPR numbering differs
// .text:0x00152AB4 size:0x6F0 mapped:0x80791B48
#if NONMATCHING
void fn_3_152AB4(u8 flag, u8 idx) {
    Vec w;
    Vec view;
    Vec diff;
    Vec v;
    Particle* p;
    Emitter* e;
    camera_803c639c_s* cam;
    f32* tgt;
    f32 ang;
    f32 k;
    s32 count;
    count = 0;
    if (g_d_GameSettings.GameModeSelected == 7 && g_Minigame.GameMode_MiniGame == 4) {
        e = fn_800339F0(NULL, 0x1C);
        if (e != NULL) {
            p = e->particles;
            tgt = &lbl_3_data_26C1C[2 * idx];
            do {
                if (p->uvOrder == flag && p->life != 0) {
                    p->delay = 0;
                    p->uvOrder = 0xFF;
                    fn_3_1524E8(p, 1);
                    cam = fn_80052734(fn_8005268C());
                    w.x = p->pos.x;
                    w.y = p->pos.y;
                    w.z = p->pos.z;
                    PSMTXMultVec(cam->view, &w, &view);
                    v.z = v.y = v.x = lbl_3_rodata_3934[0];
                    PSVECSubtract(&v, &cam->eye, &v);
                    p->u.phys.mass = PSVECMag(&v);
                    PSMTX44MultVec(cam->proj, &view, &view);
                    view.z = lbl_3_rodata_3948;
                    p->pos.x = view.x;
                    p->pos.y = view.y;
                    p->pos.z = view.z;
                    p->sizeX = p->sizeY = (f32)lbl_3_data_26C0C[0] / lbl_3_rodata_3930;
                    w.x = w.y = p->sizeX;
                    w.z = p->u.phys.mass;
                    PSMTX44MultVec(cam->proj, &w, &view);
                    p->sizeX = view.x * (p->texIndex != 0 ? lbl_3_rodata_3A08 : lbl_3_rodata_3978);
                    p->sizeY = view.y * (p->texIndex != 0 ? lbl_3_rodata_3A08 : lbl_3_rodata_3978);
                    p->unk4C = 3;
                    p->life = lbl_3_data_26C0C[3];
                    ang = lbl_3_rodata_39B8 * (f32)(lbl_3_rodata_3A10 * (lbl_3_rodata_3990 * ((f64)((f32)rand() / lbl_3_rodata_3970) - lbl_3_rodata_3968)));
                    diff.x = tgt[0] - p->pos.x;
                    diff.y = tgt[1] - p->pos.y;
                    diff.z = lbl_3_rodata_3934[0];
                    if (PSVECMag(&diff) >= lbl_3_rodata_3978) {
                        k = lbl_3_rodata_392C;
                    } else {
                        k = lbl_3_rodata_392C / (PSVECMag(&diff) * lbl_3_rodata_39A8);
                    }
                    PSVECNormalize(&diff, &diff);
                    diff.x *= lbl_3_rodata_3948;
                    diff.y *= lbl_3_rodata_3948;
                    v.x = diff.x * (f32)cos(ang) + -diff.y * (f32)sin(ang);
                    v.y = diff.x * (f32)sin(ang) + diff.y * (f32)cos(ang);
                    v.z = lbl_3_rodata_3934[0];
                    PSVECScale(&v, (f32)lbl_3_data_26C0C[2] / lbl_3_rodata_3930 * k, &v);
                    v.z = p->u.phys.mass;
                    PSMTX44MultVec(cam->proj, &v, &v);
                    v.z = lbl_3_rodata_3934[0];
                    p->u.phys.vel.x = v.x;
                    p->u.phys.vel.y = v.y;
                    p->u.phys.vel.z = v.z;
                    p->color.c.a = 0xFF;
                    p->colorStep.v[0] = idx;
                    p->colorStep.v[1] = count++ == 0;
                }
                p = p->next;
            } while (p != NULL);
        }
    }
}
#endif

// .text:0x001531A4 size:0x31C mapped:0x80792238
void fn_3_1531A4(Particle* o) {
    Mtx m;
    Vec up;
    Vec axis;
    Vec dir;
    Vec off;
    f32 ang;
    f32 r;
    camera_803c639c_s* cam;
    cam = fn_80052734(fn_8005268C());
    if (o->texIndex != 0) {
        r = fn_3_119854(2);
    } else {
        r = fn_3_119854(0);
    }
    up = lbl_3_rodata_38DC;
    off.x = lbl_3_rodata_3934[0];
    off.y = lbl_3_rodata_3934[0];
    off.z = lbl_3_rodata_3A04 * r;
    off.x += r * ((f64)(rand() % 50 - 25) / lbl_3_rodata_39E8);
    off.y += r * ((f64)(rand() % 50 - 25) / lbl_3_rodata_39E8);
    off.z += r * ((f64)(rand() % 50 - 25) / lbl_3_rodata_39E8);
    PSVECSubtract(&cam->eye, &o->u.phys.accel, &dir);
    PSVECNormalize(&dir, &dir);
    ang = (f32)acos(PSVECDotProduct(&up, &dir));
    PSVECCrossProduct(&up, &dir, &axis);
    if (lbl_3_rodata_3934[0] == PSVECMag(&axis)) {
        axis.x = lbl_3_rodata_3934[0];
        axis.z = lbl_3_rodata_3934[0];
        axis.y = lbl_3_rodata_3948;
    }
    PSMTXRotAxisRad(m, &axis, ang);
    PSMTXMultVec(m, &off, &off);
    o->pos.x = o->u.phys.accel.x + off.x;
    o->pos.y = o->u.phys.accel.y + off.y;
    o->pos.z = o->u.phys.accel.z + off.z;
    o->sizeX = o->sizeY = (f32)lbl_3_data_26BFC[0];
    o->unk4C = 2;
    o->life = lbl_3_data_26BFC[3];
    o->u.phys.vel.x = o->u.phys.vel.z = lbl_3_rodata_3934[0];
    o->u.phys.vel.y = (f32)lbl_3_data_26BFC[2] / lbl_3_rodata_3930;
}

// .text:0x001534C0 size:0x1E8 mapped:0x80792554
void fn_3_1534C0(Particle* o) {
    Mtx m;
    Vec up;
    Vec axis;
    Vec dir;
    Vec off;
    f32 ang;
    f32 r;
    camera_803c639c_s* cam;
    cam = fn_80052734(fn_8005268C());
    if (o->texIndex != 0) {
        r = fn_3_119854(2);
    } else {
        r = fn_3_119854(0);
    }
    up = lbl_3_rodata_38DC;
    off.x = lbl_3_rodata_3934[0];
    off.y = lbl_3_rodata_3934[0];
    off.z = lbl_3_rodata_3A04 * r;
    PSVECSubtract(&cam->eye, &o->u.phys.accel, &dir);
    PSVECNormalize(&dir, &dir);
    ang = (f32)acos(PSVECDotProduct(&up, &dir));
    PSVECCrossProduct(&up, &dir, &axis);
    if (lbl_3_rodata_3934[0] == PSVECMag(&axis)) {
        axis.x = lbl_3_rodata_3934[0];
        axis.z = lbl_3_rodata_3934[0];
        axis.y = lbl_3_rodata_3948;
    }
    PSMTXRotAxisRad(m, &axis, ang);
    PSMTXMultVec(m, &off, &off);
    o->pos.x = o->u.phys.accel.x + off.x;
    o->pos.y = o->u.phys.accel.y + off.y;
    o->pos.z = o->u.phys.accel.z + off.z;
    o->sizeX = o->sizeY = (f32)lbl_3_data_26BEC[0];
    o->unk4C = 1;
    o->life = lbl_3_data_26BEC[3];
    o->u.phys.vel.x = o->u.phys.vel.z = lbl_3_rodata_3934[0];
    o->u.phys.vel.y = (f32)lbl_3_data_26BEC[2] / lbl_3_rodata_3930;
}

#if NONMATCHING
static inline void Inl1534C0(Particle* o) {
    Mtx m;
    Vec up;
    Vec axis;
    Vec dir;
    Vec off;
    f32 ang;
    f32 r;
    camera_803c639c_s* cam;
    cam = fn_80052734(fn_8005268C());
    if (o->texIndex != 0) {
        r = fn_3_119854(2);
    } else {
        r = fn_3_119854(0);
    }
    up = lbl_3_rodata_38DC;
    off.x = lbl_3_rodata_3934[0];
    off.y = lbl_3_rodata_3934[0];
    off.z = lbl_3_rodata_3A04 * r;
    PSVECSubtract(&cam->eye, &o->u.phys.accel, &dir);
    PSVECNormalize(&dir, &dir);
    ang = (f32)acos(PSVECDotProduct(&up, &dir));
    PSVECCrossProduct(&up, &dir, &axis);
    if (lbl_3_rodata_3934[0] == PSVECMag(&axis)) {
        axis.x = lbl_3_rodata_3934[0];
        axis.z = lbl_3_rodata_3934[0];
        axis.y = lbl_3_rodata_3948;
    }
    PSMTXRotAxisRad(m, &axis, ang);
    PSMTXMultVec(m, &off, &off);
    o->pos.x = o->u.phys.accel.x + off.x;
    o->pos.y = o->u.phys.accel.y + off.y;
    o->pos.z = o->u.phys.accel.z + off.z;
    o->sizeX = o->sizeY = (f32)lbl_3_data_26BEC[0];
    o->unk4C = 1;
    o->life = lbl_3_data_26BEC[3];
    o->u.phys.vel.x = o->u.phys.vel.z = lbl_3_rodata_3934[0];
    o->u.phys.vel.y = (f32)lbl_3_data_26BEC[2] / lbl_3_rodata_3930;
}
#endif

#if NONMATCHING
static inline void Inl1531A4(Particle* o) {
    Mtx m;
    Vec up;
    Vec axis;
    Vec dir;
    Vec off;
    f32 ang;
    f32 r;
    camera_803c639c_s* cam;
    cam = fn_80052734(fn_8005268C());
    if (o->texIndex != 0) {
        r = fn_3_119854(2);
    } else {
        r = fn_3_119854(0);
    }
    up = lbl_3_rodata_38DC;
    off.x = lbl_3_rodata_3934[0];
    off.y = lbl_3_rodata_3934[0];
    off.z = lbl_3_rodata_3A04 * r;
    off.x += r * ((f64)(rand() % 50 - 25) / lbl_3_rodata_39E8);
    off.y += r * ((f64)(rand() % 50 - 25) / lbl_3_rodata_39E8);
    off.z += r * ((f64)(rand() % 50 - 25) / lbl_3_rodata_39E8);
    PSVECSubtract(&cam->eye, &o->u.phys.accel, &dir);
    PSVECNormalize(&dir, &dir);
    ang = (f32)acos(PSVECDotProduct(&up, &dir));
    PSVECCrossProduct(&up, &dir, &axis);
    if (lbl_3_rodata_3934[0] == PSVECMag(&axis)) {
        axis.x = lbl_3_rodata_3934[0];
        axis.z = lbl_3_rodata_3934[0];
        axis.y = lbl_3_rodata_3948;
    }
    PSMTXRotAxisRad(m, &axis, ang);
    PSMTXMultVec(m, &off, &off);
    o->pos.x = o->u.phys.accel.x + off.x;
    o->pos.y = o->u.phys.accel.y + off.y;
    o->pos.z = o->u.phys.accel.z + off.z;
    o->sizeX = o->sizeY = (f32)lbl_3_data_26BFC[0];
    o->unk4C = 2;
    o->life = lbl_3_data_26BFC[3];
    o->u.phys.vel.x = o->u.phys.vel.z = lbl_3_rodata_3934[0];
    o->u.phys.vel.y = (f32)lbl_3_data_26BFC[2] / lbl_3_rodata_3930;
}
#endif

#if NONMATCHING
static inline void Inl152794(Particle* o) {
    Mtx m;
    Vec up;
    Vec axis;
    Vec dir;
    Vec off;
    f32 ang;
    f32 r;
    camera_803c639c_s* cam;
    cam = fn_80052734(fn_8005268C());
    if (o->texIndex != 0) {
        r = fn_3_119854(2);
    } else {
        r = fn_3_119854(0);
    }
    up = lbl_3_rodata_38DC;
    off.x = lbl_3_rodata_3934[0];
    off.y = lbl_3_rodata_3934[0];
    off.z = lbl_3_rodata_3A04 * r;
    off.x += r * ((f64)(rand() % 50 - 25) / lbl_3_rodata_39E8);
    off.y += r * ((f64)(rand() % 50 - 25) / lbl_3_rodata_39E8);
    off.z += r * ((f64)(rand() % 50 - 25) / lbl_3_rodata_39E8);
    PSVECSubtract(&cam->eye, &o->u.phys.accel, &dir);
    PSVECNormalize(&dir, &dir);
    ang = (f32)acos(PSVECDotProduct(&up, &dir));
    PSVECCrossProduct(&up, &dir, &axis);
    if (lbl_3_rodata_3934[0] == PSVECMag(&axis)) {
        axis.x = lbl_3_rodata_3934[0];
        axis.z = lbl_3_rodata_3934[0];
        axis.y = lbl_3_rodata_3948;
    }
    PSMTXRotAxisRad(m, &axis, ang);
    PSMTXMultVec(m, &off, &off);
    o->pos.x = o->u.phys.accel.x + off.x;
    o->pos.y = o->u.phys.accel.y + off.y;
    o->pos.z = o->u.phys.accel.z + off.z;
    o->sizeX = o->sizeY = (f32)lbl_3_data_26C0C[0];
    o->unk4C = 3;
    o->life = lbl_3_data_26C0C[3];
    o->u.phys.vel.x = o->u.phys.vel.z = lbl_3_rodata_3934[0];
    o->u.phys.vel.y = -((f32)lbl_3_data_26C0C[2] / lbl_3_rodata_3930);
}
#endif

// NONMATCHING 93%: the original inlines 1534C0/1531A4/152794 (one per case); CW won't auto-inline the last two, and making the
// standalone functions call shared helpers changes their stack layout, so these are static-inline copies of the three bodies.
// The rest is the original reaching 26BEC/26BFC/26C0C through the pooled lbl_3_data_266A8 base
// .text:0x001536A8 size:0x7E4 mapped:0x8079273C
#if NONMATCHING
void fn_3_1536A8(Particle* obj, u8 mode) {
    switch (mode) {
    case 1:
        Inl1534C0(obj);
        break;
    case 2:
        Inl1531A4(obj);
        break;
    case 3:
        Inl152794(obj);
        break;
    }
}
#endif
#pragma dont_inline on

// .text:0x00153E8C size:0x100 mapped:0x80792F20
void fn_3_153E8C(Particle* obj, f32* pos, u8 b, u8 c, u8 d) {
    f32 r;
    obj->delay = (d != 0) * lbl_3_data_26BEC[3] + (s32)(d * lbl_3_data_26BDC[3]) / lbl_3_data_26BDC[0];
    obj->texIndex = c == 4;
    obj->uvFrame = 0;
    obj->uvOrder = b;
    obj->color.c.b = 0xFF;
    obj->color.c.g = 0xFF;
    obj->color.c.r = 0xFF;
    obj->color.c.a = lbl_3_data_26BDC[1];
    obj->u.phys.accel.x = pos[0];
    if (obj->texIndex != 0) {
        r = fn_3_119854(2);
    } else {
        r = fn_3_119854(0);
    }
    obj->u.phys.accel.y = -pos[1] - lbl_3_rodata_3A18 * r;
    obj->u.phys.accel.z = pos[2];
    obj->colorStep.v[1] = 0;
    obj->colorStep.v[0] = 0;
}

// .text:0x00153F8C size:0x158 mapped:0x80793020
void fn_3_153F8C(Emitter* h, u32 a, u32 b, Vec* c) {
    f32* pos;
    f32 r;
    u8 flag;
    Particle* q;
    u8 i;
    i = 0;
    q = h->particles;
    pos = (f32*)c;
    h->tex = MG_ASSETS.textures[2];
    do {
        if (q->life == 0) {
            flag = i != 0;
            q->delay = flag * lbl_3_data_26BEC[3] + (s32)(i * lbl_3_data_26BDC[3]) / lbl_3_data_26BDC[0];
            q->texIndex = (u8)b == 4;
            q->uvFrame = 0;
            q->uvOrder = a;
            q->color.c.b = 0xFF;
            q->color.c.g = 0xFF;
            q->color.c.r = 0xFF;
            q->color.c.a = lbl_3_data_26BDC[1];
            q->u.phys.accel.x = pos[0];
            if (q->texIndex != 0) {
                r = fn_3_119854(2);
            } else {
                r = fn_3_119854(0);
            }
            q->u.phys.accel.y = -pos[1] - lbl_3_rodata_3A18 * r;
            q->u.phys.accel.z = pos[2];
            q->colorStep.v[1] = 0;
            q->colorStep.v[0] = 0;
            fn_3_1536A8(q, flag + 1);
            i++;
        }
        q = q->next;
    } while (q != NULL && i < lbl_3_data_26BDC[0]);
}

// .text:0x001540E4 size:0xE0 mapped:0x80793178
void fn_3_1540E4(u32 a, u32 b, Vec* c) {
    Particle* p;
    Emitter* h = fn_800339F0(0, 0x1C);
    if (h != NULL) {
        fn_3_153F8C(h, a, b, c);
        return;
    }
    h = fn_80033A24((EmitterUpdateFn)fn_3_151F2C, 0x80, 0, lbl_3_data_26BDC[0] * 0xF, 1, 0x1C);
    if (h != NULL) {
        p = h->particles;
        do {
            p->life = 0;
            p->unk4C = 0;
            p->uvOrder = 0xFF;
            p = p->next;
        } while (p != NULL);
        fn_3_153F8C(h, a, b, c);
        memset(lbl_3_bss_B894, 0, 0xF);
    }
}

// .text:0x001541C4 size:0x50 mapped:0x80793258
void fn_3_1541C4(u32 a, u32 b, Vec* c) {
    if (g_d_GameSettings.GameModeSelected == 7 && g_Minigame.GameMode_MiniGame == 4 && c != NULL) {
        fn_3_1540E4(a, b, c);
    }
}

// .text:0x00154214 size:0x24 mapped:0x807932A8
void fn_3_154214(void) {
    pitchingMachinePitching(0x27);
}

// .text:0x00154238 size:0xBC mapped:0x807932CC

void fn_3_154238(s16 id) {
    Particle* p;
    Particle** link;
    Particle* first;
    Particle* last;
    Emitter* h = fn_800339F0(0, 0x27);
    if (h != NULL) {
        p = h->particles;
        link = &h->particles;
        last = NULL;
        first = NULL;
        do {
            if (p->u.follow.id == id) {
                *link = p->next;
                if (last != NULL) {
                    last->next = p;
                } else {
                    first = p;
                }
                p->next = NULL;
                last = p;
                h->count--;
            } else {
                link = &p->next;
            }
            p = *link;
        } while (p != NULL);
        if (first != NULL) {
            fn_80033794(first);
        }
    }
}

// NONMATCHING 93%: respawn block inlined twice (as in the original); remaining diffs are scheduling of the list-head store and the pooled data base
// .text:0x001542F4 size:0x6FC mapped:0x80793388
#if NONMATCHING
static inline void respawn_1542F4(Particle* o) {
    struct { Control c; u32 pad[2]; } cc;
    Mtx m;
    Vec dir;
    Vec v;
    f32* pos;
    f32* rot;
    rot = o->u.follow.rot;
    pos = o->u.follow.pos;
    o->life = lbl_3_data_26BC0[6];
    cc.c.type = 0;
    CTRLSetRotation(&cc.c, lbl_3_rodata_39AC * rot[0], lbl_3_rodata_39AC * rot[1], lbl_3_rodata_39AC * rot[2]);
    CTRLBuildMatrix(&cc.c, m);
    if (g_Minigame.GameMode_MiniGame == 1) {
        dir = lbl_3_data_26BB4;
    } else {
        PSVECScale(&lbl_3_data_26BB4, lbl_3_rodata_3950, &dir);
    }
    v.x = (f32)(lbl_3_rodata_3A08 * ((f64)(rand() % 40 - 20) / lbl_3_rodata_39E8) + (f64)dir.x);
    v.y = dir.y;
    v.z = (f32)(lbl_3_rodata_3A08 * ((f64)(rand() % 40 - 20) / lbl_3_rodata_39E8) + (f64)dir.z);
    PSMTXMultVec(m, &v, &v);
    v.x = v.x + pos[0];
    v.y = v.y - __fabs(pos[1]);
    v.z = v.z + pos[2];
    o->pos.x = v.x;
    o->pos.y = v.y;
    o->pos.z = v.z;
    o->sizeY = o->sizeX = (f32)lbl_3_data_26BC0[2];
    o->color.c.a = lbl_3_data_26BC0[4];
}

u32 fn_3_1542F4(Emitter* e) {
    Particle* p;
    s32* d;
    s32 a;
    if (lbl_80366158._28 != 0) {
        return 0;
    }
    if (e->particles == NULL) {
        return 0;
    }
    p = fn_80031F34(e->particles, e->count);
    e->particles = p;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
    d = (s32*)lbl_3_data_26BC0;
    do {
        if (p->delay != 0) {
            p->delay -= 1;
            if (p->delay == 0) {
                respawn_1542F4(p);
            }
        } else if (p->life != 0) {
            fn_8003403C(p->sizeX, p->sizeY);
            fn_80033CC8(p, e->tex);
            if (d[6] / p->life < 2) {
                a = p->color.c.a + d[5] / (d[6] / 2);
                if (a > d[5]) {
                    a = d[5];
                }
                p->color.c.a = a;
                p->sizeX = lbl_3_rodata_394C * ((f32)d[3] / lbl_3_rodata_3930 / (f32)(d[6] / 2)) + p->sizeX;
                p->sizeY = p->sizeX;
            } else {
                a = p->color.c.a - d[5] / (d[6] / 2);
                if (a < d[4]) {
                    a = d[4];
                }
                p->color.c.a = a;
                p->sizeX = p->sizeX - lbl_3_rodata_394C * ((f32)d[3] / lbl_3_rodata_3930 / (f32)(d[6] / 2));
                p->sizeY = p->sizeX;
            }
            p->color.c.r = p->color.c.g = p->color.c.b = (s32)(lbl_3_rodata_3A1C * ((f32)p->color.c.a / lbl_3_rodata_3A1C));
            p->life -= 1;
        }
        if (p->life == 0 && p->delay <= 0) {
            respawn_1542F4(p);
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}
#endif

// .text:0x001549F0 size:0x28C mapped:0x80793A84
void fn_3_1549F0(Emitter* a, s16 b, f32* pos, f32* rot) {
    struct { Control c; u32 pad[2]; } cc;
    Mtx m;
    Vec dir;
    f64 t;
    Vec v;
    Particle* o;
    u8 i = 0;
    o = a->particles;
    a->tex = MG_ASSETS.textures[2];
    do {
        o->u.follow.id = b;
        o->u.follow.pos = pos;
        o->u.follow.rot = rot;
        o->delay = i++;
        o->texIndex = lbl_3_data_26BC0[0];
        o->uvFrame = 0;
        if (o->delay == 0) {
            o->life = lbl_3_data_26BC0[6];
            cc.c.type = 0;
            CTRLSetRotation(&cc.c, rot[0], rot[1], rot[2]);
            CTRLBuildMatrix(&cc.c, m);
            if (g_Minigame.GameMode_MiniGame == 1) {
                dir = lbl_3_data_26BB4;
            } else {
                PSVECScale(&lbl_3_data_26BB4, lbl_3_rodata_3950, &dir);
            }
            v.x = (f32)(lbl_3_rodata_3A08 * ((f64)(rand() % 40 - 20) / lbl_3_rodata_39E8) + (f64)dir.x);
            v.y = dir.y;
            v.z = (f32)(lbl_3_rodata_3A08 * ((f64)(rand() % 40 - 20) / lbl_3_rodata_39E8) + (f64)dir.z);
            PSMTXMultVec(m, &v, &v);
            v.x = v.x + pos[0];
            t = __fabs(pos[1]);
            v.y = v.y - t;
            v.z = v.z + pos[2];
            o->pos.x = v.x;
            o->pos.y = v.y;
            o->pos.z = v.z;
            o->sizeY = o->sizeX = (f32)lbl_3_data_26BC0[2];
            o->color.c.a = lbl_3_data_26BC0[4];
        }
        o = o->next;
    } while (o != NULL);
}

// fn_3_1549F0's body for fn_3_154C7C, which inlines it twice (CW won't auto-inline the real one; dir/v are declared
// in the other order here, which the inlined copies' stack layout needs)
static inline void Inl1549F0(Emitter* a, s16 b, f32* pos, f32* rot) {
    struct { Control c; u32 pad[2]; } cc;
    Mtx m;
    Vec v;
    f64 t;
    Vec dir;
    Particle* o;
    u8 i = 0;
    o = a->particles;
    a->tex = MG_ASSETS.textures[2];
    do {
        o->u.follow.id = b;
        o->u.follow.pos = pos;
        o->u.follow.rot = rot;
        o->delay = i++;
        o->texIndex = lbl_3_data_26BC0[0];
        o->uvFrame = 0;
        if (o->delay == 0) {
            o->life = lbl_3_data_26BC0[6];
            cc.c.type = 0;
            CTRLSetRotation(&cc.c, rot[0], rot[1], rot[2]);
            CTRLBuildMatrix(&cc.c, m);
            if (g_Minigame.GameMode_MiniGame == 1) {
                dir = lbl_3_data_26BB4;
            } else {
                PSVECScale(&lbl_3_data_26BB4, lbl_3_rodata_3950, &dir);
            }
            v.x = (f32)(lbl_3_rodata_3A08 * ((f64)(rand() % 40 - 20) / lbl_3_rodata_39E8) + (f64)dir.x);
            v.y = dir.y;
            v.z = (f32)(lbl_3_rodata_3A08 * ((f64)(rand() % 40 - 20) / lbl_3_rodata_39E8) + (f64)dir.z);
            PSMTXMultVec(m, &v, &v);
            v.x = v.x + pos[0];
            t = __fabs(pos[1]);
            v.y = v.y - t;
            v.z = v.z + pos[2];
            o->pos.x = v.x;
            o->pos.y = v.y;
            o->pos.z = v.z;
            o->sizeY = o->sizeX = (f32)lbl_3_data_26BC0[2];
            o->color.c.a = lbl_3_data_26BC0[4];
        }
        o = o->next;
    } while (o != NULL);
}

void fn_3_154C7C(s16 id, f32* pos, f32* rot) {
    Emitter buf; // only its particle list is filled in
    Emitter* h;
    Emitter* n;
    Particle* p;
    h = fn_800339F0(NULL, 0x27);
    if (h != NULL) {
        n = fn_800337CC(&buf, lbl_3_data_26BC0[1], 1);
        if (n != NULL) {
            Inl1549F0(n, id, pos, rot);
            p = h->particles;
            if (p != NULL) {
                while (p->next != NULL) {
                    p = p->next;
                }
                p->next = n->particles;
            } else {
                h->particles = n->particles;
            }
            h->count += n->count;
        }
    } else {
        n = fn_80033A24((EmitterUpdateFn)fn_3_1542F4, 0x80, 0, lbl_3_data_26BC0[1], 1, 0x27);
        if (n != NULL) {
            Inl1549F0(n, id, pos, rot);
        }
    }
}

// .text:0x0015521C size:0x48 mapped:0x807942B0
void fn_3_15521C(s16 a, f32* b, f32* c) {
    if (g_d_GameSettings.GameModeSelected != 7 || b == NULL || c == NULL) {
        return;
    }
    fn_3_154C7C(a, b, c);
}

// .text:0x00155264 size:0x24 mapped:0x807942F8
void fn_3_155264(void) {
    pitchingMachinePitching(0x1B);
}

// .text:0x00155288 size:0x24 mapped:0x8079431C
void fn_3_155288(void) {
    pitchingMachinePitching(0x1B);
}

// NONMATCHING 99%: respawn (155C28's spawn block) inlined twice; register numbering of the data/g_Ball bases differs
// .text:0x001552AC size:0x738 mapped:0x80794340
#if NONMATCHING
static inline void respawn_1552AC(Particle* o) {
    struct { Control c; u32 pad[2]; } cc;
    Mtx m;
    Vec dir;
    Vec v;
    f32 rx;
    f32 ry;
    f32 rz;
    f64 t;
    rx = lbl_3_rodata_39AC * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw);
    ry = lbl_3_rodata_39AC * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch);
    rz = lbl_3_rodata_39AC * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll);
    o->life = lbl_3_data_26BC0[6];
    cc.c.type = 0;
    CTRLSetRotation(&cc.c, rx, ry, rz);
    CTRLBuildMatrix(&cc.c, m);
    if (g_Minigame.GameMode_MiniGame == 1) {
        dir = lbl_3_data_26BB4;
    } else {
        PSVECScale(&lbl_3_data_26BB4, lbl_3_rodata_3950, &dir);
    }
    v.x = (f32)(lbl_3_rodata_3A08 * ((f64)(rand() % 40 - 20) / lbl_3_rodata_39E8) + (f64)dir.x);
    v.y = dir.y;
    v.z = (f32)(lbl_3_rodata_3A08 * ((f64)(rand() % 40 - 20) / lbl_3_rodata_39E8) + (f64)dir.z);
    PSMTXMultVec(m, &v, &v);
    v.x = v.x + g_Ball.AtBat_Contact_BallPos.x;
    t = __fabs(g_Ball.AtBat_Contact_BallPos.y);
    v.y = v.y - t;
    v.z = v.z + g_Ball.AtBat_Contact_BallPos.z;
    o->pos.x = v.x;
    o->pos.y = v.y;
    o->pos.z = v.z;
    o->sizeY = o->sizeX = (f32)lbl_3_data_26BC0[2];
    o->color.c.a = lbl_3_data_26BC0[4];
}

u32 fn_3_1552AC(Emitter* e) {
    Particle* p;
    s32* d;
    s32 a;
    if (lbl_80366158._28 != 0) {
        return 0;
    }
    fn_80033620(e);
    p = e->particles;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
    d = (s32*)lbl_3_data_26BC0;
    do {
        if (p->delay != 0) {
            p->delay -= 1;
            if (p->delay == 0) {
                respawn_1552AC(p);
            }
        } else if (p->life != 0) {
            fn_8003403C(p->sizeX, p->sizeY);
            fn_80033CC8(p, e->tex);
            if (d[6] / p->life < 2) {
                a = p->color.c.a + d[5] / (d[6] / 2);
                if (a > d[5]) {
                    a = d[5];
                }
                p->color.c.a = a;
                p->sizeX = p->sizeX + (f32)d[3] / lbl_3_rodata_3930 / (f32)(d[6] / 2);
                p->sizeY = p->sizeX;
            } else {
                a = p->color.c.a - d[5] / (d[6] / 2);
                if (a < d[4]) {
                    a = d[4];
                }
                p->color.c.a = a;
                p->sizeX = p->sizeX - (f32)d[3] / lbl_3_rodata_3930 / (f32)(d[6] / 2);
                p->sizeY = p->sizeX;
            }
            p->color.c.r = p->color.c.g = p->color.c.b = (s32)(lbl_3_rodata_3A1C * ((f32)p->color.c.a / lbl_3_rodata_3A1C));
            p->life -= 1;
        }
        if (p->life == 0 && p->delay <= 0) {
            respawn_1552AC(p);
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}
#endif

// .text:0x001559E4 size:0x244 mapped:0x80794A78
void fn_3_1559E4(Particle* o, f32* pos, f32* rot) {
    struct { Control c; u32 pad[2]; } cc;
    Mtx m;
    Vec v;
    Vec dir;
    f64 t;
    o->life = lbl_3_data_26BC0[6];
    cc.c.type = 0;
    CTRLSetRotation(&cc.c, rot[0], rot[1], rot[2]);
    CTRLBuildMatrix(&cc.c, m);
    if (g_Minigame.GameMode_MiniGame == 1) {
        dir = lbl_3_data_26BB4;
    } else {
        PSVECScale(&lbl_3_data_26BB4, lbl_3_rodata_3950, &dir);
    }
    v.x = (f32)(lbl_3_rodata_3A08 * ((f64)(rand() % 40 - 20) / lbl_3_rodata_39E8) + (f64)dir.x);
    v.y = dir.y;
    v.z = (f32)(lbl_3_rodata_3A08 * ((f64)(rand() % 40 - 20) / lbl_3_rodata_39E8) + (f64)dir.z);
    PSMTXMultVec(m, &v, &v);
    v.x = v.x + pos[0];
    t = __fabs(pos[1]);
    v.y = v.y - t;
    v.z = v.z + pos[2];
    o->pos.x = v.x;
    o->pos.y = v.y;
    o->pos.z = v.z;
    o->sizeY = o->sizeX = (f32)lbl_3_data_26BC0[2];
    o->color.c.a = lbl_3_data_26BC0[4];
}

// .text:0x00155C28 size:0x2E0 mapped:0x80794CBC
void fn_3_155C28(Emitter* a) {
    struct { Control c; u32 pad[2]; } cc;
    Mtx m;
    Vec dir;
    Vec v;
    Particle* o;
    u8 i = 0;
    f32 rx;
    f32 ry;
    f32 rz;
    f64 t;
    o = a->particles;
    a->tex = MG_ASSETS.textures[2];
    do {
        o->delay = i++;
        o->texIndex = lbl_3_data_26BC0[0];
        o->uvFrame = 0;
        if (o->delay == 0) {
            rx = lbl_3_rodata_39AC * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw);
            ry = lbl_3_rodata_39AC * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch);
            rz = lbl_3_rodata_39AC * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll);
            o->life = lbl_3_data_26BC0[6];
            cc.c.type = 0;
            CTRLSetRotation(&cc.c, rx, ry, rz);
            CTRLBuildMatrix(&cc.c, m);
            if (g_Minigame.GameMode_MiniGame == 1) {
                dir = lbl_3_data_26BB4;
            } else {
                PSVECScale(&lbl_3_data_26BB4, lbl_3_rodata_3950, &dir);
            }
            v.x = (f32)(lbl_3_rodata_3A08 * ((f64)(rand() % 40 - 20) / lbl_3_rodata_39E8) + (f64)dir.x);
            v.y = dir.y;
            v.z = (f32)(lbl_3_rodata_3A08 * ((f64)(rand() % 40 - 20) / lbl_3_rodata_39E8) + (f64)dir.z);
            PSMTXMultVec(m, &v, &v);
            v.x = v.x + g_Ball.AtBat_Contact_BallPos.x;
            t = __fabs(g_Ball.AtBat_Contact_BallPos.y);
            v.y = v.y - t;
            v.z = v.z + g_Ball.AtBat_Contact_BallPos.z;
            o->pos.x = v.x;
            o->pos.y = v.y;
            o->pos.z = v.z;
            o->sizeY = o->sizeX = (f32)lbl_3_data_26BC0[2];
            o->color.c.a = lbl_3_data_26BC0[4];
        }
        o = o->next;
    } while (o != NULL);
}

// .text:0x00155F08 size:0x310 mapped:0x80794F9C
void fn_3_155F08(void) {
    struct { Control c; u32 pad[2]; } cc;
    Mtx m;
    Vec dir;
    Vec v;
    u8 i;
    Particle* o;
    Emitter* a;
    f32 rx;
    f32 ry;
    f32 rz;
    f64 t;
    a = fn_80033A24((EmitterUpdateFn)fn_3_1552AC, 0x80, 0, lbl_3_data_26BC0[1], 1, 0x1B);
    if (a != NULL) {
        o = a->particles;
        a->tex = MG_ASSETS.textures[2];
        i = 0;
        do {
            o->delay = i++;
            o->texIndex = lbl_3_data_26BC0[0];
            o->uvFrame = 0;
            if (o->delay == 0) {
                rx = lbl_3_rodata_39AC * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw);
                ry = lbl_3_rodata_39AC * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch);
                rz = lbl_3_rodata_39AC * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll);
                o->life = lbl_3_data_26BC0[6];
                cc.c.type = 0;
                CTRLSetRotation(&cc.c, rx, ry, rz);
                CTRLBuildMatrix(&cc.c, m);
                if (g_Minigame.GameMode_MiniGame == 1) {
                    dir = lbl_3_data_26BB4;
                } else {
                    PSVECScale(&lbl_3_data_26BB4, lbl_3_rodata_3950, &dir);
                }
                v.x = (f32)(lbl_3_rodata_3A08 * ((f64)(rand() % 40 - 20) / lbl_3_rodata_39E8) + (f64)dir.x);
                v.y = dir.y;
                v.z = (f32)(lbl_3_rodata_3A08 * ((f64)(rand() % 40 - 20) / lbl_3_rodata_39E8) + (f64)dir.z);
                PSMTXMultVec(m, &v, &v);
                v.x = v.x + g_Ball.AtBat_Contact_BallPos.x;
                t = __fabs(g_Ball.AtBat_Contact_BallPos.y);
                v.y = v.y - t;
                v.z = v.z + g_Ball.AtBat_Contact_BallPos.z;
                o->pos.x = v.x;
                o->pos.y = v.y;
                o->pos.z = v.z;
                o->sizeY = o->sizeX = (f32)lbl_3_data_26BC0[2];
                o->color.c.a = lbl_3_data_26BC0[4];
            }
            o = o->next;
        } while (o != NULL);
    }
}

// .text:0x00156218 size:0x330 mapped:0x807952AC
void fn_3_156218(void) {
    struct { Control c; u32 pad[2]; } cc;
    Mtx m;
    Vec dir;
    Vec v;
    u8 i;
    Particle* o;
    Emitter* a;
    f32 rx;
    f32 ry;
    f32 rz;
    f64 t;
    if (g_d_GameSettings.GameModeSelected == 7 && g_Minigame.GameMode_MiniGame == 1) {
        a = fn_80033A24((EmitterUpdateFn)fn_3_1552AC, 0x80, 0, lbl_3_data_26BC0[1], 1, 0x1B);
        if (a != NULL) {
            o = a->particles;
            a->tex = MG_ASSETS.textures[2];
            i = 0;
            do {
                o->delay = i++;
                o->texIndex = lbl_3_data_26BC0[0];
                o->uvFrame = 0;
                if (o->delay == 0) {
                    rx = lbl_3_rodata_39AC * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw);
                    ry = lbl_3_rodata_39AC * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch);
                    rz = lbl_3_rodata_39AC * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll);
                    o->life = lbl_3_data_26BC0[6];
                    cc.c.type = 0;
                    CTRLSetRotation(&cc.c, rx, ry, rz);
                    CTRLBuildMatrix(&cc.c, m);
                    if (g_Minigame.GameMode_MiniGame == 1) {
                        dir = lbl_3_data_26BB4;
                    } else {
                        PSVECScale(&lbl_3_data_26BB4, lbl_3_rodata_3950, &dir);
                    }
                    v.x = (f32)(lbl_3_rodata_3A08 * ((f64)(rand() % 40 - 20) / lbl_3_rodata_39E8) + (f64)dir.x);
                    v.y = dir.y;
                    v.z = (f32)(lbl_3_rodata_3A08 * ((f64)(rand() % 40 - 20) / lbl_3_rodata_39E8) + (f64)dir.z);
                    PSMTXMultVec(m, &v, &v);
                    v.x = v.x + g_Ball.AtBat_Contact_BallPos.x;
                    t = __fabs(g_Ball.AtBat_Contact_BallPos.y);
                    v.y = v.y - t;
                    v.z = v.z + g_Ball.AtBat_Contact_BallPos.z;
                    o->pos.x = v.x;
                    o->pos.y = v.y;
                    o->pos.z = v.z;
                    o->sizeY = o->sizeX = (f32)lbl_3_data_26BC0[2];
                    o->color.c.a = lbl_3_data_26BC0[4];
                }
                o = o->next;
            } while (o != NULL);
        }
    }
}

// NONMATCHING 92%: 1575F0 inlined; the trail-size float constants load in a different order (pooled addi+lfd), and the (u8) on the tex index adds a clrlslwi (without it CW strength-reduces (i+1)<<5 into an extra saved reg)
// .text:0x00156548 size:0x428 mapped:0x807955DC
#pragma dont_inline off
#if NONMATCHING
void fn_3_156548(u32 n, f32 x, f32 y, f32 z) {
    Vec quad[4];
    Mtx44 proj;
    Vec oldPos;
    Vec trail;
    Vec newPos;
    Vec* v;
    TexArchive* arc;
    f32 k;
    f32 size;
    f32 h;
    s32 i;
    k = lbl_3_rodata_392C / fn_80052768_getCamera(0)->zoom;
    fn_800B24D4(0xD);
    v = fn_3_1575F0(n);
    if (v == NULL) {
        return;
    }
    C_MTXFrustum(proj, lbl_3_rodata_3A20 * k, lbl_3_rodata_3A24 * k, lbl_3_rodata_39F0 * k, lbl_3_rodata_3A28 * k,
                 lbl_3_rodata_392C, lbl_3_rodata_3A2C);
    fn_800B27DC(proj, 0);
    PSMTXMultVec(((camera_803c639c_s*)fn_80052734(0))->view, v, &oldPos);
    v->x = x;
    v->y = y;
    v->z = z;
    PSMTXMultVec(((camera_803c639c_s*)fn_80052734(0))->view, v, &newPos);
    PSVECSubtract(&oldPos, &newPos, &oldPos);
    fn_800B2160(2);
    i = 7;
    do {
        switch (i) {
        case 0:
        case 4:
        case 7:
            PSVECScale(&oldPos, lbl_3_data_26BAC + ((f32)i * (lbl_3_data_26BB0 - lbl_3_data_26BAC)) / lbl_3_rodata_3A30, &trail);
            PSVECAdd(&newPos, &trail, &trail);
            if (i >= 4) {
                size = lbl_3_rodata_39A8 * (f32)(7 - i) * lbl_3_rodata_39F0 + lbl_3_rodata_39A8;
            } else {
                size = lbl_3_rodata_392C;
            }
            h = size * lbl_3_rodata_39A8;
            quad[0].x = trail.x - h;
            quad[0].y = trail.y - h;
            quad[0].z = trail.z;
            quad[1].x = trail.x - h;
            quad[1].y = trail.y + h;
            quad[1].z = trail.z;
            quad[2].x = trail.x + h;
            quad[2].y = trail.y + h;
            quad[2].z = trail.z;
            quad[3].x = trail.x + h;
            quad[3].y = trail.y - h;
            quad[3].z = trail.z;
            fn_800B2160(3);
            arc = MG_ASSETS.textures[1];
            fn_800B1468(quad, 0xFFFFFFFF, TEX_ARCHIVE_IMG(arc, 0));
            if (i >= 4) {
                size = lbl_3_rodata_39A8 * (f32)(7 - i) * lbl_3_rodata_39F0 + lbl_3_rodata_39A8;
            } else {
                size = lbl_3_rodata_392C;
            }
            h = size * lbl_3_rodata_39A8;
            quad[0].x = trail.x - h;
            quad[0].y = trail.y - h;
            quad[1].x = trail.x - h;
            quad[1].y = trail.y + h;
            quad[2].x = trail.x + h;
            quad[2].y = trail.y + h;
            quad[3].x = trail.x + h;
            quad[3].y = trail.y - h;
            fn_800B2160(2);
            arc = MG_ASSETS.textures[1];
            fn_800B1468(quad, 0xFFFFFFFF, &arc->entries[arc->entries[(u8)(i + 1)].index]);
            break;
        }
    } while (i-- != 0);
}
#endif
#pragma dont_inline on

// .text:0x00156970 size:0x394 mapped:0x80795A04
typedef struct {
    Vec pos;
    u32 color;
    u16 uv[2];
} RepQuadVtx; // size 0x14

void fn_3_156970(Vec* pos, u32 color, TexImage* tex) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    Mtx m;
    RepQuadVtx v[4];
    s32 i;
    PSMTXIdentity(m);
    for (i = 0; i < 4; i++) {
        memcpy(&v[i].pos, &pos[i], sizeof(Vec));
        v[i].color = color;
        memcpy(v[i].uv, &lbl_3_data_26B9C[i], 4);
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(GX_CULL_NONE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    if (lbl_3_bss_B854 != tex) {
        if (tex->tlut != NULL) {
            GXInitTexObjCI(&texObj, PTR32_GET(u8, tex->data), tex->width, tex->height, tex->format, GX_CLAMP, GX_CLAMP, GX_FALSE, 0);
            GXInitTlutObj(&tlutObj, PTR32_GET(void, tex->tlut), tex->tlutFormat, tex->tlutEntries);
            GXLoadTlut(&tlutObj, 0);
        } else {
            GXInitTexObj(&texObj, PTR32_GET(u8, tex->data), tex->width, tex->height, tex->format, GX_CLAMP, GX_CLAMP, GX_FALSE);
        }
        GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, tex->minLOD, tex->maxLOD, tex->lodBias, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&texObj, GX_TEXMAP0);
        lbl_3_bss_B854 = tex;
    }
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(v[i].pos.x, v[i].pos.y, v[i].pos.z);
        GXColor1u32(v[i].color);
        GXTexCoord2f32(v[i].uv[0], v[i].uv[1]);
    }
}

// NONMATCHING 94%: 1575F0 inlined; colour index *4 scheduled later, sin/cos temps of the trail rotation get different FPRs, (u8) on the tex index as in 156548
// .text:0x00156D04 size:0x608 mapped:0x80795D98
#pragma dont_inline off
#if NONMATCHING
void fn_3_156D04(u32 n, f32 x, f32 y, f32 z) {
    Vec quad[4];
    Mtx44 proj;
    Vec oldPos;
    Vec trail;
    Vec newPos;
    Vec tmp;
    Vec* v;
    TexArchive* arc;
    u32* colors;
    s32 ci;
    f32 k;
    f32 ang;
    f32 scale;
    f32 size;
    f32 h;
    s32 i;
    colors = lbl_3_data_26B84;
    ci = EFFECT_MG_OBJS[n].colorIdx;
    k = lbl_3_rodata_392C / fn_80052768_getCamera(0)->zoom;
    fn_800B24D4(0xD);
    v = fn_3_1575F0(n);
    if (v == NULL) {
        return;
    }
    C_MTXFrustum(proj, lbl_3_rodata_3A20 * k, lbl_3_rodata_3A24 * k, lbl_3_rodata_39F0 * k, lbl_3_rodata_3A28 * k,
                 lbl_3_rodata_392C, lbl_3_rodata_3A2C);
    GXSetProjection(proj, GX_PERSPECTIVE);
    PSMTXMultVec(((camera_803c639c_s*)fn_80052734(0))->view, v, &oldPos);
    v->x = x;
    v->y = y;
    v->z = z;
    PSMTXMultVec(((camera_803c639c_s*)fn_80052734(0))->view, v, &newPos);
    PSVECSubtract(&oldPos, &newPos, &oldPos);
    tmp = oldPos;
    ang = lbl_3_rodata_39B8 * (f32)((f64)(rand() % 15000) / lbl_3_rodata_39C8);
    ang *= (f32)(-((rand() % 2) * 2) + 1);
    oldPos.x = tmp.x * (f32)cos(ang) + tmp.y * -(f32)sin(ang);
    oldPos.y = tmp.x * (f32)sin(ang) + tmp.y * (f32)cos(ang);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    i = 7;
    scale = (f64)(rand() % 500 + 1000) / lbl_3_rodata_39C8;
    do {
        switch (i) {
        case 0:
        case 4:
        case 7:
            PSVECScale(&oldPos, scale * (lbl_3_data_26B94[0] + ((f32)i * (lbl_3_data_26B94[1] - lbl_3_data_26B94[0])) / lbl_3_rodata_3A30), &trail);
            PSVECAdd(&newPos, &trail, &trail);
            if (i >= 4) {
                size = (f32)(7 - i) * lbl_3_rodata_39F0 + lbl_3_rodata_392C;
            } else {
                size = lbl_3_rodata_39C4;
            }
            h = scale * (size * lbl_3_rodata_39A8);
            quad[0].x = trail.x - h;
            quad[0].y = trail.y - h;
            quad[0].z = trail.z;
            quad[1].x = trail.x - h;
            quad[1].y = trail.y + h;
            quad[1].z = trail.z;
            quad[2].x = trail.x + h;
            quad[2].y = trail.y + h;
            quad[2].z = trail.z;
            quad[3].x = trail.x + h;
            quad[3].y = trail.y - h;
            quad[3].z = trail.z;
            GXSetBlendMode(GX_BM_SUBTRACT, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
            if (lbl_3_bss_B858 != 0) {
                arc = MG_ASSETS.textures[1];
                fn_3_156970(quad, 0xFFFFFFFF, TEX_ARCHIVE_IMG(arc, 0));
            }
            if (i >= 4) {
                size = (f32)(7 - i) * lbl_3_rodata_39F0 + lbl_3_rodata_392C;
            } else {
                size = lbl_3_rodata_39C4;
            }
            h = scale * (size * lbl_3_rodata_39A8);
            quad[0].x = trail.x - h;
            quad[0].y = trail.y - h;
            quad[1].x = trail.x - h;
            quad[1].y = trail.y + h;
            quad[2].x = trail.x + h;
            quad[2].y = trail.y + h;
            quad[3].x = trail.x + h;
            quad[3].y = trail.y - h;
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
            arc = MG_ASSETS.textures[2];
            fn_3_156970(quad, colors[ci], TEX_ARCHIVE_IMG(arc, (u8)(i + 10)));
            break;
        }
    } while (i-- != 0);
}
#endif
#pragma dont_inline on

// .text:0x0015730C size:0xA0 mapped:0x807963A0
void fn_3_15730C(u32 n, f32 x, f32 y, f32 z) {
    Emitter* e = lbl_3_bss_B850;
    Particle* p;
    f32* v;
    if (e != NULL) {
        p = e->particles;
        while (n >= 7) {
            p = p->next;
            n -= 7;
        }
        v = &((VecSlotParticle*)p)->v[n].x;
    } else {
        v = NULL;
    }
    if (v != NULL) {
        v[0] = x;
        v[1] = y;
        v[2] = z;
    }
}

// NONMATCHING 94%: lbl_3_data_266A8 is this TU's own .data (orig keeps r29 = d+0x23C, t[0] via 0x23c(r31)); also f3/f4 swapped in the int->float divides
// .text:0x001573AC size:0x1C4 mapped:0x80796440
#if NONMATCHING
void fn_3_1573AC(struct CharActor* o) {
    Vec pos;
    Vec dir;
    struct { Control c; u32 pad[2]; } c;
    Mtx m;
    V3I* e;
    ParticleParams5** t;
    s16* q;
    s32 i;
    e = ((V3I*)&lbl_3_data_268E4[6]);
    pos.x = (f32)e[o->kind].x / lbl_3_rodata_3930;
    pos.y = (f32)e[o->kind].y / lbl_3_rodata_3930;
    pos.z = (f32)e[o->kind].z / lbl_3_rodata_3930;
    fn_8001B728(o->modelIndex, 4, &pos);
    c.c.type = 0;
    CTRLSetRotation(&c.c, o->rot.x, o->rot.y, o->rot.z);
    CTRLBuildMatrix(&c.c, m);
    dir.y = dir.x = lbl_3_rodata_3934[0];
    dir.z = lbl_3_rodata_392C;
    PSMTXMultVec(m, &dir, &dir);
    t = ((ParticleParams5**)lbl_3_data_268E4);
    t[0]->tex = t[1]->tex = t[2]->tex = MG_ASSETS.textures[2];
    q = EFFECT266A8->sparkTex[0];
    q += o->index * 2;
    t[0]->texIndex = t[1]->texIndex = q[1];
    fn_80030D88(&pos, &dir, ((ParticleParams5**)lbl_3_data_268E4)[0], 0x29);
    fn_80030D88(&pos, &dir, t[1], 0x29);
    fn_80030D88(&pos, &dir, t[2], 0x29);
}
#endif

// .text:0x00157570 size:0x18 mapped:0x80796604
extern Emitter* lbl_3_bss_B850;

void fn_3_157570(void) {
    lbl_3_bss_B850->u.t5.unk18 = 1;
}

// .text:0x00157588 size:0x68 mapped:0x8079661C
#ifdef TARGET_PC
// Called as an emitter update (s32(Emitter*)); see rep_1E08.c.
static s32 fn_3_15767C_update(Emitter* e) {
    // At the end of the minigame the owner drops lbl_3_bss_B850 while this emitter is still listed
    // for a frame; the GameCube read the null pointer's fields from low RAM, PC faults. End it.
    if (lbl_3_bss_B850 == NULL) {
        return 1;
    }
    fn_3_15767C();
    return 0;
}
#define FN_3_15767C_UPDATE fn_3_15767C_update
#else
#define FN_3_15767C_UPDATE (EmitterUpdateFn)fn_3_15767C
#endif
void fn_3_157588(int n) {
    Emitter* p = fn_80033A24(FN_3_15767C_UPDATE, 0x80, 0, (n + 6) / 7, 1, 0x28);
    lbl_3_bss_B850 = p;
    p->u.t5.unk18 = 0;
}

// .text:0x001575F0 size:0x8C mapped:0x80796684
#pragma dont_inline off
void* fn_3_1575F0(u32 n) {
    Emitter* e = lbl_3_bss_B850;
    Particle* p;
    if (e != NULL) {
        p = e->particles;
        while (n >= 7) {
            p = p->next;
            n -= 7;
        }
        return &((VecSlotParticle*)p)->v[n];
    }
    return NULL;
}
#pragma dont_inline on

// NONMATCHING 91%: orig hoists copies of d+8 (addi r25; mr r24/r23/r22) -> needs the .data defined in this TU
// .text:0x0015767C size:0x27C mapped:0x80796710
#if NONMATCHING
void fn_3_15767C(void) {
    Vec pos;
    Vec dir;
    Vec diff;
    EffectData266A8* d = EFFECT266A8;
    EffectMgObj* f;
    Vec* tgt;
    u32 i;
    s32 j;
    if (g_d_GameSettings.GameModeSelected == 7) {
        if (g_Minigame.GameMode_MiniGame == 5 && lbl_3_bss_B850->u.t5.unk18 == 0) {
        for (i = 0; i < 0x28; i++) {
            f = &EFFECT_MG_OBJS[i];
            if (f->active != 0) {
                pos.x = f->pos.x;
                pos.y = -f->pos.y;
                pos.z = f->pos.z;
                {
                    Emitter* e = lbl_3_bss_B850;
                    Particle* p;
                    u32 n = i;
                    if (e != NULL) {
                        p = e->particles;
                        while (n >= 7) {
                            p = p->next;
                            n -= 7;
                        }
                        tgt = &((VecSlotParticle*)p)->v[n];
                    } else {
                        tgt = NULL;
                    }
                }
                PSVECSubtract(tgt, &pos, &dir);
                if (0.0f != PSVECMag(&dir)) {
                    s32 k = f->colorIdx;
                    d->sparks[0].tex = d->sparks[1].tex = d->sparks[2].tex = MG_ASSETS.textures[2];
                    d->trail.tex = lbl_3_common_bss_35154.tex;
                    if (k <= 3 && k >= 0) {
                        s16* q = d->sparkTex[0];
                        q += k * 2;
                        for (j = 0; j < 2; j++) {
                            d->sparks[j].texIndex = q[j];
                        }
                        fn_8002F5F4(&pos, &dir, &d->trail);
                        if (lbl_80366158._28 == 0) {
                            fn_80030D88(&pos, &dir, &d->sparks[1], 0x29);
                            fn_80030D88(&pos, &dir, &d->sparks[2], 0x29);
                            PSVECNormalize(&dir, &dir);
                            PSVECSubtract(&pos, tgt, &diff);
                            fn_80030470(&pos, &dir, &diff, d->sparks, 0x29);
                        }
                    }
                }
            }
        }
        lbl_3_bss_B854 = NULL;
        }
    }
    if (lbl_3_bss_B850->u.t5.unk18 != 0) {
        lbl_3_bss_B850 = NULL;
    }
}
#endif

// .text:0x001578F8 size:0x24 mapped:0x8079698C
void fn_3_1578F8(void) {
    pitchingMachinePitching(0x16);
}

// .text:0x0015791C size:0x1A8 mapped:0x807969B0
f32 fn_3_15791C(s32 i) {
    s32 q = (i + 0x30) / 120;
    s32 t = (i + 0x30) % 120;
    f32 c;
    f32 r;
    if (t >= 48) {
        c = cos(lbl_3_rodata_3A34 * (lbl_3_rodata_392C + ((f32)t - lbl_3_rodata_3A38) / lbl_3_rodata_3A3C));
    } else {
        c = cos(lbl_3_rodata_3A34 * ((f32)t / lbl_3_rodata_3A38));
    }
    r = c * lbl_3_rodata_39A8;
    r += lbl_3_rodata_39A8;
    if (q != 0) {
        u8 gs = g_GameLogic.gameStatus;
        if (gs != 0xE && gs != 0x22 && gs != 0x24 && gs != 0x26) {
            r += lbl_3_rodata_39A8 * ((f32)i - lbl_3_rodata_3A3C) / lbl_3_rodata_3A40;
        }
    }
    return lbl_3_rodata_3A44 * r;
}

#ifdef TARGET_PC
u32 fn_3_157AC4(Emitter* o);
// fn_3_157DB8 (auto_00_00157DB8_text.c) with the real Emitter/Particle layout.
void port_fn_3_157DB8(s32 count) {
    Emitter* e = fn_80033A24((EmitterUpdateFn)fn_3_157AC4, 0x80, 0, 1, 1, 0x16);
    if (e != NULL) {
        e->u.seq.index = 0;
        e->u.seq.count = count;
        e->particles->texIndex = 0;
        PCOLOR_SET(e->particles->color, 0xFFFFFFFF);
    }
}
#endif

// NONMATCHING 95%: wave code is fn_3_15791C inlined by hand (call keeps f3/f4 swapped); only the 38D0 Vec copy loads are scheduled above the prologue stores
// .text:0x00157AC4 size:0x2F4 mapped:0x80796B58
#if NONMATCHING
u32 fn_3_157AC4(Emitter* o) {
    Mtx m;
    s32 q;
    s32 i;
    Particle* p;
    s32 t;
    f32 w;
    f32 c;
    f32 r;
    u32 res;
    Vec dir;
    p = o->particles;
    dir = lbl_3_rodata_38D0;
    PSMTXRotRad(m, 'Y', shortAngleToRad(g_Minigame._1AF8));
    PSMTXMultVec(m, &dir, &dir);
    i = o->u.seq.index;
    q = (i + 0x30) / 120;
    t = (i + 0x30) % 120;
    if (t >= 48) {
        c = cos(lbl_3_rodata_3A34 * (lbl_3_rodata_392C + ((f32)t - lbl_3_rodata_3A38) / lbl_3_rodata_3A3C));
    } else {
        c = cos(lbl_3_rodata_3A34 * ((f32)t / lbl_3_rodata_3A38));
    }
    r = c * lbl_3_rodata_39A8;
    r += lbl_3_rodata_39A8;
    if (q != 0) {
        u8 gs = g_GameLogic.gameStatus;
        if (gs != 0xE && gs != 0x22 && gs != 0x24 && gs != 0x26) {
            r += lbl_3_rodata_39A8 * ((f32)i - lbl_3_rodata_3A3C) / lbl_3_rodata_3A40;
        }
    }
    w = lbl_3_rodata_3A44 * r;
    p->sizeY = w;
    p->sizeX = w;
    p->pos.x = g_Minigame._1AE0 + dir.x + p->sizeX * EFFECT266A8->scale[0];
    p->pos.y = g_Minigame._1AE4 + dir.y + p->sizeY * EFFECT266A8->scale[1];
    p->pos.z = g_Minigame._1AE8 + dir.z;
    fn_8003403C(p->sizeX, p->sizeY);
    fn_80033CC8(o->particles, MG_ASSETS.textures[0]);
    if (lbl_80366158._28 == 0) {
        o->u.seq.index += 1;
    }
    if (g_Minigame._1A40 != 0) {
        res = 1;
    } else {
        res = 0;
        if (o->u.seq.index == o->u.seq.count) {
            if (g_GameLogic.gameStatus != 0xE) {
                res = 1;
            }
        }
    }
    return res;
}
#endif

#pragma dont_inline off

// .data of this file (0x266A8-0x26F00). The code reaches most of it through one pooled base
// (lbl_3_data_266A8 + offset), so the objects must stay in this order.
// .data 0x000266A8..0x00026F00
f32 lbl_3_data_266A8[3] = {0.45f, -0.4f, 0.0f};
s32 lbl_3_data_266B4[80] = {
    21, 2, 240000, 0, 0, 4, 2, 120000,
    90000, 0, 155, 500000, 1000000, -500000, 500000, -256,
    0, -28000, 1, 0, 7, 4, 78000, 60000,
    50000, 12, 6, 109000, 101000, 0, 60, 4500000,
    9500000, -1000000, 4500000, -256, 0, 0, 0, 0,
    18, 0, 90000, 120000, 10000, 20, 10, 103000,
    105999, 0, 60, 10000000, 18000000, 1000000, -1000000, 0x3c3c3c00,
    0, 0, 0, 0, 20, 8, 0, 250000,
    50000, 550000, 0, 0, 12, 13, 14, 15,
    16, 17, 18, 19, 720906, 983054, 1114128, 851980,
}; // particle parameters (x100000 fixed point), reached from lbl_3_data_266A8
#ifdef PORT_LP64
// GameCube block = lbl_3_data_266A8[3] ++ lbl_3_data_266B4[80] (83 words):
//   w0-1 scale, w2/22/42 sparks[k] (tex + 19 words), w62 trail (tex + 9 words, the last being
//   texIndex2[0]), w72-78 texIndex2[1..7], w79-82 sparkTex (s16 pairs, big-endian halves).
static EffectData266A8* port_effect266A8(void) {
    static EffectData266A8 s_eff;
    static int s_init;
    if (!s_init) {
        u32 w[83];
        s32 k;
        s32 i;
        s32* t;
        s_init = 1;
        memcpy(w, lbl_3_data_266A8, 3 * sizeof(u32));
        memcpy(w + 3, lbl_3_data_266B4, 80 * sizeof(u32));
        memcpy(&s_eff.scale[0], &w[0], sizeof(f32));
        memcpy(&s_eff.scale[1], &w[1], sizeof(f32));
        for (k = 0; k < 3; k++) {
            s_eff.sparks[k].tex = NULL; // w[2 + 20k] == 0; set at run time
            t = &s_eff.sparks[k].texIndex;
            for (i = 0; i < 19; i++) {
                t[i] = (s32)w[2 + 20 * k + 1 + i];
            }
        }
        s_eff.trail.tex = NULL; // w[62] == 0
        t = &s_eff.trail.texIndex;
        for (i = 0; i < 9; i++) {
            t[i] = (s32)w[63 + i];
        }
        t = s_eff.trail.texIndex2;
        for (i = 1; i < 8; i++) {
            t[i] = (s32)w[71 + i];
        }
        for (i = 0; i < 4; i++) {
            s_eff.sparkTex[i][0] = (s16)(w[79 + i] >> 16);
            s_eff.sparkTex[i][1] = (s16)(w[79 + i] & 0xFFFF);
        }
    }
    return &s_eff;
}
_Static_assert(sizeof(((EffectData266A8*)0)->trailRaw) >= offsetof(ParticleParams8, texIndex2) + 8 * sizeof(s32),
               "trail indices must fit");
#endif
s32 lbl_3_data_267F4[20] = {
    0, 10, 3, 100000, 30000, 10000, 12, 8,
    110000, 50000, 0, 60, 4500000, 20000000, 0, 2000000,
    -256, 0, 75000, 0,
}; // particle parameters (x100000 fixed point)
s32 lbl_3_data_26844[20] = {
    0, 10, 5, 18000, 20000, 60000, 12, 6,
    109000, 101000, 0, 60, 4500000, 9400000, -1000000, 4500000,
    -256, 0, 75000, 0,
}; // particle parameters (x100000 fixed point)
s32 lbl_3_data_26894[20] = {
    0, 18, 1, 60000, 10000, 50000, 30, 8,
    104000, 106000, 0, 90, 12800000, 10000000, 1000000, 6000000,
    0x3c3c3c00, 0, 75000, 0,
}; // particle parameters (x100000 fixed point)
// Parameter sets by effect id (code reaches it as lbl_3_data_266A8 + 0x23C).
s32* lbl_3_data_268E4[168] = {lbl_3_data_267F4, lbl_3_data_26844, lbl_3_data_26894};
u32 lbl_3_data_26B84[4] = {0xFF0000FF, 0x0000FFFF, 0xFFFF00FF, 0x00FF00FF}; // RGBA colours (lbl_3_data_266A8 + 0x4DC)
f32 lbl_3_data_26B94[2] = {-0.4f, 6.0f}; // trail scale range (lbl_3_data_266A8[0x13B..0x13C])
u32 lbl_3_data_26B9C[4] = {
    0x00000000, 0x00010000, 0x00010001, 0x00000001,
};
f32 lbl_3_data_26BAC = -0.2f;
f32 lbl_3_data_26BB0 = 3.0f;
Vec lbl_3_data_26BB4 = {0.087f, -0.757f, 0.001f};
s32 lbl_3_data_26BC0[7] = {
    3, 32, 0, 35000, 0, 255, 32,
};
s32 lbl_3_data_26BDC[4] = {
    16, 0, 255, 28,
};
s32 lbl_3_data_26BEC[4] = {
    0, 150000, 0, 16,
};
s32 lbl_3_data_26BFC[4] = {
    0, 15000, 0, 32,
};
s32 lbl_3_data_26C0C[4] = {
    100000, 100000, 10000, 64,
};
f32 lbl_3_data_26C1C[8] = {
    -0.75f, 0.699999988f, 0.75f, 0.699999988f, -0.75f, -0.699999988f, 0.75f, -0.699999988f,
};
s32 lbl_3_data_26C3C[22] = {
    2, 32, 0, 50000, 0, 255, 32, 15,
    9, 150, 40000, 70000, 30000, 80000, 4400, 50000,
    12000, 15000, 0, 104719, 60, 29,
};
s32 lbl_3_data_26C94[9] = {
    2, 90, 200000, 100000, 0, 0, 255, 36,
    30,
};
u8 lbl_3_data_26CB8[24] = {4, 5, 6, 7, 8, 16, 17, 18, 19, 20, 22, 23, 24, 25, 26, 28, 29, 30, 31, 32, 33, 34, 35, 0};
s32 lbl_3_data_26CD0[12] = {
    2, 6, 40, 100000, 50000, 0, 255, 127,
    0, 40000, 440, 31,
};
s32 lbl_3_data_26D00[20] = {6, 5, 645, 5, 0, 600000, 800000, 0, 255, 0, 2, 0, 200000, 300000, 0, 255, 0, 20, 20, 32};
Vec lbl_3_data_26D50[1] = {
    {3.70000005f, -9.30000019f, 0.0f},
};
s32 lbl_3_data_26D5C[11] = {
    7, 1, 8, 5, 0, 1000000, 1200000, 0,
    255, 0, 33,
};
s32 lbl_3_data_26D88[15] = {
    8, 5, 30, 5, 0, 250000, 400000, 255,
    255, 255, 0, 80, 0, 100000, 34,
};
s32 lbl_3_data_26DC4[15] = {
    8, 16, 30, 15, 250000, 375000, 500000, 0,
    0, 0, 255, 127, 0, 100000, 34,
};
Vec lbl_3_data_26E00[3] = {
    {2.03500009f, -5.71799994f, 1.01400006f}, {1.79299998f, -4.52299976f, 0.913999975f}, {1.28999996f, -4.11899996f, 0.814999998f},
};
s32 lbl_3_data_26E24[7] = {
    3, 16, 100, 0, 30000, 0, 255,
};
s32 lbl_3_data_26E40[15] = {
    8, 6, 60, 30000, 5, 0, 100000, 40000,
    50000, 0, 220, 0, 30000, 15000, 36,
};
s32 lbl_3_data_26E7C[8] = {
    100, 5000, 1200000, 15000, 15000, 0, 60, 37,
};
s32 lbl_3_data_26E9C[25] = {
    6, 30, 4, 5, 0, 250000, 350000, 0,
    255, 0, 5, 20, 7, 2, 0, 250000,
    350000, 0, 120, 0, 0, 4259909, 5046345, 4128768,
    0,
};

