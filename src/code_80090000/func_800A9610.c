/* @header
 * func_800A9610
 * VRAM 0x800A9610 | ROM 0x55D80 | size 0x12C
 * asm: asm/nonmatchings/code_80090000/func_800A9610.s
 */
#include "common.h"

extern s32 D_800EA0B8;
extern u8 D_8007EF30[];
void func_800B48CC(s32);

void func_800A9610(s32 d) {
    if (d < 0) {
        D_800EA0B8--;
        if (D_800EA0B8 == 6 && !(D_8007EF30[0x14D] & 2)) {
            D_800EA0B8--;
        }
        if (D_800EA0B8 == 5 && !(D_8007EF30[0x14D] & 1)) {
            D_800EA0B8--;
        }
        if (D_800EA0B8 < 0) {
            D_800EA0B8 = 8;
        }
    } else {
        D_800EA0B8++;
        if (D_800EA0B8 == 5 && !(D_8007EF30[0x14D] & 1)) {
            D_800EA0B8++;
        }
        if (D_800EA0B8 == 6 && !(D_8007EF30[0x14D] & 2)) {
            D_800EA0B8++;
        }
        if (D_800EA0B8 >= 9) {
            D_800EA0B8 = 0;
        }
    }
    func_800B48CC(D_800EA0B8);
}
