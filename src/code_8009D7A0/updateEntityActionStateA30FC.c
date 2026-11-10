/* @header
 * updateEntityActionStateA30FC  (originally func_800A30FC)
 * VRAM 0x800A30FC | ROM 0x9659C | size 0x268
 * asm: asm/nonmatchings/code_8009D7A0/updateEntityActionStateA30FC.s
 */
#include "common.h"

/* Taunt/action step machine for D_800EB408 (switch on step):
 *  0 -> choose an animation id from the hitInfo bits and play it. The
 *       mask 0xE1 selects one of two id families (3/4/5 or 6/7/8) driven by
 *       flags 0x10000000/0x20000000/0x40000000, then advance;
 *  1 -> wait out animation, then run the shared DONE() tail;
 *  2 -> play the next animation (id from selector 3) and advance;
 *  3 -> wait out animation, then run the shared DONE() tail.
 * DONE() starts the follow-up clip and finishes the action with stateTimer 100. */
void func_800A7D1C(void *, s32);
void func_800B68A0(void *, void *, void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
s32 func_800D2B64(void *, f32, u16, s32);
#endif
void func_800D427C(void *, s32, s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D4D44 */
s16 func_800D4D44(void *, s32, f32);
#endif
#define DONE() func_800D427C(D_800EB408, func_800D4D44(D_800EB408, 2, 0.0f), 3); func_800A6C48(D_800EB408, 0x40); D_800EB408->stateTimer = 100; D_800EB408->step = 1

void updateEntityActionStateA30FC(void) {
    s16 id;
    switch (D_800EB408->step) {
    case 0:
        if (D_800EB408->hitInfo & 0xE1) {
            if (D_800EB408->hitInfo & 0x10000000)
                id = func_800D4D44(D_800EB408, 3, 0.0f);
            if (D_800EB408->hitInfo & 0x20000000)
                id = func_800D4D44(D_800EB408, 4, 0.0f);
            if (D_800EB408->hitInfo & 0x40000000)
                id = func_800D4D44(D_800EB408, 5, 0.0f);
        } else {
            if (D_800EB408->hitInfo & 0x10000000)
                id = func_800D4D44(D_800EB408, 6, 0.0f);
            if (D_800EB408->hitInfo & 0x20000000)
                id = func_800D4D44(D_800EB408, 7, 0.0f);
            if (D_800EB408->hitInfo & 0x40000000)
                id = func_800D4D44(D_800EB408, 8, 0.0f);
        }
        func_800D427C(D_800EB408, id, 1);
        D_800EB408->step++;
        break;
    case 1:
        func_800D2B64(D_800EB408, 1.0f, 0, 2);
        if (D_800EB408->animFramesLeft <= 0) {
            func_800A7D1C(D_800EB408, 3);
            func_800B68A0(D_800EB408, D_800EB408, D_800EB408);
            DONE();
        }
        break;
    case 2:
        func_800D427C(D_800EB408, func_800D4D44(D_800EB408, 3, 0.0f), 1);
        D_800EB408->step++;
        break;
    case 3:
        func_800D2B64(D_800EB408, 1.0f, 0, 2);
        if (D_800EB408->animFramesLeft <= 0) {
            DONE();
        }
        break;
    }
}
