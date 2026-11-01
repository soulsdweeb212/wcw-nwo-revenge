/* @header
 * func_800AA0A4
 * VRAM 0x800AA0A4 | ROM 0x56814 | size 0x34
 * asm: asm/nonmatchings/code_80090000/func_800AA0A4.s
 */
#include "common.h"

extern s32 D_8007E228[];
extern s32 D_8007E8C0[];
void func_8002AD34(s32, s32);

void func_800AA0A4(s32 i) {
    func_8002AD34(D_8007E228[i + 0x1A2], D_8007E8C0[i + 0x1C]);
}
