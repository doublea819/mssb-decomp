#ifndef __GAME_AUTO_00_0011D3AC_TEXT_H_
#define __GAME_AUTO_00_0011D3AC_TEXT_H_

#include "mssbTypes.h"
#include "main/scene_task.h" // SCENE_TASK_VIEW_LINKS
#include "main/file_80024D2C.h" // ShapeAnimPlayer
#include "C3/anim.h"            // ANIMBank

// lbl_3_common_bss_32724: minigame result-screen assets and state, only the fields used here.
#ifdef PORT_LP64
// 64-bit: the pointer block (0x00-0x7C on GameCube) would be 0xB0 bytes and run over the flag
// bytes from 0x96 that the HUD views share (and past the 0x124-byte object), so it gets its own
// storage (g_port_mgAssets, MG_ASSETS) and this view keeps only the flags at their offsets.
typedef struct MinigameAssetPtrs {
    u8* model;
    ShapeAnimPlayer anim;
    void* skin;          // skin header for actor 17
    void* textures[3];
    ANIMBank* animBanks[3];
} MinigameAssetPtrs;
extern MinigameAssetPtrs g_port_mgAssets;
#define MG_ASSETS g_port_mgAssets
typedef struct MinigameAssets {
    /*0x00*/ u8 _00[0x96];
    /*0x96*/ u8 quit;
    /*0x97*/ u8 _97[0xB7 - 0x97];
    /*0xB7*/ u8 _B7;
    /*0xB8*/ u8 _B8[0xD8 - 0xB8];
    /*0xD8*/ u8 loadState;
} MinigameAssets;
#else
#define MG_ASSETS lbl_3_common_bss_32724
typedef struct MinigameAssets {
    /*0x00*/ u8* model;
    /*0x04*/ ShapeAnimPlayer anim;
    /*0x60*/ void* skin;          // skin header for actor 17
    /*0x64*/ void* textures[3];
    /*0x70*/ ANIMBank* animBanks[3];
    /*0x7C*/ u8 _7C[0x96 - 0x7C];
    /*0x96*/ u8 quit;
    /*0x97*/ u8 _97[0xB7 - 0x97];
    /*0xB7*/ u8 _B7;
    /*0xB8*/ u8 _B8[0xD8 - 0xB8];
    /*0xD8*/ u8 loadState;
} MinigameAssets;
#endif

// lbl_3_common_bss_34C90 (GamePauseState, game/auto_00_00097144_text.h, whose lbl_3_common_bss_32724
// declaration clashes with MinigameAssets): only the field used here.
typedef struct MinigamePauseView {
    /*0x000*/ u8 _000[0x1D2];
    /*0x1D2*/ u8 state; // GamePauseState.state
} MinigamePauseView;

// One actor's relocated data in lbl_8036E548 (CharMgr).
typedef struct MinigameActorData {
    /*0x0*/ void* layout;
    /*0x4*/ void* geometry;
    /*0x8*/ void* textures;
} MinigameActorData; // size: 0xC

// lbl_8036E548 (CharMgr in main/file_80011640.h), only the fields used here.
#ifdef PORT_LP64 // offsets for 64-bit pointers (wasm32 uses the GameCube layout)
// PC: CharMgr.trailFile at 0x39B8, trailLayout (the start of the relocated
// entries) at 0x39C0, _3078 at 0x3CB0 (clang's arm64 layout of CharMgr).
typedef struct MinigameCharMgrAssets {
    u8 _0000[0x39B8];
    u32* file;
    union {
        void* ptr[81];
        MinigameActorData actor[27];
    } data;
    u8 _2EE4[0x3CB0 - 0x39C0 - 81 * 8];
    s16 _3078;
} MinigameCharMgrAssets;
#else
typedef struct MinigameCharMgrAssets {
    /*0x0000*/ u8 _0000[0x2D9C];
    /*0x2D9C*/ u32* file;                    // offset table at the start of the loaded file
    /*0x2DA0*/ union {
        void* ptr[81]; // relocated file entries 0..80
        MinigameActorData actor[27];
    } data;
    /*0x2EE4*/ u8 _2EE4[0x3078 - 0x2EE4];
    /*0x3078*/ s16 _3078;
} MinigameCharMgrAssets;
#endif

// Sprite object in lbl_80371C30 (LayoutObj in main/file_8000F150.h), only the fields used here.
typedef struct PasswordSprite {
    /*0x00*/ struct PasswordSprite* link;
    /*0x04*/ void* _04;
    /*0x08*/ struct PasswordSprite* child;
    /*0x0C*/ u8 _0C[0x54 - 0xC];
    /*0x54*/ u32 flags;
    /*0x58*/ u8 _58[4];
    /*0x5C*/ u32 frame; // 16.16
    /*0x60*/ u8 _60[4];
    /*0x64*/ u16 anim;
    /*0x66*/ u8 _66[2];
    /*0x68*/ u8 visible;
    /*0x69*/ u8 animState;
} PasswordSprite;

typedef struct PasswordSlot {
    /*0x0*/ PasswordSprite* obj;
    /*0x4*/ void* owner;
} PasswordSlot;

// Queue task (lbl_803CC1B8) for the password / roulette / score-board screens.
typedef struct PasswordTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ SCENE_TASK_VIEW_LINKS
    /*0x14*/ u16 baseIdx; // first sprite in lbl_80371C30
    /*0x16*/ u16 count;
    /*0x18*/ u16 spins;
    /*0x1A*/ u16 done;
    /*0x1C*/ u16 state;
    /*0x1E*/ u16 _1E;
    /*0x20*/ u16 bits;
    /*0x22*/ u16 key;
    /*0x24*/ u32 sfx;     // roulette spin voice, 0xFFFFFFFF: none
} PasswordTask;

// Score-board task: same header, per-player "counting" flags at 0x24.
typedef struct ScoreBoardTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ SCENE_TASK_VIEW_LINKS
    /*0x14*/ u16 baseIdx;
    /*0x16*/ u16 count;
    /*0x18*/ u8 _18[0x1C - 0x18];
    /*0x1C*/ u16 state;
    /*0x1E*/ u8 _1E[0x24 - 0x1E];
    /*0x24*/ u8 counting[4];
} ScoreBoardTask;

// Password source record filled by fn_3_109DE0.
typedef struct PasswordRecord {
    /*0x0*/ u32 score;
    /*0x4*/ s16 value;
    /*0x6*/ s16 charID;
} PasswordRecord;

// This unit's view of g_Minigame (overlays the per-minigame area at 0x1DBC).
typedef struct MG11D3View {
    /*0x0000*/ u8 _0000[0x1DF4];
    /*0x1DF4*/ u8 hit[4];          // per player: score changed this frame
    /*0x1DF8*/ u8 _1DF8[0x1E04 - 0x1DF8];
#ifdef TARGET_PC
    /*0x1E04*/ PTR32(void) rouletteTask; // fn_3_11DECC task (PTR32: GameCube layout)
#else
    /*0x1E04*/ void* rouletteTask; // fn_3_11DECC task
#endif
    /*0x1E08*/ u8 _1E08[0x1E1C - 0x1E08];
    /*0x1E1C*/ u8 roundPick[6];    // roulette result per round (1-based)
    /*0x1E22*/ u8 _1E22[0x1E2A - 0x1E22];
    /*0x1E2A*/ u8 round;
} MG11D3View;

void fn_3_11D3AC(void);
s32 fn_3_11D6A0(void);
void fn_3_11D780(void);
void fn_3_11DACC(u8* code, u8* raw, u8 bits, u8 key);
u16 fn_3_11DDC4(u8* data, u32 len);
void fn_3_11DE80(void);
void fn_3_11DECC(void);
void fn_3_11E308(void);
void fn_3_11E364(void);
void fn_3_11E7C4(void);

#endif
