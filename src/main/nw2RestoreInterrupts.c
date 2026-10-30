/* @header
 * nw2RestoreInterrupts  (originally func_80026B30)
 * VRAM 0x80026B30 | ROM 0x27730 | size 0x1C
 * asm: asm/nonmatchings/main/nw2RestoreInterrupts.s
 */
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
".set noreorder\n"
".set noat\n"
"\n"
".globl nw2RestoreInterrupts\n"
".ent nw2RestoreInterrupts\n"
"nw2RestoreInterrupts:\n"
"mfc0 $t0, $12 /* handwritten instruction */\n"
"or $t0, $t0, $a0\n"
"mtc0 $t0, $12 /* handwritten instruction */\n"
"nop\n"
"nop\n"
"jr $ra\n"
"nop\n"
"nop\n"
".end nw2RestoreInterrupts\n"
".set at\n"
".set reorder\n"
);
