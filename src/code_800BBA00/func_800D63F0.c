#include "common.h"

/* Range/threshold helper for an entity's attachment. Picks the threshold
 * table by the attachment tier (s8 at p[0x364]+4), then walks it downward
 * while func_800BF1E0(p,3) is below table[i], decrementing the level. Reads
 * the X/Z scale from the interleaved D_800E3F64/D_800E3F68 tables at that
 * level, applies the mode multipliers (2 doubles, 3/4 -> 1.5, 5 -> 8), writes
 * X/Z to `out` (+0 and +8) when given, and overrides X for flagged entities
 * (+0x20 bit 0x80). Returns the resulting X. */
extern s16 D_800E3F50[], D_800E3F54[], D_800E3F5C[];
extern f32 D_800E3F64[][2], D_800E3F68[][2];
s16 func_800BF1E0(void *, s32);
#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))
f32 func_800D63F0(void *p, void *out, s16 mode) {
    s16 *table; s32 i; s16 level; f32 x, z;
    switch (F(F(p, void *, 0x364), s8, 4)) {
    case 1: table = D_800E3F50; break;
    case 2: table = D_800E3F54; break;
    case 3: table = D_800E3F5C; break;
    }
    i = 0; level = F(F(p, void *, 0x364), s8, 4);
    while (func_800BF1E0(p, 3) < table[(s16)i]) { i++; level--; }
    x = D_800E3F64[level][0]; z = D_800E3F68[level][0];
    if (mode == 2) { x *= 2.0; z *= 2.0; }
    if (mode == 3) x = 1.5f;
    if (mode == 4) x = 1.5f;
    if (out) { F(out, f32, 0) = x; F(out, f32, 8) = z; }
    if (F(p, u64, 0x20) & 0x80) {
        if (mode == 0) x = 3.0f;
        if (mode == 2) x = 12.0f;
    }
    if (mode == 5) x = 8.0f;
    return x;
}
