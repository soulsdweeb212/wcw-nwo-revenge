/* @header
 * func_8000670C
 * VRAM 0x8000670C | ROM 0x730C | size 0x108
 * asm: asm/nonmatchings/main/func_8000670C.s
 */
#include "common.h"

typedef struct { s32 w0, w1, w2, w3; } IdInfo;
typedef struct { void *f0; void *f4; } Nw2TwoBuf;
#ifdef TARGET_PC
/* PC: arg0 is a picture pair (common.h's Nw2TexPair), two pointers there, the palette at +8; callers step arrays of
 * pairs by sizeof(Nw2TexPair). This view keeps its own field names, so the assert checks that it has the same
 * layout. */
_Static_assert(sizeof(Nw2TwoBuf) == sizeof(Nw2TexPair) && offsetof(Nw2TwoBuf, f0) == offsetof(Nw2TexPair, img) &&
                   offsetof(Nw2TwoBuf, f4) == offsetof(Nw2TexPair, pal),
               "Nw2TwoBuf must follow Nw2TexPair");
#endif
void *allocateHeap(u32);
void releaseHeapBlock(void *);
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void lookupResourceDescriptor(IdInfo *, u16);
void func_80003684(IdInfo *, u16, void *);
#endif
/* Loads the two resources arg1/arg2 into arg0's two buffers. For each id: if the
 * existing buffer is too small for the decoded resource it is freed and a new
 * one (at least 0x808 / 0x20 bytes) is allocated; the resource is then decoded
 * into the buffer. */
void func_8000670C(Nw2TwoBuf *arg0, s16 arg1, s16 arg2) {
    IdInfo a, b, c;
    if (arg1) {
        lookupResourceDescriptor(&a, arg1);
        if (arg0->f0 != 0) {
            if (a.w2 < 0x809) goto keep1;
            releaseHeapBlock(arg0->f0);
        }
        if (a.w2 < 0x808) a.w2 = 0x808;
        arg0->f0 = allocateHeap(a.w2);
keep1:
        func_80003684(&c, arg1, arg0->f0);
    }
    if (arg2) {
        lookupResourceDescriptor(&b, arg2);
        if (arg0->f4 != 0) {
            if (b.w2 < 0x21) goto keep2;
            releaseHeapBlock(arg0->f4);
        }
        if (b.w2 < 0x20) b.w2 = 0x20;
        arg0->f4 = allocateHeap(b.w2);
keep2:
        func_80003684(&c, arg2, arg0->f4);
    }
}
