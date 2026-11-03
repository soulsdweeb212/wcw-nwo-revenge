/* @header
 * func_800A2BC0
 * VRAM 0x800A2BC0 | ROM 0x4F330 | size 0x940
 * asm: asm/nonmatchings/code_80090000/func_800A2BC0.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } V;
typedef struct { u8 pad0[4]; u32 img; u8 pad8[4]; s16 width; s16 height; s16 h; } Spr;

extern V *D_800E7CB4;
u32 func_8001CE80(V *);
void appendPaletteSetupDisplayList(G **);

#define _SHIFTL(v, s, w) ((unsigned int)(((unsigned int)(v) & ((0x01 << (w)) - 1)) << (s)))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define gSetImage(pkt, cmd, fmt, siz, width, i) \
{ G *_g = (G *)(pkt); \
  _g->w0 = _SHIFTL(cmd, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) | _SHIFTL((width) - 1, 0, 12); \
  _g->w1 = (unsigned int)(i); }
#define gDPSetTextureImage(pkt, f, s, w, i) gSetImage(pkt, 0xFD, f, s, w, i)
#define gDPSetTile(pkt, fmt, siz, line, tmem, tile, palette, cmt, maskt, shiftt, cms, masks, shifts) \
{ G *_g = (G *)(pkt); \
  _g->w0 = _SHIFTL(0xF5, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) | _SHIFTL(line, 9, 9) | _SHIFTL(tmem, 0, 9); \
  _g->w1 = _SHIFTL(tile, 24, 3) | _SHIFTL(palette, 20, 4) | _SHIFTL(cmt, 18, 2) | _SHIFTL(maskt, 14, 4) | \
           _SHIFTL(shiftt, 10, 4) | _SHIFTL(cms, 8, 2) | _SHIFTL(masks, 4, 4) | _SHIFTL(shifts, 0, 4); }
#define gDPNoParam(pkt, cmd) { G *_g = (G *)(pkt); _g->w0 = _SHIFTL(cmd, 24, 8); _g->w1 = 0; }
#define gDPLoadSync(pkt) gDPNoParam(pkt, 0xE6)
#define gDPPipeSync(pkt) gDPNoParam(pkt, 0xE7)
#define gDPLoadBlock(pkt, tile, uls, ult, lrs, dxt) \
{ G *_g = (G *)(pkt); \
  _g->w0 = (_SHIFTL(0xF3, 24, 8) | _SHIFTL(uls, 12, 12) | _SHIFTL(ult, 0, 12)); \
  _g->w1 = (_SHIFTL(tile, 24, 3) | _SHIFTL((MIN(lrs, 2047)), 12, 12) | _SHIFTL(dxt, 0, 12)); }
#define gDPLoadTileGeneric(pkt, c, tile, uls, ult, lrs, lrt) \
{ G *_g = (G *)(pkt); \
  _g->w0 = _SHIFTL(c, 24, 8) | _SHIFTL(uls, 12, 12) | _SHIFTL(ult, 0, 12); \
  _g->w1 = _SHIFTL(tile, 24, 3) | _SHIFTL(lrs, 12, 12) | _SHIFTL(lrt, 0, 12); }
#define gDPSetTileSize(pkt, t, uls, ult, lrs, lrt) gDPLoadTileGeneric(pkt, 0xF2, t, uls, ult, lrs, lrt)
#define gDPLoadTile(pkt, t, uls, ult, lrs, lrt) gDPLoadTileGeneric(pkt, 0xF4, t, uls, ult, lrs, lrt)

#define TXL2WORDS_4b(txls) MAX(1, ((txls) / 16))
#define CALC_DXT_4b(width) (((1 << 11) + TXL2WORDS_4b(width) - 1) / TXL2WORDS_4b(width))

#define gDPLoadTextureBlock_4b(pkt, timg, fmt, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt) \
{ \
  gDPSetTextureImage(pkt, fmt, 2, 1, timg); \
  gDPSetTile(pkt, fmt, 2, 0, 0, 7, 0, cmt, maskt, shiftt, cms, masks, shifts); \
  gDPLoadSync(pkt); \
  gDPLoadBlock(pkt, 7, 0, 0, (((width) * (height) + 3) >> 2) - 1, CALC_DXT_4b(width)); \
  gDPPipeSync(pkt); \
  gDPSetTile(pkt, fmt, 0, ((((width) >> 1) + 7) >> 3), 0, 0, pal, cmt, maskt, shiftt, cms, masks, shifts); \
  gDPSetTileSize(pkt, 0, 0, 0, ((width) - 1) << 2, ((height) - 1) << 2); \
}

#define gDPLoadTextureTile_4b(pkt, timg, fmt, width, height, uls, ult, lrs, lrt, pal, cms, cmt, masks, maskt, shifts, shiftt) \
{ \
  gDPSetTextureImage(pkt, fmt, 1, ((width) >> 1), timg); \
  gDPSetTile(pkt, fmt, 1, (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), 0, 7, 0, cmt, maskt, shiftt, cms, masks, shifts); \
  gDPLoadSync(pkt); \
  gDPLoadTile(pkt, 7, (uls) << 1, (ult) << 2, (lrs) << 1, (lrt) << 2); \
  gDPPipeSync(pkt); \
  gDPSetTile(pkt, fmt, 0, (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), 0, 0, pal, cmt, maskt, shiftt, cms, masks, shifts); \
  gDPSetTileSize(pkt, 0, (uls) << 2, (ult) << 2, (lrs) << 2, (lrt) << 2); \
}

#define SPVERTEX(g, v, n, v0) { G *_g = (g); _g->w0 = _SHIFTL(1, 24, 8) | _SHIFTL((n), 12, 8) | _SHIFTL((v0) + (n), 1, 7); _g->w1 = func_8001CE80(v); }
#define TRI_W1(v0, v1, v2) (_SHIFTL((v0) * 2, 16, 8) | _SHIFTL((v1) * 2, 8, 8) | _SHIFTL((v2) * 2, 0, 8))
#define SP2TRI(g, a0, a1, a2, b0, b1, b2) { G *_g = (g); _g->w0 = (_SHIFTL(7, 24, 8) | TRI_W1(a0, a1, a2)); _g->w1 = TRI_W1(b0, b1, b2); }
#define VTX(X, Y, S, T) { V *v = D_800E7CB4++; v->ob[0] = (X); v->ob[1] = (Y); v->ob[2] = 0; v->flag = 0; v->tc[0] = (S); v->tc[1] = (T); v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF; }

void func_800A2BC0(G **dl, Spr *r, s32 *x, s32 *y, s32 n, s32 h) {
    G *g = *dl;
    s32 w = r->h;
    s32 x0, x1, y0, y1;

    if (w < h) {
        w = h;
    }
    appendPaletteSetupDisplayList(&g);
    if (w >= 0x100) {
        x0 = x[0] + ((x[1] - x[0]) << 8) / w;
        x1 = x[2] + ((x[3] - x[2]) << 8) / w;
        y0 = y[0] + ((y[1] - y[0]) << 8) / w;
        y1 = y[2] + ((y[3] - y[2]) << 8) / w;
        SPVERTEX(g++, D_800E7CB4, 6, n);
        VTX(x[0], y[0], 0, 0);
        VTX(x0, y0, 0x2000, 0);
        VTX(x[1], y[1], w << 5, 0);
        VTX(x[2], y[2], 0, 0x1C0);
        VTX(x1, y1, 0x2000, 0x1C0);
        VTX(x[3], y[3], w << 5, 0x1C0);
        gDPLoadTextureTile_4b(g++, r->img, 2, r->width, r->height, 0, 0, 0x100, 14, 0, 0, 0, 0, 0, 0, 0);
        SP2TRI(g++, n, n + 1, n + 4, n, n + 4, n + 3);
        gDPLoadTextureTile_4b(g++, r->img, 2, r->width, r->height, 0x100, 0, r->width, 14, 0, 0, 0, 0, 0, 0, 0);
        SP2TRI(g++, n + 1, n + 2, n + 5, n + 1, n + 5, n + 4);
    } else {
        SPVERTEX(g++, D_800E7CB4, 4, n);
        VTX(x[0], y[0], 0, 0);
        VTX(x[1], y[1], w << 5, 0);
        VTX(x[2], y[2], 0, 0x1C0);
        VTX(x[3], y[3], w << 5, 0x1C0);
        gDPLoadTextureBlock_4b(g++, r->img, 2, r->width, r->height, 0, 0, 0, 0, 0, 0, 0);
        SP2TRI(g++, n, n + 1, n + 3, n, n + 3, n + 2);
    }
    *dl = g;
}
