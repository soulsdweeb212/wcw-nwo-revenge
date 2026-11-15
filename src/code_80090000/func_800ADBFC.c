/* @header
 * func_800ADBFC
 * VRAM 0x800ADBFC | ROM 0x5A36C | size 0x184
 * asm: asm/nonmatchings/code_80090000/func_800ADBFC.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the menus D_800E8230 and their elements hold addresses, so they are common.h's Nw2Menu and Nw2MenuEl, read by
 * field name; the N64's labels inside the menus have no PC symbol: D_800E85D8 is D_800E8230[3], D_800E85EC its el,
 * D_800E9AA4 D_800E8230[20].el. p + k * 0x148 is element k; +0xA is fA, +0x20 f20, +8 f8 and +0x16 f16. */
extern Nw2Menu D_800E8230[];
extern u8 D_8007EF30[];
#else
extern u8 *D_800E85EC, *D_800E9AA4[];
extern u8 D_8007EF30[], D_800E85D8[];
#endif
extern s32 D_800D5F1C;
#ifdef TARGET_PC
/* PC: the functions this file calls, declared with their definitions' types (func_800ADD80.c, func_800B5300.c,
 * func_800AD970.c, whose parameter is a record type of its own file); C99 has no implicit declarations. */
s32 func_800ADD80(s32 a);
void func_800B5300(s32 id);
void func_800AD970(void *a);
#endif

s32 func_800ADBFC(void) {
#ifdef TARGET_PC
    Nw2MenuEl *p = D_800E8230[3].el; /* PC: by name (see above) */
#else
    u8 *p = D_800E85EC;
#endif
    u16 f = *(u16 *)(D_8007EF30 + 8);
    s32 r = 3;
#ifndef TARGET_PC /* on PC the menu is D_800E8230[3], by name */
    u8 *q = D_800E85D8;
#endif
    s32 n, i;
    s32 id;

    if (f & 0x8000) {
        if (f & 0x10) {
            id = 0x16;
            n = 0;
        } else if (D_800D5F1C < 2) {
            id = 0x2A;
            n = 0;
        } else {
            id = 0x29;
            n = 2;
        }
    } else {
        switch (f & 0xF0) {
        case 0x20:
            id = 0x1E;
            n = 6;
            break;
        case 0x40:
            id = 0x18;
            n = 6;
            break;
        case 0x80:
            id = 0x24;
            n = 5;
            break;
        default:
            id = 0x15;
            n = 3;
            break;
        }
    }
#ifdef TARGET_PC
    /* PC: by name (see above) */
    if (n == 0) {
        p->f20 = id;
        D_800E8230[3].cur = 0;
        func_800ADD80(id);
        func_800B5300(0x40B);
        D_800E8230[20].el[3].f8 = -1;
        r = 0xD;
        D_800E8230[20].el[3].f16 = 0;
    } else {
        for (i = 0; i < n; i++, id++, p++) {
            p->fA &= 0xFFBE;
            p->f20 = id;
        }
        for (; n < 6; n++) {
            p->fA |= 1;
            p++;
        }
        D_800E8230[3].cur = 0;
        func_800AD970(&D_800E8230[3]);
    }
#else
    if (n == 0) {
        *(s16 *)(p + 0x20) = id;
        *(s16 *)(q + 4) = 0;
        func_800ADD80(id);
        func_800B5300(0x40B);
        *(s16 *)(D_800E9AA4[0] + 0x3E0) = -1;
        r = 0xD;
        D_800E9AA4[0][0x3EE] = 0;
    } else {
        for (i = 0; i < n; i++, id++, p += 0x148) {
            *(u16 *)(p + 0xA) &= 0xFFBE;
            *(s16 *)(p + 0x20) = id;
        }
        for (; n < 6; n++) {
            *(u16 *)(p + 0xA) |= 1;
            p += 0x148;
        }
        *(s16 *)(q + 4) = 0;
        func_800AD970(q);
    }
#endif
    return r;
}
