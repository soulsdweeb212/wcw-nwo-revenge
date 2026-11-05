/* @header
 * func_800266FC
 * VRAM 0x800266FC | ROM 0x272FC | size 0x10
 * asm: asm/nonmatchings/main/func_800266FC.s
 */
/* func_800266FC: libultra __osPopThread(OSThread **queue). Removes and returns the head of a
 * priority-ordered thread queue: t = *queue; *queue = t->next. No empty check: every queue ends in
 * the priority -1 sentinel thread, and callers only pop when they know a thread is waiting.
 * Callers: startThread (osStartThread), func_8001CAC0 (osSendMesg), func_8001C990 (osRecvMesg),
 * func_80026E60 (osJamMesg), and from asm the dispatcher func_8002670C (__osDispatchThread) and the
 * exception handler's send_mesg func_800264BC (pops the thread waiting on the event's message
 * queue, then hands it to func_800266B4 to put it on __osRunQueue). Pure
 * logic; the original uses $t9 as its temporary, which the C reproduces with a register variable. */
#ifdef NON_MATCHING
#include "common.h"
typedef struct OSThreadLink { struct OSThreadLink *next; } OSThreadLink;

/* Unlinks and returns the first thread of a priority-ordered queue (the queue is never empty:
 * it always ends in the priority -1 sentinel). The register variable only pins the temporary to
 * $t9, the register the hand-written original used; it emits no code. */
OSThreadLink *func_800266FC(OSThreadLink **queue) {
    register OSThreadLink *head = *queue;
    register OSThreadLink *next asm("$25") = head->next;
    *queue = next;
    return head;
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    ".globl func_800266FC\n"
    ".ent func_800266FC\n"
    "func_800266FC:\n"
    "lw $v0, 0x0($a0)\n"
    "lw $t9, 0x0($v0)\n"
    "jr $ra\n"
    "sw $t9, 0x0($a0)\n"
    ".end func_800266FC\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
