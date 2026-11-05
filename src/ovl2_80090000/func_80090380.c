/* @header
 * func_80090380
 * VRAM 0x80090380 | ROM 0x83820 | size 0x224
 * asm: asm/nonmatchings/ovl2_80090000/func_80090380.s
 */
#include "common.h"

void func_80004AFC(void);
void *allocateHeap(u32 bytes);
u32 osVirtualToPhysical(void *);

typedef struct {
    u32 w0;
    u32 w1;
} Gfx2;

typedef struct {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 pad3[5];
    s16 f8;
    s16 fA;
    void *vtx;
    Gfx2 *dl2;
    Gfx2 *dl;
} Node;

#define CMD(g, a, b) { Gfx2 *_d = (g)++; _d->w0 = (a); _d->w1 = (b); }

/* Build a textured quad node; mode 2 uses a TLUT, anything else non-zero point/bilerp filtering. */
void func_80090380(Node *n, u16 mode) {
    Gfx2 *g;
    Gfx2 *h;

    func_80004AFC();
    n->f0 = 1;
    n->f2 = 4;
    n->f1 = 2;
    n->vtx = allocateHeap(0x40);
    n->dl = allocateHeap(0x60);
    n->dl2 = allocateHeap(0x200);
    g = n->dl;
    if (mode != 0) {
        if (mode == 2) {
            CMD(g, 0xE3001001, 0xC000);
        } else {
            CMD(g, 0xE3001201, 0);
        }
    }
    CMD(g, 0xD9DFFFFF, 0);
    CMD(g, 0x01004008, osVirtualToPhysical(n->vtx));
    CMD(g, 0x06000204, 0x40206);
    CMD(g, 0xE7000000, 0);
    CMD(g, 0xD9FFFFFF, 0x200000);
    if (mode != 0) {
        if (mode == 2) {
            CMD(g, 0xE3001001, 0x8000);
        } else {
            CMD(g, 0xE3001201, 0x2000);
        }
    }
    CMD(g, 0xDF000000, 0);
    n->f8 = 1;
    n->fA = 1;
    h = n->dl2;
    CMD(h, 0xE200001C, 0xF0A4000);
    CMD(h, 0xFCFFFFFF, 0xFFFE793C);
    if (n->dl != NULL) {
        CMD(h, 0xDE010000, (u32)n->dl - 0x80000000);
    } else {
        CMD(h, 0xDF000000, 0);
    }
}
