/* @header
 * loadTextureIntoCacheSlot  (originally func_8000BC78)
 * VRAM 0x8000BC78 | ROM 0xC878 | size 0x158
 * asm: asm/nonmatchings/main/loadTextureIntoCacheSlot.s
 */
#include "common.h"

extern s32 D_8007C438[][23];
extern u16 D_8007C318[][23];

typedef struct {
    s32 start;
    s32 end;
    s32 size;
    s32 rangeSize;
} Nw2SectionInfo;

void *allocateHeap(u32 bytes);
void releaseHeapBlock(s32);
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void lookupResourceDescriptor(Nw2SectionInfo *, s32);
void func_80003684(Nw2SectionInfo *, s32, void *);
#endif
void func_80004F80(void *, s16, s16);
void func_8000B884(s32, s16, s16);

/* Loads resource `arg2` into texture-cache row arg3, slot arg4: frees any
 * existing buffer in that slot, allocates at least 0x20 bytes for the decoded
 * resource, decodes it into the new buffer and records its halfword length in
 * D_8007C318. Then refreshes the palette cache for the entity. */
#ifdef TARGET_PC
/* PC: not ported yet. The function keeps the loaded buffer's address in the texture-cache table D_8007C438, which
 * this file and func_8000C91C view as s32 and func_8000B884, func_8000CD84 and func_8000CFD4 as void *. Its PC storage
 * would be 0x2E0 bytes and so run 0x160 bytes into the animation rows that overlay 2 reaches at +0x180. That table has
 * no PC layout yet (docs/port.md, "Shared records on PC"). Even without a resource to load (arg2 == 0),
 * func_8000B884 then reads the slot's buffer from the table for most slots (those with a palette id in D_8003086C),
 * and on PC no address could have been kept there. So the PC stops the program here instead of keeping or reading half
 * an address. (arg0 is a display record, Nw2Descr4BA8 in common.h; its palette is the pointer field f1C on PC.) */
void loadTextureIntoCacheSlot(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    (void)arg0;
    (void)arg1;
    (void)arg2;
    (void)arg3;
    (void)arg4;
    port_fatal("loadTextureIntoCacheSlot: the texture-cache table D_8007C438 has no PC layout yet");
}
#else
void loadTextureIntoCacheSlot(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    Nw2SectionInfo info;
    Nw2SectionInfo out;
    u32 size;
    s32 r;
    s32 *base;
    s32 *row;
    s32 *slot;
    u16 id;
    void *buf;

    func_80004F80(arg0, arg1, arg2);
    if (arg2 != 0) {
        id = arg2 & 0xFFFF;
        lookupResourceDescriptor(&info, id);
        r = arg3;
        base = (s32 *)D_8007C438;
        row = base + r * 23;
        slot = (s32 *)(arg4 * 4 + (s32)row);
        if (*slot != 0) {
            releaseHeapBlock(*slot);
            *slot = 0;
        }
        size = info.size;
        if (size < 0x20) {
            size = 0x20;
        }
        buf = allocateHeap(size);
        *slot = (s32)buf;
        func_80003684(&out, id, buf);
        D_8007C318[r][arg4] = (u16)(size >> 1);
    }
    func_8000B884(*(s32 *)((u8 *)arg0 + 0x1C), arg3, arg4);
}
#endif
