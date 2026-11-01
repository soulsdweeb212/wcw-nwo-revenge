/* @header
 * func_8009F8BC
 * VRAM 0x8009F8BC | ROM 0x4C02C | size 0xE4
 * asm: asm/nonmatchings/code_80090000/func_8009F8BC.s
 */
#include "common.h"

typedef struct { u32 w0; u32 w1; } Gfx;
extern Gfx *D_800DC580;
extern u8 D_800DC58C[], D_800E7558[], D_C9538[], D_800C9C70[];
void func_800B830C(void *);
void func_8009EC58(Gfx **, void *);
#define W(a, b) { Gfx *t = g++; t->w0 = (u32)(a); t->w1 = (u32)(b); }

void func_8009F8BC(Gfx **dl) {
    Gfx *g = *dl;
    s32 i;
    D_800DC580 = g;
    func_800B830C(D_800DC58C);
    W(0xDE000000, D_C9538);
    W(0xDE000000, D_800C9C70);
    W(0xE3001001, 0x8000);
    W(0xDF000000, 0);
    for (i = 0; i < 4; i++) {
        func_8009EC58(&g, D_800E7558 + i * 0xEC);
    }
    *dl = g;
}
