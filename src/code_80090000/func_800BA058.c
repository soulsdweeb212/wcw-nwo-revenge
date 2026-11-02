/* @header
 * func_800BA058
 * VRAM 0x800BA058 | ROM 0x667C8 | size 0x14C
 * asm: asm/nonmatchings/code_80090000/func_800BA058.s
 */
#include "common.h"

extern u8 *D_800DCFB8;
extern u8 D_8007EF30[], D_8007E8C0[];
extern s32 D_800DCFBC;
extern u8 D_8007E908[];
void func_800BACF0(u8 *, s32);

s32 func_800BA058(void) {
    u8 *p;
    u8 c;
    u8 *n;
    s32 i;
    u8 *d = D_800DCFB8;
    D_8007EF30[0x14C] = d[1];
    D_8007EF30[0x14D] = d[0];
    for (i = 0; i < 12; i++) {
        *(u16 *)(D_8007EF30 + 0x14E + i * 2) = ((u16 *)d)[i + 1];
    }
    p = D_800DCFB8;
    c = p[0x3B];
    D_8007E8C0[0x66E] = (*(u16 *)(p + 0x3A) >> 2) & 1;
    D_8007E8C0[0x66F] = (*(u16 *)(p + 0x3A) >> 3) & 1;
    D_8007EF30[0] = (*(u16 *)(p + 0x3A) >> 4) & 1;
    D_8007EF30[3] = (*(u16 *)(p + 0x3A) >> 5) & 1;
    D_8007EF30[1] = (*(u16 *)(p + 0x3A) >> 6) & 1;
    n = D_8007E908;
    D_8007EF30[2] = (*(u16 *)(p + 0x3A) >> 7) & 1;
    D_8007EF30[4] = (*(u16 *)(p + 0x3A) >> 8) & 7;
    D_8007E8C0[0x66D] = c & 3;
    func_800BACF0(n, 0);
    func_800BACF0(n + 9, 1);
    func_800BACF0(n + 0x12, 2);
    func_800BACF0(n + 0x1B, 3);
    return D_800DCFBC;
}
