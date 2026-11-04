/* @header
 * func_800AA38C
 * VRAM 0x800AA38C | ROM 0x56AFC | size 0xE8
 * asm: asm/nonmatchings/code_80090000/func_800AA38C.s
 */
#include "common.h"

extern u8 D_8007EF30[];
void func_80021C40(void *, void *, s32);

void func_800AA38C(s32 i, s32 j) {
    u8 t[16];
    u8 *p = D_8007EF30 + 8;
    u8 *a;
    u8 *b;
    s32 x, y;
    if (*(u16 *)p & 0x20) {
        u8 *q;
        x = i << 5;
        q = p + 0x44;
        a = x + q;
        y = j << 5;
        b = y + q;
        func_80021C40(a, t, 0x10);
        func_80021C40(b, a, 0x10);
        func_80021C40(t, b, 0x10);
        {
            u8 *r = p + 0x54;
            a = x + r;
            b = y + r;
        }
    } else {
        s32 k = i << 4;
        u8 *q = p + 0x44;
        a = k + q;
        b = (j << 4) + q;
    }
    func_80021C40(a, t, 0x10);
    func_80021C40(b, a, 0x10);
    func_80021C40(t, b, 0x10);
}
