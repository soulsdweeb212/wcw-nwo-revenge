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

/* Return a pointer to record arg0 (stride 0x24) in the table at D_8007BD38. */
u8 *func_800087DC(s32 arg0) {
    u32 off = (s16)arg0 * 0x24 + 0xFFFDFFFC;
    return D_8007BD38 + off + 0x14;
}

/* Load resource 0x20F into the heap block referenced by D_8007BD38. */
void func_80008634(void) {
    s32 buf1[4];
    s32 buf2[4];
    u8 *v;

    lookupResourceDescriptor(buf1, 0x20F);
    v = allocateHeap(buf1[2]);
    D_8007BD38 = v;
    func_80003684(buf2, 0x20F, (s32)v);
}

/* Release the shared table and the four auxiliary buffers in D_800485A0. */
void func_80008AF0(void) {
    void **p = D_800485A0;
    u32 i;

    releaseHeapBlock(D_8007BD38);
    D_8007BD38 = NULL;
    i = 0;
    do {
        releaseHeapBlock(*p++);
        i++;
    } while (i < 4U);
    D_800485A0[i] = NULL;
}

/* Set the uniform scale of part arg0's matrix from its size. */
void func_80008C94(s16 arg0) {
    f32 f = func_8000B370(arg0);

    func_8001BE70(D_800706C4 + arg0 * 0xFC, f, f, f);
}
