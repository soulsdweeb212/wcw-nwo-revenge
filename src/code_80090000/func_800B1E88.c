/* @header
 * func_800B1E88
 * VRAM 0x800B1E88 | ROM 0x5E5F8 | size 0x110
 * asm: asm/nonmatchings/code_80090000/func_800B1E88.s
 */
#include "common.h"

extern u8 *D_800E9834;
extern s32 D_800E7BF0, D_800E7BF4, D_800E7BF8, D_800E7BFC;
extern u8 D_8007E8C0[];
s32 func_80099694(u16, u16);
void func_8002A820(u8 *, s32);
void func_800B1E88(void) {
    u8 *p;
    u8 *q;
    u8 *buf;
    s32 k, n, i, c, r;
    p = (u8 *)func_80099694(*(u16 *)(D_800E9834 + 0x20), *(u16 *)(D_800E9834 + 0x22));
    r = D_800E7BF4;
    c = D_800E7BF0;
    k = c + r * 20;
    if (c >= 5) {
        k += 2;
    }
    if (c >= 10) {
        k += 2;
    }
    buf = D_8007E8C0 + 0x80;
    q = p + k;
    if (D_800E7BF8 == 0) {
        n = 0x18;
    } else if (D_800E7BF8 == 1) {
        n = 0xA;
    } else {
        n = 0x14;
    }
    func_8002A820(buf, 8);
    buf[D_800E7BFC] = *q;
    for (i = 0; i < n; i++) {
        if (buf[i] == 0) {
            break;
        }
    }
    {
        s32 *q = &D_800E7BFC;
        if (*q < n - 1) {
            *q += 1;
        }
    }
}
