/* @header
 * func_80026C10
 * VRAM 0x80026C10 | ROM 0x27810 | size 0x10
 * asm: asm/nonmatchings/main/func_80026C10.s
 */
/* func_80026C10: libultra __osSetFpcCsr(u32). Swaps the FPU control/status register FCSR (cp1
 * control register $31): returns the old value, writes the new one. Only caller:
 * initializePiAndRdram (__osInitialize) with 0x01000800 = FPCSR_FS (flush denormals to zero) |
 * FPCSR_EV (trap on invalid operation), round-to-nearest. Asm because cfc1/ctc1 have no C form. */
#ifdef NON_MATCHING
#include "common.h"
/* FPU control register 31 is FCSR (rounding mode, cause/enable/flag bits, FS flush-to-zero). */
static inline u32 getFpcCsr(void) {
    u32 csr;
    __asm__ __volatile__("cfc1 %0, $31" : "=r"(csr));
    return csr;
}
static inline void setFpcCsr(u32 csr) {
    __asm__ __volatile__("ctc1 %0, $31" : : "r"(csr));
}

/* Returns the previous FCSR. */
u32 func_80026C10(u32 csr) {
    u32 old = getFpcCsr();
    setFpcCsr(csr);
    return old;
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    ".globl func_80026C10\n"
    ".ent func_80026C10\n"
    "func_80026C10:\n"
    "cfc1 $v0, $31\n"
    "ctc1 $a0, $31\n"
    "jr $ra\n"
    "nop\n"
    ".end func_80026C10\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
