/* @header
 * func_800273A0
 * VRAM 0x800273A0 | ROM 0x27FA0 | size 0x30
 * asm: asm/nonmatchings/main/func_800273A0.s
 */
#include "common.h"

extern s32 D_80037600;
extern s32 D_80037608;

/* Start a DMA transfer when the PI status bit 0 is set; returns 0, or -1 if busy. */
s32 func_800273A0(s32 arg0) {
    s32 r;
    if (*(vu32 *)0xA4040010 & 1) {
        *(vu32 *)0xA4080000 = arg0;
        r = 0;
    } else {
        r = -1;
    }
    return r;
}
