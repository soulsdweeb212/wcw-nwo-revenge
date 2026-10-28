#include "common.h"

s16 func_800D7690(void *, s32, s32);
s32 func_800D4198(s32);

/* Ticks the entity's 0x18 counter down (an extra tick when the movement check
 * succeeds and a tick back when the global 0x2EE gate is set), returning 1 when
 * the counter reaches zero unless arg2 holds it at zero. */
s32 func_800D7984(u8 *arg0, s32 arg1, s32 arg2) {
    *(u16 *)(arg0 + 0x18) = *(u16 *)(arg0 + 0x18) - 1;
    if (func_800D7690(arg0, arg1 & 0xFFFF, 1) == 1) {
        *(u16 *)(arg0 + 0x18) = *(u16 *)(arg0 + 0x18) - 1;
    }
    if ((func_800D4198(0x2EE) << 24) != 0) {
        *(u16 *)(arg0 + 0x18) = *(u16 *)(arg0 + 0x18) + 1;
    }
    if ((s16)*(u16 *)(arg0 + 0x18) <= 0) {
        if (arg2 << 24) {
            *(u16 *)(arg0 + 0x18) = 0;
        } else {
            return 1;
        }
    }
    return 0;
}
