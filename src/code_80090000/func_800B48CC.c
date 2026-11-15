/* @header
 * func_800B48CC
 * VRAM 0x800B48CC | ROM 0x6103C | size 0x158
 * asm: asm/nonmatchings/code_80090000/func_800B48CC.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the menus and their elements hold addresses, so they are common.h's Nw2Menu and Nw2MenuEl, which N follows (the
 * assert checks). D_800E95C4 and D_800E95B4 are the el and cur of D_800E8230[16], D_800E96FC and D_800E96EC those of
 * [17]: the labels have no PC symbol, and the PC reads the menus by field name. */
typedef struct { u8 pad[0xA]; u16 f; u8 pad2[0x14]; u16 x; u16 y; u8 pad3[sizeof(Nw2MenuEl) - 0x24]; } N;
_Static_assert(offsetof(N, f) == offsetof(Nw2MenuEl, fA) && offsetof(N, x) == offsetof(Nw2MenuEl, f20) &&
                   offsetof(N, y) == offsetof(Nw2MenuEl, f22) && sizeof(N) == sizeof(Nw2MenuEl),
               "N must follow common.h's Nw2MenuEl");
extern Nw2Menu D_800E8230[];
extern s16 D_80038A90;
#else
typedef struct { u8 pad[0xA]; u16 f; u8 pad2[0x14]; u16 x; u16 y; u8 pad3[0x124]; } N;
extern N *D_800E96FC, *D_800E95C4;
extern s16 D_80038A90, D_800E95B4, D_800E96EC;
#endif
extern u8 D_800EA0D8[];
extern u16 D_800CD24C[];
s32 func_800BA940(void *, s32);

s32 func_800B48CC(s32 k) {
    N *p;
    s32 t, c, i;
    u16 v;
    if (D_80038A90 == 0x10) {
#ifdef TARGET_PC
        p = (N *)D_800E8230[17].el; /* PC: by name (see above) */
#else
        p = D_800E96FC;
#endif
        t = 0;
        c = 0;
    } else {
#ifdef TARGET_PC
        p = (N *)D_800E8230[16].el; /* PC: by name (see above) */
#else
        p = D_800E95C4;
#endif
        t = 1;
        c = 0x10;
    }
    if (k == 1 || k == 4) {
        c |= 0x80;
    } else if (k == 7) {
        c |= 0x80;
    }
    for (i = 0; i < 10; i++, p++) {
        p->x = (i + 0x7601) | c;
        p->y = 0;
        p->f &= 0xFFDF;
    }
    func_800BA940(D_800EA0D8 + t * 0xA0, (k << 4) | 0xF);
    p->x = D_800CD24C[k * 2];
    p->f &= 0xFFDF;
    p++;
    v = D_800CD24C[k * 2 + 1];
    p->f &= 0xFFDF;
    p->x = v;
#ifdef TARGET_PC
    if (D_80038A90 == 0x10) { /* PC: by name (see above) */
        D_800E8230[17].cur = 10;
        return 0x11;
    }
    D_800E8230[16].cur = 10;
#else
    if (D_80038A90 == 0x10) {
        D_800E96EC = 10;
        return 0x11;
    }
    D_800E95B4 = 10;
#endif
    return 0x10;
}
