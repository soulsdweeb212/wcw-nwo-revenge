/* @header
 * func_800B0360
 * VRAM 0x800B0360 | ROM 0xA3800 | size 0x1B8
 * asm: asm/nonmatchings/code_8009D7A0/func_800B0360.s
 */
#include "common.h"

/* Two-state approach/engage sequencer for the active action (D_800FABD0),
 * driven by the AI wrestler's state (D_800FAF58->state must be 1, else the
 * action is reset). State 0 picks a random countdown (func_800D4148 & 15) and
 * advances. State 1 turns toward the opponent (func_800D3650 on the two pelvis
 * joints -> D_800E3CF0 written to +6); it resets on close range (func_800D3B24
 * within 100), or switches to action 0x15 when the AI wrestler is on the floor
 * and +0x1E differs from +0x2C; otherwise it counts down +0xE and resets at zero. */
s32 func_800D3650(void *, void *); s8 func_800D3B24(void *, void *, f32, s32); s32 func_800D4148(void);
extern u16 D_800E3CF0[]; extern void *D_800FABD0; 
#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))
#define RESET(id) { void *p = D_800FABD0; Wrestler *g = D_800F9B60; F(p, s16, 2) = id; F(p, s16, 4) = 0; F(p, u16, 0x2E) = (u16)g->state; F(p, u32, 0x5C) &= ~7; }
void func_800B0360(void) {
    u16 command;
    switch (F(D_800FABD0, s16, 4)) {
    case 0:
        if (D_800FAF58->state == 1) {
            F(D_800FABD0, u16, 6) = 0;
            F(D_800FABD0, s16, 0xE) = func_800D4148() & 15;
            F(D_800FABD0, s16, 4)++;
        } else RESET(0)
        break;
    case 1:
        if (D_800FAF58->state == 1) {
            if (func_800D3B24(&D_800FAF58->jointA[1], &D_800F9B60->jointA[1], 100.0f, 0)) RESET(0)
            if ((D_800FAF58->flags & WR_FLAG_ON_FLOOR) && F(D_800FABD0, s16, 0x1E) != F(D_800FABD0, s16, 0x2C)) { RESET(0x15) }
            else {
                command = D_800E3CF0[(s16)func_800D3650(&D_800FAF58->jointA[1], &D_800F9B60->jointA[1])];
                F(D_800FABD0, u16, 6) = command;
                if (--F(D_800FABD0, s16, 0xE) < 0) RESET(0)
            }
        } else RESET(0)
        break;
    }
}
#undef F
#undef RESET
