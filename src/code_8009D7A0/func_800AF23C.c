/* @header
 * func_800AF23C
 * VRAM 0x800AF23C | ROM 0xA26DC | size 0x1A0
 * asm: asm/nonmatchings/code_8009D7A0/func_800AF23C.s
 */
#include "common.h"

typedef struct {s16 f0,f2,f4;u16 f6;s16 f8,fA,fC,fE,f10,f12; u8 pad14[14]; s16 f22; u8 pad24[10]; u16 f2E; u32 f30; f32 f34; u8 pad38[36]; u32 f5C;} ActionF23;
extern ActionF23 *D_800FABD0,*D_800FAF58,*D_800F9B60;
extern f64 D_800E5200;
s8 func_800D4198(s16);
s16 func_800D4148(void);

/* Action-record substate handler (D_800FABD0 is the action record, D_800FAF58 the
 * paired entity, D_800F9B60 the current action source). Substate 0 arms a 0x20 tick
 * delay; substate 1, while the paired entity is in state 1 or 0x2B and this action's
 * f34 is below the D_800E5200 threshold and the entity check and f22==10 hold, picks
 * a follow-up action (11/28/29) from the score returned by func_800D4148
 * (<500 / <750 / else), or resets to action 0 when the guard fails. */
void func_800AF23C(void) {
 switch(D_800FABD0->f4) {
 case 0: D_800FABD0->f6=0x20; D_800FABD0->f4++; break;
 case 1:
 switch(D_800FAF58->fA) {
 case 1: case 0x2B:
 if(D_800FABD0->f34 < D_800E5200 && func_800D4198(D_800FABD0->f12) && D_800FABD0->f22==10) {
 s16 score=func_800D4148();
 if(score<500) {
 ActionF23 *record=D_800FABD0,*other=D_800F9B60;
 record->f2=11; record->f4=0; record->f2E=other->fA; record->f5C&=~7;
 } else if(score<750) {
 ActionF23 *record=D_800FABD0,*other=D_800F9B60;
 record->f2=28; record->f4=0; record->f2E=other->fA; record->f5C&=~7;
 } else {
 ActionF23 *record=D_800FABD0,*other=D_800F9B60;
 record->f2=29; record->f4=0; record->f2E=other->fA; record->f5C&=~7;
 }
 return;
 }
 default: {
 ActionF23 *record=D_800FABD0,*other=D_800F9B60;
 record->f2=0; record->f4=0; record->f2E=other->fA; record->f5C&=~7;
 } break;
 case 0x5F: break;
 }
 break;
 }
}
