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

extern Stream9990 D_800706A8[];
extern void *D_8004859C;
s32 func_800219B0(void *, void *, s32);
s32 func_8001C990(void *, void *, s32);

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
    while (func_800219B0(D_8004859C, &D_800706A8[n].io[idx], 0) != 0) {
    }
    idx ^= 1;
    if (D_800706A8[n].started) {
        func_8001C990(D_800706A8[n].mq[idx], NULL, 1);
    } else {
        D_800706A8[n].started = 1;
    }
    D_800706A8[n].idx = idx;
    D_800706A8[n].dev += count;
    D_800706A8[n].dram += count;
    D_800706A8[n].remaining -= count;
}
