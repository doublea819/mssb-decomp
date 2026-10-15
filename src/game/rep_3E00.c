#include "game/rep_3E00.h"
#define REP_HEADER_FN repHeader_3E00
#include "header_rep_inline.h"
#include "main/file_80011640.h" // CharMgr lbl_8036E548
#include "main/file_80024D2C.h" // ShapeData, ShapeAnimPlayer
#include "main/file_800BD8C4.h" // ActorObjectInitTable

#ifdef PORT_LP64
// GameCube: this work area is lbl_3_common_bss_32724 0x00-0x60, below the HUD flags (0x96+).
// 64-bit it is 0xA8 bytes and would run over them, so it gets its own storage (nothing else
// reads it as TrailShapeWork).
static TrailShapeWork sTrailShapeWork;
#define TRAIL_WORK sTrailShapeWork
#else
extern TrailShapeWork lbl_3_common_bss_32724;
#define TRAIL_WORK lbl_3_common_bss_32724
#endif
extern void LoadActorLayout(void*);
extern void convertGeometryAndSknHeader(void* geo, void* skn);
extern void haveActLayoutPointToGeoHeader(void*, void*);
extern void convertTextureHeader(void*);
struct GQRValueGroups;
extern void fn_800BD190(struct GQRValueGroups* groups, void* textures);
extern void* _OSAllocFromHeap(int, int);
extern void* memset(void*, int, size_t);
extern void fn_3_11D2C8(s32 idx, s32 start, s32 count, void* animBank, struct sHdr* skHeader);
extern f32 lbl_3_rodata_3E50;

// The trail* fields are written and read back through a volatile view, which forces the reloads.
#define VMGR ((volatile CharMgr*)&lbl_8036E548)

// 91%: only register allocation differs. Original has b=r31, bss=r30, a=r29, c=r28, zero=r29, one=r31;
// ours ranks the bss pointer (r31) above b (r30) as soon as the unit has any branch (zero check).
// Recipe so far: `#pragma opt_propagation off` keeps the idx/zero/one/cnt constants unfolded, and
// volatile field accesses force the reloads of fields 2DA0/2DA4/2DA8 after the stores.
// A static inline helper taking `u8* bss` as a parameter gave the right mapping when zero was a literal.
// Also tried (no gain): all 5040 local-declaration orders, ~2500 statement orders of the first block, `register`,
// int/ptr/u8 types for zero/one, reusing a/b as zero/one, inline helpers (bss param). An inline helper with
// literal zero folded gets bss=r30/b=r31 right (30 diff lines) but then the cmpwi/bne is dropped.
// .text:0x00166448 size:0x19C mapped:0x807A54DC
#pragma opt_propagation off
void fn_3_166448(void) {
    void* b;
    TrailShapeWork* bss = &TRAIL_WORK;
    void* a;
    void* c;
    u8* hdr = (u8*)lbl_8036E548.trailFile; // file of 32-bit offsets from its own start
    int idx = 3;
    u32* p;
#ifdef TARGET_PC
    port_swap_offset_header(hdr, 5);
#endif
    p = (u32*)hdr + idx;
    VMGR->trailLayout = hdr + ((u32*)hdr)[0];
    VMGR->trailGeo = hdr + ((u32*)hdr)[1];
    VMGR->trailTex = hdr + ((u32*)hdr)[2];
    a = VMGR->trailLayout;
    b = VMGR->trailGeo;
    bss->shape = (ShapeData*)(hdr + p[0]);
    c = VMGR->trailTex;
    bss->anim.set = (ShapeAnimSet*)(hdr + p[1]);
    LoadActorLayout(a);
    convertGeometryAndSknHeader(b, NULL);
    haveActLayoutPointToGeoHeader(a, b);
    convertTextureHeader(c);
    fn_800BD190((struct GQRValueGroups*)b, c);
    {
    int one = 1;
    int zero = 0;
    fn_80025DDC((u8*)bss->shape);
    fn_80025FFC(bss->shape, &bss->anim);
    fn_80025EEC(&bss->anim, 0, 0);
    if (zero == 0) {
        bss->anim.state.loops = one;
    }
    {
    int cnt = 1;
    lbl_8036E548._3078 = cnt;
#ifdef TARGET_PC
    lbl_8036E548.trail2 = _OSAllocFromHeap(0x20, cnt * sizeof(CharTrail)); // 0x30 on PC
    memset(lbl_8036E548.trail2, 0, lbl_8036E548._3078 * sizeof(CharTrail));
#else
    lbl_8036E548.trail2 = _OSAllocFromHeap(0x20, cnt * 0x28);
    memset(lbl_8036E548.trail2, 0, lbl_8036E548._3078 * 0x28);
#endif
    lbl_8036E548.slots68 = ActorObjectInitTable(lbl_8036E548._3078);
    }
    fn_3_11D2C8(0, 0, 1, 0, 0);
    TRAIL_WORK.anim.state.speed = lbl_3_rodata_3E50;
    fn_80025C58(TRAIL_WORK.shape, (ShapeModel**)&lbl_8036E548.slots68->objects[0]);
    }
}
