/* @header
 * func_800005AC
 * VRAM 0x800005AC | ROM 0x11AC | size 0x24
 * asm: asm/nonmatchings/main/func_800005AC.s
 */
#include "common.h"

void func_80000D80(void *, s32);
extern s32 D_8003DE30;

/* Remove message arg0 from the event list at D_8003DE30. */
void func_800005AC(s32 arg0) {
    func_80000D80(&D_8003DE30, arg0);
}
