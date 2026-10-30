/* @header
 * releaseResourcePool  (originally func_8002AAFC)
 * VRAM 0x8002AAFC | ROM 0x2B6FC | size 0xFC
 * asm: asm/nonmatchings/main/func_8002AAFC.s
 */
#include "common.h"

extern u32 D_80064AD0, D_80064AD4, D_8007FC34, D_8007FC3C;
void releaseHeapBlock(u32);

/* Release the 128-entry resource pool at D_8007FC34 (stride 0x18): free the
 * object of every slot flagged -1 and clear the slot; then for every occupied
 * slot, clear the two header fields of objects that live inside the D_8007FC3C
 * buffer and free the slot's object; finally free the pool and its buffers. */
void releaseResourcePool(void) {
    s32 i, offset, count;
    u32 slot = D_8007FC34;
    for (i = 0; i < 128; i++, slot += 0x18) {
        if (*(s32 *)slot == -1) { releaseHeapBlock(*(u32 *)(slot + 4)); *(u32 *)slot = 0; }
    }
    count = 0; offset = 0;
    do {
        u32 t = offset + D_8007FC34;
        u32 q = *(u32 *)t;
        slot = t;
        if (q) {
            if (q >= D_8007FC3C && q < D_8007FC3C + 0xB40) { *(s32 *)(q + 0x40) = 0; *(s32 *)(q + 0x44) = 0; *(u8 *)q = 0; }
            releaseHeapBlock(*(u32 *)(slot + 4)); *(u32 *)slot = 0;
        }
        count++; offset += 0x18;
    } while (count < 128);
    releaseHeapBlock(D_80064AD0); releaseHeapBlock(D_80064AD4); releaseHeapBlock(D_8007FC3C); releaseHeapBlock(D_8007FC34);
}
