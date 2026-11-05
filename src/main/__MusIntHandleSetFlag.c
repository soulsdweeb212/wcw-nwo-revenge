/* @header
 * __MusIntHandleSetFlag  (originally func_800160E8)
 * VRAM 0x800160E8 | ROM 0x16CE8 | size 0x54
 * asm: asm/nonmatchings/main/__MusIntHandleSetFlag.s
 */
/* SDK: libmus, libmus/src/player.c (same code as the SDK source). */
#include "common.h"

extern u32 max_channels;
extern u8 *mus_channels;

/* Applies the mask/value pair (flags & arg1) | arg2 to the flags word of every
 * voice whose key matches arg0. */
void __MusIntHandleSetFlag(s32 arg0, u32 arg1, u32 arg2) {
    volatile u64 pad;
    u32 n = max_channels;
    u8 *p = mus_channels;
    u32 i = 0;
    u32 count;

    if (n != 0) {
        count = n;
        do {
            i++;
            if (*(s32 *)(p + 0x60) == arg0) {
                *(s32 *)p = (*(s32 *)p & arg1) | arg2;
            }
            p += 0x158;
        } while (i < count);
    }
}
