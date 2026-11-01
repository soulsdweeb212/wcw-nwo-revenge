/* @header
 * func_800AA4DC
 * VRAM 0x800AA4DC | ROM 0x56C4C | size 0x2C
 * asm: asm/nonmatchings/code_80090000/func_800AA4DC.s
 */
#include "common.h"

extern s16 D_800E7CB8;
extern u8 D_800E7B67[];

s32 func_800AA4DC(void) {
    s32 r;
    if (D_800E7CB8 <= 0) {
        r = -1;
    } else {
        r = D_800E7B67[D_800E7CB8 * 2];
    }
    return r;
}
