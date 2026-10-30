/* @header
 * func_8000B370
 * VRAM 0x8000B370 | ROM 0xBF70 | size 0x54
 * asm: asm/nonmatchings/main/func_8000B370.s
 */
#include "common.h"

extern u16 D_8006A2A4[];
extern s16 *D_80031998[];
extern f32 D_800318C0[];

/* Decode part arg0's entry: pick the group and index from D_8006A2A4, read the s16
 * from D_80031998, and return the float for its 0x7000 field in D_800318C0. */
f32 func_8000B370(s32 arg0) {
    u16 v = D_8006A2A4[(s16)arg0];
    u32 g = (v >> 8) & 0x1F;
    u32 n = (v & 0x1F) - 1;
    s16 x = D_80031998[g][n];
    u32 m = x;
    m &= 0x7000;
    return D_800318C0[m >> 12];
}
