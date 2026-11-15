/* @header
 * func_8009F8BC
 * VRAM 0x8009F8BC | ROM 0x4C02C | size 0xE4
 * asm: asm/nonmatchings/code_80090000/func_8009F8BC.s
 */
#include "common.h"

#ifndef TARGET_PC /* on PC, port.h defines Gfx, the 16-byte command */
typedef struct { u32 w0; u32 w1; } Gfx;
#endif
#ifdef TARGET_PC
/* PC: D_800DC580 and D_800DC58C are labels of the scene object D_800DC570 (its display list at +0x10 and its matrices
 * from +0x1C), which have no PC symbol: the object keeps its N64 layout (common.h's Nw2SceneObj) and holds the list as
 * a handle (port.h's PTR_TO_SLOT). The display list at 0x800C9538 by its own address (port.h's DL_ADDR turns it into
 * the command word; D_C9538 is its N64 physical address, a link constant). */
extern Nw2SceneObj D_800DC570;
extern u8 D_800E7558[], D_800C9538[], D_800C9C70[];
#else
extern Gfx *D_800DC580;
extern u8 D_800DC58C[], D_800E7558[], D_C9538[], D_800C9C70[];
#endif
void func_800B830C(void *);
void func_8009EC58(Gfx **, void *);
#ifdef TARGET_PC
/* PC: the second word is as wide as a pointer; the callers pass addresses through DL_ADDR. */
#define W(a, b) { Gfx *t = g++; t->w0 = (u32)(a); t->w1 = (b); }
#else
#define W(a, b) { Gfx *t = g++; t->w0 = (u32)(a); t->w1 = (u32)(b); }
#endif

void func_8009F8BC(Gfx **dl) {
    Gfx *g = *dl;
    s32 i;
#ifdef TARGET_PC
    /* PC: the object's fields by name, as above. */
    D_800DC570.dl = PTR_TO_SLOT(g);
    func_800B830C(D_800DC570.local);
#else
    D_800DC580 = g;
    func_800B830C(D_800DC58C);
#endif
#ifdef TARGET_PC
    /* PC: the two display lists' addresses as the whole pointers (port.h's DL_ADDR). */
    W(0xDE000000, DL_ADDR(D_800C9538));
    W(0xDE000000, DL_ADDR(D_800C9C70));
#else
    W(0xDE000000, D_C9538);
    W(0xDE000000, D_800C9C70);
#endif
    W(0xE3001001, 0x8000);
    W(0xDF000000, 0);
    for (i = 0; i < 4; i++) {
        func_8009EC58(&g, D_800E7558 + i * 0xEC);
    }
    *dl = g;
}
