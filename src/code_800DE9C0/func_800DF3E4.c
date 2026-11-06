/* @header
 * func_800DF3E4
 * VRAM 0x800DF3E4 | ROM 0xD2884 | size 0x1E0
 * asm: asm/nonmatchings/code_800DE9C0/func_800DF3E4.s
 */
#include "common.h"

/* Grab/throw attempt: when asked (flags & 0x10), self WR_FLAG_ON_APRON starts
 * action 9; otherwise, if other has flag 0x400000, not 0x1000000000, shares a
 * zone bit (WR_FLAG_IN_RING / WR_FLAG_ON_FLOOR) with self and distance is under
 * func_800D3EEC(&other->x, &self->jointA[1], other->heading) + D_800E76A0, the
 * paired actions 0x32/0x33 start; else if other is rebounding off the ropes
 * (frameStatus bit 0), both are WR_FLAG_IN_RING and distance < D_800E76A8, the
 * paired actions 0x34/0x35 start; otherwise action 0x40. Returns 1 if an action
 * was chosen. */
extern f64 D_800E76A0, D_800E76A8;
f32 func_800D3EEC(void *,void *,s32);
void func_800E212C(void *);
void beginPairedEntityActions(void *,s32,void *,s32);
s32 func_800DF3E4(Wrestler *self,Wrestler *other,s32 flags,f32 distance) {
    if(flags & 0x10) {
        if(self->flags&WR_FLAG_ON_APRON) { func_800A6C48(self,9); return 1; }
        if((other->flags&0x400000ULL) && (f64)distance < (f64)func_800D3EEC(&other->x,&self->jointA[1],other->heading)+D_800E76A0 && !(other->flags&0x1000000000ULL) && (self->flags&other->flags&(WR_FLAG_IN_RING|WR_FLAG_ON_FLOOR))) {
            func_800E212C(self); beginPairedEntityActions(self,0x32,other,0x33); return 1;
        }
        if((other->frameStatus&1) && (self->flags&other->flags&WR_FLAG_IN_RING) && (f64)distance < D_800E76A8) {
            func_800E212C(self); beginPairedEntityActions(self,0x34,other,0x35); return 1;
        }
        func_800E212C(self); func_800A6C48(self,0x40); return 1;
    }
    return 0;
}
