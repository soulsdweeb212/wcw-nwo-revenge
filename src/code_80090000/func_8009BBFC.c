/* @header
 * func_8009BBFC
 * VRAM 0x8009BBFC | ROM 0x4836C | size 0x414
 * asm: asm/nonmatchings/code_80090000/func_8009BBFC.s
 */
#include "common.h"

typedef struct {
    u32 w0;
    u32 w1;
} NwGfx;

#define NW_SHIFTL(v, s, w) ((unsigned int)(((unsigned int)(v) & ((0x01 << (w)) - 1)) << (s)))

#define nwDPNoParam(pkt, cmd) \
    { NwGfx *_g = (NwGfx *)(pkt); _g->w0 = NW_SHIFTL(cmd, 24, 8); _g->w1 = 0; }

#define nwImmp1(pkt, c, p0) \
    { NwGfx *_g = (NwGfx *)(pkt); _g->w0 = NW_SHIFTL(c, 24, 8); _g->w1 = (unsigned int)(p0); }

#define nwSPTextureRectangle(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy) \
    { \
        NwGfx *_g = (NwGfx *)(pkt); \
        _g->w0 = (NW_SHIFTL(0xE4, 24, 8) | NW_SHIFTL(xh, 12, 12) | NW_SHIFTL(yh, 0, 12)); \
        _g->w1 = (NW_SHIFTL(tile, 24, 3) | NW_SHIFTL(xl, 12, 12) | NW_SHIFTL(yl, 0, 12)); \
        nwImmp1(pkt, 0xE1, (NW_SHIFTL(s, 16, 16) | NW_SHIFTL(t, 0, 16))); \
        nwImmp1(pkt, 0xF1, (NW_SHIFTL(dsdx, 16, 16) | NW_SHIFTL(dtdy, 0, 16))); \
    }

static inline void nwFillBorder(NwGfx **pkt, s32 xl, s32 yl, s32 xh, s32 yh)
{
    NwGfx *gp = *pkt;
    s32 y, y2;

    if (xl < 0) xl = 0;
    if (xh >= 480) xh = 479;
    if (yl < 0) yl = 0;
    if (yh >= 240) yh = 239;
    nwDPNoParam(gp++, 0xE7);
    for (y = yl; y < yh; y += 4) {
        y2 = y + 4;
        if (yh < y2) y2 = yh;
        nwSPTextureRectangle(gp++, xl << 2, y << 2, xh << 2, y2 << 2, 0, 0, 0, 1 << 10, 1 << 10);
    }
    nwDPNoParam(gp++, 0xE7);
    *pkt = gp;
}

void func_8009BBFC(NwGfx **gpp, s32 x, s32 y, s32 w, s32 h)
{
    NwGfx *gp = *gpp;
    s32 top, bottom;

    { NwGfx *_g = gp++; _g->w0 = 0xFCFFFFFF; _g->w1 = 0xFFFDF6FB; }
    if (y > 0) {
        nwFillBorder(&gp, 0, 0, 479, y);
        top = y;
    } else {
        top = 0;
    }
    if (y + h < 239) {
        nwFillBorder(&gp, 0, y + h, 479, 239);
        bottom = y + h;
    } else {
        bottom = 239;
    }
    if (x > 0) {
        nwFillBorder(&gp, 0, top, x, bottom);
    }
    if (x + w < 479) {
        nwFillBorder(&gp, x + w, top, 479, bottom);
    }
    *gpp = gp;
}
