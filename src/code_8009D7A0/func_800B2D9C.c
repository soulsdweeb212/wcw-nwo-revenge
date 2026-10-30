/* @header
 * func_800B2D9C
 * VRAM 0x800B2D9C | ROM 0xA623C | size 0x1A4
 * asm: asm/nonmatchings/code_8009D7A0/func_800B2D9C.s
 */
#include "common.h"

/* Multi-phase action gate on self D_800FABD0 driven by the actor's state
 * (D_800FAF58+0xA): each phase arms a flag/marker, advances or resets to idle
 * (copying the actor's state into self+0x2E and clearing the action bits). */
extern u8 *D_800FABD0, *D_800FAF58, *D_800F9B60;
#define A(o,t) (*(t *)(D_800FABD0+(o)))
void func_800B2D9C(void) {
 switch(A(4,s16)) {
 case 0: A(6,s16)=4; A(4,s16)++; break;
 case 1:
 switch(*(s16 *)(D_800FAF58+0xA)) {
 case 3: A(6,u16)=0x8000; break;
 case 0x63: A(4,s16)++; break;
 case 4: A(4,s16)=3; break;
 default: goto reset;
 } break;
 case 2:
 if (*(s16 *)(D_800FAF58+0xA)!=0x63) {
   u8 *other=D_800F9B60;
   A(2,s16)=0; A(4,s16)=0; A(0x2E,u16)=*(u16*)(other+0xA); A(0x5C,u32)&=~7;
 }
 break;
 case 3:
 switch ((s16)*(u16 *)(D_800FAF58+0xA)) {
 case 3: A(6,s16)=0x10; A(8,s16)=0x10; break;
 case 4:
 case 23: break;
 case 6:
 case 43: A(0xC,s8)=0x50; break;
 default: goto reset;
 } break;
 }
 return;
reset: { u8 *other=D_800F9B60;
 A(2,s16)=0; A(4,s16)=0; A(0x2E,u16)=*(u16*)(other+0xA); A(0x5C,u32)&=~7; }
}
#undef A
