/* @header
 * func_80099E2C
 * VRAM 0x80099E2C | ROM 0x8D2CC | size 0x144
 * asm: asm/nonmatchings/ovl2_80090000/func_80099E2C.s
 */
#include "common.h"

#ifdef TARGET_PC
typedef Gfx G; /* on PC a command is port.h's 16-byte Gfx, which keeps a whole pointer in w1 */
#else
typedef struct { u32 w0, w1; } G;
#endif
typedef struct { u8 w; u8 h; } Meta;

#ifndef TARGET_PC /* on PC, port_decls.h declares func_80006178, which takes the list as Gfx ** */
void func_80006178(G **, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32);
#endif

#define GFX_CMD(pkt, a, b) { G *_g = (pkt); _g->w0 = (a); _g->w1 = (b); }

#ifdef TARGET_PC
/* PC: pal is the palette's address, which the callers (func_80098D54, func_80098C64, func_80098CE8) pass as a pointer
 * and which a u32 would cut in half; it goes into the palette command whole (port.h's DL_ADDR). The picture's pixels
 * start 8 bytes into m, after its header, and func_80006178 takes their own address on PC; the N64 passes m + 8 plus
 * 0x80000000, which the function subtracts again. */
void func_80099E2C(G **dl, Meta *m, void *pal, f32 x, f32 y) {
    G *g = *dl;

    GFX_CMD(g++, 0xFD100000, DL_ADDR(pal));
    GFX_CMD(g++, 0xE8000000, 0);
    GFX_CMD(g++, 0xF5000100, 0x07000000);
    GFX_CMD(g++, 0xE6000000, 0);
    GFX_CMD(g++, 0xF0000000, 0x0703C000);
    GFX_CMD(g++, 0xE7000000, 0);
    func_80006178(&g, (u8 *)m + 8, 2, 0, m->w + 1, m->h + 1, 0x80, 0x10, 0, 0,
                  m->w, m->h + 1, x, y);
    GFX_CMD(g++, 0xE7000000, 0);
    *dl = g;
}
#else
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
#endif
