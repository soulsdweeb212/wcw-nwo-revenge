/* @header
 * func_800BABF4
 * VRAM 0x800BABF4 | ROM 0x67364 | size 0x64
 * asm: asm/nonmatchings/code_80090000/func_800BABF4.s
 */
#include "common.h"

extern s32 D_800DCFC4, D_800DCFBC;
s32 func_8000424C(void);
s32 func_800B9640(s32, s32);
void func_80004290(void);
extern u8 *D_800DCFB8;
extern u8 D_8007E228[];
extern u16 D_800D2918, D_800D291A;
void func_80021C40(void *, void *, s32);

s32 func_800BABF4(void) {
    func_80021C40(D_8007E228 + 0x18, D_800DCFB8 + 0x2D20, 0x40);
    D_800DCFC4 = func_8000424C();
    D_800DCFBC = func_800B9640(D_800D2918, D_800D291A);
    func_80004290();
    return 0;
}
