/* @header
 * func_800C5718
 * VRAM 0x800C5718 | ROM 0x71E88 | size 0x234
 * asm: asm/nonmatchings/code_80090000/func_800C5718.s
 */
#include "common.h"

typedef struct { u8 *p; u16 a; u16 b; u8 c[4]; } P;
extern P D_8006E178[];
extern u8 D_800E7C18[][0x10];
extern u16 D_800EA0C8[], D_800EA0C0[], D_800EA0C2, D_800EA0C4;
extern s32 D_800E753C, D_800D5F1C;
extern u16 D_800E81E8;
extern P D_800EA0BC;
void func_80003E78(s32);
s32 func_800ABDDC(void);
void func_800C55B0(s32);
void bcopy(void *, void *, s32);

void func_800C5718(void) {
    s32 n, i, j;
    u8 *c;
    u8 v;
    s32 o, f;

    func_80003E78(1);
    n = func_800ABDDC();
    if (n != D_800E753C) {
        for (i = 0; i < 4; i++) {
            for (j = 0xF; j >= 0; j--) {
                D_800E7C18[i][j] = 0;
            }
        }
        D_800E753C = n;
    }
    i = 0;
    D_800D5F1C = 0;
    o = 1;
    f = 4;
    c = D_800E7C18[0];
    for (; i < 4; i++) {
        if (D_8006E178[i].p[3] == 0 && D_800D5F1C == i) {
            D_800D5F1C = i + 1;
        }
        D_800EA0C8[i] = 0;
        for (j = 0; j < 0x10; j++) {
            if ((D_8006E178[i].b >> j) & 1) {
                D_800EA0C8[i] |= o << j;
                c[j] = f;
            } else if ((D_8006E178[i].a >> j) & 1) {
                v = c[j];
                c[j] = v + 0xFF;
                if (v & 0x80) {
                    D_800EA0C8[i] |= o << j;
                    c[j] = o;
                }
            }
        }
        c += 0x10;
    }
    if (n >= 4) {
        func_800C55B0(n);
    } else {
        bcopy(&D_8006E178[n], &D_800EA0BC, 0xC);
        D_800EA0C4 = D_800EA0C8[n];
    }
    D_800E81E8 = 0;
    D_800EA0C0[0] |= D_8006E178[0].a;
    D_800EA0C2 |= D_8006E178[0].b;
    D_800EA0C4 |= D_800EA0C8[0];
}
