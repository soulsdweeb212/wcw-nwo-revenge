/* @header
 * func_800266B4
 * VRAM 0x800266B4 | ROM 0x272B4 | size 0x48
 * asm: asm/nonmatchings/main/func_800266B4.s
 */
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
".set noreorder\n"
".set noat\n"
".globl func_800266B4\n"
".ent func_800266B4\n"
"func_800266B4:\n"
"addu $t9, $a0, $zero\n"
"lw $t8, 0x0($a0)\n"
"lw $t7, 0x4($a1)\n"
"lw $t6, 0x4($t8)\n"
"slt $at, $t6, $t7\n"
"bnez $at, .L800266E8\n"
"nop\n"
".L800266D0:\n"
"addu $t9, $t8, $zero\n"
"lw $t8, 0x0($t8)\n"
"lw $t6, 0x4($t8)\n"
"slt $at, $t6, $t7\n"
"beqz $at, .L800266D0\n"
"nop\n"
".L800266E8:\n"
"lw $t8, 0x0($t9)\n"
"sw $t8, 0x0($a1)\n"
"sw $a1, 0x0($t9)\n"
"jr $ra\n"
"sw $a0, 0x8($a1)\n"
".end func_800266B4\n"
".set at\n"
".set reorder\n"
);
