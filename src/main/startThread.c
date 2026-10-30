/* @header
 * startThread  (originally func_8001CD20)
 * VRAM 0x8001CD20 | ROM 0x1D920 | size 0x118
 * asm: asm/nonmatchings/main/func_8001CD20.s
 */
#include "common.h"

typedef struct ThreadCD20 { struct ThreadCD20 *next; s32 priority; struct ThreadCD20 **queue; struct ThreadCD20 *tlnext; u16 state; } ThreadCD20;
extern ThreadCD20 *D_80037248, *D_80037250;
s32 nw2DisableInterrupts(void);
void nw2RestoreInterrupts(s32);
void func_800266B4(ThreadCD20 **, ThreadCD20 *);
ThreadCD20 *func_800266FC(ThreadCD20 **);
void func_8002670C(void);
void func_800265AC(ThreadCD20 **);
/* Makes `thread` runnable: interrupts off, then depending on its state it is
 * queued on the runnable list (state 2) or moved off its wait queue (state 8).
 * Finally it either starts the scheduler (no current thread) or preempts the
 * current thread when `thread` has higher priority. */
void startThread(ThreadCD20 *thread) {
 s32 mask=nw2DisableInterrupts();
 switch(thread->state) {
 case 8: thread->state=2; func_800266B4(&D_80037248,thread); break;
 case 1:
 if(thread->queue==NULL || thread->queue==&D_80037248) { thread->state=2; func_800266B4(&D_80037248,thread); }
 else {thread->state=8;func_800266B4(thread->queue,thread);func_800266B4(&D_80037248,func_800266FC(thread->queue));}
 break;
 }
 if(D_80037250==NULL) func_8002670C();
 else if(D_80037250->priority<D_80037248->priority) {D_80037250->state=2;func_800265AC(&D_80037248);}
 nw2RestoreInterrupts(mask);
}
