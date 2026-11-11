/* @header
 * applyEntityMovementC8D84  (originally func_800C8D84)
 * VRAM 0x800C8D84 | ROM 0xBC224 | size 0x290
 * asm: asm/nonmatchings/code_800BBA00/applyEntityMovementC8D84.s
 */
#include "common.h"

/* Builds and applies a wrestler's horizontal movement vector from a set of
 * direction bits, then moves the other wrestler by the same amount and keeps
 * self's and the opponent's heading in sync.
 * When bit 0x10 of ent->grappleCtx is set the direction comes from a pair of
 * tables (D_800E3C10/D_800E3C12) selected by (ent->ringSide & 1): the wrestler
 * walks forward (t) along X or Z and opposes a matching flag with -t.
 * Otherwise the 0xF00 flags pick the axis/sign directly (0x800/0x400 Z+/-,
 * 0x100/0x200 X+/-), scaled by D_800E6940 unless func_800D7A68 is odd.
 * After moving both it re-derives a +/-0x22 turn from the 0x8000/0x4000
 * flags and writes the shared heading to self and opponent, finally
 * placing the opponent's position relative to self's position. */
typedef struct { f32 a, b, c, d; } Nw2Snapshot;

#ifdef TARGET_PC
/* PC: 16-bit values, so declared u16: the PC starts game variables in its own byte order by the width their
 * declarations give (port/game_vars.tsv). */
extern u16 D_800E3C10[];
extern u16 D_800E3C12[];
#else
extern u8 D_800E3C10[];
extern u8 D_800E3C12[];
#endif
extern f64 D_800E6940;
f32 func_800D63F0(void *, void *, s32);
void func_800D2600(void *, s32, f32);
s32 func_800D7A68(s32);
s32 func_800D35B0(s32, s32);
void func_800D3E40(void *, f32 *, s32, void *);
#ifdef TARGET_PC
/* The N64 code calls translateEntityXZ without a declaration, which C89 allows; the PC compiler (C99 and later)
 * refuses that. Declared here with its definition's types (translateEntityXZ.c). */
void translateEntityXZ(Wrestler *w, f32 *d);
#endif

void applyEntityMovementC8D84(Wrestler *ent, Wrestler *other, u16 flags, f32 scale) {
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
    startPos = *(Nw2Snapshot *)&ent->x;
    move[0] = 0.0f;
    move[2] = 0.0f;
    if (ent->grappleCtx & 0x10) {
        side = ent->ringSide & 1;
#ifdef TARGET_PC
        if (flags & (*(u16 *)((u8 *)D_800E3C10 + side * 4) | *(u16 *)((u8 *)D_800E3C12 + side * 4))) {
#else
        if (flags & (*(u16 *)(D_800E3C10 + side * 4) | *(u16 *)(D_800E3C12 + side * 4))) {
#endif
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
    func_800D2600(ent, other->id, 4.0f);
    move[0] = ent->x - startPos.a;
    move[2] = ent->z - startPos.c;
    translateEntityXZ(other, move);
    func_800D2BAC(ent, other, 2.0f, 2);
    if (!(ent->grappleCtx & 0x10)) {
        delta = -((flagCopy & 0x8000) != 0) & 0x22;
        if (flagCopy & 0x4000) {
            delta = -0x22;
        }
        newMode = func_800D35B0(D_800FAF5C->heading, delta);
        partnerMode = &D_800F9B00->heading;
        D_800FAF5C->heading = newMode;
        *partnerMode = newMode;
        posRot[0] = 0.0f;
        posRot[2] = scale;
        func_800D3E40(&D_800F9B00->x, posRot, func_800D35B0(D_800F9B00->heading, 0x800), &D_800FAF5C->x);
    }
}
