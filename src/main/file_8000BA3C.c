#include "main/file_8000BA3C.h"
#include "stl/math.h"
#include "stl/mem.h"
#include "main/file_800B0724.h"

// main/file_8000A0AC
// Same functions as main/file_8000A0AC.h, seen through this file's key views.
void fn_8000A0AC(f32 t, f32* curve, AnimFrame* a, AnimFrame* b);
s32 fn_8000A3EC(Mtx out, SpriteDrawParams* params, AnimFrame* a, AnimFrame* b, f32* curve, f32 t, f32 z);
void interpolatePointsBezier_Vec2s(f32 t, f32* curve, AnimKeyV0* p0, AnimKeyV0* p1, AnimKeyV0* p2, AnimKeyV0* p3, u32 mode);
s32 fn_8000AF1C(Mtx out, SpriteDrawParams* params, AnimKeyV0* a, AnimKeyV0* b, void* animC, f32* curve, f32 t);

// Copy four transformed quad corners (in the given order) into the vertex positions.
#define SET_QUAD_POS(a, b, c, d)                          \
    do {                                                  \
        lbl_80366188.u.v[0].pos.x = q.pt[a].pos.x;          \
        lbl_80366188.u.v[0].pos.y = q.pt[a].pos.y;          \
        lbl_80366188.u.v[0].pos.z = q.pt[a].pos.z;          \
        lbl_80366188.u.v[1].pos.x = q.pt[b].pos.x;          \
        lbl_80366188.u.v[1].pos.y = q.pt[b].pos.y;          \
        lbl_80366188.u.v[1].pos.z = q.pt[b].pos.z;          \
        lbl_80366188.u.v[2].pos.x = q.pt[c].pos.x;          \
        lbl_80366188.u.v[2].pos.y = q.pt[c].pos.y;          \
        lbl_80366188.u.v[2].pos.z = q.pt[c].pos.z;          \
        lbl_80366188.u.v[3].pos.x = q.pt[d].pos.x;          \
        lbl_80366188.u.v[3].pos.y = q.pt[d].pos.y;          \
        lbl_80366188.u.v[3].pos.z = q.pt[d].pos.z;          \
    } while (0)

// Advance to the next entry of an animation block.
static inline AnimEntry* AnimEntry_Next(AnimEntry* entry, u32 fullWords, u32 rawWords) {
    AnimEntry* next = entry;
    switch (entry->type & 0x7FFF) {
    case ANIM_ENTRY_FULL:
        next = (AnimEntry*)((u32*)entry + fullWords);
        break;
    case ANIM_ENTRY_RAW:
        next = (AnimEntry*)((u32*)entry + rawWords);
        break;
    case ANIM_ENTRY_SPARSE:
        next = (AnimEntry*)((u32*)entry + entry->size);
        break;
    case ANIM_ENTRY_SPANS:
        next = (AnimEntry*)((u32*)entry + entry->size);
        break;
    }
    return next;
}

// Decode an animation entry into a full frame of anim->paramCount words.
static inline void AnimEntry_Decode(AnimEntry* entry, AnimBlock* block, u32* out, u32 outSize) {
    u32* dst;
    u32* values;
    u16* idx;
    u16* span;
    u8* src;
    s32 n;
    s32 count;

    switch (entry->type & 0x7FFF) {
    case ANIM_ENTRY_FULL:
        memset(out, 0, outSize);
        memcpy(out, block->entries, block->size);
        break;
    case ANIM_ENTRY_RAW:
        memcpy(out, entry, outSize);
        break;
    case ANIM_ENTRY_SPARSE:
        memset(out, 0, outSize);
        dst = out + 1;
        memcpy(dst, &block->entries[0].count, block->size - 4);
        memcpy(out, entry, 4);
        n = entry->count;
        values = (u32*)entry + entry->size;
        idx = (u16*)entry + n;
        while (values--, idx--, n-- != 0) {
            dst[idx[4]] = *values;
        }
        break;
    case ANIM_ENTRY_SPANS:
        memset(out, 0, outSize);
        dst = out + 1;
        memcpy(dst, &block->entries[0].count, block->size - 4);
        memcpy(out, entry, 4);
        span = entry->data;
        src = (u8*)entry + ((count = entry->count) * 4 + 8);
        while (count-- != 0) {
            memcpy((u8*)dst + span[0], src, span[1]);
            src += span[1];
            span += 2;
        }
        break;
    }
}

// Scale each channel of an RGBA color by the matching channel of another.
static inline u32 ModulateColor(u32 c, u32 r, u32 g, u32 b, u32 a) {
    r = r * (c >> 24) / 255;
    g = g * ((c >> 16) & 0xFF) / 255;
    b = b * ((c >> 8) & 0xFF) / 255;
    a = a * (c & 0xFF) / 255;
    return (r << 24) | (g << 16) | (b << 8) | a;
}

// .text:0x8000BA3C size:0x758
// NONMATCHING: ~75% (large function written as equivalent C): the original keeps the color channels in stack arrays; register allocation differs
#if NONMATCHING
s32 fn_8000BA3C(u32* time, Anim* anim, s32 trackIdx, Mtx mtx, s32 flags, u32 color, u16** outLoop, s16* path) {
    AnimFrame frames[2];
    SpriteDrawParams params;
    Mtx m;
    f32 curve[4];
    AnimEntry* cur[2];
    u32 subTime;
    u16* subLoop;
    AnimTrack* track;
    PTR32(AnimBlock)* blockPtr;
    AnimBlock* block;
    AnimEntry* entry;
    AnimLoop* loop;
    AnimFrame* next;
    u16* loops;
    u32 t;
    u32 start;
    s32 numBlocks;
    s32 result;
    s32 n;
    s32 i;
    u16 prevTime;
    u32 colR;
    u32 colG;
    u32 colB;
    u32 colA;
    u32 dt;
    u32 span;
    f32 f;

    if (path != NULL) {
        path[0] = trackIdx;
    }
    t = *time;
    // TODO type: anim->table->tracks[trackIdx]
    track = PTR32_GET(AnimTrack, *(PTR32(AnimTrack)*)((u8*)PTR32_GET(AnimTrackTable, anim->table) + trackIdx * 4 + 8));
    result = 0;
    loops = PTR32_GET(u16, track->loops);
    numBlocks = track->count & 0x7FFFFFFF;
    *outLoop = NULL;

    // Apply the loop markers (last one first).
    loop = (AnimLoop*)(loops + 2) + loops[0];
    for (n = loops[0]; n != 0; n--) {
        loop--;
        if (t >= (u32)loop->end << 16) {
            *outLoop = &loop->start;
            result = loop->mode + 1;
            if (loop->mode == 0) {
                t = t % ((u32)loop->end << 16);
            } else if (loop->mode == 2) {
                start = **outLoop << 16;
                t = start + (t - start) % (((u32)loop->end << 16) - start);
            }
            *time = t;
            break;
        }
    }

    numBlocks--;
    // TODO type: &track->blocks[numBlocks - 1]
    blockPtr = (PTR32(AnimBlock)*)((u8*)track + numBlocks * 4 + 8);
    lbl_80366188.unk7F = 0;
    if (path != NULL) {
        path[1] = 0;
    }
    colR = color >> 24;
    colG = (color >> 16) & 0xFF;
    colB = (color >> 8) & 0xFF;
    colA = color & 0xFF;

    do {
        block = PTR32_GET(AnimBlock, *blockPtr--);
        entry = block->entries;
        cur[1] = entry;
        n = block->count;
        while (n-- != 0) {
            cur[0] = entry;
            prevTime = entry->time;
            if (t < (u32)entry->time << 16) {
                cur[1] = entry;
                entry = AnimEntry_Next(entry, (u32)block->size >> 2, anim->paramCount);
                continue;
            }

            // Find where the current segment started.
            if (entry->type & 0x8000) {
                for (i = n; i != 0; i--) {
                    entry = AnimEntry_Next(entry, (u32)block->size >> 2, anim->paramCount);
                    if (!(n != 1 && (entry->type & 0x8000))) {
                        prevTime = entry->time;
                    }
                    n--;
                }
            }

            for (i = 0; i < 2; i++) {
                AnimEntry_Decode(cur[i], block, (u32*)&frames[i], anim->paramCount * 4);
            }

            next = (frames[1].kind == 0) ? &frames[0] : &frames[1];
            if (frames[0].kind != 0) {
                f = 1.0f;
                dt = t - ((u32)frames[0].time << 16);
                span = (u32)(next->time - frames[0].time) << 16;
                if (dt < span) {
                    f = (f32)dt / (f32)span;
                }
                if ((frames[0].flags >> 4) & 1) {
                    fn_8000A0AC(f, curve, &frames[0], next);
                }
                flags |= fn_8000A3EC(m, &params, &frames[0], next, curve, f, next->unk18);
                PSMTXConcat(mtx, m, m);
                for (i = 0; i < 4; i++) {
                    params.color[i] = ModulateColor(params.color[i], colR, colG, colB, colA);
                }
                switch (frames[0].kind) {
                case 1:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                    if (path != NULL && lbl_80366188.callback != NULL) {
                        lbl_80366188.path = path;
                        lbl_80366188.mtx = m;
                        lbl_80366188.color = params.color[0];
                        lbl_80366188.callback(&lbl_80366188, m);
                    }
                    if (frames[0].kind == 3) {
                        subTime = t - ((u32)prevTime << 16);
                        fn_8000BA3C(&subTime, anim, frames[0].subTrack, m, flags, params.color[0], &subLoop, path + 2);
                    }
                    break;
                }
            }
            break;
        }
        if (path != NULL) {
            path[1]++;
        }
    } while (--numBlocks != 0);
    return result;
}
#endif

// .text:0x8000C194 size:0xAB8
// NONMATCHING: ~75% (large function written as equivalent C): the original keeps the color channels in stack arrays; register allocation differs
#if NONMATCHING
s32 fn_8000C194(u32* time, Anim* anim, s32 trackIdx, Mtx mtx, s32 flags, u32 color, u16** outLoop, SpriteBank* bank) {
    AnimFrame frames[2];
    SpriteDrawParams params;
    Mtx m;
    MtxBox scale;
    SpriteQuad q;
    f32 curve[4];
    AnimEntry* cur[2];
    u32 subTime;
    s32 drawOk;
    u16* subLoop;
    AnimTrack* track;
    PTR32(AnimBlock)* blockPtr;
    AnimBlock* block;
    AnimEntry* entry;
    AnimLoop* loop;
    AnimFrame* next;
    u16* loops;
    u32 t;
    u32 start;
    s32 numBlocks;
    s32 result;
    s32 n;
    s32 i;
    u16 prevTime;
    u32 colR;
    u32 colG;
    u32 colB;
    u32 colA;
    u32 dt;
    u32 span;
    f32 f;
    f32 z;
    f32 k;

    t = *time;
    // TODO type: anim->table->tracks[trackIdx]
    track = PTR32_GET(AnimTrack, *(PTR32(AnimTrack)*)((u8*)PTR32_GET(AnimTrackTable, anim->table) + trackIdx * 4 + 8));
    result = 0;
    loops = PTR32_GET(u16, track->loops);
    numBlocks = track->count & 0x7FFFFFFF;
    *outLoop = NULL;

    // Apply the loop markers (last one first).
    loop = (AnimLoop*)(loops + 2) + loops[0];
    for (n = loops[0]; n != 0; n--) {
        loop--;
        if (t >= (u32)loop->end << 16) {
            *outLoop = &loop->start;
            result = loop->mode + 1;
            if (loop->mode == 0) {
                t = t % ((u32)loop->end << 16);
            } else if (loop->mode == 2) {
                start = **outLoop << 16;
                t = start + (t - start) % (((u32)loop->end << 16) - start);
            }
            *time = t;
            break;
        }
    }

    colR = color >> 24;
    colG = (color >> 16) & 0xFF;
    numBlocks--;
    // TODO type: &track->blocks[numBlocks - 1]
    blockPtr = (PTR32(AnimBlock)*)((u8*)track + numBlocks * 4 + 8);
    colB = (color >> 8) & 0xFF;
    colA = color & 0xFF;
    lbl_80366188.unk7F = 0;

    do {
        block = PTR32_GET(AnimBlock, *blockPtr--);
        entry = block->entries;
        cur[1] = entry;
        n = block->count;
        while (n-- != 0) {
            cur[0] = entry;
            prevTime = entry->time;
            if (t < (u32)entry->time << 16) {
                cur[1] = entry;
                entry = AnimEntry_Next(entry, (u32)block->size >> 2, anim->paramCount);
                continue;
            }

            // Find where the current segment started.
            if (entry->type & 0x8000) {
                for (i = n; i != 0; i--) {
                    entry = AnimEntry_Next(entry, (u32)block->size >> 2, anim->paramCount);
                    if (!(n != 1 && (entry->type & 0x8000))) {
                        prevTime = entry->time;
                    }
                    n--;
                }
            }

            for (i = 0; i < 2; i++) {
                AnimEntry_Decode(cur[i], block, (u32*)&frames[i], anim->paramCount * 4);
            }

            next = (frames[1].kind == 0) ? &frames[0] : &frames[1];
            if (frames[0].kind != 0) {
                f = 1.0f;
                dt = t - ((u32)frames[0].time << 16);
                span = (u32)(next->time - frames[0].time) << 16;
                if (dt < span) {
                    f = (f32)dt / (f32)span;
                }
                if ((frames[0].flags >> 4) & 1) {
                    fn_8000A0AC(f, curve, &frames[0], next);
                }
                flags |= fn_8000A3EC(m, &params, &frames[0], next, curve, f, next->unk18);
                PSMTXConcat(mtx, m, m);
                if ((frames[0].flags2 >> 7) & 1) {
                    fn_800B1188();
                }
                fn_800B117C(frames[0].flags & 1);
                if (frames[0].flags & 1) {
                    // Perspective: scale by depth around the screen center.
                    z = m[2][3];
                    scale = lbl_800E65D0;
                    k = -z / 1280.0f;
                    scale.m[2][2] = k;
                    scale.m[1][1] = k;
                    scale.m[0][0] = k;
                    scale.m[2][3] = z;
                    PSMTXInverse(scale.m, scale.m);
                    PSMTXConcat(scale.m, m, m);
                    scale.m[2][2] = 1.0f / 1280.0f;
                    scale.m[1][1] = 1.0f / 1280.0f;
                    scale.m[0][0] = 1.0f / 1280.0f;
                    scale.m[2][3] = -1.0f;
                    PSMTXConcat(scale.m, m, m);
                }
                for (i = 0; i < 4; i++) {
                    params.color[i] = ModulateColor(params.color[i], colR, colG, colB, colA);
                }
                if (frames[0].kind != 3) {
                    switch (frames[0].blend) {
                    case 0:
                        fn_800B2160(1);
                        if (frames[0].kind != 3 && ((frames[0].flags2 >> 7) & 1)) {
                            fn_800B1188();
                        }
                        break;
                    case 1:
                        fn_800B2160(2);
                        break;
                    case 2:
                        fn_800B2160(3);
                        break;
                    }
                }
                switch (frames[0].kind) {
                case 1:
                    q.xy[0][0] = 0.0f;
                    q.xy[0][1] = 0.0f;
                    q.xy[3][0] = 256.0f;
                    q.xy[3][1] = 256.0f;
                    q.xy[1][0] = 256.0f;
                    q.xy[1][1] = 0.0f;
                    q.xy[2][0] = 0.0f;
                    q.xy[2][1] = 256.0f;
                    AddVec2iToQuad(&q, m, &params);
                    lbl_80366188.unk7E = 0;
                    SET_QUAD_POS(0, 1, 3, 2);
                    lbl_80366188.perCornerColor = flags | ((frames[0].flags >> 5) & 1);
                    lbl_80366188.u.v[0].color = params.color[0];
                    lbl_80366188.u.v[1].color = params.color[3];
                    lbl_80366188.u.v[2].color = params.color[2];
                    lbl_80366188.u.v[3].color = params.color[1];
                    drawOk = TRUE;
                    if (((frames[0].flags >> 3) & 1) && lbl_80366188.drawCallback != NULL) {
                        drawOk = lbl_80366188.drawCallback(&lbl_80366188);
                    }
                    if (drawOk) {
                        fn_800B1388(&lbl_80366188);
                    }
                    break;
                case 2:
                    drawOk = TRUE;
                    if (((frames[0].flags >> 3) & 1) && lbl_80366188.drawCallback != NULL) {
                        lbl_80366188.bank = NULL;
                        lbl_80366188.perCornerColor = 1;
                        lbl_80366188.unk7E = 1;
                        memcpy(lbl_80366188.u.circle.mtx, m, sizeof(Mtx));
                        lbl_80366188.u.circle.color0 = params.color[0];
                        lbl_80366188.u.circle.color1 = params.color[1];
                        lbl_80366188.u.circle.x = frames[0].x;
                        lbl_80366188.u.circle.y = frames[0].y;
                        lbl_80366188.u.circle.radius = 128.0f;
                        lbl_80366188.u.circle.radius2 = params.radius2;
                        lbl_80366188.u.circle.segments = params.segments;
                        lbl_80366188.u.circle.arcSegments = params.arcSegments;
                        drawOk = lbl_80366188.drawCallback(&lbl_80366188);
                    }
                    if (drawOk) {
                        if (params.radius2 == 0.0f) {
                            fn_8000E030((CircleElem*)&frames[0], m, &params);
                        } else {
                            fn_8000D8A4((CircleElem*)&frames[0], m, &params);
                        }
                    }
                    break;
                case 3:
                    subTime = t - ((u32)prevTime << 16);
                    fn_8000C194(&subTime, anim, frames[0].subTrack, m, flags, params.color[0], &subLoop, bank);
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                    SetSpriteRect((SpriteRectElem*)&frames[0], bank, m, &params, flags);
                    drawOk = TRUE;
                    if (((frames[0].flags >> 3) & 1) && lbl_80366188.drawCallback != NULL) {
                        drawOk = lbl_80366188.drawCallback(&lbl_80366188);
                    }
                    if (drawOk) {
                        DrawSprite_TexObj(lbl_80366188.u.v, lbl_803CBBD8);
                    }
                    break;
                }
            }
            fn_800B117C(0);
            break;
        }
    } while (--numBlocks != 0);
    return result;
}
#endif

// .text:0x8000CC4C size:0x2A4
// NONMATCHING: ~90%: same instructions, saved-register allocation and scheduling differ
#if NONMATCHING
void fn_8000CC4C(Anim* anim, AnimBlock* block, u8* src, u32 ofs, u32 len) {
    AnimEntry* entry;
    s32 i;
    s32 j;
    u32 end;
    u32 base;
    u32 limit;
    u32 wofs;
    u32 n;
    u16* idx;
    u16* span;
    u8* dst;
    u32 so;
    u32 sl;
    u32 se;

    entry = block->entries;
    end = ofs + len;
    for (i = 0; i < block->count; i++) {
        switch (entry->type & 0x7FFF) {
        case ANIM_ENTRY_FULL:
            if (block->size < end && block->size - ofs == 0) {
                break;
            }
        case ANIM_ENTRY_RAW:
            memcpy((u8*)entry + ofs, src, len);
            break;
        case ANIM_ENTRY_SPARSE:
            base = ofs - 4;
            limit = base + len;
            idx = (u16*)entry;
            dst = (u8*)entry + (((entry->count + 1) * 2) & ~3) + 8;
            for (j = 0; j < entry->count; j++) {
                wofs = idx[4] * 4;
                if (wofs >= limit) {
                    break;
                }
                if (wofs + 4 > base) {
                    n = wofs + 4 - base;
                    if (n < 4) {
                        if (n > len) {
                            n = len;
                        }
                        memcpy(dst + 4 - n, src, n);
                    } else {
                        n = limit - wofs;
                        if (n < 4) {
                            memcpy(dst, src + len + 4 - n, n);
                        } else {
                            memcpy(dst, src + wofs - base, 4);
                        }
                    }
                }
                idx++;
                dst += 4;
            }
            break;
        case ANIM_ENTRY_SPANS:
            base = ofs - 4;
            limit = base + len;
            span = (u16*)entry;
            dst = (u8*)entry + entry->count * 4 + 8;
            for (j = 0; j < entry->count; j++) {
                so = span[4];
                sl = span[5];
                if (so >= limit) {
                    break;
                }
                se = so + sl;
                if (se > base) {
                    n = base - so;
                    if (n < sl) {
                        n = sl - n;
                        if (n > len) {
                            n = len;
                        }
                        memcpy(dst + (base - so), src, n);
                    } else if (limit < se) {
                        memcpy(dst, src + (so - base), limit - so);
                    } else {
                        memcpy(dst, src + (so - base), sl);
                    }
                }
                dst += sl;
                span += 2;
            }
            break;
        }
        entry = AnimEntry_Next(entry, (u32)block->size >> 2, anim->paramCount);
    }
}
#endif

// .text:0x8000CEF0 size:0x274
BOOL fn_8000CEF0(Anim* anim, s32 trackIdx, u32 blockIdx, s32 entryIdx, u32* out) {
    AnimTrack* track;
    AnimBlock* block;
    AnimEntry* entry;
    s32 n;
    u32 outSize;
    u32* dst;
    u32* values;
    u16* idx;
    u16* span;
    u8* src;
    s32 count;

    // TODO type: anim->table->tracks[trackIdx] (typed indexing folds the +8)
    track = PTR32_GET(AnimTrack, *(PTR32(AnimTrack)*)((u8*)PTR32_GET(AnimTrackTable, anim->table) + trackIdx * 4 + 8));
    if (blockIdx >= (track->count & 0x7FFFFFFF) - 1) {
        return FALSE;
    }
    // TODO type: track->blocks[blockIdx]
    block = PTR32_GET(AnimBlock, *(PTR32(AnimBlock)*)((u8*)track + (blockIdx + 1) * 4 + 8));
    n = block->count - entryIdx;
    if (n <= 0) {
        return FALSE;
    }
    entry = block->entries;
    while (--n) {
        entry = AnimEntry_Next(entry, (u32)block->size >> 2, anim->paramCount);
    }
    outSize = anim->paramCount * 4;
    switch (entry->type & 0x7FFF) {
    case ANIM_ENTRY_FULL:
        memset(out, 0, outSize);
        memcpy(out, block->entries, block->size);
        break;
    case ANIM_ENTRY_RAW:
        memcpy(out, entry, outSize);
        break;
    case ANIM_ENTRY_SPARSE:
        memset(out, 0, outSize);
        dst = out + 1;
        memcpy(dst, &block->entries[0].count, block->size - 4);
        memcpy(out, entry, 4);
        n = entry->count;
        values = (u32*)entry + entry->size;
        idx = (u16*)entry + n;
        while (values--, idx--, n-- != 0) {
            dst[idx[4]] = *values;
        }
        break;
    case ANIM_ENTRY_SPANS:
        memset(out, 0, outSize);
        dst = out + 1;
        memcpy(dst, &block->entries[0].count, block->size - 4);
        memcpy(out, entry, 4);
        span = entry->data;
        src = (u8*)entry + ((count = entry->count) * 4 + 8);
        while (count-- != 0) {
            memcpy((u8*)dst + span[0], src, span[1]);
            src += span[1];
            span += 2;
        }
        break;
    }
    return TRUE;
}

// .text:0x8000D164 size:0x6D4
// NONMATCHING: ~75% (large function written as equivalent C): the original keeps the color channels in stack arrays; register allocation differs
#if NONMATCHING
s32 fn_8000D164(u32* time, Anim* anim, s32 trackIdx, Mtx mtx, s32 flags, u32 color, u16** outLoop, SpriteBank* bank) {
    SpriteDrawParams params;
    Mtx m;
    f32 curve[4];
    u32 subTime;
    s32 drawOk;
    u16* subLoop;
    void* animC;
    AnimTrack* track;
    PTR32(AnimBlockV0)* blockPtr;
    AnimBlockV0* block;
    AnimKeyV0* key;
    AnimKeyV0* next;
    AnimKeyV0* k;
    AnimLoop* loop;
    u16* loops;
    u32 t;
    u32 start;
    s32 numBlocks;
    s32 result;
    s32 n;
    s32 idx;
    s32 i;
    u16 keyTime;
    u16 prevTime;
    u32 colR;
    u32 colG;
    u32 colB;
    u32 colA;
    u32 dt;
    u32 span;
    f32 f;

    // TODO type: anim->table->tracks[trackIdx]
    track = PTR32_GET(AnimTrack, *(PTR32(AnimTrack)*)((u8*)PTR32_GET(AnimTrackTable, anim->table) + trackIdx * 4 + 8));
    animC = PTR32_GET(void, anim->unkC);
    t = *time;
    result = 0;
    loops = PTR32_GET(u16, track->loops);
    numBlocks = track->count;
    *outLoop = NULL;

    // Apply the loop markers (last one first).
    loop = (AnimLoop*)(loops + 2) + loops[0];
    for (n = loops[0]; n != 0; n--) {
        loop--;
        if (t >= (u32)loop->end << 16) {
            *outLoop = &loop->start;
            result = loop->mode + 1;
            if (loop->mode == 0) {
                t = t % ((u32)loop->end << 16);
            } else if (loop->mode == 2) {
                start = **outLoop << 16;
                t = start + (t - start) % (((u32)loop->end << 16) - start);
            }
            *time = t;
            break;
        }
    }

    numBlocks--;
    // TODO type: &track->blocks[numBlocks - 1]
    blockPtr = (PTR32(AnimBlockV0)*)((u8*)track + numBlocks * 4 + 8);
    lbl_80366188.unk7F = 0;
    colR = color >> 24;
    colG = (color >> 16) & 0xFF;
    colB = (color >> 8) & 0xFF;
    colA = color & 0xFF;

    do {
        block = PTR32_GET(AnimBlockV0, *blockPtr--);
        idx = block->count;
        n = idx;
        key = &block->keys[idx];
        next = key - 1;
        while (n-- != 0) {
            keyTime = key[-1].time;
            idx--;
            key--;
            prevTime = keyTime;
            if (t < (u32)keyTime << 16) {
                next = key;
                continue;
            }

            // Find where the current segment started.
            if (key->linked) {
                k = key;
                for (i = n; i != 0; i--) {
                    if (!(n != 1 && k[-1].linked)) {
                        prevTime = k[-1].time;
                    }
                    k--;
                    n--;
                }
            }
            if (next->kind == 0) {
                next = key;
            }
            if (key->kind == 0) {
                break;
            }

            f = 1.0f;
            dt = t - ((u32)keyTime << 16);
            span = (u32)(next->time - keyTime) << 16;
            if (dt < span) {
                f = (f32)dt / (f32)span;
            }
            if (key->curved) {
                if (key[-1].curved && idx != 0) {
                    if (key[1].curved) {
                        interpolatePointsBezier_Vec2s(f, curve, key - 1, key, key + 1, key + 2, 1);
                    } else {
                        interpolatePointsBezier_Vec2s(f, curve, key - 1, key - 1, key, key + 1, 2);
                    }
                } else if (idx == 0) {
                    interpolatePointsBezier_Vec2s(f, curve, key, key + 1, key + 1, key + 2, 0);
                } else {
                    interpolatePointsBezier_Vec2s(f, curve, key, key + 1, key + 2, key + 2, 0);
                }
            }
            flags |= fn_8000AF1C(m, &params, key, next, animC, curve, f);
            PSMTXConcat(mtx, m, m);
            for (i = 0; i < 4; i++) {
                params.color[i] = ModulateColor(params.color[i], colR, colG, colB, colA);
            }
            switch (key->blend) {
            case 0:
                fn_800B2160(1);
                break;
            case 1:
                fn_800B2160(2);
                break;
            case 2:
                fn_800B2160(3);
                break;
            }
            switch (key->kind) {
            case 1:
            case 2:
                fn_8000E7BC((SpriteElem*)key, m, &params, flags);
                drawOk = TRUE;
                if (lbl_80366188.drawCallback != NULL && key->useCallback) {
                    drawOk = lbl_80366188.drawCallback(&lbl_80366188);
                }
                if (drawOk) {
                    fn_800B1388(&lbl_80366188);
                }
                break;
            case 3:
                drawOk = TRUE;
                if (lbl_80366188.drawCallback != NULL && key->useCallback) {
                    lbl_80366188.elem = key;
                    lbl_80366188.bank = NULL;
                    lbl_80366188.perCornerColor = 1;
                    lbl_80366188.unk7E = 1;
                    memcpy(lbl_80366188.u.circle.mtx, m, sizeof(Mtx));
                    lbl_80366188.u.circle.color0 = params.color[0];
                    lbl_80366188.u.circle.color1 = params.color[1];
                    lbl_80366188.u.circle.x = ((Circle2DElem*)key)->x;
                    lbl_80366188.u.circle.y = ((Circle2DElem*)key)->y;
                    lbl_80366188.u.circle.radius = 128.0f;
                    lbl_80366188.u.circle.radius2 = params.radius2;
                    lbl_80366188.u.circle.segments = params.segments;
                    lbl_80366188.u.circle.arcSegments = params.arcSegments;
                    drawOk = lbl_80366188.drawCallback(&lbl_80366188);
                }
                if (drawOk) {
                    if (params.radius2 == 0.0f) {
                        fn_8000E2D4((Circle2DElem*)key, m, &params);
                    } else {
                        fn_8000DC9C((Circle2DElem*)key, m, &params);
                    }
                }
                break;
            case 4:
                fn_8000EC0C((SpriteElem*)key, bank, m, &params, flags);
                drawOk = TRUE;
                if (lbl_80366188.drawCallback != NULL && key->useCallback) {
                    drawOk = lbl_80366188.drawCallback(&lbl_80366188);
                }
                if (drawOk) {
                    DrawSprite_TexObj(lbl_80366188.u.v, lbl_803CBBD8);
                }
                break;
            case 5:
                subTime = t - ((u32)prevTime << 16);
                fn_8000D164(&subTime, anim, key->subTrack, m, flags, params.color[0], &subLoop, bank);
                break;
            }
            break;
        }
    } while (--numBlocks != 0);
    return result;
}
#endif

// .text:0x8000D838 size:0x6C
s32 fn_8000D838(u32* time, Anim* anim, s32 trackIdx, Mtx mtx, s32 flags, u32 color, u16** outLoop, SpriteBank* bank) {
    s16 path[60];

#ifdef TARGET_PC
    {
        // Guard (PC): an out-of-range track index or a stale animation reads junk offsets and
        // crashes (seen in Bob-omb Derby after home-run streaks). Skip the sprite for this frame
        // and report what was asked for, so the cause can be traced.
        AnimTrackTable* tbl = anim != NULL ? PTR32_GET(AnimTrackTable, anim->table) : NULL;
        u32 ntracks = tbl != NULL ? *(u32*)tbl : 0;
        if (tbl == NULL || trackIdx < 0 || (u32)trackIdx >= ntracks || ntracks > 0x400) {
            static int s_reports;
            if (s_reports < 20) {
                s_reports++;
                OSReport("[port] spani: bad track %d (of %u) in anim %p\n", (int)trackIdx,
                         ntracks, (void*)anim);
            }
            *outLoop = NULL;
            return 0;
        }
    }
#endif
    if (anim->unk6 == 0) {
        return fn_8000D164(time, anim, trackIdx, mtx, flags, color, outLoop, bank);
    }
    // TODO type: anim->table->tracks[trackIdx]->count
    if ((PTR32_GET(AnimTrack, *(PTR32(AnimTrack)*)((u8*)PTR32_GET(AnimTrackTable, anim->table) + trackIdx * 4 + 8)))->count & 0x80000000) {
        path[0] = -1;
        path[1] = 0;
        return fn_8000BA3C(time, anim, trackIdx, mtx, flags, color, outLoop, &path[2]);
    }
    return fn_8000C194(time, anim, trackIdx, mtx, flags, color, outLoop, bank);
}

// .text:0x8000D8A4 size:0x3F8
// NONMATCHING: ~80%: our compiler unrolls the final strip loop 2x; saved-register allocation differs
#if NONMATCHING
void fn_8000D8A4(CircleElem* elem, Mtx mtx, SpriteDrawParams* params) {
    QuadVtx strip[516];
    Vec ring0[257];
    Vec ring1[257];
    Vec out;
    Vec pt;
    f32 radius[2];
    u32 color0;
    u32 color1;
    s32 i;
    s32 j;
    s32 n;
    s32 step;
    s16 angle;
    f32 a;
    f32 s;
    f32 c;
    f32 z;
    u32 count;
    Vec* p0;
    Vec* p1;
    QuadVtx* v;

    if (!elem->hidden || params->arcSegments != 0) {
        z = elem->z;
        if (params->radius2 > 128.0f) {
            radius[1] = 128.0f;
            color1 = params->color[1];
            radius[0] = params->radius2;
            color0 = params->color[0];
        } else {
            radius[0] = 128.0f;
            color0 = params->color[1];
            radius[1] = params->radius2;
            color1 = params->color[0];
        }
        for (i = 0; i < 2; i++) {
            pt.x = 128.0f + radius[i];
            pt.y = 128.0f;
            pt.z = elem->unk18 + z;
            PSMTXMultVec(mtx, &pt, &out);
            if (i != 0) {
                ring1[0].x = out.x;
                ring1[0].y = out.y;
                ring1[0].z = out.z;
            } else {
                ring0[0].x = out.x;
                ring0[0].y = out.y;
                ring0[0].z = out.z;
            }
        }
        if (params->arcSegments != 0) {
            n = params->arcSegments;
        } else {
            n = params->segments - 1;
        }
        step = 0x10000 / params->segments;
        p1 = &ring1[1];
        p0 = &ring0[1];
        angle = 0;
        do {
            angle -= step;
            a = 0.0000958738f * angle;
            s = sin(a);
            c = cos(a);
            for (j = 0; j < 2; j++) {
                pt.x = c * radius[j] + 128.0f;
                pt.y = s * radius[j] + 128.0f;
                pt.z = elem->unk18 + z;
                PSMTXMultVec(mtx, &pt, &out);
                if (j != 0) {
                    p1->x = out.x;
                    p1->y = out.y;
                    p1->z = out.z;
                } else {
                    p0->x = out.x;
                    p0->y = out.y;
                    p0->z = out.z;
                }
            }
            p1++;
            p0++;
        } while (--n);
        if (!elem->hidden) {
            ring1[params->segments].x = ring1[0].x;
            ring0[params->segments].x = ring0[0].x;
            ring1[params->segments].y = ring1[0].y;
            ring0[params->segments].y = ring0[0].y;
            ring1[params->segments].z = ring1[0].z;
            ring0[params->segments].z = ring0[0].z;
        }
        if (elem->hidden) {
            count = (params->arcSegments + 1) * 2;
        } else {
            count = (params->segments + 1) * 2;
        }
        memset(strip, 0, sizeof(strip));
        v = strip;
        p0 = ring0;
        p1 = ring1;
        for (i = 0; i < count; i += 2) {
            v[0].pos.x = p0->x;
            v[0].pos.y = p0->y;
            v[0].pos.z = p0->z;
            v[1].pos.x = p1->x;
            v[1].pos.y = p1->y;
            v[1].pos.z = p1->z;
            v[0].color = color0;
            v[1].color = color1;
            p0++;
            p1++;
            v += 2;
        }
        DrawNullSprite(strip, count);
    }
}
#endif

// .text:0x8000DC9C size:0x394
// NONMATCHING: ~80%: our compiler unrolls the final strip loop 2x; saved-register allocation differs
#if NONMATCHING
void fn_8000DC9C(Circle2DElem* elem, Mtx mtx, SpriteDrawParams* params) {
    QuadVtx strip[516];
    Vec ring0[257];
    Vec ring1[257];
    Mtx m;
    Vec out;
    Vec pt;
    f32 radius[2];
    u32 color0;
    u32 color1;
    s32 i;
    s32 j;
    s32 n;
    s32 step;
    s16 angle;
    f32 a;
    f32 s;
    f32 c;
    u32 count;
    Vec* p0;
    Vec* p1;
    QuadVtx* v;

    if (!elem->hidden || params->arcSegments != 0) {
        PSMTXCopy(mtx, m);
        if (params->radius2 > 128.0f) {
            radius[1] = 128.0f;
            color1 = params->color[1];
            radius[0] = params->radius2;
            color0 = params->color[0];
        } else {
            radius[0] = 128.0f;
            color0 = params->color[1];
            radius[1] = params->radius2;
            color1 = params->color[0];
        }
        for (i = 0; i < 2; i++) {
            pt.x = 128.0f + radius[i];
            pt.y = 128.0f;
            pt.z = 0.0f;
            PSMTXMultVec(m, &pt, &out);
            if (i != 0) {
                ring1[0].x = out.x;
                ring1[0].y = out.y;
                ring1[0].z = out.z;
            } else {
                ring0[0].x = out.x;
                ring0[0].y = out.y;
                ring0[0].z = out.z;
            }
        }
        if (params->arcSegments != 0) {
            n = params->arcSegments;
        } else {
            n = params->segments - 1;
        }
        step = 0x10000 / params->segments;
        p1 = &ring1[1];
        p0 = &ring0[1];
        angle = 0;
        do {
            angle -= step;
            a = 0.0000958738f * angle;
            s = sin(a);
            c = cos(a);
            for (j = 0; j < 2; j++) {
                pt.x = c * radius[j] + 128.0f;
                pt.y = s * radius[j] + 128.0f;
                pt.z = 0.0f;
                PSMTXMultVec(m, &pt, &out);
                if (j != 0) {
                    p1->x = out.x;
                    p1->y = out.y;
                    p1->z = out.z;
                } else {
                    p0->x = out.x;
                    p0->y = out.y;
                    p0->z = out.z;
                }
            }
            p1++;
            p0++;
        } while (--n);
        if (!elem->hidden) {
            ring1[params->segments].x = ring1[0].x;
            ring0[params->segments].x = ring0[0].x;
            ring1[params->segments].y = ring1[0].y;
            ring0[params->segments].y = ring0[0].y;
            ring1[params->segments].z = ring1[0].z;
            ring0[params->segments].z = ring0[0].z;
        }
        if (elem->hidden) {
            count = (params->arcSegments + 1) * 2;
        } else {
            count = (params->segments + 1) * 2;
        }
        v = strip;
        p0 = ring0;
        p1 = ring1;
        for (i = 0; i < count; i += 2) {
            v[0].pos.x = p0->x;
            v[0].pos.y = p0->y;
            v[0].pos.z = p0->z;
            v[1].pos.x = p1->x;
            v[1].pos.y = p1->y;
            v[1].pos.z = p1->z;
            v[0].color = color0;
            v[1].color = color1;
            p0++;
            p1++;
            v += 2;
        }
        DrawNullSprite(strip, count);
    }
}
#endif

// .text:0x8000E030 size:0x2A4
// NONMATCHING: ~90%, saved-register allocation differs (count/n/angle); .sdata2 constant names need a split
#if NONMATCHING
void fn_8000E030(CircleElem* elem, Mtx mtx, SpriteDrawParams* params) {
    Vec center;
    Vec pt;
    QuadVtx verts[259];
    QuadVtx* v;
    s32 count;
    s32 n;
    s32 step;
    s16 angle;
    f32 s;
    f32 a;
    f32 c;

    if (!elem->hidden || params->arcSegments != 0) {
        center.x = 128.0f;
        center.y = 128.0f;
        center.z = elem->z;
        PSMTXMultVec(mtx, &center, &verts[0].pos);
        verts[0].color = params->color[0];
        pt.x = 128.0f + center.x;
        pt.y = center.y;
        pt.z = elem->unk18 + elem->z;
        PSMTXMultVec(mtx, &pt, &verts[1].pos);
        verts[1].color = params->color[1];
        if (params->arcSegments != 0) {
            n = params->arcSegments;
            count = params->arcSegments + 2;
        } else {
            count = params->segments + 2;
            n = params->segments - 1;
        }
        step = 0x10000 / params->segments;
        v = &verts[2];
        angle = 0;
        do {
            angle -= step;
            a = 0.0000958738f * angle;
            s = sin(a);
            c = cos(a);
            pt.x = 128.0f * c + center.x;
            pt.y = 128.0f * s + center.y;
            pt.z = elem->z;
            PSMTXMultVec(mtx, &pt, &v->pos);
            v->color = params->color[1];
            v++;
        } while (--n);
        if (params->arcSegments == 0) {
            verts[params->segments + 1].pos.x = verts[1].pos.x;
            verts[params->segments + 1].pos.y = verts[1].pos.y;
            verts[params->segments + 1].pos.z = verts[1].pos.z;
            verts[params->segments + 1].color = params->color[1];
        }
        fn_800B12DC(verts, count);
    }
}
#endif

// .text:0x8000E2D4 size:0x490
// NONMATCHING: ~75% (with w left uninitialized as in the original): scheduling and float register allocation differ
// litcheck: 1.0 (stands in for the uninitialized w)
#if NONMATCHING
void fn_8000E2D4(Circle2DElem* elem, Mtx mtx, SpriteDrawParams* params) {
    Vec pos[257];
    u32 colors[257];
    Vec* p;
    u32* c;
    s32 i;
    s32 n;
    s32 step;
    s16 angle;
    f32 x;
    f32 y;
    f32 w = 1.0f; // the original reads an uninitialized register here
    f32 px;
    f32 py;
    f32 a;
    f32 s;

    if (!elem->hidden || params->arcSegments != 0) {
        for (p = pos, i = 0; i < 257; i++, p++) {
            p->x = 0.0f;
            p->y = 0.0f;
            p->z = 0.0f;
        }
        colors[0] = params->color[0];
        angle = 0;
        y = 128 - elem->y;
        x = 128 - elem->x;
        pos[0].x = (s32)(mtx[0][0] * x + mtx[0][1] * y + mtx[0][3] * w);
        pos[0].y = (s32)(mtx[1][0] * x + mtx[1][1] * y + mtx[1][3] * w);
        pos[0].z = (s32)(mtx[2][0] * x + mtx[2][1] * y + mtx[2][3] * w);
        colors[1] = params->color[1];
        step = 0x10000 / params->segments;
        pos[1].x = (s32)(mtx[0][0] * (128.0f + x) + mtx[0][1] * (128.0f + y) + mtx[0][3] * w);
        pos[1].y = (s32)(mtx[1][0] * (128.0f + x) + mtx[1][1] * (128.0f + y) + mtx[1][3] * w);
        pos[1].z = (s32)(mtx[2][0] * (128.0f + x) + mtx[2][1] * (128.0f + y) + mtx[2][3] * w);
        n = params->segments;
        if (n != params->arcSegments) {
            n = params->arcSegments + 1;
        }
        p = &pos[n];
        c = &colors[n];
        do {
            angle -= step;
            a = 0.0000958738f * angle;
            s = sin(a);
            py = 128.0f * s + y;
            px = 128.0f * (f32)cos(a) + x;
            p->x = (s32)(mtx[0][0] * px + mtx[0][1] * py + mtx[0][3] * w);
            p->y = (s32)(mtx[1][0] * px + mtx[1][1] * py + mtx[1][3] * w);
            p->z = (s32)(mtx[2][0] * px + mtx[2][1] * py + mtx[2][3] * w);
            p--;
            *c = params->color[1];
            c--;
        } while (--n);
        if (params->segments == params->arcSegments) {
            pos[params->arcSegments + 1].x = pos[1].x;
            pos[params->arcSegments + 1].y = pos[1].y;
            pos[params->arcSegments + 1].z = pos[1].z;
            colors[params->arcSegments + 1] = params->color[1];
        }
        fn_800B13C0(pos, colors, params->arcSegments + 2);
    }
}
#endif

// .text:0x8000E764 size:0x58
void fn_8000E764(f32 angle, Vec2f* out) {
    out->x = sin(angle);
    out->y = cos(angle);
}

// .text:0x8000E7BC size:0x144
void fn_8000E7BC(SpriteElem* elem, Mtx mtx, SpriteDrawParams* params, s32 perCorner) {
    SpriteQuad q;

    q.xy[0][0] = 0.0f;
    q.xy[0][1] = 0.0f;
    q.xy[3][0] = 256.0f;
    q.xy[3][1] = 256.0f;
    q.xy[1][0] = 256.0f;
    q.xy[1][1] = 0.0f;
    q.xy[2][0] = 0.0f;
    q.xy[2][1] = 256.0f;
    AddVec2iToQuad(&q, mtx, params);
    lbl_80366188.unk7E = 0;
    lbl_80366188.elem = elem;
    lbl_80366188.u.v[0].color = params->color[0];
    lbl_80366188.u.v[0].pos.x = q.pt[0].pos.x;
    lbl_80366188.u.v[0].pos.y = q.pt[0].pos.y;
    lbl_80366188.u.v[0].pos.z = q.pt[0].pos.z;
    lbl_80366188.u.v[1].pos.x = q.pt[1].pos.x;
    lbl_80366188.u.v[1].pos.y = q.pt[1].pos.y;
    lbl_80366188.u.v[1].pos.z = q.pt[1].pos.z;
    lbl_80366188.u.v[2].pos.x = q.pt[3].pos.x;
    lbl_80366188.u.v[2].pos.y = q.pt[3].pos.y;
    lbl_80366188.u.v[2].pos.z = q.pt[3].pos.z;
    lbl_80366188.u.v[3].pos.x = q.pt[2].pos.x;
    lbl_80366188.u.v[3].pos.y = q.pt[2].pos.y;
    lbl_80366188.u.v[3].pos.z = q.pt[2].pos.z;
    lbl_80366188.perCornerColor = elem->perCorner | (perCorner | (elem->type == 2));
    if (lbl_80366188.perCornerColor) {
        lbl_80366188.u.v[1].color = params->color[3];
        lbl_80366188.u.v[2].color = params->color[2];
        lbl_80366188.u.v[3].color = params->color[1];
    } else {
        lbl_80366188.u.v[1].color = params->color[0];
        lbl_80366188.u.v[2].color = params->color[0];
        lbl_80366188.u.v[3].color = params->color[0];
    }
}

#ifdef TARGET_PC
#include "main/file_80034F50.h"
// MSSB_SPANI_TRACE: log each distinct (bank, texture index) a sprite draws, once, with its size/format
// and the sprite object that drew it (to identify which object/bank a given image comes from).
static void port_trace_tex_use(SpriteBank* bank, s32 texIdx, TexImage* tex) {
    extern int port_spani_trace_on(void);
    extern u32 port_spani_trace_frame;
    extern void OSReport(const char*, ...);
    extern SpaniObj lbl_8039C3E0[];
    extern SpaniObj* lbl_803CBC9C;
    static struct { void* bank; s32 idx; } s_seen[1024];
    static s32 s_n;
    s32 i;
    if (!port_spani_trace_on()) {
        return;
    }
    for (i = 0; i < s_n; i++) {
        if (s_seen[i].bank == bank && s_seen[i].idx == texIdx) {
            return;
        }
    }
    if (s_n < 1024) {
        s_seen[s_n].bank = bank;
        s_seen[s_n].idx = texIdx;
        s_n++;
    }
    {
        SpaniObj* o = lbl_803CBC9C;
        OSReport("[texuse] f=%u bank %p tex %d %dx%d fmt %d ci %d obj %d anim %d layer %d slot %d\n",
                 port_spani_trace_frame, (void*)bank, (int)texIdx, (int)tex->width, (int)tex->height,
                 (int)tex->format, tex->tlut != 0, o ? (int)(o - lbl_8039C3E0) : -1,
                 o ? (int)o->animId : -1, o ? (int)o->layer : -1, o ? (int)o->texSlot : -1);
    }
}
#define PORT_TRACE_TEX_USE(b, i, t) port_trace_tex_use((b), (i), (t))
#else
#define PORT_TRACE_TEX_USE(b, i, t)
#endif

// .text:0x8000E900 size:0x30C
void SetSpriteRect(SpriteRectElem* elem, SpriteBank* bank, Mtx mtx, SpriteDrawParams* params, s32 perCorner) {
    SpriteQuad q;
    TexImage* tex;
    f32 x = 0.0f;
    f32 y = 0.0f;

    tex = TEX_ARCHIVE_IMG(bank, elem->texIdx);
    lbl_803CBBD8 = tex;
    PORT_TRACE_TEX_USE(bank, elem->texIdx, tex);
    q.xy[0][0] = x;
    q.xy[0][1] = y;
    q.xy[1][0] = x + tex->width;
    q.xy[1][1] = y;
    q.xy[2][0] = x;
    q.xy[2][1] = y + tex->height;
    q.xy[3][0] = q.xy[1][0];
    q.xy[3][1] = q.xy[2][1];
    AddVec2iToQuad(&q, mtx, params);
    lbl_80366188.unk7E = 0;
    lbl_80366188.u.v[0].color = params->color[0];
    lbl_80366188.u.v[1].color = params->color[1];
    lbl_80366188.u.v[2].color = params->color[2];
    lbl_80366188.u.v[3].color = params->color[3];
    if (elem->flipX && elem->flipY) {
        SET_QUAD_POS(3, 1, 0, 2);
    } else if (elem->flipX) {
        SET_QUAD_POS(1, 3, 2, 0);
    } else if (elem->flipY) {
        SET_QUAD_POS(2, 0, 1, 3);
    } else {
        SET_QUAD_POS(0, 2, 3, 1);
    }
    lbl_80366188.u.v[0].s = 0;
    lbl_80366188.u.v[0].t = 0;
    lbl_80366188.u.v[1].s = 0;
    lbl_80366188.u.v[1].t = 0x400;
    lbl_80366188.u.v[2].s = 0x400;
    lbl_80366188.u.v[2].t = 0x400;
    lbl_80366188.u.v[3].s = 0x400;
    lbl_80366188.u.v[3].t = 0;
    lbl_80366188.bank = bank;
    lbl_80366188.perCornerColor = perCorner | elem->perCorner;
}

// .text:0x8000EC0C size:0x310
void fn_8000EC0C(SpriteElem* elem, SpriteBank* bank, Mtx mtx, SpriteDrawParams* params, s32 perCorner) {
    SpriteQuad q;
    TexImage* tex;
    f32 x = 0.0f;
    f32 y = 0.0f;

    tex = TEX_ARCHIVE_IMG(bank, elem->texIdx);
    lbl_803CBBD8 = tex;
    PORT_TRACE_TEX_USE(bank, elem->texIdx, tex);
    q.xy[0][0] = x;
    q.xy[0][1] = y;
    q.xy[1][0] = x + tex->width;
    q.xy[1][1] = y;
    q.xy[2][0] = x;
    q.xy[2][1] = y + tex->height;
    q.xy[3][0] = q.xy[1][0];
    q.xy[3][1] = q.xy[2][1];
    AddVec2iToQuad(&q, mtx, params);
    lbl_80366188.unk7E = 0;
    lbl_80366188.elem = elem;
    lbl_80366188.u.v[0].color = params->color[0];
    lbl_80366188.u.v[1].color = params->color[1];
    lbl_80366188.u.v[2].color = params->color[2];
    lbl_80366188.u.v[3].color = params->color[3];
    if (elem->flipX && elem->flipY) {
        SET_QUAD_POS(3, 1, 0, 2);
    } else if (elem->flipX) {
        SET_QUAD_POS(1, 3, 2, 0);
    } else if (elem->flipY) {
        SET_QUAD_POS(2, 0, 1, 3);
    } else {
        SET_QUAD_POS(0, 2, 3, 1);
    }
    lbl_80366188.u.v[0].s = 0;
    lbl_80366188.u.v[0].t = 0;
    lbl_80366188.u.v[1].s = 0;
    lbl_80366188.u.v[1].t = 1;
    lbl_80366188.u.v[2].s = 1;
    lbl_80366188.u.v[2].t = 1;
    lbl_80366188.u.v[3].s = 1;
    lbl_80366188.u.v[3].t = 0;
    lbl_80366188.bank = bank;
    lbl_80366188.perCornerColor = perCorner | elem->perCorner;
}

// .text:0x8000EF1C size:0x234
// NONMATCHING ~85%: saved-register/scheduling differences; float constants
// are unnamed until this unit's .sdata2 is split.
#if NONMATCHING
void AddVec2iToQuad(SpriteQuad* quad, Mtx mtx, SpriteDrawParams* params) {
    Mtx m;
    QuadPoint pts[4];
    s32 i;

    for (i = 0; i < 4; i++) {
        pts[i].pos.x = quad->xy[i][0] + params->ofs[i][0];
        pts[i].pos.y = quad->xy[i][1] + params->ofs[i][1];
        pts[i].pos.z = 0.0f;
    }
    PSMTXCopy(mtx, m);
    PSMTXMultVec(m, &pts[0].pos, &pts[0].pos);
    PSMTXMultVec(m, &pts[1].pos, &pts[1].pos);
    PSMTXMultVec(m, &pts[2].pos, &pts[2].pos);
    PSMTXMultVec(m, &pts[3].pos, &pts[3].pos);
    for (i = 0; i < 4; i++) {
        quad->pt[i].pos.x = pts[i].pos.x;
        quad->pt[i].pos.y = pts[i].pos.y;
    }
    for (i = 0; i < 4; i++) {
        quad->pt[i].pos.z = pts[i].pos.z;
    }
}
#endif

// ---- Data (initialisers generated from the original DOL) ----

// .sbss 0x803CBBD8..0x803CBBDC (MWCC lays these out in reverse definition order)
TexImage* lbl_803CBBD8;

