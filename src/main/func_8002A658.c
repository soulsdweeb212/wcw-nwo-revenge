#include "common.h"

s32 releaseHeapBlock(s32);
extern void *D_8007FC34;

/* Free every resource entry whose key is -1 (the unused marker) and clear the key;
 * walks the 128 entries of the table at D_8007FC34, stride 0x18. */
void func_8002A658(void) {
    s32 i;
    u8 *entry;

    entry = D_8007FC34;
    i = 0;
    do {
        i += 1;
        if (*(s32 *)(entry + 0) == -1) {
            releaseHeapBlock(*(s32 *)(entry + 4));
            *(s32 *)(entry + 0) = 0;
        }
        entry += 0x18;
    } while (i < 0x80);
}
