/* @header
 * func_800AA070
 * VRAM 0x800AA070 | ROM 0x567E0 | size 0x34
 * asm: asm/nonmatchings/code_80090000/func_800AA070.s
 */
#include "common.h"

extern s32 D_8007E228[];
extern s32 D_8007E8C0[];
void func_8002AD04(s32, s32);

void func_800AA070(s32 i) {
    func_8002AD04(D_8007E228[i + 0x1A2], D_8007E8C0[i + 0x1C]);
}
