/* @header
 * func_80098560
 * VRAM 0x80098560 | ROM 0x8BA00 | size 0x17C
 * asm: asm/nonmatchings/ovl2_80090000/func_80098560.s
 */
#include "common.h"

typedef struct {
    u32 w0;
    u32 w1;
} G;

typedef struct {
    s32 flags;
} Node;

/* Current display-list buffer (0..2). Its own scalar symbol (new build.json entry, 0x800E2E9A):
 * as D_800E2E98+2 the address is forced into a register and CSE shares it. */
extern u8 D_800E2E9A;
#ifndef TARGET_PC /* on PC, port_decls.h declares D_800EB0C0 */
extern G *D_800EB0C0;
#endif
extern Node *D_800EB0C4;
extern G *D_800EB18C[3];
typedef struct {
    s16 id; /* -1 = none */
    s16 scale;
    s16 x;
    s16 y;
    void *tex; /* D_800EB1B4 */
} Icon;

extern Icon D_800EB1AC;
extern u16 D_800EB1BC;
extern s16 D_800EB1BE;

void func_80097BE0(G **);
void func_800986DC(G **, Icon *);
s8 func_800D633C(void);

/* the 4-byte frame gap between g and g2 comes from g2 being an inline's local */
static inline void drawExtra(G **pg) {
    G *g2 = *pg;

    func_800986DC(&g2, &D_800EB1AC);
    *pg = g2;
}

s32 func_80098560(void) {
    G *g;

    if (D_800EB1BC == 0) {
        g = D_800EB18C[D_800E2E9A];
        func_80097BE0(&g);
        if (D_800EB1BE >= 0) {
            D_800EB1BC = 1;
            drawExtra(&g);
        }
        if (g == D_800EB18C[D_800E2E9A]) {
            D_800EB0C4->flags |= 0x80;
        } else {
            D_800EB0C4->flags &= ~0x80;
        }
        g->w0 = 0xDF000000;
        g->w1 = 0;
        g++;
        D_800EB0C0 = D_800EB18C[D_800E2E9A++];
        D_800E2E9A %= 3;
    } else if (func_800D633C()) { /* one shared return: a `return 0` in the first arm sets v0 mid-block */
        D_800EB0C4->flags |= 0x80;
    }
    return 0;
}
