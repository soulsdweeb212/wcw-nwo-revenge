/* @header
 * func_800ABE20
 * VRAM 0x800ABE20 | ROM 0x9F2C0 | size 0x1D8
 * asm: asm/nonmatchings/code_8009D7A0/func_800ABE20.s
 */
#include "common.h"

/* Counter/reaction decision when action state 4 begins. Sets the action mode
 * (f0) to 4, then chooses a counter action (0x27..0x2A) from the AI self's
 * zone flags (0x40 in ring, 0x80 apron, 0x100 floor), the opponent's state/step
 * and the distance D_800FABD0->distance[opponent's dirIndex] against the
 * thresholds D_800E4E50/58/60, gated by func_800D4198(action->f12). */
typedef struct { s16 f0; u8 pad[0x10]; s16 f12; u8 pad14[0x34]; f32 distance[4]; } ActionABE;
extern ActionABE *D_800FABD0; 
extern f64 D_800E4E50, D_800E4E58, D_800E4E60;
s8 func_800D4198(s16); void func_800AD958(s32);
#define DIST D_800FABD0->distance[D_800F9B60->dirIndex]
void func_800ABE20(void) {
    D_800FABD0->f0 = 4;
    if (D_800FAF58->flags & WR_FLAG_IN_RING) {
        if (D_800E4E50 < DIST) func_800AD958(0x27);
        else if (D_800F9B60->state == 10 && ((D_800F9B60->step >= 3 && D_800F9B60->step <= 4) || D_800F9B60->step == 7) && func_800D4198(D_800FABD0->f12)) {
            if (DIST < D_800E4E58) func_800AD958(0x29);
            else if (D_800F9B60->step == 3) func_800AD958(0x2A);
            else func_800AD958(0x28);
        } else if (func_800D4198(D_800FABD0->f12)) func_800AD958(0x28);
        else func_800AD958(0x27);
    } else if (D_800FAF58->flags & WR_FLAG_ON_APRON) func_800AD958(0x28);
    else if (D_800FAF58->flags & WR_FLAG_ON_FLOOR) {
        if (DIST < D_800E4E60) func_800AD958(0x28); else func_800AD958(0x27);
    }
}
#undef DIST
