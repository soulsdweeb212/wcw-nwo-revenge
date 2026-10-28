#include "common.h"

extern s8 D_800F99A0[];
extern u8 D_800F98E2[];

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
