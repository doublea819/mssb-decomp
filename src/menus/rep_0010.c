// Translation unit 0x0010: the menus.rel boot code (.text 0x0..0xA70, _prolog/_epilog),
// its .data 0x0..0x128 and .bss 0x0..0x18, and the common block 0xB644..0xFC68.
// The rodata starts with dolsqrtf2's weak constants (the first unit to emit them) and
// then the per-TU float table.
// Functions in reverse address order (-inline deferred).
#include "game/UnknownHomes_Game.h"
#define REP_HEADER_FN repHeader_menus_0010
#include "header_rep_inline.h"
#include "menus/rep_0010.h"
#include "static/GameSettings.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXTev.h"
#include "Dolphin/OS/OSUtil.h"
#include "musyx/musyx.h"
#include "main/file_80008E00.h"
#include "menus/auto_00_00000D08_text.h"
#include "main/aramloader.h"
extern ARAMLoader lbl_803C6CF8;

extern void fn_800A7D4C(s32, void*);
extern void* fn_800B0A5C_insertQueue(void*, s32);
extern void fn_800B0A14_removeQueue(void* unused);

// fn_800B0A14_removeQueue ignores its argument. Some callers pass nothing: r3 is
// whatever the previous call left (e.g. right after fn_80034CEC). The matching
// build calls it through a (void) cast there; the port passes NULL.
#ifndef REMOVE_QUEUE_NOARG
#if NONMATCHING
#define REMOVE_QUEUE_NOARG() fn_800B0A14_removeQueue(NULL)
#else
#define REMOVE_QUEUE_NOARG() ((void (*)(void))fn_800B0A14_removeQueue)()
#endif
#endif

extern void fn_8001F228(void);
extern void fn_80062744(void);
extern void fn_8001E474(void);
extern s32 fn_80036C88(s32*, s32*);
extern void fn_800B0D28(s32*);
extern MenuFlags lbl_800E877C; // the SceneFlow lbl_803CBBCC points at
extern u8* lbl_803CC1B8;
extern u32 lbl_803CB750;
extern void fn_8004153C(void);
extern void fn_800A97D0(s32, s32);
#include "main/charsel_state_type.h"
extern CharSelectState lbl_8034E9A0;
extern void* ARAMTransfer(void* instr, void* dest, u8 mode, u32 aramAddr);
extern void fn_800216F8(u8 group, s32 (*callback)(u8* state));
extern s32 fn_80022A24(u8, u8);
extern void fn_800229CC(void);

extern MenuPad lbl_803C77B8[];
// Layer setup for fn_80036C88 (fn_2_0's GX setup is the layer callback in lbl_2_data_C0).
s32 lbl_2_data_0[0x30] = {
#ifdef TARGET_PC
    // Layer 8 holds Career Mode's menu text on PC (port/game/career.c).
    0xA40, 0, 0, 0, 0x900, 0x5E60, 0x4DE0, 0x2700, 0x6000, 0, 0, 0, 0, 0x400, 0x8C0, 0x20, 0x6A0,
#else
    0xA40, 0, 0, 0, 0x900, 0x5E60, 0x4DE0, 0x2700, 0, 0, 0, 0, 0, 0x400, 0x8C0, 0x20, 0x6A0,
#endif
};
MenuLayerCallback lbl_2_data_C0 = {0, fn_2_0};
// ARAM transfer of the menu save buffer (fn_2_554).
u32 lbl_2_data_C8[4] = {0, 0x46E0, 0x06CF8800, 0x46E0};

// .bss 0x0..0x18 (only the queue pointer is used). mwcc emits file statics in
// reverse order of definition.
static u8 lbl_2_bss_8[0x10];
static MenuCmdQueue* lbl_2_bss_4; // command queue task (fn_2_374)
static u32 lbl_2_bss_0;

// Common block 0xB644..0xFC68: lbl_2_bss_B644 is used here, the rest by other units.
// mwcc lists unreferenced commons in reverse order of definition.
MenuTeamSel lbl_2_bss_F468;
MenuSelVars lbl_2_bss_F410;
u8 lbl_2_bss_E8CC[0xB44];
u8 lbl_2_bss_DCE8[0xBE4];
u8 lbl_2_bss_D988[0x360]; // unreferenced
u8* lbl_2_bss_D984; // sound data block (fn_2_10AC)
u32 lbl_2_bss_D974[4];
s16 lbl_2_bss_D958[0xE];
u32 lbl_2_bss_B644;

// fn_2_A14, size:0x5C
void fn_2_A14(void) {
    fn_800B0A5C_insertQueue(fn_2_160, 0x1000);
    fn_800B0A5C_insertQueue(fn_2_110, 0xF000);
    lbl_803CBBCC->step = 0;
    lbl_803CBBCC->scene = 0;
}

// fn_2_978, size:0x9C
void fn_2_978(void) {
    u8 mode = lbl_80366158._1D;
    fn_800B0A5C_insertQueue(fn_2_11D8, 0x2000);
    // Next menu scene for the boot mode.
    switch (mode) {
    case 0:
        fn_2_11A0(0x11);
        break;
    case 1:
        fn_2_11A0(0xE);
        break;
    case 3: // one empty case makes mwcc pick the jump table (more empty labels do not)
        break;
    case 7:
        fn_2_11A0(1);
        break;
    case 9:
        fn_2_11A0(1);
        break;
    }
    lbl_80366158._1D = 1;
}

// fn_2_940, size:0x38
void fn_2_940(void) {
    if (lbl_803CBBCC->_00 == 5) {
        REMOVE_QUEUE_NOARG();
    }
}

// fn_2_794, size:0x1AC
void fn_2_794(void) {
    MenuTask* task = (MenuTask*)lbl_803CC1B8;
    switch (lbl_803CBBCC->_00) {
    case 0:
        task->_10 = 0;
        fn_800B0A5C_insertQueue(fn_2_160, 0x1000);
        fn_800B0A5C_insertQueue(fn_2_110, 0xF000);
        lbl_803CBBCC->step = 0;
        lbl_803CBBCC->scene = 0;
        fn_800B0A5C_insertQueue(fn_2_940, 0x100);
        (lbl_803CBBCC->_00)++;
        break;
    case 1:
        lbl_803CBBCC->_00 = 3;
        break;
    case 3:
        fn_2_978(); // inlined
        lbl_803CBBCC->_00 = 4;
    case 4:
        if (task->_10 != 0) {
            lbl_803CBBCC->_00 = 5;
    case 5:
            task->parent->_10 = task->_10;
            REMOVE_QUEUE_NOARG();
        }
        break;
    }
}

// fn_2_708, size:0x8C
void fn_2_708(void) {
    MenuBootTask* o = (MenuBootTask*)lbl_803CC1B8;
    lbl_803CB750 += OSGetTick();
    fn_8004153C();
    fn_800A97D0(0x10, 0x1E);
    lbl_803CBBCC->_00 = 0;
    o->state = 0;
    fn_800B0A5C_insertQueue(fn_2_664, 0x1000);
    (*(MenuBootTask**)&lbl_803CC1B8)->func = fn_2_554;
}

// fn_2_664, size:0xA4
void fn_2_664(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        s8 a;
        if (lbl_803C66B0.active[i] == 1 || (a = lbl_8034E9A0.ports[i]) == -1) {
            lbl_8034E9A0.input[i].held = 0;
            lbl_8034E9A0.input[i].pressed = 0;
            lbl_8034E9A0.input[i].repeat = 0;
        } else {
            lbl_8034E9A0.input[i].held = lbl_803C77B8[(s8)lbl_8034E9A0.ports[i]].held;
            lbl_8034E9A0.input[i].pressed = lbl_803C77B8[(s8)lbl_8034E9A0.ports[i]].down;
            lbl_8034E9A0.input[i].repeat = lbl_803C77B8[(s8)lbl_8034E9A0.ports[i]].repeat;
        }
    }
}

// fn_2_554, size:0x110
void fn_2_554(void) {
    MenuBootTask* o = (MenuBootTask*)lbl_803CC1B8;
    switch (o->state) {
    case 0:
        lbl_2_bss_B644 = OSGetTick();
        fn_800216F8(2, fn_2_10FC);
        o->state = 1;
    case 1:
        if ((*(MenuBootTask**)&lbl_803CC1B8)->_10 != 0) {
            sndVolume(0x7F, 0xA, 0xFF);
            o->state = 2;
    case 2:
            ARAMTransfer(lbl_2_data_C8, &lbl_8034E9A0, 1, 0);
            o->state = 3;
        }
        break;
    case 3:
        if ((s32)(u8)lbl_803C6CF8.idle == 1) {
#ifdef TARGET_PC
            port_swap_char_stats(&lbl_8034E9A0, 6 * 9); // loaded big-endian
#endif
            o->func = fn_2_794;
            lbl_2_bss_4 = fn_800B0A5C_insertQueue(fn_2_374, 0x8000);
        }
        break;
    }
}

// fn_2_510, size:0x44
u8 fn_2_510(MenuCmdQueue* q) {
    if (q->tail == q->head) {
        return 0;
    }
    q->tail = (q->tail + 1) % 32;
    return q->cmds[q->tail];
}

// fn_2_4C4, size:0x4C
s32 fn_2_4C4(MenuCmdQueue* q, s8 value) {
    u8 n = (q->head + 1) % 32;
    if (n == q->tail) {
        return 0;
    }
    q->head = n;
    q->cmds[q->head] = value;
    return 1;
}

// fn_2_374, size:0x150
void fn_2_374(void) {
    MenuCmdQueue* o = (MenuCmdQueue*)lbl_803CC1B8;
    u8 v;
    switch (o->state) {
    case 0:
        o->state = fn_2_510(o);
        break;
    case 1:
        if (fn_80022A24(g_d_GameSettings.StadiumID, g_d_GameSettings.miniGameStadiumIndicator) != 0) {
            v = fn_2_510(o);
            o->state = v;
            if (v == 2) {
    case 2:
                fn_800229CC();
                o->state = fn_2_510(o);
            }
        }
        break;
    }
}

// fn_2_328, size:0x4C
void fn_2_328(void) {
    MenuCmdQueue* q = lbl_2_bss_4;
    u8 n = (q->head + 1) % 32;
    if (n != q->tail) {
        q->head = n;
        q->cmds[q->head] = 1;
    }
}

// fn_2_2DC, size:0x4C
void fn_2_2DC(void) {
    MenuCmdQueue* q = lbl_2_bss_4;
    u8 n = (q->head + 1) % 32;
    if (n != q->tail) {
        q->head = n;
        q->cmds[q->head] = 2;
    }
}

// fn_2_2D8, size:0x4
void fn_2_2D8(void) {
}

// fn_2_1A8, size:0x130
s32 fn_2_1A8(u8 idx, u8 kind, u16 mask) {
    u16 v = 0;
    s32 r = -1;
    switch (kind) {
    case 0:
        v = lbl_803C77B8[idx].held;
        break;
    case 1:
        v = lbl_803CBBCC->padHeld[idx];
        break;
    case 2:
        v = lbl_803C77B8[idx].repeat;
        break;
    }
    v &= mask;
    if (kind == 1) {
        lbl_803CBBCC->_10 |= 1 << idx;
    }
    if (v & 0x100) {
        r = 4;
    } else if (v & 0x200) {
        r = 5;
    } else if (v & 8) {
        r = 0;
    } else if (v & 4) {
        r = 1;
    } else if (v & 1) {
        r = 2;
    } else if (v & 2) {
        r = 3;
    } else if (v & 0x40) {
        r = 6;
    } else if (v & 0x20) {
        r = 7;
    }
    return r;
}

// fn_2_160, size:0x48
void fn_2_160(void) {
    lbl_803CBBCC->padHeld[0] |= lbl_803C77B8[0].down;
    lbl_803CBBCC->padHeld[1] |= lbl_803C77B8[1].down;
    lbl_803CBBCC->_10 = 0;
}

// fn_2_110, size:0x50
void fn_2_110(void) {
    u8 i;
    for (i = 0; i < 2; i++) {
        SceneFlow* p = lbl_803CBBCC;
        if (p->_10 & (1 << (u8)i)) {
            p->padHeld[i] = 0;
        }
    }
}

// _prolog, size:0x88
void _prolog(void) {
    s32* layers;
    lbl_803CBBCC = (SceneFlow*)&lbl_800E877C; // MenuFlags starts with a SceneFlow
    lbl_800E877C.scene = 0;
    fn_800A7D4C(0, &lbl_2_data_C0);
    fn_800B0A5C_insertQueue(fn_2_708, 0x8000);
    fn_80062744();
    fn_8001E474();
    layers = lbl_2_data_0 + 0x17;
    fn_80036C88(lbl_2_data_0, layers);
    fn_800B0D28(layers);
}

// _epilog, size:0x20
void _epilog(void) {
    fn_8001F228();
}

// fn_2_3C, size:0x2C
void fn_2_3C(void) {
    fn_800A7D4C(0, &lbl_2_data_C0);
}

// fn_2_0, size:0x3C
void fn_2_0(void* node) {
    GXSetZCompLoc(0);
    GXSetAlphaCompare(4, 0, 0, 7, 0);
}

