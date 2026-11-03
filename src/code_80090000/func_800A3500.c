/* @header
 * func_800A3500
 * VRAM 0x800A3500 | ROM 0x4FC70 | size 0x2FC
 * asm: asm/nonmatchings/code_80090000/func_800A3500.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
typedef struct { u8 pad0[0x10]; s16 h; } Spr;
extern s32 D_800CCBF8[];
extern f64 D_800D61F0;
Spr *func_800B600C(s32, s32);
void func_800A2BC0(G **, Spr *, s32 *, s32 *, s32, s32);

static inline void wobble(s32 *x, s32 *y, s32 n) {
    s32 i;
    x[0] = D_800CCBF8[n & 0xF];
    i = n - 1;
    x[1] = D_800CCBF8[i & 0xF];
    i = n - 2;
    x[2] = D_800CCBF8[i & 0xF];
    i = n - 3;
    x[3] = D_800CCBF8[i & 0xF];
    i = n - 4;
    y[0] = D_800CCBF8[i & 0xF];
    i = n - 5;
    y[1] = D_800CCBF8[i & 0xF];
    i = n - 6;
    y[2] = D_800CCBF8[i & 0xF];
    i = n - 7;
    y[3] = D_800CCBF8[i & 0xF];
}

static inline s32 lo(s32 b, s32 w) {
    w--;
    return b - w;
}

static inline s32 hi(s32 b, s32 w) {
    w--;
    return b + w;
}

void func_800A3500(G **dl, u8 *t, s32 id, s32 flags) {
    s32 x[4];
    s32 y[4];
    G *g = *dl;
    Spr *r;
    s32 x0, x1;

    { G *d = g++; d->w0 = 0xE7000000; d->w1 = 0; }
    { G *d = g++; d->w0 = 0xFA000000; d->w1 = t[0x16] >> 1; }
    { G *d = g++; d->w0 = 0xFC51FEA3; d->w1 = 0x44FE773B; }
    { G *d = g++; d->w0 = 0x07000206; d->w1 = 0x604; }
    { G *d = g++; d->w0 = 0xE7000000; d->w1 = 0; }
    { G *d = g++; d->w0 = 0xFA000000; d->w1 = t[0x16]; }
    { G *d = g++; d->w0 = 0xFC5196A3; d->w1 = 0x112CFE7F; }
    r = func_800B600C(id, (flags & 0xFFFF) | 8);
    x0 = -0x3A;
    if (r->h >= 0x80) {
        x1 = 0x3A;
    } else {
        x1 = r->h * D_800D61F0;
        x0 = -(x1 + 3);
        x1 -= 3;
    }
    if (flags & 0x10000) {
        y[3] = 0;
        y[2] = 0;
        y[1] = 0;
        y[0] = 0;
        x[3] = 0;
        x[2] = 0;
        x[1] = 0;
        x[0] = 0;
    } else {
        wobble(x, y, *(s16 *)(t + 0x14));
    }
    x[0] = lo(x0, x[0]);
    x[1] = hi(x1, x[1]);
    x[2] = lo(x0, x[2]);
    x[3] = hi(x1, x[3]);
    y[0] = -6 - y[0];
    y[1] = -6 - y[1];
    y[2] += 6;
    y[3] += 6;
    func_800A2BC0(&g, r, x, y, 4, r->h);
    *dl = g;
}
