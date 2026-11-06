/* @header
 * func_800B113C
 * VRAM 0x800B113C | ROM 0xA45DC | size 0x104
 * asm: asm/nonmatchings/code_8009D7A0/func_800B113C.s
 */
#include "common.h"

/* Two-step action handler on the D_800FABD0 record. In state 0 it arms the
 * action by storing the frames left until the opponent's hit window opens
 * (anim.hitStart - animFrame - 1, clamped to 0) into the timer at +0xE, but only
 * when the opponent's state (D_800F9B60->state) is 0x44 and the randomised aim
 * test succeeds; then it advances to state 1. State 1 counts the timer down and,
 * when it reaches 0, switches the action to its follow-up (f6 = 0x8000,
 * sub-state 1) and copies the opponent's state into +0x2E. */
s8 func_800D4198(s16);
extern u8 *D_800FABD0;

typedef struct {
    u8 pad0[2];
    s16 subState;    /* @0x2 */
    s16 state;       /* @0x4 */
    u16 f6;          /* @0x6 */
    u8 pad8[6];
    u16 timer;       /* @0xE */
    u8 pad10[2];
    s16 angle;       /* @0x12 */
    u8 pad14[0x1A];
    u16 subMode;     /* @0x2E */
    u8 pad30[0x2C];
    u32 flags;       /* @0x5C */
} Nw2ActionB113C;

void func_800B113C(void) {
    Nw2ActionB113C *p = (Nw2ActionB113C *)D_800FABD0;
    Wrestler *g;
    u16 clamp;
    u16 mode;
    s16 d;
    switch (p->state) {
    case 0:
        clamp = 0;
        if (D_800F9B60->state == 0x44 && func_800D4198(p->angle)) {
            d = (D_800F9B60->anim.hitStart - (u16)D_800F9B60->animFrame) - 1;
            clamp = d & ((~d) >> 31);
        }
        ((Nw2ActionB113C *)D_800FABD0)->timer = clamp;
        ((Nw2ActionB113C *)D_800FABD0)->state++;
        break;
    case 1:
        if ((s16)--p->timer <= 0) {
            g = D_800F9B60;
            p->f6 = 0x8000;
            p->subState = 1;
            p->state = 0;
            mode = g->state;
            p->flags &= ~7;
            p->state = 1;
            p->subMode = mode;
        }
        break;
    }
}
