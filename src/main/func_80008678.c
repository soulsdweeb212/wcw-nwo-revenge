/* @header
 * func_80008678
 * VRAM 0x80008678 | ROM 0x9278 | size 0x2C
 * asm: asm/nonmatchings/main/func_80008678.s
 */
#include "common.h"

s32 releaseHeapBlock(s32);
extern s32 D_8007BD38;

/* Release the shared record table and clear the pointer. */
void func_80008678(void) {
    releaseHeapBlock(D_8007BD38);
    D_8007BD38 = 0;
}
