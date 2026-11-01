/* @header
 * func_800A8F60
 * VRAM 0x800A8F60 | ROM 0x556D0 | size 0x38
 * asm: asm/nonmatchings/code_80090000/func_800A8F60.s
 */
#include "common.h"

extern u8 D_800CCB04[];

void func_800A8F60(u8 *p) {
    s32 i;
    for (i = 0; i < 8; i++) {
        p[i] = D_800CCB04[i];
    }
    p[i] = 0xA;
}
