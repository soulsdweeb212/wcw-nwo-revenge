/* @header
 * func_800B511C
 * VRAM 0x800B511C | ROM 0x6188C | size 0x90
 * asm: asm/nonmatchings/code_80090000/func_800B511C.s
 */
#include "common.h"


extern u8 *D_800E9AA4;
extern u8 D_8007EF30[];
#define W(o) (*(s16 *)(D_8007EF30 + (o)))

void func_800B511C(s32 a) {
    u8 *p = D_800E9AA4;
    s32 x;
    s32 v;
    if (a < 5) {
        if (a < 2) {
            if (a != 1) {
                goto zero;
            }
            x = 0x90;
        } else {
            x = 0x150;
        }
        W(0x24) = x;
        W(0x26) = 0xC0;
    } else {
zero:
        W(0x24) = 0;
        W(0x26) = 0;
    }
    switch (a) {
    case 3:
        v = 0x1002;
        break;
    case 4:
        v = 0x1001;
        break;
    default:
        v = 0x1000;
        break;
    }
    W(0x28) = v;
    *(s16 *)(p + 0x22) = 0xFF;
}
