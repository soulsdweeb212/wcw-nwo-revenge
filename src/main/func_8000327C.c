/* @header
 * func_8000327C
 * VRAM 0x8000327C | ROM 0x3E7C | size 0x28
 * asm: asm/nonmatchings/main/func_8000327C.s
 */
#include "common.h"

s32 MusBankStartEffect(s32, s16);
extern s32 D_800482D4;

/* Forward arg0 to MusBankStartEffect with the current context D_800482D4. */
void func_8000327C(s16 arg0) {
    MusBankStartEffect(D_800482D4, arg0);
}
