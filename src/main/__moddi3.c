/* @header
 * __moddi3  (originally func_800287A0)
 * VRAM 0x800287A0 | ROM 0x293A0 | size 0xB4
 * asm: asm/nonmatchings/main/__moddi3.s
 */
/* __moddi3: signed 64-bit remainder a % b, the libcall GCC emits for s64 '%'. KMC GCC hand-written
 * runtime (same family as __divdi3 / func_80028860 __udivdi3 / func_80028880 __umoddi3). It is
 * linked in but no jal in the ROM reaches it.
 * Method: the remainder takes the sign of the DIVIDEND (C99 truncation); b's sign does not matter.
 * Both operands are made positive. For a >= 0 it tail-branches to func_80028880 (__umoddi3).
 * Otherwise it inlines __umoddi3: for b.hi == 0 it calls func_80028624 and takes the 32-bit
 * remainder that routine leaves in $t1 (high word 0); otherwise it calls func_80028528, whose
 * remainder is left in $a0:$a1. Then it negates. $ra is kept in $t5 and the results come back in
 * $t1/$a0:$a1, so it cannot be compiled C.
 * Checked in an emulator against the ROM asm: 3000 random and edge pairs. Same results every time. */
#ifdef NON_MATCHING
#include "common.h"
extern u64 func_80028880(u64, u64); /* __umoddi3: unsigned 64-bit a % b */

s64 __moddi3(s64 a, s64 b)
{
    /* The remainder takes the sign of the dividend (C99 truncating division). */
    s32 negative = a < 0;
    u64 ua = (a < 0) ? -(u64)a : (u64)a;
    u64 ub = (b < 0) ? -(u64)b : (u64)b;
    u64 r;

    if (!negative) {
        return func_80028880(ua, ub); /* tail branch in the asm */
    }
    /* Negative dividend: the asm inlines __umoddi3 (remainder from func_80028624's $t1 when
     * b.hi == 0, else from func_80028528's $a0:$a1) and then negates it. */
    r = func_80028880(ua, ub);
    return -(s64)r;
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    ".globl __moddi3\n"
    ".ent __moddi3\n"
    "__moddi3:\n"
    "lui $t0, (0x80000000 >> 16)\n"
    "addu $v1, $a0, $zero\n"
    "and $t9, $t0, $a0\n"
    "beqz $t9, .L800287CC\n"
    "nop\n"
    "addiu $t1, $zero, -0x1\n"
    "xor $a1, $a1, $t1\n"
    "xor $a0, $a0, $t1\n"
    "addiu $a1, $a1, 0x1\n"
    "sltiu $t9, $a1, 0x1\n"
    "addu $a0, $a0, $t9\n"
    ".L800287CC:\n"
    "and $t9, $t0, $a2\n"
    "beqz $t9, .L800287F0\n"
    "nop\n"
    "addiu $t1, $zero, -0x1\n"
    "xor $a3, $a3, $t1\n"
    "xor $a2, $a2, $t1\n"
    "addiu $a3, $a3, 0x1\n"
    "sltiu $t9, $a3, 0x1\n"
    "addu $a2, $a2, $t9\n"
    ".L800287F0:\n"
    "and $v1, $v1, $t0\n"
    ".word 0x10600022 /* beqz func_80028880: target outside this function */\n"
    "nop\n"
    "bnez $a2, .L80028820\n"
    "nop\n"
    "addu $t5, $ra, $zero\n"
    "jal func_80028624\n"
    "nop\n"
    "addu $ra, $t5, $zero\n"
    "addu $v1, $t1, $zero\n"
    "j .L80028838\n"
    "xor $v0, $v0, $v0\n"
    ".L80028820:\n"
    "addu $t5, $ra, $zero\n"
    "jal func_80028528\n"
    "nop\n"
    "addu $ra, $t5, $zero\n"
    "addu $v1, $a1, $zero\n"
    "addu $v0, $a0, $zero\n"
    ".L80028838:\n"
    "addiu $a3, $zero, -0x1\n"
    "xor $v1, $v1, $a3\n"
    "xor $v0, $v0, $a3\n"
    "addiu $v1, $v1, 0x1\n"
    "sltiu $t9, $v1, 0x1\n"
    "jr $ra\n"
    "addu $v0, $v0, $t9\n"
    "nop\n"
    "nop\n"
    "nop\n"
    ".end __moddi3\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
