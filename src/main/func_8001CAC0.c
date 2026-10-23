#include "common.h"

typedef struct { s32 *list; s32 *sendList; s32 count, index, limit; s32 *entries; } Nw2SendQueue;
typedef struct { s32 next, priority; s32 *queue, *threadNext; u16 state; } Nw2Thread;
extern void *D_80037250;
s32 nw2DisableInterrupts(void);
void nw2RestoreInterrupts(s32);
void func_800265AC(void *);
void *func_800266FC(void *);
void startThread(void *);
/* Send a message to the queue with interrupt protection: when the queue is full
 * either fail (wait != 1) or block the running thread (state 8) and yield its
 * send list until space frees up; otherwise append the message at the tail
 * slot (index + count) % limit and wake a waiting receiver. Returns 0 on
 * success, -1 when non-blocking and full. */
s32 func_8001CAC0(Nw2SendQueue *q, s32 msg, s32 wait) {
    s32 state = nw2DisableInterrupts();
    while (q->count >= q->limit) {
        if (wait != 1) { nw2RestoreInterrupts(state); return -1; }
        ((Nw2Thread *)D_80037250)->state = 8;
        func_800265AC(&q->sendList);
    }
    q->entries[(q->index + q->count) % q->limit] = msg;
    q->count++;
    if (*q->list != 0) startThread(func_800266FC(q));
    nw2RestoreInterrupts(state);
    return 0;
}
