/* @header
 * func_800AE1E4
 * VRAM 0x800AE1E4 | ROM 0x5A954 | size 0xE4
 * asm: asm/nonmatchings/code_80090000/func_800AE1E4.s
 */
#include "common.h"

extern u8 D_8007EF30[];
extern u8 *D_800E8FAC;
void func_800A8EF0(s32);
#define B(o) (*(u8 *)(D_8007EF30 + (o)))

void func_800AE1E4(void) {
    u16 f = *(u16 *)(D_8007EF30 + 8);
    u8 *p = D_800E8FAC;
    s32 a;
    if (f & 0x8000) {
        a = **(u8 **)(D_8007EF30 + 0x30);
        a += 2;
    } else if (f & 0x80) {
        a = 8;
    } else {
        a = 7;
    }
    func_800A8EF0(a);
    p[0xE] = B(0x1A0);
    p[0x52E] = B(0x1A2);
    p[0x29E] = B(0x1A1);
    p[0x7BE] = B(0x1A3);
    p[0xA4E] = B(0x1A4);
    p[0xCDE] = B(0x1A5);
    p[0xF6E] = B(0x1A6);
    p[0x11FE] = B(0x1A7);
    p[0x148E] = B(0x1A8);
    p[0x171E] = B(0x1A9);
    p[0x19AE] = B(0x1AA);
}
