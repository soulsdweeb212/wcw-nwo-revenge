/* @header
 * func_800B0FD4
 * VRAM 0x800B0FD4 | ROM 0xA4474 | size 0xE4
 * asm: asm/nonmatchings/code_8009D7A0/func_800B0FD4.s
 */
#include "common.h"

s16 func_800B10B8(void);
extern u8 *D_800FABD0, *D_800F9B60, *D_800FAF58;
/* Three-state countdown action on D_800FABD0 (state +4): state 0 seeds the
 * countdown (+0xE) from func_800B10B8, state 1 decrements it and sets the count
 * word to 0x20 when it reaches zero, state 2 resets the action (copying the
 * entity's animation) unless the entity is still in state 0x5F. */
void func_800B0FD4(void) {
 u8 *p=D_800FABD0; u8 *g; u32 state;
 switch (*(s16*)(p+4)) {
 case 0:
 *(s16*)(D_800FABD0+0xE)=func_800B10B8();
 (*(s16*)(D_800FABD0+4))++;
 break;
 case 1:
 (*(s16*)(p+0xE))--;
 if (*(s16*)(p+0xE)<=0) { *(s16*)(p+6)=0x20; (*(s16*)(p+4))++; }
 break;
 case 2:
 if (*(s16*)(D_800FAF58+0xA)!=0x5F) {
 g=D_800F9B60;
 *(s16*)(p+2)=0; *(s16*)(p+4)=0;
 state=*(u16*)(g+0xA);
 *(u32*)(p+0x5C)&=~7;
 *(u16*)(p+0x2E)=state;
 }
 break;
 }
}
