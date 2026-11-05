/* @header
 * osSpTaskYielded  (originally func_80020DA0)
 * VRAM 0x80020DA0 | ROM 0x219A0 | size 0x4C
 * asm: asm/nonmatchings/main/osSpTaskYielded.s
 */
/* SDK: libultra 2.0I, ultralib src/io/sptaskyielded.c (same code as the SDK source). */
#include "common.h"

extern s32 __osSpGetStatus(void);

/* Update arg0's +4 status from the hardware VI status: when status bit 0x80 is set,
 * OR in the retrace bit (bit 8) and clear bit 1; return the retrace bit. */
s32 osSpTaskYielded(void *arg0) {
    u32 v;
    s32 r;

    v = __osSpGetStatus();
    r = v >> 8;
    r &= 1;
    if (v & 0x80) {
        *(s32 *)((u8 *)arg0 + 4) = (*(s32 *)((u8 *)arg0 + 4) | r) & ~2;
    }
    return r;
}
