/* @header
 * func_80028880
 * VRAM 0x80028880 | ROM 0x29480 | size 0x40
 * asm: asm/nonmatchings/main/func_80028880.s
 */
/* func_80028880: unsigned 64-bit remainder, n % d (the libgcc entry __umoddi3; same hand-written
 * 64-bit math helpers as func_80028860, not libultra). Uses the same two division workers as
 * func_80028860 but keeps their hidden second result instead of the quotient: func_80028624 (d <
 * 2^32) leaves the 32-bit remainder in $t1, func_80028528 (d >= 2^32) leaves the 64-bit remainder
 * in $a0:$a1. It has no stack frame: $ra is parked in $t5 across the jal. Those non-ABI register
 * results are why it is asm. Only caller: __moddi3, which branches here (beqz) when the dividend is
 * non-negative, after making both operands non-negative. No C code calls it directly. d == 0
 * reaches func_80028624's `break 7`. */
#ifdef NON_MATCHING
#include "common.h"
/* The two divide workers return the quotient in $v0:$v1 but also leave the remainder in
 * registers the C ABI cannot see, which is why this routine is assembly:
 *   func_80028624 (divisor < 2^32): 32-bit remainder in $t1. It does not read $a2 (0 here).
 *   func_80028528 (divisor >= 2^32): 64-bit remainder in $a0:$a1 (hi:lo).
 * The helpers below make that contract explicit: each is the original's `jal` with the
 * argument registers set up, plus a copy of the hidden result register. The original keeps its
 * return address in $t5 across the jal instead of using a stack frame. */
static inline u32 remainderBy32(u32 nHi, u32 nLo, u32 dLo) {
    register u32 a0 asm("$4") = nHi;
    register u32 a1 asm("$5") = nLo;
    register u32 a2 asm("$6") = 0;
    register u32 a3 asm("$7") = dLo;
    register u32 t1 asm("$9");
    __asm__ __volatile__(".set noreorder\n\tjal func_80028624\n\tnop\n\t.set reorder"
                         : "=r"(t1), "=r"(a0), "=r"(a1)
                         : "1"(a0), "2"(a1), "r"(a2), "r"(a3)
                         : "$2", "$3", "$8", "$10", "$25", "$31", "hi", "lo");
    return t1;
}
static inline u64 remainderBy64(u32 nHi, u32 nLo, u32 dHi, u32 dLo) {
    register u32 a0 asm("$4") = nHi;
    register u32 a1 asm("$5") = nLo;
    register u32 a2 asm("$6") = dHi;
    register u32 a3 asm("$7") = dLo;
    __asm__ __volatile__(".set noreorder\n\tjal func_80028528\n\tnop\n\t.set reorder"
                         : "=r"(a0), "=r"(a1), "=r"(a2), "=r"(a3)
                         : "0"(a0), "1"(a1), "2"(a2), "3"(a3)
                         : "$2", "$3", "$8", "$25", "$31");
    return ((u64)a0 << 32) | a1;
}

/* Unsigned 64-bit remainder: n % d. */
u64 func_80028880(u64 n, u64 d) {
    u32 dHi = (u32)(d >> 32);

    if (dHi == 0) {
        return (u64)remainderBy32((u32)(n >> 32), (u32)n, (u32)d);   /* $v0 = 0, $v1 = $t1 */
    }
    return remainderBy64((u32)(n >> 32), (u32)n, dHi, (u32)d);       /* $v0:$v1 = $a0:$a1 */
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    ".globl func_80028880\n"
    ".ent func_80028880\n"
    "func_80028880:\n"
    "bnez $a2, .L800288A4\n"
    "nop\n"
    "addu $t5, $ra, $zero\n"
    "jal func_80028624\n"
    "nop\n"
    "addu $ra, $t5, $zero\n"
    "addu $v1, $t1, $zero\n"
    "jr $ra\n"
    "xor $v0, $v0, $v0\n"
    ".L800288A4:\n"
    "addu $t5, $ra, $zero\n"
    "jal func_80028528\n"
    "nop\n"
    "addu $ra, $t5, $zero\n"
    "addu $v1, $a1, $zero\n"
    "jr $ra\n"
    "addu $v0, $a0, $zero\n"
    ".end func_80028880\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
