/* @header
 * func_800DA6DC
 * VRAM 0x800DA6DC | ROM 0xCDB7C | size 0x9C
 * asm: asm/nonmatchings/code_800BBA00/func_800DA6DC.s
 */
#include "common.h"

s8 func_800D8DF0(Wrestler *);
s8 func_800D96A0(Wrestler *);

/* Return 1 when any of these holds: the wrestler is the legal man (WR_FLAG_LEGAL), its partner's flags
 * (partnerFlags) have any of the bits 0x600000000000, or one of func_800D8DF0 / func_800D96A0 returns nonzero.
 * Returns 0 otherwise. */
s32 func_800DA6DC(Wrestler *w) {
    if (w->flags & WR_FLAG_LEGAL) {
        goto ret1;
    }
    if (w->partnerFlags & ((u64)0x6000 << 32)) {
        goto ret1;
    }
    if (func_800D8DF0(w)) {
        goto ret1;
    }
    if (func_800D96A0(w)) {
        goto ret1;
    }
    return 0;
ret1:
    return 1;
}
