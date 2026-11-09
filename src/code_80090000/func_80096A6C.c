/* @header
 * func_80096A6C
 * VRAM 0x80096A6C | ROM 0x431DC | size 0x320
 * asm: asm/nonmatchings/code_80090000/func_80096A6C.s
 */
#include "common.h"

#ifdef TARGET_PC
typedef Gfx Gfx96; /* on PC a command is port.h's 16-byte Gfx */
#else
typedef struct { u32 w0, w1; } Gfx96;
#endif

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((1 << (w)) - 1)) << (s)))

#ifdef TARGET_PC
/* On PC the texture address goes into the command as the whole pointer: the calls below pass DL_ADDR(texture), which
 * a (u32) cast would cut to 32 bits. */
#define gDPSetTextureImage(pkt, fmt, siz, width, i) { \
    Gfx96 *_g = (Gfx96 *)(pkt); \
    _g->w0 = _SHIFTL(0xFD, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) | _SHIFTL((width) - 1, 0, 12); \
    _g->w1 = (uintptr_t)(i); }
#else
#define gDPSetTextureImage(pkt, fmt, siz, width, i) { \
    Gfx96 *_g = (Gfx96 *)(pkt); \
    _g->w0 = _SHIFTL(0xFD, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) | _SHIFTL((width) - 1, 0, 12); \
    _g->w1 = (u32)(i); }
#endif

#define gDPSetTile(pkt, fmt, siz, line, tmem, tile, palette, cmt, maskt, shiftt, cms, masks, shifts) { \
    Gfx96 *_g = (Gfx96 *)(pkt); \
    _g->w0 = _SHIFTL(0xF5, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) | _SHIFTL(line, 9, 9) | _SHIFTL(tmem, 0, 9); \
    _g->w1 = _SHIFTL(tile, 24, 3) | _SHIFTL(palette, 20, 4) | _SHIFTL(cmt, 18, 2) | _SHIFTL(maskt, 14, 4) | _SHIFTL(shiftt, 10, 4) | _SHIFTL(cms, 8, 2) | _SHIFTL(masks, 4, 4) | _SHIFTL(shifts, 0, 4); }

#define gDPNoParam(pkt, cmd) { Gfx96 *_g = (Gfx96 *)(pkt); _g->w0 = _SHIFTL(cmd, 24, 8); _g->w1 = 0; }

#define gDPLoadTileGeneric(pkt, c, tile, uls, ult, lrs, lrt) { \
    Gfx96 *_g = (Gfx96 *)(pkt); \
    _g->w0 = _SHIFTL(c, 24, 8) | _SHIFTL(uls, 12, 12) | _SHIFTL(ult, 0, 12); \
    _g->w1 = _SHIFTL(tile, 24, 3) | _SHIFTL(lrs, 12, 12) | _SHIFTL(lrt, 0, 12); }

#define gDPLoadTextureTile(pkt, timg, fmt, siz, width, uls, ult, lrs, lrt, tb, lb) { \
    gDPSetTextureImage(pkt, fmt, 1, width, timg); \
    gDPSetTile(pkt, fmt, 1, ((((lrs) - (uls) + 1) * tb) + 7) >> 3, 0, 7, 0, 2, 0, 0, 2, 0, 0); \
    gDPNoParam(pkt, 0xE6); \
    gDPLoadTileGeneric(pkt, 0xF4, 7, (uls) << 2, (ult) << 2, (lrs) << 2, (lrt) << 2); \
    gDPNoParam(pkt, 0xE7); \
    gDPSetTile(pkt, fmt, siz, ((((lrs) - (uls) + 1) * lb) + 7) >> 3, 0, 0, 0, 2, 0, 0, 2, 0, 0); \
    gDPLoadTileGeneric(pkt, 0xF2, 0, (uls) << 2, (ult) << 2, (lrs) << 2, (lrt) << 2); }

void func_80096A6C(Gfx96 **out, void *texture, s32 format, s32 width, s32 height, s32 uls, s32 ult, s32 lrs, s32 lrt)
{
    Gfx96 *dl = *out;

    switch (format) {
    case 1:
#ifdef TARGET_PC
        gDPLoadTextureTile(dl++, DL_ADDR(texture), 3, 1, width, uls, ult, lrs, lrt, 1, 1);
#else
        gDPLoadTextureTile(dl++, (u32)texture - 0x80000000, 3, 1, width, uls, ult, lrs, lrt, 1, 1);
#endif
        break;
    case 2:
        {
#ifdef TARGET_PC
            gDPSetTextureImage(dl++, 0, 2, width, DL_ADDR(texture));
#else
            gDPSetTextureImage(dl++, 0, 2, width, (u32)texture - 0x80000000);
#endif
            gDPSetTile(dl++, 0, 2, ((((lrs) - (uls) + 1) * 2) + 7) >> 3, 0, 7, 0, 2, 0, 0, 2, 0, 0);
            gDPNoParam(dl++, 0xE6);
            gDPLoadTileGeneric(dl++, 0xF4, 7, (uls) << 2, (ult) << 2, (lrs) << 2, (lrt) << 2);
            gDPNoParam(dl++, 0xE7);
            gDPSetTile(dl++, 0, 2, ((((lrs) - (uls) + 1) * 2) + 7) >> 3, 0, 0, 0, 2, 0, 0, 2, 0, 0);
            gDPLoadTileGeneric(dl++, 0xF2, 0, (uls) << 2, (ult) << 2, (lrs) << 2, (lrt) << 2);
        }
        break;
    default:
#ifdef TARGET_PC
        gDPSetTextureImage(dl++, 3, 1, (width) >> 1, DL_ADDR(texture));
#else
        gDPSetTextureImage(dl++, 3, 1, (width) >> 1, (u32)texture - 0x80000000);
#endif
        gDPSetTile(dl++, 3, 1, (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), 0, 7, 0, 2, 0, 0, 2, 0, 0);
        gDPNoParam(dl++, 0xE6);
        gDPLoadTileGeneric(dl++, 0xF4, 7, (uls) << 1, (ult) << 2, (lrs) << 1, (lrt) << 2);
        gDPNoParam(dl++, 0xE7);
        gDPSetTile(dl++, 3, 0, (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), 0, 0, 0, 2, 0, 0, 2, 0, 0);
        gDPLoadTileGeneric(dl++, 0xF2, 0, (uls) << 2, (ult) << 2, (lrs) << 2, (lrt) << 2);
        break;
    }
    *out = dl;
}
