#include "common.h"

/* buildCiTextureDisplayList: emits the RDP display list for a color-index
 * texture object.  It derives the tile dimensions from the texture's clamp
 * masks, emits the optional 2D-primitive cull command, then loads the palette,
 * tile descriptor and texture image (4-bit or 8-bit depending on the format
 * mode), and finally appends a branch to the next display list. */

#define EMIT(a, b) { Nw2RdpCmd *g = dl++; g->w0 = (u32)(a); g->w1 = (u32)(b); }
#define TILE_CMD(tile) ((((u32)clampT & 3) << 18) | (tile) | (((u32)maskT & 15) << 14) | (((u32)clampS & 3) << 8) | (((u32)maskS & 15) << 4))
#define LOAD_TEXTURE(pal, divisor, add, shift, fmt, line) \
    EMIT(0xFD100000, obj->palette - 0x80000000); \
    EMIT(0xE8000000, 0); EMIT(0xF5000100, 0x07000000); EMIT(0xE6000000, 0); EMIT(0xF0000000, pal); EMIT(0xE7000000, 0); \
    EMIT(0xFD500000, (u32)obj->tex + 0x80000008); EMIT(0xF5500000, TILE_CMD(0x07000000)); EMIT(0xE6000000, 0); \
    { Nw2RdpCmd *g = dl++; s32 numerator; s32 count; g->w0 = 0xF3000000; \
      if ((s16)obj->width / divisor > 0) numerator = (s16)obj->width / divisor + 0x7FF; else numerator = 0x800; \
      count = ((((s16)obj->width) * ((s16)obj->height) + add) >> shift) - 1; if (count >= 0x800) count = 0x7FF; \
      g->w1 = ((count & 0xFFF) << 12) | 0x07000000 | ((((s16)obj->width / divisor) > 0) ? numerator / ((s16)obj->width / divisor) : numerator) & 0xFFF; } \
    EMIT(0xE7000000, 0); EMIT(fmt | (((((line) + 7) >> 3) & 0x1FF) << 9), TILE_CMD(0)); \
    EMIT(0xF2000000, ((((((s16)obj->width - 1) * 4) & 0xFFF) << 12) | ((((s16)obj->height - 1) * 4) & 0xFFF)));

Nw2RdpCmd *buildCiTextureDisplayList(Nw2TextureDisplayObj *obj, s16 mode) {
    u8 clampS, clampT, maskS, maskT;
    Nw2RdpCmd *dl = obj->dl;
    clampS = obj->tex->clampS;
    clampT = obj->tex->clampT;
    maskS = obj->tex->maskS;
    maskT = obj->tex->maskT;
    obj->width = (u16)(1 << maskS);
    obj->height = (u16)(1 << maskT);
    if (mode == 0) {
        EMIT(0xE200001C, 0x0F0A7008);
        EMIT(0xFC15FE2B, 0xFFFFF3F9);
    } else if (obj->colorPtr != 0) {
        if (obj->count < 9) {
            Nw2RdpCmd *g = dl++;
            g->w0 = ((u32)(obj->first * 2) & 0xFFFF) | 0x03000000;
            g->w1 = (u32)((obj->first + obj->count) * 2) & 0xFFFF;
        }
    }
    if (obj->tex->mode != 1) {
        LOAD_TEXTURE(0x0703C000, 16, 3, 2, 0xF5400000, ((s16)obj->width >> 1));
    } else {
        LOAD_TEXTURE(0x073FC000, 8, 1, 1, 0xF5480000, (s16)obj->width);
    }
    if (obj->next) {
        dl->w0 = 0xDE010000;
        dl->w1 = (u32)obj->next - 0x80000000;
    } else {
        dl->w0 = 0xDF000000;
        dl->w1 = 0;
    }
    return dl;
}
