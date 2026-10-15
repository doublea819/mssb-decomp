#ifdef TARGET_PC
extern void port_trace_value(const char* tag, int value);
#define MGTRACE(tag, v) port_trace_value(tag, (int)(v))
#else
#define MGTRACE(tag, v) ((void)0)
#endif
#include "game/rep_34B0.h"
#define REP_HEADER_FN repHeader_34B0
#include "header_rep_inline.h"

#include "game/UnknownHomes_Game.h"
#include "musyx/musyx.h"
#include "main/file_8001FE00.h"         // SceneFade lbl_8037169C
#include "static/GameSettings.h"
#include "game/auto_00_001608F0_text.h"
#include "game/auto_00_001658F0_text.h" // StarChanceState

extern u8 lbl_800EFBA4[];
extern GameScores g_Scores;
#include "game/auto_00_00097144_text.h" // GameHudFlags lbl_3_common_bss_32724

extern void setInMemBatterConstants(s32);
extern void fn_3_F1DC(void);
extern void ballPhysica(void);
extern s32 fn_3_108854(void);
extern void fn_3_75560(void);
extern void fn_3_12DB80(void);
extern void atBat_batter(void);
extern void fn_3_8A958(void);
extern void fn_3_59A90(void);
extern void fn_3_14CA00(void);
extern u8 lbl_3_data_2127C[][5]; // [minigame][difficulty]: CPU strength
extern s16 lbl_3_data_21790[];   // [difficulty]: points needed to win
extern void fn_3_751B4(void);
extern void setDefaultInMemBatter(void);
extern void fn_3_8913C(void);
extern void fn_3_58870(void);
extern void fn_3_BF1AC(void);
extern void fn_3_BF158(void);
extern void* memset(void*, int, size_t);

extern void fn_3_5A6D4(u8 status);
extern f32 lbl_3_data_21770[];         // barrel physics constants
extern VecXYZ lbl_3_data_216BC[15];    // barrel home positions
extern int random_fn_3_9EE24(int max);
extern f32 lbl_3_rodata_351C[];
extern f32 lbl_3_rodata_3518;
extern void fn_8004C108(f32*, s32);
extern u32 fn_3_90064(s32 id);
extern u8 lbl_3_data_18C48[];
extern s32 fn_3_6C938(s32, s32);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern u8 lbl_3_data_21798[];
extern u8 lbl_803CBC3C[];
extern u8 lbl_3_common_bss_32234[];
extern void fn_3_F578(void);
extern void fn_3_753E8(s32);
extern void fn_3_6EBB4(s32);
extern void setBatterContactConstants(void);
extern s32 someAnimationIndFunction(void);
extern void fn_3_10F550(s32, s32);
extern void fn_3_10AD48(void);
extern s16 lbl_3_data_217A4[];
extern void fn_3_DE4FC(void);
extern s16 lbl_3_data_21788[];
extern StarChanceState lbl_3_common_bss_37400;

// .text:0x0012E8FC size:0x214 mapped:0x8076D990
void fn_3_12E8FC(void) {
    s32 i;
    s32 have = 0;
    s32 pick;

    if (g_Minigame.barrelBatterChargeMeter >= lbl_3_data_21788[2]) {
        for (i = 0, pick = 0; i < 15; i++) {
            if (g_Minigame.barrels[i].barrelState == 0) {
                pick++;
            }
        }
        pick = random_fn_3_9EE24(pick);
        g_Minigame.barrelBatterChargeMeter = 0;
        have = 1;
    }
    for (i = 0; i < 15; i++) {
        if (g_Minigame.barrels[i].barrelState == 0) {
            g_Minigame.barrels[i].barrelState = 1;
            g_Minigame.barrels[i].animationCounter = 0;
            g_Minigame.barrels[i].currentPos.x = lbl_3_data_216BC[i].x;
            g_Minigame.barrels[i].currentPos.y = lbl_3_data_216BC[i].y;
            g_Minigame.barrels[i].currentPos.z = lbl_3_data_216BC[i].z;
            g_Minigame.barrels[i].currentPos.y = g_Minigame.barrels[i].currentPos.y + lbl_3_data_21770[0];
            g_Minigame.barrels[i].currentPos.y = g_Minigame.barrels[i].currentPos.y + ((f64)((i % 3) * 10) - (f64)(random_fn_3_9EE24(0x65) * 5) / 100.0);
            g_Minigame.barrels[i].barrelColour = random_fn_3_9EE24(3);
            if (have != 0) {
                if (pick == 0) {
                    pick = -1;
                    g_Minigame.barrels[i].barrelColour = 3;
                    g_Minigame.bB_bombBarrelID = i;
                } else if (pick > 0) {
                    pick--;
                }
            }
        }
    }
}

// .text:0x0012EB10 size:0x270 mapped:0x8076DBA4
// Drop the barrels above blown-up ones (state 4) down by one slot in each row.
void fn_3_12EB10(void) {
    s32 i; // unused copy of the barrel index (kept: the original keeps it too)
    s32 row;
    s32 j;
    s32 k;
    s32 n;

    for (row = 0; row < 5; row++) {
        for (j = 0, i = row * 3; j < 2; j++, i++) {
            for (;;) {
                n = row * 3 + j;
                if (g_Minigame.barrels[n].barrelState != 4) {
                    break;
                }
                for (k = j + 1; k < 3; k++) {
                    n = k + row * 3;
                    g_Minigame.barrels[n - 1].barrelState = g_Minigame.barrels[n].barrelState;
                    g_Minigame.barrels[n - 1].barrelColour = g_Minigame.barrels[n].barrelColour;
                    g_Minigame.barrels[n - 1].currentPos.x = g_Minigame.barrels[n].currentPos.x;
                    g_Minigame.barrels[n - 1].currentPos.y = g_Minigame.barrels[n].currentPos.y;
                    g_Minigame.barrels[n - 1].currentPos.z = g_Minigame.barrels[n].currentPos.z;
                    g_Minigame.barrels[n].barrelState = 0;
                }
            }
        }
    }
    for (row = 0; row < 5; row++) {
        u8* s = &g_Minigame.barrels[row * 3 + 2].barrelState;
        if (*s == 4) {
            *s = 0;
        }
    }
}

// .text:0x0012ED80 size:0xE8 mapped:0x8076DE14
u8 fn_3_12ED80(void) {
    s32 i;
    for (i = 1; i < 15; i += 3) {
        if (g_Minigame.barrels[i].replacingBarrelInd != 0) {
            return 0;
        }
        if (g_Minigame.barrels[i + 1].replacingBarrelInd != 0) {
            return 0;
        }
    }
    return 1;
}

// .text:0x0012EE68 size:0x13C mapped:0x8076DEFC
void fn_3_12EE68(s32 i) {
    BB_barrelStruct* a;
    BB_barrelStruct* b;
    u8 k;

    a = &g_Minigame.barrels[i];
    if (i % 3 == 2) {
        return;
    }
    b = &g_Minigame.barrels[i + 1];
    if (b->barrelState == 4) {
        return;
    }
    if (b->barrelState == 3 && b->currentPos.y - a->currentPos.y > 0.3 + lbl_3_data_21770[3]) {
        return;
    }
    b->replacingBarrelInd = 1;
    b->velo_bounceUpOnBlowUp = lbl_3_data_21770[4];
    if ((i + 1) % 3 == 1) {
        b->_28 = lbl_3_data_216BC[i].y;
    } else {
        k = 0;
        k |= (g_Minigame.barrels[i - 1].barrelState == 2);
        k |= (g_Minigame.barrels[i].barrelState == 2);
        b->_28 = lbl_3_data_216BC[k].y;
    }
}

// .text:0x0012EFA4 size:0x2E8 mapped:0x8076E038
// Move a barrel that is dropping into a freed slot (replacingBarrelInd set).
void fn_3_12EFA4(s32 i) {
    BB_barrelStruct* a = &g_Minigame.barrels[i];
    BB_barrelStruct* b;
    f32 v[3];

    a->currentPos.y += a->velo_bounceUpOnBlowUp;
    if (a->velo_bounceUpOnBlowUp > lbl_3_rodata_3518 && i % 3 == 1) {
        b = &g_Minigame.barrels[i + 1];
        if (b->barrelState != 4 && b->replacingBarrelInd == 0) {
            fn_3_12EE68(i);
        }
        if (b->currentPos.y - a->currentPos.y < lbl_3_data_21770[3]) {
            a->velo_bounceUpOnBlowUp -= lbl_3_data_21770[5];
        }
    }
    a->velo_bounceUpOnBlowUp -= lbl_3_data_21770[5];
    if (a->velo_bounceUpOnBlowUp > lbl_3_rodata_3518 && i % 3 == 2) {
        b = &g_Minigame.barrels[i - 1];
        if (a->currentPos.y - b->currentPos.y < lbl_3_data_21770[3]) {
            a->velo_bounceUpOnBlowUp += lbl_3_data_21770[5];
        }
    }
    if (a->currentPos.y < a->_28) {
        a->currentPos.y = a->_28;
        a->velo_bounceUpOnBlowUp = lbl_3_rodata_3518;
        a->replacingBarrelInd = 0;
        if (a->barrelState != 4) {
            v[1] = a->currentPos.y;
            v[2] = a->currentPos.z;
            v[0] = a->currentPos.x;
            v[2] = v[2] - lbl_3_rodata_351C[0];
            v[1] = -a->_28;
            if (lbl_3_rodata_3518 == a->_28) {
                fn_8004C108(v, 1);
                fn_3_90064(0x2E4);
            } else {
                fn_8004C108(v, 0);
                fn_3_90064(0x2E5);
            }
        }
    }
}

// .text:0x0012F28C size:0x198 mapped:0x8076E320
void fn_3_12F28C(s32 i) {
    BB_barrelStruct* b;

    b = &g_Minigame.barrels[i];
    if (b->animationCounter >= b->delayUntilBlownUp) {
        b->barrelState = 4;
        b->animationCounter = 0;
        fn_3_12EE68(i);
        fn_3_6C854(g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.rosterID], 0);
    }
}

// .text:0x0012F424 size:0x200 mapped:0x8076E4B8
// Barrel i was blown up: neighbouring standing barrels of the same colour
// (or all of them when force is set) start blowing up after `delay` frames.
void fn_3_12F424(s32 i, s32 delay, s32 force) {
    s32 colour = g_Minigame.barrels[i].barrelColour;
    s32 n;

    if (i % 3 != 2) {
        n = i + 1;
        if (g_Minigame.barrels[n].barrelState == 2 && n != g_Minigame.bB_bombBarrelID &&
            (g_Minigame.barrels[n].barrelColour == colour || force != 0)) {
            g_Minigame.barrels[n].barrelState = 3;
            g_Minigame.barrels[n].animationCounter = 0;
            g_Minigame.barrels[n].delayUntilBlownUp = delay;
        }
    }
    if (i - (i / 3) * 3 != 0) {
        n = i - 1;
        if (g_Minigame.barrels[n].barrelState == 2 && n != g_Minigame.bB_bombBarrelID &&
            (g_Minigame.barrels[n].barrelColour == colour || force != 0)) {
            g_Minigame.barrels[n].barrelState = 3;
            g_Minigame.barrels[n].animationCounter = 0;
            g_Minigame.barrels[n].delayUntilBlownUp = delay;
        }
    }
    if (i / 3 > 0) {
        n = i - 3;
        if (g_Minigame.barrels[n].barrelState == 2 && n != g_Minigame.bB_bombBarrelID &&
            (g_Minigame.barrels[n].barrelColour == colour || force != 0)) {
            g_Minigame.barrels[n].barrelState = 3;
            g_Minigame.barrels[n].animationCounter = 0;
            g_Minigame.barrels[n].delayUntilBlownUp = delay;
        }
    }
    if (i / 3 < 4) {
        n = i + 3;
        if (g_Minigame.barrels[n].barrelState == 2 && n != g_Minigame.bB_bombBarrelID &&
            (g_Minigame.barrels[n].barrelColour == colour || force != 0)) {
            g_Minigame.barrels[n].barrelState = 3;
            g_Minigame.barrels[n].animationCounter = 0;
            g_Minigame.barrels[n].delayUntilBlownUp = delay;
        }
    }
}

// .text:0x0012F624 size:0x3B0 mapped:0x8076E6B8
// Barrel Batter: after the hit, find the barrel the ball struck, chain-blow up
// matching neighbours and award points.
// NONMATCHING 99.7%: hit-barrel id / lbl_3_data_21788[0] get r8/r7 instead of r9/r8.
#if NONMATCHING
void fn_3_12F624(void) {
    s32 done[15];
    s32 row;
    s32 col;
    s32 i;
    s32 any;
    s32 delay;
    s32 pts;
    s32 id;

    if (g_Ball.framesSinceHit > 0 && g_Minigame.barrelBatter_scoreCalculatedInd == 0) {
        if (g_Ball.AtBat_Contact_BallPos.z < lbl_3_data_216BC[0].z - lbl_3_data_21770[2]) {
            return;
        }
        if (g_Batter.contactType < 1 || g_Batter.contactType > 3) {
            return;
        }
        for (row = 0; row < 3; row++) {
            if (g_Ball.AtBat_Contact_BallPos.y < lbl_3_data_21770[3] + lbl_3_data_216BC[row].y) {
                break;
            }
        }
        if (row < 3 && !(g_Ball.AtBat_Contact_BallPos.x < lbl_3_data_216BC[0].x - lbl_3_data_21770[2])) {
            for (col = 0; col < 15; col += 3) {
                if (g_Ball.AtBat_Contact_BallPos.x < lbl_3_data_21770[2] + lbl_3_data_216BC[col].x) {
                    break;
                }
            }
            if (col < 15) {
                g_Minigame.barrelBatter_hitBarrelID = col + row;
                for (row = 0; row < 15; row++) {
                    done[row] = 0;
                }
                id = g_Minigame.barrelBatter_hitBarrelID;
                g_Minigame.barrels[id].barrelState = 3;
                g_Minigame.barrels[id].animationCounter = 0;
                g_Minigame.barrels[id].delayUntilBlownUp = lbl_3_data_21788[0];
                delay = lbl_3_data_21788[0] + lbl_3_data_21788[1];
                if (g_Minigame.bB_bombBarrelID == id && g_Minigame.barrels[id].barrelColour == 3) {
                    g_Minigame.bB_bombBarrelHitInd = 1;
                }
                for (;;) {
                    any = 0;
                    for (i = 0; i < 15; i++) {
                        if (g_Minigame.barrels[i].barrelState == 3 && g_Minigame.barrels[i].delayUntilBlownUp != delay &&
                            done[i] == 0) {
                            if (g_Minigame.bB_bombBarrelHitInd != 0) {
                                fn_3_12F424(i, delay, 1);
                            } else {
                                fn_3_12F424(i, delay, 0);
                            }
                            done[i] = 1;
                            any = 1;
                            g_Minigame.barrelBatter_barrelsHit++;
                        }
                    }
                    if (any == 0) {
                        break;
                    }
                    delay += lbl_3_data_21788[1];
                }
                if (g_Minigame.bB_bombBarrelHitInd == 0 && g_Minigame.barrelBatter_barrelsHit >= 2) {
                    g_Minigame.barrelBatterChargeMeter += g_Minigame.barrelBatter_barrelsHit - 1;
                }
                if (g_Minigame.barrelBatter_barrelsHit <= 1) {
                    pts = lbl_3_data_217A4[5] * g_Minigame.barrelBatter_barrelsHit;
                } else {
                    pts = g_Minigame.barrelBatter_barrelsHit * ((g_Minigame.barrelBatter_barrelsHit - 1) * lbl_3_data_217A4[5]);
                }
                g_Minigame.miniGameCurrentPoints[g_Minigame.rosterID] += pts;
                g_Minigame._1DF4[0] = pts;
                if (g_d_GameSettings.exhibitionMatchInd == 0 && g_Minigame.rosterID == lbl_3_common_bss_37400.humanPlayer) {
                    fn_3_1608F0(2, pts, g_Minigame.barrelBatter_barrelsHit);
                }
            }
        }
        g_Minigame.barrelBatter_scoreCalculatedInd = 1;
    }
}
#endif

// Barrel falling into place: same as fn_3_12F9D4 but with the float loads in x/y/z order
// (what the inlined copies in fn_3_1323CC, fn_3_1307D0 and friends use).
static inline void mgStep_1323CC(s32 idx) {
    f32 v[3];
    BB_barrelStruct* a = &g_Minigame.barrels[idx];
    a->currentPos.y += lbl_3_data_21770[1];
    if (a->currentPos.y < a->desiredPos.y) {
        a->currentPos.y = a->desiredPos.y;
        if (a->posAtStartOfTurn.y != a->desiredPos.y) {
            f32 x = a->currentPos.x;
            f32 y = a->currentPos.y;
            f32 z = a->currentPos.z;
            v[1] = y;
            v[0] = x;
            v[2] = z;
            v[1] = -v[1];
            v[2] = v[2] - lbl_3_rodata_351C[0];
            if (y <= lbl_3_rodata_3518) {
                fn_8004C108(v, 1);
                fn_3_90064(0x2E4);
            } else {
                fn_8004C108(v, 0);
                fn_3_90064(0x2E5);
            }
        }
        a->barrelState = 2;
    }
}

// .text:0x0012F9D4 size:0xF0 mapped:0x8076EA68
void fn_3_12F9D4(s32 idx) {
    f32 v[3];
    BB_barrelStruct* a = &g_Minigame.barrels[idx];
    a->currentPos.y += lbl_3_data_21770[1];
    if (a->currentPos.y < a->desiredPos.y) {
        a->currentPos.y = a->desiredPos.y;
        if (a->posAtStartOfTurn.y != a->desiredPos.y) {
            f32 z = a->currentPos.z;
            f32 y = a->currentPos.y;
            f32 x = a->currentPos.x;
            v[1] = y;
            v[2] = z;
            v[0] = x;
            v[1] = -v[1];
            v[2] = v[2] - lbl_3_rodata_351C[0];
            if (y <= lbl_3_rodata_3518) {
                fn_8004C108(v, 1);
                fn_3_90064(0x2E4);
            } else {
                fn_8004C108(v, 0);
                fn_3_90064(0x2E5);
            }
        }
        a->barrelState = 2;
    }
}

// .text:0x0012FAC4 size:0x2A8 mapped:0x8076EB58
void fn_3_12FAC4(void) {
    BB_barrelStruct* p;
    BB_barrelStruct* a;
    s32 i;
    f32 v[3];

    fn_3_12F624();
    for (i = 0; i < 15; i++) {
        p = &g_Minigame.barrels[i];
        if (p->animationCounter < 0x7FFE) {
            p->animationCounter += 1;
        } else {
            p->animationCounter = 0x7FFF;
        }
        if (p->barrelState == 1) {
            a = &g_Minigame.barrels[i];
            a->currentPos.y += lbl_3_data_21770[1];
            if (a->currentPos.y < a->desiredPos.y) {
                a->currentPos.y = a->desiredPos.y;
                if (a->posAtStartOfTurn.y != a->desiredPos.y) {
                    f32 z, y, x;
                    z = a->currentPos.z;
                    y = a->currentPos.y;
                    x = a->currentPos.x;
                    v[1] = y;
                    v[2] = z;
                    v[0] = x;
                    v[1] = -v[1];
                    v[2] = v[2] - lbl_3_rodata_351C[0];
                    if (y <= lbl_3_rodata_3518) {
                        fn_8004C108(v, 1);
                        fn_3_90064(0x2E4);
                    } else {
                        fn_8004C108(v, 0);
                        fn_3_90064(0x2E5);
                    }
                }
                a->barrelState = 2;
            }
        }
        if (p->barrelState == 3) {
            fn_3_12F28C(i);
        }
        if (p->replacingBarrelInd != 0) {
            fn_3_12EFA4(i);
        }
    }
}

// .text:0x0012FD6C size:0x118 mapped:0x8076EE00
void fn_3_12FD6C(void) {
    s32 i;
    for (i = 0; i < 15; i++) {
        if (g_Minigame.barrels[i].barrelState != 0) {
            g_Minigame.barrels[i].posAtStartOfTurn.x = g_Minigame.barrels[i].currentPos.x;
            g_Minigame.barrels[i].posAtStartOfTurn.y = g_Minigame.barrels[i].currentPos.y;
            g_Minigame.barrels[i].posAtStartOfTurn.z = g_Minigame.barrels[i].currentPos.z;
            g_Minigame.barrels[i].barrelState = 1;
        }
        g_Minigame.barrels[i].animationCounter = 0;
    }
}

// .text:0x0012FE84 size:0x150 mapped:0x8076EF18
void fn_3_12FE84(void) {
    s32 i;
    for (i = 0; i < 15; i++) {
        g_Minigame.barrels[i].barrelState = 1;
        g_Minigame.barrels[i].animationCounter = 0;
        g_Minigame.barrels[i].replacingBarrelInd = 0;
        g_Minigame.barrels[i].desiredPos.x = lbl_3_data_216BC[i].x;
        g_Minigame.barrels[i].desiredPos.y = lbl_3_data_216BC[i].y;
        g_Minigame.barrels[i].desiredPos.z = lbl_3_data_216BC[i].z;
        g_Minigame.barrels[i].currentPos.x = lbl_3_data_216BC[i].x;
        g_Minigame.barrels[i].currentPos.y = lbl_3_data_216BC[i].y;
        g_Minigame.barrels[i].currentPos.z = lbl_3_data_216BC[i].z;
        g_Minigame.barrels[i].currentPos.y = g_Minigame.barrels[i].currentPos.y + lbl_3_data_21770[0];
        g_Minigame.barrels[i].currentPos.y = g_Minigame.barrels[i].currentPos.y + ((f64)((i % 3) * 10) - (f64)(random_fn_3_9EE24(0x65) * 5) / 100.0);
        g_Minigame.barrels[i].barrelColour = random_fn_3_9EE24(3);
    }
}

// .text:0x0012FFD4 size:0x2B4 mapped:0x8076F068
// NONMATCHING 98%: inherits the fn_3_12EB10 difference (inlined in both).
#if NONMATCHING
void fn_3_12FFD4(void) {
    g_Minigame.bB_bombBarrelID = -1;
    fn_3_12EB10();
    fn_3_12E8FC();
    if (g_Minigame.pointsTargetReachedInd != 0) {
        fn_3_5A6D4(8);
    } else {
        fn_3_5A6D4(0);
    }
}
#endif

// .text:0x00130288 size:0x548 mapped:0x8076F31C
// Barrel Batter: end-of-pitch bookkeeping; once all barrels have settled,
// refill the rack and move on to the next pitch or end the turn.
// NONMATCHING 99%: inherits the fn_3_12EB10 difference (fn_3_12FFD4 and fn_3_12EB10 are inlined in both).
#if NONMATCHING
void fn_3_130288(void) {
    if (g_Minigame.turnOverStatus == 0 && g_Ball.framesSinceHit >= lbl_3_data_217A4[4]) {
        g_Minigame.turnOverStatus = 1;
        if (g_Minigame.multiPlayerInd == 0 && g_Minigame.soloMinigameDifficulty <= 2 &&
            g_Minigame.miniGameCurrentPoints[g_Minigame.rosterID] >= g_Minigame.pointsReqToWin_challenge) {
            g_Minigame.pointsTargetReachedInd = 2;
            g_Minigame._1A37 = 1;
            g_Minigame.challenge_minigame_haven_tWonYetIndicator = 0;
            fn_3_10F550(1, lbl_3_data_217A4[10]);
        }
        if (g_Minigame.bB_bombBarrelHitInd != 0) {
            g_Minigame.bB_pitchesRemainingInTurn += lbl_3_data_21798[g_Minigame.multiPlayerInd + 6];
        }
        if (g_Minigame.bB_pitchesRemainingInTurn == 0) {
            g_Minigame.pointsTargetReachedInd = 2;
        }
    }
    if (g_Minigame.turnOverStatus != 0) {
        if (g_Minigame.turnOverStatus == 1) {
            g_Minigame.turnOverStatus = 2;
            g_GameLogic.CountdownUntilFade = lbl_3_data_217A4[1];
        }
        if (--g_GameLogic.CountdownUntilFade <= 0) {
            if (fn_3_12ED80()) {
                fn_3_12FFD4();
            }
        }
        if (g_Minigame.pointsTargetReachedInd != 0
            && (g_Minigame.multiPlayerInd == 0
                || (g_Minigame.multiPlayerInd != 0 && g_Minigame.turnNumberWithinRound + 1 >= g_Minigame.miniGameNumberOfParticipants
                    && g_Scores.inning >= g_Scores.maxInnings))
            && g_Minigame._1A37 == 0 && g_GameLogic.CountdownUntilFade == 1) {
            sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
        }
    }
}
#endif

// .text:0x001307D0 size:0x2B0 mapped:0x8076F864
// NONMATCHING 99%: registers only; the original gives i/b/base/table r29/r28/r27/r26,
// ours r26/r27/r29/r28 (the barrel step and fn_3_12F28C are inlined in both).
#if NONMATCHING
void fn_3_1307D0(void) {
    BB_barrelStruct* b;
    s32 i;

    ballPhysica();
    fn_3_12F624();
    for (i = 0; i < 15; i++) {
        b = &g_Minigame.barrels[i];
        if (b->animationCounter < 0x7FFE) {
            b->animationCounter += 1;
        } else {
            b->animationCounter = 0x7FFF;
        }
        if (b->barrelState == 1) {
            mgStep_1323CC(i);
        }
        if (b->barrelState == 3) {
            fn_3_12F28C(i);
        }
        if (b->replacingBarrelInd != 0) {
            fn_3_12EFA4(i);
        }
    }
    ((void (*)(void))fn_3_130288)(); // a call in the original (not inlined)
}
#endif

// .text:0x00130A80 size:0x4C mapped:0x8076FB14
void fn_3_130A80(void) {
    g_Minigame.bB_bombBarrelID = -1;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;
    fn_3_5A6D4(8);
}

// .text:0x00130ACC size:0x1A0 mapped:0x8076FB60
void fn_3_130ACC(void) {
    MGTRACE("bb.ballsLeft", g_Minigame.bB_pitchesRemainingInTurn);
    MGTRACE("bb.pitcherState", g_Pitcher.pitcherActionState);
    MGTRACE("bb.turnOver", g_Minigame.turnOverStatus);
    if (g_Minigame.turnOverStatus == 0) {
        if (g_Pitcher.pitcherActionState == 4) {
            if (g_Minigame.bB_pitchesRemainingInTurn == 0) {
                g_Minigame.turnOverStatus = 1;
                g_Minigame.pointsTargetReachedInd = 2;
            }
            g_Minigame.bB_bombBarrelHitInd = 0;
            g_Minigame.bB_bombBarrelID = -1;
        }
        return;
    }
    if (g_Minigame.turnOverStatus == 1) {
        g_Minigame.turnOverStatus = 2;
        g_GameLogic.CountdownUntilFade = lbl_3_data_217A4[0];
    }
    g_GameLogic.CountdownUntilFade -= 1;
    if (g_Minigame.pointsTargetReachedInd != 0) {
        if (g_GameLogic.CountdownUntilFade <= 0) {
            fn_3_130A80();
        }
    } else if (g_GameLogic.CountdownUntilFade <= 0) {
        fn_3_5A6D4(0);
    }
    if (g_Minigame.pointsTargetReachedInd != 0
        && (g_Minigame.multiPlayerInd == 0
            || (g_Minigame.multiPlayerInd != 0 && g_Minigame.turnNumberWithinRound + 1 >= g_Minigame.miniGameNumberOfParticipants
                && g_Scores.inning >= g_Scores.maxInnings))
        && g_Minigame._1A37 == 0 && g_GameLogic.CountdownUntilFade == 1) {
        sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
    }
}

// .text:0x00130C6C size:0x4A8 mapped:0x8076FD00
// Barrel Batter: per-frame update while a pitch is in play.
// NONMATCHING 99%: registers only in the barrel loop (as fn_3_1307D0); fn_3_130ACC is inlined in both.
#if NONMATCHING
void fn_3_130C6C(void) {
    BB_barrelStruct* b;
    s32 i;
    s8 p;

    if (g_Minigame.turnOverStatus == 0) {
        if (fn_3_108854() != 0) {
            return;
        }
        if (g_Minigame.miniGameTurnCounter != 0 || g_GameLogic.FrameCountOfCurrentPitch >= lbl_3_data_217A4[8]) {
            fn_3_75560();
        }
        fn_3_12DB80();
        atBat_batter();
        p = 0;
        do {
            g_Minigame._1DBC[p] = 0;
            p++;
        } while (p < 4);
        fn_3_8A958();
        fn_3_12F624();
        for (i = 0; i < 15; i++) {
            b = &g_Minigame.barrels[i];
            if (b->animationCounter < 0x7FFE) {
                b->animationCounter += 1;
            } else {
                b->animationCounter = 0x7FFF;
            }
            if (b->barrelState == 1) {
                mgStep_1323CC(i);
            }
            if (b->barrelState == 3) {
                fn_3_12F28C(i);
            }
            if (b->replacingBarrelInd != 0) {
                fn_3_12EFA4(i);
            }
        }
    }
    fn_3_130ACC();
}
#endif

// .text:0x00131114 size:0x88 mapped:0x807701A8
void fn_3_131114(void) {
    setInMemBatterConstants(g_Minigame.rosterID);
    fn_3_F1DC();
    fn_3_751B4();
    setDefaultInMemBatter();
    fn_3_8913C();
    fn_3_58870();
    memset(g_Minigame._1D7C, 0, 0x78);
    fn_3_BF1AC();
    fn_3_BF158();
    g_FieldingLogic._0AE = 0;
    unkSimulationRelatedStruct._05 = 0;
    unkSimulationRelatedStruct._06 = 4;
}

// .text:0x0013119C size:0xF0 mapped:0x80770230
void fn_3_13119C(void) {
    GameControlsStruct* gl = &g_GameLogic;
    switch (gl->_125) {
    case 0:
        changeScene(1, 6);
        gl->_125 = 1;
        break;
    case 1: {
        s32 t = gl->FrameCountOfCurrentPitch;
        if (t >= *(s16*)(lbl_3_data_18C48 + 4) ||
            (t >= *(s16*)(lbl_3_data_18C48 + 2) && fn_3_6C938(1, 0x1100) != 0)) {
            changeScene(3, 6);
            gl->_125 = 2;
        }
        break;
    }
    case 2:
        if (lbl_8037169C._13 != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            gl->_125 = 3;
        }
        break;
    case 3:
        fn_3_5A6D4(7);
        break;
    }
}

// .text:0x0013128C size:0x48 mapped:0x80770320
void fn_3_13128C(void) {
    if (g_Scores.inning >= g_Scores.maxInnings) {
        fn_3_5A6D4(0xF);
    } else {
        fn_3_5A6D4(6);
    }
}

// .text:0x001312D4 size:0x26C mapped:0x80770368
void fn_3_1312D4(void) {
    fn_3_DE4FC();
    fn_3_5A6D4(0xE);
    fn_3_12FE84();
    fn_3_12FD6C();
}

// .text:0x00131540 size:0x748 mapped:0x807705D4
// Barrel Batter: end of a turn (barrels keep settling while the scene fades).
// NONMATCHING 99%: registers only (fn_3_12FD6C, fn_3_1312D4 and the barrel loop are inlined in both).
#if NONMATCHING
void fn_3_131540(void) {
    BB_barrelStruct* b;
    s32 i;

    switch (g_GameLogic._125) {
    case 0:
        fn_3_12FD6C();
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_Minigame.turnNumberWithinRound += 1;
        g_GameLogic._125 += 1;
        break;
    case 1:
        if (g_Minigame._1A37 == 1) {
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy >= lbl_3_data_217A4[3]) {
                g_GameLogic._125 += 1;
            }
        } else if (g_GameLogic.FrameCountOfCurrentAtBat_Copy >= lbl_3_data_217A4[2]) {
            g_GameLogic._125 += 1;
        }
        break;
    case 2:
        changeScene(3, 6);
        g_GameLogic._125 += 1;
        break;
    case 3:
        if (lbl_8037169C._13 != 0) {
            if (g_Minigame.multiPlayerInd != 0) {
                if (g_Minigame.turnNumberWithinRound < g_Minigame.miniGameNumberOfParticipants) {
                    fn_3_5A6D4(7);
                } else {
                    fn_3_5A6D4(0x19);
                }
            } else {
                fn_3_1312D4();
            }
            fn_3_14CA00();
            lbl_3_common_bss_32724._B7 = 1;
        }
        break;
    }
    fn_3_12F624();
    for (i = 0; i < 15; i++) {
        b = &g_Minigame.barrels[i];
        if (b->animationCounter < 0x7FFE) {
            b->animationCounter += 1;
        } else {
            b->animationCounter = 0x7FFF;
        }
        if (b->barrelState == 1) {
            mgStep_1323CC(i);
        }
        if (b->barrelState == 3) {
            fn_3_12F28C(i);
        }
        if (b->replacingBarrelInd != 0) {
            fn_3_12EFA4(i);
        }
    }
}
#endif

// .text:0x00131C88 size:0x23C mapped:0x80770D1C
void fn_3_131C88(void) {
    fn_3_131114();
    fn_3_12FD6C();

    g_Minigame._18A0 = 0;
    g_Minigame.turnOverStatus = 0;
    g_Minigame.barrelBatter_scoreCalculatedInd = 0;
    g_Minigame.barrelBatter_hitBarrelID = -1;
    g_Minigame.barrelBatter_barrelsHit = 0;
    g_Minigame.bB_bombBarrelHitInd = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_Ball.framesSinceHit = -1;
    g_Batter.swingInd = 0;
    g_Batter.framesSinceStartOfSwing = 0;
    g_Pitcher.windupCountdownUntilBallReleased = lbl_3_data_217A4[7];
    if (g_GameLogic.pre_PostMiniGameInd != 0) {
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.hudElementLoadingInd = 1;
    } else {
        g_GameLogic.minigameLastTurnSuccessInd = 0;
    }
    g_GameLogic.pre_PostMiniGameInd = 0;
    changeScene(1, 6);
    fn_3_5A6D4(1);
}

// .text:0x00131EC4 size:0x138 mapped:0x80770F58
void fn_3_131EC4(void) {
    GameControlsStruct* gl = &g_GameLogic;
    MiniGameStruct* mg;
    switch (gl->_125) {
    case 0:
        mg = &g_Minigame;
        mg->rosterID = mg->minigameControlStruct[0].turnOrder[mg->turnNumberWithinRound];
        gl->pre_PostMiniGameInd = 1;
        mg->miniGameTurnCounter = 0;
        mg->pointsTargetReachedInd = 0;
        if (mg->multiPlayerInd == 0) {
            mg->bB_pitchesRemainingInTurn = lbl_3_data_21798[mg->soloMinigameDifficulty];
        } else {
            mg->bB_pitchesRemainingInTurn = lbl_3_data_21798[4];
        }
        fn_3_F578();
        fn_3_753E8(0);
        fn_3_6EBB4(-1);
        setBatterContactConstants();
        setInMemBatterConstants(mg->rosterID);
        lbl_803CBC3C[2] = 0;
        gl->_125 += 1;
        break;
    case 1:
        if (someAnimationIndFunction() != 0) {
            lbl_3_common_bss_32234[1] = 1;
            gl->_125 += 1;
        }
        break;
    default:
        lbl_3_common_bss_32724._B6 = 1;
        fn_3_5A6D4(0);
        break;
    }
}

// .text:0x00131FFC size:0x80 mapped:0x80771090
void fn_3_131FFC(void) {
    g_Scores.inning += 1;
    g_Minigame.turnNumberWithinRound = 0;
    if (g_Minigame.multiPlayerInd == 0) {
        fn_3_5A6D4(7);
        return;
    }
    fn_3_10F550(4, 0);
    if (g_Scores.inning == 1) {
        fn_3_10AD48();
    }
    fn_3_5A6D4(7);
}

// .text:0x0013207C size:0x40 mapped:0x80771110
void fn_3_13207C(void) {
    sndFXStartEx(0x1BD, lbl_800EFBA4[6], 0x3F, 0);
    fn_3_5A6D4(6);
}

// .text:0x001320BC size:0x310 mapped:0x80771150
// Barrel Batter: set up the minigame.
void fn_3_1320BC(void) {
    s32 i;

    if (g_GameLogic._125 == 0) {
        fn_3_59A90();
        g_GameLogic.secondaryGameMode = 5;
        for (i = 0; i < 4; i++) {
            g_Minigame.miniGameCurrentPoints[i] = 0;
            g_Minigame.miniGameLatestPoints[i] = 0;
            g_Minigame.minigamePoints_current_Latest[i].current = 0;
            g_Minigame.minigamePoints_current_Latest[i].latest = 0;
            g_Minigame.minigameControlStruct[0].fieldOrder[i] = -1;
            g_Minigame.minigameFielderIndex[i] = -1;
            g_Minigame._18FC[i] = -1;
            g_Minigame._1900[i] = -1;
            g_Minigame.minigameControlStruct[0]._24[i] = 1;
        }
        g_Scores.inning = 0;
        g_Minigame.pointsReqToWin_challenge = 0;
        g_Minigame._1A37 = 0;
        g_Minigame.minigamePlayerSelectedOrder = -1;
        g_Minigame.rosterID = -1;
        g_Minigame._17C0 = 0;
        g_Minigame.bB_bombBarrelHitInd = 0;
        g_Minigame.bB_bombBarrelID = -1;
        if (g_Minigame.multiPlayerInd == 0) {
            g_Scores.maxInnings = 1;
            for (i = 0; i < 4; i++) {
                g_Minigame.minigameControlStruct[0].aIStrength[i] = lbl_3_data_2127C[g_Minigame.GameMode_MiniGame][g_Minigame.soloMinigameDifficulty];
            }
            if (g_Minigame.soloMinigameDifficulty <= 2) {
                g_Minigame.pointsReqToWin_challenge = lbl_3_data_21790[g_Minigame.soloMinigameDifficulty];
            }
        } else {
            if (g_Minigame._1A3C != 0) {
                g_Minigame.minigameControlStruct[0].aIStrength[0] = lbl_3_data_2127C[7][0];
                g_Minigame.minigameControlStruct[0].aIStrength[1] = lbl_3_data_2127C[7][0];
                g_Minigame.minigameControlStruct[0].aIStrength[2] = lbl_3_data_2127C[7][0];
                g_Minigame.minigameControlStruct[0].aIStrength[3] = lbl_3_data_2127C[7][0];
            }
            g_Scores.maxInnings = lbl_3_data_21798[5];
        }
        fn_3_12FE84();
        g_Minigame.turnNumberWithinRound = 0;
        g_Minigame.barrelBatter_scoreCalculatedInd = 0;
        g_Minigame.barrelBatterChargeMeter = 0;
        g_GameLogic._125 += 1;
    } else {
        fn_3_5A6D4(5);
    }
}


// .text:0x001323CC size:0x11C mapped:0x80771460
void fn_3_1323CC(void) {
    u32 i;
    for (i = 0; i < 15; i++) {
        if (g_Minigame.barrels[i].barrelState == 1) {
            mgStep_1323CC(i);
        }
    }
}

// The original expands fn_3_1307D0 into fn_3_1324E8. CW only does that with a larger inline size
// limit (with -inline deferred, the value in effect at the end of the file counts) and only from a
// copy that is always visible (fn_3_1307D0 itself is NONMATCHING).
#pragma inline_max_size(100000)
// Inline copy of fn_3_1307D0.
static inline void fn_3_1307D0_inline(void) {
    BB_barrelStruct* b;
    s32 i;

    ballPhysica();
    fn_3_12F624();
    for (i = 0; i < 15; i++) {
        b = &g_Minigame.barrels[i];
        if (b->animationCounter < 0x7FFE) {
            b->animationCounter += 1;
        } else {
            b->animationCounter = 0x7FFF;
        }
        if (b->barrelState == 1) {
            mgStep_1323CC(i);
        }
        if (b->barrelState == 3) {
            fn_3_12F28C(i);
        }
        if (b->replacingBarrelInd != 0) {
            fn_3_12EFA4(i);
        }
    }
    ((void (*)(void))fn_3_130288)(); // a call in the original (not inlined)
}

// .text:0x001324E8 size:0x9F4 mapped:0x8077157C
// Barrel Batter: per-frame dispatch on the game status.
void fn_3_1324E8(void) {
    switch (g_GameLogic.gameStatus) {
    case 4:
        fn_3_1320BC();
        break;
    case 26:
        fn_3_13207C();
        break;
    case 6:
        fn_3_131FFC();
        break;
    case 7:
        fn_3_131EC4();
        break;
    case 0:
        fn_3_131C88();
        break;
    case 1:
        fn_3_130C6C();
        break;
    case 2:
        fn_3_1307D0_inline();
        break;
    case 8:
        fn_3_131540();
        break;
    case 25:
        fn_3_13128C();
        break;
    case 3:
        fn_3_13119C();
        break;
    case 15:
        fn_3_1312D4();
        break;
    }
}
