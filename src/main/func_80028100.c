/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
".set noreorder\n"
".set noat\n"
"\n"
".globl func_80028100\n"
".ent func_80028100\n"
"func_80028100:\n"
"mtc0 $a0, $11 /* handwritten instruction */\n"
"jr $ra\n"
"nop\n"
"nop\n"
".end func_80028100\n"
".set at\n"
".set reorder\n"
);
