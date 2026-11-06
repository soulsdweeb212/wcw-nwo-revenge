/* @header
 * func_800A83DC
 * VRAM 0x800A83DC | ROM 0x9B87C | size 0x938
 * asm: asm/nonmatchings/code_8009D7A0/func_800A83DC.s
 */
#include "common.h"

extern u8 D_80075468[];

void func_800D4AD0(Wrestler *);
void func_800D4B10(Wrestler *);
void func_800D427C(Wrestler *, s16, s32);
s16 func_800D5438(Wrestler *, s32);
void unpackAnimationParameters(void *, void *);

/* Enter state st: step, stepFlags and pairSignals cleared, flags bits 0x10810000000 cleared and 0x1000000000 set;
 * func_800DECAC(w, 0, 0, 0) only zeroes D_800F98D0[w->id]. */
#define SETACT(w, st) \
    (w)->state = (st); \
    (w)->step = 0; \
    (w)->stepFlags = 0; \
    (w)->pairSignals = 0; \
    (w)->flags = ((w)->flags & ~0x10810000000ULL) | 0x1000000000ULL; \
    func_800DECAC((w), 0, 0, 0);

/* Inlined copy of func_800A7C40: make entry moveId of owner's move table the current move of w. */
static inline void load83(Wrestler *w, s8 owner, s16 moveId)
{
    u8 *tbl;
    w->moveOwnerId = owner;
    w->moveId = moveId;
    tbl = &D_80075468[0x10] + w->moveOwnerId * 0x1A30;
    unpackAnimationParameters(&w->move, tbl + moveId * 0x18);
    if (moveId < 0xEF) {
        if (w->move.flags & 0x8000) {
            w->flags |= 0x4000000000000000ULL;
        } else {
            w->flags &= ~0x4000000000000000ULL;
        }
    }
}

/* Called for the mover a and its opponent b once a's animation has ended (the callers test animFramesLeft <= 0).
 * Clears flags bits 0x3800000 on both, then:
 * - anim.endPose 5 and move.moveCode 0: both finish their animation (func_800D4AD0); a enters state 0x45 step 2
 *   (grappleCtx = (b's grappleCtx & 2) | 0x440, stateTimer 0x5A, or 0x3C without bit 2) with animation 0xE8E,
 *   b enters state 0x46 step 2 (stateTimer and grappleCtx 0) with 0xE8F (both through func_800D427C(w, id, 1)).
 * - move.flags & 0x1E00 (paired-move kinds): both apply anim.endZone (func_800D4B10); b's lastMoveTakenId /
 *   lastMoveTakenParam = a's move.nameId / move.unk3A4; states 0x3E/0x3F when bit 0x200 is set, else 0x3C/0x3D.
 * - moveCode 0x9D/0x9F (state 0x1F) or 0xA1/0xA3 (state 7): only a, which drops attached[0] and
 *   WR_FLAG_PAIR_LEADER, finishes its animation and enters that state at step 1.
 * - other nonzero moveCode: both finish their animation. For 0x99..0xA6, a->counterKind = 0, 1, 2, 4 ... 0x20
 *   picked from the code (0x9A and 0xA5 have no case, so m is stored uninitialised) and the states are 0x58/0x59.
 *   Otherwise a's current move becomes entry moveCode of its own move table (inlined func_800A7C40), func_800D427C
 *   starts func_800D5438(a, 0) on a and func_800D5438(a, 1) on b, and the states are 0x49/0x4A (moveCode
 *   0x5A..0x69, also grappleCtx |= 0x80) or 0x53/0x54.
 * Every state change goes through SETACT and, except in the first case, sets WR_FLAG_RERUN. Returns 1 when one of
 * these cases applied, 0 otherwise (anim.endPose not 5, no 0x1E00 bit, moveCode 0: only the 0x3800000 bits were
 * cleared). */
s32 func_800A83DC(Wrestler *a, Wrestler *b)
{
    s32 k;
    s16 m;

    a->flags &= ~0x3800000ULL;
    b->flags &= ~0x3800000ULL;
    if (a->anim.endPose == 5 && a->move.moveCode == 0) {
        func_800D4AD0(a);
        func_800D4AD0(b);
        SETACT(a, 0x45);
        a->step = 2;
        a->grappleCtx = (b->grappleCtx & 2) | 0x440;
        if (a->grappleCtx & 2) {
            if (b) {
                a->stateTimer = 0x5A;
            } else {
                a->stateTimer = 0x5A;
            }
        } else {
            a->stateTimer = 0x3C;
        }
        func_800D427C(a, 0xE8E, 1);
        SETACT(b, 0x46);
        b->step = 2;
        b->stateTimer = 0;
        b->grappleCtx = 0;
        func_800D427C(b, 0xE8F, 1);
        goto done;
    }
    if (a->move.flags & 0x1E00) {
        func_800D4B10(a);
        func_800D4B10(b);
        b->lastMoveTakenId = a->move.nameId;
        b->lastMoveTakenParam = a->move.unk3A4;
        if (a->move.flags & 0x200) {
            SETACT(a, 0x3E);
            a->flags |= WR_FLAG_RERUN;
            SETACT(b, 0x3F);
            b->flags |= WR_FLAG_RERUN;
        } else {
            SETACT(a, 0x3C);
            a->flags |= WR_FLAG_RERUN;
            SETACT(b, 0x3D);
            b->flags |= WR_FLAG_RERUN;
        }
        goto done;
    }
    if (a->move.moveCode != 0) {
        if (a->move.moveCode == 0x9F || a->move.moveCode == 0x9D) {
            a->attached[0] = -1;
            a->flags &= ~WR_FLAG_PAIR_LEADER;
            func_800D4AD0(a);
            SETACT(a, 0x1F);
            a->step = 1;
            a->flags |= WR_FLAG_RERUN;
            goto done;
        }
        if (a->move.moveCode == 0xA1 || a->move.moveCode == 0xA3) {
            a->attached[0] = -1;
            a->flags &= ~WR_FLAG_PAIR_LEADER;
            func_800D4AD0(a);
            SETACT(a, 7);
            a->step = 1;
            a->flags |= WR_FLAG_RERUN;
            goto done;
        }
        func_800D4AD0(a);
        func_800D4AD0(b);
        k = a->move.moveCode;
        if ((u8)(k - 0x99) < 14) {
            switch (k) {
            case 0x99: m = 0; break;
            case 0x9B: case 0x9C: m = 1; break;
            case 0x9E: m = 2; break;
            case 0xA0: m = 4; break;
            case 0xA2: m = 8; break;
            case 0xA4: m = 0x10; break;
            case 0xA6: m = 0x20; break;
            }
            a->counterKind = m;
            SETACT(a, 0x58);
            a->flags |= WR_FLAG_RERUN;
            SETACT(b, 0x59);
            b->flags |= WR_FLAG_RERUN;
        } else if ((u32)(k - 0x5A) < 0x10) {
            load83(a, a->id, (u8)k);
            func_800D427C(a, func_800D5438(a, 0), 1);
            func_800D427C(b, func_800D5438(a, 1), 1);

            a->grappleCtx |= 0x80;
            SETACT(a, 0x49);
            a->flags |= WR_FLAG_RERUN;
            SETACT(b, 0x4A);
            b->flags |= WR_FLAG_RERUN;
        } else {
            load83(a, a->id, (u8)k);
            func_800D427C(a, func_800D5438(a, 0), 1);
            func_800D427C(b, func_800D5438(a, 1), 1);

            SETACT(a, 0x53);
            a->flags |= WR_FLAG_RERUN;
            SETACT(b, 0x54);
            b->flags |= WR_FLAG_RERUN;
        }
        goto done;
    }
    return 0;
done:
    return 1;
}
