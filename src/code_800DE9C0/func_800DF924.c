/* @header
 * func_800DF924
 * VRAM 0x800DF924 | ROM 0xD2DC4 | size 0x78
 * asm: asm/nonmatchings/code_800DE9C0/func_800DF924.s
 */
#include "common.h"

s32 checkEntityAttackHit(void *, s32);
s32 isEntityActionEligible(void *, void *, s16);
void func_800E212C(void *);

/* Returns 1 when w has WR_FLAG_SPECIAL, its profile has bit 0x20000 (u64 at
 * profile + 0x38), or other is in state 0x75. */
s32 func_800DF924(Wrestler *w, Wrestler *other) {
    s32 r = 0;

    if (w->flags & WR_FLAG_SPECIAL) {
        r = 1;
    }
    if ((*(u64 *)(w->profile + 0x38) & 0x20000) || other->state == 0x75) {
        r = 1;
    }
    return r;
}
