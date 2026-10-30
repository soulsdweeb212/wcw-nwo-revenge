/* @header
 * func_80028F3C
 * VRAM 0x80028F3C | ROM 0x29B3C | size 0x284
 * asm: asm/nonmatchings/main/func_80028F3C.s
 */
#include "common.h"

s32 func_80028E28(u8 *, s32);

typedef struct {
    u8 *f0;
    s32 f4;
    s32 f8;
    s16 fC;
    u16 fE;
    u16 f10;
} Nw2Str28F3C;

void func_80028F3C(Nw2Str28F3C *arg0, s32 arg1) {
    volatile unsigned long long pad;
    u8 *str;
    s32 max;
    s32 sum;
    s32 height;
    u16 mask;
    s32 enabled;
    u8 c;

    str = arg0->f0;
    max = 0;
    sum = 0;
    height = 0xE;
    if (arg1 & 0x8000) {
        height = 0x18;
    }
    mask = arg1 & 0x40;
    enabled = mask == 0;
    while ((c = *str) != 0) {
        switch (c) {
        case 0xA:
            if (enabled) {
                sum = 0;
                if (arg1 & 0x8000) {
                    height += 0x18;
                } else {
                    height += 0xE;
                }
            }
            str += 1;
            break;
        case 0x3C:
            if (mask) {
                enabled = 1;
            }
            str += 1;
            break;
        case 0x3E:
            enabled &= -(mask == 0);
            str += 1;
            break;
        case 0x7B:
            enabled = mask != 0;
            str += 1;
            break;
        case 0x7D:
            enabled = mask == 0;
            str += 1;
            break;
        case 0x23:
            if (enabled) {
                u8 d = str[1];
                s32 v;
                if (d >= '0' && d <= '9') {
                    v = d - '0';
                } else if (d >= 'a' && d <= 'z') {
                    v = d - 'a' + 10;
                } else if (d >= 'A' && d <= 'Z') {
                    v = d - 'A' + 10;
                } else {
                    v = 0;
                }
                sum += v;
            }
            str += 2;
            break;
        case 0x40:
            str += 2;
            break;
        default:
            if (enabled) {
                sum += func_80028E28(str, arg1);
            }
            str += 1;
            break;
        }
        if (max < sum) {
            max = sum;
        }
    }
    arg0->fE = height + 1;
    arg0->f10 = max + 1;
    if (arg1 & 4) {
        arg0->f10 = max + 2;
    }
    if (arg1 & 8) {
        arg0->f10 = arg0->f10 + 1;
    }
    if (arg1 & 1) {
        s32 t = (s16)arg0->f10;
        if (arg1 & 0x8000) {
            arg0->f10 = t + 0x10;
        } else {
            arg0->f10 = t + 8;
        }
    }
    if (arg1 & 2) {
        arg0->f10 = arg0->f10 + 0x10;
        arg0->fE = arg0->fE + 0x10;
    }
    {
        s16 t = (arg0->f10 + 0x11) & ~0xF;
        arg0->fC = t;
        arg0->f8 = (t * (s16)arg0->fE) >> 1;
    }
}
