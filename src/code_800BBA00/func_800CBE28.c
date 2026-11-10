/* @header
 * func_800CBE28
 * VRAM 0x800CBE28 | ROM 0xBF2C8 | size 0x330
 * asm: asm/nonmatchings/code_800BBA00/func_800CBE28.s
 */
#include "common.h"

extern s8 D_800FAF78;
extern u16 D_800FAF8A;

void func_800A7C40(void *, s8, s16);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *, s32);
#endif
void func_800D427C(void *, s16, s32);
s8 func_800A93C0(void);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D4AD0(void *);
s16 func_800BF2FC(void *);
void addEntityHealthDelta(void *, s32);
void beginEntityActionA8D8C(void *);

/* Three-step grapple state machine on self->step (D_800FAF5C).  Step 0
 * raises flag 0x200000000000 and sends the attack animation (0xEF + move.unk3A7)
 * via func_800A7C40/func_800D5438/func_800D427C.  Step 1 keeps that flag, toggles
 * the 0x100 'clear' bit of pairSignals from D_800FAF78, applies the 4.0f
 * separation (func_800D2BAC) unless move.flags has 0x400000, arms the 0x1 'hit' bit
 * from D_800FAF8A bit 0x10 or func_800A93C0, and when animFramesLeft runs out (or the
 * pairSignals/attached word reads 0x100000 under mask 0x180000) selects the follow-up
 * animation from the pairSignals bits (0x10 -> 6, 0x208 -> 4, else 2) and advances.
 * Step 2 runs the 2.0f separation (func_800D2BEC), clears attached[0]/flag
 * 0x40000000, ends the action via func_800BF2FC/addEntityHealthDelta, and finishes
 * with beginEntityActionA8D8C or func_800A6C48(0x2B) by move.flags bit 2. */
void func_800CBE28(void) {
    s16 animId;
    s32 mode;
    u32 f;

    switch (D_800FAF5C->step) {
    case 0:
        D_800FAF5C->flags |= 0x200000000000ULL;
        func_800A7C40(D_800FAF5C, D_800FAF5C->moveOwnerId, (s16)((s8)D_800FAF5C->move.unk3A7 + 0xEF));
        animId = func_800D5438(D_800FAF5C, 0);
        mode = 1;
        func_800D427C(D_800FAF5C, animId, mode);
        D_800FAF5C->step++;
        break;
    case 1:
        D_800FAF5C->flags |= 0x200000000000ULL;
        if (D_800FAF78) {
            D_800FAF5C->pairSignals |= 0x100;
        } else {
            D_800FAF5C->pairSignals &= 0xFEFF;
        }
        if (!(D_800FAF5C->move.flags & 0x400000)) {
            func_800D2BAC(D_800FAF5C, D_800F9B00, 4.0f, 0xFFFFE);
        }
        if (!(D_800FAF5C->pairSignals & 0x21F)) {
            if ((D_800FAF8A & 0x10) || func_800A93C0()) {
                D_800FAF5C->pairSignals |= 1;
            }
        }
        if (D_800FAF5C->pairSignals & 8) {
            D_800FAF5C->pairSignals &= 0xFFEF;
        }
        if (D_800FAF5C->animFramesLeft <= 0 || (*(u32 *)&D_800FAF5C->pairSignals & 0x180000) == 0x100000) {
            f = D_800FAF5C->pairSignals;
            if (f & 0x21F) {
                f |= 0x20;
                D_800FAF5C->pairSignals = f;
                if (f & 0x10) {
                    animId = 6;
                } else if (f & 0x208) {
                    animId = 4;
                } else {
                    animId = 2;
                }
                if (D_800FAF5C->state == 0x38) {
                    animId = animId + D_800FAF5C->animId;
                } else {
                    animId = func_800D5438(D_800FAF5C, animId);
                }
                mode = 0;
                func_800D427C(D_800FAF5C, animId, mode);
                D_800FAF5C->step++;
            }
        }
        break;
    case 2: {
        Wrestler *t;
        func_800D2BEC(D_800FAF5C, D_800F9B00, NULL, 2.0f, 0, 0xFFFFE);
        t = D_800FAF5C;
        if (t->animFramesLeft <= 0) {
            t->attached[0] = -1;
            t->flags &= ~WR_FLAG_PAIR_LEADER;
            func_800D4AD0(D_800FAF5C);
            if (func_800BF2FC(D_800FAF5C) < 0x31) {
                addEntityHealthDelta(D_800FAF5C, 3);
            }
            if (D_800FAF5C->move.flags & 2) {
                beginEntityActionA8D8C(D_800FAF5C);
            } else {
                func_800A6C48(D_800FAF5C, 0x2B);
            }
        }
        break;
    }
    default:
        break;
    }
}
