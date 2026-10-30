/* @header
 * startPiDmaWithHandle  (originally func_80027970)
 * VRAM 0x80027970 | ROM 0x28570 | size 0x1CC
 * asm: asm/nonmatchings/main/func_80027970.s
 */
#include "common.h"

/* Start a PI DMA transfer using a PI handle. Waits for the PI to go idle
 * (PI_STATUS bits 0..1), and if the handle differs from the one last used for
 * its domain, programs the domain's latency/pulse/page/release registers and
 * records it in D_80037620. Sets the DRAM and device addresses, then triggers
 * a write (direction 0) or read (direction 1) of `size` bytes. Returns 0, or
 * -1 for an unknown direction. */
extern Nw2PiHandle *D_80037620[];
u32 func_8001CE80(void *);

s32 startPiDmaWithHandle(Nw2PiHandle *h, s32 direction, u32 devAddr, void *dramAddr, s32 size) {
    Nw2PiHandle *old;
    volatile u32 *reg;
    u32 stat;
    s32 domain;

    stat = *(volatile u32 *)0xA4600010;
    while (stat & 3) stat = *(volatile u32 *)0xA4600010;
    domain = h->domain;
    old = D_80037620[domain];
    if (old != h) {
        if (domain == 0) {
            if (old->latency != h->latency) *(volatile u32 *)0xA4600014 = h->latency;
            if (old->pulse != h->pulse) *(volatile u32 *)0xA460001C = h->pulse;
            if (old->page != h->page) *(volatile u32 *)0xA4600020 = h->page;
            if (old->release != h->release) *(volatile u32 *)0xA4600018 = h->release;
        } else {
            if (old->latency != h->latency) *(volatile u32 *)0xA4600024 = h->latency;
            if (old->pulse != h->pulse) *(volatile u32 *)0xA460002C = h->pulse;
            if (old->page != h->page) *(volatile u32 *)0xA4600030 = h->page;
            if (old->release != h->release) *(volatile u32 *)0xA4600028 = h->release;
        }
        D_80037620[domain] = h;
    }
    *(volatile u32 *)0xA4600000 = func_8001CE80(dramAddr);
    *(volatile u32 *)0xA4600004 = (h->base | devAddr) & 0x1FFFFFFF;
    switch (direction) {
    case 0: reg = (volatile u32 *)0xA460000C; break;
    case 1: reg = (volatile u32 *)0xA4600008; break;
    default: return -1;
    }
    *reg = size - 1;
    return 0;
}
