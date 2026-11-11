/* @header
 * func_80006E2C
 * VRAM 0x80006E2C | ROM 0x7A2C | size 0x50
 * asm: asm/nonmatchings/main/func_80006E2C.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: its definition takes the block's address as a pointer (u8 *), so it is declared with a pointer here. */
void releaseHeapBlock(void *);
#else
s32 releaseHeapBlock(s32);
#endif

/* Release the two heap allocations referenced by arg0 (+0 and +4) and clear the
 * pointers. */
#ifdef TARGET_PC
/* PC: arg0 is a picture pair (common.h's Nw2TexPair), whose two addresses are 8-byte pointers at +0 and +8, not
 * 4-byte words at +0 and +4. The PC frees and clears the same two fields by name, as pointers. */
void func_80006E2C(void *arg0) {
    Nw2TexPair *pair = arg0;

    if (pair->img != NULL) {
        releaseHeapBlock(pair->img);
        pair->img = NULL;
    }
    if (pair->pal != NULL) {
        releaseHeapBlock(pair->pal);
        pair->pal = NULL;
    }
}
#else
void func_80006E2C(void *arg0) {
    s32 a;
    s32 b;

    a = *(s32 *)((s8 *)arg0 + 0);
    if (a != 0) {
        releaseHeapBlock(a);
        *(s32 *)((s8 *)arg0 + 0) = 0;
    }
    b = *(s32 *)((s8 *)arg0 + 4);
    if (b != 0) {
        releaseHeapBlock(b);
        *(s32 *)((s8 *)arg0 + 4) = 0;
    }
}
#endif
