/* @header
 * func_800A572C
 * VRAM 0x800A572C | ROM 0x98BCC | size 0x190
 * asm: asm/nonmatchings/code_8009D7A0/func_800A572C.s
 */
#include "common.h"

typedef struct { s32 x, y, z, heading; } Nw2PosRecord;

extern Nw2PosRecord D_800F9B18[];
extern s8 D_800FADB8;

void beginEntityActionA8D8C(void *);
void func_800B68A0(void *, void *, void *);
s8 func_800C472C(void *, void *, s32);
void func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D36B4(void *, void *, void *);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
s16 func_800D5438(void *, s32);
void translateEntityXZ(void *, void *);

/* Two-step action handler on D_800EB408, held by D_800EB414.
 * Step 0: start the holder's animation, compute a world XZ delta from the root
 * position and the pelvis (jointA[1]) and translate the wrestler by it, then snapshot x/y/z/heading
 * into D_800F9B18[D_800FADB8] and advance to step 1.
 * Step 1: run boundary correction; when the animation has ended, run the
 * standard teardown and either restart the entity action or finish. */
void func_800A572C(void) {
    s32 worldDelta[4];

    switch (D_800EB408->step) {
    case 0:
        func_800D427C(D_800EB408, func_800D5438(D_800EB414, 2), 0);
        func_800D36B4(&D_800EB408->x, &D_800EB408->jointA[1], worldDelta);
        translateEntityXZ(D_800EB408, worldDelta);
        D_800F9B18[D_800FADB8] = *(Nw2PosRecord *)&D_800EB408->x;
        D_800EB408->step++;
        break;
    case 1:
        func_800D2BEC(D_800EB408, D_800EB414, D_800EB418, 4.0f, 0, 0xFFFFE);
        if (D_800EB408->animFramesLeft == 1) {
            func_800B68A0(D_800EB414, D_800EB414, D_800EB408);
        }
        if (D_800EB408->animFramesLeft <= 0) {
            func_800D4AD0(D_800EB408);
            if (func_800C472C(D_800EB414, D_800EB408, 2) == 0) {
                beginEntityActionA8D8C(D_800EB408);
            }
        }
        break;
    }
}
