/* @header
 * func_8002A2FC
 * VRAM 0x8002A2FC | ROM 0x2AEFC | size 0x2F8
 * asm: asm/nonmatchings/main/func_8002A2FC.s
 */
#include "common.h"

extern Nw2ResourceEntryHashed *D_8007FC34;
void func_80028F3C(Nw2ResourceEntryHashed *, s32);
void func_800295B4(Nw2ResourceEntryHashed *, s32);
void func_80029A24(void *, s32, s32, void *);
void fillNibblePixelLevels(Nw2ResourceEntryHashed *);
void slantNibbleBitmapRows(Nw2ResourceEntryHashed *, s32);
void func_8002A1C4(Nw2ResourceEntryHashed *);
void bzero(void *, s32);
void *allocateHeap(u32);

#ifdef TARGET_PC
/* PC: the key of the resource-name cache is as wide as a pointer (port.h's ResKey), so an entry is 0x20 bytes, and the
 * function takes its key as a ResKey. Its local copy of an entry is the entry's PC layout (Nw2ResourceEntryHashed in
 * common.h). The PC tells an id from the address of a name by port.h's RES_KEY_IS_ID, because a PC address can have
 * bit 0x40000000 set, and reads the allocation and the sizes in reserved by name, where the N64 code reads the entry
 * at +4, +8, +0xC and +0xE. */
typedef Nw2ResourceEntryHashed Nw2HashRec18;
#else
typedef struct {
    u32 key;
    void *allocation;
    u8 reserved[10];
    u16 variant;
    union { struct { u16 length, sum; } h; u32 word; } hash;
} Nw2HashRec18;
#endif

/* Look up a resource in the 0x80-entry cache by (key, variant, string hash),
 * or claim a free entry and build it. String keys probe and hash their bytes;
 * bit 0x40000000 keys point at a 0x20-byte name buffer instead. The returned
 * entry owns its allocation and is post-processed per the option bits. */
#ifdef TARGET_PC
void *func_8002A2FC(ResKey key, u16 flags) { /* PC: the key as wide as a pointer, as above */
#else
void *func_8002A2FC(u32 key, u16 flags) {
#endif
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
#ifdef TARGET_PC
    if (!RES_KEY_IS_ID(key) && *str != 0) { /* PC: the id test of port.h, as above */
#else
    if (!(key & 0x40000000) && *str != 0) {
#endif
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
#ifdef TARGET_PC
    /* PC: an id is told by port.h's test; the entry's key holds the name buffer's address, which 32 bits would cut. */
    if (RES_KEY_IS_ID(key)) {
        entry->key = RES_KEY_NAME(nameBuf);
#else
    if (key & 0x40000000) {
        entry->key = (u32)nameBuf;
#endif
        func_80029A24(nameBuf, key & 0x3FFFFF, flags, str);
    } else {
        entry->key = key;
    }
    entry->variant = flags;
    func_80028F3C(entry, flags);
#ifdef TARGET_PC
    /* PC: the allocation's size is the u32 at the start of reserved (the entry's +8 on N64). */
    allocation = allocateHeap(*(u32 *)entry->reserved);
#else
    allocation = allocateHeap(*(u32 *)((u8 *)entry + 8));
#endif
    entry->allocation = allocation;
    if (allocation == NULL) {
        entry->key = 0;
        return NULL;
    }
#ifdef TARGET_PC
    bzero(allocation, *(u32 *)entry->reserved); /* PC: the size, as above */
#else
    bzero(allocation, *(u32 *)((u8 *)entry + 8));
#endif
    func_800295B4(entry, flags);
#ifdef TARGET_PC
    if (RES_KEY_IS_ID(key)) { /* PC: the id test of port.h */
#else
    if (key & 0x40000000) {
#endif
        entry->key = key;
    }
    if (flags & 1) {
        slantNibbleBitmapRows(entry, flags);
    }
    if (flags & 4) {
#ifdef TARGET_PC
        /* PC: the entry's fields by name: the allocation (+4 on N64), and in reserved the row count (+0xE on N64) and
         * the row width (+0xC on N64). */
        pix = entry->allocation;
        row = 0;
        while (row < *(s16 *)(entry->reserved + 6)) {
            col = 0;
            while (col < (s16)*(u16 *)(entry->reserved + 4) / 2) {
                if (col < (s16)*(u16 *)(entry->reserved + 4) / 2 - 1) {
#else
        pix = *(u8 **)((u8 *)entry + 4);
        row = 0;
        while (row < *(s16 *)((u8 *)entry + 0xE)) {
            col = 0;
            while (col < (s16)*(u16 *)((u8 *)entry + 0xC) / 2) {
                if (col < (s16)*(u16 *)((u8 *)entry + 0xC) / 2 - 1) {
#endif
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
