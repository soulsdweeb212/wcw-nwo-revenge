/* @header
 * MusHandleGetPtrBank  (originally func_80014268)
 * VRAM 0x80014268 | ROM 0x14E68 | size 0x5C
 * asm: asm/nonmatchings/main/MusHandleGetPtrBank.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (same code as the SDK source). */
#include "common.h"

extern u32 max_channels;
extern u8 *mus_channels;

/* Return the s32 at +0x98 of the first voice record whose key (+0x60) matches arg0,
 * or 0 when there is no match (or arg0 is 0). */
s32 MusHandleGetPtrBank(s32 key) {
    u32 i;
    u8 *p;

    if (key == 0) {
        return 0;
    }
    p = mus_channels;
    for (i = 0; i < max_channels; i++) {
        if (*(s32 *)(p + 0x60) == key) {
            return *(s32 *)(p + 0x98);
        }
        p += 0x158;
    }
    return 0;
}
