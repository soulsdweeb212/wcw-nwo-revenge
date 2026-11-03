/* @header
 * func_800A171C
 * VRAM 0x800A171C | ROM 0x4DE8C | size 0x4E8
 * asm: asm/nonmatchings/code_80090000/func_800A171C.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
typedef struct { u8 pad0[0x10]; s16 f10; } Def;
typedef struct {
    u8 pad0[0x16];
    u8 f16;
    u8 pad17[0x24 - 0x17];
    Def *def;
    u8 pad28[0x68 - 0x28];
    u8 f68[0x18];
    u8 f80;
    u8 pad81[0x148 - 0x81];
} El;
typedef struct { u8 pad0[5]; u8 n; } Items;
typedef struct {
    Items *items;
    s16 cur;
    u8 pad6[4];
    u16 fA;
    u8 padC[2];
    s16 fE;
    u8 pad10[2];
    s16 f12;
    El *el;
    u8 pad18[0x5C - 0x18];
    void *f5C;
    u8 pad60[0x138 - 0x60];
} Menu;

extern u8 D_800E79B4, D_800E7542;
extern s32 D_800E8208, D_800DC73C, D_800E7CB4;
extern u8 *D_800DC734, *D_800DC740;
extern G *D_800DC738;
extern Menu *D_800E7978;
extern El *D_800E7520;
extern Menu D_800E8230[];
extern s16 D_80038A90;
extern s32 D_80038A8C, D_80038A98, D_800E6B90, D_800E74C8, D_800E7C90;
extern f32 D_800DC828;
void func_800AC144(void);
void func_800A0750(El *, s32, f32 *, f32, Menu *, s32);
void func_800A0420(El *, f32 *, s32, s32);
void func_8009F2F8(G **, s32);
void func_8009F8BC(G **);
s32 func_800B807C(s32, s32);
void func_800B6334(void);
void func_80096A20(s32, s32);

s32 func_800A171C(void) {
    f32 pos[8];
    s32 i, j, k, any, f, x, g, t, h;
    Menu *m;
    El *e, *p;

    D_800E79B4 -= (D_800E79B4 & 0x80) ? D_800E8208 * 8 : D_800E8208 * 2;
    D_800E7542 = ((D_800E79B4 & 0x80) ? (u8)~D_800E79B4 : D_800E79B4) * 2;
    D_800DC73C ^= 1;
    D_800DC738 = (G *)(D_800DC734 + (D_800DC73C << 15));
    D_800E7CB4 = (s32)(D_800DC740 + (D_800DC73C << 13));
    { G *d = D_800DC738++; d->w0 = 0xDF000000; d->w1 = 0; }
    func_800AC144();
    D_800E7978 = &D_800E8230[D_80038A90];
    D_800E7520 = &D_800E7978->el[D_800E7978->cur];
    for (i = 0, m = D_800E8230; i < 0x18; i++, m++) {
        t = (i == D_80038A90);
        if (i == 0x14) {
            t |= 0x10;
        }
        f = t;
        if ((i == 13 || i == 14) && m->fA != 0) {
            f |= 0x20;
        }
        any = 0;
        for (j = 0, e = m->el; j < m->items->n; j++, e++) {
            if (e->f16 != 0) {
                any = -1;
            } else {
                e->f80 |= 0x80;
            }
        }
        if (any) {
            if (f & 0x31) {
                m->fE -= m->f12;
                m->f12--;
                if (m->fE <= 0) {
                    m->f12 = 0;
                    m->fE = 0;
                }
            } else if (m->fE < 0x88) {
                m->f12++;
                m->fE += m->f12;
            } else {
                m->fE = 0x88;
                m->f12 = 0x10;
            }
        }
        if (any) goto draw;
        if (f) {
        draw:
            m->f5C = m->el->f68;
            p = m->el;
            for (k = 0; k < m->items->n; k++, p++) {
                x = (k == m->cur) << 1;
                if (p->def->f10 == m->cur) {
                    h = f | 8;
                    g = x | h;
                } else {
                    g = x | f;
                }
                func_800A0750(p, g, pos, D_800DC828, m, k + i * 2);
                func_800A0420(p, pos, i, g);
            }
        } else {
            m->f5C = 0;
        }
    }
    if (D_80038A8C != 0) {
        if (D_80038A8C > 0 && D_80038A8C < 0x41F) {
            D_80038A8C += 0x18;
            if (D_80038A8C >= 0x420) {
                D_80038A8C = 0x41F;
            }
            if (D_800E74C8 >= 0) {
                D_800E74C8 = D_80038A8C >= 0x320 ? D_80038A8C - 0x320 : 0;
            }
        }
    } else if (D_800E7C90 == 0) {
        if (D_800E74C8 > 0) {
            D_800E74C8 -= 0x18;
            if (D_800E74C8 < 0) {
                D_800E74C8 = 0;
            }
        } else {
            D_800E74C8 += 0xC;
            if (D_800E74C8 > 0) {
                D_800E74C8 = 0;
            }
        }
    }
    func_8009F2F8(&D_800DC738, D_800E74C8);
    func_8009F8BC(&D_800DC738);
    if (D_80038A8C >= 0x41F) {
        if (D_80038A8C == 0x83E || (D_80038A90 == 0x17 && func_800B807C(-1, -1)) || (D_80038A90 != 0x17 && D_80038A8C == 0x41F)) {
            if (D_800E6B90 < 0) {
                D_80038A98 = -1;
            }
            return 1;
        }
    } else if (D_80038A8C < 0) {
        return D_80038A8C == -1 ? -1 : 1;
    } else {
        func_800B6334();
        func_80096A20(0, 0xF0);
        return 0;
    }
}
