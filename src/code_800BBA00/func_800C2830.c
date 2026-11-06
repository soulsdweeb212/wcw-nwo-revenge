/* @header
 * func_800C2830
 * VRAM 0x800C2830 | ROM 0xB5CD0 | size 0x40
 * asm: asm/nonmatchings/code_800BBA00/func_800C2830.s
 */
#include "common.h"

extern u8 D_8007EF30[];
extern u8 D_800FABE8[], D_800FABEC[], D_800FABEE[];

/* Returns 1 when w->flags has bit 0 or 1 set, or when the u16 at
 * D_8007EF30 + 0x170 has neither bit 0x400 nor bit 4; otherwise 0. */
s32 func_800C2830(Wrestler *w) {
    if (w->flags & 3) return 1;
    return (*(u16 *)(D_8007EF30 + 0x170) & 0x404) == 0;
}
