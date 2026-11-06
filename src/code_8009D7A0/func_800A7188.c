/* @header
 * func_800A7188
 * VRAM 0x800A7188 | ROM 0x9A628 | size 0xB8
 * asm: asm/nonmatchings/code_8009D7A0/func_800A7188.s
 */
#include "common.h"

s32 func_800D36E8(f32, f32);
void func_800D4AD0(void *);
/* When animFramesLeft is 1 (the animation ends this tick): calls func_800D4AD0 (pose = anim.endPose, heading +=
 * anim.headingDelta, then func_800D4B10), puts the wrestler in state 0x2B (step, stepFlags and pairSignals cleared, flag bits
 * 0x10800000000 | WR_FLAG_RERUN replaced with 0x1000000000, func_800DECAC(w, 0, 0, 0)) and raises WR_FLAG_RERUN.
 * Returns 1 then, else 0. */
s32 func_800A7188(Wrestler *w) {
    if (w->animFramesLeft == 1) {
        func_800D4AD0(w);
        w->state = 0x2B;
        w->step = 0;
        w->stepFlags = 0;
        w->pairSignals = 0;
        w->flags = (w->flags & ~0x10810000000ULL) | 0x1000000000ULL;
        func_800DECAC(w, 0, 0, 0);
        w->flags |= WR_FLAG_RERUN;
        return 1;
    }
    return 0;
}
