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
