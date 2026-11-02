/* @header
 * func_800B6B5C
 * VRAM 0x800B6B5C | ROM 0x632CC | size 0x20C
 * asm: asm/nonmatchings/code_80090000/func_800B6B5C.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;

void func_800B6B5C(G **dl, s32 f, s32 w, s32 h, u32 t, u32 p) {
    G *g = *dl;

    if (f) {
        { G *d = g++; d->w0 = 0xFD100000; d->w1 = p - 0x80000000; }
        { G *d = g++; d->w0 = 0xE8000000; d->w1 = 0; }
        { G *d = g++; d->w0 = 0xF5000100; d->w1 = 0x07000000; }
        { G *d = g++; d->w0 = 0xE6000000; d->w1 = 0; }
        { G *d = g++; d->w0 = 0xF0000000; d->w1 = 0x073FC000; }
        { G *d = g++; d->w0 = 0xE7000000; d->w1 = 0; }
        { G *d = g++; d->w0 = ((w - 1) & 0xFFF) | 0xFD480000; d->w1 = t - 0x80000000; }
        { G *d = g++; d->w0 = (((h + 7) >> 3 & 0x1FF) << 9) | 0xF5480000; d->w1 = 0x07000000; }
        { G *d = g++; d->w0 = (((h + 7) >> 3 & 0x1FF) << 9) | 0xF5480000; d->w1 = 0; }
    } else {
        { G *d = g++; d->w0 = 0xFD100000; d->w1 = p - 0x80000000; }
        { G *d = g++; d->w0 = 0xE8000000; d->w1 = 0; }
        { G *d = g++; d->w0 = 0xF5000100; d->w1 = 0x07000000; }
        { G *d = g++; d->w0 = 0xE6000000; d->w1 = 0; }
        { G *d = g++; d->w0 = 0xF0000000; d->w1 = 0x0703C000; }
        { G *d = g++; d->w0 = 0xE7000000; d->w1 = 0; }
        { G *d = g++; d->w0 = ((w - 1) & 0xFFF) | 0xFD400000; d->w1 = t - 0x80000000; }
        { G *d = g++; d->w0 = 0xF5400000; d->w1 = 0x07000000; }
        { G *d = g++; d->w0 = 0xF5400000; d->w1 = 0; }
    }
    *dl = g;
}
