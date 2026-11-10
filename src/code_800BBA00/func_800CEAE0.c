/* @header
 * func_800CEAE0
 * VRAM 0x800CEAE0 | ROM 0xC1F80 | size 0x130
 * asm: asm/nonmatchings/code_800BBA00/func_800CEAE0.s
 */
#include "common.h"

extern f64 D_800E6A10, D_800E6A18, D_800E6A20;
extern f32 D_800FADE4[][23], D_800FADEC[][23];
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D3B24 */
s8 func_800D3B24(void *, void *, f32, s32);
#endif
/* Proximity test between a source (src) and a target wrestler (tgt): interpolate
 * the source's XZ between jointA[9] and jointA[17] by D_800E6A10, then test that
 * point against the target's jointA[3] circle (radius D_800FADEC[tgt->id][0] +
 * D_800E6A18) first, and failing that against the target's pelvis (jointA[1])
 * circle (D_800FADE4[tgt->id][0] scaled by D_800E6A20 + D_800E6A18). */
s32 func_800CEAE0(Wrestler *src, Wrestler *tgt) {
    f32 point[3];
    f64 margin;
    s32 hit;
    point[0] = (src->jointA[17].x - src->jointA[9].x) * D_800E6A10 + src->jointA[9].x;
    point[2] = (src->jointA[17].z - src->jointA[9].z) * D_800E6A10 + src->jointA[9].z;
    margin = D_800E6A18;
    if (func_800D3B24(point, &tgt->jointA[3], D_800FADEC[tgt->id][0] + margin, 0)) hit = 1;
    else hit = func_800D3B24(point, &tgt->jointA[1], D_800FADE4[tgt->id][0] * D_800E6A20 + margin, 0) != 0;
    return hit;
}
