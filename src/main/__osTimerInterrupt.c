/* @header
 * __osTimerInterrupt  (originally func_80027094)
 * VRAM 0x80027094 | ROM 0x27C94 | size 0x13C
 * asm: asm/nonmatchings/main/__osTimerInterrupt.s
 */
/* SDK: libultra 2.0I, ultralib src/os/timerintr.c (same code as the SDK source). */
#include "common.h"

extern Nw2TimerQueueEntry *g_80038820;
extern u32 D_8007BD60;
u32 osGetCount(void);
void __osSetCompare(u32);
void __osSetTimerIntr(u64);
s32 osSendMesg(void *,u32,s32);
u64 __osInsertTimer(Nw2TimerQueueEntry *);
void __osTimerInterrupt(void) {
    Nw2TimerQueueEntry *t;
    u32 count, old;
    u64 elapsed;
    if (g_80038820->next == g_80038820) return;
    for (;;) {
        t=g_80038820->next;
        if(t==g_80038820) {__osSetCompare(0); D_8007BD60=0; return;}
        count=osGetCount(); old=D_8007BD60; D_8007BD60=count;
        elapsed=(u32)(count-old);
        if(t->value>elapsed) {t->value-=elapsed; __osSetTimerIntr(t->value); return;}
        t->prev->next=t->next; t->next->prev=t->prev;
        t->next=NULL; t->prev=NULL;
        if(t->queue) osSendMesg(t->queue,t->message,0);
        if(t->interval) {t->value=t->interval; __osInsertTimer(t);}
    }
}
