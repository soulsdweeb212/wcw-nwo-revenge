/* @header
 * func_800DA158
 * VRAM 0x800DA158 | ROM 0xCD5F8 | size 0x180
 * asm: asm/nonmatchings/code_800BBA00/func_800DA158.s
 */
#include "common.h"

/*
 * Per-frame script update for the current object (D_800FAF5C).
 * `state` (offset 0xC) walks 0..3; states 1 and 3 wait for `timer` (offset 4)
 * to run out before cleaning up and moving on.  State 0/2 start playing a
 * sound and advance immediately.
 */
typedef struct {
    s32 f0;
    s16 timer;
    s16 f6;
    s32 f8;
    s16 state;
    s16 fE;
    u8 pad10[4];
    s16 f14;
    s16 f16;
    u8 pad18[0x24];
    s16 modelId;
    s16 collisionId;
    u8 pad40[0x18];
    s32 modelData;
} Nw2F5C;

extern void *D_800FAF5C;
extern s32 D_800E3CA0[];
extern s32 D_800E3CC0[];
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
void func_800A6C48(void *, s32);
void func_800A7364(void *);
void func_800D427C(void *, s32, s32);
void func_800D4AD0(void *);
void func_800DA3D8(void *);
void func_800E212C(void *);

void func_800DA158(void) {
    switch (((Nw2F5C *)D_800FAF5C)->state) {
    case 0:
        func_800A7364(D_800FAF5C);
        ((Nw2F5C *)D_800FAF5C)->modelData = D_800E3CA0[((Nw2F5C *)D_800FAF5C)->modelId];
        func_800D427C(D_800FAF5C, 0x1089, 2);
        func_800E212C(D_800FAF5C);
        ((Nw2F5C *)D_800FAF5C)->state++;
        break;
    case 1:
        if (((Nw2F5C *)D_800FAF5C)->timer <= 0) {
            func_800DA3D8(D_800FAF5C);
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        break;
    case 2:
        func_800D427C(D_800FAF5C,
                      func_800D3550(func_800D3684(D_800E3CC0[((Nw2F5C *)D_800FAF5C)->collisionId],
                                                  ((Nw2F5C *)D_800FAF5C)->modelData)) < 0x400
                          ? 0x10A3 : 0x10A4,
                      2);
        func_800E212C(D_800FAF5C);
        ((Nw2F5C *)D_800FAF5C)->state++;
        break;
    case 3:
        if (((Nw2F5C *)D_800FAF5C)->timer <= 0) {
            func_800DA3D8(D_800FAF5C);
            func_800D427C(D_800FAF5C, 0xF13, 2);
            func_800A6C48(D_800FAF5C, 0xA);
            ((Nw2F5C *)D_800FAF5C)->state = 4;
            ((Nw2F5C *)D_800FAF5C)->f16 = 0;
        }
        break;
    }
}
