/* @header
 * func_800A2AF4
 * VRAM 0x800A2AF4 | ROM 0x4F264 | size 0x68
 * asm: asm/nonmatchings/code_80090000/func_800A2AF4.s
 */
#include "common.h"

s32 func_800996B0(u32 **, s32, s32);
void func_800A289C(u32 **, s32, s32, s32);

void func_800A2AF4(u32 **dl, s32 b, s32 c, s32 d, s32 e) {
    u32 *g = *dl;
    func_800A289C(&g, func_800996B0(&g, b, d | 8), c, e);
    *dl = g;
}
