/* @header
 * func_80028528
 * VRAM 0x80028528 | ROM 0x29128 | size 0xFC
 * asm: asm/nonmatchings/main/func_80028528.s
 */
/* func_80028528: internal helper of this ROM's hand-written 64-bit division runtime (same family as func_80028624; not
 * libultra, name unknown): the "divisor needs 64 bits" path, used by __udivdi3/__umoddi3/__divdi3/__moddi3 when the
 * divisor high word $a2 is non-zero. In: dividend $a0:$a1, divisor $a2:$a3. Out: quotient in $v0:$v1 ($v0 always 0: a
 * divisor >= 2^32 leaves a quotient < 2^32) and, outside the C ABI, the remainder in $a0:$a1 (func_80028880/__umoddi3
 * and __moddi3 read it). Method: d > n gives 0; d == n gives 1, remainder 0; otherwise shift d left (with a quotient
 * bit mask) while the shifted d stays strictly below n or until d's top bit is set, then restoring division back down
 * to bit 0. Edge case kept from the asm (a real bug in the ROM): when d << k == n exactly for some k >= 1 the
 * overshoot undo also fires, so the top quotient bit is lost: the result is 2^k - 1 with remainder d instead of 2^k
 * remainder 0 (e.g. 2^33 / 2^32 = 1 rem 2^32; 0x30000000000 / 0x300000000 = 0xFF). Confirmed with a MIPS interpreter
 * on the ROM bytes; all other inputs tested (20000) give exact quotient and remainder. Only affects 64-bit divides
 * whose divisor is >= 2^32 and that divide exactly (remainder 0) with a quotient that is a power of two >= 2; with a
 * non-zero remainder a power-of-two quotient comes out right (e.g. (2^33 + 1) / 2^32 = 2 rem 1). The 32-bit bit mask
 * also means it is wrong if called directly with $a2 == 0 and a quotient >= 2^32 (no caller does). Callers (all asm):
 * func_80028860 (tail call), func_80028880, __divdi3, __moddi3. In the C the out-of-ABI remainder is handed back
 * through the setRemainderA0A1 inline-asm helper as the last step. */
#ifdef NON_MATCHING
#include "common.h"

/* Hands the 64-bit remainder back in $a0:$a1 (hi:lo), outside the C ABI, as the asm does: __umoddi3 (func_80028880)
 * and __moddi3 read $a0/$a1 straight after the call. One asm statement so neither input can be given $a0/$a1 and
 * be overwritten by the other move; it must be the last thing before the return. */
static inline void setRemainderA0A1(u32 hi, u32 lo) {
    __asm__ __volatile__("move $4, %0\n\tmove $5, %1" : : "r"(hi), "r"(lo) : "$4", "$5");
}

/* Unsigned 64-bit / 64-bit divide by shift-and-subtract (restoring division), for divisors >= 2^32: the quotient
 * then fits in 32 bits, so it is returned zero-extended. */
u64 func_80028528(u32 nHi, u32 nLo, u32 dHi, u32 dLo) {
    u64 n = ((u64)nHi << 32) | nLo;     /* $a0:$a1, becomes the remainder */
    u64 d = ((u64)dHi << 32) | dLo;     /* $a2:$a3 */
    u32 q = 0;                          /* $v1 */
    u32 bit;                            /* $v0, the quotient bit d currently stands for */

    if (d > n) {
        /* quotient 0, remainder n (the asm returns with $a0:$a1 untouched) */
    } else if (d == n) {
        n = 0;                          /* quotient 1, remainder 0 */
        q = 1;
    } else {
        /* Normalise: shift d left while it stays strictly below n (or until its top bit is set). A shift that
         * reaches or passes n is undone. NOTE: undoing it also when d << k == n exactly loses one quotient bit:
         * e.g. n = 2^33, d = 2^32 gives quotient 1, remainder 2^32 (see the caveat in the header comment). */
        bit = 1;
        while ((d >> 63) == 0) {
            d <<= 1;
            if (d < n) {
                bit <<= 1;
                continue;
            }
            d >>= 1;
            break;
        }

        /* Restoring division from that bit down to bit 0. */
        do {
            if (d <= n) {
                n -= d;
                q |= bit;
            }
            d >>= 1;
            bit >>= 1;
        } while (bit != 0);
    }

    setRemainderA0A1((u32)(n >> 32), (u32)n);  /* remainder out in $a0:$a1 */
    return q;                           /* quotient out in $v0:$v1: $v0 = 0, $v1 = q */
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    ".globl func_80028528\n"
    ".ent func_80028528\n"
    "func_80028528:\n"
    "xor $v1, $v1, $v1\n"
    "sltu $t9, $a2, $a0\n"
    "bnez $t9, .L80028570\n"
    "nop\n"
    "bne $a0, $a2, .L80028568\n"
    "nop\n"
    "sltu $t9, $a3, $a1\n"
    "bnez $t9, .L80028570\n"
    "nop\n"
    "bne $a1, $a3, .L80028568\n"
    "nop\n"
    "xor $a1, $a1, $a1\n"
    "xor $a0, $a0, $a0\n"
    "addiu $v1, $zero, 0x1\n"
    "jr $ra\n"
    "xor $v0, $v0, $v0\n"
    ".L80028568:\n"
    "jr $ra\n"
    "xor $v0, $v0, $v0\n"
    ".L80028570:\n"
    "addiu $v0, $zero, 0x1\n"
    "lui $t0, (0x80000000 >> 16)\n"
    ".L80028578:\n"
    "and $t9, $a2, $t0\n"
    "bnez $t9, .L800285CC\n"
    "nop\n"
    "srl $t9, $a3, 31\n"
    "sll $a2, $a2, 1\n"
    "or $a2, $a2, $t9\n"
    "sll $a3, $a3, 1\n"
    "sltu $t9, $a2, $a0\n"
    "bnez $t9, .L800285B4\n"
    "nop\n"
    "bne $a0, $a2, .L800285BC\n"
    "nop\n"
    "sltu $t9, $a3, $a1\n"
    "beqz $t9, .L800285BC\n"
    "nop\n"
    ".L800285B4:\n"
    "j .L80028578\n"
    "sll $v0, $v0, 1\n"
    ".L800285BC:\n"
    "sll $t9, $a2, 31\n"
    "srl $a3, $a3, 1\n"
    "or $a3, $a3, $t9\n"
    "srl $a2, $a2, 1\n"
    ".L800285CC:\n"
    "sltu $t9, $a2, $a0\n"
    "bnez $t9, .L800285EC\n"
    "nop\n"
    "bne $a0, $a2, .L80028600\n"
    "nop\n"
    "sltu $t9, $a1, $a3\n"
    "bnez $t9, .L80028600\n"
    "nop\n"
    ".L800285EC:\n"
    "sltu $t9, $a1, $a3\n"
    "subu $a1, $a1, $a3\n"
    "subu $a0, $a0, $a2\n"
    "subu $a0, $a0, $t9\n"
    "or $v1, $v1, $v0\n"
    ".L80028600:\n"
    "sll $t9, $a2, 31\n"
    "srl $a3, $a3, 1\n"
    "or $a3, $a3, $t9\n"
    "srl $a2, $a2, 1\n"
    "srl $v0, $v0, 1\n"
    "bnez $v0, .L800285CC\n"
    "nop\n"
    "jr $ra\n"
    "xor $v0, $v0, $v0\n"
    ".end func_80028528\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
