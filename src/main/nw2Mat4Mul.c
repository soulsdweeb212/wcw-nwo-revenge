/* @header
 * nw2Mat4Mul  (originally func_8001B310)
 * VRAM 0x8001B310 | ROM 0x1BF10 | size 0xDC
 * asm: asm/nonmatchings/main/func_8001B310.s
 */
#include "common.h"

/* Multiply two 4x4 float matrices: out = a * b, computed into a temporary so
 * that out may alias a or b. */
void nw2Mat4Mul(f32 a[4][4], f32 b[4][4], f32 out[4][4]) {
    f32 m[4][4];
    s32 row, col, n;

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            m[row][col] = 0.0f;
            for (n = 0; n < 4; n++) {
                m[row][col] += a[row][n] * b[n][col];
            }
        }
    }
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            out[row][col] = m[row][col];
        }
    }
}
