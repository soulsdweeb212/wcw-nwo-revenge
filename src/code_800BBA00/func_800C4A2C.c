/* @header
 * func_800C4A2C
 * VRAM 0x800C4A2C | ROM 0xB7ECC | size 0x234
 * asm: asm/nonmatchings/code_800BBA00/func_800C4A2C.s
 */
#include "common.h"

extern f32 D_800E3C70[];
extern f32 D_800E3C74[];
extern s32 D_800E3CB0[];
extern s32 D_800E3CC0[];
extern s32 D_800E3F20[];
extern s32 D_800FABD8;
extern s8 D_800FADB8;

void func_800A7188(void *);
s32 func_800A7240(void *, s32, s32, u64);
void func_800A7C40(void *, s8, s16);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
s8 func_800C2CDC(void *, s32);
s32 func_800C3A78(void *, void *, s32);
s32 func_800D427C(void *, s16, s32);
s32 func_800D5438(void *, s32);

/* D_800FAF5C step machine:
 *   0: snap x/z from the dirIndex table, start the AD animation, advance;
 *   1: play the dirIndex-selected action 0x155 and advance only if it was queued;
 *   2: clear the action's flag bit and, if a target is in range, attach it (range 8);
 *   3: on animation 0x184F set the "grabbed" flag, then refresh the object. */
void func_800C4A2C(void) {
    switch (D_800FAF5C->step) {
    case 0:
        D_800FAF5C->x = D_800E3C70[D_800FAF5C->dirIndex * 2];
        D_800FAF5C->z = D_800E3C74[D_800FAF5C->dirIndex * 2];
        func_800A7C40(D_800FAF5C, D_800FAF5C->id, 0xAD);
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 2);
        func_800A7F6C(D_800FAF5C, 0);
        func_800A837C(D_800FAF5C);
        goto inc;
    case 1:
        {
            s32 queued;
            if ((u32)((u16)D_800FAF5C->animId - 0x184F) < 2)
                queued = func_800A7240(D_800FAF5C, D_800E3CB0[D_800FAF5C->dirIndex], 0x155, 0);
            else
                queued = func_800A7240(D_800FAF5C, D_800E3CC0[D_800FAF5C->dirIndex], 0x155, 0);
            if ((queued << 24) == 0)
                return;
        }
inc:
        D_800FAF5C->step = (s16)((u16)D_800FAF5C->step + 1);
        return;
    case 2:
        D_800FABD8 &= ~D_800E3F20[D_800FADB8];
        {
            s8 target = func_800C2CDC(D_800FAF5C, 1);
            if (target != -1) {
                D_800FAF5C->step = (s16)((u16)D_800FAF5C->step + 1);
                func_800C3A78(D_800FAF5C, &D_800F9D10[target], 8);
            }
        }
    case 3:
        if (D_800FAF5C->animId == 0x184F)
            D_800FAF5C->flags |= 0x80000000000ULL;
        func_800A7188(D_800FAF5C);
        break;
    }
}
