/* @header
 * osAiSetFrequency  (originally func_80022000)
 * VRAM 0x80022000 | ROM 0x22C00 | size 0x118
 * asm: asm/nonmatchings/main/osAiSetFrequency.s
 */
/* SDK: libultra 2.0I, ultralib src/io/aisetfreq.c (same code as the SDK source). */
#include "common.h"

extern s32 osViClock;   /* AI clock frequency */
extern f64 D_8003B8F0;   /* 2^32, used to wrap negative rates */

/* Program the AI DAC-rate and bit-rate registers (0xA4500010 / 0xA4500014) for
 * the requested sample rate arg0. Returns -1 if the rate is out of range,
 * otherwise the realised rate. */
s32 osAiSetFrequency(s32 arg0) {
    f32 num;
    f64 den;
    f32 temp;
    u32 dacRate;
    u32 bitRate;

    num = (f32)osViClock;
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
    return osViClock / (s32)dacRate;
}
