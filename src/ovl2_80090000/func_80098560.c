/* @header
 * func_80098560
 * VRAM 0x80098560 | ROM 0x8BA00 | size 0x17C
 * asm: asm/nonmatchings/ovl2_80090000/func_80098560.s
 */
#include "common.h"

#ifdef TARGET_PC
/* On PC a command is port.h's 16-byte Gfx, as in func_800982AC.c, which allocates these lists (D_800EB18C), and
 * func_800986DC.c, which writes into them. */
typedef Gfx G;
#else
typedef struct {
    u32 w0;
    u32 w1;
} G;
#endif

#ifndef TARGET_PC /* on PC the object's work block is common.h's Nw2SceneWork, read by name */
typedef struct {
    s32 flags;
} Node;
#endif

/* Current display-list buffer (0..2). Its own scalar symbol (new build.json entry, 0x800E2E9A):
 * as D_800E2E98+2 the address is forced into a register and CSE shares it. */
extern u8 D_800E2E9A;
#ifndef TARGET_PC /* on PC D_800EB0C0 has no symbol: it is the dl of D_800EB0B0, which port_decls.h declares */
extern G *D_800EB0C0;
#endif
#ifdef TARGET_PC
/* PC: the N64 label D_800EB0C4 is D_800EB0B0's work (+0x14). D_800EB0B0 keeps its N64 layout (Nw2SceneObj in
 * common.h), so work holds the handle (port.h's PTR_TO_SLOT) of the object's work block (Nw2SceneWork); hudWork turns
 * it back into the block, whose kind is the N64's flags. */
static inline Nw2SceneWork *hudWork(void) {
    return SLOT_TO_PTR(D_800EB0B0.work);
}
#else
extern Node *D_800EB0C4;
#endif
extern G *D_800EB18C[3];
#ifdef TARGET_PC
/* PC: the icon is common.h's Nw2HudIcon, as port_decls.h declares D_800EB1AC: the picture's pointer at +8 is 8 bytes,
 * so an icon is 0x10 bytes. */
typedef Nw2HudIcon Icon;
#else
typedef struct {
    s16 id; /* -1 = none */
    s16 scale;
    s16 x;
    s16 y;
    void *tex; /* D_800EB1B4 */
} Icon;
#endif

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
#ifdef TARGET_PC
            hudWork()->kind |= 0x80; /* PC: see hudWork */
#else
            D_800EB0C4->flags |= 0x80;
#endif
        } else {
#ifdef TARGET_PC
            hudWork()->kind &= ~0x80;
#else
            D_800EB0C4->flags &= ~0x80;
#endif
        }
        g->w0 = 0xDF000000;
        g->w1 = 0;
        g++;
#ifdef TARGET_PC
        /* PC: the object's dl (+0x10, the N64 label D_800EB0C0) holds the list's handle (port.h's PTR_TO_SLOT). */
        D_800EB0B0.dl = PTR_TO_SLOT(D_800EB18C[D_800E2E9A++]);
#else
        D_800EB0C0 = D_800EB18C[D_800E2E9A++];
#endif
        D_800E2E9A %= 3;
    } else if (func_800D633C()) { /* one shared return: a `return 0` in the first arm sets v0 mid-block */
#ifdef TARGET_PC
        hudWork()->kind |= 0x80;
#else
        D_800EB0C4->flags |= 0x80;
#endif
    }
    return 0;
}
