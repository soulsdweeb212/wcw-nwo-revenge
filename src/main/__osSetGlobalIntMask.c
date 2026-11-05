/* @header
 * __osSetGlobalIntMask  (originally func_80028160)
 * VRAM 0x80028160 | ROM 0x28D60 | size 0x40
 * asm: asm/nonmatchings/main/__osSetGlobalIntMask.s
 */
/* SDK: libultra 2.0I, ultralib src/os/setglobalintmask.c (same code as the SDK source). */
#include "common.h"

s32 __osDisableInt();
void __osRestoreInt(s32);
extern s32 D_80038810;

/* Set the bits of arg0 in D_80038810, with interrupts disabled. */
void __osSetGlobalIntMask(s32 arg0) {
    s32 saved;

    saved = __osDisableInt();
    D_80038810 |= arg0;
    __osRestoreInt(saved);
}
