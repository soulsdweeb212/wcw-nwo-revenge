/* @header
 * func_800032A4
 * VRAM 0x800032A4 | ROM 0x3EA4 | size 0x58
 * asm: asm/nonmatchings/main/func_800032A4.s
 */
#include "common.h"

s32 MusBankStartEffect2(s32,s16,s16,s16,s16,s16); extern s32 D_800482D4;
/* Forward five parameters to MusBankStartEffect2 with the current context D_800482D4;
 * the last argument is truncated to s16. */
void func_800032A4(s16 a,s16 b,s16 c,s16 d,s32 e) { s32 value=*(volatile s32 *)&e; value=(s16)value; MusBankStartEffect2(D_800482D4,a,b,c,d,value); }
