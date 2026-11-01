/* @header
 * func_800BABC0
 * VRAM 0x800BABC0 | ROM 0x67330 | size 0x34
 * asm: asm/nonmatchings/code_80090000/func_800BABC0.s
 */
#include "common.h"

extern u8 *D_800DCFB8;
extern u8 D_8007E228[];
void func_80021C40(void *, void *, s32);

s32 func_800BABC0(void) {
    func_80021C40(D_800DCFB8 + 0x2D20, D_8007E228 + 0x18, 0x40);
    return 0;
}
