#include "game/auto_00_0011D3AC_text.h"
#ifdef PORT_LP64
MinigameAssetPtrs g_port_mgAssets;
#endif
#include "main/SpaniDesc.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "static/GameSettings.h"
#include "game/rep_2BF8.h"
#include "game/rep_1838.h"

extern MinigameAssets lbl_3_common_bss_32724;
extern MinigameCharMgrAssets lbl_8036E548;
extern PasswordSlot lbl_80371C30[];
extern void* lbl_803CC1B8; // current queue task
#include "main/aramloader.h" // ARAMLoader lbl_803C6CF8
extern MinigamePauseView lbl_3_common_bss_34C90;
extern u8 lbl_800EFBA4[];
extern AssetLoadInstructions lbl_3_data_225F0[3]; // ARAM load records (rep_3310)
extern SpaniDesc lbl_3_data_25464[46];        // sprite descriptors (fn_80034E20)
extern SpaniDesc lbl_3_data_25A24[38];
extern SpaniDesc lbl_3_data_25EE4[23];
extern SpaniDesc lbl_3_data_26254[19];
extern u8 lbl_3_data_261C4[9][16];   // password digit substitution tables
extern u16 lbl_3_data_81FC[];        // sound ids

extern void LoadActorLayout(void* layout);
extern void convertGeometryAndSknHeader(void* geometry, void* skin);
extern void fn_80034E20(void* group, void* descs);
extern void fn_3_109DE0(PasswordRecord* out);
extern s32 fn_3_107988(u32 pick);
extern s32 fn_3_107C88(void);
extern u8 fn_3_107CD0(void);
extern u32 fn_3_90064(s32 id);
extern s32 sndFXKeyOff(u32 voice);
extern s32 sndFXCtrl(u32 voice, u8 ctrl, u8 value);
extern s32 sndFXStartEx(u16 fid, u8 vol, u8 pan, u8 studio);

#define MG11D3 ((MG11D3View*)&g_Minigame)
#define SPRITE(task, n) (lbl_80371C30[(task)->baseIdx + (n)].obj)
// Sprite k + i of a task; this operand order is what the original compiles to.
#define SPRITE_I(task, k, i) (lbl_80371C30[(k) + (task)->baseIdx + (i)].obj)

// .text:0x0011D3AC size:0x2F4 mapped:0x8075C440
// Relocates the result-screen asset file loaded from ARAM.
// NONMATCHING 78%: relocation loop index/base registers differ and the remainder-loop guard is placed differently
#if NONMATCHING
void fn_3_11D3AC(void) {
    u32* file;
    s32 i;
    s32 k;
    s32 skip;

    file = lbl_8036E548.file;
#ifdef TARGET_PC
    port_swap_offset_table(file, 81 + 9); // 27 actor sets, then 9 result-screen files
#endif
    lbl_8036E548._3078 = 0;
    for (i = 0; i < 81; i++) {
        lbl_8036E548.data.ptr[i] = (u8*)file + file[i];
    }
    MG_ASSETS.model = (u8*)file + file[i++];
    MG_ASSETS.anim.set = (void*)((u8*)file + file[i++]);
    MG_ASSETS.skin = (u8*)file + file[i++];
    MG_ASSETS.animBanks[0] = (ANIMBank*)((u8*)file + file[i++]);
    ANIMGet(MG_ASSETS.animBanks[0]);
    MG_ASSETS.animBanks[1] = (ANIMBank*)((u8*)file + file[i++]);
    ANIMGet(MG_ASSETS.animBanks[1]);
    MG_ASSETS.animBanks[2] = (ANIMBank*)((u8*)file + file[i++]);
    ANIMGet(MG_ASSETS.animBanks[2]);
    MG_ASSETS.textures[0] = (u8*)file + file[i++];
    MG_ASSETS.textures[1] = (u8*)file + file[i++];
    MG_ASSETS.textures[2] = (u8*)file + file[i++];

    for (k = 0; k < 27; k++) {
        void* layout = lbl_8036E548.data.actor[k].layout;
        void* geometry = lbl_8036E548.data.actor[k].geometry;
        void* textures = lbl_8036E548.data.actor[k].textures;

        LoadActorLayout(layout);
        if (k == 17) {
            convertGeometryAndSknHeader(geometry, MG_ASSETS.skin);
        } else {
            convertGeometryAndSknHeader(geometry, NULL);
        }
        haveActLayoutPointToGeoHeader(layout, geometry);
        convertTextureHeader(textures);
        fn_800BD190(geometry, textures);
    }

    skip = 0;
    fn_80025DDC(MG_ASSETS.model);
    fn_80025FFC(MG_ASSETS.model, &MG_ASSETS.anim);
    fn_80025EEC(&MG_ASSETS.anim, 0, 0);
    if (skip == 0) {
        MG_ASSETS.anim.state.loops = 1;
    }
    convertTextureHeader(MG_ASSETS.textures[0]);
    convertTextureHeader(MG_ASSETS.textures[1]);
    convertTextureHeader(MG_ASSETS.textures[2]);
}
#endif

// .text:0x0011D6A0 size:0xE0 mapped:0x8075C734
// Loads the result-screen assets; returns 1 once done.
s32 fn_3_11D6A0(void) {
    switch (lbl_3_common_bss_32724.loadState) {
    case 0:
        lbl_8036E548.file = (u32*)ARAMTransfer(&lbl_3_data_225F0[1], 0, 0, 0);
        lbl_3_common_bss_32724.loadState++;
        break;
    case 1:
        if ((s32)lbl_803C6CF8.idle == 1) {
            lbl_3_common_bss_32724.loadState++;
        }
        break;
    case 2:
        if (g_d_GameSettings.GameModeSelected != 6) {
            fn_3_11D3AC();
        }
        lbl_3_common_bss_32724.loadState++;
        break;
    default:
        return 1;
    }
    return 0;
}

// .text:0x0011D780 size:0x34C mapped:0x8075C814
// Password display task.
void fn_3_11D780(void) {
    PasswordTask* task = lbl_803CC1B8;
    u8 raw[8];
    u8 code[16];
    u32 i;

    if (lbl_3_common_bss_32724.quit != 0) {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    if (g_Minigame._1A3C != 0) {
        if (g_GameLogic._125 == 4) {
            fn_80034CEC(task);
            REMOVE_QUEUE_NOARG();
            return;
        }
        if (g_GameLogic.gameStatus != 0x24) {
            fn_80034CEC(task);
            REMOVE_QUEUE_NOARG();
            return;
        }
    } else {
        if (g_GameLogic._125 == 3) {
            fn_80034CEC(task);
            REMOVE_QUEUE_NOARG();
            return;
        }
        if (g_GameLogic.gameStatus != 0xE) {
            fn_80034CEC(task);
            REMOVE_QUEUE_NOARG();
            return;
        }
    }
    if (g_Minigame._1907 != 1) {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }

    switch (task->state) {
    case 0:
        fn_80034E20(task, lbl_3_data_26254);
        if (g_Minigame._1A3C != 0) {
            SPRITE(task, 0)->anim = 0xBF;
            task->_1E = 3;
        } else {
            SPRITE(task, 0)->anim = 0xBE;
            task->_1E = 7;
        }
        task->bits = random_fn_3_9EE24(0x100);
        task->key = random_fn_3_9EE24(0x1A);
        task->state = 1;
        // fallthrough
    case 1:
        fn_3_11DACC(code, raw, task->bits, task->key);
        i = 0;
        do {
            fn_800363D8(task, i + 2, 1, 0xBD, code[i]);
            fn_800363D8(task, i + 2, 2, 0xBD, code[i]);
            i++;
        } while (i < 16);
        task->state = 2;
        break;
    case 2:
        if (g_GameLogic._125 == task->_1E) {
            SPRITE(task, 0)->visible = 1;
            SPRITE(task, 0)->frame = 0;
            SPRITE(task, 1)->visible = 1;
            SPRITE(task, 1)->frame = 0;
            i = 0;
            do {
                SPRITE_I(task, 2, i)->frame = 0;
                i++;
            } while (i < 16);
            task->state = 3;
        }
        break;
    case 3:
        if (g_GameLogic._125 != task->_1E) {
            SPRITE(task, 0)->visible = 4;
            SPRITE(task, 0)->frame = 0x140000;
            SPRITE(task, 1)->visible = 4;
            task->state = 2;
        }
        break;
    }
}

// .text:0x0011DACC size:0x2F8 mapped:0x8075CB60
// Builds the 16-digit password: packs the record into raw[8], CRCs it and scatters
// the bits over the digits, then substitutes each digit through a table chosen by key.
// NONMATCHING 88%: the original keeps an empty 5-iteration loop (dead code) that CW drops here; one extra saved register
#if NONMATCHING
void fn_3_11DACC(u8* code, u8* raw, u8 bits, u8 key) {
    PasswordRecord rec;
    u32 score;
    u32 value;
    u32 i;
    u32 crc;
    u32 flags;
    s16 charID;
    u32 random;

    fn_3_109DE0(&rec);
    if (g_Minigame._1A3C != 0) {
        score = rec.score;
        random = 1;
        value = random_fn_3_9EE24(1000);
    } else {
        score = rec.score;
        random = 0;
        value = rec.value;
    }
    if (score > 9999) {
        score = 9999;
    }
    if (value > 999) {
        value = 999;
    }
    charID = charID;
    flags = bits;
    raw[0] = random;
    raw[1] = score;
    raw[2] = score >> 8;
    raw[3] = value;
    raw[4] = value >> 8;
    raw[5] = charID = rec.charID;
    raw[6] = 0;
    raw[7] = bits;

    crc = fn_3_11DDC4(raw, 8);

    code[0] = key;
    code[1] = crc & 3;
    i = 2;
    do {
        code[i] = (crc >> i) & 1;
        i++;
    } while (i < 16);
    code[1] |= (flags & 1) << 2;
    i = 1;
    do {
        code[i * 2 + 1] |= ((flags >> i) & 1) << 1;
        i++;
    } while (i < 8);
    i = 0;
    do {
        code[i * 2 + 2] |= ((score >> (i * 2)) & 3) << 1;
        i++;
    } while (i < 7);
    code[1] |= random << 3;
    // The original has an empty 5-iteration loop here (dead code).
    i = 0;
    do {
        code[i * 2 + 3] |= ((value >> (i * 2)) & 3) << 2;
        i++;
    } while (i < 5);
    code[12] |= (charID & 1) << 3;
    code[13] |= (charID << 1) & 0xC;
    code[14] |= charID & 8;
    code[15] |= (charID >> 2) & 0xC;
    i = 1;
    do {
        code[i] = lbl_3_data_261C4[code[0] % 9][code[i]];
        i++;
    } while (i < 16);
}
#endif

// .text:0x0011DDC4 size:0xBC mapped:0x8075CE58
// CRC-16 (reflected CCITT polynomial 0x8408, initial value 0).
u16 fn_3_11DDC4(u8* data, u32 len) {
    u32 crc = 0;
    u32 b;
    u32 i;
    u32 j;

    for (i = 0; i < len; i++, data++) {
        b = *data;
        for (j = 0; j < 8; j++) {
            if ((crc ^ b) & 1) {
                crc >>= 1;
                crc ^= 0x8408;
            } else {
                crc >>= 1;
            }
            b >>= 1;
        }
    }
    return crc;
}

// .text:0x0011DE80 size:0x4C mapped:0x8075CF14
void fn_3_11DE80(void) {
    if (g_GameLogic._125 == 0) {
#ifdef TARGET_PC
        PTR32_SET(MG11D3->rouletteTask, fn_800B0A5C_insertQueue(fn_3_11DECC, 2));
#else
        MG11D3->rouletteTask = fn_800B0A5C_insertQueue(fn_3_11DECC, 2);
#endif
    }
}

// .text:0x0011DECC size:0x43C mapped:0x8075CF60
// Round roulette task: spins six panels and stops on this round's pick.
// NONMATCHING 98%: the original keeps two copies of the task pointer (r30/r28) and tests animState == 2 via cntlzw
#if NONMATCHING
void fn_3_11DECC(void) {
    PasswordTask* task = lbl_803CC1B8;
    PasswordTask* t = task;
    u32 i;
    u32 pick;

    if (g_GameLogic._125 == 4) {
        if (task->state != 0 && task->sfx != 0xFFFFFFFF) {
            sndFXKeyOff(task->sfx);
            sndFXCtrl(task->sfx, 7, 0);
            task->sfx = 0xFFFFFFFF;
        }
        MG11D3->rouletteTask = 0;
        fn_80034CEC(t);
        REMOVE_QUEUE_NOARG();
        return;
    }

    switch (task->state) {
    case 0:
        fn_80034E20(task, lbl_3_data_25EE4);
        if (MG11D3->round >= 1) {
            t->_1E = MG11D3->roundPick[MG11D3->round - 1] - 1;
        }
        task->sfx = 0xFFFFFFFF;
        t->state = 1;
        break;
    case 1:
        if ((SPRITE(task, 3)->frame >> 16) == 0x37) {
            SPRITE(task, 3)->visible = 0;
            task->state = 2;
        }
        break;
    case 2:
        SPRITE(task, 3)->visible = 1;
        i = 0;
        do {
            SPRITE_I(t, 4, i)->visible = 1;
            i++;
        } while (i < 6);
        task->sfx = fn_3_90064(lbl_3_data_81FC[0x23]);
        t->state = 3;
        break;
    case 3:
        if (SPRITE(task, 3)->animState == 2) {
            SPRITE(task, 3)->frame = 0x370000;
            i = 0;
            do {
                SPRITE_I(t, 4, i)->frame = 0;
                i++;
            } while (i < 6);
            t->_1E--;
            if ((s16)t->_1E < 0) {
                t->_1E = 5;
            }
            if (t->_1E == MG11D3->roundPick[MG11D3->round - 1] - 1) {
                t->spins++;
                if (t->spins >= 2) {
                    SPRITE(t, 3)->visible = 0;
                    i = 0;
                    do {
                        SPRITE_I(t, 4, i)->visible = 0;
                        i++;
                    } while (i < 6);
                    t->state = 4;
                }
            }
        }
        break;
    case 4:
        sndFXKeyOff(task->sfx);
        sndFXCtrl(task->sfx, 7, 0);
        task->sfx = 0xFFFFFFFF;
        fn_3_90064(lbl_3_data_81FC[0x24]);
        SPRITE(t, 10)->visible = 1;
        t->state = 5;
        break;
    case 5:
        if (SPRITE(task, 10)->animState == 2) {
            task->state = 6;
        }
        break;
    case 6:
        task->done = 1;
        break;
    }

    i = 0;
    do {
        pick = (t->_1E + i) % 6 + 1;
        SPRITE_I(t, 10, i)->child = SPRITE(t, pick + 15);
        SPRITE(t, pick + 15)->link = SPRITE_I(t, 10, i);
        if (SPRITE_I(t, 10, i)->visible == 0) {
            SPRITE_I(t, 10, i)->frame = (fn_3_107988(pick) == 0) << 16;
        }
        i++;
    } while (i < 6);
}
#endif

// .text:0x0011E308 size:0x5C mapped:0x8075D39C
void fn_3_11E308(void) {
    if (g_GameLogic._125 == 1 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
        ((ResultsTask*)fn_800B0A5C_insertQueue(fn_3_E911C, 2))->mode = 1;
    }
}

// The score boards close when the minigame quits, ends or a pause menu leaves it.
static inline u32 ScoreBoard_ShouldClose(void) {
    if (lbl_3_common_bss_32724.quit != 0 || lbl_3_common_bss_32724._B7 != 0) {
        return 1;
    }
    if (g_GameLogic.gameStatus == 0xF) {
        return 1;
    }
    if (g_Minigame.pauseInd != 0) {
        u8 menu = lbl_3_common_bss_34C90.state;

        if (menu == 7 || menu == 9) {
            return 1;
        }
        if (menu == 13) {
            return 1;
        }
    }
    if (g_GameLogic.gameStatus == 0xE && g_GameLogic.FrameCountOfCurrentPitch == 0) {
        return 1;
    }
    return 0;
}

// .text:0x0011E364 size:0x460 mapped:0x8075D3F8
// Score board (four players): counts the shown points toward the real ones.
// NONMATCHING 94%: the original strength-reduces i*3+0x15/16/17 into separate registers (one more saved reg) and does not mask fn_3_107CD0's u8 result
#if NONMATCHING
void fn_3_11E364(void) {
    ScoreBoardTask* task = lbl_803CC1B8;
    u32 changed = 0;
    u32 i;
    u32 shown;
    u32 leader;
    s32 noTie;
    s32 diff;

    if (ScoreBoard_ShouldClose()) {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    switch (task->state) {
    case 0:
        fn_80034E20(task, lbl_3_data_25A24);
        i = 0;
        do {
            fn_800363D8(task, i + 9, 1, 0x65, i);
            SPRITE_I(task, 0x11, i)->frame = inMemRoster[0][i].stats.CharID << 16;
            i++;
        } while (i < 4);
        i = 0;
        do {
            SPRITE_I(task, 0x21, i)->flags &= ~2;
            i++;
        } while (i < 4);
        task->state = 1;
        break;
    case 1:
        leader = fn_3_107CD0();
        noTie = fn_3_107C88();
        i = 0;
        do {
            if (MG11D3->hit[i] != 0) {
                MG11D3->hit[i] = 0;
                SPRITE_I(task, 1, i)->frame = 0;
                SPRITE_I(task, 1, i)->visible = 1;
            }
            diff = g_Minigame.miniGameCurrentPoints[i] - g_Minigame.minigamePoints_current_Latest[i].current;
            if (diff > 0) {
                g_Minigame.minigamePoints_current_Latest[i].current++;
                changed = 1;
                task->counting[i] = 1;
            } else if (diff < 0) {
                changed = 1;
                g_Minigame.minigamePoints_current_Latest[i].current--;
            } else if (task->counting[i] != 0) {
                task->counting[i] = 0;
                SPRITE(task, i * 3 + 0x15)->frame = 0;
                SPRITE(task, i * 3 + 0x16)->frame = 0;
                SPRITE(task, i * 3 + 0x17)->frame = 0;
            }
            shown = g_Minigame.minigamePoints_current_Latest[i].current;
            if (shown > 999) {
                shown = 999;
            }
            fn_800363D8(task, i * 3 + 0x15, 1, 0x66, (shown % 1000) / 100);
            fn_800363D8(task, i * 3 + 0x16, 1, 0x66, (shown % 100) / 10);
            fn_800363D8(task, i * 3 + 0x17, 1, 0x66, shown % 10);
            if (noTie == 0 && g_Minigame.minigamePoints_current_Latest[i].current ==
                                  g_Minigame.minigamePoints_current_Latest[leader].current) {
                SPRITE_I(task, 0x21, i)->flags |= 2;
            } else {
                SPRITE_I(task, 0x21, i)->flags &= ~2;
            }
            i++;
        } while (i < 4);
        break;
    }
    if (changed != 0) {
        sndFXStartEx(0x1C0, lbl_800EFBA4[9], 0x3F, 0);
    }
}
#endif

// .text:0x0011E7C4 size:0x464 mapped:0x8075D858
// Score board variant: also flashes a marker when a player's count finishes.
// NONMATCHING 95%: same differences as fn_3_11E364
#if NONMATCHING
void fn_3_11E7C4(void) {
    ScoreBoardTask* task = lbl_803CC1B8;
    u32 i;
    u32 shown;
    u32 leader;
    s32 noTie;
    s32 diff;

    if (ScoreBoard_ShouldClose()) {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    switch (task->state) {
    case 0:
        fn_80034E20(task, lbl_3_data_25464);
        i = 0;
        do {
            fn_800363D8(task, i + 9, 1, 0x65, i);
            SPRITE_I(task, 0x11, i)->frame = inMemRoster[0][i].stats.CharID << 16;
            i++;
        } while (i < 4);
        i = 0;
        do {
            SPRITE_I(task, 0x29, i)->flags &= ~2;
            i++;
        } while (i < 4);
        task->state = 1;
        break;
    case 1:
        leader = fn_3_107CD0();
        noTie = fn_3_107C88();
        i = 0;
        do {
            if (MG11D3->hit[i] != 0) {
                MG11D3->hit[i] = 0;
                SPRITE_I(task, 1, i)->frame = 0;
                SPRITE_I(task, 1, i)->visible = 1;
            }
            diff = g_Minigame.miniGameCurrentPoints[i] - g_Minigame.minigamePoints_current_Latest[i].current;
            if (diff > 0) {
                g_Minigame.minigamePoints_current_Latest[i].current++;
                task->counting[i] = 1;
            } else if (diff < 0) {
                g_Minigame.minigamePoints_current_Latest[i].current--;
            } else if (task->counting[i] != 0) {
                task->counting[i] = 0;
                SPRITE_I(task, 0x19, i)->frame = 0;
                SPRITE_I(task, 0x19, i)->visible = 1;
                SPRITE(task, i * 3 + 0x1D)->frame = 0;
                SPRITE(task, i * 3 + 0x1E)->frame = 0;
                SPRITE(task, i * 3 + 0x1F)->frame = 0;
            }
            shown = g_Minigame.minigamePoints_current_Latest[i].current;
            if (shown > 999) {
                shown = 999;
            }
            fn_800363D8(task, i * 3 + 0x1D, 1, 0x66, (shown % 1000) / 100);
            fn_800363D8(task, i * 3 + 0x1E, 1, 0x66, (shown % 100) / 10);
            fn_800363D8(task, i * 3 + 0x1F, 1, 0x66, shown % 10);
            if (noTie == 0 && g_Minigame.minigamePoints_current_Latest[i].current ==
                                  g_Minigame.minigamePoints_current_Latest[leader].current) {
                SPRITE_I(task, 0x29, i)->flags |= 2;
            } else {
                SPRITE_I(task, 0x29, i)->flags &= ~2;
            }
            i++;
        } while (i < 4);
        break;
    }
}
#endif
