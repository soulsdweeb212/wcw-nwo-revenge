/* @header
 * func_800B19AC
 * VRAM 0x800B19AC | ROM 0xA4E4C | size 0x20C
 * asm: asm/nonmatchings/code_8009D7A0/func_800B19AC.s
 */
#include "common.h"

extern u8 *D_800FABD0, *D_800FAF58, *D_800F9B60;
extern f64 D_800E5270;
extern u8 D_800FAC08[];
extern s8 func_800D4198(s16);
#define A(o,t) (*(t *)(D_800FABD0+(o)))
/* Counter-action handler. State 0 sets the action variant (0x6 = 4) and advances.
 * State 1 watches the entity's stance (0xA): when the opponent is attacking
 * (stance 3, sub-state 0xC == 2) it rolls a random gate and a height-vs-table
 * check to either flinch (set 0x8 = 0xF00, or 0x6 = 0x10) and advance, or start
 * the counter (0x6 = 0x4000); any other stance resets. State 2 sets the flinch
 * flag for stance 3 and falls into the shared `reset` for every other stance.
 * `reset` stops the action and syncs the action's 0x2E field with D_800F9B60. */
void func_800B19AC(void) {
 switch(A(4,s16)) {
 case 0: A(6,s16)=4; A(4,s16)++; break;
 case 1:
   switch(*(s16 *)(D_800FAF58+0xA)) {
   case 3:
     if (*(s16 *)(D_800FAF58+0xC)==2) {
       if (A(0x22,s16)!=0xE && func_800D4198(A(0x12,s16)) && D_800E5270 < (f64)A(0x34,f32)) {
         if (func_800D4198(0x1F4)) A(8,s16)=0xF00; else A(6,s16)=0x10;
         A(4,s16)++;
       } else if (A(0x3C,f32) < *(f32 *)(D_800FAC08 + *(s8 *)(D_800FAF58+0)*64)) {
         A(6,s16)=0x4000; A(4,s16)++;
       }
     }
     break;
   case 4: A(4,s16)++; break;
   default: goto reset;
   } break;
 case 2:
   switch(*(s16 *)(D_800FAF58+0xA)) {
   case 3: A(8,s16)=0xF00; break;
   case 4: case 6: case 7: break;
   default: { u8 *other;
   reset: other=D_800F9B60;
   A(2,s16)=0; A(4,s16)=0; A(0x2E,u16)=*(u16 *)(other+0xA); A(0x5C,u32)&=~7;
   } break;
   }
   break;
 }
}
#undef A
