/* @header
 * func_800BB5A4
 * VRAM 0x800BB5A4 | ROM 0x67D14 | size 0x144
 * asm: asm/nonmatchings/code_80090000/func_800BB5A4.s
 */
#include "common.h"

s32 func_8002AEE0(void);
s32 func_8001C580(void);

s32 func_800BB5A4(void) {
    s32 t;
    switch (func_8002AEE0() & 0xF0) {
    case 0x00:
        return 1;
    case 0x10:
        return 2;
    case 0x20:
        return 3;
    case 0x30:
        return 4;
    case 0x40:
        return 5;
    case 0x50:
        return 6;
    case 0x60:
        return 7;
    case 0x70:
        return 8;
    }
    t = func_8001C580() % 100;
    if (t < 10) {
        return 1;
    }
    if (t < 15) {
        return 3;
    }
    if (t < 25) {
        return 4;
    }
    if (t < 30) {
        return 5;
    }
    if (t < 40) {
        return 6;
    }
    if (t < 50) {
        return 7;
    }
    return (t < 60) * 8;
}
