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
s32 func_8001C990(void *,void *,s32);s32 func_8001CAC0(void *,void *,s32);
void func_8001C860(void);void loadRspTask(void *);void func_80020D4C(void *);void func_80020D80(void);s32 func_80020DA0(void *);
/* RSP task thread: blocks for a task message, runs the previous task's pending
 * display list, loads and starts the new task, waits for it to finish, and
 * notifies the waiter. If the previous task still had work (func_80020DA0) it is
 * re-run instead of the new one. */
void rspTaskThread(void){
 TaskEEC *msg; void *reply; s32 state; TaskEEC *previous; u8 *base=D_800440C0; CurrentEEC *current=(CurrentEEC *)(base+0x4b4); u8 *queue=base+0x70;
 for(;;){
 func_8001C990(base,&msg,1);state=0;func_8001C860();previous=D_80044570;
 if(previous){state=2;func_80020D80();func_8001C990(base+0x70,&reply,1);if(func_80020DA0((u8 *)previous+0x10))state=1;}
 current->task=msg;loadRspTask((u8 *)msg+0x10);func_80020D4C((u8 *)msg+0x10);
 func_8001C990(queue,&reply,1);current->task=0;
 if(current->notify)func_8001CAC0((u8 *)current-0x3d4,&reply,1);
 if(state==1){u8 *task=(u8 *)previous+0x10;loadRspTask(task);func_80020D4C(task);}else if(state==2)func_8001CAC0(queue,&reply,1);
 func_8001CAC0(msg->queue,msg->message,1);
 }
}
