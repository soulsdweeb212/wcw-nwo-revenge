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
/* Collision/interaction resolver: given acting entity `actor`, the other entity
 * `other`, an option `mask` and the precomputed direction result `d`, decide
 * whether `actor` reacts to `other`. Returns 1 and starts the matching action
 * (grapple, paired actions, generic hit reaction, or stagger) when a reaction
 * fires, else 0. */
s32 func_800E022C(u8 *actor,u8 *other,s32 mask,Nw2DirectionResult *d) {
 if(mask&0x20) {
 if((*(u64 *)(actor+0x20)&*(u64 *)(other+0x20)&0x40) && (*(u64 *)(other+0x20)&0x100000) && (*(u16 *)(other+0x28)&0x20) && (u32)(func_800D3550(func_800D3684(*(s32 *)(other+0x58),d->angle))-0x71)>=0x71F) {
 func_800E212C(actor); func_800A6C48(actor,0x19); return 1;
 }
 if(*(s16 *)(other+0xA)==0x2D && (*(u64 *)(actor+0x20)&*(u64 *)(other+0x20)&0x140) && (f64)d->y<D_800E76C8) {
 func_800E212C(actor); beginPairedEntityActions(actor,0x83,other,0x84); return 1;
 }
 if(tryBeginPairedActionOnContact(actor,other,d->y)) {func_800E212C(actor); return 1;}
 if((*(u64 *)(actor+0x20)&0x140) && !(*(u64 *)(actor+0x20)&9)) {func_800E212C(actor);func_800A6C48(actor,0x5F);return 1;}
 }
 return 0;
}
