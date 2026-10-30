/* @header
 * func_800E074C
 * VRAM 0x800E074C | ROM 0xD3BEC | size 0x34
 * asm: asm/nonmatchings/code_800DE9C0/func_800E074C.s
 */
#include "common.h"

s32 checkEntityAttackHit(void *, s32);
s32 isEntityActionEligible(void *, void *, s16);
void func_800A6C48(void *, s32);
void func_800E212C(void *);

/* When flag 8 is set, report whether the entity's attack hit arg1. */
s32 func_800E074C(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 & 8) {
        if ((checkEntityAttackHit((void *)arg0, arg1 & 0xFFFF) << 24) != 0) {
            return 1;
        }
    }
    return 0;
}
