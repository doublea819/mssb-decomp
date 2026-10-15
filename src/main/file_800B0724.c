#include "main/file_800B0724.h"
#include "main/file_80069BDC.h"
#include "Dolphin/os.h"
#include "Dolphin/ai.h"
#include "Dolphin/ar.h"
#include "musyx/musyx.h"
#include "main/file_8000BA3C.h"
#include "stl/mem.h"
#include "main/file_800B9974.h"
#include "main/file_800BDEA0.h"

extern const f32 lbl_803CCF08; // -1.0f
extern const f32 lbl_803CCF0C; // 0.0f
extern const f32 lbl_803CCF10; // 1.0f
extern SoundConfig lbl_801112F0;
extern SndHeap* lbl_803CBB10;

// .text:0x800B0724 size:0xD8
// Like C_MTXLookAt, but handles a camera looking straight up or down.
void makeLookAtMatrix(Mtx m, Vec* camPos, Vec* camUp, Vec* target) {
    if (camPos->x == target->x && camPos->z == target->z) {
        m[0][0] = lbl_803CCF08;
        m[0][1] = lbl_803CCF0C;
        m[0][2] = lbl_803CCF0C;
        m[0][3] = camPos->x;
        if (camPos->y - target->y <= lbl_803CCF0C) {
            m[1][0] = lbl_803CCF0C;
            m[1][1] = lbl_803CCF0C;
            m[1][2] = lbl_803CCF08;
            m[1][3] = camPos->z;
            m[2][0] = lbl_803CCF0C;
            m[2][1] = lbl_803CCF08;
            m[2][2] = lbl_803CCF0C;
            m[2][3] = camPos->y;
        } else {
            m[1][0] = lbl_803CCF0C;
            m[1][1] = lbl_803CCF0C;
            m[1][2] = lbl_803CCF10;
            m[1][3] = -camPos->z;
            m[2][0] = lbl_803CCF0C;
            m[2][1] = lbl_803CCF10;
            m[2][2] = lbl_803CCF0C;
            m[2][3] = -camPos->y;
        }
    } else {
        C_MTXLookAt(m, camPos, camUp, target);
    }
}

// .text:0x800B07FC size:0x38
void soundQuit(void) {
    SND_HOOKS hooks = {SndAlloc, SndFree};
    sndSetHooks(&hooks);
    sndQuit();
}

// .text:0x800B0834 size:0x100
void initSound(SoundConfig* config, u8* aiStack, u8* heapStart, u32 heapSize) {
    SND_HOOKS hooks = {SndAlloc, SndFree};
    u8* heapEnd;
    AIInit(aiStack);
    ARInit(NULL, 0);
    ARQInit();
    if (config == NULL) {
        config = &lbl_801112F0;
    }
#ifdef TARGET_PC
    // MusyX's structures are bigger on PC (pointers), and the DSP emulation
    // needs heap memory (32-bit physical addresses): use a larger pool in the
    // game heap instead of the static buffer.
    heapSize *= 4;
    heapStart = (u8*)port_heap_alloc(heapSize, 32);
#endif
    heapEnd = heapStart + heapSize;
    lbl_803CBB10->cur = heapStart;
    lbl_803CBB10->end = heapEnd;
    lbl_803CBB10->free = (u32)(heapEnd - heapStart);
    sndSetHooks(&hooks);
    if (sndInit(config->voices, config->music, config->sfx, config->studios, config->flags, config->aramSize) != 0) {
        OSPanic("sound.c", 0x116, "gYd_MusyXInit()::Failed to sndInit().");
    }
    if (OSGetSoundMode() == 0) {
        sndOutputMode(SND_OUTPUTMODE_MONO);
    } else {
        sndOutputMode(SND_OUTPUTMODE_STEREO);
    }
}


// The sprite display lists are GX command streams: big-endian on PC too.
#ifdef TARGET_PC
#define DL_BE16(p) swap16_inplace(p)
#define DL_BE32(p) swap32_inplace(p)
#define DL_BE32_ARRAY(p, n) swap32_array((p), (n))
static inline void DL_BE_QUADVTX(u8* p, s32 count) {
    s32 i;
    for (i = 0; i < count; i++, p += 0x14) {
        swap32_array(p, 4); // pos, color
        swap16_array(p + 0x10, 2); // s, t
    }
}
#else
#define DL_BE16(p)
#define DL_BE32(p)
#define DL_BE32_ARRAY(p, n)
#define DL_BE_QUADVTX(p, count)
#endif
// GD also writes aurora's texture/TLUT bind commands on PC (file_800A1A70.c).
#ifdef TARGET_PC
#define DL_AURORA_TEX_BYTES 64
#else
#define DL_AURORA_TEX_BYTES 0
#endif

// fn_800B0934, size:0x4
void fn_800B0934(void) {
}

// .text:0x800B0938 size:0x64
void SndFree(void* ptr) {
    SndBlockHdr* hdr = (SndBlockHdr*)ptr - 1;
    u8* prevCur = hdr->prevCur;
    if (prevCur + hdr->size != lbl_803CBB10->cur) {
        OSReport("sNp_SndFree err\n");
        while (TRUE) {
        }
    }
    lbl_803CBB10->cur = prevCur;
    lbl_803CBB10->free = (s32)(lbl_803CBB10->end - lbl_803CBB10->cur);
}

// .text:0x800B099C size:0x78
// NONMATCHING 84.6%: block-cur temp lands in r4 instead of r6 (matches only if `size` is reused to hold newCur as an integer)
#if NONMATCHING
void* SndAlloc(u32 size) {
    u8* cur;
    u8* hdrEnd;
    u8* block;
    u8* newCur;
    u32 taken;
    s32 remaining;
    size = (size + 3) & ~3;
    cur = lbl_803CBB10->cur;
    // Round cur + header up to 32 bytes (only the low address bits matter).
    hdrEnd = cur + sizeof(SndBlockHdr);
    block = hdrEnd + (-(u32)(size_t)hdrEnd & 0x1F);
    taken = (u32)(block - cur);
    taken += size;
    newCur = block + size;
    remaining = (s32)(lbl_803CBB10->end - newCur);
    if (remaining < 0) {
        OSReport("sNp_SndAlloc:: no enough space:%d\n", remaining);
        while (TRUE) {
        }
    }
    ((SndBlockHdr*)block)[-1].prevCur = cur;
    ((SndBlockHdr*)block)[-1].size = taken;
    lbl_803CBB10->free = remaining;
    lbl_803CBB10->cur = newCur;
    return block;
}
#endif

// Draw queue: lbl_803C7A24 holds 64 task slots. Slots 0-5 are the sentinels of three
// priority-sorted lists (head = slot 2n, tail = slot 2n+1); lbl_803CC1B0 picks the list.
extern u16 lbl_803CC1B0; // active list
extern u16 lbl_803CC1B2; // queued task count
extern u16 lbl_803CC1B4; // last slot handed out
extern SceneTask lbl_80111300; // root task (parent of the sentinels)
extern SceneTask lbl_803C7A24[64];

// fn_800B0A14_removeQueue, size:0x48
// Unlinks the running task (lbl_803CC1B8) and frees its slot.
void fn_800B0A14_removeQueue(void* unused) {
    if (lbl_803CC1B2 != 0) {
        SceneTask* neighbor = lbl_803CC1B8->prev;
        neighbor->next = lbl_803CC1B8->next;
        neighbor = lbl_803CC1B8->next;
        neighbor->prev = lbl_803CC1B8->prev;
        lbl_803CC1B8->func = NULL;
        lbl_803CC1B2--;
    }
}

// nop_function, size:0x4
void nop_function(void) {
}

// fn_800B0C80, size:0x34
// Sets the function run by each list's head sentinel.
void fn_800B0C80(void (*draw)(void)) {
    SceneTask* head;
    s32 remaining;
    if (draw == NULL) {
        draw = nop_function;
    }
    remaining = 3;
    head = lbl_803C7A24;
    do {
        remaining--;
        head->func = draw;
        head += 2;
    } while (remaining != 0);
}

// resetAllDrawingStructs, size:0x98
void resetAllDrawingStructs(void) {
    s32 remaining;
    SceneTask* head;
    SceneTask* slot;
    s32 count;
    head = lbl_803C7A24;
    remaining = 3;
    do {
        head[0].prev = NULL;
        head[0].next = &head[1];
        head[0].parent = &lbl_80111300;
        head[0]._10 = 0;
        head[0].priority = 0;
        head[1].prev = &head[0];
        head[1].next = NULL;
        head[1].parent = &lbl_80111300;
        head[1]._10 = 0;
        head[1].priority = 0xFFFF;
        head += 2;
    } while (--remaining != 0);
    slot = &lbl_803C7A24[6];
    count = 64 - 6;
    do {
        slot->func = NULL;
        slot++;
    } while (--count != 0);
    lbl_803CC1B2 = 0;
    lbl_803CC1B0 = 0;
    lbl_803CC1B4 = 5;
}

// fn_800B0A5C_insertQueue, size:0xD0
// Queues draw in the first free slot, before the first task with a higher priority.
void* fn_800B0A5C_insertQueue(void* draw, u16 priority) {
    SceneTask* node;
    SceneTask* prev;
    SceneTask* entry;
    s32* args;
    u16 idx;
    s32 i;
    do {
        lbl_803CC1B4++;
        idx = lbl_803CC1B4 & 0x3F;
        lbl_803CC1B4 = idx;
    } while (*(void**)&lbl_803C7A24[idx] != NULL); // read as a plain word: lbl_803CC1B4 is reloaded each pass
    node = &lbl_803C7A24[lbl_803CC1B0 * 2];
    do {
        node = node->next;
    } while (node->priority < priority);
    prev = node->prev;
    entry = &lbl_803C7A24[idx];
    node->prev = entry;
    prev->next = entry;
    entry->func = (void (*)(void))draw;
    entry->prev = prev;
    entry->next = node;
    entry->parent = lbl_803CC1B8;
    entry->_10 = 0;
    entry->priority = priority;
    entry->u14.res = NULL;
    lbl_803CC1B2++;
    args = (s32*)&entry->nodes; // TODO type: clears the task's 0x18-0x3F user words
    for (i = 0; i < 5; i++) {
        args[i * 2 + 1] = 0;
        args[i * 2] = 0;
    }
    return entry;
}

// .text:0x800B0B2C size:0xBC
// NONMATCHING 90%: register allocation only (inlined resetAllDrawingStructs uses r6/r7/r5 instead of r5/r6/r3)
#if NONMATCHING
// resetAllDrawingStructs, then points every list's sentinels at nop_function.
void resetAllDrawingStructs_tonop(void) {
    SceneTask* slot;
    s32 count;
    resetAllDrawingStructs();
    slot = lbl_803C7A24;
    count = 6;
    do {
        slot->func = nop_function;
        slot++;
    } while (--count != 0);
}
#endif

// .text:0x800B0CB8 size:0x70
// Task functions are called with a pointer to caller-stack scratch space.
typedef void (*DrawScriptFunc)(void* scratch);
// Tasks are defined as void(void) and get a scratch buffer in r3 they don't
// use; wasm needs the call to match the definition.
#ifdef TARGET_PC
#define CALL_DRAW_SCRIPT(f, scratch) ((void (*)(void))(f))()
#else
#define CALL_DRAW_SCRIPT(f, scratch) ((DrawScriptFunc)(f))(scratch)
#endif

// Runs the root task, then every task of the active list in order.
void RunDrawScripts_with_stack_variables(void) {
    u8 rootScratch[0x1C];
    u8 listScratch[0x14];
    SceneTask* task;
    lbl_803CC1B8 = &lbl_80111300;
    CALL_DRAW_SCRIPT(lbl_80111300.func, rootScratch);
    task = &lbl_803C7A24[lbl_803CC1B0 * 2];
#ifdef TARGET_PC
    {
        extern void port_trace_tasks(void** funcs, int count);
        void* funcs[64];
        int n = 0;
        SceneTask* t = task;
        funcs[n++] = (void*)lbl_80111300.func;
        while (t != NULL && n < 64) {
            funcs[n++] = (void*)t->func;
            t = t->next;
        }
        port_trace_tasks(funcs, n);
        {
            extern void port_trace_game(void);
            extern void port_trace_scene(void);
            port_trace_game();
            port_trace_scene();
        }
    }
#endif
#ifdef TARGET_PC
    {
        extern int port_spani_trace_on(void);
        extern void port_spani_flag_snapshot(void);
        extern void port_spani_flag_check(void* func);
        if (port_spani_trace_on()) {
            port_spani_flag_snapshot();
            do {
                void* fn = (void*)task->func;
                lbl_803CC1B8 = task;
                CALL_DRAW_SCRIPT(task->func, listScratch);
                port_spani_flag_check(fn);
                task = task->next;
            } while (task != NULL);
            return;
        }
    }
#endif
    do {
        lbl_803CC1B8 = task;
        CALL_DRAW_SCRIPT(task->func, listScratch);
        task = task->next;
    } while (task != NULL);
}

// Sprite system globals (see SpriteWork / SpriteState).
extern SpriteWork lbl_802FE8B8;
// The same memory as lbl_802FE8B8.wanted/.committed and .proj; fn_800B24D4 addresses them by these names.
#ifdef TARGET_PC
// One object on PC (the GameCube symbols are addresses inside lbl_802FE8B8).
#define lbl_802FEBF8 (lbl_802FE8B8.wanted) // [SPRITE_MAX_LAYERS * 2]: .wanted then .committed
#define lbl_802FE918 (lbl_802FE8B8.proj)
#else
extern SpriteState lbl_802FEBF8[SPRITE_MAX_LAYERS * 2]; // alias of lbl_802FE8B8.wanted
extern SpriteProj lbl_802FE918[SPRITE_MAX_LAYERS];      // alias of lbl_802FE8B8.proj
#endif
extern SpriteDrawCmd lbl_80111340[2][SPRITE_MAX_LAYERS]; // per buffer, per layer
extern GDCurrentDL* lbl_803CC0F0;  // __GDCurrentDL
extern GDCurrentDL* lbl_803CC1C0;  // current layer's display list
extern s32 lbl_803CC1C4;           // display-list buffer being filled (0/1)
extern s32 lbl_803CC1C8;           // texcoord fraction bits
extern s32 lbl_803CC1CC;           // scissor x
extern s32 lbl_803CC1D0;           // scissor y
extern s32 lbl_803CC1D4;           // current layer
extern s32* lbl_803CC1D8[2];       // per buffer: optional per-layer display-list sizes
extern s32 lbl_803CC1E0;           // size of one display-list buffer
extern GDCurrentDL* lbl_803CC1E4;  // display lists of the buffer being filled
extern s32 lbl_803CBB28;           // scissor width
extern s32 lbl_803CBB2C;           // scissor height
extern s32 lbl_803CBB30;           // layer count
extern SpriteState* lbl_803CBB34;  // wanted state of the current layer
extern SpriteState* lbl_803CBB38;  // committed state of the current layer
extern s32 lbl_803CBB3C;           // display-list growth granularity
extern SpriteProj* lbl_803CBB40;   // default projection of the current layer
extern u8 lbl_803CBB18[8];         // BP commands: untextured TEV order
extern u8 lbl_803CBB20[8];         // BP commands: textured TEV order
extern s16 lbl_801115A0[4][2];     // quad texcoords (scaled by fn_800B27A4)
extern Mtx44 lbl_801115B0;         // screen projection for fn_800B1188
extern QuadVtx lbl_801115F0[4];    // full-screen quad
extern QuadVtx lbl_803C8A24[510];  // fn_800B13C0 vertex scratch

extern u8 lbl_80111580[]; // 4x4 white RGB5A3 texture
void fn_800A7D4C(s32 layer, DrawNode* node); // queue a draw node on a layer

// GD (display-list) functions; they write to lbl_803CC0F0.
void GDInitGDLObj(GDCurrentDL* dl, u8* start, s32 length);
void GDSetBlendMode(GXBlendMode type, GXBlendFactor src, GXBlendFactor dst, GXLogicOp op);
void GDSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1);
void GDSetTexLookupMode(GXTexMapID id, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter minFilt, GXTexFilter magFilt,
                        f32 minLod, f32 maxLod, f32 lodBias, GXBool biasClamp, GXBool edgeLod, GXAnisotropy maxAniso);
void GDSetTexImgAttr(GXTexMapID id, u16 width, u16 height, GXTexFmt format);
void GDSetTexImgPtr(GXTexMapID id, void* image);
void GDSetTexTlut(GXTexMapID id, u32 tmemAddr, GXTlutFmt format);
void GDSetTexCoordScale2(GXTexCoordID coord, u16 sScale, GXBool sBias, GXBool sWrap, u16 tScale, GXBool tBias, GXBool tWrap);
void GDLoadTlut(void* tlut, u32 tmemAddr, GXTlutSize size);

// Fills a projection from a 4x4 matrix, like GXSetProjection.
static inline void SpriteProjFromMtx(SpriteProj* proj, Mtx44 m, s32 type) {
    s32 col = (type == GX_ORTHOGRAPHIC) + 2;
    proj->type = type;
    proj->p[0] = m[0][0];
    proj->p[1] = m[0][col];
    proj->p[2] = m[1][1];
    proj->p[3] = m[1][col];
    proj->p[4] = m[2][2];
    proj->p[5] = m[2][3];
}

// Sets the wanted projection of the current layer.
static inline void SpriteSetProjection(Mtx44 m, s32 type) {
    SpriteProjFromMtx(&lbl_803CBB34->proj, m, type);
}

// Makes sure the current layer's display list has room for size more bytes.
static inline void SpriteReserve(s32 size) {
    s32 needed = size;
    needed -= lbl_803CC1C0->end - lbl_803CC1C0->pDisplayListData;
    if (needed > 0 && AllocateSprite(lbl_803CC1D4, needed) > 0) {
        OSPanic("sprt.c", 0x19F, "SPRITE BUFFER OVERFLOW\n");
    }
}

#ifdef TARGET_PC
// MSSB_SPRITE_ZTEST=0 (test switch): sprites keep writing depth but never fail the depth test, to tell
// whether a flicker comes from sprites depth-testing against each other / the depth-reset quad.
static u32 port_sprite_zmode(u32 v) {
    static int s_noTest = -1;
    if (s_noTest < 0) {
        extern char* getenv(const char*);
        const char* e = getenv("MSSB_SPRITE_ZTEST");
        s_noTest = (e != NULL && e[0] == '0');
    }
    return s_noTest ? (v | 0xE) : v; // compare func bits 1-3 -> GX_ALWAYS
}
#define PORT_SPRITE_ZMODE(v) port_sprite_zmode(v)
#else
#define PORT_SPRITE_ZMODE(v) (v)
#endif

// Writes the BP Z-mode command; returns whether the committed Z mode changed.
static inline BOOL SpriteSyncZMode(void) {
    if (lbl_803CBB38->zMode != lbl_803CBB34->zMode) {
        lbl_803CBB38->zMode = lbl_803CBB34->zMode;
        SpriteReserve(5);
        *lbl_803CC1C0->pDisplayListData = 0x61;
        *(u32*)(lbl_803CC1C0->pDisplayListData + 1) = PORT_SPRITE_ZMODE(lbl_803CBB38->zMode);
        DL_BE32((lbl_803CC1C0->pDisplayListData + 1));
        lbl_803CC1C0->pDisplayListData += 5;
        return TRUE;
    }
    return FALSE;
}

// fn_800B0D38, size:0x30
void fn_800B0D38(s32 index, s32 value) {
    if (index >= 0 && index < lbl_803CBB30) {
        lbl_80111340[1][index].link = value;
        lbl_80111340[0][index].link = value;
    }
}

// fn_800B0D28, size:0x10
void fn_800B0D28(s32* layerSizes) {
    lbl_803CC1D8[0] = layerSizes;
    lbl_803CC1D8[1] = layerSizes;
}

// .text:0x800B0D68 size:0x414
// NONMATCHING 90%: same instructions; register allocation and some scheduling differ
#if NONMATCHING
// Grows layer's display list by at least needed bytes, taking unused space from the
// neighbouring layers (moving the lists in between). Returns how many bytes are still missing.
s32 AllocateSprite(s32 layer, s32 needed) {
    s32 below;
    s32 above;
    s32 last;
    u8* flushStart;
    u8* flushEnd;
    s32 remaining;
    s32 take;
    s32 avail;
    s32 moved;
    s32 i;
    u8* src;

    if (needed <= 0) {
        return 0;
    }
    // Round up to the growth granularity (small requests) or to 32 bytes.
    remaining = (needed < lbl_803CBB3C) ? lbl_803CBB3C * ((lbl_803CBB3C + needed - 1) / lbl_803CBB3C)
                                        : (needed + 0x1F) / 32 * 32;
    below = layer;
    last = lbl_803CBB30 - 1;
    above = layer;
    flushEnd = lbl_803CC1E4[0].begin;
    flushStart = lbl_803CC1E4[last].end;
    do {
        // Take free space from the end of a lower layer: shift the layers in between down.
        below -= (below > 0);
        avail = lbl_803CC1E4[below].length -
                (((s32)(lbl_803CC1E4[below].pDisplayListData - lbl_803CC1E4[below].begin) + 0x1F) & ~0x1F);
        if (remaining <= avail) {
            avail = remaining;
        }
        take = (below != layer) * avail;
        if (take != 0) {
            lbl_803CC1E4[below].length -= take;
            lbl_803CC1E4[below].end -= take;
            src = lbl_803CC1E4[below + 1].begin;
            moved = 0;
            i = below;
            do {
                i++;
                moved += lbl_803CC1E4[i].length;
                lbl_803CC1E4[i].begin -= take;
                lbl_803CC1E4[i].end -= take;
                lbl_803CC1E4[i].pDisplayListData -= take;
            } while (i < layer);
            if (moved != 0) {
                memmove(src - take, src, moved);
                if (flushStart > src - take) {
                    flushStart = src - take;
                }
                if (flushEnd < src) {
                    flushEnd = src;
                }
            }
            remaining -= take;
            lbl_803CC1E4[layer].length += take;
            lbl_803CC1E4[layer].end += take;
        }

        // Take free space from the end of a higher layer: shift the layers in between up.
        above += (above < last);
        avail = lbl_803CC1E4[above].length -
                (((s32)(lbl_803CC1E4[above].pDisplayListData - lbl_803CC1E4[above].begin) + 0x1F) & ~0x1F);
        if (remaining <= avail) {
            avail = remaining;
        }
        take = (above != layer) * avail;
        if (take != 0) {
            lbl_803CC1E4[above].length -= take;
            lbl_803CC1E4[above].end -= take;
            src = lbl_803CC1E4[layer + 1].begin;
            moved = 0;
            for (i = layer + 1; i <= above; i++) {
                moved += lbl_803CC1E4[i].length;
                lbl_803CC1E4[i].begin += take;
                lbl_803CC1E4[i].end += take;
                lbl_803CC1E4[i].pDisplayListData += take;
            }
            if (moved != 0) {
                memmove(src + take, src, moved);
                if (flushEnd < src + take) {
                    flushEnd = src + take;
                }
                if (flushStart > src) {
                    flushStart = src;
                }
            }
            remaining -= take;
            lbl_803CC1E4[layer].length += take;
            lbl_803CC1E4[layer].end += take;
        }
    } while (remaining > 0 && (below != 0 || last - above != 0));

    if (flushStart < flushEnd) {
        DCStoreRange(flushStart, (u32)(flushEnd - flushStart));
    }
    if (remaining > 0) {
        return remaining;
    }
    return 0;
}
#endif

// fn_800B117C, size:0xC
void fn_800B117C(u8 value) {
    lbl_803CBB34->noAlphaTest = value;
}

// .text:0x800B1188 size:0x11C
// Draws the full-screen quad lbl_801115F0 with the screen projection lbl_801115B0.
void fn_800B1188(void) {
    SpriteProj savedProj;
    u8 savedNoAlphaTest;
    u32 savedZMode;
    s16 one;
    memcpy(&savedProj, &lbl_803CBB38->proj, sizeof(SpriteProj));
    savedZMode = lbl_803CBB38->zMode;
    savedNoAlphaTest = lbl_803CBB38->noAlphaTest;
    one = 1 << lbl_803CC1C8;
    lbl_801115F0[3].s = one;
    lbl_801115F0[2].s = one;
    lbl_801115F0[2].t = one;
    lbl_801115F0[1].t = one;
    SpriteSetProjection(lbl_801115B0, GX_ORTHOGRAPHIC);
    lbl_803CBB34->noAlphaTest = 1;
    if (lbl_803CBB34->zMode != 0x4000001F) {
        lbl_803CBB34->zMode = 0x4000001F;
    }
    DrawSprite(GX_QUADS, lbl_801115F0, 4, NULL, 0, 0);
    memcpy(&lbl_803CBB34->proj, &savedProj, sizeof(SpriteProj));
    lbl_803CBB34->noAlphaTest = savedNoAlphaTest;
    lbl_803CBB34->zMode = savedZMode;
}

// .text:0x800B12A4 size:0x38
void DrawNullSprite(QuadVtx* verts, s32 count) {
    DrawSprite(GX_TRIANGLESTRIP, verts, count, NULL, 0, 0);
}

// .text:0x800B12DC size:0x38
void fn_800B12DC(QuadVtx* verts, s32 count) {
    DrawSprite(GX_TRIANGLEFAN, verts, count, NULL, 0, 0);
}

// .text:0x800B1314 size:0x3C
void fn_800B1314(QuadVtx* verts, TexImage* tex, u16 width, u16 height) {
    DrawSprite(GX_QUADS, verts, 4, tex, width, height);
}

// .text:0x800B1350 size:0x38
void DrawSprite_TexObj(QuadVtx* verts, TexImage* tex) {
    DrawSprite(GX_QUADS, verts, 4, tex, tex->width, tex->height);
}

// .text:0x800B1388 size:0x38
void fn_800B1388(QuadState* quad) {
    DrawSprite(GX_QUADS, quad->u.v, 4, NULL, 0, 0);
}

// .text:0x800B13C0 size:0xA8
void fn_800B13C0(Vec* pos, u32* colors, s32 count) {
    QuadVtx* v = lbl_803C8A24;
    s32 i;
    for (i = 0; i < count; i++) {
        memcpy(&v[i].pos, &pos[i], sizeof(Vec));
        v[i].color = colors[i];
        memcpy(&v[i].s, lbl_801115A0, 4);
    }
    DrawSprite(GX_TRIANGLEFAN, lbl_803C8A24, count, NULL, 0, 0);
}

// .text:0x800B1468 size:0x98
void fn_800B1468(Vec* pos, u32 color, TexImage* tex) {
    QuadVtx verts[4];
    s32 i;
    for (i = 0; i < 4; i++) {
        memcpy(&verts[i].pos, &pos[i], sizeof(Vec));
        verts[i].color = color;
        memcpy(&verts[i].s, lbl_801115A0[i], 4);
    }
    DrawSprite(GX_QUADS, verts, 4, tex, tex->width, tex->height);
}

// .text:0x800B1500 size:0x9BC
// NONMATCHING 94%: register allocation (verts/tex/dirty) differs, and the original evaluates an unused
// "all corners degenerate?" float check on verts (no effect, omitted here)
// litcheck: 0.0 (only the omitted check compares against it)
#if NONMATCHING
// Appends a primitive to the current layer's display list, first writing any state
// (projection, matrix, blend, alpha test, Z mode, texture) that differs from what the
// list already has. Consecutive quads with no state change are merged into one draw.
void DrawSprite(s32 prim, QuadVtx* verts, s32 count, TexImage* tex, u16 width, u16 height) {
    BOOL dirty = FALSE;
    BOOL changed;
    s32 alphaTest;

    if (tex != NULL) {
        lbl_803CC0F0 = lbl_803CC1C0;
        dirty = fn_800B1EBC(tex, 0, width, height);
        lbl_803CC0F0 = NULL;
    }

    if (memcmp(&lbl_803CBB38->proj, &lbl_803CBB34->proj, sizeof(SpriteProj)) != 0) {
        memcpy(&lbl_803CBB38->proj, &lbl_803CBB34->proj, sizeof(SpriteProj));
        SpriteReserve(0x21);
        // XF load: 7 projection registers at 0x1020
        *lbl_803CC1C0->pDisplayListData = 0x10;
        *(u16*)(lbl_803CC1C0->pDisplayListData + 1) = 6;
        DL_BE16((lbl_803CC1C0->pDisplayListData + 1));
        *(u16*)(lbl_803CC1C0->pDisplayListData + 3) = 0x1020;
        DL_BE16((lbl_803CC1C0->pDisplayListData + 3));
        lbl_803CC1C0->pDisplayListData += 5;
        *(u32*)lbl_803CC1C0->pDisplayListData = *(u32*)&lbl_803CBB34->proj.p[0];
        DL_BE32(lbl_803CC1C0->pDisplayListData);
        lbl_803CC1C0->pDisplayListData += 4;
        *(u32*)lbl_803CC1C0->pDisplayListData = *(u32*)&lbl_803CBB34->proj.p[1];
        DL_BE32(lbl_803CC1C0->pDisplayListData);
        lbl_803CC1C0->pDisplayListData += 4;
        *(u32*)lbl_803CC1C0->pDisplayListData = *(u32*)&lbl_803CBB34->proj.p[2];
        DL_BE32(lbl_803CC1C0->pDisplayListData);
        lbl_803CC1C0->pDisplayListData += 4;
        *(u32*)lbl_803CC1C0->pDisplayListData = *(u32*)&lbl_803CBB34->proj.p[3];
        DL_BE32(lbl_803CC1C0->pDisplayListData);
        lbl_803CC1C0->pDisplayListData += 4;
        *(u32*)lbl_803CC1C0->pDisplayListData = *(u32*)&lbl_803CBB34->proj.p[4];
        DL_BE32(lbl_803CC1C0->pDisplayListData);
        lbl_803CC1C0->pDisplayListData += 4;
        *(u32*)lbl_803CC1C0->pDisplayListData = *(u32*)&lbl_803CBB34->proj.p[5];
        DL_BE32(lbl_803CC1C0->pDisplayListData);
        lbl_803CC1C0->pDisplayListData += 4;
        *(u32*)lbl_803CC1C0->pDisplayListData = lbl_803CBB34->proj.type;
        DL_BE32(lbl_803CC1C0->pDisplayListData);
        lbl_803CC1C0->pDisplayListData += 4;
        changed = TRUE;
    } else {
        changed = FALSE;
    }
    dirty |= changed;

    if (memcmp(lbl_803CBB38->mtx, lbl_803CBB34->mtx, sizeof(Mtx)) != 0) {
        PSMTXCopy(lbl_803CBB34->mtx, lbl_803CBB38->mtx);
        SpriteReserve(0x35);
        // XF load: position matrix 0 (12 registers at 0)
        *lbl_803CC1C0->pDisplayListData = 0x10;
        *(u16*)(lbl_803CC1C0->pDisplayListData + 1) = 0xB;
        DL_BE16((lbl_803CC1C0->pDisplayListData + 1));
        *(u16*)(lbl_803CC1C0->pDisplayListData + 3) = 0;
        DL_BE16((lbl_803CC1C0->pDisplayListData + 3));
        lbl_803CC1C0->pDisplayListData += 5;
        memcpy(lbl_803CC1C0->pDisplayListData, lbl_803CBB34->mtx, sizeof(Mtx));
        DL_BE32_ARRAY(lbl_803CC1C0->pDisplayListData, 12);
        changed = TRUE;
        lbl_803CC1C0->pDisplayListData += sizeof(Mtx);
    } else {
        changed = FALSE;
    }
    dirty |= changed;

    if (lbl_803CBB38->blendMode != lbl_803CBB34->blendMode) {
        lbl_803CBB38->blendMode = lbl_803CBB34->blendMode;
        SpriteReserve(0xA);
        lbl_803CC0F0 = lbl_803CC1C0;
        switch (lbl_803CBB34->blendMode) {
        case 0:
            GDSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_CLEAR);
            break;
        case 1:
            GDSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
            break;
        case 2:
            GDSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
            break;
        case 3:
            GDSetBlendMode(GX_BM_SUBTRACT, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
            break;
        }
        changed = TRUE;
    } else {
        changed = FALSE;
    }
    dirty |= changed;

    alphaTest = 0;
    if (lbl_803CBB34->noAlphaTest) {
        alphaTest = 2;
    }
    if (lbl_803CBB38->alphaTest == alphaTest) {
        changed = FALSE;
    } else {
        lbl_803CBB38->alphaTest = alphaTest;
        if (alphaTest != 0) {
            if (lbl_803CBB38->zMode != 0x40000013) {
                lbl_803CBB38->zMode = 0x40000013;
                SpriteReserve(5);
                *lbl_803CC1C0->pDisplayListData = 0x61;
                *(u32*)(lbl_803CC1C0->pDisplayListData + 1) = PORT_SPRITE_ZMODE(0x40000013);
                DL_BE32((lbl_803CC1C0->pDisplayListData + 1));
                lbl_803CC1C0->pDisplayListData += 5;
            }
            SpriteReserve(5);
            lbl_803CC0F0 = lbl_803CC1C0;
            GDSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
            lbl_803CC0F0 = NULL;
        } else {
            if (lbl_803CBB38->zMode != lbl_803CBB34->zMode) {
                lbl_803CBB38->zMode = lbl_803CBB34->zMode;
                SpriteReserve(5);
                *lbl_803CC1C0->pDisplayListData = 0x61;
                *(u32*)(lbl_803CC1C0->pDisplayListData + 1) = PORT_SPRITE_ZMODE(lbl_803CBB34->zMode);
                DL_BE32((lbl_803CC1C0->pDisplayListData + 1));
                lbl_803CC1C0->pDisplayListData += 5;
            }
            SpriteReserve(5);
            lbl_803CC0F0 = lbl_803CC1C0;
            GDSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
            lbl_803CC0F0 = NULL;
        }
        changed = TRUE;
    }
    {
        BOOL zChanged = changed;
        if (!changed) {
            zChanged = SpriteSyncZMode();
        }
        dirty |= zChanged;
    }

    if ((lbl_803CBB34->textured == 1) == !tex) {
        u8* cmd = lbl_803CBB20;
        if (tex == NULL) {
            cmd = lbl_803CBB18;
        }
        SpriteReserve(5);
        memcpy(lbl_803CC1C0->pDisplayListData, cmd, 5);
        dirty = TRUE;
        lbl_803CC1C0->pDisplayListData += 5;
        lbl_803CBB34->textured = (tex != NULL);
    }

    if (lbl_803CBB34->primOffset >= 0 && !dirty) {
        u8* hdr = lbl_803CC1C0->begin + lbl_803CBB34->primOffset;
#ifdef TARGET_PC
        u16 n = read_be16(hdr + 1);
#else
        u16 n = *(u16*)(hdr + 1);
#endif
        if (hdr[0] == GX_QUADS && prim == GX_QUADS &&
            lbl_803CC1C0->pDisplayListData == hdr + n * sizeof(QuadVtx) + 3 && n < 0xFFFF - count) {
            s32 size = count * sizeof(QuadVtx);
            SpriteReserve(size);
            hdr = lbl_803CC1C0->begin + lbl_803CBB34->primOffset;
            memcpy(lbl_803CC1C0->pDisplayListData, verts, size);
            DL_BE_QUADVTX(lbl_803CC1C0->pDisplayListData, count);
            lbl_803CC1C0->pDisplayListData += size;
#ifdef TARGET_PC
            swap16_inplace(hdr + 1);
            *(u16*)(hdr + 1) += count;
            swap16_inplace(hdr + 1);
#else
            *(u16*)(hdr + 1) += count;
#endif
            return;
        }
    }
    {
        s32 size = count * sizeof(QuadVtx);
        lbl_803CBB34->primOffset = (s32)(lbl_803CC1C0->pDisplayListData - lbl_803CC1C0->begin);
        SpriteReserve(size + 3);
        *lbl_803CC1C0->pDisplayListData = prim;
        *(u16*)(lbl_803CC1C0->pDisplayListData + 1) = count;
        DL_BE16((lbl_803CC1C0->pDisplayListData + 1));
        lbl_803CC1C0->pDisplayListData += 3;
        memcpy(lbl_803CC1C0->pDisplayListData, verts, size);
        DL_BE_QUADVTX(lbl_803CC1C0->pDisplayListData, count);
        lbl_803CC1C0->pDisplayListData += size;
    }
}
#endif

// .text:0x800B1EBC size:0x2A4
// NONMATCHING 99.6%: map/width/height parameters get different saved registers
#if NONMATCHING
// Loads tex into texture map `map` of the current display list (if it isn't already)
// and sets the texcoord scale. Returns whether anything was written.
s32 fn_800B1EBC(TexImage* tex, s32 map, u32 width, u32 height) {
    s32 id = map + 1;
    s32 written;
    lbl_803CBB34->texSerial[map] = lbl_803CBB34->serial;
    written = FALSE;
    lbl_803CBB34->serial++;
    if (lbl_803CBB34->tex[map] != tex) {
        lbl_803CBB34->tex[map] = tex;
        SpriteReserve(((tex->tlut != NULL) * 7 + 4) * 5 + DL_AURORA_TEX_BYTES);
        if (tex->tlut != NULL) {
            u32 tmem;
            u32 tlutSize = GX_TLUT_16;
            while (tlutSize * 16 < tex->tlutEntries) {
                tlutSize *= 2;
            }
            tmem = (map << 13) + 0xC0000;
            GDLoadTlut(PTR32_GET(void, tex->tlut), tmem, tlutSize);
            GDSetTexTlut(id, tmem, tex->tlutFormat);
        }
        {
            s32 wrapS = tex->wrapS;
            s32 wrapT;
            // Only power-of-two dimensions can repeat/mirror.
            if (wrapS != GX_CLAMP) {
                u16 n = tex->width;
                u16 bits = 0;
                while (n != 0) {
                    bits += n & 1;
                    n >>= 1;
                }
                if (bits > 1) {
                    wrapS = GX_CLAMP;
                }
            }
            wrapT = tex->wrapT;
            if (wrapT != GX_CLAMP) {
                u16 n = tex->height;
                u16 bits = 0;
                while (n != 0) {
                    bits += n & 1;
                    n >>= 1;
                }
                if (bits > 1) {
                    wrapT = GX_CLAMP;
                }
            }
            GDSetTexLookupMode(id, wrapS, wrapT, tex->minFilter, tex->magFilter, tex->minLOD, tex->maxLOD, tex->lodBias,
                        GX_FALSE, GX_FALSE, GX_ANISO_1);
        }
        GDSetTexImgAttr(id, tex->width, tex->height, tex->format);
        GDSetTexImgPtr(id, PTR32_GET(u8, tex->data));
        written = TRUE;
    }
    if (lbl_803CBB34->texWidth != width || lbl_803CBB34->texHeight != height) {
        lbl_803CBB34->texWidth = width;
        lbl_803CBB34->texHeight = height;
        SpriteReserve(0xF);
        GDSetTexCoordScale2(map, width, GX_FALSE, GX_FALSE, height, GX_FALSE, GX_FALSE);
        written = TRUE;
    }
    return written;
}
#endif

// fn_800B2160, size:0xC
void fn_800B2160(u8 value) {
    lbl_803CBB34->blendMode = value;
}

// fn_800B216C, size:0x3C
// Sets the wanted Z mode (enable, compare func, update enable); returns whether it changed.
s32 fn_800B216C(u8 flag, u32 mode, u8 index) {
    u32 value = ((u32)index << 4) | (flag | (mode << 1)) | 0x40000000;
    if (lbl_803CBB34->zMode == value) {
        return 0;
    }
    lbl_803CBB34->zMode = value;
    return 1;
}

// fn_800B21A8, size:0x98
void fn_800B21A8(s32 mode) {
    if (mode == 2) {
        s32 changed;
        u32 old = lbl_803CBB34->zMode;
        if (old == 0x40000013) {
            changed = 0;
        } else {
            lbl_803CBB34->zMode = 0x40000013;
            changed = 1;
        }
        if (changed != 0) {
            lbl_803CBB34->savedZMode = old;
        }
    } else if (mode != 0) {
        if (lbl_803CBB34->zMode != 0x40000017) {
            lbl_803CBB34->zMode = 0x40000017;
        }
    } else {
        if (lbl_803CBB34->zMode != 0x4000001F) {
            lbl_803CBB34->zMode = 0x4000001F;
        }
    }
}

// .text:0x800B2240 size:0x294
// SpriteDrawCmd callback: sets up GX for sprites and runs a layer's display list.
#ifdef TARGET_PC
extern int port_spani_trace_on(void);
extern int port_spani_trace_budget(void);
extern u32 port_spani_trace_frame;
// Draw-thread side of MSSB_SPANI_TRACE: what each sprite layer node actually hands the renderer.
static void port_trace_sprite_draw(SpriteDrawCmd* cmd, GDCurrentDL* dl) {
    static s32 s_prev[2][SPRITE_MAX_LAYERS];
    s32 idx = (s32)(cmd - &lbl_80111340[0][0]);
    s32 len = (s32)(dl->pDisplayListData - dl->begin);
    if (idx < 0 || idx >= 2 * SPRITE_MAX_LAYERS) {
        return;
    }
    {
        s32 prev = s_prev[idx / SPRITE_MAX_LAYERS][idx % SPRITE_MAX_LAYERS];
        if (((len == 0) != (prev == 0) || (prev > 256 && len < prev / 2) || (len > 256 && prev < len / 2)) &&
            port_spani_trace_budget()) {
            OSReport("[sdraw] f=%u buf %d layer %d bytes %d -> %d\n", port_spani_trace_frame,
                     (int)(idx / SPRITE_MAX_LAYERS), (int)(idx % SPRITE_MAX_LAYERS), (int)prev, (int)len);
        }
        s_prev[idx / SPRITE_MAX_LAYERS][idx % SPRITE_MAX_LAYERS] = len;
    }
}
#endif
void fn_800B2240(SpriteDrawCmd* cmd) {
    GDCurrentDL* dl = cmd->dl;
#ifdef TARGET_PC
    if (port_spani_trace_on()) {
        port_trace_sprite_draw(cmd, dl);
    }
#endif
    GXColor fogColor;
    GXTexObj texObj;
    Mtx mtx;

    GXSetScissor(lbl_803CC1CC, lbl_803CC1D0, lbl_803CBB28, lbl_803CBB2C);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetZCompLoc(GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetCullMode(GX_CULL_NONE);
    fogColor.r = fogColor.g = fogColor.b = 0;
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, fogColor);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, lbl_803CC1C8);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXInitTexObj(&texObj, lbl_80111580, 4, 4, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXLoadTexObj(&texObj, GX_TEXMAP1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
#ifdef TARGET_PC
    // On the GameCube this ran right after fn_800B251C left lbl_803CBB40 at layer 0; on PC the main
    // thread may already be moving it between layers, so use layer 0's default projection directly.
    GXSetProjectionv(&lbl_802FE918[0].type);
#else
    GXSetProjectionv(&lbl_803CBB40->type);
#endif
    PSMTXIdentity(mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXCallDisplayList(dl->begin, (u32)(dl->pDisplayListData - dl->begin));
}

// .text:0x800B24D4 size:0x48
// Selects the layer that sprite drawing goes to.
void fn_800B24D4(s32 layer) {
    SpriteState* state;
    lbl_803CC1D4 = layer;
    state = &lbl_802FEBF8[layer];
    lbl_803CBB34 = state;
    lbl_803CBB38 = state + SPRITE_MAX_LAYERS;
    lbl_803CBB40 = &lbl_802FE918[layer];
    lbl_803CC1C0 = &lbl_803CC1E4[layer];
}

#ifdef TARGET_PC
#include <stdlib.h>
// MSSB_SPANI_TRACE=1: log when 2D sprites stop/start producing draw data (flicker hunt).
u32 port_spani_trace_frame;
int port_spani_trace_on(void) {
    static int s_on = -1;
    if (s_on < 0) {
        const char* e = getenv("MSSB_SPANI_TRACE");
        s_on = (e != NULL && e[0] != '\0' && e[0] != '0');
    }
    return s_on;
}
int port_spani_trace_budget(void) {
    static int s_lines = 0;
    return s_lines++ < 30000;
}
// Bytes written so far this frame into all sprite layer display lists.
u32 port_sprite_total_bytes(void) {
    u32 total = 0;
    s32 i;
    if (lbl_803CC1E4 == NULL) {
        return 0;
    }
    for (i = 0; i < lbl_803CBB30; i++) {
        total += (u32)(lbl_803CC1E4[i].pDisplayListData - lbl_803CC1E4[i].begin);
    }
    return total;
}
static void port_trace_layers(void) {
    static s32 s_prev[SPRITE_MAX_LAYERS];
    s32 i;
    for (i = 0; i < lbl_803CBB30 && i < SPRITE_MAX_LAYERS; i++) {
        s32 len = (s32)(lbl_803CC1E4[i].pDisplayListData - lbl_803CC1E4[i].begin);
        s32 cap = (s32)(lbl_803CC1E4[i].end - lbl_803CC1E4[i].begin);
        s32 prev = s_prev[i];
        // Log empty<->non-empty changes and big drops (>50%).
        if (((len == 0) != (prev == 0) || (prev > 256 && len < prev / 2) || (len > 256 && prev < len / 2)) &&
            port_spani_trace_budget()) {
            OSReport("[spani] f=%u layer %d (id %d) bytes %d -> %d (cap %d)\n", port_spani_trace_frame, (int)i,
                     (int)lbl_802FE8B8.layerIds[i], (int)prev, (int)len, (int)cap);
        }
        s_prev[i] = len;
    }
}
#endif

// .text:0x800B251C size:0x288
// NONMATCHING 91%: the original addresses the SpriteWork arrays from a pooled base (base+0x340, then +n*0x90);
// ours folds the offsets, plus small scheduling differences
#if NONMATCHING
// Ends the frame: pads and flushes every layer's display list and queues it for drawing
// (fn_800B2240), then switches to the other buffer and resets all layer states.
void fn_800B251C(void) {
    SpriteWork* work = &lbl_802FE8B8;
    s32* layerId;
    s32 i;
    s32 len;
    SpriteState* state;
    GDCurrentDL* dls;

    if (lbl_803CC1C0 == NULL) {
        return;
    }
#ifdef TARGET_PC
    port_spani_trace_frame++; // also numbers MSSB_FRAME_DUMP captures
    if (port_spani_trace_on()) {
        port_trace_layers();
    }
#endif
    layerId = &work->layerIds[0];
    i = 0;
    lbl_803CC1C0 = lbl_803CC1E4;
    while (i < lbl_803CBB30) {
        len = (s32)(lbl_803CC1C0->pDisplayListData - lbl_803CC1C0->begin);
        if (len != 0) {
            while (len & 0x1F) {
                len++;
                *lbl_803CC1C0->pDisplayListData = 0;
                lbl_803CC1C0->pDisplayListData++;
            }
            DCStoreRangeNoSync(lbl_803CC1C0->begin, len);
#ifdef TARGET_PC
            {
                // The draw thread runs this node during the NEXT frame's update, concurrently with
                // the main thread. On the GameCube it always finished before this function's reset
                // of that buffer (below, one frame later); on PC it can lag (texture uploads, shader
                // compiles), and then read a zero length / moved begin and drop the whole layer.
                // Hand it a snapshot of begin/length taken now; the bytes themselves are not
                // rewritten until the main loop has waited for the draw pass.
                static GDCurrentDL s_dlSnap[2][SPRITE_MAX_LAYERS];
                GDCurrentDL* snap = &s_dlSnap[lbl_803CC1C4][i];
                *snap = *lbl_803CC1C0;
                lbl_80111340[lbl_803CC1C4][i].dl = snap;
            }
#else
            lbl_80111340[lbl_803CC1C4][i].dl = lbl_803CC1C0;
#endif
            lbl_80111340[lbl_803CC1C4][i].draw = fn_800B2240;
            fn_800A7D4C(*layerId, (DrawNode*)&lbl_80111340[lbl_803CC1C4][i]);
        }
        layerId++;
        i++;
        lbl_803CC1C0++;
    }

    lbl_803CC1D4 = lbl_803CBB30;
    lbl_803CC1C4 ^= 1;
    state = work->wanted + lbl_803CBB30;
    dls = *(work->dl + lbl_803CC1C4);
    lbl_803CC1E4 = dls;
    lbl_803CBB34 = state;
    lbl_803CBB38 = state + SPRITE_MAX_LAYERS;
    lbl_803CBB40 = work->proj + lbl_803CBB30;
    lbl_803CC1C0 = dls + lbl_803CBB30;
    lbl_803CC1C0->end = dls[0].begin + lbl_803CC1E0;
    while (lbl_803CC1D4 != 0) {
        lbl_803CC1D4--;
        lbl_803CC1C0--;
        lbl_803CBB34--;
        lbl_803CBB38--;
        lbl_803CBB40--;
        memset(lbl_803CBB34, 0, sizeof(SpriteState));
        PSMTXIdentity(lbl_803CBB34->mtx);
        memcpy(&lbl_803CBB34->proj, lbl_803CBB40, sizeof(SpriteProj));
        lbl_803CBB34->blendMode = 1;
        lbl_803CBB34->primOffset = -1;
        memcpy(lbl_803CBB38, lbl_803CBB34, sizeof(SpriteState));
        // Optional new layer sizes: lay the lists out downwards from the buffer end.
        if (lbl_803CC1D8[lbl_803CC1C4] != NULL) {
            lbl_803CC1C0->length = lbl_803CC1D8[lbl_803CC1C4][lbl_803CC1D4];
            lbl_803CC1C0->begin = lbl_803CC1C0->end - lbl_803CC1C0->length;
            if (lbl_803CC1D4 != 0) {
                lbl_803CC1C0[-1].end = lbl_803CC1C0->begin;
            }
        }
        lbl_803CC1C0->pDisplayListData = lbl_803CC1C0->begin;
    }
    lbl_803CC1D8[lbl_803CC1C4] = NULL;
}
#endif

// .text:0x800B27A4 size:0x38
// Sets the texcoord fraction bits; the quad texcoords become 1.0 in that format.
void fn_800B27A4(s32 fracBits) {
    if (fracBits >= 0 && fracBits <= 14) {
        s16 one = 1 << fracBits;
        lbl_803CC1C8 = fracBits;
        lbl_801115A0[3][0] = one;
        lbl_801115A0[2][1] = one;
        lbl_801115A0[2][0] = one;
        lbl_801115A0[1][1] = one;
    }
}

// .text:0x800B27DC size:0x78
// NONMATCHING 77%: int-to-float conversion and column index are scheduled in a different order
#if NONMATCHING
void fn_800B27DC(Mtx44 m, s32 type) {
    SpriteSetProjection(m, type);
}
#endif

// .text:0x800B2854 size:0x274
// NONMATCHING 80%: the original recomputes bufSize/2 after the memcpy and keeps the projection column
// computation inside the loop (reproduced with the two pragmas below); left: the proj offset induction
// variable starts from i*0x1C instead of 0, and register allocation
#pragma opt_propagation off
#pragma opt_loop_invariants off
#if NONMATCHING
// Initialises the sprite system: numLayers layers drawing into buf, split into two
// display-list buffers of bufSize/2 (one is filled while the other is drawn). Each layer
// gets layerSizes[i] bytes (or an equal share) and the projection proj.
void fn_800B2854(u8* buf, s32 bufSize, Mtx44 proj, s32 projType, s32 numLayers, s32* layerIds, s32* layerSizes) {
    u8* buf0;
    u8* buf1;
    s32 size;
    s32 i;
    s32* sizes;
    GDCurrentDL* dl;
    s32 defaultSize;
    SpriteState* state;
    GDCurrentDL* dls;
    SpriteWork* work = &lbl_802FE8B8;

    lbl_803CBB30 = numLayers;
    lbl_803CC1E0 = bufSize / 2;
    memcpy(work->layerIds, layerIds, numLayers * sizeof(s32));
    bufSize /= 2;
    buf0 = buf;
    buf1 = buf + bufSize;
    dl = work->dl[0];
    sizes = layerSizes;
    defaultSize = bufSize / numLayers;
    for (i = 0; i < numLayers; i++) {
        if (layerSizes != NULL) {
            size = *sizes;
        } else {
            size = defaultSize;
        }
        GDInitGDLObj(&dl[0], buf0, size);
        GDInitGDLObj(&dl[SPRITE_MAX_LAYERS], buf1, size);
        SpriteProjFromMtx(&lbl_803CBB40[i], proj, projType);
        buf0 += size;
        buf1 += size;
        sizes++;
        dl++;
    }

    lbl_803CC1D4 = lbl_803CBB30;
    state = &work->wanted[lbl_803CBB30];
    lbl_803CBB34 = state;
    lbl_803CBB38 = state + SPRITE_MAX_LAYERS;
    dls = work->dl[lbl_803CC1C4];
    lbl_803CC1E4 = dls;
    lbl_803CC1C0 = &dls[lbl_803CBB30];
    lbl_803CBB40 = &work->proj[lbl_803CBB30];
    lbl_803CC1C0->end = dls[0].begin + lbl_803CC1E0;
    while (lbl_803CC1D4 != 0) {
        lbl_803CC1D4--;
        lbl_803CC1C0--;
        lbl_803CBB34--;
        lbl_803CBB38--;
        lbl_803CBB40--;
        memset(lbl_803CBB34, 0, sizeof(SpriteState));
        PSMTXIdentity(lbl_803CBB34->mtx);
        memcpy(&lbl_803CBB34->proj, lbl_803CBB40, sizeof(SpriteProj));
        lbl_803CBB34->blendMode = 1;
        lbl_803CBB34->primOffset = -1;
        memcpy(lbl_803CBB38, lbl_803CBB34, sizeof(SpriteState));
    }
    lbl_803CC1D8[1] = NULL;
    lbl_803CC1D8[0] = NULL;
}
#endif

#pragma opt_propagation reset
#pragma opt_loop_invariants reset

// .text:0x800B2AC8 size:0x84
// For every bone whose flags have bit 3 or 4 set, passes the skinning state's
// unk8 (fn_800BF068) to the bone's display object (fn_800BC824).
void fn_800B2AC8(LoadedActorLayout* layout) {
    s32 i;
    LoadedGeoPalette* pal = PTR32_GET(LoadedGeoPalette, layout->pal);
    for (i = 0; i < layout->totalBones; i++) {
        if ((layout->bones[i].flags & 0x18) && layout->bones[i].geoFileID != 0xFFFF) {
            struct DODisplayObj* obj = (struct DODisplayObj*)PTR32_GET(u8, PTR32_GET(LoadedGeoEntry, pal->entries)[layout->bones[i].geoFileID].obj);
            fn_800BC824(obj, ((SkinState*)fn_800BF068())->unk8);
        }
    }
}

// .text:0x800B2B4C size:0x8
void fn_800B2B4C(GameActor* actor, f32 speed) {
    actor->blendSpeed = speed;
}

// .text:0x800B2B54 size:0x18
void fn_800B2B54(GameActor* actor, u16 bone, u8 value) {
    actor->boneArray[bone]->flags = value;
}

// .text:0x800B2B6C size:0x8
void Set_FUN_800b2b6c(GameActor* actor, u16* boneRemap) {
    actor->boneRemap = boneRemap;
}

// .text:0x800B2B74 size:0x34
// Moves a bone to the end of the actor's draw-priority list.
void fn_800B2B74(GameActor* actor, u16 bone) {
    DSInsertListObject(&actor->drawPriorityList, actor->drawPriorityList.Tail, (Ptr)actor->boneArray[bone]);
}

// .text:0x800B2BA8 size:0x3C
// Gives a bone another actor's bone's display object (or none); returns the old one.
struct DODisplayObj* fn_800B2BA8(GameActor* actor, u16 bone, GameActor* src, u16 srcBone) {
    GameBone* dst = actor->boneArray[bone];
    struct DODisplayObj* old = dst->dispObj;
    if (src != NULL) {
        dst->dispObj = src->boneArray[srcBone]->dispObj;
    } else {
        dst->dispObj = NULL;
    }
    return old;
}

// .text:0x800B2BE4 size:0x18
// Restores a bone's original display object.
void fn_800B2BE4(GameActor* actor, u16 bone) {
    GameBone* b = actor->boneArray[bone];
    b->dispObj = b->baseDispObj;
}

// .text:0x800B2BFC size:0xC
void fn_800B2BFC(GameActor* actor, u16 boneA, u16 boneB) {
    actor->anchorBoneA = boneA;
    actor->anchorBoneB = boneB;
}

// .text:0x800B2C08 size:0x8
void fn_800B2C08(GameActor* actor, u16 bone) {
    actor->rootBone = bone;
}

// .text:0x800B2C10 size:0x34
// Transforms v in place by the actor's matrix at index.
void fn_800B2C10(GameActor* actor, u16 index, Vec* v) {
    PSMTXMultVec(actor->forwardMtxArray[index], v, v);
}

// ---- Data (initialisers generated from the original DOL) ----

// .data 0x801112F0..0x80111640
SoundConfig lbl_801112F0 = {64, 48, 16, 1, 0, 0x800000}; // NOTE: type size 0xC != symbol size 0x10
void PrepFilesToBeLoaded(void);
SceneTask lbl_80111300 = {
    PrepFilesToBeLoaded,
    NULL,
    NULL,
    NULL,
    0,
    0,
    {NULL},
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    {0, 0, 0, 0},
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};
SpriteDrawCmd lbl_80111340[2][24] = {
    {
        {0, fn_800B2240, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
    },
    {
        {0, fn_800B2240, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
        {0, NULL, NULL},
    },
};
u8 lbl_80111580[32] = {
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
};
s16 lbl_801115A0[4][2] = {{0, 0}, {0, 1}, {1, 1}, {1, 0}};
Mtx44 lbl_801115B0 = {
    {0.003125f, 0.0f, 0.0f, -1.0f},
    {0.0f, -0.004464286f, 0.0f, 1.0f},
    {0.0f, 0.0f, -5.9604645e-08f, -1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
};
#ifdef TARGET_PC
// The depth-reset quad must write the far-plane depth exactly, as on the GameCube (24-bit 0xFFFFFF):
// sprites drawn after it with LEQUAL can sit exactly on the far plane (GX z_ndc = 0). aurora uses
// reversed Z (depth = -z_ndc, LEQUAL -> GreaterEqual), so the original -16777215 (z_ndc = -2^-24)
// stores depth 2^-24 and a far-plane sprite (depth 0) fails 0 >= 2^-24: it blinks out while its entry
// animation requests the reset (team logos, minigame panels). -2^24, exact with the 2^-24 scale in
// lbl_801115B0, gives z_ndc = 0 -> depth 0 -> the test passes, as on hardware.
#define SPRITE_ZRESET_Z -16777216.0f
#else
#define SPRITE_ZRESET_Z -16777215.0f
#endif
QuadVtx lbl_801115F0[4] = {
    {{0.0f, 0.0f, SPRITE_ZRESET_Z}, 0, 0, 0},
    {{0.0f, 448.0f, SPRITE_ZRESET_Z}, 0, 0, 1},
    {{640.0f, 448.0f, SPRITE_ZRESET_Z}, 0, 1, 1},
    {{640.0f, 0.0f, SPRITE_ZRESET_Z}, 0, 1, 0},
};

// .bss 0x802FE8A0..0x803009F8 (MWCC lays these out in reverse definition order)
// lbl_802FE918 (.proj), lbl_802FEBF8 (.wanted) and lbl_802FF978 (.committed) are
// inside lbl_802FE8B8. TODO port: fn_800B24D4 still names lbl_802FEBF8/lbl_802FE918
// (the original references them as separate symbols).
SpriteWork lbl_802FE8B8;
SndHeap lbl_802FE8A0[2];

// .sdata 0x803CBB10..0x803CBB48
SndHeap* lbl_803CBB10 = lbl_802FE8A0;
u8 lbl_803CBB18[8] = {97, 40, 59, 240, 64, 0, 0, 0};
u8 lbl_803CBB20[8] = {97, 40, 59, 240, 65, 0, 0, 0};
s32 lbl_803CBB28 = 640;
s32 lbl_803CBB2C = 480;
s32 lbl_803CBB30 = 1;
SpriteState* lbl_803CBB34 = lbl_802FE8B8.wanted;
SpriteState* lbl_803CBB38 = lbl_802FE8B8.committed;
s32 lbl_803CBB3C = 1024;
SpriteProj* lbl_803CBB40 = lbl_802FE8B8.proj;

// .sbss 0x803CC1B0..0x803CC1E8 (MWCC lays these out in reverse definition order)
GDCurrentDL* lbl_803CC1E4;
s32 lbl_803CC1E0;
s32* lbl_803CC1D8[2];
s32 lbl_803CC1D4;
s32 lbl_803CC1D0;
s32 lbl_803CC1CC;
s32 lbl_803CC1C8;
s32 lbl_803CC1C4;
GDCurrentDL* lbl_803CC1C0;
SceneTask* lbl_803CC1B8;
u16 lbl_803CC1B4;
u16 lbl_803CC1B2;
u16 lbl_803CC1B0;

