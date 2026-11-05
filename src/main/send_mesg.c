/* @header
 * send_mesg  (originally func_800264BC)
 * VRAM 0x800264BC | ROM 0x270BC | size 0xBC
 * asm: asm/nonmatchings/main/send_mesg.s
 */
/* send_mesg: libultra send_mesg (exceptasm.s), the private helper the exception handler __osExceptionPreamble
 * calls to post a hardware event. a0 is the byte offset MESG(OS_EVENT_xxx) = event*8 into
 * __osEventStateTab (D_8007DF30, {OSMesgQueue *queue; OSMesg msg} per event, filled by osSetEventMesg).
 * If a queue is registered and not full, the event's message is stored at msg[(first + validCount) %
 * msgCount] and validCount++; if a thread is blocked receiving on that queue (mtqueue->next != NULL, the
 * list ends at the -1-priority sentinel) it is popped (__osPopThread) and inserted into
 * __osRunQueue (D_80037248) by __osEnqueueThread. A full queue silently drops the event.
 * Non-standard calling convention, which is why it is asm: it keeps its return address in $s2 (move s2,
 * ra ... jr s2) instead of a stack frame, because it runs inside the exception handler on the interrupted
 * thread's stack, and it never touches the handler's live $t0/$s0/$s1/$k0/$k1. It does overwrite $at,
 * $t1-$t5, $a0, $a1, HI/LO (div, mult), $s2 and $ra (plus the leaf helpers' $v0, $t6-$t9); $s2 was
 * already saved to the thread context. $a0 on return is the eventOffset argument on the early-return
 * paths, or &__osRunQueue (0x80037248) when a receiver was woken. When an earlier event in the same
 * exception went through here, that leftover $a0 is what the cart path of __osExceptionPreamble posts when no
 * cart hook is installed (its `li a0` landed in a delay slot); otherwise it posts the interrupted
 * thread's own $a0 (or whatever the handler last put there). The
 * signed % keeps the compiler-style divide-by-zero (break 7) and overflow (break 6) checks. Same
 * instructions as ultralib. */
#ifdef NON_MATCHING
#include "common.h"

/* libultra OSThread / OSMesgQueue / __OSEventState; only the fields used here. */
typedef struct OSThread { struct OSThread *next; s32 priority; struct OSThread **queue; } OSThread;
typedef struct {
    OSThread *mtqueue;   /* +00 threads blocked receiving (sentinel-terminated list) */
    OSThread *fullqueue; /* +04 threads blocked sending */
    s32 validCount;      /* +08 messages currently queued */
    s32 first;           /* +0C index of the oldest message */
    s32 msgCount;        /* +10 capacity */
    void **msg;          /* +14 message ring buffer */
} OSMesgQueue;
typedef struct { OSMesgQueue *queue; void *msg; } OSEventState;

extern OSEventState D_8007DF30[];   /* __osEventStateTab[OS_NUM_EVENTS] */
extern OSThread *D_80037248;        /* __osRunQueue */
void __osEnqueueThread(OSThread **queue, OSThread *thread); /* __osEnqueueThread */
OSThread *__osPopThread(OSThread **queue);              /* __osPopThread */

/* send_mesg: post the message registered for an event (osSetEventMesg) to its queue.
 * eventOffset is the byte offset into __osEventStateTab, i.e. OS_EVENT_xxx * 8. */
void send_mesg(s32 eventOffset) {
    OSEventState *es = (OSEventState *)((u8 *)D_8007DF30 + eventOffset);
    OSMesgQueue *mq = es->queue;
    s32 count;

    if (mq == NULL) return;                 /* nobody registered for this event */
    count = mq->validCount;
    if (count >= mq->msgCount) return;      /* queue full: the event is dropped */
    /* signed %, with the compiler's divide-by-zero / overflow break traps (break 7 / break 6) */
    mq->msg[(mq->first + count) % mq->msgCount] = es->msg;
    mq->validCount = count + 1;
    /* A receiver is blocked on the queue: pop it and make it runnable.
     * mtqueue is the first field, so the queue pointer doubles as &mq->mtqueue. */
    if (mq->mtqueue->next != NULL) {
        __osEnqueueThread(&D_80037248, __osPopThread(&mq->mtqueue));
    }
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    ".globl send_mesg\n"
    ".ent send_mesg\n"
    "send_mesg:\n"
    "addu $s2, $ra, $zero\n"
    "lui $t2, %hi(D_8007DF30)\n"
    "addiu $t2, $t2, %lo(D_8007DF30)\n"
    "addu $t2, $t2, $a0\n"
    "lw $t1, 0x0($t2)\n"
    "beqz $t1, .L80026570\n"
    "nop\n"
    "lw $t3, 0x8($t1)\n"
    "lw $t4, 0x10($t1)\n"
    "slt $at, $t3, $t4\n"
    "beqz $at, .L80026570\n"
    "nop\n"
    "lw $t5, 0xC($t1)\n"
    "addu $t5, $t5, $t3\n"
    "div $zero, $t5, $t4\n"
    "bnez $t4, .L80026504\n"
    "nop\n"
    "break 7\n"
    ".L80026504:\n"
    "addiu $at, $zero, -0x1\n"
    "bne $t4, $at, .L8002651C\n"
    "lui $at, (0x80000000 >> 16)\n"
    "bne $t5, $at, .L8002651C\n"
    "nop\n"
    "break 6\n"
    ".L8002651C:\n"
    "mfhi $t5\n"
    "lw $t4, 0x14($t1)\n"
    "addiu $at, $zero, 0x4\n"
    "mult $t5, $at\n"
    "mflo $t5\n"
    "addu $t4, $t4, $t5\n"
    "lw $t5, 0x4($t2)\n"
    "sw $t5, 0x0($t4)\n"
    "addiu $t2, $t3, 0x1\n"
    "sw $t2, 0x8($t1)\n"
    "lw $t2, 0x0($t1)\n"
    "lw $t3, 0x0($t2)\n"
    "beqz $t3, .L80026570\n"
    "nop\n"
    "jal __osPopThread\n"
    "addu $a0, $t1, $zero\n"
    "addu $t2, $v0, $zero\n"
    "addu $a1, $t2, $zero\n"
    "lui $a0, %hi(D_80037248)\n"
    "jal __osEnqueueThread\n"
    "addiu $a0, $a0, %lo(D_80037248)\n"
    ".L80026570:\n"
    "jr $s2\n"
    "nop\n"
    ".end send_mesg\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
