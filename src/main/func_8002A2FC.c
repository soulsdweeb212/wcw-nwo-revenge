#include "common.h"

extern Nw2ResourceEntryHashed *D_8007FC34;
void func_80028F3C(Nw2ResourceEntryHashed *, s32);
void func_800295B4(Nw2ResourceEntryHashed *, s32);
void func_80029A24(void *, s32, s32, void *);
void fillNibblePixelLevels(Nw2ResourceEntryHashed *);
void slantNibbleBitmapRows(Nw2ResourceEntryHashed *, s32);
void func_8002A1C4(Nw2ResourceEntryHashed *);
void func_80021F60(void *, s32);
void *allocateHeap(u32);

typedef struct {
    u32 key;
    void *allocation;
    u8 reserved[10];
    u16 variant;
    union { struct { u16 length, sum; } h; u32 word; } hash;
} Nw2HashRec18;

/* Look up a resource in the 0x80-entry cache by (key, variant, string hash),
 * or claim a free entry and build it. String keys probe and hash their bytes;
 * bit 0x40000000 keys point at a 0x20-byte name buffer instead. The returned
 * entry owns its allocation and is post-processed per the option bits. */
void *func_8002A2FC(u32 key, u16 flags) {
    u32 variant = flags & 0xffff;
    u8 nameBuf[0x20];
    Nw2HashRec18 hash;
    Nw2HashRec18 *hp;
    u8 *str;
    Nw2ResourceEntryHashed *entry;
    Nw2ResourceEntryHashed *scan;
    s32 i;
    s32 row;
    s32 col;
    u8 *pix;
    u8 ch;
    u16 length;
    void *allocation;

    hp = &hash;
    hash.key = key;
    hp->hash.h.length = 0;
    hp->hash.h.sum = 0;
    str = (u8 *)key;
    if (!(key & 0x40000000) && *str != 0) {
        do {
            ch = *(volatile u8 *)str;
            str++;
            length = *(volatile u16 *)&hp->hash.h.length;
            length = length + 1;
            hp->hash.h.sum = hp->hash.h.sum + (ch << (*(volatile u16 *)&hp->hash.h.length & 7));
            hp->hash.h.length = length;
        } while (*str != 0);
    }
    scan = D_8007FC34;
    i = 0;
    for (; i < 0x80; i++, scan++) {
        if (scan->key == key && scan->variant == variant && scan->hash.word == hash.hash.word) {
            entry = scan;
            goto have;
        }
    }
    i = 0;
    scan = D_8007FC34;
    for (; i < 0x80; i++, scan++) {
        if (scan->key == 0) {
            scan->hash.h.length = hash.hash.h.length;
            scan->hash.h.sum = hash.hash.h.sum;
            entry = scan;
            goto have;
        }
    }
    entry = NULL;
have:
    if (entry == NULL) {
        return NULL;
    }
    if (entry->key != 0) {
        return entry;
    }
    if (key & 0x40000000) {
        entry->key = (u32)nameBuf;
        func_80029A24(nameBuf, key & 0x3FFFFF, flags, str);
    } else {
        entry->key = key;
    }
    entry->variant = flags;
    func_80028F3C(entry, flags);
    allocation = allocateHeap(*(u32 *)((u8 *)entry + 8));
    entry->allocation = allocation;
    if (allocation == NULL) {
        entry->key = 0;
        return NULL;
    }
    func_80021F60(allocation, *(u32 *)((u8 *)entry + 8));
    func_800295B4(entry, flags);
    if (key & 0x40000000) {
        entry->key = key;
    }
    if (flags & 1) {
        slantNibbleBitmapRows(entry, flags);
    }
    if (flags & 4) {
        pix = *(u8 **)((u8 *)entry + 4);
        row = 0;
        while (row < *(s16 *)((u8 *)entry + 0xE)) {
            col = 0;
            while (col < (s16)*(u16 *)((u8 *)entry + 0xC) / 2) {
                if (col < (s16)*(u16 *)((u8 *)entry + 0xC) / 2 - 1) {
                    u8 v = pix[0];
                    if (!(v & 0xF) && ((pix[1] & 0xF0) == 0xF0)) {
                        pix[0] = v | 0xF;
                    }
                }
                if (col != 0) {
                    if (pix[0] == 0xF) {
                        pix[0] = pix[0] | 0xF0;
                    }
                }
                col++;
                pix++;
            }
            row++;
        }
    }
    if (flags & 2) {
        fillNibblePixelLevels(entry);
    }
    if (flags & 8) {
        func_8002A1C4(entry);
    }
    return entry;
}
