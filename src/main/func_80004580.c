#include "common.h"

typedef struct Nw2ResourceDesc {
    void *p0;
    void *p1;
    s32 size;
    s32 len;
} Nw2ResourceDesc;

typedef struct Nw2ResNode {
    struct Nw2ResNode *next;
    void *data;
    u16 id;
    u16 count;
} Nw2ResNode;

extern Nw2ResNode *nw2ResourceCacheHead;
void *allocateHeap(s32);
void lookupResourceDescriptor(void *, s32);
void func_80003684(void *, s32, void *);

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
        node = allocateHeap(0xC);
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
