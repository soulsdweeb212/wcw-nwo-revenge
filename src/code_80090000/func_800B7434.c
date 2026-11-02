/* @header
 * func_800B7434
 * VRAM 0x800B7434 | ROM 0x63BA4 | size 0x148
 * asm: asm/nonmatchings/code_80090000/func_800B7434.s
 */
#include "common.h"

u8 *func_800B600C(s32, s32);

static inline u8 *load(s32 x, u8 **b, u8 **c) {
    u8 *q;
    u16 n;
    q = func_800B600C(x, 0);
    if (q == 0) {
        return 0;
    }
    n = *(u16 *)(q + 0xA);
    *c = q + 0x10;
    *b = *c + n * 2;
    return q;
}

#define E(a, b) { Nw2GfxCommand *q = g++; q->w0 = (u32)(a); q->w1 = (u32)(b); }
#define PAL(n) \
    E(0xFD100000, (u32)c - 0x80000000); \
    E(0xE8000000, 0); \
    E(0xF5000100, 0x07000000); \
    E(0xE6000000, 0); \
    E(0xF0000000, n); \
    E(0xE7000000, 0);

u8 *func_800B7434(Nw2GfxCommand **dl, s32 a) {
    u8 *b;
    u8 *c;
    Nw2GfxCommand *g = *dl;
    u8 *v;
    v = load(a, &b, &c);
    if (v == 0) {
        return 0;
    }
    if (v[8] == 8) {
        PAL(0x073FC000)
    } else {
        PAL(0x0703C000)
    }
    *dl = g;
    return b;
}
