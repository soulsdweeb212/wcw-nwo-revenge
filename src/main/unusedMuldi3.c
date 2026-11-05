/* @header
 * unusedMuldi3  (originally func_800284F4)
 * VRAM 0x800284F4 | ROM 0x290F4 | size 0x34
 * asm: asm/nonmatchings/main/unusedMuldi3.s
 */
/* unusedMuldi3: a 64x64->64 multiply in the shape of libgcc's __muldi3 (same hand-written 64-bit
 * math library as __divdi3/__moddi3/__udivdi3/__umoddi3; not libultra). It computes v0:v1 =
 * a0*a2 + ((a1*a2 + a0*a3) << 32) (mod 2^64). That is the product of x = a1:a0 and y = a3:a2, i.e.
 * it treats $a0/$a2 as the LOW words, while the o32 big-endian convention used everywhere else (and
 * by __divdi3 here, which tests the sign in $a0) passes the high word in $a0/$a2. So under the real
 * calling convention it gives a wrong product (it uses hi*hi as the 64-bit partial product).
 * It fits neither convention: the arguments are read little-endian ($a0/$a2 low) but the result is
 * returned big-endian (high word in $v0, low in $v1), so it is not a little-endian leftover
 * either; the reason is unknown. Nothing calls it: no jal/j/pointer in any code
 * or data (gcc here multiplies 64-bit values inline), so it is dead code. The nops keep two
 * instructions between each mflo and the next multu (the R4000 HI/LO hazard).
 * Not named __muldi3: KMC's assembler applies its VR4300 multiply fix (a nop before each multu) to
 * functions with some names (__muldi3, __udivdi3, mul64 ...) and not others, and that changes the
 * bytes. unusedMuldi3 assembles to the original. */
#ifdef NON_MATCHING
#include "common.h"
/* Low 32 bits of a 32x32 product (the asm uses multu + mflo; signedness does not change them). */
static inline u32 mulLo(u32 a, u32 b) {
    return (u32)((u64)a * b);
}

/* Returns, in $v0:$v1 (hi:lo), the low 64 bits of
 *     x * y   where x = a1:a0 and y = a3:a2 (each word pair written hi:lo),
 * i.e. a0*a2 + ((a1*a2 + a0*a3) << 32). Under the normal o32 big-endian convention
 * (a0:a1 = first u64 hi:lo, a2:a3 = second) this is NOT the product: the full 64-bit
 * partial product is taken of the two HIGH words. Nothing in the ROM calls it. */
u64 unusedMuldi3(u32 a0, u32 a1, u32 a2, u32 a3) {
    u32 cross = mulLo(a1, a2);        /* multu a1, a2 ; mflo t0 */
    u64 full;

    cross += mulLo(a0, a3);           /* multu a0, a3 ; mflo v1 ; addu t0, t0, v1 */
    full = (u64)a0 * a2;              /* multu a0, a2 ; mflo v1 (lo) ; mfhi v0 (hi) */
    return full + ((u64)cross << 32); /* addu v0, v0, t0 (high word only, no carry) */
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    ".globl unusedMuldi3\n"
    ".ent unusedMuldi3\n"
    "unusedMuldi3:\n"
    "multu $a1, $a2\n"
    "mflo $t0\n"
    "nop\n"
    "nop\n"
    "multu $a0, $a3\n"
    "mflo $v1\n"
    "addu $t0, $t0, $v1\n"
    "nop\n"
    "multu $a0, $a2\n"
    "mflo $v1\n"
    "mfhi $v0\n"
    "jr $ra\n"
    "addu $v0, $v0, $t0\n"
    ".end unusedMuldi3\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
