/* @header
 * func_800B015C
 * VRAM 0x800B015C | ROM 0xA35FC | size 0x204
 * asm: asm/nonmatchings/code_8009D7A0/func_800B015C.s
 */
#include "common.h"

/* Per-frame entity decision state machine (switch on self->state at +4).
 * state 0: roll a new value and arm a countdown timer (roll%28+8).
 * state 1: count the timer down; if the opponent is ready, take or clear an
 *          action based on whether it matches the target state / distance,
 *          with a random 1-in-N check; otherwise reset the action. */
extern void *D_800FABD0,*D_800FAF58,*D_800F9B60;
extern f64 D_800E5230,D_800E5238;
s32 func_800D4148(void); s8 func_800D4198(s16); s8 func_800D8DF0(void *);
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define W(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
void func_800B015C(void) {
 s16 roll; u16 newState; void *tgt; void *e; void *other; void *self=D_800FABD0;
 switch(H(self,4)) {
 case 0:
 roll=func_800D4148(); H(D_800FABD0,4)++; H(D_800FABD0,14)=roll%28+8;
 break;
 case 1:
 if(H(D_800FAF58,10)==1) {
 if(--H(D_800FABD0,14)<0) {
 if(func_800D8DF0(D_800FAF58)) {
 e=D_800FABD0;
 if(H(e,0x2E)==H(D_800F9B60,10) && F(e,0x34)>D_800E5230) {
 if(func_800D4198(200)) {
 e=D_800FABD0; tgt=D_800F9B60;
 H(e,2)=7; H(e,4)=0; newState=H(tgt,10);
 } else goto clear;
 } else goto clear2;
 } else {
 clear: e=D_800FABD0;
 clear2: other=D_800F9B60;
 H(e,2)=0; H(e,4)=0; newState=H(other,10);
 }
 H(e,0x2E)=newState; W(e,0x5C)&=~7;
 } else if(!(F(D_800FABD0,0x34)<D_800E5238)) {
 if(H(D_800FABD0,0x2E)!=H(D_800F9B60,10)) {
 H(D_800FABD0,2)=0; H(D_800FABD0,4)=0; H(D_800FABD0,0x2E)=H(D_800F9B60,10); W(D_800FABD0,0x5C)&=~7;
 }
 } else goto reset;
 } else {
 void *resetTgt; s16 resetVal;
 reset: resetTgt=D_800F9B60;
 H(self,2)=0; H(self,4)=0; resetVal=H(resetTgt,10);
 W(self,0x5C)&=~7; H(self,0x2E)=resetVal;
 }
 break;
 }
}
