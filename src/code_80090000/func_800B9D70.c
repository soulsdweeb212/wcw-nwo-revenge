/* @header
 * func_800B9D70
 * VRAM 0x800B9D70 | ROM 0x664E0 | size 0x30
 * asm: asm/nonmatchings/code_80090000/func_800B9D70.s
 */
#include "common.h"

s32 releaseHeapBlock(s32);                            /* extern */
extern s32 D_800D2970;

void func_800B9D70(void) {
    if (D_800D2970 != 0) {
        releaseHeapBlock(D_800D2970);
        D_800D2970 = 0;
    }
}
