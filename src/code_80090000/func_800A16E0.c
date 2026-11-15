/* @header
 * func_800A16E0
 * VRAM 0x800A16E0 | ROM 0x4DE50 | size 0x3C
 * asm: asm/nonmatchings/code_80090000/func_800A16E0.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the three variables hold the addresses of heap blocks (func_800A167C allocates them), which an s32 would cut in
 * half; releaseHeapBlock's definition takes a u8 * and returns nothing. */
void releaseHeapBlock(u8 *);
extern u8 *D_800DC730;
extern u8 *D_800DC734;
extern u8 *D_800DC740;
#else
s32 releaseHeapBlock(s32);                            /* extern */
extern s32 D_800DC730;
extern s32 D_800DC734;
extern s32 D_800DC740;
#endif

void func_800A16E0(void) {
    releaseHeapBlock(D_800DC740);
    releaseHeapBlock(D_800DC734);
    releaseHeapBlock(D_800DC730);
}
