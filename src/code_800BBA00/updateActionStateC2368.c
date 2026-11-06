/* @header
 * updateActionStateC2368  (originally func_800C2368)
 * VRAM 0x800C2368 | ROM 0xB5808 | size 0x2CC
 * asm: asm/nonmatchings/code_800BBA00/updateActionStateC2368.s
 */
#include "common.h"

/* D_800FAF5C step machine (steps 0..2): step 0 reads the zone flags and moveMode to
 * pick a fall or spin animation and computes the per-tick heading step (turnPerTick);
 * step 1 either waits for the reaction probe or steps the heading over 6 ticks;
 * step 2 runs a 2.0s timeout and clears the action. Case 0 falls through to 1. */
void func_800D427C(void *, s32, s32);
s32 func_800D3684(s32, s32);
s32 func_800D35B0(s32, s32);
void func_800D7E80(void *, s32);
s8 func_800D8D74(void *, s32);
void func_800C278C(void *, f32);
void func_800D4AD0(void *);

void updateActionStateC2368(void) {
    s32 t0;
    switch (D_800FAF5C->step) {
    case 0:
        if (D_800FAF5C->flags & 0x40) {
            if (D_800FAF5C->moveMode & 0x8000) {
                func_800D7E80(D_800FAF5C, 0);
                D_800FAF5C->flags = (D_800FAF5C->flags & ~0x40ULL) | 0x80ULL;
                t0 = 0xE7E;
            } else {
                D_800FAF5C->turnPerTick = func_800D3684(D_800FAF5C->turnPerTick, D_800FAF5C->heading) / 6;
                t0 = 0xE7C;
                D_800FAF5C->flags = (D_800FAF5C->flags & ~0x40ULL) | 0x180ULL;
                D_800FAF5C->stateTimer = 0;
            }
        } else {
            if (D_800FAF5C->moveMode & 0x8000) {
                func_800D7E80(D_800FAF5C, 0);
                D_800FAF5C->flags = (D_800FAF5C->flags & ~0x100ULL) | 0x80ULL;
                t0 = 0xE81;
            } else {
                D_800FAF5C->turnPerTick = func_800D3684(D_800FAF5C->turnPerTick, D_800FAF5C->heading) / 6;
                t0 = 0xE7D;
                D_800FAF5C->flags = (D_800FAF5C->flags & ~0x100ULL) | 0xC0ULL;
                D_800FAF5C->stateTimer = 0;
            }
        }
        func_800D427C(D_800FAF5C, t0, 3);
        D_800FAF5C->step = D_800FAF5C->step + 1;
    case 1:
        D_800FAF5C->flags |= 0x1000000000ULL;
        if (D_800FAF5C->moveMode & 0x8000) {
            if (func_800D8D74(D_800FAF5C, 0)) {
                D_800FAF5C->step = D_800FAF5C->step + 1;
            }
        } else {
            D_800FAF5C->heading = func_800D35B0(D_800FAF5C->heading, D_800FAF5C->turnPerTick);
            D_800FAF5C->stateTimer = D_800FAF5C->stateTimer + 1;
            if ((s16)D_800FAF5C->stateTimer >= 6) {
                D_800FAF5C->step = D_800FAF5C->step + 1;
            }
        }
        break;
    case 2:
        func_800C278C(D_800FAF5C, 2.0f);
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        break;
    }
}
