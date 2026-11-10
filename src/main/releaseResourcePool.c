/* @header
 * releaseResourcePool  (originally func_8002AAFC)
 * VRAM 0x8002AAFC | ROM 0x2B6FC | size 0xFC
 * asm: asm/nonmatchings/main/releaseResourcePool.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the pool D_8007FC34, the name buffers D_8007FC3C, the resources D_80064AD0 and D_80064AD4 and each entry's
 * allocation are addresses, which a u32 would cut in half; releaseHeapBlock takes them as pointers. The pool's
 * entries are Nw2ResourceEntryHashed (common.h), 0x20 bytes on PC because the key is as wide as a pointer (port.h's
 * ResKey), so the PC version steps through them as entries instead of by 0x18 bytes. A key that points into the 40
 * name buffers (Nw2KeyedBufferEntry, the same 0x48 bytes on both) is compared as a whole address, and the buffer's
 * key0, key1 and first byte (+0x40, +0x44 and +0 on both) are cleared by name. */
extern void *D_80064AD0, *D_80064AD4;
extern Nw2ResourceEntryHashed *D_8007FC34;
extern Nw2KeyedBufferEntry *D_8007FC3C;
void releaseHeapBlock(void *);

void releaseResourcePool(void) {
    s32 i;
    Nw2ResourceEntryHashed *slot = D_8007FC34;
    for (i = 0; i < 128; i++, slot++) {
        if (slot->key == (ResKey)-1) { releaseHeapBlock(slot->allocation); slot->key = 0; }
    }
    slot = D_8007FC34;
    for (i = 0; i < 128; i++, slot++) {
        ResKey q = slot->key;
        if (q) {
            if (q >= (ResKey)D_8007FC3C && q < (ResKey)(D_8007FC3C + 40)) {
                Nw2KeyedBufferEntry *name = (Nw2KeyedBufferEntry *)q;
                name->key0 = 0; name->key1 = 0; name->buffer[0] = 0;
            }
            releaseHeapBlock(slot->allocation); slot->key = 0;
        }
    }
    releaseHeapBlock(D_80064AD0); releaseHeapBlock(D_80064AD4);
    releaseHeapBlock(D_8007FC3C); releaseHeapBlock(D_8007FC34);
}
#else
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
#endif
