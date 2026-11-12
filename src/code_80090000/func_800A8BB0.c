/* @header
 * func_800A8BB0
 * VRAM 0x800A8BB0 | ROM 0x55320 | size 0x340
 * asm: asm/nonmatchings/code_80090000/func_800A8BB0.s
 */
#include "common.h"


#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx. D_800CB7B8's records hold two addresses (a display list, then the vertices),
 * so they are pointers on PC, as the other files that read the table declare them (VtxSet in func_8009FE3C). */
typedef Gfx G;
typedef struct { void *dl; u8 *vtx; u16 n; u8 padA[6]; } Mdl;
#else
typedef struct { u32 w0, w1; } G;
typedef struct { u8 pad0[4]; u8 *vtx; u8 pad8[8]; } Mdl;
#endif
typedef struct { u8 pad0[0xE]; u8 idx; } Def;
typedef struct { u8 pad0[0x24]; Def *def; } Obj;

extern Mdl D_800CB7B8[];
#ifdef TARGET_PC
/* PC: func_800B6F88 hands back the texture's and the palette's addresses (u8 ** in its definition). */
s32 func_800B6F88(s32, u8 **, u8 **);
#else
s32 func_800B6F88(s32, s32 *, s32 *);
#endif

#define SHL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define PHYS(x) ((u32)((char *)(x) - 0x80000000))
#define TRI_W1(v0, v1, v2) (SHL((v0) * 2, 16, 8) | SHL((v1) * 2, 8, 8) | SHL((v2) * 2, 0, 8))
#define TRI_W1F(v0, v1, v2, f) (((f) == 0) ? TRI_W1(v0, v1, v2) : ((f) == 1) ? TRI_W1(v1, v2, v0) : TRI_W1(v2, v0, v1))
#define SP2TRI(g, a0, a1, a2, f0, b0, b1, b2, f1) { G *_g = (g); _g->w0 = (TRI_W1F(a0, a1, a2, f0) | c); _g->w1 = TRI_W1F(b0, b1, b2, f1); }
#define EMIT(a, b) { G *_g = g++; _g->w0 = (a); _g->w1 = (b); }
#ifdef TARGET_PC
/* PC: the second word as wide as a pointer; the callers pass the texture's address through DL_ADDR. */
#define SETTIMG(g, fmt, siz, w, i) { G *_g = (g); _g->w0 = SHL(0xFD, 24, 8) | SHL(fmt, 21, 3) | SHL(siz, 19, 2) | SHL((w) - 1, 0, 12); _g->w1 = (i); }
#else
#define SETTIMG(g, fmt, siz, w, i) { G *_g = (g); _g->w0 = SHL(0xFD, 24, 8) | SHL(fmt, 21, 3) | SHL(siz, 19, 2) | SHL((w) - 1, 0, 12); _g->w1 = (u32)(i); }
#endif
#define SETTILE(g, fmt, siz, line, tmem, tile, pal, cmt, maskt, shiftt, cms, masks, shifts) { G *_g = (g); _g->w0 = SHL(0xF5, 24, 8) | SHL(fmt, 21, 3) | SHL(siz, 19, 2) | SHL(line, 9, 9) | SHL(tmem, 0, 9); _g->w1 = SHL(tile, 24, 3) | SHL(pal, 20, 4) | SHL(cmt, 18, 2) | SHL(maskt, 14, 4) | SHL(shiftt, 10, 4) | SHL(cms, 8, 2) | SHL(masks, 4, 4) | SHL(shifts, 0, 4); }
#define NOPARAM(g, c) { G *_g = (g); _g->w0 = SHL(c, 24, 8); _g->w1 = 0; }
#define LOADTILE(g, tile, uls, ult, lrs, lrt) { G *_g = (g); _g->w0 = SHL(0xF4, 24, 8) | SHL(uls, 12, 12) | SHL(ult, 0, 12); _g->w1 = SHL(lrs, 12, 12) | (SHL(lrt, 0, 12) | c); }
#define SETTILESIZE(g, tile, uls, ult, lrs, lrt) { G *_g = (g); _g->w0 = SHL(0xF2, 24, 8) | SHL(uls, 12, 12) | SHL(ult, 0, 12); _g->w1 = SHL(tile, 24, 3) | SHL(lrs, 12, 12) | SHL(lrt, 0, 12); }
#define LOADTEXTILE_4b(g, timg, fmt, width, height, uls, ult, lrs, lrt, pal, cms, cmt, masks, maskt, shifts, shiftt) \
    { \
        SETTIMG(g++, fmt, 1, ((width) >> 1), timg); \
        SETTILE(g++, fmt, 1, (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), 0, 7, 0, cmt, maskt, shiftt, cms, masks, shifts); \
        NOPARAM(g++, 0xE6); \
        LOADTILE(g++, 7, (uls) << 1, (ult) << 2, (lrs) << 1, (lrt) << 2); \
        NOPARAM(g++, 0xE7); \
        SETTILE(g++, fmt, 0, (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), 0, 0, pal, cmt, maskt, shiftt, cms, masks, shifts); \
        SETTILESIZE(g++, 0, (uls) << 2, (ult) << 2, (lrs) << 2, (lrt) << 2); \
    }

#ifdef TARGET_PC
/* PC: the texture and the palette are addresses, so pointers, and every address goes into a command as the whole
 * pointer (port.h's DL_ADDR), where the N64 subtracts 0x80000000 in 32 bits (PHYS) or casts to a u32. */
void func_800A8BB0(G **dl, Obj *o) {
    G *g = *dl;
    u8 *vtx = D_800CB7B8[o->def->idx].vtx;
    u8 *tex, *pal;
    s32 x, y, x0, x1, y0, y1;
    u8 *v;
    u32 c;

    if (func_800B6F88(9, &tex, &pal)) {
        EMIT(0xFC5196A3, 0x112CFE7F);
        EMIT(0xE2001E01, 0);
        SETTIMG(g++, 0, 2, 1, DL_ADDR(pal));
        NOPARAM(g++, 0xE8);
        SETTILE(g++, 0, 0, 0, 256, 7, 0, 0, 0, 0, 0, 0, 0);
        NOPARAM(g++, 0xE6);
        { G *_g = g++; _g->w0 = SHL(0xF0, 24, 8); _g->w1 = SHL(7, 24, 3) | SHL(15, 14, 10); }
        NOPARAM(g++, 0xE7);
        c = 0x07000000;
        for (y = 0; y < 0xF0; y += 0x30) {
            EMIT(0x0100C018, DL_ADDR(vtx + y * 2));
            for (x = 0; x < 5; x++) {
                uptr t = DL_ADDR(tex);
                x0 = x * 64 - 1;
                if (x0 < 0) {
                    x0 = 0;
                }
                x1 = x * 64 + 0x41;
                if (x1 >= 0x140) {
                    x1 = 0x13F;
                }
                y0 = y - 1;
                if (y0 < 0) {
                    y0 = 0;
                }
                y1 = y + 0x31;
                if (y1 >= 0xF0) {
                    y1 = 0xEF;
                }
                LOADTEXTILE_4b(g, t, 3, 320, 240, x0, y0, x1, y1, 0, 2, 2, 0, 0, 0, 0);
                SP2TRI(g++, x, x + 1, x + 7, 0, x, x + 7, x + 6, 0);
            }
        }
    }
    EMIT(0xDF000000, 0);
    *dl = g;
}
#else
void func_800A8BB0(G **dl, Obj *o) {
    G *g = *dl;
    u8 *vtx = D_800CB7B8[o->def->idx].vtx;
    s32 tex, pal;
    s32 x, y, x0, x1, y0, y1;
    u8 *v;
    u32 c;

    if (func_800B6F88(9, &tex, &pal)) {
        EMIT(0xFC5196A3, 0x112CFE7F);
        EMIT(0xE2001E01, 0);
        SETTIMG(g++, 0, 2, 1, PHYS(pal));
        NOPARAM(g++, 0xE8);
        SETTILE(g++, 0, 0, 0, 256, 7, 0, 0, 0, 0, 0, 0, 0);
        NOPARAM(g++, 0xE6);
        { G *_g = g++; _g->w0 = SHL(0xF0, 24, 8); _g->w1 = SHL(7, 24, 3) | SHL(15, 14, 10); }
        NOPARAM(g++, 0xE7);
        c = 0x07000000;
        for (y = 0; y < 0xF0; y += 0x30) {
            EMIT(0x0100C018, (u32)(vtx + y * 2));
            for (x = 0; x < 5; x++) {
                u32 t = PHYS(tex);
                x0 = x * 64 - 1;
                if (x0 < 0) {
                    x0 = 0;
                }
                x1 = x * 64 + 0x41;
                if (x1 >= 0x140) {
                    x1 = 0x13F;
                }
                y0 = y - 1;
                if (y0 < 0) {
                    y0 = 0;
                }
                y1 = y + 0x31;
                if (y1 >= 0xF0) {
                    y1 = 0xEF;
                }
                LOADTEXTILE_4b(g, t, 3, 320, 240, x0, y0, x1, y1, 0, 2, 2, 0, 0, 0, 0);
                SP2TRI(g++, x, x + 1, x + 7, 0, x, x + 7, x + 6, 0);
            }
        }
    }
    EMIT(0xDF000000, 0);
    *dl = g;
}
#endif
