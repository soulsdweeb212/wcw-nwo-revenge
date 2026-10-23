#include "common.h"

typedef struct { s32 x, y, z, heading; } Nw2PosRecord;

extern Nw2PosRecord D_800F9B18[];
extern s8 D_800FADB8;
extern void *D_800EB414;
extern void *D_800EB418;

void beginEntityActionA8D8C(void *);
void func_800B68A0(void *, void *, void *);
s8 func_800C472C(void *, void *, s32);
void func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D36B4(void *, void *, void *);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
s16 func_800D5438(void *, s32);
void translateEntityXZ(void *, void *);

/* Two-state action handler (state at action object +0xC).
 * State 0: refresh the animation, convert the action's local offset into a
 * world XZ delta and translate the object, then snapshot its position record
 * (x/y/z/heading at +0x4C) into D_800F9B18[D_800FADB8] and advance to state 1.
 * State 1: run boundary correction; when the action timer has expired, run the
 * standard teardown and either restart the entity action or finish. */
void func_800A572C(void) {
    s32 worldDelta[4];

    switch (((Nw2F408 *)D_800EB408)->fC) {
    case 0:
        func_800D427C(D_800EB408, func_800D5438(D_800EB414, 2), 0);
        func_800D36B4((void *)((u8 *)D_800EB408 + 0x4C), (void *)((u8 *)D_800EB408 + 0x6C), worldDelta);
        translateEntityXZ(D_800EB408, worldDelta);
        D_800F9B18[D_800FADB8] = *(Nw2PosRecord *)((u8 *)D_800EB408 + 0x4C);
        ((Nw2F408 *)D_800EB408)->fC++;
        break;
    case 1:
        func_800D2BEC(D_800EB408, D_800EB414, D_800EB418, 4.0f, 0, 0xFFFFE);
        if (((Nw2F408 *)D_800EB408)->f4 == 1) {
            func_800B68A0(D_800EB414, D_800EB414, D_800EB408);
        }
        if (((Nw2F408 *)D_800EB408)->f4 <= 0) {
            func_800D4AD0(D_800EB408);
            if (func_800C472C(D_800EB414, D_800EB408, 2) == 0) {
                beginEntityActionA8D8C(D_800EB408);
            }
        }
        break;
    }
}
