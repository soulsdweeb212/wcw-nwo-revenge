/* @header
 * func_800B99D0
 * VRAM 0x800B99D0 | ROM 0x66140 | size 0x58
 * asm: asm/nonmatchings/code_80090000/func_800B99D0.s
 */
#include "common.h"

extern s32 D_800DCFC4, D_800DCFBC;
s32 func_8000424C(void);
s32 func_800B9640(s32, s32);
void func_80004290(void);

s32 func_800B99D0(s32 a, s32 b) {
    D_800DCFC4 = func_8000424C();
    D_800DCFBC = func_800B9640(a, b);
    func_80004290();
    return D_800DCFBC;
}
