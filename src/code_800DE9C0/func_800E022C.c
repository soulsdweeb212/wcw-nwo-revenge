/* @header
 * func_800E022C
 * VRAM 0x800E022C | ROM 0xD36CC | size 0x1F4
 * asm: asm/nonmatchings/code_800DE9C0/func_800E022C.s
 */
#include "common.h"

extern f64 D_800E76C8;
void func_800E212C(void *);
void beginPairedEntityActions(void *,s32,void *,s32);
s8 tryBeginPairedActionOnContact(void *,void *,f32);
/* Collision/interaction resolver: given acting wrestler `actor`, the other
 * wrestler `other`, an option `mask` and the precomputed direction result `d`,
 * decide whether `actor` reacts to `other` (only when mask has 0x20). Both
 * WR_FLAG_IN_RING with other flag 0x100000, other running (moveMode 0x20) and
 * the heading delta func_800D3550(func_800D3684(other->heading, d->angle))
 * outside 0x71..0x78F starts action 0x19; other in state 0x2D, a shared zone bit
 * (WR_FLAG_IN_RING / WR_FLAG_ON_FLOOR) and d->y < D_800E76C8 starts the paired
 * actions 0x83/0x84; then tryBeginPairedActionOnContact(actor, other, d->y);
 * finally an actor in the ring or on the floor without flag bits 0x1 / 0x8
 * starts 0x5F. Returns 1 when a reaction fires, else 0. */
s32 func_800E022C(Wrestler *actor,Wrestler *other,s32 mask,Nw2DirectionResult *d) {
    if(mask&0x20) {
        if((actor->flags&other->flags&WR_FLAG_IN_RING) && (other->flags&0x100000) && (other->moveMode&0x20) && (u32)(func_800D3550(func_800D3684(other->heading,d->angle))-0x71)>=0x71F) {
            func_800E212C(actor); func_800A6C48(actor,0x19); return 1;
        }
        if(other->state==0x2D && (actor->flags&other->flags&(WR_FLAG_IN_RING|WR_FLAG_ON_FLOOR)) && (f64)d->y<D_800E76C8) {
            func_800E212C(actor); beginPairedEntityActions(actor,0x83,other,0x84); return 1;
        }
        if(tryBeginPairedActionOnContact(actor,other,d->y)) {func_800E212C(actor); return 1;}
        if((actor->flags&(WR_FLAG_IN_RING|WR_FLAG_ON_FLOOR)) && !(actor->flags&9)) {func_800E212C(actor);func_800A6C48(actor,0x5F);return 1;}
    }
    return 0;
}
