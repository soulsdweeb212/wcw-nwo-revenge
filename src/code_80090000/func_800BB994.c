/* @header
 * func_800BB994
 * VRAM 0x800BB994 | ROM 0x68104 | size 0x134
 * asm: asm/nonmatchings/code_80090000/func_800BB994.s
 */
#include "common.h"

s32 func_800BB994(s32 x, s32 y) {
    s32 a = x / 4;
    s32 b = y / 4;
    if (y < 0) {
        return 0;
    }
    if (b != 3) {
        switch (a) {
        case 0:
            if (y == 0x10 || y == 0x14) {
                goto yes;
            }
            if (y == 0x18 || y == 0x19 || y == 0x1C) {
                goto yes;
            }
            if (y != 0x1D) {
                break;
            }
            goto yes;
        case 1:
            if (y == 0x11 || y == 0x15) {
                goto yes;
            }
            if (y == 0x1A || y == 0x1B || y == 0x1E) {
                goto yes;
            }
            if (y != 0x1F) {
                break;
            }
            goto yes;
        default:
            if (y == 0x10 || y == 0x14) {
                goto yes;
            }
            if (y == 0x19 || y == 0x1B) {
                goto yes;
            }
            if (y == 0x1D || y == 0x1F) {
                goto yes;
            }
            break;
        }
    }
    return 0;
yes:
    return 1;
}
