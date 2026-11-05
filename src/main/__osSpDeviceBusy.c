/* @header
 * __osSpDeviceBusy  (originally func_80027360)
 * VRAM 0x80027360 | ROM 0x27F60 | size 0x18
 * asm: asm/nonmatchings/main/__osSpDeviceBusy.s
 */
/* SDK: libultra 2.0I, ultralib src/io/sp.c (same code as the SDK source). */
#include "common.h"

s32 __osSpDeviceBusy(void) {
    return (*(vu32 *)0xA4040010 & 0x1C) != 0;
}

extern s32 __osTimerCounter;
s32 __osDisableInt(void);
s32 osGetCount(void);
void __osRestoreInt(s32);
void __osSetCompare(s32, s32);
