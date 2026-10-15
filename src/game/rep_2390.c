#include "game/rep_2390.h"
#define REP_HEADER_FN repHeader_2390
#include "header_rep_inline.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/mtx.h"
#include "main/file_800263FC.h"
#include "main/file_80011640.h"
#include "main/file_80008E00.h" // lbl_80366158

extern Rep2390Bss35154 lbl_3_common_bss_35154;
extern u16 lbl_3_data_6660[];

// .data lbl_3_data_17DC0..18268: separate statics reached through one pooled base.
// Ball particle effects, three per ball state (pitch, hit, live ball, and a fourth set).
static ParticleParams5 lbl_3_data_17DC0[12] = {
    {NULL, 21, 5, 280000, 0, 0, 4, 2, 120000, 90000, 0, 128, 1000000, 1000000, -500000, 500000, 0xFFFFFF00, 0, -28000, 1},
    {NULL, 7, 10, 78000, 60000, 50000, 12, 6, 109000, 101000, 0, 40, 4500000, 9500000, -1000000, 4500000, 0xFFFFFF00, 0, 0, 0},
    {NULL, 4, 3, 90000, 100000, 10000, 20, 10, 103000, 105999, 0, 60, 10000000, 18000000, 1000000, -1000000, 0x3C3C3C00, 0, 0, 0},
    {NULL, 21, 5, 280000, 0, 0, 4, 2, 120000, 90000, 0, 128, 500000, 1000000, -500000, 500000, 0xFFFFFF00, 0, -28000, 1},
    {NULL, 7, 10, 78000, 60000, 50000, 12, 6, 109000, 101000, 0, 40, 4500000, 9500000, -1000000, 4500000, 0xFFFFFF00, 0, 0, 0},
    {NULL, 4, 3, 90000, 100000, 10000, 20, 10, 103000, 105999, 0, 60, 10000000, 18000000, 1000000, -1000000, 0x3C3C3C00, 0, 0, 0},
    {NULL, 21, 5, 350000, 0, 0, 4, 2, 120000, 90000, 0, 60, 500000, 1000000, -500000, 500000, 0xFFFFFF00, 0, -50000, 1},
    {NULL, 7, 10, 70000, 80000, 50000, 20, 10, 109000, 110000, 0, 40, 4500000, 9000000, -4500000, 4500000, 0xFFFFFF00, 0, 0, 0},
    {NULL, 4, 5, 90000, 100000, 10000, 20, 10, 103000, 105999, 0, 60, 10000000, 18000000, 4500000, -4500000, 0x3C3C3C00, 0, 0, 0},
    {NULL, 21, 3, 140000, 0, 0, 16, 2, 120000, 90000, 0, 128, 1000000, 1000000, -500000, 500000, 0xFFFFFF00, 0, -28000, 1},
    {NULL, 7, 10, 39000, 30000, 50000, 12, 6, 109000, 101000, 0, 40, 4500000, 9500000, -1000000, 4500000, 0xFFFFFF00, 0, 0, 0},
    {NULL, 4, 3, 45000, 50000, 10000, 20, 10, 103000, 105999, 0, 60, 10000000, 18000000, 1000000, -1000000, 0x3C3C3C00, 0, 0, 0},
};
// Trail parameters (ParticleParams8 with 8 texture indices), one per ball state.
#ifdef PORT_LP64
// ParticleParams8 is 8-byte aligned on LP64 (tex pointer), so it has 4 bytes
// of tail padding after texIndex2[0] (0x28): a wrapper's extra indices would
// start at 0x30 while fn_8002F5F4 reads texIndex2[1..7] from 0x2C. Spell the
// whole parameter block out with the 8 indices contiguous (same prefix).
typedef struct {
    TexArchive* tex;
    s32 texIndex;
    s32 count;
    s32 taper;
    s32 sizeMax;
    s32 sizeMin;
    s32 length;
    s32 offset;
    u32 gray;
    s32 texIndex2[8];
} ParticleParams8x8;
#define P8X8_PARAMS(f) ((ParticleParams8*)(f))
static ParticleParams8x8 lbl_3_data_18180[3] = {
    {NULL, 20, 8, 7, 250000, 50000, 550000, 0, 0, {12, 13, 14, 15, 16, 17, 18, 19}},
    {NULL, 20, 8, 7, 250000, 50000, 550000, 0, 0, {12, 13, 14, 15, 16, 17, 18, 19}},
    {NULL, 20, 8, 7, 300000, 100000, 550000, 0, 0, {12, 13, 14, 15, 16, 17, 18, 19}},
};
#else
typedef struct {
    ParticleParams8 p;
    s32 texIndex2[7];
} ParticleParams8x8;
#define P8X8_PARAMS(f) (&(f)->p)
static ParticleParams8x8 lbl_3_data_18180[3] = {
    {{NULL, 20, 8, 7, 250000, 50000, 550000, 0, 0, {12}}, {13, 14, 15, 16, 17, 18, 19}},
    {{NULL, 20, 8, 7, 250000, 50000, 550000, 0, 0, {12}}, {13, 14, 15, 16, 17, 18, 19}},
    {{NULL, 20, 8, 7, 300000, 100000, 550000, 0, 0, {12}}, {13, 14, 15, 16, 17, 18, 19}},
};
#endif
static Vec lbl_3_data_1824C = {0.0f, 0.0f, 1.0f};  // emit direction
static Vec lbl_3_data_18258 = {0.0f, 0.0f, -0.2f}; // offset from the animation point
// lbl_3_data_18264: 4 zero bytes (padding)

// .text:0x000CB3AC size:0x18C mapped:0x8070A440
void fn_3_CB3AC(void) {
    Vec sp8;
    CharActor* q = lbl_8036E548.active[0];
    ParticleParams5* p10;
    ParticleParams5* p11;
    ParticleParams5* p9;
    u16* t;
    s32 i;
    u16 anim;
    if (PSVECMag(&lbl_3_data_1824C) && q != 0) {
        lbl_3_data_17DC0[11].tex = lbl_3_common_bss_35154.tex;
        lbl_3_data_17DC0[10].tex = lbl_3_common_bss_35154.tex;
        lbl_3_data_17DC0[9].tex = lbl_3_common_bss_35154.tex;
        lbl_3_data_17DC0[9].texIndex = 0x15;
        lbl_3_data_17DC0[10].texIndex = 7;
        p10 = &lbl_3_data_17DC0[10];
        p11 = &lbl_3_data_17DC0[11];
        p9 = &lbl_3_data_17DC0[9];
        anim = 0x1A;
        if (q->_25A != 0) {
            i = 0;
            t = lbl_3_data_6660;
            do {
                if (t[0] == 0x1A) {
                    anim = lbl_3_data_6660[i * 2 + 1];
                    break;
                }
                if (t[1] == 0x1A) {
                    anim = lbl_3_data_6660[i * 2];
                    break;
                }
                t += 2;
            } while (lbl_3_data_6660[++i * 2] != 0xFFFF);
        }
        getAnimRelatedCoordinates(0, anim, &sp8);
        PSVECAdd(&sp8, &lbl_3_data_18258, &sp8);
        if (lbl_80366158._28 == 0) {
            fn_80030D88(&sp8, &lbl_3_data_1824C, p10, 5);
            fn_80030D88(&sp8, &lbl_3_data_1824C, p11, 5);
            fn_80030470(&sp8, &lbl_3_data_1824C, &lbl_3_data_1824C, p9, 5);
        }
    }
}


// .text:0x000CB538 size:0x17C mapped:0x8070A5CC
// WIP: orig has mode in r28 and k/loop counter in r29 (we swap them); stwx vs add+stw for the 0x44-stride store; decl-order permutations of k/j/e/r28 tried.
void fn_3_CB538(s32 mode) {
    Vec d;
    Vec bv;
    Vec* p31;
    Vec* p30;
    s32 j;
    s32 k;
    ParticleParams5* e;
    ParticleParams5* r28;
    TexArchive* v;
    ParticleParams8x8* f;
    if (g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        k = 2;
    } else {
        k = g_Ball.framesSinceHit > 0;
    }
    p30 = &lbl_3_common_bss_35154.ballPos[1];
    p31 = &lbl_3_common_bss_35154.ballPos[0];
    PSVECSubtract(p30, p31, &d);
    if (PSVECMag(&d)) {
        e = &lbl_3_data_17DC0[k * 3];
        v = lbl_3_common_bss_35154.tex;
        e[2].tex = v;
        e[1].tex = v;
        f = &lbl_3_data_18180[k];
        P8X8_PARAMS(f)->tex = v;
        e[0].tex = v;
        if (mode == 2) {
            e[0].texIndex = 0x1B;
            e[1].texIndex = 0x1C;
        } else {
            e[0].texIndex = 0x15;
            e[1].texIndex = 7;
        }
        fn_8002F5F4(p31, &d, P8X8_PARAMS(f));
        if (lbl_80366158._28 == 0) {
            r28 = e + 1;
            j = 1;
            do {
                fn_80030D88(p31, &d, r28, 5);
                j++;
                r28++;
            } while (j < 3);
            PSVECNormalize(&d, &d);
            PSVECSubtract(p31, p30, &bv);
            fn_80030470(p31, &d, &bv, e, 5);
        }
    }
}
