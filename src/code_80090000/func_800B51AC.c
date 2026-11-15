/* @header
 * func_800B51AC
 * VRAM 0x800B51AC | ROM 0x6191C | size 0x154
 * asm: asm/nonmatchings/code_80090000/func_800B51AC.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_800E9AA4 is the N64's label of D_800E8230[20].el, which has no PC symbol; the menus and their elements hold
 * addresses, so they are common.h's Nw2Menu and Nw2MenuEl, read by field name: P(0x10), P(0x12), P(0x20) and P(0x22)
 * are the element's f10, f12, f20 and f22 read as u16, Q(0x12) its f12. */
extern Nw2Menu D_800E8230[];
extern u8 D_8007EF30[];
#define W(o) (*(u16 *)(D_8007EF30 + (o)))

void func_800B51AC(void) {
    Nw2MenuEl *p = D_800E8230[20].el;
    u16 c = p->f10;
    s32 tx = W(0x24);
    s32 ty = W(0x26);
    s32 x = (c & 0xFF) * 8;
    s32 y = (c >> 8) * 8;
    s32 t;
    if (x != tx || y != ty) {
        p->f12 += 8;
        if (x < tx) {
            x += p->f12;
            if (x > tx) {
                x = tx;
            }
        } else if (x > tx) {
            x -= p->f12;
            if (x < tx) {
                x = tx;
            }
        }
        if (y < ty) {
            y += p->f12;
            if (y > ty) {
                y = ty;
            }
        } else if (y > ty) {
            y -= p->f12;
            if (y < ty) {
                y = ty;
            }
        }
        if (p->f22 != 0) {
            t = (u16)p->f22 - p->f12;
            if (t <= 0) {
                t = 0;
            }
            p->f22 = t;
        }
        if (x == tx && y == ty) {
            p->f12 = 0;
            p->f22 = 0;
            p->f20 = W(0x28);
        }
        p->f10 = ((x / 8) & 0xFF) | (((y / 8) & 0xFF) << 8);
    }
}
#else
extern u8 *D_800E9AA4;
extern u8 D_8007EF30[];
#define W(o) (*(u16 *)(D_8007EF30 + (o)))
#define P(o) (*(u16 *)(p + (o)))
#define Q(o) (*(s16 *)(p + (o)))

void func_800B51AC(void) {
    u8 *p = D_800E9AA4;
    u16 c = P(0x10);
    s32 tx = W(0x24);
    s32 ty = W(0x26);
    s32 x = (c & 0xFF) * 8;
    s32 y = (c >> 8) * 8;
    s32 t;
    if (x != tx || y != ty) {
        P(0x12) += 8;
        if (x < tx) {
            x += Q(0x12);
            if (x > tx) {
                x = tx;
            }
        } else if (x > tx) {
            x -= Q(0x12);
            if (x < tx) {
                x = tx;
            }
        }
        if (y < ty) {
            y += Q(0x12);
            if (y > ty) {
                y = ty;
            }
        } else if (y > ty) {
            y -= Q(0x12);
            if (y < ty) {
                y = ty;
            }
        }
        if (P(0x22) != 0) {
            t = P(0x22) - Q(0x12);
            if (t <= 0) {
                t = 0;
            }
            P(0x22) = t;
        }
        if (x == tx && y == ty) {
            P(0x12) = 0;
            P(0x22) = 0;
            P(0x20) = W(0x28);
        }
        P(0x10) = ((x / 8) & 0xFF) | (((y / 8) & 0xFF) << 8);
    }
}
#endif
