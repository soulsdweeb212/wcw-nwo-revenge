/* @header
 * func_80026B00
 * VRAM 0x80026B00 | ROM 0x27700 | size 0xC
 * asm: asm/nonmatchings/main/func_80026B00.s
 */
/* func_80026B00: libultra __osGetSR(). Returns CP0 Status ($12). Only caller: initializePiAndRdram
 * (__osInitialize), which ORs in SR_CU1 (0x20000000, FPU usable) and writes it back with
 * func_80026C20 (__osSetSR). Asm because mfc0 has no C form. */
#ifdef NON_MATCHING
#include "common.h"
/* CP0 register 12 is Status (IE, EXL, ERL, KSU, IM[7:0], BEV, CU0-CU3 ...). */
static inline u32 getStatus(void) {
    u32 sr;
    __asm__ __volatile__("mfc0 %0, $12" : "=r"(sr));
    return sr;
}

u32 func_80026B00(void) {
    return getStatus();
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl func_80026B00\n"
    ".ent func_80026B00\n"
    "func_80026B00:\n"
    "mfc0 $v0, $12 /* handwritten instruction */\n"
    "jr $ra\n"
    "nop\n"
    "nop\n"
    ".end func_80026B00\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
