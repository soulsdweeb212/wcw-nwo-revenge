/* @header
 * func_8000DE40
 * VRAM 0x8000DE40 | ROM 0xEA40 | size 0x28
 * asm: asm/nonmatchings/main/func_8000DE40.s
 */
#include "common.h"

extern s16 D_800307A0;

/* Set the grayscale-conversion flag from whether arg0 is zero. */
void func_8000DE40(s32 arg0) {
    if ((arg0 << 0x10) == 0) {
        D_800307A0 = 1;
        return;
    }
    D_800307A0 = 0;
}
