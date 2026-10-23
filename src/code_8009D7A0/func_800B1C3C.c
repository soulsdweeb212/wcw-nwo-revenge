#include "common.h"

/* Range-based action/pose selector for the active move (D_800FABD0).
 * Computes an effective range from the move's reach (+0x12) scaled by
 * func_800B3AD8, and if the target is in range sets the action's contact
 * flags (+0xA) from the move id (+0x22): id 10 picks a close/far value
 * (0x8000/0x20) via func_800D4198(500), ids 6/17/23 use 0x10, anything else
 * 0x4000; otherwise 0x4000. Copies +0xA into +8 and +6 (or only +6 when out
 * of range). Finally, unless the global state (D_800FAF58+0xA) is 0x2D..0x2F,
 * resets the action record (+2/+4 cleared, +0x2E copied from D_800F9B60+0xA,
 * flags +0x5C bits 0..2 cleared). */
extern u8 *D_800FABD0, *D_800FAF58, *D_800F9B60;
extern f64 D_800E5278;
f32 func_800B3AD8(void *);
s8 func_800D4198(s16);
#define C3(p, t, o) (*(t *)((u8 *)(p) + (o)))
void func_800B1C3C(void) {
    s32 state;
    if (func_800D4198((s16)(s32)((f32)C3(D_800FABD0, s16, 0x12) * func_800B3AD8(D_800FABD0)))) {
        if (func_800D4198((s16)(s32)(C3(D_800FABD0, s16, 0x12) * D_800E5278))) {
            switch (C3(D_800FABD0, s16, 0x22)) {
            case 10:
                if (func_800D4198(500)) C3(D_800FABD0, u16, 0xA) = 0x8000;
                else C3(D_800FABD0, u16, 0xA) = 0x20;
                break;
            case 6: case 17: case 23: C3(D_800FABD0, u16, 0xA) = 0x10; break;
            default: C3(D_800FABD0, u16, 0xA) = 0x4000; break;
            }
        } else C3(D_800FABD0, u16, 0xA) = 0x4000;
        C3(D_800FABD0, u16, 8) = C3(D_800FABD0, u16, 0xA);
        C3(D_800FABD0, u16, 6) = C3(D_800FABD0, u16, 0xA);
    } else C3(D_800FABD0, u16, 6) = C3(D_800FABD0, u16, 0xA);
    state = C3(D_800FAF58, s16, 0xA);
    if (state < 0x30) { if (state >= 0x2D) return; }
    {
        u8 *p = D_800FABD0, *g = D_800F9B60;
        C3(p, s16, 2) = 0; C3(p, s16, 4) = 0;
        C3(p, u16, 0x2E) = C3(g, u16, 0xA);
        C3(p, u32, 0x5C) &= ~7;
    }
}
#undef C3
