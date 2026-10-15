#include "game/kinoko.h"
#include "header_rep_data.h"
#include "Dolphin/GX/GXFifo.h"
#include "static/GameSettings.h"
#include "static/Camera.h"
#include "Dolphin/GX/GXTypes.h"
#include "main/file_80008E00.h" // lbl_80366158
#include "game/UnknownHomes_Game.h" // g_Minigame
#pragma dont_inline on

// One mushroom-ribbon segment (0x2C bytes).
typedef struct KinokoSeg {
    /*0x00*/ Vec pos;
    /*0x0C*/ Vec edgeA;     // pos + side * lbl_3_rodata_4038 (fn_3_169E70)
    /*0x18*/ Vec edgeB;     // pos + side * lbl_3_rodata_403C
    /*0x24*/ GXColor color; // a fades along the ribbon
    /*0x28*/ u8 colorFrom;  // lbl_3_data_2A308 indices blended by fn_3_16B5B4
    /*0x29*/ u8 colorTo;
    /*0x2A*/ u8 active;
    /*0x2B*/ u8 _2B;
} KinokoSeg; // size: 0x2C

// lbl_3_data_28928: the mushroom ribbon effect.
typedef struct KinokoState {
    /*0x0000*/ KinokoSeg ribbon[6][25]; // [0] is the head of each ribbon
    /*0x19C8*/ u8 _19C8[0x19D4 - 0x19C8];
    /*0x19D4*/ s32 tick;
    /*0x19D8*/ u8 _19D8[0x19DC - 0x19D8];
    /*0x19DC*/ s8 charId;
    /*0x19DD*/ u8 enabled;
    /*0x19DE*/ u8 _19DE[2];
} KinokoState; // size: 0x19E0

// lbl_3_bss_BA00: the texture the mushroom aura currently uses (one of lbl_3_bss_BA08's two).
typedef struct {
    /*0x0*/ u8* buf;      // KinokoTex.img0 or img1
    /*0x4*/ GXTexObj* tex; // KinokoTex.tex0 or tex1
} KinokoCtl;
// lbl_3_bss_BA08 (right after lbl_3_bss_BA00): frame counter and the two 4x4 IA8 aura textures.
typedef struct {
    /*0x00*/ s32 frame;
    /*0x04*/ GXTexObj tex1;
    /*0x24*/ GXTexObj tex0;
    /*0x44*/ u8 _44[0x58 - 0x44];
    /*0x58*/ u8 img1[0x40]; // 32-byte aligned
    /*0x98*/ u8 img0[0x40];
} KinokoTex; // size: 0xD8
extern KinokoCtl lbl_3_bss_BA00;
extern KinokoTex lbl_3_bss_BA08;
// The original reaches lbl_3_bss_BA08's members as offsets from lbl_3_bss_BA00 (the two are
// adjacent in .bss); the port names them.
#if NONMATCHING
#define KINOKO_FRAME(c) (lbl_3_bss_BA08.frame)
#define KINOKO_TEX0(c) (&lbl_3_bss_BA08.tex0)
#define KINOKO_TEX1(c) (&lbl_3_bss_BA08.tex1)
#define KINOKO_IMG0(c) (lbl_3_bss_BA08.img0)
#define KINOKO_IMG1(c) (lbl_3_bss_BA08.img1)
#else
// c: lbl_3_bss_BA00 as a u8*.
#define KINOKO_FRAME(c) (*(s32*)((c) + 8))
#define KINOKO_TEX0(c) ((GXTexObj*)((c) + 0x2C))
#define KINOKO_TEX1(c) ((GXTexObj*)((c) + 0xC))
#define KINOKO_IMG0(c) ((c) + 0xA0)
#define KINOKO_IMG1(c) ((c) + 0x60)
#endif
extern s8 lbl_3_data_2A330;
extern s32 fn_800247E4(s32, s32, s32, s32);
extern void DCFlushRange(void*, u32);


extern s32 fn_8005268C(void);
extern camera_803c639c_s* fn_80052768_getCamera(s32);

// .text:0x0016917C size:0x2C0
void fn_3_16917C(s32 unused, s32* stage, s32* coord, s32* map, u8* c1, u8* c2) {
    KinokoCtl* c = &lbl_3_bss_BA00;
    s32 v;
    s32 i;
    s32 t;
    KINOKO_FRAME((u8*)c) += (lbl_80366158._28 == 0);
    if ((KINOKO_FRAME((u8*)c) & 1) == 0) {
        v = c->buf[fn_800247E4(0, 0, 4, 4)];
        v += lbl_3_data_2A330 * 2;
        if (v > 0xFF) {
            v = 0xFF;
        } else if (v < 0) {
            v = 0;
        }
        for (i = 0; i < 32; i += 2) {
            c->buf[i] = v;
        }
        DCFlushRange(c->buf, 4);
        t = v + lbl_3_data_2A330 * 2;
        if (t > 0xFF || t < 0) {
            lbl_3_data_2A330 *= -1;
        }
    }
    GXLoadTexObj(c->tex, *map);
    GXSetTexCoordGen2(*coord, 1, 4, 0x3C, 0, 0x7D);
    GXSetTevOrder(*stage, *coord, *map, 0xFF);
    if (c->buf == KINOKO_IMG0((u8*)c)) {
        GXSetTevColorIn(*stage, 0, 8, 9, 0xF);
        GXSetTevColorOp(*stage, 0, 0, 0, 1, 0);
        GXSetTevAlphaIn(*stage, 7, 7, 7, 0);
        GXSetTevAlphaOp(*stage, 0, 0, 0, 1, 0);
    } else {
        GXSetTevColorIn(*stage, 0xF, 8, 9, 0);
        GXSetTevColorOp(*stage, 0, 0, 0, 1, 0);
        GXSetTevAlphaIn(*stage, 7, 7, 7, 0);
        GXSetTevAlphaOp(*stage, 0, 0, 0, 1, 0);
    }
    *stage += 1;
    *coord += 1;
    *map += 1;
    *c1 += 1;
    *c2 += 1;
}

// .text:0x0016943C size:0x164
void fn_3_16943C(void) {
    s32 v;
    s32 i;
    s32 t;
    lbl_3_bss_BA08.frame += (lbl_80366158._28 == 0);
    if ((lbl_3_bss_BA08.frame & 1) == 0) {
        v = lbl_3_bss_BA00.buf[fn_800247E4(0, 0, 4, 4)];
        v += lbl_3_data_2A330 * 2;
        if (v > 0xFF) {
            v = 0xFF;
        } else if (v < 0) {
            v = 0;
        }
        for (i = 0; i < 32; i += 2) {
            lbl_3_bss_BA00.buf[i] = v;
        }
        DCFlushRange(lbl_3_bss_BA00.buf, 4);
        t = v + lbl_3_data_2A330 * 2;
        if (t > 0xFF || t < 0) {
            lbl_3_data_2A330 *= -1;
        }
    }
}

// .text:0x001695A0 size:0x4
void fn_3_1695A0(void) {
}

extern void fn_80011604(s32, void*);

// .text:0x001695A4 size:0x5C
void fn_3_1695A4(s32 a, u8 flag) {
    u8* p = (u8*)&lbl_3_bss_BA00;
    if (flag == 0) {
        ((KinokoCtl*)p)->buf = KINOKO_IMG0(p);
        ((KinokoCtl*)p)->tex = KINOKO_TEX0(p);
    } else {
        ((KinokoCtl*)p)->buf = KINOKO_IMG1(p);
        ((KinokoCtl*)p)->tex = KINOKO_TEX1(p);
    }
    fn_80011604(a, fn_3_16917C);
}

// The ribbon state, the colour table and the two draw nodes. Defined here: the original
// addresses them through one pooled base.
KinokoState lbl_3_data_28928 = { 0 };
u8 lbl_3_data_2A308[6][4] = {
    { 0xFF, 0x00, 0x00, 0xC8 }, { 0xFF, 0xFF, 0x00, 0xC8 }, { 0x00, 0xFF, 0x00, 0xC8 },
    { 0x00, 0xFF, 0xFF, 0xC8 }, { 0x00, 0x00, 0xFF, 0xC8 }, { 0xFF, 0x00, 0xFF, 0xC8 },
};
typedef struct KinokoNode {
    /*0x0*/ uintptr_t link; // (pointer-sized on PC, like DrawLink) set by fn_800A7D4C
    /*0x4*/ void (*draw)(void* node);
} KinokoNode;
KinokoNode lbl_3_data_2A320[2] = {
    { 0, fn_3_169984 },
    { 0, fn_3_169984 },
};
s8 lbl_3_data_2A330 = -1; // ribbon sway direction (+1/-1)
// One ribbon quad (between two segments) for fn_3_169984.
typedef struct {
    struct {
        Vec* pos;
        GXColor* color;
    } vtx[4];
    Vec v; // centre, for the depth sort
    u8 flag;
    u8 pad[3];
} RibEnt;
extern RibEnt lbl_3_bss_BAE0[];
extern void* memcpy(void*, const void*, size_t);
extern void fn_3_16A07C(void);
extern f32 lbl_3_rodata_402C; // -1.0f
extern void* memset(void*, int, size_t);
extern void* fn_800B0A5C_insertQueue(void*, s32);

// .text:0x0016C394 size:0x7C
void fn_3_16C394(s8 a) {
#ifdef TARGET_PC
    // A second mushroom while the ribbon task is still running would add a second fn_3_16A07C
    // task; both link the same draw node (lbl_3_data_2A320[parity]) each frame, which makes the
    // draw list point at itself and the draw thread loop forever (Chain Chomp freeze + FIFO
    // overflow). Restart the effect on the running task instead.
    s32 running = lbl_3_data_28928.enabled != 0;
#endif
    memset(&lbl_3_data_28928, 0, sizeof(lbl_3_data_28928));
    #ifdef TARGET_PC
    memset(lbl_3_bss_BAE0, 0, 149 * sizeof(RibEnt)); // 0x1BF0 = 149 GameCube-sized (0x30) entries
#else
    memset(lbl_3_bss_BAE0, 0, 0x1BF0);
#endif
    lbl_3_data_28928.charId = a;
    lbl_3_data_28928.enabled = 1;
    lbl_3_data_28928.tick = 1;
    fn_3_16B884();
#ifdef TARGET_PC
    if (running) {
        return;
    }
#endif
    fn_800B0A5C_insertQueue(fn_3_16A07C, 0);
}

extern char lbl_3_rodata_4050[];
extern char lbl_3_rodata_405C[];
extern s32 fn_8001B728(s32, s32, void*);
extern void OSPanic(const char*, int, const char*, ...);

// .text:0x0016B488 size:0x12C
void fn_3_16B488(void* out, s8 id) {
    if (out == NULL) {
        OSPanic(lbl_3_rodata_4050, 0x11C, lbl_3_rodata_405C);
    }
    memset(out, 0, 0xC);
    if (fn_8001B728(lbl_3_data_28928.charId, id, out) == 0) {
        switch (id) {
        case 28:
            fn_8001B728(lbl_3_data_28928.charId, 0x1E, out);
            break;
        case 32:
            fn_8001B728(lbl_3_data_28928.charId, 0x22, out);
            break;
        case 7:
            fn_8001B728(lbl_3_data_28928.charId, 5, out);
            break;
        case 18:
            fn_8001B728(lbl_3_data_28928.charId, 0x13, out);
            break;
        case 24:
            fn_8001B728(lbl_3_data_28928.charId, 0x19, out);
            break;
        }
    }
}

// .text:0x00169600 size:0x204
void fn_3_169600(void) {
    u8* base = (u8*)&lbl_3_bss_BA00;
    u32 i;
    u32 j;
    u32 idx;
    u8* p;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            idx = fn_800247E4(j, i, 4, 4);
            if (idx < 0x20) {
                p = KINOKO_IMG0(base);
                p += idx;
                p[2] = 0xFF;
                p[0] = 0xFF;
                p[3] = 0x9B;
                p[1] = 0x9B;
            } else {
                p = KINOKO_IMG0(base);
                p += idx;
                p[2] = 0;
                p[0] = 0;
                p[3] = 0xFF;
                p[1] = 0xFF;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            idx = fn_800247E4(j, i, 4, 4);
            if (idx < 0x20) {
                p = KINOKO_IMG1(base);
                p += idx;
                p[2] = 0xFF;
                p[0] = 0xFF;
                p[3] = 0;
                p[1] = 0;
            } else {
                p = KINOKO_IMG1(base);
                p += idx;
                p[2] = 0x9B;
                p[0] = 0x9B;
                p[3] = 0xFF;
                p[1] = 0xFF;
            }
        }
    }
    GXInitTexObj(KINOKO_TEX0(base), KINOKO_IMG0(base), 4, 4, 6, 1, 1, 0);
    GXInitTexObjLOD(KINOKO_TEX0(base), 1, 1, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    GXInitTexObj(KINOKO_TEX1(base), KINOKO_IMG1(base), 4, 4, 6, 1, 1, 0);
    GXInitTexObjLOD(KINOKO_TEX1(base), 1, 1, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    lbl_3_data_2A330 = -1;
    KINOKO_FRAME(base) = 0;
}

// .text:0x00169804 size:0x180
void fn_3_169804(void) {
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 1, 0);
    GXSetCullMode(2);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorIn(0, 0xF, 0xF, 0xF, 0xA);
    GXSetTevAlphaIn(0, 7, 7, 7, 5);
    GXSetTevOrder(0, 0xFF, 0xFF, 4);
    GXSetTevOp(0, 4);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXLoadPosMtxImm(fn_80052768_getCamera(fn_8005268C())->view, 0);
    GXSetCurrentMtx(0);
    GXSetProjection(fn_80052768_getCamera(fn_8005268C())->proj, 0);
}

// .text:0x00169984 size:0x37C mapped:0x807A8A18
// One entry of the back-to-front sort of the mushroom ribbon quads.
typedef struct RibSortEnt {
    f32 depth;
    u32 idx;
} RibSortEnt;

// Draws the ribbon quads sorted by view-space depth.
// NONMATCHING 97%: loop counters/pointers get different saved registers (r27/r28/r30 rotated)
#if NONMATCHING
void fn_3_169984(void* node) {
    RibSortEnt swap;
    Vec viewPos;
    f32 view[3][4];
    RibSortEnt list[149];
    RibSortEnt* sorted;
    RibSortEnt* front;
    RibSortEnt* back;
    RibSortEnt* a;
    RibSortEnt* b;
    RibEnt* e;
    u32 i;
    u32 j;
    f32 noDepth;

    PSMTXCopy(fn_80052768_getCamera(fn_8005268C())->view, view);
    sorted = list;
    noDepth = lbl_3_rodata_402C;
    e = lbl_3_bss_BAE0;
    back = &list[148];
    front = sorted;
    for (i = 0; i < 149; i++) {
        if (e->flag == 0) {
            back->idx = i;
            back->depth = noDepth;
            back--;
        } else {
            PSMTXMultVec(view, &e->v, &viewPos);
            front->depth = viewPos.z;
            front->idx = i;
            front++;
        }
        e++;
    }
    a = sorted;
    for (i = 0; i < 148; i++) {
        for (j = i + 1, b = &list[j]; j < 149; j++) {
            if (a->depth > b->depth) {
                memcpy(&swap, a, sizeof(RibSortEnt));
                memcpy(a, b, sizeof(RibSortEnt));
                memcpy(b, &swap, sizeof(RibSortEnt));
            }
            b++;
        }
        a++;
    }

    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 1, 0);
    GXSetCullMode(2);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorIn(0, 0xF, 0xF, 0xF, 0xA);
    GXSetTevAlphaIn(0, 7, 7, 7, 5);
    GXSetTevOrder(0, 0xFF, 0xFF, 4);
    GXSetTevOp(0, 4);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXLoadPosMtxImm(fn_80052768_getCamera(fn_8005268C())->view, 0);
    GXSetCurrentMtx(0);
    GXSetProjection(fn_80052768_getCamera(fn_8005268C())->proj, 0);

    for (i = 0; i < 149; i++) {
        e = &lbl_3_bss_BAE0[sorted->idx];
        if (e->flag != 0) {
            GXBegin(0x80, 0, 4);
            {
                f32* q = &e->vtx[0].pos->x;
                f32 z = q[2];
                f32 y = q[1];
                f32 x = q[0];
                GXWGFIFO_F32(x);
                GXWGFIFO_F32(y);
                GXWGFIFO_F32(z);
            }
            GXWGFIFO_U32(*(u32*)e->vtx[0].color);
            {
                f32* q = &e->vtx[1].pos->x;
                f32 z = q[2];
                f32 y = q[1];
                f32 x = q[0];
                GXWGFIFO_F32(x);
                GXWGFIFO_F32(y);
                GXWGFIFO_F32(z);
            }
            GXWGFIFO_U32(*(u32*)e->vtx[1].color);
            {
                f32* q = &e->vtx[2].pos->x;
                f32 z = q[2];
                f32 y = q[1];
                f32 x = q[0];
                GXWGFIFO_F32(x);
                GXWGFIFO_F32(y);
                GXWGFIFO_F32(z);
            }
            GXWGFIFO_U32(*(u32*)e->vtx[2].color);
            {
                f32* q = &e->vtx[3].pos->x;
                f32 z = q[2];
                f32 y = q[1];
                f32 x = q[0];
                GXWGFIFO_F32(x);
                GXWGFIFO_F32(y);
                GXWGFIFO_F32(z);
            }
            GXWGFIFO_U32(*(u32*)e->vtx[3].color);
        }
        sorted++;
    }
}
#endif

// .text:0x00169D00 size:0x170
void fn_3_169D00(KinokoSeg* base, u32* cnt) {
    KinokoSeg* p = &base[24];
    KinokoSeg* q;
    u32 i = 0x18;
    while (i != 0 && *cnt < 0x95) {
        if (p->active != 0) {
            q = &base[i - 1];
            PSVECAdd(&p->pos, &q->pos, &lbl_3_bss_BAE0[*cnt].v);
            PSVECScale(&lbl_3_bss_BAE0[*cnt].v, 0.5f, &lbl_3_bss_BAE0[*cnt].v);
            lbl_3_bss_BAE0[*cnt].vtx[0].pos = &q->edgeA;
            lbl_3_bss_BAE0[*cnt].vtx[0].color = &q->color;
            lbl_3_bss_BAE0[*cnt].vtx[1].pos = &q->edgeB;
            lbl_3_bss_BAE0[*cnt].vtx[1].color = &q->color;
            lbl_3_bss_BAE0[*cnt].vtx[2].pos = &p->edgeB;
            lbl_3_bss_BAE0[*cnt].vtx[2].color = &p->color;
            lbl_3_bss_BAE0[*cnt].vtx[3].pos = &p->edgeA;
            lbl_3_bss_BAE0[*cnt].vtx[3].color = &p->color;
            lbl_3_bss_BAE0[*cnt].flag = 1;
            *cnt += 1;
        }
        p--;
        i--;
    }
}

extern f32 lbl_3_rodata_4028;
extern f32 lbl_3_rodata_402C;
extern f32 lbl_3_rodata_4034;
extern f32 lbl_3_rodata_4038;
extern f32 lbl_3_rodata_403C;

// .text:0x00169E70 size:0x20C
void fn_3_169E70(KinokoSeg* base) {
    Vec a;
    Vec b;
    Vec c;
    Vec d;
    Vec e;
    camera_803c639c_s* cam = fn_80052768_getCamera(0);
    KinokoSeg* p = base;
    u32 i = 0;
    f32 m;
    do {
        if (p->active != 0) {
            a.x = cam->view[2][0];
            a.y = cam->view[2][1];
            a.z = cam->view[2][2];
            m = PSVECMag(&a);
            if (m == lbl_3_rodata_4028) {
                a.x = lbl_3_rodata_4028;
                a.y = lbl_3_rodata_4028;
                a.z = lbl_3_rodata_4034;
            } else {
                PSVECNormalize(&a, &a);
            }
            if (i == 0) {
                memcpy(&b, &p->pos, sizeof(Vec));
            } else {
                memcpy(&b, &base[i - 1].pos, sizeof(Vec));
            }
            if (i == 0x18) {
                memcpy(&c, &p->pos, sizeof(Vec));
            } else {
                memcpy(&c, &base[i + 1].pos, sizeof(Vec));
            }
            PSVECSubtract(&b, &c, &d);
            m = PSVECMag(&d);
            if (m == lbl_3_rodata_4028) {
                d.z = lbl_3_rodata_4028;
                d.y = lbl_3_rodata_4028;
                d.x = lbl_3_rodata_4034;
            }
            PSVECNormalize(&d, &d);
            PSVECCrossProduct(&d, &a, &e);
            m = PSVECMag(&e);
            if (m == lbl_3_rodata_4028) {
                e.z = lbl_3_rodata_4028;
                e.y = lbl_3_rodata_4028;
                e.x = lbl_3_rodata_402C;
            }
            PSVECNormalize(&e, &e);
            PSVECScale(&e, lbl_3_rodata_4038, &p->edgeA);
            PSVECScale(&e, lbl_3_rodata_403C, &p->edgeB);
            PSVECAdd(&p->edgeA, &p->pos, &p->edgeA);
            PSVECAdd(&p->edgeB, &p->pos, &p->edgeB);
        }
        i++;
        p++;
    } while (i < 0x19);
}

// The original inlines fn_3_16B5B4 and copies of fn_3_169D00 into fn_3_16A07C and fn_3_16B884:
// inlining stays on from here to the end of the file (deferred inlining reads the final state).
#pragma dont_inline off
// .text:0x0016A07C size:0x140C mapped:0x807A9110
extern u8 lbl_803CBBC0; // index of the display list buffer in use
extern void fn_800A7D4C(s32 list, void* node);
extern void fn_800B0A14_removeQueue(void*);

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
#define KINOKO_RIBBON(r) (lbl_3_data_28928.ribbon[r])
#define KINOKO_TICK (lbl_3_data_28928.tick)
// Segment i of ribbon r takes segment i - 1's place, faded to `alpha`.
#define KINOKO_TRAIL(r, i, alpha)                                                            \
    do {                                                                                     \
        memcpy(&KINOKO_RIBBON(r)[i], &KINOKO_RIBBON(r)[(i) - 1], sizeof(KinokoSeg));        \
        KINOKO_RIBBON(r)[i].color.a = (alpha);                                               \
    } while (0)

// Advances a ribbon colour index (0..5).
#define KINOKO_NEXT_COLOR(c)      \
    do {                          \
        v = ++(c);                \
        if (v >= 6) {             \
            (c) = v - 6;          \
        }                         \
    } while (0)

// Inline copy of fn_3_169D00 (the original expands it once per ribbon in fn_3_16A07C).
static inline void fn_3_169D00_inline(KinokoSeg* base, u32* cnt) {
    KinokoSeg* p = &base[24];
    KinokoSeg* q;
    u32 i = 0x18;
    while (i != 0 && *cnt < 0x95) {
        if (p->active != 0) {
            q = &base[i - 1];
            PSVECAdd(&p->pos, &q->pos, &lbl_3_bss_BAE0[*cnt].v);
            PSVECScale(&lbl_3_bss_BAE0[*cnt].v, 0.5f, &lbl_3_bss_BAE0[*cnt].v);
            lbl_3_bss_BAE0[*cnt].vtx[0].pos = &q->edgeA;
            lbl_3_bss_BAE0[*cnt].vtx[0].color = &q->color;
            lbl_3_bss_BAE0[*cnt].vtx[1].pos = &q->edgeB;
            lbl_3_bss_BAE0[*cnt].vtx[1].color = &q->color;
            lbl_3_bss_BAE0[*cnt].vtx[2].pos = &p->edgeB;
            lbl_3_bss_BAE0[*cnt].vtx[2].color = &p->color;
            lbl_3_bss_BAE0[*cnt].vtx[3].pos = &p->edgeA;
            lbl_3_bss_BAE0[*cnt].vtx[3].color = &p->color;
            lbl_3_bss_BAE0[*cnt].flag = 1;
            *cnt += 1;
        }
        p--;
        i--;
    }
}

// Per-frame task of the mushroom ribbon effect: trails the ribbon segments,
// cycles their colours, rebuilds the quad list and queues the draw.
// NONMATCHING 97%: register allocation; the original also keeps the ribbon pointers of the
// fn_3_169E70 calls in saved registers and reuses them in the inlined fn_3_169D00 loops.
#if NONMATCHING
void fn_3_16A07C(void) {
    u32 i;
    u32 count;
    u8 alpha;
    u8 v;

    if (g_d_GameSettings._55 != 0 || g_Minigame._1A40 != 0) {
        REMOVE_QUEUE_NOARG(); // removes the running task
        memset(&lbl_3_data_28928, 0, sizeof(lbl_3_data_28928));
        return;
    }
    if (g_Minigame.playerIDWithPowerup[0] == -1 || lbl_3_data_28928.enabled == 0) {
        REMOVE_QUEUE_NOARG();
        memset(&lbl_3_data_28928, 0, sizeof(lbl_3_data_28928));
        return;
    }

    if (lbl_80366158._28 == 0) {
        KINOKO_TICK++;
        // Trail: every segment takes the previous one's place.
        for (i = 24; i != 0; i--) {
            alpha = (24 - i) * 8;
            KINOKO_TRAIL(0, i, alpha);
            KINOKO_TRAIL(1, i, alpha);
            KINOKO_TRAIL(2, i, alpha);
            KINOKO_TRAIL(3, i, alpha);
            KINOKO_TRAIL(4, i, alpha);
            KINOKO_TRAIL(5, i, alpha);
        }
        if (KINOKO_TICK % 5 == 0) {
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(0)[0].colorFrom);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(0)[0].colorTo);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(1)[0].colorFrom);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(1)[0].colorTo);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(2)[0].colorFrom);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(2)[0].colorTo);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(3)[0].colorFrom);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(3)[0].colorTo);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(4)[0].colorFrom);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(4)[0].colorTo);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(5)[0].colorFrom);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(5)[0].colorTo);
        }
        fn_3_16B5B4(KINOKO_RIBBON(0), 0x1C, KINOKO_TICK % 5);
        fn_3_16B5B4(KINOKO_RIBBON(1), 0x20, KINOKO_TICK % 5);
        fn_3_16B5B4(KINOKO_RIBBON(2), 4, KINOKO_TICK % 5);
        fn_3_16B5B4(KINOKO_RIBBON(3), 7, KINOKO_TICK % 5);
        fn_3_16B5B4(KINOKO_RIBBON(4), 0x12, KINOKO_TICK % 5);
        fn_3_16B5B4(KINOKO_RIBBON(5), 0x18, KINOKO_TICK % 5);
    }

    fn_3_169E70(KINOKO_RIBBON(0));
    fn_3_169E70(KINOKO_RIBBON(1));
    fn_3_169E70(KINOKO_RIBBON(2));
    fn_3_169E70(KINOKO_RIBBON(3));
    fn_3_169E70(KINOKO_RIBBON(4));
    fn_3_169E70(KINOKO_RIBBON(5));
    count = 0;
    #ifdef TARGET_PC
    memset(lbl_3_bss_BAE0, 0, 149 * sizeof(RibEnt)); // 0x1BF0 = 149 GameCube-sized (0x30) entries
#else
    memset(lbl_3_bss_BAE0, 0, 0x1BF0);
#endif
    fn_3_169D00_inline(KINOKO_RIBBON(0), &count);
    fn_3_169D00_inline(KINOKO_RIBBON(1), &count);
    fn_3_169D00_inline(KINOKO_RIBBON(2), &count);
    fn_3_169D00_inline(KINOKO_RIBBON(3), &count);
    fn_3_169D00_inline(KINOKO_RIBBON(4), &count);
    fn_3_169D00_inline(KINOKO_RIBBON(5), &count);
    fn_800A7D4C(1, &lbl_3_data_2A320[lbl_803CBBC0]);
}
#endif

extern const f32 lbl_3_rodata_4040;
extern const f64 lbl_3_rodata_4048;

// .text:0x0016B5B4 size:0x2D0 mapped:0x807AA648
void fn_3_16B5B4(KinokoSeg* out, s8 id, int t) {
    f64 k1;
    f32 k = (f32)t / lbl_3_rodata_4040;
    k1 = lbl_3_rodata_4048 - k;
    out->color.r = k1 * lbl_3_data_2A308[out->colorFrom][0] + k * lbl_3_data_2A308[out->colorTo][0];
    out->color.g = k1 * lbl_3_data_2A308[out->colorFrom][1] + k * lbl_3_data_2A308[out->colorTo][1];
    out->color.b = k1 * lbl_3_data_2A308[out->colorFrom][2] + k * lbl_3_data_2A308[out->colorTo][2];
    out->color.a = k1 * lbl_3_data_2A308[out->colorFrom][3] + k * lbl_3_data_2A308[out->colorTo][3];
    out->active = 1;
    if (out == NULL) {
        OSPanic(lbl_3_rodata_4050, 0x11C, lbl_3_rodata_405C);
    }
    memset(&out->pos, 0, sizeof(Vec));
    if (fn_8001B728(lbl_3_data_28928.charId, id, &out->pos) == 0) {
        switch (id) {
        case 28:
            fn_8001B728(lbl_3_data_28928.charId, 0x1E, out);
            break;
        case 32:
            fn_8001B728(lbl_3_data_28928.charId, 0x22, out);
            break;
        case 7:
            fn_8001B728(lbl_3_data_28928.charId, 5, out);
            break;
        case 18:
            fn_8001B728(lbl_3_data_28928.charId, 0x13, out);
            break;
        case 24:
            fn_8001B728(lbl_3_data_28928.charId, 0x19, out);
            break;
        }
    }
}

// Inline copy of fn_3_16B5B4 for fn_3_16B884 (the original inlines it there with t = 0; the 5.0f
// literal lets k fold to a 0.0f constant).
static inline void fn_3_16B5B4_inline(KinokoSeg* out, s8 id, int t) {
    f64 k1;
    f32 k = (f32)t / 5.0f;
    k1 = lbl_3_rodata_4048 - k;
    out->color.r = k1 * lbl_3_data_2A308[out->colorFrom][0] + k * lbl_3_data_2A308[out->colorTo][0];
    out->color.g = k1 * lbl_3_data_2A308[out->colorFrom][1] + k * lbl_3_data_2A308[out->colorTo][1];
    out->color.b = k1 * lbl_3_data_2A308[out->colorFrom][2] + k * lbl_3_data_2A308[out->colorTo][2];
    out->color.a = k1 * lbl_3_data_2A308[out->colorFrom][3] + k * lbl_3_data_2A308[out->colorTo][3];
    out->active = 1;
    if (out == NULL) {
        OSPanic(lbl_3_rodata_4050, 0x11C, lbl_3_rodata_405C);
    }
    memset(&out->pos, 0, sizeof(Vec));
    if (fn_8001B728(lbl_3_data_28928.charId, id, &out->pos) == 0) {
        switch (id) {
        case 28:
            fn_8001B728(lbl_3_data_28928.charId, 0x1E, out);
            break;
        case 32:
            fn_8001B728(lbl_3_data_28928.charId, 0x22, out);
            break;
        case 7:
            fn_8001B728(lbl_3_data_28928.charId, 5, out);
            break;
        case 18:
            fn_8001B728(lbl_3_data_28928.charId, 0x13, out);
            break;
        case 24:
            fn_8001B728(lbl_3_data_28928.charId, 0x19, out);
            break;
        }
    }
}

// .text:0x0016B884 size:0xB10 mapped:0x807AA918
// Resets the six mushroom ribbons (25 KinokoSeg each).
// NONMATCHING 72%: the original computes 1.0 - k once (f31) for all six inlined copies and re-reads
// the stored from/to indices with clrlslwi; register allocation differs throughout.
#if NONMATCHING
void fn_3_16B884(void) {
    u32 i;
    u8 alpha;

    KINOKO_RIBBON(0)[0].colorFrom = 0;
    KINOKO_RIBBON(0)[0].colorTo = 1;
    fn_3_16B5B4_inline(KINOKO_RIBBON(0), 0x1C, 0);
    KINOKO_RIBBON(1)[0].colorFrom = 1;
    KINOKO_RIBBON(1)[0].colorTo = 2;
    fn_3_16B5B4_inline(KINOKO_RIBBON(1), 0x20, 0);
    KINOKO_RIBBON(2)[0].colorFrom = 2;
    KINOKO_RIBBON(2)[0].colorTo = 3;
    fn_3_16B5B4_inline(KINOKO_RIBBON(2), 4, 0);
    KINOKO_RIBBON(3)[0].colorFrom = 3;
    KINOKO_RIBBON(3)[0].colorTo = 4;
    fn_3_16B5B4_inline(KINOKO_RIBBON(3), 7, 0);
    KINOKO_RIBBON(4)[0].colorFrom = 4;
    KINOKO_RIBBON(4)[0].colorTo = 5;
    fn_3_16B5B4_inline(KINOKO_RIBBON(4), 0x12, 0);
    KINOKO_RIBBON(5)[0].colorFrom = 5;
    KINOKO_RIBBON(5)[0].colorTo = 0;
    fn_3_16B5B4_inline(KINOKO_RIBBON(5), 0x18, 0);

    for (i = 1; i < 25; i++) {
        alpha = (24 - i) * 8;
        KINOKO_TRAIL(0, i, alpha);
        KINOKO_TRAIL(1, i, alpha);
        KINOKO_TRAIL(2, i, alpha);
        KINOKO_TRAIL(3, i, alpha);
        KINOKO_TRAIL(4, i, alpha);
        KINOKO_TRAIL(5, i, alpha);
    }
}
#endif

