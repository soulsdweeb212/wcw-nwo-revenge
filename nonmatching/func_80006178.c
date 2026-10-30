#include "common.h"

typedef struct { u32 w0, w1; } Gfx6178;

extern f64 D_8003B120;

#define GFX_CMD(pkt, a, b) { Gfx6178 *_g = (pkt); _g->w0 = (a); _g->w1 = (b); }

void func_80006178(Gfx6178 **glistp, u32 timg, s32 fmt, u32 mode, u32 width, s32 unused,
                   s32 stepX, s32 stepY, s32 startX, s32 startY, s32 endX, s32 endY,
                   f32 fx, f32 fy)
{
    u32 ex1, ey1;
    u32 hw;
    Gfx6178 *gfx = *glistp;
    s32 x, y;
    s32 sx, sy;
    s32 x0, x1, y0, y1;
    s32 rx, ry;
    s32 siz;
    f32 rowT, colT;
    f64 half;

    sy = fy;
    y = startY;
    if (y < endY) {
        ex1 = endX - 1;
        ey1 = endY - 1;
        half = D_8003B120;
        siz = (fmt & 7) << 21;
        hw = width >> 1;
        goto mid;
        do {
            sx = 0;
        mid:
            sx = fx;
            x = startX;
            if (x < endX) {
                rowT = (f32)y - half;
                do {
                    colT = (f32)x - half;
                    x0 = x - 1;
                    if (x0 < 0) {
                        x0 = 0;
                    }
                    x1 = x + stepX;
                    if (ex1 < (u32)x1) {
                        x1 = ex1;
                    }
                    y0 = y - 1;
                    if (y0 < 0) {
                        y0 = 0;
                    }
                    y1 = y + stepY;
                    if (ey1 < (u32)y1) {
                        y1 = ey1;
                    }
                    switch (mode) {
                    case 0: {
                        u32 c;
                        GFX_CMD(gfx++, siz | 0xFD080000 | ((hw - 1) & 0xFFF), timg - 0x80000000);
                        c = 0xF5080000;
                        c = siz | (((((((x1 - x0 + 1) >> 1) + 7) >> 3) & 0x1FF) << 9) | c);
                        GFX_CMD(gfx++, c, 0x07080200);
                        GFX_CMD(gfx++, 0xE6000000, 0);
                        GFX_CMD(gfx++, 0xF4000000 | (((x0 * 2) & 0xFFF) << 12) | ((y0 * 4) & 0xFFF),
                                0x07000000 | (((x1 * 2) & 0xFFF) << 12) | ((y1 * 4) & 0xFFF));
                        GFX_CMD(gfx++, 0xE7000000, 0);
                        GFX_CMD(gfx++, siz | 0xF5000000 | ((((((x1 - x0 + 1) >> 1) + 7) >> 3) & 0x1FF) << 9), 0x00080200);
                        GFX_CMD(gfx++, 0xF2000000 | (((x0 * 4) & 0xFFF) << 12) | ((y0 * 4) & 0xFFF),
                                (((x1 * 4) & 0xFFF) << 12) | ((y1 * 4) & 0xFFF));
                        break;
                    }
                    case 1:
                        GFX_CMD(gfx++, siz | 0xFD080000 | ((width - 1) & 0xFFF), timg - 0x80000000);
                        GFX_CMD(gfx++, 0xF5000000 | siz | 0x80000 | ((((x1 - x0 + 8) >> 3) & 0x1FF) << 9), 0x07080200);
                        GFX_CMD(gfx++, 0xE6000000, 0);
                        GFX_CMD(gfx++, 0xF4000000 | (((x0 * 4) & 0xFFF) << 12) | ((y0 * 4) & 0xFFF),
                                0x07000000 | (((x1 * 4) & 0xFFF) << 12) | ((y1 * 4) & 0xFFF));
                        GFX_CMD(gfx++, 0xE7000000, 0);
                        GFX_CMD(gfx++, 0xF5000000 | siz | 0x80000 | ((((x1 - x0 + 8) >> 3) & 0x1FF) << 9), 0x00080200);
                        GFX_CMD(gfx++, 0xF2000000 | (((x0 * 4) & 0xFFF) << 12) | ((y0 * 4) & 0xFFF),
                                (((x1 * 4) & 0xFFF) << 12) | ((y1 * 4) & 0xFFF));
                        break;
                    case 2:
                        GFX_CMD(gfx++, siz | 0xFD100000 | ((width - 1) & 0xFFF), timg - 0x80000000);
                        GFX_CMD(gfx++, siz | 0xF5100000 | ((((((x1 - x0) * 2) + 9) >> 3) & 0x1FF) << 9), 0x07080200);
                        GFX_CMD(gfx++, 0xE6000000, 0);
                        GFX_CMD(gfx++, 0xF4000000 | (((x0 * 4) & 0xFFF) << 12) | ((y0 * 4) & 0xFFF),
                                0x07000000 | (((x1 * 4) & 0xFFF) << 12) | ((y1 * 4) & 0xFFF));
                        GFX_CMD(gfx++, 0xE7000000, 0);
                        GFX_CMD(gfx++, siz | 0xF5100000 | ((((((x1 - x0) * 2) + 9) >> 3) & 0x1FF) << 9), 0x00080200);
                        GFX_CMD(gfx++, 0xF2000000 | (((x0 * 4) & 0xFFF) << 12) | ((y0 * 4) & 0xFFF),
                                (((x1 * 4) & 0xFFF) << 12) | ((y1 * 4) & 0xFFF));
                        break;
                    }
                    rx = sx + stepX;
                    if ((u32)rx > (u32)(sx + (endX - x))) {
                        rx = sx + (endX - x);
                    }
                    if (rx > 0x1E0) {
                        rx = 0x1E0;
                    }
                    ry = sy + stepY;
                    if ((u32)ry > (u32)(sy + (endY - y))) {
                        ry = sy + (endY - y);
                    }
                    if (ry > 0xF0) {
                        ry = 0xF0;
                    }
                    rx *= 4;
                    ry *= 4;
                    GFX_CMD(gfx++, 0xE4000000 | ((rx & 0xFFF) << 12) | (ry & 0xFFF),
                            (((sx * 4) & 0xFFF) << 12) | ((sy * 4) & 0xFFF));
                    GFX_CMD(gfx++, 0xE1000000, ((s32)(colT * 32.0f) << 16) | ((s32)(rowT * 32.0f) & 0xFFFF));
                    GFX_CMD(gfx++, 0xF1000000, 0x04000400);
                    x += stepX;
                    sx += stepX;
                } while (x < endX);
            }
            y += stepY;
            sy += stepY;
        } while (y < endY);
    }
    *glistp = gfx;
}
