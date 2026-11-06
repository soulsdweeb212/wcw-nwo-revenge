/* @header
 * func_800BF228
 * VRAM 0x800BF228 | ROM 0xB26C8 | size 0x2C
 * asm: asm/nonmatchings/code_800BBA00/func_800BF228.s
 */
#include "common.h"

extern u16 D_800EB4B8[];

/* Add `delta` to w->bodyPart[index], wrapping as a byte and clamping to 0 when
 * the result is negative. */
void func_800BF228(Wrestler *w, s16 index, s32 delta) {
    u8 sum = w->bodyPart[index] + delta;

    w->bodyPart[index] = sum;
    if ((s8)sum < 0) {
        w->bodyPart[index] = 0;
    }
}
