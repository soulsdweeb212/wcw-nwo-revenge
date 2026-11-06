/* @header
 * func_800B8278
 * VRAM 0x800B8278 | ROM 0xAB718 | size 0x154
 * asm: asm/nonmatchings/code_8009D7A0/func_800B8278.s
 */
#include "common.h"

/* Builds a bitmask over the 4 entity slots from their flag words: for each live
 * slot (characterId != -1), flag 0x8000 sets bit 6+i, else flag 0x200 sets bit i and
 * adds 0x10 (flag 0x600000000000) and 0x20 (flag 0x100). */
/* The loop body is wrapped in do { } while (0), as a macro would be: without it the delay slots are filled differently. */
u16 func_800B8278(void) {
    s16 i;
    u16 r;
    s32 lo;
    s32 hi;

    r = 0;
    lo = 1;
    hi = 0x40;
    for (i = 0; i < 4; lo <<= 1, i++, hi <<= 1) {
        do {
            if (D_800F9D10[i].characterId != -1) {
                u64 f = D_800F9D10[i].flags;

                if (D_800F9D10[i].flags & 0x8000) {
                    r |= hi;
                } else if (f & WR_FLAG_LEGAL) {
                    r |= lo;
                    if (f & 0x600000000000ULL) {
                        r |= 0x10;
                    }
                    if (D_800F9D10[i].flags & WR_FLAG_ON_FLOOR) {
                        r |= 0x20;
                    }
                }
            }
        } while (0);
    }
    return r;
}
