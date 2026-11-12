/* @header
 * func_800B6548
 * VRAM 0x800B6548 | ROM 0x62CB8 | size 0x3F0
 * asm: asm/nonmatchings/code_80090000/func_800B6548.s
 */
#include "common.h"

#ifdef TARGET_PC
typedef Gfx G; /* PC: a command is port.h's 16-byte Gfx, which keeps a whole pointer in w1 */
#else
typedef struct { u32 w0, w1; } G;
#endif

#define SHL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define MAXI(a, b) ((a) > (b) ? (a) : (b))
#define MINI(a, b) ((a) < (b) ? (a) : (b))
#ifdef TARGET_PC
#define PHYS(x) DL_ADDR(x) /* PC: the palette's or texture's address as the whole pointer (port.h's DL_ADDR) */
#else
#define PHYS(x) ((u32)((char *)(x) - 0x80000000))
#endif
#define TXL2WORDS(t, b) MAXI(1, ((t) * (b) / 8))
#define CALC_DXT(w, b) (((1 << 11) + TXL2WORDS(w, b) - 1) / TXL2WORDS(w, b))
#define TXL2WORDS_4b(t) MAXI(1, ((t) / 16))
#define CALC_DXT_4b(w) (((1 << 11) + TXL2WORDS_4b(w) - 1) / TXL2WORDS_4b(w))
#ifdef TARGET_PC
/* PC: w1 takes the whole address that PHYS gives; a (u32) cast would cut it in half. */
#define SETTIMG(g, fmt, siz, w, i) { G *_g = (g); _g->w0 = SHL(0xFD, 24, 8) | SHL(fmt, 21, 3) | SHL(siz, 19, 2) | SHL((w) - 1, 0, 12); _g->w1 = (i); }
#else
#define SETTIMG(g, fmt, siz, w, i) { G *_g = (g); _g->w0 = SHL(0xFD, 24, 8) | SHL(fmt, 21, 3) | SHL(siz, 19, 2) | SHL((w) - 1, 0, 12); _g->w1 = (u32)(i); }
#endif
#define SETTILE(g, fmt, siz, line, tmem, tile, pal) { G *_g = (g); _g->w0 = SHL(0xF5, 24, 8) | SHL(fmt, 21, 3) | SHL(siz, 19, 2) | SHL(line, 9, 9) | SHL(tmem, 0, 9); _g->w1 = SHL(tile, 24, 3) | SHL(pal, 20, 4); }
#define NOPARAM(g, c) { G *_g = (g); _g->w0 = SHL(c, 24, 8); _g->w1 = 0; }
#define LOADBLOCK(g, tile, lrs, dxt) { G *_g = (g); _g->w0 = SHL(0xF3, 24, 8); _g->w1 = SHL(tile, 24, 3) | SHL(MINI(lrs, 0x7FF), 12, 12) | SHL(dxt, 0, 12); }
#define LOADTLUT(g, tile, count) { G *_g = (g); _g->w0 = SHL(0xF0, 24, 8); _g->w1 = SHL(tile, 24, 3) | SHL(count, 14, 10); }
#define SETTILESIZE(g, tile, lrs, lrt) { G *_g = (g); _g->w0 = SHL(0xF2, 24, 8); _g->w1 = SHL(tile, 24, 3) | SHL(lrs, 12, 12) | SHL(lrt, 0, 12); }

#ifdef TARGET_PC
/* PC: img and pal are the texture's and the palette's addresses, so pointers, as the callers (func_800B6D68,
 * func_800B6FE0, func_800B7260 and others) declare them; an s32 would cut each in half. */
void func_800B6548(G **dl, s32 flag, s32 w, s32 h, u8 *img, u8 *pal) {
#else
void func_800B6548(G **dl, s32 flag, s32 w, s32 h, s32 img, s32 pal) {
#endif
    G *g = *dl;

    if (flag & 1) {
        SETTIMG(g++, 0, 2, 1, PHYS(pal));
        NOPARAM(g++, 0xE8);
        SETTILE(g++, 0, 0, 0, 256, 7, 0);
        NOPARAM(g++, 0xE6);
        LOADTLUT(g++, 7, 255);
        NOPARAM(g++, 0xE7);
        SETTIMG(g++, 2, 2, 1, PHYS(img));
        SETTILE(g++, 2, 2, 0, 0, 7, 0);
        NOPARAM(g++, 0xE6);
        LOADBLOCK(g++, 7, (((w * h) + 1) >> 1) - 1, CALC_DXT(w, 1));
        NOPARAM(g++, 0xE7);
        SETTILE(g++, 2, 1, ((w * 1) + 7) >> 3, 0, 0, 0);
        SETTILESIZE(g++, 0, (w - 1) << 2, (h - 1) << 2);
    } else {
        SETTIMG(g++, 0, 2, 1, PHYS(pal));
        NOPARAM(g++, 0xE8);
        SETTILE(g++, 0, 0, 0, 256, 7, 0);
        NOPARAM(g++, 0xE6);
        LOADTLUT(g++, 7, 15);
        NOPARAM(g++, 0xE7);
        SETTIMG(g++, 2, 2, 1, PHYS(img));
        SETTILE(g++, 2, 2, 0, 0, 7, 0);
        NOPARAM(g++, 0xE6);
        LOADBLOCK(g++, 7, (((w * h) + 3) >> 2) - 1, CALC_DXT_4b(w));
        NOPARAM(g++, 0xE7);
        SETTILE(g++, 2, 0, (((w) >> 1) + 7) >> 3, 0, 0, 0);
        SETTILESIZE(g++, 0, (w - 1) << 2, (h - 1) << 2);
    }
    *dl = g;
}
