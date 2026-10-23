#include "common.h"

extern s8 D_800F99A0[];
extern u8 D_800F98E2[];

/* Swaps the id-table slot of arg1 into arg0's: stores arg0's id into arg1's
 * table record and moves the 0x30000 flag word from arg1 to arg0. */
void func_800E2090(s8 *arg0, s8 *arg1) {
    s8 temp;

    temp = D_800F99A0[arg1[0]];
    D_800F99A0[arg0[0]] = temp;
    D_800F98E2[temp * 0x30] = arg0[0];
    *(u64 *)(arg0 + 0x20) |= *(u64 *)(arg1 + 0x20) & 0x30000LL;
    *(u64 *)(arg1 + 0x20) &= ~0x30000LL;
}

s8 func_800D8DF0(u8 *);

/* Returns 1 when the entity is busy or its facing quadrant is outside the
 * direction mask arg1 (the entity's bit0 selects which two quadrants map to
 * which mask bits). */
s32 func_800DEEE8(u8 *arg0, u32 arg1) {
    s32 mask;

    if (func_800D8DF0(arg0)) {
        return 1;
    }
    mask = 0;
    if (arg0[0] & 2) {
        switch (*(s16 *)(arg0 + 0x3C)) {
        case 0: mask = 0x200; break;
        case 1: mask = 0x400; break;
        }
    } else {
        switch (*(s16 *)(arg0 + 0x3C)) {
        case 2: mask = 0x100; break;
        case 3: mask = 0x800; break;
        }
    }
    return (mask & arg1) == 0;
}
