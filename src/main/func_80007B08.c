/* @header
 * func_80007B08
 * VRAM 0x80007B08 | ROM 0x8708 | size 0x48
 * asm: asm/nonmatchings/main/func_80007B08.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: releaseHeapBlock with its definition's type (releaseHeapBlock.c): it takes an address, which an s32 would cut
 * to 32 bits. */
void releaseHeapBlock(u8 *);
#else
s32 releaseHeapBlock(s32);
#endif

/* Reset two allocation groups in arg0: clear the s16 counters at +4/+6 and release
 * and clear the pointer at +0, then the same at +0xC/+0xE and +8. */
#ifdef TARGET_PC
/* PC: arg0 is an arena in its PC layout (Nw2MeshArena, common.h): its two bases are pointers, which the N64's 4-byte
 * fields at +0x0 and +0x8 would cut in half, so every field goes by name, in the N64's order. releaseHeapBlock does
 * nothing for NULL, on PC as on the N64. */
void func_80007B08(void *arg0) {
    Nw2MeshArena *a = arg0;

    a->vertUsed = 0;
    a->vertCap = 0;
    releaseHeapBlock((u8 *)a->verts);
    a->verts = NULL;
    a->cmdUsed = 0;
    a->cmdCap = 0;
    releaseHeapBlock((u8 *)a->cmds);
    a->cmds = NULL;
}
#else
void func_80007B08(void *arg0) {
    *(s16 *)((s8 *)arg0 + 6) = 0;
    *(s16 *)((s8 *)arg0 + 4) = 0;
    releaseHeapBlock(*(s32 *)((s8 *)arg0 + 0));
    *(s32 *)((s8 *)arg0 + 0) = 0;
    *(s16 *)((s8 *)arg0 + 0xE) = 0;
    *(s16 *)((s8 *)arg0 + 0xC) = 0;
    releaseHeapBlock(*(s32 *)((s8 *)arg0 + 8));
    *(s32 *)((s8 *)arg0 + 8) = 0;
}
#endif
