/* @header
 * func_80096D8C
 * VRAM 0x80096D8C | ROM 0x434FC | size 0x3F8
 * asm: asm/nonmatchings/code_80090000/func_80096D8C.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } GfxD8C;
extern f64 D_800D6070;
void func_80096A6C(GfxD8C **, void *, s32, s32, s32, s32, s32, s32, s32);

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((1 << (w)) - 1)) << (s)))
#define gImmp1(pkt, c, p0) { GfxD8C *_g = (GfxD8C *)(pkt); _g->w0 = _SHIFTL(c, 24, 8); _g->w1 = (u32)(p0); }
#define gSPTextureRectangle(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy) { \
    GfxD8C *_g = (GfxD8C *)(pkt); \
    _g->w0 = (_SHIFTL(0xE4, 24, 8) | _SHIFTL(xh, 12, 12) | _SHIFTL(yh, 0, 12)); \
    _g->w1 = (_SHIFTL(tile, 24, 3) | _SHIFTL(xl, 12, 12) | _SHIFTL(yl, 0, 12)); \
    gImmp1(pkt, 0xE1, (_SHIFTL(s, 16, 16) | _SHIFTL(t, 0, 16))); \
    gImmp1(pkt, 0xF1, (_SHIFTL(dsdx, 16, 16) | _SHIFTL(dtdy, 0, 16))); }

void func_80096D8C(GfxD8C **gfxp, void *tex, s32 fmt, s32 x, s32 y, s32 texw, s32 h, s32 w, s32 dh)
{
    GfxD8C *gfx = *gfxp;
    s32 rows = 48;
    s32 cols = 64;
    s32 dtdy;
    f32 scale;
    s32 s, t, sx, xi;
    s32 uls, ult, lrs, lrt;
    f32 fy, fs, ft;
    f32 xl, xh, yl, yh;

    if (fmt != 0) {
        rows = 24;
    }
    scale = D_800D6070 / h * dh;
    dtdy = (h << 10) / dh;
    do {
        t = 0;
    } while (0);
    if (y < 0) t = -y;
    for (fy = 0.0f; t < h; t += rows, fy += rows) {
        if (x < 0) {
            s = -x;
            sx = 0;
        } else {
            s = 0;
            sx = x;
        }
        for (; s < w; s += cols, sx += cols) {
            ft = t;
            uls = s - 1;
            if (uls < 0) uls = 0;
            lrs = s + cols;
            fs = s;
            if (lrs > w - 1) lrs = w - 1;
            ult = t - 1;
            if (ult < 0) ult = 0;
            lrt = t + rows;
            if (lrt > h - 1) lrt = h - 1;
            func_80096A6C(&gfx, tex, fmt, texw, h, uls, ult, lrs, lrt);
            xi = sx + cols;
            xl = sx;
            yl = y + fy * scale;
            if (xi > x + w - 1) xi = x + w - 1;
            xh = xi;
            if (!(xh <= 480.0f)) {
                xh = 480.0f;
            }
            yh = y + (fy + rows) * scale;
            if (!(yh <= y + (h - 1) * scale)) {
                yh = y + (h - 1) * scale;
            }
            if (!(yh <= 240.0f)) {
                yh = 240.0f;
            }
            gSPTextureRectangle(gfx++, (s32)xl << 2, (s32)yl << 2, (s32)xh << 2, (s32)yh << 2, 0,
                                (s32)(fs * 32.0f), (s32)(ft * 32.0f), 1 << 10, dtdy);
        }
    }
    *gfxp = gfx;
}
