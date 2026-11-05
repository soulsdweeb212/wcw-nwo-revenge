/* @header
 * osSetThreadPri  (originally func_8001CC50)
 * VRAM 0x8001CC50 | ROM 0x1D850 | size 0xC8
 * asm: asm/nonmatchings/main/osSetThreadPri.s
 */
/* SDK: libultra 2.0I, ultralib src/os/setthreadpri.c (same code as the SDK source). */
#include "common.h"

typedef struct Obj {
    s32 f0;
    s32 f4;
    s32 f8;
    s16 fC;
    s16 fE;
    u16 f10;
} Obj;

extern Obj *__osRunQueue;
extern Obj *__osRunningThread;
extern s32 __osDisableInt(void);
extern void __osRestoreInt(s32);
extern void __osDequeueThread(s32, void *);
extern void __osEnqueueThread(s32, void *);
extern void __osEnqueueAndYield(void *);

/* Sets a thread's priority (arg0==NULL means the current thread). If it changed,
 * re-queues the thread on its wait queue (unless current or state 1) and
 * preempts the current thread when the runnable queue now outranks it. Runs
 * with interrupts disabled. */
void osSetThreadPri(Obj *arg0, s32 arg1) {
    s32 s1 = arg1;
    Obj *s0 = arg0;
    s32 s2 = __osDisableInt();

    if (s0 == NULL)
        s0 = __osRunningThread;
    if (s0->f4 != s1) {
        s0->f4 = s1;
        if (s0 != __osRunningThread && s0->f10 != 1) {
            __osDequeueThread(s0->f8, s0);
            __osEnqueueThread(s0->f8, s0);
        }
        if (__osRunningThread->f4 < __osRunQueue->f4) {
            __osRunningThread->f10 = 2;
            __osEnqueueAndYield(&__osRunQueue);
        }
    }
    __osRestoreInt(s2);
}
