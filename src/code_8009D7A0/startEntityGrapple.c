/* @header
 * startEntityGrapple  (originally func_800B5340)
 * VRAM 0x800B5340 | ROM 0xA87E0 | size 0x3F0
 * asm: asm/nonmatchings/code_8009D7A0/startEntityGrapple.s
 */
#include "common.h"

/* Resolve a grapple/lockup between 'self' and its nearest other entity.
 * Finds the partner (func_800D26A0), computes the pair's facing flags
 * (getEntityPairFacingFlags) and sets the 0x08000000 facing bit, then based on
 * the two entities' status words and action ids either starts a mutual grapple
 * (both action 5, slot indices swapped) or a one-sided lockup, or runs the
 * grapple check func_800B678C. Returns 1 if a grapple/lockup started. */
s32 func_800D26A0(void*,s32,s32);s32 getEntityPairFacingFlags(void*,void*);
void func_800A6BE0(void*,s32); void func_800A6CDC(void*,s32);void func_800E212C(void*);s16 func_800B678C(void*,void*,u16);
s32 startEntityGrapple(Wrestler *self,s16 arg1,u16 arg2) {
    s32 id; Wrestler *other; u32 facing; s16 result;
    id=func_800D26A0(self,0,-1);
    if((s8)id != -1) {
        self->flags&=~0x08000000ULL;
        other=&D_800F9D10[(s8)id];
        other->flags&=~0x08000000ULL;
        facing=getEntityPairFacingFlags(self,other);
        if(facing&2) self->flags|=0x08000000ULL;
        if(facing&8) other->flags|=0x08000000ULL;
        if(other->flags&0x100000ULL) {
            if(self->flags&WR_FLAG_ON_APRON) {
                func_800A6CDC(self,0x28);func_800A6CDC(other,0x28);
                self->hitInfo=0x80800000;other->hitInfo=0x80800000;
                self->heldById=other->id;other->heldById=self->id;return 1;
            }
            func_800E212C(self);func_800E212C(other);func_800A6BE0(self,5);func_800A6BE0(other,5);return 1;
        }
        if((u32)((u16)other->state-0x40)<2 && !(other->flags&0x08000000ULL)) {
            func_800E212C(self);func_800A6BE0(self,5);func_800A6BE0(other,0x41);other->step=2;return 1;
        }
        if((self->moveMode&0x20) && other->state==0x14) {
            func_800A6BE0(self,5);func_800A6CDC(other,0x28);other->hitInfo=0x200000;return 1;
        }
        result=func_800B678C(self,other,(u16)arg2);
        if(result) {if(result==1) {func_800E212C(self);func_800A6C48(self,0x8A);return 1;}return 0;}
        if((self->moveMode&0x80) && (s8)id==self->heldById && D_800F9D10[(s8)id].state==0x19) return 0;
        if(self->flags&WR_FLAG_ON_APRON) {
            if(!(other->flags&0x0040001000000000ULL)) {
                func_800A6CDC(self,0x28);self->hitInfo=0x80400000;func_800A6CDC(other,0x28);other->hitInfo=0x80800000;other->heldById=self->id;return 1;
            }
            if((s16)arg1==0) {self->moveDelta[0]=0;self->moveDelta[2]=0;self->flags|=0x1000000ULL;return 0;}
        }
        func_800A6C48(self,3);self->step=3;return 1;
    }
    self->steppedOverId=-1;return 0;
}
