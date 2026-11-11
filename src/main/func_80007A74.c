/* @header
 * func_80007A74
 * VRAM 0x80007A74 | ROM 0x8674 | size 0x88
 * asm: asm/nonmatchings/main/func_80007A74.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the heap functions with their definitions' types (allocateHeap.c, releaseHeapBlock.c): they return and take
 * addresses, which the N64 declarations' s32 would cut to 32 bits. */
void *allocateHeap(u32);
void releaseHeapBlock(u8 *);
#else
s32 allocateHeap(s32);
void releaseHeapBlock(s32);
#endif

/* Reinitializes the descriptor's two pools: frees the old buffers and allocates
 * new ones sized for arg1 0x10-byte and arg2 8-byte records. */
#ifdef TARGET_PC
/* PC: arg0 is an arena in its PC layout (Nw2MeshArena, common.h): its two bases are pointers, which the N64's 4-byte
 * fields at +0x0 and +0x8 would cut in half, so every field goes by name. Pool 2 holds display-list commands, 16 bytes
 * on PC (port.h's Gfx), so its block holds the N64's number of commands at sizeof(Gfx) each. The counts are written
 * from the s32 arguments as on the N64, which stores their low 16 bits. */
void func_80007A74(void *arg0, s32 arg1, s32 arg2) {
    Nw2MeshArena *a = arg0;

    if (a->verts != NULL) {
        releaseHeapBlock((u8 *)a->verts);
    }
    a->vertUsed = 0;
    a->vertCap = arg1;
    a->verts = allocateHeap((arg1 & 0xFFFF) * NW2_MESH_ARENA_VERTEX_SIZE);
    if (a->cmds != NULL) {
        releaseHeapBlock((u8 *)a->cmds);
    }
    a->cmdUsed = 0;
    a->cmdCap = arg2;
    a->cmds = allocateHeap((arg2 & 0xFFFF) * sizeof(Gfx));
}
#else
void func_80007A74(void *arg0, s32 arg1, s32 arg2) {
    s32 old;

    old = *(s32 *)((u8 *)arg0 + 0);
    if (old != 0) {
        releaseHeapBlock(old);
    }
    *(s16 *)((u8 *)arg0 + 6) = 0;
    *(s16 *)((u8 *)arg0 + 4) = arg1;
    *(s32 *)((u8 *)arg0 + 0) = allocateHeap((arg1 & 0xFFFF) * 0x10);
    old = *(s32 *)((u8 *)arg0 + 8);
    if (old != 0) {
        releaseHeapBlock(old);
    }
    *(s16 *)((u8 *)arg0 + 0xE) = 0;
    *(s16 *)((u8 *)arg0 + 0xC) = arg2;
    *(s32 *)((u8 *)arg0 + 8) = allocateHeap((arg2 & 0xFFFF) * 8);
}
#endif
