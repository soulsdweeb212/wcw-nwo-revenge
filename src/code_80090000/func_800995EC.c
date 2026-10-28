#include "common.h"

extern u8 updateEntityReactionState[];
s32 func_80099734(s32);
void func_800B75D4(s32 *, s32, s32);
u8 *func_80028D18(s32, s32);
u8 *func_80029A24(u8 *, s32, s32);

/* Builds the name string for arg0 into its cached record (or returns the
 * default string), appending the 0x28/0x29 encoded groups for the upper bits. */
u8 *func_800995EC(u32 arg0) {
    u8 *r;
    u8 *p;

    r = func_80028D18(arg0, 4);
    if (r == NULL) {
        return updateEntityReactionState + 0x200;
    }
    if (*r != 0) {
        return r;
    }
    p = func_80029A24(r, arg0 & 0x3F, 0);
    if ((arg0 >> 10) & 0x1F) {
        *p = 0x28;
        p = func_80029A24(p + 1, (arg0 >> 12) & 0x3F, 0);
        *p = 0x29;
        p = p + 1;
    }
    *p = 0;
    return r;
}
