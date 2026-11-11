/* @header
 * setupEntityMoveCD990  (originally func_800CD990)
 * VRAM 0x800CD990 | ROM 0xC0E30 | size 0x274
 * asm: asm/nonmatchings/code_800BBA00/setupEntityMoveCD990.s
 */
#include "common.h"

/* Sets up w's approach to `target` from w's grappleCtx bits. The heading table entry D_800EB600[id] starts as the
 * direction from w's pelvis (jointA[1]) to the target's (func_800D3890) and the step count D_800EB620[id] as 6.
 * Each set bit then picks the animation and a distance (later bits win): 0x400 0xE8A / 73.5, 0x40 0xE8E / 53.5,
 * 0x80 0xE92 / 72.1 with the heading = target->heading turned by 0x800, 0x100 0xE96 / 76.0 with the heading =
 * D_800E3C90[target->ringSide], 0x200 0xE9A keeping w->heading and zeroing moveDelta x/z, 0x40000 0xEB4 / 80.0 with
 * 10 steps, 0x100000 0xE88. Without bit 0x200 it sets moveDelta (func_800A72FC, over the step count) toward the
 * point that distance from the target's pelvis in the direction of the heading turned by 0x800, then moves w by
 * the XZ offset from its root to its pelvis (translateEntityXZ). Finally turnPerTick = turn from w->heading to the
 * table heading / steps, the animation is started (func_800D427C(w, anim, 2)) and stateTimer is cleared. */
extern s32 D_800EB600[], D_800E3C90[];
extern s16 D_800EB620[];
f32 func_800D3890(void *, void *, void *);
s32 func_800D35B0(s32, s32);
void func_800D3E40(void *, void *, s32, void *);
void func_800A72FC(void *, void *, s16);
void func_800D36B4(void *, void *, void *);
void translateEntityXZ(Wrestler *, f32 *);
void func_800D427C(void *, s32, s32);
void setupEntityMoveCD990(Wrestler *w, Wrestler *target) {
    Nw2DirectionResult dir;
    f32 pos[3];
    s32 *heading;
    s16 *steps;
    u8 id;
    s16 anim;
    s32 angle;
    s32 *headings;
    s16 *stepCounts;
    WrJointPos *selfPos = &w->jointA[1], *targetPos = &target->jointA[1];
    id = w->id;
    func_800D3890(selfPos, targetPos, &dir);
    headings = D_800EB600;
    angle = dir.angle;
    stepCounts = D_800EB620;
    heading = headings + (s8)id;
    steps = stepCounts + (s8)id;
    *heading = angle;
    dir.x = 0;
    *steps = 6;
    if ((w->grappleCtx & 0x400)) { anim = 0xE8A; dir.z = 73.5f; }
    if ((w->grappleCtx & 0x40)) { anim = 0xE8E; dir.z = 53.5f; }
    if ((w->grappleCtx & 0x80)) { anim = 0xE92; *heading = func_800D35B0(target->heading, 0x800); dir.z = 72.1f; }
    if ((w->grappleCtx & 0x100)) { anim = 0xE96; *heading = D_800E3C90[target->ringSide]; dir.z = 76.0f; }
    if ((w->grappleCtx & 0x200)) { anim = 0xE9A; *heading = w->heading; w->moveDelta[0] = 0; w->moveDelta[2] = 0; }
    if ((w->grappleCtx & 0x40000)) { anim = 0xEB4; dir.z = 80.0f; *steps = 10; }
    if ((w->grappleCtx & 0x100000)) anim = 0xE88;
    if (!(w->grappleCtx & 0x200)) {
        func_800D3E40(targetPos, &dir, func_800D35B0(*heading, 0x800), pos);
        func_800A72FC(w, pos, *steps);
        func_800D36B4(&w->x, selfPos, &dir);
#ifdef TARGET_PC
        /* PC: the offset's x as the f32 * the function takes; it reads x and z, at dir's +0 and +8, as on the N64. */
        translateEntityXZ(w, &dir.x);
#else
        translateEntityXZ(w, &dir);
#endif
    }
    w->turnPerTick = func_800D3684(*heading, w->heading) / *steps;
    func_800D427C(w, anim, 2);
    w->stateTimer = 0;
}
