#include "common.h"

typedef s32 M2C_UNK;
M2C_UNK releaseHeapBlock(s32);
extern s32 D_800E7518;

/* Frees the priority/resource request table. */
void func_80098EC8(void) {
    releaseHeapBlock(D_800E7518);
}
