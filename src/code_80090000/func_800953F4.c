/* @header
 * func_800953F4
 * VRAM 0x800953F4 | ROM 0x41B64 | size 0x490
 * asm: asm/nonmatchings/code_80090000/func_800953F4.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx. */
typedef Gfx NwGfx;

/* PC: o is the picture that func_800B600C hands back (func_80095884), an entry of the resource-name cache: f4 is its
 * allocation, the texture, and fC, fE and f10 are the 16-bit sizes at +4, +6 and +8 of reserved, which the N64 reads at
 * +0xC, +0xE and +0x10. On PC the entry is common.h's Nw2ResourceEntryHashed, so Obj953 follows it, with the texture
 * as a pointer. */
typedef struct {
    u8 pad0[8];
    void *f4;
    u8 pad10[4];
    u16 fC;
    s16 fE;
    s16 f10;
} Obj953;
_Static_assert(offsetof(Obj953, f4) == offsetof(Nw2ResourceEntryHashed, allocation) &&
                   offsetof(Obj953, fC) == offsetof(Nw2ResourceEntryHashed, reserved) + 4 &&
                   offsetof(Obj953, fE) == offsetof(Nw2ResourceEntryHashed, reserved) + 6 &&
                   offsetof(Obj953, f10) == offsetof(Nw2ResourceEntryHashed, reserved) + 8,
               "Obj953 must follow Nw2ResourceEntryHashed");
#else
typedef struct {
    u32 w0;
    u32 w1;
} NwGfx;

typedef struct {
    u8 pad0[4];
    u32 f4;
    u8 pad8[4];
    u16 fC;
    s16 fE;
    s16 f10;
} Obj953;
#endif

#define NW_SHIFTL(v, s, w) ((unsigned int)(((unsigned int)(v) & ((0x01 << (w)) - 1)) << (s)))

#define nwSPModifyVertex(pkt, vtx, where, val) \
    { NwGfx *_g = (NwGfx *)(pkt); \
      _g->w0 = (NW_SHIFTL(0x02, 24, 8) | NW_SHIFTL((where), 16, 8) | NW_SHIFTL((vtx) * 2, 0, 16)); \
      _g->w1 = (unsigned int)(val); }

#define nwDPNoParam(pkt, cmd) \
    { NwGfx *_g = (NwGfx *)(pkt); _g->w0 = NW_SHIFTL(cmd, 24, 8); _g->w1 = 0; }

#ifdef TARGET_PC
/* PC: the texture's address goes into the command as the whole pointer: the call below passes DL_ADDR(o->f4), which
 * an unsigned int would cut to 32 bits. */
#define nwSetImage(pkt, cmd, fmt, siz, width, i) \
    { NwGfx *_g = (NwGfx *)(pkt); \
      _g->w0 = NW_SHIFTL(cmd, 24, 8) | NW_SHIFTL(fmt, 21, 3) | NW_SHIFTL(siz, 19, 2) | NW_SHIFTL((width) - 1, 0, 12); \
      _g->w1 = (uintptr_t)(i); }
#else
#define nwSetImage(pkt, cmd, fmt, siz, width, i) \
    { NwGfx *_g = (NwGfx *)(pkt); \
      _g->w0 = NW_SHIFTL(cmd, 24, 8) | NW_SHIFTL(fmt, 21, 3) | NW_SHIFTL(siz, 19, 2) | NW_SHIFTL((width) - 1, 0, 12); \
      _g->w1 = (unsigned int)(i); }
#endif

#define nwDPSetTile(pkt, fmt, siz, line, tmem, tile, palette, cmt, maskt, shiftt, cms, masks, shifts) \
    { NwGfx *_g = (NwGfx *)(pkt); \
      _g->w0 = NW_SHIFTL(0xF5, 24, 8) | NW_SHIFTL(fmt, 21, 3) | NW_SHIFTL(siz, 19, 2) | NW_SHIFTL(line, 9, 9) | NW_SHIFTL(tmem, 0, 9); \
      _g->w1 = NW_SHIFTL(tile, 24, 3) | NW_SHIFTL(palette, 20, 4) | NW_SHIFTL(cmt, 18, 2) | NW_SHIFTL(maskt, 14, 4) | NW_SHIFTL(shiftt, 10, 4) | NW_SHIFTL(cms, 8, 2) | NW_SHIFTL(masks, 4, 4) | NW_SHIFTL(shifts, 0, 4); }

#define nwDPLoadTileGeneric(pkt, c, tile, uls, ult, lrs, lrt) \
    { NwGfx *_g = (NwGfx *)(pkt); \
      _g->w0 = NW_SHIFTL(c, 24, 8) | NW_SHIFTL(uls, 12, 12) | NW_SHIFTL(ult, 0, 12); \
      _g->w1 = NW_SHIFTL(tile, 24, 3) | NW_SHIFTL(lrs, 12, 12) | NW_SHIFTL(lrt, 0, 12); }

#define nwDPLoadTextureTile_4b(pkt, timg, fmt, width, height, uls, ult, lrs, lrt, cms, cmt, masks, maskt, shifts, shiftt) \
    { \
        nwSetImage(pkt, 0xFD, fmt, 1, ((width) >> 1), timg); \
        nwDPSetTile(pkt, fmt, 1, (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), 0, 7, 0, cmt, maskt, shiftt, cms, masks, shifts); \
        nwDPNoParam(pkt, 0xE6); \
        nwDPLoadTileGeneric(pkt, 0xF4, 7, (uls) << 1, (ult) << 2, (lrs) << 1, (lrt) << 2); \
        nwDPNoParam(pkt, 0xE7); \
        nwDPSetTile(pkt, fmt, 0, (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), 0, 0, 0, cmt, maskt, shiftt, cms, masks, shifts); \
        nwDPLoadTileGeneric(pkt, 0xF2, 0, (uls) << 2, (ult) << 2, (lrs) << 2, (lrt) << 2); \
    }

#define nwSP1Triangle_w1(v0, v1, v2) \
    (NW_SHIFTL((v0) * 2, 16, 8) | NW_SHIFTL((v1) * 2, 8, 8) | NW_SHIFTL((v2) * 2, 0, 8))

#define nwSP1Quadrangle(pkt, v0, v1, v2, v3) \
    { NwGfx *_g = (NwGfx *)(pkt); \
      _g->w0 = (NW_SHIFTL(0x07, 24, 8) | nwSP1Triangle_w1(v0, v1, v2)); \
      _g->w1 = nwSP1Triangle_w1(v0, v2, v3); }

void func_800953F4(NwGfx **gpp, Obj953 *o, s32 x, s32 y, s32 w, s32 h)
{
    NwGfx *gp = *gpp;
    s32 step;
    s32 sw, dx, cx;
    s32 i, v;
    s32 uls, lrs;

    step = (o->fE < 24) ? 240 : 144;
    if (o->f10 >= step) {
        sw = w;
        dx = (sw * step) / o->f10;
    } else {
        sw = (w * o->f10) / step;
        dx = w;
    }
    cx = -sw / 2;
    v = 0;
    for (i = 0; i < o->f10; v += 2) {
        nwSPModifyVertex(gp++, v, 0x18, ((u32)((y - h / 2) << 18) >> 16) | ((x + cx) << 18));
        nwSPModifyVertex(gp++, v, 0x14, i << 21);
        nwSPModifyVertex(gp++, v + 1, 0x18, ((u32)((y + h / 2) << 18) >> 16) | ((x + cx) << 18));
        nwSPModifyVertex(gp++, v + 1, 0x14, ((u32)((o->fE - 1) << 21) >> 16) | (i << 21));
        cx += dx;
        i += step;
    }
    nwSPModifyVertex(gp++, v, 0x18, ((u32)((y - h / 2) << 18) >> 16) | ((x + sw / 2) << 18));
    nwSPModifyVertex(gp++, v, 0x14, (o->f10 - 1) << 21);
    nwSPModifyVertex(gp++, v + 1, 0x18, ((u32)((y + h / 2) << 18) >> 16) | ((x + sw / 2) << 18));
    nwSPModifyVertex(gp++, v + 1, 0x14, ((u32)((o->fE - 1) << 21) >> 16) | ((o->f10 - 1) << 21));
    v = 0;
    for (i = 0; i < o->f10; v += 2) {
        lrs = i + step + 1;
        uls = i - (i > 0);
        if (lrs >= o->f10) {
            lrs = o->f10 - 1;
        }
#ifdef TARGET_PC
        /* PC: the texture's address as the whole pointer (port.h's DL_ADDR). */
        nwDPLoadTextureTile_4b(gp++, DL_ADDR(o->f4), 2, (s16)o->fC, 0, uls, 0, lrs, o->fE - 1, 0, 0, 0, 0, 0, 0);
#else
        nwDPLoadTextureTile_4b(gp++, o->f4, 2, (s16)o->fC, 0, uls, 0, lrs, o->fE - 1, 0, 0, 0, 0, 0, 0);
#endif
        nwSP1Quadrangle(gp++, v, v + 2, v + 3, v + 1);
        i += step;
    }
    *gpp = gp;
}
