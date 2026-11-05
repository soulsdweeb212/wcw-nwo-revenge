/* @header
 * func_80099E2C
 * VRAM 0x80099E2C | ROM 0x8D2CC | size 0x144
 * asm: asm/nonmatchings/ovl2_80090000/func_80099E2C.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
typedef struct { u8 w; u8 h; } Meta;

void func_80006178(G **, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32);

#define GFX_CMD(pkt, a, b) { G *_g = (pkt); _g->w0 = (a); _g->w1 = (b); }

void func_80099E2C(G **dl, Meta *m, u32 pal, f32 x, f32 y) {
    G *g = *dl;

    GFX_CMD(g++, 0xFD100000, pal - 0x80000000);
    GFX_CMD(g++, 0xE8000000, 0);
    GFX_CMD(g++, 0xF5000100, 0x07000000);
    GFX_CMD(g++, 0xE6000000, 0);
    GFX_CMD(g++, 0xF0000000, 0x0703C000);
    GFX_CMD(g++, 0xE7000000, 0);
    func_80006178(&g, (u8 *)m + 0x80000008, 2, 0, m->w + 1, m->h + 1, 0x80, 0x10, 0, 0,
                  m->w, m->h + 1, x, y);
    GFX_CMD(g++, 0xE7000000, 0);
    *dl = g;
}
