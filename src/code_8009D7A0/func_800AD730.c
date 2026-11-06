/* @header
 * func_800AD730
 * VRAM 0x800AD730 | ROM 0xA0BD0 | size 0x7C
 * asm: asm/nonmatchings/code_8009D7A0/func_800AD730.s
 */
#include "common.h"

extern s16 D_800EB420[];

/* Return wrestler index's D_800EB420 value when its profile has flag bit 0 set
 * (+0x38) and it is in state 75; otherwise -1. */
s32 func_800AD730(s16 index)
{
    if (*(u64 *)(D_800F9D10[index].profile + 0x38) & 1)
    {
        if (D_800F9D10[index].state == 75)
            return D_800EB420[index];
        return -1;
    }
    return -1;
}
