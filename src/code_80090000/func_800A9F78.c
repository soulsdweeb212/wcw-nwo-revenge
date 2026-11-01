/* @header
 * func_800A9F78
 * VRAM 0x800A9F78 | ROM 0x566E8 | size 0x28
 * asm: asm/nonmatchings/code_80090000/func_800A9F78.s
 */
#include "common.h"

extern u8 D_8007EF30[];

u8 func_800A9F78(s32 i) {
    if (*(u16 *)(D_8007EF30 + 8) & 0x90) {
        return D_8007EF30[(i << 4) + 0x51];
    }
    return D_8007EF30[(i << 5) + 0x51];
}
