#include "common.h"

s16 func_800D7690(void *, s32, s32);
s32 func_800D35B0(s32, s32);
void translateEntityXZ(void *, void *);

extern u8 D_8007E228[];
extern u8 D_8007EF30[];
extern u8 D_800F9850[];

/* Ticks the entity's 0x18 counter down (an extra tick when the movement check
 * succeeds) and returns 1 when it has gone negative. */
s32 func_800D7894(u8 *arg0, s32 arg1) {
    *(u16 *)(arg0 + 0x18) = *(u16 *)(arg0 + 0x18) - 1;
    if (func_800D7690(arg0, arg1 & 0xFFFF, 1) == 1) {
        *(u16 *)(arg0 + 0x18) = *(u16 *)(arg0 + 0x18) - 1;
    }
    return (u32)(s16)*(u16 *)(arg0 + 0x18) >> 31;
}
