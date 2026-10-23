#include "common.h"

extern s32 D_800604EC;

/* Steps the 32-bit RNG seed eight times (injecting the feedback bit when the
 * tap bits 0x48000000 are 0x48/0x08 patterns) and returns arg0 scaled by the
 * new seed as 16.16 fixed point. */
s32 func_80015B84(s32 arg0) {
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v1;
    u32 var_a2;

    var_a2 = 0;
    do {
        temp_a1 = D_800604EC * 2;
        temp_v0 = D_800604EC & 0x48000000;
        temp_v1 = (temp_v0 == 0x48000000) | (temp_v0 == 0x08000000);
        D_800604EC = temp_a1;
        var_a2 += 1;
        if (temp_v1 != 0) {
            D_800604EC = temp_a1 | 1;
        }
    } while (var_a2 < 8U);
    return (s32) ((f32) arg0 * (((f32) D_800604EC / 65536.0f) / 65536.0f));
}
