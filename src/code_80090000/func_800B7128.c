/* @header
 * func_800B7128
 * VRAM 0x800B7128 | ROM 0x63898 | size 0x74
 * asm: asm/nonmatchings/code_80090000/func_800B7128.s
 */
#include "common.h"

void func_800B6938(u32 **, s32, s32, u8 *, u8 *);
static inline u8 *hdr(u8 *q, u8 **b, u8 **c, u32 **g, u32 *t) {
    u16 n = *(u16 *)(q + 0xA);
    *c = q + 0x10;
    *g = t;
    *b = *c + n * 2;
    return q;
}
u8 *func_800B7128(u32 **dl, u8 *h) {
    u8 *b;
    u8 *c;
    u32 *t = *dl;
    u32 *g;
    hdr(h, &b, &c, &g, t);
    
    func_800B6938(&g, h[8] == 8, *(u16 *)(h + 4), b, c);
    *dl = g;
    return h;
}
