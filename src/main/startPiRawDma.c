/* @header
 * startPiRawDma  (originally func_80027880)
 * VRAM 0x80027880 | ROM 0x28480 | size 0xD0
 * asm: asm/nonmatchings/main/startPiRawDma.s
 */
#include "common.h"

extern u32 D_80000308;
u32 func_8001CE80(void *);

/* Start a raw PI DMA transfer: wait for the PI to be idle, program the DRAM and
 * device addresses (devAddr ORed with the current PI device base), select the
 * read (0xA4600008) or write (0xA460000C) length register by direction, and set
 * it to size-1. Returns 0, or -1 for an invalid direction. */
s32 startPiRawDma(s32 direction, u32 devAddr, void *dramAddr, u32 size) {
    u32 stat;
    volatile u32 *reg;
    stat = *(volatile u32 *)0xA4600010;
    while (stat & 3) stat = *(volatile u32 *)0xA4600010;
    *(volatile u32 *)0xA4600000 = func_8001CE80(dramAddr);
    *(volatile u32 *)0xA4600004 = (D_80000308 | devAddr) & 0x1FFFFFFF;
    switch (direction) {
    case 0: reg = (volatile u32 *)0xA460000C; break;
    case 1: reg = (volatile u32 *)0xA4600008; break;
    default: return -1;
    }
    *reg = size - 1;
    return 0;
}
