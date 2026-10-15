#include "main/file_80011640.h"
#include "main/file_80021308.h"
#include "main/file_800A6870.h"
#include "Dolphin/mtx.h"
#include "Dolphin/stl.h"
#include "Dolphin/GX/GXTypes.h"
#include "Dolphin/gx.h"
#include "math.h"
#include "C3/anim.h"
#include "C3/actor.h"
#include "main/file_800B2C44.h"

// Globals owned by other units (only the fields used here).
typedef struct GameSettingsView {
    /*0x00*/ u8 _00[0x6];
    /*0x06*/ u8 _06;
    /*0x07*/ u8 GameModeSelected;
    /*0x08*/ u8 _08;
    /*0x09*/ u8 StadiumID;
    /*0x0A*/ u8 _0A[0x4];
    /*0x0E*/ u8 _0E;
    /*0x0F*/ u8 _0F[0x2];
    /*0x11*/ u8 minigamesEnabled;
    /*0x12*/ u8 _12[0x54 - 0x12];
    /*0x54*/ u8 _54;
} GameSettingsView;



// Camera returned by fn_80052734.
typedef struct CameraView {
    /*0x00*/ Mtx44 proj;
    /*0x40*/ Mtx view;
    /*0x70*/ Vec eye;
    /*0x7C*/ Vec target;
    /*0x88*/ Vec up;
} CameraView;

// Camera description handed to the shadow renderer.
typedef struct ShadowView {
    /*0x00*/ Vec eye;
    /*0x0C*/ Vec up;
    /*0x18*/ Vec target;
    /*0x24*/ u8 _24[0x1C];
    /*0x40*/ Mtx view;
    /*0x70*/ u8 _70[0xE4 - 0x70];
} ShadowView; // size: 0xE4


extern GameSettingsView g_d_GameSettings;
extern AramLoader lbl_803716B8; // main/file_80021308.h
extern DiskFileEntry* lbl_803CB790;
extern u32 lbl_803CBBF0;
extern CharLoadTask* lbl_803CC1B8;
extern CharPart lbl_80118220[13];

typedef struct RosterEntry {
    /*0x00*/ u8 _00[0x24];
    /*0x24*/ s16 charId;
    /*0x26*/ u8 _26;
    /*0x27*/ u8 _27;
    /*0x28*/ u8 _28[0xA0 - 0x28];
} RosterEntry; // size: 0xA0

extern RosterEntry inMemRoster[2][9];

extern LightPos lbl_80367318[4];
extern StadiumLights lbl_800F7478[];
extern u8 lbl_803CBC3C[4];
extern DiskFileEntry lbl_800EE910[2];

extern void fn_80023B90(LightSrc* src, LightPos* dst);
// fn_800BEBCC takes its Vec by value. The PPC ABI passes a pointer to a caller-made copy,
// and these matched callers make that copy themselves (dir2 = dir), so the matching build
// passes the copy's address; the port passes the value.
#if NONMATCHING
#define VEC_ARG(v) (v)
typedef Vec VecArg;
#else
#define VEC_ARG(v) (&(v))
typedef Vec* VecArg;
#endif
extern void fn_800BEBCC(u8 index, VecArg dir);
extern void fn_800B2C10(GameActor* model, u16 joint, Vec* out);
extern void fn_800B2C44(GameActor* model, u16 joint, Vec* out);
extern void convertTextureHeader(void* textures);
extern void convertGeometryAndSknHeader(void* geo, void* skn);
struct GQRValueGroups;
extern void fn_800BD190(struct GQRValueGroups* groups, void* textures);
extern void fn_8002399C(ActorObject* slot, s32 modelIndex, u16 index, void* layout, void* bank, void* skn);
extern void fn_800B2B74(GameActor* model, u16 joint);
extern void fn_800B2B54(GameActor* model, u16 joint, s32 arg);
extern struct DODisplayObj* fn_800B2BA8(GameActor* model, u16 joint, GameActor* src, u16 srcJoint);
extern void fn_800B2C08(GameActor* model, u16 joint);
extern void fn_800BD548(ActorObject* slot, s32 count, ...);
extern s32 fn_80063010(CharActor* actor, ActorObject* slot);
extern s32 fn_8004B7B4(CharActor* actor, ActorObject* slot);
extern s32 fn_8004BD6C(CharActor* actor, ActorObject* slot);
extern void* fn_80052634(CharActor* actor, ActorObject* slot);
extern s32 fn_80062ED4(CharActor* actor, ActorObject* slot);
extern void fn_800238E0(ActorObjectTable* list, u8 first, u8 last, void* layout);
extern void OSPanic(const char* file, int line, const char* msg, ...);
extern u8 lbl_803CB7B4[8];
extern u8 lbl_803CB7C4[4];
extern s16 lbl_800EEAAC[];
extern CharPart* lbl_803CBC10;
extern u8 lbl_803CBC14;
extern u8 lbl_803CBC15;
extern void* _OSAllocFromHeap(s32 heap, u32 size);
extern void fn_800BD2DC(void);
extern void fn_800BD2CC(s32 channel, GXColor color);
extern void LITAlloc(void** light);
extern void LITInitAttn(void* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);
extern void LITInitPos(void* light, f32 x, f32 y, f32 z);
extern void LITInitColor(void* light, u32* color);
extern void fn_800B4CA0(GameActor* model, f32 v);
extern void fn_800B4C04(GameActor* model, f32 v);
extern void Set_FUN_800b2b6c(GameActor* model, void* p);
extern void fn_800BDA24(ActorObject* slot);
extern s32 fn_800527BC(void);
extern CameraView* fn_80052734(u16 index);
extern s32 fn_8003A538(void);
extern void fn_8003A4C8(void);
extern u16 fn_8005268C(void);
extern void fn_800BD1E8(void (*callback)(Mtx m, s32* stage, s32* coord, s32* map, u8* numTevStages, u8* numTexGens));
extern u8 GetDrawShadows(void);
extern void DrawShadows(u8 enable);
extern void fn_800BEC00(s32 reverse);
extern void fn_800BF058(void (*draw)(ActorObject*, Mtx));
extern void fn_800BE09C(ActorObjectTable* list, ShadowView* view);
extern void fn_800BDFE0(ActorObjectTable* list);
extern void fn_800BDEA0(void);
extern void (*lbl_803CBBF4)(void);
extern DiskFileEntry* lbl_803CB794;
extern void* lbl_803CBC30;
extern u8 lbl_803CBC34[8];
extern s16 lbl_800EEB18[54];
extern ActorObjectTable* fn_80023AA4(void);
extern void fn_80023B04(s32 count);
extern DiskFileEntry* lbl_803CB7A8;
extern u8* lbl_803CBC24;
// lbl_800EE930: trail model file descriptor followed by joint mirror pair
// lists (0xFFFF-terminated u16 pairs).
typedef struct ModelData {
    /*0x00*/ DiskFileEntry trailFile;
    /*0x10*/ u8 _10[0x20];
    /*0x30*/ u16 mirrorPairs[0x1C];
    /*0x68*/ u16 mirrorPairs41[0xC];
    /*0x80*/ u16 mirrorPairs16[0x54];
} ModelData; // size: 0x128

extern ModelData lbl_800EE930;
extern u16 lbl_803CB798[4];
extern u16 lbl_803CB7A0[4];
typedef struct Unk80366158 {
    /*0x00*/ u8 _00[LBL_80366158_PAD(0x28)];
    /*0x28*/ u8 _28;
} Unk80366158;

extern Unk80366158 lbl_80366158;
extern f32 fn_800B4A44(GameActor* model, u16 joint);
extern f32 fn_800B4C40(GameActor* model);
extern s32 fn_8004AD54(u32 stadium, s32 flags);
extern void fn_8004B208(CharActor* actor, s16 anim, s32 a, f32 t);
extern void fn_800B2B4C(GameActor* model, f32 v);
extern void fn_800B993C(void);
extern u8 lbl_800EEA58[25];
extern void fn_8003A540(s32 arg);
extern void fn_800BF048(void (*fn)(void* arg));
typedef struct BattingOrder {
    /*0x0*/ s8 roster;
    /*0x1*/ u8 _1;
    /*0x2*/ s8 pos;
    /*0x3*/ u8 _3;
} BattingOrder;

extern BattingOrder lbl_80354720[2][9];
extern u8 lbl_803CB7C2;
extern u8 lbl_803CBBF8;
extern u8 lbl_803CBBF9;
extern u8 lbl_803CBBFA;
extern s32 lbl_803CBC28;
extern u8 lbl_803CBC2C;
extern u8 fn_8003AE54(void);
extern void fn_8003A8A0(void* display, Mtx m, s32 a);
extern f32 lbl_803CB7BC;
extern u8 lbl_803CB7C0;
extern u8 lbl_803CB7C1;
extern f32 charSizeMultipliers[][2];
extern void fn_8004B6EC(CharActor* actor, ActorObject* slot);
extern void fn_8004B7F4(CharActor* actor, ActorObject* slot);
extern void fn_8004BAEC(CharActor* actor, ActorObject* slot);
extern void fn_8005240C(CharActor* actor, ActorObject* slot);
extern s32 fn_80024C6C(CharActor* actor, s32 which);
extern void fn_800BEA04(Vec pos);
extern void fn_800BD8C4(ActorObjectTable* list, MtxPtr view);
extern CharDrawCallback lbl_803CB7AC[2];
extern u8 lbl_803CBBC0;
extern void fn_80052694(s32 cam);
extern void fn_8003414C(MtxPtr view);
extern void minigamesGXStuff(void);
extern void fn_800BDA94(ActorObject* slot, MtxPtr view);
extern void fn_800BD670(ActorObjectTable* list, MtxPtr view);
extern void LITInitDir(void* light, f32 x, f32 y, f32 z);
extern void LITXForm(void* light, MtxPtr view);
extern u8 lbl_803CBBFB;
extern u8 lbl_803CBBFC;
extern u8 lbl_803CBBFD;
extern void* lbl_803CBC00;
extern u8 lbl_803CBC0C;
extern CharPart* lbl_803CBC1C;
extern CharParts* lbl_803CBC20;
extern u8 lbl_803CBC04;
extern void* lbl_803CBC08;
extern void fn_8003AC90(void);
extern void fn_800ACFB0(void* object);
extern void fn_800B9AA8(void* object);
extern void fn_800B2D5C(GameActor* model);
extern void fn_800B0A14_removeQueue(void* unused);
extern void* fn_800B0A5C_insertQueue(void* draw, s32 priority);

static inline s32 getJoint(CharActor* actor, s32 k) {
    return actor != NULL ? actor->jointIdx[k] : 0xFFFF;
}

static inline void copyPartJointData(CharActor* actor, s32 which) {
    s32 joint = actor != NULL ? actor->jointIdx[lbl_803CB7B4[which]] : 0xFFFF;
    GameActor** models;
    GameActor* model;
    GameBone* dst;
    GameActor* src;
    GameBone** jp;
    s32 i;
    s32 n;

    if (joint != 0xFFFF) {
        models = &actor->model;
        i = 0;
        do {
            model = *models;
            if (lbl_800EEAAC[actor->kind] >= 0 && actor->parts != NULL) {
                dst = model->boneArray[joint];
                if (which & 1) {
                    src = lbl_8036E548.partSlots->objects[actor->parts->part[1].slot].actor;
                } else {
                    src = lbl_8036E548.partSlots->objects[actor->parts->part[0].slot].actor;
                }
                if (src != NULL) {
                    n = src->totalBones;
                    jp = &src->boneArray[n];
                    do {
                        jp--;
                        n--;
                        if ((*jp)->dispObj != NULL) {
                            dst->dispObj = (*jp)->dispObj;
                            break;
                        }
                    } while (n != 0);
                }
                break;
            }
            models--;
        } while (i-- != 0);
    }
}

static inline void initModelJoints(CharActor* actor, ActorObject* slot) {
    s32 j;

    fn_800B2B74(slot->actor, actor->jointIdx[19]);
    fn_800B2B74(slot->actor, actor->jointIdx[25]);
    fn_800B2B74(slot->actor, actor->jointIdx[36]);
    j = actor->jointIdx[3];
    if (j != 0xFFFF) {
        fn_800B2B54(actor->model, j, 0xD);
    }
    j = actor->jointIdx[3];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->actor, j, 0, 0);
        slot->actor->boneArray[(u16)j]->stepTranslation = 1;
    }
    j = actor->jointIdx[2];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->actor, j, 0, 0);
        slot->actor->boneArray[(u16)j]->stepTranslation = 1;
    }
    j = actor->jointIdx[1];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->actor, j, 0, 0);
        slot->actor->boneArray[(u16)j]->stepTranslation = 1;
    }
    j = actor->jointIdx[36];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->actor, j, 0, 0);
    }
    j = actor->jointIdx[46];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->actor, j, 0, 0);
        slot->actor->boneArray[(u16)j]->stepTranslation = 1;
    }
    fn_800B2C08(slot->actor, actor->jointIdx[4]);
}

static inline void drawSlot(ActorObject* slot, s32 pass, MtxPtr view) {
    GameActor* model = slot->actor;

    if (slot->callback != NULL) {
        slot->callback(slot);
    }
    switch (slot->numLights) {
    case 0:
        fn_8001DD58(model, pass, view, 0);
        break;
    case 1:
        fn_8001DD58(model, pass, view, 1, slot->lights[0]);
        break;
    case 2:
        fn_8001DD58(model, pass, view, 2, slot->lights[0], slot->lights[1]);
        break;
    case 3:
        fn_8001DD58(model, pass, view, 3, slot->lights[0], slot->lights[1], slot->lights[2]);
        break;
    case 4:
        fn_8001DD58(model, pass, view, 4, slot->lights[0], slot->lights[1], slot->lights[2], slot->lights[3]);
        break;
    case 5:
        fn_8001DD58(model, pass, view, 5, slot->lights[0], slot->lights[1], slot->lights[2], slot->lights[3], slot->lights[4]);
        break;
    case 6:
        fn_8001DD58(model, pass, view, 6, slot->lights[0], slot->lights[1], slot->lights[2], slot->lights[3], slot->lights[4], slot->lights[5]);
        break;
    case 7:
        fn_8001DD58(model, pass, view, 7, slot->lights[0], slot->lights[1], slot->lights[2], slot->lights[3], slot->lights[4], slot->lights[5], slot->lights[6]);
        break;
    case 8:
        fn_8001DD58(model, pass, view, 8, slot->lights[0], slot->lights[1], slot->lights[2], slot->lights[3], slot->lights[4], slot->lights[5], slot->lights[6], slot->lights[7]);
        break;
    }
}

// .text:0x80011468 size:0x108
void fn_80011468(void) {
    s32 i;
    for (i = 0; i < 13; i++) {
        CharActor* actor = lbl_8036E548.active[i];
        if (actor != NULL) {
            ActorObject* obj = &lbl_8036E548.slots->objects[actor->modelIndex];
            switch (actor->kind) {
            case 19:
                fn_8004B6EC(actor, obj);
                break;
            case 40:
            case 41:
                fn_8004B7F4(actor, obj);
                break;
            case 38:
                obj->actor->tickFlag = 1;
            case 18:
                fn_8004BAEC(actor, obj);
                break;
            case 14:
            case 37:
                fn_8005240C(actor, obj);
                break;
            case 6:
            case 10:
            case 12:
            case 24:
            case 25:
            case 26:
            case 42:
                obj->actor->tickFlag = 1;
                break;
            case 20:
            case 43:
                if (actor->anim[0] == 0x40) {
                    obj->actor->tickFlag = 0;
                } else {
                    obj->actor->tickFlag = 1;
                }
                break;
            }
        }
    }
}

// .text:0x80011570 size:0x8
CharActor* fn_80011570(void) {
    return lbl_803CBC18;
}

// .text:0x80011578 size:0x50
void fn_80011578(void) {
    s8 i = 0;
    s32 n;
    for (n = 13; n != 0; n--) {
        if (i >= 0 && i < 13) {
            CharActor* actor = lbl_8036E548.active[(u32)i];
            if (actor != NULL) {
                actor->tevHook = NULL;
            }
        }
        i++;
    }
}

// .text:0x800115C8 size:0x3C
void fn_800115C8(s8 index) {
    if (index >= 0 && index < 13) {
        CharActor* actor = lbl_8036E548.active[index];
        if (actor != NULL) {
            actor->tevHook = NULL;
        }
    }
}

// .text:0x80011604 size:0x3C
void fn_80011604(s8 index, DOTevHook value) {
    CharActor* actor;
    if (index < 0 || index >= 13) {
        return;
    }
    actor = lbl_8036E548.active[index];
    if (actor != NULL) {
        actor->tevHook = value;
    }
}

// .text:0x80011640 size:0x9C
void fn_80011640(Mtx a, Mtx out) {
    Mtx scale = {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.93333334f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
    };
    PSMTXConcat(scale, a, out);
}

// .text:0x800116DC size:0xF0
void fn_800116DC(CharActor* actor, Mtx m, u16 joint) {
    Mtx tmp;
    Mtx scale = {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0714285f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
    };
    MtxPtr dst;

    PSMTXConcat(scale, m, tmp);
    tmp[0][3] = 0.0f;
    tmp[1][3] = 0.0f;
    tmp[2][3] = 0.0f;
    PSMTXInverse(tmp, tmp);
    dst = actor->model->boneArray[joint]->forwardMtx;
    tmp[0][3] = dst[0][3];
    tmp[1][3] = dst[1][3];
    tmp[2][3] = dst[2][3];
    PSMTXCopy(tmp, dst);
}

// .text:0x800117CC size:0xE0
void fn_800117CC(Mtx src, Mtx m, Mtx dst) {
    Mtx tmp;
    Mtx scale = {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0714285f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
    };

    PSMTXConcat(scale, m, tmp);
    tmp[0][3] = 0.0f;
    tmp[1][3] = 0.0f;
    tmp[2][3] = 0.0f;
    PSMTXInverse(tmp, tmp);
    tmp[0][3] = src[0][3];
    tmp[1][3] = src[1][3];
    tmp[2][3] = src[2][3];
    PSMTXCopy(tmp, dst);
}

// .text:0x800118AC size:0xC0
MtxPtr fn_800118AC(Mtx m, Mtx out) {
    Mtx scale = {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0714285f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
    };

    PSMTXConcat(scale, m, out);
    out[0][3] = 0.0f;
    out[1][3] = 0.0f;
    out[2][3] = 0.0f;
    PSMTXInverse(out, out);
    return out;
}

// .text:0x8001196C size:0xF4
static inline void clearSlotRefs(s32 index) {
    s32 j;
    for (j = 0; j < 13; j++) {
        if (lbl_8036E548._2D6A[j] == index) {
            lbl_8036E548._2D6A[j] = -1;
        }
    }
}

static inline void detachOwnedPart(s32 index) {
    CharActor* actor;
    CharPart* part;

    actor = lbl_8036E548.active[index];
    if (actor != NULL && (part = actor->part) != NULL && actor->index == index) {
        part->_61 = -1;
        part->player.curIdx = -2;
        lbl_8036E548.active[index]->part = NULL;
    }
}

static inline void detachOwnedParts(s32 index) {
    CharActor* actor;
    CharParts* parts;

    actor = lbl_8036E548.active[index];
    if (actor != NULL && (parts = actor->parts) != NULL && actor->index == index) {
        parts->_D1 = parts->_D0;
        parts->_D0 = -1;
        parts->part[0].player.curIdx = -2;
        parts->part[1].player.curIdx = -2;
        lbl_8036E548.active[index]->parts = NULL;
    }
}

// NONMATCHING 98.6%: r7/r8 swapped (active[i] pointer vs parts)
#if NONMATCHING
void fn_8001196C(void) {
    s32 i;

    for (i = 0; i < 9; i++) {
        detachOwnedPart(i);
        detachOwnedParts(i);
        lbl_8036E548.active[i]->_25C = 0;
        lbl_8036E548.active[i] = NULL;
        clearSlotRefs(i);
    }
}
#endif

// .text:0x80011A60 size:0x104
// NONMATCHING 99.0%: register allocation only
#if NONMATCHING
void fn_80011A60(void) {
    s32 i;
    s32 idx;

    for (i = 0; i < 4; i++) {
        idx = i + 9;
        detachOwnedPart(idx);
        detachOwnedParts(idx);
        if (lbl_8036E548.active[idx] != NULL) {
            lbl_8036E548.active[idx]->_25C = 0;
            lbl_8036E548.active[idx] = NULL;
        }
        clearSlotRefs(idx);
    }
}
#endif

// .text:0x80011B64 size:0x80
void fn_80011B64(s32 index) {
    CharActor* actor;
    CharPart* part;
    CharParts* parts;

    actor = lbl_8036E548.active[index];
    if (actor != NULL) {
        part = actor->part;
        if (part != NULL) {
            part->_61 = -1;
            part->player.curIdx = -2;
            lbl_8036E548.active[index]->part = NULL;
        }
        parts = lbl_8036E548.active[index]->parts;
        if (parts != NULL) {
            parts->_D1 = parts->_D0;
            parts->_D0 = -1;
            parts->part[0].player.curIdx = -2;
            parts->part[1].player.curIdx = -2;
            lbl_8036E548.active[index]->parts = NULL;
        }
    }
}

// .text:0x80011BE4 size:0xC4
void fn_80011BE4(s32 index) {
    s32 j;
    CharActor* actor;
    CharPart* part;
    CharParts* parts;

    actor = lbl_8036E548.active[index];
    if (actor != NULL) {
        part = actor->part;
        if (part != NULL) {
            part->_61 = -1;
            part->player.curIdx = -2;
            lbl_8036E548.active[index]->part = NULL;
        }
        parts = lbl_8036E548.active[index]->parts;
        if (parts != NULL) {
            parts->_D1 = parts->_D0;
            parts->_D0 = -1;
            parts->part[0].player.curIdx = -2;
            parts->part[1].player.curIdx = -2;
            lbl_8036E548.active[index]->parts = NULL;
        }
        lbl_8036E548.active[index]->_25C = 0;
    }
    lbl_8036E548.active[index] = NULL;
    for (j = 0; j < 13; j++) {
        if (lbl_8036E548._2D6A[j] == index) {
            lbl_8036E548._2D6A[j] = -1;
        }
    }
}

// .text:0x80011CA8 size:0xA44
static inline void copyPart(CharPart* dst, CharPart* src) {
    dst->files = src->files;
    dst->slot = src->slot;
    dst->player.set = src->player.set;
    dst->player.seqs = src->player.seqs;
    dst->player.tableList = src->player.tableList;
    dst->player.model = src->player.model;
    dst->player.curIdx = src->player.curIdx;
    memcpy(&dst->player.state, &src->player.state, sizeof(dst->player.state));
    memcpy(dst->player.tables, src->player.tables, sizeof(dst->player.tables));
}

static inline void stashPart(CharPart* tmp, CharPart* src) {
    copyPart(&tmp[src->slot % 6], src);
}

// NONMATCHING 99.7%: copy-field temps register allocation; used[] initialiser is an anonymous .sbss2 object
#if NONMATCHING
s32 fn_80011CA8(CharActor* actor, s32 a, s32 b) {
    u8 used[6] = { 0, 0, 0, 0, 0, 0 };
    CharPart tmp[6];
    s32 idx = actor->index;
    s32 first;
    s32 second;
    s32 k;
    s32 n;

    stashPart(tmp, &lbl_8036E548.partsPool[idx * 3 + 0].part[0]);
    stashPart(tmp, &lbl_8036E548.partsPool[idx * 3 + 0].part[1]);
    stashPart(tmp, &lbl_8036E548.partsPool[idx * 3 + 1].part[0]);
    stashPart(tmp, &lbl_8036E548.partsPool[idx * 3 + 1].part[1]);
    stashPart(tmp, &lbl_8036E548.partsPool[idx * 3 + 2].part[0]);
    stashPart(tmp, &lbl_8036E548.partsPool[idx * 3 + 2].part[1]);
    if ((u32)(a - 2) > 2) {
        if (actor->_25B != 0) {
            first = 2;
            second = 3;
        } else {
            first = 4;
            second = 5;
        }
    } else if (actor->_25A != 0) {
        first = 4;
        second = 1;
    } else {
        first = 0;
        second = 3;
    }
    copyPart(&actor->parts->part[0], &tmp[first]);
    copyPart(&actor->parts->part[1], &tmp[second]);
    used[first] = 1;
    used[second] = 1;
    n = 0;
    for (k = 0; k < 6; k++) {
        if (used[k] == 0) {
            switch (n) {
            case 0:
                copyPart(&lbl_8036E548.partsPool[idx * 3 + 1].part[0], &tmp[k]);
                break;
            case 1:
                copyPart(&lbl_8036E548.partsPool[idx * 3 + 1].part[1], &tmp[k]);
                break;
            case 2:
                copyPart(&lbl_8036E548.partsPool[idx * 3 + 2].part[0], &tmp[k]);
                break;
            case 3:
                copyPart(&lbl_8036E548.partsPool[idx * 3 + 2].part[1], &tmp[k]);
                break;
            }
            n++;
        }
    }
    copyPartJointData(lbl_8036E548.active[actor->index], 0);
    copyPartJointData(lbl_8036E548.active[actor->index], 1);
    fn_80025EEC(&actor->parts->part[0].player, a, b);
    fn_80025EEC(&actor->parts->part[1].player, a, b);
    return 1;
}
#endif

// .text:0x800126EC size:0x10C
void fn_800126EC(CharPart* part, void* tex, u8* fileIdx) {
    void* layout;
    void* geo;
    ActorObject* slot;

    slot = &lbl_8036E548.partSlots->objects[part->slot];
    layout = PTR32_GET(void, part->files[fileIdx[0]]);
    geo = PTR32_GET(void, part->files[fileIdx[1]]);
    LoadActorLayout(layout);
    convertGeometryAndSknHeader(geo, NULL);
    haveActLayoutPointToGeoHeader(layout, geo);
    fn_800BD190(geo, tex);
    fn_800238E0(lbl_8036E548.partSlots, part->slot, part->slot, layout);
    if (part->files[2] != NULL) {
        fn_80025DDC(PTR32_GET(void, part->files[fileIdx[2]]));
        fn_80025C58(PTR32_GET(void, part->files[fileIdx[2]]), (ShapeModel**)slot);
    }
    part->player.set = PTR32_GET(void, part->files[fileIdx[3]]);
    fn_80025FFC(PTR32_GET(void, part->files[fileIdx[2]]), &part->player);
}

// .text:0x800127F8 size:0x398

// NONMATCHING 98.9%: register allocation only (actor/tex, joint-copy temps)
#if NONMATCHING
u8 LoadModel(CharActor* actor) {
    CharParts* parts;
    CharPart* part;
    void** files;
    void* tex;

    if (actor == NULL) {
        OSPanic("model.c", 0x22E6, " Character Data None \n");
        return 0;
    }
    parts = actor->parts;
    if (parts == NULL) {
        OSPanic("model.c", 0x22EA, " Character Parts Data None \n");
        return 0;
    }
    if (lbl_803CBC14 == 0 && (s32)(u8)lbl_803C6CF8.idle == 1) {
        if (parts->_CD != 0) {
            part = &parts->part[1];
            lbl_803CBC10 = part;
            fn_80021CA4(actor->parts->_CF, 5, part->files);
            lbl_803CBC15 = 1;
        } else {
            lbl_803CBC10 = &parts->part[0];
            fn_80021CA4(actor->parts->_CF, 0, parts->part[0].files);
            lbl_803CBC15 = 0;
        }
        lbl_803CBC14 = 1;
    }
    if (lbl_803716B8.keepTask == 0) {
        part = lbl_803CBC10;
        tex = actor->parts->tex;
#ifdef TARGET_PC
        // The part file starts with 4 big-endian 32-bit offsets (PTR32 entries).
        {
            PTR32(void)* tbl = part->files;
            s32 k;
            port_swap_offset_table(tbl, 4);
            for (k = 0; k < 4; k++) {
                if (tbl[k] != 0) {
                    tbl[k] += PTR_TO_U32(tbl);
                }
            }
        }
#else
        files = part->files;
        if (files[0] != NULL) {
            files[0] = (u8*)files + (uintptr_t)files[0];
        }
        files = part->files;
        if (files[1] != NULL) {
            files[1] = (u8*)files + (uintptr_t)files[1];
        }
        files = part->files;
        if (files[2] != NULL) {
            files[2] = (u8*)files + (uintptr_t)files[2];
        }
        files = part->files;
        if (files[3] != NULL) {
            files[3] = (u8*)files + (uintptr_t)files[3];
        }
#endif
        fn_800126EC(part, tex, lbl_803CB7C4);
        copyPartJointData(lbl_8036E548.active[actor->index], lbl_803CBC15);
        lbl_803CBC14 = 0;
        lbl_803CBC10 = NULL;
        return 1;
    }
    return 0;
}
#endif

static inline BOOL loadPartModel(CharPart* part, s8 kind, s32 mode, void* tex) {
    void** files;

    if (lbl_803CBC0C == 0 && (s32)(u8)lbl_803C6CF8.idle == 1) {
        lbl_803CBC1C = part;
        lbl_803CBC0C = 1;
        fn_80021CA4(kind, mode, part->files);
    }
    if (lbl_803716B8.keepTask == 0) {
        part = lbl_803CBC1C;
        lbl_803CBC0C = 0;
#ifdef TARGET_PC
        // The part file starts with 4 big-endian 32-bit offsets (PTR32 entries).
        {
            PTR32(void)* tbl = part->files;
            s32 k;
            port_swap_offset_table(tbl, 4);
            for (k = 0; k < 4; k++) {
                if (tbl[k] != 0) {
                    tbl[k] += PTR_TO_U32(tbl);
                }
            }
        }
#else
        files = part->files;
        if (files[0] != NULL) {
            files[0] = (u8*)files + (uintptr_t)files[0];
        }
        files = part->files;
        if (files[1] != NULL) {
            files[1] = (u8*)files + (uintptr_t)files[1];
        }
        files = part->files;
        if (files[2] != NULL) {
            files[2] = (u8*)files + (uintptr_t)files[2];
        }
        files = part->files;
        if (files[3] != NULL) {
            files[3] = (u8*)files + (uintptr_t)files[3];
        }
#endif
        fn_800126EC(part, tex, lbl_803CB7C4);
        lbl_803CBC1C = NULL;
        return TRUE;
    }
    return FALSE;
}

// .text:0x80012B90 size:0xAF0
// NONMATCHING 89%: state-machine register allocation and part-model loader scheduling
#if NONMATCHING
u8 fn_80012B90(CharActor* actor) {
    s8 kind = actor->kind;
    s8 idx = actor->index;
    u8 st = lbl_803CBC04;
    CharParts* p;
    void* tex;
    s32 n;
    s32 flag;
    s32 mode;

    if (st < 3) {
        p = &lbl_8036E548.partsPool[idx * 3];
    } else if (st < 6) {
        p = &lbl_8036E548.partsPool[idx * 3 + 1];
    } else if (st < 9) {
        p = &lbl_8036E548.partsPool[idx * 3 + 2];
    }
    switch (st) {
    case 0:
    case 3:
    case 6:
        tex = PTR32_GET(void, actor->files[0]);
        p->tex = tex;
        lbl_803CBC08 = tex;
        p->_CF = kind;
        if (lbl_803CBC04 == 0) {
            p->_D1 = p->_D0;
            p->_D0 = actor->index;
        } else {
            p->_D1 = 9;
            p->_D0 = 9;
        }
        n = lbl_803CBC04 / 3 + idx * 3;
        p->_CD = actor->_25A;
        p->_CE = actor->_25B;
        p->_CC = 1;
        lbl_803CBC04++;
        p->part[0].slot = n * 2;
        p->part[1].slot = n * 2 + 1;
        break;
    case 1:
    case 2:
        flag = p->_CD == 0;
        if (flag == p->_CD) {
            mode = 1 - flag;
        } else {
            mode = 3 - flag;
        }
        if (loadPartModel(flag ? &p->part[0] : &p->part[1], p->_CF, mode, lbl_803CBC08)) {
            p->_CD = p->_CD == 0;
            lbl_803CBC04++;
        }
        break;
    case 4:
        if (loadPartModel(&p->part[1], p->_CF, 1, lbl_803CBC08)) {
            lbl_803CBC04 = 5;
        }
        break;
    case 5:
        if (loadPartModel(&p->part[0], p->_CF, 0, lbl_803CBC08)) {
            lbl_803CBC04 = 6;
        }
        break;
    case 7:
        if (loadPartModel(&p->part[1], p->_CF, 5, lbl_803CBC08)) {
            lbl_803CBC04 = 8;
        }
        break;
    case 8:
        if (loadPartModel(&p->part[0], p->_CF, 4, lbl_803CBC08)) {
            actor->parts = &lbl_8036E548.partsPool[idx * 3];
            lbl_803CBC04 = 0;
            lbl_803CBC08 = NULL;
            return 1;
        }
        break;
    }
    return 0;
}
#endif

// .text:0x80013680 size:0xB84

static inline void claimParts(CharParts* p, void* tex, s8 kind, s8 idx, CharActor* actor) {
    p->tex = tex;
    p->_CF = kind;
    p->_D1 = p->_D0;
    p->_D0 = idx;
    p->_CD = actor->_25A;
    p->_CE = actor->_25B;
}

// NONMATCHING 85%: register allocation and pool-entry addressing in the search loops
#if NONMATCHING
u8 fn_80013680(CharActor* actor) {
    s8 kind = actor->kind;
    s8 idx = actor->index;
    void* tex;
    CharParts* p;
    CharActor* other;
    u8 i;
    u8 k;
    BOOL lo;
    BOOL same;
    BOOL alt;

    if (lbl_803CBBFB == 0) {
        lbl_803CBBFB = 1;
        tex = PTR32_GET(void, actor->files[0]);
        lbl_803CBC00 = tex;
        for (i = 0; i < 13; i++) {
            p = &lbl_8036E548.partsPool[i];
            if (p->_CF == kind && p->_CD == actor->_25A && p->_CE == actor->_25B && p->_D0 == -1 && p->tex == tex
                && ((actor->index < 9 && p->_D1 < 9) || (actor->index >= 9 && p->_D1 >= 9))) {
                lbl_8036E548.partsPool[i]._D0 = idx;
                actor->parts = &lbl_8036E548.partsPool[i];
                actor->parts->_CC = 1;
                copyPartJointData(lbl_8036E548.active[actor->index], 0);
                copyPartJointData(lbl_8036E548.active[actor->index], 1);
                lbl_803CBBFD = 0;
                lbl_803CBBFC = 0;
                lbl_803CBBFB = 0;
                lbl_803CBC00 = NULL;
                return 1;
            }
        }
        if (lbl_803CBBFC == 0 && lbl_803CBBFD == 0) {
            for (i = 0; i < 13; i++) {
                if (lbl_8036E548.partsPool[i]._D0 == actor->index && lbl_8036E548.partsPool[i]._D0 < 9) {
                    lbl_8036E548.partsPool[i]._D0 = -1;
                    break;
                }
            }
            for (i = 0; i < 13; i++) {
                p = &lbl_8036E548.partsPool[i];
                if (p->_D0 == -1) {
                    lbl_803CBC20 = p;
                    claimParts(p, tex, kind, idx, actor);
                    break;
                }
            }
            if (i == 13) {
                for (i = 0; i < 13; i++) {
                    p = &lbl_8036E548.partsPool[i];
                    lbl_803CBC20 = p;
                    for (k = 0; k < 13; k++) {
                        other = lbl_8036E548.active[k];
                        if (other != NULL && p->_CF == other->kind) {
                            break;
                        }
                    }
                    if (k == 13) {
                        claimParts(p, lbl_803CBC00, kind, idx, actor);
                        break;
                    }
                }
            }
        }
        lbl_803CBC20->part[1].player.active = 0;
        lbl_803CBC20->part[0].player.active = 0;
    }
    if (lbl_803CBBFB == 0) {
        return 0;
    }
    if (idx < 9) {
        alt = actor->_25A != 0;
    } else {
        alt = actor->_25B != 0;
    }
    lo = idx < 9;
    same = alt == lo;
    for (;;) {
        if (lbl_803CBBFC == 0) {
            p = lbl_803CBC20;
            if (loadPartModel(&p->part[1], p->_CF, (lo && p->_CD != 0) ? 3 : (same ? 5 : 1), lbl_803CBC00)) {
                lbl_803CBBFC = 1;
                continue;
            }
        } else if (lbl_803CBBFD == 0) {
            p = lbl_803CBC20;
            if (loadPartModel(&p->part[0], p->_CF, (lo && p->_CD != 1) ? 2 : (same ? 4 : 0), lbl_803CBC00)) {
                lbl_803CBBFD = 1;
            }
        }
        break;
    }
    if (lbl_803CBBFC == 0 || lbl_803CBBFD == 0) {
        return 0;
    }
    actor->parts = lbl_803CBC20;
    copyPartJointData(lbl_8036E548.active[actor->index], 0);
    copyPartJointData(lbl_8036E548.active[actor->index], 1);
    actor->parts->_CC = 1;
    lbl_803CBC20 = NULL;
    lbl_803CBBFB = 0;
    lbl_803CBBFD = 0;
    lbl_803CBBFC = 0;
    lbl_803CBC00 = NULL;
    return 1;
}
#endif

// .text:0x80014204 size:0x3F4
// NONMATCHING 88%: unrolled size/slot loops scheduled differently
#if NONMATCHING
void fn_80014204(s32 count) {
    u32 max = 0;
    u32 size;
    u32 s;
    s32 n = 0;
    s32 k;
    s32 j;
    s32 i;
    s32 total;
    u8* buf;

    for (k = 0; k < 54; k++) {
        if (lbl_800EEAAC[k] >= 0) {
            for (j = 0; j < 6; j++) {
                size = lbl_803CB7A8[n + j].sizeFlags & 0x0FFFFFFF;
                if (max < size) {
                    max = size;
                }
            }
            n += 6;
        }
    }
    s = (max + 0x1F) & ~0x1F;
    buf = _OSAllocFromHeap(0x20, count * (s * 6));
    total = count * 3;
    lbl_803CBC24 = buf;
    for (i = 0; i < total; i++) {
        lbl_8036E548.partsPool[i].part[0].files = (void**)(buf + s * (i * 2));
        lbl_8036E548.partsPool[i].part[1].files = (void**)(buf + s * (i * 2 + 1));
    }
    for (i = 0; i < total; i++) {
        lbl_8036E548.partsPool[i]._D0 = -1;
        lbl_8036E548.partsPool[i]._D1 = -1;
        lbl_8036E548.partsPool[i]._CF = -1;
        lbl_8036E548.partsPool[i]._CE = 0xFF;
        lbl_8036E548.partsPool[i]._CD = 0xFF;
        lbl_8036E548.partsPool[i].tex = NULL;
        lbl_8036E548.partsPool[i]._CC = 0;
        lbl_8036E548.partsPool[i].part[0].slot = i * 2;
        lbl_8036E548.partsPool[i].part[1].slot = i * 2 + 1;
    }
}
#endif

// .text:0x800145F8 size:0x398
static inline u32 maxPartSize(u32 max, s32 idx) {
    s32 j;
    u32 size;

    for (j = 0; j < 6; j++) {
        size = lbl_803CB7A8[idx + j].sizeFlags & 0x0FFFFFFF;
        if (max < size) {
            max = size;
        }
    }
    return max;
}

// NONMATCHING 84%: max-size loops unrolled/scheduled differently
#if NONMATCHING
void fn_800145F8(s32 mode) {
    u32 max = 0;
    u32 s;
    u8* buf;
    s32 t;
    s32 i;
    s32 idx;

    if (mode == 0) {
        for (t = 0; t < 2; t++) {
            for (i = 0; i < 9; i++) {
                idx = lbl_800EEAAC[inMemRoster[t][i].charId];
                if (idx >= 0) {
                    max = maxPartSize(max, idx);
                }
            }
        }
    } else {
        for (i = 0; i < 54; i++) {
            idx = lbl_800EEAAC[i];
            if (idx >= 0) {
                max = maxPartSize(max, idx);
            }
        }
    }
    s = (max + 0x1F) & ~0x1F;
    buf = _OSAllocFromHeap(0x20, s * 26);
    lbl_803CBC24 = buf;
    for (i = 0; i < 13; i++) {
        lbl_8036E548.partsPool[i].part[0].files = (void**)(buf + s * (i * 2));
        lbl_8036E548.partsPool[i].part[1].files = (void**)(buf + s * (i * 2 + 1));
    }
    for (i = 0; i < 13; i++) {
        lbl_8036E548.partsPool[i]._CF = -1;
        lbl_8036E548.partsPool[i]._D1 = -1;
        lbl_8036E548.partsPool[i]._D0 = -1;
        lbl_8036E548.partsPool[i]._CD = 0xFF;
        lbl_8036E548.partsPool[i]._CE = 0xFF;
        lbl_8036E548.partsPool[i].tex = NULL;
        lbl_8036E548.partsPool[i]._CC = 0;
        lbl_8036E548.partsPool[i].part[0].slot = i * 2;
        lbl_8036E548.partsPool[i].part[1].slot = i * 2 + 1;
    }
}
#endif

// .text:0x80014990 size:0x88
void fn_80014990(s32 index, void* model, ShapeAnimSet* set) {
    CharActor* actor;
    CharPart* part;

    if (index >= 0 && index < 13) {
        actor = lbl_8036E548.active[index];
        if (actor != NULL) {
            goto found;
        }
    }
    return;
found:
    part = &lbl_80118220[index];
    actor->part = part;
    part->slot = actor->kind;
    part->_61 = actor->index;
    part->player.set = set;
    part->player.model = model;
    fn_80025FFC(model, &part->player);
}

// .text:0x80014A18 size:0x334
// NONMATCHING 89%: free-slot search ladder addressing and register allocation
#if NONMATCHING
s32 fn_80014A18(void) {
    s32 i;
    s32 k;
    s32 done;
    CharActor* actor;

    if (lbl_8036E548._2D8E == 0) {
        lbl_8036E548._2D8E = 1;
        lbl_8036E548.loadActor = -1;
        for (i = 0; i < 9; i++) {
            lbl_8036E548._2D7F[i] = -1;
        }
    }
    if (lbl_8036E548._2D8E == 1) {
        for (i = 0; i <= 8; i++) {
            for (k = 0; k < 9; k++) {
                if (lbl_8036E548.active[i]->kind == lbl_8036E548._2D7F[k]) {
                    lbl_8036E548.active[i]->banks.b[5] = lbl_8036E548.animBufs[5 + k];
                    break;
                }
            }
            if (k >= 9) {
                lbl_8036E548.loadStep = 0;
                lbl_8036E548._2D8E = 2;
                lbl_8036E548.loadActor = i;
                break;
            }
        }
        if (i > 8) {
            return 1;
        }
    }
    if (lbl_8036E548._2D8E == 2) {
        actor = &lbl_8036E548.actors[lbl_8036E548.active[lbl_8036E548.loadActor]->modelIndex];
        if (lbl_8036E548.loadStep == 0) {
            k = 0;
            if (lbl_8036E548._2D7F[0] >= 0) {
                k = 1;
                if (lbl_8036E548._2D7F[1] >= 0) {
                    k = 2;
                    if (lbl_8036E548._2D7F[2] >= 0) {
                        k = 3;
                        if (lbl_8036E548._2D7F[3] >= 0) {
                            k = 4;
                            if (lbl_8036E548._2D7F[4] >= 0) {
                                k = 5;
                                if (lbl_8036E548._2D7F[5] >= 0) {
                                    k = 6;
                                    if (lbl_8036E548._2D7F[6] >= 0) {
                                        k = 7;
                                        if (lbl_8036E548._2D7F[7] >= 0) {
                                            k = 8;
                                            if (lbl_8036E548._2D7F[8] >= 0) {
                                                k = 9;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            lbl_8036E548._2D7F[k] = actor->kind;
            if (lbl_8036E548._2D7C == 0) {
                actor->banks.b[2] = lbl_8036E548.animBufs[5 + k];
                ARAMTransfer(&lbl_803CB790[actor->kind * 0x13 + 4], actor->banks.b[2], 0, 0);
            } else {
                actor->banks.b[5] = lbl_8036E548.animBufs[5 + k];
                ARAMTransfer(&lbl_803CB790[actor->kind * 0x13 + 0x11], actor->banks.b[5], 0, 0);
            }
            lbl_8036E548.loadStep = 1;
            done = 0;
        } else if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            if (lbl_8036E548._2D7C == 0) {
                ANIMGet(actor->banks.b[2]);
            } else {
                ANIMGet(actor->banks.b[5]);
            }
            done = 1;
        } else {
            done = 0;
        }
        if (done) {
            lbl_8036E548._2D8E = 1;
        }
    }
    return 0;
}
#endif

// .text:0x80014D4C size:0x104
s32 fn_80014D4C(s32 id) {
    s32 file;

    if (id < 0) {
        return 1;
    }
    if (lbl_8036E548.preload[1].id == id) {
        return 1;
    }
    if (lbl_8036E548.preload[1].state <= 1) {
        if (g_d_GameSettings.GameModeSelected == 2) {
            file = id * 0x13 + 0xA;
        } else {
            file = id * 0x13 + 2;
        }
        if ((s32)(u8)lbl_803C6CF8.idle != 1) {
            lbl_8036E548.preload[1].state = 1;
            return 0;
        }
        ARAMTransfer(&lbl_803CB790[file], lbl_8036E548.preload[1].buffer, 0, 0);
        lbl_8036E548.preload[1].state = 2;
    } else if ((s32)(u8)lbl_803C6CF8.idle == 1) {
        lbl_8036E548.preload[1].id = id;
        lbl_8036E548.preload[1].state = 0;
        return 1;
    }
    return 0;
}

// .text:0x80014E50 size:0xF0
s32 fn_80014E50(s32 id) {
    s32 file;

    if (id < 0) {
        return 1;
    }
    if (lbl_8036E548.preload[2].state <= 1) {
        file = id * 0x13;
        if ((s32)(u8)lbl_803C6CF8.idle != 1) {
            lbl_8036E548.preload[2].state = 1;
            return 0;
        }
        if (fn_8002204C(id, lbl_8036E548.preload[2].buffer) == 0) {
            ARAMTransfer(&lbl_803CB790[file], lbl_8036E548.preload[2].buffer, 0, 0);
        }
        lbl_8036E548.preload[2].state = 2;
    } else if (lbl_803716B8.keepTask == 0 && (s32)(u8)lbl_803C6CF8.idle == 1) {
        lbl_8036E548.preload[2].id = id;
        lbl_8036E548.preload[2].state = 0;
        return 1;
    }
    return 0;
}

// .text:0x80014F40 size:0xCC
s32 fn_80014F40(s32 id) {
    s32 file;

    if (id < 0) {
        return 1;
    }
    if (lbl_8036E548.preload[0].state <= 1) {
        file = id * 0x13 + 1;
        if (lbl_803C6CF8.idle != 1) {
            lbl_8036E548.preload[0].state = 1;
            return 0;
        }
        ARAMTransfer(&lbl_803CB790[file], lbl_8036E548.preload[0].buffer, 0, 0);
        lbl_8036E548.preload[0].state = 2;
    } else if ((s32)(u8)lbl_803C6CF8.idle == 1) {
        lbl_8036E548.preload[0].id = id;
        lbl_8036E548.preload[0].state = 0;
        return 1;
    }
    return 0;
}

// .text:0x8001500C size:0x45C
// NONMATCHING 88%: register allocation in the inlined part-attach step
#if NONMATCHING
s32 fn_8001500C(s32 team, s32 roster, s32 index) {
    CharActor** slot;
    CharActor* actor;
    CharPart* part;
    u8 kind;
    s32 k;
    s32 n;
    BOOL ok;
    BOOL done;

    if (lbl_8036E548.state == 1) {
        return 0;
    }
    if (lbl_8036E548.state == 2) {
        lbl_8036E548.active[index] = &lbl_8036E548.actors[lbl_8036E548._2D79];
        lbl_8036E548.loadStep = 0;
        lbl_8036E548.state = 3;
    }
    if (lbl_8036E548.state == 3) {
        if (fn_80017340(lbl_8036E548._2D79) == 0) {
            return 0;
        }
        if (lbl_8036E548._2D78 != 0 && lbl_8036E548.active[index]->part != NULL) {
            if (lbl_8036E548.active[index]->parts == NULL) {
                lbl_8036E548.state = 5;
                return 0;
            }
            lbl_8036E548.state = 0;
            return 1;
        }
        if (lbl_803CBC34[3] != 0) {
            lbl_8036E548.state = 4;
        } else if (lbl_803CBC34[4] != 0 && index == 9) {
            lbl_8036E548.state = 4;
        } else {
            lbl_8036E548.state = 5;
        }
    }
    if (lbl_8036E548.state == 4) {
        slot = &lbl_8036E548.active[index];
        actor = *slot;
        kind = actor->kind;
        if (lbl_803CBBF9 == 0) {
            for (k = 0; lbl_80118220[k]._61 != -2; k++) {
                if (kind == (s8)lbl_80118220[k].slot && lbl_80118220[k]._61 == -1) {
                    part = &lbl_80118220[k];
                    actor->part = part;
                    part->slot = kind;
                    part->_61 = index;
                    part->player.model = PTR32_GET(void, actor->files[4]);
                    done = TRUE;
                    goto next;
                }
            }
            lbl_803CBBF9 = 1;
            for (n = 0; lbl_80118220[n]._61 != -2; n++) {
                if (lbl_80118220[n]._61 == -1) {
                    break;
                }
            }
            lbl_803CBC28 = n;
        }
        n = lbl_803CBC28;
        lbl_80118220[n].player.active = 0;
        if (lbl_800EEB18[kind] == -1 || actor->files[4] == NULL) {
            ok = TRUE;
            actor->part = NULL;
        } else {
            if (lbl_803CBBFA == 0) {
                fn_80021ADC(lbl_800EEB18[kind], lbl_80118220[n].files);
                lbl_803CBBFA = 1;
            }
            if ((s32)(u8)lbl_803C6CF8.idle == 1) {
                part = &lbl_80118220[n];
                part->slot = kind;
                part->_61 = index;
                part->player.set = (ShapeAnimSet*)part->files;
                fn_80025FFC(PTR32_GET(void, actor->files[4]), &part->player);
                actor->part = part;
                ok = TRUE;
                lbl_803CBBFA = 0;
            } else {
                ok = FALSE;
            }
        }
        if (ok) {
            done = TRUE;
            lbl_803CBBF9 = 0;
        } else {
            done = FALSE;
        }
    next:
        if (!done) {
            return 0;
        }
        if (lbl_8036E548._2D78 != 0 && (*slot)->parts != NULL) {
            lbl_8036E548.state = 0;
            return 1;
        }
        lbl_8036E548.state = 5;
    }
    if (lbl_8036E548.state == 5) {
        if (fn_80013680(lbl_8036E548.active[index])) {
            lbl_8036E548.state = 0;
            return 1;
        }
        return 0;
    }
    if (index == 9) {
        lbl_8036E548._2D78 = fn_80017098(team, roster, 1, index, 1, -1);
    } else {
        lbl_8036E548._2D78 = fn_80017098(team, roster, 1, index, 0, -1);
    }
    if (lbl_8036E548._2D78 == 0) {
        return 0;
    }
    if (index == 9) {
        lbl_8036E548.state = 2;
        return 0;
    }
    if (lbl_8036E548.active[index]->parts != NULL) {
        return lbl_8036E548._2D78;
    }
    lbl_8036E548.state = 5;
    return 0;
}
#endif

// .text:0x80015468 size:0x4E4
// NONMATCHING 93%: free-slot search ladder addressing and register allocation
#if NONMATCHING
s32 fn_80015468(s32 team) {
    s32 i;
    s32 k;
    s32 done;
    CharActor* actor;
    s32 used[9];

    if (lbl_8036E548._2D8E == 0) {
        lbl_8036E548._2D8E = 1;
        lbl_8036E548.loadActor = -1;
        for (k = 0; k < 9; k++) {
            used[k] = 0;
        }
        for (i = 0; i <= 8; i++) {
            for (k = 0; k < 9; k++) {
                if (lbl_8036E548.active[i] != NULL && lbl_8036E548.active[i]->kind == lbl_8036E548._2D7F[k]) {
                    used[k] = 1;
                    break;
                }
            }
        }
        for (k = 0; k < 9; k++) {
            if (used[k] == 0) {
                lbl_8036E548._2D7F[k] = -1;
            }
        }
    }
    if (lbl_8036E548._2D8E == 1) {
        for (i = 0; i <= 8; i++) {
            for (k = 0; k < 9; k++) {
                if (lbl_8036E548.active[i]->kind == lbl_8036E548._2D7F[k]) {
                    lbl_8036E548.active[i]->banks.b[2] = lbl_8036E548.animBufs[5 + k];
                    break;
                }
            }
            if (k >= 9) {
                lbl_8036E548.loadStep = 0;
                lbl_8036E548._2D8E = 2;
                lbl_8036E548.loadActor = i;
                break;
            }
        }
        if (i > 8) {
            return 1;
        }
    }
    if (lbl_8036E548._2D8E == 2) {
        actor = &lbl_8036E548.actors[lbl_8036E548.active[lbl_8036E548.loadActor]->modelIndex];
        if (lbl_8036E548.loadStep == 0) {
            k = 0;
            if (lbl_8036E548._2D7F[0] >= 0) {
                k = 1;
                if (lbl_8036E548._2D7F[1] >= 0) {
                    k = 2;
                    if (lbl_8036E548._2D7F[2] >= 0) {
                        k = 3;
                        if (lbl_8036E548._2D7F[3] >= 0) {
                            k = 4;
                            if (lbl_8036E548._2D7F[4] >= 0) {
                                k = 5;
                                if (lbl_8036E548._2D7F[5] >= 0) {
                                    k = 6;
                                    if (lbl_8036E548._2D7F[6] >= 0) {
                                        k = 7;
                                        if (lbl_8036E548._2D7F[7] >= 0) {
                                            k = 8;
                                            if (lbl_8036E548._2D7F[8] >= 0) {
                                                k = 9;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            lbl_8036E548._2D7F[k] = actor->kind;
            if (lbl_8036E548._2D7C == 0) {
                actor->banks.b[2] = lbl_8036E548.animBufs[5 + k];
                ARAMTransfer(&lbl_803CB790[actor->kind * 0x13 + 4], actor->banks.b[2], 0, 0);
            } else {
                actor->banks.b[5] = lbl_8036E548.animBufs[5 + k];
                ARAMTransfer(&lbl_803CB790[actor->kind * 0x13 + 0x11], actor->banks.b[5], 0, 0);
            }
            lbl_8036E548.loadStep = 1;
            done = 0;
        } else if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            if (lbl_8036E548._2D7C == 0) {
                ANIMGet(actor->banks.b[2]);
            } else {
                ANIMGet(actor->banks.b[5]);
            }
            done = 1;
        } else {
            done = 0;
        }
        if (done) {
            lbl_8036E548._2D8E = 1;
        }
    }
    return 0;
}
#endif

// .text:0x8001594C size:0x9F8
// Attaches a CharPart (lbl_80118220) to each actor that needs one; returns
// TRUE once all lbl_803CBBF8 actors are done.
static inline BOOL attachActorParts(void) {
    CharActor* actor;
    CharPart* part;
    s32 idx;
    u8 kind;
    s32 k;
    s32 n;
    BOOL ok;
    BOOL done;

    if (lbl_803CB7C2 != 0) {
        lbl_803CB7C2 = 0;
        if (lbl_803CBC34[0] != 0) {
            lbl_803CBC2C = 0;
            lbl_803CBBF8 = 9;
        } else {
            if (lbl_803CBC34[1] != 0) {
                lbl_803CBC2C = 0;
                lbl_803CBBF8++;
            }
            if (lbl_803CBC34[2] != 0) {
                lbl_803CBBF8++;
                if (lbl_803CBC34[1] == 0) {
                    lbl_803CBC2C = 1;
                }
            }
        }
    }
    if (lbl_803CBBF8 == 0) {
        return TRUE;
    }
    idx = lbl_803CBBF0 + lbl_803CBC2C;
    actor = lbl_8036E548.active[idx];
    kind = actor->kind;
    if (lbl_803CBBF9 == 0) {
        for (k = 0; lbl_80118220[k]._61 != -2; k++) {
            if (kind == (s8)lbl_80118220[k].slot && lbl_80118220[k]._61 == -1) {
                part = &lbl_80118220[k];
                actor->part = part;
                part->slot = kind;
                part->_61 = idx;
                part->player.model = PTR32_GET(void, actor->files[4]);
                done = TRUE;
                goto next;
            }
        }
        lbl_803CBBF9 = 1;
        for (n = 0; lbl_80118220[n]._61 != -2; n++) {
            if (lbl_80118220[n]._61 == -1) {
                break;
            }
        }
        lbl_803CBC28 = n;
    }
    n = lbl_803CBC28;
    lbl_80118220[n].player.active = 0;
    if (lbl_800EEB18[kind] == -1 || actor->files[4] == NULL) {
        ok = TRUE;
        actor->part = NULL;
    } else {
        if (lbl_803CBBFA == 0) {
            fn_80021ADC(lbl_800EEB18[kind], lbl_80118220[n].files);
            lbl_803CBBFA = 1;
        }
        if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            part = &lbl_80118220[n];
            part->slot = kind;
            part->_61 = idx;
            part->player.set = (ShapeAnimSet*)part->files;
            fn_80025FFC(PTR32_GET(void, actor->files[4]), &part->player);
            actor->part = part;
            ok = TRUE;
            lbl_803CBBFA = 0;
        } else {
            ok = FALSE;
        }
    }
    if (ok) {
        done = TRUE;
        lbl_803CBBF9 = 0;
    } else {
        done = FALSE;
    }
next:
    if (done) {
        lbl_803CBBF0++;
    }
    if (lbl_803CBBF8 == lbl_803CBBF0) {
        lbl_803CBBF0 = 0;
        return TRUE;
    }
    return FALSE;
}

static inline BOOL setupActorModels(void) {
    if (fn_80013680(lbl_8036E548.active[lbl_803CBBF0])) {
        lbl_803CBBF0++;
    }
    if (lbl_803CBBF0 == 9) {
        lbl_803CBBF0 = 0;
        return TRUE;
    }
    return FALSE;
}

// NONMATCHING 92%: register allocation in the inlined part-attach state machine
#if NONMATCHING
s32 fn_8001594C(s32 team) {
    BattingOrder* order;
    s32 i;
    s32 k;

    if (lbl_8036E548.state == 1) {
        return 0;
    }
    if (lbl_8036E548.state == 2) {
        lbl_8036E548.active[lbl_8036E548._2D7A[1]] = &lbl_8036E548.actors[lbl_8036E548._2D79];
        lbl_8036E548.state = 0;
        lbl_8036E548._2D7A[1]++;
    }
    if (lbl_8036E548._2D7A[1] == 9) {
        lbl_8036E548._2D8E = 0;
        lbl_8036E548._2D7A[1] = 10;
    }
    if (lbl_8036E548._2D7C == 0) {
        if (lbl_8036E548._2D7A[1] == 10) {
            if (fn_80015468(team) == 0) {
                return 0;
            }
            lbl_8036E548._2D7A[1] = 11;
        }
        if (lbl_8036E548._2D7A[1] == 11) {
            if (!attachActorParts()) {
                return 0;
            }
            lbl_8036E548._2D7A[1] = 12;
        }
        if (lbl_8036E548._2D7A[1] == 12) {
            if (!setupActorModels()) {
                return 0;
            }
            return 1;
        }
    } else {
        if (lbl_8036E548._2D7A[1] == 10) {
            if (fn_80014A18() == 0) {
                return 0;
            }
            lbl_8036E548._2D7A[1] = 11;
        }
        if (lbl_8036E548._2D7A[1] == 11) {
            if (!attachActorParts()) {
                return 0;
            }
            lbl_8036E548._2D7A[1] = 12;
        }
        if (lbl_8036E548._2D7A[1] == 12) {
            if (!setupActorModels()) {
                return 0;
            }
            return 1;
        }
    }
    order = lbl_80354720[team];
    for (i = 0; i < 9; i++) {
        if (lbl_8036E548.active[i] == NULL) {
            continue;
        }
        for (k = 0; k < 9; k++) {
            if (lbl_8036E548.active[i]->kind == inMemRoster[team][order[k].roster].charId) {
                break;
            }
        }
        if (k >= 9) {
            fn_80011BE4(i);
        }
    }
    for (k = 0; k < 9; k++) {
        if ((s8)lbl_8036E548._2D7A[1] == order[k].pos) {
            break;
        }
    }
    if (fn_80017098(team, k, 0, lbl_8036E548._2D7A[1], 0, -1) != 0) {
        lbl_8036E548.state = 2;
    }
    return 0;
}
#endif

// .text:0x80016344 size:0x3CC
// NONMATCHING 91%: register allocation / state-machine scheduling
#if NONMATCHING
s32 fn_80016344(u8 kind, s32 index, u8 arg2, s32 roster) {
    CharActor* actor;
    BOOL ok;

    if (lbl_8036E548.state == 6) {
        return 1;
    }
    if (lbl_8036E548.state == 1) {
        return 0;
    }
    if (lbl_8036E548.state == 2) {
        lbl_8036E548.active[index] = &lbl_8036E548.actors[index];
        lbl_8036E548.active[index]->_25A = arg2;
        lbl_8036E548.active[index]->_25B = arg2;
        lbl_8036E548.loadStep = 0;
        lbl_8036E548.state = 3;
    }
    if (lbl_8036E548.state == 3) {
        if (index == 12) {
            actor = &lbl_8036E548.actors[index];
            if (lbl_8036E548.loadStep == 0) {
                lbl_8036E548.loadStep = 1;
                lbl_8036E548._2D7F[index] = actor->kind;
                actor->banks.b[5] = lbl_8036E548.animBufs[4];
                ARAMTransfer(&lbl_803CB790[actor->kind * 0x13 + 0x11], actor->banks.b[5], 0, 0);
                ok = FALSE;
            } else if ((s32)(u8)lbl_803C6CF8.idle == 1) {
                ANIMGet(actor->banks.b[5]);
                ok = TRUE;
            } else {
                ok = FALSE;
            }
            if (!ok) {
                return 0;
            }
        } else {
            actor = &lbl_8036E548.actors[index];
            if (lbl_8036E548.loadStep == 0) {
                lbl_8036E548.loadStep = 1;
                lbl_8036E548._2D7F[index] = actor->kind;
                if (g_d_GameSettings.GameModeSelected == 2) {
                    actor->banks.b[5] = lbl_8036E548.animBufs[0];
                    fn_80021BBC(actor->kind, actor->banks.b[5]);
                } else if (index >= 9) {
                    actor->banks.b[5] = lbl_8036E548.animBufs[0];
                    ARAMTransfer(&lbl_803CB790[actor->kind * 0x13 + 0x10], actor->banks.b[5], 0, 0);
                } else {
                    actor->banks.b[5] = lbl_8036E548.bankSets[index][4];
                    fn_80021BBC(actor->kind, actor->banks.b[5]);
                }
                ok = FALSE;
            } else if ((s32)(u8)lbl_803C6CF8.idle == 1) {
                ANIMGet(actor->banks.b[5]);
                ok = TRUE;
            } else {
                ok = FALSE;
            }
            if (!ok) {
                return 0;
            }
        }
        lbl_8036E548.state = 4;
    }
    if (lbl_8036E548.state == 4) {
        if (lbl_800EEB18[kind] == -1 || lbl_8036E548.actors[index].files[4] == NULL) {
            lbl_8036E548.actors[index].part = NULL;
            ok = TRUE;
        } else {
            if (lbl_803CBBFA == 0) {
                fn_80021ADC(lbl_800EEB18[kind], lbl_80118220[0].files);
                lbl_803CBBFA = 1;
            }
            if ((s32)(u8)lbl_803C6CF8.idle == 1) {
                lbl_80118220[0].slot = kind;
                lbl_80118220[0]._61 = index;
                lbl_80118220[0].player.set = (ShapeAnimSet*)lbl_80118220[0].files;
                fn_80025FFC(PTR32_GET(void, lbl_8036E548.actors[index].files[4]), &lbl_80118220[0].player);
                lbl_803CBBFA = 0;
                lbl_8036E548.actors[index].part = &lbl_80118220[0];
                ok = TRUE;
            } else {
                ok = FALSE;
            }
        }
        if (!ok) {
            return 0;
        }
        lbl_8036E548.state = 5;
    }
    if (lbl_8036E548.state == 5) {
        if (!fn_80013680(&lbl_8036E548.actors[index])) {
            return 0;
        }
        lbl_8036E548.state = 0;
        return 1;
    }
    fn_80017098(0, roster, 1, index, 1, kind);
    return 0;
}
#endif

// .text:0x80016710 size:0x450
// NONMATCHING 86%: register allocation / stub callee inlining (fn_80012B90, fn_80013680)
#if NONMATCHING
s32 fn_80016710(u8 kind, s32 index) {
    CharActor* actor;
    CharPart* part;
    BOOL ok;

    if (lbl_8036E548.state == 6) {
        return 1;
    }
    if (lbl_8036E548.state == 1) {
        return 0;
    }
    if (lbl_8036E548.state == 2) {
        lbl_8036E548.active[index] = &lbl_8036E548.actors[index];
        lbl_8036E548.loadStep = 0;
        lbl_8036E548.state = 3;
    }
    if (lbl_8036E548.state == 3) {
        actor = &lbl_8036E548.actors[index];
        if (lbl_8036E548.loadStep == 0) {
            lbl_8036E548.loadStep = 1;
            lbl_8036E548._2D7F[index] = actor->kind;
            if (g_d_GameSettings.GameModeSelected == 2) {
                actor->banks.b[5] = lbl_8036E548.animBufs[0];
                fn_80021BBC(actor->kind, actor->banks.b[5]);
            } else if (index >= 9) {
                actor->banks.b[5] = lbl_8036E548.animBufs[0];
                ARAMTransfer(&lbl_803CB790[actor->kind * 0x13 + 0x10], actor->banks.b[5], 0, 0);
            } else {
                actor->banks.b[5] = lbl_8036E548.bankSets[index][4];
                fn_80021BBC(actor->kind, actor->banks.b[5]);
            }
            ok = FALSE;
        } else if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            ANIMGet(actor->banks.b[5]);
            ok = TRUE;
        } else {
            ok = FALSE;
        }
        if (!ok) {
            return 0;
        }
        lbl_8036E548.state = 4;
    }
    if (lbl_8036E548.state == 4) {
        if (g_d_GameSettings.GameModeSelected == 2) {
            if (lbl_800EEB18[kind] == -1 || lbl_8036E548.actors[index].files[4] == NULL) {
                lbl_8036E548.actors[index].part = NULL;
                ok = TRUE;
            } else {
                if (lbl_803CBBFA == 0) {
                    fn_80021ADC(lbl_800EEB18[kind], lbl_80118220[0].files);
                    lbl_803CBBFA = 1;
                }
                if ((s32)(u8)lbl_803C6CF8.idle == 1) {
                    lbl_80118220[0].slot = kind;
                    lbl_80118220[0]._61 = index;
                    lbl_80118220[0].player.set = (ShapeAnimSet*)lbl_80118220[0].files;
                    fn_80025FFC(PTR32_GET(void, lbl_8036E548.actors[index].files[4]), &lbl_80118220[0].player);
                    lbl_803CBBFA = 0;
                    lbl_8036E548.actors[index].part = &lbl_80118220[0];
                    ok = TRUE;
                } else {
                    ok = FALSE;
                }
            }
            if (!ok) {
                return 0;
            }
        } else {
            if (lbl_800EEB18[kind] == -1 || lbl_8036E548.actors[index].files[4] == NULL) {
                lbl_8036E548.actors[index].part = NULL;
                ok = TRUE;
            } else {
                if (lbl_803CBBFA == 0) {
                    fn_80021ADC(lbl_800EEB18[kind], lbl_80118220[index].files);
                    lbl_803CBBFA = 1;
                }
                if ((s32)(u8)lbl_803C6CF8.idle == 1) {
                    part = &lbl_80118220[index];
                    part->slot = kind;
                    part->_61 = index;
                    part->player.set = (ShapeAnimSet*)part->files;
                    fn_80025FFC(PTR32_GET(void, lbl_8036E548.actors[index].files[4]), &part->player);
                    lbl_803CBBFA = 0;
                    lbl_8036E548.actors[index].part = part;
                    ok = TRUE;
                } else {
                    ok = FALSE;
                }
            }
            if (!ok) {
                return 0;
            }
        }
        lbl_8036E548.state = 5;
    }
    if (lbl_8036E548.state == 5) {
        if (g_d_GameSettings.GameModeSelected == 2) {
            if (!fn_80013680(&lbl_8036E548.actors[index])) {
                return 0;
            }
        } else {
            if (!fn_80012B90(&lbl_8036E548.actors[index])) {
                return 0;
            }
        }
        return 1;
    }
    fn_80017098(0, 0, 0, index, 1, kind);
    return 0;
}
#endif

// .text:0x80016B60 size:0x41C
s32 fn_80016B60(CharActor* actor) {
    s32 file;

    if (lbl_8036E548.loadStep == 0) {
        lbl_8036E548.loadStep = 1;
    }
    if (lbl_8036E548.loadStep == 1) {
        actor->banks.b[2] = lbl_8036E548.bankSets[actor->modelIndex][0];
        if (g_d_GameSettings.GameModeSelected == 7) {
            file = actor->kind * 0x13 + 0xD;
        } else {
            file = actor->kind * 0x13 + 4;
        }
        ARAMTransfer(&lbl_803CB790[file], actor->banks.b[2], 0, 0);
        lbl_8036E548.loadStep = 2;
    } else if (lbl_8036E548.loadStep == 2) {
        if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            ANIMGet(actor->banks.b[2]);
            lbl_8036E548.loadStep = 3;
        }
    } else if (lbl_8036E548.loadStep == 3) {
        actor->banks.b[1] = lbl_8036E548.bankSets[actor->modelIndex][1];
        if (g_d_GameSettings.GameModeSelected == 2) {
            file = actor->kind * 0x13 + 0xB;
        } else if (g_d_GameSettings.GameModeSelected == 6) {
            file = actor->kind * 0x13 + 0xE;
        } else {
            file = actor->kind * 0x13 + 0xC;
        }
        ARAMTransfer(&lbl_803CB790[file], actor->banks.b[1], 0, 0);
        lbl_8036E548.loadStep = 4;
    } else if (lbl_8036E548.loadStep == 4) {
        if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            ANIMGet(actor->banks.b[1]);
            lbl_8036E548.loadStep = 5;
        }
    } else if (lbl_8036E548.loadStep == 5) {
        actor->banks.b[3] = lbl_8036E548.bankSets[actor->modelIndex][2];
        if (g_d_GameSettings.minigamesEnabled != 0 || g_d_GameSettings.GameModeSelected == 2) {
            file = actor->kind * 0x13 + 0x12;
        } else {
            file = actor->kind * 0x13 + 5;
        }
        ARAMTransfer(&lbl_803CB790[file], actor->banks.b[3], 0, 0);
        lbl_8036E548.loadStep = 6;
    } else if (lbl_8036E548.loadStep == 6) {
        if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            ANIMGet(actor->banks.b[3]);
            actor->banks.b[0] = lbl_8036E548.bankSets[0][3];
            lbl_8036E548.loadStep = 9;
        }
    } else if (lbl_8036E548.loadStep == 7) {
        actor->banks.b[0] = lbl_8036E548.bankSets[actor->modelIndex][3];
        if (g_d_GameSettings.GameModeSelected == 7) {
            file = actor->kind * 0x13 + 9;
        } else if (g_d_GameSettings.GameModeSelected == 2) {
            file = actor->kind * 0x13 + 0xA;
        } else {
            file = actor->kind * 0x13 + 2;
        }
        ARAMTransfer(&lbl_803CB790[file], actor->banks.b[0], 0, 0);
        lbl_8036E548.loadStep = 8;
    } else if (lbl_8036E548.loadStep == 8) {
        if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            ANIMGet(actor->banks.b[0]);
            lbl_8036E548.loadStep = 9;
        }
    } else if (lbl_8036E548.loadStep == 9) {
        actor->banks.b[5] = lbl_8036E548.bankSets[actor->modelIndex][4];
        ARAMTransfer(&lbl_803CB790[actor->kind * 0x13 + 0x10], actor->banks.b[5], 0, 0);
        lbl_8036E548.loadStep = 10;
    } else if (lbl_8036E548.loadStep == 10) {
        if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            ANIMGet(actor->banks.b[5]);
            lbl_8036E548.loadStep = 0;
            return 1;
        }
    }
    return 0;
}

// .text:0x80016F7C size:0x11C
s32 fn_80016F7C(void) {
    CharActor* src;
    CharActor* dst;

    if (lbl_8036E548._2D8E == 0) {
        lbl_8036E548._2D8E = 1;
        lbl_8036E548.loadStep = 0;
        lbl_8036E548.loadActor = 0;
    }
    do {
        if (fn_80016B60(&lbl_8036E548.actors[lbl_8036E548.loadActor]) == 0) {
            goto fail;
        }
        if (g_d_GameSettings.GameModeSelected == 6) {
            src = &lbl_8036E548.actors[lbl_8036E548.loadActor];
            dst = &lbl_8036E548.actors[lbl_8036E548.loadActor + 4];
            dst->banks.b[0] = src->banks.b[0];
            dst->banks.b[1] = src->banks.b[1];
            dst->banks.b[2] = src->banks.b[2];
            dst->banks.b[3] = src->banks.b[3];
            dst->banks.b[4] = src->banks.b[4];
            dst->banks.b[5] = src->banks.b[5];
            dst->banks.b[6] = src->banks.b[6];
        }
        lbl_8036E548.loadActor++;
    } while (lbl_8036E548.loadActor < 4);
    return 1;
fail:
    return 0;
}

// .text:0x80017098 size:0x2A8
// NONMATCHING 87%: roster-entry field addresses are hoisted differently
#if NONMATCHING
s32 fn_80017098(s32 team, s32 roster, s32 arg2, s32 index, s32 arg4, s32 kind) {
    CharLoadTask* task;
    RosterEntry* entry;
    CharActor* actor;
    s32 same;
    s32 slot;
    s32 i;
    s32 j;

    if (kind >= 0) {
        task = fn_800B0A5C_insertQueue(fn_800177B4, 0);
        slot = index;
        goto setup;
    }
    entry = &inMemRoster[team][roster];
    for (i = 0; i < 13; i++) {
        actor = &lbl_8036E548.actors[i];
        same = 0;
        if (actor->kind == entry->charId && actor->_25A == entry->_26 && actor->_25B == entry->_27 && actor->roster == (s8)roster) {
            same = 1;
        }
        if (actor->team == team && same && actor->_258 == arg2 && actor->_259 == arg4) {
            lbl_8036E548.state = 0;
            lbl_8036E548._2D6A[i] = index;
            lbl_8036E548._2D79 = i;
            actor->index = index;
            for (j = 0; j < 13; j++) {
                if (lbl_8036E548.active[j] == actor) {
                    lbl_8036E548.active[j] = NULL;
                    break;
                }
            }
            lbl_8036E548.active[index] = actor;
            return 1;
        }
    }
    task = fn_800B0A5C_insertQueue(fn_800177B4, 0);
    if (index >= 9) {
        slot = 9;
        if (lbl_8036E548._2D6A[9] >= 0) {
            slot = 10;
            if (lbl_8036E548._2D6A[10] >= 0) {
                slot = 11;
                if (lbl_8036E548._2D6A[11] >= 0) {
                    slot = 12;
                    if (lbl_8036E548._2D6A[12] >= 0) {
                        slot = 13;
                    }
                }
            }
        }
    } else {
        for (slot = 0; slot < 13; slot++) {
            if (lbl_8036E548._2D6A[slot] < 0) {
                break;
            }
        }
    }
setup:
    task->state = 0;
    task->actor = slot;
    task->team = team;
    task->roster = roster;
    task->_1B = arg2;
    task->index = index;
    task->_1D = arg4;
    if (kind < 0) {
        task->kind = inMemRoster[team][roster].charId;
    } else {
        task->kind = kind;
    }
    lbl_8036E548._2D6A[slot] = index;
    lbl_8036E548.state = 1;
    lbl_8036E548._2D79 = slot;
    return 0;
}
#endif

// .text:0x80017340 size:0x24C
// NONMATCHING 78%: loop induction variables (original indexes active[i + 9] per pass)
#if NONMATCHING
s32 fn_80017340(s32 actorIdx) {
    CharActor* actor = &lbl_8036E548.actors[actorIdx];
    s32 used[4];
    CharActor* other;
    s32 i;
    s32 j;
    s32 k;
    s32 file;

    if (lbl_8036E548.loadStep == 0) {
        used[0] = 0;
        used[1] = 0;
        used[2] = 0;
        used[3] = 0;
        for (i = 0; i < 4; i++) {
            j = i + 9;
            for (k = 0; k < 4; k++) {
                other = lbl_8036E548.active[j];
                if (other != NULL) {
                    if (actor->kind == lbl_8036E548.bankOwner[k]) {
                        actor->banks.b[1] = lbl_8036E548.animBufs[k + 1];
                        return 1;
                    }
                    if (other->kind == lbl_8036E548.bankOwner[k]) {
                        used[k] = 1;
                        break;
                    }
                }
            }
        }
        if (used[0] == 0) {
            lbl_8036E548.bankOwner[0] = -1;
        }
        if (used[1] == 0) {
            lbl_8036E548.bankOwner[1] = -1;
        }
        if (used[2] == 0) {
            lbl_8036E548.bankOwner[2] = -1;
        }
        if (used[3] == 0) {
            lbl_8036E548.bankOwner[3] = -1;
        }
        k = 0;
        if (lbl_8036E548.bankOwner[0] >= 0) {
            k = 1;
            if (lbl_8036E548.bankOwner[1] >= 0) {
                k = 2;
                if (lbl_8036E548.bankOwner[2] >= 0) {
                    k = 3;
                    if (lbl_8036E548.bankOwner[3] >= 0) {
                        k = 4;
                    }
                }
            }
        }
        lbl_8036E548.bankOwner[k] = actor->kind;
        actor->banks.b[1] = lbl_8036E548.animBufs[k + 1];
        if (g_d_GameSettings.GameModeSelected == 2) {
            file = actor->kind * 0x13 + 0xB;
        } else {
            file = actor->kind * 0x13 + 3;
        }
        ARAMTransfer(&lbl_803CB790[file], actor->banks.b[1], 0, 0);
        lbl_8036E548.loadStep = 1;
    } else if ((s32)(u8)lbl_803C6CF8.idle == 1) {
        ANIMGet(actor->banks.b[1]);
        return 1;
    }
    return 0;
}
#endif

// .text:0x8001758C size:0x228
// NONMATCHING 98.2%: actor->kind reload scheduled later, r9/r11 swap
#if NONMATCHING
s32 fn_8001758C(u8* state, s32 actorIdx, u8 kind, u8 team, u8 roster, s8 arg5, u8 index, u8 arg7) {
    CharActor* actor = &lbl_8036E548.actors[actorIdx];
    s32 file;

    switch (*state) {
    case 0:
        if ((s32)(u8)lbl_803C6CF8.idle != 1) {
            break;
        }
        actor->_25C = 1;
        actor->team = team;
        actor->roster = roster;
        actor->index = index;
        actor->kind = kind;
        actor->_258 = arg5;
        actor->_259 = arg7;
        actor->_25A = inMemRoster[team][roster]._26;
        file = actor->kind * 0x13;
        actor->_25B = inMemRoster[team][roster]._27;
        actor->_278 = (index == 9);
        if (arg7 == 0) {
            file += 1;
        }
        if (actor->_278 != 0 && arg7 == 1 && lbl_8036E548.preload[2].id == kind) {
            memcpy(actor->files, lbl_8036E548.preload[2].buffer, lbl_8036E548.preload[2].size);
            goto load;
        }
        if (index >= 10 && index <= 12 && arg7 == 0 && lbl_8036E548.preload[0].id == kind) {
            memcpy(actor->files, lbl_8036E548.preload[0].buffer, lbl_8036E548.preload[0].size);
            goto load;
        }
        if (arg7 == 0 || fn_8002204C(actor->kind, actor->files) == 0) {
            ARAMTransfer(&lbl_803CB790[file], actor->files, 0, 0);
        }
        *state = 1;
        break;
    case 1:
        if (lbl_803716B8.keepTask == 0 && (s32)(u8)lbl_803C6CF8.idle == 1) {
        load:
            fn_80017814(actor, actor->modelIndex, index, fn_8001FDD4);
            return 1;
        }
        break;
    }
    return 0;
}
#endif

// .text:0x800177B4 size:0x60
void fn_800177B4(void) {
    CharLoadTask* task = lbl_803CC1B8;

    if (fn_8001758C(&task->state, task->actor, task->kind, task->team, (s32)task->roster, task->_1B, task->index, task->_1D) != 0) {
        lbl_8036E548.state = 2;
        fn_800B0A14_removeQueue(&lbl_8036E548);
    }
}

// .text:0x80017814 size:0x514
// NONMATCHING 93.2%: register allocation (joint temps, relocation base)
#if NONMATCHING
void fn_80017814(CharActor* actor, s32 modelIndex, s32 index, void (*callback)(ActorObject*)) {
    ActorObject* slot = &lbl_8036E548.slots->objects[modelIndex];
    PTR32(void)* files = actor->files;
    void* tex;
    void* layout;
    void* geo;
    void* skn;
    void* bank;
    s32 count;
    s32 i;
    s32 j;

    // TODO(port): the file header holds 32-bit offsets relocated in place; on PC
    // void* entries are 8 bytes, so these tables need PTR32 entries (Phase 3).
#ifdef TARGET_PC
    port_swap_offset_table(files, 5);
    if (files[0] != 0) {
        actor->files[0] += PTR_TO_U32(files);
        if (actor->files[1] != 0) {
            actor->files[1] += PTR_TO_U32(files);
            if (actor->files[2] != 0) {
                actor->files[2] += PTR_TO_U32(files);
                if (actor->files[3] != 0) {
                    actor->files[3] += PTR_TO_U32(files);
                    if (actor->files[4] != 0) {
                        actor->files[4] += PTR_TO_U32(files);
                    }
                }
            }
        }
    }
#else
    if (files[0] != NULL) {
        actor->files[0] = (u8*)files + (uintptr_t)files[0];
        if (actor->files[1] != NULL) {
            actor->files[1] = (u8*)files + (uintptr_t)files[1];
            if (actor->files[2] != NULL) {
                actor->files[2] = (u8*)files + (uintptr_t)files[2];
                if (actor->files[3] != NULL) {
                    actor->files[3] = (u8*)files + (uintptr_t)files[3];
                    if (actor->files[4] != NULL) {
                        actor->files[4] = (u8*)files + (uintptr_t)files[4];
                    }
                }
            }
        }
    }
#endif
    tex = PTR32_GET(void, actor->files[0]);
    convertTextureHeader(tex);
    if (actor->files[1] != NULL) {
        layout = PTR32_GET(void, actor->files[1]);
        geo = PTR32_GET(void, actor->files[2]);
        skn = PTR32_GET(void, actor->files[3]);
        LoadActorLayout(layout);
        convertGeometryAndSknHeader(geo, skn);
        haveActLayoutPointToGeoHeader(layout, geo);
        fn_800BD190(geo, tex);
    } else {
        return;
    }
    if (index < 9) {
        bank = actor->banks.b[2];
    } else {
        bank = actor->banks.b[1];
    }
    fn_8002399C(slot, actor->modelIndex, (u16)modelIndex, layout, bank, skn);
    if (actor->files[4] != NULL) {
        fn_80025DDC(PTR32_GET(void, actor->files[4]));
        fn_80025C58(PTR32_GET(void, actor->files[4]), (ShapeModel**)slot);
    }
    count = slot->actor->totalBones;
    memset(actor->jointIdx, 0xFF, sizeof(actor->jointIdx));
    for (i = 0; i < count; i++) {
        if (slot->actor->boneArray[i]->boneID != 0xFFFF) {
            actor->jointIdx[slot->actor->boneArray[i]->boneID] = i;
        }
    }
    fn_800B2B74(slot->actor, actor->jointIdx[19]);
    fn_800B2B74(slot->actor, actor->jointIdx[25]);
    fn_800B2B74(slot->actor, actor->jointIdx[36]);
    actor->model = slot->actor;
    j = actor->jointIdx[3];
    if (j != 0xFFFF) {
        fn_800B2B54(actor->model, j, 0xD);
    }
    fn_800BD548(slot, 4, lbl_8036E548.lights[0], lbl_8036E548.lights[1], lbl_8036E548.lights[2], lbl_8036E548.lights[3]);
    CTRLSetTranslation(&slot->worldControl.base, 0.0f, 0.0f, 0.0f);
    CTRLSetRotation(&slot->worldControl.base, 0.0f, 0.0f, 0.0f);
    slot->unk54 = 0.5f;
    slot->setSpeed = 1;
    j = actor->jointIdx[3];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->actor, j, 0, 0);
        slot->actor->boneArray[(u16)j]->stepTranslation = 1;
    }
    j = actor->jointIdx[2];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->actor, j, 0, 0);
        slot->actor->boneArray[(u16)j]->stepTranslation = 1;
    }
    j = actor->jointIdx[1];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->actor, j, 0, 0);
        slot->actor->boneArray[(u16)j]->stepTranslation = 1;
    }
    j = actor->jointIdx[36];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->actor, j, 0, 0);
    }
    j = actor->jointIdx[46];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->actor, j, 0, 0);
        slot->actor->boneArray[(u16)j]->stepTranslation = 1;
    }
    fn_800B2C08(slot->actor, actor->jointIdx[4]);
    fn_8001FC4C(actor);
    slot->callback = callback;
    actor->_060 = -1;
    actor->anim[0] = -1;
    actor->anim[1] = -1;
    actor->anim[2] = -1;
    actor->_068 = -1;
    actor->_06A[0] = -1;
    actor->_06A[1] = -1;
    actor->_06A[2] = -1;
    actor->mode[0] = 0;
    actor->mode[1] = 0;
    actor->_25F[0] = 0;
    actor->_25F[1] = 0;
    actor->_25F[2] = 0;
    actor->_262[0] = 0;
    actor->_262[1] = 0;
    actor->_262[2] = 0;
    actor->_265[0] = 0;
    actor->_265[1] = 0;
    actor->_265[2] = 0;
    actor->_268 = 0;
    actor->_269[0] = 0;
    actor->_269[1] = 0;
    actor->_269[2] = 0;
    actor->_26C[0] = 0;
    actor->_26C[1] = 0;
    actor->_26C[2] = 0;
    actor->_270[0] = 0;
    actor->_270[1] = 0;
    actor->_270[2] = 0;
    actor->_273 = 0;
    actor->_277 = 0xFF;
    switch (actor->kind) {
    case 2:
        fn_800638B4(actor, slot);
        break;
    case 33:
    case 34:
    case 35:
    case 36:
        fn_80063010(actor, slot);
        break;
    case 19:
        fn_8004B7B4(actor, slot);
        break;
    case 12:
    case 21:
    case 22:
    case 23:
    case 42:
        slot->actor->tickFlag = 1;
        break;
    case 24:
    case 25:
    case 26:
        slot->actor->tickFlag = 1;
        break;
    case 20:
    case 43:
        fn_800637BC(actor, slot);
        break;
    case 38:
        slot->actor->tickFlag = 1;
        fn_8004BD6C(actor, slot);
        break;
    case 41:
        fn_800637D4(actor, slot);
    case 18:
    case 40:
        fn_8004BD6C(actor, slot);
        break;
    case 14:
    case 37:
        fn_80052634(actor, slot);
        break;
    case 16:
    case 44:
    case 45:
    case 46:
    case 47:
        fn_80062ED4(actor, slot);
        break;
    }
}
#endif

// .text:0x80017D28 size:0x94
void fn_80017D28(CharActor* src) {
    s32 modelIndex = src->modelIndex + 4;
    CharActor* dst = &lbl_8036E548.actors[modelIndex];

    dst->kind = src->kind;
    dst->index = src->index;
    dst->modelIndex = modelIndex;
    dst->_25C = 1;
    dst->mode[0] = 0;
    dst->parts = src->parts;
    dst->_25A = src->_25A;
    dst->_25B = src->_25B;
    dst->files = src->_0C;
    fn_80017814(dst, modelIndex, 0, fn_8001FDD4);
}

// .text:0x80017DBC size:0x268
// NONMATCHING 97.4%: argument load order around fn_800B2B74
#if NONMATCHING
void fn_80017DBC(CharActor* actor, s32 modelIndex) {
    ActorObject* slot = &lbl_8036E548.slots->objects[modelIndex];

    initModelJoints(actor, slot);
    switch (actor->kind) {
    case 2:
        fn_800638B4(actor, slot);
        break;
    case 33:
    case 34:
    case 35:
    case 36:
        fn_80063010(actor, slot);
        break;
    case 19:
        fn_8004B7B4(actor, slot);
        break;
    case 20:
    case 43:
        fn_800637BC(actor, slot);
        break;
    case 38:
        slot->actor->tickFlag = 1;
        fn_8004BD6C(actor, slot);
        break;
    case 41:
        fn_800637D4(actor, slot);
    case 18:
    case 40:
        fn_8004BD6C(actor, slot);
        break;
    case 14:
    case 37:
        fn_80052634(actor, slot);
        break;
    case 16:
    case 44:
    case 45:
    case 46:
    case 47:
        fn_80062ED4(actor, slot);
        break;
    }
}
#endif

// .text:0x80018024 size:0x24C
// NONMATCHING 76%: original indexes the ARAM table with lwzx instead of strength-reduced pointers
#if NONMATCHING
void fn_80018024(void) {
    u32 max0 = 0;
    u32 max1 = 0;
    u32 size;
    u32 size0;
    u32 size1;
    s32 k;
    s32 i;
    u8* p;

    for (k = 0; k < 54 * 0x13; k += 0x13) {
        size = lbl_803CB790[k].sizeFlags & 0x0FFFFFFF;
        if (max0 < size) {
            max0 = size;
        }
        size = lbl_803CB790[k + 1].sizeFlags & 0x0FFFFFFF;
        if (max1 < size) {
            max1 = size;
        }
    }
    size0 = (max0 + 0x1F) & ~0x1F;
    lbl_8036E548._2D64 = size0;
    size1 = (max1 + 0x1F) & ~0x1F;
    if (g_d_GameSettings.GameModeSelected == 6) {
        lbl_8036E548.fileBuf = _OSAllocFromHeap(0x20, (size0 + size1) * 4);
    } else {
        lbl_8036E548.fileBuf = _OSAllocFromHeap(0x20, size0 * 4);
    }
    p = lbl_8036E548.fileBuf;
    if (g_d_GameSettings.GameModeSelected == 6) {
        for (i = 0; i < 4; i++) {
            lbl_8036E548.actors[i].files = (void**)p;
            p += size0;
            lbl_8036E548.actors[i].part = NULL;
            lbl_8036E548.actors[i].parts = NULL;
            lbl_8036E548.actors[i]._0C = (void**)p;
            p += size1;
            lbl_8036E548.actors[i + 4].part = NULL;
            lbl_8036E548.actors[i + 4].parts = NULL;
        }
    } else {
        for (i = 0; i < 4; i++) {
            lbl_8036E548.actors[i].files = (void**)p;
            p += size0;
            lbl_8036E548.actors[i].part = NULL;
            lbl_8036E548.actors[i].parts = NULL;
        }
    }
}
#endif

// .text:0x80018270 size:0x650
// NONMATCHING 87%: max-size loops unrolled/scheduled differently
#if NONMATCHING
void fn_80018270(s32 mode) {
    u32 max1 = 0;
    u32 max0 = 0;
    u32 size;
    u32 s0;
    u32 s1;
    u32 total;
    s32 i;
    s32 t;
    s32 k;
    u8* p;

    if (mode == 2) {
        p = _OSAllocFromHeap(0x20, 0x13E80);
        lbl_8036E548.fileBuf = p;
        lbl_8036E548.actors[0].files = (void**)p;
        for (i = 1; i < 9; i++) {
            lbl_8036E548.actors[i].files = _OSAllocFromHeap(0x20, 0x12C40);
        }
        for (k = 0; k < 54; k++) {
            size = lbl_803CB790[k * 0x13].sizeFlags & 0x0FFFFFFF;
            if (max0 < size) {
                max0 = size;
            }
        }
        s0 = (max0 + 0x1F) & ~0x1F;
        total = s0 * 4 + 0x13E80;
        p = _OSAllocFromHeap(0x20, total);
        lbl_8036E548.actors[10].files = (void**)(p + s0);
        lbl_8036E548.actors[11].files = (void**)(p + s0 * 2);
        lbl_8036E548.actors[12].files = (void**)(p + s0 * 3);
        lbl_8036E548._2D64 = total;
        lbl_8036E548.actors[9].files = (void**)p;
        lbl_8036E548.preload[0].buffer = p + s0 * 4;
        lbl_8036E548.preload[0].size = 0x13E80;
        lbl_8036E548.preload[0].id = -1;
        lbl_8036E548.preload[0].state = 0;
    } else {
        if (mode == 0) {
            for (t = 0; t < 2; t++) {
                for (i = 0; i < 9; i++) {
                    size = lbl_803CB790[inMemRoster[t][i].charId * 0x13].sizeFlags & 0x0FFFFFFF;
                    if (max0 < size) {
                        max0 = size;
                    }
                }
            }
            for (t = 0; t < 2; t++) {
                for (i = 0; i < 9; i++) {
                    size = lbl_803CB790[inMemRoster[t][i].charId * 0x13 + 1].sizeFlags & 0x0FFFFFFF;
                    if (max1 < size) {
                        max1 = size;
                    }
                }
            }
        } else {
            for (k = 0; k < 54; k++) {
                size = lbl_803CB790[k * 0x13].sizeFlags & 0x0FFFFFFF;
                if (max0 < size) {
                    max0 = size;
                }
            }
            for (k = 0; k < 54; k++) {
                size = lbl_803CB790[k * 0x13 + 1].sizeFlags & 0x0FFFFFFF;
                if (max1 < size) {
                    max1 = size;
                }
            }
        }
        s1 = (max1 + 0x1F) & ~0x1F;
        s0 = (max0 + 0x1F) & ~0x1F;
        total = s1 * 9 + s0 * 4 + s0 + s1;
        p = _OSAllocFromHeap(0x20, total);
        lbl_8036E548.fileBuf = p;
        lbl_8036E548._2D64 = total;
        for (i = 0; i < 9; i++) {
            lbl_8036E548.actors[i].files = (void**)p;
            p += s1;
        }
        lbl_8036E548.actors[9].files = (void**)p;
        p += s0;
        lbl_8036E548.actors[10].files = (void**)p;
        p += s0;
        lbl_8036E548.actors[11].files = (void**)p;
        p += s0;
        lbl_8036E548.actors[12].files = (void**)p;
        p += s0;
        lbl_8036E548.preload[2].buffer = p;
        lbl_8036E548.preload[2].size = s0;
        lbl_8036E548.preload[2].id = -1;
        lbl_8036E548.preload[2].state = 0;
        lbl_8036E548.preload[0].buffer = p + s0;
        lbl_8036E548.preload[0].size = s1;
        lbl_8036E548.preload[0].id = -1;
        lbl_8036E548.preload[0].state = 0;
    }
    for (i = 0; i < 13; i++) {
        lbl_8036E548.actors[i].part = NULL;
        lbl_8036E548.actors[i].parts = NULL;
    }
}
#endif

// .text:0x800188C0 size:0xF8
void fn_800188C0(void) {
    CharLoadTask* task = lbl_803CC1B8;

    switch (task->state) {
    case 0:
        if (g_d_GameSettings.GameModeSelected == 6) {
            lbl_8036E548.stadiumFiles = ARAMTransfer(&lbl_800EE910[1], NULL, 0, 0);
        } else {
            lbl_8036E548.stadiumFiles = ARAMTransfer(&lbl_800EE910[0], NULL, 0, 0);
        }
        task->state++;
        break;
    case 1:
        if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            task->state++;
        }
        break;
    case 2:
        lbl_8036E548._307B = 0;
        fn_800B0A14_removeQueue(&lbl_8036E548);
        break;
    }
}

// .text:0x800189B8 size:0x2C
void fn_800189B8(void) {
    fn_800ACFB0(lbl_8036E548._2C88);
}

// .text:0x800189E4 size:0x154
void fn_800189E4(void) {
    u32 max = 0;
    u32 size;
    s32 i;
    u8* buf;

    for (i = 0; i < 54; i++) {
        size = lbl_803CB790[i * 0x13 + 0xF].sizeFlags & 0x0FFFFFFF;
        if (max < size) {
            max = size;
        }
    }
    size = (max + 0x1F) & ~0x1F;
    lbl_8036E548._2CA4 = size;
    buf = _OSAllocFromHeap(0x20, size * 4);
    lbl_8036E548._2C88 = buf;
    for (i = 0; i < 4; i++) {
        lbl_8036E548.bankSets[i][4] = buf;
        lbl_8036E548.actors[i].banks.b[5] = NULL;
        buf += size;
    }
}

// .text:0x80018B38 size:0x3C
void fn_80018B38(void) {
    fn_800ACFB0(lbl_8036E548._2C88);
    lbl_8036E548._2D68 = -1;
}

// .text:0x80018B74 size:0x278
// NONMATCHING 95.7%: size temporaries register allocation
#if NONMATCHING
void fn_80018B74(void) {
    u32 max0 = 0;
    u32 max1 = 0;
    u32 max2 = 0;
    u32 max3 = 0;
    u32 max4 = 0;
    u32 size;
    u32 s0;
    u32 s1;
    u32 s2;
    u32 s3;
    u32 s4;
    u32 total;
    s32 k;
    s32 m;
    u8* p;
    DiskFileEntry* f;

    f = lbl_803CB790;
    for (k = 0; k < 54; k++) {
        if (g_d_GameSettings.GameModeSelected == 7) {
            size = f[0xD].sizeFlags & 0x0FFFFFFF;
            if (max0 < size) {
                max0 = size;
            }
        } else {
            size = f[4].sizeFlags & 0x0FFFFFFF;
            if (max0 < size) {
                max0 = size;
            }
        }
        if (g_d_GameSettings.GameModeSelected == 6) {
            size = f[0xE].sizeFlags & 0x0FFFFFFF;
            if (max1 < size) {
                max1 = size;
            }
        } else {
            size = f[0xC].sizeFlags & 0x0FFFFFFF;
            if (max1 < size) {
                max1 = size;
            }
        }
        size = f[0x12].sizeFlags & 0x0FFFFFFF;
        if (max2 < size) {
            max2 = size;
        }
        if (g_d_GameSettings.GameModeSelected == 7) {
            size = f[9].sizeFlags & 0x0FFFFFFF;
            if (max3 < size) {
                max3 = size;
            }
        } else {
            size = f[2].sizeFlags & 0x0FFFFFFF;
            if (max3 < size) {
                max3 = size;
            }
        }
        size = f[0x10].sizeFlags & 0x0FFFFFFF;
        if (max4 < size) {
            max4 = size;
        }
        f += 0x13;
    }
    s2 = (max2 + 0x1F) & ~0x1F;
    s1 = (max1 + 0x1F) & ~0x1F;
    s4 = (max4 + 0x1F) & ~0x1F;
    s0 = (max0 + 0x1F) & ~0x1F;
    s3 = (max3 + 0x1F) & ~0x1F;
    lbl_8036E548.bankSize[2] = s0;
    total = s3 + (s0 + (s1 + s2 + s4)) * 4;
    lbl_8036E548.bankSize[1] = s1;
    lbl_8036E548.bankSize[3] = s2;
    lbl_8036E548.bankSize[0] = s3;
    lbl_8036E548._2CA4 = s4;
    lbl_8036E548._2D60 = total;
    p = _OSAllocFromHeap(0x20, total);
    lbl_8036E548._2C88 = p;
    for (m = 0; m < 4; m++) {
        lbl_8036E548.bankSets[m][0] = p;
        p += s0;
        lbl_8036E548.bankSets[m][1] = p;
        p += s1;
        lbl_8036E548.bankSets[m][2] = p;
        p += s2;
        if (m == 0) {
            lbl_8036E548.bankSets[m][3] = p;
            p += s3;
        } else {
            lbl_8036E548.bankSets[m][3] = lbl_8036E548.bankSets[0][3];
        }
        lbl_8036E548.bankSets[m][4] = p;
        p += s4;
        lbl_8036E548.actors[m].banks.b[0] = NULL;
        lbl_8036E548.actors[m].banks.b[3] = NULL;
        lbl_8036E548.actors[m].banks.b[4] = NULL;
        lbl_8036E548.actors[m].banks.b[1] = NULL;
        lbl_8036E548.actors[m].banks.b[2] = NULL;
        lbl_8036E548.actors[m].banks.b[5] = NULL;
    }
    lbl_8036E548._2D68 = -1;
}
#endif

// .text:0x80018DEC size:0x8EC
// NONMATCHING 91%: size-table loops unrolled/scheduled differently
#if NONMATCHING
void fn_80018DEC(s32 mode) {
    u32 m0 = 0;
    u32 m1 = 0;
    u32 m5 = 0;
    u32 m6 = 0;
    u32 m7 = 0;
    u32 m8 = 0;
    u32 s0;
    u32 s1;
    u32 s5;
    u32 s6;
    u32 s7;
    u32 s8;
    u32 total;
    u32 size;
    DiskFileEntry* f;
    s32 k;
    s32 t;
    s32 i;
    u8* p;

    if (mode == 2) {
        for (k = 0; k < 54; k++) {
            f = &lbl_803CB790[k * 0x13];
            size = f[0xA].sizeFlags & 0x0FFFFFFF;
            if (m0 < size) {
                m0 = size;
            }
            size = f[0xB].sizeFlags & 0x0FFFFFFF;
            if (m1 < size) {
                m1 = size;
            }
            size = f[0x12].sizeFlags & 0x0FFFFFFF;
            if (m6 < size) {
                m6 = size;
            }
            size = f[4].sizeFlags & 0x0FFFFFFF;
            if (m8 < size) {
                m8 = size;
            }
        }
        for (i = 1; i < 9; i++) {
            f = &lbl_803CB790[inMemRoster[0][i].charId * 0x13];
            size = f[4].sizeFlags & 0x0FFFFFFF;
            if (m5 < size) {
                m5 = size;
            }
            size = f[6].sizeFlags & 0x0FFFFFFF;
            if (m7 < size) {
                m7 = size;
            }
        }
    } else if (mode == 0) {
        for (t = 0; t < 2; t++) {
            for (i = 0; i < 9; i++) {
                f = &lbl_803CB790[inMemRoster[t][i].charId * 0x13];
                size = f[2].sizeFlags & 0x0FFFFFFF;
            if (m0 < size) {
                m0 = size;
            }
                size = f[3].sizeFlags & 0x0FFFFFFF;
            if (m1 < size) {
                m1 = size;
            }
                size = f[4].sizeFlags & 0x0FFFFFFF;
            if (m5 < size) {
                m5 = size;
            }
                size = f[5].sizeFlags & 0x0FFFFFFF;
            if (m6 < size) {
                m6 = size;
            }
                size = f[6].sizeFlags & 0x0FFFFFFF;
            if (m7 < size) {
                m7 = size;
            }
            }
        }
    } else {
        for (k = 0; k < 54; k++) {
            f = &lbl_803CB790[k * 0x13];
            size = f[2].sizeFlags & 0x0FFFFFFF;
            if (m0 < size) {
                m0 = size;
            }
            size = f[3].sizeFlags & 0x0FFFFFFF;
            if (m1 < size) {
                m1 = size;
            }
            size = f[4].sizeFlags & 0x0FFFFFFF;
            if (m5 < size) {
                m5 = size;
            }
            size = f[5].sizeFlags & 0x0FFFFFFF;
            if (m6 < size) {
                m6 = size;
            }
            size = f[6].sizeFlags & 0x0FFFFFFF;
            if (m7 < size) {
                m7 = size;
            }
        }
    }
    s0 = (m0 + 0x1F) & ~0x1F;
    s1 = (m1 + 0x1F) & ~0x1F;
    s6 = (m6 + 0x1F) & ~0x1F;
    s7 = (m7 + 0x1F) & ~0x1F;
    s5 = (m5 + 0x1F) & ~0x1F;
    lbl_8036E548.bankSize[0] = s0;
    s8 = (m8 + 0x1F) & ~0x1F;
    lbl_8036E548.bankSize[1] = s1;
    lbl_8036E548.bankSize[3] = s6;
    lbl_8036E548.bankSize[4] = s7;
    lbl_8036E548.bankSize[2] = s5;
    if (mode == 2) {
        total = s0 + (s1 * 4 + s5 * 8 + s8 + s6 + s7) + s0;
        lbl_8036E548._2C88 = _OSAllocFromHeap(0x20, total);
    } else {
        total = s0 + (s1 * 4 + s5 * 9 + s6 + s7) + s0;
        lbl_8036E548._2C88 = _OSAllocFromHeap(0x20, total);
    }
    lbl_8036E548._2D60 = total;
    i = 15;
    lbl_8036E548.animBufs[15] = lbl_8036E548._2C88;
    p = (u8*)lbl_8036E548._2C88 + s7;
    while (i > 14) {
        i--;
        lbl_8036E548.animBufs[i] = p;
        p += s6;
    }
    if (mode == 2) {
        while (i > 6) {
            i--;
            lbl_8036E548.animBufs[i] = p;
            p += s5;
        }
        i--;
        lbl_8036E548.animBufs[i] = p;
        p += s8;
    } else {
        while (i > 5) {
            i--;
            lbl_8036E548.animBufs[i] = p;
            p += s5;
        }
    }
    while (i > 1) {
        i--;
        lbl_8036E548.animBufs[i] = p;
        p += s1;
    }
    while (i > 0) {
        i--;
        lbl_8036E548.animBufs[i] = p;
        p += s0;
    }
    lbl_8036E548.preload[1].buffer = p;
    lbl_8036E548.preload[1].size = s0;
    lbl_8036E548.preload[1].id = -1;
    lbl_8036E548.preload[1].state = 0;
    for (i = 0; i < 13; i++) {
        lbl_8036E548.actors[i].banks.b[0] = NULL;
        lbl_8036E548.actors[i].banks.b[3] = NULL;
        lbl_8036E548.actors[i].banks.b[4] = NULL;
        lbl_8036E548.actors[i].banks.b[1] = NULL;
        lbl_8036E548.actors[i].banks.b[2] = NULL;
        lbl_8036E548.actors[i].banks.b[5] = NULL;
    }
}
#endif

// .text:0x800196D8 size:0x388
// NONMATCHING 99.5%: relocation loop counter register
#if NONMATCHING
void fn_800196D8(void) {
    CharLoadTask* task = lbl_803CC1B8;
    CharLoadTask* child;
    Vec dir2;
    Vec dir;
    f32 mag;
    u8* base;
    void** raw;
    s32 i;

    switch (task->state) {
    case 0:
        child = fn_800B0A5C_insertQueue(fn_800188C0, 0);
        child->state = 0;
        child->kind = 0;
        child->_17[0] = 0xFF;
        lbl_8036E548._307B = 1;
        task->state++;
        break;
    case 1:
        if (lbl_8036E548._307B == 0) {
            task->state++;
        }
        break;
    case 2:
        dir.x = -lbl_80367318[0].x;
        dir.y = -lbl_80367318[0].y;
        dir.z = -lbl_80367318[0].z;
        mag = dolsqrtf2(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
        dir.x /= mag;
        lbl_8036E548._3087 = 1;
        dir.y /= mag;
        dir.z /= mag;
        fn_8003A540(0);
        lbl_8036E548._3086 = 1;
        DrawShadows(1);
        dir2 = dir;
        fn_800BEBCC(0, VEC_ARG(dir2));
        fn_800BF048(fn_8001AAF0);
        fn_800BF058(fn_8001AB10);
#ifdef TARGET_PC
        port_relocate_offset_table(lbl_8036E548.stadiumFiles, 80);
#else
        base = (u8*)lbl_8036E548.stadiumFiles;
        raw = (void**)base;
        for (i = 0; i < 80; i++) {
            ((void**)lbl_8036E548.stadiumFiles)[i] = base + (uintptr_t)raw[i];
        }
#endif
        lbl_8036E548._307C = 0;
        lbl_8036E548._307D = 0;
        lbl_8036E548._3082 = 0;
        fn_8001F8A4();
        task->state++;
        break;
    default:
        challengeMapMaybe();
        lbl_8036E548._2D7D[0] = 1;
        lbl_8036E548._307C = 1;
        fn_800B0A14_removeQueue(&lbl_8036E548);
        break;
    }
}
#endif

// .text:0x80019A60 size:0x1A0
// NONMATCHING 99.0%: light-table base register and colour temp stack slots
#if NONMATCHING
void fn_80019A60(void) {
    LightPos* lights = lbl_80367318;
    CharQueueTask* task;
    s32 i;
    StadiumLights* st;
    LightPos* lp;
    u32 c;
    GXColor color;

    task = fn_800B0A5C_insertQueue(fn_800196D8, 0);
    task->_14 = 0;
    task->parent->_10 = 0;
    for (i = 0; i < 4; i++) {
        fn_80023B90(&lbl_800F7478[g_d_GameSettings._54].light[i], &lbl_80367318[i]);
    }
    fn_800BD2DC();
    st = &lbl_800F7478[g_d_GameSettings._54];
    if (st->ambient.a != 0) {
        color = st->ambient;
        fn_800BD2CC(1, color);
    }
    lp = lights;
    for (i = 0; i < 4; i++) {
        LITAlloc(&lbl_8036E548.lights[i]);
        LITInitAttn(lbl_8036E548.lights[i], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        LITInitPos(lbl_8036E548.lights[i], lp->x, lp->y, lp->z);
        c = lp->color;
        LITInitColor(lbl_8036E548.lights[i], &c);
        lp++;
    }
    if (lbl_8036E548.slots6C != NULL) {
        for (i = 0; i < lbl_8036E548.slots6C->count; i++) {
            fn_800BD548(&lbl_8036E548.slots6C->objects[i], 4, lbl_8036E548.lights[0], lbl_8036E548.lights[1], lbl_8036E548.lights[2], lbl_8036E548.lights[3]);
        }
    }
}
#endif

// .text:0x80019C00 size:0x65C
// NONMATCHING 94%: register allocation of the setup loops
#if NONMATCHING
void fn_80019C00(void) {
    CharLoadTask* task = lbl_803CC1B8;
    CharLoadTask* child;
    Vec dir2;
    Vec dir;
    f32 mag;
    u8* base;
    void** raw;
    u32 max;
    u32 size;
    u32 s;
    s32 i;
    s32 k;
    s32 idx;
    u8* buf;

    switch (task->state) {
    case 0:
        fn_80018024();
        fn_80023B04(((g_d_GameSettings.GameModeSelected == 6) + 1) * 4);
        max = 0;
        for (i = 4; i < 13; i++) {
            lbl_80118220[i]._61 = -1;
        }
        for (k = 0; k < 54; k++) {
            idx = lbl_800EEB18[k];
            if (idx >= 0) {
                size = lbl_803CB794[idx].sizeFlags & 0x0FFFFFFF;
                if (max < size) {
                    max = size;
                }
            }
        }
        s = (max + 0x1F) & ~0x1F;
        buf = _OSAllocFromHeap(0x20, s * 4);
        lbl_803CBC30 = buf;
        for (i = 0; i < 4; i++) {
            lbl_80118220[i].files = (void**)(buf + s * i);
            lbl_80118220[i]._61 = -1;
            lbl_80118220[i].slot = 0xFF;
        }
        fn_80014204(4);
        lbl_8036E548.partSlots = fn_80023AA4();
        for (i = 0; i < 4; i++) {
            lbl_8036E548.actors[i].modelIndex = i;
            lbl_8036E548.active[i] = NULL;
            lbl_8036E548._2D6A[i] = -1;
            lbl_8036E548.actors[i].roster = -1;
        }
        for (i = 0; i < 9; i++) {
            lbl_8036E548._2D7F[i] = -1;
        }
        lbl_8036E548.bankOwner[0] = -1;
        lbl_8036E548.bankOwner[1] = -1;
        lbl_8036E548.bankOwner[2] = -1;
        lbl_8036E548.bankOwner[3] = -1;
        lbl_8036E548.state = 0;
        lbl_8036E548._2D7A[1] = 0;
        lbl_8036E548._2D7C = 0;
        task->state++;
        break;
    case 1:
        child = fn_800B0A5C_insertQueue(fn_800188C0, 0);
        child->state = 0;
        child->kind = 0;
        child->_17[0] = 0xFF;
        lbl_8036E548._307B = 1;
        task->state++;
        break;
    case 2:
        if (lbl_8036E548._307B == 0) {
            if (g_d_GameSettings.GameModeSelected == 6) {
                task->state++;
            } else {
                task->state = 5;
            }
        }
        break;
    case 3:
        lbl_8036E548.trailFile = ARAMTransfer(&lbl_800EE930.trailFile, NULL, 0, 0);
        task->state++;
        break;
    case 4:
        if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            task->state++;
        }
        break;
    case 5:
        dir.x = -lbl_80367318[0].x;
        dir.y = -lbl_80367318[0].y;
        dir.z = -lbl_80367318[0].z;
        mag = dolsqrtf2(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
        dir.x /= mag;
        lbl_8036E548._3087 = 1;
        dir.y /= mag;
        dir.z /= mag;
        fn_8003A540(0);
        lbl_8036E548._3086 = 1;
        DrawShadows(1);
        dir2 = dir;
        fn_800BEBCC(0, VEC_ARG(dir2));
        fn_800BF048(fn_8001AAF0);
        fn_800BF058(fn_8001AB10);
#ifdef TARGET_PC
        port_relocate_offset_table(lbl_8036E548.stadiumFiles, 80);
#else
        base = (u8*)lbl_8036E548.stadiumFiles;
        raw = (void**)base;
        for (i = 0; i < 80; i++) {
            ((void**)lbl_8036E548.stadiumFiles)[i] = base + (uintptr_t)raw[i];
        }
#endif
        lbl_8036E548._307C = 0;
        lbl_8036E548._307D = 0;
        lbl_8036E548._3082 = 0;
        fn_8001F8A4();
        task->state++;
        break;
    case 6:
        challengeMapMaybe();
        if (g_d_GameSettings.GameModeSelected == 6) {
            fn_8001F5E8();
        }
        task->state++;
        break;
    default:
        lbl_8036E548._2D7D[0] = 1;
        lbl_8036E548._307C = 1;
        fn_800B0A14_removeQueue(&lbl_8036E548);
        break;
    }
}
#endif

// .text:0x8001A25C size:0x1A0
// NONMATCHING 99.0%: light-table base register and colour temp stack slots
#if NONMATCHING
void fn_8001A25C(void) {
    LightPos* lights = lbl_80367318;
    CharQueueTask* task;
    s32 i;
    StadiumLights* st;
    LightPos* lp;
    u32 c;
    GXColor color;

    task = fn_800B0A5C_insertQueue(fn_80019C00, 0);
    task->_14 = 0;
    task->parent->_10 = 0;
    for (i = 0; i < 4; i++) {
        fn_80023B90(&lbl_800F7478[g_d_GameSettings._54].light[i], &lbl_80367318[i]);
    }
    fn_800BD2DC();
    st = &lbl_800F7478[g_d_GameSettings._54];
    if (st->ambient.a != 0) {
        color = st->ambient;
        fn_800BD2CC(1, color);
    }
    lp = lights;
    for (i = 0; i < 4; i++) {
        LITAlloc(&lbl_8036E548.lights[i]);
        LITInitAttn(lbl_8036E548.lights[i], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        LITInitPos(lbl_8036E548.lights[i], lp->x, lp->y, lp->z);
        c = lp->color;
        LITInitColor(lbl_8036E548.lights[i], &c);
        lp++;
    }
    if (lbl_8036E548.slots6C != NULL) {
        for (i = 0; i < lbl_8036E548.slots6C->count; i++) {
            fn_800BD548(&lbl_8036E548.slots6C->objects[i], 4, lbl_8036E548.lights[0], lbl_8036E548.lights[1], lbl_8036E548.lights[2], lbl_8036E548.lights[3]);
        }
    }
}
#endif

// .text:0x8001A3FC size:0x2B4
// NONMATCHING 73%: the original keeps count in a register (not folded) and unrolls the 13-actor reset
// loop 3x with four peeled iterations; as a for loop it unrolls 6x, as a do-while not at all
#if NONMATCHING
void fn_8001A3FC(s32 arg) {
    s32 count;
    s32 i;
    s32 k;
    s32 idx;
    u32 max;
    u32 size;
    void* p;

    fn_80018270(arg);
    count = 1;
    lbl_803CBC34[0] = 0;
    lbl_803CBC34[1] = 0;
    lbl_803CBC34[2] = 0;
    lbl_803CBC34[3] = 0;
    lbl_803CBC34[4] = count;
    for (i = count; i < 13; i++) {
        lbl_80118220[i]._61 = -2;
    }
    if (count != 0) {
        max = 0;
        for (k = 0; k < 54; k++) {
            idx = lbl_800EEB18[k];
            if (idx >= 0) {
                size = lbl_803CB794[idx].sizeFlags & 0x0FFFFFFF;
                if (max < size) {
                    max = size;
                }
            }
        }
        p = _OSAllocFromHeap(0x20, (max + 0x1F) & ~0x1F);
        lbl_80118220[0].files = p;
        lbl_803CBC30 = p;
        lbl_80118220[0].slot = lbl_80118220[0]._61 = -1;
    }
    fn_800145F8(arg);
    lbl_8036E548.partSlots = fn_80023AA4();
    fn_80018DEC(arg);
    fn_80023B04(0xD);
    i = 0;
    do {
        lbl_8036E548.actors[i].modelIndex = i;
        lbl_8036E548.active[i] = NULL;
        lbl_8036E548.actors[i].roster = lbl_8036E548._2D6A[i] = -1;
        i++;
    } while (i < 13);
    for (i = 0; i < 9; i++) {
        lbl_8036E548._2D7F[i] = -1;
    }
    lbl_8036E548.bankOwner[0] = -1;
    lbl_8036E548.bankOwner[1] = -1;
    lbl_8036E548.bankOwner[2] = -1;
    lbl_8036E548.bankOwner[3] = -1;
}
#endif

// .text:0x8001A6B0 size:0x3F4
// NONMATCHING 99.5%: mixed saved/rematerialised lbl_8036E548 base registers
#if NONMATCHING
void challengeMapRelated(void) {
    CharLoadTask* task = lbl_803CC1B8;
    CharLoadTask* child;
    CharQueueTask* parent;
    Vec dir2;
    Vec dir;
    f32 mag;
    u8* base;
    void** raw;
    s32 i;

    if (lbl_8036E548._3082 != 0) {
        return;
    }
    switch (task->state) {
    case 0:
        lbl_8036E548.state = 0;
        lbl_8036E548._2D7A[1] = 0;
        lbl_8036E548._2D7C = 0;
        lbl_8036E548._2D7A[0] = 0;
        task->kind = 0;
        task->_17[1] = 0;
        task->state = 1;
        break;
    case 1:
        if (fn_8001594C(g_d_GameSettings._0E ^ 1) != 0) {
            task->state = 2;
        }
        break;
    case 2:
        child = fn_800B0A5C_insertQueue(fn_800188C0, 0);
        child->state = 0;
        child->kind = 0;
        child->_17[0] = 0xFF;
        lbl_8036E548._307B = 1;
        task->state++;
        break;
    case 3:
        if (lbl_8036E548._307B == 0) {
            task->state = 6;
        }
        break;
    case 6:
        dir.x = -lbl_80367318[0].x;
        dir.y = -lbl_80367318[0].y;
        dir.z = -lbl_80367318[0].z;
        mag = dolsqrtf2(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
        dir.x /= mag;
        lbl_8036E548._3087 = 1;
        dir.y /= mag;
        dir.z /= mag;
        fn_8003A540(0);
        lbl_8036E548._3086 = 1;
        DrawShadows(1);
        dir2 = dir;
        fn_800BEBCC(0, VEC_ARG(dir2));
        fn_800BF048(fn_8001AAF0);
        fn_800BF058(fn_8001AB10);
#ifdef TARGET_PC
        port_relocate_offset_table(lbl_8036E548.stadiumFiles, 80);
#else
        base = (u8*)lbl_8036E548.stadiumFiles;
        raw = (void**)base;
        for (i = 0; i < 80; i++) {
            ((void**)lbl_8036E548.stadiumFiles)[i] = base + (uintptr_t)raw[i];
        }
#endif
        lbl_8036E548._3082 = 0;
        lbl_8036E548._307C = 0;
        lbl_8036E548._307D = 0;
        fn_8001F8A4();
        task->state++;
        break;
    case 7:
        challengeMapMaybe();
        task->state++;
        break;
    case 8:
        lbl_8036E548._307C = 1;
        parent = task->parent;
        parent->_10 = 1;
        fn_800B0A14_removeQueue(parent);
        break;
    }
}
#endif

// .text:0x8001AAA4 size:0x4C
void fn_8001AAA4(void) {
    CharQueueTask* task = fn_800B0A5C_insertQueue(challengeMapRelated, 0);
    task->_14 = 0;
    task->parent->_10 = 0;
    lbl_8036E548._3082 = 0;
    lbl_803CBBF0 = 0;
}

// .text:0x8001AAF0 size:0x20
void fn_8001AAF0(void* arg) {
    fn_8003AC90();
}

// .text:0x8001AB10 size:0x488
// NONMATCHING 98.4%: early-return branch layout and register allocation
#if NONMATCHING
void fn_8001AB10(ActorObject* slot, Mtx view) {
    CharActor* actor = &lbl_8036E548.actors[slot->id];
    BOOL homeRun = g_d_GameSettings.GameModeSelected == 6;
    f32 t;
    f32 y;
    u8 v;
    GameBone* joint;
    GameActor* model;
    GXColor c;
    Mtx mv;
    Mtx m;

    if (actor->mode[0] == 3) {
        y = actor->pos.y;
        if (y < 0.0f) {
            y = -y;
        }
        t = (lbl_803CB7BC - y) / lbl_803CB7BC;
        if (t > 1.0f) {
            t = 1.0f;
        } else if (t < 0.0f) {
            t = 0.0f;
        }
        v = fn_8003AE54();
        c.a = 0xFF;
        v = t * v;
        c.b = v;
        c.g = v;
        c.r = v;
    } else if (actor->mode[0] == 1) {
        if (actor->_277 == 0) {
            return;
        }
        v = fn_8003AE54();
        c.b = v;
        c.g = v;
        c.r = v;
        c.a = actor->_277;
    } else {
        return;
    }
    GXSetChanMatColor(GX_COLOR0A0, c);
    if (homeRun) {
        PSMTXTrans(m, actor->pos.x, actor->pos.y, actor->pos.z);
    } else {
        PSMTXTrans(m, actor->pos.x, actor->pos.y, actor->pos.z);
    }
    if (!homeRun) {
        PSMTXConcat(view, m, mv);
        for (joint = (GameBone*)slot->actor->drawPriorityList.Head; joint != NULL; joint = (GameBone*)joint->drawPriorityLink.Next) {
            if (joint->dispObj != NULL) {
                DOSetWorldMatrix(joint->dispObj, joint->forwardMtx);
                fn_8003A8A0(joint->dispObj, mv, 1);
            }
        }
        model = slot->actor;
        if (model->skinObject != NULL) {
            if (model->skHeader != NULL) {
                fn_8003A8A0(model->skinObject, mv, 0);
            } else {
                DOVARenderSkin(model->skinObject, view, (MtxPtr)model->skinMtxArray, (MtxPtr)model->skinInvTransposeMtxArray, 0, NULL);
            }
        }
        v = fn_8003AE54();
        c.b = v;
        c.g = v;
        c.r = v;
        c.a = 0xFF;
        GXSetChanMatColor(GX_COLOR0A0, c);
    } else {
        c.b = lbl_803CB7C1;
        c.g = lbl_803CB7C1;
        c.r = lbl_803CB7C1;
        c.a = lbl_803CB7C0;
        fn_800BD2CC(1, c);
        PSMTXConcat(view, m, mv);
        drawSlot(slot, 0, mv);
    }
}
#endif

// .text:0x8001AF98 size:0x268
void fn_8001AF98(void) {
    BOOL homeRun = g_d_GameSettings.GameModeSelected == 6;
    u32 sx;
    u32 sy;
    u32 sw;
    u32 sh;
    Vec dir;
    Vec dir2;
    f32 proj[7];
    f32 viewport[6];
    ShadowView view;
    CameraView* cam;

    if (lbl_8036E548._3087 != 0 && fn_8003A538() == 0) {
        DrawShadows(lbl_8036E548._3086);
    } else {
        DrawShadows(0);
        return;
    }
    GXGetProjectionv(proj);
    GXGetViewportv(viewport);
    GXGetScissor(&sx, &sy, &sw, &sh);
    fn_800BEC00(homeRun);
    if (homeRun) {
        cam = fn_80052734(fn_8005268C());
        PSVECSubtract(&cam->eye, &cam->target, &dir);
        dir.y = 2.0f * -dir.y;
        if (PSVECMag(&dir)) {
            PSVECNormalize(&dir, &dir);
            dir2 = dir;
            fn_800BEBCC(0, VEC_ARG(dir2));
        }
    } else {
        fn_800BD1E8(NULL);
    }
    if (GetDrawShadows()) {
        view.eye = fn_80052734(0)->eye;
        view.target = fn_80052734(0)->target;
        view.up = fn_80052734(0)->up;
        PSMTXCopy(fn_80052734(0)->view, view.view);
        fn_800BE09C(lbl_8036E548.slots, &view);
        fn_800BF058(fn_8001AB10);
        fn_800BDFE0(lbl_8036E548.slots);
        if (lbl_8036E548.callback != NULL) {
            lbl_8036E548.callback();
        }
        if (homeRun) {
            fn_8003A4C8();
        } else {
            fn_800BDEA0();
        }
    }
    if (lbl_803CBBF4 != NULL) {
        lbl_803CBBF4();
        lbl_803CBBF4 = NULL;
    }
    GXSetScissor(sx, sy, sw, sh);
    GXSetViewport(viewport[0], viewport[1], viewport[2], viewport[3], viewport[4], viewport[5]);
    GXSetProjectionv(proj);
    GXInvalidateTexAll();
}

// fn_8001B200, size:0x14
void fn_8001B200(void) {
    lbl_8036E548.callback = NULL;
}

// fn_8001B214, size:0x10
void fn_8001B214(void (*callback)(void)) {
    lbl_8036E548.callback = callback;
}

// .text:0x8001B224 size:0xAC
void fn_8001B224(void) {
    s32 i;
    CharActor* actor;

    memcpy(lbl_8036E548.actors, lbl_8036C4FC, sizeof(lbl_8036E548.actors));
    for (i = 0; i < 13; i++) {
        actor = lbl_8036E548.active[i];
        if (actor != NULL && (actor->mode[0] != 0 || i <= 8)) {
            fn_8001BE50(i, actor->anim[0], actor->_25F[0], actor->_262[0], actor->_06A[0] + 1, actor->_265[0], 0);
        }
    }
}

// .text:0x8001B2D0 size:0x38
void fn_8001B2D0(void) {
    memcpy(lbl_8036C4FC, lbl_8036E548.actors, sizeof(lbl_8036E548.actors));
}

// .text:0x8001B308 size:0x54
void fn_8001B308(s32 index, s32 enable) {
    CharActor* actor = lbl_8036E548.active[index];
    ActorObject* slot;

    if (actor != NULL) {
        slot = &lbl_8036E548.slots->objects[actor->modelIndex];
        if (enable == 0) {
            slot->boneRemap = NULL;
        } else {
            slot->boneRemap = actor->mirror;
        }
    }
}

// .text:0x8001B35C size:0x17C
static inline f32 getJointHeight(CharActor* actor, s32 k) {
    f32 y;
    s32 j;
    ActorObject* slot;
    Vec v;

    if (actor != NULL) {
        j = getJoint(actor, k);
        if (j == 0xFFFF) {
            y = 0.0f;
        } else {
            slot = &lbl_8036E548.slots->objects[actor->modelIndex];
            fn_800B2C44(slot->actor, j, &v);
            y = v.y;
            y += actor->pos.y;
        }
    }
    return y;
}

s32 fn_8001B35C(s32 index, s32 kind) {
    CharActor* actor = lbl_8036E548.active[index];
    s32 k = 1;
    s32 steps = 0;
    f32 d;
    f32 t;

    if (actor == NULL) {
        return 0;
    }
    switch (kind) {
    case 1:
        k = 2;
        break;
    case 0:
        k = 3;
        break;
    case 2:
        k = 1;
        break;
    }
    d = getJointHeight(actor, k) - actor->pos.y;
    if (d < 0.0f && d >= -30.0f) {
        steps = 1;
        t = -0.5f;
        while (TRUE) {
            if (d > t) {
                break;
            }
            t -= 0.5f;
            steps++;
        }
    } else if (d >= 0.5f && d < 30.0f) {
        t = 0.5f;
        while (TRUE) {
            if (d < t) {
                break;
            }
            t += 0.5f;
            steps--;
        }
    }
    return steps;
}

// .text:0x8001B4D8 size:0x114
static inline void getRootOffset(CharActor* actor, u16 idx, s32 k, Vec* out) {
    u16 j0 = getJoint(actor, k);
    u16 j1 = getJoint(actor, 0);
    ActorObjectTable* list = lbl_8036E548.slots;
    Vec v;

    fn_800B2C44(list->objects[idx].actor, list->objects[idx].actor->anchorBoneA, &v);
    list->objects[idx].unk64 = j1;
    list->objects[idx].unk66 = j0;
    *out = v;
}

void fn_8001B4D8(s32 index, s32 enable) {
    CharActor* actor = lbl_8036E548.active[index];
    s32 modelIndex;
    Vec d;

    if (actor != NULL) {
        modelIndex = actor->modelIndex;
        if (enable != 0 && actor->_268 == 0) {
            getRootOffset(actor, modelIndex, 0, &d);
            actor->pos.x += d.x;
            actor->pos.y += d.y;
            actor->pos.z += d.z;
            actor->_268 = 1;
        }
    }
}

// .text:0x8001B5EC size:0x13C
static inline void setRootJoints(CharActor* actor, u16 idx, s32 k) {
    u16 j0 = getJoint(actor, k);
    u16 j1 = getJoint(actor, 0);
    ActorObjectTable* list = lbl_8036E548.slots;
    Vec v;

    fn_800B2C44(list->objects[idx].actor, list->objects[idx].actor->anchorBoneA, &v);
    list->objects[idx].unk64 = j1;
    list->objects[idx].unk66 = j0;
}

void fn_8001B5EC(s32 index, s32 enable) {
    CharActor* actor = lbl_8036E548.active[index];
    s32 modelIndex;

    if (actor != NULL) {
        modelIndex = actor->modelIndex;
        if (enable == 0) {
            setRootJoints(actor, modelIndex, 4);
        } else {
            setRootJoints(actor, modelIndex, 0);
        }
    }
}

// .text:0x8001B728 size:0xE4
s32 fn_8001B728(s32 index, s32 joint, Vec* out) {
    CharActor* actor = lbl_8036E548.active[index];
    s32 j;
    ActorObject* slot;

    if (actor == NULL) {
        return 0;
    }
    j = getJoint(actor, joint);
    if (j == 0xFFFF) {
        return 0;
    }
    slot = &lbl_8036E548.slots->objects[actor->modelIndex];
    fn_800B2C10(slot->actor, j, out);
    out->x += actor->pos.x;
    out->y += actor->pos.y;
    out->z += actor->pos.z;
    return 1;
}

// .text:0x8001B80C size:0x10C
BOOL getAnimRelatedCoordinates(s32 index, s32 joint, Vec* out) {
    CharActor* actor = lbl_8036E548.active[index];
    s32 j;
    ActorObject* slot;
    Vec pos;

    if (actor == NULL) {
        return FALSE;
    }
    j = getJoint(actor, joint);
    if (j == 0xFFFF) {
        out->x = 0.0f;
        out->y = 0.0f;
        out->z = 0.0f;
        return FALSE;
    }
    slot = &lbl_8036E548.slots->objects[actor->modelIndex];
    fn_800B2C44(slot->actor, j, &pos);
    out->x = pos.x;
    out->y = pos.y;
    out->z = pos.z;
    out->x += actor->pos.x;
    out->y += actor->pos.y;
    out->z += actor->pos.z;
    return TRUE;
}

// .text:0x8001B918 size:0x78
void QueueCharacterAnimation(s32 index, s32 anim, s32 a, s32 b, s32 c, s32 d, s32 e) {
    CharActor* actor = lbl_8036E548.active[index];

    actor->anim[2] = anim;
    actor->_06A[2] = c;
    actor->_25F[2] = a;
    actor->_262[2] = b;
    actor->_265[2] = d;
    actor->_26C[2] = 0;
    if (e == -1) {
        actor->_269[2] = 5;
    } else {
        actor->_269[2] = e;
    }
    if ((anim >= 0x3F && anim < 0x4B) || (anim >= 0x4B && anim < 0x69)) {
        lbl_8036E548.active[index]->_26C[2] = 1;
    }
}

// .text:0x8001B990 size:0xB4
void AnimateCharacter(s32 index, s32 anim, s32 a, u8 mode, s32 b, s32 c, s32 d, s32 e) {
    CharActor* actor = lbl_8036E548.active[index];

    if (actor == NULL) {
        return;
    }
    if (mode == 1 && actor->anim[0] == anim) {
        return;
    }
    if (mode == 3) {
        mode = 1;
    }
    actor->anim[1] = anim;
    actor->_06A[1] = c;
    actor->_25F[1] = a;
    actor->mode[1] = mode;
    actor->_262[1] = b;
    actor->_265[1] = d;
    actor->_26C[1] = 0;
    if (e == -1) {
        actor->_269[1] = 5;
    } else {
        actor->_269[1] = e;
    }
    actor->anim[2] = -1;
    if ((anim >= 0x3F && anim < 0x4B) || (anim >= 0x4B && anim < 0x69)) {
        lbl_8036E548.active[index]->_26C[1] = 1;
    }
}

// .text:0x8001BA44 size:0x40C
// Splits a global animation id into an actor anim bank and an index in it.
static inline BOOL splitAnimId(s32 anim, s32* bank, s32* idx) {
#ifdef TARGET_PC
    // The callers use bank/idx even when this doesn't set them (stack garbage
    // on GameCube): make that an out-of-range index of bank 0.
    *bank = 0;
    *idx = -1;
#endif
    if (anim < 0) {
        return FALSE;
    }
    if (anim < 0x2D) {
        *idx = anim;
        *bank = 2;
    } else if (anim < 0x3D) {
        *idx = anim - 0x2D;
        *bank = 1;
    } else if (anim < 0x3F) {
        *idx = anim - 0x3D;
        *bank = 4;
    } else if (anim < 0x4B) {
        *idx = anim - 0x3F;
        *bank = 3;
    } else if (anim < 0x69) {
        *idx = anim - 0x4B;
        *bank = 0;
    } else {
        *bank = 5;
        *idx = anim - 0x69;
    }
    return TRUE;
}

static inline void resetRootJoint(CharActor* actor, ActorObject* slot, s32 index) {
    if (actor->_26C[0] == 0) {
        fn_800B2B54(actor->model, getJoint(actor, 4), 0xD);
    } else {
        fn_800B2B54(actor->model, getJoint(actor, 4), 1);
        fn_800B2B54(slot->actor, getJoint(lbl_8036E548.active[index], 4), 1);
        fn_800B2B4C(slot->actor, 0.125f);
        slot->actor->blend = 0.0f;
    }
}

// NONMATCHING 85%: register allocation and joint-lookup scheduling
#if NONMATCHING
void fn_8001BA44(s32 index, s32 anim, u8 a, u8 b, s16 c, u8 d, u8 e) {
    CharActor* actor = lbl_8036E548.active[index];
    ActorObject* slot;
    CharAnimBank* bankData;
    s32 bank;
    s32 idx;
    f32 speed = 0.0f;

    if (actor == NULL) {
        return;
    }
    slot = &lbl_8036E548.slots->objects[actor->modelIndex];
    if (e != 0) {
        speed = 1.0f / e;
    }
    resetRootJoint(actor, slot, index);
    if (splitAnimId(anim, &bank, &idx)) {
        bankData = actor->banks.b[bank];
        if (bankData != NULL) {
            if (!(idx < bankData->count && idx >= 0)) {
                return;
            }
            slot->animBank = bankData;
            slot->seqNum = idx;
            slot->time = 0.0f;
            slot->setAnimation = 1;
            slot->setTime = bankData != NULL;
            slot->setSpeed = bankData != NULL;
            slot->speed = speed;
        }
        if (actor->part != NULL) {
            fn_80025EEC(&actor->part->player, bank, idx);
        }
        if (actor->parts != NULL) {
            fn_80011CA8(actor, bank, idx);
        }
        if (a != 0) {
            slot->visFlags = 3;
        } else {
            slot->visFlags = 2;
        }
        slot->time = c * actor->_04C;
        slot->setTime = 1;
        fn_8001B5EC(index, b);
        fn_8001B308(index, d);
        actor->_268 = b;
    } else {
        slot->animBank = NULL;
        slot->seqNum = 0;
        slot->time = 0.0f;
        slot->setAnimation = 1;
        slot->setTime = 0;
        slot->setSpeed = 0;
        slot->speed = 0.0f;
    }
}
#endif

// .text:0x8001BE50 size:0x3E4
// NONMATCHING 95.8%: register allocation and joint-lookup scheduling
#if NONMATCHING
void fn_8001BE50(s32 index, s32 anim, u8 a, u8 b, s16 c, u8 d, u8 e) {
    CharActor* actor = lbl_8036E548.active[index];
    ActorObject* slot;
    CharAnimBank* bankData;
    s32 bank;
    s32 idx;
    f32 speed = 0.0f;

    if (actor == NULL) {
        return;
    }
    slot = &lbl_8036E548.slots->objects[actor->modelIndex];
    if (e != 0) {
        speed = 1.0f / e;
    }
    resetRootJoint(actor, slot, index);
    // NOTE: bank/idx stay unset for a negative anim id, as in the original.
    splitAnimId(anim, &bank, &idx);
    bankData = actor->banks.b[bank];
    if (bankData != NULL) {
        if (!(idx < bankData->count && idx >= 0)) {
            return;
        }
        slot->animBank = bankData;
        slot->seqNum = idx;
        slot->time = 0.0f;
        slot->setAnimation = 1;
        slot->setTime = bankData != NULL;
        slot->setSpeed = bankData != NULL;
        slot->speed = speed;
    }
    if (actor->part != NULL) {
        fn_80025EEC(&actor->part->player, bank, idx);
    }
    if (actor->parts != NULL && actor->parts->_CC != 0) {
        fn_80025EEC(&actor->parts->part[1].player, bank, idx);
        fn_80025EEC(&actor->parts->part[0].player, bank, idx);
    }
    if (a != 0) {
        slot->visFlags = 3;
    } else {
        slot->visFlags = 2;
    }
    slot->time = c * actor->_04C;
    slot->setTime = 1;
    fn_8001B5EC(index, b);
    fn_8001B308(index, d);
    actor->_268 = b;
}
#endif

// .text:0x8001C234 size:0x2F4
void fn_8001C234(u32* doneMask) {
    CharActor* actor;
    f32 frames;
    s32 i;
    f32 t;
    s32 n;
    s32 j;

    *doneMask = 0;
    for (i = 0; i < 13; i++) {
        actor = lbl_8036E548.active[i];
        if (actor == NULL || actor->mode[0] == 0) {
            continue;
        }
        n = actor->_06A[0];
        if (n < 600 && lbl_80366158._28 == 0 && lbl_803CBC3C[0] == 0 && actor->_26F == 0) {
            actor->_06A[0] = n + 1;
        }
        frames = 1.0f;
        j = getJoint(lbl_8036E548.active[i], 4);
        if (j != 0xFFFF) {
            frames = fn_800B4A44(lbl_8036E548.slots->objects[actor->modelIndex].actor, j);
        }
        actor->_068 = frames / actor->_04C;
        if (actor->_070 >= 0) {
            actor->_068 = actor->_070;
        }
        actor->_070 = -1;
        if (actor->mode[1] == 1 || (actor->mode[1] == 2 && actor->_068 == 0 && actor->_06A[0] > 1) || actor->anim[0] == -1) {
            *doneMask |= 1 << i;
            if (actor->anim[1] >= 0) {
                t = actor->_06A[1];
                if (g_d_GameSettings.minigamesEnabled != 0 && g_d_GameSettings._06 == 2) {
                    fn_8001BA44(i, actor->anim[1], actor->_25F[1], actor->_262[1], actor->_06A[1], actor->_265[1], actor->_269[1]);
                } else {
                    fn_8001BE50(i, actor->anim[1], actor->_25F[1], actor->_262[1], actor->_06A[1], actor->_265[1], actor->_269[1]);
                }
                actor->_060 = actor->anim[0];
                actor->anim[0] = actor->anim[1];
                actor->anim[1] = -1;
                actor->_25F[0] = actor->_25F[1];
                actor->_262[0] = actor->_262[1];
                actor->_265[0] = actor->_265[1];
                actor->_269[0] = actor->_269[1];
                actor->_26C[0] = actor->_26C[1];
                actor->_06A[0] = 0;
                if (actor->anim[2] >= 0) {
                    actor->anim[1] = actor->anim[2];
                    actor->_06A[1] = actor->_06A[2];
                    actor->_25F[1] = actor->_25F[2];
                    actor->_262[1] = actor->_262[2];
                    actor->mode[1] = 2;
                    actor->_265[1] = actor->_265[2];
                    actor->_269[1] = actor->_269[2];
                    actor->_26C[1] = actor->_26C[2];
                    actor->anim[2] = -1;
                    continue;
                }
            } else {
                t = 0.0f;
            }
            actor->mode[1] = 0;
        } else {
            t = fn_800B4C40(lbl_8036E548.slots->objects[actor->modelIndex].actor);
        }
        if (lbl_803CBC3C[0] == 0) {
            fn_8004B208(actor, actor->anim[0], fn_8004AD54(g_d_GameSettings.StadiumID, actor->_275), t);
        }
    }
}

// .text:0x8001C528 size:0x60
void fn_8001C528(void) {
    s32 i;

    for (i = 0; i < 13; i++) {
        lbl_8036E548.actors[i]._060 = -1;
        lbl_8036E548.actors[i].anim[0] = -1;
        lbl_8036E548.actors[i].anim[1] = -1;
        lbl_8036E548.actors[i].anim[2] = -1;
        lbl_8036E548.actors[i]._068 = 0;
        lbl_8036E548.actors[i]._06A[0] = 0;
        lbl_8036E548.actors[i].mode[1] = 1;
        lbl_8036E548.actors[i]._25F[0] = 0;
        lbl_8036E548.actors[i]._262[0] = 0;
        lbl_8036E548.actors[i]._268 = 0;
        lbl_8036E548.actors[i]._269[0] = 0;
        lbl_8036E548.actors[i]._269[1] = 0;
        lbl_8036E548.actors[i]._269[2] = 0;
        lbl_8036E548.actors[i]._26F = 0;
    }
}

// .text:0x8001C588 size:0xF4
s32 fn_8001C588(s32 id) {
    if (lbl_803CBC3C[3] == 0) {
        if ((s32)(u8)lbl_803C6CF8.idle != 1) {
            goto fail;
        }
        lbl_803CBC3C[3] = 1;
    }
    if (lbl_803CBC3C[3] == 1) {
        ARAMTransfer(&lbl_803CB790[id * 0x13 + 6], lbl_8036E548.animBufs[15], 0, 0);
        lbl_803CBC3C[3] = 2;
    } else if (lbl_803CBC3C[3] == 2 && (s32)(u8)lbl_803C6CF8.idle == 1) {
        ANIMGet(lbl_8036E548.animBufs[15]);
        if (lbl_8036E548.active[1]->banks.b[4] == NULL) {
            lbl_8036E548.active[1]->banks.b[4] = lbl_8036E548.animBufs[15];
        }
        return 1;
    }
fail:
    lbl_803CBC3C[0] = 0;
    return 0;
}

// .text:0x8001C67C size:0x2A4
// NONMATCHING 99.7%: joint offset/list registers swapped, mfcr scheduling
#if NONMATCHING
int fn_8001C67C_animation(int id, int index) {
    ActorObjectTable* list;
    GameActor* model;
    CharActor* actor;
    s32 i;
    s32 file;

    if (lbl_803CBC3C[2] == 0) {
        if ((s32)(u8)lbl_803C6CF8.idle != 1) {
            return 0;
        }
        list = lbl_8036E548.slots64;
        model = list->objects[4].actor;
        if (model->boneArray[0]->animPipe != NULL && model->boneArray[0]->animPipe->currentTrack != NULL) {
            for (i = 0; i < model->totalBones; i++) {
                ACTSetBoneTrack(model->boneArray[i], NULL, 0.0f, model->blend < 1.0f);
            }
            list->objects[4].setAnimation = 0;
            list->objects[4].setTime = 0;
            list->objects[4].setSpeed = 0;
            list->objects[4].speed = 0.0f;
        }
        lbl_803CBC3C[2] = 1;
    }
    if (lbl_803CBC3C[2] == 1) {
        if (g_d_GameSettings.minigamesEnabled != 0) {
            if (g_d_GameSettings.GameModeSelected == 7) {
                file = id * 0x13 + 9;
            } else {
                file = id * 0x13 + 2;
            }
            ARAMTransfer(&lbl_803CB790[file], lbl_8036E548.bankSets[0][3], 0, 0);
        } else {
            if (id == lbl_8036E548.preload[1].id) {
                memcpy(lbl_8036E548.animBufs[0], lbl_8036E548.preload[1].buffer, lbl_8036E548.preload[1].size);
                goto loaded;
            }
            if (g_d_GameSettings.GameModeSelected == 2) {
                file = id * 0x13 + 0xA;
            } else {
                file = id * 0x13 + 2;
            }
            ARAMTransfer(&lbl_803CB790[file], lbl_8036E548.animBufs[0], 0, 0);
        }
        lbl_803CBC3C[2] = 2;
    } else if (lbl_803CBC3C[2] == 2 && (s32)(u8)lbl_803C6CF8.idle == 1) {
        if (g_d_GameSettings.minigamesEnabled != 0) {
            ANIMGet(lbl_8036E548.bankSets[0][3]);
            actor = lbl_8036E548.active[index];
            if (actor->banks.b[0] == NULL) {
                actor->banks.b[0] = lbl_8036E548.bankSets[0][3];
            }
        } else {
        loaded:
            ANIMGet(lbl_8036E548.animBufs[0]);
            actor = lbl_8036E548.active[index];
            if (actor->banks.b[0] == NULL) {
                actor->banks.b[0] = lbl_8036E548.animBufs[0];
            }
        }
        lbl_8036E548._2D68 = id;
        return 1;
    }
    lbl_803CBC3C[0] = 0;
    return 0;
}
#endif

// .text:0x8001C920 size:0x120
s32 fn_8001C920(s32 id) {
    s32 file;

    if (lbl_803CBC3C[1] == 0) {
        if ((s32)(u8)lbl_803C6CF8.idle != 1) {
            goto fail;
        }
        lbl_803CBC3C[1] = 1;
    }
    if (lbl_803CBC3C[1] == 1) {
        if (g_d_GameSettings.minigamesEnabled != 0 || g_d_GameSettings.GameModeSelected == 2) {
            file = id * 0x13 + 0x12;
        } else {
            file = id * 0x13 + 5;
        }
        ARAMTransfer(&lbl_803CB790[file], lbl_8036E548.animBufs[14], 0, 0);
        lbl_803CBC3C[1] = 2;
    } else if (lbl_803CBC3C[1] == 2 && (s32)(u8)lbl_803C6CF8.idle == 1) {
        ANIMGet(lbl_8036E548.animBufs[14]);
        if (lbl_8036E548.active[0]->banks.b[3] == NULL) {
            lbl_8036E548.active[0]->banks.b[3] = lbl_8036E548.animBufs[14];
        }
        return 1;
    }
fail:
    lbl_803CBC3C[0] = 0;
    return 0;
}

// .text:0x8001CA40 size:0xD0
static inline void loadLights(LightSrc* src, s32 count) {
    s32 i;
    Vec dir;
    Vec dir2;

    for (i = 0; i < count; i++) {
        fn_80023B90(&src[i], &lbl_80367318[i]);
    }
    dir.x = lbl_80367318[0].x;
    dir.y = lbl_80367318[0].y;
    dir.z = lbl_80367318[0].z;
    PSVECNormalize(&dir, &dir);
    dir2 = dir;
    fn_800BEBCC(0, VEC_ARG(dir2));
}

void fn_8001CA40(u8 stadium) {
    g_d_GameSettings._54 = stadium;
    loadLights(lbl_800F7478[stadium].light, 4);
}

// .text:0x8001CB10 size:0xC4
void fn_8001CB10(LightSrc* src, s32 count) {
    s32 i;
    LightPos* dst;
    Vec dir2;
    Vec dir;

    for (i = 0; i < count; i++) {
        fn_80023B90(&src[i], &lbl_80367318[i]);
    }
    dir.x = lbl_80367318[0].x;
    dir.y = lbl_80367318[0].y;
    dir.z = lbl_80367318[0].z;
    PSVECNormalize(&dir, &dir);
    dir2 = dir;
    fn_800BEBCC(0, VEC_ARG(dir2));
}

// .text:0x8001CBD4 size:0xF4
void fn_8001CBD4(void) {
    s32 stadium;

    if (g_d_GameSettings.GameModeSelected == 7) {
        stadium = g_d_GameSettings.StadiumID + 7;
    } else {
        stadium = g_d_GameSettings.StadiumID;
    }
    fn_8001CA40(stadium);
}

// .text:0x8001CCC8 size:0x1AC
// NONMATCHING 98.7%: scheduling of the stadium light setup
#if NONMATCHING
void fn_8001CCC8(void) {
    LightPos* lights = lbl_80367318;
    s32 i;
    StadiumLights* st;
    LightPos* lp;
    u32 c;
    GXColor color;

    lbl_8036E548._3085 = 4;
    fn_8001CBD4();
    fn_800BD2DC();
    st = &lbl_800F7478[g_d_GameSettings._54];
    if (st->ambient.a != 0) {
        color = st->ambient;
        fn_800BD2CC(1, color);
    }
    lp = lights;
    for (i = 0; i < 4; i++) {
        LITAlloc(&lbl_8036E548.lights[i]);
        LITInitAttn(lbl_8036E548.lights[i], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        LITInitPos(lbl_8036E548.lights[i], lp->x, lp->y, lp->z);
        c = lp->color;
        LITInitColor(lbl_8036E548.lights[i], &c);
        lp++;
    }
}
#endif

// .text:0x8001CE74 size:0x200
// NONMATCHING 96.1%: light-table base register and scheduling
#if NONMATCHING
void fn_8001CE74(void) {
    LightPos* lp = lbl_80367318;
    s32 i;
    StadiumLights* st;
    GXColor color;
    u32 c;

    lbl_8036E548._3085 = 4;
    fn_8001CBD4();
    fn_800BD2DC();
    st = &lbl_800F7478[g_d_GameSettings._54];
    if (st->ambient.a != 0) {
        color = st->ambient;
        fn_800BD2CC(1, color);
    }
    for (i = 0; i < 4; i++) {
        LITAlloc(&lbl_8036E548.lights[i]);
        LITInitAttn(lbl_8036E548.lights[i], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        LITInitPos(lbl_8036E548.lights[i], lp->x, lp->y, lp->z);
        c = lp->color;
        LITInitColor(lbl_8036E548.lights[i], &c);
        lp++;
    }
    if (lbl_8036E548.slots6C != NULL) {
        for (i = 0; i < lbl_8036E548.slots6C->count; i++) {
            fn_800BD548(&lbl_8036E548.slots6C->objects[i], 4, lbl_8036E548.lights[0], lbl_8036E548.lights[1], lbl_8036E548.lights[2], lbl_8036E548.lights[3]);
        }
    }
}
#endif

// .text:0x8001D074 size:0x5C
void fn_8001D074(s32 index, s32 enable) {
    CharActor* actor = lbl_8036E548.active[index];
    GameActor* model;

    if (actor != NULL) {
        model = lbl_8036E548.slots->objects[actor->modelIndex].actor;
        if (enable != 0) {
            model->flags |= 4;
        } else {
            model->flags &= 0xFB;
        }
    }
}

// .text:0x8001D0D0 size:0x40
void fn_8001D0D0(s32 index, f32 scale) {
    CTRLSetScale(&lbl_8036E548.slots68->objects[index].worldControl.base, scale, scale, scale);
}

// .text:0x8001D110 size:0x38
void fn_8001D110(s32 index, f32 x, f32 y, f32 z) {
    CTRLSetScale(&lbl_8036E548.slots68->objects[index].worldControl.base, x, y, z);
}

// .text:0x8001D148 size:0x38
void fn_8001D148(s32 index, f32 x, f32 y, f32 z) {
    CTRLSetScale(&lbl_8036E548.slots64->objects[index].worldControl.base, x, y, z);
}

// .text:0x8001D180 size:0x154
// NONMATCHING 96.2%: register allocation only
#if NONMATCHING
void fn_8001D180(s32 index, s32 which, s32 enable) {
    CharActor* actor = lbl_8036E548.active[index];
    s32 joint = actor != NULL ? actor->jointIdx[lbl_803CB7B4[which]] : 0xFFFF;
    GameActor** models;
    GameActor* model;
    GameBone* dst;
    GameActor* src;
    GameBone** jp;
    s32 i;
    s32 n;

    if (joint == 0xFFFF) {
        return;
    }
    models = &actor->model;
    i = 0;
    do {
        model = *models;
        if (enable == 0) {
            if (model != NULL && model->boneArray[joint] != NULL) {
                model->boneArray[joint]->dispObj = NULL;
            }
        } else if (lbl_800EEAAC[actor->kind] >= 0 && actor->parts != NULL) {
            dst = model->boneArray[joint];
            if (which & 1) {
                src = lbl_8036E548.partSlots->objects[actor->parts->part[1].slot].actor;
            } else {
                src = lbl_8036E548.partSlots->objects[actor->parts->part[0].slot].actor;
            }
            if (src == NULL) {
                return;
            }
            n = src->totalBones;
            jp = &src->boneArray[n];
            do {
                jp--;
                n--;
                if ((*jp)->dispObj != NULL) {
                    dst->dispObj = (*jp)->dispObj;
                    return;
                }
            } while (n != 0);
            return;
        }
        models--;
    } while (i-- != 0);
}
#endif

// .text:0x8001D2D4 size:0x8A0
static inline void updateTrailSlot(ActorObjectTable* list, s32 i, CharTrail* t) {
    list->objects[i].animateBones = t->_26 & 1;
    if (t->_26 != 0) {
        CTRLSetTranslation(&list->objects[i].worldControl.base, t->_04[0], t->_04[1], t->_04[2]);
        CTRLSetRotation(&list->objects[i].worldControl.base, 57.295776f * t->_04[3], 57.295776f * t->_04[4], 57.295776f * t->_04[5]);
    }
}

// NONMATCHING 90%: register allocation and loop strength-reduction differences
#if NONMATCHING
void fn_8001D2D4(void) {
    u32 doneMask;
    s32 i;
    CharActor* actor;
    ActorObject* slot;
    CharParts* parts;
    CharParts* parts2;
    ShapeAnimState* st0;
    ShapeAnimState* st1;
    ShapeAnimState* st2;
    GameActor* model;
    f32 scale;
    CharTrail* t;
    Vec p;
    Mtx m;

    if (lbl_8036E548._307A == 0 || lbl_8036E548._307C == 0) {
        return;
    }
    if (lbl_80366158._28 != 0) {
        lbl_803CBC3C[0] = 1;
    }
    fn_8001C234(&doneMask);
    for (i = 0; i < 13; i++) {
        actor = lbl_8036E548.active[i];
        if (actor == NULL) {
            continue;
        }
        slot = &lbl_8036E548.slots->objects[actor->modelIndex];
        switch (actor->kind) {
        case 19:
            fn_8004B6EC(actor, slot);
            break;
        case 40:
        case 41:
            fn_8004B7F4(actor, slot);
            break;
        case 38:
            slot->actor->tickFlag = 1;
        case 18:
            fn_8004BAEC(actor, slot);
            break;
        case 14:
        case 37:
            fn_8005240C(actor, slot);
            break;
        case 6:
        case 10:
        case 12:
        case 24:
        case 25:
        case 26:
        case 42:
            slot->actor->tickFlag = 1;
            break;
        case 20:
        case 43:
            if (actor->anim[0] == 0x40) {
                slot->actor->tickFlag = 0;
            } else {
                slot->actor->tickFlag = 1;
            }
            break;
        }
    }
    for (i = 0; i < lbl_8036E548.slots->count; i++) {
        lbl_8036E548.slots->objects[i].animateBones = 0;
    }
    for (i = 0; i < 13; i++) {
        actor = lbl_8036E548.active[i];
        if (actor == NULL) {
            continue;
        }
        slot = &lbl_8036E548.slots->objects[actor->modelIndex];
        if (actor->part != NULL) {
            st0 = &actor->part->player.state;
        } else {
            st0 = NULL;
        }
        parts = actor->parts;
        if (parts != NULL) {
            st1 = &parts->part[0].player.state;
            st2 = &parts->part[1].player.state;
        } else {
            st1 = NULL;
            st2 = NULL;
        }
        slot->animateBones = actor->mode[0];
        CTRLSetRotation(&slot->worldControl.base, 57.295776f * actor->rot.x, 57.295776f * actor->rot.y, 57.295776f * actor->rot.z);
        scale = charSizeMultipliers[actor->kind][lbl_8036E548._307A == 5];
        CTRLSetScale(&slot->worldControl.base, scale, scale, scale);
        if (lbl_803CBC3C[0] != 0) {
            slot->unk54 = 0.0f;
            slot->setSpeed = 1;
            if (st0 != NULL) {
                st0->active = 0;
            }
            if (st1 != NULL) {
                st1->active = 0;
            }
            if (st2 != NULL) {
                st2->active = 0;
            }
        } else if (actor->_26F != 0) {
            slot->unk54 = 0.0f;
            slot->setSpeed = 1;
            actor->_26F = 0;
            if (st0 != NULL) {
                st0->active = 0;
            }
            if (st1 != NULL) {
                st1->active = 0;
            }
            if (st2 != NULL) {
                st2->active = 0;
            }
        } else {
            slot->unk54 = actor->_04C;
            slot->setSpeed = 1;
            if (st0 != NULL) {
                st0->speed = actor->_04C;
            }
            if (st1 != NULL) {
                st1->speed = actor->_04C;
            }
            if (st2 != NULL) {
                st2->speed = actor->_04C;
            }
            if (st0 != NULL) {
                st0->active = 1;
            }
            if (st1 != NULL) {
                st1->active = 1;
            }
            if (st2 != NULL) {
                st2->active = 1;
            }
        }
        if (actor->_068 != 0) {
            if (actor->part != NULL) {
                fn_80024DB0(&actor->part->player.state);
            }
            parts = actor->parts;
            if (parts != NULL && parts->part[0].player.set != NULL && parts->part[1].player.set != NULL && parts->_CC != 0) {
                fn_80024DB0(&parts->part[0].player.state);
                fn_80024DB0(&actor->parts->part[1].player.state);
            }
        }
    }
    fn_8001DB74(lbl_8036E548.slots);
    for (i = 0; i < 13; i++) {
        actor = lbl_8036E548.active[i];
        if (actor == NULL || actor->mode[0] == 0) {
            continue;
        }
        slot = &lbl_8036E548.slots->objects[actor->modelIndex];
        model = slot->actor;
        if (!(model->flags & 9)) {
            continue;
        }
        if (model != NULL) {
            p.z = 0.0f;
            p.y = 0.0f;
            p.x = 0.0f;
            fn_800B2C88(model, model->rootBone, m);
            PSMTXTransApply(m, m, actor->pos.x, actor->pos.y, actor->pos.z);
            PSMTXMultVec(m, &p, &p);
            fn_800BEA04(p);
        }
        if (actor->part != NULL) {
            fn_80024FA4((ShapeModel**)&slot->actor, actor->part->player.model, &actor->part->player.state, -1);
        }
        parts = actor->parts;
        if (parts != NULL && parts->part[0].player.set != NULL && parts->part[1].player.set != NULL && parts->_CC != 0) {
            if (actor->anim[0] >= 0x3A && actor->anim[0] <= 0x3C && actor->_25B == 0) {
                fn_80024FA4((ShapeModel**)&lbl_8036E548.partSlots->objects[parts->part[0].slot].actor, parts->part[0].player.model, &parts->part[1].player.state, fn_80024C6C(actor, 0));
                parts2 = actor->parts;
                fn_80024FA4((ShapeModel**)&lbl_8036E548.partSlots->objects[parts2->part[1].slot].actor, parts->part[1].player.model, &parts2->part[0].player.state, fn_80024C6C(actor, 1));
            } else {
                fn_80024FA4((ShapeModel**)&lbl_8036E548.partSlots->objects[parts->part[0].slot].actor, parts->part[0].player.model, &parts->part[0].player.state, fn_80024C6C(actor, 1));
                parts2 = actor->parts;
                fn_80024FA4((ShapeModel**)&lbl_8036E548.partSlots->objects[parts2->part[1].slot].actor, parts2->part[1].player.model, &parts2->part[1].player.state, fn_80024C6C(actor, 0));
            }
        }
    }
    if (lbl_8036E548._307A == 2) {
        lbl_803CBC3C[0] = 0;
        return;
    }
    lbl_803CBC3C[0] = 0;
    if (lbl_8036E548.trail != NULL) {
        if (lbl_8036E548.trail[5]._26 != 0) {
            fn_80024DB0(&lbl_8036E548.stadiumAnim[0].state);
            fn_80024FA4((ShapeModel**)&lbl_8036E548.slots64->objects[5].actor, lbl_8036E548.stadiumAnim[0].model, &lbl_8036E548.stadiumAnim[0].state, -1);
        }
        if (lbl_8036E548.trail[6]._26 != 0) {
            fn_80024DB0(&lbl_8036E548.stadiumAnim[1].state);
            fn_80024FA4((ShapeModel**)&lbl_8036E548.slots64->objects[6].actor, lbl_8036E548.stadiumAnim[1].model, &lbl_8036E548.stadiumAnim[1].state, -1);
        }
        for (i = 0; i < 25; i++) {
            t = &lbl_8036E548.trail[i];
            if (i == 4) {
                t->_26 = 0;
                lbl_8036E548.slots64->objects[i].animateBones = t->_26;
            }
            updateTrailSlot(lbl_8036E548.slots64, i, t);
        }
        fn_800BD8C4(lbl_8036E548.slots64, fn_80052734(0)->view);
    }
    if (lbl_8036E548._3078 != 0) {
        for (i = 0; i < lbl_8036E548._3078; i++) {
            updateTrailSlot(lbl_8036E548.slots68, i, &lbl_8036E548.trail2[i]);
        }
        fn_800BD8C4(lbl_8036E548.slots68, fn_80052734(0)->view);
    }
    if (lbl_8036E548._3070 != NULL) {
        lbl_8036E548._3070(fn_80052734(0)->view);
        lbl_8036E548._3070 = NULL;
    }
}
#endif

// .text:0x8001DB74 size:0x1E4
// NONMATCHING 96.2%: register allocation of the slot/camera loops
#if NONMATCHING
void fn_8001DB74(ActorObjectTable* list) {
    u16 i;
    u16 k;
    CharActor* actor;
    ActorObject* slot;
    GameActor* model;
    MtxPtr view;
    u8 mask;
    s32 shift;
    Mtx m;

    for (i = 0; i < list->count; i++) {
        actor = lbl_8036E548.active[i];
        if (actor == NULL || actor->mode[0] == 0) {
            continue;
        }
        slot = &lbl_8036E548.slots->objects[actor->modelIndex];
        if (slot->actor == NULL) {
            continue;
        }
        if (slot->setAnimation != 0) {
            ACTSetAnimation(slot->actor, slot->animBank, 0, slot->seqNum, 0.0f, slot->speed);
        }
        if (slot->setTime != 0) {
            fn_800B4CA0(slot->actor, slot->time);
        }
        if (slot->setSpeed != 0) {
            fn_800B4C04(slot->actor, slot->unk54);
        }
        if (slot->visFlags & 2) {
            fn_800B4AFC(slot->actor, slot->visFlags & 1);
        }
        Set_FUN_800b2b6c(slot->actor, slot->boneRemap);
        if (slot->animateBones != 0) {
            fn_800BDA24(slot);
        }
        for (k = 0; k < fn_800527BC(); k++) {
            view = fn_80052734(k)->view;
            shift = k * 3;
            mask = ~(3 << shift);
            if (lbl_8036E548._307A == 5) {
                slot->actor->flags = 1;
            } else {
                PSMTXTrans(m, actor->pos.x, actor->pos.y, actor->pos.z);
                PSMTXConcat(view, m, m);
                model = slot->actor;
                model->flags = (model->flags & mask) | (fn_800B3C04(k, model, m) << shift);
            }
        }
        slot->setAnimation = 0;
        slot->setTime = 0;
        slot->setSpeed = 0;
        slot->visFlags &= 1;
    }
}
#endif

// .text:0x8001DD58 size:0x14C
void fn_8001DD58(GameActor* model, s32 pass, MtxPtr view, u8 n, ...) {
    va_list args;
    GameBone* joint;

    if (model->flags & (1 << (pass * 3))) {
        if (model->skinObject != NULL) {
            GXInvalidateVtxCache();
            va_start(args, n);
            if (model->skHeader != NULL) {
                DOVARender(model->skinObject, view, n, &args);
            } else {
                DOVARenderSkin(model->skinObject, view, (MtxPtr)model->skinMtxArray, (MtxPtr)model->skinInvTransposeMtxArray, n, &args);
            }
        }
        for (joint = (GameBone*)model->drawPriorityList.Head; joint != NULL; joint = (GameBone*)joint->drawPriorityLink.Next) {
            if (joint->dispObj != NULL) {
                DOSetWorldMatrix(joint->dispObj, joint->forwardMtx);
            }
            va_start(args, n);
            DOVARender(joint->dispObj, view, n, &args);
        }
    }
}

// .text:0x8001DEA4 size:0x234
void fn_8001DEA4(ActorObject* slot, s32 pass, MtxPtr view) {
    drawSlot(slot, pass, view);
}

// .text:0x8001E0D8 size:0x388
// NONMATCHING 98.9%: slot/loop-counter registers swapped
#if NONMATCHING
void fn_8001E0D8(ActorObjectTable* list, s32 pass, Mtx view) {
    u8 last = 0xFF;
    GXColor amb = lbl_800F7478[g_d_GameSettings._54].ambient;
    GXColor c;
    u16 i;
    CharActor* actor;
    ActorObject* slot;
    Mtx m;

    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (i = 0; i < list->count; i++) {
        actor = lbl_8036E548.active[i];
        if (actor == NULL || actor->mode[0] == 2) {
            continue;
        }
        slot = &lbl_8036E548.slots->objects[actor->modelIndex];
        if (slot->actor == NULL || slot->animateBones == 0) {
            continue;
        }
        if (last != actor->_277) {
            last = actor->_277;
            if (0xFF - last != 0) {
                amb.a = last;
                if (last == 0) {
                    continue;
                }
                c = amb;
                fn_800BD2CC(1, c);
            } else {
                fn_800BD2CC(1, lbl_800F7478[g_d_GameSettings._54].ambient);
            }
        }
        PSMTXTrans(m, actor->pos.x, actor->pos.y, actor->pos.z);
        PSMTXConcat(view, m, m);
        fn_800B9948(actor->tevHook);
        lbl_803CBC18 = actor;
        fn_8001DEA4(slot, pass, m);
    }
    fn_800B993C();
}
#endif



// fn_8001E460, size:0x14
void fn_8001E460(CharDrawCallback value) {
    lbl_803CB7AC[lbl_803CBBC0] = value;
}

// fn_8001E474, size:0x14
void fn_8001E474(void) {
    lbl_803CB7AC[0] = 0;
    lbl_803CB7AC[1] = 0;
}

// .text:0x8001E488 size:0x2FC
void fn_8001E488(void) {
    int blend;
    CharActor* actor;
    ActorObject* slot;
    s32 i;
    Mtx* view;
    f32 x;
    f32 y;
    Mtx44 proj;

    blend = GX_BM_BLEND;
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(blend, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
#ifdef TARGET_PC
    {
        extern int port_spani_trace_on(void);
        extern u32 port_spani_trace_frame;
        extern void OSReport(const char*, ...);
        static s32 s_last[4] = {-1, -1, -1, -1};
        if (port_spani_trace_on()) {
            for (i = 0; i < 4 && i < lbl_8036E548.slots->count; i++) {
                s32 r;
                actor = lbl_8036E548.active[i];
                slot = &lbl_8036E548.slots->objects[i];
                if (actor == NULL) r = 1;
                else if (slot->actor == NULL) r = 2;
                else if (slot->animateBones == 0) r = 3;
                else r = 0;
                if (r != s_last[i]) {
                    OSReport("[mdl] f=%u player %d %s (kind %d mode %d alpha %d)\n", port_spani_trace_frame, (int)i,
                             r == 0 ? "DRAWN" : r == 1 ? "no-actor" : r == 2 ? "no-model" : "animateBones=0",
                             actor ? (int)actor->kind : -1, actor ? (int)actor->mode[0] : -1, actor ? (int)actor->_277 : -1);
                    s_last[i] = r;
                }
            }
        }
    }
#endif
    for (i = 0; i < lbl_8036E548.slots->count; i++) {
        actor = lbl_8036E548.active[i];
        if (actor != NULL) {
            slot = &lbl_8036E548.slots->objects[i];
            if (slot->actor != NULL && slot->animateBones != 0) {
                x = actor->pos.x / 1280.0f;
                y = actor->pos.y / 1280.0f;
                C_MTXFrustum(proj, (-0.175f) + y, 0.175f + y, 0.25f + x, (-0.25f) + x, 1.0f, 512.0f);
                GXSetProjection(proj, GX_PERSPECTIVE);
                view = &fn_80052734(0)->view;
                fn_8001DEA4(slot, 0, *view);
            }
        }
    }
}

// .text:0x8001E784 size:0x9E8
static inline void drawTrailObjects(void) {
    s32 i;
    ActorObject* slot;

    if (lbl_8036E548._3078 != 0) {
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
        GXSetCullMode(GX_CULL_BACK);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        for (i = 0; i < lbl_8036E548.slots68->count; i++) {
            slot = &lbl_8036E548.slots68->objects[i];
            if (slot->actor != NULL && slot->animateBones != 0) {
                if (lbl_8036E548.trail2[i].draw != NULL) {
#ifdef TARGET_PC
                    // The minigame callbacks (rep_3310: fn_3_1194AC, fn_3_11897C, ...) take the slot
                    // index; on the GameCube it was already in r3 here. Pass it explicitly.
                    ((void (*)(s32))lbl_8036E548.trail2[i].draw)(i);
#else
                    lbl_8036E548.trail2[i].draw();
#endif
                }
                fn_800BDA94(slot, fn_80052734(0)->view);
            }
        }
    }
}

static inline void drawMinigameLayer(void) {
    fn_8003414C(fn_80052734(fn_8005268C())->view);
    minigamesGXStuff();
}

// NONMATCHING 93%: register allocation (measured with fn_8001E488 compiled, as in the NONMATCHING build;
// the original inlines it, so this function only reaches 64% while fn_8001E488 is left out)
#if NONMATCHING
void fn_8001E784(void) {
    LightPos* lp;
    StadiumLights* st;
    GXColor c;
    u32 color;
    Vec dir;
    s32 i;
    s32 cam;
    u8 sel;

    GXSetCurrentGXThread();
    if (lbl_8036E548._307A != 0) {
        lp = lbl_80367318;
        if (lbl_8036E548._3085 != 0) {
            st = &lbl_800F7478[g_d_GameSettings._54];
            c = st->ambient;
            fn_800BD2CC(st->ambient.a != 0, c);
            for (i = 0; i < 4; i++) {
                LITInitAttn(lbl_8036E548.lights[i], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
                LITInitPos(lbl_8036E548.lights[i], lp->x, lp->y, lp->z);
                color = lp->color;
                LITInitColor(lbl_8036E548.lights[i], &color);
                dir.x = lp->x;
                dir.y = lp->y;
                dir.z = lp->z;
                PSVECNormalize(&dir, &dir);
                LITInitDir(lbl_8036E548.lights[i], dir.x, dir.y, dir.z);
                LITXForm(lbl_8036E548.lights[i], fn_80052734(0)->view);
                lp++;
            }
        }
        cam = fn_800527BC() - 1;
        do {
            fn_80052694(cam);
            if (lbl_8036E548._307A == 3) {
                if (lbl_803CB7AC[lbl_803CBBC0 == 0] != NULL) {
                    lbl_803CB7AC[lbl_803CBBC0 == 0](fn_80052734(cam)->view, 0, 1);
                }
                if (lbl_803CB7AC[lbl_803CBBC0 == 0] != NULL) {
                    lbl_803CB7AC[lbl_803CBBC0 == 0](fn_80052734(cam)->view, 1, 1);
                    lbl_803CB7AC[lbl_803CBBC0 == 0] = NULL;
                }
                drawTrailObjects();
                if (lbl_8036E548._307E != 0) {
                    drawMinigameLayer();
                }
            } else if (lbl_8036E548._307A == 5) {
                fn_8001E488();
            } else if (lbl_8036E548._307A == 2) {
                GXSetZCompLoc(GX_FALSE);
                fn_8001E0D8(lbl_8036E548.slots, cam, fn_80052734(cam)->view);
            } else if (lbl_8036E548._307A == 4) {
                fn_8001E0D8(lbl_8036E548.slots, cam, fn_80052734(cam)->view);
                drawTrailObjects();
                drawMinigameLayer();
            } else {
                if (lbl_803CB7AC[lbl_803CBBC0 == 0] != NULL) {
                    lbl_803CB7AC[lbl_803CBBC0 == 0](fn_80052734(cam)->view, 0, 1);
                }
                if (lbl_8036E548._307C != 0) {
                    fn_8001E0D8(lbl_8036E548.slots, cam, fn_80052734(cam)->view);
                    fn_800BD670(lbl_8036E548.slots64, fn_80052734(cam)->view);
                    drawTrailObjects();
                    if (lbl_8036E548._3074 != NULL) {
                        lbl_8036E548._3074(fn_80052734(cam)->view);
                        lbl_8036E548._3074 = NULL;
                    }
                }
                if (lbl_803CB7AC[lbl_803CBBC0 == 0] != NULL) {
                    lbl_803CB7AC[lbl_803CBBC0 == 0](fn_80052734(cam)->view, 1, 1);
                    lbl_803CB7AC[lbl_803CBBC0 == 0] = NULL;
                }
                if (lbl_8036E548._307E != 0) {
                    drawMinigameLayer();
                }
            }
        } while (cam-- != 0);
        GXSetScissor(0, 0, 640, 448);
        return;
    }
    if (lbl_8036E548._3088 != 0 && lbl_8036E548._307E != 0) {
        if (lbl_803CB7AC[lbl_803CBBC0 == 0] != NULL) {
            lbl_803CB7AC[lbl_803CBBC0 == 0](fn_80052734(0)->view, 0, 1);
        }
        if (lbl_803CB7AC[lbl_803CBBC0 == 0] != NULL) {
            lbl_803CB7AC[lbl_803CBBC0 == 0](fn_80052734(0)->view, 1, 1);
            lbl_803CB7AC[lbl_803CBBC0 == 0] = NULL;
        }
    }
    drawMinigameLayer();
}
#endif

// .text:0x8001F16C size:0xBC
// NONMATCHING 99.1%: loop counter and active[] walker swap r28/r30
#if NONMATCHING
void fn_8001F16C(void) {
    ActorObjectTable* list;
    s32 i;
    CharActor* actor;
    ActorObject* slot;
    u8 st = lbl_8036E548._307A;

    if (st != 0 && st != 3) {
        list = lbl_8036E548.slots;
        for (i = 0; i < list->count; i++) {
            actor = lbl_8036E548.active[i];
            if (actor != NULL) {
                slot = &lbl_8036E548.slots->objects[actor->modelIndex];
                if (slot->actor != NULL && slot->animateBones != 0) {
                    fn_800B2D5C(slot->actor);
                }
            }
        }
    }
}
#endif

// .text:0x8001F228 size:0x298
void fn_8001F228(void) {
    s32 i;
    s32 j;

    lbl_8036E548._307A = 0;
    lbl_8036E548._0004[0] = 0;
    lbl_8036E548._0004[1] = 0;
    for (i = 0; i < 21; i++) {
        lbl_8036E548._000C[i] = 0;
    }
    lbl_8036E548.slots = NULL;
    lbl_8036E548.slots64 = NULL;
    lbl_8036E548.slots68 = NULL;
    lbl_8036E548.slots6C = NULL;
    lbl_8036E548._0070 = 0;
    for (i = 0; i < 13; i++) {
        lbl_8036E548.actors[i]._25C = 0;
        lbl_8036E548.active[i] = NULL;
    }
    lbl_8036E548.stadiumFiles = NULL;
    lbl_8036E548._2C88 = NULL;
    lbl_8036E548.fileBuf = NULL;
    // NOTE: the original clears 16 entries per bankSets row, running past the
    // end of bankSets into preload[] and _2D60/_2D64.
    for (i = 0; i < 16; i++) {
        lbl_8036E548.animBufs[i] = NULL;
        for (j = 0; j < 4; j++) {
            lbl_8036E548.bankSets[j][i] = NULL;
        }
    }
    for (i = 0; i < 13; i++) {
        lbl_8036E548._2D6A[i] = -1;
    }
    lbl_8036E548.trail = NULL;
    lbl_8036E548.trail2 = NULL;
    lbl_8036E548._2D98 = 0;
    lbl_8036E548.trailFile = NULL;
    lbl_8036E548._307C = 0;
    lbl_8036E548._3085 = 0;
    lbl_8036E548.callback = NULL;
    lbl_8036E548._3087 = 0;
    lbl_8036E548._3086 = 0;
    DrawShadows(0);
}

// .text:0x8001F4C0 size:0x128
void challengeMapMaybe(void) {
    s32 i;
    CharActor* actor;

    for (i = 0; i < 13; i++) {
        actor = &lbl_8036E548.actors[i];
        actor->_25C = 0;
        actor->mode[0] = 0;
        actor->_04C = 0.5f;
        actor->_060 = 0;
        actor->anim[0] = 0;
        actor->anim[1] = 0;
        actor->_06A[0] = 0;
        actor->mode[1] = 1;
        actor->_268 = 0;
        actor->_273 = 0;
        actor->_274 = 0;
        actor->_278 = 0;
        actor->tevHook = NULL;
        actor->pos.x = 0.0f;
        actor->pos.y = 0.0f;
        actor->pos.z = 0.0f;
        actor->rot.x = 0.0f;
        actor->rot.y = 0.0f;
        actor->rot.z = 0.0f;
        actor->_070 = -1;
    }
    for (i = 0; i < 13; i++) {
        if (lbl_8036E548.active[i] != NULL) {
            lbl_8036E548.active[i]->_25C = 1;
        }
    }
    for (i = 0; i < 25; i++) {
        lbl_8036E548.trail[i]._26 = 0;
        lbl_8036E548.trail[i]._04[0] = 0.0f;
        lbl_8036E548.trail[i]._04[1] = 0.0f;
        lbl_8036E548.trail[i]._04[2] = 0.0f;
        lbl_8036E548.trail[i]._04[3] = 0.0f;
        lbl_8036E548.trail[i]._04[4] = 0.0f;
        lbl_8036E548.trail[i]._04[5] = 0.0f;
    }
    lbl_8036E548._3078 = 0;
}

// .text:0x8001F5E8 size:0x2BC
// NONMATCHING 70%: original reloads the relocated trail pointers and indexes the trail array; ours keeps them in registers
#if NONMATCHING
void fn_8001F5E8(void) {
    u32* file;
    void* layout;
    void* geo;
    void* tex;
    s32 count = 30;
    s32 i;

    lbl_8036E548._3078 = count;
    // TODO type: file header of offsets, relocated here.
    file = lbl_8036E548.trailFile;
#ifdef TARGET_PC
    port_swap_offset_header(file, 5);
#endif
    lbl_8036E548.trailLayout = (u8*)file + file[0];
    lbl_8036E548.trailGeo = (u8*)file + file[1];
    lbl_8036E548.trailTex = (u8*)file + file[2];
    layout = lbl_8036E548.trailLayout;
    geo = lbl_8036E548.trailGeo;
    tex = lbl_8036E548.trailTex;
    LoadActorLayout(layout);
    convertGeometryAndSknHeader(geo, NULL);
    haveActLayoutPointToGeoHeader(layout, geo);
    convertTextureHeader(tex);
    fn_800BD190(geo, tex);
    lbl_8036E548.slots68 = ActorObjectInitTable(count);
    for (i = 0; i < count; i++) {
        fn_800BDC88(lbl_8036E548.slots68, i, i, lbl_8036E548.trailLayout, 0, 0);
        fn_800BD548(&lbl_8036E548.slots68->objects[i], 4, lbl_8036E548.lights[0], lbl_8036E548.lights[1], lbl_8036E548.lights[2], lbl_8036E548.lights[3]);
        CTRLSetTranslation(&lbl_8036E548.slots68->objects[i].worldControl.base, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(&lbl_8036E548.slots68->objects[i].worldControl.base, 0.0f, 0.0f, 0.0f);
    }
    lbl_8036E548.trail2 = _OSAllocFromHeap(0x20, count * sizeof(CharTrail));
    for (i = 0; i < count; i++) {
        lbl_8036E548.trail2[i]._04[0] = 0.0f;
        lbl_8036E548.trail2[i]._04[1] = 0.0f;
        lbl_8036E548.trail2[i]._04[2] = 0.0f;
        lbl_8036E548.trail2[i]._04[3] = 0.0f;
        lbl_8036E548.trail2[i]._04[4] = 0.0f;
        lbl_8036E548.trail2[i]._04[5] = 0.0f;
        lbl_8036E548.trail2[i]._26 = 0;
        lbl_8036E548.trail2[i].draw = NULL;
    }
}
#endif

// .text:0x8001F8A4 size:0x3A8
// NONMATCHING 89%: register allocation; light-kind range checks scheduled differently
#if NONMATCHING
void fn_8001F8A4(void) {
    s32 i;
    void* layout;
    void* geo;
    void* tex;
    u8* kind;
    ActorObject* slot;

    for (i = 0; i < 24; i++) {
        layout = PTR32_GET(void, lbl_8036E548.stadiumFiles->obj[i].layout);
        geo = PTR32_GET(void, lbl_8036E548.stadiumFiles->obj[i].geo);
        tex = PTR32_GET(void, lbl_8036E548.stadiumFiles->obj[i].tex);
        LoadActorLayout(layout);
        convertGeometryAndSknHeader(geo, NULL);
        haveActLayoutPointToGeoHeader(layout, geo);
        if (i == 11) {
            tex = PTR32_GET(void, lbl_8036E548.stadiumFiles->obj[10].tex);
        } else {
            convertTextureHeader(tex);
        }
        fn_800BD190(geo, tex);
    }
    ANIMGet(PTR32_GET(void, lbl_8036E548.stadiumFiles->bank));
    fn_80025DDC(PTR32_GET(void, lbl_8036E548.stadiumFiles->anim[0].shape));
    lbl_8036E548.stadiumAnim[0].set = PTR32_GET(ShapeAnimSet, lbl_8036E548.stadiumFiles->anim[0].set);
    fn_80025FFC(PTR32_GET(void, lbl_8036E548.stadiumFiles->anim[0].shape), &lbl_8036E548.stadiumAnim[0]);
    fn_80025EEC(&lbl_8036E548.stadiumAnim[0], 0, 0);
    fn_80025DDC(PTR32_GET(void, lbl_8036E548.stadiumFiles->anim[1].shape));
    lbl_8036E548.stadiumAnim[1].set = PTR32_GET(ShapeAnimSet, lbl_8036E548.stadiumFiles->anim[1].set);
    fn_80025FFC(PTR32_GET(void, lbl_8036E548.stadiumFiles->anim[1].shape), &lbl_8036E548.stadiumAnim[1]);
    fn_80025EEC(&lbl_8036E548.stadiumAnim[1], 0, 0);
    lbl_8036E548.slots64 = ActorObjectInitTable(25);
    kind = lbl_800EEA58;
    for (i = 0; i < 25; i++) {
        layout = PTR32_GET(void, lbl_8036E548.stadiumFiles->obj[*kind].layout);
        if (*kind < 0x10) {
            fn_800BDC88(lbl_8036E548.slots64, i, i, layout, 0, 0);
        } else {
            fn_800BDC88(lbl_8036E548.slots64, i, i, layout, PTR32_GET(void, lbl_8036E548.stadiumFiles->bank), 0);
            slot = &lbl_8036E548.slots64->objects[i];
            slot->seqNum = 0;
            slot->time = 0.0f;
            slot->setAnimation = 1;
            slot->setTime = slot->animBank != NULL;
            slot->setSpeed = slot->animBank != NULL;
            slot->speed = 0.0f;
            ACTSetAnimation(slot->actor, slot->animBank, 0, slot->seqNum, 0.0f, slot->speed);
            fn_800B4AFC(slot->actor, 0);
        }
        if (*kind == 0 || *kind == 4 || (*kind >= 7 && *kind <= 10) || (*kind >= 12 && *kind <= 18) || *kind == 19) {
            fn_800BD548(&lbl_8036E548.slots64->objects[i], 4, lbl_8036E548.lights[0], lbl_8036E548.lights[1], lbl_8036E548.lights[2], lbl_8036E548.lights[3]);
        } else {
            fn_800BD548(&lbl_8036E548.slots64->objects[i], 0, 0, 0, 0);
        }
        CTRLSetTranslation(&lbl_8036E548.slots64->objects[i].worldControl.base, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(&lbl_8036E548.slots64->objects[i].worldControl.base, 0.0f, 0.0f, 0.0f);
        if (i == 5) {
            fn_80025C58(lbl_8036E548.stadiumAnim[0].model, (ShapeModel**)&lbl_8036E548.slots64->objects[i].actor);
        } else if (i == 6) {
            fn_80025C58(lbl_8036E548.stadiumAnim[1].model, (ShapeModel**)&lbl_8036E548.slots64->objects[i].actor);
        }
        kind++;
    }
    lbl_8036E548.trail = _OSAllocFromHeap(0x20, 25 * sizeof(CharTrail));
    for (i = 0; i < 25; i++) {
        lbl_8036E548.trail[i]._04[0] = 0.0f;
        lbl_8036E548.trail[i]._04[1] = 0.0f;
        lbl_8036E548.trail[i]._04[2] = 0.0f;
        lbl_8036E548.trail[i]._04[3] = 0.0f;
        lbl_8036E548.trail[i]._04[4] = 0.0f;
        lbl_8036E548.trail[i]._04[5] = 0.0f;
        lbl_8036E548.trail[i]._26 = 0;
        lbl_8036E548.trail[i].draw = NULL;
    }
}
#endif

// .text:0x8001FC4C size:0x188
static inline void mirrorJointPairs(CharActor* actor, u16* pairs) {
    u16 a;
    u16 b;

    for (; pairs[0] != 0xFFFF; pairs += 2) {
        a = actor->jointIdx[pairs[0]];
        b = actor->jointIdx[pairs[1]];
        if (a != 0xFFFF && b != 0xFFFF) {
            actor->mirror[a] = b;
            actor->mirror[b] = a;
        }
    }
}

// NONMATCHING 84%: mirror tables are addressed from lbl_800EE930 instead of the original's lbl_800EE800 anchor (this unit's .data is not split)
#if NONMATCHING
void fn_8001FC4C(CharActor* actor) {
    s32 i;
    u16* pairs;

    for (i = 0; i < 0x78; i++) {
        actor->mirror[i] = i;
    }
    pairs = lbl_800EE930.mirrorPairs;
    i = 0;
    do {
        u16 a = actor->jointIdx[pairs[0]];
        u16 b = actor->jointIdx[pairs[1]];
        if (a != 0xFFFF && b != 0xFFFF) {
            actor->mirror[a] = b;
            actor->mirror[b] = a;
        }
        i += 2;
        pairs += 2;
    } while (lbl_800EE930.mirrorPairs[i] != 0xFFFF);
    switch (actor->kind) {
    case 20:
    case 43:
        pairs = lbl_803CB798;
        break;
    case 41:
        pairs = lbl_800EE930.mirrorPairs41;
        break;
    case 17:
        pairs = lbl_803CB7A0;
        break;
    case 16:
    case 44:
    case 45:
    case 46:
    case 47:
        pairs = lbl_800EE930.mirrorPairs16;
        break;
    default:
        pairs = NULL;
        break;
    }
    if (pairs == NULL) {
        return;
    }
    mirrorJointPairs(actor, pairs);
}
#endif

// .text:0x8001FDD4 size:0x2C
void fn_8001FDD4(ActorObject* slot) {
    if (slot->lights[0] != NULL) {
        fn_800B9AA8(slot->lights[0]);
    }
}

// ---- Data (initialisers generated from the original DOL) ----

// .bss 0x80118220..0x80118740 (MWCC lays these out in reverse definition order)
CharPart lbl_80118220[13];

// .sdata 0x803CB790..0x803CB7C8
extern DiskFileEntry lbl_800F1D78[];
DiskFileEntry *lbl_803CB790 = lbl_800F1D78;
extern DiskFileEntry lbl_800F71D8[];
DiskFileEntry *lbl_803CB794 = lbl_800F71D8;
u16 lbl_803CB798[4] = {74, 75, 65535, 0};
u16 lbl_803CB7A0[4] = {47, 52, 65535, 0};
extern DiskFileEntry lbl_800F5D98[];
DiskFileEntry *lbl_803CB7A8 = lbl_800F5D98;
CharDrawCallback lbl_803CB7AC[2] = {NULL, NULL};
u8 lbl_803CB7B4[8] = {19, 25, 20, 26, 74, 75, 60, 61};
f32 lbl_803CB7BC = 2.0f;
u8 lbl_803CB7C0 = 32;
u8 lbl_803CB7C1 = 255;
u8 lbl_803CB7C2 = 1;
u8 lbl_803CB7C4[4] = {0, 1, 2, 3}; // NOTE: type size 0x4 != symbol size 0x1
// lbl_803CB7C5 is part of the object above

// .sbss 0x803CBBF0..0x803CBC40 (MWCC lays these out in reverse definition order)
u8 lbl_803CBC3C[4];
u8 lbl_803CBC34[8];
void* lbl_803CBC30;
u8 lbl_803CBC2C;
s32 lbl_803CBC28;
u8* lbl_803CBC24;
CharParts* lbl_803CBC20;
CharPart* lbl_803CBC1C;
CharActor* lbl_803CBC18;
u8 lbl_803CBC15;
u8 lbl_803CBC14;
CharPart* lbl_803CBC10;
u8 lbl_803CBC0C;
void* lbl_803CBC08;
u8 lbl_803CBC04;
void* lbl_803CBC00;
u8 lbl_803CBBFD;
u8 lbl_803CBBFC;
u8 lbl_803CBBFB;
u8 lbl_803CBBFA;
u8 lbl_803CBBF9;
u8 lbl_803CBBF8;
void (*lbl_803CBBF4)(void);
u32 lbl_803CBBF0;


#ifdef PORT_LP64
#include <stddef.h>
// MinigameActorView (game/auto_00_000DEB90_text.h) hard-codes these PC offsets.
_Static_assert(offsetof(CharActor, pos) == 0x68, "MinigameActorView.pos");
_Static_assert(offsetof(CharActor, rot) == 0x74, "MinigameActorView._40/rotY");
_Static_assert(offsetof(CharActor, mode) == 0x295, "MinigameActorView.visible");
#endif
