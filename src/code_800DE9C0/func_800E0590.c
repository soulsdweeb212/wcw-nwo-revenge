/* @header
 * func_800E0590
 * VRAM 0x800E0590 | ROM 0xD3A30 | size 0x130
 * asm: asm/nonmatchings/code_800DE9C0/func_800E0590.s
 */
#include "common.h"

extern f64 D_800E76D8;
f32 func_800D3EEC(void *,void *,s32);
void func_800E212C(void *);
void beginPairedEntityActions(void *,s32,void *,s32);
/* When mask has bit 2, other has flag 0x400000 and not 0x1000000000, both are
 * WR_FLAG_IN_RING or both WR_FLAG_ON_FLOOR, and d->y is below
 * func_800D3EEC(&other->x, &self->jointA[1], other->heading) + D_800E76D8,
 * starts the paired actions 0x30 (self) / 0x31 (other) and returns 1; else 0. */
s32 func_800E0590(Wrestler *self,Wrestler *other,s32 mask,Nw2DirectionResult *d) {
    if(mask & 2) {
        if((other->flags&0x400000) && !(other->flags&0x1000000000ULL)) {
            if((self->flags&other->flags&WR_FLAG_IN_RING) || (self->flags&other->flags&WR_FLAG_ON_FLOOR)) {
                if(d->y < func_800D3EEC(&other->x,&self->jointA[1],other->heading)+D_800E76D8) {
                    func_800E212C(self); beginPairedEntityActions(self,0x30,other,0x31); return 1;
                }
            }
        }
    }
    return 0;
}
