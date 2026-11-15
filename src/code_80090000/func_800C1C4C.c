/* @header
 * func_800C1C4C
 * VRAM 0x800C1C4C | ROM 0x6E3BC | size 0x24
 * asm: asm/nonmatchings/code_80090000/func_800C1C4C.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_800DF210 holds the address of a heap block (func_800C1B24 allocates it), which an s32 would cut in half;
 * releaseHeapBlock's definition takes a u8 *. */
extern u8 *D_800DF210;
void releaseHeapBlock(u8 *);
#else
extern s32 D_800DF210;
void releaseHeapBlock(s32);
#endif

void func_800C1C4C(void) {
    releaseHeapBlock(D_800DF210);
}
