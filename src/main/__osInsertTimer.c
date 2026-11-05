/* @header
 * __osInsertTimer  (originally func_80027230)
 * VRAM 0x80027230 | ROM 0x27E30 | size 0x108
 * asm: asm/nonmatchings/main/__osInsertTimer.s
 */
/* SDK: libultra 2.0I, ultralib src/os/timerintr.c (same code as the SDK source). */
#include "common.h"

typedef struct Nw2Timer {struct Nw2Timer *next,*prev; u64 interval,value; void *mq; u32 msg;} Nw2Timer;
extern Nw2Timer *__osTimerList;
u32 __osDisableInt(void);
void __osRestoreInt(u32);
u64 __osInsertTimer(Nw2Timer *t) {
    Nw2Timer *p; u64 value; u32 mask;
    mask=__osDisableInt();
    p=__osTimerList->next;
    value=t->value;
    while(p!=__osTimerList && p->value<value) {value-=p->value;p=p->next;}
    t->value=value;
    if(p!=__osTimerList) p->value-=value;
    t->next=p;t->prev=p->prev;p->prev->next=t;p->prev=t;
    __osRestoreInt(mask);
    return value;
}
