/* @header
 * func_800A71A8
 * VRAM 0x800A71A8 | ROM 0x53918 | size 0xE8
 * asm: asm/nonmatchings/code_80090000/func_800A71A8.s
 */
#include "common.h"

#ifndef TARGET_PC /* on PC, port.h defines Gfx, the 16-byte command */
typedef struct { u32 w0; u32 w1; } Gfx;
#endif
#define W(a, b) { Gfx *t = g++; t->w0 = (a); t->w1 = (b); }

void func_800A71A8(Gfx **dl, u8 *c) {
    Gfx *g = *dl;
    W(0xFA000000, ((c[0x17] >> 1) << 24) | ((c[0x17] >> 1) << 16) | ((c[0x17] >> 1) << 8) | (c[0x16] >> 1));
    W(0xE7000000, 0);
    W(0xFC51FEA3, 0x44FE773B);
    W(0x7000206, 0x604);
    W(0xE7000000, 0);
    W(0xFA000000, (c[0x17] << 24) | (c[0x17] << 16) | (c[0x17] << 8) | c[0x16]);
    *dl = g;
}
