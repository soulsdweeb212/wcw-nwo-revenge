/* @header
 * func_800D78F4
 * VRAM 0x800D78F4 | ROM 0xCAD94 | size 0x90
 * asm: asm/nonmatchings/code_800BBA00/func_800D78F4.s
 */
#include "common.h"

s16 func_800D7690(void *, s32, s32);

/* Ticks the entity's 0x18 counter down (an extra tick when the movement check
 * succeeds), returning 1 when it reaches zero unless arg2 holds it at zero. */
s32 func_800D78F4(u8 *arg0, s32 arg1, s32 arg2) {
    s32 v;

    *(u16 *)(arg0 + 0x18) = *(u16 *)(arg0 + 0x18) - 1;
    if (func_800D7690(arg0, arg1 & 0xFFFF, 1) == 1) {
        *(u16 *)(arg0 + 0x18) = *(u16 *)(arg0 + 0x18) - 1;
    }
    v = (s16)*(u16 *)(arg0 + 0x18);
    if (v >= 0) v = 0; else v = 1;
    if (v != 0) {
        if (arg2 << 24) {
            *(u16 *)(arg0 + 0x18) = 0;
        } else {
            return 1;
        }
    }
    return 0;
}
