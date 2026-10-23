#include "common.h"

/* Builds the 4x4 identity matrix in float and converts it to the 2x4
 * fixed-point word layout (two 16.16 values packed per word pair) at out. */
void func_8001B220(s32 *out) {
    f32 m[4][4];
    s32 *w;
    s32 *q;
    s32 i, j;
    s32 k, l;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == j) {
                m[i][i] = 1.0f;
            } else {
                m[i][j] = 0.0f;
            }
        }
    }

    w = out;
    q = out + 8;
    for (k = 0; k < 4; k++) {
        for (l = 0; l < 2; l++) {
            s32 v0 = m[k][l * 2] * 65536.0f;
            s32 v1 = m[k][l * 2 + 1] * 65536.0f;

            *w++ = (v0 & 0xFFFF0000) | ((u32)v1 >> 16);
            *q++ = ((v0 << 16) & 0xFFFF0000) | (v1 & 0xFFFF);
        }
    }
}
