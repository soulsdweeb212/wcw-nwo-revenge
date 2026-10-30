/* @header
 * func_80028860
 * VRAM 0x80028860 | ROM 0x29460 | size 0x18
 * asm: asm/nonmatchings/main/func_80028860.s
 */
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
".set noreorder\n"
".set noat\n"
".globl func_80028860\n"
".ent func_80028860\n"
"func_80028860:\n"
"bnez $a2, .L80028870\n"
"nop\n"
"j func_80028624\n"
"nop\n"
".L80028870:\n"
"j func_80028528\n"
"nop\n"
"nop\n"
"nop\n"
".end func_80028860\n"
".set at\n"
".set reorder\n"
);
