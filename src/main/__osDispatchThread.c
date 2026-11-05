/* @header
 * __osDispatchThread  (originally func_8002670C)
 * VRAM 0x8002670C | ROM 0x2730C | size 0x188
 * asm: asm/nonmatchings/main/__osDispatchThread.s
 */
/* __osDispatchThread: libultra __osDispatchThread (exceptasm.s), followed by __osCleanupThread at +0x17C.
 * Pops the highest-priority thread off __osRunQueue (__osPopThread), makes it
 * __osRunningThread with state OS_STATE_RUNNING (4), loads Status from its saved SR with the
 * CPU interrupt mask ANDed with __OSGlobalIntMask, reloads all GPRs (64-bit ld), LO/HI, EPC =
 * saved pc, and, if thread->fp, FCSR and f0-f30; then writes MI_INTR_MASK_REG (0xA430000C) with
 * __osRcpImTable[saved rcp & (globalmask >> 16)] (__osRcpImTable, 64 u16 set/clear words), waits 4 nops and
 * erets into the thread. Reached by `j` from the exception handler (__osExceptionPreamble), __osEnqueueAndYield
 * (__osEnqueueAndYield), osStartThread when no thread is running yet (osStartThread starting the scheduler) and
 * osDestroyThread when the current thread destroys itself. The last 3 instructions after
 * the eret are __osCleanupThread: `move a0, zero; jal osDestroyThread`. osCreateThread
 * (osCreateThread) puts __osDispatchThread + 0x17C into each new thread's ra, so a thread entry function that
 * returns destroys its own thread. Must be asm: it restores every register (including sp/ra) and only
 * $k0/$k1 may stay live afterwards; mtc0/ctc1/eret. Same instructions as ultralib 2.0I (no thread
 * profiler hook, VERSION_K+ only). The C below names the cleanup entry __osCleanupThread; a C-only build
 * would also have to point osCreateThread at that symbol instead of __osDispatchThread + 0x17C. */
#ifdef NON_MATCHING
#include "common.h"

/* libultra OSThread (0x1B0 bytes). The register save area is __OSThreadContext. */
typedef struct {
    u64 at, v0, v1, a0, a1, a2, a3;                 /* +20..+50 */
    u64 t0, t1, t2, t3, t4, t5, t6, t7;             /* +58..+90 */
    u64 s0, s1, s2, s3, s4, s5, s6, s7;             /* +98..+D0 */
    u64 t8, t9, gp, sp, s8, ra, lo, hi;             /* +D8..+110 */
    u32 sr, pc, cause, badvaddr, rcp;               /* +118..+128 */
    u32 fpcsr;                                      /* +12C */
    f64 fp0, fp2, fp4, fp6, fp8, fp10, fp12, fp14;  /* +130..+168 */
    f64 fp16, fp18, fp20, fp22, fp24, fp26, fp28, fp30; /* +170..+1A8 */
} OSThreadContext;
typedef struct OSThread {
    struct OSThread *next;   /* +00 */
    s32 priority;            /* +04 */
    struct OSThread **queue; /* +08 */
    struct OSThread *tlnext; /* +0C */
    u16 state;               /* +10 OS_STATE_STOPPED 1, RUNNABLE 2, RUNNING 4, WAITING 8 */
    u16 flags;               /* +12 */
    s32 id;                  /* +14 */
    s32 fp;                  /* +18 nonzero once the thread has used the FPU */
    s32 pad;                 /* +1C */
    OSThreadContext context; /* +20 */
} OSThread;

extern OSThread *__osRunQueue;  /* __osRunQueue (priority-sorted, ends in the -1 sentinel __osThreadTail) */
extern OSThread *__osRunningThread;
extern u32 __OSGlobalIntMask;        /* bits 15..8 CPU IM, bits 21..16 RCP (MI) mask */
extern u16 __osRcpImTable[];      /* __osRcpImTable[64]: MI_INTR_MASK_REG set/clear word per 6-bit mask */
extern vu32 D_A430000C;       /* MI_INTR_MASK_REG */
OSThread *__osPopThread(OSThread **queue); /* __osPopThread */
void osDestroyThread(OSThread *thread);       /* osDestroyThread */

/* CP0 Status ($12), EPC ($14), FPU control/status ($31), eret. */
static inline void setStatus(u32 v) { __asm__ __volatile__("mtc0 %0, $12" : : "r"(v)); }
static inline void setEPC(u32 v) { __asm__ __volatile__("mtc0 %0, $14" : : "r"(v)); }
static inline void setFpcsr(u32 v) { __asm__ __volatile__("ctc1 %0, $31" : : "r"(v)); }
/* LO/HI <- $k1 (the full 64-bit register just reloaded with ld). */
static inline void k1ToLo(void) { __asm__ __volatile__("mtlo $27"); }
static inline void k1ToHi(void) { __asm__ __volatile__("mthi $27"); }
static inline void pipelineNop(void) { __asm__ __volatile__("nop"); }
static inline void exceptionReturn(void) { __asm__ __volatile__("eret"); }
/* Reload one register, full 64 bits, from the context at byte offset `off` of the thread
 * (base in $k0, the kernel register that no thread owns): one ld / ldc1 each. */
#define LOAD_GPR(reg, off, base) __asm__ __volatile__("ld " reg ", %1(%0)" : : "r"(base), "i"(off))
#define LOAD_FPR(reg, off, base) __asm__ __volatile__("ldc1 " reg ", %1(%0)" : : "r"(base), "i"(off))

/* __osDispatchThread: run the highest-priority runnable thread. Pops it off the run queue,
 * makes it the running thread, restores its whole register context and erets to its pc.
 * Never returns to the caller. */
void __osDispatchThread(void) {
    register OSThread *k0 asm("$26");
    register u32 k1 asm("$27");
    OSThread *t;

    t = __osPopThread(&__osRunQueue);
    __osRunningThread = t;
    t->state = 4;                                  /* OS_STATE_RUNNING */
    k0 = t;

    /* Status = thread's SR, but CPU interrupt-mask bits only where the global mask allows. */
    k1 = k0->context.sr;
    setStatus((k1 & 0xFFFF00FF) | (k1 & 0xFF00 & (__OSGlobalIntMask & 0xFF00)));

    /* Restore all general registers except $0, $k0, $k1 (the original runs this with only
     * $k0/$k1 live; a compiled version cannot guarantee that, see the file comment). */
    __asm__ __volatile__(".set noat\n\tld $1, %1(%0)\n\t.set at" : : "r"(k0), "i"(0x20));
    LOAD_GPR("$2", 0x28, k0);  LOAD_GPR("$3", 0x30, k0);
    LOAD_GPR("$4", 0x38, k0);  LOAD_GPR("$5", 0x40, k0);  LOAD_GPR("$6", 0x48, k0);  LOAD_GPR("$7", 0x50, k0);
    LOAD_GPR("$8", 0x58, k0);  LOAD_GPR("$9", 0x60, k0);  LOAD_GPR("$10", 0x68, k0); LOAD_GPR("$11", 0x70, k0);
    LOAD_GPR("$12", 0x78, k0); LOAD_GPR("$13", 0x80, k0); LOAD_GPR("$14", 0x88, k0); LOAD_GPR("$15", 0x90, k0);
    LOAD_GPR("$16", 0x98, k0); LOAD_GPR("$17", 0xA0, k0); LOAD_GPR("$18", 0xA8, k0); LOAD_GPR("$19", 0xB0, k0);
    LOAD_GPR("$20", 0xB8, k0); LOAD_GPR("$21", 0xC0, k0); LOAD_GPR("$22", 0xC8, k0); LOAD_GPR("$23", 0xD0, k0);
    LOAD_GPR("$24", 0xD8, k0); LOAD_GPR("$25", 0xE0, k0); LOAD_GPR("$28", 0xE8, k0); LOAD_GPR("$29", 0xF0, k0);
    LOAD_GPR("$30", 0xF8, k0); LOAD_GPR("$31", 0x100, k0);
    LOAD_GPR("$27", 0x108, k0); k1ToLo();          /* ld $k1, lo; mtlo $k1 */
    LOAD_GPR("$27", 0x110, k0); k1ToHi();          /* ld $k1, hi; mthi $k1 */
    k1 = k0->context.pc; setEPC(k1);              /* eret will resume at the thread's pc */

    if (k0->fp != 0) {                             /* thread uses the FPU: FCSR + all 16 even FPRs */
        k1 = k0->context.fpcsr; setFpcsr(k1);
        LOAD_FPR("$f0", 0x130, k0);  LOAD_FPR("$f2", 0x138, k0);  LOAD_FPR("$f4", 0x140, k0);
        LOAD_FPR("$f6", 0x148, k0);  LOAD_FPR("$f8", 0x150, k0);  LOAD_FPR("$f10", 0x158, k0);
        LOAD_FPR("$f12", 0x160, k0); LOAD_FPR("$f14", 0x168, k0); LOAD_FPR("$f16", 0x170, k0);
        LOAD_FPR("$f18", 0x178, k0); LOAD_FPR("$f20", 0x180, k0); LOAD_FPR("$f22", 0x188, k0);
        LOAD_FPR("$f24", 0x190, k0); LOAD_FPR("$f26", 0x198, k0); LOAD_FPR("$f28", 0x1A0, k0);
        LOAD_FPR("$f30", 0x1A8, k0);
    }

    /* RCP interrupt mask: the thread's saved 6-bit MI mask ANDed with the global RCP mask
     * (no extra & 0x3F: __OSGlobalIntMask bits above 21 are expected to be 0), translated by
     * the table into the MI_INTR_MASK_REG set/clear word. */
    k1 = k0->context.rcp & (__OSGlobalIntMask >> 16);
    D_A430000C = __osRcpImTable[k1];

    pipelineNop(); pipelineNop(); pipelineNop(); pipelineNop();  /* let CP0/MI writes settle */
    exceptionReturn();                             /* eret: PC = EPC, clears Status.EXL */
}

/* __osCleanupThread: the 3 instructions after the eret (__osDispatchThread + 0x17C). osCreateThread
 * (osCreateThread) stores this address as the new thread's ra, so a thread whose entry
 * function returns lands here and destroys itself (osDestroyThread(NULL) = current thread). */
void __osCleanupThread(void) {
    osDestroyThread(NULL);
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl __osDispatchThread\n"
    ".ent __osDispatchThread\n"
    "__osDispatchThread:\n"
    "lui $a0, %hi(__osRunQueue)\n"
    "jal __osPopThread\n"
    "addiu $a0, $a0, %lo(__osRunQueue)\n"
    "lui $at, %hi(__osRunningThread)\n"
    "sw $v0, %lo(__osRunningThread)($at)\n"
    "addiu $t0, $zero, 0x4\n"
    "sh $t0, 0x10($v0)\n"
    "addu $k0, $v0, $zero\n"
    "lw $k1, 0x118($k0) /* handwritten instruction */\n"
    "lui $t0, %hi(__OSGlobalIntMask)\n"
    "addiu $t0, $t0, %lo(__OSGlobalIntMask)\n"
    "lw $t0, 0x0($t0)\n"
    "andi $t0, $t0, 0xFF00\n"
    "andi $t1, $k1, 0xFF00 /* handwritten instruction */\n"
    "and $t1, $t1, $t0\n"
    "lui $at, (0xFFFF00FF >> 16)\n"
    "ori $at, $at, (0xFFFF00FF & 0xFFFF)\n"
    "and $k1, $k1, $at\n"
    "or $k1, $k1, $t1\n"
    "mtc0 $k1, $12 /* handwritten instruction */\n"
    "ld $at, 0x20($k0) /* handwritten instruction */\n"
    "ld $v0, 0x28($k0) /* handwritten instruction */\n"
    "ld $v1, 0x30($k0) /* handwritten instruction */\n"
    "ld $a0, 0x38($k0) /* handwritten instruction */\n"
    "ld $a1, 0x40($k0) /* handwritten instruction */\n"
    "ld $a2, 0x48($k0) /* handwritten instruction */\n"
    "ld $a3, 0x50($k0) /* handwritten instruction */\n"
    "ld $t0, 0x58($k0) /* handwritten instruction */\n"
    "ld $t1, 0x60($k0) /* handwritten instruction */\n"
    "ld $t2, 0x68($k0) /* handwritten instruction */\n"
    "ld $t3, 0x70($k0) /* handwritten instruction */\n"
    "ld $t4, 0x78($k0) /* handwritten instruction */\n"
    "ld $t5, 0x80($k0) /* handwritten instruction */\n"
    "ld $t6, 0x88($k0) /* handwritten instruction */\n"
    "ld $t7, 0x90($k0) /* handwritten instruction */\n"
    "ld $s0, 0x98($k0) /* handwritten instruction */\n"
    "ld $s1, 0xA0($k0) /* handwritten instruction */\n"
    "ld $s2, 0xA8($k0) /* handwritten instruction */\n"
    "ld $s3, 0xB0($k0) /* handwritten instruction */\n"
    "ld $s4, 0xB8($k0) /* handwritten instruction */\n"
    "ld $s5, 0xC0($k0) /* handwritten instruction */\n"
    "ld $s6, 0xC8($k0) /* handwritten instruction */\n"
    "ld $s7, 0xD0($k0) /* handwritten instruction */\n"
    "ld $t8, 0xD8($k0) /* handwritten instruction */\n"
    "ld $t9, 0xE0($k0) /* handwritten instruction */\n"
    "ld $gp, 0xE8($k0) /* handwritten instruction */\n"
    "ld $sp, 0xF0($k0) /* handwritten instruction */\n"
    "ld $fp, 0xF8($k0) /* handwritten instruction */\n"
    "ld $ra, 0x100($k0) /* handwritten instruction */\n"
    "ld $k1, 0x108($k0) /* handwritten instruction */\n"
    "mtlo $k1\n"
    "ld $k1, 0x110($k0) /* handwritten instruction */\n"
    "mthi $k1\n"
    "lw $k1, 0x11C($k0) /* handwritten instruction */\n"
    "mtc0 $k1, $14 /* handwritten instruction */\n"
    "lw $k1, 0x18($k0) /* handwritten instruction */\n"
    "beqz $k1, .L8002683C /* handwritten instruction */\n"
    "nop\n"
    "lw $k1, 0x12C($k0) /* handwritten instruction */\n"
    "ctc1 $k1, $31\n"
    "ldc1 $fv0, 0x130($k0)\n"
    "ldc1 $fv1, 0x138($k0)\n"
    "ldc1 $ft0, 0x140($k0)\n"
    "ldc1 $ft1, 0x148($k0)\n"
    "ldc1 $ft2, 0x150($k0)\n"
    "ldc1 $ft3, 0x158($k0)\n"
    "ldc1 $fa0, 0x160($k0)\n"
    "ldc1 $fa1, 0x168($k0)\n"
    "ldc1 $ft4, 0x170($k0)\n"
    "ldc1 $ft5, 0x178($k0)\n"
    "ldc1 $fs0, 0x180($k0)\n"
    "ldc1 $fs1, 0x188($k0)\n"
    "ldc1 $fs2, 0x190($k0)\n"
    "ldc1 $fs3, 0x198($k0)\n"
    "ldc1 $fs4, 0x1A0($k0)\n"
    "ldc1 $fs5, 0x1A8($k0)\n"
    ".L8002683C:\n"
    "lw $k1, 0x128($k0) /* handwritten instruction */\n"
    "lui $k0, %hi(__OSGlobalIntMask) /* handwritten instruction */\n"
    "addiu $k0, $k0, %lo(__OSGlobalIntMask) /* handwritten instruction */\n"
    "lw $k0, 0x0($k0) /* handwritten instruction */\n"
    "srl $k0, $k0, 16\n"
    "and $k1, $k1, $k0\n"
    "sll $k1, $k1, 1\n"
    "lui $k0, %hi(__osRcpImTable) /* handwritten instruction */\n"
    "addiu $k0, $k0, %lo(__osRcpImTable) /* handwritten instruction */\n"
    "addu $k1, $k1, $k0\n"
    "lhu $k1, 0x0($k1) /* handwritten instruction */\n"
    "lui $k0, (0xA430000C >> 16) /* handwritten instruction */\n"
    "ori $k0, $k0, (0xA430000C & 0xFFFF) /* handwritten instruction */\n"
    "sw $k1, 0x0($k0) /* handwritten instruction */\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "eret /* handwritten instruction */\n"
    "addu $a0, $zero, $zero\n"
    "jal osDestroyThread\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    ".end __osDispatchThread\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
