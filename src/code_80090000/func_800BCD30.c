/* @header
 * func_800BCD30
 * VRAM 0x800BCD30 | ROM 0x694A0 | size 0xC4
 * asm: asm/nonmatchings/code_80090000/func_800BCD30.s
 */
#include "common.h"

extern struct { u8 pad0[8]; u16 mode; } D_8007EF30;
extern s32 D_800E7C90;
void func_8000E55C(s32, s32, s32);

s32 func_800BCD30(void) {
    s32 r = -1;

    switch (D_800E7C90) {
    case 0x1D: case 0x1E: case 0x1F: case 0x20: case 0x21:
        r = 0x13;
        break;
    case 0x24: case 0x25: case 0x26: case 0x27: case 0x28:
        r = 0x12;
        break;
    case 0x38: case 0x39: case 0x3A:
        r = 0xB;
        break;
    case 2: case 3:
        r = 0x10;
        break;
    case 6: case 7:
        r = (D_8007EF30.mode & 0x60) ? 0x11 : 0x10;
        break;
    case 4: case 5: case 8: case 9:
        r = 0x11;
        break;
    case 0xD: case 0xE: case 0xF: case 0x10: case 0x11: case 0x12: case 0x13: case 0x14:
        r = -1;
        break;
    case 0xA: case 0xB: case 0xC: case 0x15: case 0x2F: case 0x30: case 0x31: case 0x3C: case 0x3D: case 0x3E:
        r = 0;
        break;
    case 0x3B:
        func_8000E55C(0, 0x10, 0x50);
        break;
    default:
        func_8000E55C(0, 1, 0x50);
        break;
    }
    return r;
}
