#include "common.h"

extern s8 D_800706A4[];
extern s8 D_800485B0[];
extern s8 D_800485D0[];
extern u8 D_800517D0[];

void setIndexedS16Pair(s32, s32, s8, s8);
void func_80001DC4(void *);
void buildEntityPartTransforms(void *, s32, f32, f32);

/* Per-part state byte for a part index. */
s8 func_8000B710(s32 partIndex) {
    return D_800706A4[(s16)partIndex];
}

/* Flushes all 8 pending per-entity part entries: each entry that is still
 * pending (>= 0) is forwarded to setIndexedS16Pair and then cleared to -1. */
void func_8000B2B8(s32 entityIndex) {
    s16 e = (s16)entityIndex;
    s8 *pending = D_800485B0 + e * 8;
    s8 *values = D_800485D0 + e * 8;
    s32 i = 0;

    do {
        s8 *p = pending + (s16)i;
        s8 v = *p;

        if (v >= 0) {
            setIndexedS16Pair(e, 0, values[(s16)i], v);
            *p = -1;
        }
        i++;
    } while (i < 8U);
}

/* Flushes a single pending per-entity part entry (single-element form of
 * func_8000B2B8). */
void func_8000B248(s32 entityIndex, s32 partIndex) {
    s8 *p = D_800485B0 + (s16)entityIndex * 8 + (s16)partIndex;
    s8 v = *p;

    if (v >= 0) {
        setIndexedS16Pair((s16)entityIndex, 0, D_800485D0[(s16)entityIndex * 8 + (s16)partIndex], v);
        *p = -1;
    }
}

/* Rebuilds the part transforms of an entity, then recomputes its transform
 * node from the given pose values. */
void func_8000CD18(s32 entityIndex, f32 arg1, f32 arg2) {
    u8 *entity = D_800517D0 + (s16)entityIndex * 0x13C4;

    buildEntityPartTransforms(entity, (s16)entityIndex, arg1, arg2);
    func_80001DC4(entity);
}
