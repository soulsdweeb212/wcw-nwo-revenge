/* @header
 * func_80004580
 * VRAM 0x80004580 | ROM 0x5180 | size 0xD8
 * asm: asm/nonmatchings/main/func_80004580.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the loader writes the 16-byte ResDesc of port.h. With two pointers, the N64 layout below would be 24 bytes on a
 * 64-bit PC, and .size would be read from the wrong place. */
typedef ResDesc Nw2ResourceDesc;
#else
typedef struct Nw2ResourceDesc {
    void *p0;
    void *p1;
    s32 size;
    s32 len;
} Nw2ResourceDesc;
#endif

typedef struct Nw2ResNode {
    struct Nw2ResNode *next;
    void *data;
    u16 id;
    u16 count;
} Nw2ResNode;

extern Nw2ResNode *nw2ResourceCacheHead;
void *allocateHeap(s32);
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void lookupResourceDescriptor(void *, s32);
void func_80003684(void *, s32, void *);
#endif

/* Returns the cached data buffer for resource arg0, creating (and decoding) a
 * cache node for it on first use and bumping its reference count. */
void *func_80004580(s16 arg0) {
    Nw2ResNode *node;
    Nw2ResNode *prev;
    Nw2ResourceDesc d1;
    Nw2ResourceDesc d2;
    void *buf;

    node = nw2ResourceCacheHead;
    prev = NULL;
    while (node != NULL && node->id != (u16)arg0) {
        prev = node;
        node = node->next;
    }
    if (node == NULL) {
#ifdef TARGET_PC
        /* PC: the node holds two 8-byte pointers, so it is sizeof(Nw2ResNode) = 0x18 bytes, not 0xC. */
        node = allocateHeap(sizeof(Nw2ResNode));
#else
        node = allocateHeap(0xC);
#endif
        if (prev == NULL) {
            nw2ResourceCacheHead = node;
        } else {
            prev->next = node;
        }
        node->next = NULL;
        lookupResourceDescriptor(&d1, (u16)arg0);
        buf = allocateHeap(d1.size);
        node->data = buf;
        func_80003684(&d2, (u16)arg0, buf);
        node->id = arg0;
        node->count = 0;
    }
    node->count++;
    return node->data;
}
