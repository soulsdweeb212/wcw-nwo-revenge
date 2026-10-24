#include "common.h"

typedef struct {
    u32 w0;
    u32 w1;
} NwGfx;

typedef struct {
    u8 pad0[4];
    u32 f4;
    u8 pad8[4];
    u16 fC;
    s16 fE;
    s16 f10;
} Obj953;

#define NW_SHIFTL(v, s, w) ((unsigned int)(((unsigned int)(v) & ((0x01 << (w)) - 1)) << (s)))

#define nwSPModifyVertex(pkt, vtx, where, val) \
    { NwGfx *_g = (NwGfx *)(pkt); \
      _g->w0 = (NW_SHIFTL(0x02, 24, 8) | NW_SHIFTL((where), 16, 8) | NW_SHIFTL((vtx) * 2, 0, 16)); \
      _g->w1 = (unsigned int)(val); }

#define nwDPNoParam(pkt, cmd) \
    { NwGfx *_g = (NwGfx *)(pkt); _g->w0 = NW_SHIFTL(cmd, 24, 8); _g->w1 = 0; }

#define nwSetImage(pkt, cmd, fmt, siz, width, i) \
    { NwGfx *_g = (NwGfx *)(pkt); \
      _g->w0 = NW_SHIFTL(cmd, 24, 8) | NW_SHIFTL(fmt, 21, 3) | NW_SHIFTL(siz, 19, 2) | NW_SHIFTL((width) - 1, 0, 12); \
      _g->w1 = (unsigned int)(i); }

#define nwDPSetTile(pkt, fmt, siz, line, tmem, tile, palette, cmt, maskt, shiftt, cms, masks, shifts) \
    { NwGfx *_g = (NwGfx *)(pkt); \
      _g->w0 = NW_SHIFTL(0xF5, 24, 8) | NW_SHIFTL(fmt, 21, 3) | NW_SHIFTL(siz, 19, 2) | NW_SHIFTL(line, 9, 9) | NW_SHIFTL(tmem, 0, 9); \
      _g->w1 = NW_SHIFTL(tile, 24, 3) | NW_SHIFTL(palette, 20, 4) | NW_SHIFTL(cmt, 18, 2) | NW_SHIFTL(maskt, 14, 4) | NW_SHIFTL(shiftt, 10, 4) | NW_SHIFTL(cms, 8, 2) | NW_SHIFTL(masks, 4, 4) | NW_SHIFTL(shifts, 0, 4); }

#define nwDPLoadTileGeneric(pkt, c, tile, uls, ult, lrs, lrt) \
    { NwGfx *_g = (NwGfx *)(pkt); \
      _g->w0 = NW_SHIFTL(c, 24, 8) | NW_SHIFTL(uls, 12, 12) | NW_SHIFTL(ult, 0, 12); \
      _g->w1 = NW_SHIFTL(tile, 24, 3) | NW_SHIFTL(lrs, 12, 12) | NW_SHIFTL(lrt, 0, 12); }

#define nwDPLoadTextureTile_4b(pkt, timg, fmt, width, height, uls, ult, lrs, lrt, cms, cmt, masks, maskt, shifts, shiftt) \
    { \
        nwSetImage(pkt, 0xFD, fmt, 1, ((width) >> 1), timg); \
        nwDPSetTile(pkt, fmt, 1, (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), 0, 7, 0, cmt, maskt, shiftt, cms, masks, shifts); \
        nwDPNoParam(pkt, 0xE6); \
        nwDPLoadTileGeneric(pkt, 0xF4, 7, (uls) << 1, (ult) << 2, (lrs) << 1, (lrt) << 2); \
        nwDPNoParam(pkt, 0xE7); \
        nwDPSetTile(pkt, fmt, 0, (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), 0, 0, 0, cmt, maskt, shiftt, cms, masks, shifts); \
        nwDPLoadTileGeneric(pkt, 0xF2, 0, (uls) << 2, (ult) << 2, (lrs) << 2, (lrt) << 2); \
    }

#define nwSP1Triangle_w1(v0, v1, v2) \
    (NW_SHIFTL((v0) * 2, 16, 8) | NW_SHIFTL((v1) * 2, 8, 8) | NW_SHIFTL((v2) * 2, 0, 8))

#define nwSP1Quadrangle(pkt, v0, v1, v2, v3) \
    { NwGfx *_g = (NwGfx *)(pkt); \
      _g->w0 = (NW_SHIFTL(0x07, 24, 8) | nwSP1Triangle_w1(v0, v1, v2)); \
      _g->w1 = nwSP1Triangle_w1(v0, v2, v3); }

void func_800953F4(NwGfx **gpp, Obj953 *o, s32 x, s32 y, s32 w, s32 h)
{
    NwGfx *gp = *gpp;
    s32 step;
    s32 sw, dx, cx;
    s32 i, v;
    s32 uls, lrs;

    step = (o->fE < 24) ? 240 : 144;
    if (o->f10 >= step) {
        sw = w;
        dx = (sw * step) / o->f10;
    } else {
        sw = (w * o->f10) / step;
        dx = w;
    }
    cx = -sw / 2;
    v = 0;
    for (i = 0; i < o->f10; v += 2) {
        nwSPModifyVertex(gp++, v, 0x18, ((u32)((y - h / 2) << 18) >> 16) | ((x + cx) << 18));
        nwSPModifyVertex(gp++, v, 0x14, i << 21);
        nwSPModifyVertex(gp++, v + 1, 0x18, ((u32)((y + h / 2) << 18) >> 16) | ((x + cx) << 18));
        nwSPModifyVertex(gp++, v + 1, 0x14, ((u32)((o->fE - 1) << 21) >> 16) | (i << 21));
        cx += dx;
        i += step;
    }
    nwSPModifyVertex(gp++, v, 0x18, ((u32)((y - h / 2) << 18) >> 16) | ((x + sw / 2) << 18));
    nwSPModifyVertex(gp++, v, 0x14, (o->f10 - 1) << 21);
    nwSPModifyVertex(gp++, v + 1, 0x18, ((u32)((y + h / 2) << 18) >> 16) | ((x + sw / 2) << 18));
    nwSPModifyVertex(gp++, v + 1, 0x14, ((u32)((o->fE - 1) << 21) >> 16) | ((o->f10 - 1) << 21));
    v = 0;
    for (i = 0; i < o->f10; v += 2) {
        lrs = i + step + 1;
        uls = i - (i > 0);
        if (lrs >= o->f10) {
            lrs = o->f10 - 1;
        }
        nwDPLoadTextureTile_4b(gp++, o->f4, 2, (s16)o->fC, 0, uls, 0, lrs, o->fE - 1, 0, 0, 0, 0, 0, 0);
        nwSP1Quadrangle(gp++, v, v + 2, v + 3, v + 1);
        i += step;
    }
    *gpp = gp;
}
