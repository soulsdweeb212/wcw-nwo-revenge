/* @header
 * func_800BF018
 * VRAM 0x800BF018 | ROM 0xB24B8 | size 0x138
 * asm: asm/nonmatchings/code_800BBA00/func_800BF018.s
 */
#include "common.h"

extern f64 D_800E5868;
extern f64 D_800E5870;
extern f64 D_800E5878;
s32 func_800BED3C(u8 *, s32, u32);

/* Directional boundary test for obj (facing +0x3E): for the front/back
 * quadrants (0/2) compares the X position (+0x6C) against the low/high f64
 * thresholds; for the left/right quadrants (1/3) compares the Z position
 * (+0x74). When a bound is crossed it runs func_800BED3C; if that returns a
 * mask intersecting the request it reports 2, otherwise 1, else 0. */
s32 func_800BF018(u8 *obj, s32 arg1, u32 mask) {
    s32 flag = 0, result;
    u32 m = mask;
    s16 state = *(s16 *)(obj + 0x3E);

    switch (state) {
    case 0:
    case 2:
        if ((m & 0x200) && (f64)*(f32 *)(obj + 0x6C) < D_800E5868) {
            flag = 1;
            break;
        }
        if ((m & 0x100) && D_800E5878 < (f64)*(f32 *)(obj + 0x6C)) {
            flag = 1;
        }
        break;
    case 1:
    case 3:
        if ((m & 0x400) && (f64)*(f32 *)(obj + 0x74) < D_800E5870) {
            flag = 1;
            break;
        }
        if ((m & 0x800) && D_800E5878 < (f64)*(f32 *)(obj + 0x74)) {
            flag = 1;
        }
        break;
    }

    result = flag;
    if (result == 0) {
        result = 0;
    } else {
        result = func_800BED3C(obj, arg1, mask);
        if (m & result & 0xFFFF) {
            return 2;
        }
        return 1;
    }
    return result;
}
