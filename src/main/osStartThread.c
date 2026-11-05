/* @header
 * osStartThread  (originally func_8001CD20)
 * VRAM 0x8001CD20 | ROM 0x1D920 | size 0x118
 * asm: asm/nonmatchings/main/osStartThread.s
 */
/* SDK: libultra 2.0I, ultralib src/os/startthread.c (same code as the SDK source). */
#include "common.h"

typedef struct ThreadCD20 { struct ThreadCD20 *next; s32 priority; struct ThreadCD20 **queue; struct ThreadCD20 *tlnext; u16 state; } ThreadCD20;
extern ThreadCD20 *D_80037248, *D_80037250;
s32 __osDisableInt(void);
void __osRestoreInt(s32);
void __osEnqueueThread(ThreadCD20 **, ThreadCD20 *);
ThreadCD20 *__osPopThread(ThreadCD20 **);
void __osDispatchThread(void);
void __osEnqueueAndYield(ThreadCD20 **);
/* Makes `thread` runnable: interrupts off, then depending on its state it is
 * queued on the runnable list (state 2) or moved off its wait queue (state 8).
 * Finally it either starts the scheduler (no current thread) or preempts the
 * current thread when `thread` has higher priority. */
void osStartThread(ThreadCD20 *thread) {
    s32 mask=__osDisableInt();
    switch(thread->state) {
    case 8: thread->state=2; __osEnqueueThread(&D_80037248,thread); break;
    case 1:
        if(thread->queue==NULL || thread->queue==&D_80037248) { thread->state=2; __osEnqueueThread(&D_80037248,thread); }
        else {thread->state=8;__osEnqueueThread(thread->queue,thread);__osEnqueueThread(&D_80037248,__osPopThread(thread->queue));}
        break;
    }
    if(D_80037250==NULL) __osDispatchThread();
    else if(D_80037250->priority<D_80037248->priority) {D_80037250->state=2;__osEnqueueAndYield(&D_80037248);}
    __osRestoreInt(mask);
}
