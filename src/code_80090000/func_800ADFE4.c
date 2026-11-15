/* @header
 * func_800ADFE4
 * VRAM 0x800ADFE4 | ROM 0x5A754 | size 0xDC
 * asm: asm/nonmatchings/code_80090000/func_800ADFE4.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: T is two menu elements (0x290 bytes on the N64), which hold addresses, so on PC it is two of common.h's
 * Nw2MenuEl, whose fields T's follow (the asserts check). D_800E8D3C is D_800E8230[9].el, and D_800E8D2C
 * D_800E8230[9].cur: the labels have no PC symbol, and the PC reads the menu (common.h's Nw2Menu) by field name. */
typedef struct { u8 pad0[0xC]; s8 c; u8 d; u8 e; u8 padF; s16 h; u8 pad12[2 * sizeof(Nw2MenuEl) - 0x12]; } T;
_Static_assert(offsetof(T, c) == offsetof(Nw2MenuEl, fC) && offsetof(T, d) == offsetof(Nw2MenuEl, fD) &&
                   offsetof(T, e) == offsetof(Nw2MenuEl, fE) && offsetof(T, h) == offsetof(Nw2MenuEl, f10) &&
                   sizeof(T) == 2 * sizeof(Nw2MenuEl),
               "T must be two of common.h's Nw2MenuEl");
extern Nw2Menu D_800E8230[];
#else
typedef struct { u8 pad0[0xC]; s8 c; u8 d; u8 e; u8 padF; s16 h; u8 pad12[0x290 - 0x12]; } T;
extern T *D_800E8D3C;
#endif
extern u8 D_8007E8C0[], D_8007EF30[];
extern s32 D_800EA0B8;
#ifndef TARGET_PC /* on PC, D_800E8230[9].cur (see above) */
extern s16 D_800E8D2C;
#endif
s16 func_800A06F8(T *, s32);

void func_800ADFE4(void) {
#ifdef TARGET_PC
    T *p = (T *)D_800E8230[9].el; /* PC: by name (see above) */
#else
    T *p = D_800E8D3C;
#endif
    s32 i;
    p[0].e = D_8007E8C0[0x66D];
    p[2].e = D_8007E8C0[0x66E];
    p[1].e = D_8007E8C0[0x66F];
    p[3].e = D_8007EF30[0];
    p[4].e = D_8007EF30[3];
    p[5].e = D_8007EF30[1];
    p[6].e = D_8007EF30[2];
#ifdef TARGET_PC
    for (i = 0, p = (T *)D_800E8230[9].el; i < 8; i++, p++) {
#else
    for (i = 0, p = D_800E8D3C; i < 8; i++, p++) {
#endif
        u8 e = p->e;
        p->c = e;
        p->d = e;
        p->h = func_800A06F8(p, p->c);
    }
    D_800EA0B8 = 0;
#ifdef TARGET_PC
    D_800E8230[9].cur = 0x10; /* PC: by name (see above) */
#else
    D_800E8D2C = 0x10;
#endif
}
