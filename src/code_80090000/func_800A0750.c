/* @header
 * func_800A0750
 * VRAM 0x800A0750 | ROM 0x4CEC0 | size 0xE00
 * asm: asm/nonmatchings/code_80090000/func_800A0750.s
 */
#include "common.h"

typedef struct {
    s16 x, y;
    u16 f4;
    u8 pad6[9];
    u8 fF;
    s16 f10;
    u8 pad12[2];
    u16 flags;
} Def;

typedef struct El {
    f32 x, y;
    s16 f8;
    u16 fA;
    s8 fC, fD, fE;
    u8 fF;
    s16 f10;
    s16 f12;
    s16 f14;
    u8 f16;
    u8 pad17;
    u8 f18, f19;
    s16 f1A;
    f32 f1C;
    u16 f20;
    s16 f22;
    Def *def;
    u8 pad28[0x144 - 0x28];
    struct El *parent;
} El;

typedef struct { f32 x, y, z; f32 rx, ry, rz; f32 s; } Pos;

typedef struct {
    void *items;
    s16 cur;
    u8 pad6[6];
    s16 fC;
    s16 fE;
    s16 f10;
    s16 f12;
    El *el;
    u8 pad18[0x138 - 0x18];
} Menu;

extern s32 D_800E7C8C;
extern s16 D_800E9F7C;
extern s32 D_800E8208;
extern u8 D_800E7542;
extern El *D_800E7520;
extern s32 D_800E7BF8;
extern Menu D_800E8230[];

/* Rest value of a slide offset (fC/fE) for this element type. */
static inline s32 home(El *p, s32 c) {
    s32 r;
    switch (p->def->fF & 0xF) {
    case 6:
    case 7:
    case 8:
    case 9:
        r = c;
        break;
    case 1:
    case 5:
        r = c << 7;
        break;
    default:
        r = c << 6;
        break;
    }
    return r;
}

void func_800A0750(El *p, s32 g, Pos *pos, f32 scale, Menu *m, s32 idx) {
    s32 h0, h1, step, t, x;
    El *par;
    u16 lo, hi;
    s32 f20hi, f20lo;
    f32 target, glow, b, f, old;
    s32 c;

    pos->x = p->x + m->fC;
    pos->y = (p->y + m->fE) - 14 * 0.2; /* folds to 0x4006666666666667, one ulp above the literal 2.8 */
    pos->z = m->f10;
    pos->s = 1.0f;
    pos->rx = pos->ry = pos->rz = 0.0f;
    if (!(g & 1)) {
        pos->rz = (m->fE * ((idx & 3) * 2 - 3)) / 2;
        pos->rx = (m->fE * (((idx + 1) & 3) * 2 - 3)) / 2;
        pos->ry = (m->fE * (((idx + 2) & 3) * 2 - 3)) / 2;
    }
    if (p->fA & 1) {
        p->f16 = 0;
        p->fA |= 1;
        return;
    }
    f20lo = p->f20 & 0xFF;
    f20hi = p->f20 & 0xFF00;
    h0 = home(p, p->fC);
    h1 = home(p, p->fE);
    x = p->def->fF & 0xF;
    if (x == 1 || x == 5) {
        step = D_800E7C8C * 3;
    } else {
        step = D_800E7C8C * 2;
    }
    p->fA &= 0xFFFE;
    if ((p->fA & 0x40) && (g & 1)) {
        target = 128.0f;
    } else if (p->fA & 0x20) {
        target = 0.0f;
    } else if (g & 0x11) {
        target = 255.0f;
    } else {
        target = 0.0f;
    }
    if (p->f16 != target) {
        if (D_800E9F7C != 0) {
            p->f19 += D_800E7C8C;
        } else {
            p->f19 += D_800E8208;
        }
        if (p->f16 < target) {
            f = p->f16 + (s8)p->f19;
            if (target < f) {
                p->f16 = target;
                p->f19 = 0;
            } else {
                p->f16 = f;
            }
        } else {
            f = p->f16 - (s8)p->f19;
            if (f < target) {
                p->f16 = target;
                p->f19 = 0;
            } else {
                p->f16 = f;
            }
        }
    }
    if (p->def->flags & 0x4000) {
        glow = D_800E7542 + 0x80;
    } else {
        glow = (D_800E7542 >> 1) + 0x7F;
    }
    b = 255.0f;
    if (p->f16 == 0xFF && (p->fA & 0x80)) {
        b = glow;
        p->f14 = b;
    } else if (p->f16 == 0xFF && ((g & 0xA) || f20hi == 0x7700)) {
        x = ((u16)p->f14 + 1) & 0x1FF;
        b = x;
        p->f14 = x;
    } else if (f20hi == 0x5000 && (D_800E7520->f20 & 0xFF00) != f20hi) {
        b = 128.0f;
    } else if (f20hi == 0x6400) {
        b = glow;
    } else if (f20hi == 0x7D00 && f20lo != D_800E7BF8) {
        b = 128.0f;
    }
    if (p->f16 == 0) {
        p->f10 = h0;
        p->f12 = 0;
        p->f14 = b;
        p->fF = 0;
        p->f8 = 0;
        p->fC = p->fD = p->fE;
        return;
    }
    par = p->parent;
    if (!(p->def->flags & 0x200)) {
        if (par != NULL && (par->fA & 8)) {
            p->f8 = par->f8;
        } else if (p->fA & 8) {
            old = p->f8; /* only set on this path; the test below reads it on every path */
            p->f8 += (s8)p->fF;
            if (p->def->flags & 0x400) {
                if (p->f8 >= 0) {
                    p->fF = 0;
                    p->f8 = 0;
                } else if (p->f8 < -0x5A) {
                    p->fF = 2;
                } else if (p->f8 < -0x2D) {
                    p->fF++;
                } else {
                    if ((s8)p->fF < 3) {
                        c = (s8)p->fF;
                    } else {
                        c = (s8)p->fF - 1;
                    }
                    p->fF = c;
                }
            } else if (p->f8 < 0) {
                p->fF += 8;
                if (p->f8 < -0x14) {
                    p->f8 = -0x14;
                    p->fF = 0;
                }
            } else if (old < 0.0f) {
                p->fF = 0;
                p->f8 = 0;
            } else {
                p->fF--;
            }
            if (p->f8 == 0 && (s8)p->fF == 0) {
                p->fA &= 0xFFF7;
            }
        }
        if (p->def->flags & 0x400) {
            if (old != 0.0f && p->f8 >= -0x5A) {
                pos->x += (p->def->x - p->x) * (p->f8 + 0x5A) * (1.0f / 90.0f);
                pos->y += (p->def->y - p->y) * (p->f8 + 0x5A) * (1.0f / 90.0f);
                pos->s = (s8)p->fF * 0.2 * pos->s + pos->s;
                if (p->def->fF & 0x20) {
                    pos->rz += p->f8 * 4.0;
                } else {
                    pos->rz += (s8)p->fF * 8.0;
                }
                if (p->f8 == 0) {
                    p->x = p->def->x;
                    p->y = p->def->y;
                    pos->rz = 0.0f;
                    p->f1C = p->def->f4 * (1.0 / 1024);
                }
            }
        } else {
            pos->rz += (f64)p->f8;
        }
    }
    if (p->f14 != b) {
        p->f18 += D_800E8208 * 2;
        if (p->f14 < b) {
            p->f14 += (s8)p->f18;
            if (b < p->f14) {
                p->f14 = b;
                p->f18 = 0;
            }
        } else {
            p->f14 -= (s8)p->f18;
            if (p->f14 < b) {
                p->f14 = b;
                p->f18 = 0;
            }
        }
    }
    if (p->def->fF & 0xF) {
        if (p->f12 != 0) {
            p->f10 += p->f12;
            if (p->f12 < 0) {
                p->f12 -= step;
            } else {
                p->f12 += step;
            }
            if ((p->f12 < 0 && p->f10 < h0) || (p->f12 > 0 && h0 < p->f10)) {
                p->f10 = h1;
                p->f12 = 0;
                p->fC = p->fD = p->fE;
                if (p == &D_800E8230[12].el[2]) {
                    p->f16 = target;
                }
            }
        } else if (p->fD != p->fC) {
            p->f12 = p->fD < p->fC ? D_800E7C8C : -D_800E7C8C;
            lo = (p->fA >> 8) & 0xF;
            hi = p->fA >> 12;
            if (lo == hi) {
                p->fE = p->fC;
            } else if (lo < p->fC) {
                p->fE = hi;
            } else if (p->fC < hi) {
                p->fE = lo;
            } else {
                p->fE = p->fC;
            }
        }
    }
    pos->s *= scale;
    t = p->def->fF;
    switch (t & 0xF) {
    case 11:
        if (p->f10 >= 0x80) {
            p->f16 = 0;
            p->f19 = 0;
            p->f12 = p->fC > p->fD ? D_800E7C8C : -D_800E7C8C;
            pos->s *= 3.6666667f;
        } else {
            pos->s = pos->s * (f32)((p->f10 + 0x30) * (1.0 / 48));
        }
        break;
    case 1:
        if (t & 0x40) {
            pos->y += p->f10;
        }
        if (p->def->fF & 0x80) {
            pos->x += p->f10;
        }
        break;
    case 5:
        /* h0 is reused for the angle: one variable keeps both in a3 */
        h0 = ((u8)p->f10 * 0xB4) * (1.0 / 128);
        if (t & 0x40) {
            pos->rx -= h0;
        }
        if (p->def->fF & 0x80) {
            pos->ry -= h0;
        }
        break;
    default:
        switch (p->def->fF & 0xF) {
        case 3:
        case 12:
            h0 = (((p->f10 * 2) & 0xFF) * 0xB4) * (1.0 / 128);
            break;
        case 2:
            h0 = (((p->f10 * 4) & 0xFF) * 0xB4) * (1.0 / 128);
            break;
        default:
            h0 = ((u8)p->f10 * 0xB4) * (1.0 / 128);
            break;
        }
        if (p->def->fF & 0x40) {
            pos->rx += h0;
        }
        if (p->def->fF & 0x80) {
            pos->ry += h0;
        }
        break;
    }
}
