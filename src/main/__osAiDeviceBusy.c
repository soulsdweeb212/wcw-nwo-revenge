/* @header
 * __osAiDeviceBusy  (originally func_80027340)
 * VRAM 0x80027340 | ROM 0x27F40 | size 0x14
 * asm: asm/nonmatchings/main/__osAiDeviceBusy.s
 */
/* SDK: libultra 2.0I, ultralib src/io/ai.c (same code as the SDK source). */
#include "common.h"

s32 __osAiDeviceBusy(void) {
    s32 value;
    s32 zero;
    value = *(vs32 *)0xA450000C;
    zero = 0;
    return value < zero;
}
