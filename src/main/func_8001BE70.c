/* @header
 * func_8001BE70
 * VRAM 0x8001BE70 | ROM 0x1CA70 | size 0x60
 * asm: asm/nonmatchings/main/func_8001BE70.s
 */
#include "common.h"

/* Build a 4x4 scale matrix from an identity matrix, with diagonal scale factors
 * (sx, sy, sz). */
void func_8001BE70(void *matrix, f32 sx, f32 sy, f32 sz) {
    initIdentityMatrix4x4(matrix);
    *(f32 *)((s8 *)matrix + 0) = sx;
    *(f32 *)((s8 *)matrix + 0x14) = sy;
    *(f32 *)((s8 *)matrix + 0x28) = sz;
    *(f32 *)((s8 *)matrix + 0x3C) = 1.0f;
}
