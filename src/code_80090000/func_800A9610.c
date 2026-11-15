/* @header
 * func_800A9610
 * VRAM 0x800A9610 | ROM 0x55D80 | size 0x12C
 * asm: asm/nonmatchings/code_80090000/func_800A9610.s
 */
#include "common.h"

extern s32 D_800EA0B8;
extern u8 D_8007EF30[];
#ifdef TARGET_PC
/* PC: func_800B48CC's definition returns an s32. */
s32 func_800B48CC(s32);
#else
void func_800B48CC(s32);
#endif

#ifdef TARGET_PC
/* PC: the N64 definition is void, but it ends with its call of func_800B48CC, so that call's result (0x10 or 0x11) is
 * still in v0 when it returns, and func_800AB3AC and func_800AC144 use it as their result. On PC nothing carries a
 * result that a function does not return, so the PC definition returns it, as their declarations (s32) read it. */
s32 func_800A9610(s32 d) {
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
    return func_800B48CC(D_800EA0B8);
}
#else
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
#endif
