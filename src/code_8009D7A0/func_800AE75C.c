#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;
extern u8 *D_800FAF58;
extern s16 D_800E3658[];
extern f64 D_800E4E68;
extern f64 D_800E4E70;
extern f64 D_800E4E40;
extern f64 D_800E4E38;
extern f64 D_800E4E30;
extern u8 D_800E35F8;
extern u8 D_800E35E0;
s8 func_800D4198(s16);
void func_800AD958(s32);
void func_800ADA38(void *);

/* Two-state action helper on D_800FABD0 (state +4): state 0 sets the count word
 * to 0x20 and advances; state 1 resets the action to state 0 with the entity's
 * animation copied. */
void func_800AE75C(void) {
    u8 *o = D_800FABD0;
    switch (*(s16 *)(o + 4)) {
    case 0:
        *(s16 *)(o + 6) = 0x20;
        (*(s16 *)(o + 4))++;
        break;
    case 1: {
        u8 *g = D_800F9B60;
        *(s16 *)(o + 2) = 0;
        *(s16 *)(o + 4) = 0;
        *(u16 *)(o + 0x2E) = *(u16 *)(g + 0xA);
        *(u32 *)(o + 0x5C) &= ~7;
        break;
    }
    }
}
