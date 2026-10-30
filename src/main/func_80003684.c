/* @header
 * func_80003684
 * VRAM 0x80003684 | ROM 0x4284 | size 0x170
 * asm: asm/nonmatchings/main/func_80003684.s
 */
#include "common.h"

/*
 * Decode the resource descriptor for `id` into `out`.  The descriptor table
 * D_800482E0 holds packed ROM addresses (low bit = "compressed"); a compressed
 * resource is loaded into a temporary heap buffer and decompressed by
 * func_800037F4, otherwise the raw bytes are read straight into `buf`.
 */
typedef struct {
    u8 *volatile src;
    u8 *volatile dst;
    s32 size;
    s32 delta;
} Nw2ResourceDesc;

void *allocateHeap(u32);
void readRomSynchronousChunks(void *, void *, s32);
void func_800037F4(void *, void *);
void releaseHeapBlock(void *);

extern s32 *D_800482E0;
extern s32 *D_800482E4;
extern u8 D_000DAC50[];

void *func_80003684(void *out, s32 id, void *buf) {
    Nw2ResourceDesc res;
    Nw2ResourceDesc rec;
    Nw2ResourceDesc *p;
    s32 *entry;
    s32 index;
    s32 srcWord;
    s32 dstWord;
    u8 *srcPtr;
    u8 *dstPtr;

    p = &res;
    if ((u16)id < 1 || (u16)id >= 0x1DEA) {
        for (;;) {}
    }
    id = id - 1;
    index = id & 0xFFFF;
    entry = D_800482E0 + index;
    srcWord = entry[0];
    rec.src = (u8 *)srcWord;
    dstWord = entry[1];
    srcPtr = (u8 *)((srcWord & ~1) + (s32)D_000DAC50);
    rec.src = (u8 *)(srcWord & ~1);
    rec.src = srcPtr;
    rec.dst = (u8 *)dstWord;
    dstPtr = (u8 *)((dstWord & ~1) + (s32)D_000DAC50);
    rec.dst = (u8 *)(dstWord & ~1);
    rec.dst = dstPtr;
    rec.size = D_800482E4[index];
    rec.delta = (srcWord & 1) ? (s32)(dstPtr - srcPtr) : 0;
    *p = rec;
    if (res.delta > 0) {
        u8 *b = allocateHeap(res.delta);
        readRomSynchronousChunks(res.src, b, res.delta);
        func_800037F4(b, buf);
        releaseHeapBlock(b);
    } else {
        readRomSynchronousChunks(res.src, buf, res.size);
    }
    *(Nw2ResourceDesc *)out = res;
    return out;
}
