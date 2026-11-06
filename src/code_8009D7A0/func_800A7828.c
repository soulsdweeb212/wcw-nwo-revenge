/* @header
 * func_800A7828
 * VRAM 0x800A7828 | ROM 0x9ACC8 | size 0x140
 * asm: asm/nonmatchings/code_8009D7A0/func_800A7828.s
 */
#include "common.h"

s8 func_800D4198(s16);

/* If self and other share a zone bit (WR_FLAG_IN_RING or WR_FLAG_ON_FLOOR), other lacks flag 0x1000000000 and has
 * flag 0x400000, and either bit 0 of self's stepFlags is set or func_800D4198(0x12C) succeeds: put other in state
 * 0x2C (step, stepFlags and pairSignals cleared, flag bits 0x10800000000 | WR_FLAG_RERUN replaced with 0x1000000000,
 * func_800DECAC(other, 0, 0, 0)), then set its step to 4 and raise WR_FLAG_RERUN. */
void func_800A7828(Wrestler *self, Wrestler *other) {
    u64 f0 = self->flags;
    u64 f1 = other->flags;
    if ((f0 & f1 & (WR_FLAG_IN_RING | WR_FLAG_ON_FLOOR)) && !(f1 & 0x1000000000) && (f1 & 0x400000)) {
        if ((self->stepFlags & 1) || func_800D4198(0x12C)) {
            other->state = 0x2C;
            other->step = 0;
            other->stepFlags = 0;
            other->pairSignals = 0;
            other->flags = (other->flags & ~0x10810000000ULL) | 0x1000000000ULL;
            func_800DECAC(other, 0, 0, 0);
            other->step = 4;
            other->flags |= WR_FLAG_RERUN;
        }
    }
}
