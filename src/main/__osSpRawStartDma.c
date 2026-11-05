/* @header
 * __osSpRawStartDma  (originally func_800273D0)
 * VRAM 0x800273D0 | ROM 0x27FD0 | size 0xF8
 * asm: asm/nonmatchings/main/__osSpRawStartDma.s
 */
/* SDK: libultra 2.0I, ultralib src/io/sprawdma.c (same code as the SDK source). */
#include "common.h"

extern char D_8003B970[];
extern char D_8003B974[];
void __assert(char *, char *, s32);
u32 osVirtualToPhysical(void *);
s32 __osSpDeviceBusy(void);

/* Validates a raw PI DMA request (device address, DRAM address and size must
 * all be 8-byte aligned, warning otherwise), bails if the PI is busy, then
 * programs the PI address/length registers: direction 0 writes PI_WR_LEN
 * (cart->RAM), otherwise PI_RD_LEN (RAM->cart). Returns -1 if busy, else 0. */
s32 __osSpRawStartDma(s32 dir, u32 devAddr, u32 dramAddr, u32 size) {
    if (devAddr & 7) {
        __assert(D_8003B970, D_8003B974, 0x3A);
    }
    if (dramAddr & 7) {
        __assert(D_8003B970, D_8003B974, 0x3B);
    }
    if (size & 7) {
        __assert(D_8003B970, D_8003B974, 0x3C);
    }
    if (__osSpDeviceBusy() != 0) {
        return -1;
    }
    *(vu32 *)0xA4040000 = devAddr;
    *(vu32 *)0xA4040004 = osVirtualToPhysical((void *)dramAddr);
    if (dir == 0) {
        *(vu32 *)0xA404000C = size - 1;
    } else {
        *(vu32 *)0xA4040008 = size - 1;
    }
    return 0;
}
