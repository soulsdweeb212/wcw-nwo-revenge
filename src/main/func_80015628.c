/* @header
 * func_80015628
 * VRAM 0x80015628 | ROM 0x16228 | size 0xF0
 * asm: asm/nonmatchings/main/func_80015628.s
 */
#include "common.h"

#define F(o,t) (*(t *)((u8 *)arg0+(o)))

/* Advance a sequence channel by one tick: bump the fixed-point time (u64 at
 * +0x20), decrement the note countdown at +0xC2 and, when it expires, read the
 * next event byte from the stream at +0x4C. A byte >= 0x80 is a detune/length
 * command that masks the note byte at +0xDC; otherwise the byte is the note and
 * the countdown becomes 1. Runs until the time reaches the end time at +0x10. */
void func_80015628(void *arg0) {
    u8 c;
    u16 n;
    do {
        n = F(0xC2, u16) - 1;
        F(0x20, u64) += 0x100;
        F(0xC2, u16) = n;
        if (!n) {
            c = *F(0x4C, u8 *)++;
            if (c >= 0x80) {
                F(0xDC, u8) = c & 0x7F;
                c = *F(0x4C, u8 *)++;
                if (c >= 0x80) {
                    F(0xC2, u16) = (c & 0x7F) << 8;
                    F(0xC2, u16) += *F(0x4C, u8 *)++ + 2;
                } else F(0xC2, u16) = c + 2;
            } else {
                F(0xDC, u8) = c; F(0xC2, u16) = 1;
            }
        }
    } while (F(0x20, u64) < F(0x10, u64));
}
#undef F
