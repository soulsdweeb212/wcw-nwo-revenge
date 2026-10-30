/* @header
 * func_80015574
 * VRAM 0x80015574 | ROM 0x16174 | size 0x58
 * asm: asm/nonmatchings/main/func_80015574.s
 */
#include "common.h"

/* Advance a two-phase blink timer: decrement the frame countdown at +0xF0; when it
 * reaches zero, toggle the phase byte at +0xF1 and reload the countdown from the
 * other phase's duration (+0xEE or +0xEF). Returns the current phase as f32. */
f32 func_80015574(void *arg0) {
    u8 t;

    t = *(u8 *)((s8 *)arg0 + 0xF0) - 1;
    *(u8 *)((s8 *)arg0 + 0xF0) = t;
    if (!(t & 0xFF)) {
        if (*(s8 *)((s8 *)arg0 + 0xF1) == 0) {
            *(s8 *)((s8 *)arg0 + 0xF1) = (s8) *(u8 *)((s8 *)arg0 + 0xF8);
            *(u8 *)((s8 *)arg0 + 0xF0) = (u8) *(u8 *)((s8 *)arg0 + 0xEE);
        } else {
            *(s8 *)((s8 *)arg0 + 0xF1) = 0;
            *(u8 *)((s8 *)arg0 + 0xF0) = (u8) *(u8 *)((s8 *)arg0 + 0xEF);
        }
    }
    return (f32) *(s8 *)((s8 *)arg0 + 0xF1);
}
