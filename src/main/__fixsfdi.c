/* @header
 * __fixsfdi  (originally func_800288C0)
 * VRAM 0x800288C0 | ROM 0x294C0 | size 0xEC
 * asm: asm/nonmatchings/main/__fixsfdi.s
 */
/* __fixsfdi: f32 -> s64 conversion that truncates toward zero, the libcall GCC emits for (s64)f.
 * KMC GCC hand-written runtime. Linked in but no jal in the ROM reaches it. The float arrives in
 * $f12; it is spilled to the stack and reloaded as an integer. The result is $v0:$v1.
 * Behaviour: exponent < 127 (|x| < 1, zero, denormals) -> 0. Unbiased exponent >= 64 (too big,
 * +-Inf, NaN) -> 0x8000000000000000 for either sign. Otherwise the 24-bit significand (implicit 1
 * included) is shifted into place, and the result is negated if the sign bit is set.
 * BUG in this ROM: for unbiased exponent 55..63 (|x| >= 2^55) it clears the low word and sets the
 * high word to (incoming $v0) >> (shift - 32), using whatever the caller left in $v0, where it
 * should use significand << (shift - 32). Those inputs give garbage. The C reproduces this by
 * reading $v0 with one inline-asm move at entry. That is best effort: compiled C does not promise
 * $v0 is untouched by then.
 * Checked in an emulator against the ROM asm: all 256 exponents with both signs, plus 5500 random
 * bit patterns. Same results every time, including the garbage path given the same stale $v0. */
#ifdef NON_MATCHING
#include "common.h"
/* Whatever the caller left in $v0 on entry. The asm reads it by mistake on one path (see below). */
static inline u32 incomingV0(void)
{
    u32 r;
    __asm__ __volatile__("move %0, $2" : "=r"(r));
    return r;
}

s64 __fixsfdi(f32 x)
{
    u32 staleV0 = incomingV0();
    union { f32 f; u32 u; } bits;
    u32 exp, mant, hi, lo, shift;

    bits.f = x; /* the asm spills $f12 to the stack and reloads it as an integer */
    exp = (bits.u >> 23) & 0xFF;
    if (exp < 127) {
        return 0; /* |x| < 1, zero and denormals truncate to 0 */
    }
    exp -= 127; /* unbiased exponent: x = 1.mant * 2^exp */
    if (exp >= 64) {
        /* Too big, +-Inf or NaN: 0x8000000000000000 regardless of sign. */
        return (s64)((u64)0x80000000 << 32);
    }
    mant = (bits.u & 0x7FFFFF) | 0x800000; /* 24-bit significand with the implicit 1 */
    if (exp < 23) {
        hi = 0;
        lo = mant >> (23 - exp); /* drop fraction bits: truncation toward zero */
    } else if (exp == 23) {
        hi = 0;
        lo = mant;
    } else {
        shift = exp - 23; /* 1..40 */
        if (shift < 32) {
            hi = mant >> (32 - shift);
            lo = mant << shift;
        } else {
            /* BUG in the original: should be hi = mant << (shift - 32). It clears lo and shifts
             * the stale $v0 instead, so |x| >= 2^55 converts to garbage. srlv uses shift & 31. */
            lo = 0;
            hi = staleV0 >> ((shift - 32) & 31);
        }
    }
    if (bits.u & 0x80000000) {
        /* Negate hi:lo (two's complement with carry). */
        hi = ~hi;
        lo = ~lo + 1;
        hi += (lo == 0);
    }
    return (s64)(((u64)hi << 32) | lo);
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    ".globl __fixsfdi\n"
    ".ent __fixsfdi\n"
    "__fixsfdi:\n"
    "addiu $sp, $sp, -0x8\n"
    "swc1 $fa0, 0x0($sp)\n"
    "nop\n"
    "lw $a0, 0x0($sp)\n"
    "addiu $sp, $sp, 0x8\n"
    "addu $v1, $a0, $zero\n"
    "srl $a0, $a0, 23\n"
    "andi $a0, $a0, 0xFF\n"
    "sltiu $t9, $a0, 0x7F\n"
    "bnez $t9, .L800289A0\n"
    "addiu $a0, $a0, -0x7F\n"
    "sltiu $t9, $a0, 0x40\n"
    "beqz $t9, .L80028994\n"
    "nop\n"
    "addu $a2, $v1, $zero\n"
    "lui $t9, (0x7FFFFF >> 16)\n"
    "ori $t9, $t9, (0x7FFFFF & 0xFFFF)\n"
    "and $v1, $v1, $t9\n"
    "lui $t9, (0x800000 >> 16)\n"
    "or $v1, $v1, $t9\n"
    "sltiu $t9, $a0, 0x17\n"
    "bnez $t9, .L80028958\n"
    "addiu $a0, $a0, -0x17\n"
    "beqz $a0, .L80028960\n"
    "nop\n"
    "addu $a3, $a0, $zero\n"
    "sltiu $t9, $a0, 0x20\n"
    "bnez $t9, .L80028940\n"
    "addiu $a0, $a0, -0x20\n"
    "xor $v1, $v1, $v1\n"
    "j .L80028964\n"
    "srlv $v0, $v0, $a0\n"
    ".L80028940:\n"
    "negu $a0, $a0\n"
    "addu $v0, $v1, $zero\n"
    "srlv $v0, $v0, $a0\n"
    "addu $a0, $a3, $zero\n"
    "j .L80028964\n"
    "sllv $v1, $v1, $a0\n"
    ".L80028958:\n"
    "negu $a0, $a0\n"
    "srlv $v1, $v1, $a0\n"
    ".L80028960:\n"
    "xor $v0, $v0, $v0\n"
    ".L80028964:\n"
    "lui $t9, (0x80000000 >> 16)\n"
    "and $t9, $t9, $a2\n"
    "beqz $t9, .L8002898C\n"
    "nop\n"
    "addiu $a2, $zero, -0x1\n"
    "xor $v1, $v1, $a2\n"
    "xor $v0, $v0, $a2\n"
    "addiu $v1, $v1, 0x1\n"
    "sltiu $t9, $v1, 0x1\n"
    "addu $v0, $v0, $t9\n"
    ".L8002898C:\n"
    "jr $ra\n"
    "nop\n"
    ".L80028994:\n"
    "addiu $v1, $zero, 0x0\n"
    "jr $ra\n"
    "lui $v0, (0x80000000 >> 16)\n"
    ".L800289A0:\n"
    "xor $v0, $v0, $v0\n"
    "jr $ra\n"
    "xor $v1, $v1, $v1\n"
    "nop\n"
    ".end __fixsfdi\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
