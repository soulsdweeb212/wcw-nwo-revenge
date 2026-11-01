/* @header
 * func_800BB360
 * VRAM 0x800BB360 | ROM 0x67AD0 | size 0x7C
 * asm: asm/nonmatchings/code_80090000/func_800BB360.s
 */
#include "common.h"

extern s32 D_800DCFC4, D_800DCFBC;
extern u8 D_800DCF50[];
s32 func_8000424C(void);
void func_80004290(void);
s32 func_80024850(s32, void *, s32);
s32 readWriteControllerPakBank(s32, void *, s32);

s32 func_800BB360(void) {
    u8 buf[0x68];
    s32 x = func_8000424C();
    D_800DCFC4 = x;
    D_800DCFBC = func_80024850(x, D_800DCF50, 0);
    if (D_800DCFBC == 0xA) {
        if (readWriteControllerPakBank(D_800DCFC4, buf, 0) == 0) {
            D_800DCFBC = 0x40;
        }
    }
    func_80004290();
    return D_800DCFBC;
}
