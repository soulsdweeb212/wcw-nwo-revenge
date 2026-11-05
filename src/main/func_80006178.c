/* @header
 * func_80006178
 * VRAM 0x80006178 | ROM 0x6D78 | size 0x594
 * asm: asm/nonmatchings/main/func_80006178.s
 */
#include "common.h"

/* libultra gbi.h (only what this function uses) */
typedef struct { u32 w0, w1; } Gwords;
typedef union { Gwords words; long long force_structure_alignment; } Gfx;

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define OS_K0_TO_PHYSICAL(x) (u32)(((char *)(x)-0x80000000))

#define G_SETTIMG 0xfd
#define G_SETTILE 0xf5
#define G_LOADSYNC 0xe6
#define G_LOADTILE 0xf4
#define G_RDPPIPESYNC 0xe7
#define G_SETTILESIZE 0xf2
#define G_TEXRECT 0xe4
#define G_RDPHALF_1 0xe1
#define G_RDPHALF_2 0xf1
#define G_TX_LOADTILE 7
#define G_TX_RENDERTILE 0
#define G_IM_SIZ_4b 0
#define G_IM_SIZ_8b 1
#define G_IM_SIZ_16b 2
#define G_IM_SIZ_8b_TILE_BYTES 1
#define G_IM_SIZ_8b_LINE_BYTES 1
#define G_IM_SIZ_16b_TILE_BYTES 2
#define G_IM_SIZ_16b_LINE_BYTES 2
#define G_TEXTURE_IMAGE_FRAC 2
#define G_TX_CLAMP 0x2
#define G_TX_NOMASK 0
#define G_TX_NOLOD 0

#define gSetImage(pkt, cmd, fmt, siz, width, i)                             \
{                                                                           \
    Gfx *_g = (Gfx *)(pkt);                                                 \
    _g->words.w0 = _SHIFTL(cmd, 24, 8) | _SHIFTL(fmt, 21, 3) |              \
                   _SHIFTL(siz, 19, 2) | _SHIFTL((width)-1, 0, 12);         \
    _g->words.w1 = (unsigned int)(i);                                       \
}
#define gDPSetTextureImage(pkt, f, s, w, i) gSetImage(pkt, G_SETTIMG, f, s, w, i)
#define gDPSetTile(pkt, fmt, siz, line, tmem, tile, palette, cmt,           \
                   maskt, shiftt, cms, masks, shifts)                       \
{                                                                           \
    Gfx *_g = (Gfx *)(pkt);                                                 \
    _g->words.w0 = _SHIFTL(G_SETTILE, 24, 8) | _SHIFTL(fmt, 21, 3) |        \
                   _SHIFTL(siz, 19, 2) | _SHIFTL(line, 9, 9) |              \
                   _SHIFTL(tmem, 0, 9);                                     \
    _g->words.w1 = _SHIFTL(tile, 24, 3) | _SHIFTL(palette, 20, 4) |         \
                   _SHIFTL(cmt, 18, 2) | _SHIFTL(maskt, 14, 4) |            \
                   _SHIFTL(shiftt, 10, 4) | _SHIFTL(cms, 8, 2) |            \
                   _SHIFTL(masks, 4, 4) | _SHIFTL(shifts, 0, 4);            \
}
#define gDPNoParam(pkt, cmd)                                                \
{                                                                           \
    Gfx *_g = (Gfx *)(pkt);                                                 \
    _g->words.w0 = _SHIFTL(cmd, 24, 8);                                     \
    _g->words.w1 = 0;                                                       \
}
#define gDPLoadSync(pkt) gDPNoParam(pkt, G_LOADSYNC)
#define gDPPipeSync(pkt) gDPNoParam(pkt, G_RDPPIPESYNC)
#define gDPLoadTileGeneric(pkt, c, tile, uls, ult, lrs, lrt)                \
{                                                                           \
    Gfx *_g = (Gfx *)(pkt);                                                 \
    _g->words.w0 = _SHIFTL(c, 24, 8) | _SHIFTL(uls, 12, 12) |               \
                   _SHIFTL(ult, 0, 12);                                     \
    _g->words.w1 = _SHIFTL(tile, 24, 3) | _SHIFTL(lrs, 12, 12) |            \
                   _SHIFTL(lrt, 0, 12);                                     \
}
#define gDPSetTileSize(pkt, t, uls, ult, lrs, lrt)                          \
    gDPLoadTileGeneric(pkt, G_SETTILESIZE, t, uls, ult, lrs, lrt)
#define gDPLoadTile(pkt, t, uls, ult, lrs, lrt)                             \
    gDPLoadTileGeneric(pkt, G_LOADTILE, t, uls, ult, lrs, lrt)

#define gDPLoadTextureTile(pkt, timg, fmt, siz, width, height,              \
                           uls, ult, lrs, lrt, pal,                         \
                           cms, cmt, masks, maskt, shifts, shiftt)          \
{                                                                           \
    gDPSetTextureImage(pkt, fmt, siz, width, timg);                         \
    gDPSetTile(pkt, fmt, siz,                                               \
               (((((lrs)-(uls)+1) * siz##_TILE_BYTES)+7)>>3), 0,            \
               G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, masks, shifts);   \
    gDPLoadSync(pkt);                                                       \
    gDPLoadTile(pkt, G_TX_LOADTILE,                                         \
                (uls)<<G_TEXTURE_IMAGE_FRAC, (ult)<<G_TEXTURE_IMAGE_FRAC,   \
                (lrs)<<G_TEXTURE_IMAGE_FRAC, (lrt)<<G_TEXTURE_IMAGE_FRAC);  \
    gDPPipeSync(pkt);                                                       \
    gDPSetTile(pkt, fmt, siz,                                               \
               (((((lrs)-(uls)+1) * siz##_LINE_BYTES)+7)>>3), 0,            \
               G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts);\
    gDPSetTileSize(pkt, G_TX_RENDERTILE,                                    \
                   (uls)<<G_TEXTURE_IMAGE_FRAC, (ult)<<G_TEXTURE_IMAGE_FRAC,\
                   (lrs)<<G_TEXTURE_IMAGE_FRAC, (lrt)<<G_TEXTURE_IMAGE_FRAC)\
}

#define gDPLoadTextureTile_4b(pkt, timg, fmt, width, height,                \
                              uls, ult, lrs, lrt, pal,                      \
                              cms, cmt, masks, maskt, shifts, shiftt)       \
{                                                                           \
    gDPSetTextureImage(pkt, fmt, G_IM_SIZ_8b, ((width)>>1), timg);          \
    gDPSetTile(pkt, fmt, G_IM_SIZ_8b,                                       \
               (((((lrs)-(uls)+1)>>1)+7)>>3), 0, G_TX_LOADTILE, 0,          \
               cmt, maskt, shiftt, cms, masks, shifts);                     \
    gDPLoadSync(pkt);                                                       \
    gDPLoadTile(pkt, G_TX_LOADTILE,                                         \
                (uls)<<(G_TEXTURE_IMAGE_FRAC-1), (ult)<<(G_TEXTURE_IMAGE_FRAC), \
                (lrs)<<(G_TEXTURE_IMAGE_FRAC-1), (lrt)<<(G_TEXTURE_IMAGE_FRAC)); \
    gDPPipeSync(pkt);                                                       \
    gDPSetTile(pkt, fmt, G_IM_SIZ_4b,                                       \
               (((((lrs)-(uls)+1)>>1)+7)>>3), 0,                            \
               G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts);\
    gDPSetTileSize(pkt, G_TX_RENDERTILE,                                    \
                   (uls)<<G_TEXTURE_IMAGE_FRAC, (ult)<<G_TEXTURE_IMAGE_FRAC,\
                   (lrs)<<G_TEXTURE_IMAGE_FRAC, (lrt)<<G_TEXTURE_IMAGE_FRAC)\
}

#define gImmp1(pkt, c, p0)                                                  \
{                                                                           \
    Gfx *_g = (Gfx *)(pkt);                                                 \
    _g->words.w0 = _SHIFTL(c, 24, 8);                                       \
    _g->words.w1 = (unsigned int)(p0);                                      \
}

/* Draws a large texture as a grid of stepX x stepY tiles: for each tile it
 * loads the texels (one texel of border on each side, clamped to the image)
 * with gDPLoadTextureTile{,_4b} for 4, 8 or 16 bpp, then draws a texture
 * rectangle at screen position (fx, fy) + offset, clipped to 480x240.
 * `height` is the unused height argument of the load macros. */
void func_80006178(Gfx **glistp, void *timg, s32 fmt, u32 siz, u32 width, u32 height,
                   s32 stepX, s32 stepY, s32 startX, s32 startY, s32 endX, s32 endY,
                   f32 fx, f32 fy)
{
    Gfx *gfx = *glistp;
    s32 x, y, sx, sy;
    s32 uls, ult, lrs, lrt;
    s32 rx, ry;
    f32 s, t;

    for (y = startY, sy = fy; y < endY; y += stepY, sy += stepY) {
        for (x = startX, sx = fx; x < endX; x += stepX, sx += stepX) {
            s = (f32)x - 0.5;
            t = (f32)y - 0.5;
            uls = x - 1;
            if (uls < 0) {
                uls = 0;
            }
            lrs = x + stepX;
            if (lrs > (u32)(endX - 1)) {
                lrs = endX - 1;
            }
            ult = y - 1;
            if (ult < 0) {
                ult = 0;
            }
            lrt = y + stepY;
            if (lrt > (u32)(endY - 1)) {
                lrt = endY - 1;
            }
            switch (siz) {
            case 0:
                gDPLoadTextureTile_4b(gfx++, OS_K0_TO_PHYSICAL(timg), fmt, width, height,
                                      uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP,
                                      G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            case 1:
                gDPLoadTextureTile(gfx++, OS_K0_TO_PHYSICAL(timg), fmt, G_IM_SIZ_8b, width, height,
                                   uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP,
                                   G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            case 2:
                gDPLoadTextureTile(gfx++, OS_K0_TO_PHYSICAL(timg), fmt, G_IM_SIZ_16b, width, height,
                                   uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP,
                                   G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            }
            rx = sx + stepX;
            if (rx > (u32)(sx + (endX - x))) {
                rx = sx + (endX - x);
            }
            if (rx > 480) {
                rx = 480;
            }
            ry = sy + stepY;
            if (ry > (u32)(sy + (endY - y))) {
                ry = sy + (endY - y);
            }
            if (ry > 240) {
                ry = 240;
            }
            rx <<= 2;
            ry <<= 2;
            /* gSPTextureRectangle written out: the upper-left corner is
             * computed after the first word is stored (a plain macro call
             * schedules sy << 2 after the x term). */
            {
                Gfx *_g = gfx++;
                s32 xl, yl;

                _g->words.w0 = _SHIFTL(G_TEXRECT, 24, 8) | _SHIFTL(rx, 12, 12) | _SHIFTL(ry, 0, 12);
                xl = sx << 2;
                yl = sy << 2;
                _g->words.w1 = _SHIFTL(G_TX_RENDERTILE, 24, 3) | _SHIFTL(xl, 12, 12) | _SHIFTL(yl, 0, 12);
                gImmp1(gfx++, G_RDPHALF_1, _SHIFTL((s32)(s * 32.0f), 16, 16) | _SHIFTL((s32)(t * 32.0f), 0, 16));
                gImmp1(gfx++, G_RDPHALF_2, _SHIFTL(1 << 10, 16, 16) | _SHIFTL(1 << 10, 0, 16));
            }
        }
    }
    *glistp = gfx;
}
