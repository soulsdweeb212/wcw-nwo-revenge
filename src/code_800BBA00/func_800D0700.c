/* @header
 * func_800D0700
 * VRAM 0x800D0700 | ROM 0xC3BA0 | size 0x104
 * asm: asm/nonmatchings/code_800BBA00/func_800D0700.s
 */
#include "common.h"

/* Called with (D_800FAF5C, D_800F9B00, D_800FAF8A). Unless the opponent has WR_FLAG_SPECIAL and self does not:
 * when self has none of flag bits 9 and 0x4000000 and arg2 has a bit of 0xC030, set self flag 0x4000000, plus
 * 0x2000000 when func_800B71F8(self, opponent, 1) returns nonzero. */
s8 func_800B71F8(Wrestler *, Wrestler *, s32);
void func_800D0700(Wrestler *self, Wrestler *opponent, s32 arg2) {
    if ((self->flags & WR_FLAG_SPECIAL) || !(opponent->flags & WR_FLAG_SPECIAL)) {
        if (!(self->flags & 9) && !(self->flags & 0x4000000) && (arg2 & 0xC030)) {
            if (func_800B71F8(self,opponent,1)) self->flags |= 0x2000000;
            self->flags |= 0x4000000;
        }
    }
}
