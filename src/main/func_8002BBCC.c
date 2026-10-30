/* @header
 * func_8002BBCC
 * VRAM 0x8002BBCC | ROM 0x2C7CC | size 0x70
 * asm: asm/nonmatchings/main/func_8002BBCC.s
 */
#include "common.h"

s32 func_8002B7E0(s32, s32);
void func_80021C40(void *, void *, s32);

/* Copies the four 0x2A-byte name variants (0x18- and 0xA-byte halves) of the
 * group arg0 into consecutive records. */
void func_8002BBCC(s32 arg0) {
    u8 *base = (u8 *)func_8002B7E0(arg0, 0);
    s32 i;
    u8 *p;
    i = 1;
    p = base + 0x2A;
    for (; i < 4; i++) {
        func_80021C40(base, p, 0x18);
        func_80021C40(base + 0x19, p + 0x19, 0xA);
        p += 0x2A;
    }
}
