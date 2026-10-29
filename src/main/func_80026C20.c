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
