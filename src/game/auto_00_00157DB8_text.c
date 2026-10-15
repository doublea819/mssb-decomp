#include "game/auto_00_00157DB8_text.h"
#include "game/rep_1200.h"
#include "game/auto_00_0005985C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_80011640.h"
#include "game/auto_00_000B3B70_text.h"
#include "main/file_8000F150.h"
#include "main/file_80069BDC.h"
#include "game/rep_1770.h"
#include "game/auto_00_001293D0_text.h"
#include "main/menu_globals.h"
#include "game/auto_00_00097144_text.h"
#include "game/rep_16B8.h"
#include "game/auto_00_0009143C_text.h"
#include "main/file_800527C4.h"
#include "main/file_8004C5F8.h"
#ifdef TARGET_PC
#include "musyx/musyx.h" // SND_AUX_* (SoundManager views)
#endif

extern s16 lbl_3_data_FC1C;
extern u8 lbl_3_data_BD90[];
extern u8 lbl_3_data_BD50[];
extern u8 lbl_3_data_B3F4[];
// SoundManager (main/file_80021308.h, which clashes with this file's MusyX prototypes): only the field used here.
typedef struct PracticeSoundView {
#ifdef TARGET_PC // SoundManager's head (main/file_80021308.h): pointers are 8 bytes here
    /*0x000*/ u32 _000_unk0;
    /*0x004*/ void* _004_groups[48];
    /*0x0C4*/ SND_AUX_REVERBHI _0C4_reverb;
    /*0x2A4*/ SND_AUX_CHORUS _2A4_chorus;
    /*0x340*/ u8 _340[0x398 - 0x340];
#else
    /*0x000*/ u8 _000[0x398];
#endif
    /*0x398*/ u8 unk398;
} PracticeSoundView;
extern PracticeSoundView lbl_800EF808;
extern void fn_80034E20(void*, void*);
extern void fn_3_6B870(void);
// Emitter / Particle (main/file_800263FC.h, which can't be included next to
// UnknownHomes_Static.h): only the fields used here.
typedef struct PracticeParticle {
    /*0x00*/ u8 _00[0x40];
    /*0x40*/ u32 color;
    /*0x44*/ u8 _44[0x4D - 0x44];
    /*0x4D*/ u8 texIndex;
} PracticeParticle;
typedef struct PracticeEmitter {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ PracticeParticle* particles;
    /*0x10*/ u8 _10[0x18 - 0x10];
    /*0x18*/ s32 index; // u.seq
    /*0x1C*/ s32 count;
} PracticeEmitter;
extern PracticeEmitter* fn_80033A24(void* update, int priority, int unk14, int n, int strict, int type);
extern u32 fn_3_157AC4(PracticeEmitter* o);
extern void fn_3_5F154(void);
extern void fn_3_5EFEC(void);
extern void fn_3_5EDD8(void);
extern void fn_3_5F3FC(void);
extern void fn_3_5CD24(void);
extern void fn_3_9669C(void);
extern u8 lbl_3_data_FAF4[];
extern u8 lbl_3_data_B85C[];
extern void fn_3_8A350(void);
extern void fn_3_F7B8(void);
extern void fn_3_59338(void);
extern u16 lbl_3_data_BA5C[10];

// Sprite idx of lbl_80371C30. As a helper (rather than indexing directly) the index
// is summed before scaling, as some of the original functions do.
static inline LayoutObj* practiceSprite(s32 idx) {
    return lbl_80371C30[idx].obj;
}
extern u8 lbl_3_data_9D50[][5];
extern u8 lbl_3_data_A594[4];
extern u8 lbl_3_data_B5D4[];
extern s16 lbl_3_data_B834[][4];
extern u8 lbl_3_data_BA70[];
extern MenuDef lbl_800FEF70[];
extern PracticeMsgEntry lbl_3_data_103B8[][4][4];
extern u8 lbl_3_data_FAA8[3][9];
extern s16 lbl_3_data_104B8[][2][3];
extern u8 lbl_3_data_B1BC[];
extern u16 lbl_3_data_B3DC[6];
extern u16 lbl_3_data_B3E8[6];
extern u8 lbl_3_data_FAC4[8];

// fn_3_157DB8, size:0x70
void fn_3_157DB8(s32 arg0) {
#ifdef TARGET_PC
    // PracticeEmitter/PracticeParticle use GameCube offsets (4-byte pointers); the real
    // Emitter lives in rep_3880.c, next to its update callback.
    extern void port_fn_3_157DB8(s32 count);
    port_fn_3_157DB8(arg0);
    return;
#endif
    PracticeEmitter* e = fn_80033A24(fn_3_157AC4, 0x80, 0, 1, 1, 0x16);
    if (e != NULL) {
        e->index = 0;
        e->count = arg0;
        e->particles->texIndex = 0;
        e->particles->color = -1;
    }
}

// fn_3_1580AC, size:0x60
void fn_3_1580AC(void) {
    PracticeMsgTask* o = (PracticeMsgTask*)lbl_803CC1B8;
    fn_80034E20(o, lbl_3_data_BD90);
    o->state = 0;
    o->text = 0;
    lbl_803CC1B8->func = fn_3_157E28;
}

// fn_3_15810C, size:0xF0
void fn_3_15810C(void) {
    PracticeTask* o = (PracticeTask*)lbl_803CC1B8;
    s32 lim;
    if (lbl_3_common_bss_32724.hudOff == 0) {
        lim = 0x96;
        if (g_Practice.practiceType_2 == 0) {
            lim = 0x5A;
        }
        if (g_Practice._186 < lim - 0x14) {
            LayoutObj* t = lbl_80371C30[o->baseIdx].obj;
            if ((t->_5C >> 16) >= 0x21) {
                t->_68 = 0;
            }
        } else {
            lbl_80371C30[o->baseIdx].obj->_68 = 1;
        }
        if (g_Practice._1C7 == 0 || lbl_3_common_bss_34C90.state != 0) {
            return;
        }
    }
    fn_80034CEC(o);
    REMOVE_QUEUE_NOARG();
}

// fn_3_1581FC, size:0x68
void fn_3_1581FC(void) {
    fn_80034E20(lbl_803CC1B8, lbl_3_data_BD50);
    if (lbl_800EF808.unk398 == 1) {
        playSoundEffect(0x1AD);
    }
    lbl_803CC1B8->func = fn_3_15810C;
}

// fn_3_158264, size:0x148
void fn_3_158264(PracticeTask* o) {
    s32 v;
    s32 c;
    u8* row = lbl_3_data_FAF4 + g_Practice.practiceType_2 * 4;
    v = row[g_Practice.practiceLevel];
    fn_800363D8(o, 1, 3, 0x32, v);
    fn_800363D8(o, 1, 4, 0x32, v);
    c = g_Practice.guidedPracticeCounter;
    fn_800363D8(o, 1, 1, 0x32, c);
    fn_800363D8(o, 1, 2, 0x32, c);
    if (c != o->_1A) {
        LayoutSlot* t = &lbl_80371C30[1];
        LayoutObj* q = t[o->baseIdx].obj;
        if ((q->_5C >> 16) <= 9) {
            q->_5C = 0xA0000;
            t[o->baseIdx].obj->_68 = 1;
        }
        q = t[o->baseIdx].obj;
        if ((q->_5C >> 16) >= 0x13) {
            q->_5C = 0x90000;
            t[o->baseIdx].obj->_68 = 0;
            o->_1A = c;
        }
    }
}

// fn_3_1589C4, size:0x1A0
void fn_3_1589C4(void) {
    if (g_Practice.practiceType_2 == 0 || g_Practice.practiceType_2 == 1 || g_Practice.practiceType_2 == 2) {
        if (g_Practice.tutorialState == 3 && g_Practice._1C7 == 0) {
            if (lbl_3_common_bss_32724._C6 == 0) {
                fn_800B0A5C_insertQueue(fn_3_1586B0, 2);
                lbl_3_common_bss_32724._C6 = 1;
            }
            if (g_Practice.practiceType_2 == 2 && g_Ball.totalFramesAtPlay == 1) {
                fn_800B0A5C_insertQueue(fn_3_9669C, 2);
            }
            if (g_Practice.practiceType_2 == 2) {
                if (g_Practice._186 == 0x3C) {
                    fn_800B0A5C_insertQueue(fn_3_1581FC, 2);
                }
            } else if (g_Practice._186 == 1) {
                fn_800B0A5C_insertQueue(fn_3_1581FC, 2);
            }
        }
    } else if (g_Practice.practiceType_2 == 3) {
        if (g_Practice.tutorialState == 3 && g_Practice._1C7 == 0) {
            if (lbl_3_common_bss_32724._C7 == 0) {
                fn_800B0A5C_insertQueue(fn_3_1586B0, 2);
                fn_800B0A5C_insertQueue(fn_3_9669C, 2);
            }
            if (g_Practice._186 == 1) {
                fn_800B0A5C_insertQueue(fn_3_1581FC, 2);
            }
        }
    }
}

// fn_3_1590C8, size:0x4C
void fn_3_1590C8(void) {
    if (g_Practice.tutorialState == 0 && g_Practice.practiceState == 7) {
        fn_800B0A5C_insertQueue(fn_3_158FE4, 2);
    }
}

// fn_3_159590, size:0x64
void fn_3_159590(void) {
    PracticeTask* o = (PracticeTask*)lbl_803CC1B8;
    fn_80034E20(o, lbl_3_data_B3F4);
    o->timer = 0;
    o->_1A = 0;
    o->text[0] = 0;
    lbl_803CC1B8->func = fn_3_159114;
}

// fn_3_15AD94, size:0x40
void fn_3_15AD94(void) {
    if (g_Pitcher.currentStateFrameCounter > lbl_3_data_FC1C) {
        fn_3_750C4(2);
    }
}

// fn_3_15ADD4, size:0x60
void fn_3_15ADD4(void) {
    fn_3_6B870();
    g_GameLogic._135 = 0;
    g_GameLogic._136 = 0;
    if (g_GameLogic.secondaryGameMode == 0xF && g_Strikes.outs >= 3) {
        g_Strikes.outs = 0;
    }
    fn_3_5A6D4(7);
}


// fn_3_15AF78, size:0x160
void fn_3_15AF78(void) {
    g_GameLogic.hudElementLoadingInd = 0;
    g_GameLogic.hudLoadingRelated = 0;
    if (g_Ball.totalFramesAtPlay < 0x7FFE) {
        g_Ball.totalFramesAtPlay++;
    } else {
        g_Ball.totalFramesAtPlay = 0x7FFF;
    }
    if (g_Practice.frames_sinceMovedToFromMenu < 0xFFFE) {
        g_Practice.frames_sinceMovedToFromMenu++;
    } else {
        g_Practice.frames_sinceMovedToFromMenu = 0xFFFF;
    }
    switch (g_GameLogic.gameStatus) {
    case 0:
        fn_3_5F154();
        break;
    case 1:
        fn_3_5EFEC();
        break;
    case 2:
        fn_3_5EDD8();
        break;
    case 7:
        fn_3_5F3FC();
        if (g_GameLogic.FrameCountOfCurrentPitch == 1) {
            fn_3_15AE34();
        }
        break;
    case 8:
        fn_3_15ADD4();
        break;
    case 10:
        fn_3_5CD24();
        break;
    }
    if (g_Practice.practiceLevel != 7 && g_Practice.practiceLevel != 6) {
        g_Strikes.outs = 0;
    }
}

// fn_3_15B610, size:0x18C
void fn_3_15B610(void) {
    switch (g_Practice.tutorialState) {
    case 0:
        fn_3_15B494();
        break;
    case 3:
        fn_3_15AF78();
        break;
    }
}

// fn_3_158FE4, size:0xE4
void fn_3_158FE4(void) {
    PracticeMsgTask* o;
    LayoutObj* w;
    LayoutSlot* e;
    fn_80034E20(o = (PracticeMsgTask*)lbl_803CC1B8, lbl_3_data_B85C);
    e = lbl_80371C30;
    e += o->baseIdx;
    w = e[8].obj;
    w->flags &= ~2;
    fn_800363D8(o, 0xD, 1, 0xE, g_Practice.practiceLevel);
    fn_800363D8(o, 0xD, 2, 0xE, g_Practice.practiceLevel);
    g_Practice.laukituTextChannelIndex = -1;
    g_Practice.diagramTextChannelIndex = -1;
    o->timer = 0;
    o->_1A = 0;
    o->state = 0;
    o->text = 0;
    o->_20 = 0;
    lbl_803CC1B8->func = fn_3_158B64;
}

// .text:0x0015B0D8 size:0x12C
void fn_3_15B0D8(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        g_GameLogic._13E[i] = 0;
        g_GameLogic._140[i] = 0;
        g_GameLogic.teamAIInd[i] = 0;
        g_GameLogic.autoFielding[i] = 0;
        g_GameLogic.batterHandedness[i] = 0;
        g_GameLogic.battingAIInd[i] = 0;
    }
    g_Practice.aIEnabled = 0;
    g_Practice.practiceBatterHandedness = 0;
    g_Practice.freePracticeInd_writeOnly = 0;
    g_Practice._1A4 = 0;
    if (g_GameLogic.secondaryGameMode == 0xF) {
        g_Practice.aIEnabled = 1;
        g_GameLogic._13E[g_GameLogic.teamFielding] = 1;
        g_Practice.freePracticeInd_writeOnly = 1;
        g_GameLogic._140[g_GameLogic.awayTeamBattingInd_battingTeam] = 1;
        g_Practice.rosterID = 1;
        g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] = 1;
        g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] = 1;
    } else {
        g_Practice.practiceBatterHandedness = 1;
        g_GameLogic._13E[g_GameLogic.teamBatting] = 1;
        g_Practice._1A4 = 1;
        g_GameLogic.batterHandedness[g_GameLogic.homeTeamBattingInd_fieldingTeam] = 1;
        g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] = 1;
    }
    g_Practice._186 = 0;
    fn_3_5A684();
    fn_3_8A350();
    fn_3_F7B8();
    fn_3_75434();
    fn_3_59338();
    g_GameLogic.EventTriggers_GameHasStarted = 0;
    g_GameLogic.currentBatterPerTeam[0] = 1;
    g_GameLogic.currentBatterPerTeam[1] = 1;
}

// .text:0x0015AE34 size:0x144

// NONMATCHING 97%: register coloring of the ids[] constants and second-loop pointer (r7/r9), stw scheduling
// .text:0x0015AE34 size:0x144
#if NONMATCHING
void fn_3_15AE34(void) {
    s32 ids[4];
    InMemRunnerType* r;
    s32* q;
    s32* p;
    s32 i;
    s32 j;

    if (g_GameLogic.secondaryGameMode == 0xF) {
        q = ids;
        ids[0] = 1;
        ids[1] = 2;
        ids[2] = 3;
        ids[3] = 4;
        for (i = 0, p = q; i < 4; i++, p++) {
            for (j = 1, r = &g_Runners[1]; j < 4; j++, r++) {
                if (r->rosterID == *p) {
                    *p = -1;
                }
            }
        }
        for (i = 0; i < 4; q++, i++) {
            if (*q >= 0) {
                g_Practice.rosterID = ids[i];
                break;
            }
        }
    }
    if (g_GameLogic.TeamStars[0] == 0) {
        g_GameLogic.TeamStars[0] = 5;
    }
    if (g_GameLogic.TeamStars[1] == 0) {
        g_GameLogic.TeamStars[1] = 5;
    }
    if (g_Strikes.outs >= 3) {
        g_Strikes.outs = 0;
    }
    g_Practice.guidedPracticeCompletionRelated = 0;
}
#endif

#if !NONMATCHING
// Switch jump tables of fn_3_15B494; mwcc emits them itself once the function matches.
void* jumptable_3_data_26F2C[8] = {
    (u8*)fn_3_15B494 + 0x38, (u8*)fn_3_15B494 + 0x84, (u8*)fn_3_15B494 + 0xA8, (u8*)fn_3_15B494 + 0xC0,
    (u8*)fn_3_15B494 + 0x124, (u8*)fn_3_15B494 + 0x16C, (u8*)fn_3_15B494 + 0x16C, (u8*)fn_3_15B494 + 0x13C,
};
#endif

// .text:0x0015B494 size:0x17C
// NONMATCHING 95%: case 3 roster lookup address arithmetic scheduled differently (r4/r5 swap); rest only jumptable label
#if NONMATCHING
void fn_3_15B494(void) {
    switch (g_Practice.practiceState) {
    case 0:
        lbl_8036E548.state = 0;
        lbl_8036E548._2D7A[1] = 0;
        lbl_8036E548._2D7C = 0;
        lbl_3_common_bss_32724._9C = 0;
        g_Practice._1D9 = 0;
        g_Practice._1C7 = 0;
        lbl_8036E548._307D = 0;
        fn_3_15B204();
        fn_3_15B0D8();
        fn_80011BE4(9);
        fn_3_B3C94(1);
        break;
    case 1:
        if (fn_8001594C(g_GameLogic.teamFielding) != 0) {
            fn_3_B3C94(2);
        }
        break;
    case 2:
        if (fn_3_750DC() != 0) {
            fn_3_B3C94(3);
        }
        break;
    case 3:
        {
            s32 t = g_GameLogic.homeTeamBattingInd_fieldingTeam;
            if (fn_80014D4C(inMemRoster[g_GameLogic.teamBatting][g_GameLogic.battingOrderAndPositionMapping[t][g_GameLogic.currentBatterPerTeam[t]][0]].stats.CharID) != 0) {
                fn_3_B3C94(4);
            }
        }
        break;
    case 4:
        if (fn_3_B3CD4() != 0) {
            fn_3_B3C94(7);
        }
        break;
    case 7:
        fn_3_B3B70();
        g_GameLogic.freeFieldingPracticeInd = 1;
        g_GameLogic.TeamStars[0] = 5;
        g_GameLogic.TeamStars[1] = 5;
        fn_3_5A6D4(7);
        fn_3_B3C78(3);
        break;
    }
}
#endif

// .text:0x0015A244 size:0x204
void fn_3_15A244(void) {
    PracticeMsgTask* o = (PracticeMsgTask*)lbl_803CC1B8;
    s32 i;

    fn_80034E20(o, lbl_3_data_B1BC);
    for (i = 0; i < 5; i++) {
        lbl_80371C30[o->baseIdx + i + 6].obj->_5C = lbl_3_data_B3DC[lbl_3_data_FAC4[i]] << 16;
    }
    o->state = 1;
    if (g_Practice.practiceType_1 == 1 || g_Practice.practiceType_1 == 2 || g_Practice.practiceType_1 == 3 ||
        g_Practice.practiceType_1 == 4 || g_Practice.practiceType_1 == 5) {
        lbl_80371C30[o->baseIdx].obj->_64 = lbl_3_data_B3E8[g_Practice.practiceType];
        lbl_80371C30[o->baseIdx].obj->_5C = 0x320000;
        lbl_80371C30[o->baseIdx].obj->_68 = 4;
        lbl_80371C30[o->baseIdx + 1 + g_Practice.practiceType].obj->_5C = 0x690000;
        lbl_80371C30[o->baseIdx + 11 + g_Practice.practiceType].obj->_5C = 0x690000;
        o->state = 5;
    }
    lbl_3_common_bss_32724._C0 = 1;
    lbl_803CC1B8->func = fn_3_159D50;
}

// .text:0x00157E28 size:0x284
void fn_3_157E28(void) {
    PracticeMsgTask* o = (PracticeMsgTask*)lbl_803CC1B8;
    LayoutObj* obj;

    if (lbl_3_common_bss_32724.hudOff != 0) {
        goto end;
    }
    if (o->state == 0) {
        o->text = fn_8000F988((LayoutGroup*)o, 4, 0, 5, 0, 0);
        lbl_80366B18.entries[o->text].hAlign = 0;
        lbl_80366B18.entries[o->text].vAlign = 1;
        fn_8000FD9C(o->text, 2, 0);
        o->state++;
    } else if (o->state == 1) {
        obj = lbl_80371C30[o->baseIdx].obj;
        if ((obj->_5C >> 16) >= 0xF) {
            obj->_68 = 0;
        }
        if (g_Practice.loadingGuidedPractice == 0) {
            if (g_Practice._1C7 != 0) {
                goto end;
            }
            lbl_80371C30[o->baseIdx + 1].obj->_68 = 4;
            lbl_80371C30[o->baseIdx + 2].obj->_68 = 4;
            lbl_80371C30[o->baseIdx + 2].obj->_5C = 0x90000;
            o->state++;
        }
    } else if (o->state == 2) {
        if ((lbl_80371C30[o->baseIdx + 1].obj->_5C >> 16) == 0) {
            goto end;
        }
    }
    if (g_Practice._1C7 != 0) {
        lbl_80371C30[o->baseIdx + 3].obj->flags &= ~2;
    } else {
        lbl_80371C30[o->baseIdx + 3].obj->flags |= 2;
    }
    if (g_Practice._188 == 1) {
        fn_8000FE08(o->text, 5,
            lbl_3_data_104B8[g_Practice.practiceLevel_2][g_Practice._1D7][g_Practice._1D8]);
    }
    g_Practice.currentMessageDoneTyping = lbl_80366B18.entries[o->text].finished;
    return;
end:
    fn_8000FEE8(o->text);
    fn_8000F8F4((LayoutGroup*)o);
    fn_80034CEC(o);
    REMOVE_QUEUE_NOARG();
}

// .text:0x0015B204 size:0x290
void fn_3_15B204(void) {
    s32 i;
    s32 found;

    for (i = 0; i < 9; i++) {
        fn_3_B4124(0, i, lbl_3_data_FAA8[1][i], -1);
        if (g_GameLogic.secondaryGameMode == 0x10) {
            fn_3_B4124(1, i, lbl_3_data_FAA8[2][i], -1);
        } else {
            fn_3_B4124(1, i, lbl_3_data_FAA8[0][i], -1);
        }
    }
    if (g_GameLogic.secondaryGameMode == 0xF) {
        if (g_Minigame._19E8[g_Practice.homeAway]._0 == 1) {
            fn_3_B4124(0, 0, 0, -1);
        } else {
            fn_3_B4124(0, 0, 1, -1);
        }
        fn_3_B4124(1, 0, g_Minigame._19E8[g_Practice.homeAway]._0, g_Minigame.battingHandedness[g_Practice.homeAway]);
        return;
    }
    fn_3_B4124(0, 0, g_Minigame._19E8[g_Practice.homeAway]._0, g_Minigame.battingHandedness[g_Practice.homeAway]);
    found = 0;
    for (i = 1; i < 9; i++) {
        if (g_Minigame._19E8[g_Practice.homeAway]._0 == inMemRoster[0][i].stats.CharID) {
            fn_3_B4124(0, i, 0x2E, -1);
            found = 1;
            break;
        }
    }
    if (found == 0) {
        for (i = 0; i < 9; i++) {
            if (inMemRoster[1][i].stats.CharID == g_Minigame._19E8[g_Practice.homeAway]._0) {
                if (i == 0 || i == 1 || i == 8) {
                    fn_3_B4124(1, i, 3, -1);
                } else if (i == 2 || i == 3 || i == 4) {
                    fn_3_B4124(1, i, 0x13, -1);
                } else {
                    fn_3_B4124(1, i, 0x11, -1);
                }
                break;
            }
        }
    }
}

// .text:0x0015A75C size:0x298
void fn_3_15A75C(void) {
    if (g_GameLogic.hudElementLoadingInd != 0 && lbl_3_common_bss_32724._A5 == 0 && g_Practice.instructionNumber < 0) {
        lbl_3_common_bss_32724._A5 = 1;
        lbl_3_common_bss_32724._A6 = 0;
        lbl_3_common_bss_32724._A7 = 0xFF;
        if (g_Practice.practiceLevel == 4) {
            fn_800B0A5C_insertQueue(fn_3_9976C, 2);
        } else if (g_Practice.practiceLevel == 5) {
            fn_800B0A5C_insertQueue(fn_3_99BDC, 2);
        } else if (g_Practice.practiceType_2 == 4) {
            fn_800B0A5C_insertQueue(fn_3_9C28C, 2);
            fn_800B0A5C_insertQueue(fn_3_9A8A4, 2);
        } else if (g_Practice.practiceType_2 == 0) {
            if (g_Practice.practiceLevel == 1) {
                fn_800B0A5C_insertQueue(fn_3_99BDC, 2);
            }
        } else if (g_Practice.practiceType_2 == 1) {
            if (g_Practice.practiceLevel == 1) {
                fn_800B0A5C_insertQueue(fn_3_9976C, 2);
            }
        }
    }
    if (lbl_3_common_bss_32724._A5 != 0 && lbl_3_common_bss_32724._A6 < 0xFF) {
        if (lbl_3_common_bss_32724._A6 < 0xF0) {
            lbl_3_common_bss_32724._A6 += 0x10;
        } else {
            lbl_3_common_bss_32724._A6 = 0xFF;
        }
    }
    if (lbl_3_common_bss_32724._A7 != 0 && lbl_3_common_bss_32724._A7 < 0xFF) {
        if (lbl_3_common_bss_32724._A7 <= 0x10) {
            lbl_3_common_bss_32724._A7 = 0;
            lbl_3_common_bss_32724._A5 = 0;
        } else {
            lbl_3_common_bss_32724._A7 -= 0x10;
        }
    } else if (lbl_3_common_bss_32724._A5 != 0) {
        if (g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 0 && g_GameLogic.gameStatus != 7) {
            lbl_3_common_bss_32724._A7 = 0xF0;
        }
        if (lbl_3_common_bss_34C90._1D5 != 0) {
            lbl_3_common_bss_32724._A7 = 0xF0;
        }
        if (g_Practice._19F != 0 &&
            (lbl_3_common_bss_34C90.state == 7 || lbl_3_common_bss_34C90.state == 9 || lbl_3_common_bss_34C90.state == 0xB)) {
            lbl_3_common_bss_32724._A7 = 0;
            lbl_3_common_bss_32724._A5 = 0;
        }
        if (g_Practice._1C7 != 0 &&
            (lbl_3_common_bss_34C90.state == 5 || lbl_3_common_bss_34C90.state == 0xB || lbl_3_common_bss_34C90.state == 7)) {
            lbl_3_common_bss_32724._A7 = 0;
            lbl_3_common_bss_32724._A5 = 0;
        }
    }
    if (g_GameLogic.gameStatus == 8) {
        lbl_3_common_bss_32724._A7 = 0;
        lbl_3_common_bss_32724._A5 = 0;
    }
}

// .text:0x001583AC size:0x304
void fn_3_1583AC(void) {
    PracticeTask* o = (PracticeTask*)lbl_803CC1B8;
    s32 v;
    s32 c;
    s32 i;
    s32 any;

    if (lbl_3_common_bss_32724.hudOff == 0 && (g_Practice._1C7 == 0 || lbl_3_common_bss_34C90.state != 0) &&
        (g_Practice._19F == 0 || (lbl_3_common_bss_34C90.state != 7 && lbl_3_common_bss_34C90.state != 0xB))) {
        if (o->timer == 0) {
            for (i = 0; i < 4; i++) {
                PracticeMsgEntry* e = &lbl_3_data_103B8[g_Practice.practiceType_2][g_Practice.practiceLevel][i];
                if (e->enabled != 0) {
                    o->text[i] = fn_8000F988((LayoutGroup*)o, i + 0x12, 0, 5, e->msg, 0);
                    lbl_80366B18.entries[o->text[i]].hAlign = 1;
                    lbl_80366B18.entries[o->text[i]].vAlign = 1;
                }
            }
            o->timer++;
        }
        // fn_3_158264(o) written out: calling it colors its locals differently
        {
            u8* row = lbl_3_data_FAF4 + g_Practice.practiceType_2 * 4;
            v = row[g_Practice.practiceLevel];
            fn_800363D8(o, 1, 3, 0x32, v);
            fn_800363D8(o, 1, 4, 0x32, v);
            c = g_Practice.guidedPracticeCounter;
            fn_800363D8(o, 1, 1, 0x32, c);
            fn_800363D8(o, 1, 2, 0x32, c);
            if (c != o->_1A) {
                LayoutSlot* t = &lbl_80371C30[1];
                LayoutObj* q = t[o->baseIdx].obj;
                if ((q->_5C >> 16) <= 9) {
                    q->_5C = 0xA0000;
                    t[o->baseIdx].obj->_68 = 1;
                }
                q = t[o->baseIdx].obj;
                if ((q->_5C >> 16) >= 0x13) {
                    q->_5C = 0x90000;
                    t[o->baseIdx].obj->_68 = 0;
                    o->_1A = c;
                }
            }
        }
    } else {
        any = 0;
        for (i = 0; i < 4; i++) {
            if (lbl_3_data_103B8[g_Practice.practiceType_2][g_Practice.practiceLevel][i].enabled > 0) {
                fn_8000FEE8(o->text[i]);
                any = 1;
            }
        }
        if (any) {
            fn_8000F8F4((LayoutGroup*)o);
        }
        lbl_3_common_bss_32724._C6 = 0;
        fn_80034CEC(o);
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x0015A448 size:0x314
void fn_3_15A448(void) {
    if (g_GameLogic.secondaryGameMode == 0xA) {
        if (lbl_3_common_bss_32724._D9 == 0 && g_GameLogic.framesOfExitingToMenu == 0) {
            fn_800B0A5C_insertQueue(fn_3_12C3F0, 2);
            fn_800B0A5C_insertQueue(fn_80053FE8, 2);
            lbl_8034E978.menu = 0x3C;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[0x3C].track;
        }
        if (g_Practice.practiceType_1 == 0) {
            if (g_Practice.practiceState == 2) {
                if (lbl_3_common_bss_32724._C0 == 0) {
                    fn_800B0A5C_insertQueue(fn_3_15A244, 2);
                }
                if (lbl_3_common_bss_32724._BC == 0) {
                    fn_800B0A5C_insertQueue(fn_3_12BFE8, 2);
                }
                lbl_8034E978.menu = 0x3C;
                lbl_8034E978.prevTrack = lbl_8034E978.track;
                lbl_8034E978.track = lbl_800FEF70[0x3C].track;
            }
            if (g_Practice.practiceState == 7 && g_Practice.framesSincePracticeMenuDefaultTransition == 1) {
                fn_8004CC4C(0, 1, 1, 0, 0x89);
                fn_800B0A5C_insertQueue(fn_8004D0F0, 2);
            }
        }
        if ((g_Practice.practiceType_1 == 1 || g_Practice.practiceType_1 == 2 || g_Practice.practiceType_1 == 3 ||
            g_Practice.practiceType_1 == 4 || g_Practice.practiceType_1 == 5) &&
            g_Practice.practiceState == 0) {
            if (lbl_3_common_bss_32724._C0 == 0) {
                fn_800B0A5C_insertQueue(fn_3_15A244, 2);
            }
            if (lbl_3_common_bss_32724._C1 == 0) {
                fn_800B0A5C_insertQueue(fn_3_1599B8, 2);
            }
            if (lbl_3_common_bss_32724._BC == 0) {
                fn_800B0A5C_insertQueue(fn_3_12BFE8, 2);
            }
            lbl_8034E978.menu = 0x3D;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[0x3D].track;
        }
    }
    if (g_Practice.practiceType_1 == 6) {
        if (g_Practice.practiceState == 1 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            if (lbl_3_common_bss_32724._C1 == 0) {
                lbl_3_common_bss_32724._C2 = 1;
                fn_800B0A5C_insertQueue(fn_3_1599B8, 2);
            }
            fn_800B0A5C_insertQueue(fn_80051D00, 2);
            fn_800B0A5C_insertQueue(fn_3_159590, 2);
            lbl_8034E978.menu = 0x3E;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[0x3E].track;
        }
        if (g_Practice.practiceState == 5) {
            fn_80050F78(0);
        }
        if (g_Practice.practiceState == 4) {
            fn_80050F78(1);
        }
    }
}

// .text:0x001586B0 size:0x314
void fn_3_1586B0(void) {
    PracticeTask* o = (PracticeTask*)lbl_803CC1B8;
    s32 i;
    s16 msg;

    fn_80034E20(o, lbl_3_data_BA70);
    if (g_Practice.practiceType_2 == 2 || g_Practice.practiceType_2 == 3) {
        lbl_80371C30[o->baseIdx].obj->_64 = 0x3B;
    }
    o->_1A = g_Practice.guidedPracticeCounter;
    if (g_Practice.practiceType_2 == 3) {
        lbl_80371C30[o->baseIdx + 1].obj->flags &= ~2;
    } else {
        fn_3_158264(o);
    }
    for (i = 0; i < 4; i++) {
        msg = lbl_3_data_103B8[g_Practice.practiceType_2][g_Practice.practiceLevel][i].enabled;
        if (msg == 0) {
            lbl_80371C30[o->baseIdx + 2 + i].obj->flags &= ~2;
        } else {
            lbl_80371C30[o->baseIdx + 0xE + i].obj->_5C = msg << 16;
        }
    }
    o->timer = 0;
    lbl_803CC1B8->func = fn_3_1583AC;
}

// .text:0x001599B8 size:0x398
void fn_3_1599B8(void) {
    PracticeTask* o = (PracticeTask*)lbl_803CC1B8;
    s32 i;

    fn_80034E20(o, lbl_3_data_B5D4);
    o->text[0] = 0xFFFF;
    o->text[1] = 0xFFFF;
    o->text[2] = 0xFFFF;
    o->text[3] = 0xFFFF;
    for (i = 0; i < 4; i++) {
        fn_800363D8(o, i + 2, 1, 0x77, i);
        fn_800363D8(o, i + 2, 2, 0x77, i + 4);
        if (g_Practice.practiceType_1 == 5 || g_Practice.practiceType_1 == 6) {
            lbl_80371C30[o->baseIdx + 0xA + i].obj->flags &= ~2;
        } else if (g_Practice.levelCleared[g_Practice.practiceType_2][i] == 0) {
            lbl_80371C30[o->baseIdx + 0xA + i].obj->flags &= ~2;
        }
        o->text[i] = fn_8000F988((LayoutGroup*)o, i + 0xE, i, 5, lbl_3_data_B834[g_Practice.practiceType_2][i], 0);
    }
    for (; i < 4; i++) {
        lbl_80371C30[o->baseIdx + 2 + i].obj->flags &= ~2;
        lbl_80371C30[o->baseIdx + 6 + i].obj->flags &= ~2;
        lbl_80371C30[o->baseIdx + 0xE + i].obj->flags &= ~2;
        lbl_80371C30[o->baseIdx + 0xA + i].obj->flags &= ~2;
    }
    o->timer = 0;
    if (lbl_3_common_bss_32724._C2 != 0) {
        o->timer = 2;
        lbl_80371C30[o->baseIdx].obj->_5C = 0xF0000;
    }
    lbl_3_common_bss_32724._C1 = 1;
    o->_1A = 0;
    lbl_803CC1B8->func = fn_3_1595F4;
}

// .text:0x0015A9F4 size:0x3A0
void fn_3_15A9F4(void) {
    if (g_GameLogic.secondaryGameMode == 0x11 || g_GameLogic.framesOfExitingToMenu != 0) {
        return;
    }
    if (g_GameLogic.secondaryGameMode == 0xA) {
        lbl_3_common_bss_32724._A7 = 0;
        fn_3_15A448();
        return;
    }
    if (g_Practice.practiceType_2 == 0 || g_Practice.practiceType_2 == 1 || g_Practice.practiceType_2 == 2 ||
        g_Practice.practiceType_2 == 3) {
        fn_3_1590C8();
    }
    if (g_Practice._1C7 != 0) {
        if (g_Practice.frames_onPauseScreen == 1) {
            fn_800B0A5C_insertQueue(fn_3_9894C, 2);
        }
    } else if (g_Practice._19F != 0) {
        if (lbl_3_common_bss_34C90.state == 1 && g_Practice.frames_onPauseScreen2 == 1) {
            if (lbl_3_common_bss_32724.pauseTitleShown == 0) {
                fn_800B0A5C_insertQueue(fn_3_98DE0, 2);
            }
            fn_800B0A5C_insertQueue(fn_3_9894C, 2);
        }
        if (lbl_3_common_bss_34C90.state == 3 && lbl_3_common_bss_34C90._1D3 == 3) {
            fn_800B0A5C_insertQueue(fn_3_983B8, 2);
        }
    }
    if (g_Practice.loadingGuidedPractice != 0 && g_Practice._1D5 == 0) {
        fn_800B0A5C_insertQueue(fn_3_1580AC, 2);
        g_Practice._1D5 = 1;
    }
    fn_3_97144();
    if ((g_Practice.practiceType_2 == 4 || g_Practice.practiceType_2 == 3) && g_Practice.practiceLevel != 4 &&
        g_Practice.practiceLevel != 5) {
        fn_3_96914();
    }
    fn_3_15A75C();
    if (g_Practice.practiceLevel == 7 || g_Practice.practiceLevel == 6) {
        fn_3_9143C();
    }
    fn_3_1589C4();
}

// .text:0x001595F4 size:0x3C4
void fn_3_1595F4(void) {
    PracticeTask* o = (PracticeTask*)lbl_803CC1B8;
    s32 i;

    if (g_GameLogic.secondaryGameMode == 0xA &&
        (g_Practice.practiceType_1 == 1 || g_Practice.practiceType_1 == 2 || g_Practice.practiceType_1 == 3 ||
         g_Practice.practiceType_1 == 4 || g_Practice.practiceType_1 == 5 || g_Practice.practiceType_1 == 6)) {
        if (o->timer == 0) {
            o->timer = 1;
        } else if (o->timer == 1) {
            if ((s32)(lbl_80371C30[o->baseIdx].obj->_5C >> 16) >= 0xF) {
                o->timer = 2;
            }
        } else if (o->timer == 2) {
            o->_1A += 0x20;
            if (o->_1A > 0xFF) {
                o->_1A = 0xFF;
            }
            for (i = 0; i < 4; i++) {
                if (g_Practice.subMenuCursor == i) {
                    if (g_Practice.practiceState == 3 || g_Practice.practiceState == 4) {
                        lbl_80371C30[o->baseIdx + 2 + i].obj->_68 = 1;
                        lbl_80371C30[o->baseIdx + 6 + i].obj->_68 = 1;
                    } else {
                        LayoutObj* obj = lbl_80371C30[o->baseIdx + 2 + i].obj;
                        if ((s32)(obj->_5C >> 16) < 9) {
                            obj->_68 = 1;
                        } else {
                            obj->_68 = 0;
                        }
                        lbl_80371C30[o->baseIdx + 6 + i].obj->_5C = 0x10000;
                        lbl_80371C30[o->baseIdx + 6 + i].obj->_68 = 0;
                    }
                } else {
                    lbl_80371C30[o->baseIdx + 2 + i].obj->_5C = 0;
                    lbl_80371C30[o->baseIdx + 2 + i].obj->_68 = 0;
                    lbl_80371C30[o->baseIdx + 6 + i].obj->_5C = 0;
                    lbl_80371C30[o->baseIdx + 6 + i].obj->_68 = 0;
                }
            }
            if (g_Practice.practiceType_1 != 6 && g_Practice.practiceState == 6) {
                o->timer = 3;
            }
        } else if (o->timer == 3) {
            if (o->_1A >= 0x20) {
                o->_1A -= 0x20;
            } else {
                o->_1A = 0;
            }
            lbl_80371C30[o->baseIdx].obj->_68 = 4;
            lbl_80371C30[o->baseIdx + 1].obj->_68 = 4;
        }
        for (i = 0; i < 4; i++) {
            LayoutObj* obj = lbl_80371C30[o->baseIdx + 0xE + i].obj;
            obj->color = o->_1A | (obj->color & ~0xFF);
        }
        return;
    }
    lbl_3_common_bss_32724._C1 = 0;
    lbl_3_common_bss_32724._C2 = 0;
    for (i = 0; i < 4; i++) {
        if (o->text[i] != 0xFFFF) {
            fn_8000FEE8(o->text[i]);
        }
    }
    fn_8000F8F4((LayoutGroup*)o);
    fn_80034CEC(o);
    REMOVE_QUEUE_NOARG();
}

// .text:0x00159114 size:0x47C
// NONMATCHING 99.8%: r0/r4/r6 coloring around the 0xD sprite frame compare in the common block
#if NONMATCHING
void fn_3_159114(void) {
    PracticeStepTask* o = (PracticeStepTask*)lbl_803CC1B8;
    s32 done;

    if (o->frames < 0xFFFE) {
        o->frames++;
    } else {
        o->frames = 0xFFFF;
    }
    if (lbl_3_common_bss_32724.hudOff != 0 || g_Practice.practiceType_1 != 6) {
        goto end;
    }
    if (o->step == 0) {
        o->step = 1;
        o->frames = 0;
    } else if (o->step == 1) {
        done = 0;
        if ((s32)(lbl_80371C30[o->baseIdx].obj->_5C >> 16) >= 0xE) {
            done |= 0x10;
            lbl_80371C30[o->baseIdx].obj->_68 = 0;
            lbl_80371C30[o->baseIdx + 2].obj->_68 = 0;
        }
        if (done == 0x10) {
            o->step = 2;
        }
    } else if (o->step == 2) {
        s32 id = g_Minigame._19E8[g_Practice.homeAway]._0;
        lbl_80371C30[o->baseIdx + 5].obj->_5C = lbl_3_data_A594[g_Minigame.battingHandedness[g_Practice.homeAway]] << 16;
        if (lbl_800E8558[id]._0[0] != 0 &&
            (s8)g_Minigame._19E8[g_Practice.homeAway]._1 == 0 && g_Minigame._19E8[g_Practice.homeAway]._6 == 0) {
            lbl_80371C30[o->baseIdx + 7].obj->flags |= 2;
        } else {
            lbl_80371C30[o->baseIdx + 7].obj->flags &= ~2;
        }
        if (g_Practice.practiceState == 4) {
            goto end;
        }
        if (g_Practice.practiceState == 5) {
            o->step = 3;
            o->frames = 0;
        }
    } else if (o->step == 3) {
        if (o->frames == 1) {
            lbl_80371C30[o->baseIdx].obj->_68 = 1;
            lbl_80371C30[o->baseIdx + 2].obj->_68 = 1;
        }
    }
    if (g_Minigame._19DA[0] >= 0) {
        ChallengeTeamInfo* c; // lbl_800E8558 (CharTableEntry in main/file_8004C5F8.h)
        if (g_Minigame._19E8[0]._0 != (practiceSprite(o->baseIdx + 0xD)->_5C >> 16)) {
            practiceSprite(o->baseIdx + 8)->_5C = 0;
            practiceSprite(o->baseIdx + 9)->_5C = 0;
        }
        practiceSprite(o->baseIdx + 8)->flags |= 2;
        practiceSprite(o->baseIdx + 8)->_68 = 1;
        practiceSprite(o->baseIdx + 9)->flags |= 2;
        practiceSprite(o->baseIdx + 9)->_68 = 1;
        practiceSprite(o->baseIdx + 0xD)->_5C = g_Minigame._19E8[0]._0 << 16;
        practiceSprite(o->baseIdx + 0xB)->flags |= 2;
        practiceSprite(o->baseIdx + 0xB)->_68 = 1;
        c = &lbl_800E8558[g_Minigame._19E8[0]._0];
        practiceSprite(o->baseIdx + 0xC)->_5C = lbl_3_data_9D50[c->_0[0]][c->_4[1]] << 16;
    } else {
        practiceSprite(o->baseIdx + 8)->_5C = 0;
        practiceSprite(o->baseIdx + 8)->flags &= ~2;
        practiceSprite(o->baseIdx + 9)->_5C = 0;
        practiceSprite(o->baseIdx + 9)->flags &= ~2;
        practiceSprite(o->baseIdx + 0xD)->_5C = 0x360000;
        practiceSprite(o->baseIdx + 0xB)->_5C = 0;
        practiceSprite(o->baseIdx + 0xB)->flags &= ~2;
    }
    return;
end:
    fn_80034CEC(o);
    REMOVE_QUEUE_NOARG();
}
#endif

// .text:0x00158B64 size:0x480
void fn_3_158B64(void) {
    PracticeMsgTask* o;
    s32 shown;
    LayoutObj* obj;
    u32 frame;
    s16 idx;

    shown = 0;
    o = (PracticeMsgTask*)lbl_803CC1B8;
    if (lbl_3_common_bss_32724.hudOff == 0 && (g_Practice.tutorialState != 2 || g_Practice.practiceState != 3)) {
        if (o->state == 0) {
            o->state++;
            idx = g_Practice.laukituTextChannelIndex = fn_8000F988((LayoutGroup*)o, 9, 0, 5, 0, 0);
            lbl_80366B18.entries[idx].hAlign = 0;
            lbl_80366B18.entries[idx].vAlign = 1;
            fn_8000FD9C(idx, 2, 0);
            idx = g_Practice.diagramTextChannelIndex = fn_8000F988((LayoutGroup*)o, 0xA, 0, 5, 0, 0);
            lbl_80366B18.entries[idx].hAlign = 1;
            lbl_80366B18.entries[idx].vAlign = 1;
        }
        if (g_Practice.instructionComplete_readyToAdvance != 0 || g_Practice.allInstructionsComplete != 0) {
            lbl_80371C30[o->baseIdx + 7].obj->flags |= 2;
        } else {
            lbl_80371C30[o->baseIdx + 7].obj->flags &= ~2;
        }
        obj = lbl_80371C30[o->baseIdx].obj;
        frame = obj->_5C >> 16;
        if (g_Practice.textRelatedIndicator != 0) {
            if ((s32)frame <= 0xF) {
                obj->_68 = 1;
            } else if (obj->_69 == 2) {
                shown = 1;
            }
        } else if ((s32)frame > 0xF) {
            obj->_68 = 4;
        } else if ((s32)frame < 0xF) {
            obj->_68 = 1;
        } else {
            obj->_68 = 0;
        }
        if (g_Practice.maybeControlFlag1 != 0 && shown != 0) {
            lbl_80371C30[o->baseIdx + 8].obj->_64 = lbl_3_data_BA5C[g_Practice.maybeControlFlag1];
            lbl_80371C30[o->baseIdx + 8].obj->flags |= 2;
            lbl_80371C30[o->baseIdx + 4].obj->_68 = 1;
            lbl_80371C30[o->baseIdx + 5].obj->_68 = 1;
            shown = lbl_80371C30[o->baseIdx + 4].obj->_69 == 2; // the original reuses the flag here
            if (shown) {
                lbl_80371C30[o->baseIdx + 10].obj->color = (lbl_80371C30[o->baseIdx + 10].obj->color & ~0xFF) | 0xFF;
            } else {
                lbl_80371C30[o->baseIdx + 10].obj->color &= ~0xFF;
            }
        } else {
            lbl_80371C30[o->baseIdx + 8].obj->flags &= ~2;
            lbl_80371C30[o->baseIdx + 4].obj->_68 = 4;
            lbl_80371C30[o->baseIdx + 5].obj->_68 = 4;
            lbl_80371C30[o->baseIdx + 10].obj->color &= ~0xFF;
        }
        lbl_80371C30[o->baseIdx + 6].obj->_5C = g_Practice.maybeControlFlag2 << 16;
        if (g_Practice.lakituTextIndex >= 0) {
            g_Practice.lakituTextIndex_stored = g_Practice.lakituTextIndex;
            g_Practice.lakituTextIndex = -1;
            fn_8000FE08(g_Practice.laukituTextChannelIndex, 5, g_Practice.lakituTextIndex_stored);
        }
        if (g_Practice.diagramTitleTextIndex >= 0) {
            g_Practice.diagramTitleTextIndex_stored = g_Practice.diagramTitleTextIndex;
            g_Practice.diagramTitleTextIndex = -1;
            fn_8000FE08(g_Practice.diagramTextChannelIndex, 5, g_Practice.diagramTitleTextIndex_stored);
        }
        g_Practice.currentMessageDoneTyping = lbl_80366B18.entries[g_Practice.laukituTextChannelIndex].finished;
        return;
    }
    g_Practice.currentMessageDoneTyping = 1;
    if (g_Practice.laukituTextChannelIndex >= 0) {
        fn_8000FEE8(g_Practice.laukituTextChannelIndex);
    }
    if (g_Practice.diagramTextChannelIndex >= 0) {
        fn_8000FEE8(g_Practice.diagramTextChannelIndex);
    }
    if (g_Practice.laukituTextChannelIndex >= 0 || g_Practice.diagramTextChannelIndex >= 0) {
        fn_8000F8F4((LayoutGroup*)o);
    }
    lbl_8034E978._26 = 1;
    fn_80034CEC(o);
    REMOVE_QUEUE_NOARG();
}

// .text:0x00159D50 size:0x4F4
void fn_3_159D50(void) {
    PracticeMsgTask* o = (PracticeMsgTask*)lbl_803CC1B8;
    LayoutObj* obj;
    u32 frame;
    s32 i;
    s32 done;

    if (lbl_3_common_bss_32724.hudOff == 0 && g_Practice.practiceType_1 != 6 && g_GameLogic.secondaryGameMode == 0xA) {
        if (o->state == 1) {
            obj = lbl_80371C30[o->baseIdx].obj;
            if ((obj->_5C >> 16) >= 0x19) {
                obj->_68 = 0;
                o->state = 2;
            }
        } else if (o->state == 2) {
            for (i = 0; i < 5; i++) {
                if (g_Practice.practiceType == i) {
                    obj = lbl_80371C30[o->baseIdx + i + 1].obj;
                    if ((obj->_5C >> 16) < 0x5A) {
                        obj->_68 = 1;
                        lbl_80371C30[o->baseIdx + i + 0xB].obj->_68 = 1;
                    } else {
                        obj->_5C = 0xA0000;
                        lbl_80371C30[o->baseIdx + i + 0xB].obj->_5C = 0xA0000;
                    }
                } else {
                    obj = lbl_80371C30[o->baseIdx + i + 1].obj;
                    frame = obj->_5C >> 16;
                    if (frame > 0xA) {
                        obj->_5C = 0xA0000;
                        lbl_80371C30[o->baseIdx + i + 1].obj->_68 = 4;
                        lbl_80371C30[o->baseIdx + i + 0xB].obj->_5C = 0xA0000;
                        lbl_80371C30[o->baseIdx + i + 0xB].obj->_68 = 4;
                    } else if (frame != 0) {
                        obj->_68 = 4;
                        lbl_80371C30[o->baseIdx + i + 0xB].obj->_68 = 4;
                    } else {
                        obj->_68 = 0;
                        lbl_80371C30[o->baseIdx + i + 0xB].obj->_68 = 0;
                    }
                }
            }
            if (g_Practice.practiceState == 5) {
                lbl_80371C30[o->baseIdx].obj->_68 = 1;
                lbl_80371C30[o->baseIdx].obj->_64 = lbl_3_data_B3E8[g_Practice.practiceType];
                lbl_80371C30[o->baseIdx + 1 + g_Practice.practiceType].obj->_68 = 1;
                lbl_80371C30[o->baseIdx + 1 + g_Practice.practiceType].obj->_5C = 0x5A0000;
                lbl_80371C30[o->baseIdx + 11 + g_Practice.practiceType].obj->_68 = 1;
                lbl_80371C30[o->baseIdx + 11 + g_Practice.practiceType].obj->_5C = 0x5A0000;
                o->state = 3;
            }
        } else if (o->state == 3) {
            obj = lbl_80371C30[o->baseIdx].obj;
            if ((obj->_5C >> 16) >= 0x28) {
                obj->_68 = 0;
            }
            if (g_Practice.practiceType_1 == 1 || g_Practice.practiceType_1 == 2 || g_Practice.practiceType_1 == 3 ||
                g_Practice.practiceType_1 == 4 || g_Practice.practiceType_1 == 5) {
                if (g_Practice.practiceState == 3) {
                    if (g_Practice.practiceType_2 == 4) {
                        lbl_80371C30[o->baseIdx].obj->_68 = 1;
                        o->state = 9;
                    }
                } else if (g_Practice.practiceState == 6) {
                    lbl_80371C30[o->baseIdx].obj->_68 = 4;
                    lbl_80371C30[o->baseIdx + 1 + g_Practice.practiceType].obj->_68 = 4;
                    lbl_80371C30[o->baseIdx + 11 + g_Practice.practiceType].obj->_68 = 4;
                    o->state = 4;
                }
            }
        } else if (o->state == 4) {
            done = 0;
            obj = lbl_80371C30[o->baseIdx].obj;
            if ((obj->_5C >> 16) <= 0x19) {
                done = 1;
                obj->_68 = 0;
            }
            obj = lbl_80371C30[o->baseIdx + 1 + g_Practice.practiceType].obj;
            if ((obj->_5C >> 16) <= 0x5A) {
                done++;
                obj->_68 = 0;
                lbl_80371C30[o->baseIdx + 11 + g_Practice.practiceType].obj->_68 = 0;
            }
            if (done >= 2) {
                o->state = 2;
            }
        } else if (o->state == 5) {
            obj = lbl_80371C30[o->baseIdx].obj;
            if ((obj->_5C >> 16) <= 0x28) {
                obj->_68 = 0;
                o->state = 3;
            }
        }
    } else {
        fn_80034CEC(o);
        REMOVE_QUEUE_NOARG();
        lbl_3_common_bss_32724._C0 = 0;
    }
}
