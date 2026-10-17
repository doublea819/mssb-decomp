#ifdef TARGET_PC
#define MG_TASK_PTR PTR32_GET(void, g_Minigame._1E04)
#else
#define MG_TASK_PTR (g_Minigame._1E04)
#endif
#ifdef TARGET_PC
// Character select (PC): set while a player's panels are hidden only because the new character's
// model is still loading (the game clears _19E8[i]._7 for ~20 frames of hover + ~25 frames of load).
// The 2D panels don't need the model, so the HUD (fn_3_12A910) keeps them shown meanwhile; _7 itself
// still gates confirming the pick.
u8 g_port_selLoading[4];
#endif
#include "game/auto_00_00106DFC_text.h"
// UnknownHomes_Game.h gives the typed globals; its guessed prototype of this unit's
// minigame_checkIfAIInputIs_Algorithmic_Or_ControllerBased disagrees, so hide it.
#define minigame_checkIfAIInputIs_Algorithmic_Or_ControllerBased UHG_minigame_checkIfAIInputIs_Algorithmic_Or_ControllerBased
#include "game/UnknownHomes_Game.h"
#undef minigame_checkIfAIInputIs_Algorithmic_Or_ControllerBased
#include "static/GameSettings.h"
#include "game/auto_00_000AC9F8_text.h" // PauseMenuState lbl_3_common_bss_34C90
#include "main/file_80069BDC.h"         // StatInput, gChallengeState
#include "main/file_800639BC.h"         // CharSelectLayout lbl_803616CC, CharSelectState lbl_8034E9A0
#include "main/file_80011640.h"         // CharMgr lbl_8036E548
#include "main/file_8001FE00.h"         // SceneFade lbl_8037169C
#include "main/file_80008E00.h"         // lbl_80366158
#include "main/file_8004C5F8.h"         // RosterSelect lbl_803C6028, ConfirmDialog lbl_803C5F74
#include "game/auto_00_001658F0_text.h" // StarChanceState

extern StarChanceState lbl_3_common_bss_37400;
extern ARAMLoaderView lbl_803C6CF8;
extern HudFlagsView lbl_3_common_bss_32724;
extern RandSeedView lbl_3_data_228;

// Character id -> its stats in the character-select roster ([id / 9][id % 9]).
#define CHAR_STATS(id) (&lbl_8034E9A0.roster[0][0] + (id))
extern GameScores g_Scores;

// .data 0x21268..0x222A8: this TU's tables, many of them read by the minigame units
// (rep_31F0 .. rep_37A8) as globals. Element types follow their readers.
u8 lbl_3_data_21268[8] = {1, 2, 4, 5, 3, 6, 7, 0};
u8 lbl_3_data_21270[8] = {1, 4, 1, 4, 0, 3, 1, 0};
u8 lbl_3_data_21278[4] = {30, 60, 0, 0};
u8 lbl_3_data_2127C[40] = {0, 1, 2, 3, 0, 0, 1, 2, 2, 0, 0, 1, 2, 2, 0, 0, 1, 2, 2, 0, 0, 1, 2, 2, 0, 0, 1, 2, 2, 0, 0, 1, 2, 2, 0, 2, 2, 2, 2, 0};
u8 lbl_3_data_212A4[17][6] = {{0, 1, 4, 5, 2, 3}, {13, 12, 17, 21, 24, 28}, {6, 5, 7, 8, 38, 11}, {0, 1, 2, 4, 9, 10}, {0, 1, 2, 4, 9, 10}, {41, 0, 5, 14, 10, 27}, {20, 15, 3, 1, 48, 11}, {7, 8, 13, 6, 18, 39}, {7, 8, 13, 6, 18, 39}, {17, 16, 8, 19, 28, 40}, {6, 38, 21, 14, 7, 5}, {0, 1, 2, 4, 9, 10}, {0, 1, 2, 4, 9, 10}, {40, 17, 16, 14, 3, 10}, {12, 37, 27, 20, 33, 11}, {41, 2, 38, 9, 19, 48}, {41, 2, 38, 9, 19, 48}};
f32 lbl_3_data_2130C[28] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
s16 lbl_3_data_2137C[2] = {120, 60};
f32 lbl_3_data_21380[3] = {0.0f, 1.6f, 18.0f};
f32 lbl_3_data_2138C[4] = {0.005f, 0.005f, 0.005f, 0.005f};
u8 lbl_3_data_2139C[8] = {120, 140, 160, 170, 190, 0, 0, 0};
u8 lbl_3_data_213A4[48] = {0, 100, 0, 0, 0, 0, 50, 50, 0, 0, 0, 40, 0, 60, 0, 0, 30, 10, 20, 40, 10, 20, 0, 20, 50, 0, 0, 0, 65, 0, 0, 10, 25, 30, 40, 0, 15, 15, 20, 20, 20, 20, 20, 0, 0, 0, 50, 50};
u8 lbl_3_data_213D4[8] = {0, 0, 1, 2, 2, 3, 0, 0};
u8 lbl_3_data_213DC[4] = {0, 2, 4, 0};
u8 lbl_3_data_213E0[4] = {25, 55, 15, 30};
u8 lbl_3_data_213E4[8] = {3, 3, 3, 3, 3, 3, 0, 0};
s16 lbl_3_data_213EC[10] = {50, 60, 70, 80, 90, 100, 25, 200, 15, 0};
s16 lbl_3_data_21400[8] = {10, 1000, 10, 1500, 10, 2000, 10, 0};
s16 lbl_3_data_21410[6] = {250, 260, 270, 280, 300, 0};
s16 lbl_3_data_2141C[14] = {0, 150, 270, 290, 280, 300, 290, 320, 310, 340, 330, 360, 350, 380};
f32 lbl_3_data_21438[4] = {0.001f, 170.0f, 1.5f, 130.0f};
s16 lbl_3_data_21448[10] = {90, 30, 160, 90, 90, 128, 64, 10, 30, 90};
u16 lbl_3_data_2145C[2] = {20, 70};
u8 lbl_3_data_21460[8] = {0, 1, 2, 4, 3, 5, 3, 0};
u8 lbl_3_data_21468[24] = {60, 30, 10, 0, 0, 0, 30, 40, 10, 0, 10, 10, 20, 20, 20, 0, 20, 20, 15, 10, 10, 0, 25, 40};
u8 lbl_3_data_21480[8] = {20, 20, 20, 0, 20, 20, 0, 0};
u8 lbl_3_data_21488[24] = {0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0};
s8 lbl_3_data_214A0[24] = {0, 0, -6, 4, 0, 0, 0, 0, -4, 3, 0, 0, 0, 0, -3, 2, 0, 0, 0, 0, -3, 1, 0, 0};
s8 lbl_3_data_214B8[12] = {15, -10, 10, 10, -10, 10, 5, -10, 5, 5, -10, 5};
s8 lbl_3_data_214C4[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
s8 lbl_3_data_214D0[12] = {22, -20, 20, 15, -20, 20, 10, -20, 10, 5, -20, 10};
s8 lbl_3_data_214DC[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
s8 lbl_3_data_214E8[12] = {35, -30, 30, 30, -30, 30, 20, -30, 20, 15, -30, 20};
s8 lbl_3_data_214F4[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
VecXZ lbl_3_data_21500[4] = {{0.0f, 0.0f}, {-5.0f, 25.0f}, {5.0f, 25.0f}, {10.0f, 25.0f}};
f32 lbl_3_data_21520[42] = {0.0f, 0.0f, 10.2f, 0.0f, 0.0f, 8.5f, 0.0f, 0.0f, 6.8f, 0.0f, 0.0f, 5.1f, 0.0f, 0.0f, 3.4f, 0.0f, 0.0f, 1.7f, 0.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0.0f, 0.0f, 23.0f, 0.0f, 0.0f, 26.0f, 0.0f, 0.0f, 29.0f, 0.0f, 0.0f, 32.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 38.0f, 0.0f};
f32 lbl_3_data_215C8[6] = {0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.2f};
Vec lbl_3_data_215E0[7] = {{0.0f, 1.5f, 10.2f}, {0.0f, 1.5f, 8.5f}, {0.0f, 1.5f, 6.8f}, {0.0f, 1.5f, 5.1f}, {0.0f, 1.5f, 3.4f}, {0.0f, 1.5f, 1.7f}, {0.0f, 1.5f, 0.0f}};
f32 lbl_3_data_21634[5] = {0.2f, 0.1f, 0.0044f, 0.5f, 0.3f};
u32 lbl_3_data_21648[3] = {1, 2, 5};
s16 lbl_3_data_21654[12] = {30, 123, 150, 10, 17, 22, 17, 5, 10, 15, 100, 50};
u8 lbl_3_data_2166C[5] = {3, 3, 3, 3, 3};
u8 lbl_3_data_21671 = 3;
s16 lbl_3_data_21672 = 1;
f32 lbl_3_data_21674[2] = {0.1f, 0.1f};
s16 lbl_3_data_2167C[6] = {90, 60, 90, 30, 60, 0};
f32 lbl_3_data_21688[3] = {0.1f, 0.3f, 1.0f};
u8 lbl_3_data_21694[28] = {90, 95, 100, 100, 100, 100, 80, 75, 80, 85, 85, 85, 90, 65, 55, 60, 65, 65, 65, 70, 40, 55, 60, 65, 65, 65, 70, 40};
u8 lbl_3_data_216B0[8] = {216, 40, 226, 30, 236, 20, 241, 15};
u8 lbl_3_data_216B8[4] = {80, 60, 40, 30};
f32 lbl_3_data_216BC[45] = {-8.4f, 0.0f, 25.0f, -8.4f, 4.5f, 25.0f, -8.4f, 9.0f, 25.0f, -4.2f, 0.0f, 25.0f, -4.2f, 4.5f, 25.0f, -4.2f, 9.0f, 25.0f, 0.0f, 0.0f, 25.0f, 0.0f, 4.5f, 25.0f, 0.0f, 9.0f, 25.0f, 4.2f, 0.0f, 25.0f, 4.2f, 4.5f, 25.0f, 4.2f, 9.0f, 25.0f, 8.4f, 0.0f, 25.0f, 8.4f, 4.5f, 25.0f, 8.4f, 9.0f, 25.0f};
f32 lbl_3_data_21770[6] = {20.0f, -1.0f, 2.1f, 4.5f, 0.2f, 0.1f};
s16 lbl_3_data_21788[4] = {3, 5, 10, 0};
s16 lbl_3_data_21790[4] = {1000, 1500, 2000, 0};
u8 lbl_3_data_21798[12] = {15, 15, 15, 15, 5, 3, 3, 0, 63, 0, 0, 0};
s16 lbl_3_data_217A4[12] = {20, 30, 80, 180, 45, 4, 20, 30, 120, 130, 90, 0};
s8 lbl_3_data_217BC[8] = {1, 0, -1, -3, -4, 0, 0, 0};
u8 lbl_3_data_217C4[4] = {1, 1, 1, 1};
s8 lbl_3_data_217C8[4] = {15, 20, 30, 50};
s8 lbl_3_data_217CC[4] = {70, 55, 45, 30};
s8 lbl_3_data_217D0[4] = {3, 2, 2, 1};
s8 lbl_3_data_217D4[4] = {30, 25, 15, 15};
f32 lbl_3_data_217D8[8] = {1.5f, 0.0f, 0.5f, 0.0f, -0.5f, 0.0f, -1.5f, 0.0f};
f32 lbl_3_data_217F8[3] = {0.0f, 0.0f, 18.5f};
u8 lbl_3_data_21804[92] = {0, 50, 0, 90, 0, 110, 0, 150, 0, 150, 0, 150, 0, 150, 0, 150, 255, 255, 0, 70, 0, 110, 0, 120, 0, 140, 0, 140, 0, 140, 0, 140, 0, 140, 255, 255, 0, 100, 0, 100, 0, 100, 0, 140, 0, 140, 0, 140, 0, 140, 0, 140, 255, 255, 0, 100, 0, 100, 0, 100, 0, 140, 0, 140, 0, 140, 0, 140, 0, 140, 255, 255, 0, 100, 0, 100, 0, 100, 0, 140, 0, 140, 0, 140, 0, 140, 0, 140, 255, 255, 0, 0};
u8 lbl_3_data_21860[20] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};
u8 lbl_3_data_21874[8] = {60, 60, 60, 90, 60, 0, 0, 0};
u8 lbl_3_data_2187C[8] = {95, 5, 90, 10, 80, 20, 0, 0};
u8 lbl_3_data_21884[8] = {1, 1, 5, 1, 1, 10, 0, 0};
f32 lbl_3_data_2188C[7] = {0.1f, 0.3f, 0.1f, 0.3f, -0.01f, 0.7f, 0.5f};
s16 lbl_3_data_218A8[2] = {120, 0};
u8 lbl_3_data_218AC[16] = {180, 160, 150, 160, 140, 140, 130, 110, 100, 130, 120, 110, 150, 130, 110, 0};
f32 lbl_3_data_218BC[18] = {4.0f, 0.3f, 0.07f, 0.3f, 0.2f, 0.2f, 0.04f, 0.5f, 0.05f, 0.05f, 0.1f, 0.1f, 15.0f, 30.0f, 0.1f, 0.2f, 0.04f, 1.8f};
s16 lbl_3_data_21904[12] = {90, 120, 60, 90, 180, 10, 20, 30, 50, 120, 10, 0};
f32 lbl_3_data_2191C[2] = {0.85f, 2.0f};
s16 lbl_3_data_21924[4] = {545, 300, 180, 0};
u8 lbl_3_data_2192C[8] = {30, 40, 10, 20, 5, 10, 5, 10};
f32 lbl_3_data_21934[4] = {0.7f, 0.6f, 0.5f, 0.4f};
u8 lbl_3_data_21944[8] = {30, 40, 20, 30, 15, 20, 10, 15};
u8 lbl_3_data_2194C[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
u8 lbl_3_data_2195C[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
u8 lbl_3_data_2196C[8] = {70, 80, 50, 60, 20, 30, 10, 20};
u8 lbl_3_data_21974[8] = {80, 90, 60, 70, 30, 40, 20, 30};
s8 lbl_3_data_2197C[4] = {10, 20, 30, 30};
s8 lbl_3_data_21980[4] = {4, 5, 6, 7};
u8 lbl_3_data_21984[8] = {60, 60, 60, 90, 60, 0, 0, 0};
f32 lbl_3_data_2198C[8] = {0.0f, 10.0f, -10.0f, 20.0f, 10.0f, 20.0f, 0.0f, 30.0f};
f32 lbl_3_data_219AC[3] = {0.0f, 4.0f, 20.0f};
f32 lbl_3_data_219B8[19] = {0.28f, 0.3f, 0.05f, 0.18f, 0.03f, 0.25f, 0.55f, 0.5f, 0.5f, 0.05f, 0.15f, -0.01f, 0.5f, 0.5f, 0.45f, 0.3f, 0.05f, 0.08f, 0.25f};
s16 lbl_3_data_21A04[8] = {15, 30, 1, 420, 128, 1, 10, 10};
f32 lbl_3_data_21A14[7] = {14.0f, 15.0f, 10.0f, 13.0f, 1.4f, 1.5f, 1.05f};
s16 lbl_3_data_21A30[6] = {480, 420, 600, 90, 100, 10};
s16 lbl_3_data_21A3C[4] = {500, 505, -1, -1};
s16 lbl_3_data_21A44[2] = {2, 0};
f32 lbl_3_data_21A48[3] = {0.0f, 0.5f, 20.0f};
f32 lbl_3_data_21A54[3] = {2.0f, 13.0f, 0.4f};
s16 lbl_3_data_21A60[2] = {60, 10};
f32 lbl_3_data_21A64[9] = {30.0f, 1.5f, 0.4f, 0.7f, 50.0f, 0.5f, 60.0f, 120.0f, 300.0f};
s16 lbl_3_data_21A88[4] = {2, 3, 4, 4};
s16 lbl_3_data_21A90[32] = {3, 5, 3, 5, 2, 5, 2, 5, 3, 5, 2, 5, 2, 4, 2, 4, 3, 5, 2, 4, 1, 3, 1, 3, 3, 5, 2, 4, 1, 3, 1, 3};
#ifdef TARGET_PC
s16 lbl_3_data_21AD0[16] = {4, 4, 3, 3, 4, 3, 2, 2, 4, 3, 2, 1, 4, 3, 2, 1}; // BE s16[4][4]
#else
u8 lbl_3_data_21AD0[32] = {0, 4, 0, 4, 0, 3, 0, 3, 0, 4, 0, 3, 0, 2, 0, 2, 0, 4, 0, 3, 0, 2, 0, 1, 0, 4, 0, 3, 0, 2, 0, 1};
#endif
s16 lbl_3_data_21AF0[2] = {20, 0};
f32 lbl_3_data_21AF4 = 0.2f;
f32 lbl_3_data_21AF8[6] = {0.3f, 0.15f, -0.01f, 0.85f, 1.5f, 0.5f};
s16 lbl_3_data_21B10[3] = {60, 300, 300};
u8 lbl_3_data_21B16 = 80;
f32 lbl_3_data_21B18[2] = {0.1f, 0.95f};
s16 lbl_3_data_21B20[4] = {90, 120, 180, 10};
f32 lbl_3_data_21B28[4] = {1.0f, 1.2f, 1.3f, 1.3f};
f32 lbl_3_data_21B38[4] = {3.0f, 4.0f, 5.0f, 6.0f};
f32 lbl_3_data_21B48[4] = {2.0f, 3.0f, 5.0f, 6.0f};
f32 lbl_3_data_21B58[4] = {2.0f, 3.0f, 4.0f, 5.0f};
f32 lbl_3_data_21B68[4] = {3.0f, 4.0f, 6.0f, 7.0f};
f32 lbl_3_data_21B78[4] = {3.0f, 4.0f, 6.0f, 7.0f};
s8 lbl_3_data_21B88[4] = {30, 20, 10, 5};
s16 lbl_3_data_21B8C[4] = {15, 10, 9, 8};
f32 lbl_3_data_21B94[12] = {-7.5f, 0.0f, 0.0f, -2.5f, 0.0f, 0.0f, 2.5f, 0.0f, 0.0f, 7.5f, 0.0f, 0.0f};
f32 lbl_3_data_21BC4[86] = {14.0f, 0.0f, 18.0f, 14.0f, 6.0f, 18.0f, 10.0f, 5.0f, 15.0f, 14.0f, 7.0f, 18.0f, 0.0f, 0.0f, 30.0f, 0.0f, 6.0f, 30.0f, 0.0f, 5.0f, 25.0f, 0.0f, 7.0f, 30.0f, -14.0f, 0.0f, 18.0f, -14.0f, 6.0f, 18.0f, -10.0f, 5.0f, 15.0f, -14.0f, 7.0f, 18.0f, 14.0f, 0.0f, 18.0f, 14.0f, 6.5f, 18.0f, 13.5f, 7.5f, 17.5f, 14.0f, 10.0f, 18.0f, 0.0f, 0.0f, 30.0f, 0.0f, 6.5f, 30.0f, 0.0f, 7.5f, 25.0f, 0.0f, 10.0f, 30.0f, -14.0f, 0.0f, 18.0f, -14.0f, 6.5f, 18.0f, -13.5f, 7.5f, 17.5f, -14.0f, 10.0f, 18.0f, 0.0f, 0.0f, -10.0f, 0.0f, 0.0f, -10.0f, 0.0f, 0.0f, -10.0f, 0.0f, 0.0f, -10.0f, 1.5f, 1.75f};
f32 lbl_3_data_21D1C[4] = {0.35f, 1.0f, 0.35f, 1.0f};
f32 lbl_3_data_21D2C[2] = {0.0f, 1.0f};
Vec lbl_3_data_21D34[4][3] = {{{-7.5f, 1.0f, -2.0f}, {-7.5f, 0.5f, -4.0f}, {-7.5f, 0.0f, -6.0f}}, {{-2.5f, 1.0f, -2.0f}, {-2.5f, 0.5f, -4.0f}, {-2.5f, 0.0f, -6.0f}}, {{2.5f, 1.0f, -2.0f}, {2.5f, 0.5f, -4.0f}, {2.5f, 0.0f, -6.0f}}, {{7.5f, 1.0f, -2.0f}, {7.5f, 0.5f, -4.0f}, {7.5f, 0.0f, -6.0f}}}; // held-object offsets per home slot (rep_37A8)
s16 lbl_3_data_21DC4[2] = {30, 45};
s16 lbl_3_data_21DC8[30] = {20, 30, 20, 50, 60, 50, 20, 30, 20, 50, 60, 50, 20, 30, 20, 50, 60, 50, 40, 60, 40, 70, 90, 70, 20, 30, 20, 50, 60, 50};
s16 lbl_3_data_21E04[2] = {180, 240};
u8 lbl_3_data_21E08[8] = {60, 60, 60, 90, 60, 0, 0, 0};
u8 lbl_3_data_21E10[8] = {5, 5, 5, 5, 30, 40, 0, 0};
u8 lbl_3_data_21E18[4] = {1, 1, 2, 2};
u8 lbl_3_data_21E1C[4] = {45, 30, 0, 0};
s8 lbl_3_data_21E20[4] = {70, 20, 10, 0};
f32 lbl_3_data_21E24[17] = {0.5f, 2.0f, 0.25f, 1.0f, 0.75f, 1.0f, 0.75f, 1.0f, 0.3f, 0.3f, 0.2f, -0.01f, 0.99f, 0.75f, 1.0f, 3.0f, 0.01f};
s16 lbl_3_data_21E68[26] = {90, 10, 30, 15, 5, 30, 30, 30, 40, 15, 180, 30, 115, 15, 30, 60, 10, 90, 30, 0, 150, 50, 80, 60, 3, 0};
u8 lbl_3_data_21E9C[16] = {0, 10, 20, 70, 15, 15, 30, 40, 40, 20, 20, 20, 50, 20, 20, 20};
s16 lbl_3_data_21EAC[8] = {30, 60, 20, 35, 8, 15, 8, 15};
s8 lbl_3_data_21EBC[4] = {70, 40, 20, 15};
s8 lbl_3_data_21EC0[4] = {30, 50, 70, 85};
u8 lbl_3_data_21EC4[4] = {10, 6, 3, 0};
u8 lbl_3_data_21EC8[992] = {0, 0, 4, 11, 64, 19, 118, 76, 26, 99, 80, 0, 0, 7, 219, 72, 0, 0, 4, 11, 64, 3, 227, 220, 26, 107, 48, 0, 0, 2, 20, 32, 0, 0, 4, 11, 64, 2, 236, 16, 26, 109, 72, 0, 0, 1, 49, 8, 0, 0, 4, 11, 64, 14, 114, 192, 26, 110, 128, 0, 0, 6, 7, 104, 0, 0, 4, 11, 64, 4, 148, 4, 26, 116, 136, 0, 0, 2, 14, 52, 0, 0, 4, 11, 64, 7, 106, 224, 24, 237, 112, 0, 0, 3, 107, 200, 0, 0, 4, 11, 64, 16, 253, 112, 26, 118, 152, 0, 0, 5, 226, 132, 0, 0, 4, 11, 64, 13, 183, 56, 26, 124, 128, 0, 0, 4, 154, 180, 0, 0, 4, 11, 64, 14, 152, 100, 26, 129, 32, 0, 0, 5, 157, 192, 0, 0, 4, 11, 64, 11, 119, 24, 26, 134, 192, 0, 0, 5, 2, 136, 0, 0, 4, 11, 64, 13, 135, 252, 26, 139, 200, 0, 0, 4, 123, 196, 0, 0, 4, 11, 64, 13, 100, 60, 26, 144, 72, 0, 0, 4, 227, 172, 0, 0, 4, 11, 64, 13, 92, 124, 26, 149, 48, 0, 0, 4, 141, 156, 0, 0, 4, 11, 64, 11, 118, 124, 26, 153, 192, 0, 0, 4, 117, 24, 0, 0, 4, 11, 64, 4, 65, 248, 26, 158, 56, 0, 0, 1, 170, 132, 0, 0, 4, 11, 64, 16, 101, 104, 26, 159, 232, 0, 0, 6, 140, 16, 0, 0, 4, 11, 64, 16, 229, 160, 14, 151, 168, 0, 0, 9, 188, 172, 0, 0, 4, 11, 64, 1, 105, 128, 14, 161, 104, 0, 0, 0, 214, 196, 0, 0, 4, 11, 64, 1, 105, 128, 14, 162, 64, 0, 0, 0, 201, 68, 0, 0, 4, 11, 64, 1, 105, 128, 14, 163, 16, 0, 0, 0, 231, 0, 0, 0, 4, 11, 64, 1, 105, 128, 14, 163, 248, 0, 0, 0, 214, 76, 0, 0, 4, 11, 64, 1, 105, 128, 14, 164, 208, 0, 0, 0, 201, 0, 0, 0, 4, 11, 64, 1, 105, 128, 14, 165, 160, 0, 0, 0, 207, 252, 0, 0, 4, 11, 64, 1, 105, 128, 14, 166, 112, 0, 0, 0, 215, 32, 0, 0, 4, 11, 64, 1, 105, 128, 14, 167, 72, 0, 0, 0, 214, 204, 0, 0, 4, 11, 64, 1, 105, 128, 14, 168, 32, 0, 0, 0, 210, 28, 0, 0, 4, 11, 64, 1, 105, 128, 14, 168, 248, 0, 0, 0, 208, 188, 0, 0, 4, 11, 64, 1, 105, 128, 14, 169, 208, 0, 0, 0, 181, 68, 0, 0, 4, 11, 64, 1, 105, 128, 14, 170, 136, 0, 0, 0, 196, 248, 0, 0, 4, 11, 64, 10, 223, 252, 24, 174, 232, 0, 0, 4, 186, 176, 0, 0, 4, 11, 64, 55, 207, 92, 24, 179, 168, 0, 0, 32, 138, 240, 0, 0, 4, 11, 64, 0, 168, 32, 24, 237, 56, 0, 0, 0, 55, 88, 0, 0, 4, 11, 64, 17, 236, 36, 24, 240, 224, 0, 0, 13, 136, 24, 0, 0, 4, 11, 64, 1, 147, 232, 25, 27, 136, 0, 0, 0, 137, 216, 0, 0, 4, 11, 64, 6, 200, 80, 6, 201, 96, 0, 0, 2, 200, 132, 0, 0, 4, 11, 64, 5, 177, 120, 6, 204, 48, 0, 0, 3, 85, 92, 0, 0, 4, 11, 64, 30, 177, 116, 24, 212, 56, 0, 0, 15, 178, 32, 0, 0, 4, 11, 64, 1, 237, 96, 26, 166, 120, 0, 0, 0, 207, 240, 0, 0, 4, 11, 64, 0, 191, 48, 26, 167, 72, 0, 0, 0, 38, 224, 0, 0, 4, 11, 64, 0, 52, 152, 26, 167, 112, 0, 0, 0, 14, 40, 0, 0, 4, 11, 64, 0, 189, 224, 26, 167, 128, 0, 0, 0, 36, 244, 0, 0, 4, 11, 64, 0, 96, 136, 26, 167, 168, 0, 0, 0, 18, 144, 0, 0, 4, 11, 64, 0, 73, 240, 26, 167, 192, 0, 0, 0, 24, 244, 0, 0, 4, 11, 64, 0, 94, 204, 26, 167, 224, 0, 0, 0, 29, 56, 0, 0, 4, 11, 64, 0, 38, 112, 26, 168, 0, 0, 0, 0, 11, 232, 0, 0, 0, 0, 0, 2, 130, 64, 26, 168, 16, 0, 0, 2, 130, 64, 0, 0, 0, 0, 0, 2, 130, 64, 26, 170, 152, 0, 0, 2, 130, 64, 0, 0, 0, 0, 0, 2, 130, 64, 26, 173, 32, 0, 0, 2, 130, 64, 0, 0, 0, 0, 0, 2, 130, 64, 26, 175, 168, 0, 0, 2, 130, 64, 0, 0, 0, 0, 0, 2, 130, 64, 26, 178, 48, 0, 0, 2, 130, 64, 0, 0, 0, 0, 0, 2, 130, 64, 26, 180, 184, 0, 0, 2, 130, 64, 0, 0, 0, 0, 0, 2, 130, 64, 26, 183, 64, 0, 0, 2, 130, 64, 0, 0, 0, 0, 0, 2, 130, 64, 26, 185, 200, 0, 0, 2, 130, 64, 0, 0, 0, 0, 0, 2, 130, 64, 26, 188, 80, 0, 0, 2, 130, 64, 0, 0, 0, 0, 0, 2, 130, 64, 26, 190, 216, 0, 0, 2, 130, 64, 0, 0, 0, 0, 0, 2, 130, 64, 26, 193, 96, 0, 0, 2, 130, 64, 0, 0, 0, 0, 0, 2, 130, 64, 26, 195, 232, 0, 0, 2, 130, 64, 0, 0, 0, 0, 0, 2, 130, 64, 26, 198, 112, 0, 0, 2, 130, 64, 0, 0, 0, 0, 0, 2, 130, 64, 26, 200, 248, 0, 0, 2, 130, 64, 0, 0, 0, 0, 0, 2, 130, 64, 26, 203, 128, 0, 0, 2, 130, 64, 0, 0, 0, 0, 0, 2, 130, 64, 26, 206, 8, 0, 0, 2, 130, 64, 0, 0, 0, 0, 0, 2, 130, 64, 26, 208, 144, 0, 0, 2, 130, 64};

extern s32 fn_3_5B380(u16);
extern void fn_8004CC18(void);
extern u8 lbl_3_data_B060[];
extern void fn_800203E0(u8 scene, s8 variant);
extern void fn_3_10C81C(void);
extern void fn_3_E1370(int mode);
extern s32 fn_80016F7C(void);
extern s32 fn_3_90DD8(void);
extern void fn_8003A540(s32);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern void minigamesGXStuff(void);
extern void minigamesSetSomePointers(void);
extern void fn_3_1128EC(void);
extern u8 lbl_3_data_18918[];
extern s16 lbl_3_data_18C48[];
extern void fn_3_10952C(void);
extern void fn_3_5B368(void);
extern s32 fn_3_5B220(s32);
extern void fn_3_10EFAC(void);
extern u8 lbl_3_data_20FDC[];
extern u8 lbl_3_data_18910[];
extern u8 lbl_800E86F0[];
extern void fn_3_10BE7C(void);
extern void fn_80062A74(void);
extern void fn_80062A94(void);
extern void fn_3_10B27C(void);
extern void fn_3_1079C8(u8*, s32);
extern u8 lbl_800E86F0[];
extern void* _OSAllocFromHeap(s32, s32);
extern void* ARAMTransfer(void* instr, void* dest, u8 mode, u32 aramAddr);
extern u32 fn_3_90064(s32 id);
extern void fn_3_5A6D4(s32);
#ifdef TARGET_PC
extern s32 port_career_training_active(void);
#endif
extern void fn_3_5E60(void);
extern void fn_3_B95EC(void);
extern void fn_3_909B0(void);
extern void fn_3_9081C(void);
extern void fn_80035B50(int);
extern void fn_80018B38(void);
extern void fn_80011BE4(s32);
extern void* memset(void*, int, size_t);
extern void* memcpy(void*, const void*, size_t);
extern void* memcpy(void*, const void*, size_t);
extern void fn_3_9DC18(void*, s32, s32);
extern void manageStadiumLoading(void);
extern void* fn_800B0A5C_insertQueue(void*, s32);
extern void fn_3_9E078(s32*, s32, s32);
extern void changeScene(s32, s32);
extern void fn_3_1128E8(void);
extern void fn_3_1160B8(void);
extern void fn_3_1323CC(void);
extern void fn_3_141A2C(void);
extern void fn_3_1471C0(void);
extern void fn_3_13C464(void);
extern s32 fn_3_6C938(s32, s32);
extern u8 lbl_3_data_188FC[];
extern u8 lbl_3_data_188E8[];
extern u8 lbl_800EFBA4[];
extern u8 sndFXStartEx(s32, u8, u8, u8);
extern void fn_3_5B408(void);

#pragma dont_inline on

// fn_3_106EB0, size:0x24
void fn_3_106EB0(void) {
    fn_3_90064(0x30B);
}

// fn_3_107078, size:0x2C
void fn_3_107078(void) {
    if (g_Minigame.minigameControlStruct[0]._1C[g_Minigame._1908] == 1) {
        g_Minigame._1A3F = 1;
    }
}

// fn_3_10F550, size:0x14
void fn_3_10F550(s8 a, s16 b) {
    g_Minigame._1A41 = a;
    g_Minigame.someGraphicFrameCountdown = b;
}

// fn_3_106DFC, size:0x54
void fn_3_106DFC(void) {
    g_Camera._AB0 = _OSAllocFromHeap(4, 0x8000);
    g_Camera._146C = _OSAllocFromHeap(4, 0x8000);
}

// fn_3_106E50, size:0x60
s32 fn_3_106E50(void) {
    if ((s32)lbl_803C6CF8.idle == 1) {
        g_Camera._1B4 = ARAMTransfer(lbl_3_data_20FDC, 0, 0, 0);
#ifdef TARGET_PC
        port_forget_camera_anim_list(); // a new copy to byte-swap (fn_3_FC448)
#endif
        return 1;
    }
    return 0;
}

// fn_3_107988, size:0x40
s32 fn_3_107988(u32 v) {
    u32 i;
    u32 n = g_Minigame._1E2A - 1;
    for (i = 0; i < n; i++) {
        if (g_Minigame._1E1C[i] == v) {
            return 1;
        }
    }
    return 0;
}

// fn_3_109D88, size:0x58
RankEnt* fn_3_109D88(void) {
    if (g_Minigame._1A3C != 0) {
        return (RankEnt*)lbl_803616CC.tail;
    }
    if (g_Minigame.GameMode_MiniGame != 0) {
        return (RankEnt*)lbl_803616CC.groups[g_Minigame.GameMode_MiniGame - 1];
    }
    return (RankEnt*)lbl_803616CC.head;
}

// fn_3_107D70, size:0x44
u8 fn_3_107D70(s8 i) {
    if (g_d_GameSettings.GameModeSelected == 7 && i >= 0 && i < 4) {
        return g_Minigame._1DC8[i];
    }
    return 0;
}

// fn_3_107DB4, size:0x44
u8 fn_3_107DB4(s8 i) {
    if (g_d_GameSettings.GameModeSelected == 7 && i >= 0 && i < 4) {
        return g_Minigame._1DC4[i];
    }
    return 0;
}

// fn_3_107DF8, size:0x44
u8 fn_3_107DF8(s8 i) {
    if (g_d_GameSettings.GameModeSelected == 7 && i >= 0 && i < 4) {
        return g_Minigame._1DC0[i];
    }
    return 0;
}

// minigame_checkIfAIInputIs_Algorithmic_Or_ControllerBased, size:0x44
u8 minigame_checkIfAIInputIs_Algorithmic_Or_ControllerBased(s8 i) {
    if (g_d_GameSettings.GameModeSelected == 7 && i >= 0 && i < 4) {
        return g_Minigame._1DBC[i];
    }
    return 0;
}

// fn_3_107C40, size:0x48
s32 fn_3_107C40(void) {
    u32 n = g_Minigame.miniGameNumberOfParticipants;
    s16 v = g_Minigame.miniGameCurrentPoints[0];
    u32 i;
    for (i = 1; i < n; i++) {
        if (g_Minigame.miniGameCurrentPoints[i] != v) {
            return 0;
        }
    }
    return 1;
}

// fn_3_107C88, size:0x48
s32 fn_3_107C88(void) {
    u32 n = g_Minigame.miniGameNumberOfParticipants;
    s16 v = g_Minigame.minigamePoints_current_Latest[0].current;
    u32 i;
    for (i = 1; i < n; i++) {
        if (g_Minigame.minigamePoints_current_Latest[i].current != v) {
            return 0;
        }
    }
    return 1;
}

// fn_3_107CD0, size:0x64
u8 fn_3_107CD0(void) {
    u8 arr[4];
    u8* p = arr;
    u32 i = 0;
    do {
        *p = i;
        i++;
        p++;
    } while (i < g_Minigame.miniGameNumberOfParticipants);
    fn_800246D4(fn_3_107D34, arr, arr, 1, g_Minigame.miniGameNumberOfParticipants);
    return arr[0];
}

// fn_3_1078F8, size:0x90
void fn_3_1078F8(void) {
    u32 i;
    memset(&g_Minigame._1E04, 0, 0x28);
    g_Minigame._1A3D = 0;
    g_Minigame._1A3F = 0;
    lbl_8036E548._307E = 0;
    i = 0;
    do {
        g_Minigame._1E1C[i] = i + 1;
        i++;
    } while (i < 6);
    fn_3_9DC18(g_Minigame._1E1C, 6, 0);
    fn_3_5A6D4(0x28);
}

// fn_3_10AD48, size:0xD0
void fn_3_10AD48(void) {
    s32 arr[4];
    s32 i;
    for (i = 0; i < 4; i++) {
        arr[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        if (g_Minigame.minigameControlStruct[0].characterIndex[i] >= 0) {
            arr[i] = i;
        }
    }
    fn_3_9E078(arr, g_Minigame.miniGameNumberOfParticipants, 0);
    for (i = 0; i < 4; i++) {
        g_Minigame.minigameControlStruct[0].turnOrder[i] = arr[i];
    }
}

// fn_3_10AE18, size:0xD8
void fn_3_10AE18(void) {
    s32 arr[4];
    s32 i;
    for (i = 0; i < 4; i++) {
        arr[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        if (g_Minigame.minigameControlStruct[0].characterIndex[i] >= 0) {
            arr[i] = i;
        }
    }
    fn_3_9E078(arr, g_Minigame.miniGameNumberOfParticipants, 0);
    for (i = 0; i < 4; i++) {
        g_Minigame.minigameControlStruct[0].turnOrder[i] = arr[i];
    }
    fn_3_5A6D4(0x1A);
}

// fn_3_10768C, size:0xF8
void fn_3_10768C(void) {
    switch (g_GameLogic._125) {
    case 0:
        g_Minigame.GameMode_MiniGame = g_Minigame._1E1C[g_Minigame._1E2A++];
        changeScene(1, 6);
        g_GameLogic._125 = 1;
        break;
    case 1:
        if (((MinigameTask*)MG_TASK_PTR)->_1A != 0) {
            changeScene(3, 6);
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        if (lbl_8037169C._13 != 0) {
            g_GameLogic._125 = 3;
        }
        break;
    case 3:
        g_GameLogic._125 = 4;
        break;
    case 4:
        fn_3_5A6D4(0x21);
        break;
    }
}

// fn_3_107B9C, size:0x34
s32 fn_3_107B9C(void* a, void* b) {
    if (g_Minigame._1E26[*(u8*)b] != g_Minigame._1E26[*(u8*)a]) {
        return g_Minigame._1E26[*(u8*)b] - g_Minigame._1E26[*(u8*)a];
    }
    return *(u8*)a - *(u8*)b;
}

// fn_3_107BD0, size:0x34
s32 fn_3_107BD0(void* a, void* b) {
    if (g_Minigame._1E22[*(u8*)b] != g_Minigame._1E22[*(u8*)a]) {
        return g_Minigame._1E22[*(u8*)b] - g_Minigame._1E22[*(u8*)a];
    }
    return *(u8*)a - *(u8*)b;
}

// fn_3_107C04, size:0x3C
s32 fn_3_107C04(void* a, void* b) {
    if (g_Minigame.miniGameCurrentPoints[*(u8*)b] != g_Minigame.miniGameCurrentPoints[*(u8*)a]) {
        return g_Minigame.miniGameCurrentPoints[*(u8*)b] - g_Minigame.miniGameCurrentPoints[*(u8*)a];
    }
    return *(u8*)a - *(u8*)b;
}

// fn_3_107D34, size:0x3C
s32 fn_3_107D34(void* a, void* b) {
    if (g_Minigame.minigamePoints_current_Latest[*(u8*)b].current != g_Minigame.minigamePoints_current_Latest[*(u8*)a].current) {
        return g_Minigame.minigamePoints_current_Latest[*(u8*)b].current - g_Minigame.minigamePoints_current_Latest[*(u8*)a].current;
    }
    return *(u8*)a - *(u8*)b;
}

// fn_3_10F5BC, size:0xC8
void fn_3_10F5BC(void) {
    u32 t;
    if (g_Minigame._1A2C >= 0) {
        lbl_8036E548._307E = 0;
        fn_3_B95EC();
        fn_3_5E60();
    }
    g_Minigame._1A2C = -1;
    t = lbl_3_data_18910[g_Minigame.GameMode_MiniGame];
    lbl_3_data_228._10 = 0;
    g_d_GameSettings.StadiumID = t;
    g_d_GameSettings.miniGameStadiumIndicator = 0;
    if (g_d_GameSettings.StadiumID == 0 || g_d_GameSettings.StadiumID == 4 || g_d_GameSettings.StadiumID == 1 || g_d_GameSettings.StadiumID == 3) {
        g_d_GameSettings.miniGameStadiumIndicator = 1;
    }
    fn_800B0A5C_insertQueue(manageStadiumLoading, 0);
}

// fn_3_107784, size:0x17C
void fn_3_107784(void) {
    switch (g_GameLogic._125) {
    case 0:
        g_GameLogic._125 = g_GameLogic._125 + 1;
        g_Minigame._1A1E = 0;
        if (g_Minigame._1A1C == 0) {
            fn_800B0A5C_insertQueue((void*)fn_80062A94, 1);
        }
        break;
    case 1:
        changeScene(1, 6);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = g_GameLogic._125 + 1;
        break;
    case 2:
        fn_3_10B27C();
        if (g_Minigame._1A1D == 2) {
            g_GameLogic._125 = 5;
        } else if (g_Minigame._1A1D != 0) {
            g_GameLogic._125 = g_GameLogic._125 + 1;
        }
        break;
    case 3:
        changeScene(3, 6);
        if (lbl_8037169C._13 != 0) {
            g_GameLogic._125 = g_GameLogic._125 + 1;
        }
        break;
    case 4:
        fn_80062A74();
        g_Minigame._1A1C = 0;
        fn_3_5A6D4(0x29);
        break;
    case 5:
        changeScene(3, 6);
        if (lbl_8037169C._13 != 0) {
            g_GameLogic._125 = 6;
        }
        break;
    case 6:
        fn_3_5A6D4(0x1E);
        break;
    }
}

// fn_3_10C58C, size:0x218
void fn_3_10C58C(void) {
    s32 i;
    CharacterStats* r;
    g_Minigame.minigameControlStruct[0].characterIndex[0] = -1;
    g_Minigame.minigameControlStruct[0].battingHandedness[0] = 0;
    g_Minigame.minigameControlStruct[0].charID[0] = 0xFF;
    g_Minigame.minigameControlStruct[0].characterIndex[1] = -1;
    g_Minigame.minigameControlStruct[0].battingHandedness[1] = 0;
    g_Minigame.minigameControlStruct[0].charID[1] = 0xFF;
    g_Minigame.minigameControlStruct[0].characterIndex[2] = -1;
    g_Minigame.minigameControlStruct[0].battingHandedness[2] = 0;
    g_Minigame.minigameControlStruct[0].charID[2] = 0xFF;
    g_Minigame.minigameControlStruct[0].characterIndex[3] = -1;
    g_Minigame.minigameControlStruct[0].battingHandedness[3] = 0;
    g_Minigame.minigameControlStruct[0].charID[3] = 0xFF;
    g_Minigame.miniGameNumberOfParticipants = 0;
    g_Minigame._1907 = 0;
    fn_3_10BE7C();
    for (i = 0; i < 4; i++) {
        if (g_Minigame._19DA[i] >= 0) {
            r = &inMemRoster[0][i];
            g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.miniGameNumberOfParticipants] = i;
            g_Minigame.minigameControlStruct[0].battingHandedness[g_Minigame.miniGameNumberOfParticipants] = (u8)g_Minigame._19DA[i];
            if (g_Minigame.minigameControlStruct[0].battingHandedness[g_Minigame.miniGameNumberOfParticipants] == 0) {
                g_Minigame._1907++;
            }
            memcpy(r, CHAR_STATS(g_Minigame._19E8[i]._0), 0xA0);
            if (g_Minigame.minigameControlStruct[0]._08[i] != 0) {
                r->stats.SlapContactSize += lbl_800E86F0[0];
                r->stats.ChargeContactSize += lbl_800E86F0[1];
                r->stats.SlapHitPower += lbl_800E86F0[2];
                r->stats.ChargeHitPower += lbl_800E86F0[3];
                r->stats.BuntingContactSize += lbl_800E86F0[4];
                r->stats.Speed += lbl_800E86F0[5];
                r->stats.ThrowingArm += lbl_800E86F0[6];
                r->stats.CurveBallSpeed += lbl_800E86F0[7];
                r->stats.FastBallSpeed += lbl_800E86F0[8];
                r->stats.cursedBall += lbl_800E86F0[9];
                r->stats.Curve += lbl_800E86F0[0xA];
                r->stats.curveControl += lbl_800E86F0[0xB];
            }
            g_Minigame.minigameControlStruct[0].charID[g_Minigame.miniGameNumberOfParticipants] = r->stats.CharID;
            g_Minigame.miniGameNumberOfParticipants++;
        }
    }
}

// fn_3_10F1D4, size:0x204
void fn_3_10F1D4(void) {
    u8 s = g_GameLogic._125;
    u8 m;
    switch (s) {
    case 0:
        changeScene(6, 6);
        g_GameLogic._125 = g_GameLogic._125 + 1;
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        lbl_8036E548._307E = 0;
        g_Minigame._19E4 = 0;
        break;
    case 1:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x14) {
            g_GameLogic._125 = s + 1;
        }
        break;
    case 2:
        fn_3_10EFAC();
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        break;
    case 3:
        if (lbl_3_common_bss_32724._BB == 0) {
            g_GameLogic._125 = s + 1;
        }
        break;
    case 4:
        m = g_Minigame.GameMode_MiniGame;
        if (m >= 1 && m <= 6) {
            if (g_Minigame._190A != 0) {
                g_Minigame._19E4 = 0;
            } else {
                g_Minigame._19E4 = g_d_GameSettings._14[m - 1];
            }
        }
        fn_3_5A6D4(0x1E);
        break;
    case 5:
        {
        InputStruct* cp = g_Controls;
        cp += lbl_80366158._27;
        switch (fn_3_5B380(cp->newButtonInput)) {
        case 1:
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = g_GameLogic._125 + 1;
            break;
        case 2:
            g_GameLogic._125 = 2;
            break;
        }
        }
        break;
    case 6:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x2D) {
            changeScene(4, 6);
        }
        if (lbl_8037169C._13 != 0) {
            fn_80062A74();
            g_Minigame._1A1C = 0;
            g_GameLogic._125 = g_GameLogic._125 + 1;
        }
        break;
    case 7:
        fn_8004CC18();
        g_GameLogic.framesOfExitingToMenu = 1;
        break;
    }
}

// fn_3_10EFAC, size:0x228
void fn_3_10EFAC(void) {
    InputStruct* c = &g_Controls[lbl_80366158._27];
    u8 t;
    if (lbl_3_common_bss_32724._BB == 0) {
        if (c->newButtonInput & 0x100) {
            t = lbl_3_data_21268[(s8)g_Minigame._19E1];
            if (t == 6 && g_d_GameSettings._12 < 1) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            } else if (t == 7 && g_d_GameSettings._12 < 2) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            } else {
                g_GameLogic._125 = 3;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            }
        } else if (c->newButtonInput & 0x200) {
            fn_3_5B408();
            g_GameLogic._125 = 5;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        } else if (c->_08 & 1) {
            if ((s8)g_Minigame._19E1 != 0) {
                g_Minigame._19E1--;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (c->_08 & 2) {
            if ((s8)g_Minigame._19E1 < 6) {
                g_Minigame._19E1++;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
    g_Minigame.GameMode_MiniGame = lbl_3_data_21268[(s8)g_Minigame._19E1];
    if (g_Minigame.GameMode_MiniGame == 7) {
        g_Minigame._1A3C = 1;
    } else {
        g_Minigame._1A3C = 0;
    }
    lbl_3_common_bss_32724._B9 = g_Minigame._19E1;
}

#pragma dont_inline off

// fn_3_1104A8, size:0x2C
void fn_3_1104A8(void) {
    s8 i = 0;
    do {
        i++;
        g_Minigame._1DBC[i - 1] = 0;
    } while (i < 4);
}

// fn_3_10C7A4, size:0x78
void fn_3_10C7A4(void) {
    s32 i;
    fn_8001CA40(0);
    for (i = 0; i < 4; i++) {
        fn_80011BE4(i);
        g_Minigame._19E8[i]._1 = 0;
        g_Minigame._19E8[i]._2 = -1;
    }
}

// fn_3_10F564, size:0x58
s32 fn_3_10F564(void) {
    if (g_Minigame._1A2C == -1) {
        if (lbl_3_data_228._10 != 0) {
            g_Minigame._1A2C = lbl_3_data_18910[g_Minigame.GameMode_MiniGame];
            return 0;
        }
        return 1;
    }
    return 0;
}

// fn_3_10B200, size:0x7C
void fn_3_10B200(void) {
    if (g_d_GameSettings.GameModeSelected != 6) {
        lbl_8036E548._3078 = 0;
    }
    fn_80035B50(0xD);
    fn_3_B95EC();
    fn_3_5E60();
    fn_80018B38();
    fn_3_909B0();
    fn_3_9081C();
    fn_80035B50(0x11);
    g_Minigame._19DF = 0x1E;
    fn_3_5A6D4(0x1D);
}

// fn_3_10FB74, size:0x70
void fn_3_10FB74(void) {
    u8 s = g_GameLogic._125;
    switch (s) {
    case 0:
        lbl_3_common_bss_32724.loadStep = 0;
        lbl_3_common_bss_34C58._2C = 0;
        g_GameLogic._125 = s + 1;
        break;
    }
    lbl_8036E548._307A = 0;
    fn_3_5A6D4(0x1D);
}

// fn_3_10A01C, size:0x84
void fn_3_10A01C(void) {
    u8 m = g_Minigame.GameMode_MiniGame;
    if (m == 1) {
        fn_3_1128E8();
    } else if (m == 2) {
        fn_3_1160B8();
    } else if (m == 3) {
        fn_3_1323CC();
    } else if (m == 4) {
        fn_3_141A2C();
    } else if (m == 5) {
        fn_3_1471C0();
    } else if (m == 6) {
        fn_3_13C464();
    }
}

// fn_3_10C450, size:0x13C
void fn_3_10C450(s32 a, s32 b) {
    CharacterStats* r = &inMemRoster[0][a];
    memcpy(r, CHAR_STATS(b), 0xA0);
    if (g_Minigame.minigameControlStruct[0]._08[a] != 0) {
        r->stats.SlapContactSize += lbl_800E86F0[0];
        r->stats.ChargeContactSize += lbl_800E86F0[1];
        r->stats.SlapHitPower += lbl_800E86F0[2];
        r->stats.ChargeHitPower += lbl_800E86F0[3];
        r->stats.BuntingContactSize += lbl_800E86F0[4];
        r->stats.Speed += lbl_800E86F0[5];
        r->stats.ThrowingArm += lbl_800E86F0[6];
        r->stats.CurveBallSpeed += lbl_800E86F0[7];
        r->stats.FastBallSpeed += lbl_800E86F0[8];
        r->stats.cursedBall += lbl_800E86F0[9];
        r->stats.Curve += lbl_800E86F0[0xA];
        r->stats.curveControl += lbl_800E86F0[0xB];
    }
}

// fn_3_10754C, size:0x140
void fn_3_10754C(StatInput* dst) {
    u8 buf[8];
    s32 i;
    u32 k;
    fn_8006C398(dst);
    if (g_Minigame._1A3C != 0 && g_Minigame._1908 >= 0 && g_Minigame._1908 < 4) {
        i = 0;
        do {
            dst->vals[i] = g_Minigame._1E10[i];
            i++;
        } while ((u32)i < 6);
        i = 0;
        do {
            dst->order[i] = g_Minigame._1E1C[i];
            i++;
        } while ((u32)i < 6);
        fn_3_1079C8(buf, 1);
        k = 0;
        do {
            if (g_Minigame._1908 == buf[k * 2]) {
                dst->_12 = buf[k * 2 + 1];
            }
            k++;
        } while (k < g_Minigame.miniGameNumberOfParticipants);
        {
        CharacterStats* r = inMemRoster[0];
        dst->_13 = g_Minigame._1E22[g_Minigame._1908];
        dst->_14[0] = r[g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame._1908]].stats.CharID;
        }
    }
}

// fn_3_1070A4, size:0x188
static inline void fn_3_107078_inl(void) {
    if (g_Minigame.minigameControlStruct[0]._1C[g_Minigame._1908] == 1) {
        g_Minigame._1A3F = 1;
    }
}

void fn_3_1070A4(void) {
    u16 t;
    MiniGameStruct* m;
    switch (g_GameLogic._125) {
    case 0:
        m = &g_Minigame;
        m->_1A3D = m->_1907;
        m->_1A3E = 1;
        lbl_3_common_bss_32724._B8 = 0;
        if (m->_1907 == 1 && m->minigameControlStruct[0]._1C[m->_1908] == 1) {
            m->_1A3F = 1;
        }
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 1;
        break;
    case 1:
        changeScene(1, 6);
        t = g_GameLogic.FrameCountOfCurrentAtBat_Copy;
        if (t == lbl_3_data_2137C[1]) {
            lbl_3_common_bss_32724._B8 = 1;
        }
        if (t > 300) {
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        if (fn_3_6C938(1, 0x1100) != 0) {
            g_GameLogic._125 = 6;
        }
        break;
    case 6:
        g_GameLogic._125 = 7;
        break;
    case 7:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x3C) {
            g_GameLogic._125 = 8;
        }
        break;
    case 8:
        lbl_3_common_bss_34C90.state = 0;
        lbl_3_common_bss_34C90.subState = 0;
        if (g_Minigame._19E7 == 1) {
            fn_3_5A6D4(0x24);
        } else {
            fn_3_5A6D4(0x22);
        }
        break;
    }
}

// fn_3_108854, size:0x194
s32 fn_3_108854(void) {
    s32 i;
    s8 c;
    if (g_Minigame.turnOverStatus != 0) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        c = g_Minigame.minigameControlStruct[0].characterIndex[i];
        if (c >= 0 && g_Minigame.minigameControlStruct[0].battingHandedness[i] == 0 && (g_Controls[c].newButtonInput & 0x1000)) {
            goto found;
        }
    }
    return 0;
found:
    g_Minigame.pauseInd = 1;
    lbl_3_common_bss_34C90.team = g_Minigame.minigameControlStruct[0].characterIndex[i];
    lbl_3_common_bss_34C90._0A = 0;
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        lbl_3_common_bss_34C90.menuType = 0x10;
    } else if (g_Minigame._1A3C != 0) {
        lbl_3_common_bss_34C90.menuType = 0xD;
    } else {
        lbl_3_common_bss_34C90.menuType = 9;
    }
    lbl_3_common_bss_34C90.subState = 0;
    lbl_3_common_bss_34C90.cursor = 0;
    return 1;
}

// fn_3_1079C8, size:0x1D4
void fn_3_1079C8(u8* out, s32 mode) {
    u8 order[4];
    s16 vals[4];
    u32 i;

    i = 0;
    do {
        order[i] = i;
        i++;
    } while (i < g_Minigame.miniGameNumberOfParticipants);
    switch (mode) {
    case 0:
    default:
        fn_800246D4(fn_3_107C04, order, order, 1, g_Minigame.miniGameNumberOfParticipants);
        i = 0;
        do {
            vals[i] = g_Minigame.miniGameCurrentPoints[i];
            i++;
        } while (i < g_Minigame.miniGameNumberOfParticipants);
        break;
    case 1:
        fn_800246D4(fn_3_107BD0, order, order, 1, g_Minigame.miniGameNumberOfParticipants);
        i = 0;
        do {
            vals[i] = g_Minigame._1E22[i];
            i++;
        } while (i < g_Minigame.miniGameNumberOfParticipants);
        break;
    case 2:
        fn_800246D4(fn_3_107B9C, order, order, 1, g_Minigame.miniGameNumberOfParticipants);
        i = 0;
        do {
            vals[i] = g_Minigame._1E26[i];
            i++;
        } while (i < g_Minigame.miniGameNumberOfParticipants);
        break;
    }
    out[0] = order[0];
    out[1] = 0;
    for (i = 1; i < g_Minigame.miniGameNumberOfParticipants; i++) {
        out[i * 2] = order[i];
        if (vals[order[i]] == vals[order[i - 1]]) {
            out[i * 2 + 1] = out[i * 2 - 1];
        } else {
            out[i * 2 + 1] = i;
        }
    }
}

// fn_3_109CE8, size:0xA0
static inline RankEnt* fn_3_109D88_inl(void) {
    if (g_Minigame._1A3C != 0) {
        return (RankEnt*)lbl_803616CC.tail;
    }
    if (g_Minigame.GameMode_MiniGame != 0) {
        return (RankEnt*)lbl_803616CC.groups[g_Minigame.GameMode_MiniGame - 1];
    }
    return (RankEnt*)lbl_803616CC.head;
}

#pragma opt_unroll_loops off
u32 fn_3_109CE8(RankEnt* p) {
    RankEnt* e;
    s32 v;
    u32 i;
    if (g_Minigame._1907 == 1) {
        e = fn_3_109D88_inl();
        v = p->score;
        i = 0;
        do {
            if (v > e[i].score || (v == e[i].score && p->sub > e[i].sub)) {
                break;
            }
            i++;
        } while (i < 5);
        return i;
    }
#ifdef TARGET_PC
    // The original returns r3 unchanged (the pointer p): a value >= 5, "not ranked".
    return 5;
#endif
}
#pragma opt_unroll_loops reset

// fn_3_1089E8, size:0x26C
void fn_3_1089E8(void) {
    s32 n;
    s32 row;
    s32 r;
    s32 k;
    n = 5;
    row = lbl_3_common_bss_34C90.menuType - 10;
    if (g_Minigame._1A3C != 0) {
        if (g_Minigame._1E2A >= 6) {
            n = 4;
        } else {
            n = 3;
        }
    } else if (lbl_3_common_bss_34C90.menuType == 0xC) {
        n = 4;
    }
    r = fn_3_6C938(1, 0x100);
    if (r != 0) {
        if (g_Minigame._1A3C != 0) {
            if (g_Minigame._1E2A >= 6) {
                if (lbl_3_common_bss_34C90.cursor == 3) {
                    lbl_3_common_bss_34C90.subState = 8;
                } else if (lbl_3_common_bss_34C90.cursor == 1) {
                    lbl_3_common_bss_34C90.subState = 6;
                } else {
                    lbl_3_common_bss_34C90.subState = 6;
                }
            } else {
                k = (u8)lbl_3_common_bss_34C90.cursor;
                if (k == 2) {
                    lbl_3_common_bss_34C90.subState = 8;
                } else {
                    lbl_3_common_bss_34C90.subState = 6;
                }
            }
        } else {
            switch ((lbl_3_data_188FC + row * 5)[lbl_3_common_bss_34C90.cursor]) {
            case 4:
                lbl_3_common_bss_34C90.subState = 8;
                break;
            default:
                lbl_3_common_bss_34C90.subState = 6;
                break;
            }
        }
        lbl_3_common_bss_34C90.team = r - 1;
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        if (lbl_3_common_bss_34C90.subState == 8) {
            fn_3_5B408();
        }
    } else if (fn_3_6C938(2, 8) != 0) {
        if (lbl_3_common_bss_34C90.cursor == 0) {
            lbl_3_common_bss_34C90.cursor = n - 1;
        } else {
            lbl_3_common_bss_34C90.cursor--;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (fn_3_6C938(2, 4) != 0) {
        if (lbl_3_common_bss_34C90.cursor < n - 1) {
            lbl_3_common_bss_34C90.cursor++;
        } else {
            lbl_3_common_bss_34C90.cursor = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// fn_3_108230, size:0x284
void fn_3_108230(void) {
    s32 row;
    s32 n;
    InputStruct* c;
    u8 v;
    row = 0;
    n = 6;
    c = &g_Controls[lbl_3_common_bss_34C90.team];
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        row = 2;
        n = 4;
    } else if (g_Minigame._1A3C != 0) {
        row = 1;
        n = 5;
    }
    if (c->newButtonInput & 0x1000) {
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        lbl_3_common_bss_34C90.subState = 4;
    } else if (c->newButtonInput & 0x100) {
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        switch ((lbl_3_data_188E8 + row * 6)[lbl_3_common_bss_34C90.cursor]) {
        case 0:
            lbl_3_common_bss_34C90.subState = 4;
            break;
        case 1:
            lbl_3_common_bss_34C90.subState = 0xC;
            break;
        case 3:
            lbl_3_common_bss_34C90.subState = 0xA;
            break;
        case 2:
            lbl_3_common_bss_34C90.subState = 0xB;
            break;
        case 4:
            lbl_3_common_bss_34C90.subState = 6;
            break;
        case 5:
            fn_3_5B408();
            lbl_3_common_bss_34C90.subState = 8;
            break;
        }
    } else if (c->newButtonInput & 0x200) {
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        if (lbl_3_common_bss_34C90.cursor != 0) {
            lbl_3_common_bss_34C90.cursor = 0;
        } else {
            lbl_3_common_bss_34C90.subState = 4;
        }
    } else if (c->_08 & 8) {
        if (lbl_3_common_bss_34C90.cursor == 0) {
            lbl_3_common_bss_34C90.cursor = n - 1;
        } else {
            lbl_3_common_bss_34C90.cursor--;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (c->_08 & 4) {
        lbl_3_common_bss_34C90.cursor++;
        if (lbl_3_common_bss_34C90.cursor >= n) {
            lbl_3_common_bss_34C90.cursor = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// fn_3_109254, size:0x2D8
void fn_3_109254(void) {
    InputStruct* c = &g_Controls[lbl_80366158._27];
    switch (g_GameLogic._125) {
    case 0:
        fn_3_5B368();
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        if (g_Minigame._1907 == 1) {
            fn_3_10952C();
            if (g_Minigame._1A3C != 0) {
                g_GameLogic._125 = 1;
            } else {
                g_GameLogic._125 = 5;
            }
        } else {
            g_GameLogic._125 = 5;
        }
        break;
    case 1:
        if (((MinigameTask*)MG_TASK_PTR)->_18 != 0) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0x1E;
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy >= 0x1E) {
            if ((c->buttonInput & 0x10) && (c->buttonInput & 0x800) && (c->buttonInput & 0x200)) {
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                g_GameLogic._125 = 3;
            } else if (c->newButtonInput & 0x1100) {
                ((MinigameTask*)MG_TASK_PTR)->_1A = 1;
                g_GameLogic._125 = 4;
            }
        }
        break;
    case 3:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x1E && (c->newButtonInput & 0x200)) {
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = 2;
        }
        break;
    case 4:
        if (MG_TASK_PTR == NULL) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = 5;
        }
        break;
    case 5:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x14) {
            g_GameLogic._125 = 6;
        }
        break;
    case 6:
        if (c->newButtonInput & 0x1100) {
            g_GameLogic._125 = 7;
        }
        break;
    case 7:
        if (g_Minigame._1A44 != 0 || g_Minigame._1A45 != 0 || g_Minigame._1A43 != 0 || g_Minigame._1A46[0] != 0) {
            if (fn_3_5B220(1) != 0) {
                g_GameLogic._125 = 8;
                g_Minigame._1A46[0] = 0;
            }
        } else {
            g_GameLogic._125 = 8;
        }
        break;
    case 8:
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 9;
        break;
    case 9:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x14) {
            g_GameLogic._125 = 10;
        }
        break;
    case 10:
        lbl_3_common_bss_34C90.state = 0;
        lbl_3_common_bss_34C90.subState = 0;
        fn_3_5A6D4(0x22);
        break;
    }
}

// fn_3_10AEF0, size:0x310
void fn_3_10AEF0(void) {
    s32 i;
    switch (g_GameLogic._125) {
    case 0:
        fn_800203E0(7, 0);
        g_Minigame._1A40 = 0;
        g_Minigame._19A7 = lbl_3_data_21270[g_Minigame.GameMode_MiniGame];
        g_Minigame._1A3E = 0;
        lbl_8036E548._307E = 1;
        lbl_8036E548._2D8E = 0;
        g_GameLogic._125 = 1;
        if (g_d_GameSettings.exhibitionMatchInd == 0) {
            g_d_GameSettings._36 = g_Minigame.minigameControlStruct[0].charID[g_Minigame._1908];
        }
        break;
    case 1:
        fn_3_10C81C();
        if (g_Minigame._1A0F[0] < 0) {
            fn_3_E1370(lbl_3_data_18918[g_Minigame.GameMode_MiniGame]);
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        if (fn_80016F7C() != 0) {
            g_GameLogic._125 = 3;
            lbl_3_common_bss_34C58._2C = 0;
        }
        break;
    case 3:
        if (fn_3_90DD8() != 0) {
            g_GameLogic._125 = 5;
        }
        break;
    case 5:
        g_GameLogic._125 = 6;
        break;
    case 6:
        if (lbl_8037169C.done == 0) {
            return;
        }
        if (g_GameLogic.FrameCountOfCurrentPitch >= lbl_3_data_18C48[2] ||
            (g_GameLogic.FrameCountOfCurrentPitch >= lbl_3_data_18C48[1] && fn_3_6C938(2, 0x1100) != 0)) {
            g_GameLogic._125 = 7;
            changeScene(3, 6);
            fn_8003A540(0);
        }
        break;
    case 7:
        if (lbl_8037169C._13 != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            g_GameLogic._125 = 8;
        }
        break;
    case 8:
        lbl_8036E548._307A = 1;
        g_Minigame._1A38 = 0;
        g_Minigame._1A39 = 0;
        for (i = 0; i < 4; i++) {
            if (g_Minigame.minigameControlStruct[0].characterIndex[i] >= 0) {
                g_Minigame.minigameControlStruct[0].turnOrder[i] = i;
            }
        }
        if (g_GameLogic.secondaryGameMode == 3) {
            minigamesSetSomePointers();
            minigamesGXStuff();
            g_Minigame._18A6 = 0;
        }
        if (g_Minigame.GameMode_MiniGame == 2) {
            fn_3_5A6D4(0x23);
        } else if (g_Minigame.miniGameNumberOfParticipants >= 2) {
            if (g_GameLogic.secondaryGameMode == 8) {
                fn_3_5A6D4(0x1A);
            } else {
                fn_3_5A6D4(0x23);
            }
        } else {
            fn_3_5A6D4(0x1A);
        }
        break;
    }
    if (g_GameLogic.secondaryGameMode == 3 && g_GameLogic._125 >= 3) {
        fn_3_1128EC();
    }
}

// fn_3_107E80, size:0x3B0
void fn_3_107E80(void) {
    InputStruct* c = &g_Controls[lbl_3_common_bss_34C90.team];
    s32 row;
    s8 (*t)[5];
    s32 k;
    switch (lbl_3_common_bss_34C90._1D4) {
    case 0:
        if (lbl_3_common_bss_34C90.subState == 0xB || g_d_GameSettings.GameModeSelected == 6) {
            g_Minigame._1A1E = 1;
            g_Minigame._1A1F = 0;
            g_Minigame._1A20 = 0;
            g_Minigame._1A22 = 0;
            if (g_Minigame.multiPlayerInd != 0) {
                g_Minigame._1A20 = 2;
            } else if (g_Minigame.soloMinigameDifficulty == 3) {
                g_Minigame._1A20 = 1;
            }
            row = g_Minigame.GameMode_MiniGame;
            if (g_GameLogic.gameStatus == 0x28) {
                row = 7;
            }
            g_Minigame._1A21 = 0;
            t = (s8(*)[5])(lbl_3_data_B060 + row * 0xF);
            for (k = 0; k < 5; k++) {
                if (t[g_Minigame._1A20][k] >= 0) {
                    g_Minigame._1A21++;
                }
            }
        }
        lbl_3_common_bss_34C90._1D9 = 1;
        lbl_3_common_bss_34C90.subFrames = 0;
        lbl_3_common_bss_34C90._1D4 = 1;
        break;
    case 1:
        if (lbl_3_common_bss_34C90._1D9 == 3) {
            lbl_3_common_bss_34C90._1D4 = 2;
        }
        break;
    case 2:
        lbl_3_common_bss_34C90._1D4 = 3;
        break;
    case 3:
        if (lbl_3_common_bss_34C90.subFrames > 0x14) {
            lbl_3_common_bss_34C90._1D4 = 4;
        }
        break;
    case 4:
        if (lbl_3_common_bss_32724._C4 == 0) {
            if (c->newButtonInput & 0x200) {
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                lbl_3_common_bss_34C90.subFrames = 0;
                lbl_3_common_bss_34C90._1D4 = 5;
            } else if (lbl_3_common_bss_34C90.subState == 0xB || (g_d_GameSettings.GameModeSelected == 6 && g_GameLogic.gameStatus == 0xB)) {
                if (c->_08 & 2) {
                    if (g_Minigame._1A1E == g_Minigame._1A21) {
                        g_Minigame._1A1E = 1;
                    } else {
                        g_Minigame._1A1E++;
                    }
                    g_Minigame._1A22 = 0;
                    g_Minigame._1A1F = 0x14;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                } else if (c->_08 & 1) {
                    if (g_Minigame._1A1E == 1) {
                        g_Minigame._1A1E = g_Minigame._1A21;
                    } else {
                        g_Minigame._1A1E--;
                    }
                    g_Minigame._1A22 = 1;
                    g_Minigame._1A1F = 0x14;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            }
        }
        break;
    case 5:
        if (lbl_3_common_bss_34C90.subFrames > 0x14) {
            lbl_3_common_bss_34C90.frames = 0;
            lbl_3_common_bss_34C90.subState = 1;
        }
        break;
    }
}

extern void fn_3_110634(void);

#pragma dont_inline off

// NONMATCHING 90%: inlined fn_3_1104A8 loop picks i/ptr regs swapped, port re-extsb missing
#if NONMATCHING
// fn_3_1104D4, size:0x160
void fn_3_1104D4(void) {
    s8 i;
    s8 port;
    InputStruct* pad;
    MiniGameStruct* mg = &g_Minigame;

    fn_3_1104A8();

    i = 0;
    do {
        port = mg->minigameControlStruct[0].characterIndex[i];
        if (port >= 0 && port < 4 && i == (s8)g_Minigame.rosterID && mg->minigameControlStruct[0].battingHandedness[i] != 0) {
            pad = &g_Minigame._1D7C[port];
            g_Minigame._1DBC[port] = 1;
            memset(pad, 0, 0x10);
            switch (g_Pitcher.pitcherActionState) {
            case 2:
                if (mg->bB_cpuSwingStep == 0) {
                    fn_3_110634();
                    mg->bB_cpuSwingStep = 1;
                }
                if (g_Pitcher.windupCountdownUntilBallReleased <= mg->bB_cpuSwingFrame) {
                    pad->buttonInput |= 0x100;
                }
                break;
            case 3:
                if (g_Ball.pitchHangtimeCounter < g_Pitcher.frameWhenUnhittable - (s16)mg->bB_cpuStickInput) {
                    pad->buttonInput |= 0x100;
                }
                break;
            }
        }
        i++;
    } while (i < 4);
}
#endif

extern void fn_3_8B318(s32);
extern s32 fn_3_90928(void);
extern void fn_800189E4(void);
extern s32 fn_80035838(void* aramAddr, u8 id);

// fn_3_10F3D8, size:0x178
void fn_3_10F3D8(void) {
    u8 s = g_GameLogic._125;
    switch (s) {
    case 0:
        fn_3_8B318(-1);
        fn_3_10C7A4();
        lbl_3_common_bss_34C58._2C = 0;
        g_GameLogic._125++;
    case 1:
        if (fn_3_90928() != 0) {
            g_GameLogic._125++;
        }
        break;
    case 2:
        if (fn_80035838(lbl_3_data_21EC8 + 0x1D0, 9) != 0) {
            g_GameLogic._125++;
        }
        break;
    case 3:
        if (g_d_GameSettings.GameModeSelected == 7) {
            if (fn_80035838(lbl_3_data_21EC8 + 0xD0, 0x11) != 0) {
                g_GameLogic._125++;
            }
        } else {
            g_GameLogic._125 = s + 1;
        }
        break;
    default:
        fn_800189E4();
        fn_800B0A5C_insertQueue(fn_80062A94, 1);
        g_Minigame._1A1C = 1;
        fn_3_5A6D4(g_Minigame._19DF);
        break;
    }
}

typedef struct {
    /*0x00*/ s16 resultCoins[3];
    /*0x06*/ s16 winMarginPercent;
    /*0x08*/ s16 lossMarginPercent;
    /*0x0A*/ s16 starPercent;
    /*0x0C*/ s16 _0C[3];
    /*0x12*/ s16 bjCoins[3];
    /*0x18*/ s16 bjPoints[3];
    /*0x1E*/ s16 _1E;
} CoinRewardTable; // size: 0x20
extern CoinRewardTable lbl_3_data_607C;
extern void fn_3_161078(void);

// fn_3_106ED4, size:0x1A4
void fn_3_106ED4(void) {
    s32 i;
    if (g_d_GameSettings.GameModeSelected == 6) {
        if (g_Minigame.challenge_minigame_haven_tWonYetIndicator == 0) {
            if (g_Minigame.minigameControlStruct[0]._1C[g_d_GameSettings._35] == 1) {
                g_d_GameSettings.challengeMinigame_baseCoinsEarned += g_Minigame.miniGameCurrentPoints[g_d_GameSettings._35];
            } else {
                g_d_GameSettings.challengeMinigame_baseCoinsEarned += lbl_3_data_607C._1E;
            }
        }
    } else if (g_Minigame.challenge_minigame_haven_tWonYetIndicator != 0) {
        g_d_GameSettings.challengeMinigame_baseCoinsEarned += lbl_3_data_607C._0C[1];
    } else if (g_Minigame.minigameControlStruct[0]._1C[g_d_GameSettings._35] == 1) {
        for (i = 0; i < 4; i++) {
            if (g_Minigame.minigameControlStruct[0]._1C[i] > 1) {
                break;
            }
        }
        g_d_GameSettings.challengeMinigame_baseCoinsEarned += lbl_3_data_607C._0C[0];
    } else if (g_d_GameSettings.challengeDifficulty != 0) {
        g_d_GameSettings.challengeMinigame_baseCoinsEarned += lbl_3_data_607C._0C[2];
    }
    for (i = 0; i < 4; i++) {
        g_d_GameSettings._20[i][0] = g_Minigame.miniGameCurrentPoints[i];
        g_d_GameSettings._20[i][1] = g_Minigame.minigameControlStruct[0]._1C[i];
    }
    fn_3_161078();
}

extern void possiblyTransitionBlackScreen(void);
extern void fn_3_5BAC(void);
extern void fn_3_1658F0(void);

// NONMATCHING 99%: post-loop g_Minigame/lbl_3_common_bss_32724 address loads scheduled in swapped order, r6/r7 swap
#if NONMATCHING
// fn_3_10FBE4, size:0x1E4
void fn_3_10FBE4(void) {
    s32 i;
    u8 port;
    g_GameLogic.secondaryGameMode = 2;
    fn_800B0A5C_insertQueue(possiblyTransitionBlackScreen, 2);
    fn_800B0A5C_insertQueue(fn_3_5BAC, 4);
    g_Scores.maxInnings = 5;
    g_Scores._AB = 5;
    g_Minigame._19DF = 0x1C;
    g_Minigame._19E1 = 0;
    g_Minigame._19E2 = 0;
    g_Minigame._19E3 = 0;
    g_Minigame._19E6 = 1;
    g_Minigame._19E7 = 1;
    g_Minigame.GameMode_MiniGame = 1;
    g_Minigame.soloMinigameDifficulty = 0;
    g_Minigame._1A2C = -1;
    g_Minigame._1A0C = -1;
    g_Minigame._19A7 = 4;
    g_Minigame.pauseInd = 0;
    g_Minigame._1A3C = 0;
    g_Minigame._1A3F = 0;
    g_Minigame._190A = 0;
    g_Minigame._1D6D = -1;
    g_Minigame._1A40 = 1;
    g_Minigame.challenge_minigame_haven_tWonYetIndicator = 1;
    g_Minigame._19A9 = 0;
    g_Minigame._1A3D = 0;
    g_Minigame._19E0 = 0;
    g_Minigame._1A38 = 0;
    g_Minigame._1A39 = 0;
    g_Minigame._1A46[0] = 0;
    g_Minigame._1A1C = 0;
    for (i = 0; i < 4; i++) {
        g_Minigame._19DA[i] = -1;
        g_Minigame._19E8[i]._0 = -1;
        g_Minigame._19E8[i]._2 = -1;
        g_Minigame._19E8[i]._3 = -1;
        g_Minigame._19E8[i]._7 = 0;
        g_Minigame._19E8[i]._8 = 0;
        g_Minigame._1A0F[i] = -1;
        g_Minigame._19D2[i] = 0x14;
        g_Minigame._1A13[i] = 0;
        g_Minigame.minigameControlStruct[0].aIStrength[i] = 0;
        g_Minigame.minigameControlStruct[0]._08[i] = 0;
    }
    lbl_3_common_bss_32724._B9 = 0;
    g_Minigame._1A1B = 0;
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        g_Minigame._190A = 1;
        port = g_d_GameSettings._35;
        g_Minigame._19DA[port] = port;
        lbl_3_common_bss_37400.humanPlayer = port;
        g_Minigame.GameMode_MiniGame = g_d_GameSettings._33;
        fn_3_1658F0();
        g_Minigame._19DF = 0x1E;
        fn_3_5A6D4(0x1B);
    } else {
        fn_3_5A6D4(0x1B);
    }
}
#endif
extern s16 lbl_80109410[8];

// NONMATCHING 93%: original hoists g_Minigame+0x18CC / inMemRoster+0x24 into saved regs shared with the inlined fn_3_10754C
#if NONMATCHING
// fn_3_109DE0, size:0x23C
void fn_3_109DE0(RankEnt* out) {
    StatInput stat;
    s32 lim;
    memset(out, 0, sizeof(RankEnt));
    if (g_Minigame._1907 == 1) {
        {
        CharacterStats* r = inMemRoster[0];
        out->charId = r[g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame._1908]].stats.CharID;
        }
        if (g_Minigame._1A3C != 0) {
            fn_3_10754C(&stat);
            out->score = fn_8006C13C(&stat);
            out->sub = 0;
            return;
        }
        out->score = g_Minigame.miniGameCurrentPoints[g_Minigame._1908];
        if (out->score > lbl_80109410[g_Minigame.GameMode_MiniGame]) {
            out->score = lbl_80109410[g_Minigame.GameMode_MiniGame];
        }
        switch (g_Minigame.GameMode_MiniGame) {
        case 1:
            out->sub = g_Minigame.bOD_HitPowerOfEachChar[g_Minigame._1908];
            if (out->sub > 999) {
                out->sub = 999;
            }
            break;
        default:
            out->sub = 0;
            break;
        }
    }
}
#endif


extern int random_fn_3_9EE24(int max);
extern u8 lbl_3_data_18944[];
extern u8 lbl_3_data_1894C[][7];
extern u8 lbl_3_data_18978[];

// NONMATCHING 92%: settings byte 0x36 should be sign-extended once up front, saved-reg numbering differs
#if NONMATCHING
// fn_3_10F684, size:0x298
void fn_3_10F684(void) {
    s32 picks[6];
    s32 i;
    s32 n;
    s32 slot;
    s32 r;
    s32 j;

    n = 0;
    g_Minigame.GameMode_MiniGame = g_d_GameSettings._33;
    g_Minigame._19DA[g_d_GameSettings._35] = 0;
    for (i = 0; i < 4; i++) {
        if (g_d_GameSettings._35 == i) {
            g_Minigame._19E8[i]._0 = (s8)g_d_GameSettings._36;
            g_Minigame._19E8[i]._1 = 1;
        } else {
            g_Minigame._19DA[i] = 1;
            n++;
            g_Minigame.minigameControlStruct[0].aIStrength[i] = lbl_3_data_18978[g_d_GameSettings.challengeDifficulty];
            if (n >= lbl_3_data_18944[g_Minigame.GameMode_MiniGame]) {
                break;
            }
        }
    }

    g_Minigame.miniGameNumberOfParticipants = lbl_3_data_18944[g_Minigame.GameMode_MiniGame] + 1;
    g_Minigame._1907 = 1;
    g_Minigame.multiPlayerInd = 1;
    g_Minigame.soloMinigameDifficulty = 0;
#ifdef TARGET_PC
    {
        extern s32 port_career_training_active(void);
        if (port_career_training_active()) {
            u8 c = g_d_GameSettings._36;
            g_Minigame.soloMinigameDifficulty = 1; // Career training: always the Flower level
            // What character select would have set for your player.
            g_Minigame._19E8[g_d_GameSettings._35]._6 = 0;
            g_Minigame.battingHandedness[g_d_GameSettings._35] =
                CHAR_STATS(c)->stats.FieldingArm * 2 + CHAR_STATS(c)->stats.BattingStance;
            g_Minigame.minigameControlStruct[0]._08[g_d_GameSettings._35] = 0;
        }
    }
#endif
    for (j = 0; j < 6; j++) {
        picks[j] = lbl_3_data_1894C[g_Minigame.GameMode_MiniGame][j + 1];
    }
    slot = 0;
    for (i = 0; i < lbl_3_data_18944[g_Minigame.GameMode_MiniGame]; i++) {
        for (;;) {
            if ((s32)(u8)g_Minigame._19DA[slot] == 1) {
                break;
            }
            slot++;
        }
        r = random_fn_3_9EE24(lbl_3_data_1894C[g_Minigame.GameMode_MiniGame][0] - i);
        for (j = 0; j < 6; j++) {
            if (picks[j] != 0xFF) {
                if (r == 0) {
                    g_Minigame._19E8[slot]._0 = picks[j];
                    g_Minigame._19E8[slot]._1 = 1;
                    slot++;
                    picks[j] = 0xFF;
                    break;
                }
                r--;
            }
        }
    }
}
#endif

// Rebuilds the minigame player list (0x18CC/0x18D0/0x18D8) and their rosters from the
// slot setup. The original inlines it into fn_3_10F91C/fn_3_10FDC8 and fn_3_10E60C.
static inline void buildMinigamePlayersInline(void) {
    s32 i;
    MiniGameStruct* mg;
    mg = &g_Minigame;
    for (i = 0; i < 4; i++) {
        mg->minigameControlStruct[0].characterIndex[i] = -1;
        mg->minigameControlStruct[0].battingHandedness[i] = 0;
        mg->minigameControlStruct[0].charID[i] = 0xFF;
    }
    mg->miniGameNumberOfParticipants = 0;
    mg->_1907 = 0;
    fn_3_10BE7C();
    for (i = 0; i < 4; i++) {
        if (g_Minigame._19DA[i] >= 0) {
            g_Minigame.minigameControlStruct[0].characterIndex[mg->miniGameNumberOfParticipants] = i;
            g_Minigame.minigameControlStruct[0].battingHandedness[mg->miniGameNumberOfParticipants] = (u8)g_Minigame._19DA[i];
            if (g_Minigame.minigameControlStruct[0].battingHandedness[mg->miniGameNumberOfParticipants] == 0) {
                mg->_1907++;
            }
            fn_3_10C450(i, g_Minigame._19E8[i]._0);
            g_Minigame.minigameControlStruct[0].charID[mg->miniGameNumberOfParticipants] = inMemRoster[0][i].stats.CharID;
            mg->miniGameNumberOfParticipants++;
        }
    }
}

// Body of fn_3_10F91C (sets up the minigame player slots and their rosters); the original
// inlines it into fn_3_10FDC8, so it lives in a static inline that both use.
static inline void setupMinigamePlayersInline(void) {
    switch (g_GameLogic._125) {
    case 0:
        fn_3_10F684();
        lbl_3_common_bss_32724.loadStep = 0;
        g_GameLogic._125++;
        break;
    }
    buildMinigamePlayersInline();
    fn_3_5A6D4(0x21);
}

void fn_3_10F91C(void) {
    setupMinigamePlayersInline();
}

extern void fn_3_15F998(void);
extern void fn_3_147DFC(void);

// fn_3_10722C, size:0x320
void fn_3_10722C(void) {
    u8 buf[8];
    u32 i;
    u32 j;
    switch (g_GameLogic._125) {
    case 0:
        i = 0;
        do {
            g_Minigame._1E26[i] = g_Minigame._1E22[i];
            i++;
        } while (i < g_Minigame.miniGameNumberOfParticipants);
        fn_3_1079C8(buf, 0);
        i = 0;
        do {
            g_Minigame._1E22[buf[i * 2]] += lbl_3_data_21EC4[buf[i * 2 + 1]] * (g_Minigame._1E2A >= 6U ? 2 : 1);
            i++;
        } while (i < g_Minigame.miniGameNumberOfParticipants);
        fn_3_1079C8((u8*)g_Minigame.resultSlot, 1);
        if (g_Minigame._1907 == 1) {
            g_Minigame._1E10[g_Minigame.GameMode_MiniGame - 1] = g_Minigame.miniGameCurrentPoints[g_Minigame._1908];
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (i == g_Minigame.resultSlot[j].player) {
                    g_Minigame.minigameControlStruct[0]._1C[i] = g_Minigame.resultSlot[j].taken + 1;
                }
            }
        }
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 1;
        break;
    case 1:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x78) {
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x708 || fn_3_6C938(1, 0x1100) != 0) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = 3;
        }
        break;
    case 3:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x78) {
            g_GameLogic._125 = 4;
        }
        break;
    case 4:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x708 || fn_3_6C938(1, 0x1100) != 0) {
            g_GameLogic._125 = 5;
        }
        break;
    case 5:
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 6;
        if (g_Minigame._1E2A >= 6) {
            changeScene(3, 6);
        }
        break;
    case 6:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x3C) {
            g_GameLogic._125 = 7;
        }
        break;
    case 7:
        if (g_Minigame._1E2A >= 6) {
            fn_3_15F998();
            fn_3_147DFC();
            lbl_3_common_bss_34C58._31 = 0;
            fn_3_5A6D4(0x27);
        } else {
            lbl_3_common_bss_34C90.state = 0;
            lbl_3_common_bss_34C90.subState = 0;
            fn_3_5A6D4(0x22);
        }
        break;
    }
}

extern void fn_3_6AB30(void);
extern void fn_3_11CF84(void);
extern u8 lbl_3_data_6104[8];

static inline void satInc16(s16* p) {
    if (*p < 0x7FFE) {
        (*p)++;
    } else {
        *p = 0x7FFF;
    }
}

// fn_3_1084B4, size:0x3A0
void fn_3_1084B4(void) {
    lbl_80366158._28 = 1;
    satInc16(&lbl_3_common_bss_34C90._0A);
    satInc16(&lbl_3_common_bss_34C90.frames);
    satInc16(&lbl_3_common_bss_34C90.subFrames);
    switch (lbl_3_common_bss_34C90.subState) {
    case 0:
        lbl_3_common_bss_34C90.frames = 0;
        lbl_3_common_bss_34C90.subState = 1;
        break;
    case 1:
        lbl_3_common_bss_34C90.subState = 3;
        break;
    case 2:
        if (lbl_3_common_bss_34C90.frames > 0x14) {
            lbl_3_common_bss_34C90.subState = 3;
        }
        break;
    case 3:
        fn_3_108230();
        lbl_3_common_bss_34C90.frames = 0;
        lbl_3_common_bss_34C90.subFrames = 0;
        lbl_3_common_bss_34C90._1D4 = 0;
        break;
    case 4:
        lbl_3_common_bss_34C90._1D9 = 1;
        lbl_3_common_bss_34C90.subState = 5;
        break;
    case 5:
        if (lbl_3_common_bss_34C90._1D9 == 3) {
            g_Minigame.pauseInd = 0;
        }
        break;
    case 6:
        changeScene(3, 6);
        if (lbl_8037169C._13 != 0) {
            lbl_3_common_bss_34C90.subState = 7;
        }
        break;
    case 7:
        lbl_8036E548._307A = 0;
        g_Minigame._1A40 = 1;
        lbl_3_common_bss_34C90._1D9 = 2;
        g_Minigame.pauseInd = 0;
        fn_3_6AB30();
        fn_3_11CF84();
        g_Minigame._19DF = 0x1C;
        fn_3_5A6D4(0x1D);
        break;
    case 8:
        switch (fn_3_5B380(g_Controls[lbl_3_common_bss_34C90.team].newButtonInput)) {
        case 1:
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            lbl_3_common_bss_34C90.subState = 9;
            break;
        case 2:
            lbl_3_common_bss_34C90.subState = 3;
            break;
        }
        break;
    case 9:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x2D) {
            if (g_d_GameSettings.exhibitionMatchInd == 0) {
                fn_800203E0(0xC, (s8)lbl_3_data_6104[gChallengeState._441C]);
            } else {
                changeScene(4, 6);
            }
        }
        if (lbl_8037169C._13 != 0) {
            g_Minigame._1A40 = 1;
            lbl_3_common_bss_34C90._1D9 = 2;
            g_Minigame.pauseInd = 0;
            g_d_GameSettings._13 = 1;
            fn_3_11CF84();
            fn_8004CC18();
#ifdef TARGET_PC
            { extern void port_career_training_exit(s32 result); port_career_training_exit(-1); }
#endif
            g_GameLogic.framesOfExitingToMenu = 1;
        }
        break;
    case 10:
        fn_3_107E80();
        break;
    case 11:
        fn_3_107E80();
        break;
    case 12:
        changeScene(3, 6);
        if (lbl_8037169C._13 != 0) {
            lbl_3_common_bss_34C90.subState = 0xD;
        }
        break;
    case 13:
        g_Minigame._1A38 = 1;
        fn_3_11CF84();
        lbl_8036E548._307A = 0;
        fn_3_6AB30();
        g_Minigame._1A40 = 1;
        lbl_3_common_bss_34C90._1D9 = 2;
        g_Minigame.pauseInd = 0;
        fn_3_5A6D4(4);
        break;
    }
}

extern void fn_80011B64(s32 index);
extern s32 fn_80016710(u8 kind, s32 index);

typedef struct {
    s32 port;
    s32 timer;
} PortTimer;

// NONMATCHING 93%: original passes the s8 kind to fn_80016710 sign-extended (no u8 prototype); saved-reg numbering and the else-branch base reloads differ
#if NONMATCHING
// fn_3_10C81C, size:0x404
void fn_3_10C81C(void) {
    PortTimer ents[4];
    s32 count;
    s32 n;
    s32 i;
    s32 j;
    s32 k;
    s32 done;
    s8 cur;
    s32 index;
    s8 a;

    count = 4;
    for (;;) {
        if (g_d_GameSettings.GameModeSelected == 2) {
            count = 1;
        }
        n = 0;
        for (i = 0; i < count; i++) {
            ents[i].port = -1;
            if (g_Minigame._1A0C != i) {
                a = g_Minigame._19E8[i]._0;
                if (a != -1 && (a != g_Minigame._19E8[i]._2 || (s8)g_Minigame._19E8[i]._4 != g_Minigame.battingHandedness[i])) {
                    g_Minigame._19E8[i]._7 = 0;
#ifdef TARGET_PC
                    g_port_selLoading[i] = 1; // hidden only because the model is still loading
#endif
                    if ((u16)g_Minigame._19D2[i] >= 0x14 || g_Minigame._19DE == 4) {
                        ents[n].port = i;
                        ents[n].timer = (u16)g_Minigame._19D2[i];
                        n++;
                        g_Minigame._19E8[i]._5 = g_Minigame.battingHandedness[i];
                    }
                }
            }
        }
        for (i = 0; i < n - 1; i++) {
            for (j = i + 1; j < n; j++) {
                s32 t = ents[i].timer;
                if (t < ents[j].timer) {
                    s32 p = ents[i].port;
                    ents[i].port = ents[j].port;
                    ents[i].timer = ents[j].timer;
                    ents[j].port = p;
                    ents[j].timer = t;
                }
            }
        }
        g_Minigame._1A0F[0] = -1;
        g_Minigame._1A0F[1] = -1;
        g_Minigame._1A0F[2] = -1;
        g_Minigame._1A0F[3] = -1;
        k = 0;
        if (g_Minigame._1A0C >= 0) {
            g_Minigame._1A0F[0] = (u8)g_Minigame._1A0C;
            k = 1;
        }
        {
            s8* dst = &g_Minigame._1A0F[k];
            PortTimer* src = ents;
            for (i = n; i > 0; i--) {
                *dst = src->port;
                src++;
                dst++;
            }
        }
        if (g_Minigame._1A0F[0] < 0) {
            break;
        }
        cur = (u8)g_Minigame._1A0F[0];
        index = cur;
        if (g_d_GameSettings.GameModeSelected == 2) {
            index = 9;
        }
        if (g_Minigame._1A1B == 0) {
            g_Minigame._1A1B = 1;
            fn_80011B64(index);
        }
#ifdef TARGET_PC
        {
            extern int port_spani_trace_on(void);
            extern void OSReport(const char*, ...);
            static s32 s_loadPolls;
            s_loadPolls++;
            if (g_Minigame._19E8[cur]._3 >= 0) {
                done = fn_80016710(g_Minigame._19E8[cur]._3, index);
            } else {
                done = fn_80016710(g_Minigame._19E8[cur]._0, index);
            }
            if (done != 0) {
                if (port_spani_trace_on()) {
                    OSReport("[charload] player %d char %d loaded after %d polls (frames)\n", (int)cur,
                             (int)g_Minigame._19E8[cur]._0, (int)s_loadPolls);
                }
                s_loadPolls = 0;
            }
        }
#else
        if (g_Minigame._19E8[cur]._3 >= 0) {
            done = fn_80016710(g_Minigame._19E8[cur]._3, index);
        } else {
            done = fn_80016710(g_Minigame._19E8[cur]._0, index);
        }
#endif
        if (done != 0) {
            g_Minigame._19E8[cur]._2 = (u8)g_Minigame._19E8[cur]._3;
            g_Minigame._19E8[cur]._3 = -1;
            lbl_8036E548.state = 0;
            g_Minigame._19E8[cur]._4 = g_Minigame._19E8[cur]._5;
            g_Minigame._1A0C = -1;
            g_Minigame._1A0F[0] = -1;
            g_Minigame._1A13[cur] = 0;
            g_Minigame._1A1B = 0;
            fn_3_E1370(3);
            continue;
        }
        if (g_Minigame._19E8[cur]._3 < 0) {
            g_Minigame._19E8[cur]._3 = g_Minigame._19E8[cur]._0;
        }
        g_Minigame._19E8[cur]._2 = -1;
        g_Minigame._1A0C = cur;
        break;
    }
    for (i = 0; i < 4; i++) {
        if (g_Minigame._1A13[i] != 0 && g_Minigame._19E8[i]._0 == g_Minigame._19E8[i]._2) {
            g_Minigame._1A13[i] = 0;
        }
    }
}
#endif

extern void fn_800189B8(void);
extern void fn_3_908E8(void);
extern s32 fn_3_90860(void);
extern s32 fn_3_90A18(void);
extern void fn_80018B74(void);
extern s32 fn_80020388(void);
extern void fn_3_BF070(void);

// fn_3_10B8D0, size:0x5AC
void fn_3_10B8D0(void) {
    s32 i;
    u32 t;
    switch (g_GameLogic._125) {
    case 0:
        lbl_8036E548._307E = 0;
        if (g_Minigame._1A3C == 0 || g_Minigame._1E2A <= 1) {
            if (g_Minigame._1A38 == 0) {
                fn_80062A74();
                fn_800189B8();
                if (g_d_GameSettings.GameModeSelected == 7) {
                    fn_80035B50(0x11);
                }
                fn_80035B50(9);
                fn_3_908E8();
            }
        }
        g_Minigame._1A1C = 0;
        g_Minigame._1A41 = 0;
        g_Minigame.multiPlayerInd = 0;
        g_Minigame._19AA = 0;
        g_Minigame._1908 = -1;
        g_Minigame._1A1D = 0;
        g_Minigame._1A23 = 0;
        g_Minigame._1A24[0] = 2;
        g_Minigame._1A46[0] = 0;
        if (g_d_GameSettings.exhibitionMatchInd == 0) {
            g_Minigame._1A24[0] = 0;
        }
        g_d_GameSettings._3A = g_Minigame.soloMinigameDifficulty;
        lbl_8037169C._15 = 0;
        lbl_3_common_bss_34C58._2C = 0;
        if (g_Minigame._1907 != 1 || g_Minigame._1A3C != 0) {
            g_Minigame.multiPlayerInd = 1;
            g_Minigame.soloMinigameDifficulty = 0;
        }
        if (g_Minigame._1907 == 1) {
            for (i = 0; i < 4; i++) {
                if (g_Minigame.minigameControlStruct[0].battingHandedness[i] == 0) {
                    g_Minigame._1908 = i;
                    break;
                }
            }
        }
        if (g_d_GameSettings.GameModeSelected == 6) {
            g_d_GameSettings._33 = 0;
        } else {
            g_d_GameSettings._33 = g_Minigame.GameMode_MiniGame;
        }
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125++;
        if (g_Minigame._1A38 != 0 && g_Minigame._1A3C == 0) {
            changeScene(1, 6);
            g_GameLogic._125 = 2;
        }
        break;
    case 1:
        if (fn_80035838(lbl_3_data_21EC8 + (g_Minigame.GameMode_MiniGame + 6) * 0x10, 0x11) != 0) {
            changeScene(1, 6);
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125++;
        }
        break;
    case 2:
        if (g_Minigame._1A38 != 0 && g_Minigame._1A3C == 0) {
            g_GameLogic._125 = 8;
        } else if (fn_3_90860() != 0) {
            lbl_3_common_bss_34C58._2C = 0;
            g_GameLogic._125++;
        }
        break;
    case 3:
        g_d_GameSettings.StadiumID = lbl_3_data_18910[g_Minigame.GameMode_MiniGame];
        if (fn_3_90A18() != 0) {
            g_GameLogic._125++;
        }
        break;
    case 4:
        fn_80018B74();
        g_GameLogic._125++;
    case 5:
        g_Minigame._1A2C = -1;
        t = lbl_3_data_18910[g_Minigame.GameMode_MiniGame];
        lbl_3_data_228._10 = 0;
        g_d_GameSettings.StadiumID = t;
        g_d_GameSettings.miniGameStadiumIndicator = 0;
        if (g_d_GameSettings.StadiumID == 0 || g_d_GameSettings.StadiumID == 4 || g_d_GameSettings.StadiumID == 1 || g_d_GameSettings.StadiumID == 3) {
            g_d_GameSettings.miniGameStadiumIndicator = 1;
        }
        fn_800B0A5C_insertQueue(manageStadiumLoading, 0);
        g_GameLogic._125++;
        break;
    case 6:
        if (fn_3_10F564() == 0) {
            g_GameLogic._125++;
        }
        break;
    case 7:
        if (fn_80020388() != 0) {
            g_GameLogic._125++;
        }
        break;
    case 8:
        if (g_Minigame._1A1D != 0) {
            changeScene(3, 6);
            if (g_Minigame._1A1D == 2) {
                g_GameLogic._125 = 10;
            } else {
                g_GameLogic._125 = 9;
            }
        }
        break;
    case 9:
        if (lbl_8037169C._13 != 0) {
            if (g_d_GameSettings.GameModeSelected == 6) {
                g_Scores._AB = g_Scores.maxInnings = g_Minigame._1A24[0] * 2 + 1;
                fn_3_5A6D4(5);
            } else {
                fn_3_5A6D4(4);
            }
            fn_3_BF070();
        }
        break;
    case 10:
        if (lbl_8037169C._13 != 0) {
            g_GameLogic._125 = 11;
        }
        break;
    case 11:
        g_Minigame._1A38 = 0;
        fn_3_10B200();
        break;
    }
    if (g_GameLogic._125 >= 2 && g_Minigame._1A1D == 0) {
        fn_3_10B27C();
    }
}

extern u8 lbl_800E854C[12];
extern u8 lbl_3_data_609C[][6];

void fn_3_10BE7C(void) {
    s32 m;
    s32 n;
    s32 k;
    s32 j;
    s32 pool[12];
    u8 mode;
    s32 taken[4];
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_Minigame.minigameControlStruct[0].battingHandedness[i] == 0 && g_Minigame._19DA[i] >= 0) {
            taken[i] = g_Minigame._19E8[i]._0;
        } else {
            taken[i] = -1;
        }
    }

    if (g_d_GameSettings.GameModeSelected == 6 && g_d_GameSettings.exhibitionMatchInd == 0) {
        for (i = 0; i < lbl_3_data_1894C[0][0]; i++) {
            pool[i] = lbl_3_data_1894C[0][i + 1];
        }
    } else if (g_Minigame._1A3C != 0) {
        for (i = 0; i < 12; i++) {
            pool[i] = lbl_800E854C[i];
        }
        fn_3_9E078(pool, 12, 0);
    } else {
        mode = g_Minigame.GameMode_MiniGame;
        if ((mode == 1 || mode == 3) && g_Minigame._1908 >= 0) {
            return;
        }
        n = 6;
        if (g_d_GameSettings.exhibitionMatchInd == 0) {
            if (mode == 2) {
                k = g_Minigame.soloMinigameDifficulty;
            } else if (mode == 4) {
                k = g_Minigame.soloMinigameDifficulty + 3;
            } else if (mode == 5) {
                k = g_Minigame.soloMinigameDifficulty + 6;
            } else if (mode == 6) {
                k = g_Minigame.soloMinigameDifficulty + 9;
            } else {
                k = 0;
            }
            n = 0;
            for (i = 0; i < 6; i++) {
                pool[i] = lbl_3_data_609C[k][i];
                if (pool[i] != 0xFF) {
                    n++;
                }
            }
        } else {
            if (mode == 2) {
                if (g_Minigame.soloMinigameDifficulty == 3) {
                    k = -1;
                } else {
                    k = g_Minigame.soloMinigameDifficulty + 1;
                }
            } else if (mode == 4) {
                k = g_Minigame.soloMinigameDifficulty + 5;
            } else if (mode == 5) {
                k = g_Minigame.soloMinigameDifficulty + 9;
            } else if (mode == 6) {
                k = g_Minigame.soloMinigameDifficulty + 0xD;
            } else {
                k = 0;
            }
            if (k < 0) {
                for (i = 0; i < 6; i++) {
                    pool[i] = -1;
                }
            } else {
                for (i = 0; i < 6; i++) {
                    pool[i] = lbl_3_data_212A4[k][i];
                }
            }
        }
        fn_3_9E078(pool, n, 0);
    }

    i = 0;
    k = 0;
    for (; i < 4; i++) {
        if (g_Minigame._19DA[i] != 0 && (s8)g_Minigame._19E8[i]._1 == 0) {
            for (m = k; k < 6; k++, m++) {
                for (j = 0; j < 4; j++) {
                    if (pool[m] == taken[j] && pool[m] >= 0) {
                        break;
                    }
                }
                if (j >= 4) {
                    break;
                }
            }
            g_Minigame._19E8[i]._0 = pool[m];
            g_Minigame._19D2[i] = 0x14;
            g_Minigame.battingHandedness[i] = CHAR_STATS(pool[m])->stats.FieldingArm * 2 + CHAR_STATS(pool[m])->stats.BattingStance;
            k++;
        }
    }
}

extern u8 lbl_3_data_18920[][5];

// NONMATCHING 99%: in case 7 the original reuses the loop counter register as the zero for the 0x1A3D/0x1A3F/0x307E stores
#if NONMATCHING
// fn_3_108C54, size:0x600
void fn_3_108C54(void) {
    u32 i;
    s32 j;
    CharacterStats* src;

    satInc16(&lbl_3_common_bss_34C90._0A);
    satInc16(&lbl_3_common_bss_34C90.frames);
    satInc16(&lbl_3_common_bss_34C90.subFrames);
    switch (lbl_3_common_bss_34C90.subState) {
    case 0:
        if (g_Minigame.multiPlayerInd != 0 || g_d_GameSettings._14[g_Minigame.GameMode_MiniGame - 1] == 0) {
            lbl_3_common_bss_34C90.menuType = 0xC;
        } else if (g_Minigame._1A44 != 0) {
            lbl_3_common_bss_34C90.menuType = 0xB;
        } else {
            lbl_3_common_bss_34C90.menuType = 0xA;
        }
        if (g_Minigame._1A3C != 0) {
            if (g_Minigame._1E2A >= 6) {
                lbl_3_common_bss_34C90.menuType = 0xF;
            } else {
                lbl_3_common_bss_34C90.menuType = 0xE;
            }
        }
        lbl_3_common_bss_34C90._0A = 0;
        lbl_3_common_bss_34C90.frames = 0;
        lbl_3_common_bss_34C90.cursor = 0;
        lbl_3_common_bss_34C90.subState = 1;
        break;
    case 1:
        lbl_3_common_bss_34C90.frames = 0;
        lbl_3_common_bss_34C90.subState = 2;
        break;
    case 2:
        if (lbl_3_common_bss_34C90.frames >= 0x14) {
            lbl_3_common_bss_34C90.subState = 3;
        }
        break;
    case 3:
        fn_3_1089E8();
        lbl_3_common_bss_34C90.frames = 0;
        lbl_3_common_bss_34C90.subFrames = 0;
        break;
    case 6:
        changeScene(3, 6);
        if (lbl_8037169C._13 != 0) {
            lbl_3_common_bss_34C90.subState = 7;
        }
        break;
    case 7:
        if (g_Minigame._1A3C != 0) {
            if (g_Minigame._1E2A >= 6) {
                if (lbl_3_common_bss_34C90.cursor == 0) {
                    g_Minigame._1A38 = 1;
                    memset(&g_Minigame._1E04, 0, 0x28);
                    i = 0;
                    g_Minigame._1A3D = 0;
                    g_Minigame._1A3F = 0;
                    lbl_8036E548._307E = 0;
                    do {
                        g_Minigame._1E1C[i] = i + 1;
                        i++;
                    } while (i < 6);
                    fn_3_9DC18(g_Minigame._1E1C, 6, 0);
                    fn_3_5A6D4(0x28);
                    fn_3_5A6D4(0x29);
                } else if (lbl_3_common_bss_34C90.cursor == 1) {
                    g_Minigame._19DF = 0x1E;
                    fn_3_5A6D4(0x1D);
                } else {
                    g_Minigame._19DF = 0x1C;
                    fn_3_5A6D4(0x1D);
                }
                fn_3_FBD70();
                fn_3_FBD58();
            } else if (lbl_3_common_bss_34C90.cursor == 0) {
                fn_3_5A6D4(0x29);
            } else {
                fn_3_5A6D4(0x1D);
            }
        } else {
            switch ((lbl_3_data_188FC + lbl_3_common_bss_34C90.menuType * 5 - 50)[lbl_3_common_bss_34C90.cursor]) {
            case 0:
                g_Minigame._1A38 = 1;
                fn_3_5A6D4(4);
                break;
            case 1:
                g_Minigame._19DF = 0x1E;
                fn_3_5A6D4(0x1D);
                break;
            case 2:
                g_Minigame._19DF = 0x1E;
                g_Minigame._19E0 = 1;
                fn_3_5A6D4(0x1D);
                break;
            case 3:
                g_Minigame._19DF = 0x1C;
                fn_3_5A6D4(0x1D);
                break;
            case 5:
                g_Minigame._1A38 = 1;
                g_Minigame.soloMinigameDifficulty++;
                g_Minigame._1A39 = 1;
                fn_3_5A6D4(0x21);
                break;
            }
        }
        fn_3_11CF84();
        if (g_Minigame._1A39 != 0) {
            fn_3_10BE7C();
            g_Minigame.miniGameNumberOfParticipants = lbl_3_data_18920[g_Minigame.GameMode_MiniGame][g_Minigame.soloMinigameDifficulty];
            for (j = 0; j < 4; j++) {
                if (g_Minigame.minigameControlStruct[0].battingHandedness[j] != 0) {
                    if (g_Minigame.miniGameNumberOfParticipants == 1) {
                        g_Minigame.minigameControlStruct[0].characterIndex[j] = -1;
                    } else {
                        src = CHAR_STATS(g_Minigame._19E8[g_Minigame.minigameControlStruct[0].characterIndex[j]]._0);
                        memcpy(&inMemRoster[0][g_Minigame.minigameControlStruct[0].characterIndex[j]], src, 0xA0);
                        g_Minigame.battingHandedness[j] = src->stats.FieldingArm * 2 + src->stats.BattingStance;
                        g_Minigame.minigameControlStruct[0].charID[j] = inMemRoster[0][g_Minigame.minigameControlStruct[0].characterIndex[j]].stats.CharID;
                    }
                }
            }
        }
        g_Minigame._1A40 = 1;
        g_Minigame._19A9 = 0;
        fn_3_15F998();
        fn_3_147DFC();
        lbl_8036E548._307A = 0;
        lbl_3_common_bss_34C90._1D9 = 2;
        break;
    case 8:
        switch (fn_3_5B380(g_Controls[lbl_3_common_bss_34C90.team].newButtonInput)) {
        case 1:
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            lbl_3_common_bss_34C90.subState = 9;
            break;
        case 2:
            lbl_3_common_bss_34C90.subState = 3;
            break;
        }
        break;
    case 9:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x2D) {
            changeScene(4, 6);
        }
        if (lbl_8037169C._13 != 0) {
            g_Minigame._1A40 = 1;
            lbl_3_common_bss_34C90._1D9 = 2;
            fn_3_15F998();
            fn_3_147DFC();
            fn_3_11CF84();
            fn_8004CC18();
            g_GameLogic.framesOfExitingToMenu = 1;
        }
        break;
    }
}
#endif

// fn_3_10B27C, size:0x654
void fn_3_10B27C(void) {
    s32 row;
    s8 (*t)[5];
    s32 k;

    if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
        g_Minigame._1A1E = 0;
        g_Minigame._1A1F = 0;
        g_Minigame._1A20 = 0;
        g_Minigame._1A22 = 0;
        if (g_Minigame.multiPlayerInd != 0) {
            g_Minigame._1A20 = 2;
        } else if (g_Minigame.soloMinigameDifficulty == 3) {
            g_Minigame._1A20 = 1;
        }
        row = g_Minigame.GameMode_MiniGame;
        if (g_GameLogic.gameStatus == 0x28) {
            row = 7;
        }
        g_Minigame._1A21 = 0;
        t = (s8(*)[5])(lbl_3_data_B060 + row * 0xF);
        for (k = 0; k < 5; k++) {
            if (t[g_Minigame._1A20][k] >= 0) {
                g_Minigame._1A21++;
            }
        }
    }
    if (lbl_8037169C.done == 0) {
        return;
    }
    if (g_Minigame._1A1F != 0) {
        g_Minigame._1A1F--;
        return;
    }
    if (g_Minigame._1A1E == 0) {
        if (fn_3_6C938(1, 0x200) != 0) {
            if (g_Minigame._1A3C == 0 || g_GameLogic.gameStatus == 0x28) {
                g_Minigame._1A1D = 2;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            }
        } else if ((g_GameLogic._125 >= 8 || g_GameLogic.gameStatus == 0x28) && fn_3_6C938(1, 0x100) != 0) {
            if (g_d_GameSettings.GameModeSelected == 6) {
                if (g_Minigame._1A23 == 0) {
                    g_Minigame._1A1D = 1;
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                }
            } else {
                g_Minigame._1A1D = 1;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            }
        } else if (fn_3_6C938(2, 0x20) != 0) {
            g_Minigame._1A1E = 1;
            g_Minigame._1A22 = 0;
            g_Minigame._1A1F = 0x1E;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (g_d_GameSettings.GameModeSelected == 6 && g_d_GameSettings.exhibitionMatchInd != 0) {
            if (fn_3_6C938(2, 8) != 0 && g_Minigame._1A23 == 1) {
                g_Minigame._1A23 = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            } else if (fn_3_6C938(2, 4) != 0 && g_Minigame._1A23 == 0) {
                g_Minigame._1A23 = 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            } else if (g_Minigame._1A23 == 1) {
                if (fn_3_6C938(2, 1) != 0) {
                    if (g_Minigame._1A24[0] == 0) {
                        g_Minigame._1A24[0] = 4;
                    } else {
                        g_Minigame._1A24[0]--;
                    }
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                } else if (fn_3_6C938(2, 2) != 0) {
                    if (g_Minigame._1A24[0] == 4) {
                        g_Minigame._1A24[0] = 0;
                    } else {
                        g_Minigame._1A24[0]++;
                    }
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            }
        }
    } else {
        if ((g_GameLogic._125 >= 8 || g_GameLogic.gameStatus == 0x28) && fn_3_6C938(0, 0x100) != 0) {
            g_Minigame._1A1D = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (fn_3_6C938(2, 0x220) != 0) {
            g_Minigame._1A1E = 0;
            g_Minigame._1A22 = 0;
            g_Minigame._1A1F = 0x1E;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        } else if (g_Minigame._1A21 > 1) {
            if (fn_3_6C938(2, 2) != 0) {
                if (g_Minigame._1A1E == g_Minigame._1A21) {
                    g_Minigame._1A1E = 1;
                } else {
                    g_Minigame._1A1E++;
                }
                g_Minigame._1A22 = 0;
                g_Minigame._1A1F = 0x14;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            } else if (fn_3_6C938(2, 1) != 0) {
                if (g_Minigame._1A1E == 1) {
                    g_Minigame._1A1E = g_Minigame._1A21;
                } else {
                    g_Minigame._1A1E--;
                }
                g_Minigame._1A22 = 1;
                g_Minigame._1A1F = 0x14;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
}

extern void fn_3_112BD8(void);
extern void fn_3_1160BC(void);
extern void fn_3_1324E8(void);
extern void fn_3_141A30(void);
extern void fn_3_1471C4(void);
extern void fn_3_13C468(void);
extern void fn_3_10E60C(void);
extern void fn_3_10A0A0(void);

// fn_3_10FDC8, size:0x6E0
void fn_3_10FDC8(void) {
    s32 order[4];
    s32 i;
    u8 m;

    if (g_Minigame.pauseInd != 0) {
        fn_3_1084B4();
        return;
    }
    g_GameLogic.hudElementLoadingInd = 0;
    g_GameLogic.hudLoadingRelated = 0;
    satInc16(&g_Ball.totalFramesAtPlay);
    switch (g_GameLogic.gameStatus) {
    case 27:
        fn_3_10FB74();
        break;
    case 28:
        fn_3_10F1D4();
        break;
    case 29:
        fn_3_10F3D8();
        break;
    case 30:
        fn_3_10E60C();
        break;
    case 33:
        fn_3_10B8D0();
        break;
    case 5:
        fn_3_10AEF0();
        break;
    case 35:
        for (i = 0; i < 4; i++) {
            order[i] = -1;
        }
        for (i = 0; i < 4; i++) {
            if (g_Minigame.minigameControlStruct[0].characterIndex[i] >= 0) {
                order[i] = i;
            }
        }
        fn_3_9E078(order, g_Minigame.miniGameNumberOfParticipants, 0);
        for (i = 0; i < 4; i++) {
            g_Minigame.minigameControlStruct[0].turnOrder[i] = order[i];
        }
        fn_3_5A6D4(0x1A);
        break;
    case 14:
        fn_3_10A0A0();
        break;
    case 36:
        fn_3_109254();
        break;
    case 34:
        fn_3_108C54();
        break;
    case 38:
        fn_3_10722C();
        break;
    case 40:
        fn_3_107784();
        break;
    case 41:
        switch (g_GameLogic._125) {
        case 0:
            g_Minigame.GameMode_MiniGame = g_Minigame._1E1C[g_Minigame._1E2A++];
            changeScene(1, 6);
            g_GameLogic._125 = 1;
            break;
        case 1:
            if (((MinigameTask*)MG_TASK_PTR)->_1A != 0) {
                changeScene(3, 6);
                g_GameLogic._125 = 2;
            }
            break;
        case 2:
            if (lbl_8037169C._13 != 0) {
                g_GameLogic._125 = 3;
            }
            break;
        case 3:
            g_GameLogic._125 = 4;
            break;
        case 4:
            fn_3_5A6D4(0x21);
            break;
        }
        break;
    case 39:
        fn_3_1070A4();
        break;
    case 37:
        setupMinigamePlayersInline();
        break;
    default:
        m = g_Minigame.GameMode_MiniGame;
        if (m == 1) {
            fn_3_112BD8();
        } else if (m == 2) {
            fn_3_1160BC();
        } else if (m == 3) {
            fn_3_1324E8();
        } else if (m == 4) {
            fn_3_141A30();
        } else if (m == 5) {
            fn_3_1471C4();
        } else if (m == 6) {
            fn_3_13C468();
        }
        if ((u32)g_Minigame._17C4 == 0x258) {
            fn_3_90064(0x2FD);
        }
        break;
    }
}


// NONMATCHING 90%: inlines fn_3_109DE0 (itself NONMATCHING; differences are inside that inline: base hoisting)
#if NONMATCHING
// fn_3_10952C, size:0x7BC
void fn_3_10952C(void) {
    RankEnt score;
    StatInput cur;
    StatInput* best;
    RankEnt* tbl;
    u32 rank;
    u32 i;
    u8 chara;
    s16 bestTotal;

    g_Minigame._1E03 = 5;
    if (g_Minigame._1907 != 1) {
        return;
    }
    if (!(g_Minigame._1A3C != 0 || (g_Minigame.GameMode_MiniGame != 4 && g_Minigame.GameMode_MiniGame != 5 && g_Minigame.GameMode_MiniGame != 6) ||
          g_Minigame.minigameControlStruct[0]._1C[g_Minigame._1908] == 1)) {
        return;
    }
    fn_3_109DE0(&score);
    rank = fn_3_109CE8(&score);
    g_Minigame._1E03 = rank;
    if (rank < 5) {
        tbl = fn_3_109D88_inl();
        for (i = 4; i > rank; i--) {
            memcpy(&tbl[i], &tbl[i - 1], sizeof(RankEnt));
        }
        memcpy(&tbl[rank], &score, sizeof(RankEnt));
        g_Minigame._1A43 = rank + 1;
    }
    if (g_Minigame._1A3C != 0) {
        fn_3_10754C(&cur);
        chara = lbl_800E8558[cur._14[0]]._2;
        best = &lbl_803616CC.stats[chara];
        bestTotal = fn_8006C13C(best);
        if (fn_8006C13C(&cur) > bestTotal) {
            fn_3_10754C(best);
            g_Minigame._1A46[0] = 1;
        } else {
            bestTotal = fn_8006C13C(best);
            if (fn_8006C13C(&cur) == bestTotal && cur._12 < best->_12) {
                fn_3_10754C(best);
                g_Minigame._1A46[0] = 1;
            }
        }
        if (3 - (s8)lbl_803616CC._400[chara] > cur._12) {
            lbl_803616CC._400[chara] = 3 - cur._12;
            g_Minigame._1A46[0] = 1;
        }
    }
}
#endif

extern void fn_80050FE8(s32 p0, s32 p1, s32 p2, s32 p3, s32 arg4, s32 lockMode);
extern void fn_8004FDA0(s32 id);
extern void fn_80050138(s32 byId, s32 entry0, s32 entry1, s32 entry2, s32 entry3, s32 any);
extern s16 fn_80050760(s32 p, s32 unused, s32 pressed, u16 dirs, s32 mode);
extern void fn_800506E8(s8 owner, s32 entry, s32 set);
extern void fn_3_972C8(void);
extern void fn_3_60768(void);
extern u8 lbl_803C6714[];
extern void fn_3_10CC20(void);

// NONMATCHING 95%: saved-reg numbering of the loop walkers; original passes the u8 port to fn_800506E8 without extsb (no s8 prototype)
#if NONMATCHING
// fn_3_10E60C, size:0x9A0
void fn_3_10E60C(void) {
    s32 i;
    s32 j;
    u8 port;
    u8 state;

    if (g_GameLogic._125 <= 2) {
        for (i = 0; i < 4; i++) {
            g_Minigame._19E8[i]._8 = (u8)g_Minigame._19E8[i]._7;
            g_Minigame._19E8[i]._7 = 1;
#ifdef TARGET_PC
            g_port_selLoading[i] = 0;
#endif
        }
    }
    switch (g_GameLogic._125) {
    case 0:
        for (i = 0; i < 4; i++) {
            if ((s32)(u8)g_Minigame._19DA[i] == 1) {
                g_Minigame._19DA[i] = -1;
            }
            g_Minigame.minigameControlStruct[0].aIStrength[i] = 0;
            g_Minigame._1A13[i] = 1;
        }
        if (g_Minigame._190A != 0) {
            fn_80050FE8(1, 1, 1, 1, 1, 0);
            for (i = 0; i < 0x36; i++) {
#ifdef TARGET_PC
                // Career training: only your player is offered (and picked for you, below).
                if (port_career_training_active() ? i != g_d_GameSettings._36
                                                  : (s32)starMissionCompletionTracker[i]._31 != 1) {
#else
                if ((s32)starMissionCompletionTracker[i]._31 != 1) {
#endif
                    fn_8004FDA0(i);
                }
            }
            g_Minigame._19E8[lbl_3_common_bss_37400.humanPlayer]._0 = g_d_GameSettings._36;
        } else {
            fn_80050FE8(1, 1, 1, 1, 1, 1);
            for (i = 0; i < 4; i++) {
                if (g_Minigame._19DA[i] < 0) {
                    g_Minigame._19E8[i]._0 = -1;
                }
            }
        }
        // remove duplicate character picks
        for (i = 0; i < 3; i++) {
            if (g_Minigame._19E8[i]._0 >= 0) {
                for (j = i + 1; j < 4; j++) {
                    if (g_Minigame._19E8[i]._0 == g_Minigame._19E8[j]._0) {
                        g_Minigame._19E8[j]._0 = -3;
                    }
                }
            }
        }
        fn_80050138(1, g_Minigame._19E8[0]._0, g_Minigame._19E8[1]._0, g_Minigame._19E8[2]._0,
                    g_Minigame._19E8[3]._0, 1);
        for (i = 0; i < 4; i++) {
            g_Minigame._19E8[i]._1 = 0;
            g_Minigame._19D2[i] = 0x14;
        }
        lbl_8036E548._307E = 0;
        lbl_8036E548.state = 0;
        lbl_8036E548._307A = 5;
        g_Minigame.bB_bombBarrelHitInd = -1;
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_Minigame._19DE = 0;
        g_Minigame._19E2 = 0;
        g_Minigame._19E3 = 0;
        if (g_Minigame._1A1C == 0) {
            fn_800B0A5C_insertQueue(fn_80062A94, 1);
        }
        changeScene(1, 6);
        g_GameLogic._125++;
        break;
    case 1:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            for (i = 0; i < 4; i++) {
                if (g_Minigame._19DA[i] == 0) {
                    g_Minigame._19E8[i]._0 = fn_80050760(i, 0, 0, 0, 0);
                    g_Minigame._19E8[i]._6 = 0;
                    g_Minigame.battingHandedness[i] = CHAR_STATS(g_Minigame._19E8[i]._0)->stats.FieldingArm * 2 +
                                             CHAR_STATS(g_Minigame._19E8[i]._0)->stats.BattingStance;
                    g_Minigame.minigameControlStruct[0]._08[i] = 0;
                }
            }
            changeScene(1, 6);
        }
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x1E) {
            g_Minigame._19DE = 0;
            if (g_Minigame._19E0 != 0) {
                g_Minigame._19DE = 5;
                g_Minigame._19E0 = 0;
                port = lbl_80366158._27;
                g_Minigame._19E8[port]._1 = 1;
                fn_800506E8(port, g_Minigame._19E8[port]._0, 1);
            }
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125++;
        }
        break;
    case 2:
        fn_3_10CC20();
        break;
    case 3:
        if (g_d_GameSettings.GameModeSelected == 6) {
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x14) {
                switch (fn_3_5B380(g_Controls[lbl_80366158._27].newButtonInput)) {
                case 1:
                    g_GameLogic._125 = 4;
                    g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                    break;
                case 2:
                    g_GameLogic._125 = 2;
                    break;
                }
            }
            return;
        }
        g_GameLogic._125 = 4;
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        break;
    case 4:
        if (g_Minigame._1A0C == -1) {
            if (g_d_GameSettings.GameModeSelected == 6) {
                if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x2D) {
                    changeScene(4, 6);
                }
                if (lbl_8037169C._13 != 0) {
                    g_GameLogic._125 = 5;
                }
            } else if (g_GameLogic.FrameCountOfCurrentAtBat_Copy >= 0xF) {
                fn_3_5A6D4(0x1C);
            }
        }
        lbl_8036E548._307A = 0;
        break;
    case 5:
        fn_3_972C8();
        fn_8004CC18();
        g_GameLogic.framesOfExitingToMenu = 1;
        break;
    case 6:
        if (g_Minigame._1A0F[0] < 0) {
            for (i = 0; i < 4; i++) {
                if (g_Minigame._19E8[i]._7 == 0 && (s8)g_Minigame._19E8[i]._1 != 0) {
                    break;
                }
            }
            if (i >= 4) {
                changeScene(3, 6);
                if (g_Minigame._1A3C == 0) {
                    lbl_803C6714[6] = 6;
                    g_Minigame._1A1C = 0;
                }
            }
        }
        if (lbl_8037169C._13 != 0) {
            g_GameLogic._125 = 7;
        }
        break;
    case 7:
        fn_3_60768();
        buildMinigamePlayersInline();
        lbl_8036E548._307A = 0;
        g_Minigame._1A1D = 0;
        if (g_Minigame._1A3C != 0) {
            memset(&g_Minigame._1E04, 0, 0x28);
            i = 0;
            g_Minigame._1A3D = 0;
            g_Minigame._1A3F = 0;
            lbl_8036E548._307E = 0;
            do {
                g_Minigame._1E1C[i] = i + 1;
                i++;
            } while ((u32)i < 6);
            fn_3_9DC18(g_Minigame._1E1C, 6, 0);
            fn_3_5A6D4(0x28);
        } else {
            fn_3_5A6D4(0x21);
        }
        break;
    }
    state = g_GameLogic._125;
    if (state == 3 || state == 4) {
        g_Minigame._19E8[0]._7 = 0;
        g_Minigame._19E8[1]._7 = 0;
        g_Minigame._19E8[2]._7 = 0;
        g_Minigame._19E8[3]._7 = 0;
    }
    if (state >= 2) {
        fn_3_10C81C();
    }
}
#endif

extern void fn_8004CC4C(u8 first, u8 second, u8 third, s32 selection, u16 value);
extern void fn_8004D0F0(void);
extern void fn_8004CC2C(void);
extern void fn_3_8C07C(void);
extern void fn_3_8FC0C(void);

// NONMATCHING 93%: inlines fn_3_109DE0 (itself NONMATCHING; remaining differences are inside that inline)
#if NONMATCHING
// fn_3_10A0A0, size:0xCA8
void fn_3_10A0A0(void) {
    RankEnt score;
    u32 rank;
    s32 ok;
    s32 i;
    u8 m;
    u8 v;
    u8* p;

    switch (g_GameLogic._125) {
    case 0:
        lbl_3_common_bss_32724._B8 = 0;
        g_Minigame._19A9 = 1;
        g_Minigame._19AA = 0;
        g_Minigame._1A44 = 0;
        g_Minigame._1A45 = 0;
        g_Minigame._1A43 = 0;
        g_Minigame._1A3D = 0;
        if (g_d_GameSettings.exhibitionMatchInd == 0) {
            fn_3_106ED4();
        } else if (g_Minigame.soloMinigameDifficulty == 3 || g_d_GameSettings.GameModeSelected == 6) {
            ok = 1;
            if (g_d_GameSettings.GameModeSelected == 6) {
                if (g_Minigame._1908 < 0) {
                    ok = 0;
                }
            } else {
                m = g_Minigame.GameMode_MiniGame;
                if ((m == 2 || m == 4 || m == 5 || m == 6) && g_Minigame.minigameControlStruct[0]._1C[g_Minigame._1908] > 1) {
                    ok = 0;
                }
            }
            if (ok != 0) {
                fn_3_109DE0(&score);
                rank = fn_3_109CE8(&score);
                if (rank >= 5) {
                    g_Minigame._1A43 = 0;
                } else {
                    g_Minigame._1A43 = rank + 1;
                    g_Minigame._19AA = 1;
                }
            }
        } else if (g_Minigame._1A37 == 1 && g_d_GameSettings.exhibitionMatchInd != 0 && g_Minigame.GameMode_MiniGame >= 1 && g_Minigame.GameMode_MiniGame <= 6) {
            p = &g_d_GameSettings._14[g_Minigame.GameMode_MiniGame - 1];
            if (*p == g_Minigame.soloMinigameDifficulty) {
                g_Minigame._1A44 = 1;
                (*p)++;
                for (i = 0; i < 6; i++) {
                    if (g_d_GameSettings._14[i] < 3) {
                        break;
                    }
                }
                if (i >= 6) {
                    g_Minigame._1A45 = 2;
                    g_d_GameSettings._12 = 2;
                }
            }
        }
        fn_3_8C07C();
        fn_3_5B368();
        changeScene(1, 6);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 1;
        break;
    case 1:
        g_Minigame._19A9 = 2;
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        if (g_Minigame._1A37 == 0) {
            fn_3_8FC0C();
        }
        g_GameLogic._125 = 2;
        break;
    case 2:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == lbl_3_data_2137C[1]) {
            lbl_3_common_bss_32724._B8 = 1;
        }
        if (g_Minigame._1A44 == 1) {
            if (g_GameLogic.FrameCountOfCurrentPitch > 0x12C) {
                g_GameLogic._125 = 5;
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            }
        } else if (g_Minigame._1A45 != 0) {
            if (g_GameLogic.FrameCountOfCurrentPitch > 0x12C) {
                g_GameLogic._125 = 6;
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            }
        } else if (g_GameLogic.FrameCountOfCurrentPitch > 0x12C) {
            if (g_d_GameSettings.exhibitionMatchInd == 0) {
                if (g_GameLogic.FrameCountOfCurrentPitch > 0x1A4) {
                    g_GameLogic._125 = 3;
                }
            } else if (g_Minigame.GameMode_MiniGame == 1 && g_Minigame.soloMinigameDifficulty == 3 && fn_3_6C938(0, 0x10) != 0 &&
                       fn_3_6C938(0, 0x800) != 0 && fn_3_6C938(0, 0x200) != 0) {
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                g_GameLogic._125 = 7;
            } else if (fn_3_6C938(1, 0x1100) != 0) {
                g_GameLogic._125 = 3;
            }
        }
        break;
    case 7:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x1E && fn_3_6C938(1, 0x200) != 0) {
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            g_GameLogic.FrameCountOfCurrentPitch = 0x10E;
            g_GameLogic._125 = 2;
        }
        break;
    case 5:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            v = g_d_GameSettings._14[g_Minigame.GameMode_MiniGame - 1];
            fn_8004CC4C(9, 0, v - 1, 0, v + 0x8C);
            fn_800B0A5C_insertQueue(fn_8004D0F0, 2);
            g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 0;
            fn_3_90064(0x301);
        } else if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x96) {
            if (fn_3_6C938(1, 0x1100) != 0) {
                fn_8004CC2C();
                g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 1;
            } else if (g_GameLogic.scoreBook_logoFadeDirectionLeft_Right != 0 && lbl_803C5F74.state == 4) {
                if (g_Minigame._1A45 != 0) {
                    g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                    g_GameLogic._125 = 6;
                } else {
                    g_GameLogic._125 = 3;
                }
            }
        }
        break;
    case 6:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            fn_8004CC4C(9, 0, 4, 0, 0x91);
            fn_800B0A5C_insertQueue(fn_8004D0F0, 2);
            g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 0;
        } else if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x96) {
            if (fn_3_6C938(1, 0x1100) != 0) {
                fn_8004CC2C();
                g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 1;
            } else if (g_GameLogic.scoreBook_logoFadeDirectionLeft_Right != 0 && lbl_803C5F74.state == 4) {
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                g_GameLogic._125 = 3;
            }
        }
        break;
    case 3:
        if (g_Minigame._1A44 != 0 || g_Minigame._1A45 != 0) {
            if (fn_3_5B220(1) != 0) {
                g_GameLogic._125 = 4;
            }
        } else {
            g_GameLogic._125 = 4;
        }
        break;
    case 4:
        if (g_Minigame._190A != 0) {
            g_GameLogic._125 = 9;
        } else {
            g_GameLogic._125 = 8;
        }
        fn_3_8FC0C();
        break;
    case 8:
        if (g_d_GameSettings.GameModeSelected == 6) {
            lbl_3_common_bss_34C90.subState = 0;
            if (g_Minigame._1908 >= 0) {
                fn_3_5A6D4(0x24);
            } else {
                fn_3_5A6D4(0x22);
            }
        } else if (g_Minigame.multiPlayerInd == 0 && g_Minigame._1A3C == 0 && g_Minigame.soloMinigameDifficulty == 3) {
            fn_3_5A6D4(0x24);
        } else {
            lbl_3_common_bss_34C90.state = 0;
            lbl_3_common_bss_34C90.subState = 0;
            if (g_Minigame._1A3C != 0) {
                fn_3_5A6D4(0x26);
            } else {
                fn_3_5A6D4(0x22);
            }
        }
        break;
    case 9:
        fn_800203E0(0xC, (s8)lbl_3_data_6104[gChallengeState._441C]);
        if (lbl_8037169C._13 != 0) {
            g_GameLogic._125 = 10;
        }
        break;
    case 10:
        m = g_Minigame.GameMode_MiniGame;
        if (m == 1 || m == 3) {
            if (g_Minigame._1A37 != 0) {
                g_d_GameSettings._38 = 1;
            } else {
                g_d_GameSettings._38 = 0;
            }
        } else if (g_Minigame.challenge_minigame_haven_tWonYetIndicator != 0) {
            g_d_GameSettings._38 = 0;
        } else {
            g_d_GameSettings._38 = g_Minigame.minigameControlStruct[0]._1C[g_d_GameSettings._35];
        }
        fn_3_15F998();
        fn_3_147DFC();
        fn_3_11CF84();
#ifdef TARGET_PC
        { extern void port_career_training_exit(s32 result); port_career_training_exit(g_Minigame._1A37); }
#endif
        g_GameLogic.framesOfExitingToMenu = 1;
        break;
    }
    fn_3_10A01C();
}
#endif

extern s32 fn_8004FD64(s32 player);
extern s32 fn_8004FDE8(s32 p, s32 q);
extern u32 fn_800628D4(s32 kind);
#include "main/unlock_flags.h"
extern UnlockFlags lbl_80361B20;


static inline void satIncU16(u16* p) {
    if (*p < 0xFFFE) {
        (*p)++;
    } else {
        *p = 0xFFFF;
    }
}

static inline u8 charSkinCount(s8 c) {
    return CHAR_STATS(c)->stats.FieldingArm * 2 + CHAR_STATS(c)->stats.BattingStance;
}

// Clears the character picked by slot k (unlocking it in the roster) if it was taken.
static inline void releaseSlotChar(s32 k) {
    if (g_Minigame._19E8[k]._0 >= 0) {
        if ((s32)g_Minigame._19E8[k]._1 == 1) {
            fn_800506E8(k, g_Minigame._19E8[k]._0, 0);
        }
        if (g_Minigame._19E8[k]._2 != -1) {
            g_Minigame._19E8[k]._0 = -1;
            g_Minigame._19E8[k]._2 = -1;
            g_Minigame._1A13[k] = 1;
            g_Minigame._19E8[k]._1 = 0;
        }
    }
}

// NONMATCHING 92%: original calls fn_800506E8/fn_80050760 without the s8/s16 prototypes (no extsb/extsh), plus regalloc
#if NONMATCHING
// fn_3_10CC20, size:0x19EC
void fn_3_10CC20(void) {
    s8 slotChar[4];
    u8 used[12];
    InputStruct* pads;
    InputStruct* pad;
    s32 i;
    s32 j;
    s32 k;
    s32 changed;
    s32 ready;
    s32 n;
    s32 r;
    u8 port;
    u8 maxSel;
    u8 t;
    u8 s;
    s8 c;
    s8 old;
    s16 sel;

    port = lbl_80366158._27;
    maxSel = g_d_GameSettings._14[g_Minigame.GameMode_MiniGame - 1];
    pads = g_Controls;
    pad = &pads[port];
    if (g_Minigame._190A != 0) {
        maxSel = 2;
    }
    s = g_Minigame._19DE;
    if (s == 0) {
        changed = 0;
        for (i = 0; i < 4; i++) {
            lbl_803C6028._74[i] = 0;
            slotChar[i] = -1;
            if (g_Minigame._19DA[i] == 0) {
                if (i != port && (s8)g_Minigame._19E8[i]._1 == 0 && (pads[i].newButtonInput & 0x200) &&
                    lbl_803C6028._92 != 0) {
                    g_Minigame._19DA[i] = -1;
                    g_Minigame._19E7--;
                    sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                }
            } else if (i == port) {
                g_Minigame._19DA[i] = 0;
                changed = 1;
                slotChar[i] = -3;
            } else if (g_Minigame._190A == 0 && (pads[i].newButtonInput & 0x100)) {
                g_Minigame._19DA[i] = 0;
                changed = 1;
                slotChar[i] = -3;
                g_Minigame._19E7++;
            }
        }
        if (changed != 0) {
            fn_80050138(0, slotChar[0], slotChar[1], slotChar[2], slotChar[3], 0);
        }

        ready = 0;
        for (i = 0; i < 4; i++) {
            pad = &pads[i];
            if (g_Minigame._19DA[i] != 0) {
                continue;
            }
            satIncU16((u16*)&g_Minigame._19D2[i]);
            if (slotChar[i] == -3) {
                // newly joined: put the cursor on a default character
                g_Minigame._19E8[i]._0 = fn_80050760(i, 0, 0, 0, 0);
                g_Minigame._19E8[i]._7 = 0;
                g_Minigame.battingHandedness[i] = charSkinCount(g_Minigame._19E8[i]._0);
                g_Minigame.minigameControlStruct[0]._08[i] = 0;
                if (g_d_GameSettings.exhibitionMatchInd == 0 &&
                    gChallengeState._43D6[g_Minigame._19E8[i]._0] != 0) {
                    g_Minigame.minigameControlStruct[0]._08[i] = 0;
                }
                if (i != port) {
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                }
            } else if ((s8)g_Minigame._19E8[i]._1 != 0) {
                // character locked in
                if (!(pad->newButtonInput & 0x200)) {
                    ready++;
                } else {
                    if (lbl_803C6028._92 == 0) {
                        continue;
                    }
                    g_Minigame._19E8[i]._1 = 0;
                    fn_800506E8(i, g_Minigame._19E8[i]._0, 0);
                    fn_80050760(i, 0, 0, 0, 0);
                    sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                    for (j = 0; j < 4; j++) {
                        if (i != j && g_Minigame._19DA[j] == 0) {
                            c = fn_8004FDE8(i, j);
                            if (c >= -1) {
                                g_Minigame._19E8[j]._0 = c;
                            }
                        }
                    }
                }
            } else {
#ifdef TARGET_PC
                if (((pad->newButtonInput & 0x100) || (port_career_training_active() && i == port)) &&
                    g_Minigame._19E8[i]._0 >= 0 && g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x1E) {
#else
                if ((pad->newButtonInput & 0x100) && g_Minigame._19E8[i]._0 >= 0 &&
                    g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x1E) {
#endif
                    if (g_Minigame._19E8[i]._6 != 0) {
                        sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                        goto browse;
                    }
                    if (lbl_803C6028._7F[i] < 0 &&
                        g_Minigame._19E8[i]._0 == g_Minigame._19E8[i]._2 &&
                        (s8)g_Minigame._19E8[i]._4 == (s8)g_Minigame._19E8[i]._5 &&
                        g_Minigame._19E8[i]._7 != 0 && (s8)g_Minigame._19E8[i]._8 != 0) {
                        g_Minigame._19E8[i]._1 = 1;
                        fn_800506E8(i, g_Minigame._19E8[i]._0, 1);
                        fn_800628D4(g_Minigame._19E8[i]._0);
                    }
                } else if ((pad->newButtonInput & 0x200) && g_d_GameSettings.exhibitionMatchInd != 0) {
                    if (lbl_803C6028._92 == 0) {
                        continue;
                    }
                    if (lbl_803C6028._7F[i] < 0) {
                        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                        g_GameLogic._125 = 3;
                        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                        return;
                    }
                } else {
                browse:
                    old = g_Minigame._19E8[i]._0;
                    r = fn_80050760(i, pad->buttonInput, pad->newButtonInput, pad->_08, 0);
                    if (r >= 0) {
                        g_Minigame._19E8[i]._0 = r;
                        if (old != g_Minigame._19E8[i]._0) {
                            g_Minigame._19D2[i] = 0;
                            g_Minigame.battingHandedness[i] = charSkinCount(g_Minigame._19E8[i]._0);
                            g_Minigame.minigameControlStruct[0]._08[i] = 0;
                            if (g_d_GameSettings.exhibitionMatchInd == 0 &&
                                gChallengeState._43D6[g_Minigame._19E8[i]._0] != 0) {
                                g_Minigame.minigameControlStruct[0]._08[i] = 0;
                            }
                        }
                        g_Minigame._19E8[i]._6 = 0;
                    } else {
                        g_Minigame._19E8[i]._0 = fn_8004FD64(i);
                        g_Minigame._19E8[i]._6 = 1;
                        g_Minigame._19E8[i]._7 = 0;
                    }
                }
            }
            // Z: cycle the costume
            if (g_Minigame._19E8[i]._6 == 0 && (s8)g_Minigame._19E8[i]._1 == 0 &&
                (pad->newButtonInput & 0x400)) {
                g_Minigame._19D2[i] = 0;
                g_Minigame.battingHandedness[i]++;
                if (g_Minigame.battingHandedness[i] > 3) {
                    g_Minigame.battingHandedness[i] = 0;
                }
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            if (g_Minigame._190A != 0) {
                if (gChallengeState._43D6[g_Minigame._19E8[i]._0] != 0) {
                    g_Minigame.minigameControlStruct[0]._08[i] = 1;
                } else {
                    g_Minigame.minigameControlStruct[0]._08[i] = 0;
                }
            } else if (lbl_80361B20.unlocked[g_Minigame._19E8[i]._0] != 0 && (pad->newButtonInput & 0x800)) {
                g_Minigame.minigameControlStruct[0]._08[i] ^= 1;
                if (g_Minigame.minigameControlStruct[0]._08[i] != 0) {
                    sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                } else {
                    sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                }
            }
        }

        n = g_Minigame._19E7;
        if ((u8)ready >= n) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_Minigame._19DE = 2;
            g_Minigame._19E6 = n;
            if (g_Minigame._1A3C != 0) {
                if (n == 4) {
                    g_Minigame._19DE = 7;
                } else {
                    g_Minigame._19DE = 6;
                }
                g_Minigame._19E6 = 4;
            } else if (n == 1 && g_d_GameSettings.GameModeSelected != 6) {
                g_Minigame._19DE = 5;
            } else if (n == 4) {
                g_Minigame._19DE = 7;
            } else if (g_d_GameSettings.GameModeSelected == 6 && g_d_GameSettings.exhibitionMatchInd != 0) {
                g_Minigame._19DE = 2;
                g_Minigame._19E6 = lbl_3_data_18920[g_Minigame.GameMode_MiniGame][4];
            } else {
                t = lbl_3_data_18920[g_Minigame.GameMode_MiniGame][4];
                if (n >= t) {
                    g_Minigame._19DE = 1;
                    if (g_Minigame._19E7 >= t) {
                        g_Minigame._1A0D = 0;
                    } else {
                        g_Minigame._1A0D = t - g_Minigame._19E7;
                    }
                    g_Minigame._1A0E = 4 - g_Minigame._19E7;
                    g_Minigame._19E3 = g_Minigame._1A0D;
                } else {
                    g_Minigame._19E6 = t;
                    g_Minigame._19DE = 2;
                }
            }
        }
    } else if (s == 1) {
        if (pad->newButtonInput & 0x100) {
            if ((s8)g_Minigame._19E3 != 0) {
                g_Minigame._19DE = 2;
                g_Minigame._19E6 = g_Minigame._19E3 + g_Minigame._19E7;
            } else {
                g_Minigame._19DE = 7;
            }
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pad->newButtonInput & 0x200) {
            g_Minigame._19E8[port]._1 = 0;
            fn_800506E8(port, g_Minigame._19E8[port]._0, 0);
            g_Minigame._19DE = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        } else if (pad->_08 & 8) {
            if ((s8)g_Minigame._19E3 > g_Minigame._1A0D) {
                g_Minigame._19E3--;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (pad->_08 & 4) {
            if ((s8)g_Minigame._19E3 < g_Minigame._1A0E) {
                g_Minigame._19E3++;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    } else if (s == 2 || s == 6) {
        // fill the remaining slots with CPU players
        n = g_Minigame._19E6 - g_Minigame._19E7;
        for (i = 0; i < 4; i++) {
            if (n == 0) {
                break;
            }
            if (g_Minigame._19DA[i] == -1) {
                g_Minigame._19DA[i] = 1;
                n--;
                g_Minigame._19E8[i]._0 = -1;
                g_Minigame._19E8[i]._2 = -1;
                lbl_803C6028._74[i] = 1;
            }
        }
        if (g_d_GameSettings.GameModeSelected == 6 && g_d_GameSettings.exhibitionMatchInd == 0) {
            g_Minigame._19DE = 8;
        } else if (g_Minigame._19E7 == 1 && g_d_GameSettings.GameModeSelected != 6) {
            g_Minigame._19DE = 8;
        } else {
            g_Minigame._19DE = 3;
        }
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
    } else if (s == 3) {
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            if (g_Minigame.bB_bombBarrelHitInd >= 0) {
                g_Minigame.bB_bombBarrelHitInd = -1;
            } else {
                // give each CPU slot a random character not already taken
                for (k = 0; k < 12; k++) {
                    used[k] = 0;
                }
                n = 12;
                for (i = 0; i < 4; i++) {
                    slotChar[i] = -1;
                    if ((s8)g_Minigame._19E8[i]._1 != 0) {
                        c = g_Minigame._19E8[i]._0;
                        for (k = 0; k < 12; k++) {
                            if (c == lbl_800E854C[k]) {
                                used[k] = 1;
                                n--;
                            }
                        }
                        g_Minigame._19E8[i]._0 = c;
                    }
                }
                for (i = 0; i < 4; i++) {
                    if ((s32)(u8)g_Minigame._19DA[i] == 1 && (s8)g_Minigame._19E8[i]._1 == 0) {
                        r = random_fn_3_9EE24(n);
                        for (k = 0; k < 12; k++) {
                            if (used[k] == 0) {
                                if (r == 0) {
                                    slotChar[i] = lbl_800E854C[k];
                                    fn_80050138(1, slotChar[0], slotChar[1], slotChar[2], slotChar[3], 0);
                                    g_Minigame._19E8[i]._0 = slotChar[i];
                                    g_Minigame.battingHandedness[i] = charSkinCount(slotChar[i]);
                                    g_Minigame.minigameControlStruct[0]._08[i] = 0;
                                    break;
                                }
                                r--;
                            }
                        }
                        break;
                    }
                }
            }
        } else if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x2D) {
            // the main player sets up the first CPU slot that is not locked in
            for (i = 0; i < 4; i++) {
                if ((s32)(u8)g_Minigame._19DA[i] != 1 || (s32)g_Minigame._19E8[i]._1 == 1) {
                    continue;
                }
                satIncU16((u16*)&g_Minigame._19D2[i]);
                if ((pad->newButtonInput & 0x100) && g_Minigame._19E8[i]._0 >= 0 &&
                    g_Minigame._19E8[i]._6 == 0) {
                    if (lbl_803C6028._7F[i] < 0 &&
                        g_Minigame._19E8[i]._0 == g_Minigame._19E8[i]._2 &&
                        (s8)g_Minigame._19E8[i]._4 == (s8)g_Minigame._19E8[i]._5 &&
                        g_Minigame._19E8[i]._7 != 0 && (s8)g_Minigame._19E8[i]._8 != 0) {
                        g_Minigame._19DE = 4;
                        g_Minigame.bB_bombBarrelHitInd = i;
                        g_Minigame._19E8[i]._1 = 1;
                        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                        fn_800506E8(i, g_Minigame._19E8[i]._0, 1);
                        fn_800628D4(g_Minigame._19E8[i]._0);
                    }
                } else {
                    old = g_Minigame._19E8[i]._0;
                    r = fn_80050760(i, pad->buttonInput, pad->newButtonInput, pad->_08, 0);
                    if (r >= 0) {
                        g_Minigame._19E8[i]._0 = r;
                        if (old != g_Minigame._19E8[i]._0) {
                            g_Minigame._19D2[i] = 0;
                            g_Minigame.battingHandedness[i] = charSkinCount(g_Minigame._19E8[i]._0);
                            g_Minigame.minigameControlStruct[0]._08[i] = 0;
                        }
                        g_Minigame._19E8[i]._6 = 0;
                    } else {
                        g_Minigame._19E8[i]._6 = 1;
                        g_Minigame._19E8[i]._7 = 0;
                    }
                }
                if ((pad->newButtonInput & 0x400) && g_Minigame._19E8[i]._6 == 0) {
                    g_Minigame._19D2[i] = 0;
                    g_Minigame.battingHandedness[i]++;
                    if (g_Minigame.battingHandedness[i] > 3) {
                        g_Minigame.battingHandedness[i] = 0;
                    }
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
                if (lbl_80361B20.unlocked[g_Minigame._19E8[i]._0] != 0 && (pad->newButtonInput & 0x800)) {
                    g_Minigame.minigameControlStruct[0]._08[i] ^= 1;
                    if (g_Minigame.minigameControlStruct[0]._08[i] != 0) {
                        sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                    } else {
                        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                    }
                }
                break;
            }
            if (i >= 4) {
                g_Minigame._19DE = 7;
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            } else {
                // B on a human pad: step back
                for (j = 0; j < 4; j++) {
                    if (g_Minigame._19DA[j] != 0 || !(pads[j].newButtonInput & 0x200)) {
                        continue;
                    }
                    lbl_803C6028._7F[i] = -1;
                    if (j == port) {
                        for (k = 3; k >= 0; k--) {
                            if ((s32)(u8)g_Minigame._19DA[k] == 1) {
                                if ((s8)g_Minigame._19E8[k]._1 != 0) {
                                    fn_800506E8(k, g_Minigame._19E8[k]._0, 0);
                                    g_Minigame._19E8[k]._1 = 0;
                                    break;
                                }
                                if (g_Minigame._19E8[k]._2 != -1 ||
                                    g_Minigame._19E8[k]._3 != -1) {
                                    g_Minigame._19E8[k]._0 = -1;
                                    g_Minigame._19E8[k]._2 = -1;
                                    g_Minigame._19E8[k]._7 = 0;
                                    g_Minigame._1A13[k] = 1;
                                }
                            }
                        }
                        if (k < 0) {
                            for (k = 3; k >= 0; k--) {
                                if ((s32)(u8)g_Minigame._19DA[k] == 1) {
                                    if (g_Minigame._19E8[k]._0 >= 0) {
                                        if (g_Minigame._19E8[k]._2 == -1) {
                                            g_Minigame._19E8[k]._4 = 1;
                                        } else {
                                            g_Minigame._19E8[k]._0 = -1;
                                            g_Minigame._19E8[k]._2 = -1;
                                            g_Minigame._1A13[k] = 1;
                                            g_Minigame._19E8[k]._1 = 0;
                                        }
                                    }
                                    g_Minigame._19DA[k] = -1;
                                }
                            }
                            fn_800506E8(j, g_Minigame._19E8[j]._0, 0);
                            g_Minigame._19DE = 0;
                            g_Minigame._19E8[j]._1 = 0;
                        }
                    } else {
                        fn_800506E8(j, g_Minigame._19E8[j]._0, 0);
                        g_Minigame._19DE = 0;
                        g_Minigame._19E8[j]._1 = 0;
                        for (k = 0; k < 4; k++) {
                            if ((s32)(u8)g_Minigame._19DA[k] == 1) {
                                releaseSlotChar(k);
                                g_Minigame._19DA[k] = -1;
                            }
                        }
                    }
                    sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                    return;
                }
            }
        }
    } else if (s == 4) {
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x28) {
            if (pad->newButtonInput & 0x100) {
                g_Minigame.bB_bombBarrelHitInd = -1;
                g_Minigame._19DE = 3;
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            } else if (pad->newButtonInput & 0x200) {
                sel = g_Minigame.bB_bombBarrelHitInd;
                fn_800506E8(sel, g_Minigame._19E8[sel]._0, 0);
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                g_Minigame._19E8[g_Minigame.bB_bombBarrelHitInd]._1 = 0;
                g_Minigame._19DE = 3;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            } else if (pad->_08 & 8) {
                if (g_Minigame.minigameControlStruct[0].aIStrength[g_Minigame.bB_bombBarrelHitInd] != 0) {
                    g_Minigame.minigameControlStruct[0].aIStrength[g_Minigame.bB_bombBarrelHitInd]--;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            } else if (pad->_08 & 4) {
                if (g_Minigame.minigameControlStruct[0].aIStrength[g_Minigame.bB_bombBarrelHitInd] < 3) {
                    g_Minigame.minigameControlStruct[0].aIStrength[g_Minigame.bB_bombBarrelHitInd]++;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            }
        }
    } else if (s == 5) {
        for (i = 0; i < 4; i++) {
            if (g_Minigame._19DA[i] >= 0 && (s8)g_Minigame._19E8[i]._1 != 0) {
                satIncU16((u16*)&g_Minigame._19D2[i]);
            }
        }
#ifdef TARGET_PC
        if (port_career_training_active()) {
            g_Minigame._19E4 = 1; // Career training: the Flower level
        }
#endif
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x1E) {
#ifdef TARGET_PC
            if ((pad->newButtonInput & 0x100) || port_career_training_active()) {
#else
            if (pad->newButtonInput & 0x100) {
#endif
                g_Minigame._19DE = 6;
                g_Minigame.soloMinigameDifficulty = (u8)g_Minigame._19E4;
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            } else if (pad->newButtonInput & 0x200) {
                g_Minigame._19E8[port]._1 = 0;
                fn_800506E8(port, g_Minigame._19E8[port]._0, 0);
                g_Minigame._19DE = 0;
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            } else if (pad->_08 & 1) {
                if (g_Minigame._19E4 > 0) {
                    g_Minigame._19E4--;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            } else if (pad->_08 & 2) {
                if (g_Minigame._19E4 < maxSel) {
                    g_Minigame._19E4++;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            }
            g_Minigame._19E6 = lbl_3_data_18920[g_Minigame.GameMode_MiniGame][g_Minigame._19E4];
        }
    } else if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x5A) {
        g_GameLogic._125 = 6;
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
    }

    // START on an unused pad drops all CPU players and lets that pad join (versus mode only)
    s = g_Minigame._19DE;
    if (g_d_GameSettings.exhibitionMatchInd != 0 && (s == 1 || (s >= 2 && s <= 4) || s == 5) && g_GameLogic.FrameCountOfCurrentAtBat_Copy >= 0x1E) {
        slotChar[0] = -1;
        slotChar[1] = -1;
        slotChar[2] = -1;
        slotChar[3] = -1;
        for (i = 0; i < 4; i++) {
            slotChar[i] = -1;
            if (g_Minigame._19DA[i] != 0 && (pads[i].newButtonInput & 0x100)) {
                releaseSlotChar(i);
                g_Minigame._19DA[i] = 0;
                g_Minigame._19E8[i]._0 = -1;
                g_Minigame._19E8[i]._2 = -1;
                slotChar[i] = -3;
                break;
            }
        }
        if (i < 4) {
            for (k = 0; k < 4; k++) {
                if ((s32)(u8)g_Minigame._19DA[k] == 1) {
                    releaseSlotChar(k);
                    g_Minigame._19DA[k] = -1;
                }
            }
            fn_80050138(0, slotChar[0], slotChar[1], slotChar[2], slotChar[3], 0);
            g_Minigame._19E7++;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            g_Minigame._19DE = 0;
        }
    }
}
#endif
