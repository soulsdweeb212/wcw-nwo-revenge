/* @header
 * func_80096F64
 * VRAM 0x80096F64 | ROM 0x8A404 | size 0x84
 * asm: asm/nonmatchings/ovl2_80090000/func_80096F64.s
 */
#include "common.h"

extern s16 *D_800E2CF4[];
extern u8 *D_800E2D58[];
extern s8 D_800F99B4;
extern s8 D_800F99B5;
extern s8 D_800F9A9E;
extern s16 D_800F9AA0;
extern s8 D_800F9AF8;

void func_80096F64(void) {
    s32 v;

    v = (s8)(D_800E2CF4[D_800F99B4][D_800F9A9E] + 0x5C) / 2;
    D_800F9AF8 = v;
    D_800F99B5 = D_800E2D58[D_800F99B4][D_800F9A9E];
    if (v >= 5) {
        D_800F9AA0 = 0x6F;
    } else {
        D_800F9AA0 = 0x50;
    }
}
