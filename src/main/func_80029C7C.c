/* @header
 * func_80029C7C
 * VRAM 0x80029C7C | ROM 0x2A87C | size 0x218
 * asm: asm/nonmatchings/main/func_80029C7C.s
 */
#include "common.h"

void func_80021F60(void *, s32);
s32 func_80028E28(u8 *, u16);

s32 func_80029C7C(u8 *str, s32 arg1, s32 *out, s32 count)
{
    u16 mask;
    s32 enabled;
    s32 neg;
    s32 row;
    s32 index;
    s32 sum;
    s32 width;
    s32 step;
    u8 c;
    u16 f;

    f = arg1;
    func_80021F60(out, count * 4);
    row = 0;
    index = 0;
    sum = 0;
    mask = arg1 & 0x40;
    enabled = mask == 0;
    neg = -enabled;

    for (;;) {
        c = *str;
        width = 4;
        switch (c) {
        case 0x0A:
            row++;
            if (enabled) {
                width = 0;
                sum = 0;
            }
            step = 1;
            break;
        case 0x3C:
            if (mask) enabled = 1;
            step = 1;
            break;
        case 0x3E:
            enabled &= neg;
            step = 1;
            break;
        case 0x7B:
            enabled = mask != 0;
            step = 1;
            break;
        case 0x7D:
            enabled = mask == 0;
            step = 1;
            break;
        case 0x23:
            if (enabled) {
                u8 d = str[1];
                if (d >= '0' && d <= '9') width = d - '0';
                else if (d >= 'a' && d <= 'z') width = d - 'a' + 10;
                else if (d >= 'A' && d <= 'Z') width = d - 'A' + 10;
                else width = 0;
            }
            step = 2;
            break;
        case 0x40:
            width = 0;
            step = 2;
            break;
        default:
            if (enabled) width = func_80028E28(str, f);
            step = 1;
            break;
        }
        out[index] = (sum & 0xFFFF) | (row << 24) | ((width & 0xFF) << 16);
        if (index < count && *str != 0) {
            if (step == 1) out[index + 1] = (sum & 0xFFFF) | (row << 24);
            str += step;
            index += step;
            sum += width;
        } else {
            return (sum & 0xFFFF) | (width << 16);
        }
    }
}
