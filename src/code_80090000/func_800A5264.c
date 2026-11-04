/* @header
 * func_800A5264
 * VRAM 0x800A5264 | ROM 0x519D4 | size 0x1C8
 * asm: asm/nonmatchings/code_80090000/func_800A5264.s
 */
#include "common.h"


typedef struct { u32 w0, w1; } G;
typedef struct { u8 pad[0x10]; s16 h; } T;
extern u8 D_8007EF30[], D_800CCCC0[];
u8 *func_800B75D4(G **, void *, s32);
void *func_8002AD34(s32, s32);
void *lookupPlayerNameById(void *, void *);

void func_800A5264(G **dl, s32 a) {
    G *g = *dl;
    s32 n = a & 0xF;
    T *t;
    void *p, *x;

    func_800B75D4(&g, D_800CCCC0 + n * 8, 8);
    { G *d = g++; d->w0 = 0x07000206; d->w1 = 0x604; }
    func_800B75D4(&g, D_800CCCC0 + 0x48, 8);
    { G *d = g++; d->w0 = 0x0714161A; d->w1 = 0x141A18; }
    if (a & 0x20) {
        u16 v = *(u16 *)(D_8007EF30 + 0xC90 + n * 4);
        /* `a` is reused for the name ids; without the reuse the 0x20 test is computed into a's register. */
        a = v & 0xFFF;
        x = func_8002AD34(a, (v >> 12) & 3);
        v = *(u16 *)(D_8007EF30 + 0xC92 + n * 4);
        a = v & 0xFFF;
        p = lookupPlayerNameById(x, func_8002AD34(a, (v >> 12) & 3));
    } else {
        u16 v = *(u16 *)(D_8007EF30 + 0xC90 + n * 2);
        a = v & 0xFFF;
        p = func_8002AD34(a, (v >> 12) & 3);
    }
    t = (T *)func_800B75D4(&g, p, 8);
    if (t->h >= 0x80) {
        G *d = g;
        d[0].w0 = 0x0214000E;
        d[0].w1 = t->h << 21;
        g = d + 1;
        d[1].w0 = 0x02140012;
        d[1].w1 = (t->h << 21) | 0x1C0;
        g = d + 2;
    }
    { G *d = g++; d->w0 = 0x070C0E12; d->w1 = 0xC1210; }
    *dl = g;
}
