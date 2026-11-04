/* @header
 * func_800C55B0
 * VRAM 0x800C55B0 | ROM 0x71D20 | size 0x168
 * asm: asm/nonmatchings/code_80090000/func_800C55B0.s
 */
#include "common.h"



typedef struct { s32 p; u16 a; u16 b; s16 c; s8 x; s8 y; } P;
extern P D_8006E178[];
extern u16 D_800EA0C0[], D_800EA0C8[];
extern u16 D_800EA0C2, D_800EA0C4;
extern s8 D_800EA0C6, D_800EA0C7;
extern s32 D_800D5F1C;

void func_800C55B0(s32 mode) {
    s32 ymin = 0, ymax = 0, xmin = 0, xmax;
    s32 i, n, v;
    D_800EA0C4 = 0;
    D_800EA0C2 = 0;
    D_800EA0C0[0] = 0;
    xmax = 0;
    if (mode == 5) {
        n = D_800D5F1C;
        if (n >= 5) {
            n = 4;
        }
    } else {
        n = D_800D5F1C;
        if (n >= 3) {
            n = 2;
        }
    }
    for (i = 0; i < n; i++) {
        D_800EA0C0[0] |= D_8006E178[i].a;
        D_800EA0C0[1] |= D_8006E178[i].b;
        D_800EA0C0[2] |= D_800EA0C8[i];
        v = D_8006E178[i].x;
        if (xmax < v) {
            xmax = v;
        }
        if (v < xmin) {
            xmin = v;
        }
        v = D_8006E178[i].y;
        if (ymax < v) {
            ymax = v;
        }
        if (v < ymin) {
            ymin = v;
        }
    }
    if (-xmin < xmax) {
        D_800EA0C6 = xmax;
    } else {
        D_800EA0C6 = xmin;
    }
    if (-ymin < ymax) {
        D_800EA0C7 = ymax;
    } else {
        D_800EA0C7 = ymin;
    }
}
