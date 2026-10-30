/* @header
 * func_80026C30
 * VRAM 0x80026C30 | ROM 0x27830 | size 0x44
 * asm: asm/nonmatchings/main/func_80026C30.s
 */
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
".set noreorder\n"
".set noat\n"
"\n"
".globl func_80026C30\n"
".ent func_80026C30\n"
"func_80026C30:\n"
"mfc0 $t0, $10 /* handwritten instruction */\n"
"addiu $t1, $zero, 0x1E\n"
"lui $t2, (0x80000000 >> 16)\n"
"mtc0 $t2, $10 /* handwritten instruction */\n"
"mtc0 $zero, $2 /* handwritten instruction */\n"
"mtc0 $zero, $3 /* handwritten instruction */\n"
".L80026C48:\n"
"mtc0 $t1, $0 /* handwritten instruction */\n"
"nop\n"
"tlbwi /* handwritten instruction */\n"
"nop\n"
"nop\n"
"addi $t1, $t1, -0x1 /* handwritten instruction */\n"
"bgez $t1, .L80026C48\n"
"nop\n"
"mtc0 $t0, $10 /* handwritten instruction */\n"
"jr $ra\n"
"nop\n"
"nop\n"
"nop\n"
"nop\n"
".end func_80026C30\n"
".set at\n"
".set reorder\n"
);
