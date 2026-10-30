/* @header
 * setupEntityMoveCD990  (originally func_800CD990)
 * VRAM 0x800CD990 | ROM 0xC0E30 | size 0x274
 * asm: asm/nonmatchings/code_800BBA00/setupEntityMoveCD990.s
 */
#include "common.h"

/* Sets up an entity's directional approach toward a target.
 * It computes the heading/offset to the target (func_800D3890) and stores it
 * in the per-entity heading table D_800EB600[id] with a default step count of
 * 6 in D_800EB620[id]. Successively set bits of the +0x2C flag word then pick
 * the move animation (0xE8A..0xEB4) and offset z: 0x400, 0x40, 0x80 (re-aim
 * to the target's +0x58), 0x100 (aim from D_800E3C90[+0x3C]), 0x200 (keep the
 * current heading and zero the +0x33C/+0x344 vector), 0x40000 (10 steps).
 * Unless flag 0x200 keeps the heading, it moves the entity and its target,
 * then stores the per-frame step at +0x348 and starts animation `anim`. */
extern s32 D_800EB600[], D_800E3C90[];
extern s16 D_800EB620[];
f32 func_800D3890(void *, void *, void *);
s32 func_800D35B0(s32, s32);
void func_800D3E40(void *, void *, s32, void *);
void func_800A72FC(void *, void *, s16);
void func_800D36B4(void *, void *, void *);
void translateEntityXZ(void *, void *);
void func_800D427C(void *, s32, s32);
void setupEntityMoveCD990(u8 *arg0, u8 *arg1) {
    Nw2DirectionResult dir;
    f32 pos[3];
    s32 *heading;
    s16 *steps;
    u8 id;
    s16 anim;
    s32 angle;
    s32 *headings;
    s16 *stepCounts;
    u8 *selfPos = arg0 + 0x6C, *targetPos = arg1 + 0x6C;
    id = arg0[0];
    func_800D3890(selfPos, targetPos, &dir);
    headings = D_800EB600;
    angle = dir.angle;
    stepCounts = D_800EB620;
    heading = headings + (s8)id;
    steps = stepCounts + (s8)id;
    *heading = angle;
    dir.x = 0;
    *steps = 6;
    if ((*(s32 *)(arg0 + 0x2C) & 0x400)) { anim = 0xE8A; dir.z = 73.5f; }
    if ((*(s32 *)(arg0 + 0x2C) & 0x40)) { anim = 0xE8E; dir.z = 53.5f; }
    if ((*(s32 *)(arg0 + 0x2C) & 0x80)) { anim = 0xE92; *heading = func_800D35B0(*(s32 *)(arg1 + 0x58), 0x800); dir.z = 72.1f; }
    if ((*(s32 *)(arg0 + 0x2C) & 0x100)) { anim = 0xE96; *heading = D_800E3C90[*(s16 *)(arg1 + 0x3C)]; dir.z = 76.0f; }
    if ((*(s32 *)(arg0 + 0x2C) & 0x200)) { anim = 0xE9A; *heading = *(s32 *)(arg0 + 0x58); *(s32 *)(arg0 + 0x33C) = 0; *(s32 *)(arg0 + 0x344) = 0; }
    if ((*(s32 *)(arg0 + 0x2C) & 0x40000)) { anim = 0xEB4; dir.z = 80.0f; *steps = 10; }
    if ((*(s32 *)(arg0 + 0x2C) & 0x100000)) anim = 0xE88;
    if (!(*(s32 *)(arg0 + 0x2C) & 0x200)) {
        func_800D3E40(targetPos, &dir, func_800D35B0(*heading, 0x800), pos);
        func_800A72FC(arg0, pos, *steps);
        func_800D36B4(arg0 + 0x4C, selfPos, &dir);
        translateEntityXZ(arg0, &dir);
    }
    *(s32 *)(arg0 + 0x348) = func_800D3684(*heading, *(s32 *)(arg0 + 0x58)) / *steps;
    func_800D427C(arg0, anim, 2);
    *(s16 *)(arg0 + 0x16) = 0;
}
