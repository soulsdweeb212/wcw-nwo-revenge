/* @header
 * func_80028860
 * VRAM 0x80028860 | ROM 0x29460 | size 0x18
 * asm: asm/nonmatchings/main/func_80028860.s
 */
/* func_80028860: unsigned 64-bit divide, n / d (the libgcc entry __udivdi3; not libultra, it
 * belongs to the hand-written 64-bit math helpers at 0x800284F4-0x800288C0 with __divdi3/__moddi3).
 * Picks the worker by the divisor's high word: d < 2^32 -> func_80028624 (long division by a 32-bit
 * divisor), otherwise func_80028528 (shift-and-subtract, quotient < 2^32). Both are tail jumps (j),
 * so the worker returns straight to our caller. Callers: initializePiAndRdram (osClockRate * 3 /
 * 4), func_800B1B54 (a[i] * 1000 / total), and __divdi3, which branches here (beqz) when the
 * quotient's sign is positive after it has made both operands non-negative. d == 0 reaches
 * func_80028624's `break 7` (divide-by-zero trap). */
#ifdef NON_MATCHING
#include "common.h"
/* The two worker routines; both take the dividend in $a0:$a1 (hi:lo) and the divisor in $a2:$a3
 * and return the 64-bit quotient in $v0:$v1, i.e. the normal o32 u64 return. */
u64 func_80028624(u32 nHi, u32 nLo, u32 dHi, u32 dLo); /* divisor < 2^32: long division by 32 bits */
u64 func_80028528(u32 nHi, u32 nLo, u32 dHi, u32 dLo); /* divisor >= 2^32: 64-bit shift-and-subtract */

/* Unsigned 64-bit divide: n / d. */
u64 func_80028860(u64 n, u64 d) {
    u32 dHi = (u32)(d >> 32);

    if (dHi != 0) {
        return func_80028528((u32)(n >> 32), (u32)n, dHi, (u32)d);   /* tail jump (j) */
    }
    return func_80028624((u32)(n >> 32), (u32)n, dHi, (u32)d);       /* tail jump (j) */
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    ".globl func_80028860\n"
    ".ent func_80028860\n"
    "func_80028860:\n"
    "bnez $a2, .L80028870\n"
    "nop\n"
    "j func_80028624\n"
    "nop\n"
    ".L80028870:\n"
    "j func_80028528\n"
    "nop\n"
    "nop\n"
    "nop\n"
    ".end func_80028860\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
