/* @header
 * buildCi4TextureDisplayList  (originally func_80011460)
 * VRAM 0x80011460 | ROM 0x12060 | size 0x304
 * asm: asm/nonmatchings/main/buildCi4TextureDisplayList.s
 */
#include "common.h"

/* Builds the RDP display list for a CI4 (4-bit colour-index) texture: sets the
 * color-combiner/other-mode, loads the TLUT palette and tile, sizes the tile with
 * the line/texel count, and closes the list. Returns the end of the list. */
#ifdef TARGET_PC
/* On PC a command is port.h's 16-byte Gfx, and palette is a pointer: it holds the palette's address, which a u32 would
 * cut in half. That makes Nw2Ci4Object 16 bytes on PC (8 on N64). */
typedef Gfx Nw2Gfx;
typedef struct { u32 f0; u8 cms, cmt, masks, maskt; } Nw2Ci4Texture;
typedef struct { Nw2Ci4Texture *tex; void *palette; } Nw2Ci4Object;
#else
typedef struct { u32 w0, w1; } Nw2Gfx;
typedef struct { u32 f0; u8 cms, cmt, masks, maskt; } Nw2Ci4Texture;
typedef struct { Nw2Ci4Texture *tex; u32 palette; } Nw2Ci4Object;
#endif

#define EmitCommand(a, b) { Nw2Gfx *g = dl++; g->w0 = (u32)(a); g->w1 = (u32)(b); }
#ifdef TARGET_PC
/* On PC an address goes into its command as the whole pointer (port.h's DL_ADDR); EmitCommand would cut it to 32
 * bits. */
#define EmitAddress(a, p) { Nw2Gfx *g = dl++; g->w0 = (u32)(a); g->w1 = DL_ADDR(p); }
#endif

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
#ifdef TARGET_PC
    EmitAddress(0xFD100000, obj->palette);
#else
    EmitCommand(0xFD100000, obj->palette - 0x80000000);
#endif
    EmitCommand(0xE8000000, 0);
    EmitCommand(0xF5000100, 0x07000000);
    EmitCommand(0xE6000000, 0);
    EmitCommand(0xF0000000, 0x0703C000);
    EmitCommand(0xE7000000, 0);
#ifdef TARGET_PC
    /* The texels start 8 bytes into the texture, after its header (Nw2Ci4Texture). */
    EmitAddress(0xFD500000, (u8 *)obj->tex + 8);
#else
    EmitCommand(0xFD500000, (u32)obj->tex + 0x80000008);
#endif
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
