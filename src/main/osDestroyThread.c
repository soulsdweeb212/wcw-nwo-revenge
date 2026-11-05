/* @header
 * osDestroyThread  (originally func_80026CE0)
 * VRAM 0x80026CE0 | ROM 0x278E0 | size 0xCC
 * asm: asm/nonmatchings/main/osDestroyThread.s
 */
/* SDK: libultra 2.0I, ultralib src/os/destroythread.c (same code as the SDK source). */
#include "common.h"

typedef struct Node26 {
    s32 f0;
    s32 f4;
    void *owner;
    struct Node26 *next;
    u16 type;
} Node26;

extern Node26 *D_8003724C;
extern Node26 *D_80037250;

s32 __osDisableInt(void);
void __osRestoreInt(s32);
void __osDispatchThread(void);
void __osDequeueThread(void *, void *);

/* Remove arg0 from the interrupt-protected object list D_8003724C. A NULL arg0
 * means the default node D_80037250; a node whose type isn't 1 is first detached
 * from its owner. When the default node is removed, run __osDispatchThread. */
void osDestroyThread(Node26 *arg0) {
    Node26 *node = arg0;
    s32 state = __osDisableInt();
    Node26 *prev;
    Node26 *cur;

    if (node == NULL) {
        node = D_80037250;
    } else if (node->type != 1) {
        __osDequeueThread(node->owner, node);
    }

    {
        Node26 *head = D_8003724C;
        if (head == node) {
            D_8003724C = node->next;
        } else {
            prev = head;
            cur = prev->next;
            while (cur != NULL) {
                if (cur == node) {
                    prev->next = node->next;
                    break;
                }
                prev = cur;
                cur = cur->next;
            }
        }
    }

    if (node == D_80037250) {
        __osDispatchThread();
    }
    __osRestoreInt(state);
}
