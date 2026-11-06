/* @header
 * func_800A9028
 * VRAM 0x800A9028 | ROM 0x9C4C8 | size 0xD4
 * asm: asm/nonmatchings/code_8009D7A0/func_800A9028.s
 */
#include "common.h"

/* Return the state-derived action mask for wrestler arg0:
 * state 0x58 -> 4, state 0x3E -> 2, state 0x49 -> 1 only when grappleCtx has
 * bit 2 set, state 7 -> 0x10 only when flags contain 0x10000000000; otherwise 0. */
s32 func_800A9028(s16 arg0) {
    s16 state = D_800F9D10[arg0].state;
    s32 result = 0;

    switch (state) {
    case 0x58: result = 4; break;
    case 0x49: if (D_800F9D10[arg0].grappleCtx & 2) result = 1; break;
    case 0x3E: result = 2; break;
    case 7: if (D_800F9D10[arg0].flags & 0x10000000000ULL) result = 0x10; break;
    }
    return result;
}
