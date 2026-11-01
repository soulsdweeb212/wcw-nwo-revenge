/* @header
 * func_800B6F68
 * VRAM 0x800B6F68 | ROM 0x636D8 | size 0x20
 * asm: asm/nonmatchings/code_80090000/func_800B6F68.s
 */
#include "common.h"

u8 *func_800B6F68(u8 *a, u8 **b, u8 **c) {
    u8 *p = a + 0x10;
    *c = p;
    p += *(u16 *)(a + 0xA) * 2;
    *b = p;
    return a;
}
