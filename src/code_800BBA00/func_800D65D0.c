/* @header
 * func_800D65D0
 * VRAM 0x800D65D0 | ROM 0xC9A70 | size 0x40
 * asm: asm/nonmatchings/code_800BBA00/func_800D65D0.s
 */
#include "common.h"

extern u32 D_800FABD8;
extern u16 D_800E3F84[];
extern u16 D_800E3F8C[];
extern u8 D_80030560[];
extern u8 D_8007C438[];

/* Classify the entity's quadrant (+0x3C) against mask arg1: 1, 2 or 0. */
s32 func_800D65D0(u8 *arg0, s32 arg1) {
    s32 idx = *(s16 *)(arg0 + 0x3C);

    if (D_800E3F84[idx] & arg1) {
        return 1;
    }
    return ((D_800E3F8C[idx] & arg1) != 0) * 2;
}
