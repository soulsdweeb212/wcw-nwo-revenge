/* @header
 * osJamMesg  (originally func_80026E60)
 * VRAM 0x80026E60 | ROM 0x27A60 | size 0x134
 * asm: asm/nonmatchings/main/osJamMesg.s
 */
/* SDK: libultra 2.0I, ultralib src/os/jammesg.c (same code as the SDK source). */
#include "common.h"

typedef struct { s32 *list; s32 *sendList; s32 count, index, limit; s32 *entries; } Nw2SendQueue;
typedef struct { s32 next, priority; s32 *queue, *threadNext; u16 state; } Nw2Thread;
extern void *D_80037250;
s32 __osDisableInt(void);
void __osRestoreInt(s32);
void __osEnqueueAndYield(void *);
void *__osPopThread(void *);
void osStartThread(void *);
/* Send a message to the queue with interrupt protection: when the queue is full
 * either fail (wait != 1) or block the running thread (state 8) and yield its
 * send list until space frees up; otherwise append the message at the tail
 * (index = (index + limit - 1) % limit) and wake a waiting receiver. Returns 0
 * on success, -1 when non-blocking and full. */
s32 osJamMesg(Nw2SendQueue *q, s32 msg, s32 wait) {
    s32 state = __osDisableInt();
    while (q->count >= q->limit) {
        if (wait != 1) { __osRestoreInt(state); return -1; }
        ((Nw2Thread *)D_80037250)->state = 8;
        __osEnqueueAndYield(&q->sendList);
    }
    q->index = (q->index + q->limit - 1) % q->limit;
    q->entries[q->index] = msg;
    q->count++;
    if (*q->list != 0) osStartThread(__osPopThread(q));
    __osRestoreInt(state);
    return 0;
}
