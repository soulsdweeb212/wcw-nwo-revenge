/* @header
 * func_800A8F98
 * VRAM 0x800A8F98 | ROM 0x55708 | size 0x4C
 * asm: asm/nonmatchings/code_80090000/func_800A8F98.s
 */
#include "common.h"

extern u8 D_800CCB04[];
extern u8 D_8007E8C0[];

static inline void copy(u8 *p) {
    s32 i;
    for (i = 0; i < 8; i++) {
        p[i] = D_800CCB04[i];
    }
    p[i] = 0xA;
}

void func_800A8F98(s32 n) {
    copy(D_8007E8C0 + 0x48 + n * 9);
}
