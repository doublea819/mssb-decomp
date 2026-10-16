#include "menus/rep_01A0.h"
#define REP_HEADER_FN repHeader_menus_01A0
#include "header_rep_inline.h"
// math.h first with dolsqrtf2 static: UnknownHomes_Game.h makes it extern inline,
// which would emit its _half/_three statics into this unit's .rodata.
#include "math.h"
#undef SQRT2_LINKAGE
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_80069BDC.h"
#include "musyx/musyx.h"
#include "main/file_8004207C.h"
#include "menus/auto_00_00000D08_text.h"
#include "menus/rep_0200.h"
#include "menus/auto_00_00001254_text.h"
#include "menus/rep_05F0.h"
#include "menus/rep_0640.h"
#include "menus/rep_0A58.h"
#include "menus/rep_0AB0.h"
#include "menus/rep_0438.h"
#include "menus/auto_00_0004B1AC_text.h"
#include "menus/auto_00_0001B1BC_text.h"
#include "menus/auto_00_00071EC4_text.h"
#include "menus/rep_0FD8.h"

// Menu music sequences (used by fn_2_D88/fn_2_E84).
SeqEnt lbl_2_data_128[2] = {
    {0x1F, 0x13, 0},
    {0x1F, 0x14, 1},
};

// Menu music voice and its fade-out state.
SND_VOICEID lbl_2_data_134 = SND_ID_ERROR; // SND_ID_ERROR when not playing
// mwcc emits file statics in reverse order of definition.
static u8 lbl_2_bss_1C;                    // nonzero while a fade task is queued
static f32 lbl_2_bss_18;                   // current volume

// Menu scene handlers, indexed by scene id (called from fn_2_11D8).
#ifdef TARGET_PC
extern void port_career_scene(void); // scene 18: Career Mode menu (port/game/career.c)
void (*lbl_2_data_138[19])(void) = {
    fn_2_119C,  fn_2_8EEC8, fn_2_121C,  fn_2_121C,   fn_2_1164,  fn_2_27E0,
    fn_2_19D04, fn_2_54BB0, fn_2_5E104, fn_2_12F88,  fn_2_110B0, fn_80048764,
    fn_2_11698, fn_8004A2BC, fn_2_1A1B4, fn_2_53408, fn_2_1B7B4, fn_2_854B0,
    port_career_scene,
};
#else
void (*lbl_2_data_138[18])(void) = {
    fn_2_119C,  fn_2_8EEC8, fn_2_121C,  fn_2_121C,   fn_2_1164,  fn_2_27E0,
    fn_2_19D04, fn_2_54BB0, fn_2_5E104, fn_2_12F88,  fn_2_110B0, fn_80048764,
    fn_2_11698, fn_8004A2BC, fn_2_1A1B4, fn_2_53408, fn_2_1B7B4, fn_2_854B0,
};
#endif

// With -inline deferred, mwcc emits functions in reverse source order:
// the functions below are in reverse address order.

// .text:0x00000C74 size:0x94
void fn_2_C74(u8 volume) {
    if (lbl_2_data_134 != SND_ID_ERROR && sndFXCheck(lbl_2_data_134) == lbl_2_data_134) {
        sndFXCtrl(lbl_2_data_134, 7, volume);
    } else {
        lbl_2_bss_18 = volume;
    }
}

// .text:0x00000C18 size:0x5C
void fn_2_C18(void) {
    if (lbl_2_data_134 != SND_ID_ERROR && sndFXCheck(lbl_2_data_134) == lbl_2_data_134) {
        sndFXKeyOff(lbl_2_data_134);
        lbl_2_data_134 = SND_ID_ERROR;
    }
}

// .text:0x00000B38 size:0xE0
void fn_2_B38(void) {
    lbl_2_bss_18 += lbl_803CC1B8->u14.rate;
    if (lbl_2_bss_18 < 0.0f) {
        lbl_2_bss_18 = 0.0f;
    }
    sndFXCtrl(lbl_2_data_134, 7, lbl_2_bss_18);
    if (0.0f == lbl_2_bss_18) {
        lbl_2_bss_1C = 0;
        if (lbl_2_data_134 != SND_ID_ERROR && sndFXCheck(lbl_2_data_134) == lbl_2_data_134) {
            sndFXKeyOff(lbl_2_data_134);
            lbl_2_data_134 = SND_ID_ERROR;
        }
#if NONMATCHING
        fn_800B0A14_removeQueue(NULL); // the argument is unused
#else
        REMOVE_QUEUE_NOARG(); // original passes a stale r3
#endif
    }
}

// .text:0x00000A70 size:0xC8
void fn_2_A70(u16 frames) {
    SceneTask* task;

    if (lbl_2_bss_1C == 0 && lbl_2_data_134 != SND_ID_ERROR && sndFXCheck(lbl_2_data_134) == lbl_2_data_134) {
        task = fn_800B0A5C_insertQueue(fn_2_B38, 0x8000);
        if (frames == 0) {
            frames = 1;
        }
        task->u14.rate = -lbl_2_bss_18 / frames;
        lbl_2_bss_1C = 1;
    }
}
