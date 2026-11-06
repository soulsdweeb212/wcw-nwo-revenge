/* @header
 * func_800DA158
 * VRAM 0x800DA158 | ROM 0xCD5F8 | size 0x180
 * asm: asm/nonmatchings/code_800BBA00/func_800DA158.s
 */
#include "common.h"

/*
 * Per-frame script update for the current wrestler (D_800FAF5C).
 * `step` walks 0..3; steps 1 and 3 wait for animFramesLeft to run out before
 * cleaning up and moving on.  Step 0 sets heading from D_800E3CA0[ringSide];
 * steps 0/2 start an animation and advance immediately.
 */
extern s32 D_800E3CA0[];
extern s32 D_800E3CC0[];
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
void func_800A7364(void *);
void func_800D427C(void *, s32, s32);
void func_800D4AD0(void *);
void func_800DA3D8(void *);
void func_800E212C(void *);

void func_800DA158(void) {
    switch (D_800FAF5C->step) {
    case 0:
        func_800A7364(D_800FAF5C);
        D_800FAF5C->heading = D_800E3CA0[D_800FAF5C->ringSide];
        func_800D427C(D_800FAF5C, 0x1089, 2);
        func_800E212C(D_800FAF5C);
        D_800FAF5C->step++;
        break;
    case 1:
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800DA3D8(D_800FAF5C);
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        break;
    case 2:
        func_800D427C(D_800FAF5C,
                      func_800D3550(func_800D3684(D_800E3CC0[D_800FAF5C->dirIndex],
                                                  D_800FAF5C->heading)) < 0x400
                          ? 0x10A3 : 0x10A4,
                      2);
        func_800E212C(D_800FAF5C);
        D_800FAF5C->step++;
        break;
    case 3:
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800DA3D8(D_800FAF5C);
            func_800D427C(D_800FAF5C, 0xF13, 2);
            func_800A6C48(D_800FAF5C, 0xA);
            D_800FAF5C->step = 4;
            D_800FAF5C->stateTimer = 0;
        }
        break;
    }
}
