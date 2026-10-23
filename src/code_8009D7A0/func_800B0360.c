#include "common.h"

/* Two-state approach/engage sequencer for the active action (D_800FABD0),
 * driven by the global state (D_800FAF58+0xA must be 1, else the action is
 * reset). State 0 picks a random facing (func_800D4148 & 15) and advances.
 * State 1 turns toward the target (func_800D3650 -> D_800E3CF0 written to +6);
 * it resets on close range (func_800D3B24 within 100), or switches to action
 * 0x15 when the target is blocking (flag 0x100) and the required facing
 * (+0x1E vs +0x2C) differs; otherwise it counts down +0xE and resets at zero. */
s32 func_800D3650(void *, void *); s8 func_800D3B24(void *, void *, f32, s32); s32 func_800D4148(void);
extern u16 D_800E3CF0[]; extern void *D_800F9B60, *D_800FABD0, *D_800FAF58;
#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))
#define RESET(id) { void *p = D_800FABD0, *g = D_800F9B60; F(p, s16, 2) = id; F(p, s16, 4) = 0; F(p, u16, 0x2E) = F(g, u16, 0xA); F(p, u32, 0x5C) &= ~7; }
void func_800B0360(void) {
    u16 command;
    switch (F(D_800FABD0, s16, 4)) {
    case 0:
        if (F(D_800FAF58, s16, 0xA) == 1) {
            F(D_800FABD0, u16, 6) = 0;
            F(D_800FABD0, s16, 0xE) = func_800D4148() & 15;
            F(D_800FABD0, s16, 4)++;
        } else RESET(0)
        break;
    case 1:
        if (F(D_800FAF58, s16, 0xA) == 1) {
            if (func_800D3B24((u8 *)D_800FAF58 + 0x6C, (u8 *)D_800F9B60 + 0x6C, 100.0f, 0)) RESET(0)
            if ((F(D_800FAF58, u64, 0x20) & 0x100) && F(D_800FABD0, s16, 0x1E) != F(D_800FABD0, s16, 0x2C)) { RESET(0x15) }
            else {
                command = D_800E3CF0[(s16)func_800D3650((u8 *)D_800FAF58 + 0x6C, (u8 *)D_800F9B60 + 0x6C)];
                F(D_800FABD0, u16, 6) = command;
                if (--F(D_800FABD0, s16, 0xE) < 0) RESET(0)
            }
        } else RESET(0)
        break;
    }
}
#undef F
#undef RESET
