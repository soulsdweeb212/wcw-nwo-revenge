#include "common.h"

extern Nw2TimerQueueEntry *g_80038820;
extern u32 D_8007BD60;
u32 func_80026AF0(void);
void func_80028100(u32);
void programTimerCountdown(u64);
s32 func_8001CAC0(void *,u32,s32);
u64 insertTimer(Nw2TimerQueueEntry *);
void handleTimerInterrupt(void) {
 Nw2TimerQueueEntry *t;
 u32 count, old;
 u64 elapsed;
 if (g_80038820->next == g_80038820) return;
 for (;;) {
  t=g_80038820->next;
  if(t==g_80038820) {func_80028100(0); D_8007BD60=0; return;}
  count=func_80026AF0(); old=D_8007BD60; D_8007BD60=count;
  elapsed=(u32)(count-old);
  if(t->value>elapsed) {t->value-=elapsed; programTimerCountdown(t->value); return;}
  t->prev->next=t->next; t->next->prev=t->prev;
  t->next=NULL; t->prev=NULL;
  if(t->queue) func_8001CAC0(t->queue,t->message,0);
  if(t->interval) {t->value=t->interval; insertTimer(t);}
 }
}
