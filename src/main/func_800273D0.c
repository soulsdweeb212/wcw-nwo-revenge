#include "common.h"

extern char D_8003B970[];
extern char D_8003B974[];
void func_8001CEE0(char *, char *, s32);
u32 func_8001CE80(void *);
s32 func_80027360(void);

/* Validates a raw PI DMA request (device address, DRAM address and size must
 * all be 8-byte aligned, warning otherwise), bails if the PI is busy, then
 * programs the PI address/length registers: direction 0 writes PI_WR_LEN
 * (cart->RAM), otherwise PI_RD_LEN (RAM->cart). Returns -1 if busy, else 0. */
s32 func_800273D0(s32 dir, u32 devAddr, u32 dramAddr, u32 size) {
    if (devAddr & 7) {
        func_8001CEE0(D_8003B970, D_8003B974, 0x3A);
    }
    if (dramAddr & 7) {
        func_8001CEE0(D_8003B970, D_8003B974, 0x3B);
    }
    if (size & 7) {
        func_8001CEE0(D_8003B970, D_8003B974, 0x3C);
    }
    if (func_80027360() != 0) {
        return -1;
    }
    *(vu32 *)0xA4040000 = devAddr;
    *(vu32 *)0xA4040004 = func_8001CE80((void *)dramAddr);
    if (dir == 0) {
        *(vu32 *)0xA404000C = size - 1;
    } else {
        *(vu32 *)0xA4040008 = size - 1;
    }
    return 0;
}
