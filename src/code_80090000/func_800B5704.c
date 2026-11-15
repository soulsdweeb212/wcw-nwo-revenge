/* @header
 * func_800B5704
 * VRAM 0x800B5704 | ROM 0x61E74 | size 0x1E8
 * asm: asm/nonmatchings/code_80090000/func_800B5704.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the menus D_800E8230 and their elements hold addresses, so they are common.h's Nw2Menu and Nw2MenuEl, read by
 * field name; the N64's labels inside the menus have no PC symbol: D_800E9AA4 is D_800E8230[20].el, D_800E837C and
 * D_800E836C are [1].el and [1].cur, D_800E85EC and D_800E85DC [3]'s, D_800E8724 and D_800E8714 [4]'s, D_800E885C
 * and D_800E884C [5]'s, D_800E8994 and D_800E8984 [6]'s, D_800E8D3C and D_800E8D2C [9]'s, D_800E996C [19].el. E's
 * f is an element's fA; the N64 counts the loop of case -1 in a (a pointer), the PC in i. */
extern Nw2Menu D_800E8230[];

void func_800B5704(s32 x) {
    Nw2MenuEl *a = 0;
    Nw2MenuEl *b = 0;
    s32 i;

    switch (x) {
    case 1:
        a = &D_800E8230[20].el[1];
        b = &D_800E8230[1].el[D_800E8230[1].cur];
        break;
    case 5:
        a = &D_800E8230[20].el[2];
        b = &D_800E8230[5].el[D_800E8230[5].cur];
        break;
    case 6:
        a = &D_800E8230[20].el[2];
        b = &D_800E8230[6].el[D_800E8230[6].cur];
        break;
    case 4:
        a = &D_800E8230[20].el[2];
        b = &D_800E8230[4].el[D_800E8230[4].cur];
        break;
    case 3:
        b = &D_800E8230[3].el[D_800E8230[3].cur];
        /* fall through - into case 2, which sets a, as on the N64 */
    case 2:
        a = &D_800E8230[20].el[3];
        break;
    case 19:
        a = &D_800E8230[20].el[4];
        D_800E8230[19].el[1].fA &= ~1;
        b = &D_800E8230[19].el[3];
        break;
    case 9:
        switch (D_800E8230[9].cur) {
        case 0xE:
            a = &D_800E8230[20].el[4];
            b = &D_800E8230[9].el[14];
            break;
        case 0xF:
            a = &D_800E8230[20].el[4];
            b = &D_800E8230[9].el[15];
            break;
        }
        break;
    case -1:
        for (i = 1; i < 9; i++) {
            D_800E8230[20].el[i].fA |= 0x20;
        }
        a = 0;
        break;
    }
    if (a) {
        a->fA |= 0x20;
    }
    if (b) {
        b->fA &= ~1;
    }
}
#else
typedef struct { u8 pad[0xA]; u16 f; u8 pad2[0x13C]; } E;
extern E *D_800E9AA4, *D_800E837C, *D_800E885C, *D_800E8994, *D_800E8724, *D_800E85EC, *D_800E8D3C;
extern E *D_800E996C[];
extern s16 D_800E836C, D_800E884C, D_800E8984, D_800E8714, D_800E85DC, D_800E8D2C;

void func_800B5704(s32 x) {
    E *a = 0;
    E *b = 0;
    u16 *q;

    switch (x) {
    case 1:
        a = &D_800E9AA4[1];
        b = &D_800E837C[D_800E836C];
        break;
    case 5:
        a = &D_800E9AA4[2];
        b = &D_800E885C[D_800E884C];
        break;
    case 6:
        a = &D_800E9AA4[2];
        b = &D_800E8994[D_800E8984];
        break;
    case 4:
        a = &D_800E9AA4[2];
        b = &D_800E8724[D_800E8714];
        break;
    case 3:
        b = &D_800E85EC[D_800E85DC];
    case 2:
        a = &D_800E9AA4[3];
        break;
    case 19:
        a = &D_800E9AA4[4];
        *(u16 *)((u8 *)D_800E996C[0] + 0x152) &= ~1;
        b = &D_800E996C[0][3];
        break;
    case 9:
        switch (D_800E8D2C) {
        case 0xE:
            a = &D_800E9AA4[4];
            b = &D_800E8D3C[14];
            break;
        case 0xF:
            a = &D_800E9AA4[4];
            b = &D_800E8D3C[15];
            break;
        }
        break;
    case -1:
        q = &D_800E9AA4[1].f;
        for (a = (E *)1; (s32)a < 9; a = (E *)((s32)a + 1), q += 0xA4) {
            *q |= 0x20;
        }
        a = 0;
        break;
    }
    if (a) {
        a->f |= 0x20;
    }
    if (b) {
        b->f &= ~1;
    }
}
#endif
