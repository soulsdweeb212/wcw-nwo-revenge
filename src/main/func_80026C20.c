/* @header
 * func_80026C20
 * VRAM 0x80026C20 | ROM 0x27820 | size 0x10
 * asm: asm/nonmatchings/main/func_80026C20.s
 */
/* func_80026C20: libultra __osSetSR(u32). Writes CP0 Status ($12), followed by one nop for the CP0
 * write hazard. Only caller: initializePiAndRdram (__osInitialize), enabling coprocessor 1
 * (SR_CU1). Asm because mtc0 has no C form. */
#ifdef NON_MATCHING
#include "common.h"
/* CP0 register 12 is Status. The nop is the CP0 hazard slot after mtc0; it is written inside the
 * same noreorder region so the assembler neither drops it nor moves it into the jr delay slot. */
static inline void setStatus(u32 sr) {
    __asm__ __volatile__(".set noreorder\n\tmtc0 %0, $12\n\tnop\n\t.set reorder" : : "r"(sr));
}

void func_80026C20(u32 sr) {
    setStatus(sr);
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl func_80026C20\n"
    ".ent func_80026C20\n"
    "func_80026C20:\n"
    "mtc0 $a0, $12 /* handwritten instruction */\n"
    "nop\n"
    "jr $ra\n"
    "nop\n"
    ".end func_80026C20\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
