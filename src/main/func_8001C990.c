/* @header
 * func_8001C990
 * VRAM 0x8001C990 | ROM 0x1D590 | size 0x124
 * asm: asm/nonmatchings/main/func_8001C990.s
 */
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
s32 nw2DisableInterrupts(void);
void nw2RestoreInterrupts(s32);
void func_800265AC(void *);
void *func_800266FC(s32 **);
void startThread(void *);

s32 func_8001C990(Nw2MsgQueue *q, s32 *msg, s32 wait) {
    s32 state = nw2DisableInterrupts();

    while (q->count == 0) {
        if (wait == 0) {
            nw2RestoreInterrupts(state);
            return -1;
        }
        ((Nw2Thread *)D_80037250)->state = 8;
        func_800265AC(q);
    }
    if (msg != NULL) {
        *msg = q->entries[q->index];
    }
    q->index = (q->index + 1) % q->limit;
    q->count--;
    if (*q->list != 0) {
        startThread(func_800266FC(&q->list));
    }
    nw2RestoreInterrupts(state);
    return 0;
}
