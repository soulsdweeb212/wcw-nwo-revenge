/* @header
 * osCreateMesgQueue  (originally func_8001C890)
 * VRAM 0x8001C890 | ROM 0x1D490 | size 0x24
 * asm: asm/nonmatchings/main/osCreateMesgQueue.s
 */
/* SDK: libultra 2.0I, ultralib src/os/createmesgqueue.c (same code as the SDK source). */
#include "common.h"

extern s32 D_80037240;

/* Message-queue header (same layout documented for osSendMesg in context.h):
 * +0 receive wait list, +4 send wait list, +8 count, +C read index,
 * +10 capacity, +14 entry array. */
typedef struct {
    s32 *receiveWaitList;
    s32 *sendWaitList;
    s32 count;
    s32 readIndex;
    s32 capacity;
    s32 *entries;
} Nw2MessageQueue;

/* Initialize a message queue: both wait lists point at the shared D_80037240
 * head, count and read index are cleared, and the caller supplies the entry
 * array and capacity. */
void osCreateMesgQueue(Nw2MessageQueue *queue, s32 *entries, s32 capacity) {
    queue->receiveWaitList = &D_80037240;
    queue->sendWaitList = &D_80037240;
    queue->count = 0;
    queue->readIndex = 0;
    queue->capacity = capacity;
    queue->entries = entries;
}
