/* @header
 * __MusIntRemapPtrs  (originally func_80015F2C)
 * VRAM 0x80015F2C | ROM 0x16B2C | size 0x38
 * asm: asm/nonmatchings/main/__MusIntRemapPtrs.s
 */
/* SDK: libmus, libmus/src/player.c (same code as the SDK source). */
#include "common.h"

/* Adds arg1 to each of the arg2 non-zero s32 entries starting at arg0. */
void __MusIntRemapPtrs(s32 *arg0, s32 arg1, u32 arg2) {
    volatile u64 pad;
    u32 i = 0;

    if (arg2 != 0) {
        do {
            i++;
            if (*arg0 != 0) {
                *arg0 += arg1;
            }
            arg0++;
        } while (i < arg2);
    }
}
