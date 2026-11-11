/* @header
 * func_80007B50
 * VRAM 0x80007B50 | ROM 0x8750 | size 0x34
 * asm: asm/nonmatchings/main/func_80007B50.s
 */
#include "common.h"

/* Allocates arg1 0x10-byte records from the descriptor's first pool (+0/+4/+6),
 * returning the block or NULL when it would overflow. */
#ifdef TARGET_PC
/* PC: arg0 is an arena in its PC layout (Nw2MeshArena, common.h), whose pool-1 base is a pointer, read here by name.
 * A vertex record is 16 bytes on both machines. As on the N64, the count moves on even when the pool overflows, and
 * the result is then NULL. The address is worked out in a uptr, as the N64 works it out in an s32, so that an empty
 * arena (base NULL) does no arithmetic on a null pointer. */
void *func_80007B50(void *arg0, s32 arg1) {
    Nw2MeshArena *a = arg0;
    u16 first = a->vertUsed;
    u16 used = first + arg1;

    a->vertUsed = used;
    return (used <= a->vertCap) ? (void *)((uptr)a->verts + (uptr)first * NW2_MESH_ARENA_VERTEX_SIZE) : NULL;
}
#else
void *func_80007B50(void *arg0, s32 arg1) {
    u16 used = *(u16 *)((u8 *)arg0 + 6);
    s32 off = used * 0x10;
    u16 cap = *(u16 *)((u8 *)arg0 + 4);
    s32 p = *(s32 *)arg0;

    p += off;
    used += arg1;
    *(u16 *)((u8 *)arg0 + 6) = used;
    return (used <= cap) ? (void *)p : NULL;
}
#endif
