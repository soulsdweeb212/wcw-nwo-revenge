#include "common.h"

typedef struct Nw2FreeNode {
    struct Nw2FreeNode *next;
} Nw2FreeNode;

/* Manager object behind D_80037510; a singly-linked free list hangs off +0x2C. */
typedef struct {
    u8 pad0[0x2C];
    Nw2FreeNode *freeList;
} Nw2Manager37510;

extern Nw2Manager37510 *D_80037510;

/* Pop the head of the D_80037510 free list and return it with its next pointer
 * cleared; returns NULL when the list is empty. */
void *func_800207BC(void) {
    Nw2FreeNode *node;
    void *result;

    node = D_80037510->freeList;
    result = NULL;
    if (node != NULL) {
        result = node;
        D_80037510->freeList = node->next;
        node->next = NULL;
    }
    return result;
}
