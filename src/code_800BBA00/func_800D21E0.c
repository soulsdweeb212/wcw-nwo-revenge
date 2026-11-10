/* @header
 * func_800D21E0
 * VRAM 0x800D21E0 | ROM 0xC5680 | size 0x1D4
 * asm: asm/nonmatchings/code_800BBA00/func_800D21E0.s
 */
#include "common.h"

/* Three-step turn/move action on self D_800FAF5C:
 * 0) choose the turn animation and reset stateTimer,
 * 1) advance the turn each frame (switching to the follow-up action id and
 *    setting step 7 when the opponent is in a given mode),
 * 2) run the 4-frame hold then hand control back. */
extern s32 D_800EB610[]; extern s16 D_800EB628[];
#ifdef TARGET_PC
/* PC: port_decls.h declares func_800D5438, so the PC copy of this line leaves it out. */
void selectTurnAnimationCDC04(void *,void *);
void func_800D427C(void *,s16,s32);
s32 func_800D35B0(s32,s32);
void translateEntityXZ(void *,void *);
s32 func_800D2BEC(void *,void *,void *,f32,u16,s32);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
void func_800C472C(void *,void *,s32);
#else
void selectTurnAnimationCDC04(void *,void *); void func_800D427C(void *,s16,s32); s16 func_800D5438(void *,s32); s32 func_800D35B0(s32,s32); void translateEntityXZ(void *,void *); s32 func_800D2BEC(void *,void *,void *,f32,u16,s32); void func_800D4AD0(void *); void beginEntityActionA8D8C(void *); void func_800C472C(void *,void *,s32);
#endif
static inline s16 step(Wrestler *self,Wrestler *other) {
    s8 slot;
    self->stateTimer++; slot=self->id;
    if(D_800EB628[slot]<self->stateTimer) {
        self->heading=D_800EB610[slot];
        if(other->grappleCtx&0x100000) self->step=7;
        return 1;
    }
    if(other->grappleCtx&0x200) translateEntityXZ(self,self->moveDelta);
    self->heading=func_800D35B0(self->heading,self->turnPerTick);
    return 0;
}
void func_800D21E0(void) {
    switch(D_800FAF5C->step) {
    case 0:
        selectTurnAnimationCDC04(D_800FAF5C,D_800F9B00);
        D_800FAF5C->stateTimer=0;
        func_800D427C(D_800FAF5C,func_800D5438(D_800F9B00,1),2);
        D_800FAF5C->step++;
    case 1:
        if(step(D_800FAF5C,D_800F9B00)) D_800FAF5C->step++;
        break;
    case 2:
        func_800D2BEC(D_800FAF5C,D_800F9B00,0,4.0f,0,0xFFFFE);
        if(D_800FAF5C->animFramesLeft<=0) { func_800D4AD0(D_800FAF5C); beginEntityActionA8D8C(D_800FAF5C); func_800C472C(D_800F9B00,D_800FAF5C,2); }
        break;
    }
}
