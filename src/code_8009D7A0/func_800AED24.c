/* @header
 * func_800AED24
 * VRAM 0x800AED24 | ROM 0xA21C4 | size 0x1A4
 * asm: asm/nonmatchings/code_8009D7A0/func_800AED24.s
 */
#include "common.h"

/* Two-phase action gate for self D_800FABD0:
 * phase 0 watches the actor's state and either advances (when its f22 slot is
 * 5) or resets to idle; phase 1 either resets when the actor's flag is set, or
 * rolls a random choice between action 43 and action 9. */
typedef struct {s16 f0,f2,f4,f6,f8,fA;u8 padC[0x14];u64 flags;u8 pad28[6];u16 f2E;u8 pad30[0x2C];u32 f5C;} AEDObj;
extern AEDObj *D_800FABD0,*D_800FAF58,*D_800F9B60;
s8 func_800D4198(s16);
void func_800AED24(void) {
 s16 phase=D_800FABD0->f4;
 switch(phase) {
 case 0:
 switch(D_800FAF58->fA) {
 case 1:
 if(D_800F9B60->fA!=12) {
 if(*(s16 *)((u8 *)D_800FABD0+0x22)==5) D_800FABD0->f4=phase+1;
 else {D_800FABD0->f2=0;D_800FABD0->f4=0;D_800FABD0->f2E=D_800F9B60->fA;D_800FABD0->f5C&=~7;}
 }
 break;
 case 11:case 43:break;
 default:
 D_800FABD0->f2=0;D_800FABD0->f4=0;D_800FABD0->f2E=D_800F9B60->fA;D_800FABD0->f5C&=~7;
 break;
 }
 break;
 case 1:
 if(D_800FAF58->flags&0x100) {
 AEDObj *other=D_800F9B60;u16 oldState;
 D_800FABD0->f2=0;D_800FABD0->f4=0;oldState=other->fA;D_800FABD0->f5C&=~7;D_800FABD0->f2E=oldState;
 }else{
 if(func_800D4198(300)) {
 AEDObj *self=D_800FABD0,*other=D_800F9B60;
 self->f2=43;self->f4=0;self->f2E=other->fA;self->f5C&=~7;
 }else {
 AEDObj *self=D_800FABD0,*other=D_800F9B60;
 self->f2=9;self->f4=0;self->f2E=other->fA;self->f5C&=~7;
 }
 }
 break;
 }
}
