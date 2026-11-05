/* @header
 * __osSetCompare  (originally func_80028100)
 * VRAM 0x80028100 | ROM 0x28D00 | size 0xC
 * asm: asm/nonmatchings/main/__osSetCompare.s
 */
/* __osSetCompare: libultra __osSetCompare(u32). Writes CP0 Compare ($11). Writing Compare clears a
 * pending timer interrupt (Cause IP7) and arms the next one for when Count equals the value.
 * Callers: __osSetTimerIntr (Compare = Count + delay) and
 * __osTimerInterrupt (Compare = 0 when the timer list is empty). Asm because
 * mtc0 has no C form. */
#ifdef NON_MATCHING
#include "common.h"
/* CP0 register 11 is Compare: writing it acknowledges a pending timer interrupt (Cause IP7)
 * and arms the next one for when Count reaches the new value. */
static inline void setCompare(u32 value) {
    __asm__ __volatile__("mtc0 %0, $11" : : "r"(value));
}

void __osSetCompare(u32 value) {
    setCompare(value);
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl __osSetCompare\n"
    ".ent __osSetCompare\n"
    "__osSetCompare:\n"
    "mtc0 $a0, $11 /* handwritten instruction */\n"
    "jr $ra\n"
    "nop\n"
    "nop\n"
    ".end __osSetCompare\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
