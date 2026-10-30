/* @header
 * func_800C16BC
 * VRAM 0x800C16BC | ROM 0xB4B5C | size 0x11C
 * asm: asm/nonmatchings/code_800BBA00/func_800C16BC.s
 */
#include "common.h"

typedef struct {
    u8 pad0[0xC];
    s16 state;
    u8 padE[0x12];
    u64 flags;
    u8 pad28[0x16];
    s16 f3E;
    u8 pad40[0xC];
    f32 f4C;
    u8 pad50[0x4];
    f32 f54;
    u8 pad58[0x14];
    f32 vec[3];
} Nw2C16BCObj;

extern void *D_800FAF5C;
extern u16 D_800E3CF0[];
extern void *D_800F9B00;
extern void *D_800F9B14;
extern f32 D_800F9B0C;
void func_800A7240(void *, void *, s32, u64);
s32 func_800D6658(void *, void *, u16, s32, f32);
void func_800A6C48(void *, s32);
s32 func_800D36E8(f32, f32);
s16 func_800D3614(s32);
void func_800E212C(void *);

/* Two-state facing/approach action on D_800FAF5C: raises the entity's
 * 0x1000000000 flag, then state 0 sets the quadrant (+0x3E) from the X/Z
 * delta (f4C/f54) and refreshes the entity; state 1 plays animation 0x155 and
 * waits for the approach test, then stores the new quadrant from the vector
 * and starts action 0x61. */
void func_800C16BC(void) {
    s32 state;

    ((Nw2C16BCObj *)D_800FAF5C)->flags |= 0x1000000000ULL;
    state = ((Nw2C16BCObj *)D_800FAF5C)->state;
    switch (state) {
    case 0:
        ((Nw2C16BCObj *)D_800FAF5C)->f3E = func_800D3614(func_800D36E8(((Nw2C16BCObj *)D_800FAF5C)->f4C, ((Nw2C16BCObj *)D_800FAF5C)->f54));
        func_800E212C(D_800FAF5C);
        ((Nw2C16BCObj *)D_800FAF5C)->state++;
        return;
    case 1:
        func_800A7240(D_800FAF5C, D_800F9B14, 0x155, 0x100000000ULL);
        if ((u16)func_800D6658(D_800FAF5C, D_800F9B00, D_800E3CF0[((Nw2C16BCObj *)D_800FAF5C)->f3E], 0, D_800F9B0C)) {
            ((Nw2C16BCObj *)D_800FAF5C)->f3E = getXZDirectionQuadrant(((Nw2C16BCObj *)D_800FAF5C)->vec);
            func_800A6C48(D_800FAF5C, 0x61);
        }
        return;
    }
}
