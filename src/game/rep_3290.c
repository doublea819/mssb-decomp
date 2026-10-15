// g_Minigame stays a byte array here (the matched code's address arithmetic depends on it); MG is its
// typed view.
#define g_Minigame g_Minigame_header_decl
#ifdef TARGET_PC
extern void port_trace_value(const char* tag, int value);
#define MGTRACE(tag, v) port_trace_value(tag, (int)(v))
#else
#define MGTRACE(tag, v) ((void)0)
#endif
#include "game/rep_3290.h"
#undef g_Minigame
#define REP_HEADER_FN repHeader_3290
#include "header_rep_inline.h"
#include "stl/math.h"

extern void* memset(void*, int, size_t);

extern u8 g_Minigame[];
#define MG ((Mg3290*)g_Minigame)
// Byte offset of a Mg3290 field: some matched code needs the original `base + (i + offset)` arithmetic.
#define MGO(field) ((s32)OFFSET_OF(Mg3290, field))
extern s16 lbl_3_data_21654[];
extern u8 lbl_3_data_21694[];
extern u8 lbl_3_data_216B0[];
extern u8 lbl_3_data_216B8[];
extern s32 RandomInt_Game(s32);
extern s32 RandomInt_Game_Range(s32, s32);
extern f32 lbl_3_data_21634[];
extern f32 lbl_3_data_219B8[];
extern s16 lbl_3_data_2167C[];
extern f32 lbl_3_data_21674[];

extern void fn_3_1500C8(void);
extern f32 lbl_3_data_215C8[];
extern f32 lbl_3_data_21688[];
extern void fn_8004C108(f32*, s32);
extern u32 fn_3_90064(s32 id);
#pragma dont_inline on

// .text:0x001133C4 size:0x338 mapped:0x80752458
extern s16 lbl_3_data_5F3C[4];
extern f32 LinearInterpolateToNewRange(f32 value, f32 prevMin, f32 prevMax, f32 nextMin, f32 nextMax);

// NONMATCHING 98%: the main loop walker is not shared with the clear loop's base; one extsb is CSE'd
#if NONMATCHING
void fn_3_1133C4(void) {
    MgPad_3290* pad;
    u8 ci;
    s8 i;
    i = 0;
    do {
        MG->cpu.active[i] = 0;
        i++;
    } while (i < 4);
    i = 0;
    do {
        ci = MG->port[i];
        if ((s8)ci >= 0 && (s8)ci < 4 && i == MG->currentPlayer && MG->isCpu[i] != 0) {
            pad = &MG->cpu.pad[(s8)ci];
            MG->cpu.active[(s8)ci] = 1;
            memset(pad, 0, sizeof(MgPad_3290));
            switch (MG->cpu.state) {
            case 0:
                fn_3_1136FC();
                MG->cpu.timer = 60;
                MG->cpu.state = 1;
                break;
            case 1:
                if (--MG->cpu.timer <= 0) {
                    switch (MG->cpu.plan) {
                    case 0:
                        MG->cpu.state = 2;
                        break;
                    case 1:
                        MG->cpu.state = 4;
                        break;
                    case 2:
                        MG->cpu.state = 6;
                        break;
                    case 3:
                    default:
                        MG->cpu.state = 8;
                        break;
                    }
                }
                break;
            case 2:
                pad->trig |= 0x100;
                pad->held |= 0x100;
                MG->cpu.state = 3;
                break;
            case 3:
                if (g_Pitcher.windupCountdownUntilBallReleased < lbl_3_data_5F3C[2]) {
                    MG->cpu.state = 9;
                } else {
                    pad->held |= 0x100;
                }
                break;
            case 4:
                pad->trig |= 0x100;
                pad->held |= 0x100;
                MG->cpu.state = 5;
                break;
            case 5:
                pad->held |= 0x100;
                break;
            case 6:
                pad->trig |= 0x100;
                pad->held |= 0x100;
                MG->cpu.state = 7;
                break;
            case 7:
                if (g_Pitcher.framesAHeldForChargePitches == 0 &&
                    (s16)LinearInterpolateToNewRange(1.0f - (f32)g_Pitcher.windupCountdownUntilBallReleased /
                                                                (f32)g_Pitcher.pitchWindUpCountDown,
                                                     0.0f, 1.0f, lbl_3_data_21654[0], lbl_3_data_21654[1]) >=
                        MG->cpu.target) {
                    MG->cpu.state = 9;
                } else {
                    pad->held |= 0x100;
                }
                break;
            case 8:
                pad->trig |= 0x100;
                pad->held |= 0x100;
                MG->cpu.state = 9;
                break;
            case 9:
                break;
            }
        }
        i++;
    } while (i < 4);
}
#endif

// .text:0x001136FC size:0x220 mapped:0x80752790
void fn_3_1136FC(void) {
    u8* p;
    u8 d;
    s8 i;
    s16 lo;
    u8* g;
    s16 hi;
    s8 k;
    g = g_Minigame;
    i = 0;
    lo = 0;
    hi = 0x7FFF;
    p = g;
    k = 0;
    d = g[(s8)g[MGO(currentPlayer)] + MGO(aIStrength)];
    do {
        u8* e = g + p[MGO(wallOrder)] * (s32)sizeof(MgEnt_3290);
        lo += ((MgEnt_3290*)(e + MGO(wall)))->width;
        if (((MgEnt_3290*)(e + MGO(wall)))->type == 2) {
            k = i;
            i++;
            break;
        }
        i++;
        p++;
    } while (i < 7);
    if (i < 7) {
        s16 w = MG->wall[MG->wallOrder[i]].width;
        hi = lo + w - 1;
    }
    if (RandomInt_Game(0x64) < (s8)(lbl_3_data_21694 + d * 7)[k]) {
        s8* q = (s8*)lbl_3_data_216B0 + d * 2;
        s16 r = RandomInt_Game_Range(*(s8*)(lbl_3_data_216B0 + d * 2), q[1]);
        lo += r;
        hi += r;
    }
    if (lo <= lbl_3_data_21654[2] && lbl_3_data_21654[2] <= hi) {
        ((Mg3290*)g)->cpu.plan = 0;
    } else if (lo <= lbl_3_data_21654[3] && lbl_3_data_21654[3] <= hi) {
        ((Mg3290*)g)->cpu.plan = 3;
    } else if (hi >= lbl_3_data_21654[0] && lo <= lbl_3_data_21654[1]) {
        ((Mg3290*)g)->cpu.plan = 2;
        if (lo < lbl_3_data_21654[0]) {
            lo = lbl_3_data_21654[0];
        }
        if (hi > lbl_3_data_21654[1]) {
            hi = lbl_3_data_21654[1];
        }
        ((Mg3290*)g)->cpu.target = RandomInt_Game_Range(lo, hi);
    } else {
        ((Mg3290*)g)->cpu.plan = 1;
    }
    if (((Mg3290*)g)->cpu.plan == 0 && RandomInt_Game(0x64) < (s8)lbl_3_data_216B8[d]) {
        ((Mg3290*)g)->cpu.plan = 1;
    }
    MGTRACE("wb.difficulty", ((Mg3290*)g)->difficulty);
    MGTRACE("wb.cpuPlayer", (s8)g[MGO(currentPlayer)]);
    MGTRACE("wb.cpuStrength", d);
    MGTRACE("wb.cpuAim(lo*1000+hi)", lo * 1000 + hi);
    MGTRACE("wb.cpuPlan", ((Mg3290*)g)->cpu.plan);
}

// .text:0x0011391C size:0x34 mapped:0x807529B0
void fn_3_11391C(void) {
    memset(&MG->cpu, 0, sizeof(MgCpu_3290));
}

// .text:0x00113950 size:0xF8 mapped:0x807529E4
// The original strength-reduces one walker per element size (1, 2 and 12 bytes) from the g_Minigame
// base: each walker is a view of g_Minigame shifted by i elements, read at element [0].
void fn_3_113950(void) {
    Mg3290* p6 = MG;
    Mg3290* p7 = MG;
    Mg3290* p8 = MG;
    f32 g = lbl_3_data_21634[2];
    f32 fl = lbl_3_data_219B8[0xE];
    f32 bn = lbl_3_data_21634[3];
    f32 dm = lbl_3_data_21634[4];
    s16 mx = lbl_3_data_2167C[4];
    s32 i;
    for (i = 0; i < 100; i++, p6 = (Mg3290*)((u8*)p6 + 1), p7 = (Mg3290*)((u8*)p7 + 2), p8 = (Mg3290*)((u8*)p8 + 12)) {
        if (p6->coinVisible[0] != 0) {
            p7->coinFrames[0] = p7->coinFrames[0] + 1;
            p8->coinPos[0].x = p8->coinPos[0].x + p8->coinVel[0].x;
            p8->coinPos[0].y = p8->coinPos[0].y + p8->coinVel[0].y;
            p8->coinPos[0].z = p8->coinPos[0].z + p8->coinVel[0].z;
            p8->coinVel[0].y = p8->coinVel[0].y - g;
            if (p8->coinPos[0].y < fl) {
                p8->coinPos[0].y = fl;
                p8->coinVel[0].y = -p8->coinVel[0].y * bn;
                p8->coinVel[0].x = p8->coinVel[0].x * dm;
                p8->coinVel[0].z = p8->coinVel[0].z * dm;
            }
            if (p7->coinFrames[0] > mx) {
                p6->coinVisible[0] = 0;
            }
        }
    }
}

// .text:0x00113A48 size:0x2D8 mapped:0x80752ADC
extern f32 LinearInterpolateToNewRange(f32 value, f32 prevMin, f32 prevMax, f32 nextMin, f32 nextMax);

void fn_3_113A48(void) {
    u8* p;
    s32 i;
    s32 sum;
    s16 rem;
    if (g_Ball.pitchHangtimeCounter == 1) {
        MG->pitchPower = lbl_3_data_21654[3];
        if (g_Pitcher.ChargePitchType == 3) {
            MG->pitchPower = lbl_3_data_21654[2];
        } else if (g_Pitcher.ChargePitchType >= 2) {
            MG->pitchPower = LinearInterpolateToNewRange(g_Pitcher.pitchChargeUp, 0.0f, 1.0f, lbl_3_data_21654[0],
                                                         lbl_3_data_21654[1]);
        }
        MG->powerRemaining = MG->pitchPower;
        sum = 0;
        p = g_Minigame;
        i = 0;
        do {
            u8* e = g_Minigame + p[MGO(wallOrder)] * (s32)sizeof(MgEnt_3290);
            sum += ((MgEnt_3290*)(e + MGO(wall)))->width;
            if (((MgEnt_3290*)(e + MGO(wall)))->type == 2) {
                i++;
                break;
            }
            i++;
            p++;
        } while (i < 7);
        if (MG->pitchPower >= sum) {
            if (i < 7) {
                if (MG->pitchPower <= sum + MG->wall[MG->wallOrder[i]].width - 1) {
                    MG->hitNoteBlock = 1;
                }
            } else {
                MG->hitNoteBlock = 1;
            }
        }
        if (MG->hitNoteBlock != 1) {
            rem = MG->pitchPower;
            for (i = 0; i < 7; i++) {
                rem -= MG->wall[MG->wallOrder[i]].width;
                if (rem < 0) {
                    break;
                }
            }
            i--;
            if (i >= 0 && MG->wall[MG->wallOrder[i]].type == 1) {
                MG->_1A8B = i;
                MG->hitBowserWall = 1;
            }
        }
    }
}

// .text:0x00113D20 size:0x1A0 mapped:0x80752DB4
void fn_3_113D20(void) {
    MgEnt_3290* e;
    int i;
    s8 flag;
    f32 a;
    f32 n;
    s8 dir;
    flag = 0;
    for (i = 0; i < 7; i++) {
        e = &MG->wall[i];
        a = e->vel.x;
        if (a != 0.0f || e->vel.y != 0.0f) {
            e->vel.x = e->vel.y * cos(a) + e->vel.x;
            n = e->vel.x;
            if (n >= 0.0f) {
                dir = -1;
            } else {
                dir = 1;
            }
            if (a < n) {
                if (a < 0.0f && n >= 0.0f) {
                    flag = 1;
                }
            } else if (a > 0.0f) {
                if (n <= 0.0f) {
                    flag = 1;
                }
            }
            if (flag) {
                e->vel.y = e->vel.y * lbl_3_data_21688[2];
                if (fabs(e->vel.y) < e->vel.z * lbl_3_data_21688[2]) {
                    e->vel.z = 0.0f;
                    e->vel.y = 0.0f;
                    e->vel.x = 0.0f;
                }
                flag = 0;
            }
            e->vel.y = dir * e->vel.z + e->vel.y;
        }
    }
}

// .text:0x00113EC0 size:0x54 mapped:0x80752F54
void fn_3_113EC0(void) {
    g_Pitcher.ballVelocity.z = -g_Pitcher.ballVelocity.z;
    g_Pitcher.ballVelocity.x *= lbl_3_data_21674[0];
    g_Pitcher.ballVelocity.y *= lbl_3_data_21674[0];
    MG->ballStopped = 1;
    g_Pitcher.ballVelocity.z *= lbl_3_data_21674[0];
}

// .text:0x00113F14 size:0x2F0 mapped:0x80752FA8
extern int rand(void);
extern void fn_3_6C854(int team, int kind);
extern u32 lbl_3_data_21648[];
extern Vec lbl_3_data_215E0[];

void fn_3_113F14(void) {
    s32 i;
    MgEnt_3290* e;
    s32 j;
    u8 hit;
    u8 cnt;
    f32 ang;
    f32 y;
    if (g_Ball.pitchHangtimeCounter >= 1) {
        hit = MG->ballStopped;
        y = g_Ball.AtBat_Contact_BallPos.z - g_Ball.groundYForBounces - lbl_3_data_21674[1];
        for (i = 0; i < 7; i++) {
            e = &MG->wall[i];
            if (e->state == 3 && y <= e->pos.z && hit == 0) {
                e->width -= MG->powerRemaining;
                if (e->width <= 0) {
                    MG->powerRemaining = -e->width;
                    e->state = 4;
                    MG->latestPoints[MG->currentPlayer] += lbl_3_data_21654[7 + e->type];
                    cnt = lbl_3_data_21648[e->type];
                    for (j = 0; j < 100; j++) {
                        if (MG->coinVisible[j] == 0) {
                            MG->coinFrames[j] = 0;
                            MG->coinVisible[j] = 1;
                            MG->coinPos[j].x = lbl_3_data_215E0[e->slot].x;
                            MG->coinPos[j].y = lbl_3_data_215E0[e->slot].y;
                            MG->coinPos[j].z = lbl_3_data_215E0[e->slot].z;
                            ang = 0.017453292f * (rand() % 180);
                            MG->coinVel[j].x = lbl_3_data_21634[1] * (f32)cos(ang);
                            MG->coinVel[j].z = lbl_3_data_21634[1] * (f32)sin(ang);
                            MG->coinVel[j].y = lbl_3_data_21634[0];
                            if (--cnt == 0) {
                                break;
                            }
                        }
                    }
                    fn_3_6C854(((s8*)(g_Minigame + MGO(port)))[MG->currentPlayer], 0);
                } else {
                    e->vel.x = 0.0f;
                    e->vel.y = lbl_3_data_21688[0];
                    e->vel.z = lbl_3_data_21688[1];
                    fn_3_90064(0x2E1);
                    g_Pitcher.ballVelocity.z = -g_Pitcher.ballVelocity.z;
                    g_Pitcher.ballVelocity.x *= lbl_3_data_21674[0];
                    g_Pitcher.ballVelocity.y *= lbl_3_data_21674[0];
                    MG->ballStopped = 1;
                    g_Pitcher.ballVelocity.z *= lbl_3_data_21674[0];
                }
                return;
            }
        }
    }
}

// .text:0x00114204 size:0x180 mapped:0x80753298
void fn_3_114204(void) {
    int cnt;
    int i;
    MgEnt_3290* e;
    cnt = 0;
    for (i = 0; i < 7; i++) {
        e = &MG->wall[i];
        if (e->state == 2) {
            e->pos.x += lbl_3_data_215C8[3];
            e->pos.y += lbl_3_data_215C8[4];
            e->pos.z += lbl_3_data_215C8[5];
            if (e->pos.z >= e->home.z) {
                e->pos.z = e->home.z;
                e->state = 3;
            }
            cnt++;
        }
    }
    if (cnt == 0) {
        for (i = 0; i < 7; i++) {
            e = &MG->wall[i];
            if (e->state == 1) {
                e->pos.x += lbl_3_data_215C8[0];
                e->pos.y += lbl_3_data_215C8[1];
                e->pos.z += lbl_3_data_215C8[2];
                if (e->pos.y <= e->home.y) {
                    e->pos.y = e->home.y;
                    e->state = 3;
                    fn_8004C108(&e->home.x, 1);
                    fn_3_90064(0x2F4);
                }
                cnt++;
            }
        }
        if (cnt == 0) {
            MG->phase = 2;
        }
    }
}

// .text:0x00114384 size:0x634 mapped:0x80753418
extern void fn_800246D4(s32 (*compare)(void* key, void* elem), u8* src, u8* dst, s32 size, s32 count);
extern Vec lbl_3_data_21520[14];
extern GameScores g_Scores;

#define MG_ENT_3290(idx) (&MG->wall[idx])

// NONMATCHING 95%: saved-register numbering (list base not kept in r28) and one lwzx/lwz in the removal loop
#if NONMATCHING
// Sets up a new round of targets: sorts the order list, places them and picks the special ones.
void fn_3_114384(void) {
    s32 maxNormal;
    u32 i;
    u32 j;
    u32 placed;
    u32 k;
    u32 last;
    s32 m;
    u8 n;
    u8 pick;
    MgEnt_3290* e;
    u8 cand[8];
    u32 counts[3];
    u32 list[7];

    if (MG->multiPlayerInd != 0 || MG->_1A3C != 0 || MG->difficulty != 3) {
        switch (g_Scores.inning) {
        case 1:
            maxNormal = 1;
            break;
        case 2:
            maxNormal = 2;
            break;
        default:
            maxNormal = 3;
            break;
        }
    } else if (MG->turnCounter < 6) {
        maxNormal = 1;
    } else if (MG->turnCounter < 11) {
        maxNormal = 2;
    } else if (MG->turnCounter < 16) {
        maxNormal = 3;
    } else {
        maxNormal = 4;
    }
    fn_800246D4(fn_3_1149B8, MG->wallOrder, MG->wallOrder, 1, 7);
    i = 0;
    do {
        MG_ENT_3290(MG->wallOrder[i])->slot = i;
        i++;
    } while (i < 7);
    i = 0;
    do {
        counts[i] = 0;
        i++;
    } while (i < 3);
    placed = 0;
    i = 0;
    do {
        e = MG_ENT_3290(MG->wallOrder[i]);
        if (e->state == 3) {
            placed++;
            counts[e->type]++;
        }
        i++;
    } while (i < 7);
    i = 0;
    do {
        e = MG_ENT_3290(MG->wallOrder[i]);
        e->home.x = lbl_3_data_21520[e->slot].x;
        e->home.y = lbl_3_data_21520[e->slot].y;
        e->home.z = lbl_3_data_21520[e->slot].z;
        if (i < placed) {
            e->state = 2;
        } else {
            e->pos.x = e->home.x;
            e->pos.y = e->home.y;
            e->pos.z = e->home.z;
            e->pos.x += lbl_3_data_21520[e->slot + 7].x;
            e->pos.y += lbl_3_data_21520[e->slot + 7].y;
            e->pos.z += lbl_3_data_21520[e->slot + 7].z;
            e->state = 1;
            e->type = 1;
            counts[e->type]++;
            e->width = lbl_3_data_21654[4 + e->type];
        }
        e->timer = 0;
        e->vel.x = 0.0f;
        e->vel.y = 0.0f;
        e->vel.z = 0.0f;
        i++;
    } while (i < 7);
    if (placed < 7) {
        if (counts[2] == 0) {
            // place one type-2 target, avoiding the last two slots that had one
            n = 0;
            for (j = placed; j < 7; j++) {
                k = 0;
                do {
                    if (j == MG->specialWall[k]) {
                        break;
                    }
                    k++;
                } while (k < 2);
                if (k >= 2) {
                    cand[n++] = j;
                }
            }
            if (n != 0) {
                pick = cand[RandomInt_Game(n)];
            } else {
                pick = RandomInt_Game_Range(placed, 6);
            }
            counts[1]--;
            e = MG_ENT_3290(MG->wallOrder[pick]);
            e->type = 2;
            e->width = lbl_3_data_21654[4 + e->type];
        }
        if (counts[1] > maxNormal) {
            // turn surplus type-1 targets into type 0, never next to a type-2 one
            m = 0;
            for (j = placed; j < 7; j++) {
                if (MG_ENT_3290(MG->wallOrder[j])->type != 2 &&
                    (j == 0 || MG_ENT_3290(MG->wallOrder[j - 1])->type != 2) &&
                    (j == 6 || maxNormal <= 1 || MG_ENT_3290(MG->wallOrder[j + 1])->type != 2)) {
                    list[m] = j;
                    m++;
                }
            }
            if (m != 0) {
                while (counts[1] > maxNormal) {
                    k = RandomInt_Game(m);
                    last = m - 1;
                    counts[1]--;
                    e = MG_ENT_3290(MG->wallOrder[list[k]]);
                    e->type = 0;
                    e->width = lbl_3_data_21654[4 + e->type];
                    for (j = k; j < last; j++) {
                        list[j] = list[j + 1];
                    }
                    if (--m <= 0) {
                        break;
                    }
                }
            }
        }
    }
    i = 0;
    do {
        MG->specialWall[1 + i] = MG->specialWall[i];
        i++;
    } while (i < 1);
    i = 0;
    do {
        if (MG_ENT_3290(MG->wallOrder[i])->type == 2) {
            MG->specialWall[0] = i;
            break;
        }
        i++;
    } while (i < 7);
    MG->phase = 1;
    MG->_1A80 = 7;
}
#endif

// .text:0x001149B8 size:0x74 mapped:0x80753A4C
s32 fn_3_1149B8(void* a, void* b) {
    MgEnt_3290* ea = &MG->wall[*(u8*)a];
    MgEnt_3290* eb = &MG->wall[*(u8*)b];
    if (ea->state == 3 && eb->state != 3) {
        return -1;
    }
    if (ea->state != 3 && eb->state == 3) {
        return 1;
    }
    return ea->slot - eb->slot;
}

// .text:0x00114A2C size:0x5C mapped:0x80753AC0
void fn_3_114A2C(void) {
    u8 v = MG->phase;
    if (v == 0) {
        fn_3_114384();
        fn_3_1500C8();
    } else if (v == 1) {
        fn_3_114204();
    } else if (v == 2) {
        fn_3_113F14();
        fn_3_113D20();
    }
}

// .text:0x00114A88 size:0x538 mapped:0x80753B1C
extern InMemFielderType g_Fielders[];
extern VecXZ lbl_3_data_450C;
extern VecXZ lbl_3_data_21500[];


// NONMATCHING 94%: float constants (incl. the inlined dolsqrtf2's) get pooled behind one base register
#pragma pool_data off // each float constant is its own .rodata symbol in the original
#if NONMATCHING
// Moves the fielders to their next positions over lbl_3_data_2167C[1] frames; init snaps them.
void fn_3_114A88(s32 init) {
    s32 i;
    s32 d;
    f32 inv;
    f32 dx;
    f32 dz;
    InMemFielderType* f;
    if (++MG->rotationCounter == 1 || init != 0) {
        if (MG->difficulty != 3 || MG->multiPlayerInd != 0) {
            f = &g_Fielders[MG->fielder[MG->turnOrder[(MG->turnNumberWithinRound + 3) % 4]]];
            f->pos.x = MG->pitcherX;
            f->pos.z = MG->pitcherZ;
        }
        for (i = 0; i < 4; i++) {
            if (MG->port[i] >= 0) {
                d = i - MG->turnNumberWithinRound;
                if (d < 0) {
                    d += MG->numParticipants;
                }
                if (d == 0) {
                    MG->target[MG->turnOrder[i]].x = lbl_3_data_450C.x;
                    MG->target[MG->turnOrder[i]].z = lbl_3_data_450C.z;
                } else {
                    MG->target[MG->turnOrder[i]].x = lbl_3_data_21500[d].x;
                    MG->target[MG->turnOrder[i]].z = lbl_3_data_21500[d].z;
                }
            }
        }
        if (init != 0) {
            for (i = 0; i < MG->numParticipants; i++) {
                f = &g_Fielders[MG->fielder[i]];
                f->pos.x = MG->target[i].x;
                f->pos.y = 0.0f;
                f->pos.z = MG->target[i].z;
            }
            return;
        }
    }
    if (MG->rotationCounter >= lbl_3_data_2167C[1]) {
        MG->rotateInd = 0;
        for (i = 0; i < 4; i++) {
            if (MG->port[i] >= 0) {
                g_Fielders[MG->fielder[i]].speed = 0.0f;
            }
        }
    } else {
        inv = 1.0f / (lbl_3_data_2167C[1] - MG->rotationCounter);
        for (i = 0; i < 4; i++) {
            if (MG->port[i] >= 0) {
                f = &g_Fielders[MG->fielder[i]];
                dx = (MG->target[i].x - f->pos.x) * inv;
                dz = (MG->target[i].z - f->pos.z) * inv;
                f->velX = dx;
                f->velZ = dz;
                f->pos.x += dx;
                f->pos.z += dz;
                f->speed = dolsqrtf2(dx * dx + dz * dz);
                if (f->speed > 0.0f) {
                    f->_038 = dx / f->speed;
                    f->_03C = dx / f->speed; // sic: original divides dx for both
                }
            }
        }
    }
}
#endif
#pragma pool_data reset


#pragma dont_inline off
