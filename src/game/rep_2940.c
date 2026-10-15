#include "game/rep_2940.h"
#define REP_HEADER_FN repHeader_2940
#include "header_rep_inline.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_80011640.h"
#include "main/file_8000F150.h"
#include "main/file_8004207C.h"
#include "game/rep_FE0.h"
#include "game/rep_F80.h"

extern void fn_3_6A25C(void);
extern void fn_3_6A250(void);

extern f32 lbl_3_data_18DD4[];

// g_Fielders entry (size 0x268), only the fields used here.
typedef struct {
    /* 0x000 */ Vec pos;
    /* 0x00C */ f32 height;
    /* 0x010 */ u8 _010[0x1E6 - 0x10];
    /* 0x1E6 */ u8 _1E6;
    /* 0x1E7 */ u8 _1E7[0x20F - 0x1E7];
    /* 0x20F */ u8 _20F;
    /* 0x210 */ u8 _210[0x263 - 0x210];
    /* 0x263 */ u8 _263;
    /* 0x264 */ u8 _264[0x268 - 0x264];
} Fielder2940;

// g_UnkAnimation_31EAC entry (size 0x54), only the fields used here.
typedef struct {
    /* 0x00 */ u8 _00[0x28];
    /* 0x28 */ f32 rotY;
    /* 0x2C */ u8 _2C[0x42 - 0x2C];
    /* 0x42 */ u8 _42;
    /* 0x43 */ u8 _43[0x54 - 0x43];
} FielderAnim2940;

extern Fielder2940 g_Fielders[];
extern FielderAnim2940 g_UnkAnimation_31EAC[];
extern f32 lbl_3_data_217D8[][2]; // per runner: x/z offset for secondaryGameMode 6

// .text:0x000E1478 size:0x4EC mapped:0x8072050C
void fn_3_E1478(void) {
    s32 i;
    s32 runner;
    s8 port;
    CharActor* ra;
    InMemRunnerType* r;
    f32 rotY;
    Fielder2940* fd;
    CharActor* actor;
    FielderAnim2940* anim;
    s32 fielder;

    if (g_GameLogic.gameStatus != 0 && g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 2 &&
        g_GameLogic.gameStatus != 8 && g_GameLogic.gameStatus != 3 && g_GameLogic.gameStatus != 0xB &&
        g_GameLogic.gameStatus != 0xD && g_GameLogic.gameStatus != 0x1A &&
        (g_Minigame.GameMode_MiniGame != 2 || g_GameLogic.gameStatus != 7)) {
        fn_3_E12F8();
        return;
    }
    for (i = 0; i < 4; i++) {
        if (lbl_8036E548.active[i] != NULL) {
            lbl_8036E548.active[i]->mode[0] = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        port = g_Minigame.minigameControlStruct[0].characterIndex[i];
        if (port < 0) {
            continue;
        }
        if (g_GameLogic.gameStatus == 3) {
            if (lbl_8036E548.active[port] != NULL) {
                lbl_8036E548.active[port]->mode[0] = 0;
            }
            continue;
        }
        if (g_Minigame.minigameControlStruct[0]._24[i] == 0) {
            if (g_Minigame.minigameFielderIndex[i] < 0) {
                return;
            }
            fielder = g_Minigame.minigameFielderIndex[i];
            actor = lbl_8036E548.active[port];
            if (actor == NULL) {
                continue;
            }
            if (g_d_GameSettings.GameModeSelected == 6) {
                switch (g_GameLogic.gameStatus) {
                case 0:
                case 1:
                case 2:
                case 7:
                    actor = fn_800111FC(actor, 1);
                    break;
                case 0xB:
                case 0xC:
                case 0xD:
                    break;
                default:
                    actor = fn_800111FC(actor, 0);
                    break;
                }
            }
            actor->mode[0] = 1;
            actor->_278 = 0;
            anim = &g_UnkAnimation_31EAC[fielder];
            fd = &g_Fielders[fielder];
            if (anim->_42 == 0) {
                actor->pos.x = fd->pos.x;
                actor->pos.y = -fd->pos.y - fd->height;
                actor->pos.z = fd->pos.z;
            }
            rotY = fn_3_6AF9C(fielder);
            actor->rot.y = rotY;
            actor->rot.x = 0.0f;
            actor->rot.z = 0.0f;
            anim->rotY = rotY;
            actor->_275 = fd->_1E6;
            if (g_Fielders[i]._263 != 0) {
                actor->mode[0] = 2;
            }
            if (g_Minigame.GameMode_MiniGame == 6 && fd->_20F == 0 &&
                g_Minigame.starDashStunType[i] == 3 && (g_d_GameSettings.FrameCountWhileNotAtMainMenu & 1)) {
                actor->mode[0] = 2;
            }
        } else {
            if (g_Minigame.rosterID == i) {
                runner = 0;
            } else {
                runner = i;
                if (g_Minigame.GameMode_MiniGame == 1 || g_Minigame.GameMode_MiniGame == 3) {
                    continue;
                }
            }
            if (lbl_8036E548.active[port] == NULL) {
                continue;
            }
            ra = fn_800111FC(lbl_8036E548.active[port], 0);
            if (g_GameLogic.gameStatus == 7 && (g_d_GameSettings._33 == 0 || (u8)(g_d_GameSettings._33 - 1) <= 1)) {
                continue;
            }
            if (g_Minigame.rosterID == i) {
                ra->_278 = 1;
            }
            ra->mode[0] = 1;
            r = &g_Runners[runner];
            ra->pos.x = r->position.x;
            ra->pos.y = r->position.y;
            ra->pos.z = r->position.z;
            ra->rot.x = 0.0f;
            ra->rot.y = r->runningAngle;
            ra->rot.z = 0.0f;
            if (g_GameLogic.secondaryGameMode == 6) {
                ra->pos.x += lbl_3_data_217D8[i][0];
                ra->pos.z += lbl_3_data_217D8[i][1];
                if (g_Minigame._1B15[i] == 3 && (g_d_GameSettings.FrameCountWhileNotAtMainMenu & 1)) {
                    ra->mode[0] = 2;
                }
            }
            if (g_d_GameSettings.GameModeSelected == 6 && runner == 0 && g_Pitcher.strikeOutOrWalk == 3) {
                if (ra->kind == 0x30 || ra->kind == 0x31 || ra->kind == 0x32 || ra->kind == 0x33) {
                    ra->mode[0] = 2;
                    if ((s32)fn_8004ACC4(1) != 0) {
                        fn_3_6A2A4(ra->kind);
                    }
                }
            }
            ra->_275 = r->someCollisionCheck;
        }
    }
}

// .text:0x000E1370 size:0x108 mapped:0x80720404
void fn_3_E1370(int mode) {
    s8* mg = (s8*)&g_Minigame;
    CharActor* p;
    int i;
    for (i = 0; i < 4; i++) {
        if (mode == 3) {
            p = lbl_8036E548.active[i];
            if (g_d_GameSettings.GameModeSelected == 2) {
                p = lbl_8036E548.active[9];
                if (i >= 1) {
                    return;
                }
            }
            if (p != NULL) {
                p->_25A = mg[0x19EC + i * 9] / 2;
                p->_25B = mg[0x19EC + i * 9] % 2;
            }
        }
    }
}

// .text:0x000E12F8 size:0x78 mapped:0x8072038C
void fn_3_E12F8(void) {
    int i;
    CharActor* p;
    for (i = 0; i < 4; i++) {
        p = lbl_8036E548.active[i];
        if (p != NULL) {
            p->mode[0] = 0;
        }
    }
    fn_3_6A25C();
    fn_3_6A250();
}

// .text:0x000E11E0 size:0x118 mapped:0x80720274
void fn_3_E11E0(void) {
    int i;
    lbl_8036E548._2D68 = -1;
    for (i = 0; i < 4; i++) {
        CharActor* e = lbl_8036E548.active[i];
        if (e != NULL) {
            e->mode[0] = 0;
            if (g_Minigame._1A13[i] == 0 && g_Minigame._19E8[i]._2 >= 0 &&
                g_Minigame._19E8[i]._7 != 0) {
                s8 t = g_Minigame._19DA[i];
                if (t >= 0) {
                    if (g_d_GameSettings.exhibitionMatchInd == 0) {
                        if (t >= 1) {
                        } else {
                            goto set;
                        }
                    } else if (g_Minigame._19E6 != 1 || g_d_GameSettings.GameModeSelected == 6 || g_Minigame._1A3C != 0 || t < 1) {
                    set:
                        e->mode[0] = 1;
                        e->pos.x = lbl_3_data_18DD4[i * 3];
                        e->pos.y = -lbl_3_data_18DD4[i * 3 + 1];
                        e->pos.z = lbl_3_data_18DD4[i * 3 + 2];
                        e->rot.x = 0.0f;
                        e->rot.y = 0.0f;
                        e->rot.z = 0.0f;
                    }
                }
            }
        }
    }
#ifdef TARGET_PC
    {
        extern int port_spani_trace_on(void);
        extern u32 port_spani_trace_frame;
        extern void OSReport(const char*, ...);
        extern u8 g_port_selLoading[4];
        static s32 s_last[4] = {-99, -99, -99, -99};
        if (port_spani_trace_on()) {
            for (i = 0; i < 4; i++) {
                CharActor* e = lbl_8036E548.active[i];
                s32 key = ((u8)g_Minigame._19E8[i]._0) | ((u8)g_Minigame._19E8[i]._2 << 8) |
                          ((u8)g_Minigame._19E8[i]._7 << 16) | ((g_Minigame._1A13[i] & 1) << 24) |
                          ((e ? e->mode[0] & 3 : 3) << 25) | ((g_port_selLoading[i] & 1) << 27);
                if (key != s_last[i]) {
                    OSReport("[sel] f=%u player %d hover %d loaded %d pending %d _7 %d loading %d 1A13 %d mode %d\n",
                             port_spani_trace_frame, i, (int)g_Minigame._19E8[i]._0, (int)g_Minigame._19E8[i]._2,
                             (int)g_Minigame._19E8[i]._3, (int)g_Minigame._19E8[i]._7, (int)g_port_selLoading[i],
                             (int)g_Minigame._1A13[i], e ? (int)e->mode[0] : -1);
                    s_last[i] = key;
                }
            }
        }
    }
#endif
}

