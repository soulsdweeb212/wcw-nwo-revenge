/* @header
 * func_800284F4
 * VRAM 0x800284F4 | ROM 0x290F4 | size 0x34
 * asm: asm/nonmatchings/main/func_800284F4.s
 */
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
".set noreorder\n"
".set noat\n"
".globl func_800284F4\n"
".ent func_800284F4\n"
"func_800284F4:\n"
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
".end func_800284F4\n"
".set at\n"
".set reorder\n"
);
