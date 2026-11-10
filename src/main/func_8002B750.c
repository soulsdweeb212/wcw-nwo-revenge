/* @header
 * func_8002B750
 * VRAM 0x8002B750 | ROM 0x2C350 | size 0x40
 * asm: asm/nonmatchings/main/func_8002B750.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_8003A594 holds the address of the wrestler-name table (func_8002BAB8 declares it u8 *), which an s32 would cut
 * to its lower half. */
extern u8 *D_8003A594;
#else
extern s32 D_8003A594;
#endif

s32 func_8002B7E0(s32, s32);
void bcopy(void *, void *, s32);
void func_8002BAB8(void);
#ifdef TARGET_PC
/* PC: allocateHeap returns a pointer (its definition is void *allocateHeap(u32)). Declared to return s32, the call
 * would keep only the lower 32 bits of the address it returns. */
void *allocateHeap(u32);
#else
s32 allocateHeap(s32);
#endif

/* Lazily allocates the 0x3480-byte wrestler-name table and builds it. Returns 1
 * when it was just created. */
s32 func_8002B750(void) {
    if (D_8003A594 == 0) {
        D_8003A594 = allocateHeap(0x3480);
        func_8002BAB8();
        return 1;
    }
    return 0;
}
