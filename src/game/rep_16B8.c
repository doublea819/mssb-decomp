#include "game/rep_16B8.h"
#define REP_HEADER_FN repHeader_16B8
#include "header_rep_inline.h"
#include "main/menu_globals.h"

extern u8 lbl_3_data_F390[];
extern u8 lbl_3_data_E160[];
extern u8 lbl_3_data_E21C[];
extern u8 lbl_3_data_E2F8[];
extern u8 lbl_3_data_E278[];
extern u16 lbl_3_data_E200[];
extern void fn_3_ED574(void);
extern u8 lbl_3_data_BF6C[];

extern u8 lbl_3_data_E0E0[];

extern u8 lbl_3_data_F350[];

extern u8 lbl_3_data_F3F0[];

extern u8 lbl_3_data_E120[];

extern void fn_80034E20(void*, void*);
extern void fn_800363D8(void*, s32, s32, s32, s32);
extern u8 lbl_3_data_C1EC[];

extern RepLineScoreData lbl_3_data_EC1C;
extern u8 lbl_3_data_F430[12][2]; // per captain: logo frames
extern u8 lbl_3_data_EABC[];
extern u8 lbl_3_data_E85C[];
extern f32 lbl_3_data_C1CC[4]; // field-map transform: offset x, offset y, scale x, scale y
extern void fn_3_ED0F4(void);
extern u8 lbl_3_data_F224[];
extern u8 lbl_3_data_F200[3][12]; // [0]: fn_3_91E4C thresholds, [1]/[2]: line-score column _72 values
extern u8 lbl_3_data_E378[];
extern u8 lbl_3_data_8D88[];
extern u8 lbl_3_data_BFEC[];
extern u8 lbl_3_data_E758[];
extern u16 lbl_3_data_F344[]; // per stadium: anim id
extern u8 lbl_3_data_E75C[];
#include "static/UnknownHomes_Static.h"
#include "musyx/musyx.h"
#include "main/SpaniDesc.h"
#include "game/auto_00_00097144_text.h" // GameHudFlags lbl_3_common_bss_32724, GamePauseState lbl_3_common_bss_34C90
#include "game/auto_00_001658F0_text.h" // StarChanceState lbl_3_common_bss_37400
extern StarChanceState lbl_3_common_bss_37400;

extern RepBannerData lbl_3_data_BE50;
extern RepRunningLogic g_RunningLogic;
extern RepSoundParams lbl_3_data_8404[];
extern RepSoundParams lbl_3_data_84B8[];
extern u16 lbl_3_data_81DC[];
#include "main/file_80021308.h" // SoundManager
extern SoundManager lbl_800EF808;
extern RepFielderView g_Fielders[9];
BOOL fn_3_1650C(int* outX, int* outY, BOOL r5, f32 pX, f32 pY, f32 pZ);
extern void fn_8003649C(void* owner, s32 idx, s32 track, u16 animId, u32 frame);
extern GameScores g_Scores;

// .text:0x00091520 size:0x540 mapped:0x806D05B4
void fn_3_91520(void) {
    RepTask* task = (void*)lbl_803CC1B8;
    int sx;
    int sy;
    if (lbl_3_common_bss_32724.hudOff == 0) {
    if (task->timer < 0xFFFE) {
        task->timer++;
    } else {
        task->timer = 0xFFFF;
    }
    if (g_UnkSound_32718._08 != 0) {
        if (g_Stats.replayInd != 0) {
            g_UnkSound_32718._08 = 0;
            return;
        }
        if (g_GameLogic.framesOfExitingToMenu != 0) {
            g_UnkSound_32718._08 = 0;
            return;
        }
        fn_3_1650C(&sx, &sy, FALSE, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
        switch (g_UnkSound_32718._08) {
        case 1:
            if (task->_1C == 0) {
                REP_OBJ(task, 0)->_5C = 0;
                REP_OBJ(task, 0)->flags |= 2;
                REP_OBJ(task, 0)->_68 = 1;
                REP_OBJ(task, 0)->x = sx;
                REP_OBJ(task, 0)->y = sy;
                task->_1C = 1;
            }
            break;
        case 2:
            if (task->_1E == 0) {
                REP_OBJ(task, 1)->_5C = 0;
                REP_OBJ(task, 1)->flags |= 2;
                REP_OBJ(task, 1)->_68 = 1;
                REP_OBJ(task, 1)->_64 = 1;
                REP_OBJ(task, 1)->x = sx;
                REP_OBJ(task, 1)->y = sy;
                task->_1E = 1;
            }
            break;
        case 3:
            if (task->_1E == 0) {
                REP_OBJ(task, 1)->_5C = 0;
                REP_OBJ(task, 1)->flags |= 2;
                REP_OBJ(task, 1)->_68 = 1;
                REP_OBJ(task, 1)->_64 = 2;
                REP_OBJ(task, 1)->x = sx;
                REP_OBJ(task, 1)->y = sy;
                task->_1E = 1;
            }
            break;
        case 4:
            if (g_d_GameSettings.GameModeSelected == 6) {
                g_UnkSound_32718._08 = 0;
                return;
            }
            if (task->_20 == 0) {
                REP_OBJ(task, 2)->_5C = 0;
                REP_OBJ(task, 2)->flags |= 2;
                REP_OBJ(task, 2)->_68 = 0;
                REP_OBJ(task, 2)->x = 0.0f;
                REP_OBJ(task, 2)->y = 0.0f;
                task->_20 = 1;
            }
            break;
        }
        task->timer = 0;
        g_UnkSound_32718._08 = 0;
    } else {
        if (task->_1C != 0 && ((REP_OBJ(task, 0)->_69 == 2) ? 1 : 0)) {
            REP_OBJ(task, 0)->flags &= ~2;
            task->_1C = 0;
        }
        if (task->_1E != 0 && ((REP_OBJ(task, 1)->_69 == 2) ? 1 : 0)) {
            REP_OBJ(task, 1)->flags &= ~2;
            task->_1E = 0;
        }
        if (task->_20 != 0) {
            if (task->timer == 0x1E) {
                playSoundEffect(0x1AC);
                REP_OBJ(task, 2)->_68 = 1;
            }
            if (((REP_OBJ(task, 2)->_69 == 2) ? 1 : 0)) {
                REP_OBJ(task, 2)->flags &= ~2;
                task->_20 = 0;
            }
        }
    }
    } else {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x00091A60 size:0x68 mapped:0x806D0AF4
void fn_3_91A60(void) {
    RepTask* o;
    fn_80034E20(o = (void*)lbl_803CC1B8, lbl_3_data_BF6C);
    o->timer = 0;
    o->_1C = 0;
    o->_1E = 0;
    o->_20 = 0;
    lbl_803CC1B8->func = fn_3_91520;
}

// .text:0x00091AC8 size:0x88 mapped:0x806D0B5C
void fn_3_91AC8(void) {
    void* p = (void*)lbl_803CC1B8;
    if (lbl_3_common_bss_32724.hudOff == 0 && g_Stats.replayInd == 0) {
        if (g_GameLogic.gameStatus == 2 || g_GameLogic.gameStatus == 1) {
            return;
        }
    }
    fn_80034CEC(p);
    REMOVE_QUEUE_NOARG();
    lbl_3_common_bss_32724._B2 = 0;
}
// .text:0x00091B50 size:0x4C mapped:0x806D0BE4
void fn_3_91B50(void) {
    fn_80034E20((void*)lbl_803CC1B8, lbl_3_data_F350);
    lbl_803CC1B8->func = fn_3_91AC8;
}

// .text:0x00091B9C size:0xD4 mapped:0x806D0C30
void fn_3_91B9C(void) {
    RepTask* p = (void*)lbl_803CC1B8;
    if (lbl_3_common_bss_32724.hudOff == 0) {
        u32 idx = p->baseIdx;
        LayoutSlot* t = lbl_80371C30;
        if ((t[idx].obj->_5C >> 16) >= 0x4B) {
            LayoutObj* q = t[idx + 1].obj;
            q->flags |= 2;
        }
        if ((g_Stats.replayInd == 0 && g_Stats._39 == 0) || g_GameLogic.gameStatus == 3 || g_GameLogic.gameStatus == 0xB || g_GameLogic.gameStatus == 0xE) {
            goto call;
        }
    } else {
call:
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
        lbl_3_common_bss_32724._B0 = 0;
        lbl_3_common_bss_32724._B1 = 0;
    }
}

// .text:0x00091C70 size:0x5C mapped:0x806D0D04
void fn_3_91C70(void) {
    fn_80034E20((void*)lbl_803CC1B8, lbl_3_data_F390);
    lbl_3_common_bss_32724._B0 = 1;
    lbl_803CC1B8->func = fn_3_91B9C;
}

// .text:0x00091CCC size:0x50 mapped:0x806D0D60
void fn_3_91CCC(void) {
    void* p = (void*)lbl_803CC1B8;
    if (lbl_3_common_bss_32724.hudOff != 0 || lbl_3_common_bss_32724._CD != 0) {
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x00091D1C size:0x130 mapped:0x806D0DB0
void fn_3_91D1C(void) {
    RepTask* o;
    s32 i;
    fn_80034E20(o = (void*)lbl_803CC1B8, lbl_3_data_F224);
    lbl_80371C30[o->baseIdx + 3].obj->_64 = lbl_3_data_F344[g_d_GameSettings.StadiumID];
    for (i = 0; i < 3; i++) {
        s32 k = g_GameLogic.currentBatterPerTeam[g_GameLogic.awayTeamBattingInd_battingTeam] - (-i);
        s32 m;
        if (k > 9) k -= 9;
        m = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][k][0];
        lbl_80371C30[o->baseIdx - (-5) - (-i)].obj->_5C = inMemRoster[g_GameLogic.teamFielding][m].stats.CharID << 16;
    }
    fn_800363D8(o, 1, 4, 7, g_d_GameSettings.StadiumID);
    lbl_803CC1B8->func = fn_3_91CCC;
}

// .text:0x00091E4C size:0x178 mapped:0x806D0EE0
// NONMATCHING 99%: only the tail differs: original `bge remove; b end`, ours `blt end` after the 0x1A counter check
// (tried goto/else-return/switch fallthrough forms)
#if NONMATCHING
void fn_3_91E4C(void) {
    RepTask* task = (void*)lbl_803CC1B8;
    s32 i;
    s32 v;
    if (lbl_3_common_bss_32724._CD == 0) {
        if (lbl_3_common_bss_32724._CE == 0) {
            return;
        }
        REP_OBJ(task, 0)->_68 = 4;
        REP_OBJ(task, 1)->_68 = 4;
        v = REP_OBJ(task, 1)->_5C >> 16;
        for (i = 0; i < 11; i++) {
            if (v <= lbl_3_data_F200[0][i]) {
                if (i == 0) {
                    REP_OBJ(task, 2)->_68 = 4;
                    REP_OBJ(task, 3)->_68 = 4;
                }
                lbl_80371C30[task->baseIdx + 6 + i].obj->_68 = 4;
                lbl_80371C30[task->baseIdx + 17 + i].obj->_68 = 4;
            }
        }
        task->_1A++;
        if (task->_1A < 45) {
            return;
        }
    }
    fn_80034CEC(task);
    REMOVE_QUEUE_NOARG();
    if (g_GameLogic.gameStatus == 3) {
        lbl_8034E978._26 = 1;
    }
}
#endif

// .text:0x00091FC4 size:0xD14 mapped:0x806D1058
// NONMATCHING 87% (with the two helpers inlined): the original reaches lbl_3_data_EC1C/F200/F430 through the
// pooled lbl_3_data_8D88 base; the helpers stay calls here because the file ends in `dont_inline on`
#if NONMATCHING
static void fn_3_91FC4_digits(RepTask* task, s32 slot, s32 n) {
    if (n >= 99) {
        n = 99;
    }
    if (n < 10) {
        REP_OBJ(task, slot)->_64 = lbl_3_data_EC1C.blankDigitAnim;
        fn_800363D8(task, slot, 1, 0xC4, n);
    } else {
        fn_800363D8(task, slot, 2, 0xC4, n % 10);
        fn_800363D8(task, slot, 1, 0xC4, n / 10);
    }
}

// One line-score column: col 1..9 on screen, showing inning `inning`.
static void fn_3_91FC4_column(RepTask* task, s32 col, s32 inning) {
    s32 n;
    REP_OBJ(task, col + 5)->flags |= 2;
    fn_3_91FC4_digits(task, col + 5, g_Scores.team[0].runs[inning]);
    if (inning < lbl_3_common_bss_32724._CF || (inning == lbl_3_common_bss_32724._CF && lbl_3_common_bss_32724._D0 != 0)) {
        REP_OBJ(task, col + 16)->flags |= 2;
        n = g_Scores.team[1].runs[inning];
        if (n >= 99) {
            n = 99;
        }
        if (n < 10) {
            if (inning >= g_Scores.inning && (g_GameLogic.winType == 3 || g_GameLogic.winType == 6)) {
                fn_800363D8(task, col + 16, 2, 0xC4, 11);
                fn_800363D8(task, col + 16, 1, 0xC4, n);
            } else {
                REP_OBJ(task, col + 16)->_64 = lbl_3_data_EC1C.blankDigitAnim;
                fn_800363D8(task, col + 16, 1, 0xC4, n);
            }
        } else {
            fn_800363D8(task, col + 16, 2, 0xC4, n % 10);
            fn_800363D8(task, col + 16, 1, 0xC4, n / 10);
        }
    } else if (g_GameLogic.gameStatus == 0xE) {
        REP_OBJ(task, col + 16)->flags |= 2;
        REP_OBJ(task, col + 16)->_64 = lbl_3_data_EC1C.blankDigitAnim;
        fn_800363D8(task, col + 16, 1, 0xC4, 10);
    }
}

void fn_3_91FC4(void) {
    RepTask* task = (void*)lbl_803CC1B8;
    s32 extra = 0;
    s32 i;
    s32 col;
    s32 inning;
    s32 shown;
    u8 innings = lbl_3_common_bss_32724._CF;
    if (innings == 12) {
        lbl_3_data_EC1C.lineDescs[0].animId = 0xC9;
        extra = 1;
        lbl_3_data_EC1C.lineDescs[1].animId = 0xC1;
    } else if (innings == 11) {
        lbl_3_data_EC1C.lineDescs[0].animId = 0xC8;
        extra = 1;
        lbl_3_data_EC1C.lineDescs[1].animId = 0xC1;
    } else if (innings == 10) {
        lbl_3_data_EC1C.lineDescs[0].animId = 0xC7;
        extra = 1;
        lbl_3_data_EC1C.lineDescs[1].animId = 0xC1;
    } else if (innings > 5 || g_Scores.maxInnings > 5) {
        lbl_3_data_EC1C.lineDescs[0].animId = 0xC6;
        extra = 1;
        lbl_3_data_EC1C.lineDescs[1].animId = 0xC1;
    } else {
        lbl_3_data_EC1C.lineDescs[0].animId = 0xCA;
        lbl_3_data_EC1C.lineDescs[1].animId = 0xC5;
    }
    fn_80034E20(task, lbl_3_data_EC1C.lineDescs);
    if (extra) {
        REP_OBJ(task, 2)->_72 = lbl_3_data_F200[1][0];
        REP_OBJ(task, 3)->_72 = lbl_3_data_F200[2][0];
        for (i = 0; i < 11; i++) {
            REP_OBJ(task, i + 6)->_72 = lbl_3_data_F200[1][i + 1];
            REP_OBJ(task, i + 17)->_72 = lbl_3_data_F200[2][i + 1];
        }
    }
    REP_OBJ(task, 4)->_64 = lbl_3_data_F430[g_GameLogic.logo[0].captain][0];
    REP_OBJ(task, 5)->_64 = lbl_3_data_F430[g_GameLogic.logo[1].captain][0];
    REP_OBJ(task, 4)->_5C = g_GameLogic.logo[0].variationID << 16;
    REP_OBJ(task, 5)->_5C = g_GameLogic.logo[1].variationID << 16;
    // totals: runs (slots 15/26) and hits (slots 16/27)
    if (lbl_3_common_bss_32724._CF >= 1) {
        REP_OBJ(task, 15)->flags |= 2;
        REP_OBJ(task, 16)->flags |= 2;
        fn_3_91FC4_digits(task, 15, g_Scores.team[0].runs[0]);
        fn_3_91FC4_digits(task, 16, g_Scores.hits[0].runs[0]);
    }
    if (lbl_3_common_bss_32724._CF >= 2 || lbl_3_common_bss_32724._D0 != 0) {
        REP_OBJ(task, 26)->flags |= 2;
        REP_OBJ(task, 27)->flags |= 2;
        fn_3_91FC4_digits(task, 26, g_Scores.team[1].runs[0]);
        fn_3_91FC4_digits(task, 27, g_Scores.hits[1].runs[0]);
    }
    if (lbl_3_common_bss_32724._CF >= 10) {
        // extra innings: innings 10.. first, then a gap, then the remaining early innings
        for (col = 1, inning = 10; col <= 9; col++, inning++) {
            if (inning <= lbl_3_common_bss_32724._CF) {
                shown = inning;
            } else if (inning == lbl_3_common_bss_32724._CF + 1) {
                continue;
            } else {
                shown = col;
            }
            fn_3_91FC4_column(task, col, shown);
        }
    } else {
        for (col = 1; col <= lbl_3_common_bss_32724._CF; col++) {
            fn_3_91FC4_column(task, col, col);
        }
    }
    lbl_3_common_bss_32724._CD = 0;
    lbl_3_common_bss_32724._CE = 0;
    task->_1A = 0;
    lbl_803CC1B8->func = fn_3_91E4C;
}
#endif

// .text:0x00092CD8 size:0x6F4 mapped:0x806D1D6C
void fn_3_92CD8(RepScoreTask* task) {
    s32 team;
    s32 a;
    s32 b;
    s32 done;
    s32 k;
    for (k = 0; k < 2; k++) {
        for (team = 0; team < 2; team++) {
            if (task->score[k][team] >= 100) {
                task->score[k][team] = 99;
            }
        }
    }
    if (task->_1A == 0 && ((REP_OBJ(task, 11)->_5C >> 16) >= 20 || (REP_OBJ(task, 12)->_5C >> 16) >= 20)) {
        for (k = 11; k < 17; k++) {
            lbl_80371C30[task->baseIdx + k].obj->_68 = 0;
            lbl_80371C30[task->baseIdx + k].obj->_5C = 20 << 16;
        }
    }
    for (team = 0; team < 2; team++) {
        if (team == 0) {
            a = 11;
            b = 5;
        } else {
            a = 14;
            b = 8;
        }
        if (task->score[1][team] == task->score[0][team]) {
            if (task->score[0][team] < 10) {
                lbl_80371C30[task->baseIdx + a + 1].obj->flags &= ~2;
                lbl_80371C30[task->baseIdx + a + 2].obj->flags &= ~2;
                lbl_80371C30[task->baseIdx + a].obj->flags |= 2;
                fn_800363D8(task, a, 1, 0xF6, task->score[0][team]);
            } else {
                lbl_80371C30[task->baseIdx + a].obj->flags &= ~2;
                lbl_80371C30[task->baseIdx + a + 1].obj->flags |= 2;
                lbl_80371C30[task->baseIdx + a + 2].obj->flags |= 2;
                fn_800363D8(task, a + 1, 1, 0xF6, task->score[0][team] / 10);
                fn_800363D8(task, a + 2, 1, 0xF6, task->score[0][team] % 10);
            }
            for (k = 0; k < 3; k++) {
                lbl_80371C30[task->baseIdx + a + k].obj->_5C = 20 << 16;
                lbl_80371C30[task->baseIdx + b + k].obj->_5C = 45 << 16;
                lbl_80371C30[task->baseIdx + b + k].obj->flags &= ~2;
            }
        } else {
            done = 0;
            if (task->score[0][team] < 10) {
                lbl_80371C30[task->baseIdx + a].obj->_68 = 1;
                if ((s32)(lbl_80371C30[task->baseIdx + a].obj->_5C >> 16) >= 45) {
                    done = 1;
                    lbl_80371C30[task->baseIdx + a].obj->_68 = 0;
                }
            } else {
                lbl_80371C30[task->baseIdx + a + 1].obj->_68 = 1;
                lbl_80371C30[task->baseIdx + a + 2].obj->_68 = 1;
                if ((lbl_80371C30[task->baseIdx + a + 1].obj->_5C >> 16) >= 45) {
                    done = 1;
                    lbl_80371C30[task->baseIdx + a + 1].obj->_68 = 0;
                    lbl_80371C30[task->baseIdx + a + 2].obj->_68 = 0;
                }
            }
            if (task->score[1][team] < 10) {
                lbl_80371C30[task->baseIdx + b].obj->flags |= 2;
                lbl_80371C30[task->baseIdx + b].obj->_68 = 1;
                fn_800363D8(task, b, 1, 0xF6, task->score[1][team]);
                if ((lbl_80371C30[task->baseIdx + b].obj->_5C >> 16) >= 70) {
                    done++;
                    lbl_80371C30[task->baseIdx + b].obj->_68 = 0;
                }
            } else {
                lbl_80371C30[task->baseIdx + b + 1].obj->flags |= 2;
                lbl_80371C30[task->baseIdx + b + 2].obj->flags |= 2;
                lbl_80371C30[task->baseIdx + b + 1].obj->_68 = 1;
                lbl_80371C30[task->baseIdx + b + 2].obj->_68 = 1;
                fn_800363D8(task, b + 1, 1, 0xF6, task->score[1][team] / 10);
                fn_800363D8(task, b + 2, 1, 0xF6, task->score[1][team] % 10);
                if ((lbl_80371C30[task->baseIdx + b + 1].obj->_5C >> 16) >= 70) {
                    done++;
                    lbl_80371C30[task->baseIdx + b + 1].obj->_68 = 0;
                    lbl_80371C30[task->baseIdx + b + 2].obj->_68 = 0;
                }
            }
            if (done >= 2) {
                task->score[0][team] = task->score[1][team];
            }
        }
    }
}

#pragma dont_inline on
// .text:0x000933CC size:0x178 mapped:0x806D2460
void fn_3_933CC(void) {
    RepScoreTask* o = (void*)lbl_803CC1B8;
    u16 w = o->timer;
    if (w < 0xFFFE) {
        o->timer = w + 1;
    } else {
        o->timer = 0xFFFF;
    }
    if (lbl_3_common_bss_32724.hudOff == 0 && g_GameLogic.gameStatus == 0x13) {
        LayoutSlot* t;
        u16 c;
        fn_3_92CD8(o);
        if (o->_1A == 0) {
            LayoutObj* q = lbl_80371C30[o->baseIdx].obj;
            t = lbl_80371C30;
            if ((q->_5C >> 16) >= 0x15) {
                q->_68 = 0;
                { LayoutSlot* e = t; e += o->baseIdx; e[3].obj->_68 = 0; }
                { LayoutSlot* e = t; e += o->baseIdx; e[4].obj->_68 = 0; }
                o->_1A = 1;
            }
        }
        c = o->timer;
        if (c >= 0x1E && (c - 0x1E) % 27 == 0) {
            if (o->score[1][g_GameLogic.homeTeamBattingInd_fieldingTeam] < g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0]) {
                o->score[1][g_GameLogic.homeTeamBattingInd_fieldingTeam]++;
            }
        }
    } else {
        fn_80034CEC(o);
        REMOVE_QUEUE_NOARG();
        lbl_3_common_bss_32724._C5 = 0;
    }
}

#pragma dont_inline on
// .text:0x00093544 size:0x144 mapped:0x806D25D8
void fn_3_93544(void) {
    RepScoreTask* o;
    fn_80034E20(o = (void*)lbl_803CC1B8, lbl_3_data_EC1C.scoreDescs);
    lbl_80371C30[o->baseIdx + 1].obj->_64 = lbl_3_data_F430[g_GameLogic.logo[0].captain][1];
    lbl_80371C30[o->baseIdx + 2].obj->_64 = lbl_3_data_F430[g_GameLogic.logo[1].captain][1];
    lbl_80371C30[o->baseIdx + 1].obj->_5C = g_GameLogic.logo[0].variationID << 16;
    lbl_80371C30[o->baseIdx + 2].obj->_5C = g_GameLogic.logo[1].variationID << 16;
    if (g_GameLogic.homeTeamBattingInd_fieldingTeam == 0) {
        o->score[0][0] = g_Scores._A0;
        o->score[0][1] = g_Scores.team[1].runs[0];
    } else {
        o->score[0][0] = g_Scores.team[0].runs[0];
        o->score[0][1] = g_Scores._A0;
    }
    o->score[1][0] = o->score[0][0];
    o->score[1][1] = o->score[0][1];
    fn_3_92CD8(o);
    o->timer = 0;
    o->_1A = 0;
    lbl_803CC1B8->func = fn_3_933CC;
}

#pragma dont_inline reset
// .text:0x00093688 size:0x2D8 mapped:0x806D271C
void fn_3_93688(RepTask* task) {
    s32 n;
    if (g_Scores.team[0].runs[0] >= 10) {
        n = g_Scores.team[0].runs[0];
        if (n >= 99) {
            n = 99;
        }
        REP_OBJ(task, 4)->flags &= ~2;
        REP_OBJ(task, 5)->flags |= 2;
        REP_OBJ(task, 6)->flags |= 2;
        fn_8003649C(task, 5, 2, 0xF6, n / 10);
        fn_8003649C(task, 6, 3, 0xF6, n % 10);
    } else {
        REP_OBJ(task, 4)->flags |= 2;
        REP_OBJ(task, 5)->flags &= ~2;
        REP_OBJ(task, 6)->flags &= ~2;
        fn_8003649C(task, 4, 1, 0xF6, g_Scores.team[0].runs[0]);
    }
    n = g_Scores.team[1].runs[0];
    if (n >= 10) {
        if (n >= 99) {
            n = 99;
        }
        REP_OBJ(task, 7)->flags &= ~2;
        REP_OBJ(task, 8)->flags |= 2;
        REP_OBJ(task, 9)->flags |= 2;
        fn_8003649C(task, 8, 5, 0xF6, n / 10);
        fn_8003649C(task, 9, 6, 0xF6, n % 10);
    } else {
        REP_OBJ(task, 7)->flags |= 2;
        REP_OBJ(task, 8)->flags &= ~2;
        REP_OBJ(task, 9)->flags &= ~2;
        fn_8003649C(task, 7, 4, 0xF6, g_Scores.team[1].runs[0]);
    }
}

// .text:0x00093960 size:0x3FC mapped:0x806D29F4
void fn_3_93960(void) {
    RepTask* task = (void*)lbl_803CC1B8;
    if (lbl_3_common_bss_32724._98 == 2) {
        lbl_3_common_bss_32724._98 = 1;
        task->timer = 0;
    }
    if (task->timer < 0xFFFE) {
        task->timer++;
    } else {
        task->timer = 0xFFFF;
    }
    if (lbl_3_common_bss_32724.hudOff == 0 && (g_GameLogic.gameStatus != 3 || g_GameLogic._125 != 9) &&
        (g_GameLogic.gameStatus != 9 || g_GameLogic._125 != 4) &&
        (g_GameLogic.gameStatus != 5 || (g_GameLogic._125 != 0xA && g_GameLogic._125 != 0xB)) &&
        ((g_UnkSound_32718._07 != 7 && g_UnkSound_32718._07 != 0x14) || task->timer <= 30) &&
        g_GameLogic.gameStatus != 8 && g_GameLogic.gameStatus != 6 && (g_GameLogic.gameStatus != 2 || task->timer <= 90)) {
        s32 n = g_Scores.team[0].runs[0];
        if (n >= 10) {
            if (n >= 99) {
                n = 99;
            }
            REP_OBJ(task, 4)->flags &= ~2;
            REP_OBJ(task, 5)->flags |= 2;
            REP_OBJ(task, 6)->flags |= 2;
            fn_8003649C(task, 5, 2, 0xF6, n / 10);
            fn_8003649C(task, 6, 3, 0xF6, n % 10);
        } else {
            REP_OBJ(task, 4)->flags |= 2;
            REP_OBJ(task, 5)->flags &= ~2;
            REP_OBJ(task, 6)->flags &= ~2;
            fn_8003649C(task, 4, 1, 0xF6, g_Scores.team[0].runs[0]);
        }
        n = g_Scores.team[1].runs[0];
        if (n >= 10) {
            if (n >= 99) {
                n = 99;
            }
            REP_OBJ(task, 7)->flags &= ~2;
            REP_OBJ(task, 8)->flags |= 2;
            REP_OBJ(task, 9)->flags |= 2;
            fn_8003649C(task, 8, 5, 0xF6, n / 10);
            fn_8003649C(task, 9, 6, 0xF6, n % 10);
        } else {
            REP_OBJ(task, 7)->flags |= 2;
            REP_OBJ(task, 8)->flags &= ~2;
            REP_OBJ(task, 9)->flags &= ~2;
            fn_8003649C(task, 7, 4, 0xF6, g_Scores.team[1].runs[0]);
        }
        return;
    }
    lbl_3_common_bss_32724._98 = 0;
    fn_80034CEC(task);
    REMOVE_QUEUE_NOARG();
}

// .text:0x00093D5C size:0x3E0 mapped:0x806D2DF0
// NONMATCHING 98%: same instructions; the 3<<16 constant and the slot-7..9 bases get r28/r29-r31 instead of r31/r28-r30
#if NONMATCHING
void fn_3_93D5C(void) {
    RepTask* task = (void*)lbl_803CC1B8;
    s32 n;
    fn_80034E20(task, lbl_3_data_EABC);
    REP_OBJ(task, 2)->_64 = lbl_3_data_F430[g_GameLogic.logo[0].captain][1];
    REP_OBJ(task, 3)->_64 = lbl_3_data_F430[g_GameLogic.logo[1].captain][1];
    REP_OBJ(task, 2)->_5C = g_GameLogic.logo[0].variationID << 16;
    REP_OBJ(task, 3)->_5C = g_GameLogic.logo[1].variationID << 16;
    REP_OBJ(task, 4)->_5C = 0 << 16;
    REP_OBJ(task, 5)->_5C = 1 << 16;
    REP_OBJ(task, 6)->_5C = 2 << 16;
    REP_OBJ(task, 7)->_5C = 3 << 16;
    REP_OBJ(task, 8)->_5C = 4 << 16;
    REP_OBJ(task, 9)->_5C = 5 << 16;
    n = g_Scores.team[0].runs[0];
    if (n >= 10) {
        if (n >= 99) {
            n = 99;
        }
        REP_OBJ(task, 4)->flags &= ~2;
        REP_OBJ(task, 5)->flags |= 2;
        REP_OBJ(task, 6)->flags |= 2;
        fn_8003649C(task, 5, 2, 0xF6, n / 10);
        fn_8003649C(task, 6, 3, 0xF6, n % 10);
    } else {
        REP_OBJ(task, 4)->flags |= 2;
        REP_OBJ(task, 5)->flags &= ~2;
        REP_OBJ(task, 6)->flags &= ~2;
        fn_8003649C(task, 4, 1, 0xF6, g_Scores.team[0].runs[0]);
    }
    n = g_Scores.team[1].runs[0];
    if (n >= 10) {
        if (n >= 99) {
            n = 99;
        }
        REP_OBJ(task, 7)->flags &= ~2;
        REP_OBJ(task, 8)->flags |= 2;
        REP_OBJ(task, 9)->flags |= 2;
        fn_8003649C(task, 8, 5, 0xF6, n / 10);
        fn_8003649C(task, 9, 6, 0xF6, n % 10);
    } else {
        REP_OBJ(task, 7)->flags |= 2;
        REP_OBJ(task, 8)->flags &= ~2;
        REP_OBJ(task, 9)->flags &= ~2;
        fn_8003649C(task, 7, 4, 0xF6, g_Scores.team[1].runs[0]);
    }
    lbl_3_common_bss_32724._98 = 1;
    task->timer = 0;
    lbl_803CC1B8->func = fn_3_93960;
}
#endif

// .text:0x0009413C size:0x58 mapped:0x806D31D0
void fn_3_9413C(void) {
    void* p = (void*)lbl_803CC1B8;
    if (lbl_3_common_bss_32724.hudOff != 0 || g_GameLogic.gameStatus != 9) {
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x00094194 size:0x574 mapped:0x806D3228
void fn_3_94194(void) {
    RepTask* task = (void*)lbl_803CC1B8;
    s32 i;
    s32 n;
    fn_80034E20(task, lbl_3_data_E85C);
    if (g_Scores.team[0].runs[0] == g_Scores.team[1].runs[0]) {
        REP_OBJ(task, 9)->_64 = 0xE6;
    }
    if (g_GameLogic.winType != 5 && g_GameLogic.winType != 6) {
        REP_OBJ(task, 17)->flags &= ~2;
    }
    for (i = 0; i < 3; i++) {
        lbl_80371C30[3 + task->baseIdx + i].obj->_64 = lbl_3_data_F430[g_GameLogic.logo[0].captain][1];
        lbl_80371C30[6 + task->baseIdx + i].obj->_64 = lbl_3_data_F430[g_GameLogic.logo[1].captain][1];
        lbl_80371C30[3 + task->baseIdx + i].obj->_5C = g_GameLogic.logo[0].variationID << 16;
        lbl_80371C30[6 + task->baseIdx + i].obj->_5C = g_GameLogic.logo[1].variationID << 16;
    }
    if (g_Scores.team[0].runs[0] < 10) {
        REP_OBJ(task, 10)->flags &= ~2;
        fn_800363D8(task, 11, 1, 0xF6, g_Scores.team[0].runs[0]);
    } else {
        n = g_Scores.team[0].runs[0];
        if (n > 99) {
            n = 99;
        }
        fn_800363D8(task, 10, 1, 0xF6, n / 10);
        fn_800363D8(task, 11, 1, 0xF6, n % 10);
    }
    if (g_Scores.team[1].runs[0] < 10) {
        if (g_GameLogic.winType == 3 || g_GameLogic.winType == 6) {
            fn_800363D8(task, 12, 1, 0xF6, g_Scores.team[1].runs[0]);
            fn_800363D8(task, 13, 1, 0xF6, 10);
        } else {
            fn_800363D8(task, 12, 1, 0xF6, g_Scores.team[1].runs[0]);
            REP_OBJ(task, 13)->flags &= ~2;
        }
    } else {
        n = g_Scores.team[1].runs[0];
        if (n > 99) {
            n = 99;
        }
        fn_800363D8(task, 12, 1, 0xF6, n / 10);
        fn_800363D8(task, 13, 1, 0xF6, n % 10);
    }
    if (g_Scores._A4 == 0) {
        REP_OBJ(task, 1)->_64 = 0xEC;
        REP_OBJ(task, 2)->_64 = 0xE9;
        REP_OBJ(task, 15)->flags &= ~2;
        REP_OBJ(task, 4)->flags |= 2;
        REP_OBJ(task, 5)->flags |= 2;
    } else if (g_Scores._A4 == 1) {
        REP_OBJ(task, 1)->_64 = 0xE8;
        REP_OBJ(task, 2)->_64 = 0xED;
        REP_OBJ(task, 16)->flags &= ~2;
        REP_OBJ(task, 7)->flags |= 2;
        REP_OBJ(task, 8)->flags |= 2;
    } else {
        for (i = 10; i < 14; i++) {
            lbl_80371C30[task->baseIdx + i].obj->_64 = 0xEA;
        }
        REP_OBJ(task, 1)->_64 = 0xE3;
        REP_OBJ(task, 2)->_64 = 0xE4;
        REP_OBJ(task, 14)->flags &= ~2;
        REP_OBJ(task, 15)->flags &= ~2;
        REP_OBJ(task, 16)->flags &= ~2;
    }
    lbl_803CC1B8->func = fn_3_9413C;
}

// .text:0x00094708 size:0x58 mapped:0x806D379C
void fn_3_94708(void) {
    void* p = (void*)lbl_803CC1B8;
    if (lbl_3_common_bss_32724.hudOff != 0 || g_GameLogic._125 > 9) {
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x00094760 size:0x158 mapped:0x806D37F4
// NONMATCHING 98%: only the scheduling of `li r6,0x25` / `li r4,5` (original hoists them above the first stores)
#if NONMATCHING
void fn_3_94760(void) {
    RepTask* task;
    fn_80034E20(task = (void*)lbl_803CC1B8, lbl_3_data_E75C);
    REP_OBJ(task, 3)->_64 = lbl_3_data_F430[g_GameLogic.logo[0].captain][0];
    REP_OBJ(task, 4)->_64 = lbl_3_data_F430[g_GameLogic.logo[1].captain][0];
    REP_OBJ(task, 3)->_5C = g_GameLogic.logo[0].variationID << 16;
    REP_OBJ(task, 4)->_5C = g_GameLogic.logo[1].variationID << 16;
    fn_800363D8(task, 5, 1, 0x25, g_GameLogic.teams[g_GameLogic._000] + g_GameLogic._13E[g_GameLogic._000] * 4);
    fn_800363D8(task, 6, 1, 0x25, g_GameLogic.teams[g_GameLogic._000 ^ 1] + g_GameLogic._13E[g_GameLogic._000 ^ 1] * 4);
    lbl_803CC1B8->func = fn_3_94708;
}
#endif

// .text:0x000948B8 size:0x78 mapped:0x806D394C
void fn_3_948B8(void) {
    RepTask* p = (void*)lbl_803CC1B8;
    if (lbl_3_common_bss_32724.hudOff != 0 || g_GameLogic.gameStatus != 0x17 || lbl_80371C30[p->baseIdx].obj->_69 == 2) {
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x00094930 size:0x4C mapped:0x806D39C4
void fn_3_94930(void) {
    fn_80034E20((void*)lbl_803CC1B8, lbl_3_data_F3F0);
    lbl_803CC1B8->func = fn_3_948B8;
}

// .text:0x0009497C size:0x248 mapped:0x806D3A10
void fn_3_9497C(void) {
    RepTask* task = (void*)lbl_803CC1B8;
    u16 mode;
    s32 i;
    s32 j;
    LayoutObj* obj;

    if (lbl_3_common_bss_32724.hudOff != 0) {
        goto remove;
    }
    if (g_UnkSound_32718._07 == 0 || g_GameLogic.gameStatus == 1) {
        REP_OBJ(task, 0)->_68 = 1;
        REP_OBJ(task, 2)->_68 = 1;
        REP_OBJ(task, 3)->_68 = 1;
        REP_OBJ(task, 4)->_68 = 1;
        REP_OBJ(task, 5)->_68 = 1;
    }
    mode = task->_1C;
    if (mode == 2) {
        if (lbl_3_common_bss_32724._B4 == 0) {
            goto remove;
        }
    } else if (mode != 0) {
        if (g_GameLogic.gameStatus != 0x16) {
            goto remove;
        }
    } else if (lbl_3_common_bss_32724._B3 == 0) {
        goto remove;
    }
    if (mode != 2) {
        for (i = 0; i < task->_1A; i++) {
            for (j = 1; j < 6; j++) {
                obj = lbl_80371C30[task->baseIdx + (lbl_3_data_E758[i] + j)].obj;
                if (obj->_5C >> 16 > 40) {
                    lbl_80371C30[task->baseIdx + (lbl_3_data_E758[i] + j)].obj->_5C = 60 << 16;
                }
            }
        }
    }
    return;
    remove:
    fn_80034CEC(task);
    REMOVE_QUEUE_NOARG();
}

// .text:0x00094BC4 size:0x2A4 mapped:0x806D3C58
// NONMATCHING 99% (raw-offset version; this typed rewrite allocates registers differently): only the loop-setup
// copies differed (original `addi r7,r4,bss@l` / `addi r8,r3,DATA@l` direct; ours added `mr r7,r4` / `mr r8,r0`)
#if NONMATCHING
void fn_3_94BC4(void) {
    RepTask* task = (void*)lbl_803CC1B8;
    StarChanceSlot* e;
    u8* order;
    s32 i;
    s32 j;
    s32 n;
    s32 first;
    s32 k;
    if (lbl_3_common_bss_32724._B4 != 0) {
        task->_1C = 2;
    } else if (g_GameLogic.gameStatus == 0x16) {
        task->_1C = 1;
    } else {
        task->_1C = 0;
    }
    fn_80034E20(task, lbl_3_data_E378);
    e = lbl_3_common_bss_37400.slots;
    order = lbl_3_data_E758;
    n = 0;
    for (i = 0; i < 9; i++, e++) {
        if (e->active == 0) {
            continue;
        }
        first = *order;
        lbl_80371C30[task->baseIdx + first].obj->_5C = e->charID << 16;
        for (j = 0; j < 5; j++) {
            k = first + j + 1;
            if (j >= e->target) {
                lbl_80371C30[task->baseIdx + k].obj->flags &= ~2;
            } else {
                lbl_80371C30[task->baseIdx + k].obj->flags |= 2;
                lbl_80371C30[task->baseIdx + k].obj->_68 = 0;
                lbl_80371C30[task->baseIdx + k].obj->_5C = 0;
                if (j < e->achieved) {
                    lbl_80371C30[task->baseIdx + k].obj->_5C = 1 << 16;
                } else if (j < e->bonus + e->achieved) {
                    if (task->_1C == 2) {
                        lbl_80371C30[task->baseIdx + k].obj->_5C = 40 << 16;
                    } else {
                        lbl_80371C30[task->baseIdx + k].obj->_5C = 60 << 16;
                    }
                    lbl_80371C30[task->baseIdx + k].obj->_68 = 1;
                }
            }
        }
        order++;
        n++;
    }
    if (n < 0) {
        // unreachable (n >= 0); the original calls fn_800B0A14_removeQueue with a stale r3 here
        fn_800B0A14_removeQueue(task);
        return;
    }
    REP_OBJ(task, 1)->_5C = (n - 1) << 16;
    task->_1A = n;
    lbl_803CC1B8->func = fn_3_9497C;
}
#endif

// .text:0x00094E68 size:0x198 mapped:0x806D3EFC
void fn_3_94E68(void) {
    RepTask* p = (void*)lbl_803CC1B8;
    u8 g;
    if (lbl_3_common_bss_32724.hudOff == 0 && (p->_1C == lbl_3_common_bss_37400.type || lbl_3_common_bss_37400._47 == 2) &&
        (g = g_GameLogic.gameStatus) != 3 && (g != 8 || lbl_3_common_bss_37400._47 == 0) && (g != 0 || lbl_3_common_bss_37400._47 != 2)) {
        if (g_Stats.replayInd != 0) {
            LayoutSlot* t = lbl_80371C30;
            t[p->baseIdx].obj->flags &= ~2;
            t[p->baseIdx + 1].obj->flags &= ~2;
        } else if (g <= 1 || g == 2) {
            LayoutSlot* t = lbl_80371C30;
            t[p->baseIdx].obj->flags |= 2;
            t[p->baseIdx + 1].obj->flags |= 2;
        } else {
            LayoutSlot* t = lbl_80371C30;
            t[p->baseIdx].obj->flags &= ~2;
            t[p->baseIdx + 1].obj->flags &= ~2;
        }
        return;
    }
    fn_80034CEC(p);
    REMOVE_QUEUE_NOARG();
}

// .text:0x00095000 size:0x98 mapped:0x806D4094
void fn_3_95000(void) {
    RepTask* p;
    fn_80034E20(p = (void*)lbl_803CC1B8, lbl_3_data_E2F8);
    {
        LayoutSlot* t = lbl_80371C30;
        s32 v = lbl_3_data_E200[lbl_3_common_bss_37400.type];
        t[p->baseIdx + 2].obj->_5C = v << 16;
    }
    p->_1C = lbl_3_common_bss_37400.type;
    lbl_803CC1B8->func = fn_3_94E68;
}

// .text:0x00095098 size:0x8C mapped:0x806D412C
void fn_3_95098(void) {
    RepTask* p = (void*)lbl_803CC1B8;
    if (lbl_3_common_bss_32724.hudOff != 0 || lbl_80371C30[p->baseIdx].obj->_69 == 2) {
        fn_800B0A5C_insertQueue(fn_3_95000, 2);
        lbl_3_common_bss_32724._B3 = 0;
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x00095124 size:0x90 mapped:0x806D41B8
void fn_3_95124(void) {
    RepTask* p;
    fn_80034E20(p = (void*)lbl_803CC1B8, lbl_3_data_E278);
    {
        LayoutSlot* t = lbl_80371C30;
        s32 v = lbl_3_data_E200[lbl_3_common_bss_37400.type];
        t[p->baseIdx + 2].obj->_5C = v << 16;
    }
    lbl_803CC1B8->func = fn_3_95098;
}

// .text:0x000951B4 size:0x128 mapped:0x806D4248
void fn_3_951B4(void) {
    RepTask* p = (void*)lbl_803CC1B8;
    if (g_Ball.deadBallReason == 1) {
        if (g_GameLogic.gameStatus == 0x14) {
            lbl_80371C30[p->baseIdx].obj->_68 = 1;
        }
        if (g_GameLogic.gameStatus == 2 || g_GameLogic.gameStatus == 0x14) {
            return;
        }
    } else {
        if (g_UnkSound_32718._07 == 0 || g_GameLogic.gameStatus == 1) {
            lbl_80371C30[p->baseIdx].obj->_68 = 1;
        }
        if (lbl_3_common_bss_32724.hudOff == 0 && lbl_3_common_bss_37400._42 != 0) {
            if (g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 2) {
                return;
            }
        }
    }
    lbl_3_common_bss_32724._B4 = 0;
    fn_80034CEC(p);
    REMOVE_QUEUE_NOARG();
}

// .text:0x000952DC size:0xB0 mapped:0x806D4370
void fn_3_952DC(void) {
    RepTask* p = (void*)lbl_803CC1B8;
    if (lbl_3_common_bss_32724._B5 != 0) {
        REMOVE_QUEUE_NOARG();
        return;
    }
    fn_80034E20(p, lbl_3_data_E21C);
    if (lbl_3_common_bss_37400._47 == 1) {
        LayoutSlot* t = lbl_80371C30;
        t[p->baseIdx].obj->_64 = 0x5A;
    }
    lbl_3_common_bss_32724._B5 = 1;
    lbl_803CC1B8->func = fn_3_951B4;
}

// .text:0x0009538C size:0x70 mapped:0x806D4420
void fn_3_9538C(void) {
    RepTask* p = (void*)lbl_803CC1B8;
    if (lbl_3_common_bss_32724.hudOff != 0 || g_GameLogic.gameStatus != 0x16) {
        fn_800B0A5C_insertQueue(fn_3_95000, 2);
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x000953FC size:0xC8 mapped:0x806D4490
void fn_3_953FC(void) {
    RepTask* p;
    fn_80034E20(p = (void*)lbl_803CC1B8, lbl_3_data_E160);
    {
        LayoutSlot* t = lbl_80371C30;
        s32 v = lbl_3_data_E200[lbl_3_common_bss_37400.type];
        t[p->baseIdx + 2].obj->_5C = v << 16;
    }
    {
        LayoutSlot* t = lbl_80371C30;
        s32 v = lbl_3_data_E200[lbl_3_common_bss_37400.type];
        t[p->baseIdx + 3].obj->_5C = v << 16;
    }
    lbl_3_common_bss_32724._B4 = 0;
    lbl_3_common_bss_32724._B3 = 0;
    lbl_803CC1B8->func = fn_3_9538C;
}

// .text:0x000954C4 size:0x58 mapped:0x806D4558
void fn_3_954C4(void) {
    RepTask* p = (void*)lbl_803CC1B8;
    if (lbl_3_common_bss_32724.hudOff != 0 || g_GameLogic.gameStatus != 0x16) {
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x0009551C size:0x4C mapped:0x806D45B0
void fn_3_9551C(void) {
    fn_80034E20((void*)lbl_803CC1B8, lbl_3_data_E120);
    lbl_803CC1B8->func = fn_3_954C4;
}

// .text:0x00095568 size:0x64 mapped:0x806D45FC
void fn_3_95568(void) {
    RepTask* p = (void*)lbl_803CC1B8;
    if (lbl_3_common_bss_32724.hudOff != 0 || lbl_80371C30[p->baseIdx].obj->_69 == 2) {
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x000955CC size:0x54 mapped:0x806D4660
void fn_3_955CC(void) {
    fn_80034E20((void*)lbl_803CC1B8, lbl_3_data_E0E0);
    playSoundEffect(0x1A9);
    lbl_803CC1B8->func = fn_3_95568;
}

// .text:0x00095620 size:0x350 mapped:0x806D46B4
// NONMATCHING 97%: original loads the -2.0f / int->float constants through `addi rN; lfs 0(rN)` and schedules the two conversions differently
#if NONMATCHING
void fn_3_95620(void) {
    RepTask* task = (void*)lbl_803CC1B8;
    RepFielderView* f;
    int sx;
    int sy;
    s16 idx;
    if (lbl_3_common_bss_32724.hudOff != 0) {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 2) {
        if (g_GameLogic.secondaryGameMode == 0xD || (u8)(g_GameLogic.secondaryGameMode - 0xE) <= 1 || g_GameLogic.secondaryGameMode == 0x10) {
            if (g_Practice._186 != 0) {
                REP_OBJ(task, 0)->flags &= ~2;
                return;
            }
        } else {
            REP_OBJ(task, 0)->flags &= ~2;
            return;
        }
    }
    if (g_Stats.replayInd != 0) {
        REP_OBJ(task, 0)->flags &= ~2;
        return;
    }
    if (g_GameLogic.gameStatus != 2) {
        REP_OBJ(task, 0)->flags &= ~2;
        return;
    }
    if (g_GameLogic.sceneID == 1) {
        REP_OBJ(task, 0)->flags &= ~2;
        return;
    }
    if (g_GameLogic._13E[g_GameLogic.teamFielding] != 0) {
        REP_OBJ(task, 0)->flags &= ~2;
        return;
    }
    if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0 && g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
        REP_OBJ(task, 0)->flags &= ~2;
        return;
    }
    if (g_FieldingLogic._139 != 0) {
        REP_OBJ(task, 0)->flags &= ~2;
        return;
    }
    idx = g_FieldingLogic._0B0;
    if (idx < 0) {
        REP_OBJ(task, 0)->flags &= ~2;
        return;
    }
    REP_OBJ(task, 0)->flags |= 2;
    f = &g_Fielders[idx];
    fn_3_1650C(&sx, &sy, FALSE, f->x, -2.0f - f->_00C, f->z);
    REP_OBJ(task, 0)->x = sx;
    REP_OBJ(task, 0)->y = sy;
    REP_OBJ(task, 0)->color = (REP_OBJ(task, 0)->color & 0xFF) | 0xFFFFFF00;
}
#endif

// .text:0x00095970 size:0x4C mapped:0x806D4A04
void fn_3_95970(void) {
    fn_80034E20((void*)lbl_803CC1B8, lbl_3_data_C1EC);
    lbl_803CC1B8->func = fn_3_95620;
}

// .text:0x000959BC size:0xCE0 mapped:0x806D4A50
// NONMATCHING 91%: (with the alpha helper pasted in by hand; it stays a call here because the file ends in
// `dont_inline on`) block layout of the i == 0 runner case, a few `+1` slot offsets folded into lwz, regalloc
#if NONMATCHING
static inline void fn_3_959BC_setAlpha(RepFieldHudTask* task, s32 alpha) {
    s32 i;
    if (g_d_GameSettings.GameModeSelected == 6) {
        for (i = 1; i < 6; i++) {
            lbl_80371C30[task->baseIdx + i].obj->color = alpha | (lbl_80371C30[task->baseIdx + i].obj->color & ~0xFF);
        }
    } else {
        for (i = 1; i < 14; i++) {
            lbl_80371C30[task->baseIdx + i].obj->color = alpha | (lbl_80371C30[task->baseIdx + i].obj->color & ~0xFF);
        }
    }
}

void fn_3_959BC(void) {
    RepFieldHudTask* task = (void*)lbl_803CC1B8;
    s32 i;
    s32 any;
    s32 phase;
    s32 digit;
    s32 slot;
    s32 alpha;
    u8 status;
    InMemRunnerType* r;
    f32 sx;
    f32 sy;
    if (task->timer < 0xFFFE) {
        task->timer++;
    } else {
        task->timer = 0xFFFF;
    }
    if (lbl_3_common_bss_32724.hudOff != 0 ||
        (g_d_GameSettings.GameModeSelected == 2 && (g_Practice.tutorialState == 0 || g_Practice._1C7 != 0))) {
        goto remove;
    }
    if (task->blinkTimer != 0) {
        if (task->blinkTimer < 0xFFFE) {
            task->blinkTimer++;
        } else {
            task->blinkTimer = 0xFFFF;
        }
    }
    if (g_d_GameSettings.GameModeSelected == 6) {
        if (g_Minigame.framesSincePanelHit == 1) {
            any = 0;
            for (i = 0; i < 4; i++) {
                if (g_Minigame._191C[i] > i) {
                    any = 1;
                }
            }
            if (any) {
                task->blinkTimer = 1;
            }
        }
        if (task->blinkTimer != 0) {
            for (i = 1; i < 5; i++) {
                lbl_80371C30[task->baseIdx + i].obj->flags &= ~2;
            }
            phase = (task->blinkTimer - 1) % 45;
            if (phase == 0) {
                for (i = 0; i < 4; i++) {
                    digit = task->progress[i] % 10;
                    if (digit == 4) {
                        task->progress[i] = 14;
                    } else if (digit < g_Minigame._191C[i]) {
                        task->progress[i]++;
                        lbl_80371C30[(task->progress[i] % 10) % 4 + task->baseIdx + 1].obj->flags |= 2;
                    } else if (digit > 0 && digit < 4 && digit == g_Minigame._191C[i]) {
                        lbl_80371C30[digit % 4 + task->baseIdx + 1].obj->flags |= 2;
                        if (task->progress[i] < 10) {
                            task->progress[i] += 10;
                        }
                    }
                }
            }
            for (i = 0; i < 4; i++) {
                slot = (task->progress[i] % 10) % 4 + 1;
                if (task->progress[i] <= g_Minigame._191C[i]) {
                    if (slot == 1) {
                        lbl_80371C30[task->baseIdx + slot].obj->flags |= 2;
                    } else if (phase <= 15 || phase > 30) {
                        lbl_80371C30[task->baseIdx + slot].obj->flags |= 2;
                    }
                    g_Minigame._1925 |= 1 << (slot - 1);
                } else if (task->progress[i] >= 10) {
                    g_Minigame._1925 |= 1 << (slot - 1);
                    lbl_80371C30[task->baseIdx + slot].obj->flags |= 2;
                }
            }
        }
    } else {
        // runner markers (slots 1-4) and occupied-base markers (slots 9-11)
        lbl_80371C30[task->baseIdx + 9].obj->flags &= ~2;
        lbl_80371C30[task->baseIdx + 10].obj->flags &= ~2;
        lbl_80371C30[task->baseIdx + 11].obj->flags &= ~2;
        r = g_Runners;
        for (i = 0; i < 4; i++, r++) {
            status = r->runnerOnFieldOrOutOrScored;
            if (status != 1 || g_Strikes.outs >= 3) {
                lbl_80371C30[task->baseIdx + (i + 1)].obj->flags &= ~2;
                continue;
            }
            if (i == 0) {
                if (g_Ball.framesSinceHit < 1) {
                    lbl_80371C30[task->baseIdx + (i + 1)].obj->flags &= ~2;
                    continue;
                }
                if (status == 1 || status == 5) {
                    if (g_Ball.framesSinceHit < 16) {
                        lbl_80371C30[task->baseIdx + (i + 1)].obj->color =
                            (g_Ball.framesSinceHit * 16) | (lbl_80371C30[task->baseIdx + (i + 1)].obj->color & ~0xFF);
                    } else {
                        lbl_80371C30[task->baseIdx + (i + 1)].obj->color = (lbl_80371C30[task->baseIdx + (i + 1)].obj->color & ~0xFF) | 0xFF;
                    }
                }
            } else {
                lbl_80371C30[task->baseIdx + (i + 1)].obj->color = (lbl_80371C30[task->baseIdx + (i + 1)].obj->color & ~0xFF) | 0xFF;
            }
            lbl_80371C30[task->baseIdx + (i + 1)].obj->flags |= 2;
            sx = lbl_3_data_C1CC[2] * r->position.x;
            sy = lbl_3_data_C1CC[3] * -r->position.z;
            lbl_80371C30[task->baseIdx + (i + 1)].obj->x = sx + lbl_3_data_C1CC[0];
            lbl_80371C30[task->baseIdx + (i + 1)].obj->y = sy + lbl_3_data_C1CC[1];
            if (r->currentBase >= 1 && r->currentBase <= 3) {
                lbl_80371C30[task->baseIdx + r->currentBase + 8].obj->flags |= 2;
            }
        }
        // steal indicator (slot 12)
        REP_OBJ(task, 12)->flags &= ~2;
        if (g_GameLogic.sceneID == 1) {
            for (i = 1; i < 4; i++) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored != 0 && g_Runners[i].furthestBaseForcedToGoToOnWalk != 0) {
                    REP_OBJ(task, 12)->flags |= 2;
                    for (; i < 4; i++) {
                        if (g_Runners[i].stealingStatus == 3) {
                            break;
                        }
                    }
                    if (i < 4) {
                        REP_OBJ(task, 12)->_64 = 0xA2;
                    } else {
                        REP_OBJ(task, 12)->_64 = 0xA6;
                    }
                    break;
                }
            }
        }
        // CPU-batting indicator (slot 13)
        REP_OBJ(task, 13)->flags &= ~2;
        if (g_d_GameSettings.GameModeSelected != 2 && g_GameLogic._13E[g_GameLogic.teamBatting] == 0 &&
            g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] != 0) {
            REP_OBJ(task, 13)->flags |= 2;
        }
    }
    if (task->timer <= 16) {
        alpha = task->timer * 16;
        if (alpha > 0xFF) {
            alpha = 0xFF;
        }
        fn_3_959BC_setAlpha(task, alpha);
    }
    if (lbl_3_common_bss_34C90._1D5 != 0 && g_d_GameSettings.GameModeSelected != 6) {
        alpha = 0xF0 - lbl_3_common_bss_34C90._00C * 16;
        if (alpha <= 0) {
            goto remove;
        }
        fn_3_959BC_setAlpha(task, alpha);
    }
    if (g_GameLogic.hudLoadingRelated == 0 && g_GameLogic.gameStatus != 3 && g_GameLogic.gameStatus != 0xE &&
        g_GameLogic.secondaryGameMode != 0xA) {
        return;
    }
remove:
    lbl_3_common_bss_32724._C7 = 0;
    fn_80034CEC(task);
    REMOVE_QUEUE_NOARG();
}
#endif

// .text:0x0009669C size:0x278 mapped:0x806D5730
void fn_3_9669C(void) {
    RepFieldHudTask* o = (void*)lbl_803CC1B8;
    s32 k;
    InMemRunnerType* r;
    if (g_d_GameSettings.GameModeSelected == 6) {
        fn_80034E20(o, lbl_3_data_8D88);
        for (k = 1; k < 4; k++) {
            if (g_Minigame._1914[k] != 0) {
                LayoutObj* e = lbl_80371C30[o->baseIdx - (-1) - (-k)].obj;
                e->flags |= 2;
                lbl_80371C30[o->baseIdx - (-1) - (-k)].obj->_68 = 0;
                o->progress[k] = k;
            } else {
                o->progress[k] = 9;
            }
            lbl_80371C30[o->baseIdx - (-1) - (-k)].obj->_5C = (k - 1) << 16;
        }
        if (g_Minigame._19A2 != 0) {
            LayoutSlot* e = lbl_80371C30;
            e += o->baseIdx;
            e[5].obj->flags |= 2;
        }
    } else {
        fn_80034E20(o, lbl_3_data_BFEC);
        REP_SLOT_OBJ(o->baseIdx + 9)->_5C = 0;
        REP_SLOT_OBJ(o->baseIdx + 0xA)->_5C = 0x10000;
        REP_SLOT_OBJ(o->baseIdx + 0xB)->_5C = 0x20000;
        r = g_Runners;
        for (k = 0; k < 4; k++, r++) {
            s16 v = r->charID;
            if (v >= 0) {
                REP_SLOT_OBJ(o->baseIdx + 5 + k)->_5C = v << 16;
            }
        }
    }
    lbl_3_common_bss_32724._C7 = 1;
    o->timer = 0;
    o->blinkTimer = 0;
    o->progress[0] = 0;
    lbl_803CC1B8->func = fn_3_959BC;
}

// .text:0x00096914 size:0x78 mapped:0x806D59A8
void fn_3_96914(void) {
    if (lbl_3_common_bss_32724._C7 == 0 && g_GameLogic.hudElementLoadingInd != 0) {
        fn_800B0A5C_insertQueue(fn_3_9669C, 2);
        if (g_d_GameSettings.GameModeSelected == 6) {
            fn_800B0A5C_insertQueue(fn_3_ED574, 2);
        }
    }
}

// .text:0x0009698C size:0x318 mapped:0x806D5A20
void fn_3_9698C(void) {
    RepTask* task = (void*)lbl_803CC1B8;
    if (task->timer < 0xFFFE) {
        task->timer++;
    } else {
        task->timer = 0xFFFF;
    }
    if (lbl_3_common_bss_32724.hudOff != 0 || g_Stats.replayInd != 0) {
        goto remove;
    }
    if (task->_1C == 15) {
        if (REP_OBJ(task, 0)->_69 == 2) {
            if (g_d_GameSettings.GameModeSelected == 6) {
                fn_800B0A5C_insertQueue(fn_3_ED0F4, 2);
            }
            goto remove;
        }
        if (g_GameLogic.gameStatus != 2 && g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 0 && g_GameLogic.gameStatus != 20) {
            goto remove;
        }
    } else if (task->_1E == 2) {
        if (REP_OBJ(task, 0)->_69 == 2 || g_GameLogic.hudElementLoadingInd != 0) {
            goto remove;
        }
        if (g_GameLogic.gameStatus != 2 && g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 0) {
            goto remove;
        }
    } else if (task->_1E == 1) {
        if (g_GameLogic.hudElementLoadingInd != 0) {
            goto remove;
        }
        if (g_GameLogic.gameStatus != 2 && g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 0) {
            goto remove;
        }
    }
    if (task->_1E == 0) {
        if ((REP_OBJ(task, 0)->_5C >> 16) >= lbl_3_data_BE50.kinds[task->_1C][1]) {
            task->_1E = 1;
            REP_OBJ(task, 0)->_68 = 0;
        }
    } else if (task->_1E == 1) {
        if (g_UnkSound_32718._02 != 0 || (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_32724._B4 != 0)) {
            REP_OBJ(task, 0)->_68 = 1;
            task->_1E = 2;
        } else {
            if (task->_1A < 0xFFFE) {
                task->_1A++;
            } else {
                task->_1A = 0xFFFF;
            }
            if (task->_1A >= lbl_3_data_BE50.kinds[task->_1C][2]) {
                REP_OBJ(task, 0)->_68 = 1;
                task->_1E = 2;
            }
        }
    }
    if ((task->_1C == 0x10 || task->_1C == 0x16) && task->timer == 0x23) {
        playSoundEffect(0x15C);
    }
    return;
remove:
    g_UnkSound_32718._07 = 0;
    fn_80034CEC(task);
    REMOVE_QUEUE_NOARG();
}

#if !NONMATCHING
// Switch jump tables of fn_3_96CA4; mwcc emits them itself once the function matches.
void* jumptable_3_data_F448[23] = {
    (u8*)fn_3_96CA4 + 0x25C, (u8*)fn_3_96CA4 + 0xF0, (u8*)fn_3_96CA4 + 0xFC, (u8*)fn_3_96CA4 + 0x174,
    (u8*)fn_3_96CA4 + 0x180, (u8*)fn_3_96CA4 + 0x108, (u8*)fn_3_96CA4 + 0x18C, (u8*)fn_3_96CA4 + 0x25C,
    (u8*)fn_3_96CA4 + 0x114, (u8*)fn_3_96CA4 + 0x120, (u8*)fn_3_96CA4 + 0x12C, (u8*)fn_3_96CA4 + 0x138,
    (u8*)fn_3_96CA4 + 0x144, (u8*)fn_3_96CA4 + 0x168, (u8*)fn_3_96CA4 + 0x15C, (u8*)fn_3_96CA4 + 0x25C,
    (u8*)fn_3_96CA4 + 0x248, (u8*)fn_3_96CA4 + 0x168, (u8*)fn_3_96CA4 + 0x150, (u8*)fn_3_96CA4 + 0x25C,
    (u8*)fn_3_96CA4 + 0x25C, (u8*)fn_3_96CA4 + 0x198, (u8*)fn_3_96CA4 + 0x254,
};
#endif

// .text:0x00096CA4 size:0x4A0 mapped:0x806D5D38
// NONMATCHING 87%: original reaches lbl_3_data_BE50 through the pooled lbl_3_data_8D88 base (+0x30C8/+0x3190/+0x31A4; data defined in this TU), so registers and stack frame differ
#if NONMATCHING
void fn_3_96CA4(void) {
    RepTask* task = (void*)lbl_803CC1B8;
    s16 anim;
    u32 stadium;
    u8 v;
    s32 voice;
    s32 lead;
    s16 runs;
    if (g_UnkSound_32718._07 == 0xD && lbl_3_common_bss_32724._98 != 0) {
        return;
    }
    task->_1C = g_UnkSound_32718._07;
    anim = lbl_3_data_BE50.kinds[task->_1C][0];
    if (g_d_GameSettings.minigamesEnabled == 0 && (anim == 0xBB || anim == 0xFD)) {
        if (++lbl_3_common_bss_32724._A9 == 2) {
            task->_1C = 0x17;
        }
        if (lbl_3_common_bss_32724._A9 == 3) {
            task->_1C = 0x18;
        }
        anim = lbl_3_data_BE50.kinds[task->_1C][0];
    }
    switch (g_UnkSound_32718._07) {
    case 1:
        playSoundEffect(0x15C);
        break;
    case 2:
        playSoundEffect(0x15D);
        break;
    case 5:
        playSoundEffect(0x165);
        break;
    case 8:
        playSoundEffect(0x15A);
        break;
    case 9:
        playSoundEffect(0x15B);
        break;
    case 10:
        playSoundEffect(0x162);
        break;
    case 11:
        playSoundEffect(0x163);
        break;
    case 12:
        playSoundEffect(0x15E);
        break;
    case 18:
        playSoundEffect(0x15C);
        break;
    case 14:
        playSoundEffect(0x15F);
        break;
    case 13:
    case 17:
        playSoundEffect(0x160);
        break;
    case 3:
        playSoundEffect(0x164);
        break;
    case 4:
        playSoundEffect(0x166);
        break;
    case 6:
        playSoundEffect(0x167);
        break;
    case 21:
        if (lbl_800EF808.unk398 == 1) {
            stadium = g_d_GameSettings.StadiumID;
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[25].vol;
            } else {
                v = lbl_3_data_8404[stadium * 15 + 25].vol;
            }
            voice = sndFXStartEx(lbl_3_data_81DC[stadium] + 0x19, v, 0x3F, 0);
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[25].ctrl;
            } else {
                v = lbl_3_data_8404[stadium * 15 + 25].ctrl;
            }
            sndFXCtrl(voice, 0x5B, v);
        }
        break;
    case 16:
        playSoundEffect(0x15A);
        break;
    case 22:
        playSoundEffect(0x164);
        break;
    }
    lbl_3_data_BE50.desc[0].animId = anim;
    if (g_d_GameSettings.GameModeSelected != 6 && task->_1C == 0xF) {
        lead = 0;
        if (g_d_GameSettings.GameModeSelected == 2) {
            lbl_3_data_BE50.desc[0].animId = lbl_3_data_BE50.runsAnim[g_RunningLogic.runsScored - 1];
        } else {
            runs = g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0];
            if (g_Scores._A0 < runs && g_Scores._A0 + g_RunningLogic.runsScored > runs) {
                lead = 1;
            }
            if (g_Scores.inning >= g_Scores.maxInnings && g_Scores._AD != 0 && g_Scores._A0 + g_RunningLogic.runsScored > runs) {
                if (lead) {
                    if (g_RunningLogic.runsScored == 4) {
                        lbl_3_data_BE50.desc[0].animId = lbl_3_data_BE50.runsAnim[8];
                    } else {
                        lbl_3_data_BE50.desc[0].animId = lbl_3_data_BE50.runsAnim[7];
                    }
                } else {
                    lbl_3_data_BE50.desc[0].animId = lbl_3_data_BE50.runsAnim[6];
                }
            } else if (lead) {
                if (g_RunningLogic.runsScored == 4) {
                    lbl_3_data_BE50.desc[0].animId = lbl_3_data_BE50.runsAnim[5];
                } else {
                    lbl_3_data_BE50.desc[0].animId = lbl_3_data_BE50.runsAnim[4];
                }
            } else {
                lbl_3_data_BE50.desc[0].animId = lbl_3_data_BE50.runsAnim[g_RunningLogic.runsScored - 1];
            }
        }
    }
    if (task->_1C == 0x15) {
        lbl_3_data_BE50.desc[0].texId = 0xE;
    } else {
        lbl_3_data_BE50.desc[0].texId = 2;
    }
    fn_80034E20(task, lbl_3_data_BE50.desc);
    if (g_d_GameSettings.GameModeSelected == 6) {
        REP_OBJ(task, 0)->y = lbl_3_data_BE50.kinds[task->_1C][3];
    }
    task->timer = 0;
    task->_1A = 0;
    task->_1E = 0;
    lbl_803CC1B8->func = fn_3_9698C;
}
#endif


// Sprite/layout tables of the in-game screens (.data 0x8D88-0xF448), then a table at 0xF4A4 that
// follows this file's jump table. Read as globals by rep_16B8, rep_1610, rep_1770, rep_2BF8,
// rep_3448 and the auto 97144/1293D0/157DB8 units; the jump table at 0xF448 marks the end of this
// file's data, so they are defined here.
// .data 0x00008D88..0x0000F4D0
u8 lbl_3_data_8D88[224] = {
    0, 0, 0, 161, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 8, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 164, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 163, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 163, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 163, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 6, 0, 255, 14, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
SpaniDesc lbl_3_data_8E68[2] = {
    {0, 48, 0.0f, 0.0f, -1, 1, 5, 255, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
#ifdef TARGET_PC
s16 lbl_3_data_8EA8[14] = {-1, -1, -1, 50, 48, 49, -1, -1, -1, -1, -1, -1, -1, 0}; // BE s16 table
#else
u8 lbl_3_data_8EA8[28] = {
    255, 255, 255, 255, 255, 255, 0, 50, 0, 48, 0, 49, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0,
};
#endif
SpaniDesc lbl_3_data_8EC4[3] = {
    {0, 73, 0.0f, 0.0f, -1, 1, 7, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 72, 0.0f, 0.0f, -1, 1, 7, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
SpaniDesc lbl_3_data_8F24[2] = {
    {0, 7, 0.0f, 0.0f, -1, 0, 7, 255, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
SpaniDesc lbl_3_data_8F64[3] = {
    {0, 39, 0.0f, 0.0f, -1, 1, 5, 255, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 35, 0.0f, 0.0f, -1, 1, 5, 0, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
u16 lbl_3_data_8FC4[4] = {35, 36, 37, 38};
SpaniDesc lbl_3_data_8FCC[2] = {
    {0, 60, 0.0f, 0.0f, -1, 1, 5, 255, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
SpaniDesc lbl_3_data_900C[13] = {
    {0, 363, 100.0f, 0.0f, -1, 2, 8, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 363, 200.0f, 0.0f, -1, 2, 8, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 363, 300.0f, 0.0f, -1, 2, 8, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 364, 0.0f, 0.0f, -1, 0, 8, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 364, 0.0f, 0.0f, -1, 0, 8, 1, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 364, 0.0f, 0.0f, -1, 0, 8, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 365, 0.0f, 0.0f, -1, 0, 8, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 365, 0.0f, 0.0f, -1, 0, 8, 1, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 365, 0.0f, 0.0f, -1, 0, 8, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 131, 0.0f, 0.0f, -1, 0, 8, 0, 1, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 131, 0.0f, 0.0f, -1, 0, 8, 1, 1, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 131, 0.0f, 0.0f, -1, 0, 8, 2, 1, {0, 0, 0}, 0.0f, 0, 1, 2},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
u16 lbl_3_data_91AC[8] = {3, 2, 0, 4, 6, 1, 5, 7};
SpaniDesc lbl_3_data_91BC[2] = {
    {0, 251, 0.0f, 0.0f, -1, 2, 4, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
#ifdef TARGET_PC
u16 lbl_3_data_91FC[6] = {0, 251, 253, 252, 315, 0}; // BE u16 table
#else
u8 lbl_3_data_91FC[12] = {0, 0, 0, 251, 0, 253, 0, 252, 1, 59, 0, 0};
#endif
u8 lbl_3_data_9208[192] = {
    0, 0, 1, 45, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 22, 0, 255, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 35, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 22, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 45, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 22, 0, 255, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 35, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 22, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 46, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 21, 0, 255, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u16 lbl_3_data_92C8[6] = {297, 292, 294, 298, 292, 0};
u8 lbl_3_data_92D4[256] = {
    0, 0, 0, 99, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 8, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 98, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 97, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 94, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 91, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 46, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 255, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 5, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u16 lbl_3_data_93D4[8][2] = {{7, 7}, {0, 0}, {1, 1}, {2, 2}, {4, 4}, {3, 3}, {5, 5}, {6, 6}};
u16 lbl_3_data_93F4[5][2] = {{1, 1}, {2, 2}, {4, 4}, {3, 3}, {0, 0}};
u8 lbl_3_data_9408[2368] = {
    0, 0, 0, 70, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 19, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 6, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 7, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 70, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 73, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 18, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 73, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 19, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 73, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 20, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 73, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 21, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 68, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 68, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 68, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 68, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 67, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 7, 0, 26, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 67, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 7, 0, 27, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 67, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 7, 0, 28, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 67, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 7, 0, 29, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 63, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 63, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 63, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 63, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 62, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 34, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 62, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 35, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 62, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 36, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 62, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 37, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 80, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 80, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 80, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 80, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 83, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 83, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 83, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 83, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 79, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 42, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 79, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 43, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 79, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 44, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 79, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 45, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 82, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 82, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 82, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 82, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 81, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 54, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 81, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 55, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 81, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 56, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 81, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 57, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 130, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 46, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 130, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 47, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 130, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 48, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 130, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 49, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 57, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 59, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 58, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 67, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 58, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 67, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 58, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 67, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 58, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 67, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 7, 0, 255, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u16 lbl_3_data_9D48[2] = {70}; // read as u16, padded to 4
u16 lbl_3_data_9D4C[2] = {14}; // read as u16, padded to 4
u8 lbl_3_data_9D50[10 * 5 + 2] = { // [10][5] (read as u8[][5]), padded to 4
    0, 0, 0, 0, 0,
    4, 1, 0, 0, 0,
    1, 2, 3, 4, 5,
    1, 2, 3, 4, 6,
    1, 4, 0, 0, 0,
    2, 1, 3, 0, 0,
    2, 1, 4, 0, 0,
    4, 1, 2, 0, 0,
    2, 1, 4, 3, 0,
    0, 4, 1, 2, 0,
    0, 0, // padding
};
u16 lbl_3_data_9D84[8] = {71, 65, 66, 67, 69, 68, 70, 0};
u8 lbl_3_data_9D94[288] = {
    0, 0, 0, 52, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 51, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 46, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 46, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 46, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 46, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u16 lbl_3_data_9EB4[2][2] = {{22, 28}, {22, 28}};
u8 lbl_3_data_9EBC[2][8] = {{8, 7, 6, 5, 4, 3, 2, 1}, {6, 5, 4, 0, 3, 2, 1, 0}};
u8 lbl_3_data_9ECC[232] = {
    0, 0, 0, 108, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 106, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 105, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 105, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 105, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 105, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 1, 0, 0, 3, 2, 1, 0,
};
u8 lbl_3_data_9FB4[1504] = {
    0, 0, 0, 108, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 104, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 102, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 103, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 70, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 20, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 19, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 70, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 8, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 6, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 6, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 6, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 6, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 73, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 10, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 73, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 11, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 73, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 12, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 73, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 13, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 68, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 68, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 68, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 68, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 67, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 6, 0, 18, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 67, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 6, 0, 19, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 67, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 6, 0, 20, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 67, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 6, 0, 21, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 26, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 27, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 28, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 29, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 57, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 59, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 58, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 35, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 58, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 35, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 58, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 35, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 58, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 35, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_A594[4] = {0, 1, 2, 3};
u8 lbl_3_data_A598[800] = {
    0, 0, 0, 48, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 255, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 48, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 255, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 48, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 255, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 48, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 255, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 48, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 255, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 48, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 255, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 48, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 255, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 7, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 8, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 9, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 10, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 11, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 12, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 13, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 56, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 255, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 55, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 54, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u16 lbl_3_data_A8B8[152] = {
    0, 10, 20, 30, 40, 50, 60, 0,
    0, 63, 0, 0, 0, 0, 65535, 65535,
    8, 255, 768, 0, 0, 0, 1, 0,
    0, 55, 0, 0, 0, 0, 65535, 65535,
    7, 0, 768, 0, 0, 0, 1, 3,
    0, 55, 0, 0, 0, 0, 65535, 65535,
    7, 0, 768, 0, 0, 0, 1, 4,
    0, 55, 0, 0, 0, 0, 65535, 65535,
    7, 0, 768, 0, 0, 0, 1, 5,
    0, 55, 0, 0, 0, 0, 65535, 65535,
    6, 0, 768, 0, 0, 0, 1, 6,
    0, 55, 0, 0, 0, 0, 65535, 65535,
    7, 0, 768, 0, 0, 0, 1, 2,
    0, 55, 0, 0, 0, 0, 65535, 65535,
    7, 0, 768, 0, 0, 0, 1, 1,
    0, 55, 0, 0, 0, 0, 65535, 65535,
    7, 0, 768, 0, 0, 0, 1, 0,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
u16 lbl_3_data_A9E8[8] = {62, 55, 56, 57, 59, 58, 60, 61};
SpaniDesc lbl_3_data_A9F8[5] = {
    {0, 223, 0.0f, 0.0f, -1, 3, 5, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 223, 0.0f, 0.0f, -1, 3, 5, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 223, 0.0f, 0.0f, -1, 3, 5, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 223, 0.0f, 0.0f, -1, 3, 5, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
u16 lbl_3_data_AA98[12] = {223, 230, 226, 225, 227, 229, 228, 224, 255, 254, 256, 0};
SpaniDesc lbl_3_data_AAB0[43] = {
    {0, 312, 0.0f, 0.0f, -1, 0, 6, 255, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 311, 0.0f, 0.0f, -1, 1, 6, 0, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 310, 0.0f, 0.0f, -1, 1, 6, 0, 1, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 8, 0.0f, 0.0f, -1, 0, 7, 255, 17, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 7, 0.0f, 0.0f, -1, 0, 7, 3, 17, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 10, 0.0f, 0.0f, -1, 1, 6, 3, 17, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 186, 0.0f, 0.0f, -1, 1, 5, 255, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 8, 0.0f, 0.0f, -1, 0, 7, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 10, 0.0f, 0.0f, -1, 0, 6, 255, 17, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 5, 0.0f, 0.0f, -1, 0, 7, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 1, 0.0f, 0.0f, -1, 0, 6, 9, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 1, 0.0f, 0.0f, -1, 0, 6, 9, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 1, 0.0f, 0.0f, -1, 0, 6, 9, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 1, 0.0f, 0.0f, -1, 0, 6, 9, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 7, 0.0f, 0.0f, -1, 0, 6, 10, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 7, 0.0f, 0.0f, -1, 0, 6, 11, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 7, 0.0f, 0.0f, -1, 0, 6, 12, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 7, 0.0f, 0.0f, -1, 0, 6, 13, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 131, 0.0f, 0.0f, -1, 0, 6, 10, 1, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 131, 0.0f, 0.0f, -1, 0, 6, 11, 1, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 131, 0.0f, 0.0f, -1, 0, 6, 12, 1, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 131, 0.0f, 0.0f, -1, 0, 6, 13, 1, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 6, 0.0f, 0.0f, -1, 0, 6, 10, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 6, 0.0f, 0.0f, -1, 0, 6, 11, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 6, 0.0f, 0.0f, -1, 0, 6, 12, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 6, 0.0f, 0.0f, -1, 0, 6, 13, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 3, 0.0f, 0.0f, -1, 1, 6, 255, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 21, 0.0f, 0.0f, -1, 0, 6, 26, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 245, 0.0f, 0.0f, -1, 0, 6, 255, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 244, 0.0f, 0.0f, -1, 0, 6, 28, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 246, 0.0f, 0.0f, -1, 0, 6, 28, 1, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 243, 0.0f, 0.0f, -1, 0, 6, 28, 1, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 241, 0.0f, 0.0f, -1, 0, 6, 31, 1, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 241, 0.0f, 0.0f, -1, 0, 6, 31, 1, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 241, 0.0f, 0.0f, -1, 0, 6, 31, 1, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 241, 0.0f, 0.0f, -1, 0, 6, 31, 1, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 241, 0.0f, 0.0f, -1, 0, 6, 31, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 10, 0.0f, 0.0f, -1, 0, 6, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 11, 0.0f, 0.0f, -1, 0, 6, 37, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 14, 0.0f, 0.0f, -1, 0, 6, 37, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 131, 0.0f, 0.0f, -1, 0, 6, 39, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 15, 0.0f, 0.0f, -1, 3, 6, 37, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
u16 lbl_3_data_B010[40] = {
    9, 8, 0, 0, 10, 8, 7, 10,
    11, 9, 8, 7, 10, 11, 9, 8,
    7, 10, 11, 9, 8, 7, 10, 11,
    9, 8, 7, 10, 11, 9, 8, 7,
    10, 11, 9, 6, 5, 8, 9, 7,
};
u8 lbl_3_data_B060[120] = {
    0, 1, 2, 255, 255, 0, 1, 2, 255, 255, 0, 1, 2, 255, 255, 0,
    3, 255, 255, 255, 1, 3, 255, 255, 255, 2, 4, 255, 255, 255, 0, 3,
    255, 255, 255, 1, 4, 255, 255, 255, 2, 3, 255, 255, 255, 0, 3, 255,
    255, 255, 1, 3, 255, 255, 255, 2, 4, 255, 255, 255, 0, 3, 255, 255,
    255, 1, 3, 255, 255, 255, 2, 3, 255, 255, 255, 0, 3, 255, 255, 255,
    1, 3, 255, 255, 255, 2, 3, 255, 255, 255, 0, 3, 255, 255, 255, 1,
    3, 255, 255, 255, 2, 3, 255, 255, 255, 0, 1, 255, 255, 255, 0, 1,
    255, 255, 255, 0, 1, 255, 255, 255,
};
u16 lbl_3_data_B0D8[4] = {2, 3, 4, 5};
SpaniDesc lbl_3_data_B0E0[3] = {
    {0, 1, 0.0f, 0.0f, -1, 1, 2, 255, 17, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 0, 0.0f, 0.0f, -1, 0, 2, 0, 17, {0, 0, 0}, 0.0f, 0, 1, 0},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
u8 lbl_3_data_B140[124] = {
    0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
    0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 35,
    0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 22, 0, 255,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 46,
    0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 1, 21, 0, 255,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_B1BC[544] = {
    0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 8, 0, 255, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 2, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 3, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 4, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 5, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4,
    0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u16 lbl_3_data_B3DC[6] = {1, 2, 4, 3, 0, 0};
u16 lbl_3_data_B3E8[6] = {3, 4, 5, 6, 7, 0};
u8 lbl_3_data_B3F4[480] = {
    0, 0, 0, 70, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 19, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 19, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 70, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 73, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 4, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 68, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 67, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 6, 0, 6, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 80, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 7, 0, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 83, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 7, 0, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 79, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 82, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 81, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 11, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 130, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_B5D4[608] = {
    0, 0, 0, 116, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 8, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 115, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 118, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 11,
    0, 0, 0, 118, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 10,
    0, 0, 0, 118, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 9,
    0, 0, 0, 118, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 8,
    0, 0, 0, 117, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 117, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 117, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 117, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 113, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 7,
    0, 0, 0, 113, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6,
    0, 0, 0, 113, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5,
    0, 0, 0, 113, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4,
    0, 1, 0, 114, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    0, 6, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 1, 0, 114, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    0, 6, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 1, 0, 114, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    0, 6, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 1, 0, 114, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    0, 6, 0, 255, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
s16 lbl_3_data_B834[5][4] = {{7, 8, 9, 10}, {11, 12, 13, 14}, {15, 16, 17, 18}, {19, 20, 21, 22}, {25, 26, 23, 24}};
u8 lbl_3_data_B85C[512] = {
    0, 0, 0, 62, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 255, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 54, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4,
    0, 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 51, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 63, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 5, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5,
    0, 0, 0, 37, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 255, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 1, 0, 48, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 255, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 1, 0, 49, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 255, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 13, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u16 lbl_3_data_BA5C[10] = {0, 42, 37, 39, 43, 45, 40, 38, 41, 44};
u8 lbl_3_data_BA70[736] = {
    0, 0, 0, 58, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 255, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 56, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4,
    0, 0, 0, 57, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 57, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 57, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 57, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 52, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 2, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 52, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 3, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 52, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 4, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 52, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 5, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 63, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 2, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 63, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 3, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 63, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 4, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 63, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 5, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 12, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 13, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 2, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 3, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 4, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 5, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_BD50[64] = {
    0, 0, 0, 53, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 255, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_BD90[192] = {
    0, 0, 0, 62, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 4, 0, 255, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 4, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 54, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 4, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4,
    0, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 4, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5,
    0, 1, 0, 48, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 255, 11, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
RepBannerData lbl_3_data_BE50 = {
    {
        {-1, 0, 0, 0},
        {187, 45, 10, -70},
        {223, 11, 39, 0},
        {220, 28, 37, -70},
        {219, 8, 47, -70},
        {186, 0, 0, -40},
        {222, 9, 46, 0},
        {218, 70, 55, 0},
        {252, 12, 40, 0},
        {247, 7, 48, 0},
        {249, 8, 48, 0},
        {248, 31, 27, 0},
        {251, 0, 0, 0},
        {250, 0, 0, 0},
        {254, 0, 0, 0},
        {156, 0, 0, 0},
        {253, 12, 25, 0},
        {250, 0, 0, 0},
        {187, 45, 50, 0},
        {-1, 0, 0, 0},
        {217, 70, 55, 0},
        {61, 71, 90, 0},
        {221, 22, 30, 0},
        {216, 33, 32, 0},
        {224, 39, 21, 0},
    },
    {156, 114, 115, 124, 151, 153, 129, 131, 152, 0},
    {
        {0, 251, 0.0f, 0.0f, -1, 1, 4, 255, 2, {0, 0, 0}, 0.0f, 0, 0, 0},
        {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
    },
};
u8 lbl_3_data_BF6C[128] = {
    0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 4, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 4, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 4, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_BFEC[480] = {
    0, 0, 0, 161, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 8, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 167, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    2, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 167, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    2, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 167, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    2, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 167, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    2, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 7, 0, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 163, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 8, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 163, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 8, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 163, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 8, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 166, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 6, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 160, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 6, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
f32 lbl_3_data_C1CC[4] = {556.0f, 102.0f, 2.3f, 2.3f};
s16 lbl_3_data_C1DC[8] = {557, 107, 602, 60, 557, 17, 511, 60}; // unreferenced; x/y pairs
u8 lbl_3_data_C1EC[64] = {
    0, 0, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 9, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_C22C[288] = {
    0, 0, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    0, 6, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    0, 6, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    0, 6, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    0, 6, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    0, 6, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    0, 6, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    0, 6, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_C34C[544] = {
    0, 0, 1, 20, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 26, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 21, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    0, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    0, 5, 0, 4, 15, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    0, 5, 0, 4, 16, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 17, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    0, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 17, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    2, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 17, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    2, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 19, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    0, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 19, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    2, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 19, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    2, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 19, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    0, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 19, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    2, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 19, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
    2, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_C56C[2][0x660] = {
    {
        0, 0, 0, 44, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 28, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 26, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
        0, 0, 0, 33, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 8,
        0, 0, 0, 33, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 9,
        0, 0, 0, 30, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 12,
        0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 29, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 15,
        0, 0, 0, 29, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 14,
        0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 19,
        0, 0, 0, 43, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 18,
        0, 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5,
        0, 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4,
        0, 0, 0, 37, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 23,
        0, 0, 0, 37, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 22,
        0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 17, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4,
        0, 0, 0, 18, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 17, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5,
        0, 0, 0, 31, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 26,
        0, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 28,
        0, 0, 0, 38, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 30,
        0, 0, 0, 46, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 14,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 13,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 12,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 11,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 10,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 14,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 13,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 12,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 11,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 10,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        2, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 44, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        2, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 46, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 39, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        3, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 33,
        0, 0, 0, 39, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        3, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 32,
        0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 44, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 27, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
        0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
        0, 0, 0, 33, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 10,
        0, 0, 0, 33, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 11,
        0, 0, 0, 30, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 13,
        0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 29, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 17,
        0, 0, 0, 29, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 16,
        0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 21,
        0, 0, 0, 43, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 20,
        0, 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 7,
        0, 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6,
        0, 0, 0, 37, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 25,
        0, 0, 0, 37, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24,
        0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 17, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6,
        0, 0, 0, 18, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 17, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 7,
        0, 0, 0, 31, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 27,
        0, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 29,
        0, 0, 0, 38, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 31,
        0, 0, 0, 46, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 19,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 18,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 17,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 16,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 15,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 9,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 8,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 7,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6,
        0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        1, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 19,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 18,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 17,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 16,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 15,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 9,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 8,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 7,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6,
        0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 23, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5,
        0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 44, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        2, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        0, 7, 0, 46, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 39, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        3, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 35,
        0, 0, 0, 39, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
        3, 7, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 34,
        0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
};
u16 lbl_3_data_D22C[4] = {0, 1, 2, 3};
u16 lbl_3_data_D234[14] = {12, 0, 6, 2, 8, 4, 10, 5, 11, 3, 9, 1, 7, 0};
u8 lbl_3_data_D250[8] = {17, 21, 27, 35, 45}; // read as u8[5] (rep_1770), padded to 8
u8 lbl_3_data_D258[288] = {
    0, 0, 0, 75, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 8, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 8, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 8, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 74, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 8, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 79, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 8, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 70, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 8, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 77, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 8, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 76, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 8, 0, 6, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_D378[384] = {
    0, 0, 0, 75, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 8, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 8, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 73, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 8, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 74, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 8, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 78, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 8, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 70, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 8, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 77, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 8, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 76, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 8, 0, 6, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 80, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 8, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 4, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_D4F8[192] = {
    0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 18, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 6, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_D5B8[128] = {
    0, 0, 0, 213, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 7, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 212, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 212, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 6, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
s16 lbl_3_data_D638[8] = {0, 56, 640, 584, 16, 64, 432, 384}; // MarkerEdges (rep_2BF8)
u8 lbl_3_data_D648[352] = {
    0, 0, 0, 209, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 2, 0, 255, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 218, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 2, 0, 255, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 190, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 206, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 206, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 206, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 206, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 206, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 206, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 206, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_D7A8[64] = {
    0, 0, 0, 209, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 8, 0, 255, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
PauseGeom lbl_3_data_D7E8[6] = { // pause menu geometry (auto_00_00097144_text)
    {214, 191, 15, {2, 1, 0, 0, 0, 0, 0}},
    {213, 190, 15, {3, 2, 1, 0, 0, 0, 0}},
    {215, 192, 17, {4, 3, 2, 1, 0, 0, 0}},
    {216, 192, 17, {5, 4, 3, 2, 1, 0, 0}},
    {217, 193, 17, {6, 5, 4, 3, 2, 1, 0}},
    {218, 194, 23, {7, 6, 5, 4, 3, 2, 1}},
};
// PauseLayout[19] (auto_00_00097144_text.h, read there) plus 2 pad bytes: the symbol is 0x158 bytes, so it is defined as u16[].
u16 lbl_3_data_D860[172] = {
    5, 1, 0, 4, 2, 5, 3, 0, 0, 4, 1, 0, 2, 5, 3, 0,
    0, 0, 7, 1, 0, 30, 29, 4, 2, 5, 3, 6, 1, 0, 30, 29,
    2, 5, 3, 0, 5, 0, 11, 8, 14, 12, 3, 0, 0, 4, 0, 11,
    8, 12, 3, 0, 0, 0, 5, 0, 11, 8, 15, 12, 3, 0, 0, 4,
    2, 14, 6, 12, 3, 0, 0, 0, 3, 2, 6, 12, 3, 0, 0, 0,
    0, 6, 0, 0, 26, 7, 8, 9, 3, 0, 5, 2, 6, 13, 15, 9,
    3, 0, 0, 5, 2, 27, 6, 15, 9, 3, 0, 0, 4, 2, 6, 15,
    9, 3, 0, 0, 0, 5, 0, 0, 7, 8, 17, 3, 0, 0, 3, 2,
    16, 17, 3, 0, 0, 0, 0, 4, 2, 6, 15, 17, 3, 0, 0, 0,
    4, 0, 0, 7, 8, 18, 0, 0, 0, 4, 1, 0, 7, 8, 3, 0,
    0, 0, 3, 2, 6, 15, 3, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_D9B8[6 * 7 + 2] = { // [6][7], padded to 4
    6, 10, 0, 0, 0, 0, 0,
    6, 8, 10, 0, 0, 0, 0,
    6, 8, 10, 12, 0, 0, 0,
    6, 8, 10, 12, 14, 0, 0,
    6, 8, 10, 12, 14, 17, 0,
    6, 8, 10, 12, 14, 17, 23,
    0, 0, // padding
};
u8 lbl_3_data_D9E4[96] = {
    0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 255, 19, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 0, 19, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u16 lbl_3_data_DA44[2][3] = {{1, 0, 2}, {3, 0, 4}};
u8 lbl_3_data_DA50[1664] = {
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 255, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 29, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 255, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 20, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 1, 28, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 1, 19, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 1, 19, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 1, 19, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 1, 19, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 21, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 1, 21, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 1, 21, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 1, 21, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 25, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 1, 25, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 1, 25, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 1, 25, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 13, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 1, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 14, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 1, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 15, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 1, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 1, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 13, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 14, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 15, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 18, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 25, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 20, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 28, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 19, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 27, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 1, 19, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 27, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 1, 19, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 27, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 1, 19, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 27, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 21, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 27, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 1, 21, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 27, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 1, 21, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 27, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 1, 21, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 27, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 25, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 27, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 1, 25, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 27, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 1, 25, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 27, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 1, 25, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 27, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 37, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 1, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 38, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 1, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 39, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 1, 23, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 40, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 1, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 37, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 38, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 39, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 24, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 40, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 18, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 49, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u16 lbl_3_data_E0D0[8] = {1, 0, 1, 14, 1, 14, 3, 2};
u8 lbl_3_data_E0E0[64] = {
    0, 0, 0, 53, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_E120[64] = {
    0, 0, 0, 159, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_E160[160] = {
    0, 0, 0, 91, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 4, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 92, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 4, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 4, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 4, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u16 lbl_3_data_E200[14] = {0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0};
u8 lbl_3_data_E21C[92] = {
    0, 0, 0, 89, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 4, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    6, 255, 255, 255, 255, 1, 2, 255, 255, 255, 5, 6, 7, 255, 255, 0,
    1, 2, 3, 255, 4, 5, 6, 7, 8, 0, 0, 0,
};
u8 lbl_3_data_E278[128] = {
    0, 0, 0, 93, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 4, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 94, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 4, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 4, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_E2F8[128] = {
    0, 0, 0, 102, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 103, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_E378[992] = {
    0, 0, 0, 96, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 98, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 97, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 97, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 97, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 97, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 3, 0, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_E758[1] = {6};
u8 lbl_3_data_E759[3] = {12, 18, 24}; // unreferenced
u8 lbl_3_data_E75C[256] = {
    0, 0, 0, 183, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 179, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 180, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 2, 16, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 181, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 182, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_E85C[608] = {
    0, 0, 0, 225, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 236, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    0, 0, 0, 237, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 2, 16, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 2, 16, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 2, 16, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 229, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6,
    0, 0, 0, 235, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 8,
    0, 0, 0, 235, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 7,
    0, 0, 0, 235, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5,
    0, 0, 0, 235, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4,
    0, 0, 0, 231, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 9,
    0, 0, 0, 185, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 185, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 226, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 10,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_EABC[352] = {
    0, 0, 0, 245, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 243, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 1, 16, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 244, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 244, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 244, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 244, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 244, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 244, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    2, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
RepLineScoreData lbl_3_data_EC1C = {
    {
        {0, 14, 0.0f, 0.0f, -1, 1, 5, 255, 2, {0, 0, 0}, 0.0f, 0, 1, 0},
        {0, 1, 0.0f, 0.0f, -1, 0, 5, 0, 15, {0, 0, 0}, 0.0f, 0, 1, 1},
        {0, 1, 0.0f, 0.0f, -1, 0, 5, 0, 16, {0, 0, 0}, 0.0f, 0, 1, 0},
        {0, 13, 0.0f, 0.0f, -1, 1, 5, 255, 2, {0, 0, 0}, 0.0f, 0, 1, 0},
        {0, 15, 0.0f, 0.0f, -1, 1, 5, 255, 2, {0, 0, 0}, 0.0f, 0, 1, 0},
        {0, 12, 0.0f, 0.0f, -1, 2, 5, 4, 2, {0, 0, 0}, 0.0f, 0, 1, 5},
        {0, 12, 0.0f, 0.0f, -1, 2, 5, 4, 2, {0, 0, 0}, 0.0f, 0, 1, 3},
        {0, 12, 0.0f, 0.0f, -1, 2, 5, 4, 2, {0, 0, 0}, 0.0f, 0, 1, 4},
        {0, 12, 0.0f, 0.0f, -1, 2, 5, 4, 2, {0, 0, 0}, 0.0f, 0, 1, 2},
        {0, 12, 0.0f, 0.0f, -1, 2, 5, 4, 2, {0, 0, 0}, 0.0f, 0, 1, 1},
        {0, 12, 0.0f, 0.0f, -1, 2, 5, 4, 2, {0, 0, 0}, 0.0f, 0, 1, 0},
        {0, 12, 0.0f, 0.0f, -1, 1, 5, 4, 2, {0, 0, 0}, 0.0f, 0, 1, 5},
        {0, 12, 0.0f, 0.0f, -1, 1, 5, 4, 2, {0, 0, 0}, 0.0f, 0, 1, 3},
        {0, 12, 0.0f, 0.0f, -1, 1, 5, 4, 2, {0, 0, 0}, 0.0f, 0, 1, 4},
        {0, 12, 0.0f, 0.0f, -1, 1, 5, 4, 2, {0, 0, 0}, 0.0f, 0, 1, 2},
        {0, 12, 0.0f, 0.0f, -1, 1, 5, 4, 2, {0, 0, 0}, 0.0f, 0, 1, 1},
        {0, 12, 0.0f, 0.0f, -1, 1, 5, 4, 2, {0, 0, 0}, 0.0f, 0, 1, 0},
        {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
    },
    {
        {0, 198, 0.0f, 0.0f, -1, 1, 7, 255, 2, {0, 0, 0}, 0.0f, 0, 1, 0},
        {0, 193, 0.0f, 0.0f, -1, 1, 7, 255, 2, {0, 0, 0}, 0.0f, 0, 1, 0},
        {0, 210, 0.0f, 0.0f, -1, 1, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 15},
        {0, 210, 0.0f, 0.0f, -1, 1, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 14},
        {0, 0, 0.0f, 0.0f, -1, 0, 6, 2, 15, {0, 0, 0}, 0.0f, 0, 1, 0},
        {0, 0, 0.0f, 0.0f, -1, 0, 6, 3, 16, {0, 0, 0}, 0.0f, 0, 1, 0},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 13},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 12},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 11},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 10},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 9},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 0},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 0},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 0},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 0},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 8},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 7},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 6},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 5},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 4},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 3},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 2},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 0},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 0},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 0},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 0},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 1},
        {0, 195, 0.0f, 0.0f, -1, 3, 6, 1, 2, {0, 0, 0}, 0.0f, 0, 1, 0},
        {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
    },
    194,
    195,
};
u8 lbl_3_data_F200[3][12] = {
    {5, 7, 11, 9, 13, 17, 15, 19, 21, 23, 25, 0},
    {23, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11},
    {22, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
};
u8 lbl_3_data_F224[288] = {
    0, 0, 0, 62, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 4, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 4, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 4, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 4, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 67, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 4, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 4, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 4, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 131, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 4, 0, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u16 lbl_3_data_F344[6] = {65, 66, 65, 66, 65, 66};
u8 lbl_3_data_F350[64] = {
    0, 0, 0, 177, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_F390[96] = {
    0, 0, 0, 176, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 5, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 178, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    3, 4, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_F3F0[64] = {
    0, 0, 0, 109, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 4, 0, 255, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_3_data_F430[12][2] = {{0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}};
u8 lbl_3_data_F4A4[44] = {
    0, 0, 0, 0, 2, 5, 4, 3, 8, 3, 4, 5, 2, 6, 0, 1,
    8, 6, 7, 1, 2, 0, 7, 4, 4, 3, 1, 2, 5, 1, 2, 4,
    6, 8, 7, 6, 8, 5, 3, 3, 5, 7, 4, 6,
}; // unreferenced byte table; likely a function-local static

