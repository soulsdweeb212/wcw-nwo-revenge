/* @header
 * applyEntityMovementC8D84  (originally func_800C8D84)
 * VRAM 0x800C8D84 | ROM 0xBC224 | size 0x290
 * asm: asm/nonmatchings/code_800BBA00/applyEntityMovementC8D84.s
 */
#include "common.h"

/* Builds and applies an entity's horizontal movement vector from a set of
 * direction bits, then moves the other entity away and keeps the two
 * entities' +0x58 value in sync.
 * When bit 0x10 of ent+0x2C is set the direction comes from a pair of
 * tables (D_800E3C10/D_800E3C12) selected by (ent+0x3C & 1): the entity
 * walks forward (t) along X or Z and opposes a matching flag with -t.
 * Otherwise the 0xF00 flags pick the axis/sign directly (0x800/0x400 Z+/-,
 * 0x100/0x200 X+/-), scaled by D_800E6940 unless func_800D7A68 is odd.
 * After moving both entities it re-derives a +/-0x22 delta from the 0x8000/
 * 0x4000 flags and reapplies the shared +0x58 value to both, finally
 * orienting the other entity's +0x4C vector toward ent+0x4C. */
typedef struct { f32 a, b, c, d; } Nw2Snapshot;

extern u8 D_800E3C10[];
extern u8 D_800E3C12[];
extern f64 D_800E6940;
extern void *D_800F9B00;
extern void *D_800FAF5C;
f32 func_800D63F0(void *, void *, s32);
void func_800D2600(void *, s32, f32);
s32 func_800D2BAC(void *, void *, f32, s32);
s32 func_800D7A68(s32);
s32 func_800D35B0(s32, s32);
void func_800D3E40(void *, f32 *, s32, void *);

void applyEntityMovementC8D84(u8 *ent, u8 *other, u16 flags, f32 scale) {
    f32 posRot[4];
    f32 move[3];
    Nw2Snapshot startPos;
    u16 side;
    f32 speed;
    s32 delta;
    s32 newMode;
    u16 flagCopy;
    s32 *partnerMode;

    flagCopy = flags;
    startPos = *(Nw2Snapshot *)(ent + 0x4C);
    move[0] = 0.0f;
    move[2] = 0.0f;
    if (*(u32 *)(ent + 0x2C) & 0x10) {
        side = *(u16 *)(ent + 0x3C) & 1;
        if (flags & (*(u16 *)(D_800E3C10 + side * 4) | *(u16 *)(D_800E3C12 + side * 4))) {
            speed = func_800D63F0(ent, 0, 4);
            if (side != 0) {
                move[0] = 0.0f;
                if (flags & 0x800) {
                    move[2] = speed;
                } else {
                    move[2] = -speed;
                }
            } else {
                move[2] = 0.0f;
                if (flags & 0x100) {
                    move[0] = speed;
                } else {
                    move[0] = -speed;
                }
            }
        }
    } else if (flags & 0xF00) {
        speed = func_800D63F0(ent, 0, 4);
        if (flags & 0x800) {
            move[2] = speed;
        }
        if (flags & 0x100) {
            move[0] = speed;
        }
        if (flags & 0x400) {
            move[2] = -speed;
        }
        if (flags & 0x200) {
            move[0] = -speed;
        }
        if (!(func_800D7A68(flagCopy & 0xFFFF) & 1)) {
            move[0] = (f32)((f64)move[0] * D_800E6940);
            move[2] = (f32)((f64)move[2] * D_800E6940);
        }
    }
    translateEntityXZ(ent, move);
    func_800D2600(ent, *(s8 *)other, 4.0f);
    move[0] = *(f32 *)(ent + 0x4C) - startPos.a;
    move[2] = *(f32 *)(ent + 0x54) - startPos.c;
    translateEntityXZ(other, move);
    func_800D2BAC(ent, other, 2.0f, 2);
    if (!(*(u32 *)(ent + 0x2C) & 0x10)) {
        delta = -((flagCopy & 0x8000) != 0) & 0x22;
        if (flagCopy & 0x4000) {
            delta = -0x22;
        }
        newMode = func_800D35B0(*(s32 *)((u8 *)D_800FAF5C + 0x58), delta);
        partnerMode = (s32 *)((u8 *)D_800F9B00 + 0x58);
        *(s32 *)((u8 *)D_800FAF5C + 0x58) = newMode;
        *partnerMode = newMode;
        posRot[0] = 0.0f;
        posRot[2] = scale;
        func_800D3E40((u8 *)D_800F9B00 + 0x4C, posRot, func_800D35B0(*(s32 *)((u8 *)D_800F9B00 + 0x58), 0x800), (u8 *)D_800FAF5C + 0x4C);
    }
}
