/* @header
 * func_800ADFB8
 * VRAM 0x800ADFB8 | ROM 0xA1458 | size 0x200
 * asm: asm/nonmatchings/code_8009D7A0/func_800ADFB8.s
 */
#include "common.h"

/* Combat/reaction selector, run each frame: when the actor is in action
 * state 1, latch its current attack byte, then react to its flag bits by
 * arming the self record (D_800FABD0) with a new sub-action (0x50, or the
 * 0x34/0x35 states with the opponent's state copied in) once the relevant
 * distance/timing thresholds are passed. */
typedef struct {
    s8 b0; u8 pad1[0x9]; s16 state; u8 padC[0x14]; u64 flags; u8 pad28[0x4C]; f32 f74; u8 pad78[0x2DB]; s8 b353; s8 b354; s8 b355;
} Nw2FAF58;
typedef struct {
    u8 pad0[0xA]; s16 state; u8 padC[0x14]; u64 flags;
} Nw2FAF80;
typedef struct {
    u8 pad0[0x20]; u64 flags;
} Nw2FADDC;
typedef struct {
    u8 pad0[2]; s16 f2; s16 f4; u8 pad6[6]; s8 bC; u8 padD[0x11]; s16 s1E; u8 pad20[0xE]; s16 s2E; u8 pad30[0xC]; f32 f3C; u8 pad40[0x1C]; u32 f5C;
} Nw2FABD0;
typedef struct {
    u8 pad0[0xA]; u16 uA;
} Nw2F9B60;

extern Nw2FAF58 *D_800FAF58;
extern Nw2FAF80 *D_800FAF80;
extern Nw2FADDC *D_800FADDC;
extern Nw2FABD0 *D_800FABD0;
extern Nw2F9B60 *D_800F9B60;
extern f64 D_800E51B0;
extern f64 D_800E51B8;

void func_800ADFB8(void) {
    if (D_800FAF58->state != 1) return;
    if (D_800FAF58->b353 != D_800FAF58->b355) {
        if (D_800E51B0 < (f64)D_800FABD0->f3C) {
            D_800FAF58->b353 = D_800FAF58->b355;
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
    if (D_800FAF58->flags & 0x100) {
        u16 newState;
        Nw2FABD0 *actor;
        if (D_800E51B8 <= (f64)D_800FAF58->f74) {
            D_800FABD0->f2 = 0x34;
            D_800FABD0->f4 = 0;
            D_800FABD0->s2E = D_800F9B60->uA;
            D_800FABD0->f5C &= ~7;
            return;
        }
        if (D_800FAF58->b0 == 2) {
            actor = D_800FABD0;
            if (actor->s1E >= 2) return;
        } else {
            actor = D_800FABD0;
            if (actor->s1E < 2) return;
        }
        actor->f2 = 0x35;
        actor->f4 = 0;
        newState = D_800F9B60->uA;
        actor->f5C &= ~7;
        actor->s2E = newState;
    }
}
