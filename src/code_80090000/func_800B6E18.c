/* @header
 * func_800B6E18
 * VRAM 0x800B6E18 | ROM 0x63588 | size 0xA0
 * asm: asm/nonmatchings/code_80090000/func_800B6E18.s
 */
#include "common.h"

u8 *func_800B600C(s32, s32);
void func_800B6938(u32 **, s32, s32, u8 *, u8 *);
void func_800B6548(u32 **, s32, s32, s32, u8 *, u8 *);

static inline u8 *hdr(u8 *a, u8 **b, u8 **c) {
    u8 *p = a + 0x10;
    *c = p;
    p += *(u16 *)(a + 0xA) * 2;
    *b = p;
    return a;
}

static inline u8 *load(s32 a, u8 **b, u8 **c) {
    u8 *v = func_800B600C(a, 0);
    if (v == 0) {
        return 0;
    }
    return hdr(v, b, c);
}

u8 *func_800B6E18(u32 **dl, s32 a, s32 b, s32 i, s32 j) {
    u32 *g = *dl;
    u8 *v = func_800B600C(i, 0);
    u8 *w;
    if (v == 0) {
        return 0;
    }
    w = func_800B600C(j, 0);
    if (w) {
        func_800B6938(&g, a == 1, b, v, w);
        *dl = g;
        return v;
    }
    return 0;
}
