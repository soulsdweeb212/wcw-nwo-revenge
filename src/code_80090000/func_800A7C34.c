/* @header
 * func_800A7C34
 * VRAM 0x800A7C34 | ROM 0x543A4 | size 0x268
 * asm: asm/nonmatchings/code_80090000/func_800A7C34.s
 */
#include "common.h"


#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx. */
typedef Gfx G;
#else
typedef struct { u32 w0, w1; } G;
#endif
typedef struct { u8 pad[0x10]; u16 wh; u8 pad2[0xE]; u16 a; u16 b; } T;
extern struct { u8 pad[0xA]; u16 f; u8 pad2[0x1C]; u16 g; } D_8007EF30;
extern u16 D_800C9252;
extern u8 D_800C9C70[];
void func_800A77C4(G **, s32, s32, s32, s32, s32, s32);
void func_800B6FE0(G **, s32);

void func_800A7C34(G **dl, T *t) {
    G *g = *dl;
    u32 wh = t->wh;
    s32 a, b, w, h, x, y, f;
    {
        G *p = g++;
        p->w0 = 0xDE000000;
#ifdef TARGET_PC
        /* PC: the branch target as the whole pointer (port.h's DL_ADDR). */
        p->w1 = DL_ADDR(D_800C9C70);
#else
        p->w1 = (u32)D_800C9C70;
#endif
    }
    a = wh & 0xFF;
    w = a * 8;
    b = wh >> 8;
    h = b * 8;
    if (w == 0 || h == 0) {
        func_800B6FE0(&g, D_800C9252);
        {
            G *p = g++;
            p->w0 = 0xDF000000;
            p->w1 = 0;
        }
    } else {
        f = D_8007EF30.f & 0x1F;
        x = w * 0x18 / 32;
        y = h * 0x18 / 32;
        {
            G *p = g++;
            p->w0 = 0xFC121624;
            p->w1 = 0xFF2FFFFF;
        }
        if (t->a != D_8007EF30.g) {
            {
                G *p = g++;
                p->w0 = 0xFA000000;
                p->w1 = (((0xFF - t->b) * 3) / 4) & 0xFF;
            }
            func_800A77C4(&g, x, y, w, h, f, D_8007EF30.g);
            {
                G *p = g++;
                p->w0 = 0xE7000000;
                p->w1 = 0;
            }
            {
                G *p = g++;
                p->w0 = 0xE200001C;
                p->w1 = 0x5041C8;
            }
            {
                G *p = g++;
                p->w0 = 0xFA000000;
                p->w1 = ((t->b * 3) / 4) & 0xFF;
            }
            func_800A77C4(&g, x, y, w, h, f, t->a);
        } else {
            {
                G *p = g++;
                p->w0 = 0xFA000000;
                p->w1 = 0xC0;
            }
            func_800A77C4(&g, x, y, w, h, f, t->a);
        }
    }
    *dl = g;
}
