/* @header
 * loadTextureIntoCacheSlot  (originally func_8000BC78)
 * VRAM 0x8000BC78 | ROM 0xC878 | size 0x158
 * asm: asm/nonmatchings/main/loadTextureIntoCacheSlot.s
 */
#include "common.h"

#ifndef TARGET_PC /* on PC, port_decls.h declares D_8007C438: the addresses as void * */
extern s32 D_8007C438[][23];
#endif
extern u16 D_8007C318[][23];

typedef struct {
    s32 start;
    s32 end;
    s32 size;
    s32 rangeSize;
} Nw2SectionInfo;

void *allocateHeap(u32 bytes);
#ifdef TARGET_PC
/* PC: its definition takes the block's address as a pointer, so it is declared with a pointer here. */
void releaseHeapBlock(void *);
#else
void releaseHeapBlock(s32);
#endif
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void lookupResourceDescriptor(Nw2SectionInfo *, s32);
void func_80003684(Nw2SectionInfo *, s32, void *);
#endif
void func_80004F80(void *, s16, s16);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_8000B884, which takes the palette as a u16 * */
void func_8000B884(s32, s16, s16);
#endif

/* Loads resource `arg2` into texture-cache row arg3, slot arg4: frees any
 * existing buffer in that slot, allocates at least 0x20 bytes for the decoded
 * resource, decodes it into the new buffer and records its halfword length in
 * D_8007C318. Then refreshes the palette cache for the entity. */
#ifdef TARGET_PC
/* PC: the texture-cache table is void *[4][23] (port_decls.h), so the slot is a void ** and the buffer's address is
 * kept whole; the N64 computes the slot's address and stores the buffer's address in 32 bits. The animation rows that
 * follow the table on the N64 are a variable of their own on PC (D_8007C5B8). arg0 is a display record (Nw2Descr4BA8
 * in common.h): its palette is the pointer f1C on PC (+0x1C on the N64). */
void loadTextureIntoCacheSlot(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    Nw2SectionInfo info;
    Nw2SectionInfo out;
    u32 size;
    void **slot;
    u16 id;
    void *buf;

    func_80004F80(arg0, arg1, arg2);
    if (arg2 != 0) {
        id = arg2 & 0xFFFF;
        lookupResourceDescriptor(&info, id);
        slot = &D_8007C438[arg3][arg4];
        if (*slot != NULL) {
            releaseHeapBlock(*slot);
            *slot = NULL;
        }
        size = info.size;
        if (size < 0x20) {
            size = 0x20;
        }
        buf = allocateHeap(size);
        *slot = buf;
        func_80003684(&out, id, buf);
        D_8007C318[arg3][arg4] = (u16)(size >> 1);
    }
    func_8000B884(((Nw2Descr4BA8 *)arg0)->f1C, arg3, arg4);
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
