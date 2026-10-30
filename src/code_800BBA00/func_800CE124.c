/* @header
 * func_800CE124
 * VRAM 0x800CE124 | ROM 0xC15C4 | size 0x1A4
 * asm: asm/nonmatchings/code_800BBA00/func_800CE124.s
 */
#include "common.h"

/* Set up a launch/knockback displacement for self: pick an X/Z offset and
 * facing angle from the action bits in self+0x2C (each of 0x800/0x1000/0x2000
 * chooses a direction, sign flipped by 0x4000/0x40), store the angle on the
 * opponent, build the offset vector, and start the per-frame heading step. */
void translateEntityXZ(void *, void *);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
void func_800D3E40(void *, void *, s32, void *);
void func_800D36B4(void *, void *, void *);
s32 func_800A72FC(void *, void *, s32);

void func_800CE124(u8 *self, u8 *opp, u8 *dir)
{
    s32 angle;
    f32 vec[4];

    if (*(s32 *)(self + 0x2C) & 0x800) {
        *(f32 *)(dir + 8) = 80.0f;
        if (*(s32 *)(self + 0x2C) & 0x4000) {
            *(f32 *)(dir + 0) = -50.0f;
            angle = 0x6AB;
        } else {
            angle = 0x955;
            *(f32 *)(dir + 0) = 50.0f;
        }
    }
    if (*(s32 *)(self + 0x2C) & 0x1000) {
        *(f32 *)(dir + 8) = -80.0f;
        if (*(s32 *)(self + 0x2C) & 0x4000) {
            *(f32 *)(dir + 0) = 50.0f;
            angle = -0x155;
        } else {
            angle = 0x155;
            *(f32 *)(dir + 0) = -50.0f;
        }
    }
    if (*(s32 *)(self + 0x2C) & 0x2000) {
        *(f32 *)(dir + 0) = 0.0f;
        if (*(s32 *)(self + 0x2C) & 0x40) {
            angle = 0;
            *(f32 *)(dir + 8) = -80.0f;
        } else {
            angle = 0x800;
            *(f32 *)(dir + 8) = 80.0f;
        }
    }
    *(s32 *)(dir + 0xC) = func_800D35B0(*(s32 *)(opp + 0x58), angle);
    func_800D3E40(opp + 0x6C, dir, *(s32 *)(opp + 0x58), vec);
    func_800A72FC(self, vec, 0xA);
    func_800D36B4(self + 0x4C, self + 0x6C, vec);
    translateEntityXZ(self, vec);
    {
        s32 delta = func_800D3684(*(s32 *)(dir + 0xC), *(s32 *)(self + 0x58));
        *(s16 *)(self + 0x16) = 0;
        *(s32 *)(self + 0x348) = delta / 10;
    }
}
