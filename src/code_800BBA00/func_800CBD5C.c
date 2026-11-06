/* @header
 * func_800CBD5C
 * VRAM 0x800CBD5C | ROM 0xBF1FC | size 0xCC
 * asm: asm/nonmatchings/code_800BBA00/func_800CBD5C.s
 */
#include "common.h"

s8 func_800B71F8(void *, s32, s32);

/* Paired-wrestler action gate: applies only when self is SPECIAL (WR_FLAG_SPECIAL) or other is not,
 * and self's flags lack mask 9. Then, if arg2 has any of the bits 0xC030 and other->unk036 does not
 * already have bit 4, set that bit on other and, when func_800B71F8(self,0,0) succeeds, also bit 8.
 * The caller func_800CB878 passes the wrestler being updated, its opponent and D_800FAF8A. */
void func_800CBD5C(Wrestler *self, Wrestler *other, s32 arg2) {
    u8 bits;
    if ((self->flags & WR_FLAG_SPECIAL) || !(other->flags & WR_FLAG_SPECIAL)) {
        if (!(self->flags & 9)) {
            bits = other->unk036;
            if (!(bits & 4) && (arg2 & 0xC030)) {
                other->unk036 = bits|4;
                if (func_800B71F8(self,0,0)) other->unk036 |= 8;
            }
        }
    }
}
