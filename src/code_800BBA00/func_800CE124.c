/* @header
 * func_800CE124
 * VRAM 0x800CE124 | ROM 0xC15C4 | size 0x1A4
 * asm: asm/nonmatchings/code_800BBA00/func_800CE124.s
 */
#include "common.h"

/* Set up a 10-tick scripted move of self around opp: pick an X/Z offset and a
 * facing angle from self->grappleCtx (each of 0x800/0x1000/0x2000 chooses a
 * direction, sign flipped by 0x4000/0x40), store opp->heading + angle in dir+0xC,
 * rotate the offset by opp->heading around opp's pelvis (jointA[1]) into vec, set
 * self->moveDelta to 1/10 of the way from self's pelvis to vec (func_800A72FC),
 * shift self's body by the root-to-pelvis delta (func_800D36B4 + translateEntityXZ),
 * clear stateTimer and set turnPerTick to 1/10 of the turn to the dir+0xC heading. */
void translateEntityXZ(void *, void *);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
void func_800D3E40(void *, void *, s32, void *);
void func_800D36B4(void *, void *, void *);
s32 func_800A72FC(void *, void *, s32);

void func_800CE124(Wrestler *self, Wrestler *opp, u8 *dir)
{
    s32 angle;
    f32 vec[4];

    if (self->grappleCtx & 0x800) {
        *(f32 *)(dir + 8) = 80.0f;
        if (self->grappleCtx & 0x4000) {
            *(f32 *)(dir + 0) = -50.0f;
            angle = 0x6AB;
        } else {
            angle = 0x955;
            *(f32 *)(dir + 0) = 50.0f;
        }
    }
    if (self->grappleCtx & 0x1000) {
        *(f32 *)(dir + 8) = -80.0f;
        if (self->grappleCtx & 0x4000) {
            *(f32 *)(dir + 0) = 50.0f;
            angle = -0x155;
        } else {
            angle = 0x155;
            *(f32 *)(dir + 0) = -50.0f;
        }
    }
    if (self->grappleCtx & 0x2000) {
        *(f32 *)(dir + 0) = 0.0f;
        if (self->grappleCtx & 0x40) {
            angle = 0;
            *(f32 *)(dir + 8) = -80.0f;
        } else {
            angle = 0x800;
            *(f32 *)(dir + 8) = 80.0f;
        }
    }
    *(s32 *)(dir + 0xC) = func_800D35B0(opp->heading, angle);
    func_800D3E40(&opp->jointA[1], dir, opp->heading, vec);
    func_800A72FC(self, vec, 0xA);
    func_800D36B4(&self->x, &self->jointA[1], vec);
    translateEntityXZ(self, vec);
    {
        s32 delta = func_800D3684(*(s32 *)(dir + 0xC), self->heading);
        self->stateTimer = 0;
        self->turnPerTick = delta / 10;
    }
}
