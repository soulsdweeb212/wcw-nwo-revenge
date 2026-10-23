#include "common.h"

/* Map a reaction bitmask to a 0..3 category, or -1. */
s32 func_800D7A2C(s32 arg0) {
    if (arg0 & 0x800) {
        return 0;
    }
    if (arg0 & 0x100) {
        return 1;
    }
    if (arg0 & 0x400) {
        return 2;
    }
    return (arg0 & 0x200) ? 3 : -1;
}

/* Map the 0xF00 field of arg0 to a 0..8 category. */
s32 func_800D7A68(s32 arg0) {
    u16 t = arg0 & 0xF00;

    if (t == 0) {
        return 0;
    }
    if (t == 0x800) {
        return 1;
    }
    if (t == 0x900) {
        return 2;
    }
    if (t == 0x100) {
        return 3;
    }
    if (t == 0x500) {
        return 4;
    }
    if (t == 0x400) {
        return 5;
    }
    if (t == 0x600) {
        return 6;
    }
    if (t == 0x200) {
        return 7;
    }
    if (t == 0xA00) {
        return 8;
    }
    return 0;
}

s16 func_800D7690(void *, s32, s32);
s32 func_800D4198(s32);

/* Tick arg0's +0x18 countdown, adjusting it by two sub-checks; return 1 when it
 * expires and a reset is not requested. */
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
            return 0;
        }
        return 1;
    }
    return 0;
}

/* Map the 0xF00 field of arg0 to a 0..3 category, or -1. */
s32 func_800D7B08(s32 arg0) {
    s32 t = arg0 & 0xF00;

    if (t == 0x900) {
        return 0;
    }
    if (t == 0x500) {
        return 1;
    }
    if (t == 0x600) {
        return 2;
    }
    return (t == 0xA00) ? 3 : -1;
}
