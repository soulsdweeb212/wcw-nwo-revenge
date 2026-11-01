/* @header
 * func_80097BB4
 * VRAM 0x80097BB4 | ROM 0x8B054 | size 0x2C
 * asm: asm/nonmatchings/ovl2_80090000/func_80097BB4.s
 */
#include "common.h"

extern s8 D_800F99B4;
extern s8 D_800F99B5;

void func_80097BB4(void) {
    if (D_800F99B4) {
        D_800F99B4 = 0;
        D_800F99B5 = 0x78;
    }
}
