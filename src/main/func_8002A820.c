/* @header
 * func_8002A820
 * VRAM 0x8002A820 | ROM 0x2B420 | size 0x150
 * asm: asm/nonmatchings/main/func_8002A820.s
 */
#include "common.h"

/* func_8002A820: invalidates a resource cache entry. It hashes the key string,
 * then looks for an exact (key, variant, hash) match or, failing that, a free
 * slot; if the matching key rings into the D_8007FC3C keyed-buffer pool it
 * clears that buffer header (u32 +0, +0x40, +0x44) and marks the entry's key
 * -1. Returns -1 when an existing entry was invalidated, 0 for a free slot or
 * no match. */
extern Nw2ResourceEntryHashed *D_8007FC34;
extern u8 *D_8007FC3C;

static __inline__ void checksumA820(Nw2ResourceEntryHashed *q) {
    u8 *p = (u8 *)q->key;
    q->hash.h.length = 0;
    q->hash.h.sum = 0;
    if (!((u32)p & 0x40000000)) {
        while (*p) {
            q->hash.h.sum += *p++ << (q->hash.h.length & 7);
            q->hash.h.length++;
        }
    }
}

s32 func_8002A820(u8 *key, s32 arg1) {
    Nw2ResourceEntryHashed temp;
    Nw2ResourceEntryHashed *entry, *found;
    u32 variant = arg1 & 0xFFFF;
    s32 i;
    u32 value;

    temp.key = (u32)key;
    checksumA820(&temp);
    entry = D_8007FC34;
    for (i = 0; i < 128; i++, entry++) {
        if (entry->key == (u32)key && entry->variant == variant && entry->hash.word == temp.hash.word) {
            found = entry;
            goto got;
        }
    }
    i = 0;
    entry = D_8007FC34;
    for (; i < 128; i++, entry++) {
        if (!entry->key) {
            entry->hash.h.length = temp.hash.h.length;
            found = entry;
            found->hash.h.sum = temp.hash.h.sum;
            goto got;
        }
    }
    found = 0;
got:
    if (!found) {
        return 0;
    }
    value = found->key;
    if (value) {
        if (value >= (u32)D_8007FC3C && value < (u32)(D_8007FC3C + 0xB40)) {
            *(u32 *)(value + 0x40) = 0;
            *(u32 *)(value + 0x44) = 0;
            *(u8 *)value = 0;
        }
        found->key = -1;
        return -1;
    }
    return 0;
}
