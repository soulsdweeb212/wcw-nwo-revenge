/* @header
 * func_8009126C
 * VRAM 0x8009126C | ROM 0x3D9DC | size 0x28
 * asm: asm/nonmatchings/code_80090000/func_8009126C.s
 */
#include "common.h"

extern u8 D_800C5D10[];

/* Append a G_LOAD_UCODE display-list command (0xDE000000 + ucode pointer) to *arg0. */
#ifdef TARGET_PC
/* PC: the command is port.h's 16-byte Gfx, and the address goes into it as the whole pointer (port.h's DL_ADDR).
 * D_800C5D10 + 0x48 is the label D_800C5D58, which the asm loads; the PC names it. */
extern u8 D_800C5D58[];
void func_8009126C(Gfx **arg0) {
    Gfx *p = *arg0;
    p->w0 = 0xDE000000;
    p->w1 = DL_ADDR(D_800C5D58);
    *arg0 = p + 1;
}
#else
void func_8009126C(u32 **arg0) {
    u32 *p = *arg0;
    u32 *start = p;
    p += 2;
    start[0] = 0xDE000000;
    start[1] = (u32)D_800C5D10 + 0x48;
    *arg0 = p;
}
#endif
