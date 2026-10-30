/* @header
 * updateActionRequestState  (originally func_800AF3DC)
 * VRAM 0x800AF3DC | ROM 0xA287C | size 0x150
 * asm: asm/nonmatchings/code_8009D7A0/func_800AF3DC.s
 */
#include "common.h"

extern u8 *D_800FABD0,*D_800F9B60,*D_800FAF58;
extern u16 D_800FAC14[][32],D_800FAC1C[][32];
s8 func_800D4198(s16);
/* Two-state action request handler on D_800FABD0 (state at +4). State 0: when
 * the action is available and the entity's counter is still below its threshold
 * (from the per-entity D_800FAC14/1C table), reset the action to state 10 and
 * copy the entity's animation; otherwise bump the counter and advance to
 * state 1. State 1: abort (reset to state 0) when the entity is no longer in
 * the 0x55 state. */
void updateActionRequestState(void) {
 u8 *p=D_800FABD0,*g; u16 v;
 switch(*(s16*)(p+4)) {
 case 0:
 if(func_800D4198(*(s16*)(p+0x12))) {
 if(*(u64*)(D_800F9B60+0x20)&0x200000) v=D_800FAC1C[*(s8*)D_800FAF58][0];
 else v=D_800FAC14[*(s8*)D_800FAF58][0];
 p=D_800FABD0;
 if((s16)(v+25)<*(s16*)(p+0x28)) {
 g=D_800F9B60;
 *(s16*)(p+2)=10;*(s16*)(p+4)=0;
 *(u16*)(p+0x2E)=*(u16*)(g+10);*(u32*)(p+0x5C)&=~7;
 break;
 }
 }
 *(s16*)(D_800FABD0+6)=0x4000;(*(s16*)(D_800FABD0+4))++;
 break;
 case 1:
 if(*(s16*)(D_800FAF58+10)!=0x55) {
 g=D_800F9B60;*(s16*)(p+2)=0;*(s16*)(p+4)=0;
 *(u16*)(p+0x2E)=*(u16*)(g+10);*(u32*)(p+0x5C)&=~7;
 }
 break;
 }
}
