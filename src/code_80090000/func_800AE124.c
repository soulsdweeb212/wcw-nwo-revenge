/* @header
 * func_800AE124
 * VRAM 0x800AE124 | ROM 0x5A894 | size 0xC0
 * asm: asm/nonmatchings/code_80090000/func_800AE124.s
 */
#include "common.h"

extern u8 *D_800E8FAC;
extern u8 D_8007EF30[];
void func_800BA760(s32);

void func_800AE124(void) {
    u8 *p = D_800E8FAC;
    D_8007EF30[0x1A0] = p[0xE];
    D_8007EF30[0x1A2] = p[0x52E];
    D_8007EF30[0x1A1] = p[0x29E];
    D_8007EF30[0x1A3] = p[0x7BE];
    D_8007EF30[0x1A4] = p[0xA4E];
    D_8007EF30[0x1A5] = p[0xCDE];
    D_8007EF30[0x1A6] = p[0xF6E];
    D_8007EF30[0x1A7] = p[0x11FE];
    D_8007EF30[0x1A8] = p[0x148E];
    D_8007EF30[0x1A9] = p[0x171E];
    D_8007EF30[0x1AA] = p[0x19AE];
    if (*(u16 *)(D_8007EF30 + 8) & 0x80) {
        func_800BA760(1);
    } else {
        func_800BA760(0);
    }
}
