/* @header
 * func_80098960
 * VRAM 0x80098960 | ROM 0x8BE00 | size 0x304
 * asm: asm/nonmatchings/ovl2_80090000/func_80098960.s
 */
#include "common.h"

#ifdef TARGET_PC
/* On PC a command is port.h's 16-byte Gfx, as in func_80099628.c, which allocates these lists (D_800EB29C), and
 * func_80098D54.c and func_80099E2C.c, which write into them. */
typedef Gfx G;
#else
typedef struct {
    u32 w0, w1;
} G;
#endif

#define _SHIFTL(v, s, w) ((unsigned int)(((unsigned int)(v) & ((0x01 << (w)) - 1)) << (s)))
#define EMIT(a, b) { G *_g = g++; _g->w0 = (a); _g->w1 = (b); }
#define gDPFillRectangle(ulx, uly, lrx, lry) \
    EMIT(_SHIFTL(0xF6, 24, 8) | _SHIFTL(lrx, 14, 10) | _SHIFTL(lry, 2, 10), \
         _SHIFTL(ulx, 14, 10) | _SHIFTL(uly, 2, 10))

extern s8 D_800E2F48[];
extern s8 D_800E2F4F;

s32 func_80098960(G **dl, s16 dir) {
    s32 r = 0;
    G *g = *dl;

    EMIT(0xFA000000, 0x80);
    EMIT(0xE200001C, 0x504240);
    EMIT(0xFCFFFFFF, 0xFFFDF6FB);
    gDPFillRectangle(155, 0x73 - D_800E2F48[D_800E2F4F], 240, 120);
    gDPFillRectangle(240, 0x73 - D_800E2F48[D_800E2F4F], 325, 120);
    gDPFillRectangle(155, 120, 240, D_800E2F48[D_800E2F4F] + 0x7D);
    gDPFillRectangle(240, 120, 325, D_800E2F48[D_800E2F4F] + 0x7D);
    gDPFillRectangle(0xE6 - D_800E2F48[D_800E2F4F] * 3, 183, D_800E2F48[D_800E2F4F] * 3 + 0xFA, 200);
    gDPFillRectangle(0xF0 - D_800E2F48[D_800E2F4F] * 2, 41, D_800E2F48[D_800E2F4F] * 2 + 0xF0, 58);
    EMIT(0xE7000000, 0);
    EMIT(0xE200001C, 0x0F0A7008);
    *dl = g;
    if (dir == 1) {
        D_800E2F4F++;
        if (D_800E2F4F >= 7) {
            D_800E2F4F = 6;
            r = 1;
        }
    } else {
        D_800E2F4F--;
        if (D_800E2F4F < 0) {
            D_800E2F4F = 0;
            r = 1;
        }
    }
    return r;
}
