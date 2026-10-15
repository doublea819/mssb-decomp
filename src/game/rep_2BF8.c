#include "main/scene_task.h" // SCENE_TASK_VIEW_HEAD
#include "game/rep_2BF8.h"
#include "main/SpaniDesc.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_00097144_text.h"
#include "game/rep_720.h"
#include "main/file_80011640.h"
#include "main/file_80069BDC.h"
#define REP_HEADER_FN repHeader_2BF8
#include "header_rep_inline.h"
#include "static/GameSettings.h"

// Sprite layouts and frame tables of the minigame results boards. The original
// reaches them as file statics through one pooled base.
static SpaniDesc lbl_3_data_19770[6] = { // results board (fn_3_ED784 / fn_3_ECD48)
    {0, 10, 0.0f, 0.0f, -1, 1, 9, 255, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 11, 0.0f, 0.0f, -1, 0, 7, 255, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 12, 0.0f, 0.0f, -1, 0, 7, 255, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 13, 0.0f, 0.0f, -1, 0, 7, 255, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 14, 0.0f, 0.0f, -1, 0, 7, 255, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
static SpaniDesc lbl_3_data_19830[7] = {
    {0, 1, 0.0f, 0.0f, -1, 1, 9, 255, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 103, 0.0f, 0.0f, -1, 0, 7, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 2, 0.0f, 0.0f, -1, 1, 7, 1, 14, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 2, 0.0f, 0.0f, -1, 1, 7, 1, 14, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 2, 0.0f, 0.0f, -1, 1, 7, 1, 14, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 2, 0.0f, 0.0f, -1, 1, 7, 1, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
static SpaniDesc lbl_3_data_19910[3] = { // fn_3_EC804
    {0, 17, 0.0f, 0.0f, -1, 1, 7, 255, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 15, 0.0f, 0.0f, -1, 1, 7, 0, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
static u16 lbl_3_data_19970[4] = {17, 18, 19, 20}; // fn_3_EC804: anim per stadium kind
static u16 lbl_3_data_19978[4] = {135, 135, 135, 135}; // stop frame
static u16 lbl_3_data_19980[4] = {190, 190, 190, 190}; // end frame
static SpaniDesc lbl_3_data_19988[16] = {
    {0, 27, 0.0f, 0.0f, -1, 1, 7, 255, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 30, 0.0f, 0.0f, -1, 0, 7, 0, 14, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 30, 0.0f, 0.0f, -1, 0, 7, 0, 14, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 30, 0.0f, 0.0f, -1, 0, 7, 0, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 28, 0.0f, 0.0f, -1, 1, 7, 255, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 26, 0.0f, 0.0f, -1, 0, 7, 1, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 26, 0.0f, 0.0f, -1, 0, 7, 2, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 26, 0.0f, 0.0f, -1, 0, 7, 3, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 26, 0.0f, 0.0f, -1, 0, 7, 1, 14, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 26, 0.0f, 0.0f, -1, 0, 7, 2, 14, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 26, 0.0f, 0.0f, -1, 0, 7, 3, 14, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 29, 0.0f, 0.0f, -1, 1, 7, 255, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 23, 0.0f, 0.0f, -1, 1, 7, 255, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 25, 0.0f, 0.0f, -1, 0, 7, 255, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 24, 0.0f, 0.0f, -1, 0, 7, 13, 14, {0, 0, 0}, 0.0f, 0, 1, 0},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
static u16 lbl_3_data_19B88[8] = {0, 1, 2, 3, 4, 6, 7, 5}; // symbol -> sprite frame
static SpaniDesc lbl_3_data_19B98[46] = {
    {0, 113, 0.0f, 0.0f, -1, 0, 7, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 75, 0.0f, 0.0f, -1, 0, 7, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 75, 0.0f, 0.0f, -1, 0, 7, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 75, 0.0f, 0.0f, -1, 0, 7, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 75, 0.0f, 0.0f, -1, 0, 7, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 92, 0.0f, 0.0f, -1, 0, 7, 1, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 92, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 92, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 92, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 96, 0.0f, 0.0f, -1, 0, 7, 1, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 96, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 96, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 96, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 131, 0.0f, 0.0f, -1, 0, 7, 9, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 131, 0.0f, 0.0f, -1, 0, 7, 10, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 131, 0.0f, 0.0f, -1, 0, 7, 11, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 131, 0.0f, 0.0f, -1, 0, 7, 12, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 98, 0.0f, 0.0f, -1, 0, 7, 1, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 98, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 98, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 98, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 95, 0.0f, 0.0f, -1, 0, 7, 1, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 95, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 95, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 95, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 1, 3, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 1, 3, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 1, 3, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 1, 3, {0, 0, 0}, 0.0f, 0, 1, 7},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 7},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 7},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 7},
    {0, 93, 0.0f, 0.0f, -1, 1, 7, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 93, 0.0f, 0.0f, -1, 1, 7, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 93, 0.0f, 0.0f, -1, 1, 7, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 93, 0.0f, 0.0f, -1, 1, 7, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
static u16 lbl_3_data_1A158[4][2] = {{108, 107}, {110, 109}, {112, 111}, {114, 113}}; // [numPlayers - 1][batting side]
static SpaniDesc lbl_3_data_1A168[46] = {
    {0, 103, 0.0f, 0.0f, -1, 1, 7, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 99, 0.0f, 0.0f, -1, 0, 7, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 99, 0.0f, 0.0f, -1, 0, 7, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 99, 0.0f, 0.0f, -1, 0, 7, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 99, 0.0f, 0.0f, -1, 0, 7, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 85, 0.0f, 0.0f, -1, 0, 7, 1, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 85, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 85, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 85, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 92, 0.0f, 0.0f, -1, 0, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 92, 0.0f, 0.0f, -1, 0, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 92, 0.0f, 0.0f, -1, 0, 7, 7, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 92, 0.0f, 0.0f, -1, 0, 7, 8, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 96, 0.0f, 0.0f, -1, 0, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 96, 0.0f, 0.0f, -1, 0, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 96, 0.0f, 0.0f, -1, 0, 7, 7, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 96, 0.0f, 0.0f, -1, 0, 7, 8, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 131, 0.0f, 0.0f, -1, 0, 7, 13, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 131, 0.0f, 0.0f, -1, 0, 7, 14, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 131, 0.0f, 0.0f, -1, 0, 7, 15, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 131, 0.0f, 0.0f, -1, 0, 7, 16, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 98, 0.0f, 0.0f, -1, 0, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 98, 0.0f, 0.0f, -1, 0, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 98, 0.0f, 0.0f, -1, 0, 7, 7, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 98, 0.0f, 0.0f, -1, 0, 7, 8, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 95, 0.0f, 0.0f, -1, 0, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 95, 0.0f, 0.0f, -1, 0, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 95, 0.0f, 0.0f, -1, 0, 7, 7, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 95, 0.0f, 0.0f, -1, 0, 7, 8, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 7, 3, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 7, 3, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 7, 3, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 8, 3, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 8, 3, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 8, 3, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 93, 0.0f, 0.0f, -1, 1, 7, 1, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 93, 0.0f, 0.0f, -1, 1, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 93, 0.0f, 0.0f, -1, 1, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 93, 0.0f, 0.0f, -1, 1, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
static u16 lbl_3_data_1A728[4] = {103, 104, 105, 106};
static SpaniDesc lbl_3_data_1A730[22] = {
    {0, 103, 0.0f, 0.0f, -1, 0, 7, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 87, 0.0f, 0.0f, -1, 0, 7, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 87, 0.0f, 0.0f, -1, 0, 7, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 87, 0.0f, 0.0f, -1, 0, 7, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 87, 0.0f, 0.0f, -1, 0, 7, 0, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 86, 0.0f, 0.0f, -1, 0, 7, 1, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 86, 0.0f, 0.0f, -1, 0, 7, 1, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 86, 0.0f, 0.0f, -1, 0, 7, 1, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 86, 0.0f, 0.0f, -1, 0, 7, 1, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 86, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 86, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 86, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 86, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 86, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 86, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 86, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 86, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 86, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 86, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 86, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 86, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
static SpaniDesc lbl_3_data_1A9F0[44] = { // fn_3_EA454
    {0, 33, 0.0f, 0.0f, -1, 1, 7, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 37, 0.0f, 0.0f, -1, 1, 7, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 42, 0.0f, 0.0f, -1, 1, 7, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 41, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 41, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 41, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 41, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 46, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 46, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 46, 0.0f, 0.0f, -1, 0, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 46, 0.0f, 0.0f, -1, 0, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 98, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 98, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 98, 0.0f, 0.0f, -1, 0, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 98, 0.0f, 0.0f, -1, 0, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 83, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 83, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 83, 0.0f, 0.0f, -1, 0, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 83, 0.0f, 0.0f, -1, 0, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 382, 0.0f, 0.0f, -1, 1, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 383, 0.0f, 0.0f, -1, 1, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 384, 0.0f, 0.0f, -1, 1, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 385, 0.0f, 0.0f, -1, 1, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 95, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 95, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 95, 0.0f, 0.0f, -1, 0, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 95, 0.0f, 0.0f, -1, 0, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 7},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 8},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 7},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 8},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 7},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 8},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 7},
    {0, 100, 0.0f, 0.0f, -1, 1, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 8},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
static u16 lbl_3_data_1AF70[8] = {33, 27, 28, 29, 31, 30, 32, 0}; // title per game
static u16 lbl_3_data_1AF80[4] = {37, 38, 39, 40};
static u16 lbl_3_data_1AF88[4] = {34, 35, 36, 0};
static u16 lbl_3_data_1AF90[4] = {42, 43, 44, 45}; // [numPlayers - 1]
static u16 lbl_3_data_1AF98[8] = {6, 0, 1, 2, 4, 3, 5, 0}; // frame per game
static u16 lbl_3_data_1AFA8[4] = {382, 383, 384, 385}; // per rank
static SpaniDesc lbl_3_data_1AFB0[65] = { // results board (fn_3_E911C)
    {0, 367, 0.0f, 0.0f, -1, 1, 7, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 366, 0.0f, 0.0f, -1, 1, 7, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 387, 0.0f, 0.0f, -1, 0, 7, 255, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 386, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 386, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 386, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 386, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 380, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 380, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 380, 0.0f, 0.0f, -1, 0, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 380, 0.0f, 0.0f, -1, 0, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 381, 0.0f, 0.0f, -1, 1, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 381, 0.0f, 0.0f, -1, 1, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 381, 0.0f, 0.0f, -1, 1, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 381, 0.0f, 0.0f, -1, 1, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 131, 0.0f, 0.0f, -1, 0, 7, 11, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 131, 0.0f, 0.0f, -1, 0, 7, 11, 1, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 131, 0.0f, 0.0f, -1, 0, 7, 12, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 131, 0.0f, 0.0f, -1, 0, 7, 12, 1, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 131, 0.0f, 0.0f, -1, 0, 7, 13, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 131, 0.0f, 0.0f, -1, 0, 7, 13, 1, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 131, 0.0f, 0.0f, -1, 0, 7, 14, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 131, 0.0f, 0.0f, -1, 0, 7, 14, 1, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 375, 0.0f, 0.0f, -1, 1, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 376, 0.0f, 0.0f, -1, 1, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 377, 0.0f, 0.0f, -1, 1, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 373, 0.0f, 0.0f, -1, 1, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 374, 0.0f, 0.0f, -1, 1, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 382, 0.0f, 0.0f, -1, 1, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 383, 0.0f, 0.0f, -1, 1, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 384, 0.0f, 0.0f, -1, 1, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 385, 0.0f, 0.0f, -1, 1, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 98, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 98, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 98, 0.0f, 0.0f, -1, 0, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 98, 0.0f, 0.0f, -1, 0, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 100, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 100, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 7},
    {0, 100, 0.0f, 0.0f, -1, 0, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 8},
    {0, 100, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 100, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 7},
    {0, 100, 0.0f, 0.0f, -1, 0, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 8},
    {0, 100, 0.0f, 0.0f, -1, 0, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 100, 0.0f, 0.0f, -1, 0, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 7},
    {0, 100, 0.0f, 0.0f, -1, 0, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 8},
    {0, 100, 0.0f, 0.0f, -1, 0, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 100, 0.0f, 0.0f, -1, 0, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 7},
    {0, 100, 0.0f, 0.0f, -1, 0, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 8},
    {0, 378, 0.0f, 0.0f, -1, 1, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 9},
    {0, 378, 0.0f, 0.0f, -1, 1, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 9},
    {0, 378, 0.0f, 0.0f, -1, 1, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 9},
    {0, 378, 0.0f, 0.0f, -1, 1, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 9},
    {0, 379, 0.0f, 0.0f, -1, 1, 7, 3, 3, {0, 0, 0}, 0.0f, 0, 1, 10},
    {0, 379, 0.0f, 0.0f, -1, 1, 7, 4, 3, {0, 0, 0}, 0.0f, 0, 1, 10},
    {0, 379, 0.0f, 0.0f, -1, 1, 7, 5, 3, {0, 0, 0}, 0.0f, 0, 1, 10},
    {0, 379, 0.0f, 0.0f, -1, 1, 7, 6, 3, {0, 0, 0}, 0.0f, 0, 1, 10},
    {0, 370, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 370, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 370, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 370, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 371, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 371, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 371, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 371, 0.0f, 0.0f, -1, 0, 7, 2, 3, {0, 0, 0}, 0.0f, 0, 1, 0},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
static u16 lbl_3_data_1B7D0[4] = {375, 376, 377, 373}; // per rank

// Layout object (LayoutObj in main/file_8000F150.h), only the fields used here.
typedef struct ResultsSprite {
    /*0x00*/ void* _00[3]; // three pointers (GameCube: 0xC bytes; PC: the fields below sit later)
    /*0x0C*/ u8 _0C[0x54 - 0x0C];
    /*0x54*/ u32 flags;
    /*0x58*/ u8 _58[0x4];
    /*0x5C*/ u32 frame; // 16.16
    /*0x60*/ u8 _60[0x4];
    /*0x64*/ u16 anim;
    /*0x66*/ u8 _66[2];
    /*0x68*/ u8 visible;
    /*0x69*/ u8 animState;
} ResultsSprite;

extern u8 lbl_800EFBA4[];
extern u16 lbl_3_data_81DC[];
extern u16 lbl_3_data_81FC[];
extern u8 lbl_3_data_8404[]; // [stadium][0x1E]
extern u8 lbl_3_data_84B8[];

extern void fn_80034E20(void*, void*);
extern void fn_3_1079C8(u8* out, s32 mode);
extern u32 fn_3_90064(s32 id);
extern s32 fn_3_125424(u8* a, s32 i, u32 v);
extern u32 sndFXCtrl(int, int, u8);
extern s32 sndFXStartEx(u16, u8, u8, u8);

#define SPRITE(task, n) ((ResultsSprite*)lbl_80371C30[(task)->baseIdx + (n)].obj)

// Screen-edge limits of the off-screen player markers (lbl_3_data_D638).
typedef struct MarkerEdges {
    /*0x0*/ s16 leftFade;  // fade in from here ...
    /*0x2*/ s16 left;      // ... to here, and clamp to it
    /*0x4*/ s16 rightFade;
    /*0x6*/ s16 right;
    /*0x8*/ s16 topFade;
    /*0xA*/ s16 top;
    /*0xC*/ s16 bottomFade;
    /*0xE*/ s16 bottom;
} MarkerEdges;

extern MarkerEdges lbl_3_data_D638;
extern u16 lbl_3_data_91AC[]; // marker rotation per screen-edge direction (see fn_3_E9D30)

extern const f32 lbl_3_rodata_2C48; // 0.2f
extern const f32 lbl_3_rodata_2C4C; // 255.0f
extern const f32 lbl_3_rodata_2C50; // 1.0f

#define MARKER(task, i) (lbl_80371C30[(task)->u14.objIdx + (i)].obj)

static inline s32 fadeAlpha(s32 v, s32 from, s32 to) {
    return lbl_3_rodata_2C4C * (lbl_3_rodata_2C50 - (f32)(v - from) / (f32)(to - from));
}


typedef struct {
    void* fn;
    SCENE_TASK_VIEW_LINKS
    u16 u14;
    u16 u16_;
    u16 u18;
    u16 u1A;
    u16 u1C;
    u16 u1E;
} QObj;
extern SpaniDesc lbl_3_data_8EC4[3];
extern SpaniDesc lbl_3_data_900C[13];
extern void fn_3_E9D30(void);
extern u8 lbl_800EF808[];
extern void fn_3_9C28C(void);
extern void fn_3_9894C(void);
extern void fn_3_98DE0(void);
extern void fn_3_EA8FC(void);
extern void fn_3_EB6E0(void);
extern void fn_3_129458(void);
extern void fn_3_9143C(void);
extern void fn_3_96914(void);
extern void fn_3_97144(void);
extern void fn_3_EAEF4(void);
extern void fn_3_EDA3C(void);
extern void fn_3_1254F8(void);
extern void fn_3_126604(void);
extern void fn_3_1274B4(void);
extern void fn_3_128B90(void);
extern void fn_3_E911C(void);
extern void fn_3_12C3F0(void);
extern void fn_3_12B7A0(void);
extern void fn_3_12A6C4(void);
extern void fn_80053FE8(void);
extern void fn_80051D00(void);
extern void fn_8004D0F0(void);
extern s32 fn_80050F78(s32);
extern SpaniDesc lbl_3_data_8FCC[2];
extern SpaniDesc lbl_3_data_8F64[3];
extern u16 lbl_3_data_8FC4[];
extern u16 lbl_3_data_81DC[];
extern u8 lbl_3_data_8404[];
extern u8 lbl_3_data_84B8[];
extern u32 sndFXCtrl(int, int, u8);
extern s32 sndFXStartEx(u16, u8, u8, u8);
extern SpaniDesc lbl_3_data_8F24[2];
extern SpaniDesc lbl_3_data_8E68[2];
extern u8 lbl_3_data_8EA8[];
extern void fn_80034E20(void*, void*);
extern void fn_3_ED2F4(void);
extern void fn_3_ED0F4(void);
extern void fn_3_EC014(void);
extern void fn_3_ED6E0(void);

// Typed views for the functions below. ((u8*)&g_Minigame), ((u8*)&lbl_80371C30) and
// lbl_803CC1B8 are declared as raw bytes in this file (the older functions
// index them by offset), so the newer code reaches them through these.
typedef struct EaSprite {
    /*0x00*/ void* _00[3]; // three pointers (GameCube: 0xC bytes; PC: the fields below sit later)
    /*0x0C*/ u8 _0C[0x48 - 0x0C];
    /*0x48*/ f32 x;
    /*0x4C*/ f32 y;
    /*0x50*/ u8 _50[0x4];
    /*0x54*/ u32 flags;
    /*0x58*/ u32 color;
    /*0x5C*/ u32 frame; // 16.16
    /*0x60*/ u8 _60[0x4];
    /*0x64*/ u16 anim;
    /*0x66*/ u8 _66[2];
    /*0x68*/ u8 visible;
    /*0x69*/ u8 animState;
} EaSprite;
#ifdef TARGET_PC
#include "main/file_8000F150.h"
#include <stddef.h>
_Static_assert(offsetof(EaSprite, anim) == offsetof(LayoutObj, _64), "EaSprite view");
_Static_assert(offsetof(EaSprite, x) == offsetof(LayoutObj, x), "EaSprite view");
_Static_assert(offsetof(ResultsSprite, frame) == offsetof(LayoutObj, _5C), "ResultsSprite view");
#endif

typedef struct EaSlot {
    /*0x0*/ EaSprite* obj;
    /*0x4*/ u32 _04;
} EaSlot;

// Minigame HUD task (queue item).
typedef struct EaTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ SCENE_TASK_VIEW_LINKS
    /*0x14*/ u16 baseIdx;
    /*0x16*/ u16 _16;
    /*0x18*/ u16 param; // set by the creator
    /*0x1A*/ u16 _1A;
    /*0x1C*/ u16 state;
    /*0x1E*/ u16 _1E; // fn_3_EB6E0: first player in turn order
    /*0x20*/ u16 _20; // fn_3_EB6E0: title sub-state
    /*0x22*/ u16 _22;
    /*0x24*/ u8 pending[4];
} EaTask;

// g_Minigame (MiniGameStruct in game/UnknownHomes_Game.h), only the fields used here.
typedef struct EaMinigame {
    /*0x0000*/ u8 _0000[0x1890];
    /*0x1890*/ s16 points[4]; // miniGameCurrentPoints
    /*0x1898*/ u8 _1898[0x18BC - 0x1898];
    /*0x18BC*/ struct {
        s16 shown; // displayed score, counts towards points[]
        s16 delta;
    } _18BC[4];
    /*0x18CC*/ s8 characterIndex[4]; // minigameControlStruct[0]
    /*0x18D0*/ u8 _18D0[0x18E0 - 0x18D0];
    /*0x18E0*/ s8 order[4];
    /*0x18E4*/ u8 _18E4[0x18F4 - 0x18E4];
    /*0x18F4*/ s8 player[3];
    /*0x18F7*/ u8 _18F7[0x1906 - 0x18F7];
    /*0x1906*/ u8 numPlayers;
    /*0x1907*/ u8 _1907[2];
    /*0x1909*/ u8 _1909;
    /*0x190A*/ u8 _190A;
    /*0x190B*/ u8 _190B;
    /*0x190C*/ u8 turn;
    /*0x190D*/ u8 _190D[0x1921 - 0x190D];
    /*0x1921*/ u8 _1921;
    /*0x1922*/ u8 _1922[0x1927 - 0x1922];
    /*0x1927*/ u8 reelStop[3];  // slot reels (fn_3_EC014)
    /*0x192A*/ u8 reelPos[3];
    /*0x192D*/ u8 reelResult;
    /*0x192E*/ u8 reelTarget[3];
    /*0x1931*/ u8 reelState[3];
    /*0x1934*/ u8 _1934;
    /*0x1935*/ u8 _1935[0x1939 - 0x1935];
    /*0x1939*/ u8 _1939;
    /*0x193A*/ u8 _193A[0x19A0 - 0x193A];
    /*0x19A0*/ u8 _19A0; // a score is still counting
    /*0x19A1*/ u8 _19A1[0x19C6 - 0x19A1];
    /*0x19C6*/ s8 _19C6;
    /*0x19C7*/ u8 _19C7[0x19CD - 0x19C7];
    /*0x19CD*/ u8 _19CD;
    /*0x19CE*/ u8 _19CE;
    /*0x19CF*/ u8 _19CF[0x1A2A - 0x19CF];
    /*0x1A2A*/ u8 game;  // indexes the per-game tables
    /*0x1A2B*/ u8 _1A2B;
    /*0x1A2C*/ u8 _1A2C[0x1A3C - 0x1A2C];
    /*0x1A3C*/ u8 _1A3C;
    /*0x1A3D*/ u8 _1A3D[0x1DF4 - 0x1A3D];
    /*0x1DF4*/ u8 marks[4];
} EaMinigame;

#define EA_MG (*(EaMinigame*)&g_Minigame)
#define EA_TASK ((EaTask*)lbl_803CC1B8)
#define EA_SPRITE(task, n) (((EaSlot*)&lbl_80371C30)[(task)->baseIdx + (n)].obj)
// Same for an already computed slot index (the matched code scales the whole index).
#define EA_SLOT_OBJ(i) (*(EaSprite**)((u8*)&lbl_80371C30 + (i) * sizeof(EaSlot)))
// Character id of roster entry i, counting through both teams (inMemRoster[2][9] flattened).
#define EA_CHAR_ID(i) ((&inMemRoster[0][0])[i].stats.CharID)

extern void fn_3_ED058(void);


extern s16 lbl_80109410[]; // per-game score cap
extern void fn_3_1079C8(u8* out, s32 mode);
extern s32 fn_3_107C40(void);

// Entry filled by fn_3_1079C8: a player and its placing.
typedef struct EaOrder {
    /*0x0*/ u8 player;
    /*0x1*/ u8 rank;
} EaOrder;

extern u8 lbl_800EFBA4[];
extern u8 fn_3_107CD0(void);
extern s32 fn_3_107C88(void);

// Slot-reel task (fn_3_EC014); same header as EaTask.
typedef struct EaReelTask {
    /*0x00*/ SCENE_TASK_VIEW_HEAD // SceneTask head (main/scene_task.h)
    /*0x14*/ u16 baseIdx;
    /*0x16*/ u8 _16[0x1C - 0x16];
    /*0x1C*/ u16 state;
    /*0x1E*/ u8 _1E[0x24 - 0x1E];
    /*0x24*/ s32 voice; // looping reel sound, -1 when off
} EaReelTask;

extern s16 lbl_3_data_189C4[][7]; // reel symbols

extern u8 lbl_8037169C[];     // SceneFade in main/file_8001FE00.h
extern u32 fn_3_12536C(void);

// fn_3_EDD10, size:0x29C
void fn_3_EDD10(void) {
    if (g_GameLogic.gameStatus == 0x1C || (u8)(g_GameLogic.gameStatus - 0x1D) <= 3 || g_GameLogic.gameStatus == 0x21) {
        fn_3_EDA3C();
        return;
    }
    lbl_3_common_bss_32724._DA = 0;
    fn_3_97144();
    fn_3_96914();
    fn_3_ED818();
    fn_3_9143C();
    if (g_Minigame.framesSincePanelHit == 1) {
        fn_800B0A5C_insertQueue(fn_3_ED784, 2);
    }
    if (g_Minigame.panelHitInd != 0 && lbl_3_common_bss_32724._D6 == 0 && g_GameLogic.gameStatus == 2) {
        ((QObj*)fn_800B0A5C_insertQueue(fn_3_EA8FC, 2))->u18 = 1;
        fn_800B0A5C_insertQueue(fn_3_EAEF4, 2);
    }
    if (g_Minigame._19CE != 0 && g_Minigame._19BA == 1) {
        fn_800B0A5C_insertQueue(fn_3_ED2A8, 2);
    }
    if (g_GameLogic.gameStatus == 0xE || g_GameLogic.gameStatus == 0x22) {
        fn_3_129458();
    }
    if (g_GameLogic.gameStatus == 5) {
        if (g_Minigame._1E02 == 0) {
            fn_800B0A5C_insertQueue(fn_3_1254F8, 2);
        }
    } else if (g_GameLogic.gameStatus == 0x22) {
        if (lbl_3_common_bss_34C90.state == 1) {
            fn_800B0A5C_insertQueue(fn_3_9894C, 2);
        }
    } else if (g_GameLogic.gameStatus == 3) {
        if (g_GameLogic._125 == 0 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
            ((QObj*)fn_800B0A5C_insertQueue(fn_3_E911C, 2))->u18 = 0;
        }
    } else if (g_GameLogic.gameStatus == 0x24) {
        if (g_GameLogic._125 == 5 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
            fn_800B0A5C_insertQueue(fn_3_1274B4, 2);
        }
    } else if (g_GameLogic.gameStatus == 9) {
    } else if (g_GameLogic.gameStatus == 0xD) {
        if (lbl_3_common_bss_34C90.state == 2) {
            fn_800B0A5C_insertQueue(fn_3_128B90, 2);
        }
    } else if (g_GameLogic.gameStatus == 0xB) {
        if (lbl_3_common_bss_34C90.state == 8 && lbl_3_common_bss_34C90._1D4 == 2) {
            fn_800B0A5C_insertQueue(fn_3_126604, 2);
        }
    }
}

// fn_3_EDA3C, size:0x2D4
void fn_3_EDA3C(void) {
    if (g_GameLogic.gameStatus >= 0x1C && g_GameLogic.gameStatus <= 0x20 && lbl_3_common_bss_32724._D9 == 0 && g_GameLogic.framesOfExitingToMenu == 0) {
        fn_800B0A5C_insertQueue(fn_3_12C3F0, 2);
        fn_800B0A5C_insertQueue(fn_80053FE8, 2);
        lbl_8034E978.menu = 0x2E;
        lbl_8034E978.prevTrack = lbl_8034E978.track;
        lbl_8034E978.track = lbl_800FEF70[0x2E].track;
    }
    if (g_GameLogic.gameStatus == 0x1E) {
        if (g_GameLogic._125 == 1 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
            if (lbl_3_common_bss_32724._DC == 0) {
                fn_800B0A5C_insertQueue(fn_80051D00, 2);
                lbl_3_common_bss_32724._DC = 1;
            }
            if (lbl_3_common_bss_32724._DA != 1) {
                fn_800B0A5C_insertQueue(fn_3_12B7A0, 2);
            }
        }
        if (g_GameLogic._125 == 2) {
            if (lbl_3_common_bss_32724._DC == 0 && g_Minigame._19DE != 5 && g_Minigame._19DE != 8) {
                fn_800B0A5C_insertQueue(fn_80051D00, 2);
                lbl_3_common_bss_32724._DC = 1;
            }
            if (g_Minigame._19DE == 1 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
                fn_800B0A5C_insertQueue(fn_3_12A6C4, 2);
            }
        }
        if (g_GameLogic._125 == 7) {
            fn_80050F78(1);
            lbl_3_common_bss_32724._DC = 0;
        }
        if (g_GameLogic._125 == 3 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            fn_8004CC4C(0, 1, 1, 0, 0x89);
            fn_800B0A5C_insertQueue(fn_8004D0F0, 2);
        }
        if (g_GameLogic._125 == 5) {
            fn_80050F78(1);
        }
    } else if (g_GameLogic.gameStatus == 0x21) {
        if (g_GameLogic._125 == 2 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            fn_800B0A5C_insertQueue(fn_3_126604, 2);
            lbl_8034E978.menu = 0x32;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[0x32].track;
            if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_32724._D9 == 0) {
                fn_800B0A5C_insertQueue(fn_3_12C3F0, 2);
            }
        }
    }
}

// fn_3_ED818, size:0x224
void fn_3_ED818(void) {
    if (g_GameLogic.hudElementLoadingInd != 0 && lbl_3_common_bss_32724._A5 == 0) {
        lbl_3_common_bss_32724._A5 = 1;
        lbl_3_common_bss_32724._A6 = 0;
        lbl_3_common_bss_32724._A7 = 0xFF;
        fn_800B0A5C_insertQueue(fn_3_9C28C, 2);
        ((QObj*)fn_800B0A5C_insertQueue(fn_3_EA8FC, 2))->u18 = 0;
        fn_800B0A5C_insertQueue(fn_3_EB6E0, 2);
    }
    if (g_Ball.totalFramesAtPlay == 0xF && g_Minigame.toyfield_waitFor_CoinsX2_AnimationToEnd == 0 && g_Minigame.toyField_pointMultiplier > 1 && g_Pitcher.nPitchesThisAB == 0) {
        fn_800B0A5C_insertQueue(fn_3_ED490, 2);
    }
    if (lbl_3_common_bss_32724._A5 != 0 && lbl_3_common_bss_32724._A6 < 0xFF) {
        if (lbl_3_common_bss_32724._A6 < 0xF0) {
            lbl_3_common_bss_32724._A6 = lbl_3_common_bss_32724._A6 + 0x10;
        } else {
            lbl_3_common_bss_32724._A6 = 0xFF;
        }
    }
    if (lbl_3_common_bss_32724._A7 != 0 && lbl_3_common_bss_32724._A7 < 0xFF) {
        if (lbl_3_common_bss_32724._A7 <= 0x10) {
            lbl_3_common_bss_32724._A7 = 0;
            lbl_3_common_bss_32724._A5 = 0;
        } else {
            lbl_3_common_bss_32724._A7 = lbl_3_common_bss_32724._A7 - 0x10;
        }
    } else if (lbl_3_common_bss_32724._A5 != 0) {
        if (g_GameLogic.gameStatus == 8) {
            lbl_3_common_bss_32724._A7 = 0;
            lbl_3_common_bss_32724._A5 = 0;
        } else if (g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 0 && g_GameLogic.gameStatus != 0xB && g_GameLogic.gameStatus != 0xD) {
            lbl_3_common_bss_32724._A7 = 0xF0;
        }
    }
    if (g_GameLogic.gameStatus == 0xB && lbl_3_common_bss_34C90.state == 1) {
        fn_800B0A5C_insertQueue(fn_3_9894C, 2);
        if (lbl_3_common_bss_32724.pauseTitleShown == 0) {
            fn_800B0A5C_insertQueue(fn_3_98DE0, 2);
        }
    }
}

// fn_3_ED784, size:0x94
void fn_3_ED784(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    if (g_Minigame.toyFieldBallStateResult2 == 0xB) {
        *(void**)p = fn_3_EC014;
    } else {
        s32 v = ((s16*)lbl_3_data_8EA8)[g_Minigame.toyFieldBallStateResult2];
        if (v < 0) {
            fn_800B0A14_removeQueue(p);
        } else {
            lbl_3_data_8E68[0].animId = (s16)v;
            fn_80034E20(p, lbl_3_data_8E68);
            lbl_803CC1B8->func = fn_3_ED6E0;
        }
    }
}

// fn_3_ED6E0, size:0xA4
void fn_3_ED6E0(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    if (lbl_3_common_bss_32724.hudOff != 0 || ((EaSlot*)&lbl_80371C30)[p->u14].obj->animState == 2 || g_GameLogic.gameStatus == 8) {
        if (g_Minigame._1921 != 0) {
            fn_800B0A5C_insertQueue(fn_3_ED0F4, 2);
        }
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
    }
}

// fn_3_ED574, size:0x16C
void fn_3_ED574(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    s32 v;
    fn_80034E20(p, lbl_3_data_8EC4);
    fn_800363D8(p, 1, 6, 0x4A, g_Minigame.toyField_selectedTurns % 10);
    fn_800363D8(p, 1, 5, 0x4A, g_Minigame.toyField_selectedTurns / 10);
    v = g_Minigame.toyField_turnNumber;
    if (v > g_Minigame.toyField_selectedTurns) {
        v = g_Minigame.toyField_selectedTurns;
    }
    fn_800363D8(p, 1, 2, 0x4A, v % 10);
    if (v >= 10) {
        fn_800363D8(p, 1, 1, 0x4A, v / 10);
    } else {
        fn_800363D8(p, 1, 1, 0x4A, 10);
    }
    lbl_803CC1B8->func = fn_3_ED4FC;
}

// fn_3_ED4FC, size:0x78
void fn_3_ED4FC(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    if (lbl_3_common_bss_32724.hudOff != 0 || g_GameLogic.hudLoadingRelated != 0 || g_GameLogic.gameStatus == 3 || g_GameLogic.gameStatus == 0xE || g_GameLogic.secondaryGameMode == 0xA) {
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
    }
}

// fn_3_ED490, size:0x6C
void fn_3_ED490(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    fn_80034E20(p, lbl_3_data_8F24);
    g_Minigame.toyfield_waitFor_CoinsX2_AnimationToEnd = 1;
    p->u1C = 0;
    lbl_803CC1B8->func = fn_3_ED2F4;
}

// fn_3_ED2F4, size:0x19C
void fn_3_ED2F4(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    u32 stadium;
    u8 v;
    s32 v2;
    if (lbl_3_common_bss_32724.hudOff == 0) {
        if (g_UnkSound_32718._07 == 0) {
            ((EaSlot*)&lbl_80371C30)[p->u14].obj->visible = 1;
            if (p->u1C == 0) {
                if (lbl_800EF808[0x398] == 1) {
                    stadium = g_d_GameSettings.StadiumID;
                    if (g_d_GameSettings.GameModeSelected == 6) {
                        v = lbl_3_data_84B8[0x36];
                    } else {
                        v = lbl_3_data_8404[stadium * 0x1E + 0x36];
                    }
                    v2 = sndFXStartEx(lbl_3_data_81DC[stadium] + 0x1B, v, 0x3F, 0);
                    if (g_d_GameSettings.GameModeSelected == 6) {
                        v = lbl_3_data_84B8[0x37];
                    } else {
                        v = lbl_3_data_8404[stadium * 0x1E + 0x37];
                    }
                    sndFXCtrl(v2, 0x5B, v);
                }
                p->u1C = 1;
            }
        } else {
            ((EaSlot*)&lbl_80371C30)[p->u14].obj->visible = 0;
        }
        if (((EaSlot*)&lbl_80371C30)[p->u14].obj->animState == 2) {
            goto remove;
        }
    } else {
remove:
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
        g_Minigame.toyfield_waitFor_CoinsX2_AnimationToEnd = 0;
    }
}

// fn_3_ED2A8, size:0x4C
void fn_3_ED2A8(void) {
    fn_80034E20(lbl_803CC1B8, lbl_3_data_8FCC);
    lbl_803CC1B8->func = fn_3_ED244;
}

// fn_3_ED244, size:0x64
void fn_3_ED244(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    if (lbl_3_common_bss_32724.hudOff != 0 || ((EaSlot*)&lbl_80371C30)[p->u14].obj->animState == 2) {
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x000ED0F4 size:0x150 mapped:0x8072C188
void fn_3_ED0F4(void) {
    u32 stadium;
    EaTask* task = EA_TASK;
    u8 vol;
    EaSlot* slots;
    s32 voice;
    u8* mix;

    fn_80034E20(task, lbl_3_data_8F64);
    slots = (EaSlot*)lbl_80371C30;
    slots[task->baseIdx + 1].obj->anim = lbl_3_data_8FC4[EA_MG._1921 - 1];
    stadium = g_d_GameSettings.StadiumID;
    if (g_d_GameSettings.GameModeSelected == 6) {
        mix = lbl_3_data_84B8;
        vol = mix[0x38];
    } else {
        vol = lbl_3_data_8404[stadium * 0x1E + 0x38];
    }
    voice = sndFXStartEx(lbl_3_data_81DC[stadium] + 0x1C, vol, 0x3F, 0);
    if (g_d_GameSettings.GameModeSelected == 6) {
        vol = lbl_3_data_84B8[0x39];
    } else {
        vol = lbl_3_data_8404[stadium * 0x1E + 0x39];
    }
    sndFXCtrl(voice, 0x5B, vol);
    task->param = 0;
    EA_MG._19CD = 1;
    EA_TASK->func = fn_3_ED058;
}

// fn_3_ED058, size:0x9C
void fn_3_ED058(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    p->u18++;
    if (lbl_3_common_bss_32724.hudOff != 0 || (g_GameLogic.gameStatus != 2 && g_GameLogic.gameStatus != 1) || ((EaSlot*)&lbl_80371C30)[p->u14].obj->animState == 2) {
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
        g_Minigame._19CD = 3;
    }
}

// fn_3_ECD48, size:0x310
void fn_3_ECD48(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    u8* q = g_Minigame.hudFlags;
    u32 stadium;
    u32 stadium2;
    u8 v;
    s32 v2;
    u32 j;
    s32 n;
    if (lbl_3_common_bss_32724.hudOff != 0) {
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
        return;
    }
    if (g_GameLogic.gameStatus == 8) {
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
        return;
    }
    switch (p->u1C) {
    case 0:
        fn_80034E20(p, lbl_3_data_19770);
        stadium = g_d_GameSettings.StadiumID;
        if (g_d_GameSettings.GameModeSelected == 6) {
            v = lbl_3_data_84B8[0x22];
        } else {
            v = lbl_3_data_8404[stadium * 0x1E + 0x22];
        }
        v2 = sndFXStartEx(lbl_3_data_81DC[stadium] + 0x11, v, 0x3F, 0);
        if (g_d_GameSettings.GameModeSelected == 6) {
            v = lbl_3_data_84B8[0x23];
        } else {
            v = lbl_3_data_8404[stadium * 0x1E + 0x23];
        }
        sndFXCtrl(v2, 0x5B, v);
        p->u1C = 1;
        p->u1E = 0;
        break;
    case 1:
        if (((EaSlot*)&lbl_80371C30)[p->u14].obj->frame >> 16 == 0xA0) {
            j = 0;
            do {
                n = p->u14 + g_Minigame.playerOrder[1 + j];
                j++;
                EA_SLOT_OBJ(n + 1)->visible = 1;
            } while (j < (u32)(g_Minigame.miniGameNumberOfParticipants - 1));
            p->u1C = 2;
        }
        p->u1E = p->u1E + 1;
        if (p->u1E == 0x3C) {
            stadium2 = g_d_GameSettings.StadiumID;
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[0x24];
            } else {
                v = lbl_3_data_8404[stadium2 * 0x1E + 0x24];
            }
            v2 = sndFXStartEx(lbl_3_data_81DC[stadium2] + 0x12, v, 0x3F, 0);
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[0x25];
            } else {
                v = lbl_3_data_8404[stadium2 * 0x1E + 0x25];
            }
            sndFXCtrl(v2, 0x5B, v);
        }
        break;
    case 2:
        n = p->u14;
        n += g_Minigame.playerOrder[1];
        if (EA_SLOT_OBJ(n + 1)->frame >> 16 >= 6) {
            j = 0;
            do {
                q[g_Minigame.playerOrder[1 + j]] = 2;
                j++;
            } while (j < (u32)(g_Minigame.miniGameNumberOfParticipants - 1));
            g_Minigame._1934 = 2;
            p->u1C = 3;
        }
        break;
    case 3:
        break;
    }
}

// fn_3_ECBB0, size:0x198
void fn_3_ECBB0(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    u8* q = g_Minigame.hudFlags;
    u32 j;
    s32 n;
    if (lbl_3_common_bss_32724.hudOff != 0) {
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
        return;
    }
    if (g_GameLogic.gameStatus == 8) {
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
        return;
    }
    switch (p->u1C) {
    case 0:
        fn_80034E20(p, lbl_3_data_19830);
        ((EaSlot*)&lbl_80371C30)[p->u14 + 1].obj->frame = 0xA0000;
        j = 0;
        do {
            n = p->u14 + j;
            j++;
            EA_SLOT_OBJ(n + 2)->flags &= ~2;
        } while (j < 4);
        n = p->u14 + g_Minigame.playerOrder[0];
        EA_SLOT_OBJ(n + 2)->flags |= 2;
        n = p->u14 + g_Minigame.playerOrder[1];
        EA_SLOT_OBJ(n + 2)->flags |= 2;
        q[g_Minigame.playerOrder[0]] = 1;
        q[g_Minigame.playerOrder[1]] = 1;
        p->u1C = 1;
        break;
    case 1:
        g_Minigame._1934 = 2;
        p->u1C = 2;
        break;
    case 2:
        break;
    }
}

// .text:0x000EC804 size:0x3AC mapped:0x8072B898
// NONMATCHING 99%: the original reuses the dead pool-base register r31 for `stadium`; ours gives it r28
// (u8/s32 stadium and declaration order do not change it)
#if NONMATCHING
void fn_3_EC804(void) {
    EaTask* task = EA_TASK;
    u8* q = g_Minigame.hudFlags;
    u32 stadium;
    u8 vol;
    s32 voice;

    if (lbl_3_common_bss_32724.hudOff != 0) {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    if (g_GameLogic.gameStatus == 8) {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    switch (task->state) {
    case 0:
        fn_80034E20(task, lbl_3_data_19910);
        EA_SPRITE(task, 0)->anim = lbl_3_data_19970[g_Minigame.playerOrder[1]];
        EA_SPRITE(task, 1)->anim = (task->param != 0) + 0xF;
        task->_1E = lbl_3_data_19978[g_Minigame.playerOrder[1]];
        task->_20 = lbl_3_data_19980[g_Minigame.playerOrder[1]];
        stadium = g_d_GameSettings.StadiumID;
        if (g_d_GameSettings.GameModeSelected == 6) {
            vol = lbl_3_data_84B8[0x20];
        } else {
            vol = lbl_3_data_8404[stadium * 0x1E + 0x20];
        }
        voice = sndFXStartEx(lbl_3_data_81DC[stadium] + 0x10, vol, 0x3F, 0);
        if (g_d_GameSettings.GameModeSelected == 6) {
            vol = lbl_3_data_84B8[0x21];
        } else {
            vol = lbl_3_data_8404[stadium * 0x1E + 0x21];
        }
        sndFXCtrl(voice, 0x5B, vol);
        task->state = 1;
        break;
    case 1:
        if (task->_1E == EA_SPRITE(task, 0)->frame >> 16) {
            if (task->param != 0) {
                stadium = g_d_GameSettings.StadiumID;
                if (g_d_GameSettings.GameModeSelected == 6) {
                    vol = lbl_3_data_84B8[0xE];
                } else {
                    vol = lbl_3_data_8404[stadium * 0x1E + 0xE];
                }
                voice = sndFXStartEx(lbl_3_data_81DC[stadium] + 7, vol, 0x3F, 0);
                if (g_d_GameSettings.GameModeSelected == 6) {
                    vol = lbl_3_data_84B8[0xF];
                } else {
                    vol = lbl_3_data_8404[stadium * 0x1E + 0xF];
                }
                sndFXCtrl(voice, 0x5B, vol);
            } else {
                stadium = g_d_GameSettings.StadiumID;
                if (g_d_GameSettings.GameModeSelected == 6) {
                    vol = lbl_3_data_84B8[0xC];
                } else {
                    vol = lbl_3_data_8404[stadium * 0x1E + 0xC];
                }
                voice = sndFXStartEx(lbl_3_data_81DC[stadium] + 6, vol, 0x3F, 0);
                if (g_d_GameSettings.GameModeSelected == 6) {
                    vol = lbl_3_data_84B8[0xD];
                } else {
                    vol = lbl_3_data_8404[stadium * 0x1E + 0xD];
                }
                sndFXCtrl(voice, 0x5B, vol);
            }
        }
        if (EA_SPRITE(task, 0)->frame >> 16 >= task->_20) {
            q[g_Minigame.playerOrder[1]] = 2;
            g_Minigame._1934 = 2;
            task->state = 2;
        }
        break;
    case 2:
        break;
    }
}
#endif

// .text:0x000EC014 size:0x7F0 mapped:0x8072B0A8
// NONMATCHING 95%: animState == 2 tests compile to cntlzw in the original; register allocation
#if NONMATCHING
void fn_3_EC014(void) {
    EaReelTask* task = (EaReelTask*)lbl_803CC1B8;
    u32 i;
    u32 n;
    u32 stadium;
    u8 vol;
    s32 voice;
    s32 sym;

    if (lbl_3_common_bss_32724.hudOff != 0 || g_GameLogic.gameStatus == 8 || task->state == 7) {
        if (task->state != 0 && task->voice != -1) {
            sndFXKeyOff(task->voice);
            sndFXCtrl(task->voice, 7, 0);
            task->voice = -1;
        }
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    if (EA_MG._19CE != 0) {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    switch (task->state) {
    case 0:
        fn_80034E20(task, lbl_3_data_19988);
        i = 0;
        do {
            EA_MG.reelState[i] = 0;
            i++;
        } while (i < 3);
        task->voice = -1;
        task->state = 1;
        break;
    case 1:
        if (EA_SPRITE(task, 0)->animState == 2 && EA_SPRITE(task, 0xC)->animState == 2) {
            i = 0;
            do {
                EA_SPRITE(task, i + 1)->visible = 1;
                i++;
            } while (i < 3);
            EA_SPRITE(task, 0xD)->visible = 1;
            EA_SPRITE(task, 0xE)->visible = 1;
            stadium = g_d_GameSettings.StadiumID;
            if (g_d_GameSettings.GameModeSelected == 6) {
                vol = lbl_3_data_84B8[4];
            } else {
                vol = lbl_3_data_8404[stadium * 0x1E + 4];
            }
            voice = sndFXStartEx(lbl_3_data_81DC[stadium] + 2, vol, 0x3F, 0);
            if (g_d_GameSettings.GameModeSelected == 6) {
                vol = lbl_3_data_84B8[5];
            } else {
                vol = lbl_3_data_8404[stadium * 0x1E + 5];
            }
            sndFXCtrl(voice, 0x5B, vol);
            task->voice = voice;
            task->state = 2;
        }
        break;
    case 2:
        i = 0;
        do {
            if (EA_SPRITE(task, i + 1)->animState == 2) {
                EA_SPRITE(task, i + 1)->frame = 0;
                EA_MG.reelPos[i]++;
                if (EA_MG.reelPos[i] >= 7) {
                    EA_MG.reelPos[i] = 0;
                }
                switch (EA_MG.reelState[i]) {
                case 0:
                    if (EA_MG.reelStop[i] >= 1) {
                        EA_SPRITE(task, i + 1)->anim = 0x1F;
                        EA_MG.reelState[i] = 1;
                    }
                    break;
                case 1:
                    if (EA_MG.reelStop[i] >= 2 &&
                        EA_MG.reelTarget[i] == lbl_3_data_189C4[i][(EA_MG.reelPos[i] + 1) % 7]) {
                        EA_SPRITE(task, i + 1)->anim = 0x20;
                        EA_MG.reelState[i] = 2;
                    }
                    break;
                case 2:
                    if (EA_MG.reelTarget[i] == lbl_3_data_189C4[i][EA_MG.reelPos[i]]) {
                        EA_SPRITE(task, i + 1)->visible = 0;
                        stadium = g_d_GameSettings.StadiumID;
                        EA_MG.reelStop[i] = 3;
                        if (g_d_GameSettings.GameModeSelected == 6) {
                            vol = lbl_3_data_84B8[6];
                        } else {
                            vol = lbl_3_data_8404[stadium * 0x1E + 6];
                        }
                        voice = sndFXStartEx(lbl_3_data_81DC[stadium] + 3, vol, 0x3F, 0);
                        if (g_d_GameSettings.GameModeSelected == 6) {
                            vol = lbl_3_data_84B8[7];
                        } else {
                            vol = lbl_3_data_8404[stadium * 0x1E + 7];
                        }
                        sndFXCtrl(voice, 0x5B, vol);
                        if (i == 2) {
                            sndFXKeyOff(task->voice);
                            sndFXCtrl(task->voice, 7, 0);
                            task->voice = -1;
                        }
                        EA_MG.reelState[i] = 3;
                    }
                    break;
                }
            }
            i++;
        } while (i < 3);
        n = 0;
        i = 0;
        do {
            if (EA_MG.reelState[i] == 3) {
                n++;
            }
            i++;
        } while (i < 3);
        if (n >= 3) {
            task->state = 3;
        }
        break;
    case 3:
        i = 0;
        do {
            EA_SPRITE(task, i + 5)->visible = 1;
            i++;
        } while (i < 3);
        switch (EA_MG.reelResult) {
        case 0:
        case 3:
        case 4:
        case 5:
            EA_MG._1934 = 1;
            task->state = 4;
            break;
        case 1:
        case 2:
        case 6:
        case 7:
        case 8:
            EA_MG._1934 = 2;
            task->state = 8;
            break;
        }
        break;
    case 4:
        if (EA_SPRITE(task, 5)->animState == 2) {
            task->state = 5;
        }
        break;
    case 5:
        EA_SPRITE(task, 0)->visible = 4;
        EA_SPRITE(task, 0xC)->visible = 4;
        EA_SPRITE(task, 0xD)->visible = 4;
        task->state = 6;
        break;
    case 6:
        if ((EA_SPRITE(task, 0)->frame >> 16) == 0 && (EA_SPRITE(task, 0xC)->frame >> 16) == 0 &&
            (EA_SPRITE(task, 0xD)->frame >> 16) == 0) {
            switch (EA_MG.reelResult) {
            case 0:
                fn_800B0A5C_insertQueue(fn_3_ECD48, 2);
                break;
            case 3:
                ((EaTask*)fn_800B0A5C_insertQueue(fn_3_EC804, 2))->param = 0;
                break;
            case 4:
                ((EaTask*)fn_800B0A5C_insertQueue(fn_3_EC804, 2))->param = 1;
                break;
            case 5:
                fn_800B0A5C_insertQueue(fn_3_ECBB0, 2);
                break;
            }
            task->state = 7;
        }
        break;
    case 7:
    case 8:
        break;
    }
    i = 0;
    do {
        sym = lbl_3_data_189C4[i][EA_MG.reelPos[i]];
        fn_800363D8(task, i + 5, 1, 0x21, lbl_3_data_19B88[sym]);
        fn_800363D8(task, i + 5, 2, 0x22, lbl_3_data_19B88[sym]);
        sym = lbl_3_data_189C4[i][(EA_MG.reelPos[i] + 1) % 7];
        fn_800363D8(task, i + 8, 1, 0x21, lbl_3_data_19B88[sym]);
        fn_800363D8(task, i + 8, 2, 0x22, lbl_3_data_19B88[sym]);
        i++;
    } while (i < 3);
}
#endif

// fn_3_EBFD4, size:0x40
s32 fn_3_EBFD4(void) {
    if (lbl_3_common_bss_32724.hudOff != 0 || g_GameLogic.gameStatus == 2 || g_GameLogic.gameStatus == 8) {
        return 1;
    }
    return 0;
}

// .text:0x000EB6E0 size:0x8F4 mapped:0x8072A774
// NONMATCHING 91%: register allocation and branch layout in the score loops
#if NONMATCHING
void fn_3_EB6E0(void) {
    EaTask* task = EA_TASK;
    u32 sound = 0;
    u32 i;
    s8 who;
    s8 chara;
    s32 d;
    s32 step;
    s16 target;
    u32 v;
    u8 leader;
    s32 tied;

    if (EA_MG.game != 0) {
        if (fn_3_12536C() != 0) {
            fn_80034CEC(task);
            REMOVE_QUEUE_NOARG();
            return;
        }
    } else if (fn_3_EBFD4()) {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    switch (task->state) {
    case 0:
        fn_80034E20(task, lbl_3_data_19B98);
        if (EA_MG.game != 0) {
            i = 0;
            do {
                EA_SPRITE(task, i + 1)->frame = 0;
                i++;
            } while (i < 4);
        } else {
            i = 0;
            do {
                EA_SPRITE(task, i + 1)->frame = 1 << 16;
                i++;
            } while (i < 4);
        }
        i = 0;
        do {
            EA_SPRITE(task, i + 0x29)->flags &= ~2;
            i++;
        } while (i < 4);
        task->_1E = EA_MG.turn;
        EA_SPRITE(task, 0)->anim = lbl_3_data_1A158[EA_MG.numPlayers - 1][g_Batter.batterHand];
        task->_20 = 0;
        if (EA_MG.game != 0 && (g_Scores.inning != 1 || EA_MG.turn != 0)) {
            task->_1E--;
            EA_SPRITE(task, 0)->frame = 10 << 16;
            task->_20 = 1;
        }
        task->state = 1;
        break;
    case 1:
        EA_MG._19A0 = 0;
        i = 0;
        do {
            who = EA_MG.order[(task->_1E + i) % EA_MG.numPlayers];
            d = EA_MG.points[who] - EA_MG._18BC[who].shown;
            if (d < 0) {
                step = d / 8;
                EA_MG._19A0 = 1;
                if (step != 0) {
                    EA_MG._18BC[who].shown += step;
                } else {
                    EA_MG._18BC[who].shown += d / (d < 0 ? -d : d);
                }
                sound = 1;
            }
            i++;
        } while (i < EA_MG.numPlayers);
        if (EA_MG._19A0 == 0) {
            i = 0;
            do {
                if (EA_MG.points[i] != EA_MG._18BC[i].shown) {
                    EA_MG._19A0 = 1;
                    task->state = 2;
                }
                i++;
            } while (i < EA_MG.numPlayers);
        }
        break;
    case 2:
        EA_MG._19A0 = 0;
        i = 0;
        do {
            who = EA_MG.order[(task->_1E + i) % EA_MG.numPlayers];
            target = EA_MG.points[who];
            d = target - EA_MG._18BC[who].shown;
            if (d > 0) {
                EA_MG._19A0 = 1;
                step = d / 8;
                task->pending[who] = 1;
                if (step != 0) {
                    EA_MG._18BC[who].shown += step;
                } else {
                    EA_MG._18BC[who].shown += d / (d < 0 ? -d : d);
                }
                sound = 1;
            } else if (d == 0) {
                EA_MG._18BC[who].shown = target;
                if (task->pending[who] != 0) {
                    task->pending[who] = 0;
                    EA_SPRITE(task, i + 0x15)->frame = 0;
                    EA_SPRITE(task, i + 0x15)->visible = 1;
                    EA_SPRITE(task, i * 4 + 0x19)->frame = 0;
                    EA_SPRITE(task, i * 4 + 0x1A)->frame = 0;
                    EA_SPRITE(task, i * 4 + 0x1B)->frame = 0;
                    EA_SPRITE(task, i * 4 + 0x1C)->frame = 0;
                }
            }
            i++;
        } while (i < EA_MG.numPlayers);
        if (EA_MG._19A0 == 0) {
            i = 0;
            do {
                if (EA_MG.points[i] != EA_MG._18BC[i].shown) {
                    EA_MG._19A0 = 1;
                }
                i++;
            } while (i < EA_MG.numPlayers);
            task->state = 1;
        }
        break;
    }
    switch (task->_20) {
    case 0:
        if (fn_3_125424((u8*)task, 0, 10) != 0) {
            task->_20 = 2;
        }
        break;
    case 1:
        if (lbl_8037169C[0x10] == 0) {
            EA_SPRITE(task, 0)->visible = 1;
            if (EA_SPRITE(task, 0)->animState == 2) {
                EA_SPRITE(task, 0)->visible = 0;
                EA_SPRITE(task, 0)->frame = 10 << 16;
                task->_1E++;
                task->_20 = 2;
            }
        }
        break;
    case 2:
        if (EA_MG.game == 1) {
            if (g_GameLogic.gameStatus == 0 || g_GameLogic.gameStatus == 1) {
                fn_3_125424((u8*)task, 0, 10);
            } else {
                fn_3_125424((u8*)task, 0, 0);
            }
        }
        break;
    }
    leader = fn_3_107CD0();
    tied = fn_3_107C88();
    i = 0;
    do {
        who = EA_MG.order[(task->_1E + i) % EA_MG.numPlayers];
        chara = EA_MG.characterIndex[who];
        fn_800363D8(task, i + 5, 1, 0x65, chara);
        EA_SPRITE(task, i + 0xD)->frame = EA_CHAR_ID(chara) << 16;
        v = EA_MG._18BC[who].shown;
        if ((EA_SPRITE(task, i + 1)->frame >> 16) == 0) {
            if (v > 9999) {
                v = 9999;
            }
        } else if (v > 999) {
            v = 999;
        }
        fn_800363D8(task, i * 4 + 0x19, 1, 0x66, (v % 10000) / 1000);
        fn_800363D8(task, i * 4 + 0x1A, 1, 0x66, (v % 1000) / 100);
        fn_800363D8(task, i * 4 + 0x1B, 1, 0x66, (v % 100) / 10);
        fn_800363D8(task, i * 4 + 0x1C, 1, 0x66, v % 10);
        if (tied == 0 && EA_MG._18BC[who].shown == EA_MG._18BC[leader].shown) {
            EA_SPRITE(task, i + 0x29)->flags |= 2;
        } else {
            EA_SPRITE(task, i + 0x29)->flags &= ~2;
        }
        i++;
    } while (i < EA_MG.numPlayers);
    if (sound != 0 && EA_MG.game == 0) {
        sndFXStartEx(0x1C0, lbl_800EFBA4[9], 0x3F, 0);
    }
}
#endif

// fn_3_EB684, size:0x5C
s32 fn_3_EB684(void) {
    if (lbl_3_common_bss_32724.hudOff != 0 || lbl_3_common_bss_32724._B7 != 0) {
        return 1;
    }
    if (g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 2 && g_GameLogic.gameStatus != 0xB) {
        return 1;
    }
    return 0;
}

// .text:0x000EAEF4 size:0x790 mapped:0x80729F88
// NONMATCHING 90%: loop induction/register allocation; leader index kept as a byte offset in the original
#if NONMATCHING
void fn_3_EAEF4(void) {
    EaTask* task = EA_TASK;
    u32 sound = 0;
    u32 i;
    s32 d;
    s32 step;
    u32 v;
    u8 leader;
    s32 tied;
    s8 chara;

    if (fn_3_EB684()) {
        lbl_3_common_bss_32724._D6 = 0;
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    switch (task->state) {
    case 0:
        i = 0;
        do {
            EA_MG.marks[i] = 0;
            i++;
        } while (i < 4);
        lbl_3_common_bss_32724._D6 = 1;
        lbl_3_common_bss_32724._B7 = 0;
        fn_80034E20(task, lbl_3_data_1A168);
        i = 0;
        do {
            chara = EA_MG.characterIndex[i];
            fn_800363D8(task, i + 9, 1, 0x65, chara);
            EA_SPRITE(task, i + 0x11)->frame = EA_CHAR_ID(chara) << 16;
            i++;
        } while (i < EA_MG.numPlayers);
        i = 0;
        do {
            EA_SPRITE(task, i + 0x29)->flags &= ~2;
            i++;
        } while (i < 4);
        task->state = 1;
        break;
    case 1:
        EA_MG._19A0 = 0;
        i = 0;
        do {
            d = EA_MG.points[i] - EA_MG._18BC[i].shown;
            if (d < 0) {
                EA_MG._19A0 = 1;
                if ((EA_SPRITE(task, 0)->frame >> 16) >= 10) {
                    step = d / 8;
                    if (step != 0) {
                        EA_MG._18BC[i].shown += step;
                    } else {
                        EA_MG._18BC[i].shown += d / (d < 0 ? -d : d);
                    }
                }
                sound = 1;
            }
            i++;
        } while (i < EA_MG.numPlayers);
        if (EA_MG._19A0 == 0) {
            i = 0;
            do {
                if (EA_MG.points[i] != EA_MG._18BC[i].shown) {
                    EA_MG._19A0 = 1;
                    task->state = 2;
                }
                i++;
            } while (i < EA_MG.numPlayers);
        }
        break;
    case 2:
        EA_MG._19A0 = 0;
        i = 0;
        do {
            d = EA_MG.points[i] - EA_MG._18BC[i].shown;
            if (d > 0) {
                EA_MG._19A0 = 1;
                EA_TASK->pending[i] = 1;
                if ((EA_SPRITE(task, 0)->frame >> 16) >= 10) {
                    step = d / 8;
                    if (step != 0) {
                        EA_MG._18BC[i].shown += step;
                    } else {
                        EA_MG._18BC[i].shown += d / (d < 0 ? -d : d);
                    }
                }
                sound = 1;
            } else if (d == 0) {
                if (EA_TASK->pending[i] != 0) {
                    EA_TASK->pending[i] = 0;
                    EA_SPRITE(task, i + 0x19)->frame = 0;
                    EA_SPRITE(task, i + 0x19)->visible = 1;
                    EA_SPRITE(task, i * 3 + 0x1D)->frame = 0;
                    EA_SPRITE(task, i * 3 + 0x1E)->frame = 0;
                    EA_SPRITE(task, i * 3 + 0x1F)->frame = 0;
                }
            }
            i++;
        } while (i < EA_MG.numPlayers);
        if (EA_MG._19A0 == 0) {
            i = 0;
            do {
                if (EA_MG.points[i] != EA_MG._18BC[i].shown) {
                    EA_MG._19A0 = 1;
                }
                i++;
            } while (i < EA_MG.numPlayers);
            task->state = 1;
        }
        break;
    }
    if (g_UnkSound_32718._07 == 5) {
        task->_22 = 1;
    }
    EA_SPRITE(task, 0)->anim = lbl_3_data_1A728[EA_MG._19C6];
    if (task->_22 != 0) {
        EA_SPRITE(task, 0)->visible = 1;
    } else {
        fn_3_125424((u8*)task, 0, 10);
    }
    leader = fn_3_107CD0();
    tied = fn_3_107C88();
    i = 0;
    do {
        v = EA_MG._18BC[i].shown;
        if (v > 999) {
            v = 999;
        }
        fn_800363D8(task, i * 3 + 0x1D, 1, 0x66, (v % 1000) / 100);
        fn_800363D8(task, i * 3 + 0x1E, 1, 0x66, (v % 100) / 10);
        fn_800363D8(task, i * 3 + 0x1F, 1, 0x66, v % 10);
        if (tied == 0 && EA_MG._18BC[i].shown == EA_MG._18BC[leader].shown) {
            EA_SPRITE(task, i + 0x29)->flags |= 2;
        } else {
            EA_SPRITE(task, i + 0x29)->flags &= ~2;
        }
        i++;
    } while (i < EA_MG.numPlayers);
    i = 0;
    do {
        if (EA_MG.marks[i] != 0) {
            switch (EA_MG.marks[i]) {
            case 1:
                EA_SPRITE(task, i + 0xD)->anim = 0x60;
                break;
            case 2:
                EA_SPRITE(task, i + 0xD)->anim = 0x61;
                break;
            }
            EA_SPRITE(task, i + 0xD)->frame = 0;
            EA_SPRITE(task, i + 0xD)->visible = 1;
            EA_MG.marks[i] = 0;
        }
        i++;
    } while (i < EA_MG.numPlayers);
    if (sound != 0 && EA_MG._1939 == 0) {
        sndFXStartEx(0x1C0, lbl_800EFBA4[9], 0x3F, 0);
    }
}
#endif

// .text:0x000EA8FC size:0x5F8 mapped:0x80729990
// NONMATCHING 87%: the batter-side digit offset is computed as 3 & ~((-x | x) >> 31) in the original; loop register allocation
#if NONMATCHING
void fn_3_EA8FC(void) {
    EaTask* task = EA_TASK;
    u32 i;
    s8 who;
    s16 delta;
    s32 anim;

    if (task->param != 0) {
        if (fn_3_EB684()) {
            lbl_3_common_bss_32724._D6 = 0;
            fn_80034CEC(task);
            REMOVE_QUEUE_NOARG();
            return;
        }
    } else if (fn_3_EBFD4()) {
        lbl_3_common_bss_32724._D6 = 0;
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    switch (task->state) {
    case 0:
        fn_80034E20(task, lbl_3_data_1A730);
        if (task->param != 0) {
            EA_SPRITE(task, 0)->frame = 10 << 16;
        } else {
            EA_SPRITE(task, 0)->anim = lbl_3_data_1A158[EA_MG.numPlayers - 1][g_Batter.batterHand];
            EA_SPRITE(task, 0)->frame = 10 << 16;
            EA_SPRITE(task, 1)->anim = 0x58;
            EA_SPRITE(task, 2)->anim = 0x58;
            EA_SPRITE(task, 3)->anim = 0x58;
            EA_SPRITE(task, 4)->anim = 0x58;
        }
        task->state = 1;
        break;
    case 1:
        for (i = 0; i < EA_MG.numPlayers; i++) {
            if (task->param != 0) {
                who = i;
            } else {
                who = EA_MG.order[(EA_MG.turn + i) % EA_MG.numPlayers];
            }
            delta = EA_MG._18BC[who].delta;
            if (delta != 0) {
                if (delta < 0) {
                    delta *= -1;
                    anim = 0x59;
                } else {
                    anim = 0x5A;
                }
                if (delta > 999) {
                    delta = 999;
                }
                if (task->param != 0) {
                    if (delta >= 100) {
                        EA_SPRITE(task, i + 1)->frame = 2 << 16;
                    } else if (delta >= 10) {
                        EA_SPRITE(task, i + 1)->frame = 1 << 16;
                    } else {
                        EA_SPRITE(task, i + 1)->frame = 0;
                    }
                } else if (delta >= 100) {
                    EA_SPRITE(task, i + 1)->frame = ((g_Batter.batterHand == 0 ? 3 : 0) + 2) << 16;
                } else if (delta >= 10) {
                    EA_SPRITE(task, i + 1)->frame = ((g_Batter.batterHand == 0 ? 3 : 0) + 1) << 16;
                } else {
                    EA_SPRITE(task, i + 1)->frame = (g_Batter.batterHand == 0 ? 3 : 0) << 16;
                }
                fn_800363D8(task, i * 4 + 5, 1, anim, 11);
                fn_800363D8(task, i * 4 + 6, 1, anim, (delta % 1000) / 100);
                fn_800363D8(task, i * 4 + 7, 1, anim, (delta % 100) / 10);
                fn_800363D8(task, i * 4 + 8, 1, anim, delta % 10);
                if (EA_MG._19A0 != 0) {
                    fn_3_125424((u8*)task, i * 4 + 5, 8);
                    fn_3_125424((u8*)task, i * 4 + 6, 8);
                    fn_3_125424((u8*)task, i * 4 + 7, 8);
                    fn_3_125424((u8*)task, i * 4 + 8, 8);
                } else {
                    EA_SPRITE(task, i * 4 + 5)->visible = 1;
                    EA_SPRITE(task, i * 4 + 6)->visible = 1;
                    EA_SPRITE(task, i * 4 + 7)->visible = 1;
                    EA_SPRITE(task, i * 4 + 8)->visible = 1;
                }
            }
        }
        break;
    }
}
#endif

// .text:0x000EA454 size:0x4A8 mapped:0x807294E8
// NONMATCHING 96%: score-cap register allocation and the /10000 constant spill
#if NONMATCHING
void fn_3_EA454(void) {
    EaTask* task = EA_TASK;
    EaOrder order[4];
    u32 i;
    u32 j;
    s16 score;
    s16 cap;
    s8 chara;

    if (lbl_3_common_bss_32724.hudOff != 0) {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 6 && lbl_3_common_bss_34C90.state == 5) {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    if (g_GameLogic.gameStatus == 0x22 && (lbl_3_common_bss_34C90.state == 7 || g_GameLogic.framesOfExitingToMenu != 0)) {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    if (g_GameLogic.gameStatus == 0x26) {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    if (g_GameLogic.gameStatus == 0x24) {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    switch (task->state) {
    case 0:
        fn_80034E20(task, lbl_3_data_1A9F0);
        EA_SPRITE(task, 0)->anim = lbl_3_data_1AF70[EA_MG.game];
        if (EA_MG.game != 0 && EA_MG._1909 == 0 && EA_MG._1A3C == 0) {
            if (EA_MG._190A != 0) {
                EA_SPRITE(task, 1)->anim = lbl_3_data_1AF88[EA_MG._1A2B];
            } else {
                EA_SPRITE(task, 1)->anim = lbl_3_data_1AF80[EA_MG._1A2B];
            }
        } else {
            EA_SPRITE(task, 1)->anim = 0x175;
        }
        fn_3_1079C8((u8*)order, 0);
        EA_SPRITE(task, 2)->anim = lbl_3_data_1AF90[EA_MG.numPlayers - 1];
        for (i = 0; i < EA_MG.numPlayers; i++) {
            chara = EA_MG.characterIndex[i];
            EA_SPRITE(task, i + 3)->frame = lbl_3_data_1AF98[EA_MG.game] << 16;
            EA_SPRITE(task, i + 7)->frame = chara << 16;
            if (fn_3_107C40() != 0) {
                EA_SPRITE(task, i + 0x13)->anim = 0x175;
            } else {
                j = 0;
                do {
                    if (i == order[j].player) {
                        EA_SPRITE(task, i + 0x13)->anim = lbl_3_data_1AFA8[order[j].rank];
                        break;
                    }
                    j++;
                } while (j < EA_MG.numPlayers);
            }
            score = EA_MG.points[i];
            cap = lbl_80109410[EA_MG.game];
            if (score > cap) {
                score = cap;
            }
            fn_800363D8(task, i * 4 + 0x1B, 1, 0x66, (score % 10000) / 1000);
            fn_800363D8(task, i * 4 + 0x1C, 1, 0x66, (score % 1000) / 100);
            fn_800363D8(task, i * 4 + 0x1D, 1, 0x66, (score % 100) / 10);
            fn_800363D8(task, i * 4 + 0x1E, 1, 0x66, score % 10);
        }
        task->state = 1;
        // fallthrough
    case 1:
        break;
    }
}
#endif

// .text:0x000EA340 size:0x114 mapped:0x807293D4
// NONMATCHING 99%: `add r7, r0, r4` operand order of baseIdx + i (3 sites)
#if NONMATCHING
void fn_3_EA340(void) {
    EaTask* task = EA_TASK;
    s32 i;
    s32 frame;

    fn_80034E20(task, lbl_3_data_900C);
    for (i = 0; i < 3; i++) {
        if (EA_MG.player[i] >= 0) {
            frame = EA_MG.characterIndex[EA_MG.player[i]] << 16;
            EA_SPRITE(task, i + 3)->frame = frame;
            EA_SPRITE(task, i + 6)->frame = frame;
            EA_SPRITE(task, i + 9)->frame = EA_CHAR_ID(EA_MG.player[i]) << 16;
        }
    }
    task->param = 0;
    EA_TASK->func = fn_3_E9D30;
}
#endif

// .text:0x000E9D30 size:0x610 mapped:0x80728DC4
// NONMATCHING 96%: saved-register numbering (dir/i/alpha) and a few scheduling swaps; same calls, stores and flow
#if NONMATCHING
// Minigame task: an arrow at the screen edge for each player that is off screen.
void fn_3_E9D30(void) {
    SceneTask* task = lbl_803CC1B8;
    Vec pos;
    int sx;
    int sy;
    s32 dir;
    s32 alphaX;
    s32 alphaY;
    s32 x;
    s32 y;
    s32 i;
    s32 k;
    s32 dx;
    s32 dz;

    if (lbl_3_common_bss_32724.hudOff == 0 && g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL &&
        g_Minigame._19CE == 0 && g_Minigame.turnOverStatus == 0) {
        for (i = 0; i < 3; i++) {
            if (g_Minigame.minigameControlStruct[0].fieldOrder[i] < 0) {
                continue;
            }
            dir = -1;
            alphaX = 0xFF;
            alphaY = 0xFF;
            getAnimRelatedCoordinates(g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigameControlStruct[0].fieldOrder[i]], 4, &pos);
            if (fn_3_1650C(&sx, &sy, FALSE, pos.x, pos.y, pos.z) == 0) {
                // off screen: move the point toward the camera until it is on screen
                for (k = 0; k < 3; k++) {
                    dx = (s32)(g_pCamera->_284C.x - pos.x);
                    dz = (s32)(g_pCamera->_284C.z - pos.z);
                    dx = dx * lbl_3_rodata_2C48;
                    dz = dz * lbl_3_rodata_2C48;
                    pos.x += dx;
                    pos.z += dz;
                    if (fn_3_1650C(&sx, &sy, FALSE, pos.x, pos.y, pos.z) != 0) {
                        break;
                    }
                }
            }

            x = lbl_3_data_D638.left;
            if (sx <= x) {
                dir = 2;
                if (sx > lbl_3_data_D638.leftFade) {
                    alphaX = fadeAlpha(sx, lbl_3_data_D638.leftFade, x);
                }
            } else {
                x = lbl_3_data_D638.right;
                if (sx >= x) {
                    dir = 5;
                    if (sx < lbl_3_data_D638.rightFade) {
                        alphaX = fadeAlpha(sx, lbl_3_data_D638.rightFade, x);
                    }
                } else {
                    x = sx;
                }
            }
            if (alphaX > 0xFF) {
                alphaX = 0xFF;
            }

            y = lbl_3_data_D638.top;
            if (sy <= y) {
                dir += 1;
                if (sy > lbl_3_data_D638.topFade) {
                    alphaY = fadeAlpha(sy, lbl_3_data_D638.topFade, y);
                }
            } else {
                y = lbl_3_data_D638.bottom;
                if (sy >= y) {
                    dir += 2;
                    if (sy < lbl_3_data_D638.bottomFade) {
                        alphaY = fadeAlpha(sy, lbl_3_data_D638.bottomFade, y);
                    }
                } else {
                    y = sy;
                }
            }
            if (alphaY > 0xFF) {
                alphaY = 0xFF;
            }

            if (dir < 0 || alphaX <= 0 || alphaY <= 0) {
                MARKER(task, i)->flags &= ~2;
                continue;
            }
            MARKER(task, i)->flags |= 2;
            MARKER(task, i)->x = x;
            MARKER(task, i)->y = y;
            if (dir == 2 || dir == 5) {
                MARKER(task, i)->color = (MARKER(task, i)->color & ~0xFF) | alphaX;
            } else if (dir >= 2) {
                // corner: the stronger of the two
                if (alphaX > alphaY) {
                    MARKER(task, i)->color = (MARKER(task, i)->color & ~0xFF) | alphaX;
                } else {
                    MARKER(task, i)->color = (MARKER(task, i)->color & ~0xFF) | alphaY;
                }
            } else {
                MARKER(task, i)->color = (MARKER(task, i)->color & ~0xFF) | alphaY;
            }
            MARKER(task, i)->_5C = lbl_3_data_91AC[dir] << 16;
        }
        return;
    }
    lbl_3_common_bss_32724._97 = 0;
    fn_80034CEC(task);
    REMOVE_QUEUE_NOARG();
}
#endif

// .text:0x000E911C size:0xC14 mapped:0x807281B0
// NONMATCHING 88%: the original keeps a second copy of the task pointer (r30) and the
// data pool base (r27) live; loops over sprites get unrolled differently.
#if NONMATCHING
void fn_3_E911C(void) {
    ResultsTask* task = ((ResultsTask*)lbl_803CC1B8);
    u16 mode = task->mode;
    ResultsOrder order[4];
    u32 tick = 0;
    u32 i;
    u32 stadium;
    u8 vol;
    s32 voice;
    u32 n;
    s32 idx;
    s8 chara;
    u8 player;

    if (mode != 0) {
        if (lbl_3_common_bss_32724.hudOff != 0 || g_GameLogic.gameStatus != 0x26) {
            fn_80034CEC(task);
            REMOVE_QUEUE_NOARG();
            return;
        }
    } else if (lbl_3_common_bss_32724.hudOff != 0 || g_GameLogic.gameStatus != 3) {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }

    switch (task->state) {
    case 0:
        fn_80034E20(task, lbl_3_data_1AFB0);
        if (task->mode != 0) {
            if (g_Minigame._1E2A >= 6) {
                SPRITE(task, 0)->anim = 0x170;
                fn_3_90064(lbl_3_data_81FC[0x36]);
            } else {
                SPRITE(task, 0)->anim = 0x16F;
                fn_3_90064(lbl_3_data_81FC[0x25]);
            }
        } else {
            if (g_Minigame.toyField_turnNumber == 0) {
                SPRITE(task, 0)->anim = 0x171;
            } else {
                SPRITE(task, 0)->anim = 0x16F;
            }
            stadium = g_d_GameSettings.StadiumID;
            if (g_d_GameSettings.GameModeSelected == 6) {
                vol = lbl_3_data_84B8[0x1C];
            } else {
                vol = lbl_3_data_8404[stadium * 0x1E + 0x1C];
            }
            voice = sndFXStartEx(lbl_3_data_81DC[stadium] + 0xE, vol, 0x3F, 0);
            if (g_d_GameSettings.GameModeSelected == 6) {
                vol = lbl_3_data_84B8[0x1D];
            } else {
                vol = lbl_3_data_8404[stadium * 0x1E + 0x1D];
            }
            sndFXCtrl(voice, 0x5B, vol);
        }
        if (task->mode != 0) {
            task->kind = 0;
        } else {
            task->kind = 2;
        }
        i = 0;
        do {
            idx = task->baseIdx + i;
            i++;
            ((ResultsSprite*)lbl_80371C30[idx + 0x38].obj)->flags &= ~2;
        } while (i < 4);
        if (task->kind == 2 && g_Minigame.toyField_turnNumber == 0) {
            SPRITE(task, 0x1B)->flags &= ~2;
            i = 0;
            do {
                idx = task->baseIdx + i;
                i++;
                ((ResultsSprite*)lbl_80371C30[idx + 0x1C].obj)->flags &= ~2;
            } while (i < 4);
        }
        task->state = 1;
        break;

    case 1:
        if (mode != 0) {
            if (task->round != 0) {
                fn_3_1079C8((u8*)order, 1);
            } else {
                fn_3_1079C8((u8*)order, 2);
            }
        } else {
            fn_3_1079C8((u8*)order, 0);
        }
        if (task->mode == 0 && g_Minigame.toyField_turnNumber == 0) {
            SPRITE(task, 2)->anim = 0x183;
        } else {
            SPRITE(task, 2)->anim = 0x184;
        }
        SPRITE(task, 2)->frame = 0;
        SPRITE(task, 2)->visible = 1;
        for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
            player = order[i].player;
            chara = g_Minigame.minigameControlStruct[0].characterIndex[player];
            SPRITE(task, i + 3)->frame = task->kind << 16;
            SPRITE(task, i + 7)->frame = chara << 16;
            // chara indexes inMemRoster flattened (both teams)
            SPRITE(task, i * 2 + 0xF)->frame = (&inMemRoster[0][0])[chara].stats.CharID << 16;
            SPRITE(task, i * 2 + 0x10)->frame = (&inMemRoster[0][0])[chara].stats.CharID << 16;
            SPRITE(task, i + 0x17)->anim = lbl_3_data_1B7D0[order[i].rank];
            SPRITE(task, i + 0x1C)->anim = lbl_3_data_1AFA8[order[i].rank];
            if (task->mode != 0) {
                if (task->round != 0) {
                    task->score[i] = g_Minigame._1E22[player];
                } else {
                    task->score[i] = g_Minigame._1E26[player];
                }
            } else {
                task->score[i] = g_Minigame.miniGameCurrentPoints[player];
            }
            SPRITE(task, i * 3 + 0x24)->frame = 0;
            SPRITE(task, i * 3 + 0x25)->frame = 0;
            SPRITE(task, i * 3 + 0x26)->frame = 0;
            SPRITE(task, i * 3 + 0x24)->visible = 1;
            SPRITE(task, i * 3 + 0x25)->visible = 1;
            SPRITE(task, i * 3 + 0x26)->visible = 1;
            if (task->mode != 0 && task->round == 0) {
                task->bonus[i] = g_Minigame._1E22[player] - g_Minigame._1E26[player];
                n = task->bonus[i];
                if (n > 99) {
                    n = 99;
                }
                if (n >= 10) {
                    fn_800363D8(task, i + 0x3C, 1, 0x174, 11);
                } else {
                    fn_800363D8(task, i + 0x3C, 1, 0x174, 10);
                }
                if (n >= 10) {
                    fn_800363D8(task, i + 0x3C, 2, 0x174, (n % 100) / 10);
                } else {
                    fn_800363D8(task, i + 0x3C, 2, 0x174, 11);
                }
                fn_800363D8(task, i + 0x3C, 3, 0x174, n % 10);
            }
            SPRITE(task, i + 0x3C)->frame = 0;
            SPRITE(task, i + 0x3C)->visible = 0;
        }
        task->state = 2;
        // fallthrough
    case 2:
        switch (task->kind) {
        case 0:
        case 1:
            if (task->round != 0) {
                if (g_GameLogic._125 >= 5) {
                    task->state = 7;
                }
            } else if (SPRITE(task, 2)->animState == 2) {
                task->state = 5;
            }
            break;
        case 2:
            if (g_Minigame.toyField_turnNumber == 0 && SPRITE(task, 2)->animState == 2) {
                task->timer = 0;
                task->state = 3;
            }
            break;
        }
        break;

    case 3:
        task->timer++;
        if (task->timer >= 4) {
            task->timer = 0;
            task->cursor++;
            if (task->cursor >= 4) {
                task->cursor = 0;
            }
            for (i = 0; i < 4; i++) {
                if (i == task->cursor) {
                    SPRITE(task, i + 0x38)->flags |= 2;
                } else {
                    SPRITE(task, i + 0x38)->flags &= ~2;
                }
            }
            if (task->cursor == g_Minigame.rosterID) {
                task->spins++;
                if (task->spins >= 5) {
                    SPRITE(task, g_Minigame.rosterID + 0x38)->visible = 1;
                    task->state = 4;
                }
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        break;

    case 5:
        for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
            if (task->bonus[i] != 0) {
                ResultsSprite* spr = SPRITE(task, i + 0x3C);
                if ((spr->frame >> 16) >= 9) {
                    spr->visible = 0;
                    task->timer = 0;
                    task->state = 6;
                } else {
                    spr->visible = 1;
                }
            }
        }
        break;

    case 6:
        task->timer++;
        if (task->timer >= 4) {
            for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
                if (task->bonus[i] != 0) {
                    tick = 1;
                    task->score[i]++;
                    task->bonus[i]--;
                }
            }
            task->timer = 0;
        }
        for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
            if (task->bonus[i] != 0) {
                break;
            }
        }
        if (i >= g_Minigame.miniGameNumberOfParticipants && g_GameLogic._125 >= 3) {
            task->state = 7;
        }
        break;

    case 7:
        if (fn_3_125424((u8*)task, 2, 0) != 0) {
            switch (task->kind) {
            case 0:
                if (task->round == 0) {
                    if (g_Minigame._1E2A >= 6) {
                        task->kind = 1;
                    }
                    task->round = 1;
                    task->state = 1;
                }
                break;
            }
        }
        break;
    }

    if (task->state >= 1) {
        for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
            n = task->score[i];
            if (task->mode != 0) {
                if (n > 99) {
                    n = 99;
                }
            } else if (n > 999) {
                n = 999;
            }
            fn_800363D8(task, i * 3 + 0x24, 1, 0x66, (n % 1000) / 100);
            fn_800363D8(task, i * 3 + 0x25, 1, 0x66, (n % 100) / 10);
            fn_800363D8(task, i * 3 + 0x26, 1, 0x66, n % 10);
        }
    }
    if (tick != 0) {
        sndFXStartEx(0x1C1, lbl_800EFBA4[0xA], 0x3F, 0);
    }
}
#endif
