#include "common.h"

extern u8 *D_8007BD38;
extern void *D_800485A0[];
extern u8 D_800706C4[];

u8 *allocateHeap(s32);
void lookupResourceDescriptor(void *, s32);
void func_80003684(void *, s32, s32);
void releaseHeapBlock(void *);
f32 func_8000B370(s16);
void func_8001BE70(void *, f32, f32, f32);

/* Set the uniform scale of part arg0's matrix from its size. */
void func_80008C94(s16 arg0) {
    f32 f = func_8000B370(arg0);

    func_8001BE70(D_800706C4 + arg0 * 0xFC, f, f, f);
}
