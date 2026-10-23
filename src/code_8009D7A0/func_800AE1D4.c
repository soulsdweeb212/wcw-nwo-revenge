#include "common.h"

/* Action selector for self D_800FABD0:
 * phase 0 arms the flag word; phase 1, when the actor is in a given state and
 * close enough, picks a follow-up action based on self->f22 (a fixed action,
 * one of two random choices, or reset to idle). */
typedef struct {s16 f0,f2,f4;u16 f6;s16 f8,fA,fC,fE,f10,f12; u8 pad14[14]; s16 f22; u8 pad24[10]; u16 f2E; u32 f30; f32 f34; u8 pad38[36]; u32 f5C;} ActionE1;
extern ActionE1 *D_800FABD0,*D_800FAF58,*D_800F9B60;
extern f64 D_800E51C0;
s8 func_800D4198(s16);
void func_800AE1D4(void) {
 switch(D_800FABD0->f4) {
 case 0: D_800FABD0->f6=0x8000; D_800FABD0->f4++; break;
 case 1:
 switch(D_800FAF58->fA) {
 case 1: case 0x2B:
 if(D_800FABD0->f34 < D_800E51C0 && func_800D4198(D_800FABD0->f12)) {
 switch(D_800FABD0->f22) {
 case 6: {
 ActionE1 *self=D_800FABD0,*other=D_800F9B60;
 self->f2=0x1F; self->f4=0; self->f2E=other->fA; self->f5C&=~7; return;
 }
 case 10:
 if(func_800D4198(750)) {
 ActionE1 *self=D_800FABD0,*other=D_800F9B60;
 self->f2=11;self->f4=0;self->f2E=other->fA;self->f5C&=~7;
 } else {
 ActionE1 *self=D_800FABD0,*other=D_800F9B60;
 self->f2=29;self->f4=0;self->f2E=other->fA;self->f5C&=~7;
 }
 return;
 }
 }
 default: {
 ActionE1 *self=D_800FABD0,*other=D_800F9B60;
 self->f2=0;self->f4=0;self->f2E=other->fA;self->f5C&=~7;
 } break;
 case 0x44: break;
 }
 break;
 }
}
