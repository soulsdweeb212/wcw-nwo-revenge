/* @header
 * func_800ADFB8
 * VRAM 0x800ADFB8 | ROM 0xA1458 | size 0x200
 * asm: asm/nonmatchings/code_8009D7A0/func_800ADFB8.s
 */
#include "common.h"

/* Combat/reaction selector, run each frame: when the actor is in action
 * state 1, copy its partnerId into opponentId when they differ and f3C passes
 * D_800E51B0, then react to its flag bits by
 * arming the self record (D_800FABD0) with a new sub-action (0x50, or the
 * 0x34/0x35 states with the opponent's state copied in) once the relevant
 * distance/timing thresholds are passed. */
typedef struct {
    u8 pad0[2]; s16 f2; s16 f4; u8 pad6[6]; s8 bC; u8 padD[0x11]; s16 s1E; u8 pad20[0xE]; s16 s2E; u8 pad30[0xC]; f32 f3C; u8 pad40[0x1C]; u32 f5C;
} Nw2FABD0;

extern Nw2FABD0 *D_800FABD0;
extern f64 D_800E51B0;
extern f64 D_800E51B8;

void func_800ADFB8(void) {
    if (D_800FAF58->state != 1) return;
    if (D_800FAF58->opponentId != D_800FAF58->partnerId) {
        if (D_800E51B0 < (f64)D_800FABD0->f3C) {
            D_800FAF58->opponentId = D_800FAF58->partnerId;
        }
    }
    if (D_800FAF58->flags & 1) {
        if (D_800FAF80->state == 0x17) {
            D_800FABD0->bC = 0x50;
        }
        if ((D_800FAF80->flags & 0x1000000000000000ULL) || (D_800FADDC->flags & 0x1000000000000000ULL)) {
            D_800FABD0->bC = 0x50;
        }
    }
    if (D_800FAF58->flags & WR_FLAG_ON_FLOOR) {
        u16 newState;
        Nw2FABD0 *actor;
        if (D_800E51B8 <= (f64)D_800FAF58->jointA[1].z) {
            D_800FABD0->f2 = 0x34;
            D_800FABD0->f4 = 0;
            D_800FABD0->s2E = D_800F9B60->state;
            D_800FABD0->f5C &= ~7;
            return;
        }
        if (D_800FAF58->id == 2) {
            actor = D_800FABD0;
            if (actor->s1E >= 2) return;
        } else {
            actor = D_800FABD0;
            if (actor->s1E < 2) return;
        }
        actor->f2 = 0x35;
        actor->f4 = 0;
        newState = D_800F9B60->state;
        actor->f5C &= ~7;
        actor->s2E = newState;
    }
}
