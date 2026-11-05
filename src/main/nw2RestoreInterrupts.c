/* @header
 * nw2RestoreInterrupts  (originally func_80026B30)
 * VRAM 0x80026B30 | ROM 0x27730 | size 0x1C
 * asm: asm/nonmatchings/main/nw2RestoreInterrupts.s
 */
/* nw2RestoreInterrupts: libultra __osRestoreInt(OSIntMask). Status |= mask, where mask is the 0/1
 * that nw2DisableInterrupts returned, so interrupts come back on only if they were on before. Two
 * nops after mtc0 for the CP0 hazard. Paired with nw2DisableInterrupts around every critical
 * section in the OS layer (32 files: message queues, threads, timers, PI/SI managers, controller
 * pak ...). Identical to the reference __osRestoreInt, which is the same in every libultra version
 * (only __osDisableInt gained __OSGlobalIntMask handling, in 2.0J). */
#ifdef NON_MATCHING
#include "common.h"
/* CP0 register 12 is Status. The helpers are macros (not inline functions) so the register
 * variables below stay in $t0, the register the original used. Each CP0 access sits in its own
 * noreorder region so the assembler adds no hazard nops of its own; the two nops after mtc0 are
 * the original's explicit CP0 hazard slots. */
#define GET_STATUS(sr) __asm__ __volatile__(".set noreorder\n\tmfc0 %0, $12\n\t.set reorder" : "=r"(sr))
#define SET_STATUS_THEN_2_NOPS(sr) \
    __asm__ __volatile__(".set noreorder\n\tmtc0 %0, $12\n\tnop\n\tnop\n\t.set reorder" : : "r"(sr))

/* `mask` is what nw2DisableInterrupts returned: 1 if SR.IE was set before, else 0. */
void nw2RestoreInterrupts(s32 mask) {
    register u32 sr asm("$8"); /* $t0 */
    GET_STATUS(sr);
    sr |= mask;
    SET_STATUS_THEN_2_NOPS(sr);
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl nw2RestoreInterrupts\n"
    ".ent nw2RestoreInterrupts\n"
    "nw2RestoreInterrupts:\n"
    "mfc0 $t0, $12 /* handwritten instruction */\n"
    "or $t0, $t0, $a0\n"
    "mtc0 $t0, $12 /* handwritten instruction */\n"
    "nop\n"
    "nop\n"
    "jr $ra\n"
    "nop\n"
    "nop\n"
    ".end nw2RestoreInterrupts\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
