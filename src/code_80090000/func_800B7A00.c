/* @header
 * func_800B7A00
 * VRAM 0x800B7A00 | ROM 0x64170 | size 0x220
 * asm: asm/nonmatchings/code_80090000/func_800B7A00.s
 */
#include "common.h"

typedef struct { u8 pad0[4]; u32 f4; u8 pad8[4]; s16 w; s16 h; } T;
T *func_800B600C(s32, s32);
void appendPaletteSetupDisplayList(Nw2GfxCommand **);

#define E(a, b) { Nw2GfxCommand *q = g++; q->w0 = (u32)(a); q->w1 = (u32)(b); }

T *func_800B7A00(Nw2GfxCommand **dl, s32 id, s32 b) {
    Nw2GfxCommand *g = *dl;
    T *t;
    t = func_800B600C((id & 0x3FFFFF) | 0xC0000000, b);
    if (t == 0) {
        return 0;
    }
    if (!(b & 0x80000000)) {
        appendPaletteSetupDisplayList(&g);
    }
    E(0xFD500000, t->f4 - 0x80000000);
    E(0xF5500000, 0x07000000);
    E(0xE6000000, 0);
    { Nw2GfxCommand *q = g++;
        s32 n, c;
        s32 pad[1];
        q->w0 = 0xF3000000;
        n = t->w / 16 > 0 ? t->w / 16 + 0x7FF : 0x800;
        c = ((t->w * t->h + 3) >> 2) - 1;
        if (c >= 0x800) {
            c = 0x7FF;
        }
        q->w1 = ((c & 0xFFF) << 12) | 0x07000000 | ((t->w / 16 > 0 ? n / (t->w / 16) : n) & 0xFFF);
    }
    E(0xE7000000, 0);
    E(0xF5400000 | ((((t->w >> 1) + 7) >> 3 & 0x1FF) << 9), 0);
    E(0xF2000000, (((t->w - 1) * 4 & 0xFFF) << 12) | ((t->h - 1) * 4 & 0xFFF));
    *dl = g;
    return t;
}
