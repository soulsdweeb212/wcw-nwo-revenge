#include "common.h"

extern void *D_800EB40C;
void beginEntityActionA8D8C(void *);
void func_800C472C(void *, void *, s32);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
s16 func_800D5438(void *, s32);
void func_800D7E80(void *, void *);
void func_800D8D74(void *, s32);

/* Action state machine for an entity (D_800EB408) carrying/attaching to
 * D_800EB40C. State 0 plays the carry animation and attaches to the target,
 * then falls into state 1, which drives the attach with a 0xFFFFE flag mask and,
 * once the action timer expires, releases and hands control back. */
void advanceCarryAction(void) {
    switch (((Nw2F408 *)D_800EB408)->fC) {
    case 0:
        func_800D427C(D_800EB408, func_800D5438(D_800EB40C, 1), 2);
        func_800D7E80(D_800EB408, D_800EB40C);
        ((Nw2F408 *)D_800EB408)->fC++;
    case 1:
        func_800D8D74(D_800EB408, 0);
        func_800D2BEC(D_800EB408, D_800EB40C, 0, 2.0f, 0, 0xFFFFE);
        if (((Nw2F408 *)D_800EB408)->f4 <= 0) {
            func_800D4AD0(D_800EB408);
            beginEntityActionA8D8C(D_800EB408);
            func_800C472C(D_800EB40C, D_800EB408, 2);
        }
        break;
    }
}
