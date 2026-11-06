/* @header
 * func_800E074C
 * VRAM 0x800E074C | ROM 0xD3BEC | size 0x34
 * asm: asm/nonmatchings/code_800DE9C0/func_800E074C.s
 */
#include "common.h"

s32 checkEntityAttackHit(Wrestler *, s32);
s32 isEntityActionEligible(void *, void *, s16);
void func_800E212C(void *);

/* When arg2 has bit 8, returns 1 if checkEntityAttackHit(w, arg1 & 0xFFFF)
 * (attack hit test between w and its partner record) succeeds; else 0. */
s32 func_800E074C(Wrestler *w, s32 arg1, s32 arg2) {
    if (arg2 & 8) {
        if ((checkEntityAttackHit(w, arg1 & 0xFFFF) << 24) != 0) {
            return 1;
        }
    }
    return 0;
}
