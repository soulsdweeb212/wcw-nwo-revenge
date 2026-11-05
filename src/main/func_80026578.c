/* @header
 * func_80026578
 * VRAM 0x80026578 | ROM 0x27178 | size 0x34
 * asm: asm/nonmatchings/main/func_80026578.s
 */
/* func_80026578: not a function but the `handle_CpU` block of libultra __osException (exceptasm.s),
 * split out because in the original it follows send_mesg (func_800264BC), after the end of
 * func_80025F30, and is followed by __osEnqueueAndYield (func_800265AC). func_80025F30 branches
 * here (beq) when the Cause exception code is 11 (CpU, "coprocessor unusable"), with $k0 = the
 * interrupted thread (__osRunningThread, its context already saved) and $t0 = Cause. If the
 * unusable coprocessor (Cause.CE, bits 29:28) is not 1 it branches to `panic` (.L8002648C:
 * __osFaultedThread = thread, state STOPPED, flags FAULT, save BadVAddr, post OS_EVENT_FAULT,
 * dispatch). For CP1 it implements lazy FPU enabling: thread->fp = 1 (from now on the handler
 * saves/restores its FPU registers), thread->context.sr |= SR_CU1, then branches to
 * `enqueueRunning` (.L80026474: push the thread back on the head of __osRunQueue and j
 * __osDispatchThread), so the faulting FPU instruction is re-executed with the FPU enabled. The
 * final store sits in the branch delay slot. Uses $k1 as scratch. Must be asm: it lives inside the
 * exception handler, uses $k0/$k1 and exits by branching to labels in another routine. */
#ifdef NON_MATCHING
#include "common.h"
#define CAUSE_CEMASK  0x30000000 /* Cause bits 29:28: number of the unusable coprocessor */
#define CAUSE_CESHIFT 28
#define SR_CU1        0x20000000 /* Status bit 29: coprocessor 1 (FPU) usable */

typedef struct OSThreadCpU {
    /* 0x000 */ u8 pad0[0x18];
    /* 0x018 */ s32 fp;          /* 1 = thread uses the FPU, so its FPU registers are saved/restored */
    /* 0x01C */ u8 pad1C[0x118 - 0x1C];
    /* 0x118 */ u32 sr;          /* saved Status register (context.sr) */
} OSThreadCpU;

/* The two exits are labels inside func_80025F30 (the exception handler), not functions; they
 * are reached with a branch (b/bne), never returned from. */
void excEnqueueRunning(OSThreadCpU *thread); /* .L80026474: push `thread` on the run-queue head, j func_8002670C */
void excPanic(OSThreadCpU *thread);          /* .L8002648C: stop `thread`, post the fault event, dispatch */

/* Entered from func_80025F30 by `beq` when the Cause exception code is 11 (CpU, coprocessor
 * unusable), with the interrupted thread in $k0 and the Cause register value in $t0. */
void func_80026578(OSThreadCpU *thread /* $k0 */, u32 cause /* $t0 */) {
    if (((cause & CAUSE_CEMASK) >> CAUSE_CESHIFT) != 1) {
        excPanic(thread);                /* CP0/CP2/CP3 unusable: a real fault */
        return;
    }
    /* First FPU instruction executed by this thread: from now on it owns FPU state. */
    thread->fp = 1;
    thread->sr |= SR_CU1;                /* returns to the thread with the FPU enabled */
    excEnqueueRunning(thread);           /* store is in the branch delay slot */
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl func_80026578\n"
    ".ent func_80026578\n"
    "func_80026578:\n"
    "lui $at, (0x30000000 >> 16)\n"
    "and $t1, $t0, $at\n"
    "srl $t1, $t1, 28\n"
    "addiu $t2, $zero, 0x1\n"
    ".word 0x152AFFC0 /* bne .L8002648C: target outside this function */\n"
    "nop\n"
    "addiu $t1, $zero, 0x1\n"
    "sw $t1, 0x18($k0) /* handwritten instruction */\n"
    "lw $k1, 0x118($k0) /* handwritten instruction */\n"
    "lui $at, (0x20000000 >> 16)\n"
    "or $k1, $k1, $at\n"
    ".word 0x1000FFB3 /* b .L80026474: target outside this function */\n"
    "sw $k1, 0x118($k0) /* handwritten instruction */\n"
    ".end func_80026578\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
