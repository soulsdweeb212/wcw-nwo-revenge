/* @header
 * func_80090000_ovl2  (originally func_80090000)
 * VRAM 0x80090000 | ROM 0x834A0 | size 0x30
 * asm: asm/nonmatchings/ovl2_80090000/func_80090000_ovl2.s
 */
#include "common.h"

s32 func_80090030();                                  /* extern */
extern s32 D_800F99B0;

void func_80090000_ovl2(void) {
    do {
        D_800F99B0 = 0;
        func_80090030();
    } while (D_800F99B0 != 0);
}
