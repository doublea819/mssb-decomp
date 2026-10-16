#include "main/file_80034F50.h"
#include "Dolphin/os.h"
#include "Dolphin/stl.h"
#include "main/file_8004C5F8.h" // lbl_803C5F74, fn_80052734

// spani_default.c

typedef struct SpaniPad {
    /*0x00*/ u16 held;
    /*0x02*/ u16 unk2;
    /*0x04*/ u16 trig;
    /*0x06*/ u8 unk6[0x20 - 0x06];
} SpaniPad;

typedef struct SpaniDrawState {
    /*0x00*/ u8 unk0[0x84];
    /*0x84*/ s32 unk84;
    /*0x88*/ void (*drawCallback)(void);
    /*0x8C*/ u8 unk8C[0x90 - 0x8C];
} SpaniDrawState;

extern SpaniObj lbl_8039C3E0[SPANI_OBJ_COUNT];     // sprite objects
extern SpaniRef lbl_80371C30[];                    // owner-indexed sprite references
extern SpaniTexSlot lbl_803C4BE0[SPANI_TEX_SLOT_COUNT]; // loaded texture/anim banks
extern s16 lbl_8023D6C0[SPANI_OBJ_COUNT];          // texture slot -> id
extern SpaniPad lbl_803C77B8[4];
#include "main/aramloader.h" // lbl_803C6CF8
extern SpaniDrawState lbl_80366188;
extern Mtx lbl_800F78E0[4];
extern Mtx44 lbl_801F8640;
extern Mtx44 lbl_801F8680;
#ifdef TARGET_PC
// PC: 32KB more sprite display list per buffer (Career Mode's menu text lives on layer 8).
#define SPRITE_DL_POOL 0x2A800
#else
#define SPRITE_DL_POOL 0x22800
#endif
extern u8 lbl_801F86C0[];

typedef struct SpaniStrings {
    char noSlot[0x1C];  // " SabNo = %d not to add  \n"
    char file[0x10];    // "spani_default.c"
    char noEmpty[0x14]; // "gasSpani No Empty \n"
} SpaniStrings;
extern SpaniStrings lbl_800E68A8;
extern char lbl_800E68C4[]; // "spani_default.c"
extern char lbl_800E68E8[]; // "It is a number not registered. \n"

extern s32 lbl_803CB810;
extern s32 lbl_803CB814;
extern f32 lbl_803CBBDC;
extern f32 lbl_803CBBE0;
extern u8 lbl_803CBBE4;
extern u8 lbl_803CBC90;
extern u8 lbl_803CBC91;
extern void* lbl_803CBC94;
extern s32 lbl_803CBC98;
extern SpaniObj* lbl_803CBC9C;

extern void* ARAMTransfer(void* instr, void* dest, u8 mode, u32 aramAddr);
extern void convertTextureHeader(void* textures);
extern void fn_800B24D4(u32);
extern void fn_800ACFB0(void* object);
extern void fn_800B0D38(s32 index, s32 value);
extern s32 fn_800B216C(u8 flag, u32 mode, u8 index);
extern void fn_800B21A8(s32 mode);
struct QuadState;
extern s32 fn_80034BCC(struct QuadState* q, Mtx unused); // main/file_800263FC.h
extern s32 (*fn_8000A094(s32 (*callback)(struct QuadState*, Mtx)))(struct QuadState*, Mtx); // TODO: main/file_80008E00.h (Anim/Spani types clash)
extern void fn_8000B9C8(SpaniAnim* anim);
extern void fn_8000CC4C(SpaniAnim* anim, SpaniTrack* track, void* src, u32 offset, u32 size);
extern u32 fn_8000CEF0(SpaniAnim* anim, u16 animId, u32 track, u32 frame, SpaniKey* out);
extern u8 fn_8000D838(u32* frame, SpaniAnim* anim, u16 animId, Mtx mtx, s32 arg4, s32 arg5, void* arg6, void* tex);
extern void fn_8000F534(SpaniObj* obj, s32 arg1);
extern void fn_80011140(void);
extern void DrawTextOnCondition(u8 layer);
extern void fn_800B27A4(s32 arg0);
extern void fn_800B27DC(Mtx44 mtx, s32 arg1);
extern void fn_800B2854(u8* buf, s32 bufSize, Mtx44 proj, s32 projType, s32 numLayers, s32* layerIds, s32* layerSizes);

static inline s32 spaniFindSlot(s32 id) {
    s32 i;
    for (i = 0; i < SPANI_OBJ_COUNT; i++) {
        if (id == lbl_8023D6C0[i]) {
            return i;
        }
    }
    return -1;
}

static inline s8 spaniFindFreeSlot(void) {
    u8 i = 0;
    do {
        if (lbl_803C4BE0[i].data == NULL) {
            return i;
        }
        i++;
    } while (i < SPANI_TEX_SLOT_COUNT);
    return -1;
}

static inline void spaniClearSlot(s32 id) {
    s32 slot = spaniFindSlot(id);
    if (slot != -1) {
        lbl_8023D6C0[slot] = -1;
        lbl_803C4BE0[slot].data = NULL;
        lbl_803C4BE0[slot].tex = NULL;
        lbl_803C4BE0[slot].anim = NULL;
        PSMTXIdentity(lbl_803C4BE0[slot].mtx);
    }
}

#ifdef TARGET_PC
static void* s_slotEntry[SPANI_TEX_SLOT_COUNT];
extern int port_spani_trace_on(void);
extern int port_spani_trace_budget(void);
#endif

// .text:0x80034F50 size:0x218
SpaniObj* fn_80034F50(SpaniDesc* desc) {
    s32 i;
    SpaniObj* obj;

    for (i = 0; i < SPANI_OBJ_COUNT; i++) {
        if (lbl_8039C3E0[i].flags == 0) {
            s32 slot;
            for (slot = 0; slot < SPANI_OBJ_COUNT; slot++) {
                if (desc->texId == lbl_8023D6C0[slot]) {
                    break;
                }
            }
            obj = &lbl_8039C3E0[i];
            obj->flags = 1;
            if (desc->type == 1) {
                obj->flags |= 4;
            }
            obj->unk58 = desc->unkC;
            obj->unk74 = desc->unkC;
            obj->animId = desc->animId;
            obj->layer = desc->layer;
            obj->texSlot = slot;
            obj->baseX = desc->x;
            obj->baseY = desc->y;
            obj->baseZ = 0.0f;
            obj->scale = desc->scale;
            obj->is3D = desc->is3D;
            obj->unk4 = 0;
            obj->unk8 = 0;
            obj->unk72 = desc->unk1E;
            obj->unk71 = desc->unk1D;
            if (desc->playMode == 2) {
                obj->playMode = 0;
            } else if (desc->playMode == 3) {
                obj->playMode = 1;
            } else {
                obj->playMode = desc->playMode;
                obj->flags |= 2;
            }
            obj->frame = 0;
            obj->frameStep = 0x10000;
            obj->unkA8 = 0;
            PSMTXIdentity(obj->mtx);
#ifdef TARGET_PC
            if (port_spani_trace_on() && port_spani_trace_budget()) {
                OSReport("[spobj] create obj %d anim %u layer %u texId %u -> slot %d (entry %p) parent %d\n", (int)i,
                         desc->animId, desc->layer, desc->texId, (int)slot,
                         slot < SPANI_TEX_SLOT_COUNT ? s_slotEntry[slot] : NULL, (int)desc->parent);
            }
#endif
            return obj;
        }
    }
    return NULL;
}

#ifdef TARGET_PC
extern int port_spani_trace_on(void);
extern int port_spani_trace_budget(void);
extern u32 port_sprite_total_bytes(void);
extern u32 port_spani_trace_frame;
// state: 0 inactive, 1 hidden (flag 2 clear), 2 parent not ready, 3 drew nothing, 4 drew
static u8 s_spaniTraceState[SPANI_OBJ_COUNT];
static void spaniTrace(s32 i, SpaniObj* obj, u8 st, u32 bytes) {
    static const char* names[] = {"inactive", "hidden", "parent-wait", "EMPTY", "drawn"};
    u8 prev = s_spaniTraceState[i];
    s_spaniTraceState[i] = st;
    if (prev == st || prev == 0 || st == 0) {
        return; // only log changes on live objects (creation/destruction is noise)
    }
    if (!port_spani_trace_budget()) {
        return;
    }
    OSReport("[spani] f=%u obj %d anim %u layer %u slot %u frame %u.%04x res %u flags %x 3d %u scale %.3f pos %.1f,%.1f: %s -> %s (%u bytes)\n",
             port_spani_trace_frame, (int)i, obj->animId, obj->layer, obj->texSlot, obj->frame >> 16,
             obj->frame & 0xFFFF, obj->animResult, (unsigned)obj->flags, obj->is3D, obj->scale, obj->posX,
             obj->posY, names[prev], names[st], bytes);
}
#define SPANI_TRACE(st, bytes) do { if (traceOn) spaniTrace(i, obj, (st), (bytes)); } while (0)
#else
#define SPANI_TRACE(st, bytes) do { } while (0)
#endif

#ifdef TARGET_PC
// MSSB_SPANI_TRACE: name the scene task that toggles a sprite's visible bit (flags & 2).
extern const char* port_sym_name(void* p);
static u32 s_flagSnap[SPANI_OBJ_COUNT];
void port_spani_flag_snapshot(void) {
    s32 i;
    for (i = 0; i < SPANI_OBJ_COUNT; i++) {
        s_flagSnap[i] = lbl_8039C3E0[i].flags;
    }
}
void port_spani_flag_check(void* func) {
    s32 i;
    for (i = 0; i < SPANI_OBJ_COUNT; i++) {
        u32 f = lbl_8039C3E0[i].flags;
        u32 o = s_flagSnap[i];
        if (((f ^ o) & 2) && o != 0 && f != 0 && port_spani_trace_budget()) {
            OSReport("[flagw] f=%u task %s obj %d anim %u layer %u flags %x -> %x\n", port_spani_trace_frame,
                     port_sym_name(func), (int)i, lbl_8039C3E0[i].animId, lbl_8039C3E0[i].layer, (unsigned)o,
                     (unsigned)f);
        }
        s_flagSnap[i] = f;
    }
}
#endif

// .text:0x80035168 size:0x550
// NONMATCHING 97.5%: original keeps separate k*4 and texOverride walkers (r29/r30); regalloc
#if NONMATCHING
void fn_80035168(void) {
#ifdef TARGET_PC
    u16* sp8[1]; // loop marker out-parameter of fn_8000D838 (a u16*)
#else
    u8 sp8[4];
#endif
    Mtx inv;
    Mtx mtx;
    Mtx* views = lbl_800F78E0;
    MtxPtr view;
    SpaniObj* obj;
    s32 i;
    s32 unk74;
    s32 k;
    s32 layer;
#ifdef TARGET_PC
    int traceOn = port_spani_trace_on();
    u32 traceBytes = 0;
#endif

    if (lbl_803C77B8[0].held & 0x1000) {
        if (lbl_803C77B8[3].trig & 1) {
            if (lbl_803CB814 > lbl_803CBC98) {
                lbl_803CB814--;
            }
        } else if ((lbl_803C77B8[3].trig & 2) && lbl_803CB814 < SPANI_OBJ_COUNT) {
            lbl_803CB814++;
        }
        if (lbl_803C77B8[3].trig & 4) {
            if (lbl_803CBC98 > 0) {
                lbl_803CBC98--;
            }
        } else if ((lbl_803C77B8[3].trig & 8) && lbl_803CBC98 < lbl_803CB814) {
            lbl_803CBC98++;
        }
    }
    fn_8000A094(fn_80034BCC);
    for (i = lbl_803CBC98, obj = &lbl_8039C3E0[i]; i < lbl_803CB814; i++, obj++) {
        u32 flags = obj->flags;
        if (flags == 0) {
            SPANI_TRACE(0, 0);
            continue;
        }
        if (!(flags & 2)) {
            if (flags & 4) {
                fn_8000F534(obj, 0);
            }
            SPANI_TRACE(1, 0);
            continue;
        }
        if (obj->parent != NULL && obj->unkA8 == 0) {
            if (flags & 4) {
                fn_8000F534(obj, 0);
            }
            SPANI_TRACE(2, 0);
            continue;
        }
#ifdef TARGET_PC
        if (traceOn) {
            traceBytes = port_sprite_total_bytes();
        }
#endif
        fn_800B24D4(obj->layer);
        if (obj->is3D) {
            fn_800B27DC(lbl_801F8640, 0);
            view = views[0];
            fn_800B21A8(obj->unk71);
        } else {
            fn_800B27DC(lbl_801F8680, 0);
            if (obj->layer == 0x15) {
                view = views[3];
                lbl_803CBBE0 = 256.5f;
                fn_800B216C(1, 3, 0);
            } else {
                if (obj->layer >= 0xF && obj->layer <= 0x16) {
                    view = views[1];
                    lbl_803CBBE0 = 511.0f;
                } else {
                    view = views[2];
                    lbl_803CBBE0 = 2.0f;
                }
                fn_800B21A8(obj->unk71);
            }
        }
        obj->posX = obj->baseX;
        obj->posY = obj->baseY;
        obj->posZ = obj->baseZ;
        if (obj->is3D) {
            PSMTXScale(obj->mtx, -obj->scale, obj->scale, 1.0f);
            PSMTXInverse(fn_80052734(0)->view, inv);
            inv[0][3] = inv[1][3] = inv[2][3] = 0.0f;
            PSMTXConcat(inv, obj->mtx, obj->mtx);
            PSMTXTrans(inv, obj->posX, obj->posY, obj->posZ);
            PSMTXConcat(inv, obj->mtx, obj->mtx);
            PSMTXConcat(fn_80052734(0)->view, obj->mtx, obj->mtx);
            obj->unk74 = obj->unk58;
        } else {
            if (obj->parent == NULL) {
                obj->posX -= (s32)((u32)lbl_803C4BE0[obj->texSlot].anim->width >> 1);
                obj->posY -= (s32)((u32)lbl_803C4BE0[obj->texSlot].anim->height >> 1);
                obj->unk74 = obj->unk58;
                PSMTXIdentity(obj->mtx2);
            }
            obj->posZ = 0.0f;
            PSMTXTrans(obj->mtx, obj->posX, obj->posY, 0.0f);
            PSMTXConcat(obj->mtx2, obj->mtx, obj->mtx);
        }
        unk74 = obj->unk74;
        k = 0;
        lbl_803CBBE4 = obj->is3D;
        do {
            if (obj->texOverride[k] != 0xFFFF) {
                SpaniAnim* anim = lbl_803C4BE0[obj->texSlot].anim;
                SpaniTrack* track = PTR32_GET(SpaniTrack, PTR32_GET(SpaniSeq, PTR32_GET(SpaniSeqList, anim->seqList)->seqs[obj->animId])->tracks[k]);
                SpaniKey* keys = track->keys;
                fn_8000CC4C(anim, track, &obj->texOverride[k], (u32)((u8*)&keys->texIdx - (u8*)keys), sizeof(u16));
            }
            k++;
        } while (k < SPANI_TEX_OVERRIDE_COUNT);
        if (obj->parent == NULL) {
            PSMTXConcat(view, obj->mtx, mtx);
        } else {
            PSMTXCopy(obj->mtx, mtx);
        }
        lbl_803CBC9C = obj;
        if (!(obj->flags & 4)) {
            SpaniTexSlot* s = &lbl_803C4BE0[obj->texSlot];
            obj->animResult = fn_8000D838(&obj->frame, s->anim, obj->animId, mtx, 0, unk74, sp8, s->tex);
        }
        obj->unkA8 = 0;
        if (obj->playMode == 1) {
            switch (obj->animResult) {
            case 0:
                obj->frame += obj->frameStep;
                break;
            case 1:
                obj->frame = 0;
                break;
            case 2:
            case 3:
                break;
            default:
                obj->frame += obj->frameStep;
                break;
            }
        } else if (obj->playMode == 4) {
            if (obj->frame > obj->frameStep) {
                obj->frame -= obj->frameStep;
            } else {
                obj->frame = 0;
            }
        }
        if (obj->flags & 4) {
            fn_8000F534(obj, 1);
        }
#ifdef TARGET_PC
        if (traceOn) {
            u32 b = port_sprite_total_bytes() - traceBytes;
            SPANI_TRACE(b != 0 ? 4 : 3, b);
        }
#endif
    }
    for (layer = 1; layer < 9; layer++) {
        fn_800B24D4(layer);
        fn_800B21A8(0);
        DrawTextOnCondition(layer);
    }
    fn_800B24D4(2);
}
#endif


// .text:0x800356B8 size:0x98
void fn_800356B8(void) {
    s32 i;

    for (i = 0; i < SPANI_OBJ_COUNT; i++) {
        lbl_8039C3E0[i].parent = NULL;
        lbl_8039C3E0[i].unk4 = 0;
        lbl_8039C3E0[i].unk8 = 0;
        lbl_8039C3E0[i].flags = 0;
        PSMTXIdentity(lbl_8039C3E0[i].mtx);
        lbl_80371C30[i].obj = NULL;
        lbl_80371C30[i].unk4 = 0;
    }
    fn_80011140();
    lbl_803C5F74.active = 0;
}

// .text:0x80035750 size:0xE8
// NONMATCHING 92%: original keeps only &slot->anim (r28) across the call
#if NONMATCHING
void fn_80035750(void* data, void* tex, s16 id) {
    s32 slot;
    SpaniTexSlot* s;
    SpaniAnim** pa;

    slot = spaniFindFreeSlot();
    if (slot == -1) {
        OSReport(" SabNo = %d not to add  \n", slot);
        OSPanic("spani_default.c", 0x49C, "gasSpani No Empty \n");
    }
    s = &lbl_803C4BE0[slot];
    pa = &s->anim;
    s->data = data;
#ifdef TARGET_PC
    s_slotEntry[slot] = data; // a stadium/file bank, not a table entry
    if (port_spani_trace_on()) {
        OSReport("[bank] file bank id %d -> slot %d (data %p)\n", (int)id, (int)slot, data);
    }
#endif
    s->tex = tex;
    *pa = data;
    lbl_8023D6C0[slot] = id;
    convertTextureHeader(s->tex);
    fn_8000B9C8(*pa);
}
#endif


// .text:0x80035838 size:0x1C8
s32 fn_80035838(void* aramAddr, u8 id) {
    u8 done = 0;

    if (lbl_803CBC90 == 2) {
        lbl_803CBC90 = 0;
        lbl_803CBC94 = NULL;
        lbl_803CB810 = -1;
    }
    switch (lbl_803CBC90) {
    case 0:
        lbl_803CBC91 = spaniFindFreeSlot();
        if (lbl_803CBC91 == -1) {
            OSReport(" SabNo = %d not to add  \n", lbl_803CBC91);
            OSPanic("spani_default.c", 0x45A, "gasSpani No Empty \n");
        }
        lbl_8023D6C0[lbl_803CBC91] = id;
#ifdef TARGET_PC
        if (port_spani_trace_on()) {
            s32 k, dup = -1;
            for (k = 0; k < SPANI_TEX_SLOT_COUNT; k++) {
                if (k != lbl_803CBC91 && lbl_8023D6C0[k] == id) {
                    dup = k;
                }
            }
            OSReport("[bank] load id %u -> slot %d (entry %p, existing slot with same id: %d)\n", id,
                     (int)lbl_803CBC91, aramAddr, (int)dup);
        }
#endif
        lbl_803C4BE0[lbl_803CBC91].data = ARAMTransfer(aramAddr, 0, 0, 0);
#ifdef TARGET_PC
        s_slotEntry[lbl_803CBC91] = aramAddr;
#endif
        lbl_803CBC94 = aramAddr;
        lbl_803CB810 = id;
        lbl_803CBC90++;
        break;
    case 1:
        if ((s8)lbl_803C6CF8.idle == 1) {
            SpaniTexSlot* s = lbl_803C4BE0;
            SpaniAnim** pa;
            s32* hdr;
            s += lbl_803CBC91;
            pa = &s->anim;
            hdr = s->data;
#ifdef TARGET_PC
            {
                extern void port_bank_dump(s32 id, const void* data, u32 size);
                port_bank_dump(lbl_803CB810, hdr, lbl_803C6CF8.sizeInfo & 0x0FFFFFFF);
            }
            port_swap_offset_table(hdr, 2); // texture archive, animation
#endif
            s->tex = (u8*)hdr + hdr[0];
            *pa = (SpaniAnim*)((u8*)hdr + hdr[1]);
            convertTextureHeader(s->tex);
            fn_8000B9C8(*pa);
            done = 1;
            lbl_803CBC90++;
        }
        break;
    }
    return done;
}


// .text:0x80035A00 size:0x150
void fn_80035A00(void) {
    s32 id;

    for (id = 0; id < 25; id++) {
        if ((u32)id > 1) {
            spaniClearSlot(id);
        }
    }
}

// .text:0x80035B50 size:0x154
void fn_80035B50(int id) {
    s32 slot = spaniFindSlot(id);
#ifdef TARGET_PC
    if (port_spani_trace_on()) {
        OSReport("[bank] free id %d (slot %d)\n", id, (int)slot);
    }
#endif

    if (slot != -1) {
        lbl_8023D6C0[slot] = -1;
        fn_800ACFB0(lbl_803C4BE0[slot].data);
        lbl_803C4BE0[slot].data = NULL;
        lbl_803C4BE0[slot].tex = NULL;
        lbl_803C4BE0[slot].anim = NULL;
        PSMTXIdentity(lbl_803C4BE0[slot].mtx);
    }
}

// .text:0x80035CA4 size:0x130
void fn_80035CA4(s32 id) {
#ifdef TARGET_PC
    if (port_spani_trace_on()) {
        OSReport("[bank] clear id %d (slot %d)\n", (int)id, (int)spaniFindSlot(id));
    }
#endif
    spaniClearSlot(id);
}

// .text:0x80035DD4 size:0xFC
s32 fn_80035DD4(s32 id) {
    s32 i;
    for (i = 0; i < SPANI_OBJ_COUNT; i++) {
        if (id == lbl_8023D6C0[i]) {
            return i;
        }
    }
    return -1;
}

// .text:0x80035ED0 size:0x1C
void fn_80035ED0(s32 idx) {
    lbl_8039C3E0[idx].flags = 0;
}

// .text:0x80035EEC size:0x34
void fn_80035EEC(u16 frame, s32 idx) {
    if (lbl_8039C3E0[idx].frame > (u32)(frame << 16)) {
        lbl_8039C3E0[idx].frame = frame << 16;
        lbl_8039C3E0[idx].playMode = 0;
    }
}

// .text:0x80035F20 size:0x214
// NONMATCHING 76%: track search loop shape (original keeps n live across tracks, lwzx indexing)
#if NONMATCHING
SpaniKey* fn_80035F20(s32 texId, s32 objIdx, u16 keyIdx, s16 track) {
    s32 slot;
    SpaniSeq* seq;
    u32 t;
    PTR32(SpaniTrack)* pp;
    SpaniTrack* tr;
    SpaniKey* key;
    s32 n;

    slot = spaniFindSlot(texId);
    if (slot == -1) {
        OSPanic(lbl_800E68C4, 0x31C, lbl_800E68E8);
    }
    seq = PTR32_GET(SpaniSeq, PTR32_GET(SpaniSeqList, lbl_803C4BE0[slot].anim->seqList)->seqs[lbl_8039C3E0[objIdx].animId]);
    t = seq->trackCount - 1;
    pp = &seq->tracks[t];
    if (track == -1) {
        tr = PTR32_GET(SpaniTrack, *pp);
        n = tr->keyCount;
        key = &tr->keys[n];
        do {
            n--;
            key--;
        } while (n != 0);
        return &key[keyIdx];
    }
    do {
        tr = PTR32_GET(SpaniTrack, *pp--);
        n = tr->keyCount;
        key = &tr->keys[n];
        if (t == track) {
            break;
        }
        do {
            n--;
            key--;
        } while (n != 0);
        t--;
    } while (t != 0);
    while (n != 0) {
        n--;
        key--;
    }
    return key;
}
#endif


// .text:0x80036134 size:0xE0
void fn_80036134(SpaniOwner* owner, s32 srcIdx, u32 track, s32 dstIdx) {
    SpaniKey key;
    s16 x;
    s16 y;
    SpaniObj* obj = lbl_80371C30[owner->u14.objIdx + srcIdx].obj;

    fn_8000CEF0(lbl_803C4BE0[obj->texSlot].anim, obj->animId, track, obj->frame >> 16, &key);
    x = key.x;
    y = key.y;
    lbl_80371C30[owner->u14.objIdx + dstIdx].obj->baseX = x;
    lbl_80371C30[owner->u14.objIdx + dstIdx].obj->baseY = y;
}

// .text:0x80036214 size:0x5C
s32 fn_80036214(SpaniOwner* owner, s32 idx, u32 track, u32 frame) {
    SpaniKey key;
    SpaniObj* obj = lbl_80371C30[owner->u14.objIdx + idx].obj;

    fn_8000CEF0(lbl_803C4BE0[obj->texSlot].anim, obj->animId, track, frame, &key);
#ifdef TARGET_PC
    // The key's colour word is RGBA bytes, left big-endian by the spani swap.
    return read_be32(&key.unk1C);
#else
    return key.unk1C;
#endif
}

// .text:0x80036270 size:0x80
void fn_80036270(SpaniOwner* owner, s32 idx, u32 track, u32 frame, s16* outX, s16* outY) {
    SpaniKey key;
    SpaniObj* obj = lbl_80371C30[owner->u14.objIdx + idx].obj;

    fn_8000CEF0(lbl_803C4BE0[obj->texSlot].anim, obj->animId, track, frame, &key);
    *outX = key.x;
    *outY = key.y;
}

// .text:0x800362F0 size:0xE8
void fn_800362F0(SpaniOwner* owner, s32 idx) {
    s32 i;

    for (i = 0; i < SPANI_TEX_OVERRIDE_COUNT; i++) {
        lbl_80371C30[owner->u14.objIdx + idx].obj->texOverride[i] = 0xFFFF;
    }
}

// .text:0x800363D8 size:0xC4
void fn_800363D8(SpaniOwner* owner, s32 idx, u32 slot, u16 animId, u32 frame) {
    SpaniKey key;
    u16 texIdx;

    if (slot < SPANI_TEX_OVERRIDE_COUNT) {
        SpaniObj* obj = lbl_80371C30[owner->u14.objIdx + idx].obj;
        if (fn_8000CEF0(lbl_803C4BE0[obj->texSlot].anim, animId, 0, frame, &key)) {
            texIdx = key.texIdx;
        } else {
            texIdx = 0;
        }
        lbl_80371C30[owner->u14.objIdx + idx].obj->texOverride[slot] = texIdx;
    }
}

// .text:0x8003649C size:0xD0
// NONMATCHING 77%: original uses lwzu for &slot->anim and lwzx word-array indexing
#if NONMATCHING
void fn_8003649C(SpaniOwner* owner, s32 idx, s32 track, u16 animId, u32 frame) {
    u16 texIdx;
    SpaniKey key;
    SpaniObj* obj = lbl_80371C30[owner->u14.objIdx + idx].obj;
    u16 curAnim = obj->animId;
    SpaniTexSlot* s = &lbl_803C4BE0[obj->texSlot];
    SpaniTrack* tr;
    SpaniKey* keys;

    if (fn_8000CEF0(s->anim, animId, 0, frame, &key)) {
        texIdx = key.texIdx;
    } else {
        texIdx = 0;
    }
    tr = PTR32_GET(SpaniTrack, PTR32_GET(SpaniSeq, PTR32_GET(SpaniSeqList, s->anim->seqList)->seqs[curAnim])->tracks[track]);
    keys = tr->keys;
    fn_8000CC4C(s->anim, tr, &texIdx, (u32)((u8*)&keys->texIdx - (u8*)keys), sizeof(u16));
}
#endif


// .text:0x8003656C size:0xE0
// NONMATCHING 81%: original uses lwzu for &slot->anim and lwzx word-array indexing
#if NONMATCHING
void fn_8003656C(SpaniOwner* owner, s32 idx, s32 track, u16 animId, u32 frame) {
    s32 val;
    SpaniKey key;
    SpaniObj* obj = lbl_80371C30[owner->u14.objIdx + idx].obj;
    u16 curAnim = obj->animId;
    SpaniTexSlot* s = &lbl_803C4BE0[obj->texSlot];
    SpaniAnim* anim = s->anim;
    SpaniTrack* tr;

    if (fn_8000CEF0(anim, animId, 0, frame, &key)) {
        val = key.unk1C;
    } else {
        val = 0;
    }
    tr = PTR32_GET(SpaniTrack, PTR32_GET(SpaniSeq, PTR32_GET(SpaniSeqList, s->anim->seqList)->seqs[curAnim])->tracks[track]);
    fn_8000CC4C(anim, tr, &val, (u32)((u8*)&tr->keys[0].unk1C - (u8*)&tr->keys[0]), sizeof(s32));
}
#endif


// .text:0x8003664C size:0x1D8
// NONMATCHING 88%: lwzx word-array indexing; loop register allocation
#if NONMATCHING
void fn_8003664C(s32 texId, s32 objIdx, s16 texIdx, u32 track) {
    s32 slot;
    SpaniSeq* seq;
    u32 t;
    PTR32(SpaniTrack)* pp;
    SpaniTrack* tr;
    SpaniKey* key;
    s32 n;

    slot = spaniFindSlot(texId);
    if (slot == -1) {
        OSPanic(lbl_800E68C4, 0x15E, lbl_800E68E8);
    }
    seq = PTR32_GET(SpaniSeq, PTR32_GET(SpaniSeqList, lbl_803C4BE0[slot].anim->seqList)->seqs[lbl_8039C3E0[objIdx].animId]);
    t = seq->trackCount - 1;
    pp = &seq->tracks[t];
    do {
        tr = PTR32_GET(SpaniTrack, *pp--);
        n = tr->keyCount;
        key = &tr->keys[n];
        do {
            n--;
            key--;
            if (key->enabled != 0 && t == track) {
                key->texIdx = texIdx;
            }
        } while (n != 0);
        t--;
    } while (t != 0);
}
#endif


// .text:0x80036824 size:0x1B8
// NONMATCHING 94%: original indexes seqs/tracks as word arrays ([i + 2], lwzx) and computes the track pointer from t
#if NONMATCHING
u16 fn_80036824(s32 texId, s32 animId, u16 keyIdx) {
    s32 slot;
    SpaniSeq* seq;
    u32 t;
    PTR32(SpaniTrack)* pp;
    SpaniTrack* tr;
    SpaniKey* key;
    s32 n;

    slot = spaniFindSlot(texId);
    if (slot == -1) {
        OSPanic(lbl_800E68C4, 0x12A, lbl_800E68E8);
    }
    seq = PTR32_GET(SpaniSeq, PTR32_GET(SpaniSeqList, lbl_803C4BE0[slot].anim->seqList)->seqs[animId]);
    t = seq->trackCount - 1;
    pp = &((PTR32(SpaniTrack)*)seq)[t + 2];
    do {
        tr = PTR32_GET(SpaniTrack, *pp--);
        n = tr->keyCount;
        key = &tr->keys[n];
        do {
            n--;
            key--;
            if (n == keyIdx) {
                return key->texIdx;
            }
        } while (n != 0);
        t--;
    } while (t != 0);
    return 0;
}
#endif


// .text:0x800369DC size:0x60
void fn_800369DC(f32 zoom) {
    if (0.0f != zoom) {
        f32 s = 1.0f / zoom;
        C_MTXFrustum(lbl_801F8640, -0.175f * s, 0.175f * s, 0.25f * s, -0.25f * s, 1.0f, 512.0f);
    }
}

// .text:0x80036A3C size:0x24C
void fn_80036A3C(void) {
    s32 modes[23];
    s32 i;

    C_MTXFrustum(lbl_801F8680, -0.175f, 0.175f, -0.25f, 0.25f, 1.0f, 512.0f);
    for (i = 0; i < 23; i++) {
        switch (i) {
        case 12:
            modes[i] = 9;
            break;
        case 11:
            modes[i] = 0xA;
            break;
        case 10:
        case 13:
        case 14:
            modes[i] = 0xB;
            break;
        case 0:
            modes[i] = 0xD;
            break;
        default:
            modes[i] = 0xC;
            break;
        }
    }
    fn_800B2854(lbl_801F86C0, 2 * SPRITE_DL_POOL, lbl_801F8680, 0, 23, modes, NULL);
    fn_800B27A4(10);
    for (i = 0xD; i < 23; i++) {
        fn_800B0D38(i, 2);
    }
    for (i = 0; i < SPANI_OBJ_COUNT; i++) {
        lbl_8023D6C0[i] = -1;
    }
    lbl_803CBBE4 = 0;
    lbl_803CBBE0 = 2.0f;
    lbl_803CBBDC = 1280.0f;
    memset(lbl_8039C3E0, 0, sizeof(lbl_8039C3E0));
    lbl_80366188.unk84 = 0;
    lbl_80366188.drawCallback = NULL;
}

// .text:0x80036C88 size:0x3CC
s32 fn_80036C88(s32* src, s32* dst) {
    s32 i;
    s32 sum;
    s32 diff;
    s32 idx;

    memcpy(dst, src, 23 * sizeof(s32));
    sum = 0;
    for (i = 0; i < 23; i++) {
        sum += src[i];
    }
    diff = SPRITE_DL_POOL - sum;
    if (diff < 0) {
        s32 excess = -diff;
        s32 take;
        do {
            s32 min = 0x7FFFFFFF;
            for (i = 0; i < 23; i++) {
                if (dst[i] != 0 && min >= dst[i]) {
                    idx = i;
                    min = dst[i];
                }
            }
            take = dst[idx];
            if (excess <= take) {
                take = excess;
            }
            excess -= take;
            dst[idx] -= take;
        } while (excess > 0 && take != 0);
        if (excess != 0) {
            for (i = 0; i < 23; i++) {
                dst[i] = 0x1800;
            }
        }
        return 1;
    }
    if (diff != 0) {
        s32 add = (diff / 23 / 32) * 32;
        s32 j;
        for (j = 0; j < 23; j++) {
            dst[j] += add;
        }
        diff -= add * 23; dst[0] += diff;
    }
    return 0;
}

// ---- Data (initialisers generated from the original DOL) ----

// .data 0x800F78E0..0x800F79A0
Mtx lbl_800F78E0[4] = {
    {{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
    {
        {0.39921874f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.39921874f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.39921874f, -511.0f},
    },
    {{0.0015625f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0015625f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0015625f, -2.0f}},
    {
        {0.20039062f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.20039062f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.20039062f, -256.5f},
    },
};

// .bss 0x801F8640..0x8023DD80 (MWCC lays these out in reverse definition order)
s16 lbl_8023D6C0[0x360];
u8 lbl_801F86C0[2 * SPRITE_DL_POOL];
Mtx44 lbl_801F8680;
Mtx44 lbl_801F8640;

// .sdata 0x803CB810..0x803CB818
s32 lbl_803CB810 = -1;
s32 lbl_803CB814 = 864;

// .sbss 0x803CBC90..0x803CBCA0 (MWCC lays these out in reverse definition order)
SpaniObj* lbl_803CBC9C;
s32 lbl_803CBC98;
void* lbl_803CBC94;
u8 lbl_803CBC91;
u8 lbl_803CBC90;

