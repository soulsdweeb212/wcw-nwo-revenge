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

/* Pointer to the resource entry for entity arg0 (0x24-byte stride). */
u8 *func_800087DC(s32 arg0) {
    u32 off = (s16)arg0 * 0x24 + 0xFFFDFFFC;
    return D_8007BD38 + off + 0x14;
}

/* Looks up resource descriptor 0x20F, allocates its size and stashes the block
 * in D_8007BD38. */
void func_80008634(void) {
    s32 buf1[4];
    s32 buf2[4];
    u8 *v;

    lookupResourceDescriptor(buf1, 0x20F);
    v = allocateHeap(buf1[2]);
    D_8007BD38 = v;
    func_80003684(buf2, 0x20F, (s32)v);
}

/* Releases the shared resource block and the four cached blocks. */
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

/* Builds a cube of size func_8000B370(arg0) at D_800706C4 + arg0*0xFC. */
void func_80008C94(s16 arg0) {
    f32 f = func_8000B370(arg0);

    func_8001BE70(D_800706C4 + arg0 * 0xFC, f, f, f);
}
