/* @header
 * buildTiledTextureDisplayList  (originally func_80097184)
 * VRAM 0x80097184 | ROM 0x438F4 | size 0x5B8
 * asm: asm/nonmatchings/code_80090000/buildTiledTextureDisplayList.s
 */
#include "common.h"

/* buildTiledTextureDisplayList: draws a texture over a destination rectangle by
 * splitting the source image into 64x48 (or 64x24 for the alternate format)
 * tiles and emitting a textured quad per tile, clipping tiles that fall entirely
 * outside the 480x240 screen.  scaleX/scaleY map source pixels to destination
 * pixels. */

#ifdef TARGET_PC
/* PC: the display list at 0x800C95B8 by its own address (port.h's DL_ADDR turns it into the command word; D_C95B8 is
 * its N64 physical address, a link constant). func_80096A6C takes the texture as a pointer, as its definition does. */
extern u8 D_800C95B8[];
void func_80096A6C(Nw2RdpCmd **, void *, s32, s32, s32, s32, s32, s32, s32);
#else
extern u8 D_C95B8[];
void func_80096A6C(Nw2RdpCmd **, s32, s32, s32, s32, s32, s32, s32, s32);
#endif
#define EMIT_X(a, b) { Nw2RdpCmd *g = dl++; g->w0 = (a); g->w1 = ((unsigned short)b); }

#ifdef TARGET_PC
/* PC: the texture is an address, so a pointer: its callers pass the texture's own address, and an s32 would cut it to
 * 32 bits. */
void buildTiledTextureDisplayList(Nw2RdpCmd **out, void *texture, s32 format, s32 x, s32 y,
                                  s32 width, s32 height, s32 drawWidth, s32 drawHeight, s32 mode) {
#else
void buildTiledTextureDisplayList(Nw2RdpCmd **out, s32 texture, s32 format, s32 x, s32 y,
                                  s32 width, s32 height, s32 drawWidth, s32 drawHeight, s32 mode) {
#endif
    Nw2RdpCmd *dl = *out;
    register f32 scaleY = (f64)drawHeight / height;
    register f32 scaleX = (f64)drawWidth / width;
    int tileHeight = 48, tileWidth = 64;
    f32 x0, x1, y0, y1;
    s32 tileY, tileX, right, bottom, loadLeft, loadTop, loadRight, loadBottom;
    if (format)
        tileHeight = 24;
#ifdef TARGET_PC
    /* PC: the branch target as the whole pointer (port.h's DL_ADDR). */
    { Nw2RdpCmd *g = dl++; g->w0 = 0xDE000000; g->w1 = DL_ADDR(D_800C95B8); }
#else
    { Nw2RdpCmd *g = dl++; g->w0 = 0xDE000000; g->w1 = (u32)D_C95B8; }
#endif
    for (tileY = 0; tileY <= height; tileY += tileHeight) {
        for (tileX = 0; tileX <= width; tileX += tileWidth) {
            loadLeft = tileX - 1; if (loadLeft < 0) loadLeft = 0;
            loadTop = tileY - 1; if (loadTop < 0) loadTop = 0;
            loadRight = tileX + tileWidth; if (loadRight > width - 1) loadRight = width - 1;
            loadBottom = tileY + tileHeight; if (loadBottom > height - 1) loadBottom = height - 1;
            right = tileX + tileWidth - 1; if (right > width - 1) right = width - 1;
            bottom = tileY + tileHeight - 1; if (bottom > height - 1) bottom = height - 1;
            x1 = (f32)x + (tileX + tileWidth) * scaleX;
            x0 = (f32)x + tileX * scaleX;
            y0 = (f32)y + tileY * scaleY;
            if (!(x1 <= (f32)(x + drawWidth))) x1 = x + drawWidth;
            y1 = (f32)y + (tileY + tileHeight) * scaleY;
            if (!(y1 <= (f32)(y + drawHeight))) y1 = y + drawHeight;
            if ((x0 < 0.f) & (x1 < 0.f)) continue;
            if ((y0 < 0.f) & (y1 < 0.f)) continue;
            if ((x0 >= 480.f) & (x1 >= 480.f)) continue;
            if ((y0 >= 240.f) & (y1 >= 240.f)) continue;
            if ((x0 == x1) | (y0 == y1)) continue;
            EMIT_X(0xE7000000, 0);
            func_80096A6C(&dl, texture, format, mode, height, loadLeft, loadTop, loadRight, loadBottom);
            EMIT_X(0x02180000, ((s32)(y0 * 4.f) & 0xFFFF) | ((s32)(x0 * 4.f) << 16));
            EMIT_X(0x02180002, ((s32)(y0 * 4.f) & 0xFFFF) | ((s32)(x1 * 4.f) << 16));
            EMIT_X(0x02180004, ((s32)(y1 * 4.f) & 0xFFFF) | ((s32)(x0 * 4.f) << 16));
            EMIT_X(0x02180006, ((s32)(y1 * 4.f) & 0xFFFF) | ((s32)(x1 * 4.f) << 16));
            EMIT_X(0x02140000, ((u32)(tileY << 21) >> 16) | (tileX << 21));
            EMIT_X(0x02140002, ((u32)(tileY << 21) >> 16) | (right << 21));
            EMIT_X(0x02140004, ((u32)(bottom << 21) >> 16) | (tileX << 21));
            EMIT_X(0x02140006, ((u32)(bottom << 21) >> 16) | (right << 21));
            EMIT_X(0x07000206, 0x604);
        }
    }
    *out = dl;
}
#undef EMIT_X
