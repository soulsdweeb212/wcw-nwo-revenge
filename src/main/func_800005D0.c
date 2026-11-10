/* @header
 * func_800005D0
 * VRAM 0x800005D0 | ROM 0x11D0 | size 0x34
 * asm: asm/nonmatchings/main/func_800005D0.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the types of the definitions. func_80000EE0 returns the address of the task queue D_800440F8, which an s32
 * would cut in half; osSendMesg (SDK code that the port replaces with a stand-in, renamed port_osSendMesg by port.h)
 * takes the queue as a pointer and the message as a 4-byte value, the size of a message slot in the game's queues. */
s32 *func_80000EE0(void);
s32 osSendMesg(void *, s32, s32);
#else
s32 func_80000EE0();
s32 osSendMesg(s32, s32, s32);
#endif

/* Send message arg0 (blocking) to the current event queue. */
#ifdef TARGET_PC
/* PC: the only caller, submitGraphicsTask, passes the address of a task (the task block at +0x4000 of a render-list
 * record), which an s32 would cut in half, so the PC definition takes a pointer (port_decls.h declares it
 * so). A message is 4 bytes in the game's queues (the port's queues keep the N64 size), so the task goes as a 32-bit
 * handle (port.h's PTR_TO_SLOT); the port's renderTaskThread, which receives it, turns it back with SLOT_TO_PTR. */
void func_800005D0(void *arg0) {
    osSendMesg(func_80000EE0(), PTR_TO_SLOT(arg0), 1);
}
#else
void func_800005D0(s32 arg0) {
    osSendMesg(func_80000EE0(), arg0, 1);
}
#endif
