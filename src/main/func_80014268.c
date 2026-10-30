/* @header
 * func_80014268
 * VRAM 0x80014268 | ROM 0x14E68 | size 0x5C
 * asm: asm/nonmatchings/main/func_80014268.s
 */
#include "common.h"

extern u32 D_800604C8;
extern u8 *D_800604D0;

/* Return the s32 at +0x98 of the first voice record whose key (+0x60) matches arg0,
 * or 0 when there is no match (or arg0 is 0). */
s32 func_80014268(s32 key) {
    u32 i;
    u8 *p;

    if (key == 0) {
        return 0;
    }
    p = D_800604D0;
    for (i = 0; i < D_800604C8; i++) {
        if (*(s32 *)(p + 0x60) == key) {
            return *(s32 *)(p + 0x98);
        }
        p += 0x158;
    }
    return 0;
}
