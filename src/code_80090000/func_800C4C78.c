/* @header
 * func_800C4C78
 * VRAM 0x800C4C78 | ROM 0x713E8 | size 0xF8
 * asm: asm/nonmatchings/code_80090000/func_800C4C78.s
 */
#include "common.h"

extern s32 D_800D5E80, D_800D5E84, D_800E8200, D_800E8204, D_800EA2D0, D_800EA2D4;
void func_800C4140(s32, s32, s32);
void func_800C491C(s32);
void func_800C4B50(void);

void func_800C4C78(s32 a) {
    D_800D5E84 = 0;
    switch (a) {
    case 2:
        D_800D5E80 = 1;
        func_800C4140(0, D_800E8200, D_800EA2D0);
        if (D_800E8204 >= 0) {
            func_800C4140(1, D_800E8204, D_800EA2D4);
            func_800C491C(2);
        } else {
            func_800C491C(1);
        }
        break;
    case 1:
        func_800C4B50();
        break;
    case 0:
        D_800D5E80 = 0;
        func_800C4140(0, D_800E8200, D_800EA2D0);
        func_800C4140(1, D_800E8204, D_800EA2D4);
        break;
    }
}
