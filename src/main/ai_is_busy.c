/* @header
 * ai_is_busy  (originally func_80027340)
 * VRAM 0x80027340 | ROM 0x27F40 | size 0x14
 * asm: asm/nonmatchings/main/func_80027340.s
 */
#include "common.h"

s32 ai_is_busy(void) {
    s32 value;
    s32 zero;
    value = *(vs32 *)0xA450000C;
    zero = 0;
    return value < zero;
}
