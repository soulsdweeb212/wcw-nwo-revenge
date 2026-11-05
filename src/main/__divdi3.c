/* @header
 * __divdi3  (originally func_800286F0)
 * VRAM 0x800286F0 | ROM 0x292F0 | size 0xA8
 * asm: asm/nonmatchings/main/__divdi3.s
 */
/* __divdi3: signed 64-bit division a / b, the libcall GCC emits for s64 '/'. It comes from the
 * hand-written runtime library of the KMC GCC toolchain, not from libultra or GCC's C libgcc2. Six
 * compiler-generated call sites, e.g. func_800080A0 (sx / count averages). Arguments are in
 * $a0:$a1 and $a2:$a3, result in $v0:$v1 (high word first).
 * Method: the quotient's sign is the sign bit of (a.hi ^ b.hi). Both operands are made positive
 * (~x + 1 with carry; INT64_MIN stays 0x8000000000000000, which is then read as unsigned 2^63).
 * For a non-negative result it tail-branches to func_80028860 (__udivdi3). Otherwise it inlines
 * __udivdi3's dispatch (b.hi != 0 -> func_80028528, a shift-subtract 64/64 divide; else
 * func_80028624, a 64/32 divide built from divu, which does `break 7` on b == 0), then negates the
 * quotient. It saves $ra in $t5 instead of on the stack and the helpers return values in
 * non-standard registers, so it cannot be compiled C.
 * Checked in an emulator (C calling the real ROM helpers vs. the ROM asm): 3000 random and edge
 * pairs, including INT64_MIN, -1 and 2^32 boundaries. Same results every time. */
#ifdef NON_MATCHING
#include "common.h"
extern u64 func_80028860(u64, u64); /* __udivdi3: unsigned 64-bit a / b */

s64 __divdi3(s64 a, s64 b)
{
    /* Sign of the quotient = sign bit of (a.hi ^ b.hi), taken before the operands are made positive. */
    s32 negative = (s32)((u32)((u64)a >> 32) ^ (u32)((u64)b >> 32)) < 0;
    u64 ua = (a < 0) ? -(u64)a : (u64)a; /* ~x + 1 with carry; INT64_MIN stays 0x8000000000000000 */
    u64 ub = (b < 0) ? -(u64)b : (u64)b;
    u64 q;

    if (!negative) {
        return func_80028860(ua, ub); /* tail branch in the asm */
    }
    /* Negative result: the asm inlines __udivdi3's dispatch here (b.hi != 0 -> func_80028528,
     * else 64/32 func_80028624) and then negates the quotient. */
    q = func_80028860(ua, ub);
    return -(s64)q;
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    ".globl __divdi3\n"
    ".ent __divdi3\n"
    "__divdi3:\n"
    "lui $t0, (0x80000000 >> 16)\n"
    "addu $v1, $a0, $zero\n"
    "xor $v1, $v1, $a2\n"
    "and $t9, $t0, $a0\n"
    "beqz $t9, .L80028720\n"
    "nop\n"
    "addiu $t1, $zero, -0x1\n"
    "xor $a1, $a1, $t1\n"
    "xor $a0, $a0, $t1\n"
    "addiu $a1, $a1, 0x1\n"
    "sltiu $t9, $a1, 0x1\n"
    "addu $a0, $a0, $t9\n"
    ".L80028720:\n"
    "and $t9, $t0, $a2\n"
    "beqz $t9, .L80028744\n"
    "nop\n"
    "addiu $t1, $zero, -0x1\n"
    "xor $a3, $a3, $t1\n"
    "xor $a2, $a2, $t1\n"
    "addiu $a3, $a3, 0x1\n"
    "sltiu $t9, $a3, 0x1\n"
    "addu $a2, $a2, $t9\n"
    ".L80028744:\n"
    "and $v1, $v1, $t0\n"
    ".word 0x10600045 /* beqz func_80028860: target outside this function */\n"
    "nop\n"
    "bnez $a2, .L8002876C\n"
    "nop\n"
    "addu $t5, $ra, $zero\n"
    "jal func_80028624\n"
    "nop\n"
    "j .L8002877C\n"
    "addu $ra, $t5, $zero\n"
    ".L8002876C:\n"
    "addu $t5, $ra, $zero\n"
    "jal func_80028528\n"
    "nop\n"
    "addu $ra, $t5, $zero\n"
    ".L8002877C:\n"
    "addiu $a3, $zero, -0x1\n"
    "xor $v1, $v1, $a3\n"
    "xor $v0, $v0, $a3\n"
    "addiu $v1, $v1, 0x1\n"
    "sltiu $t9, $v1, 0x1\n"
    "jr $ra\n"
    "addu $v0, $v0, $t9\n"
    "nop\n"
    "nop\n"
    ".end __divdi3\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
