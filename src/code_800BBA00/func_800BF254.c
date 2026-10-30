/* @header
 * func_800BF254
 * VRAM 0x800BF254 | ROM 0xB26F4 | size 0x18
 * asm: asm/nonmatchings/code_800BBA00/func_800BF254.s
 */
#include "common.h"

extern u16 D_800EB4B8[];

void func_800BF254(s32 arg0) {
    D_800EB4B8[(s8)arg0] = 0;
}
