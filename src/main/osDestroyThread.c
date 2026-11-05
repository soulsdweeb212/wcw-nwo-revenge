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

extern Node26 *__osActiveQueue;
extern Node26 *__osRunningThread;

s32 __osDisableInt(void);
void __osRestoreInt(s32);
void __osDispatchThread(void);
void __osDequeueThread(void *, void *);

/* Remove arg0 from the interrupt-protected object list __osActiveQueue. A NULL arg0
 * means the default node __osRunningThread; a node whose type isn't 1 is first detached
 * from its owner. When the default node is removed, run __osDispatchThread. */
void osDestroyThread(Node26 *arg0) {
    Node26 *node = arg0;
    s32 state = __osDisableInt();
    Node26 *prev;
    Node26 *cur;

    if (node == NULL) {
        node = __osRunningThread;
    } else if (node->type != 1) {
        __osDequeueThread(node->owner, node);
    }

    {
        Node26 *head = __osActiveQueue;
        if (head == node) {
            __osActiveQueue = node->next;
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

    if (node == __osRunningThread) {
        __osDispatchThread();
    }
    __osRestoreInt(state);
}
