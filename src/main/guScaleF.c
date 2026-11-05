/* @header
 * guScaleF  (originally func_8001BE70)
 * VRAM 0x8001BE70 | ROM 0x1CA70 | size 0x60
 * asm: asm/nonmatchings/main/guScaleF.s
 */
/* SDK: libultra 2.0I, ultralib src/gu/scale.c (same code as the SDK source). */
#include "common.h"

/* Build a 4x4 scale matrix from an identity matrix, with diagonal scale factors
 * (sx, sy, sz). */
void guScaleF(void *matrix, f32 sx, f32 sy, f32 sz) {
    guMtxIdentF(matrix);
    *(f32 *)((s8 *)matrix + 0) = sx;
    *(f32 *)((s8 *)matrix + 0x14) = sy;
    *(f32 *)((s8 *)matrix + 0x28) = sz;
    *(f32 *)((s8 *)matrix + 0x3C) = 1.0f;
}
