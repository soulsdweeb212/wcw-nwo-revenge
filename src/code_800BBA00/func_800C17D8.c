#include "common.h"

typedef struct {
    u8 pad0[0xC];
    s16 state;
    u8 padE[0x12];
    u64 flags;
    u8 pad28[0x16];
    s16 f3E;
    u8 pad40[0x2C];
    f32 vec[3];
} Nw2C17D8Obj;

extern void *D_800FAF5C;
extern s32 D_800E3C90[];
extern u16 D_800E3CD0[];
extern void *D_800F9B00;
extern f32 D_800F9B0C;
void func_800A7240(void *, s32, s32, u64);
s32 func_800D6658(void *, void *, u16, s32, f32);
void func_800A6C48(void *, s32);

/* Two-state quadrant approach action on D_800FAF5C: raises the 0x1000000000
 * flag, then state 0 stores the quadrant from the facing vector; state 1 plays
 * the quadrant animation and waits for the approach test, then starts action
 * 0x60. */
void func_800C17D8(void) {
    s32 state;

    ((Nw2C17D8Obj *)D_800FAF5C)->flags |= 0x1000000000ULL;
    state = ((Nw2C17D8Obj *)D_800FAF5C)->state;
    switch (state) {
    case 0:
        ((Nw2C17D8Obj *)D_800FAF5C)->f3E = getXZDirectionQuadrant(((Nw2C17D8Obj *)D_800FAF5C)->vec);
        ((Nw2C17D8Obj *)D_800FAF5C)->state++;
        break;
    case 1:
        func_800A7240(D_800FAF5C, D_800E3C90[((Nw2C17D8Obj *)D_800FAF5C)->f3E], 0x155, 0);
        if ((u16)func_800D6658(D_800FAF5C, D_800F9B00, D_800E3CD0[((Nw2C17D8Obj *)D_800FAF5C)->f3E], 0, D_800F9B0C)) {
            func_800A6C48(D_800FAF5C, 0x60);
        }
        break;
    }
}
