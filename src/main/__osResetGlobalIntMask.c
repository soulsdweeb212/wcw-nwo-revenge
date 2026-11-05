/* @header
 * __osResetGlobalIntMask  (originally func_80028110)
 * VRAM 0x80028110 | ROM 0x28D10 | size 0x48
 * asm: asm/nonmatchings/main/__osResetGlobalIntMask.s
 */
/* SDK: libultra 2.0I, ultralib src/os/resetglobalintmask.c (same code as the SDK source). */
#include "common.h"

s32 __osDisableInt();
void __osRestoreInt(s32);
extern s32 D_80038810;

/* Clear the bits of arg0 in D_80038810 (always leaving bits 0 and 0x400 set), with
 * interrupts disabled. */
void __osResetGlobalIntMask(s32 arg0) {
    s32 saved;

    saved = __osDisableInt();
    D_80038810 &= ~arg0 | 0x401;
    __osRestoreInt(saved);
}
