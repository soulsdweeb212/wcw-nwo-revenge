/* @header
 * func_80097BE0
 * VRAM 0x80097BE0 | ROM 0x8B080 | size 0x254
 * asm: asm/nonmatchings/ovl2_80090000/func_80097BE0.s
 */
#include "common.h"

typedef struct {
    u32 w0;
    u32 w1;
} G;

extern s16 D_800E2E98;
extern s16 D_800EB19C;
extern s16 D_800EB1A8;
extern s16 D_800EB1AA;

s32 func_8000DEE4(s32);
void func_800986DC(G **g, s16 *p);

#define EMIT(a, b) { G *d = g++; d->w0 = (a); d->w1 = (b); }

/* Darkens the screen and fills the bar rectangle ulx=239-y..lrx=y+240, rows 178..206. */
static inline void drawBar(G **pg, s16 y) {
    G *g = *pg;

    EMIT(0xFA000000, 0x80);
    EMIT(0xE200001C, 0x504240);
    EMIT(0xFCFFFFFF, 0xFFFDF6FB);
    EMIT(0xF6000000 | (((s16)(y + 0xF0) & 0x3FF) << 14) | (0xCE << 2), (((s16)(0xEF - y) & 0x3FF) << 14) | (0xB2 << 2));
    EMIT(0xE7000000, 0);
    *pg = g;
}

void func_80097BE0(G **dl) {
    G *g;
    s16 *t;

    if (D_800EB1A8 >= 0) {
        if (D_800EB1AA == 0) {
            D_800E2E98 = 0;
        }
        if (D_800E2E98 < 0xEF) {
            D_800E2E98 += 0x18;
            if (D_800E2E98 >= 0xF0) {
                D_800E2E98 = 0xEF;
                D_800EB19C = 0;
                func_8000DEE4(0x410);
            }
        }
        if (D_800EB1AA < 3) {
            D_800EB1AA++;
        } else {
            D_800EB1A8 = -1;
        }
        t = &D_800EB19C;
        g = *dl;
        drawBar(&g, D_800E2E98);
        if (*t != -1) {
            func_800986DC(&g, t);
        }
        *dl = g;
    } else if (D_800E2E98 > 0) {
        g = *dl;
        drawBar(&g, D_800E2E98);
        *dl = g;
        D_800E2E98 -= 0x18;
        if (D_800E2E98 < 0) {
            D_800E2E98 = 0;
        }
    }
}
