#include "game/rep_3310.h"
#include "main/SpaniDesc.h"
#include "Unknown/File_0x800a64e0.h"
#include "game/rep_1D58.h"
#include "game/rep_1C0.h"
#define REP_HEADER_FN repHeader_3310
#include "header_rep_inline.h"
#include "C3/geoPalette.h"
#include "C3/anim.h"
#include "Dolphin/GX.h"
#include "static/Camera.h"
#include "game/UnknownHomes_Game.h"
#include "static/GameSettings.h"
#include "game/auto_00_0011D3AC_text.h"
#include "main/file_80008E00.h"
#include "main/file_80069BDC.h"
#include "main/file_8000F150.h"
#include "main/file_80024D2C.h"
#include "main/file_800527C4.h"
extern MinigameAssets lbl_3_common_bss_32724;

extern Rep3310CharMgr lbl_8036E548;

extern f32 lbl_3_data_2262C;
extern f32 lbl_3_data_22650[];
extern u8 lbl_3_data_22670[];
extern const f32 lbl_3_rodata_33AC;
extern const f32 lbl_3_rodata_33B0;
extern f32 lbl_3_data_21A64[];
struct TexArchive;
extern void fn_80033B58(struct TexArchive* arc, s32 idx, GXTexWrapMode wrapS, GXTexWrapMode wrapT);
extern s32 fn_8005268C(void);
extern camera_803c639c_s* fn_80052768_getCamera(int index);

// The unit's .data (0x225F0-0x226E0). Defined here: the original reaches these through one pooled
// base. Address order (initialized data keeps declaration order).
AssetLoadInstructions lbl_3_data_225F0[3] = { // ARAM load records (auto_00_0011D3AC reads [1])
    {1035, {0x40001640}, {0x8EB4800}, 3128},
    {1035, {0x400B2D00}, {0x8EB5800}, 436552},
    {0, {1670}, {0x8F20800}, 1672},
};
f32 lbl_3_data_22620[3] = { 0.0f, -0.15f, 18.5f };
f32 lbl_3_data_2262C = 0.45f;
u8 lbl_3_data_22630[4] = { 0, 1, 3, 2 };
u8 lbl_3_data_22634[4] = { 0x0F, 0x0F, 0x0F, 0x0F };
u8 lbl_3_data_22638[4] = { 2, 0, 3, 1 };
u8 lbl_3_data_2263C[2] = { 0, 1 };
u8 lbl_3_data_2263E = 2;
u8 lbl_3_data_2263F = 6;
f32 lbl_3_data_22640[4] = { 0.75f, 0.05f, 3.0f, 0.02f };
f32 lbl_3_data_22650[3] = { 5.0f, 5.0f, 10.0f };
Rep3310BallCfg lbl_3_data_2265C = { { 1, 0, 2, 3 }, 2.0f, 8.0f, 1.0f, 60 };
u8 lbl_3_data_22670[8] = { 2, 0, 3, 4, 1, 0, 0, 0 };
f32 lbl_3_data_22678[4] = { 2.0f, 2.5f, 1.0f, 1.0f };
f32 lbl_3_data_22688[3] = { 0.5f, 0.0f, -0.5f };
f32 lbl_3_data_22694[6] = { 0.5f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f };
s16 lbl_3_data_226AC[8] = { 0, 0, 0x14, 0xA, 0, 0, 0xF50, 0 };
u8 lbl_3_data_226BC[8] = { 3, 1, 4, 2, 0, 0, 0, 0 };
f32 lbl_3_data_226C4[4] = { 1.5f, 0.7f, 1.0f, 0.5f };
f32 lbl_3_data_226D4[2] = { 1.0f, 30.0f };
f32 lbl_3_data_226DC = 4.0f;
extern f64 acos(f64);
extern f64 sin(f64);
extern f64 cos(f64);
extern void* memcpy(void* dst, const void* src, size_t n);
extern s16 lbl_3_data_217A4[];
extern u32 fn_3_90064(s32 id);
extern f32 lbl_3_data_21A48[];
extern void fn_8001D0D0(int, f32);
extern f32 shortAngleToRad(s16 ang);
extern void minigamesSetSomePointers(void);
extern void minigamesGXStuff(void);
extern void minigamesSetSomePointers2(void);
extern void fn_80035B50(int);
extern void fn_80018B38(void);
extern void fn_3_909B0(void);
extern void fn_3_9081C(void);
extern void fn_800BD548(ActorObject* obj, u8 numLights, ...);
extern void fn_80034E20(void*, void*);
extern SpaniDesc lbl_3_data_69D0[];
extern void fn_80034CEC(void*);
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
extern void* _OSAllocFromHeap(int, int);


// .text:0x00116840 size:0x190 mapped:0x807558D4
// Places the 3 runners (sprites 0x82..0x84); a runner that just started (state 0x1C == 1)
// gets its idle animation.
void fn_3_116840(void) {
    Rep3310Sprite* e;
    Rep3310Racer* g;
    s32 i;
    for (i = 0; i < 3; i++) {
        g = &MG3310.racers[i];
        e = &lbl_8036E548.sprites[i + 0x82];
        e->visible = 0;
        if (g->state != 0) {
            e->visible = 1;
            e->pos[0] = g->pos.x;
            e->pos[1] = -g->pos.y;
            e->pos[2] = g->pos.z;
            fn_8001D0D0(i + 0x82, lbl_3_data_22678[g->_2B]);
            e->rot[1] = lbl_3_data_22688[i];
            e->draw = fn_3_11897C;
            if (g->_1C == 1) {
                fn_3_1189C8(i, 0, 0, 6, 1);
                g->_1C += 1;
            }
        }
    }
}

// .text:0x001169D0 size:0x168 mapped:0x80755A64
void fn_3_1169D0(void) {
    s32 i;
    lbl_8036E548.sprites[0xFB].visible = 0;
    for (i = 0; i < 7; i++) {
        lbl_8036E548.sprites[0xE6 + i].visible = 0;
        lbl_8036E548.sprites[0xED + i].visible = 0;
        lbl_8036E548.sprites[0xF4 + i].visible = 0;
        lbl_8036E548.sprites[0xFC + i].visible = 0;
        lbl_8036E548.sprites[0x103 + i].visible = 0;
        lbl_8036E548.sprites[0x10A + i].visible = 0;
    }
}

// .text:0x00116B38 size:0x3C mapped:0x80755BCC
extern f32 fn_800B4A94(void* p);

void fn_3_116B38(void) {
    s32 i = 2;
    if (g_Minigame.GameMode_MiniGame == 3) {
        i = 0x1F;
    }
    ((Rep3310Sprite*)lbl_8036E548.sprites)[i].visible = 0; // the cast is needed to match
}

// .text:0x00116B74 size:0x8A8 mapped:0x80755C08
// NONMATCHING 98%: register allocation (measured with the NONMATCHING per-mode helpers enabled, which the
// original inlines)
#if NONMATCHING
extern void fn_8001D110(s32 i, f32 a, f32 b, f32 c);
extern u8 lbl_3_data_21BC4[];
extern f32 lbl_3_data_226C4[];
static inline void hideSprites_116B74(void) {
    u32 i;
    Rep3310Sprite* e;
    for (i = 0; i < 40; i++) {
        e = &lbl_8036E548.sprites[i];
        e->visible = 0;
        e->draw = NULL;
    }
}
// Per-frame sprite placement for the current minigame (g_Minigame[0x1A2A]).
void fn_3_116B74(void) {
    Rep3310Sprite* e;
    f32* v;
    s32 i;

    switch (g_Minigame.GameMode_MiniGame) {
    case 1:
        fn_3_116B38();
        break;
    case 2:
        fn_3_1169D0();
        break;
    case 3:
        fn_3_116B38();
        fn_3_119F6C();
        break;
    case 4:
        fn_3_119934();
        fn_3_117494();
        break;
    case 6:
        fn_3_118164();
        fn_3_117FC8();
        hideSprites_116B74();
        fn_3_1179EC();
        fn_3_117494();
        break;
    case 5:
        fn_3_1194FC();
        fn_3_116840();
        hideSprites_116B74();
        for (i = 0; i < 7; i++) {
            e = &lbl_8036E548.sprites[i + 0xE9];
            e->visible = 0;
            if (i >= 4) {
                v = (f32*)(lbl_3_data_21BC4 + i * 0x30 - 0xC0);
                e->visible = 1;
                e->pos[0] = v[0];
                e->pos[1] = -v[1];
                e->pos[2] = v[2];
                fn_8001D110(i + 0xE9, lbl_3_data_226C4[0], lbl_3_data_226C4[1], lbl_3_data_226C4[0]);
                e->draw = fn_3_11881C;
            }
        }
        lbl_8036E548.sprites[0xF0].visible = 0;
        lbl_8036E548.sprites[0xF1].visible = 0;
        lbl_8036E548.sprites[0xF2].visible = 0;
        lbl_8036E548.sprites[0xF3].visible = 0;
        break;
    }
}
#endif

// .text:0x0011741C size:0x78 mapped:0x807564B0
void fn_3_11741C(s32 i) {
    GameActor* t = lbl_8036E548.objs->objects[i].actor;
    s32 k;
    s32 v = g_Minigame._CCE[0] == 1 ? 0 : 2;
    for (k = 0; k < t->totalBones; k++) {
        PTR32_GET(DOTexBank, t->boneArray[k]->dispObj->textureData->texturePalette)->tex[0].texIndex = v;
    }
}

// .text:0x00117494 size:0xF4 mapped:0x80756528
extern const f32 lbl_3_rodata_33C0;
extern const f32 lbl_3_rodata_33C4;
extern const f32 lbl_3_rodata_33C8;

void fn_3_117494(void) {
    MiniGameStruct* g = &g_Minigame;
    Rep3310Sprite* p = lbl_8036E548.sprites;
    p[237].visible = 0;
    p[101].visible = 0;
    p[237].draw = NULL;
    if (g->_CCE[0] != 0 && (g->_CCC > 0x3C || g->_CCC % 2 != 0)) {
        p[237].visible = 1;
        p[237].draw = fn_3_11741C;
        p[237].pos[0] = g->_CB0;
        p[237].pos[1] = -g->_CB4;
        p[237].pos[2] = g->_CB8;
        fn_8001D0D0(0xED, lbl_3_rodata_33C0);
        p[101].visible = 1;
        p[101].pos[0] = g->_CB0;
        p[101].pos[1] = lbl_3_rodata_33C4;
        p[101].pos[2] = g->_CB8;
        fn_8001D0D0(0x65, lbl_3_rodata_33C8);
    }
}

// .text:0x00117588 size:0x464 mapped:0x8075661C
// NONMATCHING 92%: (measured with the rodata externs) scheduling/register order of the quad corner math
#pragma pool_data off // each float constant is its own .rodata symbol in the original
#if NONMATCHING
// Draws the ground shadow quad under sprite idx (0xE9..0xEC), shrinking it with height,
// then picks the actor's texture from its state byte.
void fn_3_117588(s32 idx) {
    f32 uv[4][2] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
    Vec quad[4];
    GXColor color;
    Rep3310Sprite* e = &lbl_8036E548.sprites[idx];
    Rep3310Bouncer* state = &MG3310.c.bouncers[idx - 0xE9];
    GameActor* actor;
    f32 size = 2.5f * (1.0f - (-e->pos[1] * 0.5f) / lbl_3_data_21A64[0]);
    f32 hw;
    f32 hd;
    s32 k;
    u16 tex;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);

    hw = 2.8f * size * 0.5f;
    hd = 2.5f * size * 0.5f;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 0x9B;
    quad[0].x = -hw + e->pos[0];
    quad[0].y = -0.060000002f;
    quad[0].z = hd + e->pos[2];
    quad[1].x = hw + e->pos[0];
    quad[1].y = -0.060000002f;
    quad[1].z = hd + e->pos[2];
    quad[2].x = hw + e->pos[0];
    quad[2].y = -0.060000002f;
    quad[2].z = -hd + e->pos[2];
    quad[3].x = -hw + e->pos[0];
    quad[3].y = -0.060000002f;
    quad[3].z = -hd + e->pos[2];

    GXLoadPosMtxImm(fn_80052768_getCamera(fn_8005268C())->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetProjection(fn_80052768_getCamera(fn_8005268C())->proj, GX_PERSPECTIVE);
    fn_80033B58(MG_ASSETS.textures[2], 0x13, GX_CLAMP, GX_CLAMP);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (k = 0; k < 4; k++) {
        GXPosition3f32(quad[k].x, quad[k].y, quad[k].z);
        GXColor1u32(*(u32*)&color);
        GXTexCoord2f32(uv[k][0], uv[k][1]);
    }

    actor = lbl_8036E548.objs->objects[idx].actor;
    if (state->state == 1 || state->state == 5) {
        tex = 0;
    } else {
        tex = 1;
    }
    for (k = 0; k < actor->totalBones; k++) {
        PTR32_GET(DOTexBank, actor->boneArray[k]->dispObj->textureData->texturePalette)->tex[0].texIndex = tex;
    }
}
#endif
#pragma pool_data reset

// .text:0x001179EC size:0xF8 mapped:0x80756A80
extern const f32 lbl_3_rodata_33DC;

void fn_3_1179EC(void) {
    Rep3310Sprite* e;
    f32* v;
    u32 i;
    for (i = 0; i < 4; i++) {
        e = &lbl_8036E548.sprites[(i + 0xE9)];
        v = MG3310.c.bouncers[i].f;
        e->visible = 0;
        e->draw = NULL;
        if (MG3310.c.bouncers[i].state != 0) {
            e->visible = 1;
            e->pos[0] = v[0];
            e->pos[1] = -v[1];
            e->pos[2] = v[2];
            e->rot[0] = lbl_3_rodata_33DC * v[6];
            e->rot[1] = lbl_3_rodata_33DC * v[7];
            e->rot[2] = lbl_3_rodata_33DC * v[8];
            fn_8001D0D0(i + 0xE9, lbl_3_rodata_33C0);
            e->draw = fn_3_117588;
        }
    }
}

// .text:0x00117AE4 size:0x94 mapped:0x80756B78
void fn_3_117AE4(void) {
    Rep3310Sprite* p = lbl_8036E548.sprites;
    f32 z = 0.0f;
    p[231].visible = 1;
    p[231].pos[0] = lbl_3_data_21A48[0];
    p[231].pos[2] = lbl_3_data_21A48[2];
    p[231].pos[1] = z;
    p[231].rot[0] = z;
    p[231].rot[2] = z;
    p[231].rot[1] = shortAngleToRad(0x1000 - g_Minigame._1D64);
    fn_8001D0D0(0xE7, 3.0f);
}

// .text:0x00117B78 size:0x450 mapped:0x80756C0C
// NONMATCHING 92%: (measured with the rodata externs) the original builds -1.5 with fneg and schedules the rotation math differently
// litcheck: -1.5 (the original negates its 1.5f with fneg)
#if NONMATCHING
// Draws the square ground marker under sprite idx, rotated by its yaw (rot[1]).
void fn_3_117B78(s32 idx) {
    f32 uv[4][2] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
    Vec quad[4];
    Vec tmp;
    GXColor color;
    Rep3310Sprite* e = &lbl_8036E548.sprites[idx];
    u32 k;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);

    quad[0].x = -1.5f;
    quad[0].z = 1.5f;
    quad[1].x = 1.5f;
    quad[1].z = 1.5f;
    quad[2].x = 1.5f;
    quad[2].z = -1.5f;
    quad[3].x = -1.5f;
    quad[3].z = -1.5f;
    for (k = 0; k < 4; k++) {
        f32 s;
        f32 c;
        memcpy(&tmp, &quad[k], sizeof(Vec));
        s = sin(-e->rot[1]);
        quad[k].x = tmp.x * (f32)cos(-e->rot[1]) + tmp.z * -s;
        c = cos(-e->rot[1]);
        quad[k].z = tmp.x * (f32)sin(-e->rot[1]) + tmp.z * c;
    }
    for (k = 0; k < 4; k++) {
        quad[k].x += e->pos[0];
        quad[k].y = -0.060000002f;
        quad[k].z += e->pos[2];
    }
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 0x9B;

    GXLoadPosMtxImm(fn_80052768_getCamera(fn_8005268C())->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetProjection(fn_80052768_getCamera(fn_8005268C())->proj, GX_PERSPECTIVE);
    fn_80033B58(MG_ASSETS.textures[2], 0x14, GX_CLAMP, GX_CLAMP);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (k = 0; k < 4; k++) {
        GXPosition3f32(quad[k].x, quad[k].y, quad[k].z);
        GXColor1u32(*(u32*)&color);
        GXTexCoord2f32(uv[k][0], uv[k][1]);
    }
}
#endif

// .text:0x00117FC8 size:0xDC mapped:0x8075705C
extern const f32 lbl_3_rodata_33CC;
extern const f32 lbl_3_rodata_33D0;
extern const f32 lbl_3_rodata_33D4;
extern const f32 lbl_3_rodata_33D8;
extern f32 RandomF32_Game_Range(f32 a, f32 b);
extern f32 fn_3_9FEA8(f32 v);

void fn_3_117FC8(void) {
    Rep3310Sprite* p = lbl_8036E548.sprites;
    p[232].visible = 0;
    lbl_8036E548.sprites[0x65].visible = 0;
    if (g_Minigame._72A != 0) {
        p[232].visible = 1;
        p[232].pos[0] = g_Minigame._6E8;
        p[232].pos[1] = -g_Minigame._6EC;
        p[232].pos[2] = g_Minigame._6F0;
        fn_8001D0D0(0xE8, lbl_3_rodata_33CC);
        if (g_Minigame._724 == 0) {
            p[232].rot[1] = RandomF32_Game_Range(lbl_3_rodata_33D0, lbl_3_rodata_33D4);
        } else {
            p[232].rot[1] = fn_3_9FEA8(lbl_3_rodata_33D8 + p[232].rot[1]);
        }
        p[232].draw = fn_3_117B78;
    }
}

// .text:0x001180A4 size:0xC0 mapped:0x80757138
extern const f32 lbl_3_rodata_33AC;
extern const f32 lbl_3_rodata_33C4;
extern const f32 lbl_3_rodata_33F4;

void fn_3_1180A4(void) {
    Rep3310Sprite* p = lbl_8036E548.sprites;
    p[100].visible = 0;
    p[230].visible = 0;
    if (g_Minigame._B6C._40[0] == 1) {
        p[230].visible = 1;
        p[230].pos[0] = g_Minigame._B6C._0.x;
        p[230].pos[1] = -g_Minigame._B6C._0.y;
        p[230].pos[2] = g_Minigame._B6C._0.z;
        p[230].rot[0] = lbl_3_rodata_33AC;
        p[230].rot[1] = lbl_3_rodata_33AC;
        p[230].rot[2] = lbl_3_rodata_33AC;
        p[100].visible = 1;
        p[100].draw = NULL;
        p[100].pos[0] = g_Minigame._B6C._0.x;
        p[100].pos[1] = lbl_3_rodata_33C4;
        p[100].pos[2] = g_Minigame._B6C._0.z;
        fn_8001D0D0(0x64, lbl_3_rodata_33F4);
    }
}

// .text:0x00118164 size:0x1F4 mapped:0x807571F8
extern const f32 lbl_3_rodata_33F8;
extern const f32 lbl_3_rodata_33FC;
extern const f32 lbl_3_rodata_3400;
extern s16 lbl_3_data_21A04[];
void fn_3_118164(void) {
    Rep3310Sprite* e1;
    Rep3310Sprite* e2;
    s32 i;
    s32 j;
    for (i = 0; i < 0x64; i++) {
        j = i + 0x82;
        e1 = &lbl_8036E548.sprites[j];
        e1->visible = 0;
        e2 = &lbl_8036E548.sprites[i];
        e2->visible = 0;
        if (g_Minigame.wallBall_coinsVisibleInd[i] == 1 || g_Minigame.wallBall_coinsVisibleInd[i] == 3) {
            e1->visible = 1;
            e1->pos[0] = g_Minigame.wallBall_coinCoordinates[i].x;
            e1->pos[1] = -g_Minigame.wallBall_coinCoordinates[i].y;
            e1->pos[2] = g_Minigame.wallBall_coinCoordinates[i].z;
            e1->rot[0] = lbl_3_rodata_33AC;
            e1->rot[2] = lbl_3_rodata_33AC;
            fn_8001D0D0(j, lbl_3_rodata_33F8);
            if (MG3310.e.coinFrames[i] <= 1) {
                e1->rot[1] = RandomF32_Game_Range(lbl_3_rodata_33D0, lbl_3_rodata_33D4);
            } else if (g_Minigame.wallBall_coinsVisibleInd[i] == 1) {
                e1->rot[1] = fn_3_9FEA8(lbl_3_rodata_33FC + e1->rot[1]);
            } else {
                e1->rot[1] = fn_3_9FEA8(lbl_3_rodata_33F4 + e1->rot[1]);
            }
            e2->visible = 1;
            *(s32*)e2 = 0;
            e2->pos[0] = g_Minigame.wallBall_coinCoordinates[i].x;
            e2->pos[1] = lbl_3_rodata_33C4;
            e2->pos[2] = g_Minigame.wallBall_coinCoordinates[i].z;
            fn_8001D0D0(i, lbl_3_rodata_3400);
            if (MG3310.e.coinFrames[i] > lbl_3_data_21A04[3] - 0xB4 &&
                g_Minigame.wallBall_coinsVisibleInd[i] == 1 && (g_d_GameSettings.FrameCountWhileNotAtMainMenu & 1)) {
                e1->visible = 0;
                e2->visible = 0;
            }
            if (g_Minigame.wallBall_coinsVisibleInd[i] == 3 && (g_d_GameSettings.FrameCountWhileNotAtMainMenu & 1)) {
                e1->visible = 0;
                e2->visible = 0;
            }
        }
    }
}

// .text:0x00118358 size:0xA4 mapped:0x807573EC
extern void* memset(void* dst, int c, size_t n);

void fn_3_118358(s32 i, f32* v) {
    // objects[i + 0x82].actor, addressed as the original does (base + 0x34 then an indexed load)
    GameBone* o = (*(GameActor**)((u8*)lbl_8036E548.objs + (i + 0x82) * sizeof(ActorObject) + OFFSET_OF(ActorObjectTable, objects[0].actor)))->boneArray[17];
    if (i < 0 || i > 2) {
        return;
    }
    if (v != NULL) {
        memset(v, 0, 0xC);
        PSMTXMultVec(o->forwardMtx, (Vec*)v, (Vec*)v);
        v[1] *= -1.0f;
    }
}

// .text:0x001183FC size:0x10C mapped:0x80757490
extern f32 lbl_3_data_21B94[];
extern const f32 lbl_3_rodata_33AC;
extern f32 lbl_3_data_226DC;
void fn_3_1183FC(void) {
    s32 i;
    Rep3310Sprite* e;
    for (i = 0; i < 4; i++) {
        e = &lbl_8036E548.sprites[i];
        e[240].pos[0] = lbl_3_data_21B94[i * 3];
        e[240].pos[1] = -lbl_3_data_21B94[i * 3 + 1];
        e[240].pos[2] = lbl_3_data_21B94[i * 3 + 2];
        e[240].pos[1] = lbl_3_rodata_33AC;
        e[240].pos[2] = e[240].pos[2] - lbl_3_data_226DC;
        e[240].visible = 1;
    }
}

// .text:0x00118508 size:0x10C mapped:0x8075759C
void fn_3_118508(void) {
    SceneTask* p = lbl_803CC1B8;
    u8* m; // byte cursor over MG3310.a.markers, as the original steps it
    s32 i;
    if (g_GameLogic.gameStatus == 0xF) {
        fn_80034CEC(p);
        REMOVE_QUEUE_NOARG();
        return;
    }
    for (i = 0, m = (u8*)&g_Minigame; i < 0x28; m += sizeof(Rep3310Marker), i++) {
        if (m[OFFSET_OF(Rep3310MinigameView, a.markers[0].active)] == 0) {
            lbl_80371C30[p->u14.objIdx + i].obj->flags &= ~2;
        } else {
            lbl_80371C30[p->u14.objIdx + i].obj->flags |= 2;
            lbl_80371C30[p->u14.objIdx + i].obj->x = *(f32*)(m + OFFSET_OF(Rep3310MinigameView, a.markers[0].pos[0]));
            lbl_80371C30[p->u14.objIdx + i].obj->y = -*(f32*)(m + OFFSET_OF(Rep3310MinigameView, a.markers[0].pos[1]));
            lbl_80371C30[p->u14.objIdx + i].obj->z = *(f32*)(m + OFFSET_OF(Rep3310MinigameView, a.markers[0].pos[2]));
        }
    }
}

// .text:0x00118614 size:0x138 mapped:0x807576A8
void fn_3_118614(void) {
    SceneTask* p;
    s32 i;
    fn_80034E20(p = lbl_803CC1B8, lbl_3_data_69D0);
    for (i = 0; i < 0x28; i++) {
        lbl_80371C30[p->u14.objIdx + i].obj->_5C = 0x20000;
    }
    lbl_803CC1B8->func = fn_3_118508;
}

// .text:0x0011874C size:0xD0 mapped:0x807577E0
extern f32 lbl_3_data_226D4[];
extern const f32 lbl_3_rodata_3408;
extern const f32 lbl_3_rodata_33E0;
extern void fn_8001D110(s32 i, f32 a, f32 b, f32 c);

void fn_3_11874C(void) {
    s32 i;
    if (g_GameLogic.secondaryGameMode == 8) {
        return;
    }
    for (i = 0; i < 0x28; i++) {
        Rep3310Sprite* p = &lbl_8036E548.sprites[i];
        f32* v = MG3310.a.markers[i].pos;
        p->visible = 0;
        *(s32*)p = 0;
        if (MG3310.a.markers[i].active != 0) {
            p->visible = 1;
            p->pos[0] = v[0];
            p->pos[2] = v[2];
            p->pos[1] = lbl_3_rodata_3408;
            fn_8001D110(i, lbl_3_data_226D4[1], lbl_3_rodata_33E0, lbl_3_data_226D4[1]);
        }
    }
}

// .text:0x0011881C size:0x60 mapped:0x807578B0
// NONMATCHING 90%: objs[i].actor: base+0x34 is folded into the load (add; lwz 0x34) where the original does addi r0,base,0x34; lwzx (docs/patterns/unsolved.md)
#if NONMATCHING
extern u8 lbl_3_data_226BC[];
void fn_3_11881C(s32 i) {
    s32 tex;
    if (i - 0xE9 < 4) {
        tex = lbl_3_data_226BC[i - 0xE9];
    } else {
        tex = lbl_3_data_226BC[4];
    }
    PTR32_GET(DOTexBank, lbl_8036E548.objs->objects[i].actor->boneArray[0]->dispObj->textureData->texturePalette)->tex[0].texIndex = tex;
}
#endif

// .text:0x0011887C size:0x100 mapped:0x80757910
extern f32 lbl_3_data_21B94[];
extern u8 lbl_3_data_21BC4[];
extern f32 lbl_3_data_226C4[];
extern const f32 lbl_3_rodata_33AC;

void fn_3_11887C(void) {
    Rep3310Sprite* e;
    s32 i;
    f32* v;
    for (i = 0; i < 7; i++) {
        e = &lbl_8036E548.sprites[(i + 0xE9)];
        e->visible = 1;
        if (i < 4) {
            v = &lbl_3_data_21B94[i * 3];
            e->pos[0] = v[0];
            e->pos[1] = -v[1];
            e->pos[2] = v[2];
            e->pos[1] = lbl_3_rodata_33AC;
            fn_8001D110(i + 0xE9, lbl_3_data_226C4[2], lbl_3_data_226C4[3], lbl_3_data_226C4[2]);
            e->draw = fn_3_11881C;
        } else {
            v = (f32*)(lbl_3_data_21BC4 + i * 0x30 - 0xC0);
            e->pos[0] = v[0];
            e->pos[1] = -v[1];
            e->pos[2] = v[2];
            fn_8001D110(i + 0xE9, lbl_3_data_226C4[0], lbl_3_data_226C4[1], lbl_3_data_226C4[0]);
            e->draw = fn_3_11881C;
        }
    }
}

// .text:0x0011897C size:0x4C mapped:0x80757A10
// NONMATCHING 90%: objs[i].actor: base+0x34 is folded into the load (add; lwz 0x34) where the original does addi r0,base,0x34; lwzx (docs/patterns/unsolved.md)
#if NONMATCHING
// Sets the skin texture of player-ball sprite i (0x82..0x84) from its state byte.
void fn_3_11897C(s32 i) {
    PTR32_GET(DOTexBank, lbl_8036E548.objs->objects[i].actor->skinObject->textureData->texturePalette)->tex[0].texIndex =
        lbl_3_data_22670[MG3310.racers[i - 0x82].skin];
}
#endif

// .text:0x001189C8 size:0x150 mapped:0x80757A5C
extern f32 lbl_3_data_22694[];
extern s16 lbl_3_data_226AC[];
void fn_3_1189C8(s32 i, s32 a, s32 b, s32 d, u8 flag) {
    Rep3310Racer* m = &MG3310.racers[i];
    ActorObject* o = &lbl_8036E548.objs->objects[(i + 0x82)];
    f32 inv = lbl_3_rodata_33AC;
    u8 t;
    void* x;
    if (d != 0) {
        inv = 1.0f / (f32)d;
    }
    x = MG_ASSETS.animBanks[2];
    o->animBank = x;
    o->seqNum = a;
    o->time = lbl_3_rodata_33AC;
    o->setAnimation = 1;
    o->setTime = (x != 0);
    o->setSpeed = (x != 0);
    o->speed = inv;
    o->unk54 = lbl_3_data_22694[a];
    o->setSpeed = 1;
    o->time = (f32)(b + lbl_3_data_226AC[a]);
    o->setTime = 1;
    if (flag != 0) {
        o->visFlags = 3;
    } else {
        o->visFlags = 2;
    }
    m->anim = a;
    m->animFrame = b;
}

// .text:0x00118B18 size:0x7A0 mapped:0x80757BAC
// NONMATCHING 74%: same instructions apart from addressing; the original reaches lbl_3_data_22678/22688/22694/226AC through the lbl_3_data_225F0 pooled base (one saved reg), we use one lis per access; inlined fn_3_1189C8 copies
#if NONMATCHING
extern s16 lbl_3_data_21E68[];
extern f32 lbl_3_data_22678[];
extern f32 lbl_3_data_22688[];
extern s32 fn_3_143770(u8* p);
extern f32 LinearInterpolateToNewRange(f32 value, f32 prevMin, f32 prevMax, f32 nextMin, f32 nextMax);
// Animation state machine of runner i (&MG3310.racers[i]), actor 0x82 + i.
void fn_3_118B18(s32 i) {
    Rep3310Racer* g = &MG3310.racers[i];
    s32 frame;

    g->animFrame += 1;
    if (g->state == 1) {
        if (g->_1A <= 1) {
            fn_3_1189C8(i, 2, 0, 0, 0);
            fn_8001D0D0(i + 0x82, 0.01f);
        } else {
            fn_8001D0D0(i + 0x82, LinearInterpolateToNewRange((f32)g->_1A, 0.0f, (f32)lbl_3_data_21E68[5],
                                                               lbl_3_data_22678[g->_2B + 2], lbl_3_data_22678[g->_2B]));
        }
        if (g->_1C == 1) {
            fn_3_1189C8(i, 0, 0, 6, 1);
        }
    } else if (g->state == 4) {
        if (g->_1A <= 1) {
            fn_3_1189C8(i, 4, 0, 0, 0);
        }
    } else if (g->_1E == 2) {
        if (g->_2B == 0) {
            fn_3_1189C8(i, 1, 0, 0, 0);
        } else {
            fn_3_1189C8(i, 5, 0, 0, 0);
        }
    } else if (g->_1E == lbl_3_data_21E68[7]) {
        if (g->anim != 0) {
            fn_3_1189C8(i, 0, 0, 6, 1);
        }
    } else {
        if (g->_2E != 0 && (g->_26 == 1 || g->_2B != 0)) {
            // lbl_3_data_226AC is followed by two u8 frame counts at +0xC/+0xD
            frame = (u8)(lbl_3_data_226AC[6] >> 8) - lbl_3_data_21E68[13] - 1;
            if (g->_2B == 0) {
                fn_3_143770((u8*)g);
            }
            fn_3_1189C8(i, 3, frame, 2, 0);
        }
        if (g->anim == 3 && g->animFrame == (u8)lbl_3_data_226AC[6] - lbl_3_data_226AC[3]) {
            fn_3_1189C8(i, 0, 0, 6, 1);
            g->_0C.z = 0.0f;
            g->_0C.x = 0.0f;
            g->_0C.y = lbl_3_data_22688[i];
        }
    }
}
#endif

// .text:0x001192B8 size:0x1B0 mapped:0x8075834C
extern s16 lbl_3_data_21E68[];
extern f32 lbl_3_data_22678[];
extern f32 lbl_3_data_22688[];
extern const f32 lbl_3_rodata_33E0;
void fn_3_1192B8(void) {
    Rep3310Racer* g;
    Rep3310Sprite* e;
    s32 i;
    for (i = 0; i < 3; i++) {
        g = &MG3310.racers[i];
        e = &lbl_8036E548.sprites[(i + 0x82)];
        e->visible = 0;
        if (g->state != 0) {
            e->visible = 1;
            e->pos[0] = g->pos.x;
            e->pos[1] = -g->pos.y;
            e->pos[2] = g->pos.z;
            if (g->state != 3) {
                fn_8001D0D0(i + 0x82, lbl_3_data_22678[g->_2B]);
            } else {
                f32 t = (f32)g->_1A / (f32)lbl_3_data_21E68[6];
                f32* q = &lbl_3_data_22678[g->_2B];
                f32 u = lbl_3_rodata_33E0 - t;
                fn_8001D0D0(i + 0x82, u * q[0] + q[2] * t);
            }
            if (g->_2B == 0) {
                e->rot[1] = g->_0C.y;
                e->rot[0] = lbl_3_rodata_33AC;
                e->rot[2] = lbl_3_rodata_33AC;
            } else {
                e->rot[1] = lbl_3_data_22688[i];
            }
            if (g->state == 4 && g->_1C <= 0 && (g->_1A & 1)) {
                e->visible = 0;
            }
            e->draw = fn_3_11897C;
            ((void (*)(s32))fn_3_118B18)(i);
        }
    }
}

// .text:0x00119468 size:0x44 mapped:0x807584FC
extern void fn_3_14225C(void);

void fn_3_119468(s32 i) {
    GameActor* o = lbl_8036E548.objs->objects[i].actor;
    if (o->flags & 9) {
        fn_3_14225C();
    }
}

// .text:0x001194AC size:0x50 mapped:0x80758540
// NONMATCHING 90%: objs[i].actor: base+0x34 is folded into the load (add; lwz 0x34) where the original does addi r0,base,0x34; lwzx (docs/patterns/unsolved.md)
#if NONMATCHING
void fn_3_1194AC(s32 i) {
    PTR32_GET(DOTexBank, lbl_8036E548.objs->objects[i].actor->boneArray[0]->dispObj->textureData->texturePalette)->tex[0].texIndex =
        lbl_3_data_2265C.tex[g_Minigame._1AFE[i + 1]];
}
#endif

// .text:0x001194FC size:0x358 mapped:0x80758590
// NONMATCHING 90%: register allocation, the state 0/3/4 test is folded to a range compare, and the bounce counter update order differs; the original reaches lbl_3_data_2265C through the lbl_3_data_225F0 pooled base
#pragma pool_data off // each float constant is its own .rodata symbol in the original
#if NONMATCHING
extern void fn_3_15521C(s16 idx, f32* pos, f32* rot); // rep_3880.h
// Places the 50 balls (sprites 0x85.., or 0xB7.. while state 5) and their shadows (0x28..).
void fn_3_1194FC(void) {
    Vec dir;
    Vec fwd = {0.0f, 0.0f, 1.0f};
    Rep3310Sprite* e;
    Rep3310Sprite* alt;
    Rep3310Sprite* shadow;
    s32 base;
    s32 i;
    f32 ang;
    f32 s;

    for (i = 0; i < 50; i++) {
        e = &lbl_8036E548.sprites[i + 0x85];
        e->visible = 0;
        e->draw = NULL;
        alt = &lbl_8036E548.sprites[i + 0xB7];
        alt->visible = 0;
        alt->draw = NULL;
        shadow = &lbl_8036E548.sprites[i + 0x28];
        shadow->visible = 0;
        shadow->draw = NULL;
        if (g_Minigame.wallBall_coinsVisibleInd[i] == 0 || g_Minigame.wallBall_coinsVisibleInd[i] == 3 || g_Minigame.wallBall_coinsVisibleInd[i] == 4) {
            continue;
        }
        if (g_Minigame._1B84[i] == 5) {
            alt->draw = NULL;
            e = alt;
            base = 0xB7;
        } else {
            base = 0x85;
            e->draw = fn_3_1194AC;
        }
        e->visible = 1;
        e->pos[0] = g_Minigame.wallBall_coinCoordinates[i].x;
        e->pos[1] = -g_Minigame.wallBall_coinCoordinates[i].y;
        e->pos[2] = g_Minigame.wallBall_coinCoordinates[i].z;
        if (g_Minigame.wallBall_coinsVisibleInd[i] == 2) {
            s = lbl_3_data_2265C.scale -
                ((f32)g_Minigame._1C4C[i] * (lbl_3_data_2265C.scale - lbl_3_data_2265C.minScale)) /
                    (f32)lbl_3_data_2265C.squashFrames;
            if (lbl_80366158._28 == 0) {
                fn_8001D110(base + i, lbl_3_data_2265C.scale, s, lbl_3_data_2265C.scale);
                g_Minigame._1C4C[i] = g_Minigame._1C4C[i] - g_Minigame._1C1A[i] * 2 + 1;
                if (g_Minigame._1C4C[i] >= 60) {
                    g_Minigame._1C1A[i] = g_Minigame._1C1A[i] == 0;
                }
                g_Minigame._1C4C[i] = g_Minigame._1C4C[i] - g_Minigame._1C1A[i] * 2 + 1;
            }
            e->rot[0] = 0.0f;
            e->rot[1] = 0.0f;
            e->rot[2] = 0.0f;
            if (g_Minigame._1B84[i] == 5) {
                e->pos[1] -= 0.5f;
            }
            continue;
        }
        fn_8001D0D0(base + i, lbl_3_data_2265C.scale);
        if (g_Minigame.wallBall_coinsVisibleInd[i] != 6) {
            dir.x = MG3310.d.coinVel[i].x;
            dir.y = 0.0f;
            dir.z = MG3310.d.coinVel[i].z;
            PSVECNormalize(&dir, &dir);
            ang = acos(PSVECDotProduct(&fwd, &dir));
            if (dir.x < 0.0f) {
                ang = 6.2831855f - ang;
            }
            if (lbl_80366158._28 == 0) {
                e->rot[1] = ang;
                e->rot[0] += -0.17453292f;
            }
        }
        if (g_Minigame._1B84[i] == 5 && MG3310.e.coinFrames[i] == 1) {
            fn_3_15521C(i, e->pos, e->rot);
        }
        if (g_Minigame._1B84[i] == 5) {
            e->draw = fn_3_119468;
        }
        shadow->visible = 1;
        shadow->pos[0] = g_Minigame.wallBall_coinCoordinates[i].x;
        shadow->pos[1] = -0.05f;
        shadow->pos[2] = g_Minigame.wallBall_coinCoordinates[i].z;
        fn_8001D0D0(i + 0x28, lbl_3_data_2265C.shadowScale);
    }
}
#endif
#pragma pool_data reset

// .text:0x00119854 size:0x24 mapped:0x807588E8
f32 fn_3_119854(u8 i) {
    if (i > 2) {
        i = 2;
    }
    return lbl_3_data_22650[i];
}

// .text:0x00119878 size:0xBC mapped:0x8075890C
// NONMATCHING 97%: the sprite-array and g_Minigame base registers (r5/r6) come out swapped; declaration/init orders, nested ifs and no-local forms did not help
#if NONMATCHING
void fn_3_119878(void) {
    MiniGameStruct* g = &g_Minigame;
    Rep3310Sprite* p = lbl_8036E548.sprites;
    p[0xA6].visible = 0;
    p[0xA6].draw = NULL;
    if (g->_CCE[0] != 0 &&
        (g->_CCC > 0x3C || g->_CCC % 2 != 0 ||
         g->_1B19 == 2 || g->_1B19 == 3)) {
        p[0xA6].visible = 1;
        p[0xA6].draw = fn_3_11741C;
        p[0xA6].pos[0] = g->_CB0;
        p[0xA6].pos[1] = -g->_CB4;
        p[0xA6].pos[2] = g->_CB8;
        fn_8001D0D0(0xA6, 3.5f);
    }
}
#endif

// .text:0x00119934 size:0x300 mapped:0x807589C8
// NONMATCHING 97%: (measured with the rodata externs) frsp of the acos result is scheduled after the v.z load, f1/f2 swapped
#pragma pool_data off // each float constant is its own .rodata symbol in the original
#if NONMATCHING
extern f32 lbl_3_data_2188C[];
// Places the base markers (sprites 0x82..0x90, or the shared 0xA5 one) and the
// running fielders' shadows (sprites 0x91..0xA4), spinning each a little per frame.
void fn_3_119934(void) {
    Rep3310Sprite* shared = &lbl_8036E548.sprites[0xA5];
    Rep3310Sprite* e;
    Vec dir;
    f32 ang;
    s32 i;
    s32 k;
    u8 base;

    shared->visible = 0;
    for (i = 0; i < 15; i++) {
        e = &lbl_8036E548.sprites[i + 0x82];
        e->visible = 0;
        base = g_Minigame.wallBall_coinsVisibleInd[i];
        k = MG3310.f.kindState[base] - 2;
        if (k == 2) {
            if (base >= 1 && base <= 6) {
                shared->visible = 1;
                shared->pos[0] = g_Minigame.wallBall_coinCoordinates[i].x;
                shared->pos[1] = g_Minigame.wallBall_coinCoordinates[i].y;
                shared->pos[2] = g_Minigame.wallBall_coinCoordinates[i].z;
                fn_8001D0D0(0xA5, lbl_3_data_22650[k]);
                shared->rot[1] += 0.005f;
                if (shared->rot[1] > 3.1415927f) {
                    shared->rot[1] -= 6.2831855f;
                }
            }
        } else if (base >= 1 && base <= 6) {
            e->visible = 1;
            e->pos[0] = g_Minigame.wallBall_coinCoordinates[i].x;
            e->pos[1] = g_Minigame.wallBall_coinCoordinates[i].y;
            e->pos[2] = g_Minigame.wallBall_coinCoordinates[i].z;
            fn_8001D0D0(i + 0x82, lbl_3_data_22650[k]);
            e->rot[1] += 0.005f;
            if (e->rot[1] > 3.1415927f) {
                e->rot[1] -= 6.2831855f;
            }
        }
    }
    for (i = 15; i < 35; i++) {
        e = &lbl_8036E548.sprites[i + 0x82];
        e->visible = 0;
        if (g_Minigame.turnOverStatus == 0 && g_Minigame.wallBall_coinsVisibleInd[i] == 1) {
            e->visible = 1;
            e->pos[0] = g_Minigame.wallBall_coinCoordinates[i].x;
            e->pos[1] = -g_Minigame.wallBall_coinCoordinates[i].y;
            e->pos[2] = g_Minigame.wallBall_coinCoordinates[i].z;
            fn_8001D0D0(i + 0x82, 5.0f);
            if (MG3310.e.coinFrames[i] == 0) {
                e->rot[0] = RandomF32_Game_Range(-3.1415927f, 3.1415927f);
                memcpy(&dir, &MG3310.d.coinVel[i], sizeof(Vec));
                dir.y = 0.0f;
                PSVECNormalize(&dir, &dir);
                ang = acos(dir.x);
                if (dir.z < 0.0f) {
                    ang = 6.2831855f - ang;
                }
                e->rot[1] = ang;
            } else if (lbl_80366158._28 == 0) {
                memcpy(&dir, &MG3310.d.coinVel[i], sizeof(Vec));
                dir.y = 0.0f;
                e->rot[0] += (0.05f * PSVECMag(&dir)) / lbl_3_data_2188C[3];
            }
        }
    }
}
#endif
#pragma pool_data reset

// .text:0x00119C34 size:0x74 mapped:0x80758CC8
void fn_3_119C34(void) {
    ActorObject* p = &lbl_8036E548.objs->objects[31];
    void* v = MG_ASSETS.animBanks[1];
    s8 t;
    p->animBank = v;
    p->seqNum = 1;
    t = v != 0;
    p->time = 0.0f;
    p->setAnimation = 1;
    p->setTime = t;
    p->setSpeed = t;
    p->speed = 0.0f;
    p->unk54 = 1.0f;
    p->setSpeed = 1;
    p->time = 0.0f;
    p->setTime = 1;
    p->visFlags = 2;
}

// .text:0x00119CA8 size:0x80 mapped:0x80758D3C
void fn_3_119CA8(s32 i) {
    ActorObject* e = &lbl_8036E548.objs->objects[i];
    void* v = MG_ASSETS.animBanks[1];
    s8 t;
    e->animBank = v;
    e->seqNum = 0;
    t = v != 0;
    e->time = 0.0f;
    e->setAnimation = 1;
    e->setTime = t;
    e->setSpeed = t;
    e->speed = 0.0f;
    e->unk54 = 1.0f;
    e->setSpeed = 1;
    e->time = 0.0f;
    e->setTime = 1;
    e->visFlags = 2;
}

// .text:0x00119D28 size:0xC mapped:0x80758DBC
f32 fn_3_119D28(void) {
    return lbl_3_data_2262C;
}

// .text:0x00119D34 size:0xFC mapped:0x80758DC8
void fn_3_119D34(void) {
    Rep3310Sprite* q = &lbl_8036E548.sprites[31];
    q->visible = 1;
    fn_3_11A92C(q, 0x1F);
    if (lbl_80366158._28 == 0 && g_GameLogic.gameStatus == 1 && g_Pitcher.pitchTotalTimeCounter == lbl_3_data_217A4[7]) {
        {

        ActorObject* p = &lbl_8036E548.objs->objects[31];
        void* v = MG_ASSETS.animBanks[1];
        s8 t;
        p->animBank = v;
        p->seqNum = 1;
        t = v != 0;
        p->time = 0.0f;
        p->setAnimation = 1;
        p->setTime = t;
        p->setSpeed = t;
        p->speed = 0.0f;
        p->unk54 = 1.0f;
        p->setSpeed = 1;
        p->time = 0.0f;
        p->setTime = 1;
        p->visFlags = 2;
}
        fn_3_90064(0x2E6);
    }
}

// .text:0x00119E30 size:0xB0 mapped:0x80758EC4
// NONMATCHING 90%: objs[i].actor: base+0x34 is folded into the load (add; lwz 0x34) where the original does addi r0,base,0x34; lwzx (docs/patterns/unsolved.md)
#if NONMATCHING
extern u8 lbl_3_data_2263C[];
extern u8 lbl_3_data_2263E;
// Blinks the highlighted runner's texture (swaps texture records 0-2 through lbl_3_data_2263C).
void fn_3_119E30(s32 i) {
    TextureData* td;
    if (g_Minigame.barrels[g_Minigame.bB_bombBarrelID].animationCounter % lbl_3_data_2263E == 0) {
        td = lbl_8036E548.objs->objects[i].actor->boneArray[0]->dispObj->textureData;
        PTR32_GET(DOTexBank, td->texturePalette)->tex[0].texIndex = lbl_3_data_2263C[PTR32_GET(DOTexBank, td->texturePalette)->tex[0].texIndex] == 0;
        PTR32_GET(DOTexBank, td->texturePalette)->tex[1].texIndex = lbl_3_data_2263C[PTR32_GET(DOTexBank, td->texturePalette)->tex[1].texIndex] == 0;
        PTR32_GET(DOTexBank, td->texturePalette)->tex[2].texIndex = lbl_3_data_2263C[PTR32_GET(DOTexBank, td->texturePalette)->tex[2].texIndex] == 0;
    }
}
#endif

// .text:0x00119EE0 size:0x8C mapped:0x80758F74
// NONMATCHING 90%: objs[i].actor: base+0x34 is folded into the load (add; lwz 0x34) where the original does addi r0,base,0x34; lwzx (docs/patterns/unsolved.md)
#if NONMATCHING
extern u8 lbl_3_data_22638[];
void fn_3_119EE0(s32 i) {
    BB_barrelStruct* g = &g_Minigame.barrels[i];
    TextureData* td = lbl_8036E548.objs->objects[i].actor->boneArray[0]->dispObj->textureData;
    PTR32_GET(DOTexBank, td->texturePalette)->tex[0].texIndex = lbl_3_data_22638[g->barrelColour] * 3;
    PTR32_GET(DOTexBank, td->texturePalette)->tex[1].texIndex = lbl_3_data_22638[g->barrelColour] * 3 + 1;
    PTR32_GET(DOTexBank, td->texturePalette)->tex[2].texIndex = lbl_3_data_22638[g->barrelColour] * 3 + 2;
}
#endif

// .text:0x00119F6C size:0x2A0 mapped:0x80759000
// NONMATCHING 92%: typed rewrite of a 95% raw-offset version; saved-reg assignment and loop induction pointers differ (the original strength-reduces the 0x28/0x90/0x34 strides into separate counters)
#pragma pool_data off // each float constant is its own .rodata symbol in the original
#if NONMATCHING
extern u8 lbl_3_data_2263F;
extern void fn_3_14DC80(s8 a);
extern void fn_3_14CB28(s8 a);
// Places the 15 runners: sprite i normally, sprite 0x10 + i (an animated actor) while
// scoring (state 4), and the shared highlight sprite 0xF for the selected runner.
void fn_3_119F6C(void) {
    Rep3310Sprite* hilite = &lbl_8036E548.sprites[0xF];
    Rep3310Sprite* e;
    Rep3310Sprite* runner;
    GameActor* actor;
    BB_barrelStruct* p;
    u32 frame;
    u32 k;
    s32 i;
    u8 flag = 0;

    hilite->visible = 0;
    for (i = 0; i < 15; i++) {
        e = &lbl_8036E548.sprites[i];
        p = &g_Minigame.barrels[i];
        runner = &lbl_8036E548.sprites[i + 0x10];
        runner->visible = 0;
        e->visible = 0;
        if (p->barrelState == 0) {
            continue;
        }
        if (p->barrelState == 4) {
            e = runner;
            if (p->animationCounter == 0) {
                fn_3_119CA8(i + 0x10);
                fn_3_14DC80(i);
                fn_3_90064(0x2E3);
            }
            frame = fn_800B4A94(lbl_8036E548.objs->objects[i + 0x10].actor);
            if (frame <= lbl_3_data_2263F) {
                if ((frame & 1) == 0) {
                    actor = lbl_8036E548.objs->objects[i + 0x10].actor;
                    for (k = 0; k < actor->totalBones; k++) {
                        struct ANIMPipe* anim = actor->boneArray[k]->animPipe;
                        if (anim != NULL) {
                            anim->time += anim->speed;
                        }
                    }
                    runner->visible = 0;
                    continue;
                }
                if (frame == 0) {
                    fn_3_14CB28(i);
                }
            }
        } else if (p->barrelColour == 3 && i == g_Minigame.bB_bombBarrelID) {
            flag = 1;
            e = hilite;
        }
        e->visible = 1;
        e->pos[0] = p->currentPos.x;
        e->pos[1] = -p->currentPos.y;
        e->pos[2] = p->currentPos.z;
        e->rot[0] = 0.0f;
        e->rot[1] = 0.0f;
        e->rot[2] = 0.0f;
        if (flag != 0) {
            fn_8001D0D0(0xF, 0.75f);
        } else {
            fn_8001D0D0(i, 0.75f);
        }
        if (flag != 0) {
            flag = 0;
            e->draw = fn_3_119E30;
        } else if (p->barrelState != 4) {
            e->draw = fn_3_119EE0;
        } else {
            e->draw = NULL;
        }
    }
}
#endif
#pragma pool_data reset

// .text:0x0011A20C size:0x4 mapped:0x807592A0
void fn_3_11A20C(void) {
    return;
}

// .text:0x0011A210 size:0x140 mapped:0x807592A4
extern const f32 lbl_3_rodata_342C;
extern const f32 lbl_3_rodata_3430;
void fn_3_11A210(void) {
    Rep3310Sprite* e1;
    Rep3310Sprite* e2;
    s32 i;
    for (i = 0; i < 100; i++) {
        e1 = &lbl_8036E548.sprites[(i + 0x82)];
        e1->visible = 0;
        e1->draw = 0;
        e2 = &lbl_8036E548.sprites[i];
        e2->visible = 0;
        e2->draw = 0;
        if (g_Minigame.wallBall_coinsVisibleInd[i] != 0) {
            e1->visible = 1;
            e1->pos[0] = g_Minigame.wallBall_coinCoordinates[i].x;
            e1->pos[1] = -g_Minigame.wallBall_coinCoordinates[i].y;
            e1->pos[2] = g_Minigame.wallBall_coinCoordinates[i].z;
            fn_8001D0D0(i + 0x82, lbl_3_rodata_342C);
            if (MG3310.e.coinFrames[i] <= 1) {
                e1->rot[1] = RandomF32_Game_Range(lbl_3_rodata_33D0, lbl_3_rodata_33D4);
            } else {
                e1->rot[1] = fn_3_9FEA8(lbl_3_rodata_33FC + e1->rot[1]);
            }
            e2->visible = 1;
            e2->pos[0] = g_Minigame.wallBall_coinCoordinates[i].x;
            e2->pos[1] = lbl_3_rodata_33C4;
            e2->pos[2] = g_Minigame.wallBall_coinCoordinates[i].z;
            fn_8001D0D0(i, lbl_3_rodata_3430);
        }
    }
}

// .text:0x0011A350 size:0x3C mapped:0x807593E4
u32 fn_3_11A350(int i) {
    return fn_800B4A94(lbl_8036E548.objs->objects[i].actor);
}

// .text:0x0011A38C size:0x7C mapped:0x80759420
void fn_3_11A38C(s32 i, s16 h) {
    ActorObject* e = &lbl_8036E548.objs->objects[i];
    void* v = MG_ASSETS.animBanks[0];
    s8 t;
    e->animBank = v;
    e->seqNum = h;
    t = v != 0;
    e->time = 0.0f;
    e->setAnimation = 1;
    e->setTime = t;
    e->setSpeed = t;
    e->speed = 0.0f;
    e->unk54 = 1.0f;
    e->setSpeed = 1;
    e->time = 0.0f;
    e->setTime = 1;
    e->visFlags = 2;
}

// .text:0x0011A408 size:0x524 mapped:0x8075949C
// NONMATCHING 94%: (measured with the rodata externs) register allocation and the j + kind*7 + 0xFC sum order
#pragma pool_data off // each float constant is its own .rodata symbol in the original
#if NONMATCHING
extern u8 lbl_3_data_22634[];
extern s16 lbl_3_data_21654[];
extern f32 lbl_3_data_21520[];
extern void fn_3_151710(ActorObject* obj, Vec* pos); // rep_3880.h: (void*, Vec*)
extern void fn_3_14C348(Rep3310Item* item, u8 caught); // rep_3880.h: (f32* pos, u8)
extern void fn_3_1666B0(Rep3310Item* item); // rep_3E58.h: (Vec* pos)
// Places the 7 bonus items (g_Minigame + 0x72C) and their shadows; state 4 plays the
// pickup animation once, state 5 waits for it to end.
void fn_3_11A408(void) {
    Rep3310Item* item;
    Rep3310Sprite* e;
    Rep3310Sprite* shadow;
    ActorObject* obj;
    GameActor* actor;
    Vec pos;
    s32 j;
    s32 n;
    u32 k;
    u8 caught = 0;
    u8 t;

    lbl_8036E548.sprites[0xFB].visible = 0;
    for (j = 0; j < 7; j++) {
        item = &MG3310.b.items[j];
        lbl_8036E548.sprites[0xE6 + j].visible = 0;
        lbl_8036E548.sprites[0xED + j].visible = 0;
        lbl_8036E548.sprites[0xF4 + j].visible = 0;
        lbl_8036E548.sprites[0xFC + j].visible = 0;
        lbl_8036E548.sprites[0x103 + j].visible = 0;
        lbl_8036E548.sprites[0x10A + j].visible = 0;
        if (item->state == 0) {
            continue;
        }
        if (item->state == 4) {
            n = j + (item->kind == 2) * 7 + 0xFC;
            if (item->kind == 2) {
                if (g_Minigame.wallBall_hitNoteBlock == 1) {
                    pos.x = item->pos[0];
                    pos.y = g_Ball.AtBat_Contact_BallPos.y;
                    pos.z = item->pos[2];
                    fn_3_11A38C(n, 3);
                    fn_3_151710(&lbl_8036E548.objs->objects[n], &pos);
                    fn_3_90064(0x2EB);
                } else {
                    fn_3_11A38C(n, item->kind);
                    fn_3_90064(0x2EC);
                }
            } else if (item->kind == 0) {
                fn_3_11A38C(n, item->kind);
                fn_3_90064(0x2E2);
            } else {
                if (item->kind == 1) {
                    caught = 1;
                }
                fn_3_90064(0x2FF);
            }
            fn_3_14C348(item, caught);
            if (caught) {
                item->state = 0;
                continue;
            }
            item->state = 5;
        } else if (item->state == 5) {
            n = j + (item->kind == 2) * 7 + 0xFC;
            t = (u32)fn_800B4A94(lbl_8036E548.objs->objects[n].actor);
            if (t < lbl_3_data_22634[item->kind] / 2 && t % 2 == 0) {
                actor = lbl_8036E548.objs->objects[n].actor;
                for (k = 0; k < actor->totalBones; k++) {
                    struct ANIMPipe* anim = actor->boneArray[k]->animPipe;
                    if (anim != NULL) {
                        anim->time += anim->speed;
                    }
                }
                continue;
            }
        } else if (item->kind == 0) {
            if (item->timer > lbl_3_data_21654[item->kind + 4] / 2) {
                n = j + 0xED;
            } else {
                n = 0xFB;
            }
        } else if (item->kind == 1) {
            n = j + 0xF4;
        } else {
            n = j + 0x10A;
            fn_3_1666B0(item);
        }

        e = &lbl_8036E548.sprites[n];
        e->visible = 1;
        e->pos[0] = item->pos[0];
        e->pos[1] = -item->pos[1];
        e->pos[2] = item->pos[2];
        e->rot[0] = 0.0f;
        e->rot[1] = 0.0f;
        e->rot[2] = 0.0f;
        e->rot[0] = item->spin;
        fn_8001D0D0(n, 1.75f);
        if (-e->pos[1] <= lbl_3_data_21520[22] && item->state < 4) {
            shadow = &lbl_8036E548.sprites[0xE6 + j];
            shadow->visible = 1;
            shadow->pos[0] = e->pos[0];
            shadow->pos[1] = -e->pos[1];
            shadow->pos[2] = e->pos[2];
            shadow->pos[1] = -0.03f;
            shadow->rot[0] = 0.0f;
            shadow->rot[1] = 0.0f;
            shadow->rot[2] = 0.0f;
            fn_8001D0D0(0xE6 + j, 1.75f * (1.0f - -e->pos[1] / lbl_3_data_21520[22]));
        }
    }
}
#endif
#pragma pool_data reset

// .text:0x0011A92C size:0x200 mapped:0x807599C0
#pragma dont_inline on
extern f32 lbl_3_data_22620[];
extern f32 lbl_3_data_21380[];
extern const f32 lbl_3_rodata_33E4;
extern const f32 lbl_3_rodata_3440;
extern const f64 lbl_3_rodata_3438;
extern void fn_3_14A90C(f32*);
extern void fn_3_14B9A0(u32 a, Vec* b);
// .bss (laid out last-defined-first)
static u8 lbl_3_bss_B6C0[0x40]; // unused
static f32 lbl_3_bss_B6BC;
static u8 lbl_3_bss_B6B8[0x4]; // unused
void fn_3_11A92C(Rep3310Sprite* q, s32 n) {
    f32 v[3];
    u8 t;
    u8 k;
    q->pos[0] = lbl_3_data_22620[0];
    q->pos[1] = lbl_3_data_22620[1];
    q->pos[2] = lbl_3_data_22620[2];
    q->rot[0] = lbl_3_rodata_33AC;
    q->rot[1] = lbl_3_rodata_33AC;
    q->rot[2] = lbl_3_rodata_33AC;
    fn_8001D0D0(n, lbl_3_data_2262C);
    if (g_Minigame.pauseInd == 0 && g_d_GameSettings.GameModeSelected != 2) {
        t = g_Minigame.GameMode_MiniGame;
        if (t == 1) {
            if (g_Pitcher.pitcherActionState >= 3) {
                if (g_Pitcher.currentStateFrameCounter == 1 && g_Pitcher.pitcherActionState == 3) {
                    lbl_3_bss_B6BC = lbl_3_rodata_33CC;
                    v[0] = lbl_3_data_21380[0];
                    v[1] = -lbl_3_data_21380[1];
                    v[2] = lbl_3_data_21380[2] - lbl_3_rodata_33E4;
                    fn_80062C24((Vec*)v);
                    fn_3_90064(0x2D6);
                }
                q->pos[2] = q->pos[2] + lbl_3_bss_B6BC;
                lbl_3_bss_B6BC = -((lbl_3_rodata_3438 * (q->pos[2] - lbl_3_data_22620[2])) - lbl_3_bss_B6BC);
                return;
            }
        } else if (t == 3) {
            if (g_Pitcher.currentStateFrameCounter == 1) {
                k = g_Pitcher.pitcherActionState;
                if (k == 1) {
                    fn_3_14B9A0(lbl_3_data_217A4[6] + lbl_3_data_217A4[7], (Vec*)lbl_3_data_22620);
                    fn_3_90064(0x30E);
                    return;
                } else if (k == 3) {
                    v[0] = lbl_3_data_21380[0];
                    v[1] = lbl_3_rodata_3440 + lbl_3_data_21380[1];
                    v[2] = lbl_3_data_21380[2] - lbl_3_rodata_33E4;
                    fn_3_14A90C(v);
                }
            }
        }
    }
}
#pragma dont_inline reset

// .text:0x0011AB2C size:0x140 mapped:0x80759BC0
void fn_3_11AB2C(void) {
    s32 n = 2;
    Rep3310Sprite* e;
    ShapeAnimState* t;
    if (g_d_GameSettings.GameModeSelected == 2) {
        n = 0;
    }
    e = &lbl_8036E548.sprites[n];
    if (e != NULL) {
        e->visible = 1;
        fn_3_11A92C(e, n);
        if (g_Pitcher.pitcherActionState >= 2 && lbl_80366158._28 == 0) {
            t = &MG_ASSETS.anim.state;
            if (t != NULL) {
                MG_ASSETS.anim.state.active = 1;
            }
            fn_80024DB0(t);
            fn_80024FA4((ShapeModel**)&lbl_8036E548.objs->objects[n].actor, MG_ASSETS.anim.model, t, -1);
        } else if (g_Pitcher.pitcherActionState < 2 && MG_ASSETS.anim.state.loops == 0) {
            MG_ASSETS.anim.state.keyIdx = 0;
            MG_ASSETS.anim.state.frame = MG_ASSETS.anim.state.keyIdx;
            MG_ASSETS.anim.state.loops = 1;
        }
    }
}

// .text:0x0011AC6C size:0xAF0 mapped:0x80759D00
// NONMATCHING 94%: all helpers inline as in the original; left: register allocation and the original reaching lbl_3_data_226C4/226D4/226DC through the lbl_3_data_225F0 pooled base
#if NONMATCHING
// Per-frame sprite update for the current minigame (g_Minigame[0x1A2A]); hides every
// sprite while the game logic is in states 0x1B..0x29.
void fn_3_11AC6C(void) {
    Rep3310Sprite* e;
    s32 i;

    if (g_GameLogic.gameStatus >= 0x1B && g_GameLogic.gameStatus <= 0x29) {
        if (lbl_8036E548.count != 0) {
            for (i = 0; i < lbl_8036E548.count; i++) {
                e = &lbl_8036E548.sprites[i];
                if (e != NULL) {
                    e->visible = 0;
                }
            }
        }
        return;
    }
    switch (g_Minigame.GameMode_MiniGame) {
    case 1:
        fn_3_11AB2C();
        break;
    case 2:
        fn_3_11A408();
        fn_3_11A210();
        break;
    case 3:
        fn_3_119F6C();
        fn_3_119D34();
        break;
    case 4:
        fn_3_119934();
        fn_3_119878();
        break;
    case 6:
        fn_3_118164();
        fn_3_1180A4();
        fn_3_117FC8();
        fn_3_11874C();
        fn_3_117AE4();
        fn_3_1179EC();
        fn_3_117494();
        break;
    case 5:
        fn_3_1194FC();
        fn_3_1192B8();
        fn_3_11874C();
        fn_3_11887C();
        fn_3_1183FC();
        break;
    }
}
#endif

// .text:0x0011B75C size:0x448 mapped:0x8075A7F0
void fn_3_11B75C(void) {
    lbl_8036E548.count = 0xF4;
#ifdef PORT_LP64
    lbl_8036E548.sprites = _OSAllocFromHeap(0x20, lbl_8036E548.count * sizeof(Rep3310Sprite)); // 0x30 on PC
#else
    lbl_8036E548.sprites = _OSAllocFromHeap(0x20, lbl_8036E548.count * 0x28);
#endif
    lbl_8036E548.objs = ActorObjectInitTable(lbl_8036E548.count);
    fn_3_11D2C8(0, 0, 0x82, 0, 0);
    fn_3_11D2C8(0x11, 0x82, 3, MG_ASSETS.animBanks[2], MG_ASSETS.skin);
    fn_3_11D2C8(0x12, 0x85, 0x32, 0, 0);
    fn_3_11D2C8(0xD, 0xB7, 0x32, 0, 0);
    fn_3_11D2C8(0x13, 0xE9, 7, 0, 0);
    fn_3_11D2C8(0x14, 0xF0, 4, 0, 0);
}

// .text:0x0011BBA4 size:0x488 mapped:0x8075AC38
void fn_3_11BBA4(void) {
    lbl_8036E548.count = 0xEE;
#ifdef PORT_LP64
    lbl_8036E548.sprites = _OSAllocFromHeap(0x20, lbl_8036E548.count * sizeof(Rep3310Sprite)); // 0x30 on PC
#else
    lbl_8036E548.sprites = _OSAllocFromHeap(0x20, lbl_8036E548.count * 0x28);
#endif
    lbl_8036E548.objs = ActorObjectInitTable(lbl_8036E548.count);
    fn_3_11D2C8(0, 0, 0x82, 0, 0);
    fn_3_11D2C8(0x15, 0x82, 0x64, 0, 0);
    fn_3_11D2C8(0x16, 0xE6, 1, 0, 0);
    fn_3_11D2C8(0x17, 0xE7, 1, 0, 0);
    fn_3_11D2C8(0x18, 0xE8, 1, 0, 0);
    fn_3_11D2C8(0x19, 0xE9, 4, 0, 0);
    fn_3_11D2C8(0x1A, 0xED, 1, 0, 0);
}

// .text:0x0011C02C size:0x2A0 mapped:0x8075B0C0
void fn_3_11C02C(void) {
    lbl_8036E548.count = 0xA7;
#ifdef PORT_LP64
    lbl_8036E548.sprites = _OSAllocFromHeap(0x20, lbl_8036E548.count * sizeof(Rep3310Sprite)); // 0x30 on PC
#else
    lbl_8036E548.sprites = _OSAllocFromHeap(0x20, lbl_8036E548.count * 0x28);
#endif
    lbl_8036E548.objs = ActorObjectInitTable(lbl_8036E548.count);
    fn_3_11D2C8(0, 0, 0x82, 0, 0);
    fn_3_11D2C8(0xB, 0x82, 0x23, 0, 0);
    fn_3_11D2C8(0xC, 0xA5, 1, 0, 0);
    fn_3_11D2C8(0x1A, 0xA6, 1, 0, 0);
}

// .text:0x0011C2CC size:0x32C mapped:0x8075B360
static inline void initObj_11C2CC(s32 i) {
    void* v = MG_ASSETS.animBanks[1];
    ActorObject* e = &lbl_8036E548.objs->objects[i];
    e->animBank = v;
    e->seqNum = 0;
    e->time = 0.0f;
    e->setAnimation = 1;
    e->setTime = v != 0;
    e->setSpeed = v != 0;
    e->speed = 0.0f;
    e->unk54 = 1.0f;
    e->setSpeed = 1;
    e->time = 0.0f;
    e->setTime = 1;
    e->visFlags = 2;
}
void fn_3_11C2CC(void) {
    s32 i;
    lbl_8036E548.count = 0x20;
#ifdef PORT_LP64
    lbl_8036E548.sprites = _OSAllocFromHeap(0x20, lbl_8036E548.count * sizeof(Rep3310Sprite)); // 0x30 on PC
#else
    lbl_8036E548.sprites = _OSAllocFromHeap(0x20, lbl_8036E548.count * 0x28);
#endif
    lbl_8036E548.objs = ActorObjectInitTable(lbl_8036E548.count);
    fn_3_11D2C8(8, 0, 0xF, 0, 0);
    fn_3_11D2C8(9, 0xF, 1, 0, 0);
    fn_3_11D2C8(0xA, 0x10, 0xF, 0, 0);
    fn_3_11D2C8(0x10, 0x1F, 1, 0, 0);
    for (i = 0; i < 0xF; i++) {
        initObj_11C2CC(i + 0x10);
    }
}

// .text:0x0011C5F8 size:0x708 mapped:0x8075B68C
static inline void initObj_11C5F8(s32 i, s16 h) {
    void* v = MG_ASSETS.animBanks[0];
    ActorObject* e = &lbl_8036E548.objs->objects[i];
    e->animBank = v;
    e->seqNum = h;
    e->time = 0.0f;
    e->setAnimation = 1;
    e->setTime = v != 0;
    e->setSpeed = v != 0;
    e->speed = 0.0f;
    e->unk54 = 1.0f;
    e->setSpeed = 1;
    e->time = 0.0f;
    e->setTime = 1;
    e->visFlags = 2;
}
void fn_3_11C5F8(void) {
    u16 i;
    lbl_8036E548.count = 0x111;
#ifdef PORT_LP64
    lbl_8036E548.sprites = _OSAllocFromHeap(0x20, lbl_8036E548.count * sizeof(Rep3310Sprite)); // 0x30 on PC
#else
    lbl_8036E548.sprites = _OSAllocFromHeap(0x20, lbl_8036E548.count * 0x28);
#endif
    lbl_8036E548.objs = ActorObjectInitTable(lbl_8036E548.count);
    fn_3_11D2C8(0, 0, 0x82, 0, 0);
    fn_3_11D2C8(0x15, 0x82, 0x64, 0, 0);
    fn_3_11D2C8(1, 0xE6, 7, 0, 0);
    fn_3_11D2C8(2, 0xED, 7, 0, 0);
    fn_3_11D2C8(3, 0xF4, 7, 0, 0);
    fn_3_11D2C8(5, 0xFB, 1, 0, 0);
    fn_3_11D2C8(6, 0xFC, 7, 0, 0);
    fn_3_11D2C8(7, 0x103, 7, 0, 0);
    fn_3_11D2C8(4, 0x10A, 7, 0, 0);
    for (i = 0; i < 7; i++) {
        initObj_11C5F8(i + 0xFC, 0);
        initObj_11C5F8(i + 0x103, 2);
    }
}

// .text:0x0011CD00 size:0x204 mapped:0x8075BD94
extern void* _OSAllocFromHeap(int, int);
void fn_3_11CD00(void) {
    lbl_8036E548.count = 3;
#ifdef PORT_LP64
    lbl_8036E548.sprites = _OSAllocFromHeap(0x20, lbl_8036E548.count * sizeof(Rep3310Sprite)); // 0x30 on PC
#else
    lbl_8036E548.sprites = _OSAllocFromHeap(0x20, lbl_8036E548.count * 0x28);
#endif
    lbl_8036E548.objs = ActorObjectInitTable(lbl_8036E548.count);
    fn_3_11D2C8(0xD, 0, 1, 0, 0);
    fn_3_11D2C8(0xE, 1, 1, 0, 0);
    fn_3_11D2C8(0xF, 2, 1, 0, 0);
    MG_ASSETS.anim.state.speed = 0.5f;
    fn_80025C58((ShapeData*)MG_ASSETS.model, (ShapeModel**)&lbl_8036E548.objs->objects[2].actor);
}

// .text:0x0011CF04 size:0x80 mapped:0x8075BF98
void fn_3_11CF04(void) {
    if (g_d_GameSettings.GameModeSelected != 6) {
        lbl_8036E548.count = 0;
    }
    lbl_8036E548._307E = 0;
    minigamesSetSomePointers();
    minigamesGXStuff();
    minigamesSetSomePointers2();
    fn_80035B50(0xD);
    fn_3_B95EC();
    fn_3_5E60();
    fn_80018B38();
    fn_3_909B0();
    fn_3_9081C();
    fn_80035B50(0x11);
}

// .text:0x0011CF84 size:0x22C mapped:0x8075C018
extern void fn_80011B64(s32);
extern void fn_800B4CDC(void*);
extern void fn_800B4278(void*);
extern void fn_800ACFB0(void*);
extern void fn_800B993C(void);
extern void fn_3_90CB0(void);
void fn_3_11CF84(void) {
    s32 i;
    if ((g_Minigame._1A3C == 0 || g_Minigame._1E2A >= 6) && g_Minigame._1A38 == 0) {
        for (i = 0; i < 4; i++) {
            fn_80011B64(i);
        }
    }
    for (i = lbl_8036E548.count - 1; i >= 0; i--) {
        lbl_8036E548.objs->objects[i].animateBones = 0;
    }
    for (i = lbl_8036E548.count - 1; i >= 0; i--) {
        fn_800B4CDC(lbl_8036E548.objs->objects[i].actor);
    }
    if (g_d_GameSettings.GameModeSelected == 7) {
        for (i = lbl_8036E548.count - 1; i >= 0; i--) {
            fn_800B4278(lbl_8036E548.objs->objects[i].actor);
        }
        fn_800ACFB0(lbl_8036E548.objs);
        fn_800ACFB0(lbl_8036E548.sprites);
    }
    fn_800B993C();
    fn_3_90CB0();
    if (g_Minigame._1A38 == 0 || g_Minigame._1A3C != 0) {
        fn_3_11CF04();
    }
}

// .text:0x0011D1B0 size:0x118 mapped:0x8075C244
void fn_3_11D1B0(void) {
    s32 i;
    switch (g_Minigame.GameMode_MiniGame) {
    case 1:
        ((void (*)(void))fn_3_11CD00)();
        break;
    case 2:
        ((void (*)(void))fn_3_11C5F8)();
        break;
    case 3:
        ((void (*)(void))fn_3_11C2CC)();
        break;
    case 4:
        ((void (*)(void))fn_3_11C02C)();
        break;
    case 6:
        ((void (*)(void))fn_3_11BBA4)();
        break;
    case 5:
        ((void (*)(void))fn_3_11B75C)();
        break;
    }
    for (i = 0; i < lbl_8036E548.count; i++) {
        lbl_8036E548.sprites[i].pos[0] = lbl_3_rodata_33AC;
        lbl_8036E548.sprites[i].pos[1] = lbl_3_rodata_33AC;
        lbl_8036E548.sprites[i].pos[2] = lbl_3_rodata_33AC;
        lbl_8036E548.sprites[i].rot[0] = lbl_3_rodata_33AC;
        lbl_8036E548.sprites[i].rot[1] = lbl_3_rodata_33AC;
        lbl_8036E548.sprites[i].rot[2] = lbl_3_rodata_33AC;
        lbl_8036E548.sprites[i].visible = 0;
        lbl_8036E548.sprites[i].draw = NULL;
    }
}

// .text:0x0011D2C8 size:0xE4 mapped:0x8075C35C
void fn_3_11D2C8(s32 idx, s32 start, s32 count, void* animBank, struct sHdr* skHeader) {
    s32 k;
    for (k = start; k < start + count; k++) {
        fn_800BDC88(lbl_8036E548.objs, (u16)k, (u16)k, lbl_8036E548.data[idx].layout, animBank, skHeader);
        fn_800BD548(&lbl_8036E548.objs->objects[k], 4, lbl_8036E548.lights[0], lbl_8036E548.lights[1], lbl_8036E548.lights[2], lbl_8036E548.lights[3]);
        CTRLSetTranslation(&lbl_8036E548.objs->objects[k].worldControl.base, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(&lbl_8036E548.objs->objects[k].worldControl.base, 0.0f, 0.0f, 0.0f);
    }
}


