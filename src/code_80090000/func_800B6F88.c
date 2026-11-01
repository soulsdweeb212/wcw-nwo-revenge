/* @header
 * func_800B6F88
 * VRAM 0x800B6F88 | ROM 0x636F8 | size 0x58
 * asm: asm/nonmatchings/code_80090000/func_800B6F88.s
 */
#include "common.h"

u8 *func_800B600C(u8 *, s32);

static inline u8 *hdr(u8 *a, u8 **b, u8 **c) {
    u8 *p = a + 0x10;
    *c = p;
    p += *(u16 *)(a + 0xA) * 2;
    *b = p;
    return a;
}

u8 *func_800B6F88(u8 *a, u8 **b, u8 **c) {
    u8 *v = func_800B600C(a, 0);
    if (v == 0) {
        return 0;
    }
    return hdr(v, b, c);
}
