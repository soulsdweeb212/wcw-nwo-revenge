#include "common.h"

typedef struct {
    u8 pad0[4];
    void *f4;
    u8 pad8[4];
    s16 fC;
    s16 fE;
    s16 f10;
} Nw2Tex98804;

extern u8 D_C95F0[];
extern u8 D_C95B8[];
extern u8 D_C9678[];
extern u8 D_C9620[];

s32 func_8002AD68(s32);
s32 func_8002AE24(s32);
s32 func_8002AD34(s32, s32);
Nw2Tex98804 *func_800B600C(s32, s32);
void appendPaletteSetupDisplayList(void *);
void func_80096D8C(void *, void *, s32, s32, s32, s32, s32, s32, s32);

#define EMIT(a, b) { Nw2GfxCommand *q = p; p = q + 1; q->w0 = (a); q->w1 = (b); }

void func_80098804(void **out, s32 id, s32 arg2, s32 x, s32 y, s32 color) {
    void *p;
    s32 pad1;
    void *q;
    void **pp;
    s32 *pq;
    Nw2Tex98804 *tex;
    s32 yl;
    s32 yh;
    u32 xl;
    u32 xh;
    s32 top;
    s32 top2;
    f64 fy;
    s32 r;

    pp = &p;
    pq = &pad1;
    p = *out;
    EMIT(0xDE000000, (u32)D_C95F0);
    EMIT(0xDE000000, (u32)D_C95B8);
    EMIT(0xFA000000, (color / 2) & 0xFF);
    yl = (s32)(((f64)(y - 4) + 7.0) * 4.0) & 0xFFFF;
    yh = (s32)(((f64)(y + 4) + 35.0) * 4.0) & 0xFFFF;
    xl = (x - 0x50) << 18;
    xh = (x + 0x50) << 18;
    EMIT(0x02180000, yl | xl);
    EMIT(0x02180002, yl | xh);
    EMIT(0x02180004, yh | xl);
    EMIT(0x02180006, yh | xh);
    EMIT(0xDE000000, (u32)D_C9678);
    EMIT(0xDE000000, (u32)D_C9620);
    EMIT(0xFA000000, color & 0xFF);

    q = p;
    r = func_8002AD68(id);
    fy = y;
    top = (s32)(fy + 21.0);
    tex = func_800B600C(r, 8);
    if (tex != NULL) {
        appendPaletteSetupDisplayList(&q);
        func_80096D8C(&q, tex->f4, 0, x - 8 - tex->f10, top, tex->fC, tex->fE, tex->fC, tex->fE * (0x200 - color) / 255);
        p = q;
    }

    q = p;
    tex = func_800B600C(func_8002AE24(id), 8);
    if (tex != NULL) {
        appendPaletteSetupDisplayList(&q);
        func_80096D8C(&q, tex->f4, 0, x + 8, top, tex->fC, tex->fE, tex->fC, tex->fE * (0x200 - color) / 255);
        p = q;
    }

    top2 = (s32)(fy + 7.0);
    q = p;
    tex = func_800B600C(func_8002AD34(id, arg2), 8);
    if (tex != NULL) {
        appendPaletteSetupDisplayList(&q);
        func_80096D8C(&q, tex->f4, 0, x - (s16)(u16)tex->f10 / 2, top2, tex->fC, tex->fE, tex->fC, tex->fE * (0x200 - color) / 255);
        p = q;
    }
    *out = p;
}
