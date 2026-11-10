/* @header
 * func_80090380
 * VRAM 0x80090380 | ROM 0x83820 | size 0x224
 * asm: asm/nonmatchings/ovl2_80090000/func_80090380.s
 */
#include "common.h"

void func_80004AFC(void);
void *allocateHeap(u32 bytes);
u32 osVirtualToPhysical(void *);

#ifdef TARGET_PC
typedef Gfx Gfx2; /* on PC a command is port.h's 16-byte Gfx */
#else
typedef struct {
    u32 w0;
    u32 w1;
} Gfx2;
#endif

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
#ifdef TARGET_PC
/* n is the display record, whose PC layout is that of Nw2TextureDisplayObj (common.h): with 8-byte pointers vtx, dl2
 * and dl fall on its colorPtr, dl and next, as the assert checks. */
_Static_assert(offsetof(Node, vtx) == offsetof(Nw2TextureDisplayObj, colorPtr) &&
                   offsetof(Node, dl2) == offsetof(Nw2TextureDisplayObj, dl) &&
                   offsetof(Node, dl) == offsetof(Nw2TextureDisplayObj, next),
               "Node must follow the display record's PC layout");
#endif

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
#ifdef TARGET_PC
    /* PC: room for the same number of commands, 12 and 64, at 16 bytes each instead of 8. */
    n->dl = allocateHeap(0x60 / 8 * sizeof(Gfx2));
    n->dl2 = allocateHeap(0x200 / 8 * sizeof(Gfx2));
#else
    n->dl = allocateHeap(0x60);
    n->dl2 = allocateHeap(0x200);
#endif
    g = n->dl;
    if (mode != 0) {
        if (mode == 2) {
            CMD(g, 0xE3001001, 0xC000);
        } else {
            CMD(g, 0xE3001201, 0);
        }
    }
    CMD(g, 0xD9DFFFFF, 0);
#ifdef TARGET_PC
    /* PC: the vertices' address as the whole pointer (port.h's DL_ADDR); osVirtualToPhysical returns a u32. */
    CMD(g, 0x01004008, DL_ADDR(n->vtx));
#else
    CMD(g, 0x01004008, osVirtualToPhysical(n->vtx));
#endif
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
#ifdef TARGET_PC
        /* PC: the branch target goes into the command as the whole pointer (port.h's DL_ADDR). */
        CMD(h, 0xDE010000, DL_ADDR(n->dl));
#else
        CMD(h, 0xDE010000, (u32)n->dl - 0x80000000);
#endif
    } else {
        CMD(h, 0xDF000000, 0);
    }
}
