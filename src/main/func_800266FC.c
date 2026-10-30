/* @header
 * func_800266FC
 * VRAM 0x800266FC | ROM 0x272FC | size 0x10
 * asm: asm/nonmatchings/main/func_800266FC.s
 */
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
".set noreorder\n"
".set noat\n"
".globl func_800266FC\n"
".ent func_800266FC\n"
"func_800266FC:\n"
"lw $v0, 0x0($a0)\n"
"lw $t9, 0x0($v0)\n"
"jr $ra\n"
"sw $t9, 0x0($a0)\n"
".end func_800266FC\n"
".set at\n"
".set reorder\n"
);
