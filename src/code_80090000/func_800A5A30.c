/* @header
 * func_800A5A30
 * VRAM 0x800A5A30 | ROM 0x521A0 | size 0xA68
 * asm: asm/nonmatchings/code_80090000/func_800A5A30.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } V;
typedef struct { u8 pad0[4]; u32 img; u8 pad8[4]; s16 width; } Spr;
typedef struct { u8 pad0[0x16]; u8 f16; u8 f17; u8 pad18[8]; u16 f20; u16 f22; } Item;
typedef struct { s32 x; s32 y; s32 page; s32 len; } Kb;

extern V *D_800E7CB4;
extern s32 D_800CCD40;
extern Kb D_800E7BF0;
u32 osVirtualToPhysical(V *);
s32 func_80099694(u16, u16);
Spr *func_800B600C(s32, s32);
void appendPaletteSetupDisplayList(G **);
void func_800B6FE0(G **, s32);

#define _SHIFTL(v, s, w) ((unsigned int)(((unsigned int)(v) & ((0x01 << (w)) - 1)) << (s)))

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
#define gDPLoadTileGeneric(pkt, c, tile, uls, ult, lrs, lrt) \
{ G *_g = (G *)(pkt); \
  _g->w0 = _SHIFTL(c, 24, 8) | _SHIFTL(uls, 12, 12) | _SHIFTL(ult, 0, 12); \
  _g->w1 = _SHIFTL(tile, 24, 3) | _SHIFTL(lrs, 12, 12) | _SHIFTL(lrt, 0, 12); }
#define gDPSetTileSize(pkt, t, uls, ult, lrs, lrt) gDPLoadTileGeneric(pkt, 0xF2, t, uls, ult, lrs, lrt)
#define gDPLoadTile(pkt, t, uls, ult, lrs, lrt) gDPLoadTileGeneric(pkt, 0xF4, t, uls, ult, lrs, lrt)

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

#define TRI_W(v0, v1, v2) (_SHIFTL((v0) * 2, 16, 8) | _SHIFTL((v1) * 2, 8, 8) | _SHIFTL((v2) * 2, 0, 8))
#define QUAD(pkt, v0, v1, v2, v3) \
    { G *_g = (G *)(pkt); _g->w0 = (_SHIFTL(0x07, 24, 8) | TRI_W(v0, v1, v2)); _g->w1 = TRI_W(v0, v2, v3); }
#define EMIT(a, b) { G *_g = g++; _g->w0 = (a); _g->w1 = (b); }
#define VTX(X, Y, S, T) { V *v = D_800E7CB4++; v->ob[0] = (X); v->ob[1] = (Y); v->ob[2] = 0; v->flag = 0; \
    v->tc[0] = (S); v->tc[1] = (T); v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF; }

/* One 256x14 band of the CI4 keyboard image, drawn on the quad of vertices 2k..2k+3. */
#define BAND(k) \
{ \
  gDPPipeSync(g++); \
  gDPLoadTextureTile_4b(g++, spr->img, 2, spr->width, 0, 0, (k) * 14, 255, ((k) + 1) * 14, 0, 0, 0, 0, 0, 0, 0); \
  QUAD(g++, (k) * 2, (k) * 2 + 1, (k) * 2 + 3, (k) * 2 + 2); \
}

void func_800A5A30(G **dl, Item *it) {
    G *g = *dl;
    s32 x, y, i;
    u8 buf[12];
    Spr *spr;

    D_800CCD40 += 8;
    gDPPipeSync(g++);
    EMIT(0xFC51FEA3, 0x44FE773B);
    EMIT(0xFA000000, it->f16 >> 1);
    QUAD(g++, 14, 15, 17, 16);
    if (D_800E7BF0.y < 6) {
        /* x first steps a colour through a local table that nothing reads; the ROM keeps it in the same register as
           the cursor x below, so it is one variable */
        x = D_800CCD40;
        for (i = 0; i < 12; i++) {
            if (x & 0x100) {
                buf[i] = x;
            } else {
                buf[i] = ~x;
            }
            x += 0x50;
        }
        x = D_800E7BF0.x * 2 - 6;
        if (it->f20 & 0x80) {
            x += 2;
        } else {
            if (D_800E7BF0.x >= 5) {
                x++;
            }
            if (D_800E7BF0.x >= 10) {
                x++;
            }
        }
        x *= 6;
        x--;
        y = D_800E7BF0.y * 12;
        EMIT(0xFA000000, it->f16 >> 1);
        EMIT(0x01008038, osVirtualToPhysical(D_800E7CB4));
        VTX(x - 6, y - 6, 0, 0);
        VTX(x + 6, y - 6, 0, 0);
        VTX(x - 6, y + 6, 0, 0);
        VTX(x + 6, y + 6, 0, 0);
        VTX(x - 7, y - 7, 0, 0);
        VTX(x + 7, y - 7, 0x200, 0);
        VTX(x - 7, y + 7, 0, 0x200);
        VTX(x + 7, y + 7, 0x200, 0x200);
        QUAD(g++, 20, 21, 23, 22);
    }
    EMIT(0xFA000000, it->f16);
    spr = func_800B600C(func_80099694(it->f20, it->f22), 0x88);
    if (spr == NULL) {
        return;
    }
    appendPaletteSetupDisplayList(&g);
    BAND(0);
    BAND(1);
    BAND(2);
    BAND(3);
    BAND(4);
    BAND(5);
    if (D_800E7BF0.y < 6) {
        EMIT(0xFA000000, it->f16);
        func_800B6FE0(&g, 0xE6);
        QUAD(g++, 24, 25, 27, 26);
    }
    *dl = g;
}
