/* @header
 * nw2DisableInterrupts  (originally func_80026B10)
 * VRAM 0x80026B10 | ROM 0x27710 | size 0x20
 * asm: asm/nonmatchings/main/nw2DisableInterrupts.s
 */
/* nw2DisableInterrupts: libultra __osDisableInt(). Clears Status.IE (bit 0) and returns its
 * previous value (0 or 1) for nw2RestoreInterrupts. The mask ~1 is built in $at (li at,-2) because
 * `and` only takes a 16-bit zero-extended immediate. One nop before the return covers the CP0 write
 * hazard. 2.0I form: no __OSGlobalIntMask handling (added in 2.0J). Callers: 32 files, see
 * nw2RestoreInterrupts. */
#ifdef NON_MATCHING
#include "common.h"
#define SR_IE 0x00000001 /* Status bit 0: global interrupt enable */
/* CP0 register 12 is Status. The helpers are macros (not inline functions) so the register
 * variables below stay where the original keeps them ($t0, $t1, $at, $v0). Each CP0 access sits
 * in its own noreorder region so the assembler adds no hazard nops of its own. */
#define GET_STATUS(sr) __asm__ __volatile__(".set noreorder\n\tmfc0 %0, $12\n\t.set reorder" : "=r"(sr))
#define SET_STATUS(sr) __asm__ __volatile__(".set noreorder\n\tmtc0 %0, $12\n\t.set reorder" : : "r"(sr))
/* One explicit CP0 hazard nop, ordered after the computation of `v`. */
#define HAZARD_NOP_AFTER(v) __asm__ __volatile__(".set noreorder\n\tnop\n\t.set reorder" : : "r"(v))

/* Clears SR.IE and returns its previous value (0 or 1) for nw2RestoreInterrupts. */
s32 nw2DisableInterrupts(void) {
    register u32 sr asm("$8");          /* $t0 */
    register u32 notIE asm("$1");       /* $at */
    register u32 off asm("$9");         /* $t1 */
    register s32 wasEnabled asm("$2");  /* $v0 */
    GET_STATUS(sr);
    notIE = ~SR_IE;                     /* -2 */
    off = sr & notIE;
    SET_STATUS(off);
    wasEnabled = sr & SR_IE;
    HAZARD_NOP_AFTER(wasEnabled);
    return wasEnabled;
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl nw2DisableInterrupts\n"
    ".ent nw2DisableInterrupts\n"
    "nw2DisableInterrupts:\n"
    "mfc0 $t0, $12 /* handwritten instruction */\n"
    "addiu $at, $zero, -0x2\n"
    "and $t1, $t0, $at\n"
    "mtc0 $t1, $12 /* handwritten instruction */\n"
    "andi $v0, $t0, 0x1\n"
    "nop\n"
    "jr $ra\n"
    "nop\n"
    ".end nw2DisableInterrupts\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
