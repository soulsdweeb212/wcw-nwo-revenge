/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
".set noreorder\n"
".set noat\n"
"\n"
".globl func_80026B00\n"
".ent func_80026B00\n"
"func_80026B00:\n"
"mfc0 $v0, $12 /* handwritten instruction */\n"
"jr $ra\n"
"nop\n"
"nop\n"
".end func_80026B00\n"
".set at\n"
".set reorder\n"
);
