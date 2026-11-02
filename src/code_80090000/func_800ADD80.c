/* @header
 * func_800ADD80
 * VRAM 0x800ADD80 | ROM 0x5A4F0 | size 0x178
 * asm: asm/nonmatchings/code_80090000/func_800ADD80.s
 */
#include "common.h"

extern u8 D_8007EF30[];

s32 func_800ADD80(s32 a) {
    D_8007EF30[0x81] = 0;
    D_8007EF30[0x71] = 0;
    D_8007EF30[0x61] = 0;
    D_8007EF30[0x51] = 0;
    switch (a) {
    case 0x16:
    case 0x27:
        D_8007EF30[0x51] = 1;
        break;
    case 0x15:
    case 0x19:
    case 0x20:
    case 0x26:
    case 0x29:
        D_8007EF30[0x51] = 1;
        D_8007EF30[0x61] = 2;
        break;
    case 0x18:
    case 0x25:
        D_8007EF30[0x51] = 1;
        D_8007EF30[0x61] = 2;
        D_8007EF30[0x71] = 3;
        break;
    case 0x1E:
    case 0x24:
        D_8007EF30[0x51] = 1;
        D_8007EF30[0x61] = 2;
        D_8007EF30[0x71] = 3;
        D_8007EF30[0x81] = 4;
        break;
    case 0x1A:
        D_8007EF30[0x51] = 1;
        D_8007EF30[0x61] = 1;
        D_8007EF30[0x71] = 2;
        break;
    case 0x1B:
        D_8007EF30[0x71] = 1;
        break;
    case 0x21:
        D_8007EF30[0x51] = 1;
        D_8007EF30[0x61] = 1;
        D_8007EF30[0x71] = 2;
        D_8007EF30[0x81] = 2;
        break;
    case 0x1F:
        D_8007EF30[0x51] = 1;
        D_8007EF30[0x61] = 2;
        D_8007EF30[0x71] = 3;
        D_8007EF30[0x81] = 3;
        break;
    case 0x1C:
    case 0x22:
    case 0x2A:
        D_8007EF30[0x51] = 1;
        D_8007EF30[0x61] = 1;
        break;
    }
    return (*(u16 *)(D_8007EF30 + 8) & 0x80) ? 8 : 0xD;
}
