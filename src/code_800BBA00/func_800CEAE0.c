#include "common.h"

extern f64 D_800E6A10, D_800E6A18, D_800E6A20;
extern f32 D_800FADE4[][23], D_800FADEC[][23];
s8 func_800D3B24(void *, void *, f32, s32);
/* Proximity test between a source (arg0) and a target entity (arg1): interpolate
 * the source's XZ between +0xEC/F4 and +0x16C/174 by D_800E6A10, then test that
 * point against the target's +0x8C circle (margin D_800FADEC + D_800E6A18)
 * first, and failing that against the target's +0x6C circle (D_800FADE4 scaled
 * by D_800E6A20 + margin). */
s32 func_800CEAE0(u8 *arg0, s8 *arg1) {
    f32 point[3];
    f64 margin;
    s32 hit;
    point[0] = (*(f32 *)(arg0 + 0x16C) - *(f32 *)(arg0 + 0xEC)) * D_800E6A10 + *(f32 *)(arg0 + 0xEC);
    point[2] = (*(f32 *)(arg0 + 0x174) - *(f32 *)(arg0 + 0xF4)) * D_800E6A10 + *(f32 *)(arg0 + 0xF4);
    margin = D_800E6A18;
    if (func_800D3B24(point, arg1 + 0x8C, D_800FADEC[*arg1][0] + margin, 0)) hit = 1;
    else hit = func_800D3B24(point, arg1 + 0x6C, D_800FADE4[*arg1][0] * D_800E6A20 + margin, 0) != 0;
    return hit;
}
