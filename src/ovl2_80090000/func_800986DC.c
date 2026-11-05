/* @header
 * func_800986DC
 * VRAM 0x800986DC | ROM 0x8BB7C | size 0x284
 * asm: asm/nonmatchings/ovl2_80090000/func_800986DC.s
 */
#include "common.h"

typedef struct {
    u32 w0;
    u32 w1;
} G;

typedef struct {
    u8 pad0[4];
    u32 addr;
    u8 pad8[4];
    s16 fmt;
    s16 h;
    s16 w;
} Tex;

typedef struct {
    s16 id;
    s16 scale;
    s16 x;
    s16 y;
    Tex *tex;
} Icon;

extern u32 D_800E2E80[];

void func_80006178(G **, u32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32);

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
        EMIT(0xFD100000, D_800E2E80[ic->id] - 0x80000000);
        EMIT(0xE8000000, 0);
        EMIT(0xF5000100, 0x07000000);
        EMIT(0xE6000000, 0);
        EMIT(0xF0000000, 0x0703C000);
        EMIT(0xE7000000, 0);
        EMIT(0xFA000000, 0xFF);
        EMIT(0xFB000000, -1);
        EMIT(0xE3001201, 0);
        EMIT(0xE3000C00, 0);
        func_80006178(&g, t->addr - 0x80000000, 2, 0, t->fmt, t->h, 0x40, 0x20, 0, 0, t->w, t->h,
                      ic->x - t->w * h, ic->y);
        EMIT(0xE7000000, 0);
        EMIT(0xE3000C00, 0x80000);
        EMIT(0xE3001201, 0x2000);
        *dl = g;
    }
}
