/* @header
 * osRecvMesg  (originally func_8001C990)
 * VRAM 0x8001C990 | ROM 0x1D590 | size 0x124
 * asm: asm/nonmatchings/main/osRecvMesg.s
 */
/* SDK: libultra 2.0I, ultralib src/os/recvmesg.c (same code as the SDK source). */
#include "common.h"

typedef struct {
    s32 f0;
    s32 *list;
    s32 count;
    s32 index;
    s32 limit;
    s32 *entries;
} Nw2MsgQueue;

typedef struct {
    s32 next;
    s32 priority;
    s32 *queue;
    s32 *threadNext;
    u16 state;
} Nw2Thread;

extern void *D_80037250;
s32 __osDisableInt(void);
void __osRestoreInt(s32);
void __osEnqueueAndYield(void *);
void *__osPopThread(s32 **);
void osStartThread(void *);

s32 osRecvMesg(Nw2MsgQueue *q, s32 *msg, s32 wait) {
    s32 state = __osDisableInt();

    while (q->count == 0) {
        if (wait == 0) {
            __osRestoreInt(state);
            return -1;
        }
        ((Nw2Thread *)D_80037250)->state = 8;
        __osEnqueueAndYield(q);
    }
    if (msg != NULL) {
        *msg = q->entries[q->index];
    }
    q->index = (q->index + 1) % q->limit;
    q->count--;
    if (*q->list != 0) {
        osStartThread(__osPopThread(&q->list));
    }
    __osRestoreInt(state);
    return 0;
}
