/* @header
 * func_800032A4
 * VRAM 0x800032A4 | ROM 0x3EA4 | size 0x58
 * asm: asm/nonmatchings/main/func_800032A4.s
 */
#include "common.h"

s32 MusBankStartEffect2(s32,s16,s16,s16,s16,s16); extern s32 D_800482D4;
/* Forward five parameters to MusBankStartEffect2 with the current context D_800482D4;
 * the last argument is truncated to s16. */
#ifdef TARGET_PC
/* PC: the callers use a result (playEntitySound and func_8000DEE4 declare it to return s32): the sound's handle,
 * which MusBankStartEffect2 leaves in v0 on the N64, where this function, declared void, does not touch v0 before
 * it returns. On PC the function returns it (port_decls.h declares it so). */
s32 func_800032A4(s16 a, s16 b, s16 c, s16 d, s32 e) {
    s32 value = *(volatile s32 *)&e;
    value = (s16)value;
    return MusBankStartEffect2(D_800482D4, a, b, c, d, value);
}
#else
void func_800032A4(s16 a,s16 b,s16 c,s16 d,s32 e) { s32 value=*(volatile s32 *)&e; value=(s16)value; MusBankStartEffect2(D_800482D4,a,b,c,d,value); }
#endif
