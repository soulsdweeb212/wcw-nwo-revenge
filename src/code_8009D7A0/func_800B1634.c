/* @header
 * func_800B1634
 * VRAM 0x800B1634 | ROM 0xA4AD4 | size 0x9C
 * asm: asm/nonmatchings/code_8009D7A0/func_800B1634.s
 */
#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;
s8 func_800D4198(s16);
f32 func_800B3AD8(void *);

/* Return a countdown value for the current action record D_800FABD0 when its
 * mode field (+0x22) is one of 6/0x17/0x11 and the entity animation check
 * func_800D4198 passes: entity[D_800F9B60+0x370] minus the timer (entity+6)
 * minus one, clamped at 0. */
s16 func_800B1634(void) {
    s16 count = 0;
    u8 *act = D_800FABD0;
    s16 mode = *(s16 *)(act + 0x22);
    if (mode == 6 || mode == 0x17 || mode == 0x11) {
        if (func_800D4198(*(s16 *)(act + 0x12))) {
            count = D_800F9B60[0x370] - *(u16 *)(D_800F9B60 + 6) - 1;
            if (count < 0) count = 0;
        }
    }
    return count;
}
