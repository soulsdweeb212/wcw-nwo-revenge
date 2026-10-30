/* @header
 * func_800AD730
 * VRAM 0x800AD730 | ROM 0xA0BD0 | size 0x7C
 * asm: asm/nonmatchings/code_8009D7A0/func_800AD730.s
 */
#include "common.h"

extern s16 D_800EB420[], D_800F9D1A[][0x1d8];
extern u8 *D_800FA074[][0xec];

/* Return entity index's base value when its linked record has flag bit 0 set and
 * its state is 75; otherwise -1. */
s32 func_800AD730(s16 index)
{
    if (*(u64 *)(D_800FA074[index][0] + 0x38) & 1)
    {
        if (D_800F9D1A[index][0] == 75)
            return D_800EB420[index];
        return -1;
    }
    return -1;
}
