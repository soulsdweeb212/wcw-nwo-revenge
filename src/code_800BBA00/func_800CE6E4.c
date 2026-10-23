#include "common.h"

void translateEntityXZ(void*,void*);
s32 func_800D35B0(s32,s32);
/* Advances the entity along its stored vector and turns it, until the +0x16
 * phase counter reaches 6 (then locks the heading to a1 and returns 1). */
s32 func_800CE6E4(u8 *p, s32 a1) {
    if (*(s16 *)(p + 0x16) < 6) {
        translateEntityXZ(p, p + 0x33C);
        *(s32 *)(p + 0x58) = func_800D35B0(*(s32 *)(p + 0x58), *(s32 *)(p + 0x348));
        (*(s16 *)(p + 0x16))++;
        return 0;
    }
    *(s32 *)(p + 0x58) = a1;
    return 1;
}
