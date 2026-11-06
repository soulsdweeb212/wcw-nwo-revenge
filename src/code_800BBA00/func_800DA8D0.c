/* @header
 * func_800DA8D0
 * VRAM 0x800DA8D0 | ROM 0xCDD70 | size 0xF0
 * asm: asm/nonmatchings/code_800BBA00/func_800DA8D0.s
 */
#include "common.h"

/* Looks for a present wrestler targeting arg0 in states 0x6B..0x6D at step 2..3
 * with unk034 bit 2 set and bit 1 clear; marks it with unk034 bit 0x10 and
 * returns 1, else 0. */
s32 func_800DA8D0(Wrestler *arg0) {
    s16 i;
    for (i = 0; i < 4; i++) {
        if (D_800F9D10[i].characterId == -1) continue;
        if (D_800F9D10[i].opponentId != arg0->id) continue;
        if (D_800F9D10[i].state >= 0x6E) continue;
        if (D_800F9D10[i].state < 0x6B) continue;
        if ((D_800F9D10[i].unk034 & 2) == 0) continue;
        if ((u32)((u16)D_800F9D10[i].step - 2) >= 2) continue;
        if (D_800F9D10[i].unk034 & 1) continue;
        D_800F9D10[i].unk034 |= 0x10;
        return 1;
    }
    return 0;
}
