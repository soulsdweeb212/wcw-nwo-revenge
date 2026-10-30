/* @header
 * func_80026C20
 * VRAM 0x80026C20 | ROM 0x27820 | size 0x10
 * asm: asm/nonmatchings/main/func_80026C20.s
 */
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
".set noreorder\n"
".set noat\n"
"\n"
".globl func_80026C20\n"
".ent func_80026C20\n"
"func_80026C20:\n"
"mtc0 $a0, $12 /* handwritten instruction */\n"
"nop\n"
"jr $ra\n"
"nop\n"
".end func_80026C20\n"
".set at\n"
".set reorder\n"
);
