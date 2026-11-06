/* @header
 * func_800E0780
 * VRAM 0x800E0780 | ROM 0xD3C20 | size 0x5C
 * asm: asm/nonmatchings/code_800DE9C0/func_800E0780.s
 */
#include "common.h"

s32 checkEntityAttackHit(void *, s32);
s32 isEntityActionEligible(void *, void *, s16);
void func_800E212C(void *);

/* When arg1 bit 0x2000 is set and the wrestler has WR_FLAG_SPECIAL, clear WR_FLAG_SPECIAL and reset spirit to 0x32
 * (50, neutral). */
void func_800E0780(Wrestler *w, s32 arg1) {
    u64 f;

    if (arg1 & 0x2000) {
        f = w->flags;
        if (f & WR_FLAG_SPECIAL) {
            w->flags = f & ~WR_FLAG_SPECIAL;
            w->spirit = 0x32;
        }
    }
}
