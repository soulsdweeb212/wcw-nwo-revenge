#include "common.h"

extern u8 *D_800FABD0,*D_800FAF58,*D_800F9B60;
extern u8 D_8007EF30[],D_8007E8C0[];
extern s8 D_800FACE8;
/* Two-state action counter handler on D_800FABD0 (state at +4). State 0 sets
 * the action's count word (0xC000 when the entity is short on its 0x80000
 * condition, else 0x8000) and advances. State 1, when the entity is in state
 * 0x3A/0x3C and all the global gates allow it, sets +8 to 0x10; otherwise the
 * action is reset (state 0, entity animation copied). */
void updateActionCounterState(void){
 switch(*(s16 *)(D_800FABD0+4)) {
 case 0:
 if(*(s16 *)(D_800FABD0+0x26)<10 && (*(u64 *)(D_800FAF58+0x20)&0x80000)) *(u16 *)(D_800FABD0+6)=0xc000;
 else *(u16 *)(D_800FABD0+6)=0x8000;
 (*(s16 *)(D_800FABD0+4))++;break;
 case 1:
 switch(*(s16 *)(D_800FAF58+0xa)){
 case 0x3a: case 0x3c:
 if((*(u64 *)(D_800FAF58+0x20)&0x100) && !(*(u16 *)(D_8007EF30+0x170)&0x100) && *(s8 *)(D_8007E8C0+0x66c) && D_800FACE8<3) *(s16 *)(D_800FABD0+8)=0x10;
 break;
 default:{
 u8 *g=D_800F9B60;
 *(s16 *)(D_800FABD0+2)=0;*(s16 *)(D_800FABD0+4)=0;
 *(u16 *)(D_800FABD0+0x2e)=*(u16 *)(g+0xa);
 *(u32 *)(D_800FABD0+0x5c)&=~7;
 }break;
 }break;
 }
}
