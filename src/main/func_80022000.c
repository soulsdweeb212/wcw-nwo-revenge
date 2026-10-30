/* @header
 * func_80022000
 * VRAM 0x80022000 | ROM 0x22C00 | size 0x118
 * asm: asm/nonmatchings/main/func_80022000.s
 */
#include "common.h"

extern s32 D_80038808;   /* AI clock frequency */
extern f64 D_8003B8F0;   /* 2^32, used to wrap negative rates */

/* Program the AI DAC-rate and bit-rate registers (0xA4500010 / 0xA4500014) for
 * the requested sample rate arg0. Returns -1 if the rate is out of range,
 * otherwise the realised rate. */
s32 func_80022000(s32 arg0) {
    f32 num;
    f64 den;
    f32 temp;
    u32 dacRate;
    u32 bitRate;

    num = (f32)D_80038808;
    den = (f64)arg0;
    if (arg0 < 0) {
        den += D_8003B8F0;
    }
    temp = num / (f32)den + 0.5f;
    dacRate = (u32)temp;
    if (dacRate < 0x84) {
        return -1;
    }
    bitRate = dacRate / 66;
    if ((bitRate & 0xFF) >= 0x11) {
        bitRate = 0x10;
    }
    *(volatile u32 *)0xA4500010 = dacRate - 1;
    *(volatile u32 *)0xA4500014 = (bitRate & 0xFF) - 1;
    return D_80038808 / (s32)dacRate;
}
