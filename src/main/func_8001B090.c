#include "common.h"

/* Converts the 4x4 float matrix in into the 2x4 fixed-point word/halfword
 * layout at out (16.16 values split across two word arrays). */
void func_8001B090(f32 *in, s32 *out) {
    s32 *p = out;
    s32 *q = out + 8;
    s32 i;

    for (i = 0; i < 4; i++) {
        f32 *base = in + i * 4;
        s32 j;
        f32 *row;
        j = 0;
        row = base;
        for (; j < 2; j++) {
            s32 v0 = *row * 65536.0f;
            s32 v1 = row[1] * 65536.0f;

            row += 2;
            *p++ = (v0 & 0xFFFF0000) | ((u32)v1 >> 16);
            *q++ = ((v0 << 16) & 0xFFFF0000) | (v1 & 0xFFFF);
        }
    }
}
