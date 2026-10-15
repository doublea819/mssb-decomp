#include "menus/auto_00_00001254_text.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_8000F150.h"
#include "main/menu_globals.h"
#include "menus/menu_work.h"
#include "main/charsel_state.h"
#include "main/file_8001FE00.h"
#include "main/file_80008E00.h"
#include <string.h>

// This unit's .bss (emitted in reverse order of definition). Sizes are the distances
// between the original symbols; only the leading elements are used: lbl_2_bss_20[0] and
// lbl_2_bss_3A0[0] are step counters, lbl_2_bss_3E0 s8 flags per batting slot and
// lbl_2_bss_3A8 one byte per character.
static s16 lbl_2_bss_3E4[0x1BA];
static u8 lbl_2_bss_3E0[4];
static u8 lbl_2_bss_3A8[0x38];
static u8 lbl_2_bss_3A0[8];
static u8 lbl_2_bss_20[0x380];
extern u8 lbl_2_bss_758; // followed by 0x387 unreferenced bytes; stays in the auto split

extern void fn_800625A4(u8, s32);
// fn_800625A4 really takes an s32 port; one call passes it unmasked. wasm traps
// on a call through a mismatched prototype, so PC calls the definition's type.
#ifdef TARGET_PC
#define CALL_FN_800625A4_S32(port, sound) fn_800625A4((port), (sound))
#else
#define CALL_FN_800625A4_S32(port, sound) (((void (*)(s32, s32))fn_800625A4)((port), (sound)))
#endif

extern u8 lbl_803CB748[];
extern u8 lbl_803CBD24[];
extern void fn_8004D0F0(void);
extern s32 fn_8004CA6C(u16 buttons);
extern void fn_8004CC2C(void);
extern u8 lbl_80108EC4[];
extern u32 fn_800628D4(s32 id);
extern void fn_80050FE8(s32 p0, s32 p1, s32 p2, s32 p3, s32 arg4, s32 lockMode);
extern void fn_2_7265C(void);
extern s16 fn_80067AC8(s16 id, s8 col);
extern void fn_80021AC8(void);
extern void fn_2_74D8C(void);
extern s8 lbl_80108DB8[];
extern u8 lbl_803CBBC4[];
extern void fn_2_15A90(s32* value, s32 min, u8 max);
extern void fn_2_836A4(void);
extern void fn_2_85108(void);
extern u8 lbl_2_data_720[];
extern void fn_800216F8(s32 group, void* callback);
extern s32 fn_8006285C(u8* state);
extern void fn_8006496C(void);
extern void fn_2_82E58(void);
extern u8 lbl_2_bss_E8CC[];
extern u8 lbl_2_bss_DCE8[];
extern u8 lbl_803C6028[];
extern s32 fn_80050760(s32 p, s32 held, s32 pressed, s32 dirs, s32 mode);
extern u8 lbl_2_data_180[];
extern MenuTask* lbl_803CC1B8;
extern u8 lbl_803CBCE0[];
extern u8 lbl_803C6714[];
extern void initializeUnknown(void);
extern void fn_80062764(void* task);
extern s32 fn_80022B68(void);
extern void fn_2_12988(void);
extern s32 fn_800697B0(void);
extern void fn_8003F23C(void);
extern void fn_80066EAC(u8 team);
extern u8 lbl_803CBCD8[];
extern MenuProgress lbl_80361B20;
extern u8 lbl_2_data_130C[];
extern void fn_2_328(void);
extern void fn_2_2DC(void);
extern s32 fn_80062578(void);
extern s32 fn_80050F78(s32 arg);
extern void fn_2_19F2C(void);
extern void fn_80062A74(void);
extern s32 fn_80021410(void);
extern void fn_80035CA4(s32 id);
extern void fn_2_11A0(u16 value);
extern void fn_80021AC0(s32 team, s32 slot);
extern u8 lbl_2_data_E64[];
extern void fn_800649BC(void);
extern void fn_800671FC(void);
extern void fn_800684A4(void);
extern void fn_80069854(void);
extern void fn_80067F70(u8 team);
extern void characterSelectScreen(u8 team);
extern void fn_2_72630(void);
extern void fn_800678CC(s32 team);
extern void unsure_FillRosterPositions(u8 team);
extern MenuCharEntry lbl_800E8558[54];

extern void fn_2_7DDC(void);
extern void fn_2_3624(u8 port);
extern void fn_2_104FC(u16 port);
extern void fn_2_87A8(void);
extern void fn_2_7504(void);

extern CharSelectState lbl_8034E9A0;
#define CS_STATS(id) ((CharacterStats*)&lbl_8034E9A0.roster[(id) / 9][(id) % 9])

extern u32 lbl_803CB750[];

extern MenuTeamSel lbl_2_bss_F468;


extern u8 lbl_2_bss_100B4;
extern MenuSelVars lbl_2_bss_F410;
extern u8 lbl_800FDE84[];
extern void fn_800506E8(s32, s32, s32);
extern void fn_80050138(s32, s32, s32, s32, s32, s32);
extern MenuOrderEntry lbl_80353B98[2][9];
extern MenuOrderEntry lbl_80354720[2][9];
extern u8 lbl_803CB8D0[];
extern u8 lbl_800E8754[];
extern s16 randRange_FUN_80042bf0(s32, s32);
extern u8 lbl_80109038[];
extern s32 fn_80067B40(s32, u8, s32);
// lbl_800EF808 is SoundManager (main/file_80021308.h), which clashes with this
// unit's prototypes.
typedef struct MenuSoundMgr1254 {
    /*0x00*/ u32 _00;
    /*0x04*/ void* groups[48];
} MenuSoundMgr1254;
extern MenuSoundMgr1254 lbl_800EF808;
extern MenuDefEntry lbl_800FEF70[];
extern s16 lbl_80108EDC[][5]; // character groups (5 ids each)
extern u8 lbl_800EFBA4[];
extern int sndFXStartEx(int, int, int, int);
extern void fn_8004EEF4(s32, s32, s32, s32, s32);
extern u8 lbl_803C6724[];
extern u8 lbl_2_data_E88[];
extern void fn_800670A0(u8);
// The challenge save block (starMissionCompletionTracker) as the menus see it.
#define CHALLENGE ((MenuCtx*)starMissionCompletionTracker)
#define CHALLENGE_B ((u8*)starMissionCompletionTracker)
extern u8 lbl_2_data_3CE0[];
extern CaptainSelMenu lbl_2_bss_100B8;
extern void fn_2_16A74(s32, s32);

// fn_2_1D54, size:0x70
void fn_2_1D54(s32* selection, u8 controller, s32 count) {
    u16 buttons = lbl_8034E9A0.input[controller].repeat;
    if (buttons & 8) {
        (*selection)--;
        if (*selection < 0) {
            *selection = count - 1;
        }
    } else if (buttons & 4) {
        (*selection)++;
        if (*selection == count) {
            *selection = 0;
        }
    }
}

// fn_2_6138, size:0x68
void fn_2_6138(void) {
    fn_800625A4(0, 19);
    fn_800625A4(1, 19);
    lbl_2_bss_F468._4F = 0;
    lbl_2_bss_F468._2E = 0;
    lbl_2_bss_100B4 = 1;
    lbl_803CBBCC->step = 8;
}

// fn_2_35D0, size:0x54
u8 fn_2_35D0(u8 index) {
    u8* flag = (u8*)lbl_2_bss_F468._45 + (u32)index; // = &_45[index]; the unsigned index matches
    if (*flag != 0) {
        *flag = 0;
        sndFXRelated(0x200);
        return 1;
    }
    return 0;
}

// fn_2_112F4, size:0x4C
s32 fn_2_112F4(void* menu, s32 item, s32 index, const u16* values, s16 value) {
    LayoutObj* object = lbl_80371C30[((MenuTask*)menu)->baseIdx + item].obj;
    if ((s32)(object->_5C >> 16) == values[index + 1] - 1) {
        object->_64 = value;
        return 1;
    }
    return 0;
}

// fn_2_1258, size:0x48
u32 fn_2_1258(const void* base, u32 offset, s32 size) {
    u32 value = 0;
    switch (size) {
    case 1:
        value = *((const u8*)base + offset);
        break;
    case 2:
        value = *(const u16*)((const u8*)base + offset);
        break;
    case 3:
        break;
    case 4:
        value = *(const u32*)((const u8*)base + offset);
        break;
    }
    return value;
}

// fn_2_8780, size:0x14
s32 fn_2_8780(s32 mode) {
    if (mode != 0) {
        return 0x13;
    }
    return 9;
}

// fn_2_8794, size:0x14
s32 fn_2_8794(s32 mode, s32 index) {
    if (mode != 0) index += 10;
    return index;
}

// fn_2_57E8, size:0x8
s8 fn_2_57E8(s32 unused, s32 value) {
    return value;
}

// fn_2_EC34, size:0x20
void fn_2_EC34(void) {
    if (lbl_2_bss_F468._56 == 0) lbl_2_bss_F468._56 = 1;
}

// fn_2_145C, size:0x30
s32 fn_2_145C(u16* a, u16* b) {
    for (;;) {
        u16 x = *a++;
        u16 y = *b++;
        if (x != y) {
            return 0;
        }
        if (x == 0x4000) {
            return 1;
        }
    }
}

// fn_2_1554, size:0x24
u32 fn_2_1554(void) {
    lbl_803CB750[0] = lbl_803CB750[0] * 0x5D588B65 + 1;
    return lbl_803CB750[0];
}

// fn_2_1328, size:0x2C
void fn_2_1328(u32* value, u16 increment) {
    u32 sum = *value + increment;
    if (sum > 0x7FFFFFFF) {
        *value = 0x7FFFFFFF;
        return;
    }
    *value = sum;
}

// fn_2_12A0, size:0x2C
void fn_2_12A0(s16* value, s32 increment) {
    s16 current = *value;
    if (current < 0x7FFF - (s16)increment) {
        *value = current + increment;
        return;
    }
    *value = 0x7FFF;
}

// fn_2_12CC, size:0x2C
void fn_2_12CC(u8* value, s32 increment) {
    u8 current = *value;
    if (current + (u16)increment > 0xFF) {
        *value = 0xFF;
        return;
    }
    *value = current + increment;
}

// fn_2_12F8, size:0x30
void fn_2_12F8(u16* value, s32 increment) {
    u16 current = *value;
    if (current + (u16)increment > 0xFFFF) {
        *value = 0xFFFF;
        return;
    }
    *value = current + increment;
}

// fn_2_1D28, size:0x2C
void fn_2_1D28(void) {
    lbl_8034E9A0._472A = 0xFF;
    lbl_8034E9A0._4756 = 0;
    lbl_8034E9A0._4754 = 0;
    lbl_8034E9A0._4755 = 3;
    lbl_8034E9A0._48B3 = 0;
}

// fn_2_1254, size:0x4
void fn_2_1254(void) {
    return;
}

// fn_2_1DC4, size:0x4
void fn_2_1DC4(void) {
    return;
}

// fn_2_893C, size:0x4
void fn_2_893C(void) {
    return;
}

// fn_2_CCBC, size:0x24
void fn_2_CCBC(void) {
    fn_2_7DDC();
    fn_2_7504();
}

// fn_2_2BB8, size:0x164
void fn_2_2BB8(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        s16* t = (s16*)lbl_2_data_E88;
        u8* pa = lbl_803C6724 + i * 9;
        MenuOrderEntry* pb = lbl_80354720[i];
        s32* pw = &lbl_8034E9A0.captain[i];
        s32 j;
        for (j = 0; j < 9; j++) {
            s32 w = *pw;
            s32 v;
            if (w == 0) {
                v = t[0];
                pa[2] = v;
                pa[0x26] = CS_STATS(v)->chem[w];
            } else {
                v = t[9];
                pa[2] = v;
                pa[0x26] = CS_STATS(v)->chem[w];
            }
            pb->slot = j;
            pb->_1 = j;
            pb->_0 = j;
            t++;
            pa++;
            pb++;
        }
        fn_800670A0(i);
    }
}

// fn_2_3204, size:0x38
void fn_2_3204(void) {
    ((void (*)(u8, s32, s32))fn_2_2FC0)(lbl_803297E0._CF5F, 1, 1);
}

// fn_2_5F80, size:0x118
void fn_2_5F80(void) {
    s32 i;
    s32 j;
    s32 k;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 9; j++) {
            for (k = 0; k < 9; k++) {
                if (*(s8*)&lbl_80354720[i][j].slot == *(s8*)&lbl_80354720[i][k].slot) {
                    (lbl_803C6724 + i * 9 + j)[2] = inMemRoster[i][k].stats.CharID;
                }
            }
            (lbl_803C6724 + i * 9 + j)[0x14] = j;
        }
    }
}

// fn_2_6098, size:0x3C
void fn_2_6098(s32 index) {
    lbl_2_bss_F468.cursor[(u8)index] = 9;
    fn_800625A4((u8)index, 0x17);
}

// fn_2_1BAC, size:0x88
void fn_2_1BAC(void) {
    memset(&lbl_803C66B0.steps[0][1], 0, 0x54);
    lbl_803C66B0.active[1] = 0;
    lbl_803C66B0.active[0] = 0;
    memset(&lbl_803C5EA4, 0, 0x3A);
    memset(lbl_8034E9A0._489B, 0, sizeof(lbl_8034E9A0._489B));
    memset(&lbl_8034E978, 0, sizeof(lbl_8034E978));
}

// fn_2_60D4, size:0x64
s32 fn_2_60D4(u8 index) {
    u8* p;
    if (g_d_GameSettings.GameModeSelected != 5) {
        return lbl_8034E9A0.captain[index];
    }
    if (index != 0) {
        return lbl_8034E9A0.captain[index];
    }
    return lbl_8034E9A0.captain[index];
}

// fn_2_148C, size:0x6C
s32 fn_2_148C(u16* p) {
    s32 n = 0;
    for (;;) {
        u16 c = *p++;
        if (c & 0x4000) {
            switch (c & 0x3FFF) {
            case 0:
                goto done;
            case 2:
                n += 0xB;
                break;
            case 3:
                n += 0x16;
                break;
            }
        } else if (c & 0x8000) {
            n += 0x16;
        } else {
            n += 0xB;
        }
    }
done:
    return n;
}

// fn_2_120D0, size:0x9C
void fn_2_120D0(void) {
    lbl_8034E9A0._48AD = 1;
    lbl_8034E9A0._4755 = 3;
    lbl_803C66B0.steps[0][0] = 0;
    lbl_803C66B0.portOf[1] = 0;
    lbl_803C66B0.portOf[0] = 0;
    lbl_8034E9A0._472A = 0xFF;
    lbl_8034E9A0._48AF = 1;
    lbl_8034E9A0._48B1 = 1;
    memset(&lbl_803C66B0.steps[0][1], 0, 6);
    lbl_8034E978._26 = 1;
    fn_800AD038((void*)lbl_8034E9A0.heapMarkA[0]);
    ((u8*)&g_d_GameSettings)[0x10] = 0;
}

// fn_2_7D44, size:0x98
void fn_2_7D44(void) {
    if (lbl_803CBBCC->prevScene == 9) {
        memset(&lbl_2_bss_100B8, 0, sizeof(lbl_2_bss_100B8));
    }
    lbl_8034E9A0._4755 = 1;
    lbl_2_bss_100B8.count = 4;
    fn_2_16A74(0, 0);
    fn_2_16A74(1, 0);
    fn_2_16A74(2, 0);
    fn_2_16A74(3, 0);
}

// fn_2_33BC, size:0xD0
s32 fn_2_33BC(void) {
    s32 r = 1;
    s32 i;
    s8 a = CHALLENGE->order[0]._3;
    for (i = 1; i < 9; i++) {
        if (a == CHALLENGE->order[i]._3) {
            r = 0;
        }
    }
    return r;
}

// fn_2_A62C, size:0xB4
s32 fn_2_A62C(void) {
    s32 i;
    s32 j;
    s32 a;
    for (i = 0; i < 9; i++) {
        a = *(s8*)(lbl_803C6724 + 2 + i);
        for (j = 0; j < 9; j++) {
            if (a == *(s8*)(lbl_803C6724 + 0xB + j) && a != 0xFF) {
                return 1;
            }
        }
    }
    return 0;
}

// fn_2_1216C, size:0xCC
void fn_2_1216C(void) {
    s8 buf[4];
    s8 k;
    memset(buf, 2, 4);
    if (((u8*)&g_d_GameSettings)[0x10] == 0) {
        k = *(s8*)&lbl_8034E9A0.ports[0];
        buf[k] = 1;
        if (k == 0) {
            buf[1] = 2;
        } else {
            buf[0] = 2;
        }
    } else {
        buf[*(s8*)&lbl_8034E9A0.ports[1]] = 1;
        buf[*(s8*)&lbl_8034E9A0.ports[0]] = 1;
    }
    fn_8004EEF4(buf[0], buf[1], buf[2], buf[3], 1);
}

// fn_2_1C34, size:0xF4
void fn_2_1C34(u32 buttons) {
    switch ((u16)buttons) {
    case 0x100:
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        break;
    case 0x200:
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        break;
    case 1:
    case 2:
    case 4:
    case 8:
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        break;
    case 3:
    case 0x20:
    case 0x40:
    case 0x400:
    case 0x800:
        break;
    }
}

// fn_2_1354, size:0x108
void fn_2_1354(SortEntry* e, s32 n, s32 descending) {
    u32 i;
    u32 j;
    SortEntry t;
    if (n >= 2) {
        if (descending == 0) {
            for (i = 0; i < (u32)n; i++) {
                j = i;
                while (j >= 1 && e[j - 1].value > e[j].value) {
                    t = e[j - 1];
                    e[j - 1] = e[j];
                    e[j] = t;
                    j--;
                }
            }
        } else {
            SortEntry t2;
            for (i = 0; i < (u32)n; i++) {
                j = i;
                while (j >= 1 && e[j - 1].value < e[j].value) {
                    t2 = e[j - 1];
                    e[j - 1] = e[j];
                    e[j] = t2;
                    j--;
                }
            }
        }
    }
}

// fn_2_A50C, size:0x120
s32 fn_2_A50C(void) {
    s32 i;
    s32 j;
    s32 a;
    for (i = 0; i < 9; i++) {
        a = *(s8*)(lbl_803C6724 + 2 + i);
        for (j = 0; j < 9; j++) {
            if (a == *(s8*)(lbl_803C6724 + 0xB + j)) {
                return 1;
            }
        }
    }
    return 0;
}

// fn_2_EC54, size:0x140
void fn_2_EC54(s32 index) {
    s32 i;
    s32 j;
    if (g_d_GameSettings.GameModeSelected == 5) {
        return;
    }
    if (((u8*)&g_d_GameSettings)[0x10] == 1) {
        lbl_2_bss_100B8._2E[1] = 0;
        lbl_2_bss_100B8._2E[0] = 0;
    } else {
        lbl_2_bss_100B8._2E[index] = 0;
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 9; j++) {
            lbl_803C6724[i * 9 + 0x26 + j] = 0;
        }
        if (lbl_2_bss_F468._45[i] != 0) {
            lbl_2_bss_F468._45[i] = 0;
        }
    }
    if (lbl_2_bss_F468._56 == 0) {
        lbl_2_bss_F468._56 = 1;
    }
    lbl_2_bss_F468._2E = 1;
    lbl_2_bss_100B4 = 1;
    lbl_803CBBCC->step = 8;
}

// fn_2_C324, size:0x160
s8 fn_2_C324(s32 id) {
    s32 r;
    s32 i;
    s32 j;
    s32 k;
    s16 v;
    r = -1;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 5; j++) {
            if (id == lbl_80108EDC[i][j]) {
                r = i;
                goto found;
            }
        }
    }
found:
    if (r == -1) {
        return r;
    }
    for (k = 0; k < 9; k++) {
        v = inMemRoster[0][k].stats.CharID;
        for (j = 0; j < 5; j++) {
            if (v == lbl_80108EDC[r][j] && v != id) {
                return r;
            }
        }
    }
    return -1;
}

// fn_2_A040, size:0x160
void fn_2_A040(s32 a, s32 b, u8 c, u8 d) {
    s16* t;
    s32 n;
    s32 i;
    s32 j;
    t = lbl_80108EDC[a];
    if (t[b] != -1 && b < 4) {
        n = b + 1;
        if (n == 5 || t[n] == -1) {
            n = 0;
        }
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 9; j++) {
                if (*(s8*)(lbl_803C6724 + i * 9 + 2 + j) == t[n]) {
                    return;
                }
            }
        }
        (lbl_803C6724 + c * 9 + d)[2] = t[n];
        return;
    }
    (lbl_803C6724 + c * 9 + d)[2] = t[0];
}

// fn_2_B508, size:0x164
void fn_2_B508(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 0x36; i++) {
        for (j = 1; j < 9; j++) {
            if (*(s8*)(lbl_803C6724 + j + 0xB) == i) {
                lbl_8034E9A0.charFlag[i] = 0;
                fn_800506E8(*(s8*)&lbl_8034E9A0.ports[1], i, 0);
                fn_80067B40(1, i, 0);
            }
        }
    }
    for (i = 1; i < 9; i++) {
        lbl_80354720[1][i].slot = i;
        lbl_80353B98[1][i].slot = i;
        lbl_803C6724[0xB + i] = 0x36;
        lbl_803C6724[0x53 + i] = 0;
    }
}

// fn_2_52CC, size:0x178
#pragma opt_propagation off
void fn_2_52CC(void) {
    s32 i;
    s32 one = 1;
    lbl_2_bss_100B8._2E[0] = one;
    lbl_803C66B0.portOf[0] = one;
    lbl_2_bss_F468.cursor[one] = 0xA;
    lbl_803C5EA4._0E = one;
    if (lbl_8034E9A0.charFlag[lbl_2_bss_F410.charSel[5]] != 0) {
        for (i = 0; i < 0x20; i++) {
            if (lbl_8034E9A0.charFlag[lbl_800FDE84[i]] == 0) {
                lbl_2_bss_F410.charSel[5] = lbl_800FDE84[i];
                break;
            }
        }
    }
    switch (*(s8*)&lbl_8034E9A0.ports[1]) {
    case 0:
        fn_80050138(one, lbl_2_bss_F410.charSel[5], -1, -1, -1, 0);
        break;
    case 1:
        fn_80050138(one, -1, lbl_2_bss_F410.charSel[5], -1, -1, 0);
        break;
    case 2:
        fn_80050138(one, -1, -1, lbl_2_bss_F410.charSel[5], -1, 0);
        break;
    case 3:
        fn_80050138(one, -1, -1, -1, lbl_2_bss_F410.charSel[5], 0);
        break;
    }
}
#pragma opt_propagation reset

// fn_2_86EC, size:0x94
void fn_2_86EC(void) {
    if (g_d_GameSettings.GameModeSelected == 5 && lbl_8037169C.done == 0) {
        fn_800203E0(0xA, lbl_2_data_3CE0[CHALLENGE->_441E]);
    }
    fn_2_7DDC();
    fn_2_7504();
    lbl_2_bss_F468._56 = 0;
    lbl_803CBBCC->step = 2;
}

// fn_2_C698, size:0x144
void fn_2_C698(u8 a, s32 b) {
    s32 slot;
    if (g_d_GameSettings.GameModeSelected != 5) {
        u8 idx = b;
        u8* row = lbl_803C6724;
        u8* p;
        row += idx * 9;
        p = row;
        p += a;
        slot = *(s8*)(p + 2);
        lbl_8034E9A0.charFlag[slot] = 1;
        if (((u8*)&g_d_GameSettings)[0x10] == 0 && idx != 0) {
            if (*(s8*)&lbl_8034E9A0.ports[0] == 0) {
                fn_800506E8(1, slot, 1);
            } else {
                fn_800506E8(0, slot, 1);
            }
        } else {
            fn_800506E8(*(s8*)&lbl_8034E9A0.ports[idx], slot, 1);
        }
        fn_80067B40(b, slot, 1);
        return;
    }
    {
        u8* r2 = lbl_803C6724;
        r2 += a;
        slot = *(s8*)(r2 + 2);
    }
    fn_800506E8(0, slot, 1);
    lbl_8034E9A0.charFlag[slot] = 1;
    fn_80067B40(b, slot, 1);
}

// fn_2_1DC8, size:0x168
void fn_2_1DC8(void) {
    switch (lbl_2_bss_F410._00) {
    case 0:
        lbl_8034E9A0._4708 = 0;
        ((u8*)&g_d_GameSettings)[7] = 0;
        break;
    case 1:
        lbl_8034E9A0._4708 = 1;
        ((u8*)&g_d_GameSettings)[7] = 5;
#ifdef TARGET_PC
        changeScene(4, 6); // Career goes straight into a game, like Toy Field (port/game/career.c)
#endif
        break;
    case 3:
        lbl_8034E9A0._4708 = 3;
        ((u8*)&g_d_GameSettings)[7] = 7;
        changeScene(4, 6);
        break;
    case 2:
        lbl_8034E9A0._4708 = 2;
        ((u8*)&g_d_GameSettings)[7] = 6;
        changeScene(4, 6);
        break;
    case 4:
        lbl_8034E9A0._4708 = 4;
        ((u8*)&g_d_GameSettings)[7] = 2;
        ((u8*)&g_d_GameSettings)[9] = 0;
        ((u8*)&g_d_GameSettings)[0xA] = 2;
        changeScene(4, 6);
        break;
    case 6:
        lbl_8034E9A0._4708 = 6;
        break;
    case 5:
        lbl_8034E9A0._4708 = 5;
        break;
    }
    lbl_803CBBCC->step = 5;
    fn_800625A4(0, 0x58);
}

// fn_2_6484, size:0x184
void fn_2_6484(void) {
    switch (lbl_2_bss_F468._33) {
    case 0:
        if (lbl_803C66B0.step[0] == 0 || lbl_803C66B0.step[1] == 0) {
            if (lbl_2_bss_F468._34 == 0) {
                fn_800625A4(0, 0x1E);
                lbl_2_bss_F468._34 = 1;
            }
            lbl_2_bss_F468._33 = 1;
        }
        break;
    case 1:
        if (lbl_803C66B0.step[0] == 0 || lbl_803C66B0.step[1] == 0) {
            ((void (*)(void))fn_2_87A8)();
        }
        break;
    case 2:
        if (lbl_803C66B0.step[0] == 0 || lbl_803C66B0.step[1] == 0) {
            lbl_8034E9A0._472A = 1;
            if (lbl_2_bss_F468._35 == 0) {
                lbl_2_bss_F468._2E = 0;
                lbl_2_bss_100B4 = 1;
                lbl_803CBBCC->step = 8;
                fn_800625A4(0, 0x13);
                fn_800625A4(1, 0x13);
            } else {
                fn_800625A4(1, 0x12);
                lbl_803CBBCC->step = 2;
            }
            lbl_2_bss_F468._35 = 0;
            lbl_2_bss_F468._33 = 0;
        }
        break;
    }
}

// fn_2_6608, size:0x17C
void fn_2_6608(void) {
    s32 i;
    u8* p;
    if (lbl_2_bss_F468._59[0] != 0) {
        fn_2_3624(0);
    } else if (lbl_2_bss_F468._59[1] != 0 && lbl_2_bss_100B8._2E[0] != 0 && ((u8*)&g_d_GameSettings)[0x10] == 0) {
        fn_2_3624(0);
    } else {
        fn_2_104FC(0);
    }
    if (((u8*)&g_d_GameSettings)[0x10] == 1) {
        if (lbl_2_bss_F468._59[1] != 0) {
            fn_2_3624(1);
        } else {
            fn_2_104FC(1);
        }
    }
    if (lbl_2_bss_F468._56 != 0) {
        lbl_803C5EA4._08[1] = 0;
        lbl_803C5EA4._08[0] = 0;
        lbl_2_bss_100B8._30[1] = 0;
        lbl_2_bss_100B8._30[0] = 0;
        if (((u8*)&g_d_GameSettings)[0x10] == 0) {
            lbl_2_bss_F468.cursor[0] = 9;
            lbl_803C66B0.portOf[0] = 0;
        }
        for (i = 0; i < 2; i++) {
            if (lbl_2_bss_F468._59[i] != 0) {
                CALL_FN_800625A4_S32(i, 0x1B);
                lbl_2_bss_F468._59[i] = 0;
            } else {
                CALL_FN_800625A4_S32(i, 0xB);
            }
        }
    }
}


// fn_2_9F70, size:0xD0
s32 fn_2_9F70(s8 team) {
    s32 result;
    u8 other;
    s32 i;
    s32 j;
    u8 v;
    other = lbl_2_bss_F468._2F[team ^ 1];
    switch (lbl_2_bss_F468._10[(s8)lbl_2_bss_F468._2F[team]]) {
    case 1:
        result = 2;
        break;
    case 2:
        result = 1;
        break;
    case 3:
        result = 1;
        break;
    }
retry:
    for (i = 0; i < 9; i++) {
        v = inMemRoster[(s8)other][i].stats.CharID;
        for (j = 0; j < 9; j++) {
            if (v == 0) {
                if (result == 1 || result == 2) {
                    return 3;
                }
                result = 2;
                goto retry;
            }
        }
    }
    return result;
}

// fn_2_6784, size:0x100
void fn_2_6784(void) {
    s32 i;
    s32 j;
    u8 dup;
    u8 v;
    for (i = 0; i < 9; i++) {
        if (i == 0) {
            lbl_8034E9A0.captain[1] = 0;
            lbl_803C6724[0xB] = 0;
            lbl_803C6724[0x53] = 1;
            lbl_8034E9A0.charFlag[lbl_803C6724[0xB]] = 1;
        } else {
            do {
                dup = 0;
                v = lbl_80109038[randRange_FUN_80042bf0(0, 9)];
                for (j = 0; j < i; j++) {
                    if (*(s8*)(lbl_803C6724 + j + 0xB) == v) {
                        dup = 1;
                    }
                }
            } while (dup);
            lbl_803C6724[i + 0xB] = v;
            lbl_803C6724[i + 0x53] = 1;
            lbl_8034E9A0.charFlag[v] = 1;
        }
        lbl_80354720[1][i]._0 = i;
        lbl_80354720[1][i].slot = i;
        lbl_80354720[1][i]._1 = i;
    }
}

static inline void fn_2_87A8_work(s32 prev) {
    MenuPad* pad;
    u16 b;
    pad = (MenuPad*)&lbl_803C77B8;
    pad += *(s8*)&lbl_8034E9A0.ports[0];
    b = pad->repeat;
    if (b & 8) {
        if ((lbl_2_bss_F410._4C = prev - 1) < 0) {
            lbl_2_bss_F410._4C = 3;
        }
        if (prev != lbl_2_bss_F410._4C) {
            fn_800625A4(0, 0x20);
        }
        ((void (*)(u32))fn_2_1C34)(8);
    } else if (b & 4) {
        if ((lbl_2_bss_F410._4C = prev + 1) == 4) {
            lbl_2_bss_F410._4C = 0;
        }
        if (prev != lbl_2_bss_F410._4C) {
            fn_800625A4(0, 0x20);
        }
        ((void (*)(u32))fn_2_1C34)(4);
    } else if (pad->down & 0x200) {
        lbl_2_bss_F468._33 = 2;
        lbl_2_bss_F468._34 = 0;
        lbl_2_bss_F468._35 = 1;
        lbl_803C5EA4._0E = 1;
        fn_800625A4(1, 0x1F);
        ((void (*)(u32))fn_2_1C34)(0x200);
    } else if (pad->down & 0x100) {
        lbl_800E8754[3] = lbl_803CB8D0[prev];
        fn_800625A4(0, 0x21);
        lbl_2_bss_F468._33 = 2;
        lbl_2_bss_F468._34 = 0;
        lbl_2_bss_F468._35 = 0;
        ((void (*)(u32))fn_2_1C34)(0x100);
    }
}

// fn_2_87A8, size:0x194
void fn_2_87A8(void) {
    s32 prev = lbl_2_bss_F410._4C;
    if (lbl_803C66B0.active[0] != 0 || lbl_803C66B0.active[1] != 0) {
        return;
    }
    fn_2_87A8_work(prev);
}

// NONMATCHING 80%: lo/hi register allocation and scheduling around the inlined fn_2_1554
#if NONMATCHING
// fn_2_14F8, size:0x5C
s32 fn_2_14F8(s32 a, s32 b) {
    s32 lo;
    s32 hi;
    if (a == b) {
        return a;
    }
    if (a <= b) {
        lo = a;
        hi = b;
    } else {
        lo = b;
        hi = a;
    }
    return (s32)(fn_2_1554() >> 16) % (hi - lo + 1) + lo;
}
#endif

// NONMATCHING 95%: (base + i + 9)[2] folded into one displacement; loop counters in other regs
#if NONMATCHING
// fn_2_A1A0, size:0xE8
void fn_2_A1A0(s32 count, s32 team) {
    s32 i;
    s32 v;
    u8* row = lbl_803C6724 + (u8)team * 9;
retry:
    while (lbl_8034E9A0.charFlag[0] != 0) {
    }
    for (i = 0; i < (u8)count; i++) {
        s32 idx = i + 2;
        if (g_d_GameSettings._10 == 0 && lbl_2_bss_100B8._2E[0] != 0) {
            v = (s8)(lbl_803C6724 + i)[2];
        } else {
            v = (s8)row[idx];
        }
        if (v == 0) {
            goto retry;
        }
        if (g_d_GameSettings._10 == 0 && lbl_2_bss_100B8._2E[0] != 0) {
            v = (s8)(lbl_803C6724 + i + 9)[2];
        } else {
            v = (s8)row[idx];
        }
        if (v == 0) {
            goto retry;
        }
    }
    (lbl_803C6724 + (u8)team * 9 + (u8)count)[2] = 0;
}
#endif

#define g_Pads ((MenuPad*)&lbl_803C77B8)

// fn_2_1A88, size:0x124
void fn_2_1A88(void) {
    s32 n;
    s32 i;
    lbl_8034E9A0.ports[0] = 0;
    n = 1;
    for (i = 1; i < 4; i++) {
        if (g_Pads[i].err != -1) {
            lbl_8034E9A0.ports[n++] = i;
        }
    }
    while (n < 4) {
        *(s8*)&lbl_8034E9A0.ports[n++] = -1; // n runs to 4: also clears _46FA
    }
}

// fn_2_348C, size:0x144
void fn_2_348C(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 6; i++) {
        s32 locked = g_d_GameSettings._1A[i] == 0;
        for (j = 0; j < 0x36; j++) {
            if (lbl_803CB748[i] == lbl_800E8558[j].lockId) {
                lbl_8034E9A0.charFlag[j] = locked;
            }
        }
        lbl_803CB748[i] = lbl_803CB748[i];
    }
}

// NONMATCHING 85%: team kept in two regs (raw + clrlwi) differently; loop counter/pointer regs swapped
#if NONMATCHING
// fn_2_5184, size:0x148
void fn_2_5184(u8 team) {
    s32 i;
    s8* row;
    lbl_2_bss_F468._3D[team] = 0;
    if (g_d_GameSettings.GameModeSelected == 5) {
        return;
    }
    if (lbl_2_bss_F468._37[team] == 0) {
        fn_2_102C8(team);
        lbl_2_bss_F468.cursor[team] = 9;
        return;
    }
    row = (s8*)(lbl_803C6724 + team * 9);
    for (i = 0; i < 9; i++) {
        if (lbl_8034E9A0.captain[team] != row[2]) {
            lbl_8034E9A0.charFlag[row[2]] = 0;
            fn_800506E8(*(s8*)&lbl_8034E9A0.ports[team], row[2], 0);
            fn_80067B40(team, row[2], 0);
            row[2] = -1;
            row[0x4A] = 0;
            row[0x26] = 0;
        }
        row++;
    }
    lbl_2_bss_F468._37[team] = 0;
    lbl_2_bss_F468._43[team] = 1;
    fn_800625A4(team, 0x19);
}
#endif

// NONMATCHING 85%: register allocation/scheduling of the selection pointer; the trailing loop really never exits in the original
#if NONMATCHING
// fn_2_EAE0, size:0x154
void fn_2_EAE0(void) {
    s32 i;
    s32* sel;
    s32 port;
    for (i = 0; i < (g_d_GameSettings._10 == 1) + 1; i++) {
        if (lbl_803C5EA4._08[i] != 0) {
            sel = &lbl_2_bss_F410.charSel[i + 4];
            if (lbl_8034E9A0.charFlag[lbl_800FDE84[*sel]] != 0) {
                do {
                    do {
                        (*sel)++;
                        if (*sel == 0x36) {
                            *sel = 0;
                        }
                    } while (lbl_8034E9A0.charFlag[lbl_800FDE84[*sel]] != 0);
                } while (lbl_2_bss_F410.charSel[4] == lbl_2_bss_F410.charSel[5]);
            }
            for (;;) {
                port = *(s8*)&lbl_8034E9A0.ports[i];
                if (lbl_8034E9A0._46FC[port] != 0) {
                    port = *(s8*)&lbl_8034E9A0.ports[0] == 0;
                }
                ((void (*)(s32*, u8, s32))fn_2_1D54)(&lbl_2_bss_F410.charSel[i + 4], port, 0x36);
            }
        }
    }
}
#endif

// NONMATCHING 90%: team*4 index recomputed from the raw u8 param (clrlslwi) instead of reusing the clrlwi copy
#if NONMATCHING
// fn_2_CCE0, size:0x164
void fn_2_CCE0(u8 team) {
    s32 i;
    if (lbl_2_bss_F468._37[team] != 0) {
        return;
    }
    for (i = 0; i < 9; i++) {
        s32 v = (s8)(lbl_803C6724 + team * 9)[i + 2];
        if (v == -1 || v == 0x36) {
            break;
        }
    }
    if (i == 9) {
        lbl_2_bss_F468._37[team] = 1;
        lbl_2_bss_F468.prevCursor[team] = lbl_2_bss_F468.cursor[team];
        lbl_2_bss_F468.cursor[team] = 9;
        lbl_2_bss_F468._41[team] = 0;
        fn_800625A4(team, 0x14);
        fn_80050138(1, -1, -1, -1, -1, 0);
    } else {
        lbl_2_bss_F468.prevCursor[team] = lbl_2_bss_F468.cursor[team];
        lbl_2_bss_F468.cursor[team] = (s8)(lbl_803C6724 + team * 9)[i + 0x14];
        fn_800625A4(team, 0xE);
    }
}
#endif

// NONMATCHING 98%: case 4 store scheduling (lbl_2_bss_3A0 address via addi in the original)
// nmverify: fn_2_2FC0 fn_2_8940 inlined on one side (calls match once expanded)
#if NONMATCHING
// fn_2_323C, size:0x180
void fn_2_323C(void) {
    switch (lbl_2_bss_3A0[0]) {
    case 0:
        fn_800B0A5C_insertQueue(fn_8004D0F0, 0x3000);
        lbl_2_bss_3A0[0]++;
        break;
    case 1:
        switch (fn_8004CA6C(lbl_8034E9A0.input[lbl_803CBD24[4]].pressed)) {
        case 0:
            break;
        case 1:
            fn_8004CC2C();
            break;
        case 3:
            fn_2_2FC0(0xA, 1, 1);
            lbl_803CBD24[4] = 0;
            fn_800625A4(0, 0x13);
            fn_800625A4(1, 0x13);
            changeScene(0xF, 6);
            lbl_2_bss_3A0[0] = 0;
            lbl_2_bss_F468._2E = 0;
            lbl_2_bss_100B4 = 1;
            lbl_803CBBCC->step = 8;
            break;
        case 2:
            fn_8004CC2C();
            break;
        case 4:
            lbl_2_bss_3A0[0] = 0;
            lbl_803CBD24[4] = 0;
            lbl_803297E0._CF5F = 0;
            lbl_803CBBCC->step = 2;
            break;
        }
        break;
    }
}
#endif

// NONMATCHING 75%: same instructions, store order/scheduling differs (second loop never runs, as in the original)
#if NONMATCHING
// fn_2_B324, size:0x1E4
void fn_2_B324(void) {
    s32 i;
    s32 base0 = lbl_8034E9A0.captain[0];
    s32 base1 = lbl_8034E9A0.captain[1];
    for (i = 0; i < 9; i++) {
        lbl_80354720[0][i]._0 = i;
        lbl_80354720[1][i]._0 = i;
        lbl_80354720[0][i]._1 = i;
        lbl_80354720[1][i]._1 = i;
        lbl_80354720[0][i].slot = i;
        lbl_80354720[1][i].slot = i;
        lbl_80354720[0][i]._3 = 1;
        lbl_80354720[1][i]._3 = 1;
        lbl_80353B98[0][i]._0 = i;
        lbl_80353B98[1][i]._0 = i;
        lbl_80353B98[0][i]._1 = i;
        lbl_80353B98[1][i]._1 = i;
        lbl_80353B98[0][i].slot = i;
        lbl_80353B98[1][i].slot = i;
        inMemRoster[0][i].stats.CharID = base0 + i;
        inMemRoster[1][i].stats.CharID = base1 + i;
    }
    for (; i < 9; i++) {
        lbl_80354720[0][i]._0 = i;
        lbl_80354720[1][i]._0 = i;
        lbl_80354720[0][i]._1 = -1;
        lbl_80354720[1][i]._1 = -1;
        lbl_80354720[0][i].slot = -1;
        lbl_80354720[1][i].slot = -1;
        lbl_80354720[0][i]._3 = -1;
        lbl_80354720[1][i]._3 = -1;
        lbl_80353B98[0][i]._0 = i;
        lbl_80353B98[1][i]._0 = i;
        lbl_80353B98[0][i]._1 = -1;
        lbl_80353B98[1][i]._1 = -1;
        lbl_80353B98[0][i].slot = -1;
        lbl_80353B98[1][i].slot = -1;
        inMemRoster[0][i].stats.CharID = 0;
        inMemRoster[1][i].stats.CharID = 0;
    }
}
#endif

// NONMATCHING 93%: random id kept as mr+extsh instead of extsh in place; loop regs rotated
#if NONMATCHING
// fn_2_FAA0, size:0x214
void fn_2_FAA0(s32 team) {
    s32 i;
    s32 g;
    s32 k;
    s16 id;
    s32 w = lbl_8034E9A0.captain[(u8)team];
    u8* row = lbl_803C6724 + (u8)team * 9;
    for (i = 0; i < 9; i++) {
        s32 v = (s8)row[2];
        if (v == -1 || v == 0x36) {
            do {
                id = randRange_FUN_80042bf0(0, 0x35);
            } while (lbl_8034E9A0.charFlag[id] != 0);
            fn_80067B40(team, id, 1);
            for (g = 0; g < 9; g++) {
                for (k = 0; k < 5; k++) {
                    if (id == lbl_80108EDC[g][k]) {
                        s16* grp = lbl_80108EDC[g];
                        lbl_8034E9A0.charFlag[grp[1]] = 1;
                        lbl_8034E9A0.charFlag[grp[2]] = 1;
                        lbl_8034E9A0.charFlag[grp[3]] = 1;
                        lbl_8034E9A0.charFlag[grp[4]] = 1;
                        id = grp[0];
                        goto found;
                    }
                }
            }
        found:
            if (g_d_GameSettings._10 == 0 && (u8)team != 0) {
                if (*(s8*)&lbl_8034E9A0.ports[0] == 0) {
                    fn_800506E8(1, id, 1);
                } else {
                    fn_800506E8(1, id, 1);
                }
            } else {
                fn_800506E8(*(s8*)&lbl_8034E9A0.ports[(u8)team], id, 1);
            }
            row[2] = id;
            lbl_8034E9A0.charFlag[id] = 1;
            row[0x26] = CS_STATS(id)->chem[w];
        }
        row++;
    }
}
#endif

// fn_2_C484, size:0x214
void fn_2_C484(s32 owner, s16 id) {
    s32 i;
    for (i = 0; i < 0x36; i++) {
        if (i == id) {
            lbl_8034E9A0.charFlag[i] = 0;
            if (g_d_GameSettings.GameModeSelected == 5) {
                if (fn_2_C324(i) == -1) {
                    fn_800506E8(owner & 0xFF, i, 0);
                }
            } else {
                fn_800506E8(owner & 0xFF, i, 0);
                fn_80067B40(owner, i, 0);
            }
            return;
        }
    }
}

#define g_Roster ((CharacterStats*)inMemRoster)

// fn_2_11EA8, size:0x228
void fn_2_11EA8(void) {
    CharacterStats* src;
    s32 i;
    s8 sel;
    for (i = 0; i < 9; i++) {
        sel = *(s8*)(lbl_803C6724 + i + 2);
        src = CS_STATS(sel);
        MENU_COPY_CHAR_STATS(&g_Roster[i], src);
        lbl_80354720[0][i].slot = i;
        lbl_80354720[0][i]._1 = i;
        lbl_80354720[0][i]._0 = i;
    }
}

// NONMATCHING 88%: original keeps raw + two clrlwi copies of team (r27/r29/r30); we keep one
// nmverify: fn_2_ABC0 inlined on one side (calls match once expanded)
#if NONMATCHING
// fn_2_102C8, size:0x234
void fn_2_102C8(u8 team) {
    s32 i;
    s32 empty = 0;
    s32 other;
    u8* flag;
    for (i = 0; i < 9; i++) {
        s32 v = (s8)(lbl_803C6724 + team * 9)[i + 2];
        if (v == -1 || v == 0x36) {
            empty++;
        }
    }
    other = team ^ 1;
    if (lbl_2_bss_F468._41[other] != 0) {
        flag = &lbl_8034E9A0.charFlag[lbl_2_bss_F410.charSel[other + 4]];
        if (*flag == 0) {
            *flag = 1;
            lbl_2_bss_F468._3B[team] = 1;
        }
    }
    if (empty != 0) {
        do {
            lbl_803CBD24[2] = randRange_FUN_80042bf0(0, 2);
        } while (lbl_803CBD24[3] == lbl_803CBD24[2]);
        fn_2_ABC0(team);
        switch (lbl_803CBD24[2]) {
        case 0:
            fn_2_FCB4(team);
            break;
        case 1:
            fn_2_FAA0(team);
            break;
        case 2:
            fn_2_F200(team);
            break;
        }
        fn_800678CC(team);
        unsure_FillRosterPositions(team);
        fn_800625A4(team, 0x16);
        lbl_803CBD24[3] = lbl_803CBD24[2];
        lbl_2_bss_F468._37[team] = 1;
    } else {
        lbl_2_bss_F468.cursor[team] = 9;
        fn_800625A4(team, 0x11);
    }
    if (lbl_2_bss_F468._3B[team] != 0) {
        lbl_2_bss_F468._3B[team] = 0;
        lbl_8034E9A0.charFlag[lbl_2_bss_F410.charSel[other + 4]] = 0;
    }
}
#endif

// fn_2_110B0, size:0x244
void fn_2_110B0(void) {
    SceneFlow* scene = lbl_803CBBCC;
    s32 ok;
    switch (scene->step) {
    case 0:
        if (g_d_GameSettings.GameModeSelected == 5 || scene->prevScene != 9) {
            scene->step = 5;
        } else {
            lbl_803297E0._CFA1 = 0;
            scene->step = 1;
        }
        break;
    case 1:
        fn_2_86EC();
        break;
    case 2:
        if (g_d_GameSettings.GameModeSelected == 5) {
            ok = lbl_8037169C.done;
        } else {
            ok = 1;
        }
        if (ok) {
            ((void (*)(void))fn_2_6608)();
        }
        break;
    case 3:
        if ((s8)lbl_2_bss_F468._36 < 0 && lbl_803C66B0.step[0] == 0 && lbl_803C66B0.step[1] == 0) {
            fn_2_72630();
            lbl_2_bss_F468._33 = 0;
            lbl_803CBBCC->step = 4;
        } else {
            lbl_2_bss_F468._36--;
        }
        break;
    case 4:
        ((void (*)(void))fn_2_6484)();
        break;
    case 5:
        fn_2_6D3C();
        break;
    case 6:
        fn_2_323C();
        break;
    case 7:
        if ((s8)lbl_2_bss_F468._36 < 0) {
            fn_800625A4(0, 0x13);
            fn_800625A4(1, 0x13);
            lbl_2_bss_F468._4F = 0;
            lbl_2_bss_F468._2E = 0;
            lbl_2_bss_100B4 = 1;
            lbl_803CBBCC->step = 8;
        } else {
            lbl_2_bss_F468._36--;
        }
        break;
    case 8:
        fn_2_61A0();
        break;
    }
}

// fn_2_2FC0, size:0x244
void fn_2_2FC0(u8 mode, s32 b, s32 c) {
    switch (mode) {
    case 9:
        fn_800684A4();
        if (c == 0) {
            break;
        }
    case 10:
        memset(lbl_8034E9A0.charFlag, 0, sizeof(lbl_8034E9A0.charFlag));
        (lbl_8034E9A0.charFlag)[lbl_8034E9A0.captain[0]] = 1;
        (lbl_8034E9A0.charFlag)[lbl_8034E9A0.captain[1]] = 1;
        fn_2_348C();
        fn_80067F70(0);
        fn_80067F70(1);
        fn_2_8940();
        fn_800678CC(0);
        fn_800678CC(1);
        unsure_FillRosterPositions(0);
        unsure_FillRosterPositions(1);
        characterSelectScreen(0);
        characterSelectScreen(1);
        fn_80069854();
        if (c == 0) {
            break;
        }
    case 12:
        fn_800671FC();
        if (b != 0) {
            fn_800649BC();
        }
        break;
    case 11:
        break;
    }
}

// NONMATCHING 90%: preset base (+0x4380) hoisted differently; the ==1 test is cmpwi (enum field) in the original
#if NONMATCHING
// fn_2_6AF4, size:0x248
void fn_2_6AF4(void) {
    u8 idx = 0; // uninitialized in the original if no captain matches
    s32 i;
    u8 id;
    for (i = 0; i < 12; i++) {
        if ((s8)CHALLENGE->_441F == lbl_80108EC4[i]) {
            idx = i;
            break;
        }
    }
    for (i = 0; i < 9; i++) {
        id = lbl_8034E9A0.presets[idx][i];
        lbl_80354720[1][i]._0 = i;
        lbl_80354720[1][i].slot = i;
        lbl_80354720[1][i]._1 = i;
        lbl_803C6724[0xB + i] = ((CharacterStats*)&lbl_8034E9A0.roster[(u8)(id / 9)][(u8)(id % 9)])->stats.CharID;
        lbl_803C6724[0x53 + i] = 1;
    }
    lbl_8034E9A0.captain[0] = CHALLENGE->_441D;
    lbl_8034E9A0.captain[1] = (s8)CHALLENGE->_441F;
    for (i = 0; i < 9; i++) {
        if (CHALLENGE->chars[(s8)lbl_803C6724[0xB + i]]._31 == 1) {
            lbl_803C6724[0xB + i] = 0x36;
        }
    }
}
#endif

// NONMATCHING 80%: inlines fn_2_A1A0 (itself NONMATCHING) and fn_2_C698; slot index scheduling differs
#if NONMATCHING
// fn_2_CA60, size:0x25C
void fn_2_CA60(u8 slot, s32 team) {
    s32 v = (s8)(lbl_803C6724 + (u8)team * 9)[slot + 2];
    if (v != -1 && v != 0x36) {
        MenuOrderEntry* order = lbl_80354720[(u8)team];
        order[slot]._1 = slot;
        order[slot]._0 = slot;
        g_Roster[(u8)team * 9 + slot].stats.CharID = v;
    } else {
        fn_2_A1A0(slot, team);
    }
    fn_2_C698(slot, team);
}
#endif

// NONMATCHING 97%: register-only diff inside the inlined fn_2_C324 (r12/r30/r31 rotated)
#if NONMATCHING
// fn_2_6884, size:0x270
void fn_2_6884(void) {
    s32 i;
    s32 k;
    s8 g;
    for (i = 0; i < 9; i++) {
        s16 id = CHALLENGE->order[i].charId;
        lbl_803C6724[i + 2] = id;
        lbl_80354720[0][i]._1 = CHALLENGE->order[i]._2;
        lbl_80354720[0][i]._0 = i;
        lbl_803C6724[i + 0x4A] = 1;
        lbl_80354720[0][i].slot = i;
        lbl_8034E9A0.charFlag[(u8)id] = 1;
        g = fn_2_C324((u8)id);
        if (g != -1) {
            for (k = 0; k < 5; k++) {
                s16 v = lbl_80108EDC[g][k];
                if (v != -1) {
                    lbl_8034E9A0.charFlag[v] = 1;
                }
            }
        }
    }
}
#endif

// NONMATCHING 70%: retry loop shape (slot==0 test inside the loop in the original) and store addressing differ; inlines fn_2_C698
// nmverify: fn_2_14F8 inlined on one side (calls match once expanded)
#if NONMATCHING
// fn_2_C7DC, size:0x284
void fn_2_C7DC(u8 slot, s32 team) {
    s32 id;
    s32 j;
    MenuOrderEntry* order;
    MenuOrderEntry* order2;
    if (slot == 0) {
        order = &lbl_80354720[(u8)team][slot];
        order2 = &lbl_80353B98[(u8)team][slot];
        order->_1 = slot;
        order2->_1 = slot;
        order2->_0 = slot;
        order->_0 = slot;
        order->slot = slot;
        g_Roster[(u8)team * 9 + slot].stats.CharID = lbl_8034E9A0.captain[(u8)team];
        order2->slot = slot;
        return;
    }
retry:
    id = fn_2_14F8(0, 0x35);
    if (lbl_8034E9A0.charFlag[lbl_800FDE84[id]] != 0) {
        goto retry;
    }
    for (j = 0; j < slot; j++) {
        if (g_Roster[j].stats.CharID == id || g_Roster[9 + j].stats.CharID == id) {
            goto retry;
        }
    }
    order = &lbl_80354720[(u8)team][slot];
    order2 = &lbl_80353B98[(u8)team][slot];
    order->_1 = slot;
    order->_0 = slot;
    order2->_1 = slot;
    order2->_0 = slot;
    order->slot = slot;
    g_Roster[(u8)team * 9 + slot].stats.CharID = id;
    order2->slot = slot;
    fn_2_C698(slot, team);
}
#endif

// NONMATCHING 70%: the original fully unrolls the 8-entry preset scan; flag reads use [1],[2] after writing [0],[1] exactly as the original does
#if NONMATCHING
// fn_2_A288, size:0x284
void fn_2_A288(void) {
    u8 idx = 0; // uninitialized in the original if the captain isn't found
    u8 n = 0;
    s32 i;
    s32 k;
    s32 j;
    for (i = 0; i < 12; i++) {
        if (lbl_80108EC4[i] == lbl_8034E9A0.captain[0]) {
            lbl_8034E9A0._470B = i;
            idx = i;
        } else if (lbl_80108EC4[i] == lbl_8034E9A0.captain[1]) {
            lbl_8034E9A0._470C = i;
        }
    }
    for (k = 1; k < 3; k++) {
        for (j = 1; j < 9; j++) {
            u8 v = lbl_8034E9A0.presets[idx][k * 0x12 + j];
            if (v == lbl_8034E9A0.captain[1] && v != 0xFF) {
                lbl_2_bss_3E0[k - 1] = -1;
            }
        }
        if ((s8)lbl_2_bss_3E0[k - 1] == -1) {
            lbl_2_bss_3E0[k - 1] = 0;
        } else {
            lbl_2_bss_3E0[k - 1] = 1;
        }
    }
    for (k = 1; k < 3; k++) {
        if ((s8)lbl_2_bss_3E0[k] == 0) {
            n++;
        }
    }
    if (n == 2) {
        lbl_2_bss_3E0[0] = -1;
    }
}
#endif

#ifdef TARGET_PC
s32 port_menu_mode_enabled(s32 entry);
s32 port_stadium_select_enabled(void);
#endif

// fn_2_1800, size:0x288
void fn_2_1800(void) {
    MenuButtons b;
    u16 repeat;
    memset(&b, 0, sizeof(b));
    b.held = lbl_8034E9A0.input[0].held;
    b.down = lbl_8034E9A0.input[0].pressed;
    b.repeat = repeat = lbl_8034E9A0.input[0].repeat;
    if (lbl_803C66B0.active[0] != 0) {
        return;
    }
    if (b.down & 0x100) {
#ifdef TARGET_PC
        if (!port_menu_mode_enabled(lbl_2_bss_F410._00)) {
            return; // not offered on PC (port/game/menu_scope.c)
        }
#endif
        fn_2_1DC8();
        lbl_80366158._27 = 0;
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (b.down & 0x200) {
        lbl_80366158._29 = 2;
        lbl_8034E9A0._472A = 0;
        lbl_803CBBCC->step = 6;
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
    } else if ((b.repeat & 8) || (b.repeat & 4)) {
        lbl_2_bss_F410._04 = lbl_2_bss_F410._00;
        if (repeat & 8) {
            if (--lbl_2_bss_F410._00 < 0) {
                lbl_2_bss_F410._00 = 6;
            }
        } else if (repeat & 4) {
            if (++lbl_2_bss_F410._00 == 7) {
                lbl_2_bss_F410._00 = 0;
            }
        }
#ifdef TARGET_PC
        // Skip the modes the port doesn't offer (port/game/menu_scope.c).
        while (!port_menu_mode_enabled(lbl_2_bss_F410._00)) {
            if (repeat & 8) {
                if (--lbl_2_bss_F410._00 < 0) {
                    lbl_2_bss_F410._00 = 6;
                }
            } else if (++lbl_2_bss_F410._00 == 7) {
                lbl_2_bss_F410._00 = 0;
            }
        }
#endif
        fn_800625A4(0, 0x56);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// fn_2_1578, size:0x288
void fn_2_1578(void) {
    MenuButtons b;
    u16 repeat;
    memset(&b, 0, sizeof(b));
    b.held = lbl_8034E9A0.input[0].held;
    b.down = lbl_8034E9A0.input[0].pressed;
    b.repeat = repeat = lbl_8034E9A0.input[0].repeat;
    if (lbl_803C66B0.active[0] != 0) {
        return;
    }
    if (b.down & 0x100) {
        fn_2_1DC8();
        lbl_80366158._27 = 0;
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (b.down & 0x200) {
        lbl_80366158._29 = 2;
        lbl_8034E9A0._472A = 0;
        lbl_803CBBCC->step = 6;
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
    } else if ((b.repeat & 8) || (b.repeat & 4)) {
        lbl_2_bss_F410._04 = lbl_2_bss_F410._00;
        if (repeat & 8) {
            if (--lbl_2_bss_F410._00 < 0) {
                lbl_2_bss_F410._00 = 6;
            }
        } else if (repeat & 4) {
            if (++lbl_2_bss_F410._00 == 7) {
                lbl_2_bss_F410._00 = 0;
            }
        }
        fn_800625A4(0, 0x56);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// NONMATCHING 93%: same instructions, scheduling/register rotation in the unrolled pick loop
#if NONMATCHING
// fn_2_2D1C, size:0x2A4
void fn_2_2D1C(void) {
    s32 t;
    s32 i;
    lbl_8034E9A0.captain[0] = 10;
    lbl_8034E9A0.captain[1] = 2;
    for (t = 0; t < 2; t++) {
        s16* tbl = (s16*)lbl_2_data_E64 + t * 9;
        for (i = 0; i < 9; i++) {
            s32 v = tbl[i];
            lbl_803C6724[t * 9 + i + 2] = v;
            lbl_803C6724[t * 9 + i + 0x26] =
                CS_STATS(v)->chem[lbl_8034E9A0.captain[t]];
        }
    }
    for (t = 0; t < 2; t++) {
        for (i = 0; i < 9; i++) {
            lbl_80354720[t][i].slot = i;
            lbl_80354720[t][i]._1 = i;
            lbl_80354720[t][i]._0 = i;
        }
    }
}
#endif

// NONMATCHING 85%: the original inlines fn_2_CA60 (NONMATCHING) into the slot loop; fn_2_14F8 must stay a call
// nmverify: fn_2_14F8 fn_2_ABC0 inlined on one side (calls match once expanded)
#if NONMATCHING
// fn_2_B66C, size:0x2B4
void fn_2_B66C(void) {
    s8 pick;
    s32 k;
    s32 i;
    fn_2_A6E0();
    if ((s8)lbl_2_bss_3E0[0] == -1) {
        pick = -1;
    } else {
        do {
            k = fn_2_14F8(1, 2);
        } while ((s8)lbl_2_bss_3E0[k] == 0);
        pick = k;
    }
    switch (pick) {
    case 0:
        lbl_2_bss_F468._10[1] = 1;
        break;
    case 1:
        lbl_2_bss_F468._10[1] = 2;
        break;
    case -1:
        lbl_2_bss_F468._10[1] = 3;
        break;
    }
    fn_2_ABC0(1);
    for (i = 0; i < 9; i++) {
        fn_2_CA60(i, 1);
    }
}
#endif

// NONMATCHING 99%: two li constants scheduled differently in the CF5F branch
#if NONMATCHING
// fn_2_61A0, size:0x2E4
void fn_2_61A0(void) {
    s32 i;
    s32 t;
    s32 j;
    if (fn_80062578() == 0) {
        return;
    }
    if (lbl_2_bss_F468._2E == 0) {
        if (fn_80050F78(0) == 0) {
            lbl_803C66B0.active[1] = 1;
            lbl_803C66B0.active[0] = 1;
            return;
        }
    } else if (fn_80050F78(2) == 0) {
        lbl_803C66B0.active[1] = 1;
        lbl_803C66B0.active[0] = 1;
        return;
    }
    if ((s8)lbl_2_bss_F468._36 > 0) {
        lbl_2_bss_F468._36--;
        return;
    }
    lbl_803C66B0.active[1] = 0;
    lbl_803C66B0.active[0] = 0;
    if (lbl_2_bss_F468._2E == 0) {
        if (lbl_803297E0._CF5F != 0) {
            fn_2_19F2C();
            lbl_8034E9A0._48AD = 1;
            lbl_803C66B0.steps[0][0] = 0;
            memset(&lbl_803C66B0.steps[0][1], 0, 6);
            lbl_8034E9A0._4755 = 3;
            fn_80062A74();
            fn_80021410();
            fn_80035CA4(0xF);
            fn_80035CA4(0x12);
            fn_80035CA4(9);
            fn_80035CA4(6);
            lbl_8034E9A0._48AF = 1;
            lbl_8034E9A0._48B1 = 1;
            lbl_8034E978._26 = 1;
            lbl_803297E0._CF5F = 0;
            fn_2_11A0(4);
        } else {
            lbl_2_bss_F468._28 = 0;
            lbl_2_bss_F468._29 = 0;
            lbl_2_bss_F468._2A = 0;
            lbl_2_bss_F468._2B = 0;
            lbl_2_bss_F468._2C = 0;
            fn_2_8940();
            fn_2_AEE8();
            lbl_803C66B0.steps[0][0] = 0;
            memset(&lbl_803C66B0.steps[0][1], 0, 6);
            lbl_8034E9A0._48B1 = 1;
            fn_2_11A0(0xB);
            for (i = 1; i < 9; i++) {
                fn_80021AC0(0, i);
                fn_80021AC0(1, i);
            }
        }
    } else {
        if (lbl_8034E978._24 != 0) {
            return;
        }
        lbl_2_bss_F468._41[1] = 0;
        lbl_2_bss_F468._41[0] = 0;
        lbl_2_bss_F468._37[1] = 0;
        lbl_2_bss_F468._37[0] = 0;
        for (t = 0; t < 2; t++) {
            for (j = 0; j < 9; j++) {
                lbl_803C6724[t * 9 + j + 0x4A] = 0;
            }
        }
        fn_2_11A0(9);
        lbl_803CBBCC->prevStep = 0;
    }
    fn_800AD038((void*)lbl_8034E9A0.heapMarkA[0]);
    lbl_8034E9A0._4755 = 3;
    lbl_8034E9A0._472A = 0;
    lbl_8034E9A0._48AD = 1;
}
#endif

// NONMATCHING 85%: captain-stats pointer setup and the sort's cached chem[i] register differ
#if NONMATCHING
// fn_2_ABC0, size:0x328
void fn_2_ABC0(u8 team) {
    u8 chem[0x36];
    u8 ids[0x36];
    s32 i;
    s32 j;
    s32 cap = lbl_8034E9A0.captain[team];
    CharacterStats* c = CS_STATS(cap);
    for (i = 0; i < 0x36; i++) {
        ids[i] = i;
        chem[i] = c->chem[i];
    }
    for (i = 0; i < 0x36; i++) {
        for (j = i + 1; j < 0x36; j++) {
            if (chem[i] < chem[j]) {
                u8 tc = chem[i];
                u8 ti = ids[i];
                chem[i] = chem[j];
                ids[i] = ids[j];
                chem[j] = tc;
                ids[j] = ti;
            }
        }
    }
    for (i = 0; i < 0x36; i++) {
        lbl_8034E9A0.chemOrder[team][i] = ids[i];
    }
}
#endif

// NONMATCHING 80%: stadium-selection pointer kept in a register differently; branch layout of the button chain
// nmverify: fn_2_14F8 fn_2_1C34 inlined on one side (calls match once expanded)
#if NONMATCHING
// fn_2_11340, size:0x358
void fn_2_11340(u8 team) {
    u8 found = 0;
    s32* stadium = &lbl_2_bss_F410._44;
    s32 prev;
    s32 r;
    s8 port;
    u16 repeat;
    u16 down;
    if (lbl_803CBCD8[0] != 0) {
        prev = *stadium;
        do {
            if (lbl_80361B20._F5 != 0) {
                r = fn_2_14F8(0, 5);
            } else {
                r = fn_2_14F8(0, 4);
            }
        } while (prev == r);
        *stadium = r;
        lbl_803CBCD8[1]--;
        fn_800625A4(0, 0x28);
        return;
    }
    if (lbl_803C66B0.active[0] != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected != 5) {
        port = lbl_8034E9A0.ports[team];
        if (g_d_GameSettings.PlayerPorts[0] == port) {
            found = 1;
        }
        if (g_d_GameSettings.PlayerPorts[1] == port) {
            found = 1;
        }
        lbl_8034E9A0.ports[team] = port;
        if (!found) {
            return;
        }
    } else if (team != 0) {
        return;
    }
    repeat = lbl_8034E9A0.input[team].repeat;
    down = lbl_8034E9A0.input[team].pressed;
#ifdef TARGET_PC
    if (!port_stadium_select_enabled()) {
        // Mario Stadium only (port/game/menu_scope.c): no moving, no roulette.
        *stadium = 0;
        repeat &= ~3;
        down &= ~0x20;
    }
#endif
    if (repeat & 1) {
        if (lbl_803C66B0.step[0] != 0x24) {
            if (--*stadium < 0) {
                *stadium = 5;
            }
            fn_800625A4(0, 0x28);
            fn_2_1C34(1);
        }
    } else if (repeat & 2) {
        if (lbl_803C66B0.step[0] != 0x24) {
            if (++*stadium == 6) {
                *stadium = 0;
            }
            fn_800625A4(0, 0x28);
            fn_2_1C34(2);
        }
    } else if (down & 0x20) {
        if (g_d_GameSettings.GameModeSelected != 5) {
            lbl_803CBCD8[0] = 1;
            lbl_803CBCD8[1] = 6;
        }
    } else if (down & 0x100) {
        if (*stadium < 6) {
            if (lbl_80361B20._F5 == 0 && lbl_2_data_130C[*stadium] == 1) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            } else if (lbl_803C66B0.step[0] == 0) {
                g_d_GameSettings.StadiumID = lbl_2_data_130C[*stadium];
                lbl_2_bss_F468._58 = 1;
                fn_2_328();
                fn_2_1C34(0x100);
                fn_800625A4(0, 0x25);
                lbl_803CBBCC->step = 4;
            }
        }
    } else if (down & 0x200) {
        if (lbl_803CBCD8[0] == 0 && lbl_803C66B0.step[0] == 0) {
            fn_2_2DC();
            fn_2_1C34(0x200);
            lbl_803CBBCC->prevScene = 0xC;
            fn_800625A4(0, 0x24);
            lbl_803CBBCC->step = 3;
        }
    }
}
#endif

// NONMATCHING 75%: the original inlines fn_2_CA60 (NONMATCHING) into the slot loop
#if NONMATCHING
// fn_2_BF90, size:0x394
void fn_2_BF90(void) {
    s32 idx = -1;
    s32 i;
    memset(lbl_8034E9A0.charFlag, 0, sizeof(lbl_8034E9A0.charFlag));
    for (i = 0; i < 12; i++) {
        if (lbl_80108EC4[i] == (s8)CHALLENGE->_441F) {
            lbl_8034E9A0._470C = i;
            idx = (u8)i;
        }
    }
    lbl_2_bss_F468._10[1] = 0;
    lbl_2_bss_F468._10[0] = 0;
    for (i = 0; i < 9; i++) {
        lbl_803C6724[0xB + i] = lbl_8034E9A0.presets[idx][i];
    }
    for (i = 0; i < 9; i++) {
        fn_2_CA60(i, 1);
    }
}
#endif

// NONMATCHING 90%: mode-5 copy loop register/scheduling; inlined fn_2_52CC indexes F468 via slwi/stwx in the original
#if NONMATCHING
// fn_2_5444, size:0x3A4
void fn_2_5444(u8 team) {
    s32 i;
    u8 s10;
    lbl_2_bss_F468._3D[team] = 0;
    if (g_d_GameSettings.GameModeSelected == 5) {
        for (i = 0; i < 9; i++) {
            s16 id = (s8)lbl_803C6724[i + 2];
            u8 pos = lbl_803C6724[i + 0x14];
            CHALLENGE->order[i].charId = id;
            CHALLENGE->order[i]._2 = i;
            CHALLENGE->order[i]._3 = pos;
            g_Roster[i].stats.CharID = id;
            lbl_80354720[0][i].slot = pos;
        }
        fn_800625A4(0, 0x13);
        fn_800625A4(1, 0x13);
        lbl_2_bss_F468._2E = 0;
        lbl_2_bss_100B4 = 1;
        lbl_803CBBCC->step = 8;
        return;
    }
    s10 = g_d_GameSettings._10;
    if (s10 == 0 && lbl_2_bss_100B8._2E[0] != 0) {
        fn_800625A4(1, 0x11);
        lbl_8034E9A0._472A = 0xFF;
        lbl_2_bss_F468._36 = 0x1E;
        lbl_803CBBCC->step = 3;
    } else if (s10 == 0) {
        fn_2_52CC();
        fn_800625A4(0, 0x11);
    } else if (s10 == 1) {
        lbl_2_bss_100B8._2E[team] = 1;
        fn_800625A4(team, 0x11);
        if (lbl_2_bss_100B8._2E[0] != 0 && lbl_2_bss_100B8._2E[1] != 0) {
            lbl_2_bss_F468._4F = 1;
            lbl_2_bss_F468._36 = 0x1E;
            lbl_803CBBCC->step = 7;
        }
    }
}
#endif

// NONMATCHING 88%: copy-loop induction registers differ (r14-r16 vs r17-r19); v >> 1 is extrwi in the original
#if NONMATCHING
// fn_2_8940, size:0x3B8
void fn_2_8940(void) {
    s32 t;
    s32 i;
    s8 sel;
    CharacterStats* src;
    CharacterStats* dst;
    for (t = 0; t < 2; t++) {
        for (i = 0; i < 9; i++) {
            sel = lbl_803C6724[t * 9 + i + 2];
            src = CS_STATS(sel);
            dst = &g_Roster[t * 9 + i];
            MENU_COPY_CHAR_STATS(dst, src);
            lbl_80354720[t][i].slot = lbl_803C6724[t * 9 + i + 0x14];
            if (t == 0 && g_d_GameSettings.GameModeSelected == 5) {
                s32 v = lbl_2_bss_3A8[CHALLENGE->order[i].charId];
                dst->stats.FieldingArm = v >> 1;
                dst->stats.BattingStance = v % 2;
            }
        }
    }
    for (t = 0; t < 2; t++) {
        for (i = 0; i < 9; i++) {
            lbl_803C5EA4._12[t][i] = (s8)lbl_803C6724[t * 9 + i + 2];
        }
    }
    fn_80066EAC(0);
    fn_80066EAC(1);
}
#endif

// NONMATCHING 85%: lbl_2_data_180 and the state pointer are hoisted once in the original; case bodies laid out differently
#if NONMATCHING
static inline void fn_2_27E0_init(void) {
    initializeUnknown();
    lbl_8034E9A0._4700 = 0;
    lbl_8034E9A0._472A = 0xFF;
    lbl_8034E9A0._4756 = 0;
    lbl_8034E9A0._4754 = 0;
    lbl_8034E9A0._4755 = 3;
    lbl_8034E9A0._48B3 = 0;
    lbl_8034E9A0._4701 = 0;
    lbl_8034E9A0._4702 = 0;
    lbl_8034E9A0._4703 = 0;
    lbl_8034E9A0._4704 = 0;
    lbl_8034E9A0._4705 = 0;
    lbl_8034E9A0._4706 = 0;
    lbl_8034E9A0._4707 = 0;
    lbl_8034E9A0._4700 = 1;
    if (lbl_803CBBCC->prevScene != 1) {
        fn_80062764(lbl_803CC1B8);
    }
    lbl_2_bss_20[0]++;
}

// fn_2_27E0, size:0x3D8
void fn_2_27E0(void) {
    s16 v;
    switch (lbl_2_bss_20[0]) {
    case 0:
        fn_2_19F2C();
        switch (lbl_803CBBCC->prevScene) {
        case 8:
            lbl_2_bss_20[0] = 3;
            break;
        case 6:
        case 9:
        case 12:
            lbl_2_bss_20[0] = 0xC;
            break;
        case 15:
            if (lbl_8034E9A0._4756 == 0) {
                lbl_2_bss_20[0] = 0xC;
                break;
            }
        default:
            fn_2_27E0_init();
            break;
        }
        break;
    case 1:
        lbl_2_bss_20[0]++;
    case 2:
        if (fn_80022B68() != 0) {
            lbl_2_bss_20[0]++;
        }
        break;
    case 3:
        fn_2_12988();
        lbl_2_bss_20[0]++;
        break;
    case 4:
        if (fn_800697B0() == 0) {
            lbl_2_bss_20[0]++;
        }
        break;
    case 5:
        if (fn_80035838(lbl_2_data_180 + 0x2C4, 6) != 0) {
            lbl_2_bss_20[0]++;
        }
        break;
    case 6:
        if (fn_80035838(lbl_2_data_180 + 0x2D4, 9) != 0) {
            lbl_2_bss_20[0]++;
        }
        break;
    case 7:
        if (fn_80035838(lbl_2_data_180 + 0x2E4, 0x12) != 0) {
            lbl_2_bss_20[0]++;
        }
        break;
    case 8:
        if (fn_80035838(lbl_2_data_180 + 0x2F4, 0xF) != 0) {
            if (lbl_803CBBCC->prevScene == 1) {
                lbl_2_bss_20[0] = 0xB;
            } else {
                lbl_2_bss_20[0]++;
            }
        }
        break;
    case 9:
        if (lbl_8034E9A0._48B4 != 0) {
            if (lbl_803CBCE0[0] == 0) {
                fn_8003F23C();
            }
            lbl_2_bss_20[0]++;
        } else {
            lbl_2_bss_20[0] = 0xB;
        }
        break;
    case 10:
        if (lbl_803CBCE0[0] == 0) {
            v = lbl_803CC1B8->_10;
            if (v == 1 || v == 0xB) {
                lbl_803CBCE0[0] = 1;
                lbl_80361B20._DE[0] = 1;
                lbl_80361B20._DE[1] = 1;
                lbl_80361B20._DE[2] = 1;
                lbl_80361B20._DE[3] = 1;
                lbl_80361B20._DE[4] = 1;
                lbl_80361B20._DE[5] = 1;
                lbl_2_bss_20[0]++;
            }
        } else {
            lbl_2_bss_20[0]++;
        }
        break;
    case 11:
        if (lbl_803CBBCC->prevScene != 6 && lbl_803C6714[4] == 0) {
            fn_800B0A5C_insertQueue(fn_80062A94, 0x1000);
        }
        lbl_803CBBCC->step = 0;
        lbl_2_bss_20[0]++;
        break;
    case 12:
        fn_2_1F30();
        break;
    }
}
#endif

// NONMATCHING 80%: same shape as fn_2_ABC0 for both teams; pointer/induction registers differ
#if NONMATCHING
// fn_2_AEE8, size:0x43C
void fn_2_AEE8(void) {
    u8 chem[0x36];
    u8 ids[2][0x36];
    s32 t;
    s32 i;
    s32 j;
    s32 cap;
    CharacterStats* c;
    for (t = 0; t < 2; t++) {
        for (i = 0; i < 0x36; i++) {
            ids[t][i] = i;
        }
    }
    for (t = 0; t < 2; t++) {
        cap = lbl_8034E9A0.captain[t];
        c = CS_STATS(cap);
        for (i = 0; i < 0x36; i++) {
            chem[i] = c->chem[i];
        }
        for (i = 0; i < 0x36; i++) {
            for (j = i + 1; j < 0x36; j++) {
                if (chem[i] < chem[j]) {
                    u8 tc = chem[i];
                    u8 ti = ids[t][i];
                    chem[i] = chem[j];
                    ids[t][i] = ids[t][j];
                    chem[j] = tc;
                    ids[t][j] = ti;
                }
            }
        }
    }
    for (t = 0; t < 2; t++) {
        for (i = 0; i < 0x36; i++) {
            lbl_8034E9A0.chemOrder[t][i] = ids[t][i];
        }
    }
}
#endif

// NONMATCHING 85%: register allocation and branch layout differ; fn_2_35D0 inlines as in the original
#if NONMATCHING
static inline void fn_2_ED94_toggle(u8 team, u16 held) {
    if (lbl_2_bss_F468._47[team] == 0 && (held & 2)) {
        lbl_2_bss_F468._47[team] = 1;
        lbl_2_bss_F468._49[team] = 0;
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (lbl_2_bss_F468._47[team] == 1 && (held & 1)) {
        lbl_2_bss_F468._47[team] = 0;
        lbl_2_bss_F468._49[team] = 0;
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// fn_2_ED94, size:0x46C
s32 fn_2_ED94(u8 team, u16 held, u16 pressed, s32 dirs) {
    s8 owner;
    if (lbl_2_bss_F468._41[team] == 0) {
        if ((held & 8) || (held & 4) || (held & 1) || (held & 2)) {
            if (lbl_2_bss_F468._45[team] != 0) {
                fn_2_ED94_toggle(team, held);
                dirs = 0;
                pressed = 0;
                held = 0;
            }
            if (lbl_2_bss_F468._59[team] != 0) {
                dirs = 0;
                pressed = 0;
                held = 0;
            }
            fn_2_57F0(team, held, pressed, dirs);
            return 1;
        }
    } else {
        if (lbl_2_bss_F468._59[team] != 0) {
            lbl_2_bss_F468._41[team] = 0;
            fn_800625A4(team, 0xD);
            return 1;
        }
        if (lbl_2_bss_F468.cursor[team] != 9) {
            lbl_2_bss_F468._20[team] = lbl_2_bss_F410.charSel[team + 4];
            if (lbl_2_bss_F468._45[team] != 0) {
                fn_2_ED94_toggle(team, held);
                if (g_d_GameSettings._10 == 0 && team != 0) {
                    owner = *(s8*)&lbl_8034E9A0.ports[0] == 0;
                    lbl_803C6028[0x74 + owner] = 1;
                    lbl_2_bss_F410.charSel[team + 4] = fn_80050760(owner, 0, 0, 0, 0);
                } else {
                    owner = *(s8*)&lbl_8034E9A0.ports[team];
                    if (lbl_8034E9A0._46FC[owner] != 0) {
                        owner = *(s8*)&lbl_8034E9A0.ports[0] == 0;
                    }
                    lbl_2_bss_F410.charSel[team + 4] = fn_80050760(owner, 0, 0, 0, 0);
                }
            } else if (g_d_GameSettings._10 == 0 && team != 0) {
                owner = *(s8*)&lbl_8034E9A0.ports[0] == 0;
                lbl_803C6028[0x74 + owner] = 1;
                lbl_2_bss_F410.charSel[team + 4] = fn_80050760(owner, held, pressed, dirs, 0);
            } else {
                owner = *(s8*)&lbl_8034E9A0.ports[team];
                if (lbl_8034E9A0._46FC[owner] != 0) {
                    owner = *(s8*)&lbl_8034E9A0.ports[0] == 0;
                }
                lbl_2_bss_F410.charSel[team + 4] = fn_80050760(owner, held, pressed, dirs, 0);
            }
        }
    }
    if (pressed & 0x100) {
        if (fn_2_35D0(team)) {
            return 1;
        }
        fn_2_DFAC(team);
        return 1;
    }
    if (pressed & 0x200) {
        if (fn_2_35D0(team)) {
            return 1;
        }
        fn_2_CE44(team);
        return 1;
    }
    return 0;
}
#endif

#define FN_2_9ACC_RESTORE(t, i)                                                   \
    do {                                                                          \
        CharacterStats* dst = &g_Roster[(t) * 9 + (i)];                            \
        CharacterStats* src = &((CharacterStats*)lbl_2_bss_E8CC)[(t) * 9 + (i)];    \
        MenuOrderEntry* order = &lbl_80354720[(t)][(i)];                          \
        MenuOrderEntry* saved = &((MenuOrderEntry(*)[9])lbl_2_bss_DCE8)[(t)][(i)];                        \
        MENU_COPY_CHAR_STATS(dst, src);                                           \
        order->_0 = saved->_0;                                                      \
        order->_1 = saved->_1;                                                      \
        order->slot = saved->slot;                                                      \
        dst->stats.CharID = lbl_8034E9A0.captain[(t)];                      \
        order->_3 = saved->_3;                                                      \
    } while (0)

// NONMATCHING 90%: same instructions modulo induction registers (r18-r22 vs r26-r31)
#if NONMATCHING
// fn_2_9ACC, size:0x4A4
void fn_2_9ACC(u16 team) {
    s32 t;
    s32 i;
    if (g_d_GameSettings._10 == 1) {
        for (i = 0; i < 9; i++) {
            if (lbl_2_bss_100B8._30[team] != 0) {
                FN_2_9ACC_RESTORE(team, i);
            }
        }
        return;
    }
    for (t = 0; t < 2; t++) {
        for (i = 0; i < 9; i++) {
            if (lbl_2_bss_100B8._30[t] != 0) {
                FN_2_9ACC_RESTORE(t, i);
            }
        }
    }
}
#endif

// NONMATCHING 85%: both duplicate scans inline as in the original; registers and flag-store forms differ
#if NONMATCHING
static inline s32 fn_2_A6E0_shared(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 9; i++) {
        s8 a = lbl_803C6724[2 + i];
        for (j = 0; j < 9; j++) {
            if (a == (s8)lbl_803C6724[0xB + j] && a != -1) {
                return 1;
            }
        }
    }
    return 0;
}

// fn_2_A6E0, size:0x4E0
void fn_2_A6E0(void) {
    s32 k;
    s32 n = 0;
    if (g_d_GameSettings.GameModeSelected == 5) {
        return;
    }
    if (lbl_2_bss_100B8._2E[0] != 0 && g_d_GameSettings._10 == 0) {
        lbl_2_bss_3E0[1] = fn_2_A50C() == 0;
        lbl_2_bss_3E0[2] = fn_2_A50C() == 0;
        if ((s8)lbl_2_bss_3E0[1] == 0 && (s8)lbl_2_bss_3E0[2] == 0) {
            lbl_2_bss_3E0[0] = -1;
        }
    } else {
        for (k = 1; k < 3; k++) {
            if (fn_2_A6E0_shared() == 0) {
                lbl_2_bss_3E0[k - 1] = 1;
            } else {
                lbl_2_bss_3E0[k - 1] = 0;
            }
            if (fn_2_A6E0_shared() == 0) {
                lbl_2_bss_3E0[k + 1] = 1;
            } else {
                lbl_2_bss_3E0[k + 1] = 0;
            }
        }
        if ((s8)lbl_2_bss_3E0[0] == 0) {
            n = 1;
        }
        if ((s8)lbl_2_bss_3E0[1] == 0) {
            n++;
        }
        if ((s8)lbl_2_bss_3E0[2] == 0) {
            n++;
        }
        if ((s8)lbl_2_bss_3E0[3] == 0) {
            n++;
        }
        if (n == 4) {
            lbl_2_bss_3E0[0] = -1;
        }
    }
}
#endif

// NONMATCHING 87%: only computes colours/slots into locals (the draw calls that used them
// are compiled out), so it has no side effects; kept as a readable reconstruction. The original
// reloads starMissionCompletionTracker[0x441F] per team and ends with a dead compare chain on
// lbl_803CBBCC+4 (2..3, 9, 0x13, 4) that no C form here reproduces.
#if NONMATCHING
// fn_2_95D8, size:0x4F4
void fn_2_95D8(void) {
    u32 color[2];
    s8 slot[2][9];
    s8 used[0x36];
    s32 t;
    s32 i;
    s32 j;
    s32 sel;
    s32 cap;
    s32 n;
    if (lbl_803CBBCC->step < 4) {
        for (t = 0; t < 2; t++) {
            if (t == 0) {
                sel = lbl_2_bss_F468.cursor[t];
            } else {
                sel = lbl_2_bss_F468.cursor[t] - 10;
            }
            if (t == 0) {
                color[t] = 0xFF0F;
            } else {
                color[t] = 0xF00F;
            }
            for (i = 0; i < 9; i++) {
                for (j = 0; j < 9; j++) {
                    if (i == (s8)lbl_80354720[t][j]._1) {
                        break;
                    }
                }
                if (g_d_GameSettings.GameModeSelected != 5) {
                    cap = lbl_8034E9A0.captain[t];
                } else if (t == 0) {
                    cap = lbl_8034E9A0.captain[t];
                } else {
                    cap = (s8)CHALLENGE->_441F;
                }
                if ((s8)lbl_803C6724[t * 9 + i + 2] == cap) {
                    color[t] = 0x88FF;
                } else if (i == sel) {
                    color[t] = 0xFF0F;
                } else {
                    color[t] = 0xFFFF;
                }
            }
        }
        n = 5;
        for (t = 0; t < 2; t++) {
            for (i = 0; i < 9; i++) {
                slot[t][i] = -1;
            }
        }
        for (i = 0; i < 0x36; i++) {
            used[i] = -1;
        }
        for (i = 0; i < 0x36; i++) {
            if (i == lbl_2_bss_F410.charSel[4]) {
                color[0] = 0xFFF;
            } else if (i == lbl_2_bss_F410.charSel[5]) {
                color[1] = 0xF0FF;
            } else {
                color[0] = 0xFFFF;
                color[1] = 0xFFFF;
            }
            for (t = 0; t < 2; t++) {
                for (j = 0; j < 9; j++) {
                    if (i == (s8)lbl_803C6724[t * 9 + j + 2] && t == 0 && color[0] != 0xFFF) {
                        used[i] = i;
                        color[0] = 0x88F;
                        slot[t][j] = i;
                    } else if (i == (s8)lbl_803C6724[t * 9 + j + 2] && t != 0 && color[0] != 0xFFF) {
                        used[i] = i;
                        color[0] = 0x808F;
                        slot[t][j] = i;
                    }
                }
            }
            if (lbl_8034E9A0.charFlag[i] != 0 && used[i] == -1) {
                color[0] = 0x888F;
            }
            if (g_d_GameSettings._10 != 1 || i != lbl_2_bss_F410.charSel[5]) {
                n++;
            }
            if (n == 0x1A) {
                n = 6;
            }
        }
    }
}
#endif

// NONMATCHING 80%: chemOrder entry reloads/addressing and loop registers differ
// nmverify: fn_2_14F8 inlined on one side (calls match once expanded)
#if NONMATCHING
// fn_2_FCB4, size:0x614
void fn_2_FCB4(u8 team) {
    s8 cand[0x36];
    s32 empty = 0;
    s32 cap = lbl_8034E9A0.captain[team];
    s32 i;
    s32 j;
    s32 g;
    s32 k;
    s8 r;
    s8 id;
    s8 t;
    s16* grp;
    u8* row;
    u8* other;
    u8 ot;
    memset(cand, -1, 0x36);
    for (i = 0; i < 0x36; i++) {
        for (g = 0; g < 9; g++) {
            for (k = 1; k < 5; k++) {
                if (lbl_8034E9A0.chemOrder[team][i] == lbl_80108EDC[g][k]) {
                    lbl_8034E9A0.charFlag[lbl_8034E9A0.chemOrder[team][i]] = 1;
                }
            }
        }
        if (lbl_8034E9A0.charFlag[lbl_8034E9A0.chemOrder[team][i]] == 0) {
            cand[i] = lbl_8034E9A0.chemOrder[team][i];
        }
    }
    for (i = 0; i < 0x36; i++) {
        for (j = i; j < 0x36; j++) {
            t = cand[i];
            if (t == -1 && cand[j] != -1) {
                cand[i] = cand[j];
                cand[j] = t;
            }
        }
    }
    row = lbl_803C6724 + team * 9;
    for (i = 0; i < 9; i++) {
        s32 v = (s8)row[i + 2];
        if (v == -1 || v == 0x36) {
            empty++;
        }
    }
    for (i = 0; i < 9; i++) {
        s32 v = (s8)row[i + 2];
        if (v != -1 && v != 0x36) {
            continue;
        }
        do {
            r = fn_2_14F8(0, (s8)(0x14 - (9 - empty)));
            id = cand[r];
        } while (id == -1 || lbl_8034E9A0.charFlag[id] == 1);
        cand[r] = -1;
        lbl_8034E9A0.charFlag[id] = 1;
        if (g_d_GameSettings._10 == 0 && team != 0) {
            if (*(s8*)&lbl_8034E9A0.ports[0] == 0) {
                fn_800506E8(1, id, 1);
            } else {
                fn_800506E8(1, id, 1);
            }
        } else {
            fn_800506E8(*(s8*)&lbl_8034E9A0.ports[team], id, 1);
        }
        fn_80067B40(team, id, 1);
        for (g = 0; g < 9; g++) {
            for (k = 0; k < 5; k++) {
                if (id == lbl_80108EDC[g][k]) {
                    grp = lbl_80108EDC[g];
                    id = grp[0];
                    for (k = 0; k < 5; k++) {
                        s16 m = grp[k];
                        if (m != -1) {
                            for (j = 0; j < 0x36; j++) {
                                if (cand[j] == m) {
                                    cand[j] = -1;
                                }
                            }
                        }
                    }
                    goto found;
                }
            }
        }
    found:
        row[i + 2] = id;
        empty--;
        row[i + 0x26] = CS_STATS(id)->chem[cap];
    }
    for (i = 0; i < 45; i++) {
        lbl_8034E9A0.charFlag[lbl_80108EDC[0][i]] = 0;
    }
    ot = team ^ 1;
    other = lbl_803C6724 + ot * 9;
    for (i = 0; i < 9; i++) {
        fn_80067B40(ot, other[i + 2], 1);
        fn_80067B40(team, row[i + 2], 1);
    }
    if (g_d_GameSettings._1A[5] == 0) {
        lbl_8034E9A0.charFlag[53] = 1;
        lbl_8034E9A0.charFlag[52] = 1;
        lbl_8034E9A0.charFlag[27] = 1;
    }
}
#endif

// NONMATCHING 70%: the original inlines fn_2_CA60 (NONMATCHING) and fully unrolls the team-1 reset loop
// nmverify: fn_2_14F8 fn_2_ABC0 inlined on one side (calls match once expanded)
#if NONMATCHING
// fn_2_B920, size:0x670
void fn_2_B920(void) {
    u8 idx0 = 0;
    u8 idx1 = 0;
    s32 i;
    s8 pick;
    s32 k;
    s32 type;
    memset(lbl_8034E9A0.charFlag, 0, sizeof(lbl_8034E9A0.charFlag));
    if (g_d_GameSettings.GameModeSelected != 5) {
        for (i = 0; i < 12; i++) {
            if (lbl_80108EC4[i] == lbl_8034E9A0.captain[0]) {
                lbl_8034E9A0._470B = i;
                idx0 = i;
            } else if (lbl_80108EC4[i] == lbl_8034E9A0.captain[1]) {
                lbl_8034E9A0._470C = i;
                idx1 = i;
            }
        }
    } else {
        for (i = 0; i < 12; i++) {
            if (lbl_80108EC4[i] == CHALLENGE->_441D) {
                lbl_8034E9A0._470B = i;
            } else if (lbl_80108EC4[i] == (s8)CHALLENGE->_441F) {
                lbl_8034E9A0._470C = i;
            }
        }
    }
    fn_2_A288();
    if ((s8)lbl_2_bss_3E0[0] != -1) {
        do {
            k = fn_2_14F8(1, 2);
        } while ((s8)lbl_2_bss_3E0[k] == 0);
        pick = k;
    } else {
        pick = -1;
    }
    switch (pick) {
    case 0:
        lbl_2_bss_F468._10[0] = 1;
        break;
    case 1:
        lbl_2_bss_F468._10[0] = 2;
        break;
    case -1:
        lbl_2_bss_F468._10[0] = 3;
        break;
    }
    lbl_2_bss_F468._10[1] = 3;
    for (i = 0; i < 9; i++) {
        lbl_803C6724[i + 2] = lbl_8034E9A0.presets[idx0][lbl_2_bss_F468._10[0] * 0x12 + i];
    }
    type = lbl_2_bss_F468._10[1];
    for (i = 0; i < 9; i++) {
        lbl_803C6724[i + 0xB] = lbl_8034E9A0.presets[idx1][type * 0x12 + i];
    }
    lbl_2_bss_F468._10[1] = type;
    fn_2_ABC0(0);
    lbl_8034E9A0.charFlag[lbl_8034E9A0.captain[1]] = 1;
    for (i = 0; i < 9; i++) {
        fn_2_CA60(i, 0);
    }
    for (i = 0; i < 9; i++) {
        lbl_80354720[1][i].slot = i;
        lbl_80353B98[1][i].slot = i;
        lbl_803C6724[0xB + i] = (i == 0) ? (s8)lbl_8034E9A0.captain[1] : 0x36;
        lbl_803C6724[0x53 + i] = (i == 0) ? 1 : 0;
    }
}
#endif

// NONMATCHING 75%: the original repeats the sound call per branch and indexes state via stwx; same transitions
// nmverify: sndFXStartEx repeated per branch in original (tail duplication)
// nmverify:  inlined on one side (calls match once expanded)
#if NONMATCHING
// fn_2_57F0, size:0x790
void fn_2_57F0(u8 team, u16 held, u16 pressed, u16 repeat) {
    MenuTeamSel* state = &lbl_2_bss_F468;
    u8* done = lbl_2_bss_F468._37;
    state->prevCursor[team] = state->cursor[team];
    if ((repeat & 8) || (pressed & 8)) {
        if (state->cursor[team] == 9) {
            state->cursor[team] = 2;
            fn_800625A4(team, 0xE);
        } else if (state->cursor[team] == 10) {
            if (done[team] != 0) {
                state->cursor[team] = 9;
                fn_800625A4(team, 0x18);
            } else {
                state->cursor[team] = 2;
                fn_800625A4(team, 0xE);
            }
        } else {
            switch (state->cursor[team]) {
            case 0: state->cursor[team] = 5; break;
            case 1: state->cursor[team] = 0; break;
            case 2: state->cursor[team] = 8; break;
            case 3: state->cursor[team] = 7; break;
            case 4: state->cursor[team] = 6; break;
            case 5: state->cursor[team] = 7; break;
            case 6: state->cursor[team] = 4; break;
            case 7: state->cursor[team] = 1; break;
            case 8:
                if (g_d_GameSettings.GameModeSelected != 5) {
                    state->cursor[team] = 10;
                } else if (done[team] != 0) {
                    state->cursor[team] = 9;
                } else {
                    state->cursor[team] = 2;
                }
                break;
            }
            if (state->prevCursor[team] != state->cursor[team]) {
                fn_800625A4(team, 0xE);
            }
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if ((repeat & 4) || (pressed & 4)) {
        if (state->cursor[team] == 9) {
            if (g_d_GameSettings.GameModeSelected != 5) {
                state->cursor[team] = 10;
                fn_800625A4(team, 0x18);
            } else {
                state->cursor[team] = 8;
                fn_800625A4(team, 0xE);
            }
        } else if (state->cursor[team] == 10) {
            state->cursor[team] = 8;
            fn_800625A4(team, 0xE);
        } else {
            switch (state->cursor[team]) {
            case 0: state->cursor[team] = 1; break;
            case 1: state->cursor[team] = 7; break;
            case 2:
                if (g_d_GameSettings.GameModeSelected != 5) {
                    if (done[team] != 0) {
                        state->cursor[team] = 9;
                    } else {
                        state->cursor[team] = 10;
                    }
                } else if (done[team] != 0) {
                    state->cursor[team] = 9;
                } else {
                    state->cursor[team] = 8;
                }
                break;
            case 3: state->cursor[team] = 0; break;
            case 4: state->cursor[team] = 6; break;
            case 5: state->cursor[team] = 0; break;
            case 6: state->cursor[team] = 4; break;
            case 7: state->cursor[team] = 5; break;
            case 8: state->cursor[team] = 2; break;
            }
            if (state->prevCursor[team] != state->cursor[team]) {
                fn_800625A4(team, 0xE);
            }
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if ((repeat & 1) || (pressed & 1)) {
        if (state->cursor[team] == 9) {
            state->cursor[team] = 0;
            fn_800625A4(team, 0xE);
        } else if (state->cursor[team] == 10) {
            state->cursor[team] = 1;
            fn_800625A4(team, 0xE);
        } else {
            switch (state->cursor[team]) {
            case 0: state->cursor[team] = 4; break;
            case 1:
                if (g_d_GameSettings.GameModeSelected != 5) {
                    state->cursor[team] = 10;
                } else if (done[team] != 0) {
                    state->cursor[team] = 9;
                } else {
                    return;
                }
                break;
            case 2: state->cursor[team] = 3; break;
            case 3: state->cursor[team] = 5; break;
            case 4: state->cursor[team] = 2; break;
            case 5: state->cursor[team] = 4; break;
            case 6: state->cursor[team] = 8; break;
            case 7: state->cursor[team] = 6; break;
            case 8: state->cursor[team] = 7; break;
            case 9: break;
            case 10: state->cursor[team] = 1; break;
            }
            if (state->prevCursor[team] != state->cursor[team]) {
                fn_800625A4(team, 0xE);
            }
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if ((repeat & 2) || (pressed & 2)) {
        if (state->cursor[team] == 9) {
            state->cursor[team] = 0;
            fn_800625A4(team, 0xE);
        } else if (state->cursor[team] == 10) {
            if (done[team] != 0) {
                state->cursor[team] = 9;
                fn_800625A4(team, 0x18);
            } else {
                state->cursor[team] = 1;
                fn_800625A4(team, 0xE);
            }
        } else {
            switch (state->cursor[team]) {
            case 0:
                if (done[team] != 0) {
                    state->cursor[team] = 9;
                    fn_800625A4(team, 0x18);
                } else {
                    state->cursor[team] = 2;
                    fn_800625A4(team, 0xE);
                }
                break;
            case 1:
                if (g_d_GameSettings.GameModeSelected != 5) {
                    state->cursor[team] = 10;
                } else if (done[team] != 0) {
                    state->cursor[team] = 9;
                } else {
                    return;
                }
                break;
            case 2: state->cursor[team] = 4; break;
            case 3: state->cursor[team] = 2; break;
            case 4: state->cursor[team] = 5; break;
            case 5: state->cursor[team] = 3; break;
            case 6: state->cursor[team] = 7; break;
            case 7: state->cursor[team] = 8; break;
            case 8: state->cursor[team] = 6; break;
            }
            if (state->prevCursor[team] != state->cursor[team]) {
                fn_800625A4(team, 0xE);
            }
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}
#endif

// NONMATCHING 70%: the original inlines fn_2_6784, fn_2_6AF4 and fn_2_6884 (the latter two NONMATCHING here)
#if NONMATCHING
// fn_2_6D3C, size:0x7C8
void fn_2_6D3C(void) {
    if (g_d_GameSettings.GameModeSelected == 5 && lbl_803C5EA4._11 == 0) {
        if (lbl_2_bss_F468._2C == 0) {
            if (lbl_2_bss_F468._2D == 0) {
                fn_800216F8(0x25, fn_8006285C);
                lbl_2_bss_F468._2D = 1;
                return;
            }
            if (lbl_2_bss_F468._2D == 1) {
                if (lbl_803CC1B8->_10 == 0) {
                    return;
                }
                lbl_803CC1B8->_10 = 0;
                initializeUnknown();
                fn_800B0A5C_insertQueue(fn_80062A94, 0x1000);
                lbl_2_bss_F468._2D = 0;
            }
        }
        lbl_2_bss_F468._2C = 1;
        if (lbl_2_bss_F468._28 == 0 && fn_800697B0() != 0) {
            return;
        }
        lbl_2_bss_F468._28 = 1;
        if (lbl_2_bss_F468._29 == 0 && fn_80035838(lbl_2_data_720 + 0x5F4, 6) == 0) {
            return;
        }
        lbl_2_bss_F468._29 = 1;
        if (lbl_2_bss_F468._2A == 0 && fn_80035838(lbl_2_data_720 + 0x604, 9) == 0) {
            return;
        }
        lbl_2_bss_F468._2A = 1;
        if (lbl_2_bss_F468._2B == 0 && fn_80035838(lbl_2_data_720 + 0x624, 0xF) == 0) {
            return;
        }
        lbl_2_bss_F468._2B = 1;
    }
    if (g_d_GameSettings.GameModeSelected == 5 && CHALLENGE->_4445 != 0) {
        CHALLENGE->_4445 = 0;
        lbl_803297E0._CFA1 = 1;
        if (lbl_80361B20._E4[0] != 0) {
            lbl_803297E0._CF70 = 0;
        } else {
            lbl_803297E0._CF70 = 1;
        }
        fn_2_BF90();
        unsure_FillRosterPositions(1);
    } else if (g_d_GameSettings.GameModeSelected == 5 && CHALLENGE->_4445 == 0) {
        if (CHALLENGE->_441D == 9 && (s8)CHALLENGE->_44EF != 0) {
            fn_2_6784();
        } else {
            fn_2_6AF4();
        }
        fn_2_6884();
        lbl_803297E0._CFA1 = 0;
    }
    if (g_d_GameSettings.GameModeSelected == 5) {
        fn_8006496C();
    }
    fn_2_82E58();
    lbl_803CBBCC->step = 1;
}
#endif

// lbl_2_bss_F410._44 through a byte offset: the member access allocates registers differently.
#define F410_STADIUM (*(s32*)((u8*)&lbl_2_bss_F410 + offsetof(MenuSelVars, _44)))

// fn_2_11698, size:0x810
void fn_2_11698(void) {
    s8 best = -1;
    s32 i;
    SceneFlow* scene = lbl_803CBBCC;
    switch (scene->step) {
    case 0:
        if (scene->prevScene == 0xD) {
            fn_800625A4(0, 0x26);
            lbl_803CBBCC->step = 1;
            return;
        }
        if (g_d_GameSettings.GameModeSelected == 5) {
            changeScene(1, 6);
            fn_2_836A4();
            lbl_2_bss_F468._57 = 0;
            for (i = 0; i < 4; i++) {
                if (lbl_80361B20._E4[i] != 0 && best < i) {
                    best = i;
                }
            }
            if (best != -1) {
                lbl_2_bss_F468._57 = best + 1;
                if (lbl_2_bss_F468._57 > 3) {
                    lbl_2_bss_F468._57 = 3;
                }
            }
            lbl_803CBBCC->step = 5;
            return;
        }
        fn_2_85108();
        if (lbl_803C66B0.active[0] == 0 && lbl_803C66B0.active[1] == 0) {
            lbl_8034E978.menu = 5;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[5].track;
            lbl_803C5EA4._36 = 1;
            lbl_803C5EA4.prevMode = lbl_803C5EA4.mode;
            lbl_803C5EA4.mode = 2;
            lbl_803C66B0.steps[0][0] = 4;
            if (lbl_8034E9A0._4703 == 0) {
                F410_STADIUM = 0;
                F410_STADIUM = 0;
            }
            lbl_8034E9A0._4703 = 1;
            fn_800625A4(0, 0x27);
            lbl_803CBBCC->step = 1;
        }
        break;
    case 1:
        if (lbl_803C66B0.active[0] == 0 && lbl_803C66B0.active[1] == 0) {
            lbl_803CBBCC->step = 2;
        }
        break;
    case 2:
        for (i = 0; i < 2; i++) {
            fn_2_11340(i);
        }
        break;
    case 3:
        if (lbl_803CBCD8[4] == 0 && lbl_803C66B0.step[0] == 0) {
            lbl_803C66B0.steps[0][0] = 3;
            lbl_803CBBCC->step = 0xB;
        }
        break;
    case 4:
        if (lbl_803C66B0.step[0] == 0) {
            lbl_2_bss_100B4 = 1;
            lbl_803CBBCC->step = 0xC;
        }
        break;
    case 5:
        if (lbl_803C66B0.active[0] == 0) {
            lbl_803CBBC4[0] = 0;
            lbl_803CBBC4[2] = 0;
            lbl_803CBBC4[3] = 0;
            lbl_803CBBC4[4] = 0;
            F410_STADIUM = 0;
            changeScene(1, 6);
            lbl_803C5EA4._36 = 1;
            lbl_803C5EA4.prevMode = lbl_803C5EA4.mode;
            lbl_803C5EA4.mode = 4;
            lbl_803CBBC4[0] = 0x5D;
            lbl_803CBBC4[5] = 0;
            lbl_803CBBCC->step = 6;
        }
        break;
    case 6:
        if (lbl_803C66B0.active[0] == 0) {
            lbl_803CBBC4[1] = F410_STADIUM;
            fn_2_15A90(&F410_STADIUM, 0, lbl_2_bss_F468._57);
            lbl_8034E9A0._4711 = F410_STADIUM;
            if (lbl_803CBBC4[1] != (u8)F410_STADIUM) {
                lbl_803CBBC4[0] = 0x5E;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            if (lbl_8034E9A0.input[0].pressed & 0x100) {
                if (F410_STADIUM < 6) {
                    if (lbl_80361B20._E4[lbl_8034E9A0._4711 - 1] == 0 && lbl_8034E9A0._4711 != 0) {
                        sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                        return;
                    }
                    lbl_803CBBC4[0] = 0x60;
                    lbl_8034E9A0._472A = 1;
                    ((void (*)(u32))fn_2_1C34)(0x100);
                    lbl_803CBBCC->step = 7;
                }
            } else if (lbl_8034E9A0.input[0].pressed & 0x200) {
                ((void (*)(u32))fn_2_1C34)(0x200);
                lbl_803CBBC4[0] = 0x60;
                lbl_8034E9A0._472A = 1;
                lbl_803CBBCC->step = 8;
            }
        }
        break;
    case 7:
        if (lbl_803CBBC4[5] != 0) {
            lbl_803CBBC4[5] = 0;
            lbl_2_bss_100B4 = 1;
            lbl_803CBBCC->step = 0xC;
        }
        break;
    case 8:
        if (lbl_803CBBC4[5] != 0) {
            lbl_803CBBCC->step = 0xB;
        }
        break;
    case 9:
        fn_800B0A5C_insertQueue(fn_8004D0F0, 0x3000);
        lbl_803CBBCC->step = 0xA;
        break;
    case 10:
        switch (fn_8004CA6C(lbl_8034E9A0.input[0].pressed)) {
        case 0:
            break;
        case 1:
            fn_8004CC2C();
            break;
        case 3:
            ((void (*)(u8, s32, s32))fn_2_2FC0)(0xC, 1, 1);
            lbl_803CBCD8[4] = 1;
            fn_80035CA4(0xF);
            fn_80035CA4(0x12);
            fn_80035CA4(9);
            fn_80035CA4(6);
            lbl_8034E9A0._48AF = 1;
            lbl_8034E9A0._48B1 = 1;
            lbl_8034E978._26 = 1;
            changeScene(0xF, 6);
            lbl_803CBBCC->step = 0xC;
            lbl_2_bss_758 = 1;
            break;
        case 2:
            fn_8004CC2C();
            break;
        case 4:
            lbl_803297E0._CF5F = 0;
            lbl_803CBBCC->step = 2;
            break;
        }
        break;
    case 11:
        if (g_d_GameSettings.GameModeSelected != 5) {
            if (lbl_803CBCD8[4] == 0 && lbl_803C66B0.step[0] == 0) {
                lbl_803CBCD8[1] = 0;
                lbl_803CBCD8[0] = 0;
                fn_2_11A0(0xB);
                goto reset;
            }
        } else {
            lbl_803CBBC4[4] = 1;
            if (lbl_803C50E8._47 == 0) {
                fn_2_11A0(0xF);
            } else {
                lbl_8034E978._26 = 1;
                lbl_8034E9A0._48AF = 1;
                fn_2_11A0(5);
            }
        reset:
            lbl_803CBBCC->prevStep = 0;
        }
        break;
    case 12:
        if (lbl_2_bss_758 != 0) {
            if (lbl_8034E978._24 == 0) {
                fn_80062A74();
                lbl_2_bss_758 = 0;
                changeScene(0xF, 6);
                fn_2_11A0(4);
            }
        } else if (g_d_GameSettings.GameModeSelected != 5) {
            lbl_803CBCD8[4] = 0;
            lbl_2_bss_F468._58 = 0;
            fn_2_11A0(0xD);
        } else if (lbl_803CBBC4[3] != 1) {
            lbl_803CBBC4[4] = 1;
            fn_2_11A0(9);
        }
        break;
    }
}

// NONMATCHING 87%: the original strength-reduces the roster index into a walking pointer
// (ours indexes) and its prologue/register order differs.
#if NONMATCHING
#define CHAR_CLASS(id) (CS_STATS(id)->stats.CharacterClass)

// Collects the unused character ids of one class from lbl_80108DB8 into cand; returns count - 1.
// cand is only 8 bytes in the original; a longer run spills into the next stack array.
static inline s32 collectClass(s8* cand, u8 cls, s32 last) {
    s32 i;
    s8* p = cand;
    for (i = 0; i < 32; i++) {
        s16 id = (u8)lbl_80108DB8[i];
        if (CHAR_CLASS(id) == cls && lbl_8034E9A0.charFlag[id] == 0) {
            *p++ = id;
            last++;
        }
    }
    return last;
}

// fn_2_F200, size:0x8A0
// Fills the empty roster slots of a team with random unused characters, preferring a class
// (lbl_8034E9A0 +0x31) the team has fewer than two of.
void fn_2_F200(u8 team) {
    s8 cand[8];
    s8 classes[9];
    u8 n1 = 0;
    u8 n2 = 0;
    u8 n3 = 0;
    u8 n0 = 0;
    u8 full1 = 0;
    u8 full2 = 0;
    u8 full3 = 0;
    u8 full0 = 0;
    s32 cap = lbl_8034E9A0.captain[team];
    s8* row;
    s32 i;
    s32 g;
    s32 k;
    s32 last;
    s16 id;

    memset(classes, -1, 9);
    row = (s8*)lbl_803C6724 + team * 9;
    for (i = 0; i < 9; i++) {
        s32 v = row[i + 2];
        if (v != -1 && v != 0x36) {
            classes[i] = CHAR_CLASS(v);
            switch (classes[i]) {
            case 0:
                if (++n0 >= 2) {
                    full0 = 1;
                }
                break;
            case 1:
                if (++n1 >= 2) {
                    full1 = 1;
                }
                break;
            case 2:
                if (++n2 >= 2) {
                    full2 = 1;
                }
                break;
            case 3:
                if (++n3 >= 2) {
                    full3 = 1;
                }
                break;
            }
        }
    }
    for (i = 0; i < 9; i++) {
        s32 v = row[i + 2];
        if (v != -1 && v != 0x36) {
            continue;
        }
        memset(cand, -1, 8);
        last = -1;
        if (full0 == 0) {
            last = collectClass(cand, 0, last);
            if (cand[0] == -1) {
                goto random;
            }
            id = cand[randRange_FUN_80042bf0(0, (s8)last)];
            if (++n0 >= 2) {
                full0 = 1;
            }
        } else if (full1 == 0) {
            last = collectClass(cand, 1, last);
            if (cand[0] == -1) {
                goto random;
            }
            id = cand[randRange_FUN_80042bf0(0, (s8)last)];
            if (++n1 >= 2) {
                full1 = 1;
            }
        } else if (full2 == 0) {
            last = collectClass(cand, 2, last);
            if (cand[0] == -1) {
                goto random;
            }
            id = cand[randRange_FUN_80042bf0(0, (s8)last)];
            if (++n2 >= 2) {
                full2 = 1;
            }
        } else if (full3 == 0) {
            last = collectClass(cand, 3, last);
            if (cand[0] == -1) {
                goto random;
            }
            id = cand[randRange_FUN_80042bf0(0, (s8)last)];
            if (++n3 >= 2) {
                full3 = 1;
            }
        } else {
        random:
            // no class short of two, or none of its characters left: any unused character
            do {
                id = randRange_FUN_80042bf0(0, 0x35);
            } while (lbl_8034E9A0.charFlag[id] != 0);
        }
        fn_80067B40(team, id, 1);
        for (g = 0; g < 9; g++) {
            for (k = 0; k < 5; k++) {
                if (id == lbl_80108EDC[g][k]) {
                    s16* grp = lbl_80108EDC[g];
                    lbl_8034E9A0.charFlag[grp[1]] = 1;
                    lbl_8034E9A0.charFlag[grp[2]] = 1;
                    id = grp[0];
                    lbl_8034E9A0.charFlag[grp[3]] = 1;
                    lbl_8034E9A0.charFlag[grp[4]] = 1;
                    goto found;
                }
            }
        }
    found:
        if (g_d_GameSettings._10 == 0 && team != 0) {
            if (*(s8*)&lbl_8034E9A0.ports[0] == 0) {
                fn_800506E8(1, id, 1);
            } else {
                fn_800506E8(1, id, 1);
            }
        } else {
            fn_800506E8(*(s8*)&lbl_8034E9A0.ports[team], id, 1);
        }
        row[i + 2] = id;
        lbl_8034E9A0.charFlag[id] = 1;
        row[i + 0x26] = CS_STATS(id)->chem[cap];
    }
}
#endif

// NONMATCHING 95%: inlines fn_2_1A88/fn_2_1BAC/fn_2_1800 (the last NONMATCHING); the case-2 button copy reloads one word
#if NONMATCHING
static inline void fn_2_1F30_unload(void) {
    fn_80035B50(0xF);
    fn_80035B50(0x12);
    fn_80035B50(9);
    fn_80035B50(6);
    fn_800AD054((void*)lbl_8034E9A0.heapMarkB[0], (void*)lbl_8034E9A0.heapMarkB[1]);
}

// fn_2_1F30, size:0x8B0
void fn_2_1F30(void) {
    switch (lbl_803CBBCC->step) {
    case 0:
        if (lbl_803CBBCC->prevScene < 5) {
            fn_2_1A88();
        }
        fn_2_1BAC();
        memset(&lbl_8034E9A0._4712, 0, 2); // _4712 and _4713
        lbl_2_bss_F410._00 = lbl_8034E9A0._4712;
        lbl_2_bss_F410._04 = lbl_8034E9A0._4713;
        g_d_GameSettings._10 = 0;
        lbl_803C66B0.steps[0][0] = 0;
        memset(&lbl_803C66B0.steps[0][1], 0, 6);
        lbl_8034E9A0._472A = 0xFF;
        fn_2_74D8C();
        fn_800625A4(0, 0x54);
        (lbl_803CBBCC->step)++;
        break;
    case 1:
        (lbl_803CBBCC->step)++;
        break;
    case 2:
        fn_2_1800();
        break;
    case 3:
        lbl_8034E9A0._4728 = g_d_GameSettings.GameModeSelected;
        lbl_8034E9A0._4729 = g_d_GameSettings._10;
        g_d_GameSettings.exhibitionMatchInd = 1;
#ifdef TARGET_PC
        if (g_d_GameSettings.GameModeSelected == 5) {
            // Career Mode replaces Challenge (port/game/career.c): set up the next career game and
            // load game.rel straight from here, as Toy Field and the minigames do.
            extern BOOL port_career_setup_next_game(void);
            port_career_setup_next_game();
            fn_80062A74();
            fn_2_1F30_unload();
            fn_80021410();
            fn_800ACFB0(lbl_800EF808.groups[37]);
            fn_2_11A0(4);
            lbl_2_bss_20[0] = 0;
            break;
        }
#endif
        if (g_d_GameSettings.GameModeSelected == 0) {
            fn_2_11A0(9);
        } else if (g_d_GameSettings.GameModeSelected == 5) {
            if (lbl_803C50E8._47 != 0) {
                g_d_GameSettings._10 = 0;
                fn_2_11A0(0xC);
            } else {
                fn_2_11A0(0xF);
            }
        } else {
            fn_80062A74();
            fn_2_1F30_unload();
            fn_80021410();
            fn_800ACFB0(lbl_800EF808.groups[37]);
            fn_2_11A0(4);
        }
        lbl_2_bss_20[0] = 0;
        break;
    case 4:
        lbl_8034E9A0._48AF = 1;
        lbl_8034E9A0._48B1 = 1;
        lbl_803CBBCC->step = 3;
        break;
    case 5:
        if (lbl_803C66B0.active[0] == 0) {
            lbl_8034E9A0._4712 = lbl_2_bss_F410._00;
            lbl_8034E9A0._4713 = lbl_2_bss_F410._04;
            switch (lbl_8034E9A0._4708) {
            case 0:
                fn_80021AC8();
                fn_2_82E58();
                changeScene(3, 6);
                lbl_803CBBCC->step = 3;
                break;
            default:
                lbl_803CBBCC->step = 4;
                break;
            case 6:
                lbl_8034E9A0._48AF = 1;
                lbl_8034E9A0._48B1 = 1;
                changeScene(3, 6);
                lbl_803CBBCC->step = 8;
                break;
            case 5:
                lbl_8034E9A0._48AF = 1;
                lbl_8034E9A0._48B1 = 1;
                changeScene(3, 6);
                lbl_803CBBCC->step = 0xA;
                break;
            case 1:
                lbl_8034E9A0._4756 = 0;
                lbl_8034E9A0._48AF = 1;
                lbl_8034E9A0._48B1 = 1;
                changeScene(3, 6);
                lbl_803CBBCC->step = 3;
                break;
            }
            lbl_8034E9A0._472A = 0;
        }
        break;
    case 6:
        lbl_803CBCE0[0] = 0;
        lbl_8034E9A0._48B4 = 0;
        fn_80062A74();
        fn_2_1F30_unload();
        fn_2_11A0(1);
        lbl_2_bss_20[0] = 0;
        break;
    case 7:
        lbl_8034E9A0._472A = 0;
        fn_2_11A0(1);
        lbl_803CBCE0[0] = 0;
        lbl_8034E9A0._48B4 = 0;
        break;
    case 8:
        fn_2_11A0(6);
        lbl_2_bss_20[0] = 0;
        break;
    case 9:
        fn_80062A74();
        fn_2_1F30_unload();
        fn_80021410();
        fn_800ACFB0(lbl_800EF808.groups[37]);
        fn_2_11A0(7);
        lbl_2_bss_20[0] = 0;
        break;
    case 10:
        fn_2_1F30_unload();
        fn_2_11A0(8);
        lbl_2_bss_20[0] = 0;
        break;
    }
}
#endif

// NONMATCHING 70%: the release sequence is duplicated in the original (once per branch) and
// fn_2_C698 is inlined into each copy.
#if NONMATCHING
static void fn_2_4970_release(u8 team, s32 slot) {
    u8* row = lbl_803C6724 + team * 9;
    s32 g = 0;
    s32 i;
    s32 k;
    s32 dup = 0;
    fn_2_C698(slot, team);
    if (g_d_GameSettings.GameModeSelected != 5) {
        fn_800506E8(team, (s8)row[slot + 2], 0);
        fn_80067B40(team, row[slot + 2], 0);
        lbl_8034E9A0.charFlag[(s8)row[slot + 2]] = 0;
    } else if (fn_80067B40(team, row[slot + 2], 2) != 0) {
        for (i = 0; i < 9; i++) {
            for (k = 0; k < 5; k++) {
                if ((s8)row[slot + 2] == lbl_80108EDC[i][k]) {
                    g = i;
                    goto found;
                }
            }
        }
    found:
        for (i = 0; i < 9; i++) {
            for (k = 0; k < 5; k++) {
                s16 m = lbl_80108EDC[g][k];
                if ((s8)row[i + 2] == m && m != -1 && (s8)row[i + 2] != (s8)row[slot + 2]) {
                    dup = 1;
                }
            }
        }
        if (dup == 0) {
            fn_800506E8(team, (s8)fn_80067AC8((s8)row[slot + 2], 0), 0);
            lbl_8034E9A0.charFlag[fn_80067AC8((s8)row[slot + 2], 0)] = 0;
        }
    } else {
        fn_800506E8(team, (s8)row[slot + 2], 0);
        lbl_8034E9A0.charFlag[(s8)row[slot + 2]] = 0;
    }
    row[slot + 0x26] = 0;
    row[slot + 2] = -1;
}

// fn_2_4970, size:0x814
// nmverify: fn_2_4970_release inlined on one side (calls match once expanded)
void fn_2_4970(u8 team, s32 empty) {
    MenuTeamSel* state = &lbl_2_bss_F468;
    s32 cur = state->cursor[team];
    u8* row = lbl_803C6724 + team * 9;
    s32 slot = 0; // uninitialized in the original if no position matches
    s32 j;
    s8 v;
    for (j = 0; j < 9; j++) {
        if ((s8)row[j + 0x14] == cur) {
            slot = j;
        }
    }
    v = row[slot + 2];
    if (v == empty) {
        if (--state->cursor[team] < 0) {
            state->cursor[team] = 8;
        }
    } else {
        if (lbl_2_bss_F468._37[team] == 0 && lbl_2_bss_F468._3D[team] == 0) {
            state->prevCursor[team] = cur;
            if (--state->cursor[team] < 0) {
                state->cursor[team] = 8;
            }
            if (v != -1 && v != 0x36) {
                fn_2_4970_release(team, slot);
                row[slot + 0x4A] = 0;
            }
        } else {
            fn_2_4970_release(team, slot);
            lbl_2_bss_F468._3D[team] = 0;
            row[slot + 0x4A] = 0;
        }
        lbl_2_bss_F468._37[team] = 0;
    }
    fn_800625A4(team, 0x10);
}
#endif

// NONMATCHING 85%: plain loops; the original unrolls the unique-position check and the
// 54-entry star-rating table.
#if NONMATCHING
// fn_2_7504, size:0x840
void fn_2_7504(void) {
    s32 free = 0;
    u8 unique = 0;
    u8 u;
    s32 t;
    s32 i;
    u32 cap;
    lbl_803CBD24[2] = 0;
    lbl_803CBD24[3] = 0xFF;
    lbl_2_bss_F468._61[1] = -1;
    lbl_2_bss_F468._61[0] = -1;
    lbl_2_bss_F468._65[1] = 0;
    lbl_2_bss_F468._65[0] = 0;
    if (lbl_803CBBCC->prevScene != 9) {
        if (g_d_GameSettings._10 == 0 && g_d_GameSettings.GameModeSelected != 5) {
            lbl_2_bss_100B8._2E[0] = 1;
            lbl_2_bss_100B8._2E[1] = 1;
        } else {
            lbl_2_bss_100B8._2E[1] = 0;
            lbl_2_bss_100B8._2E[0] = 0;
        }
        if (g_d_GameSettings.GameModeSelected == 5) {
            for (t = 0; t < 2; t++) {
                u8* row = lbl_803C6724 + t * 9;
                if (t == 0) {
                    cap = CHALLENGE->_441D;
                    u = 1;
                    for (i = 1; i < 9; i++) {
                        if (CHALLENGE->order[0]._3 == CHALLENGE->order[i]._3) {
                            u = 0;
                        }
                    }
                    unique = u;
                } else {
                    cap = (u8)(s8)CHALLENGE->_441F;
                }
                for (i = 0; i < 9; i++) {
                    s8 id = row[i + 2];
                    if (t == 0 && lbl_803297E0._CFA1 == 0) {
                        row[i + 0x14] = CHALLENGE->order[i]._3;
                    } else if (t == 0 && unique != 0) {
                        row[i + 0x14] = CHALLENGE->order[i]._3;
                    } else {
                        row[i + 0x14] = i;
                    }
                    row[i + 0x26] = CS_STATS(id)->chem[cap];
                }
            }
            for (i = 0; i < 0x36; i++) {
                CharacterStats* c = CS_STATS(i);
                lbl_2_bss_3A8[i] = c->stats.BattingStance + c->stats.FieldingArm * 2;
            }
            if (lbl_803CBBCC->prevScene != 0xB && lbl_803297E0._CFA1 == 0) {
                for (i = 0; i < 9; i++) {
                    lbl_2_bss_3A8[CHALLENGE->order[i].charId] =
                        CHALLENGE->order[i]._4;
                }
            }
        }
    } else {
        for (t = 0; t < 2; t++) {
            u8* row = lbl_803C6724 + t * 9;
            for (i = 0; i < 9; i++) {
                row[i + 0x14] = i;
                row[i + 0x4A] = 0;
                row[i + 0x26] = 0;
                if (i != 0) {
                    row[i + 2] = -1;
                }
            }
        }
    }
    if (g_d_GameSettings.GameModeSelected == 5) {
        for (t = 0; t < 2; t++) {
            fn_800678CC(t);
        }
    }
    lbl_8034E9A0._4702 = 1;
    if (g_d_GameSettings.GameModeSelected == 5) {
        for (i = 0; i < 0x36; i++) {
            if (lbl_8034E9A0.charFlag[i] == 0) {
                free++;
            }
        }
        if (free == 0) {
            lbl_2_bss_F468._3F = 1;
            lbl_2_bss_F468._37[0] = 1;
            lbl_2_bss_F468.cursor[0] = 9;
            return;
        }
        lbl_2_bss_F468._3F = 0;
    }
}
#endif

// NONMATCHING 80%: same copies; loop pointer registers and some load scheduling differ.
#if NONMATCHING
#define FN_2_8CF8_SAVE(t, i)                                                      \
    do {                                                                          \
        CharacterStats* src = &g_Roster[(t) * 9 + (i)];                            \
        CharacterStats* dst = &((CharacterStats*)lbl_2_bss_E8CC)[(t) * 9 + (i)];    \
        MenuOrderEntry* order = &lbl_80354720[(t)][(i)];                          \
        MenuOrderEntry* saved = &((MenuOrderEntry(*)[9])lbl_2_bss_DCE8)[(t)][(i)];                        \
        MENU_COPY_CHAR_STATS(dst, src);                                           \
        saved->_0 = order->_0;                                                      \
        saved->_1 = order->_1;                                                      \
        saved->slot = order->slot;                                                      \
        saved->_3 = order->_3;                                                      \
        lbl_2_bss_3E4[(t) * 9 + (i)] = src->stats.CharID;                                  \
    } while (0)

#define FN_2_8CF8_LOAD(t, i)                                                      \
    do {                                                                          \
        CharacterStats* dst = &g_Roster[(t) * 9 + (i)];                            \
        CharacterStats* src = &((CharacterStats*)lbl_2_bss_E8CC)[(t) * 9 + (i)];    \
        MenuOrderEntry* order = &lbl_80354720[(t)][(i)];                          \
        MenuOrderEntry* saved = &((MenuOrderEntry(*)[9])lbl_2_bss_DCE8)[(t)][(i)];                        \
        MENU_COPY_CHAR_STATS(dst, src);                                           \
        order->_0 = saved->_0;                                                      \
        order->_1 = saved->_1;                                                      \
        order->slot = saved->slot;                                                      \
        order->_3 = saved->_3;                                                      \
        dst->stats.CharID = lbl_2_bss_3E4[(t) * 9 + (i)];                                  \
    } while (0)

// fn_2_8CF8, size:0x8E0
void fn_2_8CF8(u16 team) {
    s32 t;
    s32 i;
    if (lbl_2_bss_100B8._30[team] != 0) {
        if (g_d_GameSettings._10 != 1) {
            for (t = 0; t < 2; t++) {
                for (i = 0; i < 9; i++) {
                    FN_2_8CF8_SAVE(t, i);
                }
            }
        } else {
            for (i = 0; i < 9; i++) {
                FN_2_8CF8_SAVE(team, i);
            }
        }
        fn_2_9ACC(team);
        return;
    }
    if (g_d_GameSettings._10 != 1) {
        for (t = 0; t < 2; t++) {
            for (i = 0; i < 9; i++) {
                FN_2_8CF8_LOAD(t, i);
            }
        }
        return;
    }
    for (i = 0; i < 9; i++) {
        FN_2_8CF8_LOAD(team, i);
    }
}
#endif

// NONMATCHING 70%: plain loops; fn_2_348C inlines into the non-challenge branch as in the original.
#if NONMATCHING
// fn_2_7DDC, size:0x910
void fn_2_7DDC(void) {
    u8 buf[4];
    s32 i;
    s32 t;
    s32 g;
    s32 k;
    s32* sel;
    if (g_d_GameSettings.GameModeSelected != 5) {
        memset(lbl_8034E9A0.charFlag, 0, sizeof(lbl_8034E9A0.charFlag));
    }
    lbl_8034E9A0._48AD = 0;
    lbl_803C66B0.steps[0][0] = 2;
    memset(buf, 0xFF, 4);
    if (lbl_803CBBCC->prevScene == 9) {
        lbl_803C66B0.portOf[0] = 0;
        lbl_803C66B0.portOf[1] = 1;
    } else {
        if (g_d_GameSettings._10 == 0 && g_d_GameSettings.GameModeSelected != 5) {
            lbl_803C66B0.portOf[0] = 1;
        } else {
            lbl_803C66B0.portOf[0] = 0;
        }
        lbl_803C66B0.portOf[1] = 1;
    }
    memset(buf, 0, 4);
    if (g_d_GameSettings._10 == 0) {
        buf[*(s8*)&lbl_8034E9A0.ports[0]] = 1;
        if (*(s8*)&lbl_8034E9A0.ports[0] == 0) {
            buf[1] = 2;
        } else {
            buf[0] = 2;
        }
    } else {
        buf[*(s8*)&lbl_8034E9A0.ports[1]] = 1;
        buf[*(s8*)&lbl_8034E9A0.ports[0]] = 1;
    }
    if (g_d_GameSettings.GameModeSelected != 5) {
        fn_80050FE8(buf[0], buf[1], buf[2], buf[3], 0, 1);
    } else {
        fn_80050FE8(buf[0], buf[1], buf[2], buf[3], 0, 0);
    }
    fn_2_7265C();
    lbl_8034E9A0._472A = 0xFF;
    if (lbl_803CBBCC->prevScene != 0xB && g_d_GameSettings.GameModeSelected != 5) {
        lbl_2_bss_F468.cursor[0] = 0xA;
        lbl_2_bss_F468.cursor[1] = 0xA;
    } else {
        lbl_2_bss_F468.cursor[0] = 9;
        lbl_2_bss_F468.cursor[1] = 9;
    }
    if (g_d_GameSettings.GameModeSelected == 5) {
        for (i = 0; i < 0x36; i++) {
            if (CHALLENGE->chars[i]._31 == 1) {
                lbl_8034E9A0.charFlag[i] = 0;
                fn_800506E8(0, i, 0);
            } else {
                s16 alt;
                lbl_8034E9A0.charFlag[i] = 1;
                alt = fn_80067AC8(i, 0);
                if (alt != -1 && CHALLENGE->chars[alt]._31 == 1) {
                    fn_800506E8(0, i, 0);
                } else {
                    fn_800506E8(0, i, 1);
                }
            }
        }
        for (i = 0; i < 9; i++) {
            s8 id = lbl_803C6724[i + 2];
            lbl_8034E9A0.charFlag[id] = 1;
            fn_800506E8(0, id, 1);
            if (fn_80067B40(0, lbl_803C6724[i + 2], 2) != 0) {
                for (g = 0; g < 9; g++) {
                    for (k = 0; k < 5; k++) {
                        if ((s8)lbl_803C6724[i + 2] == lbl_80108EDC[g][k]) {
                            s16* grp = lbl_80108EDC[g];
                            s32 m;
                            for (m = 0; m < 5; m++) {
                                if (grp[m] == -1) {
                                    goto next;
                                }
                                lbl_8034E9A0.charFlag[grp[m]] = 1;
                            }
                        }
                    }
                }
            }
        next:;
        }
        lbl_2_bss_F468._37[0] = 1;
    } else {
        fn_2_348C();
        for (t = 0; t < 2; t++) {
            for (i = 0; i < 9; i++) {
                s8 id = lbl_803C6724[t * 9 + i + 2];
                if (id == -1) {
                    continue;
                }
                lbl_8034E9A0.charFlag[id] = 1;
                if (g_d_GameSettings._10 == 0 && t != 0) {
                    if (*(s8*)&lbl_8034E9A0.ports[0] == 0) {
                        fn_800506E8(1, id, 1);
                    } else {
                        fn_800506E8(0, id, 1);
                    }
                } else {
                    fn_800506E8(*(s8*)&lbl_8034E9A0.ports[t], (s8)lbl_803C6724[t * 9 + i + 2], 1);
                }
                fn_80067B40(t, lbl_803C6724[t * 9 + i + 2], 1);
            }
        }
    }
    for (t = 0; t < 2; t++) {
        sel = &lbl_2_bss_F410.charSel[t + 4];
        if (g_d_GameSettings._10 == 0 && t != 0) {
            lbl_803C6028[0x74 + *(s8*)&lbl_8034E9A0.ports[t]] = 1;
        } else {
            lbl_803C6028[0x74 + *(s8*)&lbl_8034E9A0.ports[t]] = 0;
        }
        if (t != 0) {
            *sel = 9;
        } else {
            *sel = 0;
        }
        if (lbl_8034E9A0.charFlag[*sel] != 0) {
            for (i = 0; i < 32; i++) {
                u8 c = lbl_800FDE84[i];
                if (lbl_8034E9A0.charFlag[c] == 0 && c != 0xFF) {
                    *sel = lbl_800FDE84[i];
                    break;
                }
            }
        }
        switch (*(s8*)&lbl_8034E9A0.ports[t]) {
        case 0:
            fn_80050138(1, *sel, -1, -1, -1, 0);
            break;
        case 1:
            fn_80050138(1, -1, *sel, -1, -1, 0);
            break;
        case 2:
            fn_80050138(1, -1, -1, *sel, -1, 0);
            break;
        case 3:
            fn_80050138(1, -1, -1, -1, *sel, 0);
            break;
        }
    }
    if (lbl_803CBBCC->prevScene == 9) {
        fn_800625A4(0, 0xA);
        fn_800625A4(1, 0xA);
    } else if (lbl_803CBBCC->prevScene != 0xB && g_d_GameSettings.GameModeSelected == 5) {
        fn_800625A4(0, 0xA);
        fn_800625A4(1, 0xA);
    } else {
        fn_800625A4(0, 9);
        fn_800625A4(1, 9);
    }
    lbl_803C66B0.steps[0][0] = 2;
}
#endif

// NONMATCHING 70%: plain C; the original inlines fn_2_5184/fn_2_C698 and unrolls the counting loops.
#if NONMATCHING
// fn_2_DFAC, size:0xB34
void fn_2_DFAC(u8 team) {
    MenuTeamSel* state = &lbl_2_bss_F468;
    s32* sel = &lbl_2_bss_F410.charSel[4];
    s32 cur = state->cursor[team];
    s32 cap = lbl_8034E9A0.captain[team];
    u8* row = lbl_803C6724 + team * 9;
    s32 slot = 0;
    s32 locked;
    s32 n = 0;
    s32 free = 0;
    s32 g = -1;
    s32 i;
    s32 k;
    s32 id;
    s8 p;
    if (lbl_803C66B0.step[0] == 0xB) {
        return;
    }
    for (i = 0; i < 9; i++) {
        if ((s8)cur == (s8)row[i + 0x14]) {
            slot = i;
            break;
        }
    }
    locked = g_d_GameSettings.GameModeSelected == 5 && lbl_2_bss_F468._3F != 0;
    if (lbl_2_bss_F468._41[team] == 0) {
        if (state->cursor[team] == 9) {
            fn_2_5444(team);
            ((void (*)(u32))fn_2_1C34)(0x100);
            return;
        }
        if (state->cursor[team] == 10) {
            if (locked) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                return;
            }
            fn_2_5184(team);
            ((void (*)(u32))fn_2_1C34)(0x100);
            return;
        }
        if ((s8)row[slot + 2] == lbl_8034E9A0.captain[team]) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
        if (locked) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
        lbl_2_bss_F468._41[team] = 1;
        fn_800625A4(team, 0xD);
        ((void (*)(u32))fn_2_1C34)(0x100);
        return;
    }
    id = sel[team];
    if (lbl_8034E9A0.charFlag[id] != 0 || id == -1) {
        sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
        return;
    }
    if (locked) {
        return;
    }
    if (g_d_GameSettings._10 == 1 && id != -1) {
        u8 other = team ^ 1;
        if (id == sel[other] && lbl_2_bss_F468._41[other] != 0) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
    }
    p = row[slot + 2];
    if (g_d_GameSettings.GameModeSelected != 5) {
        if (p != -1 && p != 0x36) {
            fn_800506E8(team, p, 0);
            lbl_8034E9A0.charFlag[(s8)row[slot + 2]] = 0;
            fn_80067B40(team, row[slot + 2], 0);
        }
    } else {
        for (i = 0; i < 9; i++) {
            s8 v = row[i + 2];
            if (v != -1 && v != 0x36 && v != cap) {
                n++;
            }
        }
        for (i = 0; i < 0x36; i++) {
            if (lbl_8034E9A0.charFlag[i] == 0) {
                free++;
            }
        }
        if (free <= 8 - n && p != -1 && p != 0x36) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
        if (p != -1 && p != 0x36) {
            if (fn_80067B40(team, row[slot + 2], 2) != 0) {
                for (i = 0; i < 9 && g == -1; i++) {
                    for (k = 0; k < 5; k++) {
                        if ((s8)row[slot + 2] == lbl_80108EDC[i][k]) {
                            g = i;
                            break;
                        }
                    }
                }
                if (g != -1) {
                    for (i = 0; i < 9; i++) {
                        for (k = 0; k < 5; k++) {
                            s16 m = lbl_80108EDC[g][k];
                            if ((s8)row[i + 2] == m && i != slot && m != -1) {
                                goto assign;
                            }
                        }
                    }
                    fn_800506E8(team, (s8)fn_80067AC8((s8)row[slot + 2], 0), 0);
                    lbl_8034E9A0.charFlag[fn_80067AC8((s8)row[slot + 2], 0)] = 0;
                }
            } else {
                fn_800506E8(team, (s8)row[slot + 2], 0);
                lbl_8034E9A0.charFlag[(s8)row[slot + 2]] = 0;
            }
        }
    }
assign:
    row[slot + 2] = sel[team];
    row[slot + 0x4A] = 1;
    fn_800628D4((s8)row[slot + 2]);
    fn_800678CC(team);
    fn_2_C698(slot, team);
    lbl_803C5EA4._0C[team] = slot;
    lbl_803C5EA4._0A[team] = 1;
    row[slot + 0x26] = CS_STATS(sel[team])->chem[cap];
    fn_800625A4(team, 0xF);
    if (lbl_2_bss_F468._37[team] != 0) {
        lbl_2_bss_F468._41[team] = 0;
    }
}
#endif

// NONMATCHING 70%: plain C; the original inlines fn_2_35D0, fn_2_A040 and fn_2_C698 and
// unrolls the slot searches.
#if NONMATCHING
// fn_2_104FC, size:0xBB4
void fn_2_104FC(u16 port) {
    u8 team = lbl_803C66B0.portOf[port];
    MenuTeamSel* state = &lbl_2_bss_F468;
    s32* sel = &lbl_2_bss_F410.charSel[4];
    u8* row = lbl_803C6724 + team * 9;
    u16 held;
    u16 down;
    u16 repeat;
    s32 slot = 0;
    s32 n = 0;
    s32 i;
    s32 g;
    s32 k;
    s8 owner;
    if (lbl_803C66B0.step[team] != 0) {
        down = 0;
        repeat = 0;
        held = 0;
    } else if (g_d_GameSettings._10 == 1 && lbl_2_bss_100B8._2E[team] != 0) {
        held = lbl_8034E9A0.input[port].held & 0x200;
        down = lbl_8034E9A0.input[port].pressed & 0x200;
        repeat = lbl_8034E9A0.input[port].repeat & 0x200;
    } else if (lbl_2_bss_F468._52[team] != 0) {
        down = 0;
        repeat = 0;
        held = 0;
    } else {
        held = lbl_8034E9A0.input[port].held;
        down = lbl_8034E9A0.input[port].pressed;
        repeat = lbl_8034E9A0.input[port].repeat;
    }
    if (down & 0x1000) {
        return;
    }
    if (down & 0x40) {
        if (fn_2_35D0(team)) {
            return;
        }
        if (lbl_2_bss_F468._41[team] != 0) {
            if (g_d_GameSettings.GameModeSelected != 5 && lbl_8034E9A0.charFlag[sel[team]] == 0) {
                owner = *(s8*)&lbl_8034E9A0.ports[team];
                if (lbl_8034E9A0._46FC[owner] != 0) {
                    owner = *(s8*)&lbl_8034E9A0.ports[0] == 0;
                }
                sel[team] = fn_80050760(owner, held, down, repeat, 0);
            }
        } else if (g_d_GameSettings.GameModeSelected != 5) {
            s8 v;
            for (i = 0; i < 9; i++) {
                if ((s8)row[i + 0x14] == state->cursor[team]) {
                    slot = i;
                    break;
                }
            }
            v = row[slot + 2];
            if (v == -1 || v == 0x36) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                return;
            }
            if (state->cursor[team] == 9 || state->cursor[team] == 10) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                return;
            }
            lbl_2_bss_F468._50[team] = 0;
            for (g = 0; g < 9; g++) {
                for (k = 0; k < 5; k++) {
                    if (v == lbl_80108EDC[g][k]) {
                        lbl_2_bss_F468._50[team] = 1;
                        goto found;
                    }
                }
            }
        found:
            if (lbl_2_bss_F468._50[team] != 0) {
                fn_2_A040(g, k, team, slot);
                fn_2_C698(slot, team);
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    } else if (down & 0x800) {
        if (fn_2_35D0(team)) {
            return;
        }
        for (i = 0; i < 9; i++) {
            s8 v = row[i + 2];
            if (v != -1 && v != 0x36) {
                n++;
            }
        }
        if (n != 1 && g_d_GameSettings.GameModeSelected != 5) {
            for (i = 1; i < 9; i++) {
                s8 v = row[i + 2];
                if (v != -1 && v != 0x36) {
                    lbl_8034E9A0.charFlag[v] = 0;
                    fn_800506E8(*(s8*)&lbl_8034E9A0.ports[team], v, 0);
                    fn_80067B40(team, row[i + 2], 0);
                    row[i + 2] = -1;
                    row[i + 0x4A] = 0;
                    row[i + 0x26] = 0;
                }
            }
            lbl_2_bss_F468._37[team] = 0;
            lbl_2_bss_F468._41[team] = 0;
            lbl_2_bss_F468._50[team] = 0;
            state->prevCursor[team] = state->cursor[team];
            state->cursor[team] = 0xA;
            lbl_2_bss_F468._3D[team] = 0;
            lbl_2_bss_F468._52[team] = 1;
        }
    } else if (down & 0x10) {
        if (fn_2_35D0(team)) {
            return;
        }
        for (i = 0; i < 9; i++) {
            if ((s8)row[i + 0x14] == state->cursor[team]) {
                slot = i;
                break;
            }
        }
        if (state->cursor[team] != 0xA && state->cursor[team] != 9) {
            s8 v = row[slot + 2];
            if (v != -1 && v != 0x36 && lbl_2_bss_F468._41[team] == 0) {
                lbl_2_bss_F468._45[team] = 1;
                lbl_2_bss_F468._4B[team] = 1;
                lbl_2_bss_F468._47[team] = 0;
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                return;
            }
        }
        if (lbl_2_bss_F468._41[team] != 0) {
            if (lbl_8034E9A0.charFlag[sel[team]] == 0 && sel[team] != -1) {
                lbl_2_bss_F468._45[team] = 1;
                lbl_2_bss_F468._4B[team] = 1;
                lbl_2_bss_F468._47[team] = 0;
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
            }
        }
    } else if (down & 0x20) {
        if (fn_2_35D0(team)) {
            return;
        }
        if (lbl_2_bss_F468._59[team] == 0) {
            lbl_2_bss_F468._59[team] = 1;
            lbl_2_bss_F468._61[team] = -1;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            if (lbl_2_bss_F468._41[team] != 0) {
                lbl_2_bss_F468._41[team] = 0;
                fn_800625A4(team, 0xD);
                return;
            }
            if (state->cursor[team] == 0xA) {
                lbl_2_bss_F468._63[team] = 1;
                state->prevCursor[team] = state->cursor[team];
                state->cursor[team] = 1;
                fn_800625A4(team, 0xE);
                return;
            }
            fn_800625A4(team, 0x1A);
        }
    } else {
        fn_2_ED94(team, held, down, repeat);
    }
}
#endif

// NONMATCHING 85%: register allocation differs throughout and the original walks the roster
// with pointers where ours indexes it; fn_2_EC54/fn_2_C698 inline as in the original.
#if NONMATCHING
static void fn_2_CE44_clear_ratings(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 9; j++) {
            lbl_803C6724[i * 9 + 0x26 + j] = 0;
        }
    }
}

static void fn_2_CE44_reset_both(void) {
    lbl_2_bss_100B8._2E[1] = 0;
    lbl_2_bss_100B8._2E[0] = 0;
    lbl_803C5EA4._0E = 0;
    lbl_803C66B0.portOf[1] = 0;
    lbl_803C66B0.portOf[0] = 0;
    lbl_2_bss_F468.cursor[1] = 9;
    lbl_2_bss_F468.cursor[0] = 9;
    fn_800625A4(0, 0x12);
}

// fn_2_CE44, size:0x1168
void fn_2_CE44(u8 team) {
    MenuTeamSel* state = &lbl_2_bss_F468;
    s32 cap;
    u8* row;
    s32 n = 0;
    s8 free = 0;
    s32 slot = 0; // uninitialized in the original if no position matches
    s32 st;
    s32 i;
    s32 t;
    if ((g_d_GameSettings.GameModeSelected == 5 && lbl_2_bss_F468._3F != 0) ? 1 : 0) {
        sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
        return;
    }
    if (lbl_2_bss_F468._41[team] != 0) {
        lbl_2_bss_F468._41[team] = 0;
        fn_800625A4(team, 0xD);
        goto end;
    }
    cap = lbl_8034E9A0.captain[team];
    row = lbl_803C6724 + team * 9;
    for (i = 0; i < 9; i++) {
        s8 v = row[i + 2];
        if (v != -1 && v != 0x36 && v != cap) {
            n++;
        }
    }
    if (g_d_GameSettings.GameModeSelected == 5) {
        for (i = 0; i < 0x36; i++) {
            if (lbl_8034E9A0.charFlag[i] == 0) {
                free++;
            }
        }
        if (free <= 8 - n) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
    }
    state->prevCursor[team] = state->cursor[team];
    if (n == 0) {
        lbl_2_bss_F468._37[team] = 0;
        if (state->cursor[team] == 9) {
            state->cursor[team] = 0;
            switch (team) {
            case 0:
                if ((s8)lbl_803C6724[2] == lbl_8034E9A0.captain[0]) {
                    state->cursor[0] = 1;
                }
                break;
            case 1:
                if ((s8)lbl_803C6724[0xB] == lbl_8034E9A0.captain[1]) {
                    state->cursor[1] = 1;
                }
                break;
            }
        }
    }
    if (g_d_GameSettings._10 == 0) {
        st = state->cursor[team];
        if (st != 9 && st != 10 && n != 0) {
            fn_2_4970(team, cap);
            goto end;
        }
        if (st == 9) {
            state->prevCursor[team] = state->cursor[team];
            state->cursor[team]--;
            if (cap == (s8)row[8 + 2]) {
                state->cursor[team]--;
            }
            fn_800625A4(team, 0x15);
            goto end;
        }
        if (st == 10) {
            if (n == 0 && lbl_803C5EA4._0E != 0) {
                fn_2_CE44_reset_both();
                goto end;
            }
            if (n == 0 && lbl_803C5EA4._0E == 0) {
                if (lbl_803C66B0.active[0] == 0 && lbl_803C66B0.active[1] == 0) {
                    fn_2_CE44_clear_ratings();
                    fn_2_EC54(team);
                    goto end;
                }
                return;
            }
            state->prevCursor[team] = state->cursor[team];
            state->cursor[team] = 8;
            if (cap == (s8)row[8 + 2]) {
                state->cursor[team]--;
            }
            fn_800625A4(team, 0x15);
            goto end;
        }
        if (lbl_2_bss_F468._37[0] != 0 && n == 0) {
            fn_2_CE44_reset_both();
            goto end;
        }
        if (n == 0) {
            if (lbl_803C66B0.active[0] == 0 && lbl_803C66B0.active[1] == 0) {
                fn_2_CE44_clear_ratings();
                fn_2_EC54(team);
                goto end;
            }
            return;
        }
        goto end;
    }
    if (g_d_GameSettings._10 != 1) {
        goto end;
    }
    st = state->cursor[team];
    if (st != 9 && st != 10) {
        if (n == 0) {
            if (lbl_803C66B0.active[0] == 0 && lbl_803C66B0.active[1] == 0) {
                lbl_2_bss_F468._45[1] = 0;
                lbl_2_bss_F468._45[0] = 0;
                state->cursor[1] = 0;
                state->cursor[0] = 0;
                lbl_2_bss_F468._5F[1] = 0;
                lbl_2_bss_F468._5F[0] = 0;
                fn_2_EC54(team);
            }
            return;
        }
        for (i = 0; i < 9; i++) {
            if ((s8)row[i + 0x14] == st) {
                slot = i;
            }
        }
        state->cursor[team] = st;
        if ((s8)row[slot + 2] == cap) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
        state->prevCursor[team] = state->cursor[team];
        if (--state->cursor[team] < 0) {
            state->cursor[team] = 8;
        }
        if ((s8)row[state->cursor[team] + 2] == cap) {
            if (--state->cursor[team] < 0) {
                state->cursor[team] = 8;
            }
        }
        st = state->prevCursor[team];
        for (i = 0; i < 9; i++) {
            if ((s8)row[i + 0x14] == st) {
                slot = i;
            }
        }
        if ((s8)row[slot + 2] != -1) {
            s32 old;
            fn_2_C698(slot, team);
            fn_800506E8(team, (s8)row[slot + 2], 0);
            fn_80067B40(team, row[slot + 2], 0);
            old = (s8)row[slot + 2]; // the removed character, read before the slot is cleared
            row[slot + 0x26] = 0;
            row[slot + 2] = -1;
            lbl_2_bss_F468._3D[0] = 0;
            lbl_8034E9A0.charFlag[old] = 0;
            row[slot + 0x4A] = 0;
            lbl_2_bss_F468._37[team] = 0;
        }
        fn_800625A4(team, 0x10);
        goto end;
    }
    if (st == 9 || st == 10) {
        if (lbl_2_bss_100B8._2E[team] != 0) {
            lbl_2_bss_100B8._2E[team] = 0;
            fn_800625A4(team, 0x12);
            ((void (*)(u32))fn_2_1C34)(0x200);
            return;
        }
        if (n != 0) {
            state->prevCursor[team] = state->cursor[team];
            state->cursor[team] = 8;
            if (cap == (s8)row[8 + 2]) {
                state->cursor[team]--;
            }
            fn_800625A4(team, 0x15);
            ((void (*)(u32))fn_2_1C34)(0x200);
            return;
        }
        if (lbl_803C66B0.active[0] != 0 || lbl_803C66B0.active[1] != 0) {
            return;
        }
        fn_2_CE44_clear_ratings();
        lbl_2_bss_F468._45[1] = 0;
        lbl_2_bss_F468._45[0] = 0;
        state->cursor[1] = 0;
        state->cursor[0] = 0;
        lbl_2_bss_F468._5F[1] = 0;
        lbl_2_bss_F468._5F[0] = 0;
        for (t = 0; t < 2; t++) {
            u8* r = lbl_803C6724 + t * 9;
            for (i = 1; i < 9; i++) {
                s8 id = r[i + 2];
                lbl_8034E9A0.charFlag[id] = 0;
                fn_800506E8(*(s8*)&lbl_8034E9A0.ports[t], id, 0);
                fn_80067B40(t, r[i + 2], 0);
                r[i + 2] = -1;
                r[i + 0x4A] = 0;
                r[i + 0x26] = 0;
            }
            lbl_2_bss_F468._37[t] = 0;
            if (state->cursor[t] == 9) {
                state->cursor[t] = 0;
                switch (t) {
                case 0:
                    if ((s8)lbl_803C6724[2] == lbl_8034E9A0.captain[0]) {
                        state->cursor[0] = 1;
                    }
                    break;
                case 1:
                    if ((s8)lbl_803C6724[0xB] == lbl_8034E9A0.captain[1]) {
                        state->cursor[1] = 0xB;
                    }
                    break;
                }
            }
            lbl_2_bss_F468._3D[t] = 0;
        }
        fn_2_EC54(team);
    }
end:
    ((void (*)(u32))fn_2_1C34)(0x200);
}
#endif

// NONMATCHING 88%: register allocation and scheduling; the inlined fn_2_35D0/fn_2_52CC/
// fn_2_A040/fn_2_C698 bodies and the per-branch cursor sounds are laid out as in the original.
#if NONMATCHING
// Per-team views used by fn_2_3624 (written out at every use like the original, which
// recomputes each address instead of keeping a team base pointer).
#define TEAM_ROW(off) (lbl_803C6724[team * 9 + (off)])

#define FN_2_3624_FIND_SLOT(row, value, out)              \
    do {                                                  \
        s32 j_;                                           \
        s8 want_ = (value);                               \
        for (j_ = 0; j_ < 9; j_++) {                      \
            if ((s8)(row)[j_ + 0x14] == want_) {          \
                (out) = j_;                               \
                break;                                    \
            }                                             \
        }                                                 \
    } while (0)

// fn_2_3624, size:0x134C
// nmverify:  inlined on one side (calls match once expanded)
void fn_2_3624(u8 port) {
    u8 team = lbl_803C66B0.portOf[port];
    u16 btn[3];
    u16 repeat;
    u16 down;
    s8 slot = 0;
    s32 i;
    s32 g;
    s32 k;
    memset(btn, 0, 6);
    if (lbl_803C66B0.step[team] != 0) {
        return;
    }
    btn[0] = lbl_8034E9A0.input[port].held;
    btn[1] = down = lbl_8034E9A0.input[port].pressed;
    btn[2] = repeat = lbl_8034E9A0.input[port].repeat;
    if (repeat & 8) {
        if (lbl_2_bss_F468._45[team] != 0) {
            return;
        }
        if (lbl_2_bss_F468.cursor[team] == 9) {
            lbl_2_bss_F468.cursor[team] = 2;
            fn_800625A4(team, 0xE);
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (lbl_2_bss_F468.cursor[team] == 10) {
            if (lbl_2_bss_F468._37[team] != 0) {
                lbl_2_bss_F468.cursor[team] = 9;
                fn_800625A4(team, 0x18);
            } else {
                lbl_2_bss_F468.cursor[team] = 2;
                fn_800625A4(team, 0xE);
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else {
            lbl_2_bss_F468.prevCursor[team] = lbl_2_bss_F468.cursor[team];
            switch (lbl_2_bss_F468.cursor[team]) {
            case 0: lbl_2_bss_F468.cursor[team] = 5; break;
            case 1: lbl_2_bss_F468.cursor[team] = 0; break;
            case 2: lbl_2_bss_F468.cursor[team] = 8; break;
            case 3: lbl_2_bss_F468.cursor[team] = 7; break;
            case 4: lbl_2_bss_F468.cursor[team] = 6; break;
            case 5: lbl_2_bss_F468.cursor[team] = 7; break;
            case 6: lbl_2_bss_F468.cursor[team] = 4; break;
            case 7: lbl_2_bss_F468.cursor[team] = 1; break;
            case 8:
                if (lbl_2_bss_F468._37[team] != 0 && lbl_2_bss_F468._5F[team] == 0) {
                    lbl_2_bss_F468.cursor[team] = 9;
                } else {
                    lbl_2_bss_F468.cursor[team] = 2;
                }
                break;
            }
            if (lbl_2_bss_F468.prevCursor[team] != lbl_2_bss_F468.cursor[team]) {
                fn_800625A4(team, 0xE);
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if (repeat & 4) {
        if (lbl_2_bss_F468._45[team] != 0) {
            return;
        }
        if (lbl_2_bss_F468.cursor[team] == 9) {
            lbl_2_bss_F468.cursor[team] = 8;
            fn_800625A4(team, 0xE);
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else {
            lbl_2_bss_F468.prevCursor[team] = lbl_2_bss_F468.cursor[team];
            switch (lbl_2_bss_F468.cursor[team]) {
            case 0: lbl_2_bss_F468.cursor[team] = 1; break;
            case 1: lbl_2_bss_F468.cursor[team] = 7; break;
            case 2:
                if (lbl_2_bss_F468._37[team] != 0 && lbl_2_bss_F468._5F[team] == 0) {
                    lbl_2_bss_F468.cursor[team] = 9;
                } else {
                    lbl_2_bss_F468.cursor[team] = 8;
                }
                break;
            case 3: lbl_2_bss_F468.cursor[team] = 0; break;
            case 4: lbl_2_bss_F468.cursor[team] = 6; break;
            case 5: lbl_2_bss_F468.cursor[team] = 0; break;
            case 6: lbl_2_bss_F468.cursor[team] = 4; break;
            case 7: lbl_2_bss_F468.cursor[team] = 5; break;
            case 8: lbl_2_bss_F468.cursor[team] = 2; break;
            }
            if (lbl_2_bss_F468.prevCursor[team] != lbl_2_bss_F468.cursor[team]) {
                fn_800625A4(team, 0xE);
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if (repeat & 1) {
        if (lbl_2_bss_F468._45[team] != 0) {
            if (lbl_2_bss_F468._47[team] == 1) {
                lbl_2_bss_F468._47[team] = 0;
                lbl_2_bss_F468._49[team] = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            return;
        }
        if (lbl_2_bss_F468.cursor[team] == 9) {
            lbl_2_bss_F468.cursor[team] = 0;
            fn_800625A4(team, 0xE);
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else {
            lbl_2_bss_F468.prevCursor[team] = lbl_2_bss_F468.cursor[team];
            switch (lbl_2_bss_F468.cursor[team]) {
            case 0: lbl_2_bss_F468.cursor[team] = 4; break;
            case 1:
                if (lbl_2_bss_F468._37[team] != 0 && lbl_2_bss_F468._5F[team] == 0) {
                    lbl_2_bss_F468.cursor[team] = 9;
                    break;
                }
                return;
            case 2: lbl_2_bss_F468.cursor[team] = 3; break;
            case 3: lbl_2_bss_F468.cursor[team] = 5; break;
            case 4: lbl_2_bss_F468.cursor[team] = 2; break;
            case 5: lbl_2_bss_F468.cursor[team] = 4; break;
            case 6: lbl_2_bss_F468.cursor[team] = 8; break;
            case 7: lbl_2_bss_F468.cursor[team] = 6; break;
            case 8: lbl_2_bss_F468.cursor[team] = 7; break;
            case 10: lbl_2_bss_F468.cursor[team] = 1; break;
            }
            if (lbl_2_bss_F468.prevCursor[team] != lbl_2_bss_F468.cursor[team]) {
                fn_800625A4(team, 0xE);
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if (repeat & 2) {
        if (lbl_2_bss_F468._45[team] != 0) {
            if (lbl_2_bss_F468._47[team] == 0) {
                lbl_2_bss_F468._47[team] = 1;
                lbl_2_bss_F468._49[team] = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            return;
        }
        if (lbl_2_bss_F468.cursor[team] == 9) {
            lbl_2_bss_F468.cursor[team] = 0;
            fn_800625A4(team, 0xE);
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else {
            lbl_2_bss_F468.prevCursor[team] = lbl_2_bss_F468.cursor[team];
            switch (lbl_2_bss_F468.cursor[team]) {
            case 0:
                if (lbl_2_bss_F468._37[team] != 0 && lbl_2_bss_F468._5F[team] == 0) {
                    lbl_2_bss_F468.cursor[team] = 9;
                    fn_800625A4(team, 0x18);
                } else {
                    lbl_2_bss_F468.cursor[team] = 2;
                    fn_800625A4(team, 0xE);
                }
                break;
            case 1:
                if (lbl_2_bss_F468._37[team] != 0 && lbl_2_bss_F468._5F[team] == 0) {
                    lbl_2_bss_F468.cursor[team] = 9;
                    break;
                }
                return;
            case 2: lbl_2_bss_F468.cursor[team] = 4; break;
            case 3: lbl_2_bss_F468.cursor[team] = 2; break;
            case 4: lbl_2_bss_F468.cursor[team] = 5; break;
            case 5: lbl_2_bss_F468.cursor[team] = 3; break;
            case 6: lbl_2_bss_F468.cursor[team] = 7; break;
            case 7: lbl_2_bss_F468.cursor[team] = 8; break;
            case 8: lbl_2_bss_F468.cursor[team] = 6; break;
            }
            if (lbl_2_bss_F468.prevCursor[team] != lbl_2_bss_F468.cursor[team]) {
                fn_800625A4(team, 0xE);
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if (down & 0x100) {
        if (fn_2_35D0(team)) {
            return;
        }
        if (lbl_2_bss_F468.cursor[team] == 9) {
            lbl_2_bss_F468._59[team] = 0;
            lbl_2_bss_F468._61[team] = -1;
            lbl_2_bss_F468._65[team] = 1;
            if (g_d_GameSettings.GameModeSelected == 5) {
                for (i = 0; i < 9; i++) {
                    s16 id = (s8)lbl_803C6724[i + 2];
                    u8 pos = lbl_803C6724[i + 0x14];
                    CHALLENGE->order[i].charId = id;
                    CHALLENGE->order[i]._2 = i;
                    CHALLENGE->order[i]._3 = pos;
                    g_Roster[i].stats.CharID = id;
                    lbl_80354720[0][i].slot = pos;
                }
                lbl_2_bss_F468._2E = 0;
                lbl_2_bss_100B4 = 1;
                lbl_803CBBCC->step = 8;
            } else if (g_d_GameSettings._10 == 0) {
                if (team != 0) {
                    lbl_2_bss_F468._36 = 0x1E;
                    lbl_803CBBCC->step = 3;
                } else {
                    fn_2_52CC();
                }
            } else {
                lbl_2_bss_100B8._2E[team] = 1;
                if (lbl_2_bss_100B8._2E[0] != 0 && lbl_2_bss_100B8._2E[1] != 0) {
                    lbl_2_bss_F468._4F = 1;
                    lbl_2_bss_F468._36 = 0x1E;
                    lbl_803CBBCC->step = 7;
                }
            }
            fn_800625A4(team, 0x1B);
        } else if (lbl_2_bss_F468._5F[team] == 0) {
            lbl_2_bss_F468._61[team] = lbl_2_bss_F468.cursor[team];
            fn_800625A4(team, 0x1C);
        } else {
            s32 j1 = 0;
            s32 j2 = 0;
            s8 v1 = 0;
            s32 v2 = 0;
            for (i = 0; i < 9; i++) {
                if ((s8)TEAM_ROW(i + 0x14) == (s8)lbl_2_bss_F468._61[team]) {
                    j1 = i;
                    v1 = lbl_2_bss_F468._61[team];
                }
                if ((s8)TEAM_ROW(i + 0x14) == lbl_2_bss_F468.cursor[team]) {
                    j2 = i;
                    v2 = lbl_2_bss_F468.cursor[team];
                }
            }
            TEAM_ROW(j1 + 0x14) = v2;
            TEAM_ROW(j2 + 0x14) = v1;
            fn_800625A4(team, 0x1C);
        }
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (down & 0x200) {
        if (fn_2_35D0(team)) {
            return;
        }
        if (lbl_2_bss_F468._5F[team] != 0) {
            fn_800625A4(team, 0x1D);
        }
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
    } else if (down & 0x20) {
        if (fn_2_35D0(team)) {
            return;
        }
        if (lbl_2_bss_F468._5F[team] != 0) {
            lbl_2_bss_F468._5F[team] = 0;
        }
        fn_800625A4(team, 0x1B);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        lbl_2_bss_F468._59[team] = 0;
    } else if (down & 0x40) {
        s8 v;
        if (fn_2_35D0(team) || g_d_GameSettings.GameModeSelected == 5) {
            return;
        }
        FN_2_3624_FIND_SLOT(lbl_803C6724 + team * 9, lbl_2_bss_F468.cursor[team], slot);
        v = TEAM_ROW(slot + 2);
        if (v == -1 || v == 0x36) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
        if (lbl_2_bss_F468.cursor[team] == 9) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
        lbl_2_bss_F468._50[team] = 0;
        for (g = 0; g < 9; g++) {
            for (k = 0; k < 5; k++) {
                if (v == lbl_80108EDC[g][k]) {
                    lbl_2_bss_F468._50[team] = 1;
                    goto found;
                }
            }
        }
    found:
        if (lbl_2_bss_F468._50[team] != 0) {
            fn_2_A040(g, k, team, slot);
            fn_2_C698(slot, team);
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if (down & 0x10) {
        if (fn_2_35D0(team)) {
            return;
        }
        FN_2_3624_FIND_SLOT(lbl_803C6724 + team * 9, lbl_2_bss_F468.cursor[team], slot);
        if (lbl_2_bss_F468.cursor[team] != 9) {
            s8 v = TEAM_ROW(slot + 2);
            if (v != -1 && v != 0x36 && lbl_2_bss_F468._41[team] == 0) {
                lbl_2_bss_F468._45[team] = 1;
                lbl_2_bss_F468._4B[team] = 1;
                lbl_2_bss_F468._47[team] = 0;
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
            }
        }
    }
}
#undef TEAM_ROW
#endif
