#include "common.h"

s32 func_8001C990(void *, s32 *, s32);
s32 func_8001CAC0(void *, void *, s32);

/* Listener link: the next listener in the chain and the queue to notify. */
typedef struct E0CLink { struct E0CLink *next; void *queue; } E0CLink;

/* Event loop for an object: waits on its own queue (object+0x40) for a message.
 * Message 0x29A increments the object's counter (object+0x27C) and re-sends the
 * object to every listener queue (list head at object+0x260); message 0x29D sends
 * object+0x20 to every listener queue instead. */
void func_80000E0C(u8 *object) {
    s32 msg;
    E0CLink *listener;
    for (;;) {
        func_8001C990(object + 0x40, &msg, 1);
        switch (msg) {
        case 0x29A:
            listener = *(E0CLink **)(object + 0x260);
            (*(s32 *)(object + 0x27C))++;
            while (listener) {
                func_8001CAC0(listener->queue, object, 0);
                listener = listener->next;
            }
            break;
        case 0x29D:
            listener = *(E0CLink **)(object + 0x260);
            while (listener) {
                func_8001CAC0(listener->queue, object + 0x20, 0);
                listener = listener->next;
            }
            break;
        }
    }
}
