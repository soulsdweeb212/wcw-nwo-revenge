/* @header
 * func_800A3E00
 * VRAM 0x800A3E00 | ROM 0x50570 | size 0x484
 * asm: asm/nonmatchings/code_80090000/func_800A3E00.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } V;
typedef struct { u8 pad0[4]; void *img; u8 pad8[4]; s16 w; s16 h; s16 len; } Spr;

extern V *D_800E7CB4;
Spr *func_800B600C(s32, s32);
void appendPaletteSetupDisplayList(G **);
u32 osVirtualToPhysical(V *);

#define SHL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define SETTIMG(g, fmt, siz, w, i) { G *_g = (g); _g->w0 = SHL(0xFD, 24, 8) | SHL(fmt, 21, 3) | SHL(siz, 19, 2) | SHL((w) - 1, 0, 12); _g->w1 = (u32)(i); }
#define SETTILE(g, fmt, siz, line, tmem, tile, pal, cmt, maskt, shiftt, cms, masks, shifts) { G *_g = (g); _g->w0 = SHL(0xF5, 24, 8) | SHL(fmt, 21, 3) | SHL(siz, 19, 2) | SHL(line, 9, 9) | SHL(tmem, 0, 9); _g->w1 = SHL(tile, 24, 3) | SHL(pal, 20, 4) | SHL(cmt, 18, 2) | SHL(maskt, 14, 4) | SHL(shiftt, 10, 4) | SHL(cms, 8, 2) | SHL(masks, 4, 4) | SHL(shifts, 0, 4); }
#define NOPARAM(g, c) { G *_g = (g); _g->w0 = SHL(c, 24, 8); _g->w1 = 0; }
#define LOADTILE(g, tile, uls, ult, lrs, lrt) { G *_g = (g); _g->w0 = SHL(0xF4, 24, 8) | SHL(uls, 12, 12) | SHL(ult, 0, 12); _g->w1 = SHL(tile, 24, 3) | SHL(lrs, 12, 12) | SHL(lrt, 0, 12); }
#define SETTILESIZE(g, tile, uls, ult, lrs, lrt) { G *_g = (g); _g->w0 = SHL(0xF2, 24, 8) | SHL(uls, 12, 12) | SHL(ult, 0, 12); _g->w1 = SHL(tile, 24, 3) | SHL(lrs, 12, 12) | SHL(lrt, 0, 12); }
#define LOADTEXTILE_4b(g, timg, fmt, width, height, uls, ult, lrs, lrt, pal, cms, cmt, masks, maskt, shifts, shiftt) \
    { \
        SETTIMG(g++, fmt, 1, ((width) >> 1), timg); \
        SETTILE(g++, fmt, 1, (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), 0, 7, 0, cmt, maskt, shiftt, cms, masks, shifts); \
        NOPARAM(g++, 0xE6); \
        LOADTILE(g++, 7, (uls) << 1, (ult) << 2, (lrs) << 1, (lrt) << 2); \
        NOPARAM(g++, 0xE7); \
        SETTILE(g++, fmt, 0, (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), 0, 0, pal, cmt, maskt, shiftt, cms, masks, shifts); \
        SETTILESIZE(g++, 0, (uls) << 2, (ult) << 2, (lrs) << 2, (lrt) << 2); \
    }
#define TRI_W1(v0, v1, v2) (SHL((v0) * 2, 16, 8) | SHL((v1) * 2, 8, 8) | SHL((v2) * 2, 0, 8))
#define SP2TRI(g, a0, a1, a2, b0, b1, b2) { G *_g = (g); _g->w0 = (SHL(7, 24, 8) | TRI_W1(a0, a1, a2)); _g->w1 = TRI_W1(b0, b1, b2); }
#define SPVERTEX(g, v, n, v0) { G *_g = (g); _g->w0 = SHL(1, 24, 8) | SHL((n), 12, 8) | SHL((v0) + (n), 1, 7); _g->w1 = osVirtualToPhysical(v); }

void func_800A3E00(G **dl, s32 id) {
    G *g = *dl;
    Spr *s = func_800B600C(id, 0x8008);
    V *v;
    s32 half, step, x, i, k, uls, lrs;

    if (s == NULL) {
        return;
    }
    if (s->len >= 0x90) {
        step = 0x2400 / s->len;
        half = 0x40;
    } else {
        half = s->len / 2;
        step = 0x40;
    }
    x = -half / 2;
    appendPaletteSetupDisplayList(&g);
    SPVERTEX(g++, D_800E7CB4, (s16)(s->len / 144) * 2 + 4, 0);
    k = 0;
    i = 0;
    while (i < s->len) {
        lrs = i + 0x91;
        uls = i - (i > 0);
        if (lrs >= s->len) {
            lrs = s->len - 1;
        }
        {
            V *v = D_800E7CB4++;
            v->ob[0] = x; v->ob[1] = -6; v->ob[2] = 0; v->flag = 0;
            v->tc[0] = i << 5; v->tc[1] = 0;
            v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
        }
        {
            V *v = D_800E7CB4++;
            v->ob[0] = x; v->ob[1] = 6; v->ob[2] = 0; v->flag = 0;
            v->tc[0] = i << 5; v->tc[1] = (s->h - 1) << 5;
            v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
        }
        i += 0x90;
        LOADTEXTILE_4b(g, s->img, 2, s->w, s->h, uls, 0, lrs, s->h - 1, 0, 0, 0, 0, 0, 0, 0);
        SP2TRI(g++, k, k + 2, k + 3, k, k + 3, k + 1);
        k += 2;
        x += step;
    }
    v = D_800E7CB4++;
    v->ob[0] = half / 2; v->ob[1] = -6; v->ob[2] = 0; v->flag = 0;
    v->tc[0] = (s->len - 1) << 5; v->tc[1] = 0;
    v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
    v = D_800E7CB4++;
    v->ob[0] = half / 2; v->ob[1] = 6; v->ob[2] = 0; v->flag = 0;
    v->tc[0] = (s->len - 1) << 5; v->tc[1] = (s->h - 1) << 5;
    v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
    *dl = g;
}
