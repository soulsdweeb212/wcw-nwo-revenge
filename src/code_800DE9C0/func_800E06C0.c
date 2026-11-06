/* @header
 * func_800E06C0
 * VRAM 0x800E06C0 | ROM 0xD3B60 | size 0x8C
 * asm: asm/nonmatchings/code_800DE9C0/func_800E06C0.s
 */
#include "common.h"

s32 checkEntityAttackHit(void *, s32);
s32 isEntityActionEligible(Wrestler *, Wrestler *, s16);
void func_800E212C(Wrestler *);

/* When the low byte of arg2 is nonzero: func_800E212C(self) (detaches self from
 * its model part if bound), then, if isEntityActionEligible(self, other, 0x56),
 * starts state 0x44 at step 3 with grappleCtx = 0x200000, else state 0x17.
 * Returns 1 when handled, else 0. */
s32 func_800E06C0(Wrestler *self, Wrestler *other, s32 arg2) {
    if (arg2 << 24) {
        func_800E212C(self);
        if (isEntityActionEligible(self, other, 0x56) << 24) {
            func_800A6C48(self, 0x44);
            self->step = 3;
            self->grappleCtx = 0x200000;
            return 1;
        }
        func_800A6C48(self, 0x17);
        return 1;
    }
    return 0;
}
