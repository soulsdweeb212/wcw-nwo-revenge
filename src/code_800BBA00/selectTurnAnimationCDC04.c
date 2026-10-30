/* @header
 * selectTurnAnimationCDC04  (originally func_800CDC04)
 * VRAM 0x800CDC04 | ROM 0xC10A4 | size 0x2E0
 * asm: asm/nonmatchings/code_800BBA00/selectTurnAnimationCDC04.s
 */
#include "common.h"

/* Turn/step animation selector: reads the driver's state flags (+0x2C) and sets
 * `actor`'s heading and animation accordingly, then stores the per-frame heading
 * delta divided by the actor's step count into actor+0x348. The step count is
 * reset to 6 (or 0xA for the 0x40000 case) in D_800EB628[actorId]. */
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
void translateEntityXZ(void *, void *);

void selectTurnAnimationCDC04(void *actor, void *driver) {
    s8 id = *(s8 *)actor;
    s16 driverId = *(s8 *)driver;
    s16 *countTable = D_800EB628;
    s16 *countPtr = countTable + id;
    s16 anim;
    f32 offset[3];
    f32 result[4];
    f32 position[4];

    *countPtr = 6;
    if (*(u32 *)((u8 *)driver + 0x2C) & 0x400) {
        anim = 0xE8B;
        D_800EB610[id] = func_800D35B0(D_800EB600[driverId], 0x800);
    }
    if (*(u32 *)((u8 *)driver + 0x2C) & 0x40) {
        D_800EB610[id] = D_800EB600[driverId];
        anim = 0xE8F;
    }
    if (*(u32 *)((u8 *)driver + 0x2C) & 0x80) {
        anim = 0xE93;
        D_800EB610[id] = func_800D35B0(D_800EB600[driverId], 0x800);
    }
    if (*(u32 *)((u8 *)driver + 0x2C) & 0x100) {
        anim = 0xE97;
        D_800EB610[id] = func_800D35B0(D_800EB600[driverId], 0x800);
        func_800A7364(actor);
    }
    if (*(u32 *)((u8 *)driver + 0x2C) & 0x200) {
        D_800EB610[id] = func_800D35B0(D_800EB600[driverId], 0x800);
        offset[0] = 0.0f;
        offset[2] = 82.5f;
        anim = 0xE9B;
        func_800D3E40((u8 *)driver + 0x4C, offset, func_800D35B0(D_800EB610[id], 0x800), result);
        func_800A72FC(actor, result, *countPtr);
    }
    if (*(u32 *)((u8 *)driver + 0x2C) & 0x40000) {
        anim = 0xEB5;
        D_800EB610[id] = func_800D35B0(D_800EB600[driverId], 0x800);
        *countPtr = 0xA;
    }
    if (*(u32 *)((u8 *)driver + 0x2C) & 0x40640) {
        func_800D36B4((u8 *)actor + 0x4C, (u8 *)actor + 0x6C, position);
        translateEntityXZ(actor, position);
    }
    if (*(u32 *)((u8 *)driver + 0x2C) & 0x100000) {
        anim = 0xE89;
    }
    func_800D427C(actor, anim, 2);
    *(s32 *)((u8 *)actor + 0x348) = func_800D3684(D_800EB610[id], *(s32 *)((u8 *)actor + 0x58)) / *countPtr;
}
