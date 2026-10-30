/* @header
 * renderTaskThread  (originally func_80001034)
 * VRAM 0x80001034 | ROM 0x1C34 | size 0x1A0
 * asm: asm/nonmatchings/main/renderTaskThread.s
 */
#include "common.h"

typedef struct
{
  s32 f0;
  s32 f4;
  u32 flags;
  s32 framebuffer;
  u8 task[0x40];
  s32 queue;
  s32 message;
} RenderTask;
typedef struct RenderListener
{
  struct RenderListener *next;
  void *queue;
} RenderListener;
typedef struct
{
  u8 pad[0x260];
  RenderListener *listeners;
} RenderManager;
extern RenderManager *D_80044580;
extern RenderTask *D_80044570;
extern RenderTask *D_80044578;
extern s32 D_80044574;
extern s32 D_8002EEA0;
extern u8 D_800441D8[];
s32 func_8001C740(s32);
s32 func_8001C990(void *, void *, s32);
s32 func_8001CAC0(s32, s32, s32);
void func_800011D4(void *);
void loadRspTask(void *);
void func_80020D4C(void *);
void func_80021130(s32);
void func_800210E0(s32);

/* Render-thread main loop (entry of the graphics thread started by func_80000AF0).
 * Registers a listener on the render manager, then forever: receive a RenderTask,
 * run prep (func_800011D4), publish it for the swap path if requested (D_80044574),
 * load/execute the RSP task, ACK the queue messages, swap framebuffers when the
 * task requests an end-frame (flags & 0x40), and post completion back on the
 * task's own queue. func_8001C740 saves/restores the OS thread interrupt mask. */
void renderTaskThread(void)
{
  RenderListener listener;
  RenderTask *task;
  s32 message;
  s32 savedMask;
  RenderManager *manager = D_80044580;
  u8 *queueBase;
  savedMask = func_8001C740(1);
  ;
  listener.queue = D_800441D8;
  listener.next = manager->listeners;
  manager->listeners = &listener;
  func_8001C740(savedMask);
  for (;;)
  {
    func_8001C990(D_800441D8 - 0xE0, &task, 1);
    func_800011D4(task);
    savedMask = func_8001C740(1);
    if (D_80044574)
    {
      D_80044578 = task;
      func_8001C740(savedMask);
      func_8001C990((D_800441D8 - 0xE0) + 0xA8, &message, 1);
      savedMask = func_8001C740(1);
      D_80044578 = NULL;
    }
    func_8001C740(savedMask);
    savedMask = func_8001C740(1);
    D_80044570 = task;
    func_8001C740(savedMask);
    loadRspTask(task->task);
    func_80020D4C(task->task);
    func_8001C990((D_800441D8 - 0xE0) + 0x38, &message, 1);
    savedMask = func_8001C740(1);
    D_80044570 = NULL;
    func_8001C740(savedMask);
    func_8001C990((D_800441D8 - 0xE0) + 0x70, &message, 1);
    if (task->flags & 0x40)
    {
      if (D_8002EEA0)
      {
        func_80021130(0);
        D_8002EEA0 = 0;
      }
      func_800210E0(task->framebuffer);
    }
    func_8001CAC0(task->queue, task->message, 1);
  }

}
