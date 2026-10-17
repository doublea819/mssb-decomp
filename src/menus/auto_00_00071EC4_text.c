#include "menus/auto_00_00071EC4_text.h"

#include "static/UnknownHomes_Static.h"
#include "menus/menu_work.h"
#include "main/file_8000F150.h"
#include "main/SpaniDesc.h"
#include "main/charsel_state.h"

extern s32 fn_80036214(MenuTask* o, s32 a, s32 b, s32 c);
extern s32 fn_8004A34C(MsgBox* box, s8 a, u8 msgId, s8 b, u8 arg);
extern void fn_80023CF4(s32 a);
extern void fn_8004C9FC(void);
extern void fn_2_11A0(u16 v);
extern void fn_8004CA08(u32 v);
void fn_2_75BE4(MenuTask* o, s32 index);
extern u8 lbl_803C6724[];
extern u8 lbl_803CBBC4[];
extern u8 lbl_803CBCD8[];
extern MenuTeamSel lbl_2_bss_F468;
void fn_2_74F40(MenuTask* o, s32 index);
extern MenuCtx* lbl_2_bss_1A8248[];
extern MenuData* lbl_2_bss_1A824C[];
extern void* lbl_2_data_2A1E8[];
extern void* lbl_2_data_2A2EC[];
// .bss 0xA840..0xB29C (mwcc emits file statics in reverse order of definition).
static u8 lbl_2_bss_ABC4[0x6D8]; // unreferenced
static u8 lbl_2_bss_ABC0;
static u8 lbl_2_bss_A848[0x378]; // unreferenced
static s32 lbl_2_bss_A844;
static s32 lbl_2_bss_A840;
extern MenuSelVars lbl_2_bss_F410;
extern SpaniDesc lbl_2_data_2D33C[];
extern void fn_80053FE8(void);
extern void fn_8004E2EC(void);
extern void fn_8004F964(void);
extern void fn_80062674(s32 index);
extern s32 fn_800626EC(s32 index);
extern void fn_800625A4(s32 a, s32 b);
extern MenuTask* lbl_803CC1B8;
extern s32 fn_80042DA8(void* owner, s32 b, s32 c); // owner: LayoutOwner*
extern void fn_80034E20(void* object, void* data);
extern MenuDefEntry lbl_800FEF70[];
extern MenuProgress lbl_80361B20;
extern u8 lbl_800FE930[];
extern CharSelectState lbl_8034E9A0;
extern SpaniDesc lbl_2_data_2B4DC[];
extern SpaniDesc lbl_2_data_2AADC[];
#include "menus/auto_00_00001254_text.h"

// fn_2_73028, size:0x4
void fn_2_73028(void) {
}

// fn_2_71EC4, size:0x38
void fn_2_71EC4(MenuEntry* obj) {
    ((void (*)(MenuEntry*))lbl_2_data_2A1E8[obj->state])(obj);
}

// fn_2_71EFC, size:0x24
void fn_2_71EFC(MenuEntry* obj) {
    s32 i = obj->objectId;
    MenuCtx* b = lbl_2_bss_1A8248[0];
    *((u8*)b + i * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)) = 0;
}

// fn_2_71F60, size:0xD8
void fn_2_71F60(void) {
    s32 off;
    s32 i;
    MenuEntry* obj;
    MenuData* h;
    u8 x = lbl_2_bss_1A8248[0]->_44F2;
#ifdef TARGET_PC
    {
        // MSSB_TRACE_MAP=1: where the map walkers are (port/src/trace.c)
        extern void port_trace_map(const void* entries, int stride, int count, int mode, int nodeOffset);
        port_trace_map(lbl_2_bss_1A8248[0]->entries, sizeof(MenuEntry), 8, x, offsetof(MenuEntry, targetLocation));
    }
#endif
    if (x == 1) {
        return;
    }
    if (x == 2 || x == 3) {
        return;
    }
    i = 0;
    off = 0;
    for (; i < 8; i++) {
        obj = (MenuEntry*)((u8*)lbl_2_bss_1A8248[0] + off + offsetof(MenuCtx, entries));
        PTR32_SET(obj->update, (MenuEntryUpdateFn*)lbl_2_data_2A2EC[obj->typeC3]);
        PTR32_GET(MenuEntryUpdateFn, obj->update)(obj);
        off += sizeof(MenuEntry);
    }
    h = lbl_2_bss_1A824C[0];
    if (h->_1972BC != 0) {
        h->_1972BC = 0;
        REMOVE_QUEUE_NOARG();
    }
}

// fn_2_72038, size:0x1C
void fn_2_72038(s32 index, s16 value) {
    *(s16*)((u8*)lbl_2_bss_1A8248[0] + index * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0]._B4)) = value;
}

// fn_2_72054, size:0x28
void fn_2_72054(s32 index, s8 value) {
    MenuEntry* e = &lbl_2_bss_1A8248[0]->entries[index];
    e->typeC3 = value;
    e->state = 0;
}

// fn_2_72630, size:0x2C
void fn_2_72630(void) {
    fn_800B0A5C_insertQueue((void*)fn_2_72594, 0x3000);
}

// fn_2_73B54, size:0x40
s32 fn_2_73B54(s32 a) {
    s32 b = lbl_2_bss_A840;
    if (b == 0 && a == 6) {
        return 4;
    }
    if (b == 6 && a == 0) {
        return 1;
    }
    return 1;
}

// fn_2_744C8, size:0x50
void fn_2_744C8(void) {
    if ((lbl_803C66B0.steps[1][1] == 1) ? 1 : 0) {
        fn_80062674(0);
        lbl_803C66B0.steps[1][1] = 2;
    }
}

// fn_2_74518, size:0x4C
void fn_2_74518(void) {
    if ((lbl_803C66B0.steps[1][1] == 0) ? 1 : 0) {
        fn_800626EC(0);
        lbl_803C66B0.steps[1][1] = 1;
    }
}

// fn_2_74D8C, size:0x2C
void fn_2_74D8C(void) {
    fn_800B0A5C_insertQueue((void*)fn_2_74CD8, 0x1000);
}

// fn_2_76098, size:0x4
void fn_2_76098(void) {
}

// fn_2_7609C, size:0x30
void fn_2_7609C(s32 unused, u8 a, u8 c) {
    if (c == 0) {
        fn_2_8794(a, 0);
    }
}

// fn_2_7664C, size:0x4
void fn_2_7664C(void) {
}

// fn_2_78034, size:0x28
void fn_2_78034(s32 unused, s32 index) {
    if ((lbl_803C66B0.steps[2][index + 1] == 0) ? 1 : 0) {
        lbl_803C66B0.steps[2][index + 1] = 1;
    }
}

// fn_2_79634, size:0x54
void fn_2_79634(s32 unused, s32 index) {
    if ((lbl_803C66B0.steps[2][index + 1] == 1) ? 1 : 0) {
        fn_80062674(index);
        lbl_803C66B0.steps[2][index + 1] = 2;
    }
}

// fn_2_85108, size:0x54
void fn_2_85108(void) {
    MenuState* a = &lbl_8034E978;
    MenuDefEntry* b = lbl_800FEF70;
    a->menu = 5;
    a->prevTrack = a->track;
    a->track = b[5].track;
    fn_800B0A5C_insertQueue((void*)fn_2_84FA8, 0x3000);
}

// fn_2_8515C, size:0x4
void fn_2_8515C(void) {
}

// fn_2_85160, size:0x48
void fn_2_85160(void) {
    MenuTask* p = lbl_803CC1B8;
    if (--p->_10 == 0) {
        fn_800625A4(0, 4);
        REMOVE_QUEUE_NOARG();
    }
}

// fn_2_73B94, size:0x5C
s32 fn_2_73B94(s32 a) {
    if (lbl_2_bss_A840 == 0 && a == 6) {
        return 0x2D;
    }
    if (lbl_2_bss_A840 == 6 && a == 0) {
        return 0xE;
    }
    if (lbl_2_bss_A840 <= a) {
        return 0x1D;
    } else if (lbl_2_bss_A840 > a) {
        return 0x2C;
    }
}

// fn_2_82CF0, size:0xF8
void fn_2_82CF0(void) {
    MenuTask* o = lbl_8034E9A0._4748;
    if (lbl_803C5EA4._36 != 0) {
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_5C = 0;
        MENU_SLOT_OBJ(&lbl_80371C30[1], o->baseIdx)->_5C = 0x280000;
        (&lbl_80371C30[2])[o->baseIdx].obj->_64 = lbl_803C5EA4.mode + 0x123;
        (&lbl_80371C30[3])[o->baseIdx].obj->_64 = lbl_803C5EA4.prevMode + 0x123;
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_68 = 1;
        MENU_SLOT_OBJ(&lbl_80371C30[1], o->baseIdx)->_68 = 4;
        lbl_803C5EA4._36 = 0;
    }
    if (lbl_8034E9A0._48AF != 0) {
        lbl_8034E9A0._48AF = 0;
        fn_80034CEC(o);
        REMOVE_QUEUE_NOARG();
    }
}

// fn_2_82DE8, size:0x70
void fn_2_82DE8(void) {
    lbl_8034E9A0._4748 = lbl_803CC1B8;
    lbl_8034E9A0._48AF = 0;
    lbl_803C5EA4.prevMode = 0;
    lbl_803C5EA4.mode = 0;
    fn_80034E20(lbl_803CC1B8, lbl_2_data_2B4DC);
    lbl_803CC1B8->func = fn_2_82CF0;
}

// fn_2_82E58, size:0x68
void fn_2_82E58(void) {
    if (lbl_803CBBCC->prevScene != 0xB && g_d_GameSettings.GameModeSelected != 5) {
        fn_800B0A5C_insertQueue((void*)fn_2_82DE8, 0x3000);
    }
    fn_800B0A5C_insertQueue((void*)fn_2_8279C, 0x3000);
}

// fn_2_71F20, size:0x40
void fn_2_71F20(MenuEntry* obj) {
    PTR32_SET(obj->update, (MenuEntryUpdateFn*)lbl_2_data_2A2EC[obj->typeC3]);
    PTR32_GET(MenuEntryUpdateFn, obj->update)(obj);
}

// fn_2_72594, size:0x9C
void fn_2_72594(void) {
    MenuTask* obj;
    s32 i;
    fn_80034E20(obj = lbl_803CC1B8, lbl_2_data_2AADC);
    for (i = 0; i < 4; i++) {
        fn_800363D8(obj, i + 7, 1, 0x32, 3 - i);
    }
    fn_800363D8(obj, 2, 1, 0x35, 0);
    lbl_803CC1B8->func = fn_2_7207C;
}

// fn_2_74DB8, size:0x5C
s32 fn_2_74DB8(s32 a) {
    switch (a) {
    case 13:
    case 16:
    case 20:
    case 22:
    case 25:
    case 34:
    case 42:
    case 50:
    case 52:
        return 1;
    case 21:
    case 24:
    case 29:
    case 33:
    case 44:
    case 51:
    case 53:
        return 2;
    case 23:
    case 30:
    case 36:
    case 45:
        return 3;
    case 12:
    case 26:
    case 27:
    case 31:
    case 35:
    case 43:
    case 46:
    case 49:
        return 4;
    case 32:
        return 5;
    case 47:
        return 6;
    default:
        return 0;
    }
}

// fn_2_74E14, size:0x12C
void fn_2_74E14(MenuTask* o, s32 a, s32 b, u8 c) {
    s32 v = (b - 1) << 16;
    s32 r;
    lbl_80371C30[0x97 + o->baseIdx + a].obj->flags |= 2;
    lbl_80371C30[0x97 + o->baseIdx + a].obj->_5C = 0;
    lbl_80371C30[0x97 + o->baseIdx + a].obj->_68 = 1;
    lbl_80371C30[0x9B + o->baseIdx + c + a * 4].obj->_5C = v;
    r = fn_80036214(o, 0xAB, 0, (b + 1) / 2 - 1);
    lbl_80371C30[0xA3 + o->baseIdx + c + a * 4].obj->_5C = v;
    lbl_80371C30[0xA3 + o->baseIdx + c + a * 4].obj->color = r;
}

// fn_2_75B58, size:0x8C
u8 fn_2_75B58(MenuTask* a, s32 index) {
    s32 i;
    s32 hits;
    s32 total;
    u8 n;
    hits = 0;
    total = 0;
    i = 0;
    n = *(u8*)&lbl_8034E9A0.teamRating[index];
    for (; i < n; i++) {
        total++;
        hits += fn_80042DA8(a, i + 0x6E + index * 5, 0x1E) != 0;
    }
    return hits == total;
}

// fn_2_74CD8, size:0xB4
void fn_2_74CD8(void) {
    MenuTask* obj;
    s32 i;
    fn_80034E20(obj = lbl_803CC1B8, lbl_2_data_2D33C);
    for (i = 0; i < 7; i++) {
        fn_800363D8(obj, i + 0x18, 1, 0x36, i);
    }
    fn_800363D8(obj, 0x20, 1, 0x32, 0);
    lbl_2_bss_A840 = lbl_2_bss_F410._00;
    lbl_803CC1B8->func = fn_2_747FC;
}

// fn_2_836A4, size:0xA0
void fn_2_836A4(void) {
    MenuState* a;
    if (lbl_803C50E8._47 != 0) {
        fn_800B0A5C_insertQueue((void*)fn_80053FE8, 0);
    }
    a = &lbl_8034E978;
    a->prevTrack = a->track;
    a->menu = 0xC;
    a->track = lbl_800FEF70[12].track;
    if (lbl_803CBBCC->prevScene != 9) {
        fn_800B0A5C_insertQueue((void*)fn_2_82DE8, 0x3000);
    }
    fn_800B0A5C_insertQueue((void*)fn_2_834F0, 0x3000);
}

// fn_2_738C8, size:0xCC
void fn_2_738C8(void) {
    MenuState* a;
    if (lbl_803CBBCC->prevScene == 5) {
        fn_800B0A5C_insertQueue((void*)fn_80053FE8, 0);
    }
    if (g_d_GameSettings.GameModeSelected == 5) {
        a = &lbl_8034E978;
        a->menu = 0xD;
        a->prevTrack = a->track;
        a->track = lbl_800FEF70[13].track;
        fn_800B0A5C_insertQueue((void*)fn_8004E2EC, 0x3000);
    } else {
        a = &lbl_8034E978;
        a->menu = 0;
        a->prevTrack = a->track;
        a->track = lbl_800FEF70[0].track;
        fn_800B0A5C_insertQueue((void*)fn_8004F964, 0x3000);
    }
}

// fn_2_72A58, size:0x30
void fn_2_72A58(void) {
    if ((lbl_803CBBC4[3] == 1) ? 1 : 0) {
        lbl_803CBBC4[3] = 0;
        lbl_803CBBC4[2] = 0;
        lbl_803CBBC4[0] = 0;
    }
}

// fn_2_72DDC, size:0x78
void fn_2_72DDC(MenuTask* a) {
    if ((lbl_803CBBC4[3] == 1) ? 1 : 0) {
        if ((s32)(fn_80042DA8(a, 0, 0x19) != 0) == 1) {
            lbl_803CBBC4[3] = 0;
            lbl_803CBBC4[2] = 0;
            lbl_803CBBC4[0] = 0;
        }
    }
}

// fn_2_7293C, size:0xA4
void fn_2_7293C(MenuTask* a) {
    if ((lbl_803CBBC4[3] == 1) ? 1 : 0) {
        s32 n = 0;
        n += fn_80042DA8(a, 0, 0x19) != 0;
        n += fn_80042DA8(a, 1, 0x19) != 0;
        if (n == 2) {
            lbl_803CBBC4[3] = 0;
            lbl_803CBBC4[2] = 0;
            lbl_803CBBC4[0] = 0;
        }
    }
}

// fn_2_728C0, size:0x7C
void fn_2_728C0(MenuTask* o) {
    if ((lbl_803CBBC4[2] == 0) ? 1 : 0) {
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_5C = 0x190000;
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_68 = 4;
        MENU_SLOT_OBJ(&lbl_80371C30[1], o->baseIdx)->_5C = 0x190000;
        MENU_SLOT_OBJ(&lbl_80371C30[1], o->baseIdx)->_68 = 4;
        lbl_803CBBC4[2] = 1;
        lbl_803CBBC4[3] = 1;
    }
}

// fn_2_729E0, size:0x78
void fn_2_729E0(MenuTask* o) {
    if ((lbl_803CBBC4[2] == 0) ? 1 : 0) {
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_5C = 0x190000;
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_68 = 1;
        MENU_SLOT_OBJ(&lbl_80371C30[1], o->baseIdx)->_5C = 0x190000;
        MENU_SLOT_OBJ(&lbl_80371C30[1], o->baseIdx)->_68 = 1;
        lbl_803CBBC4[2] = 1;
        lbl_803CBBC4[3] = 1;
    }
}

// fn_2_72D60, size:0x7C
void fn_2_72D60(MenuTask* o) {
    if ((lbl_803CBBC4[2] == 0) ? 1 : 0) {
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_5C = 0x190000;
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_68 = 4;
        MENU_SLOT_OBJ(&lbl_80371C30[1], o->baseIdx)->_5C = 0x190000;
        MENU_SLOT_OBJ(&lbl_80371C30[1], o->baseIdx)->_68 = 4;
        lbl_803CBBC4[2] = 1;
        lbl_803CBBC4[3] = 1;
    }
}

// fn_2_72814, size:0xAC
void fn_2_72814(MenuTask* a) {
    if ((lbl_803CBBC4[3] == 1) ? 1 : 0) {
        s32 n = 0;
        n += fn_80042DA8(a, 0, 0) != 0;
        n += fn_80042DA8(a, 1, 0) != 0;
        if (n == 2) {
            lbl_803CBBC4[3] = 0;
            lbl_803CBBC4[2] = 0;
            lbl_803CBBC4[0] = 0;
            lbl_803CBBC4[4] = 1;
        }
    }
}

// fn_2_72CB4, size:0xAC
void fn_2_72CB4(MenuTask* a) {
    if ((lbl_803CBBC4[3] == 1) ? 1 : 0) {
        s32 n = 0;
        n += fn_80042DA8(a, 0, 0) != 0;
        n += fn_80042DA8(a, 1, 0) != 0;
        if (n == 2) {
            lbl_803CBBC4[3] = 0;
            lbl_803CBBC4[2] = 0;
            lbl_803CBBC4[0] = 0;
            lbl_803CBBC4[4] = 1;
        }
    }
}

// fn_2_83744, size:0x94
void fn_2_83744(MenuTask* o) {
    if ((MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_5C >> 16) == 0x14) {
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_68 = 1;
    }
    if ((MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_5C >> 16) == 0x1E) {
        lbl_803CBCD8[4] = 1;
        fn_80062674(0);
        lbl_803C66B0.steps[8][1] = 2;
    }
}

// fn_2_8082C, size:0xAC
void fn_2_8082C(MenuTask* a, s32 index) {
    if ((lbl_803C66B0.steps[2][index + 1] == 1) ? 1 : 0) {
        s32 n = 0;
        n += fn_80042DA8(a, index + 0x89, 5) != 0;
        n += fn_80042DA8(a, index + 0x8B, 0xA) != 0;
        if (n == 2) {
            fn_80062674(index);
            lbl_803C66B0.steps[2][index + 1] = 2;
        }
    }
}

// fn_2_80B5C, size:0xD0
void fn_2_80B5C(MenuTask* a, s32 index) {
    if ((lbl_803C66B0.steps[2][index + 1] == 1) ? 1 : 0) {
        s32 n = 0;
        n += fn_80042DA8(a, index, 0) != 0;
        n += fn_80042DA8(a, index + 2, 0) != 0;
        n += fn_80042DA8(a, index + 0x89, 0xA) != 0;
        if (n == 3) {
            fn_80062674(index);
            lbl_803C66B0.steps[2][index + 1] = 2;
        }
    }
}

// fn_2_74564, size:0xD8
void fn_2_74564(MenuTask* a) {
    s32 i;
    s32 hits;
    s32 total;
    s32 cur;
    cur = lbl_2_bss_F410._00;
    if ((lbl_803C66B0.steps[1][1] == 1) ? 1 : 0) {
        hits = 0;
        total = 0;
        for (i = 0; i < 7; i++) {
            if (cur == i) {
                total++;
                hits += fn_80042DA8(a, i + 3, 0xE) != 0;
            }
        }
        hits += fn_80042DA8(a, 0x20, 0xA) != 0;
        if (hits == total + 1) {
            fn_80062674(0);
            lbl_803C66B0.steps[1][1] = 2;
            fn_800625A4(0, 0x57);
        }
    }
}

// fn_2_7EF68, size:0xC8
void fn_2_7EF68(MenuTask* o, s32 index) {
    s32 i;
    for (i = 0; i < 9; i++) {
        if (i == lbl_2_bss_F468.cursor[index]) {
            MENU_SLOT_OBJ(lbl_80371C30, 0x22 + o->baseIdx + i + index * 9)->flags |= 2;
        }
    }
}

// fn_2_79688, size:0xDC
void fn_2_79688(MenuTask* o, s32 index) {
    s32 i;
    if (lbl_803C66B0.steps[2][index + 1] != 0) {
        return;
    }
    for (i = 0; i < 9; i++) {
        MENU_SLOT_OBJ(lbl_80371C30, 0x46 + o->baseIdx + i + index * 9)->_68 = 4;
    }
    MENU_SLOT_OBJ(lbl_80371C30, 0x95 + o->baseIdx + index)->_5C = 0xA0000;
    MENU_SLOT_OBJ(lbl_80371C30, 0x95 + o->baseIdx + index)->_68 = 1;
}

// fn_2_79930, size:0x1F4
void fn_2_79930(MenuTask* o, s32 i) {
    u8* e = (u8*)&lbl_803C66B0 + i;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        s32 base = i * 9;
        s32 j;
        for (j = 0; j < 9; j++) {
            u8* p = lbl_803C6724 + base + j;
            s32 k = *(s8*)(p + 0x14);
            s32 v = *(s8*)(p + 2);
            MENU_SLOT_OBJ(lbl_80371C30, 0x34 + o->baseIdx + k + base)->flags |= 2;
            MENU_SLOT_OBJ(lbl_80371C30, 0x34 + o->baseIdx + k + base)->_5C = 0;
            MENU_SLOT_OBJ(lbl_80371C30, 0x34 + o->baseIdx + k + base)->_68 = 1;
            MENU_SLOT_OBJ(lbl_80371C30, 0x58 + o->baseIdx + k + base)->_5C = v << 16;
        }
        fn_2_75BE4(o, i);
        if (lbl_2_bss_F468.cursor[i] == 9) {
            MENU_SLOT_OBJ(lbl_80371C30, 0x93 + o->baseIdx + i)->_5C = 0;
            MENU_SLOT_OBJ(lbl_80371C30, 0x93 + o->baseIdx + i)->_68 = 1;
            MENU_SLOT_OBJ(lbl_80371C30, 0x95 + o->baseIdx + i)->_5C = 0;
            MENU_SLOT_OBJ(lbl_80371C30, 0x95 + o->baseIdx + i)->_68 = 1;
            MENU_SLOT_OBJ(lbl_80371C30, 0x91 + o->baseIdx + i)->_5C = 0xA0000;
            MENU_SLOT_OBJ(lbl_80371C30, 0x91 + o->baseIdx + i)->_68 = 4;
        }
        fn_800626EC(i);
        *e = 1;
    }
}

// fn_2_7EE7C, size:0xEC
void fn_2_7EE7C(MenuTask* o, s32 index) {
    s32 v = lbl_2_bss_F468.cursor[index];
    if (lbl_2_bss_F468._41[index] != 0) {
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + 0x22 + v + index * 9)->flags &= ~2;
    } else {
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + 0x22 + v + index * 9)->flags |= 2;
    }
    fn_2_74F40(o, index);
    lbl_803C66B0.step[index] = 0;
    if (lbl_2_bss_F468._59[index] != 0) {
        fn_800625A4(index, 0x1A);
    }
}

// fn_2_80500, size:0xDC
void fn_2_80500(MenuTask* o, s32 index) {
    u8* p = (u8*)&lbl_803C66B0 + index;
    if ((*(p += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        u8 b = ((s8)lbl_8034E9A0.ports[0] == 0) ? 1 : 0;
        MENU_SLOT_OBJ(&lbl_80371C30[123], o->baseIdx)->_5C = b << 16;
        MENU_SLOT_OBJ(&lbl_80371C30[25], o->baseIdx)->_5C = (b + 4) << 16;
        fn_800626EC(index);
        *p = 1;
    }
    if (*p == 1) {
        fn_80062674(index);
        *p = 2;
        ((u8*)&g_d_GameSettings)[0x10] = 0;
    }
}

// fn_2_7E860, size:0x114
void fn_2_7E860(MenuTask* a, s32 index) {
    if ((lbl_803C66B0.steps[2][index + 1] == 1) ? 1 : 0) {
        s32 n = 0;
        n += fn_80042DA8(a, index + 0xC, 0xA) != 0;
        n += fn_80042DA8(a, index + 0xE, 0xE) != 0;
        n += fn_80042DA8(a, index + 0x12, 0xA) != 0;
        n += fn_80042DA8(a, index + 0x1C, 0x14) != 0;
        n += fn_80042DA8(a, index + 0x6A, 0x1E) != 0;
        if (n == 5) {
            fn_80062674(index);
            lbl_803C66B0.steps[2][index + 1] = 2;
        }
    }
}

// fn_2_7A460, size:0x158
void fn_2_7A460(MenuTask* o, s32 index) {
    if ((lbl_803C66B0.steps[2][index + 1] == 1) ? 1 : 0) {
        s32 n = 0;
        n += fn_80042DA8(o, index, 0x28) != 0;
        n += fn_80042DA8(o, index + 2, 0x28) != 0;
        n += fn_80042DA8(o, index + 0x85, 0x1E) != 0;
        n += fn_80042DA8(o, index + 0x1C, 0x1E) != 0;
        n += fn_80042DA8(o, index + 0x6A, 0x32) != 0;
        if (n == 5) {
            MENU_SLOT_OBJ(lbl_80371C30, 0xC + o->baseIdx + index)->flags &= ~2;
            MENU_SLOT_OBJ(lbl_80371C30, 0x12 + o->baseIdx + index)->flags &= ~2;
            fn_80062674(index);
            lbl_803C66B0.steps[2][index + 1] = 2;
        }
    }
}

// fn_2_73BF0, size:0xCC
s32 fn_2_73BF0(s32 arg0) {
    s32 r;
    if (lbl_2_bss_A840 == 0 && arg0 == 6) {
        if (lbl_8034E9A0._4752 != 0) { r = 0x36; } else { r = 0x36; }
    } else if (lbl_2_bss_A840 == 6 && arg0 == 0) {
        if (lbl_8034E9A0._4752 != 0) { r = 8; } else { r = 0; }
    } else if (lbl_2_bss_A840 <= arg0) {
        if (lbl_8034E9A0._4752 != 0) { r = 0x17; } else { r = 0xF; }
    } else if (lbl_2_bss_A840 > arg0) {
        if (lbl_8034E9A0._4752 != 0) { r = 0x26; } else { r = 0x1E; }
    } else r = arg0;
    return r;
}

extern SpaniDesc lbl_2_data_2AF4C[];
extern u8 lbl_803C6724[];
extern void fn_2_7308C(void);

// fn_2_73758, size:0x144
void fn_2_73758(void) {
    MenuTask* obj;
    s32 i;
    fn_80034E20(obj = lbl_803CC1B8, lbl_2_data_2AF4C);
    for (i = 0; i < 8; i++) {
        MENU_SLOT_OBJ(lbl_80371C30, obj->baseIdx + i + 4)->_5C = *(s8*)(lbl_803C6724 + 3 + i) << 16;
    }
    lbl_803CBCD8[5] = 0;
    lbl_803CC1B8->func = fn_2_7308C;
}

// fn_2_7A5B8, size:0xDC
void fn_2_7A5B8(MenuTask* o, s32 index) {
    if ((lbl_803C66B0.steps[2][index + 1] == 0) ? 1 : 0) {
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + index)->_5C = 0x140000;
        MENU_SLOT_OBJ(lbl_80371C30, 2 + o->baseIdx + index)->_5C = 0x140000;
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + index)->_68 = 1;
        MENU_SLOT_OBJ(lbl_80371C30, 2 + o->baseIdx + index)->_68 = 1;
        MENU_SLOT_OBJ(lbl_80371C30, 133 + o->baseIdx + index)->_5C = 0x140000;
        MENU_SLOT_OBJ(lbl_80371C30, 133 + o->baseIdx + index)->_68 = 1;
        MENU_SLOT_OBJ(lbl_80371C30, 28 + o->baseIdx + index)->_5C = 0x140000;
        MENU_SLOT_OBJ(lbl_80371C30, 28 + o->baseIdx + index)->_68 = 1;
        MENU_SLOT_OBJ(lbl_80371C30, 106 + o->baseIdx + index)->_5C = 0x1E0000;
        MENU_SLOT_OBJ(lbl_80371C30, 106 + o->baseIdx + index)->_68 = 1;
        if (g_d_GameSettings.GameModeSelected != 5 || index == 0) {
            MENU_SLOT_OBJ(lbl_80371C30, 147 + o->baseIdx + index)->flags &= ~2;
        }
        fn_800626EC(index);
        lbl_803C66B0.steps[2][index + 1] = 1;
    }
}

extern u8 lbl_2_data_2DC84[];
extern SpaniDesc lbl_2_data_2DC8C[];
extern void fn_2_845A8(void);

// fn_2_84FA8, size:0x160
void fn_2_84FA8(void) {
    MenuTask* obj;
    s32 i;
    s8 v;
    fn_80034E20(obj = lbl_803CC1B8, lbl_2_data_2DC8C);
    for (i = 0; i < 6; i++) {
        if (lbl_80361B20._F5 == 0 && lbl_2_data_2DC84[i] == 1) {
            v = 6;
        } else {
            v = lbl_2_data_2DC84[i];
        }
        fn_800363D8(obj, i + 6, 2, 0x1E, v);
    }
    if (lbl_80361B20._F5 == 0 && lbl_2_data_2DC84[lbl_2_bss_F410._44] == 1) {
        v = 0x12;
    } else {
        v = lbl_2_data_2DC84[lbl_2_bss_F410._44];
    }
    if (lbl_2_bss_F410._44 != 0) {
        fn_800363D8(obj, 0, 1, 0x20, v);
    }
    lbl_803CBCD8[4] = 0;
    obj->timerA = 0;
    lbl_803CC1B8->func = fn_2_845A8;
}

// fn_2_851A8, size:0x168
void fn_2_851A8(void) {
    switch (lbl_803CC1B8->_10) {
    case 0:
        fn_800625A4(0, 0);
        lbl_803CC1B8->_10 = lbl_803CC1B8->_10 + 1;
    case 1:
        if (lbl_803C66B0.steps[0][1] == 0) {
            lbl_803C66B0.steps[0][1] = 1;
            fn_800626EC(0);
            switch (lbl_803C66B0.step[0]) {
            case 0:
            case 1:
            case 2:
            case 3:
                break;
            case 4:
                fn_80062674(0);
                break;
            }
        }
        if (lbl_803C66B0.steps[0][1] == 1) {
            switch (lbl_803C66B0.step[0]) {
            case 0:
            case 1:
            case 2:
                lbl_803C66B0.steps[0][1] = 2;
                fn_80062674(0);
                break;
            case 3:
                if (lbl_2_bss_F410._00 == 0) {
                    lbl_803C66B0.steps[0][1] = 2;
                    ((MenuTask*)fn_800B0A5C_insertQueue((void*)fn_2_85160, lbl_803CC1B8->priority))->_10 = 0xB4;
                } else {
                    fn_800625A4(0, 4);
                }
                break;
            case 4:
                lbl_803C66B0.steps[0][1] = 2;
                fn_80062674(0);
                REMOVE_QUEUE_NOARG();
                break;
            }
        }
        break;
    }
}

extern u8 lbl_800EFBA4[];
extern u32 sndFXStartEx(u32 fid, u8 vol, u8 pan, u8 studio);

// fn_2_85310, size:0x1A0
s32 fn_2_85310(u16 a, u16 b, u16 c) {
    s32 r = 0;
    if (c & 3) {
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        if (lbl_2_bss_F410._00 == 1) {
            fn_800625A4(0, 1);
        } else {
            fn_800625A4(0, 2);
        }
        lbl_2_bss_F410._00 ^= 1;
    } else if (b & 0x100) {
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        fn_800625A4(0, 3);
        r = 1;
    } else if (b & 0x200) {
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        if (lbl_2_bss_F410._00 == 1) {
            fn_800625A4(0, 3);
            r = 1;
        } else {
            fn_800625A4(0, 2);
            lbl_2_bss_F410._00 = 1;
        }
    }
    if ((c | (a | b)) != 0) {
        lbl_2_bss_F410._04 = 0x258;
    } else {
        if (--lbl_2_bss_F410._04 == 0) {
            fn_800625A4(0, 3);
            r = 1;
        }
    }
    return r;
}

extern s8 lbl_2_data_2E2EC;

// fn_2_854B0, size:0x18C
void fn_2_854B0(void) {
    MsgBox* g;
    switch (lbl_803CBBCC->step) {
    case 0:
        fn_8004CA08(0x258);
        fn_8004A34C(&lbl_803C50E8, 0, 0x4A, 0, 0);
        lbl_803CBBCC->step = 2;
        break;
    case 2:
        g = &lbl_803C50E8;
        switch (g->result) {
        case 2:
        case 4:
            fn_8004C9FC();
            fn_80023CF4(g->result == 2);
            {
                s32 st = 4;
                if (g->result == 2) {
                    st = 3;
                }
                lbl_803CBBCC->step = st;
            }
            break;
        }
        break;
    case 3:
        fn_8004A34C(&lbl_803C50E8, 0, 0x4B, 0, 0);
        lbl_803CBBCC->step = 6;
        break;
    case 4:
        fn_8004A34C(&lbl_803C50E8, 0, 0x4C, 0, 0);
        lbl_803CBBCC->step = 6;
        break;
    case 6:
        switch (lbl_803C50E8.result) {
        case 2:
            fn_2_11A0(1);
            fn_8004CA08(-1);
            break;
        }
        break;
    }
}

// fn_2_837D8, size:0x19C
void fn_2_837D8(MenuTask* o) {
    s32 n;
    s32 v;
    if ((lbl_803C66B0.steps[7][1] == 0) ? 1 : 0) {
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_68 = 4;
        MENU_SLOT_OBJ(&lbl_80371C30[1], o->baseIdx)->_5C = 0;
        MENU_SLOT_OBJ(&lbl_80371C30[1], o->baseIdx)->_68 = 0;
        (&lbl_80371C30[2])[o->baseIdx].obj->_68 = 1;
        (&lbl_80371C30[5])[o->baseIdx].obj->_68 = 1;
        (&lbl_80371C30[3])[o->baseIdx].obj->_68 = 1;
        MENU_SLOT_OBJ(&lbl_80371C30[4], o->baseIdx)->_5C = 0x280000;
        MENU_SLOT_OBJ(&lbl_80371C30[4], o->baseIdx)->_68 = 4;
        fn_800626EC(0);
        lbl_803C66B0.steps[7][1] = 1;
    }
    if (lbl_803C66B0.steps[7][1] == 1) {
        n = fn_80042DA8(o, 0, 0xA) != 0;
        if (n + (fn_80042DA8(o, 4, 0x14) != 0) == 2) {
            v = lbl_2_bss_F410._44;
            if (lbl_80361B20._F5 == 0 && v != 0) {
                v -= 1;
            }
            lbl_2_data_2E2EC = v;
#if NONMATCHING
            fn_80062674(0);
#else
            // fn_80062674 ignores a second argument; the original passes &lbl_2_data_2E2EC in r4.
            ((void (*)(s32, s8*))fn_80062674)(0, &lbl_2_data_2E2EC);
#endif
            lbl_803C66B0.steps[7][1] = 2;
        }
    }
}

extern void fn_80062674(s32 index);
extern s32 fn_800626EC(s32 index);

// fn_2_78F78, size:0x1B4
void fn_2_78F78(MenuTask* o, s32 i) {
    u8* e = (u8*)&lbl_803C66B0 + i;
    s32 ok = (*(e += offsetof(TutorialSteps, steps[2][1])) == 0);
    if (ok) {
        MENU_SLOT_OBJ(lbl_80371C30, 0xA + o->baseIdx + i)->flags |= 2;
        MENU_SLOT_OBJ(lbl_80371C30, 0xA + o->baseIdx + i)->_68 = 1;
        MENU_SLOT_OBJ(lbl_80371C30, 0x1E + o->baseIdx + i)->_68 = 1;
        MENU_SLOT_OBJ(lbl_80371C30, 0x89 + o->baseIdx + i)->_5C = 0;
        MENU_SLOT_OBJ(lbl_80371C30, 0x89 + o->baseIdx + i)->_68 = 1;
        MENU_SLOT_OBJ(lbl_80371C30, 0x8D + o->baseIdx + i)->_5C = 0;
        MENU_SLOT_OBJ(lbl_80371C30, 0x8D + o->baseIdx + i)->_68 = 1;
        MENU_SLOT_OBJ(lbl_80371C30, 0x6A + o->baseIdx + i)->_68 = 4;
        if (((u8*)&g_d_GameSettings)[7] != 5) {
            MENU_SLOT_OBJ(lbl_80371C30, 0x8F + o->baseIdx + i)->_64 = 8;
            MENU_SLOT_OBJ(lbl_80371C30, 0x8F + o->baseIdx + i)->_5C = 0;
            MENU_SLOT_OBJ(lbl_80371C30, 0x8F + o->baseIdx + i)->_68 = 1;
        }
        fn_800626EC(i);
        *e = 1;
    }
    if (*e == 1) {
        fn_80062674(i);
        *e = 2;
    }
}

extern u8 lbl_800FE5D4[];
extern u8 lbl_2_data_2B3A4[];
// The challenge save block (starMissionCompletionTracker) as the menus see it.
#define CHALLENGE ((MenuCtx*)starMissionCompletionTracker)

// fn_2_73994, size:0x1C0
void fn_2_73994(MenuTask* o, s32 i) {
    s32 a;
    s32 b;
    u8 x;
    u8 y;
    if (((u8*)&g_d_GameSettings)[7] != 5) {
        b = lbl_803C6724[i];
        a = lbl_800FE5D4[lbl_2_bss_F410.charSel[i]];
        b = lbl_800FE5D4[b];
    } else if (i != 0) {
        b = *(s8*)&CHALLENGE->_441F;
        a = b;
    } else {
        a = b = CHALLENGE->_441D;
    }
    x = lbl_8034E9A0.roster[a / 9][a % 9].stats.CaptainStarHitPitch;
    y = lbl_8034E9A0.roster[b / 9][b % 9].stats.CaptainStarHitPitch;
    MENU_SLOT_OBJ(lbl_80371C30, 0x82 + o->baseIdx + i)->_5C = lbl_2_data_2B3A4[x] << 16;
    MENU_SLOT_OBJ(lbl_80371C30, 0x7E + o->baseIdx + i)->_5C = lbl_2_data_2B3A4[x] << 16;
    fn_800363D8(o, i + 0x89, 1, 3, lbl_2_data_2B3A4[x]);
    fn_800363D8(o, i + 0x8B, 1, 3, lbl_2_data_2B3A4[y]);
}

// fn_2_83974, size:0x168
void fn_2_83974(MenuTask* o) {
    s32 n;
    if ((lbl_803C66B0.steps[7][1] == 0) ? 1 : 0) {
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_5C = 0xA0000;
        MENU_SLOT_OBJ(&lbl_80371C30[1], o->baseIdx)->_5C = 0;
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_68 = 1;
        MENU_SLOT_OBJ(&lbl_80371C30[1], o->baseIdx)->_68 = 0;
        (&lbl_80371C30[2])[o->baseIdx].obj->_68 = 4;
        (&lbl_80371C30[3])[o->baseIdx].obj->_68 = 4;
        (&lbl_80371C30[5])[o->baseIdx].obj->_68 = 4;
        (&lbl_80371C30[4])[o->baseIdx].obj->_68 = 1;
        fn_800626EC(0);
        lbl_803C66B0.steps[7][1] = 1;
    }
    if (lbl_803C66B0.steps[7][1] == 1) {
        n = fn_80042DA8(o, 0, 0x14) != 0;
        n += fn_80042DA8(o, 2, 0) != 0;
        n += fn_80042DA8(o, 5, 0) != 0;
        n += fn_80042DA8(o, 3, 0) != 0;
        if (n == 4) {
            lbl_2_data_2E2EC = lbl_2_bss_F410._44;
            fn_80062674(0);
            lbl_803C66B0.steps[7][1] = 2;
        }
    }
}

#include "main/file_8001FE00.h" // SceneFade lbl_8037169C
extern void changeScene(s32 a, s32 b);

// fn_2_7463C, size:0x1C0
s32 fn_2_7463C(MenuTask* o) {
    s32 i;
    s32 cur = lbl_2_bss_F410._00;
    s32 ok = (lbl_803C66B0.steps[1][1] == 0);
    if (ok) {
        for (i = 0; i < 7; i++) {
            if (cur == i) {
                MENU_SLOT_OBJ(lbl_80371C30, 3 + o->baseIdx + i)->flags |= 2;
                MENU_SLOT_OBJ(lbl_80371C30, 3 + o->baseIdx + i)->_5C = 0;
                MENU_SLOT_OBJ(lbl_80371C30, 3 + o->baseIdx + i)->_68 = 1;
                MENU_SLOT_OBJ(lbl_80371C30, 0x18 + o->baseIdx + i)->_5C = 0;
                MENU_SLOT_OBJ(lbl_80371C30, 0x18 + o->baseIdx + i)->_68 = 1;
            } else {
                MENU_SLOT_OBJ(lbl_80371C30, 0x18 + o->baseIdx + i)->_5C = 0;
                MENU_SLOT_OBJ(lbl_80371C30, 0x18 + o->baseIdx + i)->_68 = 0;
                MENU_SLOT_OBJ(lbl_80371C30, 3 + o->baseIdx + i)->flags &= ~2;
            }
        }
        if (lbl_8037169C.state != 0) {
            changeScene(1, 6);
        }
        MENU_SLOT_OBJ(&lbl_80371C30[32], o->baseIdx)->_5C = 0;
        MENU_SLOT_OBJ(&lbl_80371C30[32], o->baseIdx)->_68 = 1;
        ok = fn_800626EC(0);
        lbl_803C66B0.steps[1][1] = 1;
    }
    return ok;
}

extern SpaniDesc lbl_2_data_2E02C[];
extern void fn_2_82EC0(void);

// fn_2_834F0, size:0x1B4
void fn_2_834F0(void) {
    MenuTask* obj;
    s32 i;
    fn_80034E20(obj = lbl_803CC1B8, lbl_2_data_2E02C);
    for (i = 0; i < 4; i++) {
        if (lbl_2_bss_F468._57 < i) {
            fn_800363D8(obj, i + 3, 1, 0x6B, 4);
        } else {
            fn_800363D8(obj, i + 3, 1, 0x6B, i);
        }
    }
    MENU_SLOT_OBJ(&lbl_80371C30[12], obj->baseIdx)->_5C = 0;
    if (lbl_80361B20._F4 != 0) {
        (&lbl_80371C30[1])[obj->baseIdx].obj->_64 = 0x22;
        (&lbl_80371C30[11])[obj->baseIdx].obj->_5C = 0x40000;
    } else {
        (&lbl_80371C30[1])[obj->baseIdx].obj->_64 = 0x21;
        (&lbl_80371C30[11])[obj->baseIdx].obj->_5C = 0;
    }
    if (lbl_80361B20._E4[0] != 0) {
        MENU_SLOT_OBJ(&lbl_80371C30[9], obj->baseIdx)->flags |= 2;
        MENU_SLOT_OBJ(&lbl_80371C30[9], obj->baseIdx)->_68 = 1;
        fn_800363D8(obj, 9, 1, 0x27, 0);
    }
    lbl_803CC1B8->func = fn_2_82EC0;
}

// fn_2_80C2C, size:0x1E0
void fn_2_80C2C(MenuTask* o, s32 i) {
    u8* e = (u8*)&lbl_803C66B0 + i;
    s32 ok = (*(e += offsetof(TutorialSteps, steps[2][1])) == 0);
    if (ok) {
        if (lbl_803C66B0.active[i] != 0) {
            fn_80062674(i);
            lbl_803C66B0.step[i] = 2;
        }
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + i)->_5C = 0x140000;
        MENU_SLOT_OBJ(lbl_80371C30, 2 + o->baseIdx + i)->_5C = 0x140000;
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + i)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 2 + o->baseIdx + i)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 4 + o->baseIdx + i)->_5C = 0x1E0000;
        MENU_SLOT_OBJ(lbl_80371C30, 4 + o->baseIdx + i)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 0x89 + o->baseIdx + i)->_68 = 1;
        MENU_SLOT_OBJ(lbl_80371C30, 0x80 + o->baseIdx + i)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 0x78 + o->baseIdx + i)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 0x7C + o->baseIdx + i)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 0x97 + o->baseIdx + i)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 0xAC + o->baseIdx + i)->_68 = 4;
        (&lbl_80371C30[132])[o->baseIdx].obj->flags &= ~2;
        fn_800626EC(i);
        *e = 1;
    }
}

// fn_2_84194, size:0x1F4
void fn_2_84194(MenuTask* o) {
    s32 n;
    if ((lbl_803C66B0.steps[7][1] == 0) ? 1 : 0) {
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_5C = 0xA0000;
        MENU_SLOT_OBJ(&lbl_80371C30[1], o->baseIdx)->_5C = 0xA0000;
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_68 = 4;
        MENU_SLOT_OBJ(&lbl_80371C30[1], o->baseIdx)->_68 = 4;
        (&lbl_80371C30[2])[o->baseIdx].obj->_68 = 4;
        (&lbl_80371C30[3])[o->baseIdx].obj->_68 = 4;
        (&lbl_80371C30[5])[o->baseIdx].obj->_68 = 4;
        (&lbl_80371C30[4])[o->baseIdx].obj->_68 = 4;
        fn_800626EC(0);
        lbl_803C66B0.steps[7][1] = 1;
    }
    if (lbl_803C66B0.steps[7][1] == 1) {
        n = fn_80042DA8(o, 0, 0) != 0;
        n += fn_80042DA8(o, 1, 0) != 0;
        n += fn_80042DA8(o, 2, 0) != 0;
        n += fn_80042DA8(o, 3, 0) != 0;
        n += fn_80042DA8(o, 5, 0) != 0;
        if (n == 5) {
            lbl_2_data_2E2EC = lbl_2_bss_F410._44;
            fn_80062674(0);
            lbl_803C66B0.steps[7][1] = 2;
            lbl_2_data_2E2EC = -1;
            fn_80034CEC(o);
            REMOVE_QUEUE_NOARG();
        }
    }
}



// fn_2_802EC, size:0x214
void fn_2_802EC(MenuTask* o) {
    s32 n;
    if ((lbl_803C66B0.steps[2][2] == 0) ? 1 : 0) {
        MENU_SLOT_OBJ(&lbl_80371C30[129], o->baseIdx)->flags |= 2;
        MENU_SLOT_OBJ(&lbl_80371C30[129], o->baseIdx)->_5C = 0;
        MENU_SLOT_OBJ(&lbl_80371C30[129], o->baseIdx)->_68 = 1;
        MENU_SLOT_OBJ(&lbl_80371C30[132], o->baseIdx)->flags &= ~2;
        MENU_SLOT_OBJ(&lbl_80371C30[132], o->baseIdx)->_68 = 0;
        MENU_SLOT_OBJ(&lbl_80371C30[125], o->baseIdx)->_5C = 0;
        MENU_SLOT_OBJ(&lbl_80371C30[125], o->baseIdx)->_68 = 1;
        (&lbl_80371C30[152])[o->baseIdx].obj->flags |= 2;
        MENU_SLOT_OBJ(&lbl_80371C30[134], o->baseIdx)->_5C = 0;
        MENU_SLOT_OBJ(&lbl_80371C30[134], o->baseIdx)->_68 = 1;
        MENU_SLOT_OBJ(&lbl_80371C30[138], o->baseIdx)->_5C = 0;
        MENU_SLOT_OBJ(&lbl_80371C30[138], o->baseIdx)->_68 = 1;
        fn_2_7630C(o, 1);
        fn_2_74F40(o, 1);
        fn_800626EC(1);
        lbl_803C66B0.steps[2][2] = 1;
    }
    if (lbl_803C66B0.steps[2][2] == 1) {
        n = fn_80042DA8(o, 0x81, 0x14) != 0;
        n += fn_80042DA8(o, 0x7D, 0x14) != 0;
        n += fn_80042DA8(o, 0x86, 0xA) != 0;
        n += fn_80042DA8(o, 0x8A, 5) != 0;
        if (n == 4) {
            fn_80062674(1);
            lbl_803C66B0.steps[2][2] = 2;
        }
    }
}

// fn_2_84388, size:0x220
void fn_2_84388(MenuTask* o) {
    s32 n;
    s32 cur;
    if ((lbl_803C66B0.steps[7][1] == 0) ? 1 : 0) {
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_5C = 0;
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx)->_68 = 1;
        cur = lbl_2_bss_F410._44;
        MENU_SLOT_OBJ(&lbl_80371C30[4], o->baseIdx)->_5C = 0;
        MENU_SLOT_OBJ(&lbl_80371C30[4], o->baseIdx)->_68 = 1;
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + 6)->color = (MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + 6)->color & ~0xFF) | 0xFF;
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + 7)->color = (MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + 7)->color & ~0xFF) | 0xFF;
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + 8)->color = (MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + 8)->color & ~0xFF) | 0xFF;
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + 9)->color = (MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + 9)->color & ~0xFF) | 0xFF;
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + 10)->color = (MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + 10)->color & ~0xFF) | 0xFF;
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + 11)->color = (MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + 11)->color & ~0xFF) | 0xFF;
        MENU_SLOT_OBJ(lbl_80371C30, 6 + o->baseIdx + cur)->_5C = 0x10000;
        MENU_SLOT_OBJ(lbl_80371C30, 6 + o->baseIdx + cur)->_68 = 1;
        fn_800626EC(0);
        lbl_803C66B0.steps[7][1] = 1;
    }
    if (lbl_803C66B0.steps[7][1] == 1) {
        n = fn_80042DA8(o, 0, 0xA) != 0;
        if (n + (fn_80042DA8(o, 4, 0x14) != 0) == 2) {
            lbl_2_data_2E2EC = lbl_2_bss_F410._44;
            fn_80062674(0);
            lbl_803C66B0.steps[7][1] = 2;
        }
    }
}

// fn_2_800B0, size:0x23C
void fn_2_800B0(MenuTask* o, s32 i) {
    u8* e = (u8*)&lbl_803C66B0 + i;
    s32 n;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + i)->_5C = 0x140000;
        MENU_SLOT_OBJ(lbl_80371C30, 2 + o->baseIdx + i)->_5C = 0x140000;
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + i)->_68 = 1;
        MENU_SLOT_OBJ(lbl_80371C30, 2 + o->baseIdx + i)->_68 = 1;
        MENU_SLOT_OBJ(lbl_80371C30, 0x80 + o->baseIdx + i)->_5C = 0x140000;
        MENU_SLOT_OBJ(lbl_80371C30, 0x80 + o->baseIdx + i)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 0x78 + o->baseIdx + i)->_5C = 0x140000;
        MENU_SLOT_OBJ(lbl_80371C30, 0x78 + o->baseIdx + i)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 0x7C + o->baseIdx + i)->_5C = 0x140000;
        MENU_SLOT_OBJ(lbl_80371C30, 0x7C + o->baseIdx + i)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 0x97 + o->baseIdx + i)->_64 = 0x77;
        MENU_SLOT_OBJ(lbl_80371C30, 0x97 + o->baseIdx + i)->_5C = 0;
        MENU_SLOT_OBJ(lbl_80371C30, 0x97 + o->baseIdx + i)->flags &= ~2;
        MENU_SLOT_OBJ(lbl_80371C30, 0xB0 + o->baseIdx + i)->flags &= ~2;
        fn_800626EC(i);
        *e = 1;
    }
    if (*e == 1) {
        n = fn_80042DA8(o, i, 0x1E) != 0;
        if (n + (fn_80042DA8(o, i + 2, 0x1E) != 0) == 2) {
            fn_80062674(i);
            *e = 2;
        }
    }
}

// fn_2_760CC, size:0x240
void fn_2_760CC(MenuTask* o) {
    s32 a;
    s32 b;
    u8 x;
    u8 y;
    a = (lbl_800FE930 + lbl_80361B20._F4 * 6)[lbl_2_bss_F410.charSel[0]];
    b = (lbl_800FE930 + lbl_80361B20._F4 * 6)[lbl_803C6724[0]];
    x = lbl_8034E9A0.roster[a / 9][a % 9].stats.CaptainStarHitPitch;
    y = lbl_8034E9A0.roster[b / 9][b % 9].stats.CaptainStarHitPitch;
    MENU_SLOT_OBJ(&lbl_80371C30[130], o->baseIdx)->_5C = lbl_2_data_2B3A4[x] << 16;
    fn_800363D8(o, 0x89, 1, 3, lbl_2_data_2B3A4[x]);
    fn_800363D8(o, 0x8B, 1, 3, lbl_2_data_2B3A4[y]);
    (&lbl_80371C30[126])[o->baseIdx].obj->_5C = lbl_2_data_2B3A4[x] << 16;
    MENU_SLOT_OBJ(&lbl_80371C30[128], o->baseIdx)->_5C = 0;
    MENU_SLOT_OBJ(&lbl_80371C30[137], o->baseIdx)->_5C = 0;
    MENU_SLOT_OBJ(&lbl_80371C30[139], o->baseIdx)->_5C = 0xA0000;
    MENU_SLOT_OBJ(&lbl_80371C30[120], o->baseIdx)->_5C = 0;
    MENU_SLOT_OBJ(&lbl_80371C30[124], o->baseIdx)->_5C = 0;
    MENU_SLOT_OBJ(&lbl_80371C30[128], o->baseIdx)->_68 = 1;
    MENU_SLOT_OBJ(&lbl_80371C30[137], o->baseIdx)->_68 = 1;
    MENU_SLOT_OBJ(&lbl_80371C30[139], o->baseIdx)->_68 = 4;
    MENU_SLOT_OBJ(&lbl_80371C30[120], o->baseIdx)->_68 = 1;
    MENU_SLOT_OBJ(&lbl_80371C30[124], o->baseIdx)->_68 = 1;
}

extern void fn_2_16A74(s32 a, s32 b);
extern CaptainSelMenu lbl_2_bss_100B8;

// fn_2_805DC, size:0x250
void fn_2_805DC(MenuTask* o, s32 i) {
    u8* e = (u8*)&lbl_803C66B0 + i;
    u8 f;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        (&lbl_80371C30[129])[o->baseIdx].obj->flags &= ~2;
        MENU_SLOT_OBJ(&lbl_80371C30[132], o->baseIdx)->flags |= 2;
        MENU_SLOT_OBJ(&lbl_80371C30[132], o->baseIdx)->_68 = 1;
        (&lbl_80371C30[152])[o->baseIdx].obj->flags &= ~2;
        MENU_SLOT_OBJ(&lbl_80371C30[134], o->baseIdx)->_5C = 0xA0000;
        MENU_SLOT_OBJ(&lbl_80371C30[134], o->baseIdx)->_68 = 4;
        MENU_SLOT_OBJ(&lbl_80371C30[138], o->baseIdx)->_5C = 0x50000;
        MENU_SLOT_OBJ(&lbl_80371C30[138], o->baseIdx)->_68 = 4;
        MENU_SLOT_OBJ(&lbl_80371C30[121], o->baseIdx)->_5C = 0x140000;
        MENU_SLOT_OBJ(&lbl_80371C30[121], o->baseIdx)->_68 = 4;
        MENU_SLOT_OBJ(&lbl_80371C30[125], o->baseIdx)->_5C = 0x140000;
        MENU_SLOT_OBJ(&lbl_80371C30[125], o->baseIdx)->_68 = 4;
        f = ((s8)lbl_8034E9A0.ports[0] == 0);
        (&lbl_80371C30[123])[o->baseIdx].obj->_5C = f << 16;
        (&lbl_80371C30[25])[o->baseIdx].obj->_5C = (f + 4) << 16;
        fn_800626EC(i);
        *e = 1;
    }
    if (*e == 1) {
        u8 n = (fn_80042DA8(o, 0x86, 0) != 0);
        if (n + (fn_80042DA8(o, 0x8A, 0) != 0) == 2) {
            if (((u8*)&g_d_GameSettings)[0x10] == 1 && lbl_2_bss_100B8.picked[0] == 0) {
                fn_2_16A74(1, 0);
            }
            fn_80062674(i);
            *e = 2;
            ((u8*)&g_d_GameSettings)[0x10] = 0;
        }
    }
}

// fn_2_80E0C, size:0x150
void fn_2_80E0C(MenuTask* a, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 1) ? 1 : 0) {
        s32 n;
        s32 k;
        n = 0;
        k = 0;
        k++;
        n += fn_80042DA8(a, index, 0x14) != 0;
        k++;
        n += fn_80042DA8(a, index + 2, 0x14) != 0;
        if (index == 0 || lbl_2_bss_100B8.picked[0] != 0 || ((u8*)&g_d_GameSettings)[0x10] != 0) {
            k++;
            n += fn_80042DA8(a, index + 0x85, 0xA) != 0;
            k++;
            n += fn_80042DA8(a, index + 0x87, 0xA) != 0;
            k++;
            n += fn_80042DA8(a, index + 0x89, 5) != 0;
            k++;
            n += fn_80042DA8(a, index + 0x8B, 0xA) != 0;
        }
        if (n == k) {
            fn_80062674(index);
            *e = 2;
        }
    }
}

// fn_2_79B24, size:0x1D4
void fn_2_79B24(MenuTask* a, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 1) ? 1 : 0) {
        s32 n;
        s32 k;
        s32 j;
        s32 found;
        s8 v;
        n = 0;
        k = 0;
        v = (s8)lbl_2_bss_F468.cursor[index];
        for (j = 0; j < 9; j++) {
            if (v == (s8)lbl_803C6724[index * 9 + j + 0x14]) {
                found = j;
                break;
            }
        }
        if ((s8)(lbl_803C6724 + index * 9)[found + 2] != -1) {
            k++;
            n += fn_80042DA8(a, v + 0x34 + index * 9, 0xA) != 0;
        }
        if (n == k) {
            fn_80062674(index);
            *e = 2;
        }
    }
}

// fn_2_79FAC, size:0x1E8
void fn_2_79FAC(MenuTask* a, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 1) ? 1 : 0) {
        s32 n;
        s32 k;
        s32 j;
        s8 found;
        s32 v;
        n = 0;
        k = 0;
        v = lbl_2_bss_F468.prevCursor[index];
        for (j = 0; j < 9; j++) {
            s32 t = (s8)lbl_803C6724[index * 9 + j + 0x14];
            if (t == v) {
                found = j;
                break;
            }
        }
        if ((s8)(lbl_803C6724 + index * 9)[found + 2] != -1 && (s8)(lbl_803C6724 + index * 9)[found + 2] != 0x36 && v < 9) {
            k++;
            n += fn_80042DA8(a, v + 0x34 + index * 9, 0x14) != 0;
        }
        if (n == k) {
            fn_80062674(index);
            *e = 2;
        }
    }
}

// fn_2_79764, size:0x1CC


static inline s32 CheckRowHits(MenuTask* a, s32 base, u8 count) {
    s32 i;
    s32 n = 0;
    s32 k = 0;
    for (i = 0; i < count; i++) {
        k++;
        n += fn_80042DA8(a, i + 0x6E + base, 0x1E) != 0;
    }
    return n == k;
}

void fn_2_79764(MenuTask* a, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 1) ? 1 : 0) {
        s32 j;
        s32 n1;
        s32 k1;
        s32 i;
        n1 = 0;
        k1 = 0;
        for (i = 0; i < 9; i++) {
            k1++;
            n1 += fn_80042DA8(a, i + 0x34 + index * 9, 0x14) != 0;
        }
        if (CheckRowHits(a, index * 5, *(u8*)&lbl_8034E9A0.teamRating[index]) && n1 == k1) {
            for (j = 0; j < 9; j++) {
                if (*(s8*)(lbl_803C6724 + index * 9 + j + 0x4A) == 0) {
                    lbl_803C6724[index * 9 + j + 0x4A] = 1;
                }
            }
            fn_80062674(index);
            *e = 2;
        }
    }
}

extern void fn_2_CCE0(u8 a);

// fn_2_7F714, size:0x1A8
void fn_2_7F714(MenuTask* a, s32 index) {
    s32 n;
    s32 k;
    s32 j;
    s32 v;
    s32 found;
    if (lbl_803C66B0.steps[2][index + 1] == 1) {
        n = 0;
        k = 0;
        v = (s8)lbl_2_bss_F468.cursor[index];
        for (j = 0; j < 9; j++) {
            s32 t = (s8)lbl_803C6724[index * 9 + j + 0x14];
            if (t == v) {
                found = j;
                break;
            }
        }
        k++;
        n += fn_80042DA8(a, v + 0x34 + index * 9, 0xA) != 0;
        if (CheckRowHits(a, index * 5, *(u8*)&lbl_8034E9A0.teamRating[index]) && n == k) {
            fn_80062674(index);
            fn_2_CCE0(index);
        }
    }
}

// fn_2_7AC64, size:0x1D8
void fn_2_7AC64(MenuTask* a, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 1) ? 1 : 0) {
        s32 n;
        s32 k;
        n = 0;
        k = 0;
        k++;
        n += fn_80042DA8(a, index, 0x14) != 0;
        k++;
        n += fn_80042DA8(a, index + 2, 0x14) != 0;
        k++;
        n += fn_80042DA8(a, index + 0x1C, 0xA) != 0;
        k++;
        n += fn_80042DA8(a, index + 0x6A, 0xA) != 0;
        if (((u8*)&g_d_GameSettings)[7] == 5) {
            k++;
            n += fn_80042DA8(a, index + 0x89, 5) != 0;
            k++;
            n += fn_80042DA8(a, index + 0x85, 0xA) != 0;
        }
        if (CheckRowHits(a, index * 5, *(u8*)&lbl_8034E9A0.teamRating[index]) && n == k) {
            fn_80062674(index);
            if (lbl_803CBBCC->prevScene == 0xB && index == 0 && ((u8*)&g_d_GameSettings)[0x10] == 0) {
                fn_800625A4(0, 0x11);
            } else {
                *e = 2;
            }
        }
    }
}

// fn_2_7F030, size:0x28C
void fn_2_7F030(MenuTask* o, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    s32 n;
    s32 k;
    s32 v0 = lbl_2_bss_F468.cursor[index];
    s32 v1 = lbl_2_bss_F468.prevCursor[index];
    s32 j;
    s32 f0;
    s32 f1;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 1) ? 1 : 0) {
        n = 0;
        k = 0;
        for (j = 0; j < 9; j++) {
            s32 t = (s8)lbl_803C6724[index * 9 + j + 0x14];
            if (t == v0) {
                f0 = j;
            }
            if (t == v1) {
                f1 = j;
            }
        }
        if (v0 == v1) {
            k++;
            n += fn_80042DA8(o, v0 + 0x34 + index * 9, 0) != 0;
        } else if ((s8)(lbl_803C6724 + index * 9)[f0 + 2] != -1 && (s8)(lbl_803C6724 + index * 9)[f0 + 2] != 0x36) {
            k++;
            n += fn_80042DA8(o, v0 + 0x34 + index * 9, 0xA) != 0;
        }
        if (lbl_8034E9A0.captain[index] == (s8)(lbl_803C6724 + index * 9)[f1 + 2]) {
            k++;
            n += fn_80042DA8(o, v1 + 0x34 + index * 9, 0x14) != 0;
        }
        if (CheckRowHits(o, index * 5, *(u8*)&lbl_8034E9A0.teamRating[index]) && n == k) {
            if (v0 == v1) {
                MENU_SLOT_OBJ(lbl_80371C30, 0x34 + o->baseIdx + v0 + index * 9)->flags &= ~2;
            }
            fn_80062674(index);
            *e = 2;
        }
    }
}

extern void fn_2_102C8(u8 a);

// fn_2_7912C, size:0x268
void fn_2_7912C(MenuTask* o, s32 index) {
    s32 j;
    u8* e;
    s32 n;
    s32 k;
    e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        if (lbl_803C66B0.steps[0][0] == 2) {
            for (j = 1; j < 9; j++) {
                if ((s8)(lbl_803C6724 + index * 9)[(s8)lbl_803C6724[index * 9 + j + 0x14] + 2] != -1 && (s8)(lbl_803C6724 + index * 9)[(s8)lbl_803C6724[index * 9 + j + 0x14] + 2] != 0x36) {
                    MENU_SLOT_OBJ(lbl_80371C30, 0x34 + o->baseIdx + j + index * 9)->_68 = 4;
                }
            }
            fn_2_75BE4(o, index);
        }
        fn_800626EC(index);
        *e = 1;
    }
    if (*e != 1) {
        return;
    }
    n = 0;
    k = 0;
    for (j = 1; j < 9; j++) {
        if ((s8)(lbl_803C6724 + index * 9)[(s8)lbl_803C6724[index * 9 + j + 0x14] + 2] != -1 && (s8)(lbl_803C6724 + index * 9)[(s8)lbl_803C6724[index * 9 + j + 0x14] + 2] != 0x36) {
            k++;
            n += fn_80042DA8(o, j + 0x34 + index * 9, 0) != 0;
        }
    }
    if ((lbl_803C66B0.steps[0][0] != 2 || CheckRowHits(o, index * 5, *(u8*)&lbl_8034E9A0.teamRating[index])) && n == k) {
        u8* p;
        fn_80062674(index);
        *e = 2;
        p = (u8*)&lbl_2_bss_F468 + index;
        if (*(p += offsetof(MenuTeamSel, _43[0])) != 0) {
            fn_2_102C8(index);
            *p = 0;
        }
    }
}

// fn_2_7A748, size:0x290
void fn_2_7A748(MenuTask* o, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 1) ? 1 : 0) {
        s32 n;
        n = 0;
        n += fn_80042DA8(o, index, 0) != 0;
        n += fn_80042DA8(o, index + 2, 0) != 0;
        n += fn_80042DA8(o, index + 0x85, 0) != 0;
        n += fn_80042DA8(o, index + 0x6A, 0) != 0;
        if (n == 4) {
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + index)->_64 = 0x47;
        MENU_SLOT_OBJ(lbl_80371C30, 2 + o->baseIdx + index)->_64 = 0x47;
        MENU_SLOT_OBJ(lbl_80371C30, 151 + o->baseIdx + index)->_64 = 0x78;
        MENU_SLOT_OBJ(lbl_80371C30, 153 + o->baseIdx + index)->_64 = 0x79;
        (&lbl_80371C30[28])[o->baseIdx].obj->flags &= ~2;
        (&lbl_80371C30[29])[o->baseIdx].obj->flags &= ~2;
        (&lbl_80371C30[30])[o->baseIdx].obj->flags &= ~2;
        (&lbl_80371C30[31])[o->baseIdx].obj->flags &= ~2;
        (&lbl_80371C30[120])[o->baseIdx].obj->flags |= 2;
        (&lbl_80371C30[121])[o->baseIdx].obj->flags |= 2;
        (&lbl_80371C30[124])[o->baseIdx].obj->flags |= 2;
        (&lbl_80371C30[125])[o->baseIdx].obj->flags |= 2;
        (&lbl_80371C30[128])[o->baseIdx].obj->flags |= 2;
        (&lbl_80371C30[129])[o->baseIdx].obj->flags |= 2;
        (&lbl_80371C30[15])[o->baseIdx].obj->_68 = 0;
            fn_80062674(index);
            *e = 2;
        }
    }
}

// fn_2_7D85C, size:0x25C
void fn_2_7D85C(MenuTask* o, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    s32 n;
    s32 k;
    s32 j;
    s32 f0;
    s32 v1;
    s32 v0;
    s32 f1;
    if (*(e += offsetof(TutorialSteps, steps[2][1])) == 1) {
        v1 = lbl_2_bss_F468.prevCursor[index];
        v0 = lbl_2_bss_F468.cursor[index];
        n = 0;
        k = 0;
        for (j = 0; j < 9; j++) {
            s32 t = (s8)lbl_803C6724[index * 9 + j + 0x14];
            if (t == v0) {
                f0 = j;
            }
            if (t == v1) {
                f1 = j;
            }
        }
        if (v1 != 9 && v1 != 10 && v1 < 9 && (s8)(lbl_803C6724 + index * 9)[f1 + 2] != -1 && (s8)(lbl_803C6724 + index * 9)[f1 + 2] != 0x36 && v1 != *(s8*)&lbl_2_bss_F468._61[index] && v1 != v0) {
            k++;
            n += fn_80042DA8(o, v1 + 0x34 + index * 9, 0x14) != 0;
        }
        if (v0 != 9 && v0 != 10 && v0 < 9 && (s8)(lbl_803C6724 + index * 9)[f0 + 2] != -1 && (s8)(lbl_803C6724 + index * 9)[f0 + 2] != 0x36 && v0 != *(s8*)&lbl_2_bss_F468._61[index]) {
            k++;
            n += fn_80042DA8(o, v0 + 0x34 + index * 9, 0xA) != 0;
        }
        if (n == k) {
            u8* p;
            lbl_2_bss_F468.prevCursor[index] = lbl_2_bss_F468.cursor[index];
            fn_80062674(index);
            *e = 2;
            p = (u8*)&lbl_2_bss_F468 + index;
            if (*(p += offsetof(MenuTeamSel, _63[0])) != 0) {
                *p = 0;
                fn_800625A4(index, 0x1A);
            }
        }
    }
}

// fn_2_79CF8, size:0x2B4
void fn_2_79CF8(MenuTask* o, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        s8 v0;
        s8 v1;
        s8 found;
        s32 j;
        v0 = lbl_2_bss_F468.cursor[index];
        v1 = lbl_2_bss_F468.prevCursor[index];
        for (j = 0; j < 9; j++) {
            if (v0 == (s8)lbl_803C6724[index * 9 + j + 0x14]) {
                found = j;
                break;
            }
        }
        if (v1 == 9) {
            MENU_SLOT_OBJ(lbl_80371C30, 0x95 + o->baseIdx + index)->_5C = 0xA0000;
            MENU_SLOT_OBJ(lbl_80371C30, 0x95 + o->baseIdx + index)->_68 = 4;
        } else if (v1 == 10) {
            MENU_SLOT_OBJ(lbl_80371C30, 0x91 + o->baseIdx + index)->_5C = 0xA0000;
            MENU_SLOT_OBJ(lbl_80371C30, 0x91 + o->baseIdx + index)->_68 = 4;
        }
        MENU_SLOT_OBJ(lbl_80371C30, 0x46 + o->baseIdx + v0 + index * 9)->_5C = 0;
        MENU_SLOT_OBJ(lbl_80371C30, 0x46 + o->baseIdx + v0 + index * 9)->_68 = 1;
        if ((s8)(lbl_803C6724 + index * 9)[found + 2] != -1) {
            MENU_SLOT_OBJ(lbl_80371C30, 0x34 + o->baseIdx + v0 + index * 9)->_5C = 0x140000;
            MENU_SLOT_OBJ(lbl_80371C30, 0x34 + o->baseIdx + v0 + index * 9)->_68 = 4;
        }
        fn_800626EC(index);
        *e = 1;
    }
}

// fn_2_79394, size:0x2A0
void fn_2_79394(MenuTask* o, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    s32 n;
    s32 k;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        if (lbl_2_bss_F468.cursor[index] == 9) {
            MENU_SLOT_OBJ(lbl_80371C30, 0x95 + o->baseIdx + index)->_5C = 0;
            MENU_SLOT_OBJ(lbl_80371C30, 0x95 + o->baseIdx + index)->_68 = 1;
            MENU_SLOT_OBJ(lbl_80371C30, 0x91 + o->baseIdx + index)->_5C = 0xA0000;
            MENU_SLOT_OBJ(lbl_80371C30, 0x91 + o->baseIdx + index)->_68 = 4;
        } else if (lbl_2_bss_F468.cursor[index] == 10) {
            MENU_SLOT_OBJ(lbl_80371C30, 0x95 + o->baseIdx + index)->_5C = 0xA0000;
            MENU_SLOT_OBJ(lbl_80371C30, 0x95 + o->baseIdx + index)->_68 = 4;
            MENU_SLOT_OBJ(lbl_80371C30, 0x91 + o->baseIdx + index)->_5C = 0;
            MENU_SLOT_OBJ(lbl_80371C30, 0x91 + o->baseIdx + index)->_68 = 1;
        }
        fn_800626EC(index);
        *e = 1;
    }
    if (*e == 1) {
        n = 0;
        k = 0;
        if (lbl_2_bss_F468.cursor[index] == 9) {
            k++;
            n += (MENU_SLOT_OBJ(lbl_80371C30, 0x95 + o->baseIdx + index)->_5C >> 16) >= 10;
            k++;
            n += (MENU_SLOT_OBJ(lbl_80371C30, 0x91 + o->baseIdx + index)->_5C >> 16) == 0;
        } else if (lbl_2_bss_F468.cursor[index] == 10) {
            k++;
            n += (MENU_SLOT_OBJ(lbl_80371C30, 0x95 + o->baseIdx + index)->_5C >> 16) == 0;
            k++;
            n += (MENU_SLOT_OBJ(lbl_80371C30, 0x91 + o->baseIdx + index)->_5C >> 16) >= 10;
        }
        if (n == k) {
            lbl_2_bss_F468.prevCursor[index] = lbl_2_bss_F468.cursor[index];
            fn_80062674(index);
            *e = 2;
        }
    }
}

// fn_2_7A194, size:0x2CC
void fn_2_7A194(MenuTask* o, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        s32 v;
        s8 found;
        s32 j;
        v = lbl_2_bss_F468.prevCursor[index];
        for (j = 0; j < 9; j++) {
            s32 t = (s8)lbl_803C6724[index * 9 + j + 0x14];
            if (t == v) {
                found = j;
                break;
            }
        }
        MENU_SLOT_OBJ(lbl_80371C30, 147 + o->baseIdx + index)->_5C = 0;
        MENU_SLOT_OBJ(lbl_80371C30, 147 + o->baseIdx + index)->_68 = 1;
        MENU_SLOT_OBJ(lbl_80371C30, 149 + o->baseIdx + index)->_5C = 0;
        MENU_SLOT_OBJ(lbl_80371C30, 149 + o->baseIdx + index)->_68 = 1;
        if (v == 10) {
            MENU_SLOT_OBJ(lbl_80371C30, 145 + o->baseIdx + index)->_5C = 0xA0000;
            MENU_SLOT_OBJ(lbl_80371C30, 145 + o->baseIdx + index)->_68 = 4;
        } else if (v != 9) {
            MENU_SLOT_OBJ(lbl_80371C30, 70 + o->baseIdx + v + index * 9)->_5C = 0xF0000;
            MENU_SLOT_OBJ(lbl_80371C30, 70 + o->baseIdx + v + index * 9)->_68 = 4;
            if ((s8)(lbl_803C6724 + index * 9)[found + 2] != -1 && (s8)(lbl_803C6724 + index * 9)[found + 2] != 0x36) {
                MENU_SLOT_OBJ(lbl_80371C30, 52 + o->baseIdx + v + index * 9)->_5C = 0xA0000;
                MENU_SLOT_OBJ(lbl_80371C30, 52 + o->baseIdx + v + index * 9)->_68 = 1;
            }
        }
        fn_800626EC(index);
        *e = 1;
    }
}

// fn_2_7A9D8, size:0x28C
void fn_2_7A9D8(MenuTask* o, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + index)->_5C = 0x140000;
        MENU_SLOT_OBJ(lbl_80371C30, 0x2 + o->baseIdx + index)->_5C = 0x140000;
        MENU_SLOT_OBJ(lbl_80371C30, o->baseIdx + index)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 0x2 + o->baseIdx + index)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 0x4 + o->baseIdx + index)->_5C = 0x1E0000;
        MENU_SLOT_OBJ(lbl_80371C30, 0x4 + o->baseIdx + index)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 0x85 + o->baseIdx + index)->_5C = 0xA0000;
        MENU_SLOT_OBJ(lbl_80371C30, 0x85 + o->baseIdx + index)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 0x89 + o->baseIdx + index)->_5C = 0x50000;
        MENU_SLOT_OBJ(lbl_80371C30, 0x89 + o->baseIdx + index)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 0x6a + o->baseIdx + index)->_5C = 0xA0000;
        MENU_SLOT_OBJ(lbl_80371C30, 0x6a + o->baseIdx + index)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 0x34 + o->baseIdx + index)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 0x93 + o->baseIdx + index)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 0x8f + o->baseIdx + index)->_68 = 4;
        MENU_SLOT_OBJ(lbl_80371C30, 0xb2 + o->baseIdx + index)->flags &= ~2;
        MENU_SLOT_OBJ(lbl_80371C30, 0xae + o->baseIdx + index)->flags &= ~2;
        MENU_SLOT_OBJ(lbl_80371C30, 0x97 + o->baseIdx + index)->flags &= ~2;
        MENU_SLOT_OBJ(lbl_80371C30, 0xac + o->baseIdx + index)->flags &= ~2;
        MENU_SLOT_OBJ(lbl_80371C30, 0xc + o->baseIdx + index)->flags &= ~2;
        MENU_SLOT_OBJ(lbl_80371C30, 0x12 + o->baseIdx + index)->flags &= ~2;
        fn_800626EC(index);
        *e = 1;
    }
}

extern void* memset(void* dst, int c, size_t n);

// fn_2_76650, size:0x224
void fn_2_76650(MenuTask* o, u8 k, u32 mask) {
    s32 buf[2];
    s32 i;
    s32 n;
    memset(buf, -1, 2);
    for (i = 0, n = 0; i < 14; i++) {
        if (mask & (1 << i)) {
            switch (i) {
                case 0:
                    i++;
                    break;
                case 1:
                    buf[n++] = 1;
                    break;
                case 2:
                    buf[n++] = 2;
                    break;
                case 3:
                    buf[n++] = 3;
                    break;
                case 4:
                    buf[n++] = 4;
                    break;
                case 5:
                    buf[n++] = 5;
                    break;
                case 6:
                    buf[n++] = 6;
                    break;
                case 7:
                    buf[n++] = 7;
                    break;
                case 8:
                    buf[n++] = 8;
                    break;
                case 9:
                    buf[n++] = 9;
                    break;
                case 10:
                    buf[n++] = 10;
                    break;
                case 11:
                    buf[n++] = 11;
                    break;
                case 12:
                    buf[n++] = 12;
                    break;
                default:
                    buf[n++] = 13;
                    break;
            }
        }
    }
    buf[0]--;
    buf[1]--;
    for (i = 0; i < 2; i++) {
        if (buf[i] < 0) {
            buf[i] = 12;
        }
    }
    MENU_SLOT_OBJ(lbl_80371C30, 0xCE + o->baseIdx + k)->_5C = buf[0] << 16;
    MENU_SLOT_OBJ(lbl_80371C30, 0xD0 + o->baseIdx + k)->_5C = buf[1] << 16;
}


// fn_2_73CBC, size:0x240
void fn_2_73CBC(MenuTask* o) {
    s32 i;
    s32 n;
    s32 k;
    s32 mode;
    s32 t;
    mode = lbl_2_bss_F410._00;
    if ((lbl_803C66B0.steps[1][1] == 1) ? 1 : 0) {
        n = 0;
        k = 0;
        if (lbl_8034E9A0._4751 == 0) {
            for (i = 0; i < 7; i++) {
                t = fn_2_73B94(mode);
                if (lbl_2_bss_F410._00 == i) {
                    k++;
                    n += fn_80042DA8(o, i + 3, t) != 0;
                }
                if (lbl_2_bss_A840 == 0 && mode == 6 && i == lbl_2_bss_A840) {
                    k++;
                    n += fn_80042DA8(o, i + 3, 0) != 0;
                } else if (lbl_2_bss_A840 == 6 && mode == 0 && i == lbl_2_bss_A840) {
                    k++;
                    n += fn_80042DA8(o, i + 3, 0x36) != 0;
                }
            }
            k++;
            n += fn_80042DA8(o, mode + 0x11, 0xE) != 0;
            k++;
            n += fn_80042DA8(o, 0x20, 0xA) != 0;
        }
        if (n == k) {
            if (lbl_8034E9A0._4751 != 0) {
                lbl_2_bss_A844 = lbl_2_bss_A840;
            }
            lbl_2_bss_A840 = mode;
            lbl_8034E9A0._4752 = 0;
            if (lbl_8034E9A0._4751 == 0) {
                fn_80062674(0);
            }
            lbl_803C66B0.steps[1][1] = 2;
            fn_800625A4(0, 0x57);
        }
    }
}

// fn_2_7302C, size:0x60
// NONMATCHING 70%: CW turns the search loop into a ctr loop; original keeps cmpw/blt
#if NONMATCHING
s32 fn_2_7302C(void) {
    u8 n = lbl_80361B20._F4;
    u8* p = lbl_800FE930 + n * 6;
    s32 i;
    for (i = 0; i < (n != 0) + 5; i++) {
        if (lbl_8034E9A0.captain[0] == *p) {
            break;
        }
        p++;
    }
    return i;
}
#endif

extern void fn_80051D00(void);

// lbl_8034E978 is the MenuState, lbl_800FEF70 the MenuDef table (main/file_800527C4.h).
static inline void SetMenu(s32 menu) {
    lbl_8034E978.menu = menu;
    lbl_8034E978.prevTrack = lbl_8034E978.track;
    lbl_8034E978.track = lbl_800FEF70[menu].track;
}

// fn_2_7265C, size:0x1B8
void fn_2_7265C(void) {
    s32 i;
    s32 menu;
    s32 found = 0;
    if (g_d_GameSettings.GameModeSelected == 5 && lbl_803C5EA4._11 == 0) {
        lbl_803C5EA4._11 = 1;
        fn_800B0A5C_insertQueue((void*)fn_80053FE8, 0x3000);
        fn_800B0A5C_insertQueue((void*)fn_2_82DE8, 0x3000);
    }
    for (i = 0; i < 54; i++) {
        if (lbl_80361B20._00[i] != 0) {
            found = 1;
            break;
        }
    }
    if (g_d_GameSettings.GameModeSelected != 5) {
        if (found) {
            menu = 2;
        } else {
            menu = 1;
        }
    } else {
        menu = 0x13;
    }
    SetMenu(menu);
    fn_800B0A5C_insertQueue((void*)fn_80051D00, 0x3000);
}


#define MN_SLOTS (lbl_80371C30)
#define BASE(o) ((o)->baseIdx)
// Write the index constant first (K + BASE(o) + i): CW keeps that order.
#define MN_SLOT(i) (MN_SLOTS[i].obj)

extern u8 lbl_80108EC4[];
extern u8 lbl_2_data_2AF08[];

// Body of fn_2_72E54; also inlined into fn_2_7308C.
static inline void setupHeaderSlots(MenuTask* o) {
    s32 j;
    s32 found = -1;
    u8 v;
    if ((lbl_803CBBC4[2] == 0) ? 1 : 0) {
        LayoutSlot* slots = MN_SLOTS;
        LayoutSlot* next = slots + 1;
        s32 zero = 0;
        u8* tbl = lbl_80108EC4;
        slots[o->baseIdx].obj->_5C = zero;
        slots[o->baseIdx].obj->_68 = 1;
        next[o->baseIdx].obj->_5C = zero;
        next[o->baseIdx].obj->_68 = 1;
        v = lbl_800FE930[lbl_80361B20._F4 * 6 + lbl_2_bss_F410.charSel[0]];
        for (j = 0; j < 6; j++) {
            if (tbl[j] == v) {
                found = j;
                break;
            }
        }
        MN_SLOT(2 + BASE(o))->_5C = lbl_2_data_2AF08[found] << 18;
        v = lbl_800FE5D4[lbl_2_bss_F410.charSel[0]];
        for (j = 0; j < 6; j++) {
            if (tbl[j] == v) {
                break;
            }
        }
        lbl_803CBBC4[2] = 1;
        lbl_803CBBC4[3] = 1;
    }
}

// fn_2_72E54, size:0x1D4
// NONMATCHING 83%: zero kept in r30/slot base in r31 swapped vs ours, search loop uses lbz not lbzu
#if NONMATCHING
void fn_2_72E54(MenuTask* o) {
    setupHeaderSlots(o);
}
#endif

// lbl_803C6724: per-team roster (+2) and field position (+0x14) tables.
typedef struct TeamTbl {
    /*0x00*/ u8 _00[2];
    /*0x02*/ s8 roster[2][9];
    /*0x14*/ s8 pos[2][9];
    /*0x26*/ u8 stat[2][9];
} TeamTbl;

#define TEAM_TBL ((TeamTbl*)lbl_803C6724)

// fn_2_7E194, size:0x1EC
// NONMATCHING 94%: unrolled roster search addresses each entry from the base instead of a walking pointer
#if NONMATCHING
void fn_2_7E194(MenuTask* o, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    s32 n;
    s32 k;
    s8 pos;
    s32 player;
    s32 j;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 1) ? 1 : 0) {
        n = 0;
        k = 0;
        k++;
        n += fn_80042DA8(o, index + 0x1C, 0xA) != 0;
        k++;
        n += fn_80042DA8(o, index + 0x6A, 0xA) != 0;
        k++;
        n += fn_80042DA8(o, index + 0x89, 5) != 0;
        if (g_d_GameSettings._10 == 0 && index == 0) {
            // team 1 roster (+2) / field positions (+0x14), 9 entries each
            {
            TeamTbl* tt = TEAM_TBL;
            player = lbl_8034E9A0.captain[1];
            for (j = 0; j < 9; j++) {
                if (tt->roster[1][j] == player) {
                    pos = tt->pos[1][j];
                }
            }
            }
            k++;
            n += fn_80042DA8(o, pos + 0x3D, 0x14) != 0;
        }
        if (n == k) {
            fn_80062674(index);
            *e = 2;
        }
    }
}
#endif

// Body of fn_2_72A88; also inlined into fn_2_7308C.
static inline void setupHeaderRoster(MenuTask* o) {
    s32 j;
    s32 found = -1;
    u8 v;
    if ((lbl_803CBBC4[2] == 0) ? 1 : 0) {
        v = (lbl_800FE930 + lbl_80361B20._F4 * 6)[lbl_2_bss_F410.charSel[0]];
        for (j = 0; j < 6; j++) {
            if (lbl_80108EC4[j] == v) {
                found = j;
                break;
            }
        }
        MN_SLOT(2 + BASE(o))->_5C = lbl_2_data_2AF08[found] << 18;
        MN_SLOT(3 + BASE(o))->_5C = lbl_2_data_2AF08[found] << 18;
        for (j = 0; j < 8; j++) {
            MN_SLOT(4 + BASE(o) + j)->_5C = TEAM_TBL->roster[0][j + 1] << 16;
        }
        lbl_803CBBC4[2] = 1;
        lbl_803CBBC4[3] = 1;
    }
}

// fn_2_72A88, size:0x22C
// NONMATCHING 94%: character search loop uses lbz instead of the original lbzu walker; register order differs
#if NONMATCHING
void fn_2_72A88(MenuTask* o) {
    setupHeaderRoster(o);
}
#endif

// fn_2_7F8BC, size:0x240
void fn_2_7F8BC(MenuTask* o, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        s8 v;
        s8 found;
        s32 j;
        s32 x;
        v = lbl_2_bss_F468.cursor[index];
        for (j = 0; j < 9; j++) {
            s8 t = lbl_803C6724[index * 9 + j + 0x14];
            if (t == v) {
                found = j;
                break;
            }
        }
        x = ((s8*)lbl_803C6724 + index * 9)[found + 2];
        MN_SLOT(0x34 + BASE(o) + v + index * 9)->flags |= 2;
        MN_SLOT(0x34 + BASE(o) + v + index * 9)->_5C = 0;
        MN_SLOT(0x34 + BASE(o) + v + index * 9)->_68 = 1;
        MN_SLOT(0x58 + BASE(o) + v + index * 9)->_5C = x << 16;
        fn_2_75BE4(o, index);
        fn_2_74F40(o, index);
        fn_800626EC(index);
        *e = 1;
    }
}

// fn_2_808D8, size:0x284
// NONMATCHING 85%: original hoists the five slot pointers (base+0x78..0x8B) into registers before the stores; frame/stack layout differs
#if NONMATCHING
void fn_2_808D8(MenuTask* o, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        if (g_d_GameSettings.GameModeSelected != 5) {
            fn_2_7630C(o, index);
        } else {
            u8* chars = lbl_800FE930 + lbl_80361B20._F4 * 6;
            s32 a = chars[lbl_2_bss_F410.charSel[0]];
            s32 b = chars[lbl_803C6724[0]];
            u8 x = lbl_8034E9A0.roster[a / 9][a % 9].stats.CaptainStarHitPitch;
            u8 y = lbl_8034E9A0.roster[b / 9][b % 9].stats.CaptainStarHitPitch;
            MN_SLOT(0x82 + BASE(o))->_5C = lbl_2_data_2B3A4[x] << 16;
            fn_800363D8(o, 0x89, 1, 3, lbl_2_data_2B3A4[x]);
            fn_800363D8(o, 0x8B, 1, 3, lbl_2_data_2B3A4[y]);
            MN_SLOT(0x7E + BASE(o))->_5C = lbl_2_data_2B3A4[x] << 16;
            MN_SLOT(0x80 + BASE(o))->_5C = 0;
            MN_SLOT(0x89 + BASE(o))->_5C = 0;
            MN_SLOT(0x8B + BASE(o))->_5C = 0xA0000;
            MN_SLOT(0x78 + BASE(o))->_5C = 0;
            MN_SLOT(0x7C + BASE(o))->_5C = 0;
            MN_SLOT(0x80 + BASE(o))->_68 = 1;
            MN_SLOT(0x89 + BASE(o))->_68 = 1;
            MN_SLOT(0x8B + BASE(o))->_68 = 4;
            MN_SLOT(0x78 + BASE(o))->_68 = 1;
            MN_SLOT(0x7C + BASE(o))->_68 = 1;
        }
        fn_2_74F40(o, index);
        fn_800626EC(index);
        *e = 1;
    }
}
#endif

// fn_2_7805C, size:0x310
// NONMATCHING 88%: original re-extsb's the prev byte at each use; CW CSEs our (s8) cast
#if NONMATCHING
void fn_2_7805C(MenuTask* o, s32 index) {
    u8* sel = (u8*)&lbl_2_bss_F468 + index;
    u8 prev = *(sel += offsetof(MenuTeamSel, _61[0])); // F468[0x61 + index]
    s8 found;
    s32 j;
    s32 n;
    s32 k;
    u8* e;
    for (j = 0; j < 9; j++) {
        if ((s8)lbl_803C6724[index * 9 + j + 0x14] == (s8)prev) {
            found = j;
        }
    }
    e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        if ((s8)prev != lbl_2_bss_F468.cursor[index]) {
            MN_SLOT(0x46 + BASE(o) + (s8)prev + index * 9)->_68 = 4;
            if ((s8)(lbl_803C6724 + index * 9)[found + 2] != -1 && (s8)(lbl_803C6724 + index * 9)[found + 2] != 0x36) {
                MN_SLOT(0x34 + BASE(o) + (s8)prev + index * 9)->_68 = 1;
            }
        }
        if (lbl_2_bss_F468._37[index] != 0) {
            MN_SLOT(0x93 + BASE(o) + index)->_64 = 9;
            MN_SLOT(0x93 + BASE(o) + index)->_5C = 0xA0000;
            MN_SLOT(0x93 + BASE(o) + index)->_68 = 0;
        }
        fn_800626EC(index);
        *e = 1;
    }
    if (*e == 1) {
        n = 0;
        k = 0;
        if ((s8)*sel != lbl_2_bss_F468.cursor[index]) {
            if ((s8)(lbl_803C6724 + index * 9)[found + 2] != -1 && (s8)(lbl_803C6724 + index * 9)[found + 2] != 0x36) {
                k++;
                n += fn_80042DA8(o, (s8)prev + index * 9 + 0x34, 0x14) != 0;
            }
        }
        if (n == k) {
            lbl_2_bss_F468._5F[index] = 0;
            *sel = -1;
            fn_80062674(index);
            *e = 2;
        }
    }
}
#endif

// fn_2_7630C, size:0x340
// NONMATCHING 97%: registers only (team byte in r7 vs r6, a/b swapped r0/r3)
#if NONMATCHING
void fn_2_7630C(MenuTask* o, u8 index) {
    u8 team;
    s32 a;
    s32 b;
    u8 x;
    u8 y;
    if (g_d_GameSettings._10 == 0) {
        team = lbl_803C66B0.portOf[0];
    } else {
        team = lbl_803C66B0.portOf[index];
    }
    a = lbl_800FE5D4[lbl_2_bss_F410.charSel[team]];
    b = lbl_803C6724[team];
    b = lbl_800FE5D4[b];
    x = lbl_8034E9A0.roster[a / 9][a % 9].stats.CaptainStarHitPitch;
    y = lbl_8034E9A0.roster[b / 9][b % 9].stats.CaptainStarHitPitch;
    MN_SLOT(0x82 + BASE(o) + team)->_5C = lbl_2_data_2B3A4[x] << 16;
    MN_SLOT(0x85 + BASE(o) + team)->_5C = 0xA0000;
    MN_SLOT(0x87 + BASE(o) + team)->_5C = 0xA0000;
    MN_SLOT(0x85 + BASE(o) + team)->_68 = 0;
    MN_SLOT(0x87 + BASE(o) + team)->_68 = 0;
    fn_800363D8(o, team + 0x89, 1, 3, lbl_2_data_2B3A4[x]);
    fn_800363D8(o, team + 0x8B, 1, 3, lbl_2_data_2B3A4[y]);
    MN_SLOT(0x7E + BASE(o) + team)->_5C = lbl_2_data_2B3A4[x] << 16;
    MN_SLOT(0x1A + BASE(o) + team)->flags |= 2;
    MN_SLOT(0x1A + BASE(o) + team)->_68 = 1;
    MN_SLOT(0x80 + BASE(o) + team)->_5C = 0;
    MN_SLOT(0x89 + BASE(o) + team)->_5C = 0;
    MN_SLOT(0x8B + BASE(o) + team)->_5C = 0xA0000;
    MN_SLOT(0x78 + BASE(o) + team)->_5C = 0;
    MN_SLOT(0x7C + BASE(o) + team)->_5C = 0;
    MN_SLOT(0x80 + BASE(o) + team)->_68 = 1;
    MN_SLOT(0x89 + BASE(o) + team)->_68 = 1;
    MN_SLOT(0x8B + BASE(o) + team)->_68 = 4;
    MN_SLOT(0x78 + BASE(o) + team)->_68 = 1;
    MN_SLOT(0x7C + BASE(o) + team)->_68 = 1;
}
#endif


// fn_2_7F2BC, size:0x458
void fn_2_7F2BC(MenuTask* o, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        s32 fc;
        s32 sel;
        s32 cur;
        s32 j;
        s32 fs;
        sel = lbl_2_bss_F468.cursor[index];
        cur = lbl_2_bss_F468.prevCursor[index];
        for (j = 0; j < 9; j++) {
            s8 t = lbl_803C6724[index * 9 + j + 0x14];
            if (t == sel) {
                fs = j;
            }
            if (t == cur) {
                fc = j;
            }
        }
        if (sel != 9 && sel != 10) {
            if ((s8)(lbl_803C6724 + index * 9)[fs + 2] != -1 && (s8)(lbl_803C6724 + index * 9)[fs + 2] != 0x36) {
                MN_SLOT(0x34 + BASE(o) + sel + index * 9)->_5C = 0;
                MN_SLOT(0x34 + BASE(o) + sel + index * 9)->_68 = 1;
            }
            MN_SLOT(0x46 + BASE(o) + sel + index * 9)->_5C = 0;
            MN_SLOT(0x46 + BASE(o) + sel + index * 9)->_68 = 1;
            MN_SLOT(0x22 + BASE(o) + sel + index * 9)->flags |= 2;
        }
        if (cur != 9 && cur != 10) {
            if (lbl_2_bss_F468.prevCursor[index] != lbl_2_bss_F468.cursor[index]) {
                MN_SLOT(0x46 + BASE(o) + cur + index * 9)->_5C = 0xF0000;
                MN_SLOT(0x46 + BASE(o) + cur + index * 9)->_68 = 4;
                if (lbl_8034E9A0.captain[index] == (s8)(lbl_803C6724 + index * 9)[fc + 2]) {
                    MN_SLOT(0x34 + BASE(o) + cur + index * 9)->_68 = 1;
                } else {
                    MN_SLOT(0x34 + BASE(o) + cur + index * 9)->_68 = 4;
                }
            }
            MN_SLOT(0x22 + BASE(o) + cur + index * 9)->flags &= ~2;
        }
        fn_2_75BE4(o, index);
        fn_2_74F40(o, index);
        if ((MN_SLOT(0x93 + BASE(o) + index)->_5C >> 16) == 10 &&
            lbl_8034E9A0.captain[index] != (s8)(lbl_803C6724 + index * 9)[fc + 2]) {
            MN_SLOT(0x93 + BASE(o) + index)->_5C = 0xA0000;
            MN_SLOT(0x93 + BASE(o) + index)->_68 = 4;
            MN_SLOT(0x95 + BASE(o) + index)->_5C = 0xA0000;
            MN_SLOT(0x95 + BASE(o) + index)->_68 = 4;
        } else if ((MN_SLOT(0x8F + BASE(o) + index)->_5C >> 16) == 10 && sel == 10) {
            MN_SLOT(0x91 + BASE(o) + index)->_5C = 0xA0000;
            MN_SLOT(0x91 + BASE(o) + index)->_68 = 4;
        }
        if (sel == cur) {
            MN_SLOT(0x34 + BASE(o) + sel + index * 9)->_68 = 4;
        }
        fn_800626EC(index);
        *e = 1;
    }
}

// fn_2_75BE4, size:0x4B4
// Average a stat over the team's non-captain players and show it as 0-5 stars.
// NONMATCHING 85%: stars kept in a different register (extsb. vs cmpwi), register allocation
#if NONMATCHING
void fn_2_75BE4(MenuTask* o, s32 index) {
    s32 sum = 0;
    s32 avg = 0;
    s32 count = 0;
    s8 stars = 0;
    s32 j;
    for (j = 0; j < 9; j++) {
        u8 v = TEAM_TBL->stat[index][j];
        if (v != 0 && TEAM_TBL->roster[index][j] != lbl_8034E9A0.captain[index]) {
            sum += v;
            count++;
        }
    }
    if (count != 0) {
        avg = sum / count;
    }
    if (avg >= 70) {
        stars = 5;
    } else if (avg <= 69 && avg >= 55) {
        stars = 4;
    } else if (avg <= 54 && avg >= 35) {
        stars = 3;
    } else if (avg <= 34 && avg >= 15) {
        stars = 2;
    } else if (avg <= 14 && avg > 0) {
        stars = 1;
    }
    lbl_8034E9A0.teamRating[index] = stars;
    for (j = 0; j < 5; j++) {
        LayoutObj* star = MN_SLOT(0x6E + BASE(o) + j + index * 5);
        if ((star->_5C >> 16) == 30) {
            star->_68 = 1;
        }
    }
    for (j = 0; j < stars; j++) {
        MN_SLOT(0x6E + BASE(o) + j + index * 5)->_5C = 0;
        MN_SLOT(0x6E + BASE(o) + j + index * 5)->_68 = 1;
    }
}
#endif

// fn_2_78AC0, size:0x4B8
// NONMATCHING 85%: prev byte kept raw and re-extended in the original; register allocation
#if NONMATCHING
void fn_2_78AC0(MenuTask* o, s32 index) {
    u8* sel = (u8*)&lbl_2_bss_F468 + index;
    s8 prev = sel[offsetof(MenuTeamSel, _61[0])];
    s32 cur = lbl_2_bss_F468.cursor[index];
    s8 found;
    s32 j;
    s32 n;
    s32 k;
    u8* e;
    u8* flag;
    if (prev != -1) {
        for (j = 0; j < 9; j++) {
            if (TEAM_TBL->pos[index][j] == prev) {
                found = j;
            }
        }
    }
    e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        MN_SLOT(0xA + BASE(o) + index)->_5C = 0xF0000;
        MN_SLOT(0xA + BASE(o) + index)->_68 = 4;
        MN_SLOT(0x1E + BASE(o) + index)->_68 = 4;
        MN_SLOT(0x93 + BASE(o) + index)->_64 = 9;
        MN_SLOT(0x89 + BASE(o) + index)->_5C = 0;
        MN_SLOT(0x89 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x8D + BASE(o) + index)->_5C = 0x140000;
        MN_SLOT(0x8D + BASE(o) + index)->_68 = 4;
        MN_SLOT(0x6A + BASE(o) + index)->_68 = 1;
        if (g_d_GameSettings.GameModeSelected != 5) {
            MN_SLOT(0x8F + BASE(o) + index)->_64 = 7;
        }
        if (prev != -1 && prev != (s8)cur) {
            MN_SLOT(0x46 + BASE(o) + prev + index * 9)->_68 = 4;
            if (TEAM_TBL->roster[index][found] != -1 && TEAM_TBL->roster[index][found] != 0x36) {
                MN_SLOT(0x34 + BASE(o) + prev + index * 9)->_5C = 0xA0000;
                MN_SLOT(0x34 + BASE(o) + prev + index * 9)->_68 = 1;
            }
        }
        fn_800626EC(index);
        *e = 1;
    }
    if (*e == 1) {
        n = fn_80042DA8(o, index + 0x89, 5) != 0;
        k = 2;
        n += fn_80042DA8(o, index + 0x6A, 0xA) != 0;
        if (prev != -1 && lbl_2_bss_F468._56 == 0 && prev != (s8)cur) {
            if (TEAM_TBL->roster[index][found] != -1 && TEAM_TBL->roster[index][found] != 0x36) {
                k = 3;
                n += fn_80042DA8(o, prev + index * 9 + 0x34, 0x14) != 0;
            }
        }
        if (n == k) {
            sel[offsetof(MenuTeamSel, _61[0])] = -1;
            fn_80062674(index);
            *e = 2;
            flag = (u8*)&lbl_2_bss_F468 + index;
            if (*(flag += offsetof(MenuTeamSel, _65[0])) != 0) {
                if (g_d_GameSettings.GameModeSelected == 5) {
                    fn_800625A4(0, 0x13);
                    fn_800625A4(1, 0x13);
                } else if (g_d_GameSettings._10 == 0) {
                    fn_800625A4(index, 0x11);
                } else {
                    fn_800625A4(index, 0x11);
                }
                *flag = 0;
                return;
            }
            if (lbl_2_bss_F468._56 != 0) {
                fn_800625A4(index, 0xB);
            }
        }
    }
}
#endif

#ifdef TARGET_PC
s32 port_menu_row(s32 entry);
s32 port_stadium_select_enabled(void);
// Main menu without the modes the port doesn't offer (port/game/menu_scope.c):
// their buttons are hidden and the ones below move up. The rows are placed by
// the sprites' animations (base position 0), so moving one is a base offset.
static MenuTask* sPortMainMenuTask; // the main-menu layout task while it is up
static s32 sPortCareerRows;          // > 0: the layout is the Career menu's, with this many rows

// Career menu (port/game/career.c): the main menu's own layout (background, button plates and
// their word pictures, the orange plate of the highlighted row); career.c swaps the word
// pictures. The mode descriptions are kept running but drawn transparent: the highlight steps
// wait on their animations, and hidden sprites don't animate.
static void port_career_menu_layout(MenuTask* o) {
    s32 i;
    for (i = 0; i < 7; i++) {
        LayoutObj* hl = MN_SLOT(3 + BASE(o) + i);
        LayoutObj* btn = MN_SLOT(0xA + BASE(o) + i);
        LayoutObj* panel = MN_SLOT(0x11 + BASE(o) + i);
        LayoutObj* label = MN_SLOT(0x18 + BASE(o) + i);
        if (btn == NULL || label == NULL || panel == NULL || hl == NULL) {
            continue;
        }
        hl->y = btn->y = panel->y = label->y = 0.0f;
        if (i < sPortCareerRows) {
            btn->flags |= 2;
            label->flags |= 2;
            panel->flags |= 2;
        } else {
            btn->flags &= ~2;
            label->flags &= ~2;
            panel->flags &= ~2;
            hl->flags &= ~2;
        }
    }
    for (i = 0x20; i <= 0x21; i++) {
        if (MN_SLOT(i + BASE(o)) != NULL) {
            MN_SLOT(i + BASE(o))->color &= ~0xFF;
        }
    }
}

static void port_main_menu_layout(MenuTask* o) {
    static const u8 kSlots[] = {3, 0xA, 0x11, 0x18}; // highlight, button, panel, item
    const f32 kRowStep = 46.0f; // distance between two rows
    s32 i;
    s32 k;
    sPortMainMenuTask = o;
    if (sPortCareerRows > 0) {
        port_career_menu_layout(o);
        return;
    }
    for (i = 0; i < 7; i++) {
        s32 row = port_menu_row(i);
        for (k = 0; k < (s32)sizeof(kSlots); k++) {
            LayoutObj* q = MN_SLOT(kSlots[k] + BASE(o) + i);
            if (q == NULL) {
                continue;
            }
            if (row < 0) {
                q->flags &= ~2;
            } else if (kSlots[k] != 0x11) {
                q->y = (f32)(row - i) * kRowStep;
            }
        }
    }
}
#endif

// fn_2_747FC, size:0x4DC
// NONMATCHING 80%: slot base+0x20 not hoisted as in the original; frame size and register allocation differ
#if NONMATCHING
void fn_2_747FC(void) {
    MenuTask* o = lbl_803CC1B8;
    s32 mode = lbl_2_bss_F410._00;
    s32 i;
    s32 n;
    s32 k;
#ifdef TARGET_PC
    port_main_menu_layout(o);
#endif
    if (lbl_8034E9A0._472A == 0) {
#ifdef TARGET_PC
        sPortMainMenuTask = NULL;
        sPortCareerRows = 0;
#endif
        fn_80034CEC(o);
        REMOVE_QUEUE_NOARG();
        lbl_8034E9A0._472A = 0xFF;
        return;
    }
    switch (lbl_803C66B0.step[0]) {
    case 0x54:
        if ((lbl_803C66B0.steps[1][1] == 0) ? 1 : 0) {
            for (i = 0; i < 7; i++) {
                if (mode == i) {
                    MN_SLOT(3 + BASE(o) + i)->flags |= 2;
                    MN_SLOT(3 + BASE(o) + i)->_5C = 0;
                    MN_SLOT(3 + BASE(o) + i)->_68 = 1;
                    MN_SLOT(0x18 + BASE(o) + i)->_5C = 0;
                    MN_SLOT(0x18 + BASE(o) + i)->_68 = 1;
                } else {
                    MN_SLOT(0x18 + BASE(o) + i)->_5C = 0;
                    MN_SLOT(0x18 + BASE(o) + i)->_68 = 0;
                    MN_SLOT(3 + BASE(o) + i)->flags &= ~2;
                }
            }
            if (lbl_8037169C.state != 0) {
                changeScene(1, 6);
            }
            MN_SLOT(0x20 + BASE(o))->_5C = 0;
            MN_SLOT(0x20 + BASE(o))->_68 = 1;
            fn_800626EC(0);
            lbl_803C66B0.steps[1][1] = 1;
        }
        mode = lbl_2_bss_F410._00;
        if (lbl_803C66B0.steps[1][1] == 1) {
            n = 0;
            k = 0;
            for (i = 0; i < 7; i++) {
                if (mode == i) {
                    k++;
                    n += fn_80042DA8(o, i + 3, 0xE) != 0;
                }
            }
            k++;
            n += fn_80042DA8(o, 0x20, 0xA) != 0;
            if (n == k) {
                fn_80062674(0);
                lbl_803C66B0.steps[1][1] = 2;
                fn_800625A4(0, 0x57);
            }
        }
        break;
    case 0x55:
        if ((lbl_803C66B0.steps[1][1] == 0) ? 1 : 0) {
            fn_800626EC(0);
            lbl_803C66B0.steps[1][1] = 1;
        }
        if (lbl_803C66B0.steps[1][1] == 1) {
            fn_80062674(0);
            lbl_803C66B0.steps[1][1] = 2;
        }
        break;
    case 0x56:
        fn_2_73EFC(o);
        fn_2_73CBC(o);
        break;
    case 0x57:
        if ((lbl_803C66B0.steps[1][1] == 0) ? 1 : 0) {
            MN_SLOT(0x11 + BASE(o) + mode)->_5C = 0xE0000;
            MN_SLOT(0x11 + BASE(o) + mode)->_68 = 1;
            lbl_803C66B0.steps[1][1] = 1;
        }
        if (lbl_803C66B0.steps[1][1] == 1) {
            if (lbl_8034E9A0.input[0].held == 0 && lbl_8034E9A0._4751 != 0) {
                lbl_8034E9A0._4752 = 1;
                if (lbl_2_bss_F410._00 != lbl_2_bss_F410._04) {
                    fn_800625A4(0, 0x56);
                }
                lbl_8034E9A0._4751 = 0;
                lbl_2_bss_A840 = lbl_2_bss_A844;
            } else if ((fn_80042DA8(o, mode + 0x11, 0x37) != 0) == 1) {
                MN_SLOT(0x11 + BASE(o) + mode)->_5C = 0xE0000;
                MN_SLOT(0x11 + BASE(o) + mode)->_68 = 1;
            }
        }
        break;
    case 0x58:
        if ((lbl_803C66B0.steps[1][1] == 0) ? 1 : 0) {
            MN_SLOT(0x11 + BASE(o) + mode)->_5C = 0x370000;
            MN_SLOT(0x11 + BASE(o) + mode)->_68 = 1;
            fn_800626EC(0);
            lbl_803C66B0.steps[1][1] = 1;
        }
        if (lbl_803C66B0.steps[1][1] == 1 && (fn_80042DA8(o, mode + 0x11, 0x41) != 0) == 1) {
            fn_80062674(0);
            lbl_803C66B0.steps[1][1] = 2;
        }
        break;
    }
}
#endif

#ifdef TARGET_PC
// --- Career menu on the main menu's layout (port/game/career.c)
// Opens the layout with `rows` rows (1-7) and the cursor on `row`; it plays the main menu's intro.
void port_career_layout_open(s32 rows, s32 row) {
    sPortCareerRows = rows;
    lbl_2_bss_F410._00 = row;
    lbl_2_bss_F410._04 = row;
    lbl_8034E9A0._4751 = 0;
    lbl_8034E9A0._4752 = 0;
    lbl_803C66B0.steps[0][0] = 0;
    memset(&lbl_803C66B0.steps[0][1], 0, 6);
    lbl_8034E9A0._472A = 0xFF;
    fn_2_74D8C();
    fn_800625A4(0, 0x54);
}

// Changes the page in place: a new row count and the cursor on `row`.
void port_career_layout_page(s32 rows, s32 row) {
    s32 prev = lbl_2_bss_F410._00;
    sPortCareerRows = rows;
    if (row != prev) {
        // From a row the new page doesn't have (Create's Complete is row 6; the hub has 4 rows),
        // the move would start on a hidden plate, which never animates: start from the target.
        lbl_2_bss_F410._04 = prev < rows ? prev : row;
        lbl_2_bss_F410._00 = row;
        lbl_803C66B0.steps[1][1] = 0;
        fn_800625A4(0, 0x56);
    }
}

// Moves the highlight to `row`, as the main menu's own cursor does (fn_2_1800).
void port_career_layout_move(s32 row) {
    lbl_2_bss_F410._04 = lbl_2_bss_F410._00;
    lbl_2_bss_F410._00 = row;
    fn_800625A4(0, 0x56);
}

// Frees the layout (the task removes itself on its next frame).
void port_career_layout_close(void) {
    if (sPortMainMenuTask != NULL) {
        lbl_8034E9A0._472A = 0; // the Career rows stay until the task is gone (no main-menu frame)
    } else {
        sPortCareerRows = 0;
    }
}

s32 port_career_layout_up(void) {
    return sPortMainMenuTask != NULL;
}

// The layout's busy flag: input waits while the highlight animates.
s32 port_career_layout_busy(void) {
    return lbl_803C66B0.active[0] != 0;
}

// The busy flag stuck (an animation step that never reports done): clear it. Returns the step.
s32 port_career_layout_unstick(void) {
    extern u32 lbl_803C663C[4]; // how many animations are still running (fn_800626EC / fn_80062674)
    s32 step = lbl_803C66B0.step[0];
    // The count too: left above 0 it never gets back to 0, so every later move (and the game's own
    // screens, e.g. the lineup) would wait on the busy flag forever.
    lbl_803C663C[0] = 0;
    lbl_803C66B0.active[0] = 0;
    lbl_803C66B0.step[0] = 0;
    return step;
}

// Sprite `slot` of the layout (0x18 + row: a row's label, 0x20: the description), or NULL.
LayoutObj* port_career_layout_obj(s32 slot) {
    if (sPortMainMenuTask == NULL || slot < 0 || slot >= sPortMainMenuTask->count) {
        return NULL;
    }
    return MN_SLOT(slot + BASE(sPortMainMenuTask));
}
#endif

// fn_2_7E380, size:0x4E0
// NONMATCHING 97%: unrolled roster search addresses each entry from the base instead of a walking pointer (see fn_2_7E194)
#if NONMATCHING
void fn_2_7E380(MenuTask* o, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        s8 pos;
        s32 player;
        s32 j;
        MN_SLOT(0xC + BASE(o) + index)->flags |= 2;
        MN_SLOT(0x12 + BASE(o) + index)->flags |= 2;
        MN_SLOT(0xC + BASE(o) + index)->_68 = 4;
        MN_SLOT(0xE + BASE(o) + index)->_68 = 4;
        MN_SLOT(0x12 + BASE(o) + index)->_5C = 0xA0000;
        MN_SLOT(0x12 + BASE(o) + index)->_68 = 4;
        MN_SLOT(0xB6 + BASE(o) + index)->flags |= 2;
        MN_SLOT(0x1C + BASE(o) + index)->_5C = 0x140000;
        MN_SLOT(0x1C + BASE(o) + index)->_68 = 4;
        MN_SLOT(0x6A + BASE(o) + index)->_5C = 0x1E0000;
        MN_SLOT(0x6A + BASE(o) + index)->_68 = 4;
        MN_SLOT(0x93 + BASE(o) + index)->_5C = 0;
        MN_SLOT(0x93 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x95 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x8F + BASE(o) + index)->_5C = 0;
        MN_SLOT(0x8F + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x89 + BASE(o) + index)->_5C = 0xA0000;
        MN_SLOT(0x89 + BASE(o) + index)->_68 = 4;
        MN_SLOT(0x97 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0xAC + BASE(o) + index)->_68 = 1;
        if (g_d_GameSettings._10 == 0 && index == 0) {
            // single player: also set up team 1's (CPU) objects
            player = lbl_8034E9A0.captain[1];
            for (j = 0; j < 9; j++) {
                if (TEAM_TBL->roster[1][j] == player) {
                    pos = TEAM_TBL->pos[1][j];
                }
            }
            for (j = 0; j < 9; j++) {
                if (index == 0) {
                    if (j != pos) {
                        MN_SLOT(9 + 0x46 + BASE(o) + j)->flags &= ~2;
                    } else {
                        MN_SLOT(9 + 0x34 + BASE(o) + pos)->_68 = 1;
                        MN_SLOT(9 + 0x46 + BASE(o) + pos)->_68 = 4;
                        MN_SLOT(9 + 0x46 + BASE(o) + pos)->flags |= 2;
                    }
                }
                MN_SLOT(0x22 + BASE(o) + j + 9)->flags &= ~2;
            }
            MN_SLOT(0x93 + BASE(o) + 1)->_68 = 4;
            MN_SLOT(0x95 + BASE(o) + 1)->_68 = 4;
            MN_SLOT(0x8F + BASE(o) + 1)->_68 = 4;
            MN_SLOT(0x91 + BASE(o) + 1)->_68 = 4;
            MN_SLOT(0x97 + BASE(o) + 1)->flags &= ~2;
            MN_SLOT(0xAC + BASE(o) + 1)->flags &= ~2;
        }
        fn_800626EC(index);
        *e = 1;
    }
}
#endif

// fn_2_7E974, size:0x508
// NONMATCHING 80%: orig unrolls the 9-slot loop by 3, ours stays rolled
#if NONMATCHING
void fn_2_7E974(MenuTask* o, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        s8 other;
        s32 j;
        MN_SLOT(0xC + BASE(o) + index)->flags |= 2;
        MN_SLOT(0x12 + BASE(o) + index)->flags |= 2;
        MN_SLOT(0xC + BASE(o) + index)->_5C = 0;
        MN_SLOT(0xC + BASE(o) + index)->_68 = 1;
        MN_SLOT(0xE + BASE(o) + index)->_5C = 0;
        MN_SLOT(0xE + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x10 + BASE(o) + index)->_5C = (u8)lbl_8034E9A0.captainVariant[index] << 16;
        MN_SLOT(0x12 + BASE(o) + index)->_5C = 0;
        MN_SLOT(0x12 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x14 + BASE(o) + index)->_5C = (u8)lbl_8034E9A0.captainVariant[index] << 16;
        MN_SLOT(0xB6 + BASE(o) + index)->flags &= ~2;
        MN_SLOT(0x1C + BASE(o) + index)->_5C = 0xA0000;
        MN_SLOT(0x1C + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x6A + BASE(o) + index)->_5C = 0xA0000;
        MN_SLOT(0x6A + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x93 + BASE(o) + index)->_5C = 0xA0000;
        MN_SLOT(0x93 + BASE(o) + index)->_68 = 4;
        MN_SLOT(0x8F + BASE(o) + index)->_5C = 0xA0000;
        MN_SLOT(0x8F + BASE(o) + index)->_68 = 4;
        MN_SLOT(0x89 + BASE(o) + index)->_5C = 0x50000;
        MN_SLOT(0x89 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x97 + BASE(o) + index)->_68 = 4;
        MN_SLOT(0xAC + BASE(o) + index)->_68 = 4;
        if (g_d_GameSettings._10 == 0) {
            other = (s8)lbl_8034E9A0.ports[0] == 0;
            if (lbl_2_bss_F468._37[1] != 0) {
                MN_SLOT(0x98 + BASE(o))->_68 = 4;
            }
        }
        if (g_d_GameSettings._10 == 0 && lbl_2_bss_F468._37[0] != 0 && index == 0) {
            for (j = 0; j < 9; j++) {
                MN_SLOT(9 + 0x46 + BASE(o) + j)->flags |= 2;
                MN_SLOT(9 + 0x46 + BASE(o) + j)->_64 = other + 0x11;
                MN_SLOT(9 + 0x46 + BASE(o) + j)->_5C = 0;
                MN_SLOT(9 + 0x46 + BASE(o) + j)->_68 = 0;
            }
            MN_SLOT(0x8F + BASE(o) + other)->_68 = 1;
            MN_SLOT(0x91 + BASE(o) + other)->_5C = 0;
            MN_SLOT(0x91 + BASE(o) + other)->_68 = 1;
        }
        fn_800626EC(index);
        *e = 1;
    }
}
#endif

extern u8 lbl_803CB8D0[];

// fn_2_7207C, size:0x518
void fn_2_7207C(void) {
    MenuTask* o = lbl_803CC1B8;
    s32 i;
    s32 n;
    switch (lbl_803C66B0.step[0]) {
    case 30:
        if ((lbl_803C66B0.steps[5][1] == 0) ? 1 : 0) {
            MN_SLOT(BASE(o))->_5C = 0;
            MN_SLOT(BASE(o))->_68 = 1;
            MN_SLOT(2 + BASE(o))->_68 = 1;
            for (i = 0; i < 4; i++) {
                MN_SLOT(3 + BASE(o) + i)->color &= ~0xFF;
            }
            MN_SLOT(3 + BASE(o) + lbl_803CB8D0[lbl_2_bss_F410._4C])->_68 = 1;
            MN_SLOT(3 + BASE(o) + lbl_803CB8D0[lbl_2_bss_F410._4C])->color = (MN_SLOT(3 + BASE(o) + lbl_803CB8D0[lbl_2_bss_F410._4C])->color & ~0xFF) | 0xFF;
            MN_SLOT(7 + BASE(o) + lbl_803CB8D0[lbl_2_bss_F410._4C])->_5C = 0;
            MN_SLOT(7 + BASE(o) + lbl_803CB8D0[lbl_2_bss_F410._4C])->_68 = 1;
            fn_800626EC(0);
            lbl_803C66B0.steps[5][1] = 1;
        }
        if (lbl_803C66B0.steps[5][1] == 1) {
            n = fn_80042DA8(o, 0, 0x16) != 0;
            if (n + (fn_80042DA8(o, lbl_803CB8D0[lbl_2_bss_F410._4C] + 7, 5) != 0) == 2) {
                lbl_803C66B0.step[1] = 0;
                fn_80062674(0);
                lbl_803C66B0.steps[5][1] = 2;
            }
        }
        break;
    case 31:
        if ((lbl_803C66B0.steps[5][1] == 0) ? 1 : 0) {
            MN_SLOT(BASE(o))->_68 = 1;
            fn_800626EC(0);
            lbl_803C66B0.steps[5][1] = 1;
        }
        if (lbl_803C66B0.steps[5][1] == 1 && fn_80042DA8(o, 0, 0x1C) != 0) {
            fn_80062674(0);
            lbl_803C66B0.steps[5][1] = 2;
        }
        break;
    case 32:
        if ((lbl_803C66B0.steps[5][1] == 0) ? 1 : 0) {
            for (i = 0; i < 4; i++) {
                MN_SLOT(3 + BASE(o) + i)->_68 = 0;
                MN_SLOT(7 + BASE(o) + i)->_68 = 0;
                MN_SLOT(3 + BASE(o) + i)->_5C = 0;
                MN_SLOT(7 + BASE(o) + i)->_5C = 0;
                MN_SLOT(3 + BASE(o) + i)->color &= ~0xFF;
            }
            MN_SLOT(3 + BASE(o) + lbl_803CB8D0[lbl_2_bss_F410._4C])->_68 = 1;
            MN_SLOT(3 + BASE(o) + lbl_803CB8D0[lbl_2_bss_F410._4C])->color = (MN_SLOT(3 + BASE(o) + lbl_803CB8D0[lbl_2_bss_F410._4C])->color & ~0xFF) | 0xFF;
            MN_SLOT(7 + BASE(o) + lbl_803CB8D0[lbl_2_bss_F410._4C])->_5C = 0;
            MN_SLOT(7 + BASE(o) + lbl_803CB8D0[lbl_2_bss_F410._4C])->_68 = 1;
            fn_800626EC(0);
            lbl_803C66B0.steps[5][1] = 1;
        }
        if (lbl_803C66B0.steps[5][1] == 1 && fn_80042DA8(o, lbl_803CB8D0[lbl_2_bss_F410._4C] + 7, 5) != 0) {
            fn_80062674(0);
            lbl_803C66B0.steps[5][1] = 2;
        }
        break;
    case 33:
        if ((lbl_803C66B0.steps[5][1] == 0) ? 1 : 0) {
            MN_SLOT(BASE(o))->_68 = 1;
            fn_800626EC(0);
            lbl_803C66B0.steps[5][1] = 1;
        }
        if (lbl_803C66B0.steps[5][1] == 1) {
            fn_80062674(0);
            lbl_803C66B0.steps[5][1] = 2;
        }
        break;
    }
    if (lbl_8034E9A0._472A == 1) {
        lbl_8034E9A0._472A = 0xFF;
        fn_80034CEC(o);
        REMOVE_QUEUE_NOARG();
    }
}

extern SpaniDesc lbl_2_data_2B59C[];

// fn_2_8279C, size:0x554
// NONMATCHING 93%: CW sign-extends the team icon differently (extsb vs extsh); register allocation
#if NONMATCHING
void fn_2_8279C(void) {
    MenuTask* o = lbl_803CC1B8;
    u8* w;
    s32 i;
    s8 other;
    s8 icon;
    s32 cpu;
    u8 x;
    lbl_8034E9A0._474C = o;
    fn_80034E20(o, lbl_2_data_2B59C);
    w = lbl_8034E9A0.ports;
    for (i = 0; i < 2; i++) {
        if (g_d_GameSettings._10 == 0 && i != 0) {
            if (g_d_GameSettings._10 == 0) {
                if ((s8)lbl_8034E9A0.ports[0] == 0) {
                    other = 1;
                } else {
                    other = 0;
                }
            }
            MN_SLOT(0x7A + BASE(o) + i)->_5C = other << 16;
            MN_SLOT(0x18 + BASE(o) + i)->_5C = (other + 4) << 16;
        } else {
            cpu = 0;
            MN_SLOT(0x7A + BASE(o) + i)->_5C = (s8)w[0] << 16;
            if (g_d_GameSettings._10 == 0 && i != 0) {
                cpu = 1;
            }
            if (cpu) {
                if ((s8)w[0] == -1) {
                    icon = (i != 0) + 4;
                } else {
                    icon = (s8)w[0] + 4;
                }
            } else {
                icon = (s8)w[0];
            }
            MN_SLOT(0x18 + BASE(o) + i)->_5C = icon << 16;
        }
        w++;
        MN_SLOT(0x1A + BASE(o) + i)->flags &= ~2;
        MN_SLOT(0xB2 + BASE(o) + i)->flags &= ~2;
    }
    if (g_d_GameSettings.GameModeSelected == 5) {
        MN_SLOT(0x98 + BASE(o))->flags &= ~2;
        x = lbl_8034E9A0.roster[CHALLENGE->_441D / 9][CHALLENGE->_441D % 9].stats.CaptainStarHitPitch;
        fn_800363D8(o, 0x89, 1, 3, lbl_2_data_2B3A4[x]);
        fn_800363D8(o, 0x8B, 1, 3, lbl_2_data_2B3A4[x]);
        x = lbl_8034E9A0.roster[CHALLENGE->_441F / 9][CHALLENGE->_441F % 9].stats.CaptainStarHitPitch;
        fn_800363D8(o, 0x8A, 1, 3, lbl_2_data_2B3A4[x]);
        fn_800363D8(o, 0x8C, 1, 3, lbl_2_data_2B3A4[x]);
    }
    for (i = 0; i < 2; i++) {
        s32 j;
        for (j = 0; j < 5; j++) {
            MN_SLOT(0x6E + BASE(o) + i * 5 + j)->_5C = 0;
            MN_SLOT(0x6E + BASE(o) + i * 5 + j)->_68 = 0;
        }
    }
    MN_SLOT(0x1C + BASE(o))->flags &= ~2;
    MN_SLOT(0x1D + BASE(o))->flags &= ~2;
    MN_SLOT(0x1E + BASE(o))->flags &= ~2;
    MN_SLOT(0x1F + BASE(o))->flags &= ~2;
    MN_SLOT(0x84 + BASE(o))->flags &= ~2;
    MN_SLOT(0xAE + BASE(o))->flags &= ~2;
    MN_SLOT(0xAF + BASE(o))->flags &= ~2;
    lbl_8034E9A0._48B2 = 0;
    lbl_8034E9A0._48B1 = 0;
    *(u16*)&lbl_8034E9A0.charFlag[9] = 0; // clears charFlag[9] and [10]
    *(void**)lbl_803CC1B8 = fn_2_81628;
}
#endif

extern s32 translateStarPitchHitIndex(u8 pitch);
extern u8 translateStarPitch(u8 star);
extern u8 translateStarSwing(u8 star);

// fn_2_76874, size:0x57C
// Show the selected character's star swing / star pitch icons.
// NONMATCHING 85%: roster search and stats pointer scheduled differently; register allocation
#if NONMATCHING
void fn_2_76874(MenuTask* o, u8 index) {
    u8* shown = (u8*)&lbl_2_bss_F468 + index;
    if (*(shown += offsetof(MenuTeamSel, _49[0])) == 0) {
        s32 c;
        s32 j;
        s32 row;
        s32 col;
        StatTable* stats;
        u8 star;
        u8 swing;
        u8 pitch;
        MN_SLOT(0xE0 + BASE(o) + index)->flags &= ~2;
        MN_SLOT(0xE0 + BASE(o) + index)->_68 = 0;
        MN_SLOT(0xB6 + BASE(o) + index)->_68 = 4;
        MN_SLOT(0xC6 + BASE(o) + index)->_68 = 4;
        if (lbl_803CBBCC->scene == 9) {
            if (g_d_GameSettings.GameModeSelected != 5) {
                c = lbl_800FE5D4[lbl_2_bss_F410.charSel[index]];
            } else {
                c = lbl_800FE930[lbl_80361B20._F4 * 6 + lbl_2_bss_F410.charSel[index]];
            }
        } else if (lbl_2_bss_F468._41[index] == 0) {
            for (j = 0; j < 9; j++) {
                if (TEAM_TBL->pos[index][j] == lbl_2_bss_F468.cursor[index]) {
                    break;
                }
            }
            c = TEAM_TBL->roster[index][j];
        } else {
            c = lbl_2_bss_F410.charSel[4 + index];
            if (c == -1) {
                *shown = 0;
                return;
            }
        }
        lbl_2_bss_F468._4D[index] = c;
        row = (s8)(c / 9);
        col = (s8)(c % 9);
        stats = &lbl_8034E9A0.roster[row][col].stats;
        star = stats->CaptainStarHitPitch;
        if (star == 0) {
            swing = stats->NonCaptainStarSwing + 0xB;
            pitch = stats->NonCaptainStarPitch + 0xB;
        } else if (g_d_GameSettings.GameModeSelected != 5) {
            swing = star - 1;
            pitch = swing;
        } else {
            s8 hit = translateStarPitchHitIndex(star - 1);
            if (hit != -1 && (s8)CHALLENGE->_15F1[hit] == 0 && lbl_803CBBCC->scene == 9) {
                stats = &lbl_8034E9A0.roster[row][col].stats;
                swing = stats->NonCaptainStarSwing + 0xB;
                pitch = stats->NonCaptainStarPitch + 0xB;
            } else if (hit != -1 && (s8)CHALLENGE->_43C2[hit] == 0 && lbl_803CBBCC->scene == 0xA) {
                stats = &lbl_8034E9A0.roster[row][col].stats;
                swing = stats->NonCaptainStarSwing + 0xB;
                pitch = stats->NonCaptainStarPitch + 0xB;
            } else {
                swing = star - 1;
                pitch = star - 1;
            }
        }
        swing = translateStarSwing(swing);
        pitch = translateStarPitch(pitch);
        MN_SLOT(0xE6 + BASE(o) + index)->_64 = swing;
        MN_SLOT(0xE6 + BASE(o) + index)->_5C = 0;
        MN_SLOT(0xE6 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0xE8 + BASE(o) + index)->_64 = pitch;
        MN_SLOT(0xE8 + BASE(o) + index)->_5C = 0;
        MN_SLOT(0xE8 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0xEA + BASE(o) + index)->flags |= 2;
        MN_SLOT(0xEA + BASE(o) + index)->_68 = 1;
        MN_SLOT(0xE2 + BASE(o) + index)->_68 = 1;
        *shown = 1;
    }
    if (lbl_803CBBCC->scene == 0xA) {
        u8* sel = (u8*)&lbl_2_bss_F468 + index;
        if (sel[offsetof(MenuTeamSel, _41[0])] != 0 && sel[offsetof(MenuTeamSel, _4D[0])] != lbl_2_bss_F410.charSel[4 + index]) {
            fn_2_74F40(o, index);
            *shown = 0;
        }
    }
}
#endif

// fn_2_7FAFC, size:0x5B4
void fn_2_7FAFC(MenuTask* o, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    s32 n;
    s32 k;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        s32 a;
        s32 b;
        u8 y;
        u8 x;
        MN_SLOT(BASE(o) + index)->_5C = 0x1E0000;
        MN_SLOT(2 + BASE(o) + index)->_5C = 0x1E0000;
        MN_SLOT(BASE(o) + index)->_68 = 4;
        MN_SLOT(2 + BASE(o) + index)->_68 = 4;
        MN_SLOT(4 + BASE(o) + index)->_64 = 0x50;
        MN_SLOT(4 + BASE(o) + index)->_5C = 0;
        MN_SLOT(4 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x85 + BASE(o) + index)->_5C = 0x140000;
        MN_SLOT(0x85 + BASE(o) + index)->_68 = 4;
        MN_SLOT(0x89 + BASE(o) + index)->_5C = 0xA0000;
        MN_SLOT(0x89 + BASE(o) + index)->_68 = 4;
        MN_SLOT(0x82 + BASE(o) + index)->flags |= 2;
        MN_SLOT(0x7A + BASE(o) + index)->flags |= 2;
        if (g_d_GameSettings._10 == 0 && index != 0) {
            if ((s8)lbl_8034E9A0.ports[0] == 0) {
                MN_SLOT(0x7A + BASE(o) + index)->_5C = 0x10000;
            } else {
                MN_SLOT(0x7A + BASE(o) + index)->_5C = 0;
            }
        } else {
            MN_SLOT(0x7A + BASE(o) + index)->_5C = (s8)lbl_8034E9A0.ports[index] << 16;
        }
        if (g_d_GameSettings.GameModeSelected != 5) {
            b = lbl_803C6724[index];
            a = lbl_800FE5D4[lbl_2_bss_F410.charSel[index]];
            b = lbl_800FE5D4[b];
        } else if (index != 0) {
            b = *(s8*)&CHALLENGE->_441F;
            a = b;
        } else {
            a = b = CHALLENGE->_441D;
        }
        x = lbl_8034E9A0.roster[a / 9][a % 9].stats.CaptainStarHitPitch;
        y = lbl_8034E9A0.roster[b / 9][b % 9].stats.CaptainStarHitPitch;
        MN_SLOT(0x82 + BASE(o) + index)->_5C = lbl_2_data_2B3A4[x] << 16;
        MN_SLOT(0x7E + BASE(o) + index)->_5C = lbl_2_data_2B3A4[x] << 16;
        fn_800363D8(o, index + 0x89, 1, 3, lbl_2_data_2B3A4[x]);
        fn_800363D8(o, index + 0x8B, 1, 3, lbl_2_data_2B3A4[y]);
        MN_SLOT(0x80 + BASE(o) + index)->_5C = 0;
        MN_SLOT(0x80 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x78 + BASE(o) + index)->_5C = 0;
        MN_SLOT(0x78 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x7C + BASE(o) + index)->_5C = 0;
        MN_SLOT(0x7C + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x97 + BASE(o) + index)->_64 = 0x78;
        MN_SLOT(0x97 + BASE(o) + index)->_5C = 0;
        MN_SLOT(0x97 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x99 + BASE(o) + index)->_64 = 0x79;
        fn_2_74F40(o, index);
        MN_SLOT(0xAC + BASE(o) + index)->_68 = 4;
        fn_800626EC(index);
        *e = 1;
    }
    if (*e == 1) {
        n = 0;
        k = 0;
        k++;
        n += fn_80042DA8(o, index, 0x14) != 0;
        k++;
        n += fn_80042DA8(o, index + 2, 0x14) != 0;
        k++;
        n += fn_80042DA8(o, index + 0x85, 0xA) != 0;
        k++;
        n += fn_80042DA8(o, index + 0x89, 5) != 0;
        if (n == k) {
            fn_80062674(index);
            *e = 2;
        }
    }
}

// fn_2_73EFC, size:0x5CC
// NONMATCHING 88%: inlined fn_2_73BF0/fn_2_73B54 results allocated differently; register allocation
#if NONMATCHING
void fn_2_73EFC(MenuTask* o) {
    s32 mode = lbl_2_bss_F410._00;
    s32 prev = lbl_2_bss_F410._04;
    s32 i;
    if ((lbl_803C66B0.steps[1][1] == 0) ? 1 : 0) {
        for (i = 0; i < 7; i++) {
            if (lbl_8034E9A0.input[0].pressed == 0 && lbl_8034E9A0.input[0].repeat != 0) {
                lbl_8034E9A0._4751 = 1;
                if (mode == i) {
                    MN_SLOT(3 + BASE(o) + i)->flags |= 2;
                    MN_SLOT(3 + BASE(o) + i)->_5C = 0xE0000;
                    MN_SLOT(3 + BASE(o) + i)->_68 = 0;
                } else {
                    MN_SLOT(3 + BASE(o) + i)->flags &= ~2;
                }
                MN_SLOT(0x20 + BASE(o))->_5C = 0xA0000;
                MN_SLOT(0x21 + BASE(o))->_5C = 0;
                fn_800363D8(o, 0x20, 1, 0x32, mode);
                fn_800363D8(o, 0x21, 1, 0x32, prev);
                MN_SLOT(0x20 + BASE(o))->_68 = 0;
                MN_SLOT(0x21 + BASE(o))->_68 = 0;
            } else {
                s32 frame;
                s8 state;
                lbl_8034E9A0._4751 = 0;
                frame = fn_2_73BF0(mode);
                state = fn_2_73B54(mode);
                if (mode == i) {
                    MN_SLOT(3 + BASE(o) + i)->flags |= 2;
                    MN_SLOT(3 + BASE(o) + i)->_5C = frame << 16;
                    MN_SLOT(3 + BASE(o) + i)->_68 = state;
                } else {
                    MN_SLOT(3 + BASE(o) + i)->flags &= ~2;
                }
                if (lbl_2_bss_A840 == 0 && mode == 6 && i == lbl_2_bss_A840) {
                    MN_SLOT(3 + BASE(o) + i)->flags |= 2;
                    MN_SLOT(3 + BASE(o) + i)->_5C = 0x80000;
                    MN_SLOT(3 + BASE(o) + i)->_68 = 4;
                } else if (lbl_2_bss_A840 == 6 && mode == 0 && i == lbl_2_bss_A840) {
                    MN_SLOT(3 + BASE(o) + i)->flags |= 2;
                    MN_SLOT(3 + BASE(o) + i)->_5C = 0x2D0000;
                    MN_SLOT(3 + BASE(o) + i)->_68 = 1;
                }
                MN_SLOT(0x20 + BASE(o))->_5C = 0;
                MN_SLOT(0x21 + BASE(o))->_5C = 0xA0000;
                fn_800363D8(o, 0x20, 1, 0x32, mode);
                fn_800363D8(o, 0x21, 1, 0x32, prev);
                MN_SLOT(0x20 + BASE(o))->_68 = 1;
                MN_SLOT(0x21 + BASE(o))->_68 = 1;
            }
        }
        MN_SLOT(0x18 + BASE(o) + mode)->_5C = 0;
        MN_SLOT(0x18 + BASE(o) + mode)->_68 = 1;
        MN_SLOT(0x18 + BASE(o) + prev)->_5C = 0;
        MN_SLOT(0x18 + BASE(o) + prev)->_68 = 0;
        if (lbl_8034E9A0._4751 == 0) {
            MN_SLOT(0x11 + BASE(o) + mode)->_5C = 0;
            MN_SLOT(0x11 + BASE(o) + mode)->_68 = 1;
        } else {
            MN_SLOT(0x11 + BASE(o) + mode)->_5C = 0;
            MN_SLOT(0x11 + BASE(o) + mode)->_68 = 0;
        }
        if (lbl_8034E9A0._4751 == 0) {
            fn_800626EC(0);
        }
        lbl_803C66B0.steps[1][1] = 1;
    }
}
#endif

// fn_2_82EC0, size:0x630
void fn_2_82EC0(void) {
    MenuTask* o = lbl_803CC1B8;
    s32 sel = lbl_2_bss_F410._44;
    s32 prev = lbl_803CBBC4[1];
    s32 f;
    s32 i;
    s32 n;
    s32 k;
    switch (lbl_803CBBC4[0]) {
    case 0x5D:
        if ((lbl_803CBBC4[2] == 0) ? 1 : 0) {
            MN_SLOT(BASE(o))->_68 = 1;
            MN_SLOT(1 + BASE(o))->_68 = 1;
            MN_SLOT(2 + BASE(o))->_68 = 1;
            MN_SLOT(3 + BASE(o) + sel)->_68 = 1;
            lbl_803CBBC4[2] = 1;
            lbl_803CBBC4[3] = 1;
        }
        if ((lbl_803CBBC4[3] == 1) ? 1 : 0) {
            lbl_803CBBC4[0] = 0;
            lbl_803CBBC4[3] = 0;
            lbl_803CBBC4[2] = 0;
            lbl_803CBBC4[0] = 0x5F;
        }
        break;
    case 0x5F:
        if ((MN_SLOT(3 + BASE(o) + sel)->_5C >> 16) >= 0x37) {
            MN_SLOT(3 + BASE(o) + sel)->_5C = 0x50000;
            MN_SLOT(3 + BASE(o) + sel)->_68 = 1;
        }
        if ((MN_SLOT(BASE(o))->_5C >> 16) >= 0x23) {
            MN_SLOT(BASE(o))->_5C = 0x230000;
            MN_SLOT(BASE(o))->_68 = 0;
        }
        break;
    case 0x5E:
        if ((lbl_803CBBC4[2] == 0) ? 1 : 0) {
            MN_SLOT(3 + BASE(o) + sel)->_68 = 1;
            if (lbl_2_bss_F468._57 >= sel) {
                f = sel << 16;
                MN_SLOT(0xC + BASE(o))->_5C = f;
                if (lbl_80361B20._F4 != 0) {
                    MN_SLOT(0xB + BASE(o))->_5C = (sel + 4) << 16;
                } else {
                    MN_SLOT(0xB + BASE(o))->_5C = f;
                }
            } else {
                MN_SLOT(0xC + BASE(o))->_5C = 0x80000;
                MN_SLOT(0xB + BASE(o))->_5C = 0x80000;
            }
            if (lbl_80361B20._E4[sel] != 0) {
                fn_800363D8(o, 9, 1, 0x27, sel);
            } else {
                fn_800363D8(o, 9, 1, 0x27, 4);
            }
            if (prev != -1) {
                MN_SLOT(3 + BASE(o) + prev)->_5C = 0;
                MN_SLOT(3 + BASE(o) + prev)->_68 = 0;
            }
            lbl_803CBBC4[2] = 1;
            lbl_803CBBC4[3] = 1;
        }
        if ((lbl_803CBBC4[3] == 1) ? 1 : 0) {
            lbl_803CBBC4[0] = 0;
            lbl_803CBBC4[3] = 0;
            lbl_803CBBC4[2] = 0;
            lbl_803CBBC4[0] = 0x5F;
        }
        break;
    case 0x60:
        if ((lbl_803CBBC4[2] == 0) ? 1 : 0) {
            MN_SLOT(BASE(o))->_5C = 0x230000;
            MN_SLOT(BASE(o))->_68 = 1;
            MN_SLOT(1 + BASE(o))->_68 = 4;
            MN_SLOT(3 + BASE(o) + sel)->_5C = 0x370000;
            MN_SLOT(3 + BASE(o) + sel)->_68 = 1;
            MN_SLOT(7 + BASE(o))->_68 = 4;
            MN_SLOT(8 + BASE(o))->_68 = 4;
            MN_SLOT(0xA + BASE(o))->_68 = 4;
            MN_SLOT(9 + BASE(o))->_68 = 4;
            lbl_803CBBC4[2] = 1;
            lbl_803CBBC4[3] = 1;
        }
        if ((lbl_803CBBC4[3] == 1) ? 1 : 0) {
            n = 0;
            k = 0;
            k++;
            n += fn_80042DA8(o, sel + 3, 0x46) != 0;
            if (n == k) {
                lbl_803CBBC4[0] = 0;
                lbl_803CBBC4[3] = 0;
                lbl_803CBBC4[2] = 0;
                lbl_803CBBC4[0] = 0x61;
            }
        }
        break;
    case 0x61:
        if ((lbl_803CBBC4[2] == 0) ? 1 : 0) {
            MN_SLOT(2 + BASE(o))->_68 = 4;
            for (i = 0; i < 4; i++) {
                MN_SLOT(3 + BASE(o) + i)->_5C = 0;
                MN_SLOT(3 + BASE(o) + i)->_68 = 0;
            }
            lbl_803CBBC4[2] = 1;
            lbl_803CBBC4[3] = 1;
        }
        if ((lbl_803CBBC4[3] == 1) ? 1 : 0) {
            n = 0;
            k = 0;
            k++;
            n += fn_80042DA8(o, 2, 0) != 0;
            if (n == k) {
                lbl_803CBBC4[0] = 0;
                lbl_803CBBC4[3] = 0;
                lbl_803CBBC4[2] = 0;
                lbl_803CBBC4[4] = 1;
            }
        }
        break;
    }
    if (lbl_803CBBC4[4] != 0 && lbl_803CBBC4[3] != 1) {
        lbl_803CBBC4[4] = 0;
        lbl_803CBBC4[5] = 1;
        fn_80034CEC(o);
        REMOVE_QUEUE_NOARG();
    }
}

extern u8 lbl_2_data_2D998[];
extern u8 lbl_2_data_2E2ED[3];
// The original reaches lbl_2_data_2DC84 (icon per selection, 8 bytes), lbl_2_data_2E2EC
// (current selection) and lbl_2_data_2E2ED (previous selection) from the pooled base
// lbl_2_data_2D998; the matching build keeps that addressing, other builds name them.
#if NONMATCHING
#define SEL_ICON(i) (lbl_2_data_2DC84[i])
#define SEL_CUR (*(u8*)&lbl_2_data_2E2EC)
#define SEL_PREV (lbl_2_data_2E2ED[0])
#else
#define SEL_ICON(i) (lbl_2_data_2D998[0x2EC + (i)])
#define SEL_CUR (lbl_2_data_2D998[0x954])
#define SEL_PREV (lbl_2_data_2D998[0x955])
#endif

// NONMATCHING 75%: SelIcon inline expands with extra loads/extensions; register allocation
#if NONMATCHING
// SEL_ICON: icon per selection; icon 1 is swapped for `alt` when lbl_80361B20._F5 == 0.
static inline s16 SelIcon(s8 v, u8 alt) {
    s32 swap = 0;
    if (SEL_ICON(lbl_2_bss_F410._44) == 1 && lbl_80361B20._F5 == 0) {
        swap = 1;
    }
    return swap ? alt : SEL_ICON(v);
}

// fn_2_83B34, size:0x660
void fn_2_83B34(MenuTask* o, s8 sel) {
    s32 i;
    s32 n;
    s32 k;
    if ((lbl_803C66B0.steps[7][1] == 0) ? 1 : 0) {
        for (i = 0; i < 6; i++) {
            MN_SLOT(6 + BASE(o) + i)->_68 = 0;
            MN_SLOT(6 + BASE(o) + i)->_5C = 0;
        }
        if (lbl_803CBCD8[0] != 0) {
            if ((s8)lbl_803CBCD8[1] == 0) {
                MN_SLOT(BASE(o))->color = (MN_SLOT(BASE(o))->color & ~0xFF) | 0xFF;
                MN_SLOT(1 + BASE(o))->color = (MN_SLOT(1 + BASE(o))->color & ~0xFF) | 0xFF;
                MN_SLOT(BASE(o))->_5C = 0;
                MN_SLOT(1 + BASE(o))->_5C = 0xA0000;
                fn_800363D8(o, 0, 1, 0x20, SEL_ICON(sel));
                if ((s8)SEL_CUR == -1) {
                    fn_800363D8(o, 1, 1, 0x20, SEL_ICON(sel));
                } else {
                    fn_800363D8(o, 1, 1, 0x20, SEL_ICON((s8)SEL_CUR));
                }
                MN_SLOT(BASE(o))->_68 = 1;
                MN_SLOT(1 + BASE(o))->_68 = 1;
                sel = SEL_CUR;
            }
        } else {
            MN_SLOT(BASE(o))->color = (MN_SLOT(BASE(o))->color & ~0xFF) | 0xFF;
            MN_SLOT(1 + BASE(o))->color = (MN_SLOT(1 + BASE(o))->color & ~0xFF) | 0xFF;
            MN_SLOT(BASE(o))->_5C = 0;
            MN_SLOT(1 + BASE(o))->_5C = 0xA0000;
            fn_800363D8(o, 0, 1, 0x20, SelIcon(sel, 0x12));
            if ((s8)SEL_CUR == -1) {
                fn_800363D8(o, 1, 1, 0x20, SelIcon(sel, 0x12));
            } else {
                u8 t = SEL_ICON((s8)SEL_CUR);
                fn_800363D8(o, 1, 1, 0x20, (s16)((t == 1 && lbl_80361B20._F5 == 0) ? 0x12 : t));
            }
            MN_SLOT(BASE(o))->_68 = 1;
            MN_SLOT(1 + BASE(o))->_68 = 4;
        }
        MN_SLOT(6 + BASE(o) + sel)->_5C = 0x10000;
        MN_SLOT(6 + BASE(o) + sel)->_68 = 1;
        {
            s16 icon = SelIcon(sel, 6);
            MN_SLOT(2 + BASE(o))->_5C = 0;
            fn_800363D8(o, 2, 1, 0x22, icon);
        }
        {
            s16 icon = SelIcon(sel, 6);
            MN_SLOT(3 + BASE(o))->_5C = 0;
            fn_800363D8(o, 3, 1, 0x25, icon);
            fn_800363D8(o, 3, 3, 0x24, icon);
            MN_SLOT(3 + BASE(o))->_68 = 1;
        }
        lbl_803C66B0.steps[7][1] = 1;
    }
    if (lbl_803C66B0.steps[7][1] == 1) {
        n = 0;
        k = 0;
        if ((s8)lbl_803CBCD8[1] == 0) {
            k++;
            n += fn_80042DA8(o, 0, 0xA) != 0;
            k++;
            n += fn_80042DA8(o, 1, 0) != 0;
            k++;
            n += fn_80042DA8(o, sel + 6, 4) != 0;
        }
        if (n == k) {
            SEL_PREV = SEL_CUR;
            SEL_CUR = sel;
            o->timerA = 0;
            if ((s8)lbl_803CBCD8[1] < 0) {
                lbl_803CBCD8[1] = 0;
                lbl_803CBCD8[0] = 0;
            }
            lbl_803C66B0.steps[7][1] = 2;
            lbl_803C66B0.step[0] = 0;
        }
    }
}
#endif

// fn_2_80F5C, size:0x6CC
void fn_2_80F5C(MenuTask* o, s32 index) {
    u8* e = &lbl_803C66B0.steps[2][1];
    if ((e[index] == 0) ? 1 : 0) {
        MN_SLOT(BASE(o) + index)->_64 = 0x47;
        MN_SLOT(2 + BASE(o) + index)->_64 = 0x47;
        MN_SLOT(4 + BASE(o) + index)->_64 = 0x50;
        MN_SLOT(BASE(o) + index)->_5C = 0;
        MN_SLOT(2 + BASE(o) + index)->_5C = 0;
        MN_SLOT(BASE(o) + index)->_68 = 1;
        MN_SLOT(2 + BASE(o) + index)->_68 = 1;
        MN_SLOT(4 + BASE(o) + index)->_5C = 0;
        MN_SLOT(4 + BASE(o) + index)->_68 = 1;
        MN_SLOT(6 + BASE(o))->_68 = 1;
        MN_SLOT(8 + BASE(o))->_68 = 1;
        MN_SLOT(0x12 + BASE(o) + index)->flags &= ~2;
        MN_SLOT(0xC + BASE(o) + index)->flags &= ~2;
        MN_SLOT(0x99 + BASE(o) + index)->_64 = 0x79;
        if (index != 0 && lbl_2_bss_100B8.picked[0] == 0 && g_d_GameSettings._10 == 0) {
            LayoutSlot* s84 = MN_SLOTS + 0x84;
            MN_SLOT(0x80 + BASE(o) + index)->flags &= ~2;
            MN_SLOT(0x7A + BASE(o) + index)->_68 = 0;
            MN_SLOT(0x97 + BASE(o) + index)->flags &= ~2;
            s84[BASE(o)].obj->flags |= 2;
            s84[BASE(o)].obj->_68 = 1;
        } else {
            if (g_d_GameSettings.GameModeSelected == 5) {
                MN_SLOT(0x84 + BASE(o))->flags &= ~2;
                MN_SLOT(0x98 + BASE(o))->flags &= ~2;
                MN_SLOT(0xAD + BASE(o))->flags &= ~2;
            } else if (index != 0 && lbl_803C5EA4._05 != 0) {
                MN_SLOT(BASE(o) + index)->_64 = 0x47;
                MN_SLOT(2 + BASE(o) + index)->_64 = 0x47;
                MN_SLOT(4 + BASE(o) + index)->_64 = 0x50;
                MN_SLOT(BASE(o) + index)->_5C = 0x140000;
                MN_SLOT(2 + BASE(o) + index)->_5C = 0x140000;
                MN_SLOT(BASE(o) + index)->_68 = 1;
                MN_SLOT(2 + BASE(o) + index)->_68 = 1;
                MN_SLOT(4 + BASE(o) + index)->_68 = 1;
                MN_SLOT(0x84 + BASE(o))->flags &= ~2;
                MN_SLOT(0x97 + BASE(o) + index)->flags |= 2;
                MN_SLOT(0x97 + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x97 + BASE(o) + index)->_68 = 1;
                MN_SLOT(0x7A + BASE(o) + index)->_5C = (s8)lbl_8034E9A0.ports[1] << 16;
                MN_SLOT(0x19 + BASE(o))->_5C = (s8)lbl_8034E9A0.ports[1] << 16;
                MN_SLOT(0x1A + BASE(o) + index)->flags |= 2;
                MN_SLOT(0x1A + BASE(o) + index)->_68 = 1;
                if (lbl_803C66B0.step[0] == 4 && lbl_803C66B0.steps[2][1] == 1) {
                    fn_80062674(0);
                    lbl_803C66B0.steps[2][1] = 2;
                }
            }
            fn_2_7630C(o, index);
            MN_SLOT(0x80 + BASE(o) + index)->flags |= 2;
            MN_SLOT(0x80 + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x80 + BASE(o) + index)->_68 = 1;
            MN_SLOT(0x85 + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x87 + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x85 + BASE(o) + index)->_68 = 1;
            MN_SLOT(0x87 + BASE(o) + index)->_68 = 1;
            MN_SLOT(0x89 + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x8B + BASE(o) + index)->_5C = 0x50000;
            MN_SLOT(0x89 + BASE(o) + index)->_68 = 1;
            MN_SLOT(0x8B + BASE(o) + index)->_68 = 1;
            MN_SLOT(0x78 + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x78 + BASE(o) + index)->_68 = 1;
            MN_SLOT(0x7C + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x7C + BASE(o) + index)->_68 = 1;
            fn_2_74F40(o, index);
        }
        MN_SLOT(0xAC + BASE(o) + index)->flags &= ~2;
        fn_800626EC(index);
        e[index] = 1;
    }
}

// fn_2_7308C, size:0x6CC
// Team-select header state machine; each case is a pair of the small helpers above.
// NONMATCHING 94%: the inlined fn_2_72E54/fn_2_72A88 bodies keep their own mismatches (lbz instead of the
// original lbzu search walker, register order)
#if NONMATCHING
void fn_2_7308C(void) {
    MenuTask* o = lbl_803CC1B8;
    switch (lbl_803CBBC4[0]) {
    case 1:
        setupHeaderSlots(o);
        fn_2_72DDC(o);
        break;
    case 2:
        fn_2_728C0(o);
        fn_2_72814(o);
        break;
    case 3:
        setupHeaderRoster(o);
        fn_2_72A58();
        break;
    case 0x47:
        fn_2_72D60(o);
        fn_2_72CB4(o);
        break;
    }
    if (lbl_803CBCD8[5] != 0) {
        lbl_803CBCD8[5] = 0;
        fn_80034CEC(o);
        REMOVE_QUEUE_NOARG();
    }
}
#endif

// fn_2_7DAB8, size:0x6DC
// NONMATCHING 85%: second position search stays a ctr loop (orig fully unrolled); register allocation
#if NONMATCHING
void fn_2_7DAB8(MenuTask* o, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        s32 cur = lbl_2_bss_F468.prevCursor[index];
        s32 sel = lbl_2_bss_F468.cursor[index];
        s32 fs;
        s32 fc;
        s32 fp;
        s32 j;
        u8* p;
        for (j = 0; j < 9; j++) {
            s8 t = TEAM_TBL->pos[index][j];
            if (t == sel) {
                fs = j;
            }
            if (t == cur) {
                fc = j;
            }
        }
        if (cur != 9 && cur != 10 && cur < 9) {
            if (cur != (s8)lbl_2_bss_F468._61[index]) {
                MN_SLOT(0x46 + BASE(o) + cur + index * 9)->_5C = 0xF0000;
                MN_SLOT(0x46 + BASE(o) + cur + index * 9)->_68 = 4;
                if (TEAM_TBL->roster[index][fc] != -1 && TEAM_TBL->roster[index][fc] != 0x36) {
                    MN_SLOT(0x34 + BASE(o) + cur + index * 9)->_5C = 0xA0000;
                    MN_SLOT(0x34 + BASE(o) + cur + index * 9)->_68 = 1;
                }
            }
            MN_SLOT(0x22 + BASE(o) + cur + index * 9)->flags &= ~2;
        }
        if (sel != 9 && sel != 10 && sel < 9 && sel != (s8)lbl_2_bss_F468._61[index]) {
            MN_SLOT(0x46 + BASE(o) + sel + index * 9)->_5C = 0;
            MN_SLOT(0x46 + BASE(o) + sel + index * 9)->_68 = 1;
            if (TEAM_TBL->roster[index][fs] != -1 && TEAM_TBL->roster[index][fs] != 0x36) {
                MN_SLOT(0x34 + BASE(o) + sel + index * 9)->_5C = 0x140000;
                MN_SLOT(0x34 + BASE(o) + sel + index * 9)->_68 = 4;
            }
            if (lbl_2_bss_F468._41[index] == 0) {
                MN_SLOT(0x22 + BASE(o) + sel + index * 9)->flags |= 2;
                MN_SLOT(0x22 + BASE(o) + sel + index * 9)->_68 = 1;
            }
        }
        fn_2_74F40(o, index);
        if (sel == 9) {
            MN_SLOT(0x95 + BASE(o) + index)->_68 = 1;
        } else if (sel == 10) {
            MN_SLOT(0x91 + BASE(o) + index)->_68 = 1;
        } else {
            if ((MN_SLOT(0x95 + BASE(o) + index)->_5C >> 16) > 10) {
                MN_SLOT(0x95 + BASE(o) + index)->_5C = 0xA0000;
                MN_SLOT(0x95 + BASE(o) + index)->_68 = 4;
            }
            if ((MN_SLOT(0x91 + BASE(o) + index)->_5C >> 16) > 10 || cur == 10) {
                MN_SLOT(0x91 + BASE(o) + index)->_5C = 0xA0000;
                MN_SLOT(0x91 + BASE(o) + index)->_68 = 4;
            }
        }
        p = (u8*)&lbl_2_bss_F468 + index;
        if (p[offsetof(MenuTeamSel, _5F[0])] != 0) {
            u8 prev = *(p += offsetof(MenuTeamSel, _61[0]));
            if (cur == (s8)prev || sel == (s8)prev) {
                for (j = 0; j < 9; j++) {
                    if (TEAM_TBL->pos[index][j] == (s8)lbl_2_bss_F468._61[index]) {
                        fp = j;
                    }
                }
                if (TEAM_TBL->roster[index][fp] != -1 && TEAM_TBL->roster[index][fp] != 0x36) {
                    MN_SLOT(0x34 + BASE(o) + (s8)*p + index * 9)->_5C = 0xA0000;
                    MN_SLOT(0x34 + BASE(o) + (s8)*p + index * 9)->_68 = 0;
                }
                MN_SLOT(0x46 + BASE(o) + (s8)*p + index * 9)->_5C = 0xF0000;
                MN_SLOT(0x46 + BASE(o) + (s8)*p + index * 9)->_68 = 0;
                if (sel == (s8)*p) {
                    MN_SLOT(0x22 + BASE(o) + (s8)*p + index * 9)->flags |= 2;
                }
            } else {
                MN_SLOT(0x22 + BASE(o) + (s8)prev + index * 9)->flags &= ~2;
            }
        }
        fn_800626EC(index);
        *e = 1;
    }
}
#endif

// fn_2_7836C, size:0x754
// NONMATCHING 75%: TEAM_TBL[index] indexing computed with mulli per access; orig hoists index*9 and walks with lbzu
#if NONMATCHING
void fn_2_7836C(MenuTask* o, s8 index) {
    u8* sel = (u8*)&lbl_2_bss_F468 + index;
    s8 fp;
    s8 fs;
    s32 j;
    s32 n;
    s32 k;
    u8* e;
    if (sel[offsetof(MenuTeamSel, _5F[0])] == 0) {
        u8 prev = lbl_2_bss_F468._61[index];
        for (j = 0; j < 9; j++) {
            if (TEAM_TBL->pos[index][j] == (s8)prev) {
                fp = j;
            }
        }
        e = (u8*)&lbl_803C66B0 + index;
        if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
            if ((s8)prev != -1) {
                MN_SLOT(0x46 + BASE(o) + (s8)prev + index * 9)->_5C = 0;
                MN_SLOT(0x46 + BASE(o) + (s8)prev + index * 9)->_68 = 1;
                if (TEAM_TBL->roster[index][fp] != -1 && TEAM_TBL->roster[index][fp] != 0x36) {
                    MN_SLOT(0x34 + BASE(o) + (s8)prev + index * 9)->_5C = 0x140000;
                    MN_SLOT(0x34 + BASE(o) + (s8)prev + index * 9)->_68 = 4;
                }
            }
            if (lbl_2_bss_F468._37[index] != 0) {
                MN_SLOT(0x93 + BASE(o) + index)->_64 = 0xA;
                MN_SLOT(0x93 + BASE(o) + index)->_68 = 1;
            }
            fn_800626EC(index);
            *e = 1;
        }
        if (*e == 1) {
            n = 0;
            k = 0;
            if (TEAM_TBL->roster[index][fp] != -1 && TEAM_TBL->roster[index][fp] != 0x36 && (s8)prev != -1) {
                k++;
                n += fn_80042DA8(o, (s8)prev + index * 9 + 0x34, 0xA) != 0;
            }
            if (n == k) {
                sel[offsetof(MenuTeamSel, _5F[0])] = 1;
                fn_80062674(index);
                *e = 2;
            }
        }
    } else {
        u8* pp = (u8*)&lbl_2_bss_F468 + index;
        u8 prev = *(pp += offsetof(MenuTeamSel, _61[0]));
        s8 cur = lbl_2_bss_F468.cursor[index];
        for (j = 0; j < 9; j++) {
            s8 t = TEAM_TBL->pos[index][j];
            if (t == (s8)prev) {
                fp = j;
            }
            if (t == cur) {
                fs = j;
            }
        }
        e = (u8*)&lbl_803C66B0 + index;
        if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
            if ((s8)prev != -1) {
                s8 r = TEAM_TBL->roster[index][fp];
                if (r != -1 && r != 0x36) {
                    MN_SLOT(0x58 + BASE(o) + (s8)prev + index * 9)->_5C = r << 16;
                    MN_SLOT(0x34 + BASE(o) + (s8)prev + index * 9)->flags |= 2;
                    MN_SLOT(0x34 + BASE(o) + (s8)prev + index * 9)->_5C = 0xA0000;
                    MN_SLOT(0x34 + BASE(o) + (s8)prev + index * 9)->_68 = 1;
                } else {
                    MN_SLOT(0x34 + BASE(o) + (s8)prev + index * 9)->flags &= ~2;
                }
            }
            {
                s8 r = TEAM_TBL->roster[index][fs];
                if (r != -1 && r != 0x36) {
                    MN_SLOT(0x58 + BASE(o) + cur + index * 9)->_5C = r << 16;
                    MN_SLOT(0x34 + BASE(o) + cur + index * 9)->_5C = 0xA0000;
                    MN_SLOT(0x34 + BASE(o) + cur + index * 9)->_68 = 0;
                    MN_SLOT(0x34 + BASE(o) + cur + index * 9)->flags |= 2;
                } else {
                    MN_SLOT(0x34 + BASE(o) + cur + index * 9)->flags &= ~2;
                }
            }
            if ((s8)prev != cur && (s8)prev != -1) {
                MN_SLOT(0x46 + BASE(o) + (s8)prev + index * 9)->_5C = 0xF0000;
                MN_SLOT(0x46 + BASE(o) + (s8)prev + index * 9)->_68 = 4;
            }
            if (lbl_2_bss_F468._37[index] != 0) {
                MN_SLOT(0x93 + BASE(o) + index)->_64 = 9;
                MN_SLOT(0x93 + BASE(o) + index)->_5C = 0xA0000;
                MN_SLOT(0x93 + BASE(o) + index)->_68 = 0;
            }
            fn_2_74F40(o, index);
            fn_800626EC(index);
            *e = 1;
        }
        if (*e == 1) {
            n = 0;
            k = 0;
            if (TEAM_TBL->roster[index][fp] != -1 && TEAM_TBL->roster[index][fp] != 0x36 && (s8)prev != -1 && (s8)prev != cur) {
                k++;
                n += fn_80042DA8(o, (s8)prev + index * 9 + 0x34, 0x14) != 0;
            }
            if (n == k) {
                sel[offsetof(MenuTeamSel, _5F[0])] = 0;
                *pp = -1;
                fn_80062674(index);
                *e = 2;
            }
        }
    }
}
#endif

extern u8 fn_80064918(s16 charId);

// fn_2_76DF0, size:0x8B0
// Show the selected character's stat page (bat/throw hands, ability icons).
// NONMATCHING 90%: register allocation (index kept in r31 vs r29) and the shown-flag pointer walk
#if NONMATCHING
void fn_2_76DF0(MenuTask* o, u8 index) {
    u8* shown = (u8*)&lbl_2_bss_F468 + index;
    if (*(shown += offsetof(MenuTeamSel, _49[0])) == 0) {
        s32 c;
        s32 j;
        s32 frame;
        StatTable* stats;
        u32 mask;
        u8 bat;
        u8 thr;
        u8 flag;
        if (lbl_803CBBCC->scene == 9) {
            if (g_d_GameSettings.GameModeSelected != 5) {
                c = lbl_800FE5D4[lbl_2_bss_F410.charSel[index]];
            } else {
                c = lbl_800FE930[lbl_80361B20._F4 * 6 + lbl_2_bss_F410.charSel[index]];
            }
        } else {
            if (lbl_2_bss_F468._41[index] == 0) {
                for (j = 0; j < 9; j++) {
                    if (TEAM_TBL->pos[index][j] == lbl_2_bss_F468.cursor[index]) {
                        break;
                    }
                }
                c = TEAM_TBL->roster[index][j];
            } else {
                c = lbl_2_bss_F410.charSel[4 + index];
                if (c == -1) {
                    *shown = 0;
                    return;
                }
            }
            lbl_2_bss_F468._4D[index] = c;
        }
        frame = c << 16;
        stats = &lbl_8034E9A0.roster[(s8)(c / 9)][(s8)(c % 9)].stats;
        mask = stats->FieldingStats;
        bat = stats->HitTrajectoryPushPull;
        thr = stats->HitTrajectoryHighLow;
        flag = stats->BattingStance;
        MN_SLOT(0xB4 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0xCA + BASE(o) + index)->_5C = frame;
        MN_SLOT(0xCC + BASE(o) + index)->_5C = fn_80064918(c) << 16;
        MN_SLOT(0xC6 + BASE(o) + index)->_5C = 0;
        MN_SLOT(0xDE + BASE(o) + index)->_5C = frame;
        fn_2_76650(o, index, mask);
        for (j = 0; j < 6; j++) {
            MN_SLOT(0xD2 + BASE(o) + index + j * 2)->_5C = j << 16;
        }
        for (j = 0; j < 6; j++) {
            MN_SLOT(0xBA + BASE(o) + index + j * 2)->_5C = 0;
        }
        switch (bat) {
        case 0:
            MN_SLOT(0xBA + BASE(o) + index)->_68 = 1;
            MN_SLOT(0xBC + BASE(o) + index)->_68 = 0;
            MN_SLOT(0xBE + BASE(o) + index)->_68 = 0;
            break;
        case 1:
            if (flag == 0) {
                MN_SLOT(0xBA + BASE(o) + index)->_68 = 0;
                MN_SLOT(0xBC + BASE(o) + index)->_68 = 1;
                MN_SLOT(0xBE + BASE(o) + index)->_68 = 0;
            } else {
                MN_SLOT(0xBA + BASE(o) + index)->_68 = 0;
                MN_SLOT(0xBC + BASE(o) + index)->_68 = 0;
                MN_SLOT(0xBE + BASE(o) + index)->_68 = 1;
            }
            break;
        case 2:
            if (flag == 0) {
                MN_SLOT(0xBA + BASE(o) + index)->_68 = 0;
                MN_SLOT(0xBC + BASE(o) + index)->_68 = 0;
                MN_SLOT(0xBE + BASE(o) + index)->_68 = 1;
            } else {
                MN_SLOT(0xBA + BASE(o) + index)->_68 = 0;
                MN_SLOT(0xBC + BASE(o) + index)->_68 = 1;
                MN_SLOT(0xBE + BASE(o) + index)->_68 = 0;
            }
            break;
        }
        switch (thr) {
        case 0:
            MN_SLOT(0xC0 + BASE(o) + index)->_68 = 1;
            MN_SLOT(0xC2 + BASE(o) + index)->_68 = 0;
            MN_SLOT(0xC4 + BASE(o) + index)->_68 = 0;
            break;
        case 1:
            MN_SLOT(0xC0 + BASE(o) + index)->_68 = 0;
            MN_SLOT(0xC2 + BASE(o) + index)->_68 = 1;
            MN_SLOT(0xC4 + BASE(o) + index)->_68 = 0;
            break;
        case 2:
            MN_SLOT(0xC0 + BASE(o) + index)->_68 = 0;
            MN_SLOT(0xC2 + BASE(o) + index)->_68 = 0;
            MN_SLOT(0xC4 + BASE(o) + index)->_68 = 1;
            break;
        }
        MN_SLOT(0xE0 + BASE(o) + index)->flags |= 2;
        MN_SLOT(0xE0 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0xB6 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0xC6 + BASE(o) + index)->_5C = 0;
        MN_SLOT(0xC6 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0xEA + BASE(o) + index)->flags &= ~2;
        MN_SLOT(0xEA + BASE(o) + index)->_68 = 0;
        MN_SLOT(0xE2 + BASE(o) + index)->_68 = 4;
        *shown = 1;
    }
    if (lbl_803CBBCC->scene == 0xA) {
        u8* sel = (u8*)&lbl_2_bss_F468 + index;
        if (sel[offsetof(MenuTeamSel, _41[0])] != 0 && sel[offsetof(MenuTeamSel, _4D[0])] != lbl_2_bss_F410.charSel[4 + index]) {
            fn_2_74F40(o, index);
            *shown = 0;
        }
    }
}
#endif

// NONMATCHING 85%: register allocation; captain search/flag pointers scheduled differently
#if NONMATCHING
// Field position of the team's captain (player id at lbl_8034E9A0 + 0x46E0).
static inline u8 CaptainPos(s32 team, u8 pos) {
    s32 j;
    for (j = 0; j < 9; j++) {
        if (lbl_8034E9A0.captain[team] == TEAM_TBL->roster[team][j]) {
            pos = TEAM_TBL->pos[team][j];
            break;
        }
    }
    return pos;
}

// fn_2_776A0, size:0x994
void fn_2_776A0(MenuTask* o, s32 port) {
    u8 team = lbl_803C66B0.portOf[port];
    u16 buttons = lbl_8034E9A0.input[port].pressed;
    u8 pos;
    s32 j;
    u8* t;
    if (lbl_803C66B0.steps[0][0] == 2) {
        t = (u8*)&lbl_2_bss_F468 + team;
        if (t[offsetof(MenuTeamSel, _45[0])] == 0) {
            if (t[offsetof(MenuTeamSel, _41[0])] == 0) {
                if (lbl_2_bss_F468.prevCursor[team] != lbl_2_bss_F468.cursor[team]) {
                    fn_2_74F40(o, team);
                }
            } else {
                if (lbl_2_bss_F468._20[team] != lbl_2_bss_F410.charSel[4 + team]) {
                    fn_2_74F40(o, team);
                }
            }
        }
    }
    if ((buttons & 0x800) && lbl_803CBBCC->scene == 0xA) {
        u8* sel = (u8*)&lbl_2_bss_F468 + team;
        if (sel[offsetof(MenuTeamSel, _52[0])] != 0 && g_d_GameSettings.GameModeSelected != 5 && sel[offsetof(MenuTeamSel, _54[0])] == 0) {
            u8* st = (u8*)&lbl_803C66B0 + team;
            s32 cur;
            if (st[offsetof(TutorialSteps, active[0])] != 0) {
                fn_80062674(team);
                lbl_803C66B0.steps[2][team + 1] = 2;
            } else {
                if (g_d_GameSettings._10 == 0 && team != 0) {
                    st[offsetof(TutorialSteps, step[0])] = 0;
                }
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            }
            pos = CaptainPos(team, pos);
            for (j = 0; j < 9; j++) {
                if (j != (s8)pos) {
                    MN_SLOT(0x34 + BASE(o) + j + team * 9)->_68 = 4;
                }
            }
            MN_SLOT(0x34 + BASE(o) + (s8)pos + team * 9)->_68 = 1;
            fn_2_75BE4(o, team);
            MN_SLOT(0x91 + BASE(o) + team)->_68 = 1;
            cur = lbl_2_bss_F468.prevCursor[team];
            if (cur == 9) {
                MN_SLOT(0x93 + BASE(o) + team)->_68 = 4;
                MN_SLOT(0x95 + BASE(o) + port)->_5C = 0xA0000;
                MN_SLOT(0x95 + BASE(o) + team)->_68 = 4;
            } else if (cur == 10) {
                MN_SLOT(0x93 + BASE(o) + team)->_68 = 4;
            } else {
                MN_SLOT(0x46 + BASE(o) + cur + team * 9)->_5C = 0xF0000;
                MN_SLOT(0x46 + BASE(o) + cur + team * 9)->_68 = 4;
                MN_SLOT(0x93 + BASE(o) + team)->_68 = 4;
            }
            for (j = 0; j < 9; j++) {
                MN_SLOT(0x97 + BASE(o) + team)->flags &= ~2;
                MN_SLOT(0xAC + BASE(o) + team)->flags &= ~2;
                MN_SLOT(0x22 + BASE(o) + j + team * 9)->flags &= ~2;
            }
            sel[offsetof(MenuTeamSel, _54[0])] = 1;
        }
    }
    if (lbl_803C66B0.steps[0][0] == 2) {
        t = (u8*)&lbl_2_bss_F468 + team;
        if (t[offsetof(MenuTeamSel, _45[0])] == 0 && t[offsetof(MenuTeamSel, _50[0])] != 0) {
            s32 sp = lbl_2_bss_F468.cursor[team];
            for (j = 0; j < 9; j++) {
                if (TEAM_TBL->pos[team][j] == sp) {
                    break;
                }
            }
            MN_SLOT(0x58 + BASE(o) + sp + team * 9)->_5C = TEAM_TBL->roster[team][j] << 16;
            fn_2_74F40(o, team);
            t[offsetof(MenuTeamSel, _50[0])] = 0;
        }
    }
    t = (u8*)&lbl_2_bss_F468 + team;
    if (t[offsetof(MenuTeamSel, _54[0])] != 0) {
        pos = CaptainPos(team, pos);
        if ((fn_80042DA8(o, (s8)pos + team * 9 + 0x34, 0x14) != 0) == 1) {
            t[offsetof(MenuTeamSel, _54[0])] = 0;
            lbl_2_bss_F468._52[team] = 0;
        }
    }
    t = (u8*)&lbl_2_bss_F468 + team;
    if (t[offsetof(MenuTeamSel, _4B[0])] != 0) {
        u8* u = (u8*)&lbl_2_bss_F468 + team;
        if (u[offsetof(MenuTeamSel, _45[0])] != 0) {
            switch (u[offsetof(MenuTeamSel, _47[0])]) {
            case 0:
                fn_2_76DF0(o, team);
                return;
            case 1:
                fn_2_76874(o, team);
                return;
            }
        } else {
            if (u[offsetof(MenuTeamSel, _47[0])] == 0) {
                s32 n;
                if ((MN_SLOT(0xB4 + BASE(o) + team)->_5C >> 16) > 5) {
                    MN_SLOT(0xB4 + BASE(o) + team)->_5C = 0x50000;
                }
                MN_SLOT(0xB4 + BASE(o) + team)->_68 = 4;
                MN_SLOT(0xB6 + BASE(o) + team)->_68 = 4;
                MN_SLOT(0xC6 + BASE(o) + team)->_68 = 4;
                n = fn_80042DA8(o, team + 0xB4, 0) != 0;
                n += fn_80042DA8(o, team + 0xB6, 0) != 0;
                n += fn_80042DA8(o, team + 0xC6, 0) != 0;
                if (n == 3) {
                    t[offsetof(MenuTeamSel, _4B[0])] = 0;
                }
            } else {
                if ((MN_SLOT(0xB4 + BASE(o) + team)->_5C >> 16) > 5) {
                    MN_SLOT(0xB4 + BASE(o) + team)->_5C = 0x50000;
                }
                MN_SLOT(0xB4 + BASE(o) + team)->_68 = 4;
                MN_SLOT(0xE2 + BASE(o) + team)->_68 = 4;
                if ((fn_80042DA8(o, team + 0xE2, 0) != 0) == 1) {
                    t[offsetof(MenuTeamSel, _4B[0])] = 0;
                }
            }
            lbl_2_bss_F468._49[team] = 0;
        }
    }
}
#endif


// fn_2_845A8, size:0xA00
// NONMATCHING 85%: switch arms schedule slot loads differently; register allocation
#if NONMATCHING
void fn_2_845A8(void) {
    MenuTask* o = lbl_803CC1B8;
    s32 i;
    s32 n;
    s32 k;
#ifdef TARGET_PC
    if (!port_stadium_select_enabled()) {
        // Mario Stadium only (port/game/menu_scope.c): hide the other parks' icons.
        for (i = 1; i < 6; i++) {
            LayoutObj* q = MN_SLOT(6 + BASE(o) + i);
            if (q != NULL) {
                q->flags &= ~2;
            }
        }
    }
#endif
    if (lbl_803CBCD8[4] != 0) {
        lbl_803CBCD8[4] = 0;
        SEL_CUR = -1;
        fn_80034CEC(o);
        REMOVE_QUEUE_NOARG();
        return;
    }
    SEL_PREV = -1;
    switch (lbl_803C66B0.step[0]) {
    case 39:
        if ((lbl_803C66B0.steps[7][1] == 0) ? 1 : 0) {
            MN_SLOT(BASE(o))->_5C = 0;
            MN_SLOT(BASE(o))->_68 = 1;
            MN_SLOT(4 + BASE(o))->_5C = 0;
            MN_SLOT(4 + BASE(o))->_68 = 1;
            for (i = 0; i < 6; i++) {
                MN_SLOT(6 + BASE(o) + i)->color = (MN_SLOT(6 + BASE(o) + i)->color & ~0xFF) | 0xFF;
            }
            MN_SLOT(6 + BASE(o) + lbl_2_bss_F410._44)->_5C = 0x10000;
            MN_SLOT(6 + BASE(o) + lbl_2_bss_F410._44)->_68 = 1;
            fn_800626EC(0);
            lbl_803C66B0.steps[7][1] = 1;
        }
        if (lbl_803C66B0.steps[7][1] == 1) {
            n = fn_80042DA8(o, 0, 0xA) != 0;
            n += fn_80042DA8(o, 4, 0x14) != 0;
            if (n == 2) {
                SEL_CUR = lbl_2_bss_F410._44;
                fn_80062674(0);
                lbl_803C66B0.steps[7][1] = 2;
            }
        }
        break;
    case 36:
        if ((lbl_803C66B0.steps[7][1] == 0) ? 1 : 0) {
            MN_SLOT(BASE(o))->_5C = 0xA0000;
            MN_SLOT(1 + BASE(o))->_5C = 0xA0000;
            MN_SLOT(BASE(o))->_68 = 4;
            MN_SLOT(1 + BASE(o))->_68 = 4;
            MN_SLOT(2 + BASE(o))->_68 = 4;
            MN_SLOT(3 + BASE(o))->_68 = 4;
            MN_SLOT(5 + BASE(o))->_68 = 4;
            MN_SLOT(4 + BASE(o))->_68 = 4;
            fn_800626EC(0);
            lbl_803C66B0.steps[7][1] = 1;
        }
        if (lbl_803C66B0.steps[7][1] == 1) {
            n = fn_80042DA8(o, 0, 0) != 0;
            n += fn_80042DA8(o, 1, 0) != 0;
            n += fn_80042DA8(o, 2, 0) != 0;
            n += fn_80042DA8(o, 3, 0) != 0;
            n += fn_80042DA8(o, 5, 0) != 0;
            if (n == 5) {
                SEL_CUR = lbl_2_bss_F410._44;
                fn_80062674(0);
                lbl_803C66B0.steps[7][1] = 2;
                SEL_CUR = -1;
                fn_80034CEC(o);
                REMOVE_QUEUE_NOARG();
            }
        }
        break;
    case 38:
        if ((lbl_803C66B0.steps[7][1] == 0) ? 1 : 0) {
            MN_SLOT(BASE(o))->_68 = 4;
            MN_SLOT(1 + BASE(o))->_5C = 0;
            MN_SLOT(1 + BASE(o))->_68 = 0;
            MN_SLOT(2 + BASE(o))->_68 = 1;
            MN_SLOT(5 + BASE(o))->_68 = 1;
            MN_SLOT(3 + BASE(o))->_68 = 1;
            MN_SLOT(4 + BASE(o))->_5C = 0x280000;
            MN_SLOT(4 + BASE(o))->_68 = 4;
            fn_800626EC(0);
            lbl_803C66B0.steps[7][1] = 1;
        }
        if (lbl_803C66B0.steps[7][1] == 1) {
            n = fn_80042DA8(o, 0, 0xA) != 0;
            n += fn_80042DA8(o, 4, 0x14) != 0;
            if (n == 2) {
                s32 sel = lbl_2_bss_F410._44;
                if (lbl_80361B20._F5 == 0 && sel != 0) {
                    sel--;
                }
                SEL_CUR = sel;
                fn_80062674(0);
                lbl_803C66B0.steps[7][1] = 2;
            }
        }
        break;
    case 37:
        if ((lbl_803C66B0.steps[7][1] == 0) ? 1 : 0) {
            MN_SLOT(BASE(o))->_5C = 0xA0000;
            MN_SLOT(1 + BASE(o))->_5C = 0;
            MN_SLOT(BASE(o))->_68 = 1;
            MN_SLOT(1 + BASE(o))->_68 = 0;
            MN_SLOT(2 + BASE(o))->_68 = 4;
            MN_SLOT(3 + BASE(o))->_68 = 4;
            MN_SLOT(5 + BASE(o))->_68 = 4;
            MN_SLOT(4 + BASE(o))->_68 = 1;
            fn_800626EC(0);
            lbl_803C66B0.steps[7][1] = 1;
        }
        if (lbl_803C66B0.steps[7][1] == 1) {
            n = fn_80042DA8(o, 0, 0x14) != 0;
            n += fn_80042DA8(o, 2, 0) != 0;
            n += fn_80042DA8(o, 5, 0) != 0;
            n += fn_80042DA8(o, 3, 0) != 0;
            if (n == 4) {
                SEL_CUR = lbl_2_bss_F410._44;
                fn_80062674(0);
                lbl_803C66B0.steps[7][1] = 2;
            }
        }
        break;
    case 49:
        if ((MN_SLOT(BASE(o))->_5C >> 16) == 0x14) {
            MN_SLOT(BASE(o))->_68 = 1;
        }
        if ((MN_SLOT(BASE(o))->_5C >> 16) == 0x1E) {
            lbl_803CBCD8[4] = 1;
            fn_80062674(0);
            lbl_803C66B0.steps[8][1] = 2;
        }
        break;
    case 40:
        fn_2_83B34(o, lbl_2_bss_F410._44);
        break;
    }
    if (lbl_803CBCD8[4] == 0 && lbl_803C66B0.step[0] != 0x25 && lbl_803C66B0.step[0] != 0x24) {
        s32 sel = lbl_2_bss_F410._44;
        if (lbl_803CBBCC->scene != 0xD && lbl_2_bss_F468._58 == 0 &&
            (s8)SEL_CUR == sel && (s8)SEL_PREV == -1) {
            s32 t;
            s32 off;
            u8 icon;
            u8 icon2;
            if (lbl_80361B20._F5 == 0 && SEL_ICON(sel) == 1) {
                fn_800363D8(o, 0, 1, 0x20, 0x12);
                fn_800363D8(o, 1, 1, 0x20, 0x12);
                return;
            }
            // Cycle the icon animation every 100 frames.
            for (t = 0, off = 0, i = 0; i < 3; i++, off += 6, t += 100) {
                if (o->timerA == t) {
                    icon = SEL_ICON(sel);
                    if (lbl_2_bss_ABC0 != 0) {
                        icon2 = icon + 0xC;
                        lbl_2_bss_ABC0 = 0;
                    } else if (i != 0) {
                        icon2 = icon + (i - 1) * 6;
                    } else {
                        icon2 = icon;
                    }
                    MN_SLOT(BASE(o))->_5C = 0;
                    MN_SLOT(1 + BASE(o))->_5C = 0xA0000;
                    fn_800363D8(o, 0, 1, 0x20, icon + off);
                    fn_800363D8(o, 1, 1, 0x20, icon2);
                    MN_SLOT(BASE(o))->color = (MN_SLOT(BASE(o))->color & ~0xFF) | 0xFF;
                    MN_SLOT(1 + BASE(o))->color = (MN_SLOT(1 + BASE(o))->color & ~0xFF) | 0xFF;
                    MN_SLOT(BASE(o))->_68 = 1;
                    MN_SLOT(1 + BASE(o))->_68 = 4;
                }
            }
            fn_80042DA8(o, 0, 0xA);
            fn_80042DA8(o, 1, 0);
            o->timerA++;
            if (o->timerA > 300) {
                o->timerA = 0;
                lbl_2_bss_ABC0 = 1;
            }
        }
    }
}
#endif

extern BOOL fn_80067B40(s32 unused, u8 charId, u8 flag);

// fn_2_74F40, size:0xC18
// Refresh the selected character's stat bars (fn_2_74E14) and ability icon.
// NONMATCHING 85%: same calls and stores; fn_2_74E14 inlined with different register allocation, BOOL test codegen differs
#if NONMATCHING
void fn_2_74F40(MenuTask* o, s32 index) {
    s32 c;
    StatTable* stats;
    if (lbl_803CBBCC->scene == 9 || lbl_803C66B0.step[index] == 0xB) {
        if (g_d_GameSettings.GameModeSelected != 5) {
            c = lbl_800FE5D4[lbl_2_bss_F410.charSel[index]];
        } else {
            c = lbl_800FE930[lbl_80361B20._F4 * 6 + lbl_2_bss_F410.charSel[0]];
        }
        stats = &lbl_8034E9A0.roster[c / 9][c % 9].stats;
        fn_2_74E14(o, index, stats->PitchingStatBar, 1);
        fn_2_74E14(o, index, stats->RunningStatBar, 3);
        fn_2_74E14(o, index, stats->BattingStatBar, 0);
        fn_2_74E14(o, index, stats->FieldingStatBar, 2);
        MN_SLOT(0xAE + BASE(o) + index)->flags &= ~2;
        return;
    }
    if (lbl_2_bss_F468._41[index] != 0) {
        MN_SLOT(0xB2 + BASE(o) + index)->flags &= ~2;
        c = lbl_2_bss_F410.charSel[4 + index];
    } else {
        s32 sel = lbl_2_bss_F468.cursor[index];
        if (sel != 9 && sel != 10) {
            s32 j;
            for (j = 0; j < 9; j++) {
                if (TEAM_TBL->pos[index][j] == (s8)sel) {
                    c = TEAM_TBL->roster[index][j];
                }
            }
        } else {
            c = -1;
        }
    }
    if (c != -1 && fn_80067B40(0, c, 2) && g_d_GameSettings.GameModeSelected != 5) {
        MN_SLOT(0xB2 + BASE(o) + index)->flags |= 2;
        MN_SLOT(0xB2 + BASE(o) + index)->_5C = 0;
        MN_SLOT(0xB2 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0xAE + BASE(o) + index)->flags |= 2;
        MN_SLOT(0xAE + BASE(o) + index)->_5C = fn_2_74DB8(c) << 16;
    } else {
        MN_SLOT(0xB2 + BASE(o) + index)->flags &= ~2;
        if (lbl_2_bss_F468.cursor[index] != 9 && lbl_2_bss_F468.cursor[index] != 10) {
            MN_SLOT(0xAE + BASE(o) + index)->flags |= 2;
            MN_SLOT(0xAE + BASE(o) + index)->_5C = 0;
        }
    }
    MN_SLOT(0xAC + BASE(o) + index)->flags |= 2;
    {
        u8 con;
        u8 spd;
        u8 pwr;
        u8 fld;
        if (c >= 0 && c < 0x36) {
            stats = &lbl_8034E9A0.roster[c / 9][c % 9].stats;
            con = stats->BattingStatBar;
            spd = stats->RunningStatBar;
            pwr = stats->PitchingStatBar;
            fld = stats->FieldingStatBar;
            MN_SLOT(0xB0 + BASE(o) + index)->flags |= 2;
            MN_SLOT(0xB0 + BASE(o) + index)->_5C = c << 16;
            MN_SLOT(0xAC + BASE(o) + index)->_5C = 0;
            MN_SLOT(0xAC + BASE(o) + index)->_68 = 1;
        } else {
            pwr = 0;
            fld = 0;
            spd = 0;
            con = 0;
            MN_SLOT(0xB0 + BASE(o) + index)->flags &= ~2;
        }
        if (c >= 0 && c < 0x36) {
            fn_2_74E14(o, index, pwr, 1);
            fn_2_74E14(o, index, spd, 3);
            fn_2_74E14(o, index, con, 0);
            fn_2_74E14(o, index, fld, 2);
            return;
        }
    }
    MN_SLOT(0x97 + BASE(o) + index)->flags &= ~2;
}
#endif

// fn_2_81628, size:0x1174
// Per-frame driver of the team/field-position menu: runs each player's state handler.
// NONMATCHING 89%: the per-state handlers are called through casts so CW keeps them out of line (the
// original calls them); the frame is 0x10 bigger (four spills) and the saved registers are coloured differently
#if NONMATCHING
void fn_2_81628(void) {
    MenuTask* o = lbl_8034E9A0._474C;
    u8* st;
    s32 i;
    s32 j;
    s32 n;
    s32 k;
    s8 pos;
    s8 f20;
    s8 f21;
    if (lbl_8034E9A0._48B2 != 0) {
        fn_80034CEC(o);
        REMOVE_QUEUE_NOARG();
    }
    st = (u8*)&lbl_803C66B0;
    if (lbl_803C66B0.steps[0][0] == 1) {
        for (i = 0; i < 2; i++, st++) {
            switch (st[offsetof(TutorialSteps, step[0])]) {
            case 1:
                fn_2_80F5C(o, i);
                if (st[offsetof(TutorialSteps, steps[2][1])] == 1) {
                    n = fn_80042DA8(o, i, 0x14) != 0;
                    k = 2;
                    n += fn_80042DA8(o, i + 2, 0x14) != 0;
                    if (i == 0 || lbl_2_bss_100B8.picked[0] != 0 || g_d_GameSettings._10 != 0) {
                        n += fn_80042DA8(o, i + 0x85, 0xA) != 0;
                        n += fn_80042DA8(o, i + 0x87, 0xA) != 0;
                        n += fn_80042DA8(o, i + 0x89, 5) != 0;
                        k = 6;
                        n += fn_80042DA8(o, i + 0x8B, 0xA) != 0;
                    }
                    if (n == k) {
                        fn_80062674(i);
                        st[offsetof(TutorialSteps, steps[2][1])] = 2;
                    }
                }
                break;
            case 2:
                ((void (*)(MenuTask*, s32))fn_2_80C2C)(o, i);
                if (st[offsetof(TutorialSteps, steps[2][1])] == 1) {
                    n = fn_80042DA8(o, i, 0) != 0;
                    n += fn_80042DA8(o, i + 2, 0) != 0;
                    n += fn_80042DA8(o, i + 0x89, 0xA) != 0;
                    if (n == 3) {
                        fn_80062674(i);
                        st[offsetof(TutorialSteps, steps[2][1])] = 2;
                    }
                }
                break;
            case 3:
                fn_2_808D8(o, i);
                if (st[offsetof(TutorialSteps, steps[2][1])] == 1) {
                    n = fn_80042DA8(o, i + 0x89, 5) != 0;
                    n += fn_80042DA8(o, i + 0x8B, 0xA) != 0;
                    if (n == 2) {
                        fn_80062674(i);
                        st[offsetof(TutorialSteps, steps[2][1])] = 2;
                    }
                }
                break;
            case 4:
                ((void (*)(MenuTask*, s32))fn_2_805DC)(o, i);
                break;
            case 5:
                if (st[offsetof(TutorialSteps, steps[2][1])] == 0) {
                    MN_SLOT(0x7B + BASE(o))->_5C = ((s8)lbl_8034E9A0.ports[0] == 0) << 16;
                    MN_SLOT(0x19 + BASE(o))->_5C = (((s8)lbl_8034E9A0.ports[0] == 0) + 4) << 16;
                    fn_800626EC(i);
                    st[offsetof(TutorialSteps, steps[2][1])] = 1;
                }
                if (st[offsetof(TutorialSteps, steps[2][1])] == 1) {
                    fn_80062674(i);
                    st[offsetof(TutorialSteps, steps[2][1])] = 2;
                    g_d_GameSettings._10 = 0;
                }
                break;
            case 6:
                ((void (*)(MenuTask*))fn_2_802EC)(o);
                break;
            case 7:
                ((void (*)(MenuTask*, s32))fn_2_800B0)(o, i);
                break;
            case 8:
                fn_2_7FAFC(o, i);
                break;
            }
            fn_2_776A0(o, i);
            if (i != 0 && (MN_SLOT(6 + BASE(o))->_5C >> 16) == 0x3C) {
                MN_SLOT(7 + BASE(o))->_68 = 1;
                MN_SLOT(9 + BASE(o))->_68 = 1;
            }
        }
    } else if (lbl_803C66B0.steps[0][0] == 2) {
        for (i = 0; i < 2; i++, st++) {
            switch (st[offsetof(TutorialSteps, step[0])]) {
            case 9:
                fn_2_7BFF8(o, i);
                break;
            case 10:
                fn_2_7AE3C(o, i);
                ((void (*)(MenuTask*, s32))fn_2_7AC64)(o, i);
                break;
            case 11:
                fn_2_7A9D8(o, i);
                ((void (*)(MenuTask*, s32))fn_2_7A748)(o, i);
                break;
            case 14:
                fn_2_7DAB8(o, i);
                fn_2_7D85C(o, i);
                break;
            case 15:
                fn_2_7F8BC(o, i);
                if (st[offsetof(TutorialSteps, steps[2][1])] == 1) {
                    s32 sel = lbl_2_bss_F468.cursor[i];
                    s32 hit;
                    // (the original also runs an unused position search here)
                    hit = fn_80042DA8(o, (s8)sel + i * 9 + 0x34, 0xA) != 0;
                    if (fn_2_75B58(o, i) && hit == 1) {
                        fn_80062674(i);
                        fn_2_CCE0(i);
                    }
                }
                break;
            case 16:
                fn_2_7F2BC(o, i);
                fn_2_7F030(o, i);
                break;
            case 12:
                for (j = 0; j < 9; j++) {
                    if (j == lbl_2_bss_F468.cursor[i]) {
                        MN_SLOT(0x22 + BASE(o) + j + i * 9)->flags |= 2;
                    }
                }
                break;
            case 13: {
                s32 sel = lbl_2_bss_F468.cursor[i];
                if (lbl_2_bss_F468._41[i] != 0) {
                    MN_SLOT(0x22 + BASE(o) + sel + i * 9)->flags &= ~2;
                } else {
                    MN_SLOT(0x22 + BASE(o) + sel + i * 9)->flags |= 2;
                }
                fn_2_74F40(o, i);
                st[offsetof(TutorialSteps, step[0])] = 0;
                if (lbl_2_bss_F468._59[i] != 0) {
                    fn_800625A4(i, 0x1A);
                }
                break;
            }
            case 17:
                fn_2_7E974(o, i);
                if (st[offsetof(TutorialSteps, steps[2][1])] == 1) {
                    n = fn_80042DA8(o, i + 0xC, 0xA) != 0;
                    n += fn_80042DA8(o, i + 0xE, 0xE) != 0;
                    n += fn_80042DA8(o, i + 0x12, 0xA) != 0;
                    n += fn_80042DA8(o, i + 0x1C, 0x14) != 0;
                    n += fn_80042DA8(o, i + 0x6A, 0x1E) != 0;
                    if (n == 5) {
                        fn_80062674(i);
                        st[offsetof(TutorialSteps, steps[2][1])] = 2;
                    }
                }
                break;
            case 18:
                fn_2_7E380(o, i);
                if (st[offsetof(TutorialSteps, steps[2][1])] == 1) {
                    n = fn_80042DA8(o, i + 0x1C, 0xA) != 0;
                    n += fn_80042DA8(o, i + 0x6A, 0xA) != 0;
                    k = 3;
                    n += fn_80042DA8(o, i + 0x89, 5) != 0;
                    if (g_d_GameSettings._10 == 0 && i == 0) {
                        s32 player = lbl_8034E9A0.captain[1];
                        for (j = 0; j < 9; j++) {
                            if (TEAM_TBL->roster[1][j] == player) {
                                pos = TEAM_TBL->pos[1][j];
                            }
                        }
                        k = 4;
                        n += fn_80042DA8(o, pos + 0x3D, 0x14) != 0;
                    }
                    if (n == k) {
                        fn_80062674(i);
                        st[offsetof(TutorialSteps, steps[2][1])] = 2;
                    }
                }
                break;
            case 19:
                ((void (*)(MenuTask*, s32))fn_2_7A5B8)(o, i);
                if (st[offsetof(TutorialSteps, steps[2][1])] == 1) {
                    n = fn_80042DA8(o, i, 0x28) != 0;
                    n += fn_80042DA8(o, i + 2, 0x28) != 0;
                    n += fn_80042DA8(o, i + 0x85, 0x1E) != 0;
                    n += fn_80042DA8(o, i + 0x1C, 0x1E) != 0;
                    n += fn_80042DA8(o, i + 0x6A, 0x32) != 0;
                    if (n == 5) {
                        MN_SLOT(0xC + BASE(o) + i)->flags &= ~2;
                        MN_SLOT(0x12 + BASE(o) + i)->flags &= ~2;
                        fn_80062674(i);
                        st[offsetof(TutorialSteps, steps[2][1])] = 2;
                    }
                }
                break;
            case 20:
                ((void (*)(MenuTask*, s32))fn_2_7A194)(o, i);
                if (st[offsetof(TutorialSteps, steps[2][1])] == 1) {
                    s32 cur = lbl_2_bss_F468.prevCursor[i];
                    n = 0;
                    k = 0;
                    for (j = 0; j < 9; j++) {
                        if (TEAM_TBL->pos[i][j] == cur) {
                            f20 = j;
                            break;
                        }
                    }
                    if (TEAM_TBL->roster[i][f20] != -1 && TEAM_TBL->roster[i][f20] != 0x36 && cur < 9) {
                        k = 1;
                        n = fn_80042DA8(o, cur + i * 9 + 0x34, 0x14) != 0;
                    }
                    if (n == k) {
                        fn_80062674(i);
                        st[offsetof(TutorialSteps, steps[2][1])] = 2;
                    }
                }
                break;
            case 21:
                ((void (*)(MenuTask*, s32))fn_2_79CF8)(o, i);
                if (st[offsetof(TutorialSteps, steps[2][1])] == 1) {
                    s32 sel = lbl_2_bss_F468.cursor[i];
                    n = 0;
                    k = 0;
                    for (j = 0; j < 9; j++) {
                        if ((s8)sel == TEAM_TBL->pos[i][j]) {
                            f21 = j;
                            break;
                        }
                    }
                    if (TEAM_TBL->roster[i][f21] != -1) {
                        k = 1;
                        n = fn_80042DA8(o, (s8)sel + i * 9 + 0x34, 0xA) != 0;
                    }
                    if (n == k) {
                        fn_80062674(i);
                        st[offsetof(TutorialSteps, steps[2][1])] = 2;
                    }
                }
                break;
            case 22:
                ((void (*)(MenuTask*, s32))fn_2_79930)(o, i);
                if (st[offsetof(TutorialSteps, steps[2][1])] == 1) {
                    s32 hits = 0;
                    s32 total = 0;
                    for (j = 0; j < 9; j++) {
                        total++;
                        hits += fn_80042DA8(o, j + i * 9 + 0x34, 0x14) != 0;
                    }
                    if (fn_2_75B58(o, i) && hits == total) {
                        for (j = 0; j < 9; j++) {
                            if ((s8)lbl_803C6724[0x4A + i * 9 + j] == 0) {
                                lbl_803C6724[0x4A + i * 9 + j] = 1;
                            }
                        }
                        fn_80062674(i);
                        st[offsetof(TutorialSteps, steps[2][1])] = 2;
                    }
                }
                break;
            case 23:
                if (st[offsetof(TutorialSteps, steps[2][1])] == 0) {
                    for (j = 0; j < 9; j++) {
                        MN_SLOT(0x46 + BASE(o) + j + i * 9)->_68 = 4;
                    }
                    MN_SLOT(0x95 + BASE(o) + i)->_5C = 0xA0000;
                    MN_SLOT(0x95 + BASE(o) + i)->_68 = 1;
                }
                if (st[offsetof(TutorialSteps, steps[2][1])] == 1) {
                    fn_80062674(i);
                    st[offsetof(TutorialSteps, steps[2][1])] = 2;
                }
                break;
            case 24:
                fn_2_79394(o, i);
                break;
            case 25:
                fn_2_7912C(o, i);
                break;
            case 26:
                ((void (*)(MenuTask*, s32))fn_2_78F78)(o, i);
                break;
            case 27:
                fn_2_78AC0(o, i);
                break;
            case 28:
                fn_2_7836C(o, i);
                break;
            case 29:
                fn_2_7805C(o, i);
                break;
            }
            fn_2_776A0(o, i);
        }
        if (i != 0 && (MN_SLOT(6 + BASE(o))->_5C >> 16) == 0x3C) {
            MN_SLOT(7 + BASE(o))->_68 = 1;
            MN_SLOT(9 + BASE(o))->_68 = 1;
        }
    }
    if (lbl_8034E9A0._48B1 != 0) {
        fn_80034CEC(o);
        REMOVE_QUEUE_NOARG();
    }
}
#endif

// fn_2_7AE3C, size:0x11BC
// NONMATCHING 88%: same stores and calls; register allocation and some slot-index scheduling differ
#if NONMATCHING
void fn_2_7AE3C(MenuTask* o, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        s32 j;
        s8 cpos;
        s32 other;
        MN_SLOT(6 + BASE(o))->_68 = 1;
        MN_SLOT(8 + BASE(o))->_68 = 1;
        MN_SLOT(0x1C + BASE(o))->flags |= 2;
        MN_SLOT(0x1D + BASE(o))->flags |= 2;
        MN_SLOT(0x1E + BASE(o))->flags |= 2;
        MN_SLOT(0x1F + BASE(o))->flags |= 2;
        MN_SLOT(0x78 + BASE(o))->flags &= ~2;
        MN_SLOT(0x79 + BASE(o))->flags &= ~2;
        MN_SLOT(0x7C + BASE(o))->flags &= ~2;
        MN_SLOT(0x7D + BASE(o))->flags &= ~2;
        MN_SLOT(0x80 + BASE(o))->flags &= ~2;
        MN_SLOT(0x81 + BASE(o))->flags &= ~2;
        MN_SLOT(0x97 + BASE(o) + index)->_64 = 0x77;
        MN_SLOT(0x99 + BASE(o) + index)->_64 = 0x76;
        for (j = 0; j < 9; j++) {
            MN_SLOT(0x22 + BASE(o) + j + index * 9)->flags &= ~2;
        }
        MN_SLOT(BASE(o) + index)->_64 = 0x48;
        MN_SLOT(2 + BASE(o) + index)->_64 = 0x48;
        MN_SLOT(4 + BASE(o) + index)->_64 = 0x51;
        MN_SLOT(BASE(o) + index)->_5C = 0;
        MN_SLOT(2 + BASE(o) + index)->_5C = 0;
        MN_SLOT(4 + BASE(o) + index)->_5C = 0;
        MN_SLOT(BASE(o) + index)->_68 = 1;
        MN_SLOT(2 + BASE(o) + index)->_68 = 1;
        MN_SLOT(4 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x12 + BASE(o) + index)->_5C = 0xA0000;
        MN_SLOT(0x12 + BASE(o) + index)->_68 = 4;
        if (g_d_GameSettings.GameModeSelected != 5) {
            s32 captain;
            MN_SLOT(0x1C + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x1C + BASE(o) + index)->_68 = 1;
            captain = lbl_8034E9A0.captain[index];
            for (j = 0; j < 9; j++) {
                if (TEAM_TBL->roster[index][j] == captain) {
                    cpos = TEAM_TBL->pos[index][j];
                }
            }
            lbl_8034E9A0.captain[index] = captain; // the original writes it back
            for (j = 0; j < 9; j++) {
                s8 p = TEAM_TBL->pos[index][j];
                if (g_d_GameSettings._10 == 0 && lbl_2_bss_F468._37[index] == 0 && index == 1) {
                    // single player: only the CPU captain's marker is shown
                    if (j == cpos) {
                        other = (s8)lbl_8034E9A0.ports[0] == 0;
                        MN_SLOT(0x46 + BASE(o) + j + index * 9)->_64 = other + 0x11;
                        MN_SLOT(0x46 + BASE(o) + j + index * 9)->flags |= 2;
                    } else {
                        MN_SLOT(0x46 + BASE(o) + j + index * 9)->flags &= ~2;
                    }
                } else {
                    if (g_d_GameSettings._10 == 0) {
                        if ((s8)lbl_8034E9A0.ports[0] == 0) {
                            other = 1;
                        } else {
                            other = 0;
                        }
                    }
                    if (g_d_GameSettings._10 == 0 && index != 0) {
                        MN_SLOT(0x46 + BASE(o) + p + index * 9)->_64 = other + 0x11;
                    } else {
                        MN_SLOT(0x46 + BASE(o) + p + index * 9)->_64 = (s8)lbl_8034E9A0.ports[index] + 0x11;
                    }
                    MN_SLOT(0x46 + BASE(o) + p + index * 9)->_5C = 0;
                    MN_SLOT(0x46 + BASE(o) + p + index * 9)->flags |= 2;
                    MN_SLOT(0x46 + BASE(o) + p + index * 9)->_68 = 0;
                }
                if (TEAM_TBL->roster[index][j] != -1) {
                    MN_SLOT(0x34 + BASE(o) + p + index * 9)->flags |= 2;
                    if (j == lbl_2_bss_F468.cursor[index]) {
                        MN_SLOT(0x34 + BASE(o) + p + index * 9)->_5C = 0xA0000;
                        MN_SLOT(0x34 + BASE(o) + p + index * 9)->_68 = 0;
                        MN_SLOT(0x22 + BASE(o) + p + index * 9)->flags |= 2;
                        MN_SLOT(0x22 + BASE(o) + p + index * 9)->_68 = 1;
                    } else {
                        MN_SLOT(0x34 + BASE(o) + p + index * 9)->_5C = 0x140000;
                        MN_SLOT(0x34 + BASE(o) + p + index * 9)->_68 = 0;
                        MN_SLOT(0x22 + BASE(o) + p + index * 9)->flags &= ~2;
                    }
                    MN_SLOT(0x58 + BASE(o) + p + index * 9)->_5C = TEAM_TBL->roster[index][j] << 16;
                    MN_SLOT(0x58 + BASE(o) + p + index * 9)->_68 = 0;
                } else {
                    MN_SLOT(0x34 + BASE(o) + p + index * 9)->flags &= ~2;
                    MN_SLOT(0x22 + BASE(o) + p + index * 9)->flags &= ~2;
                }
            }
            MN_SLOT(0x6A + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x6A + BASE(o) + index)->_68 = 1;
            for (j = 0; j < 5; j++) {
                MN_SLOT(0x6E + BASE(o) + index * 5 + j)->_5C = 0;
                MN_SLOT(0x6E + BASE(o) + index * 5 + j)->_68 = 0;
            }
            if (g_d_GameSettings._10 != 0 || index == 0) {
                MN_SLOT(0x8F + BASE(o) + index)->_68 = 1;
                MN_SLOT(0x91 + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x91 + BASE(o) + index)->_68 = 1;
            }
        } else {
            MN_SLOT(0x80 + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x80 + BASE(o) + index)->_68 = 0;
            MN_SLOT(0x82 + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x82 + BASE(o) + index)->_68 = 0;
            MN_SLOT(0x78 + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x78 + BASE(o) + index)->_68 = 0;
            MN_SLOT(0x7A + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x7A + BASE(o) + index)->_68 = 0;
            MN_SLOT(0x97 + BASE(o) + index)->_64 = 0x77;
            MN_SLOT(0x98 + BASE(o))->flags &= ~2;
            MN_SLOT(0x97 + BASE(o))->_5C = 0;
            MN_SLOT(0x97 + BASE(o))->flags &= ~2;
            MN_SLOT(0xB0 + BASE(o) + index)->flags &= ~2;
            MN_SLOT(0x89 + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x89 + BASE(o) + index)->_68 = 1;
            MN_SLOT(0x85 + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x85 + BASE(o) + index)->_68 = 1;
            MN_SLOT(0x1C + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x1C + BASE(o) + index)->_68 = 1;
            if (g_d_GameSettings._10 == 0) {
                if ((s8)lbl_8034E9A0.ports[0] == 0) {
                    other = 1;
                } else {
                    other = 0;
                }
            }
            for (j = 0; j < 9; j++) {
                s8 p = TEAM_TBL->pos[index][j];
                if (index != 0) {
                    MN_SLOT(0x46 + BASE(o) + p + index * 9)->_64 = other + 0x11;
                } else {
                    MN_SLOT(0x46 + BASE(o) + p + index * 9)->_64 = (s8)lbl_8034E9A0.ports[index] + 0x11;
                }
                if (j == lbl_2_bss_F468.cursor[index]) {
                    MN_SLOT(0x46 + BASE(o) + p + index * 9)->flags |= 2;
                    MN_SLOT(0x46 + BASE(o) + p + index * 9)->_68 = 1;
                } else {
                    MN_SLOT(0x46 + BASE(o) + p + index * 9)->flags |= 2;
                    MN_SLOT(0x46 + BASE(o) + p + index * 9)->_68 = 0;
                }
                if (TEAM_TBL->roster[index][j] != -1) {
                    MN_SLOT(0x34 + BASE(o) + p + index * 9)->flags |= 2;
                    if (j == lbl_2_bss_F468.cursor[index]) {
                        MN_SLOT(0x34 + BASE(o) + p + index * 9)->_5C = 0xA0000;
                        MN_SLOT(0x34 + BASE(o) + p + index * 9)->_68 = 0;
                    } else {
                        MN_SLOT(0x34 + BASE(o) + p + index * 9)->_5C = 0x140000;
                        MN_SLOT(0x34 + BASE(o) + p + index * 9)->_68 = 0;
                    }
                    MN_SLOT(0x58 + BASE(o) + TEAM_TBL->pos[index][j] + index * 9)->_5C = TEAM_TBL->roster[index][j] << 16;
                    MN_SLOT(0x58 + BASE(o) + TEAM_TBL->pos[index][j] + index * 9)->_68 = 0;
                } else {
                    MN_SLOT(0x34 + BASE(o) + j + index * 9)->flags &= ~2;
                }
            }
            if (lbl_803CBBCC->prevScene == 0xB && index == 0 && g_d_GameSettings._10 == 0) {
                MN_SLOT(0x6A + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x6A + BASE(o) + index)->_68 = 0;
            } else {
                MN_SLOT(0x6A + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x6A + BASE(o) + index)->_68 = 1;
            }
            fn_2_75BE4(o, index);
        }
        if (lbl_803CBBCC->prevScene == 0xB || g_d_GameSettings.GameModeSelected == 5) {
            if (g_d_GameSettings.GameModeSelected != 5 || index == 0) {
                MN_SLOT(0x93 + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x93 + BASE(o) + index)->_68 = 1;
                MN_SLOT(0x95 + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x95 + BASE(o) + index)->_68 = 1;
            }
            if (g_d_GameSettings.GameModeSelected != 5) {
                MN_SLOT(0x8F + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x8F + BASE(o) + index)->_68 = 1;
                MN_SLOT(0x91 + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x91 + BASE(o) + index)->_68 = 0;
            }
        }
        if (lbl_2_bss_F468._3F != 0 && lbl_2_bss_F468._37[0] != 0 && g_d_GameSettings.GameModeSelected == 5) {
            if (index == 0) {
                MN_SLOT(0x93 + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x93 + BASE(o) + index)->_68 = 1;
                MN_SLOT(0x95 + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x95 + BASE(o) + index)->_68 = 1;
            } else {
                MN_SLOT(0x93 + BASE(o) + index)->flags &= ~2;
            }
        }
        fn_800626EC(index);
        *e = 1;
    }
}
#endif

extern u8 lbl_80108ED0[];

// fn_2_7BFF8, size:0x1864
// NONMATCHING 90%: same stores and calls; register allocation, a few constants CSE'd
#if NONMATCHING
void fn_2_7BFF8(MenuTask* o, s32 index) {
    u8* e = (u8*)&lbl_803C66B0 + index;
    s32 n;
    s32 k;
    if ((*(e += offsetof(TutorialSteps, steps[2][1])) == 0) ? 1 : 0) {
        s32 a;
        s32 b;
        u8 x;
        u8 y;
        s32 j;
        u8 cpos;
        s32 other;
        if (g_d_GameSettings.GameModeSelected != 5) {
            b = lbl_803C6724[index];
            a = lbl_800FE5D4[lbl_2_bss_F410.charSel[index]];
            b = lbl_800FE5D4[b];
        } else if (index != 0) {
            b = *(s8*)&CHALLENGE->_441F;
            a = b;
        } else {
            a = b = CHALLENGE->_441D;
        }
        x = lbl_8034E9A0.roster[a / 9][a % 9].stats.CaptainStarHitPitch;
        y = lbl_8034E9A0.roster[b / 9][b % 9].stats.CaptainStarHitPitch;
        MN_SLOT(0x82 + BASE(o) + index)->_5C = lbl_2_data_2B3A4[x] << 16;
        MN_SLOT(0x7E + BASE(o) + index)->_5C = lbl_2_data_2B3A4[x] << 16;
        fn_800363D8(o, index + 0x89, 1, 3, lbl_2_data_2B3A4[x]);
        fn_800363D8(o, index + 0x8B, 1, 3, lbl_2_data_2B3A4[y]);
        MN_SLOT(6 + BASE(o))->_68 = 1;
        MN_SLOT(8 + BASE(o))->_68 = 1;
        MN_SLOT(0x1A + BASE(o) + index)->flags |= 2;
        MN_SLOT(0x1A + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x89 + BASE(o) + index)->_5C = 0;
        MN_SLOT(0x89 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x85 + BASE(o) + index)->_5C = 0;
        MN_SLOT(0x85 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x82 + BASE(o) + index)->flags &= ~2;
        MN_SLOT(0x7A + BASE(o) + index)->flags &= ~2;
        MN_SLOT(0x82 + BASE(o) + index)->_5C = lbl_80108ED0[lbl_8034E9A0.captain[1]] << 16;
        MN_SLOT(0x7E + BASE(o) + index)->_5C = lbl_2_bss_F410.charSel[index] << 16;
        MN_SLOT(0x7A + BASE(o) + index)->_5C = (s8)lbl_8034E9A0.ports[1] << 16;
        MN_SLOT(0x84 + BASE(o))->flags &= ~2;
        MN_SLOT(0x97 + BASE(o) + index)->_64 = 0x77;
        MN_SLOT(0x97 + BASE(o) + index)->_5C = 0;
        MN_SLOT(0x97 + BASE(o) + index)->flags &= ~2;
        MN_SLOT(0xB0 + BASE(o) + index)->flags &= ~2;
        for (j = 0; j < 9; j++) {
            MN_SLOT(0x22 + BASE(o) + j + index * 9)->flags &= ~2;
        }
        MN_SLOT(BASE(o) + index)->_64 = 0x48;
        MN_SLOT(2 + BASE(o) + index)->_64 = 0x48;
        MN_SLOT(4 + BASE(o) + index)->_64 = 0x51;
        MN_SLOT(BASE(o) + index)->_5C = 0x280000;
        MN_SLOT(2 + BASE(o) + index)->_5C = 0x280000;
        MN_SLOT(4 + BASE(o) + index)->_5C = 0;
        MN_SLOT(BASE(o) + index)->_68 = 4;
        MN_SLOT(2 + BASE(o) + index)->_68 = 4;
        MN_SLOT(4 + BASE(o) + index)->_68 = 1;
        MN_SLOT(0x10 + BASE(o) + index)->_5C = (u8)lbl_8034E9A0.captainVariant[index] << 16;
        MN_SLOT(0x14 + BASE(o) + index)->_5C = (u8)lbl_8034E9A0.captainVariant[index] << 16;
        MN_SLOT(0x1C + BASE(o))->flags |= 2;
        MN_SLOT(0x1D + BASE(o))->flags |= 2;
        MN_SLOT(0x1E + BASE(o))->flags |= 2;
        MN_SLOT(0x1F + BASE(o))->flags |= 2;
        MN_SLOT(0x78 + BASE(o))->flags &= ~2;
        MN_SLOT(0x79 + BASE(o))->flags &= ~2;
        MN_SLOT(0x7C + BASE(o))->flags &= ~2;
        MN_SLOT(0x7D + BASE(o))->flags &= ~2;
        MN_SLOT(0x80 + BASE(o))->flags &= ~2;
        MN_SLOT(0x81 + BASE(o))->flags &= ~2;
        if (g_d_GameSettings.GameModeSelected != 5) {
            s32 captain;
            MN_SLOT(4 + BASE(o) + index)->_5C = 0;
            MN_SLOT(4 + BASE(o) + index)->_68 = 1;
            if (g_d_GameSettings._10 == 0 && index == 0) {
                MN_SLOT(0x1C + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x1C + BASE(o) + index)->_68 = 0;
                MN_SLOT(0xC + BASE(o) + index)->_5C = 0x140000;
                MN_SLOT(0xC + BASE(o) + index)->_68 = 4;
                MN_SLOT(0xE + BASE(o) + index)->_5C = 0x180000;
                MN_SLOT(0xE + BASE(o) + index)->_68 = 4;
                MN_SLOT(0x12 + BASE(o) + index)->_5C = 0x140000;
                MN_SLOT(0x12 + BASE(o) + index)->_68 = 4;
            } else {
                MN_SLOT(0x1C + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x1C + BASE(o) + index)->_68 = 1;
                MN_SLOT(0x89 + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x89 + BASE(o) + index)->_68 = 1;
                MN_SLOT(0x97 + BASE(o) + index)->flags &= ~2;
                MN_SLOT(0xC + BASE(o) + index)->flags |= 2;
                MN_SLOT(0x12 + BASE(o) + index)->flags |= 2;
                MN_SLOT(0xC + BASE(o) + index)->_5C = 0x140000;
                MN_SLOT(0xC + BASE(o) + index)->_68 = 1;
                MN_SLOT(0xE + BASE(o) + index)->_5C = 0x180000;
                MN_SLOT(0xE + BASE(o) + index)->_68 = 4;
                MN_SLOT(0x12 + BASE(o) + index)->_5C = 0x140000;
                MN_SLOT(0x12 + BASE(o) + index)->_68 = 1;
            }
            MN_SLOT(0x6A + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x6A + BASE(o) + index)->_68 = 1;
            captain = lbl_8034E9A0.captain[index];
            for (j = 0; j < 9; j++) {
                if (TEAM_TBL->roster[index][j] == captain) {
                    cpos = TEAM_TBL->pos[index][j];
                }
            }
            lbl_8034E9A0.captain[index] = captain; // the original writes it back
            for (j = 0; j < 9; j++) {
                if (g_d_GameSettings._10 == 0 && lbl_2_bss_F468._37[index] == 0 && index == 1) {
                    if (j == cpos) {
                        other = (s8)lbl_8034E9A0.ports[0] == 0;
                        MN_SLOT(0x46 + BASE(o) + j + index * 9)->_64 = other + 0x11;
                        MN_SLOT(0x46 + BASE(o) + j + index * 9)->flags |= 2;
                    } else {
                        MN_SLOT(0x46 + BASE(o) + j + index * 9)->flags &= ~2;
                    }
                } else {
                    if (g_d_GameSettings._10 == 0) {
                        if ((s8)lbl_8034E9A0.ports[0] == 0) {
                            other = 1;
                        } else {
                            other = 0;
                        }
                    }
                    if (g_d_GameSettings._10 == 0 && index != 0) {
                        MN_SLOT(0x46 + BASE(o) + j + index * 9)->_64 = other + 0x11;
                    } else {
                        MN_SLOT(0x46 + BASE(o) + j + index * 9)->_64 = (s8)lbl_8034E9A0.ports[index] + 0x11;
                    }
                    MN_SLOT(0x46 + BASE(o) + j + index * 9)->_5C = 0;
                    MN_SLOT(0x46 + BASE(o) + j + index * 9)->flags |= 2;
                    MN_SLOT(0x46 + BASE(o) + j + index * 9)->_68 = 0;
                }
                if (TEAM_TBL->roster[index][j] != -1) {
                    MN_SLOT(0x34 + BASE(o) + j + index * 9)->flags |= 2;
                    if (j == lbl_2_bss_F468.cursor[index]) {
                        MN_SLOT(0x34 + BASE(o) + j + index * 9)->_5C = 0xA0000;
                        MN_SLOT(0x34 + BASE(o) + j + index * 9)->_68 = 0;
                    } else {
                        MN_SLOT(0x34 + BASE(o) + j + index * 9)->_5C = 0x140000;
                        MN_SLOT(0x34 + BASE(o) + j + index * 9)->_68 = 0;
                    }
                    MN_SLOT(0x58 + BASE(o) + TEAM_TBL->pos[index][j] + index * 9)->_5C = TEAM_TBL->roster[index][j] << 16;
                    MN_SLOT(0x58 + BASE(o) + TEAM_TBL->pos[index][j] + index * 9)->_68 = 0;
                } else {
                    MN_SLOT(0x34 + BASE(o) + j + index * 9)->flags &= ~2;
                }
            }
            fn_2_75BE4(o, index);
            if (g_d_GameSettings._10 != 0 || index == 0) {
                MN_SLOT(0x93 + BASE(o) + index)->_68 = 1;
                MN_SLOT(0x95 + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x91 + BASE(o) + index)->_68 = 1;
                MN_SLOT(0x8F + BASE(o) + index)->_68 = 1;
                MN_SLOT(0x91 + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x91 + BASE(o) + index)->_68 = 0;
            }
            MN_SLOT(0xAE + BASE(o))->flags |= 2;
            MN_SLOT(0xAF + BASE(o))->flags |= 2;
        } else {
            MN_SLOT(0x1C + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x1C + BASE(o) + index)->_68 = 1;
            MN_SLOT(0x89 + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x89 + BASE(o) + index)->_68 = 1;
            if (g_d_GameSettings._10 == 0) {
                if ((s8)lbl_8034E9A0.ports[0] == 0) {
                    other = 1;
                } else {
                    other = 0;
                }
            }
            for (j = 0; j < 9; j++) {
                if (index != 0) {
                    MN_SLOT(0x46 + BASE(o) + j + index * 9)->_64 = other + 0x11;
                } else {
                    MN_SLOT(0x46 + BASE(o) + j + index * 9)->_64 = (s8)lbl_8034E9A0.ports[index] + 0x11;
                }
                MN_SLOT(0x46 + BASE(o) + j + index * 9)->_5C = 0;
                if (j == lbl_2_bss_F468.cursor[index]) {
                    MN_SLOT(0x46 + BASE(o) + j + index * 9)->flags |= 2;
                    MN_SLOT(0x46 + BASE(o) + j + index * 9)->_68 = 1;
                } else {
                    MN_SLOT(0x46 + BASE(o) + j + index * 9)->flags |= 2;
                    MN_SLOT(0x46 + BASE(o) + j + index * 9)->_68 = 0;
                }
                if (TEAM_TBL->roster[index][j] != -1) {
                    MN_SLOT(0x34 + BASE(o) + j + index * 9)->flags |= 2;
                    if (j == lbl_2_bss_F468.cursor[index]) {
                        MN_SLOT(0x34 + BASE(o) + j + index * 9)->_5C = 0xA0000;
                        MN_SLOT(0x34 + BASE(o) + j + index * 9)->_68 = 0;
                    } else {
                        MN_SLOT(0x34 + BASE(o) + j + index * 9)->_5C = 0x140000;
                        MN_SLOT(0x34 + BASE(o) + j + index * 9)->_68 = 0;
                    }
                    MN_SLOT(0x58 + BASE(o) + TEAM_TBL->pos[index][j] + index * 9)->_5C = TEAM_TBL->roster[index][j] << 16;
                    MN_SLOT(0x58 + BASE(o) + TEAM_TBL->pos[index][j] + index * 9)->_68 = 0;
                } else {
                    MN_SLOT(0x34 + BASE(o) + j + index * 9)->flags &= ~2;
                }
            }
            fn_2_75BE4(o, index);
            MN_SLOT(0x6A + BASE(o) + index)->_5C = 0xA0000;
            MN_SLOT(0x6A + BASE(o) + index)->_68 = 1;
        }
        if (lbl_803CBBCC->prevScene == 0xB) {
            if (g_d_GameSettings.GameModeSelected != 5) {
                u8 s93;
                u8 s95;
                u8 s8f;
                if (index == 0 && g_d_GameSettings._10 == 0) {
                    s93 = 0;
                    s95 = 0;
                    s8f = 0;
                } else {
                    s93 = 1;
                    s95 = 1;
                    s8f = 1;
                }
                MN_SLOT(0x93 + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x93 + BASE(o) + index)->_68 = s93;
                MN_SLOT(0x95 + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x95 + BASE(o) + index)->_68 = s95;
                MN_SLOT(0x8F + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x8F + BASE(o) + index)->_68 = s8f;
                MN_SLOT(0x91 + BASE(o) + index)->_5C = 0;
                MN_SLOT(0x91 + BASE(o) + index)->_68 = 0;
            } else {
                if (index == 1) {
                    MN_SLOT(0x93 + BASE(o) + index)->flags &= ~2;
                } else {
                    MN_SLOT(0x93 + BASE(o) + index)->flags |= 2;
                    MN_SLOT(0x93 + BASE(o) + index)->_5C = 0;
                    MN_SLOT(0x93 + BASE(o) + index)->_68 = 1;
                    MN_SLOT(0x95 + BASE(o) + index)->_5C = 0;
                    MN_SLOT(0x95 + BASE(o) + index)->_68 = 1;
                }
                MN_SLOT(0x8F + BASE(o) + index)->flags &= ~2;
            }
        }
        if (lbl_2_bss_F468._3F != 0 && lbl_2_bss_F468._37[0] != 0 && index == 0 &&
            g_d_GameSettings.GameModeSelected == 5) {
            MN_SLOT(0x93 + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x93 + BASE(o) + index)->_68 = 1;
            MN_SLOT(0x95 + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x95 + BASE(o) + index)->_68 = 1;
            MN_SLOT(0x8F + BASE(o) + index)->_68 = 1;
            MN_SLOT(0x91 + BASE(o) + index)->_5C = 0;
            MN_SLOT(0x91 + BASE(o) + index)->_68 = 0;
        }
        fn_800626EC(index);
        *e = 1;
    }
    if (*e == 1) {
        s32 hit;
        if (g_d_GameSettings.GameModeSelected != 5) {
            n = fn_80042DA8(o, index, 0x14) != 0;
            n += fn_80042DA8(o, index + 2, 0x14) != 0;
            if (g_d_GameSettings._10 == 0 && index == 0) {
                n += fn_80042DA8(o, index + 0x6A, 0x1E) != 0;
                n += fn_80042DA8(o, index + 0xC, 0xA) != 0;
                n += fn_80042DA8(o, index + 0xE, 0xE) != 0;
                k = 6;
                n += fn_80042DA8(o, index + 0x12, 0xA) != 0;
            } else {
                n += fn_80042DA8(o, index + 0x1C, 0xA) != 0;
                n += fn_80042DA8(o, index + 0x6A, 0xA) != 0;
                n += fn_80042DA8(o, index + 0xC, 0x1E) != 0;
                n += fn_80042DA8(o, index + 0xE, 0xE) != 0;
                n += fn_80042DA8(o, index + 0x12, 0x1E) != 0;
                k = 8;
                n += fn_80042DA8(o, index + 0x89, 5) != 0;
            }
        } else {
            n = fn_80042DA8(o, index, 0x14) != 0;
            n += fn_80042DA8(o, index + 2, 0x14) != 0;
            n += fn_80042DA8(o, index + 0x1C, 0xA) != 0;
            n += fn_80042DA8(o, index + 0x6A, 0xA) != 0;
            k = 5;
            n += fn_80042DA8(o, index + 0x89, 5) != 0;
        }
        hit = n + (fn_80042DA8(o, index + 0x85, 0xA) != 0);
        if (fn_2_75B58(o, index) && hit == k + 1) {
            fn_80062674(index);
            *e = 2;
        }
    }
}
#endif
