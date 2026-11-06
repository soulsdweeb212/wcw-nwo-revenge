/* @header
 * selectTurnAnimationCDC04  (originally func_800CDC04)
 * VRAM 0x800CDC04 | ROM 0xC10A4 | size 0x2E0
 * asm: asm/nonmatchings/code_800BBA00/selectTurnAnimationCDC04.s
 */
#include "common.h"

/* Turn/step animation selector for `actor` paired with `driver`: from the driver's grappleCtx bits it picks the
 * animation (0xE8B, 0xE8F, 0xE93, 0xE97, 0xE9B, 0xEB5, 0xE89; later bits win) and the target heading
 * D_800EB610[id], mostly the driver's heading table entry D_800EB600[driver id] turned by 0x800 (bit 0x40: taken
 * unchanged). Bit 0x100 also calls func_800A7364(actor) (root x/z to the pelvis, then onto the apron line of its
 * ringSide); bit 0x200 sets moveDelta (func_800A72FC, over the step count) toward the point 82.5 from the driver's
 * root in the direction of the target heading turned by 0x800; bits 0x40640 move the actor by the XZ offset from
 * its root to its pelvis (jointA[1]). The step count D_800EB628[id] is 6 (0xA for bit 0x40000). Starts the
 * animation with func_800D427C(actor, anim, 2) and sets turnPerTick to the signed turn from heading to the target
 * heading divided by the step count. */
extern s32 D_800EB600[];
extern s32 D_800EB610[];
extern s16 D_800EB628[];

s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
void func_800D36B4(void *, void *, void *);
void func_800D3E40(void *, f32 *, s32, void *);
void func_800A72FC(void *, void *, s16);
void func_800A7364(void *);
void func_800D427C(void *, s16, s32);
void translateEntityXZ(Wrestler *, f32 *);

void selectTurnAnimationCDC04(Wrestler *actor, Wrestler *driver) {
    s8 id = actor->id;
    s16 driverId = driver->id;
    s16 *countTable = D_800EB628;
    s16 *countPtr = countTable + id;
    s16 anim;
    f32 offset[3];
    f32 result[4];
    f32 position[4];

    *countPtr = 6;
    if (driver->grappleCtx & 0x400) {
        anim = 0xE8B;
        D_800EB610[id] = func_800D35B0(D_800EB600[driverId], 0x800);
    }
    if (driver->grappleCtx & 0x40) {
        D_800EB610[id] = D_800EB600[driverId];
        anim = 0xE8F;
    }
    if (driver->grappleCtx & 0x80) {
        anim = 0xE93;
        D_800EB610[id] = func_800D35B0(D_800EB600[driverId], 0x800);
    }
    if (driver->grappleCtx & 0x100) {
        anim = 0xE97;
        D_800EB610[id] = func_800D35B0(D_800EB600[driverId], 0x800);
        func_800A7364(actor);
    }
    if (driver->grappleCtx & 0x200) {
        D_800EB610[id] = func_800D35B0(D_800EB600[driverId], 0x800);
        offset[0] = 0.0f;
        offset[2] = 82.5f;
        anim = 0xE9B;
        func_800D3E40(&driver->x, offset, func_800D35B0(D_800EB610[id], 0x800), result);
        func_800A72FC(actor, result, *countPtr);
    }
    if (driver->grappleCtx & 0x40000) {
        anim = 0xEB5;
        D_800EB610[id] = func_800D35B0(D_800EB600[driverId], 0x800);
        *countPtr = 0xA;
    }
    if (driver->grappleCtx & 0x40640) {
        func_800D36B4(&actor->x, &actor->jointA[1], position);
        translateEntityXZ(actor, position);
    }
    if (driver->grappleCtx & 0x100000) {
        anim = 0xE89;
    }
    func_800D427C(actor, anim, 2);
    actor->turnPerTick = func_800D3684(D_800EB610[id], actor->heading) / *countPtr;
}
