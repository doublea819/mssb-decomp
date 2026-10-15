#ifndef __MAIN_FILE_800263FC_H__
#define __MAIN_FILE_800263FC_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "main/file_80024184.h"
#include "main/file_80034F50.h"
#include "main/file_80022DAC.h"

// Particle effect system: a pool of 0x1400 particles (lbl_80180040) and
// 16 emitters (lbl_801F8040), each emitter owning a singly linked list of
// particles and sitting in a priority-sorted doubly linked active list
// (head lbl_803CBC84).


struct ActorObject;

// Particle colours are written and read both as one RGBA word (0xRRGGBBAA,
// what GXColor1u32 takes and what the parameter tables hold) and as bytes
// (color.c.a / color.v[3] = alpha, v[k] += colorStep.v[k]). On GameCube the
// two views agree. On a little-endian host the word's alpha is byte 0 while
// c.a/v[3] is its red byte, so effects whose alpha is animated through the
// byte views (fire: 0xFFFFFF00 + per-frame c.a) never become visible. The
// port keeps the GameCube byte order (r, g, b, a) in memory and converts at
// the word accesses.
#ifdef TARGET_PC
static inline u32 port_rgba_get(const void* col) {
    const u8* b = (const u8*)col;
    return ((u32)b[0] << 24) | ((u32)b[1] << 16) | ((u32)b[2] << 8) | (u32)b[3];
}
static inline void port_rgba_set(void* col, u32 rgba) {
    u8* b = (u8*)col;
    b[0] = (u8)(rgba >> 24);
    b[1] = (u8)(rgba >> 16);
    b[2] = (u8)(rgba >> 8);
    b[3] = (u8)rgba;
}
#define PCOLOR_WORD(col, word) port_rgba_get(&(col))
#define PCOLOR_SET(col, x) port_rgba_set(&(col), (u32)(x))
#else
#define PCOLOR_WORD(col, word) ((col).word)
#define PCOLOR_SET(col, x) ((col).rgba = (x))
#endif
#define PCOLOR_GET(col) PCOLOR_WORD(col, rgba)

typedef struct Particle {
    /* 0x00 */ struct Particle* next;
    /* 0x04 */ Vec pos;
    /* 0x10 */ union {
        struct {
            /* 0x10 */ Vec vel;
            /* 0x1C */ Vec accel;
            /* 0x28 */ Vec force;
            /* 0x34 */ f32 mass;
        } phys;
        struct {
            /* 0x10 */ f32 unk10;
            /* 0x14 */ f32 unk14;
            /* 0x18 */ s32 unk18;
            /* 0x1C */ s32 unk1C;
            /* 0x20 */ s32 unk20;
            /* 0x24 */ u8 pad24[0x38 - 0x24];
        } t6;
        struct {
            /* 0x10 */ Vec dir;
            /* 0x1C */ Vec vel;
            /* 0x28 */ f32 sizeX;
            /* 0x2C */ f32 sizeY;
            /* 0x30 */ f32 sizeXDelta; // over the whole life
            /* 0x34 */ f32 sizeYDelta;
        } tB;
        struct {
            /* 0x10 */ Vec prev;    // previous position (tail end)
            /* 0x1C */ f32 width;
            /* 0x20 */ s32 id;
            /* 0x24 */ s32 alphaMax;
            /* 0x28 */ s32 maxLife;
            /* 0x2C */ u8 pad2C[0x38 - 0x2C];
        } trail;
        struct {
            /* 0x10 */ Vec vel;
            /* 0x1C */ f32 unk1C;
            /* 0x20 */ f32 unk20;
            /* 0x24 */ f32 unk24;
            /* 0x28 */ f32 unk28;
            /* 0x2C */ s32 unk2C;
            /* 0x30 */ s32 unk30;
            /* 0x34 */ f32 unk34;
        } t5;
        struct {
            /* 0x10 */ f32 dSize1;
            /* 0x14 */ f32 dSize2;
            /* 0x18 */ s16 dAlpha1;
            /* 0x1A */ s16 dAlpha2;
            /* 0x1C */ s16 phase1; // frames of the first phase
            /* 0x1E */ s16 life0;
        } tE;
        struct {
            /* 0x10 */ f32* pos; // followed position (game.rel rep_3880)
            /* 0x14 */ f32* rot; // followed rotation, degrees
            /* 0x18 */ s16 id;   // owner id (fn_3_154238 kills by id)
        } follow;
        struct {
            /* 0x10 */ f32 dSizeY1;
            /* 0x14 */ f32 dSizeY2;
            /* 0x18 */ f32 dSizeX1;
            /* 0x1C */ f32 dSizeX2;
            /* 0x20 */ s16 dAlpha1;
            /* 0x22 */ s16 dAlpha2;
            /* 0x24 */ s16 phase1;
            /* 0x26 */ s16 life0;
        } tEsub;
    } u;
    /* 0x38 */ f32 sizeX;
    /* 0x3C */ f32 sizeY;
    /* 0x40 */ union {
        u32 rgba;
        GXColor c;
        u8 v[4];
    } color;
    /* 0x44 */ union {
        u32 all;
        u8 v[4]; // signed steps added to color every frame
        struct {
            u8 alpha0;
            u8 pad;
            s16 maxLife;
        } tB;
    } colorStep;
    /* 0x48 */ s16 delay;       // frames before the particle appears
    /* 0x4A */ s16 life;        // frames left (0: dead)
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ u8 texIndex;
    /* 0x4E */ u8 uvFrame;
    /* 0x4F */ u8 uvOrder;      // 2 bits per corner: index into lbl_800F78C0
    /* 0x50 */ f32 dSize;  // type 15: size change per frame
    /* 0x54 */ s32 dAlpha; // type 15: alpha change per frame
    /* 0x58 */ u8 unk58[0x60 - 0x58];
} Particle; // size 0x60

struct Emitter;
typedef s32 (*EmitterUpdateFn)(struct Emitter* e); // returns nonzero when finished

typedef struct Emitter {
    /* 0x00 */ struct Emitter* prev;
    /* 0x04 */ struct Emitter* next;
    /* 0x08 */ EmitterUpdateFn update; // NULL: emitter is free
    /* 0x0C */ Particle* particles;
    /* 0x10 */ TexArchive* tex;
#ifdef TARGET_PC // bitfields in MWCC (big-endian) bit order
    /* 0x14 */ u16 count : 12;
    /* 0x14 */ u16 unk14 : 4;
#else
    /* 0x14 */ u16 unk14 : 4;
    /* 0x14 */ u16 count : 12;
#endif
    /* 0x16 */ u8 priority;
#ifdef TARGET_PC // bitfields in MWCC (big-endian) bit order
    /* 0x17 */ u8 type : 7;
    /* 0x17 */ u8 active : 1;
#else
    /* 0x17 */ u8 active : 1;
    /* 0x17 */ u8 type : 7;
#endif
    /* 0x18 */ union {
        struct {
            /* 0x18 */ Vec pos;       // spawn position
            /* 0x24 */ Vec dir;       // spray direction
            /* 0x30 */ f32 speed;
            /* 0x34 */ s32 spawnLeft; // frames left in which dead particles respawn
            /* 0x38 */ f32 bounce;    // vel.y multiplier at the floor
            /* 0x3C */ f32 floorY;
            /* 0x40 */ u32 color;
            /* 0x44 */ f32 size;
        } t1;
        struct {
            /* 0x18 */ u8 unk18;
        } t5;
        struct {
            /* 0x18 */ Vec* target;   // particles are pulled towards *target
            /* 0x1C */ f32 intensity; // scales alpha; <= 0 hides the emitter
            /* 0x20 */ s16 texIndex;
        } attract;
        struct {
            /* 0x18 */ Particle* sub; // second particle list (ring around the center)
            /* 0x1C */ u16 subCount;
        } tE;
        struct {
            /* 0x18 */ struct {
                Vec min;
                Vec max;
            } boxes[2]; // particles entering a box stop

            /* 0x48 */ void* unk48; // ParticleParams5* sparks (fn_80028628), or NULL
            /* 0x4C */ u8 unk4C;
            /* 0x4D */ u8 unk4D;
            /* 0x4E */ u8 unk4E;
            /* 0x4F */ u8 unk4F;
            /* 0x50 */ s32 unk50;
            /* 0x54 */ u8 unk54;
            /* 0x55 */ u8 unk55;
            /* 0x56 */ u8 unk56;
        } t4;
        struct {
            /* 0x18 */ Vec pos;
            /* 0x24 */ Vec prevPos;
            /* 0x30 */ s32 fadeLife; // particles start fading out at this life
        } t9;
        struct {
            /* 0x18 */ Vec start;
            /* 0x24 */ Vec end;
            /* 0x30 */ Vec dir;
            /* 0x3C */ s32 texIndex;
            /* 0x40 */ u16 unk40;
        } t10;
        struct {
#ifdef TARGET_PC
            // 4 bytes as on the GameCube: fn_3_151204 also writes t1.pos.y..dir.x (union + 4) for this
            // emitter, which an 8-byte pointer would overlap (Wall Ball crash).
            /* 0x18 */ PTR32(struct ActorObject) obj;
#else
            /* 0x18 */ struct ActorObject* obj; // actor whose bones the particles follow (game.rel rep_3880)
#endif
        } follow;
        struct {
            /* 0x18 */ Vec origin; // game.rel rep_3880 sweep (fn_3_14B53C)
            /* 0x24 */ Vec pos;
            /* 0x30 */ f32 len;
            /* 0x34 */ s16 total;
            /* 0x36 */ s16 left;
        } sweep;
        struct {
            /* 0x18 */ s32 index; // game.rel rep_3880 (fn_3_157AC4)
            /* 0x1C */ s32 count;
        } seq;
        struct {
            /* 0x18 */ s32 _18;
            /* 0x1C */ u8 _1C[4];
            /* 0x20 */ void* owner; // game: the stadium object the burst belongs to (sta_c2)
            /* 0x24 */ u8 _24;
            /* 0x25 */ u8 drawn;    // game: set once drawn this frame (sta_c2 fn_3_CDFA4)
        } game;
        /* 0x18 */ f32 f[0x12]; // per-type parameters, see fn_80027918
        /* 0x18 */ u8 raw[0x48];
    } u;
} Emitter; // size 0x60

// u/v texel coordinates of one quad corner (lbl_800F7860).
typedef struct UVCoord {
    /* 0x0 */ u16 u;
    /* 0x2 */ u16 v;
} UVCoord;

// Spawn parameters of the spark/trail emitter (type 9). Float values are
// stored as fixed point (x100000); angles in degrees.
typedef struct ParticleParams9 {
    /* 0x00 */ TexArchive* tex;
    /* 0x04 */ s32 texIndex;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 life;
    /* 0x10 */ s32 sizeMin;
    /* 0x14 */ s32 sizeMax;
    /* 0x18 */ s32 speed;
    /* 0x1C */ s32 delayRange;
    /* 0x20 */ s32 lifeRange;
    /* 0x24 */ s32 yawMin;
    /* 0x28 */ s32 yawMax;
    /* 0x2C */ s32 pitchMin;
    /* 0x30 */ s32 pitchMax;
    /* 0x34 */ s32 fadeLife;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 angleMin;
    /* 0x44 */ s32 angleMax;
} ParticleParams9;

typedef struct TexCoordF {
    /* 0x0 */ f32 s;
    /* 0x4 */ f32 t;
} TexCoordF;

// Spawn parameters of the burst emitter (type 11). Float values are fixed
// point (x100000).
typedef struct ParticleParamsB {
    /* 0x00 */ TexArchive* tex;
    /* 0x04 */ s32 texIndex;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 instant;  // particles that start without delay
    /* 0x10 */ s32 delayMax;
    /* 0x14 */ s32 lifeMin;
    /* 0x18 */ s32 lifeMax;
    /* 0x1C */ s32 speedMin;
    /* 0x20 */ s32 speedMax;
    /* 0x24 */ s32 velMin;
    /* 0x28 */ s32 velMax;
    /* 0x2C */ s32 sizeXMin;
    /* 0x30 */ s32 sizeXMax;
    /* 0x34 */ s32 sizeYMin;
    /* 0x38 */ s32 sizeYMax;
    /* 0x3C */ s32 endXMin;
    /* 0x40 */ s32 endXMax;
    /* 0x44 */ s32 endYMin;
    /* 0x48 */ s32 endYMax;
    /* 0x4C */ u32 color;
} ParticleParamsB;

#include "main/particle_params5.h" // ParticleParams5

// Spawn parameters of the beam emitter (type 8): count pairs of particles
// placed along a direction. Fixed point x100000.
typedef struct ParticleParams8 {
    /* 0x00 */ TexArchive* tex;
    /* 0x04 */ s32 texIndex;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 taper;     // last steps shrink towards sizeMin
    /* 0x10 */ s32 sizeMax;
    /* 0x14 */ s32 sizeMin;
    /* 0x18 */ s32 length;
    /* 0x1C */ s32 offset;
    /* 0x20 */ u32 gray;      // color = gray, gray, gray, 0xFF
    /* 0x24 */ s32 texIndex2[1]; // count entries
} ParticleParams8;

// Spawn parameters of the type-4 trails (fn_80028628). Fixed point x100000.
typedef struct ParticleParams4 {
    /* 0x00 */ TexArchive* tex;
    /* 0x04 */ s32 texIndex;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
} ParticleParams4;

// Type-4 trail: each logical particle is a head node followed by
// extraNodes extension nodes, all taken from the particle pool (the same
// memory as Particle, viewed differently).
typedef struct TrailHead {
    /* 0x00 */ Particle* next;
    /* 0x04 */ struct TrailHead* last; // last node of this particle's chain
    /* 0x08 */ Vec hist[4];            // recent positions (ring, histIdx)
    /* 0x38 */ f32 unk38;
    /* 0x3C */ union {
        u32 rgba;
        u8 v[4];
    } color;
    /* 0x40 */ Vec vel;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 unk52;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ u8 unk56;
    /* 0x57 */ u8 extraNodes;
    /* 0x58 */ u8 histIdx;
    /* 0x59 */ u8 extIdx;
    /* 0x5A */ u8 histMax;
    /* 0x5B */ u8 histCount;
    /* 0x5C */ u8 pad5C[4];
} TrailHead;

typedef struct TrailExt {
    /* 0x00 */ Particle* next;
    /* 0x04 */ struct TrailExt* prev; // previous node of the chain
    /* 0x08 */ Vec ext[7];            // older positions (ring, extIdx)
    /* 0x5C */ u8 pad5C[4];
} TrailExt;

// Shape used by fn_80028628: a header followed by count entries.
typedef struct TrailShapeEntry {
    /* 0x0 */ u16 color; // RGBA4444, or index into the palette
    /* 0x2 */ u16 x;
    /* 0x4 */ u16 y;
    /* 0x6 */ u16 z;
} TrailShapeEntry;

typedef struct TrailShape {
    /* 0x0 */ u16 hasZ : 1;
    /* 0x0 */ u16 count : 15;
    /* 0x2 */ u16 sizeX; // coordinates are centered on size / 2
    /* 0x4 */ u16 sizeY;
    /* 0x6 */ u16 sizeZ;
    /* 0x8 */ TrailShapeEntry entries[1]; // count entries
} TrailShape;

// Spark particle (type 12): a different view of a Particle pool entry.
typedef struct SparkParticle {
    /* 0x00 */ Particle* next;
    /* 0x04 */ Vec pos;
    /* 0x10 */ Vec vel;
    /* 0x1C */ Vec accel;
    /* 0x28 */ f32 angle;
    /* 0x2C */ f32 spin;
    /* 0x30 */ f32 size;
    /* 0x34 */ union {
        u32 rgba;
        u8 v[4];
    } color;
    /* 0x38 */ s16 delay;
    /* 0x3A */ s16 life;
    /* 0x3C */ u8 texIndex;
    /* 0x3D */ s8 fadeIn;
    /* 0x3E */ s8 fadeOut;
    /* 0x3F */ u8 fadeStart; // fade out when life drops below this
    /* 0x40 */ u8 alphaMax;
    /* 0x41 */ u8 additive;
    /* 0x42 */ u8 zTest;
    /* 0x43 */ u8 pad43[0x60 - 0x43];
} SparkParticle;

typedef struct ParticleParamsC {
    /* 0x00 */ TexArchive* tex;
    /* 0x04 */ s32 texIndex;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
} ParticleParamsC;

// Spawn parameters of the type-14 (ground ring) emitter.
typedef struct ParticleParamsE {
    /* 0x00 */ TexArchive* tex;
    /* 0x04 */ s32 subTexIndex;
    /* 0x08 */ s32 subCount;
    /* 0x0C */ s32 subLife;
    /* 0x10 */ s32 subPhase1;
    /* 0x14 */ f32 subSizeY[3]; // start, end of phase 1, end
    /* 0x20 */ f32 subSizeX[3];
    /* 0x2C */ s32 subAlpha[3];
    /* 0x38 */ f32 radius;
    /* 0x3C */ f32 angle0;      // degrees
    /* 0x40 */ f32 angleSpan;   // degrees
    /* 0x44 */ s32 texIndex;
    /* 0x48 */ s32 count;
    /* 0x4C */ s32 life;
    /* 0x50 */ s32 phase1;
    /* 0x54 */ f32 size[3];
    /* 0x60 */ s32 alpha[3];
    /* 0x6C */ s32 unk6C;
} ParticleParamsE; // size: 0x70 (template: lbl_80108D48)

// Streak particle (type 10): flies from start towards end in three eased
// phases. A different view of a Particle pool entry.
typedef struct StreakParticle {
    /* 0x00 */ Particle* next;
    /* 0x04 */ Vec offset;
    /* 0x10 */ Vec dir;
    /* 0x1C */ f32 sizeX;
    /* 0x20 */ f32 sizeY;
    /* 0x24 */ f32 lenA;
    /* 0x28 */ f32 lenB;
    /* 0x2C */ f32 reach;
    /* 0x30 */ union {
        u32 rgba;
        GXColor c;
    } color;
    /* 0x34 */ f32 spin;
    /* 0x38 */ u16 uvOrder; // 4 bits per corner
    /* 0x3A */ u16 delay;
    /* 0x3C */ u16 rem[3];  // frames left in each phase
    /* 0x42 */ u16 dur[3];
    /* 0x48 */ u16 fade;
    /* 0x4A */ u8 pad4A[0x60 - 0x4A];
} StreakParticle;

typedef struct ParticleParamsA {
    /* 0x00 */ TexArchive* tex;
    /* 0x04 */ s32 texIndex;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
} ParticleParamsA;

// Spawn parameters of the type-15 (smoke) emitter.
typedef struct ParticleParamsF {
    /* 0x00 */ TexArchive* tex;
    /* 0x04 */ s32 texIndex;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 life;
    /* 0x10 */ Vec vel;
    /* 0x1C */ f32 velScale;
    /* 0x20 */ Vec accel;
    /* 0x2C */ f32 accelScale;
    /* 0x30 */ f32 size0;
    /* 0x34 */ f32 size1;
    /* 0x38 */ s32 alpha0;
    /* 0x3C */ s32 alpha1;
    /* 0x40 */ Vec pos;
    /* 0x4C */ u8 r;
    /* 0x4D */ u8 g;
    /* 0x4E */ u8 b;
} ParticleParamsF;

// Particle pulled towards a target point (fn_80026E58). A different view
// of a Particle pool entry.
typedef struct AttractParticle {
    /* 0x00 */ Particle* next;
    /* 0x04 */ Vec pos;
    /* 0x10 */ f32 t;     // fraction of the distance kept each frame
    /* 0x14 */ f32 dt;
    /* 0x18 */ f32 size;
    /* 0x1C */ union {
        u32 rgba;
        GXColor c;
    } color;
    /* 0x20 */ s16 life;
    /* 0x22 */ s16 life0;
    /* 0x24 */ s16 delay;
    /* 0x26 */ s16 fadeIn;
    /* 0x28 */ s16 fadeOut;
    /* 0x2A */ u8 alphaMax;
    /* 0x2B */ u8 pad2B[0x60 - 0x2B];
} AttractParticle;

typedef struct ParticleParamsAttract {
    /* 0x00 */ TexArchive* tex;
    /* 0x04 */ s32 texIndex;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
} ParticleParamsAttract;

// Queue task that flashes the stadium lights (fn_8002852C).
typedef struct LightFlashTask {
#ifdef TARGET_PC
    SCENE_TASK_VIEW_HEAD // SceneTask head (main/scene_task.h)
    StadiumLight light;
#else
    /* 0x00 */ u8 unk0[0x14];
    /* 0x14 */ StadiumLight light;
#endif
    /* 0x1E */ u8 r;
    /* 0x1F */ u8 g;
    /* 0x20 */ u8 b;
    /* 0x21 */ u8 alpha;
    /* 0x22 */ u8 repeat;
    /* 0x23 */ u8 timer;
    /* 0x24 */ u8 duration;
    /* 0x25 */ u8 pad25;
} LightFlashTask;

// Head of the active emitter list; aliases the prev/next of an Emitter.
typedef struct EmitterHead {
    /* 0x0 */ struct Emitter* prev;
    /* 0x4 */ struct Emitter* next;
} EmitterHead;

// Spawn template copied from lbl_800F787C.
typedef struct ParticleParams {
    /* 0x00 */ TexArchive* tex;
    /* 0x04 */ s32 texIndex;
    /* 0x08 */ s32 size;   // x100000
    /* 0x0C */ s32 unkC;   // x100000
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 life;
    /* 0x18 */ s32 unk18[(0x44 - 0x18) / 4];
} ParticleParams; // size 0x44

typedef struct ParticleSortEntry {
    /* 0x0 */ Particle* p;
    /* 0x4 */ f32 z;
} ParticleSortEntry;

void fn_8002BC84(Emitter* e, Vec* pos, Vec* dir, ParticleParams5* prm);
void fn_8002C2D0(Vec* pos, Vec* dir, ParticleParams5* prm);
s32 fn_800263FC(Emitter* e);
void fn_80026998(ParticleParamsF* prm);
s32 fn_80026E58(Emitter* e);
void fn_80027300(Emitter* e, Vec* center, Vec* target, ParticleParamsAttract* prm, f32 radius);
void fn_80027674(Vec* center, Vec* target, ParticleParamsAttract* prm, u8 type, f32 radius);
void fn_8002852C(void);
u8 fn_8002A85C(Emitter* e, Particle* p);
u8 fn_8002AC68(Emitter* e, Particle* p);
s32 fn_8002B014(Emitter* e);
void fn_8002B400(Emitter* e, ParticleParamsE* prm, Vec* pos);
void fn_8002B7F8(Vec* pos, ParticleParamsE* prm, u8 withSub);
s32 fn_80028F48(Emitter* e);
void fn_8002955C(Vec* pos, Vec* axis, ParticleParamsC* prm);
void fn_800297F0(Emitter* e, Vec* pos, Vec* axis, ParticleParamsC* prm);
void fn_80028628(Vec* from, Vec* to, ParticleParams4* prm, TrailShape* shape, u32* palette, struct ParticleParams5* spark, s32 flash); // spark: trail sparks (ParticleParams5*), may be NULL
s32 fn_8002C56C(Emitter* e);
void fn_8002CDD0(Vec* end);
void fn_8002CE4C(Vec* start, Vec* end, ParticleParamsA* prm);
s32 fn_8002D82C(Emitter* e);
void fn_8002DC68(Vec* pos);
void fn_8002DCE4(Vec* from, Vec* to, ParticleParams9* prm);
s32 fn_8002ECA0(Emitter* e);
s32 fn_8002F1AC(Vec* pos, s32 id);
void fn_8002F258(Vec* pos, s32 id, ParticleParams* prm);
void fn_8002F5F4(Vec* pos, Vec* dir, ParticleParams8* prm);
s32 fn_8002F9FC(Emitter* e);
void fn_8002FDB8(Emitter* e, Vec* pos, Vec* dir, Vec* velScale, ParticleParams5* prm);
void fn_80030470(Vec* pos, Vec* dir, Vec* velScale, ParticleParams5* prm, u8 type);
void fn_80030720(Emitter* e, Vec* pos, Vec* dir, ParticleParams5* prm);
void fn_80030D88(Vec* pos, Vec* dir, ParticleParams5* prm, u8 type);
void fn_800317C4(Emitter* e, Vec* pos, ParticleParams5* prm);
void fn_80031CA4(Vec* pos, ParticleParams5* prm);
Particle* fn_80031F34(Particle* list, s32 n);
s32 fn_80032038(const void* a, const void* b);
f32 fn_800335BC(s32 angle);
f32 fn_800335EC(s32 angle);
s32 fn_800328E0(Emitter* e);
void fn_800330CC(s32 n, u32 color, Vec* pos, Vec* dir, s32 spawnFrames, TexArchive* tex, f32 speed, f32 size);
void fn_8002A1CC(Vec* pos, ParticleParamsB* prm);
void fn_80032064(Vec* pos, ParticleParamsB* prm);
void fn_80032284(Vec* pos);
void fn_800324EC(u16 anim, s32 a, s32 b, ParticleParamsB* prm);
void fn_80033620(Emitter* e);
void fn_80033794(Particle* list);
Emitter* fn_800337CC(Emitter* e, s32 n, s32 strict);
void pitchingMachinePitching(u8 type);
void fn_80033964(Emitter* e);
Emitter* fn_80033A24(EmitterUpdateFn update, u8 priority, s32 unk14, s32 n, s32 strict, u8 type);
s32 fn_80033928(u8 type);
Emitter* fn_800339F0(Emitter* after, u8 type);
void fn_80027918(u8 type, f32 v);
void fn_800332B8(Vec* axis, Vec* out, f32 yawMin, f32 yawMax, f32 pitchMin, f32 pitchMax);
void fn_80033B58(TexArchive* arc, s32 idx, GXTexWrapMode wrapS, GXTexWrapMode wrapT);
void fn_80033CC8(Particle* p, TexArchive* arc);
void fn_80033F64(f32 width, f32 height, f32 angleDeg);
void fn_8003403C(f32 width, f32 height);
void fn_800340F4(Mtx m);
void fn_80034120(Mtx m);
void minigamesSetSomePointers(void);
void minigamesSetSomePointers2(void);
void fn_8003414C(Mtx view);

#include "main/scene_task.h" // SpaniGroup

// lbl_80371C30 entries.
typedef struct SpaniSlot {
    /* 0x0 */ SpaniObj* obj;
    /* 0x4 */ SpaniGroup* owner;
} SpaniSlot;

struct QuadState;
// QuadCallback (main/file_8000BA3C.h): copies the quad's matrix and colour to the attached sprites
// whose parent anim id and tag match q->path[0] and q->path[1].
s32 fn_80034BCC(struct QuadState* q, Mtx unused);
void fn_80034CEC(SpaniGroup* g);
void fn_80034E20(SpaniGroup* g, SpaniDesc* descs);

#endif
