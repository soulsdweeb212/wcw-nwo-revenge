/* @header
 * func_800ADF84
 * VRAM 0x800ADF84 | ROM 0x5A6F4 | size 0x60
 * asm: asm/nonmatchings/code_80090000/func_800ADF84.s
 */
#include "common.h"

extern u8 *D_800E8D3C;
extern u8 D_8007E8C0[], D_8007EF30[];

void func_800ADF84(void) {
    u8 *p = D_800E8D3C;
    p[0xE] = D_8007E8C0[0x66D];
    p[0x52E] = D_8007E8C0[0x66E];
    p[0x29E] = D_8007E8C0[0x66F];
    p[0x7BE] = D_8007EF30[0];
    p[0xA4E] = D_8007EF30[3];
    p[0xCDE] = D_8007EF30[1];
    p[0xF6E] = D_8007EF30[2];
}
