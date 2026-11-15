/* @header
 * func_8002A658
 * VRAM 0x8002A658 | ROM 0x2B258 | size 0x64
 * asm: asm/nonmatchings/main/func_8002A658.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the table and each entry's allocation are addresses, which an s32 would cut in half; releaseHeapBlock's
 * definition takes a u8 *. */
void releaseHeapBlock(u8 *);
extern Nw2ResourceEntryHashed *D_8007FC34;
#else
s32 releaseHeapBlock(s32);
extern void *D_8007FC34;
#endif

/* Free every resource entry whose key is -1 (the unused marker) and clear the key;
 * walks the 128 entries of the table at D_8007FC34, stride 0x18. */
#ifdef TARGET_PC
/* PC: the entries of the resource-name cache are Nw2ResourceEntryHashed (common.h), 0x20 bytes on PC because the key
 * is as wide as a pointer (port.h's ResKey), so the allocation follows at +8 instead of +4; the PC version steps
 * through them as entries instead of by 0x18 bytes. */
void func_8002A658(void) {
    s32 i;
    Nw2ResourceEntryHashed *entry = D_8007FC34;

    for (i = 0; i < 0x80; i++, entry++) {
        if (entry->key == (ResKey)-1) {
            releaseHeapBlock(entry->allocation);
            entry->key = 0;
        }
    }
}
#else
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
#endif
