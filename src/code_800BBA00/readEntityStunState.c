/* @header
 * readEntityStunState  (originally func_800BFB20)
 * VRAM 0x800BFB20 | ROM 0xB2FC0 | size 0x170
 * asm: asm/nonmatchings/code_800BBA00/readEntityStunState.s
 */
#include "common.h"

s16 updateEntityStunTimer(void *, s32, s32);
/* Reads wrestler arg0's spirit and SPECIAL timer. While SPECIAL is active the
 * spirit reads as 100 and the timer comes from updateEntityStunTimer; otherwise
 * the stored spirit (clamped to 1..99 unless WR_FLAG_SPIRIT_EMPTY is set) is
 * returned with a zero timer. Returns 1 when the 0x40000000000 flag is set. */
s32 readEntityStunState(s8 arg0, s16 *arg1, s16 *arg2) {
    if (D_800F9D10[arg0].flags & WR_FLAG_SPECIAL) {
        *arg1 = 100;
        *arg2 = updateEntityStunTimer(&D_800F9D10[arg0], 0, 4);
    } else {
        *arg1 = D_800F9D10[arg0].spirit;
        if (*arg1 >= 100) *arg1 = 99;
        else if (*arg1 <= 0 && !(D_800F9D10[arg0].flags & WR_FLAG_SPIRIT_EMPTY)) *arg1 = 1;
        *arg2 = 0;
    }
    if (D_800F9D10[arg0].flags & 0x40000000000ULL) return 1;
    return 0;
}
