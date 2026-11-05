/* @header
 * __scMain  (originally func_80000E0C)
 * VRAM 0x80000E0C | ROM 0x1A0C | size 0xD4
 * asm: asm/nonmatchings/main/__scMain.s
 */
/* SDK: libultra 2.0I, ultralib src/sched/sched.c (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

s32 osRecvMesg(void *, s32 *, s32);
s32 osSendMesg(void *, void *, s32);

/* Listener link: the next listener in the chain and the queue to notify. */
typedef struct E0CLink { struct E0CLink *next; void *queue; } E0CLink;

/* Event loop for an object: waits on its own queue (object+0x40) for a message.
 * Message 0x29A increments the object's counter (object+0x27C) and re-sends the
 * object to every listener queue (list head at object+0x260); message 0x29D sends
 * object+0x20 to every listener queue instead. */
void __scMain(u8 *object) {
    s32 msg;
    E0CLink *listener;
    for (;;) {
        osRecvMesg(object + 0x40, &msg, 1);
        switch (msg) {
        case 0x29A:
            listener = *(E0CLink **)(object + 0x260);
            (*(s32 *)(object + 0x27C))++;
            while (listener) {
                osSendMesg(listener->queue, object, 0);
                listener = listener->next;
            }
            break;
        case 0x29D:
            listener = *(E0CLink **)(object + 0x260);
            while (listener) {
                osSendMesg(listener->queue, object + 0x20, 0);
                listener = listener->next;
            }
            break;
        }
    }
}
