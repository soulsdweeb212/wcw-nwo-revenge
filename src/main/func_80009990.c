/* @header
 * func_80009990
 * VRAM 0x80009990 | ROM 0xA590 | size 0x1F4
 * asm: asm/nonmatchings/main/func_80009990.s
 */
#include "common.h"

typedef struct {
    u16 type;
    u8 pri;
    u8 status;
    void *retQueue;
    u32 dramAddr;
    u32 devAddr;
    s32 size;
    void *piHandle;
} IoMsg9990;

typedef struct {
    u8 pad0[0xC];
    u32 dev;
    u32 dram;
    s32 remaining;
    u8 pad18[0x78];
    u8 mq[2][0x18];
    IoMsg9990 io[2];
    void *msgs[2];
    u16 idx;
    u16 started;
} Stream9990;

#ifndef TARGET_PC /* on PC, port_decls.h declares D_800706A8 (as Nw2AnimStream) and D_8004859C */
extern Stream9990 D_800706A8[];
extern void *D_8004859C;
#endif
s32 osEPiStartDma(void *, void *, s32);
s32 osRecvMesg(void *, void *, s32);

#ifdef TARGET_PC
/* PC: the stream record is Nw2AnimStream (common.h), read by field name: source is a RomAddr, destination a host
 * pointer, and the two reads are port.h's PortIoMesg requests, whose dramAddr holds the whole address (the N64's
 * Stream9990 view keeps it in a u32). The N64 code reaches the same fields through its own view at the N64 offsets:
 * dev +0xC, dram +0x10, mq +0x90, io +0xC0, msgs +0xF0, idx +0xF8, started +0xFA. */
void func_80009990(s16 n)
{
    Nw2AnimStream *s = &D_800706A8[n];
    s32 count;
    s32 idx;

    if (s->remaining == 0) {
        return;
    }
    count = 0x80;
    if (s->remaining < 0x80) {
        count = s->remaining;
    }
    idx = s->ioNext;
    s->ios[idx].retQueue = s->ioQueues[idx];
    s->ios[idx].pri = 0;
    s->ios[idx].devAddr = s->source;
    s->ios[idx].dramAddr = s->destination;
    s->ios[idx].size = count;
    while (osEPiStartDma(D_8004859C, &s->ios[idx], 0) != 0) {
    }
    idx ^= 1;
    if (s->ioStarted) {
        osRecvMesg(s->ioQueues[idx], NULL, 1);
    } else {
        s->ioStarted = 1;
    }
    s->ioNext = idx;
    s->source += count;
    s->destination += count;
    s->remaining -= count;
}
#else
void func_80009990(s16 n)
{
    s32 count;
    s32 idx;

    if (D_800706A8[n].remaining == 0) {
        return;
    }
    count = 0x80;
    if (D_800706A8[n].remaining < 0x80) {
        count = D_800706A8[n].remaining;
    }
    idx = D_800706A8[n].idx;
    D_800706A8[n].io[idx].retQueue = D_800706A8[n].mq[idx];
    D_800706A8[n].io[idx].pri = 0;
    D_800706A8[n].io[idx].devAddr = D_800706A8[n].dev;
    D_800706A8[n].io[idx].dramAddr = D_800706A8[n].dram;
    D_800706A8[n].io[idx].size = count;
    while (osEPiStartDma(D_8004859C, &D_800706A8[n].io[idx], 0) != 0) {
    }
    idx ^= 1;
    if (D_800706A8[n].started) {
        osRecvMesg(D_800706A8[n].mq[idx], NULL, 1);
    } else {
        D_800706A8[n].started = 1;
    }
    D_800706A8[n].idx = idx;
    D_800706A8[n].dev += count;
    D_800706A8[n].dram += count;
    D_800706A8[n].remaining -= count;
}
#endif
