#ifdef TARGET_PC
#define MG_STARDASH_PTR PTR32_GET(f32, g_Minigame.starDashRelated_0_5Or1_5)
#else
#define MG_STARDASH_PTR (g_Minigame.starDashRelated_0_5Or1_5)
#endif
#include "game/rep_3520.h"
#include "game/rep_1838.h"
#include "game/rep_540.h"
#include "game/rep_AC8.h"
#include "game/rep_D0.h"
#include "Dolphin/mtx.h"
#include "Dolphin/stl.h"
#include "game/UnknownHomes_Game.h"
#define REP_HEADER_FN repHeader_3520
#include "header_rep_inline.h"
#include "stl/math.h"
#pragma dont_inline on


#include "static/UnknownHomes_Static.h"
#include "main/file_800B993C.h"
extern s16 lbl_3_data_21AF0[];
extern u8 lbl_3_data_88DC[];
extern f64 lbl_3_rodata_3698;
extern f32 lbl_3_rodata_364C;
extern f32 lbl_3_rodata_3690;
// The original passes the raw (unextended) byte to these s8-taking functions,
// as an unprototyped call does.
extern void fn_3_14E988(s32 arg); // defined (s8); the calls here pass an int (no extsb)
extern void fn_800115C8(s32 arg); // defined (s8); the calls here pass an int (no extsb)
extern f32 lbl_3_rodata_35D0;
extern f32 lbl_3_data_219AC[];
extern s16 lbl_3_data_21A30[];
extern f32 lbl_3_data_21A14[];
extern f32 lbl_3_rodata_363C;
extern f32 lbl_3_rodata_3688;
extern f32 lbl_3_rodata_368C;
extern f64 lbl_3_rodata_3670;
extern f32 lbl_3_rodata_3628;
extern f64 lbl_3_rodata_3678;
extern f64 lbl_3_rodata_3680;
extern s16 lbl_3_data_21AD0[][4]; // per difficulty
extern f32 lbl_3_rodata_3648;
extern f32 lbl_3_rodata_36C8;
extern f32 lbl_3_data_21A48[];
extern f32 lbl_3_rodata_35D8;
extern f32 lbl_3_rodata_3620;
extern f32 lbl_3_rodata_35DC;
extern f32 lbl_3_rodata_3638;
extern s16 lbl_3_data_21A3C[];
extern s16 lbl_3_data_21A04[];
extern s16 lbl_3_data_21A44;
extern s16 lbl_3_data_21B20[];
extern f32 lbl_3_data_21AF4;
extern f64 lbl_3_rodata_3668;
extern f64 lbl_3_rodata_35E0;
extern f32 lbl_3_rodata_365C;
extern void fn_800528B4(void);
extern int rand();
extern u32 fn_3_90064(s32 id);
extern void fn_3_150010(s8 a);
extern void fn_3_106EB0(void);
extern f32 lbl_3_data_21A64;
extern s16 lbl_3_data_21A90[];
extern InMemFielderType g_Fielders[9];
extern s16 lbl_3_data_21B8C[];
extern f32 lbl_3_data_219B8[];
extern u8 lbl_3_data_21278[];
extern void fn_3_10F550(s32, u8);
extern void fn_3_5A6D4(s32);
extern void changeScene(s32, s32);
extern s8 lbl_3_data_21B88[];
extern f32 lbl_3_rodata_35FC;
extern f32 lbl_3_rodata_3600;
extern f32 lbl_3_rodata_363C;
extern f32 lbl_3_rodata_35C4[];
extern f32 lbl_3_rodata_35B8[];
extern s16 lbl_3_data_21A60;
extern f32 lbl_3_rodata_3644;
extern void fn_3_157570(void);
extern void fn_3_DE4FC(void);
extern void fn_80011578(void);
extern void fn_3_14E894(void);
extern u8 lbl_800EFBA4[];
extern s32 sndFXStartEx(s32, u8, u8, u8);

extern u8 lbl_80366158[];
#ifdef TARGET_PC // the struct holds pointers: reach the byte through it (port/game/views.c)
u8* port_80366158_byte(u32 gcOffset);
#define LBL_80366158_U8(off) (*port_80366158_byte(off))
#else
#define LBL_80366158_U8(off) lbl_80366158[off]
#endif
extern s8 lbl_3_data_26580;
extern s32 fn_800247E4(s32, s32, s32, s32);
extern void DCFlushRange(void*, u32);
#ifndef TARGET_PC
extern void GXLoadTexObj(void*, s32);
extern void GXSetTexCoordGen2(s32, s32, s32, s32, s32, s32);
extern void GXSetTevOrder(s32, s32, s32, s32);
extern void GXSetTevColorIn(s32, s32, s32, s32, s32);
extern void GXSetTevColorOp(s32, s32, s32, s32, s32, s32);
extern void GXSetTevAlphaIn(s32, s32, s32, s32, s32);
extern void GXSetTevAlphaOp(s32, s32, s32, s32, s32, s32);
extern void GXInitTexObj(void*, void*, s32, s32, s32, s32, s32, s32);
extern void GXInitTexObjLOD(void*, s32, s32, f32, f32, f32, s32, s32, s32);
#endif
static u8 lbl_3_bss_B781; // difficulty row for the obstacle drop timings
static u8 lbl_3_bss_B780; // number of active obstacles
static u8 s_buf[0x40];
static u8 s_pad[0x18];
#ifdef TARGET_PC
static GXTexObj s_tex[1]; // GXTexObj is 0x40 bytes in aurora
#else
static u8 s_tex[0x20];
#endif
static s32 s_cnt;
static s16 lbl_3_bss_B702;
static u8 s_B700;

// .text:0x00132EDC size:0x208
void fn_3_132EDC(struct DODisplayObj* dispObj, s32* stage, s32* coord, s32* map, u8* c1, u8* c2, MtxPtr camera) {
    s32 v;
    s32 i;
    s_cnt += (LBL_80366158_U8(0x28) == 0);
    if ((s_cnt & 1) == 0) {
        {
            u8* r = s_buf;
            v = r[fn_800247E4(0, 0, 4, 4)];
        }
        v += lbl_3_data_26580 * 2;
        if (v > 0xFF) {
            v = 0xFF;
        } else if (v < 0) {
            v = 0;
        }
        for (i = 0; i < 32; i += 2) {
            s_buf[i] = v;
        }
        DCFlushRange(s_buf, 0x40);
        if (v + lbl_3_data_26580 * 2 > 0xFF || v + lbl_3_data_26580 * 2 < 0) {
            lbl_3_data_26580 *= -1;
        }
    }
    GXLoadTexObj(s_tex, *map);
    GXSetTexCoordGen2(*coord, 1, 4, 0x3C, 0, 0x7D);
    GXSetTevOrder(*stage, *coord, *map, 0xFF);
    GXSetTevColorIn(*stage, 0xF, 8, 9, 0);
    GXSetTevColorOp(*stage, 0, 0, 0, 1, 0);
    GXSetTevAlphaIn(*stage, 7, 7, 7, 0);
    GXSetTevAlphaOp(*stage, 0, 0, 0, 1, 0);
    *stage += 1;
    *coord += 1;
    *map += 1;
    *c1 += 1;
    *c2 += 1;
}

// .text:0x001330E4 size:0x11C
void fn_3_1330E4(void) {
    s32 v;
    s32 i;
    s_cnt += (LBL_80366158_U8(0x28) == 0);
    if ((s_cnt & 1) == 0) {
        v = s_buf[fn_800247E4(0, 0, 4, 4)];
        v += lbl_3_data_26580 * 2;
        if (v > 0xFF) {
            v = 0xFF;
        } else if (v < 0) {
            v = 0;
        }
        for (i = 0; i < 32; i += 2) {
            s_buf[i] = v;
        }
        DCFlushRange(s_buf, 0x40);
        if (v + lbl_3_data_26580 * 2 > 0xFF || v + lbl_3_data_26580 * 2 < 0) {
            lbl_3_data_26580 *= -1;
        }
    }
}

// .text:0x00133200 size:0x120 mapped:0x80772294
void fn_3_133200(void) {
    u32 i;
    u32 j;
    u32 idx;
    u8* p;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            idx = fn_800247E4(j, i, 4, 4);
            if (idx < 0x20) {
                p = s_buf;
                p += idx;
                p[2] = 0xFF;
                p[0] = 0xFF;
                p[3] = 0x96;
                p[1] = 0x96;
            } else {
                p = s_buf;
                p += idx;
                p[2] = 0x96;
                p[0] = 0x96;
                p[3] = 0x96;
                p[1] = 0x96;
            }
        }
    }
    GXInitTexObj(s_tex, s_buf, 4, 4, 6, 1, 1, 0);
    GXInitTexObjLOD(s_tex, 1, 1, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    lbl_3_data_26580 = -1;
    s_cnt = 0;
}

// .text:0x00133320 size:0x2C mapped:0x807723B4
#define MG3520 ((Mg3520*)&g_Minigame) // this minigame's view of the shared minigame area
// Coin pool (100 entries) overlaid on g_Minigame: positions at 0xCD0, velocities at 0x1180,
// per-coin timers at 0x17C8 and states at 0x193A. MiniGameStruct only declares the first 30.
#define COIN_POS(i) (MG3520->coinPos[i])
#define COIN_VEL(i) (MG3520->coinVel[i])
#define COIN_TIMER(i) (MG3520->coinTimer[i])
#define COIN_STATE(i) (MG3520->coinState[i])

#pragma opt_unroll_loops off
void fn_3_133320(void) {
    s8 i = 0;
    do {
        g_Minigame._1DC8[i] = 0;
        i++;
    } while (i < 4);
}
#pragma opt_unroll_loops reset

// .text:0x0013334C size:0x1170 mapped:0x807723E0
extern void* _OSAllocFromHeap(s32 align, s32 size);
extern u8 lbl_803CBBC0;
extern s16 lbl_3_data_21A88[];
extern f32 lbl_3_data_21B28[];
extern f32 lbl_3_data_21B38[];
extern f32 lbl_3_data_21B48[];
extern f32 lbl_3_data_21B58[];
extern f32 lbl_3_data_21B68[];
extern f32 lbl_3_data_21B78[];
extern f32 lbl_3_rodata_35D4;
extern f32 lbl_3_rodata_35F8;
extern f32 lbl_3_rodata_35FC;
extern f32 lbl_3_rodata_3600;
extern f32 lbl_3_rodata_35D8;
extern f32 lbl_3_rodata_35DC;
static inline void h133320(void);
static inline int quad_i(f32 x, f32 y);
#define CPU_STATE (&MG3520->cpu)
static inline void arenaRot(CpuState3520* cpu, f32* outX, f32* outZ, f32 x, f32 z) {
    x = x - lbl_3_data_21A48[0];
    z = z - lbl_3_data_21A48[2];
    *outX = x * cpu->rotCos - z * cpu->rotSin;
    *outZ = x * cpu->rotSin + z * cpu->rotCos;
}
// Quadrant (0..3) of a world point in the rotating arena frame.
static inline s32 arenaQuad(CpuState3520* cpu, f32 x, f32 z) {
    f32 qx, qz;
    arenaRot(cpu, &qx, &qz, x, z);
    return quad_i(qx, qz);
}
// Turn from angle a toward b by at most 1/lbl_3_data_21B8C[c] of the difference (fn_3_1345AC).
static inline s16 h1345AC(s16 a, s16 b, s32 c) {
    s16 d;
    if (a < 0 || b < 0) {
        return b;
    }
    d = fn_3_9FCA4(b, a) / lbl_3_data_21B8C[c];
    if (d == 0 || (((d >> 31) ^ d) - (d >> 31)) > 0x5DC) {
        return b;
    }
    return fn_3_9FE6C_normalizeAngle(a + d);
}
// No active obstacle within the box half-size of (x, z).
static inline int noObstacleNear(f32 x, f32 z) {
    s8 k = 0;
    do {
        u8 st = MG3520->objs[k].state;
        if (st >= 1 && st <= 3) {
            f32 ax = fabs(MG3520->objs[k].pos.x - x);
            f32 az = fabs(MG3520->objs[k].pos.z - z);
            if (ax <= lbl_3_rodata_35D8 && az <= lbl_3_rodata_35DC) {
                break;
            }
        }
        k++;
    } while (k < lbl_3_data_21A88[g_Minigame.soloMinigameDifficulty]);
    return k >= lbl_3_data_21A88[g_Minigame.soloMinigameDifficulty];
}
// NONMATCHING 89%: the original keeps &g_Minigame copies on the stack and allocates the
// per-player loop registers differently; logic and calls are the same
#if NONMATCHING
// CPU control for the minigame players: pick a target (ball, coin bag, item or
// best coin), steer around obstacles and the powered-up player, and dash.
void fn_3_13334C(void) {
    CpuState3520* cpu = CPU_STATE;
    CoinCand* cands = _OSAllocFromHeap(4, 1000);
    s32 ballQuad, bagQuad, itemQuad;
    u32 nCands;
    s8 i;
    h133320();
    cpu->rotSin = sin(-fn_3_9FDD8(g_Minigame._1D64));
    cpu->rotCos = cos(-fn_3_9FDD8(g_Minigame._1D64));
    ballQuad = g_Minigame._72A != 0 ? arenaQuad(cpu, g_Minigame._6E8, g_Minigame._6F0) : 4;
    bagQuad = g_Minigame._B6C._40[0] != 0 ? arenaQuad(cpu, g_Minigame._B6C._0.x, g_Minigame._B6C._0.z) : 4;
    itemQuad = g_Minigame._CCE[0] == 1 ? arenaQuad(cpu, g_Minigame._CB0, g_Minigame._CB8) : 4;
    // collect the free coins
    nCands = 0;
    {
        CoinCand* c = cands;
        s8 n;
        for (n = 0; n < 100; n++) {
            if (COIN_STATE(n) == 1) {
                c->coin = n;
                arenaRot(cpu, &c->x, &c->z, COIN_POS(n).x, COIN_POS(n).z);
                c->quad = quad_i(c->x, c->z);
                c++;
                nCands++;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        s8 ch = g_Minigame.minigameControlStruct[0].characterIndex[i];
        CpuSlot3520* slot = &cpu->slot[i];
        InputStruct* in;
        InMemFielderType* f;
        u8 ai;
        f32 qx, qz;
        u32 quad;
        if (ch < 0 || ch >= 4 || g_Minigame.minigameControlStruct[0].battingHandedness[i] == 0) {
            continue;
        }
        g_Minigame._1DC8[ch] = 1;
        memset(&g_Minigame._1D7C[ch], 0, sizeof(InputStruct));
        g_Minigame._1D7C[ch].controlStickAngle = -1;
        in = &g_Minigame._1D7C[ch];
        ai = g_Minigame.minigameControlStruct[0].aIStrength[i];
        f = &g_Fielders[g_Minigame.minigameFielderIndex[i]];
        arenaRot(cpu, &qx, &qz, f->pos.x, f->pos.z);
        quad = quad_i(qx, qz);
        switch (slot->state) {
        case 0: {
            f32 tx, tz;
            u32 tq;
            if (lbl_803CBBC0 != 0 && g_FieldingLogic.boost[i].scale <= lbl_3_data_21B28[ai] &&
                (g_Minigame._1D72 == 0 || i == g_Minigame._1D6D || fn_3_135520(qx, qz, lbl_3_rodata_35D4) == 0)) {
                in->buttonInput = in->newButtonInput |= 0x200;
            }
            tq = 4;
            if (i == g_Minigame._1D6D) {
                fn_3_134658(i, &tx, &tz, (s32*)&tq);
            }
            if (tq == 4 && g_Minigame._72A != 0) {
                tx = g_Minigame._6E8;
                tz = g_Minigame._6F0;
                tq = ballQuad;
            }
            if (tq == 4 && g_Minigame._B6C._40[0] != 0) {
                InMemFielderType* m = &g_Fielders[g_Minigame.minigameFielderIndex[i]];
                f32 dz = m->pos.z - g_Minigame._B6C._0.z;
                f32 dx = m->pos.x - g_Minigame._B6C._0.x;
                if (dx * dx + dz * dz <= lbl_3_data_21B78[ai] * lbl_3_data_21B78[ai] &&
                    noObstacleNear(g_Minigame._B6C._0.x, g_Minigame._B6C._0.z)) {
                    tx = g_Minigame._B6C._0.x;
                    tz = g_Minigame._B6C._0.z;
                    tq = bagQuad;
                }
            }
            if (tq == 4 && g_Minigame._CCE[0] == 1) {
                InMemFielderType* m = &g_Fielders[g_Minigame.minigameFielderIndex[i]];
                f32 dz = m->pos.z - g_Minigame._CB8;
                f32 dx = m->pos.x - g_Minigame._CB0;
                if (dx * dx + dz * dz <= lbl_3_data_21B68[ai] * lbl_3_data_21B68[ai] &&
                    noObstacleNear(g_Minigame._CB0, g_Minigame._CB8)) {
                    tx = g_Minigame._CB0;
                    tz = g_Minigame._CB8;
                    tq = itemQuad;
                }
            }
            if (tq == 4 && (u32)g_Minigame._17C4 != 0) {
                CoinCand* best = fn_3_1350BC(i, quad, nCands, cands);
                if (best != NULL && best->valid != 0) {
                    tx = COIN_POS(best->coin).x;
                    tz = COIN_POS(best->coin).z;
                    tq = best->quad;
                }
            }
            if (tq != 4) {
                InMemFielderType* m;
                if (fn_3_134C80(i, quad, tq, tx, tz)) {
                    tq = fn_3_13493C(i, &tx, &tz, 2);
                }
                m = &g_Fielders[g_Minigame.minigameFielderIndex[i]];
                in->controlStickAngle = h1345AC(slot->lastStick, radToShortAngle(atan2(tz - m->pos.z, tx - m->pos.x)), ai);
            }
            // keep away from the powered-up player
            if (g_Minigame._1D6D >= 0 && i != g_Minigame._1D6D) {
                InMemFielderType* m = &g_Fielders[g_Minigame.minigameFielderIndex[i]];
                InMemFielderType* h = &g_Fielders[g_Minigame.minigameFielderIndex[g_Minigame._1D6D]];
                f32 dz = m->pos.z - h->pos.z;
                f32 dx = m->pos.x - h->pos.x;
                if (dx * dx + dz * dz <= lbl_3_data_21B38[ai] * lbl_3_data_21B38[ai]) {
                    s16 off, away, tangent, d;
                    InMemFielderType* p;
                    {
                        // fn_3_1344BC(g_Minigame._1D6D, i)
                        InMemFielderType* pi = &g_Fielders[g_Minigame.minigameFielderIndex[i]];
                        f32 angH = atan2(h->pos.z - lbl_3_data_21A48[2], h->pos.x - lbl_3_data_21A48[0]);
                        s16 si = radToShortAngle(atan2(pi->pos.z - lbl_3_data_21A48[2], pi->pos.x - lbl_3_data_21A48[0]));
                        off = fn_3_9FCA4(radToShortAngle(angH), si) >= 0 ? 0 : 0x800;
                    }
                    away = radToShortAngle(atan2(dz, dx));
                    p = &g_Fielders[g_Minigame.minigameFielderIndex[i]];
                    tangent = fn_3_9FE6C_normalizeAngle(
                        radToShortAngle(atan2(-(p->pos.x - lbl_3_data_21A48[0]), p->pos.z - lbl_3_data_21A48[2])) + off);
                    d = fn_3_9FCA4(tangent, away) / 2;
                    in->controlStickAngle = fn_3_9FE6C_normalizeAngle(radToShortAngle(atan2(dz, dx)) + d);
                }
            }
            // steer around obstacles
            if (i != g_Minigame._1D6D) {
                s8 k = 0;
                do {
                    u8 st = MG3520->objs[k].state;
                    if (st >= 1 && st <= 3) {
                        InMemFielderType* m = &g_Fielders[g_Minigame.minigameFielderIndex[i]];
                        f32 dz = m->pos.z - MG3520->objs[k].pos.z;
                        f32 dx = m->pos.x - MG3520->objs[k].pos.x;
                        if (dx * dx + dz * dz <= lbl_3_data_21B48[ai] * lbl_3_data_21B48[ai]) {
                            s16 a = fn_3_9FCA4(radToShortAngle(atan2(dz, dx)), in->controlStickAngle);
                            in->controlStickAngle =
                                h1345AC(in->controlStickAngle, fn_3_9FE6C_normalizeAngle(in->controlStickAngle + a / 2), ai);
                        }
                    }
                    k++;
                } while (k < lbl_3_data_21A88[g_Minigame.soloMinigameDifficulty]);
            }
            // steer away from a dropped item
            if (g_Minigame._CCE[0] == 2) {
                InMemFielderType* m = &g_Fielders[g_Minigame.minigameFielderIndex[i]];
                f32 dz = m->pos.z - g_Minigame._CB8;
                f32 dx = m->pos.x - g_Minigame._CB0;
                if (dx * dx + dz * dz <= lbl_3_data_21B58[ai] * lbl_3_data_21B58[ai]) {
                    s16 a = fn_3_9FCA4(radToShortAngle(atan2(dz, dx)), in->controlStickAngle);
                    in->controlStickAngle =
                        h1345AC(in->controlStickAngle, fn_3_9FE6C_normalizeAngle(in->controlStickAngle + a / 2), ai);
                }
            }
            // spokes are spinning: dash out of the way when near one
            if (g_Minigame._1D72 != 0 && i != g_Minigame._1D6D) {
                f32 r = dolsqrtf2(qx * qx + qz * qz);
                if (fn_3_135520(qx, qz, lbl_3_rodata_35F8 * r + slot->radius) == 1) {
                    InMemFielderType* m;
                    if (RandomInt_Game(100) < lbl_3_data_21B88[ai]) {
                        slot->radius = lbl_3_rodata_35FC;
                    } else {
                        slot->radius = lbl_3_rodata_3600;
                    }
                    m = &g_Fielders[g_Minigame.minigameFielderIndex[i]];
                    in->controlStickAngle = fn_3_9FE6C_normalizeAngle(
                        radToShortAngle(atan2(-(m->pos.x - lbl_3_data_21A48[0]), m->pos.z - lbl_3_data_21A48[2])));
                    slot->state = 1;
                }
            }
            break;
        }
        case 1:
            slot->timer = 1;
            slot->state = 2;
            // fallthrough
        case 2: {
            InMemFielderType* m = &g_Fielders[g_Minigame.minigameFielderIndex[i]];
            in->controlStickAngle = fn_3_9FE6C_normalizeAngle(
                radToShortAngle(atan2(-(m->pos.x - lbl_3_data_21A48[0]), m->pos.z - lbl_3_data_21A48[2])));
            if (slot->timer-- <= 0) {
                g_Minigame._1D7C[ch].buttonInput |= 0x100;
                g_Minigame._1D7C[ch].newButtonInput |= 0x100;
                slot->state = 3;
            }
            break;
        }
        case 3:
            if (f->_203 == 0) {
                slot->state = 0;
            }
            break;
        }
        slot->lastStick = in->controlStickAngle;
    }
    fn_800ACFB0(cands);
}
#endif

// .text:0x001344BC size:0xF0 mapped:0x80773550
int fn_3_1344BC(int a, int b) {
    u8* tbl = (u8*)g_Minigame.minigameFielderIndex;
    int ib = (s8)tbl[b] * sizeof(InMemFielderType);
    int ia = (s8)tbl[a] * sizeof(InMemFielderType);
    u8* fz = (u8*)&g_Fielders[0].pos.z; // byte cursors into g_Fielders
    f32 dxb = *(f32*)((u8*)&g_Fielders[0].pos.x + ib) - lbl_3_data_21A48[0];
    f32 dzb = *(f32*)(fz + ib) - lbl_3_data_21A48[2];
    f32 angA = atan2(*(f32*)(fz + ia) - lbl_3_data_21A48[2], *(f32*)((u8*)&g_Fielders[0].pos.x + ia) - lbl_3_data_21A48[0]);
    s16 sb = radToShortAngle(atan2(dzb, dxb));
    s16 sa = radToShortAngle(angA);
    return fn_3_9FCA4(sa, sb) >= 0;
}

// .text:0x001345AC size:0xAC mapped:0x80773640
s16 fn_3_1345AC(s16 a, s16 b, s32 c) {
    s16 d;
    if (a < 0 || b < 0) {
        return b;
    }
    d = fn_3_9FCA4(b, a) / lbl_3_data_21B8C[c];
    if (d == 0 || (((d >> 31) ^ d) - (d >> 31)) > 0x5DC) {
        return b;
    }
    return fn_3_9FE6C_normalizeAngle(a + d);
}

// .text:0x00134658 size:0x2B0 mapped:0x807736EC
typedef struct { f32 d; s16 pts; u8 idx; u8 pad; } F134658Ent;
extern f32 lbl_3_rodata_3610;
extern void fn_800246D4(void*, void*, void*, int, int);
#define SEL134658(IDX)                                                   \
    {                                                                    \
        s8* tb = g_Minigame.minigameFielderIndex;                                            \
        f32 sx, sz;                                                      \
        *ox = g_Fielders[tb[IDX]].pos.x;                                 \
        *oz = g_Fielders[tb[IDX]].pos.z;                                 \
        sx = *ox;                                                        \
        sz = *oz;                                                        \
        if (sx >= lbl_3_rodata_35D0) {                                   \
            if (sz >= lbl_3_rodata_35D0) {                               \
                r = 0;                                                   \
            } else {                                                     \
                r = 3;                                                   \
            }                                                            \
        } else if (sz >= lbl_3_rodata_35D0) {                            \
            r = 1;                                                       \
        } else {                                                         \
            r = 2;                                                       \
        }                                                                \
        *out = r;                                                        \
    }
// NONMATCHING 93%: g_Minigame base lands in r0 then mr (orig addi r7,r7 directly); float regs f1/f3 swapped
#if NONMATCHING
void fn_3_134658(int a, f32* ox, f32* oz, s32* out) {
    F134658Ent e[4];
    F134658Ent* q = e;
    F134658Ent* w = q;
    u32 n = 0;
    u32 i = 0;
    u32 k;
    s32 r;
    do {
        if (i != a && g_Minigame.starDashStunType[i] == 0) {
            InMemFielderType* f = &g_Fielders[g_Minigame.minigameFielderIndex[i]];
            if (f->_20F == 0) {
                InMemFielderType* h;
                f32 dx, dz;
                n++;
                h = &g_Fielders[g_Minigame.minigameFielderIndex[a]];
                dz = f->pos.z - h->pos.z;
                dx = f->pos.x - h->pos.x;
                w->d = dx * dx + dz * dz;
                w->pts = g_Minigame.miniGameCurrentPoints[i];
                w->idx = i;
                w++;
            }
        }
        i++;
    } while (i < 4);
    if (n != 0) {
        fn_800246D4(fn_3_134918, e, e, 8, n);
        k = 0;
        do {
            if (q->d <= lbl_3_rodata_3610 && q->pts > 0) {
                SEL134658(e[k].idx);
                return;
            }
            k++;
            q++;
        } while (k < n);
        fn_800246D4(fn_3_134908, e, e, 8, n);
        if (e[0].pts > 0) {
            SEL134658(e[0].idx);
        }
    }
}
#endif


// .text:0x00134908 size:0x10 mapped:0x8077399C
s32 fn_3_134908(s16* a, s16* b) {
    return b[2] - a[2];
}

// .text:0x00134918 size:0x24 mapped:0x807739AC
s32 fn_3_134918(f32* a, f32* b) {
    if (*a < *b) {
        return -1;
    }
    return *a > *b;
}

// .text:0x0013493C size:0x344 mapped:0x807739D0
static inline void rot_i(f32* outX, f32* outY, f32 x, f32 y) {
    f32* d = lbl_3_data_21A48;
    Mg3520U* g = (Mg3520U*)&g_Minigame;
    x = x - d[0];
    y = y - d[2];
    *outX = x * *(f32*)&g->mg._1DD3[29] - y * *(f32*)&g->mg._1DD3[25];
    *outY = x * *(f32*)&g->mg._1DD3[25] + y * *(f32*)&g->mg._1DD3[29];
}
static inline int quad_i(f32 x, f32 y) {
    if (x >= 0.0f) {
        if (y >= 0.0f) {
            return 0;
        }
        return 3;
    }
    if (y >= 0.0f) {
        return 1;
    }
    return 2;
}
extern const f32 lbl_3_rodata_3614;
extern const f32 lbl_3_rodata_3618;
extern const f32 lbl_3_rodata_361C;
int fn_3_13493C(u32 idx, f32* ox, f32* oz, u32 depth) {
    u8* fi = (u8*)g_Minigame.minigameFielderIndex + idx;
    u8* fz = (u8*)&g_Fielders[0].pos.z; // stepped by fielder * sizeof(InMemFielderType)
    f32 ang, a, x1, z1, x2, z2, d1, dx, dz;
    dx = *ox - g_Fielders[((s8)*fi)].pos.x;
    dz = *oz - *(f32*)(fz + (s8)*fi * sizeof(InMemFielderType));
    ang = atan2(dz, dx);
    if (g_Minigame._1D72 != 0 && idx != g_Minigame._1D6D) {
        a = fn_3_9FEA8(ang + lbl_3_rodata_3614);
        *ox = lbl_3_rodata_3618 * (f32)cos(a) + lbl_3_data_21A48[0];
        *oz = lbl_3_rodata_3618 * (f32)sin(a) + lbl_3_data_21A48[2];
    } else {
        a = fn_3_9FEA8(ang - lbl_3_rodata_3614);
        x1 = lbl_3_rodata_3618 * (f32)cos(a) + lbl_3_data_21A48[0];
        z1 = lbl_3_rodata_3618 * (f32)sin(a) + lbl_3_data_21A48[2];
        dx = x1 - g_Fielders[((s8)*fi)].pos.x;
        dz = z1 - *(f32*)(fz + (s8)*fi * sizeof(InMemFielderType));
        d1 = dx * dx + dz + dz;
        a += lbl_3_rodata_361C;
        a = fn_3_9FEA8(a);
        x2 = lbl_3_rodata_3618 * (f32)cos(a) + lbl_3_data_21A48[0];
        z2 = lbl_3_rodata_3618 * (f32)sin(a) + lbl_3_data_21A48[2];
        dx = x2 - g_Fielders[((s8)*fi)].pos.x;
        dz = z2 - *(f32*)(fz + (s8)*fi * sizeof(InMemFielderType));
        if (d1 < dx * dx + dz + dz) {
            *ox = x1;
            *oz = z1;
        } else {
            *ox = x2;
            *oz = z2;
        }
    }
    if (depth != 0) {
        if (fn_3_134D4C(lbl_3_data_21A48[0], lbl_3_data_21A48[2], lbl_3_rodata_3620,
                        g_Fielders[((s8)*fi)].pos.x, *(f32*)(fz + (s8)*fi * sizeof(InMemFielderType)), *ox, *oz)) {
            fn_3_13493C(idx, ox, oz, depth - 1);
        }
    }
    {
        f32 qx, qy;
        rot_i(&qx, &qy, *ox, *oz);
        return quad_i(qx, qy);
    }
}

// .text:0x00134C80 size:0xCC mapped:0x80773D14
int fn_3_134C80(u32 a, u32 b, u32 c, f32 x, f32 y) {
    if (g_Minigame._1D72 != 0 && a != g_Minigame._1D6D && (c == ((b + 1) & 3) || c == ((b + 2) & 3))) {
        return 1;
    }
    return !!fn_3_134D4C(lbl_3_data_21A48[0], lbl_3_data_21A48[2], lbl_3_rodata_3620,
                         g_Fielders[g_Minigame.minigameFielderIndex[a]].pos.x, g_Fielders[g_Minigame.minigameFielderIndex[a]].pos.z, x, y);
}

// .text:0x00134D4C size:0x370 mapped:0x80773DE0
u32 fn_3_134D4C(f32 ax, f32 az, f32 r, f32 bx, f32 bz, f32 x, f32 y) {
    f32 dist, len, dot, disc;
    dist = dolsqrtf2((ax - bx) * (ax - bx) + (az - bz) * (az - bz));
    len = dolsqrtf2((x - bx) * (x - bx) + (y - bz) * (y - bz));
    dot = (ax - bx) * ((x - bx) / len) + (az - bz) * ((y - bz) / len);
    if (dist < r) {
        return 1;
    }
    if (dist == r && dot > 0.0f) {
        return 2;
    }
    if (dot > 0.0f) {
        disc = dot * dot + (r * r - dist * dist);
        if (disc >= 0.0f) {
            if (dot - dolsqrtf2(disc) <= len) {
                return 3;
            }
        }
    }
    return 0;
}

// .text:0x001350BC size:0x400 mapped:0x80774150
extern const f32 lbl_3_rodata_3624;
extern f32 lbl_3_rodata_3628;
extern f32 lbl_3_rodata_362C;
extern f32 lbl_3_rodata_3630;
extern f32 lbl_3_rodata_3634;
extern f32 lbl_3_rodata_3638;
extern f32 lbl_3_data_21B38[];
extern f32 lbl_3_data_21B58[];
extern s16 lbl_3_data_21A88[];
extern f32 lbl_3_data_21A54[];
static inline int nearObstacle(Mg3520Obj* o, f32 x, f32 z) {
    int r = 0;
    f64 ax = fabs(o->pos.x - x);
    f64 az = fabs(o->pos.z - z);
    f32 fx = ax;
    f32 fz = az;
    if (fx <= lbl_3_rodata_35D8 && fz <= lbl_3_rodata_35DC) {
        r = 1;
    }
    return r;
}
// NONMATCHING 96.8%: saved-register numbering differs and the obstacle-loop base gets addi r0 + mr
// (docs/patterns/loops.md "global base u8* g = ((u8*)&g_Minigame)" open item)
#if NONMATCHING
CoinCand* fn_3_1350BC(u32 player, u32 quad, u32 n, CoinCand* cands) {
    s32 ai = g_Minigame.minigameControlStruct[0].aIStrength[player];
    CoinCand* c;
    u32 i;
    if (n != 0) {
    i = 0;
    c = cands;
    do {
        f32 cx, cz, dx, dz, r;
        InMemFielderType* f;
        u32 k;
        c->valid = 1;
        cz = MG3520->coinPos[c->coin].z;
        cx = MG3520->coinPos[c->coin].x;
        dx = cx - lbl_3_data_21A48[0];
        dz = cz - lbl_3_data_21A48[2];
        if (dx * dx + dz * dz < lbl_3_rodata_3624) {
            c->valid = 0;
        } else if (player != g_Minigame._1D6D) {
            if (g_Minigame._1D6D >= 0) {
                r = lbl_3_data_21B38[ai];
                f = &g_Fielders[g_Minigame.minigameFielderIndex[g_Minigame._1D6D]];
                dz = cz - f->pos.z;
                dx = cx - f->pos.x;
                if (dx * dx + dz * dz <= r * r) {
                    c->valid = 0;
                }
            }
            if (c->valid != 0) {
                Mg3520Obj* o;
                for (k = 0, o = MG3520->objs; ; ) {
                    u8 st = o->state;
                    if (st >= 1 && st <= 3) {
                        if (nearObstacle(o, cx, cz)) {
                            c->valid = 0;
                            break;
                        }
                    }
                    k++;
                    o++;
                    if (k >= lbl_3_data_21A88[g_Minigame.soloMinigameDifficulty]) {
                        break;
                    }
                }
            }
            if (c->valid != 0 && g_Minigame._CCE[0] == 2) {
                dz = cz - g_Minigame._CB8;
                r = lbl_3_data_21B58[ai];
                dx = cx - g_Minigame._CB0;
                if (dx * dx + dz * dz <= r * r) {
                    c->valid = 0;
                }
            }
        }
        dz = MG3520->coinPos[c->coin].z - g_Fielders[g_Minigame.minigameFielderIndex[player]].pos.z;
        dx = MG3520->coinPos[c->coin].x - g_Fielders[g_Minigame.minigameFielderIndex[player]].pos.x;
        c->score = dx * dx + dz * dz;
        for (k = 0; k < g_Minigame.miniGameNumberOfParticipants; k++) {
            if (k != player) {
                f32 d;
                dz = MG3520->coinPos[c->coin].z - g_Fielders[g_Minigame.minigameFielderIndex[k]].pos.z;
                dx = MG3520->coinPos[c->coin].x - g_Fielders[g_Minigame.minigameFielderIndex[k]].pos.x;
                d = dx * dx + dz * dz;
                if (d < lbl_3_rodata_3628 && d < c->score) {
                    c->score += lbl_3_rodata_362C;
                }
            }
        }
        if (g_Minigame._1D72 != 0 && player != g_Minigame._1D6D) {
            if (c->quad == ((quad + 1) & 3)) {
                c->score += lbl_3_rodata_3630;
            } else if (c->quad == ((quad + 2) & 3)) {
                c->score += lbl_3_rodata_3634;
            }
            if (fn_3_135520(c->x, c->z, lbl_3_rodata_3638 * lbl_3_data_21A54[2])) {
                c->valid = 0;
            }
        }
        i++;
        c++;
    } while (i < n);
    fn_800246D4(fn_3_135698, cands, cands, sizeof(CoinCand), n);
    return cands;
    }
    return NULL;
}
#endif

// .text:0x001354BC size:0x64 mapped:0x80774550
int fn_3_1354BC(int idx, f32 x, f32 y) {
    int r = 0;
    // MG3520->objs[idx].pos.x / .z; the byte-offset base keeps the original register use
    f64 ax = fabs(((f32*)(((u8*)&g_Minigame) + (s32)OFFSET_OF(Mg3520, objs[0].pos.x)))[idx * (s32)(sizeof(Mg3520Obj) / sizeof(f32))] - x);
    f64 ay = fabs(((f32*)(((u8*)&g_Minigame) + (s32)OFFSET_OF(Mg3520, objs[0].pos.z)))[idx * (s32)(sizeof(Mg3520Obj) / sizeof(f32))] - y);
    f32 fx = ax;
    f32 fy = ay;
    if (fx <= lbl_3_rodata_35D8 && fy <= lbl_3_rodata_35DC) {
        r = 1;
    }
    return r;
}

// .text:0x00135520 size:0xE0 mapped:0x807745B4
u32 fn_3_135520(f32 x, f32 y, f32 r) {
    if (x >= lbl_3_rodata_35D0) {
        if (y >= lbl_3_rodata_35D0) {
            if (y <= r) {
                return 1;
            }
            if (x <= r) {
                return 2;
            }
        } else {
            if (x <= r) {
                return 1;
            }
            if (y >= -r) {
                return 2;
            }
        }
    } else {
        if (y >= lbl_3_rodata_35D0) {
            if (x >= -r) {
                return 1;
            }
            if (y <= r) {
                return 2;
            }
        } else {
            if (y >= -r) {
                return 1;
            }
            if (x >= -r) {
                return 2;
            }
        }
    }
    return 0;
}

// .text:0x00135600 size:0x4C mapped:0x80774694
void fn_3_135600(f32* outX, f32* outY, f32 x, f32 y) {
    f32* d = lbl_3_data_21A48;
    Mg3520U* g = (Mg3520U*)&g_Minigame;
    f32 dy = y - d[2];
    f32 dx = x - d[0];
    *outX = dx * *(f32*)&g->mg._1DD3[29] - dy * *(f32*)&g->mg._1DD3[25];
    *outY = dx * *(f32*)&g->mg._1DD3[25] + dy * *(f32*)&g->mg._1DD3[29];
}

// .text:0x0013564C size:0x4C mapped:0x807746E0
int fn_3_13564C(f32 x, f32 y) {
    if (x >= lbl_3_rodata_35D0) {
        if (y >= lbl_3_rodata_35D0) {
            return 0;
        }
        return 3;
    }
    if (y >= lbl_3_rodata_35D0) {
        return 1;
    }
    return 2;
}

// .text:0x00135698 size:0x60 mapped:0x8077472C
int fn_3_135698(CoinCand* a, CoinCand* b) {
    u8 fa = a->valid;
    if (fa != 0 && b->valid == 0) {
        return -1;
    }
    if (fa == 0 && b->valid != 0) {
        return 1;
    }
    {
        if (a->score < b->score) {
            return -1;
        }
        return a->score > b->score;
    }
}

// NONMATCHING 99%: only g_Minigame base reg materialization (addi r0 + mr) differs; same as fn_3_13BB30
// .text:0x001356F8 size:0xAC mapped:0x8077478C
#if NONMATCHING
void fn_3_1356F8(void) {
    CpuSlot3520* q = MG3520->cpu.slot;
    f32 v;
    u8 st;
    u32 i;

    memset(g_Minigame._1D7C, 0, 0x78); // through the CPU state
    for (i = 0; i < 4; i++, q++) {
        st = g_Minigame.minigameControlStruct[0].aIStrength[i];
        q->lastStick = -1;
        if (RandomInt_Game(100) < (s8)lbl_3_data_21B88[st]) {
            v = lbl_3_rodata_35FC;
        } else {
            v = lbl_3_rodata_3600;
        }
        q->radius = v;
    }
}
#endif


// .text:0x001357A4 size:0x98 mapped:0x80774838
void fn_3_1357A4(f32* out, Vec* dir) {
    Vec base = *(Vec*)lbl_3_rodata_35C4;
    Vec v;
    if (out == NULL || dir == NULL) {
        return;
    }
    PSVECNormalize(dir, &v);
    PSVECScale(&v, lbl_3_rodata_363C, &v);
    out[0] = base.x + v.x;
    out[2] = base.z + v.z;
}

// .text:0x0013583C size:0xE8 mapped:0x807748D0
void fn_3_13583C(f32* out) {
    Vec c = *(Vec*)lbl_3_rodata_35B8;
    Vec d;
    if (out != NULL) {
        PSVECSubtract((Vec*)out, &c, &d);
        d.y = lbl_3_rodata_35D0;
        if (PSVECMag(&d) <= lbl_3_rodata_363C) {
            Vec v;
            Vec base = *(Vec*)lbl_3_rodata_35C4;
            if (out != NULL) {
                PSVECNormalize(&d, &v);
                PSVECScale(&v, lbl_3_rodata_363C, &v);
                out[0] = base.x + v.x;
                out[2] = base.z + v.z;
            }
        }
    }
}

// .text:0x00135924 size:0x140 mapped:0x807749B8
void fn_3_135924(void) {
    u32 i;
    for (i = 0; i < 100; i++) {
        if (g_Minigame.wallBall_coinsVisibleInd[i] == 1) {
            if (MG3520->coinPos[i].y < lbl_3_rodata_35FC) {
                Vec d;
                Vec c = *(Vec*)lbl_3_rodata_35B8;
                if (&MG3520->coinPos[i].x != NULL) {
                    PSVECSubtract(&MG3520->coinPos[i], &c, &d);
                    d.y = lbl_3_rodata_35D0;
                    if (PSVECMag(&d) <= lbl_3_rodata_363C) {
                        Vec v;
                        Vec base = *(Vec*)lbl_3_rodata_35C4;
                        if (&MG3520->coinPos[i].x != NULL) {
                            PSVECNormalize(&d, &v);
                            PSVECScale(&v, lbl_3_rodata_363C, &v);
                            MG3520->coinPos[i].x = base.x + v.x;
                            MG3520->coinPos[i].z = base.z + v.z;
                        }
                    }
                }
            }
        }
    }
}

// .text:0x00135A64 size:0x1B4 mapped:0x80774AF8
extern f32 lbl_3_rodata_3640;
extern f32 lbl_3_data_219AC[];
extern f32 lbl_3_data_21A54[];
extern f32 lbl_3_data_47BC[];
// NONMATCHING 98%: g_Minigame base lands in r5 then mr r27 (orig addi r27 directly); a/b loop incr order differs
#if NONMATCHING
void fn_3_135A64(void) {
    s32 t;
    s32 j;
    f32 d;
    s16 ang;
    InMemFielderType* f;
    s32 i;
    if (g_Minigame.turnOverStatus == 0 && !(g_Minigame._1D48 < lbl_3_rodata_3640)) {
        for (i = 0; i < 4; i++) {
            t = g_Minigame.minigameFielderIndex[i];
            if ((s8)t < 0 || i == g_Minigame._1D6D || g_Minigame.starDashStunType[i] != 0) {
                continue;
            }
            f = &g_Fielders[(s8)t];
            if (f->_203 != 0 && f->_204 > 3) {
                continue;
            }
#ifdef TARGET_PC // wasm traps on a call through a mismatched prototype
            ang = fn_3_9FB8C(f->pos.x - lbl_3_data_219AC[0], f->pos.z - lbl_3_data_219AC[2]);
#else
            ang = ((int (*)(f32, f32))fn_3_9FB8C)(f->pos.x - lbl_3_data_219AC[0], f->pos.z - lbl_3_data_219AC[2]);
#endif
            for (j = 0; j < 4; j++) {
                if (fn_3_9FCF8(ang, MG3520->spokeAng[j]) > 0x200) {
                    continue;
                }
                d = fn_3_9EFD0(&MG3520->spokes[j].a, &MG3520->spokes[j].b, &f->pos, 0);
                if (d < lbl_3_data_21A54[2] + lbl_3_data_47BC[f->weight] && d >= lbl_3_rodata_35D0) {
                    fn_3_1360BC(i);
                    g_Minigame.starDashStunType[i] = 3;
                    MG3520->stunTimer[i] = 0;
                    fn_3_25844(g_Minigame.minigameFielderIndex[i], 2);
                    fn_3_6C854(g_Minigame.minigameControlStruct[0].characterIndex[i], 2);
                    break;
                }
            }
        }
    }
}
#endif


// .text:0x00135C18 size:0x220 mapped:0x80774CAC
extern void fn_3_156548(u32, f32, f32, f32);
extern void fn_3_15730C(u32, f32, f32, f32);
// NONMATCHING 97%: structure and float regs match; int saved regs (gp/ge/ep/i/k/n) and prologue lis order differ
#if NONMATCHING
void fn_3_135C18(void) {
    Mg3520Ent* e;
    f32 spC;
    s32 i = 0;
    f32 lo;
    s32 k;
    f32 mid;
    f32 step;
    f32 v;
    f32 sp8;
    s32 n;
    f32 zero = lbl_3_rodata_35D0;
    n = 0;
    lo = g_Minigame._1D48 * lbl_3_data_21A54[1] - lbl_3_data_21A54[0];
    step = (lbl_3_data_21A54[1] - lbl_3_data_21A54[0]) / (f32)(&lbl_3_data_21A60)[1];
    mid = lo + lbl_3_data_21A54[0];
    e = MG3520->ents;
    do {
        Vec* a = &MG3520->spokes[i].a;
        Vec* b = &MG3520->spokes[i].b;
        getComponentsFromSAng(MG3520->spokeAng[i], &spC, &sp8);
        v = lo;
        k = 0;
        a->x = spC * lbl_3_data_21A54[0] + lbl_3_data_21A48[0];
        a->z = sp8 * lbl_3_data_21A54[0] + lbl_3_data_21A48[2];
        b->x = spC * mid + lbl_3_data_21A48[0];
        b->z = sp8 * mid + lbl_3_data_21A48[2];
        spC = (b->x - a->x) / lo;
        sp8 = (b->z - a->z) / lo;
        for (; k < (&lbl_3_data_21A60)[1]; k++, e++, n++) {
            e->pos.x = spC * v + a->x;
            e->pos.z = sp8 * v + a->z;
            if (v < zero) {
                e->_26 = 0;
            } else {
                v -= step;
                if (e->_26 != 0) {
                    fn_3_156548(n, e->pos.x, -e->pos.y, e->pos.z);
                } else {
                    fn_3_15730C(n, e->pos.x, -e->pos.y, e->pos.z);
                    e->_26 = 1;
                }
            }
        }
        i++;
    } while (i < 4);
}
#endif


// .text:0x00135E38 size:0x60 mapped:0x80774ECC
void fn_3_135E38(void) {
    s32 t;
    fn_3_135C18();
    t = lbl_3_data_21A3C[g_Minigame._1D73 * 2 - 1] * 0x3C;
    if (t == MG3520->timer) {
        g_Minigame._1D72 = 3;
        g_Minigame._1D62 = 0;
    }
}

// .text:0x00135E98 size:0xB4 mapped:0x80774F2C
void fn_3_135E98(void) {
    s16 t = g_Minigame._1D62 + 1;
    g_Minigame._1D62 = t;
    g_Minigame._1D48 = lbl_3_rodata_3644 - (f32)t / (f32)lbl_3_data_21A60;
    fn_3_135C18();
    if (g_Minigame._1D62 >= lbl_3_data_21A60) {
        g_Minigame._1D72 = 0;
    }
}

// .text:0x00135F4C size:0xA8 mapped:0x80774FE0
void fn_3_135F4C(void) {
    s16 t = g_Minigame._1D62 + 1;
    g_Minigame._1D62 = t;
    g_Minigame._1D48 = (f32)t / (f32)lbl_3_data_21A60;
    fn_3_135C18();
    if (g_Minigame._1D62 >= lbl_3_data_21A60) {
        g_Minigame._1D72 = 2;
    }
}

// .text:0x00135FF4 size:0x54 mapped:0x80775088
void fn_3_135FF4(void) {
    u8 i = g_Minigame._1D73;
    u32 t = lbl_3_data_21A3C[i * 2] * 0x3C;
    if (t == MG3520->timer) {
        g_Minigame._1D72 = 1;
        g_Minigame._1D62 = 0;
        g_Minigame._1D48 = lbl_3_rodata_35D0;
        g_Minigame._1D73 = g_Minigame._1D73 + 1;
    }
}

// .text:0x00136048 size:0x74 mapped:0x807750DC
void fn_3_136048(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        MG3520->spokeAng[i] += lbl_3_data_21A44;
        MG3520->spokeAng[i] = fn_3_9FE6C_normalizeAngle(MG3520->spokeAng[i]);
    }
}

// .text:0x001360BC size:0x164 mapped:0x80775150
void fn_3_1360BC(int p) {
    s16* pts;
    int n;
    InMemFielderType* f;
    int i;
    int k;
    f = &g_Fielders[g_Minigame.minigameFielderIndex[p]];
    MG3520->_1DF4[p] = 1;
    pts = (s16*)(((u8*)&g_Minigame) + (s32)OFFSET_OF(MiniGameStruct, miniGameCurrentPoints[0])) + p; // byte form keeps the original lhau
    n = lbl_3_data_21B20[3];
    if (*pts < n) {
        n = *pts;
    }
    if (n != 0) {
        for (i = 0, k = 0; i < 0x32; i++) {
            if (MG3520->coinState[i] == 0) {
                MG3520->coinPos[i].x = f->pos.x;
                MG3520->coinPos[i].y = f->pos.y;
                MG3520->coinPos[i].z = f->pos.z;
                MG3520->coinPos[i].y = f->_16C;
                MG3520->coinVel[i].y = lbl_3_data_219B8[18];
                getComponentsFromSAng(random_fn_3_9EE24(0x1000), &MG3520->coinVel[i].x, &MG3520->coinVel[i].z);
                {
                    f32 r = RandomF32_Game_Range(lbl_3_data_219B8[16], lbl_3_data_219B8[17]);
                    k++;
                    MG3520->coinVel[i].x *= r;
                    MG3520->coinVel[i].z *= r;
                }
                MG3520->coinState[i] = 1;
                MG3520->coinTimer[i] = 0;
                g_Minigame._1D6C++;
                if (k >= n) {
                    break;
                }
            }
        }
        fn_3_90064(0x2E8);
        *pts -= n;
    }
}

// .text:0x00136220 size:0x66C mapped:0x807752B4
extern f32 lbl_3_data_21B18[];
extern f32 lbl_3_data_2198C[];
extern f32 lbl_3_data_4444[];
extern f32 lbl_3_rodata_3650;
extern f32 lbl_3_rodata_3644;
extern u32 fn_3_90220(s32 idx, s32 off);
#define KNOCK_VX(i) (MG3520->knockVel[i].x)
#define KNOCK_VY(i) (MG3520->knockVel[i].y)
#define KNOCK_VZ(i) (MG3520->knockVel[i].z)
#define STUN_TIMER(i) (MG3520->stunTimer[i])
// Per-fielder stun state machine (1: hit, 2: knocked back, 3: recovering) and
// push-out from walls.
void fn_3_136220(void) {
    VecSrcDst seg;
    CollisionStruct col;
    InMemFielderType* f;
    u32 t;
    s32 i;
    for (i = 0; i < 4; i++) {
        s32 fi = (u8)g_Minigame.minigameFielderIndex[i];
        if ((s8)fi < 0) {
            continue;
        }
        f = &g_Fielders[(s8)fi];
        if (f->_20F == 0) {
            u8 st = g_Minigame.starDashStunType[i];
            if (st == 1) {
                f32 len = dolsqrtf2(KNOCK_VX(i) * KNOCK_VX(i) + KNOCK_VZ(i) * KNOCK_VZ(i));
                KNOCK_VX(i) *= lbl_3_data_21B18[0] / len;
                KNOCK_VZ(i) *= lbl_3_data_21B18[0] / len;
                KNOCK_VY(i) = lbl_3_rodata_35D0;
                STUN_TIMER(i) = 0;
                g_Minigame.starDashStunType[i] = 2;
                if ((s8)g_Minigame.playerIDWithPowerup[0] == i) {
                    fn_800115C8(g_Minigame.playerIDWithPowerup[0]);
                    ((s8*)g_Minigame.playerIDWithPowerup)[0] = -1;
                }
                fn_3_1360BC(i);
                fn_3_90064(0x2E7);
                fn_3_90220(f->charID, 10);
                fn_3_6C854(g_Minigame.minigameControlStruct[0].characterIndex[i], 2);
            } else if (st == 2) {
                f32 len;
                STUN_TIMER(i)++;
                len = dolsqrtf2(KNOCK_VX(i) * KNOCK_VX(i) + KNOCK_VZ(i) * KNOCK_VZ(i));
                if (len > lbl_3_rodata_35D0) {
                    seg.src.x = f->pos.x;
                    seg.src.y = lbl_3_rodata_3648;
                    seg.src.z = f->pos.z;
                    seg.dst.x = lbl_3_rodata_3638 * KNOCK_VX(i) + f->pos.x;
                    seg.dst.y = lbl_3_rodata_3648;
                    seg.dst.z = lbl_3_rodata_3638 * KNOCK_VZ(i) + f->pos.z;
                    if ((u32)checkCollision(&seg, &col, 0, 0) != 0) {
                        KNOCK_VX(i) = lbl_3_rodata_35D0;
                        KNOCK_VZ(i) = lbl_3_rodata_35D0;
                    }
                    f->pos.x = f->pos.x + KNOCK_VX(i);
                    f->pos.y = f->pos.y + KNOCK_VY(i);
                    f->pos.z = f->pos.z + KNOCK_VZ(i);
                    KNOCK_VX(i) *= lbl_3_data_21B18[1];
                    KNOCK_VZ(i) *= lbl_3_data_21B18[1];
                }
                if (STUN_TIMER(i) > lbl_3_data_21B20[1]) {
                    g_Minigame.starDashStunType[i] = 3;
                    f->velX = lbl_3_rodata_35D0;
                    f->velZ = lbl_3_rodata_35D0;
                    STUN_TIMER(i) = 0;
                    f->speed = lbl_3_rodata_35D0;
                }
            } else if (st == 3) {
                STUN_TIMER(i)++;
                if (STUN_TIMER(i) > lbl_3_data_21B20[2]) {
                    g_Minigame.starDashStunType[i] = 0;
                }
            }
        }
        seg.src.x = f->pos.x;
        seg.src.y = lbl_3_rodata_3648;
        seg.src.z = f->pos.z;
        seg.dst.x = f->pos.x;
        seg.dst.y = lbl_3_rodata_3644;
        seg.dst.z = f->pos.z;
        t = checkCollision(&seg, &col, 0, 0);
        t &= 0x7F;
        if (t == 2 || t == 3 || t == 7 || t == 8 || t == 5) {
            // inside a wall: push toward (or away from) the field center
            f32 dz = lbl_3_data_4444[8] - f->pos.z;
            f32 dx = lbl_3_data_4444[8] - f->pos.x;
            f32 d = dolsqrtf2(dx * dx + dz * dz);
            if (lbl_3_rodata_35D0 == d) {
                f->pos.x = lbl_3_data_2198C[i * 2 + 0];
                f->pos.z = lbl_3_data_2198C[i * 2 + 1];
            } else {
                dx /= d;
                dz /= d;
                if (d < lbl_3_rodata_364C) {
                    f->pos.x = f->pos.x - lbl_3_rodata_3650 * dx;
                    f->pos.z = f->pos.z - lbl_3_rodata_3650 * dz;
                } else {
                    f->pos.x = lbl_3_rodata_3650 * dx + f->pos.x;
                    f->pos.z = lbl_3_rodata_3650 * dz + f->pos.z;
                }
            }
        }
    }
}

// .text:0x0013688C size:0x468 mapped:0x80775920
extern f32 lbl_3_data_21AF8[];
extern s16 lbl_3_data_21B10[];
extern f32 lbl_3_data_47BC[];
extern void fn_3_1695A4(s32 a, u8 flag);
extern void fn_3_16C394(s8 a);
static inline void refl_w(f32* a, f32* b) {
    f32 d;
    d = (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
    d *= 2.0f;
    a[0] = a[0] - d * b[0];
    a[1] = a[1] - d * b[1];
    a[2] = a[2] - d * b[2];
}
void fn_3_13688C(Obj136* o) {
    VecSrcDst seg;
    CollisionStruct col;
    f32 best, r, d, rr, dx, dz;
    s32 sel, i;
    InMemFielderType* f;
    seg.src.x = o->pos.x;
    seg.src.y = -o->pos.y;
    seg.src.z = o->pos.z;
    o->vel.y = o->vel.y + lbl_3_data_21AF8[2];
    o->pos.x = o->vel.x + o->pos.x;
    o->pos.y = o->vel.y + o->pos.y;
    o->pos.z = o->vel.z + o->pos.z;
    if (o->pos.y < 0.0f) {
        o->pos.y = 0.0f;
        o->vel.y = 0.0f;
    }
    seg.dst.x = o->pos.x;
    seg.dst.y = -o->pos.y;
    seg.dst.z = o->pos.z;
    if ((u32)checkCollision(&seg, &col, 0, 0) == 5) {
        col.normal.y *= -1.0f;
        refl_w(&o->vel.x, &col.normal.x);
        o->pos.x = col.position.x;
        o->pos.y = -col.position.y;
        o->pos.z = col.position.z;
    }
    seg.dst.x = o->pos.x;
    seg.dst.y = -o->pos.y;
    seg.dst.z = o->pos.z;
    if (fn_3_1373E0(&seg, &o->vel, &col, lbl_3_data_21AF8[3])) {
        o->pos.x = col.position.x;
        o->pos.y = col.position.y;
        o->pos.z = col.position.z;
        memcpy(&o->vel, &col.normal, sizeof(Vec));
        seg.dst.x = o->pos.x;
        seg.dst.y = -o->pos.y;
        seg.dst.z = o->pos.z;
        if ((u32)checkCollision(&seg, &col, 0, 0) == 5) {
            col.normal.y *= -1.0f;
            refl_w(&o->vel.x, &col.normal.x);
            o->pos.x = col.position.x;
            o->pos.y = -col.position.y;
            o->pos.z = col.position.z;
        }
    }
    best = 99999.9f;
    i = 0;
    sel = -1;
    for (; i < 4; i++) {
        s32 fi = (u8)g_Minigame.minigameFielderIndex[i];
        if ((s8)fi < 0) {
            continue;
        }
        if (g_Minigame.starDashStunType[i] != 0 && g_Minigame.starDashStunType[i] != 3) {
            continue;
        }
        f = &g_Fielders[(s8)fi];
        if (f->_203 != 0 && f->_204 > 3) {
            continue;
        }
        if (f->_16C + f->height < o->pos.y) {
            continue;
        }
        dz = f->pos.z - o->pos.z;
        rr = lbl_3_data_21AF8[3] + lbl_3_data_47BC[f->weight];
        dx = f->pos.x - o->pos.x;
        d = dx * dx + dz * dz;
        rr = rr * rr;
        if (d < rr && d < best) {
            best = d;
            sel = i;
        }
    }
    if (sel >= 0) {
        g_Minigame.playerIDWithPowerup[0] = sel;
        g_Minigame._1D58 = lbl_3_data_21B10[2];
        if (MG3520->item.state == 2) {
            u8 t = *(u8*)&g_Minigame._1D6D; // read unsigned, compared signed
            if ((s8)t == sel) {
                fn_3_14E988(t);
                fn_800115C8((s8)sel);
                g_Minigame._1D6D = -1;
            }
#ifdef TARGET_PC
            PTR32_SET(g_Minigame.starDashRelated_0_5Or1_5, &lbl_3_data_21AF8[5]);
#else
            g_Minigame.starDashRelated_0_5Or1_5 = &lbl_3_data_21AF8[5];
#endif
            fn_3_90064(0x2F5);
            fn_3_1695A4((s8)sel, 0);
        } else {
#ifdef TARGET_PC
            PTR32_SET(g_Minigame.starDashRelated_0_5Or1_5, &lbl_3_data_21AF8[4]);
#else
            g_Minigame.starDashRelated_0_5Or1_5 = &lbl_3_data_21AF8[4];
#endif
            fn_3_90064(0x2F6);
            fn_3_16C394(sel);
        }
        o->state = 0;
        o->timer = lbl_3_data_21B10[0];
    } else {
        o->timer -= 1;
        if (o->timer <= 0) {
            o->state = 0;
            o->timer = lbl_3_data_21B10[0];
        }
    }
}

// .text:0x00136CF4 size:0x1B0 mapped:0x80775D88
extern u8 lbl_3_data_21B16;
extern f32 lbl_3_rodata_3658;
extern f32 lbl_3_rodata_3660;
// 99.5%: only the first block differs (pu extsb lands in r4, orig lbz r3 / extsb r5 / lha r4); rest matches
void fn_3_136CF4(Obj136* o) {
    Mg3520U* g = (Mg3520U*)&g_Minigame;
    s32 pu;
    u8 raw;
    f32 ang;
    raw = g->mg.playerIDWithPowerup[0];
    pu = (s8)raw;
    if (pu != -1) {
        if (--g->mg._1D58 <= 0) {
            if (g->mg._1D6D != pu) {
                fn_800115C8(raw);
            }
            ((s8*)g->mg.playerIDWithPowerup)[0] = -1;
        }
    } else {
        o->timer -= 1;
        if (o->timer <= 0) {
            if ((s8)(rand() % 100 - lbl_3_data_21B16) < 0) {
                o->state = 1;
            } else {
                o->state = 2;
            }
            o->pos.x = lbl_3_data_219AC[0];
            o->pos.y = lbl_3_data_219AC[1];
            o->pos.z = lbl_3_data_219AC[2];
            o->vel.y = lbl_3_data_21AF8[0];
            ang = lbl_3_rodata_3660 * (lbl_3_rodata_3658 * ((f32)rand() / lbl_3_rodata_365C));
            o->vel.x = lbl_3_data_21AF8[1] * (f32)cos(ang);
            o->vel.z = lbl_3_data_21AF8[1] * (f32)sin(ang);
            o->timer = lbl_3_data_21B10[1];
        }
    }
}

// .text:0x00136EA4 size:0x1FC mapped:0x80775F38
// 99%: same pu/extsb register block as fn_3_136CF4 differs (r4/r5 vs orig r5/r3)
void fn_3_136EA4(void) {
    Mg3520U* g = (Mg3520U*)&g_Minigame;
    s32 pu;
    u8 raw;
    f32 ang;
    if (g->mg.turnOverStatus != 0) {
        ((s8*)g->mg.playerIDWithPowerup)[0] = -1;
        g->x.item.state = 0;
    } else if (g->x.item.state != 0) {
        fn_3_13688C(&g->x.item);
    } else {
        raw = g->mg.playerIDWithPowerup[0];
        pu = (s8)raw;
        if (pu != -1) {
            if (--g->mg._1D58 <= 0) {
                if (g->mg._1D6D != pu) {
                    fn_800115C8(raw);
                }
                ((s8*)g->mg.playerIDWithPowerup)[0] = -1;
            }
        } else {
            g->mg._CCC -= 1;
            if (g->mg._CCC <= 0) {
                if ((s8)(rand() % 100 - lbl_3_data_21B16) < 0) {
                    g->x.item.state = 1;
                } else {
                    g->x.item.state = 2;
                }
                g_Minigame._CB0 = lbl_3_data_219AC[0];
                g_Minigame._CB4 = lbl_3_data_219AC[1];
                g_Minigame._CB8 = lbl_3_data_219AC[2];
                g_Minigame._CC0 = lbl_3_data_21AF8[0];
                ang = lbl_3_rodata_3660 * (lbl_3_rodata_3658 * ((f32)rand() / lbl_3_rodata_365C));
                g_Minigame._CBC = lbl_3_data_21AF8[1] * (f32)cos(ang);
                g_Minigame._CC4 = lbl_3_data_21AF8[1] * (f32)sin(ang);
                g->mg._CCC = lbl_3_data_21B10[1];
            }
        }
    }
}

// .text:0x001370A0 size:0x148 mapped:0x80776134
void fn_3_1370A0(camera_803c639c_s* o) {
    Vec sp8;
    Mtx m;
    memset(&sp8, 0, sizeof(Vec));
    sp8.y = lbl_3_data_21AF4 * (lbl_3_rodata_3668 * ((f64)((f32)rand() / lbl_3_rodata_365C) - lbl_3_rodata_35E0));
    PSMTXInverse((f32(*)[4])(&o->view[0][0]), m);
    PSMTXMultVecSR(m, &sp8, &sp8);
    o->eye.x += sp8.x;
    o->eye.y += sp8.y;
    o->eye.z += sp8.z;
    o->target.x += sp8.x;
    o->target.y += sp8.y;
    o->target.z += sp8.z;
    lbl_3_bss_B702--;
    if (lbl_3_bss_B702 <= 0) {
        lbl_3_bss_B702 = 0;
        fn_800528B4();
    }
}

#pragma dont_inline off
// .text:0x001371E8 size:0x3C mapped:0x8077627C
void fn_3_1371E8(void) {
    lbl_3_bss_B702 = lbl_3_data_21AF0[0];
    fn_800528AC((fn_800528AC_parameter)fn_3_1370A0);
}

// .text:0x00137224 size:0x1BC mapped:0x807762B8
void fn_3_137224(Mg3520Obj* o) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    f32 d;
    u32 i;
    for (i = 0; i < 100; i++) {
        if (COIN_STATE(i) == 1) {
            f32 y = COIN_POS(i).y;
            if (!(y > lbl_3_data_219B8[14]) && !(COIN_VEL(i).y > lbl_3_rodata_3670)) {
                sp20.x = COIN_POS(i).x;
                sp20.y = y;
                sp20.z = COIN_POS(i).z;
                PSVECSubtract(&sp20, &o->pos, &sp14);
                d = PSVECMag(&sp14);
                d = (lbl_3_rodata_3628 - d) / lbl_3_rodata_3628;
                sp14.y = lbl_3_rodata_35D0;
                if (!PSVECMag(&sp14)) {
                    sp14.z = lbl_3_rodata_3648;
                }
                PSVECNormalize(&sp14, &sp14);
                sp8.x = lbl_3_rodata_35D0;
                sp8.z = lbl_3_rodata_35D0;
                sp8.y = lbl_3_rodata_3680 * (lbl_3_rodata_3668 * ((f64)((f32)rand() / lbl_3_rodata_365C) - lbl_3_rodata_35E0)) + lbl_3_rodata_3678;
                PSVECScale(&sp8, d, &sp8);
                PSVECAdd(&sp8, &COIN_VEL(i), &COIN_VEL(i));
            }
        }
    }
}

#pragma dont_inline on

// .text:0x001373E0 size:0x5C0 mapped:0x80776474
// NONMATCHING 91%: prologue constant loads get addi+lfs 0(rX), push-out sign branch laid out differently, regalloc
#if NONMATCHING
// Clip a sphere (radius r) moving along seg against the box obstacles (0x40-byte
// records at g_Minigame+0xBB0, state at +0x3D). On a hit, fills col (contact
// position and the reflected velocity) and returns 1.
u8 fn_3_1373E0(VecSrcDst* seg, Vec* vel, CollisionStruct* col, f32 r) {
    Vec d1;
    Vec d2;
    Vec n1;
    Vec hit;
    Vec dir;
    f32 r2;
    f32 hw;
    f32 hd;
    u32 i;
    // side planes (nx, nz, d): -x, +x, +z, -z
    f32 planes[4][3] = { { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f } };
    r2 = lbl_3_rodata_3638 * r;
    hw = lbl_3_rodata_363C + r;
    hd = lbl_3_rodata_3688 + r;
    for (i = 0; i < lbl_3_bss_B780; i++) {
        Vec* op;
        u8 inside;
        u8 st;
        f32 th, t;
        f32* p;
        op = &MG3520->objs[i].pos;
        inside = 1;
        st = MG3520->objs[i].state;
        if (!(st > 1 || st == 4)) {
            continue;
        }
        if (op->y > -seg->dst.y) {
            th = r2;
        } else {
            th = lbl_3_rodata_368C;
        }
        if (th < fabs(op->y + seg->dst.y)) {
            continue;
        }
        PSVECSubtract(&seg->dst, op, &d1);
        if (fabs(d1.x) > hw || fabs(d1.z) > hd) {
            continue;
        }
        if (PSVECMag(&d1) != 0.0f) {
            PSVECNormalize(&d1, &n1);
        } else {
            memset(&n1, 0, sizeof(Vec));
        }
        PSVECSubtract(&seg->dst, &seg->src, &dir);
        if (PSVECMag(&dir) != 0.0f) {
            PSVECNormalize(&dir, &dir);
        } else {
            memset(&dir, 0, sizeof(Vec));
        }
        dir.y = lbl_3_rodata_35D0;
        n1.y = lbl_3_rodata_35D0;
        if (PSVECDotProduct(&n1, &dir) > lbl_3_rodata_35D0) {
            continue;
        }
        PSVECSubtract(&seg->src, op, &d2);
        if (fabs(d2.x) <= hw && fabs(d2.z) <= hd) {
            // started inside the box
            PSVECSubtract(&seg->src, &seg->dst, &dir);
            dir.y = lbl_3_rodata_35D0;
            if (PSVECMag(&dir) != 0.0f) {
                PSVECNormalize(&dir, &dir);
                inside = 0;
                seg->dst.x = seg->src.x;
                seg->dst.z = seg->src.z;
                seg->src.x = lbl_3_rodata_364C * dir.x + seg->src.x;
                seg->src.z = lbl_3_rodata_3690 * dir.z + seg->src.z;
            } else {
                // not moving: push out to the nearest face
                f32 nz = n1.z;
                f32 nx = n1.x;
                f64 ratio = fabs(nz / nx);
                if (lbl_3_rodata_3698 < ratio) {
                    nz = fabs(nz) / nz;
                } else if (lbl_3_rodata_3698 > ratio) {
                    nx = fabs(nx) / nx;
                } else {
                    nz = fabs(nz) / nz;
                    nx = fabs(nx) / nx;
                }
                col->position.x = nx * hw + op->x;
                col->position.y = -seg->src.y;
                col->position.z = nz * hd + op->z;
                col->normal.x = lbl_3_rodata_3648 * vel->x;
                col->normal.y = vel->y;
                col->normal.z = lbl_3_rodata_3648 * vel->z;
                return 1;
            }
        }
        // intersect with the x face the segment is heading into
        PSVECSubtract(&seg->dst, &seg->src, &dir);
        if (dir.x > lbl_3_rodata_35D0) {
            p = planes[0];
        } else {
            p = planes[1];
        }
        p[2] = p[0] * (hw * (fabs(p[0]) / p[0]) + op->x);
        t = -((seg->src.x * p[0] + seg->src.z * p[1]) - p[2]) / (dir.x * p[0] + dir.z * p[1]);
        hit.x = dir.x * t + seg->src.x;
        hit.z = dir.z * t + seg->src.z;
        hit.y = -seg->src.y;
        if (fabs(hit.z - op->z) <= hd && t >= lbl_3_rodata_35D0) {
            memcpy(&col->normal, vel, sizeof(Vec));
            col->normal.x *= lbl_3_rodata_3648;
        } else {
            // otherwise the z face
            if (dir.z > lbl_3_rodata_35D0) {
                p = planes[3];
            } else {
                p = planes[2];
            }
            p[2] = p[1] * (op->z + (hd * fabs(p[1])) / p[1]);
            t = -((seg->src.x * p[0] + seg->src.z * p[1]) - p[2]) / (dir.x * p[0] + dir.z * p[1]);
            hit.x = dir.x * t + seg->src.x;
            hit.z = dir.z * t + seg->src.z;
            hit.y = -seg->src.y;
            memcpy(&col->normal, vel, sizeof(Vec));
            col->normal.z *= lbl_3_rodata_3648;
        }
        if (inside) {
            memcpy(col, &hit, sizeof(Vec));
        } else {
            seg->dst.y *= lbl_3_rodata_3648;
            memcpy(col, &seg->dst, sizeof(Vec));
        }
        return 1;
    }
    return 0;
}
#endif

// .text:0x001379A0 size:0x170 mapped:0x80776A34
// NONMATCHING 96%: only the first (unrolled) fielder-index loop differs: orig keeps g_Minigame in r7 plus a separate induction ptr in r4
#if NONMATCHING
u8 fn_3_1379A0(s32 idx) {
    InMemFielderType* f = &g_Fielders[idx];
    Mg3520Obj* o = MG3520->objs;
    u32 k;
    u32 n;
    for (k = 0; k < 4; k++) {
        if ((s8)g_Minigame.minigameFielderIndex[k] == idx) {
            break;
        }
    }
    if (k == (u32)(s8)g_Minigame._1D6D) {
        return 0;
    }
    for (n = 0; n < lbl_3_bss_B780; n++, o++) {
        u8 st = o->state;
        if (st == 3 || st == 5) {
            f32 fy = f->_15C + (f->height + f->pos.y);
            f32 py = o->pos.y;
            f32 th;
            f32 dx, dz;
            f64 ta, tb;
            if (fy < py) {
                th = f->_16C;
            } else {
                th = lbl_3_rodata_368C;
            }
            if (!(th < fabs(fy - py))) {
                f32 ex = f->pos.x + f->velX;
                f32 ez = f->pos.z + f->velZ;
                ta = fabs(o->pos.x - ex);
                tb = fabs(o->pos.z - ez);
                dx = ta;
                dz = tb;
                if (dx < lbl_3_rodata_363C) {
                  if (dz < lbl_3_rodata_3688) {
                    return 1;
                  }
                }
            }
        }
    }
    return 0;
}
#endif


// .text:0x00137B10 size:0x1E8 mapped:0x80776BA4
// NONMATCHING 98%: only the Vec v x/y/z load registers and store order differ (orig f1=x,f0=0.0,f2=z)
#if NONMATCHING
u8 fn_3_137B10(Mg3520Obj* o) {
    s32 i;
    u8 ret;
    f32* d = &lbl_3_data_21A64;
    ret = 0;
    i = 0;
    for (; i < 4; i++) {
        s32 fr = g_Minigame.minigameFielderIndex[i];
        u8 st;
        InMemFielderType* f;
        f32 fy, py, th;
        f32 dx, dz;
        f64 ta, tb;
        if ((s8)fr < 0) {
            continue;
        }
        st = g_Minigame.starDashStunType[i];
        if (st != 0 && st != 3) {
            continue;
        }
        if (o->state != 2 && i != g_Minigame._1D6D) {
            continue;
        }
        f = &g_Fielders[(s8)fr];
        py = o->pos.y;
        fy = f->_15C + (f->height + f->pos.y);
        if (fy < py) {
            th = f->_16C;
        } else {
            th = lbl_3_rodata_368C;
        }
        if (th < fabs(fy - py)) {
            continue;
        }
        ta = fabs(o->pos.x - f->pos.x);
        tb = fabs(o->pos.z - f->pos.z);
        dx = ta;
        dz = tb;
        if (dx <= lbl_3_rodata_363C && dz <= lbl_3_rodata_3688) {
            if (i == g_Minigame._1D6D) {
                if (ret == 0) {
                    Vec v;
                    v.y = lbl_3_rodata_35D0;
                    v.x = f->_038;
                    v.z = f->_03C;
                    ret = 1;
                    PSVECScale(&v, d[2], &v);
                    v.y = d[3];
                    memcpy(&o->_0C, &v, 12);
                    o->_24.x = d[4];
                    o->_3A = 0;
                    o->state = 4;
                }
            } else {
                g_Minigame.starDashStunType[i] = 1;
                MG3520->knockVel[i].x = f->pos.x - o->pos.x;
                MG3520->knockVel[i].z = f->pos.z - o->pos.z;
                o->_3E = 1;
                o->_3F = 0;
            }
        }
    }
    return ret;
}
#endif


// .text:0x00137CF8 size:0xEC mapped:0x80776D8C
static inline void h137CF8(Mg3520Obj* o) {
    u32 t;
    s16* row;
    int lo;
    PSVECAdd(&o->pos, &o->_0C, &o->pos);
    if (fn_3_137B10(o) == 0 && o->pos.y >= lbl_3_data_21A64) {
        t = MG3520->timer / 60 / 20;
        if (t > 3) {
            t = 3;
        }
        o->state = 0;
        o->_3A = 0;
        row = lbl_3_data_21A90 + g_Minigame.soloMinigameDifficulty * 8;
        lo = row[t * 2];
        t = random_fn_3_9EE24((row[t * 2 + 1] - lo) * 60);
        o->_38 = t + lo * 60;
    }
}
void fn_3_137CF8(Mg3520Obj* o) {
    h137CF8(o);
}

// .text:0x00137DE4 size:0x130 mapped:0x80776E78
static inline void h137DE4(Mg3520Obj* o) {
    u32 t;
    s16* row;
    int lo;
    PSVECAdd(&o->pos, &o->_0C, &o->pos);
    PSVECAdd(&o->_18, &o->_24, &o->_18);
    if (o->_3A < 0x7FFE) {
        o->_3A++;
    } else {
        o->_3A = 0x7FFF;
    }
    if ((f32)o->_3A >= (&lbl_3_data_21A64)[7]) {
        t = MG3520->timer / 60 / 20;
        if (t > 3) {
            t = 3;
        }
        o->state = 0;
        o->_3A = 0;
        row = lbl_3_data_21A90 + g_Minigame.soloMinigameDifficulty * 8;
        lo = row[t * 2];
        t = random_fn_3_9EE24((row[t * 2 + 1] - lo) * 60);
        o->_38 = t + lo * 60;
    }
}
void fn_3_137DE4(Mg3520Obj* o) {
    h137DE4(o);
}

// .text:0x00137F14 size:0x118 mapped:0x80776FA8
static inline void h137F14(Mg3520Obj* o) {
    if (g_Minigame._72A != 0) {
        o->_0C.y = (&lbl_3_data_21A64)[5];
        o->state = 5;
        o->_3A = 0;
    } else {
        if (o->_3E != 0) {
            o->_3F++;
            if (o->_3F >= 10) {
                fn_3_90064(0x303);
                o->_3E = 0;
            }
        }
        if (o->_3A < 0x7FFE) {
            o->_3A++;
        } else {
            o->_3A = 0x7FFF;
        }
        if (fn_3_137B10(o) == 0 && (f32)o->_3A >= (&lbl_3_data_21A64)[6]) {
            o->_0C.y = (&lbl_3_data_21A64)[5];
            o->state = 5;
            o->_3A = 0;
        }
    }
}
void fn_3_137F14(Mg3520Obj* o) {
    h137F14(o);
}

// .text:0x0013802C size:0x2B4 mapped:0x807770C0
static inline void h13802C(Mg3520Obj* o) {
    Vec* vel;
    if (g_Minigame._72A != 0) {
        o->_0C.y = (&lbl_3_data_21A64)[5];
        o->state = 5;
        o->_3A = 0;
        return;
    }
    PSVECAdd(&o->pos, vel = &o->_0C, &o->pos);
    if (fn_3_137B10(o) != 0) {
        (&g_Minigame._1D78)[(s8)o->_3C] = 0;
        fn_3_90064(0x30D);
        return;
    }
    if (o->pos.y <= 0.0f) {
        o->pos.y = 0.0f;
        memset(vel, 0, sizeof(Vec));
        o->_3A = 0;
        o->state = 3;
        fn_3_1371E8();
        fn_3_137224(o);
        (&g_Minigame._1D78)[(s8)o->_3C] = 0;
        fn_3_90064(0x2F7);
    }
}
void fn_3_13802C(Mg3520Obj* o) {
    if (g_Minigame._72A != 0) {
        o->_0C.y = (&lbl_3_data_21A64)[5];
        o->state = 5;
        o->_3A = 0;
        return;
    }
    PSVECAdd((Vec*)o, &o->_0C, (Vec*)o);
    if (fn_3_137B10((Mg3520Obj*)o) != 0) {
        (&g_Minigame._1D78)[(s8)o->_3C] = 0;
        fn_3_90064(0x30D);
        return;
    }
    if (o->pos.y <= 0.0f) {
        o->pos.y = 0.0f;
        memset(&o->_0C, 0, 0xC);
        o->_3A = 0;
        o->state = 3;
        fn_3_1371E8();
        fn_3_137224((Mg3520Obj*)o);
        (&g_Minigame._1D78)[(s8)o->_3C] = 0;
        fn_3_90064(0x2F7);
    }
}

// .text:0x001382E0 size:0x168 mapped:0x80777374
static inline void h1382E0(Mg3520Obj* o) {
    u32 t0 = MG3520->timer / 60 / 20;
    int t = t0;
    s16* row;
    int lo;
    if (g_Minigame._72A != 0) {
        o->state = 0;
        o->_3A = 0;
        row = lbl_3_data_21A90 + g_Minigame.soloMinigameDifficulty * 8;
        lo = row[t0 * 2];
        t0 = random_fn_3_9EE24((row[t0 * 2 + 1] - lo) * 60);
        o->_38 = t0 + lo * 60;
        return;
    }
    if (o->_3A < 0x7FFE) {
        o->_3A++;
    } else {
        o->_3A = 0x7FFF;
    }
    if ((u32)t > 3) {
        t = 3;
    }
    if (o->_3A / 60 >= lbl_3_data_21AD0[lbl_3_bss_B781][t]) {
        f32 z = lbl_3_rodata_35D0;
        o->_0C.z = z;
        o->_0C.x = z;
        o->_0C.y = -(&lbl_3_data_21A64)[1];
        o->state = 2;
        o->_3A = 0;
    }
}
// (inline copy above is used by fn_3_138AA4; the standalone copy keeps its own register shape)
void fn_3_1382E0(Mg3520Obj* o) {
    u32 t0 = MG3520->timer / 60 / 20;
    int t = t0;
    s16* row;
    int lo;
    if (g_Minigame._72A != 0) {
        o->state = 0;
        o->_3A = 0;
        row = lbl_3_data_21A90 + g_Minigame.soloMinigameDifficulty * 8;
        lo = row[t0 * 2];
        t0 = random_fn_3_9EE24((row[t0 * 2 + 1] - lo) * 60);
        o->_38 = t0 + lo * 60;
        return;
    }
    if (o->_3A < 0x7FFE) {
        (o->_3A)++;
    } else {
        o->_3A = 0x7FFF;
    }
    if ((u32)t > 3) {
        t = 3;
    }
    if (o->_3A / 60 >= lbl_3_data_21AD0[lbl_3_bss_B781][t]) {
        f32 z = lbl_3_rodata_35D0;
        o->_0C.z = z;
        o->_0C.x = z;
        o->_0C.y = -(&lbl_3_data_21A64)[1];
        o->state = 2;
        o->_3A = 0;
    }
}

// .text:0x00138448 size:0x6C mapped:0x807774DC
static inline void h138448(Mg3520Obj* a) {
    if (g_Minigame._72A == 0) {
        if (a->_3A < 0x7FFE) {
            a->_3A++;
        } else {
            a->_3A = 0x7FFF;
        }
        if (a->_3A >= a->_38) {
            a->_3E = 0;
            fn_3_1384B4(a);
        }
    }
}
void fn_3_138448(Mg3520Obj* a) {
    if (g_Minigame._72A == 0) {
        s16* t = &a->_3A;
        if (*t < 0x7FFE) {
            *t += 1;
        } else {
            *t = 0x7FFF;
        }
        if (a->_3A >= a->_38) {
            a->_3E = 0;
            fn_3_1384B4((Mg3520Obj*)a);
        }
    }
}

// .text:0x001384B4 size:0x5F0 mapped:0x80777548
// Respawn obstacle o at a spot chosen from the free coins inside its angular
// sector [o+0x30, o+0x34] (degrees) around the field center.
extern f32 lbl_3_rodata_36A0;
extern f32 lbl_3_rodata_35D4;
extern f32 lbl_3_rodata_36A4;
extern f32 lbl_3_rodata_36A8;
// NONMATCHING 95.6%: float saved-register numbering and zero-init/store scheduling differ
#if NONMATCHING
void fn_3_1384B4(Mg3520Obj* o) {
    Vec center = { 0.0f, 0.0f, 20.0f };
    Vec rel;
    Vec n;
    Vec off;
    Vec axis = { 1.0f, 0.0f, 0.0f };
    u32 idx[100];
    f32 sx = lbl_3_rodata_35D0;
    f32 sz = sx;
    u32 cnt = 0;
    u32 i;
    u32* list = idx;
    u32* w = list;
    for (i = 0; i < 100; i++) {
        if (COIN_STATE(i) == 1) {
            f32 ang;
            rel.y = lbl_3_rodata_35D0;
            rel.x = COIN_POS(i).x - center.x;
            rel.z = COIN_POS(i).z - center.z;
            PSVECNormalize(&rel, &n);
            ang = lbl_3_rodata_36A0 * (f32)acos(PSVECDotProduct(&axis, &n));
            if (n.z < lbl_3_rodata_35D0) {
                ang = lbl_3_rodata_3658 - ang;
            }
            if (ang >= o->_30 && ang <= o->_34) {
                cnt++;
                sx += rel.x;
                *w = i;
                sz += rel.z;
                w++;
            }
        }
    }
    if (cnt != 0) {
        f32 vz = lbl_3_rodata_35D0;
        f32 vx = vz;
        f32 sdx, sdz, len;
        u32 k;
        sx = sx / (f32)cnt;
        sz = sz / (f32)cnt;
        for (k = 0; k < cnt; k++) {
            u32 c = *list;
            rel.x = COIN_POS(c).x - center.x;
            rel.z = COIN_POS(c).z - center.z;
            vx = vx + pow(rel.x - sx, 2.0);
            vz = vz + pow(rel.z - sz, 2.0);
            list++;
        }
        sdx = sqrt(vx / (f32)cnt);
        sdz = sqrt(vz / (f32)cnt);
        off.x = off.y = off.z = lbl_3_rodata_35D0;
        if (sdx > lbl_3_rodata_364C) {
            off.x = sdx * (fabs(sx) / sx) + sx;
        } else {
            off.x = sx;
        }
        if (sdz > lbl_3_rodata_3690) {
            off.z = sdz * (fabs(sz) / sz) + sz;
        } else {
            off.z = sz;
        }
        len = sqrt(pow(off.x, 2.0) + pow(off.z, 2.0));
        if (len < lbl_3_rodata_35D4) {
            PSVECNormalize(&off, &off);
            off.x *= lbl_3_rodata_35D4;
            off.z *= lbl_3_rodata_35D4;
        } else if (len > lbl_3_rodata_36A4) {
            PSVECNormalize(&off, &off);
            off.x *= lbl_3_rodata_36A4;
            off.z *= lbl_3_rodata_36A4;
        }
    } else {
        f32 lo = o->_30;
        f32 ang = lbl_3_rodata_3660 * ((o->_34 - lo) * ((f32)rand() / lbl_3_rodata_365C) + lo);
        off.x = cos(ang);
        off.z = sin(ang);
        off.y = lbl_3_rodata_35D0;
        PSVECNormalize(&off, &off);
        PSVECScale(&off, lbl_3_rodata_36A8 * ((f32)rand() / lbl_3_rodata_365C) + lbl_3_rodata_35D4, &off);
    }
    {
        // keep the spot at least a box half-size away from the sector's edge line
        f32 c = cos(lbl_3_rodata_3660 * o->_34);
        f32 s = sin(lbl_3_rodata_3660 * o->_34);
        f32 dot = off.x * c + off.z * s;
        f32 px = c * dot;
        f32 pz = s * dot;
        f32 ex = off.x - px;
        f32 ez = off.z - pz;
        f32 bx = 3.5 * (fabs(ex) / ex);
        f32 bz = 3.125 * (fabs(ez) / ez);
        if (fabs(ex) < fabs(bx)) {
            off.x = px + bx;
        }
        if (fabs(ez) < fabs(bz)) {
            off.z = pz + bz;
        }
    }
    o->pos.x = off.x + center.x;
    o->pos.y = lbl_3_data_21A64;
    o->pos.z = off.z + center.z;
    memset(&o->_18, 0, sizeof(Vec));
    memset(&o->_24, 0, sizeof(Vec));
    o->_3A = 0;
    o->state = 1;
}
#endif

// .text:0x00138AA4 size:0x71C mapped:0x80777B38
// Run the per-obstacle state handlers (records at g_Minigame+0xBB0, state at +0x3D).
#pragma dont_inline off
void fn_3_138AA4(void) {
    u32 n;
    if (g_Minigame.turnOverStatus != 0) {
        return;
    }
    for (n = 0; n < lbl_3_bss_B780; n++) {
        if (n >= 4) {
            break;
        }
        switch (MG3520->objs[n].state) {
        case 0:
            h138448(&MG3520->objs[n]);
            break;
        case 1:
            h1382E0(&MG3520->objs[n]);
            break;
        case 2:
            h13802C(&MG3520->objs[n]);
            break;
        case 3:
            h137F14(&MG3520->objs[n]);
            break;
        case 4:
            h137DE4(&MG3520->objs[n]);
            break;
        case 5:
            h137CF8(&MG3520->objs[n]);
            break;
        }
    }
}
#pragma dont_inline on

// .text:0x001391C0 size:0x540 mapped:0x80778254
// NONMATCHING 98.4%: registers only; saved-register numbering is rotated (b/n/g/table bases)
#if NONMATCHING
void fn_3_1391C0(void) {
    UnkStructMinigame* b = &g_Minigame._B6C;
    VecSrcDst seg;
    CollisionStruct col;
    f32 rad, best, d, rr, dx, dz;
    s32 sel, k, n, c;
    seg.src.x = b->_0.x;
    seg.src.y = -b->_0.y;
    seg.src.z = b->_0.z;
    b->_C.y += lbl_3_data_219B8[11];
    b->_0.x = b->_C.x + b->_0.x;
    b->_0.y = b->_C.y + b->_0.y;
    b->_0.z = b->_C.z + b->_0.z;
    seg.dst.x = b->_0.x;
    seg.dst.y = -b->_0.y;
    seg.dst.z = b->_0.z;
    if ((u32)checkCollision(&seg, &col, 0, 0) == 5) {
        col.normal.y *= lbl_3_rodata_3648;
        refl_w(&b->_C.x, &col.normal.x);
        b->_0.x = col.position.x;
        b->_0.y = -col.position.y;
        b->_0.z = col.position.z;
    }
    seg.dst.x = b->_0.x;
    seg.dst.y = -b->_0.y;
    seg.dst.z = b->_0.z;
    if (fn_3_1373E0(&seg, (Vec*)&b->_C, &col, lbl_3_data_219B8[15])) {
        b->_0.x = col.position.x;
        b->_0.y = col.position.y;
        b->_0.z = col.position.z;
        memcpy(&b->_C, &col.normal, sizeof(Vec));
        seg.dst.x = b->_0.x;
        seg.dst.y = -b->_0.y;
        seg.dst.z = b->_0.z;
        if ((u32)checkCollision(&seg, &col, 0, 0) == 5) {
            col.normal.y *= lbl_3_rodata_3648;
            refl_w(&b->_C.x, &col.normal.x);
            b->_0.x = col.position.x;
            b->_0.y = -col.position.y;
            b->_0.z = col.position.z;
        }
    }
    if (b->_0.y < lbl_3_data_219B8[14]) {
        // hit the ground: scatter the carried coins
        for (n = 0; n < 10; n++) {
            s32 ang;
            f32 r;
            c = b->coins[n];
            COIN_POS(c).x = b->_0.x;
            COIN_POS(c).y = b->_0.y;
            COIN_POS(c).z = b->_0.z;
            ang = random_fn_3_9EE24(0x1000);
            getComponentsFromSAng(ang + (random_fn_3_9EE24(lbl_3_data_21A04[4] * 2) - lbl_3_data_21A04[4]), &COIN_VEL(c).x, &COIN_VEL(c).z);
            r = RandomF32_Game_Range(-lbl_3_data_219B8[9], lbl_3_data_219B8[10]);
            COIN_VEL(c).x *= r;
            COIN_VEL(c).z *= r;
            COIN_VEL(c).y = RandomF32_Game_Range(lbl_3_data_219B8[7], lbl_3_data_219B8[8]);
            COIN_STATE(c) = 1;
            COIN_TIMER(c) = 0;
        }
        b->_40[0] = 0;
        return;
    }
    best = 99999.9f;
    rad = lbl_3_data_219B8[15];
    k = 0;
    sel = -1;
    for (; k < 4; k++) {
        s32 fi = (u8)g_Minigame.minigameFielderIndex[k];
        InMemFielderType* f;
        if ((s8)fi < 0) {
            continue;
        }
        if (g_Minigame.starDashStunType[k] != 0 && g_Minigame.starDashStunType[k] != 3) {
            continue;
        }
        f = &g_Fielders[(s8)fi];
        if (f->_203 != 0 && f->_204 > 3) {
            continue;
        }
        if (f->_16C + f->height < b->_0.y) {
            continue;
        }
        rr = rad + lbl_3_data_47BC[f->weight];
        dx = f->pos.x - b->_0.x;
        dz = f->pos.z - b->_0.z;
        d = dx * dx + dz * dz;
        rr = rr * rr;
        if (d < rr && d < best) {
            best = d;
            sel = k;
        }
    }
    if (sel >= 0) {
        // caught: the fielder scores all carried coins
        g_Minigame.miniGameCurrentPoints[sel] += lbl_3_data_21A04[5] * 10;
        for (n = 0; n < 10; n++) {
            s32 ang;
            f32 base, r;
            c = b->coins[n];
            COIN_POS(c).x = b->_0.x;
            COIN_POS(c).y = b->_0.y;
            COIN_POS(c).z = b->_0.z;
            ang = random_fn_3_9EE24(0x1000);
            base = RandomF32_Game_Range(lbl_3_data_219B8[2], lbl_3_data_219B8[3]);
            COIN_STATE(c) = 3;
            getComponentsFromSAng(ang, &COIN_VEL(c).x, &COIN_VEL(c).z);
            r = base + RandomF32_Game_Range(-lbl_3_data_219B8[4], lbl_3_data_219B8[4]);
            COIN_VEL(c).x *= r;
            COIN_VEL(c).z *= r;
            COIN_VEL(c).y = RandomF32_Game_Range(lbl_3_data_219B8[0], lbl_3_data_219B8[1]);
            COIN_TIMER(c) = 0;
        }
        fn_3_90064(0x30A);
        b->_40[0] = 0;
        lbl_3_common_bss_34C58._30 = lbl_3_data_88DC[1];
    }
}
#endif

// .text:0x00139700 size:0x4C mapped:0x80778794
void fn_3_139700(void) {
    if (MG3520->_BAC != 0) {
        if (g_Minigame.turnOverStatus != 0) {
            MG3520->_BAC = 0;
            return;
        }
        fn_3_1391C0();
    }
}

// .text:0x0013974C size:0xBC mapped:0x807787E0
void fn_3_13974C(void) {
    u32 i;
    for (i = 0; i < 100; i++) {
        if (COIN_STATE(i) == 3) {
            COIN_TIMER(i)++;
            PSVECAdd(&COIN_POS(i), &COIN_VEL(i), &COIN_POS(i));
            COIN_VEL(i).y += lbl_3_data_219B8[11];
            if (COIN_VEL(i).y < lbl_3_rodata_35D0) {
                COIN_STATE(i) = 0;
                g_Minigame._1D6C--;
            }
        }
    }
}

// .text:0x00139808 size:0x498 mapped:0x8077889C
void fn_3_139808(void) {
    VecSrcDst seg;
    CollisionStruct col;
    f32 rad, best, d, rr, dx, dz;
    s32 sel, i, k;
    InMemFielderType* f;
    for (i = 0; i < 100; i++) {
        if (COIN_STATE(i) != 1) {
            continue;
        }
        COIN_TIMER(i)++;
        if (COIN_TIMER(i) > lbl_3_data_21A04[3]) {
            COIN_STATE(i) = 0;
            g_Minigame._1D6C--;
            continue;
        }
        seg.src.x = COIN_POS(i).x;
        seg.src.y = -COIN_POS(i).y;
        seg.src.z = COIN_POS(i).z;
        COIN_VEL(i).y += lbl_3_data_219B8[11];
        COIN_POS(i).x += COIN_VEL(i).x;
        COIN_POS(i).y += COIN_VEL(i).y;
        COIN_POS(i).z += COIN_VEL(i).z;
        if (COIN_POS(i).y < lbl_3_data_219B8[14]) {
            COIN_POS(i).y = lbl_3_data_219B8[14];
            COIN_VEL(i).y *= -lbl_3_data_219B8[12];
            COIN_VEL(i).x *= lbl_3_data_219B8[13];
            COIN_VEL(i).z *= lbl_3_data_219B8[13];
        }
        seg.dst.x = COIN_POS(i).x;
        seg.dst.y = -COIN_POS(i).y;
        seg.dst.z = COIN_POS(i).z;
        if ((u32)checkCollision(&seg, &col, 0, 0) == 5) {
            col.normal.y *= lbl_3_rodata_3648;
            refl_w(&COIN_VEL(i).x, &col.normal.x);
            COIN_POS(i).x = col.position.x;
            COIN_POS(i).y = -col.position.y;
            COIN_POS(i).z = col.position.z;
        }
        seg.dst.x = COIN_POS(i).x;
        seg.dst.y = -COIN_POS(i).y;
        seg.dst.z = COIN_POS(i).z;
        if (fn_3_1373E0(&seg, &COIN_VEL(i), &col, lbl_3_data_219B8[15])) {
            COIN_POS(i).x = col.position.x;
            COIN_POS(i).y = col.position.y;
            COIN_POS(i).z = col.position.z;
            memcpy(&COIN_VEL(i), &col.normal, sizeof(Vec));
            seg.dst.x = COIN_POS(i).x;
            seg.dst.y = -COIN_POS(i).y;
            seg.dst.z = COIN_POS(i).z;
            if ((u32)checkCollision(&seg, &col, 0, 0) == 5) {
                col.normal.y *= lbl_3_rodata_3648;
                refl_w(&COIN_VEL(i).x, &col.normal.x);
                COIN_POS(i).x = col.position.x;
                COIN_POS(i).y = -col.position.y;
                COIN_POS(i).z = col.position.z;
            }
        }
        if (g_Minigame.turnOverStatus != 0) {
            continue;
        }
        best = 99999.9f;
        rad = lbl_3_data_219B8[15];
        k = 0;
        sel = -1;
        for (; k < 4; k++) {
            // g_Minigame.minigameFielderIndex[k] / starDashStunType[k]: the byte-offset form keeps the original registers
            s32 fi = ((u8*)&g_Minigame)[(s32)OFFSET_OF(MiniGameStruct, minigameFielderIndex[0]) + k];
            if ((s8)fi < 0) {
                continue;
            }
            if (((u8*)&g_Minigame)[(s32)OFFSET_OF(MiniGameStruct, starDashStunType[0]) + k] != 0 && ((u8*)&g_Minigame)[(s32)OFFSET_OF(MiniGameStruct, starDashStunType[0]) + k] != 3) {
                continue;
            }
            f = &g_Fielders[(s8)fi];
            if (f->_203 != 0 && f->_204 > 3) {
                continue;
            }
            if (f->_16C + f->height < COIN_POS(i).y) {
                continue;
            }
            dz = f->pos.z - COIN_POS(i).z;
            rr = rad + lbl_3_data_47BC[f->weight];
            rr = rad + lbl_3_data_47BC[f->weight];
            dz = f->pos.z - COIN_POS(i).z;
            rr = rad + lbl_3_data_47BC[f->weight];
            dx = f->pos.x - COIN_POS(i).x;
            dz = f->pos.z - COIN_POS(i).z;
            d = dx * dx + dz * dz;
            rr = rr * rr;
            if (d < rr && d < best) {
                best = d;
                sel = k;
            }
        }
        if (sel >= 0) {
            g_Minigame.miniGameCurrentPoints[sel] += lbl_3_data_21A04[5];
            COIN_STATE(i) = 3;
            COIN_VEL(i).z = 0.0f;
            COIN_VEL(i).x = 0.0f;
            COIN_VEL(i).y = RandomF32_Game_Range(lbl_3_data_219B8[0], lbl_3_data_219B8[1]);
            COIN_TIMER(i) = 0;
            if (lbl_3_common_bss_34C58._30 == 0) {
                fn_3_90064(0x2E9);
                lbl_3_common_bss_34C58._30 = lbl_3_data_88DC[1];
            }
        }
    }
}

// .text:0x00139CA0 size:0x2E4 mapped:0x80778D34
void fn_3_139CA0(void) {
    UnkStructMinigame* s = NULL;
    s32 i;
    u8 flag = 0;
    s32 n;
    s16 t;
    s32 ang;
    f32 base;
    if (g_Minigame.turnOverStatus == 0) {
        t = g_Minigame._1D50;
        g_Minigame._1D50 = --t;
        if (t <= 0) {
            n = lbl_3_data_21A04[2];
            if (MG3520->coinCount % lbl_3_data_21A04[6] == 0 && (0x64 - g_Minigame._1D6C) >= 10 && g_Minigame._B6C._40[0] == 0) {
                s = &g_Minigame._B6C;
                s->_40[0] = 1;
                n = 10;
                flag = 1;
            }
            ang = random_fn_3_9EE24(0x1000);
            base = RandomF32_Game_Range(lbl_3_data_219B8[2], lbl_3_data_219B8[3]);
            for (i = 0; i < 100; i++) {
                if (flag) {
                    if (n != 0) {
                        if (COIN_STATE(i) == 0) {
                            COIN_STATE(i) = 2;
                            COIN_TIMER(i) = 0;
                            g_Minigame._1D6C++;
                            s->coins[n - 1] = i;
                            n--;
                        }
                    } else {
                        f32 r;
                        s->_0.x = lbl_3_data_219AC[0];
                        s->_0.y = lbl_3_data_219AC[1];
                        s->_0.z = lbl_3_data_219AC[2];
                        getComponentsFromSAng(ang + (random_fn_3_9EE24(lbl_3_data_21A04[4] * 2) - lbl_3_data_21A04[4]), &s->_C.x, &s->_C.z);
                        r = base + RandomF32_Game_Range(-lbl_3_data_219B8[4], lbl_3_data_219B8[4]);
                        s->_C.x *= r;
                        s->_C.z *= r;
                        s->_C.y = RandomF32_Game_Range(lbl_3_data_219B8[5], lbl_3_data_219B8[6]);
                        break;
                    }
                } else if (COIN_STATE(i) == 0) {
                    f32 r;
                    COIN_POS(i).x = lbl_3_data_219AC[0];
                    COIN_POS(i).y = lbl_3_data_219AC[1];
                    COIN_POS(i).z = lbl_3_data_219AC[2];
                    getComponentsFromSAng(ang + (random_fn_3_9EE24(lbl_3_data_21A04[4] * 2) - lbl_3_data_21A04[4]), &COIN_VEL(i).x, &COIN_VEL(i).z);
                    r = base + RandomF32_Game_Range(-lbl_3_data_219B8[4], lbl_3_data_219B8[4]);
                    COIN_VEL(i).x *= r;
                    COIN_VEL(i).z *= r;
                    COIN_VEL(i).y = RandomF32_Game_Range(lbl_3_data_219B8[0], lbl_3_data_219B8[1]);
                    n--;
                    COIN_STATE(i) = 1;
                    COIN_TIMER(i) = 0;
                    g_Minigame._1D6C++;
                    MG3520->coinCount += 1;
                    if (n <= 0) {
                        fn_3_90064(0x2E8);
                        break;
                    }
                }
            }
            g_Minigame._1D50 = RandomInt_Game_Range(lbl_3_data_21A04[0], lbl_3_data_21A04[1]);
        }
    }
}

// .text:0x00139F84 size:0xC4 mapped:0x80779018
// The coin loop walks g_Minigame with byte pointers (one per coin array) to keep the original's induction registers.
void fn_3_139F84(void) {
    u32 i;
    u8* a;
    s16* b;
    u8* c;
    fn_3_139CA0();
    fn_3_139808();
    a = ((u8*)&g_Minigame);
    b = (s16*)((u8*)&g_Minigame);
    c = ((u8*)&g_Minigame);
    for (i = 0; i < 100; i++) {
        if (a[(s32)OFFSET_OF(Mg3520, coinState[0])] == 3) {
            b[(s32)(OFFSET_OF(Mg3520, coinTimer[0]) / sizeof(s16))]++;
            PSVECAdd((Vec*)(c + (s32)OFFSET_OF(Mg3520, coinPos[0])), (Vec*)(c + (s32)OFFSET_OF(Mg3520, coinVel[0])), (Vec*)(c + (s32)OFFSET_OF(Mg3520, coinPos[0])));
            *(f32*)(c + (s32)OFFSET_OF(Mg3520, coinVel[0].y)) += lbl_3_data_219B8[11];
            if (*(f32*)(c + (s32)OFFSET_OF(Mg3520, coinVel[0].y)) < lbl_3_rodata_35D0) {
                a[(s32)OFFSET_OF(Mg3520, coinState[0])] = 0;
                g_Minigame._1D6C--;
            }
        }
        a++;
        b++;
        c += sizeof(Vec);
    }
}

// .text:0x0013A048 size:0x64 mapped:0x807790DC
void fn_3_13A048(int i, int j) {
    s16* arr = &g_Minigame.miniGameCurrentPoints[0];
    s16 v = arr[j];
    s16 c = lbl_3_data_21A04[7];
    if (v < c) {
        arr[i] += v;
        arr[j] = 0;
    } else {
        arr[i] += c;
        arr[j] -= c;
    }
}

static inline void aim_13A724(void);
static inline void reflect3(f32* out, f32* a, f32* b) {
    f32 d = (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
    d = d * lbl_3_rodata_3638;
    out[0] = a[0] - d * b[0];
    out[1] = a[1] - d * b[1];
    out[2] = a[2] - d * b[2];
}
// Bounce the flight arc (start 0x6F4, end 0x70C) off a wall hit
static inline void bounceArc(CollisionStruct* c) {
    Vec n;
    Vec d;
    n.x = -c->normal.z;
    n.y = 0.0f;
    n.z = c->normal.x;
    d.x = c->position.x - g_Minigame._6F4;
    d.y = 0.0f;
    d.z = c->position.z - g_Minigame._6FC;
    if (d.x * n.x + d.z * n.z > lbl_3_rodata_35D0) {
        n.x *= lbl_3_rodata_3648;
        n.z *= lbl_3_rodata_3648;
    }
    reflect3(&d.x, &d.x, &n.x);
    n.x *= lbl_3_rodata_3648;
    n.z *= lbl_3_rodata_3648;
    g_Minigame._6F4 = c->position.x + d.x;
    g_Minigame._6FC = c->position.z + d.z;
    d.x = c->position.x - g_Minigame._70C;
    d.y = 0.0f;
    d.z = c->position.z - g_Minigame._714;
    reflect3(&d.x, &d.x, &n.x);
    g_Minigame._70C = c->position.x + d.x;
    g_Minigame._714 = c->position.z + d.z;
    g_Minigame._700 = lbl_3_rodata_36C8 * (g_Minigame._70C + g_Minigame._6F4);
    g_Minigame._708 = lbl_3_rodata_36C8 * (g_Minigame._714 + g_Minigame._6FC);
}
// .text:0x0013A0AC size:0x678 mapped:0x80779140
extern f32 lbl_3_rodata_36CC;
extern void fn_3_28E4(Vec* out, Vec* points, int count, f32 frame);
extern void fn_3_1608F0(s32 kind, s32 value, s32 extra);
extern void fn_80011604(s8 index, DOTevHook value);
typedef struct Bss37400View3520 {
    /*0x00*/ u8 _00[0x40];
    /*0x40*/ s16 humanPlayer;
} Bss37400View3520;
extern Bss37400View3520 lbl_3_common_bss_37400;
// NONMATCHING 94%: the inlined wall bounce is scheduled differently (float regs, store order)
#if NONMATCHING
// Ball in flight along the arc 0x6F4 -> 0x700 -> 0x70C; bounces off walls, lands,
// or is caught by the nearest fielder.
void fn_3_13A0AC(void) {
    VecSrcDst seg;
    CollisionStruct col;
    f32 best, d;
    s32 sel, k;
    g_Minigame._724++;
    g_Minigame._726++;
    if (g_Minigame.turnOverStatus != 0) {
        g_Minigame._72A = 0;
        return;
    }
    if (g_Minigame._724 > lbl_3_data_21A30[0]) {
        g_Minigame._72A = 0;
        fn_3_14E988(4);
        return;
    }
    seg.src.x = g_Minigame._6E8;
    seg.src.y = -(lbl_3_data_21A14[2] * lbl_3_rodata_36C8);
    seg.src.z = g_Minigame._6F0;
    fn_3_28E4((Vec*)&g_Minigame._6E8, (Vec*)&g_Minigame._6F4, 3, (f32)g_Minigame._726 / (f32)g_Minigame._728);
    seg.dst.x = g_Minigame._6E8;
    seg.dst.y = -(lbl_3_data_21A14[2] * lbl_3_rodata_36C8);
    seg.dst.z = g_Minigame._6F0;
    if ((u32)checkCollision(&seg, &col, 0, 0) == 5) {
        Vec n;
        Vec d;
        n.x = -col.normal.z;
        n.y = 0.0f;
        n.z = col.normal.x;
        d.x = col.position.x - g_Minigame._6F4;
        d.y = 0.0f;
        d.z = col.position.z - g_Minigame._6FC;
        if (d.x * n.x + d.z * n.z > lbl_3_rodata_35D0) {
            n.x *= lbl_3_rodata_3648;
            n.z *= lbl_3_rodata_3648;
        }
        g_Minigame._6E8 = col.position.x;
        reflect3(&d.x, &d.x, &n.x);
        n.x *= lbl_3_rodata_3648;
        n.z *= lbl_3_rodata_3648;
        g_Minigame._6F4 = col.position.x + d.x;
        g_Minigame._6FC = col.position.z + d.z;
        d.x = col.position.x - g_Minigame._70C;
        d.y = 0.0f;
        d.z = col.position.z - g_Minigame._714;
        reflect3(&d.x, &d.x, &n.x);
        g_Minigame._70C = col.position.x + d.x;
        g_Minigame._714 = col.position.z + d.z;
        g_Minigame._700 = lbl_3_rodata_36C8 * (g_Minigame._70C + g_Minigame._6F4);
        g_Minigame._708 = lbl_3_rodata_36C8 * (g_Minigame._714 + g_Minigame._6FC);
        g_Minigame._6F0 = seg.src.z;
    }
    if (g_Minigame._6EC <= lbl_3_data_21A14[4]) {
        // landed: start a new arc from here
        g_Minigame._6EC = lbl_3_data_21A14[4];
        g_Minigame._72B++;
        aim_13A724();
    }
    best = lbl_3_rodata_36CC;
    k = 0;
    sel = -1;
    for (; k < 4; k++) {
        s32 fi = (u8)g_Minigame.minigameFielderIndex[k];
        InMemFielderType* f;
        if ((s8)fi < 0) {
            continue;
        }
        f = &g_Fielders[(s8)fi];
        if (f->_16C + f->height < g_Minigame._6EC - lbl_3_data_21A14[5]) {
            continue;
        }
        d = dolsqrtf2(SQ(g_Minigame._6E8 - f->pos.x) + SQ(g_Minigame._6F0 - f->pos.z));
        if (d < lbl_3_data_21A14[5] + lbl_3_data_47BC[f->weight] && d < best) {
            best = d;
            sel = k;
        }
    }
    if (sel >= 0) {
        g_Minigame.miniGameCurrentPoints[sel] += lbl_3_data_21A30[5];
        g_Minigame._72A = 0;
        g_Minigame._1D6D = sel;
        g_Minigame._1D56 = lbl_3_data_21A30[1];
        fn_3_14E988(4);
        if ((s8)g_Minigame.playerIDWithPowerup[0] == sel) {
            fn_800115C8((s8)sel);
            if (MG_STARDASH_PTR == &lbl_3_data_21AF8[5]) {
                ((s8*)g_Minigame.playerIDWithPowerup)[0] = -1;
            }
        }
        fn_3_150010(sel);
        fn_80011604(sel, fn_3_132EDC);
        if (g_d_GameSettings.exhibitionMatchInd == 0 && sel == lbl_3_common_bss_37400.humanPlayer) {
            fn_3_1608F0(3, 0, 0);
        }
    }
}
#endif

// .text:0x0013A724 size:0x178 mapped:0x807797B8
static inline void aim_13A724(void) {
    Vec v;
    f32 r;
    g_Minigame._6F4 = g_Minigame._6E8;
    g_Minigame._6F8 = g_Minigame._6EC;
    g_Minigame._6FC = g_Minigame._6F0;
    g_Minigame._728 = RandomInt_Game_Range(lbl_3_data_21A30[3], lbl_3_data_21A30[4]);
    r = RandomF32_Game_Range(lbl_3_data_21A14[0], lbl_3_data_21A14[1]);
    v.x = lbl_3_data_219AC[0] - g_Minigame._6E8;
    v.y = lbl_3_data_219AC[1] - g_Minigame._6EC;
    v.z = lbl_3_data_219AC[2] - g_Minigame._6F0;
    // result unused: the original computes the distance and drops it
#pragma dont_inline off
    dolsqrtf2(v.x * v.x + v.z * v.z);
#pragma dont_inline on
    getComponentsFromSAng(random_fn_3_9EE24(0x1000), &v.x, &v.z);
    {
        f32 nx, nz;
        nx = v.x * r + g_Minigame._6F4;
        nz = v.z * r + g_Minigame._6FC;
        g_Minigame._70C = nx;
        g_Minigame._714 = nz;
        g_Minigame._710 = lbl_3_data_21A14[4];
        g_Minigame._700 = lbl_3_rodata_36C8 * (g_Minigame._6F4 + nx);
        g_Minigame._708 = lbl_3_rodata_36C8 * (g_Minigame._6FC + nz);
    }
    g_Minigame._704 = g_Minigame._6F8 + RandomF32_Game_Range(lbl_3_data_21A14[2], lbl_3_data_21A14[3]);
    g_Minigame._726 = 0;
}

void fn_3_13A724(void) {
    aim_13A724();
}

// .text:0x0013A89C size:0x1DC mapped:0x80779930
static inline void launch_13A89C(void) {
    if (g_Minigame.turnOverStatus == 0) {
        if ((g_Minigame._1D52 -= 1) <= 0) {
            g_Minigame._6E8 = lbl_3_data_219AC[0];
            g_Minigame._6EC = lbl_3_data_219AC[1];
            g_Minigame._6F0 = lbl_3_data_219AC[2];
            g_Minigame._72B = 0;
            aim_13A724();
            g_Minigame._72A = 1;
            g_Minigame._724 = 0;
            g_Minigame._1D52 = lbl_3_data_21A30[2];
            fn_3_150010(4);
            fn_3_106EB0();
        }
    }
}

void fn_3_13A89C(void) {
    launch_13A89C();
}

// .text:0x0013AA78 size:0x23C mapped:0x80779B0C
#pragma dont_inline off
void fn_3_13AA78(void) {
    if (g_Minigame._72A != 0) {
        fn_3_13A0AC();
    } else {
        launch_13A89C();
    }
    if ((s8)g_Minigame._1D6D >= 0 && (--g_Minigame._1D56 < 0 || g_Minigame.turnOverStatus != 0)) {
        fn_3_14E988((u8)g_Minigame._1D6D);
        fn_800115C8((u8)g_Minigame._1D6D);
        g_Minigame._1D6D = -1;
    }
}
#pragma dont_inline on

// .text:0x0013ACB4 size:0x10C mapped:0x80779D48
// NONMATCHING 87%: same instructions, the two reflections are scheduled differently
#if NONMATCHING
void fn_3_13ACB4(CollisionStruct* c) {
    bounceArc(c);
}
#endif

// .text:0x0013ADC0 size:0x5C mapped:0x80779E54
void fn_3_13ADC0(f32* out, f32* a, f32* b) {
    f32 d = (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
    d = d * lbl_3_rodata_3638;
    out[0] = a[0] - d * b[0];
    out[1] = a[1] - d * b[1];
    out[2] = a[2] - d * b[2];
}

static inline void clr(u32 s) {
    u32 i;
    for (i = s; i < 100; i++) {
        g_Minigame.wallBall_coinsVisibleInd[i] = 0;
    }
}
// .text:0x0013AE1C size:0x1C8 mapped:0x80779EB0
void fn_3_13AE1C(void) {
    fn_3_DE4FC();
    if (g_Minigame.soloMinigameDifficulty <= 2 && g_Minigame.multiPlayerInd == 0) {
        if (g_Minigame.minigameControlStruct[0]._1C[g_Minigame._1908] == 1 && g_Minigame.challenge_minigame_haven_tWonYetIndicator == 0) {
            g_Minigame._1A37 = 1;
        } else {
            g_Minigame._1A37 = 2;
        }
    }
    fn_3_5A6D4(0xE);
    fn_80011578();
    {
        u32 i;
        for (i = 0; i < 100; i++) {
            g_Minigame.wallBall_coinsVisibleInd[i] = 0;
        }
    }
    g_Minigame._1D50 = 0x1E;
    g_Minigame._1D6C = 0;
    g_Minigame._BED = 0;
    MG3520->objs[1].state = 0;
    MG3520->objs[2].state = 0;
    g_Minigame._CAD = 0;
    MG3520->item.state = 0;
}

// .text:0x0013AFE4 size:0x2A0 mapped:0x8077A078
void fn_3_13AFE4(void) {
    if (g_Minigame.turnOverStatus == 0) {
        if (MG3520->_17C4 == 0) {
            g_Minigame.turnOverStatus = 1;
            fn_3_10F550(3, 0);
            sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
        }
        return;
    }
    if (g_Minigame.turnOverStatus == 1) {
        g_Minigame.turnOverStatus = 2;
        g_GameLogic.CountdownUntilFade = lbl_3_data_21B20[0];
        fn_3_14E894();
    }
    if (--g_GameLogic.CountdownUntilFade == 7) {
        changeScene(3, 6);
    }
    if (g_GameLogic.CountdownUntilFade <= 0) {
        fn_3_DE4FC();
        if (g_Minigame.soloMinigameDifficulty <= 2 && g_Minigame.multiPlayerInd == 0) {
            if (g_Minigame.minigameControlStruct[0]._1C[g_Minigame._1908] == 1 && g_Minigame.challenge_minigame_haven_tWonYetIndicator == 0) {
                g_Minigame._1A37 = 1;
            } else {
                g_Minigame._1A37 = 2;
            }
        }
        fn_3_5A6D4(0xE);
        fn_80011578();
        clr(0);
        g_Minigame._1D50 = 0x1E;
        g_Minigame._1D6C = 0;
        g_Minigame._BED = 0;
        MG3520->objs[1].state = 0;
        MG3520->objs[2].state = 0;
        g_Minigame._CAD = 0;
        MG3520->item.state = 0;
    }
}

// .text:0x0013B284 size:0x740 mapped:0x8077A318
// Inline copies of the per-frame helpers that fn_3_13B284 inlines.
#pragma opt_unroll_loops off
static inline void h133320(void) {
    s8 i = 0;
    do {
        g_Minigame._1DC8[i] = 0;
        i++;
    } while (i < 4);
}

#pragma opt_unroll_loops reset
static inline void h13974C(void) {
    u32 i;
    for (i = 0; i < 100; i++) {
        if (COIN_STATE(i) == 3) {
            COIN_TIMER(i)++;
            PSVECAdd(&COIN_POS(i), &COIN_VEL(i), &COIN_POS(i));
            COIN_VEL(i).y += lbl_3_data_219B8[11];
            if (COIN_VEL(i).y < lbl_3_rodata_35D0) {
                COIN_STATE(i) = 0;
                g_Minigame._1D6C--;
            }
        }
    }
}

static inline void h139700(void) {
    if (MG3520->_BAC != 0) {
        if (g_Minigame.turnOverStatus != 0) {
            MG3520->_BAC = 0;
            return;
        }
        fn_3_1391C0();
    }
}

static inline void h136048(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        MG3520->spokeAng[i] += lbl_3_data_21A44;
        MG3520->spokeAng[i] = fn_3_9FE6C_normalizeAngle(MG3520->spokeAng[i]);
    }
}

static inline void h136EA4(void) {
    Mg3520U* g = (Mg3520U*)&g_Minigame;
    s32 pu;
    s16 t;
    f32 ang;
    if (g->mg.turnOverStatus != 0) {
        ((s8*)g->mg.playerIDWithPowerup)[0] = -1;
        g->x.item.state = 0;
    } else if (g->x.item.state != 0) {
        fn_3_13688C(&g->x.item);
    } else {
        pu = (s8)g->mg.playerIDWithPowerup[0];
        if (pu != -1) {
            t = g->mg._1D58;
            g->mg._1D58 = --t;
            if (t <= 0) {
                if (g->mg._1D6D != pu) {
                    fn_800115C8(g->mg.playerIDWithPowerup[0]);
                }
                ((s8*)g->mg.playerIDWithPowerup)[0] = -1;
            }
        } else {
            g->mg._CCC -= 1;
            if (g->mg._CCC <= 0) {
                if ((s8)(rand() % 100 - lbl_3_data_21B16) < 0) {
                    g->x.item.state = 1;
                } else {
                    g->x.item.state = 2;
                }
                g_Minigame._CB0 = lbl_3_data_219AC[0];
                g_Minigame._CB4 = lbl_3_data_219AC[1];
                g_Minigame._CB8 = lbl_3_data_219AC[2];
                g_Minigame._CC0 = lbl_3_data_21AF8[0];
                ang = lbl_3_rodata_3660 * (lbl_3_rodata_3658 * ((f32)rand() / lbl_3_rodata_365C));
                g_Minigame._CBC = lbl_3_data_21AF8[1] * (f32)cos(ang);
                g_Minigame._CC4 = lbl_3_data_21AF8[1] * (f32)sin(ang);
                g->mg._CCC = lbl_3_data_21B10[1];
            }
        }
    }
}

static inline void h135924(void) {
    u32 i;
    for (i = 0; i < 100; i++) {
        if (g_Minigame.wallBall_coinsVisibleInd[i] == 1) {
            if (MG3520->coinPos[i].y < lbl_3_rodata_35FC) {
                Vec d;
                Vec c = *(Vec*)lbl_3_rodata_35B8;
                if (&MG3520->coinPos[i].x != NULL) {
                    PSVECSubtract(&MG3520->coinPos[i], &c, &d);
                    d.y = lbl_3_rodata_35D0;
                    if (PSVECMag(&d) <= lbl_3_rodata_363C) {
                        Vec v;
                        Vec base = *(Vec*)lbl_3_rodata_35C4;
                        if (&MG3520->coinPos[i].x != NULL) {
                            PSVECNormalize(&d, &v);
                            PSVECScale(&v, lbl_3_rodata_363C, &v);
                            MG3520->coinPos[i].x = base.x + v.x;
                            MG3520->coinPos[i].z = base.z + v.z;
                        }
                    }
                }
            }
        }
    }
}

static inline void h13AFE4(void) {
    if (g_Minigame.turnOverStatus == 0) {
        if (MG3520->_17C4 == 0) {
            g_Minigame.turnOverStatus = 1;
            fn_3_10F550(3, 0);
            sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
        }
        return;
    }
    if (g_Minigame.turnOverStatus == 1) {
        g_Minigame.turnOverStatus = 2;
        g_GameLogic.CountdownUntilFade = lbl_3_data_21B20[0];
        fn_3_14E894();
    }
    if (--g_GameLogic.CountdownUntilFade == 7) {
        changeScene(3, 6);
    }
    if (g_GameLogic.CountdownUntilFade <= 0) {
        fn_3_DE4FC();
        if (g_Minigame.soloMinigameDifficulty <= 2 && g_Minigame.multiPlayerInd == 0) {
            if (g_Minigame.minigameControlStruct[0]._1C[g_Minigame._1908] == 1 && g_Minigame.challenge_minigame_haven_tWonYetIndicator == 0) {
                g_Minigame._1A37 = 1;
            } else {
                g_Minigame._1A37 = 2;
            }
        }
        fn_3_5A6D4(0xE);
        fn_80011578();
        clr(0);
        g_Minigame._1D50 = 0x1E;
        g_Minigame._1D6C = 0;
        g_Minigame._BED = 0;
        MG3520->objs[1].state = 0;
        MG3520->objs[2].state = 0;
        g_Minigame._CAD = 0;
        MG3520->item.state = 0;
    }
}

extern u16 lbl_3_data_81FC[];
extern s32 fn_3_108854(void);
extern void fn_3_2F484(void);
// NONMATCHING 95.8%: saved-register numbering differs (g_Minigame bases kept in other regs)
#if NONMATCHING
// Per-frame update for this minigame.
void fn_3_13B284(void) {
    if (fn_3_108854() != 0) {
        return;
    }
    if (g_Minigame.turnOverStatus == 0) {
        g_Minigame._17C0++;
    }
    if ((u32)g_Minigame._17C4 != 0) {
        g_Minigame._17C4--;
        // countdown beeps during the last 10 seconds
        if ((u32)g_Minigame._17C4 < 600 && (u32)g_Minigame._17C4 != 0 && (u32)g_Minigame._17C4 % 60 == 0) {
            fn_3_90064(lbl_3_data_81FC[0x28]);
        }
    }
    fn_3_13334C();
    fn_3_2F484();
    h133320();
    fn_3_136220();
    fn_3_139CA0();
    fn_3_139808();
    h13974C();
    h139700();
    fn_3_13AA78();
    h136048();
    fn_3_138AA4();
    h136EA4();
    h135924();
    h13AFE4();
}
#endif

#pragma dont_inline off
// .text:0x0013B9C4 size:0x16C mapped:0x8077AA58
void fn_3_13B9C4(void) {
    u32 i;
    fn_3_157570();
    fn_3_DE4FC();
    fn_3_5A6D4(0xE);
    fn_80011578();
    for (i = 0; i < 100; i++) {
        g_Minigame.wallBall_coinsVisibleInd[i] = 0;
    }
    g_Minigame._1D50 = 0x1E;
    g_Minigame._1D6C = 0;
    g_Minigame._BED = 0;
    MG3520->objs[1].state = 0;
    MG3520->objs[2].state = 0;
    g_Minigame._CAD = 0;
    MG3520->item.state = 0;
}

// .text:0x0013BB30 size:0xC4 mapped:0x8077ABC4
// Inline copy for fn_3_13C468, which inlines this function and matches with it.
static inline void h13BB30(void) {
    u8* g;
    CpuSlot3520* q;
    u8 st;
    u32 i;
    f32 v;
    fn_3_F1DC();
    q = MG3520->cpu.slot;
    memset(g_Minigame._1D7C, 0, 0x78);
    g = ((u8*)&g_Minigame);
    for (i = 0; i < 4; i++) {
        st = g[(s32)OFFSET_OF(MiniGameStruct, minigameControlStruct[0].aIStrength[0])];
        q->lastStick = -1;
        if (RandomInt_Game(100) < (s8)lbl_3_data_21B88[st]) {
            v = lbl_3_rodata_35FC;
        } else {
            v = lbl_3_rodata_3600;
        }
        q->radius = v;
        q++;
        g++;
    }
    changeScene(1, 6);
    fn_3_5A6D4(2);
}

// NONMATCHING 94%: only g_Minigame base reg materialization (addi r0 + mr) differs; same as fn_3_1356F8
#if NONMATCHING
void fn_3_13BB30(void) {
    u8* g;
    CpuSlot3520* q;
    u8 st;
    u32 i;
    f32 v;
    fn_3_F1DC();
    q = MG3520->cpu.slot;
    memset(g_Minigame._1D7C, 0, 0x78);
    g = g_Minigame.minigameControlStruct[0].aIStrength;
    for (i = 0; i < 4; i++) {
        st = *g;
        q->lastStick = -1;
        if (RandomInt_Game(100) < (s8)lbl_3_data_21B88[st]) {
            v = lbl_3_rodata_35FC;
        } else {
            v = lbl_3_rodata_3600;
        }
        q->radius = v;
        q++;
        g++;
    }
    changeScene(1, 6);
    fn_3_5A6D4(2);
}
#endif


// .text:0x0013BBF4 size:0xC4 mapped:0x8077AC88
void fn_3_13BBF4(void) {
    switch (g_GameLogic._125) {
    case 0:
        fn_3_10F550(2, lbl_3_data_21278[0]);
        changeScene(1, 6);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 1;
        break;
    case 1:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > lbl_3_data_21278[0] + lbl_3_data_21278[1]) {
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        fn_3_5A6D4(0);
        break;
    }
}

#pragma dont_inline on

// .text:0x0013BCB8 size:0x7AC mapped:0x8077AD4C
static inline void h133200(void) {
    u32 i;
    u32 j;
    u32 idx;
    u8* p;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            idx = fn_800247E4(j, i, 4, 4);
            if (idx < 0x20) {
                p = s_buf;
                p += idx;
                p[2] = 0xFF;
                p[0] = 0xFF;
                p[3] = 0x96;
                p[1] = 0x96;
            } else {
                p = s_buf;
                p += idx;
                p[2] = 0x96;
                p[0] = 0x96;
                p[3] = 0x96;
                p[1] = 0x96;
            }
        }
    }
    GXInitTexObj(s_tex, s_buf, 4, 4, 6, 1, 1, 0);
    GXInitTexObjLOD(s_tex, 1, 1, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    lbl_3_data_26580 = -1;
    s_cnt = 0;
}
extern u8 lbl_3_data_2127C[];
extern u8 lbl_3_data_21984[];
extern f32 lbl_3_rodata_36D0;
extern void fn_3_59A90(void);
extern void fn_3_58870(void);
extern void fn_3_6E24C(s32 player, s32 fielder);
extern void fn_3_169600(void);
extern void fn_3_C39C8(void);
extern void minigamesGXStuff(void);
extern void minigamesSetSomePointers2(void);
// NONMATCHING 93%: unrolled reset loops and saved-register numbering differ
#if NONMATCHING
// Minigame setup (g_GameLogic._125 == 0), then hand over to the next state.
void fn_3_13BCB8(void) {
    s32 i;
    s32 k;
    u32 n;
    if (g_GameLogic._125 != 0) {
        fn_3_5A6D4(5);
        return;
    }
    fn_3_59A90();
    g_GameLogic.secondaryGameMode = 8;
    g_Minigame._17C0 = 0;
    g_Minigame.turnOverStatus = 0;
    g_Minigame._1A37 = 0;
    for (i = 0; i < 4; i++) {
        g_Minigame.miniGameCurrentPoints[i] = 0;
        g_Minigame.miniGameLatestPoints[i] = 0;
        g_Minigame.minigamePoints_current_Latest[i].current = 0;
        g_Minigame.minigamePoints_current_Latest[i].latest = 0;
        g_Minigame.minigameControlStruct[0].fieldOrder[i] = -1;
        g_Minigame.minigameFielderIndex[i] = -1;
        g_Minigame._18FC[i] = -1;
        g_Minigame._1900[i] = -1;
        g_Minigame.minigameControlStruct[0]._24[i] = 0;
    }
    g_Minigame.pointsReqToWin_challenge = 0;
    g_Minigame.minigamePlayerSelectedOrder = -1;
    g_Minigame.rosterID = -1;
    lbl_3_common_bss_34C58._30 = 0;
    if (g_Minigame.multiPlayerInd == 0) {
        u8 ai = lbl_3_data_2127C[g_Minigame.GameMode_MiniGame * 5 + g_Minigame.soloMinigameDifficulty];
        g_Minigame._17C4 = lbl_3_data_21984[g_Minigame.soloMinigameDifficulty] * 60;
        g_Minigame.minigameControlStruct[0].aIStrength[0] = ai;
        g_Minigame.minigameControlStruct[0].aIStrength[1] = ai;
        g_Minigame.minigameControlStruct[0].aIStrength[2] = ai;
        g_Minigame.minigameControlStruct[0].aIStrength[3] = ai;
    } else {
        if (g_Minigame._1A3C != 0) {
            g_Minigame.minigameControlStruct[0].aIStrength[0] = lbl_3_data_2127C[0x23];
            g_Minigame.minigameControlStruct[0].aIStrength[1] = lbl_3_data_2127C[0x23];
            g_Minigame.minigameControlStruct[0].aIStrength[2] = lbl_3_data_2127C[0x23];
            g_Minigame.minigameControlStruct[0].aIStrength[3] = lbl_3_data_2127C[0x23];
        }
        g_Minigame._17C4 = lbl_3_data_21984[4] * 60;
    }
    fn_3_58870();
    // place the active players on their start spots
    k = 0;
    for (i = 0; i < 4; i++) {
        if (g_Minigame.minigameControlStruct[0].characterIndex[i] >= 0) {
            InMemFielderType* f;
            g_Minigame.minigameControlStruct[0].fieldOrder[k] = i;
            g_Minigame.minigameFielderIndex[g_Minigame.minigameControlStruct[0].fieldOrder[k]] = k + 2;
            fn_3_6E24C(i, g_Minigame.minigameFielderIndex[g_Minigame.minigameControlStruct[0].fieldOrder[k]]);
            f = &g_Fielders[g_Minigame.minigameFielderIndex[g_Minigame.minigameControlStruct[0].fieldOrder[k]]];
            g_Minigame.starDashStunType[i] = 0;
            f->minigamePlayer = i;
            f->pos.x = lbl_3_data_2198C[k * 2 + 0];
            f->pos.z = lbl_3_data_2198C[k * 2 + 1];
            f->pos.y = lbl_3_rodata_35D0;
            f->height = lbl_3_rodata_35D0;
            f->_1D2 = 0;
            f->facing = lbl_3_rodata_36D0;
            k++;
        }
    }
    for (i = 0; i < 100; i++) {
        COIN_STATE(i) = 0;
    }
    g_Minigame._1D50 = 30;
    g_Minigame._1D6C = 0;
    g_Minigame._1D54 = 0;
    g_Minigame._B6C._40[0] = 0;
    g_Minigame._72A = 0;
    g_Minigame._1D52 = 600;
    g_Minigame._1D6D = -1;
    g_Minigame._1D72 = 0;
    g_Minigame._1D73 = 0;
    // four spokes, a quarter turn apart
    for (i = 0; i < 4; i++) {
        MG3520->spokes[i].a.y = lbl_3_data_21A48[1];
        MG3520->spokes[i].b.y = lbl_3_data_21A48[1];
        MG3520->spokeAng[i] = i * 0x400;
    }
    for (i = 0; i < 40; i++) {
        MG3520->ents[i]._26 = 0;
        MG3520->ents[i].pos.y = lbl_3_data_21A48[1];
        MG3520->ents[i]._22 = 0;
    }
    if (g_Minigame.multiPlayerInd == 0 && g_Minigame._1A3C == 0) {
        lbl_3_bss_B781 = g_Minigame.soloMinigameDifficulty;
        lbl_3_bss_B780 = lbl_3_data_21A88[g_Minigame.soloMinigameDifficulty];
    } else {
        lbl_3_bss_B781 = 3;
        lbl_3_bss_B780 = 4;
    }
    for (i = 0; i < 4; i++) {
        Mg3520Obj* o = &MG3520->objs[i];
        memset(o, 0, sizeof(Vec));
        memset(&o->_0C, 0, sizeof(Vec));
        memset(&o->_18, 0, sizeof(Vec));
        memset(&o->_24, 0, sizeof(Vec));
        o->state = 0;
    }
    // obstacles: first drop time and angular sector
    for (i = 0; i < lbl_3_bss_B780; i++) {
        Mg3520Obj* o = &MG3520->objs[i];
        s16* row = lbl_3_data_21A90 + g_Minigame.soloMinigameDifficulty * 8;
        s32 r = random_fn_3_9EE24((row[1] - row[0]) * 60);
        o->_38 = row[0] * 60 + r;
        o->_30 = (f32)((360 / lbl_3_bss_B780) * i);
        o->_34 = o->_30 + (f32)(360 / lbl_3_data_21A88[lbl_3_bss_B781]);
    }
    g_Minigame._1D78 = 0;
    g_Minigame._1D79 = 0;
    g_Minigame._1D7A = 0;
    g_Minigame._1D7B = 0;
    g_Minigame._1D76 = 0;
    g_Minigame._CCC = lbl_3_data_21B10[0];
    g_Minigame._CCE[0] = 0;
    ((s8*)g_Minigame.playerIDWithPowerup)[0] = -1;
    h133200();
    fn_3_169600();
    minigamesSetSomePointers();
    minigamesGXStuff();
    minigamesSetSomePointers2();
    fn_3_C39C8();
    g_GameLogic._125++;
}
#endif

// .text:0x0013C464 size:0x4 mapped:0x8077B4F8
void fn_3_13C464(void) {
    return;
}

// .text:0x0013C468 size:0x328 mapped:0x8077B4FC
void fn_3_13C468(void) {
    switch (g_GameLogic.gameStatus) {
    case 4:
        fn_3_13BCB8();
        break;
    case 0x1A:
        fn_3_13BBF4();
        break;
    case 0:
        h13BB30();
        break;
    case 2:
        fn_3_13B284();
        break;
    case 0xF:
        fn_3_13B9C4();
        break;
    }
    if (lbl_3_common_bss_34C58._30 != 0) {
        lbl_3_common_bss_34C58._30 -= 1;
    }
}


#pragma dont_inline off
