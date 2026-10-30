/* @header
 * func_800AD218
 * VRAM 0x800AD218 | ROM 0xA06B8 | size 0xAC
 * asm: asm/nonmatchings/code_8009D7A0/func_800AD218.s
 */
#include "common.h"

s32 func_800A93C0();                                /* extern */

/* Selects an action input: when the gate func_800A93C0 is clear, either sets
 * the pending 0x200000 flag on the object (for a fresh attack input) or writes
 * the combined direction mask to *arg4. Returns 1 on a selection. */
s32 func_800AD218(void *arg0, s32 arg1, s32 arg2, s32 arg3, s16 *arg4) {
    s32 temp_a0;
    s32 temp_a2;

    if ((func_800A93C0() << 0x18) == 0) {
        temp_a0 = *(s32 *)((u8 *)arg0 + 0x2C);
        if (temp_a0 & 1 & ((arg3 << 0x18) != 0)) {
            *(s32 *)((u8 *)arg0 + 0x2C) = (s32)(temp_a0 | 0x200000);
            return 1;
        }
        temp_a2 = arg2 & 0xC000;
        if (temp_a2 != 0) {
            *arg4 = temp_a2 | (arg1 & 0xF00);
            return 1;
        }
        return 0;
    }
    return 0;
}
