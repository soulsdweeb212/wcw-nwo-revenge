/* @header
 * func_800B9F18
 * VRAM 0x800B9F18 | ROM 0x66688 | size 0x140
 * asm: asm/nonmatchings/code_80090000/func_800B9F18.s
 */
#include "common.h"

extern u8 *D_800DCFB8;
extern u8 D_8007EF30[], D_8007E8C0[];
extern u16 D_800D2900, D_800D2902;
extern s32 D_800DCFC4, D_800DCFBC;
s32 func_8000424C(void);
s32 func_800B9640(u16, u16);
void func_80004290(void);

s32 func_800B9F18(void) {
    s32 i;
    u8 *d;
    u8 *s = D_8007EF30 + 0x14C;
    D_800DCFB8[1] = s[0];
    D_800DCFB8[0] = D_8007EF30[0x14D];
    i = 0;
    s += 2;
    d = D_800DCFB8;
    do {
        *(u16 *)(d + 2) = *(u16 *)s;
        s += 2;
        d += 2;
        i++;
    } while (i < 12);
    *(u16 *)(D_800DCFB8 + 0x3A) = (D_8007E8C0[0x66D] & 3) | ((D_8007E8C0[0x66E] & 1) << 2) | ((D_8007E8C0[0x66F] & 1) << 3) | ((D_8007EF30[0] & 1) << 4) | ((D_8007EF30[3] & 1) << 5) | ((D_8007EF30[1] & 1) << 6) | ((D_8007EF30[2] & 1) << 7) | ((D_8007EF30[4] & 7) << 8);
    D_800DCFC4 = func_8000424C();
    D_800DCFBC = func_800B9640(D_800D2900, D_800D2902);
    func_80004290();
    return 0;
}
