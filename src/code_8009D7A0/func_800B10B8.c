/* @header
 * func_800B10B8
 * VRAM 0x800B10B8 | ROM 0xA4558 | size 0x84
 * asm: asm/nonmatchings/code_8009D7A0/func_800B10B8.s
 */
#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;
s8 func_800D4198(s16);
f32 func_800B3AD8(void *);
/* Returns the remaining countdown for the entity when it is in state 0x44 (and
 * the chance roll passes): the entity limit minus the elapsed counter. */
s16 func_800B10B8(void) {
    s16 result = 0;
    if (*(s16 *)(D_800F9B60 + 0xA) == 0x44) {
        if (func_800D4198(*(s16 *)(D_800FABD0 + 0x12))) {
            result = D_800F9B60[0x370] - *(u16 *)(D_800F9B60 + 6) - 1;
            if (result < 0) result = 0;
        }
    }
    return result;
}
