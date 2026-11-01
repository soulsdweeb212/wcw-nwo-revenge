/* @header
 * func_800BA4B4
 * VRAM 0x800BA4B4 | ROM 0x66C24 | size 0xE8
 * asm: asm/nonmatchings/code_80090000/func_800BA4B4.s
 */
#include "common.h"

extern u8 *D_800DCFB8;
u8 *func_8002B790(s32, s32);
void func_80021C40(void *, void *, s32);

s32 func_800BA4B4(void) {
    s32 i, j;
    u8 *s;
    u8 *d;
    for (i = 0; i < 0x40; i++) {
        for (j = 0; j < 4; j++) {
            d = func_8002B790(i, j);
            s = D_800DCFB8 + 0x600 + i * 0x9C + j * 0x26;
            func_80021C40(s, d, 0x18);
            func_80021C40(s + 0x18, d + 0x19, 0xA);
            d[0x24] = s[0x22];
            d[0x25] = s[0x23];
            d[0x26] = 0;
            d[0x27] = s[0x25] & 0x1F;
            d[0x28] = (*(u16 *)(s + 0x24) >> 5) & 0x1F;
        }
    }
    return 0;
}
