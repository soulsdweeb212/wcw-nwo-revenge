/* @header
 * func_8001CEF0
 * VRAM 0x8001CEF0 | ROM 0x1DAF0 | size 0xA4
 * asm: asm/nonmatchings/main/func_8001CEF0.s
 */
#include "common.h"

/* Build a 16-entry s16 table at obj+8 from the 16-bit input at obj+0:
 * entries 0..7 are zeroed, entry 8 holds the halved input, entries 9..15 hold
 * successive powers of (half / D_8003B6D0) scaled by D_8003B6D0. Also sets the
 * control half-word at obj+2 (0x4000 - half) and obj+0x2C = 1. */
extern f64 D_8003B6D0;

void func_8001CEF0(u8 *obj) {
    s32 raw;
    s16 half;
    s32 shifted;
    s32 i;
    f64 scale;
    f64 ratio;
    f64 step;

    raw = *(s16 *)obj;
    half = raw;
    shifted = half >> 1;
    half = shifted;
    *(s32 *)(obj + 0x2C) = 1;
    *(s16 *)(obj + 2) = 0x4000 - shifted;
    for (i = 7; i >= 0; i--)
        *(s16 *)(obj + i * 2 + 8) = 0;
    ratio = (f64)half / D_8003B6D0;
    scale = D_8003B6D0;
    *(s16 *)(obj + 0x18) = half;
    step = ratio;
    for (i = 9; i < 16; i++) {
        ratio = ratio * step;
        *(s16 *)(obj + i * 2 + 8) = (s16)(s32)(ratio * scale);
    }
}
