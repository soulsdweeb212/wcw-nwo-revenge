#include "common.h"

s32 func_80016730(s32 arg0, s32 arg1) {
    return arg1 + 2;
}

u8 *func_80016738(u8 *arg0, u8 *arg1) {
    u8 *temp_v1;
    s32 temp_a2;

    temp_v1 = *(u8 **)(arg0 + 0x94);
    temp_a2 = *(s32 *)(temp_v1 + 0x14);
    if (temp_a2 == *(s32 *)(temp_v1 + 0x10)) {
        *(u32 *)(arg0 + 0xA0) = 0;
    } else {
        *(u32 *)(arg0 + 0xA0) = (u32)(temp_v1 + *(s32 *)(temp_a2 + *arg1 * 4));
        arg1++;
    }
    return arg1;
}

s32 func_8001677C(s32 arg0, s32 arg1) {
    return arg1 + 1;
}

s32 func_80016784(u8 *arg0, u8 *arg1) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    a = *arg1++;
    b = *arg1++;
    c = *arg1++;
    d = *arg1++;
    *(s16 *)(arg0 + 0xC2) = 1;
    *(s32 *)(arg0 + 0x4C) = *(s32 *)(arg0 + 0xA8) + ((c << 8) + d);
    *(s16 *)(arg0 + 0xC4) = 1;
    *(s32 *)(arg0 + 0x48) = *(s32 *)(arg0 + 0xA4) + ((arg1[0] << 8) + arg1[1]);
    return *(s32 *)(arg0 + 0x9C) + ((a << 8) + b);
}
