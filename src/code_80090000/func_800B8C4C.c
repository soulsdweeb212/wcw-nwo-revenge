/* @header
 * func_800B8C4C
 * VRAM 0x800B8C4C | ROM 0x653BC | size 0x5DC
 * asm: asm/nonmatchings/code_80090000/func_800B8C4C.s
 */
#include "common.h"




extern u8 *D_800DCFB8;
extern u8 D_8007EF30[], D_8007E8C0[];
extern u8 D_8003A486[], D_8003A488[], D_8003A4AF, D_8003A4B1;
extern u8 D_800CCAFC[];
u16 func_8002B528(s32);
void func_800A8EF0(s32);
void func_800A8F60(u8 *);
void func_8002BAB8(void);
u8 *func_8002B790(s32, s32);
void func_80021C40(void *, void *, s32);
void func_800B9228(u8 *, s32);
u8 *func_800B4BC8(s32);
void func_80021F60(void *, s32);

#define OPTS() ((D_8007EF30[0x1A0] & 7) | ((D_8007EF30[0x1A2] & 1) << 3) | ((D_8007EF30[0x1A3] & 1) << 4) | \
    ((D_8007EF30[0x1A4] & 1) << 5) | ((D_8007EF30[0x1A5] & 1) << 6) | ((D_8007EF30[0x1A1] & 7) << 7) | \
    ((D_8007EF30[0x1A6] & 1) << 10) | ((D_8007EF30[0x1A7] & 1) << 11) | ((D_8007EF30[0x1A8] & 1) << 12) | \
    ((D_8007EF30[0x1A9] & 1) << 13))

void func_800B8C4C(s32 mode) {
    s32 i, j, k, m, n;
    s32 pad[4]; /* unused 16 bytes of frame */
    u8 *q, *e, *p, *r, *s, *d;

    switch (mode) {
    case 0:
        D_800DCFB8[1] = 0;
        D_800DCFB8[0] = 0;
        for (i = 0, m = 0; i < 5; i++, m += 20) {
            *(u16 *)(D_800DCFB8 + i * 2 + 2) = func_8002B528(D_8003A486[m]);
            /* `i << 1` (not `i * 2`) keeps D_800DCFB8 as the first addu operand */
            *(u16 *)(D_800DCFB8 + (i << 1) + 0xE) = func_8002B528(D_8003A488[m]);
        }
        *(u16 *)(D_800DCFB8 + 0xC) = func_8002B528(D_8003A4AF);
        *(u16 *)(D_800DCFB8 + 0x18) = func_8002B528(D_8003A4B1);
        func_800A8EF0(0);
        *(u16 *)(D_800DCFB8 + 0x1A) = OPTS();
        *(u16 *)(D_800DCFB8 + 0x1C) = D_8007EF30[0x1AA] & 7;
        func_800A8EF0(1);
        *(u16 *)(D_800DCFB8 + 0x1E) = OPTS();
        *(u16 *)(D_800DCFB8 + 0x20) = D_8007EF30[0x1AA] & 7;
        for (i = 0; i < 8; i++) {
            D_8007E8C0[0x66D + i] = D_800CCAFC[i];
        }
        q = D_8007E8C0 + 0x48;
        *(u16 *)(D_800DCFB8 + 0x3A) = (D_8007E8C0[0x66D] & 3) | ((D_8007E8C0[0x66E] & 1) << 2) | ((D_8007E8C0[0x66F] & 1) << 3) | ((D_8007EF30[0] & 1) << 4) | ((D_8007EF30[3] & 1) << 5) | ((D_8007EF30[1] & 1) << 6) | ((D_8007EF30[2] & 1) << 7) | ((D_8007EF30[4] & 7) << 8);
        func_800A8F60(q);
        func_800A8F60(q + 9);
        func_800A8F60(q + 0x12);
        func_800A8F60(q + 0x1B);
        r = D_800DCFB8;
        for (i = 0, n = 0x22; i < 4; n += 6, i++) {
            /* w set twice in the loop, so loop.c leaves r + n unreduced */
            u16 *w = (u16 *)(r + n);
            *w++ = (q[0] & 0xF) | ((q[1] & 0xF) << 4) | ((q[2] & 0xF) << 8) | ((q[3] & 0xF) << 12);
            *w = (q[4] & 0xF) | ((q[5] & 0xF) << 4) | ((q[6] & 0xF) << 8) | ((q[7] & 0xF) << 12);
        }
        break;
    case 2:
        func_8002BAB8();
        for (i = 0; i < 0x40; i++) {
            for (j = 0; j < 4; j++) {
                p = D_800DCFB8 + 0x600 + i * 0x9C + j * 0x26;
                d = func_8002B790(i, j);
                func_80021C40(d, p, 0x18);
                func_80021C40(d + 0x19, p + 0x18, 0xA);
                p[0x22] = d[0x24];
                p[0x23] = d[0x25];
                *(u16 *)(p + 0x24) = (d[0x27] & 0x1F) | ((d[0x28] & 0x1F) << 5);
            }
            func_800B9228(D_800DCFB8 + 0x600 + i * 0x9C, 0x98);
        }
        break;
    case 1:
        s = D_800DCFB8 + 0x40;
        for (k = 0; k < 9; k++) {
            for (j = 0; j < 10; j++) {
                e = func_800B4BC8((k << 4) | j);
                *(u32 *)s = *(u32 *)e;
                *(u16 *)(s + 4) = *(u16 *)(e + 4);
                *(u16 *)(s + 0xA) = *(u16 *)(e + 0xA);
                func_80021C40(e + 6, s + 6, 3);
                func_80021C40(e + 0xC, s + 0xC, 3);
                s += 0x10;
            }
        }
        break;
    case 3:
        func_80021F60(D_800DCFB8 + 0x2D20, 0x40);
        break;
    }
}
