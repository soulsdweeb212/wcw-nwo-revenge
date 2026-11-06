/* @header
 * func_800CBC4C
 * VRAM 0x800CBC4C | ROM 0xBF0EC | size 0x110
 * asm: asm/nonmatchings/code_800BBA00/func_800CBC4C.s
 */
#include "common.h"

void func_800A7C40(void *, s8, s16);
void func_800A7F6C(void *, s32);
/* Picks self's move from bits 1/2 of self->unk036 (0xC4, 0xC6, 0xC8 or 0xCA) and loads it with
 * func_800A7C40 from other's move table when unk036 bit 0x10 is set and other lacks flags 9, else from
 * self's own; then func_800A7F6C(self, 0). When unk036 bit 8 is set or other->pairSignals has bit 0x10,
 * other gets move self->moveId + 1 from the same table and 1 is returned; otherwise 0. */
s32 func_800CBC4C(Wrestler *self, Wrestler *other) {
    s16 anim;
    s8 id;
    u8 flags = self->unk036;
    if (flags & 1) anim = (-((flags & 2) != 0) & 0xC6) | 0xC4;
    else anim = (-((flags & 2) != 0) & 0xCA) | 0xC8;
    if ((self->unk036 & 0x10) && !(other->flags & 9)) id = other->id;
    else id = self->id;
    func_800A7C40(self,id,anim);
    func_800A7F6C(self,0);
    if ((self->unk036 & 8) || (other->pairSignals & 0x10)) {
        func_800A7C40(other,id,(s16)((u16)self->moveId+1));
        return 1;
    }
    return 0;
}
