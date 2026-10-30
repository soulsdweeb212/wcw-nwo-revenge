/* @header
 * func_80008634
 * VRAM 0x80008634 | ROM 0x9234 | size 0x44
 * asm: asm/nonmatchings/main/func_80008634.s
 */
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
