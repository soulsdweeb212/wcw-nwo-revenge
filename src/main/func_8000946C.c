#include "common.h"

typedef struct {
    s16 id;
    s16 state;
    u8 *buffer;
    u8 *source;
    u8 *destination;
    s32 remaining;
    s16 f14;
    s16 f16;
    u8 pad18[0x40];
    u8 queue[24];
    s16 type;
    u8 priority;
    u8 status;
    void *returnQueue;
    u8 *dram;
    u8 *cart;
    s32 size;
    u8 tail[0x78];
} StreamSlot;

typedef struct {
    s16 a;
    s16 b;
} A2B2Rec;

extern StreamSlot D_800706AC[];
extern u8 *D_800485A0[];
extern s32 D_8004859C;
extern A2B2Rec D_8006A2B2[];

void func_8000B2B8(s32);
void lookupResourceDescriptor(void *, u16);
void func_8001C5B0(void *, s32);
s32 func_800219B0(s32, void *, s32);
s32 func_8001C990(void *, void *, s32);

/* Loads/advances a streamed resource for slot D_800706AC[slot].  If the requested
 * resource or frame differs from the current one it aborts the slot
 * (func_8000B2B8), looks up the resource descriptor, sets the source/destination
 * pointers and the remaining byte count at a per-frame offset (frame>>1 * 0x62)
 * inside the resource, primes the first chunk (func_8001C5B0), fills the DMA
 * queue message without waiting for a free slot, and enqueues it
 * (func_8001C990).  Then it clamps the requested frame to the resource's per-slot
 * maximum from D_8006A2B2 and records the destination buffer pointer. */
void func_8000946C(s16 slot, s16 resourceId, s16 frame) {
    s32 desc[4];
    s32 chunk;
    s32 offset;
    s32 headerBytes;
    u8 *src;

    if (resourceId != D_800706AC[slot].f14 || frame < D_800706AC[slot].state) {
        func_8000B2B8(slot);
        lookupResourceDescriptor(desc, (u16)resourceId);
        offset = (((frame << 16) >> 17) * 0x62) & ~0x1F;
        src = (u8 *)desc[0] + 4;
        D_800706AC[slot].source = src + offset;
        D_800706AC[slot].destination = D_800485A0[slot] + offset;
        headerBytes = offset + 4;
        D_800706AC[slot].remaining = desc[2] - headerBytes;
        D_800706AC[slot].state = frame;
        chunk = 0x100;
        func_8001C5B0(D_800706AC[slot].destination, D_800706AC[slot].remaining);
        if (D_800706AC[slot].remaining < 0x100) {
            chunk = D_800706AC[slot].remaining;
        }
        D_800706AC[slot].returnQueue = D_800706AC[slot].queue;
        D_800706AC[slot].priority = 0;
        D_800706AC[slot].size = chunk;
        D_800706AC[slot].cart = D_800706AC[slot].source;
        D_800706AC[slot].dram = D_800706AC[slot].destination;
        do {
        } while (func_800219B0(D_8004859C, &D_800706AC[slot].type, 0) != 0);
        D_800706AC[slot].f16 = -1;
        D_800706AC[slot].id = resourceId;
        D_800706AC[slot].f14 = resourceId;
        D_800706AC[slot].source += chunk;
        D_800706AC[slot].destination += chunk;
        D_800706AC[slot].remaining -= chunk;
        func_8001C990(D_800706AC[slot].queue, 0, 1);
    }

    {
        u8 *dst;
        s16 curId = D_800706AC[slot].f14;
        s16 maxFrame = D_8006A2B2[curId - 0xE39].a;
        if (maxFrame < frame) {
            frame = maxFrame;
        }
        dst = D_800485A0[slot];
        D_800706AC[slot].buffer = dst + ((frame << 16) >> 17) * 0x62;
    }
}
