/* @header
 * func_80098EC8
 * VRAM 0x80098EC8 | ROM 0x45638 | size 0x24
 * asm: asm/nonmatchings/code_80090000/func_80098EC8.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_800E7518 holds the pool's address (port_decls.h: a Nw2ResourceRequest *), and releaseHeapBlock takes it as the
 * pointer it is (its definition's u8 *). */
void releaseHeapBlock(u8 *);
#else
typedef s32 M2C_UNK;
M2C_UNK releaseHeapBlock(s32);
extern s32 D_800E7518;
#endif

/* Frees the priority/resource request table. */
void func_80098EC8(void) {
#ifdef TARGET_PC
    releaseHeapBlock((u8 *)D_800E7518);
#else
    releaseHeapBlock(D_800E7518);
#endif
}
