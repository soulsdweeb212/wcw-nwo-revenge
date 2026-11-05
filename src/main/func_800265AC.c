/* @header
 * func_800265AC
 * VRAM 0x800265AC | ROM 0x271AC | size 0x108
 * asm: asm/nonmatchings/main/func_800265AC.s
 */
/* func_800265AC: libultra __osEnqueueAndYield(OSThread **queue) (exceptasm.s): the running thread
 * voluntarily gives up the CPU. Called with interrupts disabled by osRecvMesg (func_8001C990),
 * osSendMesg (func_8001CAC0) and osJamMesg (func_80026E60) to block on a message queue's wait list, and
 * with &__osRunQueue by osStartThread (startThread), osSetThreadPri (func_8001CC50) and osYieldThread
 * (func_800281A0) to let a higher-priority thread run; NULL means "don't requeue me".
 * It saves only what a callee must preserve into __osRunningThread (D_80037250): SR | EXL, s0-s7, gp,
 * sp, s8, ra, and pc = ra (so when the thread is next dispatched the eret "returns" from this call), plus
 * FCSR and f20-f30 if the thread uses the FPU; it re-ORs into the saved SR and RCP mask the interrupt bits
 * the global mask __OSGlobalIntMask (D_80038810) had disabled, saves MI_INTR_MASK_REG (0xA430000C) as the
 * thread's RCP mask, inserts the thread into `queue` by priority (__osEnqueueThread, func_800266B4, if
 * queue != NULL) and jumps to __osDispatchThread (func_8002670C), never returning normally. Must be asm:
 * it captures the caller's live callee-saved registers and sp with no frame of its own, and reads FCSR
 * (cfc1). Same instructions as ultralib; uses $k0/$k1 as scratch (safe: interrupts are off). Some C files
 * here declare it with a second argument (osYieldThread passes 2); the routine ignores $a1 on entry. */
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
    u16 flags;               /* +12 OS_FLAG_CPU_BREAK 1, OS_FLAG_FAULT 2 */
    s32 id;                  /* +14 */
    s32 fp;                  /* +18 nonzero once the thread has used the FPU */
    s32 pad;                 /* +1C */
    OSThreadContext context; /* +20 */
} OSThread;

extern OSThread *D_80037250;  /* __osRunningThread */
extern u32 D_80038810;        /* __OSGlobalIntMask: bits 15..8 CPU IM, bits 21..16 RCP (MI) mask */
extern vu32 D_A430000C;       /* MI_INTR_MASK_REG (read: currently enabled MI interrupts) */
void func_800266B4(OSThread **queue, OSThread *thread); /* __osEnqueueThread */
void func_8002670C(void);                               /* __osDispatchThread (never returns) */

/* CP0 Status ($12) and FPU control/status ($31). */
static inline u32 getStatus(void) { u32 v; __asm__ __volatile__("mfc0 %0, $12" : "=r"(v)); return v; }
static inline u32 getFpcsr(void) { u32 v; __asm__ __volatile__("cfc1 %0, $31" : "=r"(v)); return v; }
/* Store one live register, full 64 bits, into the context: one sd / sdc1 each. */
#define SAVE_GPR(reg, field, ctx) __asm__ __volatile__("sd " reg ", %0" : "=m"((ctx)->field))
#define SAVE_FPR(reg, field, ctx) __asm__ __volatile__("sdc1 " reg ", %0" : "=m"((ctx)->field))

/* __osEnqueueAndYield(OSThread **queue): the running thread gives up the CPU. Saves just
 * the callee-saved state (the caller expects t/a/v registers to be clobbered by a call),
 * puts the thread on `queue` (if not NULL) and jumps to __osDispatchThread. When the thread
 * is dispatched again, eret goes to the saved pc = its return address, with Status.EXL set
 * here so that eret is legal, i.e. the call simply "returns". */
void func_800265AC(OSThread **queue) {
    OSThread *t = D_80037250;
    OSThreadContext *c = &t->context;
    u32 sr, imask, rcp;

    c->sr = getStatus() | 2;               /* Status | EXL */
    /* In the original these are the caller's registers at the moment of the call
     * (this routine has no stack frame and touches none of them first). */
    SAVE_GPR("$16", s0, c); SAVE_GPR("$17", s1, c); SAVE_GPR("$18", s2, c); SAVE_GPR("$19", s3, c);
    SAVE_GPR("$20", s4, c); SAVE_GPR("$21", s5, c); SAVE_GPR("$22", s6, c); SAVE_GPR("$23", s7, c);
    SAVE_GPR("$28", gp, c); SAVE_GPR("$29", sp, c); SAVE_GPR("$30", s8, c); SAVE_GPR("$31", ra, c);
    c->pc = (u32)__builtin_return_address(0);  /* sw $ra, pc: resume where we were called from */

    if (t->fp != 0) {                      /* FPU used: save FCSR and the callee-saved f20..f30 */
        c->fpcsr = getFpcsr();
        SAVE_FPR("$f20", fp20, c); SAVE_FPR("$f22", fp22, c); SAVE_FPR("$f24", fp24, c);
        SAVE_FPR("$f26", fp26, c); SAVE_FPR("$f28", fp28, c); SAVE_FPR("$f30", fp30, c);
    }

    /* If any CPU interrupt is enabled in the saved SR, OR back the bits that the global mask
     * had disabled (undoes the masking __osDispatchThread applied; libultra's known-imperfect
     * scheme, see osSetIntMask). */
    sr = c->sr;
    imask = sr & 0xFF00;
    if (imask != 0) {
        imask |= ~D_80038810 & 0xFF00;
        c->sr = (sr & 0xFFFF00FF) | imask;
    }

    /* Same idea for the RCP interrupt mask: current MI mask, plus the thread's previously
     * saved RCP bits that the global mask has disabled. */
    rcp = D_A430000C;
    if (rcp != 0) {
        rcp |= ~(D_80038810 >> 16) & 0x3F & c->rcp;
    }
    c->rcp = rcp;

    if (queue != NULL) {
        func_800266B4(queue, t);           /* a0 = queue, a1 = running thread */
    }
    func_8002670C();                       /* j __osDispatchThread: does not return here */
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl func_800265AC\n"
    ".ent func_800265AC\n"
    "func_800265AC:\n"
    "lui $a1, %hi(D_80037250)\n"
    "lw $a1, %lo(D_80037250)($a1)\n"
    "mfc0 $t0, $12 /* handwritten instruction */\n"
    "ori $t0, $t0, 0x2\n"
    "sw $t0, 0x118($a1)\n"
    "sd $s0, 0x98($a1)\n"
    "sd $s1, 0xA0($a1)\n"
    "sd $s2, 0xA8($a1)\n"
    "sd $s3, 0xB0($a1)\n"
    "sd $s4, 0xB8($a1)\n"
    "sd $s5, 0xC0($a1)\n"
    "sd $s6, 0xC8($a1)\n"
    "sd $s7, 0xD0($a1)\n"
    "sd $gp, 0xE8($a1)\n"
    "sd $sp, 0xF0($a1)\n"
    "sd $fp, 0xF8($a1)\n"
    "sd $ra, 0x100($a1)\n"
    "sw $ra, 0x11C($a1)\n"
    "lw $k1, 0x18($a1) /* handwritten instruction */\n"
    "beqz $k1, .L80026624 /* handwritten instruction */\n"
    "nop\n"
    "cfc1 $k1, $31\n"
    "nop\n"
    "sw $k1, 0x12C($a1) /* handwritten instruction */\n"
    "sdc1 $fs0, 0x180($a1)\n"
    "sdc1 $fs1, 0x188($a1)\n"
    "sdc1 $fs2, 0x190($a1)\n"
    "sdc1 $fs3, 0x198($a1)\n"
    "sdc1 $fs4, 0x1A0($a1)\n"
    "sdc1 $fs5, 0x1A8($a1)\n"
    ".L80026624:\n"
    "lw $k1, 0x118($a1) /* handwritten instruction */\n"
    "andi $t1, $k1, 0xFF00 /* handwritten instruction */\n"
    "beqz $t1, .L80026664\n"
    "nop\n"
    "lui $t0, %hi(D_80038810)\n"
    "addiu $t0, $t0, %lo(D_80038810)\n"
    "lw $t0, 0x0($t0)\n"
    "addiu $at, $zero, -0x1\n"
    "xor $t0, $t0, $at\n"
    "andi $t0, $t0, 0xFF00\n"
    "or $t1, $t1, $t0\n"
    "lui $at, (0xFFFF00FF >> 16)\n"
    "ori $at, $at, (0xFFFF00FF & 0xFFFF)\n"
    "and $k1, $k1, $at\n"
    "or $k1, $k1, $t1\n"
    "sw $k1, 0x118($a1) /* handwritten instruction */\n"
    ".L80026664:\n"
    "lui $k1, %hi(D_A430000C) /* handwritten instruction */\n"
    "lw $k1, %lo(D_A430000C)($k1) /* handwritten instruction */\n"
    "beqz $k1, .L8002669C /* handwritten instruction */\n"
    "nop\n"
    "lui $k0, %hi(D_80038810) /* handwritten instruction */\n"
    "addiu $k0, $k0, %lo(D_80038810) /* handwritten instruction */\n"
    "lw $k0, 0x0($k0) /* handwritten instruction */\n"
    "srl $k0, $k0, 16\n"
    "addiu $at, $zero, -0x1\n"
    "xor $k0, $k0, $at\n"
    "andi $k0, $k0, 0x3F /* handwritten instruction */\n"
    "lw $t0, 0x128($a1)\n"
    "and $k0, $k0, $t0\n"
    "or $k1, $k1, $k0\n"
    ".L8002669C:\n"
    "beqz $a0, .L800266AC\n"
    "sw $k1, 0x128($a1) /* handwritten instruction */\n"
    "jal func_800266B4\n"
    "nop\n"
    ".L800266AC:\n"
    "j func_8002670C\n"
    "nop\n"
    ".end func_800265AC\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
