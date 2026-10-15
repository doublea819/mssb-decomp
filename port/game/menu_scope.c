// What the PC port offers: Exhibition at Mario Stadium (plus Practice and
// Options). Challenge, Toy Field, Minigames, Records and the other stadiums
// aren't offered; the menus skip them unless `allmodes = true` in user.ini (or
// MSSB_ALLMODES=1 in the environment, for the test scripts).
//
//   main menu (fn_2_1800 / fn_2_1DC8, auto_00_00001254_text.c): entries
//     0 Exhibition, 1 Challenge, 2 Toy Field, 3 Minigames, 4 Practice,
//     5 Records, 6 Options; the draw task (fn_2_747FC) hides 1-3 and 5 and
//     moves 4 and 6 up (port_menu_row)
//   stadium select (fn_2_11340): the cursor stays on Mario Stadium (0)
//   game options (fn_800494CC / fn_80049220, file_8004207C.c): Star Skills
//     (option 2, which also gates star chances) is locked off and its row is
//     hidden (fn_800559EC, file_800527C4.c); `starskills = true` in
//     user.ini brings the option back.
#include "mssbTypes.h"

#include <stdlib.h>

const char* port_user_ini_get(const char* key);
int port_user_ini_bool(const char* key);

static s32 all_modes(void) {
    static s32 s_all = -1;
    if (s_all < 0) {
        const char* env = getenv("MSSB_ALLMODES");
        s_all = (port_user_ini_get("allmodes") != NULL && port_user_ini_bool("allmodes")) ||
                (env != NULL && env[0] == '1');
    }
    return s_all;
}

// Main menu entry `entry` can be picked.
s32 port_menu_mode_enabled(s32 entry) {
    return all_modes() || entry == 0 || entry == 4 || entry == 6;
}

// The row the main menu draws entry `entry` in (-1: hidden).
s32 port_menu_row(s32 entry) {
    if (all_modes()) {
        return entry;
    }
    switch (entry) {
    case 0:
        return 0; // Exhibition
    case 4:
        return 1; // Practice
    case 6:
        return 2; // Options
    default:
        return -1;
    }
}

// Stadium select can move off Mario Stadium.
s32 port_stadium_select_enabled(void) {
    return all_modes();
}

// The game options screen offers Star Skills (option 2), which gates star moves,
// star chances and the HUD star meter. On unless user.ini says `starskills = false`.
s32 port_star_skills_enabled(void) {
    static s32 s_on = -1;
    if (s_on < 0) {
        s_on = port_user_ini_get("starskills") == NULL || port_user_ini_bool("starskills");
    }
    return s_on;
}
