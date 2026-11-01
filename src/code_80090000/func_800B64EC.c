/* @header
 * func_800B64EC
 * VRAM 0x800B64EC | ROM 0x62C5C | size 0x5C
 * asm: asm/nonmatchings/code_80090000/func_800B64EC.s
 */
#include "common.h"

u8 *func_800B64EC(u8 *a, s32 i) {
    u32 n = (a[3] << 24) | (a[2] << 16) | (a[1] << 8) | a[0];
    if (i < 0 || (u32)i >= n) {
        return a;
    }
    return a + ((s32 *)(a + 4))[i];
}
