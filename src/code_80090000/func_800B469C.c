/* @header
 * func_800B469C
 * VRAM 0x800B469C | ROM 0x60E0C | size 0x230
 * asm: asm/nonmatchings/code_80090000/func_800B469C.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the menus D_800E8230 and their elements hold addresses, so they are common.h's Nw2Menu and Nw2MenuEl, read by
 * field name; the N64's labels inside the menus have no PC symbol: D_800E948C and D_800E95C4 are D_800E8230[15].el
 * and [16].el, D_800E9AA4 is [20].el, D_800E947C and D_800E95B4 the cur of menus 15 and 16. p + k * 0x148 is
 * element k; +8 is f8, +0xA fA, +0x20 f20 and +0x22 f22 (R's a and b). */
extern Nw2Menu D_800E8230[];
extern u16 D_800EA0C2;
extern s32 D_800EA0B8;
extern u8 D_8007EF30[];
s32 func_800B2F94(s32);
s32 func_800B39C0(void);
s32 func_800B43C0(s32);
s32 func_800B4A24(void);
void func_800B5704(s32);

s32 func_800B469C(void) {
    Nw2MenuEl *p = D_800E8230[15].el;
    s32 r = -1;
    u32 a, k;
    s32 f, i, o;
    Nw2MenuEl *e;
    u16 v;
    Nw2MenuEl *q;

    a = (u16)p[10].f22;
    k = a >> 8;
    e = &p[10];
    if (k < 0xA) {
        if (D_800EA0C2 & 0x8000) {
            a = 0x900;
        }
        p[10].f22 = func_800B2F94(a);
    } else if (k == 0xA) {
        p[10].f22 = func_800B39C0();
    } else if (k == 0xB) {
        o = 1;
        f = -1;
        q = &D_800E8230[20].el[5];
        for (i = 5; i < 9; i++) {
            if (q->f8 != 0) {
                f = 0;
            } else {
                q->f22 = o;
            }
            q++;
        }
        if (f && (D_800EA0C2 & 0x8000)) {
            q = &D_800E8230[20].el[5];
            for (i = 5; i < 9; i++) {
                if (q->f8 == 0) {
                    q->f22 = 0;
                }
                q++;
            }
            e->f22 = 0xC00;
        }
    } else if (k == 0xC) {
        v = func_800B43C0(a);
        p[10].f22 = v;
        if ((v >> 8) == 0xD) {
            D_800EA0B8 = 0;
            r = func_800B4A24();
            D_800E8230[16].el[13].fA &= ~1;
            if (*(u16 *)(D_8007EF30 + 8) & 0x8000) {
                D_800E8230[16].el[13].f20 = 0x98;
            } else {
                D_800E8230[16].el[13].f20 = 0x9A;
                D_800E8230[16].el[12].fA &= ~1;
            }
            D_800E8230[16].cur = 0xD;
            func_800B5704(-1);
        }
    } else {
        D_800E8230[15].el[20].fA &= ~1;
        if (*(u16 *)(D_8007EF30 + 8) & 0x8000) {
            D_800E8230[15].el[20].f20 = 0x98;
        } else {
            D_800E8230[15].el[20].f20 = 0x9A;
            D_800E8230[15].el[19].fA &= ~1;
        }
        D_800E8230[15].cur = 0x14;
    }
    return r;
}
#else
typedef struct { u8 p0[8]; s16 a; u8 p1[0x18]; s16 b; u8 p2[0x124]; } R;
extern u8 *D_800E948C[], *D_800E95C4[];
extern R *D_800E9AA4;
extern u16 D_800EA0C2;
extern s16 D_800E95B4, D_800E947C;
extern s32 D_800EA0B8;
extern u8 D_8007EF30[];
s32 func_800B2F94(s32);
s32 func_800B39C0(void);
s32 func_800B43C0(s32);
s32 func_800B4A24(void);
void func_800B5704(s32);

s32 func_800B469C(void) {
    u8 *p = D_800E948C[0];
    s32 r = -1;
    u32 a, k;
    s32 f, i, o;
    u8 *e;
    u16 v;
    s16 *q;

    a = *(u16 *)(p + 0xCF2);
    k = a >> 8;
    e = p + 0xCD0;
    if (k < 0xA) {
        if (D_800EA0C2 & 0x8000) {
            a = 0x900;
        }
        *(u16 *)(p + 0xCF2) = func_800B2F94(a);
    } else if (k == 0xA) {
        *(u16 *)(p + 0xCF2) = func_800B39C0();
    } else if (k == 0xB) {
        o = 1;
        f = -1;
        q = &D_800E9AA4[5].b;
        for (i = 5; i < 9; i++) {
            if (q[-0xD] != 0) {
                f = 0;
            } else {
                *q = o;
            }
            q += 0xA4;
        }
        if (f && (D_800EA0C2 & 0x8000)) {
            q = &D_800E9AA4[5].b;
            for (i = 5; i < 9; i++) {
                if (q[-0xD] == 0) {
                    *q = 0;
                }
                q += 0xA4;
            }
            *(u16 *)(e + 0x22) = 0xC00;
        }
    } else if (k == 0xC) {
        v = func_800B43C0(a);
        *(u16 *)(p + 0xCF2) = v;
        if ((v >> 8) == 0xD) {
            D_800EA0B8 = 0;
            r = func_800B4A24();
            *(u16 *)(D_800E95C4[0] + 0x10B2) &= ~1;
            if (*(u16 *)(D_8007EF30 + 8) & 0x8000) {
                *(u16 *)(D_800E95C4[0] + 0x10C8) = 0x98;
            } else {
                *(u16 *)(D_800E95C4[0] + 0x10C8) = 0x9A;
                *(u16 *)(D_800E95C4[0] + 0xF6A) &= ~1;
            }
            D_800E95B4 = 0xD;
            func_800B5704(-1);
        }
    } else {
        *(u16 *)(D_800E948C[0] + 0x19AA) &= ~1;
        if (*(u16 *)(D_8007EF30 + 8) & 0x8000) {
            *(u16 *)(D_800E948C[0] + 0x19C0) = 0x98;
        } else {
            *(u16 *)(D_800E948C[0] + 0x19C0) = 0x9A;
            *(u16 *)(D_800E948C[0] + 0x1862) &= ~1;
        }
        D_800E947C = 0x14;
    }
    return r;
}
#endif
