/* @header
 * func_800B7354
 * VRAM 0x800B7354 | ROM 0x63AC4 | size 0xE0
 * asm: asm/nonmatchings/code_80090000/func_800B7354.s
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

u8 *func_800B7354(u32 **dl, s32 x, s32 a) {
    u8 *b;
    u8 *c;
    u32 *g = *dl;
    u8 *v;
    v = load(a, &b, &c);
    if (v == 0) {
        return 0;
    }
    b += *(u16 *)(v + 4) * x * v[8] / 8;
    func_800B6938(&g, v[8] == 8, *(u16 *)(v + 4), b, c);
    *dl = g;
    return v;
}
