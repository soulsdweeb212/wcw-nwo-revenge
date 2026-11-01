/* @header
 * func_800C54FC
 * VRAM 0x800C54FC | ROM 0x71C6C | size 0xB4
 * asm: asm/nonmatchings/code_80090000/func_800C54FC.s
 */
#include "common.h"

extern s32 D_800D5F48, D_800D5F4C;
s32 func_8000DEE4(s32);
void func_8000DF78(s32);
void func_80013DB0(s32, s32);

static inline void set(s32 a, s32 b) {
    if (a >= 0) {
        if (b < 0) {
            b = 0;
        }
        if (b >= 0x7F) {
            b = 0x7F;
        }
        func_80013DB0(a, b);
    }
}

s32 func_800C54FC(s32 a) {
    if (a) {
        if (D_800D5F48 < 0) {
            D_800D5F48 = func_8000DEE4(0x41D);
        }
        if (a > 0) {
            D_800D5F4C = a;
        }
        set(D_800D5F48, D_800D5F4C);
        return 1;
    }
    if (D_800D5F48 < 0) {
        return 0;
    }
    func_8000DF78(D_800D5F48);
    return D_800D5F48 = -1;
}
