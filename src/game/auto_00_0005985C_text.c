#include "game/auto_00_0005985C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_80008E00.h"
#include "main/file_8004207C.h"
#include "main/file_80069BDC.h"
#include "main/file_8004C5F8.h"
#include "game/running_logic.h"         // g_RunningLogic
#include "game/auto_00_000AC9F8_text.h" // PauseMenuState
#include "game/auto_00_000249E8_text.h" // SceneWork
#include "game/auto_00_001658F0_text.h" // StarChanceState
#include "game/rep_3CE0.h"              // FadeState
#include "game/rep_1C0.h"               // RandSeedView
#include "game/auto_00_0009C578_text.h" // GameLineScore
#include "game/rep_AC8.h"               // FielderStateEntry

extern s32 fn_80022B68(void);
// From main/file_80021308.h (not includable here: its sound prototypes clash
// with include/static/UnknownHomes_Static.h).
typedef struct DiskFileEntry {
    /* 0x0 */ u32 offset;
    /* 0x4 */ u32 sizeFlags;
    /* 0x8 */ u32 aramOffset;
    /* 0xC */ u32 unkC;
} DiskFileEntry; // size: 0x10
typedef void (*AramQueueCallback)(DiskFileEntry* entry, void* dst, void* user);
extern s32 fn_80022CB4(DiskFileEntry* entry, void* dst, s32 mode, u32 aramAddr, AramQueueCallback callback, void* user);
extern DiskFileEntry lbl_800F1D78[];

#ifdef TARGET_PC
#include "main/aramloader.h" // ARAMLoader lbl_803C6CF8 (holds pointers)
#else
// View of lbl_803C6CF8 (ARAMLoader in main/file_800A6870.h, whose ARAMTransfer
// prototype clashes with include/static/UnknownHomes_Static.h).
typedef struct {
    /*0x000*/ u8 _000[0x715];
    /*0x715*/ u8 idle; // 1 when the pending disc/ARAM transfer finished (ARAMLoader.idle)
    /*0x716*/ u8 _716[0x724 - 0x716];
} ARAMLoaderView; // size: 0x724
extern ARAMLoaderView lbl_803C6CF8;
#endif
extern DiskFileEntry lbl_3_data_3D60;
extern DiskFileEntry lbl_3_data_3D70;
extern DiskFileEntry lbl_3_data_3D80[0x43];
extern void fn_800216F8(u8 group, s32 (*callback)(u8* state));
extern s32 fn_3_91064(u8* state);
extern s32 fn_3_90798(u8* state);
extern s32 fn_3_90928(void);
extern void fn_3_906FC(void);
extern void manageLoadingState(void);
extern void fn_8001CE74(void);
extern void fn_3_B42A8(void);
extern void fn_8001A3FC(s32 arg);
extern void fn_80019A60(void);
extern s32 fn_3_1665E4(void);
extern s32 fn_3_106E50(void);
extern void fn_3_106DFC(void);
extern s32 fn_3_90764(u8* state);
extern void fn_8001A25C(void);
extern s32 fn_3_BF878(void);
extern s32 fn_3_11D6A0(void);
extern FadeState lbl_3_common_bss_35154;
extern s32 fn_3_910AC(u8* state);
extern s32 fn_3_90F48(u8* state);
extern s32 fn_800698F8(s32 charId);
extern s32 fn_80069B68(void);
extern void fn_3_F578(void);
extern void fn_3_753E8(int a);
extern void fn_3_58E50(void);
extern s32 someAnimationIndFunction(void);
extern void fn_3_90AB0(s32 a);
extern s32 fn_3_90C14(s32 a);
extern s32 random_fn_3_9EE24(s32 max);
extern void fn_3_1DC30(void);
extern void fn_3_1637EC(void);
extern void fn_3_7A154(s32 arg);
extern void fn_3_1DD48(void);
extern void fn_3_8A4E4(void);
extern s32 fn_8001C588(s32 id);
extern s32 fn_3_750DC(void);
extern void fn_3_1CCC8(void);
extern void fn_3_1658F0(void);
extern int rand(void);
extern void fn_8002024C(void);
extern void fn_3_79EF4(void);
extern void fn_3_AF5A4(void);
extern void fn_3_23CEC(void);
extern void fn_3_23890(void);
extern void fn_3_240F8(void);
extern void fn_3_234BC(void);
extern void fn_3_22C20(void);
extern void fn_3_230D4(void);
extern void fn_3_9D6A4(void);
extern void fn_3_8F21C(void);
extern void fn_3_8FC80(void);
extern s32 fn_80014F40(s32 id);
extern s32 fn_80014D4C(s32 id);
extern s32 fn_80014E50(s32 id);
extern s32 fn_3_6B5D8(void);
extern void fn_3_8C104(s32 v);
extern DiskFileEntry lbl_3_data_6130[0x3E];
extern void fn_3_164A74(void);
extern void fn_3_7BC20(void);
extern s16 lbl_3_data_6074[4]; // AI difficulty per challenge difficulty
// Bowser Jr. match starting situations: [home/away][difficulty][2]
typedef struct {
    /*0x0*/ s16 runs; // negative: the other team leads
    /*0x2*/ s16 outs;
    /*0x4*/ s16 bases; // 0x1: first, 0x10: second, 0x100: third
    /*0x6*/ s16 batter;
} BJStartSituation; // size: 0x8
extern BJStartSituation lbl_3_data_5FF4[2][4][2];
extern u8 lbl_8010B600[5][3]; // per challenge difficulty: innings, alt innings, mercy margin
extern SceneWork* lbl_3_common_bss_1323C;
extern SceneWork lbl_3_common_bss_134C4;
extern u8 lbl_3_data_60F0; // star chance percentage

#ifdef TARGET_PC
// SoundManager holds pointers, and main/file_80021308.h clashes with this
// unit's headers: reach SoundManager.unk39A[0] through port/game/views.c.
u8* port_sound_load_index(void);
#define lbl_800EF808 (*(struct { u8 loadIndex; }*)port_sound_load_index())
#else
// View of lbl_800EF808 (SoundManager in main/file_80021308.h).
typedef struct {
    /*0x000*/ u8 _000[0x39A];
    /*0x39A*/ u8 loadIndex; // roster slot whose sound bank is being loaded
    /*0x39B*/ u8 _39B;
} SoundManagerView; // size: 0x39C
extern SoundManagerView lbl_800EF808;
#endif

// View of lbl_8036E548 (CharMgr in main/file_80011640.h, which can't be
// included here next to main/file_8004207C.h: their fn_80024D2C prototypes clash).
#ifdef PORT_LP64 // offsets for 64-bit pointers (wasm32 uses the GameCube layout)
// PC: the fields where CharMgr/CharActor have them (offsets from clang's
// arm64 layout of main/file_80011640.h; rerun port/tools/pcview.py's checks
// if CharMgr changes).
typedef struct CharActorView {
    u8 _000[0x18];
    void** _0C;
    u8 _020[0x28A - 0x20];
    s8 kind;
    u8 _28B[0x2B8 - 0x28B];
} CharActorView; // size: 0x2B8

typedef struct CharMgrView {
    u8 _0000[0x88];
    void* slots6C;
    u8 _0090[0x1428 - 0x90];
    CharActorView actors[13];
    u8 _3780[0x3940 - 0x3780];
    struct {
        void* buffer;
        u32 size;
        s16 id;
        u8 state;
    } preload[3];
    u8 _3970[0x3987 - 0x3970];
    u8 state;
    u8 _3988[0x398B - 0x3988];
    u8 _2D7B; // CharMgr._2D7A[1]
    u8 _2D7C;
    u8 _2D7D;
    u8 _398E[0x3CB2 - 0x398E];
    u8 _307A;
    u8 _307B;
    u8 _307C;
    u8 _307D;
    u8 _307E;
    u8 _3CB7[0x3CB9 - 0x3CB7];
    u8 _3081;
    u8 _3082;
    u8 _3CBB[0x3CBF - 0x3CBB];
    u8 _3087;
    u8 _3088;
    u8 _3CC1[0x3E20 - 0x3CC1];
} CharMgrView; // size: 0x3E20 (CharMgr on PC)
#else
typedef struct CharActorView {
    /*0x000*/ u8 _000[0xC];
    /*0x00C*/ void** _0C;
    /*0x010*/ u8 _010[0x252 - 0x10];
    /*0x252*/ s8 kind;
    /*0x253*/ u8 _253[0x27C - 0x253];
} CharActorView; // size: 0x27C

typedef struct CharMgrView {
    /*0x0000*/ u8 _0000[0x6C];
    /*0x006C*/ void* slots6C;
    /*0x0070*/ u8 _0070[0xC04 - 0x70];
    /*0x0C04*/ CharActorView actors[13];
    /*0x2C50*/ u8 _2C50[0x2D3C - 0x2C50];
    /*0x2D3C*/ struct {
        void* buffer;
        u32 size;
        s16 id;
        u8 state;
    } preload[3];
    /*0x2D60*/ u8 _2D60[0x2D77 - 0x2D60];
    /*0x2D77*/ u8 state;
    /*0x2D78*/ u8 _2D78[3];
    /*0x2D7B*/ u8 _2D7B;
    /*0x2D7C*/ u8 _2D7C;
    /*0x2D7D*/ u8 _2D7D;
    /*0x2D7E*/ u8 _2D7E[0x307A - 0x2D7E];
    /*0x307A*/ u8 _307A;
    /*0x307B*/ u8 _307B;
    /*0x307C*/ u8 _307C;
    /*0x307D*/ u8 _307D;
    /*0x307E*/ u8 _307E;
    /*0x307F*/ u8 _307F[0x3081 - 0x307F];
    /*0x3081*/ u8 _3081;
    /*0x3082*/ u8 _3082;
    /*0x3083*/ u8 _3083[0x3087 - 0x3083];
    /*0x3087*/ u8 _3087;
    /*0x3088*/ u8 _3088;
    /*0x3089*/ u8 _3089[0x3154 - 0x3089];
} CharMgrView; // size: 0x3154
#endif
extern CharMgrView lbl_8036E548;
extern void fn_3_1E178(void);
extern void fn_3_7AFE4(void);
extern void setBatterContactConstants(void);
extern void fn_3_AFDA4(void);
extern void fn_3_1E154(void);
extern s32 fn_3_B32B8(void);
extern void fn_3_AFB64(void);
extern void fn_3_AFA64(void);
extern void fn_3_75560(void);
extern void atBat_batter(void);
extern void fn_3_31594(void);
extern void fn_3_7CE90(void);
extern void fn_3_77914(void);
extern void fn_3_899BC(void);
extern void fn_3_9E7D4(s32);
extern void fn_8006C9D8(void);
extern void fn_3_BF158(void);
extern void fn_3_BF1AC(void);
extern void fn_3_90CB0(void);
extern void fn_3_B95EC(void);
extern void fn_8001E474(void);
extern void fn_3_BC224(void);
extern void fn_3_972C8(void);
extern void fn_8001F228(void);
extern void fn_3_902FC(void);
extern void fn_3_8C07C(void);
extern void fn_3_90434(void);
extern void fn_3_5A6FC(void);
extern void fn_3_6011C(void);
extern void fn_3_FF4C(void);
extern void fn_3_6D304(void);
extern void fn_3_7D458(void);
extern void fn_3_668BC(void);
extern void fn_3_B482C(void);
extern void fn_3_DFBAC(void);
extern void fn_3_10FDC8(void);
extern void fn_3_66140(void);
extern void fn_3_664FC(void);
extern void fn_3_BBF94(void);
extern void fn_3_B93CC(void);
extern void fn_8003BF54(s32, s32, s32, s32, s32, s32, s32, s32, u8);
extern void fn_3_6C13C(void);
extern void fn_3_16598C(void);
extern void fn_800A7568(void);
extern void starMissionRelated2(void);
extern StarChanceState lbl_3_common_bss_37400;
extern InMemFielderType g_Fielders[9];
extern Unk32724 lbl_3_common_bss_32724;

extern FielderStateEntry lbl_3_data_3C40[];

extern void fn_80017D28(void* allocation);

extern void fn_3_58688(void);
extern void fn_3_583B8(void);
extern void fn_3_3B9E4(void);
extern void fn_3_736CC(void);
extern void fn_3_735A8(void);
extern void fn_8001AAA4(void);
extern void fn_3_6AEC0(void);
extern void ballPhysica(void);
extern void fn_3_8A958(void);
extern void fn_3_5DD30(void);
extern void fn_3_5E2C4(void);
extern void fn_3_79ACC(void);
extern void possiblyTransitionBlackScreen(void);
extern void fn_3_5BAC(void);
extern void fn_3_F1DC(void);
extern void fn_3_751B4(void);
extern void setDefaultInMemBatter(void);
extern void fn_3_8913C(void);
extern void fn_3_58870(void);
extern void fn_3_1DEB8(void);
extern void Set_803cb848(s32);
extern void fn_3_6EBB4(s32);
extern void fn_3_8A1D8(void);
extern void fn_3_6C108(void);
extern void fn_3_6B870(void);
extern s32 fn_3_6BA64(void);
extern u8 lbl_803CBC3C[];
extern void fn_3_6D4A0(void);
extern void fn_3_5A87C(void);
extern void fn_3_DFA20(void);
extern void fn_3_10FBE4(void);
extern void fn_3_6C150(void);
extern void fn_3_8F1C8(void);
extern void fn_3_5B0C4(void);
extern ScoresStruct g_Scores;
extern void fn_3_32090(void);
extern void fn_3_8911C(void);
extern void fn_3_8A350(void);
extern void fn_3_F7B8(void);
extern void fn_3_75434(void);
extern void fn_3_59338(void);
extern void fn_3_7B130(void);
extern void fn_3_22850(void);
extern int __abs(int);
extern u32 sndFXStartEx(u16 fid, u8 vol, u8 pan, u8 studio);
extern u8 lbl_800EFBA4[]; // menu sound volumes
extern void fn_3_7AF68(void);
extern void fn_3_9DB5C(void);
extern void fn_3_6C0E0(void);
extern void fn_3_67130(void);
extern void fn_3_8FC0C(void);
extern void fn_3_76558(void);
extern void* memset(void*, int, size_t);
extern void sndVolume(u8 volume, u16 time, u8 volGroup);
extern void fn_3_59F40(void);
extern void fn_3_59C2C(void);
extern void fn_3_5A28C(void);
extern s32 fn_3_6C938(s32, s32);
extern s32 fn_3_FD9FC(void);
extern void fn_3_90328(s32 vol);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern s32 fn_3_6BD6C(void);
extern u8 lbl_3_data_6104[8];
extern void fn_3_6EF1C(void);
extern void fn_3_754B8(void);
extern void initializeInMemBatter(void);
extern void fn_3_FBA8(void);
extern void fn_3_595C4(void);
extern void fn_3_8A5A4(void);
extern void fn_3_1E328(void);
extern void fn_3_7B308(void);
extern void fn_3_9DBE4(void);
extern void fn_3_7D780(void);
extern void fn_3_8FF18(void);
extern void fn_3_250FC(void);
extern void fn_3_8BE8C(void);
extern void initializeUnknown(void);
extern s32 fn_3_10007C(void);
extern void fn_3_E19E8(void);
extern void fn_3_6C1D8(void);
extern void fn_3_1663AC(void);
extern void fn_3_1CE90(void);
extern void fn_3_8DA80(void);

extern RandSeedView lbl_3_data_228;

typedef struct {
    /*0x00*/ s16 resultCoins[3]; // indexed by result: 0 win, 1 tie, 2 loss
    /*0x06*/ s16 winMarginPercent;
    /*0x08*/ s16 lossMarginPercent;
    /*0x0A*/ s16 starPercent;
    /*0x0C*/ s16 _0C[3];
    /*0x12*/ s16 bjCoins[3];
    /*0x18*/ s16 bjPoints[3];
    /*0x1E*/ s16 _1E;
} CoinRewardTable; // size: 0x20
extern CoinRewardTable lbl_3_data_607C;

#pragma dont_inline on

// fn_3_5D51C, size:0xCC
void fn_3_5D51C(void) {
    ScoresStruct* scores = &g_Scores;
    if (scores->bottomHalf == 0) {
        scores->bottomHalf = 1;
    } else {
        scores->bottomHalf = 0;
        scores->inning += 1;
    }
    g_GameLogic.homeTeamBattingInd_fieldingTeam ^= 1;
    g_GameLogic.awayTeamBattingInd_battingTeam ^= 1;
    g_GameLogic.teamBatting ^= 1;
    g_GameLogic.teamFielding ^= 1;
    g_GameLogic._131[0] = 0;
    g_GameLogic._131[1] = 0;
    g_Scores._A0 = g_Scores.runs[scores->bottomHalf][0];
    fn_3_5A684();
    fn_3_8A350();
    fn_3_F7B8();
    fn_3_75434();
    fn_3_59338();
    fn_3_7B130();
    fn_3_22850();
}

// fn_3_5C69C, size:0xB0
void fn_3_5C69C(s32 type) {
    g_Ball.framesSinceHit = 100;
    g_Ball.framesSincePickOff = 0;
    g_FieldingLogic._107 = type + 1;
    g_FieldingLogic.throwSpeedType = 3;
    fn_3_5A6D4(2);
    g_FieldingLogic._0AE = 0;
    g_Pitcher.peachDaisyStarAnimationOn = 0;
    fn_3_32090();
    fn_3_8911C();
    if (g_Strikes.balls >= 4) {
        g_Runners[0].runnerOnFieldOrOutOrScored = 5;
    } else {
        g_Runners[0].runnerOnFieldOrOutOrScored = 4;
    }
}

// fn_3_5D9F8, size:0xA4
void fn_3_5D9F8(void) {
    if (g_Stats.replayInd == 0) {
        g_Pitcher._15C = 0;
        if (g_d_GameSettings.GameModeSelected == 4 && g_Scores.bottomHalf == 0) {
            g_GameLogic.framesOfExitingToMenu = 1;
        } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
            fn_3_5A6D4(9);
        } else {
            fn_3_5A6D4(3);
        }
    }
}

// fn_3_5C530, size:0x98
s32 fn_3_5C530(s32 inning) {
    u8 finalInning = g_Scores.finalInning;
    if (inning > finalInning) {
        return 5;
    }
    if (finalInning <= 3U) {
        if (finalInning == inning && g_Scores.bottomHalf != 0) {
            return 4;
        }
        return 0;
    }
    if (inning == finalInning) {
        return 4;
    }
    if ((finalInning == 9 && inning >= 7) || (finalInning == 7 && inning >= 6)) {
        return 3;
    }
    if (inning >= 4) {
        return 2;
    }
    return 1;
}

// fn_3_5AE0C, size:0x90
void fn_3_5AE0C(void) {
    fn_3_6D4A0();
    unkSimulationRelatedStruct._08 = 0;
    unkSimulationRelatedStruct._07 = 0;
    fn_3_5A87C();
    if (g_d_GameSettings.GameModeSelected == 6) {
        fn_3_DFA20();
    } else if (g_d_GameSettings.GameModeSelected == 7) {
        fn_3_10FBE4();
    }
    g_Minigame._19AB = 0;
    fn_3_6C150();
    fn_3_8F1C8();
    lbl_803CC1B8->func = fn_3_5B0C4;
}

// fn_3_5CD24, size:0x90
void fn_3_5CD24(void) {
    GameControlsStruct* game = &g_GameLogic;
    if (game->_125 == 0) {
        lbl_3_common_bss_32724._9A = 0;
        fn_3_8A1D8();
        fn_3_6C108();
        fn_3_6B870();
        game->_125++;
    } else if (game->_125 == 1) {
        if (fn_3_6BA64() != 0) {
            lbl_803CBC3C[2] = 0;
            fn_3_5A6D4(0);
        }
    }
}

// fn_3_5F720, size:0x88
void fn_3_5F720(void) {
    fn_3_F1DC();
    fn_3_751B4();
    setDefaultInMemBatter();
    fn_3_8913C();
    fn_3_58870();
    fn_3_1DEB8();
    Set_803cb848(1);
    fn_3_6EBB4(g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]);
    g_FieldingLogic._0AE = 0;
    g_GameLogic.homeRunWordAnimationCompletedInd = 0;
    unkSimulationRelatedStruct._05 = 0;
    unkSimulationRelatedStruct._06 = 4;
}

// fn_3_5FE88, size:0x88
void fn_3_5FE88(void) {
    GameControlsStruct* game = &g_GameLogic;
    switch ((s32)game->_125) {
    case 0:
        fn_800B0A5C_insertQueue(possiblyTransitionBlackScreen, 2);
        game->_125 = 1;
        break;
    case 1:
        fn_800B0A5C_insertQueue(fn_3_5BAC, 4);
        game->_125 = 2;
        break;
    default:
        fn_3_5A6D4(5);
        break;
    }
}

// fn_3_5EDD8, size:0x80
void fn_3_5EDD8(void) {
    ballPhysica();
    fn_3_598D0();
    fn_3_8A958();
    if (g_Ball.deadBallReason != 0) {
        fn_3_5DD30();
    }
    fn_3_5C74C(0);
    fn_3_5E2C4();
    if (g_GameLogic.freeFieldingPracticeInd == 0) {
        fn_3_79ACC();
        if (g_Strikes.outs >= 3) {
            fn_3_5D094(0);
        }
    }
}

// fn_3_59BCC, size:0x60
s32 fn_3_59BCC(s32 stage) {
    SceneTask* queue = lbl_803CC1B8;
    if (stage < 1) {
        return 0;
    }
    if (stage == 1) {
        fn_8001AAA4();
    }
    if (queue->_10 != 0) {
        fn_3_6AEC0();
        return 1;
    }
    return 0;
}

// fn_3_5DCE0, size:0x50
s32 fn_3_5DCE0(void) {
    s32 handled = 0;
    if (g_Pitcher.strikeOutOrWalk == 1) {
        fn_3_736CC();
        handled = 1;
    } else if (g_Pitcher.strikeOutOrWalk == 2) {
        fn_3_735A8();
        handled = 1;
    }
    return handled;
}

// fn_3_5985C, size:0x74
void fn_3_5985C(s32 arg0, s32 arg1) {
    s32 v;
    InMemFielderType* fielder = &g_Fielders[arg0];
    if (arg0 == -1) {
        return;
    }
    fielder->_1D3[0] = arg1;
    v = lbl_3_data_3C40[arg1].anim;
    if (v >= 0) {
        g_FieldingLogic._0F8[arg0] = v;
    }
    fielder->_1D3[2] = 0;
    fielder->_1D3[3] = 0;
    fielder->_1A4 = 0;
    fielder->_1AC = 0;
    fielder->_1FF = 0;
    if (arg1 == 0x18) {
        g_FieldingLogic._0BC = arg0;
    }
}

// fn_3_598D0, size:0x48
void fn_3_598D0(void) {
    fn_3_58688();
    if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
        fn_3_583B8();
    } else {
        fn_3_3B9E4();
    }
}

// fn_3_5B408, size:0x14
void fn_3_5B408(void) {
    g_GameLogic.frame_exitMenuShowing = 0;
}

// fn_3_5B368, size:0x18
void fn_3_5B368(void) {
    g_GameLogic.frames_memoryCardWriteOnMVP = 0;
    g_GameLogic.endGameStage = 0;
}

// fn_3_5A684, size:0x1C
void fn_3_5A684(void) {
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_Strikes.outs = 0;
    g_Strikes.forcedOutToEndInningInd = 0;
}

// fn_3_59AC0, size:0x24
void fn_3_59AC0(DiskFileEntry* entry, void* dst, void* allocation) {
    fn_80017D28(allocation);
}

// fn_3_59B20, size:0xAC
void fn_3_59B20(void) {
    s32 i;
    if (g_d_GameSettings.GameModeSelected == 6) {
        for (i = 0; i < 4; i++) {
            CharActorView* actor = &lbl_8036E548.actors[i];
            fn_80022CB4(&lbl_800F1D78[actor->kind * 0x13 + 1], actor->_0C, 0, 0, fn_3_59AC0, actor);
        }
    }
}

// fn_3_59A90, size:0x30
void fn_3_59A90(void) {
    g_UnkSound_32718._02 = 0;
    g_UnkSound_32718._03 = 0;
    g_UnkSound_32718._04 = 0;
    g_UnkSound_32718._05 = 0;
    g_UnkSound_32718._06 = 0;
    g_UnkSound_32718._00 = 0;
    g_UnkSound_32718._07 = 0;
    g_UnkSound_32718._08 = 0;
}

// fn_3_59AE4, size:0x3C
s32 fn_3_59AE4(void) {
    if (g_d_GameSettings.GameModeSelected == 6) {
        return fn_80022B68();
    }
    return 1;
}

// fn_3_5A6D4, size:0x28
void fn_3_5A6D4(u8 status) {
    s8 previous;
    GameControlsStruct* game = &g_GameLogic;
    previous = game->gameStatus;
    game->FrameCountOfCurrentPitch = 0;
    game->gameStatus_prev = previous;
    game->gameStatus = status;
    game->FrameCountOfCurrentAtBat_Copy = 0;
    game->_125 = 0;
}

// fn_3_5ED98, size:0x40
void fn_3_5ED98(void) {
    fn_3_5A6D4(2);
    g_FieldingLogic._0AE = 0;
    g_Pitcher.peachDaisyStarAnimationOn = 0;
}

// fn_3_5A6A0, size:0x34
void fn_3_5A6A0(s32 a, s32 b, s32 c, s32 d) {
    GameControlsStruct* g = &g_GameLogic;
    g->homeTeamBattingInd_fieldingTeam = a;
    g->awayTeamBattingInd_battingTeam = a ^ 1;
    g->_000 = b;
    g->teamBatting = b ^ a;
    g->teamFielding = g->teamBatting ^ 1;
    g->_01C[0] = c;
    g->_01C[1] = d;
}

// fn_3_5CFD0, size:0xC4
void fn_3_5CFD0(void) {
    ChallengeState* t = &gChallengeState;
    s32 a = t->_441C;
    s32 b = t->_441E;
    if (g_d_GameSettings.exhibitionMatchInd == 0 && g_Scores.winningTeam <= 1 &&
        (g_Scores.winningTeam ^ (g_GameLogic._000 == lbl_3_common_bss_37400.humanPlayer)) != 0) {
        if ((t->_4422 >= 4 && b == 5) || (t->_4422 >= 5 && t->_44EF == 1 && a == 5)) {
            g_GameLogic.playOverFadeOutStarted = 0;
        }
        starMissionRelated2();
    }
}

// fn_3_5C5C8, size:0xD4
void fn_3_5C5C8(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        u8 st = g_Runners[i].runnerOnFieldOrOutOrScored;
        if (st == 1 || st == 3 || st == 4) {
            g_Scores._9C += 1;
            g_Runners[i].runnerOnFieldOrOutOrScored = 3;
        }
    }
}

// fn_3_5C418, size:0x118
void fn_3_5C418(void) {
    s32 inScene = 0;
    if (g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 2 || (u8)(g_GameLogic.gameStatus - 0x13) <= 3 ||
        g_GameLogic.gameStatus == 7) {
        inScene = 1;
    }
    if (unkSimulationRelatedStruct._08 == 0) {
        if (lbl_803C77B8._02 & 0x1000) {
            unkSimulationRelatedStruct._08 = 1;
        }
    } else {
        if (inScene != 0) {
            changeScene(3, 6);
        }
        if (lbl_8037169C._13 != 0 && inScene != 0) {
            if ((s32)lbl_803C6CF8.idle == 1) {
                lbl_3_common_bss_32724.hudOff = 1;
                g_GameLogic.framesOfExitingToMenu = 1;
                return;
            }
            if (unkSimulationRelatedStruct._09 == 0) {
                fn_800A7568();
                unkSimulationRelatedStruct._09 = 1;
            }
        }
    }
}

// fn_3_5D3FC, size:0x120
void fn_3_5D3FC(void) {
    s32 stage;
    GameInitVariables* gs = &g_d_GameSettings;
    s32 inning;
    u8 finalInning;
    g_GameLogic._135 = 0;
    g_GameLogic._136 = 0;
    g_RunningLogic._11 = 0;
    g_RunningLogic._13 = 0;
    g_RunningLogic.occupiedBases = 0;
    inning = g_Scores.inning;
    finalInning = g_Scores.finalInning;
    if (inning > finalInning) {
        stage = 5;
    } else if (finalInning <= 3U) {
        if (finalInning == inning && g_Scores.bottomHalf != 0) {
            stage = 4;
        } else {
            stage = 0;
        }
    } else if (inning == finalInning) {
        stage = 4;
    } else if ((finalInning == 9 && inning >= 7) || (finalInning == 7 && inning >= 6)) {
        stage = 3;
    } else if (inning >= 4) {
        stage = 2;
    } else {
        stage = 1;
    }
    g_Scores.inningStage = stage;
    g_Scores._C1 = 0;
    g_Scores._C6 = 0;
    lbl_3_common_bss_37400.state = 0;
    fn_3_6C13C();
    if (gs->exhibitionMatchInd == 0) {
        fn_3_16598C();
    }
}

// fn_3_5B220, size:0x148
s32 fn_3_5B220(s32 arg) {
    if (g_GameLogic.frames_memoryCardWriteOnMVP < 0x7FFE) {
        g_GameLogic.frames_memoryCardWriteOnMVP += 1;
    } else {
        g_GameLogic.frames_memoryCardWriteOnMVP = 0x7FFF;
    }
    switch ((s32)g_GameLogic.endGameStage) {
    case 0:
        if (arg == 1 && g_Minigame._1A3C == 0 && g_Minigame._1A44 == 0 && g_Minigame._1A45 == 0 && g_Minigame._1A43 == 0) {
            return 1;
        }
        fn_8003BF54(lbl_80366158._27, 0, 0, 1, 0, 4, 5, 0, 0);
        g_GameLogic.endGameStage += 1;
        break;
    case 1: {
        s16 v = lbl_803CC1B8->_10;
        if (v == 1 || (u16)(v - 0xB) <= 1U || v == 7) {
            g_GameLogic.endGameStage += 1;
        }
        break;
    }
    default:
        return 1;
    }
    return 0;
}

// fn_3_5ACA0, size:0x16C
void fn_3_5ACA0(void) {
    GameInitVariables* gs;
    if (g_GameLogic.framesOfExitingToMenu != 0) {
        fn_3_5A6FC();
        return;
    }
    if (g_GameLogic.FrameCountOfCurrentPitch < 0xFFFE) {
        g_GameLogic.FrameCountOfCurrentPitch += 1;
    } else {
        g_GameLogic.FrameCountOfCurrentPitch = 0xFFFF;
    }
    if (g_GameLogic.FrameCountOfCurrentAtBat_Copy < 0xFFFE) {
        g_GameLogic.FrameCountOfCurrentAtBat_Copy += 1;
    } else {
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0xFFFF;
    }
    fn_3_FF4C();
    fn_3_6D304();
    gs = &g_d_GameSettings;
    if (gs->GameModeSelected != 6 && gs->GameModeSelected != 7) {
        fn_3_7D458();
    }
    fn_3_668BC();
    if (gs->GameModeSelected == 2) {
        fn_3_B482C();
    } else if (gs->GameModeSelected == 6) {
        fn_3_DFBAC();
    } else if (gs->GameModeSelected == 7) {
        fn_3_10FDC8();
    } else if (g_GameLogic.secondaryGameMode == 0) {
        fn_3_6011C();
    }
    if (g_d_GameSettings.minigamesEnabled != 0) {
        fn_3_66140();
    } else {
        fn_3_664FC();
    }
    fn_3_BBF94();
    if (lbl_8036E548._3088 != 0) {
        fn_3_B93CC();
    }
    if (gs->GameModeSelected == 4 && lbl_80366158._2A == 0) {
        lbl_80366158._2A = 1;
    }
}

// fn_3_59918, size:0x178
void fn_3_59918(s32 x, s32 unused) {
    u8 gs;
    s32 i;
    if (g_Stats.replayInd != 0) {
        return;
    }
    if (g_Minigame.GameMode_MiniGame == 1 && g_Ball.deadBallReason != 2) {
        return;
    }
    gs = g_d_GameSettings.GameModeSelected;
    if (gs == 2 && (g_Practice.practiceLevel == 7 || g_Practice.practiceLevel == 6)) {
        if (x == 5) {
            return;
        }
    } else if (gs == 2 && g_Practice._186 != 0) {
        return;
    }
    if (gs == 6 && x == 5) {
        if (lbl_3_common_bss_32724._D3 != 0) {
            return;
        }
        lbl_3_common_bss_32724._D3 = 1;
    }
    if (g_GameLogic.playOver != 0) {
        return;
    }
    if (g_Scores._C5 != 0) {
        return;
    }
    if (x == 4) {
        if (g_Scores._C4 != 0) {
            return;
        }
        g_Scores._C4 = 1;
    }
    if (x == 0xD || x == 0x11) {
        if (g_Scores._C5 != 0) {
            return;
        }
        g_Scores._C5 = 1;
        g_GameLogic.gameOverInd = 1;
    }
    for (i = 0; i < 5; i++) {
        if (((u8*)&g_UnkSound_32718)[i + 2] == 0) {
            ((u8*)&g_UnkSound_32718)[i + 2] = x;
            return;
        }
    }
}

// fn_3_5A6FC, size:0x180
void fn_3_5A6FC(void) {
    switch ((s32)g_GameLogic.framesOfExitingToMenu) {
    case 1:
        if (g_d_GameSettings.GameModeSelected == 5 && g_d_GameSettings.bJMatchInd == 1) {
            g_d_GameSettings.home_AwaySetting ^= 1;
        }
        fn_3_BF1AC();
        lbl_3_common_bss_32724.hudOff = 1;
        if (g_d_GameSettings.minigamesEnabled != 0) {
            fn_3_90CB0();
            if (g_d_GameSettings.GameModeSelected != 6) {
                fn_3_B95EC();
            }
        } else {
            fn_3_B95EC();
        }
        fn_8001E474();
        fn_3_BC224();
        fn_3_972C8();
        fn_8001F228();
        fn_3_902FC();
        fn_3_8C07C();
        g_GameLogic.framesOfExitingToMenu += 1;
        g_d_GameSettings._55 = 1;
        return;
    case 2:
        g_GameLogic.framesOfExitingToMenu += 1;
        return;
    case 29:
        fn_3_90434();
        g_GameLogic.framesOfExitingToMenu += 1;
        return;
    case 30:
        if (g_GameLogic._128 != 0) {
            lbl_80366158._1C = 2;
        } else {
            lbl_80366158._1C = 1;
        }
        g_d_GameSettings.minigamesEnabled = 0;
        return;
    default:
        g_GameLogic.framesOfExitingToMenu += 1;
        return;
    }
}

// fn_3_5EE58, size:0x194
void fn_3_5EE58(void) {
    if (g_Stats.replayInd == 0) {
        fn_3_7CE90();
        fn_3_77914();
        g_GameLogic.playOverInd = 0;
        if (g_GameLogic.freeFieldingPracticeInd != 0) {
            fn_3_899BC();
            fn_3_9E7D4(g_GameLogic.homeTeamBattingInd_fieldingTeam);
        } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
            if (g_d_GameSettings.exhibitionMatchInd == 0 &&
                (g_GameLogic._000 ^ (g_Scores.winningTeam == g_d_GameSettings.humanTeamNumber)) != 0) {
                fn_8006C9D8();
            }
        } else if (g_Strikes.outs >= 3) {
            if (g_FieldingLogic._107 < 1U || g_FieldingLogic._107 > 3U || g_Strikes.balls >= 4) {
                fn_3_9E7D4(g_GameLogic.homeTeamBattingInd_fieldingTeam);
            }
            if (g_d_GameSettings.GameModeSelected == 2 && (g_Practice.practiceLevel == 7 || g_Practice.practiceLevel == 6)) {
                fn_3_899BC();
            }
        } else {
            fn_3_899BC();
            fn_3_9E7D4(g_GameLogic.homeTeamBattingInd_fieldingTeam);
        }
        fn_3_5A6D4(8);
        if (g_GameLogic.secondaryGameMode == 0 && g_Stats._39 == 1) {
            g_Stats._39 = 2;
        }
        fn_3_BF1AC();
        fn_3_BF158();
    }
}

// fn_3_5EFEC, size:0x168
void fn_3_5EFEC(void) {
    GameControlsStruct* game = &g_GameLogic;
    if (game->freeFieldingPracticeInd != 0) {
        if (fn_3_B32B8() != 0 || g_Practice.pauseMenuLoading != 0) {
            return;
        }
    } else {
        fn_3_AFB64();
        if (lbl_3_common_bss_34C90.active != 0) {
            fn_3_AFA64();
            return;
        }
    }
    if (g_GameLogic.frameCountdownAtBeginningOfAtBatLockout != 0) {
        g_GameLogic.frameCountdownAtBeginningOfAtBatLockout -= 1;
    }
    fn_3_75560();
    atBat_batter();
    fn_3_31594();
    fn_3_8A958();
    fn_3_5C74C(0);
    if (game->freeFieldingPracticeInd == 0 && (g_Strikes.outs >= 3 || (g_Strikes.storedOuts == 2 && g_Pitcher.strikeOutOrWalk == 1)) &&
        g_GameLogic.EventTriggers_EndOfGame == 0) {
        fn_3_5D094(0);
        if (g_GameLogic.EventTriggers_EndOfGame != 0) {
            fn_3_59918(0xD, 0);
        } else if (g_Scores._C3 == 0) {
            fn_3_59918(5, 0);
            g_Scores._C3 = 1;
        }
    }
    if (g_Pitcher.pitcherActionState == 6) {
        fn_3_5EE58();
    }
}

// fn_3_5F7A8, size:0x188
void fn_3_5F7A8(void) {
    s32 stage;
    GameInitVariables* gs = &g_d_GameSettings;
    s32 inning;
    u8 finalInning;
    g_GameLogic._135 = 0;
    g_GameLogic._136 = 0;
    g_RunningLogic._11 = 0;
    g_RunningLogic._13 = 0;
    g_RunningLogic.occupiedBases = 0;
    inning = g_Scores.inning;
    finalInning = g_Scores.finalInning;
    if (inning > finalInning) {
        stage = 5;
    } else if (finalInning <= 3U) {
        if (finalInning == inning && g_Scores.bottomHalf != 0) {
            stage = 4;
        } else {
            stage = 0;
        }
    } else if (inning == finalInning) {
        stage = 4;
    } else if ((finalInning == 9 && inning >= 7) || (finalInning == 7 && inning >= 6)) {
        stage = 3;
    } else if (inning >= 4) {
        stage = 2;
    } else {
        stage = 1;
    }
    g_Scores.inningStage = stage;
    g_Scores._C1 = 0;
    g_Scores._C6 = 0;
    lbl_3_common_bss_37400.state = 0;
    fn_3_6C13C();
    if (gs->exhibitionMatchInd == 0) {
        fn_3_16598C();
    }
    fn_3_5A684();
    fn_3_75434();
    fn_3_59338();
    fn_3_8A350();
    fn_3_1E178();
    fn_3_AFDA4();
    ((void (*)(void))fn_3_6C13C)();
    fn_3_7B130();
    setBatterContactConstants();
    ((void (*)(void))fn_3_8A1D8)();
    fn_3_7AFE4();
    fn_3_1E154();
    fn_3_6C108();
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_Strikes._1E = -1;
    g_Strikes.stateRelated = 0;
    g_GameLogic.frameCountdownAtBeginningOfAtBatLockout = 0x5A;
    g_GameLogic._13D = 0;
}

// fn_3_5B380, size:0x88
s32 fn_3_5B380(u16 buttons) {
    if (g_GameLogic.frame_exitMenuShowing < 0x7FFE) {
        g_GameLogic.frame_exitMenuShowing += 1;
    } else {
        g_GameLogic.frame_exitMenuShowing = 0x7FFF;
    }
    if (g_GameLogic.frame_exitMenuShowing > 0x14) {
        s32 choice = fn_8004CA6C(buttons);
        if (choice == 1) {
            return 1;
        } else if (choice == 2) {
            fn_8004CC2C();
        } else if (choice == 4) {
            return 2;
        }
    }
    return 0;
}

// fn_3_5B0C4, size:0x15C
void fn_3_5B0C4(void) {
    g_d_GameSettings.FrameCountWhileNotAtMainMenu++;
    lbl_80366158._28 = 0;
    lbl_80366158._28 = 0;
    fn_3_10007C();
    if (unkSimulationRelatedStruct._05 != 0) {
        if (unkSimulationRelatedStruct._06 == 0) {
            unkSimulationRelatedStruct._05 = 0;
        } else {
            unkSimulationRelatedStruct._06 -= 1;
            *lbl_803CBC3C = 1;
            goto skip;
        }
    }
    if (g_GameLogic.PauseSimulationFrameCount != 0) {
        if (--g_GameLogic.PauseSimulationFrameCount != 0) {
            lbl_80366158._28 = 1;
        } else {
            lbl_80366158._28 = 0;
        }
    }
    if (lbl_80366158._28 == 0) {
        lbl_3_data_228.counter += 1;
        fn_3_5ACA0();
    }
skip:
    if (g_d_GameSettings.minigamesEnabled != 0) {
        fn_3_E19E8();
    } else {
        fn_3_6C1D8();
        if (g_d_GameSettings.GameModeSelected == 2) {
            fn_3_1663AC();
        }
    }
    fn_3_1CE90();
    fn_3_8DA80();
    lbl_3_data_228.randomInt1 = g_Ball.StaticRandomInt1;
    lbl_3_data_228.randomInt2 = g_Ball.StaticRandomInt2;
    lbl_3_data_228.totalFrames += 1;
}

// fn_3_5B41C, size:0x184
void fn_3_5B41C(void) {
    s32 result = 2;
    s32 margin;
    if (g_Scores.winningTeam == 2) {
        result = 1;
    } else if (g_Scores.winningTeam == g_GameLogic._000) {
        result = 0;
    }
    if (g_d_GameSettings.bJMatchInd == 0) {
        g_d_GameSettings.challengeMinigame_baseCoinsEarned += lbl_3_data_607C.resultCoins[result];
        margin = __abs(g_Scores.runs[g_GameLogic._000][0] - g_Scores.runs[g_GameLogic._000 ^ 1][0]);
        if (result == 0) {
            g_d_GameSettings.challengeMinigame_baseCoinsEarned += margin * lbl_3_data_607C.winMarginPercent / 100;
        } else if (result == 2) {
            g_d_GameSettings.challengeMinigame_baseCoinsEarned += margin * lbl_3_data_607C.lossMarginPercent / 100;
        }
        g_d_GameSettings.challengeMinigame_baseCoinsEarned += g_GameLogic.TeamStars[0] * lbl_3_data_607C.starPercent / 100;
    } else {
        g_d_GameSettings.challengeMinigame_baseCoinsEarned += lbl_3_data_607C.bjCoins[result];
        g_d_GameSettings.bJMatchRelated += lbl_3_data_607C.bjPoints[result];
    }
}

// fn_3_5FF10, size:0x20C
void fn_3_5FF10(void) {
    s32 i;
    fn_3_6EF1C();
    g_GameLogic.currentBatterPerTeam[0] = 1;
    g_GameLogic.currentBatterPerTeam[1] = 1;
    g_GameLogic.TeamStars[0] = lbl_8034E9A0._470F[0];
    g_GameLogic.TeamStars[1] = lbl_8034E9A0._470F[1];
    if (lbl_800E8754._04 == 0) {
        g_GameLogic.TeamStars[0] = 0;
        g_GameLogic.TeamStars[1] = 0;
    }
    g_GameLogic.IsStarChance = 0;
    g_GameLogic.freeFieldingPracticeInd = 0;
    g_GameLogic.gameOverInd = 0;
    g_GameLogic.scoutFlag_VsScreenInd = 0;
    g_GameLogic.playBatterWalkupAnimation = 0;
    g_Scores.winningTeam = -1;
    g_Scores._AE = 0;
    g_Scores.inning = 1;
    g_Scores.bottomHalf = 0;
    g_Scores._C6 = 0;
    for (i = 0; i < 19; i++) {
        g_Scores.runs[0][i] = 0;
        g_Scores.runs[1][i] = 0;
        g_Scores._50[0][i] = 0;
        g_Scores._50[1][i] = 0;
    }
    for (i = 0; i < 2; i++) {
        g_Scores._A8[i] = 0;
        g_Scores._B3[i] = -1;
        g_Scores._B5[i] = -1;
        g_Scores._B7[i] = -1;
        g_Scores._B9[i] = 0;
        g_Scores._AF[i] = g_GameLogic.battingOrderAndPositionMapping[i][0][0];
        g_Scores._BB[i] = 1;
        g_Scores._BD[i] = 1;
    }
    fn_3_5A6D4(4);
    fn_3_754B8();
    initializeInMemBatter();
    fn_3_FBA8();
    fn_3_595C4();
    fn_3_8A5A4();
    fn_3_1E328();
    fn_3_7B308();
    fn_3_9DBE4();
    fn_3_7D780();
    fn_3_8FF18();
    fn_3_250FC();
    fn_3_8BE8C();
    initializeUnknown();
}

// fn_3_5CDB4, size:0x21C
void fn_3_5CDB4(void) {
    GameControlsStruct* game = &g_GameLogic;
    switch (game->_125) {
    case 0:
        changeScene(1, 6);
        g_GameLogic.scoreBook_teamDisplayed = 0;
        lbl_3_common_bss_32724._9B = 0;
        lbl_3_common_bss_32724._9A = 0;
        game->_125 = 1;
        break;
    case 1:
        if ((s8)game->playOverFadeOutStarted < 0 || game->scoreBook_teamDisplayed != 0) {
            if (g_GameLogic.FrameCountOfCurrentPitch >= 40 && fn_3_6C938(1, 0x1300) != 0) {
                game->_125 = 2;
            }
            if (fn_3_FD9FC() != 0) {
                game->_125 = 2;
            }
        }
        break;
    case 2:
        if (g_d_GameSettings.exhibitionMatchInd == 0 && g_d_GameSettings.bJMatchInd == 1) {
            fn_800203E0(0xC, (s8)lbl_3_data_6104[gChallengeState._441C]);
        } else {
            changeScene(3, 6);
        }
        fn_3_90328(-1);
        game->_125 = 3;
        break;
    case 3:
        if (lbl_8037169C._13 != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            game->_125 = 4;
        }
        break;
    case 4:
        if ((s8)game->playOverFadeOutStarted >= 0) {
            fn_3_5A6D4(0xE);
            fn_3_8C07C();
        } else if (g_d_GameSettings.exhibitionMatchInd == 0 && g_d_GameSettings.bJMatchInd == 1) {
            game->_125 = 5;
        } else {
            fn_3_5A6D4(0xE);
            fn_3_8C07C();
        }
        break;
    case 5:
        fn_3_8C07C();
        game->_125 = 6;
        break;
    case 6:
        game->_128 = 1;
        game->framesOfExitingToMenu = 1;
        break;
    }
    game = &g_GameLogic;
    if ((s8)game->playOverFadeOutStarted >= 0 && game->scoreBook_teamDisplayed == 0) {
        game->teamFielding = (s8)game->playOverFadeOutStarted;
        game->scoreBook_teamDisplayed = fn_3_6BD6C();
    }
}

// fn_3_5DD30, size:0x224
// NONMATCHING 89%: register allocation only (walk-off loop counters, case 3 tail scheduling)
#if NONMATCHING
void fn_3_5DD30(void) {
    s32 homeRuns;
    s32 i;
    s32 scored = 0;
    if (g_Ball.deadBallRBIsAddedInd != 0) {
        return;
    }
    if (g_Ball.deadBallReason == 3) {
        if (g_Runners[2].runnerOnFieldOrOutOrScored != 0) {
            scored = 1;
            g_Runners[2].scoredOnGRD = 1;
        }
        if (g_Runners[3].runnerOnFieldOrOutOrScored != 0) {
            scored++;
            g_Runners[3].scoredOnGRD = 1;
        }
        if (g_Scores.inning >= g_Scores.finalInning && g_Scores.bottomHalf != 0 &&
            g_Scores.runs[0][0] == g_Scores._9E && scored == 2) {
            scored = 1;
            g_Runners[2].scoredOnGRD = 0;
        }
        g_Ball.deadBallRBIsAddedInd = 1;
        lbl_3_common_bss_32A94._26 = scored;
        g_Scores.runs[g_Scores.bottomHalf][g_Scores.inning] = g_Scores._9E;
        g_Scores._9C = scored;
        if (g_Ball.AtBat_ContactResult == 0) {
            g_Ball.AtBat_ContactResult = 1;
        }
    } else if (g_Ball.deadBallReason == 4) {
        homeRuns = g_Scores.runs[1][0];
        for (i = 3; i >= 0; i--) {
            if (g_Runners[i].runnerOnFieldOrOutOrScored == 1 && (i >= 2 || g_Runners[i].baseReachedAtTimeOfThrow >= 2)) {
                g_Runners[i].scoredOnGRD = 1;
                homeRuns++;
                scored++;
            }
            if (g_Scores.inning >= g_Scores.finalInning && g_Scores.bottomHalf != 0 && g_Scores.runs[0][0] < homeRuns) {
                break;
            }
        }
        g_Scores._9C = scored;
        g_Ball.deadBallRBIsAddedInd = 1;
        lbl_3_common_bss_32A94._26 = scored;
        if (g_Ball.AtBat_ContactResult == 0) {
            g_Ball.AtBat_ContactResult = 1;
        }
    }
}
#endif

// fn_3_5AE9C, size:0x228
void fn_3_5AE9C(void) {
    changeScene(4, 0);
    g_GameLogic.framesOfExitingToMenu = 0;
    unkSimulationRelatedStruct._04 = 0;
    unkSimulationRelatedStruct._09 = 0;
    lbl_8036E548._307E = 0;
    g_d_GameSettings.minigamesEnabled = 0;
    g_d_GameSettings._13 = 0;
    g_d_GameSettings.someChallengeModeFlag = 0;
    lbl_8036E548._307A = 0;
    lbl_8036E548.slots6C = NULL;
    lbl_8036E548._307C = 0;
    lbl_8036E548._307D = 0;
    lbl_3_common_bss_32724._A4[0] = 0;
    g_d_GameSettings._55 = 0;
    g_d_GameSettings.challengeMinigame_baseCoinsEarned = 0;
    g_d_GameSettings.bJMatchRelated = 0;
    lbl_8036E548.preload[0].id = -1;
    lbl_8036E548.preload[1].id = -1;
    lbl_8036E548.preload[2].id = -1;
    g_GameLogic.teams[0] = g_d_GameSettings.PlayerPorts[0];
    g_GameLogic.teams[1] = g_d_GameSettings.PlayerPorts[1] % 4;
    g_GameLogic.logo[0].ID = lbl_8034E9A0._470D[g_d_GameSettings.home_AwaySetting];
    g_GameLogic.logo[1].ID = lbl_8034E9A0._470D[g_d_GameSettings.home_AwaySetting ^ 1];
    g_GameLogic.logo[0].variationID = g_GameLogic.logo[0].ID % 4;
    g_GameLogic.logo[1].variationID = g_GameLogic.logo[1].ID % 4;
    g_GameLogic.logo[0].captain = g_GameLogic.logo[0].ID / 4;
    g_GameLogic.logo[1].captain = g_GameLogic.logo[1].ID / 4;
    g_Scores._C7 = lbl_800E8754._05;
    if (g_d_GameSettings.GameModeSelected == 6 || g_d_GameSettings.GameModeSelected == 7) {
        g_d_GameSettings.minigamesEnabled = 1;
    }
    memset(&g_Minigame, 0, sizeof(g_Minigame));
    g_Minigame.GameMode_MiniGame = 0;
    sndVolume(0x7F, 0xA, 0xFF);
    if (g_d_GameSettings.GameModeSelected == 6 || g_d_GameSettings.GameModeSelected == 7) {
        lbl_8036E548._2D7D = 0;
        lbl_3_common_bss_32724._D7 = 0;
        lbl_803CC1B8->func = fn_3_59F40;
    } else if (g_d_GameSettings.GameModeSelected == 2) {
        lbl_803CC1B8->func = fn_3_59C2C;
    } else {
        lbl_803CC1B8->func = fn_3_5A28C;
    }
}

// fn_3_5DA9C, size:0x244
void fn_3_5DA9C(void) {
    fn_3_6B870();
    if (g_GameLogic.EventTriggers_EndOfGame != 0) {
        if (g_d_GameSettings.exhibitionMatchInd == 0 &&
            (g_GameLogic._000 ^ (g_Scores.winningTeam == g_d_GameSettings.humanTeamNumber)) != 0 &&
            (g_d_GameSettings.bJMatchInd != 1 ||
             (g_GameLogic._000 ^ (g_Scores.winningTeam != g_d_GameSettings.humanTeamNumber)) == 0)) {
            fn_8006C9D8();
        }
        fn_3_76558();
#ifdef TARGET_PC
        { extern void port_career_game_final(void); port_career_game_final(); }
#endif
    }
    g_GameLogic._135 = 0;
    g_GameLogic._136 = 0;
    g_GameLogic.playOverInd = 0;
    g_Scores._C1 = g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0] - g_Scores._A0;
    g_Pitcher._15D = 0;
    if (g_d_GameSettings.GameModeSelected == 4 &&
        (lbl_3_data_228.counter >= 0x2A30U || unkSimulationRelatedStruct._08 != 0)) {
        g_GameLogic.framesOfExitingToMenu = 1;
    } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
        if (g_Stats.replayInd == 0) { // inlined fn_3_5D9F8
            g_Pitcher._15C = 0;
            if (g_d_GameSettings.GameModeSelected == 4 && g_Scores.bottomHalf == 0) {
                g_GameLogic.framesOfExitingToMenu = 1;
            } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
                fn_3_5A6D4(9);
            } else {
                fn_3_5A6D4(3);
            }
        }
    } else if (g_Strikes.outs >= 3) {
        if (g_Stats.replayInd == 0) { // inlined fn_3_5D9F8
            g_Pitcher._15C = 0;
            if (g_d_GameSettings.GameModeSelected == 4 && g_Scores.bottomHalf == 0) {
                g_GameLogic.framesOfExitingToMenu = 1;
            } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
                fn_3_5A6D4(9);
            } else {
                fn_3_5A6D4(3);
            }
        }
    } else {
        fn_3_5A6D4(7);
    }
}

// fn_3_5F154, size:0x2A8
// NONMATCHING 99%: register allocation only (g_Scores base r8 vs r7 in the inlined fn_3_5F720 block)
#if NONMATCHING
void fn_3_5F154(void) {
    s32 diff;
    // inlined fn_3_5F720
    fn_3_F1DC();
    fn_3_751B4();
    setDefaultInMemBatter();
    fn_3_8913C();
    fn_3_58870();
    fn_3_1DEB8();
    Set_803cb848(1);
    fn_3_6EBB4(g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]);
    g_FieldingLogic._0AE = 0;
    g_GameLogic.homeRunWordAnimationCompletedInd = 0;
    unkSimulationRelatedStruct._05 = 0;
    unkSimulationRelatedStruct._06 = 4;
    g_Scores._9C = 0;
    g_Scores._9E = g_Scores.runs[g_Scores.bottomHalf][g_Scores.inning];
    g_Scores._A2 = g_Scores._A0;
    g_GameLogic._12F = 0;
    g_GameLogic._123 = 0;
    g_GameLogic.CountdownUntilFade = 999;
    g_GameLogic.PauseSimulationFrameCount = 0;
    g_GameLogic.playOver = 0;
    g_GameLogic.walkOffWinInd = 0;
    g_GameLogic.stadiumStarObtained = 0;
    g_Scores._A0 = g_Scores.runs[g_Scores.bottomHalf][0];
    g_Scores._C2 = 0;
    g_Scores._C4 = 0;
    g_Scores._C5 = 0;
    diff = g_Scores.runs[0][0] - g_Scores.runs[1][0];
    if (diff < -0x8000) {
        diff = -0x8000;
    }
    if (diff > 0x7FFF) {
        diff = 0x7FFF;
    }
    g_Scores._A6 = __abs(diff);
    g_Strikes.storedOuts = g_Strikes.outs;
    g_Strikes.runnerIndexForEachOutThisPitch[0] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[1] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[2] = -1;
    g_Strikes.GameControls_StrikeBallBitVector = g_Strikes.balls + g_Strikes.strikes * 16;
    g_Strikes.allForcedRunnersReachedTheirBaseInd = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_FieldingLogic._10E = 0;
    g_FieldingLogic._0EE = 0;
    g_FieldingLogic._10F = 0;
    g_FieldingLogic._110 = 0;
    g_FieldingLogic._128 = 0;
    g_FieldingLogic._129 = 0;
    g_FieldingLogic._0E4 = 0;
    g_RunningLogic._13 = 0;
    lbl_3_common_bss_34C90.active = 0;
    g_Practice._1B0 = 0;
    if (g_GameLogic.pre_PostMiniGameInd != 0) {
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.hudElementLoadingInd = 1;
        changeScene(1, 6);
    } else {
        g_GameLogic.minigameLastTurnSuccessInd = 0;
    }
    g_GameLogic.pre_PostMiniGameInd = 0;
    fn_3_5A6D4(1);
    if (g_GameLogic.playOverInd != 0) {
        g_GameLogic.playOverInd -= 1;
    }
    if (g_GameLogic.freeFieldingPracticeInd == 0 && g_GameLogic.EventTriggers_GameHasStarted == 0) {
        fn_3_59918(0xC, 0);
        g_GameLogic.EventTriggers_GameHasStarted = 1;
    }
    fn_3_7AF68();
    fn_3_9DB5C();
    fn_3_6C0E0();
    fn_3_67130();
    fn_3_8FC0C();
    if (lbl_3_common_bss_34C58._2A != 0) {
        lbl_3_common_bss_34C58._2A = 2;
        lbl_3_common_bss_34C58._24 = 120;
    }
}
#endif

// fn_3_5BA2C, size:0x314
void fn_3_5BA2C(void) {
    InputStruct* input = &g_Controls[lbl_80366158._27];
    if (lbl_3_common_bss_34C90.openedByBattingTeam == 0) {
        if (input->newButtonInput & 0x100) {
            if (lbl_3_common_bss_34C90.cursor == 0) {
                g_GameLogic._125 = 9;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            } else {
                lbl_3_common_bss_32724._CE = 1;
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                g_GameLogic._125 = 8;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            }
        } else if (input->newButtonInput & 2) {
            if (lbl_3_common_bss_34C90.cursor == 0) {
                lbl_3_common_bss_34C90.cursor = 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->newButtonInput & 1) {
            if ((s32)(u8)lbl_3_common_bss_34C90.cursor == 1) {
                lbl_3_common_bss_34C90.cursor = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    } else if (lbl_3_common_bss_32724._D2 == 0) {
        if (input->newButtonInput & 0x200) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = 8;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        } else if ((input->newButtonInput & 0x20) || (input->newButtonInput & 0x40)) {
            if (input->newButtonInput & 0x40) {
                g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 0;
            } else {
                g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 1;
            }
            g_GameLogic.scoreBook_teamDisplayed ^= 1;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (input->newButtonInput & 2) {
            if (g_GameLogic.scoreBook_batter_pitcherStatsDisplayed == 0) {
                g_GameLogic.scoreBook_batter_pitcherStatsDisplayed = 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->newButtonInput & 1) {
            if (g_GameLogic.scoreBook_batter_pitcherStatsDisplayed == 1) {
                g_GameLogic.scoreBook_batter_pitcherStatsDisplayed = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->buttonInput & 8) {
            if (g_GameLogic.scoreBook_scrollIndex != 0) {
                g_GameLogic.scoreBook_scrollIndex--;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->buttonInput & 4) {
            if (g_GameLogic.scoreBook_scrollIndex < 4) {
                g_GameLogic.scoreBook_scrollIndex++;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
}

// fn_3_59C2C, size:0x314
void fn_3_59C2C(void) {
    SceneTask* task = lbl_803CC1B8;
#ifdef TARGET_PC
    port_trace_value("fn_3_59C2C", unkSimulationRelatedStruct._04);
#endif
    switch (unkSimulationRelatedStruct._04) {
    case 0:
        task->_10 = 0;
        fn_800216F8(3, fn_3_91064);
        unkSimulationRelatedStruct._04++;
        break;
    case 1:
        if (task->_10 != 0) {
            task->_10 = 0;
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 2:
        fn_800216F8(g_d_GameSettings.StadiumID + 0x27, fn_3_90798);
        unkSimulationRelatedStruct._04++;
        break;
    case 3:
        if (task->_10 != 0) {
            task->_10 = 0;
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 4:
        lbl_3_data_228._10 = 0;
        fn_800B0A5C_insertQueue(manageLoadingState, 0);
        unkSimulationRelatedStruct._04++;
        break;
    case 5:
        if (lbl_3_data_228._10 == 1) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 6:
        if (fn_80035838(&lbl_3_data_3D80[0], 2) != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 7:
        if (fn_80035838(&lbl_3_data_3D80[0xE], 0xB) != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 8:
        if (fn_80035838(&lbl_3_data_3D80[0x1D], 9) != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 9:
        lbl_3_common_bss_34C58._00 = ARAMTransfer(&lbl_3_data_3D70, 0, 0, 0);
        unkSimulationRelatedStruct._04++;
        break;
    case 10:
        if ((s32)lbl_803C6CF8.idle == 1) {
            fn_3_906FC();
            lbl_3_common_bss_34C58._2C = 0;
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 11:
        if (fn_3_90928() != 0) {
            lbl_3_common_bss_34C58._2C = 0;
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 12:
        fn_8001CE74();
        fn_3_B42A8();
        fn_8001A3FC(2);
        lbl_8036E548._2D7D = 0;
        fn_80019A60();
        unkSimulationRelatedStruct._04++;
        break;
    case 13:
        if (lbl_8036E548._2D7D != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 14:
        if (fn_3_1665E4() != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 15:
        fn_3_106E50();
        unkSimulationRelatedStruct._04++;
        break;
    case 16:
        if ((s32)lbl_803C6CF8.idle == 1) {
            fn_3_106DFC();
            unkSimulationRelatedStruct._04++;
        }
        break;
    default:
        task->func = fn_3_5AE0C;
        break;
    }
}

#if !NONMATCHING
// Switch jump tables of fn_3_59F40; mwcc emits them itself once the function matches.
void* jumptable_3_data_41F4[19] = {
    (u8*)fn_3_59F40 + 0x4C, (u8*)fn_3_59F40 + 0x70, (u8*)fn_3_59F40 + 0xB8, (u8*)fn_3_59F40 + 0xDC,
    (u8*)fn_3_59F40 + 0x108, (u8*)fn_3_59F40 + 0x130, (u8*)fn_3_59F40 + 0x158, (u8*)fn_3_59F40 + 0x178,
    (u8*)fn_3_59F40 + 0x194, (u8*)fn_3_59F40 + 0x1B4, (u8*)fn_3_59F40 + 0x1D0, (u8*)fn_3_59F40 + 0x1E4,
    (u8*)fn_3_59F40 + 0x20C, (u8*)fn_3_59F40 + 0x240, (u8*)fn_3_59F40 + 0x274, (u8*)fn_3_59F40 + 0x298,
    (u8*)fn_3_59F40 + 0x2DC, (u8*)fn_3_59F40 + 0x304, (u8*)fn_3_59F40 + 0x32C,
};
#endif

// fn_3_59F40, size:0x34C
// NONMATCHING 92%: the original reaches lbl_3_data_3D60/3D80 (this unit's .data) through one pooled base
// (nmverify flags lbl_3_data_3D80 for that reason)
#if NONMATCHING
void fn_3_59F40(void) {
    SceneTask* task = lbl_803CC1B8;
    switch (unkSimulationRelatedStruct._04) {
    case 0:
        task->_10 = 0;
        lbl_3_common_bss_32724.loadStep = 0;
        unkSimulationRelatedStruct._04++;
        break;
    case 1:
        if (g_d_GameSettings.GameModeSelected == 6) {
            fn_800216F8(0x2D, fn_3_90798);
        } else {
            fn_800216F8(0x2E, fn_3_90764);
        }
        unkSimulationRelatedStruct._04++;
        break;
    case 2:
        if (task->_10 != 0) {
            task->_10 = 0;
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 3:
        lbl_3_common_bss_34C58._00 = ARAMTransfer(&lbl_3_data_3D60, 0, 0, 0);
        unkSimulationRelatedStruct._04++;
        break;
    case 4:
        if ((s32)lbl_803C6CF8.idle == 1) {
            fn_3_906FC();
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 5:
        fn_8001CE74();
        lbl_8036E548._2D7D = 0;
        fn_8001A25C();
        unkSimulationRelatedStruct._04++;
        break;
    case 6:
        if (lbl_8036E548._2D7D != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 7:
        if (fn_3_BF878() != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 8:
        if (lbl_3_common_bss_35154._3B0 == 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 9:
        if (fn_3_11D6A0() != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 10:
        fn_3_106E50();
        unkSimulationRelatedStruct._04++;
        break;
    case 11:
        if ((s32)lbl_803C6CF8.idle == 1) {
            fn_3_106DFC();
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 12:
        lbl_80366B18.tables[6] = (MsgTable*)ARAMTransfer(&lbl_3_data_3D80[0x40], 0, 1, 0);
        unkSimulationRelatedStruct._04++;
        break;
    case 13:
        if ((s32)lbl_803C6CF8.idle == 1) {
            fn_800111B4(lbl_80366B18.tables[6]);
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 14:
        if (fn_80035838(&lbl_3_data_3D80[0], 2) != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 15:
        if (fn_80035838(&lbl_3_data_3D80[0x3], 3) != 0) {
            if (g_d_GameSettings.GameModeSelected == 6) {
                unkSimulationRelatedStruct._04 = 16;
            } else {
                unkSimulationRelatedStruct._04 = 17;
            }
        }
        break;
    case 16:
        if (fn_80035838(&lbl_3_data_3D80[0x4], 0xE) != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 17:
        if (fn_80035838(&lbl_3_data_3D80[0x5], 0x14) != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 18:
        task->func = fn_3_5AE0C;
        break;
    }
}
#endif

#if !NONMATCHING
// Switch jump tables of fn_3_5A28C; mwcc emits them itself once the function matches.
void* jumptable_3_data_4240[19] = {
    (u8*)fn_3_5A28C + 0x48, (u8*)fn_3_5A28C + 0x64, (u8*)fn_3_5A28C + 0xC0, (u8*)fn_3_5A28C + 0xE8,
    (u8*)fn_3_5A28C + 0x10C, (u8*)fn_3_5A28C + 0x18C, (u8*)fn_3_5A28C + 0x1DC, (u8*)fn_3_5A28C + 0x20C,
    (u8*)fn_3_5A28C + 0x230, (u8*)fn_3_5A28C + 0x260, (u8*)fn_3_5A28C + 0x280, (u8*)fn_3_5A28C + 0x2A8,
    (u8*)fn_3_5A28C + 0x2F0, (u8*)fn_3_5A28C + 0x338, (u8*)fn_3_5A28C + 0x364, (u8*)fn_3_5A28C + 0x3D4,
    (u8*)fn_3_5A28C + 0x3D4, (u8*)fn_3_5A28C + 0x37C, (u8*)fn_3_5A28C + 0x3AC,
};
#endif

// fn_3_5A28C, size:0x3F0
// NONMATCHING 99%: scheduling only (lis inMemRoster placed one slot early in case 4)
#if NONMATCHING
void fn_3_5A28C(void) {
    SceneTask* task = lbl_803CC1B8;
#ifdef TARGET_PC
    port_trace_value("fn_3_5A28C", unkSimulationRelatedStruct._04);
#endif
    switch (unkSimulationRelatedStruct._04) {
    case 0:
        lbl_8037169C.lastPick = calledWhenStartingMatch();
        unkSimulationRelatedStruct._04++;
    case 1:
        lbl_3_common_bss_32724._A4[0] = 0;
        if (fn_80020218() != 0) {
            if (fn_80020278(lbl_8037169C.lastPick) != 0) {
                lbl_3_common_bss_32724._A4[0] = 1;
                unkSimulationRelatedStruct._04++;
            }
        } else {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 2:
        task->_10 = 0;
        fn_800216F8(1, fn_3_910AC);
        unkSimulationRelatedStruct._04++;
        break;
    case 3:
        if (task->_10 != 0) {
            task->_10 = 0;
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 4:
        {
            s16 id = fn_800698F8(inMemRoster[lbl_800EF808.loadIndex / 9][lbl_800EF808.loadIndex % 9].stats.CharID);
            fn_800216F8(id + 5, fn_3_90F48);
        }
        unkSimulationRelatedStruct._04++;
        break;
    case 5:
        if (task->_10 != 0) {
            if (lbl_800EF808.loadIndex != 17) {
                lbl_800EF808.loadIndex++;
                unkSimulationRelatedStruct._04 = 4;
            } else {
                lbl_800EF808.loadIndex = 0;
                task->_10 = 0;
                unkSimulationRelatedStruct._04++;
            }
        }
        break;
    case 6:
        fn_800216F8(g_d_GameSettings.StadiumID + 0x27, fn_3_90798);
        unkSimulationRelatedStruct._04++;
        break;
    case 7:
        if (task->_10 != 0) {
            task->_10 = 0;
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 8:
        lbl_3_data_228._10 = 0;
        fn_800B0A5C_insertQueue(manageLoadingState, 0);
        unkSimulationRelatedStruct._04++;
        break;
    case 9:
        if (lbl_3_data_228._10 != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 10:
        if (fn_80035838(&lbl_3_data_3D80[0], 2) != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 11:
        if (fn_80035838(&lbl_3_data_3D80[g_GameLogic.logo[0].ID / 4 + 0x11], 0xF) != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 12:
        if (fn_80035838(&lbl_3_data_3D80[g_GameLogic.logo[1].ID / 4 + 0x11], 0x10) != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 13:
        if (g_d_GameSettings.GameModeSelected == 4 && fn_80069B68() == 0) {
            break;
        }
        unkSimulationRelatedStruct._04++;
    case 14:
        fn_8001CE74();
        fn_8001A3FC(0);
        unkSimulationRelatedStruct._04 = 17;
        break;
    case 17:
        lbl_3_common_bss_34C58._00 = ARAMTransfer(&lbl_3_data_3D60, 0, 0, 0);
        unkSimulationRelatedStruct._04++;
        break;
    case 18:
        if ((s32)lbl_803C6CF8.idle == 1) {
            fn_3_906FC();
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 15:
    case 16:
    default:
        task->func = fn_3_5AE0C;
        break;
    }
}
#endif

// fn_3_5F3FC, size:0x324
void fn_3_5F3FC(void) {
    GameControlsStruct* game = &g_GameLogic;
    switch (game->_125) {
    case 0:
        lbl_3_common_bss_32724._9A = 0;
        game->scoutFlag_VsScreenInd = 0;
        game->playBatterWalkupAnimation = 1;
        fn_3_F578();
        fn_3_753E8(0);
        setBatterContactConstants();
        ((void (*)(void))fn_3_8A1D8)(); // called without its argument in the original
        fn_3_8913C();
        fn_3_58E50();
        fn_3_1E154();
        fn_3_7AFE4();
        fn_3_59A90();
        fn_3_6C108();
        g_Strikes.strikes = 0;
        g_Strikes.balls = 0;
        g_Strikes._1E = -1;
        g_Strikes.stateRelated = 0;
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.frameCountdownAtBeginningOfAtBatLockout = 90;
        g_GameLogic._133[0] = 0;
        g_GameLogic._133[1] = 0;
        if (g_Scores._C6 < 0xFE) {
            g_Scores._C6++;
        } else {
            g_Scores._C6 = 0xFF;
        }
        game->_125++;
    case 1:
        if (fn_3_6BA64() == 0) {
            break;
        }
        lbl_803CBC3C[2] = 0;
        game->_125++;
    case 2:
        if (someAnimationIndFunction() == 0) {
            break;
        }
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        game->_125++;
    case 3:
        if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.practiceLevel == 7) {
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
                fn_3_90AB0(g_Practice.someCharID2);
                g_Practice.someCharID2 =
                    inMemRoster[g_GameLogic.teamBatting]
                               [g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] - 1]
                                   .stats.CharID;
                lbl_3_common_bss_34C58._2C = 0;
            }
            if (fn_3_90C14(g_Practice.someCharID2) == 0) {
                break;
            }
        }
        game->_125++;
    default:
        if (g_d_GameSettings.GameModeSelected == 4 && unkSimulationRelatedStruct._08 != 0) {
            break;
        }
        if (g_GameLogic.freeFieldingPracticeInd != 0) {
            fn_3_5F154();
            break;
        }
        fn_3_5A6D4(0x16);
        fn_3_1DC30();
        g_GameLogic.IsStarChance = 0;
        lbl_3_common_bss_32724._AC = 0;
        if (lbl_800E8754._04 != 0 && (g_d_GameSettings.exhibitionMatchInd != 0 || lbl_3_common_bss_37400.type == 0) &&
            (g_GameLogic.TeamStars[0] < 5 || g_GameLogic.TeamStars[1] < 5) && !(g_RunningLogic.occupiedBases & 0xFFF0) &&
            random_fn_3_9EE24(100) < lbl_3_data_60F0) {
            g_GameLogic.IsStarChance = 1;
            lbl_3_common_bss_32724._AC = 1;
        }
        break;
    }
}

// fn_3_5D094, size:0x368
// NONMATCHING 96%: original jumps straight to the shared tail after each END_GAME (we re-test the flag); regalloc
#if NONMATCHING
#define END_GAME(team, type)                   \
    do {                                       \
        g_Scores.winningTeam = (team);         \
        g_GameLogic.EventTriggers_EndOfGame = 1; \
        g_GameLogic.winType = (type);          \
    } while (0)

void fn_3_5D094(s32 checkType) {
    s32 diff;
    if (g_GameLogic.EventTriggers_EndOfGame != 0) {
        return;
    }
    if (checkType == 0) {
        if (g_Scores.inning >= g_Scores.finalInning) {
            if (g_Scores.bottomHalf == 0) {
                if (g_Scores.runs[0][0] < g_Scores.runs[1][0]) {
                    END_GAME(1, 2);
                }
            } else if (g_Scores.runs[0][0] < g_Scores.runs[1][0]) {
                END_GAME(1, 2);
            } else if (g_Scores.runs[0][0] > g_Scores.runs[1][0]) {
                END_GAME(0, 1);
            } else if (g_Scores.inning >= g_Scores._AB) {
                END_GAME(2, 4);
            }
        } else if (g_Scores._C7 != 0 && g_Scores.bottomHalf != 0) {
            diff = g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0] -
                   g_Scores.runs[g_GameLogic.awayTeamBattingInd_battingTeam][0];
            if (diff >= g_Scores._C7) {
                END_GAME(1, 6);
                fn_3_59918(0x11, 0);
            } else if (diff <= -g_Scores._C7) {
                END_GAME(0, 5);
                fn_3_59918(0x11, 0);
            }
        }
    } else if (checkType == 1) {
        if (g_Scores.inning >= g_Scores.finalInning && g_Scores.bottomHalf == 1) {
            if (g_Scores.runs[0][0] < g_Scores.runs[1][0]) {
                END_GAME(1, 3);
            }
        } else if (g_Scores.bottomHalf != 0 && g_Scores._C7 != 0) {
            if (g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0] -
                    g_Scores.runs[g_GameLogic.awayTeamBattingInd_battingTeam][0] >=
                g_Scores._C7) {
                END_GAME(1, 6);
                fn_3_59918(0x11, 0);
            }
        }
    }
    if (g_GameLogic.EventTriggers_EndOfGame == 0) {
        return;
    }
    { // inlined fn_3_5CFD0
        ChallengeState* t = &gChallengeState;
        s32 a = t->_441C;
        s32 b = t->_441E;
        if (g_d_GameSettings.exhibitionMatchInd == 0 && g_Scores.winningTeam <= 1 &&
            (g_Scores.winningTeam ^ (g_GameLogic._000 == lbl_3_common_bss_37400.humanPlayer)) != 0) {
            if ((t->_4422 >= 4 && b == 5) || (t->_4422 >= 5 && t->_44EF == 1 && a == 5)) {
                g_GameLogic.playOverFadeOutStarted = 0;
            }
            starMissionRelated2();
        }
    }
    if ((g_GameLogic.winType == 5 || g_GameLogic.winType == 6) && g_d_GameSettings.exhibitionMatchInd == 0 &&
        g_d_GameSettings.humanTeamNumber == (g_Scores.winningTeam ^ g_GameLogic._000)) {
        fn_3_1637EC();
        g_d_GameSettings.someChallengeModeFlag = 1;
    }
}
#endif

// fn_3_5DF54, size:0x370
void fn_3_5DF54(void) {
    s32 handled = 0;
    if (g_Stats.replayInd != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 4 && unkSimulationRelatedStruct._08 != 0) {
        return;
    }
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;
    g_GameLogic.playBatterWalkupAnimation = 0;
    fn_3_7A154(1);
    fn_3_1DD48();
    if (g_FieldingLogic._107 != 0 && g_Strikes.outs < 3 && g_GameLogic.EventTriggers_EndOfGame == 0) {
        // inlined fn_3_5DCE0
        s32 r = 0;
        u8 sw = g_Pitcher.strikeOutOrWalk;
        if (sw == 1) {
            fn_3_736CC();
            r = 1;
        } else if (sw == 2) {
            fn_3_735A8();
            r = 1;
        }
        handled = r;
    }
    fn_3_77914();
    if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400._47 != 0) {
        lbl_3_common_bss_37400.type = 0;
        lbl_3_common_bss_37400._47 = 0;
    }
    if (g_GameLogic.EventTriggers_EndOfGame != 0) {
        fn_3_5A6D4(8);
        handled = 1;
    } else if (g_Strikes.outs >= 3) {
        fn_3_5A6D4(8);
        if (g_FieldingLogic._107 >= 1 && g_FieldingLogic._107 <= 3 && g_Strikes.balls < 4 && g_Strikes.strikes < 3) {
            if (g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] == 1) {
                lbl_3_common_bss_32A94._44[g_GameLogic.homeTeamBattingInd_fieldingTeam]--;
            }
        } else {
            fn_3_9E7D4(g_GameLogic.homeTeamBattingInd_fieldingTeam);
        }
        if (g_d_GameSettings.GameModeSelected == 2 && (g_Practice.practiceLevel == 7 || g_Practice.practiceLevel == 6)) {
            fn_3_899BC();
        }
        handled = 1;
    } else if (g_Ball.AtBat_ContactResult == -1 && g_Ball.maybebuntOn2Strikes == 0) {
        fn_3_8A4E4();
        fn_3_5A6D4(0);
        handled = 1;
    } else if (g_FieldingLogic._107 != 0 && g_FieldingLogic._107 != 4) {
        fn_3_899BC();
        if (handled != 0) {
            fn_3_9E7D4(g_GameLogic.homeTeamBattingInd_fieldingTeam);
            fn_3_5A6D4(8);
            handled = 1;
        } else {
            fn_3_5A6D4(0xA);
            handled = 1;
        }
    } else {
        fn_3_899BC();
        fn_3_9E7D4(g_GameLogic.homeTeamBattingInd_fieldingTeam);
        fn_3_5A6D4(8);
        handled = 1;
    }
    fn_3_BF1AC();
    Set_803cb848(0);
    fn_3_BF158();
    if (g_GameLogic.secondaryGameMode == 0 && g_Stats._39 == 1 && handled != 0) {
        if (g_Ball.deadBallReason == 1 && g_Stats.replayInd == 0) {
            fn_3_5A6D4(0x14);
        } else {
            g_Stats._39 = 2;
            fn_3_8C07C();
        }
        Set_803cb848(1);
    }
}

// fn_3_5D5E8, size:0x410
void fn_3_5D5E8(void) {
    GameControlsStruct* game = &g_GameLogic;
    s32 charId; // left unset when no batter has position 1, as in the original
    s32 i;
    if (game->_125 == 0) {
        changeScene(1, 6);
        { // inlined fn_3_5D51C
            ScoresStruct* scores = &g_Scores;
            if (scores->bottomHalf == 0) {
                scores->bottomHalf = 1;
            } else {
                scores->bottomHalf = 0;
                scores->inning += 1;
            }
            g_GameLogic.homeTeamBattingInd_fieldingTeam ^= 1;
            g_GameLogic.awayTeamBattingInd_battingTeam ^= 1;
            g_GameLogic.teamBatting ^= 1;
            g_GameLogic.teamFielding ^= 1;
            g_GameLogic._131[0] = 0;
            g_GameLogic._131[1] = 0;
            g_Scores._A0 = g_Scores.runs[scores->bottomHalf][0];
            fn_3_5A684();
            fn_3_8A350();
            fn_3_F7B8();
            fn_3_75434();
            fn_3_59338();
            fn_3_7B130();
            fn_3_22850();
        }
        { // inlined fn_3_5D3FC
            s32 stage;
            GameInitVariables* gs = &g_d_GameSettings;
            s32 inning;
            u8 finalInning;
            g_GameLogic._135 = 0;
            g_GameLogic._136 = 0;
            g_RunningLogic._11 = 0;
            g_RunningLogic._13 = 0;
            g_RunningLogic.occupiedBases = 0;
            inning = g_Scores.inning;
            finalInning = g_Scores.finalInning;
            if (inning > finalInning) {
                stage = 5;
            } else if (finalInning <= 3U) {
                if (finalInning == inning && g_Scores.bottomHalf != 0) {
                    stage = 4;
                } else {
                    stage = 0;
                }
            } else if (inning == finalInning) {
                stage = 4;
            } else if ((finalInning == 9 && inning >= 7) || (finalInning == 7 && inning >= 6)) {
                stage = 3;
            } else if (inning >= 4) {
                stage = 2;
            } else {
                stage = 1;
            }
            g_Scores.inningStage = stage;
            g_Scores._C1 = 0;
            g_Scores._C6 = 0;
            lbl_3_common_bss_37400.state = 0;
            fn_3_6C13C();
            if (gs->exhibitionMatchInd == 0) {
                fn_3_16598C();
            }
        }
        lbl_3_common_bss_32724._9B = 0;
        lbl_3_common_bss_32724._9C[0] = 0;
        lbl_803CBC3C[3] = 0;
        lbl_8036E548._3087 = 0;
        game->_125 = 1;
    } else if (game->_125 == 1) {
        if (fn_3_6BD6C() != 0) {
            lbl_8036E548._3081 = 0;
            game->_125 = 2;
        }
    } else if (game->_125 == 2) {
        for (i = 1; i < 10; i++) {
            if (g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][1] == 1) {
                charId = inMemRoster[g_GameLogic.teamFielding][g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][0]]
                             .stats.CharID;
            }
        }
        if (fn_8001C588(charId) != 0) {
            lbl_8036E548._3081 = 0;
            game->_125 = 3;
        }
    } else if (game->_125 == 3) {
        if (fn_3_750DC() != 0) {
            game->_125 = 6;
        }
    } else if (game->_125 == 6) {
        if (game->FrameCountOfCurrentPitch >= 120 && fn_3_6C938(1, 0x1300) != 0) {
            game->_125 = 7;
        }
        if (fn_3_FD9FC() != 0) {
            game->_125 = 7;
        }
    } else if (game->_125 == 7) {
        changeScene(3, 6);
        game->_125 = 8;
    } else if (game->_125 == 8) {
        if (lbl_8037169C._13 != 0) {
            game->_125 = 9;
        }
    } else if (game->_125 == 9) {
        fn_3_BF1AC();
        fn_3_BF158();
        lbl_8036E548._3087 = 1;
        fn_3_FBD70();
        fn_3_FBD58();
        fn_3_5A6D4(7);
    }
}

// fn_3_5A87C, size:0x424
// NONMATCHING 97%: register allocation (one extra saved reg; AIDifficulty base hoisted)
#if NONMATCHING
void fn_3_5A87C(void) {
    s32 i;
    u8 home;
    s32 away;
    lbl_80366158._28 = 0;
    lbl_3_data_228.counter = 0;
    lbl_3_data_228.totalFrames = 0;
    unkSimulationRelatedStruct._00 = g_d_GameSettings.FrameCountWhileNotAtMainMenu;
    unkSimulationRelatedStruct._05 = 0;
    unkSimulationRelatedStruct._06 = 4;
    g_d_GameSettings.humanTeamNumber = 0;
    g_GameLogic._125 = 0;
    g_GameLogic.EventTriggers_EndOfGame = 0;
    g_GameLogic._128 = 0;
    g_GameLogic.sceneID = 0;
    g_GameLogic.EventTriggers_GameHasStarted = 0;
    g_GameLogic._124 = 0;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.winType = 0;
    g_GameLogic._131[0] = 0;
    g_GameLogic._131[1] = 0;
    g_GameLogic._133[0] = 0;
    g_GameLogic._133[1] = 0;
    g_GameLogic._106 = -1;
    g_GameLogic.bOD_framesInLiveBallScene = -1;
    g_GameLogic.playOverFadeOutStarted = -1;
    g_GameLogic.PauseSimulationFrameCount = 0;
    g_Practice.practiceLevel = 0;
    lbl_3_common_bss_1323C = &lbl_3_common_bss_134C4;
    g_GameLogic.secondaryGameMode = 0;
    if (g_d_GameSettings.GameModeSelected == 2) {
        g_GameLogic.secondaryGameMode = 0x12;
    }
    fn_3_1CCC8();
    g_Scores.finalInning = lbl_800E8754.innings;
    g_Scores._AB = lbl_800E8754.innings + 3;
    if (g_d_GameSettings.GameModeSelected == 4) {
        g_Scores._AB = 5;
        g_Scores.finalInning = 5;
    }
    home = g_d_GameSettings.home_AwaySetting;
    away = home ^ 1;
    for (i = 0; i < 2; i++) {
        g_GameLogic._13E[i] = 0;
        g_GameLogic._140[i] = 0;
        g_GameLogic.batterHandedness[i] = 0;
        g_GameLogic.teamAIInd[i] = 0;
        g_GameLogic.autoFielding[i] = 0;
        g_GameLogic.battingAIInd[i] = 0;
    }
    g_GameLogic.AIDifficulty0Special3Weak[0] = lbl_800E8754._01[2];
    g_GameLogic.AIDifficulty0Special3Weak[1] = lbl_800E8754._01[2];
    g_GameLogic.homeTeamBattingInd_fieldingTeam = 0;
    g_GameLogic.awayTeamBattingInd_battingTeam = 1;
    g_GameLogic._000 = home;
    g_GameLogic.teamBatting = home;
    g_GameLogic.teamFielding = away;
    g_GameLogic._01C[0] = (&g_d_GameSettings.maybeHomeAway)[home];
    g_GameLogic._01C[1] = (&g_d_GameSettings.maybeHomeAway)[away];
    if (g_d_GameSettings.GameModeSelected == 2) {
        g_GameLogic.AIDifficulty0Special3Weak[home] = 1;
        g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic._000 ^ 1] = 1;
    } else if (g_d_GameSettings._10 == 0) {
        g_GameLogic._13E[1] = 1;
        g_GameLogic._140[away] = 1;
        lbl_3_common_bss_37400.humanPlayer = 0;
        g_GameLogic.batterHandedness[g_GameLogic._000 ^ 1] = 1;
        g_GameLogic.teamAIInd[g_GameLogic._000 ^ 1] = 1;
        g_GameLogic.autoFielding[g_GameLogic._000 ^ 1] = 1;
        g_GameLogic.battingAIInd[g_GameLogic._000 ^ 1] = 1;
        g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic._000] = 1;
    } else if (g_d_GameSettings._10 == 3) {
        g_GameLogic._13E[0] = 1;
        g_GameLogic._140[home] = 1;
        lbl_3_common_bss_37400.humanPlayer = 1;
        g_GameLogic.batterHandedness[g_GameLogic._000] = 1;
        g_GameLogic.teamAIInd[g_GameLogic._000] = 1;
        g_GameLogic.autoFielding[g_GameLogic._000] = 1;
        g_GameLogic.battingAIInd[g_GameLogic._000] = 1;
        g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic._000 ^ 1] = 1;
    } else if (g_d_GameSettings._10 == 2) {
        for (i = 1; i >= 0; i--) {
            g_GameLogic._13E[i] = 1;
        }
        g_GameLogic._140[1] = 1;
        g_GameLogic._140[0] = 1;
        g_GameLogic.batterHandedness[1] = 1;
        g_GameLogic.batterHandedness[0] = 1;
        g_GameLogic.teamAIInd[1] = 1;
        g_GameLogic.teamAIInd[0] = 1;
        g_GameLogic.autoFielding[1] = 1;
        g_GameLogic.autoFielding[0] = 1;
        g_GameLogic.battingAIInd[1] = 1;
        g_GameLogic.battingAIInd[0] = 1;
    } else {
        g_GameLogic.AIDifficulty0Special3Weak[0] = 1;
        g_GameLogic.AIDifficulty0Special3Weak[1] = 1;
    }
    for (i = 0; i < 2; i++) {
        if (g_GameLogic._13E[i] == 0) {
            if (lbl_800E8754.port[g_GameLogic.teams[i]]._0 != 0) {
                g_GameLogic.batterHandedness[g_GameLogic._000 ^ i] = 1;
            }
            if (lbl_800E8754.port[g_GameLogic.teams[i]]._1 != 0) {
                g_GameLogic._140[g_GameLogic._000 ^ i] = 1;
            }
            if (lbl_800E8754.port[g_GameLogic.teams[i]]._2 != 0) {
                g_GameLogic.battingAIInd[g_GameLogic._000 ^ i] = 1;
            }
            if (lbl_800E8754.port[g_GameLogic.teams[i]]._3 != 0) {
                g_GameLogic.teamAIInd[g_GameLogic._000 ^ i] = 1;
                g_GameLogic.autoFielding[g_GameLogic._000 ^ i] = 1;
            }
        }
    }
    fn_3_1658F0();
    fn_3_5FF10();
}
#endif

// fn_3_5B5A0, size:0x48C
// NONMATCHING 95%: regalloc/scheduling in the Bowser Jr. runner setup (original rematerializes g_Runners per branch)
#if NONMATCHING
void fn_3_5B5A0(void) {
    s32 i;
    s32 j;
    g_d_GameSettings.challengeMinigame_baseCoinsEarned = 0;
    g_d_GameSettings.bJMatchRelated = 0;
    if (g_d_GameSettings.GameModeSelected == 5) {
        if (g_GameLogic._13E[g_GameLogic._000] != 0) {
            g_GameLogic.AIDifficulty0Special3Weak[0] = lbl_3_data_6074[g_d_GameSettings.challengeDifficulty];
        } else {
            g_GameLogic.AIDifficulty0Special3Weak[1] = lbl_3_data_6074[g_d_GameSettings.challengeDifficulty];
        }
        if (g_d_GameSettings.bJMatchInd == 1) {
            s32 pick;
            s32 slot;
            s32 bases;
            g_Scores.inning = 9;
            g_Scores.finalInning = 9;
            g_Scores._AB = 9;
            g_Scores.bottomHalf = 1;
            g_GameLogic.homeTeamBattingInd_fieldingTeam ^= 1;
            g_GameLogic.awayTeamBattingInd_battingTeam ^= 1;
            g_GameLogic.teamBatting ^= 1;
            g_GameLogic.teamFielding ^= 1;
            pick = rand() % 2;
            g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] = lbl_3_data_5FF4[g_d_GameSettings.home_AwaySetting][g_d_GameSettings.challengeDifficulty][pick].batter;
            g_Strikes.storedOuts = lbl_3_data_5FF4[g_d_GameSettings.home_AwaySetting][g_d_GameSettings.challengeDifficulty][pick].outs;
            g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0] = lbl_3_data_5FF4[g_d_GameSettings.home_AwaySetting][g_d_GameSettings.challengeDifficulty][pick].runs;
            g_Strikes.outs = lbl_3_data_5FF4[g_d_GameSettings.home_AwaySetting][g_d_GameSettings.challengeDifficulty][pick].outs;
            if (g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0] < 0) {
                g_Scores.runs[g_GameLogic.awayTeamBattingInd_battingTeam][0] =
                    -g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0];
                g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0] = 0;
            }
            g_Runners[1].rosterID = -1;
            bases = lbl_3_data_5FF4[g_d_GameSettings.home_AwaySetting][g_d_GameSettings.challengeDifficulty][pick].bases;
            slot = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam];
            g_Runners[2].rosterID = -1;
            g_Runners[3].rosterID = -1;
            if (bases & 0x1) {
                if (--slot < 1) {
                    slot = 9;
                }
                g_Runners[1].rosterID = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][slot][0];
            }
            if (bases & 0x10) {
                if (--slot < 1) {
                    slot = 9;
                }
                g_Runners[2].rosterID = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][slot][0];
            }
            if (bases & 0x100) {
                if (--slot < 1) {
                    slot = 9;
                }
                g_Runners[3].rosterID = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][slot][0];
            }
            setBatterContactConstants();
            ((void (*)(void))fn_3_8A1D8)(); // called without its argument in the original
            g_d_GameSettings.home_AwaySetting ^= 1;
        } else {
            if (lbl_8034E9A0._46E4 == 9 || gChallengeState._16C2 == 0x2A) {
                g_Scores.finalInning = lbl_8010B600[g_d_GameSettings.challengeDifficulty][1];
            } else {
                g_Scores.finalInning = lbl_8010B600[g_d_GameSettings.challengeDifficulty][0];
            }
            g_Scores._AB = g_Scores.finalInning + 3;
        }
        g_Scores._C7 = lbl_8010B600[g_d_GameSettings.challengeDifficulty][2];
    }
    for (i = 0; i < 54; i++) {
        for (j = 0; j < 10; j++) {
            if ((s8)starMissionCompletionTracker[i].inGameMissionTracker[j].starMissionStatus != -2) {
                starMissionCompletionTracker[i].inGameMissionTracker[j].starMissionStatus = 0;
            }
        }
    }
}
#endif

#if !NONMATCHING
// Switch jump tables of fn_3_5F930; mwcc emits them itself once the function matches.
void* jumptable_3_data_655C[11] = {
    (u8*)fn_3_5F930 + 0x134, (u8*)fn_3_5F930 + 0x2F8, (u8*)fn_3_5F930 + 0x340, (u8*)fn_3_5F930 + 0x538,
    (u8*)fn_3_5F930 + 0x538, (u8*)fn_3_5F930 + 0x368, (u8*)fn_3_5F930 + 0x434, (u8*)fn_3_5F930 + 0x45C,
    (u8*)fn_3_5F930 + 0x484, (u8*)fn_3_5F930 + 0x4EC, (u8*)fn_3_5F930 + 0x518,
};
#endif

// fn_3_5F930, size:0x558
// NONMATCHING 99%: original ends with a dead `li r0,0; cmpwi r0,9` (likely a leftover loop/compare) we can't reproduce
#if NONMATCHING
void fn_3_5F930(void) {
    GameControlsStruct* game;
    u8 mode = g_d_GameSettings.GameModeSelected;
    s32 charId; // left unset when no batter has position 1, as in the original
    s32 i;
    if (mode == 4) {
        if (unkSimulationRelatedStruct._08 == 0) {
            if (lbl_803C77B8._02 & 0x1000) {
                unkSimulationRelatedStruct._08 = 1;
            }
        } else if ((s32)lbl_803C6CF8.idle == 1) {
            u8 state = g_GameLogic._125;
            if (state == 1) {
                lbl_8036E548._3082 = 1;
            }
            if (state == 1 || state >= 8 || g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
                changeScene(3, 6);
                if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
                    g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                }
                if (lbl_8037169C._13 != 0) {
                    g_GameLogic.framesOfExitingToMenu = 1;
                }
                return;
            }
        }
    }
    game = &g_GameLogic;
    switch (game->_125) {
    case 0:
        if (mode == 5) {
            fn_3_5B5A0();
        }
        { // inlined fn_3_5F7A8
            s32 stage;
            GameInitVariables* gs = &g_d_GameSettings;
            s32 inning;
            u8 finalInning;
            g_GameLogic._135 = 0;
            g_GameLogic._136 = 0;
            g_RunningLogic._11 = 0;
            g_RunningLogic._13 = 0;
            g_RunningLogic.occupiedBases = 0;
            inning = g_Scores.inning;
            finalInning = g_Scores.finalInning;
            if (inning > finalInning) {
                stage = 5;
            } else if (finalInning <= 3U) {
                if (finalInning == inning && g_Scores.bottomHalf != 0) {
                    stage = 4;
                } else {
                    stage = 0;
                }
            } else if (inning == finalInning) {
                stage = 4;
            } else if ((finalInning == 9 && inning >= 7) || (finalInning == 7 && inning >= 6)) {
                stage = 3;
            } else if (inning >= 4) {
                stage = 2;
            } else {
                stage = 1;
            }
            g_Scores.inningStage = stage;
            g_Scores._C1 = 0;
            g_Scores._C6 = 0;
            lbl_3_common_bss_37400.state = 0;
            fn_3_6C13C();
            if (gs->exhibitionMatchInd == 0) {
                fn_3_16598C();
            }
            fn_3_5A684();
            fn_3_75434();
            fn_3_59338();
            fn_3_8A350();
            fn_3_1E178();
            fn_3_AFDA4();
            ((void (*)(void))fn_3_6C13C)();
            fn_3_7B130();
            setBatterContactConstants();
            ((void (*)(void))fn_3_8A1D8)();
            fn_3_7AFE4();
            fn_3_1E154();
            fn_3_6C108();
            g_Strikes.strikes = 0;
            g_Strikes.balls = 0;
            g_Strikes._1E = -1;
            g_Strikes.stateRelated = 0;
            g_GameLogic.frameCountdownAtBeginningOfAtBatLockout = 0x5A;
            g_GameLogic._13D = 0;
        }
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        game->_125 = 1;
        changeScene(0xD, 6);
        lbl_3_common_bss_32724._9A = 0;
        lbl_3_common_bss_32724._9C[0] = 0;
        lbl_803CBC3C[2] = 0;
        lbl_803CBC3C[3] = 0;
        lbl_8036E548.state = 0;
        lbl_8036E548._2D7B = 0;
        lbl_8036E548._2D7C = 0;
        break;
    case 1:
        if (fn_3_59BCC(game->FrameCountOfCurrentAtBat_Copy) != 0) {
            game->_125 = 2;
            game->FrameCountOfCurrentAtBat_Copy = 0;
            lbl_8036E548.state = 0;
            if (lbl_3_common_bss_32724._A4[0] != 0) {
                fn_8002024C();
            }
        }
        break;
    case 2:
        if (fn_3_750DC() != 0) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            game->_125 = 5;
        }
        break;
    case 5:
        for (i = 1; i < 10; i++) {
            if (g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][1] == 1) {
                charId = inMemRoster[g_GameLogic.teamFielding][g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][0]]
                             .stats.CharID;
            }
        }
        if (fn_8001C588(charId) != 0) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            lbl_8036E548._3081 = 0;
            game->_125 = 6;
        }
        break;
    case 6:
        if (fn_3_6BA64() != 0) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            game->_125 = 7;
        }
        break;
    case 7:
        if (someAnimationIndFunction() != 0) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            game->_125 = 8;
        }
        break;
    case 8:
        if (game->FrameCountOfCurrentPitch >= 240) {
            if (mode == 4 || g_d_GameSettings._10 == 2) {
                game->_125 = 9;
            } else if (fn_3_6C938(1, 0x1300) != 0) {
                game->_125 = 9;
            }
        }
        if (fn_3_FD9FC() != 0) {
            game->_125 = 9;
        }
        break;
    case 9:
        changeScene(3, 6);
        if (lbl_8037169C._13 != 0) {
            game->_125 = 10;
        }
        break;
    case 10:
        lbl_3_common_bss_1323C->_25C = 1;
        fn_3_FBD70();
        fn_3_5A6D4(0x16);
        break;
    }
}
#endif

// fn_3_5C74C, size:0x5D8
// NONMATCHING 97%: regalloc; the 64-bit run total compare uses unsigned-style subfe; outs reloaded for the forced-runner sum
#if NONMATCHING
void fn_3_5C74C(s32 force) {
    s32 forcedRunners = 0;
    s32 i;
    s64 total = 0;
    s32 margin;
    if (!((g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3) && g_Scores._9C > 0)) {
        if (g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 2) {
            return;
        }
        if (g_Scores._9C <= 0) {
            return;
        }
        if (g_Strikes.outs >= 3 && force != 1) {
            return;
        }
        if (g_Stats.replayInd != 0 && g_Ball.deadBallReason == 1) {
            return;
        }
        if (g_Scores.inning >= g_Scores.finalInning && g_Scores.bottomHalf != 0 && g_Ball.deadBallReason == 0) {
            // walk-off: only count the runs needed to win
            s32 fieldingRuns = g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0];
            s32 needed = g_Scores.runs[g_GameLogic.awayTeamBattingInd_battingTeam][0] + 1;
            if (fieldingRuns + g_Scores._9C > needed) {
                g_Scores._9C = needed - fieldingRuns;
            }
            if (g_Scores._9C < 0) {
                g_Scores._9C = 0;
            }
        }
        if (g_FieldingLogic._107 == 0) {
            if (g_Ball.ballInitialHitDoneInd == 0 || g_Ball.AtBat_ContactResult == 0 || g_Ball.AtBat_ContactResult == -1) {
                return;
            }
        }
        for (i = 0; i < 4; i++) {
            if (g_Runners[i].runnerOnFieldOrOutOrScored == 1 && g_Runners[i].forceOutCd == 1) {
                forcedRunners++;
            }
        }
        if (g_Ball.deadBallReason == 0) {
            if (g_Strikes.outs >= 3) {
                if (g_Strikes.forcedOutToEndInningInd == 1) {
                    return;
                }
                if (g_Strikes.storedOuts == 2 && g_Ball.AtBat_ContactResult == 3) {
                    return;
                }
            } else if (g_Strikes.outs + forcedRunners >= 3) {
                return;
            }
        }
    }
    if (g_Ball.deadBallReason != 3) {
        for (i = 0; i < 4; i++) {
            if (g_Runners[i].isEligibleToScore != 0 && g_Runners[i].runnerOnFieldOrOutOrScored == 3) {
                if (g_Stats.replayInd == 0) {
                    lbl_3_common_bss_32A94._26++;
                }
                g_Runners[i].isEligibleToScore = 0;
            }
        }
    }
    if (g_Ball.deadBallReason == 1) {
        g_Scores.runs[g_Scores.bottomHalf][g_Scores.inning] = g_Scores._9E + g_RunningLogic._12;
        g_Scores._C2 = g_RunningLogic._12;
    } else {
        g_Scores.runs[g_Scores.bottomHalf][g_Scores.inning] += g_Scores._9C;
        g_Scores._C2 += g_Scores._9C;
    }
    if (g_Scores.runs[g_Scores.bottomHalf][g_Scores.inning] > 99) {
        g_Scores.runs[g_Scores.bottomHalf][g_Scores.inning] = 99;
    }
    for (i = 1; i < 19; i++) {
        total += g_Scores.runs[g_Scores.bottomHalf][i];
    }
    if (total > 99) {
        total = 99;
    }
    g_Scores.runs[g_Scores.bottomHalf][0] = total;
    margin = g_Scores.runs[0][0] - g_Scores.runs[1][0];
    if (margin < -0x8000) {
        margin = -0x8000;
    }
    if (margin > 0x7FFF) {
        margin = 0x7FFF;
    }
    g_Scores._A6 = __abs(margin);
    fn_3_79EF4();
    g_Scores._9C = 0;
    if (g_Pitcher.strikeOutOrWalk != 2 && g_Pitcher.strikeOutOrWalk != 3 && g_Ball.deadBallReason != 1) {
        lbl_3_common_bss_32724._99 = 1;
    }
    if (g_Stats.replayInd == 0 && g_Pitcher.strikeOutOrWalk != 2 && g_Pitcher.strikeOutOrWalk != 3) {
        playSoundEffect(0x198);
    }
    fn_3_5D094(1);
}
#endif

// fn_3_6011C, size:0x64C
// Per-frame game logic for normal matches. The original inlines the per-state
// handlers fn_3_5C418, fn_3_5EDD8, fn_3_5FE88, fn_3_5DA9C and fn_3_5CD24.
void fn_3_6011C(void) {
    g_GameLogic.hudElementLoadingInd = 0;
    g_GameLogic.hudLoadingRelated = 0;
    if (g_Ball.totalFramesAtPlay < 0x7FFE) {
        g_Ball.totalFramesAtPlay += 1;
    } else {
        g_Ball.totalFramesAtPlay = 0x7FFF;
    }
    if (g_Strikes.outs >= 3) {
        g_FieldingLogic._0E4++;
    }
    if (g_d_GameSettings.GameModeSelected == 4 && g_GameLogic.gameStatus != 5) {
        { // inlined fn_3_5C418
        s32 inScene = 0;
        u8 status = g_GameLogic.gameStatus;
        if ((u8)(status - 1) <= 1 || (u8)(status - 0x13) <= 3 || status == 7) {
            inScene = 1;
        }
        if (unkSimulationRelatedStruct._08 == 0) {
            if (lbl_803C77B8._02 & 0x1000) {
                unkSimulationRelatedStruct._08 = 1;
            }
        } else {
            if (inScene != 0) {
                changeScene(3, 6);
            }
            if (lbl_8037169C._13 != 0 && inScene != 0) {
                if ((s32)lbl_803C6CF8.idle == 1) {
                    lbl_3_common_bss_32724.hudOff = 1;
                    g_GameLogic.framesOfExitingToMenu = 1;
                } else if (unkSimulationRelatedStruct._09 == 0) {
                    fn_800A7568();
                    unkSimulationRelatedStruct._09 = 1;
                }
            }
        }
        }
    }
    switch (g_GameLogic.gameStatus) {
    case 0:
        fn_3_5F154();
        break;
    case 1:
        fn_3_5EFEC();
        break;
    case 2:
        { // inlined fn_3_5EDD8
        ballPhysica();
        fn_3_598D0();
        fn_3_8A958();
        if (g_Ball.deadBallReason != 0) {
            fn_3_5DD30();
        }
        fn_3_5C74C(0);
        fn_3_5E2C4();
        if (g_GameLogic.freeFieldingPracticeInd == 0) {
            fn_3_79ACC();
            if (g_Strikes.outs >= 3) {
                fn_3_5D094(0);
            }
        }
        }
        break;
    case 4:
        { // inlined fn_3_5FE88
        GameControlsStruct* game = &g_GameLogic;
        switch ((s32)game->_125) {
        case 0:
            fn_800B0A5C_insertQueue(possiblyTransitionBlackScreen, 2);
            game->_125 = 1;
            break;
        case 1:
            fn_800B0A5C_insertQueue(fn_3_5BAC, 4);
            game->_125 = 2;
            break;
        default:
            fn_3_5A6D4(5);
            break;
        }
        }
        break;
    case 5:
        fn_3_5F930();
        break;
    case 7:
        fn_3_5F3FC();
        break;
    case 8:
        { // inlined fn_3_5DA9C
        fn_3_6B870();
        if (g_GameLogic.EventTriggers_EndOfGame != 0) {
            if (g_d_GameSettings.exhibitionMatchInd == 0 &&
                (g_GameLogic._000 ^ (g_Scores.winningTeam == g_d_GameSettings.humanTeamNumber)) != 0 &&
                (g_d_GameSettings.bJMatchInd != 1 ||
                 (g_GameLogic._000 ^ (g_Scores.winningTeam != g_d_GameSettings.humanTeamNumber)) == 0)) {
                fn_8006C9D8();
            }
            fn_3_76558();
#ifdef TARGET_PC
        { extern void port_career_game_final(void); port_career_game_final(); }
#endif
        }
        g_GameLogic._135 = 0;
        g_GameLogic._136 = 0;
        g_GameLogic.playOverInd = 0;
        g_Scores._C1 = g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0] - g_Scores._A0;
        g_Pitcher._15D = 0;
        if (g_d_GameSettings.GameModeSelected == 4 &&
            (lbl_3_data_228.counter >= 0x2A30U || unkSimulationRelatedStruct._08 != 0)) {
            g_GameLogic.framesOfExitingToMenu = 1;
        } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
            if (g_Stats.replayInd == 0) { // inlined fn_3_5D9F8
                g_Pitcher._15C = 0;
                if (g_d_GameSettings.GameModeSelected == 4 && g_Scores.bottomHalf == 0) {
                    g_GameLogic.framesOfExitingToMenu = 1;
                } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
                    fn_3_5A6D4(9);
                } else {
                    fn_3_5A6D4(3);
                }
            }
        } else if (g_Strikes.outs >= 3) {
            if (g_Stats.replayInd == 0) { // inlined fn_3_5D9F8
                g_Pitcher._15C = 0;
                if (g_d_GameSettings.GameModeSelected == 4 && g_Scores.bottomHalf == 0) {
                    g_GameLogic.framesOfExitingToMenu = 1;
                } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
                    fn_3_5A6D4(9);
                } else {
                    fn_3_5A6D4(3);
                }
            }
        } else {
            fn_3_5A6D4(7);
        }
        }
        break;
    case 3:
        fn_3_5D5E8();
        break;
    case 9:
        fn_3_5CDB4();
        break;
    case 10:
        { // inlined fn_3_5CD24
        GameControlsStruct* game = &g_GameLogic;
        if (game->_125 == 0) {
            lbl_3_common_bss_32724._9A = 0;
            fn_3_8A1D8();
            fn_3_6C108();
            fn_3_6B870();
            game->_125++;
        } else if (game->_125 == 1) {
            if (fn_3_6BA64() != 0) {
                lbl_803CBC3C[2] = 0;
                fn_3_5A6D4(0);
            }
        }
        }
        break;
    case 11:
        fn_3_AF5A4();
        break;
    case 19:
        fn_3_23CEC();
        break;
    case 20:
        fn_3_23890();
        break;
    case 21:
        fn_3_240F8();
        break;
    case 22:
        fn_3_234BC();
        break;
    case 23:
        fn_3_22C20();
        break;
    case 24:
        fn_3_230D4();
        break;
    case 14:
        fn_3_5BD40();
        break;
    }
    fn_3_9D6A4();
    fn_3_8F21C();
    fn_3_8FC80();
    if (g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 2) {
        if (g_d_GameSettings.GameModeSelected == 4 && unkSimulationRelatedStruct._08 != 0) {
            return;
        }
        if (lbl_3_common_bss_34C90.active != 0) {
            return;
        }
        {
            s16* pending = lbl_3_common_bss_32724.pending;
            if (pending[0] >= 0) {
                if (fn_80014F40(pending[0]) != 0) {
                    pending[0] = -1;
                }
            } else if (pending[1] >= 0) {
                if (fn_80014D4C(pending[1]) != 0) {
                    pending[1] = -1;
                }
            } else if (pending[2] >= 0) {
                if (fn_80014E50(pending[2]) != 0) {
                    pending[2] = -1;
                }
            }
        }
    }
}

#if !NONMATCHING
// Switch jump tables of fn_3_5BD40; mwcc emits them itself once the function matches.
void* jumptable_3_data_6510[12] = {
    (u8*)fn_3_5BD40 + 0x90, (u8*)fn_3_5BD40 + 0x268, (u8*)fn_3_5BD40 + 0x2A8, (u8*)fn_3_5BD40 + 0x2C8,
    (u8*)fn_3_5BD40 + 0x2F0, (u8*)fn_3_5BD40 + 0x350, (u8*)fn_3_5BD40 + 0x434, (u8*)fn_3_5BD40 + 0x528,
    (u8*)fn_3_5BD40 + 0x544, (u8*)fn_3_5BD40 + 0x584, (u8*)fn_3_5BD40 + 0x65C, (u8*)fn_3_5BD40 + 0x690,
};
#endif

// fn_3_5BD40, size:0x6D8
// Post-game: results, coin rewards, MVP and scorebook screens.
// NONMATCHING 97%: regalloc (_125 and the controller index kept in other registers); fn_3_5B41C and fn_3_5B220 are inlined by hand
#if NONMATCHING
void fn_3_5BD40(void) {
    InputStruct* input = &g_Controls[lbl_80366158._27];
    if (g_GameLogic._125 >= 3) {
        s16* timer = &lbl_3_common_bss_34C90.subFrames;
        if (*timer < 0x7FFE) {
            *timer += 1;
        } else {
            *timer = 0x7FFF;
        }
    }
    switch (g_GameLogic._125) {
    case 0:
        lbl_3_common_bss_34C90.cursor = 0;
        lbl_3_common_bss_34C90._1DB[0] = 0;
        lbl_3_common_bss_34C90.openedByBattingTeam = 0;
        lbl_3_common_bss_34C90.subFrames = 0;
        g_GameLogic.scoreBook_teamDisplayed = 0;
        g_GameLogic.scoreBook_batter_pitcherStatsDisplayed = 0;
        g_GameLogic.scoreBook_scrollIndex = 0;
        g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 0;
        g_GameLogic._118 = 0;
        g_GameLogic._11A = -1;
        if (g_d_GameSettings.exhibitionMatchInd == 0) {
            // inlined fn_3_5B41C
            s32 result = 2;
            s32 margin;
            if (g_Scores.winningTeam == 2) {
                result = 1;
            } else if (g_Scores.winningTeam == g_GameLogic._000) {
                result = 0;
            }
            if (g_d_GameSettings.bJMatchInd == 0) {
                g_d_GameSettings.challengeMinigame_baseCoinsEarned += lbl_3_data_607C.resultCoins[result];
                margin = __abs(g_Scores.runs[g_GameLogic._000][0] - g_Scores.runs[g_GameLogic._000 ^ 1][0]);
                if (result == 0) {
                    g_d_GameSettings.challengeMinigame_baseCoinsEarned += margin * lbl_3_data_607C.winMarginPercent / 100;
                } else if (result == 2) {
                    g_d_GameSettings.challengeMinigame_baseCoinsEarned += margin * lbl_3_data_607C.lossMarginPercent / 100;
                }
                g_d_GameSettings.challengeMinigame_baseCoinsEarned += g_GameLogic.TeamStars[0] * lbl_3_data_607C.starPercent / 100;
            } else {
                g_d_GameSettings.challengeMinigame_baseCoinsEarned += lbl_3_data_607C.bjCoins[result];
                g_d_GameSettings.bJMatchRelated += lbl_3_data_607C.bjPoints[result];
            }
        }
        g_GameLogic._125 = 1;
        break;
    case 1:
        if (fn_80035838(&lbl_3_data_6130[1], 0xC) != 0) {
            lbl_3_common_bss_32724._9A = 0;
            lbl_3_common_bss_32724._D1 = 1;
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        if (fn_3_6B5D8() != 0) {
            fn_3_8C104(-1);
            g_GameLogic._125 = 3;
        }
        break;
    case 3:
        changeScene(1, 6);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 4;
        break;
    case 4:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 180) {
            u8 mvp = g_GameLogic._13D;
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            if (mvp != 0) {
                if (g_d_GameSettings.exhibitionMatchInd == 0) {
                    g_GameLogic._125 = 7;
                } else {
                    g_GameLogic._125 = 6;
                }
            } else {
                g_GameLogic._125 = 7;
            }
        }
        break;
    case 5:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            fn_8004CC4C(7, 0, 0, 0, 0x8B);
            if ((s8)lbl_80353A90._101[0] >= 0) {
                fn_8004CA48(inMemRoster[0][(s8)lbl_80353A90._101[0]].stats.CharID, 0, 0, 0);
            } else if ((s8)lbl_80353A90._101[1] >= 0) {
                fn_8004CA48(inMemRoster[0][(s8)lbl_80353A90._101[1]].stats.CharID, 0, 0, 0);
            }
        }
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy >= 20 && (input->newButtonInput & 0x100)) {
            fn_8004CC2C();
        }
        if (lbl_803C5F74.state == 4) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = 6;
        }
        break;
    case 6: { // inlined fn_3_5B220(0)
        s32 done;
        if (g_GameLogic.frames_memoryCardWriteOnMVP < 0x7FFE) {
            g_GameLogic.frames_memoryCardWriteOnMVP += 1;
        } else {
            g_GameLogic.frames_memoryCardWriteOnMVP = 0x7FFF;
        }
        switch ((s32)g_GameLogic.endGameStage) {
        case 0:
            fn_8003BF54(lbl_80366158._27, 0, 0, 1, 0, 4, 5, 0, 0);
            g_GameLogic.endGameStage += 1;
            done = 0;
            break;
        case 1: {
            s16 v = lbl_803CC1B8->_10;
            if (v == 1 || (u16)(v - 0xB) <= 1U || v == 7) {
                g_GameLogic.endGameStage += 1;
            }
            done = 0;
            break;
        }
        default:
            done = 1;
            break;
        }
        if (done != 0) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = 7;
        }
        break;
    }
    case 7:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 45) {
            fn_3_5BA2C();
        }
        break;
    case 8:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 45) {
            lbl_3_common_bss_34C90.subFrames = 0;
            lbl_3_common_bss_34C90.openedByBattingTeam ^= 1;
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = 7;
        }
        break;
    case 9:
        if (g_GameLogic.playOverFadeOutStarted >= 0) {
            changeScene(3, 6);
        } else if (g_d_GameSettings.exhibitionMatchInd == 0) {
            if (g_d_GameSettings.bJMatchInd == 1) {
                fn_800203E0(0xC, (s8)lbl_3_data_6104[gChallengeState._441C]);
            } else {
                fn_800203E0(0xC, (s8)lbl_3_data_6104[gChallengeState._441E]);
            }
        } else {
            changeScene(4, 6);
        }
        if (lbl_8037169C._13 != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            g_GameLogic._125 = 10;
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        }
        break;
    case 10:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 10) {
            fn_3_8C07C();
            g_GameLogic._125 = 11;
            lbl_3_common_bss_32724._CD = 1;
        }
        break;
    case 11:
        if (g_GameLogic.playOverFadeOutStarted >= 0) {
            fn_3_5A6D4(0x17);
        } else {
            g_GameLogic._128 = 1;
            g_GameLogic.framesOfExitingToMenu = 1;
        }
        break;
    }
}
#endif

// fn_3_5E2C4, size:0xAD4
// Play-end timer: counts g_FieldingLogic._0AE up after a play and ends it.
// NONMATCHING 96%: regalloc and block layout of the limit selection
#if NONMATCHING
void fn_3_5E2C4(void) {
    s32 runnersOnField = 0;
    s32 settled = 1;
    s16 limit = 120;
    s32 i;
    s32 endFrame;
    s16* replayTimer = &lbl_3_common_bss_37400._42;
    if (g_FieldingLogic._107 == 0 && g_Ball.AtBat_ContactResult == 0 && g_Ball.deadBallReason == 0) {
        g_FieldingLogic._0AE = 0;
        return;
    }
    if (g_FieldingLogic._128 != 0 && lbl_3_common_bss_32724._B1 == 0) {
        if (g_Strikes.outs < 3 && g_RunningLogic._00 != 0) {
            g_FieldingLogic._0AE = 0;
        }
        g_FieldingLogic._128 = 0;
    }
    if (g_FieldingLogic._0EE != 0) {
        if (g_FieldingLogic._0EE < 0x7FFE) {
            g_FieldingLogic._0EE += 1;
        } else {
            g_FieldingLogic._0EE = 0x7FFF;
        }
        if (g_FieldingLogic._0EE > 90) {
            g_FieldingLogic._0EE = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        InMemRunnerType* runner = &g_Runners[i];
        if (runner->runnerOnFieldOrOutOrScored == 1) {
            s16 base = runner->baseStandingOn;
            if (base < 0) {
                settled = 0;
            } else if (runner->runningDirectionCode == 1 && runner->overRun1BStage == 0) {
                settled = 0;
            } else if (base != runner->currentBase) {
                settled = 0;
            }
            if (runner->tagUpInd == 2) {
                settled = 0;
            }
            if (runner->forceOutCd == 1) {
                settled = 0;
            }
            runnersOnField++;
        }
    }
    if (g_Ball.deadBallReason == 1) {
        if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.practiceLevel != 6 && g_Practice.practiceLevel != 7) {
            if (g_Practice._1B0 == 0) {
                if (g_Controls[g_Practice.homeAway].newButtonInput & 0x1100) {
                    g_Practice._1B0 = 1;
                }
                limit = 300;
            } else {
                limit = 45;
            }
        } else {
            limit = 120;
            if (g_GameLogic.homeRunWordAnimationCompletedInd == 0 && g_FieldingLogic._0AE == 0x76) {
                g_GameLogic.homeRunWordAnimationCompletedInd = 1;
                for (i = 0; i < 4; i++) {
                    u8 st = g_Runners[i].runnerOnFieldOrOutOrScored;
                    if (st == 1 || st == 3 || st == 4) {
                        g_Runners[i].runnerOnFieldOrOutOrScored = 3;
                        g_Scores._9C += 1;
                    }
                }
            }
        }
    } else if (g_Ball.AtBat_ContactResult == -1 && g_GameLogic.EventTriggers_EndOfGame == 0) {
        limit = 60;
    } else if (g_GameLogic.EventTriggers_EndOfGame != 0 && g_Ball.deadBallReason != 1) {
        limit = 210;
        if (g_Scores.inning >= g_Scores.finalInning && g_Scores.bottomHalf != 0) {
            fn_3_59918(0xD, 0);
        }
    } else if (g_Strikes.outs >= 3) {
        limit = 120;
    } else if (runnersOnField == 0 && g_Ball.deadBallReason != 1 && g_Ball.ballInitialHitDoneInd != 0 && g_Ball.ballState != 0) {
        limit = 120;
    } else if (g_Ball.deadBallReason == 0) {
        if (g_GameLogic.playOver == 0 && g_Ball.ballState == 3 && g_GameLogic.walkOffWinInd == 0) {
            limit = 300;
        }
        if (g_GameLogic.walkOffWinInd == 0) {
            if (g_Ball.ballState == 0 && g_Runners[0].runnerOnFieldOrOutOrScored != 3) {
                g_FieldingLogic._0AE = 0;
                return;
            }
            if (settled == 0) {
                g_FieldingLogic._0AE = 0;
                return;
            }
        }
    } else if (g_Ball.deadBallReason == 3 || g_Ball.deadBallReason == 4) {
        limit = 120;
    } else {
        limit = 60;
    }

    if (g_FieldingLogic._0AE < 0x7FFE) {
        g_FieldingLogic._0AE += 1;
    } else {
        g_FieldingLogic._0AE = 0x7FFF;
    }
    if (g_GameLogic.framePlayEnd > limit) {
        if (g_FieldingLogic._0AE > limit - 90) {
            g_FieldingLogic._0AE = 0;
            g_FieldingLogic._0EE = 0;
        }
    } else if (g_GameLogic.framePlayEnd < limit && g_FieldingLogic._10E != 0) {
        limit = g_GameLogic.framePlayEnd;
    }
    if (g_Ball.deadBallReason == 1 && g_Ball.matchFramesAndBallAngle.ballOverWallFrames == 180 && g_Stats.replayInd == 0) {
        fn_3_7CE90();
    }
    if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.type != 0 && g_Stats.replayInd == 0 &&
        g_GameLogic.playOver != 0 && g_Ball.deadBallReason != 1) {
        *replayTimer -= 1;
        if (g_FieldingLogic._0AE >= limit || *replayTimer <= 5) {
            fn_3_7CE90();
        }
        if (*replayTimer == 5 && g_Ball.deadBallReason != 1) {
            g_GameLogic.walkOffWinInd = 1;
            changeScene(3, 6);
            if (lbl_3_common_bss_37400._47 != 0) {
                fn_3_90328(6);
            }
        }
        if (*replayTimer <= 0) {
            fn_3_5DF54();
        }
        if (g_Ball.deadBallReason != 1 && g_Stats._39 != 0 && *replayTimer == 30) {
            lbl_3_common_bss_32724._B1 = 1;
        }
    } else if (g_FieldingLogic._0AE >= limit) {
        if (g_Stats.replayInd == 0) {
            fn_3_7CE90();
        }
        fn_3_5DF54();
    } else if (g_FieldingLogic._0AE == limit - 6 && g_Stats.replayInd == 0 && lbl_3_common_bss_32724._B1 == 0 &&
               g_Ball.deadBallReason != 1) {
        g_GameLogic.walkOffWinInd = 1;
        changeScene(3, 6);
    }
    endFrame = limit - 30;
    if (g_FieldingLogic._0AE == endFrame) {
        s32 showReplay;
        fn_3_7BC20();
        g_GameLogic.playOver = 1;
        showReplay = 1;
        if (g_Ball.AtBat_ContactResult == -1 && g_Ball.maybebuntOn2Strikes == 0) {
            showReplay = 0;
            g_GameLogic.playOver = 0;
        } else if (g_FieldingLogic._107 != 0 && g_FieldingLogic._107 != 4 && g_Pitcher.strikeOutOrWalk == 0) {
            showReplay = 0;
            if (g_Strikes.outs < g_Strikes.storedOuts) {
                g_GameLogic.playOver = 0;
            }
        }
        if (g_Stats._39 != 0) {
            showReplay = 1;
        }
        if (showReplay != 0) {
            lbl_3_common_bss_34C58._2A = 1;
            lbl_3_common_bss_34C58._24 = 29;
        }
        g_FieldingLogic._10E = 1;
        g_FieldingLogic._0EE = 1;
        if (g_GameLogic.IsStarChance == 1 && (g_Ball.AtBat_ContactResult != -1 || g_Ball.maybebuntOn2Strikes != 0)) {
            s32 team;
            if (g_Strikes.outs > g_Strikes.storedOuts) {
                g_GameLogic.IsStarChance = 2;
                team = g_GameLogic.teamFielding;
            } else {
                g_GameLogic.IsStarChance = 3;
                team = g_GameLogic.teamBatting;
            }
            if (g_GameLogic.TeamStars[team] < 5 && g_GameLogic.EventTriggers_EndOfGame == 0) {
                g_GameLogic.TeamStars[team] += 1;
                if (g_Stats.replayInd == 0) {
                    playSoundEffect(0x19D);
                }
            }
        }
        if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.type != 0 && g_Stats.replayInd == 0 &&
            g_GameLogic.playOver != 0) {
            fn_3_164A74();
            if (g_Ball.deadBallReason != 1) {
                *replayTimer = 120;
            }
            if (lbl_3_common_bss_37400.state == 0) {
                if (g_FieldingLogic._107 == 0) {
                    lbl_3_common_bss_32724._B4 = 1;
                } else if (g_Strikes.outs >= 3 || lbl_3_common_bss_37400._47 != 0) {
                    lbl_3_common_bss_32724._B4 = 1;
                } else {
                    *replayTimer = 8;
                }
            } else if (g_Stats._39 != 0) {
                *replayTimer = limit - 76;
            } else {
                *replayTimer = 8;
            }
        }
        g_Stats._3B = 1;
    } else if (g_FieldingLogic._0AE - 1 == endFrame && lbl_3_common_bss_37400._47 == 0 && g_Ball.deadBallReason != 1 &&
               g_Stats._39 != 0) {
        lbl_3_common_bss_32724._B1 = 1;
    }
    g_GameLogic.framePlayEnd = limit;
    g_GameLogic.CountdownUntilFade = limit - g_FieldingLogic._0AE;
}
#endif

// .data 0x3D60-0x65F0: file-loading tables, then the batting/fielding/minigame tables read as
// globals by game_batter, rep_540/AC8/1200/13B8/18E8 and others. The gap 0x5985C-0x60768 holds the
// text of the rodata-only units rep_CC8/D18/D68/DB8 (one TU each), so these tables belong to
// them; they are kept with that text here until it is split.
// .data 0x00003D60..0x000065F0
DiskFileEntry lbl_3_data_3D60 = {1035, 0x400098A0, 0x773D800, 15496};
DiskFileEntry lbl_3_data_3D70 = {1035, 0x40000970, 0x7741800, 872};
DiskFileEntry lbl_3_data_3D80[67] = {
    {0x40B, 0x4013764C, 0x1A635000, 0x7DB48},
    {0x40B, 0x4003E3DC, 0x1A6B3000, 0x21420},
    {0x40B, 0x4002EC10, 0x1A6D4800, 0x13108},
    {0x40B, 0x400E72C0, 0x1A6E8000, 0x60768},
    {0x40B, 0x40049404, 0x1A748800, 0x20E34},
    {0x40B, 0x40076AE0, 0x18ED7000, 0x36BC8},
    {0x40B, 0x4010FD70, 0x1A769800, 0x5E284},
    {0x40B, 0x400DB738, 0x1A7C8000, 0x49AB4},
    {0x40B, 0x400E9864, 0x1A812000, 0x59DC0},
    {0x40B, 0x400B7718, 0x1A86C000, 0x50288},
    {0x40B, 0x400D87FC, 0x1A8BC800, 0x47BC4},
    {0x40B, 0x400D643C, 0x1A904800, 0x4E3AC},
    {0x40B, 0x400D5C7C, 0x1A953000, 0x48D9C},
    {0x40B, 0x400B767C, 0x1A99C000, 0x47518},
    {0x40B, 0x400441F8, 0x1A9E3800, 0x1AA84},
    {0x40B, 0x40106568, 0x1A9FE800, 0x68C10},
    {0x40B, 0x4010E5A0, 0x0E97A800, 0x9BCAC},
    {0x40B, 0x40016980, 0x0EA16800, 0xD6C4},
    {0x40B, 0x40016980, 0x0EA24000, 0xC944},
    {0x40B, 0x40016980, 0x0EA31000, 0xE700},
    {0x40B, 0x40016980, 0x0EA3F800, 0xD64C},
    {0x40B, 0x40016980, 0x0EA4D000, 0xC900},
    {0x40B, 0x40016980, 0x0EA5A000, 0xCFFC},
    {0x40B, 0x40016980, 0x0EA67000, 0xD720},
    {0x40B, 0x40016980, 0x0EA74800, 0xD6CC},
    {0x40B, 0x40016980, 0x0EA82000, 0xD21C},
    {0x40B, 0x40016980, 0x0EA8F800, 0xD0BC},
    {0x40B, 0x40016980, 0x0EA9D000, 0xB544},
    {0x40B, 0x40016980, 0x0EAA8800, 0xC4F8},
    {0x40B, 0x400ADFFC, 0x18AEE800, 0x4BAB0},
    {0x40B, 0x4037CF5C, 0x18B3A800, 0x208AF0},
    {0x40B, 0x4000A820, 0x18ED3800, 0x3758},
    {0x40B, 0x4011EC24, 0x18F0E000, 0xD8818},
    {0x40B, 0x400193E8, 0x191B8800, 0x89D8},
    {0x40B, 0x4006C850, 0x06C96000, 0x2C884},
    {0x40B, 0x4005B178, 0x06CC3000, 0x3555C},
    {0x40B, 0x401EB174, 0x18D43800, 0xFB220},
    {0x40B, 0x4001ED60, 0x1AA67800, 0xCFF0},
    {0x40B, 0x4000BF30, 0x1AA74800, 0x26E0},
    {0x40B, 0x40003498, 0x1AA77000, 0xE28},
    {0x40B, 0x4000BDE0, 0x1AA78000, 0x24F4},
    {0x40B, 0x40006088, 0x1AA7A800, 0x1290},
    {0x40B, 0x400049F0, 0x1AA7C000, 0x18F4},
    {0x40B, 0x40005ECC, 0x1AA7E000, 0x1D38},
    {0x40B, 0x40002670, 0x1AA80000, 0xBE8},
    {0x0, 0x00028240, 0x1AA81000, 0x28240},
    {0x0, 0x00028240, 0x1AAA9800, 0x28240},
    {0x0, 0x00028240, 0x1AAD2000, 0x28240},
    {0x0, 0x00028240, 0x1AAFA800, 0x28240},
    {0x0, 0x00028240, 0x1AB23000, 0x28240},
    {0x0, 0x00028240, 0x1AB4B800, 0x28240},
    {0x0, 0x00028240, 0x1AB74000, 0x28240},
    {0x0, 0x00028240, 0x1AB9C800, 0x28240},
    {0x0, 0x00028240, 0x1ABC5000, 0x28240},
    {0x0, 0x00028240, 0x1ABED800, 0x28240},
    {0x0, 0x00028240, 0x1AC16000, 0x28240},
    {0x0, 0x00028240, 0x1AC3E800, 0x28240},
    {0x0, 0x00028240, 0x1AC67000, 0x28240},
    {0x0, 0x00028240, 0x1AC8F800, 0x28240},
    {0x0, 0x00028240, 0x1ACB8000, 0x28240},
    {0x0, 0x00028240, 0x1ACE0800, 0x28240},
    {0x0, 0x00028240, 0x1AD09000, 0x28240},
    {0x40B, 0x40001640, 0x08EB4800, 0xC38},
    {0x40B, 0x400B2D00, 0x08EB5800, 0x6A948},
    {0x0, 0x00000686, 0x08F20800, 0x688},
    {0x0, 0x00003C98, 0x08F21000, 0x3C98},
    {0x40B, 0x4000EBBC, 0x08F25000, 0x9570},
};
u8 lbl_3_data_428C[4] = {0}; // alignment padding (unused)
f32 lbl_3_data_4290[28] = {
    -24.0f, -7.5f, 24.0f, -7.5f, -18.0f, -8.5f, 18.0f, -8.5f, -28.5f, 0.5f, 28.5f, 0.5f, -28.5f,
    -2.5f, 28.5f, -2.5f, -27.5f, -4.5f, 27.5f, -4.5f, -24.0f, 6.0f, 24.0f, 6.0f, -23.0f, -4.5f,
    23.0f, -4.5f,
};
f32 lbl_3_data_4300[18] = {
    0.0f, 3.0f, -3.0f, 2.5f, 3.0f, 2.5f, -2.0f, 5.0f, 2.0f, 5.0f, -4.0f, 5.5f, -1.5f, 7.5f, 1.5f,
    7.5f, 4.0f, 5.5f,
};
f32 lbl_3_data_4348[14] = {
    0.6f, -0.6f, 0.6f, -0.6f, 0.6f, -0.6f, 0.6f, -0.6f, 0.6f, -0.6f, 0.6f, -0.6f, 0.6f, -0.6f,
};
u8 lbl_3_data_4380[8] = {70, 100, 55, 45, 45, 45, 70, 0};
f32 lbl_3_data_4388[35] = {
    0.44f, 0.9f, 0.66f, 0.85f, 0.999f, 0.46f, 0.9f, 0.7f, 0.87f, 0.999f, 0.4f, 0.9f, 0.6f, 0.85f,
    0.99f, 0.45f, 0.9f, 0.64f, 0.85f, 0.995f, 0.45f, 0.9f, 0.67f, 0.85f, 0.996f, 0.44f, 0.9f, 0.65f,
    0.85f, 0.996f, 0.7f, 0.9f, 0.99f, 0.9f, 0.983f,
};
f32 lbl_3_data_4414[5] = {0.35f, 0.45f, 0.5f, 0.45f, 0.5f};
f32 lbl_3_data_4428[7] = {0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.75f};
f32 lbl_3_data_4444[10] = {0.05f, 0.25f, 18.95f, 19.4f, 0.1f, 39.0f, -18.95f, 19.4f, 0.0f, 18.5f};
f32 lbl_3_data_446C[2] = {0.0f, 18.4f};
f32 lbl_3_data_4474[4] = {-0.4f, 0.4f, 0.08f, 0.16f};
f32 lbl_3_data_4484[12] = {
    6.0f, 0.0f, -6.0f, 0.0f, 20.0f, 27.0f, 8.0f, 40.0f, -8.0f, 40.0f, -20.0f, 27.0f,
};
f32 lbl_3_data_44B4[22] = {
    0.0f, 0.0f, 0.0f, 0.0f, 17.0f, 4.0f, -17.0f, 4.0f, 36.0f, 30.0f, -36.0f, 30.0f, 17.0f, 57.0f,
    -17.0f, 57.0f, -28.0f, 53.0f, 0.0f, 68.0f, 28.0f, 53.0f,
};
f32 lbl_3_data_450C[9][2] = {
    {0.0f, 18.6f},
    {0.0f, -3.8f},
    {18.5f, 22.0f},
    {11.0f, 36.0f},
    {-18.5f, 22.0f},
    {-11.0f, 36.0f},
    {-34.0f, 60.0f},
    {0.0f, 76.0f},
    {34.0f, 60.0f},
};
f32 lbl_3_data_4554[4][3][2] = {
    {{18.5f, 22.0f}, {19.0f, 19.5f}, {17.5f, 20.0f}},
    {{11.0f, 36.0f}, {4.0f, 38.0f}, {10.0f, 37.0f}},
    {{-18.5f, 22.0f}, {-18.0f, 20.0f}, {-17.5f, 22.0f}},
    {{-11.0f, 36.0f}, {-4.0f, 38.0f}, {-10.0f, 37.0f}},
};
f32 lbl_3_data_45B4[4][2] = {{14.0f, 16.0f}, {15.0f, 35.0f}, {-15.0f, 17.0f}, {-7.0f, 38.0f}};
f32 lbl_3_data_45D4[4][2] = {{-34.0f, 60.0f}, {0.0f, 76.0f}, {34.0f, 60.0f}, {0.0f, 0.0f}};
f32 lbl_3_data_45F4[2] = {0.15f, 0.35f};
f32 lbl_3_data_45FC = 0.00275f;
u8 lbl_3_data_4600 = 40;
f32 lbl_3_data_4604 = 0.08f;
u8 lbl_3_data_4608 = 2;
u8 lbl_3_data_4609[3] = {0}; // alignment padding (unused)
s16 lbl_3_data_460C[6] = {120, 140, 30, 30, 30, -1};
f32 lbl_3_data_4618[8] = {15.0f, 20.0f, 1.05f, 1.1f, 1.2f, 1.1f, 1.25f, 1.5f};
s16 lbl_3_data_4638[4] = {90, 20, 90, 90};
f32 lbl_3_data_4640[2][22] = {
    {
        0.11f, 0.111f, 0.112f, 0.118f, 0.119f, 0.12f, 0.124f, 0.125f,
        0.126f, 0.131f, 0.133f, 0.135f, 0.138f, 0.14f, 0.143f, 0.145f,
        0.147f, 0.149f, 0.151f, 0.153f, 0.155f, 0.155f,
    },
    {
        0.135f, 0.14f, 0.145f, 0.15f, 0.155f, 0.16f, 0.165f, 0.17f,
        0.175f, 0.18f, 0.185f, 0.19f, 0.195f, 0.2f, 0.2f, 0.2f,
        0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f,
    },
};
f32 lbl_3_data_46F0 = 1.5f;
f32 lbl_3_data_46F4 = 0.7f;
u8 lbl_3_data_46F8[20] = {25, 40, 16, 15, 18, 17, 50, 50, 50, 25, 45, 21, 15, 23, 17, 50, 50, 50, 0, 0};
u8 lbl_3_data_470C[1] = {10};
u8 lbl_3_data_470D[3] = {30, 0, 0}; // unreferenced
u8 lbl_3_data_4710[4] = {4, 25}; // AI reaction delay range (u8[2]), padded to 4
u8 lbl_3_data_4714[2][4][6] = {
    {{2, 2, 10, 3, 7, 10}, {3, 6, 10, 4, 11, 10}, {3, 4, 10, 4, 15, 10}, {1, 1, 10, 1, 5, 10}},
    {
        {20, 40, 50, 30, 40, 50},
        {30, 50, 60, 50, 70, 70},
        {40, 60, 70, 60, 80, 80},
        {10, 20, 30, 10, 30, 40},
    },
};
u8 lbl_3_data_4744[24] = {
    85, 90, 95, 105, 110, 115, 125, 130, 135, 140, 160, 165, 170, 180, 190, 200,
    210, 220, 230, 240, 255, 255, 0, 0,
};
u8 lbl_3_data_475C = 6;
f32 lbl_3_data_4760[3] = {0.0005f, 1.22f, 1.3f};
f32 lbl_3_data_476C[5] = {0.6f, 0.7f, 0.8f, 0.9f, 1.0f};
f32 lbl_3_data_4780[5] = {0.8f, 0.95f, 1.1f, 1.25f, 1.5f};
f32 lbl_3_data_4794[10] = {0.95f, 1.05f, 1.15f, 1.25f, 1.4f, 1.05f, 1.1f, 1.2f, 1.3f, 1.4f};
f32 lbl_3_data_47BC[5] = {0.6f, 0.7f, 0.8f, 0.9f, 1.0f};
f32 lbl_3_data_47D0[30] = {
    1.15f, 0.4f, 1.0f, 1.85f, 0.3f, 1.1f, 0.45f, 1.1f, 1.95f, 0.5f, 1.2f, 0.5f, 1.2f, 2.05f, 0.6f,
    1.3f, 0.6f, 1.3f, 2.15f, 0.7f, 1.4f, 0.7f, 1.4f, 2.25f, 0.8f, 4.5f, 1.0f, 2.0f, 2.25f, 1.0f,
};
f32 lbl_3_data_4848 = 2.5f;
s16 lbl_3_data_484C[10] = {20, 180, 768, 45, 90, 36, 55, 30, 15, 0};
s16 lbl_3_data_4860[4][3] = {{0x200, 0xA00, 0xE00}, {0x600, 0xE00, 0x200}, {0xA00, 0x1200, 0x600}, {0xE00, 0x1600, 0xA00}}; // Tbl6 (rep_18E8): angle range a..b, c
f32 lbl_3_data_4878[2] = {0.15f, 0.98f};
s16 lbl_3_data_4880 = 30;
u8 lbl_3_data_4882[2] = {0}; // alignment padding (unused)
f32 lbl_3_data_4884[8] = {0.3f, 0.02f, 0.75f, 6.0f, 0.4f, 0.02f, 0.75f, 12.0f};
s16 lbl_3_data_48A4[16] = {10, 20, 25, 30, 30, 20, 30, 40, 50, 50, 60, 75, 90, 120, 120, 0};
f32 lbl_3_data_48C4 = 0.5f;
s16 lbl_3_data_48C8[2][12] = {
    {772, 968, -256, 256, 256, 512, 2248, 2360, 768, 996, -2048, 2047},
    {772, 968, -256, 256, 256, 512, 2248, 2360, 768, 996, -2048, 2047},
};
u8 lbl_3_data_48F8[8] = {15, 15, 20, 25, 30, 0, 0, 0};
u8 lbl_3_data_4900[8] = {6, 12, 10, 0, 0, 7, 0, 0};
u8 lbl_3_data_4908[4] = {20, 20}; // bad-chemistry miss chance range (u8[2]), padded to 4
f32 lbl_3_data_490C[6] = {1.0f, 5.0f, 0.15f, 1.2f, 5.0f, 0.2f};
s16 lbl_3_data_4924[6] = {45, 6, 25, 60, 6, 25};
f32 lbl_3_data_4930[43] = {
    12.0f, 7.0f, 8.0f, 5.0f, 7.0f, 2.5f, 2.5f, 2.0f, 2.5f, 6.5f, 1.0f, 0.007f, 0.8f, 0.15f, 0.95f,
    5.0f, 0.15f, 0.15f, 0.007f, 0.2f, 0.2f, 0.1f, -0.05f, 0.95f, -0.02f, 0.1f, 0.0015f, 0.5f, 4.0f,
    2.0f, 1.1f, 5.0f, 10.0f, 0.1f, 0.3f, 0.98f, 7.0f, 15.0f, 1.5f, 5.0f, 12.0f, 5.0f, 12.0f,
};
s16 lbl_3_data_49DC[44] = {
    6, 50, 25, 15, 20, 40, 30, 12,
    30, 60, 60, 12, 6, 2, 30, 6,
    12, 2, 512, 6, 2, 20, 15, 2,
    5, 30, 10, 64, 96, 90, 90, 60,
    64, 60, 120, 64, 96, 45, 75, 60,
    3, 36, 12, 20,
};
f32 lbl_3_data_4A34[8] = {0.4f, 0.3f, 18.8f, 19.4f, 0.0f, 38.7f, -18.5f, 19.3f};
f32 lbl_3_data_4A54[52] = {
    0.0f, 0.0f, 12.5f, 10.5f, 18.0f, 16.5f, 18.8f, 19.4f, 18.6f, 22.0f, 3.0f, 37.5f, 0.0f, 38.7f,
    -3.0f, 38.7f, -17.5f, 22.0f, -18.5f, 19.3f, -18.5f, 17.5f, 0.4f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f,
    2.0f, 0.5f, 19.0f, 17.5f, 19.5f, 19.5f, 19.0f, 21.5f, 2.0f, 38.5f, 0.0f, 39.0f, -2.0f, 38.5f,
    -19.0f, 21.5f, -19.5f, 19.5f, -19.0f, 17.5f, -2.0f, 0.5f, 0.0f, 0.0f,
};
f32 lbl_3_data_4B24 = 0.012f;
f32 lbl_3_data_4B28[6] = {18.8f, 19.4f, 23.0f, 22.0f, 25.1f, 22.5f};
s16 lbl_3_data_4B40[1] = {60};
s16 lbl_3_data_4B42 = 120; // unreferenced
f32 lbl_3_data_4B44 = 0.1f;
s16 lbl_3_data_4B48[4] = {15, 10, 18, 0};
f32 lbl_3_data_4B50 = 0.3f;
s16 lbl_3_data_4B54 = 45;
f32 lbl_3_data_4B58[12] = {
    2.36f, -2.36f, 3.14f, 0.78f, -2.36f, 1.57f, -0.78f, 2.36f, 0.0f, -2.31f, -2.36f, -1.57f,
};
f32 lbl_3_data_4B88[2] = {1.0f, 0.66f};
s16 lbl_3_data_4B90[4] = {1, 15, 15, 40};
f32 lbl_3_data_4B98 = 0.4f;
s16 lbl_3_data_4B9C[6] = {10, 50, 15, 3, 30, 20}; // FieldingBoostParams (rep_AC8)
u8 bodyCheckProbabiliities[5][5] = {
    {35, 30, 27, 25, 23},
    {40, 35, 30, 27, 25},
    {50, 40, 35, 30, 27},
    {60, 50, 40, 35, 30},
    {70, 60, 50, 40, 35},
};
f32 lbl_3_data_4BC4[10] = {0.01f, 0.005f, 0.005f, 0.005f, 0.02f, 0.02f, 5.0f, 5.0f, 20.0f, 20.0f};
f32 runnerVelocityLookup[22] = {
    0.132f, 0.135f, 0.137f, 0.139f, 0.141f, 0.143f, 0.145f, 0.148f,
    0.151f, 0.154f, 0.157f, 0.16f, 0.164f, 0.168f, 0.173f, 0.176f,
    0.179f, 0.182f, 0.185f, 0.188f, 0.19f, 0.19f,
};
f32 lbl_3_data_4C44[4] = {0.5f, 0.3f, 0.5f, 0.5f};
s16 lbl_3_data_4C54[12] = {30, -20, 3, 30, 2, 20, 4, 6, 1, 4000, 1, 3};
VecXYZ maybeInitialBatPos = {0.0f, 0.6f, 0.4f};
BatNearFarReach batContactRange[2] = {{-0.85f, 0.15f}, {-0.35f, 0.35f}};
f32 lbl_3_data_4C88[3] = {0.65f, 1.55f, 1.3f};
u8 ballContactArray[2][5][2][2][4] = {
    {
        {{{50, 98, 106, 150}, {30, 95, 109, 170}}, {{40, 98, 106, 160}, {20, 95, 109, 180}}},
        {{{60, 99, 101, 150}, {40, 97, 103, 170}}, {{55, 99, 101, 160}, {35, 97, 103, 180}}},
        {{{50, 99, 101, 140}, {40, 97, 103, 160}}, {{45, 99, 101, 145}, {35, 97, 103, 165}}},
        {{{80, 98, 102, 120}, {35, 95, 105, 165}}, {{80, 98, 102, 110}, {35, 95, 105, 165}}},
        {{{0, 0, 0, 0}, {0, 0, 0, 0}}, {{0, 0, 0, 0}, {0, 0, 0, 0}}},
    },
    {
        {{{40, 96, 104, 150}, {30, 93, 107, 170}}, {{30, 96, 104, 170}, {20, 93, 107, 180}}},
        {{{60, 96, 104, 140}, {35, 93, 107, 170}}, {{50, 96, 104, 150}, {25, 93, 107, 180}}},
        {{{60, 99, 101, 140}, {40, 97, 103, 160}}, {{40, 99, 101, 160}, {30, 97, 103, 170}}},
        {{{90, 98, 102, 110}, {75, 95, 105, 125}}, {{90, 98, 102, 110}, {75, 95, 105, 125}}},
        {{{0, 0, 0, 0}, {0, 0, 0, 0}}, {{0, 0, 0, 0}, {0, 0, 0, 0}}},
    },
};
f32 ContactPerfectThresholds[3][3] = {{99.1f, 100.9f, 1.05f}, {99.7f, 100.3f, 1.1f}, {99.7f, 100.3f, 1.0f}};
s16 hittableFrameInd[2][15] = {{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0}};
s16 BattingAngleRanges[3][2][15][2] = {
    {
        {
            {0, 0},
            {0, 0},
            {-700, -500},
            {-500, -350},
            {-400, -250},
            {-350, -100},
            {-150, 250},
            {200, 300},
            {250, 400},
            {350, 550},
            {550, 700},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {-600, -400},
            {-400, -200},
            {-300, -100},
            {-200, 200},
            {100, 400},
            {300, 450},
            {350, 600},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        {
            {0, 0},
            {0, 0},
            {-750, -500},
            {-500, -300},
            {-300, -150},
            {-150, 200},
            {200, 400},
            {300, 450},
            {400, 600},
            {500, 600},
            {600, 700},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {-600, -400},
            {-400, -200},
            {-300, 100},
            {100, 400},
            {100, 400},
            {200, 500},
            {500, 700},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        {
            {0, 0},
            {0, 0},
            {-700, -600},
            {-600, -400},
            {-450, -350},
            {-400, -300},
            {-350, -200},
            {-200, 150},
            {150, 300},
            {300, 700},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {-550, -300},
            {-400, -200},
            {-300, -100},
            {-300, -100},
            {-100, 200},
            {200, 450},
            {450, 650},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
};
s16 BarrelBatterBattingAngleRanges[3][2][15][2] = {
    {
        {
            {0, 0},
            {0, 0},
            {-512, -320},
            {-200, -200},
            {-200, -200},
            {-104, -104},
            {0, 0},
            {104, 104},
            {200, 200},
            {200, 200},
            {320, 512},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
            {-200, -200},
            {104, 104},
            {0, 0},
            {104, 104},
            {200, 200},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        {
            {0, 0},
            {0, 0},
            {-512, -320},
            {-200, -200},
            {-104, -104},
            {0, 0},
            {104, 104},
            {200, 200},
            {200, 200},
            {320, 512},
            {320, 512},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {-200, -200},
            {-104, -104},
            {0, 0},
            {104, 104},
            {200, 200},
            {320, 512},
            {320, 512},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        {
            {0, 0},
            {0, 0},
            {-512, -320},
            {-512, -320},
            {-200, -200},
            {-200, -200},
            {-104, -104},
            {0, 0},
            {104, 104},
            {200, 200},
            {320, 512},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {-512, -320},
            {-512, -320},
            {-200, -200},
            {-104, -104},
            {0, 0},
            {104, 104},
            {200, 200},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
};
s16 ToyFieldBattingAngleRanges[3][2][15][2] = {
    {
        {
            {0, 0},
            {0, 0},
            {-400, -300},
            {-350, -250},
            {-250, -150},
            {-200, -50},
            {-100, 100},
            {50, 200},
            {150, 250},
            {250, 350},
            {300, 400},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {-400, -300},
            {-300, -150},
            {-150, -50},
            {-100, 100},
            {50, 150},
            {150, 300},
            {300, 400},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        {
            {0, 0},
            {0, 0},
            {-360, -300},
            {-350, -250},
            {-250, -150},
            {-150, 150},
            {50, 200},
            {150, 250},
            {200, 300},
            {250, 350},
            {300, 400},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {-150, -100},
            {-100, -100},
            {100, 150},
            {100, 200},
            {200, 300},
            {300, 350},
            {350, 400},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        {
            {0, 0},
            {0, 0},
            {-400, -300},
            {-350, -250},
            {-300, -200},
            {-250, -150},
            {-200, -50},
            {-150, 150},
            {150, 250},
            {250, 350},
            {300, 360},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {-400, -350},
            {-350, -300},
            {-300, -200},
            {-200, -100},
            {-150, -100},
            {-100, 100},
            {100, 150},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
};
s16 HitVertTrajRanges[2][5][5][2] = {
    {
        {{-50, 50}, {50, 100}, {100, 300}, {300, 400}, {400, 500}},
        {{50, 150}, {150, 200}, {200, 250}, {250, 300}, {300, 350}},
        {{50, 150}, {150, 200}, {150, 200}, {200, 300}, {300, 350}},
        {{50, 150}, {150, 200}, {200, 250}, {250, 300}, {300, 350}},
        {{-50, 50}, {50, 100}, {100, 300}, {300, 400}, {400, 500}},
    },
    {
        {{400, 450}, {450, 500}, {500, 550}, {550, 600}, {550, 600}},
        {{50, 100}, {100, 150}, {300, 400}, {350, 450}, {400, 500}},
        {{100, 200}, {350, 400}, {450, 500}, {500, 550}, {530, 580}},
        {{50, 100}, {100, 150}, {300, 400}, {350, 450}, {400, 500}},
        {{400, 450}, {450, 500}, {500, 550}, {550, 600}, {550, 600}},
    },
};
s16 toyFieldHitVertTraj[2][5][5][2] = {
    {
        {{350, 400}, {400, 450}, {450, 500}, {500, 550}, {550, 600}},
        {{100, 200}, {100, 200}, {200, 300}, {300, 400}, {400, 500}},
        {{100, 200}, {100, 200}, {200, 300}, {300, 400}, {300, 400}},
        {{100, 200}, {100, 200}, {200, 300}, {300, 400}, {400, 500}},
        {{350, 400}, {400, 450}, {450, 500}, {500, 550}, {550, 600}},
    },
    {
        {{200, 350}, {350, 400}, {400, 450}, {450, 500}, {500, 550}},
        {{200, 300}, {250, 350}, {300, 400}, {350, 450}, {400, 500}},
        {{250, 300}, {300, 350}, {350, 400}, {400, 450}, {450, 500}},
        {{200, 300}, {250, 350}, {300, 400}, {350, 450}, {400, 500}},
        {{200, 350}, {350, 400}, {400, 450}, {450, 500}, {500, 550}},
    },
};
s16 CaptainStarSwingBattingVerticalAngleRanges[12][5][2] = {
    {{59, 61}, {59, 61}, {59, 61}, {59, 61}, {59, 61}},
    {{-101, -99}, {-101, -99}, {-101, -99}, {-101, -99}, {-101, -99}},
    {{350, 400}, {350, 400}, {350, 400}, {350, 400}, {350, 400}},
    {{450, 500}, {450, 500}, {450, 500}, {450, 500}, {450, 500}},
    {{120, 160}, {160, 200}, {160, 200}, {160, 200}, {120, 160}},
    {{250, 300}, {250, 300}, {250, 300}, {250, 300}, {250, 300}},
    {{64, 80}, {64, 80}, {64, 80}, {64, 80}, {64, 80}},
    {{64, 80}, {64, 80}, {64, 80}, {64, 80}, {64, 80}},
    {{350, 400}, {350, 400}, {350, 400}, {350, 400}, {350, 400}},
    {{200, 250}, {200, 250}, {200, 250}, {200, 250}, {200, 250}},
    {{350, 600}, {350, 600}, {350, 600}, {350, 600}, {350, 600}},
    {{350, 600}, {350, 600}, {350, 600}, {350, 600}, {350, 600}},
};
s16 NonCaptainStarSwingBattingVerticalAngleRanges[3][5][2] = {
    {{250, 300}, {300, 350}, {350, 400}, {400, 450}, {450, 500}},
    {{50, 100}, {50, 100}, {50, 100}, {50, 100}, {50, 100}},
    {{120, 160}, {160, 200}, {160, 200}, {160, 200}, {120, 160}},
};
s16 bODHitVertTraj[5][5][2] = {
    {{-100, 0}, {0, 100}, {100, 200}, {200, 500}, {500, 800}},
    {{-100, 0}, {0, 100}, {100, 200}, {200, 300}, {500, 600}},
    {{256, 480}, {256, 480}, {256, 480}, {256, 480}, {256, 360}},
    {{-100, 0}, {0, 100}, {100, 200}, {200, 300}, {500, 600}},
    {{-100, 0}, {0, 100}, {100, 200}, {200, 500}, {500, 800}},
};
s16 bB_launchAngles[2][3] = {{184, 288, 64}, {0, 0, 0}};
s16 lbl_3_data_54F8[2][2] = {{500, 550}, {500, 550}};
trajZones BattingVerticalAngleRangeProbabilities[3][2][2][5] = {
    {
        {
            {
                {0, 10, 20, 30, 40},
                {20, 20, 20, 20, 20},
                {10, 25, 30, 25, 10},
                {20, 20, 20, 20, 20},
                {40, 30, 20, 10, 0},
            },
            {
                {0, 10, 20, 30, 40},
                {20, 20, 20, 20, 20},
                {10, 25, 30, 25, 10},
                {20, 20, 20, 20, 20},
                {40, 30, 20, 10, 0},
            },
        },
        {
            {
                {10, 0, 20, 30, 40},
                {20, 22, 22, 28, 8},
                {20, 25, 25, 25, 5},
                {20, 22, 22, 28, 8},
                {10, 0, 20, 30, 40},
            },
            {
                {10, 0, 20, 30, 40},
                {20, 22, 22, 28, 8},
                {20, 25, 25, 25, 5},
                {20, 22, 22, 28, 8},
                {10, 0, 20, 30, 40},
            },
        },
    },
    {
        {
            {
                {0, 10, 20, 30, 40},
                {5, 5, 15, 40, 35},
                {5, 5, 20, 40, 35},
                {5, 5, 15, 40, 35},
                {40, 30, 20, 10, 0},
            },
            {
                {0, 10, 20, 30, 40},
                {5, 5, 15, 40, 35},
                {5, 5, 20, 40, 35},
                {5, 5, 15, 40, 35},
                {40, 30, 20, 10, 0},
            },
        },
        {
            {
                {5, 0, 10, 40, 45},
                {5, 21, 12, 29, 33},
                {5, 23, 15, 27, 30},
                {5, 21, 12, 29, 33},
                {5, 0, 10, 40, 45},
            },
            {
                {5, 0, 10, 40, 45},
                {5, 21, 12, 29, 33},
                {5, 23, 15, 27, 30},
                {5, 21, 12, 29, 33},
                {5, 0, 10, 40, 45},
            },
        },
    },
    {
        {
            {
                {10, 20, 20, 20, 30},
                {35, 40, 15, 5, 5},
                {30, 40, 20, 5, 5},
                {35, 40, 15, 5, 5},
                {40, 30, 20, 5, 5},
            },
            {
                {10, 20, 20, 20, 30},
                {35, 40, 15, 5, 5},
                {30, 40, 20, 5, 5},
                {35, 40, 15, 5, 5},
                {40, 30, 20, 5, 5},
            },
        },
        {
            {
                {10, 0, 20, 30, 40},
                {35, 30, 22, 10, 3},
                {30, 30, 25, 15, 0},
                {35, 30, 22, 10, 3},
                {10, 0, 20, 30, 40},
            },
            {
                {10, 0, 20, 30, 40},
                {35, 30, 22, 10, 3},
                {30, 30, 25, 15, 0},
                {35, 30, 22, 10, 3},
                {10, 0, 20, 30, 40},
            },
        },
    },
};
trajZones ToyFieldBattingVerticalAngleRanges[3][2][2][5] = {
    {
        {
            {
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
            },
            {
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
            },
        },
        {
            {
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
            },
            {
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
            },
        },
    },
    {
        {
            {
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
            },
            {
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
            },
        },
        {
            {
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
            },
            {
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
                {20, 20, 20, 20, 20},
            },
        },
    },
    {
        {
            {
                {20, 20, 20, 20, 20},
                {10, 20, 20, 20, 30},
                {10, 20, 20, 20, 30},
                {10, 20, 20, 20, 30},
                {20, 20, 20, 20, 20},
            },
            {
                {20, 20, 20, 20, 20},
                {10, 20, 20, 20, 30},
                {10, 20, 20, 20, 30},
                {10, 20, 20, 20, 30},
                {20, 20, 20, 20, 20},
            },
        },
        {
            {
                {20, 20, 20, 20, 20},
                {30, 20, 20, 20, 10},
                {30, 20, 20, 20, 10},
                {30, 20, 20, 20, 10},
                {20, 20, 20, 20, 20},
            },
            {
                {20, 20, 20, 20, 20},
                {30, 20, 20, 20, 10},
                {30, 20, 20, 20, 10},
                {30, 20, 20, 20, 10},
                {20, 20, 20, 20, 20},
            },
        },
    },
};
trajZones bODTrajProbabilities[5] = {
    {20, 20, 20, 20, 20},
    {20, 20, 20, 20, 20},
    {20, 20, 20, 20, 20},
    {20, 20, 20, 20, 20},
    {20, 20, 20, 20, 20},
};
u8 lbl_3_data_5771[3] = {0}; // alignment padding (unused)
s16 lbl_3_data_5774[30] = {
    100, 130, -110, 140, 145, -100, 145, 150, -110, 140, 145, -100,
    100, 130, -110, 140, 150, -120, 162, 177, -160, 160, 170, 0,
    162, 177, -160, 140, 150, -120,
};
s16 lbl_3_data_57B0[60] = {
    120, 130, -200, 140, 150, -200, 160, 170, -200, 140, 150, -200,
    120, 130, -200, 150, 160, -300, 170, 190, -300, 190, 200, -300,
    170, 190, -300, 150, 160, -300, 130, 140, -200, 145, 155, -300,
    160, 170, -300, 145, 155, -300, 130, 140, -200, 140, 150, -150,
    190, 200, -200, 200, 210, -180, 190, 200, -200, 140, 150, -150,
};
s16 lbl_3_data_5828[30] = {
    100, 120, 10, 130, 140, 10, 150, 160, 10, 130, 140, 10,
    100, 120, 15, 90, 110, 20, 150, 160, 20, 170, 230, 20,
    150, 160, 20, 90, 110, 10,
};
s16 lbl_3_data_5864[30] = {
    50, 70, 0, 200, 200, 10, 200, 200, 10, 200, 200, 10,
    50, 70, 0, 50, 70, 0, 200, 200, 10, 200, 200, 10,
    200, 200, 10, 50, 70, 0,
};
s16 lbl_3_data_58A0[180] = {
    140, 150, 0, 150, 160, 150, 160, 170, 150, 150, 160, 150,
    140, 150, 0, 120, 130, 0, 130, 150, 50, 160, 170, 100,
    130, 150, 50, 120, 130, 0, 90, 100, 80, 100, 110, 80,
    110, 120, 80, 100, 110, 80, 90, 100, 80, 60, 70, 80,
    70, 80, 80, 70, 80, 80, 70, 80, 80, 60, 70, 80,
    170, 180, -120, 170, 180, -130, 190, 200, -125, 170, 180, -135,
    170, 180, -125, 150, 160, -140, 150, 160, -150, 160, 170, -150,
    150, 160, -150, 150, 160, -140, 170, 180, 0, 170, 180, 0,
    190, 200, 0, 170, 180, 0, 170, 180, 0, 160, 170, 0,
    160, 170, 0, 180, 190, 0, 160, 170, 0, 160, 170, 0,
    90, 130, -650, 90, 130, -650, 90, 130, -650, 90, 130, -650,
    90, 130, -650, 140, 160, -400, 140, 160, -400, 140, 160, -400,
    140, 160, -400, 140, 160, -400, 130, 140, -100, 140, 150, -100,
    150, 160, -100, 140, 150, -100, 130, 140, -100, 130, 140, -100,
    140, 150, -100, 150, 160, -100, 140, 150, -100, 130, 140, -100,
};
s16 lbl_3_data_5A08[46] = {
    150, 160, -150, 160, 170, -150, 170, 180, -100, 160, 170, -150,
    150, 160, -150, 150, 160, -250, 160, 170, -250, 170, 180, -250,
    160, 170, -250, 150, 160, -250, 170, 180, -300, 170, 180, -300,
    190, 200, -300, 170, 180, -300, 170, 180, -300, 0,
};
sAng lbl_3_data_5A64[5][2][2] = {
    {{256, 960}, {256, 960}},
    {{480, 640}, {480, 640}},
    {{512, 576}, {512, 576}},
    {{480, 640}, {480, 640}},
    {{256, 960}, {256, 960}},
};
s16 buntVerticalAngles[5][2][2][2] = {
    {{{-256, 960}, {-256, 960}}, {{-256, 960}, {-256, 960}}},
    {{{-96, 64}, {-96, 96}}, {{-96, 64}, {-96, 96}}},
    {{{-64, 32}, {-64, 32}}, {{-64, 32}, {-64, 32}}},
    {{{-96, 64}, {-96, 96}}, {{-96, 64}, {-96, 96}}},
    {{{-256, 960}, {-256, 960}}, {{-256, 960}, {-256, 960}}},
};
u8 buntPower[5][2] = {{20, 50}, {45, 60}, {30, 45}, {45, 60}, {20, 50}};
u8 lbl_3_data_5AE6[2] = {0}; // alignment padding (unused)
u8 swingSoundFrame[2][4] = {{4, 6, 8, 14}, {5, 6, 7, 14}};
f32 lbl_3_data_5AF0[2] = {0.8f, 1.0f};
f32 lbl_3_data_5AF8[3][5] = {
    {1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
    {0.85f, 0.95f, 1.0f, 1.05f, 1.02f},
    {1.02f, 1.05f, 1.0f, 0.95f, 0.85f},
};
trajOptions_s hitTrajOptions[19] = {
    {{100, 100, 0x111110, 0x111110}, 0},
    {{100, 100, 0x111110, 0x111110}, 2},
    {{101, 102, 0x111110, 0x111110}, 1},
    {{90, 90, 0x111110, 0x111110}, 0},
    {{94, 95, 0x111110, 0x111110}, 0},
    {{102, 103, 0x111110, 0x111110}, 1},
    {{90, 90, 0x111110, 0x1100000}, 0},
    {{85, 90, 0x111110, 0x111110}, 0},
    {{102, 103, 0x111110, 0x111110}, 1},
    {{100, 100, 0x111110, 0x111110}, 0},
    {{95, 100, 0x111110, 0x111110}, 2},
    {{104, 105, 0x111110, 0x111110}, 1},
    {{60, 60, 0x111110, 0x111110}, 0},
    {{70, 75, 0x111110, 0x111110}, 0},
    {{87, 90, 0x111110, 0x111110}, 1},
    {{70, 70, 0x111110, 0x111110}, 0},
    {{80, 85, 0x111110, 0x111110}, 0},
    {{105, 110, 0x111110, 0x111110}, 1},
    {{50, 50, 0x110110, 0x110110}, 0},
};
f32 lbl_3_data_5CB0[3] = {0.5f, 0.7f, 0.8f}; // unreferenced
VecXYZ s_ballCurveData[2] = {{0.5f, 0.001f, 0.003f}, {0.25f, 0.006f, 0.008f}};
s16 lbl_3_data_5CD4[4] = {60, 90, 15, 45};
f32 lbl_3_data_5CDC[11] = {50.0f, 0.997f, 0.85f, 0.3f, 0.5f, 0.4f, 0.5f, 0.4f, 0.6f, 0.6f, 0.7f};
f32 lbl_3_data_5D08[5] = {1.0f, 0.85f, 0.75f, 0.65f, 0.5f};
HitFloats g_hitFloats = {0.05f, 0.008f, 0.25f, 0.95f, 0.8f, 4.0f, 0.2f, 0.3f, 0.5f, 1.0f, 3.0f, 1.5f};
HitShorts g_hitShorts = {180, 12, 6, 3, 90, 60, 2, 30, 120, 1, 1, 160, 160, 1, 50, 50};
s16 lbl_3_data_5D6C[134] = {
    150, 0, 0, 0, 0, 0, 0, 130, 25, 50, 15, 20,
    5, 0, 130, 8, 10, -20, 30, -2, 0, 130, 8, 10,
    30, 35, 5, 0, 200, 10, 20, 0, 0, 0, 0, 195,
    15, 25, 0, 0, 0, 0, 90, 0, 0, 15, 20, 0,
    0, 90, 0, 0, 15, 20, 0, 0, 110, 10, 20, 15,
    30, 5, -50, 110, 5, 10, 5, 50, 5, -30, 50, 3,
    8, -90, 55, 0, 0, 50, 3, 8, -50, 40, 0, 0,
    60, 0, 0, 15, 30, 30, 0, 60, 0, 0, 20, 30,
    30, 0, 70, 3, 8, 0, 40, 0, 0, 90, 3, 8,
    25, 40, 0, 0, 130, 25, 65, 20, 20, 5, 0, 130,
    8, 10, 10, 30, -2, 0, 130, 8, 10, 50, 50, 5,
    0, 0,
};
f32 lbl_3_data_5E78[2] = {8.0f, 2.0f};
#ifdef TARGET_PC
// game_batter reads row 3, which on GameCube is the start of lbl_3_data_5E98.
f32 lbl_3_data_5E80[4][2] = {{1.0f, 1.0f}, {1.0f, 0.8f}, {1.0f, 0.5f}, {-0.53f, 0.53f}};
#else
f32 lbl_3_data_5E80[3][2] = {{1.0f, 1.0f}, {1.0f, 0.8f}, {1.0f, 0.5f}};
#endif
f32 lbl_3_data_5E98[6] = {-0.53f, 0.53f, 1.05f, 0.5f, 0.7f, 0.0f}; // game_batter reads it as lbl_3_data_5E80[3]
f32 lbl_3_data_5EB0[2] = {-0.4f, 0.4f};
f32 lbl_3_data_5EB8[3] = {0.4f, 17.0f, 3.0f};
f32 lbl_3_data_5EC4[3] = {0.4f, 17.0f, 3.0f};
f32 lbl_3_data_5ED0[3] = {0.9f, 0.8f, 1.5f};
s16 lbl_3_data_5EDC[22] = {
    10, -1, -1, 4, 1, 99, 20, 100,
    100, 0, -2, -10, -20, -5, -20, -50,
    -10, -50, -100, -30, -100, -200,
};
f32 lbl_3_data_5F08[13] = {
    0.05f, 0.01f, 0.02f, 1.0f, 0.5f, 1.0f, 0.5f, 0.8f, 1.0f, 0.85f, 1.05f, 0.5f, 0.8f,
};
s16 lbl_3_data_5F3C[4] = {16, 12, 15, 0};
u8 lbl_3_data_5F44[12] = {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0};
u8 lbl_3_data_5F50[12] = {20, 35, 40, 55, 255, 25, 38, 30, 55, 200, 0, 0};
f32 lbl_3_data_5F5C[8] = {0.35f, 7.0f, 9.0f, 1.0f, 3.0f, 5.0f, 1.0f, 0.3f};
s16 lbl_3_data_5F7C[10] = {80, 80, 55, 60, 70, 90, 35, 45, 60, 100};
f32 lbl_3_data_5F90[12] = {240.0f, 0.998f, 0.5f, 0.35f, 0.2f, 0.35f, 0.03f, 0.05f, 0.0f, 0.0f, 0.99f, 0.99f};
#ifdef TARGET_PC
s16 lbl_3_data_5FC0[2] = {0, 50}; // [1] (star pitch pause) is lbl_3_data_5FC2 on GameCube
#else
s16 lbl_3_data_5FC0[1] = {0};
s16 lbl_3_data_5FC2 = 50; // unreferenced
#endif
f32 lbl_3_data_5FC4[12] = {1.5f, 0.0f, 1.5f, 0.0f, 10.0f, 1.5f, 0.9f, 1.5f, 1.5f, 0.0f, 50.0f, 0.0f};
BJStartSituation lbl_3_data_5FF4[2][4][2] = {
    {
        {{-2, 0, 0, 2}, {-2, 1, 1, 3}},
        {{-2, 0, 1, 2}, {-2, 1, 16, 3}},
        {{-1, 0, 0, 2}, {-1, 1, 16, 3}},
        {{-1, 1, 17, 3}, {-1, 2, 273, 4}},
    },
    {
        {{0, 0, 16, 2}, {0, 0, 17, 2}},
        {{0, 1, 16, 3}, {0, 0, 0, 2}},
        {{-1, 1, 16, 3}, {-1, 0, 0, 2}},
        {{-1, 2, 16, 4}, {-1, 1, 0, 3}},
    },
};
s16 lbl_3_data_6074[4] = {3, 2, 1, 0};
CoinRewardTable lbl_3_data_607C = {{0, 0, 0}, 0, 0, 0, {10, 0, -10}, {0, 0, -10}, {1, 0, -1}, -100};
u8 lbl_3_data_609C[12][6] = {
    {29, 30, 31, 32, 255, 255},
    {29, 30, 31, 32, 255, 255},
    {29, 30, 31, 32, 255, 255},
    {34, 35, 36, 33, 255, 255},
    {34, 35, 36, 33, 255, 255},
    {34, 35, 36, 33, 255, 255},
    {44, 45, 46, 47, 255, 255},
    {44, 45, 46, 47, 255, 255},
    {44, 45, 46, 47, 255, 255},
    {40, 17, 16, 14, 3, 10},
    {12, 37, 27, 20, 33, 11},
    {41, 2, 38, 9, 19, 48},
};
u8 lbl_3_data_60E4[6][2] = {{4, 1}, {9, 1}, {12, 1}, {15, 1}, {20, 1}, {0, 0}};
u8 lbl_3_data_60F0 = 30;
u8 lbl_3_data_60F1[3] = {0}; // alignment padding (unused)
struct StarPowerCosts starPowerCosts = {5, 1, 2, 1};
u8 lbl_3_data_60F8[12] = {5, 10, 10, 5, 5, 5, 3, 3, 1, 1, 0, 0};
u8 lbl_3_data_6104[8] = {0, 1, 4, 3, 2, 5, 0, 0};
f32 lbl_3_data_610C[6] = {0.1f, 0.4f, 0.7f, 0.2f, 0.5f, 1.0f};
f32 lbl_3_data_6124[3] = {0.75f, 0.5f, 0.0f};
DiskFileEntry lbl_3_data_6130[62] = {
    {0x40B, 0x4013764C, 0x1A635000, 0x7DB48},
    {0x40B, 0x4003E3DC, 0x1A6B3000, 0x21420},
    {0x40B, 0x4002EC10, 0x1A6D4800, 0x13108},
    {0x40B, 0x400E72C0, 0x1A6E8000, 0x60768},
    {0x40B, 0x40049404, 0x1A748800, 0x20E34},
    {0x40B, 0x40076AE0, 0x18ED7000, 0x36BC8},
    {0x40B, 0x4010FD70, 0x1A769800, 0x5E284},
    {0x40B, 0x400DB738, 0x1A7C8000, 0x49AB4},
    {0x40B, 0x400E9864, 0x1A812000, 0x59DC0},
    {0x40B, 0x400B7718, 0x1A86C000, 0x50288},
    {0x40B, 0x400D87FC, 0x1A8BC800, 0x47BC4},
    {0x40B, 0x400D643C, 0x1A904800, 0x4E3AC},
    {0x40B, 0x400D5C7C, 0x1A953000, 0x48D9C},
    {0x40B, 0x400B767C, 0x1A99C000, 0x47518},
    {0x40B, 0x400441F8, 0x1A9E3800, 0x1AA84},
    {0x40B, 0x40106568, 0x1A9FE800, 0x68C10},
    {0x40B, 0x4010E5A0, 0x0E97A800, 0x9BCAC},
    {0x40B, 0x40016980, 0x0EA16800, 0xD6C4},
    {0x40B, 0x40016980, 0x0EA24000, 0xC944},
    {0x40B, 0x40016980, 0x0EA31000, 0xE700},
    {0x40B, 0x40016980, 0x0EA3F800, 0xD64C},
    {0x40B, 0x40016980, 0x0EA4D000, 0xC900},
    {0x40B, 0x40016980, 0x0EA5A000, 0xCFFC},
    {0x40B, 0x40016980, 0x0EA67000, 0xD720},
    {0x40B, 0x40016980, 0x0EA74800, 0xD6CC},
    {0x40B, 0x40016980, 0x0EA82000, 0xD21C},
    {0x40B, 0x40016980, 0x0EA8F800, 0xD0BC},
    {0x40B, 0x40016980, 0x0EA9D000, 0xB544},
    {0x40B, 0x40016980, 0x0EAA8800, 0xC4F8},
    {0x40B, 0x400ADFFC, 0x18AEE800, 0x4BAB0},
    {0x40B, 0x4037CF5C, 0x18B3A800, 0x208AF0},
    {0x40B, 0x4000A820, 0x18ED3800, 0x3758},
    {0x40B, 0x4011EC24, 0x18F0E000, 0xD8818},
    {0x40B, 0x400193E8, 0x191B8800, 0x89D8},
    {0x40B, 0x4006C850, 0x06C96000, 0x2C884},
    {0x40B, 0x4005B178, 0x06CC3000, 0x3555C},
    {0x40B, 0x401EB174, 0x18D43800, 0xFB220},
    {0x40B, 0x4001ED60, 0x1AA67800, 0xCFF0},
    {0x40B, 0x4000BF30, 0x1AA74800, 0x26E0},
    {0x40B, 0x40003498, 0x1AA77000, 0xE28},
    {0x40B, 0x4000BDE0, 0x1AA78000, 0x24F4},
    {0x40B, 0x40006088, 0x1AA7A800, 0x1290},
    {0x40B, 0x400049F0, 0x1AA7C000, 0x18F4},
    {0x40B, 0x40005ECC, 0x1AA7E000, 0x1D38},
    {0x40B, 0x40002670, 0x1AA80000, 0xBE8},
    {0x0, 0x00028240, 0x1AA81000, 0x28240},
    {0x0, 0x00028240, 0x1AAA9800, 0x28240},
    {0x0, 0x00028240, 0x1AAD2000, 0x28240},
    {0x0, 0x00028240, 0x1AAFA800, 0x28240},
    {0x0, 0x00028240, 0x1AB23000, 0x28240},
    {0x0, 0x00028240, 0x1AB4B800, 0x28240},
    {0x0, 0x00028240, 0x1AB74000, 0x28240},
    {0x0, 0x00028240, 0x1AB9C800, 0x28240},
    {0x0, 0x00028240, 0x1ABC5000, 0x28240},
    {0x0, 0x00028240, 0x1ABED800, 0x28240},
    {0x0, 0x00028240, 0x1AC16000, 0x28240},
    {0x0, 0x00028240, 0x1AC3E800, 0x28240},
    {0x0, 0x00028240, 0x1AC67000, 0x28240},
    {0x0, 0x00028240, 0x1AC8F800, 0x28240},
    {0x0, 0x00028240, 0x1ACB8000, 0x28240},
    {0x0, 0x00028240, 0x1ACE0800, 0x28240},
    {0x0, 0x00028240, 0x1AD09000, 0x28240},
};

