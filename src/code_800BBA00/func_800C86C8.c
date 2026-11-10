/* @header
 * func_800C86C8
 * VRAM 0x800C86C8 | ROM 0xBBB68 | size 0x348
 * asm: asm/nonmatchings/code_800BBA00/func_800C86C8.s
 */
#include "common.h"

extern f32 D_800EB540[];
extern u16 D_800FABE6, D_800FAF8A;
extern s8 D_800FADB8;

s8 func_800A93C0(void);
#ifndef TARGET_PC /* on PC, port_decls.h declares applyEntityMovementC8D84 and func_800D2B64 */
void applyEntityMovementC8D84(void *, void *, s32, s32);
s32 func_800D2B64(void *, f32, u16, s32);
#endif
f32 func_800D3890(void *, void *, void *);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);

/* Five-step paired-action/throw machine on self->step.  Step 0 raises the
 * 0x1000000000 flag and starts the approach animation (0x10A5/0x10B7 chosen by
 * grappleCtx bit 0x10); step 1 records the gap to the opponent (func_800D3890) into
 * the per-wrestler f32 table D_800EB540 and sends the next animation; step 2 runs
 * the contact test via applyEntityMovementC8D84 and, when the opponent's state is
 * 0x73 and the 0x10/action flags agree, arms pairSignals bits and 0x10000000; step 3
 * sends the finishing animation (0x10A9 or 0x10BB/0x10BD by pairSignals bit 0); step 4
 * keeps flag 0x1000000000 and ends the action with func_800A6C48(0x2B). */
void func_800C86C8(void) {
    s16 animId;

    switch (D_800FAF5C->step) {
    case 0:
        D_800FAF5C->flags |= 0x1000000000ULL;
        func_800D427C(D_800FAF5C, (D_800FAF5C->grappleCtx & 0x10) ? 0x10A5 : 0x10B7, 2);
        D_800FAF5C->step += 1;
        break;
    case 1:
        if (D_800FAF5C->animFramesLeft <= 0) {
            D_800EB540[(s8)D_800FADB8] = func_800D3890(&D_800FAF5C->x, &D_800F9B00->x, NULL);
            if (D_800FAF5C->grappleCtx & 0x10) {
                animId = 0x10A7;
            } else {
                animId = 0x10B9;
            }
            func_800D427C(D_800FAF5C, animId, 0);
            D_800FAF5C->step += 1;
        }
        break;
    case 2:
        if (!(D_800FAF5C->grappleCtx & 0x10)) {
            D_800FAF5C->flags |= 0x400200000000000ULL;
        }
        if (D_800F9B00->state != 0x73) {
            Wrestler *t = D_800FAF5C;
            t->attached[0] = -1;
            t->flags &= ~WR_FLAG_PAIR_LEADER;
            D_800FAF5C->step += 1;
        } else {
#ifdef TARGET_PC
            /* PC: applyEntityMovementC8D84 takes a float as its last parameter (port_decls.h), and D_800EB540 holds
             * floats (the gap recorded in step 1). The N64 code reads the float's bits as an s32 and passes them in
             * a3, an integer register, where the N64 callee reads them as a float. On the PC an s32 argument would be
             * converted to a float of another value, so the PC passes the float itself. */
            applyEntityMovementC8D84(D_800FAF5C, D_800F9B00, D_800FABE6, D_800EB540[(s8)D_800FADB8]);
#else
            applyEntityMovementC8D84(D_800FAF5C, D_800F9B00, D_800FABE6, *(s32 *)&D_800EB540[(s8)D_800FADB8]);
#endif
            if ((D_800FAF8A & 0x10) || func_800A93C0()) {
                D_800FAF5C->pairSignals |= 1;
            }
            if (D_800FAF5C->pairSignals & 3) {
                D_800FAF5C->pairSignals |= 4;
                D_800FAF5C->flags |= WR_FLAG_RERUN;
                D_800FAF5C->step++;
            }
        }
        break;
    case 3:
        if (D_800FAF5C->grappleCtx & 0x10) {
            animId = 0x10A9;
        } else {
            if (D_800F9B00->state == 0x73) {
                animId = (D_800FAF5C->pairSignals & 1) ? 0x10BB : 0x10BD;
            } else {
                animId = 0x10BD;
            }
        }
        func_800D427C(D_800FAF5C, animId, 0);
        D_800FAF5C->step += 1;
        /* fallthrough */
    case 4:
        D_800FAF5C->flags |= 0x1000000000ULL;
        func_800D2B64(D_800FAF5C, 2.0f, 0, 2);
        if (D_800FAF5C->animFramesLeft <= 0) {
            register Wrestler *t = D_800FAF5C;
            t->attached[0] = -1;
            t->flags &= ~WR_FLAG_PAIR_LEADER;
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        break;
    }
}
