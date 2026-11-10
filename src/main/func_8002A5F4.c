/* @header
 * func_8002A5F4
 * VRAM 0x8002A5F4 | ROM 0x2B1F4 | size 0x64
 * asm: asm/nonmatchings/main/func_8002A5F4.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: entry is an entry of the resource-name cache (Nw2ResourceEntryHashed, common.h), whose key is as wide as a
 * pointer on PC (port.h's ResKey), so the allocation follows at +8 instead of +4. D_8007FC3C, the address of the 40
 * name buffers, and the allocation are addresses, which a u32 or s32 would cut in half. A key that points into the
 * name buffers is compared as a whole address, and the buffer's key0, key1 and first byte (+0x40, +0x44 and +0 on
 * both) are cleared by name. */
void releaseHeapBlock(void *);
extern Nw2KeyedBufferEntry *D_8007FC3C;

void func_8002A5F4(void *entry) {
    Nw2ResourceEntryHashed *e = entry;
    ResKey key = e->key;

    if (key != 0) {
        if (key >= (ResKey)D_8007FC3C && key < (ResKey)(D_8007FC3C + 40)) {
            Nw2KeyedBufferEntry *name = (Nw2KeyedBufferEntry *)key;
            name->key0 = 0;
            name->key1 = 0;
            name->buffer[0] = 0;
        }
        releaseHeapBlock(e->allocation);
        e->key = 0;
    }
}
#else
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
#endif
