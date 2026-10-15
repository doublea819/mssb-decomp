// UnknownHomes_Game.h gives the typed globals (g_Ball, g_FieldingLogic, ...). Some of its
// guessed prototypes disagree with this file's headers; hide those under other names.
#define UHG_RENAMES_BEGIN
#define minigame_checkIfAIInputIs_Algorithmic_Or_ControllerBased UHG_minigame_checkIfAIInputIs_Algorithmic_Or_ControllerBased
#define UHG_RENAMES_END
#include "game/UnknownHomes_Game.h"
#include "static/GameSettings.h"
#undef minigame_checkIfAIInputIs_Algorithmic_Or_ControllerBased
#include "game/rep_AC8.h"
#include "game/running_logic.h" // g_RunningLogic
#include "game/rep_D0.h"
#include "game/rep_540.h"
#include "game/rep_18E8.h"
#include "game/rep_1CB8.h"
#include "game/rep_3520.h"
#include "game/rep_3E58.h"
#include "game/rep_1188.h"
#include "game/m_sound.h"
#include "game/auto_00_0006C854_text.h"
#include "game/auto_00_00106DFC_text.h"
#include "game/auto_00_001658F0_text.h" // StarChanceState (lbl_3_common_bss_37400)
#include "main/file_80069BDC.h"          // ChallengeTeamInfo lbl_800E8558[]
#include "game/auto_00_0001D86C_text.h" // FieldingChangeWork (lbl_3_common_bss_34C90)
#include "game/auto_00_0005985C_text.h" // fn_3_59918
#include "game/auto_00_00167CC4_text.h" // fn_3_1682AC
#include "game/rep_4090.h"              // fn_3_16D5E4
#define REP_HEADER_FN repHeader_AC8
#include "header_rep_inline.h"
#include "stl/math.h"
#include "stl/mem.h"
#include "musyx/musyx.h"

typedef struct { f32 a, b, c, d, e; } Ent14;
/* lbl_3_bss_C8: per-pad stick-angle history (20 frames each) */
typedef struct {
    s16 unk0[2];
    s16 hist[4][20];
    s16 cur;
    s16 unkA6;
    s16 tmp[20];
} StickHistory;
#ifdef TARGET_PC
// lbl_3_bss_16C/170 are StickHistory.cur/.tmp: the same bytes on GameCube, separate objects on PC.
#define lbl_3_bss_16C (lbl_3_bss_C8.cur)
#define lbl_3_bss_170 (lbl_3_bss_C8.tmp[0])
#endif
typedef struct { f32 a, b, c, d; } Ent16;
typedef struct {
    f32 x;
    f32 y;
    f32 z;
    u8 pad0C[0x30 - 0xC];
    f32 vx;
    f32 vz;
    u8 pad38[0xD4 - 0x38];
    f32 px;
    f32 pz;
    u8 padDC[0x128 - 0xDC];
    f32 tx;
    u8 pad12C[4];
    f32 tz;
    u8 pad134[0x148 - 0x134];
    f32 h;
    u8 pad14C[0x154 - 0x14C];
    f32 hv;
    u8 pad158[0x1B2 - 0x158];
    s16 n;
    u8 pad1B4[0x205 - 0x1B4];
    u8 st;
    u8 flag;
    u8 pad207[0x268 - 0x207];
} Fld300B8;

extern f32 lbl_3_rodata_C50;
extern f32 lbl_3_rodata_B78;
extern f32 lbl_3_rodata_B68;
extern StarChanceState lbl_3_common_bss_37400;
extern u16 lbl_3_data_81DC[];
extern u8 lbl_3_data_8404[];
extern u8 lbl_3_data_84B8[];
extern s16 lbl_3_data_4924[];
extern f32 lbl_3_data_490C[];
extern Ent14 lbl_3_data_47D0[];
extern f32 lbl_3_rodata_C54;
extern f32 lbl_3_rodata_C48;
extern InMemFielderView g_Fielders[9];
extern s16 lbl_3_data_1C3C[];
extern f32 lbl_3_data_450C[][2];
extern f32 lbl_3_data_4290[]; // [stadium][team] -> x, z
extern f32 lbl_3_rodata_B74;
extern f32 lbl_3_rodata_BA4;
extern u8 lbl_3_data_4900[][3];
extern f32 lbl_3_rodata_BC4;
extern f32 lbl_3_rodata_BC8;
extern f32 lbl_3_rodata_B90;
extern f32 lbl_3_rodata_BB4;
extern f32 lbl_3_rodata_B64;
extern u8 lbl_3_data_4714[][4][6];
extern f32 lbl_3_data_5FC4[];
extern f32 lbl_3_rodata_BCC;
extern StickHistory lbl_3_bss_C8;
extern f32 lbl_3_data_4794[];
extern f32 lbl_3_data_5CDC[];
extern f32 lbl_3_data_5D08[];
extern s16 lbl_3_data_79B4[];
extern f32 lbl_3_rodata_BBC;
extern f32 lbl_3_rodata_B84;
extern f32 lbl_3_rodata_B88;
extern f32 lbl_3_rodata_B6C;
extern f32 lbl_3_rodata_BA8;
extern f32 lbl_3_rodata_BAC;
extern f32 lbl_3_rodata_BB0;
extern f32 lbl_3_rodata_BD0;
extern f32 lbl_3_data_1C44[];
extern s16 lbl_3_data_1C54[];
extern FieldingChangeWork lbl_3_common_bss_34C90;
extern f32 lbl_3_rodata_B94;
extern f32 lbl_3_rodata_B98;
extern f32 lbl_3_rodata_B60;
extern f32 lbl_3_data_4884[];
#include "main/file_80011640.h" // CharMgr lbl_8036E548
extern f32 lbl_3_rodata_B24;
extern f32 lbl_3_rodata_B20;
extern f32 lbl_3_rodata_B9C;
extern f32 lbl_3_rodata_B48;
extern FielderStateEntry lbl_3_data_3C40[];
extern f32 lbl_3_data_4444[]; // base coordinates, (x, z) per base
extern f32 lbl_3_data_4930[];
extern s16 lbl_3_data_49DC[];
extern f32 lbl_3_rodata_BE4;
extern f32 lbl_3_rodata_B8C;
extern f32 lbl_3_rodata_BB8;
extern f32 lbl_3_rodata_CBC;
extern f32 lbl_3_rodata_BDC;
extern f32 lbl_3_rodata_BA0;
extern f32 lbl_3_rodata_BFC;
extern f32 lbl_3_rodata_B7C;
extern f32 lbl_3_rodata_BD8;
extern f32 lbl_3_rodata_C00;
#ifndef TARGET_PC
extern s16 lbl_3_bss_170;
#endif
#ifndef TARGET_PC
extern s16 lbl_3_bss_16C;
#endif
extern s16 lbl_3_data_484C[];
extern f32 lbl_3_rodata_B70;
extern f32 lbl_3_rodata_C24;
extern int __float_nan[];
extern f64 lbl_3_rodata_B30;
extern f64 lbl_3_rodata_B38;
extern f64 lbl_3_rodata_B40;
extern f32 lbl_3_rodata_C38;
extern f32 lbl_3_rodata_B80;
extern f32 lbl_3_data_18984[];
extern f32 lbl_3_rodata_B18;
extern f32 lbl_3_rodata_B1C;
extern f32 lbl_3_rodata_B28[];
extern f32 lbl_3_rodata_BC0;
extern f32 lbl_3_rodata_BD4;
extern f32 lbl_3_rodata_BE0;
extern f32 lbl_3_rodata_BE8;
extern f32 lbl_3_rodata_BEC;
extern f32 lbl_3_rodata_BF0;
extern f32 lbl_3_rodata_BF4;
extern f32 lbl_3_rodata_C04;
extern f32 lbl_3_rodata_C08;
extern f32 lbl_3_data_4848;
extern f32 lbl_3_rodata_C0C;
extern f32 lbl_3_data_46F0;
extern f32 lbl_3_data_46F4;
extern f32 lbl_3_data_21A14[];
extern f32 lbl_3_rodata_C10;
extern f32 lbl_3_rodata_C14;
extern f32 lbl_3_rodata_C18;
extern f32 lbl_3_data_4300[];
extern f32 lbl_3_data_4348[];
extern f32 lbl_3_data_4484[];
extern f32 lbl_3_data_44B4[];
extern f32 lbl_3_rodata_C1C;
extern f32 lbl_3_rodata_C20;
extern f32 lbl_3_rodata_C28;
extern f32 lbl_3_rodata_C2C;
extern f32 lbl_3_rodata_C30;
extern f32 lbl_3_rodata_C34;
extern f32 lbl_3_data_4780[];
extern f32 lbl_3_rodata_C58;
extern f32 lbl_3_rodata_C5C;
extern f32 lbl_3_rodata_C60;
extern f32 lbl_3_rodata_C3C;
extern f32 lbl_3_rodata_C40;
extern f32 lbl_3_rodata_C44;
extern f32 lbl_3_rodata_C4C;
extern GameScores g_Scores;
extern f32 lbl_3_rodata_C64;
extern f32 lbl_3_rodata_C68;
extern f32 lbl_3_data_4618[];
extern s16 lbl_3_data_4638[];
extern f32 lbl_3_data_48C4;
extern s16 lbl_3_data_48C8[][12];
extern f32 lbl_3_rodata_C6C;
extern f32 lbl_3_rodata_C70;
extern f32 lbl_3_rodata_C74;
extern f32 lbl_3_rodata_C78;
extern f32 lbl_3_rodata_C7C;
extern f32 lbl_3_rodata_C80;
extern s16 lbl_3_data_48A4[];
extern u8 lbl_3_data_48F8[];
extern FieldingBoostParams lbl_3_data_4B9C;
extern f32 lbl_3_data_4B98;
extern f32 lbl_3_rodata_C84;
extern f32 lbl_3_rodata_C88;
extern s16 lbl_3_data_7F10[];
extern f32 lbl_3_data_476C[];
extern f32 lbl_3_rodata_C8C;
extern f32 lbl_3_rodata_C90;
extern f32 lbl_3_rodata_C94;
extern f32 lbl_3_rodata_C98;
extern f32 lbl_3_rodata_C9C;
extern f32 lbl_3_rodata_CA0;
extern f32 lbl_3_rodata_CA4;
extern f32 lbl_3_rodata_CA8;
extern f64 lbl_3_rodata_CB0;
extern f32 lbl_3_rodata_CB8;
extern f32 lbl_3_rodata_CC0;
extern u8 lbl_3_data_46F8[];
extern f32 lbl_3_data_4554[][3][2];
extern f32 lbl_3_data_45B4[][2];
extern f32 lbl_3_data_45D4[][2];
extern u8 lbl_3_data_470C[];
extern f32 lbl_3_rodata_CC4;

// Prototypes of functions in other units. These mirror include/game/rep_1838.h,
// UnknownHomes_Game.h and include/main/file_800639BC.h, which can't be included here:
// they pull in UnknownHomes_Game.h, whose typed globals (g_Ball, g_Fielders, ...)
// clash with this file's u8[] views of the same objects.
s16 radToShortAngle(f32 v);
f32 shortAngleToRad_Capped(s16);
void getComponentsFromRad(f32 v, f32* x, f32* y);
void getComponentsFromSAng(s16 ang, f32* x, f32* y);
int RandomInt_Game(int max);
int RandomInt_Game_Range(int min, int max);
f32 game_atan2(f32 x, f32 y);
f32 fn_3_9EFD0(Vec* a, Vec* b, Vec* c, Vec* d);
void fn_3_9F79C(f32 a, f32 b, f32 c, f32* x, f32* y);
#ifdef __MWERKS__
// Returns s16 (rep_1838.h), but the original callers here sign-extend the result again, which CW
// only emits for an int return. The port uses the real prototype.
int fn_3_9FB8C(f32 x, f32 y);
#else
s16 fn_3_9FB8C(f32 x, f32 y);
#endif
s16 fn_3_9FCA4(s16 a, s16 b);
s16 fn_3_9FCF8(s16 a, s16 b);
s16 fn_3_9FD28(s16 ang);
s16 fn_3_9FE6C_normalizeAngle(s16);
f32 fn_3_9FEA8(f32 v);
int calculateLineIntersection(VecXZ* out, VecXZ* a, VecXZ* b);
BOOL checkFieldingStat(int, int, int);
void fn_80063958(s8 index);
s32 fn_800639BC(s8 idx, Vec* a, Vec* b);
BOOL getAnimRelatedCoordinates(s32 index, s32 joint, Vec* out);
s32 fn_3_6D658(s32, s16, s16);
void fn_3_1AE44(u8, u16, f32, f32, f32); // rep_720.h pulls in GameSettings.h
void fn_3_161588(int, s16);
int __abs(int);

#define NAN (*(f32*)__float_nan)

// g_Ball / g_Fielders reached through a pointer expression: the original declared them as byte
// arrays, and a few matched functions only keep their register allocation when read this way.
#define BALL ((InMemBallType*)&g_Ball)
#define FIELDERS ((InMemFielderView*)g_Fielders)
#ifndef ABS
#define ABS(x) ((x) < 0 ? -(x) : (x))
#endif
#define SQRT_L(x)                                                                                  \
    do {                                                                                           \
        if ((x) > 0.0f) {                                                                          \
            f64 xd = (f64)(x);                                                                     \
            f64 guess = __frsqrte(xd);                                                             \
            guess = lbl_3_rodata_B30 * guess * (lbl_3_rodata_B38 - guess * guess * xd);            \
            guess = lbl_3_rodata_B30 * guess * (lbl_3_rodata_B38 - guess * guess * xd);            \
            guess = lbl_3_rodata_B30 * guess * (lbl_3_rodata_B38 - guess * guess * xd);            \
            (x) = (f32)(xd * guess);                                                               \
        } else if ((x) < lbl_3_rodata_B40) {                                                       \
            (x) = NAN;                                                                             \
        } else if (isnan(x)) {                                                                     \
            (x) = NAN;                                                                             \
        }                                                                                          \
    } while (0)
/* squared xz distance, written out so CW does not fuse it into fmadds */
#define DIST2_XZ(ax, az, bx, bz) (((ax) - (bx)) * ((ax) - (bx)) + ((az) - (bz)) * ((az) - (bz)))

static inline void SetFielderAct(int i, int state) {
    InMemFielderView* f = &g_Fielders[i];
    int d;
    if (i != -1) {
        d = lbl_3_data_3C40[state].anim;
        f->_1D3 = state;
        if (d >= 0) {
            g_FieldingLogic._0F8[i] = d;
        }
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_1A4 = 0;
        f->_1AC = 0;
        f->_1FF = 0;
    }
}

static inline void SetFielderAct2(int i, int val, int state) {
    InMemFielderView* f = &g_Fielders[i];
    f->_1D3 = state;
    if (val >= 0) {
        g_FieldingLogic._0F8[i] = val;
    }
    f->_1D5 = 0;
    f->_1D6 = 0;
    f->_1A4 = 0;
    f->_1AC = 0;
    f->_1FF = 0;
}

/* same body as fn_3_33458, which the original inlines into fn_3_34450 */
static inline void PairPlayInline(void) {
    InMemFielderView* f;
    s16 i;
    fn_3_334EC(1);
    fn_3_33088();
    i = g_FieldingLogic._0B2;
    f = &g_Fielders[i];
    if (i != -1) {
        f->_1D3 = 0x16;
        if (lbl_3_data_3C40[22].anim >= 0) {
            g_FieldingLogic._0F8[i] = lbl_3_data_3C40[22].anim;
        }
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_1A4 = 0;
        f->_1AC = 0;
        f->_1FF = 0;
    }
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}

/* point fielder f at (x, z): sets target, heading and remaining distance */
static inline void SetRunTargetInline(InMemFielderView* f, f32 x, f32 z) {
    f32 dx;
    f32 dz;
    f32 d;
    f->_014 = x;
    f->_01C = z;
    dx = x - f->x;
    dz = z - f->z;
    if (lbl_3_rodata_B20 == dx && lbl_3_rodata_B20 == dz) {
        f->_050 = lbl_3_rodata_B20;
        f->_068 = lbl_3_rodata_B20;
    } else {
        f->_064 = (f32)atan2(dz, dx);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        f->_068 = d;
    }
    f->_1D9 = 1;
}

/* frames for fielder f to reach (x, z) */
static inline s32 EtaToInline(InMemFielderView* f, f32 x, f32 z) {
    f32 dx;
    f32 dz;
    f32 d;
    f32 sp;
    if (x == f->x && z == f->z) {
        return 1;
    }
    dx = x - f->x;
    dz = z - f->z;
    d = dx * dx + dz * dz;
    SQRT_L(d);
    sp = f->maxVelocity;
    if (sp == lbl_3_rodata_B20) {
        sp = lbl_3_rodata_B60;
    }
    return (s32)((u32)f->_1D1 >> 1) + (s32)(d / sp);
}

/* same body as fn_3_365D0, inlined into fn_3_361D8 */
static inline int Pick3Inline(int a, int b, int c, f32 x, f32 y) {
    int r = fn_3_36678(b, c, x, y, 1);
    if (r == -1) {
        return a;
    }
    if (g_FieldingLogic._0B0 < 0) {
        return fn_3_36678(a, r, x, y, 1);
    }
    return fn_3_36678(a, r, x, y, 0);
}

static inline void SetFielderActP(InMemFielderView* f, int i, int state) {
    int d;
    if (i != -1) {
        d = lbl_3_data_3C40[state].anim;
        f->_1D3 = state;
        if (d >= 0) {
            g_FieldingLogic._0F8[i] = d;
        }
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_1A4 = 0;
        f->_1AC = 0;
        f->_1FF = 0;
    }
}

/* SetFielderAct that also records the fielder in FieldingLogic+0xBC */
static inline void SetFielderActTag(int i, int state) {
    InMemFielderView* f = &g_Fielders[i];
    int d;
    if (i != -1) {
        d = lbl_3_data_3C40[state].anim;
        f->_1D3 = state;
        if (d >= 0) {
            g_FieldingLogic._0F8[i] = d;
        }
        g_FieldingLogic._0BC = i;
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_1A4 = 0;
        f->_1AC = 0;
        f->_1FF = 0;
    }
}

/* same body as fn_3_258D8, which the original inlines into fn_3_3A584 */
static inline int StartJumpInline(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int type;
    Ent16* t;
    int n;
    int k;
    f32 sc;
    if (g_FieldingLogic.curPadRec->_2 == 0) {
        return 0;
    }
    if (f->_25A != 0) {
        return 0;
    }
    type = f->superJump;
    f->_203 = 1;
    f->_15C = lbl_3_rodata_B20;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (i == 0) {
            i = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        } else {
            i = g_Minigame.minigameControlStruct[0].fieldOrder[i - 2];
        }
    }
    f->_164 = ((Ent16*)lbl_3_data_4884)[type].a;
    t = &((Ent16*)lbl_3_data_4884)[type];
    sc = t->c;
    f->_160 = f->_038 * lbl_3_rodata_B24 * sc;
    f->_168 = f->_03C * lbl_3_rodata_B24 * sc;
    k = (int)t->d;
    n = (int)(f->_164 / t->b);
    f->_1B0 = n + 1;
    f->_1AE = (n + n) + k + 2;
    f->_204 = 0;
    if (type != 0) {
        fn_3_1682AC(lbl_8036E548.active[i], 6);
    }
    g_FieldingLogic.curPadRec->_2 = 0;
    return 1;
}

/* drop fielder i's base assignment (FieldingLogic+0xD0 slots / +0xD8) */
static inline void ReleaseBaseInline(InMemFielderView* f, int i) {
    s16 k = f->_18C;
    if (k >= 0) {
        if (k <= 3) {
            if ((&g_FieldingLogic._0D0[0])[k] == i) {
                (&g_FieldingLogic._0D0[0])[k] = -1;
                g_FieldingLogic._101[k] = 0;
            }
            f->_18C = -1;
            f->_1D7 = 0;
            if (f->_1D3 == 1) {
                SetFielderActP(f, i, 12);
            }
        } else if (k == 5) {
            f->_18C = -1;
            f->_1D7 = 0;
            g_FieldingLogic._0D8 = -1;
            g_FieldingLogic.playerAtMoundCutoffLocation = 0;
            if (f->_1D3 == 14) {
                SetFielderActP(f, i, 12);
            }
        }
    }
}

/* same bodies as fn_3_3C484 / fn_3_3C270, which the original inlines into fn_3_3CCB0 */
static inline int TakeNearBaseInline(int i) {
    InMemFielderView* f = &g_Fielders[i];
    if (f->distToBase[0] < 5.0f) {
        f->_18C = 9;
    } else if (f->distToBase[1] < 5.0f) {
        f->_18C = fn_3_3D7D4(i);
    } else if (f->distToBase[2] < 5.0f) {
        f->_18C = fn_3_3D7D4(i);
    } else if (f->distToBase[3] < 5.0f) {
        f->_18C = fn_3_3D7D4(i);
    } else {
        return 0;
    }
    f->_1D7 = 2;
    if (i != -1) {
        int v;
        f->_1D3 = 0xE;
        v = lbl_3_data_3C40[14].anim;
        if (v >= 0) {
            g_FieldingLogic._0F8[i] = v;
        }
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_1A4 = 0;
        f->_1AC = 0;
        f->_1FF = 0;
    }
    f->_1D6 = 0xB;
    return 1;
}

static inline int GoHomeInline(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 tx;
    f32 tz;
    f32 dz;
    f32 dx;
    f32 d;
    f32 a2;
    f32 b2;
    f->_18C = 0xE;
    f->_1D7 = 2;
    if (i != -1) {
        f->_1D3 = 0xE;
        if (lbl_3_data_3C40[14].anim >= 0) {
            g_FieldingLogic._0F8[i] = lbl_3_data_3C40[14].anim;
        }
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_1A4 = 0;
        f->_1AC = 0;
        f->_1FF = 0;
    }
    f->_1D6 = 0xB;
    tx = lbl_3_data_4444[8];
    tz = lbl_3_data_4444[9];
    f->_014 = tx;
    f->_01C = tz;
    dx = tx - f->x;
    dz = tz - f->z;
    if (0.0f == dx && 0.0f == dz) {
        f->_050 = 0.0f;
        f->_068 = 0.0f;
    } else {
        f->_064 = (f32)atan2(dz, dx);
        a2 = dz * dz;
        d = dx * dx + a2;
        SQRT_L(d);
        f->_068 = d;
    }
    f->_1D9 = 1;
    return 1;
}

// Inlined copy of fn_3_52560 (frames for fielder i to reach x/z); defined later in this file.
static inline int FramesToReachAC8(int i, f32 x, f32 z) {
    InMemFielderView* f = &g_Fielders[i];
    f32 d;
    f32 spd;
    if (x == f->x && z == f->z) {
        return 1;
    }
    d = (x - f->x) * (x - f->x) + (z - f->z) * (z - f->z);
    SQRT_L(d);
    spd = f->maxVelocity;
    return ((u32)f->_1D1 >> 1) + (int)(d / (lbl_3_rodata_B20 == spd ? lbl_3_rodata_B60 : spd));
}

// Fielder i goes to cover its assigned base (0x18C), or relays/backs up.
static inline void FielderGoCoverAC8(int i) {
    InMemFielderView* f = &g_Fielders[i];
    if (f->_1D7 == 1) {
        SetFielderAct(i, 1);
        g_FieldingLogic._0D0[f->_18C] = i;
    } else if (f->_18C == 6) {
        SetFielderAct(i, 0xB);
    } else {
        SetFielderAct(i, 0xC);
        f->_1D5 = 4;
    }
}

// Fielder i stops covering its base (0x18C), clearing the base's cover slot if it held it.
static inline void FielderReleaseCoverAC8(int i) {
    InMemFielderView* f = &g_Fielders[i];
    s16 t = f->_18C;
    if (t < 0) {
        return;
    }
    if (t <= 3) {
        if (g_FieldingLogic._0D0[t] == i) {
            g_FieldingLogic._0D0[t] = -1;
            g_FieldingLogic._101[t] = 0;
        }
        f->_18C = -1;
        f->_1D7 = 0;
        if (f->_1D3 == 1) {
            SetFielderAct(i, 0xC);
        }
    } else if (t == 5) {
        f->_18C = -1;
        f->_1D7 = 0;
        g_FieldingLogic._0D8 = -1;
        g_FieldingLogic.playerAtMoundCutoffLocation = 0;
        if (f->_1D3 == 0xE) {
            SetFielderAct(i, 0xC);
        }
    }
}

// After becoming the ball chaser, fielder i runs fn_3_48480 and gives up any base it was covering.
static inline void FielderTakeOverAC8(int i) {
    fn_3_48480(i);
    if (g_FieldingLogic._0D8 != i && g_Fielders[i]._18C < 0) {
        return;
    }
    FielderReleaseCoverAC8(i);
}

static inline void SetTargetAC8(int i, f32 x, f32 z) {
    InMemFielderView* f = &g_Fielders[i];
    f32 dx;
    f32 dz;
    f32 d;
    f->_014 = x;
    f->_01C = z;
    dx = x - f->x;
    dz = z - f->z;
    if (0.0f == dx && 0.0f == dz) {
        f->_050 = 0.0f;
        f->_068 = 0.0f;
    } else {
        f->_064 = atan2(dz, dx);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        f->_068 = d;
    }
    f->_1D9 = 1;
}

// same body as fn_3_4CFB0: aim the pitcher (fielder 0) at the base he covers
static inline void PitcherCoverInl(void) {
    int st = g_Fielders[0]._18C;
    f32 x;
    f32 z;
    f32 d;
    if (st == 1) {
        d = lbl_3_data_4444[2] - g_Fielders[0].x;
        if (d > 15.0f) {
            d = 15.0f;
        }
        x = lbl_3_data_4444[2];
        d = d / lbl_3_rodata_B78;
        z = lbl_3_data_4444[3] - d;
    } else if (st == 3) {
        d = g_Fielders[0].x - lbl_3_data_4444[6];
        if (d > 15.0f) {
            d = 15.0f;
        }
        x = lbl_3_data_4444[6];
        d = d / lbl_3_rodata_B78;
        z = lbl_3_data_4444[7] - d;
    } else {
        x = lbl_3_data_4444[st * 2];
        z = (lbl_3_data_4444 + 1)[st * 2];
    }
    SetTargetAC8(0, x, z);
}

// same body as fn_3_530EC: stop fielder i where it stands
static inline void StopFielderInl(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f->_014 = f->x;
    f->_018 = f->y;
    f->_01C = f->z;
    f->_030 = lbl_3_rodata_B20;
    f->_034 = lbl_3_rodata_B20;
    f->_050 = lbl_3_rodata_B20;
    f->_068 = lbl_3_rodata_B20;
}

// same body as fn_3_51DF0: infield zone of point (x, z)
static inline int FieldZoneInl(f32 x, f32 z) {
    f32 d;
    f32 xx;
    if (40.0f + (x - z) > 0.0f && 40.0f + (-x - z) > 0.0f) {
        return 0;
    }
    xx = x * x;
    d = xx + z * z;
    SQRT_L(d);
    if (d < lbl_3_rodata_C70) {
        return 1;
    }
    z -= lbl_3_rodata_C74;
    d = xx + z * z;
    SQRT_L(d);
    if (d < lbl_3_rodata_C78) {
        return 1;
    }
    if (d < lbl_3_rodata_C7C) {
        return 2;
    }
    if (d < lbl_3_rodata_C80) {
        return 3;
    }
    return 4;
}

// same body as fn_3_4B8D0: fielder i gives up the base it covers
static inline void ReleaseBaseInl(int i) {
    InMemFielderView* f = &g_Fielders[i];
    s16 k = f->_18C;
    if (k >= 0) {
        if (k <= 3) {
            if (g_FieldingLogic._0D0[k] == i) {
                g_FieldingLogic._0D0[k] = -1;
                g_FieldingLogic._101[k] = 0;
            }
            f->_18C = -1;
            f->_1D7 = 0;
            if (f->_1D3 == 1 && i != -1) {
                f->_1D3 = 0xC;
                if (lbl_3_data_3C40[12].anim >= 0) {
                    g_FieldingLogic._0F8[i] = lbl_3_data_3C40[12].anim;
                }
                f->_1D5 = 0;
                f->_1D6 = 0;
                f->_1A4 = 0;
                f->_1AC = 0;
                f->_1FF = 0;
            }
        } else if (k == 5) {
            f->_18C = -1;
            f->_1D7 = 0;
            g_FieldingLogic._0D8 = -1;
            g_FieldingLogic.playerAtMoundCutoffLocation = 0;
            if (f->_1D3 == 0xE && i != -1) {
                f->_1D3 = 0xC;
                if (lbl_3_data_3C40[12].anim >= 0) {
                    g_FieldingLogic._0F8[i] = lbl_3_data_3C40[12].anim;
                }
                f->_1D5 = 0;
                f->_1D6 = 0;
                f->_1A4 = 0;
                f->_1AC = 0;
                f->_1FF = 0;
            }
        }
    }
}

// same body as fn_3_555AC: which baseline corner (1-4) fielder i stands in, 0 if none
static inline void CornerZoneInl(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 lo;
    f32 hi;
    f->_1DE = 0;
    if ((f->z) > lbl_3_rodata_C18) {
        return;
    }
    if ((f->z) < lbl_3_rodata_C88) {
        return;
    }
    if ((f->x) > lbl_3_rodata_B90) {
        return;
    }
    if ((f->x) < lbl_3_rodata_CB8) {
        return;
    }
    if ((f->z) > lbl_3_data_4444[3]) {
        lo = lbl_3_data_4444[5] - lbl_3_rodata_B68;
        hi = lbl_3_rodata_B8C + lbl_3_data_4444[5];
        if ((f->x) > lbl_3_rodata_B20) {
            if ((f->z) > -(f->x) + lo && (f->z) < -(f->x) + hi) {
                f->_1DE = 2;
            }
        } else {
            if ((f->z) > (f->x) + lo && (f->z) < (f->x) + hi) {
                f->_1DE = 3;
            }
        }
    } else {
        lo = lbl_3_data_4444[1] - lbl_3_rodata_B8C;
        hi = lbl_3_rodata_B68 + lbl_3_data_4444[1];
        if ((f->x) > lbl_3_rodata_B20) {
            if ((f->z) > (f->x) + lo && (f->z) < (f->x) + hi) {
                f->_1DE = 1;
            }
        } else {
            if ((f->z) > -(f->x) + lo && (f->z) < -(f->x) + hi) {
                f->_1DE = 4;
            }
        }
    }
}

static inline int StartDiveInl(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int type;
    Ent16* t;
    int n;
    int k;
    f32 sc;
    if (f->_203 != 0) {
        return 0;
    }
    if (g_FieldingLogic.curPadRec->_2 == 0) {
        return 0;
    }
    if (f->_25A != 0) {
        return 0;
    }
    type = f->superJump;
    f->_203 = 1;
    f->_15C = lbl_3_rodata_B20;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (i == 0) {
            i = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        } else {
            i = g_Minigame.minigameControlStruct[0].fieldOrder[i - 2];
        }
    }
    f->_164 = ((Ent16*)lbl_3_data_4884)[type].a;
    t = &((Ent16*)lbl_3_data_4884)[type];
    sc = t->c;
    f->_160 = f->_038 * lbl_3_rodata_B24 * sc;
    f->_168 = f->_03C * lbl_3_rodata_B24 * sc;
    k = (int)t->d;
    n = (int)(f->_164 / t->b);
    f->_1AE = (n + n) + k + 2;
    f->_1B0 = n + 1;
    f->_204 = 0;
    if (type != 0) {
        fn_3_1682AC(lbl_8036E548.active[i], 6);
    }
    g_FieldingLogic.curPadRec->_2 = 0;
    return 1;
}

#pragma dont_inline on

// .text:0x000251E4 size:0x1C0 mapped:0x80664278
void fn_3_251E4(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 pos[3];
    int r;
    if (f->_1BE < 0x7FFE) {
        f->_1BE = f->_1BE + 1;
    } else {
        f->_1BE = 0x7FFF;
    }
    f->_1C0 = f->_1C0 - 1;
    if (f->_210 == 1) {
        if (f->_1C0 <= 0) {
            f->_210 = 2;
            f->_1BE = 0;
            f->_1C0 = lbl_3_data_49DC[0x22];
            return;
        }
        f->_174 = f->_174 * lbl_3_data_4930[35];
        f->_050 = f->_174;
        getComponentsFromSAng(f->_1C2, &f->_038, &f->_03C);
        f->_030 = f->_038 * f->_050;
        f->_034 = f->_03C * f->_050;
        r = fn_3_51798(i, pos);
        if (r != 0) {
            if (r == 2 && !(pos[0] > lbl_3_rodata_B18) && !(pos[0] < lbl_3_rodata_B1C)) {
                f->_030 = pos[0] - f->x;
                f->_034 = pos[2] - f->z;
                f->x = pos[0];
                f->z = pos[2];
            } else {
                f->_050 = lbl_3_rodata_B20;
                f->_030 = lbl_3_rodata_B20;
                f->_034 = lbl_3_rodata_B20;
            }
        } else {
            f->x = f->x + f->_030;
            f->z = f->z + f->_034;
        }
        f->_014 = f->x;
        f->_01C = f->z;
        return;
    }
    if (f->_1C0 <= 0) {
        f->_210 = 0;
    }
}

// .text:0x000253A4 size:0x2A4 mapped:0x80664438
int fn_3_253A4(int i, s16 ang) {
    InMemFielderView* f = &g_Fielders[i];
    if (f->_207 != 0 || f->_205 != 0 || f->_25E != 0) {
        return 0;
    }
    f->_1C2 = ang;
    f->_210 = 1;
    f->_1BE = 0;
    f->_1C0 = lbl_3_data_49DC[0x21];
    f->_174 = lbl_3_data_4930[34];
    if (f->_252 == 4 || f->_252 == 5) {
        f->_174 = lbl_3_rodata_B20;
    }
    if (f->_207 != 0) {
        f->_174 = lbl_3_rodata_B20;
    }
    if (g_d_GameSettings.minigamesEnabled != 0) {
        u8* m = (u8*)&g_Minigame + f->_20D; // player _20D's bytes at [0] below
        if (((MiniGameStruct*)m)->minigameControlStruct[0].battingHandedness[0] == 0) {
            fn_3_6C854(((MiniGameStruct*)m)->minigameControlStruct[0].characterIndex[0], 2);
        }
    } else if (g_GameLogic._13E[g_GameLogic.teamFielding] == 0) {
        fn_3_6C854(g_GameLogic.teamFielding, 2);
    }
    fn_3_90220(f->charID, 10);
    if (g_Ball.fielderWBallIndex == i) {
        fn_3_A9354(i, 1);
        g_FieldingLogic._13B = 1;
        g_FieldingLogic._111 = 0;
    }
    if (f->_252 != 0) {
        if (g_d_GameSettings.GameModeSelected != 6 && i != g_FieldingLogic._0B0 && i != -1) {
            f->_1D3 = 0xC;
            if (lbl_3_data_3C40[12].anim >= 0) {
                g_FieldingLogic._0F8[i] = lbl_3_data_3C40[12].anim;
            }
            f->_1D5 = 0;
            f->_1D6 = 0;
            f->_1A4 = 0;
            f->_1AC = 0;
            f->_1FF = 0;
        }
        f->_252 = 0;
        f->_050 = lbl_3_rodata_B20;
        f->_194 = 0;
        f->_1E9 = 0;
        f->_1DF = 0;
        f->_205 = 0;
        f->_25E = 0;
        if (f->_1E8 != 0) {
            f->_1E8 = 2;
        }
        if (g_Ball.fielderWBallIndex >= 0 && g_Ball.catchAnimationTotalFrames != 0) {
            g_Ball.catchAnimationTotalFrames = 0;
            g_Ball.AtBat_Contact_BallPos.x = g_Ball.fielderActionCatchCoords.x;
            g_Ball.AtBat_Contact_BallPos.y = g_Ball.fielderActionCatchCoords.y;
            g_Ball.AtBat_Contact_BallPos.z = g_Ball.fielderActionCatchCoords.z;
        }
    }
    f->_262 = 0;
    f->_203 = 0;
    f->_20F = 0;
    f->_1EE = 0;
    g_Ball.catchAnimationTotalFrames = 0;
    return 1;
}

// .text:0x00025648 size:0x1FC mapped:0x806646DC
void fn_3_25648(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 pos[3];
    int r;
    f->_1BA = f->_1BA - 1;
    if (f->_1BA <= 0) {
        f->_20F = 0;
        f->_050 = lbl_3_rodata_B20;
        f->_030 = lbl_3_rodata_B20;
        f->_034 = lbl_3_rodata_B20;
        return;
    }
    f->_1B8 = f->_1B8 + 1;
    f->_1BC = fn_3_9FE6C_normalizeAngle(f->_1BC + lbl_3_data_49DC[0x20]);
    f->_050 = lbl_3_data_4930[33];
    getComponentsFromSAng(f->_1BC, &f->_038, &f->_03C);
    f->_030 = f->_038 * f->_050;
    f->_034 = f->_03C * f->_050;
    r = fn_3_51798(i, pos);
    if (r != 0) {
        if (r == 2 && !(pos[0] > lbl_3_rodata_B18) && !(pos[0] < lbl_3_rodata_B1C)) {
            f->_030 = pos[0] - f->x;
            f->_034 = pos[2] - f->z;
            f->x = pos[0];
            f->z = pos[2];
        } else {
            f->_050 = lbl_3_rodata_B20;
            f->_030 = lbl_3_rodata_B20;
            f->_034 = lbl_3_rodata_B20;
        }
    } else {
        f->x = f->x + f->_030;
        f->z = f->z + f->_034;
    }
    f->_014 = f->x;
    f->_01C = f->z;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        u8* m = (u8*)&g_Minigame + f->_20D; // player _20D's bytes at [0] below
        if (((MiniGameStruct*)m)->minigameControlStruct[0].battingHandedness[0] == 0) {
            fn_3_6C854(((MiniGameStruct*)m)->minigameControlStruct[0].characterIndex[0], 0);
        }
    } else if (g_GameLogic._13E[g_GameLogic.teamFielding] == 0) {
        fn_3_6C854(g_GameLogic.teamFielding, 0);
    }
}

// .text:0x00025844 size:0x94 mapped:0x806648D8
void fn_3_25844(int i, int j) {
    InMemFielderView* f = &g_Fielders[i];
    if (f->_20F == 0) {
        f->_1BC = radToShortAngle(f->_048);
        f->_20F = 1;
        f->_1B8 = 0;
        f->_1BA = lbl_3_data_49DC[j + 0x1D];
        f->_252 = 0;
        f->_203 = 0;
        f->_205 = 0;
        f->_207 = 0;
        f->_1EE = 0;
    }
}

// .text:0x000258D8 size:0x190 mapped:0x8066496C
// ~60%: type reg r7 vs r8, lfsx table access, float op order/scheduling differ
int fn_3_258D8(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int type;
    Ent16* t;
    int n;
    int k;
    f32 sc;
    if (g_FieldingLogic.curPadRec->_2 == 0) {
        return 0;
    }
    if (f->_25A != 0) {
        return 0;
    }
    type = f->superJump;
    f->_203 = 1;
    f->_15C = lbl_3_rodata_B20;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (i == 0) {
            i = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        } else {
            i = g_Minigame.minigameControlStruct[0].fieldOrder[i - 2];
        }
    }
    f->_164 = ((Ent16*)lbl_3_data_4884)[type].a;
    t = &((Ent16*)lbl_3_data_4884)[type];
    sc = t->c;
    f->_160 = f->_038 * lbl_3_rodata_B24 * sc;
    f->_168 = f->_03C * lbl_3_rodata_B24 * sc;
    k = (int)t->d;
    n = (int)(f->_164 / t->b);
    f->_1AE = (n + n) + k + 2;
    f->_1B0 = n + 1;
    f->_204 = 0;
    if (type != 0) {
        fn_3_1682AC(lbl_8036E548.active[i], 6);
    }
    g_FieldingLogic.curPadRec->_2 = 0;
    return 1;
}

// .text:0x00025A68 size:0x1D8 mapped:0x80664AFC
void fn_3_25A68(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 d;
    f32 pos[1];
    f->_228 = f->_228 * lbl_3_rodata_B28[0];
    f->_230 = f->_230 * lbl_3_rodata_B28[0];
    f->_030 = f->_228;
    f->_034 = f->_230;
    d = f->_030 * f->_030 + f->_034 * f->_034;
    SQRT_L(d);
    f->_050 = d;
    if (fn_3_51798(i, pos) != 0) {
        f->x = f->_0D4;
        f->z = f->_0D8;
        f->_050 = 0.0f;
        f->_030 = 0.0f;
        f->_034 = 0.0f;
    } else {
        f->x = f->x + f->_030;
        f->z = f->z + f->_034;
    }
    f->_014 = f->x;
    f->_01C = f->z;
    f->_1F0 = 1;
}

// .text:0x00025C40 size:0x5A8 mapped:0x80664CD4
// NONMATCHING 88%: float register allocation and lhax/lfsu addressing of the pitch table / ball position differ
#if NONMATCHING
void fn_3_25C40(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int who = i;
    Vec v;
    f32 dx;
    f32 dz;
    f32 dy;
    f32 d;
    f32 t;
    s16 cnt;
    s16* tbl;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (i == 0) {
            who = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        } else {
            who = g_Minigame.minigameControlStruct[0].fieldOrder[i - 2];
        }
    }
    if (g_Ball.catchAnimationTotalFrames == 0) {
        if (f->_252 == 3) {
            if (f->_24C > lbl_3_data_49DC[0x1A]) {
                return;
            }
            dz = f->_224 - f->z;
            dx = f->_21C - f->x;
            d = dx * dx + dz * dz;
            SQRT_L(d);
            tbl = lbl_3_data_79B4 + f->charID * 8;
            t = lbl_3_rodata_B48 * tbl[4] / d;
            g_Ball.diveCatchLocationOffset.y = lbl_3_rodata_B48 * tbl[7];
            dx *= t;
            dz *= t;
            g_Ball.diveCatchLocationOffset.x = f->x + dx;
            g_Ball.diveCatchLocationOffset.z = f->z + dz;
        } else {
            if (f->_24C > lbl_3_data_49DC[0x18]) {
                return;
            }
            dz = f->_224 - f->z;
            dx = f->_21C - f->x;
            d = dx * dx + dz * dz;
            SQRT_L(d);
            tbl = lbl_3_data_79B4 + f->charID * 8;
            t = lbl_3_rodata_B48 * tbl[0] / d;
            dx *= t;
            dz *= t;
            g_Ball.diveCatchLocationOffset.x = f->x + dx;
            g_Ball.diveCatchLocationOffset.z = f->z + dz;
            g_Ball.diveCatchLocationOffset.y = lbl_3_rodata_B48 * tbl[2];
        }
        g_Ball.fielderActionCatchCoords.x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.fielderActionCatchCoords.y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.fielderActionCatchCoords.z = g_Ball.AtBat_Contact_BallPos.z;
        g_Ball.catchAnimationTotalFrames = f->_24C;
        if (f->_265 == 0 && f->_252 == 3) {
            f->_24C = lbl_3_data_49DC[0x25];
            g_Ball.catchAnimationTotalFrames = lbl_3_data_49DC[0x25];
        }
        g_Batter.invisibleBallForPeachStarHit = 0;
    } else {
        if (f->_265 != 0) {
            getAnimRelatedCoordinates(who, 0x42, &v);
            v.y = -v.y;
        } else if (f->_252 == 3) {
            v.x = g_Ball.diveCatchLocationOffset.x;
            v.y = g_Ball.diveCatchLocationOffset.y;
            v.z = g_Ball.diveCatchLocationOffset.z;
        } else if (f->handedness == 0) {
            getAnimRelatedCoordinates(who, 0x4F, &v);
        } else {
            getAnimRelatedCoordinates(who, 0x4E, &v);
        }
        cnt = f->_24C;
        t = (f32)cnt / (f32)g_Ball.catchAnimationTotalFrames;
        dy = g_Ball.AtBat_Contact_BallPos.y - v.y;
        dx = g_Ball.AtBat_Contact_BallPos.x - v.x;
        dz = g_Ball.AtBat_Contact_BallPos.z - v.z;
        dy *= t;
        dx *= t;
        dz *= t;
        g_Ball.fielderActionCatchCoords.y = v.y + dy;
        g_Ball.fielderActionCatchCoords.x = v.x + dx;
        g_Ball.fielderActionCatchCoords.z = v.z + dz;
        if (cnt == 1) {
            g_Ball.catchAnimationTotalFrames = 0;
        }
        g_Ball.fielderActionOccuring = 1;
    }
}
#endif

// .text:0x000261E8 size:0x47C mapped:0x8066527C
// NONMATCHING 98%: load order of 0x12C/0x148 in the height lerp and one f0/f1 swap
#if NONMATCHING
void fn_3_261E8(int i) {
    InMemFielderView* f = &g_Fielders[i];
    Vec v;
    f32 n;
    f32 h;
    f32 d;
    int hit;
    s16 cnt = f->_24C;
    if (f->_252 == 4) {
        if (f->_25C != 0) {
            n = f->_25C;
            f->_228 = (f->_128 - f->x) / n;
            f->_230 = (f->_130 - f->z) / n;
            f->_148 += (f->_12C - f->_148) / n;
            f->_25C = f->_25C - 1;
            if (f->_25C == 0) {
                fn_3_90220(f->charID, 0);
            }
        } else {
            n = cnt;
            f->_228 = (f->_134 - f->x) / n;
            f->_230 = (f->_13C - f->z) / n;
            h = (f->_138 - f->_148) / n;
            f->_164 = h;
            f->_148 += h;
        }
    } else if (f->_24E <= 1) {
        f->_228 = 0.0f;
        f->_22C = 0.0f;
        f->_230 = 0.0f;
        if (f->_252 == 3 || f->_252 == 7 || f->_252 == 8) {
            if (checkFieldingStat(g_GameLogic.teamFielding, f->rosterID, 7) != 0 && f->_252 == 3 && f->_25B == 0) {
                f->_228 = 0.0f;
                f->_230 = 0.0f;
            } else {
                v.x = f->_21C - f->x;
                v.z = f->_224 - f->z;
                f->_228 = v.x / f->_24C;
                f->_230 = v.z / f->_24C;
                if (f->_252 == 7 || f->_252 == 8) {
                    f->_262 = lbl_3_data_49DC[0x15];
                }
            }
        }
    }
    if (checkFieldingStat(g_GameLogic.teamFielding, f->rosterID, 7) != 0 || f->_265 != 0) {
        if (f->_25B == 0) {
            fn_3_25C40(i);
        }
    } else {
        f->x = f->x + f->_228;
        f->y = f->y + f->_22C;
        f->z = f->z + f->_230;
        f->_030 = f->_228;
        f->_034 = f->_230;
        d = f->_030 * f->_030 + f->_034 * f->_034;
        SQRT_L(d);
        f->_050 = d;
    }
    hit = fn_3_51798(i, &v.x);
    if (hit == 1) {
        f->_25B = 1;
        g_Ball.catchAnimationTotalFrames = 0;
    }
    if (hit != 0) {
        f->x = f->_0D4;
        f->z = f->_0D8;
        f->_050 = 0.0f;
        f->_030 = 0.0f;
        f->_034 = 0.0f;
    }
    if (f->_050 > 0.0f) {
        f->_038 = f->_030 / f->_050;
        f->_03C = f->_034 / f->_050;
    } else {
        f->_03C = 0.0f;
        f->_038 = 0.0f;
    }
}
#endif

// .text:0x00026664 size:0x410 mapped:0x806656F8
void fn_3_26664(int i) {
    int who = i;
    InMemFielderView* f = &g_Fielders[i];
    int mode;
    int pct;
    f->_258 = 0;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (i == 0) {
            who = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        } else {
            who = g_Minigame.minigameControlStruct[0].fieldOrder[i - 2];
        }
    }
    if ((g_d_GameSettings.GameModeSelected != 2 || g_Practice.instructionNumber < 0) && g_Ball.numFieldersWhoHandledBallDuringPlay == 0 && g_Ball.hitWallInd == 0) {
        if (g_Ball.framesOnGroundUntilPickedUp < 5) {
            goto go;
        }
    }
    return;
go:
    if (checkFieldingStat(g_GameLogic.teamFielding, f->rosterID, 10) != 0) {
        fn_3_1682AC(lbl_8036E548.active[who], 10);
        playSoundEffect(0x1A8);
        return;
    }
    mode = 0;
    if (g_d_GameSettings.GameModeSelected == 6) {
        mode = 1;
    }
    if (g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0) {
        if (f->_259 != 0) {
            pct = lbl_3_data_4714[mode][f->characterClass][5];
        } else if (f->_260 != 0) {
            pct = lbl_3_data_4714[mode][f->characterClass][4];
        } else if (f->_254 == 0) {
            pct = lbl_3_data_4714[mode][f->characterClass][3];
        } else {
            pct = lbl_3_data_4714[mode][f->characterClass][4];
        }
        if (i == 0) {
            pct *= 2;
        }
        pct *= 10;
        if (g_d_GameSettings.exhibitionMatchInd == 0 && g_d_GameSettings.humanTeamNumber == g_GameLogic.teamFielding &&
            (((s8)g_d_GameSettings.challengeCaptainStarBought[3]) != 0 || ((s8)g_d_GameSettings._4F) != 0)) {
            pct = pct * lbl_3_data_5FC4[6];
        }
        if (RandomInt_Game(1000) < pct) {
            f->_258 = 3;
        } else {
            f->_258 = 1;
        }
    } else {
        if (f->_259 != 0) {
            pct = lbl_3_data_4714[mode][f->characterClass][2];
        } else if (f->_260 != 0) {
            pct = lbl_3_data_4714[mode][f->characterClass][1];
        } else if (f->_254 == 0) {
            pct = lbl_3_data_4714[mode][f->characterClass][0];
        } else {
            pct = lbl_3_data_4714[mode][f->characterClass][1];
        }
        pct *= 10;
        if (g_d_GameSettings.exhibitionMatchInd == 0 && g_d_GameSettings.humanTeamNumber == g_GameLogic.teamFielding &&
            (((s8)g_d_GameSettings.challengeCaptainStarBought[3]) != 0 || ((s8)g_d_GameSettings._4F) != 0)) {
            pct = pct * lbl_3_data_5FC4[6];
        }
        if (RandomInt_Game(1000) < pct) {
            f->_258 = 2;
        } else {
            f->_258 = 0;
        }
    }
    g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy = 0;
}

// .text:0x00026A74 size:0xBD4 mapped:0x80665B08
// NONMATCHING 88%: the original inlines fn_3_27764 for the already-caught case; we call it (same behaviour)
// nmverify: fn_3_27764 inlined on one side (calls match once expanded)
#if NONMATCHING
void fn_3_26A74(int i) {
    InMemFielderView* f = &g_Fielders[i];
    InMemRunnerType* r;
    int k;
    int t;
    f32 d;
    f32 spd;
    int stadium;
    int vol;
    int pan;
    u32 vid;
    if (g_Ball.ballState == 1) {
        fn_3_27764(i);
        return;
    }
    if (g_Ball.AtBat_ContactResult == 0 || (g_Ball.framesOnGroundUntilPickedUp == 0 && g_Ball.numberOfThrowsDuringPlay == 0 && g_Ball.numFieldersWhoHandledBallDuringPlay == 1)) {
        if (g_Ball.fairBallInd == -1) {
            if (fn_3_B7E10(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) != 0) {
                g_Ball.fairBallInd = 1;
            } else {
                g_Ball.fairBallInd = 0;
            }
        }
        g_Ball.AtBat_ContactResult = 3;
        if (g_FieldingLogic._108 != 0) {
            g_FieldingLogic._108 = 2;
        }
    } else if (g_Ball.AtBat_ContactResult == 1) {
        if (g_Ball.ballInitialHitDoneInd == 0 && fn_3_B7E10(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) != 0) {
            fn_3_A0F0();
        } else {
            g_Ball.AtBat_ContactResult = 2;
            if (g_FieldingLogic._108 != 0) {
                g_FieldingLogic._108 = 2;
            }
        }
        if (g_Ball.fairBallInd == -1) {
            if (g_Ball.AtBat_ContactResult == -1) {
                g_Ball.fairBallInd = 1;
            } else {
                g_Ball.fairBallInd = 0;
            }
        }
        if (g_Ball.ballState == 0 && g_Ball.AtBat_ContactResult != -1 && g_FieldingLogic._108 == 0 &&
            g_Ball.hangtimeOfHit + 15 > g_Ball.framesSinceHit && g_FieldingLogic._108 == 0 &&
            g_d_GameSettings.GameModeSelected != 6) {
            fn_3_59918(4, 0);
        }
    }
    if (f->_252 == 2) {
        g_FieldingLogic._11F = 1;
    } else {
        g_FieldingLogic._11F = 0;
    }
    if (f->_1D7 == 1) {
        fn_3_5372C(i);
        if (g_FieldingLogic._0D0[f->_18C] == i &&
            g_FieldingLogic._101[f->_18C] == 1) {
            g_Ball.baseBallAndFielderAreOn = f->_18C;
            for (k = 0, r = g_Runners; k < 4; k++, r++) {
                if (r->runnerOnFieldOrOutOrScored == 1) {
                    if (f->_18C == r->baseStandingOn && r->timeStandingOnBase < 120 &&
                        (r->tagUpInd != 2 || r->startingBase_baseAchieved == r->baseStandingOn)) {
                        fn_3_59918(2, 0);
                    }
                } else if (r->runnerOnFieldOrOutOrScored == 3 && f->_18C == 0 && r->timeStandingOnBase < 60) {
                    fn_3_59918(2, 0);
                }
            }
        }
    }
    g_FieldingLogic._114 = f->_259;
    if (((s8)g_FieldingLogic._115) < 0) {
        g_FieldingLogic._115 = f->_259;
    }
    if (g_Ball.numberOfThrowsDuringPlay == 0) {
        if (f->_118 == f->x && f->_11C == f->z) {
            t = 1;
        } else {
            d = DIST2_XZ(f->_118, f->_11C, f->x, f->z);
            SQRT_L(d);
            spd = f->maxVelocity;
            if (0.0f == spd) {
                spd = lbl_3_rodata_B60;
            }
            t = (f->_1D1 >> 1) + (int)(d / spd);
        }
        if (g_Ball.framesSinceHit - t < lbl_3_data_49DC[0x26]) {
            g_FieldingLogic._133 = 1;
        }
    }
    if (g_Ball.AtBat_ContactResult == 3 && g_Ball.numberOfThrowsDuringPlay == 0) {
        if (f->_252 == 4 || f->_252 == 5) {
            g_FieldingLogic._133 = 2;
            g_UnkSound_32718._08 = 4;
            g_FieldingLogic._134 = i;
            if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanPlayer == g_GameLogic.teamFielding &&
                g_Ball.AtBat_ContactResult == 3) {
                fn_3_161588(2, f->rosterID);
            }
        } else if (f->_203 != 0) {
            if (g_Ball.AtBat_Contact_BallPos.y > f->reach[3] + lbl_3_data_4930[38]) {
                g_FieldingLogic._133 = 2;
                g_UnkSound_32718._08 = 4;
                g_FieldingLogic._134 = i;
                if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanPlayer == g_GameLogic.teamFielding &&
                    g_Ball.AtBat_ContactResult == 3) {
                    fn_3_161588(2, f->rosterID);
                }
            }
        } else {
            if (g_FieldingLogic._133 == 1 && f->_259 != 0) {
                g_FieldingLogic._133 = 2;
                g_UnkSound_32718._08 = 4;
                g_FieldingLogic._134 = i;
                if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanPlayer == g_GameLogic.teamFielding &&
                    g_Ball.AtBat_ContactResult == 3) {
                    fn_3_161588(2, f->rosterID);
                }
            }
            if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanPlayer == g_GameLogic.teamFielding &&
                g_Ball.AtBat_ContactResult == 3 && f->_259 == 2) {
                fn_3_161588(3, f->rosterID);
            }
        }
    }
    if (g_Ball.currentStarSwing == 1 || g_Ball.currentStarSwing == 2) {
        f->_1EF = (&g_hitShorts.fireballStunFrames)[g_Batter.lightFireballStunID];
    }
    if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanPlayer == g_GameLogic.teamFielding &&
        g_FieldingLogic._107 == 0) {
        if (g_Ball.numFieldersWhoHandledBallDuringPlay == 0) {
            fn_3_161588(1, f->rosterID);
        }
        if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0 && g_Ball.numberOfThrowsDuringPlay == 0) {
            fn_3_161588(9, f->rosterID);
        }
        if (f->_252 == 6) {
            fn_3_161588(4, f->rosterID);
        } else if (f->_252 == 5) {
            fn_3_161588(5, f->rosterID);
        }
    }
    SetFielderAct(i, 0xA);
    g_FieldingLogic._0B0 = -1;
    if (g_Ball.numberOfThrowsDuringPlay < 0xFE) {
        g_Ball.numberOfThrowsDuringPlay = g_Ball.numberOfThrowsDuringPlay + 1;
    } else {
        g_Ball.numberOfThrowsDuringPlay = 0xFF;
    }
    if (g_Ball.numFieldersWhoHandledBallDuringPlay < 0xFE) {
        g_Ball.numFieldersWhoHandledBallDuringPlay = g_Ball.numFieldersWhoHandledBallDuringPlay + 1;
    } else {
        g_Ball.numFieldersWhoHandledBallDuringPlay = 0xFF;
    }
    g_Ball.AtBat_Contact_BallPos.x = f->x;
    g_Ball.AtBat_Contact_BallPos.y = f->y;
    g_Ball.AtBat_Contact_BallPos.z = f->z;
    g_Ball.physicsSubstruct.velocity.x = 0.0f;
    g_Ball.physicsSubstruct.velocity.y = 0.0f;
    g_Ball.physicsSubstruct.velocity.z = 0.0f;
    g_Ball.physicsSubstruct.acceleration.x = 0.0f;
    g_Ball.physicsSubstruct.acceleration.y = 0.0f;
    g_Ball.physicsSubstruct.acceleration.z = 0.0f;
    g_Ball.ballState = 1;
    g_Ball.fielderWBallIndex = i;
    g_Ball.fielderAboutToGetBall_hasBall = i;
    g_Ball.fielderBeingThrownTo = -1;
    g_Ball.ballIsLooseInd_unused = 0;
    g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt = 0;
    g_Ball.timeSinceBallPickedUp = 0;
    g_Ball.looseBall_5FrameCountdown = 0;
    g_Ball.ballPickedUpCaught.x = f->x;
    g_Ball.ballPickedUpCaught.z = f->z;
    g_Ball.framesOnGroundUntilPickedUp = 0;
    g_Ball.ballInitialHitDoneInd = 1;
    g_Ball.warioWaluGarlicIsActive = 0;
    g_Ball.catchAnimationTotalFrames = 0;
    g_Ball.ballIsRollingIndicator = 0;
    if (g_Ball.ballZoneWhenCaught < 0) {
        g_Ball.ballZoneWhenCaught = g_Ball.ballZoneAwayFromHome;
    }
    if (g_Ball.fielderWithBallIndexStored == -1) {
        g_Ball.fielderWithBallIndexStored = i;
    }
    if (g_Ball.fielderWithBallIndexStored2 == -1) {
        g_Ball.fielderWithBallIndexStored2 = i;
    }
    f->_252 = 0;
    f->_050 = 0.0f;
    f->_194 = 0;
    f->_1E9 = 0;
    f->_1DF = 0;
    f->_215 = 0;
    f->_265 = 0;
    if (f->_1E8 != 0) {
        f->_1E8 = 2;
    }
    g_FieldingLogic._0C4 = -1;
    g_FieldingLogic._0CC = -1;
    g_FieldingLogic._0DE = -1;
    g_FieldingLogic._0DC = g_Ball.baseBallAndFielderAreOn;
    g_FieldingLogic._0E2 = -1;
    g_FieldingLogic._0B0 = -1;
    g_FieldingLogic._0B2 = -1;
    g_FieldingLogic._0B4 = -1;
    g_FieldingLogic._12C = 0;
    g_FieldingLogic._140 = 0;
    g_FieldingLogic._142 = 0;
    g_FieldingLogic._109 = 0;
    g_Batter.invisibleBallForPeachStarHit = 0;
    g_Minigame._19C6 = f->_20D;
    if (g_FieldingLogic._143 == 1) {
        g_FieldingLogic._143 = 2;
    }
    if (g_Ball.currentStarSwing != 0) {
        g_Ball.currentStarSwing = 0;
    }
    if (lbl_800E8558[f->charID]._2 == 0x19) {
        fn_3_16696C();
    }
    fn_3_8FF5C(0x16C, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
    if (g_d_GameSettings.GameModeSelected == 6) {
        stadium = g_d_GameSettings.StadiumID;
        vol = g_d_GameSettings.GameModeSelected == 6 ? lbl_3_data_84B8[0x2C] : lbl_3_data_8404[stadium * 0x1E + 0x2C];
        vid = sndFXStartEx(lbl_3_data_81DC[stadium] + 0x16, vol, 0x3F, 0);
        pan = g_d_GameSettings.GameModeSelected == 6 ? lbl_3_data_84B8[0x2D] : lbl_3_data_8404[stadium * 0x1E + 0x2D];
        sndFXCtrl(vid, 0x5B, pan);
    }
}
#endif

// .text:0x00027648 size:0xF0 mapped:0x806666DC
void fn_3_27648(void) {
    InMemFielderView* f = g_Fielders;
    int i;
    for (i = 0; i < 9; i++) {
        if (f->_252 != 0) {
            f->_25B = 1;
            g_Ball.catchAnimationTotalFrames = 0;
        }
        f++;
    }
}

// .text:0x00027738 size:0x2C mapped:0x806667CC

void fn_3_27738(s32 i) {
    InMemFielderView* f = &g_Fielders[i];
    f->_25B = 1;
    g_Ball.catchAnimationTotalFrames = 0;
}

static inline void Inl27764(int i) {
    InMemFielderView* f = &g_Fielders[i];
    if (g_d_GameSettings.GameModeSelected != 6 && i != g_FieldingLogic._0B0 && i != -1) {
        f->_1D3 = 0xC;
        if (lbl_3_data_3C40[12].anim >= 0) {
            g_FieldingLogic._0F8[i] = lbl_3_data_3C40[12].anim;
        }
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_1A4 = 0;
        f->_1AC = 0;
        f->_1FF = 0;
    }
    f->_252 = 0;
    f->_050 = lbl_3_rodata_B20;
    f->_194 = 0;
    f->_1E9 = 0;
    f->_1DF = 0;
    f->_205 = 0;
    f->_25E = 0;
    if (f->_1E8 != 0) {
        f->_1E8 = 2;
    }
    if (g_Ball.fielderWBallIndex >= 0 && g_Ball.catchAnimationTotalFrames != 0) {
        g_Ball.catchAnimationTotalFrames = 0;
        g_Ball.AtBat_Contact_BallPos.x = g_Ball.fielderActionCatchCoords.x;
        g_Ball.AtBat_Contact_BallPos.y = g_Ball.fielderActionCatchCoords.y;
        g_Ball.AtBat_Contact_BallPos.z = g_Ball.fielderActionCatchCoords.z;
    }
}

// .text:0x00027764 size:0xFC mapped:0x806667F8
void fn_3_27764(int i) {
    Inl27764(i);
}

// .text:0x00027860 size:0x508 mapped:0x806668F4
// The original inlines fn_3_27764 in both cancel branches (Inl27764 is its body)
void fn_3_27860(int i) {
    InMemFielderView* f = &g_Fielders[i];
    u8* m;
    f32 d;
    f->_24C = f->_24C - 1;
    f->_24E = f->_24E + 1;
    if (f->_25B != 0) {
        if (f->_24C <= 0) {
            f->_252 = 0;
        }
    } else if (g_Ball.fielderWBallIndex >= 0) {
        Inl27764(i);
    } else if (g_Ball.deadBallReason != 0) {
        Inl27764(i);
    } else if (f->_24C > 0) {
        if (f->_264 != 0) {
            d = DIST2_XZ(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z, f->x, f->z);
            SQRT_L(d);
            if (d < lbl_3_rodata_B64) {
                g_FieldingLogic._144 = 1;
            }
        }
    } else {
        g_FieldingLogic.curBoost->state = 0;
        g_FieldingLogic.curBoost->fielder = -1;
        g_FieldingLogic.curBoost->timer = -1;
        g_FieldingLogic.curBoost->timer2 = -1;
        if (g_Ball.currentStarSwing == 1 || g_Ball.currentStarSwing == 2) {
            f->_258 = 4;
            fn_3_4DC14(i);
        } else if (f->_258 == 2 || f->_258 == 3) {
            fn_3_4DC14(i);
            if (g_d_GameSettings.minigamesEnabled != 0) {
                m = (u8*)&g_Minigame + f->_20D; // player _20D's bytes at [0] below
                if (((MiniGameStruct*)m)->minigameControlStruct[0].battingHandedness[0] == 0) {
                    fn_3_6C854(((MiniGameStruct*)m)->minigameControlStruct[0].characterIndex[0], 0);
                }
            } else if (g_GameLogic._13E[g_GameLogic.teamFielding] == 0) {
                fn_3_6C854(g_GameLogic.teamFielding, 0);
            }
        } else {
            fn_3_26A74(i);
            if (f->_258 == 0 || f->_258 == 1) {
                if (g_d_GameSettings.minigamesEnabled != 0) {
                    m = (u8*)&g_Minigame + f->_20D; // player _20D's bytes at [0] below
                    if (((MiniGameStruct*)m)->minigameControlStruct[0].battingHandedness[0] == 0) {
                        fn_3_6C854(((MiniGameStruct*)m)->minigameControlStruct[0].characterIndex[0], 0);
                    }
                } else if (g_GameLogic._13E[g_GameLogic.teamFielding] == 0) {
                    fn_3_6C854(g_GameLogic.teamFielding, 0);
                }
            }
        }
    }
}

// .text:0x00027D68 size:0x28C mapped:0x80666DFC
// NONMATCHING 92%: registers only; the loop-invariant height window lo/hi gets f5/f4 instead of f0/f1, shifting every float reg
#if NONMATCHING
int fn_3_27D68(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 h = f->_148;
    f32 hi = lbl_3_rodata_B60 + (f->reach[3] + h);
    f32 lo = f->reach[5] + h;
    CoordAndDist* pt = &g_Ball.physicsSubstruct.futureCoordsAndDist[1];
    int k;
    int n;
    f32 d;
    for (k = 1, n = 10; n != 0; pt++, k++, n--) {
        if (pt->dist < f->_070 && pt->pos.y > lo && pt->pos.y < hi) {
            d = (f->x - pt->pos.x) * (f->x - pt->pos.x) +
                (f->z - pt->pos.z) * (f->z - pt->pos.z);
            SQRT_L(d);
            if (d < f->reach[0]) {
                goto found;
            }
        }
    }
    return 0;
found:
    if (g_Ball.physicsSubstruct.futureCoordsAndDist[k + 1].dist < f->_070) {
        k -= 2;
    } else if (g_Ball.physicsSubstruct.futureCoordsAndDist[k + 2].dist < f->_070) {
        k -= 1;
    }
    if (k < 0) {
        k = 0;
    }
    f->_24C = k;
    f->_24E = 0;
    f->_252 = 5;
    f->_253 = 0;
    f->_254 = 0;
    f->_255 = 0;
    f->_25B = 0;
    f->_259 = 0;
    f->_25C = 0;
    f->_25D = 0;
    f->_25E = 0;
    f->_25F = 0;
    f->_264 = 0;
    f->_260 = 0;
    if (k < g_Ball.framesUntilBallHitsGround) {
        f->_264 = 1;
    }
    g_Ball.catchAnimationTotalFrames = 0;
    fn_3_1AE44(3, 0, g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y,
               g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.z);
    return 1;
}
#endif

#if NONMATCHING
static inline int Inl27FF4(int i) {
    InMemFielderView* f = &g_Fielders[i];
    VecSrcDst seg;
    CollisionStruct hit;
    f32 z, y, x;
    f32 d;
    if ((0.0f == f->_038 && 0.0f == f->_03C) || f->_19A < 0) {
        return 0;
    }
    x = f->x;
    z = f->z;
    y = -lbl_3_data_4930[29];
    seg.src.x = x;
    seg.dst.y = y;
    seg.src.y = y;
    seg.src.z = z;
    seg.dst.x = f->_038 * lbl_3_data_4930[28] + x;
    seg.dst.z = f->_03C * lbl_3_data_4930[28] + z;
    if ((checkCollision(&seg, &hit, 0, 0) & 0x7F) != 2) {
        return 0;
    }
    f->_207 = 1;
    f->_1B4 = lbl_3_data_49DC[7];
    f->_128 = hit.position.x;
    f->_12C = lbl_3_data_4930[29];
    f->_130 = hit.position.z;
    d = hit.normal.x * hit.normal.x + hit.normal.z * hit.normal.z;
    f->_148 = 0.0f;
    SQRT_L(d);
    f->_140 = hit.normal.x / d;
    f->_144 = hit.normal.z / d;
    f->_050 = 0.0f;
    return 1;
}
#endif

// .text:0x00027FF4 size:0x230 mapped:0x80667088
// NONMATCHING 99%: float registers differ in the segment setup (x/z/0x70 scale); body in Inl27FF4, shared with fn_3_2A288
#if NONMATCHING
int fn_3_27FF4(int i) {
    return Inl27FF4(i);
}
#endif

// .text:0x00028224 size:0xA84 mapped:0x806672B8
#define K4930(off) (lbl_3_data_4930[(off) / 4])
// NONMATCHING 80%: the original fully unrolls the two short search loops (11 and 5 steps) and keeps more in saved regs; logic and calls match
#if NONMATCHING
int fn_3_28224(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 height = f->reach[3];
    int k;
    int m;
    int j;
    f32 t0;
    f32 h;
    f32 d;
    f32 dx;
    f32 dz;
    f32 nx;
    f32 nz;
    VecSrcDst seg;
    CollisionStruct hit;
    if ((0.0f == f->_038 && 0.0f == f->_03C) || f->_19A < 0) {
        return 0;
    }
    for (k = lbl_3_data_49DC[2] - 1; k < lbl_3_data_49DC[1]; k++) {
        if (g_Ball.physicsSubstruct.futureCoordsAndDist[k].dist > g_Ball.wallAndBallIntersectionDistFromHome - K4930(0x28)) {
            break;
        }
    }
    if (k < lbl_3_data_49DC[2]) {
        return 0;
    }
    if (g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y < K4930(0x20) + height) {
        return 0;
    }
    if (k < lbl_3_data_49DC[1] &&
        fn_3_9FCF8(fn_3_9FB8C(g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.x - f->x, g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.z - f->z), f->_19A) <= 0x300) {
        f->_128 = g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.x;
        f->_130 = g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.z;
        f->_12C = K4930(0x14);
        d = DIST2_XZ(f->x, f->z, f->_128, f->_130);
        SQRT_L(d);
        if (!(d > K4930(0x10))) {
            dz = f->_130 - f->z;
            dx = f->_128 - f->x;
            seg.src.x = f->x;
            seg.src.z = f->z;
            seg.dst.y = -K4930(0x14);
            seg.src.y = -K4930(0x14);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            seg.dst.x = (dx / d) * K4930(0x10) + f->x;
            seg.dst.z = (dz / d) * K4930(0x10) + f->z;
            if ((checkCollision(&seg, &hit, 0, 0) & 0x7F) != 2) {
                return 0;
            }
            /* step back to the first frame the ball is still within reach time-wise */
            t0 = g_Ball.physicsSubstruct.futureCoordsAndDist[k].dist - K4930(0x30);
            for (m = k, j = 0; j < 11; j++, m--) {
                if (t0 < g_Ball.physicsSubstruct.futureCoordsAndDist[m].dist) {
                    break;
                }
            }
            h = height + K4930(0x24);
            k = m;
            for (j = 0; j < 5; j++) {
                if (k < lbl_3_data_49DC[2]) {
                    break;
                }
                if (g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y > h && j != 0) {
                    k++;
                    break;
                }
                k--;
            }
            f->_24C = k;
            f->_134 = g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.x;
            f->_138 = g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y - lbl_3_rodata_B68;
            f->_13C = g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.z;
            f->_134 = (g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.x / g_Ball.physicsSubstruct.futureCoordsAndDist[k].dist) * K4930(0x30) + f->_134;
            f->_13C = (g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.z / g_Ball.physicsSubstruct.futureCoordsAndDist[k].dist) * K4930(0x30) + f->_13C;
            f->_140 = game_atan2(f->_128 - f->x, f->_130 - f->z);
            f->_144 = game_atan2(-f->_128, -f->_130);
            f->_148 = 0.0f;
            if (g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y > K4930(0x24) + f->reach[3]) {
                f->_138 = K4930(0x24);
                f->_24C = k;
                f->_24E = 0;
                f->_252 = 4;
                f->_253 = 0;
                f->_254 = 0;
                f->_255 = 0;
                f->_25B = 1;
                f->_259 = 0;
                f->_25C = 0;
                f->_25D = 0;
                f->_25E = 0;
                f->_25F = 0;
                f->_264 = 0;
                f->_260 = 0;
                if (k < g_Ball.framesUntilBallHitsGround) {
                    f->_264 = 1;
                }
                f->_259 = 3;
                g_Ball.catchAnimationTotalFrames = 0;
            } else {
                f->_138 = g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y - f->reach[3];
                f->_24C = k;
                f->_24E = 0;
                f->_252 = 4;
                f->_253 = 0;
                f->_254 = 0;
                f->_255 = 0;
                f->_25B = 0;
                f->_259 = 0;
                f->_25C = 0;
                f->_25D = 0;
                f->_25E = 0;
                f->_25F = 0;
                f->_264 = 0;
                f->_260 = 0;
                if (k < g_Ball.framesUntilBallHitsGround) {
                    f->_264 = 1;
                }
                f->_259 = 3;
                g_Ball.catchAnimationTotalFrames = 0;
            }
            f->_25C = lbl_3_data_49DC[3];
            fn_3_1AE44(2, 0, g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y, g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.z);
            return 1;
        }
    }
    seg.src.x = f->x;
    seg.src.y = -K4930(0x14);
    seg.src.z = f->z;
    seg.dst.x = f->_038 * K4930(0x10) + f->x;
    seg.dst.y = -K4930(0x14);
    seg.dst.z = f->_03C * K4930(0x10) + f->z;
    if ((checkCollision(&seg, &hit, 0, 0) & 0x7F) != 2) {
        return 0;
    }
    f->_128 = hit.position.x;
    f->_130 = hit.position.z;
    f->_12C = K4930(0x14);
    d = hit.normal.x * hit.normal.x + hit.normal.z * hit.normal.z;
    SQRT_L(d);
    nx = hit.normal.x / d;
    nz = hit.normal.z / d;
    nx *= K4930(0x18);
    nz *= K4930(0x18);
    f->_134 = f->_128 + nx;
    f->_138 = f->_12C + K4930(0x20);
    f->_13C = f->_130 + nz;
    f->_140 = game_atan2(f->_128 - f->x, f->_130 - f->z);
    f->_144 = game_atan2(nx, nz);
    f->_148 = 0.0f;
    f->_24C = k;
    f->_24E = 0;
    f->_252 = 4;
    f->_253 = 0;
    f->_254 = 0;
    f->_255 = 0;
    f->_25B = 1;
    f->_259 = 0;
    f->_25C = 0;
    f->_25D = 0;
    f->_25E = 0;
    f->_25F = 0;
    f->_264 = 0;
    f->_260 = 0;
    if (k < g_Ball.framesUntilBallHitsGround) {
        f->_264 = 1;
    }
    f->_259 = 3;
    g_Ball.catchAnimationTotalFrames = 0;
    f->_25C = lbl_3_data_49DC[3];
    return 1;
}
#endif
#undef K4930

// .text:0x00028CA8 size:0x14BC mapped:0x80667D3C
/* Sets the fielder's catch state (252) and resets the per-catch flags. */
#define SET_CATCH(f, k, st, jump)                                                                                      \
    do {                                                                                                               \
        (f)->_24C = (k);                                                                                    \
        (f)->_24E = 0;                                                                                      \
        (f)->_252 = (st);                                                                                             \
        (f)->_253 = 0;                                                                                                \
        (f)->_254 = 0;                                                                                                \
        (f)->_255 = 0;                                                                                                \
        (f)->_25B = (jump);                                                                                           \
        (f)->_259 = 0;                                                                                                \
        (f)->_25C = 0;                                                                                                \
        (f)->_25D = 0;                                                                                                \
        (f)->_25E = 0;                                                                                                \
        (f)->_25F = 0;                                                                                                \
        (f)->_264 = 0;                                                                                                \
        (f)->_260 = 0;                                                                                                \
    } while (0)
// NONMATCHING 80%: register allocation and table addressing (lhax) differ; fn_3_522E0 takes the dx/dz the original leaves in f1/f2 from the preceding distance calc
#if NONMATCHING
int fn_3_28CA8(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int who = i;
    int target = -1;
    int stat3;
    int stat8;
    int stat9;
    int k;
    int k0;
    int best;
    int j;
    int dbl;
    s16* tbl;
    f32* lim;
    f32 d;
    f32 dx;
    f32 dz;
    f32 vx;
    f32 vz;
    f32 t;
    f32 ox;
    f32 oz;
    f32 reach;
    f32 sp34[3];
    Vec mid;
    s16 a;
    s16 diff;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (i == 0) {
            who = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        } else {
            who = g_Minigame.minigameControlStruct[0].fieldOrder[i - 2];
        }
    }
    stat3 = checkFieldingStat(g_GameLogic.teamFielding, f->rosterID, 3);
    stat8 = checkFieldingStat(g_GameLogic.teamFielding, f->rosterID, 8);
    stat9 = checkFieldingStat(g_GameLogic.teamFielding, f->rosterID, 9);
    tbl = &lbl_3_data_4924[stat3 * 3];
    lim = &lbl_3_data_490C[stat3 * 3];
    if (g_Ball.maxYOfHit >= lbl_3_rodata_B64 && g_Ball.AtBat_ContactResult == 0) {
        /* line drive already in flight: try to snag it at the end of its path */
        if (g_Ball.framesUntilBallHitsGround > tbl[0]) {
            goto notCaught;
        }
        target = g_Ball.framesUntilBallHitsGround - 1;
        if (fn_3_B7CDC(g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos.z) != 0) {
            goto notCaught;
        }
        if (target < tbl[1]) {
            goto notCaught;
        }
        dz = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z - f->z;
        dx = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x - f->x;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        fn_3_522E0(i, target, &ox, &oz, &reach, dx, dz);
        if (i == g_FieldingLogic.curBoost->fielder) {
            reach *= g_FieldingLogic.curBoost->scale;
        }
        if (d - reach <= 0.0f) {
            if (target > lbl_3_data_49DC[0xE]) {
                goto notCaught;
            }
            if (d / target < lbl_3_rodata_B6C) {
                goto notCaught;
            }
            goto dive;
        }
        if (d < reach * lim[0] + f->reach[7]) {
            goto run;
        }
        if (d >= reach + f->reach[7] + lim[1] || d - reach <= 0.0f ||
            g_Ball.AtBat_Contact_BallPos.y < lbl_3_rodata_B64) {
            goto notCaught;
        }
        goto chase;
    }
    if (fn_3_9FCF8(g_Ball.ballAngleFromHome, f->_180) > 0x100) {
        goto notCaught;
    }
    if (lbl_3_rodata_B70 + f->_070 < g_Ball.ballDistanceFromHome) {
        goto notCaught;
    }
    if (g_Ball.ballVelocity > lbl_3_rodata_B74) {
        k0 = fn_3_BBBC(sp34, tbl[0] + 15, 2, f->x, f->z);
        if (k0 < 0) {
            goto notCaught;
        }
        best = -1;
        if (k0 < 3) {
            k0 = 3;
        }
        for (k = k0, j = 0; j < 30 && k <= tbl[0]; j += 2, k += 2) {
            if (!(g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y > f->reach[8])) {
                if (lbl_3_rodata_B64 + f->_070 < g_Ball.physicsSubstruct.futureCoordsAndDist[k].dist && f->_07C < lbl_3_rodata_B78) {
                    break;
                }
                dz = g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.z - f->z;
                dx = g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.x - f->x;
                d = dx * dx + dz * dz;
                SQRT_L(d);
                fn_3_522E0(i, k, &ox, &oz, &reach, dx, dz);
                if (i == g_FieldingLogic.curBoost->fielder) {
                    reach *= g_FieldingLogic.curBoost->scale;
                }
                if (d - reach <= 0.0f) {
                    k0 = k;
                    goto searchDive;
                }
                if (d < reach * lim[0] + f->reach[7]) {
                    target = k;
                    goto run;
                }
                if (d < reach + f->reach[7] + lim[1] && d - reach > 0.0f && best < 0) {
                    best = k;
                }
            }
        }
        if (best < 0) {
            goto notCaught;
        }
        target = best;
        goto chase;
    }
    for (k = tbl[1]; k < tbl[0]; k += 2) {
        if (g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y > f->reach[3]) {
            continue;
        }
        dz = g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.z - f->z;
        dx = g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.x - f->x;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        fn_3_522E0(i, k, &ox, &oz, &reach, dx, dz);
        if (i == g_FieldingLogic.curBoost->fielder) {
            reach *= g_FieldingLogic.curBoost->scale;
        }
        if (d - reach <= 0.0f) {
            k0 = k;
            goto searchDive;
        }
        if (d < reach * lim[0] + f->reach[7]) {
            target = k;
            goto run;
        }
    }
    goto notCaught;

run:
    /* reachable on foot: run to the catch point */
    if (f->_1C5 != 0 && g_Ball.physicsSubstruct.futureCoordsAndDist[target].dist < f->_070) {
        return 0;
    }
    if (fn_3_B7C2C((Vec*)f, &g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos) != 0) {
        goto chase;
    }
    if (stat9 != 0 || checkFieldingStat(g_GameLogic.teamFielding, f->rosterID, 7) != 0) {
        fn_3_26664(i);
        if (f->_258 == 2) {
            goto chase;
        }
    } else if (fn_3_B7CDC(g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos.z) != 0) {
        goto chase;
    }
    SET_CATCH(f, target, 3, 0);
    if (target < g_Ball.framesUntilBallHitsGround) {
        f->_264 = 1;
    }
    g_Ball.catchAnimationTotalFrames = 0;
    f->_259 = 2;
    f->_234 = g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos.x;
    f->_238 = g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos.y;
    f->_23C = g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos.z;
    dz = f->_23C - f->z;
    dx = f->_234 - f->x;
    d = dx * dx + dz * dz;
    SQRT_L(d);
    reach = d - f->reach[7];
    t = reach / d;
    if (t <= lbl_3_rodata_B7C) {
        t = lbl_3_rodata_B7C;
    }
    f->_21C = dx * t + f->x;
    f->_224 = dz * t + f->z;
    f->_140 = game_atan2(dx, dz);
    if (stat3 != 0) {
        fn_3_1682AC(lbl_8036E548.active[who], 3);
        playSoundEffect(0x1A8);
    } else if (stat8 != 0) {
        fn_3_1682AC(lbl_8036E548.active[who], 8);
        playSoundEffect(0x1A8);
    } else if (stat9 != 0) {
        f->_265 = 1;
        fn_3_1682AC(lbl_8036E548.active[who], 8);
        playSoundEffect(0x1A8);
    }
    dbl = 0;
    if (checkFieldingStat(g_GameLogic.teamFielding, f->rosterID, 7) != 0) {
        dbl = 1;
        playSoundEffect(0x1A8);
    }
    if (target < g_Ball.framesUntilBallHitsGround && g_Ball.framesOnGroundUntilPickedUp == 0) {
        if (stat8 != 0 || stat9 != 0 || dbl != 0) {
            mid.x = f->_21C + f->_234;
            mid.y = f->_220 + f->_238;
            mid.z = f->_224 + f->_23C;
            mid.x = lbl_3_rodata_B80 * mid.x;
            mid.y = lbl_3_rodata_B80 * mid.y;
            mid.z = lbl_3_rodata_B80 * mid.z;
            fn_3_1AE44(1, target - 25, mid.x, mid.y, mid.z);
        } else {
            fn_3_1AE44(0, target - 25, f->_234, f->_238, f->_23C);
        }
    }
    return 1;

notCaught:
    if (g_FieldingLogic.curBoost->fielder != i) {
        return 0;
    }
chase:
    /* can't make the catch cleanly: head for the ball (or keep running) */
    if (f->_1C5 != 0 && g_FieldingLogic.curPadRec->_3 != 0) {
        return 0;
    }
    if (target <= 0) {
        vz = f->_03C;
        vx = f->_038;
        d = vx * vx + vz * vz;
        SQRT_L(d);
        if (d <= 0.0f) {
            return 0;
        }
        SET_CATCH(f, tbl[2], 3, 1);
        if (tbl[2] < g_Ball.framesUntilBallHitsGround) {
            f->_264 = 1;
        }
        f->_259 = 2;
        target = tbl[2];
        g_Ball.catchAnimationTotalFrames = 0;
    } else {
        if (target < tbl[2]) {
            target = tbl[2];
        }
        SET_CATCH(f, target, 3, 1);
        if (target < g_Ball.framesUntilBallHitsGround) {
            f->_264 = 1;
        }
        f->_259 = 2;
        g_Ball.catchAnimationTotalFrames = 0;
        vz = g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos.z - f->z;
        vx = g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos.x - f->x;
        d = vx * vx + vz * vz;
        SQRT_L(d);
    }
    vx = vx / d;
    vz = vz / d;
    fn_3_522E0(i, target, &ox, &oz, &reach, vx, vz);
    f->_21C = vx * reach + f->x;
    f->_224 = vz * reach + f->z;
    f->_140 = game_atan2(vx, vz);
    if (stat9 != 0) {
        f->_265 = 1;
    }
    return 1;

searchDive:
    /* the ball passes right by: look back along the path for a diving catch */
    if (k0 > lbl_3_data_49DC[0xE]) {
        return 0;
    }
    for (target = k0; target > lbl_3_data_49DC[0xF]; target -= 2) {
        if (fn_3_B7CDC(g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos.z) != 0) {
            continue;
        }
        if (g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos.y > f->reach[3]) {
            continue;
        }
        dz = g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos.z - f->z;
        dx = g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos.x - f->x;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        fn_3_522E0(i, target, &ox, &oz, &reach, dx, dz);
        if (i == g_FieldingLogic.curBoost->fielder) {
            reach *= g_FieldingLogic.curBoost->scale;
        }
        if (d / target < lbl_3_rodata_B6C) {
            continue;
        }
        goto dive;
    }
    return 0;

dive:
    SET_CATCH(f, target, 7, 0);
    f->_260 = 1;
    if (target < g_Ball.framesUntilBallHitsGround) {
        f->_264 = 1;
    }
    g_Ball.catchAnimationTotalFrames = 0;
    f->_234 = g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos.x;
    f->_238 = g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos.y;
    f->_23C = g_Ball.physicsSubstruct.futureCoordsAndDist[target].pos.z;
    dz = f->_23C - f->z;
    dx = f->_234 - f->x;
    d = dx * dx + dz * dz;
    SQRT_L(d);
    reach = d - lbl_3_data_47D0[f->catchType].e;
    t = reach / d;
    f->_21C = dx * t + f->x;
    f->_224 = dz * t + f->z;
    f->_261 = 0;
    a = fn_3_9FB8C(g_Ball.AtBat_Contact_BallPos.x - f->x, g_Ball.AtBat_Contact_BallPos.z - f->z);
    diff = fn_3_9FCA4(a, fn_3_9FB8C(f->_21C - f->x, f->_224 - f->z));
    if (diff < -0x500 || diff > 0x500) {
        f->_261 = 3;
    } else if (diff < -0x200) {
        f->_261 = 1;
    } else if (diff > 0x200) {
        f->_261 = 2;
    }
    return 1;
}
#endif
#undef SET_CATCH
#undef BALLPT

// .text:0x0002A164 size:0x124 mapped:0x806691F8
int fn_3_2A164(int i) {
    InMemFielderView* f = &g_Fielders[i];
    if (f->_074 > lbl_3_data_47D0[f->catchType].c) {
        return 0;
    }
    if (g_Ball.AtBat_Contact_BallPos.y < f->_15C) {
        return 0;
    }
    if (g_Ball.AtBat_Contact_BallPos.y > f->_15C + f->reach[3]) {
        return 0;
    }
    if (fn_3_B7CDC(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) != 0) {
        return 0;
    }
    f->_24C = 1;
    f->_24E = 0;
    f->_252 = 6;
    f->_253 = 0;
    f->_254 = 0;
    f->_255 = 0;
    f->_25B = 0;
    f->_259 = 0;
    f->_25C = 0;
    f->_25D = 0;
    f->_25E = 0;
    f->_25F = 0;
    f->_264 = 0;
    f->_260 = 0;
    if (g_Ball.framesUntilBallHitsGround > 1) {
        f->_264 = 1;
    }
    g_Ball.catchAnimationTotalFrames = 0;
    return 1;
}

// .text:0x0002A288 size:0x414 mapped:0x8066931C
// NONMATCHING 99.5%: fn_3_27FF4 inlined for the type-1 wall check via Inl27FF4; only float registers in that body differ
#if NONMATCHING
int fn_3_2A288(int i) {
    int who = i;
    InMemFielderView* f = &g_Fielders[i];
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (i == 0) {
            who = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        } else {
            who = g_Minigame.minigameControlStruct[0].fieldOrder[i - 2];
        }
    } else if (i != g_FieldingLogic._0B0) {
        return 0;
    }
    if (f->_1C5 != 0 && g_FieldingLogic.curPadRec->_4 == 0) {
        return 0;
    }
    if (g_Ball.AtBat_ContactResult == -1) {
        return 0;
    }
    if (g_Ball.framesSinceHit >= f->_1D2 + 5) {
        if (f->_1C5 == 0) {
            if (f->wallAbility == 2) {
                if (fn_3_28224(i) != 0) {
                    g_FieldingLogic.curPadRec->_2 = 0;
                    fn_3_1682AC(lbl_8036E548.active[who], 1);
                    return 1;
                }
            } else if (f->wallAbility == 1) {
                if (Inl27FF4(i) != 0) {
                    g_FieldingLogic.curPadRec->_2 = 0;
                    return 1;
                }
            } else if (f->wallAbility == 3) {
                if (fn_3_30214(i) != 0) {
                    g_FieldingLogic.curPadRec->_2 = 0;
                    fn_3_1682AC(lbl_8036E548.active[who], 2);
                    return 1;
                }
            }
        }
        if (fn_3_28CA8(i) != 0) {
            g_FieldingLogic.curPadRec->_2 = 0;
            return 1;
        }
    }
    return 0;
}
#endif

// .text:0x0002A69C size:0x63C mapped:0x80669730
// NONMATCHING 80%: register allocation (original keeps the base-table offset and radius-table pointer in saved regs) and lfsx/lfsu addressing; tail is fn_3_2B5C0's body inlined
#if NONMATCHING
int fn_3_2A69C(int i) {
    s16 base = g_FieldingLogic._0C4;
    InMemFielderView* f = &g_Fielders[i];
    f32* bpos;
    f32 lim;
    f32 r;
    f32 dx;
    f32 dz;
    f32 d;
    f32 t;
    s16 a;
    s16 diff;
    if (base < 0 || base > 3) {
        return 0;
    }
    if (i != g_Ball.fielderBeingThrownTo) {
        return 0;
    }
    if (g_Ball.framesSinceThrowStarted <= 3) {
        return 0;
    }
    if (f->_1A8 != 0) {
        return 0;
    }
    if (f->_252 == 2) {
        return 0;
    }
    bpos = &lbl_3_data_4444[base * 2];
    if (!(fn_3_9CE0(bpos[0], bpos[1]) < f->reach[0])) {
        return 0;
    }
    if (f->_1F5s == base) {
        return 0;
    }
    if (g_Ball.framesUntilThrowReachesDest > lbl_3_data_49DC[0x13]) {
        return 0;
    }
    if (g_Ball.framesUntilThrowReachesDest < lbl_3_data_49DC[0x14]) {
        return 0;
    }
    lim = lbl_3_rodata_B84 * f->maxVelocity * g_Ball.framesUntilThrowReachesDest;
    r = (&f->distToBase[0])[base] - lbl_3_data_47D0[f->catchType].d;
    if (r - lim > lbl_3_rodata_B78) {
        return 0;
    }
    if (r < lim) {
        f->_24C = g_Ball.framesUntilThrowReachesDest;
        f->_24E = 0;
        f->_252 = 8;
        f->_253 = 0;
        f->_254 = 0;
        f->_255 = 0;
        f->_25B = 0;
        f->_259 = 0;
        f->_25C = 0;
        f->_25D = 0;
        f->_25E = 0;
        f->_25F = 0;
        f->_264 = 0;
        f->_260 = 0;
        if (g_Ball.framesUntilThrowReachesDest < g_Ball.framesUntilBallHitsGround) {
            f->_264 = 1;
        }
        g_Ball.catchAnimationTotalFrames = 0;
        f->_234 = g_Ball.physicsSubstruct.futureCoordsAndDist[g_Ball.framesUntilThrowReachesDest].pos.x;
        f->_238 = g_Ball.physicsSubstruct.futureCoordsAndDist[g_Ball.framesUntilThrowReachesDest].pos.y;
        f->_23C = g_Ball.physicsSubstruct.futureCoordsAndDist[g_Ball.framesUntilThrowReachesDest].pos.z;
        dz = f->_23C - f->z;
        dx = f->_234 - f->x;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        r = d - lbl_3_data_47D0[f->catchType].d;
        if (r / g_Ball.framesUntilThrowReachesDest < lbl_3_rodata_B6C) {
            f->_21C = f->_234;
            f->_224 = f->_23C;
        } else {
            t = r / d;
            f->_21C = dx * t + f->x;
            f->_224 = dz * t + f->z;
        }
    } else {
        f->_24C = g_Ball.framesUntilThrowReachesDest;
        f->_24E = 0;
        f->_252 = 8;
        f->_253 = 0;
        f->_254 = 0;
        f->_255 = 0;
        f->_25B = 1;
        f->_259 = 0;
        f->_25C = 0;
        f->_25D = 0;
        f->_25E = 0;
        f->_25F = 0;
        f->_264 = 0;
        f->_260 = 0;
        if (g_Ball.framesUntilThrowReachesDest < g_Ball.framesUntilBallHitsGround) {
            f->_264 = 1;
        }
        dz = bpos[1] - f->z;
        dx = bpos[0] - f->x;
        g_Ball.catchAnimationTotalFrames = 0;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        f->_21C = lbl_3_rodata_B88 * (f->maxVelocity * (dx / d)) * g_Ball.framesUntilThrowReachesDest + f->x;
        f->_224 = lbl_3_rodata_B88 * (f->maxVelocity * (dz / d)) * g_Ball.framesUntilThrowReachesDest + f->z;
    }
    f->_261 = 0;
    a = fn_3_9FB8C(g_Ball.AtBat_Contact_BallPos.x - f->x, g_Ball.AtBat_Contact_BallPos.z - f->z);
    diff = fn_3_9FCA4(a, fn_3_9FB8C(f->_21C - f->x, f->_224 - f->z));
    if (diff < -0x500 || diff > 0x500) {
        f->_261 = 3;
    } else if (diff < -0x200) {
        f->_261 = 1;
    } else if (diff > 0x200) {
        f->_261 = 2;
    }
    return 1;
}
#endif

// .text:0x0002ACD8 size:0x90 mapped:0x80669D6C
int fn_3_2ACD8(int i, int j) {
    InMemFielderView* f = &g_Fielders[i];
    if (j < 1) {
        return 0;
    }
    if (fn_3_2BB04(i) != 0) {
        return 1;
    }
    f->_014 = g_Ball.physicsSubstruct.futureCoordsAndDist[j].pos.x;
    f->_01C = g_Ball.physicsSubstruct.futureCoordsAndDist[j].pos.z;
    f->_216 = 1;
    return 0;
}

// .text:0x0002AD68 size:0x858 mapped:0x80669DFC
// NONMATCHING 85%: the original inlines fn_3_2ACD8 for the short-fly case; we call it (same behaviour); loop/regalloc details differ
// nmverify: fn_3_2ACD8 inlined on one side (calls match once expanded)
#if NONMATCHING
int fn_3_2AD68(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 hmax = lbl_3_rodata_B84 * f->reach[3];
    s16 n = g_Ball.framesUntilThrowReachesDest;
    int k;
    int cnt;
    CoordAndDist* pt;
    f32 d;
    f32 dx;
    f32 dz;
    s16 ang;
    s16 diff;
    Vec a;
    Vec b;
    Vec c;
    Vec out;
    if (g_FieldingLogic._0C4 < 0) {
        return 0;
    }
    if (g_Ball.framesSinceThrowStarted <= 3) {
        return 0;
    }
    if (f->_1A8 != 0) {
        return 0;
    }
    if (f->_252 == 2) {
        return 0;
    }
    if (g_FieldingLogic._0F8[i] == 0xF) {
        if (g_FieldingLogic._13C == 0) {
            return 0;
        }
        if (f->_068 > f->reach[0]) {
            return 0;
        }
        for (k = lbl_3_data_49DC[0x17], pt = &g_Ball.physicsSubstruct.futureCoordsAndDist[k]; k <= lbl_3_data_49DC[0x16]; k++, pt++) {
            if (!(pt->pos.y > f->reach[3])) {
                d = DIST2_XZ(pt->pos.x, pt->pos.z, f->x, f->z);
                SQRT_L(d);
                if (d < f->reach[0]) {
                    break;
                }
            }
        }
        if (k > lbl_3_data_49DC[0x16]) {
            return 0;
        }
        goto hit;
    }
    if (i != g_Ball.fielderBeingThrownTo) {
        return 0;
    }
    if (g_FieldingLogic._0C4 <= 3) {
        f32* bpos = &lbl_3_data_4444[g_FieldingLogic._0C4 * 2];
        if (fn_3_9CE0(bpos[0], bpos[1]) < f->reach[0]) {
            k = n - 1;
            if (k <= 2) {
                return 0;
            }
            if (k > lbl_3_data_49DC[0x18]) {
                return 0;
            }
            if (f->_1F5s != g_FieldingLogic._0C4 && k > lbl_3_data_49DC[0x1A]) {
                return 0;
            }
            for (cnt = 10, pt = &g_Ball.physicsSubstruct.futureCoordsAndDist[k]; cnt != 0; cnt--, k--, pt--) {
                if (pt->pos.y > hmax) {
                    k++;
                    break;
                }
                d = DIST2_XZ(pt->pos.x, pt->pos.z, f->x, f->z);
                SQRT_L(d);
                if (d > lbl_3_data_4794[f->weight]) {
                    k++;
                    break;
                }
            }
            goto hit;
        }
        if (g_Ball.framesSinceThrowStarted <= 20) {
            return 0;
        }
        return fn_3_2ACD8(i, n - 2);
    }
    if (g_FieldingLogic._0C4 == 5 || g_FieldingLogic._0C4 == 6) {
        for (k = lbl_3_data_49DC[0x17], pt = &g_Ball.physicsSubstruct.futureCoordsAndDist[k]; k <= lbl_3_data_49DC[0x16]; k++, pt++) {
            if (!(pt->pos.y > f->reach[3])) {
                d = DIST2_XZ(pt->pos.x, pt->pos.z, f->x, f->z);
                SQRT_L(d);
                if (d < f->reach[0]) {
                    break;
                }
            }
        }
        if (k > lbl_3_data_49DC[0x16]) {
            return 0;
        }
        goto hit;
    }
    return 0;
hit:
    f->_24C = k;
    f->_24E = 0;
    f->_252 = 2;
    f->_253 = 0;
    f->_254 = 0;
    f->_255 = 1;
    f->_25B = 0;
    f->_259 = 0;
    f->_25C = 0;
    f->_25D = 0;
    f->_25E = 0;
    f->_25F = 0;
    f->_264 = 0;
    f->_260 = 0;
    if (k < g_Ball.framesUntilBallHitsGround) {
        f->_264 = 1;
    }
    g_Ball.catchAnimationTotalFrames = 0;
    if (g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y < f->reach[5]) {
        f->_253 = 0;
    } else if (g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y < f->reach[4]) {
        f->_253 = 1;
    } else {
        f->_253 = 2;
    }
    pt = &g_Ball.physicsSubstruct.futureCoordsAndDist[k];
    a.x = f->x;
    a.y = f->y;
    a.z = f->z;
    b.x = 0.0f;
    b.y = 0.0f;
    b.z = 0.0f;
    c.x = pt->pos.x;
    c.z = pt->pos.z;
    c.y = 0.0f;
    if (fn_3_9EFD0(&a, &b, &c, &out) >
        f->reach[2]) {
        dx = pt->pos.x - f->x;
        dz = pt->pos.z - f->z;
        ang = fn_3_9FE6C_normalizeAngle(g_Ball.ballTravelAngle + 0x800);
        diff = fn_3_9FCA4(ang, fn_3_9FB8C(dx, dz));
        if (diff > 0) {
            f->_254 = 2;
        } else {
            f->_254 = 1;
        }
    }
    f->_240 = pt->pos.x - g_Ball.AtBat_Contact_BallPos.x;
    f->_244 = pt->pos.z - g_Ball.AtBat_Contact_BallPos.z;
    return 1;
}
#endif

// .text:0x0002B5C0 size:0xD4 mapped:0x8066A654
void fn_3_2B5C0(int i) {
    InMemFielderView* f = &g_Fielders[i];
    s16 a;
    s16 d;
    f->_261 = 0;
    a = fn_3_9FB8C(g_Ball.AtBat_Contact_BallPos.x - f->x, g_Ball.AtBat_Contact_BallPos.z - f->z);
    d = fn_3_9FCA4(a, fn_3_9FB8C(f->_21C - f->x, f->_224 - f->z));
    if (d < -0x500 || d > 0x500) {
        f->_261 = 3;
    } else if (d < -0x200) {
        f->_261 = 1;
    } else if (d > 0x200) {
        f->_261 = 2;
    }
}

// .text:0x0002B694 size:0x470 mapped:0x8066A728
// NONMATCHING 90%: register allocation only (saved GPR/FPR assignment differs); the tail writes fn_3_2B5C0's body out as the original inlines it
#if NONMATCHING
int fn_3_2B694(int i) {
    InMemFielderView* f = &g_Fielders[i];
    CoordAndDist* pt;
    int k;
    f32 d;
    f32 spd;
    f32 dx;
    f32 dz;
    f32 r;
    f32 t;
    s16 a;
    s16 diff;
    if (0.0f == f->_050 || f->_19A < 0) {
        return 0;
    }
    if (g_Ball.hitWallInd != 0) {
        return 0;
    }
    if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0) {
        return 0;
    }
    if (g_Ball.AtBat_ContactResult == 1) {
        if (fn_3_9FCF8(f->_180, f->_19A) > 0x500) {
            return 0;
        }
    } else if (g_Ball.AtBat_ContactResult == 0 && fn_3_9FCF8(f->_180, f->_19A) > 0x500 &&
               lbl_3_rodata_B60 + f->_070 < g_Ball.physicsSubstruct.hitLandingSpotDistFromHome) {
        return 0;
    }
    spd = f->maxVelocity;
    if (i == g_FieldingLogic.curBoost->fielder) {
        spd *= g_FieldingLogic.curBoost->scale;
    }
    for (k = lbl_3_data_49DC[0x11], pt = &g_Ball.physicsSubstruct.futureCoordsAndDist[k]; k <= lbl_3_data_49DC[0x10]; pt++, k++) {
        if (pt->pos.y > f->reach[4]) {
            continue;
        }
        dx = pt->pos.x - f->x;
        dz = pt->pos.z - f->z;
        if (fn_3_9FCF8(fn_3_9FB8C(dx, dz), f->_19A) > lbl_3_data_49DC[0x12]) {
            continue;
        }
        d = dx * dx + dz * dz;
        SQRT_L(d);
        r = d - lbl_3_data_4794[f->weight];
        if ((int)(r / (spd * lbl_3_data_4930[30])) + 1 > k) {
            continue;
        }
        if (r < f->reach[0]) {
            continue;
        }
        if (fn_3_B7CDC(pt->pos.x, pt->pos.z) != 0) {
            continue;
        }
        f->_24C = k;
        f->_24E = 0;
        f->_252 = 7;
        f->_253 = 0;
        f->_254 = 0;
        f->_255 = 0;
        f->_25B = 0;
        f->_259 = 0;
        f->_25C = 0;
        f->_25D = 0;
        f->_25E = 0;
        f->_25F = 0;
        f->_264 = 0;
        f->_260 = 0;
        f->_260 = 1;
        if (k < g_Ball.framesUntilBallHitsGround) {
            f->_264 = 1;
        }
        t = r / d;
        g_Ball.catchAnimationTotalFrames = 0;
        f->_21C = dx * t + f->x;
        f->_224 = dz * t + f->z;
        f->_261 = 0;
        a = fn_3_9FB8C(g_Ball.AtBat_Contact_BallPos.x - f->x, g_Ball.AtBat_Contact_BallPos.z - f->z);
        diff = fn_3_9FCA4(a, fn_3_9FB8C(f->_21C - f->x, f->_224 - f->z));
        if (diff < -0x500 || diff > 0x500) {
            f->_261 = 3;
        } else if (diff < -0x200) {
            f->_261 = 1;
        } else if (diff > 0x200) {
            f->_261 = 2;
        }
        return 1;
    }
    return 0;
}
#endif

// .text:0x0002BB04 size:0x734 mapped:0x8066AB98
// NONMATCHING 85%: register allocation and int->float conversion scheduling in the trajectory loops
#if NONMATCHING
int fn_3_2BB04(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 vz;
    f32 vx;
    f32 d;
    f32 dx;
    f32 dz;
    int dive = 1;
    int aimed = 0;
    int k;
    s16 diff;
    s16 ang;
    CoordAndDist* pt;
    Vec a;
    Vec b;
    Vec c;
    Vec out;
    vz = f->_044;
    vx = f->_040;
    d = vx * vx + vz * vz;
    SQRT_L(d);
    if (0.0f != d) {
        vx = lbl_3_rodata_B24 * (vx / d);
        vz = lbl_3_rodata_B24 * (vz / d);
    }
    if (g_Ball.ballState == 3 || g_Ball.hitWallInd != 0 || i == 1) {
        dive = 0;
    }
    if (g_Ball.framesOnGroundUntilPickedUp != 0) {
        if (g_Ball.hitClassification1 == 2) {
            if (g_Ball.ballVelocity < lbl_3_rodata_B24) {
                dive = 0;
            }
        } else if (g_Ball.ballVelocity < lbl_3_rodata_B7C) {
            dive = 0;
        }
    }
    if (dive != 0) {
        for (k = 1, pt = &g_Ball.physicsSubstruct.futureCoordsAndDist[1]; k < lbl_3_data_49DC[0xB]; k++, pt++) {
            if (pt->pos.y < f->reach[3]) {
                dz = pt->pos.z - (k * vz + f->z);
                dx = pt->pos.x - (k * vx + f->x);
                d = dx * dx + dz * dz;
                SQRT_L(d);
                if (d < f->reach[0]) {
                    ang = fn_3_9FE6C_normalizeAngle(g_Ball.ballTravelAngle + 0x800);
                    diff = fn_3_9FCA4(ang, fn_3_9FB8C(dx, dz));
                    aimed = 1;
                    if (diff <= 0x400 && diff >= -0x400) {
                        goto hit;
                    }
                }
            }
        }
        return 0;
    }
    for (k = 1, pt = &g_Ball.physicsSubstruct.futureCoordsAndDist[1]; k < lbl_3_data_49DC[0xB]; k++, pt++) {
        if (pt->pos.y < f->reach[3]) {
            dz = pt->pos.z - (k * vz + f->z);
            dx = pt->pos.x - (k * vx + f->x);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            if (d < f->reach[1]) {
                goto hit;
            }
        }
    }
    return 0;
hit:
    f->_24C = k;
    f->_24E = 0;
    f->_252 = 1;
    f->_253 = 0;
    f->_254 = 0;
    f->_255 = dive;
    f->_25B = 0;
    f->_259 = 0;
    f->_25C = 0;
    f->_25D = 0;
    f->_25E = 0;
    f->_25F = 0;
    f->_264 = 0;
    f->_260 = 0;
    if (k < g_Ball.framesUntilBallHitsGround) {
        f->_264 = 1;
    }
    g_Ball.catchAnimationTotalFrames = 0;
    if (g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y < f->reach[5]) {
        f->_253 = 0;
    } else if (g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y < f->reach[4]) {
        f->_253 = 1;
    } else {
        f->_253 = 2;
    }
    if (dive != 0 && aimed != 0) {
        a.x = f->x;
        a.y = f->y;
        a.z = f->z;
        b.x = 0.0f;
        b.y = 0.0f;
        b.z = 0.0f;
        c.x = g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.x;
        c.z = g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.z;
        c.y = 0.0f;
        if (fn_3_9EFD0(&a, &b, &c, &out) >
            f->reach[2]) {
            if (diff > 0) {
                f->_254 = 2;
            } else {
                f->_254 = 1;
            }
        }
    }
    dx = g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.x - g_Ball.AtBat_Contact_BallPos.x;
    dz = g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.z - g_Ball.AtBat_Contact_BallPos.z;
    if (0.0f == dx && 0.0f == dz) {
        f->_240 = g_Ball.AtBat_Contact_BallPos.x;
        f->_244 = g_Ball.AtBat_Contact_BallPos.z;
    } else {
        f->_240 = dx;
        f->_244 = dz;
    }
    return 1;
}
#endif

// .text:0x0002C238 size:0xB8 mapped:0x8066B2CC
void fn_3_2C238(int i, int a, int b, int c, int d) {
    InMemFielderView* f = &g_Fielders[i];
    f->_24C = b;
    f->_24E = 0;
    f->_252 = a;
    f->_253 = 0;
    f->_254 = 0;
    f->_255 = d;
    f->_25B = c;
    f->_259 = 0;
    f->_25C = 0;
    f->_25D = 0;
    f->_25E = 0;
    f->_25F = 0;
    f->_264 = 0;
    f->_260 = 0;
    if (a == 7) {
        f->_260 = 1;
    }
    if (b < g_Ball.framesUntilBallHitsGround) {
        f->_264 = 1;
    }
    switch (a) {
    case 3:
        f->_259 = 2;
        break;
    case 4:
        f->_259 = 3;
        break;
    }
    g_Ball.catchAnimationTotalFrames = 0;
}

// .text:0x0002C2F0 size:0x3A8 mapped:0x8066B384
void fn_3_2C2F0(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int k;
    int idx;
    f32 half;
    f32 d;
    if (i != g_FieldingLogic.curBoost->fielder && g_Ball.warioWaluGarlicIsActive == 0 && g_Ball.AtBat_ContactResult == 0) {
        half = lbl_3_rodata_B80 * f->reach[3];
        for (k = 0; k < 20; k++) {
            idx = g_Ball.framesUntilBallHitsGround - k;
            if (half < g_Ball.physicsSubstruct.futureCoordsAndDist[idx].pos.y) {
                k--;
                break;
            }
        }
        if (k < 20) {
            d = DIST2_XZ(g_Ball.physicsSubstruct.futureCoordsAndDist[idx].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[idx].pos.z, f->x,
                         f->z);
            SQRT_L(d);
            f->_248 = d;
            if (f->_248 < lbl_3_rodata_B64) {
                if (f->_250 == 0 && g_Ball.framesUntilBallHitsGround < 45) {
                    if (g_Ball.framesUntilBallHitsGround > 30) {
                        if (f->_257 != 0) {
                            if (f->_248 < lbl_3_rodata_B8C) {
                                f->_256 = 1;
                            }
                        } else if (f->_248 < lbl_3_rodata_B78) {
                            f->_256 = 1;
                        }
                    }
                } else {
                    f->_256 = 1;
                }
                if (f->_248 < f->reach[0]) {
                    g_FieldingLogic._144 = 1;
                }
            }
        }
    }
}

// .text:0x0002C698 size:0x548 mapped:0x8066B72C
// NONMATCHING 85%: the original inlines fn_3_2A164 for the jumping-catch check; we call it (same behaviour); some branch layout/regalloc differs
// nmverify: fn_3_2A164 inlined on one side (calls match once expanded)
#if NONMATCHING
void fn_3_2C698(int i) {
    int who = i;
    InMemFielderView* f = &g_Fielders[i];
    int kind;
    if (g_GameLogic.secondaryGameMode == 7 || g_GameLogic.secondaryGameMode == 8) {
        return;
    }
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (i == 0) {
            who = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        } else {
            who = g_Minigame.minigameControlStruct[0].fieldOrder[i - 2];
        }
    }
    if (g_d_GameSettings.GameModeSelected == 6 && g_Minigame.TF_ballDespawnedInd != 0) {
        return;
    }
    if (!((g_GameLogic.secondaryGameMode > 1 && (g_d_GameSettings.GameModeSelected != 2 || g_Practice.practiceType_2 != 2) && g_GameLogic.freeFieldingPracticeInd == 0) ||
          g_GameLogic.gameStatus == 2)) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 2 && i >= 1 &&
        (g_Practice.practiceType_2 == 0 || g_Practice.practiceType_2 == 1 || g_Practice.practiceLevel == 4 || g_Practice.practiceLevel == 5)) {
        return;
    }
    if (g_Ball.catchAnimationTotalFrames != 0 || g_Ball.deadBallReason != 0 || (g_Ball.framesSinceHit < 20 && i == 1) || f->_1EE != 0 ||
        f->_1EF != 0 || f->_20F != 0 || f->_207 != 0 || (i == 0 && f->_1D2 + 5 > g_Ball.framesSinceHit) ||
        g_Ball.groundRuleDoubleInd != 0 || g_Ball.ballState == 1 || f->_210 != 0) {
        return;
    }
    if (g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow != 0 &&
        (g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow < 30 || (f->_19C == 0 && g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow < 20))) {
        return;
    }
    if (f->_1ED != 0 || f->_25A != 0 || (f->_211 != 0 && f->_212 == 3) || g_Ball.pauseBallMovementWhenInPlant != 0) {
        return;
    }
    kind = g_Ball.collisionCode & 0x7F;
    if (kind == 7 || kind == 8) {
        return;
    }
    f->_258 = 0;
    if (g_Ball.ballState == 2) {
        if (fn_3_2AD68(i) == 0) {
            fn_3_2A69C(i);
        }
    } else if (f->_203 != 0) {
        fn_3_2A164(i);
    } else if (f->_205 != 0) {
        fn_3_27D68(i);
    } else {
        if (fn_3_2BB04(i) == 0 && fn_3_2B694(i) == 0) {
            if (g_FieldingLogic.curPadRec->_2 == 0) {
                fn_3_2C2F0(i);
                return;
            }
            if (fn_3_2A288(i) == 0) {
                return;
            }
            g_FieldingLogic.curPadRec->_4 = 0;
        }
        if (f->_265 == 0 && checkFieldingStat(g_GameLogic.teamFielding, f->rosterID, 7) == 0) {
            fn_3_26664(i);
        }
        if (f->_258 == 1) {
            if (f->_259 != 0) {
                f->_1EE = 0;
            } else {
                f->_1EE = g_Ball.ballEnergy * lbl_3_data_5CDC[3] * lbl_3_data_5D08[f->weight];
                if (f->_1EE < 3) {
                    f->_1EE = 3;
                }
                f->_1EE = f->_1EE + f->_24C;
            }
        } else {
            f->_1EE = 0;
        }
        if (f->_258 <= 1 && checkFieldingStat(g_GameLogic.teamFielding, f->rosterID, 7) != 0) {
            fn_3_1682AC(lbl_8036E548.active[who], 7);
            playSoundEffect(0x1A8);
        }
    }
}
#endif

// .text:0x0002CBE0 size:0x314 mapped:0x8066BC74
// NONMATCHING 95%: registers only; loop pointer/counter r28/r29 swapped and f3/f4 in the ball-position sqrt
#if NONMATCHING
int fn_3_2CBE0(int a) {
    int n = g_Minigame.minigameFielderIndex[a];
    int i;
    InMemFielderView* f;
    s16 hb;
    f32 sz;
    f32 z;
    f32 x;
    f32 d;
    f32 sx;
    g_Minigame._1922 = a;
    g_Minigame.minigameRelatedIndex = n;
    f = &g_Fielders[n];
    fn_3_55EEC(n);
    if (g_Minigame._19BC == 1 && f->_070 > lbl_3_rodata_B90) {
        g_Minigame._19D0b[0] = 1;
    }
    if (fn_3_53130(n) != 0) {
        if (g_Minigame._19D0b[0] == 0) {
            return 0;
        }
    } else {
        if (g_Minigame._19D0b[0] == 0) {
            return 0;
        }
        f->_19E = fn_3_9FE6C_normalizeAngle(f->_180 + 0x800);
        f->_048 = shortAngleToRad_Capped(f->_19E);
        fn_3_3A584(n);
    }
    fn_3_55CC4(n);
    for (i = 0; i < 9; i++) {
        f = &g_Fielders[i];
        if (g_d_GameSettings.minigamesEnabled == 0 || g_Minigame.minigameRelatedIndex == i) {
            fn_3_54B58(i);
            f->_07C = fn_3_9CE0(f->x, f->z);
            if (0.0f == f->_050) {
                f->_038 = 0.0f;
                f->_03C = 0.0f;
            } else {
                f->_038 = f->_030 / f->_050;
                f->_03C = f->_034 / f->_050;
            }
            f->_1EA = 0;
            f->_217 = 0;
        }
    }
    fn_3_544B8();
    if (g_d_GameSettings.minigamesEnabled != 0) {
        fn_3_53F48();
    } else if ((hb = g_Ball.fielderWBallIndex) >= 0) {
        x = g_Fielders[hb].x;
        z = (&g_Fielders[0].z)[hb * 0x9A];
        g_Ball.AtBat_Contact_BallPos.x = x;
        g_Ball.AtBat_Contact_BallPos.y = (&g_Fielders[0].y)[hb * 0x9A];
        g_Ball.AtBat_Contact_BallPos.z = z;
        g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x = x;
        g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z = z;
        sx = x * x;
        sz = z * z;
        d = sx + sz;
        SQRT_L(d);
        g_Ball.ballDistanceFromHome = d;
    }
    return 1;
}
#endif

// .text:0x0002CEF4 size:0x18C mapped:0x8066BF88
void fn_3_2CEF4(int i) {
    InMemFielderView* f;
    f32 dx;
    f32 dz;
    f32 d;
    fn_3_2D47C(i);
    f = &g_Fielders[i];
    f->_19E = -1;
    dz = f->_01C - f->z;
    dx = f->_014 - f->x;
    d = dx * dx + dz * dz;
    SQRT_L(d);
    if (d < lbl_3_rodata_B80) {
        f->_068 = d;
        f->_209 = 0;
    } else {
        f->_19E = fn_3_9FB8C(dx, dz);
        f->_209 = 0;
    }
    fn_3_3A584(i);
}

// .text:0x0002D080 size:0x288 mapped:0x8066C114
// NONMATCHING 90%: constant-address hoisting in the prologue and float/int register allocation differ
#if NONMATCHING
int fn_3_2D080(int i) {
    f32 bestY = lbl_3_rodata_B94;
    int best = 9999;
    s16 lead = lbl_3_data_1C3C[1];
    InMemFielderView* f = &g_Fielders[i];
    int saved = 0;
    int found = 0;
    int k = 0;
    f32* y;
    int t;
    f32 d;
    f32 spd;
    while (k < 360) {
        y = &g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y;
        if (*y > lbl_3_rodata_B98) {
            if (*y > lbl_3_rodata_B9C) {
                k += 10;
            } else if (*y > lbl_3_rodata_BA0) {
                k += 5;
            } else {
                k += 2;
            }
            continue;
        }
        if (g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.x == f->x && g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.z == f->z) {
            t = 1;
        } else {
            d = (g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.x - f->x) * (g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.x - f->x) +
                (g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.z - f->z) * (g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.z - f->z);
            SQRT_L(d);
            spd = f->maxVelocity;
            if (lbl_3_rodata_B20 == spd) {
                spd = lbl_3_rodata_B60;
            }
            t = (f->_1D1 / 2) + (int)(d / spd);
        }
        if (t < k - lead) {
            if (!(*y < f->reach[3])) {
                if (found && bestY < *y) {
                    k = saved;
                    break;
                }
                bestY = *y;
                saved = k;
                found = 1;
            }
        } else if (found) {
            k = saved;
            break;
        }
        if (t > best && !found) {
            break;
        }
        best = t;
        k += 3;
    }
    if (k >= 360) {
        k = 359;
    }
    return k;
}
#endif

// .text:0x0002D308 size:0x174 mapped:0x8066C39C
// 95%: prologue scheduling only; original loads the 0.0f const (f0) before the sth/first fielder loads (tried local z = B20, f assigned late)
void fn_3_2D308(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 dx;
    f32 dz;
    f32 d;
    f->_19E = -1;
    dz = f->_01C - f->z;
    dx = f->_014 - f->x;
    d = dx * dx + dz * dz;
    SQRT_L(d);
    if (d < lbl_3_rodata_B80) {
        f->_068 = d;
        f->_209 = 0;
        return;
    }
    f->_19E = fn_3_9FB8C(dx, dz);
    f->_209 = 0;
}

// .text:0x0002D47C size:0x2EC mapped:0x8066C510
void fn_3_2D47C(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int hold = 0;
    int best;
    int k;
    f32 d;
    f32 bestD;
    if (g_Minigame.TF_ballDespawnedInd != 0 || g_Ball.fielderWBallIndex >= 0 || g_Ball.deadBallReason != 0) {
        hold = 1;
    }
    if (g_Minigame._1939 != 0 && hold != 0) {
        f->_208 = 4;
    } else if (hold != 0) {
        f->_014 = f->x;
        f->_01C = f->z;
        return;
    } else if (g_Ball.hitWallInd != 0) {
        f->_208 = 2;
    }
    if (f->_208 == 1) {
        if (g_Ball.AtBat_ContactResult == 1) {
            f->_208 = 2;
        } else {
            f->_014 = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            f->_01C = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        }
    }
    if (f->_208 == 2) {
        f->_014 = g_Ball.AtBat_Contact_BallPos.x;
        f->_01C = g_Ball.AtBat_Contact_BallPos.z;
    }
    if (f->_208 == 3) {
        int n = fn_3_2D080(i);
        f->_014 = g_Ball.physicsSubstruct.futureCoordsAndDist[n].pos.x;
        f->_01C = g_Ball.physicsSubstruct.futureCoordsAndDist[n].pos.z;
    }
    if (f->_208 == 4) {
        best = -1;
        bestD = lbl_3_rodata_BA4;
        for (k = 0; k < 100; k++) {
            if (g_Minigame.wallBall_coinsVisibleInd[k] != 0) {
                d = DIST2_XZ(f->x, f->z, g_Minigame.wallBall_coinCoordinates[k].x,
                             g_Minigame.wallBall_coinCoordinates[k].z);
                SQRT_L(d);
                if (d < bestD) {
                    best = k;
                    bestD = d;
                }
            }
        }
        if (best >= 0) {
            f->_014 = g_Minigame.wallBall_coinCoordinates[best].x;
            f->_01C = g_Minigame.wallBall_coinCoordinates[best].z;
        }
    }
}

// .text:0x0002D768 size:0x1C4 mapped:0x8066C7FC
void fn_3_2D768(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 dx;
    f32 dz;
    f32 d;
    if (f->_208 == 0) {
        if (f->_1DB == 0) {
            f->_208 = 1;
        } else {
            f->_208 = 3;
        }
    }
    f->_1D6 = 0;
    fn_3_2D47C(i);
    f->_19E = -1;
    dz = f->_01C - f->z;
    dx = f->_014 - f->x;
    d = dx * dx + dz * dz;
    SQRT_L(d);
    if (d < lbl_3_rodata_B80) {
        f->_068 = d;
        f->_209 = 0;
    } else {
        f->_19E = fn_3_9FB8C(dx, dz);
        f->_209 = 0;
    }
    fn_3_3A584(i);
}

// .text:0x0002D92C size:0x198 mapped:0x8066C9C0
void fn_3_2D92C(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 dx;
    f32 dz;
    f32 d;
    if (f->_1EC == 0) {
        fn_3_2D47C(i);
        f->_19E = -1;
        dz = f->_01C - f->z;
        dx = f->_014 - f->x;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        if (d < lbl_3_rodata_B80) {
            f->_068 = d;
            f->_209 = 0;
        } else {
            f->_19E = fn_3_9FB8C(dx, dz);
            f->_209 = 0;
        }
        fn_3_3A584(i);
    }
}

// .text:0x0002DAC4 size:0x230 mapped:0x8066CB58
void fn_3_2DAC4(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 dx;
    f32 dz;
    f32 d;
    if (f->_1ED == 0) {
        if (f->_208 == 0) {
            if (f->_1DB == 0) {
                f->_208 = 1;
            } else {
                f->_208 = 3;
            }
        }
        f->_1D6 = 0;
        fn_3_2D47C(i);
        f->_19E = -1;
        dz = f->_01C - f->z;
        dx = f->_014 - f->x;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        if (d < lbl_3_rodata_B80) {
            f->_068 = d;
            f->_209 = 0;
        } else {
            f->_19E = fn_3_9FB8C(dx, dz);
            f->_209 = 0;
        }
        fn_3_3A584(i);
    }
    if (g_Minigame.framesSincePanelHit != 0) {
        SetFielderAct(i, 0x1C);
    }
}

// .text:0x0002DCF4 size:0xC0 mapped:0x8066CD88
void fn_3_2DCF4(int i) {
    InMemFielderView* f = &g_Fielders[i];
    s16 n = g_Ball.framesSinceHit;
    if (n > 0 && n >= f->_1D2) {
        if (fn_3_53130(i) == 0) {
            fn_3_447C4(i);
            if (i != -1) {
                f->_1D3 = 0x1B;
                if (lbl_3_data_3C40[27].anim >= 0) {
                    g_FieldingLogic._0F8[i] = lbl_3_data_3C40[27].anim;
                }
                f->_1D5 = 0;
                f->_1D6 = 0;
                f->_1A4 = 0;
                f->_1AC = 0;
                f->_1FF = 0;
            }
        }
    }
}

// .text:0x0002DDB4 size:0x668 mapped:0x8066CE48
// NONMATCHING 80%: original re-materialises g_AiLogic per access (lis/addi/add) and uses lhau; we keep one base pointer
#if NONMATCHING
void fn_3_2DDB4(void) {
    u8 p = g_Minigame._1922;
    AIStruct* ai = &g_AiLogic;
    InMemFielderView* f = &g_Fielders[g_Minigame.minigameRelatedIndex];
    f32 d;
    f32 k;
    f32 dx;
    f32 dz;
    if (ai->_9C[p] < 0x7FFE) {
        ai->_9C[p] = ai->_9C[p] + 1;
    } else {
        ai->_9C[p] = 0x7FFF;
    }
    if (ai->_B4[p] == 0) {
        if (ai->_B8[p] == 0) {
            d = f->x * f->x + f->z * f->z;
            k = lbl_3_data_1C44[g_Batter.characterClass];
            SQRT_L(d);
            ai->_7C[p].x = (f->x / d) * k + f->x;
            ai->_7C[p].z = (f->z / d) * k + f->z;
            ai->_9C[p] = 0;
            ai->_B8[p] = 1;
        } else if (ai->_B8[p] == 2) {
            if (f->characterClass == 2 || f->characterClass == 3) {
                ai->_B4[p] = 1;
                ai->_AC[p] = f->_180;
            } else {
                ai->_B4[p] = 2;
            }
            ai->_B8[p] = 0;
        }
    } else if (ai->_B4[p] == 1) {
        if (ai->_B8[p] == 0) {
            d = f->x * f->x + f->z * f->z;
            SQRT_L(d);
            if (f->x < lbl_3_rodata_BA8) {
                ai->_AC[p] = f->_180 + RandomInt_Game(0x400) - 0x600;
            } else if (f->x > lbl_3_rodata_B70) {
                ai->_AC[p] = f->_180 + RandomInt_Game(0x400) + 0x200;
            } else if (d > lbl_3_rodata_BAC) {
                ai->_AC[p] = RandomInt_Game(0x800) + f->_180 + 0x400;
            } else if (d < lbl_3_rodata_BB0) {
                ai->_AC[p] = RandomInt_Game(0x800) + f->_180 - 0x400;
            } else if (RandomInt_Game(2) != 0) {
                ai->_AC[p] = RandomInt_Game(0x400) + ai->_AC[p] - 0x200;
            } else {
                ai->_AC[p] = RandomInt_Game(0x1000);
            }
            ai->_AC[p] = fn_3_9FE6C_normalizeAngle(ai->_AC[p]);
            ai->_A4[p] = RandomInt_Game_Range(lbl_3_data_1C54[0], lbl_3_data_1C54[1]);
            ai->_9C[p] = 0;
            ai->_B8[p] = 1;
        }
    }
    if (ai->_B8[p] == 1) {
        if (ai->_B4[p] == 1) {
            g_Controls[p].controlStickAngle = ai->_AC[p];
            if (ai->_9C[p] >= ai->_A4[p]) {
                ai->_B8[p] = 0;
            }
        } else {
            dz = ai->_7C[p].z - f->z;
            dx = ai->_7C[p].x - f->x;
            d = dx * dx + dz * dz;
            SQRT_L(d);
            if (d < lbl_3_rodata_B80) {
                ai->_B8[p] = 2;
                return;
            }
            g_Controls[p].controlStickAngle = fn_3_9FB8C(dx, dz);
        }
    }
}
#endif

// .text:0x0002E41C size:0x460 mapped:0x8066D4B0
// NONMATCHING 85%: bss base hoisting, history-fill loop guard and stfsx addressing of the pitcher copy differ; logic and calls match
#if NONMATCHING
void fn_3_2E41C(void) {
    int k;
    int i;
    int n;
    int pad;
    s16* hist;
    InputStruct* in;
    InMemFielderView* f;
    s16 v;
    u8 t;
    if (lbl_3_common_bss_34C90._1D5 != 0) {
        return;
    }
    if (g_Minigame.GameMode_MiniGame == 2) {
        if (g_Minigame.wallBallRotatePitchersInd == 0) {
            n = g_Minigame.minigameFielderIndex[g_Minigame.minigamePlayerSelectedOrder];
            g_Fielders[n].x = g_Pitcher.pitcher.x;
            g_Fielders[n].z = g_Pitcher.pitcher.z;
        }
        return;
    }
    for (k = 0; k < 4; k++) {
        if (g_Minigame.minigameFielderIndex[k] > 0) {
            g_Minigame.minigameRelatedIndex = ((u8)g_Minigame.minigameFielderIndex[k]);
            g_Minigame._1922 = k;
            if (g_d_GameSettings.GameModeSelected == 6 && g_Minigame.minigameControlStruct[0].battingHandedness[k] != 0) {
                fn_3_2DDB4();
            }
            pad = g_Minigame.minigameControlStruct[0].characterIndex[k];
            hist = lbl_3_bss_C8.hist[pad];
            in = &g_Controls[pad];
            for (i = 19; i > 0; i--) {
                lbl_3_bss_C8.tmp[i] = hist[i - 1];
            }
            lbl_3_bss_C8.tmp[0] = in->controlStickAngle;
            if (lbl_3_bss_C8.tmp[0] == -1) {
                for (i = 1; i < 20; i++) {
                    lbl_3_bss_C8.tmp[i] = -1;
                }
            }
            if (lbl_3_bss_C8.tmp[1] >= 0 && lbl_3_bss_C8.tmp[2] != 0) {
                lbl_3_bss_C8.cur = lbl_3_bss_C8.tmp[0];
            } else {
                lbl_3_bss_C8.cur = -1;
            }
            for (i = 0; i < 20; i++) {
                hist[i] = lbl_3_bss_C8.tmp[i];
            }
            g_FieldingLogic.padButtons[0] = in->buttonInput;
            g_FieldingLogic.padButtons[1] = in->newButtonInput;
            g_FieldingLogic.padButtons[2] = in->_08;
            g_FieldingLogic.curBoost = &g_FieldingLogic.boost[k];
            g_FieldingLogic.curPadRec = &g_FieldingLogic.padRec[k];
            g_FieldingLogic.padRec[k]._2 = 0;
            v = lbl_3_bss_C8.tmp[0];
            f = &g_Fielders[g_Minigame.minigameFielderIndex[k]];
            if (g_FieldingLogic._10E != 0) {
                v = -1;
            }
            f->_19E = v;
            if (g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] == 0 && v >= 0 && f->_1A0 > 10) {
                g_FieldingLogic._0CC = -1;
            }
            if (v >= 0) {
                t = g_FieldingLogic.curBoost->state;
                if (t != 3 && t != 4) {
                    if (g_FieldingLogic.padButtons[1] & 0x200) {
                        g_FieldingLogic.curBoost->timer = 0;
                    }
                    if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0 && g_Practice.practice_fielding_enableSprinting != 0) {
                        g_FieldingLogic.curBoost->timer = 0;
                    }
                }
            }
            fn_3_3A584(g_Minigame.minigameFielderIndex[k]);
        }
    }
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (g_Minigame.minigamePlayerSelectedOrder >= 0) {
            n = g_Minigame.minigameFielderIndex[g_Minigame.minigamePlayerSelectedOrder];
            g_Fielders[n].x = g_Pitcher.pitcher.x;
            g_Fielders[n].z = g_Pitcher.pitcher.z;
        }
    } else {
        g_Fielders[0].x = g_Pitcher.pitcher.x;
        g_Fielders[0].z = g_Pitcher.pitcher.z;
    }
}
#endif

// .text:0x0002E87C size:0x1A8 mapped:0x8066D910
void fn_3_2E87C(void) {
    f32 spC;
    f32 sp8;
    InMemFielderView* f;
    int i;
    u8 m;
    fn_3_58F58(0, &spC, &sp8);
    g_Fielders[0].x = spC;
    g_Fielders[0].z = sp8;
    g_Fielders[0]._014 = 0.0f;
    g_Fielders[0]._018 = 0.0f;
    g_Fielders[0]._01C = 0.0f;
    g_Fielders[0]._030 = 0.0f;
    g_Fielders[0]._034 = 0.0f;
    g_Fielders[0]._038 = 0.0f;
    m = g_Minigame.miniGameNumberOfParticipants;
    if (m >= 4) {
        g_Fielders[3].x = lbl_3_data_18984[2];
        g_Fielders[3].z = lbl_3_data_18984[3];
    } else if (m >= 3) {
        g_Fielders[3].x = lbl_3_data_18984[0];
        g_Fielders[3].z = lbl_3_data_18984[1];
    }
    if (m >= 4) {
        g_Fielders[4].x = lbl_3_data_18984[4];
        g_Fielders[4].z = lbl_3_data_18984[5];
    }
    for (i = 0; i < 9; i++) {
        f = &g_Fielders[i];
        f->_014 = 0.0f;
        f->_018 = 0.0f;
        f->_01C = 0.0f;
        f->_030 = 0.0f;
        f->_034 = 0.0f;
        f->_0D4 = f->x;
        f->_0D8 = f->z;
        f->_050 = 0.0f;
        f->_1D9 = 0;
        f->_1F5s = -1;
        spC = -f->x;
        sp8 = -f->z;
        f->_048 = atan2(sp8, spC);
    }
    g_AiLogic._B4[0] = 0;
    g_AiLogic._B8[0] = 0;
    g_AiLogic._B4[1] = 0;
    g_AiLogic._B8[1] = 0;
    g_AiLogic._B4[2] = 0;
    g_AiLogic._B8[2] = 0;
    g_AiLogic._B4[3] = 0;
    g_AiLogic._B8[3] = 0;
}

// .text:0x0002EA24 size:0x64 mapped:0x8066DAB8
void fn_3_2EA24(void) {
    int i;
    for (i = 0; i < 4; i++) {
        if (g_Minigame.minigameFielderIndex[i] >= 0) {
            fn_3_55EEC(g_Minigame.minigameFielderIndex[i]);
        }
    }
    fn_3_2E41C();
    fn_3_313B0();
}

// .text:0x0002EA88 size:0x43C mapped:0x8066DB1C
// NONMATCHING 90%: register allocation (fielder pointer/loop regs, ball-position floats) and prologue scheduling
#if NONMATCHING
void fn_3_2EA88(int a) {
    s16* p = &lbl_3_bss_170 + 0x13;
    int n = g_Minigame.minigameFielderIndex[a];
    InMemFielderView* f = &g_Fielders[n];
    int k;
    int i;
    s16 hb;
    f32 x;
    f32 z;
    f32 d;
    f32 sx;
    f32 sz;
    for (k = 0x13; k != 0; k--) {
        *p = -1;
        p--;
    }
    g_FieldingLogic.padButtons[0] = 0;
    g_FieldingLogic.padButtons[1] = 0;
    g_FieldingLogic.padButtons[2] = 0;
    if (g_Minigame.GameMode_MiniGame == 5) {
        if (f->_1D3 == 0 || f->_1D3 == 9) {
            SetFielderAct(n, 0xF);
        }
    } else {
        if (g_Ball.framesSinceHit <= 0) {
            return;
        }
        g_Minigame.minigameRelatedIndex = n;
        g_Minigame._1922 = a;
        if (g_Ball.framesSinceHit == 1) {
            fn_3_4FB34(n);
            fn_3_447C4(n);
            SetFielderAct(n, 0x1A);
            goto tail;
        }
    }
    fn_3_57BB4();
    fn_3_55EEC(n);
    lbl_3_data_3C40[g_Fielders[n]._1D3].update(n);
    fn_3_55CC4(n);
    if (g_Minigame.framesSincePanelHit != 0) {
        SetFielderAct(n, 0x1C);
    }
tail:
    for (i = 0; i < 9; i++) {
        f = &g_Fielders[i];
        if (g_d_GameSettings.minigamesEnabled == 0 || g_Minigame.minigameRelatedIndex == i) {
            fn_3_54B58(i);
            f->_07C = fn_3_9CE0(f->x, f->z);
            if (0.0f == f->_050) {
                f->_038 = 0.0f;
                f->_03C = 0.0f;
            } else {
                f->_038 = f->_030 / f->_050;
                f->_03C = f->_034 / f->_050;
            }
            f->_1EA = 0;
            f->_217 = 0;
        }
    }
    fn_3_544B8();
    if (g_d_GameSettings.minigamesEnabled != 0) {
        fn_3_53F48();
    } else if ((hb = g_Ball.fielderWBallIndex) >= 0) {
        x = g_Fielders[hb].x;
        z = (&g_Fielders[0].z)[hb * 0x9A];
        g_Ball.AtBat_Contact_BallPos.x = x;
        g_Ball.AtBat_Contact_BallPos.y = (&g_Fielders[0].y)[hb * 0x9A];
        g_Ball.AtBat_Contact_BallPos.z = z;
        g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x = x;
        g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z = z;
        sx = x * x;
        sz = z * z;
        d = sx + sz;
        SQRT_L(d);
        g_Ball.ballDistanceFromHome = d;
    }
}
#endif

// .text:0x0002EEC4 size:0x5C0 mapped:0x8066DF58
// NONMATCHING 85%: register allocation; fn_3_107D70 is declared u8 (its unit's header) but the original tests the full r3 (cmplwi)
#if NONMATCHING
void fn_3_2EEC4(int a) {
    MiniGameControlStruct* pads = &g_Minigame.minigameControlStruct[0];
    int n = g_Minigame.minigameFielderIndex[a];
    InMemFielderView* f;
    InputStruct* in;
    s16* hist;
    int i;
    s16 hb;
    f32 x;
    f32 z;
    f32 d;
    f32 sx;
    f32 sz;
    g_Minigame._1922 = a;
    g_Minigame.minigameRelatedIndex = n;
    f = &g_Fielders[n];
    in = &g_Controls[pads->characterIndex[(u8)a]];
    if (fn_3_107D70((u8)pads->characterIndex[(u8)a]) != 0) {
        in = &g_Minigame._1D7C[pads->characterIndex[g_Minigame._1922]];
    }
    hist = lbl_3_bss_C8.hist[pads->characterIndex[g_Minigame._1922]];
    for (i = 19; i > 0; i--) {
        lbl_3_bss_C8.tmp[i] = hist[i - 1];
    }
    lbl_3_bss_C8.tmp[0] = in->controlStickAngle;
    if (lbl_3_bss_C8.tmp[0] == -1) {
        for (i = 1; i < 20; i++) {
            lbl_3_bss_C8.tmp[i] = -1;
        }
    }
    if (lbl_3_bss_C8.tmp[1] >= 0 && lbl_3_bss_C8.tmp[2] != 0) {
        lbl_3_bss_C8.cur = lbl_3_bss_C8.tmp[0];
    } else {
        lbl_3_bss_C8.cur = -1;
    }
    for (i = 0; i < 20; i++) {
        hist[i] = lbl_3_bss_C8.tmp[i];
    }
    g_FieldingLogic.padButtons[0] = in->buttonInput;
    g_FieldingLogic.padButtons[1] = in->newButtonInput;
    g_FieldingLogic.padButtons[2] = in->_08;
    if (g_Minigame.GameMode_MiniGame != 5 && (g_FieldingLogic.padButtons[1] & 0x100)) {
        g_FieldingLogic.curPadRec->_2 = 2;
        g_FieldingLogic.curPadRec->stickAngle = lbl_3_bss_C8.tmp[0];
    }
    if (g_Minigame.GameMode_MiniGame == 5 || g_Minigame.GameMode_MiniGame == 6) {
        if (f->_1D3 == 0 || f->_1D3 == 9) {
            SetFielderAct(n, 0xF);
        }
    } else {
        if (g_Ball.framesSinceHit <= 0) {
            return;
        }
        if (g_Ball.framesSinceHit == 1) {
            SetFielderAct(n, 0xF);
            goto tail;
        }
    }
    fn_3_51220();
    fn_3_55EEC(n);
    lbl_3_data_3C40[f->_1D3].update(n);
    fn_3_55CC4(n);
tail:
    for (i = 0; i < 9; i++) {
        f = &g_Fielders[i];
        if (g_d_GameSettings.minigamesEnabled == 0 || g_Minigame.minigameRelatedIndex == i) {
            fn_3_54B58(i);
            f->_07C = fn_3_9CE0(f->x, f->z);
            if (0.0f == f->_050) {
                f->_038 = 0.0f;
                f->_03C = 0.0f;
            } else {
                f->_038 = f->_030 / f->_050;
                f->_03C = f->_034 / f->_050;
            }
            f->_1EA = 0;
            f->_217 = 0;
        }
    }
    fn_3_544B8();
    if (g_d_GameSettings.minigamesEnabled != 0) {
        fn_3_53F48();
    } else if ((hb = g_Ball.fielderWBallIndex) >= 0) {
        x = g_Fielders[hb].x;
        z = (&g_Fielders[0].z)[hb * 0x9A];
        g_Ball.AtBat_Contact_BallPos.x = x;
        g_Ball.AtBat_Contact_BallPos.y = (&g_Fielders[0].y)[hb * 0x9A];
        g_Ball.AtBat_Contact_BallPos.z = z;
        g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x = x;
        g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z = z;
        sx = x * x;
        sz = z * z;
        d = sx + sz;
        SQRT_L(d);
        g_Ball.ballDistanceFromHome = d;
    }
}
#endif

// .text:0x0002F484 size:0xF0 mapped:0x8066E518
void fn_3_2F484(void) {
    int i;
    fn_3_58688();
    for (i = 0; i < 4; i++) {
        if (g_Minigame.minigameFielderIndex[i] >= 0) {
            g_FieldingLogic.curBoost = &g_FieldingLogic.boost[i];
            g_FieldingLogic.curPadRec = &g_FieldingLogic.padRec[i];
            if (g_d_GameSettings.GameModeSelected != 6 || g_Minigame._19BC == 0 ||
                i != g_Minigame._19C6 || fn_3_2CBE0(i) == 0) {
                if (g_Minigame.minigameControlStruct[0].battingHandedness[i] == 0) {
                    fn_3_2EEC4(i);
                } else if (g_Minigame.GameMode_MiniGame == 6) {
                    fn_3_2EEC4(i);
                } else {
                    fn_3_2EA88(i);
                }
            }
        }
    }
}

// .text:0x0002F574 size:0x260 mapped:0x8066E608
void fn_3_2F574(int i) {
    Ent16* tbl = (Ent16*)lbl_3_data_4884;
    InMemFielderView* f = &g_Fielders[i];
    int type = f->superJump;
    f32 pos[1];
    f32 d;
    f->_204 = f->_204 + 1;
    f->_164 = f->_164 - tbl[type].b;
    if (f->_1AE >= f->_1B0 && f->_164 < 0.0f) {
        f->_164 = 0.0f;
    }
    f->_15C = f->_15C + f->_164;
    f->_1AE = f->_1AE - 1;
    if (0.0f != f->_160 || 0.0f != f->_168) {
        f->_030 = f->_160;
        f->_034 = f->_168;
        d = f->_030 * f->_030 + f->_034 * f->_034;
        SQRT_L(d);
        f->_050 = d;
        if (fn_3_51798(i, pos) != 0) {
            f->_160 = 0.0f;
            f->_168 = 0.0f;
            f->_030 = 0.0f;
            f->_034 = 0.0f;
            f->_050 = 0.0f;
        } else {
            f->x = f->x + f->_030;
            f->z = f->z + f->_034;
        }
    }
    f->_014 = f->x;
    f->_01C = f->z;
    f->_1F0 = 1;
    if (f->_1AE <= 0) {
        f->_203 = 0;
        f->_15C = 0.0f;
        f->_1A0 = 0;
    }
}

// .text:0x0002F7D4 size:0x150 mapped:0x8066E868
// NONMATCHING 80%: original addresses the jump table entry through two separately computed bases (lfsx + add); ours CSEs one
#if NONMATCHING
void fn_3_2F7D4(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int type = f->superJump;
    int n;
    int k;
    f->_203 = 1;
    f->_15C = lbl_3_rodata_B20;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (i == 0) {
            i = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        } else {
            i = g_Minigame.minigameControlStruct[0].fieldOrder[i - 2];
        }
    }
    f->_164 = ((Ent16*)lbl_3_data_4884)[type].a;
    f->_160 = f->_038 * lbl_3_rodata_B24 * ((Ent16*)lbl_3_data_4884)[type].c;
    f->_168 = f->_03C * lbl_3_rodata_B24 * ((Ent16*)lbl_3_data_4884)[type].c;
    k = (int)((Ent16*)lbl_3_data_4884)[type].d;
    n = (int)(f->_164 / ((Ent16*)lbl_3_data_4884)[type].b);
    f->_1B0 = n + 1;
    f->_1AE = n * 2 + k + 2;
    f->_204 = 0;
    if (type != 0) {
        fn_3_1682AC(lbl_8036E548.active[i], 6);
    }
}
#endif

// .text:0x0002F924 size:0x278 mapped:0x8066E9B8
void fn_3_2F924(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 dx;
    f32 dz;
    f32 dh;
    f32 k;
    f32 h;
    if (f->_207 == 1) {
        dx = f->_128 - f->x;
        dz = f->_130 - f->z;
        dh = f->_12C - f->_148;
        if (f->_1B4 > 1) {
            k = 1.0f / f->_1B4;
        } else {
            k = 1.0f;
        }
        dx *= k;
        dz *= k;
        dh *= k;
        f->_030 = dx;
        f->_034 = dz;
        f->x = f->x + f->_030;
        f->z = f->z + f->_034;
        f->_148 = f->_148 + dh;
        f->_1B4 = f->_1B4 - 1;
        if (f->_1B4 == 0) {
            f->_207 = 2;
            f->_1B4 = lbl_3_data_49DC[8];
            if (g_d_GameSettings.minigamesEnabled != 0) {
                u8* m = (u8*)&g_Minigame + f->_20D; // player _20D's bytes at [0] below
                if (((MiniGameStruct*)m)->minigameControlStruct[0].battingHandedness[0] == 0) {
                    fn_3_6C854(((MiniGameStruct*)m)->minigameControlStruct[0].characterIndex[0], 2);
                }
            } else if (g_GameLogic._13E[g_GameLogic.teamFielding] == 0) {
                fn_3_6C854(g_GameLogic.teamFielding, 2);
            }
            fn_3_90220(f->charID, 11);
        }
    } else if (f->_207 == 2) {
        f->_1B4 = f->_1B4 - 1;
        if (f->_1B4 == 0) {
            f->_207 = 3;
            f->_1B4 = lbl_3_data_49DC[9];
        }
    } else if (f->_207 == 3) {
        h = f->_148;
        f->_148 = h - h / f->_1B4;
        f->_1B4 = f->_1B4 - 1;
        if (f->_1B4 == 0) {
            f->_148 = 0.0f;
            f->_207 = 4;
            f->_1B4 = lbl_3_data_49DC[10];
        }
    } else if (f->_207 == 4) {
        f->_1B4 = f->_1B4 - 1;
        if (f->_1B4 == 0) {
            f->_207 = 0;
        }
    }
}

// .text:0x0002FB9C size:0x390 mapped:0x8066EC30
// NONMATCHING 92%: the moved flag lives in r6 (initialised at entry) in the original, ours keeps it in r0; f-reg order in the side-step segment
#if NONMATCHING
void fn_3_2FB9C(int i) {
    int moved = 0;
    InMemFielderView* f = &g_Fielders[i];
    f32 h = f->_148;
    int dir;
    int side;
    f32 a;
    f32 cx;
    f32 cz;
    f32 y;
    f32 e;
    f32 lo;
    f32 hi;
    VecSrcDst seg;
    CollisionStruct hit;
    if (g_Ball.ballState == 1 || g_Ball.ballState == 2) {
        f->_205 = 3;
        return;
    }
    if (g_FieldingLogic.padButtons[1] & 0x100) {
        f->_205 = 3;
        return;
    }
    if (g_FieldingLogic.padButtons[0] & 8) {
        dir = 1;
        h += lbl_3_data_4930[25];
    } else if (g_FieldingLogic.padButtons[0] & 4) {
        dir = 2;
        h -= lbl_3_data_4930[25];
    } else {
        goto turn;
    }
    if (h <= 0.0f) {
        f->_205 = 3;
        return;
    }
    y = -(h + f->reach[3]);
    seg.dst.y = y;
    seg.src.y = y;
    seg.src.x = lbl_3_rodata_B64 * f->_140 + f->x;
    seg.src.z = lbl_3_rodata_B64 * f->_144 + f->z;
    seg.dst.x = f->x - lbl_3_rodata_B64 * f->_140;
    seg.dst.z = f->z - lbl_3_rodata_B64 * f->_144;
    if ((checkCollision(&seg, &hit, 0, 0) & 0x7F) == 2) {
        f->_148 = h;
        moved = 1;
        f->_206 = dir;
        goto done;
    }
turn:
    if (g_FieldingLogic.padButtons[0] & 2) {
        side = 3;
        a = f->_06C - lbl_3_data_4930[26];
    } else if (g_FieldingLogic.padButtons[0] & 1) {
        side = 4;
        a = f->_06C + lbl_3_data_4930[26];
    } else {
        return;
    }
    getComponentsFromRad(a, &cx, &cz);
    hi = lbl_3_rodata_B64 + f->_070;
    lo = f->_070 - lbl_3_rodata_B64;
    y = -(f->_148 + f->reach[4]);
    seg.src.x = cx * lo;
    seg.src.z = cz * lo;
    seg.dst.x = cx * hi;
    seg.dst.z = cz * hi;
    seg.dst.y = y;
    seg.src.y = y;
    if ((checkCollision(&seg, &hit, 0, 0) & 0x7F) == 2) {
        f->x = hit.position.x;
        f->z = hit.position.z;
        if (side != 0) {
            f->_206 = side;
        }
        moved = 1;
    } else {
        moved = 0;
    }
done:
    if (moved != 0) {
        e = hit.normal.x * hit.normal.x + hit.normal.z * hit.normal.z;
        SQRT_L(e);
        f->_140 = hit.normal.x / e;
        f->_144 = hit.normal.z / e;
    }
}
#endif

// .text:0x0002FF2C size:0x18C mapped:0x8066EFC0
void fn_3_2FF2C(int i) {
    u8 st;
    InMemFielderView* f = &g_Fielders[i];
    if (f->_1B2 < 0x7FFE) {
        f->_1B2 = f->_1B2 + 1;
    } else {
        f->_1B2 = 0x7FFF;
    }
    st = f->_205;
    if (st == 5 && f->_1B2 < lbl_3_data_49DC[6]) {
        return;
    }
    if (st == 3 || st == 5) {
        if (st == 3) {
            f->_150 = f->_140 * lbl_3_data_4930[19];
            f->_158 = f->_144 * lbl_3_data_4930[19];
            f->_154 = lbl_3_data_4930[21];
        } else {
            f->_150 = f->_140 * lbl_3_data_4930[20];
            f->_158 = f->_144 * lbl_3_data_4930[20];
            f->_154 = lbl_3_data_4930[22];
        }
        f->_205 = f->_205 + 1;
    } else {
        f->_150 = f->_150 * lbl_3_data_4930[23];
        f->_158 = f->_158 * lbl_3_data_4930[23];
        f->_154 = f->_154 + lbl_3_data_4930[24];
    }
    f->x = f->x + f->_150;
    f->z = f->z + f->_158;
    f->_148 = f->_148 + f->_154;
    if (f->_148 <= 0.0f) {
        f->_148 = 0.0f;
        f->_205 = 0;
        f->_1FC = 1;
    }
    f->_030 = f->x - f->_0D4;
    f->_034 = f->z - f->_0D8;
}

// .text:0x000300B8 size:0x15C mapped:0x8066F14C
void fn_3_300B8(int i) {
    Fld300B8* f = (Fld300B8*)g_Fielders + i;
    f->flag = 0;
    if (f->st == 1) {
        s16 n = f->n;
        f32 dx = (f->tx - f->x) / (f32)n;
        f32 dz = (f->tz - f->z) / (f32)n;
        f->x += dx;
        f->z += dz;
        f->hv = f->hv - lbl_3_data_4930[18];
        f->h = f->h + f->hv;
        if (f->h < 0.0f) {
            f->h = 0.0f;
        }
        f->n = f->n - 1;
        if (f->n <= 0) {
            f->st = 2;
        }
    } else if (f->st == 2) {
        fn_3_2FB9C(i);
        f->n = 0;
    } else if (f->st >= 3) {
        fn_3_2FF2C(i);
        return;
    }
    f->vx = f->x - f->px;
    f->vz = f->z - f->pz;
}


// .text:0x00030214 size:0x350 mapped:0x8066F2A8
// NONMATCHING 90%: float register allocation/scheduling around the wall-normal block after checkCollision
#if NONMATCHING
int fn_3_30214(int i) {
    InMemFielderView* f = &g_Fielders[i];
    VecSrcDst seg;
    CollisionStruct hit;
    f32 x, z;
    f32 dx;
    f32 dz;
    f32 d;
    f32 e;
    if ((0.0f == f->_038 && 0.0f == f->_03C) || f->_19A < 0) {
        return 0;
    }
    x = f->x;
    z = f->z;
    seg.src.x = x;
    seg.dst.y = lbl_3_rodata_BB4;
    seg.src.y = lbl_3_rodata_BB4;
    seg.src.z = z;
    seg.dst.x = f->_038 * lbl_3_data_4930[15] + x;
    seg.dst.z = f->_03C * lbl_3_data_4930[15] + z;
    if ((checkCollision(&seg, &hit, 0, 0) & 0x7F) != 2) {
        return 0;
    }
    f->_205 = 1;
    dz = seg.dst.z - f->z;
    dx = seg.dst.x - f->x;
    d = dx * dx + dz * dz;
    SQRT_L(d);
    e = hit.normal.x * hit.normal.x + hit.normal.z * hit.normal.z;
    f->_1B2 = (int)(d / lbl_3_data_4930[16]) + 1;
    f->_128 = hit.normal.x * lbl_3_data_4930[27] + hit.position.x;
    f->_130 = hit.normal.z * lbl_3_data_4930[27] + hit.position.z;
    f->_154 = lbl_3_data_4930[17];
    f->_148 = 0.0f;
    SQRT_L(e);
    f->_140 = hit.normal.x / e;
    f->_144 = hit.normal.z / e;
    f->_050 = 0.0f;
    return 1;
}
#endif

// .text:0x00030564 size:0xB8 mapped:0x8066F5F8
int fn_3_30564(int i) {
    InMemFielderView* f = &g_Fielders[i];
    if (f->_25E == 3) {
        f32 k = lbl_3_data_4930[14];
        f->_150 = f->_150 * k;
        f->_158 = f->_158 * k;
        f->x = f->x + f->_150;
        f->z = f->z + f->_158;
        f->_014 = f->x;
        f->_01C = f->z;
        f->_1F0 = 1;
    } else if (f->_25E == 4) {
        f->_050 = lbl_3_rodata_B20;
        f->_25F = f->_25F - 1;
        if (f->_25F == 0) {
            f->_25E = 0;
        }
    }
    return 1;
}

// .text:0x0003061C size:0x29C mapped:0x8066F6B0
// NONMATCHING 85%: original keeps the 0.3 limit in f30 across the loop; ours keeps a table address instead (regalloc/hoisting)
#if NONMATCHING
void fn_3_3061C(void) {
    InMemFielderView* f = g_Fielders;
    f32* home = lbl_3_data_450C[0];
    int i;
    f32 dx;
    f32 dz;
    f32 d;
    for (i = 0; i < 9; i++) {
        if (f->_1F1 == 0) {
            f->_1F1 = 1;
            f->x = ((f32 (*)[2][2])lbl_3_data_4290)[g_d_GameSettings.StadiumID][g_GameLogic.awayTeamBattingInd_battingTeam ^ 1][0];
            f->y = 0.0f;
            f->z = ((f32 (*)[2][2])lbl_3_data_4290)[g_d_GameSettings.StadiumID][g_GameLogic.awayTeamBattingInd_battingTeam ^ 1][1];
            f->_014 = home[0];
            f->_01C = home[1];
            f->_1A6 = RandomInt_Game(30);
        }
        dz = f->_01C - f->z;
        dx = f->_014 - f->x;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        if (d < lbl_3_rodata_BB8 || f->_1A6 > g_GameLogic.FrameCountOfCurrentPitch) {
            f->_030 = 0.0f;
            f->_034 = 0.0f;
            f->_050 = 0.0f;
        } else {
            f->_030 = lbl_3_rodata_B74 * (dx / d) - lbl_3_rodata_B48;
            f->x = f->x + f->_030;
            f->_034 = lbl_3_rodata_B74 * (dz / d) - lbl_3_rodata_B48;
            f->z = f->z + f->_034;
            f->_050 = lbl_3_rodata_B74;
        }
        home += 2;
        f++;
    }
    fn_3_313B0();
    g_FieldingLogic._118 = 0;
    g_Ball.framesSinceHit = 100;
}
#endif

// .text:0x000308B8 size:0x1A0 mapped:0x8066F94C
void fn_3_308B8(int i, f32 x, f32 z) {
    InMemFielderView* f = &g_Fielders[i];
    f32 dx;
    f32 dz;
    f32 d;
    f->_014 = x;
    f->_01C = z;
    dx = x - f->x;
    dz = z - f->z;
    if (0.0f == dx && 0.0f == dz) {
        f->_050 = 0.0f;
        f->_068 = 0.0f;
        return;
    }
    f->_064 = atan2(dz, dx);
    d = dx * dx + dz * dz;
    SQRT_L(d);
    f->_068 = d;
    f->_1D9 = 1;
}

// .text:0x00030A58 size:0x31C mapped:0x8066FAEC
void fn_3_30A58(void) {
    int i;
    InMemFielderView* f;
    f32 x;
    f32 z;
    f32 dz;
    f32 dx;
    f32 d;
    for (i = 2; i < 9; i++) {
        f = &g_Fielders[i];
        fn_3_58F58(i, &x, &z);
        d = (f->x - x) * (f->x - x) + (f->z - z) * (f->z - z);
        SQRT_L(d);
        if (d < 0.1f) {
            x = f->x;
            z = f->z;
        }
        f->_014 = x;
        f->_01C = z;
        dx = x - f->x;
        dz = z - f->z;
        if (0.0f == dx && 0.0f == dz) {
            f->_050 = 0.0f;
            f->_068 = 0.0f;
        } else {
            f->_064 = atan2(dz, dx);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            f->_068 = d;
            f->_1D9 = 1;
        }
    }
}

// .text:0x00030D74 size:0x63C mapped:0x8066FE08
// NONMATCHING 88%: register allocation (loop pointers/counters, the x/z out-params' stack slots); first loop is fn_3_30A58's body inlined
#if NONMATCHING
void fn_3_30D74(void) {
    int i;
    InMemFielderView* f;
    f32 x;
    f32 z;
    f32 dz;
    f32 dx;
    f32 d;
    int moving;
    if (lbl_3_common_bss_34C90._1D5 != 0) {
        return;
    }
    for (i = 2; i < 9; i++) {
        f = &g_Fielders[i];
        fn_3_58F58(i, &x, &z);
        d = (f->x - x) * (f->x - x) + (f->z - z) * (f->z - z);
        SQRT_L(d);
        if (d < 0.1f) {
            x = f->x;
            z = f->z;
        }
        f->_014 = x;
        f->_01C = z;
        dx = x - f->x;
        dz = z - f->z;
        if (0.0f == dx && 0.0f == dz) {
            f->_050 = 0.0f;
            f->_068 = 0.0f;
        } else {
            f->_064 = atan2(dz, dx);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            f->_068 = d;
            f->_1D9 = 1;
        }
    }
    for (i = 2; i < 9; i++) {
        f = &g_Fielders[i];
        moving = 0;
        if (f->_068 > lbl_3_rodata_BBC) {
            moving = 1;
        } else if (f->_050 >= lbl_3_rodata_B24 && f->_068 > lbl_3_rodata_B7C) {
            moving = 1;
        }
        if (moving != 0) {
            if (g_Pitcher.pitchTotalTimeCounter <= 0) {
                f->_050 = lbl_3_rodata_B24;
            } else if (g_Batter.buntStatus >= 1 && g_Batter.buntStatus <= 3 && (i == 2 || i == 4)) {
                f->_050 = f->_050 + f->velocityPerWeight;
                if (f->_050 > f->maxVelocity) {
                    f->_050 = f->maxVelocity;
                }
            } else if (((i == 3 && g_Batter.batterHand == 0) || (i == 5 && g_Batter.batterHand != 0)) && g_Runners[1].runnerOnFieldOrOutOrScored != 0 &&
                       g_Runners[1].furthestBaseForcedToGoToOnWalk != 0) {
                f->_050 = f->_050 + f->velocityPerWeight;
                if (f->_050 > f->maxVelocity) {
                    f->_050 = f->maxVelocity;
                }
            } else if (g_Pitcher.pitchTotalTimeCounter < 60) {
                f->_17E = 60 - g_Pitcher.pitchTotalTimeCounter;
                f->_050 = f->_068 / f->_17E;
            } else {
                f->_17E = 0;
                f->_050 = 0.0f;
            }
            f->_068 = f->_068 - f->_050;
            if (f->_050 <= 0.0f) {
                f->_050 = 0.0f;
                f->_17E = -1;
            } else if (f->_068 < 0.0f) {
                f->_030 = f->_014 - f->x;
                f->_034 = f->_01C - f->z;
                f->x = f->_014;
                f->z = f->_01C;
                f->_068 = 0.0f;
                f->_17E = 0;
            } else {
                f->_030 = f->_050 * (f32)cos(f->_064);
                f->_034 = f->_050 * (f32)sin(f->_064);
                f->x = f->x + f->_030;
                f->z = f->z + f->_034;
                f->_17E = f->_068 / f->_050;
            }
            f->_1E3 = 0;
        } else {
            f->_030 = f->_014 - f->x;
            f->_034 = f->_01C - f->z;
            f->x = f->_014;
            f->z = f->_01C;
            f->_068 = 0.0f;
            f->_050 = 0.0f;
            f->_1E3 = 1;
            f->_17E = -1;
        }
    }
    g_Fielders[0].x = g_Pitcher.pitcher.x;
    g_Fielders[0].z = g_Pitcher.pitcher.z;
}
#endif

// .text:0x000313B0 size:0x1E4 mapped:0x80670444
void fn_3_313B0(void) {
    int i;
    InMemFielderView* f;
    int k;
    for (i = 0; i < 9; i++) {
        f = &g_Fielders[i];
        if (g_d_GameSettings.minigamesEnabled != 0) {
            for (k = 0; k < 4; k++) {
                if (g_Minigame.minigameFielderIndex[k] == i) {
                    break;
                }
            }
            if (k >= 4) {
                continue;
            }
        }
        if (f->_050 > 0.0f) {
            if (lbl_3_common_bss_34C90._1D5 == 0) {
                f->_048 = atan2(f->_034, f->_030);
            }
        } else if (g_Pitcher.pitchTotalTimeCounter <= 0 && g_Runners[1].runnerOnFieldOrOutOrScored == 1 && i == 2 && g_d_GameSettings.minigamesEnabled == 0) {
            f->_048 = lbl_3_rodata_BC0;
        } else {
            f->_048 = atan2(-f->z, -f->x);
        }
        if (0.0f != f->_030 || 0.0f != f->_034) {
            f->_064 = atan2(f->_034, f->_030);
            f->_19A = radToShortAngle(f->_064);
        } else {
            f->_064 = 0.0f;
            f->_19A = -1;
        }
        if (g_d_GameSettings.minigamesEnabled != 0) {
            g_Minigame.minigameRelatedIndex = i;
            fn_3_544B8();
        }
    }
    if (g_d_GameSettings.minigamesEnabled != 0) {
        fn_3_53F48();
        return;
    }
    fn_3_544B8();
}

// .text:0x00031594 size:0xE4 mapped:0x80670628
void fn_3_31594(void) {
    InputStruct* in;
    s16* p;
    int i;
    in = &g_Controls[((s32)g_GameLogic.teams[g_GameLogic.teamFielding])];
    p = &lbl_3_bss_170 + 0x13;
    for (i = 0x13; i != 0; i--) {
        p[0] = p[-1];
        p--;
    }
    if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
        in = &g_Practice.inputs[g_GameLogic.teamFielding];
    }
    g_FieldingLogic.padButtons[0] = in->buttonInput;
    g_FieldingLogic.padButtons[1] = in->newButtonInput;
    g_FieldingLogic.padButtons[2] = in->_08;
    for (i = 0; i < 9; i++) {
        fn_3_55EEC(i);
    }
    fn_3_30D74();
    fn_3_313B0();
}

// .text:0x00031678 size:0x3C4 mapped:0x8067070C
// NONMATCHING 90%: registers only; the known SetFielderAct table-value/state r0 swap (see docs/patterns/unsolved.md)
#if NONMATCHING
void fn_3_31678(void) {
    int i;
    g_Fielders[0]._18C = 0;
    SetFielderAct(0, 1);
    g_FieldingLogic._0D0[0] = 0;
    if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
        SetFielderAct(1, 0x12);
    } else {
        SetFielderAct(1, 0xF);
    }
    g_Fielders[2]._18C = 1;
    SetFielderAct(2, 1);
    g_FieldingLogic._0D0[1] = 2;
    g_Fielders[4]._18C = 3;
    SetFielderAct(4, 1);
    g_FieldingLogic._0D0[3] = 4;
    if ((f32)__abs(g_Fielders[3]._182 - 0x400) < (f32)__abs(g_Fielders[5]._182 - 0x400)) {
        g_Fielders[3]._18C = 2;
        SetFielderAct(3, 1);
        g_FieldingLogic._0D0[2] = 3;
        SetFielderAct(5, 0);
    } else {
        g_Fielders[5]._18C = 2;
        SetFielderAct(5, 1);
        g_FieldingLogic._0D0[2] = 5;
        SetFielderAct(3, 0);
    }
    for (i = 0; i < 9; i++) {
        if (g_Fielders[i]._18C >= 0 && g_Fielders[i]._18C <= 3) {
            g_Fielders[i]._1D7 = 1;
        }
    }
    fn_3_49F40(6, 5);
    fn_3_49F40(7, 1);
    fn_3_49F40(8, 4);
}
#endif

// .text:0x00031A3C size:0x214 mapped:0x80670AD0
void fn_3_31A3C(void) {
    int i;
    InMemFielderView* f;
    int v;
    f32 d;
    for (i = 0; i < 9; i++) {
        f = &g_Fielders[i];
        if (i == 1) {
            f->_182 = 0x400;
        } else if (0.0f == f->x) {
            f->_182 = 0x400;
        } else {
            v = (int)(lbl_3_rodata_BC4 * (f32)atan2(f->z, f->x) / lbl_3_rodata_BC8);
            if (v < 0) {
                v += 0x800;
            }
            f->_182 = v;
        }
        d = f->x * f->x + f->z * f->z;
        SQRT_L(d);
        f->_070 = d;
    }
    fn_3_31678();
    g_Ball.physicsSubstruct.acceleration.x = 0.0f;
    g_Ball.physicsSubstruct.acceleration.y = 0.0f;
    g_Ball.physicsSubstruct.acceleration.z = 0.0f;
    g_Ball.ballState = 3;
    g_Ball.AtBat_ContactResult = 2;
    g_Ball.fielderAboutToGetBall_hasBall = -1;
    g_Ball.fielderBeingThrownTo = -1;
    g_Ball.ballIsLooseInd_unused = 0;
    g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt = 0;
}

// .text:0x00031C50 size:0x440 mapped:0x80670CE4
// NONMATCHING 90%: registers only; the known SetFielderAct table-value/state r0 swap (see docs/patterns/unsolved.md)
#if NONMATCHING
void fn_3_31C50(void) {
    int i;
    if (g_Pitcher.pickOffLoc == 5) {
        g_Fielders[0]._18C = 5;
        g_FieldingLogic._0D8 = 0;
        SetFielderAct(0, 0xE);
        g_Fielders[1]._18C = 0;
        SetFielderAct(1, 0xA);
        g_FieldingLogic._0D0[0] = 1;
    } else {
        SetFielderAct(0, 0xA);
        g_Fielders[1]._18C = 0;
        SetFielderAct(1, 1);
        g_FieldingLogic._0D0[0] = 1;
    }
    g_Fielders[2]._18C = 1;
    SetFielderAct(2, 1);
    g_FieldingLogic._0D0[1] = 2;
    g_Fielders[4]._18C = 3;
    SetFielderAct(4, 1);
    g_FieldingLogic._0D0[3] = 4;
    if ((f32)__abs(g_Fielders[3]._182 - 0x400) < (f32)__abs(g_Fielders[5]._182 - 0x400)) {
        g_Fielders[3]._18C = 2;
        SetFielderAct(3, 1);
        g_FieldingLogic._0D0[2] = 3;
        SetFielderAct(5, 0);
    } else {
        g_Fielders[5]._18C = 2;
        SetFielderAct(5, 1);
        g_FieldingLogic._0D0[2] = 5;
        SetFielderAct(3, 0);
    }
    for (i = 0; i < 9; i++) {
        if (g_Fielders[i]._18C >= 0 && g_Fielders[i]._18C <= 3) {
            g_Fielders[i]._1D7 = 1;
        }
    }
    fn_3_49F40(6, 5);
    fn_3_49F40(7, 1);
    fn_3_49F40(8, 4);
}
#endif

// .text:0x00032090 size:0x314 mapped:0x80671124
void fn_3_32090(void) {
    int i;
    InMemFielderView* f;
    int v;
    f32 d;
    for (i = 0; i < 9; i++) {
        f = &g_Fielders[i];
        if (i == 1) {
            f->_182 = 0x400;
        } else if (0.0f == f->x) {
            f->_182 = 0x400;
        } else {
            v = (int)(lbl_3_rodata_BC4 * (f32)atan2(f->z, f->x) / lbl_3_rodata_BC8);
            if (v < 0) {
                v += 0x800;
            }
            f->_182 = v;
        }
        d = f->x * f->x + f->z * f->z;
        SQRT_L(d);
        f->_070 = d;
    }
    fn_3_31C50();
    g_Ball.physicsSubstruct.velocity.x = 0.0f;
    g_Ball.physicsSubstruct.velocity.y = 0.0f;
    g_Ball.physicsSubstruct.velocity.z = 0.0f;
    g_Ball.physicsSubstruct.acceleration.x = 0.0f;
    g_Ball.physicsSubstruct.acceleration.y = 0.0f;
    g_Ball.physicsSubstruct.acceleration.z = 0.0f;
    g_Ball.ballState = 1;
    g_Ball.AtBat_ContactResult = 2;
    g_Ball.fielderAboutToGetBall_hasBall = 0;
    g_Ball.fielderBeingThrownTo = -1;
    g_Ball.ballIsLooseInd_unused = 0;
    g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt = 0;
    if (g_FieldingLogic._107 == 1 || g_FieldingLogic._107 == 2) {
        g_Ball.numberOfThrowsDuringPlay = 1;
    }
    if (g_Pitcher.pickOffLoc == 5) {
        g_Ball.AtBat_Contact_BallPos.x = g_Fielders[1].x;
        g_Ball.AtBat_Contact_BallPos.y = g_Fielders[1].y;
        g_Ball.AtBat_Contact_BallPos.z = g_Fielders[1].z;
        g_Ball.fielderWBallIndex = 1;
        return;
    }
    g_Ball.AtBat_Contact_BallPos.x = g_Fielders[0].x;
    g_Ball.AtBat_Contact_BallPos.y = g_Fielders[0].y;
    g_Ball.AtBat_Contact_BallPos.z = g_Fielders[0].z;
    g_Ball.fielderWBallIndex = 0;
    if (g_Pitcher.pickOffLoc >= 1 && g_Pitcher.pickOffLoc <= 3) {
        g_FieldingLogic._0C4 = g_Pitcher.pickOffLoc;
    }
    v = checkFieldingStat(g_GameLogic.teamFielding, g_Fielders[0].rosterID, 5);
    g_Fielders[0]._215 = lbl_3_data_4900[v][2];
}

// .text:0x000323A4 size:0x450 mapped:0x80671438
void fn_3_323A4(void) {
    s16 n;
    s16 t3;
    s16 t2;
    f32 d;
    if (g_Fielders[1]._1DA == 0) {
        if (g_Runners[3].runnerOnFieldOrOutOrScored == 1 && g_Runners[3].runningDirectionCode == 1 && g_Runners[3].fractionalBasesRan >= lbl_3_rodata_BCC &&
            (n = g_Fielders[1]._186) > 0) {
            d = g_Ball.physicsSubstruct.futureCoordsAndDist[n].pos.x * g_Ball.physicsSubstruct.futureCoordsAndDist[n].pos.x +
                g_Ball.physicsSubstruct.futureCoordsAndDist[n].pos.z * g_Ball.physicsSubstruct.futureCoordsAndDist[n].pos.z;
            SQRT_L(d);
            if (d < lbl_3_rodata_B64) {
                g_FieldingLogic._0B0 = 1;
                g_FieldingLogic._0B2 = 0;
            } else {
                g_FieldingLogic._0B0 = 0;
            }
        } else {
            g_FieldingLogic._0B0 = 1;
            g_FieldingLogic._0B2 = 0;
        }
    } else {
        g_FieldingLogic._0B0 = 0;
    }
    if (g_Ball.Hit_HorizontalAngle < 0x400) {
        t3 = g_Fielders[3]._186;
        t2 = g_Fielders[2]._186;
        if (t3 - 15 < t2) {
            if (g_Fielders[0]._186 - t3 < 120) {
                g_FieldingLogic._0B2 = 3;
            } else {
                goto def2;
            }
        } else if (g_Ball.physicsSubstruct.futureCoordsAndDist[t2].pos.z < lbl_3_data_4444[3]) {
            if (g_Fielders[0]._186 - t2 < 80) {
                g_FieldingLogic._0B2 = 2;
            } else {
                goto def2;
            }
        } else if (g_Fielders[0]._186 - t3 < 120) {
            g_FieldingLogic._0B2 = 3;
        } else {
        def2:
            g_FieldingLogic._0B2 = 2;
        }
    } else {
        t3 = g_Fielders[5]._186;
        t2 = g_Fielders[4]._186;
        if (t3 - 15 < t2) {
            if (g_Fielders[0]._186 - t3 < 120) {
                g_FieldingLogic._0B2 = 5;
            } else {
                goto def4;
            }
        } else if (g_Ball.physicsSubstruct.futureCoordsAndDist[t2].pos.z < lbl_3_data_4444[3]) {
            if ((g_Runners[2].runnerOnFieldOrOutOrScored != 1 || t2 <= 0) && g_Fielders[0]._186 - t2 < 80) {
                g_FieldingLogic._0B2 = 4;
            } else {
                goto def4;
            }
        } else if (g_Fielders[0]._186 - t3 < 120) {
            g_FieldingLogic._0B2 = 5;
        } else {
        def4:
            g_FieldingLogic._0B2 = 4;
        }
    }
    SetFielderAct(g_FieldingLogic._0B0, 0x15);
    if (g_FieldingLogic._0B2 >= 0) {
        SetFielderAct(g_FieldingLogic._0B2, 0x16);
    }
}

// .text:0x000327F4 size:0x1C mapped:0x80671888

s32 fn_3_327F4(void) {
    return g_Ball.hitClassification2 == 1;
}

// .text:0x00032810 size:0x194 mapped:0x806718A4
// NONMATCHING 98%: registers only; the known SetFielderAct table-value/state r0 swap (see docs/patterns/unsolved.md)
#if NONMATCHING
void fn_3_32810(void) {
    SetFielderAct(0, 0x15);
    g_FieldingLogic._0B0 = 0;
    if (g_Ball.Hit_HorizontalAngle < 0x400) {
        g_FieldingLogic._0B2 = 3;
    } else {
        g_FieldingLogic._0B2 = 5;
    }
    SetFielderAct(3, 0x16);
    SetFielderAct(5, 0x16);
    g_FieldingLogic._13A = 1;
    SetFielderAct(7, 0x17);
    g_FieldingLogic._0B4 = 7;
    g_FieldingLogic._139 = 1;
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}
#endif

// .text:0x000329A4 size:0x6E4 mapped:0x80671A38
// NONMATCHING 90%: registers only; the known SetFielderAct table-value/state r0 swap (see docs/patterns/unsolved.md)
#if NONMATCHING
void fn_3_329A4(void) {
    s16 ang = g_Ball.Hit_HorizontalAngle;
    if (g_Ball.Hit_VerticalAngle >= 0x400 && g_Ball.Hit_VerticalAngle <= 0xC00) {
        ang += 0x800;
        if (ang > 0x1000) {
            ang -= 0x1000;
        }
    }
    if (ang >= 0xE00) {
        g_FieldingLogic._0B0 = 1;
        SetFielderAct(2, 0x10);
    } else if (ang >= 0xA00) {
        g_FieldingLogic._0B0 = 1;
    } else if (ang >= 0x800) {
        g_FieldingLogic._0B0 = 1;
        SetFielderAct(4, 0x10);
    } else if (ang >= 0x400) {
        if (g_Ball.Hit_VerticalAngle < 0x40) {
            g_FieldingLogic._0B0 = 4;
            SetFielderAct(6, 0x10);
        } else if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_BA0) {
            g_FieldingLogic._0B0 = 1;
            SetFielderAct(4, 0x10);
            SetFielderAct(6, 0x10);
        } else if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_B9C) {
            g_FieldingLogic._0B0 = 4;
            SetFielderAct(5, 0x10);
            SetFielderAct(6, 0x10);
        } else if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_BD0) {
            g_FieldingLogic._0B0 = 5;
            SetFielderAct(4, 0x10);
            SetFielderAct(6, 0x10);
        } else {
            g_FieldingLogic._0B0 = 6;
            SetFielderAct(5, 0x10);
        }
    } else if (g_Ball.Hit_VerticalAngle < 0x40) {
        g_FieldingLogic._0B0 = 2;
        SetFielderAct(8, 0x10);
    } else if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_BA0) {
        g_FieldingLogic._0B0 = 1;
        SetFielderAct(2, 0x10);
        SetFielderAct(8, 0x10);
    } else if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_B9C) {
        g_FieldingLogic._0B0 = 2;
        SetFielderAct(3, 0x10);
        SetFielderAct(8, 0x10);
    } else {
        /* note: the original has no else here, so the < 40 case is overwritten below */
        if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_BD0) {
            g_FieldingLogic._0B0 = 3;
            SetFielderAct(2, 0x10);
            SetFielderAct(8, 0x10);
        }
        g_FieldingLogic._0B0 = 8;
        SetFielderAct(3, 0x10);
    }
    SetFielderAct(g_FieldingLogic._0B0, 0x15);
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}
#endif

// .text:0x00033088 size:0x3D0 mapped:0x8067211C
// NONMATCHING 94%: distance sums unfused (fmuls+fadds) in the original; g_Fielders base kept in r31 there
#if NONMATCHING
void fn_3_33088(void) {
    InMemFielderView* c;
    s16 ang = fn_3_9FB8C(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
    s32 other = 6;
    InMemFielderView* o;
    f32 dc;
    f32 dother;
    f32 dx;
    f32 dz;
    c = &g_Fielders[7];
    if (ang < c->_182) {
        other = 8;
    }
    o = &g_Fielders[other];
    if (c->_1DD == 1 && o->_1DD == 1) {
        if (c->_1DB == 0 && o->_1DB == 0 && c->_186 == o->_186) {
            dx = (&g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.x)[c->_186 * 4] - c->x;
            dz = (&g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.z)[c->_186 * 4] - c->z;
            dc = dx * dx + dz * dz;
            SQRT_L(dc);
            dx = (&g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.x)[o->_186 * 4] - o->x;
            dz = (&g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.z)[o->_186 * 4] - o->z;
            dother = dx * dx + dz * dz;
            SQRT_L(dother);
            if (dc < dother) {
                g_FieldingLogic._0B2 = 7;
            } else {
                g_FieldingLogic._0B2 = other;
            }
        } else if (c->_186 <= o->_186) {
            g_FieldingLogic._0B2 = 7;
        } else {
            g_FieldingLogic._0B2 = other;
        }
    } else if (c->_1DD == 1) {
        g_FieldingLogic._0B2 = 7;
    } else if (o->_1DD == 1) {
        g_FieldingLogic._0B2 = other;
    } else if (__abs(ang - c->_182) < __abs(ang - o->_182) + 0x60) {
        g_FieldingLogic._0B2 = 7;
    } else {
        g_FieldingLogic._0B2 = other;
    }
}
#endif

// .text:0x00033458 size:0x94 mapped:0x806724EC
void fn_3_33458(void) {
    InMemFielderView* f;
    s16 i;
    fn_3_334EC(1);
    fn_3_33088();
    i = g_FieldingLogic._0B2;
    f = &g_Fielders[i];
    if (i != -1) {
        f->_1D3 = 0x16;
        if (lbl_3_data_3C40[22].anim >= 0) {
            g_FieldingLogic._0F8[i] = lbl_3_data_3C40[22].anim;
        }
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_1A4 = 0;
        f->_1AC = 0;
        f->_1FF = 0;
    }
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}

// .text:0x000334EC size:0x8B0 mapped:0x80672580
#define FLD_HANG(n) (g_Fielders[(n)]._182)
// NONMATCHING 98%: distance sums unfused (fmuls+fadds) in the original; second-pick local typed s16 there; register numbering
#if NONMATCHING
void fn_3_334EC(int a) {
    s32 sel;
    s32 j;
    s32 w;
    s32 second;
    f32 best;
    f32 d;
    f32 dx;
    f32 dz;
    InMemFielderView* f;
    if (g_Ball.hitClassification2 == 1) {
        fn_3_323A4();
    } else if (g_Ball.maxYOfHit >= lbl_3_rodata_B64 && a == 0) {
        dx = g_Fielders[0].x - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
        dz = g_Fielders[0].z - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        best = d + lbl_3_rodata_B78;
        sel = 0;
        f = &g_Fielders[1];
        for (j = 1; j < 6; j++, f++) {
            dx = f->x - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            dz = f->z - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
            d = dx * dx + dz * dz;
            SQRT_L(d);
            if (j == 3 || j == 5) {
                d -= lbl_3_rodata_B78;
            }
            if (d < best) {
                best = d;
                sel = j;
            }
        }
        g_FieldingLogic._0B0 = sel;
        SetFielderAct(sel, 0x15);
        if ((g_FieldingLogic._0B0 == 3 || g_FieldingLogic._0B0 == 5) &&
            g_Ball.landingSpotAngle >= 0x3B8 && g_Ball.landingSpotAngle <= 0x448) {
            if (g_FieldingLogic._0B0 == 3) {
                g_FieldingLogic._0B2 = 5;
            } else {
                g_FieldingLogic._0B2 = 3;
            }
            g_FieldingLogic._13A = 1;
        }
    } else {
        w = 0x8C - g_Ball.Hit_HorizontalPower;
        if (w < 0) {
            w = 0;
        }
        if (w > 0x40) {
            w = 0x40;
        }
        if (g_Ball.Hit_HorizontalAngle >= 0x3A8 - w && g_Ball.Hit_HorizontalAngle < w + 0x458 && a == 0) {
            g_FieldingLogic._0B0 = 0;
            if (g_Ball.Hit_HorizontalAngle < FLD_HANG(3) + (FLD_HANG(5) - FLD_HANG(3)) / 2) {
                g_FieldingLogic._0B2 = 3;
            } else {
                g_FieldingLogic._0B2 = 5;
            }
            if (g_Ball.landingSpotAngle >= 0x3B8 && g_Ball.landingSpotAngle <= 0x448) {
                g_FieldingLogic._13A = 1;
                if (g_FieldingLogic._0B2 == 3) {
                    SetFielderAct(5, 0x16);
                } else {
                    SetFielderAct(3, 0x16);
                }
            }
        } else if (g_Ball.Hit_HorizontalAngle < FLD_HANG(2) + (FLD_HANG(3) - FLD_HANG(2)) / 7) {
            g_FieldingLogic._0B0 = 2;
        } else if (g_Ball.Hit_HorizontalAngle < FLD_HANG(2) + (FLD_HANG(3) - FLD_HANG(2)) * 2 / 5) {
            g_FieldingLogic._0B0 = 2;
            g_FieldingLogic._0B2 = 3;
            SetFielderAct(3, 0x16);
        } else if (g_Ball.Hit_HorizontalAngle < FLD_HANG(3) + (FLD_HANG(5) - FLD_HANG(3)) / 2) {
            g_FieldingLogic._0B0 = 3;
        } else if (g_Ball.Hit_HorizontalAngle < FLD_HANG(5) + (FLD_HANG(4) - FLD_HANG(5)) * 3 / 5) {
            g_FieldingLogic._0B0 = 5;
        } else if (g_Ball.Hit_HorizontalAngle < FLD_HANG(4) - (FLD_HANG(4) - FLD_HANG(5)) / 5) {
            g_FieldingLogic._0B0 = 4;
            g_FieldingLogic._0B2 = 5;
            SetFielderAct(5, 0x16);
        } else {
            g_FieldingLogic._0B0 = 4;
        }
    }
    SetFielderAct(g_FieldingLogic._0B0, 0x15);
    if (a != 0) {
        return;
    }
    second = g_FieldingLogic._0B2;
    if (second < 0) {
        fn_3_33088();
        SetFielderAct(g_FieldingLogic._0B2, 0x16);
    } else {
        fn_3_33088();
        g_FieldingLogic._0B4 = g_FieldingLogic._0B2;
        g_FieldingLogic._0B2 = second;
        SetFielderAct(second, 0x16);
        SetFielderAct(g_FieldingLogic._0B4, 0x17);
        g_FieldingLogic._139 = 1;
    }
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}
#endif
#undef FLD_HANG

// .text:0x00033D9C size:0x34 mapped:0x80672E30
void fn_3_33D9C(void) {
    fn_3_49F40(6, 7);
    fn_3_49F40(8, 6);
}

// .text:0x00033DD0 size:0x418 mapped:0x80672E64
// NONMATCHING 97%: 10.0f const load scheduled after the operands in the s7==0 branch; *first=7 store order in the 0x1BBF branch
#if NONMATCHING
void fn_3_33DD0(s32* first, s32* second) {
    InMemFielderView* fl = g_Fielders;
    s32 other = 6;
    s16 ang;
    InMemFielderView* f;
    s32 s7;
    s32 so;
    s32 close;
    f32 d;
    *second = -1;
    ang = fn_3_9FB8C(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
    if (ang > g_Fielders[6]._182) {
        *first = 6;
        return;
    }
    if (ang < g_Fielders[8]._182) {
        *first = 8;
        return;
    }
    if (ang < g_Fielders[7]._182) {
        other = 8;
    }
    so = 10;
    f = &g_Fielders[other];
    s7 = 10;
    if (fl[7]._1DB == 0) {
        s7 = 0;
    } else if (fl[7]._1DD == 1) {
        s7 = 1;
    } else if (fl[7]._1DD == 2) {
        s7 = 2;
    } else if (fl[7]._1DD == 3) {
        s7 = 3;
    }
    if (f->_1DB == 0) {
        so = 0;
    } else if (f->_1DD == 1) {
        so = 1;
    } else if (f->_1DD == 2) {
        so = 2;
    } else if (f->_1DD == 3) {
        so = 3;
    }
    close = 0;
    if (g_Ball.wallAndBallIntersectionDistFromHome > lbl_3_rodata_BD0) {
        d = fl[7]._080 - f->_080;
        if (d < lbl_3_rodata_B20) {
            d = -d;
        }
        if (d < lbl_3_rodata_BA0) {
            close = 1;
        }
    }
    if ((s7 == so && s7 < 10) || close != 0) {
        if (s7 == 0) {
            if (fl[7]._080 <= f->_080) {
                *first = 7;
                if (f->_080 - fl[7]._080 < lbl_3_rodata_BA0) {
                    *second = other;
                }
            } else {
                *first = other;
                if (fl[7]._080 - f->_080 < lbl_3_rodata_BA0) {
                    *second = 7;
                }
            }
            return;
        }
        if (s7 == 1) {
            if (fl[7]._186 <= f->_186) {
                *first = 7;
                if (f->_186 - fl[7]._186 < 0x2D) {
                    *second = other;
                }
            } else {
                *first = other;
                if (fl[7]._186 - f->_186 < 0x2D) {
                    *second = 7;
                }
            }
            return;
        }
    } else if (s7 < so) {
        if (s7 == 0) {
            *first = 7;
            if (so == 1 && f->_186 - fl[7]._186 < 0x1E) {
                *second = other;
            }
            return;
        }
        if (s7 == 1) {
            *first = 7;
            return;
        }
        if (so == 10) {
            *first = 7;
            return;
        }
    } else if (so < s7) {
        if (so == 0) {
            *first = other;
            if (s7 == 1 && fl[7]._186 - f->_186 < 0x1E) {
                *second = 7;
            }
            return;
        }
        if (so == 1) {
            *first = other;
            return;
        }
        if (s7 == 10) {
            *first = other;
            return;
        }
    }
    if (g_Ball.landingSpotZoneAwayFromHome >= 3) {
        d = fl[7]._080 - f->_080;
        if (d < lbl_3_rodata_B20) {
            *first = 7;
            if (d > lbl_3_rodata_BD4) {
                *second = other;
            }
        } else {
            *first = other;
            if (d < lbl_3_rodata_BA0) {
                *second = 7;
            }
        }
    } else if (__abs(ang - fl[7]._182) < __abs(ang - f->_182) + 0x40) {
        *first = 7;
        *second = other;
    } else {
        *first = other;
        *second = 7;
    }
}
#endif

// .text:0x000341E8 size:0x268 mapped:0x8067327C
// NONMATCHING 99%: SetFielderAct state/table regs r0/r4 swapped (see docs/patterns/unsolved.md)
#if NONMATCHING
void fn_3_341E8(void) {
    s32 first;
    s32 second;
    s16 ang;
    fn_3_33DD0(&first, &second);
    g_FieldingLogic._0B0 = first;
    g_FieldingLogic._0B2 = second;
    SetFielderAct((s16)first, 0x16);
    SetFielderAct(g_FieldingLogic._0B2, 0x16);
    if (g_FieldingLogic._0B2 >= 0) {
        g_FieldingLogic._139 = 1;
    } else {
        ang = fn_3_9FB8C(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
        if (g_FieldingLogic._0B0 == 7) {
            if (ang < 0x400) {
                SetFielderAct(8, 0x18);
                g_FieldingLogic._0BC = 8;
            } else {
                SetFielderAct(6, 0x18);
                g_FieldingLogic._0BC = 6;
            }
        } else {
            SetFielderAct(7, 0x18);
            g_FieldingLogic._0BC = 7;
        }
    }
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_33D9C();
}
#endif

// .text:0x00034450 size:0x5F0 mapped:0x806734E4
// NONMATCHING 98%: loop-variable register order; one distance sum unfused in the original; calls fn_3_4F504/fn_3_4FB34 through casts until their prototypes gain the index arg
#if NONMATCHING
void fn_3_34450(void) {
    InMemFielderView* f = g_Fielders;
    s64 mask = 0;
    s32 i = 0;
    s32 sh = 0;
    f32 d;
    f32 dx;
    f32 dz;
    s32 a;
    for (; i < 9; i++, sh += 3, f++) {
        if (i == 1) {
            f->_182 = 0x400;
        } else if (lbl_3_rodata_B20 == f->x) {
            f->_182 = 0x400;
        } else {
            a = (s32)(lbl_3_rodata_BC4 * (f32)atan2(f->z, f->x) / lbl_3_rodata_BC8);
            if (a < 0) {
                a += 0x800;
            }
            f->_182 = a;
        }
        d = f->x * f->x + f->z * f->z;
        SQRT_L(d);
        f->_070 = d;
        dx = g_Ball.landingSpotLocation.x - f->x;
        dz = g_Ball.landingSpotLocation.z - f->z;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        f->_080 = d;
        if (i == 1) {
            fn_3_4F504(1);
        } else {
            fn_3_4FB34(i);
        }
        if (f->_1DD == 1) {
            mask |= 4 << sh;
        } else if (f->_1DD == 2) {
            mask |= 2 << sh;
        } else if (f->_1DD == 3) {
            mask |= 1 << sh;
        }
    }
    if (g_d_GameSettings.GameModeSelected == 2 && g_GameLogic.secondaryGameMode == 0xC) {
        SetFielderAct(0, 0x15);
        return;
    }
    if (g_Ball.lineDriveThroughPitcherInd != 0) {
        fn_3_32810();
    } else if (g_Ball.hitClassification3 == 7 || g_Ball.hitClassification3 == 8) {
        fn_3_329A4();
    } else if ((mask & 0x3FFFF) == 0 || (g_Ball.landingSpotZoneAwayFromHome == 4 && g_Ball.maxYOfHit > lbl_3_rodata_BD8)) {
        if (g_Ball.maxYOfHit < lbl_3_rodata_B64) {
            PairPlayInline();
        } else {
            fn_3_341E8();
        }
    } else if ((mask & 0x2DB6D) != 0) {
        fn_3_334EC(0);
    } else if ((mask & 0x12480) != 0) {
        PairPlayInline();
    } else if ((mask & 2) != 0) {
        fn_3_334EC(0);
    }
    g_FieldingLogic._0B8 = g_FieldingLogic._0B2;
    g_FieldingLogic._0BA = g_FieldingLogic._0B4;
}
#endif

// .text:0x00034A40 size:0x12E8 mapped:0x80673AD4
// NONMATCHING 96%: f-reg numbering throughout; three distance sums unfused in the original; calls fn_3_526DC through a cast until its prototype gains the index arg
#if NONMATCHING
void fn_3_34A40(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 dx;
    f32 dz;
    f32 d;
    s32 k;
    s32 t;
    if (g_Ball.fielderWBallIndex >= 0 && g_Ball.fielderWBallIndex != i) {
        if (f->_050 == lbl_3_rodata_B20) {
            f->_068 = lbl_3_rodata_B20;
            f->_014 = f->x;
            f->_018 = f->y;
            f->_01C = f->z;
            f->_030 = lbl_3_rodata_B20;
            f->_034 = lbl_3_rodata_B20;
        }
    } else {
        f->_1D6 = 0;
        f->_1EB = 0;
        f->_1A4 = 0;
        if (g_Ball.fielderAboutToGetBall_hasBall >= 0 && !(g_Ball.AtBat_ContactResult == 0 && g_Ball.hitClassification1 == 2)) {
            goto track;
        }
        if (g_Ball.fielderAboutToGetBall_hasBall >= 0) {
            /* ground ball fielded on the infield: go to / cut off the ball */
            dx = g_Ball.ballWillHitBallPos.x - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            dz = g_Ball.ballWillHitBallPos.z - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
            d = dx * dx + dz * dz;
            SQRT_L(d);
            if (g_Ball.ballVelocity > lbl_3_rodata_B20 || d > lbl_3_rodata_B9C) {
                if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < lbl_3_rodata_B78) {
                    f32 r = f->_070;
                    if (r < lbl_3_rodata_B70) {
                        SetRunTargetInline(f, f->x, f->z);
                    } else {
                        SetRunTargetInline(f, lbl_3_rodata_B70 * (f->x / r), lbl_3_rodata_B70 * (f->z / r));
                    }
                } else {
                    SetRunTargetInline(f,
                                       lbl_3_rodata_B70 * (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x / g_Ball.physicsSubstruct.hitLandingSpotDistFromHome) +
                                           g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                       lbl_3_rodata_B70 * (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z / g_Ball.physicsSubstruct.hitLandingSpotDistFromHome) +
                                           g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
                }
            } else {
                SetRunTargetInline(f, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
            }
            if (f->_068 < lbl_3_rodata_BA0) {
                f->_1D6 = 8;
            }
        } else if (g_Ball.AtBat_ContactResult == 0) {
            /* ball on the ground, nobody assigned: chase the landing point or a later trajectory point */
            if (g_Ball.framesUntilBallHitsGround - EtaToInline(f, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z) > 0xA) {
                SetRunTargetInline(f, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
            } else {
                for (k = 10; k <= 60; k += 10) {
                    if (k == 60) {
                        t = g_Ball.framesUntilBallHitsGround + k;
                        SetRunTargetInline(f, g_Ball.physicsSubstruct.futureCoordsAndDist[t].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[t].pos.z);
                        break;
                    }
                    t = g_Ball.framesUntilBallHitsGround + k;
                    if (t - EtaToInline(f, g_Ball.physicsSubstruct.futureCoordsAndDist[t].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[t].pos.z) > 5) {
                        SetRunTargetInline(f, g_Ball.physicsSubstruct.futureCoordsAndDist[t].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[t].pos.z);
                        break;
                    }
                }
            }
            if (i <= 5) {
                if (f->_080 < lbl_3_rodata_BA0) {
                    f->_1D6 = 8;
                }
            } else if (g_FieldingLogic._0B0 <= 5 &&
                       g_Ball.ballDistanceFromHome <
                           g_Fielders[g_FieldingLogic._0B0]._070) {
                if (f->_080 < lbl_3_rodata_B64) {
                    f->_1D6 = 8;
                }
            } else if (f->_080 < lbl_3_rodata_BA0) {
                f->_1D6 = 8;
            }
        } else {
            f32 near;
            f32 reach;
            f32 lead;
            f32 tx;
            f32 tz;
        track:
            /* ball in flight: lead the ball along its velocity */
            near = f->_07C;
            reach = f->_074;
            lead = lbl_3_rodata_B60 + ((near - lbl_3_rodata_B70) / lbl_3_rodata_BDC + (g_Ball.ballVelocity - lbl_3_rodata_BE0));
            tx = lead * (reach * g_Ball.ballVelocityPercent.x) + g_Ball.AtBat_Contact_BallPos.x;
            tz = lead * (reach * g_Ball.ballVelocityPercent.z) + g_Ball.AtBat_Contact_BallPos.z;
            if (i >= 6 && f->_070 < lbl_3_rodata_BB0) {
                tx = f->x;
                tz = f->z;
            }
            SetRunTargetInline(f, tx, tz);
            if (f->_074 < lbl_3_rodata_B9C && near < lbl_3_rodata_B64) {
                if (lbl_3_bss_170 >= 0) {
                    s16 a = radToShortAngle(atan2(g_Ball.AtBat_Contact_BallPos.z - f->z, g_Ball.AtBat_Contact_BallPos.x - f->x));
                    if (__abs(lbl_3_bss_170 - a) > 0x80) {
                        f->_1D6 = 8;
                    }
                } else {
                    f->_1D6 = 8;
                }
            }
        }
    }
    if (f->_050 < lbl_3_rodata_B48 && f->_1D6 == 8) {
        f->_068 = lbl_3_rodata_B20;
        f->_050 = lbl_3_rodata_B20;
        f->_014 = f->x;
        f->_01C = f->z;
        f->_1A0 = 0;
        f->_1D6 = 0;
    }
    fn_3_526DC(i);
    if (f->_050 != lbl_3_rodata_B20) {
        f->_17E = f->_068 / f->_050;
    }
}
#endif

// .text:0x00035D28 size:0xF4 mapped:0x80674DBC
void fn_3_35D28(int i) {
    InMemFielderView* f = &g_Fielders[i];
    if (g_Ball.framesSinceHit > 0 && fn_3_53130(i) == 0) {
        fn_3_34A40(i);
        fn_3_4207C(i);
        if (g_Ball.ballState != 0 && g_Ball.ballState != 3) {
            if (i != -1) {
                int v;
                f->_1D3 = 12;
                v = lbl_3_data_3C40[12].anim;
                if (v >= 0) {
                    g_FieldingLogic._0F8[i] = v;
                }
                f->_1D5 = 0;
                f->_1D6 = 0;
                f->_1A4 = 0;
                f->_1AC = 0;
                f->_1FF = 0;
            }
            if (i <= 5) {
                f->_1D5 = 3;
            } else {
                f->_1D5 = 2;
            }
        }
    }
}

// .text:0x00035E1C size:0x3BC mapped:0x80674EB0
// NONMATCHING 79%: the original unrolls the 6-entry search loop by 3 (ctr=2); ours (s16 counter) is not unrolled, an s32 counter unrolls it fully
#if NONMATCHING
void fn_3_35E1C(void) {
    s32 a = -1;
    s32 mode = 0;
    s32 b = -1;
    s16 i;
    f32 dx;
    f32 dz;
    f32 d;
    if (g_Ball.ballZoneAwayFromHome >= 3 && g_FieldingLogic._0C4 == 0) {
        mode = 1;
    } else if (g_Ball.ballZoneAwayFromHome <= 1) {
        mode = 2;
    }
    for (i = 0; i < 6; i++) {
        if (g_FieldingLogic._0F8[i] != 2 && i != g_Ball.throwingFielder) {
            if (a != -1) {
                b = i;
                break;
            }
            a = i;
        }
    }
    if (mode != 0 && a >= 0 && b >= 0) {
        if (!(g_Fielders[a]._0B8 < g_Fielders[b]._0B8)) {
            a = b;
        }
    } else {
        dx = g_Ball.throwTarget.x - g_Ball.AtBat_Contact_BallPos.x;
        dz = g_Ball.throwTarget.z - g_Ball.AtBat_Contact_BallPos.z;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        if (d < g_Fielders[a]._074) {
            a = -1;
        }
        if (d < g_Fielders[b]._074) {
            b = -1;
        }
        if (a < 0) {
            a = b;
            b = -1;
        }
        if (a < 0) {
            return;
        }
        if (b >= 0 && g_Fielders[a]._07C > g_Fielders[b]._07C) {
            a = b;
        }
    }
    if (a < 0) {
        return;
    }
    if (mode == 2) {
        if (g_Fielders[a]._07C > lbl_3_rodata_B68) {
            return;
        }
    } else if (mode == 0 && g_Fielders[a]._07C > lbl_3_rodata_B8C) {
        return;
    }
    SetFielderAct(a, 0x19);
    g_FieldingLogic._0C2 = a;
}
#endif

// .text:0x000361D8 size:0x3F8 mapped:0x8067526C
// NONMATCHING 96%: zero-init of i0/i1/i2 is li x3 (orig li+mr+mr); inlined fn_3_365D0 tail keeps an extra mr
#if NONMATCHING
int fn_3_361D8(f32 x, f32 z) {
    f32 d3, d2, d1, d0;
    f32 d;
    s32 i3, i2, i1, i0;
    s32 a1, a2, a0, a3;
    s32 ang;
    InMemFielderView* f;
    s32 i;
    s32 r;
    i2 = 0;
    d0 = d1 = d2 = d3 = lbl_3_rodata_BA4;
    f = g_Fielders;
    i0 = i1 = i2;
    i3 = 0;
    for (i = 0; i < 9; i++, f++) {
        f32 dx = f->x - x;
        f32 dz = f->z - z;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        ang = (s16)fn_3_9FB8C(dx, dz);
        if (d0 > d) {
            d2 = d1;
            i2 = i1;
            d1 = d0;
            a2 = a1;
            i1 = i0;
            a1 = a0;
            d0 = d;
            i0 = i;
            a0 = ang;
        } else if (d1 > d) {
            d2 = d1;
            i2 = i1;
            d1 = d;
            a2 = a1;
            i1 = i;
            a1 = ang;
        } else if (d2 > d) {
            d3 = d2;
            i3 = i2;
            d2 = d;
            a3 = a2;
            i2 = i;
            a2 = ang;
        } else if (d3 > d) {
            d3 = d;
            i3 = i;
            a3 = ang;
        }
    }
    if (d3 - lbl_3_rodata_B70 < d2) {
        if (fn_3_9FCF8(a1, a2) < 0x180) {
            if (fn_3_9FCF8(a0, a3) > 0x200 && fn_3_9FCF8(a1, a3) > 0x200) {
                i2 = i3;
            }
        } else if (fn_3_9FCF8(a0, a2) < 0x180) {
            if (fn_3_9FCF8(a0, a3) > 0x200 && fn_3_9FCF8(a1, a3) > 0x200) {
                i2 = i3;
            }
        } else if (fn_3_9FCF8(a0, a1) < 0x180 && fn_3_9FCF8(a0, a3) > 0x200 && fn_3_9FCF8(a2, a3) > 0x200) {
            i1 = i2;
            i2 = i3;
        }
    }
    i0 = Pick3Inline(i0, i1, i2, x, z);
    return i0;
}
#endif

// .text:0x000365D0 size:0xA8 mapped:0x80675664
int fn_3_365D0(int a, int b, int c, f32 x, f32 y) {
    int r = fn_3_36678(b, c, x, y, 1);
    if (r == -1) {
        return a;
    }
    if (g_FieldingLogic._0B0 < 0) {
        return fn_3_36678(a, r, x, y, 1);
    }
    return fn_3_36678(a, r, x, y, 0);
}

// .text:0x00036678 size:0xA9C mapped:0x8067570C
// NONMATCHING 91%: fielder x/z read via lfsx in the original; dist sums are unfused fmuls+fadds there; f-reg numbering
#if NONMATCHING
int fn_3_36678(int a, int b, f32 x, f32 z, int mode) {
    InMemFielderView* fa;
    InMemFielderView* fb;
    s16 angA;
    s16 angB;
    s16 angDiff;
    f32 distA;
    f32 distB;
    f32 dx;
    f32 dz;
    s16 dA;
    s16 dB;
    if (lbl_3_bss_16C < 0) {
        return -1;
    }
    fa = &g_Fielders[a];
    fb = &g_Fielders[b];
    angA = radToShortAngle(atan2(z - fa->z, x - fa->x));
    angB = radToShortAngle(atan2(z - fb->z, x - fb->x));
    angDiff = fn_3_9FCF8(angA, angB);
    dx = fa->x - x;
    dz = fa->z - z;
    distA = dx * dx + dz * dz;
    SQRT_L(distA);
    dx = fb->x - x;
    dz = fb->z - z;
    distB = dx * dx + dz * dz;
    SQRT_L(distB);
    if (angDiff <= 0x100) {
        if (distA < distB) {
            return a;
        }
        return b;
    }
    if (mode < 2) {
        s32 sel;
        s32 d;
        if (g_FieldingLogic._0B0 == a) {
            distA -= lbl_3_rodata_B78;
            if (distA < lbl_3_rodata_B20) {
                distA = lbl_3_rodata_B20;
            }
        } else if (g_FieldingLogic._0B0 == b) {
            distB -= lbl_3_rodata_B78;
            if (distB < lbl_3_rodata_B20) {
                distB = lbl_3_rodata_B20;
            }
        }
        if ((&lbl_3_bss_170)[3] >= 0) {
            d = __abs((&lbl_3_bss_170)[0] - (&lbl_3_bss_170)[3]);
            if (d > 0x800) {
                d = 0x1000 - d;
            }
            if (d <= 0x400) {
                f32 home;
                f32 step;
                f32 lim;
                sel = -1;
                if (a == g_FieldingLogic._0B0) {
                    sel = a;
                }
                if (b == g_FieldingLogic._0B0) {
                    sel = b;
                }
                if (sel >= 0) {
                    InMemFielderView* fs = &g_Fielders[sel];
                    f32 dSel;
                    f32 dTgt;
                    dx = fs->x - x;
                    dz = fs->z - z;
                    dSel = dx * dx + dz * dz;
                    SQRT_L(dSel);
                    dx = fs->_0D4 - x;
                    dz = fs->_0D8 - z;
                    dTgt = dx * dx + dz * dz;
                    SQRT_L(dTgt);
                    if (dSel > dTgt) {
                        goto compare;
                    }
                }
                step = lbl_3_rodata_BE4;
                home = x * x + z * z;
                SQRT_L(home);
                if (home < lbl_3_rodata_BE8) {
                    step = lbl_3_rodata_B8C;
                } else if (home < lbl_3_rodata_BEC) {
                    step = lbl_3_rodata_B64;
                } else if (home < lbl_3_rodata_BF0) {
                    step = lbl_3_rodata_BF4;
                }
                lim = lbl_3_rodata_BD8;
                if (home < lbl_3_rodata_BEC) {
                    lim = lbl_3_rodata_B8C;
                } else if (home < lbl_3_rodata_BF0) {
                    lim = lbl_3_rodata_BBC * (home - lbl_3_rodata_BE8) + lbl_3_rodata_B8C;
                }
                if (a == g_FieldingLogic._0B0) {
                    if (distA > lim) {
                        distA -= step;
                    } else {
                        distA = lbl_3_rodata_B20;
                    }
                }
                /* the original compares and subtracts distA here, not distB */
                if (b == g_FieldingLogic._0B0 && distA > lim) {
                    distB = distA - step;
                }
            }
        }
    }
compare:
    if (distB < distA) {
        f32 tf = distA;
        int ti = a;
        s16 ta = angA;
        distA = distB;
        a = b;
        angA = angB;
        distB = tf;
        b = ti;
        angB = ta;
    }
    if (mode < 3) {
        f32 gap;
        if (distA < lbl_3_rodata_B68) {
            return a;
        }
        gap = distB - distA;
        if (gap > lbl_3_rodata_B70) {
            if (gap > lbl_3_rodata_B9C && g_Ball.AtBat_ContactResult == 1 && a >= 6) {
                return a;
            }
            if (g_Ball.ballState != 0 || g_Ball.AtBat_ContactResult != 1) {
                return a;
            }
            if (a == 1 && gap > lbl_3_rodata_B9C) {
                return a;
            }
        }
        if (gap > lbl_3_rodata_BA0 && distA < lbl_3_rodata_BE4) {
            return a;
        }
        if (distA < lbl_3_rodata_B64 && distB < lbl_3_rodata_B64 && angDiff <= 0x400) {
            if (mode == 0) {
                return -1;
            }
            return a;
        }
        if (angDiff <= 0x200 && gap > lbl_3_rodata_B64 && distA < lbl_3_rodata_B70) {
            return a;
        }
    }
    dA = __abs(lbl_3_bss_16C - angA);
    dB = __abs(lbl_3_bss_16C - angB);
    if (dA > 0x800) {
        dA = 0x1000 - dA;
    }
    if (dB > 0x800) {
        dB = 0x1000 - dB;
    }
    if (__abs(dA - dB) <= 0x100) {
        return a;
    }
    if (dA > 0x400) {
        if (g_Ball.ballState == 0 && g_Ball.AtBat_ContactResult == 1 && b == 1) {
            if (dB <= 0x200) {
                return b;
            }
        } else if (dB <= 0x400) {
            return b;
        }
        if (mode == 0) {
            return -1;
        }
    }
    if (dB > 0x400) {
        if (g_Ball.ballState == 0 && g_Ball.AtBat_ContactResult == 1 && b == 1) {
            if (dA <= 0x200) {
                return a;
            }
        } else {
            return a;
        }
    }
    if (dA > dB) {
        return b;
    }
    return a;
}
#endif

// .text:0x00037114 size:0x2F8 mapped:0x806761A8
// NONMATCHING 98%: angA/fb share r29 in the original, ours uses r26 (one extra saved reg)
#if NONMATCHING
int fn_3_37114(int a, int b, int strict, f32 x, f32 z) {
    InMemFielderView* fa = &g_Fielders[a];
    InMemFielderView* fb = &g_Fielders[b];
    s32 cur = lbl_3_bss_16C;
    s16 angB;
    s16 angA;
    s16 da;
    s16 db;
    f32 dx;
    f32 dz;
    f32 d;
    if (cur < 0) {
        return -1;
    }
    dx = x - fa->x;
    dz = z - fa->z;
    /* distance computed but unused (the original keeps only the fcmpo) */
    d = dx * dx + dz * dz;
    SQRT_L(d);
    angA = fn_3_9FB8C(dx, dz);
    dx = x - fb->x;
    dz = z - fb->z;
    d = dx * dx + dz * dz;
    SQRT_L(d);
    angB = fn_3_9FB8C(dx, dz);
    if (strict != 0) {
        if (cur >= 0x580 && cur < 0xA80) {
            if (angA >= 0x580 && angA < 0xA80 && angB >= 0x580 && angB < 0xA80) {
                goto closer;
            }
            if (angA >= 0x580 && angA < 0xA80) {
                return a;
            }
            if (angB >= 0x580 && angB < 0xA80) {
                return b;
            }
        } else if (cur <= 0x280 && cur >= 0xD80) {
            if (!(angA >= 0x280 && angA < 0xD80) && !(angB >= 0x280 && angB < 0xD80)) {
                goto closer;
            }
            if (angA < 0x280 || angA >= 0xD80) {
                return a;
            }
            if (angB < 0x280 || angB >= 0xD80) {
                return b;
            }
        }
    } else if (cur >= 0x400 && cur < 0xC00) {
        if (!(angA >= 0x400 && angA < 0xC00 && angB >= 0x400 && angB < 0xC00)) {
            if (angA >= 0x400 && angA < 0xC00) {
                return a;
            }
            if (angB >= 0x400 && angB < 0xC00) {
                return b;
            }
        }
    } else if ((angA >= 0x400 && angA < 0xC00) || (angB >= 0x400 && angB < 0xC00)) {
        if (angA < 0x400 || angA >= 0xC00) {
            return a;
        }
        if (angB < 0x400 || angB >= 0xC00) {
            return b;
        }
    }
    if (strict != 0) {
        return -1;
    }
    da = fn_3_9FCF8(lbl_3_bss_16C, angA);
    db = fn_3_9FCF8(lbl_3_bss_16C, angB);
    if (__abs(da - db) > 0x100) {
        if (da > 0x400) {
            if (db > 0x400) {
                return -1;
            }
            return b;
        }
        if (db > 0x400) {
            if (da > 0x400) {
                return -1;
            }
            return a;
        }
    }
closer:
    if (angA < angB) {
        return a;
    }
    return b;
}
#endif

// .text:0x0003740C size:0x17C mapped:0x806764A0
void fn_3_3740C(void) {
    s16 ang;
    f32 mx = 0.0f;
    s32 best = 0x1000;
    s32 idx = -1;
    s32 i;
    if (g_Ball.ballState == 0 && g_FieldingLogic._0B0 <= 5) {
        for (i = 0; i < 6; i++) {
            f32 v = g_Fielders[i]._070;
            if (v > mx) {
                mx = v;
            }
        }
        if (5.0f + mx < g_Ball.ballDistanceFromHome) {
            ang = g_Ball.ballAngleFromHome;
            for (i = 6; i < 9; i++) {
                s32 d = __abs(ang - g_Fielders[i]._180);
                if (best > d) {
                    best = d;
                    idx = i;
                }
            }
            g_Ball.ballAngleFromHome = ang;
            if (i >= 0) {
                fn_3_38790(idx, 0);
            }
        }
    }
}

// .text:0x00037588 size:0x88 mapped:0x8067661C
void fn_3_37588(void) {
    if (g_Ball.ballVelocity > 0.17f) {
        fn_3_38790(fn_3_378B4(), 0);
        return;
    }
    if (g_Ball.AtBat_ContactResult == 0 && g_Ball.hitClassification1 != 0) {
        fn_3_37610(g_Ball.framesUntilBallHitsGround);
        return;
    }
    if (g_Ball.AtBat_ContactResult == 0) {
        fn_3_37610(30);
        return;
    }
    fn_3_37610(30);
}

// .text:0x00037610 size:0x2A4 mapped:0x806766A4
// 98%: prologue lis order (BFC load) and f/ao regs r6/r9 swapped in the idx>=0 block
void fn_3_37610(int a) {
    f32 t;
    f32 best = lbl_3_rodata_BFC;
    s32 idx = -1;
    s32 i;
    f32 dx;
    f32 dz;
    f32 d;
    f32 a2;
    f32 b2;
    for (i = 0; i < 9; i++) {
        InMemFielderView* f = &g_Fielders[i];
        t = f->_074;
        if (t < 5.0f && f->_20F == 0 && t < best && (f->_210 == 0 || !((0.05f * (f32)f->_1C0 + t) > best))) {
            best = t;
            idx = i;
        }
    }
    if (idx >= 0) {
        u8* base = (u8*)g_Fielders;
        int off = idx * 0x268; // sizeof(InMemFielderView)
        InMemFielderView* f = (InMemFielderView*)(base + off);
        if (!(f->_074 < lbl_3_rodata_B64)) {
            dx = g_Ball.physicsSubstruct.futureCoordsAndDist[a].pos.x - ((InMemFielderView*)(base + off))->pos.x;
            dz = g_Ball.physicsSubstruct.futureCoordsAndDist[a].pos.z - f->z;
            a2 = dx * dx;
            b2 = dz * dz;
            d = a2 + b2;
            SQRT_L(d);
            if (d > lbl_3_rodata_B64) {
                idx = -1;
            }
        }
    }
    if (idx >= 0 && idx != g_FieldingLogic._0B0 && g_FieldingLogic._0B0 >= 0) {
        InMemFielderView* g = &g_Fielders[g_FieldingLogic._0B0];
        if (g->_074 < lbl_3_rodata_BD8 && g->_20F == 0) {
            idx = -1;
        }
    }
    fn_3_38790(idx >= 0 ? idx : fn_3_361D8(g_Ball.physicsSubstruct.futureCoordsAndDist[a].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[a].pos.z), 0);
}

// .text:0x000378B4 size:0x74C mapped:0x80676948
#define FLD_ANG(n) (g_Fielders[(n)]._180)
#define FLD_RNG(n) (g_Fielders[(n)]._070)
// NONMATCHING 88%: original preloads r3=-1 and returns via bltlr/bgelr; ours materialises li r3,-1 per return; register numbering
#if NONMATCHING
s32 fn_3_378B4(void) {
    s16 cur = lbl_3_bss_170;
    s16 ang = g_Ball.ballAngleFromHome;
    s32 turn = 0x800;
    s32 mid;
    s32 w;
    if (cur >= 0 && (&lbl_3_bss_170)[3] >= 0) {
        turn = __abs(cur - (&lbl_3_bss_170)[3]);
        if (turn > 0x800) {
            turn = 0x1000 - turn;
        }
    }
    if (g_FieldingLogic._0B0 == 0) {
        if (ang >= FLD_ANG(0) - 0x40 && ang < FLD_ANG(0) + 0x40 &&
            g_Ball.ballDistanceFromHome - FLD_RNG(0) < lbl_3_rodata_B78) {
            return 0;
        }
        if (ang < FLD_ANG(0)) {
            if (cur >= 0xF00 || (cur >= 0 && cur < 0x300)) {
                return 0;
            }
            if (cur >= 0xB00 && cur < 0xF00 && g_Ball.ballDistanceFromHome - FLD_RNG(0) < lbl_3_rodata_B78) {
                return 0;
            }
        } else {
            if (cur >= 0x500 && cur < 0x900) {
                return 0;
            }
            if (cur >= 0x900 && cur < 0xD00 && g_Ball.ballDistanceFromHome - FLD_RNG(0) < lbl_3_rodata_B78) {
                return 0;
            }
        }
    }
    if (__abs(FLD_ANG(2) - FLD_ANG(3)) < 0x40 &&
        ((g_FieldingLogic._0B0 != 2 && g_FieldingLogic._0B0 != 3) || turn >= 0x400)) {
        mid = (FLD_ANG(2) + FLD_ANG(3)) / 2;
        if (ang >= mid - 0x100 && ang < mid + 0x100) {
            if (FLD_RNG(2) < FLD_RNG(3)) {
                if (FLD_RNG(2) > g_Ball.ballDistanceFromHome) {
                    return 2;
                }
                if (lbl_3_rodata_B78 + FLD_RNG(3) > g_Ball.ballDistanceFromHome) {
                    return 3;
                }
            } else {
                if (FLD_RNG(3) > g_Ball.ballDistanceFromHome) {
                    return 2;
                }
                if (lbl_3_rodata_B78 + FLD_RNG(2) > g_Ball.ballDistanceFromHome) {
                    return 3;
                }
            }
        }
    }
    if (__abs(FLD_ANG(4) - FLD_ANG(5)) < 0x40 &&
        ((g_FieldingLogic._0B0 != 4 && g_FieldingLogic._0B0 != 5) || turn >= 0x400)) {
        mid = (FLD_ANG(4) + FLD_ANG(5)) / 2;
        if (ang >= mid - 0x100 && ang < mid + 0x100) {
            if (FLD_RNG(4) <= FLD_RNG(5)) {
                if (FLD_RNG(4) > g_Ball.ballDistanceFromHome) {
                    return 4;
                }
                if (lbl_3_rodata_B78 + FLD_RNG(5) > g_Ball.ballDistanceFromHome) {
                    return 5;
                }
            } else {
                if (FLD_RNG(5) > g_Ball.ballDistanceFromHome) {
                    return 5;
                }
                if (lbl_3_rodata_B78 + FLD_RNG(4) > g_Ball.ballDistanceFromHome) {
                    return 4;
                }
            }
        }
    }
    if (ang < FLD_ANG(2) + 0x40) {
        if (g_FieldingLogic._0B0 != 3 || turn >= 0x400) {
            return 2;
        }
        return -1;
    }
    if (ang >= FLD_ANG(4) - 0x40 && ang < 0x800) {
        if (g_FieldingLogic._0B0 != 5 || turn >= 0x400) {
            return 4;
        }
        return -1;
    }
    w = 0;
    if (g_FieldingLogic._0B0 == 3) {
        w = 0x20;
    }
    if (ang >= FLD_ANG(3) - (w + 0x40) && ang < w + FLD_ANG(3) + 0x40) {
        if (g_FieldingLogic._0B0 == 2) {
            if (cur >= 0x500 && cur < 0x900) {
                return 2;
            }
            return 3;
        }
        if (g_FieldingLogic._0B0 == 5 && g_Fielders[3]._18C == 2 && turn < 0x400) {
            return -1;
        }
        if (g_FieldingLogic._0B0 == 5 && g_Fielders[3]._18C == 2 &&
            lbl_3_rodata_B64 + FLD_RNG(3) < g_Ball.ballDistanceFromHome) {
            return -1;
        }
        return 3;
    }
    w = 0;
    if (g_FieldingLogic._0B0 == 2) {
        w = 0x20;
    }
    if (ang >= FLD_ANG(5) - (w + 0x40) && ang < w + FLD_ANG(5) + 0x40) {
        if (g_FieldingLogic._0B0 == 4) {
            if ((cur >= 0 && cur < 0x300) || cur >= 0xF00) {
                return 4;
            }
            return 5;
        }
        if (g_FieldingLogic._0B0 == 3 && g_Fielders[5]._18C == 2 && turn < 0x400) {
            return -1;
        }
        if (g_FieldingLogic._0B0 == 3 && g_Fielders[5]._18C == 2 &&
            lbl_3_rodata_B64 + FLD_RNG(5) < g_Ball.ballDistanceFromHome) {
            return -1;
        }
        return 5;
    }
    if (ang >= FLD_ANG(2) && ang < FLD_ANG(3)) {
        if (cur >= 0x300 && cur < 0x700) {
            return 2;
        }
        if (cur >= 0x700 && cur < 0x900) {
            if (lbl_3_rodata_B64 + g_Fielders[2].z > g_Ball.AtBat_Contact_BallPos.z) {
                return 2;
            }
            return -1;
        }
        if (cur >= 0xD00 || (cur >= 0 && cur < 0x300)) {
            return 3;
        }
        return -1;
    }
    if (ang >= FLD_ANG(5) && ang < FLD_ANG(4)) {
        if (cur >= 0x100 && cur < 0x500) {
            return 4;
        }
        if (cur >= 0xF00 || (cur >= 0 && cur < 0x100)) {
            if (lbl_3_rodata_B64 + g_Fielders[4].z > g_Ball.AtBat_Contact_BallPos.z) {
                return 4;
            }
            return -1;
        }
        if (cur >= 0x500 && cur < 0xB00) {
            return 5;
        }
        return -1;
    }
    if (ang >= FLD_ANG(3) && ang < FLD_ANG(5)) {
        if (g_Ball.ballDistanceFromHome < lbl_3_rodata_B64 + FLD_RNG(0)) {
            if (ang < FLD_ANG(0)) {
                if (cur > 0xD00 || (cur >= 0 && cur < 0x100)) {
                    return 0;
                }
            } else if (cur >= 0x700 && cur < 0xB00) {
                return 0;
            }
        }
        if (cur >= 0x500 && cur < 0xB00) {
            return 3;
        }
        if (cur > 0xD00 || (cur >= 0 && cur < 0x300)) {
            return 5;
        }
        return -1;
    }
    return -1;
}
#endif
#undef FLD_ANG
#undef FLD_RNG

// .text:0x00038000 size:0x234 mapped:0x80677094
void fn_3_38000(void) {
    f32 t;
    f32 mx;
    s16 ang = g_Ball.ballAngleFromHome;
    f32 slack = lbl_3_rodata_B64;
    s32 k = 30;
    s32 mode = 0;
    s32 res;
    if (ang >= 0x800) {
        res = 1;
    } else {
        if (ang < 0x300 && (ang < g_Fielders[2]._180 || fn_3_9FCF8(ang, g_Fielders[3]._180) >= 0x100)) {
            mode = 8;
            mx = g_Fielders[2]._070;
        } else if (ang > 0x500 && (ang >= g_Fielders[4]._180 || fn_3_9FCF8(ang, g_Fielders[5]._180) >= 0x100)) {
            mode = 6;
            mx = g_Fielders[4]._070;
        } else if (ang < g_Fielders[3]._180) {
            f32 a = g_Fielders[3]._070;
            f32 b = g_Fielders[2]._070;
            mx = a >= b ? a : b;
        } else if (ang >= g_Fielders[5]._180) {
            f32 a = g_Fielders[5]._070;
            f32 b = g_Fielders[4]._070;
            mx = a >= b ? a : b;
        } else {
            f32 a = g_Fielders[3]._070;
            f32 b = g_Fielders[5]._070;
            mx = a >= b ? a : b;
        }
        if (g_Ball.ballVelocity > lbl_3_rodata_BB8) {
            t = g_Ball.ballVelocity - lbl_3_rodata_BB8;
            slack = slack - lbl_3_rodata_BA0 * t;
            k = (s32)(lbl_3_rodata_BDC * t) + 30;
        }
        if (mx + slack > g_Ball.ballDistanceFromHome) {
            res = fn_3_378B4();
        } else {
            res = fn_3_361D8(g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.z);
            if (mode == 8 && res == 3) {
                res = 8;
            }
            if (mode == 6 && res == 5) {
                res = 6;
            }
        }
    }
    fn_3_38790(res, 0);
}

// .text:0x00038234 size:0xD0 mapped:0x806772C8
void fn_3_38234(void) {
    InMemBallType* b = &g_Ball;
    if (b->hitClassification2 <= 4 || b->hitClassification2 == 7) {
        fn_3_38000();
        return;
    }
    if (b->maxYOfHit > lbl_3_rodata_BE4) {
        fn_3_38304();
        return;
    }
    if (b->maxYOfHit < lbl_3_rodata_B8C) {
        fn_3_38000();
        return;
    }
    if (b->someYCoord > lbl_3_rodata_B64) {
        fn_3_38304();
        return;
    }
    if (b->ballDistanceFromHome < lbl_3_rodata_C00) {
        if (lbl_3_bss_170 >= 0x900 && lbl_3_bss_170 < 0xF00) {
            fn_3_38304();
            return;
        }
        fn_3_38000();
        return;
    }
    fn_3_38304();
}

// .text:0x00038304 size:0x48C mapped:0x80677398
// NONMATCHING 92%: fielder 0x80 reads via lfsx in the original; empty-then branch shape; f-reg numbering
#if NONMATCHING
void fn_3_38304(void) {
    s32 r;
    s32 deep;
    if (g_FieldingLogic._0B0 >= 0 &&
        g_Fielders[g_FieldingLogic._0B0]._080 < lbl_3_rodata_B64) {
        return;
    }
    deep = 0;
    if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > lbl_3_rodata_BB0) {
        if (g_FieldingLogic._0B0 >= 6) {
            deep = 1;
        } else {
            f32 reach = g_Ball.ballDistanceFromHome - lbl_3_rodata_B64;
            if (reach > g_Fielders[2]._070 && reach > g_Fielders[3]._070 &&
                reach > g_Fielders[4]._070 && reach > g_Fielders[5]._070) {
                deep = 1;
            }
        }
    }
    if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > lbl_3_rodata_C04 || deep != 0) {
        s32 other;
        if (g_Fielders[6]._080 < g_Fielders[8]._080) {
            if (g_Fielders[6]._080 < g_Fielders[7]._080) {
                r = 6;
                other = 7;
            } else {
                r = 7;
                other = 6;
            }
        } else if (g_Fielders[8]._080 < g_Fielders[7]._080) {
            r = 8;
            other = 7;
        } else {
            r = 7;
            other = 8;
        }
        if (!(lbl_3_rodata_B9C + g_Fielders[r]._080 < g_Fielders[other]._080)) {
            r = fn_3_36678(r, other, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z, 0);
        }
    } else {
        s32 i0 = -1;
        s32 i1 = -1;
        s32 i2 = -1;
        f32 d0 = lbl_3_rodata_BA4;
        f32 d1 = d0;
        f32 d2 = d0;
        InMemFielderView* f = g_Fielders;
        s32 i;
        for (i = 0; i < 9; i++, f++) {
            f32 d = f->_080;
            if (d0 > d) {
                d2 = d1;
                i2 = i1;
                d1 = d0;
                i1 = i0;
                d0 = d;
                i0 = i;
            } else if (d1 > d) {
                d2 = d1;
                i2 = i1;
                d1 = d;
                i1 = i;
            } else if (d2 > d) {
                d2 = d;
                i2 = i;
            }
        }
        if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > lbl_3_rodata_BD0) {
            if (d0 <= lbl_3_rodata_BD8 && i0 == g_FieldingLogic._0B0) {
                r = i0;
            } else if (d1 - d0 > lbl_3_rodata_B9C) {
                r = i0;
            } else if (d2 - d1 > lbl_3_rodata_B9C) {
                r = fn_3_36678(i0, i1, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z, 0);
            } else {
                r = Pick3Inline(i0, i1, i2, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
            }
        } else {
            r = Pick3Inline(i0, i1, i2, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
        }
    }
    fn_3_38790(r, 0);
}
#endif


// .text:0x00038790 size:0x580 mapped:0x80677824
// NONMATCHING 98%: register allocation throughout; bss_170==0 early return emitted as beqlr; one mulli placement
#if NONMATCHING
void fn_3_38790(s32 a, s32 b) {
    s32 prev = g_FieldingLogic._0B0;
    InMemFielderView* f = &g_Fielders[a];
    s16 k;
    if (a < 0) {
        return;
    }
    if (a == prev) {
        return;
    }
    if (g_Ball.ballState == 0 && g_Ball.ballAngleFromHome >= 0x3D8 && g_Ball.ballAngleFromHome < 0x428) {
        if (prev == 3 && a == 5 && f->_18C == 2 && f->distToFielder[3] < lbl_3_rodata_BD8) {
            return;
        }
        if (prev == 5 && a == 3 && f->_18C == 2 && f->distToFielder[5] < lbl_3_rodata_BD8) {
            return;
        }
    }
    if (g_Ball.ballState == 0 && g_Ball.hitClassification2 <= 6 && a == 1) {
        if (lbl_3_bss_170 >= 0x800) {
            return;
        }
        if (lbl_3_bss_170 == 0) {
            return;
        }
    }
    g_FieldingLogic._0B0 = a;
    if (b == 0) {
        SetFielderAct((s16)a, 0xF);
    } else {
        SetFielderAct((s16)a, 0x15);
    }
    k = f->_18C;
    if (k >= 0 && k <= 5) {
        if (k >= 0 && k <= 3) {
            if ((&g_FieldingLogic._0D0[0])[k] == a) {
                (&g_FieldingLogic._0D0[0])[k] = -1;
                g_FieldingLogic._101[k] = 0;
            }
            f->_18C = -1;
            f->_1D7 = 0;
            if (f->_1D3 == 1) {
                SetFielderActP(f, a, 12);
            }
        } else if (k == 5) {
            f->_18C = -1;
            f->_1D7 = 0;
            g_FieldingLogic._0D8 = -1;
            g_FieldingLogic.playerAtMoundCutoffLocation = 0;
            if (f->_1D3 == 14) {
                SetFielderActP(f, a, 12);
            }
        }
    }
    if (g_FieldingLogic._0B0 == g_FieldingLogic._0BE) {
        g_FieldingLogic._0BE = -1;
    }
    if (prev >= 0) {
        if (prev >= 6) {
            SetFielderAct(prev, 0x10);
        } else if (g_Ball.ballState == 0) {
            InMemFielderView* p = &g_Fielders[prev];
            if (p->_070 > lbl_3_rodata_B78 + f->_070) {
                SetFielderAct(prev, 0x10);
            } else if (p->_18C == 6) {
                SetFielderAct(prev, 0xB);
            } else {
                SetFielderAct(prev, 0xC);
                g_Fielders[prev]._1D5 = 4;
            }
        } else {
            SetFielderAct(prev, 0xC);
            g_Fielders[prev]._1D5 = 4;
        }
    }
    if (g_Ball.framesSinceHit < 0x1E) {
        g_FieldingLogic._0DA = 0x14;
    } else {
        g_FieldingLogic._0DA = 0x2D;
    }
}
#endif

// .text:0x00038D10 size:0x2E8 mapped:0x80677DA4
// NONMATCHING 99%: FieldingLogic+0xB0 reg r4/r5 swapped; SetFielderAct state/table regs (see docs/patterns/unsolved.md)
#if NONMATCHING
void fn_3_38D10(void) {
    int r;
    int i;
    f32 lim;
    f32 x;
    f32 z;
    if (g_Ball.AtBat_ContactResult == 0 &&
        (g_FieldingLogic._0B0 == 3 || g_FieldingLogic._0B0 == 5)) {
        InMemFielderView* f = &g_Fielders[g_FieldingLogic._0B0];
        if (f->_080 < f->reach[0]) {
            r = g_FieldingLogic._0B0;
            goto chosen;
        }
    }
    if ((g_Fielders[3]._1DB == 0 || g_Fielders[5]._1DB == 0) && g_Ball.AtBat_ContactResult == 0) {
        x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
        z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
    } else {
        lim = lbl_3_rodata_B80 * (g_Fielders[3]._070 + g_Fielders[5]._070);
        for (i = 1; i < 120; i += 3) {
            if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].dist > lim) {
                break;
            }
        }
        x = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x;
        z = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z;
    }
    r = fn_3_37114(3, 5, 1, x, z);
    if (r < 0) {
        if (g_Ball.ballZoneAwayFromHome >= 2 && lbl_3_bss_16C > 0xA00 && lbl_3_bss_16C < 0xE00) {
            g_FieldingLogic._13A = 0;
        }
    } else {
    chosen:
        if (r == 3) {
            fn_3_38790(3, 1);
            SetFielderAct(5, 12);
        } else {
            fn_3_38790(5, 1);
            SetFielderAct(3, 12);
        }
        g_FieldingLogic._13A = 0;
    }
}
#endif

// .text:0x00038FF8 size:0x3B8 mapped:0x8067808C
// NONMATCHING 97%: goto-target layout leaves the original's dead b instructions out; one mulli scheduled early
#if NONMATCHING
void fn_3_38FF8(void) {
    InMemFielderView* f = &g_Fielders[g_FieldingLogic._0B0];
    f32 lim = f->_070;
    s32 i;
    s32 r;
    for (i = 1; i < 60; i += 3) {
        if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].dist > lim) {
            break;
        }
    }
    if (g_FieldingLogic._0B0 != 1) {
        if (i <= 1) {
            goto keep_second;
        }
        if (f->_07C < lbl_3_rodata_C08) {
            if (lbl_3_bss_16C >= 0 &&
                fn_3_9FCF8(lbl_3_bss_16C, fn_3_9FB8C(g_Ball.AtBat_Contact_BallPos.x - f->x, g_Ball.AtBat_Contact_BallPos.z - f->z)) < 0x100) {
                goto keep_first;
            }
            if (g_FieldingLogic._0B0 >= 2 && g_FieldingLogic._0B0 <= 5 &&
                (g_Ball.hitClassification2 == 2 || g_Ball.hitClassification2 == 3)) {
                goto keep_first;
            }
        }
    }
    if (g_Fielders[g_FieldingLogic._0B0]._1DB == 0 ||
        g_Fielders[g_FieldingLogic._0B2]._1DB == 0) {
        r = fn_3_36678(g_FieldingLogic._0B0, g_FieldingLogic._0B2, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                       g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z, 3);
    } else {
        r = fn_3_36678(g_FieldingLogic._0B0, g_FieldingLogic._0B2, g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x,
                       g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z, 3);
    }
    if (r >= 0) {
        if (r == g_FieldingLogic._0B2) {
            goto keep_second;
        }
        if (r == g_FieldingLogic._0B0) {
            goto keep_first;
        }
    }
    if (g_Ball.framesSinceHit > 0x5A) {
        if (g_Ball.framesSinceBallHitGroundOrWasCaught >= 0 ||
            (&g_Fielders[0]._080)[g_FieldingLogic._0B0 * 0x9A] <=
                (&g_Fielders[0]._080)[g_FieldingLogic._0B2 * 0x9A]) {
        keep_first:
            g_FieldingLogic._139 = 0;
            if (g_FieldingLogic._0B0 == 0) {
                return;
            }
        } else {
        keep_second:
            if (g_FieldingLogic._13A != 0 &&
                (g_FieldingLogic._0B2 == 3 || g_FieldingLogic._0B2 == 5)) {
                fn_3_38D10();
                if (g_FieldingLogic._13A != 0) {
                    if (!(g_Ball.ballDistanceFromHome - lbl_3_rodata_B78 >
                          g_Fielders[g_FieldingLogic._0B0]._070)) {
                        return;
                    }
                    fn_3_38790(g_FieldingLogic._0B2, 1);
                }
            } else {
                fn_3_38790(g_FieldingLogic._0B2, 1);
            }
        }
        g_FieldingLogic._139 = 0;
        g_FieldingLogic._0B2 = g_FieldingLogic._0B4;
        g_FieldingLogic._0B4 = -1;
    }
}
#endif

// .text:0x000393B0 size:0x4A8 mapped:0x80678444
// NONMATCHING 95%: the original places the B2==r tail block at the function end; one mulli scheduled differently
#if NONMATCHING
void fn_3_393B0(void) {
    InMemFielderView* base = g_Fielders;
    InMemFielderView* f = &base[g_FieldingLogic._0B0];
    s32 i;
    s32 r;
    if (g_Ball.framesSinceHit < 0x3C) {
        if (g_FieldingLogic._0B0 == 3) {
            for (i = 2; i < 30; i += 2) {
                if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].dist > base[2]._070) {
                    break;
                }
            }
            if (i < 30 && g_Ball.ballAngleFromHome > base[2]._180 &&
                g_Ball.ballAngleFromHome < f->_180 &&
                base[2]._070 > lbl_3_rodata_B60 + g_Ball.ballDistanceFromHome) {
                if (fn_3_36678(2, 3, g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z, 0) == 2) {
                    fn_3_38790(2, 0);
                    return;
                }
            }
        } else if (g_FieldingLogic._0B0 == 5) {
            for (i = 2; i < 30; i += 2) {
                if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].dist > base[4]._070) {
                    break;
                }
            }
            if (i < 30 && g_Ball.ballAngleFromHome < base[4]._180 &&
                g_Ball.ballAngleFromHome > f->_180 &&
                base[4]._070 > lbl_3_rodata_B60 + g_Ball.ballDistanceFromHome) {
                if (fn_3_36678(4, 5, g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z, 0) == 4) {
                    fn_3_38790(4, 0);
                    return;
                }
            }
        }
    }
    if (g_FieldingLogic._0B2 >= 0) {
        if (g_FieldingLogic._0B0 <= 5 && g_FieldingLogic._0B2 >= 6) {
            f32 px;
            f32 pz;
            r = -1;
            px = g_Ball.physicsSubstruct.futureCoordsAndDist[0x1e].pos.x;
            pz = g_Ball.physicsSubstruct.futureCoordsAndDist[0x1e].pos.z;
            if (g_Ball.ballVelocity < lbl_3_rodata_BBC || g_Ball.ballState == 3) {
                if (g_Ball.ballVelocity < lbl_3_rodata_B24 && g_Ball.ballState == 0 && g_Ball.ballZoneAwayFromHome <= 1 &&
                    f->_070 > g_Ball.ballDistanceFromHome && f->_07C < lbl_3_rodata_B64) {
                    SetFielderAct(g_FieldingLogic._0B2, 12);
                    g_FieldingLogic._0B2 = -1;
                }
                r = fn_3_36678(g_FieldingLogic._0B0, g_FieldingLogic._0B2,
                               px, pz, 0);
            } else if (lbl_3_rodata_B78 + f->_070 < g_Ball.ballDistanceFromHome) {
                r = fn_3_36678(g_FieldingLogic._0B0, g_FieldingLogic._0B2,
                               px, pz, 0);
            }
            if (g_FieldingLogic._0B2 != r) {
                return;
            }
            fn_3_38790(g_FieldingLogic._0B2, 1);
            g_FieldingLogic._0B2 = -1;
        }
    } else if ((g_Ball.AtBat_ContactResult == 1 || g_Ball.AtBat_ContactResult == -1 || g_Ball.ballState == 3) &&
               g_Ball.ballVelocity < lbl_3_rodata_B74 &&
               g_Fielders[g_FieldingLogic._0B0]._074 > lbl_3_rodata_BD8) {
        fn_3_37610(0x1E);
    }
}
#endif

// .text:0x00039858 size:0x56C mapped:0x806788EC
// NONMATCHING 94%: early-return/goto block layout (the original moves the 38790 tail to the end); bss_170 read via addi+lha
#if NONMATCHING
void fn_3_39858(void) {
    s32 r = g_FieldingLogic._0B0;
    InMemFielderView* f = &g_Fielders[r];
    s16 cur;
    s32 k;
    f32 t;
    if (g_FieldingLogic._0B2 < 0) {
        if (g_FieldingLogic._139 == 0 && g_FieldingLogic._0DA == 0) {
            fn_3_38304();
        }
        return;
    }
    if (r <= 5 && g_FieldingLogic._0B2 >= 6) {
        if (g_Ball.hitClassification1 == 2 || g_Ball.hitClassification1 == 5) {
            if (g_FieldingLogic._0B2 !=
                fn_3_36678(r, g_FieldingLogic._0B2, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z, 0)) {
                return;
            }
        } else if (!(lbl_3_rodata_B78 + f->_070 < g_Ball.ballDistanceFromHome)) {
            return;
        }
        fn_3_38790(g_FieldingLogic._0B2, 1);
        g_FieldingLogic._0B2 = -1;
        return;
    }
    if (g_FieldingLogic._139 == 0) {
        return;
    }
    if (g_Ball.framesSinceHit < lbl_3_data_484C[3]) {
        return;
    }
    cur = lbl_3_bss_170;
    if (cur < 0 || !(g_FieldingLogic.padButtons[0] & 0x200)) {
        if (g_Ball.ballDistanceFromHome < (f32)lbl_3_data_484C[5]) {
            return;
        }
        t = g_Ball.physicsSubstruct.hitLandingSpotDistFromHome - (f32)lbl_3_data_484C[7];
        if (t > (f32)lbl_3_data_484C[6]) {
            t = (f32)lbl_3_data_484C[6];
        }
        if (g_Ball.ballDistanceFromHome < t) {
            return;
        }
    }
    if (!((&g_Fielders[0]._080)[r * 0x9A] < lbl_3_data_4848)) {
        if ((&g_Fielders[0]._080)[g_FieldingLogic._0B2 * 0x9A] < lbl_3_data_4848) {
            r = g_FieldingLogic._0B2;
        } else {
            if (g_Ball.framesSinceHit < lbl_3_data_484C[4]) {
                if (cur <= 0) {
                    return;
                }
                for (k = 1; k < lbl_3_data_484C[8]; k++) {
                    if ((&lbl_3_bss_170)[k] <= 0 || fn_3_9FCF8(cur, (&lbl_3_bss_170)[k]) > 0x200) {
                        break;
                    }
                }
                if (k < lbl_3_data_484C[8]) {
                    return;
                }
            }
            r = fn_3_37114(g_FieldingLogic._0B0, g_FieldingLogic._0B2, 0,
                           lbl_3_rodata_B80 * ((&g_Fielders[0]._014)[g_FieldingLogic._0B0 * 0x9A] +
                                               (&g_Fielders[0]._014)[g_FieldingLogic._0B2 * 0x9A]),
                           lbl_3_rodata_B80 * ((&g_Fielders[0]._01C)[g_FieldingLogic._0B0 * 0x9A] +
                                               (&g_Fielders[0]._01C)[g_FieldingLogic._0B2 * 0x9A]));
        }
    }
    if (r < 0) {
        return;
    }
    if (r == g_FieldingLogic._0B2) {
        if (g_FieldingLogic._0BC < 0) {
            SetFielderActTag(g_FieldingLogic._0B0, 0x18);
        } else {
            SetFielderAct(g_FieldingLogic._0B0, 0xC);
        }
        SetFielderAct(g_FieldingLogic._0B2, 0x15);
        g_FieldingLogic._0B0 = g_FieldingLogic._0B2;
    } else {
        if (g_FieldingLogic._0BC < 0) {
            SetFielderActTag(g_FieldingLogic._0B2, 0x18);
        } else {
            SetFielderAct(g_FieldingLogic._0B2, 0xC);
        }
        SetFielderAct(g_FieldingLogic._0B0, 0x15);
    }
    g_FieldingLogic._0B2 = -1;
    g_FieldingLogic._139 = 0;
}
#endif

// .text:0x00039DC4 size:0xEC mapped:0x80678E58
void fn_3_39DC4(void) {
    int i;
    InMemFielderView* f;
    for (i = 0; i < 9; i++) {
        g_FieldingLogic._0F8[i] = 0;
        f = &g_Fielders[i];
        if (i != -1) {
            f->_1D3 = 0;
            if (lbl_3_data_3C40[0].anim >= 0) {
                g_FieldingLogic._0F8[i] = lbl_3_data_3C40[0].anim;
            }
            f->_1D5 = 0;
            f->_1D6 = 0;
            f->_1A4 = 0;
            f->_1AC = 0;
            f->_1FF = 0;
        }
        f->_020 = 10000.0f;
        f->_024 = 0.0f;
    }
    g_FieldingLogic._0B0 = -1;
    g_FieldingLogic._0B2 = -1;
    g_FieldingLogic._0B4 = -1;
    g_FieldingLogic._0BE = -1;
    g_FieldingLogic._139 = 0;
    g_FieldingLogic._0D0[0] = -1;
    g_FieldingLogic._101[0] = 0;
    g_FieldingLogic._0D0[1] = -1;
    g_FieldingLogic._101[1] = 0;
    g_FieldingLogic._0D0[2] = -1;
    g_FieldingLogic._101[2] = 0;
    g_FieldingLogic._0D0[3] = -1;
    g_FieldingLogic._101[3] = 0;
    fn_3_37610(0x78);
}

// .text:0x00039EB0 size:0x34C mapped:0x80678F44
// NONMATCHING 86%: early returns vs the original's nested condition chain; fielder reset loop strength-reduced differently
#if NONMATCHING
void fn_3_39EB0(void) {
    s32 ready = 1;
    u8 st;
    s16 phase;
    s16 cur;
    s32 reset;
    s32 i;
    InMemFielderView* f;
    if (g_d_GameSettings.GameModeSelected == 2 && g_GameLogic.secondaryGameMode == 0xC) {
        return;
    }
    if (g_Ball.deadBallReason != 0) {
        return;
    }
    st = g_Ball.ballState;
    if (st == 1) {
        return;
    }
    phase = g_Ball.AtBat_ContactResult;
    if (phase == 0 && g_Ball.maxYOfHit > lbl_3_rodata_BE4) {
        if (g_Ball.framesSinceHit < lbl_3_data_49DC[0x29]) {
            return;
        }
    } else if (g_Ball.framesSinceHit < lbl_3_data_49DC[0x2A]) {
        return;
    }
    if (st == 2 && g_Ball.framesUntilThrowReachesDest > 0 && g_Ball.fielderBeingThrownTo >= 0) {
        if (g_Ball.framesSinceThrowStarted == 2 && g_FieldingLogic._0C4 != 6) {
            fn_3_35E1C();
        }
        return;
    }
    if ((g_FieldingLogic._0DA = g_FieldingLogic._0DA - 1) > 0) {
        ready = 0;
    } else {
        g_FieldingLogic._0DA = 0;
    }
    if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] == 0 && (g_FieldingLogic.padButtons[0] & 0x40)) {
        return;
    }
    cur = g_FieldingLogic._0B0;
    if (cur >= 0 && g_Fielders[cur]._205 != 0) {
        return;
    }
    if (ready == 0 || g_FieldingLogic._137 != 0 || g_Ball.catchAnimationTotalFrames != 0) {
        return;
    }
    reset = 0;
    if (cur < 0 && st == 3) {
        reset = 1;
    }
    if (g_FieldingLogic._13B != 0 || reset != 0) {
        f = g_Fielders;
        for (i = 0; i < 9; i++, f++) {
            g_FieldingLogic._0F8[i] = 0;
            SetFielderAct2(i, lbl_3_data_3C40[0].anim, 0);
            f->_020 = lbl_3_rodata_C0C;
            f->_024 = lbl_3_rodata_B20;
        }
        g_FieldingLogic._0B0 = -1;
        g_FieldingLogic._0B2 = -1;
        g_FieldingLogic._0B4 = -1;
        g_FieldingLogic._0BE = -1;
        g_FieldingLogic._139 = 0;
        g_FieldingLogic._0D0[0] = -1;
        g_FieldingLogic._101[0] = 0;
        g_FieldingLogic._0D0[1] = -1;
        g_FieldingLogic._101[1] = 0;
        g_FieldingLogic._0D0[2] = -1;
        g_FieldingLogic._101[2] = 0;
        g_FieldingLogic._0D0[3] = -1;
        g_FieldingLogic._101[3] = 0;
        fn_3_37610(0x78);
        if (g_FieldingLogic._0B0 >= 0) {
            g_FieldingLogic._13B = 0;
        }
    } else if (g_FieldingLogic._0B4 >= 0) {
        fn_3_38FF8();
    } else if (g_FieldingLogic._13A != 0 && (cur == 3 || cur == 5)) {
        fn_3_38D10();
    } else if (phase == 0) {
        fn_3_39858();
    } else {
        fn_3_393B0();
    }
}
#endif

// .text:0x0003A1FC size:0x38 mapped:0x80679290
void fn_3_3A1FC(int i) {
    InMemFielderView* f = &g_Fielders[i];
    if (f->_1B6 != 0) {
        f->_050 = f->_054;
    } else {
        f->_050 = lbl_3_rodata_B20;
    }
}

// .text:0x0003A234 size:0x350 mapped:0x806792C8
// NONMATCHING 98%: extsh on the radToShortAngle results; 0x2C50 slot pointer reached via lwzu in the original
#if NONMATCHING
void fn_3_3A234(int i) {
    InMemFielderView* f = &g_Fielders[i];
    s32 who = i;
    f32 cap = f->maxVelocity;
    s16 rel;
    s32 n;
    s32 k;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (i == 0) {
            who = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        } else {
            who = g_Minigame.minigameControlStruct[0].fieldOrder[i - 2];
        }
    }
    if (f->_1A0 == 0) {
        s16 a = radToShortAngle(f->_064);
        rel = fn_3_9FE6C_normalizeAngle(a - radToShortAngle(f->_048));
        if (rel < 0x200) {
            f->_1F3 = 0;
        } else if (rel < 0x600) {
            f->_1F3 = 3;
        } else if (rel < 0xA00) {
            f->_1F3 = 1;
        } else if (rel < 0xE00) {
            f->_1F3 = 2;
        } else {
            f->_1F3 = 0;
        }
        if (f->_1E3 != 1) {
            if (f->_1F3 == 1) {
                f->_1F3 = 5;
            } else {
                f->_1F3 = 4;
            }
        }
    }
    if (f->_1F3 == 4 || f->_1F3 == 5) {
        f->_050 = lbl_3_rodata_B80 * f->velocityPerWeight + f->_050;
    } else {
        f->_050 = f->_050 + f->velocityPerWeight;
    }
    n = f->_217;
    for (k = 0; k < n; k++) {
        cap *= lbl_3_data_46F4;
    }
    if (f->_050 > cap) {
        f->_050 = cap;
    }
    if (g_FieldingLogic.curBoost->fielder == i) {
        f->_050 = g_FieldingLogic.curBoost->scale * cap;
    }
    if (g_Ball.fielderWBallIndex == i && checkFieldingStat(g_GameLogic.teamFielding, f->rosterID, 0xB) != 0) {
        CharActor** slot = lbl_8036E548.active + who;
        f->_050 = f->_050 * lbl_3_data_46F0;
        (*slot)->_279[1] = 1;
        if (f->_1A0 == 1) {
            fn_3_1682AC(lbl_8036E548.active[who], 0xB);
        }
    }
    if (g_Minigame.GameMode_MiniGame == 6) {
        if (g_Minigame._1D6D == f->_20D) {
            f->_050 = f->_050 * lbl_3_data_21A14[6];
        }
        if (((s8)g_Minigame.playerIDWithPowerup[0]) == f->_20D) {
#ifdef TARGET_PC
            f->_050 = f->_050 * *PTR32_GET(f32, g_Minigame.starDashRelated_0_5Or1_5);
#else
            f->_050 = f->_050 * *((f32*)g_Minigame.starDashRelated_0_5Or1_5);
#endif
        }
    }
}
#endif

// .text:0x0003A584 size:0x574 mapped:0x80679618
// NONMATCHING 95%: inlined fn_3_258D8 body schedules its table reads differently (lfsx); 0x2C50 slot via lwzu; calls fn_3_261E8 through a cast until its prototype gains the index arg
#if NONMATCHING
void fn_3_3A584(int i) {
    InMemFielderView* f = &g_Fielders[i];
    s32 who = i;
    s32 stop = 0;
    s16 ang;
    FieldingBoost* t;
    f32 spd;
    f32 pos[3];
    s32 r;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (i == 0) {
            who = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        } else {
            who = g_Minigame.minigameControlStruct[0].fieldOrder[i - 2];
        }
    }
    if (f->_252 != 0) {
        fn_3_261E8(i);
        f->_1A2 = 0;
        goto done;
    }
    ang = f->_19E;
    if (StartJumpInline(i) != 0) {
        goto done;
    }
    t = g_FieldingLogic.curBoost;
    if (t->state == 4 && t->fielder == i) {
        f->_050 = t->scale * f->maxVelocity;
        f->_030 = t->dirX * f->_050;
        f->_034 = t->dirZ * f->_050;
        goto move;
    }
    if (ang < 0) {
        if (t->fielder == i) {
            f->_050 = t->scale * f->maxVelocity;
            if (f->_1A2 < 0x7FFE) {
                f->_1A2 = f->_1A2 + 1;
            } else {
                f->_1A2 = 0x7FFF;
            }
            goto run;
        }
        if (f->_1B6 != 0) {
            f->_050 = f->_054;
        } else {
            f->_050 = lbl_3_rodata_B20;
        }
        if (f->_050 > lbl_3_rodata_B20) {
            goto run;
        }
        f->_1E3 = 1;
        goto done;
    }
    if (f->_1A2 < 0x7FFE) {
        f->_1A2 = f->_1A2 + 1;
    } else {
        f->_1A2 = 0x7FFF;
    }
    if (g_Ball.fielderWBallIndex == i && f->_1A2 <= lbl_3_data_49DC[0]) {
        f->_050 = lbl_3_rodata_B20;
        f->_1E3 = 1;
    } else {
        f->_064 = shortAngleToRad_Capped(ang);
        if (f->_1E3 == 4 || f->_1E3 == 1) {
            f->_0BC = f->_064;
            f->_0C0 = f->_064;
            f->_0C4 = f->_064;
            f->_0C8 = f->_064;
            f->_0CC = f->_064;
        }
        fn_3_3A234(i);
        f->_1E3 = 0;
        f->_1E4 = 0;
    }
    if (!(f->_050 > lbl_3_rodata_B20)) {
        goto done;
    }
run:
    spd = f->_050;
    if (g_Ball.fielderWBallIndex == i && checkFieldingStat(g_GameLogic.teamFielding, f->rosterID, 0xB) != 0) {
        CharActor** slot = lbl_8036E548.active + who;
        spd *= lbl_3_data_46F0;
        (*slot)->_279[1] = 1;
        if (f->_1A0 == 1) {
            fn_3_1682AC(lbl_8036E548.active[who], 0xB);
        }
    }
    f->_030 = spd * (f32)cos(f->_064);
    f->_034 = spd * (f32)sin(f->_064);
move:
    r = fn_3_51798(i, pos);
    if (r == 1) {
        stop = 1;
        f->_050 = lbl_3_rodata_B20;
        f->_030 = lbl_3_rodata_B20;
        f->_034 = lbl_3_rodata_B20;
    } else if (r == 2) {
        if (pos[0] > lbl_3_rodata_B18 || pos[0] < lbl_3_rodata_B1C) {
            f->_050 = lbl_3_rodata_B20;
        } else {
            f->_030 = lbl_3_rodata_B20;
            f->_034 = lbl_3_rodata_B20;
            f->x = pos[0];
            f->z = pos[2];
        }
        stop = 1;
    } else {
        f->x = f->x + f->_030;
        f->z = f->z + f->_034;
    }
    if (stop != 0) {
        g_FieldingLogic.curBoost->timer2 = 0;
        g_FieldingLogic.curBoost->power = 0;
        g_FieldingLogic.curBoost->fielder = -1;
        g_FieldingLogic.curBoost->taps = 0;
    }
done:
    f->_014 = f->x;
    f->_01C = f->z;
    f->_1F0 = 1;
}
#endif

// .text:0x0003AAF8 size:0xF8 mapped:0x80679B8C
void fn_3_3AAF8(int i) {
    InMemFielderView* f;
    int v;
    g_FieldingLogic_s* l;
    f = &g_Fielders[i];
    v = lbl_3_bss_170;
    l = &g_FieldingLogic;
    if (l->_10E != 0) {
        v = -1;
    }
    f->_19E = v;
    if (g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] == 0 && v >= 0 && f->_1A0 > 0xA) {
        g_FieldingLogic._0CC = -1;
    }
    if (v >= 0) {
        FieldingBoost* t = g_FieldingLogic.curBoost;
        u8 k = t->state;
        if (k != 3 && k != 4) {
            if (g_FieldingLogic.padButtons[1] & 0x200) {
                g_FieldingLogic.curBoost->timer = 0;
            }
            if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0 && g_Practice.practice_fielding_enableSprinting != 0) {
                g_FieldingLogic.curBoost->timer = 0;
            }
        }
    }
}

// .text:0x0003ABF0 size:0xD0 mapped:0x80679C84
void fn_3_3ABF0(int i) {
    InMemFielderView* f = &g_Fielders[i];
    s16 c = g_FieldingLogic._0B0;
    InMemFielderView* cf = FIELDERS + (int)c;
    InMemFielderView* g;
    if (g_Ball.framesSinceHit < lbl_3_data_484C[0]) {
        return;
    }
    if (g_FieldingLogic._139 != 0) {
        return;
    }
    if (!((cf->_256 == 1 && (&f->distToFielder[0])[c] < lbl_3_rodata_B70) || (cf->_252 != 0 && cf->_25B == 0))) {
        return;
    }
    g = g_Fielders;
    g += i;
    g->_014 = f->x;
    g->_018 = f->y;
    g->_01C = f->z;
    g->_030 = lbl_3_rodata_B20;
    g->_034 = lbl_3_rodata_B20;
    g->_050 = lbl_3_rodata_B20;
    g->_068 = lbl_3_rodata_B20;
}

// .text:0x0003ACC0 size:0x174 mapped:0x80679D54
void fn_3_3ACC0(int i) {
    InMemFielderView* f = &g_Fielders[i];
    if (g_Ball.fielderWithBallIndexStored < 0) {
        if (i == g_FieldingLogic._0B0 && g_FieldingLogic._139 == 0 && g_Ball.framesSinceHit >= lbl_3_data_484C[0]) {
            if (g_Ball.framesSinceHit < lbl_3_data_484C[1] && (lbl_3_bss_170 < 0 || !(g_FieldingLogic.padButtons[0] & 0x200)) &&
                (g_d_GameSettings.GameModeSelected != 2 || g_Practice.instructionNumber < 0 || g_Practice.practice_fielding_enableSprinting == 0)) {
                if ((f->_201 == 0 || i < 6 || i > 8 || g_Ball.ballZoneAwayFromHome != 0) && lbl_3_bss_16C >= 0) {
                    s16 t = f->_19A;
                    if (t < 0) {
                        if (g_Ball.framesSinceHit > f->_1D2 + 3) {
                            goto blk;
                        }
                    } else {
                        if (fn_3_9FCF8(lbl_3_bss_16C, t) < lbl_3_data_484C[2]) {
                            goto blk;
                        }
                    }
                }
            } else {
                goto blk;
            }
        }
        return;
    } else {
    blk:
        f->_1FF = 2;
        f->_201 = 0;
    }
}

// .text:0x0003AE34 size:0x53C mapped:0x80679EC8
// NONMATCHING 96%: fielder pointer kept in r29 vs r28; calls fn_3_261E8/fn_3_433E0 through casts until their prototypes gain the index arg
#if NONMATCHING
void fn_3_3AE34(int i) {
    s32 off = i * 0x268; // sizeof(InMemFielderView)
    InMemFielderView* f = (InMemFielderView*)((u8*)g_Fielders + off);
    s32 tgt;
    s16 k;
    if (g_Ball.framesSinceHit <= 0) {
        return;
    }
    if (f->_1FF == 0) {
        f->_201 = 0;
        if (g_FieldingLogic._0B6 == i && i >= 6 && i <= 8) {
            f->_201 = 1;
        }
        f->_1FF = 1;
    }
    if (g_d_GameSettings.GameModeSelected == 2 && g_GameLogic.secondaryGameMode == 0xC) {
        return;
    }
    switch (fn_3_53130(i)) {
    case 2:
        return;
    case 1:
        break;
    default:
        if (f->_1FF == 1) {
            if (g_Ball.framesSinceHit == f->_1D2) {
                fn_3_447C4(i);
            }
            if (f->_252 != 0) {
                fn_3_261E8(i);
                f->_1A2 = 0;
                f->_1FF = 2;
            } else {
                fn_3_433E0(i);
            }
            fn_3_3ACC0(i);
        } else {
            if (f->_1FF == 2) {
                g_FieldingLogic._139 = 0;
            }
            tgt = lbl_3_bss_170;
            if (g_FieldingLogic._10E != 0) {
                tgt = -1;
            }
            f->_19E = tgt;
            if (g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] == 0 && tgt >= 0 && f->_1A0 > 0xA) {
                g_FieldingLogic._0CC = -1;
            }
            if (tgt >= 0) {
                FieldingBoost* t = g_FieldingLogic.curBoost;
                if (t->state != 3 && t->state != 4) {
                    if (g_FieldingLogic.padButtons[1] & 0x200) {
                        t->timer = 0;
                    }
                    if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0 && g_Practice.practice_fielding_enableSprinting != 0) {
                        g_FieldingLogic.curBoost->timer = 0;
                    }
                }
            }
            fn_3_3A584(i);
        }
        break;
    }
    if (g_Ball.ballState != 0 && g_Ball.ballState != 3) {
        if (f->_18C == 6) {
            SetFielderAct(i, 0xB);
        } else {
            SetFielderAct(i, 0xC);
        }
        if (i <= 5) {
            f->_1D5 = 3;
        } else {
            f->_1D5 = 2;
        }
        g_FieldingLogic._0B0 = -1;
    }
    k = f->_18C;
    if (k >= 0 && k <= 3 && (&f->distToBase[0])[k] > lbl_3_rodata_B78) {
        if (k >= 0 && k <= 3) {
            if ((&g_FieldingLogic._0D0[0])[k] == i) {
                (&g_FieldingLogic._0D0[0])[k] = -1;
                g_FieldingLogic._101[k] = 0;
            }
            f->_18C = -1;
            f->_1D7 = 0;
            if (f->_1D3 == 1) {
                SetFielderActP(f, i, 12);
            }
        } else if (k == 5) {
            f->_18C = -1;
            f->_1D7 = 0;
            g_FieldingLogic._0D8 = -1;
            g_FieldingLogic.playerAtMoundCutoffLocation = 0;
            if (f->_1D3 == 14) {
                SetFielderActP(f, i, 12);
            }
        }
    }
    if (g_FieldingLogic._0B0 != i) {
        s16 cur = g_FieldingLogic._0B0;
        InMemFielderView* c = &g_Fielders[cur];
        if (g_Ball.framesSinceHit >= lbl_3_data_484C[0] && g_FieldingLogic._139 == 0 &&
            ((c->_256 == 1 && f->distToFielder[cur] < lbl_3_rodata_B70) || (c->_252 != 0 && c->_25B == 0))) {
            InMemFielderView* g = (InMemFielderView*)((u8*)g_Fielders + off);
            g->_014 = f->x;
            g->_018 = f->y;
            g->_01C = f->z;
            g->_030 = lbl_3_rodata_B20;
            g->_034 = lbl_3_rodata_B20;
            g->_050 = lbl_3_rodata_B20;
            g->_068 = lbl_3_rodata_B20;
        }
    }
}
#endif

// .text:0x0003B370 size:0x3F4 mapped:0x8067A404
void fn_3_3B370(int i) {
    InMemFielderView* f = &g_Fielders[i];
    s32 tgt;
    s16 k;
    if (g_Minigame.GameMode_MiniGame != 5 && g_Minigame.GameMode_MiniGame != 6 && g_Ball.framesSinceHit <= 0) {
        return;
    }
    switch (fn_3_53130(i)) {
    case 2:
        return;
    case 1:
        break;
    default:
        tgt = lbl_3_bss_170;
        if (g_FieldingLogic._10E != 0) {
            tgt = -1;
        }
        f->_19E = tgt;
        if (g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] == 0 && tgt >= 0 && f->_1A0 > 0xA) {
            g_FieldingLogic._0CC = -1;
        }
        if (tgt >= 0) {
            FieldingBoost* t = g_FieldingLogic.curBoost;
            if (t->state != 3 && t->state != 4) {
                if (g_FieldingLogic.padButtons[1] & 0x200) {
                    t->timer = 0;
                }
                if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0 && g_Practice.practice_fielding_enableSprinting != 0) {
                    g_FieldingLogic.curBoost->timer = 0;
                }
            }
        }
        fn_3_3A584(i);
        break;
    }
    if (g_Minigame.GameMode_MiniGame == 5 || g_Minigame.GameMode_MiniGame == 6) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected != 6) {
        if (g_Ball.ballState != 0 && g_Ball.ballState != 3) {
            if (f->_18C == 6) {
                SetFielderAct(i, 0xB);
            } else {
                SetFielderAct(i, 0xC);
            }
            if (i <= 5) {
                f->_1D5 = 3;
            } else {
                f->_1D5 = 2;
            }
            g_FieldingLogic._0B0 = -1;
        }
        k = f->_18C;
        if (k >= 0 && k <= 3 && (&f->distToBase[0])[k] > lbl_3_rodata_B78) {
            if (k >= 0) {
                if (k <= 3) {
                    s16 owner = (&g_FieldingLogic._0D0[0])[k];
                    if (owner == i) {
                        (&g_FieldingLogic._0D0[0])[k] = -1;
                        g_FieldingLogic._101[k] = 0;
                    }
                    f->_18C = -1;
                    f->_1D7 = 0;
                    if (f->_1D3 == 1) {
                        SetFielderActP(f, i, 12);
                    }
                } else if (k == 5) {
                    g_FieldingLogic._0D8 = -1;
                    g_FieldingLogic.playerAtMoundCutoffLocation = 0;
                    f->_18C = -1;
                    f->_1D7 = 0;
                    if (f->_1D3 == 14) {
                        SetFielderActP(f, i, 12);
                    }
                }
            }
        }
    }
}

// .text:0x0003B764 size:0x238 mapped:0x8067A7F8
void fn_3_3B764(void) {
    InMemFielderView* f = &g_Fielders[g_FieldingLogic._0B0];
    f32 dx;
    f32 dz;
    f32 d;
    f32 a2;
    f32 b2;
    if (g_FieldingLogic._0C4 >= 0) {
        g_Ball.fielderAboutToGetBall_hasBall = -1;
        return;
    }
    if (g_FieldingLogic._0B0 >= 0 && g_Ball.looseBall_5FrameCountdown == 0) {
        if (g_Ball.AtBat_ContactResult == 0) {
            if (f->_080 < lbl_3_rodata_B64) {
                g_Ball.fielderAboutToGetBall_hasBall = g_FieldingLogic._0B0;
            } else {
                g_Ball.fielderAboutToGetBall_hasBall = -1;
            }
        } else {
            dx = f->x - g_Ball.physicsSubstruct.futureCoordsAndDist[1].pos.x;
            dz = f->z - g_Ball.physicsSubstruct.futureCoordsAndDist[1].pos.z;
            a2 = dx * dx;
            b2 = dz * dz;
            d = a2 + b2;
            SQRT_L(d);
            if (d <= f->_074) {
                if (fn_3_9CE0(f->x, f->z) < f->reach[0]) {
                    g_Ball.fielderAboutToGetBall_hasBall = g_FieldingLogic._0B0;
                } else {
                    g_Ball.fielderAboutToGetBall_hasBall = -1;
                }
            }
        }
        if (g_Ball.fielderAboutToGetBall_hasBall >= 0) {
            g_Ball.ballIsLooseInd_unused = 0;
            g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt = 0;
            g_Ball.fielderBeingThrownTo = -1;
        }
    }
}

// .text:0x0003B99C size:0x48 mapped:0x8067AA30

void fn_3_3B99C(void) {
    if (g_Minigame.GameMode_MiniGame == 5) {
        return;
    }
    if (!(g_FieldingLogic.padButtons[1] & 0x100)) {
        return;
    }
    g_FieldingLogic.curPadRec->_2 = 2;
    g_FieldingLogic.curPadRec->stickAngle = lbl_3_bss_170;
}

// .text:0x0003B9E4 size:0x46C mapped:0x8067AA78
// NONMATCHING 93%: register allocation of the history/controls pointers; ball distance sum unfused in the original (fmuls+fadds); bss_170 re-addressed after fn_3_A7EF8
#if NONMATCHING
void fn_3_3B9E4(void) {
    InputStruct* ctl;
    s16* hist;
    s32 k;
    s32 i;
    InMemFielderView* f;
    g_FieldingLogic._0B6 = g_FieldingLogic._0B0;
    ctl = &g_Controls[((s32)g_GameLogic.teams[g_GameLogic.teamFielding])];
    hist = &lbl_3_bss_170;
    for (k = 19; k > 0; k--) {
        hist[k] = hist[k - 1];
    }
    fn_3_A7EF8();
    if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
        ctl = &g_Practice.inputs[g_GameLogic.teamFielding];
    }
    hist[0] = ctl->controlStickAngle;
    if (hist[0] == -1) {
        for (k = 1; k < 20; k++) {
            hist[k] = -1;
        }
    }
    if (hist[1] >= 0 && hist[2] >= 0) {
        lbl_3_bss_16C = hist[0];
    } else {
        lbl_3_bss_16C = -1;
    }
    g_FieldingLogic.padButtons[0] = ctl->buttonInput;
    g_FieldingLogic.padButtons[1] = ctl->newButtonInput;
    g_FieldingLogic.padButtons[2] = ctl->_08;
    /* inlined fn_3_3B99C */
    if (g_Minigame.GameMode_MiniGame != 5 && (g_FieldingLogic.padButtons[1] & 0x100)) {
        g_FieldingLogic.curPadRec->_2 = 2;
        g_FieldingLogic.curPadRec->stickAngle = lbl_3_bss_170;
    }
    if (g_Ball.framesSinceHit <= 0) {
        return;
    }
    if (g_Ball.framesSinceHit == 1) {
        fn_3_34450();
    } else {
        if (g_Ball.framesSinceHit > 3) {
            fn_3_39EB0();
        }
        fn_3_57144();
    }
    f = g_Fielders;
    for (i = 0; i < 9; i++, f++) {
        if (g_d_GameSettings.minigamesEnabled == 0 || g_Minigame.minigameRelatedIndex == i) {
            fn_3_54B58(i);
            f->_07C = fn_3_9CE0(f->x, f->z);
            if (f->_050 == lbl_3_rodata_B20) {
                f->_038 = lbl_3_rodata_B20;
                f->_03C = lbl_3_rodata_B20;
            } else {
                f->_038 = f->_030 / f->_050;
                f->_03C = f->_034 / f->_050;
            }
            f->_1EA = 0;
            f->_217 = 0;
        }
    }
    fn_3_544B8();
    if (g_d_GameSettings.minigamesEnabled != 0) {
        fn_3_53F48();
    } else if (g_Ball.fielderWBallIndex >= 0) {
        InMemFielderView* h = &g_Fielders[g_Ball.fielderWBallIndex];
        f32 x = h->x;
        f32 z = h->z;
        f32 d = x * x + z * z;
        g_Ball.AtBat_Contact_BallPos.x = x;
        g_Ball.AtBat_Contact_BallPos.y = h->y;
        g_Ball.AtBat_Contact_BallPos.z = z;
        g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x = x;
        g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z = z;
        SQRT_L(d);
        g_Ball.ballDistanceFromHome = d;
    }
    if (g_Ball.ballState == 1) {
        g_FieldingLogic._0B0 = g_Ball.fielderWBallIndex;
        g_FieldingLogic._139 = 0;
    } else if (g_Ball.ballState == 2 && g_FieldingLogic._0C2 < 0) {
        g_FieldingLogic._0B0 = -1;
    }
}
#endif

// .text:0x0003BE50 size:0x358 mapped:0x8067AEE4
// NONMATCHING 96%: f-reg numbering / 0.0 constant reuse; the second distance sum is unfused in the original; calls fn_3_526DC through a cast until its prototype gains the index arg
#if NONMATCHING
void fn_3_3BE50(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 t;
    f32 px;
    f32 pz;
    f32 dx;
    f32 dz;
    f32 d;
    if (f->_1EC != 0) {
        return;
    }
    if (g_Ball.framesSinceThrowStarted == 5 && g_Ball.ballVelocity != lbl_3_rodata_B20) {
        t = f->_074 / g_Ball.ballVelocity;
        px = g_Ball.physicsSubstruct.velocity.x * t + g_Ball.AtBat_Contact_BallPos.x;
        pz = g_Ball.physicsSubstruct.velocity.z * t + g_Ball.AtBat_Contact_BallPos.z;
        dx = f->x - px;
        dz = f->z - pz;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        if (d > f->reach[0]) {
            f->_1E9 = 1;
            f->_014 = px;
            f->_01C = pz;
            dx = px - f->x;
            dz = pz - f->z;
            if (dx == lbl_3_rodata_B20 && dz == lbl_3_rodata_B20) {
                f->_050 = lbl_3_rodata_B20;
                f->_068 = lbl_3_rodata_B20;
            } else {
                f->_064 = atan2(dz, dx);
                d = dx * dx + dz * dz;
                SQRT_L(d);
                f->_068 = d;
            }
            f->_1D9 = 1;
        }
    }
    fn_3_526DC(i);
    if (f->_1E9 != 0 && f->_050 == lbl_3_rodata_B20) {
        f->_1E9 = 0;
    }
    if (g_Ball.fielderBeingThrownTo == i) {
        fn_3_4E638();
    }
}
#endif

// .text:0x0003C1A8 size:0x78 mapped:0x8067B23C
void fn_3_3C1A8(int i) {
    InMemFielderView* f = &g_Fielders[i];
    if (f->_1EC == 0 && fn_3_53130(i) == 0) {
        f->_050 = lbl_3_rodata_B20;
        f->_1E3 = 1;
        f->_1D5 = 0;
        f->_014 = f->x;
        f->_01C = f->z;
    }
}

// .text:0x0003C220 size:0x50 mapped:0x8067B2B4
void fn_3_3C220(int i) {
    InMemFielderView* f = &g_Fielders[i];
    if (fn_3_53130(i) == 0) {
        f->_050 = lbl_3_rodata_B20;
        f->_068 = lbl_3_rodata_B20;
    }
}

// .text:0x0003C270 size:0x214 mapped:0x8067B304
int fn_3_3C270(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 tx;
    f32 tz;
    f32 dz;
    f32 dx;
    f32 d;
    f32 a2;
    f32 b2;
    f->_18C = 0xE;
    f->_1D7 = 2;
    if (i != -1) {
        f->_1D3 = 0xE;
        if (lbl_3_data_3C40[14].anim >= 0) {
            g_FieldingLogic._0F8[i] = lbl_3_data_3C40[14].anim;
        }
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_1A4 = 0;
        f->_1AC = 0;
        f->_1FF = 0;
    }
    f->_1D6 = 0xB;
    tx = lbl_3_data_4444[8];
    tz = lbl_3_data_4444[9];
    f->_014 = tx;
    f->_01C = tz;
    dx = tx - f->x;
    dz = tz - f->z;
    if (0.0f == dx && 0.0f == dz) {
        f->_050 = 0.0f;
        f->_068 = 0.0f;
    } else {
        f->_064 = (f32)atan2(dz, dx);
        a2 = dz * dz;
        d = dx * dx + a2;
        SQRT_L(d);
        f->_068 = d;
    }
    f->_1D9 = 1;
    return 1;
}

// .text:0x0003C484 size:0x110 mapped:0x8067B518
int fn_3_3C484(int i) {
    InMemFielderView* f = &g_Fielders[i];
    if (f->distToBase[0] < 5.0f) {
        f->_18C = 9;
    } else if (f->distToBase[1] < 5.0f) {
        f->_18C = fn_3_3D7D4(i);
    } else if (f->distToBase[2] < 5.0f) {
        f->_18C = fn_3_3D7D4(i);
    } else if (f->distToBase[3] < 5.0f) {
        f->_18C = fn_3_3D7D4(i);
    } else {
        return 0;
    }
    f->_1D7 = 2;
    if (i != -1) {
        int v;
        f->_1D3 = 0xE;
        v = lbl_3_data_3C40[14].anim;
        if (v >= 0) {
            g_FieldingLogic._0F8[i] = v;
        }
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_1A4 = 0;
        f->_1AC = 0;
        f->_1FF = 0;
    }
    f->_1D6 = 0xB;
    return 1;
}

// .text:0x0003C594 size:0x5F8 mapped:0x8067B628
// NONMATCHING 77%: our loop hoists the float constants and indexes the base arrays (lhax/sthx) where the original strength-reduces FieldingLogic/fielder pointers
#if NONMATCHING
int fn_3_3C594(int i) {
    InMemFielderView* f = &g_Fielders[i];
    s32 k;
    s32 owner;
    f32 me;
    f32 theirs;
    s16 holder = g_Ball.fielderWBallIndex;
    f32 dist = g_Ball.ballDistanceFromHome;
    f32 spd = g_Ball.ballVelocity;
    s16 ang = g_Ball.ballAngleFromHome;
    for (k = 0; k < 4; k++) {
        if (g_FieldingLogic._101[k] != 0) {
            continue;
        }
        owner = (&g_FieldingLogic._0D0[0])[k];
        if (holder == owner) {
            continue;
        }
        me = (&f->distToBase[0])[k];
        if (me < lbl_3_rodata_B60) {
            goto take;
        }
        theirs = (&g_Fielders[owner].distToBase[0])[k];
        if (!(me < theirs - lbl_3_rodata_B68)) {
            continue;
        }
        if (i != 0 || !(dist < lbl_3_rodata_C10) || !(spd < lbl_3_rodata_C14)) {
            goto take;
        }
        if (k == 1 && ang > 0x200 && ang < 0x400) {
            if (me < theirs - lbl_3_rodata_B64) {
                goto take;
            }
        } else if (k != 3 || ang <= 0x400 || ang >= 0x600 || me < theirs - lbl_3_rodata_B64) {
            goto take;
        }
    }
    owner = g_FieldingLogic._0D8;
    if (g_FieldingLogic.playerAtMoundCutoffLocation == 0 && owner != -1 &&
        (f->_0B8 < lbl_3_rodata_B64 ||
         lbl_3_rodata_B78 + f->_0B8 < g_Fielders[owner]._0B8)) {
        goto take_cutoff;
    }
    return 0;
take:
    /* take base k from its current owner */
    if (g_Ball.fielderBeingThrownTo == owner) {
        g_Ball.fielderBeingThrownTo = i;
    }
    if (owner >= 0) {
        InMemFielderView* o = &g_Fielders[owner];
        ReleaseBaseInline(o, owner);
        SetFielderAct(owner, 12);
        g_Fielders[owner]._1D5 = 3;
    }
    f->_18C = k;
    f->_1D7 = 1;
    SetFielderAct(i, 1);
    (&g_FieldingLogic._0D0[0])[k] = i;
    return 1;
take_cutoff:
    if (owner >= 0 && holder != owner) {
        InMemFielderView* o = &g_Fielders[owner];
        ReleaseBaseInline(o, owner);
        SetFielderAct(owner, 12);
        g_Fielders[owner]._1D5 = 4;
    }
    f->_18C = 5;
    f->_1D7 = 2;
    SetFielderAct(i, 0xE);
    g_FieldingLogic._0D8 = i;
    return 1;
}
#endif

// .text:0x0003CB8C size:0x124 mapped:0x8067BC20
int fn_3_3CB8C(int i) {
    InMemFielderView* f;
    if (g_Ball.AtBat_ContactResult > 1) {
        return 0;
    }
    if (g_Ball.hitWallInd != 0) {
        return 0;
    }
    if (g_FieldingLogic._0BC >= 0) {
        return 0;
    }
    if (g_Ball.AtBat_ContactResult == 0) {
        if (g_Ball.landingSpotZoneAwayFromHome < 1 || i < 6) {
            goto fail;
        }
        if (g_Ball.landingSpotAngle < 0x380 && i == 6) {
            return 0;
        }
        if (g_Ball.landingSpotAngle > 0x480 && i == 8) {
            return 0;
        }
    } else {
        if (i < 6 || i != g_FieldingLogic._0B8) {
        fail:
            return 0;
        }
    }
    f = &g_Fielders[i];
    if (i != -1) {
        f->_1D3 = 0x18;
        if (lbl_3_data_3C40[24].anim >= 0) {
            g_FieldingLogic._0F8[i] = lbl_3_data_3C40[24].anim;
        }
        g_FieldingLogic._0BC = i;
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_1A4 = 0;
        f->_1AC = 0;
        f->_1FF = 0;
    }
    g_FieldingLogic._0BC = i;
    return 1;
}

// .text:0x0003CCB0 size:0x654 mapped:0x8067BD44
// NONMATCHING 92%: cover-decision branch layout (the original keeps a 0/1 result flag); f-reg numbering in the inlined fn_3_3C270 body
#if NONMATCHING
void fn_3_3CCB0(int i) {
    InMemFielderView* f = &g_Fielders[i];
    s32 k;
    s32 cover;
    if (f->_1EC != 0 || fn_3_53130(i) != 0 || g_Ball.deadBallReason != 0) {
        return;
    }
    if (g_FieldingLogic._0C4 == 5 && f->_18C == 5) {
        fn_3_3BE50(i);
        return;
    }
    if (i <= 5) {
        if (fn_3_3C594(i) != 0) {
            return;
        }
        if (TakeNearBaseInline(i) != 0) {
            return;
        }
    }
    for (k = 0; k < 4; k++) {
        if (i == (&g_FieldingLogic._0D0[0])[k]) {
            f->_18C = k;
            SetFielderAct(i, 1);
            return;
        }
    }
    if (i >= 6) {
        cover = 0;
        if (g_Ball.AtBat_ContactResult > 1) {
        } else if (g_Ball.hitWallInd != 0) {
        } else if (g_FieldingLogic._0BC >= 0) {
        } else if (g_Ball.AtBat_ContactResult == 0) {
            if (g_Ball.landingSpotZoneAwayFromHome >= 1 && i >= 6 && !(g_Ball.landingSpotAngle < 0x380 && i == 6) &&
                !(g_Ball.landingSpotAngle > 0x480 && i == 8)) {
                cover = 1;
            }
        } else if (i >= 6 && i == g_FieldingLogic._0B8) {
            cover = 1;
        }
        if (cover != 0) {
            SetFielderActTag(i, 0x18);
            g_FieldingLogic._0BC = i;
            return;
        }
        if (f->_18C == 7) {
            goto go_home;
        }
        if (g_FieldingLogic._0F8[i] != 9) {
            g_Fielders[i]._18C = 7;
            SetFielderAct(i, 0xE);
            f->_1D6 = 0;
            f->_190 = -1;
        }
        return;
    }
    if (f->_070 > lbl_3_rodata_C18) {
        f->_18C = fn_3_3D7D4(i);
        f->_1D7 = 2;
        SetFielderAct(i, 0xE);
        f->_1D6 = 0xB;
        return;
    }
go_home:
    if (f->_1DE != 0) {
        GoHomeInline(i);
        return;
    }
    f->_030 = lbl_3_rodata_B20;
    f->_034 = lbl_3_rodata_B20;
    f->_050 = lbl_3_rodata_B20;
}
#endif

// .text:0x0003D304 size:0x3A8 mapped:0x8067C398
// NONMATCHING 96%: table x reads via lfsx in the original; f30/f31 swapped; calls fn_3_2F574/fn_3_526DC through casts until their prototypes gain the index arg
#if NONMATCHING
void fn_3_3D304(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 tx;
    f32 tz;
    f32 ox;
    f32 oz;
    f32 dx;
    f32 dz;
    f32 d;
    s32 team;
    f32* home;
    if (f->_20F != 0) {
        g_FieldingLogic._111 = 0;
        return;
    }
    if (f->_210 != 0) {
        fn_3_251E4(i);
        f->_1EE = 0;
        return;
    }
    if (fn_3_53130(i) != 0) {
        return;
    }
    if (f->_211 != 0) {
        fn_3_A96FC(i);
        return;
    }
    if (f->_1EE != 0) {
        fn_3_A9984(i);
        return;
    }
    if (f->_1EF != 0) {
        return;
    }
    if (f->_203 != 0) {
        fn_3_2F574(i);
        return;
    }
    if (g_Ball.fielderWBallIndex == i && f->_1EC == 0) {
        g_Ball.fielderWBallIndex = -1;
    }
    team = g_GameLogic.teamFielding;
    home = ((f32 (*)[2][2])lbl_3_data_4290)[g_d_GameSettings.StadiumID][g_GameLogic.awayTeamBattingInd_battingTeam];
    tx = home[0];
    tz = home[1];
    if (f->rosterID != g_GameLogic.Team_CaptainRosterLoc[team]) {
        fn_3_9F79C(lbl_3_data_4348[g_d_GameSettings.StadiumID * 2 + team], lbl_3_data_4300[i * 2],
                   lbl_3_data_4300[i * 2 + 1], &ox, &oz);
        tx += ox;
        tz += oz;
    }
    f->_1D6 = 0xD;
    f->_014 = tx;
    f->_01C = tz;
    dx = tx - f->x;
    dz = tz - f->z;
    if (lbl_3_rodata_B20 == dx && lbl_3_rodata_B20 == dz) {
        f->_050 = lbl_3_rodata_B20;
        f->_068 = lbl_3_rodata_B20;
    } else {
        f->_064 = (f32)atan2(dz, dx);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        f->_068 = d;
    }
    f->_1D9 = 1;
    fn_3_526DC(i);
    if (f->_068 <= lbl_3_rodata_B80) {
        SetFielderAct(i, 0);
        f->_1FA = 1;
    }
    if (i == g_Ball.fielderWBallIndex) {
        g_FieldingLogic._0C4 = -1;
    }
}
#endif

// .text:0x0003D6AC size:0x128 mapped:0x8067C740
void fn_3_3D6AC(int i) {
    InMemFielderView* f = &g_Fielders[i];
    if (fn_3_53130(i) == 0 && f->_1EC == 0) {
        f->_050 = 0.0f;
        f->_1E3 = 1;
        f->_1D5 = 0;
        f->_014 = f->x;
        f->_01C = f->z;
        if (g_Ball.ballState == 0) {
            if (i == 6) {
                if (g_Ball.ballAngleFromHome >= 0x400) {
                    if (g_Ball.ballAngleFromHome < 0xC00) {
                        goto body;
                    }
                }
            } else if (i != 8 || g_Ball.ballAngleFromHome < 0x400 || g_Ball.ballAngleFromHome >= 0xC00) {
                goto body;
            }
        } else {
        body:
            if (i != -1) {
                f->_1D3 = 9;
                if (lbl_3_data_3C40[9].anim >= 0) {
                    g_FieldingLogic._0F8[i] = lbl_3_data_3C40[9].anim;
                }
                f->_1D5 = 0;
                f->_1D6 = 0;
                f->_1A4 = 0;
                f->_1AC = 0;
                f->_1FF = 0;
            }
        }
        f->_1F0 = 1;
    }
}

// .text:0x0003D7D4 size:0x3A4 mapped:0x8067C868
int fn_3_3D7D4(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int r;
    int j;
    InMemFielderView* p;
    if (f->x > lbl_3_rodata_B20) {
        if (f->distToBase[2] > f->distToBase[1]) {
            r = 0xA;
        } else {
            r = 0xB;
        }
    } else if (f->distToBase[2] > f->distToBase[3]) {
        r = 0xD;
    } else {
        r = 0xC;
    }
    if (r == 0xA) {
        p = g_Fielders;
        for (j = 0; j < 6; j++, p++) {
            if (j != i && p->_18C == 0xA) {
                r = 0xB;
            }
        }
    } else if (r == 0xB) {
        p = g_Fielders;
        for (j = 0; j < 6; j++, p++) {
            if (j != i && p->_18C == 0xA) {
                r = 0xC;
            }
        }
    } else if (r == 0xC) {
        p = g_Fielders;
        for (j = 0; j < 6; j++, p++) {
            if (j != i && p->_18C == 0xA) {
                r = 0xB;
            }
        }
    } else if (r == 0xD) {
        p = g_Fielders;
        for (j = 0; j < 6; j++, p++) {
            if (j != i && p->_18C == 0xA) {
                r = 0xC;
            }
        }
    }
    return r;
}

// .text:0x0003DB78 size:0x7D4 mapped:0x8067CC0C
// NONMATCHING 92%: register/f-reg numbering in the inlined run-target blocks; calls fn_3_526DC through a cast until its prototype gains the index arg
#if NONMATCHING
void fn_3_3DB78(int i) {
    s32 off = i * 0x268; // sizeof(InMemFielderView)
    InMemFielderView* f = (InMemFielderView*)((u8*)g_Fielders + off);
    s16 k;
    if (fn_3_53130(i) != 0) {
        return;
    }
    if (g_Ball.homeRunClassification != 0 && i <= 1) {
        return;
    }
    k = f->_18C;
    if (k == 5) {
        f32 xo;
        f32 zo;
        if (g_FieldingLogic._0C4 == 5) {
            fn_3_3BE50(i);
            fn_3_A7C88();
            if (g_Ball.fielderBeingThrownTo == i) {
                fn_3_4E638();
            }
            return;
        }
        zo = lbl_3_rodata_B68;
        xo = zo;
        if (f->x < lbl_3_rodata_B20) {
            xo = lbl_3_rodata_C1C;
        }
        if (f->z < lbl_3_data_4444[9]) {
            zo = lbl_3_rodata_C1C;
        }
        if (g_FieldingLogic.playerAtMoundCutoffLocation != 0 && f->_050 <= lbl_3_rodata_C20) {
            InMemFielderView* g = (InMemFielderView*)((u8*)g_Fielders + off);
            g->_014 = f->x;
            g->_018 = f->y;
            g->_01C = f->z;
            g->_030 = lbl_3_rodata_B20;
            g->_034 = lbl_3_rodata_B20;
            g->_050 = lbl_3_rodata_B20;
            g->_068 = lbl_3_rodata_B20;
            return;
        }
        SetRunTargetInline(f, lbl_3_data_4444[8] + xo, lbl_3_data_4444[9] + zo);
        fn_3_526DC(i);
        if (f->_068 < lbl_3_rodata_B78) {
            g_FieldingLogic.playerAtMoundCutoffLocation = 1;
            f->_068 = lbl_3_rodata_B20;
            f->_1D6 = 8;
        } else {
            g_FieldingLogic.playerAtMoundCutoffLocation = 0;
            f->_1D6 = 0xB;
        }
    } else if (k == 7) {
        SetRunTargetInline(f, lbl_3_data_44B4[i * 2 + 4], lbl_3_data_44B4[i * 2 + 5]);
        fn_3_526DC(i);
        if (lbl_3_rodata_B20 == f->_068) {
            SetFielderAct(i, 0);
        }
    } else if (k >= 8 && k <= 13) {
        SetRunTargetInline(f, lbl_3_data_4484[k * 2 - 16], lbl_3_data_4484[k * 2 - 15]);
        fn_3_526DC(i);
        if (lbl_3_rodata_B20 == f->_068) {
            SetFielderAct(i, 0);
        }
    } else if (k == 14) {
        if (f->_1DE == 0) {
            SetFielderAct(i, 0);
            f->_18C = -1;
            return;
        }
        fn_3_526DC(i);
    } else if (k == 15) {
        fn_3_526DC(i);
        if (lbl_3_rodata_B20 == f->_068) {
            SetFielderAct(i, 0);
        }
    }
}
#endif

// .text:0x0003E34C size:0x11C mapped:0x8067D3E0
void fn_3_3E34C(int i) {
    InMemFielderView* f = &g_Fielders[i];
    if (f->_19C >= 1) {
        if (f->_1C5 != 0) {
            if (i != -1) {
                f->_1D3 = 0x12;
                if (lbl_3_data_3C40[18].anim >= 0) {
                    g_FieldingLogic._0F8[i] = lbl_3_data_3C40[18].anim;
                }
            f->_1D5 = 0;
            f->_1D6 = 0;
            f->_1A4 = 0;
            f->_1AC = 0;
            f->_1FF = 0;
            }
        } else if (i != -1) {
            f->_1D3 = 0;
            if (lbl_3_data_3C40[0].anim >= 0) {
                g_FieldingLogic._0F8[i] = lbl_3_data_3C40[0].anim;
            }
            f->_1D5 = 0;
            f->_1D6 = 0;
            f->_1A4 = 0;
            f->_1AC = 0;
            f->_1FF = 0;
        }
    } else if (g_FieldingLogic._11C != 0 && i != -1) {
        f->_1D3 = 0;
        if (lbl_3_data_3C40[0].anim >= 0) {
            g_FieldingLogic._0F8[i] = lbl_3_data_3C40[0].anim;
        }
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_1A4 = 0;
        f->_1AC = 0;
        f->_1FF = 0;
    }
}

// .text:0x0003E468 size:0x228 mapped:0x8067D4FC
void fn_3_3E468(void) {
    s32 i;
    int j;
    s32 k;
    int best;
    f32 min;
    InMemFielderView* f;
    for (i = 0; i < 9; i++) {
        g_Fielders[i]._18C = -1;
        g_Fielders[i]._1D7 = 0;
    }
    for (k = 0; k < 5; k++) {
        g_FieldingLogic._0D0[k] = -1;
        g_FieldingLogic._101[k] = 0;
    }
    for (j = 0; j < 4; j++) {
        min = lbl_3_rodata_C24;
        for (k = 0; k < 6; k++) {
            if (g_FieldingLogic._0F8[k] == 0 && g_Fielders[k].distToBase[j] < min) {
                min = g_Fielders[k].distToBase[j];
                best = k;
            }
        }
        f = &g_Fielders[best];
        f->_18C = j;
        f->_1D7 = 1;
        if (best != -1) {
            f->_1D3 = 1;
            if (lbl_3_data_3C40[1].anim >= 0) {
                g_FieldingLogic._0F8[best] = lbl_3_data_3C40[1].anim;
            }
            f->_1D5 = 0;
            f->_1D6 = 0;
            f->_1A4 = 0;
            f->_1AC = 0;
            f->_1FF = 0;
        }
        g_FieldingLogic._0D0[j] = best;
    }
}

// .text:0x0003E690 size:0x4DC mapped:0x8067D724
// NONMATCHING 78%: sel/pick are uninitialised in the original (we zero them); per-base search loop unrolled differently; distance sum unfused there; calls fn_3_4EFC8 through a cast until its prototype gains (int, int)
#if NONMATCHING
void fn_3_3E690(void) {
    /* sel and pick start uninitialised in the original */
    s32 sel = 0;
    s32 best = 0x270F;
    InMemFielderView* f = g_Fielders;
    s32 i;
    s32 k;
    s32 eta;
    s32 pick = 0;
    f32 bx = g_Ball.physicsSubstruct.futureCoordsAndDist[0x3c].pos.x;
    f32 bz = g_Ball.physicsSubstruct.futureCoordsAndDist[0x3c].pos.z;
    u8 phase = g_Ball.ballZoneAwayFromHome;
    for (i = 0; i < 9; i++, f++) {
        if (bx == f->x && bz == f->z) {
            eta = 1;
        } else {
            f32 dx = bx - f->x;
            f32 dz = bz - f->z;
            f32 d = dx * dx + dz * dz;
            f32 sp;
            SQRT_L(d);
            sp = f[0].maxVelocity;
            if (lbl_3_rodata_B20 == sp) {
                sp = lbl_3_rodata_B60;
            }
            eta = (f->_1D1 >> 1) + (s32)(d / sp);
        }
        if (f->_1D3 == 2) {
            eta -= 0xF;
        }
        if (f->_18C >= 0 && f->_18C <= 3) {
            eta += 0x1E;
        }
        if (f->_210 != 0) {
            eta += f->_1C0;
        } else if (f->_212 == 3) {
            eta += 0x5A;
        }
        if (f->_20F != 0) {
            eta += f->_1BA;
        }
        if (phase >= 3 && i <= 5) {
            eta += 0x1E;
        }
        if (eta < best) {
            sel = i;
            best = eta;
        }
    }
    SetFielderAct(sel, 3);
    fn_3_4EFC8(sel, 0);
    g_Fielders[sel]._1DC = 4;
    for (i = 0; i < 9; i++) {
        g_Fielders[i]._18C = -1;
        g_Fielders[i]._1D7 = 0;
    }
    g_FieldingLogic._0D0[0] = -1;
    g_FieldingLogic._101[0] = 0;
    g_FieldingLogic._0D0[1] = -1;
    g_FieldingLogic._101[1] = 0;
    g_FieldingLogic._0D0[2] = -1;
    g_FieldingLogic._101[2] = 0;
    g_FieldingLogic._0D0[3] = -1;
    g_FieldingLogic._101[3] = 0;
    g_FieldingLogic._0D8 = -1;
    g_FieldingLogic.playerAtMoundCutoffLocation = 0;
    for (k = 0; k < 4; k++) {
        f32 dmin = lbl_3_rodata_C24;
        for (i = 0; i < 6; i++) {
            if (g_FieldingLogic._0F8[i] == 0 && (&g_Fielders[i].distToBase[0])[k] < dmin) {
                dmin = (&g_Fielders[i].distToBase[0])[k];
                pick = i;
            }
        }
        g_Fielders[pick]._18C = k;
        g_Fielders[pick]._1D7 = 1;
        SetFielderAct(pick, 1);
        (&g_FieldingLogic._0D0[0])[k] = pick;
    }
    g_FieldingLogic._0BE = -1;
}
#endif

// .text:0x0003EB6C size:0x4C8 mapped:0x8067DC00
// NONMATCHING 77%: same shape as fn_3_3E690 (uninitialised sel/pick zeroed here, inner base search unrolled differently, unfused distance sum); calls fn_3_4EFC8 through a cast
#if NONMATCHING
void fn_3_3EB6C(void) {
    /* sel and pick start uninitialised in the original */
    s32 sel = 0;
    s32 best = 0x270F;
    InMemFielderView* f = g_Fielders;
    s32 i;
    s32 k;
    s32 eta;
    s32 pick = 0;
    f32 bx = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    f32 bz = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
    u8 phase = g_Ball.ballZoneAwayFromHome;
    u8 caught = g_Ball.someCollisionInd;
    for (i = 0; i < 9; i++, f++) {
        if (bx == f->x && bz == f->z) {
            eta = 1;
        } else {
            f32 dx = bx - f->x;
            f32 dz = bz - f->z;
            f32 d = dx * dx + dz * dz;
            f32 sp;
            SQRT_L(d);
            sp = f[0].maxVelocity;
            if (lbl_3_rodata_B20 == sp) {
                sp = lbl_3_rodata_B60;
            }
            eta = (f->_1D1 >> 1) + (s32)(d / sp);
        }
        if (f->_1D3 == 2) {
            eta -= 0xF;
        }
        if (f->_18C >= 0 && f->_18C <= 3) {
            eta += 0x1E;
        }
        if (caught == 0 && lbl_3_rodata_B64 + f->_070 < g_Ball.physicsSubstruct.hitLandingSpotDistFromHome) {
            eta += 0x1E;
        }
        if (phase >= 3 && i <= 5) {
            eta += 0xF;
        }
        if (eta < best) {
            sel = i;
            best = eta;
        }
    }
    SetFielderAct(sel, 3);
    fn_3_4EFC8(sel, 0);
    g_Fielders[sel]._1DC = 0;
    for (i = 0; i < 9; i++) {
        g_Fielders[i]._18C = -1;
        g_Fielders[i]._1D7 = 0;
    }
    g_FieldingLogic._0D0[0] = -1;
    g_FieldingLogic._101[0] = 0;
    g_FieldingLogic._0D0[1] = -1;
    g_FieldingLogic._101[1] = 0;
    g_FieldingLogic._0D0[2] = -1;
    g_FieldingLogic._101[2] = 0;
    g_FieldingLogic._0D0[3] = -1;
    g_FieldingLogic._101[3] = 0;
    g_FieldingLogic._0D8 = -1;
    g_FieldingLogic.playerAtMoundCutoffLocation = 0;
    for (k = 0; k < 4; k++) {
        f32 dmin = lbl_3_rodata_C24;
        for (i = 0; i < 6; i++) {
            if (g_FieldingLogic._0F8[i] == 0 && (&g_Fielders[i].distToBase[0])[k] < dmin) {
                dmin = (&g_Fielders[i].distToBase[0])[k];
                pick = i;
            }
        }
        g_Fielders[pick]._18C = k;
        g_Fielders[pick]._1D7 = 1;
        SetFielderAct(pick, 1);
        (&g_FieldingLogic._0D0[0])[k] = pick;
    }
    g_FieldingLogic._0BE = -1;
}
#endif

// .text:0x0003F034 size:0xF0 mapped:0x8067E0C8
void fn_3_3F034(void) {
    int i;
    InMemFielderView* f;
    for (i = 0; i < 9; i++) {
        g_FieldingLogic._0F8[i] = 0;
        f = &g_Fielders[i];
        if (i != -1) {
            f->_1D3 = 0;
            if (lbl_3_data_3C40[0].anim >= 0) {
                g_FieldingLogic._0F8[i] = lbl_3_data_3C40[0].anim;
            }
            f->_1D5 = 0;
            f->_1D6 = 0;
            f->_1A4 = 0;
            f->_1AC = 0;
            f->_1FF = 0;
        }
    }
    g_FieldingLogic._0D0[0] = -1;
    g_FieldingLogic._101[0] = 0;
    g_FieldingLogic._0D0[1] = -1;
    g_FieldingLogic._101[1] = 0;
    g_FieldingLogic._0D0[2] = -1;
    g_FieldingLogic._101[2] = 0;
    g_FieldingLogic._0D0[3] = -1;
    g_FieldingLogic._101[3] = 0;
    g_FieldingLogic._0BC = -1;
    g_FieldingLogic._0BE = -1;
    g_FieldingLogic._0C2 = -1;
    if (g_Ball.AtBat_ContactResult == 0 && g_Ball.hangtimeOfHit > 0x2D) {
        fn_3_3EB6C();
    } else {
        fn_3_3E690();
    }
}

// .text:0x0003F124 size:0x128 mapped:0x8067E1B8
void fn_3_3F124(void) {
    SetFielderAct(0, 0x14);
    if ((g_Fielders[3]._182 + g_Fielders[5]._182) / 2 > g_Ball.Hit_HorizontalAngle) {
        SetFielderAct(3, 3);
    } else {
        SetFielderAct(5, 3);
    }
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}

// .text:0x0003F24C size:0x514 mapped:0x8067E2E0
// NONMATCHING 98%: SetFielderAct state/table regs (see docs/patterns/unsolved.md)
#if NONMATCHING
void fn_3_3F24C(void) {
    s16 ang = g_Ball.Hit_HorizontalAngle;
    if (g_Ball.Hit_VerticalAngle >= 0x400 && g_Ball.Hit_VerticalAngle <= 0xC00) {
        ang += 0x800;
        if (ang > 0x1000) {
            ang -= 0x1000;
        }
    }
    if (ang > 0xA00 && ang < 0xE00) {
        SetFielderAct(1, 3);
    } else if (ang >= 0xE00 || ang < 0x200) {
        if (g_Ball.Hit_VerticalAngle > 0x800) {
            SetFielderAct(2, 3);
        } else if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_BA0) {
            SetFielderAct(1, 3);
            SetFielderAct(2, 3);
        } else if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_B9C) {
            SetFielderAct(2, 3);
            SetFielderAct(3, 3);
        } else {
            SetFielderAct(3, 3);
            SetFielderAct(8, 3);
        }
    } else if (g_Ball.Hit_VerticalAngle > 0x800) {
        SetFielderAct(4, 3);
    } else if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_BA0) {
        SetFielderAct(1, 3);
        SetFielderAct(4, 3);
    } else if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_B9C) {
        SetFielderAct(4, 3);
        SetFielderAct(5, 3);
    } else {
        SetFielderAct(5, 3);
        SetFielderAct(6, 3);
    }
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}
#endif


// .text:0x0003F760 size:0x590 mapped:0x8067E7F4
// NONMATCHING 99.2%: registers only; the known SetFielderAct state/table-value r0/r3 swap (see docs/patterns rep_AC8 dead ends)
#if NONMATCHING
// Assign base-covering duties (state 3) to infielders at the start of a play.
void fn_3_3F760(void) {
    int a;
    int b;
    s16 t;
    f32 d;
    SetFielderAct(0, 3);
    if (g_Fielders[(1)]._1DA == 0) {
        if (g_Runners[(3)].runnerOnFieldOrOutOrScored == 1 && g_Runners[(3)].runningDirectionCode == 1 && g_Runners[(3)].fractionalBasesRan >= lbl_3_rodata_BCC && (t = g_Fielders[(1)]._186) > 0) {
            d = g_Ball.physicsSubstruct.futureCoordsAndDist[t].pos.x * g_Ball.physicsSubstruct.futureCoordsAndDist[t].pos.x +
                g_Ball.physicsSubstruct.futureCoordsAndDist[t].pos.z * g_Ball.physicsSubstruct.futureCoordsAndDist[t].pos.z;
            SQRT_L(d);
            if (d < lbl_3_rodata_B64) {
                SetFielderAct(1, 3);
            }
        } else {
            SetFielderAct(1, 3);
        }
    }
    if (g_Ball.Hit_HorizontalAngle < 0x400) {
        if (g_Fielders[(2)]._1DA == 0) {
            a = g_Fielders[(3)]._186;
            b = g_Fielders[(2)]._186;
            if (a - 15 < b) {
                if (g_Fielders[(0)]._186 - a < 0x78) {
                    SetFielderAct(3, 3);
                }
            } else if (g_Ball.physicsSubstruct.futureCoordsAndDist[b].pos.z < lbl_3_data_4444[3]) {
                if (g_Fielders[(0)]._186 - b < 0x50) {
                    SetFielderAct(2, 3);
                }
            } else if (g_Fielders[(0)]._186 - a < 0x78) {
                SetFielderAct(3, 3);
            }
        } else if (g_Fielders[(3)]._1DA == 0) {
            if (g_Fielders[(0)]._186 - g_Fielders[(3)]._186 < 0x78) {
                SetFielderAct(3, 3);
            }
        }
    } else {
        if (g_Fielders[(4)]._1DA == 0) {
            a = g_Fielders[(5)]._186;
            b = g_Fielders[(4)]._186;
            if (a - 15 < b) {
                if (g_Fielders[(0)]._186 - a < 0x78) {
                    SetFielderAct(5, 3);
                }
            } else if (g_Ball.physicsSubstruct.futureCoordsAndDist[b].pos.z < lbl_3_data_4444[3]) {
                if (g_Runners[(2)].runnerOnFieldOrOutOrScored != 1 || (s16)b <= 0) {
                    if (g_Fielders[(0)]._186 - b < 0x50) {
                        SetFielderAct(4, 3);
                    }
                }
            } else if (g_Fielders[(0)]._186 - a < 0x78) {
                SetFielderAct(5, 3);
            }
        } else if (g_Fielders[(5)]._1DA == 0) {
            if (g_Fielders[(0)]._186 - g_Fielders[(5)]._186 < 0x78) {
                SetFielderAct(5, 3);
            }
        }
    }
}
#endif

// .text:0x0003FCF0 size:0x5B8 mapped:0x8067ED84
// NONMATCHING 91.5%: registers (SetFielderAct swap) and block order around the 2/3-of-gap compares
#if NONMATCHING
// Split base-covering duties between infielders by the batted ball's angle
// (useBall: take the angle from the ball's current position instead of ball+0x1B9C).
void fn_3_3FCF0(int useBall) {
    int ang = g_Ball.Hit_HorizontalAngle;
    int a2, a3, a4, a5;
    int q;
    if (useBall != 0) {
        ang = (s16)fn_3_9FB8C(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.hitLandingSpotDistFromHome);
    }
    a2 = g_Fielders[(2)]._182;
    a3 = g_Fielders[(3)]._182;
    a4 = g_Fielders[(4)]._182;
    a5 = g_Fielders[(5)]._182;
    if (g_Fielders[(0)]._1DA == 0 && g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < lbl_3_rodata_B90 && g_Ball.maxYOfHit < lbl_3_rodata_BD8) {
        fn_3_3F760();
        return;
    }
    if (ang < a2 + (a3 - a2) / 5) {
        SetFielderAct(2, 3);
        SetFielderAct(3, 3);
    } else if (ang < (a2 + a3) / 2) {
        SetFielderAct(2, 3);
        SetFielderAct(3, 3);
    } else if (ang < a3 + (q = (a5 - a3) / 3)) {
        SetFielderAct(3, 3);
        if (ang > g_Fielders[(0)]._182 - 0x40) {
            SetFielderAct(0, 4);
        }
    } else if (ang < a3 + q * 2) {
        SetFielderAct(0, 4);
        if (__abs(ang - g_Fielders[(3)]._182) < __abs(ang - g_Fielders[(5)]._182)) {
            SetFielderAct(3, 3);
        } else {
            SetFielderAct(5, 3);
        }
    } else if (ang < a5 + (q = (a4 - a5) / 3)) {
        SetFielderAct(5, 3);
        if (ang < g_Fielders[(0)]._182 + 0x40) {
            SetFielderAct(0, 4);
        }
    } else if (ang < a5 + q * 2) {
        SetFielderAct(4, 3);
        SetFielderAct(5, 3);
    } else {
        SetFielderAct(4, 3);
        SetFielderAct(5, 3);
    }
}
#endif

// .text:0x000402A8 size:0x95C mapped:0x8067F33C
// NONMATCHING 95.6%: registers (SetFielderAct swap); orig keeps the infield mask and ball base in swapped saved regs
#if NONMATCHING
// Assign base-covering duties at the start of a play, by the ball's direction and which
// fielders are free (0x1DB == 0), then run the other per-play fielding setups.
void fn_3_402A8(void) {
    u32 mask = 0;
    u32 inf;
    int j;
    s16 ang;
    int a;
    f32 d3, d5, dx, dz;
    for (j = 0; j < 9; j++) {
        if (g_Fielders[(j)]._1DB == 0) {
            mask |= 1 << (j * 3);
        }
    }
    inf = mask & 0x9249;
    if ((inf != 0 && g_Ball.landingSpotZoneAwayFromHome <= 1 && g_Ball.maxYOfHit >= lbl_3_rodata_BD8) ||
        ((g_Fielders[(0)]._1DB == 0 || g_Fielders[(1)]._1DB == 0) && g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < lbl_3_rodata_C28)) {
        ang = fn_3_9FB8C(g_Ball.landingSpotLocation.x, g_Ball.landingSpotLocation.z);
        if (g_Fielders[(1)]._1DB == 0 && (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < lbl_3_rodata_BE4 || (ang > 0xA00 && ang < 0xE00))) {
            SetFielderAct(1, 3);
            goto done;
        }
        if ((g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < lbl_3_rodata_C2C && ang > 0x300 && ang < 0x500) ||
            (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < lbl_3_rodata_C30 && ang > 0x300 && ang < 0x500 && (mask & 1)) ||
            (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < lbl_3_rodata_C34 && ang > 0x200 && ang < 0x600)) {
            SetFielderAct(0, 3);
            goto done;
        }
        if (ang < 0x2C0) {
            SetFielderAct(2, 3);
            goto done;
        }
        if (ang < 0x400) {
            SetFielderAct(3, 3);
            goto done;
        }
        if (ang < 0x540) {
            SetFielderAct(5, 3);
            goto done;
        }
        if (ang < 0x800) {
            SetFielderAct(4, 3);
            goto done;
        }
    }
    if (mask & 0x1240000) {
        fn_3_9FB8C(g_Ball.landingSpotLocation.x, g_Ball.landingSpotLocation.z);
        a = g_Ball.Hit_HorizontalAngle;
        if (a < 0x3C0) {
            SetFielderAct(8, 3);
            SetFielderAct(7, 3);
            SetFielderAct(3, 3);
        } else if (a > 0x440) {
            SetFielderAct(6, 3);
            SetFielderAct(7, 3);
            SetFielderAct(5, 3);
        } else {
            SetFielderAct(6, 3);
            SetFielderAct(7, 3);
            SetFielderAct(8, 3);
            dx = g_Fielders[(3)].x - g_Ball.landingSpotLocation.x;
            dz = g_Fielders[(3)].z - g_Ball.landingSpotLocation.z;
            dx = dx * dx;
            dz = dz * dz;
            d3 = dx + dz;
            SQRT_L(d3);
            dx = g_Fielders[(5)].x - g_Ball.landingSpotLocation.x;
            dz = g_Fielders[(5)].z - g_Ball.landingSpotLocation.z;
            dx = dx * dx;
            dz = dz * dz;
            d5 = dx + dz;
            SQRT_L(d5);
            if (g_Ball.landingSpotZoneAwayFromHome < 3 || !(g_Ball.maxYOfHit >= lbl_3_rodata_BD8)) {
                if (d3 < d5) {
                    SetFielderAct(3, 3);
                } else {
                    SetFielderAct(5, 3);
                }
            }
        }
    } else {
        fn_3_3FCF0(inf);
    }
done:
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}
#endif

// .text:0x00040C04 size:0x150 mapped:0x8067FC98
// 98%: temp regs in the two tail blocks (orig li r4,3 / lwz r0 / g in r5; ours li r0 / lwz r5 / g r4); same issue as fn_3_3F124
void fn_3_40C04(void) {
    int i;
    for (i = 2; i < 6; i++) {
        if (g_Fielders[i]._1DD == 2) {
            SetFielderAct(i, 3);
            break;
        }
    }
    if (i == 2) {
        SetFielderAct(3, 3);
    }
    if (i == 4) {
        SetFielderAct(5, 3);
    }
    fn_3_40D88();
}

// .text:0x00040D54 size:0x34 mapped:0x8067FDE8
void fn_3_40D54(void) {
    fn_3_49F40(6, 7);
    fn_3_49F40(8, 6);
}

// .text:0x00040D88 size:0x424 mapped:0x8067FE1C
void fn_3_40D88(void) {
    if (g_Fielders[8]._1DB == 0 && g_Fielders[6]._1DB == 0) {
        SetFielderAct(6, 3);
        SetFielderAct(7, 3);
        SetFielderAct(8, 3);
    } else if (g_Fielders[8]._1DB == 0) {
        SetFielderAct(8, 3);
        SetFielderAct(7, 3);
    } else if (g_Fielders[6]._1DB == 0) {
        SetFielderAct(6, 3);
        SetFielderAct(7, 3);
    } else if (g_Fielders[7]._1DB == 0) {
        SetFielderAct(6, 3);
        SetFielderAct(7, 3);
        SetFielderAct(8, 3);
    } else if (g_Fielders[7]._182 > g_Ball.Hit_HorizontalAngle) {
        SetFielderAct(8, 3);
        SetFielderAct(7, 3);
    } else {
        SetFielderAct(6, 3);
        SetFielderAct(7, 3);
    }
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_40D54();
}

// .text:0x000411AC size:0x628 mapped:0x80680240
// NONMATCHING 99.9%: registers only: the SetFielderAct r0/r4 swap and f1/f2 for dx*dx
#if NONMATCHING
// Start-of-play fielding setup: per-fielder angle/distance bookkeeping, then pick
// the covering scheme (fn_3_402A8 / fn_3_40C04 / fn_3_40D88 / fn_3_3F24C).
void fn_3_411AC(void) {
    int sh;
    int j;
    s64 mask = 0;
    InMemFielderView* f;
    int a;
    f32 d;
    f32 dx, dz;
    g_FieldingLogic._123 = 0;
    if (g_Scores.maxInnings <= g_Scores.inning && g_Scores._AD != 0 && g_Scores.team[0].runs[0] == g_Scores.team[1].runs[0] &&
        g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0 && g_Strikes.storedOuts <= 1 &&
        (g_RunningLogic.occupiedBases & 0x1000) && fn_3_B7E10(g_Ball.landingSpotLocation.x, g_Ball.landingSpotLocation.z) != 0 &&
        fn_3_B7D6C(g_Ball.landingSpotLocation.x, g_Ball.landingSpotLocation.z) == 0 && g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > lbl_3_rodata_C00) {
        g_FieldingLogic._123 = 1;
    }
    for (j = 0, sh = 0; j < 9; j++, sh += 3) {
        f = &g_Fielders[j];
        if (j == 1) {
            f->_182 = 0x400;
        } else if (0.0f == f->x) {
            f->_182 = 0x400;
        } else {
            a = lbl_3_rodata_BC4 * (f32)atan2(f->z, f->x) / lbl_3_rodata_BC8;
            if (a < 0) {
                a += 0x800;
            }
            f->_182 = a;
        }
        d = f->x * f->x + f->z * f->z;
        SQRT_L(d);
        f->_070 = d;
        dx = g_Ball.landingSpotLocation.x - f->x;
        dz = g_Ball.landingSpotLocation.z - f->z;
        dx = dx * dx;
        dz = dz * dz;
        d = dx + dz;
        SQRT_L(d);
        f->_080 = d;
        if (j == 1) {
            fn_3_4F504(1);
        } else {
            fn_3_4FB34(j);
        }
        if (f->_1DD == 1) {
            mask |= 4 << sh;
        } else if (f->_1DD == 2) {
            mask |= 2 << sh;
        } else if (f->_1DD == 3) {
            mask |= 1 << sh;
        }
    }
    if (g_Ball.lineDriveThroughPitcherInd != 0) {
        SetFielderAct(0, 0x14);
        if ((g_Fielders[(3)]._182 + g_Fielders[(5)]._182) / 2 > g_Ball.Hit_HorizontalAngle) {
            SetFielderAct(3, 3);
        } else {
            SetFielderAct(5, 3);
        }
        fn_3_4C9C8();
        fn_3_47778();
        fn_3_4A124();
    } else if (g_Ball.hitClassification3 == 7 || g_Ball.hitClassification3 == 8) {
        fn_3_3F24C();
    } else if ((mask & 0x3FFFF) == 0) {
        if (g_Ball.maxYOfHit < lbl_3_rodata_B8C) {
            fn_3_402A8();
        } else {
            fn_3_40D88();
        }
    } else if (mask & 0x2DB6D) {
        fn_3_402A8();
    } else if (mask & 0x12480) {
        fn_3_40C04();
    } else if (mask & 2) {
        fn_3_402A8();
    }
}
#endif

// .text:0x000417D4 size:0x1A8 mapped:0x80680868
void fn_3_417D4(int i) {
    int off = i * 0x268; // sizeof(InMemFielderView)
    InMemFielderView* f = (InMemFielderView*)((u8*)g_Fielders + off);
    InMemFielderView* g;
    f32 dx;
    f32 dz;
    f32 d;
    f32 a;
    f32 b;
    dx = g_Ball.physicsSubstruct.futureCoordsAndDist[0xa].pos.x - f->x;
    dz = g_Ball.physicsSubstruct.futureCoordsAndDist[0xa].pos.z - f->z;
    a = dx * dx;
    b = dz * dz;
    d = a + b;
    SQRT_L(d);
    if (d < lbl_3_rodata_C38 && f->_1DD == 2 && g_Ball.physicsSubstruct.futureCoordsAndDist[0xa].pos.y > f->reach[3]) {
        f->_198 = 0;
        g = FIELDERS;
        g = (InMemFielderView*)((u8*)g + off);
        g->_014 = f->x;
        g->_018 = f->y;
        g->_01C = f->z;
        g->_030 = lbl_3_rodata_B20;
        g->_034 = lbl_3_rodata_B20;
        g->_050 = lbl_3_rodata_B20;
        g->_068 = lbl_3_rodata_B20;
    }
}

// .text:0x0004197C size:0x3FC mapped:0x80680A10
// NONMATCHING 94.0%: register allocation and constant-load scheduling in the distance loop
#if NONMATCHING
// Pick the fielder closest to the ball's landing spot and send it after the ball.
// mode 1: a nearby fielder that is free takes it immediately.
void fn_3_4197C(int mode) {
    InMemFielderView* f;
    f32 best;
    f32 d;
    f32 e;
    f32 dx, dz;
    int j;
    int idx;
    s16 t;
    best = lbl_3_rodata_BA4;
    for (j = 0; j < 9; j++) {
        f = &g_Fielders[j];
        dx = g_Ball.physicsSubstruct.futureCoordsAndDist[0x5a].pos.x - f->x;
        dz = g_Ball.physicsSubstruct.futureCoordsAndDist[0x5a].pos.z - f->z;
        dx = dx * dx;
        dz = dz * dz;
        d = dx + dz;
        SQRT_L(d);
        e = d;
        if (mode == 1 && f->_19C != 0 && f->_1E0 != 1 && f->_1E0 != 2 && d < lbl_3_rodata_B78) {
            SetFielderAct(j, 0x12);
            fn_3_43038(j);
            return;
        }
        if (g_FieldingLogic._0F8[j] == 4) {
            e -= lbl_3_rodata_B78;
        }
        if (g_FieldingLogic._0F8[j] == 1) {
            if (best > e - lbl_3_rodata_B64) {
                best = e;
                idx = j;
            }
        } else if (best > e) {
            idx = j;
            best = e;
        }
    }
    f = &g_Fielders[idx];
    t = f->_18C;
    if (t != 0) {
        if (t >= 0 && t <= 3) {
            if (g_FieldingLogic._0D0[t] == idx) {
                g_FieldingLogic._0D0[t] = -1;
                g_FieldingLogic._101[t] = 0;
            }
            f->_18C = -1;
            f->_1D7 = 0;
            if (f->_1D3 == 1) {
                SetFielderAct(idx, 0xC);
            }
        } else if (t == 5) {
            f->_18C = -1;
            f->_1D7 = 0;
            g_FieldingLogic._0D8 = -1;
            g_FieldingLogic.playerAtMoundCutoffLocation = 0;
            if (f->_1D3 == 0xE) {
                SetFielderAct(idx, 0xC);
            }
        }
    }
    SetFielderAct(idx, 0x12);
    fn_3_43038(idx);
}
#endif

// .text:0x00041D78 size:0x304 mapped:0x80680E0C
// NONMATCHING 98.7%: second loop's counter/state registers swapped (orig inits counter with mr from busy)
#if NONMATCHING
// When no fielder is chasing the ball any more, pick one to go after it.
void fn_3_41D78(void) {
    int found = 0;
    int j;
    int busy;
    u8 st;
    f32 dx, dz, d, dx2, dz2;
    if (g_Ball.deadBallReason == 0 && g_Ball.AtBat_ContactResult != -1 && g_Ball.ballState != 1 && g_FieldingLogic._13F == 0) {
        if (g_Ball.ballState == 2) {
            if (g_Ball.framesUntilThrowReachesDest > 0 && g_Ball.fielderBeingThrownTo >= 0) {
                return;
            }
            dx = g_Ball.throwStartingLocation.x - g_Ball.AtBat_Contact_BallPos.x;
            dz = g_Ball.throwStartingLocation.z - g_Ball.AtBat_Contact_BallPos.z;
            dx2 = dx * dx;
            dz2 = dz * dz;
            d = dx2 + dz2;
            SQRT_L(d);
            if (!(d > lbl_3_rodata_B64 + g_Ball.throwDistance)) {
                return;
            }
        }
        for (j = 0; j < 9; j++) {
            if (g_FieldingLogic._0F8[j] == 1 || g_FieldingLogic._0F8[j] == 7) {
                found = 1;
                break;
            }
        }
        if (found == 0) {
            fn_3_4197C(0);
            return;
        }
        busy = 0;
        for (j = 0; j < 9; j++) {
            st = g_Fielders[j]._1D3;
            if (st == 2 || (u8)(st - 3) <= 1 || st == 0x12) {
                busy = 1;
                break;
            }
        }
        if (busy == 0) {
            fn_3_4197C(0);
        }
    }
}
#endif

// .text:0x0004207C size:0x7D4 mapped:0x80681110
// NONMATCHING 98.8%: loop constant/pointer setup order and one early-return shape; registers
#if NONMATCHING
// Infielder i decides whether to cover a base, relay, or back up (after a hit).
void fn_3_4207C(int i) {
    InMemFielderView* f = &g_Fielders[i];
    s16 t;
    int j;
    int k;
    InMemFielderView* g;
    if (g_Ball.deadBallReason != 0) {
        SetFielderAct(i, 0xC);
        return;
    }
    if (i <= 5) {
        if (g_Ball.ballState == 3) {
            if (g_Ball.ballZoneAwayFromHome > 2) {
                SetFielderAct(i, 0xB);
            }
            return;
        }
        t = g_Ball.AtBat_ContactResult;
        if (t == 1 && lbl_3_rodata_B60 + f->_070 < g_Ball.ballDistanceFromHome) {
            if (i == 0) {
                SetFielderAct(i, 9);
                return;
            }
            if (i != 1) {
                if (g_Ball.ballZoneAwayFromHome > 1) {
                    SetFielderAct(i, 0xB);
                    return;
                }
                SetFielderAct(i, 0xC);
                f->_1D5 = 4;
                return;
            }
        }
        if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > lbl_3_rodata_BD0 && f->_068 < lbl_3_rodata_BA0 && t == 0) {
            for (j = 6; j < 9; j++) {
                g = &g_Fielders[j];
                if (g->_1DB == 0 && g->_17E > 0 && f->_17E > g->_17E - 20) {
                    FielderGoCoverAC8(i);
                    return;
                }
            }
        }
        if (t == 0) {
            for (j = 0; j < 6; j++) {
                if (j != 1 && lbl_3_rodata_BA0 + f->_070 < g_Ball.ballDistanceFromHome) {
                    FielderGoCoverAC8(i);
                    return;
                }
            }
        }
    }
    for (j = 0; j < 9; j++) {
        if (j != i && g_FieldingLogic._0F8[j] == 1 && (&f->distToFielder[0])[j] < lbl_3_rodata_B78) {
            g = &g_Fielders[j];
            if (f->_17E < g->_17E) {
                g->_1D6 = 9;
                f->_1D6 = 0;
            } else {
                g->_1D6 = 0;
                f->_1D6 = 9;
            }
        }
    }
    k = g_Ball.fielderAboutToGetBall_hasBall;
    if (k == -1 || i == k) {
        return;
    }
    if (f->_1D7 == 1) {
        SetFielderAct(i, 1);
        g_FieldingLogic._0D0[f->_18C] = i;
    } else if (f->_18C == 6) {
        SetFielderAct(i, 0xB);
    } else if (i >= 6 || f->_070 > g_Fielders[k]._070) {
        if (f->_1C5 != 0) {
            SetFielderAct(i, 0xD);
        } else {
            SetFielderAct(i, 0x10);
        }
    } else {
        SetFielderAct(i, 0xC);
    }
}
#endif

// .text:0x00042850 size:0x1B0 mapped:0x806818E4
void fn_3_42850(int i) {
    InMemFielderView* f;
    f32 dz, d, bz, dx, bx, a2;
    bx = BALL->AtBat_Contact_BallPos.x;
    bz = BALL->AtBat_Contact_BallPos.z;
    f = &g_Fielders[i];
    f->_014 = bx;
    f->_01C = bz;
    dx = bx - f->x;
    dz = bz - f->z;
    if (0.0f == dx && 0.0f == dz) {
        f->_050 = 0.0f;
        f->_068 = 0.0f;
    } else {
        f->_064 = (f32)atan2(dz, dx);
        a2 = dz * dz;
        d = dx * dx + a2;
        SQRT_L(d);
        f->_068 = d;
    }
    f->_1D9 = 1;
}

// .text:0x00042A00 size:0x1D0 mapped:0x80681A94
void fn_3_42A00(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 dz;
    f32 dx;
    f32 d;
    CoordAndDist* b;
    f32 bx;
    f32 bz;
    // g_Ball shifted by _184 coordinates, so that futureCoordsAndDist[0] is entry _184
    b = (CoordAndDist*)&g_Ball;
    b += f->_184;
    bx = ((InMemBallType*)b)->physicsSubstruct.futureCoordsAndDist[0].pos.x;
    bz = ((InMemBallType*)b)->physicsSubstruct.futureCoordsAndDist[0].pos.z;
    f->_014 = bx;
    f->_01C = bz;
    dx = bx - f->x;
    dz = bz - f->z;
    if (0.0f == dx && 0.0f == dz) {
        f->_050 = 0.0f;
        f->_068 = 0.0f;
    } else {
        f->_064 = atan2(dz, dx);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        f->_068 = d;
    }
    f->_1D9 = 1;
    if (f->_184 <= 1) {
        f->_1DC = 5;
    }
}

// .text:0x00042BD0 size:0x10C mapped:0x80681C64
void fn_3_42BD0(int i) {
    InMemFielderView* f = &g_Fielders[i];
    InMemFielderView* o;
    int j;
    if (i >= 6 && g_Ball.ballState == 0) {
        if (f->_070 < g_Ball.ballDistanceFromHome) {
            fn_3_43038(i);
            return;
        }
        for (j = 6; j < 9; j++) {
            o = &g_Fielders[j];
            if (j != i && o->_1DC == 3 && o->_17E <= f->_17E && o->_17E < 0x5A) {
                fn_3_43038(i);
                return;
            }
        }
    }
}

// .text:0x00042CDC size:0x35C mapped:0x80681D70
// Fielder i heads for where the ball will be in 5 frames, or a spot picked by fn_3_50DD8.
void fn_3_42CDC(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 x;
    f32 z;
    f->_028 = lbl_3_rodata_B64 * g_Ball._19E4 + g_Ball.ballWillHitBallPos.x;
    f->_02C = lbl_3_rodata_B64 * g_Ball._19E8 + g_Ball.ballWillHitBallPos.z;
    if (f->_18A != 0) {
        f32 dz, dx, d;
        fn_3_50DD8(i, &x, &z, 1);
        f->_014 = x;
        f->_01C = z;
        dx = x - f->x;
        dz = z - f->z;
        if (0.0f == dx && 0.0f == dz) {
            f->_050 = 0.0f;
            f->_068 = 0.0f;
        } else {
            f->_064 = atan2(dz, dx);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            f->_068 = d;
        }
        f->_1D9 = 1;
        f->_020 = x;
        f->_024 = z;
    } else {
        f32 dz, dx, d, ox, oz;
        oz = f->_02C;
        ox = f->_028;
        f->_014 = ox;
        f->_01C = oz;
        dx = ox - f->x;
        dz = oz - f->z;
        if (0.0f == dx && 0.0f == dz) {
            f->_050 = 0.0f;
            f->_068 = 0.0f;
        } else {
            f->_064 = atan2(dz, dx);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            f->_068 = d;
        }
        f->_1D9 = 1;
    }
}

// .text:0x00043038 size:0x3A8 mapped:0x806820CC
// NONMATCHING 97.0%: float register allocation in the inlined fn_3_52560 distance code
#if NONMATCHING
// Send fielder i to the first point of the ball's flight (below catch height) it can reach in time.
void fn_3_43038(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int frames;
    int t;
    CoordAndDist* b;
    f->_1DC = 4;
    frames = 0;
    t = 5;
    while (t <= 0x78) {
        b = &g_Ball.physicsSubstruct.futureCoordsAndDist[t];
        if (b->pos.y > lbl_3_rodata_C08) {
            t++;
            continue;
        }
        frames = FramesToReachAC8(i, b->pos.x, b->pos.z);
        if (frames < t) {
            f->_184 = t;
            goto found;
        }
        t += 5;
    }
    f->_184 = 0x78;
found:
    b = &g_Ball.physicsSubstruct.futureCoordsAndDist[f->_184];
    SetTargetAC8(i, b->pos.x, b->pos.z);
    if (f->_184 >= 0x78) {
        f->_17E = 0x78;
    } else {
        f->_17E = frames;
    }
}
#endif

// .text:0x000433E0 size:0x13E4 mapped:0x80682474
// NONMATCHING 94.4%: switch lowered as compare chain in a different order, lfsx trajectory loads, and set-target float registers
#if NONMATCHING
// Per-frame update of a fielder chasing the ball: pick the target by chase mode (0x1DC) and run there.
void fn_3_433E0(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 x;
    f32 z;
    f32 d, r, px, pz;
    int t;
    int n;
    if (g_Ball.ballBounceState == 3) {
        fn_3_43038(i);
    }
    if (g_Ball.ballVelocity < lbl_3_rodata_B7C && g_Ball.ballState != 0 && g_Ball.ballState != 1) {
        if (g_Ball.AtBat_ContactResult != 0) {
            f->_1DC = 5;
        }
    } else if (g_Ball.ballVelocity < lbl_3_rodata_B24 && g_Ball.ballZoneAwayFromHome >= 3 && g_Ball.AtBat_ContactResult >= 1 &&
               g_Ball.AtBat_ContactResult <= 3 && f->_1DC != 4 && f->_1DC != 5) {
        fn_3_43038(i);
    } else if (g_FieldingLogic._107 == 3 && g_Ball.framesSinceHit <= 0xB4 && i == 1 && f->_1DC != 4) {
        fn_3_43038(i);
    }
    if (g_Ball.pauseBallMovementWhenInPlant != 0) {
        // Ball already close to the ground near the fielder: step towards it.
        x = g_Ball.AtBat_Contact_BallPos.x - f->x;
        z = g_Ball.AtBat_Contact_BallPos.z - f->z;
        {
            f32 a = x * x;
            f32 b = z * z;
            d = a + b;
            SQRT_L(d);
        }
        r = lbl_3_data_4930[36];
        if (d < r) {
            f32 dz, dx, dd, ox, oz;
            oz = f->z;
            ox = f->x;
            f->_014 = ox;
            f->_01C = oz;
            dx = ox - f->x;
            dz = oz - f->z;
            if (0.0f == dx && 0.0f == dz) {
                f->_050 = 0.0f;
                f->_068 = 0.0f;
            } else {
                f->_064 = atan2(dz, dx);
                dd = dx * dx + dz * dz;
                SQRT_L(dd);
                f->_068 = dd;
            }
            f->_1D9 = 1;
        } else {
            r = r - lbl_3_rodata_B60;
            x = r * (x / d) + f->x;
            z = r * (z / d) + f->z;
            SetTargetAC8(i, x, z);
        }
    } else if (g_FieldingLogic._123 != 0) {
        // Ball heading over the fence: go to the wall below its path.
        t = f->_184;
        if (t > 1) {
            px = g_Ball.physicsSubstruct.futureCoordsAndDist[t].pos.x;
            pz = g_Ball.physicsSubstruct.futureCoordsAndDist[t].pos.z;
            d = px * px + pz * pz;
            SQRT_L(d);
            px = g_Ball.physicsSubstruct.futureCoordsAndDist[f->_184].pos.x;
            pz = g_Ball.physicsSubstruct.futureCoordsAndDist[f->_184].pos.z;
            x = lbl_3_rodata_B80 * (px / d) + px;
            z = lbl_3_rodata_B80 * (pz / d) + pz;
            if (x < 0.0f) {
                x = x + lbl_3_rodata_BA0;
            } else {
                x = x - lbl_3_rodata_BA0;
            }
            z = z + lbl_3_rodata_BD8;
            SetTargetAC8(i, x, z);
        }
    } else {
        switch (f->_1DC) {
        case 0:
            if (f->_184 > 1) {
                if (f->_18A != 0) {
                    fn_3_50DD8(i, &x, &z, 1);
                    f->_020 = x;
                    f->_024 = z;
                } else {
                    t = f->_184;
                    px = g_Ball.physicsSubstruct.futureCoordsAndDist[t].pos.x;
                    pz = g_Ball.physicsSubstruct.futureCoordsAndDist[t].pos.z;
                    d = px * px + pz * pz;
                    SQRT_L(d);
                    px = g_Ball.physicsSubstruct.futureCoordsAndDist[f->_184].pos.x;
                    pz = g_Ball.physicsSubstruct.futureCoordsAndDist[f->_184].pos.z;
                    x = lbl_3_rodata_B80 * (px / d) + px;
                    z = lbl_3_rodata_B80 * (pz / d) + pz;
                    if (g_Ball.warioWaluGarlicIsActive != 0) {
                        if (g_AiLogic._79[0] != 0) {
                            x = g_Ball.peachDaisyStarHitFielderLoc.x;
                            z = g_Ball.peachDaisyStarHitFielderLoc.z;
                        } else {
                            x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
                            z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
                        }
                    } else if (g_Ball.autoFielderAvoidDropSpotForPeachesStarHit != 0) {
                        x = g_Ball.peachDaisyStarHitFielderLoc.x;
                        z = g_Ball.peachDaisyStarHitFielderLoc.z;
                    }
                }
                SetTargetAC8(i, x, z);
            } else {
                f->_1DC = 5;
            }
            if (i >= 6 && g_Ball.ballState == 0 && f->_184 < -5) {
                fn_3_43038(i);
            }
            break;
        case 1:
            f->_028 = g_Ball.ballWillHitBallPos.x;
            f->_02C = g_Ball.ballWillHitBallPos.z;
            if (f->_18A != 0) {
                fn_3_50DD8(i, &x, &z, 1);
                SetTargetAC8(i, x, z);
                f->_020 = x;
                f->_024 = z;
            } else {
                f32 dz, dx, dd, ox, oz;
                oz = f->_02C;
                ox = f->_028;
                f->_014 = ox;
                f->_01C = oz;
                dx = ox - f->x;
                dz = oz - f->z;
                if (0.0f == dx && 0.0f == dz) {
                    f->_050 = 0.0f;
                    f->_068 = 0.0f;
                } else {
                    f->_064 = atan2(dz, dx);
                    dd = dx * dx + dz * dz;
                    SQRT_L(dd);
                    f->_068 = dd;
                }
                f->_1D9 = 1;
            }
            break;
        case 2:
            fn_3_42CDC(i);
            break;
        case 3:
            fn_3_42BD0(i);
            break;
        case 4:
            t = f->_184;
            SetTargetAC8(i, g_Ball.physicsSubstruct.futureCoordsAndDist[t].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[t].pos.z);
            if (f->_184 <= 1) {
                f->_1DC = 5;
            }
            break;
        case 5:
            SetTargetAC8(i, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z);
            break;
        }
    }
    f->_184 = f->_184 - 1;
    fn_3_526DC(i);
    if (0.0f != f->_050) {
        f->_17E = f->_068 / f->_050;
    }
    if ((f->_1DC == 1 || f->_1DC == 2 || f->_1DC == 3) && g_Ball.AtBat_ContactResult == 0) {
        n = FramesToReachAC8(i, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
        if (g_Ball.framesUntilBallHitsGround > n) {
            f->_1DC = 0;
            f->_184 = g_Ball.framesUntilBallHitsGround - 2;
        }
    }
}
#endif

// .text:0x000447C4 size:0xBD0 mapped:0x80683858
// NONMATCHING 98.3%: float register choice in the set-target blocks and t*16 kept in r31 by orig for the traj[t+30] read
#if NONMATCHING
// Fielder i chases a batted ball: pick a target on the ball's path (or the throw line) and run there.
void fn_3_447C4(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int t;
    int mg = 0;
    CoordAndDist* e;
    f32 px, pz, dP, dL, d, k;
    f32 x;
    f32 z;
    t = f->_186 - g_Ball.framesSinceHit + 1;
    if (t < 0) {
        t *= -1;
    }
    if (t >= 0x168) {
        t = 0x167;
    }
    e = &g_Ball.physicsSubstruct.futureCoordsAndDist[t];
    px = e->pos.x;
    pz = e->pos.z;
    if (g_Ball.warioWaluGarlicIsActive != 0) {
        if (g_AiLogic._79[0] != 0) {
            px = g_Ball.peachDaisyStarHitFielderLoc.x;
            pz = g_Ball.peachDaisyStarHitFielderLoc.z;
        } else {
            px = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            pz = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        }
    } else if (g_Ball.autoFielderAvoidDropSpotForPeachesStarHit != 0) {
        px = g_Ball.peachDaisyStarHitFielderLoc.x;
        pz = g_Ball.peachDaisyStarHitFielderLoc.z;
    }
    if (g_d_GameSettings.minigamesEnabled != 0 && i >= 2) {
        mg = 1;
    }
    if (i >= 6 || mg != 0) {
        dP = px * px + pz * pz;
        SQRT_L(dP);
        if (g_Ball._1BC0 != 0 && g_Ball.someCollisionInd == 0) {
            {
                f32 a = g_Ball.ballWillHitBallPos.x * g_Ball.ballWillHitBallPos.x;
                f32 b = g_Ball.ballWillHitBallPos.z * g_Ball.ballWillHitBallPos.z;
                dL = a + b;
                SQRT_L(dL);
            }
            if (g_Ball.someCollisionVariable >= 2) {
                x = f->x - g_Ball.ballWillHitBallPos.x;
                z = f->z - g_Ball.ballWillHitBallPos.z;
                {
                    f32 a = x * x;
                    f32 b = z * z;
                    d = a + b;
                    SQRT_L(d);
                }
                k = lbl_3_rodata_B64 / d;
                x = x * k + g_Ball.ballWillHitBallPos.x;
                z = z * k + g_Ball.ballWillHitBallPos.z;
                f->_028 = x;
                f->_02C = z;
                fn_3_50C20(i, &x, &z);
                f->_1DC = 2;
                goto tail;
            }
            if (dP > dL) {
                if (f->_1DD != 1 || (f->_1C5 != 0 && f->aiLevel >= 3)) {
                    x = lbl_3_rodata_B64 * g_Ball._19E4 + g_Ball.ballWillHitBallPos.x;
                    z = lbl_3_rodata_B64 * g_Ball._19E8 + g_Ball.ballWillHitBallPos.z;
                    f->_028 = x;
                    f->_02C = z;
                    fn_3_50C20(i, &x, &z);
                    f->_1DC = 2;
                } else {
                    x = g_Ball.ballWillHitBallPos.x;
                    z = g_Ball.ballWillHitBallPos.z;
                    f->_028 = x;
                    f->_02C = z;
                    fn_3_50C20(i, &x, &z);
                    f->_1DC = 1;
                }
                {
                    f32 dz, dx, dd;
                    f->_014 = x;
                    f->_01C = z;
                    dx = x - f->x;
                    dz = z - f->z;
                    if (0.0f == dx && 0.0f == dz) {
                        f->_050 = 0.0f;
                        f->_068 = 0.0f;
                    } else {
                        f->_064 = atan2(dz, dx);
                        dd = dx * dx + dz * dz;
                        SQRT_L(dd);
                        f->_068 = dd;
                    }
                    f->_1D9 = 1;
                }
                goto tail;
            }
        }
        if (f->_1DD == 3 || f->_1DD == 4) {
            if (fn_3_B7E44(g_Ball.ballAngleFromHome, dP) != 0) {
                x = lbl_3_rodata_B64 * g_Ball._19E4 + g_Ball.ballWillHitBallPos.x;
                z = lbl_3_rodata_B64 * g_Ball._19E8 + g_Ball.ballWillHitBallPos.z;
                f->_028 = x;
                f->_02C = z;
                fn_3_50C20(i, &x, &z);
                f->_1DC = 2;
            } else {
                x = g_Ball.physicsSubstruct.futureCoordsAndDist[t + 0x1e].pos.x;
                z = g_Ball.physicsSubstruct.futureCoordsAndDist[t + 0x1e].pos.z;
                f->_028 = x;
                f->_02C = z;
                fn_3_50C20(i, &x, &z);
                f->_1DC = 3;
            }
            SetTargetAC8(i, x, z);
            goto tail;
        }
    }
    d = px * px + pz * pz;
    SQRT_L(d);
    if (d <= lbl_3_rodata_B24) {
        x = px;
        z = pz;
    } else {
        x = lbl_3_rodata_B80 * (px / d) + px;
        z = lbl_3_rodata_B80 * (pz / d) + pz;
    }
    if (g_Ball.warioWaluGarlicIsActive == 0 && g_Ball.currentStarSwing != 9 && g_Ball.currentStarSwing != 10 && g_Ball.someCollisionInd == 0 && g_Ball.numFieldersWhoHandledBallDuringPlay == 0) {
        fn_3_50DD8(i, &x, &z, 0);
    }
    SetTargetAC8(i, x, z);
    f->_1DC = 0;
tail:
    f->_020 = f->_014;
    f->_024 = f->_01C;
    fn_3_526DC(i);
    f->_184 = t;
}
#endif

// .text:0x00045394 size:0x220 mapped:0x80684428
void fn_3_45394(int i) {
    InMemFielderView* f = &g_Fielders[i];
    GameInitVariables* gs;
    if (g_FieldingLogic._107 == 3 && g_Ball.framesSinceHit < 0x91 && i == 1) {
        return;
    }
    if (g_Ball.framesSinceHit <= 0) {
        return;
    }
    if (f->_1DF != 0) {
        s16 t = f->_194;
        if (t < 0x7FFE) {
            f->_194 = t + 1;
        } else {
            f->_194 = 0x7FFF;
        }
        if (f->_194 < f->_196) {
            if (g_Ball.ballState == 1) {
                f->_194 = f->_196;
            }
            return;
        }
        f->_194 = 0;
        f->_1DF = 0;
    }
    switch (fn_3_53130(i)) {
    case 2:
        return;
    default:
        if (f->_1ED == 0) {
            fn_3_433E0(i);
        }
        gs = &g_d_GameSettings;
        if (gs->minigamesEnabled == 0) {
            fn_3_4207C(i);
        }
        if (gs->minigamesEnabled != 0) {
            if (g_Ball.deadBallReason != 0 && i != -1) {
                f->_1D3 = 0xC;
                if (lbl_3_data_3C40[12].anim >= 0) {
                    g_FieldingLogic._0F8[i] = lbl_3_data_3C40[12].anim;
                }
                f->_1D5 = 0;
                f->_1D6 = 0;
                f->_1A4 = 0;
                f->_1AC = 0;
                f->_1FF = 0;
            }
            break;
        }
    case 1:
        if (g_Ball.deadBallReason != 0) {
            if (i != -1) {
                f->_1D3 = 0xC;
                if (lbl_3_data_3C40[12].anim >= 0) {
                    g_FieldingLogic._0F8[i] = lbl_3_data_3C40[12].anim;
                }
                f->_1D5 = 0;
                f->_1D6 = 0;
                f->_1A4 = 0;
                f->_1AC = 0;
                f->_1FF = 0;
            }
        } else {
            fn_3_5372C(i);
        }
        break;
    }
}

// .text:0x000455B4 size:0x2AC mapped:0x80684648
void fn_3_455B4(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 a, b, d, a2, b2;
    s16 n = g_Ball.framesSinceHit;
    if (n >= f->_1D2) {
        if (fn_3_53130(i) == 0) {
            fn_3_447C4(i);
            a = f->_014;
            b = f->_01C;
            a2 = a * a;
            b2 = b * b;
            d = a2 + b2;
            SQRT_L(d);
            if (d > lbl_3_rodata_B9C) {
                FIELDERS->_014 = FIELDERS->x;
                FIELDERS->_018 = FIELDERS->y;
                FIELDERS->_01C = FIELDERS->z;
                FIELDERS->_030 = lbl_3_rodata_B20;
                FIELDERS->_034 = lbl_3_rodata_B20;
                FIELDERS->_050 = lbl_3_rodata_B20;
                FIELDERS->_068 = lbl_3_rodata_B20;
                if (i != -1) {
                    f->_1D3 = 9;
                    if (lbl_3_data_3C40[9].anim >= 0) {
                        g_FieldingLogic._0F8[i] = lbl_3_data_3C40[9].anim;
                    }
                    f->_1D5 = 0;
                    f->_1D6 = 0;
                    f->_1A4 = 0;
                    f->_1AC = 0;
                    f->_1FF = 0;
                }
            } else {
                fn_3_45394(i);
                if (f->_1C5 != 0) {
                    if (i != -1) {
                        f->_1D3 = 2;
                        if (lbl_3_data_3C40[2].anim >= 0) {
                            g_FieldingLogic._0F8[i] = lbl_3_data_3C40[2].anim;
                        }
                        f->_1D5 = 0;
                        f->_1D6 = 0;
                        f->_1A4 = 0;
                        f->_1AC = 0;
                        f->_1FF = 0;
                    }
                } else if (i != -1) {
                    f->_1D3 = 0x10;
                    if (lbl_3_data_3C40[16].anim >= 0) {
                        g_FieldingLogic._0F8[i] = lbl_3_data_3C40[16].anim;
                    }
                    f->_1D5 = 0;
                    f->_1D6 = 0;
                    f->_1A4 = 0;
                    f->_1AC = 0;
                    f->_1FF = 0;
                }
            }
        }
    }
}

// .text:0x00045860 size:0x11C mapped:0x806848F4
void fn_3_45860(int i) {
    InMemFielderView* f = &g_Fielders[i];
    s16 n = g_Ball.framesSinceHit;
    if (n >= f->_1D2) {
        if (fn_3_53130(i) == 0) {
            fn_3_447C4(i);
            fn_3_45394(i);
            if (f->_1C5 != 0) {
                if (i != -1) {
                    f->_1D3 = 2;
                    if (lbl_3_data_3C40[2].anim >= 0) {
                        g_FieldingLogic._0F8[i] = lbl_3_data_3C40[2].anim;
                    }
                    f->_1D5 = 0;
                    f->_1D6 = 0;
                    f->_1A4 = 0;
                    f->_1AC = 0;
                    f->_1FF = 0;
                }
            } else if (i != -1) {
                f->_1D3 = 0x10;
                if (lbl_3_data_3C40[16].anim >= 0) {
                    g_FieldingLogic._0F8[i] = lbl_3_data_3C40[16].anim;
                }
                f->_1D5 = 0;
                f->_1D6 = 0;
                f->_1A4 = 0;
                f->_1AC = 0;
                f->_1FF = 0;
            }
        }
    }
}

// .text:0x0004597C size:0x20C mapped:0x80684A10
// Move fielder i to the point on the ball's travel line closest to it.
void fn_3_4597C(int i) {
    InMemFielderView* f = &g_Fielders[i];
    VecXZ out;
    VecXZ line[2];
    VecXZ perp[2];
    f32 dz, dx, d;
    f32 lx, lz, ox, oz;
    line[0].x = g_Ball.AtBat_Contact_BallPos.x;
    line[0].z = g_Ball.AtBat_Contact_BallPos.z;
    line[1].x = g_Ball.throwTarget.x;
    line[1].z = g_Ball.throwTarget.z;
    perp[0].x = f->x;
    perp[0].z = f->z;
    lx = line[1].x - line[0].x;
    lz = -(line[1].z - line[0].z);
    perp[1].x = perp[0].x + lz;
    perp[1].z = perp[0].z + lx;
    calculateLineIntersection(&out, line, perp);
    ox = out.x;
    oz = out.z;
    f->_014 = ox;
    f->_01C = oz;
    dx = ox - f->x;
    dz = oz - f->z;
    if (0.0f == dx && 0.0f == dz) {
        f->_050 = 0.0f;
        f->_068 = 0.0f;
    } else {
        f->_064 = atan2(dz, dx);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        f->_068 = d;
    }
    f->_1D9 = 1;
}

// .text:0x00045B88 size:0x310 mapped:0x80684C1C
// Fielder i runs to cut off the ball's travel line, then hands over to the normal chase.
void fn_3_45B88(int i) {
    InMemFielderView* f = &g_Fielders[i];
    VecXZ out;
    VecXZ perp[2];
    VecXZ line[2];
    f32 dz, dx, d;
    f32 lx, lz;
    g_FieldingLogic._13C = 0;
    if (f->_1FF == 0) {
        f->_1FF = 1;
        f->_202 = 1;
        g_FieldingLogic._0B0 = i;
        line[0].x = g_Ball.AtBat_Contact_BallPos.x;
        line[0].z = g_Ball.AtBat_Contact_BallPos.z;
        line[1].x = g_Ball.throwTarget.x;
        line[1].z = g_Ball.throwTarget.z;
        perp[0].x = f->x;
        perp[0].z = f->z;
        lx = line[1].x - line[0].x;
        lz = -(line[1].z - line[0].z);
        perp[1].x = perp[0].x + lz;
        perp[1].z = perp[0].z + lx;
        calculateLineIntersection(&out, line, perp);
        f->_014 = out.x;
        f->_01C = out.z;
        dx = out.x - f->x;
        dz = out.z - f->z;
        if (0.0f == dx && 0.0f == dz) {
            f->_050 = 0.0f;
            f->_068 = 0.0f;
        } else {
            f->_064 = atan2(dz, dx);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            f->_068 = d;
        }
        f->_1D9 = 1;
    }
    switch (fn_3_53130(i)) {
    case 2:
        return;
    default:
        if (f->_202 != 0) {
            fn_3_526DC(i);
            if (g_FieldingLogic.padButtons[1] & 0x100) {
                g_FieldingLogic._13C = 1;
            }
        }
    case 1:
        if (g_Ball.ballState != 2) {
            g_FieldingLogic._0C2 = -1;
            f->_202 = 0;
            SetFielderAct(i, 9);
        }
        break;
    }
}

// .text:0x00045E98 size:0x7F0 mapped:0x80684F2C
// NONMATCHING 86.7%: orig unrolls the 9-fielder relay-reset loop 3x (ours stays rolled) and keeps the candidate array in a pointer; logic follows the asm
#if NONMATCHING
// Pick a relay (cutoff) fielder between the ball chaser and the infield.
void fn_3_45E98(void) {
    int j;
    int k;
    int n;
    int ok = 0;
    int best;
    u8 st;
    InMemFielderView* g;
    int cand[3];
    f32 bx, bz, d, bestD, px, pz;
    if (g_FieldingLogic._0C0 != 0) {
        g_FieldingLogic._0C0 -= 1;
    }
    if (g_FieldingLogic._0C4 == 6) {
        return;
    }
    if (g_Ball.fielderWBallIndex == g_FieldingLogic._0BE) {
        g_FieldingLogic._0BE = -1;
    }
    if (g_FieldingLogic._0BE == -1) {
        if (g_FieldingLogic._0C4 >= 0) {
            return;
        }
        for (j = 0; j < 9; j++) {
            if (g_Fielders[j]._18C == 6) {
                st = g_Fielders[j]._1D3;
                if (st == 2 || (u8)(st - 15) <= 1 || (u8)(st - 21) <= 2 || st == 12 || st == 0) {
                    g_Fielders[j]._18C = -1;
                } else {
                    return;
                }
            }
        }
        if (g_Ball.ballZoneAwayFromHome >= 3) {
            ok = 1;
        } else {
            if (g_Ball.ballZoneAwayFromHome <= 1) {
                return;
            }
            if (g_Ball.fielderWBallIndex >= 0) {
                return;
            }
            if (g_Ball.ballState == 0 && g_Ball.ballZoneAwayFromHome >= 2) {
                ok = 1;
            }
            for (j = 0; j < 6; j++) {
                if (g_FieldingLogic._0F8[j] == 1 || g_FieldingLogic._0F8[j] == 10) {
                    break;
                }
            }
            if (j == 6) {
                for (j = 6; j < 9; j++) {
                    if (g_FieldingLogic._0F8[j] == 1 || g_FieldingLogic._0F8[j] == 10) {
                        break;
                    }
                }
                if (j <= 8) {
                    ok = 1;
                }
            }
        }
        if (ok == 0 || g_FieldingLogic._0C0 != 0) {
            return;
        }
        cand[0] = cand[1] = cand[2] = -1;
        n = 0;
        for (j = 2; j < 6; j++) {
            st = g_FieldingLogic._0F8[j];
            if ((st == 0 || st == 8 || st == 9) && g_Fielders[j]._1ED == 0) {
                cand[n++] = j;
            }
            if (n == 3) {
                break;
            }
        }
        if (n <= 0) {
            return;
        }
        bx = lbl_3_rodata_BD0 * g_Ball.AtBat_Contact_BallPos.x / g_Ball.ballDistanceFromHome;
        bz = lbl_3_rodata_BD0 * g_Ball.AtBat_Contact_BallPos.z / g_Ball.ballDistanceFromHome;
        bestD = 0.0f;
        best = cand[0];
        for (k = 0; k < 3; k++) {
            if (cand[k] < 0) {
                continue;
            }
            g = &g_Fielders[cand[k]];
            {
                f32 dx = g->x - bx;
                f32 dz = g->z - bz;
                dx = dx * dx;
                dz = dz * dz;
                d = dx + dz;
                SQRT_L(d);
            }
            if (k == 0) {
                bestD = d;
            } else if (d < bestD) {
                bestD = d;
                best = cand[k];
            }
        }
        SetFielderAct(best, 0xB);
        g_FieldingLogic._146 = lbl_3_data_49DC[0x2B];
        return;
    }
    if (g_FieldingLogic._146 != 0) {
        return;
    }
    k = g_FieldingLogic._0BE;
    px = g_Fielders[k]._014;
    pz = g_Fielders[k]._01C;
    for (j = 2; j < 6; j++) {
        if (k == j) {
            continue;
        }
        st = g_FieldingLogic._0F8[j];
        g = &g_Fielders[j];
        if ((st == 0 || st == 8 || st == 9) && g->_1ED == 0) {
            {
                f32 dx = px - g->x;
                f32 dz = pz - g->z;
                dx = dx * dx;
                dz = dz * dz;
                d = dx + dz;
                SQRT_L(d);
            }
            if (d < g_Fielders[g_FieldingLogic._0BE]._068) {
                SetFielderAct(j, 0xB);
                g_FieldingLogic._146 = lbl_3_data_49DC[0x2B];
                return;
            }
        }
    }
}
#endif

// .text:0x00046688 size:0x254 mapped:0x8068571C
int fn_3_46688(f32* x, f32* z) {
    InMemFielderView* f = &g_Fielders[g_FieldingLogic._0B0];
    f32 dx, dz, d, t, a2, b2;
    if (g_Ball.fielderWBallIndex >= 0) {
        *x = g_Ball.AtBat_Contact_BallPos.x;
        *z = g_Ball.AtBat_Contact_BallPos.z;
    } else if (g_Ball.ballState == 2) {
        *x = g_Ball.throwStartingLocation.x;
        *z = g_Ball.deadballLastLoc.x;
    } else if (g_Ball.fielderAboutToGetBall_hasBall >= 0) {
        *x = g_Fielders[g_Ball.fielderAboutToGetBall_hasBall].x;
        *z = g_Fielders[g_Ball.fielderAboutToGetBall_hasBall].z;
    } else if (g_Ball.AtBat_ContactResult == 0) {
        *x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
        *z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
    } else {
        dx = g_Ball.AtBat_Contact_BallPos.x - f->x;
        dz = g_Ball.AtBat_Contact_BallPos.z - f->z;
        a2 = dx * dx;
        b2 = dz * dz;
        d = a2 + b2;
        SQRT_L(d);
        if (lbl_3_rodata_B20 == d) {
            *x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            *z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        } else if (g_Ball.ballVelocity <= lbl_3_rodata_B48) {
            *x = g_Ball.AtBat_Contact_BallPos.x;
            *z = g_Ball.AtBat_Contact_BallPos.z;
        } else {
            t = d / g_Ball.ballVelocity;
            *x = g_Ball.physicsSubstruct.velocity.x * t + g_Ball.AtBat_Contact_BallPos.x;
            *z = g_Ball.physicsSubstruct.velocity.z * t + g_Ball.AtBat_Contact_BallPos.z;
        }
    }
    return 1;
}

// .text:0x000468DC size:0x1E0 mapped:0x80685970
int fn_3_468DC(f32* x, f32* z) {
    if (g_Ball.fielderWBallIndex >= 0) {
        *x = g_Ball.AtBat_Contact_BallPos.x;
        *z = g_Ball.AtBat_Contact_BallPos.z;
    } else if (g_Ball.fielderAboutToGetBall_hasBall >= 0) {
        *x = g_Fielders[g_Ball.fielderAboutToGetBall_hasBall]._014;
        *z = g_Fielders[g_Ball.fielderAboutToGetBall_hasBall]._01C;
    } else if (g_FieldingLogic._0F8[7] == 1) {
        if (g_FieldingLogic._0F8[8] == 1) {
            s16 a = g_Fielders[7]._17E;
            if (a == -1 || g_Fielders[8]._17E == -1) {
                return 0;
            }
            if (a < g_Fielders[8]._17E) {
                *x = g_Fielders[7]._014;
                *z = g_Fielders[7]._01C;
            } else {
                *x = g_Fielders[8]._014;
                *z = g_Fielders[8]._01C;
            }
        } else if (g_FieldingLogic._0F8[6] == 1) {
            s16 a = g_Fielders[7]._17E;
            if (a == -1 || g_Fielders[6]._17E == -1) {
                return 0;
            }
            if (a < g_Fielders[6]._17E) {
                *x = g_Fielders[7]._014;
                *z = g_Fielders[7]._01C;
            } else {
                *x = g_Fielders[6]._014;
                *z = g_Fielders[6]._01C;
            }
        } else {
            if (g_Fielders[7]._17E == -1) {
                return 0;
            }
            *x = g_Fielders[7]._014;
            *z = g_Fielders[7]._01C;
        }
    } else if (g_FieldingLogic._0F8[8] == 1) {
        if (g_Fielders[8]._17E == -1) {
            return 0;
        }
        *x = g_Fielders[8]._014;
        *z = g_Fielders[8]._01C;
    } else {
        if (g_Fielders[6]._17E == -1) {
            return 0;
        }
        *x = g_Fielders[6]._014;
        *z = g_Fielders[6]._01C;
    }
    return 1;
}

// .text:0x00046ABC size:0x34C mapped:0x80685B50
// NONMATCHING 97.7%: float register coloring of the predicted ball position (orig keeps x/z in f0/f7)
#if NONMATCHING
// Fielder i follows the batted ball along its path at its own reach distance (0x74).
void fn_3_46ABC(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 t, px, pz, ex, ez, e;
    f32 dz, dx, d;
    if (g_Ball.framesSinceThrowStarted == 5 && g_Ball.ballVelocity != 0.0f) {
        t = f->_074 / g_Ball.ballVelocity;
        px = g_Ball.physicsSubstruct.velocity.x * t + g_Ball.AtBat_Contact_BallPos.x;
        pz = g_Ball.physicsSubstruct.velocity.z * t + g_Ball.AtBat_Contact_BallPos.z;
        ex = f->x - px;
        ez = f->z - pz;
        ex = ex * ex;
        ez = ez * ez;
        e = ex + ez;
        SQRT_L(e);
        if (e > f->reach[0]) {
            f->_1E9 = 1;
            f->_014 = px;
            f->_01C = pz;
            dx = px - f->x;
            dz = pz - f->z;
            if (0.0f == dx && 0.0f == dz) {
                f->_050 = 0.0f;
                f->_068 = 0.0f;
            } else {
                f->_064 = atan2(dz, dx);
                d = dx * dx + dz * dz;
                SQRT_L(d);
                f->_068 = d;
            }
            f->_1D9 = 1;
        }
    }
    fn_3_526DC(i);
    if (f->_1E9 != 0 && f->_050 == 0.0f) {
        f->_1E9 = 0;
    }
    if (g_Ball.fielderBeingThrownTo == i) {
        fn_3_4E638();
    }
}
#endif

// .text:0x00046E08 size:0x820 mapped:0x80685E9C
#pragma opt_unroll_loops off
// NONMATCHING 97.2%: the 3-base loop is a pointer-compare loop here (orig uses ctr); float regs. Constants are block locals so stores through outX/outZ don't force reloads
#if NONMATCHING
// Where should fielder i stand to cover its base (0x18E)? Writes the spot to outX/outZ.
int fn_3_46E08(int i, f32* outX, f32* outZ) {
    InMemFielderView* f = &g_Fielders[i];
    int inBase = 0;
    int j;
    s16 k;
    InMemFielderView* g;
    f32 x;
    f32 z;
    f32 bx, bz, d, s;
    f32* b;
    f32 r5;
    if (f->_1C5 != 0) {
        if (fn_3_468DC(&x, &z) == 0) {
            return 0;
        }
    } else {
        g = &g_Fielders[g_FieldingLogic._0B0];
        if (g_Ball.fielderWBallIndex >= 0) {
            x = g_Ball.AtBat_Contact_BallPos.x;
            z = g_Ball.AtBat_Contact_BallPos.z;
        } else if (g_Ball.ballState == 2) {
            x = g_Ball.throwStartingLocation.x;
            z = g_Ball.deadballLastLoc.x;
        } else if ((k = g_Ball.fielderAboutToGetBall_hasBall) >= 0) {
            x = g_Fielders[k].x;
            z = (&g_Fielders[0].z)[k * 0x9A];
        } else if (g_Ball.AtBat_ContactResult == 0) {
            x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        } else {
            f32 dx = g_Ball.AtBat_Contact_BallPos.x - g->x;
            f32 dz = g_Ball.AtBat_Contact_BallPos.z - g->z;
            dx = dx * dx;
            dz = dz * dz;
            d = dx + dz;
            SQRT_L(d);
            if (0.0f == d) {
                x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
                z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
            } else if (g_Ball.ballVelocity <= lbl_3_rodata_B48) {
                x = g_Ball.AtBat_Contact_BallPos.x;
                z = g_Ball.AtBat_Contact_BallPos.z;
            } else {
                d = d / g_Ball.ballVelocity;
                x = g_Ball.physicsSubstruct.velocity.x * d + g_Ball.AtBat_Contact_BallPos.x;
                z = g_Ball.physicsSubstruct.velocity.z * d + g_Ball.AtBat_Contact_BallPos.z;
            }
        }
    }
    bx = lbl_3_data_4444[f->_18E * 2];
    bz = (lbl_3_data_4444 + 1)[f->_18E * 2];
    switch (f->_18E) {
    case 0: {
        f32 c = lbl_3_rodata_C3C;
        f32 m = lbl_3_rodata_B8C;
        f32 r;
        *outX = m * (x / c);
        *outZ = m * (z / c);
        d = *outX * *outX + *outZ * *outZ;
        SQRT_L(d);
        r = lbl_3_rodata_C40;
        if (d > r) {
            s = d / r;
            if (s > lbl_3_rodata_B60) {
                *outX = *outX / s;
                *outZ = *outZ / s;
            }
        }
        break;
    }
    case 1:
        {
            f32 kk = lbl_3_rodata_B80;
            *outX = (x - bx) * kk + bx;
            *outZ = (z - bz) * kk + bz;
        }
        break;
    case 2:
        {
            f32 kk = lbl_3_rodata_B74;
            *outX = (x - bx) * kk + bx;
            *outZ = (z - bz) * kk + bz;
        }
        break;
    case 3:
        if (f->_180 < 0x480) {
            {
                f32 kk = lbl_3_rodata_B80;
                *outX = (x - bx) * kk + bx;
                *outZ = (z - bz) * kk + bz;
            }
        } else {
            {
                f32 kk = lbl_3_rodata_B78;
                *outX = bx + (x - bx) / kk;
                *outZ = bz + (z - bz) / kk;
            }
        }
        break;
    case 4:
        {
            f32 kk = lbl_3_rodata_C08;
            *outX = bx + (x - bx) / kk;
            *outZ = bz + (z - bz) / kk;
        }
        break;
    }
    r5 = lbl_3_rodata_B64;
    for (b = &lbl_3_data_4444[2]; b < &lbl_3_data_4444[8]; b += 2) {
        if (*outZ > b[1] - r5 && *outZ < r5 + b[1] && *outX > b[0] - r5 && *outX < r5 + b[0]) {
            inBase = 1;
        }
    }
    if (inBase != 0) {
        switch (f->_18E) {
        case 0:
            {
                f32 kk = lbl_3_rodata_C44;
                *outX = x / kk;
                *outZ = z / kk;
            }
            break;
        case 1:
            {
                f32 kk = lbl_3_rodata_C48;
                *outX = bx + (x - bx) / kk;
                *outZ = bz + (z - bz) / kk;
            }
            break;
        case 2:
            {
                f32 kk = lbl_3_rodata_C4C;
                *outX = bx + (x - bx) / kk;
                *outZ = bz + (z - bz) / kk;
            }
            break;
        case 3:
            {
                f32 kk = lbl_3_rodata_C48;
                *outX = bx + (x - bx) / kk;
                *outZ = bz + (z - bz) / kk;
            }
            break;
        case 4:
            {
                f32 kk = lbl_3_rodata_B80;
                *outX = (x - bx) * kk + bx;
                *outZ = (z - bz) * kk + bz;
            }
            break;
        }
        return 1;
    }
    {
        f32 dx = *outX - f->_014;
        f32 dz = *outZ - f->_01C;
        dx = dx * dx;
        dz = dz * dz;
        d = dx + dz;
        SQRT_L(d);
    }
    if (d < lbl_3_rodata_B64) {
        *outX = f->_014;
        *outZ = f->_01C;
    }
    return 1;
}
#endif
#pragma opt_unroll_loops reset

// .text:0x00047628 size:0x150 mapped:0x806866BC
#pragma opt_unroll_loops off
#pragma dont_inline off
// 99.8%: f0/f1 swapped between the hoisted 3.7f constant and runner+0x64 in the loop. Inlined into fn_3_480B8.
int fn_3_47628(void) {
    int i;
    InMemRunnerType* r;
    f32 v;
    for (i = 3; i >= 0; i--) {
        r = &g_Runners[i];
        if (r->runnerOnFieldOrOutOrScored == 1 && (!(r->fractionalBasesRan >= lbl_3_rodata_C50) || r->runningDirectionCode != 1 || r->tagUpInd == 2)) {
            r = &g_Runners[i];
            v = r->fractionalBasesRan;
            if (v >= lbl_3_rodata_B78) {
                return 0;
            }
            if (r->tagUpInd == 2 && r->percentTowardsNextBase >= lbl_3_rodata_C38) {
                return r->startingBase_baseAchieved;
            }
            if (v >= lbl_3_rodata_B68) {
                if (v >= lbl_3_rodata_C54 && g_Runners[i].runningDirectionCode == 1) {
                    return 0;
                }
                return 3;
            }
            if (v >= lbl_3_rodata_C48 && g_Runners[i].runningDirectionCode == 1) {
                return 3;
            }
            return 2;
        }
    }
    return 4;
}
#pragma dont_inline on
#pragma opt_unroll_loops reset

// .text:0x00047778 size:0x940 mapped:0x8068680C
#define FL_STATE(n) g_FieldingLogic._0F8[(n)]
#define IS_CHASING(s) ((s) == 1 || (s) == 10 || (s) == 11)
// NONMATCHING 93.8%: registers (extra saved reg for s5) and the inlined set-target sqrt temp (f2 vs f4)
#if NONMATCHING
// On a steal/pickoff situation, assign who covers second (0x18C = 6) and where the pitcher backs up.
void fn_3_47778(void) {
    u8 v = g_Ball.hitClassification2;
    u8 s3;
    u8 s5;
    u8 s;
    int a;
    if (v != 5 && v != 6 && v != 8) {
        return;
    }
    s3 = FL_STATE(3);
    if (IS_CHASING(s3)) {
        if (g_Fielders[(5)]._18C != -1) {
            g_Fielders[(3)]._18C = 6;
            g_Fielders[(3)]._1D7 = 2;
        } else {
            g_Fielders[(5)]._18C = 6;
            g_Fielders[(5)]._1D7 = 2;
            if (FL_STATE(5) == 0) {
                SetFielderAct(5, 0xB);
            }
        }
    } else if (s5 = FL_STATE(5), IS_CHASING(s5)) {
        if (g_Fielders[(3)]._18C != -1) {
            g_Fielders[(5)]._18C = 6;
            g_Fielders[(5)]._1D7 = 2;
        } else {
            g_Fielders[(3)]._18C = 6;
            g_Fielders[(3)]._1D7 = 2;
            if (s3 == 0) {
                SetFielderAct(3, 0xB);
            }
        }
    } else if (g_Ball.Hit_HorizontalAngle < 0x400) {
        if (g_Fielders[(3)]._18C == 1 && (s = FL_STATE(2), IS_CHASING(s))) {
            g_Fielders[(2)]._18C = 6;
            g_Fielders[(2)]._1D7 = 2;
        } else {
            g_Fielders[(3)]._18C = 6;
            g_Fielders[(3)]._1D7 = 2;
            if (s3 == 0) {
                SetFielderAct(3, 0xB);
            }
        }
    } else {
        if (g_Fielders[(5)]._18C == 3 && (s = FL_STATE(4), IS_CHASING(s))) {
            g_Fielders[(4)]._18C = 6;
            g_Fielders[(4)]._1D7 = 2;
        } else {
            g_Fielders[(5)]._18C = 6;
            g_Fielders[(5)]._1D7 = 2;
            if (s5 == 0) {
                SetFielderAct(5, 0xB);
            }
        }
    }
    if (FL_STATE(0) != 0) {
        return;
    }
    g_Fielders[(0)]._18C = 15;
    a = g_Ball.Hit_HorizontalAngle;
    if (a < 0x320) {
        SetTargetAC8(0, lbl_3_rodata_BF4, lbl_3_rodata_C28);
    } else if (a < 0x400) {
        SetTargetAC8(0, lbl_3_rodata_B78, lbl_3_rodata_C58);
    } else if (a < 0x4E0) {
        SetTargetAC8(0, lbl_3_rodata_C5C, lbl_3_rodata_C58);
    } else {
        SetTargetAC8(0, lbl_3_rodata_C60, lbl_3_rodata_C28);
    }
    SetFielderAct(0, 0xE);
}
#endif
#undef FL_STATE
#undef IS_CHASING

#if NONMATCHING
static inline void Inl480B8(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int base;
    f32 x;
    f32 z;
    f32 dx, dz, d;
    base = fn_3_47628();
    if (base != -1) {
        f->_18E = base;
        if (fn_3_46E08(i, &x, &z) != 0) {
            f->_014 = x;
            f->_01C = z;
            dx = x - f->x;
            dz = z - f->z;
            if (0.0f == dx && 0.0f == dz) {
                f->_050 = 0.0f;
                f->_068 = 0.0f;
            } else {
                f->_064 = atan2(dz, dx);
                d = dx * dx + dz * dz;
                SQRT_L(d);
                f->_068 = d;
            }
            f->_1D9 = 1;
        }
    }
}
#endif

// .text:0x000480B8 size:0x314 mapped:0x8068714C
// NONMATCHING 99.9%: f0/f1 swapped for the 3.7f constant vs runner+0x64 in the inlined fn_3_47628 loop (same issue as fn_3_47628)
#if NONMATCHING
// Fielder i covers the base the lead runner is heading for (fn_3_47628).
void fn_3_480B8(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int base;
    f32 x;
    f32 z;
    f32 dz, dx, d;
    base = fn_3_47628();
    if (base != -1) {
        f->_18E = base;
        if (fn_3_46E08(i, &x, &z) != 0) {
            f->_014 = x;
            f->_01C = z;
            dx = x - f->x;
            dz = z - f->z;
            if (0.0f == dx && 0.0f == dz) {
                f->_050 = 0.0f;
                f->_068 = 0.0f;
            } else {
                f->_064 = atan2(dz, dx);
                d = dx * dx + dz * dz;
                SQRT_L(d);
                f->_068 = d;
            }
            f->_1D9 = 1;
        }
    }
}
#endif

// .text:0x000483CC size:0xB4 mapped:0x80687460
void fn_3_483CC(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f->_18C = fn_3_3D7D4(i);
    f->_1D7 = 2;
    if (i != -1) {
        f->_1D3 = 0xE;
        if (lbl_3_data_3C40[14].anim >= 0) {
            g_FieldingLogic._0F8[i] = lbl_3_data_3C40[14].anim;
        }
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_1A4 = 0;
        f->_1AC = 0;
        f->_1FF = 0;
    }
    f->_1D6 = 0;
    g_FieldingLogic._0BE = -1;
}

// .text:0x00048480 size:0x5D4 mapped:0x80687514
// NONMATCHING 99.5%: fn_3_480B8 (lead-runner cover + set target) inlined via Inl480B8; f0/f1 swapped in the inlined
// fn_3_47628 loop (same issue as fn_3_47628) and a few other float registers
#if NONMATCHING
// Infielder i during a hit: cover the lead runner's base (fn_3_480B8), then react to the ball state.
void fn_3_48480(int i) {
    InMemFielderView* f = &g_Fielders[i];
    u8 st;
    switch (fn_3_53130(i)) {
    case 2:
        return;
    default:
        if (g_FieldingLogic._0C4 == 6) {
            fn_3_46ABC(i);
            fn_3_A7C88();
        } else if (g_Strikes.outs < 3) {
            Inl480B8(i);
            fn_3_526DC(i);
        }
        if (0.0f != f->_050) {
            f->_17E = f->_068 / f->_050;
        }
    case 1:
        break;
    }
    st = g_Ball.ballState;
    if (st != 0 && g_FieldingLogic._0C4 != 6 && g_Ball.ballZoneAwayFromHome <= 1) {
        f->_18C = -1;
        f->_1D7 = 0;
        SetFielderAct(i, 0xC);
        g_FieldingLogic._0BE = -1;
    } else if (st == 1 &&
               (&g_Fielders[g_Ball.fielderWBallIndex].distToBase[0])[f->_18E] < lbl_3_rodata_B70 &&
               g_FieldingLogic._0C4 != 6) {
        f->_18C = fn_3_3D7D4(i);
        f->_1D7 = 2;
        SetFielderAct(i, 0xE);
        f->_1D6 = 0;
        g_FieldingLogic._0BE = -1;
        g_FieldingLogic._0C0 = 0x5A;
    } else if (st == 2 && g_FieldingLogic._0C4 != 6) {
        f->_18C = fn_3_3D7D4(i);
        f->_1D7 = 2;
        SetFielderAct(i, 0xE);
        f->_1D6 = 0;
        g_FieldingLogic._0BE = -1;
    }
    if (g_Ball.fielderBeingThrownTo == i) {
        fn_3_4E638();
    }
}
#endif

// .text:0x00048A54 size:0xAA0 mapped:0x80687AE8
// NONMATCHING 98.6%: entry if-shape, lhau vs lha for the base-cover table, and float/int register swaps
#if NONMATCHING
// Fielder i takes over as the ball chaser (FieldingLogic+0xBE) when it can reach the ball sooner.
void fn_3_48A54(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 x;
    f32 z;
    f32 d;
    int k;
    InMemFielderView* g;
    if (fn_3_53130(i) != 0 || f->_252 != 0) {
        return;
    }
    f->_18E = fn_3_47628();
    if (g_FieldingLogic._0BE < 0) {
        if (fn_3_46E08(i, &x, &z) == 0) {
            return;
        }
        {
            f32 dz, dx, dd;
            f->_014 = x;
            f->_01C = z;
            dx = x - f->x;
            dz = z - f->z;
            if (0.0f == dx && 0.0f == dz) {
                f->_050 = 0.0f;
                f->_068 = 0.0f;
            } else {
                f->_064 = atan2(dz, dx);
                dd = dx * dx + dz * dz;
                SQRT_L(dd);
                f->_068 = dd;
            }
            f->_1D9 = 1;
        }
        g_FieldingLogic._0BE = i;
        SetFielderAct(i, 5);
        FielderTakeOverAC8(i);
        return;
    }
    if (g_FieldingLogic._0C4 == 6) {
        SetFielderAct(i, 0xC);
        g_Fielders[i]._1D5 = 4;
        return;
    }
    if (fn_3_46E08(i, &x, &z) == 0) {
        return;
    }
    {
        f32 dx = x - f->x;
        f32 dz = z - f->z;
        dx = dx * dx;
        dz = dz * dz;
        d = dx + dz;
        SQRT_L(d);
    }
    k = g_FieldingLogic._0BE;
    if (d < g_Fielders[k]._068) {
        if (g_Ball.fielderWBallIndex != k) {
            SetFielderAct(k, 0xC);
            g_Fielders[g_FieldingLogic._0BE]._1D5 = 4;
        }
        g = &g_Fielders[g_FieldingLogic._0BE];
        g->_18C = -1;
        g->_1D7 = 0;
        {
            f32 dx, dz, dd;
            f->_014 = x;
            f->_01C = z;
            dx = x - f->x;
            dz = z - f->z;
            if (0.0f == dx && 0.0f == dz) {
                f->_050 = 0.0f;
                f->_068 = 0.0f;
            } else {
                f->_064 = atan2(dz, dx);
                dd = dx * dx + dz * dz;
                SQRT_L(dd);
                f->_068 = dd;
            }
            f->_1D9 = 1;
        }
        g_FieldingLogic._0BE = i;
        SetFielderAct(i, 5);
        FielderTakeOverAC8(i);
    } else {
        SetFielderAct(i, 0xC);
        g_Fielders[i]._1D5 = 4;
    }
}
#endif

// .text:0x000494F4 size:0x4D0 mapped:0x80688588
// NONMATCHING 96.7%: orig recomputes the fielder pointer (g_Fielders + saved i*0x268) for the stop block; float regs differ
#if NONMATCHING
// Fielder i closes in on the ball; stops (target = own position) once close enough.
void fn_3_494F4(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 dz, dx, d, r, tx, tz;
    if (g_Ball.pauseBallMovementWhenInPlant != 0) {
        dz = g_Ball.AtBat_Contact_BallPos.z - f->z;
        dx = g_Ball.AtBat_Contact_BallPos.x - f->x;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        if (d < lbl_3_data_4930[37]) {
            goto stop;
        }
        dx = dx / d;
        dz = dz / d;
        r = lbl_3_data_4930[36] - lbl_3_rodata_B60;
        tx = r * dx + f->x;
        tz = r * dz + f->z;
        SetTargetAC8(i, tx, tz);
    }
    if (g_Ball.hitWallInd != 0) {
        if (f->_074 < lbl_3_data_4930[1]) {
            goto stop;
        }
    } else {
        dx = g_Ball.AtBat_Contact_BallPos.x - g_Ball.ballWillHitBallPos.x;
        dz = g_Ball.AtBat_Contact_BallPos.z - g_Ball.ballWillHitBallPos.z;
        dx = dx * dx;
        dz = dz * dz;
        d = dx + dz;
        SQRT_L(d);
        if (d < lbl_3_data_4930[2] && f->_07C < lbl_3_data_4930[3]) {
            goto stop;
        }
    }
    if (g_Ball.hitClassification1 == 2 && f->_07C < lbl_3_data_4930[3]) {
        goto stop;
    }
    return;
stop:
    {
        InMemFielderView* g = &g_Fielders[i];
        g->_014 = f->x;
        g->_018 = f->y;
        g->_01C = f->z;
        g->_030 = 0.0f;
        g->_034 = 0.0f;
        g->_050 = 0.0f;
        g->_068 = 0.0f;
    }
}
#endif

// .text:0x000499C4 size:0x254 mapped:0x80688A58
// Pick the spot (out x/z) where fielder i should go to meet the ball's flight path.
// NONMATCHING 98.8%: px/pz pointer setup uses mr+addi in the original (register coalescing); loop compare needs volatile to defeat CSE
#if NONMATCHING
void fn_3_499C4(int i, f32* out) {
    InMemFielderView* f = &g_Fielders[i];
    int k;
    int res;
    int t;
    int j;
    f32* p;
    CoordAndDist* b;
    f32* pz;
    f32* px;
    f32 y;
    f32 d;
    f32 s;
    f32 nx;
    f32 nz;
    k = g_FieldingLogic._0B0;
    out[1] = 0.0f;
    if (g_FieldingLogic._0B2 >= 0) {
        k = g_FieldingLogic._0B2;
    }
    res = 0;
    t = g_Fielders[k]._186 - g_Ball.framesSinceHit;
    if (t > 0) {
        p = &g_Ball.physicsSubstruct.futureCoordsAndDist[t].dist;
        y = *p + lbl_3_data_4930[0];
        for (j = t + 1; j < 0x168; j += 3) {
            if (y < *(volatile f32*)p) {
                break;
            }
        }
        if (j < 0x168) {
            res = j;
        }
    }
    if (res == 0) {
        t = f->_186 - g_Ball.framesSinceHit;
        if (t <= 0) {
            t = 0x5A;
        } else if (t >= 0x168) {
            t = 0x167;
        }
        b = &g_Ball.physicsSubstruct.futureCoordsAndDist[t];
        pz = &b->pos.z;
        px = &b->pos.x;
        d = b->pos.x * b->pos.x + b->pos.z * b->pos.z;
        SQRT_L(d);
        nx = *px / d;
        nz = *pz / d;
        s = d + lbl_3_data_4930[0];
        out[0] = nx * s;
        out[2] = nz * s;
        return;
    }
    b = &g_Ball.physicsSubstruct.futureCoordsAndDist[res];
    out[0] = b->pos.x;
    out[2] = b->pos.z;
}
#endif


// .text:0x00049C18 size:0x290 mapped:0x80688CAC
void fn_3_49C18(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 out[3];
    f32 dz, dx, d, ox, oz;
    switch (fn_3_53130(i)) {
    case 2:
        return;
    default:
        if (f->_1FF == 0) {
            fn_3_499C4(i, out);
            ox = out[0];
            oz = out[2];
            f->_014 = ox;
            f->_01C = oz;
            dx = ox - f->x;
            dz = oz - f->z;
            if (0.0f == dx && 0.0f == dz) {
                f->_050 = 0.0f;
                f->_068 = 0.0f;
            } else {
                f->_064 = atan2(dz, dx);
                d = dx * dx + dz * dz;
                SQRT_L(d);
                f->_068 = d;
            }
            f->_1D9 = 1;
            f->_1FF = 1;
        }
        if (f->_1FF == 1) {
            fn_3_526DC(i);
            fn_3_494F4(i);
        }
    case 1:
        if (g_Ball.ballState != 0 && g_Ball.ballState != 3) {
            SetFielderAct(i, 0xC);
            if (i <= 5) {
                f->_1D6 = 7;
            } else {
                f->_1D6 = 6;
            }
        }
        break;
    }
}


// .text:0x00049EA8 size:0x94 mapped:0x80688F3C
void fn_3_49EA8(int i) {
    u8* p;
    s32 off;
    InMemFielderView* f;
    p = (u8*)&g_FieldingLogic + i; // -> &g_FieldingLogic._0F8[i] (update-form load)
    if (*(p += OFFSET_OF(g_FieldingLogic_s, _0F8)) != 9) {
        off = i * 0x268; // sizeof(InMemFielderView)
        f = (InMemFielderView*)((u8*)g_Fielders + off);
        f->_18C = 7;
        if (i != -1) {
            f->_1D3 = 0xE;
            if (lbl_3_data_3C40[14].anim >= 0) {
                *p = lbl_3_data_3C40[14].anim;
            }
            f->_1D5 = 0;
            f->_1D6 = 0;
            f->_1A4 = 0;
            f->_1AC = 0;
            f->_1FF = 0;
        }
        g_Fielders[i]._1D6 = 0;
        g_Fielders[i]._190 = -1;
    }
}

// .text:0x00049F3C size:0x4 mapped:0x80688FD0
void fn_3_49F3C(void) {
    return;
}

// .text:0x00049F40 size:0x1E4 mapped:0x80688FD4
void fn_3_49F40(int i, int mode) {
    InMemFielderView* f;
    if (g_FieldingLogic._0F8[i] != 0) {
        return;
    }
    f = &g_Fielders[i];
    f->_1D4 = mode;
    if (mode == 0) {
        if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
            if (i == -1) {
                return;
            }
            f->_1D3 = 3;
            if (lbl_3_data_3C40[3].anim >= 0) {
                g_FieldingLogic._0F8[i] = lbl_3_data_3C40[3].anim;
            }
            f->_1D5 = 0;
            f->_1D6 = 0;
            f->_1A4 = 0;
            f->_1AC = 0;
            f->_1FF = 0;
            return;
        }
        if (i == -1) {
            return;
        }
        f->_1D3 = 0x18;
        if (lbl_3_data_3C40[24].anim >= 0) {
            g_FieldingLogic._0F8[i] = lbl_3_data_3C40[24].anim;
        }
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_1A4 = 0;
        f->_1AC = 0;
        f->_1FF = 0;
        g_FieldingLogic._0BC = i;
        return;
    }
    if (mode == 1) {
        if (i == -1) {
            return;
        }
        f->_1D3 = 8;
        if (lbl_3_data_3C40[8].anim >= 0) {
            g_FieldingLogic._0F8[i] = lbl_3_data_3C40[8].anim;
        }
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_1A4 = 0;
        f->_1AC = 0;
        f->_1FF = 0;
        return;
    }
    if (i != -1) {
        f->_1D3 = 7;
        if (lbl_3_data_3C40[7].anim >= 0) {
            g_FieldingLogic._0F8[i] = lbl_3_data_3C40[7].anim;
        }
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_1A4 = 0;
        f->_1AC = 0;
        f->_1FF = 0;
    }
    if (mode == 2 || mode == 4) {
        g_Fielders[i]._190 = 1;
    }
    if (mode == 3 || mode == 5) {
        g_Fielders[i]._190 = 3;
    }
    if (mode == 6 || mode == 7) {
        g_Fielders[i]._190 = 2;
    }
}

// .text:0x0004A124 size:0x2E4 mapped:0x806891B8
void fn_3_4A124(void) {
    int i;
    u8 st = g_Ball.hitClassification3;
    if (st == 5) {
        if (g_FieldingLogic._0F8[2] == 1 || g_FieldingLogic._0F8[2] == 0xA || g_FieldingLogic._0F8[2] == 0xB) {
            fn_3_49F40(8, 0);
            fn_3_49F40(6, 7);
            fn_3_49F40(7, 1);
            return;
        }
        if (g_FieldingLogic._0F8[4] == 1 || g_FieldingLogic._0F8[4] == 0xA || g_FieldingLogic._0F8[4] == 0xB) {
            fn_3_49F40(6, 0);
            fn_3_49F40(7, 1);
            fn_3_49F40(8, 4);
            return;
        }
        fn_3_49F40(7, 0);
        if (g_Ball.Hit_HorizontalAngle < 0x400) {
            fn_3_49F40(8, 0);
            fn_3_49F40(6, 7);
            return;
        }
        fn_3_49F40(6, 0);
        fn_3_49F40(8, 4);
        return;
    } else if (st == 6) {
        fn_3_49F40(7, 0);
        if (g_Ball.Hit_HorizontalAngle >= 0x3E0 && g_Ball.Hit_HorizontalAngle < 0x420) {
            fn_3_49F40(8, 0);
            fn_3_49F40(6, 0);
            return;
        }
        if (g_Ball.Hit_HorizontalAngle < 0x400) {
            fn_3_49F40(8, 0);
            fn_3_49F40(6, 7);
            return;
        }
        fn_3_49F40(6, 0);
        fn_3_49F40(8, 6);
        return;
    } else if (st == 7) {
        if (g_FieldingLogic._0F8[1] != 1 && g_FieldingLogic._0F8[1] != 0xA && g_FieldingLogic._0F8[1] != 0xB) {
            fn_3_49F40(8, 0);
            fn_3_49F40(6, 1);
            fn_3_49F40(7, 1);
            return;
        }
        fn_3_49F40(6, 1);
        fn_3_49F40(7, 1);
        fn_3_49F40(8, 1);
        return;
    } else if (st == 8) {
        if (g_FieldingLogic._0F8[1] != 1 && g_FieldingLogic._0F8[1] != 0xA && g_FieldingLogic._0F8[1] != 0xB) {
            fn_3_49F40(6, 0);
            fn_3_49F40(7, 1);
            fn_3_49F40(8, 1);
            return;
        }
        fn_3_49F40(6, 1);
        fn_3_49F40(7, 1);
        fn_3_49F40(8, 1);
        return;
    } else {
        fn_3_49F40(6, 1);
        fn_3_49F40(7, 1);
        fn_3_49F40(8, 4);
        i = 2;
        do {
            fn_3_49F40(i, 0);
            i += 1;
        } while (i < 6);
        return;
    }
}

// .text:0x0004A408 size:0x5A4 mapped:0x8068949C
// NONMATCHING 98.9%: sqrt temp register (f2 vs f4) in the inlined fn_3_52560; px/pz pointer split uses mr+addi in orig
#if NONMATCHING
// Pick where fielder i should go to field a ball in flight (out x/z): a point on the
// ball's trajectory it can reach in time.
void fn_3_4A408(int i, f32* outX, f32* outZ) {
    InMemFielderView* f = &g_Fielders[i];
    CoordAndDist* e;
    f32* px;
    f32* pz;
    f32 d, r, vx, vz;
    if (g_Ball.AtBat_ContactResult == 0) {
        e = &g_Ball.physicsSubstruct.futureCoordsAndDist[(g_Ball.framesUntilBallHitsGround + 30)];
        px = &e->pos.x;
        pz = &e->pos.z;
        if (FramesToReachAC8(i, *px, *pz) < g_Ball.framesUntilBallHitsGround + 30) {
            *outX = *px;
            *outZ = *pz;
        } else {
            *outX = g_Ball.physicsSubstruct.futureCoordsAndDist[g_Ball.framesUntilBallHitsGround + 0x3c].pos.x;
            *outZ = g_Ball.physicsSubstruct.futureCoordsAndDist[g_Ball.framesUntilBallHitsGround + 0x3c].pos.z;
        }
        return;
    }
    if (fn_3_9CE0(f->x, f->z) < lbl_3_rodata_B60) {
        SetFielderAct(i, 0xC);
        f->_1D5 = 3;
        return;
    }
    if (i >= 6) {
        d = g_Ball.physicsSubstruct.futureCoordsAndDist[0x3c].pos.x * g_Ball.physicsSubstruct.futureCoordsAndDist[0x3c].pos.x + g_Ball.physicsSubstruct.futureCoordsAndDist[0x3c].pos.z * g_Ball.physicsSubstruct.futureCoordsAndDist[0x3c].pos.z;
        SQRT_L(d);
        r = lbl_3_rodata_C00 - d;
        if (r > 0.0f) {
            vx = g_Ball.ballVelocityPercent.x * r;
            vz = g_Ball.ballVelocityPercent.z * r;
            *outX = vx + g_Ball.physicsSubstruct.futureCoordsAndDist[0x3c].pos.x;
            *outZ = vz + g_Ball.physicsSubstruct.futureCoordsAndDist[0x3c].pos.z;
            return;
        }
    }
    if (FramesToReachAC8(i, g_Ball.physicsSubstruct.futureCoordsAndDist[0x1e].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[0x1e].pos.z) < 30) {
        *outX = g_Ball.physicsSubstruct.futureCoordsAndDist[0x1e].pos.x;
        *outZ = g_Ball.physicsSubstruct.futureCoordsAndDist[0x1e].pos.z;
    } else {
        *outX = g_Ball.physicsSubstruct.futureCoordsAndDist[0x3c].pos.x;
        *outZ = g_Ball.physicsSubstruct.futureCoordsAndDist[0x3c].pos.z;
    }
}
#endif

// .text:0x0004A9AC size:0x77C mapped:0x80689A40
// NONMATCHING 98.2%: stack slot of the sqrt classify temp, fn_3_B7E44 arg load order, and the unrolled 9-fielder loop's pointer/regs
#if NONMATCHING
// Fielder i chases the ball (or covers the fielder at ball+0x1B7E), choosing a catch action by distance.
void fn_3_4A9AC(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int k = g_Ball.fielderAboutToGetBall_hasBall;
    int j;
    int r;
    f32 x;
    f32 z;
    f32 d;
    switch (fn_3_53130(i)) {
    case 2:
        return;
    default:
        if (f->_1C5 == 0) {
            fn_3_4A408(i, &x, &z);
        } else if (k == -1) {
            x = f->x;
            z = f->z;
        } else if (f->_074 < lbl_3_rodata_B64) {
            x = f->x;
            z = f->z;
        } else if (g_Ball.ballState == 3) {
            x = lbl_3_rodata_BA0 * g_Ball.ballVelocityPercent.x + g_Ball.AtBat_Contact_BallPos.x;
            z = lbl_3_rodata_BA0 * g_Ball.ballVelocityPercent.z + g_Ball.AtBat_Contact_BallPos.z;
        } else if (0.0f == f->_050 && (&f->distToFielder[0])[k] < lbl_3_rodata_B70) {
            x = f->x;
            z = f->z;
        } else {
            InMemFielderView* g = &g_Fielders[k];
            x = lbl_3_rodata_BA0 * g_Ball.ballVelocityPercent.x + g->_014;
            z = lbl_3_rodata_BA0 * g_Ball.ballVelocityPercent.z + g->_01C;
        }
        {
            f32 dz, dx, dd;
            f->_014 = x;
            f->_01C = z;
            dx = x - f->x;
            dz = z - f->z;
            if (0.0f == dx && 0.0f == dz) {
                f->_050 = 0.0f;
                f->_068 = 0.0f;
            } else {
                f->_064 = atan2(dz, dx);
                dd = dx * dx + dz * dz;
                SQRT_L(dd);
                f->_068 = dd;
            }
            f->_1D9 = 1;
        }
        if (i >= 6) {
            if (k >= 6 && f->_068 < lbl_3_rodata_B9C) {
                f->_1D6 = 5;
            }
            if (f->_068 < lbl_3_rodata_B70) {
                f->_1D6 = 7;
            } else if (f->_068 < lbl_3_rodata_B9C) {
                f->_1D6 = 6;
            }
            r = fn_3_B7E44(f->_180, f->_070);
            if (r == 2) {
                f->_1D6 = 8;
            }
            if (r == 1) {
                f->_1D6 = 5;
            }
        } else if (k <= 5 && f->_068 < lbl_3_rodata_BA0) {
            f->_1D6 = 7;
        }
        for (j = 0; j < 9; j++) {
            if (j != i && (&f->distToFielder[0])[j] < lbl_3_rodata_B78) {
                f->_1D6 = 9;
                break;
            }
        }
        fn_3_526DC(i);
    case 1:
        if (g_Ball.ballState != 0 && g_Ball.ballState != 3) {
            SetFielderAct(i, 0xC);
            if (i <= 5) {
                f->_1D6 = 7;
            } else {
                f->_1D6 = 6;
            }
        }
        break;
    }
    if (g_Ball.AtBat_ContactResult != 0 && (&f->distToFielder[0])[k] > lbl_3_rodata_B64 + f->_074) {
        f32 dx = g_Ball.physicsSubstruct.futureCoordsAndDist[5].pos.x - f->x;
        f32 dz = g_Ball.physicsSubstruct.futureCoordsAndDist[5].pos.z - f->z;
        dx = dx * dx;
        dz = dz * dz;
        d = dx + dz;
        SQRT_L(d);
        if (d < f->_074 && f->_1C5 != 0) {
            fn_3_43038(i);
            SetFielderAct(i, 0x12);
            g_Ball.fielderAboutToGetBall_hasBall = -1;
        }
    }
}
#endif

// .text:0x0004B128 size:0x3EC mapped:0x8068A1BC
// NONMATCHING 99.5%: sqrt temp gets f2 instead of f4 in the inlined set-target block
#if NONMATCHING
// Outfielder i lines up as cutoff man between the ball and the base it is thrown to.
void fn_3_4B128(int i) {
    f32 cx;
    f32 cz;
    f32 px;
    f32 pz;
    s16 ang;
    switch (fn_3_53130(i)) {
    case 2:
        return;
    default:
        if (g_FieldingLogic._0C4 >= 1 && g_FieldingLogic._0C4 <= 3 && g_FieldingLogic._0E6 == 1 &&
            (g_FieldingLogic._0C4 == 2 || i != 7)) {
            getComponentsFromSAng(fn_3_9FB8C(g_Ball.throwDestination.x - g_Ball.AtBat_Contact_BallPos.x, g_Ball.throwDestination.z - g_Ball.AtBat_Contact_BallPos.z), &cx, &cz);
            px = lbl_3_rodata_B9C * cx + lbl_3_data_4444[g_FieldingLogic._0C4 * 2];
            pz = lbl_3_rodata_B9C * cz + (lbl_3_data_4444 + 1)[g_FieldingLogic._0C4 * 2];
            ang = fn_3_9FB8C(px, pz);
            if (ang <= 0x800 && ((ang < 0x300 && i == 8) || (ang > 0x500 && i == 6) || (ang < 0x400 && (i == 7 || i == 8)) ||
                                 (ang >= 0x400 && (i == 7 || i == 6)))) {
                if (pz < lbl_3_data_4444[3]) {
                    if (px < 0.0f) {
                        px = lbl_3_rodata_C64;
                    } else {
                        px = lbl_3_rodata_C68;
                    }
                    pz = lbl_3_rodata_BE8;
                }
                SetTargetAC8(i, px, pz);
            }
        }
        fn_3_526DC(i);
        if (g_Fielders[i]._068 < lbl_3_rodata_B64) {
            SetFielderAct(i, 0xC);
        } else if (g_Ball.numberOfThrowsDuringPlay >= 2) {
            SetFielderAct(i, 0xC);
        }
    case 1:
        break;
    }
}
#endif

// .text:0x0004B514 size:0x3BC mapped:0x8068A5A8
// NONMATCHING 98.2%: 0.0f load scheduled before the table load; f30/f31 swapped for the offset/dx
#if NONMATCHING
// Fielder i backs up: runs to its preset spot (lbl_3_data_44B4) or 20 units behind itself.
void fn_3_4B514(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 off = 0.0f;
    if (fn_3_53130(i) != 0) {
        return;
    }
    if (f->_1D4 >= 2) {
        f32 dz, dx, d, ox, oz;
        ox = lbl_3_data_44B4[f->_1D4 * 2];
        oz = (lbl_3_data_44B4 + 1)[f->_1D4 * 2];
        f->_014 = ox;
        f->_01C = oz;
        dx = ox - f->x;
        dz = oz - f->z;
        if (0.0f == dx && 0.0f == dz) {
            f->_050 = 0.0f;
            f->_068 = 0.0f;
        } else {
            f->_064 = atan2(dz, dx);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            f->_068 = d;
        }
        f->_1D9 = 1;
    } else {
        f32 dz, dx, d, ox, oz;
        if (i == 6) {
            off = lbl_3_rodata_BA0;
        }
        if (i == 8) {
            off = lbl_3_rodata_BD4;
        }
        ox = f->x + off;
        oz = f->z - lbl_3_rodata_B9C;
        f->_014 = ox;
        f->_01C = oz;
        dx = ox - f->x;
        dz = oz - f->z;
        if (0.0f == dx && 0.0f == dz) {
            f->_050 = 0.0f;
            f->_068 = 0.0f;
        } else {
            f->_064 = atan2(dz, dx);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            f->_068 = d;
        }
        f->_1D9 = 1;
    }
    SetFielderAct(i, 6);
}
#endif

// .text:0x0004B8D0 size:0x13C mapped:0x8068A964
void fn_3_4B8D0(int i) {
    InMemFielderView* f = &g_Fielders[i];
    s16 k = f->_18C;
    if (k >= 0) {
    if (k <= 3) {
        // &g_FieldingLogic._0D0[k], reached with an update-form load as in the original
        s16* p = (s16*)&g_FieldingLogic + k;
        if (*(p += OFFSET_OF(g_FieldingLogic_s, _0D0) / sizeof(s16)) == i) {
            *p = -1;
            g_FieldingLogic._101[k] = 0;
        }
        f->_18C = -1;
        f->_1D7 = 0;
        if (f->_1D3 == 1 && i != -1) {
            f->_1D3 = 0xC;
            if (lbl_3_data_3C40[12].anim >= 0) {
                g_FieldingLogic._0F8[i] = lbl_3_data_3C40[12].anim;
            }
            f->_1D5 = 0;
            f->_1D6 = 0;
            f->_1A4 = 0;
            f->_1AC = 0;
            f->_1FF = 0;
        }
    } else if (k == 5) {
        g_FieldingLogic._0D8 = -1;
        g_FieldingLogic.playerAtMoundCutoffLocation = 0;
        f->_18C = -1;
        f->_1D7 = 0;
        if (f->_1D3 == 0xE && i != -1) {
            f->_1D3 = 0xC;
            if (lbl_3_data_3C40[12].anim >= 0) {
                g_FieldingLogic._0F8[i] = lbl_3_data_3C40[12].anim;
            }
            f->_1D5 = 0;
            f->_1D6 = 0;
            f->_1A4 = 0;
            f->_1AC = 0;
            f->_1FF = 0;
        }
    }
    }
}

// .text:0x0004BA0C size:0xFBC mapped:0x8068AAA0
#define BASE_COVER(b) (g_FieldingLogic._0D0[(b)]) // fielder covering base b (0-3), 4 = backup
#define BASE_DIST(f, b) ((f)->distToBase[b])                       // fielder f's distance to base b
// NONMATCHING 85.8%: register allocation over the whole function (orig keeps loop pointers in r7-r10/r12) and lfsx/lhax indexed loads; control flow follows the asm, including the original reading c1's distance for c2 in the backup pick
#if NONMATCHING
// Keep every base covered while runners are moving: release covers that are no longer
// needed, then give the first uncovered base (or a base needing help) to the nearest free fielder.
void fn_3_4BA0C(void) {
    int n;
    int b;
    int j;
    int k;
    int help = -1;
    int c0, c1, c2;
    int best;
    u8 s;
    InMemFielderView* h;
    f32 d0, d1, d2;
    if (g_Strikes.outs >= 3 || g_RunningLogic._10 == 0) {
        return;
    }
    for (n = 0; n < 4; n++) {
        if (BASE_COVER(n) == -1) {
            break;
        }
    }
    if (g_Fielders[(0)]._1D8 == 1 && g_Fielders[(0)]._18C != 1 && g_Fielders[(0)]._18C != 3) {
        g_Fielders[(0)]._1D8 = 0;
    }
    for (b = 0; b < 4; b++) {
        if (g_FieldingLogic._101[b] != 0 || (k = BASE_COVER(b)) < 0) {
            continue;
        }
        s = g_FieldingLogic._0F8[k];
        if (s == 7) {
            if (b == g_FieldingLogic._0CC) {
                if (!(BASE_DIST(&g_Fielders[k], g_FieldingLogic._0CC) < lbl_3_rodata_B78)) {
                    FielderReleaseCoverAC8(k);
                }
            } else if (BASE_DIST(&g_Fielders[k], b) > lbl_3_rodata_C08) {
                FielderReleaseCoverAC8(k);
            }
        } else if (s == 1 || s == 10 || s == 11) {
            if (BASE_DIST(&g_Fielders[k], b) > lbl_3_rodata_B68) {
                FielderReleaseCoverAC8(k);
            }
        }
        if (s == 2 && BASE_DIST(&g_Fielders[BASE_COVER(b)], b) > lbl_3_rodata_B90 && help == -1) {
            help = b;
        }
    }
    c0 = c1 = c2 = -1;
    k = g_FieldingLogic._0D8;
    for (j = 0; j < 6; j++) {
        if (g_Fielders[(j)]._1ED != 0) {
            continue;
        }
        s = g_FieldingLogic._0F8[j];
        if (s == 0 || s == 8 || s == 9 || (s == 9 && k == j)) {
            if (c0 == -1) {
                c0 = j;
            } else if (c1 == -1) {
                c1 = j;
            } else {
                c2 = j;
            }
        }
    }
    if (n < 4) {
        // An uncovered base: the ball holder takes it if close, else the nearest free fielder.
        k = g_Ball.fielderWBallIndex;
        if (k >= 0) {
            h = &g_Fielders[k];
            if (BASE_DIST(h, n) <= lbl_3_data_4780[h->weight]) {
                h->_18C = n;
                BASE_COVER(n) = k;
                h->_1D7 = 1;
                g_FieldingLogic._101[n] = 1;
                return;
            }
        }
        if (c0 == -1) {
            return;
        }
        {
            f32 bx = ((VecXZ*)lbl_3_data_4444)[n].x;
            f32 bz = ((VecXZ*)lbl_3_data_4444)[n].z;
            f32 dx, dz;
            d1 = d2 = lbl_3_rodata_BA4;
            dx = g_Fielders[(c0)].x - bx;
            dz = g_Fielders[(c0)].z - bz;
            dx = dx * dx;
            dz = dz * dz;
            d0 = dx + dz;
            SQRT_L(d0);
            if (c1 >= 0) {
                dx = g_Fielders[(c1)].x - bx;
                dz = g_Fielders[(c1)].z - bz;
                dx = dx * dx;
                dz = dz * dz;
                d1 = dx + dz;
                SQRT_L(d1);
            }
            if (c2 >= 0) {
                dx = g_Fielders[(c2)].x - bx;
                dz = g_Fielders[(c2)].z - bz;
                dx = dx * dx;
                dz = dz * dz;
                d2 = dx + dz;
                SQRT_L(d2);
            }
        }
        best = c2;
        if (d0 < d1) {
            if (d0 < d2) {
                best = c0;
            }
        } else if (d1 < d2) {
            best = c1;
        }
        g_Fielders[(best)]._18C = n;
        g_Fielders[(best)]._1D7 = 1;
        SetFielderAct(best, 1);
        BASE_COVER(n) = best;
        if (g_FieldingLogic._0D8 == best) {
            g_FieldingLogic._0D8 = -1;
            g_FieldingLogic.playerAtMoundCutoffLocation = 0;
        }
        return;
    }
    if (help >= 0) {
        // The fielder covering base `help` is busy: hand the base to the nearest free fielder.
        best = -1;
        for (j = 0; j < 6; j++) {
            s = g_FieldingLogic._0F8[j];
            if ((s == 0 || s == 8 || s == 9) && BASE_DIST(&g_Fielders[j], help) < lbl_3_rodata_B9C) {
                if (best == -1) {
                    best = j;
                } else if (lbl_3_rodata_B78 + BASE_DIST(&g_Fielders[j], help) < BASE_DIST(&g_Fielders[best], help)) {
                    best = j;
                }
            }
        }
        if (best < 0) {
            return;
        }
        SetFielderAct(BASE_COVER(help), 0xC);
        k = BASE_COVER(help);
        g_Fielders[(k)]._1D5 = 3;
        FielderReleaseCoverAC8(k);
        g_Fielders[(best)]._18C = help;
        g_Fielders[(best)]._1D7 = 1;
        SetFielderAct(best, 1);
        BASE_COVER(help) = best;
        if (g_FieldingLogic._0D8 == best) {
            g_FieldingLogic._0D8 = -1;
            g_FieldingLogic.playerAtMoundCutoffLocation = 0;
        }
        return;
    }
    // All bases covered: pick a backup fielder (0x18C = 5) if there isn't one.
    k = g_FieldingLogic._0D8;
    if (k != -1 && g_Fielders[(k)]._18C == 5) {
        return;
    }
    d1 = d2 = lbl_3_rodata_BA4;
    if (g_Ball.ballState == 0 && g_Ball.ballZoneAwayFromHome <= 1) {
        return;
    }
    for (j = 0; j < 9; j++) {
        if (g_FieldingLogic._0F8[j] == 7) {
            if (BASE_DIST(&g_Fielders[j], 4) < lbl_3_rodata_BD8) {
                return;
            }
            break;
        }
    }
    if (c0 < 0) {
        return;
    }
    d0 = BASE_DIST(&g_Fielders[c0], 4);
    if (c1 >= 0) {
        d1 = BASE_DIST(&g_Fielders[c1], 4);
    }
    if (c2 >= 0) {
        d2 = BASE_DIST(&g_Fielders[c1], 4); // sic: the original reads c1 here too
    }
    best = c0;
    if (d0 < d1) {
        if (!(d0 < d2)) {
            best = c2;
        }
    } else if (d1 < d2) {
        best = c1;
    } else {
        best = c2;
    }
    g_Fielders[(best)]._18C = 5;
    g_Fielders[(best)]._1D7 = 2;
    SetFielderAct(best, 0xE);
    g_FieldingLogic._0D8 = best;
}
#endif
#undef BASE_COVER
#undef BASE_DIST

// .text:0x0004C9C8 size:0x5E8 mapped:0x8068BA5C
// NONMATCHING 98.8%: registers only; the state-table value and state constant swap r0/r3 in each inlined SetFielderAct
#if NONMATCHING
void fn_3_4C9C8(void) {
    int i;
    s16 b;
    if (g_FieldingLogic._0F8[1] == 0) {
        g_Fielders[1]._18C = 0;
        SetFielderAct(1, 1);
        g_FieldingLogic._0D0[0] = 1;
    } else if (g_Ball.hitClassification2 == 7) {
        g_Fielders[0]._18C = 0;
        SetFielderAct(0, 1);
        g_FieldingLogic._0D0[0] = 0;
    }
    if (g_FieldingLogic._0F8[2] == 0) {
        g_Fielders[2]._18C = 1;
        SetFielderAct(2, 1);
        g_FieldingLogic._0D0[1] = 2;
    } else if (g_Ball.physicsSubstruct.futureCoordsAndDist[g_Fielders[2]._186].pos.z < lbl_3_data_4444[3]) {
        g_Fielders[3]._18C = 1;
        SetFielderAct(3, 1);
        g_FieldingLogic._0D0[1] = 3;
    } else {
        g_Fielders[0]._18C = 1;
        SetFielderAct(0, 1);
        g_FieldingLogic._0D0[1] = 0;
        g_Fielders[0]._1D8 = 1;
    }
    if (g_FieldingLogic._0F8[4] == 0) {
        g_Fielders[4]._18C = 3;
        SetFielderAct(4, 1);
        g_FieldingLogic._0D0[3] = 4;
    } else if (g_Ball.physicsSubstruct.futureCoordsAndDist[g_Fielders[4]._186].pos.z < lbl_3_data_4444[7]) {
        g_Fielders[5]._18C = 3;
        SetFielderAct(5, 1);
        g_FieldingLogic._0D0[3] = 5;
    } else {
        g_Fielders[0]._18C = 3;
        SetFielderAct(0, 1);
        g_FieldingLogic._0D0[3] = 0;
        g_Fielders[0]._1D8 = 1;
    }
    if (g_Ball.Hit_HorizontalAngle < 0x400 || g_Ball.hitClassification3 == 7) {
        if (g_FieldingLogic._0F8[5] == 0) {
            g_Fielders[5]._18C = 2;
        SetFielderAct(5, 1);
            g_FieldingLogic._0D0[2] = 5;
        } else if (g_FieldingLogic._0F8[3] == 0) {
            g_Fielders[3]._18C = 2;
        SetFielderAct(3, 1);
            g_FieldingLogic._0D0[2] = 3;
        } else {
            g_Fielders[3]._18C = 2;
            g_Fielders[5]._18C = 2;
        }
    } else if (g_FieldingLogic._0F8[3] == 0) {
        g_Fielders[3]._18C = 2;
        SetFielderAct(3, 1);
        g_FieldingLogic._0D0[2] = 3;
    } else if (g_FieldingLogic._0F8[5] == 0) {
        g_Fielders[5]._18C = 2;
        SetFielderAct(5, 1);
        g_FieldingLogic._0D0[2] = 5;
    } else {
        g_Fielders[3]._18C = 2;
        g_Fielders[5]._18C = 2;
    }
    for (i = 0; i < 9; i++) {
        b = g_Fielders[i]._18C;
        if (b >= 0 && b <= 3) {
            g_Fielders[i]._1D7 = 1;
        }
    }
}
#endif

// .text:0x0004CFB0 size:0x25C mapped:0x8068C044
void fn_3_4CFB0(void) {
    InMemFielderView* f;
    int st = g_Fielders[0]._18C;
    f32 x;
    f32 z;
    f32 d;
    f32 dz;
    f32 dx;
    if (st == 1) {
        d = lbl_3_data_4444[2] - g_Fielders[0].x;
        if (d > 15.0f) {
            d = 15.0f;
        }
        x = lbl_3_data_4444[2];
        d = d / lbl_3_rodata_B78;
        z = lbl_3_data_4444[3] - d;
    } else if (st == 3) {
        d = g_Fielders[0].x - lbl_3_data_4444[6];
        if (d > 15.0f) {
            d = 15.0f;
        }
        x = lbl_3_data_4444[6];
        d = d / lbl_3_rodata_B78;
        z = lbl_3_data_4444[7] - d;
    } else {
        x = lbl_3_data_4444[st * 2];
        z = (lbl_3_data_4444 + 1)[st * 2];
    }
    f = g_Fielders;
    f->_014 = x;
    f->_01C = z;
    dx = x - f->x;
    dz = z - f->z;
    if (0.0f == dx && 0.0f == dz) {
        f->_050 = 0.0f;
        f->_068 = 0.0f;
    } else {
        f->_064 = atan2(dz, dx);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        f->_068 = d;
    }
    f->_1D9 = 1;
}

// .text:0x0004D20C size:0x978 mapped:0x8068C2A0
// NONMATCHING 91%: branch layout of the early-out checks and float regs in the bag-settle math differ; base table loads are add+lfs not lfsx
#if NONMATCHING
// per-frame update for a fielder heading to / standing on a base
void fn_3_4D20C(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 dx;
    f32 dz;
    f32 d;
    f32 spd;
    s16 b;
    if (g_Ball.homeRunClassification != 0 && i <= 1) {
        return;
    }
    if (g_Ball.framesSinceHit < 0xF) {
        return;
    }
    if (i == 1 && g_FieldingLogic._118 != 0) {
        return;
    }
    if (g_Ball.framesSinceHit < f->_1D2 - 0xF && i != 0) {
        return;
    }
    if (g_Ball.framesSinceHit < f->_1D2 && i == 0) {
        return;
    }
    if (fn_3_53130(i) != 0) {
        return;
    }
    if (g_FieldingLogic._0C4 == f->_18C) {
        fn_3_A7C88();
    }
    if (f->_1D7 == 1) {
        if (f->_216 != 0) {
            dz = f->_01C - f->z;
            dx = f->_014 - f->x;
            d = dx * dx + dz * dz;
            SQRT_L(d);
            spd = d < f->maxVelocity ? d : f->maxVelocity;
            f->_030 = dx * spd;
            f->_034 = dz * spd;
            f->_050 = spd;
            f->x = f->x + f->_030;
            f->z = f->z + f->_034;
            f->_068 = d - spd;
        } else if (f->_252 != 0) {
            fn_3_261E8(i);
            f->_1A2 = 0;
        } else {
            b = f->_18C;
            if (g_FieldingLogic._101[b] == 0) {
                // not on the base yet: run to it
                if (f->_1D8 == 1) {
                    PitcherCoverInl();
                } else {
                    SetTargetAC8(i, lbl_3_data_4444[b * 2], lbl_3_data_4444[b * 2 + 1]);
                }
                fn_3_526DC(i);
            } else if (g_FieldingLogic._101[b] == 1) {
                // on the base: settle onto the bag
                if (f->distToBase[b] > lbl_3_data_4780[f->weight]) {
                    f->_014 = lbl_3_data_4444[b * 2];
                    dx = lbl_3_rodata_C20 * (lbl_3_data_4444[b * 2] - f->x);
                    dz = lbl_3_rodata_C20 * (lbl_3_data_4444[b * 2 + 1] - f->z);
                    f->_01C = lbl_3_data_4444[f->_18C * 2 + 1];
                    f->_030 = dx / f->distToBase[f->_18C];
                    f->_034 = dz / f->distToBase[f->_18C];
                    f->_050 = lbl_3_rodata_C20;
                    f->_068 = f->distToBase[f->_18C];
                    f->x = f->x + f->_030;
                    f->z = f->z + f->_034;
                } else {
                    dz = lbl_3_data_4444[b * 2 + 1] - f->z;
                    dx = lbl_3_data_4444[b * 2] - f->x;
                    d = dx * dx + dz * dz;
                    SQRT_L(d);
                    if (d < lbl_3_rodata_B24) {
                        f->x = lbl_3_data_4444[f->_18C * 2];
                        f->z = lbl_3_data_4444[f->_18C * 2 + 1];
                        StopFielderInl(i);
                    } else {
                        f->_030 = dx / lbl_3_rodata_B64;
                        f->_034 = dz / lbl_3_rodata_B64;
                        f->x = f->x + f->_030;
                        f->z = f->z + f->_034;
                    }
                }
                f->_030 = lbl_3_rodata_B20;
                f->_034 = lbl_3_rodata_B20;
                f->_050 = lbl_3_rodata_B20;
            }
        }
    }
    if (f->_1D7 == 1 && lbl_3_rodata_B20 != f->_050) {
        f->_17E = f->_068 / f->maxVelocity;
    }
    fn_3_5372C(i);
    if (g_Ball.fielderBeingThrownTo == i) {
        fn_3_4E638();
    }
}
#endif

// .text:0x0004DB84 size:0x90 mapped:0x8068CC18
int fn_3_4DB84(int i) {
    InMemFielderView* f = &g_Fielders[i];
    if (0.0f == g_Ball.ballVelocityPercent.x && 0.0f == g_Ball.ballVelocityPercent.z) {
        return 0;
    }
    if ((-(g_Ball.ballVelocityPercent.x * g_Ball.AtBat_Contact_BallPos.x) - g_Ball.ballVelocityPercent.z * g_Ball.AtBat_Contact_BallPos.z) +
            (g_Ball.ballVelocityPercent.x * f->x + g_Ball.ballVelocityPercent.z * f->z) >
        0.0f) {
        return 1;
    }
    return 0;
}

// .text:0x0004DC14 size:0x5A8 mapped:0x8068CCA8
// NONMATCHING 97.6%: saved-register assignment of the angle/index locals differs; the partner fielder x load isn't an lfsx
#if NONMATCHING
void fn_3_4DC14(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int other = -1;
    int kind = 0;
    int k;
    int low;
    int mode;
    f32 spd;
    f32 vspd;
    f32 dz;
    f32 hy;
    f32 dx;
    f32 hx; // also the nearest-distance threshold in the search loop
    int base;
    s16 a;
    int dir;
    int hang;
    int r;
    if (g_d_GameSettings.GameModeSelected != 6) {
        hx = lbl_3_data_4618[0];
        if (g_Ball.ballZoneAwayFromHome >= 3) {
            hx = lbl_3_data_4618[1];
        }
        for (k = 0; k < 9; k++) {
            if (k != i && fn_3_6D658(g_GameLogic.teamFielding, f->charID, g_Fielders[k].charID) >= lbl_3_data_4638[2]) {
                if (f->distToFielder[k] < hx && f->distToFielder[k] < 999.9f) {
                    other = k;
                    hx = f->distToFielder[k];
                }
            }
        }
        if (other >= 0) {
            kind = (f->_259 != 0) + 1;
            playSoundEffect(0x1AB);
        }
    }
    low = 0;
    spd = g_Ball.ballVelocity;
    mode = 0;
    if (g_d_GameSettings.GameModeSelected == 6) {
        mode = 1;
    }
    if (spd < lbl_3_data_48C4) {
        low = 1;
    }
    if (spd > lbl_3_rodata_B80) {
        spd = lbl_3_rodata_B80;
    }
    if (g_Ball.hardHitIndicator != 0) {
        vspd = spd * lbl_3_data_5CDC[kind + 8];
    } else {
        vspd = spd * lbl_3_data_5CDC[kind + 5];
    }
    base = fn_3_9FD28(g_Ball.ballTravelAngle + 0x800);
    if (kind != 0) {
        a = fn_3_9FB8C(g_Fielders[other].x - f->x, g_Fielders[other].z - f->z);
        dir = a + RandomInt_Game(0x200);
        dir -= 0x100;
        if (kind == 1) {
            hang = RandomInt_Game(0x100) + 0x100;
        } else {
            hang = RandomInt_Game(0x100) + 0x200;
        }
    } else if (f->_254 == 0) {
        hang = RandomInt_Game_Range(lbl_3_data_48C8[mode][0], lbl_3_data_48C8[mode][1]);
        dir = fn_3_9FD28(RandomInt_Game_Range(lbl_3_data_48C8[mode][2], lbl_3_data_48C8[mode][3]) + base);
    } else if (low == 0) {
        hang = RandomInt_Game_Range(lbl_3_data_48C8[mode][4], lbl_3_data_48C8[mode][5]);
        r = RandomInt_Game_Range(lbl_3_data_48C8[mode][6], lbl_3_data_48C8[mode][7]);
        if (f->_254 == 1) {
            r = -r;
        }
        dir = fn_3_9FD28(r + base);
    } else {
        hang = RandomInt_Game_Range(lbl_3_data_48C8[mode][8], lbl_3_data_48C8[mode][9]);
        r = RandomInt_Game_Range(lbl_3_data_48C8[mode][10], lbl_3_data_48C8[mode][11]);
        if (f->_254 == 1) {
            r = -r;
        }
        dir = fn_3_9FD28(r + base);
    }
    getComponentsFromSAng(hang, &hx, &hy);
    hy *= vspd;
    getComponentsFromSAng(dir, &dx, &dz);
    hx *= spd;
    dx *= hx;
    dz *= hx;
    g_Ball.physicsSubstruct.velocity.x = dx;
    g_Ball.physicsSubstruct.velocity.y = hy;
    g_Ball.physicsSubstruct.velocity.z = dz;
    g_Ball.physicsSubstruct.acceleration.x = lbl_3_rodata_B20;
    g_Ball.physicsSubstruct.acceleration.y = lbl_3_rodata_B20;
    g_Ball.physicsSubstruct.acceleration.z = lbl_3_rodata_B20;
    if (f->_258 == 4) {
        if (f->_20F == 0) {
            f->_1BC = radToShortAngle(f->_048);
            f->_20F = 1;
            f->_1B8 = 0;
            f->_1BA = lbl_3_data_49DC[0x1D];
            f->_252 = 0;
            f->_203 = 0;
            f->_205 = 0;
            f->_207 = 0;
            f->_1EE = 0;
        }
    } else {
        f->_1EE = (s8)(g_Ball.ballEnergy * lbl_3_data_5CDC[4]);
    }
    f->_252 = 0;
    f->_256 = 0;
    g_FieldingLogic._13B = 1;
    g_Ball.ballState = 3;
    g_Ball.fielderAboutToGetBall_hasBall = -1;
    g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy = 0;
    g_Ball.warioWaluGarlicIsActive = 0;
    g_Ball.ballIsRollingIndicator = 0;
    if (g_Ball.numFieldersWhoHandledBallDuringPlay < 0xFE) {
        g_Ball.numFieldersWhoHandledBallDuringPlay++;
    } else {
        g_Ball.numFieldersWhoHandledBallDuringPlay = 0xFF;
    }
    if (g_Ball.fielderWithBallIndexStored < 0) {
        g_Ball.fielderWithBallIndexStored = i;
    }
    if (g_Ball.numFieldersWhoHandledBallDuringPlay == 1) {
        if (fn_3_B7E10(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) != 0) {
            g_Ball.bobbleLocation_1fair_2foul = 2;
            if (g_Ball.ballInitialHitDoneInd == 0 && g_Ball.framesOnGroundUntilPickedUp != 0) {
                fn_3_A0F0();
            }
        } else {
            g_Ball.bobbleLocation_1fair_2foul = 1;
            if (g_Ball.ballInitialHitDoneInd == 0) {
                g_Ball.ballInitialHitDoneInd = 1;
            }
        }
    }
    if (kind != 0) {
        fn_3_90220(f->charID, 0);
    } else if (f->_258 != 4) {
        fn_3_90220(f->charID, 0xA);
    }
    playSoundEffect(0x16F);
    g_Ball.currentStarSwing = 0;
}
#endif

// .text:0x0004E1BC size:0x47C mapped:0x8068D250
// NONMATCHING 97%: float regs in the nearest-two-fielders loop allocated differently (f7/f9 etc.)
#if NONMATCHING
void fn_3_4E1BC(void) {
    int idx[2];
    f32 d1;
    f32 d2;
    f32 d;
    int i;
    int n;
    InMemFielderView* f;
    InMemFielderView* g;
    int k;
    s16 b;
    d1 = d2 = lbl_3_rodata_C24;
    for (i = 0; i < 9; i++) {
        f = &g_Fielders[i];
        d = (f->x - g_Ball.physicsSubstruct.futureCoordsAndDist[0x78].pos.x) * (f->x - g_Ball.physicsSubstruct.futureCoordsAndDist[0x78].pos.x) +
            (f->z - g_Ball.physicsSubstruct.futureCoordsAndDist[0x78].pos.z) * (f->z - g_Ball.physicsSubstruct.futureCoordsAndDist[0x78].pos.z);
        SQRT_L(d);
        if (d < d1) {
            d2 = d1;
            d1 = d;
            idx[1] = idx[0];
            idx[0] = i;
        } else if (d < d2) {
            d2 = d;
            idx[1] = i;
        }
    }
    for (n = 0; n < 2; n++) {
        f = &g_Fielders[idx[n]];
        fn_3_43038(idx[n]);
        if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
            SetFielderAct(idx[n], 0x12);
        } else if (n == 0) {
            SetFielderAct(idx[n], 0xF);
            g_FieldingLogic._0B0 = idx[n];
        } else {
            SetFielderAct(idx[n], 0x10);
        }
        if (f->_18C >= 0 && f->_18C <= 5) {
            // inlined fn_3_4B8D0(idx[n])
            k = idx[n];
            g = &g_Fielders[k];
            b = g->_18C;
            if (b >= 0) {
                if (b <= 3) {
                    if (g_FieldingLogic._0D0[b] == k) {
                        g_FieldingLogic._0D0[b] = -1;
                        g_FieldingLogic._101[b] = 0;
                    }
                    g->_18C = -1;
                    g->_1D7 = 0;
                    if (g->_1D3 == 1) {
                        SetFielderAct(k, 0xC);
                    }
                } else if (b == 5) {
                    g->_18C = -1;
                    g->_1D7 = 0;
                    g_FieldingLogic._0D8 = -1;
                    g_FieldingLogic.playerAtMoundCutoffLocation = 0;
                    if (g->_1D3 == 0xE) {
                        SetFielderAct(k, 0xC);
                    }
                }
            }
        }
        if (f->_18C >= 7 && f->_18C <= 0xE) {
            f->_18C = -1;
            f->_1D7 = 0;
        }
    }
}
#endif

// .text:0x0004E638 size:0x58C mapped:0x8068D6CC
void fn_3_4E638(void) {
    InMemFielderView* f = &g_Fielders[g_Ball.fielderBeingThrownTo];
    f32 d;
    f32 dLand;
    f32 dBall;
    s16 a;
    int diff;
    if (g_Ball.fielderBeingThrownTo < 0) {
        return;
    }
    d = (g_Ball.throwStartingLocation.x - g_Ball.AtBat_Contact_BallPos.x) * (g_Ball.throwStartingLocation.x - g_Ball.AtBat_Contact_BallPos.x) +
        (g_Ball.throwStartingLocation.z - g_Ball.AtBat_Contact_BallPos.z) * (g_Ball.throwStartingLocation.z - g_Ball.AtBat_Contact_BallPos.z);
    SQRT_L(d);
    if (!((g_Ball.framesSinceThrowStarted > 5 && f->_074 > f->_078) ||
          (g_Ball.framesUntilThrowReachesDest < 1 && f->_074 > lbl_3_rodata_B78) ||
          (g_Ball.ballVelocity < lbl_3_rodata_C6C && g_Ball.fielderWBallIndex < 0 && g_Ball.framesSinceThrowStarted > 0x3C) ||
          d > lbl_3_rodata_B68 + g_Ball.throwDistance || g_Ball.throwHasLastedEstimatedNOfFrames != 0)) {
        return;
    }
    if (!(f->_074 > f->reach[0])) {
        return;
    }
    if (f->_252 != 0 && f->_24C > 0) {
        return;
    }
    dLand = (g_Ball.throwTarget.x - g_Ball.throwStartingLocation.x) * (g_Ball.throwTarget.x - g_Ball.throwStartingLocation.x) +
            (g_Ball.throwTarget.z - g_Ball.throwStartingLocation.z) * (g_Ball.throwTarget.z - g_Ball.throwStartingLocation.z);
    SQRT_L(dLand);
    dBall = (g_Ball.throwStartingLocation.x - g_Ball.AtBat_Contact_BallPos.x) * (g_Ball.throwStartingLocation.x - g_Ball.AtBat_Contact_BallPos.x) +
            (g_Ball.throwStartingLocation.z - g_Ball.AtBat_Contact_BallPos.z) * (g_Ball.throwStartingLocation.z - g_Ball.AtBat_Contact_BallPos.z);
    SQRT_L(dBall);
    a = fn_3_9FB8C(g_Ball.throwTarget.x - g_Ball.throwStartingLocation.x, g_Ball.throwTarget.z - g_Ball.throwStartingLocation.z);
    diff = fn_3_9FCF8(a, fn_3_9FB8C(g_Ball.AtBat_Contact_BallPos.x - g_Ball.throwStartingLocation.x, g_Ball.AtBat_Contact_BallPos.z - g_Ball.throwStartingLocation.z));
    if (g_Ball.framesSinceThrowStarted > 5 && (lbl_3_rodata_B78 + dLand < dBall || (dLand < dBall && diff < 0x20))) {
        g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt = 1;
        if (g_GameLogic.walkOffWinInd == 0) {
            g_FieldingLogic._128 = 1;
        }
    } else {
        g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt = 2;
        g_FieldingLogic._12C = 1;
    }
    g_Ball.ballIsLooseInd_unused = 1;
    g_Ball.ballState = 3;
    fn_3_4E1BC();
    g_FieldingLogic._0C4 = -1;
    g_Ball.fielderBeingThrownTo = -1;
    g_Ball.looseBall_5FrameCountdown = 5;
}

// .text:0x0004EBC4 size:0x404 mapped:0x8068DC58
// NONMATCHING 95%: loop base pointers / best-time regs allocated differently; the eta compare tail is duplicated instead of shared
#if NONMATCHING
void fn_3_4EBC4(void) {
    int bestIdx = -1;
    s16 best = 9999;
    s16 second = 9999;
    int flag = 0;
    int eta;
    s16 raw;
    u8 kind;
    int i;
    int found;
    InMemFielderView* f;
    if (g_FieldingLogic._0C4 >= 0) {
        g_Ball.fielderAboutToGetBall_hasBall = -1;
        return;
    }
    if (g_Ball.fielderAboutToGetBall_hasBall >= 0) {
        return;
    }
    if (g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow > 0 && g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow < 0x19) {
        return;
    }
    eta = -1;
    if (g_Ball.ballZoneAwayFromHome <= 1 && g_Ball.maxYOfHit <= lbl_3_rodata_B78) {
        flag = 1;
    }
    for (i = 0; i < 9; i++) {
        f = &g_Fielders[i];
        if (g_FieldingLogic._0F8[i] != 1) {
            continue;
        }
        raw = f->_17E;
        if (raw == -1 && g_Ball.fielderAboutToGetBall_hasBall == i) {
            g_Ball.fielderAboutToGetBall_hasBall = -1;
            continue;
        }
        kind = f->_1DD;
        if (kind == 1 && i <= 5 && f->_080 > lbl_3_rodata_B64) {
            flag = 1;
            continue;
        }
        if (i >= 6 && flag != 0) {
            break;
        }
        eta = raw;
        if (raw < 0) {
            continue;
        }
        if (f->_19C != 0) {
            eta = raw + 0x3C;
        } else if (f->_1ED != 0) {
            eta = raw + 0x3C;
        }
        if (i == 0 && kind == 1 && f->_080 > f->_070) {
            eta += 0x1E;
        }
        if (eta < best) {
            bestIdx = i;
            best = eta;
        } else if (eta < second) {
            second = eta;
        }
    }
    if (bestIdx >= 0) {
        f = &g_Fielders[bestIdx];
        if (f->_1DD == 1 && best < 0x3C) {
            if (best + 0x3C < second) {
                g_Ball.fielderAboutToGetBall_hasBall = bestIdx;
            }
            if (best < 0x1E) {
                g_Ball.fielderAboutToGetBall_hasBall = bestIdx;
            }
            if (g_Ball.AtBat_ContactResult == 0) {
                if (f->_1DB == 0) {
                    g_Ball.fielderAboutToGetBall_hasBall = bestIdx;
                } else if (eta == bestIdx) {
                    g_Ball.fielderAboutToGetBall_hasBall = bestIdx;
                }
            } else {
                g_Ball.fielderAboutToGetBall_hasBall = bestIdx;
            }
        }
        kind = f->_1DC;
        if (kind == 4 && best < 0x3C) {
            g_Ball.fielderAboutToGetBall_hasBall = bestIdx;
        }
        if (kind == 2 && best < 0x1E) {
            found = 0;
            for (i = 0; i < 9; i++) {
                f = &g_Fielders[i];
                if (g_FieldingLogic._0F8[i] == 1) {
                    if (f->_1DD == 0) {
                        found = 1;
                        break;
                    }
                    if (f->_1DB == 0) {
                        found = 1;
                        break;
                    }
                    if (f->_1DC == 0 || f->_1DC == 1) {
                        found = 1;
                        break;
                    }
                }
            }
            if (found == 0) {
                g_Ball.fielderAboutToGetBall_hasBall = bestIdx;
            }
        }
    }
    if (g_Ball.fielderAboutToGetBall_hasBall >= 0) {
        g_Ball.ballIsLooseInd_unused = 0;
        g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt = 0;
        g_Ball.fielderBeingThrownTo = -1;
    }
}
#endif

// .text:0x0004EFC8 size:0x53C mapped:0x8068E05C
// NONMATCHING 93%: inlined frames-to-reach (fn_3_52560 body) and loop locals get different registers; rodata loads go through an addi base
#if NONMATCHING
void fn_3_4EFC8(int i, int mode) {
    InMemFielderView* f = &g_Fielders[i];
    int best = 0;
    int found = 0;
    int near = 0;
    int res = 0;
    f32 minH = lbl_3_rodata_B94;
    int start;
    int k;
    int t = 0; // original leaves this uninitialised if the loop never runs
    CoordAndDist* p;
    f32 h;
    f32 d;
    f32* tx;
    f32* tz;
    start = f->_1D2 - g_Ball.framesSinceHit;
    if (start < 1) {
        start = 1;
    }
    k = start;
    while (k < 0x168) {
        p = &g_Ball.physicsSubstruct.futureCoordsAndDist[k];
        if (p->pos.y > lbl_3_rodata_B98) {
            k += 3;
            continue;
        }
        t = start + (FramesToReachAC8(i, p->pos.x, p->pos.z) - 5);
        if (t < k) {
            h = p->pos.y;
            if (h < lbl_3_rodata_B68) {
                res = 1;
                break;
            }
            if (found != 0 && minH < h) {
                k = best;
                res = 2;
                break;
            }
            minH = h;
            best = k;
            found = 1;
        } else {
            if (t < k + 0x1E) {
                near = 1;
            }
            if (found != 0) {
                if (mode == 0) {
                    res = 2;
                    k = g_Ball.framesUntilBallHitsGround;
                } else {
                    k = best;
                    res = 2;
                }
                break;
            }
        }
        k++;
    }
    if (k >= 0x168) {
        k = 0x167;
    }
    f->_186 = k + g_Ball.framesSinceHit;
    if (res == 2 && g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y < lbl_3_rodata_B68) {
        res = 1;
    }
    if (res == 3 && near == 0) {
        res = 4;
    }
    f->_1DD = res;
    f->_1DA = 0;
    if (res != 1 && res != 2) {
        f->_1DA = 1;
    }
    tx = &g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.x;
    tz = &g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.z;
    d = (g_Ball.landingSpotLocation.x - tx[k * 4]) * (g_Ball.landingSpotLocation.x - tx[k * 4]) +
        (g_Ball.landingSpotLocation.z - tz[k * 4]) * (g_Ball.landingSpotLocation.z - tz[k * 4]);
    SQRT_L(d);
    if (d < lbl_3_rodata_B78 && res == 1) {
        f->_1DB = 0;
    } else {
        f->_1DB = 1;
    }
    if (f->_1DB == 0) {
        if (t + 0x1E < f->_186) {
            g_FieldingLogic._0F2 |= 1 << i;
        }
    } else if (res == 1) {
        k = f->_186;
        if (g_RunningLogic._0E + 0x1E >
            f->_186 + fn_3_A6810(tx[k * 4], tz[k * 4],
                                            lbl_3_data_4444[2], lbl_3_data_4444[3]) + 0x3C) {
            g_FieldingLogic._0F2 |= 1 << i;
        }
    }
}
#endif

// .text:0x0004F504 size:0x630 mapped:0x8068E598
// NONMATCHING 91%: same search loop as fn_3_4EFC8 plus a far-ball cutoff; loop locals land in different registers
#if NONMATCHING
void fn_3_4F504(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int prevT = 9999;
    int best = 0;
    int found = 0;
    int near = 0;
    int res = 0;
    f32 minH = lbl_3_rodata_B94;
    int start;
    int k;
    int t = 0; // original leaves this uninitialised if the loop never runs
    CoordAndDist* p;
    f32 h;
    f32 d;
    f32* tx;
    f32* tz;
    start = f->_1D2 - g_Ball.framesSinceHit;
    if (start < 1) {
        start = 1;
    }
    k = start;
    while (k < 0x168) {
        p = &g_Ball.physicsSubstruct.futureCoordsAndDist[k];
        if (p->pos.y > lbl_3_rodata_B98) {
            k += 3;
            continue;
        }
        t = start + (FramesToReachAC8(i, p->pos.x, p->pos.z) - 5);
        if (t < k) {
            h = p->pos.y;
            if (h < lbl_3_rodata_B68) {
                res = 1;
                break;
            }
            if (found != 0 && minH < h) {
                k = best;
                res = 2;
                break;
            }
            minH = h;
            best = k;
            found = 1;
        } else {
            if (t < k + 0x1E) {
                near = 1;
            }
            if (found != 0) {
                k = best;
                res = 2;
                break;
            }
        }
        if (t > prevT && found == 0) {
            d = p->pos.x * p->pos.x + p->pos.z * p->pos.z;
            SQRT_L(d);
            if (d > lbl_3_rodata_BA0) {
                res = 3;
                break;
            }
        }
        prevT = t;
        k++;
    }
    if (k >= 0x168) {
        k = 0x167;
    }
    f->_186 = k;
    if (res == 2 && g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y < lbl_3_rodata_B68) {
        res = 1;
    }
    if (res == 3 && near == 0) {
        res = 4;
    }
    f->_1DD = res;
    f->_1DA = 0;
    if (res != 1 && res != 2) {
        f->_1DA = 1;
    }
    tx = &g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.x;
    tz = &g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.z;
    d = (g_Ball.landingSpotLocation.x - tx[k * 4]) * (g_Ball.landingSpotLocation.x - tx[k * 4]) +
        (g_Ball.landingSpotLocation.z - tz[k * 4]) * (g_Ball.landingSpotLocation.z - tz[k * 4]);
    SQRT_L(d);
    if (d < lbl_3_rodata_B78 && res == 1) {
        f->_1DB = 0;
    } else {
        f->_1DB = 1;
    }
    if (f->_1DB == 0) {
        if (t + 0x1E < f->_186) {
            g_FieldingLogic._0F2 |= 1 << i;
        }
    } else if (res == 1) {
        k = f->_186;
        if (g_RunningLogic._0E + 0x1E >
            f->_186 + fn_3_A6810(tx[k * 4], tz[k * 4], lbl_3_data_4444[2], lbl_3_data_4444[3]) + 0x3C) {
            g_FieldingLogic._0F2 |= 1 << i;
        }
    }
}
#endif

// .text:0x0004FB34 size:0xD64 mapped:0x8068EBC8
// NONMATCHING 95%: same flight search as fn_3_4F504 (with the inlined fn_3_51DF0 zone test); loop locals use different registers, smaller stack frame
#if NONMATCHING
// find where fielder i (an outfielder or infielder) can meet the fly ball; fills f+0x186 / 0x1DD / 0x1DA / 0x1DB
void fn_3_4FB34(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 minH = lbl_3_rodata_B94;
    f32 hmax = lbl_3_rodata_B98;
    int best = 0;
    int found = 0;
    int near = 0;
    int prevT = 9999;
    int res = 0;
    int step = 5;
    int margin;
    int start;
    int k;
    int t = 0; // original leaves this uninitialised if the loop never runs
    int m;
    int diff;
    u8 zone;
    u8 type;
    CoordAndDist* p;
    f32 h;
    f32 d;
    f32* tx;
    f32* tz;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        step = 3;
        margin = lbl_3_data_1C3C[0];
    } else {
        type = f->aiLevel;
        if (type == 0) {
            step = 2;
        }
        if (type == 1) {
            step = 3;
        }
        if (type == 3) {
            step = g_Ball.StaticRandomInt1 % 3 + 6;
        }
        if (type == 4) {
            step = g_Ball.StaticRandomInt1 % 4 + 8;
        }
        margin = lbl_3_data_1C3C[0];
        if (i >= 6) {
            hmax = f->reach[3] - lbl_3_rodata_B24;
        }
    }
    start = f->_1D2 - g_Ball.framesSinceHit;
    if (start < 1) {
        start = 1;
    }
    k = start;
    while (k < 0x168) {
        p = &g_Ball.physicsSubstruct.futureCoordsAndDist[k];
        h = p->pos.y;
        if (h > hmax) {
            if (h > lbl_3_rodata_B9C) {
                k += 10;
            } else if (h > lbl_3_rodata_BA0) {
                k += 6;
            } else {
                k += 3;
            }
            continue;
        }
        t = start + FramesToReachAC8(i, p->pos.x, p->pos.z);
        if (t < k - margin) {
            h = p->pos.y;
            if (h < f->reach[3]) {
                res = 1;
                break;
            }
            if (found != 0 && minH < h) {
                k = best;
                res = 2;
                break;
            }
            minH = h;
            best = k;
            found = 1;
        } else {
            if (t < k + 0x1E) {
                if (i >= 2 && i <= 5 && p->dist > lbl_3_rodata_B64 + f->_070) {
                    if (t < k + 10) {
                        near = 1;
                    }
                } else {
                    near = 1;
                }
            }
            if (found != 0) {
                k = best;
                res = 2;
                break;
            }
        }
        if (t > prevT && found == 0) {
            // ball is moving away from us: look a bit further down the flight for a better spot
            if (f->aiLevel <= 1 && i >= 6 && prevT + 0xF > k) {
                diff = prevT - k;
                best = 0;
                for (m = 5; m < 75; m += 5) {
                    p = &g_Ball.physicsSubstruct.futureCoordsAndDist[(k + m)];
                    if (start + FramesToReachAC8(i, p->pos.x, p->pos.z) < k + m) {
                        best = m;
                        break;
                    }
                }
                best += 10;
                for (m = 5; m < 30; m += 5) {
                    p = &g_Ball.physicsSubstruct.futureCoordsAndDist[(k + m)];
                    t = start + FramesToReachAC8(i, p->pos.x, p->pos.z) - (k + m);
                    if (diff <= t) {
                        break;
                    }
                    best = m;
                    diff = t;
                }
                k += best;
            }
            res = 3;
            break;
        }
        prevT = t;
        k += step;
    }
    if (k >= 0x168) {
        k = 0x167;
    }
    f->_186 = k;
    if (res == 2 && g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y < lbl_3_rodata_B68) {
        res = 1;
    }
    if (res == 3 && near == 0) {
        res = 4;
    }
    f->_1DD = res;
    f->_1DA = 0;
    if (res != 1 && res != 2) {
        f->_1DA = 1;
    }
    tx = &g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.x;
    tz = &g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.z;
    d = (g_Ball.landingSpotLocation.x - tx[k * 4]) * (g_Ball.landingSpotLocation.x - tx[k * 4]) +
        (g_Ball.landingSpotLocation.z - tz[k * 4]) * (g_Ball.landingSpotLocation.z - tz[k * 4]);
    SQRT_L(d);
    if (d < lbl_3_rodata_B8C && res == 1) {
        f->_1DB = 0;
    } else if (d < lbl_3_rodata_B64 && res == 1 && i >= 6) {
        f->_1DB = 0;
    } else {
        f->_1DB = 1;
    }
    if (i <= 5 && (f->_1DD == 1 || f->_1DD == 2)) {
        zone = FieldZoneInl(tx[k * 4], tz[k * 4]);
        if (f->_1DD == 2) {
            if (zone >= 2) {
                f->_1DD = 4;
            }
        } else if (zone >= 4) {
            f->_1DD = 4;
        }
    }
    if (g_Ball.howFoulTheBallWillBe != 0 && g_Ball.maxYOfHit >= lbl_3_rodata_B70 && f->_1DB != 0) {
        f->_186 = g_Ball.framesUntilBallHitsGround - 3;
        f->_1DD = 3;
        f->_1DA = 1;
        f->_1DB = 0;
    }
    if (g_d_GameSettings.minigamesEnabled == 0) {
        if (f->_1DB == 0) {
            if (t + 0xF < f->_186) {
                g_FieldingLogic._0F2 |= 1 << i;
            }
        } else if (i <= 5 && res == 1) {
            k = f->_186;
            if (fn_3_9FCF8(fn_3_9FB8C(tx[k * 4], tz[k * 4]), f->_180) < 0x80) {
                k = f->_186;
                if (g_RunningLogic._0E - 0x14 >
                    f->_186 + fn_3_A6810(tx[k * 4], tz[k * 4], lbl_3_data_4444[2], lbl_3_data_4444[3]) + 0x14) {
                    g_FieldingLogic._0F2 |= 1 << i;
                }
            }
        }
    }
}
#endif

// .text:0x00050898 size:0x388 mapped:0x8068F92C
// NONMATCHING 99%: r28/r31 (trajectory x base / frame index) swapped
#if NONMATCHING
int fn_3_50898(int i, f32* outX, f32* outZ) {
    f32* tz;
    InMemFielderView* f;
    f32* tx;
    int k;
    s16 ang;
    int m;
    f = &g_Fielders[i];
    tx = &g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.x;
    tz = &g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.z;
    k = f->_186 - g_Ball.framesSinceHit + 1;
    ang = fn_3_9FB8C(tx[k * 4], tz[k * 4]);
    if (fn_3_9FCF8(ang, f->_180) < lbl_3_data_49DC[0x1B]) {
        return 0;
    }
    if (g_d_GameSettings.GameModeSelected == 6) {
        goto scan_z;
    }
    if (i <= 5) {
        if ((i == 3 && ang > f->_180) || (i == 5 && ang < f->_180)) {
            *outX = f->_028;
            *outZ = f->z;
            return 1;
        }
        k += lbl_3_data_48A4[f->aiLevel];
        *outX = tx[k * 4];
        *outZ = tz[k * 4];
    } else if (i == 7) {
    scan_z:
        for (m = 0x3C; m < 0xF0; m += 5) {
            if (g_Ball.physicsSubstruct.futureCoordsAndDist[m].pos.z > f->z) {
                break;
            }
        }
        if (m >= 0xF0) {
            return 0;
        }
        *outX = tx[m * 4];
        *outZ = tz[m * 4];
    } else if ((i == 6 && f->_180 > ang) || (i == 8 && f->_180 < ang)) {
        for (m = 0x3C; m < 0xF0; m += 5) {
            if (g_Ball.physicsSubstruct.futureCoordsAndDist[m].dist > f->_070) {
                break;
            }
        }
        if (m >= 0xF0) {
            return 0;
        }
        *outX = tx[m * 4];
        *outZ = tz[m * 4];
    } else {
        k += lbl_3_data_48A4[f->aiLevel + 5];
        *outX = tx[k * 4];
        *outZ = tz[k * 4];
    }
    return 1;
}
#endif

// .text:0x00050C20 size:0x1B8 mapped:0x8068FCB4
void fn_3_50C20(int i, f32* outX, f32* outZ) {
    InMemFielderView* f = &g_Fielders[i];
    s16 ang = fn_3_9FB8C(f->_028 - f->x, f->_02C - f->z);
    f32 nx;
    f32 nz;
    if (i == 7) {
        if (ang > 0x200 && ang < 0x600) {
            *outX = f->x;
            *outZ = f->_02C;
        } else {
            *outX = f->_028;
            *outZ = f->z;
        }
        f->_18A = lbl_3_data_48F8[f->aiLevel];
    } else if (i == 8) {
        if (ang > 0x100 && ang < 0x600) {
            nx = f->x / f->_070;
            nz = f->z / f->_070;
            *outX = nx * (10.0f + f->_070);
            *outZ = nz * (10.0f + f->_070);
        } else {
            *outX = f->_028;
            *outZ = f->z;
        }
        f->_18A = lbl_3_data_48F8[f->aiLevel];
    } else {
        if (ang > 0x200 && ang < 0x700) {
            nx = f->x / f->_070;
            nz = f->z / f->_070;
            *outX = nx * (10.0f + f->_070);
            *outZ = nz * (10.0f + f->_070);
        } else {
            *outX = f->_028;
            *outZ = f->z;
        }
        f->_18A = lbl_3_data_48F8[f->aiLevel];
    }
}

// .text:0x00050DD8 size:0x448 mapped:0x8068FE6C
int fn_3_50DD8(int i, f32* x, f32* z, int mode) {
    InMemFielderView* f = &g_Fielders[i];
    f32 d;
    f32 dx;
    f32 dz;
    f32 inv;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        return 0;
    }
    if (i == 0 || i == 1 || i == 2 || i == 4) {
        return 0;
    }
    if (g_Ball.someCollisionInd != 0) {
        f->_18A = 0;
        return 0;
    }
    if (mode == 0) {
        f->_028 = *x;
        f->_02C = *z;
        d = (f->x - f->_028) * (f->x - f->_028) +
            (f->z - f->_02C) * (f->z - f->_02C);
        SQRT_L(d);
        if (d < lbl_3_data_4930[31]) {
            return 0;
        }
        if (fn_3_50898(i, &dx, &dz) != 0) {
            *x = dx;
            *z = dz;
        }
        f->_18A = 1;
        f->_188 = 0x1E;
    } else if (f->_20E == 0) {
        if (f->_18A > lbl_3_data_48A4[f->aiLevel + 10]) {
            f->_20E = 1;
        } else {
            d = (f->_020 - f->x) * (f->_020 - f->x) +
                (f->_024 - f->z) * (f->_024 - f->z);
            SQRT_L(d);
            if (d < lbl_3_data_4930[32]) {
                f->_20E = 1;
            }
        }
        *x = f->_020;
        *z = f->_024;
    } else {
        dx = f->_028 - f->_020;
        dz = f->_02C - f->_024;
        f->_188 = f->_188 - 1;
        if (f->_188 <= 0) {
            *x = f->_028;
            *z = f->_02C;
            f->_18A = 0;
        } else {
            inv = 1.0f / (f32)f->_188;
            dx *= inv;
            dz *= inv;
            *x = f->_020 + dx;
            *z = f->_024 + dz;
        }
    }
    return 1;
}

// .text:0x00051220 size:0x42C mapped:0x806902B4
// NONMATCHING 97%: saturating-counter scratch regs (r4/r5/r6) differ and the int->float pool base for the final scale isn't hoisted
#if NONMATCHING
void fn_3_51220(void) {
    InMemFielderView* f;
    if (g_FieldingLogic.curBoost->state != 0) {
        if (g_FieldingLogic.curBoost->timer < 0x7FFE) {
            g_FieldingLogic.curBoost->timer = g_FieldingLogic.curBoost->timer + 1;
        } else {
            g_FieldingLogic.curBoost->timer = 0x7FFF;
        }
        if (g_FieldingLogic.curBoost->timer2 < 0x7FFE) {
            g_FieldingLogic.curBoost->timer2 = g_FieldingLogic.curBoost->timer2 + 1;
        } else {
            g_FieldingLogic.curBoost->timer2 = 0x7FFF;
        }
        g_FieldingLogic.curBoost->frames++;
        if (g_FieldingLogic.curBoost->state == 4 || g_FieldingLogic.curBoost->state == 3) {
            g_FieldingLogic.curBoost->decay--;
            if (g_FieldingLogic.curBoost->decay == 0) {
                g_FieldingLogic.curBoost->state = 0;
                g_FieldingLogic.curBoost->timer = -1;
                g_FieldingLogic.curBoost->timer2 = -1;
                g_FieldingLogic.curBoost->fielder = -1;
                g_FieldingLogic.curBoost->scale = 1.0f;
            } else {
                g_FieldingLogic.curBoost->scale = (g_FieldingLogic.curBoost->scale - 1.0f) * (1.0f - 1.0f / (f32)g_FieldingLogic.curBoost->decay);
                g_FieldingLogic.curBoost->scale += 1.0f;
            }
            return;
        }
        if (g_FieldingLogic.curBoost->timer == 1) {
            g_FieldingLogic.curBoost->taps++;
            g_FieldingLogic.curBoost->power += lbl_3_data_4B9C.powerStep;
            if (g_FieldingLogic.curBoost->power >= lbl_3_data_4B9C.powerMax) {
                g_FieldingLogic.curBoost->power = lbl_3_data_4B9C.powerMax;
                g_FieldingLogic.curBoost->state = 2;
                if (g_d_GameSettings.GameModeSelected == 2 || g_Practice.practiceType_2 == 2 || g_Practice.practiceLevel == 2) {
                    g_Practice._1CB = 1;
                }
            }
        } else if (g_FieldingLogic.curBoost->timer >= lbl_3_data_4B9C.window) {
            f = &g_Fielders[g_FieldingLogic.curBoost->fielder];
            if (f->_19E == -1) {
                g_FieldingLogic.curBoost->state = 4;
                g_FieldingLogic.curBoost->decay = lbl_3_data_4B9C.decayStop;
                g_FieldingLogic.curBoost->dirX = f->_038;
                g_FieldingLogic.curBoost->dirZ = f->_03C;
            } else {
                g_FieldingLogic.curBoost->state = 3;
                g_FieldingLogic.curBoost->decay = lbl_3_data_4B9C.decayRun;
            }
            return;
        }
        g_FieldingLogic.curBoost->scale = ((f32)g_FieldingLogic.curBoost->power / (f32)lbl_3_data_4B9C.powerMax) * lbl_3_data_4B98 + 1.0f;
    } else if (g_FieldingLogic.curBoost->timer >= 0) {
        if (g_FieldingLogic.curBoost->timer2 < 0) {
            g_FieldingLogic.curBoost->timer2 = 0;
            g_FieldingLogic.curBoost->power = 0;
            g_FieldingLogic.curBoost->fielder = -1;
            g_FieldingLogic.curBoost->taps = 0;
        }
        if (g_FieldingLogic.curBoost->timer < 0x7FFE) {
            g_FieldingLogic.curBoost->timer = g_FieldingLogic.curBoost->timer + 1;
        } else {
            g_FieldingLogic.curBoost->timer = 0x7FFF;
        }
        if (g_FieldingLogic.curBoost->timer2 < 0x7FFE) {
            g_FieldingLogic.curBoost->timer2 = g_FieldingLogic.curBoost->timer2 + 1;
        } else {
            g_FieldingLogic.curBoost->timer2 = 0x7FFF;
        }
        if (g_FieldingLogic.curBoost->timer >= lbl_3_data_4B9C.window) {
            g_FieldingLogic.curBoost->timer = -1;
            g_FieldingLogic.curBoost->timer2 = -1;
            g_FieldingLogic.curBoost->fielder = -1;
            return;
        }
        if (g_FieldingLogic.curBoost->timer == 1) {
            g_FieldingLogic.curBoost->taps++;
        }
        if (g_FieldingLogic.curBoost->taps >= lbl_3_data_4B9C.tapsNeeded) {
            if (g_d_GameSettings.minigamesEnabled != 0) {
                g_FieldingLogic.curBoost->fielder = g_Minigame.minigameRelatedIndex;
            } else {
                g_FieldingLogic.curBoost->fielder = g_FieldingLogic._0B0;
            }
            g_FieldingLogic.curBoost->frames = 0;
            g_FieldingLogic.curBoost->state = 1;
            g_FieldingLogic.curBoost->scale = 1.0f;
            g_FieldingLogic.curBoost->timer = -1;
            g_FieldingLogic.curBoost->power = lbl_3_data_4B9C.powerStep;
        }
    }
}
#endif

// .text:0x0005164C size:0x14C mapped:0x806906E0
#pragma fp_contract off
int fn_3_5164C(int i, f32* out) {
    InMemFielderView* f = &g_Fielders[i];
    f32 x = f->x + f->_030;
    f32 z = f->z + f->_034;
    int r = 0;
    f32 t;
    f32 lim;
    f32 nx;
    f32 zz;
    if (x > 0.0f) {
        if (x > z) {
            x = z + lbl_3_rodata_B80 * (x - z);
            z = x;
            r = 2;
        }
    } else {
        t = -x;
        if (t > z) {
            z += lbl_3_rodata_B80 * (t - z);
            x = -z;
            r = 2;
        }
    }
    lim = lbl_3_data_4444[5];
    t = z - lim;
    if (!(t > x)) {
        nx = -x;
        if (!(t > nx)) {
            if (x > 0.0f) {
                zz = lim - z;
                x = zz + lbl_3_rodata_B80 * (x - zz);
                z = -x + lim;
                r = 2;
            } else {
                zz = lim - z;
                x = -zz - lbl_3_rodata_B80 * (nx - zz);
                z = x + lim;
                r = 2;
            }
        }
    }
    if (z <= lbl_3_data_4444[4]) {
        return 1;
    }
    out[0] = x;
    out[2] = z;
    return r;
}
#pragma fp_contract reset

// .text:0x00051798 size:0x658 mapped:0x8069082C
// NONMATCHING 97.6%: wall-type test gets range-merged (subi/cmplwi) instead of five compares; float regs for the wall normal differ
#if NONMATCHING
// wall check for fielder i's next step; 0 = free, 1 = blocked, 2 = slide (out = corrected x/z)
int fn_3_51798(int i, f32* out) {
    InMemFielderView* f = &g_Fielders[i];
    VecSrcDst ray;
    CollisionStruct hit;
    u32 col;
    u32 r;
    f32 vx;
    f32 vz;
    f32 d;
    f32 nx;
    f32 nz;
    f32 px;
    f32 pz;
    f32 wallAng;
    f32 lim;
    f32 x;
    f32 z;
    if (lbl_3_rodata_B20 == f->_050) {
        return 0;
    }
    if (g_d_GameSettings.GameModeSelected == 6 && g_GameLogic.gameStatus == 1) {
        r = fn_3_5164C(i, out);
        if (r != 0) {
            return r;
        }
    }
    if (g_d_GameSettings.minigamesEnabled == 0 && f->distToBase[0] < lbl_3_rodata_C84 && fn_3_B7E10(f->x, f->z) == 0) {
        return 0;
    }
    if (f->_1FB != 0) {
        return 0;
    }
    if (fn_3_B7E10(f->x, f->z) != 0 || g_Minigame.GameMode_MiniGame == 6 || g_d_GameSettings.GameModeSelected == 6) {
        x = f->x + f->_030;
        z = f->z + f->_034;
        ray.dst.x = x;
        ray.src.x = x;
        ray.dst.z = z;
        ray.src.z = z;
        ray.src.y = lbl_3_rodata_C88;
        ray.dst.y = lbl_3_rodata_BA0;
        col = checkCollision(&ray, &hit, 0, 0) & 0x7F;
        if (col == BALL_COLLISION_TYPE_WALL || col == BALL_COLLISION_TYPE_STRUCTURE || col == BALL_COLLISION_TYPE_PIT_WALL ||
            col == BALL_COLLISION_TYPE_PIT || col == BALL_COLLISION_TYPE_UNCLIMBABLE_WALL) {
            return 1;
        }
        if (g_Minigame.GameMode_MiniGame == 6 && fn_3_1379A0(i) != 0) {
            memcpy(out, f, 0xC);
            return 1;
        }
    }
    vx = f->_030 / f->_050;
    vz = f->_034 / f->_050;
    ray.src.x = f->x;
    ray.src.y = lbl_3_rodata_BB4;
    ray.src.z = f->z;
    ray.dst.y = lbl_3_rodata_BB4;
    ray.dst.x = f->x + vx;
    ray.dst.z = f->z + vz;
    col = checkCollision(&ray, &hit, 0, 0) & 0x7F;
    if (col != 2 && col != 5) {
        return 0;
    }
    d = hit.normal.x * hit.normal.x + hit.normal.z * hit.normal.z;
    SQRT_L(d);
    nx = hit.normal.x / d;
    nz = hit.normal.z / d;
    px = nx * lbl_3_data_476C[f->weight];
    pz = nz * lbl_3_data_476C[f->weight];
    wallAng = game_atan2(-px, -pz);
    lim = lbl_3_data_476C[f->weight] / (f32)cos(fn_3_9FEA8(wallAng - game_atan2(vx, vz)));
    if (f->_25A == 2) {
        lim = lbl_3_data_7F10[f->charID];
    }
    d = (f->x - hit.position.x) * (f->x - hit.position.x) + (f->z - hit.position.z) * (f->z - hit.position.z);
    SQRT_L(d);
    if (d < lim) {
    x = f->x + f->_030;
    z = f->z + f->_034;
    ray.dst.x = x;
    ray.dst.z = z;
    ray.src.x = x + lbl_3_rodata_B78 * nx;
    ray.src.z = z + lbl_3_rodata_B78 * nz;
    ray.dst.x = x - lbl_3_rodata_B78 * nx;
    ray.dst.z = z - lbl_3_rodata_B78 * nz;
    if (checkCollision(&ray, &hit, 1, 0) != 0) {
        out[0] = px * lbl_3_data_476C[f->weight] + hit.position.x;
        out[2] = pz * lbl_3_data_476C[f->weight] + hit.position.z;
        return 2;
    }
    return 1;
    }
    return 0;
}
#endif

// .text:0x00051DF0 size:0x294 mapped:0x80690E84
int fn_3_51DF0(f32 x, f32 z) {
    f32 d;
    f32 xx;
    if (40.0f + (x - z) > 0.0f && 40.0f + (-x - z) > 0.0f) {
        return 0;
    }
    xx = x * x;
    d = xx + z * z;
    SQRT_L(d);
    if (d < lbl_3_rodata_C70) {
        return 1;
    }
    z -= lbl_3_rodata_C74;
    d = xx + z * z;
    SQRT_L(d);
    if (d < lbl_3_rodata_C78) {
        return 1;
    }
    if (d < lbl_3_rodata_C7C) {
        return 2;
    }
    if (d < lbl_3_rodata_C80) {
        return 3;
    }
    return 4;
}

// .text:0x00052084 size:0x25C mapped:0x80691118
f32 fn_3_52084(int i, f32 x, f32 z) {
    InMemFielderView* f = &g_Fielders[i];
    f32 d;
    f32 dx;
    f32 dz;
    f32 p;
    if (f->_050 < 0.01f) {
        d = (f->x - x) * (f->x - x) + (f->z - z) * (f->z - z);
        SQRT_L(d);
        return d;
    }
    dz = z - f->z;
    dx = x - f->x;
    p = f->_038 * dx + f->_03C * dz;
    d = (dx * dx + dz * dz) - p * p;
    if (d < 0.0f) {
        return 0.0f;
    }
    if (d > 0.0f) {
        f64 xd = (f64)d;
        f64 guess = __frsqrte(xd);
        guess = lbl_3_rodata_B30 * guess * (lbl_3_rodata_B38 - guess * guess * xd);
        guess = lbl_3_rodata_B30 * guess * (lbl_3_rodata_B38 - guess * guess * xd);
        guess = lbl_3_rodata_B30 * guess * (lbl_3_rodata_B38 - guess * guess * xd);
        return (f32)(xd * guess);
    } else if (d < lbl_3_rodata_B40) {
        return NAN;
    } else if (isnan(d)) {
        return NAN;
    }
    return d;
}

// .text:0x000522E0 size:0x280 mapped:0x80691374
void fn_3_522E0(int i, int frames, f32* outX, f32* outZ, f32* outDist, f32 dx, f32 dz) {
    InMemFielderView* f = &g_Fielders[i];
    f32 dist = 0.0f;
    f32 spd = f->_050;
    f32 d;
    f32 nx;
    f32 nz;
    s16 ang;
    int n;
    int k;
    if (dist == dx && dist == dz) {
        *outX = f->x;
        *outZ = f->z;
        *outDist = dist;
        return;
    }
    d = dx * dx + dz * dz;
    SQRT_L(d);
    nx = dx / d;
    nz = dz / d;
    // fn_3_9FB8C returns s16; only this caller uses the result without re-extending it (see its prototype)
    ang = ((s16 (*)(f32, f32))fn_3_9FB8C)(nx, nz);
    if (!(f->_050 < lbl_3_rodata_B7C) && f->_19A >= 0) {
        if (fn_3_9FCF8(ang, f->_19A) > 0x2A8) {
            spd = 0.0f;
        }
    }
    n = f->_1D1;
    for (k = 0; k <= n; k++) {
        spd += f->velocityPerWeight;
        if (spd > f->maxVelocity) {
            dist += f->maxVelocity;
            break;
        }
        dist += spd;
    }
    frames -= k + 1;
    dist += f->maxVelocity * (f32)frames;
    *outDist = dist;
    *outX = nx * dist + f->x;
    *outZ = nz * dist + f->z;
}

// .text:0x00052560 size:0x17C mapped:0x806915F4
int fn_3_52560(int i, f32 x, f32 z) {
    InMemFielderView* f = &g_Fielders[i];
    f32 d;
    f32 spd;
    if (x == f->x && z == f->z) {
        return 1;
    }
    d = (x - f->x) * (x - f->x) + (z - f->z) * (z - f->z);
    SQRT_L(d);
    spd = f->maxVelocity;
    return ((u32)f->_1D1 >> 1) + (int)(d / (lbl_3_rodata_B20 == spd ? lbl_3_rodata_B60 : spd));
}

// .text:0x000526DC size:0x870 mapped:0x80691770
// NONMATCHING 96.5%: the inlined fn_3_530EC copies recompute the fielder pointer differently; angle temps land in other regs
#if NONMATCHING
// move fielder i one frame toward its target (speed ramp, collision, facing)
void fn_3_526DC(int i) {
    InMemFielderView* f = &g_Fielders[i];
    s16 a;
    f32 dx;
    f32 dz;
    f32 d;
    f32 spd;
    f32 tmp[3];
    if (f->_1ED != 0) {
        f->_1E3 = 1;
        return;
    }
    if (f->_1FD != 0) {
        f->_1E3 = 1;
        return;
    }
    if (f->_252 != 0) {
        fn_3_261E8(i);
        f->_1A2 = 0;
        return;
    }
    if (f->_068 > lbl_3_rodata_B20) {
        a = radToShortAngle(f->_064);
        fn_3_9FCF8(a, radToShortAngle(f->_0BC)); // result unused
        if (g_d_GameSettings.minigamesEnabled == 0 || f->_1C5 == 0) {
            if (f->_1C5 != 0 && (f->_1D3 == 2 || f->_1D3 == 0x12) && (f->_1DC == 4 || f->_1DC == 5)) {
                f->_1E3 = 0;
                goto speed_table;
            }
            if (i == g_Ball.fielderWBallIndex && g_FieldingLogic._0DE >= 0 &&
                (g_FieldingLogic._111 == 2 || g_FieldingLogic._111 == 3 || g_FieldingLogic._111 == 4) && g_FieldingLogic._112 == 1) {
                f->_1E3 = 0;
                dz = g_Runners[g_FieldingLogic._0DE].position.z - f->z;
                dx = g_Runners[g_FieldingLogic._0DE].position.x - f->x;
                d = dx * dx + dz * dz;
                SQRT_L(d);
                spd = d - lbl_3_rodata_B84;
                if (g_FieldingLogic._111 == 4) {
                    spd *= lbl_3_rodata_B80;
                    if (g_FieldingLogic._0EC > 0) {
                        spd /= (f32)g_FieldingLogic._0EC;
                    }
                    f->_050 = spd;
                } else {
                    if (spd < lbl_3_rodata_B20) {
                        spd = lbl_3_rodata_B20;
                    }
                    if (g_FieldingLogic._0EC > 0) {
                        f->_050 = spd / (f32)g_FieldingLogic._0EC;
                    } else {
                        f->_050 = spd;
                    }
                }
                goto clamp;
            }
        }
        if (g_FieldingLogic._0F8[i] == 0xB && f->_1D6 >= 1 && f->_1D6 <= 9) {
            if (f->_050 < lbl_3_rodata_B48) {
                f->_1E3 = 0;
                f->_1E4 = 0;
                f->_1A2 = 0;
            } else {
                if (f->_1A2 > 0x2D) {
                    f->_1A2 = 0x2D;
                }
                if (f->_1A2 != 0) {
                    f->_1A2 = f->_1A2 - 1;
                }
            }
        } else {
            f->_1E3 = 0;
            f->_1E4 = 0;
            if (f->_1A2 < 0x7FFE) {
                f->_1A2 = f->_1A2 + 1;
            } else {
                f->_1A2 = 0x7FFF;
            }
        }
    } else {
        f->_1E3 = 1;
        if (f->_1A2 > 0x2D) {
            f->_1A2 = 0x2D;
        }
        if (f->_1A2 != 0) {
            f->_1A2 = f->_1A2 - 1;
        }
    }
speed_table:
    switch (f->_1D6) {
    case 0:
        fn_3_3A234(i);
        break;
    case 1:
    case 5:
        f->_050 = f->_050 - lbl_3_rodata_C8C;
        break;
    case 2:
    case 6:
        f->_050 = f->_050 - lbl_3_rodata_C90;
        break;
    case 3:
    case 7:
        f->_050 = f->_050 - lbl_3_rodata_C94;
        break;
    case 4:
    case 8:
        f->_050 = f->_050 - lbl_3_rodata_C98;
        break;
    case 9:
        f->_050 = lbl_3_rodata_B20;
        break;
    case 10:
        f->_050 = lbl_3_rodata_B6C;
        break;
    case 11:
        f->_050 = lbl_3_rodata_B24;
        break;
    case 12:
        f->_050 = lbl_3_rodata_C20;
        break;
    case 13:
        f->_050 = lbl_3_rodata_B74;
        break;
    }
clamp:
    if (f->_1D6 < 5 && f->_1D6 >= 1 && f->_050 < lbl_3_rodata_C20) {
        f->_050 = lbl_3_rodata_C20;
    }
    if (f->_050 <= lbl_3_rodata_B20) {
        f->_050 = lbl_3_rodata_B20;
    }
    f->_068 = f->_068 - f->_050;
    d = (f->x - f->_014) * (f->x - f->_014) +
        (f->z - f->_01C) * (f->z - f->_01C);
    SQRT_L(d);
    if (d < f->_050) {
        f->_068 = lbl_3_rodata_C9C;
    }
    if (!(f->_050 <= lbl_3_rodata_B20)) {
        if (f->_068 < lbl_3_rodata_B20) {
            // arrived (or overshot) this frame: snap to the target
            f->_068 = lbl_3_rodata_B20;
            f->_030 = f->_014 - f->x;
            f->_034 = f->_01C - f->z;
            if (fn_3_51798(i, tmp) == 0) {
                if (f->_1D6 >= 1 && f->_1D6 <= 8) {
                    f->_014 = f->x;
                    f->_01C = f->z;
                } else {
                    f->x = f->_014;
                    f->z = f->_01C;
                }
            }
            StopFielderInl(i);
        } else {
            f->_030 = f->_050 * (f32)cos(f->_064);
            f->_034 = f->_050 * (f32)sin(f->_064);
            if (fn_3_51798(i, tmp) != 0) {
                StopFielderInl(i);
            } else {
                f->x = f->x + f->_030;
                f->z = f->z + f->_034;
                f->_064 = atan2(f->_01C - f->z, f->_014 - f->x);
            }
        }
    }
    if (lbl_3_rodata_B20 == f->_050 && f->_1E4 == 0) {
        f->_1E3 = 1;
    }
    f->_1F0 = 1;
}
#endif

// .text:0x00052F4C size:0x1A0 mapped:0x80691FE0
void fn_3_52F4C(int i, f32 x, f32 z) {
    InMemFielderView* f = &g_Fielders[i];
    f32 dx;
    f32 dz;
    f32 d;
    f->_014 = x;
    f->_01C = z;
    dx = x - f->x;
    dz = z - f->z;
    if (0.0f == dx && 0.0f == dz) {
        f->_050 = 0.0f;
        f->_068 = 0.0f;
    } else {
        f->_064 = atan2(dz, dx);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        f->_068 = d;
    }
    f->_1D9 = 1;
}

// .text:0x000530EC size:0x44 mapped:0x80692180
void fn_3_530EC(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f->_014 = f->x;
    f->_018 = f->y;
    f->_01C = f->z;
    f->_030 = lbl_3_rodata_B20;
    f->_034 = lbl_3_rodata_B20;
    f->_050 = lbl_3_rodata_B20;
    f->_068 = lbl_3_rodata_B20;
}

// .text:0x00053130 size:0x5FC mapped:0x806921C4
// NONMATCHING 96%: minigame index initialised (orig leaves it unset), stack slots of the int->float temps and the 0x205 lerp schedule differ
#if NONMATCHING
// per-frame special-motion update for fielder i; returns 2 = busy, 1 = moved, 0/bool = free
int fn_3_53130(int i) {
    InMemFielderView* f = &g_Fielders[i];
    CharActor* obj = lbl_8036E548.active[9];
    int k = 0; // original leaves this unset outside minigames (only read when g_Minigame.GameMode_MiniGame is 5/6)
    f32 d;
    f32 pos[1];
    s16 n;
    u8 st;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        k = g_Minigame.minigameControlStruct[0].fieldOrder[i - 2];
        obj = lbl_8036E548.active[k];
    }
    if (f->_1D3 == 0xC && obj != NULL && obj->anim[0] >= 0x11 && obj->anim[0] <= 0x1C) {
        return 2;
    }
    if (f->_20F != 0) {
        fn_3_25648(i);
        return 2;
    }
    if (f->_210 != 0) {
        fn_3_251E4(i);
        return 2;
    }
    if (f->_211 != 0) {
        fn_3_A96FC(i);
        return 2;
    }
    if (f->_252 == 0 && f->_25B != 0) {
        if (f->_25A == 2 && f->_1ED != 0) {
            return 2;
        }
        f->_25B = 0;
    } else if (f->_25A == 2 && f->_1ED != 0) {
        return 2;
    }
    if (f->_252 == 0 && f->_262 != 0) {
        // inlined fn_3_25A68(i)
        f->_228 = f->_228 * lbl_3_rodata_B28[0];
        f->_230 = f->_230 * lbl_3_rodata_B28[0];
        f->_030 = f->_228;
        f->_034 = f->_230;
        d = f->_030 * f->_030 + f->_034 * f->_034;
        SQRT_L(d);
        f->_050 = d;
        if (fn_3_51798(i, pos) != 0) {
            f->x = f->_0D4;
            f->z = f->_0D8;
            f->_050 = 0.0f;
            f->_030 = 0.0f;
            f->_034 = 0.0f;
        } else {
            f->x = f->x + f->_030;
            f->z = f->z + f->_034;
        }
        f->_014 = f->x;
        f->_01C = f->z;
        f->_1F0 = 1;
        return 2;
    }
    if (g_Ball._1BDF != 0) {
        return 2;
    }
    if (f->_25E >= 3) {
        if (f->_25E == 3) {
            f->_150 = f->_150 * lbl_3_data_4930[14];
            f->_158 = f->_158 * lbl_3_data_4930[14];
            f->x = f->x + f->_150;
            f->z = f->z + f->_158;
            f->_014 = f->x;
            f->_01C = f->z;
            f->_1F0 = 1;
        } else if (f->_25E == 4) {
            f->_050 = 0.0f;
            f->_25F--;
            if (f->_25F == 0) {
                f->_25E = 0;
            }
        }
        return 1;
    }
    if (f->_205 != 0) {
        f->_206 = 0;
        st = f->_205;
        if (st == 1) {
            n = f->_1B2;
            f->x = f->x + (f->_128 - f->x) / (f32)n;
            f->z = f->z + (f->_130 - f->z) / (f32)n;
            f->_154 = f->_154 - lbl_3_data_4930[18];
            f->_148 = f->_148 + f->_154;
            if (f->_148 < 0.0f) {
                f->_148 = 0.0f;
            }
            f->_1B2 = f->_1B2 - 1;
            if (f->_1B2 <= 0) {
                f->_205 = 2;
            }
        } else if (st == 2) {
            fn_3_2FB9C(i);
            f->_1B2 = 0;
        } else if (st >= 3) {
            fn_3_2FF2C(i);
            return 1;
        }
        f->_030 = f->x - f->_0D4;
        f->_034 = f->z - f->_0D8;
        return 1;
    }
    if (f->_207 != 0) {
        fn_3_2F924(i);
        return 1;
    }
    if (f->_203 != 0) {
        fn_3_2F574(i);
        return 1;
    }
    if (f->_1EE != 0) {
        return 2;
    }
    if (f->_1EF != 0) {
        return 2;
    }
    if (g_Minigame.GameMode_MiniGame == 5) {
        if (g_Minigame._1C9A[k] != 0) {
            return 2;
        }
    } else if (g_Minigame.GameMode_MiniGame == 6) {
        if (g_Minigame.starDashStunType[k] == 1 || g_Minigame.starDashStunType[k] == 2) {
            return 2;
        }
    }
    if (g_Minigame.GameMode_MiniGame == 5 || g_Minigame.GameMode_MiniGame == 6) {
        return 0;
    }
    return g_Ball.framesSinceHit < f->_1D2;
}
#endif

// .text:0x0005372C size:0x7BC mapped:0x806927C0
// NONMATCHING 94%: base table / cover-slot accesses use add+lfs/lha instead of lfsx/lhax; regs differ
#if NONMATCHING
// base-cover bookkeeping for fielder i (who stands on which base)
void fn_3_5372C(int i) {
    InMemFielderView* f = &g_Fielders[i];
    s16 b;
    s16 k;
    int n;
    f32 d;
    b = f->_18C;
    if (b >= 0 && b <= 3) {
        d = (lbl_3_data_4444[b * 2] - f->x) * (lbl_3_data_4444[b * 2] - f->x) +
            (lbl_3_data_4444[b * 2 + 1] - f->z) * (lbl_3_data_4444[b * 2 + 1] - f->z);
        SQRT_L(d);
        if (lbl_3_data_4780[f->weight] > d) {
            g_FieldingLogic._101[f->_18C] = 1;
            f->_1F5 = f->_18C;
            if (i == 0 && f->_1D8 == 1) {
                f->_1D8 = 0;
            }
        }
        if (g_Ball.fielderWBallIndex == i) {
            b = f->_18C;
            k = g_FieldingLogic._0D0[b];
            if (k != i && k >= 0 && g_FieldingLogic._101[b] != 0) {
                ReleaseBaseInl(i);
            }
        }
    } else if (g_Ball.fielderWBallIndex == i) {
        for (n = 0; n < 4; n++) {
            d = (lbl_3_data_4444[n * 2] - f->x) * (lbl_3_data_4444[n * 2] - f->x) +
                (lbl_3_data_4444[n * 2 + 1] - f->z) * (lbl_3_data_4444[n * 2 + 1] - f->z);
            SQRT_L(d);
            if (lbl_3_data_4780[f->weight] > d) {
                ReleaseBaseInl(g_FieldingLogic._0D0[n]);
                f->_18C = n;
                g_FieldingLogic._0D0[n] = i;
                f->_1D7 = 1;
                g_FieldingLogic._101[n] = 1;
                break;
            }
        }
    }
    if (f->_1F5s >= 0) {
        b = f->_1F5s;
        d = (lbl_3_data_4444[b * 2] - f->x) * (lbl_3_data_4444[b * 2] - f->x) +
            (lbl_3_data_4444[b * 2 + 1] - f->z) * (lbl_3_data_4444[b * 2 + 1] - f->z);
        SQRT_L(d);
        if (g_Ball.fielderWBallIndex == i) {
            if (lbl_3_rodata_CA0 + lbl_3_data_4780[f->weight] < d) {
                f->_1F5 = -1;
            }
        } else if (lbl_3_rodata_CA4 + lbl_3_data_4780[f->weight] < d) {
            f->_1F5 = -1;
        }
    }
    if (f->_203 != 0) {
        f->_1F5 = -1;
    }
    if (f->_1F5s < 0) {
        for (n = 0; n < 4; n++) {
            if (g_FieldingLogic._0D0[n] == i) {
                g_FieldingLogic._101[n] = 0;
                break;
            }
        }
    }
}
#endif

// .text:0x00053EE8 size:0x60 mapped:0x80692F7C
void fn_3_53EE8(int i) {
    InMemFielderView* f = &g_Fielders[i];
    if (i != -1) {
        f->_1D3 = 0x13;
        if (lbl_3_data_3C40[19].anim >= 0) {
            g_FieldingLogic._0F8[i] = lbl_3_data_3C40[19].anim;
        }
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_1A4 = 0;
        f->_1AC = 0;
        f->_1FF = 0;
    }
}

// .text:0x00053F48 size:0x570 mapped:0x80692FDC
// NONMATCHING 98%: float register allocation in the overlap/midpoint math differs (f3/f4/f5 shifted)
#if NONMATCHING
// push overlapping fielders apart (radius per fielder type)
void fn_3_53F48(void) {
    int i;
    int j;
    InMemFielderView* a;
    InMemFielderView* b;
    f32 d;
    f32 rsum;
    f32 t;
    f32 mx;
    f32 mz;
    f32 dx;
    f32 dz;
    f32 dist;
    s8 ka;
    s8 kb;
    f32 tmp[3];
    for (i = 0; i < 8; i++) {
        a = &g_Fielders[i];
        if (a->rosterID < 0) {
            continue;
        }
        for (j = i + 1; j < 9; j++) {
            b = &g_Fielders[j];
            if (b->rosterID < 0) {
                continue;
            }
            d = (b->x - a->x) * (b->x - a->x) + (b->z - a->z) * (b->z - a->z);
            SQRT_L(d);
            rsum = lbl_3_data_476C[a->weight] + lbl_3_data_476C[b->weight];
            if (!(d < rsum)) {
                continue;
            }
            t = lbl_3_data_476C[a->weight] / rsum;
            mz = t * (b->z - a->z) + a->z;
            mx = t * (b->x - a->x) + a->x;
            dz = mz - a->z;
            dx = mx - a->x;
            dist = dx * dx + dz * dz;
            SQRT_L(dist);
            if (!(dist > 0.0f)) {
                continue;
            }
            dx /= dist;
            dz /= dist;
            if (g_Minigame.GameMode_MiniGame == 6) {
                ka = (u8)g_Minigame.minigameControlStruct[0].fieldOrder[i - 2];
                kb = (u8)g_Minigame.minigameControlStruct[0].fieldOrder[j - 2];
                if (g_Minigame.starDashStunType[ka] == 0 && g_Minigame.starDashStunType[kb] == 0) {
                    if (ka == (s8)((u8)g_Minigame._1D6D)) {
                        g_Minigame.starDashStunType[kb] = 1;
                        g_Minigame._1CB8[kb].x = b->x - a->x;
                        g_Minigame._1CB8[kb].z = b->z - a->z;
                        fn_3_13A048(ka, kb);
                    } else if (kb == (s8)((u8)g_Minigame._1D6D)) {
                        g_Minigame.starDashStunType[ka] = 1;
                        g_Minigame._1CB8[ka].x = a->x - b->x;
                        g_Minigame._1CB8[ka].z = a->z - b->z;
                        fn_3_13A048(kb, ka);
                    }
                }
                continue;
            }
            if (a->_050 <= lbl_3_rodata_B20) {
                b->x = dx * (lbl_3_data_476C[a->weight] + lbl_3_data_476C[b->weight]) + a->x;
                b->z = dz * (lbl_3_data_476C[a->weight] + lbl_3_data_476C[b->weight]) + a->z;
            } else if (b->_050 <= lbl_3_rodata_B20) {
                a->x = b->x - dx * (lbl_3_data_476C[a->weight] + lbl_3_data_476C[b->weight]);
                a->z = b->z - dz * (lbl_3_data_476C[a->weight] + lbl_3_data_476C[b->weight]);
            } else {
                a->x = mx - dx * lbl_3_data_476C[a->weight];
                a->z = mz - dz * lbl_3_data_476C[a->weight];
                b->x = dx * lbl_3_data_476C[b->weight] + mx;
                b->z = dz * lbl_3_data_476C[b->weight] + mz;
            }
            if (fn_3_51798(i, tmp) != 0) {
                a->x = a->_0D4;
                a->z = a->_0D8;
            }
            if (fn_3_51798(j, tmp) != 0) {
                b->x = b->_0D4;
                b->z = b->_0D8;
            }
        }
    }
}
#endif

// .text:0x000544B8 size:0x448 mapped:0x8069354C
void fn_3_544B8(void) {
    u32 kind;
    int col;
    int i;
    InMemFielderView* f;
    VecSrcDst ray;
    CollisionStruct hit;
    Vec pos;
    Vec prev;
    f32 v;
    f32 h;
    SND_VOICEID vid;
    for (i = 0; i < 9; i++) {
        f = &g_Fielders[i];
        if (g_d_GameSettings.minigamesEnabled != 0 && g_Minigame.minigameRelatedIndex != i) {
            continue;
        }
        if ((g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 2) && f->_0B8 > lbl_3_rodata_CA8 &&
            g_Ball.totalFramesAtPlay > 1 && g_Ball.totalFramesAtPlay < 0x7FFF && i % 3 != g_Ball.totalFramesAtPlay % 3) {
            // skip the ground probe on most frames: reuse last height and surface
            f->_00C = f->_010;
            col = f->_1E6;
        } else {
            ray.src.x = f->x;
            ray.src.y = lbl_3_rodata_C9C;
            ray.src.z = f->z;
            ray.dst.x = f->x;
            ray.dst.y = lbl_3_rodata_B60;
            ray.dst.z = f->z;
            col = checkCollision(&ray, &hit, 0, 0);
            if (col == 0) {
                f->_00C = lbl_3_rodata_B20;
            } else {
                f->_00C = -hit.position.y;
            }
            kind = col & 0x7F;
            if (kind == BALL_COLLISION_TYPE_WATER) {
                pos.x = f->x;
                pos.y = f->_00C;
                pos.z = f->z;
                prev.x = f->_0D4;
                prev.y = f->_00C;
                prev.z = f->_0D8;
                if ((u8)fn_800639BC(i, &pos, &prev) >= 2) {
                    if (g_d_GameSettings.StadiumID == 4) {
                        vid = sndFXStartEx(lbl_3_data_81DC[4] + 7, g_d_GameSettings.GameModeSelected == 6 ? lbl_3_data_84B8[0xE] : lbl_3_data_8404[0x86], 0x3F, 0);
                        sndFXCtrl(vid, 0x5B, g_d_GameSettings.GameModeSelected == 6 ? lbl_3_data_84B8[0xF] : lbl_3_data_8404[0x87]);
                    } else if (g_d_GameSettings.StadiumID == 5) {
                        vid = sndFXStartEx(lbl_3_data_81DC[5] + 0xC, g_d_GameSettings.GameModeSelected == 6 ? lbl_3_data_84B8[0x18] : lbl_3_data_8404[0xAE], 0x3F, 0);
                        sndFXCtrl(vid, 0x5B, g_d_GameSettings.GameModeSelected == 6 ? lbl_3_data_84B8[0x19] : lbl_3_data_8404[0xAF]);
                    }
                }
            } else {
                fn_80063958(i);
            }
            if (kind == BALL_COLLISION_TYPE_ROUGH_TERRAIN) {
                fn_3_16D5E4(i + 1);
            }
            f->_010 = f->_00C;
        }
        if (f->_203 != 0) {
            f->_00C = f->_00C + f->_15C;
        }
        if (f->_205 != 0) {
            f->_00C = f->_148;
        }
        if (f->_207 != 0) {
            f->_00C = f->_148;
        }
        if (f->_252 == 4) {
            f->_00C = f->_148;
            if (f->_25C != 0) {
                f->_25E = 1;
            } else {
                f->_25E = 2;
            }
        } else if (f->_25E != 0) {
            if (f->_25E == 2) {
                f->_25E = 3;
                f->_14C = lbl_3_rodata_B20;
                f->_25D = 0;
                v = lbl_3_rodata_B80 * f->_164;
                h = f->_148;
                do {
                    v -= lbl_3_data_4930[11];
                    h += v;
                    f->_25D++;
                } while (!(h < lbl_3_rodata_B20));
                getComponentsFromSAng(f->_180, &f->_150, &f->_158);
                f->_150 = f->_150 * -lbl_3_data_4930[13];
                f->_158 = f->_158 * -lbl_3_data_4930[13];
            } else if (f->_25E == 3) {
                f->_25D--;
                f->_14C -= lbl_3_data_4930[11];
                f->_148 += f->_14C;
                if (f->_148 < 0.0f) {
                    f->_148 = 0.0f;
                    f->_25E = 4;
                    f->_25F = lbl_3_data_49DC[4];
                }
            }
            f->_00C = f->_148;
        }
        f->_1E6 = col;
    }
}

// .text:0x00054900 size:0x258 mapped:0x80693994
void fn_3_54900(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int m = g_RunningLogic._04;
    f32 x;
    f32 z;
    if (f->_1F5s >= 0) {
        x = lbl_3_data_4444[8];
        z = lbl_3_data_4444[9];
    } else if (g_RunningLogic._10 == 0) {
        f->_04C = f->_048;
        f->_1F2 = 1;
        return;
    } else {
        if (g_Ball.AtBat_ContactResult == 3) {
            m &= 0xFFF0;
        }
        switch (m) {
        case 0x1:
            x = lbl_3_data_4444[2];
            z = lbl_3_data_4444[3];
            break;
        case 0x10:
            x = 0.7f * lbl_3_data_4444[4] + 0.3f * lbl_3_data_4444[2];
            z = 0.7f * lbl_3_data_4444[5] + 0.3f * lbl_3_data_4444[3];
            break;
        case 0x100:
            x = 0.7f * lbl_3_data_4444[6] + 0.3f * lbl_3_data_4444[4];
            z = 0.7f * lbl_3_data_4444[7] + 0.3f * lbl_3_data_4444[5];
            break;
        case 0x11:
            x = lbl_3_rodata_B80 * (lbl_3_data_4444[2] + lbl_3_data_4444[4]);
            z = lbl_3_rodata_B80 * (lbl_3_data_4444[3] + lbl_3_data_4444[5]);
            break;
        case 0x110:
            x = lbl_3_rodata_B80 * (lbl_3_data_4444[4] + lbl_3_data_4444[6]);
            z = lbl_3_rodata_B80 * (lbl_3_data_4444[5] + lbl_3_data_4444[7]);
            break;
        case 0x111:
            x = 0.3f * lbl_3_data_4444[6] + 0.7f * lbl_3_data_4444[4];
            z = 0.3f * lbl_3_data_4444[7] + 0.7f * lbl_3_data_4444[5];
            break;
        case 0x101:
            x = lbl_3_data_4444[8];
            z = lbl_3_data_4444[9];
            break;
        default:
            x = lbl_3_data_4444[0];
            z = lbl_3_data_4444[1];
            break;
        }
    }
    f->_048 = atan2(z - f->z, x - f->x);
}

// .text:0x00054B58 size:0x818 mapped:0x80693BEC
// NONMATCHING 97%: base-table / stadium-point loads come out as add+lfs instead of lfsx
#if NONMATCHING
// choose fielder i's facing angle (f + 0x48)
void fn_3_54B58(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 toBall;
    f32 toCenter;
    f32 moveDir;
    f32 dx;
    f32 dz;
    f32 d;
    u8 b;
    u8 st;
    u8 mg;
    f32* p;
    if (!(g_Ball.framesSinceHit >= f->_1D2 || i == g_Ball.fielderWBallIndex || g_Minigame.GameMode_MiniGame == 5 || g_Minigame.GameMode_MiniGame == 6)) {
        return;
    }
    st = f->_1E3;
    if (st == 2 || (u8)(st - 3) <= 1 || st == 7 || st == 8) {
        return;
    }
    if (f->_1FE != 0) {
        return;
    }
    if (f->_1FD != 0 && f->_1F9 == 0) {
        if (f->_211 != 0) {
            b = f->_214;
            f->_048 = atan2(lbl_3_data_4444[((b + 3) & 3) * 2 + 1] - lbl_3_data_4444[b * 2 + 1],
                                      lbl_3_data_4444[((b + 3) & 3) * 2] - lbl_3_data_4444[b * 2]);
        } else if (g_FieldingLogic._0E8 >= 0 && f->_1AA <= 1) {
            p = &g_Runners[g_FieldingLogic._0E8].position.x;
            f->_048 = atan2(p[2] - f->z, p[0] - f->x);
        }
        return;
    }
    toBall = atan2(g_Ball.AtBat_Contact_BallPos.z - f->z, g_Ball.AtBat_Contact_BallPos.x - f->x);
    if (g_Ball.warioWaluGarlicIsActive != 0) {
        dz = g_Ball.warioStarHitCoords[2].z - f->z;
        dx = g_Ball.warioStarHitCoords[2].x - f->x;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        if (d < f->_080) {
            toBall = atan2(dz, dx);
        }
    }
    toCenter = atan2(lbl_3_data_4444[9] - f->z, lbl_3_data_4444[8] - f->x);
    if (f->_050 >= lbl_3_rodata_B48) {
        if (lbl_3_rodata_B20 == f->_030 && lbl_3_rodata_B20 == f->_034) {
            moveDir = f->_048;
        } else {
            moveDir = atan2(f->_034, f->_030);
        }
    } else {
        moveDir = f->_048;
    }
    if (f->_1FA != 0) {
        if (f->rosterID == g_GameLogic.Team_CaptainRosterLoc[g_GameLogic.teamFielding]) {
            f->_048 = toCenter;
        } else {
            p = ((f32 (*)[2][2])lbl_3_data_4290)[g_d_GameSettings.StadiumID][g_GameLogic.awayTeamBattingInd_battingTeam]; // [stadium][team] -> x, z
            f->_048 = atan2(p[1] - f->z, p[0] - f->x);
        }
        return;
    }
    if (f->_210 != 0) {
        f->_048 = shortAngleToRad_Capped(f->_1C2 + 0x800);
        return;
    }
    if (f->_252 == 3 || f->_25A == 2) {
        f->_048 = f->_140;
        return;
    }
    if (f->_252 == 4 && f->_25C != 0) {
        f->_048 = f->_140;
        return;
    }
    if (f->_25E != 0) {
        f->_048 = f->_144;
        f->_1FC = 1;
        return;
    }
    st = f->_205;
    if (st == 1 || st == 3 || st == 4) {
        f->_048 = atan2(f->_034, f->_030);
        f->_1FC = 1;
        return;
    }
    if (st == 2 || st == 5 || st == 6) {
        f->_048 = fn_3_9FEA8(lbl_3_rodata_CB0 + atan2(-f->_144, -f->_140));
        f->_1FC = 1;
        return;
    }
    if (f->_207 != 0) {
        f->_048 = fn_3_9FEA8(atan2(-f->_144, -f->_140));
        f->_1FC = 1;
        return;
    }
    if (f->_203 != 0) {
        f->_048 = moveDir;
        f->_1FC = 1;
        return;
    }
    if (f->_1ED != 0) {
        if (f->_1F9 == 0) {
            if (f->_255 == 1) {
                f->_048 = atan2(-f->_244, -f->_240);
                f->_1FC = 1;
            } else if (f->_1EE == 0) {
                f->_048 = moveDir;
            }
            return;
        }
        goto tag_pose;
    }
    {
        mg = g_Minigame.GameMode_MiniGame;
        if (mg == 5 && g_Minigame._1B34[g_Minigame.minigameControlStruct[0].fieldOrder[i - 2]] >= 0) {
            f->_048 = atan2(f->_114 - f->z, f->_10C - f->x);
            f->_1F2 = 0;
            return;
        }
        if (f->_1F9 != 0) {
        tag_pose: // fielder is tagging a runner
        if (g_Ball.ballState == 1) {
            if (f->_1F9 == 2) {
                f->_048 = atan2(f->_114 - f->z, f->_10C - f->x);
            } else if (g_Pitcher.pickOffLoc < 1 || g_Pitcher.pickOffLoc > 3) {
                f->_048 = atan2(f->_114 - f->z, f->_10C - f->x);
            }
        }
        f->_1F2 = 0;
        return;
        }
        {
            if (g_Strikes.outs >= 3 && f->_050 != lbl_3_rodata_B20 && g_d_GameSettings.GameModeSelected != 2) {
                p = ((f32 (*)[2][2])lbl_3_data_4290)[g_d_GameSettings.StadiumID][g_GameLogic.awayTeamBattingInd_battingTeam]; // [stadium][team] -> x, z
                f->_048 = atan2(p[1] - f->z, p[0] - f->x);
                return;
            }
            if (f->_256 == 1) {
                f->_048 = toBall;
                return;
            }
            if (f->_1A0 != 0 && (f->_050 >= lbl_3_rodata_B48 || f->_1A0 >= 3)) {
                f->_048 = moveDir;
                return;
            }
            if (g_Ball.fielderWBallIndex == i) {
                if (f->_1F8 >= 2) {
                    f->_048 = toCenter;
                } else {
                    fn_3_54900(i);
                }
                return;
            }
            if (mg == 5 || mg == 6) {
                f->_048 = toCenter;
                return;
            }
            if (g_Ball.ballState == 1 || g_Ball.ballState == 2) {
                if (i >= 6) {
                    f->_048 = toCenter;
                } else {
                    f->_048 = toBall;
                }
                return;
            }
            f->_048 = toBall;
            return;
        }
    }
}
#endif

// .text:0x00055370 size:0x23C mapped:0x80694404
void fn_3_55370(void) {
    int i;
    InMemFielderView* f;
    s16 v;
    f32 d;
    for (i = 0; i < 9; i++) {
        f = &g_Fielders[i];
        if (g_d_GameSettings.minigamesEnabled != 0 && g_Minigame.minigameRelatedIndex != i) {
            continue;
        }
        fn_3_54B58(i);
        f->_07C = fn_3_9CE0(f->x, f->z);
        if (0.0f == f->_050) {
            f->_038 = 0.0f;
            f->_03C = 0.0f;
        } else {
            f->_038 = f->_030 / f->_050;
            f->_03C = f->_034 / f->_050;
        }
        f->_1EA = 0;
        f->_217 = 0;

    }
    fn_3_544B8();
    if (g_d_GameSettings.minigamesEnabled != 0) {
        fn_3_53F48();
        return;
    }
    v = g_Ball.fielderWBallIndex;
    if (v >= 0) {
        g_Ball.AtBat_Contact_BallPos.x = g_Fielders[v].x;
        g_Ball.AtBat_Contact_BallPos.y = (&g_Fielders[0].y)[v * 0x9A];
        g_Ball.AtBat_Contact_BallPos.z = (&g_Fielders[0].z)[v * 0x9A];
        g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z = g_Ball.AtBat_Contact_BallPos.z;
        d = g_Ball.AtBat_Contact_BallPos.x * g_Ball.AtBat_Contact_BallPos.x + g_Ball.AtBat_Contact_BallPos.z * g_Ball.AtBat_Contact_BallPos.z;
        SQRT_L(d);
        g_Ball.ballDistanceFromHome = d;
    }
}

// .text:0x000555AC size:0x164 mapped:0x80694640
void fn_3_555AC(int i) {
    InMemFielderView* f = &g_Fielders[i];
    f32 lo;
    f32 hi;
    f->_1DE = 0;
    if ((f->z) > lbl_3_rodata_C18) {
        return;
    }
    if ((f->z) < lbl_3_rodata_C88) {
        return;
    }
    if ((f->x) > lbl_3_rodata_B90) {
        return;
    }
    if ((f->x) < lbl_3_rodata_CB8) {
        return;
    }
    if ((f->z) > lbl_3_data_4444[3]) {
        lo = lbl_3_data_4444[5] - lbl_3_rodata_B68;
        hi = lbl_3_rodata_B8C + lbl_3_data_4444[5];
        if ((f->x) > lbl_3_rodata_B20) {
            if ((f->z) > -(f->x) + lo && (f->z) < -(f->x) + hi) {
                f->_1DE = 2;
            }
        } else {
            if ((f->z) > (f->x) + lo && (f->z) < (f->x) + hi) {
                f->_1DE = 3;
            }
        }
    } else {
        lo = lbl_3_data_4444[1] - lbl_3_rodata_B8C;
        hi = lbl_3_rodata_B68 + lbl_3_data_4444[1];
        if ((f->x) > lbl_3_rodata_B20) {
            if ((f->z) > (f->x) + lo && (f->z) < (f->x) + hi) {
                f->_1DE = 1;
            }
        } else {
            if ((f->z) > -(f->x) + lo && (f->z) < -(f->x) + hi) {
                f->_1DE = 4;
            }
        }
    }
}

// .text:0x00055710 size:0x208 mapped:0x806947A4
void fn_3_55710(int i) {
    InMemFielderView* f = &g_Fielders[i];
    int sel = f->_1F5s;
    int k;
    InMemRunnerType* r;
    u8 t;
    if (g_FieldingLogic._116 != 0) {
        r = g_Runners;
        r += g_FieldingLogic._11B;
        if (r->baseStandingOn >= 0 || r->runnerOnFieldOrOutOrScored == 2) {
            g_FieldingLogic._116 = 0;
            g_FieldingLogic._0EC = 0;
        }
    } else {
        if (g_FieldingLogic._125 >= 0) {
            sel = g_FieldingLogic._125;
        }
        if (sel >= 0) {
            for (k = 3; k >= 0; k--) {
                r = &g_Runners[k];
                if (r->runnerOnFieldOrOutOrScored == 1 && r->forceOutCd <= 0 && r->baseRunningTowards == sel && r->tagUpInd == 0 && r->baseStandingOn < 0) {
                    t = r->actionCode;
                    if (t != 0) {
                        if (t == 2) {
                            f->_211 = 2;
                            f->_212 = 0;
                            g_FieldingLogic._116 = 2;
                            g_FieldingLogic._0EC = 6;
                            g_FieldingLogic._111 = 7;
                            g_FieldingLogic._13F = 2;
                            f->_213 = k;
                            if (g_GameLogic._13E[g_GameLogic.teamFielding] == 0) {
                                fn_3_6C854(g_GameLogic.teamFielding, 2);
                            }
                        } else if (t == 3) {
                            f->_211 = 1;
                            f->_212 = 0;
                            g_FieldingLogic._116 = 1;
                            g_FieldingLogic._0EC = r->actionFrames_countDown;
                            g_FieldingLogic._111 = 6;
                            g_FieldingLogic._13F = 1;
                            f->_213 = k;
                        } else {
                            s16 v = r->actionFrames_countDown;
                            if (v < 6) {
                                g_FieldingLogic._116 = 2;
                                g_FieldingLogic._0EC = 6;
                            } else {
                                g_FieldingLogic._116 = 1;
                                g_FieldingLogic._0EC = v;
                            }
                        }
                        g_FieldingLogic._11B = k;
                        return;
                    }
                }
            }
        }
    }
}

// .text:0x00055918 size:0x3AC mapped:0x806949AC
// NONMATCHING 98%: final 9-fielder loop lacks the original's leftover `i < 9` guard; scratch regs differ in the SetFielderAct2 inlines
#if NONMATCHING
void fn_3_55918(void) {
    int i;
    InMemFielderView* f;
    if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
        fn_3_41D78();
    }
    if (g_Strikes.outs >= 3 && g_d_GameSettings.GameModeSelected != 2) {
        for (i = 0; i < 9; i++) {
            f = &g_Fielders[i];
            if (f->_1D3 != 0x11 && (g_Ball.fielderWBallIndex != i || g_FieldingLogic._116 == 0) && f->_200 == 0 && i != -1) {
                SetFielderAct2(i, lbl_3_data_3C40[17].anim, 0x11);
            }
        }
    }
    if (g_Ball._1BDF >= 1 && g_Ball._1BDF <= 4) {
        for (i = 0; i < 9; i++) {
            if (i != -1) {
                SetFielderAct2(i, lbl_3_data_3C40[0].anim, 0);
            }
        }
    } else if (g_Ball.deadBallReason != 0) {
        for (i = 0; i < 9; i++) {
            f = &g_Fielders[i];
            if (((g_Ball._1BDF >= 1 && g_Ball._1BDF <= 4) || f->_1D3 != 0xF || g_Ball.deadBallReason == 0) && f->_1D3 != 0xC && f->_252 == 0 && i != -1) {
                SetFielderAct2(i, lbl_3_data_3C40[12].anim, 0xC);
            }
        }
    }
    if (g_FieldingLogic._0C6 >= 0) {
        if (g_FieldingLogic._0C8 < 0x7FFE) {
            g_FieldingLogic._0C8 = g_FieldingLogic._0C8 + 1;
        } else {
            g_FieldingLogic._0C8 = 0x7FFF;
        }
        if (g_FieldingLogic._0C8 > 0x1E) {
            g_FieldingLogic._0C6 = -1;
            g_FieldingLogic._0C8 = 0;
        }
    }
    if (g_FieldingLogic._0C4 >= 0) {
        if (g_Ball.ballState == 2) {
            g_FieldingLogic._0F0 = 0;
        } else if (g_FieldingLogic._0F0 < 0x7FFE) {
            g_FieldingLogic._0F0 = g_FieldingLogic._0F0 + 1;
        } else {
            g_FieldingLogic._0F0 = 0x7FFF;
        }
    } else {
        g_FieldingLogic._0F0 = 0;
    }
    if (g_FieldingLogic._12B != 0) {
        if (g_Ball.fielderWBallIndex < 0) {
            g_FieldingLogic._12B = 0;
        } else if (g_Fielders[g_Ball.fielderWBallIndex]._1F5s >= 0) {
            g_FieldingLogic._12B = 0;
        } else {
            g_FieldingLogic._12B = g_FieldingLogic._12B - 1;
        }
    }
    for (i = 0; i < 9; i++) {
        g_Fielders[i]._192 = 0xF;
    }
}
#endif

// .text:0x00055CC4 size:0x228 mapped:0x80694D58
void fn_3_55CC4(int i) {
    InMemFielderView* f = &g_Fielders[i];
    s16 v;
    u8 a;
    u8 b;
    if (f->_1E8 == 2 && g_Ball.fielderWBallIndex != i) {
        f->_1E8 = 0;
    }
    if (f->_050 <= lbl_3_rodata_B20) {
        f->_19A = -1;
        f->_1A0 = 0;
    } else {
        f->_19A = radToShortAngle(f->_064);
        if (f->_1A0 < 0x7FFE) {
            f->_1A0 = f->_1A0 + 1;
        } else {
            f->_1A0 = 0x7FFF;
        }
    }
    v = g_FieldingLogic._0DE;
    if (v >= 0 && f->_1C6 == 0 && g_Runners[v].runnerOnFieldOrOutOrScored != 1) {
        g_FieldingLogic._0DE = -1;
    }
    if (g_Ball.ballState == 1 || g_Ball.ballState == 2) {
        if (g_FieldingLogic._0DC >= 0 && g_FieldingLogic._0CC == 9) {
            v = g_FieldingLogic._0DE;
            if (v >= 0) {
                if ((&g_Runners[0].percentTowardsNextBase)[v * 0x55] >= lbl_3_rodata_BB8 && (&g_Runners[0].percentTowardsNextBase)[v * 0x55] <= lbl_3_rodata_CBC) {
                    g_FieldingLogic._0F4 = v;
                }
            }
        }
        v = g_FieldingLogic._0F4;
        if (v >= 0) {

            if (g_Runners[v].runnerOnFieldOrOutOrScored != 1 || g_Runners[v].baseStandingOn >= 0) {
                g_FieldingLogic._0F4 = -1;
            } else {
                a = g_Runners[v].currentBase;
                b = g_Runners[v].nextBase;
                if (g_FieldingLogic._0C4 != -1 && g_FieldingLogic._0C4 != a && g_FieldingLogic._0C4 != b) {
                    g_FieldingLogic._0F4 = -1;
                }
                if (g_FieldingLogic._0CC != -1 && g_FieldingLogic._0CC != 9 && g_FieldingLogic._0CC != a && g_FieldingLogic._0CC != b) {
                    g_FieldingLogic._0F4 = -1;
                }
            }
        }
    }
}

// .text:0x00055EEC size:0x1258 mapped:0x80694F80
// NONMATCHING 98.6%: s16 countdown tests use extsh. instead of cmpwi; float regs in the distance blocks differ
#if NONMATCHING
// per-frame bookkeeping for fielder i: timers, distances, facing history, hand-off to the state code
void fn_3_55EEC(int i) {
    InMemFielderView* f = &g_Fielders[i];
    s16 frame;
    f32 d;
    int k;
    f->_054 = f->_050;
    f->_040 = f->_030;
    f->_044 = f->_034;
    f->_1F0 = 0;
    f->_0D4 = f->x;
    f->_0D8 = f->z;
    f->_1F6 = f->_1F5;
    if (f->_1F5s >= 0) {
        f->_1F7 = f->_1F5;
    }
    g_FieldingLogic._135 = 0;
    if (!(g_Minigame.GameMode_MiniGame == 2 && g_Minigame.wallBallRotatePitchersInd == 1)) {
        f->_030 = lbl_3_rodata_B20;
        f->_034 = lbl_3_rodata_B20;
    }
    if (f->_1AC < 0x7FFE) {
        f->_1AC = f->_1AC + 1;
    } else {
        f->_1AC = 0x7FFF;
    }
    if (f->_1A8 != 0) {
        f->_1A8 = f->_1A8 - 1;
    }
    if (f->_1EE != 0) {
        f->_1EE--;
    }
    if (f->_1EF != 0) {
        f->_1EF--;
    }
    if (f->_252 == 0 && f->_262 != 0) {
        f->_262--;
    }
    if (f->_1B6 != 0) {
        f->_1B6 = f->_1B6 - 1;
    }
    if (f->_18A != 0) {
        if (f->_18A < 0x7FFE) {
            f->_18A = f->_18A + 1;
        } else {
            f->_18A = 0x7FFF;
        }
    }
    if (i == 0) {
        // pitcher: snap back onto the mound when the play resets
        if (f->_200 != 0) {
            g_FieldingLogic._117 = 0;
        }
        frame = g_Ball.framesSinceHit;
        if ((frame == f->_1D2 && g_GameLogic.gameStatus == 2) || (f->_1E5 >= 5 && f->_1E5 <= 9 && frame <= 1 && g_GameLogic.gameStatus == 2) ||
            (g_FieldingLogic._107 != 0 && frame <= 0x65)) {
            if (!(g_Ball.lineDriveThroughPitcherInd != 0 && frame < f->_1D2) && g_FieldingLogic._117 != 0) {
                f->x = g_Pitcher.pitcherCoord.x;
                f->z = g_Pitcher.pitcherCoord.z;
                g_FieldingLogic._117 = 0;
                g_Pitcher.unused_pitcherIsFielder = 1;
            }
        }
    }
    if (i == 1 && g_d_GameSettings.minigamesEnabled == 0 && g_FieldingLogic._118 != 0) {
        // catcher: decide whether he still has to cover home
        frame = g_Ball.framesSinceHit;
        if ((frame > g_Fielders[1]._1D2 || g_FieldingLogic._107 == 3) && (frame > 0x91 || g_FieldingLogic._107 != 3)) {
            if (g_FieldingLogic._107 != 0) {
                frame -= 0x64;
            }
            if (frame < 0x78) {
                if (g_Runners[3].runnerOnFieldOrOutOrScored == 1 && g_Runners[3].fractionalBasesRan >= lbl_3_rodata_CC0) {
                    g_FieldingLogic._118 = 0;
                } else if (g_Fielders[1]._1D3 != 1) {
                    g_FieldingLogic._118 = 0;
                }
                if (g_FieldingLogic._0C4 == 0) {
                    g_FieldingLogic._118 = 0;
                }
            } else {
                g_FieldingLogic._118 = 0;
            }
        }
    }
    d = f->x * f->x + f->z * f->z;
    SQRT_L(d);
    f->_070 = d;
    f->distToBase[0] = f->_070;
    for (k = 1; k < 4; k++) {
        d = (lbl_3_data_4444[k * 2] - f->x) * (lbl_3_data_4444[k * 2] - f->x) +
            (lbl_3_data_4444[k * 2 + 1] - f->z) * (lbl_3_data_4444[k * 2 + 1] - f->z);
        SQRT_L(d);
        f->distToBase[k] = d;
    }
    d = (lbl_3_data_4444[8] - f->x) * (lbl_3_data_4444[8] - f->x) +
        (lbl_3_data_4444[9] - f->z) * (lbl_3_data_4444[9] - f->z);
    SQRT_L(d);
    f->_0B8 = d;
    f->_1F8 = FieldZoneInl(f->x, f->z);
    f->_078 = f->_074;
    d = (g_Ball.AtBat_Contact_BallPos.x - f->x) * (g_Ball.AtBat_Contact_BallPos.x - f->x) + (g_Ball.AtBat_Contact_BallPos.z - f->z) * (g_Ball.AtBat_Contact_BallPos.z - f->z);
    SQRT_L(d);
    f->_074 = d;
    if (g_Ball.AtBat_ContactResult == 0) {
        d = (g_Ball.landingSpotLocation.x - f->x) * (g_Ball.landingSpotLocation.x - f->x) +
            (g_Ball.landingSpotLocation.z - f->z) * (g_Ball.landingSpotLocation.z - f->z);
        SQRT_L(d);
        f->_080 = d;
    }
    f->_180 = fn_3_9FB8C(f->x, f->z);
    f->_06C = game_atan2(f->x, f->z);
    // pairwise fielder distances (symmetric table at +0x84)
    f->distToFielder[i] = lbl_3_rodata_B20;
    for (k = i + 1; k < 9; k++) {
        d = (g_Fielders[k].x - f->x) * (g_Fielders[k].x - f->x) +
            (g_Fielders[k].z - f->z) * (g_Fielders[k].z - f->z);
        SQRT_L(d);
        f->distToFielder[k] = d;
        g_Fielders[k].distToFielder[i] = f->distToFielder[k];
    }
    f->_0CC = f->_0C8;
    f->_0C8 = f->_0C4;
    f->_0C4 = f->_0C0;
    f->_0C0 = f->_0BC;
    f->_0BC = f->_064;
    if (g_d_GameSettings.minigamesEnabled == 0) {
        if (g_Ball.fielderWBallIndex == i) {
            fn_3_55710(i);
        }
        CornerZoneInl(i);
    }
    if (f->_252 != 0) {
        fn_3_27860(i);
    } else {
        fn_3_2C698(i);
    }
    d = (f->_014 - f->x) * (f->_014 - f->x) + (f->_01C - f->z) * (f->_01C - f->z);
    SQRT_L(d);
    f->_068 = d;
    if (g_Ball.framesSinceHit < f->_1D2 || f->_1ED != 0) {
        f->_1E2 = 1;
    } else {
        f->_1E2 = 0;
    }
    if (g_Ball.AtBat_ContactResult == -1 && f->_1C5 != 0) {
        SetFielderAct(i, 0x13);
    }
    if (g_Ball.framesSinceHit > 0x3C && g_Ball.lineDriveThroughPitcherInd != 0) {
        g_Ball.lineDriveThroughPitcherInd = 2;
    }
    f->_1E5 = 1;
    if (g_Strikes.outs >= 3) {
        f->_1E5 = 4;
    } else if (g_RunningLogic._10 == 0 || g_Ball.AtBat_ContactResult == -1 || g_Ball.deadBallReason != 0) {
        f->_1E5 = 0;
    } else if (g_Ball.fielderWBallIndex == i) {
        f->_1E5 = 3;
    } else if (g_FieldingLogic._0F8[i] == 1 || g_FieldingLogic._0F8[i] == 0xA) {
        if (g_Ball.AtBat_ContactResult == 0) {
            f->_1E5 = 2;
        } else if (g_Ball.ballVelocity > lbl_3_rodata_BB8) {
            f->_1E5 = 2;
        }
    } else if (g_Ball.ballState == 1 || g_Ball.ballState == 2) {
        if (g_Ball.ballZoneAwayFromHome <= 1) {
            if (i >= 6) {
                f->_1E5 = 0;
            } else if (f->_18C < 0) {
                f->_1E5 = 0;
            }
        }
    } else if (g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 7 || g_GameLogic.gameStatus == 0 ||
               (g_GameLogic.gameStatus == 2 && g_Ball.framesSinceHit < 0x3C)) {
        f->_1E5 = 2;
    }
}
#endif

// .text:0x00057144 size:0x344 mapped:0x806961D8
void fn_3_57144(void) {
    int i;
    InMemFielderView* f;
    f32 d;
    s16 idx;
    if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0 && g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow == 0x14) {
        fn_3_4197C(1);
    }
    if (g_FieldingLogic._123 != 0 && g_Ball.AtBat_ContactResult != 0) {
        g_FieldingLogic._123 = 0;
    }
    if (g_FieldingLogic._124 != 0) {
        g_FieldingLogic._124--;
    }
    fn_3_51220();
    for (i = 0; i < 9; i++) {
        f = &g_Fielders[i];
        fn_3_55EEC(i);
        lbl_3_data_3C40[f->_1D3].update(i);
        fn_3_55CC4(i);
    }
    if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
        fn_3_4EBC4();
    } else {
        idx = g_FieldingLogic._0B0;
        f = &g_Fielders[idx];
        if (g_FieldingLogic._0C4 >= 0) {
            g_Ball.fielderAboutToGetBall_hasBall = -1;
        } else if (idx >= 0 && g_Ball.looseBall_5FrameCountdown == 0) {
            if (g_Ball.AtBat_ContactResult == 0) {
                if (f->_080 < lbl_3_rodata_B64) {
                    g_Ball.fielderAboutToGetBall_hasBall = idx;
                } else {
                    g_Ball.fielderAboutToGetBall_hasBall = -1;
                }
            } else {
                d = (f->x - g_Ball.physicsSubstruct.futureCoordsAndDist[1].pos.x) * (f->x - g_Ball.physicsSubstruct.futureCoordsAndDist[1].pos.x) +
                    (f->z - g_Ball.physicsSubstruct.futureCoordsAndDist[1].pos.z) * (f->z - g_Ball.physicsSubstruct.futureCoordsAndDist[1].pos.z);
                SQRT_L(d);
                if (d <= f->_074) {
                    if (fn_3_9CE0(f->x, f->z) < f->reach[0]) {
                        g_Ball.fielderAboutToGetBall_hasBall = g_FieldingLogic._0B0;
                    } else {
                        g_Ball.fielderAboutToGetBall_hasBall = -1;
                    }
                }
            }
            if (g_Ball.fielderAboutToGetBall_hasBall >= 0) {
                g_Ball.ballIsLooseInd_unused = 0;
                g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt = 0;
                g_Ball.fielderBeingThrownTo = -1;
            }
        }
    }
    if (g_Ball.framesSinceHit > 5) {
        fn_3_45E98();
        fn_3_4BA0C();
        fn_3_49F3C();
    }
    fn_3_55918();
}

// .text:0x00057488 size:0x22C mapped:0x8069651C
void fn_3_57488(void) {
    s16 idx = g_FieldingLogic._0B0;
    u8 mg = g_d_GameSettings.minigamesEnabled;
    int k = idx;
    InMemFielderView* f;
    f32 d;
    if (mg != 0) {
        k = g_Minigame.minigameRelatedIndex;
    }
    f = &g_Fielders[k];
    if (g_AiLogic._78 != 0) {
        goto set;
    }
    if (g_Ball.ballState == 3) {
        goto set;
    }
    if (g_Ball.ballState == 0) {
        if (g_Ball.hitWallInd != 0 || g_Ball.ballStoppingCode1ReallySlow2Stopped != 0) {
            goto set;
        }
        if (idx >= 6 || mg != 0) {
            d = f->_020 * f->_020 + f->_024 * f->_024;
            SQRT_L(d);
            if (d > lbl_3_rodata_BA0 && g_Ball.ballDistanceFromHome > d) {
                goto set;
            }
        }
    }
    if (f->_020 > lbl_3_rodata_BFC) {
        fn_3_43038(g_FieldingLogic._0B0);
        f->_020 = f->_014;
        f->_024 = f->_01C;
    }
    return;
set:
    g_AiLogic._78 = 1;
    f->_020 = g_Ball.physicsSubstruct.futureCoordsAndDist[0xf].pos.x;
    f->_024 = g_Ball.physicsSubstruct.futureCoordsAndDist[0xf].pos.z;
}

// .text:0x000576B4 size:0x360 mapped:0x80696748
// NONMATCHING 97%: the inlined dive-start helper (same body as fn_3_258D8) schedules its table loads differently (lfsx vs lfs) and swaps some regs
#if NONMATCHING
void fn_3_576B4(int i) {
    InMemFielderView* f = &g_Fielders[i];
    FieldingPadRec* st = g_FieldingLogic.curPadRec;
    s16 t;
    f32 lim;
    f32 reach;
    int k;
    int type;
    u8* base;
    int off;
    f32* e;
    Ent16* t16;
    f32 sc;
    int n;
    if (st->_4 != 0 && g_Ball.ballState == 0 && g_Ball.framesSinceHit >= f->_1D2 + 3) {
        st->_3 = 0;
        if (g_Ball.AtBat_ContactResult == 0 && g_Ball.maxYOfHit > lbl_3_rodata_B64) {
            t = g_Ball.framesUntilBallHitsGround;
            if (t < lbl_3_data_4924[0] && t > 0x14) {
                reach = f->_050 * (f32)(t - 1);
                if (!(reach - lbl_3_rodata_B60 > f->_080)) {
                    t = f->_184;
                    if (t > 0 && f->_068 < lbl_3_rodata_B60 && g_Ball.physicsSubstruct.futureCoordsAndDist[t].pos.y <= f->reach[3]) {
                        return;
                    }
                    if (i <= 5) {
                        g_FieldingLogic.curPadRec->_2 = 2;
                    } else {
                        g_FieldingLogic.curPadRec->_2 = 2;
                        g_FieldingLogic.curPadRec->_3 = 1;
                    }
                }
            }
        } else if (i >= 2 && i <= 5) {
            if (f->_07C < f->reach[0]) {
                lim = f->_070 - lbl_3_rodata_B60;
                if (!(g_Ball.ballDistanceFromHome > lim)) {
                    for (k = 6; k <= 30; k += 2) {
                        if (g_Ball.physicsSubstruct.futureCoordsAndDist[k].dist > lim) {
                            break;
                        }
                    }
                    if (k <= 30 && g_Ball.physicsSubstruct.futureCoordsAndDist[k].pos.y > f->reach[3]) {
                        g_FieldingLogic.curPadRec->_2 = 2;
                        StartDiveInl(i);
                    }
                }
            } else {
                g_FieldingLogic.curPadRec->_2 = 2;
            }
        }
    }
}
#endif

// .text:0x00057A14 size:0x1A0 mapped:0x80696AA8
void fn_3_57A14(void) {
    int first;
    int second;
    f32 d1;
    f32 d2;
    int i;
    if (g_Ball.fielderWBallIndex >= 0) {
        g_FieldingLogic._0B0 = g_Ball.fielderWBallIndex;
        return;
    }
    if (g_Ball.ballState == 2) {
        g_FieldingLogic._0B0 = g_Ball.fielderBeingThrownTo;
        return;
    }
    d1 = d2 = lbl_3_rodata_BA4;
    second = -1;
    first = -1;
    for (i = 1; i < 9; i++) {
        InMemFielderView* f = &g_Fielders[i];
        if (f->_1D3 == 2 || f->_1D3 == 3) {
            if (f->_07C < d2) {
                if (f->_07C < d1) {
                    d2 = d1;
                    second = first;
                    d1 = f->_07C;
                    first = i;
                } else {
                    d2 = f->_07C;
                    second = i;
                }
            }
        }
    }
    if (first >= 0) {
        g_FieldingLogic._0B0 = first;
    } else if (g_Fielders[0]._1D3 == 2 || g_Fielders[0]._1D3 == 3 || g_Fielders[0]._1D3 == 4) {
        g_FieldingLogic._0B0 = 0;
    }
    if (second >= 0) {
        g_FieldingLogic._0B2 = second;
    }
    if (g_FieldingLogic._0B0 >= 0) {
        fn_3_576B4(g_FieldingLogic._0B0);
    }
}

// .text:0x00057BB4 size:0x804 mapped:0x80696C48
// NONMATCHING 99%: registers only; the sqrt temps inside the inlined SetTargetAC8 use f2/f3/f4 rotated
#if NONMATCHING
// steer the active fielder toward the ball / its catch point and record the input angle history
void fn_3_57BB4(void) {
    int k = g_FieldingLogic._0B0;
    InMemFielderView* f;
    f32 x;
    f32 z;
    f32 d;
    f32 t;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        k = g_Minigame.minigameRelatedIndex;
    }
    if (k < 0) {
        return;
    }
    f = &g_Fielders[k];
    if (g_Ball.framesSinceHit < f->_1D2) {
        return;
    }
    fn_3_57488();
    if (g_Ball.pauseBallMovementWhenInPlant != 0) {
        x = g_Ball.AtBat_Contact_BallPos.x - f->x;
        z = g_Ball.AtBat_Contact_BallPos.z - f->z;
        d = x * x + z * z;
        SQRT_L(d);
        if (d < lbl_3_data_4930[37]) {
            SetTargetAC8(k, f->x, f->z);
        } else {
            t = lbl_3_data_4930[36] - lbl_3_rodata_B60;
            x = t * (x / d) + f->x;
            z = t * (z / d) + f->z;
            SetTargetAC8(k, x, z);
        }
        f->_020 = f->_014;
        f->_024 = f->_01C;
    } else if (f->_18A != 0) {
        fn_3_50DD8(k, &x, &z, 1);
        SetTargetAC8(k, x, z);
        f->_020 = f->_014;
        f->_024 = f->_01C;
    }
    x = f->_020 - f->x;
    z = f->_024 - f->z;
    d = x * x + z * z;
    SQRT_L(d);
    if (!(d < lbl_3_rodata_B80)) {
        if (f->_1B6 == 0 && (f32)lbl_3_data_49DC[0x19] * f->maxVelocity < d) {
            g_FieldingLogic.padButtons[0] |= 0x200;
        }
        lbl_3_bss_170 = fn_3_9FB8C(x, z);
    }
    lbl_3_bss_16C = lbl_3_bss_170;
}
#endif

// .text:0x000583B8 size:0x2D0 mapped:0x8069744C
// NONMATCHING 99%: r28/r29 (fielder ptr / index) swapped in the fielder loop; the loop is fn_3_55370's body, duplicated
#if NONMATCHING
void fn_3_583B8(void) {
    s16* p;
    int k;
    int i;
    InMemFielderView* f;
    s16 v;
    f32 d;
    p = &lbl_3_bss_170 + 0x13;
    for (k = 0x13; k != 0; k--) {
        *p = -1;
        p--;
    }
    lbl_3_bss_170 = -1;
    lbl_3_bss_16C = -1;
    g_FieldingLogic.padButtons[0] = 0;
    g_FieldingLogic.padButtons[1] = 0;
    g_FieldingLogic.padButtons[2] = 0;
    if (g_Ball.framesSinceHit <= 0) {
        return;
    }
    if (g_Ball.framesSinceHit == 1) {
        fn_3_411AC();
    } else {
        if (g_FieldingLogic._13B != 0) {
            fn_3_3F034();
            g_FieldingLogic._13B = 0;
        }
        fn_3_57A14();
        fn_3_57144();
    }
    for (i = 0; i < 9; i++) {
        f = &g_Fielders[i];
        if (g_d_GameSettings.minigamesEnabled != 0 && g_Minigame.minigameRelatedIndex != i) {
            continue;
        }
        fn_3_54B58(i);
        f->_07C = fn_3_9CE0(f->x, f->z);
        if (0.0f == f->_050) {
            f->_038 = 0.0f;
            f->_03C = 0.0f;
        } else {
            f->_038 = f->_030 / f->_050;
            f->_03C = f->_034 / f->_050;
        }
        f->_1EA = 0;
        f->_217 = 0;
    }
    fn_3_544B8();
    if (g_d_GameSettings.minigamesEnabled != 0) {
        fn_3_53F48();
        return;
    }
    v = g_Ball.fielderWBallIndex;
    if (v >= 0) {
        g_Ball.AtBat_Contact_BallPos.x = g_Fielders[v].x;
        g_Ball.AtBat_Contact_BallPos.y = (&g_Fielders[0].y)[v * 0x9A];
        g_Ball.AtBat_Contact_BallPos.z = (&g_Fielders[0].z)[v * 0x9A];
        g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z = g_Ball.AtBat_Contact_BallPos.z;
        d = g_Ball.AtBat_Contact_BallPos.x * g_Ball.AtBat_Contact_BallPos.x + g_Ball.AtBat_Contact_BallPos.z * g_Ball.AtBat_Contact_BallPos.z;
        SQRT_L(d);
        g_Ball.ballDistanceFromHome = d;
    }
}
#endif

// .text:0x00058688 size:0x1E8 mapped:0x8069771C
void fn_3_58688(void) {
    s32 i;
    g_FieldingLogic._0CE = g_FieldingLogic._0CC;
    g_FieldingLogic._0E0 = g_FieldingLogic._0DE;
    if (g_Ball.looseBall_5FrameCountdown != 0) {
        g_Ball.looseBall_5FrameCountdown--;
    }
    for (i = 0; i < 9; i++) {
        g_Fielders[i]._1FC = 0;
        g_Fielders[i]._257 = g_Fielders[i]._256;
        g_Fielders[i]._256 = 0;
        g_Fielders[i]._20C = g_Fielders[i]._20B;
        g_Fielders[i]._20B = 0;
        g_Fielders[i]._216 = 0;
        g_Fielders[i]._263 = 0;
    }
    if (g_Ball.framesSinceHit == 1 || (g_Ball.framesSinceHit == 0x65 && g_FieldingLogic._107 != 0)) {
        for (i = 0; i < 9; i++) {
            g_Fielders[i]._118 = g_Fielders[i].x;
            g_Fielders[i]._11C = g_Fielders[i].z;
        }
    }
    g_FieldingLogic.padRec[0]._2 = 0;
    g_FieldingLogic.padRec[1]._2 = 0;
    g_FieldingLogic.padRec[2]._2 = 0;
    g_FieldingLogic.padRec[3]._2 = 0;
    g_FieldingLogic._144 = 0;
    g_Ball.fielderActionOccuring = 0;
    g_Pitcher.unused_pitcherIsFielder = 0;
    if (g_FieldingLogic._146 != 0) {
        g_FieldingLogic._146--;
    }
}

// .text:0x00058870 size:0x5E0 mapped:0x80697904
// NONMATCHING 88%: fielder loop regs differ, minigame flag checks unrolled differently, and the 20-entry history fill lacks the original's leftover loop guard
#if NONMATCHING
// reset all fielder and fielding-logic state for a new play
void fn_3_58870(void) {
    int i;
    int k;
    InMemFielderView* f;
    FieldingBoost* e;
    s8 v;
    f32 zero;
    if (g_d_GameSettings.minigamesEnabled == 0) {
        fn_3_591AC();
    }
    zero = lbl_3_rodata_B20;
    for (i = 0; i < 9; i++) {
        f = &g_Fielders[i];
        f->_18C = -1;
        f->_1D7 = 0;
        f->_1D8 = 0;
        f->_1D3 = 0;
        f->_1DD = 0;
        f->_17E = -1;
        f->_190 = -1;
        f->_1D5 = 0;
        f->_1D6 = 0;
        f->_192 = 0xF;
        f->_194 = 0;
        f->_1DF = 0;
        f->_198 = 0;
        f->_1E0 = 0;
        f->_1DB = 0;
        f->_1DC = 0;
        f->_19C = 0;
        f->_1EA = 0;
        f->_1E9 = 0;
        f->_1EC = 0;
        f->_1ED = 0;
        f->_1EE = 0;
        f->_1EF = 0;
        f->_1E1 = 0;
        f->_1E3 = 1;
        f->_1E4 = 0;
        f->_050 = zero;
        f->_060 = zero;
        f->_1A0 = 0;
        f->_1F2 = 0;
        f->_1E7 = 0;
        f->_1F3 = 0;
        f->_1F4 = 0;
        f->_1F5 = -1;
        f->_1F7 = -1;
        f->_1F9 = 0;
        f->_1FA = 0;
        f->_1A8 = 0;
        f->_1FC = 1;
        f->_200 = 0;
        f->_201 = 0;
        f->_202 = 0;
        f->_203 = 0;
        f->_205 = 0;
        f->_207 = 0;
        f->_148 = zero;
        f->_208 = 0;
        f->_209 = 0;
        f->_1B6 = 0;
        f->_20B = 0;
        f->_20C = 0;
        f->_18A = 0;
        f->_20F = 0;
        f->_1FD = 0;
        f->_1FE = 0;
        f->_215 = 0;
        f->_216 = 0;
        f->_210 = 0;
        f->_211 = 0;
        f->_212 = 0;
        f->_250 = 0;
        f->_252 = 0;
        f->_25B = 0;
        f->_256 = 0;
        f->_258 = 0;
        f->_259 = 0;
        f->_25A = 0;
        f->_25C = 0;
        f->_25E = 0;
        f->_25F = 0;
        f->_262 = 0;
        f->_263 = 0;
        f->_260 = 0;
        f->_265 = 0;
        f->_252 = 0;
        f->_1C5 = 0;
        g_FieldingLogic._0F8[i] = 0;
        f->_1C6 = 0;
        if (g_d_GameSettings.minigamesEnabled == 0) {
            fn_3_5372C(i);
            if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
                f->_1C5 = 1;
            }
            if (g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
                f->_1C6 = 1;
            }
        }
    }
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (g_Minigame.minigamePlayerSelectedOrder >= 0) {
            if (g_Minigame.minigameControlStruct[0].battingHandedness[g_Minigame.minigamePlayerSelectedOrder] != 0) {
                g_Fielders[0]._1C5 = 1;
                g_Fielders[0]._1C6 = 1;
            }
        } else if (g_Minigame.minigameControlStruct[0].fieldOrder[0] >= 0 && g_Minigame.minigameControlStruct[0].battingHandedness[g_Minigame.minigameControlStruct[0].fieldOrder[0]] != 0) {
            g_Fielders[2]._1C5 = 1;
            g_Fielders[2]._1C6 = 1;
        }
        for (i = 3; i < 6; i++) {
            v = g_Minigame.minigameControlStruct[0].fieldOrder[i - 2];
            if (v >= 0 && g_Minigame.minigameControlStruct[0].battingHandedness[v] != 0) {
                g_Fielders[i]._1C5 = 1;
                g_Fielders[i]._1C6 = 1;
            }
        }
    }
    for (k = 0; k < 5; k++) {
        g_FieldingLogic._0D0[k] = -1;
        g_FieldingLogic._101[k] = 0;
    }
    g_FieldingLogic._0B0 = -1;
    g_FieldingLogic._0B2 = -1;
    g_FieldingLogic._0B4 = -1;
    g_FieldingLogic._0BC = -1;
    g_FieldingLogic._0BE = -1;
    g_FieldingLogic._0C2 = -1;
    g_FieldingLogic._0C4 = -1;
    g_FieldingLogic._0C6 = -1;
    g_FieldingLogic._0CA = -1;
    g_FieldingLogic._0CC = -1;
    g_FieldingLogic._0DA = 0;
    g_FieldingLogic._0DE = -1;
    g_FieldingLogic._0DC = -1;
    g_FieldingLogic._0E2 = -1;
    g_FieldingLogic._0E8 = -1;
    g_FieldingLogic._0EA = -1;
    g_FieldingLogic._0EC = 0;
    g_FieldingLogic._0F0 = 0;
    g_FieldingLogic._0F2 = 0;
    g_FieldingLogic._107 = 0;
    g_FieldingLogic._108 = 0;
    g_FieldingLogic._10A = 0;
    g_FieldingLogic._111 = 0;
    g_FieldingLogic._10D = 0;
    g_FieldingLogic._113 = 0;
    g_FieldingLogic._114 = 0;
    g_FieldingLogic._116 = 0;
    g_FieldingLogic._117 = 1;
    g_FieldingLogic._118 = 1;
    g_FieldingLogic._11A = 0;
    g_FieldingLogic._11C = 0;
    g_FieldingLogic._11F = 0;
    g_FieldingLogic._120 = 0;
    g_FieldingLogic._115 = -1;
    g_FieldingLogic.throwSpeedType = 0;
    g_FieldingLogic._11D = 0;
    g_FieldingLogic._121 = -1;
    g_FieldingLogic._122 = 0;
    g_FieldingLogic._124 = 0;
    g_FieldingLogic._125 = -1;
    g_FieldingLogic._126 = -1;
    g_FieldingLogic._127 = 0;
    g_FieldingLogic._12A = 0;
    g_FieldingLogic._12B = 0;
    g_FieldingLogic._12C = 0;
    g_FieldingLogic._12D = 1;
    g_FieldingLogic._12E = 0;
    g_FieldingLogic._12F = 0;
    g_FieldingLogic._132 = 0;
    g_FieldingLogic._131 = 0;
    g_FieldingLogic._0F4 = -1;
    g_FieldingLogic._133 = 0;
    g_FieldingLogic._135 = 0;
    g_FieldingLogic._138 = 0;
    g_FieldingLogic._139 = 0;
    g_FieldingLogic._13A = 0;
    g_FieldingLogic._13B = 0;
    g_FieldingLogic._13F = 0;
    g_FieldingLogic._0F6 = 0;
    g_FieldingLogic._130 = 0;
    g_FieldingLogic._13E = 0;
    g_FieldingLogic._140 = 0;
    g_FieldingLogic._142 = 0;
    g_FieldingLogic._141 = 0;
    g_FieldingLogic._143 = 0;
    g_FieldingLogic._134 = -1;
    g_FieldingLogic._145 = 0;
    g_FieldingLogic._146 = 0;
    g_FieldingLogic._0C0 = 0;
    for (k = 0; k < 4; k++) {
        e = &g_FieldingLogic.boost[k];
        e->timer = -1;
        e->timer2 = -1;
        e->power = 0;
        e->frames = 0;
        e->fielder = -1;
        e->state = 0;
    }
    g_FieldingLogic.curBoost = g_FieldingLogic.boost;
    g_FieldingLogic.curPadRec = g_FieldingLogic.padRec;
    g_AiLogic._78 = 0;
    for (k = 0; k < 20; k++) {
        (&lbl_3_bss_170)[k] = -1;
    }
    lbl_3_bss_16C = -1;
    if (g_d_GameSettings.minigamesEnabled == 0) {
        int* slot = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0];
        if (slot[0] >= 9) {
            if (slot[1] >= 20) {
                slot[1] -= 20;
            } else if (slot[1] >= 10) {
                slot[1] -= 10;
            }
        }
        g_Pitcher.unused_pitcherIsFielder = 0;
    }
}
#endif

// .text:0x00058E50 size:0x108 mapped:0x80697EE4
void fn_3_58E50(void) {
    u8* m;
    int i;
    g_GameLogic.rosterLoc_skippingCap = 0;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        // m steps one byte per player: the [0] byte fields below are player i's
        m = (u8*)&g_Minigame;
        for (i = 0; i < 4; i++) {
            int v = (u8)((MiniGameStruct*)m)->minigameControlStruct[0].fieldOrder[0];
            if ((s8)v >= 0) {
                int idx = ((s8)v == (s8)((u8)g_Minigame.minigamePlayerSelectedOrder)) ? 0 : i + 2;
                InMemFielderView* f;
                fn_3_6E24C((s8)v, idx);
                f = &g_Fielders[idx];
                if (idx == 0) {
                    f->_1D2 = lbl_3_data_46F8[((MiniGameStruct*)m)->minigameControlStruct[0].battingHandedness[0] * 9];
                } else {
                    f->_1D2 = lbl_3_data_46F8[((MiniGameStruct*)m)->minigameControlStruct[0].battingHandedness[0] * 9 + 7];
                }
            }
            m++;
        }
    }
}

// .text:0x00058F58 size:0x254 mapped:0x80697FEC
// 99%: only reg swap (mulli/slwi dest r6/r7) in final table lookup
void fn_3_58F58(int n, f32* x, f32* z) {
    int flag = 0;
    int k;
    int sel;
    s16 p = g_Pitcher.pitchTotalTimeCounter;
    k = ((p > 0) ? 0 : -1) + 2;
    if (n <= 1) {
        *x = lbl_3_data_450C[n][0];
        *z = lbl_3_data_450C[n][1];
        return;
    }
    if (n <= 5) {
        u8 r = g_Runners[1].runnerOnFieldOrOutOrScored;
        if (r != 0 && g_Runners[1].furthestBaseForcedToGoToOnWalk != 0 && g_Ball.pitchHangtimeCounter > 0
            && g_Pitcher.framesUntilUnhittable < 15) {
            if (g_Batter.batterHand == 0 && n == 3) {
                *x = lbl_3_data_4444[4];
                *z = lbl_3_data_4444[5];
                return;
            }
            if (g_Batter.batterHand != 0 && n == 5) {
                *x = lbl_3_data_4444[4];
                *z = lbl_3_data_4444[5];
                return;
            }
        }
        sel = 0;
        if (p > 0x1E && (n == 2 || n == 4) && g_Batter.buntStatus >= 1 && g_Batter.buntStatus <= 3) {
            flag = 1;
        }
        if ((n == 2 && r == 1) || (n == 4 && g_Runners[3].runnerOnFieldOrOutOrScored == 1)) {
            sel = k;
        }
        if (g_Runners[2].runnerOnFieldOrOutOrScored == 1) {
            if (n == 3 && g_Batter.batterHand == 0) {
                sel = k;
                g_FieldingLogic._11E = 0;
            }
            if (n == 5 && g_Batter.batterHand == 1) {
                sel = k;
                g_FieldingLogic._11E = 1;
            }
        }
        if (flag != 0) {
            *x = lbl_3_data_45B4[n - 2][0];
            *z = lbl_3_data_45B4[n - 2][1];
            return;
        }
        *x = lbl_3_data_4554[n - 2][sel][0];
        *z = lbl_3_data_4554[n - 2][sel][1];
        return;
    }
    *x = lbl_3_data_45D4[n - 6][0];
    *z = lbl_3_data_45D4[n - 6][1];
}

// .text:0x000591AC size:0x18C mapped:0x80698240
void fn_3_591AC(void) {
    f32 spC;
    f32 sp8;
    InMemFielderView* f2;
    int j;
    int i;
    for (i = 0; i < 9; i++) {
        f2 = &g_Fielders[i];
        if (g_GameLogic.pre_PostMiniGameInd != 0) {
            fn_3_58F58(i, &spC, &sp8);
            f2->x = spC;
            f2->z = sp8;
        }
        f2->_014 = 0.0f;
        f2->_018 = 0.0f;
        f2->_01C = 0.0f;
        f2->_030 = 0.0f;
        f2->_034 = 0.0f;
        f2->_0D4 = f2->x;
        f2->_0D8 = f2->z;
        f2->_050 = 0.0f;
        f2->_1D9 = 0;
        f2->_1F5s = -1;
        f2->_20F = 0;
        spC = -f2->x;
        sp8 = -f2->z;
        f2->_048 = atan2(sp8, spC);
    }
    if (g_GameLogic.pre_PostMiniGameInd != 0) {
        for (j = 0; j < 9; j++) {
            f2 = &g_Fielders[j];
            fn_3_58F58(j, (f32*)f2, &f2->z);
            f2->y = 0.0f;
        }
    }
    if (g_Runners[1].runnerOnFieldOrOutOrScored == 1) {
        g_Fielders[2]._18C = 1;
        g_Fielders[2]._1D7 = 1;
        g_Fielders[2]._1F5 = 1;
        g_FieldingLogic._0D0[1] = 2;
        g_FieldingLogic._101[1] = 1;
    }
}

// .text:0x00059338 size:0x28C mapped:0x806983CC
// partial: logic complete, reg allocation differs (loop 1 temp/counter regs, loop 3/4 pointer regs)
void fn_3_59338(void) {
    int i;
    int j;
    int* p;
    InMemFielderView* f;
    InMemFielderView* f2;
    InMemFielderView* fb;
    for (i = 1; i < 10; i++) {
        int* q = &g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][1];
        s32 t = *q;
        if (t >= 0x14) {
            *q = t - 0x14;
        } else if (t >= 0xA) {
            *q = t - 0xA;
        }
    }
    p = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0];
    g_GameLogic.rosterLoc_skippingCap = j = 0;
    for (; j < 10; j++) {
        int b = p[1];
        if (b <= 8) {
            fn_3_6E24C(p[0], b);
        }
        p += 2;
    }
    fb = g_Fielders;
    f = fb;
    for (i = 0; i < 9; i++) {
        u8 v = g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam];
        u8* row = lbl_3_data_46F8 + v * 9;
        int t;
        f->_1D2 = row[i];
        if (v != 0) {
            t = lbl_3_data_470C[0] + (s32)((f32)(lbl_3_data_470C[1] - lbl_3_data_470C[0]) * g_AiLogic.aIDifficultyMultiplierArray[g_GameLogic.homeTeamBattingInd_fieldingTeam]);
            if (i <= 1) {
                f->_1D2 += t / 2;
            } else {
                f->_1D2 += t;
            }
        }
        f++;
    }
    f2 = fb;
    for (i = 0; i < 9; i++) {
        f2->_1F1 = 0;
        f2->_1E3 = 0;
        f2->_1FA = 0;
        f2->_217 = 0;
        f2++;
    }
}

// .text:0x000595C4 size:0x134 mapped:0x80698658
void fn_3_595C4(void) {
    u8* fl;
    InMemFielderView* f;
    int i;
    fn_3_58870();
    for (i = 0; i < 9; i++) {
        g_FieldingLogic._0F8[i] = 0;
        f = &g_Fielders[i];
        f->_1CF = 100;
        f->maxVelocity = lbl_3_rodata_CC4 * (f32)f->_1CF + lbl_3_rodata_B24;
        f->throwStrength = 120;
        f->_1D2 = 10;
        f->_1D1 = 15;
        f->velocityPerWeight = f->maxVelocity / (f32)f->_1D1;
        f->_1D3 = 0;
        f->_1D9 = 0;
        f->_1F1 = 0;
        f->_1E3 = 0;
        f->_219 = 1;
        f->rosterID = -1;
    }
    g_FieldingLogic._0B0 = -1;
    g_FieldingLogic.boost[0].scale = lbl_3_rodata_B60;
    g_FieldingLogic.boost[0].scale = lbl_3_rodata_B60;
    g_FieldingLogic.boost[0].scale = lbl_3_rodata_B60;
    g_FieldingLogic._0B2 = -1;
    g_FieldingLogic._0B4 = -1;
    g_FieldingLogic._0B6 = -1;
    g_FieldingLogic._0B8 = -1;
    g_FieldingLogic._0BA = -1;
    g_FieldingLogic._0BE = -1;
    g_FieldingLogic._136 = 1;
    g_FieldingLogic._137 = 0;
    g_FieldingLogic.curBoost = g_FieldingLogic.boost;
    g_FieldingLogic.curPadRec = g_FieldingLogic.padRec;
    g_FieldingLogic.boost[0].scale = lbl_3_rodata_B60;
}

// .text:0x000596F8 size:0x164 mapped:0x8069878C
// partial: same logic as tail of fn_3_59338; only reg allocation/fmuls dest (f0 vs f1) differ
void fn_3_596F8(void) {
    int i;
    int j;
    int (*p)[2];
    InMemFielderView* f;
    g_GameLogic.rosterLoc_skippingCap = 0;
    p = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam];
    for (j = 0; j < 10; j++) {
        int b = p[j][1];
        if (b <= 8) {
            fn_3_6E24C(p[j][0], b);
        }
    }
    for (i = 0; i < 9; i++) {
        u8 v = g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam];
        u8* row = lbl_3_data_46F8 + v * 9;
        int t;
        f = &g_Fielders[i];
        f->_1D2 = row[i];
        if (v != 0) {
            t = lbl_3_data_470C[0] + (s32)((f32)(lbl_3_data_470C[1] - lbl_3_data_470C[0]) * g_AiLogic.aIDifficultyMultiplierArray[g_GameLogic.homeTeamBattingInd_fieldingTeam]);
            if (i <= 1) {
                f->_1D2 += t / 2;
            } else {
                f->_1D2 += t;
            }
        }
    }
}


#pragma dont_inline off
