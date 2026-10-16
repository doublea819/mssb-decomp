#include "main/file_8004207C.h"
#ifdef TARGET_PC
// Career menu (port/game/career.c): its Lineup and Positions pages are this screen.
s32 port_career_lineup_active(void);
s32 port_career_lineup_take_field_view(void);
void port_career_lineup_done(s32 toGame);
#endif
#ifdef TARGET_PC
#include "main/charsel_state_type.h"
// CharSelWork is another view of CharSelectState: keep them in step on PC.
#define CSW_SAME(a, b) _Static_assert(offsetof(CharSelWork, a) == offsetof(CharSelectState, b), "CharSelWork." #a)
CSW_SAME(teamPort, ports);
CSW_SAME(_4704, _4704);
CSW_SAME(_470D, captainVariant);
CSW_SAME(input, input);
CSW_SAME(_47F9, chemPartners);
CSW_SAME(boosted, _489B);
CSW_SAME(_48B1, _48B1);
#endif
#include "main/file_80011640.h"
#include "static/GameSettings.h"
#include "static/Camera.h"
#include "static/Pad.h"
extern PadState lbl_803C77B8[4];
#include "game/UnknownHomes_Game.h"
#include "main/file_800527C4.h"
#include "Dolphin/GX/GXPerf.h"
#include "Dolphin/GX/GXMisc.h"
#include "musyx/musyx.h"
#include "Dolphin/os.h"
#include "Dolphin/mtx.h"
#include "stl/mem.h"
#include "main/file_800B0724.h"
#include "main/file_8004C5F8.h" // ConfirmDialog lbl_803C5F74
#include "main/file_80021308.h"
#include "main/file_800263FC.h"
#include "main/file_80034F50.h"

#pragma dont_inline on

extern u32 lbl_803CB750; // random seed
extern u8 lbl_800EFBA4[]; // sound effect volumes

// GP performance counters (debug overlay).
typedef struct GPMetrics {
    /*0x00*/ u32 cur[11];
    /*0x2C*/ u32 min[11];
    /*0x58*/ u32 max[11];
} GPMetrics;

extern GPMetrics lbl_802E4B28;
extern s32 lbl_803CB838; // frames until min/max reset
DECL_SECT(".sdata") extern s32 lbl_803CB83C[2]; // selected GP0/GP1 metric
extern u32 lbl_803CBCE8; // metrics enabled
extern void* lbl_803CC1B8; // current process-queue node
extern MsgDef lbl_800FB5C0[];
extern SwingFxFunc lbl_800FBE64[];
extern s8 lbl_800FBDEC[]; // anim ID -> lbl_800FBE64 index (11 = none)
extern s32 lbl_803CB848;
extern s32 lbl_803CB850;
extern s32 lbl_803CBCF8;
extern s32 lbl_803CBCFC;
extern s32 lbl_803CBD00;
extern u32 lbl_803CBD04;

typedef struct Unk80366158 {
    /*0x00*/ u8 _00[LBL_80366158_PAD(0x28)];
    /*0x28*/ u8 _28;
} Unk80366158;
extern Unk80366158 lbl_80366158;

extern void fn_8004CC18(void);
extern void fn_8004CC2C(void);
extern s32 fn_8004CA6C(u16 buttons);
extern void fn_8004D0F0(void);
extern void fn_8004C19C(CharActor* model, s32 animID, u32 colorIdx, f32 frame);
extern void fn_8004C510(CharActor* model, s32 animID, u32 colorIdx, f32 frame);

extern void fn_800569C8(void);
extern void fn_800625A4(s32 port, s32 sound);
extern DiskFileEntry lbl_800FB5B0; // disc file loaded into a sprite slot
extern MenuDef lbl_800FEF70[0x5D];
extern u8 lbl_8010B600[][3]; // innings per challenge difficulty
extern s32 lbl_803CBCF0;
extern u8 lbl_80361B20[]; // per character: can be boosted
extern u8 lbl_800E86F0[12]; // stat boosts
extern u8 lbl_802E4B00[2][9];
extern BatFxTables lbl_800FC0FC;
extern EffectParams lbl_800FBEA4;
extern EffectParams* lbl_803CB84C; // &lbl_800FBEA4
// Trail spawn template: the leading fields of ParticleParams that fn_8002F258 reads.
typedef struct TrailParams {
    /*0x00*/ void* tex; // TexArchive*
    /*0x04*/ s32 texIndex;
    /*0x08*/ s32 size;  // x100000
    /*0x0C*/ s32 unkC;
    /*0x10*/ s32 unk10;
} TrailParams;
extern TrailParams lbl_800FBE90;
extern void* lbl_803CBD0C; // TexArchive* of the effect particles (set by fn_8004B1B8)
extern char lbl_800E6920[]; // "orderchange.c"
extern char lbl_800E6930[]; // "//OZ" + SJIS "no return value"
extern f32 starMissionMenu(s16 charID);
extern f32 fn_8006CA9C(void);

extern void characterSelectScreen(s32 team);
extern void fn_800415A8(void);
extern void unsure_FillRosterPositions(s32 team);
extern void SetMenuNumber(void);
extern void fn_800671FC(void);
extern void fn_80069854(void);
extern u8 lbl_803CBCC9;
typedef struct Unk803CBD24 {
    /*0x0*/ u8 _0[4];
    /*0x4*/ u8 team;
} Unk803CBD24;
DECL_SECT(".sdata") extern Unk803CBD24 lbl_803CBD24;
extern s16 lbl_8010B42C[]; // star menu entries per character class
extern CharacterStats lbl_803C5144[2]; // picked-up player per team
extern u8 lbl_803CBCCC[2];             // picked-up slot per team
extern OrderEntry lbl_803CBCD0[2];     // picked-up order entry per team
extern u8 lbl_802E4B14[2][9];
extern u8 lbl_803CBCC8;
extern GXPerf0 lbl_800FB4C8[];
extern GXPerf1 lbl_800FB554[];

// .text:0x8004207C size:0x51C
#define SCALE_STAT(field)                    \
    v = scale * (f32)(field);                \
    (field) = v > 100 ? 100 : v

// NONMATCHING ~97.0%: chemistry loop walks a pointer instead of the original unrolled base+0x3B offsets
#if NONMATCHING
void capApplicationFunction(void) {
    s32 team;
    s32 i;
    s32 j;
    u8 bonus = 0;
    s32 barBonus = 0;
    s32 v;
    f32 scale;
    CharacterStats* c;

    for (team = 0; team < 2; team++) {
        for (i = 0; i < 9; i++) {
            c = &inMemRoster[team][i];
            if (team == 0) {
                scale = (100.0f + starMissionMenu(c->stats.CharID)) / 100.0f;
            } else {
                scale = (100.0f + fn_8006CA9C()) / 100.0f;
            }
            SCALE_STAT(c->stats.SlapContactSize);
            SCALE_STAT(c->stats.ChargeContactSize);
            SCALE_STAT(c->stats.SlapHitPower);
            SCALE_STAT(c->stats.ChargeHitPower);
            SCALE_STAT(c->stats.BuntingContactSize);
            SCALE_STAT(c->stats.Speed);
            SCALE_STAT(c->stats.ThrowingArm);
            c->stats.CurveBallSpeed += 10;
            if (c->stats.CurveBallSpeed > 200) {
                c->stats.CurveBallSpeed = 200;
            }
            c->stats.FastBallSpeed += 10;
            if (c->stats.FastBallSpeed > 200) {
                c->stats.FastBallSpeed = 200;
            }
            SCALE_STAT(c->stats.Curve);
            SCALE_STAT(c->stats.curveControl);
            if (team == 0) {
                u8* chem = c->chem;
                bonus = gChallengeSave.chemistryBonus;
                for (j = 0; j < (s32)sizeof(ChemistryTable); j++) {
                    chem[j] += bonus * 5;
                    if (chem[j] > 100) {
                        chem[j] = 100;
                    }
                }
            }
            switch (bonus) {
            case 0:
                barBonus = -1;
                break;
            case 1:
                barBonus = 0;
                break;
            case 2:
                barBonus = 1;
                break;
            case 3:
                if (starMissionCompletionTracker[c->stats.CharID].variantClassification == 0 ||
                    starMissionCompletionTracker[c->stats.CharID].variantClassification == 1) {
                    barBonus = 2;
                } else {
                    barBonus = 1;
                }
                break;
            case 4:
                if (starMissionCompletionTracker[c->stats.CharID].variantClassification == 0) {
                    barBonus = 3;
                } else if (starMissionCompletionTracker[c->stats.CharID].variantClassification == 1) {
                    barBonus = 2;
                } else {
                    barBonus = 1;
                }
                break;
            }
            c->stats.BattingStatBar += barBonus;
            if (c->stats.BattingStatBar > 10) {
                c->stats.BattingStatBar = 10;
            }
            c->stats.PitchingStatBar += barBonus;
            if (c->stats.PitchingStatBar > 10) {
                c->stats.PitchingStatBar = 10;
            }
            c->stats.RunningStatBar += barBonus;
            if (c->stats.RunningStatBar > 10) {
                c->stats.RunningStatBar = 10;
            }
            c->stats.FieldingStatBar += barBonus;
            if (c->stats.FieldingStatBar > 10) {
                c->stats.FieldingStatBar = 10;
            }
        }
    }
}
#endif

// .text:0x80042598 size:0x144
// Batting-order slot (1-9) of the player at fielding position `slot`.
s32 fn_80042598(u8 team, s32 slot) {
    OrderEntry* e = lbl_80354720[team];
    s32 i;
    for (i = 0; i < 9; i++, e++) {
        if (slot == e->slot) {
            return i + 1;
        }
    }
    OSPanic(lbl_800E6920, 0xD69, lbl_800E6930);
    return 0;
}

// Inlined copy of fn_80042598 (the original inlines it into the order-change menus).
#pragma dont_inline off
static inline s8 findOrderSlot(u8 team, s32 slot) {
    OrderEntry* e = lbl_80354720[team];
    s32 i;
    for (i = 0; i < 9; e++, i++) {
        if (slot == e->slot) {
            return i + 1;
        }
    }
    OSPanic(lbl_800E6920, 0xD69, lbl_800E6930);
    return 0;
}
#pragma dont_inline on

// .text:0x800426DC size:0x514
// NONMATCHING 74%: source stats indexed as [id/9][id%9] with u8 casts in the original; register allocation
#if NONMATCHING
void transferStatsToInMemRoster(u8 team) {
    s32 slot;
    CharacterStats* dst;
    CharacterStats* src;

    if (g_d_GameSettings.GameModeSelected == 5) {
        return;
    }
    slot = lbl_803297E0.slot[team] - 1;
    dst = &inMemRoster[team][slot];
    if (lbl_80361B20[dst->stats.CharID] == 0) {
        return;
    }
    if (++lbl_8034E9A0._4720[team] == 2) {
        lbl_8034E9A0._4720[team] = 0;
    }
    if (g_d_GameSettings.GameModeSelected != 5) {
        lbl_8034E9A0.boosted[team][slot] ^= 1;
        memcpy(lbl_802E4B00[team], lbl_8034E9A0.boosted[team], 9);
    } else {
        lbl_8034E9A0.boosted[0][slot] = 1;
    }
    if (lbl_8034E9A0.boosted[team][slot] != 0) {
        dst = &inMemRoster[team][slot];
        dst->stats.SlapContactSize += lbl_800E86F0[0];
        dst->stats.ChargeContactSize += lbl_800E86F0[1];
        dst->stats.SlapHitPower += lbl_800E86F0[2];
        dst->stats.ChargeHitPower += lbl_800E86F0[3];
        dst->stats.Speed += lbl_800E86F0[5];
        dst->stats.ThrowingArm += lbl_800E86F0[6];
        dst->stats.BuntingContactSize += lbl_800E86F0[4];
        dst->stats.CurveBallSpeed += lbl_800E86F0[7];
        dst->stats.FastBallSpeed += lbl_800E86F0[8];
        dst->stats.cursedBall += lbl_800E86F0[9];
        dst->stats.Curve += lbl_800E86F0[10];
        dst->stats.curveControl += lbl_800E86F0[11];
        dst->stats.BattingStatBar += 2;
        if (dst->stats.BattingStatBar > 10) {
            dst->stats.BattingStatBar = 10;
        }
        inMemRoster[team][slot].stats.PitchingStatBar += 2;
        if (inMemRoster[team][slot].stats.PitchingStatBar > 10) {
            inMemRoster[team][slot].stats.PitchingStatBar = 10;
        }
        inMemRoster[team][slot].stats.RunningStatBar += 2;
        if (inMemRoster[team][slot].stats.RunningStatBar > 10) {
            inMemRoster[team][slot].stats.RunningStatBar = 10;
        }
        inMemRoster[team][slot].stats.FieldingStatBar += 2;
        if (inMemRoster[team][slot].stats.FieldingStatBar > 10) {
            inMemRoster[team][slot].stats.FieldingStatBar = 10;
        }
    } else {
        CharacterStats* d = &inMemRoster[team][slot];
        s32 i;

        src = &lbl_8034E9A0.chars[dst->stats.CharID];
        memcpy(d, src, 0x1E);
        dst->stats.CharID = src->stats.CharID;
        d->stats.FieldingArm = src->stats.FieldingArm;
        d->stats.BattingStance = src->stats.BattingStance;
        memcpy(&d->stats.SlapContactSize, &src->stats.SlapContactSize, 2);
        memcpy(&d->stats.SlapHitPower, &src->stats.SlapHitPower, 2);
        d->stats.BuntingContactSize = src->stats.BuntingContactSize;
        d->stats.HitTrajectoryPushPull = src->stats.HitTrajectoryPushPull;
        d->stats.HitTrajectoryHighLow = src->stats.HitTrajectoryHighLow;
        d->stats.Speed = src->stats.Speed;
        d->stats.ThrowingArm = src->stats.ThrowingArm;
        d->stats.CharacterClass = src->stats.CharacterClass;
        d->stats.Weight = src->stats.Weight;
        d->stats.Captain = src->stats.Captain;
        d->stats.CaptainStarHitPitch = src->stats.CaptainStarHitPitch;
        memcpy(&d->stats.NonCaptainStarSwing, &src->stats.NonCaptainStarSwing, 2);
        d->stats.FieldingStats = src->stats.FieldingStats;
        memcpy(&d->stats.BattingStatBar, &src->stats.BattingStatBar, 4);
        memcpy(&d->chemistry, &src->chemistry, sizeof(ChemistryTable));
        d->BytesAfterChemistry[0] = src->BytesAfterChemistry[0];
        for (i = 0; i < 21; i++) {
            d->UnusedShorts[i] = src->UnusedShorts[i];
        }
    }
}
#endif

// .text:0x80042BF0 size:0x54
// NONMATCHING ~90%: mullw scheduled after the range subtraction
#if NONMATCHING
s32 randRange_FUN_80042bf0(s32 a, s32 b) {
    s32 lo;
    s32 hi;

    if (a == b) {
        return a;
    }
    if (a <= b) {
        lo = a;
    } else {
        lo = b;
        b = a;
    }
    lbl_803CB750 = lbl_803CB750 * 0x5D588B65 + 1;
    return (s32)(lbl_803CB750 >> 16) % (b - lo + 1) + lo;
}
#endif

// .text:0x80042C44 size:0xF4
void sndFXRelated(u16 button) {
    switch (button) {
    case 0x100:
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        break;
    case 0x200:
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        break;
    case 0x1:
    case 0x2:
    case 0x4:
    case 0x8:
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        break;
    case 0x3:
    case 0x20:
    case 0x40:
    case 0x400:
    case 0x800:
        break;
    }
}

// .text:0x80042D38 size:0x30
void fn_80042D38(u16 scene) {
    lbl_803CBBCC->prevScene = lbl_803CBBCC->scene;
    lbl_803CBBCC->prevStep = lbl_803CBBCC->step;
    lbl_803CBBCC->scene = scene;
    lbl_803CBBCC->step = 0;
}

// .text:0x80042D68 size:0x40
s32 fn_80042D68(LayoutOwner* owner, s32 idx, s32 value) {
    LayoutObj* obj = lbl_80371C30[owner->u14.objIdx + idx].obj;
    if ((s32)(obj->_5C >> 16) >= value) {
        obj->_68 = 0;
        return 1;
    }
    return 0;
}

// .text:0x80042DA8 size:0x40
s32 fn_80042DA8(LayoutOwner* owner, s32 idx, s32 value) {
    LayoutObj* obj = lbl_80371C30[owner->u14.objIdx + idx].obj;
    if ((s32)(obj->_5C >> 16) == value) {
        obj->_68 = 0;
        return 1;
    }
    return 0;
}

// .text:0x80042DE8 size:0x5A4
// NONMATCHING 99.8%: the (count >> 1) in the wrap-to-0 test still uses srawi instead of extrwi
#if NONMATCHING
void challengeStarMenu(void) {
    u8 fixed = 0;
    PortInput in;

    memset(&in, 0, sizeof(in));
    if (lbl_803297E0._CF92 != 0) {
        return;
    }
    in.held = lbl_803297E0.input[lbl_8034E9A0.teamPort[0]].held;
    in.pressed = lbl_803297E0.input[lbl_8034E9A0.teamPort[0]].pressed;
    in.repeat = lbl_803297E0.input[lbl_8034E9A0.teamPort[0]].repeat;
    if (starMissionCompletionTracker[lbl_803297E0._CF9C].variantClassification == 3) {
        fixed = 1;
    }
    if (in.repeat & 8) {
        if (lbl_803297E0._CF99 != 0) {
            if (fixed) {
                return;
            }
            lbl_803297E0.prevStarCursor2 = lbl_803297E0.starCursor2;
            lbl_803297E0.starCursor2 -= (u32)lbl_803297E0._CF9A >> 1;
            if (lbl_803297E0.starCursor2 < 0) {
                lbl_803297E0.starCursor2 += lbl_803297E0._CF9A;
            }
            if (lbl_803297E0.prevStarCursor2 != lbl_803297E0.starCursor2) {
                lbl_803297E0._CF92 = 4;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else {
            lbl_803297E0.prevSlotCursor = lbl_803297E0.slotCursor;
            lbl_803297E0.slotCursor--;
            if (lbl_803297E0.slotCursor < 0) {
                lbl_803297E0.slotCursor = 8;
            }
            if (lbl_803297E0.prevSlotCursor != lbl_803297E0.slotCursor) {
                lbl_803297E0._CF92 = 3;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    } else if (in.repeat & 4) {
        if (lbl_803297E0._CF99 != 0) {
            if (fixed) {
                return;
            }
            lbl_803297E0.prevStarCursor2 = lbl_803297E0.starCursor2;
            lbl_803297E0.starCursor2 += (u32)lbl_803297E0._CF9A >> 1;
            if (lbl_803297E0.starCursor2 >= lbl_803297E0._CF9A) {
                lbl_803297E0.starCursor2 = lbl_803297E0.starCursor2 - lbl_803297E0._CF9A;
            }
            if (lbl_803297E0.prevStarCursor2 != lbl_803297E0.starCursor2) {
                lbl_803297E0._CF92 = 4;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else {
            lbl_803297E0.prevSlotCursor = lbl_803297E0.slotCursor;
            lbl_803297E0.slotCursor++;
            if (lbl_803297E0.slotCursor == 9) {
                lbl_803297E0.slotCursor = 0;
            }
            if (lbl_803297E0.prevSlotCursor != lbl_803297E0.slotCursor) {
                lbl_803297E0._CF92 = 3;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    } else if (in.repeat & 1) {
        if (lbl_803297E0._CF99 != 0) {
            if (!fixed) {
                lbl_803297E0.prevStarCursor2 = lbl_803297E0.starCursor2;
                lbl_803297E0.starCursor2--;
                if (lbl_803297E0.starCursor2 < 0 && lbl_803297E0.starCursor2 < (s32)((u32)lbl_803297E0._CF9A >> 1)) {
                    lbl_803297E0.starCursor2 = ((u32)lbl_803297E0._CF9A >> 1) - 1;
                } else if (lbl_803297E0.starCursor2 < ((s32)((u32)lbl_803297E0._CF9A >> 1)) &&
                           lbl_803297E0.starCursor2 >= ((s32)((u32)lbl_803297E0._CF9A >> 1)) - 1) {
                    lbl_803297E0.starCursor2 = lbl_803297E0._CF9A - 1;
                }
            } else {
                lbl_803297E0.prevStarCursor2 = lbl_803297E0.starCursor2;
                lbl_803297E0.starCursor2--;
                if (lbl_803297E0.starCursor2 < 0) {
                    lbl_803297E0.starCursor2 = lbl_803297E0._CF9A - 1;
                }
            }
            if (lbl_803297E0.prevStarCursor2 != lbl_803297E0.starCursor2) {
                lbl_803297E0._CF92 = 4;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    } else if (in.repeat & 2) {
        if (lbl_803297E0._CF99 != 0) {
            if (!fixed) {
                lbl_803297E0.prevStarCursor2 = lbl_803297E0.starCursor2;
                lbl_803297E0.starCursor2++;
                if (lbl_803297E0.starCursor2 > (lbl_803297E0._CF9A >> 1) - 1 &&
                    lbl_803297E0.starCursor2 <= (lbl_803297E0._CF9A >> 1)) {
                    lbl_803297E0.starCursor2 = 0;
                } else if (lbl_803297E0.starCursor2 > lbl_803297E0._CF9A - 1 &&
                           lbl_803297E0.starCursor2 >= (lbl_803297E0._CF9A >> 1)) {
                    lbl_803297E0.starCursor2 = lbl_803297E0._CF9A >> 1;
                }
            } else {
                lbl_803297E0.prevStarCursor2 = lbl_803297E0.starCursor2;
                lbl_803297E0.starCursor2++;
                if (lbl_803297E0.starCursor2 == lbl_803297E0._CF9A) {
                    lbl_803297E0.starCursor2 = 0;
                }
            }
            if (lbl_803297E0.prevStarCursor2 != lbl_803297E0.starCursor2) {
                lbl_803297E0._CF92 = 4;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    } else if (in.pressed & 0x100) {
        if (lbl_803297E0._CF99 == 0) {
            lbl_803297E0._CF99 ^= 1;
            lbl_803297E0._CF92 = 5;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        }
    } else if (in.pressed & 0x200) {
        if (lbl_803297E0._CF99 == 0) {
            lbl_803297E0._CF92 = 2;
            lbl_803297E0.prevStarCursor2 = 0;
            lbl_803297E0.starCursor2 = 0;
            lbl_803297E0.prevSlotCursor = 0;
            lbl_803297E0.slotCursor = 0;
            lbl_803297E0._CF38 = 10;
        } else {
            lbl_803297E0._CF99 ^= 1;
            lbl_803297E0.prevStarCursor2 = 0;
            lbl_803297E0.starCursor2 = 0;
            lbl_803297E0._CF92 = 6;
        }
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
    }
}
#endif

// .text:0x8004338C size:0x4F4
void starMenuCursor(void) {
    u8 fixed = 0;
    PortInput in;
    u8 count;
    s8 cls;

    memset(&in, 0, sizeof(in));
    in.held = g_d_GameSettings._06 == 2 ? lbl_803297E0.input[lbl_8034E9A0.teamPort[0]].held
                                        : lbl_8034E9A0.input[0].held;
    in.pressed = g_d_GameSettings._06 == 2 ? lbl_803297E0.input[lbl_8034E9A0.teamPort[0]].pressed
                                           : lbl_8034E9A0.input[0].pressed;
    in.repeat = g_d_GameSettings._06 == 2 ? lbl_803297E0.input[lbl_8034E9A0.teamPort[0]].repeat
                                          : lbl_8034E9A0.input[0].repeat;
    cls = starMissionCompletionTracker[lbl_803297E0._CF9C].variantClassification;
    count = lbl_8010B42C[cls];
    if (cls == 3) {
        fixed = 1;
    }
    if (in.repeat & 8) {
        if (fixed) {
            return;
        }
        lbl_803297E0.prevStarCursor = lbl_803297E0.starCursor;
        lbl_803297E0.starCursor -= count >> 1;
        if (lbl_803297E0.starCursor < 0) {
            lbl_803297E0.starCursor += count;
        }
        if (lbl_803297E0.prevStarCursor != lbl_803297E0.starCursor) {
            lbl_803297E0._CF74 = 2;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if (in.repeat & 4) {
        if (fixed) {
            return;
        }
        lbl_803297E0.prevStarCursor = lbl_803297E0.starCursor;
        lbl_803297E0.starCursor += count >> 1;
        if (lbl_803297E0.starCursor >= count) {
            lbl_803297E0.starCursor = lbl_803297E0.starCursor - count;
        }
        if (lbl_803297E0.prevStarCursor != lbl_803297E0.starCursor) {
            lbl_803297E0._CF74 = 2;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if (in.repeat & 1) {
        if (!fixed) {
            lbl_803297E0.prevStarCursor = lbl_803297E0.starCursor;
            lbl_803297E0.starCursor--;
            if (lbl_803297E0.starCursor < 0 && lbl_803297E0.starCursor < (count >> 1)) {
                lbl_803297E0.starCursor = (count >> 1) - 1;
            } else if (lbl_803297E0.starCursor < (count >> 1) &&
                       lbl_803297E0.starCursor >= (count >> 1) - 1) {
                lbl_803297E0.starCursor = count - 1;
            }
        } else {
            lbl_803297E0.prevStarCursor = lbl_803297E0.starCursor;
            lbl_803297E0.starCursor--;
            if (lbl_803297E0.starCursor < 0) {
                lbl_803297E0.starCursor = count - 1;
            }
        }
        if (lbl_803297E0.prevStarCursor != lbl_803297E0.starCursor) {
            lbl_803297E0._CF74 = 2;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if (in.repeat & 2) {
        if (!fixed) {
            lbl_803297E0.prevStarCursor = lbl_803297E0.starCursor;
            lbl_803297E0.starCursor++;
            if (lbl_803297E0.starCursor > (count >> 1) - 1 && lbl_803297E0.starCursor <= (count >> 1)) {
                lbl_803297E0.starCursor = 0;
            } else if (lbl_803297E0.starCursor > count - 1 && lbl_803297E0.starCursor >= (count >> 1)) {
                lbl_803297E0.starCursor = count >> 1;
            }
        } else {
            lbl_803297E0.prevStarCursor = lbl_803297E0.starCursor;
            lbl_803297E0.starCursor++;
            if (lbl_803297E0.starCursor == count) {
                lbl_803297E0.starCursor = 0;
            }
        }
        if (lbl_803297E0.prevStarCursor != lbl_803297E0.starCursor) {
            lbl_803297E0._CF74 = 2;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if ((in.pressed & 0x100) || (in.pressed & 0x200)) {
        lbl_803297E0._CF74 = 3;
        if (in.pressed & 0x100) {
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else {
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        lbl_803297E0._CF38 = 2;
    }
}

#pragma dont_inline off
// .text:0x80043880 size:0x1418
// Order-change menu: left (dir 0) / right (dir 1) on the field view.
void fn_80043880(u8 dir, u8 team) {
    if (lbl_803297E0.slot[team] == 0) {
        return;
    }
    if (g_d_GameSettings._06 == 2 && lbl_803297E0._CF52[team] != 1) {
        return;
    }
    if (lbl_803297E0._CF52[team] != 1 && g_d_GameSettings._06 != 2) {
        return;
    }
    lbl_803297E0._CF4C[team] = lbl_803297E0._CF4A[team];
    if (dir == 0) {
        if (lbl_803297E0.slot[team] == 0 || lbl_803297E0._CF52[team] != 1) {
            goto end;
        }
        lbl_803297E0._CF48[team] = lbl_803297E0.slot[team];
        switch (lbl_80354720[team][lbl_803297E0.slot[team] - 1].slot) {
        case 0:
            lbl_803297E0.slot[team] = findOrderSlot(team, 4);
            break;
        case 1:
            lbl_803297E0.slot[team] = findOrderSlot(team, 4);
            break;
        case 2:
            lbl_803297E0.slot[team] = findOrderSlot(team, 3);
            break;
        case 3:
            lbl_803297E0.slot[team] = findOrderSlot(team, 5);
            break;
        case 7:
            lbl_803297E0.slot[team] = findOrderSlot(team, 6);
            break;
        case 8:
            lbl_803297E0.slot[team] = findOrderSlot(team, 7);
            break;
        case 4:
            lbl_803297E0.slot[team] = findOrderSlot(team, 2);
            break;
        case 5:
            lbl_803297E0.slot[team] = findOrderSlot(team, 4);
            break;
        case 6:
            lbl_803297E0.slot[team] = findOrderSlot(team, 8);
            break;
        }
        if (lbl_803297E0._CF48[team] != lbl_803297E0.slot[team]) {
            fn_800625A4(team, 0x3B);
        }
    } else if (lbl_803297E0.slot[team] == 0) {
        if (g_d_GameSettings._06 != 2) {
            lbl_803297E0._CF4A[team]++;
            if (lbl_803297E0._CF52[team] > 1) {
                lbl_803297E0._CF52[team] = 1;
            }
            switch (lbl_803297E0._CF52[team]) {
            case 0:
                lbl_803297E0._CF52[team] = 0;
                break;
            case 1:
                lbl_803297E0._CF52[team] = 1;
                break;
            }
            fn_800625A4(team, 0x3C);
        } else {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
    } else if (lbl_803297E0.slot[team] != 0 && lbl_803297E0._CF52[team] == 1) {
        lbl_803297E0._CF48[team] = lbl_803297E0.slot[team];
        switch (lbl_80354720[team][lbl_803297E0.slot[team] - 1].slot) {
        case 0:
            lbl_803297E0.slot[team] = findOrderSlot(team, 2);
            break;
        case 1:
            lbl_803297E0.slot[team] = findOrderSlot(team, 2);
            break;
        case 4:
            lbl_803297E0.slot[team] = findOrderSlot(team, 5);
            break;
        case 5:
            lbl_803297E0.slot[team] = findOrderSlot(team, 3);
            break;
        case 6:
            lbl_803297E0.slot[team] = findOrderSlot(team, 7);
            break;
        case 7:
            lbl_803297E0.slot[team] = findOrderSlot(team, 8);
            break;
        case 8:
            lbl_803297E0.slot[team] = findOrderSlot(team, 6);
            break;
        case 2:
            lbl_803297E0.slot[team] = findOrderSlot(team, 4);
            break;
        case 3:
            lbl_803297E0.slot[team] = findOrderSlot(team, 2);
            break;
        }
        if (lbl_803297E0._CF48[team] != lbl_803297E0.slot[team]) {
            fn_800625A4(team, 0x3B);
        }
    }
end:
    if (dir == 0) {
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else {
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// .text:0x80044C98 size:0x14E4
// Order-change menu: up (dir 0) / down (dir 1). On the field view (_CF52 set) the cursor
// jumps between fielding positions; fn_80042598 finds the batting slot of a position.
void fn_80044C98(u8 dir, u8 team) {
    lbl_803297E0._CF48[team] = lbl_803297E0.slot[team];
    if (dir == 0) {
        if (lbl_803297E0._CF52[team] == 0) {
            lbl_803297E0.slot[team]--;
            if (lbl_803297E0._CF3C[team] != 0 && lbl_803297E0.slot[team] < 1) {
                lbl_803297E0.slot[team] = 9;
                fn_800625A4(team, 0x3B);
            } else if (lbl_803297E0._CF48[team] == 0) {
                lbl_803297E0.slot[team] = 9;
                fn_800625A4(team, 0x3D);
            } else if (lbl_803297E0.slot[team] == 0) {
                fn_800625A4(team, 0x3E);
            } else {
                fn_800625A4(team, 0x3B);
            }
            return;
        }
        if (lbl_803297E0._CF48[team] == 0) {
            lbl_803297E0.slot[team] = findOrderSlot(team, 1);
            fn_800625A4(team, 0x3D);
            return;
        }
        switch (lbl_80354720[team][lbl_803297E0.slot[team] - 1].slot) {
        case 0:
            lbl_803297E0.slot[team] = findOrderSlot(team, 5);
            break;
        case 1:
            lbl_803297E0.slot[team] = findOrderSlot(team, 0);
            break;
        case 2:
            lbl_803297E0.slot[team] = findOrderSlot(team, 8);
            break;
        case 3:
            lbl_803297E0.slot[team] = findOrderSlot(team, 7);
            break;
        case 4:
            lbl_803297E0.slot[team] = findOrderSlot(team, 6);
            break;
        case 5:
            lbl_803297E0.slot[team] = findOrderSlot(team, 7);
            break;
        case 6:
            if (lbl_803297E0._CF3C[team] != 0) {
                lbl_803297E0.slot[team] = findOrderSlot(team, 4);
                fn_800625A4(team, 0x3B);
            } else {
                lbl_803297E0.slot[team] = 0;
                fn_800625A4(team, 0x3E);
            }
            break;
        case 8:
            if (lbl_803297E0._CF3C[team] != 0) {
                lbl_803297E0.slot[team] = findOrderSlot(team, 2);
                fn_800625A4(team, 0x3B);
            } else {
                lbl_803297E0.slot[team] = 0;
                fn_800625A4(team, 0x3E);
            }
            break;
        case 7:
            if (lbl_803297E0._CF3C[team] != 0) {
                lbl_803297E0.slot[team] = findOrderSlot(team, 1);
                fn_800625A4(team, 0x3B);
            } else {
                lbl_803297E0.slot[team] = 0;
                fn_800625A4(team, 0x3E);
            }
            break;
        }
        if (lbl_803297E0.slot[team] != 0 && lbl_803297E0._CF48[team] != lbl_803297E0.slot[team]) {
            fn_800625A4(team, 0x3B);
        }
    } else {
        if (lbl_803297E0._CF52[team] == 0) {
            lbl_803297E0.slot[team]++;
            if (lbl_803297E0._CF3C[team] != 0 && lbl_803297E0.slot[team] == 10) {
                lbl_803297E0.slot[team] = 1;
                fn_800625A4(team, 0x3B);
            } else if (lbl_803297E0.slot[team] == 10) {
                lbl_803297E0.slot[team] = 0;
                fn_800625A4(team, 0x3E);
            } else if (lbl_803297E0._CF48[team] == 0) {
                fn_800625A4(team, 0x3D);
            } else {
                fn_800625A4(team, 0x3B);
            }
            return;
        }
        if (lbl_803297E0._CF48[team] == 0) {
            lbl_803297E0.slot[team] = findOrderSlot(team, 7);
            fn_800625A4(team, 0x3D);
            return;
        }
        switch (lbl_80354720[team][lbl_803297E0.slot[team] - 1].slot) {
        case 0:
            lbl_803297E0.slot[team] = findOrderSlot(team, 1);
            break;
        case 2:
            lbl_803297E0.slot[team] = findOrderSlot(team, 1);
            break;
        case 4:
            lbl_803297E0.slot[team] = findOrderSlot(team, 1);
            break;
        case 3:
            lbl_803297E0.slot[team] = findOrderSlot(team, 0);
            break;
        case 5:
            lbl_803297E0.slot[team] = findOrderSlot(team, 0);
            break;
        case 7:
            lbl_803297E0.slot[team] = findOrderSlot(team, 5);
            break;
        case 6:
            lbl_803297E0.slot[team] = findOrderSlot(team, 4);
            break;
        case 8:
            lbl_803297E0.slot[team] = findOrderSlot(team, 2);
            break;
        case 1:
            if (lbl_803297E0._CF3C[team] != 0) {
                lbl_803297E0.slot[team] = findOrderSlot(team, 7);
                fn_800625A4(team, 0x3B);
            } else {
                lbl_803297E0.slot[team] = 0;
                fn_800625A4(team, 0x3E);
            }
            break;
        }
        if (lbl_803297E0.slot[team] != 0 && lbl_803297E0._CF48[team] != lbl_803297E0.slot[team]) {
            fn_800625A4(team, 0x3B);
        }
    }
}
#pragma dont_inline on

// .text:0x8004617C size:0x1078
// NONMATCHING ~98.2%: team select when g_d_GameSettings._10 > 1 (original leaves t unset), input mask scheduling
#if NONMATCHING
void fn_8004617C(s32 port) {
    s32 t;
    PortInput in;
    u8 ready;
    s8 slot;

    if (lbl_803C66B0.active[0] != 0 || lbl_803C66B0.active[1] != 0) {
        return;
    }
    if (g_d_GameSettings._06 != 2) {
        if (g_d_GameSettings._10 == 1) {
            if (port > 1) {
                return;
            }
            t = port;
        } else if (g_d_GameSettings._10 == 0) {
            if (port != 0) {
                return;
            }
            if (lbl_803297E0._CF43 == 0) {
                t = 0;
            } else {
                t = 1;
            }
        } else {
            t = port; // the original leaves this unset
        }
    } else {
        t = port;
    }
    memset(&in, 0, sizeof(in));
    in.held = lbl_803297E0._CF3A == -1 ? lbl_8034E9A0.input[port].held : lbl_803297E0.input[port].held;
    in.pressed = lbl_803297E0._CF3A == -1 ? lbl_8034E9A0.input[port].pressed : lbl_803297E0.input[port].pressed;
    in.repeat = lbl_803297E0._CF3A == -1 ? lbl_8034E9A0.input[port].repeat : lbl_803297E0.input[port].repeat;
    ready = lbl_803297E0._CF4E[t];
    if (ready != 0) {
        in.repeat &= 0x200;
        in.held &= 0x200;
        in.pressed &= 0x200;
    }
    if (in.pressed & 0x10) {
        if (lbl_803297E0._CF61[t] != 0) {
            lbl_803297E0._CF61[t] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        } else if (lbl_803297E0.slot[t] != 0) {
            lbl_803297E0._CF61[t] = 1;
            lbl_803297E0._CF65[t] = 1;
            lbl_803297E0._CF67[t] = 0;
            sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
        }
    } else if (in.repeat & 8) {
        if (lbl_803297E0._CF61[t] != 0) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == 5 && lbl_803297E0._CF70 != 0) {
            return;
        }
        if (ready != 0) {
            return;
        }
        fn_80044C98(0, t);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (in.repeat & 4) {
        if (lbl_803297E0._CF61[t] != 0) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == 5 && lbl_803297E0._CF70 != 0) {
            return;
        }
        if (ready != 0) {
            return;
        }
        fn_80044C98(1, t);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (in.repeat & 1) {
        if (lbl_803297E0._CF61[t] != 0) {
            if (lbl_803297E0._CF67[t] == 1) {
                lbl_803297E0._CF67[t] = 0;
                lbl_803297E0._CF63[t] = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            return;
        }
        if (g_d_GameSettings.GameModeSelected == 5 && lbl_803297E0._CF70 != 0) {
            return;
        }
        if (ready != 0) {
            return;
        }
        fn_80043880(0, t);
    } else if (in.repeat & 2) {
        if (lbl_803297E0._CF61[t] != 0) {
            if (lbl_803297E0._CF67[t] == 0) {
                lbl_803297E0._CF67[t] = 1;
                lbl_803297E0._CF63[t] = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            return;
        }
        if (g_d_GameSettings.GameModeSelected == 5 && lbl_803297E0._CF70 != 0) {
            return;
        }
        if (ready != 0) {
            return;
        }
        fn_80043880(1, t);
    } else if (in.pressed & 0x20) {
        if (lbl_803297E0._CF61[t] != 0) {
            lbl_803297E0._CF61[t] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (lbl_803297E0._CFA2[t] == 1) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == 5 && lbl_803297E0._CF70 != 0) {
            return;
        }
        if (g_d_GameSettings._06 == 2) {
            return;
        }
        if (lbl_803297E0._CF52[t] == 1) {
            return;
        }
        lbl_803297E0._CF54[(u8)t] = lbl_803297E0._CF52[(u8)t];
        if (g_d_GameSettings._06 != 2) {
            lbl_803297E0._CF4A[(u8)t]++;
            if (lbl_803297E0._CF4A[(u8)t] > 1) {
                lbl_803297E0._CF4A[(u8)t] = 1;
            }

            if (lbl_803297E0._CF52[(u8)t] != 1) {
                lbl_803297E0._CF52[(u8)t] = 1;
            }
            fn_800625A4((u8)t, 0x3C);
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
        }
    } else if (in.pressed & 0x40) {
        if (lbl_803297E0._CF61[t] != 0) {
            lbl_803297E0._CF61[t] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (lbl_803297E0._CFA2[t] == 1) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == 5 && lbl_803297E0._CF70 != 0) {
            return;
        }
        if (g_d_GameSettings._06 == 2) {
            return;
        }
        if (lbl_803297E0._CF52[t] == 0) {
            return;
        }
        lbl_803297E0._CF54[(u8)t] = lbl_803297E0._CF52[(u8)t];
        if (g_d_GameSettings._06 != 2) {
            lbl_803297E0._CF4A[(u8)t]--;
            if (lbl_803297E0._CF4A[(u8)t] < 0) {
                lbl_803297E0._CF4A[(u8)t] = 0;
            }

            if (lbl_803297E0._CF52[(u8)t] != 0) {
                lbl_803297E0._CF52[(u8)t] = 0;
            }
            fn_800625A4((u8)t, 0x3C);
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
        }
    } else if (in.pressed & 0x400) {
        if (lbl_803297E0._CF61[t] != 0) {
            lbl_803297E0._CF61[t] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (lbl_803297E0.slot[t] == 0) {
            return;
        }
        if (lbl_803297E0._CFA2[t] == 1) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == 5 && lbl_803297E0._CF70 != 0) {
            return;
        }
        if (g_d_GameSettings._06 == 2) {
            return;
        }
        if (ready != 0) {
            return;
        }
        lbl_803297E0._CF58[t] = 1;
    } else if (in.pressed & 0x800) {
        if (lbl_803297E0._CF61[t] != 0) {
            lbl_803297E0._CF61[t] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        slot = lbl_803297E0.slot[t];
        if (slot == 0) {
            return;
        }
        if (g_d_GameSettings._06 == 2) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == 5) {
            if (lbl_803297E0._CF71 != 0) {
                return;
            }
            lbl_803297E0._CF78 = inMemRoster[0][lbl_803297E0.slot[t] - 1].stats.CharID;
            lbl_803297E0._CF71 = 1;
            lbl_803297E0._CF72 = 1;
            lbl_803297E0.prevStarCursor = 0;
            lbl_803297E0.starCursor = 0;
            lbl_803297E0._CF74 = 1;
            lbl_803297E0._CF38 = 3;
            sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
        } else if (lbl_80361B20[inMemRoster[t][slot - 1].stats.CharID] != 0 && lbl_803297E0._CF9E[t] == 0) {
            lbl_803297E0._CF9E[t] = 1;
            sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
        }
    } else if (in.pressed & 0x100) {
        if (lbl_803297E0._CF61[t] != 0) {
            lbl_803297E0._CF61[t] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (ready != 0) {
            return;
        }
        if (lbl_803C66B0.active[0] != 0 || lbl_803C66B0.active[1] != 0) {
            return;
        }
        if (g_d_GameSettings._06 == 2 && lbl_803297E0.slot[t] != 0 && lbl_803297E0._CFA2[t] == 1) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.GameModeSelected == 5 && lbl_803297E0._CF70 != 0 && lbl_80361B20[0xE4] == 0) {
            lbl_803297E0._CF70 = 0;
            lbl_803297E0._CF6B = 1;
            fn_800625A4(0, 0x46);
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }
        slot = lbl_803297E0.slot[t];
        if (slot == 0) {
            if (lbl_803297E0._CF4E[0] != 0 && lbl_803297E0._CF4E[1] != 0) {
                lbl_803297E0._CF38 = 14;
            }
            if (lbl_803297E0.slot[t] != 0) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                return;
            }
            if (g_d_GameSettings._06 == 2) {
                fn_800625A4(t, 0x43);
                lbl_803297E0._CF38 = 14;
            } else if (g_d_GameSettings.GameModeSelected == 5) {
                fn_800625A4(0, 0x43);
                lbl_803297E0._CF38 = 14;
#ifdef TARGET_PC
            } else if (g_d_GameSettings._10 == 0 && lbl_803297E0._CF4E[0] == 0 && port_career_lineup_active()) {
                // Career: your lineup is done; the opponent's is the CPU's.
                lbl_803297E0._CF4E[0] = 1;
                lbl_803297E0._CF4E[1] = 1;
                fn_800625A4(0, 0x43);
                fn_800625A4(1, 0x43);
                lbl_803297E0._CF38 = 14;
#endif
            } else if (g_d_GameSettings._10 == 0 && lbl_803297E0._CF4E[0] == 0) {
                if (g_d_GameSettings._06 == 2) {
                    lbl_803297E0._CF38 = 10;
                    fn_800625A4(t, 0x33);
                } else {
                    lbl_803297E0._CF40 = 1;
                    lbl_803297E0._CF3C[t] = 0;
                    lbl_803297E0._CF43 = 1;
                    lbl_803297E0._CF4E[0] = 1;
                    fn_800625A4(t, 0x3F);
                }
                lbl_803297E0._CF4E[0] = 1;
            } else if (g_d_GameSettings._10 == 0 && lbl_803297E0._CF4E[1] == 0) {
                lbl_803297E0._CF4E[1] = 1;
                if (lbl_803297E0._CF4E[0] != 0 && lbl_803297E0._CF4E[1] != 0) {
                    fn_800625A4(0, 0x43);
                    fn_800625A4(1, 0x43);
                    lbl_803297E0._CF38 = 14;
                }
            } else if (g_d_GameSettings._10 == 1) {
                lbl_803297E0._CF4E[t] = 1;
                if (lbl_803297E0._CF4E[0] != 0 && lbl_803297E0._CF4E[1] != 0) {
                    if (lbl_803297E0._CF50[t ^ 1] != 0) {
                        lbl_803297E0._CF4E[t] = 0;
                        return;
                    }
                    fn_800625A4(0, 0x43);
                    fn_800625A4(1, 0x43);
                    lbl_803297E0._CF38 = 14;
                } else {
                    lbl_803297E0._CF50[t] = 1;
                    fn_800625A4(t, 0x41);
                }
            }
        } else if (lbl_803297E0._CF3C[t] == 0) {
            lbl_803297E0._CF48[t] = slot;
            lbl_803297E0._CF3E[t] = fn_800471F4(lbl_803297E0._CF3C[t], t);
            lbl_803297E0._CF3C[t] = 1;
            fn_800625A4(t, 0x3B);
            lbl_803CBCC8 = 1;
        } else {
            lbl_803297E0._CF48[t] = slot;
            lbl_803297E0._CF3E[t] = fn_800471F4(lbl_803297E0._CF3C[t], t);
            lbl_803297E0._CF3C[t] = 0;
            fn_800625A4(t, 0x3B);
            lbl_803297E0._CF56[t] = 1;
        }
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (in.pressed & 0x200) {
        if (lbl_803297E0._CF61[t] != 0) {
            lbl_803297E0._CF61[t] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.GameModeSelected == 5 && lbl_803297E0._CF70 != 0) {
            lbl_803297E0._CF70 = 0;
            lbl_803297E0._CF6B = 1;
            fn_800625A4(0, 0x46);
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (lbl_803297E0._CF3C[t] != 0) {
            lbl_803297E0._CF4E[t] = 0;
            lbl_803297E0._CF3C[t] = 0;
            if (lbl_803297E0.slot[t] != lbl_803297E0._CF48[t]) {
                fn_800625A4(t, 0x44);
            } else {
                lbl_803297E0._CF3E[t] = 0xFF;
            }
        } else if (lbl_803297E0.slot[t] == 0) {
            if (lbl_803297E0._CF3C[t] != 0) {
                lbl_803297E0._CF3C[t] = 0;
                fn_800625A4(t, 0x3B);
            } else if (lbl_803297E0.slot[t] != 0) {
                lbl_803297E0._CF4C[t] = lbl_803297E0._CF4A[t];
                lbl_803297E0.slot[t] = 0;
                fn_800625A4(t, 0x3C);
            } else if (g_d_GameSettings._10 == 0 && lbl_803297E0._CF43 != 0) {
                lbl_803297E0._CF4E[0] = 0;
                lbl_803297E0._CF4A[lbl_803297E0._CF43] = 0;
                lbl_803297E0.slot[lbl_803297E0._CF43] = 0;
                lbl_803297E0._CF43 = 0;
                lbl_803297E0._CF40 = 0;
                lbl_803297E0._CF4A[lbl_803297E0._CF43] = 0;
                lbl_803297E0.slot[lbl_803297E0._CF43] = 0;
                fn_800625A4(t, 0x40);
            } else if (ready != 0) {
                fn_800625A4(t, 0x42);
                lbl_803297E0._CF4E[t] = 0;
                lbl_803297E0._CF50[t] = 0;
            } else {
                lbl_803297E0._CF4A[0] = 0;
                lbl_803297E0.slot[0] = 0;
                lbl_803297E0._CF4A[1] = 0;
                lbl_803297E0.slot[1] = 0;
                lbl_803297E0._CF43 = 0;
                if (g_d_GameSettings._06 != 2) {
                    fn_800625A4(0, 0x3A);
                    fn_800625A4(1, 0x3A);
                    lbl_803297E0._CF38 = 12;
                } else {
                    fn_800625A4(t, 0x43);
                    lbl_803297E0._CF38 = 14;
                }
            }
        } else if (lbl_803297E0.slot[t] != 0) {
            lbl_803297E0._CF48[t] = lbl_803297E0.slot[t];
            lbl_803297E0.slot[t] = 0;
            fn_800625A4(t, 0x3E);
        } else if (lbl_803297E0._CF40 != 0) {
            lbl_803297E0._CF40 = 0;
            lbl_803297E0.slot[t] = 0;
            lbl_803297E0._CF4E[t] = 0;
        } else if (g_d_GameSettings._06 == 2) {
            lbl_803297E0._CF38 = 10;
            fn_800625A4(0, 0x33);
        } else {
            lbl_803297E0._CF4E[t] = 0;
            lbl_803297E0._CF38 = 12;
            fn_800625A4(t, 0x33);
        }
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
    }
}
#endif

// .text:0x800471F4 size:0xAEC
// Field-by-field CharacterStats copy, in the original's order.
#define COPY_CHAR_STATS(d, s)                                                         \
    do {                                                                              \
        s32 k_;                                                                       \
        memcpy((d), (s), 0x1E);                                                       \
        (d)->stats.CharID = (s)->stats.CharID;                                        \
        (d)->stats.FieldingArm = (s)->stats.FieldingArm;                              \
        (d)->stats.BattingStance = (s)->stats.BattingStance;                          \
        memcpy(&(d)->stats.SlapContactSize, &(s)->stats.SlapContactSize, 2);          \
        memcpy(&(d)->stats.SlapHitPower, &(s)->stats.SlapHitPower, 2);                \
        (d)->stats.BuntingContactSize = (s)->stats.BuntingContactSize;                \
        (d)->stats.HitTrajectoryPushPull = (s)->stats.HitTrajectoryPushPull;          \
        (d)->stats.HitTrajectoryHighLow = (s)->stats.HitTrajectoryHighLow;            \
        (d)->stats.Speed = (s)->stats.Speed;                                          \
        (d)->stats.ThrowingArm = (s)->stats.ThrowingArm;                              \
        (d)->stats.CharacterClass = (s)->stats.CharacterClass;                        \
        (d)->stats.Weight = (s)->stats.Weight;                                        \
        (d)->stats.Captain = (s)->stats.Captain;                                      \
        (d)->stats.CaptainStarHitPitch = (s)->stats.CaptainStarHitPitch;              \
        memcpy(&(d)->stats.NonCaptainStarSwing, &(s)->stats.NonCaptainStarSwing, 2);  \
        (d)->stats.FieldingStats = (s)->stats.FieldingStats;                          \
        memcpy(&(d)->stats.BattingStatBar, &(s)->stats.BattingStatBar, 4);            \
        memcpy(&(d)->chemistry, &(s)->chemistry, sizeof(ChemistryTable));             \
        (d)->BytesAfterChemistry[0] = (s)->BytesAfterChemistry[0];                    \
        for (k_ = 0; k_ < 21; k_++) {                                                 \
            (d)->UnusedShorts[k_] = (s)->UnusedShorts[k_];                            \
        }                                                                             \
    } while (0)

// NONMATCHING ~85%: CharacterStats copies use field pointers precomputed on the stack in the original
#if NONMATCHING
u8 fn_800471F4(u8 mode, u8 team) {
    s8 i;
    u8 pick;
    u8 t;

    if (mode == 0) {
        for (i = 0; i < 9; i++) {
            if (i == lbl_803297E0.slot[team] - 1) {
                lbl_803CBCCC[team] = i;
                COPY_CHAR_STATS(&lbl_803C5144[team], &inMemRoster[team][lbl_803CBCCC[team]]);
                lbl_803CBCD0[team].slot = lbl_80354720[team][lbl_803CBCCC[team]].slot;
                memcpy(lbl_802E4B14[team], lbl_8034E9A0._47F9[team][lbl_803CBCCC[team]], 9);
                memcpy(lbl_802E4B00[team], lbl_8034E9A0.boosted[team], 9);
            }
        }
    } else {
        for (i = 0; i < 9; i++) {
            if (i != lbl_803297E0.slot[team] - 1) {
                continue;
            }
            if (lbl_803297E0._CF52[team] == 0) {
                pick = lbl_803CBCCC[team];
                COPY_CHAR_STATS(&inMemRoster[team][pick], &inMemRoster[team][i]);
                lbl_80354720[team][pick].slot = lbl_80354720[team][i].slot;
                memcpy(lbl_8034E9A0._47F9[team][pick], lbl_8034E9A0._47F9[team][i], 9);
                COPY_CHAR_STATS(&inMemRoster[team][i], &lbl_803C5144[team]);
                pick = lbl_803CBCCC[team];
                t = lbl_802E4B14[team][i];
                lbl_802E4B14[team][i] = lbl_802E4B14[team][pick];
                lbl_80354720[team][i].slot = lbl_803CBCD0[team].slot;
                lbl_802E4B14[team][pick] = t;
                memcpy(lbl_8034E9A0._47F9[team][i], lbl_802E4B14[team], 9);
                pick = lbl_803CBCCC[team];
                t = lbl_802E4B00[team][i];
                lbl_802E4B00[team][i] = lbl_802E4B00[team][pick];
                lbl_802E4B00[team][pick] = t;
                memcpy(lbl_8034E9A0.boosted[team], lbl_802E4B00[team], 9);
                lbl_803297E0.swap[team][0] = lbl_803CBCCC[team];
                lbl_803297E0.swap[team][1] = i;
            } else {
                pick = lbl_803CBCCC[team];
                lbl_803297E0.swap[team][0] = pick;
                lbl_80354720[team][pick].slot = lbl_80354720[team][i].slot;
                lbl_803297E0.swap[team][1] = i;
                lbl_80354720[team][i].slot = lbl_803CBCD0[team].slot;
            }
        }
    }
    return lbl_803CBCCC[team];
}
#endif

// .text:0x80047CE0 size:0x304
// NONMATCHING ~93%: (_06 == 2) materialised as cntlzw; dead CF52 stores scheduled differently
// nmverify: fn_800625A4 original has a redundant second fn_800625A4(1, 0x38) site (_06 != 2 / _06 == 2 arms), same behaviour
// nmverify:  inlined on one side (calls match once expanded)
#if NONMATCHING
void fn_80047CE0(void) {
    s32 i;
    u8 mode;

    lbl_8034E9A0._4720[0] = 0;
    lbl_8034E9A0._4720[1] = 0;
    for (i = 0; i < 2; i++) {
        lbl_803297E0._CF52[i] = g_d_GameSettings._06 == 2;
    }
    lbl_803297E0._CF3E[1] = 0xFF;
    lbl_803297E0._CF3E[0] = 0xFF;
    lbl_803297E0._CF3C[1] = 0;
    lbl_803297E0._CF3C[0] = 0;
    lbl_803297E0._CF40 = 0;
    lbl_803297E0._CF41 = 0;
    lbl_803297E0._CF43 = 0;
    lbl_803297E0._CF48[1] = 0;
    lbl_803297E0._CF48[0] = 0;
    lbl_803297E0.slot[1] = 0;
    lbl_803297E0.slot[0] = 0;
    lbl_803297E0._CF4C[1] = 0;
    lbl_803297E0._CF4C[0] = 0;
    lbl_803297E0._CF4A[1] = 0;
    lbl_803297E0._CF4A[0] = 0;
    lbl_803297E0._CF54[1] = 0;
    lbl_803297E0._CF54[0] = 0;
    lbl_803297E0._CF52[1] = 0;
    lbl_803297E0._CF52[0] = 0;
    lbl_803297E0._CF4E[1] = 0;
    lbl_803297E0._CF4E[0] = 0;
    lbl_803297E0._CF56[1] = 0;
    lbl_803297E0._CF56[0] = 0;
    lbl_803297E0._CF58[1] = 0;
    lbl_803297E0._CF58[0] = 0;
    lbl_8034E9A0._4705 = 1;
    lbl_803C66B0.portOf[0] = 0;
    lbl_803C66B0.portOf[1] = 1;
    if (g_d_GameSettings._06 != 2) {
        if (g_d_GameSettings.GameModeSelected != 5 && lbl_803CBBCC->prevScene == 0xA
#ifdef TARGET_PC
            && !port_career_lineup_active() // keep the career team's saved order and positions
#endif
        ) {
            characterSelectScreen(0);
            characterSelectScreen(1);
        } else if (g_d_GameSettings.GameModeSelected == 5 && gChallengeSave._4445 == 0) {
            fn_800415A8();
            unsure_FillRosterPositions(1);
            characterSelectScreen(1);
        }
        lbl_803297E0._CFA2[1] = 0;
        lbl_803297E0._CFA2[lbl_803297E0._CF3B] = 0;
        lbl_803C5EA4._36 = 1;
        lbl_803C5EA4.prevMode = lbl_803C5EA4.mode;
        lbl_803C5EA4.mode = 1;
    } else if (lbl_803297E0._CFA2[lbl_803297E0._CF3B] == 0) {
        lbl_803297E0._CF52[1] = 1;
        lbl_803297E0._CF52[0] = 1;
    } else {
        lbl_803297E0._CF52[1] = 0;
        lbl_803297E0._CF52[0] = 0;
    }
    SetMenuNumber();
    if (g_d_GameSettings._06 != 2 && lbl_803CBBCC->prevScene != 0xA &&
        g_d_GameSettings._10 == 0 && g_d_GameSettings.GameModeSelected != 5
#ifdef TARGET_PC
        && !port_career_lineup_active() // a fresh visit (as from team select), not a return from stadium select
#endif
    ) {
        lbl_803297E0._CF43 = 1;
        lbl_803297E0._CF4E[0] = 1;
        fn_800625A4(0, 0x39);
        fn_800625A4(1, 0x39);
        lbl_803297E0._CF38 = 1;
        return;
    }
    mode = lbl_803297E0._CFA2[lbl_803297E0._CF3B];
    if (mode != 2 && mode != 3) {
        fn_800625A4(0, 0x38);
        fn_800625A4(1, 0x38);
        lbl_803297E0._CF38 = 1;
    } else if (mode == 2) {
        lbl_803297E0._CF7D = 1;
        lbl_803297E0._CF38 = 4;
    } else {
        lbl_803297E0._CF92 = 1;
        lbl_803297E0._CF38 = 5;
    }
}
#endif

// .text:0x80047FE4 size:0x6FC
// Inline form of fn_80042D38.
#define SET_SCENE(id)                                          \
    lbl_803CBBCC->prevScene = lbl_803CBBCC->scene;            \
    lbl_803CBBCC->prevStep = lbl_803CBBCC->step;              \
    lbl_803CBBCC->scene = (id);                               \
    lbl_803CBBCC->step = 0

// NONMATCHING ~94.5%: roster copy loop and fn_8004CA6C switch dispatch order
#if NONMATCHING
void pauseMenuSelection(void) {
    s32 i;
    PortInput in;
    u8 mode;

    switch (lbl_803297E0._CF38) {
    case 0:
        fn_80047CE0();
        break;
    case 1:
        lbl_803297E0.slot[1] = 0;
        lbl_803297E0.slot[0] = 0;
        lbl_803297E0._CF4A[1] = 0;
        lbl_803297E0._CF4A[0] = 0;
        lbl_803297E0._CF38++;
        break;
    case 2:
#ifdef TARGET_PC
        // Career > Positions: open on the field view (what R does, fn_8004617C).
        if (lbl_803C66B0.active[0] == 0 && lbl_803C66B0.active[1] == 0 && lbl_803297E0._CF52[0] == 0 &&
            port_career_lineup_take_field_view()) {
            lbl_803297E0._CF54[0] = lbl_803297E0._CF52[0];
            lbl_803297E0._CF4A[0] = 1;
            lbl_803297E0._CF52[0] = 1;
            fn_800625A4(0, 0x3C);
            break;
        }
#endif
        for (i = 0; i < 2; i++) {
            fn_8004617C(i);
        }
        break;
    case 3:
        starMenuCursor();
        break;
    case 4:
        memset(&in, 0, sizeof(in));
        if (lbl_803C66B0.step[0] != 0) {
            break;
        }
        in.held = lbl_803297E0.input[lbl_8034E9A0.teamPort[0]].held;
        in.pressed = lbl_803297E0.input[lbl_8034E9A0.teamPort[0]].pressed;
        in.repeat = lbl_803297E0.input[lbl_8034E9A0.teamPort[0]].repeat;
        if (in.pressed & 0x200) {
            lbl_803297E0._CF7D = 3;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            lbl_803297E0._CF38 = 10;
        }
        break;
    case 5:
        challengeStarMenu();
        break;
    case 6:
        switch (lbl_803CBCC9) {
        case 0:
            fn_800B0A5C_insertQueue(fn_8004D0F0, 0x3000);
            lbl_803CBCC9++;
            break;
        case 1:
            switch (fn_8004CA6C(lbl_8034E9A0.input[lbl_8034E9A0.teamPort[lbl_803CBD24.team]].pressed)) {
            case 0:
                break;
            case 1:
                fn_8004CC2C();
                break;
            case 3:
                characterSelectScreen(0);
                characterSelectScreen(1);
                fn_800671FC();
                lbl_8034E978._26 = 1;
                changeScene(0xF, 6);
                lbl_803CBD24.team = 0;
                lbl_803CBCC9 = 0;
                lbl_803297E0._CF38 = 10;
                break;
            case 2:
                fn_8004CC2C();
                break;
            case 4:
                lbl_803CBD24.team = 0;
                lbl_803CBCC9 = 0;
                lbl_803297E0._CF5F = 0;
                lbl_803297E0._CF38 = 2;
                break;
            }
            break;
        }
        break;
    case 10:
        if (lbl_803297E0._CF5F != 0) {
            lbl_8034E9A0._48AD = 1;
            lbl_803C66B0.steps[0][0] = 0;
            memset(&lbl_803C66B0.steps[0][1], 0, 6);
            lbl_803297E0._CF50[1] = 0;
            lbl_803297E0._CF50[0] = 0;
            lbl_803297E0._CF4E[1] = 0;
            lbl_803297E0._CF4E[0] = 0;
            fn_80062A74();
            fn_80021410();
            fn_80035CA4(0xF);
            fn_80035CA4(0x12);
            fn_80035CA4(9);
            fn_80035CA4(6);
            lbl_8034E9A0._48AF = 1;
            lbl_8034E9A0._48B1 = 1;
            lbl_803297E0._CF5F = 0;
#ifdef TARGET_PC
            if (port_career_lineup_active()) {
                port_career_lineup_done(1); // keeps the order and positions; the career game is set up
            }
#endif
            SET_SCENE(4);
        } else {
            if (lbl_8034E978._24 != 0) { // header animation still running
                break;
            }
            if (g_d_GameSettings.GameModeSelected == 5) {
                mode = lbl_803297E0._CFA2[lbl_803297E0._CF3B];
                if (mode != 2 && mode != 3) {
                    for (i = 0; i < 9; i++) {
                        gChallengeSave.roster[i].charID = inMemRoster[0][i].stats.CharID;
                        gChallengeSave.roster[i]._2 = lbl_80354720[0][i]._1;
                        gChallengeSave.roster[i]._3 = lbl_80354720[0][i].slot;
                        gChallengeSave.roster[i]._4 =
                            inMemRoster[0][i].stats.BattingStance + inMemRoster[0][i].stats.FieldingArm * 2;
                    }
                    lbl_803297E0._CFA1 = 0;
                }
            }
            if (g_d_GameSettings.GameModeSelected == 5 && g_d_GameSettings._06 == 2 &&
                lbl_803297E0._CFA2[lbl_803297E0._CF3B] == 2 && lbl_803297E0._CF7D != 0) {
                break;
            }
            lbl_803297E0._CF40 = 0;
            lbl_803297E0._CF3C[1] = 0;
            lbl_803297E0._CF3C[0] = 0;
            lbl_803297E0._CF50[1] = 0;
            lbl_803297E0._CF50[0] = 0;
            lbl_803297E0._CF4E[1] = 0;
            lbl_803297E0._CF4E[0] = 0;
            fn_80069854();
#ifdef TARGET_PC
            if (g_d_GameSettings._06 != 2 && port_career_lineup_active()) {
                port_career_lineup_done(0); // back to the Career menu
                SET_SCENE(18);
            } else
#endif
            if (g_d_GameSettings._06 != 2 && g_d_GameSettings.GameModeSelected == 5) {
                SET_SCENE(0xD);
            } else if (g_d_GameSettings._06 == 2) {
                mode = lbl_803297E0._CFA2[lbl_803297E0._CF3B];
                if (mode != 2 && mode != 3) {
                    if (lbl_803C66B0.active[0] != 0 || lbl_803C66B0.active[1] != 0) {
                        break;
                    }
                }
                lbl_803297E0._CF42 = 1;
                lbl_803297E0._CF40 = 0;
            } else {
                SET_SCENE(0xC);
            }
        }
        mode = lbl_803297E0._CFA2[lbl_803297E0._CF3B];
        if (mode != 2 && mode != 3) {
            lbl_803297E0._CF45 = 1;
        }
        lbl_803297E0._CF38 = 0;
        fn_800B0A14_removeQueue(NULL);
        break;
    case 12:
        if (lbl_803C66B0.active[0] != 0 || lbl_803C66B0.active[1] != 0) {
            break;
        }
        memset(lbl_8034E9A0.boosted, 0, sizeof(lbl_8034E9A0.boosted));
        lbl_803297E0._CF4E[1] = 0;
        lbl_803297E0._CF4E[0] = 0;
        lbl_803297E0._CF45 = 1;
        lbl_803297E0._CF38 = 13;
        break;
    case 13:
        lbl_803297E0._CF38 = 0;
        lbl_803297E0._CF61[1] = 0;
        lbl_803297E0._CF61[0] = 0;
        lbl_803297E0._CF50[1] = 0;
        lbl_803297E0._CF50[0] = 0;
        lbl_803297E0._CF4E[1] = 0;
        lbl_803297E0._CF4E[0] = 0;
        lbl_803C5EA4._36 = 1;
        lbl_803C5EA4.prevMode = lbl_803C5EA4.mode;
        lbl_803C5EA4.mode = 0;
#ifdef TARGET_PC
        if (port_career_lineup_active()) {
            fn_80069854();
            port_career_lineup_done(0); // B: back to the Career menu, keeping the changes
            SET_SCENE(18);
            fn_800B0A14_removeQueue(NULL);
            break;
        }
#endif
        SET_SCENE(0xA);
        fn_800B0A14_removeQueue(NULL);
        break;
    case 14:
        if (lbl_803C66B0.active[0] == 0 && lbl_803C66B0.active[1] == 0) {
            lbl_803297E0._CF38 = 10;
        }
        break;
    }
}
#endif

// .text:0x800486E0 size:0x84
void fn_800486E0(u16 priority, s8 a, s8 b) {
    fn_800B0A5C_insertQueue(pauseMenuSelection, priority);
    lbl_803297E0._CF38 = 0;
    lbl_803297E0._CF3A = a;
    lbl_803297E0._CF42 = 0;
    if (g_d_GameSettings._06 != 2) {
        lbl_803297E0._CF3B = 0;
    } else {
        lbl_803297E0._CF3B = b;
    }
}

// .text:0x80048764 size:0xBC
void fn_80048764(void) {
    switch (lbl_803CBBCC->step) {
    case 0:
        if (lbl_803C66B0.active[0] == 0 && lbl_803C66B0.active[1] == 0) {
            fn_800B0A5C_insertQueue(pauseMenuSelection, 0x1000);
            lbl_803297E0._CF38 = 0;
            lbl_803297E0._CF3A = -1;
            lbl_803297E0._CF42 = 0;
            if (g_d_GameSettings._06 != 2) {
                lbl_803297E0._CF3B = 0;
            } else {
                lbl_803297E0._CF3B = 0;
            }
            lbl_803CBBCC->step++;
        }
        break;
    case 1:
        break;
    }
}

// .text:0x80048820 size:0x3CC
// NONMATCHING ~90%: register allocation only
#if NONMATCHING
s32 fn_80048820(void* menuPtr, u16 held, u16 trig, u16 repeat, u8 holdTime) {
    DebugMenu* menu = menuPtr;
    DebugMenuItem* item;
    s32 speed;
    s32 visible;
    s32 delta;
    s32 v;

    if (holdTime >= 0x91) {
        speed = 2;
    } else if (holdTime >= 0x50) {
        speed = 1;
    } else {
        speed = 0;
    }
    visible = menu->visible;
    if (menu->count < visible) {
        visible = menu->count;
    }
    if (repeat & 8) {
        menu->cursor--;
        if (menu->wrap != 0) {
            if (menu->cursor < 0) {
                menu->cursor += menu->count;
                menu->top = menu->count - visible;
            }
            if (menu->cursor < menu->top) {
                menu->top = menu->cursor;
            }
        } else {
            if (menu->cursor < 0) {
                menu->cursor = 0;
            }
            if (menu->cursor < menu->top) {
                menu->top = menu->cursor;
            }
        }
    } else if (repeat & 4) {
        menu->cursor++;
        if (menu->wrap != 0) {
            if (menu->cursor >= menu->count) {
                menu->cursor -= menu->count;
                menu->top = 0;
            }
            while (menu->cursor - menu->top >= visible) {
                menu->top++;
            }
        } else {
            if (menu->cursor >= menu->count) {
                menu->cursor = menu->count - 1;
            }
            while (menu->cursor - menu->top >= visible) {
                menu->top++;
            }
        }
    } else if (repeat & 1) {
        item = &menu->items[menu->cursor];
        delta = -item->step[speed];
        if (item->value != NULL) {
            switch (item->type) {
            case 2:
                v = delta + *(s8*)item->value;
                if (v < item->min) {
                    v = item->min;
                }
                *(s8*)item->value = v;
                break;
            case 3:
            case 4:
            case 5:
                v = delta + *(u8*)item->value;
                if (v < item->min) {
                    v = item->min;
                }
                *(u8*)item->value = v;
                break;
            case 6:
            case 7:
            case 8:
                break;
            default:
                v = delta + *(s32*)item->value;
                if (v < item->min) {
                    v = item->min;
                }
                *(s32*)item->value = v;
                break;
            }
        }
    } else if (repeat & 2) {
        item = &menu->items[menu->cursor];
        delta = item->step[speed];
        if (item->value != NULL) {
            switch (item->type) {
            case 2:
                v = delta + *(s8*)item->value;
                if (v > item->max) {
                    v = item->max;
                }
                *(s8*)item->value = v;
                break;
            case 3:
            case 4:
            case 5:
                v = delta + *(u8*)item->value;
                if (v > item->max) {
                    v = item->max;
                }
                *(u8*)item->value = v;
                break;
            case 6:
            case 7:
            case 8:
                break;
            default:
                v = delta + *(s32*)item->value;
                if (v > item->max) {
                    v = item->max;
                }
                *(s32*)item->value = v;
                break;
            }
        }
    }
    item = &menu->items[menu->cursor];
    if (item->func != NULL) {
        if (item->value != NULL) {
            if (repeat & item->mask) {
                return item->func(menu, repeat);
            }
        } else {
            switch (item->type) {
            case 6:
                if (held & item->mask) {
                    return item->func(menu, held);
                }
                break;
            case 7:
                if (trig & item->mask) {
                    return item->func(menu, trig);
                }
                break;
            case 8:
                if (repeat & item->mask) {
                    return item->func(menu, repeat);
                }
                break;
            }
        }
    }
    return 0;
}
#endif

// fn_80048BEC, size:0x28
void fn_80048BEC(void* menuPtr, u32 a, u32 b) {
    DebugMenu* menu = menuPtr;
    s32 count = menu->count < menu->visible ? menu->count : menu->visible;
    while (count > 0) {
        count--;
    }
}

// fn_80048C14, size:0x8
void fn_80048C14(u32 value) {
    lbl_803CBCE8 = value;
}

// fn_80048C1C, size:0xC
void fn_80048C1C(void) {
    if (lbl_803CBCE8 != 0) {
        return;
    }
}

// .text:0x80048C28 size:0x124
// NONMATCHING ~92%: min/max loop uses ctr in ours, a decrementing counter in the original
#if NONMATCHING
void fn_80048C28(void) {
    u32* p;
    s32 n;

    if (lbl_803CBCE8 == 0) {
        return;
    }
    GXSetDrawSync(0xABCD);
    while (GXReadDrawSync() != 0xABCD) {
    }
    GXReadGPMetric(&lbl_802E4B28.cur[0], &lbl_802E4B28.cur[1]);
    GXReadVCacheMetric(&lbl_802E4B28.cur[2], &lbl_802E4B28.cur[3], &lbl_802E4B28.cur[4]);
    GXReadPixMetric(&lbl_802E4B28.cur[5], &lbl_802E4B28.cur[6], &lbl_802E4B28.cur[7],
                    &lbl_802E4B28.cur[8], &lbl_802E4B28.cur[9], &lbl_802E4B28.cur[10]);
    if (--lbl_803CB838 == 0) {
        memset(lbl_802E4B28.max, 0, sizeof(lbl_802E4B28.max));
        memset(lbl_802E4B28.min, 0xFF, sizeof(lbl_802E4B28.min));
        lbl_803CB838 = 300;
    }
    p = lbl_802E4B28.min;
    n = 11;
    while (n-- != 0) {
        p--;
        if (p[11] > p[0]) {
            p[11] = p[0];
        }
        if (p[22] < p[0]) {
            p[22] = p[0];
        }
    }
}
#endif

// .text:0x80048D4C size:0xB4
void fn_80048D4C(void) {
    if (lbl_803CBCE8 == 0) {
        return;
    }
    GXSetGPMetric(lbl_800FB4C8[lbl_803CB83C[0]], lbl_800FB554[lbl_803CB83C[1]]);
    GXClearGPMetric();
    if (lbl_800FB4C8[lbl_803CB83C[0]] == GX_PERF0_CLOCKS) {
        GXReadGP0Metric();
    }
    if (lbl_800FB554[lbl_803CB83C[1]] == GX_PERF1_CLOCKS) {
        GXReadGP1Metric();
    }
    GXSetVCacheMetric(GX_VC_ALL);
    GXClearVCacheMetric();
    GXClearPixMetric();
}

// .text:0x80048E00 size:0xA8
s32 fn_80048E00(s32 index, s32 value) {
    s32 count = 35;
    if (index != 0) {
        count = 23;
    }
    if (value >= count) {
        value = 0;
    } else if (value < 0) {
        value = count - 1;
    }
    if (value != lbl_803CB83C[index]) {
        lbl_803CB83C[index] = value;
        memset(lbl_802E4B28.max, 0, sizeof(lbl_802E4B28.max));
        memset(lbl_802E4B28.min, 0xFF, sizeof(lbl_802E4B28.min));
        lbl_803CB838 = 300;
    }
    return value;
}

// fn_80048EA8, size:0x10
s32 fn_80048EA8(s32 index) {
    return lbl_803CB83C[index];
}

#ifdef TARGET_PC
s32 port_star_skills_enabled(void);
#endif

// .text:0x80048EB8 size:0x368
void startGameRelated(void) {
    s32 i;

    switch (lbl_803C5F04._35) {
    case 0:
        lbl_803C5EE0._15 = 1;
        lbl_8034E9A0._48AF = 1;
        lbl_8034E978._26 = 1;
        fn_80062A74();
        fn_80021410();
        lbl_803C5F04._35++;
        break;
    case 1:
        if (lbl_803C66B0.active[0] != 0 || lbl_803C66B0.active[1] != 0) {
            if (lbl_803C66B0.step[0] == 0x31 && lbl_803C66B0.step[1] != 0) {
                fn_80062674(1);
            }
            break;
        }
        for (i = 0; i < 2; i++) {
            if (g_d_GameSettings.PlayerPorts[i] < 4) {
                lbl_800E8754.port[g_d_GameSettings.PlayerPorts[i]]._6 = lbl_803C5F04.playerOption[i][0];
                lbl_800E8754.port[g_d_GameSettings.PlayerPorts[i]]._3 = lbl_803C5F04.playerOption[i][1];
                lbl_800E8754.port[g_d_GameSettings.PlayerPorts[i]]._2 = lbl_803C5F04.playerOption[i][2];
                lbl_800E8754.port[g_d_GameSettings.PlayerPorts[i]]._4 = lbl_803C5F04.playerOption[i][3];
            } else {
                lbl_800E8754.port[i]._6 = lbl_803C5F04.playerOption[i][0];
                lbl_800E8754.port[i]._3 = lbl_803C5F04.playerOption[i][1];
                lbl_800E8754.port[i]._2 = lbl_803C5F04.playerOption[i][2];
                lbl_800E8754.port[i]._4 = lbl_803C5F04.playerOption[i][3];
            }
        }
        g_d_GameSettings.home_AwaySetting = lbl_803C5F04.option[1];
        lbl_800E8754._04 = lbl_803C5F04.option[2];
#ifdef TARGET_PC
        if (!port_star_skills_enabled()) {
            lbl_800E8754._04 = 0; // no star moves or star chances (port/game/menu_scope.c)
        }
#endif
        lbl_800E8754.innings = lbl_803C5F04.option[3] * 2 + 1;
        if (lbl_803C5F04.option[4] != 0) {
            lbl_800E8754._05 = 10;
        } else {
            lbl_800E8754._05 = 0;
        }
        lbl_800E8754._06 = 0;
        if (lbl_803C5F04._34 == 1) {
            if (g_d_GameSettings.GameModeSelected != 5) {
                fn_80035CA4(0xF);
                fn_80035CA4(0x12);
                fn_80035CA4(9);
                fn_80035CA4(6);
                lbl_803C5EA4._0F = 0;
                OSReport("Goto Game ..... option end \n");
                fn_80042D38(4);
            } else {
                transferStatsToInMemRoster(0);
                capApplicationFunction();
                fn_80035CA4(0xF);
                fn_80035CA4(9);
                fn_80035CA4(6);
                fn_80021410();
                lbl_803297E0._CF40 = 0;
                lbl_803C5EA4._0F = 0;
                changeScene(0xF, 6);
                lbl_803C5EA4._11 = 0;
                lbl_8034E9A0._48AF = 1;
                lbl_8034E978._26 = 1;
                fn_80042D38(4);
            }
        } else if (g_d_GameSettings.GameModeSelected != 5) {
            lbl_803C5EA4._36 = 1;
            lbl_803C5EA4.prevMode = lbl_803C5EA4.mode;
            lbl_803C5EA4.mode = 2;
            lbl_8034E978.menu = 5;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[5].track;
            fn_80042D38(0xC);
        } else {
            lbl_803C5F04._32 = 0;
            lbl_803C5EE0._15 = 1;
            fn_80042D38(0xB);
        }
        lbl_803C5F04._35 = 0;
        lbl_803C5F04.state = 0;
        fn_800B0A14_removeQueue(&lbl_803C5F04);
        break;
    }
}

// .text:0x80049220 size:0x2AC
#ifdef TARGET_PC
// Game options cursor: past the hidden Star Skills row (2) in the direction it
// moved (up when `up`). Only on the game options page (_36 == 0).
static s8 port_options_skip_star_skills(s8 cursor, s32 up) {
    if (cursor == 2 && lbl_803C5F04._36 == 0 && !port_star_skills_enabled()) {
        cursor = up ? 1 : 3;
    }
    return cursor;
}
#endif

// NONMATCHING ~85%: input copy goes through a zeroed stack struct; register allocation
#if NONMATCHING
void fn_80049220(u8 team) {
    u8 found = 0;
    s8 t;
    PortInput in;
    s32 count;
    s8 cursor;

    if (g_d_GameSettings.PlayerPorts[team] == lbl_8034E9A0.teamPort[team]) {
        t = team;
        found = 1;
    }
    if (!found) {
        return;
    }
    if (lbl_803C66B0.step[0] != 0 || lbl_803C66B0.step[1] != 0) {
        return;
    }
    in.held = 0;
    in.pressed = 0;
    in.repeat = 0;
    in = lbl_8034E9A0.input[t];
    if ((in.repeat & 8) || (in.repeat & 4)) {
        lbl_803C5F04.prevCursor[(u8)t] = lbl_803C5F04.cursor[(u8)t];
        cursor = lbl_803C5F04.cursor[(u8)t];
        if (lbl_803C5F04._36 == 0) {
            count = 5;
        } else if (g_d_GameSettings.GameModeSelected != 6) {
            count = 4;
        } else {
            count = 2;
        }
        if (in.repeat & 8) {
            if (--cursor < 0) {
                if (lbl_803C5F04._36 == 0) {
                    cursor = 4;
                } else {
                    cursor = 3;
                }
            }
            fn_800625A4((u8)t, 0x30);
            sndFXRelated(8);
        } else if (in.repeat & 4) {
            if (++cursor == count) {
                cursor = 0;
            }
            fn_800625A4((u8)t, 0x30);
            sndFXRelated(4);
        }
#ifdef TARGET_PC
        cursor = port_options_skip_star_skills(cursor, in.repeat & 8);
#endif
        lbl_803C5F04.cursor[(u8)t] = cursor;
    } else if (in.repeat & 1) {
        fn_80049D8C(0, t);
    } else if (in.repeat & 2) {
        fn_80049D8C(1, t);
    } else if ((in.pressed & 0x40) || (in.pressed & 0x200)) {
        if (g_d_GameSettings._06 == 2) {
            return;
        }
        if (lbl_803C5F04._36 != 1) {
            return;
        }
        lbl_803C5F04._36 = 0;
        lbl_803C5F04.state = 2;
        if (g_d_GameSettings.GameModeSelected == 5) {
            lbl_8034E978.menu = 0x14;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[0x14].track;
        } else {
            lbl_8034E978.menu = 6;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[6].track;
        }
        fn_800625A4(0, 0x2C);
        if (in.pressed & 0x200) {
            sndFXRelated(0x200);
        } else {
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    }
}
#endif

// .text:0x800494CC size:0x3AC
// NONMATCHING ~88%: teamPort/input address computation and register allocation
#if NONMATCHING
void fn_800494CC(u8 team) {
    u8 found = 0;
    s8 port;
    u16 pressed;
    u16 repeat;
    s32 count;
    s8 cursor;

    if (lbl_803C66B0.step[0] != 0 || lbl_803C66B0.step[1] != 0) {
        return;
    }
    port = lbl_8034E9A0.teamPort[team];
    if (g_d_GameSettings.PlayerPorts[0] == port) {
        found = 1;
    }
    if (g_d_GameSettings.PlayerPorts[1] == port) {
        found = 1;
    }
    lbl_8034E9A0.teamPort[team] = port;
    if (!found) {
        return;
    }
    repeat = lbl_8034E9A0.input[team].repeat;
    pressed = lbl_8034E9A0.input[team].pressed;
    if ((repeat & 8) || (repeat & 4)) {
        if (g_d_GameSettings.GameModeSelected == 5) {
            return;
        }
        lbl_803C5F04.prevCursor[0] = lbl_803C5F04.cursor[0];
        cursor = lbl_803C5F04.cursor[0];
        if (lbl_803C5F04._36 == 0) {
            count = 5;
        } else if (g_d_GameSettings.GameModeSelected != 6) {
            count = 4;
        } else {
            count = 2;
        }
        if (repeat & 8) {
            if (--cursor < 0) {
                if (lbl_803C5F04._36 == 0) {
                    cursor = 4;
                } else {
                    cursor = 3;
                }
            }
            fn_800625A4(0, 0x30);
            sndFXRelated(8);
        } else if (repeat & 4) {
            if (++cursor == count) {
                cursor = 0;
            }
            fn_800625A4(0, 0x30);
            sndFXRelated(4);
        }
#ifdef TARGET_PC
        cursor = port_options_skip_star_skills(cursor, repeat & 8);
#endif
        lbl_803C5F04.cursor[0] = cursor;
    } else if (repeat & 1) {
        fn_80049D8C(0, 0);
    } else if (repeat & 2) {
        fn_80049D8C(1, 0);
    } else if (pressed & 0x20) {
        if (g_d_GameSettings._06 == 2) {
            return;
        }
        lbl_803C5F04._36 = 1;
        lbl_803C5F04.state = 3;
        lbl_803C5F04.prevCursor[0] = lbl_803C5F04.cursor[0];
        lbl_803C5F04.cursor[0] = 0;
        if (g_d_GameSettings.GameModeSelected == 5) {
            lbl_8034E978.menu = 0x15;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[0x15].track;
        } else {
            lbl_8034E978.menu = 7;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[7].track;
        }
        fn_800625A4(0, 0x2B);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (pressed & 0x100) {
        if (lbl_803C5F04.cursor[0] != 0) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected != 5) {
            fn_800625A4(0, 0x31);
            lbl_803C5F04._35 = 0;
        } else {
            lbl_8034E9A0._48B0 = 1;
            lbl_803C5EE0._15 = 1;
            fn_80062A74();
            fn_80021410();
            lbl_803C5F04._35 = 1;
        }
        changeScene(0xF, 6);
        lbl_803C5F04.state = 5;
        lbl_803C5F04._34 = 1;
        sndFXRelated(0x100);
    } else if (pressed & 0x200) {
        if (lbl_803C5F04.cursor[0] != 0) {
            lbl_803C5F04.prevCursor[0] = lbl_803C5F04.cursor[0];
            lbl_803C5F04.cursor[0] = 0;
            fn_800625A4(0, 0x30);
        } else {
            lbl_803CBCF0 = 0;
            fn_800625A4(0, 0x2A);
            lbl_803C5F04.state = 5;
            lbl_803C5F04._34 = 0;
            lbl_803C5F04._35 = 1;
        }
        sndFXRelated(0x200);
    }
}
#endif

// .text:0x80049878 size:0x408
#define RESET_MATCH_OPTIONS(i) \
    lbl_803C5F04.option[0] = 0; \
    lbl_803C5F04.prevOption[0] = 0; \
    lbl_803C5F04.option[1] = 1; \
    lbl_803C5F04.option[2] = 1; \
    lbl_803C5F04.option[3] = 2; \
    lbl_803C5F04.option[4] = 0; \
    lbl_803C5F04.prevOption[1] = 1; \
    lbl_803C5F04.prevOption[2] = 1; \
    lbl_803C5F04.prevOption[3] = 2; \
    lbl_803C5F04.prevOption[4] = 0; \
    for (i = 0; i < 4; i++) { \
        lbl_803C5F04.playerOption[i][0] = 0; \
        lbl_803C5F04.playerOption[i][1] = 0; \
        lbl_803C5F04.playerOption[i][2] = 0; \
        lbl_803C5F04.playerOption[i][3] = 1; \
        lbl_803C5F04.prevPlayerOption[i][0] = 0; \
        lbl_803C5F04.prevPlayerOption[i][1] = 0; \
        lbl_803C5F04.prevPlayerOption[i][2] = 0; \
        lbl_803C5F04.prevPlayerOption[i][3] = 1; \
    }


// NONMATCHING ~98.9%: lis/addi order of the challenge-save block
#if NONMATCHING
void possiblyTransferDataBetweenDifferentRels(void) {
    s32 i;
    u8 stage;

    for (i = 0; i < 4; i++) {
        lbl_803C5EF8.a[i] = 0;
        lbl_803C5EF8.b[i] = 0;
    }
    lbl_803C5F04._2E = 0;
    if (lbl_8034E9A0._4704 == 0) {
        RESET_MATCH_OPTIONS(i);
        lbl_8034E9A0._4704 = 1;
    } else {
        for (i = 0; i < 2; i++) {
            if (g_d_GameSettings.PlayerPorts[i] < 4) {
                lbl_803C5F04.playerOption[i][0] = lbl_800E8754.port[g_d_GameSettings.PlayerPorts[i]]._6;
                lbl_803C5F04.playerOption[i][1] = lbl_800E8754.port[g_d_GameSettings.PlayerPorts[i]]._3;
                lbl_803C5F04.playerOption[i][2] = lbl_800E8754.port[g_d_GameSettings.PlayerPorts[i]]._2;
                lbl_803C5F04.playerOption[i][3] = lbl_800E8754.port[g_d_GameSettings.PlayerPorts[i]]._4;
            } else {
                lbl_803C5F04.playerOption[i][0] = lbl_800E8754.port[i]._6;
                lbl_803C5F04.playerOption[i][1] = lbl_800E8754.port[i]._3;
                lbl_803C5F04.playerOption[i][2] = lbl_800E8754.port[i]._2;
                lbl_803C5F04.playerOption[i][3] = lbl_800E8754.port[i]._4;
            }
        }
        lbl_803C5F04.option[1] = g_d_GameSettings.home_AwaySetting;
        lbl_803C5F04.option[2] = lbl_800E8754._04;
        lbl_803C5F04.option[3] = (u32)lbl_800E8754.innings >> 1;
        if (lbl_800E8754._05 == 10) {
            lbl_803C5F04.option[4] = 1;
        } else {
            lbl_803C5F04.option[4] = 0;
        }
        lbl_800E8754._06 = 0;
    }
    if (g_d_GameSettings.GameModeSelected == 5) {
        for (i = 0; i < 2; i++) {
            if (g_d_GameSettings.PlayerPorts[i] < 4) {
                lbl_803C5F04.playerOption[i][0] = lbl_800E8754.port[g_d_GameSettings.PlayerPorts[i]]._6;
                lbl_803C5F04.playerOption[i][1] = lbl_800E8754.port[g_d_GameSettings.PlayerPorts[i]]._3;
                lbl_803C5F04.playerOption[i][2] = lbl_800E8754.port[g_d_GameSettings.PlayerPorts[i]]._2;
                lbl_803C5F04.playerOption[i][3] = lbl_800E8754.port[g_d_GameSettings.PlayerPorts[i]]._4;
            } else {
                lbl_803C5F04.playerOption[i][0] = lbl_800E8754.port[i]._6;
                lbl_803C5F04.playerOption[i][1] = lbl_800E8754.port[i]._3;
                lbl_803C5F04.playerOption[i][2] = lbl_800E8754.port[i]._2;
                lbl_803C5F04.playerOption[i][3] = lbl_800E8754.port[i]._4;
            }
        }
        stage = gChallengeSave._441D;
        lbl_803C5F04.option[1] = 0;
        lbl_803C5F04.option[4] = 1;
        lbl_803C5F04.option[2] = 1;
        lbl_803C5F04.option[1] = 0;
        lbl_803C5F04.prevOption[1] = 0;
        lbl_803C5F04.prevOption[4] = 1;
        lbl_803C5F04.option[4] = 1;
        if (stage != 9) {
            s32 last = gChallengeSave._441F;
            if (last == 9) {
                lbl_803C5F04.option[3] = (u32)lbl_8010B600[g_d_GameSettings.challengeDifficulty][1] >> 1;
            } else if (last != 9 && stage != 9) {
                lbl_803C5F04.option[3] = (u32)lbl_8010B600[g_d_GameSettings.challengeDifficulty][0] >> 1;
            }
        } else if (gChallengeSave._16C2 == 0x2A) {
            lbl_803C5F04.option[3] = (u32)lbl_8010B600[g_d_GameSettings.challengeDifficulty][1] >> 1;
        } else {
            lbl_803C5F04.option[3] = (u32)lbl_8010B600[g_d_GameSettings.challengeDifficulty][0] >> 1;
        }
    }
#ifdef TARGET_PC
    if (!port_star_skills_enabled()) {
        lbl_803C5F04.option[2] = 0; // Star Skills off (port/game/menu_scope.c)
        lbl_803C5F04.prevOption[2] = 0;
    }
#endif
    if (g_d_GameSettings._06 == 2) {
        lbl_803C5F04._36 = 1;
        for (i = 0; i < 4; i++) {
            lbl_803C5F04.prevCursor[i] = 0;
            lbl_803C5F04.cursor[i] = 0;
        }
        lbl_803C5F04.state = 3;
    } else {
        lbl_803C5F04.prevCursor[0] = 0;
        lbl_803C5F04.cursor[0] = 0;
        lbl_803C5F04._36 = 0;
        lbl_803C5F04.state = 1;
    }
}
#endif

// .text:0x80049C80 size:0xBC
void fn_80049C80(void) {
    if (lbl_803C66B0.active[0] != 0 || lbl_803C66B0.active[1] != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 5 && lbl_8037169C.done == 0) {
        changeScene(1, 6);
    }
    lbl_803C5EA4._36 = 1;
    lbl_803C5EA4.prevMode = lbl_803C5EA4.mode;
    lbl_803C5EA4.mode = 3;
    possiblyTransferDataBetweenDifferentRels();
    memset(&lbl_803C5EE0, 0, 0x16);
    fn_800569C8();
    fn_800625A4(0, 0x29);
}

// .text:0x80049D3C size:0x50
void fn_80049D3C(void) {
    u8 mode = g_d_GameSettings.GameModeSelected;
    s32 i;

    if (mode == 6) {
        return;
    }
    if (lbl_803C5F04._36 == 0) {
        return;
    }
    for (i = 0; i < (mode == 6 ? 4 : 2); i++) {
    }
}

// .text:0x80049D8C size:0x370
// NONMATCHING ~85%: register allocation; switch-count selection layout
#if NONMATCHING
void fn_80049D8C(u8 dir, u8 team) {
    s32 count = 0;
    s8 cursor;

    lbl_803C5F04.prevCursor[team] = lbl_803C5F04.cursor[team];
    cursor = lbl_803C5F04.cursor[team];
    if (cursor == 0 && lbl_803C5F04._36 == 0) {
        return;
    }
#ifdef TARGET_PC
    if (cursor == 2 && lbl_803C5F04._36 == 0 && !port_star_skills_enabled()) {
        return; // Star Skills is locked off (port/game/menu_scope.c)
    }
#endif
    lbl_803C5F04.lastDir[team] = dir;
    if (dir == 0) {
        if (lbl_803C5F04._36 == 0) {
            if (cursor == 2 || cursor == 4) {
                goto increment;
            }
        decrement:
            lbl_803C5F04.prevOption[cursor] = lbl_803C5F04.option[cursor];
            lbl_803C5F04.option[cursor]--;
            switch (cursor) {
            case 3:
                count = 5;
                break;
            case 1:
            case 2:
            case 4:
                count = 2;
                break;
            }
            if (lbl_803C5F04.option[cursor] < 0) {
                lbl_803C5F04.option[cursor] = count - 1;
            }
            if (lbl_803C5F04.prevOption[cursor] != lbl_803C5F04.option[cursor]) {
                fn_800625A4(team, 0x30);
                sndFXRelated(2);
            }
        } else {
            lbl_803C5F04.prevPlayerOption[team][cursor] = lbl_803C5F04.playerOption[team][cursor];
            switch (cursor) {
            case 0:
                if (lbl_803C5F04.playerOption[team][0] != 0) {
                    lbl_803C5F04.playerOption[team][0] = 0;
                }
                break;
            case 1:
                if (lbl_803C5F04.playerOption[team][1] != 0) {
                    lbl_803C5F04.playerOption[team][1] = 0;
                }
                break;
            case 2:
                if (lbl_803C5F04.playerOption[team][2] != 0) {
                    lbl_803C5F04.playerOption[team][2] = 0;
                }
                break;
            case 3:
                if (lbl_803C5F04.playerOption[team][3] == 0) {
                    lbl_803C5F04.playerOption[team][3] = 1;
                }
                break;
            }
            if (lbl_803C5F04.prevPlayerOption[team][cursor] != lbl_803C5F04.playerOption[team][cursor]) {
                fn_800625A4(team, 0x30);
                sndFXRelated(2);
            }
        }
    } else {
        if (lbl_803C5F04._36 == 0) {
            if (cursor == 2 || cursor == 4) {
                goto decrement;
            }
        increment:
            lbl_803C5F04.prevOption[cursor] = lbl_803C5F04.option[cursor];
            lbl_803C5F04.option[cursor]++;
            switch (cursor) {
            case 3:
                count = 5;
                break;
            case 1:
            case 2:
            case 4:
                count = 2;
                break;
            }
            if (lbl_803C5F04.option[cursor] == count) {
                lbl_803C5F04.option[cursor] = 0;
            }
            if (lbl_803C5F04.prevOption[cursor] != lbl_803C5F04.option[cursor]) {
                fn_800625A4(team, 0x30);
                sndFXRelated(2);
            }
        } else {
            lbl_803C5F04.prevPlayerOption[team][cursor] = lbl_803C5F04.playerOption[team][cursor];
            switch (cursor) {
            case 0:
                if (lbl_803C5F04.playerOption[team][0] == 0) {
                    lbl_803C5F04.playerOption[team][0] = 1;
                }
                break;
            case 1:
                if (lbl_803C5F04.playerOption[team][1] == 0) {
                    lbl_803C5F04.playerOption[team][1] = 1;
                }
                break;
            case 2:
                if (lbl_803C5F04.playerOption[team][2] == 0) {
                    lbl_803C5F04.playerOption[team][2] = 1;
                }
                break;
            case 3:
                if (lbl_803C5F04.playerOption[team][3] != 0) {
                    lbl_803C5F04.playerOption[team][3] = 0;
                }
                break;
            }
            if (lbl_803C5F04.prevPlayerOption[team][cursor] != lbl_803C5F04.playerOption[team][cursor]) {
                fn_800625A4(team, 0x30);
                sndFXRelated(2);
            }
        }
    }
}
#endif

// .text:0x8004A0FC size:0xC0
void fn_8004A0FC(void) {
    s32 i;

    RESET_MATCH_OPTIONS(i);
}

// .text:0x8004A1BC size:0x100
void fn_8004A1BC(void) {
    s32 i;

    switch (lbl_803C5F04.state) {
    case 0:
        fn_80049C80();
        break;
    case 1:
        if (lbl_803C66B0.step[0] == 0) {
            lbl_803C5F04.state++;
        }
        break;
    case 2:
        for (i = 0; i < 2; i++) {
            fn_800494CC(i);
        }
        break;
    case 3:
        for (i = 0; i < 2; i++) {
            fn_80049220(i);
        }
        break;
    case 4:
        if (fn_80035838(&lbl_800FB5B0, 6) != 0) {
            lbl_803C5F04._32 = 1;
            lbl_803C5F04.state = 0;
        }
        break;
    case 5:
        startGameRelated();
        break;
    }
    fn_80049D3C();
}

// .text:0x8004A2BC size:0x6C
void fn_8004A2BC(void) {
    switch (lbl_803CBBCC->step) {
    case 0:
        fn_800B0A5C_insertQueue(fn_8004A1BC, 0x2000);
        lbl_803C5F04._2C = 0;
        lbl_803CBBCC->step++;
        break;
    case 1:
        break;
    }
}

// .text:0x8004A328 size:0x24
s32 fn_8004A328(MsgBox* box) {
    if (box->state != 0) {
        return 0;
    }
    box->state = 2;
    return 1;
}

// .text:0x8004A34C size:0x26C
s32 fn_8004A34C(MsgBox* box, s8 a, u8 msgId, s8 b, u8 arg) {
    MsgTask* task = NULL;
#ifdef TARGET_PC
    {
        // The boot card check's notices (see port_boot_card_quiet).
        extern s32 port_boot_card_quiet;
        if (port_boot_card_quiet && (msgId == 0 || msgId == 0xC || msgId == 0x10 || msgId == 0x22)) {
            return 1;
        }
    }
#endif

    box->msgId = msgId;
    box->_40 = a;
    box->_41 = b;
    box->state = 1;
    if (lbl_800FB5C0[msgId].kind == 10) {
        if (lbl_803C50E8.looping != 0) {
            if (lbl_803C50E8.loopStop != 0) {
                fn_8004CC18();
                lbl_803C50E8.loopStop = 0;
                lbl_803C50E8.looping = 0;
            } else if (lbl_803C50E8.loopMsg != lbl_800FB5C0[msgId].msg) {
                lbl_803C50E8.loopMsg = lbl_800FB5C0[msgId].msg;
                fn_8004CA14(0, lbl_800FB5C0[msgId].msg);
            }
        } else {
            fn_8004CC4C(lbl_800FB5C0[msgId].kind, 1, lbl_800FB5C0[msgId]._4, arg, lbl_800FB5C0[msgId].msg);
            if (lbl_800FB5C0[msgId]._5 != 0) {
                lbl_803C5F74._1E = 1;
            }
            fn_800B0A5C_insertQueue(fn_8004D0F0, 0x3000);
            lbl_803C50E8.loopStop = 0;
            lbl_803C50E8.looping = 1;
            lbl_803C50E8.loopMsg = lbl_800FB5C0[msgId].msg;
        }
    } else {
        if (lbl_803C50E8.looping != 0) {
            fn_8004CC18();
            lbl_803C50E8.looping = 0;
            lbl_803C50E8.loopStop = 0;
        }
        lbl_803C50E8.kind = lbl_800FB5C0[msgId].kind;
        lbl_803C50E8.msg = lbl_800FB5C0[msgId].msg;
        lbl_803C50E8._4E = lbl_800FB5C0[msgId]._4;
        lbl_803C50E8._4F = lbl_800FB5C0[msgId]._5;
        lbl_803C50E8.arg = arg;
        lbl_803C50E8.result = 0;
        switch (lbl_800FB5C0[msgId].type) {
        case 0:
            task = fn_800B0A5C_insertQueue(fn_8004A9E0, 0x8000);
            task->_1B = 1;
            break;
        case 1:
            task = fn_800B0A5C_insertQueue(fn_8004A7D0, 0x8000);
            task->_1B = 1;
            break;
        case 2:
            task = fn_800B0A5C_insertQueue(fn_8004A5B8, 0x8000);
            task->_1B = 1;
            break;
        case 3:
            task = fn_800B0A5C_insertQueue(fn_8004A7D0, 1);
            task->_1B = 0;
            break;
        }
    }
    if (task != NULL) {
        task->box = box;
        task->state = 0;
        task->box->_04 = 0;
    }
    return 1;
}

// .text:0x8004A5B8 size:0x218
void fn_8004A5B8(void) {
    MsgTask* task = lbl_803CC1B8;
    PadState* pads = lbl_803C77B8;
    u8 port = task->box->port;
    u16 buttons = pads[port].down & 0x100;

    lbl_803CBBCC->_10 |= 1 << port;
    switch (task->state) {
    case 0:
        lbl_803C50E8.done = 0;
        lbl_803C50E8.result = 0;
        lbl_803C50E8.cancel = 0;
        task->state++;
        break;
    case 1:
        fn_8004CC4C(lbl_803C50E8.kind, 1, lbl_803C50E8._4E, lbl_803C50E8.arg, lbl_803C50E8.msg);
        if (lbl_803C50E8._4F != 0) {
            lbl_803C5F74._1E = 1;
        }
        fn_800B0A5C_insertQueue(fn_8004D0F0, 0x3000);
        task->state = 3;
        break;
    case 2:
        task->state = 3;
        task->result = 0;
        break;
    case 3:
        if (lbl_803C50E8.cancel != 0) {
            fn_8004CC18();
            lbl_803C50E8.cancel = 0;
            task->result = 0;
            task->state = 5;
            break;
        }
        switch (fn_8004CA6C(buttons)) {
        case 0:
            task->result = 0;
            break;
        case 1:
            fn_8004CC2C();
            break;
        case 3:
            task->result = 2;
            task->state = 5;
            break;
        case 2:
            fn_8004CC2C();
            break;
        case 4:
            task->result = 2;
            task->state = 5;
            break;
        }
        break;
    case 4:
        task->timer = 15;
        task->state++;
        break;
    case 5:
        lbl_803C50E8.done = 1;
        lbl_803C50E8.result = task->result;
        fn_800B0A14_removeQueue(&lbl_803C50E8);
        task->_1B = 0;
        task->state = 0;
        break;
    }
}

// .text:0x8004A7D0 size:0x210
void fn_8004A7D0(void) {
    MsgTask* task = lbl_803CC1B8;
    PadState* pads = lbl_803C77B8;
    u8 port = task->box->port;
    u16 buttons = pads[port].down;

    lbl_803CBBCC->_10 |= 1 << port;
    switch (task->state) {
    case 0:
        lbl_803C50E8.done = 0;
        lbl_803C50E8.result = 0;
        lbl_803C50E8.cancel = 0;
        task->state++;
        break;
    case 1:
        fn_8004CC4C(lbl_803C50E8.kind, 1, lbl_803C50E8._4E, lbl_803C50E8.arg, lbl_803C50E8.msg);
        if (lbl_803C50E8._4F != 0) {
            lbl_803C5F74._1E = 1;
        }
        fn_800B0A5C_insertQueue(fn_8004D0F0, 0x3000);
        task->state++;
        break;
    case 2:
        if (lbl_803C50E8.cancel != 0) {
            fn_8004CC18();
            lbl_803C50E8.cancel = 0;
            task->result = 0;
            task->state = 3;
            break;
        }
        switch (fn_8004CA6C(buttons)) {
        case 0:
            task->result = 0;
            break;
        case 1:
            fn_8004CC2C();
            break;
        case 3:
            task->result = 2;
            task->state = 5;
            break;
        case 2:
            fn_8004CC2C();
            break;
        case 4:
            task->result = 4;
            task->state = 5;
            break;
        }
        break;
    case 3:
        task->state = 4;
        break;
    case 4:
        task->timer = 100;
        task->state++;
        break;
    case 5:
        lbl_803C50E8.done = 1;
        lbl_803C50E8.result = task->result;
        fn_800B0A14_removeQueue(&lbl_803C50E8);
        task->_1B = 0;
        task->state = 0;
        break;
    }
}

// .text:0x8004A9E0 size:0x1F8
void fn_8004A9E0(void) {
    MsgTask* task = lbl_803CC1B8;
    MsgTask* parent;
    PadState* pads = lbl_803C77B8;
    u8 port = task->box->port;
    u16 buttons = pads[port].down;

    lbl_803CBBCC->_10 |= 1 << port;
    switch (task->state) {
    case 0:
        task->timer = 15;
        task->state++;
        break;
    case 1:
        fn_8004CC4C(lbl_803C50E8.kind, 1, lbl_803C50E8._4E, lbl_803C50E8.arg, lbl_803C50E8.msg);
        if (lbl_803C50E8._4F != 0) {
            lbl_803C5F74._1E = 1;
        }
        fn_800B0A5C_insertQueue(fn_8004D0F0, 0x3000);
        task->state++;
        break;
    case 2:
        if (task->timer != 0) {
            task->timer--;
        } else {
            task->result = 0;
            task->state = 3;
        }
        break;
    case 3:
        if (buttons & 0x100) {
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            task->state++;
            task->result = 1;
        } else if (buttons & 0x200) {
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            task->state++;
            task->result = 4;
        }
        break;
    case 4:
        task->timer = 15;
        task->state++;
        break;
    case 5:
        if (task->timer != 0) {
            task->timer--;
        } else {
            parent = ((MsgTask*)lbl_803CC1B8)->parent;
            parent->result16 = task->result;
            fn_800B0A14_removeQueue(parent);
        }
        break;
    }
}

extern s32 lbl_803CBCFC;
extern s32 lbl_803CBD00;

extern s32 lbl_803CB848;

// Set_803cb848, size:0x8
void Set_803cb848(s32 value) {
    lbl_803CB848 = value;
}

// fn_8004ABE0, size:0x8
s32 fn_8004ABE0(void) {
    return lbl_803CBCFC;
}

// fn_8004ABE8, size:0x18
s32 fn_8004ABE8(s32 clear) {
    s32 value = lbl_803CBD00;
    if (clear != 0) {
        lbl_803CBD00 = 0;
    }
    return value;
}

// .text:0x8004AC00 size:0xC4
void fn_8004AC00(CharActor* model, s32 animID, u32 colorIdx, f32 frame) {
    if (lbl_80366158._28 == 1) {
        return;
    }
    if (model->kind == 0) {
        if (frame >= (f32)lbl_803CBCF8 && frame <= (f32)lbl_803CB850) {
            lbl_803CBD00 = 1;
            if (frame == 0.5) {
                lbl_803CBCFC = 1;
            } else {
                lbl_803CBCFC = 0;
            }
        }
    } else if (model->kind == 0x12) {
        fn_8004C19C(model, animID, colorIdx, frame);
    }
}

extern u32 lbl_803CBD08;

extern u32 lbl_803CBD04;

// fn_8004ACC4, size:0x18
u32 fn_8004ACC4(s32 clear) {
    u32 value = lbl_803CBD04;
    if (clear != 0) {
        lbl_803CBD04 = 0;
    }
    return value;
}

// fn_8004ACDC, size:0x18
u32 fn_8004ACDC(s32 clear) {
    u32 value = lbl_803CBD08;
    if (clear != 0) {
        lbl_803CBD08 = 0;
    }
    return value;
}

// .text:0x8004ACF4 size:0x60
void fn_8004ACF4(CharActor* model, s32 animID, u32 colorIdx, f32 frame) {
    switch (model->kind) {
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
        if (frame < 0.5f) {
            lbl_803CBD04 = 1;
        }
        break;
    }
    lbl_800FBE64[2](model, animID, colorIdx, frame);
}

// .text:0x8004AD54 size:0xC4
// NONMATCHING ~90%: nested switches instead of the original if/return chain (MWCC folds that to cntlzw)
#if NONMATCHING
s32 fn_8004AD54(u32 stadium, s32 flags) {
    s32 variant = flags & 0x7F;

    switch (stadium) {
    case 0:
        switch (variant) {
        case 1:
            return 1;
        default:
            return 0;
        }
    case 1:
        return 5;
    case 2:
        switch (variant) {
        case 1:
            return 11;
        default:
            return 10;
        }
    case 3:
        switch (variant) {
        case 1:
            return 7;
        default:
            return 6;
        }
    case 4:
        switch (variant) {
        case 10:
            return 4;
        case 1:
            return 3;
        default:
            return 2;
        }
    case 5:
        switch (variant) {
        case 10:
            return 9;
        default:
            return 8;
        }
    case 6:
        return 12;
    }
    return 0;
}
#endif


#pragma dont_inline off
// Copy of fn_8004AE18 (below) that the original inlines into fn_8004AFA8; the standalone
// body keeps its own copy because calling this from it changes the early-return branch.
static inline void fn_8004AE18_inline(s32 idx) {
    CharActor* model = lbl_8036E548.active[idx];
    Vec dir;
    Mtx m;

    lbl_800FBEA4.rgb = (lbl_800FC0FC.colors[fn_8004AD54(g_d_GameSettings.StadiumID, model->_275)].r << 24) |
                       ((lbl_800FC0FC.colors[fn_8004AD54(g_d_GameSettings.StadiumID, model->_275)].g << 16) & 0xFF0000) |
                       ((lbl_800FC0FC.colors[fn_8004AD54(g_d_GameSettings.StadiumID, model->_275)].b << 8) & 0xFF00);
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = 1.0f;
    PSMTXRotRad(m, 'Y', model->rot.y);
    PSMTXMultVec(m, &dir, &dir);
    fn_80030D88(&model->pos, &dir, (ParticleParams5 *)lbl_803CB84C, 5);
    if (model->kind == 0xE || model->kind == 0x25) {
        return;
    }
    if (model->_276 & 2) {
        getAnimRelatedCoordinates(idx, 0x1E, (VecXYZ*)&dir);
        fn_8002F1AC(&dir, idx * 2);
    }
    if (model->_276 & 4) {
        getAnimRelatedCoordinates(idx, 0x22, (VecXYZ*)&dir);
        fn_8002F1AC(&dir, idx * 2 + 1);
    }
}

// .text:0x8004AE18 size:0x190
void fn_8004AE18(s32 idx) {
    CharActor* model = lbl_8036E548.active[idx];
    Vec dir;
    Mtx m;

    lbl_800FBEA4.rgb = (lbl_800FC0FC.colors[fn_8004AD54(g_d_GameSettings.StadiumID, model->_275)].r << 24) |
                       ((lbl_800FC0FC.colors[fn_8004AD54(g_d_GameSettings.StadiumID, model->_275)].g << 16) & 0xFF0000) |
                       ((lbl_800FC0FC.colors[fn_8004AD54(g_d_GameSettings.StadiumID, model->_275)].b << 8) & 0xFF00);
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = 1.0f;
    PSMTXRotRad(m, 'Y', model->rot.y);
    PSMTXMultVec(m, &dir, &dir);
    fn_80030D88(&model->pos, &dir, (ParticleParams5 *)lbl_803CB84C, 5);
    if (model->kind == 0xE || model->kind == 0x25) {
        return;
    }
    if (model->_276 & 2) {
        getAnimRelatedCoordinates(idx, 0x1E, (VecXYZ*)&dir);
        fn_8002F1AC(&dir, idx * 2);
    }
    if (model->_276 & 4) {
        getAnimRelatedCoordinates(idx, 0x22, (VecXYZ*)&dir);
        fn_8002F1AC(&dir, idx * 2 + 1);
    }
}

// .text:0x8004AFA8 size:0x210
void fn_8004AFA8(s32 idx) {
    CharActor* model = lbl_8036E548.active[idx];
    Vec pos;

    lbl_803CB84C->stamp = lbl_803CBD0C;
    lbl_800FBE90.tex = lbl_803CBD0C;
    if (model->kind == 0xE || model->kind == 0x25) {
        return;
    }
    fn_8004AE18_inline(idx);
    if (model->_276 & 2) {
        getAnimRelatedCoordinates(idx, 0x1E, (VecXYZ*)&pos);
        fn_8002F258(&pos, idx * 2, (ParticleParams *)&lbl_800FBE90); // only reads the TrailParams prefix
    }
    if (model->_276 & 4) {
        getAnimRelatedCoordinates(idx, 0x22, (VecXYZ*)&pos);
        fn_8002F258(&pos, idx * 2 + 1, (ParticleParams *)&lbl_800FBE90); // only reads the TrailParams prefix
    }
}
#pragma dont_inline on

// fn_8004B1B8, size:0x8
void fn_8004B1B8(void* value) {
    lbl_803CBD0C = value;
}

// .text:0x8004B1C0 size:0x48
void fn_8004B1C0(s32 kind, CharActor* model, s32 animID, u32 colorIdx, f32 frame) {
    if (kind != 11) {
        lbl_800FBE64[kind](model, animID, colorIdx, frame);
    }
}

// .text:0x8004B208 size:0x68
void fn_8004B208(CharActor* model, s32 animID, u32 colorIdx, f32 frame) {
    s8 kind;

    if (lbl_803CB848 != 0 && animID >= 0 && animID < 0x75) {
        kind = lbl_800FBDEC[animID];
        if (kind != 11) {
            lbl_800FBE64[kind](model, animID, colorIdx, frame);
        }
    }
}

extern u32 lbl_803CBD04;

extern u32 lbl_803CBD08;

extern void* lbl_803CBD0C; // TexArchive* of the effect particles (set by fn_8004B1B8)

// fn_8004B270, size:0x14
void fn_8004B270(void) {
    lbl_803CBD0C = 0;
    lbl_803CBD08 = 0;
    lbl_803CBD04 = 0;
}

// ---- Data (initialisers generated from the original DOL) ----

// .data 0x800FB3F8..0x800FBF10
GXPerf0 lbl_800FB4C8[35] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32,
    33, 34, 35,
};
GXPerf1 lbl_800FB554[23] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22};
DiskFileEntry lbl_800FB5B0 = {1035, {0x4037CF5C}, {0x18B3A800}, 0x208AF0};
MsgDef lbl_800FB5C0[78] = {
    {168, 3, 10, 0, 0},
    {169, 1, 5, 0, 1},
    {170, 1, 4, 1, 0},
    {171, 2, 7, 0, 0},
    {172, 2, 7, 0, 0},
    {173, 1, 5, 0, 0},
    {174, 1, 5, 0, 0},
    {175, 2, 7, 0, 0},
    {176, 3, 10, 0, 0},
    {177, 1, 4, 0, 1},
    {178, 1, 4, 0, 1},
    {179, 1, 4, 0, 0},
    {180, 3, 10, 0, 0},
    {181, 2, 7, 0, 0},
    {182, 1, 6, 0, 0},
    {183, 1, 6, 0, 0},
    {184, 3, 10, 0, 0},
    {185, 1, 4, 0, 1},
    {186, 1, 4, 0, 0},
    {187, 1, 5, 0, 1},
    {188, 1, 5, 0, 1},
    {189, 1, 5, 0, 1},
    {190, 3, 10, 0, 0},
    {191, 1, 4, 0, 1},
    {192, 2, 7, 0, 0},
    {193, 1, 2, 0, 0},
    {194, 1, 2, 0, 0},
    {195, 1, 4, 0, 0},
    {196, 1, 4, 0, 0},
    {197, 1, 4, 0, 0},
    {198, 1, 4, 0, 0},
    {199, 1, 0, 0, 0},
    {200, 2, 7, 0, 0},
    {201, 2, 7, 0, 0},
    {202, 3, 10, 0, 0},
    {203, 1, 4, 0, 0},
    {204, 1, 4, 0, 0},
    {205, 2, 7, 0, 0},
    {206, 1, 4, 0, 0},
    {207, 1, 4, 0, 0},
    {208, 3, 10, 0, 0},
    {209, 1, 4, 1, 0},
    {210, 1, 4, 0, 1},
    {211, 1, 4, 0, 1},
    {212, 3, 10, 0, 0},
    {213, 2, 7, 0, 0},
    {214, 1, 4, 1, 0},
    {215, 1, 4, 1, 0},
    {216, 1, 4, 0, 1},
    {217, 1, 4, 0, 1},
    {218, 3, 10, 0, 0},
    {219, 2, 7, 0, 0},
    {220, 1, 4, 0, 0},
    {221, 1, 4, 0, 0},
    {222, 2, 7, 0, 0},
    {223, 2, 7, 0, 0},
    {224, 2, 7, 0, 0},
    {225, 1, 4, 0, 0},
    {226, 3, 10, 0, 0},
    {227, 2, 7, 0, 0},
    {228, 2, 7, 0, 0},
    {229, 2, 7, 0, 0},
    {230, 2, 7, 0, 0},
    {231, 1, 6, 0, 1},
    {232, 1, 6, 0, 1},
    {233, 1, 5, 0, 1},
    {234, 1, 5, 0, 1},
    {235, 1, 5, 0, 1},
    {236, 1, 5, 0, 1},
    {237, 1, 5, 0, 1},
    {238, 1, 5, 0, 1},
    {239, 1, 5, 0, 1},
    {240, 1, 5, 0, 1},
    {0, 1, 4, 0, 0},
    {446, 1, 2, 0, 0},
    {447, 2, 7, 0, 0},
    {448, 2, 7, 0, 0},
    {168, 3, 10, 0, 0},
}; // NOTE: type size 0x1D4 != symbol size 0x1D8
s16 lbl_800FB798[54] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};
s16 lbl_800FB804[54] = {
    28, 20, 36, 27, 14, 24, 28, 24,
    24, 29, 16, 19, 29, 29, 25, 30,
    26, 28, 29, 20, 30, 28, 28, 28,
    30, 30, 30, 20, 34, 29, 29, 29,
    29, 30, 30, 30, 30, 30, 20, 26,
    30, 26, 29, 30, 26, 26, 26, 26,
    26, 26, 26, 26, 20, 20,
};
s16 lbl_800FB870[54] = {
    20, 20, 20, 25, 5, 6, 14, 14,
    14, 21, 8, 14, 20, 22, 99, 22,
    22, 17, 13, 20, 16, 6, 6, 6,
    9, 9, 9, 4, 31, 22, 22, 22,
    22, 14, 14, 14, 14, 99, 8, 23,
    20, 32, 20, 16, 22, 22, 22, 22,
    20, 20, 20, 20, 4, 4,
};
s16 lbl_800FB8DC[54] = {
    32, 32, 27, 30, 13, 13, 32, 19,
    19, 35, 29, 20, 40, 33, 99, 40,
    39, 27, 28, 33, 23, 22, 22, 22,
    26, 26, 26, 20, 47, 33, 33, 33,
    33, 25, 25, 25, 25, 99, 14, 30,
    35, 34, 40, 23, 39, 39, 39, 39,
    32, 32, 32, 32, 20, 20,
};
s16 lbl_800FB948[54] = {
    18, 12, 30, 20, 7, 7, 20, 3,
    3, 21, 4, 12, 21, 21, 10, 23,
    20, 20, 18, 1, 21, 9, 9, 9,
    9, 9, 9, 5, 29, 21, 21, 21,
    21, 21, 21, 21, 21, 9, 8, 20,
    24, 22, 21, 21, 20, 20, 20, 20,
    20, 20, 20, 20, 5, 5,
};
s16 lbl_800FB9B4[54] = {
    28, 20, 36, 27, 14, 24, 28, 24,
    24, 29, 16, 19, 29, 29, 25, 30,
    26, 28, 29, 20, 30, 28, 28, 28,
    30, 30, 30, 20, 34, 29, 29, 29,
    29, 30, 30, 30, 30, 30, 20, 26,
    30, 26, 29, 30, 26, 26, 26, 26,
    26, 26, 26, 26, 20, 20,
};
s16 lbl_800FBA20[54] = {
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99,
};
s16 lbl_800FBA8C[54] = {
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99,
};
s16 lbl_800FBAF8[54] = {
    10, 10, 14, 13, 13, 13, 99, 10,
    10, 3, 10, 10, 11, 9, 99, 9,
    10, 10, 10, 10, 11, 10, 10, 10,
    10, 10, 10, 10, 9, 9, 9, 9,
    9, 99, 99, 99, 99, 99, 10, 10,
    10, 99, 11, 11, 14, 14, 14, 14,
    10, 10, 10, 10, 10, 10,
};
s16 lbl_800FBB64[54] = {
    30, 30, 28, 30, 30, 28, 25, 27,
    27, 30, 28, 28, 20, 25, 99, 25,
    28, 23, 28, 28, 25, 30, 30, 30,
    30, 30, 30, 22, 25, 25, 25, 25,
    25, 99, 99, 99, 99, 99, 19, 29,
    34, 99, 20, 25, 17, 17, 17, 17,
    30, 30, 30, 30, 22, 22,
};
s16 lbl_800FBBD0[54] = {
    12, 14, 8, 9, 9, 14, 12, 15,
    15, 13, 12, 10, 17, 99, 21, 22,
    21, 14, 13, 13, 15, 9, 9, 9,
    9, 9, 9, 6, 27, 21, 21, 21,
    21, 13, 13, 13, 13, 7, 15, 9,
    13, 15, 17, 15, 21, 21, 21, 21,
    12, 12, 12, 12, 6, 6,
};
s16 lbl_800FBC3C[54] = {
    15, 22, 13, 12, 13, 22, 15, 22,
    22, 16, 19, 13, 45, 99, 28, 22,
    25, 27, 22, 21, 20, 10, 10, 10,
    14, 14, 14, 11, 30, 28, 28, 28,
    28, 25, 25, 25, 25, 11, 16, 13,
    18, 18, 45, 20, 25, 25, 25, 25,
    15, 15, 15, 15, 11, 11,
};
s16 lbl_800FBCA8[54] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};
s16 lbl_800FBD14[54] = {
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99,
};
s16 lbl_800FBD80[54] = {
    22, 56, 99, 55, 28, 17, 50, 16,
    29, 99, 35, 65, 30, 41, 47, 19,
    15, 35, 38, 16, 40, 12, 12, 12,
    13, 13, 13, 16, 18, 41, 41, 41,
    41, 36, 36, 36, 36, 46, 94, 20,
    22, 52, 30, 40, 15, 15, 15, 15,
    6, 6, 6, 6, 16, 16,
};
s8 lbl_800FBDEC[120] = {
    11, 11, 11, 11, 11, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    1, 11, 11, 11, 11, 11, 11, 11, 11, 11, 0, 0, 4, 11, 11, 11,
    11, 11, 3, 11, 4, 8, 11, 11, 5, 5, 5, 5, 5, 3, 3, 3,
    0, 11, 0, 0, 0, 11, 3, 3, 11, 11, 11, 3, 11, 11, 11, 11,
    11, 6, 11, 6, 11, 11, 7, 11, 10, 11, 11, 11, 11, 11, 11, 11,
    11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
    11, 11, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
    11, 11, 11, 11, 11, 0, 0, 0,
};
void fn_8004BEB0(struct CharActor* model, s32 animID, u32 colorIdx, f32 frame);
void fn_8006C444(void* obj, f32 frame, s32 a, s32 b);
void fn_8006C3F8(void* obj, f32 frame, s32 a, s32 b);
#if NONMATCHING
// Port build: three handlers have other C signatures (same PPC registers), and wasm checks
// the type of indirect calls, so they go through SwingFxFunc-shaped adapters.
static void SwingFx_8004C5F8(CharActor* model, s32 animID, u32 colorIdx, f32 frame) {
    fn_8004C5F8(model, animID, colorIdx);
}
static void SwingFx_8006C444(CharActor* model, s32 animID, u32 colorIdx, f32 frame) {
    fn_8006C444(model, frame, animID, colorIdx);
}
static void SwingFx_8006C3F8(CharActor* model, s32 animID, u32 colorIdx, f32 frame) {
    fn_8006C3F8(model, frame, animID, colorIdx);
}
#define SWINGFX_ADAPT(fn) SwingFx_##fn
#else
#define SWINGFX_ADAPT(fn) (SwingFxFunc)fn_##fn
#endif
SwingFxFunc lbl_800FBE64[11] = {
    fn_8004B284,
    fn_8004BEB0,
    fn_8004C510,
    SWINGFX_ADAPT(8004C5F8),
    fn_80062C60,
    fn_80062E6C,
    fn_8004C19C,
    SWINGFX_ADAPT(8006C444),
    SWINGFX_ADAPT(8006C3F8),
    fn_8004ACF4,
    fn_8004AC00,
};
TrailParams lbl_800FBE90 = {NULL, 5, 40000, 128, 64};
EffectParams lbl_800FBEA4 = {
    NULL,
    4,
    2,
    80000,
    30000,
    {78000, 50, 5, 109000, 101000, 0, 40, 12800000, 8000000, 0, 0},
    0xFFFFFF00,
    {0, 75000, 0},
};

// .bss 0x802E4B00..0x802E4BB0 (MWCC lays these out in reverse definition order)
GPMetrics lbl_802E4B28;
u8 lbl_802E4B14[2][9];
u8 lbl_802E4B00[2][9];

// .sdata 0x803CB838..0x803CB860
s32 lbl_803CB838 = 1;
s32 lbl_803CB83C[2] = {0, 0};
s32 lbl_803CB848 = 1;
EffectParams *lbl_803CB84C = &lbl_800FBEA4;
s32 lbl_803CB850 = 45; // TODO: followed by two zero words and an unreferenced -1 (0x803CB85C)

// .sbss 0x803CBCC8..0x803CBD0C (MWCC lays these out in reverse definition order)
u32 lbl_803CBD08;
u32 lbl_803CBD04;
s32 lbl_803CBD00;
s32 lbl_803CBCFC;
s32 lbl_803CBCF8;
s32 lbl_803CBCF0;
u32 lbl_803CBCE8;
u8 lbl_803CBCE0[8]; // menu flags (menus)
u8 lbl_803CBCD8[8]; // menu flags (menus)
OrderEntry lbl_803CBCD0[2];
u8 lbl_803CBCCC[2];
u8 lbl_803CBCC9;
u8 lbl_803CBCC8;

