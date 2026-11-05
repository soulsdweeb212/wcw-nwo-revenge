/* @header
 * __floatdisf  (originally func_800289B0)
 * VRAM 0x800289B0 | ROM 0x295B0 | size 0xF4
 * asm: asm/nonmatchings/main/__floatdisf.s
 */
/* __floatdisf: s64 -> f32 conversion, the libcall GCC emits for (f32)s64. It is very
 * likely the KMC runtime's __floatdisf: it sits right after __fixsfdi with the same hand-written
 * style. Called from calculateObjectVertexCentroid and func_800080A0 (12 call sites in all) to
 * turn 64-bit coordinate sums/averages into floats. The argument is in $a0:$a1; the result is built
 * as an integer, stored to the stack and reloaded into $f0.
 * Method: 0 -> +0.0f. Negative values are negated and the sign bit set. The magnitude is shifted
 * until its leading 1 sits at bit 55 (bit 23 of the high word), with the biased exponent starting
 * at 0xB6 = 127 + 55. Mantissa = the next 23 bits. Lower bits are dropped, so it TRUNCATES toward
 * zero instead of rounding to nearest like IEEE / GCC's libgcc. Results can therefore be 1 ulp
 * smaller in magnitude than a normal (f32) cast. INT64_MIN converts correctly to -2^63.
 * Checked in an emulator against the ROM asm: 6000 random and edge values, same f32 bits. */
#ifdef NON_MATCHING
#include "common.h"
f32 __floatdisf(s64 v)
{
    union { f32 f; u32 u; } out;
    u32 hi = (u32)((u64)v >> 32);
    u32 lo = (u32)v;
    u32 sign = 0;
    s32 exp;

    if ((hi | lo) == 0) {
        out.u = lo; /* +0.0f */
        return out.f;
    }
    if (hi & 0x80000000) {
        /* Work on the magnitude (two's complement negate with carry). */
        lo = ~lo + 1;
        hi = ~hi + (lo == 0);
        sign = 0x80000000;
    }
    /* Normalise so the leading 1 sits at bit 55 (bit 23 of hi); that position is
     * worth 2^55, so the biased exponent starts at 127 + 55 = 0xB6. */
    exp = 0xB6;
    if (hi & 0xFF000000) {
        do {
            lo = (lo >> 1) | (hi << 31);
            hi >>= 1;
            exp++;
        } while (hi & 0xFF000000);
    } else {
        while (!(hi & 0x800000)) {
            hi = (hi << 1) | (lo >> 31);
            lo <<= 1;
            exp--;
        }
    }
    /* Mantissa = bits 54..32; everything in lo is dropped (truncation, no rounding). */
    out.u = (hi & 0x7FFFFF) | ((u32)exp << 23) | sign;
    return out.f;
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    ".globl __floatdisf\n"
    ".ent __floatdisf\n"
    "__floatdisf:\n"
    "addu $v0, $a1, $zero\n"
    "addu $v1, $a0, $zero\n"
    "or $a0, $a0, $a1\n"
    "bnez $a0, .L800289DC\n"
    "nop\n"
    "addiu $sp, $sp, -0x8\n"
    "sw $v0, 0x0($sp)\n"
    "nop\n"
    "lwc1 $fv0, 0x0($sp)\n"
    "jr $ra\n"
    "addiu $sp, $sp, 0x8\n"
    ".L800289DC:\n"
    "xor $a2, $a2, $a2\n"
    "lui $a0, (0x80000000 >> 16)\n"
    "and $t9, $a0, $v1\n"
    "beqz $t9, .L80028A0C\n"
    "nop\n"
    "addiu $a3, $zero, -0x1\n"
    "xor $v0, $v0, $a3\n"
    "xor $v1, $v1, $a3\n"
    "addiu $v0, $v0, 0x1\n"
    "sltiu $t9, $v0, 0x1\n"
    "addu $v1, $v1, $t9\n"
    "addu $a2, $a0, $zero\n"
    ".L80028A0C:\n"
    "addiu $a0, $zero, 0xB6\n"
    "lui $t9, (0xFF000000 >> 16)\n"
    "and $t9, $t9, $v1\n"
    "beqz $t9, .L80028A4C\n"
    "nop\n"
    ".L80028A20:\n"
    "sll $t9, $v1, 31\n"
    "srl $v0, $v0, 1\n"
    "or $v0, $v0, $t9\n"
    "srl $v1, $v1, 1\n"
    "addiu $a0, $a0, 0x1\n"
    "lui $t9, (0xFF000000 >> 16)\n"
    "and $t9, $t9, $v1\n"
    "bnez $t9, .L80028A20\n"
    "nop\n"
    "j .L80028A74\n"
    "nop\n"
    ".L80028A4C:\n"
    "lui $t9, (0x800000 >> 16)\n"
    "and $t9, $t9, $v1\n"
    "bnez $t9, .L80028A74\n"
    "nop\n"
    "srl $t9, $v0, 31\n"
    "sll $v1, $v1, 1\n"
    "or $v1, $v1, $t9\n"
    "sll $v0, $v0, 1\n"
    "j .L80028A4C\n"
    "addiu $a0, $a0, -0x1\n"
    ".L80028A74:\n"
    "lui $v0, (0x7FFFFF >> 16)\n"
    "ori $v0, $v0, (0x7FFFFF & 0xFFFF)\n"
    "and $v0, $v0, $v1\n"
    "sll $a0, $a0, 23\n"
    "or $v0, $v0, $a0\n"
    "or $v0, $v0, $a2\n"
    "addiu $sp, $sp, -0x8\n"
    "sw $v0, 0x0($sp)\n"
    "nop\n"
    "lwc1 $fv0, 0x0($sp)\n"
    "jr $ra\n"
    "addiu $sp, $sp, 0x8\n"
    "nop\n"
    "nop\n"
    "nop\n"
    ".end __floatdisf\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
