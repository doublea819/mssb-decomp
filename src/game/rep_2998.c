#include "game/rep_2998.h"
#include "game/UnknownHomes_Game.h"
#include "static/GameSettings.h"
#include "game/rep_540.h"
#include "game/rep_1838.h"
#include "game/rep_23E8.h"
#include "game/rep_AC8.h"
#include "game/auto_00_000B7EF0_text.h"
#include "game/auto_00_000D8A10_text.h"
#include "main/file_800B4A44.h"
#include "main/file_800BD3EC.h"
#include "main/file_80011640.h"
#include "main/file_8004207C.h"
#include "C3/control.h"
#include "musyx/musyx.h"
#define REP_HEADER_FN repHeader_2998
#include "header_rep_inline.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern void* _OSAllocFromHeap(s32 align, s32 size);

// rep_1D58 (stadium objects). Not from rep_1D58.h: there fn_3_B97DC takes u8*,
// fn_3_B7FC8 (void*, void*) and fn_3_B9D68 a (void) stub.
void fn_3_B939C(void);
// m_sound.h (can't be included next to UnknownHomes_Game.h: playSoundEffect differs)
void fn_3_8B890(s32 i);
s32 fn_3_8BBC4(s32 id, f32* pos, f32* dir, s32 type);
s32 fn_3_B7FC8(s32 id, s32 type);
void fn_3_B8414(Vec* min, Vec* max);
void fn_3_B8464(Mtx m, void* shadow);
void fn_3_B8574(void);
void fn_3_B97DC(ActorObject* obj, void* animBank);
void fn_3_B98E8(ActorObject* obj);
void fn_3_B9D68(void* names, s32 n, void** files, u32* out);

extern StadiumObjList lbl_3_common_bss_350E4;
extern PiranhaSpot lbl_3_data_18ED0[];
extern PiranhaFielder g_Fielders[9];
extern u8 lbl_3_data_19004[];             // file kinds for fn_3_B9D68
extern u16 lbl_3_data_81DC[];             // per stadium: crowd sound id base
extern MinigameSoundParams lbl_3_data_8404[];
extern MinigameSoundParams lbl_3_data_84B8[];

extern const u8 lbl_3_rodata_29F4[4]; // rise frames: 20, 20, 20
extern const f32 lbl_3_rodata_29F8[3]; // bite animation speeds: 0.8, 1.0, 1.2
extern Vec lbl_3_rodata_2A48;
extern const f32 lbl_3_rodata_2B20;
extern f32 lbl_3_rodata_2B24;
extern f32 lbl_3_rodata_2A54;
extern const f32 lbl_3_rodata_2A58;
extern f32 lbl_3_rodata_2A5C;
extern f32 lbl_3_rodata_2A60;
extern f32 lbl_3_rodata_2A64;
extern f32 lbl_3_rodata_2AC0;
extern f64 lbl_3_rodata_2AB8;
extern f64 lbl_3_rodata_2A98;
extern f64 lbl_3_rodata_2AC8;
extern f64 lbl_3_rodata_2AD0;
extern f64 lbl_3_rodata_2AD8;
extern const f64 lbl_3_rodata_2AE0;
extern f32 lbl_3_rodata_2B2C;
extern f32 lbl_3_rodata_2B30;

// This unit's .bss. MWCC lays statics out in reverse order of declaration.
static void* lbl_3_bss_AE18[14]; // animation banks: 0 idle, 1 rise, 2/3 look, 4/5 bite, 6 catch on the ground,
                                 // 7 hold, 8 hit, 9 sink
static u8 lbl_3_bss_AE14;        // number of plants (counted again by fn_3_E4FC4)
static u8 lbl_3_bss_AE13;
static u8 lbl_3_bss_AE12;        // number of dummy objects
static u8 lbl_3_bss_AE11;        // number of plants
static u8 lbl_3_bss_AE10;        // ambient sound playing
static s32 lbl_3_bss_AE0C;       // frames until the next ambient sound 6
static s32 lbl_3_bss_AE08;       // frames until the next ambient sound 7
static s32 lbl_3_bss_AE04;       // ambient sound handle
static u8 lbl_3_bss_AE01;        // nonzero: fn_3_E4A38 takes the vertices as they are
static u8 lbl_3_bss_AE00;

#define PLANT(i) (&lbl_3_common_bss_350E4.objs[i])

#define SET_ANIM_BANK(p) fn_3_B97DC((p)->actorObj, (p)->animBank)

static inline void playCrowdSound(s32 n) {
    s32 stadium;
    u8 vol;
    SND_VOICEID voice;

    stadium = g_d_GameSettings.StadiumID;
    if (g_d_GameSettings.GameModeSelected == 6) {
        vol = lbl_3_data_84B8[n].vol;
    } else {
        vol = lbl_3_data_8404[stadium * 15 + n].vol;
    }
    voice = sndFXStartEx(lbl_3_data_81DC[stadium] + n, vol, 0x3F, 0);
    if (g_d_GameSettings.GameModeSelected == 6) {
        vol = lbl_3_data_84B8[n].ctrl;
    } else {
        vol = lbl_3_data_8404[stadium * 15 + n].ctrl;
    }
    sndFXCtrl(voice, 0x5B, vol);
}

static inline void setBallPos(f32 x, f32 y, f32 z) {
    g_Ball.AtBat_Contact_BallPos.x = x;
    g_Ball.AtBat_Contact_BallPos.y = y;
    g_Ball.AtBat_Contact_BallPos.z = z;
}

// .text:0x000E1DB8 size:0x1F0 mapped:0x80720E4C
// Ambient plant sounds while the stadium is up.
void fn_3_E1DB8(void) {
    if (g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_READY) {
        return;
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_PAUSED) {
        if (lbl_3_bss_AE10 != 0) {
            fn_3_8B890(lbl_3_bss_AE04);
            lbl_3_bss_AE10 = 0;
        }
        return;
    }
    if (lbl_3_bss_AE10 == 0) {
        lbl_3_bss_AE04 = fn_3_8BBC4(lbl_3_data_81DC[g_d_GameSettings.StadiumID] + 5, NULL, NULL, 6);
        lbl_3_bss_AE10 = 1;
        lbl_3_bss_AE0C = rand() % 900 + 100;
        lbl_3_bss_AE08 = rand() % 900 + 100;
    }
    if (lbl_3_bss_AE0C <= 0) {
        fn_3_B7FC8(lbl_3_data_81DC[g_d_GameSettings.StadiumID] + 6, 7);
        lbl_3_bss_AE0C = rand() % 900 + 100;
    } else {
        lbl_3_bss_AE0C--;
    }
    if (lbl_3_bss_AE08 <= 0) {
        fn_3_B7FC8(lbl_3_data_81DC[g_d_GameSettings.StadiumID] + 7, 7);
        lbl_3_bss_AE08 = rand() % 900 + 100;
    } else {
        lbl_3_bss_AE08--;
    }
}

// .text:0x000E1FA8 size:0x8C mapped:0x8072103C
// Update of the dummy object: loops its animation.
void fn_3_E1FA8(PiranhaPlant* p) {
    ActorObject* o = p->actorObj;
    GameActor* actor = o->actor;
    if (o->time + o->unk54 > lbl_3_rodata_2A54) {
        o->time = lbl_3_rodata_2A58;
        o->setTime = 1;
        fn_800B4CA0(actor, o->time);
    }
    AnimateActorBones(actor);
    o->time = o->time + o->unk54;
}

// .text:0x000E2034 size:0xE4 mapped:0x807210C8
// Turn to face the ball.
void fn_3_E2034(PiranhaPlant* p) {
    Vec v2;
    Vec v1;
    f32 r;
    v1 = lbl_3_rodata_2A48;
    PSVECSubtract(&g_Ball.AtBat_Contact_BallPos, &p->pos, &v2);
    v2.y = lbl_3_rodata_2A5C;
    PSVECNormalize(&v2, &v2);
    PSVECNormalize(&v1, &v1);
    r = lbl_3_rodata_2A60 * (f32)acos(PSVECDotProduct(&v2, &v1));
    if (v2.x < lbl_3_rodata_2A5C) {
        r = lbl_3_rodata_2A64 - r;
    }
    {
        p->rotY = -r;
        CTRLSetRotation(&p->ctrl.base, 0.0f, p->rotY, 0.0f);
    }
}

// .text:0x000E2118 size:0x18C mapped:0x807211AC
// The ball hit plant idx.
void fn_3_E2118(s32 idx, s32 hitType, struct _CollisionStruct* hit) {
    PiranhaPlant* p = PLANT(idx);
    u8 state = p->state;
    if (state == 0 || state == 5) {
        return;
    }
    if (p->sleepy != 0 && state != 4) {
        if (g_Ball.AtBat_ContactResult > 1) {
            return;
        }
        p->wasHit = 1;
        p->state = 4;
        fn_3_E25D0(p, 8);
        playCrowdSound(2);
    }
    fn_3_65A8();
    fn_3_27648();
    g_FieldingLogic._13B = 1;
}

// .text:0x000E22A4 size:0x80 mapped:0x80721338
// Before drawing: pick the texture frame (blink while rising or sinking).
void fn_3_E22A4(PiranhaPlant* p) {
    // first display state of the first object: its setting holds the texture frame
    u8 st;
    u8 v;
    DisplayStateList* r;
#ifdef TARGET_PC
    {
        // On PC a palette's descriptors hold display objects only after fn_800BCE38
        // built them; otherwise they still hold layouts (see GeoPaletteHasDispObjs).
        DODisplayDataPtr pal = p->actorObj->actor->pal;
        DODescriptor* desc = PTR32_GET(DODescriptor, pal->descriptorArray);
        DisplayData* dd;
        if (GeoPaletteHasDispObjs(pal)) {
            dd = PTR32_GET(struct DODisplayObj, desc[0].dispObj)->displayData;
        } else {
            dd = PTR32_GET(DisplayData, PTR32_GET(DODisplayLayout, desc[0].layout)->displayData);
        }
        r = PTR32_GET(DisplayStateList, dd->displayStateList);
    }
#else
    r = PTR32_GET(DisplayStateList, PTR32_GET(struct DODisplayObj, PTR32_GET(DODescriptor, p->actorObj->actor->pal->descriptorArray)[0].dispObj)->displayData->displayStateList);
#endif
    r->setting &= ~0x1FFF;
    st = p->state;
    if (st != 0) {
        v = p->sleepy + 1;
        if (st == 1 || st == 5) {
            if (p->timer % 2 == 0) {
                v = 0;
            }
        }
        r->setting |= v;
    }
}

// .text:0x000E2324 size:0x2AC mapped:0x807213B8
// Knock back fielders that come close to the plant's head.
void fn_3_E2324(PiranhaPlant* p) {
    Mtx bone;
    Mtx m;
    Vec fpos;
    Vec diff;
    Vec dir;
    u8 fielders[7] = {2, 3, 4, 5, 6, 7, 8};
    Vec head = {0.0f, 0.0f, 0.0f};
    u32 i;
    f32 range;
    s32 ang;
    PiranhaFielder* f;

    if (p->holdingBall != 0) {
        return;
    }
    PSMTXCopy(p->actorObj->actor->boneArray[16]->forwardMtx, bone);
    CTRLBuildMatrix(&p->ctrl.base, m);
    PSMTXConcat(m, bone, m);
    PSMTXMultVec(m, &head, &head);
    head.y *= -1.0f;
    range = 2.2f * p->scale;
    for (i = 0; i < 7; i++) {
        f = &g_Fielders[fielders[i]];
        if (f->knockback != 0) {
            continue;
        }
        fpos.x = f->pos.x;
        fpos.y = 1.5f;
        fpos.z = f->pos.z;
        PSVECSubtract(&head, &fpos, &diff);
        dir.x = diff.x;
        dir.y = 0.0f;
        dir.z = diff.z;
        PSVECNormalize(&dir, &dir);
        if (PSVECMag(&diff) <= range) {
            ang = fn_3_9FB8C(dir.x, dir.z);
            fn_3_253A4(fielders[i], ang);
            if (p->anim != 8 && p->holdingBall == 0) {
                fn_3_E25D0(p, 9);
                p->state = 5;
            }
            playCrowdSound(4);
        }
    }
}

// .text:0x000E25D0 size:0x9C mapped:0x80721664
void fn_3_E25D0(PiranhaPlant* p, u32 anim) {
    p->animBank = lbl_3_bss_AE18[anim];
    SET_ANIM_BANK(p);
    if (anim != 0 && anim != 2 && anim != 3) {
        p->actorObj->visFlags = 2;
        fn_800B4AFC(p->actorObj->actor, p->actorObj->visFlags & 1);
    }
    p->animTime = p->actorObj->time;
    p->anim = anim;
}

// .text:0x000E266C size:0x270 mapped:0x80721700
// When an animation ends, pick the next one.
void fn_3_E266C(PiranhaPlant* p) {
    ActorObject* o = p->actorObj;
    if (p->animBank == NULL) {
        return;
    }
    if (!(o->visFlags & 1) && !fn_800B4A94(o->actor)) {
        switch (p->anim) {
        case 1:
            if (p->state == 5 || p->state == 0) {
                fn_3_E25D0(p, 0);
                break;
            }
            // fallthrough
        case 4:
        case 5:
            if (p->sleepy == 0) {
                fn_3_E25D0(p, 2);
            } else {
                fn_3_E25D0(p, 3);
            }
            break;
        case 7:
            p->rotY = -p->spitAngle;
            fn_3_E25D0(p, 8);
            CTRLSetRotation(&p->ctrl.base, 0.0f, p->rotY, 0.0f);
            break;
        case 8:
            fn_3_E25D0(p, 9);
            p->state = 5;
            break;
        default:
            fn_3_E25D0(p, 0);
            break;
        }
    }
    AnimateActorBones(o->actor);
    p->animTime = fn_800B4C40(o->actor);
}

// .text:0x000E28DC size:0xD8 mapped:0x80721970
// Snap at a ball rolling on the ground next to the plant.
u8 fn_3_E28DC(PiranhaPlant* p) {
    Vec v1;
    Vec v2;
    v1 = p->pos;
    PSVECSubtract(&g_Ball.AtBat_Contact_BallPos, &v1, &v2);
    v2.y = 0.0f;
    if (2.5 >= PSVECMag(&v2)) {
        p->animBank = lbl_3_bss_AE18[6];
        SET_ANIM_BANK(p);
        p->actorObj->visFlags = 2;
        fn_800B4AFC(p->actorObj->actor, p->actorObj->visFlags & 1);
        p->animTime = p->actorObj->time;
        p->anim = 6;
        return 1;
    }
    return 0;
}

// .text:0x000E29B4 size:0x1BC mapped:0x80721A48
// Bite at a ball flying past the plant's head.
u8 fn_3_E29B4(PiranhaPlant* p) {
    Vec pos;
    Vec d;
    ActorObject* o;
    s16 r;
    pos = p->pos;
    PSVECSubtract(&g_Ball.AtBat_Contact_BallPos, &pos, &d);
    d.y = 0.0f;
    if (5.5 * p->scale > PSVECMag(&d) && g_Ball.AtBat_Contact_BallPos.y >= 1.5 * p->scale &&
        g_Ball.AtBat_Contact_BallPos.y <= 8.5 * p->scale) {
        if (g_Ball.AtBat_Contact_BallPos.y < 5.0 * p->scale) {
            fn_3_E25D0(p, 4);
        } else {
            fn_3_E25D0(p, 5);
        }
        r = fn_3_B7F70(3);
        o = p->actorObj;
        o->unk54 = lbl_3_rodata_29F8[r];
        o->setSpeed = 1;
        fn_800B4C04(p->actorObj->actor, p->actorObj->unk54);
        return 1;
    }
    return 0;
}

// .text:0x000E2B70 size:0x308 mapped:0x80721C04
// Returns nonzero if the plant bites at the ball this frame.
u8 fn_3_E2B70(PiranhaPlant* p) {
    Vec d;
    if (g_Ball.AtBat_ContactResult >= 2) {
        return 0;
    }
    if (p->sleepy != 0) {
        return 0;
    }
    if (g_Ball.deadBallReason == 1 || g_Ball.deadBallReason == 3) {
        return 0;
    }
    if (p->anim >= 4 && p->anim <= 6) {
        return 1;
    }
    PSVECSubtract(&g_Ball.AtBat_Contact_BallPos, &g_Ball.pastCoordinates[0], &d);
    if (lbl_3_rodata_2A5C != PSVECMag(&d)) {
        return fn_3_E29B4(p);
    }
    return fn_3_E28DC(p);
}

// .text:0x000E2E78 size:0xD4 mapped:0x80721F0C
// Sinking back into the ground.
void fn_3_E2E78(PiranhaPlant* p) {
    if (p->timer == 0) {
        p->sleepy = 0;
        p->state = 0;
    } else {
        p->scale = p->scale - 1.0857142857142859 / p->riseFrames;
        p->pos.y = -(1.2 * p->scale);
        CTRLSetTranslation(&p->ctrl.base, p->pos.x, -p->pos.y, p->pos.z);
        CTRLSetScale(&p->ctrl.base, p->scale, p->scale, p->scale);
        p->timer -= 1;
    }
}

// .text:0x000E2F4C size:0xF8 mapped:0x80721FE0
// Spitting: puff of smoke at frame 20.
void fn_3_E2F4C(PiranhaPlant* p) {
    f32 ang;
    f32 x;
    f32 c;
    f32 s;
    f32 sc;
    f32 b8 = p->animTime;
    f32 d54 = p->actorObj->unk54;
    if (b8 >= 20.0) {
        if (b8 - d54 < 20.0) {
            if (lbl_800E8754._04 != 0) {
                ang = -p->rotY;
                ang = lbl_3_rodata_2AC0 * ang;
                s = sin(ang);
                x = p->scale * (lbl_3_rodata_2A98 * s) + p->pos.x;
                c = cos(ang);
                sc = p->scale;
                fn_3_CB7E8(x, lbl_3_rodata_2AC8 * sc, sc * (lbl_3_rodata_2AD0 * c) + p->pos.z);
            }
        }
    }
}

// .text:0x000E3044 size:0x240 mapped:0x807220D8
// Holding the ball: spin, then spit it out at frame 20.
void fn_3_E3044(PiranhaPlant* p) {
    f32 speed = p->actorObj->unk54;
    f32 ang;
    f32 x;
    f32 s;
    f32 c;
    f32 sc;
    if (p->anim == 7) {
        p->rotY += p->spinSpeed;
        CTRLSetRotation(&p->ctrl.base, 0.0f, p->rotY, 0.0f);
        return;
    }
    if (p->animTime >= 20.0 && p->animTime - speed < 20.0) {
        ang = p->spitAngle;
        ang = lbl_3_rodata_2AC0 * ang;
        s = sin(ang);
        x = p->scale * (lbl_3_rodata_2A98 * s) + p->pos.x;
        c = cos(ang);
        sc = p->scale;
        setBallPos(x, lbl_3_rodata_2AD8 * sc, sc * (lbl_3_rodata_2AD0 * c) + p->pos.z);
        g_Ball.physicsSubstruct.velocity.x = lbl_3_rodata_2AE0 * (f32)sin(ang);
        g_Ball.physicsSubstruct.velocity.y = lbl_3_rodata_2A5C;
        c = cos(ang);
        g_Ball.physicsSubstruct.velocity.z = lbl_3_rodata_2AE0 * -c;
        fn_3_65F4();
        p->holdingBall = 0;
        playCrowdSound(1);
    }
}

// .data 0x00018D98..0x00019018
f32 lbl_3_data_18D98[14] = {1.0f, 1.2f, 18.8f, 0.15f, 19.5f, 0.7f, 0.0f, 0.15f, 38.8f, 0.0f, -18.8f, 0.15f, 19.5f, -0.7f};
f32 lbl_3_data_18DD0 = 0.2f;
f32 lbl_3_data_18DD4[12] = {-225.0f, -30.0f, 0.0f, -75.0f, -30.0f, 0.0f, 75.0f, -30.0f, 0.0f, 225.0f, -30.0f, 0.0f};
VecXYZ lbl_3_data_18E04[4][4] = {
    {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
    {{-1.2f, 0.0f, 0.0f}, {1.2f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
    {{-2.4f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {2.4f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
    {{-3.6f, 0.0f, 0.0f}, {-1.2f, 0.0f, 0.0f}, {1.2f, 0.0f, 0.0f}, {3.6f, 0.0f, 0.0f}},
};
f32 lbl_3_data_18EC4[3] = {-1.5f, 0.0f, 1.5f};
PiranhaSpot lbl_3_data_18ED0[11] = {
    {{-18.0f, 0.0f, 52.0f}, 0.0f, 0, 1, 1, 0, 0.0f, 360.0f},
    {{-35.0f, 0.0f, 35.0f}, 0.0f, 0, 1, 2, 0, 315.0f, 180.0f},
    {{35.0f, 0.0f, 35.0f}, 0.0f, 0, 1, 3, 0, 225.0f, 180.0f},
    {{18.0f, 0.0f, 52.0f}, 0.0f, 0, 1, 4, 0, 0.0f, 360.0f},
    {{34.0f, 0.0f, 78.0f}, 0.0f, 0, 1, 5, 0, 0.0f, 360.0f},
    {{-34.0f, 0.0f, 78.0f}, 0.0f, 0, 1, 6, 0, 0.0f, 360.0f},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 2, 0, 255, 0, 0.0f, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0, 0.0f, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0, 0.0f, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0, 0.0f, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0, 0.0f, 0.0f},
};
u8 lbl_3_data_19004[20] = {1, 3, 4, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0};

// .text:0x000E3284 size:0x3E4 mapped:0x80722318
// Catch the ball if it passes through the plant's mouth.
u8 fn_3_E3284(PiranhaPlant* p) {
    Mtx m;
    Mtx bone;
    Vec mouth = {0.0f, 0.0f, 0.0f};
    Vec up = {0.0f, -1.0f, 0.0f};
    Vec cross;
    Vec facing;
    Vec spit;
    f32 range;
    f32 base;
    f32 ang;
    f32 a;

    PSMTXCopy(p->actorObj->actor->boneArray[16]->forwardMtx, bone);
    CTRLBuildMatrix(&p->ctrl.base, m);
    PSMTXConcat(m, bone, m);
    PSMTXMultVec(m, &mouth, &mouth);
    mouth.y *= -1.0f;
    range = 2.2f * p->scale;
    if ((f32)fabs(fn_3_9EFD0(&g_Ball.pastCoordinates[0], &g_Ball.AtBat_Contact_BallPos, &mouth, NULL)) <= range) {
        p->state = 3;
        fn_3_E25D0(p, 7);
        p->holdingBall = 1;
        fn_3_6620();
        base = lbl_3_data_18ED0[p->spot].spitAngle;
        p->spitAngle = base + fn_3_B7F70((u32)(10.0f * lbl_3_data_18ED0[p->spot].spitSpread)) / 10.0;
        g_Ball.physicsSubstruct.velocity.z = 0.0f;
        g_Ball.physicsSubstruct.velocity.y = 0.0f;
        g_Ball.physicsSubstruct.velocity.x = 0.0f;
        facing.x = sin(-(0.017453292f * p->rotY));
        facing.y = 0.0f;
        facing.z = -(f32)cos(-(0.017453292f * p->rotY));
        spit.x = sin(0.017453292f * p->spitAngle);
        spit.y = 0.0f;
        spit.z = -(f32)cos(0.017453292f * p->spitAngle);
        PSVECNormalize(&facing, &facing);
        PSVECNormalize(&spit, &spit);
        a = acos(PSVECDotProduct(&facing, &spit));
        ang = a;
        if (a) {
            PSVECCrossProduct(&facing, &spit, &cross);
            if (!(PSVECDotProduct(&cross, &up) > 0.0f)) {
                ang *= -1.0f;
            }
        }
        p->spinSpeed = -(57.29578f * (ang / 60.0f));
        playCrowdSound(0);
        return 1;
    }
    return 0;
}

// .text:0x000E3668 size:0xFC mapped:0x807226FC
// Up: bite at the ball or keep facing it.
void fn_3_E3668(PiranhaPlant* p) {
    Vec v1;
    Vec v2;
    f32 r;
    if (fn_3_E2B70(p)) {
        fn_3_E3284(p);
        return;
    }
    v1 = lbl_3_rodata_2A48;
    PSVECSubtract(&g_Ball.AtBat_Contact_BallPos, &p->pos, &v2);
    v2.y = lbl_3_rodata_2A5C;
    PSVECNormalize(&v2, &v2);
    PSVECNormalize(&v1, &v1);
    r = lbl_3_rodata_2A60 * (f32)acos(PSVECDotProduct(&v2, &v1));
    if (v2.x < lbl_3_rodata_2A5C) {
        r = lbl_3_rodata_2A64 - r;
    }
    p->rotY = -r;
    CTRLSetRotation(&p->ctrl.base, 0.0f, p->rotY, 0.0f);
}

// .text:0x000E3764 size:0x1B0 mapped:0x807227F8
// Rising out of the ground.
void fn_3_E3764(PiranhaPlant* p) {
    p->timer++;
    p->scale = p->scale + 1.0857142857142859 / p->riseFrames;
    CTRLSetScale(&p->ctrl.base, p->scale, p->scale, p->scale);
    p->pos.y = -(1.2 * p->scale);
    CTRLSetTranslation(&p->ctrl.base, p->pos.x, -p->pos.y, p->pos.z);
    if (fn_3_E2B70(p)) {
        if (fn_3_E3284(p)) {
            return;
        }
    } else {
        fn_3_E2034(p);
    }
    if (p->timer >= p->riseFrames) {
        p->state = 2;
    }
}

// .text:0x000E3914 size:0x274 mapped:0x807229A8
// Hidden: rise when a batted ball comes low and near.
void fn_3_E3914(PiranhaPlant* p) {
    Vec pos;
    Vec d;
    u8 star;
    if (p->active != 0) {
        return;
    }
    if (g_Ball.AtBat_ContactResult >= 2) {
        return;
    }
    if (g_Ball.AtBat_Contact_BallPos.y > 11.0) {
        return;
    }
    pos = p->pos;
    pos.y += 1.4000000000000001;
    PSVECSubtract(&g_Ball.AtBat_Contact_BallPos, &pos, &d);
    d.y = 0.0f;
    if (!(PSVECMag(&d) <= 12.5)) {
        return;
    }
    star = g_Ball.currentStarSwing2;
    if ((star == 3) | (star == 4) | (star == 11) | (star == 12)) {
        return;
    }
    p->state = 1;
    fn_3_E25D0(p, 1);
    if (p->wasHit == 0) {
        p->sleepy = fn_3_B7F70(100) / 70;
    } else {
        p->sleepy = 0;
    }
    p->timer = 0;
    p->riseFrames = lbl_3_rodata_29F4[fn_3_B7F70(3)];
    p->active = 1;
    playCrowdSound(3);
}

// .text:0x000E3B88 size:0x9CC mapped:0x80722C1C
// Per-frame update.
void fn_3_E3B88(PiranhaPlant* p) {

    if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        if (p->state != 0) {
            fn_3_E48D0(p);
        } else if (p->active != 0) {
            CTRLSetRotation(&p->ctrl.base, 0.0f, lbl_3_data_18ED0[p->spot].rotY, 0.0f);
            p->rotY = lbl_3_data_18ED0[p->spot].rotY;
            fn_3_E4554(p);
            if (p->holdingBall != 0) {
                fn_3_65F4();
                p->holdingBall = 0;
                p->spinSpeed = 0.0f;
            }
            p->active = 0;
        }
    } else {
        if (p->holdingBall != 0) {
            // keep the ball in the mouth
            Mtx bone;
            Mtx m;
            Vec mouth = {0.0f, 0.0f, 0.0f};
            PSMTXCopy(p->actorObj->actor->boneArray[17]->forwardMtx, bone);
            CTRLBuildMatrix(&p->ctrl.base, m);
            PSMTXConcat(m, bone, m);
            PSMTXMultVec(m, &mouth, &mouth);
            mouth.y *= -1.0f;
            g_Ball.AtBat_Contact_BallPos.x = mouth.x;
            g_Ball.AtBat_Contact_BallPos.y = mouth.y;
            g_Ball.AtBat_Contact_BallPos.z = mouth.z;
        }
        if (g_Ball.AtBat_ContactResult >= 2 && p->state != 0 && p->state != 5) {
            p->state = 5;
            if (p->anim != 1) {
                fn_3_E25D0(p, 9);
            } else {
                fn_800B4BC8(p->actorObj->actor, 0);
            }
        }
        switch (p->state) {
        case 0:
            fn_3_E3914(p);
            break;
        case 1:
            fn_3_E3764(p);
            break;
        case 2:
            fn_3_E3668(p);
            break;
        case 3:
            fn_3_E3044(p);
            break;
        case 4:
            fn_3_E2F4C(p);
            break;
        case 5:
            fn_3_E2E78(p);
            break;
        }
    }
    fn_3_E266C(p);
    if (p->state != 0 && p->state < 5 && p->sleepy == 0) {
        fn_3_E2324(p);
    }
}

// .text:0x000E4554 size:0x54 mapped:0x807235E8
void fn_3_E4554(PiranhaPlant* p) {
    p->animBank = lbl_3_bss_AE18[0];
    SET_ANIM_BANK(p);
    p->animTime = p->actorObj->time;
    p->anim = 0;
}

// .text:0x000E45A8 size:0x48 mapped:0x8072363C
void fn_3_E45A8(PiranhaPlant* p) {
    CTRLSetScale(&p->ctrl.base, 0.2f, 0.2f, 0.2f);
    p->scale = 0.2f;
}

// .text:0x000E45F0 size:0x68 mapped:0x80723684
void fn_3_E45F0(PiranhaPlant* p) {
    CTRLSetRotation(&p->ctrl.base, 0.0f, lbl_3_data_18ED0[p->spot].rotY, 0.0f);
    p->rotY = lbl_3_data_18ED0[p->spot].rotY;
}

// .text:0x000E4658 size:0x108 mapped:0x807236EC
void fn_3_E4658(PiranhaPlant* p) {
    p->ctrl.base.type = 0;
    CTRLSetTranslation(&p->ctrl.base, lbl_3_data_18ED0[p->spot].pos.x, lbl_3_rodata_2B20 + lbl_3_data_18ED0[p->spot].pos.y,
                       lbl_3_data_18ED0[p->spot].pos.z);
    PSVECScale(&lbl_3_data_18ED0[p->spot].pos, lbl_3_rodata_2B24, &p->pos);
    p->pos.y = p->pos.y - lbl_3_rodata_2B20;
    fn_3_E45F0(p);
    fn_3_E45A8(p);
}

// .text:0x000E4760 size:0x170 mapped:0x807237F4
void fn_3_E4760(PiranhaPlant* p) {
    fn_3_E4658(p);
    fn_3_E4554(p);
    p->timer = 0;
    p->state = 0;
    p->active = 0;
    p->sleepy = 0;
    if (p->holdingBall != 0) {
        fn_3_65F4();
        p->holdingBall = 0;
        p->spinSpeed = 0.0f;
    }
    p->wasHit = 0;
}

// .text:0x000E48D0 size:0x168
void fn_3_E48D0(PiranhaPlant* p) {
    fn_3_E4658(p);
    fn_3_E4554(p);
    p->timer = 0;
    p->state = 0;
    p->active = 0;
    p->sleepy = 0;
    if (p->holdingBall != 0) {
        fn_3_65F4();
        p->holdingBall = 0;
        p->spinSpeed = 0.0f;
    }
}

// .text:0x000E4A38 size:0x1B0 mapped:0x80723ACC
// Bounding box of a display list's vertices (the result is not used).
void fn_3_E4A38(Mtx m, VtxBatchSet* b) {
    Vec sp14;
    Vec sp8;
    int n;
    u8* p;
    int t;
    u32 cnt;
    f32 minx, miny, minz, maxx, maxy, maxz;
    minz = miny = minx = lbl_3_rodata_2B2C;
    maxz = maxy = maxx = lbl_3_rodata_2B30;
    p = b->batches;
    for (;;) {
        cnt = ((VtxBatchHdr*)p)->count;
        if (cnt == 0) break;
        t = cnt * 3;
        if (((VtxBatchHdr*)p)->strip != 0) {
            t = cnt + 2;
        }
        n = t;
        p += sizeof(VtxBatchHdr);
        do {
            if (lbl_3_bss_AE01 == 0) {
                PSMTXMultVec(m, &((VtxBatchVtx*)p)->pos, &sp14);
            } else {
                PSVECScale(&((VtxBatchVtx*)p)->pos, 1.0f, &sp14);
            }
            p += sizeof(VtxBatchVtx);
            if (minx > sp14.x) minx = sp14.x;
            if (miny > sp14.y) miny = sp14.y;
            if (minz > sp14.z) minz = sp14.z;
            if (maxx < sp14.x) maxx = sp14.x;
            if (maxy < sp14.y) maxy = sp14.y;
            if (maxz < sp14.z) maxz = sp14.z;
            n--;
        } while (n != 0);
    }
    PSVECScale(&g_Ball.AtBat_Contact_BallPos, 1.0f, &sp8);
}

// .text:0x000E4BE8 size:0xC8 mapped:0x80723C7C
// Draw matrix of object idx. Returns its shadow model, or NULL if it isn't drawn.
static inline PiranhaPlant* plantAt(s32 idx) {
    return PLANT(idx);
}
void* fn_3_E4BE8(s32 idx, Mtx m) {
    Mtx tmp;
    PiranhaPlant* p = plantAt(idx);
    CTRLBuildMatrix(&p->ctrl.base, m);
    if (p->isDummy == 0) {
        if (p->sleepy == 0 || p->state == 0 || p->state == 5 || p->state == 4) {
            return NULL;
        }
        PSMTXCopy(p->actorObj->actor->boneArray[16]->forwardMtx, tmp);
        PSMTXConcat(m, tmp, m);
    }
    return PLANT(idx)->shadow;
}

// .text:0x000E4CB0 size:0x244 mapped:0x80723D44
// Sort the plants into draw groups and register their shadows.
void fn_3_E4CB0(s32* group, s32* obj) {
    GameControl ctrl;
    Mtx m;
    Vec t;
    PiranhaSpot* s;
    u32 off;
    PiranhaPlant* p;
    int i;
    int j;
    u16* start;
    for (i = 0; i < 10; i++) {
        u32 v;
        start = &lbl_3_common_bss_350E4.groupStart[*group];
        v = (u16)(start[-1] + lbl_3_common_bss_350E4.groupCount[*group - 1]);
        start[0] = v;
        fn_3_B8574();
        s = lbl_3_data_18ED0;
        off = v;
        for (j = 0; j < 10; j++) {
            s = &lbl_3_data_18ED0[j];
            if (i == s->group && s->state != 2) {
                if (PLANT(*obj)->hasShadow) {
                    lbl_3_common_bss_350E4.groupObjs[off] = *obj;
                    lbl_3_common_bss_350E4.groupCount[*group] += 1;
                    p = PLANT(*obj);
                    off += 1;
                    ctrl = p->ctrl;
                    CTRLGetTranslation(&ctrl.base, &t.x, &t.y, &t.z);
                    CTRLSetTranslation(&ctrl.base, t.x - 4.0, t.y, t.z - 4.0);
                    CTRLBuildMatrix(&ctrl.base, m);
                    fn_3_B8464(m, p->shadow);
                    CTRLSetTranslation(&ctrl.base, 4.0 + t.x, t.y - 10.0, 4.0 + t.z);
                    CTRLBuildMatrix(&ctrl.base, m);
                    fn_3_B8464(m, p->shadow);
                    *obj += 1;
                }
            }
        }
        if (lbl_3_common_bss_350E4.groupCount[*group] != 0) {
            fn_3_B8414(&lbl_3_common_bss_350E4.groupBounds[*group * 2], &lbl_3_common_bss_350E4.groupBounds[*group * 2 + 1]);
            *group += 1;
        }
    }
}

// .text:0x000E4EF4 size:0xD0 mapped:0x80723F88
void fn_3_E4EF4(void) {
    s32 numGroups;
    s32 numObjs;
    StadiumObjList* c = &lbl_3_common_bss_350E4;
    s32 size = (c->count << 1) + (c->count << 2) + (c->count << 2) + c->count * 0x18;
    if (c->groupBounds == NULL) {
        Vec* b = _OSAllocFromHeap(4, size);
        c->groupBounds = b;
        lbl_3_common_bss_350E4.groupCount = (u32*)(b + c->count * 2);
        lbl_3_common_bss_350E4.groupObjs = (s32*)(lbl_3_common_bss_350E4.groupCount + c->count);
        lbl_3_common_bss_350E4.groupStart = (u16*)(lbl_3_common_bss_350E4.groupObjs + c->count);
    }
    memset(c->groupBounds, 0, size);
    numGroups = 0;
    numObjs = 0;
    fn_3_E4CB0(&numGroups, &numObjs);
    lbl_3_common_bss_350E4.numGroups = numGroups;
}

// .text:0x000E4FC4 size:0x8B8 mapped:0x80724058
// NONMATCHING 87.5%: register allocation and spills (orig keeps j*0x90 and 180.0f in saved regs, frame 0x90);
// same calls, stores and control flow
#if NONMATCHING
// Set up the plants. files: the stadium's file table.
void fn_3_E4FC4(void** files) {
    StadiumObjList* list = &lbl_3_common_bss_350E4;
    PiranhaSpot* s;
    PiranhaPlant* p;
    PiranhaPlant* q;
    u32* idx;
    s32 nSpots;
    u8 nObjs;
    u8 j;
    s32 i;
    s32 n;
    u8 done;
    s32 k;
    s32 size;
    u8 sh;
    ActorObject* o;
    f32 t;

    n = 0;
    done = 0;
    list->draw = fn_3_B939C;
    list->update = fn_3_E1DB8;
    lbl_3_bss_AE10 = 0;
    idx = _OSAllocFromHeap(4, 0x38);
    lbl_3_common_bss_350E4.fileIdx = idx;
    fn_3_B9D68(lbl_3_data_19004, 14, files, idx);

    // count the spots
    s = lbl_3_data_18ED0;
    for (nSpots = 0; nSpots < 10; nSpots++) {
        if (s[nSpots].state == 2) {
            break;
        }
    }
    nObjs = (u8)nSpots + 1;
    lbl_8036E548.slots6C = ActorObjectInitTable(nObjs);
    lbl_3_common_bss_350E4.numActorObjs = nObjs;
    for (i = 0, j = 0; i < (u8)nSpots; i++, j++) {
        fn_800BDC88(lbl_8036E548.slots6C, j, j, STADIUM_FILE(files, idx[1]), NULL, STADIUM_FILE(files, idx[1] + 2));
        fn_3_B98E8(&lbl_8036E548.slots6C->objects[i]);
    }
    t = lbl_3_rodata_2A58;
    fn_800BDC88(lbl_8036E548.slots6C, j, j, STADIUM_FILE(files, idx[2]), NULL, NULL);
    fn_3_B97DC(&lbl_8036E548.slots6C->objects[j], STADIUM_FILE(files, idx[2] + 2));
    o = &lbl_8036E548.slots6C->objects[j];
    o->time = t;
    o->setTime = 1;
    fn_800B4CA0(lbl_8036E548.slots6C->objects[j].actor, lbl_8036E548.slots6C->objects[j].time);
    for (k = 0; k < 10; k++) {
        lbl_3_bss_AE18[k] = STADIUM_FILE(files, idx[4 + k]);
    }
    for (k = 0; k < nObjs; k++) {
        fn_800BD548(&lbl_8036E548.slots6C->objects[k], 4, list->lights[0], list->lights[1], list->lights[2], list->lights[3]);
    }

    lbl_3_common_bss_350E4.count = 20;
    lbl_3_common_bss_350E4.objs = _OSAllocFromHeap(0x20, 20 * sizeof(PiranhaPlant));
    memset(lbl_3_common_bss_350E4.objs, 0, 20 * sizeof(PiranhaPlant));
    lbl_3_common_bss_350E4.objsBackup = _OSAllocFromHeap(0x20, 20 * sizeof(PiranhaPlant));
    memset(lbl_3_common_bss_350E4.objsBackup, 0, 20 * sizeof(PiranhaPlant));

    p = lbl_3_common_bss_350E4.objs;
    q = p;
    if (g_d_GameSettings.GameModeSelected == 7) {
        list->draw = NULL;
    } else {
        lbl_3_bss_AE13 = 0;
        for (i = 0; i < 10; i++) {
            q = p;
            if (s->state == 2) {
                done = 1;
            }
            if (done) {
                // mark the rest of the list unused
                for (; i < 11; i++) {
                    lbl_3_data_18ED0[i].state = 2;
                }
                break;
            }
            q->spot = i;
            q->isDummy = 0;
            q->group = s->group;
            p->actorObj = &lbl_8036E548.slots6C->objects[i];
            p->shadow = STADIUM_FILE(files, idx[3]);
            p->update = fn_3_E3B88;
            p->onHit = fn_3_E2118;
            p->visible = 1;
            sh = 0;
            if (p->visible && p->shadow != NULL) {
                sh = 1;
            }
            p->hasShadow = sh;
            p->_9A = 1;
            fn_3_E4658(q);
            fn_3_E4554(q);
            s++;
            n++;
            p->bit5 = 0;
            p->_92 = 0xFF;
            p->preDraw = fn_3_E22A4;
            p->_8C = 0;
            p->_94 = 0;
            p->_96 = -1;
            p->_98 = 1;
            p++;
            q = p;
            lbl_3_bss_AE14++;
        }
    }

    // the last actor object: the dummy entry
    lbl_3_bss_AE11 = n;
    q->spot = 0;
    q->isDummy = 1;
    q->group = 0;
    p->actorObj = &lbl_8036E548.slots6C->objects[j];
    p->shadow = NULL;
    p->update = fn_3_E1FA8;
    p->onHit = NULL;
    p->visible = 1;
    p->hasShadow = 0;
    p->_9A = 0;
    p->ctrl.base.type = 0;
    p->bit5 = 0;
    p->_92 = 0xFF;
    p->preDraw = NULL;
    p->_8C = 0;
    p->_94 = 0;
    p->_96 = -1;
    p->_98 = 1;
    p++;
    lbl_3_bss_AE12++;
    // drop the unused entries from the list
    k = n + 1;
    lbl_3_common_bss_350E4.count = k;
    for (; k < lbl_3_common_bss_350E4.count; k++) {
        p->isDummy = 0;
        p->actorObj = NULL;
        p->shadow = NULL;
        p->update = NULL;
        p->onHit = NULL;
        p->visible = 0;
        p->hasShadow = 0;
        p->bit5 = 0;
        p->ctrl.base.type = 0;
        CTRLSetTranslation(&p->ctrl.base, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(&p->ctrl.base, 0.0f, 0.0f, 0.0f);
        p->_92 = 0;
        p->_8C = 0;
        p->_94 = 0;
        p->_96 = -1;
        p++;
    }

    lbl_3_common_bss_350E4.groupBounds = NULL;
    if (g_d_GameSettings.GameModeSelected != 7) {
        fn_3_E4EF4();
    }
}
#endif

