/* @header
 * func_800BA940
 * VRAM 0x800BA940 | ROM 0x670B0 | size 0x124
 * asm: asm/nonmatchings/code_80090000/func_800BA940.s
 */
#include "common.h"

typedef struct { s32 a; u16 b; u8 c[4]; u16 d; u8 e[4]; } E;
typedef struct { u8 pad[0x40]; E e[6]; } R;
extern u8 *D_800DCFB8;
void bcopy(void *, void *, s32);

s32 func_800BA940(E *out, s32 id) {
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
    for (i = s; i < n; i++, out++, p++) {
        out->a = p->a;
        out->b = p->b;
        out->d = p->d;
        bcopy(p->c, out->c, 3);
        bcopy(p->e, out->e, 3);
        out->c[3] = 0;
        out->e[3] = 0;
    }
    return 0;
}
