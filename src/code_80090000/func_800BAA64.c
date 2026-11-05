/* @header
 * func_800BAA64
 * VRAM 0x800BAA64 | ROM 0x671D4 | size 0x15C
 * asm: asm/nonmatchings/code_80090000/func_800BAA64.s
 */
#include "common.h"

typedef struct { s32 a; u16 b; u8 c[4]; u16 d; u8 e[4]; } E;
extern u8 *D_800DCFB8;
extern u16 D_800D2908, D_800D290A;
extern s32 D_800DCFC4, D_800DCFBC, D_800DCFBC_alias;
void bcopy(void *, void *, s32);
s32 func_8000424C(void);
s32 func_800B9640(u16, u16);
void func_80004290(void);

s32 func_800BAA64(E *in, s32 id) {
    s32 lo = id & 0xF;
    s32 i, n, s;
    E *p;
    if (lo == 0xF) {
        s = 0;
        n = 10;
        p = (E *)(D_800DCFB8 + ((id >> 4) * 0xA0 + 0x40));
    } else {
        s = id;
        n = s + 1;
        p = (E *)(D_800DCFB8 + ((id >> 4) * 0xA0 + 0x40)) + lo;
    }
    for (i = s; i < n; i++, in++, p++) {
        p->a = in->a;
        p->b = in->b;
        p->d = in->d;
        bcopy(in->c, p->c, 3);
        bcopy(in->e, p->e, 3);
    }
    D_800DCFC4 = func_8000424C();
    D_800DCFBC = func_800B9640(D_800D2908, D_800D290A);
    func_80004290();
    D_800DCFBC = D_800DCFBC_alias;
    return 0;
}
