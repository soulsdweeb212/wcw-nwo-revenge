/* @header
 * func_800D4148
 * VRAM 0x800D4148 | ROM 0xC75E8 | size 0x50
 * asm: asm/nonmatchings/code_800BBA00/func_800D4148.s
 */
#include "common.h"

extern u16 D_800EB638[];
s32 guRandom(void);
s32 func_800D4204(void);

/* Replace one of the 32 rolling slots in D_800EB638 (chosen by the low 5 bits of
 * guRandom()) with a fresh random value and return the previous value. */
s32 func_800D4148(void) {
    s32 i = guRandom() & 0x1F;
    u16 old = D_800EB638[i];
    D_800EB638[i] = func_800D4204();
    return (s16)old;
}
