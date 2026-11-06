/* @header
 * func_800C41F0
 * VRAM 0x800C41F0 | ROM 0xB7690 | size 0x358
 * asm: asm/nonmatchings/code_800BBA00/func_800C41F0.s
 */
#include "common.h"

void playEntitySound(s8,s32);
void beginPairedEntityActions(void *,s32,void *,s32);

/* Decides whether self can counter other's move and, if so, records the move
 * category in self->counterKind and starts the counter (func_800C3A78 calls it with
 * self = the wrestler hit, other = the attacker). It rejects an other that is self's
 * tag partner (self->partnerId). When self has flag 0x8000000 (set by func_800C4610)
 * it only allows (self->state != 0x40) other states 30/7/28/31 (state 30 only
 * without other flags 9): sound 300 and self goes to state 0x5C (func_800A6C48).
 * Otherwise (other state 7, 8, 28, 30, 31, 34 or 35) it maps other->moveId to a
 * category bit in counterKind, plays sound 300 and starts a paired state pair with
 * beginPairedEntityActions (self leads): 0x5A/0x5B (mask 0x7E00), 0x79/0x7A (mask
 * 0x40, and self->grappleCtx = 0x2010000), 0x5D/0x5E (mask 1) or 0x58/0x59 (default). */
s32 func_800C41F0(Wrestler *self,Wrestler *other) {
    s32 actionMask;
    if (self->partnerId==other->id) return 0;
    if(self->flags&0x8000000) {
        if(self->state==0x40) return 0;
        switch(other->state) {
        case 30: if(other->flags&9) return 0;
        case 7: case 28: case 31:
            playEntitySound(self->id,300);func_800A6C48(self,0x5C);return 1;
        default:return 0;
        }
    }
    self->counterKind=0;
    switch((s16)(other->state-7)) {
    case 23: if(other->flags&9) return 0;
    case 0: case 1: case 21: case 24: case 27: case 28:
        if(!(other->flags&9) && (u32)((u16)other->moveId-0x95)<2) self->counterKind|=1;
        switch(other->moveId) {
        case 5:actionMask=0x80;break;case 6:actionMask=0x100;break;
        case 157:actionMask=2;break;case 159:actionMask=4;break;case 161:actionMask=8;break;case 163:actionMask=16;break;case 165:actionMask=32;break;case 182:actionMask=64;break;
        case 20:actionMask=0x200;break;case 21:actionMask=0x400;break;
        case 41:actionMask=0x2000;break;case 42:actionMask=0x4000;break;
        case 23:actionMask=0x800;break;case 24:actionMask=0x1000;break;
        default:actionMask=0;break;
        }
        self->counterKind|=actionMask;
        playEntitySound(self->id,300);
        if(self->counterKind&0x7E00) beginPairedEntityActions(self,0x5A,other,0x5B);
        else if(self->counterKind&0x40) {beginPairedEntityActions(self,0x79,other,0x7A);self->grappleCtx=0x2010000;}
        else if(self->counterKind&1) beginPairedEntityActions(self,0x5D,other,0x5E);
        else beginPairedEntityActions(self,0x58,other,0x59);
        return 1;
    }
    return 0;
}
