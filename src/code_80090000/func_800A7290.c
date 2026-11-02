/* @header
 * func_800A7290
 * VRAM 0x800A7290 | ROM 0x53A00 | size 0x110
 * asm: asm/nonmatchings/code_80090000/func_800A7290.s
 */
#include "common.h"

void func_800B7A00(Nw2GfxCommand **, s32, s32);
#define E(a, b) { Nw2GfxCommand *q = g++; q->w0 = (u32)(a); q->w1 = (u32)(b); }

void func_800A7290(Nw2GfxCommand **dl, u8 *r, s32 id, s32 f) {
    Nw2GfxCommand *g = *dl;
    E(0xE7000000, 0);
    E(0xFA000000, r[0x16] >> 1);
    E(0xFC51FEA3, 0x44FE773B);
    E(0x07080A0E, 0x00080E0C);
    E(0xE7000000, 0);
    E(0xFA000000, r[0x16]);
    E(0xFC5196A3, 0x112CFE7F);
    func_800B7A00(&g, id, f | 0x18);
    E(0x07080A0E, 0x00080E0C);
    *dl = g;
}
