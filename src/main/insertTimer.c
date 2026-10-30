/* @header
 * insertTimer  (originally func_80027230)
 * VRAM 0x80027230 | ROM 0x27E30 | size 0x108
 * asm: asm/nonmatchings/main/insertTimer.s
 */
#include "common.h"

typedef struct Nw2Timer {struct Nw2Timer *next,*prev; u64 interval,value; void *mq; u32 msg;} Nw2Timer;
extern Nw2Timer *g_80038820;
u32 nw2DisableInterrupts(void);
void nw2RestoreInterrupts(u32);
u64 insertTimer(Nw2Timer *t) {
 Nw2Timer *p; u64 value; u32 mask;
 mask=nw2DisableInterrupts();
 p=g_80038820->next;
 value=t->value;
 while(p!=g_80038820 && p->value<value) {value-=p->value;p=p->next;}
 t->value=value;
 if(p!=g_80038820) p->value-=value;
 t->next=p;t->prev=p->prev;p->prev->next=t;p->prev=t;
 nw2RestoreInterrupts(mask);
 return value;
}
