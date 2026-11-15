/* @header
 * func_800B58EC
 * VRAM 0x800B58EC | ROM 0x6205C | size 0x1F4
 * asm: asm/nonmatchings/code_80090000/func_800B58EC.s
 */
#include "common.h"


#ifdef TARGET_PC
/* PC: D_800E9AA4 is the N64's label of D_800E8230[20].el, which has no PC symbol; the menus and their elements hold
 * addresses, so they are common.h's Nw2Menu and Nw2MenuEl, read by field name: p + 0xB88 is element 9 (E's a and b
 * are its f20 and f22, +0xB9E its f16). A is the element under the cursor, whose fields A names lie before the
 * element's first address, at the same offsets on both machines (the assert checks). */
typedef struct { f32 x; f32 y; u8 p0[0xE]; u8 c; u8 p1[0x9]; u16 k; } A;
_Static_assert(offsetof(A, y) == offsetof(Nw2MenuEl, y) && offsetof(A, c) == offsetof(Nw2MenuEl, f16) &&
                   offsetof(A, k) == offsetof(Nw2MenuEl, f20),
               "A must follow common.h's Nw2MenuEl");
extern Nw2Menu D_800E8230[];
extern s16 D_80038A90;
void func_800B51AC(void);

void func_800B58EC(A *a) {
    Nw2MenuEl *p = &D_800E8230[20].el[9];
    u16 x;

    func_800B51AC();
    if (a == 0) {
        return;
    }
    p->x = a->x;
    p->y = a->y;
    p->f16 = a->c;
    p->f22 = a->k;
    p->f20 = 0x1100;
    if (D_80038A90 == 0xA || D_80038A90 == 0xC || D_80038A90 == 0 || D_80038A90 == 0x16 || D_80038A90 == 0x17) {
        p->f20 = 0x1104;
        return;
    }
    if (D_80038A90 == 8) {
        p->f20 = 0x1105;
        return;
    }
    switch ((u16)p->f22 & 0xFF00) {
    case 0x7C00:
        p->f20 = 0xFFFF;
        return;
    case 0x5000:
        p->f20 = 0x1103;
        return;
    case 0x5A00:
    case 0x5B00:
    case 0x5C00:
        p->f20 = 0x1109;
        return;
    case 0x5900:
        p->f20 = 0x1108;
        return;
    case 0x6200:
        p->f20 = 0x1102;
        return;
    }
    x = p->f22;
    if (x == 0xFFFF || (x >= 0x63 && x < 0x6F)) {
        p->f20 = 0x1104;
    } else if (x >= 0x94 && x < 0x98) {
        p->f20 = 0x1106;
    } else if (x >= 0x98 && x < 0x9B) {
        p->f20 = 0x1107;
    } else if (x >= 0x3F && x < 0x5E) {
        p->f20 = 0x1102;
    } else if (x >= 0x2B && x < 0x3F) {
        p->f20 = 0x1101;
    }
}
#else
typedef struct { u8 p0[0x20]; u16 a; u16 b; } E;
typedef struct { f32 x; f32 y; u8 p0[0xE]; u8 c; u8 p1[0x9]; u16 k; } A;
extern u8 *D_800E9AA4;
extern s16 D_80038A90;
void func_800B51AC(void);

void func_800B58EC(A *a) {
    u8 *p = D_800E9AA4;
    E *e = (E *)(p + 0xB88);
    u16 x;

    func_800B51AC();
    if (a == 0) {
        return;
    }
    *(f32 *)(p + 0xB88) = a->x;
    *(f32 *)(p + 0xB8C) = a->y;
    p[0xB9E] = a->c;
    e->b = a->k;
    e->a = 0x1100;
    if (D_80038A90 == 0xA || D_80038A90 == 0xC || D_80038A90 == 0 || D_80038A90 == 0x16 || D_80038A90 == 0x17) {
        e->a = 0x1104;
        return;
    }
    if (D_80038A90 == 8) {
        *(u16 *)(p + 0xBA8) = 0x1105;
        return;
    }
    switch (e->b & 0xFF00) {
    case 0x7C00:
        *(u16 *)(p + 0xBA8) = 0xFFFF;
        return;
    case 0x5000:
        *(u16 *)(p + 0xBA8) = 0x1103;
        return;
    case 0x5A00:
    case 0x5B00:
    case 0x5C00:
        e->a = 0x1109;
        return;
    case 0x5900:
        *(u16 *)(p + 0xBA8) = 0x1108;
        return;
    case 0x6200:
        *(u16 *)(p + 0xBA8) = 0x1102;
        return;
    }
    x = e->b;
    if (x == 0xFFFF || (x >= 0x63 && x < 0x6F)) {
        e->a = 0x1104;
    } else if (x >= 0x94 && x < 0x98) {
        e->a = 0x1106;
    } else if (x >= 0x98 && x < 0x9B) {
        e->a = 0x1107;
    } else if (x >= 0x3F && x < 0x5E) {
        e->a = 0x1102;
    } else if (x >= 0x2B && x < 0x3F) {
        e->a = 0x1101;
    }
}
#endif
