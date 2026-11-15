/* @header
 * func_800A3500
 * VRAM 0x800A3500 | ROM 0x4FC70 | size 0x2FC
 * asm: asm/nonmatchings/code_80090000/func_800A3500.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx, which func_800A2BC0 also writes on PC. The picture is the entry of the
 * resource-name cache that func_800B600C hands back for the name this file is given (port_decls.h: the key is a
 * MenuKey, port.h; func_8009FE3C passes names' addresses as MENU_KEY_NAME), common.h's Nw2ResourceEntryHashed: h, at
 * +0x10 on the N64, is reserved's +8 there, as the assert checks, and func_800A2BC0 reads the same entry through its
 * own view of that layout. */
typedef Gfx G;
typedef struct { u8 pad0[0x18]; s16 h; } Spr;
_Static_assert(offsetof(Spr, h) == offsetof(Nw2ResourceEntryHashed, reserved) + 8,
               "Spr must follow the PC layout of Nw2ResourceEntryHashed");
#else
typedef struct { u32 w0, w1; } G;
typedef struct { u8 pad0[0x10]; s16 h; } Spr;
#endif
extern s32 D_800CCBF8[];
extern f64 D_800D61F0;
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800B600C */
Spr *func_800B600C(s32, s32);
#endif
void func_800A2BC0(G **, Spr *, s32 *, s32 *, s32, s32);

static inline void wobble(s32 *x, s32 *y, s32 n) {
    s32 i;
    x[0] = D_800CCBF8[n & 0xF];
    i = n - 1;
    x[1] = D_800CCBF8[i & 0xF];
    i = n - 2;
    x[2] = D_800CCBF8[i & 0xF];
    i = n - 3;
    x[3] = D_800CCBF8[i & 0xF];
    i = n - 4;
    y[0] = D_800CCBF8[i & 0xF];
    i = n - 5;
    y[1] = D_800CCBF8[i & 0xF];
    i = n - 6;
    y[2] = D_800CCBF8[i & 0xF];
    i = n - 7;
    y[3] = D_800CCBF8[i & 0xF];
}

static inline s32 lo(s32 b, s32 w) {
    w--;
    return b - w;
}

static inline s32 hi(s32 b, s32 w) {
    w--;
    return b + w;
}

#ifdef TARGET_PC
void func_800A3500(G **dl, u8 *t, MenuKey id, s32 flags) { /* PC: the picture's key, as above */
#else
void func_800A3500(G **dl, u8 *t, s32 id, s32 flags) {
#endif
    s32 x[4];
    s32 y[4];
    G *g = *dl;
    Spr *r;
    s32 x0, x1;

    { G *d = g++; d->w0 = 0xE7000000; d->w1 = 0; }
    { G *d = g++; d->w0 = 0xFA000000; d->w1 = t[0x16] >> 1; }
    { G *d = g++; d->w0 = 0xFC51FEA3; d->w1 = 0x44FE773B; }
    { G *d = g++; d->w0 = 0x07000206; d->w1 = 0x604; }
    { G *d = g++; d->w0 = 0xE7000000; d->w1 = 0; }
    { G *d = g++; d->w0 = 0xFA000000; d->w1 = t[0x16]; }
    { G *d = g++; d->w0 = 0xFC5196A3; d->w1 = 0x112CFE7F; }
    r = func_800B600C(id, (flags & 0xFFFF) | 8);
    x0 = -0x3A;
    if (r->h >= 0x80) {
        x1 = 0x3A;
    } else {
        x1 = r->h * D_800D61F0;
        x0 = -(x1 + 3);
        x1 -= 3;
    }
    if (flags & 0x10000) {
        y[3] = 0;
        y[2] = 0;
        y[1] = 0;
        y[0] = 0;
        x[3] = 0;
        x[2] = 0;
        x[1] = 0;
        x[0] = 0;
    } else {
        wobble(x, y, *(s16 *)(t + 0x14));
    }
    x[0] = lo(x0, x[0]);
    x[1] = hi(x1, x[1]);
    x[2] = lo(x0, x[2]);
    x[3] = hi(x1, x[3]);
    y[0] = -6 - y[0];
    y[1] = -6 - y[1];
    y[2] += 6;
    y[3] += 6;
    func_800A2BC0(&g, r, x, y, 4, r->h);
    *dl = g;
}
