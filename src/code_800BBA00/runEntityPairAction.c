/* @header
 * runEntityPairAction  (originally func_800CEC10)
 * VRAM 0x800CEC10 | ROM 0xC20B0 | size 0x5A8
 * asm: asm/nonmatchings/code_800BBA00/runEntityPairAction.s
 */
#include "common.h"

/* runEntityPairAction: nine-step action machine for self (D_800FAF5C) as it
 * interacts with its opponent (D_800F9B00).  It plays the reach/grab
 * animations, resolves the linked target and, once engaged, hands off to
 * updateEntityPairInteraction; steps 5..8 handle the finish/throw variants. */

extern u16 D_800FABE6;
extern f32 D_800F9B0C;
extern s32 D_800F9B14;
extern s8 D_800FADB8;
extern s16 D_800FADBE[];
extern u16 D_800FAF8E[];

void func_800D25D0(Wrestler *, f32);
s32 func_800D2B64(Wrestler *, f32, u16, s32);
void func_800D427C(Wrestler *, s16, s32);
void func_800D4AD0(Wrestler *);
void func_800D6658(Wrestler *, Wrestler *, u16, s32, f32);
void func_800A7240(Wrestler *, s32, s32, u64);
void func_800A7364(Wrestler *);
void func_800A7D1C(Wrestler *, s32);
void beginEntityActionA8D8C(Wrestler *);
void func_800A7188(Wrestler *);
void func_800E212C(Wrestler *);
void func_800B68A0(Wrestler *, Wrestler *, Wrestler *);
s8 func_800CE748(Wrestler *);
s8 updateEntityPairInteraction(Wrestler *, void *);
void func_800CF1B8(void *, void *, s32, s32);

void runEntityPairAction(void) {
    switch (D_800FAF5C->step) {
    case 0:
        D_800FADBE[D_800FADB8] = 0;
        D_800FAF8E[D_800FADB8] = 0;
        D_800FAF5C->step++;
        /* fall through */
    case 1:
        D_800FAF5C->grappleCtx = 0;
        if (D_800FAF5C->flags & WR_FLAG_SPECIAL)
            D_800FAF5C->grappleCtx = 1;
        D_800FAF5C->step++;
        /* fall through */
    case 2:
        if (D_800FAF5C->flags & 0x20000000000ULL) {
            if (D_800FAF5C->flags & WR_FLAG_ON_APRON)
                D_800FAF5C->flags |= 0x800000000000000ULL;
            func_800D25D0(D_800FAF5C, 4.0f);
            func_800D2B64(D_800FAF5C, 4.0f, 0, 0xFFFFE);
            if (D_800FAF5C->animFramesLeft <= 0) {
                D_800FAF5C->flags &= ~0x20000000000ULL;
                if (D_800FAF5C->flags & 0x800000000000000ULL) {
                    func_800A7364(D_800FAF5C);
                    func_800D427C(D_800FAF5C, 0x108D, 2);
                    return;
                }
            }
        }
        if (!(D_800FAF5C->flags & 0x20000000000ULL)) {
            func_800D6658(D_800FAF5C, D_800F9B00, D_800FABE6, 0, D_800F9B0C);
            if (!(D_800FAF5C->flags & WR_FLAG_ON_APRON)) {
                s32 animId = D_800F9B14;
                func_800A7240(D_800FAF5C, animId, 0x155, 0x100000000ULL);
            }
        }
        D_800FAF8E[D_800FADB8] |= D_800FABE6 & 0xF00;
        if (D_800FABE6 & 0x8000) {
            if ((s16)(++D_800FADBE[D_800FADB8]) >= 8) {
                D_800FAF5C->grappleCtx |= 2;
                D_800FAF5C->step++;
                D_800FAF5C->flags |= WR_FLAG_RERUN;
            }
        } else {
            D_800FAF5C->step++;
            D_800FAF5C->flags |= WR_FLAG_RERUN;
        }
        return;
    case 3:
        func_800E212C(D_800FAF5C);
        func_800CF1B8(D_800FAF5C, D_800F9B00, D_800FAF8E[D_800FADB8], D_800F9B14);
        D_800FAF5C->step++;
        break;
    case 4: {
        s8 linkedId;
        if (!(D_800FAF5C->grappleCtx & 0x14)) {
            if (D_800FAF5C->animFrame <= D_800FAF5C->anim.hitEnd)
                func_800A7240(D_800FAF5C, D_800F9B14, 0x16, 0);
        }
        linkedId = func_800CE748(D_800FAF5C);
        if (linkedId != -1) {
            if (updateEntityPairInteraction(D_800FAF5C, &D_800F9D10[linkedId]))
                return;
        }
        if (!(D_800FAF5C->flags & WR_FLAG_ON_APRON)) {
            if (D_800FAF5C->animId != 0xEA2)
                func_800D2B64(D_800FAF5C, 1.0f, 0, 2);
            func_800D25D0(D_800FAF5C, 2.0f);
        }
        func_800A7188(D_800FAF5C);
        return;
    }
    case 5:
        func_800D427C(D_800FAF5C, 0xEBC, 3);
        D_800FAF5C->step++;
        break;
    case 6:
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800A7D1C(D_800FAF5C, 1);
            func_800B68A0(D_800FAF5C, D_800F9B00, D_800FAF5C);
            func_800D4AD0(D_800FAF5C);
            beginEntityActionA8D8C(D_800FAF5C);
        }
        return;
    case 7:
        func_800D427C(D_800FAF5C, 0xE86, 3);
        D_800FAF5C->grappleCtx = 0x408;
        if (D_800FAF5C->flags & WR_FLAG_SPECIAL)
            D_800FAF5C->grappleCtx = 0x40B;
        D_800FAF5C->step = 4;
        return;
    case 8:
        func_800D427C(D_800FAF5C, 0xE87, 1);
        D_800FAF5C->grappleCtx = 0x420;
        D_800FAF5C->step = 4;
        return;
    }
}
