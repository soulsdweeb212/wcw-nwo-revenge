/* @header
 * func_800B2BDC
 * VRAM 0x800B2BDC | ROM 0xA607C | size 0x1C0
 * asm: asm/nonmatchings/code_8009D7A0/func_800B2BDC.s
 */
#include "common.h"

/* Proximity/contact test for the active move (D_800FABD0) against the other
 * entity (index = D_800FAF58[0]^1, stride 0x3B0). Writes the direction to the
 * move's +6 from D_800E3CF0 using func_800D3650 on the two positions. If the
 * other entity lacks flag 0x80, resets the move immediately (clearing
 * +2/+4/+0x5C bits, copying D_800F9B60+0xA into +0x2E). Otherwise, when the
 * other entity is in a reaction state (0x01/0x81 via D_800F9D1A),
 * it may set +8=8 on close range (func_800D3890 vs D_800E52B0) and then falls
 * through to the same action reset. */

extern u8 *D_800FAF58, *D_800FABD0, *D_800F9B60;
extern u16 D_800E3CF0[];
extern s16 D_800F9D1A[][472];
extern f64 D_800E52B0;
s32 func_800D3650(void *, void *);
f32 func_800D3890(void *, void *, void *);
#define B2F(p, t, o) (*(t *)((u8 *)(p) + (o)))
void func_800B2BDC(void) {
    s8 id = D_800FAF58[0] ^ 1;
    s32 offset = id * 0x3B0;
    B2F(D_800FABD0, u16, 6) = D_800E3CF0[(s16)func_800D3650(D_800FAF58 + 0x6C, D_800F9D7C + offset)];
    if (!(*(u64 *)(D_800F9D30 + offset) & 0x80)) {
        u8 *p = D_800FABD0, *g = D_800F9B60;
        u16 state;
        B2F(p, s16, 2) = 0;
        B2F(p, s16, 4) = 0;
        state = B2F(g, u16, 0xA);
        B2F(p, u32, 0x5C) &= ~7;
        B2F(p, u16, 0x2E) = state;
        return;
    }
    if ((D_800F9D1A[id][0] == 1) | (D_800F9D1A[id][0] == 0x81)) {
        if (func_800D3890(D_800FAF58 + 0x6C, D_800F9D7C + id * 0x3B0, 0) < D_800E52B0) B2F(D_800FABD0, s16, 8) = 8;
        if (B2F(D_800FAF58, s16, 0xA) == 1) return;
    }
    { u8 *p = D_800FABD0, *g = D_800F9B60;
        B2F(p, s16, 2) = 0;
        B2F(p, s16, 4) = 0;
        B2F(p, u16, 0x2E) = B2F(g, u16, 0xA);
        B2F(p, u32, 0x5C) &= ~7; }
}
#undef B2F
