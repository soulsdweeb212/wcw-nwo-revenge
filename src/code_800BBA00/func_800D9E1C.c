/* @header
 * func_800D9E1C
 * VRAM 0x800D9E1C | ROM 0xCD2BC | size 0xE8
 * asm: asm/nonmatchings/code_800BBA00/func_800D9E1C.s
 */
#include "common.h"

void func_800A6BE0(Wrestler *, s32);
/* Pairs two wrestlers: puts self into state 0x80 and other into 0x7F when self is the legal man (WR_FLAG_LEGAL),
 * else self 0x7F and other 0x80 (func_800A6BE0); raises flag 0x1000000000 on self and 0x1000000000 |
 * WR_FLAG_UPDATED on other, and when setStep2 is set puts both at step 2. */
void func_800D9E1C(Wrestler *self, Wrestler *other, s16 setStep2) {
    func_800A6BE0(self, (self->flags & WR_FLAG_LEGAL) ? 0x80 : 0x7F);
    self->flags |= 0x1000000000ULL;
    func_800A6BE0(other, (self->flags & WR_FLAG_LEGAL) ? 0x7F : 0x80);
    other->flags |= 0x1000000000ULL | WR_FLAG_UPDATED;
    if (setStep2) {
        self->step = 2;
        other->step = 2;
    }
}
