/* @header
 * func_80099DF0
 * VRAM 0x80099DF0 | ROM 0x46560 | size 0x23C
 * asm: asm/nonmatchings/code_80090000/func_80099DF0.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } Gfx;

#define _SHIFTL(v, s, w) ((unsigned int)(((unsigned int)(v) & ((0x01 << (w)) - 1)) << (s)))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define gSetImage(pkt, cmd, fmt, siz, width, i) \
{ Gfx *_g = (Gfx *)(pkt); \
  _g->w0 = _SHIFTL(cmd, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) | _SHIFTL((width) - 1, 0, 12); \
  _g->w1 = (unsigned int)(i); }
#define gDPSetTextureImage(pkt, f, s, w, i) gSetImage(pkt, 0xFD, f, s, w, i)
#define gDPSetTile(pkt, fmt, siz, line, tmem, tile, palette, cmt, maskt, shiftt, cms, masks, shifts) \
{ Gfx *_g = (Gfx *)(pkt); \
  _g->w0 = _SHIFTL(0xF5, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) | _SHIFTL(line, 9, 9) | _SHIFTL(tmem, 0, 9); \
  _g->w1 = _SHIFTL(tile, 24, 3) | _SHIFTL(palette, 20, 4) | _SHIFTL(cmt, 18, 2) | _SHIFTL(maskt, 14, 4) | \
           _SHIFTL(shiftt, 10, 4) | _SHIFTL(cms, 8, 2) | _SHIFTL(masks, 4, 4) | _SHIFTL(shifts, 0, 4); }
#define gDPNoParam(pkt, cmd) { Gfx *_g = (Gfx *)(pkt); _g->w0 = _SHIFTL(cmd, 24, 8); _g->w1 = 0; }
#define gDPTileSync(pkt) gDPNoParam(pkt, 0xE8)
#define gDPLoadSync(pkt) gDPNoParam(pkt, 0xE6)
#define gDPPipeSync(pkt) gDPNoParam(pkt, 0xE7)
#define gDPLoadTLUTCmd(pkt, tile, count) \
{ Gfx *_g = (Gfx *)(pkt); _g->w0 = _SHIFTL(0xF0, 24, 8); _g->w1 = _SHIFTL((tile), 24, 3) | _SHIFTL((count), 14, 10); }
#define gDPLoadBlock(pkt, tile, uls, ult, lrs, dxt) \
{ Gfx *_g = (Gfx *)(pkt); \
  _g->w0 = (_SHIFTL(0xF3, 24, 8) | _SHIFTL(uls, 12, 12) | _SHIFTL(ult, 0, 12)); \
  _g->w1 = (_SHIFTL(tile, 24, 3) | _SHIFTL((MIN(lrs, 2047)), 12, 12) | _SHIFTL(dxt, 0, 12)); }
#define gDPLoadTileGeneric(pkt, c, tile, uls, ult, lrs, lrt) \
{ Gfx *_g = (Gfx *)(pkt); \
  _g->w0 = _SHIFTL(c, 24, 8) | _SHIFTL(uls, 12, 12) | _SHIFTL(ult, 0, 12); \
  _g->w1 = _SHIFTL(tile, 24, 3) | _SHIFTL(lrs, 12, 12) | _SHIFTL(lrt, 0, 12); }
#define gDPSetTileSize(pkt, t, uls, ult, lrs, lrt) gDPLoadTileGeneric(pkt, 0xF2, t, uls, ult, lrs, lrt)

#define TXL2WORDS_4b(txls) MAX(1, ((txls) / 16))
#define CALC_DXT_4b(width) (((1 << 11) + TXL2WORDS_4b(width) - 1) / TXL2WORDS_4b(width))

#define gDPLoadTLUT_pal16(pkt, pal, dram) \
{ \
  gDPSetTextureImage(pkt, 0, 2, 1, dram); \
  gDPTileSync(pkt); \
  gDPSetTile(pkt, 0, 0, 0, (256 + (((pal) & 0xf) * 16)), 7, 0, 0, 0, 0, 0, 0, 0); \
  gDPLoadSync(pkt); \
  gDPLoadTLUTCmd(pkt, 7, 15); \
  gDPPipeSync(pkt); \
}

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

void func_80099DF0(Gfx **glistp, s32 tex, s32 width, s32 height) {
    Gfx *gfx = *glistp;

    gDPLoadTLUT_pal16(gfx++, 0, tex + 0x80000010);
    gDPLoadTextureBlock_4b(gfx++, tex + 0x80000030, 2, width, height, 0, 0, 0, 0, 0, 0, 0);
    *glistp = gfx;
}
