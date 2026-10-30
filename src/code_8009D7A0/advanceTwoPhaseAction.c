/* @header
 * advanceTwoPhaseAction  (originally func_800A4D74)
 * VRAM 0x800A4D74 | ROM 0x98214 | size 0xF4
 * asm: asm/nonmatchings/code_8009D7A0/func_800A4D74.s
 */
#include "common.h"

typedef struct {
    s32 f0;
    s16 trigger;   /* @0x4: set to 1 to finish the current phase */
    s16 f6;
    s32 f8;
    s16 state;     /* @0xC */
    s16 fE;
    u8 pad10[6];
    u16 timer;     /* @0x16 */
} Nw2F408b;

s32 func_800D2B64(void *, f32, u16, s32);
void func_800D427C(void *, s32, s32);
void func_800D4AD0(void *);
void func_800A6C48(void *, s32);

#define P ((Nw2F408b *)D_800EB408)

/* Two-phase action on D_800EB408: state 0 plays animation 0xEBA and arms the
 * timer; state 1 waits for trigger == 1; state 2 plays animation 0xEBB; state 3
 * waits for trigger == 1. Either waiting state finishes with command 0x2B. */
void advanceTwoPhaseAction(void) {
    s16 state;

    func_800D2B64(D_800EB408, 1.0f, 0, 2);
    state = P->state;
    switch (state) {
    case 0:
        func_800D427C(D_800EB408, 0xEBA, 3);
        P->timer = 0;
        P->state++;
        break;
    case 1:
        P->timer++;
        if (P->trigger == 1) {
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    case 2:
        func_800D427C(D_800EB408, 0xEBB, 3);
        P->state++;
        break;
    case 3:
        if (P->trigger == 1) {
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
