/* @header
 * func_800C7870
 * VRAM 0x800C7870 | ROM 0xBAD10 | size 0x74
 * asm: asm/nonmatchings/code_800BBA00/func_800C7870.s
 */
#include "common.h"

extern f64 D_800E68D0;

/* Returns 1 when other is rebounding off the ropes (frameStatus bit 0), both
 * wrestlers are inside the ropes (WR_FLAG_IN_RING) and arg2 (the caller passes D_800F9B0C) is below D_800E68D0. */
s32 func_800C7870(Wrestler *self, Wrestler *other, f32 arg2) {
    if ((other->frameStatus & 1) && ((self->flags & other->flags) & WR_FLAG_IN_RING) &&
        ((f64)arg2 < D_800E68D0)) {
        return 1;
    }
    return 0;
}
