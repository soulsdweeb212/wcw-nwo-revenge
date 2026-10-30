/* @header
 * func_800B3AD8
 * VRAM 0x800B3AD8 | ROM 0xA6F78 | size 0x4C
 * asm: asm/nonmatchings/code_8009D7A0/func_800B3AD8.s
 */
#include "common.h"

/* Scale factor from arg0's s16 timer at +0x16: 0.65 below 0x41, 0.55 below 0x81,
 * otherwise 0.45. */
f32 func_800B3AD8(void *arg0) {
    f32 r;
    s16 t;

    t = *(s16 *)((s8 *)arg0 + 0x16);
    if (t >= 0x81) {
        return 0.45f;
    }
    r = 0.65f;
    if (t >= 0x41) {
        r = 0.55f;
    }
    return r;
}
