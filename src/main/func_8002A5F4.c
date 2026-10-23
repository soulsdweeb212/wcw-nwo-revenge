#include "common.h"

s32 releaseHeapBlock(s32);
extern u32 D_8007FC3C;

/* Free a keyed-buffer resource entry: if the key points into the keyed-buffer pool,
 * clear the referenced slot's +0x40/+0x44 fields and its byte 0, then release the
 * entry's allocation and clear the key. */
void func_8002A5F4(void *entry) {
    u32 key;

    key = *(u32 *)((s8 *)entry + 0);
    if (key != 0) {
        if ((key >= (u32) D_8007FC3C) && (key < (u32) (D_8007FC3C + 0xB40))) {
            *(s32 *)((s8 *)key + 0x40) = 0;
            *(s32 *)((s8 *)key + 0x44) = 0;
            *(s8 *)((s8 *)key + 0) = 0;
        }
        releaseHeapBlock(*(s32 *)((s8 *)entry + 4));
        *(u32 *)((s8 *)entry + 0) = 0U;
    }
}
