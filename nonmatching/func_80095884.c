#include "common.h"

typedef struct { u32 w0, w1; } Gfx;
typedef struct {
    u16 f0;
    u8 f2;
    u8 f3;
    s16 f4;
    s16 f6;
    u16 f8;
    u16 fA;
} PartRec;

extern u8 func_800DB4FC[];
extern u8 stepRecordedFramePlayback[];
extern u8 updateEntityAttackState[];
extern s32 D_800D6D40;
extern s32 D_800D6D44;
extern f32 sinf(f32);
extern f32 cosf(f32);
extern s32 func_800B600C(s32, s32);
extern s32 func_800B64EC(s32, s32);
extern void func_800953F4(Gfx **, s32, s32, s32, s32, s32);
extern void appendPaletteSetupDisplayList(Gfx **);

#define gState (*(s32 *)(func_800DB4FC + 0x18C))
#define gPartsHolder (*(u8 **)(func_800DB4FC + 0x184))
#define gTexTbl (*(s32 *)(func_800DB4FC + 0x1A0))
#define gBounceY D_800D6D40
#define gBounceV D_800D6D44
#define D_334 (*(f64 *)(stepRecordedFramePlayback + 0x334))
#define D_33C (*(f64 *)(stepRecordedFramePlayback + 0x33C))
#define D_344 (*(f64 *)0x800D6060)

#define G(a, b) { Gfx *_g = gfx++; _g->w0 = (a); _g->w1 = (b); }
#define GG(a, b) { Gfx *_g = g++; _g->w0 = (a); _g->w1 = (b); }
#define VXY(x, y) (((u32)((y) << 18) >> 16) | ((x) << 18))
#define VST(s, t) (((u32)((t) << 21) >> 16) | ((s) << 21))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define TXL2WORDS_4b(txls) MAX(1, ((txls) / 16))
#define CALC_DXT_4b(width) (((1 << 11) + TXL2WORDS_4b(width) - 1) / TXL2WORDS_4b(width))

static inline void drawTitle(Gfx **gdl, s32 alpha, s32 arg1, s32 arg2, s32 arg3, s32 x, s32 y)
{
    Gfx *g = *gdl;
    s32 flags;
    s32 big;

    flags = 8;
    big = arg1 & 0x100;
    if (gState == 0) {
        flags = 0x500;
    }
    GG(0xFA000000, alpha & 0xFF);
    GG(0xFB000000, 0xFFFFFF00);
    appendPaletteSetupDisplayList(&g);
    GG(0xDE000000, (u32)(updateEntityAttackState + 0x84));
    if (arg3 != 0) {
        if (!big) {
            func_800953F4(&g, func_800B600C(arg3, flags | 0x8000), x, y + 6, 0xC0, 0x10);
        } else {
            func_800953F4(&g, func_800B600C(arg3, flags), x, y + 6, 0xC0, 0xC);
        }
        func_800953F4(&g, func_800B600C(arg2, flags | 0x8000), x, y - 10, 0xC0, 0x10);
    } else {
        func_800953F4(&g, func_800B600C(arg2, flags | 0x8000), x, y, 0xC0, 0x18);
    }
    GG(0xE7000000, 0);
    *gdl = g;
}

void func_80095884(Gfx **arg0, s32 arg1, s32 arg2, s32 arg3)
{
    f32 s, fc;
    Gfx *gfx;
    s32 i;
    s32 x;
    s32 alpha;
    s32 h;
    s32 s0c, s1c, t1c;
    PartRec *rec;
    s32 tex;
    s32 t;
    s32 y;
    s32 off;
    s32 cur;
    s32 w;
    s32 t0c;
    s32 x0, x1, x2, x3, y0, y1, y2, y3;

    gfx = *arg0;
    t = arg1 & 0xFF;
    if ((u32)gState >= 6) {
        return;
    }
    rec = *(PartRec **)(gPartsHolder + 0x10);
    switch (gState) {
    case 2:
    case 3:
    case 4:
        if (t > 0x90) {
            alpha = 0;
        } else if (t > 0x80) {
            alpha = (0x90 - t) * 16;
        } else {
            alpha = 0xFF;
        }
        break;
    default:
        if (t < 0x20) {
            alpha = t * 8;
        } else if (t > 0x90) {
            alpha = 0;
        } else if (t > 0x80) {
            alpha = (0x90 - t) * 16;
        } else {
            alpha = 0xFF;
        }
        break;
    }
    x = 0xF0;
    y = 0xC8;
    off = 0;
    switch (gState) {
    case 2:
        if (t < 0x10) {
            off = (0xF - t) * 8;
        }
        if (t >= 0x24) {
            y = 0x12C;
        } else if (t >= 0x1E) {
            y = t * 16 - 0x118;
        }
        break;
    case 3:
        if (t < 0x10) {
            off = ((0x60 - t * 6) * 480) / 320;
        }
        break;
    case 4:
        if (t < 0x20) {
            x = (0x20 - t) * 15 + 0xF0;
            off = sinf((((t << 5) & 0x3FF) * 360) * D_334) * 30.0f;
        }
        break;
    }
    G(0xDE000000, (u32)(updateEntityAttackState + 0x84));
    G(0xFC119623, 0xFF2FFFFF);
    i = 0;
    cur = rec->f0;
    if (cur != 0) {
        PartRec *p = rec;
        t0c = 0;
        do {
            u32 tq;
            tex = func_800B64EC(gTexTbl, cur);
            x2 = (p->f4 * 480) / 320;
            s0c = 0;
            x3 = ((p->f4 + p->f8) * 480) / 320;
            y1 = p->f6;
            w = 1 << p->f2;
            h = 1 << p->f3;
            s1c = w;
            y3 = y1 + p->fA;
            y0 = y1;
            y2 = y3;
            x0 = x2;
            x1 = x3;
            t1c = h;
            switch (gState) {
            case 2: {
                f32 a, sn;
                a = (off * 360) * D_33C;
                fc = cosf(a);
                fc = (p->fA >> 1) * fc + (y1 + y3) / 2;
                sn = sinf(a);
                s = (p->fA >> 1) * sn;
                x0 = x2 - s;
                x2 = x2 + s;
                x1 = x3 + s;
                x3 = x3 - s;
                y2 = y3 = fc;
                y0 = y1 = -fc;
                break;
            }
            case 3:
                if (i == 0) {
                    s0c = s1c;
                    s1c = 0;
                    x2 -= off;
                    x0 = x2;
                    x3 -= off;
                    x1 = x3;
                } else {
                    x2 += off;
                    x0 = x2;
                    x3 += off;
                    x1 = x3;
                }
                break;
            case 4: {
                f32 a, A, B, C, D, E, F;
                a = off * D_344;
                y1 = -p->fA;
                x2 = p->f8 >> 1;
                x3 = -p->f8 / 2;
                fc = cosf(a);
                s = sinf(a);
                A = p->f4 + x2 * fc;
                D = y1 * s;
                B = p->f4 + x3 * fc;
                C = p->f6 + y1 * fc;
                E = x2 * s;
                F = x3 * s;
                x0 = (A - D) * 1.5f;
                x2 = A * 1.5f;
                x1 = (B - D) * 1.5f;
                y0 = C + E;
                x3 = B * 1.5f;
                y2 = p->f6 + E;
                y3 = p->f6 + F;
                y1 = C + F;
                break;
            }
            case 5:
                if (i == 0) {
                    G(0xFCFFFFFF, 0xFFFE793C);
                    G(0x02100000, (alpha / 2) & 0xFF);
                    G(0x02100002, (alpha / 2) & 0xFF);
                    G(0x02100004, ((alpha / 2) & 0xFF) | 0x80808000);
                    G(0x02100006, ((alpha / 2) & 0xFF) | 0x80808000);
                } else {
                    G(0xFC121824, 0xFF33FFFF);
                    G(0x02100000, (alpha & 0xFF) | 0x80808000);
                    G(0x02100002, (alpha & 0xFF) | 0x80808000);
                    G(0x02100004, (alpha & 0xFF) | 0xFFFFFF00);
                    G(0x02100006, (alpha & 0xFF) | 0xFFFFFF00);
                }
                break;
            }
            tq = (u32)x1 & 1;
            if (tq >> 1) {
                gBounceV = 0;
            }
            G(0xFA000000, (alpha & 0xFF) | 0xFFFFFF00);
            G(0xFD100000, tex + 0x10 - 0x80000000);
            G(0xE8000000, 0);
            G(0xF5000100, 0x07000000);
            G(0xE6000000, 0);
            G(0xF0000000, 0x0703C000);
            G(0xE7000000, 0);
            G(0xFD500000, tex + 0x30 - 0x80000000);
            G(0xF5500000, 0x07000000);
            G(0xE6000000, 0);
            G(0xF3000000, ((MIN((((w * h) + 3) >> 2) - 1, 0x7FF) & 0xFFF) << 12) | 0x07000000 |
                          (CALC_DXT_4b(w) & 0xFFF));
            G(0xE7000000, 0);
            G(0xF5400000 | (((((w >> 1) + 7) >> 3) & 0x1FF) << 9), 0);
            G(0xF2000000, ((((w - 1) << 2) & 0xFFF) << 12) | (((h - 1) << 2) & 0xFFF));
            G(0x02180000, VXY(x + x0, y + y0));
            G(0x02180002, VXY(x + x1, y + y1));
            G(0x02180004, VXY(x + x2, y + y2));
            G(0x02180006, VXY(x + x3, y + y3));
            G(0x02140000, VST(s0c, t0c));
            G(0x02140002, VST(s1c, t0c));
            G(0x02140004, VST(s0c, t1c));
            G(0x02140006, VST(s1c, t1c));
            G(0x07000206, 0x604);
            rec++;
            cur = rec->f0;
            p++;
            i++;
        } while (cur != 0);
    }
    x = 0xF0;
    y = 0xCA;
    switch (gState) {
    case 2:
        if (t < 0x10) {
            alpha = 0;
            gBounceY = 0;
            gBounceV = 0;
            y = -0x20;
        } else if (t > 0x80) {
            alpha = 0xFF;
            x = t * 32 - 0xF10;
        } else {
            gBounceY += gBounceV;
            if (gBounceY >= 0xF0) {
                gBounceV = -(gBounceV / 2);
                gBounceY = x;
            } else {
                gBounceV += 2;
            }
            y = y - (0xF0 - gBounceY);
        }
        break;
    case 3:
        if (t < 0x10) {
            alpha = 0;
            y = 0x12C;
        } else if (t < 0x20) {
            y = (0x20 - t) * 4 + 0xCA;
        }
        break;
    case 4:
        if (t < 0x20) {
            alpha = 0;
        } else if (t < 0x30) {
            x = (0x30 - t) * 32 + 0xF0;
        }
        break;
    }
    if (alpha != 0) {
        G(0xFC119623, 0xFF2FFFFF);
        drawTitle(&gfx, alpha, arg1, arg2, arg3, x, y);
    }
    *arg0 = gfx;
}
