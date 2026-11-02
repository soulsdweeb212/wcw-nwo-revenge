/* @header
 * func_800B29B4
 * VRAM 0x800B29B4 | ROM 0x5F124 | size 0x164
 * asm: asm/nonmatchings/code_80090000/func_800B29B4.s
 */
#include "common.h"

extern u8 D_8007EF30[];
#define M D_8007E848

s32 func_800B29B4(s32 a) {
    s32 r = 0;
    u16 f = *(u16 *)(D_8007EF30 + 8);
    if (f & 0x80) {
        if (a == 0 && (M & 1)) {
            r = 1000;
        } else if (a == 1 && (M & 2)) {
            r = 1000;
        } else if (a == 2 && (M & 4)) {
            r = 1000;
        } else if (a == 3 && (M & 8)) {
            r = 1000;
        }
    } else if (f & 0x20) {
        if (a == 1 && (M & 0x203)) {
            r = 1000;
        } else if (a == 3 && (M & 0x10C)) {
            r = 1000;
        }
    } else if (f & 0x40) {
        if (a == 1 && (M & 0x203)) {
            r = 1000;
        } else if (a == 2 && (M & 0x104)) {
            r = 3000;
        }
    } else {
        if (a == 0 && (M & 0x201)) {
            r = 1000;
        } else if (a == 1 && (M & 0x102)) {
            r = 1000;
        }
    }
    return r;
}
