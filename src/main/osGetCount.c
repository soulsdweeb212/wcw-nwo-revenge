/* @header
 * osGetCount  (originally func_80026AF0)
 * VRAM 0x80026AF0 | ROM 0x276F0 | size 0xC
 * asm: asm/nonmatchings/main/osGetCount.s
 */
/* osGetCount: libultra osGetCount(). Returns CP0 Count ($9), the free-running counter that ticks
 * at half the CPU clock (46.875 MHz). Callers: osGetTime (64-bit time = latched
 * total + Count delta), __osTimerInterrupt, __osSetTimerIntr
 * (__osSetTimerIntr), viMgrMain (VI manager frame timing) and __osRepairPackId (timestamp). It is
 * asm because mfc0 has no C form; one instruction plus the return. */
#ifdef NON_MATCHING
#include "common.h"
/* CP0 register 9 is Count: free-running, +1 every second CPU cycle (46.875 MHz on N64). */
static inline u32 getCount(void) {
    u32 count;
    __asm__ __volatile__("mfc0 %0, $9" : "=r"(count));
    return count;
}

u32 osGetCount(void) {
    return getCount();
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl osGetCount\n"
    ".ent osGetCount\n"
    "osGetCount:\n"
    "mfc0 $v0, $9 /* handwritten instruction */\n"
    "jr $ra\n"
    "nop\n"
    "nop\n"
    ".end osGetCount\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
