/* @header
 * func_800D63F0
 * VRAM 0x800D63F0 | ROM 0xC9890 | size 0x1E0
 * asm: asm/nonmatchings/code_800BBA00/func_800D63F0.s
 */
#include "common.h"

/* Movement speed of the wrestler (several callers turn it into moveDelta with
 * func_800D37C0(heading, speed, moveDelta); which gait each mode is, is not
 * known). Picks the threshold table by the profile's
 * speed tier (s8 at profile + 4), then walks it while bodyPart[3] (read through
 * func_800BF1E0, 50 under WR_FLAG_SPECIAL) is below table[i], lowering the tier
 * by one each step. Reads the X/Z speeds from the interleaved
 * D_800E3F64/D_800E3F68 tables at that tier, applies the mode (2 doubles both,
 * 3/4 set X to 1.5), writes X/Z to out[0]/out[2] when out is given, then for a
 * wrestler on the apron (WR_FLAG_ON_APRON) sets X to 3 in mode 0 and 12 in
 * mode 2; mode 5 sets X to 8. Returns X. */
extern s16 D_800E3F50[], D_800E3F54[], D_800E3F5C[];
extern f32 D_800E3F64[][2], D_800E3F68[][2];
s16 func_800BF1E0(void *, s32);
f32 func_800D63F0(Wrestler *w, f32 *out, s16 mode) {
    s16 *table; s32 i; s16 level; f32 x, z;
    switch (*(s8 *)(w->profile + 4)) {
    case 1: table = D_800E3F50; break;
    case 2: table = D_800E3F54; break;
    case 3: table = D_800E3F5C; break;
    }
    i = 0; level = *(s8 *)(w->profile + 4);
    while (func_800BF1E0(w, 3) < table[(s16)i]) { i++; level--; }
    x = D_800E3F64[level][0]; z = D_800E3F68[level][0];
    if (mode == 2) { x *= 2.0; z *= 2.0; }
    if (mode == 3) x = 1.5f;
    if (mode == 4) x = 1.5f;
    if (out) { out[0] = x; out[2] = z; }
    if (w->flags & WR_FLAG_ON_APRON) {
        if (mode == 0) x = 3.0f;
        if (mode == 2) x = 12.0f;
    }
    if (mode == 5) x = 8.0f;
    return x;
}
