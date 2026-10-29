/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
".set noreorder\n"
".set noat\n"
".globl func_80026C10\n"
".ent func_80026C10\n"
"func_80026C10:\n"
"cfc1 $v0, $31\n"
"ctc1 $a0, $31\n"
"jr $ra\n"
"nop\n"
".end func_80026C10\n"
".set at\n"
".set reorder\n"
);
