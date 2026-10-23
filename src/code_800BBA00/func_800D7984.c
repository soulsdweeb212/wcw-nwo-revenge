#include "common.h"

/* Maps the direction bits of arg0 (0xF00) to an index 1..8, or 0. */
s32 func_800D7A68(s32 arg0) {
    s32 t = arg0 & 0xF00;
    u16 mode;

    if (t == 0) {
        return 0;
    }
    mode = t;
    if (mode == 0x800) {
        return 1;
    }
    if (mode == 0x900) {
        return 2;
    }
    if (mode == 0x100) {
        return 3;
    }
    if (mode == 0x500) {
        return 4;
    }
    if (mode == 0x400) {
        return 5;
    }
    if (mode == 0x600) {
        return 6;
    }
    if (mode == 0x200) {
        return 7;
    }
    if (mode == 0xA00) {
        return 8;
    }
    return 0;
}

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
