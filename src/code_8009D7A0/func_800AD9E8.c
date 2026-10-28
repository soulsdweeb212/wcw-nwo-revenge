#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;
extern u8 *D_800FAF58;
s32 func_800D4148(void);

/* As func_800AD958, but only when the command actually changes. */
void func_800AD9E8(s16 arg0) {
    u8 *o = D_800FABD0;
    if (*(s16 *)(o + 2) != arg0) {
        u8 *g = D_800F9B60;
        *(s16 *)(o + 2) = arg0;
        *(s16 *)(o + 4) = 0;
        *(u16 *)(o + 0x2E) = *(u16 *)(g + 0xA);
        *(u32 *)(o + 0x5C) &= ~7;
    }
}
