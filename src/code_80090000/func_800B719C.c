/* @header
 * func_800B719C
 * VRAM 0x800B719C | ROM 0x6390C | size 0xC4
 * asm: asm/nonmatchings/code_80090000/func_800B719C.s
 */
#include "common.h"

u8 *func_800B600C(s32, s32);
void func_800B6938(u32 **, s32, s32, u8 *, u8 *);
void func_800B6548(u32 **, s32, s32, s32, u8 *, u8 *);
void func_800B6B5C(u32 **, s32, s32, s32, u8 *, u8 *);

static inline u8 *load(s32 x, u8 **b, u8 **c) {
    u8 *q;
    u16 n;
    q = func_800B600C(x, 0);
    if (q == 0) {
        return 0;
    }
    n = *(u16 *)(q + 0xA);
    *c = q + 0x10;
    *b = *c + n * 2;
    return q;
}

u8 *func_800B719C(u32 **dl, s32 x, s32 a, s32 d) {
    u8 *b;
    u8 *c;
    u32 *g = *dl;
    u8 *v;
    v = load(a, &b, &c);
    if (v == 0) {
        return 0;
    }
    func_800B6B5C(&g, v[8] == 8, *(u16 *)(v + 4), x, b + d, c);
    *dl = g;
    return v;
}
