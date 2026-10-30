/* @header
 * func_800AB0E8
 * VRAM 0x800AB0E8 | ROM 0x9E588 | size 0xC8
 * asm: asm/nonmatchings/code_8009D7A0/func_800AB0E8.s
 */
#include "common.h"

extern void *D_800FAF58;
extern s8 D_8007E8C0[], D_800FACE8;
s8 func_800D4198(s32);
void func_800AD958(s32);
s32 func_800AB0E8(void) {
 s32 chance;
 u64 flags=*(u64 *)((u8 *)D_800FAF58+0x20);
 if ((flags&0x100) && !(flags&0x8000)) {
  chance=20;
  if (D_8007E8C0[0x66C]) {
   s8 lvl = D_800FACE8;
   if (lvl < 6) {
    s32 d = 6;
    d -= lvl;
    chance = d * 2;
    chance += d;
    chance *= 8;
    chance += d;
    chance <<= 19;
    chance >>= 16;
   } else return 0;
  }
  if(func_800D4198(chance)) {
   func_800AD958(21);
   return 1;
  }
 }
 return 0;
}
