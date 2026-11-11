/* @header
 * func_80007B84
 * VRAM 0x80007B84 | ROM 0x8784 | size 0x34
 * asm: asm/nonmatchings/main/func_80007B84.s
 */
#include "common.h"

/* Allocate arg1 8-byte records from the second pool in arg0. */
#ifdef TARGET_PC
/* PC: arg0 is an arena in its PC layout (Nw2MeshArena, common.h), whose pool-2 base is a pointer, read here by name.
 * A record here is a display-list command, 16 bytes on PC (port.h's Gfx, 8 bytes on the N64), and func_80007A74
 * sized the block in sizeof(Gfx) commands, so the step is sizeof(Gfx). As on the N64, the count moves on even when
 * the pool overflows, and the result is then NULL. The address is worked out in a uptr, as the N64 works it out in an
 * s32, so that an empty arena (base NULL) does no arithmetic on a null pointer. */
void *func_80007B84(void *arg0, s32 arg1) {
    Nw2MeshArena *a = arg0;
    u16 first = a->cmdUsed;
    u16 used = first + arg1;

    a->cmdUsed = used;
    return (used <= a->cmdCap) ? (void *)((uptr)a->cmds + (uptr)first * sizeof(Gfx)) : NULL;
}
#else
void *func_80007B84(void *arg0, s32 arg1) {
    u16 used = *(u16 *)((u8 *)arg0 + 0xE);
    s32 off = used * 8;
    u16 cap = *(u16 *)((u8 *)arg0 + 0xC);
    s32 p = *(s32 *)((u8 *)arg0 + 8);

    p += off;
    used += arg1;
    *(u16 *)((u8 *)arg0 + 0xE) = used;
    return (used <= cap) ? (void *)p : NULL;
}
#endif
