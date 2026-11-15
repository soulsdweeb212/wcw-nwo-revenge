/* @header
 * func_800B50CC
 * VRAM 0x800B50CC | ROM 0x6183C | size 0x50
 * asm: asm/nonmatchings/code_80090000/func_800B50CC.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_800E9AA4 is the N64's label of D_800E8230[20].el, which has no PC symbol; the menus and their elements hold
 * addresses, so they are common.h's Nw2Menu and Nw2MenuEl, read by field name. p + k * 0x148 is element k; +0xA is
 * fA, +0x16 f16, +0x20 f20 and +0x22 f22. */
extern Nw2Menu D_800E8230[];

void func_800B50CC(void) {
    Nw2MenuEl *p = D_800E8230[20].el;
    s32 i;
    p[0].f16 = 0;
    p[0].f20 = 0x1000;
    p[0].f22 = 0;
    p[9].f16 = 0;
    for (i = 1; i < 9; i++) {
        p[i].fA |= 0x20;
    }
}
#else
typedef struct { u8 p[0xA]; u16 f; u8 q[0x13C]; } P;
extern u8 *D_800E9AA4;

void func_800B50CC(void) {
    u8 **pp = &D_800E9AA4;
    u8 *p = *pp;
    u16 *q;
    s32 i;
    p[0x16] = 0;
    *(s16 *)(p + 0x20) = 0x1000;
    *(s16 *)(p + 0x22) = 0;
    p[0xB9E] = 0;
    q = (u16 *)(*pp + 0x152);
    for (i = 1; i < 9; i++) {
        *q |= 0x20;
        q += 0xA4;
    }
}
#endif
