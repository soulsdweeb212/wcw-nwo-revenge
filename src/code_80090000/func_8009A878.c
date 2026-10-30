/* @header
 * func_8009A878
 * VRAM 0x8009A878 | ROM 0x46FE8 | size 0xDF4
 * asm: asm/nonmatchings/code_80090000/func_8009A878.s
 */
#include "common.h"

typedef struct {u32 w0,w1;} G;
typedef struct {u8 pad[0xEA];u16 tick;} State9B;
extern u8 updateEntityReactionState[];
extern s32 D_800E797C;
extern s32 D_800E81F8;
u8 *func_800B600C(s32,s32);
u8 *func_800B64EC(s32,s32);
s32 func_8001C580(void);
extern u8 D_C95F0[];
extern u8 D_C95B8[];
#define TIMER (*(s32*)(updateEntityReactionState+0x20))
#define CUR (*(s32*)(updateEntityReactionState+0x1C))
#define E(a,b) {G *_g=gfx++;_g->w0=(a);_g->w1=(u32)(b);}
#define XY(x,y) (((u32)((y)<<18)>>16)|((x)<<18))
#define ST(s,t) (((u32)((t)<<21)>>16)|((s)<<21))
#define PHYS(p) ((u32)(p)-0x80000000)
#define TLUT(p) {E(0xFD100000,PHYS(p));E(0xE8000000,0);E(0xF5000100,0x07000000);E(0xE6000000,0);E(0xF0000000,0x0703C000);E(0xE7000000,0);}
#define TEX(p) {E(0xFD500000,PHYS(p));E(0xF5500000,0x07018060);E(0xE6000000,0);E(0xF3000000,0x073FF200);E(0xE7000000,0);E(0xF5400800,0x00018060);E(0xF2000000,0x000FC0FC);}
void func_8009A878(G **arg0, State9B *arg1, s32 arg2)
{
    G *gfx;
    u8 *img;
    s32 x2, y2, x3, y3;
    s32 state, t, n, m;
    s32 x0, x1, y0, y1;
    s32 ya, yb;
    u8 *tex;

    state = D_800E797C;
    gfx = *arg0;
    t = state & 0xFF;
    n = t;
    E(0xDE000000, D_C95F0);
    E(0xDE000000, D_C95B8);
    switch (state >> 8) {
    case 0:
        TIMER = 0;
        CUR = -1;
        break;
    case 1:
        n = 8 - t;
    case 4:
        E(0xFCFFFFFF, 0xFFFDF6FB);
        E(0xFA000000, 0xFFFFFFFF);
        if (n < 4) {
            x0 = -3 * n / 4 + 50;
            x1 = 6 * n / 4 + 169;
            x2 = 3 * n / 4 + 44;
            x3 = -6 * n / 4 + 181;
            y0 = 27 * n / 4 + 148;
            y1 = 26 * n / 4 + 152;
            y2 = -28 * n / 4 + 203;
            y3 = -27 * n / 4 + 205;
        } else {
            n -= 4;
            x0 = x2 = n * 16 + 47;
            x1 = x3 = -(n * 64) / 4 + 175;
            y0 = 175;
            y1 = 178;
            y2 = 176;
            y3 = 179;
        }
        E(0x02180000, XY(x0, y0));
        E(0x02180002, XY(x1, y1));
        E(0x02180004, XY(x2, y2));
        E(0x02180006, XY(x3, y3));
        E(0x02140000, 0);
        E(0x02140002, 0);
        E(0x02140004, 0);
        E(0x02140006, 0);
        E(0x07000206, 0x604);
        if (t >= 8) {
            D_800E797C = 0;
        } else {
            D_800E797C++;
        }
        break;
    case 2:
        if (t >= 32) {
            D_800E797C = 0x300;
        } else {
            D_800E797C++;
        }
    case 3:
        if (arg2 >= 0 && (tex = func_800B600C(arg2, 0)) != 0) {
            if ((arg1->tick / 12) & 1) {
                tex += 0x840;
            } else {
                tex += 0x10;
            }
            x2 = 0;
            y2 = 0;
            x3 = 64;
            y3 = 64;
        } else {
            tex = func_800B64EC(D_800E81F8, 1) + 0x10;
            x2 = (arg1->tick & 1) * 32 + (arg1->tick & 2) * 8;
            y2 = (arg1->tick & 3) * 16;
            x3 = x2 + 64;
            y3 = y2 + 64;
        }
        if (CUR >= 0) {
            func_800B600C(CUR, 0);
        }
        if (tex != 0) {
            img = tex + 0x20;
            E(0xFB000000, 0xFFFFFFFF);
            E(0xFA000000, 0xFF);
            TLUT(tex);
            TEX(img);
            E(0x02180000, 0x00C80250);
            E(0x02180002, 0x02A40260);
            E(0x02180004, 0x00B0032C);
            E(0x02180006, 0x02D40334);
            E(0x02140000, ST(x2, y2));
            E(0x02140002, ST(x3, y2));
            E(0x02140004, ST(x2, y3));
            E(0x02140006, ST(x3, y3));
            E(0x07000206, 0x604);
        }
        if (tex != 0 && arg2 >= 0) {
            E(0xFA000000, 0xFFFFFF80);
            m = arg1->tick & 0x1F;
            x0 = -6 * m / 31 + 50;
            x1 = 12 * m / 31 + 169;
            ya = 55 * m / 31;
            yb = 53 * m / 31;
            E(0x02180000, XY(x0, ya + 0x93));
            E(0x02180002, XY(x1, yb + 0x97));
            E(0x02180004, XY(x0, ya + 0x95));
            E(0x02180006, XY(x1, yb + 0x99));
            E(0x02140000, ST(x2, y2));
            E(0x02140002, ST(x2 + 64, y2));
            E(0x02140004, ST(x2, y2 + 64));
            E(0x02140006, ST(x2 + 64, y2 + 64));
            E(0x07000206, 0x604);
        } else if (CUR >= 0) {
            if (TIMER != 0) {
                TIMER--;
                if (TIMER == 0 || TIMER == 15 || !(func_8001C580() & 7)) {
                    E(0xFA000000, 0x80);
                } else {
                    E(0xFA000000, 0xFF);
                }
                tex = func_800B600C(CUR, 0);
                if (tex != 0) {
                    tex += 0x10;
                    img = tex + 0x20;
                    TLUT(tex);
                    TEX(img);
                    E(0x02180000, 0x00C80250);
                    E(0x02180002, 0x02A40260);
                    E(0x02180004, 0x00B0032C);
                    E(0x02180006, 0x02D40334);
                    E(0x02140000, 0);
                    E(0x02140002, 0x08000000);
                    E(0x02140004, 0x800);
                    E(0x02140006, 0x08000800);
                    E(0x07000206, 0x604);
                }
            } else if (!(func_8001C580() & 0x1F)) {
                TIMER = 16;
            }
        }
        break;
    }
    *arg0 = gfx;
}
