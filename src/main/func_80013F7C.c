/* @header
 * func_80013F7C
 * VRAM 0x80013F7C | ROM 0x14B7C | size 0x88
 * asm: asm/nonmatchings/main/func_80013F7C.s
 */
#include "common.h"

extern s32 D_800604F0;
extern s32 D_800604F4;
extern u32 D_800604C8;
extern u8 *D_800604D0;
s32 func_8001381C(s32);

/* Sets the pan (clamped 0..0x7F) of every voice whose key matches arg0. Returns
 * the number updated. */
s32 func_80013F7C(s32 arg0, s32 arg1) {
    u32 i;
    s32 n;
    u8 *p;

    if (arg0 == 0) {
        return 0;
    }
    if (arg1 < 0) {
        arg1 = 0;
    } else if (arg1 >= 0x80) {
        arg1 = 0x7F;
    }
    n = 0;
    p = D_800604D0;
    for (i = 0; i < D_800604C8; i++) {
        if (*(s32 *)(p + 0x60) == arg0) {
            n++;
            p[0xEB] = arg1;
            p[0xEC] = 0xFF;
        }
        p += 0x158;
    }
    return n;
}
