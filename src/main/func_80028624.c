/* @header
 * func_80028624
 * VRAM 0x80028624 | ROM 0x29224 | size 0xC8
 * asm: asm/nonmatchings/main/func_80028624.s
 */
/* func_80028624: internal helper of this ROM's hand-written 64-bit division runtime (not libultra: libultra's
 * __ull_div etc. are IDO-compiled C using 64-bit registers; this one uses only 32-bit divu/multu, KMC GCC -mgp32
 * libgcc style). Name unknown; it is the "divisor fits in 32 bits" path. In: dividend $a0:$a1 (hi:lo), divisor low
 * word $a3 ($a2, the divisor high word, is never read; every caller comes here only when it is 0). Out: 64-bit
 * quotient in $v0:$v1, and, outside the C ABI, the 32-bit remainder in $t1. Method: q_hi = n_hi / d, r = n_hi % d;
 * while the running dividend r:n_lo is still wider than 32 bits, shift it and d right together until it fits, divide
 * by (d >> k) + 1 (an under-estimate), add that to the quotient (64-bit add with carry) and subtract estimate * d
 * (multu, 64-bit subtract with borrow); finally q += n_lo / d and the remainder is n_lo % d. d == 0 traps (break 7,
 * the standard divide-by-zero check). Callers (all asm): __udivdi3, __umoddi3 (reads
 * $t1), __divdi3 and __moddi3 (reads $t1). The prototypes in func_80028C44/__osSiRawStartDma/__osTimerServicesInit are unused
 * declarations. Verified with a MIPS interpreter on ~4000 inputs: quotient and $t1 remainder always exact. In the C
 * the out-of-ABI remainder is handed back through the setT1 inline-asm helper as the last step, so it can stand in for
 * the asm with these callers. */
#ifdef NON_MATCHING
#include "common.h"

/* Hands the 32-bit remainder back in $t1 ($9), outside the C ABI, as the asm does: __umoddi3 and
 * __moddi3 read $t1 straight after the call. Must be the last thing before the return so nothing reuses $t1. */
static inline void setT1(u32 rem) {
    __asm__ __volatile__("move $9, %0" : : "r"(rem) : "$9");
}

/* Unsigned 64-bit / 32-bit divide using only 32-bit divu/multu. The divisor is the low word of the second u64
 * argument ($a3); its high word ($a2) is never read (the callers only come here when it is 0). */
u64 func_80028624(u32 nHi, u32 nLo, u32 dHi, u32 d) {
    u32 qHi = nHi / d;                  /* divide by zero traps (break 7) */
    u32 rHi = nHi % d;                  /* the dividend is now rHi:nLo, with rHi < d */
    u32 qLo = 0;
    u32 q;
    u32 rem;
    u64 result;

    /* While the running dividend still needs 64 bits: estimate a partial quotient from its top 32 significant
     * bits, divided by a slightly too large divisor so the estimate never overshoots; add it to the quotient and
     * subtract est * d from the dividend. */
    while (rHi != 0) {
        u32 hi = rHi;
        u32 lo = nLo;
        u32 dd = d;
        u32 est;
        u32 borrow;
        u64 prod;

        do {                            /* shift dividend and divisor right together until the dividend fits */
            lo = (lo >> 1) | (hi << 31);
            hi >>= 1;
            dd >>= 1;
        } while (hi != 0);
        est = lo / (dd + 1);            /* dd + 1 is never 0: d was shifted at least once */

        qLo += est;                     /* 64-bit add into qHi:qLo */
        qHi += (qLo < est);

        prod = (u64)est * d;            /* multu */
        borrow = nLo < (u32)prod;       /* 64-bit subtract from rHi:nLo */
        nLo -= (u32)prod;
        rHi = rHi - (u32)(prod >> 32) - borrow;
    }

    /* The rest fits in 32 bits: one more divu gives the last quotient part (mflo) and the remainder (mfhi). */
    q = nLo / d;
    rem = nLo % d;
    q += qLo;
    qHi += (q < qLo);
    result = ((u64)qHi << 32) | q;
    setT1(rem);                         /* remainder out in $t1 */
    return result;                      /* quotient out in $v0:$v1 */
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    ".globl func_80028624\n"
    ".ent func_80028624\n"
    "func_80028624:\n"
    "divu $zero, $a0, $a3\n"
    "bnez $a3, .L80028634\n"
    "nop\n"
    "break 7\n"
    ".L80028634:\n"
    "mflo $t2\n"
    "mfhi $a0\n"
    "xor $t0, $t0, $t0\n"
    ".L80028640:\n"
    "beqz $a0, .L800286BC\n"
    "nop\n"
    "addu $v1, $a1, $zero\n"
    "addu $v0, $a0, $zero\n"
    "addu $t1, $a3, $zero\n"
    ".L80028654:\n"
    "sll $t9, $v0, 31\n"
    "srl $v1, $v1, 1\n"
    "or $v1, $v1, $t9\n"
    "srl $v0, $v0, 1\n"
    "bnez $v0, .L80028654\n"
    "srl $t1, $t1, 1\n"
    "addiu $t1, $t1, 0x1\n"
    "divu $zero, $v1, $t1\n"
    "bnez $t1, .L80028680\n"
    "nop\n"
    "break 7\n"
    ".L80028680:\n"
    "mflo $v1\n"
    "xor $v0, $v0, $v0\n"
    "addu $t0, $t0, $v1\n"
    "sltu $t9, $t0, $v1\n"
    "addu $t2, $t2, $v0\n"
    "addu $t2, $t2, $t9\n"
    "nop\n"
    "multu $v1, $a3\n"
    "mflo $v1\n"
    "mfhi $v0\n"
    "sltu $t9, $a1, $v1\n"
    "subu $a1, $a1, $v1\n"
    "subu $a0, $a0, $v0\n"
    "j .L80028640\n"
    "subu $a0, $a0, $t9\n"
    ".L800286BC:\n"
    "divu $zero, $a1, $a3\n"
    "bnez $a3, .L800286CC\n"
    "nop\n"
    "break 7\n"
    ".L800286CC:\n"
    "mflo $v1\n"
    "mfhi $t1\n"
    "xor $v0, $v0, $v0\n"
    "addu $v1, $v1, $t0\n"
    "sltu $t9, $v1, $t0\n"
    "addu $v0, $v0, $t2\n"
    "jr $ra\n"
    "addu $v0, $v0, $t9\n"
    "nop\n"
    ".end func_80028624\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
