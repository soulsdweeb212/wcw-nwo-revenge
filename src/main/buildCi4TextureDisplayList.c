/* @header
 * buildCi4TextureDisplayList  (originally func_80011460)
 * VRAM 0x80011460 | ROM 0x12060 | size 0x304
 * asm: asm/nonmatchings/main/func_80011460.s
 */
#include "common.h"

/* Builds the RDP display list for a CI4 (4-bit colour-index) texture: sets the
 * color-combiner/other-mode, loads the TLUT palette and tile, sizes the tile with
 * the line/texel count, and closes the list. Returns the end of the list. */
typedef struct { u32 w0, w1; } Nw2Gfx;
typedef struct { u32 f0; u8 cms, cmt, masks, maskt; } Nw2Ci4Texture;
typedef struct { Nw2Ci4Texture *tex; u32 palette; } Nw2Ci4Object;

#define EmitCommand(a, b) { Nw2Gfx *g = dl++; g->w0 = (u32)(a); g->w1 = (u32)(b); }

Nw2Gfx *buildCi4TextureDisplayList(Nw2Ci4Object *obj, Nw2Gfx *out, u16 mode)
{
    u8 cms, cmt, masks, maskt;
    u32 w;
    s32 h;
    Nw2Gfx *dl = out;

    cms = obj->tex->cms; cmt = obj->tex->cmt; masks = obj->tex->masks; maskt = obj->tex->maskt;
    w = 1 << masks; h = 1 << maskt;

    EmitCommand(0xE200001C, 0x504340);
    if (mode != 6) { EmitCommand(0xE2001E01, 3); }
    EmitCommand(0xFC119623, 0xFF2FFFFF);
    EmitCommand(0xFD100000, obj->palette - 0x80000000);
    EmitCommand(0xE8000000, 0);
    EmitCommand(0xF5000100, 0x07000000);
    EmitCommand(0xE6000000, 0);
    EmitCommand(0xF0000000, 0x0703C000);
    EmitCommand(0xE7000000, 0);
    EmitCommand(0xFD500000, (u32)obj->tex + 0x80000008);
    { u32 tile = (((maskt & 15) << 14) | 0x07000000);
      EmitCommand(0xF5500000, ((cmt & 3) << 18) | tile | ((cms & 3) << 8) | ((masks & 15) << 4)); }
    EmitCommand(0xE6000000, 0);
    { Nw2Gfx *g = dl++;
      u32 line = w >> 4;
      u32 numerator = 0x800;
      u32 count;
      g->w0 = 0xF3000000;
      if (line) numerator = line + 0x7FF;
      count = (((w * h) + 3) >> 2) - 1;
      if (count >= 0x800) count = 0x7FF;
      g->w1 = ((count & 0xFFF) << 12) | 0x07000000 | ((line ? numerator / line : numerator) & 0xFFF); }
    EmitCommand(0xE7000000, 0);
    EmitCommand(0xF5400000 | (((((w >> 1) + 7) >> 3) & 0x1FF) << 9),
                ((cmt & 3) << 18) | ((maskt & 15) << 14) | ((cms & 3) << 8) | ((masks & 15) << 4));
    EmitCommand(0xF2000000, ((((w - 1) * 4) & 0xFFF) << 12) | (((h - 1) * 4) & 0xFFF));
    dl->w0 = 0xDF000000;
    dl->w1 = 0;
    return dl;
}
