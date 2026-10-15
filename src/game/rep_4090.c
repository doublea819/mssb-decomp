#include "game/rep_4090.h"
#define REP_HEADER_FN repHeader_4090
#include "header_rep_inline.h"
#include "Dolphin/vec.h"
#include "Dolphin/rand.h"
#include "game/UnknownHomes_Game.h"
#include "game/auto_00_0016C410_text.h" // StadiumSfxMix
#include "static/GameSettings.h"
#include "main/file_800527C4.h" // fn_800527C4
#include "musyx/musyx.h"
#include "stl/math.h"
#include "Dolphin/GX.h"
#include "Dolphin/stl.h"

// Dust particles kicked up by a fielder's feet or by the ball landing (emitter type 0x1A).

s32 lbl_3_data_2A408[16] = {41, 120, 240, 40, 10, 80000, 10000, 15000, 10000, 300, 10, 60, 200, 55, 26, 0}; // dust parameters; fixed point values are /100000
extern TexArchive* lbl_803CBD0C;
extern DustFielder g_Fielders[9];
extern u16 lbl_3_data_81DC[];               // first stadium sound id, per stadium
extern StadiumSfxMix lbl_3_data_8404[][15]; // per stadium
extern StadiumSfxMix lbl_3_data_84B8[15];   // minigames (GameModeSelected 6) at stadium 4

#define FIXED(x) ((f32)(x) / 100000.0f)

// NONMATCHING 93%: our float literals are pooled into one ...rodata.0 base (the original loads each with lis/@l); register allocation differs
#pragma pool_data off // each float constant is its own .rodata symbol in the original
#if NONMATCHING
// .text:0x0016C548 size:0x330 mapped:0x807AB5DC
// Emitter update: moves, spins and fades the dust particles, frees the dead ones.
// Returns TRUE once no particle is left.
s32 fn_3_16C548(Emitter* e) {
    s32 alive = 0;
    Particle* p;
    Particle** link;
    Particle* deadTail;
    Particle* deadHead;
    s32 a;

    e->particles = fn_80031F34(e->particles, e->count);
    p = e->particles;
    link = &e->particles;
    deadTail = NULL;
    deadHead = NULL;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    do {
        if (p->life != 0) {
            fn_80033F64(p->sizeX, p->sizeY, p->u.t5.unk20);
            fn_80033CC8(p, e->tex);
            if (p->life < lbl_3_data_2A408[3]) {
                a = p->color.c.a - 255.0f / lbl_3_data_2A408[3];
                if (a < 0) {
                    a = 0;
                }
                p->color.c.a = a;
            }
            p->pos.x += p->u.t5.vel.x;
            p->pos.y -= p->u.t5.vel.y;
            p->pos.z += p->u.t5.vel.z;
            if (p->pos.y > 0.0f) {
                p->pos.y = 0.0f;
            }
            p->u.t5.vel.x -= p->u.t5.vel.x * FIXED(lbl_3_data_2A408[8]);
            p->u.t5.vel.y -= p->u.t5.vel.y * FIXED(lbl_3_data_2A408[8]);
            p->u.t5.vel.z -= p->u.t5.vel.z * FIXED(lbl_3_data_2A408[8]);
            p->u.t5.vel.y -= FIXED(lbl_3_data_2A408[9]);
            p->u.t5.unk20 += p->u.t5.unk1C * p->delay;
            if (p->u.t5.unk24 < p->u.t5.unk20 * p->delay) {
                p->u.t5.unk20 = p->u.t5.unk24 * p->delay;
                p->delay *= -1;
            }
            p->life--;
            if (p->life == 0) {
                *link = p->next;
                if (deadTail != NULL) {
                    deadTail->next = p;
                } else {
                    deadHead = p;
                }
                deadTail = p;
                p->next = NULL;
                e->count--;
            } else {
                link = &p->next;
                alive++;
            }
        }
        p = *link;
    } while (p != NULL);
    if (deadHead != NULL) {
        p = deadHead;
        do {
            p->unk4C = 0;
            p->delay = 0;
            p = p->next;
        } while (p != NULL);
        fn_80033794(deadHead);
    }
    return alive == 0;
}
#endif
#pragma pool_data reset

// NONMATCHING 99%: float literal pooling (...rodata.0) and lbl_803CBD0C addressing differ
#pragma pool_data off // each float constant is its own .rodata symbol in the original
#if NONMATCHING
// .text:0x0016C878 size:0x3B4 mapped:0x807AB90C
// Sets up n dust particles of e at pos (y negated), spread evenly around a circle.
void fn_3_16C878(Vec* pos, Emitter* e, s32 n) {
    Particle* p = e->particles;
    u32 i;
    f32 angle;
    f32 speed;
    s32 c;

    e->tex = lbl_803CBD0C;
    for (i = 0; p != NULL; i++) {
        p->delay = 0;
        p->u.t5.vel.y = FIXED(lbl_3_data_2A408[7]) + (rand() % 100 - 50) / 1000.0;
        angle = 0.017453292384743690 * ((360.0 / n) * i);
        speed = FIXED(lbl_3_data_2A408[6]) + (rand() % 100 - 50) / 1000.0;
        p->u.t5.vel.x = speed * (f32)cos(angle);
        p->u.t5.vel.z = speed * (f32)sin(angle);
        p->sizeX = p->sizeY = FIXED(lbl_3_data_2A408[5]);
        p->pos.x = pos->x;
        p->pos.y = -pos->y;
        p->pos.z = pos->z;
        p->u.t5.unk1C = lbl_3_data_2A408[10] - (rand() % 5 + 1);
        p->u.t5.unk20 = 0.0f;
        p->u.t5.unk24 = lbl_3_data_2A408[11] - (rand() % 30 + 1);
        p->delay = -((rand() % 2) * 2) + 1;
        c = (rand() % lbl_3_data_2A408[13] + 1) + lbl_3_data_2A408[12];
        p->color.c.b = c;
        p->color.c.g = c;
        p->color.c.r = c;
        p->color.c.a = 0xFF;
        p->life = lbl_3_data_2A408[1];
        p->texIndex = lbl_3_data_2A408[0];
        p->uvFrame = 0;
        p = p->next;
    }
}
#endif
#pragma pool_data reset

// NONMATCHING 83%: inlines fn_3_16C878 twice and the playDustSound copy of fn_3_16C410 like the original; float literal pooling and register allocation differ
#if NONMATCHING
// .text:0x0016CC2C size:0x8AC mapped:0x807ABCC0
// Copy of fn_3_16C410 (rep: game/auto_00_0016C410_text), inlined by the original.
static inline void playDustSound(u8 alt) {
    u32 stadium;
    s32 sound;
    GameInitVariables* gs;
    SND_VOICEID voice;
    u8 vol;
    u8 ctrl;

    if (alt) {
        if (g_d_GameSettings.StadiumID == 4) {
            sound = 5;
        } else {
            sound = 14;
        }
    } else {
        if (g_d_GameSettings.StadiumID == 4) {
            sound = 4;
        } else {
            sound = 13;
        }
    }
    gs = &g_d_GameSettings;
    stadium = gs->StadiumID;
    if (stadium == 4) {
        if (gs->GameModeSelected == 6) {
            vol = lbl_3_data_84B8[sound].vol;
        } else {
            vol = lbl_3_data_8404[stadium][sound].vol;
        }
        voice = sndFXStartEx(lbl_3_data_81DC[stadium] + sound, vol, 0x3F, 0);
        if (gs->GameModeSelected == 6) {
            ctrl = lbl_3_data_84B8[sound].ctrl5B;
        } else {
            ctrl = lbl_3_data_8404[stadium][sound].ctrl5B;
        }
        sndFXCtrl(voice, 0x5B, ctrl);
    }
}

// Spawns a puff of dust at pos: adds the particles to the running dust emitter if there is
// one, else starts a new one. who != 0 is a fielder (1-based), 0 the ball.
void fn_3_16CC2C(Vec* pos, u8 who) {
    Emitter tmp;
    Emitter* e;
    Emitter* add;
    Particle* last;
    s32 n;

    if (who) {
        if (g_d_GameSettings.StadiumID == 4) {
            n = 3;
        } else {
            n = 3;
        }
    } else if (g_d_GameSettings.StadiumID == 4) {
        n = 20;
    } else {
        n = 3;
    }
    e = fn_800339F0(NULL, 0x1A);
    if (e != NULL) {
        add = fn_800337CC(&tmp, n, 1);
        if (add == NULL) {
            return;
        }
        fn_3_16C878(pos, add, n);
        for (last = e->particles; last->next != NULL; last = last->next) {
        }
        last->next = add->particles;
        e->count += add->count;
    } else {
        e = fn_80033A24((EmitterUpdateFn)fn_3_16C548, 0x80, 0, n, 1, 0x1A);
        if (e == NULL) {
            return;
        }
        e->count = n;
        fn_3_16C878(pos, e, n);
    }
    playDustSound(who);
}
#endif

// .text:0x0016D4D8 size:0x10C mapped:0x807AC56C
#ifdef TARGET_PC
#include "main/file_80011640.h" // CharMgr lbl_8036E548: on PC its fields aren't at the GameCube offsets
#else
extern u8 lbl_8036E548[];
#endif
#ifndef TARGET_PC
extern s32 fn_8001B728(u8 a, s32 b, Vec* v);
#endif

s32 fn_3_16D4D8(s32 id_, f32 x) {
    u8 id = id_;
    f32 neg;
    Vec v = {0.0f, 0.0f, 0.0f};
#ifdef TARGET_PC
    if (lbl_8036E548.active[id]->_276 & 6) { return 1; }
#else
    u8** pp = (u8**)(lbl_8036E548 + 0x2C50);
    if (pp[id][0x276] & 6) { return 1; }
#endif
    fn_8001B728(id, 0x23, &v);
    neg = -v.y;
    v.z = 0.0f; v.y = 0.0f; v.x = 0.0f;
    fn_8001B728(id, 0x1F, &v);
    return ((x >= neg) | (x >= -v.y)) != 0;
}

// NONMATCHING 94%: the original keeps the inlined fn_3_16D4D8 result as a u8 flag (li 1/li 0, clrlwi.)
#pragma pool_data off // each float constant is its own .rodata symbol in the original
#if NONMATCHING
// .text:0x0016D5E4 size:0x22C mapped:0x807AC678
// Kicks up dust under a running fielder (who = fielder + 1) or where the ball touches down
// (who = 0), if that spot is on screen.
void fn_3_16D5E4(u8 who) {
    f32 floorY;
    Vec pos;
    DustFielder* f;

    if (g_d_GameSettings.StadiumID == 4) {
        floorY = 1.5f;
    } else {
        floorY = 0.07f;
    }
    if (who != 0) {
        f = &g_Fielders[who - 1];
        if (!fn_3_16D4D8(who - 1, floorY)) {
            return;
        }
        if (f->speed < 0.1f) {
            return;
        }
        memcpy(&pos, f, sizeof(Vec));
        pos.y = floorY;
    } else {
        f32 speed = PSVECMag(&g_Ball.physicsSubstruct.velocity);
        if (!(g_Ball.AtBat_Contact_BallPos.y <= floorY)) {
            return;
        }
        if ((g_Ball.maybeCollisionRelated & 0x7F) == 9 && !(g_Ball.pastCoordinates[0].y > floorY)) {
            return;
        }
        if (!(speed >= 0.05)) {
            return;
        }
        memcpy(&pos, &g_Ball, sizeof(Vec));
    }
    if (fn_800527C4(&pos)) {
        fn_3_16CC2C(&pos, who);
    }
}
#endif
#pragma pool_data reset

