/* @header
 * tryBeginPairedActionOnContact  (originally func_800E0420)
 * VRAM 0x800E0420 | ROM 0xD38C0 | size 0x170
 * asm: asm/nonmatchings/code_800DE9C0/tryBeginPairedActionOnContact.s
 */
#include "common.h"

extern u8 D_8007EF30[];
extern f64 D_800E76D0;
f32 func_800D3EEC(void *,void *,s32);
void beginPairedEntityActions(void *,s32,void *,s32);
/* When the global 0x100 flag (D_8007EF30+0x170) is set or self is WR_FLAG_IN_RING, and self has neither flag
 * bit 0x1 nor 0x2, the two share a zone bit (WR_FLAG_IN_RING / WR_FLAG_ON_FLOOR), other has flag 0x400000 and
 * not 0x1000000000: if dist is below func_800D3EEC(other's position, self's pelvis jointA[1], other->heading)
 * plus D_800E76D0, clear self's flag bit 0x200000000000000 and start the paired actions 0x36 (self) / 0x37
 * (other). Returns 1 when started, 0 otherwise. */
s32 tryBeginPairedActionOnContact(Wrestler *self,Wrestler *other,f32 dist) {
    if ((*(u16 *)(D_8007EF30+0x170)&0x100) || (self->flags&WR_FLAG_IN_RING)) {
        if (!(self->flags&3) && (self->flags&other->flags&(WR_FLAG_IN_RING|WR_FLAG_ON_FLOOR)) && (other->flags&0x400000) && !(other->flags&0x1000000000ULL)) {
            if (dist < func_800D3EEC(&other->x,&self->jointA[1],other->heading)+D_800E76D0) {
                self->flags &= ~0x200000000000000ULL;
                beginPairedEntityActions(self,0x36,other,0x37);
                return 1;
            }
            return 0;
        }
    }
    return 0;
}
