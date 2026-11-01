/* @header
 * func_800C1C4C
 * VRAM 0x800C1C4C | ROM 0x6E3BC | size 0x24
 * asm: asm/nonmatchings/code_80090000/func_800C1C4C.s
 */
#include "common.h"

extern s32 D_800DF210;
void releaseHeapBlock(s32);

void func_800C1C4C(void) {
    releaseHeapBlock(D_800DF210);
}
