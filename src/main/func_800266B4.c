/* @header
 * func_800266B4
 * VRAM 0x800266B4 | ROM 0x272B4 | size 0x48
 * asm: asm/nonmatchings/main/func_800266B4.s
 */
/* func_800266B4: libultra __osEnqueueThread(OSThread **queue, OSThread *t). Inserts t into a
 * priority-ordered thread queue after every thread of priority >= t's (equal priorities stay FIFO),
 * then t->queue = queue. The queue pointer itself acts as the pseudo-thread before the head (`next`
 * is at offset 0); the walk has no NULL check because every queue ends in the priority -1 sentinel.
 * Callers: startThread (osStartThread), func_8001CC50 (osSetThreadPri), the exception handler
 * func_80025F30 (redispatch: put the preempted thread back on __osRunQueue), func_800265AC
 * (__osEnqueueAndYield) and the exception handler's send_mesg func_800264BC (puts the thread it
 * popped off the event's message queue on __osRunQueue); D_80037248 is __osRunQueue. Same logic as the reference
 * exceptasm.s/thread.c: the C with register variables and empty scheduling barriers is
 * byte-identical. */
#ifdef NON_MATCHING
#include "common.h"
typedef struct OSThreadLink {
    /* 0x0 */ struct OSThreadLink *next;
    /* 0x4 */ s32 priority;
    /* 0x8 */ struct OSThreadLink **queue;
} OSThreadLink;

/* Empty asm: emits nothing, only stops gcc from moving instructions across it (here it keeps
 * gcc's delay-slot filler from pulling `move t9,a0` and `move t9,t8` into the branch slots). */
#define BARRIER() __asm__ __volatile__("")

/* Same as:
 *     pred = (OSThreadLink *)queue; succ = *queue;
 *     while (succ->priority >= t->priority) { pred = succ; succ = succ->next; }
 *     t->next = pred->next; pred->next = t; t->queue = queue;
 * The register variables only pin each value to the register the hand-written original uses
 * ($t9 pred, $t8 succ, $t7 t->priority, $t6 succ->priority, $at the slt result). */
void func_800266B4(OSThreadLink **queue, OSThreadLink *t) {
    register OSThreadLink *pred asm("$25");
    register OSThreadLink *succ asm("$24");
    register s32 pri asm("$15");
    register s32 succPri asm("$14");
    register s32 lower asm("$1");

    pred = (OSThreadLink *)queue;   /* `next` is at offset 0, so the queue head acts as a thread */
    BARRIER();
    succ = *queue;
    pri = t->priority;              /* read once */
    succPri = succ->priority;
    lower = succPri < pri;          /* signed (slt) */
    BARRIER();
    if (!lower) {
        do {                        /* no NULL check: the priority -1 sentinel ends every queue */
            BARRIER();
            pred = succ;
            succ = succ->next;
            succPri = succ->priority;
            lower = succPri < pri;
        } while (!lower);
    }
    succ = pred->next;              /* re-read; equals succ */
    t->next = succ;
    pred->next = t;
    t->queue = queue;
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    ".globl func_800266B4\n"
    ".ent func_800266B4\n"
    "func_800266B4:\n"
    "addu $t9, $a0, $zero\n"
    "lw $t8, 0x0($a0)\n"
    "lw $t7, 0x4($a1)\n"
    "lw $t6, 0x4($t8)\n"
    "slt $at, $t6, $t7\n"
    "bnez $at, .L800266E8\n"
    "nop\n"
    ".L800266D0:\n"
    "addu $t9, $t8, $zero\n"
    "lw $t8, 0x0($t8)\n"
    "lw $t6, 0x4($t8)\n"
    "slt $at, $t6, $t7\n"
    "beqz $at, .L800266D0\n"
    "nop\n"
    ".L800266E8:\n"
    "lw $t8, 0x0($t9)\n"
    "sw $t8, 0x0($a1)\n"
    "sw $a1, 0x0($t9)\n"
    "jr $ra\n"
    "sw $a0, 0x8($a1)\n"
    ".end func_800266B4\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
