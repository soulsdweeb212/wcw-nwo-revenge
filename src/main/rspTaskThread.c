/* @header
 * rspTaskThread  (originally func_80000EEC)
 * VRAM 0x80000EEC | ROM 0x1AEC | size 0x148
 * asm: asm/nonmatchings/main/rspTaskThread.s
 */
#include "common.h"

extern u8 D_800440C0[];
typedef struct {u8 pad[0x50];void *queue,*message;} TaskEEC;
typedef struct {TaskEEC *task;s32 notify;} CurrentEEC;
extern TaskEEC *D_80044570;
s32 osRecvMesg(void *,void *,s32);s32 osSendMesg(void *,void *,s32);
void osWritebackDCacheAll(void);void osSpTaskLoad(void *);void osSpTaskStartGo(void *);void osSpTaskYield(void);s32 osSpTaskYielded(void *);
/* RSP task thread: blocks for a task message, runs the previous task's pending
 * display list, loads and starts the new task, waits for it to finish, and
 * notifies the waiter. If the previous task still had work (osSpTaskYielded) it is
 * re-run instead of the new one. */
void rspTaskThread(void){
    TaskEEC *msg; void *reply; s32 state; TaskEEC *previous; u8 *base=D_800440C0; CurrentEEC *current=(CurrentEEC *)(base+0x4b4); u8 *queue=base+0x70;
    for(;;){
        osRecvMesg(base,&msg,1);state=0;osWritebackDCacheAll();previous=D_80044570;
        if(previous){state=2;osSpTaskYield();osRecvMesg(base+0x70,&reply,1);if(osSpTaskYielded((u8 *)previous+0x10))state=1;}
        current->task=msg;osSpTaskLoad((u8 *)msg+0x10);osSpTaskStartGo((u8 *)msg+0x10);
        osRecvMesg(queue,&reply,1);current->task=0;
        if(current->notify)osSendMesg((u8 *)current-0x3d4,&reply,1);
        if(state==1){u8 *task=(u8 *)previous+0x10;osSpTaskLoad(task);osSpTaskStartGo(task);}else if(state==2)osSendMesg(queue,&reply,1);
        osSendMesg(msg->queue,msg->message,1);
    }
}
