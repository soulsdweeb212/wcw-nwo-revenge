#include "common.h"

extern u8 *D_800FABD0, *D_800FAF58, *D_800F9B60;
extern u16 D_800E377C[], D_800E3788[];
extern s8 func_800D4198(s16);
extern s16 func_800D4148(void);
#define A(o,t) (*(t *)(D_800FABD0+(o)))
/* Random idle-pose timing handler. State 0 picks a base angle/frame `base` and a
 * spread `range` (from the entity's pose-variant table, or a fixed fallback),
 * then writes a randomised duration into the action's 0xE timer. State 1 counts
 * that timer down and sets the action's 8 flag high/low when it expires. State 2
 * resets the action when the entity leaves its 'waiting' pose (state 0x5D). */
void func_800B37F8(void) {
 u8 *action = D_800FABD0;
 switch(*(s16 *)(action+4)) {
 case 0: {
   s16 base, range;
   s32 r;
   base = 0xF;
   if (*(u64 *)(D_800F9B60+0x20) & 0x80000) {
     range = 7;
   } else {
     s8 variant = *(s8 *)(*(u8 **)(D_800FAF58+0x364) + 0x18) / 3;
     base = D_800E377C[variant];
     range = D_800E3788[variant];
     if (func_800D4198(0x64)) { base = 0xF; range = 5; }
   }
   r = func_800D4148() % (range * 2);
   A(4,s16)++;
   A(0xE,s16) = base + r - range;
   break; }
 case 1:
   if (--*(s16 *)(action+0xE) < 0) {
     if (func_800D4198(0x1F4)) A(8,u16) = 0x8000; else A(8,s16) = 0x4000;
     A(4,s16)++;
   }
   break;
 case 2:
   if (*(s16 *)(D_800FAF58+0xA) != 0x5D) {
     u8 *g = D_800F9B60;
     *(s16 *)(action+2)=0; *(s16 *)(action+4)=0;
     *(u16 *)(action+0x2E)=*(u16 *)(g+0xA);
     *(u32 *)(action+0x5C)&=~7;
   }
   break;
 }
}
#undef A
