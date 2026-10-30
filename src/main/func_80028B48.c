/* @header
 * func_80028B48
 * VRAM 0x80028B48 | ROM 0x29748 | size 0x14
 * asm: asm/nonmatchings/main/func_80028B48.s
 */
#include "common.h"

extern u8 D_80038E4C[];

u8 *func_80028B48(s32 arg0) {
    return &D_80038E4C[arg0 & 0xF];
}
