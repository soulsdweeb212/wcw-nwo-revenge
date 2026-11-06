/* @header
 * func_800C4610
 * VRAM 0x800C4610 | ROM 0xB7AB0 | size 0x11C
 * asm: asm/nonmatchings/code_800BBA00/func_800C4610.s
 */
#include "common.h"

s32 func_800D35B0(s32, s32);
f32 func_800D3890(void *, void *, void *);

/* Clears target flag 0x08000000, then computes a heading: attacker->heading (plus
 * 0x800 for attacker->moveId 0xB6, 0xDE..0xE0, 0xE7) turned halfway toward the
 * direction from attacker's pelvis to target's pelvis (jointA[1], func_800D3890).
 * When that heading is within 0x400 of target->heading (both face the same way),
 * target flag 0x08000000 and bit 0x1000 of target->hitInfo are set. The computed
 * heading is local only; attacker->heading is not changed. */
void func_800C4610(Wrestler *attacker, Wrestler *target) {
    Nw2DirectionResult direction;
    s32 angle;
    target->flags &= ~0x08000000ULL;
    angle = attacker->heading;
    switch (attacker->moveId) {
    case 0xB6: case 0xDE: case 0xDF: case 0xE0: case 0xE7:
        angle = func_800D35B0(angle, 0x800);
        break;
    }
    func_800D3890(&attacker->jointA[1], &target->jointA[1], &direction);
    angle = func_800D35B0(angle, func_800D3684(direction.angle, angle) / 2);
    if (func_800D3550(func_800D3684(target->heading, angle)) < 0x400) {
        target->flags |= 0x08000000ULL;
        target->hitInfo |= 0x1000;
    }
}
