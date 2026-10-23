#include "common.h"

/* Counter/reaction decision when action state 4 begins. Sets the action mode
 * (f0) to 4, then chooses a counter action (0x27..0x2A) from the opponent
 * flags (+0x20: 0x40 block, 0x80, 0x100) and the current move's distance
 * (D_800FABD0->distance[opponent quadrant at D_800F9B60+0x3E]) against the
 * thresholds D_800E4E50/58/60, gated by func_800D4198(action->f12). */
typedef struct { s16 f0; u8 pad[0x10]; s16 f12; u8 pad14[0x34]; f32 distance[4]; } ActionABE;
extern ActionABE *D_800FABD0; extern void *D_800FAF58, *D_800F9B60;
extern f64 D_800E4E50, D_800E4E58, D_800E4E60;
s8 func_800D4198(s16); void func_800AD958(s32);
#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))
#define DIST D_800FABD0->distance[F(D_800F9B60, s16, 0x3E)]
void func_800ABE20(void) {
    D_800FABD0->f0 = 4;
    if (F(D_800FAF58, u64, 0x20) & 0x40) {
        if (D_800E4E50 < DIST) func_800AD958(0x27);
        else if (F(D_800F9B60, s16, 0xA) == 10 && ((F(D_800F9B60, s16, 0xC) >= 3 && F(D_800F9B60, s16, 0xC) <= 4) || F(D_800F9B60, s16, 0xC) == 7) && func_800D4198(D_800FABD0->f12)) {
            if (DIST < D_800E4E58) func_800AD958(0x29);
            else if (F(D_800F9B60, s16, 0xC) == 3) func_800AD958(0x2A);
            else func_800AD958(0x28);
        } else if (func_800D4198(D_800FABD0->f12)) func_800AD958(0x28);
        else func_800AD958(0x27);
    } else if (F(D_800FAF58, u64, 0x20) & 0x80) func_800AD958(0x28);
    else if (F(D_800FAF58, u64, 0x20) & 0x100) {
        if (DIST < D_800E4E60) func_800AD958(0x28); else func_800AD958(0x27);
    }
}
#undef F
#undef DIST
