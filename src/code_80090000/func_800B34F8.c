/* @header
 * func_800B34F8
 * VRAM 0x800B34F8 | ROM 0x5FC68 | size 0x148
 * asm: asm/nonmatchings/code_80090000/func_800B34F8.s
 */
#include "common.h"


typedef struct { s32 a; u8 pad[0x28]; } T;
extern T D_800EA248[];
extern u8 D_800EA0D8[];
extern u16 D_800EA0E2[];
extern u8 D_8007E8C0[], D_8007E228[], D_800E7C58[];
void bcopy(void *, void *, s32);
void bzero(void *, s32);

/*
 * Placeholders (see MasterIndex, func_800B34F8):
 * - n is a constant flag that only the second CSE pass can see (the do-while's
 *   LOOP_END note ends cse1's block). Each `if (n)` block is skipped around by
 *   cse2 (its sets are invalidated: g before g2 = g + k, m/h before the last
 *   store) and then deleted with the folded jump before flow, so it leaves no code.
 * - `if (t) v++;` is dead at flow (v is not used again) but its jump survives
 *   until jump2; the block boundary makes g2 a global pseudo so it gets g's s1.
 */
void func_800B34F8(s32 a, s32 b) {
    u8 *e;
    u8 *g, *g2;
    s32 *x;
    s32 k;
    u8 *m, *h;
    s32 y, n;
    s32 t = a * 16;
    s32 pad[4];
    s32 v = D_800EA248[b].a;

    n = 0;
    e = t + D_800EA0D8;
    g = D_8007E8C0;
    k = b << 2;
    x = (s32 *)(g + k);
    *(s32 *)e = v;
    bcopy(*x * 8 + D_800E7C58, e + 6, 4);
    *(u16 *)(e + 4) = *(s32 *)(D_8007E228 + 0x688 + k) | ((*(s32 *)(D_8007E8C0 + 0x70 + k) & 3) << 12);
    bzero(e + 0xC, 4);
    do { } while (0);
    if (n) {
        g = D_8007E228;
    }
    g2 = g + k;
    *(u16 *)(e + 0xA) = 0;
    if (t) {
        v++;
    }
    y = *(s32 *)(g2 + 4);
    m = D_8007E228 + 0x688;
    h = D_8007E8C0 + 0x70;
    if (y != *x) {
        bcopy(y * 8 + D_800E7C58, t + (D_800EA0D8 + 0xC), 4);
    }
    if (n) {
        m = D_8007E228;
        h = D_8007E8C0;
    }
    *(u16 *)((u8 *)D_800EA0E2 + t) = *(s32 *)(m + k + 4) | ((*(s32 *)(h + k + 4) & 3) << 12);
}
