/* @header
 * func_800986DC
 * VRAM 0x800986DC | ROM 0x8BB7C | size 0x284
 * asm: asm/nonmatchings/ovl2_80090000/func_800986DC.s
 */
#include "common.h"

#ifdef TARGET_PC
typedef Gfx G; /* on PC a command is port.h's 16-byte Gfx, which keeps a whole pointer in w1 */
#else
typedef struct {
    u32 w0;
    u32 w1;
} G;
#endif

#ifdef TARGET_PC
/* PC: the icon's picture is an entry of the resource-name cache (func_8002A2FC returns it; func_80097E34 and
 * func_80097EF4 keep it in the icon), whose PC layout is Nw2ResourceEntryHashed in common.h: the key is as wide as a
 * pointer, so the allocation (the picture's pixels) is a pointer at +8, and the sizes lie in reserved from +0x10. fmt,
 * h and w are reserved's +4, +6 and +8, as at the N64's +0xC, +0xE and +0x10. The assert checks it. */
typedef struct {
    ResKey key;
    void *addr;
    u8 pad10[4];
    s16 fmt;
    s16 h;
    s16 w;
} Tex;
_Static_assert(offsetof(Tex, key) == offsetof(Nw2ResourceEntryHashed, key) &&
                   offsetof(Tex, addr) == offsetof(Nw2ResourceEntryHashed, allocation) &&
                   offsetof(Tex, fmt) == offsetof(Nw2ResourceEntryHashed, reserved) + 4 &&
                   offsetof(Tex, h) == offsetof(Nw2ResourceEntryHashed, reserved) + 6 &&
                   offsetof(Tex, w) == offsetof(Nw2ResourceEntryHashed, reserved) + 8 &&
                   sizeof(Tex) == sizeof(Nw2ResourceEntryHashed),
               "Tex must follow the PC layout of Nw2ResourceEntryHashed");
#else
typedef struct {
    u8 pad0[4];
    u32 addr;
    u8 pad8[4];
    s16 fmt;
    s16 h;
    s16 w;
} Tex;
#endif

typedef struct {
    s16 id;
    s16 scale;
    s16 x;
    s16 y;
    Tex *tex;
} Icon;

#ifndef TARGET_PC /* on PC, port_decls.h declares D_800E2E80, which holds palette addresses */
extern u32 D_800E2E80[];
#endif

#ifndef TARGET_PC /* on PC, port_decls.h declares func_80006178: the list as Gfx ** and the texture as a pointer */
void func_80006178(G **, u32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32);
#endif

#define EMIT(a, b) { G *q = g++; q->w0 = (a); q->w1 = (b); }

void func_800986DC(G **dl, Icon *ic) {
    G *g;
    Tex *t;
    f32 h;

    if (ic->id != -1) {
        g = *dl;
        t = ic->tex;
        h = ic->scale * 0.5; /* read before the commands (the G stores could alias it) */
        EMIT(0xFC5196A3, 0x112CFE7F);
        EMIT(0xE200001C, 0x0F0A7008);
#ifdef TARGET_PC
        /* PC: the palette's address as the whole pointer (port.h's DL_ADDR); the N64 subtracts 0x80000000 in 32
         * bits. */
        EMIT(0xFD100000, DL_ADDR(D_800E2E80[ic->id]));
#else
        EMIT(0xFD100000, D_800E2E80[ic->id] - 0x80000000);
#endif
        EMIT(0xE8000000, 0);
        EMIT(0xF5000100, 0x07000000);
        EMIT(0xE6000000, 0);
        EMIT(0xF0000000, 0x0703C000);
        EMIT(0xE7000000, 0);
        EMIT(0xFA000000, 0xFF);
        EMIT(0xFB000000, -1);
        EMIT(0xE3001201, 0);
        EMIT(0xE3000C00, 0);
#ifdef TARGET_PC
        /* PC: func_80006178 takes the picture's own address (docs/port.md, "Display lists on PC"). The N64 passes the
         * address minus 0x80000000 and the function subtracts 0x80000000 again, so the 32-bit result is the address
         * itself there too. */
        func_80006178(&g, t->addr, 2, 0, t->fmt, t->h, 0x40, 0x20, 0, 0, t->w, t->h,
                      ic->x - t->w * h, ic->y);
#else
        func_80006178(&g, t->addr - 0x80000000, 2, 0, t->fmt, t->h, 0x40, 0x20, 0, 0, t->w, t->h,
                      ic->x - t->w * h, ic->y);
#endif
        EMIT(0xE7000000, 0);
        EMIT(0xE3000C00, 0x80000);
        EMIT(0xE3001201, 0x2000);
        *dl = g;
    }
}
