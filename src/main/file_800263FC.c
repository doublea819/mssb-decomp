#include "main/file_800263FC.h"
#include "main/file_80008E00.h"
#include "Dolphin/os.h"
#include "main/file_80022DAC.h"
#include "main/file_80039AC0.h"
#include "stl/math.h"
#include "stl/mem.h"
#include "main/file_80011640.h"
#include "main/file_800A7C08.h"
#include "main/file_800BDEA0.h"
#include "static/Camera.h"
void fn_8003A540(u32 value); // main/file_8003A688.h (whole header clashes)

// Particle / emitter system.

int __abs(int);
int rand(void);
// TODO: these belong in their own units' headers.
typedef struct GameSettingsView {
    /* 0x00 */ u8 pad0[0x54];
    /* 0x54 */ u8 stadiumId;
    /* 0x55 */ u8 unk55;
    /* 0x56 */ u8 pad56[2];
} GameSettingsView;
extern GameSettingsView g_d_GameSettings; // GameInitVariables (UnknownHomes_Static.h clashes with this unit's prototypes)
void fn_800B0A14_removeQueue(void* unused);

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
typedef struct StadiumLightRow {
    StadiumLight light;
    u8 pad[0x2C - sizeof(StadiumLight)];
} StadiumLightRow;
extern StadiumLightRow lbl_800F7478[]; // per stadium
extern StadiumLightPos lbl_80367318;
extern ScreenFx lbl_803C5090;
extern LightFlashTask* lbl_803CBC70; // running light flash task
void* fn_800B0A5C_insertQueue(void* draw, u16 priority);
extern const Vec lbl_800E6820;
void SetFogNone(void);
u32 fn_8005268C(void);       // file_8004C5F8
camera_803c639c_s* fn_80052734(s32 index); // main/file_8004C5F8.h
extern u8 lbl_800F7840[]; // 4x4 RGB565 texture

extern f32 lbl_8017ED68[]; // cosine table, 0x800 steps per turn
extern Mtx lbl_8017FF78[2]; // [0]: billboard rotation (inverse view, no translation), [1]: inverse view
extern Mtx lbl_8017FFE0;
extern Vec lbl_80180010[4];     // billboard quad corners
extern Particle lbl_80180040[0x1400]; // particle pool
extern Emitter lbl_801F8040[0x10];    // emitter pool
extern UVCoord lbl_800F7860[];
extern TexCoordF lbl_800F78C0[4]; // quad corner texcoords
extern const Vec lbl_800E6778;    // (1, 0, 0)
extern const MtxBox lbl_800E67C0; // identity
extern const MtxBox lbl_800E682C; // identity
extern const MtxBox lbl_800E67F0; // identity
extern const MtxBox lbl_800E685C; // identity
// A particle colour as GXColor1u32 wants it (0xRRGGBBAA): see PCOLOR_GET in
// main/file_800263FC.h (colours keep the r,g,b,a byte order on PC).
#define PARTICLE_RGBA(col) PCOLOR_GET(col)

// Scratch for drawing type-4 trails.
typedef struct TrailScratch {
    /* 0x00 */ f32 width[18];
    /* 0x48 */ u32 color[18];
    /* 0x90 */ Vec pos[18];
} TrailScratch;
extern TrailScratch lbl_8017EC00;

// .bss
TrailScratch lbl_8017EC00;
f32 lbl_8017ED68[0x484];      // cosine table, filled at init
Mtx lbl_8017FF78[2];
Mtx lbl_8017FFE0 ATTRIBUTE_ALIGN(32);
Vec lbl_80180010[4];
Particle lbl_80180040[0x1400];
Emitter lbl_801F8040[0x10];
extern const Vec lbl_800E6784;    // (0, -1, 0)
extern s32 lbl_803CB800;
extern s32 lbl_803CB808; // easing iterations
extern f32 lbl_803CB80C;
extern f32 lbl_803CB804;
extern const Vec lbl_800E679C;    // (0, -1, 0)
extern const Vec lbl_800E6790;    // (0, -1, 0)
extern const Vec lbl_800E67A8[2]; // (1, 0, 0), (0, 0, 0)
extern s32 lbl_803CB7F8;          // respawn delay mask
extern f32 lbl_803CB7FC;          // respawn angle spread (0..1)
extern ParticleParams lbl_800F787C; // default spawn parameters
extern TexArchive* lbl_803CBD0C;
extern SpaniSlot lbl_80371C30[0x360];
extern SpaniObj* lbl_803CBC9C;
extern Particle* lbl_803CBC74; // free particle list
extern u8 lbl_803CBC78;        // nonzero: clear all emitters on next draw
extern s32 lbl_803CBC7C;
extern Emitter* lbl_803CBC80;  // free emitter list (linked through next)
extern EmitterHead lbl_803CBC84; // active list head
#define EMITTER_HEAD ((Emitter*)&lbl_803CBC84)

// .data
u8 lbl_800F7840[32] = { // 4x4 RGB565 texture (white)
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};
UVCoord lbl_800F7860[7] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}, {1, 0}, {1, 1}};
ParticleParams lbl_800F787C = {NULL, 6, 0, 1000000, 200, 20, {0, 10, 20, 0, 0, 20, 40, 1, 200, 255, 64}};
TexCoordF lbl_800F78C0[4] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

// .sdata
s32 lbl_803CB7F8 = 63;
f32 lbl_803CB7FC = 0.05f;
s32 lbl_803CB800 = 10;
f32 lbl_803CB804 = 10.0f;
s32 lbl_803CB808 = 1;
f32 lbl_803CB80C = 10.0f;

// .sbss (MWCC lays uninitialised small data out in reverse definition order)
EmitterHead lbl_803CBC84;
Emitter* lbl_803CBC80;
s32 lbl_803CBC7C;
u8 lbl_803CBC78;
Particle* lbl_803CBC74;
LightFlashTask* lbl_803CBC70;

static inline f32 CosIdx(s32 angle) {
    s32 i = __abs(angle) & 0x7FF;
    if (i >= 0x401) {
        i = 0x800 - i;
    }
    return lbl_8017ED68[i];
}

#define SinIdx(angle) CosIdx((angle) + 0x600)

// CosIdx with a branching abs (the original's form at some call sites).
static inline f32 CosIdxB(s32 angle) {
    s32 i = angle;
    if (i < 0) {
        i = -i;
    }
    i &= 0x7FF;
    if (i >= 0x401) {
        i = 0x800 - i;
    }
    return lbl_8017ED68[i];
}

static inline Emitter* FindEmitter(Emitter* e, u8 type) {
    if (e == NULL) {
        e = EMITTER_HEAD;
    }
    while ((e = e->next) != NULL) {
        if (e->type == type) {
            break;
        }
    }
    return e;
}

static inline void FreeParticles(Particle* list) {
    Particle* last = list;
    while (last != NULL && last->next != NULL) {
        last = last->next;
    }
    if (last != NULL) {
        last->next = lbl_803CBC74;
        lbl_803CBC74 = list;
    }
}

static inline Emitter* AllocParticles(Emitter* e, s32 n, s32 strict) {
    s32 count;
    Particle* p;
    Particle* last;
    count = 0;
    last = NULL;
    p = lbl_803CBC74;
    if (e != NULL) {
        while (p != NULL && n != 0) {
            last = p;
            p = p->next;
            count++;
            n--;
        }
        if (strict && n != 0) {
            return NULL;
        }
        e->count = count;
        if (count != 0) {
            e->particles = lbl_803CBC74;
            lbl_803CBC74 = p;
            if (last != NULL) {
                last->next = NULL;
            }
        } else {
            e->particles = NULL;
        }
    }
    return e;
}

static inline void FreeEmitter(Emitter* e) {
    if (e->update != NULL) {
        if (e->prev != NULL) {
            e->prev->next = e->next;
        }
        if (e->next != NULL) {
            e->next->prev = e->prev;
        }
        e->update = NULL;
        FreeParticles(e->particles);
        e->prev = NULL;
        e->next = lbl_803CBC80;
        lbl_803CBC80 = e;
    }
}

static inline Emitter* NewEmitter(EmitterUpdateFn update, u8 priority, s32 unk14, s32 n, s32 strict, u8 type) {
    Emitter* e = AllocParticles(lbl_803CBC80, n, strict);
    Emitter* at;
    if (e == NULL) {
        return NULL;
    }
    lbl_803CBC80 = lbl_803CBC80->next;
    e->update = update;
    e->priority = priority;
    e->type = type;
    e->active = 1;
    e->unk14 = unk14;
    e->next = NULL;
    e->prev = NULL;
    at = EMITTER_HEAD;
    while (at->next != NULL && at->next->priority < e->priority) {
        at = at->next;
    }
    e->next = at->next;
    if (e->next != NULL) {
        e->next->prev = e;
    }
    e->prev = at;
    at->next = e;
    return e;
}

static inline void LoadParticleTex(TexArchive* arc, s32 idx, GXTexWrapMode wrapS, GXTexWrapMode wrapT) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    TexImage* img;

    if (arc == NULL) {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        return;
    }
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
    img = &arc->entries[arc->entries[idx].index];
    if (img->tlut != NULL) {
        GXInitTexObjCI(&texObj, PTR32_GET(u8, img->data), img->width, img->height, img->format, wrapS, wrapT, GX_FALSE, 0);
        GXInitTlutObj(&tlutObj, PTR32_GET(void, img->tlut), img->tlutFormat, img->tlutEntries);
        GXLoadTlut(&tlutObj, GX_TLUT0);
    } else {
        GXInitTexObj(&texObj, PTR32_GET(u8, img->data), img->width, img->height, img->format, wrapS, wrapT, GX_FALSE);
    }
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, (f32)img->minLOD, (f32)img->maxLOD, img->lodBias, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP1);
}

// Bind particle p's texture from arc.
static inline void LoadParticleTexOf(Particle* p, TexArchive* arc) {
    LoadParticleTex(arc, p->texIndex, GX_CLAMP, GX_CLAMP);
}

static inline void DrawParticleQuad(Particle* p, TexArchive* arc, Vec* corner) {
    s32 i;

    LoadParticleTex(arc, p->texIndex, GX_CLAMP, GX_CLAMP);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(p->pos.x + corner[i].x, p->pos.y + corner[i].y, p->pos.z + corner[i].z);
        GXColor1u32(PCOLOR_GET(p->color));
        GXTexCoord2f32(lbl_800F7860[p->uvFrame + i].u, lbl_800F7860[p->uvFrame + i].v);
    }
}

static inline void QuadCorners(Vec* c, f32 width, f32 height) {
    s32 i;
    f32 y1;
    f32 x0;
    f32 x1;
    f32 y0;

    x1 = 0.5f * width;
    x0 = 0.5f * -width;
    y0 = 0.5f * -height;
    y1 = 0.5f * height;
    c[0].z = 0.0f;
    c[0].x = x0;
    c[0].y = y0;
    c[1].x = x1;
    c[1].y = y0;
    c[1].z = 0.0f;
    c[2].x = x1;
    c[2].y = y1;
    c[2].z = 0.0f;
    c[3].x = x0;
    c[3].y = y1;
    c[3].z = 0.0f;
    for (i = 0; i < 4; i++) {
        PSMTXMultVec(lbl_8017FF78[0], &c[i], &c[i]);
    }
}

// Sort a particle list back to front by view-space z (the body of fn_80031F34,
// which the original inlines into the draw functions).
static inline Particle* ZSortParticles(Particle* list, s32 n) {
    Vec v;
    s32 i = 0;
    s32 count = n;
    ParticleSortEntry* buf;
    ParticleSortEntry* ent;
    Particle* p;

    if (n != 0) {
        buf = _OSAllocFromHeap(0x20, n * 2 * sizeof(ParticleSortEntry));
        for (p = list, ent = buf; p != NULL; p = p->next) {
            if (i >= n) {
                OSReport("zsort particle err.\n");
                break;
            }
            ent->p = p;
            PSMTXMultVec(lbl_8017FFE0, &p->pos, &v);
            i++;
            ent->z = v.z;
            ent++;
        }
        fn_800C07BC(buf, buf + n, count, sizeof(ParticleSortEntry), fn_80032038);
        list = buf[0].p;
        ent = buf;
        while (--n != 0) {
            ent->p->next = ent[1].p;
            ent++;
        }
        ent->p->next = NULL;
        fn_800ACFB0(buf);
    }
    return list;
}

s32 fn_8002E3DC(Emitter* e);
s32 fn_80026E58(Emitter* e);
s32 fn_800263FC(Emitter* e);
s32 fn_8002E828(Emitter* e);
s32 fn_8002ECA0(Emitter* e);
s32 fn_80027968(Emitter* e);
s32 fn_8002F9FC(Emitter* e);
s32 fn_80031034(Emitter* e);
void fn_8002BC84(Emitter* e, Vec* pos, Vec* dir, ParticleParams5* prm);
void fn_80030720(Emitter* e, Vec* pos, Vec* dir, ParticleParams5* prm);
void fn_8002FDB8(Emitter* e, Vec* pos, Vec* dir, Vec* velScale, ParticleParams5* prm);
s32 fn_80029CC8(Emitter* e);

// Push a new position into a type-4 trail's history (ring of 4 in the head,
// then rings of 7 in each extension node).
static inline void TrailPush(TrailHead* head, Vec* pos) {
    TrailExt* node;

    head->histIdx = (head->histIdx + 1) % 4;
    if (head->extraNodes != 0) {
        node = (TrailExt*)head->last;
        head->extIdx = (head->extIdx + 1) % 7;
        while (node->prev != (TrailExt*)head) {
            memcpy(&node->ext[head->extIdx], &node->prev->ext[head->extIdx], sizeof(Vec));
            node = node->prev;
        }
        memcpy(&node->ext[head->extIdx], &head->hist[head->histIdx], sizeof(Vec));
    }
    memcpy(&head->hist[head->histIdx], pos, sizeof(Vec));
    if (head->histCount < head->histMax) {
        head->histCount++;
    }
}

// Cosine-smoothed fraction of rem / dur, applied lbl_803CB808 times.
static inline f32 EaseFrac(u16 rem, u16 dur, f32* whole) {
    f32 t = (f32)rem / (f32)dur;
    f32 frac = t - (f32)(s32)t;
    s32 n;

    *whole = t - frac;
    if (frac > 1.0f) {
        frac = frac - (f32)(s32)frac;
    }
    for (n = lbl_803CB808; n != 0; n--) {
        frac = (1.0f - CosIdx((s32)(1024.0f * frac))) * 0.5f;
    }
    return frac;
}

static inline void InitSmoke(Particle* p, ParticleParamsF* prm) {
    do {
        p->texIndex = prm->texIndex;
        p->life = prm->life;
        p->delay = 0;
        p->u.phys.vel.x = prm->vel.x * prm->velScale;
        p->u.phys.vel.y = prm->vel.y * prm->velScale;
        p->u.phys.vel.z = prm->vel.z * prm->velScale;
        p->u.phys.accel.x = prm->accel.x * prm->accelScale;
        p->u.phys.accel.y = prm->accel.y * prm->accelScale;
        p->u.phys.accel.z = prm->accel.z * prm->accelScale;
        p->sizeY = p->sizeX = prm->size0;
        p->color.c.r = prm->r;
        p->color.c.g = prm->g;
        p->color.c.b = prm->b;
        p->color.c.a = prm->alpha0;
        memcpy(&p->pos, &prm->pos, sizeof(Vec));
        p->dSize = (prm->size1 - prm->size0) / (f32)prm->life;
        p->dAlpha = (prm->alpha1 - prm->alpha0) / prm->life;
        p = p->next;
    } while (p != NULL);
}

static inline u32 Expand4444(u16 c) {
    // 0xRGBA nibbles -> 0xRRGGBBAA
    return ((c & 0xF) << 4) | (c & 0xF) | ((c << 4) & 0xF00) | ((c << 8) & 0xF000) | ((c << 8) & 0xF0000) |
           ((c << 12) & 0xF00000) | ((c << 12) & 0x0F000000) | ((c << 16) & 0xF0000000);
}

// .text:0x800263FC size:0x59C
// NONMATCHING 93%: the original addresses the scratch matrices/corners off the file-static bss base (lbl_8017EC00 + offset)
#if NONMATCHING
s32 fn_800263FC(Emitter* e) {
    s32 alive = 0;
    s32 a;
    Particle* p;
    Particle** link;
    Particle* lastDead = NULL;
    Particle* deadHead = NULL;

    p = ZSortParticles(e->particles, e->count);
    e->particles = p;
    link = &e->particles;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
    do {
        if (p->life != 0) {
            QuadCorners(lbl_80180010, p->sizeX, p->sizeY);
            DrawParticleQuad(p, e->tex, lbl_80180010);
            p->sizeX = p->sizeX + p->dSize;
            p->sizeY = p->sizeX;
            a = p->color.c.a + p->dAlpha;
            if (a > 0xFF) {
                a = 0xFF;
            } else if (a < 0) {
                a = 0;
            }
            p->color.c.a = a;
            p->pos.x = p->pos.x + p->u.phys.vel.x;
            p->pos.y = p->pos.y - p->u.phys.vel.y;
            p->pos.z = p->pos.z + p->u.phys.vel.z;
            p->u.phys.vel.x = p->u.phys.vel.x + p->u.phys.accel.x;
            p->u.phys.vel.y = p->u.phys.vel.y + p->u.phys.accel.y;
            p->u.phys.vel.z = p->u.phys.vel.z + p->u.phys.accel.z;
            p->life--;
        }
        if (p->life == 0) {
            *link = p->next;
            if (lastDead != NULL) {
                lastDead->next = p;
            } else {
                deadHead = p;
            }
            p->next = NULL;
            lastDead = p;
            e->count--;
        } else {
            link = &p->next;
            alive++;
        }
        p = *link;
    } while (p != NULL);
    if (deadHead != NULL) {
        for (p = deadHead; p != NULL; p = p->next) {
            p->unk4C = 0;
            p->delay = 0;
        }
        FreeParticles(deadHead);
    }
    return alive == 0;
}
#endif

// .text:0x80026998 size:0x4C0
// NONMATCHING 98.7%: register allocation in the inlined allocations
#if NONMATCHING
void fn_80026998(ParticleParamsF* prm) {
    Emitter tmp;
    Emitter* e;
    Emitter* t;
    Particle* last;

    if (prm == NULL) {
        return;
    }
    e = FindEmitter(NULL, 15);
    if (e != NULL) {
        t = AllocParticles(&tmp, prm->count, 1);
        if (t == NULL) {
            return;
        }
        t->tex = prm->tex;
        InitSmoke(t->particles, prm);
        if (e->particles != NULL) {
            for (last = e->particles; last->next != NULL; last = last->next) {
            }
            last->next = t->particles;
        } else {
            e->particles = t->particles;
        }
        e->count += t->count;
    } else {
        e = NewEmitter(fn_800263FC, 0x80, 0, prm->count, 1, 15);
        if (e != NULL) {
            e->tex = prm->tex;
            InitSmoke(e->particles, prm);
        }
    }
}
#endif

// .text:0x80026E58 size:0x4A8
// NONMATCHING 98.2%: the original keeps the identity-matrix source pointer in r31 (ours r27) for the struct copy
#if NONMATCHING
s32 fn_80026E58(Emitter* e) {
    MtxBox ident;
    Vec v;
    Vec tgt;
    AttractParticle* p = (AttractParticle*)e->particles;
    s32 done = 0;
    s32 a;

    ident = lbl_800E685C;
    if (e->u.attract.intensity > 0.0f) {
        GXLoadPosMtxImm(ident.m, GX_PNMTX0);
        GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
        LoadParticleTex(e->tex, e->u.attract.texIndex, GX_CLAMP, GX_CLAMP);
        tgt.x = e->u.attract.target->x;
        tgt.y = e->u.attract.target->y;
        tgt.z = e->u.attract.target->z;
        do {
            if (p->delay > 0) {
                p->delay -= (lbl_80366158._28 == 0);
            } else if (p->life > 0) {
                if (lbl_80366158._28 == 0) {
                    p->t = p->t + p->dt;
                    PSVECSubtract(&p->pos, &tgt, &v);
                    PSVECScale(&v, p->t, &v);
                    PSVECAdd(&tgt, &v, &p->pos);
                }
                PSMTXMultVec(lbl_8017FFE0, &p->pos, &v);
                if (p->life > p->life0 - p->fadeIn) {
                    a = (p->alphaMax * (p->life0 - p->life)) / p->fadeIn;
                } else if (p->fadeOut != 0) {
                    a = (p->alphaMax * p->life) / p->fadeOut;
                } else {
                    a = p->alphaMax;
                }
                if (a > p->alphaMax) {
                    a = p->alphaMax;
                }
                p->color.c.a = (s32)((f32)a * e->u.attract.intensity);
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                GXPosition3f32(v.x - p->size, v.y - p->size, v.z);
                GXColor1u32(PCOLOR_GET(p->color));
                GXTexCoord2f32(0.0f, 0.0f);
                GXPosition3f32(v.x - p->size, v.y + p->size, v.z);
                GXColor1u32(PCOLOR_GET(p->color));
                GXTexCoord2f32(0.0f, 1.0f);
                GXPosition3f32(v.x + p->size, v.y + p->size, v.z);
                GXColor1u32(PCOLOR_GET(p->color));
                GXTexCoord2f32(1.0f, 1.0f);
                GXPosition3f32(v.x + p->size, v.y - p->size, v.z);
                GXColor1u32(PCOLOR_GET(p->color));
                GXTexCoord2f32(1.0f, 0.0f);
                p->life -= (lbl_80366158._28 == 0);
            } else {
                done++;
            }
            p = (AttractParticle*)p->next;
        } while (p != NULL);
        GXLoadPosMtxImm(lbl_8017FFE0, GX_PNMTX0);
    }
    return done == e->count || 0.0f == e->u.attract.intensity;
}
#endif

// .text:0x80027300 size:0x374
// NONMATCHING 91%: float register allocation
#if NONMATCHING
void fn_80027300(Emitter* e, Vec* center, Vec* target, ParticleParamsAttract* prm, f32 radius) {
    AttractParticle* p;
    s32 lifeRange;
    s32 delayRange;
    f32 step;
    f32 yaw;
    f32 pitch;
    f32 tMin;
    f32 tRange;
    f32 dtMin;
    f32 dtRange;
    f32 size;

    e->tex = prm->tex;
    e->u.attract.intensity = 1.0f;
    e->u.attract.texIndex = prm->texIndex;
    e->u.attract.target = target;
    p = (AttractParticle*)e->particles;
    step = 360.0f / (f32)(s32)(f32)sqrt(prm->count);
    tMin = (f32)prm->unk20 / 100000.0f;
    tRange = (f32)prm->unk24 / 100000.0f - tMin;
    dtMin = (f32)prm->unk28 / 100000.0f;
    dtRange = (f32)prm->unk2C / 100000.0f - dtMin;
    size = (f32)prm->unkC / 100000.0f;
    lifeRange = prm->unk14 - prm->unk10;
    delayRange = prm->unk1C - prm->unk18;
    pitch = -180.0f;
    yaw = -180.0f;
    do {
        // spread the particles over a sphere around center
        fn_800332B8(NULL, &p->pos, yaw, yaw + step, pitch, pitch + step);
        yaw += step;
        if (yaw >= 180.0f) {
            pitch += step;
            yaw -= 360.0f;
            if (pitch >= 180.0f) {
                pitch -= 360.0f;
            }
        }
        PSVECScale(&p->pos, radius, &p->pos);
        PSVECAdd(center, &p->pos, &p->pos);
        p->t = tMin + (tRange * (f32)rand()) / 32767.0f;
        p->dt = dtMin + (dtRange * (f32)rand()) / 32767.0f;
        p->size = size;
        PCOLOR_SET(p->color, prm->unk3C);
        p->life0 = p->life = prm->unk10 + (lifeRange * rand()) / 32767;
        p->delay = prm->unk18 + (delayRange * rand()) / 32767;
        p->alphaMax = prm->unk30;
        p->fadeIn = prm->unk34;
        p->fadeOut = prm->unk38;
        PCOLOR_SET(p->color, prm->unk3C);
        p = (AttractParticle*)p->next;
    } while (p != NULL);
}
#endif

// .text:0x80027674 size:0x2A4
// NONMATCHING 94.2%: register allocation in the inlined allocations
#if NONMATCHING
void fn_80027674(Vec* center, Vec* target, ParticleParamsAttract* prm, u8 type, f32 radius) {
    Emitter tmp;
    Emitter* e = FindEmitter(NULL, type);
    Emitter* t;
    Particle* last;

    if (e != NULL) {
        t = AllocParticles(&tmp, prm->count, 1);
        if (t != NULL) {
            fn_80027300(t, center, target, prm, radius);
            last = e->particles;
            if (last == NULL) {
                // the original stores through a NULL pointer here
                e->particles = t->particles;
            } else {
                while (last->next != NULL) {
                    last = last->next;
                }
                last->next = t->particles;
            }
            e->count += t->count;
        }
    } else {
        e = NewEmitter(fn_80026E58, 0x80, 1, prm->count, 1, type);
        if (e != NULL) {
            fn_80027300(e, center, target, prm, radius);
        }
    }
}
#endif

// .text:0x80027918 size:0x50
void fn_80027918(u8 type, f32 v) {
    Emitter* e;
    Emitter* prev;
    Emitter* f = NULL;

    while (e = FindEmitter(f, type), prev = (f = e), e != NULL) {
#ifdef TARGET_PC
        // The word at 0x1C: for the attract emitters (the only users) it is
        // the intensity, which follows the 8-byte target pointer on PC.
        if (f->update == fn_80026E58) {
            f->u.attract.intensity = v;
            continue;
        }
#endif
        f->u.f[1] = v;
    }
}

// .text:0x80027968 size:0xBC4
// NONMATCHING 88%: register allocation; the scratch arrays are addressed off the file-static bss base (lbl_8017EC00 + offset) in the original
#if NONMATCHING
s32 fn_80027968(Emitter* e) {
    MtxBox ident;
    Vec c;
    Vec t;
    union {
        u32 rgba;
        u8 v[4];
    } col;
    s32 alive = 0;
    s32 idx = 0;
    s32 spawn = 0;
    s32 vertical;
    s32 k;
    s32 j;
    s32 n;
    s32 i;
    f32 w;
    TrailHead* h;
    TrailExt* node;
    ParticleParams5* sprm;
    Emitter* e5;

    ident = lbl_800E682C;
    h = (TrailHead*)e->particles;
    if (e->u.t4.unk48 != 0) {
        if (e->u.t4.unk4D-- == 0) {
            spawn = 1;
            e->u.t4.unk4D = e->u.t4.unk4C;
            e->u.t4.unk4F = (e->u.t4.unk4F + 1) % e->u.t4.unk4E;
        }
    }
    GXSetCullMode(GX_CULL_NONE);
    GXLoadPosMtxImm(ident.m, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
    if (e->tex != NULL) {
        LoadParticleTex(e->tex, h->unk54, GX_CLAMP, GX_CLAMP);
    }
    do {
        if (h->unk50 > 0) {
            if (lbl_80366158._28 == 0) {
                PSVECScale(&h->vel, h->unk38, &t);
                PSVECAdd(&h->vel, &t, &h->vel);
                h->vel.y = h->vel.y + h->unk4C;
            }
            // orientation of the offset on screen picks the strip direction
            PSMTXMultVec(lbl_8017FFE0, &h->vel, &c);
            c.x = c.x - lbl_8017FFE0[0][3];
            c.y = c.y - lbl_8017FFE0[1][3];
            c.z = c.z - lbl_8017FFE0[2][3];
            vertical = __fabs(c.x) < __fabs(c.y);
            w = ((((f32)h->unk52 / 100.0f) * 0.5f) * (f32)e->u.t4.unk54) / 100.0f;
            col.rgba = h->color.rgba;
            i = 0;
            for (k = h->histCount; k-- != 0;) {
                if (k < h->histCount && k >= 0 && k < 4) {
                    memcpy(&t, &h->hist[(h->histIdx - k + 4) % 4], sizeof(Vec));
                } else {
                    j = k - 4;
                    node = (TrailExt*)h->next;
                    for (n = j / 7; n != 0; n--) {
                        node = (TrailExt*)node->next;
                    }
                    j = j % 7;
                    memcpy(&t, &node->ext[(h->extIdx - j + 7) % 7], sizeof(Vec));
                }
                PSMTXMultVec(lbl_8017FFE0, &t, &lbl_8017EC00.pos[i]);
                col.v[3] = (h->color.v[3] * (h->histCount - 1 - k)) / h->histCount;
                lbl_8017EC00.color[i] = PCOLOR_GET(col);
                lbl_8017EC00.width[i] = (w * (f32)(h->histCount - 1 - k)) / (f32)h->histCount;
                i++;
            }
            PSVECAdd(&t, &h->vel, &t);
            PSMTXMultVec(lbl_8017FFE0, &t, &c);
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, (u16)(h->histCount + 1) * 2);
            if (vertical) {
                for (i = 0; i < h->histCount; i++) {
                    GXPosition3f32(lbl_8017EC00.pos[i].x - lbl_8017EC00.width[i], lbl_8017EC00.pos[i].y, lbl_8017EC00.pos[i].z);
                    GXColor1u32(lbl_8017EC00.color[i]);
                    GXTexCoord2f32(0.0f, 0.5f);
                    GXPosition3f32(lbl_8017EC00.pos[i].x + lbl_8017EC00.width[i], lbl_8017EC00.pos[i].y, lbl_8017EC00.pos[i].z);
                    GXColor1u32(lbl_8017EC00.color[i]);
                    GXTexCoord2f32(1.0f, 0.5f);
                }
                GXPosition3f32(c.x - w, c.y, c.z);
                GXColor1u32(PCOLOR_GET(h->color));
                GXTexCoord2f32(0.0f, 0.5f);
                GXPosition3f32(c.x + w, c.y, c.z);
                GXColor1u32(PCOLOR_GET(h->color));
                GXTexCoord2f32(1.0f, 0.5f);
            } else {
                for (i = 0; i < h->histCount; i++) {
                    GXPosition3f32(lbl_8017EC00.pos[i].x, lbl_8017EC00.pos[i].y - lbl_8017EC00.width[i], lbl_8017EC00.pos[i].z);
                    GXColor1u32(lbl_8017EC00.color[i]);
                    GXTexCoord2f32(0.0f, 0.5f);
                    GXPosition3f32(lbl_8017EC00.pos[i].x, lbl_8017EC00.pos[i].y + lbl_8017EC00.width[i], lbl_8017EC00.pos[i].z);
                    GXColor1u32(lbl_8017EC00.color[i]);
                    GXTexCoord2f32(1.0f, 0.5f);
                }
                GXPosition3f32(c.x, c.y - w, c.z);
                GXColor1u32(PCOLOR_GET(h->color));
                GXTexCoord2f32(0.0f, 0.5f);
                GXPosition3f32(c.x, c.y + w, c.z);
                GXColor1u32(PCOLOR_GET(h->color));
                GXTexCoord2f32(1.0f, 0.5f);
            }
            // head sprite
            w = ((f32)h->unk52 / 100.0f) * 0.5f;
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(c.x - w, c.y - w, c.z);
            GXColor1u32(PCOLOR_GET(h->color));
            GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(c.x - w, c.y + w, c.z);
            GXColor1u32(PCOLOR_GET(h->color));
            GXTexCoord2f32(0.0f, 1.0f);
            GXPosition3f32(c.x + w, c.y + w, c.z);
            GXColor1u32(PCOLOR_GET(h->color));
            GXTexCoord2f32(1.0f, 1.0f);
            GXPosition3f32(c.x + w, c.y - w, c.z);
            GXColor1u32(PCOLOR_GET(h->color));
            GXTexCoord2f32(1.0f, 0.0f);
            if (spawn && e->u.t4.unk4F == idx % e->u.t4.unk4E && lbl_80366158._28 == 0) {
                // emit sparks backwards from the tip
                PSVECScale(&h->vel, -1.0f, &c);
                col.v[3] = 0;
                col.v[0] = e->u.t4.unk55 + (e->u.t4.unk56 * h->color.v[0]) / 255;
                col.v[1] = e->u.t4.unk55 + (e->u.t4.unk56 * h->color.v[1]) / 255;
                col.v[2] = e->u.t4.unk55 + (e->u.t4.unk56 * h->color.v[2]) / 255;
                sprm = (ParticleParams5*)e->u.t4.unk48;
                sprm->unk40 = PCOLOR_GET(col);
                fn_80030D88(&t, &c, sprm, 5);
                e5 = FindEmitter(NULL, 5);
                if (e5 != NULL) {
                    e5->u.t5.unk18 = 0;
                }
            }
            if (lbl_80366158._28 == 0) {
                for (j = 0; j < e->u.t4.unk50; j++) {
                    if (t.x >= e->u.t4.boxes[j].min.x && t.y >= e->u.t4.boxes[j].min.y && t.z >= e->u.t4.boxes[j].min.z &&
                        t.x <= e->u.t4.boxes[j].max.x && t.y <= e->u.t4.boxes[j].max.y && t.z <= e->u.t4.boxes[j].max.z) {
                        break;
                    }
                }
                if (j < e->u.t4.unk50) {
                    h->unk50 = 0;
                } else {
                    TrailPush(h, &t);
                    n = h->color.v[3] - h->unk56;
                    if (n < 0) {
                        n = 0;
                    }
                    h->color.v[3] = n;
                    h->unk50--;
                }
            }
            alive++;
        }
        idx++;
        h = (TrailHead*)h->last->next;
    } while (h != NULL);
    GXLoadPosMtxImm(lbl_8017FFE0, GX_PNMTX0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    return alive == 0;
}
#endif

// .text:0x8002852C size:0xFC
void fn_8002852C(void) {
    LightFlashTask* q = (LightFlashTask*)lbl_803CC1B8;

    if (--q->timer == 0) {
        lbl_803CBC70 = NULL;
        fn_80023B90(&lbl_800F7478[g_d_GameSettings.stadiumId].light, &lbl_80367318);
        REMOVE_QUEUE_NOARG(); // argument unused
    } else {
        q->light.r = q->r;
        q->light.g = q->g;
        q->light.b = q->b;
        fn_80023B90(&q->light, &lbl_80367318);
        lbl_803C5090.flags = 9;
        lbl_803C5090.scale = 1.0f;
        lbl_803C5090.lines = 0x1C0;
        lbl_803C5090.repeat = q->repeat;
        lbl_803C5090.unk18 = 1;
        lbl_803C5090.r = q->r;
        lbl_803C5090.g = q->g;
        lbl_803C5090.b = q->b;
        lbl_803C5090.alpha = (q->alpha * q->timer) / q->duration;
    }
}

// .text:0x80028628 size:0x920
// NONMATCHING 75%: register allocation and float scheduling
#if NONMATCHING
void fn_80028628(Vec* from, Vec* to, ParticleParams4* prm, TrailShape* shape, u32* palette, struct ParticleParams5* spark, s32 flash) {
    Mtx m;
    Quaternion q;
    Vec ref;
    Vec d;
    Vec h;
    Vec axis;
    Vec v;
    Vec start;
    f32 speed;
    f32 back;
    f32 unk4C;
    f32 scale;
    s32 nodes;
    s32 n;
    Emitter* e;
    TrailHead* head;
    TrailExt* node;
    TrailShapeEntry* ent;
    LightFlashTask* task;
    s32 c;

    ref = lbl_800E6820;
    nodes = (prm->unk24 + 2) / 7 + 1;
    if (nodes < 1) {
        nodes = 1;
    }
    e = NewEmitter(fn_80027968, 0x12, 0, shape->count * nodes, 1, 4);
    if (e == NULL) {
        return;
    }
    PSVECSubtract(to, from, &d);
    speed = (f32)prm->unk8 / 100000.0f;
    back = (f32)prm->unk14 / 100000.0f;
    unk4C = (f32)prm->unk18 / 100000.0f;
    PSVECNormalize(&d, &d);
    memcpy(&h, &d, sizeof(Vec));
    h.y = 0.0f;
    if (PSVECMag(&h) != 0.0f) {
        PSVECNormalize(&h, &h);
        PSVECCrossProduct(&ref, &h, &axis);
        if (PSVECMag(&axis) == 0.0f || axis.y > 0.0f) {
            axis.x = 0.0f;
            axis.y = 1.0f;
            axis.z = 0.0f;
        } else {
            axis.x = 0.0f;
            axis.y = -1.0f;
            axis.z = 0.0f;
        }
        C_QUATRotAxisRad(&q, &axis, acos(PSVECDotProduct(&ref, &h)));
        PSMTXQuat(m, &q);
    } else {
        PSMTXRotRad(m, 'x', 1.5707964f);
    }
    head = (TrailHead*)e->particles;
    ent = shape->entries;
    scale = ((f32)prm->unkC / 100000.0f) / ((f32)prm->unk10 / 100000.0f);
    if (flash != 0) {
        if (lbl_803CBC70 != NULL) {
            task = lbl_803CBC70;
        } else {
            task = fn_800B0A5C_insertQueue(fn_8002852C, 5);
            lbl_803CBC70 = task;
            task->light.height = 200;
            task->light.yaw = 0x868;
            task->light.pitch = 0x592;
            task->pad25 = 1;
        }
        // TODO type: an RGBA word stored at the unaligned 0x1E (r, g, b, alpha)
#ifdef TARGET_PC // r, g, b, alpha bytes (PCOLOR_SET)
        if (palette != NULL) {
            port_rgba_set(&task->r, palette[ent->color]);
        } else {
            port_rgba_set(&task->r, Expand4444(ent->color));
        }
#else
        if (palette != NULL) {
            *(u32*)&task->r = palette[ent->color];
        } else {
            *(u32*)&task->r = Expand4444(ent->color);
        }
#endif
        c = task->r + prm->unk44;
        if (c > 0xFF) {
            c = 0xFF;
        }
        task->r = c;
        c = task->g + prm->unk44;
        if (c > 0xFF) {
            c = 0xFF;
        }
        task->g = c;
        c = task->b + prm->unk44;
        if (c > 0xFF) {
            c = 0xFF;
        }
        task->b = c;
        task->alpha = prm->unk3C;
        task->duration = task->timer = prm->unk40;
        task->repeat = 1;
        fn_8003A540(1);
    }
    e->u.t4.unk54 = prm->unk28;
    e->tex = prm->tex;
    e->u.t4.unk48 = spark;
    e->u.t4.unk4C = e->u.t4.unk4D = prm->unk30;
    e->u.t4.unk4E = prm->unk2C;
    e->u.t4.unk4F = 0;
    e->u.t4.unk55 = prm->unk34;
    e->u.t4.unk56 = prm->unk38;
    while (head != NULL) {
        v.x = ((f32)ent->x - (f32)((shape->sizeX >> 1) & 0x7FFF)) / (f32)shape->sizeX;
        v.y = ((f32)ent->y - (f32)((shape->sizeY >> 1) & 0x7FFF)) / (f32)shape->sizeY;
        if (shape->hasZ) {
            v.z = ((f32)ent->z - (f32)((shape->sizeZ >> 1) & 0x7FFF)) / (f32)shape->sizeZ;
        } else {
            v.z = 0.0f;
        }
        PSMTXMultVec(m, &v, &v);
        head->vel.x = -v.x * scale;
        head->vel.y = -v.y * scale;
        head->vel.z = -v.z * scale;
        start.x = from->x;
        start.y = from->y;
        start.z = from->z;
        head->unk38 = -back;
        head->unk4C = unk4C;
        head->unk52 = (s32)(100.0f * speed);
        if (palette != NULL) {
            PCOLOR_SET(head->color, palette[ent->color]);
        } else {
            PCOLOR_SET(head->color, Expand4444(ent->color));
        }
        head->color.v[3] = prm->unk1C;
        head->unk56 = prm->unk20;
        head->unk50 = (prm->unk1C + (prm->unk20 - 1)) / prm->unk20;
        memset(head->hist, 0, sizeof(head->hist));
        head->histMax = prm->unk24;
        head->histIdx = 0;
        node = (TrailExt*)head;
        head->histCount = 0;
        head->extraNodes = (prm->unk24 + 2) / 7;
        head->extIdx = 0;
        // link the extension nodes back to front
        for (n = head->extraNodes; n-- != 0;) {
            ((TrailExt*)node->next)->prev = node;
            node = (TrailExt*)node->next;
            memset(node->ext, 0, sizeof(node->ext));
        }
        head->last = (TrailHead*)node;
        TrailPush(head, &start);
        ent++;
        head->unk54 = prm->texIndex;
        head = (TrailHead*)head->last->next;
    }
    e->u.t4.unk50 = 2;
    e->u.t4.boxes[0].min.x = -92.5f;
    e->u.t4.boxes[0].min.y = -36.0f;
    e->u.t4.boxes[0].min.z = 53.0f;
    e->u.t4.boxes[0].max.x = -47.5f;
    e->u.t4.boxes[0].max.y = 0.0f;
    e->u.t4.boxes[0].max.z = 118.0f;
    e->u.t4.boxes[1].min.x = 29.0f;
    e->u.t4.boxes[1].min.y = -36.0f;
    e->u.t4.boxes[1].min.z = 66.0f;
    e->u.t4.boxes[1].max.x = 83.0f;
    e->u.t4.boxes[1].max.y = 0.0f;
    e->u.t4.boxes[1].max.z = 122.0f;
}
#endif

// .text:0x80028F48 size:0x614
// NONMATCHING 96.0%: register allocation
#if NONMATCHING
s32 fn_80028F48(Emitter* e) {
    MtxBox ident;
    Vec v;
    s32 lastTex = -1;
    s32 lastZ = -1;
    s32 lastBlend = -1;
    s32 a;
    s32 ang;
    f32 h;
    f32 cx;
    f32 sx;
    SparkParticle* p = (SparkParticle*)e->particles;
    Particle** link = &e->particles;
    Particle* lastDead = NULL;
    Particle* deadHead = NULL;

    ident = lbl_800E67F0;
    GXLoadPosMtxImm(ident.m, GX_PNMTX0);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    do {
        if (p->delay != 0) {
            p->delay -= (lbl_80366158._28 == 0);
        } else if (p->life > 0) {
            if (p->texIndex != lastTex) {
                lastTex = p->texIndex;
                LoadParticleTex(e->tex, lastTex, GX_CLAMP, GX_CLAMP);
            }
            if (p->additive != lastBlend) {
                lastBlend = p->additive;
                if (lastBlend != 0) {
                    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
                } else {
                    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                }
            }
            if (p->zTest != lastZ) {
                lastZ = p->zTest;
                if (lastZ != 0) {
                    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
                } else {
                    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
                }
            }
            if (lbl_80366158._28 == 0) {
                PSVECAdd(&p->vel, &p->accel, &p->vel);
                PSVECAdd(&p->pos, &p->vel, &p->pos);
                // bounce off the ground
                if (p->pos.y >= -p->size) {
                    p->pos.y = -p->size;
                    p->vel.y = -0.5f * p->vel.y;
                }
                p->angle = p->angle + p->spin;
                if (p->angle > 2048.0f) {
                    p->angle = p->angle - 2048.0f;
                }
                if (p->life < p->fadeStart) {
                    a = p->color.v[3] - p->fadeOut;
                    if (a < 0) {
                        a = 0;
                    }
                    p->color.v[3] = a;
                } else if (p->fadeIn != 0 && p->color.v[3] < p->alphaMax) {
                    a = p->color.v[3] + p->fadeIn;
                    if (a > p->alphaMax) {
                        a = p->alphaMax;
                    }
                    p->color.v[3] = a;
                }
            }
            PSMTXMultVec(lbl_8017FFE0, &p->pos, &v);
            ang = (s32)(2048.0f * p->angle);
            h = p->size * 0.5f;
            cx = h * CosIdx(ang);
            sx = h * SinIdx(ang);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(v.x + cx, v.y + sx, v.z);
            GXColor1u32(PCOLOR_GET(p->color));
            GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(v.x + sx, v.y - cx, v.z);
            GXColor1u32(PCOLOR_GET(p->color));
            GXTexCoord2f32(0.0f, 1.0f);
            GXPosition3f32(v.x - cx, v.y - sx, v.z);
            GXColor1u32(PCOLOR_GET(p->color));
            GXTexCoord2f32(1.0f, 1.0f);
            GXPosition3f32(v.x - sx, v.y + cx, v.z);
            GXColor1u32(PCOLOR_GET(p->color));
            GXTexCoord2f32(1.0f, 0.0f);
            p->life -= (lbl_80366158._28 == 0);
        }
        if (p->life == 0) {
            *link = p->next;
            if (lastDead != NULL) {
                lastDead->next = (Particle*)p;
            } else {
                deadHead = (Particle*)p;
            }
            p->next = NULL;
            lastDead = (Particle*)p;
            e->count--;
        } else {
            link = &p->next;
        }
        p = (SparkParticle*)*link;
    } while (p != NULL);
    if (deadHead != NULL) {
        FreeParticles(deadHead);
    }
    GXLoadPosMtxImm(lbl_8017FFE0, GX_PNMTX0);
    return e->count == 0;
}
#endif

// .text:0x8002955C size:0x294
// NONMATCHING 98.3%: register allocation in the inlined allocations
#if NONMATCHING
void fn_8002955C(Vec* pos, Vec* axis, ParticleParamsC* prm) {
    Emitter tmp;
    Emitter* e = FindEmitter(NULL, 12);
    Emitter* t;
    Particle* last;

    if (e != NULL) {
        t = AllocParticles(&tmp, prm->unk8, 1);
        if (t != NULL) {
            fn_800297F0(t, pos, axis, prm);
            for (last = e->particles; last->next != NULL; last = last->next) {
            }
            last->next = t->particles;
            e->count += t->count;
        }
    } else {
        e = NewEmitter(fn_80028F48, 0x80, 0, prm->unk8, 1, 12);
        if (e != NULL) {
            fn_800297F0(e, pos, axis, prm);
        }
    }
}
#endif

// .text:0x800297F0 size:0x4D8
// NONMATCHING 94%: float register allocation of yaw/pitch and scheduling of the conversions (declaration and conversion order tuned by search)
#if NONMATCHING
void fn_800297F0(Emitter* e, Vec* pos, Vec* axis, ParticleParamsC* prm) {
    SparkParticle* p;
    s32 lifeRange;
    f32 spinMin;
    f32 spinRange;
    f32 speedMin;
    f32 speedRange;
    f32 sizeMin;
    f32 sizeRange;
    f32 pitch;
    f32 yaw;
    f32 gravity;
    f32 yawRange;
    f32 pitchRange;
    f32 pitchEnd;
    s32 fadeStart;
    u8 alpha;

    e->tex = prm->tex;
    speedMin = (f32)prm->unk14 / 100000.0f;
    speedRange = (f32)prm->unk18 / 100000.0f - speedMin;
    sizeMin = (f32)prm->unk24 / 100000.0f;
    sizeRange = (f32)prm->unk28 / 100000.0f - sizeMin;
    spinMin = ((f32)prm->unk1C / 100000.0f) / 360.0f;
    lifeRange = prm->unk10 - prm->unkC;
    spinRange = ((f32)prm->unk20 / 100000.0f) / 360.0f - spinMin;
    gravity = (f32)prm->unk2C / 100000.0f;
    p = (SparkParticle*)e->particles;
    if (axis != NULL) {
        yaw = (f32)prm->unk48 / 100000.0f;
        yawRange = (f32)(prm->unk4C - prm->unk48) / 100000.0f;
        pitch = (f32)prm->unk40 / 100000.0f;
        pitchRange = (f32)(prm->unk44 - prm->unk40) / 100000.0f;
    } else {
        // spread evenly over the sphere
        pitch = -180.0f;
        yaw = -180.0f;
        yawRange = pitchRange = 360.0f / (f32)(s32)(f32)sqrt(prm->unk8);
    }
    alpha = prm->unk30;
    if (prm->unk38 != 0) {
        fadeStart = (alpha + (prm->unk38 - 1)) / prm->unk38;
    } else {
        fadeStart = 0;
    }
    do {
        p->texIndex = prm->texIndex;
        p->delay = 0;
        p->life = prm->unkC + (lifeRange * rand()) / 32767;
        pitchEnd = pitch + pitchRange;
        p->size = sizeMin + (sizeRange * (f32)rand()) / 32767.0f;
        p->pos.x = pos->x;
        p->pos.y = pos->y - p->size * 0.5f;
        p->pos.z = pos->z;
        fn_800332B8(axis, &p->vel, yaw, yaw + yawRange, pitch, pitchEnd);
        if (axis == NULL) {
            yaw += yawRange;
            if (yaw >= 180.0f) {
                pitch += pitchRange;
                yaw -= 360.0f;
                if (pitch >= 180.0f) {
                    pitch -= 360.0f;
                }
            }
        } else {
            pitch = -pitchEnd;
        }
        PSVECScale(&p->vel, speedMin + (speedRange * (f32)rand()) / 32767.0f, &p->vel);
        p->accel.x = 0.0f;
        p->accel.z = 0.0f;
        p->accel.y = gravity;
        p->spin = p->angle = spinMin + (spinRange * (f32)rand()) / 32767.0f;
        PCOLOR_SET(p->color, prm->unk30);
        p->alphaMax = alpha;
        p->fadeIn = prm->unk34;
        p->fadeOut = prm->unk38;
        p->fadeStart = fadeStart;
        p->additive = prm->unk3C;
        p->zTest = prm->unk50;
        p = (SparkParticle*)p->next;
    } while (p != NULL);
}
#endif

// .text:0x80029CC8 size:0x504
// NONMATCHING 93%: register allocation and stack layout; the original copies the identity matrix word by word
#if NONMATCHING
s32 fn_80029CC8(Emitter* e) {
    MtxBox ident;
    Vec c;
    Vec q;
    Vec t;
    Vec perp;
    Vec v0;
    Vec v1;
    Vec v2;
    Vec v3;
    f32 sx;
    f32 sy;
    s32 count;
    Particle* p;

    ident = lbl_800E67C0;
    count = e->count;
    GXLoadPosMtxImm(ident.m, GX_PNMTX0);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    PSMTXMultVec(lbl_8017FFE0, &e->u.t9.pos, &c);
    p = e->particles;
    LoadParticleTex(e->tex, p->texIndex, GX_CLAMP, GX_CLAMP);
    for (; p != NULL; p = p->next) {
        if (p->delay != 0) {
            p->delay--;
        } else if (p->life != 0) {
            PSVECAdd(&p->u.tB.dir, &p->u.tB.vel, &p->u.tB.dir);
            PSVECAdd(&p->pos, &p->u.tB.dir, &p->pos);
            p->color.c.a = (p->colorStep.tB.alpha0 * p->life) / p->colorStep.tB.maxLife;
            if (c.z <= -1.0f) {
                PSMTXMultVec(lbl_8017FFE0, &p->pos, &q);
                t.x = (c.x * q.z) / c.z;
                t.y = (c.y * q.z) / c.z;
                t.z = q.z;
                PSVECSubtract(&q, &t, &t);
                t.z = 0.0f;
                perp.x = -t.y;
                perp.y = t.x;
                perp.z = 0.0f;
                sx = p->u.tB.sizeX + (p->u.tB.sizeXDelta * (f32)(p->colorStep.tB.maxLife - p->life)) / (f32)p->colorStep.tB.maxLife;
                sy = p->u.tB.sizeY + (p->u.tB.sizeYDelta * (f32)(p->colorStep.tB.maxLife - p->life)) / (f32)p->colorStep.tB.maxLife;
                PSVECScale(&t, sy, &t);
                PSVECScale(&perp, sx * 0.5f, &perp);
                PSVECAdd(&q, &perp, &v0);
                PSVECSubtract(&q, &perp, &v1);
                PSVECSubtract(&v1, &t, &v2);
                PSVECSubtract(&v0, &t, &v3);
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                GXPosition3f32(v0.x, v0.y, v0.z);
                GXColor1u32(PCOLOR_GET(p->color));
                GXTexCoord2f32(0.0f, 1.0f);
                GXPosition3f32(v1.x, v1.y, v1.z);
                GXColor1u32(PCOLOR_GET(p->color));
                GXTexCoord2f32(0.0f, 0.0f);
                GXPosition3f32(v2.x, v2.y, v2.z);
                GXColor1u32(PCOLOR_GET(p->color));
                GXTexCoord2f32(1.0f, 0.0f);
                GXPosition3f32(v3.x, v3.y, v3.z);
                GXColor1u32(PCOLOR_GET(p->color));
                GXTexCoord2f32(1.0f, 1.0f);
            }
            p->life--;
        } else {
            count--;
        }
    }
    GXLoadPosMtxImm(lbl_8017FFE0, GX_PNMTX0);
    return count == 0;
}
#endif

// .text:0x8002A1CC size:0x690
void fn_8002A1CC(Vec* pos, ParticleParamsB* prm) {
    f32 step;
    f32 yaw;
    Emitter* e;
    Particle* p;
    f32 speedMin;
    f32 speedRange;
    f32 velMin;
    f32 velRange;
    f32 sizeXMin;
    f32 sizeXRange;
    f32 endXMin;
    f32 endXRange;
    f32 sizeYMin;
    f32 sizeYRange;
    f32 endYMin;
    f32 endYRange;
    s32 instant;
    s32 lifeRange;
    f32 pitch;

    e = NewEmitter(fn_80029CC8, 0x80, 0, prm->count, 1, 11);
    if (e == NULL) {
        return;
    }
    e->tex = prm->tex;
    memcpy(&e->u.t9.pos, pos, sizeof(Vec));
    speedMin = (f32)prm->speedMin / 100000.0f;
    speedRange = (f32)prm->speedMax / 100000.0f - speedMin;
    velMin = (f32)prm->velMin / 100000.0f;
    velRange = (f32)prm->velMax / 100000.0f - velMin;
    sizeXMin = (f32)prm->sizeXMin / 100000.0f;
    sizeXRange = (f32)prm->sizeXMax / 100000.0f - sizeXMin;
    endXMin = (f32)prm->endXMin / 100000.0f;
    endXRange = (f32)prm->endXMax / 100000.0f - endXMin;
    sizeYMin = (f32)prm->sizeYMin / 100000.0f;
    sizeYRange = (f32)prm->sizeYMax / 100000.0f - sizeYMin;
    endYMin = (f32)prm->endYMin / 100000.0f;
    endYRange = (f32)prm->endYMax / 100000.0f - endYMin;
    instant = prm->instant;
    lifeRange = prm->lifeMax - prm->lifeMin;
    step = 360.0f / (f32)(s32)(f32)sqrt(prm->instant);
    pitch = -180.0f;
    yaw = -180.0f;
    p = e->particles;
    do {
        p->texIndex = prm->texIndex;
        if (instant-- != 0) {
            p->delay = 0;
        } else {
            p->delay = (prm->delayMax * rand()) / 32767;
        }
        p->colorStep.tB.maxLife = p->life = prm->lifeMin + (lifeRange * rand()) / 32767;
        memcpy(&p->pos, pos, sizeof(Vec));
        fn_800332B8(NULL, &p->u.tB.dir, yaw, yaw + step, pitch, pitch + step);
        yaw += step;
        if (yaw >= 180.0f) {
            pitch += step;
            yaw -= 360.0f;
            if (pitch >= 180.0f) {
                pitch -= 360.0f;
            }
        }
        PSVECScale(&p->u.tB.dir, velMin + (velRange * (f32)rand()) / 32767.0f, &p->u.tB.vel);
        PSVECScale(&p->u.tB.dir, speedMin + (speedRange * (f32)rand()) / 32767.0f, &p->u.tB.dir);
        p->u.tB.sizeX = sizeXMin + (sizeXRange * (f32)rand()) / 32767.0f;
        p->u.tB.sizeY = sizeYMin + (sizeYRange * (f32)rand()) / 32767.0f;
        p->u.tB.sizeXDelta = (endXMin + (endXRange * (f32)rand()) / 32767.0f) - p->u.tB.sizeX;
        p->u.tB.sizeYDelta = (endYMin + (endYRange * (f32)rand()) / 32767.0f) - p->u.tB.sizeY;
        PCOLOR_SET(p->color, prm->color);
        p->colorStep.tB.alpha0 = p->color.c.a;
        p = p->next;
    } while (p != NULL);
}

// .text:0x8002A85C size:0x40C
// NONMATCHING 99.5%: float register allocation of the inlined corner setup
#if NONMATCHING
u8 fn_8002A85C(Emitter* e, Particle* p) {
    s32 a;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
    QuadCorners(lbl_80180010, p->sizeX, p->sizeY);
    DrawParticleQuad(p, e->tex, lbl_80180010);
    a = p->color.c.a;
    if (p->u.tEsub.life0 - p->life < p->u.tEsub.phase1) {
        p->sizeX = p->sizeX + p->u.tEsub.dSizeX1;
        p->sizeY = p->sizeY + p->u.tEsub.dSizeY1;
        a += p->u.tEsub.dAlpha1;
        p->pos.y = p->pos.y - p->u.tEsub.dSizeY1 * 0.5f;
    } else {
        p->sizeX = p->sizeX + p->u.tEsub.dSizeX2;
        p->sizeY = p->sizeY + p->u.tEsub.dSizeY2;
        a += p->u.tEsub.dAlpha2;
        p->pos.y = p->pos.y - p->u.tEsub.dSizeY2 * 0.5f;
    }
    if (a < 0) {
        a = 0;
    }
    if (a > 0xFF) {
        a = 0xFF;
    }
    p->color.c.a = a;
    p->life--;
    return p->life == 0;
}
#endif

// .text:0x8002AC68 size:0x3AC
// NONMATCHING 99.4%: float register allocation of the corner setup
#if NONMATCHING
u8 fn_8002AC68(Emitter* e, Particle* p) {
    Vec c[4];
    s32 a;
    s32 i;
    f32 x0;
    f32 x1;
    f32 z0;
    f32 z1;

    // flat quad on the ground (XZ plane)
    x0 = 0.5f * -p->sizeX;
    x1 = 0.5f * p->sizeX;
    z0 = 0.5f * -p->sizeY;
    z1 = 0.5f * p->sizeY;
    c[3].y = 0.0f;
    c[0].x = x0;
    c[0].z = z1;
    c[1].x = x1;
    c[1].z = z1;
    c[2].x = x1;
    c[2].z = z0;
    c[3].x = x0;
    c[3].z = z0;
    c[2].y = 0.0f;
    c[1].y = 0.0f;
    c[0].y = 0.0f;
    LoadParticleTexOf(p, e->tex);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(p->pos.x + c[i].x, p->pos.y + c[i].y, p->pos.z + c[i].z);
        GXColor1u32(PCOLOR_GET(p->color));
        GXTexCoord2f32(lbl_800F7860[p->uvFrame + i].u, lbl_800F7860[p->uvFrame + i].v);
    }
    a = p->color.c.a;
    if (p->u.tE.life0 - p->life < p->u.tE.phase1) {
        p->sizeX = p->sizeX + p->u.tE.dSize1;
        p->sizeY = p->sizeX;
        a += p->u.tE.dAlpha1;
    } else {
        p->sizeX = p->sizeX + p->u.tE.dSize2;
        p->sizeY = p->sizeX;
        a += p->u.tE.dAlpha2;
    }
    if (a < 0) {
        a = 0;
    }
    if (a > 0xFF) {
        a = 0xFF;
    }
    p->color.c.a = a;
    p->life--;
    return p->life == 0;
}
#endif

// .text:0x8002B014 size:0x3EC
// NONMATCHING 94.6%: register allocation in the inlined z-sorts (the original keeps the count copy in its own saved reg)
#if NONMATCHING
s32 fn_8002B014(Emitter* e) {
    s32 alive = 0;
    Particle* p;
    Particle** link;
    Particle* lastDead;
    Particle* deadHead;

    if (e->count != 0) {
        p = ZSortParticles(e->particles, e->count);
        e->particles = p;
        link = &e->particles;
        lastDead = NULL;
        deadHead = NULL;
        // note: a particle with life 0 here would never be advanced past (as in the original)
        do {
            if (p->life != 0) {
                if (p->delay <= 0) {
                    if (fn_8002AC68(e, p)) {
                        *link = p->next;
                        if (lastDead != NULL) {
                            lastDead->next = p;
                        } else {
                            deadHead = p;
                        }
                        lastDead = p;
                        p->next = NULL;
                        e->count--;
                    } else {
                        link = &p->next;
                        alive++;
                    }
                } else {
                    link = &p->next;
                    p->delay--;
                    alive++;
                }
            }
            p = *link;
        } while (p != NULL);
        if (deadHead != NULL) {
            for (p = deadHead; p != NULL; p = p->next) {
                p->unk4C = 0;
                p->delay = 0;
            }
            FreeParticles(deadHead);
        }
    }
    if (e->u.tE.subCount != 0) {
        p = ZSortParticles(e->u.tE.sub, e->u.tE.subCount);
        e->u.tE.sub = p;
        link = &e->u.tE.sub;
        lastDead = NULL;
        deadHead = NULL;
        do {
            if (p->life != 0) {
                if (p->delay <= 0) {
                    if (fn_8002A85C(e, p)) {
                        *link = p->next;
                        if (lastDead != NULL) {
                            lastDead->next = p;
                        } else {
                            deadHead = p;
                        }
                        lastDead = p;
                        p->next = NULL;
                        e->u.tE.subCount--;
                    } else {
                        link = &p->next;
                        alive++;
                    }
                } else {
                    link = &p->next;
                    p->delay--;
                    alive++;
                }
            }
            p = *link;
        } while (p != NULL);
        if (deadHead != NULL) {
            for (p = deadHead; p != NULL; p = p->next) {
                p->unk4C = 0;
                p->delay = 0;
            }
            FreeParticles(deadHead);
        }
    }
    return alive == 0;
}
#endif

// .text:0x8002B400 size:0x3F8
// NONMATCHING 95.8%: register allocation (the delay/uvFrame zero and p in the sub loop)
#if NONMATCHING
void fn_8002B400(Emitter* e, ParticleParamsE* prm, Vec* pos) {
    Particle* p = e->particles;
    s32 delay;
    s32 i = 0;
    f32 ang;

    do {
        delay = 0;
        p->uvFrame = 0;
        p->life = prm->life;
        p->texIndex = prm->texIndex;
        p->sizeX = p->sizeY = prm->size[0];
        p->color.c.r = p->color.c.g = p->color.c.b = 0xFF;
        p->color.c.a = prm->alpha[0];
        p->unk4C = 2;
        p->pos.x = pos->x;
        p->pos.y = -0.1 + -pos->y;
        p->pos.z = pos->z;
        p->u.tE.phase1 = prm->phase1;
        p->u.tE.life0 = prm->life;
        p->u.tE.dSize1 = (prm->size[1] - prm->size[0]) / (f32)p->u.tE.phase1;
        p->u.tE.dAlpha1 = (prm->alpha[1] - prm->alpha[0]) / p->u.tE.phase1;
        p->u.tE.dSize2 = (prm->size[2] - prm->size[1]) / (f32)(p->u.tE.life0 - p->u.tE.phase1);
        p->u.tE.dAlpha2 = (prm->alpha[2] - prm->alpha[1]) / (p->u.tE.life0 - p->u.tE.phase1);
        p->delay = delay;
        p = p->next;
    } while (p != NULL);
    for (p = e->u.tE.sub; p != NULL; p = p->next) {
        p->uvFrame = 0;
        p->life = prm->subLife;
        p->texIndex = prm->subTexIndex;
        p->sizeX = prm->subSizeX[0];
        p->sizeY = prm->subSizeY[0];
        p->color.c.r = p->color.c.g = p->color.c.b = 0xFF;
        p->color.c.a = prm->subAlpha[0];
        p->unk4C = 1;
        ang = 0.017453292f * prm->angle0 + (f32)i * (0.017453292f * (prm->angleSpan / (f32)prm->subCount));
        p->pos.x = prm->radius * (f32)cos(ang) + pos->x;
        p->pos.y = -0.1 + (-pos->y - p->sizeY * 0.5f);
        ang = 0.017453292f * prm->angle0 + (f32)i * (0.017453292f * (prm->angleSpan / (f32)prm->subCount));
        i++;
        p->pos.z = prm->radius * (f32)sin(ang) + pos->z;
        p->u.tEsub.phase1 = prm->subPhase1;
        p->u.tEsub.life0 = prm->subLife;
        p->u.tEsub.dSizeY1 = (prm->subSizeY[1] - prm->subSizeY[0]) / (f32)p->u.tEsub.phase1;
        p->u.tEsub.dSizeX1 = (prm->subSizeX[1] - prm->subSizeX[0]) / (f32)p->u.tEsub.phase1;
        p->u.tEsub.dAlpha1 = (prm->subAlpha[1] - prm->subAlpha[0]) / p->u.tEsub.phase1;
        p->u.tEsub.dSizeY2 = (prm->subSizeY[2] - prm->subSizeY[1]) / (f32)(p->u.tEsub.life0 - p->u.tEsub.phase1);
        p->u.tEsub.dSizeX2 = (prm->subSizeX[2] - prm->subSizeX[1]) / (f32)(p->u.tEsub.life0 - p->u.tEsub.phase1);
        p->u.tEsub.dAlpha2 = (prm->subAlpha[2] - prm->subAlpha[1]) / (p->u.tEsub.life0 - p->u.tEsub.phase1);
        p->delay = delay;
        delay += 2;
    }
}
#endif

// .text:0x8002B7F8 size:0x48C
// NONMATCHING 96.3%: register allocation in the inlined allocations
#if NONMATCHING
void fn_8002B7F8(Vec* pos, ParticleParamsE* prm, u8 withSub) {
    Emitter tmp;
    Emitter tmp2;
    Emitter* e;
    Emitter* t;
    Emitter* t2;
    Particle* last;

    if (g_d_GameSettings.unk55 != 0) {
        return;
    }
    e = FindEmitter(NULL, 14);
    if (e != NULL) {
        t = AllocParticles(&tmp, prm->count, 1);
        if (t == NULL) {
            return;
        }
        if (withSub && prm->subCount != 0) {
            t2 = AllocParticles(&tmp2, prm->subCount, 1);
            if (t2 == NULL) {
                t->u.tE.sub = NULL;
                t->u.tE.subCount = 0;
            } else {
                t->u.tE.sub = t2->particles;
                t->u.tE.subCount = t2->count;
            }
        } else {
            t->u.tE.sub = NULL;
            t->u.tE.subCount = 0;
        }
        fn_8002B400(t, prm, pos);
        for (last = e->particles; last->next != NULL; last = last->next) {
        }
        last->next = t->particles;
        e->count += prm->count;
        if (e->u.tE.sub != NULL) {
            for (last = e->u.tE.sub; last->next != NULL; last = last->next) {
            }
            last->next = t->u.tE.sub;
        } else {
            e->u.tE.sub = t->u.tE.sub;
        }
        e->u.tE.subCount += t->u.tE.subCount;
    } else {
        e = NewEmitter(fn_8002B014, 0x80, 0, prm->count, 1, 14);
        if (e == NULL) {
            return;
        }
        e->tex = prm->tex;
        if (withSub) {
            t = AllocParticles(&tmp, prm->subCount, 1);
            if (t == NULL) {
                return; // the original leaves the new emitter uninitialized here
            }
            e->u.tE.sub = t->particles;
            e->u.tE.subCount = prm->subCount;
        } else {
            e->u.tE.sub = NULL;
            e->u.tE.subCount = 0;
        }
        fn_8002B400(e, prm, pos);
    }
}
#endif

// .text:0x8002BC84 size:0x64C
// NONMATCHING 78%: float register allocation/scheduling
#if NONMATCHING
void fn_8002BC84(Emitter* e, Vec* pos, Vec* dir, ParticleParams5* prm) {
    Mtx m;
    Vec ref;
    Vec v;
    f32 angle;
    f32 sizeScale;
    f32 velMin;
    f32 velRange;
    f32 a;
    f32 sn;
    f32 cs;
    Particle* p = e->particles;

    ref = lbl_800E67A8[0];
    v = lbl_800E67A8[1];
    e->tex = prm->tex;
    velMin = (f32)prm->unk34 / 100000.0f;
    velRange = (f32)(prm->unk38 - prm->unk34) / 100000.0f;
    PSVECNormalize(dir, &v);
    angle = acos(PSVECDotProduct(&ref, &v));
    PSVECCrossProduct(&ref, &v, &v);
    PSMTXRotAxisRad(m, &v, angle);
    angle = ((360.0f * (f32)rand()) / (f32)prm->count) / 32767.0f;
    sizeScale = (f32)prm->unkC / 100000.0f;
    do {
        if (prm->count == 1) {
            memcpy(&p->pos, pos, sizeof(Vec));
            memcpy(&p->u.t5.vel, dir, sizeof(Vec));
            PSVECScale(&p->u.t5.vel, ((f32)prm->unk10 / 100000.0f) * (0.95f + (0.1f * (f32)rand()) / 32767.0f), &p->u.t5.vel);
        } else {
            // spread the particles around a ring perpendicular to dir
            v.x = 0.0f;
            v.y = cos(angle);
            v.z = sin(angle);
            angle += 360.0f / (f32)prm->count;
            PSMTXMultVec(m, &v, &v);
            PSVECScale(&v, (f32)prm->unk3C / 100000.0f, &v);
            PSVECAdd(pos, &v, &p->pos);
            PSVECScale(&v, velMin + (velRange * (f32)rand()) / 32767.0f, &p->u.t5.vel);
            PSVECScale(dir, ((f32)prm->unk10 / 100000.0f) * (0.95f + (0.1f * (f32)rand()) / 32767.0f), &v);
            PSVECAdd(&p->u.t5.vel, &v, &p->u.t5.vel);
        }
        a = (((3.1415927f * ((f32)prm->unk2C / 100000.0f)) / 180.0f) * (f32)(0x3FFF - rand())) / 32767.0f;
        sn = sin(a);
        cs = cos(a);
        p->sizeX = sizeScale * (sn - cs);
        p->sizeY = sizeScale * (cs + sn);
        p->u.t5.unk1C = 0.01f * (f32)(8 - rand() % 16) + (f32)prm->unkC / 100000.0f;
        p->u.t5.unk20 = (f32)prm->unk20 / 100000.0f;
        p->u.t5.unk24 = (f32)prm->unk24 / 100000.0f;
        p->u.t5.unk2C = prm->unk18 - prm->unk1C;
        p->u.t5.unk28 = ((f32)prm->unk14 / 100000.0f) *
                        (0.02 * lbl_803CB80C * (rand() % 256) * 0.00390625 + (1.0f - 0.01f * lbl_803CB80C));
        PCOLOR_SET(p->color, prm->unk30);
        p->u.t5.unk30 = prm->unk28;
        p->u.t5.unk34 = 0.0f;
        p->colorStep.v[0] = 0;
        p->life = p->delay = prm->unk18;
        p->unk4C = 1;
        p->uvFrame = 0;
        p->texIndex = prm->texIndex;
        p->uvOrder = 0;
        p = p->next;
    } while (p != NULL);
}
#endif

// .text:0x8002C2D0 size:0x29C
// NONMATCHING 98.4%: register allocation in the inlined allocations
#if NONMATCHING
void fn_8002C2D0(Vec* pos, Vec* dir, ParticleParams5* prm) {
    Emitter tmp;
    Emitter* e = FindEmitter(NULL, 5);
    Emitter* t;
    Particle* last;

    if (e != NULL) {
        t = AllocParticles(&tmp, prm->count, 1);
        if (t != NULL) {
            fn_8002BC84(t, pos, dir, prm);
            for (last = e->particles; last->next != NULL; last = last->next) {
            }
            last->next = t->particles;
            e->count += t->count;
        }
    } else {
        e = NewEmitter(fn_80031034, 0x11, 0, prm->count, 1, 5);
        if (e != NULL) {
            e->u.t5.unk18 = 0;
            fn_8002BC84(e, pos, dir, prm);
        }
    }
}
#endif

// .text:0x8002C56C size:0x864
// NONMATCHING 94%: register allocation and float scheduling
#if NONMATCHING
s32 fn_8002C56C(Emitter* e) {
    Mtx ident;
    Mtx rot;
    Vec a;
    Vec off;
    Vec pos;
    f32 whole;
    f32 frac;
    s32 alive = 0;
    u16 total;
    u16 elapsed;
    u16 ang;
    StreakParticle* p = (StreakParticle*)e->particles;

    LoadParticleTex(e->tex, e->u.t10.texIndex, GX_CLAMP, GX_CLAMP);
    PSMTXIdentity(ident);
    GXLoadPosMtxImm(ident, GX_PNMTX0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    if (lbl_80366158._28 == 0 && e->u.t10.unk40 != 0) {
        e->u.t10.unk40--;
    }
    do {
        if (p->rem[2] != 0) {
            alive++;
            total = p->dur[0] + p->dur[1] + p->dur[2];
            elapsed = total - (p->rem[0] + p->rem[1] + p->rem[2]);
            if (p->delay != 0) {
                p->delay -= (lbl_80366158._28 == 0);
            } else {
                if (p->rem[0] != 0) {
                    // phase 1: fly out
                    frac = EaseFrac(p->rem[0], p->dur[0], &whole);
                    frac = 1.0f - (whole + frac);
                    PSVECAdd(&e->u.t10.dir, &p->offset, &a);
                    PSVECScale(&a, p->reach * frac, &pos);
                    PSVECScale(&p->dir, p->lenA * frac, &off);
                    p->rem[0] -= (lbl_80366158._28 == 0);
                } else if (p->rem[1] != 0) {
                    // phase 2: travel to the end point
                    frac = EaseFrac(p->rem[1], p->dur[1], &whole);
                    frac = whole + frac;
                    PSVECAdd(&e->u.t10.dir, &p->offset, &a);
                    PSVECScale(&a, (1.0 - frac) + p->reach * frac, &pos);
                    PSVECScale(&p->dir, p->lenA * frac, &off);
                    p->rem[1] -= (lbl_80366158._28 == 0);
                } else {
                    // phase 3: at the end point
                    frac = EaseFrac(p->rem[2], p->dur[2], &whole);
                    PSVECAdd(&e->u.t10.dir, &p->offset, &a);
                    memcpy(&pos, &a, sizeof(Vec));
                    PSVECScale(&p->dir, p->lenB * (1.0f - (whole + frac)), &off);
                    p->rem[2] -= (lbl_80366158._28 == 0);
                }
                if ((u16)(total - elapsed) < p->fade) {
                    p->color.c.a = ((u16)(total - elapsed) * 0xFF) / p->fade;
                }
                ang = (s32)(p->spin * (f32)elapsed);
                if (ang != 0) {
                    PSMTXRotAxisRad(rot, &a, 0.017453292f * (f32)ang);
                    PSMTXMultVec(rot, &off, &off);
                }
                PSVECAdd(&e->u.t10.start, &pos, &pos);
                PSVECAdd(&pos, &off, &pos);
                PSMTXMultVec(lbl_8017FFE0, &pos, &pos);
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                GXPosition3f32(pos.x - p->sizeX, pos.y - p->sizeY, pos.z);
                GXColor1u32(PCOLOR_GET(p->color));
                GXTexCoord2f32(lbl_800F78C0[p->uvOrder & 0xF].s, lbl_800F78C0[p->uvOrder & 0xF].t);
                GXPosition3f32(pos.x + p->sizeY, pos.y - p->sizeX, pos.z);
                GXColor1u32(PCOLOR_GET(p->color));
                GXTexCoord2f32(lbl_800F78C0[(p->uvOrder >> 4) & 0xF].s, lbl_800F78C0[(p->uvOrder >> 4) & 0xF].t);
                GXPosition3f32(pos.x + p->sizeX, pos.y + p->sizeY, pos.z);
                GXColor1u32(PCOLOR_GET(p->color));
                GXTexCoord2f32(lbl_800F78C0[(p->uvOrder >> 8) & 0xF].s, lbl_800F78C0[(p->uvOrder >> 8) & 0xF].t);
                GXPosition3f32(pos.x - p->sizeY, pos.y + p->sizeX, pos.z);
                GXColor1u32(PCOLOR_GET(p->color));
                GXTexCoord2f32(lbl_800F78C0[(p->uvOrder >> 12) & 0xF].s, lbl_800F78C0[(p->uvOrder >> 12) & 0xF].t);
            }
        }
        p = (StreakParticle*)p->next;
    } while (p != NULL);
    GXLoadPosMtxImm(lbl_8017FFE0, GX_PNMTX0);
    return alive == 0;
}
#endif

// .text:0x8002CDD0 size:0x7C
void fn_8002CDD0(Vec* end) {
    Emitter* e = FindEmitter(NULL, 10);
    if (e != NULL && e->u.t10.unk40 != 0) {
        e->u.t10.end.x = end->x;
        e->u.t10.end.y = end->y;
        e->u.t10.end.z = end->z;
        PSVECSubtract(&e->u.t10.end, &e->u.t10.start, &e->u.t10.dir);
    }
}

// .text:0x8002CE4C size:0x9E0
// NONMATCHING 95.5%: scheduling/registers of the up-front parameter conversions (declaration and conversion order tuned by search); same calls and stores
#if NONMATCHING
void fn_8002CE4C(Vec* start, Vec* end, ParticleParamsA* prm) {
    Vec n;
    s32 sign = 1;
    s32 total;
    s32 p3Range;
    s32 totalRange;
    s32 fadeRange;
    s32 totalMin;
    s32 fadeMin;
    s32 p3Min;
    s32 ang;
    f32 r;
    f32 split;
    f32 splitRange;
    f32 yawMin;
    f32 yawMax;
    f32 rMin;
    f32 rRange;
    f32 dirLen;
    f32 dirLenRange;
    f32 pitchMax;
    f32 angMin;
    f32 pitchMin;
    f32 angRange;
    f32 spinMin;
    f32 spinRange;
    f32 lenAMin;
    f32 lenARange;
    f32 lenBMin;
    f32 lenBRange;
    f32 reachMin;
    f32 reachRange;
    f32 offMin;
    f32 offRange;
    Emitter* e;
    StreakParticle* p;

    e = NewEmitter(fn_8002C56C, 0x80, 0, prm->count, 1, 10);
    if (e == NULL) {
        return;
    }
    totalMin = (s32)((f32)prm->unk10 * ((f32)prm->unk14 / 100000.0f));
    totalRange = (s32)((f32)prm->unk10 * ((f32)prm->unk18 / 100000.0f) - (f32)totalMin);
    split = (f32)prm->unk1C / 100000.0f;
    splitRange = (f32)(prm->unk20 - prm->unk1C) / 100000.0f;
    p3Min = prm->unk24;
    rMin = (f32)prm->unk34 / 100000.0f;
    fadeMin = prm->unk2C;
    fadeRange = prm->unk30 - prm->unk2C;
    p3Range = prm->unk28 - prm->unk24;
    yawMax = (f32)prm->unk40 / 100000.0f;
    yawMin = (f32)prm->unk3C / 100000.0f;
    rRange = (f32)(prm->unk38 - prm->unk34) / 100000.0f;
    pitchMax = (f32)prm->unk48 / 100000.0f;
    angMin = (f32)prm->unk54 / 100000.0f;
    dirLen = (f32)prm->unk4C / 100000.0f;
    dirLenRange = (f32)(prm->unk50 - prm->unk4C) / 100000.0f;
    angRange = (f32)(prm->unk58 - prm->unk54) / 100000.0f;
    spinMin = (f32)prm->unk5C / 100000.0f;
    pitchMin = (f32)prm->unk44 / 100000.0f;
    spinRange = (f32)(prm->unk60 - prm->unk5C) / 100000.0f;
    lenAMin = (f32)prm->unk64 / 100000.0f;
    lenARange = (f32)(prm->unk68 - prm->unk64) / 100000.0f;
    lenBMin = (f32)prm->unk6C / 100000.0f;
    lenBRange = (f32)(prm->unk70 - prm->unk6C) / 100000.0f;
    reachMin = (f32)prm->unk74 / 100000.0f;
    reachRange = (f32)(prm->unk78 - prm->unk74) / 100000.0f;
    offMin = (f32)prm->unk7C / 100000.0f;
    offRange = (f32)(prm->unk80 - prm->unk7C) / 100000.0f;
    e->tex = prm->tex;
    e->u.t10.texIndex = prm->texIndex;
    e->u.t10.unk40 = prm->unk10;
    e->u.t10.start.x = start->x;
    e->u.t10.start.y = start->y;
    e->u.t10.start.z = start->z;
    e->u.t10.end.x = end->x;
    e->u.t10.end.y = end->y;
    e->u.t10.end.z = end->z;
    PSVECSubtract(end, start, &e->u.t10.dir);
    p = (StreakParticle*)e->particles;
    do {
        p->delay = (prm->unkC * rand()) / 32767;
        total = totalMin + (totalRange * rand()) / 32767;
        p->dur[0] = p->rem[0] = (s16)((f32)total * (split + (splitRange * (f32)rand()) / 32767.0f));
        p->dur[1] = p->rem[1] = total - p->dur[0];
        p->dur[2] = p->rem[2] = p3Min + (p3Range * rand()) / 32767;
        p->dir.x = dirLen + (dirLenRange * (f32)rand()) / 32767.0f;
        p->dir.y = 0.0f;
        p->dir.z = 0.0f;
        fn_800332B8(&p->dir, &p->dir, yawMin, yawMax, pitchMin, pitchMax);
        p->dir.x = p->dir.x * (f32)sign;
        sign *= -1;
        PSVECNormalize(&p->dir, &n);
        PSVECScale(&n, offMin + (offRange * (f32)rand()) / 32767.0f, &p->offset);
        p->lenA = lenAMin + (lenARange * (f32)rand()) / 32767.0f;
        p->lenB = (lenBMin + (lenBRange * (f32)rand()) / 32767.0f) - p->lenA;
        p->reach = reachMin + (reachRange * (f32)rand()) / 32767.0f;
        p->spin = spinMin + (spinRange * (f32)rand()) / 32767.0f;
        ang = (s32)(0.5f + (2048.0f * (angMin + (angRange * (f32)rand()) / 32767.0f)) / 360.0f);
        r = 1.4142135f * ((rMin + (rRange * (f32)rand()) / 32767.0f) * 0.5f);
        p->sizeX = r * CosIdxB(ang);
        p->sizeY = r * SinIdx(ang);
        p->color.rgba = 0xFFFFFFFF;
        p->uvOrder = (rand() & 1) ? 0x123 : 0x321;
        p->fade = fadeMin + (fadeRange * rand()) / 32767;
        p = (StreakParticle*)p->next;
    } while (p != NULL);
}
#endif

// .text:0x8002D82C size:0x43C
// NONMATCHING 94%: register allocation of the color/physics loop walkers (r4/r5) differs
#if NONMATCHING
s32 fn_8002D82C(Emitter* e) {
    Mtx ident;
    Vec v;
    TexCoordF* uv = lbl_800F78C0;
    Particle* p = e->particles;
    s32 alive = 0;
    TexArchive* arc = e->tex;
    s32 tex = p->texIndex;
    TexImage* img;
    GXTexObj texObj;
    GXTlutObj tlutObj;
    s32 k;
    s32 c;

    if (arc == NULL) {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    } else {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
        img = &arc->entries[arc->entries[tex].index];
        if (img->tlut != NULL) {
            GXInitTexObjCI(&texObj, PTR32_GET(u8, img->data), img->width, img->height, img->format, GX_CLAMP, GX_CLAMP, GX_FALSE, 0);
            GXInitTlutObj(&tlutObj, PTR32_GET(void, img->tlut), img->tlutFormat, img->tlutEntries);
            GXLoadTlut(&tlutObj, GX_TLUT0);
        } else {
            GXInitTexObj(&texObj, PTR32_GET(u8, img->data), img->width, img->height, img->format, GX_CLAMP, GX_CLAMP, GX_FALSE);
        }
        GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, (f32)img->minLOD, (f32)img->maxLOD, img->lodBias, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&texObj, GX_TEXMAP1);
    }
    PSMTXIdentity(ident);
    GXLoadPosMtxImm(ident, GX_PNMTX0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    do {
        if (p->life != 0) {
            alive++;
            if (p->delay != 0) {
                p->delay -= (lbl_80366158._28 == 0);
            } else {
                PSMTXMultVec(lbl_8017FFE0, &p->pos, &v);
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                GXPosition3f32(v.x - p->sizeX, v.y - p->sizeY, v.z);
                GXColor1u32(PCOLOR_GET(p->color));
                GXTexCoord2f32(uv[p->uvOrder & 3].s, uv[p->uvOrder & 3].t);
                GXPosition3f32(v.x + p->sizeY, v.y - p->sizeX, v.z);
                GXColor1u32(PCOLOR_GET(p->color));
                GXTexCoord2f32(uv[(p->uvOrder >> 2) & 3].s, uv[(p->uvOrder >> 2) & 3].t);
                GXPosition3f32(v.x + p->sizeX, v.y + p->sizeY, v.z);
                GXColor1u32(PCOLOR_GET(p->color));
                GXTexCoord2f32(uv[(p->uvOrder >> 4) & 3].s, uv[(p->uvOrder >> 4) & 3].t);
                GXPosition3f32(v.x - p->sizeY, v.y + p->sizeX, v.z);
                GXColor1u32(PCOLOR_GET(p->color));
                GXTexCoord2f32(uv[(p->uvOrder >> 6) & 3].s, uv[(p->uvOrder >> 6) & 3].t);
                if (lbl_80366158._28 == 0) {
                    p->life--;
                    for (k = 0; k < 3; k++) {
                        c = p->color.v[k] + (s8)p->colorStep.v[k];
                        if (c < 0) {
                            c = 0;
                        } else if (c > 0xFF) {
                            c = 0xFF;
                        }
                        p->color.v[k] = c;
                        (&p->u.phys.accel.x)[k] = (&p->u.phys.force.x)[k] / p->u.phys.mass;
                        (&p->u.phys.vel.x)[k] += (&p->u.phys.accel.x)[k];
                        (&p->pos.x)[k] += (&p->u.phys.vel.x)[k];
                    }
                    c = p->color.v[k] + (s8)p->colorStep.v[k];
                    if (c < 0) {
                        c = 0;
                    } else if (c > 0xFF) {
                        c = 0xFF;
                    }
                    p->color.v[k] = c;
                    if (p->life <= e->u.t9.fadeLife && p->colorStep.v[3] == 0) {
                        p->colorStep.v[3] = -0x100 / p->life;
                    }
                }
            }
        }
        p = p->next;
    } while (p != NULL);
    GXLoadPosMtxImm(lbl_8017FFE0, GX_PNMTX0);
    return alive == 0;
}
#endif

// .text:0x8002DC68 size:0x7C
void fn_8002DC68(Vec* pos) {
    Emitter* e = FindEmitter(NULL, 9);
    if (e != NULL) {
        memcpy(&e->u.t9.prevPos, &e->u.t9.pos, sizeof(Vec));
        memcpy(&e->u.t9.pos, pos, sizeof(Vec));
    }
}

// .text:0x8002DCE4 size:0x6F8
// NONMATCHING 73%: float load scheduling/registers; the cos index uses a branchy abs in the original
#if NONMATCHING
void fn_8002DCE4(Vec* from, Vec* to, ParticleParams9* prm) {
    Vec d;
    s32 sign = 1;
    f32 sizeMin = (f32)prm->sizeMin / 100000.0f;
    f32 yawMin = (f32)prm->yawMin / 100000.0f;
    f32 yawMax = (f32)prm->yawMax / 100000.0f;
    f32 pitchMin = (f32)prm->pitchMin / 100000.0f;
    f32 pitchMax = (f32)prm->pitchMax / 100000.0f;
    f32 angleRange = (f32)(prm->angleMax - prm->angleMin) / 100000.0f;
    f32 sizeRange = (f32)prm->sizeMax / 100000.0f - sizeMin;
    f32 angleBase = 45.0f + (f32)prm->angleMin / 100000.0f;
    f32 speed;
    f32 r;
    s32 ang;
    Emitter* e;
    Particle* p;

    PSVECSubtract(to, from, &d);
    speed = (f32)prm->speed / 100000.0f;
    e = NewEmitter(fn_8002D82C, 0x80, 0, prm->count, 1, 9);
    if (e == NULL) {
        return;
    }
    e->tex = prm->tex;
    e->u.t9.fadeLife = prm->fadeLife;
    memcpy(&e->u.t9.pos, to, sizeof(Vec));
    memcpy(&e->u.t9.prevPos, to, sizeof(Vec));
    p = e->particles;
    do {
        p->delay = rand() % prm->delayRange;
        p->life = prm->life - p->delay - rand() % prm->lifeRange;
        p->pos.x = from->x;
        p->pos.y = from->y;
        p->pos.z = from->z;
        p->u.phys.vel.x = d.x / (f32)(p->life - 1);
        p->u.phys.vel.y = d.y / (f32)(p->life - 1);
        p->u.phys.vel.z = d.z / (f32)(p->life - 1);
        fn_800332B8(NULL, &p->u.phys.force, yawMin, yawMax, pitchMin, pitchMax);
        PSVECScale(&p->u.phys.force, speed * (0.5f * (f32)(rand() % 256) + 0.75f), &p->u.phys.force);
        p->u.phys.force.x = p->u.phys.force.x * (f32)sign;
        sign = -sign;
        PSVECScale(&p->u.phys.force, 0.5f * (f32)-p->life, &p->u.phys.accel);
        PSVECAdd(&p->u.phys.vel, &p->u.phys.accel, &p->u.phys.vel);
        p->u.phys.mass = 1.0f;
        if (angleRange != 0.0f) {
            ang = (s32)(0.5f + (2048.0f * (angleBase + (angleRange * (f32)rand()) / 32767.0f)) / 360.0f);
            r = 1.4142135f * ((sizeMin + (sizeRange * (f32)rand()) / 32767.0f) * 0.5f);
            p->sizeX = r * CosIdx(ang);
            p->sizeY = r * SinIdx(ang);
            p->uvOrder = (rand() & 1) ? 0x1B : 0xE4;
        } else {
            r = (sizeMin + (sizeRange * (f32)rand()) / 32767.0f) * 0.5f;
            p->sizeX = r;
            p->sizeY = r;
            p->uvOrder = 0xB1;
        }
        p->color.rgba = 0xFFFFFFFF;
        p->colorStep.all = 0;
        p->texIndex = prm->texIndex;
        p = p->next;
    } while (p != NULL);
}
#endif

// .text:0x8002E3DC size:0x44C
s32 fn_8002E3DC(Emitter* e) {
    Particle* p = e->particles;
    s32 alive = 0;
    f32 size;

    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    do {
        if (lbl_80366158._28 == 0) {
            p->life -= (p->life > 0) & (lbl_80366158._28 == 0);
            p->color.c.a -= p->u.t6.unk18 / p->u.t6.unk1C;
            size = (p->u.t6.unk14 - p->u.t6.unk10) * ((f32)(p->u.t6.unk1C - p->life) / (f32)p->u.t6.unk1C) + p->u.t6.unk10;
            p->sizeY = size;
            p->sizeX = size;
        }
        QuadCorners(lbl_80180010, p->sizeX, p->sizeY);
        DrawParticleQuad(p, e->tex, lbl_80180010);
        alive += (p->life > 0);
        p = p->next;
    } while (p != NULL);
    return alive == 0;
}

// .text:0x8002E828 size:0x478
// NONMATCHING 99.8%: float register allocation of the inlined corner setup
#if NONMATCHING
s32 fn_8002E828(Emitter* e) {
    Particle* p = e->particles;
    s32 alive = 0;
    f32 size;

    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    do {
        p->life -= (p->life > 0) & (lbl_80366158._28 == 0);
        if (p->life > p->u.t6.unk20) {
            p->color.c.a = (p->u.t6.unk18 * (p->u.t6.unk1C - p->life)) / p->u.t6.unk20;
        } else {
            p->color.c.a = (p->u.t6.unk18 * p->life) / p->u.t6.unk20;
        }
        size = p->u.t6.unk10 + ((p->u.t6.unk14 - p->u.t6.unk10) * (f32)(p->u.t6.unk1C - p->life)) / (f32)p->u.t6.unk1C;
        p->sizeY = size;
        p->sizeX = size;
        QuadCorners(lbl_80180010, p->sizeX, p->sizeY);
        DrawParticleQuad(p, e->tex, lbl_80180010);
        alive += (p->life > 0);
        p = p->next;
    } while (p != NULL);
    return alive == 0;
}
#endif

// .text:0x8002ECA0 size:0x50C
// NONMATCHING 99.5%: float load order and the fcmpu operand order of the PSVECMag test
#if NONMATCHING
s32 fn_8002ECA0(Emitter* e) {
    Vec d;
    Particle* p = e->particles;
    s32 alive = 0;
    GXPrimitive prim;
    Particle* deadHead = NULL;
    Particle* lastDead = NULL;
    Particle** link = &e->particles;
    s32 a;

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    do {
        PSVECSubtract(&p->pos, &p->u.trail.prev, &d);
        LoadParticleTexOf(p, e->tex);
        if (0.0f != PSVECMag(&d)) {
            PSVECNormalize(&d, &d);
            PSVECScale(&d, p->u.trail.width * 0.5f, &d);
            prim = GX_TRIANGLESTRIP;
        } else {
            d.x = 0.0f;
            d.y = 0.0f;
            d.z = -p->u.trail.width * 0.5f;
            prim = GX_QUADS;
        }
        a = (p->u.trail.alphaMax * p->life) / p->u.trail.maxLife;
        if (a > p->u.trail.alphaMax) {
            a = p->u.trail.alphaMax;
        }
        p->color.c.a = a;
        GXBegin(prim, GX_VTXFMT0, 8);
        GXPosition3f32((p->pos.x + d.x) - d.z, p->pos.y, d.x + (p->pos.z + d.z));
        GXColor1u32(PARTICLE_RGBA(p->color));
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(d.z + (p->pos.x + d.x), p->pos.y, (p->pos.z + d.z) - d.x);
        GXColor1u32(PARTICLE_RGBA(p->color));
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(p->pos.x - d.z, p->pos.y, p->pos.z + d.x);
        GXColor1u32(PARTICLE_RGBA(p->color));
        GXTexCoord2f32(0.0f, 0.25f);
        GXPosition3f32(p->pos.x + d.z, p->pos.y, p->pos.z - d.x);
        GXColor1u32(PARTICLE_RGBA(p->color));
        GXTexCoord2f32(1.0f, 0.25f);
        GXPosition3f32(p->u.trail.prev.x - d.z, p->u.trail.prev.y, p->u.trail.prev.z + d.x);
        GXColor1u32(PARTICLE_RGBA(p->color));
        GXTexCoord2f32(0.0f, 0.75f);
        GXPosition3f32(p->u.trail.prev.x + d.z, p->u.trail.prev.y, p->u.trail.prev.z - d.x);
        GXColor1u32(PARTICLE_RGBA(p->color));
        GXTexCoord2f32(1.0f, 0.75f);
        GXPosition3f32((p->u.trail.prev.x - d.x) - d.z, p->u.trail.prev.y, d.x + (p->u.trail.prev.z - d.z));
        GXColor1u32(PARTICLE_RGBA(p->color));
        GXTexCoord2f32(0.0f, 1.0f);
        GXPosition3f32(d.z + (p->u.trail.prev.x - d.x), p->u.trail.prev.y, (p->u.trail.prev.z - d.z) - d.x);
        GXColor1u32(PARTICLE_RGBA(p->color));
        GXTexCoord2f32(1.0f, 1.0f);
        p->life -= (lbl_80366158._28 == 0);
        if (p->life == 0) {
            // unlink and collect the dead particle
            *link = p->next;
            if (lastDead != NULL) {
                lastDead->next = p;
            } else {
                deadHead = p;
            }
            p->next = NULL;
            lastDead = p;
            e->count--;
        } else {
            link = &p->next;
            alive++;
        }
        p = *link;
    } while (p != NULL);
    if (deadHead != NULL) {
        FreeParticles(deadHead);
    }
    return alive == 0;
}
#endif

// .text:0x8002F1AC size:0xAC
s32 fn_8002F1AC(Vec* pos, s32 id) {
    Emitter* e = FindEmitter(NULL, 6);
    Particle* p;
    if (e != NULL && lbl_80366158._28 == 0) {
        for (p = e->particles; p != NULL; p = p->next) {
            if (p->u.trail.id == id) {
                memcpy(&p->pos, pos, sizeof(Vec));
                p->life++;
                return 1;
            }
        }
    }
    return 0;
}

// .text:0x8002F258 size:0x39C
// NONMATCHING 97.3%: one lbl_803CBC74 load is hoisted in the original inlined particle allocation
#if NONMATCHING
void fn_8002F258(Vec* pos, s32 id, ParticleParams* prm) {
    Emitter tmp;
    Emitter* e = FindEmitter(NULL, 6);
    Emitter* t;
    Particle* p;
    Particle* last;

    if (e != NULL) {
        // append one more trail segment to the existing emitter
        t = AllocParticles(&tmp, 1, 1);
        if (t == NULL) {
            return;
        }
        t->tex = prm->tex;
        p = t->particles;
        p->pos.x = pos->x;
        p->pos.y = pos->y;
        p->pos.z = pos->z;
        p->u.trail.prev.x = pos->x;
        p->u.trail.prev.y = pos->y;
        p->u.trail.prev.z = pos->z;
        p->u.trail.width = (f32)prm->size / 100000.0f;
        p->u.trail.alphaMax = prm->unkC;
        p->u.trail.id = id;
        p->color.c.r = p->color.c.g = p->color.c.b = p->color.c.a = 0xFF;
        p->delay = 1;
        p->u.trail.maxLife = p->life = prm->unk10;
        p->unk4C = 1;
        p->texIndex = prm->texIndex;
        for (last = e->particles; last->next != NULL; last = last->next) {
        }
        last->next = t->particles;
        e->count++;
    } else {
        e = NewEmitter(fn_8002ECA0, 0x10, 0, 1, 1, 6);
        if (e == NULL) {
            return;
        }
        e->tex = prm->tex;
        p = e->particles;
        p->pos.x = pos->x;
        p->pos.y = pos->y;
        p->pos.z = pos->z;
        p->u.trail.prev.x = pos->x;
        p->u.trail.prev.y = pos->y;
        p->u.trail.prev.z = pos->z;
        p->u.trail.width = (f32)prm->size / 100000.0f;
        p->u.trail.alphaMax = prm->unkC;
        p->u.trail.id = id;
        p->color.c.r = p->color.c.g = p->color.c.b = p->color.c.a = 0xFF;
        p->delay = 1;
        p->u.trail.maxLife = p->life = prm->unk10;
        p->unk4C = 1;
        p->texIndex = prm->texIndex;
    }
}
#endif

// .text:0x8002F5F4 size:0x408
// NONMATCHING 86%: register allocation (prm/i, the inlined allocation) and a 0x10 smaller stack frame
#if NONMATCHING
void fn_8002F5F4(Vec* pos, Vec* dir, ParticleParams8* prm) {
    Vec v;
    f32 len = (f32)prm->length / 100000.0f;
    f32 start = ((f32)-prm->offset * len) / (f32)(prm->count - 1);
    f32 span = (start + len) - start;
    f32 size;
    f32 sizeMin;
    s32 i;
    Emitter* e;
    Particle* p;

    e = NewEmitter(fn_8002F9FC, 0x80, 0, prm->count * 2, 1, 8);
    if (e == NULL) {
        return;
    }
    e->tex = prm->tex;
    i = 0;
    p = e->particles;
    do {
        // two particles per step along dir: an additive one and a subtractive one
        PSVECScale(dir, start + ((f32)i * span) / (f32)(prm->count - 1), &v);
        PSVECAdd(pos, &v, &v);
        p->pos.x = v.x;
        p->pos.y = v.y;
        p->pos.z = v.z;
        if (i >= prm->count - prm->taper) {
            sizeMin = (f32)prm->sizeMin / 100000.0f;
            size = sizeMin + (((f32)prm->sizeMax / 100000.0f - sizeMin) * (f32)(prm->count - i - 1)) / (f32)prm->taper;
        } else {
            size = (f32)prm->sizeMax / 100000.0f;
        }
        p->sizeY = size;
        p->sizeX = size;
        PCOLOR_SET(p->color, (prm->gray << 24) | ((prm->gray << 8) | (prm->gray << 16)) | 0xFF);
        p->texIndex = prm->texIndex;
        p->uvFrame = 0;
        p->uvOrder = 1;
        p = p->next;
        p->pos.x = v.x;
        p->pos.y = v.y;
        p->pos.z = v.z;
        p->sizeY = size;
        p->sizeX = size;
        PCOLOR_SET(p->color, (prm->gray << 24) | ((prm->gray << 8) | (prm->gray << 16)) | 0xFF);
        p->texIndex = prm->texIndex2[i];
        p->uvFrame = 0;
        p->uvOrder = 0;
        p = p->next;
        i++;
    } while (p != NULL);
}
#endif

// .text:0x8002F9FC size:0x3BC
s32 fn_8002F9FC(Emitter* e) {
    Particle* p = e->particles;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    do {
        QuadCorners(lbl_80180010, p->sizeX, p->sizeY);
        // uvOrder selects the blend: nonzero subtracts, zero adds
        if (p->uvOrder != 0) {
            GXSetBlendMode(GX_BM_SUBTRACT, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
        } else {
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
        }
        DrawParticleQuad(p, e->tex, lbl_80180010);
        p = p->next;
    } while (p != NULL);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    return 1;
}

// .text:0x8002FDB8 size:0x6B8
// NONMATCHING 78%: float register allocation and scheduling
#if NONMATCHING
void fn_8002FDB8(Emitter* e, Vec* pos, Vec* dir, Vec* velScale, ParticleParams5* prm) {
    Mtx rot;
    Mtx base;
    Quaternion q;
    Vec up;
    Vec d;
    Vec axis;
    Vec sp;
    f32 mag;
    f32 yaw;
    f32 yaw2;
    f32 lo;
    f32 half;
    f32 k;
    s32 i;
    Particle* p;

    up = lbl_800E679C;
    e->tex = prm->tex;
    PSVECNormalize(dir, &d);
    PSVECCrossProduct(&up, &d, &axis);
    mag = PSVECMag(&axis);
    p = e->particles;
    for (i = 0; i < e->count; i++) {
        if (i & 1) {
            // odd particles use the mirrored spin of the previous particle
            yaw = -yaw2;
        } else {
            if (0.0f == mag) {
                PSMTXIdentity(base);
            } else {
                lo = (6.2831855f * ((f32)prm->unk38 / 100000.0f)) / 360.0f;
                half = ((6.2831855f * ((f32)prm->unk3C / 100000.0f)) / 360.0f - lo) * 0.5f;
                C_QUATRotAxisRad(&q, &axis, -((half * (f32)(8 - rand() % 16)) * 0.125f + (lo + half)));
                PSMTXQuat(base, &q);
            }
            yaw = ((6.2831855f * ((f32)prm->unk34 / 100000.0f)) / 360.0f) * (f32)(8 - rand() % 16) * 0.125f;
        }
        PSMTXRotRad(rot, 'Y', yaw);
        PSMTXConcat(rot, base, rot);
        PSMTXMultVec(rot, dir, &d);
        p->pos.x = pos->x;
        p->pos.y = pos->y;
        p->pos.z = pos->z;
        p->u.t5.vel.x = velScale->x * (f32)prm->unk10;
        p->u.t5.vel.y = velScale->y * (f32)prm->unk10;
        p->u.t5.vel.z = velScale->z * (f32)prm->unk10;
        // screen-space direction of the spray
        PSVECAdd(pos, &d, &d);
        PSMTXMultVec(lbl_8017FFE0, pos, &sp);
        PSMTXMultVec(lbl_8017FFE0, &d, &d);
        if (sp.z != d.z) {
            if (0.0f != d.z) {
                k = sp.z / d.z;
                d.z = sp.z;
                d.x = d.x * k;
                d.y = d.y * k;
            } else {
                k = d.z / sp.z;
                sp.z = d.z;
                sp.x = sp.x * k;
                sp.y = sp.y * k;
            }
        }
        PSVECSubtract(&sp, &d, &d);
        if (0.0f != PSVECMag(&d)) {
            PSVECNormalize(&d, &d);
        } else {
            d.x = 0.0f;
            d.y = 1.0f;
            d.z = 0.0f;
        }
        sp.y = d.x;
        sp.x = -d.y;
        sp.z = d.z;
        PSVECAdd(&d, &sp, &d);
        yaw2 = ((6.2831855f * ((f32)prm->unk30 / 100000.0f)) / 360.0f) * (f32)(8 - rand() % 16) * 0.125f;
        PSMTXRotRad(rot, 'Y', yaw2);
        PSMTXMultVec(rot, &d, &d);
        p->sizeX = d.x;
        p->sizeY = d.y;
        p->u.t5.unk1C = 0.01f * (f32)(8 - rand() % 16) + (f32)prm->unkC / 100000.0f;
        p->u.t5.unk20 = (f32)prm->unk20 / 100000.0f;
        p->u.t5.unk24 = (f32)prm->unk24 / 100000.0f;
        p->u.t5.unk2C = prm->unk18 - prm->unk1C;
        p->u.t5.unk28 = ((f32)prm->unk14 / 100000.0f) *
                        (0.02 * lbl_803CB804 * (rand() % 256) * 0.00390625 + (1.0f - 0.01f * lbl_803CB804));
        PCOLOR_SET(p->color, prm->unk40);
        p->u.t5.unk30 = prm->unk2C;
        p->u.t5.unk34 = (f32)prm->unk48 / 100000.0f;
        p->colorStep.v[0] = prm->unk4C;
        p->life = p->delay = prm->unk18;
        p->unk4C = 1;
        p->uvFrame = 0;
        p->texIndex = prm->texIndex;
        p->uvOrder = prm->unk28;
        p = p->next;
    }
}
#endif

// .text:0x80030470 size:0x2B0
// NONMATCHING 97.1%: register allocation in the inlined allocations
#if NONMATCHING
void fn_80030470(Vec* pos, Vec* dir, Vec* velScale, ParticleParams5* prm, u8 type) {
    Emitter tmp;
    Emitter* e = FindEmitter(NULL, type);
    Emitter* t;
    Particle* last;

    if (e != NULL) {
        t = AllocParticles(&tmp, prm->count, 1);
        if (t != NULL) {
            fn_8002FDB8(t, pos, dir, velScale, prm);
            for (last = e->particles; last->next != NULL; last = last->next) {
            }
            last->next = t->particles;
            e->count += t->count;
        }
    } else {
        e = NewEmitter(fn_80031034, 0x11, 0, prm->count, 1, type);
        if (e != NULL) {
            e->u.t5.unk18 = 0;
            fn_8002FDB8(e, pos, dir, velScale, prm);
        }
    }
}
#endif

// .text:0x80030720 size:0x668
// NONMATCHING 96.7%: float register allocation and scheduling
#if NONMATCHING
void fn_80030720(Emitter* e, Vec* pos, Vec* dir, ParticleParams5* prm) {
    Mtx rot;
    Mtx base;
    Quaternion q;
    Vec up;
    Vec dirN;
    Vec axis;
    Vec v;
    f32 mag;
    f32 yaw;
    f32 lo;
    f32 half;
    f32 speed;
    f32 a;
    f32 sn;
    f32 cs;
    s32 i;
    Particle* p = e->particles;

    up = lbl_800E6790;
    e->tex = prm->tex;
    PSVECNormalize(dir, &dirN);
    PSVECCrossProduct(&up, &dirN, &axis);
    mag = PSVECMag(&axis);
    for (i = 0; i < e->count; i++) {
        if (i & 1) {
            // odd particles mirror the previous one
            yaw = -yaw;
        } else {
            if (0.0f == mag) {
                PSMTXIdentity(base);
            } else {
                lo = (6.2831855f * ((f32)prm->unk38 / 100000.0f)) / 360.0f;
                half = ((6.2831855f * ((f32)prm->unk3C / 100000.0f)) / 360.0f - lo) * 0.5f;
                C_QUATRotAxisRad(&q, &axis, -((half * (f32)(8 - rand() % 16)) * 0.125f + (lo + half)));
                PSMTXQuat(base, &q);
            }
            yaw = ((6.2831855f * ((f32)prm->unk34 / 100000.0f)) / 360.0f) * (f32)(8 - rand() % 16) * 0.125f;
        }
        PSMTXRotRad(rot, 'Y', yaw);
        PSMTXConcat(rot, base, rot);
        PSMTXMultVec(rot, &dirN, &v);
        p->pos.x = pos->x;
        p->pos.y = pos->y;
        p->pos.z = pos->z;
        speed = ((f32)prm->unk10 / 100000.0f) *
                (0.02 * lbl_803CB800 * (rand() % 256) * 0.00390625 + (1.0f - 0.01f * lbl_803CB800));
        p->u.t5.vel.x = v.x * speed;
        p->u.t5.vel.y = v.y;
        p->u.t5.vel.z = v.z * speed;
        p->u.t5.unk34 = 0.0f;
        a = (((f32)prm->unk30 / 100000.0f) * 3.1415927f / 180.0f) * (f32)(0x80 - rand() % 256) * 0.0078125f +
            ((f32)prm->unk44 / 100000.0f) * 3.1415927f / 180.0f;
        sn = sin(a);
        cs = cos(a);
        p->sizeX = ((f32)prm->unkC / 100000.0f) * (sn - cs);
        p->sizeY = ((f32)prm->unkC / 100000.0f) * (cs + sn);
        p->u.t5.unk1C = 0.01f * (f32)(8 - rand() % 16) + (f32)prm->unkC / 100000.0f;
        p->u.t5.unk20 = (f32)prm->unk20 / 100000.0f;
        p->u.t5.unk24 = (f32)prm->unk24 / 100000.0f;
        p->u.t5.unk2C = prm->unk18 - prm->unk1C;
        p->u.t5.unk28 = ((f32)prm->unk14 / 100000.0f) *
                        (0.02 * lbl_803CB800 * (rand() % 256) * 0.00390625 + (1.0f - 0.01f * lbl_803CB800));
        PCOLOR_SET(p->color, prm->unk40);
        p->u.t5.unk30 = prm->unk2C;
        p->u.t5.unk34 = (f32)prm->unk48 / 100000.0f;
        p->colorStep.v[0] = prm->unk4C;
        p->life = p->delay = prm->unk18;
        p->unk4C = 1;
        p->uvFrame = 0;
        p->texIndex = prm->texIndex;
        p->uvOrder = prm->unk28;
        p = p->next;
    }
}
#endif

// .text:0x80030D88 size:0x2AC
// NONMATCHING 91%: register allocation in the inlined allocations
#if NONMATCHING
void fn_80030D88(Vec* pos, Vec* dir, ParticleParams5* prm, u8 type) {
    Emitter tmp;
    Emitter* e;
    Emitter* t;
    Particle* last;

    if (prm->count <= 0) {
        return;
    }
    e = FindEmitter(NULL, type);
    if (e != NULL) {
        t = AllocParticles(&tmp, prm->count, 1);
        if (t != NULL) {
            fn_80030720(t, pos, dir, prm);
            for (last = e->particles; last->next != NULL; last = last->next) {
            }
            last->next = t->particles;
            e->count += t->count;
        }
    } else {
        e = NewEmitter(fn_80031034, 0x11, 0, prm->count, 1, type);
        if (e != NULL) {
            e->u.t5.unk18 = 0;
            fn_80030720(e, pos, dir, prm);
        }
    }
}
#endif

// .text:0x80031034 size:0x790
// NONMATCHING 89%: the original addresses the corners/billboard matrix off the file-static bss base (lbl_8017EC00 + offset)
#if NONMATCHING
s32 fn_80031034(Emitter* e) {
    Vec a;
    Vec b;
    s32 alive = 0;
    s32 blend = -1;
    s32 alpha;
    f32 r;
    f32 o;
    f32 hx;
    f32 hy;
    s32 i;
    Particle* p;
    Particle** link;
    Particle* lastDead = NULL;
    Particle* deadHead = NULL;

    GXLoadPosMtxImm(lbl_8017FFE0, GX_PNMTX0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, e->u.t5.unk18);
    e->particles = ZSortParticles(e->particles, e->count);
    p = e->particles;
    link = &e->particles;
    while (p != NULL) {
        // uvOrder holds the blend mode for these particles (nonzero: additive)
        if (blend != p->uvOrder) {
            blend = p->uvOrder;
            if (blend != 0) {
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
            } else {
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
            }
        }
        if (p->colorStep.v[0] == 0) {
            if (p->sizeX * p->sizeX > p->sizeY * p->sizeY) {
                r = p->u.t5.unk1C * p->sizeX * 0.5f;
            } else {
                r = p->u.t5.unk1C * p->sizeY * 0.5f;
            }
            o = r;
            if (r > 0.0f) {
                o = -r;
            }
            o = o * p->u.t5.unk34;
            lbl_80180010[0].x = (-p->u.t5.unk1C * p->sizeX) * 0.5f;
            lbl_80180010[0].y = o - (p->u.t5.unk1C * p->sizeY) * 0.5f;
            lbl_80180010[0].z = 0.0f;
            lbl_80180010[1].x = (-p->u.t5.unk1C * p->sizeY) * 0.5f;
            lbl_80180010[1].y = (p->u.t5.unk1C * p->sizeX) * 0.5f + o;
            lbl_80180010[1].z = 0.0f;
            lbl_80180010[2].x = (p->u.t5.unk1C * p->sizeX) * 0.5f;
            lbl_80180010[2].y = (p->u.t5.unk1C * p->sizeY) * 0.5f + o;
            lbl_80180010[2].z = 0.0f;
            lbl_80180010[3].x = (p->u.t5.unk1C * p->sizeY) * 0.5f;
            lbl_80180010[3].y = o - (p->u.t5.unk1C * p->sizeX) * 0.5f;
            lbl_80180010[3].z = 0.0f;
        } else {
            a.x = p->sizeX * 0.5f;
            a.y = p->sizeY * 0.5f;
            a.z = 0.0f;
            b.x = p->sizeY * 0.5f;
            b.y = -p->sizeX * 0.5f;
            b.z = 0.0f;
            PSVECAdd(&a, &b, &b);
            PSVECNormalize(&b, &b);
            PSVECScale(&b, p->u.t5.unk34, &b);
            hx = p->u.t5.unk1C * p->sizeX;
            hy = p->u.t5.unk1C * p->sizeY;
            lbl_80180010[0].x = b.x - hx * 0.5f;
            lbl_80180010[0].y = b.y - hy * 0.5f;
            lbl_80180010[0].z = 0.0f;
            lbl_80180010[1].x = b.x - hy * 0.5f;
            lbl_80180010[1].y = hx * 0.5f + b.y;
            lbl_80180010[1].z = 0.0f;
            lbl_80180010[2].x = hx * 0.5f + b.x;
            lbl_80180010[2].y = hy * 0.5f + b.y;
            lbl_80180010[2].z = 0.0f;
            lbl_80180010[3].x = hy * 0.5f + b.x;
            lbl_80180010[3].y = b.y - hx * 0.5f;
            lbl_80180010[3].z = 0.0f;
        }
        if (p->u.t5.unk2C > p->life) {
            if (lbl_80366158._28 == 0) {
                p->u.t5.unk1C = p->u.t5.unk1C * p->u.t5.unk24;
            }
            alpha = (p->u.t5.unk30 * p->life) / p->u.t5.unk2C;
        } else {
            if (lbl_80366158._28 == 0) {
                p->u.t5.unk1C = p->u.t5.unk1C * p->u.t5.unk20;
            }
            // delay holds the initial life here
            alpha = (p->u.t5.unk30 * (p->delay - p->life)) / (p->delay - p->u.t5.unk2C);
        }
        for (i = 0; i < 4; i++) {
            PSMTXMultVec(lbl_8017FF78[0], &lbl_80180010[i], &lbl_80180010[i]);
        }
        DrawParticleQuad(p, e->tex, lbl_80180010);
        if (alpha < 0) {
            p->life = 0;
        } else if (lbl_80366158._28 == 0) {
            p->pos.x += p->u.t5.vel.x;
            p->pos.y += p->u.t5.vel.y;
            p->pos.z += p->u.t5.vel.z;
            p->u.t5.vel.x = p->u.t5.vel.x * p->u.t5.unk28;
            p->u.t5.vel.y = p->u.t5.vel.y * p->u.t5.unk28;
            p->u.t5.vel.z = p->u.t5.vel.z * p->u.t5.unk28;
            p->color.c.a = alpha;
            p->life--;
        }
        if (p->life == 0) {
            *link = p->next;
            if (lastDead != NULL) {
                lastDead->next = p;
            } else {
                deadHead = p;
            }
            p->next = NULL;
            lastDead = p;
            e->count--;
        } else {
            link = &p->next;
            alive++;
        }
        p = *link;
    }
    if (deadHead != NULL) {
        FreeParticles(deadHead);
    }
    return alive == 0;
}
#endif

// .text:0x800317C4 size:0x4E0
// NONMATCHING 85%: float register allocation in the per-particle setup
#if NONMATCHING
void fn_800317C4(Emitter* e, Vec* pos, ParticleParams5* prm) {
    Particle* p = e->particles;
    s32 i;
    s32 ang;
    f32 s;
    f32 c;
    f32 speed;
    f32 a;

    e->tex = prm->tex;
    for (i = 0; i < e->count; i++) {
        ang = ((i * 0x5000) / e->count + 5) / 10;
        s = SinIdx(ang);
        c = CosIdx(ang);
        p->pos.x = pos->x;
        p->pos.y = pos->y;
        p->pos.z = pos->z;
        speed = ((f32)prm->unk10 / 100000.0f) *
                (0.02 * lbl_803CB800 * (rand() % 256) * 0.00390625 + (1.0f - 0.01f * lbl_803CB800));
        p->u.t5.vel.x = s * speed;
        p->u.t5.vel.y = 0.0f;
        p->u.t5.vel.z = c * speed;
        p->u.t5.unk34 = 0.0f;
        a = (((f32)prm->unk30 / 100000.0f) * 3.1415927f / 180.0f) * (f32)(0x80 - rand() % 256) * 0.0078125f +
            ((f32)prm->unk44 / 100000.0f) * 3.1415927f / 180.0f;
        s = sin(a);
        c = cos(a);
        p->sizeX = ((f32)prm->unkC / 100000.0f) * (s - c);
        p->sizeY = ((f32)prm->unkC / 100000.0f) * (c + s);
        p->u.t5.unk1C = 0.01f * (f32)(8 - rand() % 16) + (f32)prm->unkC / 100000.0f;
        p->u.t5.unk20 = (f32)prm->unk20 / 100000.0f;
        p->u.t5.unk24 = (f32)prm->unk24 / 100000.0f;
        p->u.t5.unk2C = prm->unk18 - prm->unk1C;
        p->u.t5.unk28 = ((f32)prm->unk14 / 100000.0f) *
                        (0.02 * lbl_803CB800 * (rand() % 256) * 0.00390625 + (1.0f - 0.01f * lbl_803CB800));
        PCOLOR_SET(p->color, prm->unk40);
        p->u.t5.unk30 = prm->unk2C;
        p->u.t5.unk34 = (f32)prm->unk48 / 100000.0f;
        p->colorStep.v[0] = prm->unk4C;
        p->life = p->delay = prm->unk18;
        p->unk4C = 1;
        p->uvFrame = 0;
        p->texIndex = prm->texIndex;
        p->uvOrder = prm->unk28;
        p = p->next;
    }
}
#endif

// .text:0x80031CA4 size:0x290
// NONMATCHING 98.3%: register allocation in the inlined allocations
#if NONMATCHING
void fn_80031CA4(Vec* pos, ParticleParams5* prm) {
    Emitter tmp;
    Emitter* e = FindEmitter(NULL, 5);
    Emitter* t;
    Particle* last;

    if (e != NULL) {
        // add another ring to the running emitter
        t = AllocParticles(&tmp, prm->count, 1);
        if (t != NULL) {
            fn_800317C4(t, pos, prm);
            for (last = e->particles; last->next != NULL; last = last->next) {
            }
            last->next = t->particles;
            e->count += t->count;
        }
    } else {
        e = NewEmitter(fn_80031034, 0x11, 0, prm->count, 1, 5);
        if (e != NULL) {
            e->u.t5.unk18 = 0;
            fn_800317C4(e, pos, prm);
        }
    }
}
#endif

// .text:0x80031F34 size:0x104
// NONMATCHING 92%: the original keeps n and the count copy in separate saved regs
#if NONMATCHING
Particle* fn_80031F34(Particle* list, s32 n) {
    return ZSortParticles(list, n);
}
#endif

// .text:0x80032038 size:0x2C
s32 fn_80032038(const void* a, const void* b) {
    if (((const ParticleSortEntry*)a)->z > ((const ParticleSortEntry*)b)->z) {
        return 1;
    }
    if (((const ParticleSortEntry*)a)->z < ((const ParticleSortEntry*)b)->z) {
        return -1;
    }
    return 0;
}

// .text:0x80032064 size:0x220
void fn_80032064(Vec* pos, ParticleParamsB* prm) {
    Emitter* e;
    Particle* p;
    f32 size;
    ParticleParams* tmpl;

    tmpl = &lbl_800F787C;
    tmpl->tex = lbl_803CBD0C;
    e = NewEmitter(fn_8002E828, 0x80, 0, 1, 1, 6);
    if (e != NULL) {
        e->tex = tmpl->tex;
        p = e->particles;
        p->pos.x = pos->x;
        p->pos.y = pos->y;
        p->pos.z = pos->z;
        PCOLOR_SET(p->color, 0xFFFFFF00);
        p->u.t6.unk18 = tmpl->unk10;
        p->u.t6.unk1C = p->life = tmpl->life;
        p->u.t6.unk20 = tmpl->life / 2;
        size = (f32)tmpl->size / 100000.0f;
        p->u.t6.unk10 = size;
        p->sizeY = size;
        p->sizeX = size;
        p->u.t6.unk14 = (f32)tmpl->unkC / 100000.0f;
        p->texIndex = tmpl->texIndex;
    }
    fn_8002A1CC(pos, prm);
}

// .text:0x80032284 size:0x268
void fn_80032284(Vec* pos) {
    ParticleParams prm;
    Emitter* e;
    Particle* p;
    f32 size;

    memcpy(&prm, &lbl_800F787C, sizeof(ParticleParams));
    prm.tex = lbl_803CBD0C;
    prm.unk10 = 0xFF;
    prm.size = 500000;
    prm.unkC = 700000;
    prm.life = 0x20;
    e = NewEmitter(fn_8002E3DC, 0x80, 0, 1, 1, 7);
    if (e != NULL) {
        e->tex = prm.tex;
        p = e->particles;
        p->pos.x = pos->x;
        p->pos.y = pos->y;
        p->pos.z = pos->z;
        PCOLOR_SET(p->color, 0xFFFFFF00);
        p->color.c.a = prm.unk10;
        p->u.t6.unk18 = prm.unk10;
        p->u.t6.unk1C = p->life = prm.life;
        p->u.t6.unk20 = prm.life / 2;
        size = (f32)prm.size / 100000.0f;
        p->u.t6.unk10 = size;
        p->sizeY = size;
        p->sizeX = size;
        p->u.t6.unk14 = (f32)prm.unkC / 100000.0f;
        p->texIndex = prm.texIndex;
    }
}

// .text:0x800324EC size:0x3F4
void fn_800324EC(u16 anim, s32 a, s32 b, ParticleParamsB* prm) {
    Vec pos;
    Vec q;
    u32 colors[32];
    Emitter* e;
    Particle* p;
    u32 i;
    f32 size;
    ParticleParams* tmpl;

    if (a < 0 || a >= 13 || lbl_8036E548.active[a] == NULL) {
        return;
    }
    getAnimRelatedCoordinates(a, anim, &pos);
    if (b >= 0 && b < 13 && lbl_8036E548.active[b] != NULL) {
        // midpoint between the two actors
        getAnimRelatedCoordinates(b, anim, (VecXYZ*)&q);
        PSVECSubtract(&q, &pos, &q);
        PSVECScale(&q, 0.5f, &q);
        PSVECAdd(&pos, &q, &pos);
    }
    // never read: the camera translation and a table of 32 colors
    q.x = lbl_8017FFE0[0][3];
    q.y = lbl_8017FFE0[1][3];
    q.z = lbl_8017FFE0[2][3];
    colors[0] = (lbl_800F787C.unk18[8] << 24) | (lbl_800F787C.unk18[9] << 16) | (lbl_800F787C.unk18[10] << 8) | 0xFF;
    for (i = 1; i < 32; i++) {
        colors[i] = colors[0];
    }
    tmpl = &lbl_800F787C;
    tmpl->tex = lbl_803CBD0C;
    e = NewEmitter(fn_8002E828, 0x80, 0, 1, 1, 6);
    if (e != NULL) {
        e->tex = tmpl->tex;
        p = e->particles;
        p->pos.x = pos.x;
        p->pos.y = pos.y;
        p->pos.z = pos.z;
        PCOLOR_SET(p->color, 0xFFFFFF00);
        p->u.t6.unk18 = tmpl->unk10;
        p->u.t6.unk1C = p->life = tmpl->life;
        p->u.t6.unk20 = tmpl->life / 2;
        size = (f32)tmpl->size / 100000.0f;
        p->u.t6.unk10 = size;
        p->sizeY = size;
        p->sizeX = size;
        p->u.t6.unk14 = (f32)tmpl->unkC / 100000.0f;
        p->texIndex = tmpl->texIndex;
    }
    if (prm != NULL) {
        fn_8002A1CC(&pos, prm);
    }
}

// .text:0x800328E0 size:0x7EC
// NONMATCHING 88%: the original addresses the corners/billboard matrix off the file-static bss base (lbl_8017EC00 + offset); register allocation
#if NONMATCHING
s32 fn_800328E0(Emitter* e) {
    Mtx rotM;
    Quaternion q;
    Vec ref;
    Vec dir;
    Vec axis;
    Vec v;
    f32 angle;
    f32 s;
    f32 spread;
    f32 cosA;
    f32 sinA;
    f32 spd;
    f32 h;
    s32 ang;
    s32 r;
    s32 k;
    s32 c;
    s32 count = 0;
    Particle* p = e->particles;

    ref = lbl_800E6784;
    QuadCorners(lbl_80180010, p->sizeX, p->sizeY);
    memcpy(&dir, &e->u.t1.dir, sizeof(Vec));
    angle = acos(PSVECDotProduct(&ref, &dir));
    PSVECCrossProduct(&ref, &dir, &axis);
    angle = angle * 0.5f;
    s = sin(angle);
    q.w = cos(angle);
    q.x = axis.x * s;
    q.y = axis.y * s;
    q.z = axis.z * s;
    PSMTXQuat(rotM, &q);
    do {
        if (p->delay > 0) {
            p->delay -= (lbl_80366158._28 == 0);
            count++;
        } else if (p->life != 0) {
            if (lbl_80366158._28 == 0) {
                p->u.phys.force.z = 0.0f;
                p->u.phys.force.x = 0.0f;
                p->u.phys.force.y = 0.16344418f * p->u.phys.mass;
                p->u.phys.force.x = 0.001f * (-p->u.phys.vel.x * p->u.phys.mass) + p->u.phys.force.x;
                p->u.phys.force.y = 0.001f * (-p->u.phys.vel.y * p->u.phys.mass) + p->u.phys.force.y;
                p->u.phys.force.z = 0.001f * (-p->u.phys.vel.z * p->u.phys.mass) + p->u.phys.force.z;
                for (k = 0; k < 3; k++) {
                    c = p->color.v[k] + (s8)p->colorStep.v[k];
                    if (c < 0) {
                        c = 0;
                    } else if (c > 0xFF) {
                        c = 0xFF;
                    }
                    p->color.v[k] = c;
                    (&p->u.phys.accel.x)[k] = (&p->u.phys.force.x)[k] / p->u.phys.mass;
                    (&p->u.phys.vel.x)[k] += (&p->u.phys.accel.x)[k];
                    (&p->pos.x)[k] += (&p->u.phys.vel.x)[k];
                }
                c = p->color.v[k] + (s8)p->colorStep.v[k];
                if (c < 0) {
                    c = 0;
                } else if (c > 0xFF) {
                    c = 0xFF;
                }
                p->color.v[k] = c;
                if (p->u.phys.vel.y > 0.0f && p->pos.y >= e->u.t1.floorY) {
                    p->u.phys.vel.y = p->u.phys.vel.y * e->u.t1.bounce;
                    p->life--;
                }
                if (fabs(p->pos.x) > 300.0 || fabs(p->pos.z) > 300.0) {
                    p->life = 0;
                }
            }
            DrawParticleQuad(p, e->tex, lbl_80180010);
            count++;
        } else if (e->u.t1.spawnLeft != 0) {
            spread = lbl_803CB7FC;
            ang = (s32)(512.0f * (1.0f - spread) + (512.0f * spread * (f32)rand()) / 32767.0f);
            cosA = CosIdxB(ang);
            sinA = SinIdx(ang);
            r = rand();
            k = (rand() & 0xF) + 0x5A;
            p->u.phys.mass = 0.001f;
            p->pos.x = e->u.t1.pos.x;
            p->pos.y = e->u.t1.pos.y;
            p->pos.z = e->u.t1.pos.z;
            spd = (((e->u.t1.speed / 60.0f) * (f32)k) / 100.0f) / 0.001f;
            h = spd * cosA;
            v.y = -spd * sinA;
            v.x = h * CosIdxB(r);
            v.z = h * SinIdx(r);
            v.y = v.y + 0.16344418f;
            PSMTXMultVec(rotM, &v, &v);
            p->u.phys.vel.x = v.x;
            p->u.phys.vel.y = v.y;
            p->u.phys.vel.z = v.z;
            p->sizeX = e->u.t1.size;
            p->sizeY = e->u.t1.size;
            PCOLOR_SET(p->color, e->u.t1.color);
            p->colorStep.all = 0;
            p->life = 2;
            p->delay = r & lbl_803CB7F8;
            p->texIndex = 0xFF;
            count++;
        }
        p = p->next;
    } while (p != NULL);
    if (e->u.t1.spawnLeft > 0) {
        e->u.t1.spawnLeft--;
    }
    return count == 0;
}
#endif

// .text:0x800330CC size:0x1EC
void fn_800330CC(s32 n, u32 color, Vec* pos, Vec* dir, s32 spawnFrames, TexArchive* tex, f32 speed, f32 size) {
    Emitter* e = NewEmitter(fn_800328E0, 0x80, 0, n, 1, 1);
    if (e != NULL) {
        e->tex = tex;
        memcpy(&e->u.t1.pos, pos, sizeof(Vec));
        memcpy(&e->u.t1.dir, dir, sizeof(Vec));
        e->u.t1.speed = speed;
        e->u.t1.spawnLeft = spawnFrames;
        e->u.t1.bounce = -0.4f;
        e->u.t1.floorY = -0.0001f;
        e->u.t1.color = color;
        e->u.t1.size = size;
    }
}

// .text:0x800332B8 size:0x304
// NONMATCHING 80%: float register allocation; the original also stores yawMin/360*360 into out->x first (dead store)
#if NONMATCHING
void fn_800332B8(Vec* axis, Vec* out, f32 yawMin, f32 yawMax, f32 pitchMin, f32 pitchMax) {
    Mtx m;
    Vec cross;
    Vec ref;
    Vec axisCopy;
    f32 angle;
    Quaternion q;
    s32 yaw;
    s32 pitch;

    ref = lbl_800E6778;
    if (axis != NULL) {
        memcpy(&axisCopy, axis, sizeof(Vec));
        axis = &axisCopy;
    }
    yaw = (s32)(2048.0f * (yawMin / 360.0f) + 0.5f);
    if (yawMax != yawMin) {
        yaw += rand() % (s32)(2048.0f * ((yawMax - yawMin) / 360.0f) + 0.5f);
    }
    out->x = CosIdx(yaw);
    out->y = SinIdx(yaw);
    pitch = (s32)(2048.0f * (pitchMin / 360.0f) + 0.5f);
    if (pitchMax != pitchMin) {
        pitch += rand() % (s32)(2048.0f * ((pitchMax - pitchMin) / 360.0f) + 0.5f);
    }
    out->z = out->x * SinIdx(pitch);
    out->x = out->x * CosIdx(pitch);
    if (axis != NULL && PSVECMag(axis) != 0.0f) {
        angle = acos(PSVECDotProduct(&ref, axis));
        PSVECCrossProduct(&ref, axis, &cross);
        if (PSVECMag(&cross) != 0.0f) {
            C_QUATRotAxisRad(&q, &cross, angle);
            PSMTXQuat(m, &q);
            PSMTXMultVec(m, out, out);
        } else {
            PSVECScale(out, PSVECMag(axis), out);
        }
    }
}
#endif

// .text:0x800335BC size:0x30
f32 fn_800335BC(s32 angle) {
    s32 i = __abs(angle) & 0x7FF;
    if (i >= 0x401) {
        i = 0x800 - i;
    }
    return lbl_8017ED68[i];
}

// .text:0x800335EC size:0x34
f32 fn_800335EC(s32 angle) {
    s32 i = __abs(angle + 0x600) & 0x7FF;
    if (i >= 0x401) {
        i = 0x800 - i;
    }
    return lbl_8017ED68[i];
}

// .text:0x80033620 size:0x174
void fn_80033620(Emitter* e) {
    Vec v;
    Vec w;
    Particle tmp;
    Particle* p;
    Particle* q;
    Particle* best;
    Particle* pNext;
    Particle* bestNext;
    f32 bestZ;
    u32 i = 0;

    for (p = e->particles; p != NULL && e->count > i; p = p->next, i++) {
        q = p->next;
        if (p->delay <= 0 && p->life != 0) {
            PSMTXMultVec(lbl_8017FFE0, &p->pos, &v);
            bestZ = v.z;
            best = NULL;
            for (; q != NULL; q = q->next) {
                if (q->delay <= 0 && q->life != 0) {
                    PSMTXMultVec(lbl_8017FFE0, &q->pos, &w);
                    if (bestZ > w.z) {
                        best = q;
                        bestZ = w.z;
                    }
                }
            }
            if (best != NULL) {
                pNext = p->next;
                bestNext = best->next;
                tmp = *p;
                *p = *best;
                *best = tmp;
                p->next = pNext;
                best->next = bestNext;
            }
        }
    }
}

// .text:0x80033794 size:0x38
void fn_80033794(Particle* list) {
    FreeParticles(list);
}

// .text:0x800337CC size:0x90
Emitter* fn_800337CC(Emitter* e, s32 n, s32 strict) {
    s32 count = 0;
    Particle* p = lbl_803CBC74;
    Particle* last = NULL;
    if (e != NULL) {
        while (p != NULL && n != 0) {
            last = p;
            p = p->next;
            count++;
            n--;
        }
        if (strict && n != 0) {
            return NULL;
        }
        e->count = count;
        if (count != 0) {
            e->particles = lbl_803CBC74;
            lbl_803CBC74 = p;
            if (last != NULL) {
                last->next = NULL;
            }
        } else {
            e->particles = NULL;
        }
    }
    return e;
}

// .text:0x8003385C size:0xCC
void pitchingMachinePitching(u8 type) {
    Emitter* e = EMITTER_HEAD->next;
    while (e != NULL) {
        Emitter* found = e->type == type ? e : NULL;
        e = e->next;
        if (found != NULL) {
            FreeEmitter(found);
        }
    }
}

// .text:0x80033928 size:0x3C
s32 fn_80033928(u8 type) {
    Emitter* e;
    for (e = EMITTER_HEAD->next; e != NULL; e = e->next) {
        if (e->type == type) {
            return 1;
        }
    }
    return 0;
}

// .text:0x80033964 size:0x8C
void fn_80033964(Emitter* e) {
    FreeEmitter(e);
}

// .text:0x800339F0 size:0x34
Emitter* fn_800339F0(Emitter* after, u8 type) {
    return FindEmitter(after, type);
}

// .text:0x80033A24 size:0x134
Emitter* fn_80033A24(EmitterUpdateFn update, u8 priority, s32 unk14, s32 n, s32 strict, u8 type) {
    Emitter* e = fn_800337CC(lbl_803CBC80, n, strict);
    Emitter* at;
    if (e == NULL) {
        return NULL;
    }
    lbl_803CBC80 = lbl_803CBC80->next;
    e->update = update;
    e->priority = priority;
    e->type = type;
    e->active = 1;
    e->unk14 = unk14;
    e->next = NULL;
    e->prev = NULL;
    at = EMITTER_HEAD;
    while (at->next != NULL && at->next->priority < e->priority) {
        at = at->next;
    }
    e->next = at->next;
    if (e->next != NULL) {
        e->next->prev = e;
    }
    e->prev = at;
    at->next = e;
    return e;
}

// .text:0x80033B58 size:0x170
void fn_80033B58(TexArchive* arc, s32 idx, GXTexWrapMode wrapS, GXTexWrapMode wrapT) {
    LoadParticleTex(arc, idx, wrapS, wrapT);
}

// .text:0x80033CC8 size:0x29C
void fn_80033CC8(Particle* p, TexArchive* arc) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    TexImage* img;
    s32 tex = p->texIndex;
    Vec* corner;
    s32 i;

    if (arc == NULL) {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    } else {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
        img = &arc->entries[arc->entries[tex].index];
        if (img->tlut != NULL) {
            GXInitTexObjCI(&texObj, PTR32_GET(u8, img->data), img->width, img->height, img->format, GX_CLAMP, GX_CLAMP, GX_FALSE, 0);
            GXInitTlutObj(&tlutObj, PTR32_GET(void, img->tlut), img->tlutFormat, img->tlutEntries);
            GXLoadTlut(&tlutObj, GX_TLUT0);
        } else {
            GXInitTexObj(&texObj, PTR32_GET(u8, img->data), img->width, img->height, img->format, GX_CLAMP, GX_CLAMP, GX_FALSE);
        }
        GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, (f32)img->minLOD, (f32)img->maxLOD, img->lodBias, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&texObj, GX_TEXMAP1);
    }
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    corner = lbl_80180010;
    for (i = 0; i < 4; i++) {
        GXPosition3f32(p->pos.x + corner[i].x, p->pos.y + corner[i].y, p->pos.z + corner[i].z);
        GXColor1u32(PCOLOR_GET(p->color));
        GXTexCoord2f32(lbl_800F7860[p->uvFrame + i].u, lbl_800F7860[p->uvFrame + i].v);
    }
}

// .text:0x80033F64 size:0xD8
void fn_80033F64(f32 width, f32 height, f32 angleDeg) {
    Mtx m;
    Mtx rot;
    s32 i;
    f32 x1;
    f32 y0;
    f32 x0;
    f32 y1;

    x1 = 0.5f * width;
    x0 = 0.5f * -width;
    y0 = 0.5f * -height;
    y1 = 0.5f * height;
    lbl_80180010[0].z = 0.0f;
    lbl_80180010[0].x = x0;
    lbl_80180010[0].y = y0;
    lbl_80180010[1].x = x1;
    lbl_80180010[1].y = y0;
    lbl_80180010[1].z = 0.0f;
    lbl_80180010[2].x = x1;
    lbl_80180010[2].y = y1;
    lbl_80180010[2].z = 0.0f;
    lbl_80180010[3].x = x0;
    lbl_80180010[3].y = y1;
    lbl_80180010[3].z = 0.0f;
    PSMTXRotRad(rot, 'z', 0.017453292f * angleDeg);
    PSMTXConcat(lbl_8017FF78[0], rot, m);
    for (i = 0; i < 4; i++) {
        PSMTXMultVec(m, &lbl_80180010[i], &lbl_80180010[i]);
    }
}

// .text:0x8003403C size:0xB8
void fn_8003403C(f32 width, f32 height) {
    s32 i;
    f32 x1;
    f32 x0;
    f32 y0;
    f32 y1;

    x1 = 0.5f * width;
    x0 = 0.5f * -width;
    y0 = 0.5f * -height;
    y1 = 0.5f * height;
    lbl_80180010[0].z = 0.0f;
    lbl_80180010[0].x = x0;
    lbl_80180010[0].y = y0;
    lbl_80180010[1].x = x1;
    lbl_80180010[1].y = y0;
    lbl_80180010[1].z = 0.0f;
    lbl_80180010[2].x = x1;
    lbl_80180010[2].y = y1;
    lbl_80180010[2].z = 0.0f;
    lbl_80180010[3].x = x0;
    lbl_80180010[3].y = y1;
    lbl_80180010[3].z = 0.0f;
    for (i = 0; i < 4; i++) {
        PSMTXMultVec(lbl_8017FF78[0], &lbl_80180010[i], &lbl_80180010[i]);
    }
}

// .text:0x800340F4 size:0x2C
void fn_800340F4(Mtx m) {
    PSMTXCopy(lbl_8017FF78[0], m);
}

// .text:0x80034120 size:0x2C
void fn_80034120(Mtx m) {
    PSMTXCopy(lbl_8017FFE0, m);
}

// .text:0x8003414C size:0xD4
// NONMATCHING 74%: the original addresses these file-static bss objects off one base (lbl_8017EC00 + offset); needs the .bss split into this unit
#if NONMATCHING
void fn_8003414C(Mtx view) {
    s32 i;

    PSMTXCopy(view, lbl_8017FFE0);
    fn_800118AC(view, lbl_8017FF78[1]);
    PSMTXCopy(lbl_8017FF78[1], lbl_8017FF78[0]);
    lbl_8017FF78[0][2][3] = 0.0f;
    lbl_8017FF78[0][1][3] = 0.0f;
    lbl_8017FF78[0][0][3] = 0.0f;
    lbl_80180010[0].x = -0.5f;
    lbl_80180010[0].y = -0.5f;
    lbl_80180010[0].z = 0.0f;
    lbl_80180010[1].x = 0.5f;
    lbl_80180010[1].y = -0.5f;
    lbl_80180010[1].z = 0.0f;
    lbl_80180010[2].x = 0.5f;
    lbl_80180010[2].y = 0.5f;
    lbl_80180010[2].z = 0.0f;
    lbl_80180010[3].x = -0.5f;
    lbl_80180010[3].y = 0.5f;
    lbl_80180010[3].z = 0.0f;
    for (i = 0; i < 4; i++) {
        PSMTXMultVec(lbl_8017FF78[0], &lbl_80180010[i], &lbl_80180010[i]);
    }
}
#endif

// .text:0x80034220 size:0x30C
// NONMATCHING 82%: r3/r4 swapped in the pool-link loop, mr before the cos loop
#if NONMATCHING
void minigamesSetSomePointers(void) {
    s32 i;
    f32* t;

    lbl_803CBC78 = 1;
    memset(lbl_80180040, 0, sizeof(lbl_80180040));
    for (i = 0; i < 0x13FF; i++) {
        lbl_80180040[i].next = &lbl_80180040[i + 1];
    }
    lbl_803CBC74 = lbl_80180040;
    lbl_803CBC78 = 0;
    lbl_803CBC84.prev = NULL;
    lbl_803CBC84.next = NULL;
    memset(lbl_801F8040, 0, sizeof(lbl_801F8040));
    for (i = 0; i < 0xF; i++) {
        lbl_801F8040[i].next = &lbl_801F8040[i + 1];
    }
    lbl_803CBC80 = lbl_801F8040;
    t = lbl_8017ED68;
    i = 0;
    do {
        *t = cos((3.141592654 * i) / 1025.0);
        i++;
        t++;
    } while (i < 0x401);
    lbl_803CBC7C = 0;
}
#endif

// .text:0x8003452C size:0x39C
void minigamesGXStuff(void) {
    GXTexObj texObj;
    Emitter* e;
    Emitter* dead;
    s32 done;

    if (lbl_803CBC78 != 0) {
        lbl_803CBC78 = 0;
        e = lbl_803CBC84.next;
        while (e != NULL) {
            dead = e;
            e = e->next;
            FreeEmitter(dead);
        }
        lbl_803CBC84.next = NULL;
        return;
    }
    if (lbl_803CBC84.next == NULL) {
        return;
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    // 1 is the SDK GX_TG_MTX2x4 (GXEnum.h has the 2x4/3x4 names swapped)
    GXSetTexCoordGen2(GX_TEXCOORD0, (GXTexGenType)1, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetCullMode(GX_CULL_NONE);
    GXInitTexObj(&texObj, lbl_800F7840, 4, 4, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetProjection(fn_80052734(fn_8005268C())->proj, GX_PERSPECTIVE);
    GXLoadPosMtxImm(lbl_8017FFE0, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    SetFogNone();
    // done/dead deliberately carry over between iterations (as in the original)
    for (e = lbl_803CBC84.next; e != NULL;) {
        if (e->update != NULL) {
            done = e->update(e);
            if (done) {
                dead = e;
            }
        }
        e = e->next;
        if (done) {
            FreeEmitter(dead);
        }
    }
}

// .text:0x800348C8 size:0x304
// NONMATCHING 98.0%: extra mr for the cos table pointer
#if NONMATCHING
void minigamesSetSomePointers2(void) {
    s32 i;
    f32* t;

    memset(lbl_80180040, 0, sizeof(lbl_80180040));
    for (i = 0; i < 0x13FF; i++) {
        lbl_80180040[i].next = &lbl_80180040[i + 1];
    }
    lbl_803CBC74 = lbl_80180040;
    lbl_803CBC78 = 0;
    lbl_803CBC84.prev = NULL;
    lbl_803CBC84.next = NULL;
    memset(lbl_801F8040, 0, sizeof(lbl_801F8040));
    for (i = 0; i < 0xF; i++) {
        lbl_801F8040[i].next = &lbl_801F8040[i + 1];
    }
    lbl_803CBC80 = lbl_801F8040;
    t = lbl_8017ED68;
    i = 0;
    do {
        *t = cos((3.141592654 * i) / 1025.0);
        i++;
        t++;
    } while (i < 0x401);
    lbl_803CBC7C = 0;
}
#endif

// .text:0x80034BCC size:0x120
s32 fn_80034BCC(QuadState* q, Mtx unused) {
    SpaniObj* o;
    u8* col;
    u8* qcol = (u8*)&q->color;

    for (o = lbl_803CBC9C->unk8; o != NULL; o = o->unk4) {
        if (((SpaniObj*)o->parent)->animId == q->path[0] && o->unk72 == q->path[1]) {
            PSMTXCopy(q->mtx, o->mtx2);
            // TODO type: unk58/unk74 are RGBA colors in SpaniObj
            col = (u8*)&o->unk74;
            col[0] = (qcol[0] * ((u8*)&o->unk58)[0]) / 255;
            col[1] = (qcol[1] * ((u8*)&o->unk58)[1]) / 255;
            col[2] = (qcol[2] * ((u8*)&o->unk58)[2]) / 255;
            col[3] = (qcol[3] * ((u8*)&o->unk58)[3]) / 255;
            o->unkA8 = 1;
        }
    }
    return 0;
}

// .text:0x80034CEC size:0x134
void fn_80034CEC(SpaniGroup* g) {
    s32 base = g->u14.objIdx;
    s32 i;
    s32 dst;

    for (i = 0; i < g->u14.objCount; i++) {
        if (lbl_80371C30[base + i].obj != NULL) {
            lbl_80371C30[base + i].obj->flags = 0;
        }
    }
    dst = base;
    for (i += base; i < 0x360; i++, dst++) {
        lbl_80371C30[dst].obj = lbl_80371C30[i].obj;
        lbl_80371C30[dst].owner = lbl_80371C30[i].owner;
        if (lbl_80371C30[dst].owner != NULL) {
            lbl_80371C30[dst].owner->u14.objIdx = dst;
        }
    }
    for (i = dst; i < 0x360; i++) {
        lbl_80371C30[i].obj = NULL;
        lbl_80371C30[i].owner = NULL;
    }
}

// .text:0x80034E20 size:0x130
void fn_80034E20(SpaniGroup* g, SpaniDesc* descs) {
    SpaniDesc* d;
    SpaniSlot* base;
    s32 n = 0;
    s32 i;
    s32 k;
    SpaniObj* obj;
    s32 idx;

#ifdef TARGET_PC
    // Tables still declared as bytes hold big-endian SpaniDescs: swap them
    // in place the first time (see port_spani_descs_native).
    if (!port_spani_descs_native(descs)) {
        port_swap_spani_descs(descs);
    }
#endif
    for (i = 0; i < 0x360; i++) {
        if (lbl_80371C30[i].obj == NULL) {
            g->u14.objIdx = i;
            base = &lbl_80371C30[i];
            base->owner = g;
            break;
        }
    }
    d = descs;
    for (;;) {
        idx = n + i;
        if (d->type == 3) {
            break;
        }
        lbl_80371C30[idx].obj = fn_80034F50(d);
        obj = lbl_80371C30[idx].obj;
        if (d->parent == 0xFF || n == 0) {
            obj->parent = NULL;
        } else {
            obj->parent = base[d->parent].obj;
            obj->unk4 = ((SpaniObj*)obj->parent)->unk8;
            ((SpaniObj*)obj->parent)->unk8 = obj;
        }
        for (k = 0; k < SPANI_TEX_OVERRIDE_COUNT; k++) {
            obj->texOverride[k] = 0xFFFF;
        }
        d++;
        n++;
    }
    g->u14.objCount = n;
}
