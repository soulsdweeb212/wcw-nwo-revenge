/* @header
 * __osSpGetStatus  (originally func_80027380)
 * VRAM 0x80027380 | ROM 0x27F80 | size 0x10
 * asm: asm/nonmatchings/main/__osSpGetStatus.s
 */
/* SDK: libultra 2.0I, ultralib src/io/spgetstat.c (same code as the SDK source). */
#include "common.h"

s32 __osSpGetStatus(void) {
    return *(vu32 *)0xA4040010;
}

extern s32 D_8007BD60;
s32 __osDisableInt(void);
s32 osGetCount(void);
void __osRestoreInt(s32);
void __osSetCompare(s32, s32);
