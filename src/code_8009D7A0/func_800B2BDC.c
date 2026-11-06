/* @header
 * func_800B2BDC
 * VRAM 0x800B2BDC | ROM 0xA607C | size 0x1C0
 * asm: asm/nonmatchings/code_8009D7A0/func_800B2BDC.s
 */
#include "common.h"

/* Proximity/contact test for the active move (D_800FABD0) against the other
 * wrestler (D_800F9D10[D_800FAF58->id ^ 1]). Writes the direction to the
 * move's +6 from D_800E3CF0 using func_800D3650 on the two pelvis joints. If
 * the other wrestler is not on the apron, resets the move immediately (clearing
 * +2/+4/+0x5C bits, copying D_800F9B60->state into +0x2E). Otherwise, when the
 * other wrestler is in state 0x01/0x81,
 * it may set +8=8 on close range (func_800D3890 vs D_800E52B0) and then falls
 * through to the same action reset. */

extern u8 *D_800FABD0;
extern u16 D_800E3CF0[];
extern f64 D_800E52B0;
s32 func_800D3650(void *, void *);
f32 func_800D3890(void *, void *, void *);
#define B2F(p, t, o) (*(t *)((u8 *)(p) + (o)))
void func_800B2BDC(void) {
    s8 id = D_800FAF58->id ^ 1;
    B2F(D_800FABD0, u16, 6) = D_800E3CF0[(s16)func_800D3650(&D_800FAF58->jointA[1], &D_800F9D10[id].jointA[1])];
    if (!(D_800F9D10[id].flags & WR_FLAG_ON_APRON)) {
        u8 *p = D_800FABD0;
        Wrestler *g = D_800F9B60;
        u16 state;
        B2F(p, s16, 2) = 0;
        B2F(p, s16, 4) = 0;
        state = g->state;
        B2F(p, u32, 0x5C) &= ~7;
        B2F(p, u16, 0x2E) = state;
        return;
    }
    if ((D_800F9D10[id].state == 1) | (D_800F9D10[id].state == 0x81)) {
        if (func_800D3890(&D_800FAF58->jointA[1], &D_800F9D10[id].jointA[1], 0) < D_800E52B0) B2F(D_800FABD0, s16, 8) = 8;
        if (D_800FAF58->state == 1) return;
    }
    { u8 *p = D_800FABD0;
        Wrestler *g = D_800F9B60;
        B2F(p, s16, 2) = 0;
        B2F(p, s16, 4) = 0;
        B2F(p, u16, 0x2E) = g->state;
        B2F(p, u32, 0x5C) &= ~7; }
}
#undef B2F
