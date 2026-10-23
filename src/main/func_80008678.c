#include "common.h"

s32 releaseHeapBlock(s32);
extern s32 D_8007BD38;

/* Release the shared record table and clear the pointer. */
void func_80008678(void) {
    releaseHeapBlock(D_8007BD38);
    D_8007BD38 = 0;
}
