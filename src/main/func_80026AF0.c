/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
".set noreorder\n"
".set noat\n"
"\n"
".globl func_80026AF0\n"
".ent func_80026AF0\n"
"func_80026AF0:\n"
"mfc0 $v0, $9 /* handwritten instruction */\n"
"jr $ra\n"
"nop\n"
"nop\n"
".end func_80026AF0\n"
".set at\n"
".set reorder\n"
);
