/* @header
 * __osExceptionPreamble  (originally func_80025F30)
 * VRAM 0x80025F30 | ROM 0x26B30 | size 0x58C
 * asm: asm/nonmatchings/main/__osExceptionPreamble.s
 */
/* __osExceptionPreamble: libultra __osExceptionPreamble + __osException (exceptasm.s, 2.0I _FINALROM build), the
 * single CPU exception / interrupt handler of the whole game. The first 4 instructions are the preamble:
 * __osInitialize (osInitialize.c) copies those 16 bytes to the R4300 vectors 0x80000000 (TLB
 * refill), 0x80000080 (XTLB), 0x80000100 (cache error) and 0x80000180 (general exception); they just jump
 * to __osExceptionPreamble+0x10, the handler proper. The handler (1) spills $at, SR, $t0-$t2 into the scratch
 * frame __osThreadSave and disables interrupts (SR &= ~(IE|EXL)); (2) copies those into the
 * running thread (__osRunningThread) and saves every other GPR, LO/HI, EPC (pc) and, if the
 * thread has used the FPU (thread->fp), FCSR and f0-f30; while saving it re-ORs into the saved SR / RCP
 * mask the bits the global mask __OSGlobalIntMask had removed; (3) reads Cause: ExcCode 9
 * (break) sets OS_FLAG_CPU_BREAK and posts OS_EVENT_CPU_BREAK; ExcCode 11 (coprocessor unusable) goes to
 * handle_CpU (the separate 13-instruction symbol right after send_mesg) which lazily grants
 * CP1 (thread->fp = 1, SR |= CU1) and resumes the thread; any other non-interrupt code is a fault (thread
 * stopped, OS_FLAG_FAULT, BadVAddr saved, __osFaultedThread set, OS_EVENT_FAULT posted).
 * (4) Interrupts are served highest IP bit first through __osIntOffTable and the jump table
 * __osIntTable (jtbl_8003B930): timer (rewrite Compare, OS_EVENT_COUNTER), dev-only IP5/IP6 (dropped),
 * PreNMI (sets __osShutdown once, posts OS_EVENT_PRENMI, masks IM4 in both threads), cart/64DD
 * (hook in __osHwIntTable[1], __osHwIntTable), software 1/2 (clear the Cause bit), RCP: MI_INTR_REG &
 * global mask, each of SP/VI/AI/SI/PI/DP is acknowledged at its hardware register and posted (SP splits
 * into OS_EVENT_SP vs OS_EVENT_SP_BREAK on SP_STATUS yielded/taskdone; PI first calls the
 * __osPiIntTable hook __osPiIntTable). Every post goes through send_mesg with MESG(event) =
 * event*8. (5) Redispatch: if the run queue head (__osRunQueue) now outranks the interrupted
 * thread it is enqueued by priority, otherwise it is pushed back at the head; then j __osDispatchThread
 * (__osDispatchThread). Must be asm: it runs on no stack of its own, may only touch $k0/$k1 before saving,
 * and saves/restores registers a compiler owns. Differences from ultralib exceptasm.s: matches the
 * VERSION_J+ cart/PI hook code, no kdebug/rdb/kmc blocks (_FINALROM). Quirk inherited from that source
 * (not a ROM difference): ultralib writes `1: li a0, MESG(OS_EVENT_CART); jal send_mesg` in .set reorder
 * mode and the assembler moved the li into the delay slot of the earlier `beqz v0, 1f`, so on the cart
 * path with no hook (beqz t2 jumps straight to `jal send_mesg`) $a0 is never set and send_mesg gets a
 * stale $a0 (whatever the previous send_mesg or its helpers left there).
 * Known libultra bug kept: the RCP handler overwrites $t0 (the Cause copy) with __OSGlobalIntMask>>16, so
 * a software interrupt serviced after an RCP one writes a wrong value to Cause. The NON_MATCHING C below
 * is a faithful description in C (labels and switch = the asm's branches and jump table); it cannot run
 * as a compiled function (prologue would touch the interrupted thread's sp/ra before they are saved). */
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
/* __OSHWIntr: callback plus the stack pointer it runs on (__osSetHWIntrRoutine / PI hook). */
typedef struct { s32 (*handler)(); void *sp; } OSHWIntr;

extern OSThread __osThreadSave;    /* scratch frame for the first few registers */
extern OSThread *__osRunQueue;
extern OSThread *__osRunningThread;
extern OSThread *__osFaultedThread;
extern u32 __OSGlobalIntMask;         /* bits 15..8 CPU IM, 21..16 RCP mask */
extern s32 __osShutdown;         /* set at the first PreNMI */
extern OSHWIntr __osHwIntTable[5]; /* __osHwIntTable (entry 1 = cart / 64DD) */
extern OSHWIntr __osPiIntTable;    /* __osPiIntTable (PI hook, VERSION_J and later) */
extern u8 __osIntOffTable[32];      /* pending IP bits -> byte offset into the jump table */
extern vu32 D_A4300000;        /* MI_MODE_REG (write 0x800 = MI_CLR_DP_INTR) */
extern vu32 D_A4300008;        /* MI_INTR_REG (pending RCP interrupts) */
extern vu32 D_A430000C;        /* MI_INTR_MASK_REG */
extern vu32 D_A4040010;        /* SP_STATUS_REG */
extern vu32 D_A4400010;        /* VI_CURRENT_REG (write clears the VI interrupt) */
extern vu32 D_A450000C;        /* AI_STATUS_REG (write clears the AI interrupt) */
extern vu32 D_A4600010;        /* PI_STATUS_REG (write 2 = PI_CLR_INTR) */
extern vu32 D_A4800018;        /* SI_STATUS_REG (write clears the SI interrupt) */
void send_mesg(s32 eventOffset);                    /* send_mesg(OS_EVENT_xxx * 8) */
void __osEnqueueThread(OSThread **queue, OSThread *thread); /* __osEnqueueThread */
void __osDispatchThread(void);                               /* __osDispatchThread (never returns) */

/* Byte offsets into __osEventStateTab: MESG(OS_EVENT_xxx) = event * 8. */
#define MESG_SW1        0x00
#define MESG_SW2        0x08
#define MESG_CART       0x10
#define MESG_COUNTER    0x18
#define MESG_SP         0x20
#define MESG_SI         0x28
#define MESG_AI         0x30
#define MESG_VI         0x38
#define MESG_PI         0x40
#define MESG_DP         0x48
#define MESG_CPU_BREAK  0x50
#define MESG_SP_BREAK   0x58
#define MESG_FAULT      0x60
#define MESG_PRENMI     0x70

/* CP0: Index $0 .. BadVAddr $8, Compare $11, Status $12, Cause $13, EPC $14; FPU FCSR $31. */
static inline u32 getStatus(void) { u32 v; __asm__ __volatile__("mfc0 %0, $12" : "=r"(v)); return v; }
static inline void setStatus(u32 v) { __asm__ __volatile__("mtc0 %0, $12" : : "r"(v)); }
static inline u32 getCause(void) { u32 v; __asm__ __volatile__("mfc0 %0, $13" : "=r"(v)); return v; }
static inline void setCause(u32 v) { __asm__ __volatile__("mtc0 %0, $13" : : "r"(v)); }
static inline u32 getEPC(void) { u32 v; __asm__ __volatile__("mfc0 %0, $14" : "=r"(v)); return v; }
static inline u32 getBadVAddr(void) { u32 v; __asm__ __volatile__("mfc0 %0, $8" : "=r"(v)); return v; }
static inline u32 getCompare(void) { u32 v; __asm__ __volatile__("mfc0 %0, $11" : "=r"(v)); return v; }
static inline void setCompare(u32 v) { __asm__ __volatile__("mtc0 %0, $11" : : "r"(v)); }
static inline u32 getFpcsr(void) { u32 v; __asm__ __volatile__("cfc1 %0, $31" : "=r"(v)); return v; }
/* $v0 / $sp as they are at this point (used to set up the hook calls exactly like the asm). */
static inline u32 getV0(void) { u32 v; __asm__ __volatile__("move %0, $2" : "=r"(v)); return v; }
static inline u32 getA0(void) { u32 v; __asm__ __volatile__("move %0, $4" : "=r"(v)); return v; }
static inline void setSp(void *v) { __asm__ __volatile__("move $29, %0" : : "r"(v)); }
/* Store one live register, full 64 bits, at byte offset `off` of `base`: one sd / sdc1 each. */
#define SAVE_GPR(reg, off, base) __asm__ __volatile__("sd " reg ", %1(%0)" : : "r"(base), "i"(off))
#define SAVE_FPR(reg, off, base) __asm__ __volatile__("sdc1 " reg ", %1(%0)" : : "r"(base), "i"(off))
/* mflo/mfhi go through $t0 in the original (t0 was already saved). */
static inline void loToT0(void) { __asm__ __volatile__("mflo $8"); }
static inline void hiToT0(void) { __asm__ __volatile__("mfhi $8"); }

/* __osExceptionPreamble + __osException. Entry is through the 4-instruction preamble that
 * __osInitialize copies to the exception vectors (lui/addiu $k0 = __osExceptionPreamble+0x10; jr $k0;
 * nop); everything below is the handler proper at __osExceptionPreamble+0x10. */
void __osExceptionPreamble(void) {
    register OSThread *k0 asm("$26");
    register u32 k1 asm("$27");
    OSThread *save = &__osThreadSave;
    u32 t0;          /* the asm's $t0: Cause, but clobbered by the RCP handler (see below) */
    u32 s0;          /* pending & enabled CPU interrupts still to service */
    u32 s1;          /* pending & enabled RCP (MI) interrupts still to service */
    u32 bits, rcp;
    s32 idx;
    OSHWIntr *hw;

    /* ---- 1. Free a few registers: at, SR, t0..t2 into the scratch frame. ---- */
    k0 = save;
    __asm__ __volatile__(".set noat\n\tsd $1, %1(%0)\n\t.set at" : : "r"(k0), "i"(0x20));
    k1 = getStatus();
    k0->context.sr = k1;
    setStatus(k1 & ~3);                       /* clear IE | EXL: interrupts off, kernel mode */
    SAVE_GPR("$8", 0x58, k0); SAVE_GPR("$9", 0x60, k0); SAVE_GPR("$10", 0x68, k0);
    k0->fp = 0;                               /* scratch frame: "FPU unused" (never read back) */
    t0 = getCause();                          /* dead read, a leftover of the debug build */

    /* ---- 2. Save the full context of the interrupted (running) thread. ---- */
    {
        OSThread *from = k0;
        k0 = __osRunningThread;
        k0->context.at = from->context.at;
        /* one 64-bit ld/sd: copies sr AND the (stale) pc word next to it; pc is rewritten below */
        *(u64 *)&k0->context.sr = *(u64 *)&from->context.sr;
        k0->context.t0 = from->context.t0;
        k0->context.t1 = from->context.t1;
        k0->context.t2 = from->context.t2;
    }
    SAVE_GPR("$2", 0x28, k0);  SAVE_GPR("$3", 0x30, k0);
    SAVE_GPR("$4", 0x38, k0);  SAVE_GPR("$5", 0x40, k0);  SAVE_GPR("$6", 0x48, k0);  SAVE_GPR("$7", 0x50, k0);
    SAVE_GPR("$11", 0x70, k0); SAVE_GPR("$12", 0x78, k0); SAVE_GPR("$13", 0x80, k0);
    SAVE_GPR("$14", 0x88, k0); SAVE_GPR("$15", 0x90, k0);
    SAVE_GPR("$16", 0x98, k0); SAVE_GPR("$17", 0xA0, k0); SAVE_GPR("$18", 0xA8, k0); SAVE_GPR("$19", 0xB0, k0);
    SAVE_GPR("$20", 0xB8, k0); SAVE_GPR("$21", 0xC0, k0); SAVE_GPR("$22", 0xC8, k0); SAVE_GPR("$23", 0xD0, k0);
    SAVE_GPR("$24", 0xD8, k0); SAVE_GPR("$25", 0xE0, k0); SAVE_GPR("$28", 0xE8, k0); SAVE_GPR("$29", 0xF0, k0);
    SAVE_GPR("$30", 0xF8, k0); SAVE_GPR("$31", 0x100, k0);
    loToT0(); SAVE_GPR("$8", 0x108, k0);
    hiToT0(); SAVE_GPR("$8", 0x110, k0);

    /* Saved SR: if any CPU interrupt is enabled, OR in the bits the global mask had turned
     * off (undo the masking done at dispatch). k1 keeps the thread's IM ANDed with the
     * global mask: those are the interrupts this handler will service. */
    k1 = k0->context.sr;
    bits = k1 & 0xFF00;
    if (bits != 0) {
        u32 gm = __OSGlobalIntMask;
        k0->context.sr = (k1 & 0xFFFF00FF) | (bits | (~gm & 0xFF00));
        k1 = (k1 & 0xFFFF00FF) | (bits & (gm & 0xFF00));
    }
    /* Saved RCP mask: current MI mask plus the old saved bits the global mask disabled. */
    rcp = D_A430000C;
    if (rcp != 0) {
        rcp |= (~(__OSGlobalIntMask >> 16) & 0x3F) & k0->context.rcp;
    }
    k0->context.rcp = rcp;
    k0->context.pc = getEPC();
    if (k0->fp != 0) {                        /* thread owns the FPU: FCSR + all 16 even FPRs */
        k0->context.fpcsr = getFpcsr();
        SAVE_FPR("$f0", 0x130, k0);  SAVE_FPR("$f2", 0x138, k0);  SAVE_FPR("$f4", 0x140, k0);
        SAVE_FPR("$f6", 0x148, k0);  SAVE_FPR("$f8", 0x150, k0);  SAVE_FPR("$f10", 0x158, k0);
        SAVE_FPR("$f12", 0x160, k0); SAVE_FPR("$f14", 0x168, k0); SAVE_FPR("$f16", 0x170, k0);
        SAVE_FPR("$f18", 0x178, k0); SAVE_FPR("$f20", 0x180, k0); SAVE_FPR("$f22", 0x188, k0);
        SAVE_FPR("$f24", 0x190, k0); SAVE_FPR("$f26", 0x198, k0); SAVE_FPR("$f28", 0x1A0, k0);
        SAVE_FPR("$f30", 0x1A8, k0);
    }

    /* ---- 3. Classify by Cause.ExcCode (bits 6..2). ---- */
    t0 = getCause();
    k0->context.cause = t0;
    k0->state = 2;                            /* OS_STATE_RUNNABLE */
    bits = t0 & 0x7C;
    if (bits == 0x24) goto handle_break;      /* EXC_BREAK (9 << 2) */
    if (bits == 0x2C) goto handle_CpU;        /* EXC_CPU (11 << 2), code at handle_CpU */
    if (bits != 0) goto panic;                /* not EXC_INT: TLB miss, address error, ... */

    /* ---- 4. Interrupt: service enabled & pending IP bits, highest first. ---- */
    s0 = k1 & t0;
    for (;;) {
        bits = s0 & 0xFF00;
        idx = bits >> 12;                     /* IP4..IP7 (Cause bits 12..15) -> 1..15 */
        if (idx == 0) {
            idx = (bits >> 8) + 16;           /* IP0..IP3 (bits 8..11) -> 16..31; 16 = none */
        }
        /* The asm does lw t2, jtbl_8003B930[__osIntOffTable[idx]]; jr t2. */
        switch (__osIntOffTable[idx]) {
        case 0x00:                            /* nothing left: redispatch */
            goto redispatch;
        case 0x18:                            /* IP5, 0x2000 (dev hardware only): just drop it */
            s0 &= ~0x2000;
            continue;
        case 0x1C:                            /* IP6, 0x4000 (dev hardware only): just drop it */
            s0 &= ~0x4000;
            continue;
        case 0x20:                            /* IP7, 0x8000 timer: Count reached Compare */
            setCompare(getCompare());         /* rewriting Compare acknowledges the interrupt */
            send_mesg(MESG_COUNTER);
            s0 &= ~0x8000;
            continue;
        case 0x10:                            /* IP3, 0x800 cart (64DD) */
            s0 &= ~0x800;
            hw = &__osHwIntTable[1];
            if (hw->handler == NULL) {
                /* Quirk of the ultralib source as assembled (.set reorder moved
                 * `li a0, 0x10` into the delay slot of the later `beqz v0`), so this
                 * path posts with whatever $a0 already holds. */
                send_mesg(getA0());
                continue;
            }
            setSp(hw->sp);                    /* the hook runs on its own stack */
            if (hw->handler() != 0) {
                goto redispatch;              /* hook handled it: no message */
            }
            send_mesg(MESG_CART);
            continue;
        case 0x0C:                            /* IP2, 0x400 RCP: look at MI_INTR_REG */
            t0 = __OSGlobalIntMask >> 16;            /* libultra bug kept: clobbers the Cause copy */
            s1 = D_A4300008 & t0;
            if (s1 & 0x01) {                  /* SP */
                u32 status;
                s1 &= 0x3E;
                status = D_A4040010;
                D_A4040010 = 0x8008;          /* SP_CLR_INTR | SP_CLR_SIG3 */
                if (status & 0x300) {         /* SP_STATUS_YIELDED | SP_STATUS_TASKDONE */
                    send_mesg(MESG_SP);
                } else {
                    send_mesg(MESG_SP_BREAK);
                }
                if (s1 == 0) goto rcp_done;
            }
            if (s1 & 0x08) {                  /* VI */
                s1 &= 0x37;
                D_A4400010 = 0;
                send_mesg(MESG_VI);
                if (s1 == 0) goto rcp_done;
            }
            if (s1 & 0x04) {                  /* AI */
                s1 &= 0x3B;
                D_A450000C = 1;
                send_mesg(MESG_AI);
                if (s1 == 0) goto rcp_done;
            }
            if (s1 & 0x02) {                  /* SI */
                s1 &= 0x3D;
                D_A4800018 = 0;
                send_mesg(MESG_SI);
                if (s1 == 0) goto rcp_done;
            }
            if (s1 & 0x10) {                  /* PI */
                s1 &= 0x2F;
                D_A4600010 = 2;               /* PI_CLR_INTR */
                hw = &__osPiIntTable;
                if (hw->handler == NULL) {
                    send_mesg(MESG_PI);
                } else {
                    u32 arg;
                    setSp(hw->sp);
                    arg = getV0();            /* a0 = whatever $v0 holds (move a0, v0) */
                    if (hw->handler(arg) == 0) {
                        send_mesg(MESG_PI); /* hook returned 0: still post the message */
                    }
                }
                if (s1 == 0) goto rcp_done;
            }
            if (s1 & 0x20) {                  /* DP */
                s1 &= 0x1F;
                D_A4300000 = 0x800;           /* MI_CLR_DP_INTR */
                send_mesg(MESG_DP);
            }
rcp_done:
            s0 &= ~0x400;
            continue;
        case 0x14:                            /* IP4, 0x1000 PreNMI: reset button pressed */
            k1 = k0->context.sr & ~0x1000;    /* SR.IM4 off: the interrupted thread won't take it again */
            k0->context.sr = k1;
            if (__osShutdown != 0) {            /* already shutting down */
                s0 &= ~0x1000;
                goto redispatch;
            }
            __osShutdown = 1;
            send_mesg(MESG_PRENMI);
            s0 &= ~0x1000;
            k1 = __osRunQueue->context.sr & ~0x1000; /* ... nor the thread about to run */
            __osRunQueue->context.sr = k1;
            goto redispatch;
        case 0x08:                            /* IP1, 0x200 software interrupt 2 */
            t0 &= ~0x200;
            setCause(t0);                     /* stale/clobbered t0 if an RCP interrupt ran first */
            send_mesg(MESG_SW2);
            s0 &= ~0x200;
            continue;
        case 0x04:                            /* IP0, 0x100 software interrupt 1 */
            t0 &= ~0x100;
            setCause(t0);
            send_mesg(MESG_SW1);
            s0 &= ~0x100;
            continue;
        }
    }

handle_CpU:
    /* Coprocessor Unusable: only CP1 (FPU) is lazily granted, anything else is a fault.
     * In the ROM this block is the separate symbol handle_CpU. */
    if (((t0 & 0x30000000) >> 28) != 1) goto panic;   /* Cause.CE != 1 */
    k0->fp = 1;                                         /* thread now owns FPU state */
    k1 = k0->context.sr | 0x20000000;                   /* SR_CU1 */
    k0->context.sr = k1;
    goto enqueueRunning;

handle_break:
    k0->flags = 1;                            /* OS_FLAG_CPU_BREAK */
    send_mesg(MESG_CPU_BREAK);
    goto redispatch;

redispatch:
    /* Keep running the interrupted thread unless a woken thread now outranks it. */
    if (k0->priority < __osRunQueue->priority) {
        __osEnqueueThread(&__osRunQueue, k0);       /* back into the run queue by priority */
        __osDispatchThread();                      /* j __osDispatchThread */
    }
enqueueRunning:
    k0->next = __osRunQueue;                    /* push at the head (ahead of equal priority) */
    __osRunQueue = k0;
    __osDispatchThread();                          /* j __osDispatchThread */

panic:
    /* Unhandled exception: stop the thread and post OS_EVENT_FAULT (game's fault thread). */
    __osFaultedThread = k0;
    k0->state = 1;                            /* OS_STATE_STOPPED */
    k0->flags = 2;                            /* OS_FLAG_FAULT */
    k0->context.badvaddr = getBadVAddr();
    send_mesg(MESG_FAULT);
    __osDispatchThread();                          /* j __osDispatchThread */
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl __osExceptionPreamble\n"
    ".ent __osExceptionPreamble\n"
    "__osExceptionPreamble:\n"
    "lui $k0, %hi(__osExceptionPreamble + 0x10) /* handwritten instruction */\n"
    "addiu $k0, $k0, %lo(__osExceptionPreamble + 0x10) /* handwritten instruction */\n"
    "jr $k0\n"
    "nop\n"
    "lui $k0, %hi(__osThreadSave) /* handwritten instruction */\n"
    "addiu $k0, $k0, %lo(__osThreadSave) /* handwritten instruction */\n"
    "sd $at, 0x20($k0) /* handwritten instruction */\n"
    "mfc0 $k1, $12 /* handwritten instruction */\n"
    "sw $k1, 0x118($k0) /* handwritten instruction */\n"
    "addiu $at, $zero, -0x4\n"
    "and $k1, $k1, $at\n"
    "mtc0 $k1, $12 /* handwritten instruction */\n"
    "sd $t0, 0x58($k0) /* handwritten instruction */\n"
    "sd $t1, 0x60($k0) /* handwritten instruction */\n"
    "sd $t2, 0x68($k0) /* handwritten instruction */\n"
    "sw $zero, 0x18($k0) /* handwritten instruction */\n"
    "mfc0 $t0, $13 /* handwritten instruction */\n"
    "addu $t0, $k0, $zero\n"
    "lui $k0, %hi(__osRunningThread) /* handwritten instruction */\n"
    "lw $k0, %lo(__osRunningThread)($k0) /* handwritten instruction */\n"
    "ld $t1, 0x20($t0)\n"
    "sd $t1, 0x20($k0) /* handwritten instruction */\n"
    "ld $t1, 0x118($t0)\n"
    "sd $t1, 0x118($k0) /* handwritten instruction */\n"
    "ld $t1, 0x58($t0)\n"
    "sd $t1, 0x58($k0) /* handwritten instruction */\n"
    "ld $t1, 0x60($t0)\n"
    "sd $t1, 0x60($k0) /* handwritten instruction */\n"
    "ld $t1, 0x68($t0)\n"
    "sd $t1, 0x68($k0) /* handwritten instruction */\n"
    "sd $v0, 0x28($k0) /* handwritten instruction */\n"
    "sd $v1, 0x30($k0) /* handwritten instruction */\n"
    "sd $a0, 0x38($k0) /* handwritten instruction */\n"
    "sd $a1, 0x40($k0) /* handwritten instruction */\n"
    "sd $a2, 0x48($k0) /* handwritten instruction */\n"
    "sd $a3, 0x50($k0) /* handwritten instruction */\n"
    "sd $t3, 0x70($k0) /* handwritten instruction */\n"
    "sd $t4, 0x78($k0) /* handwritten instruction */\n"
    "sd $t5, 0x80($k0) /* handwritten instruction */\n"
    "sd $t6, 0x88($k0) /* handwritten instruction */\n"
    "sd $t7, 0x90($k0) /* handwritten instruction */\n"
    "sd $s0, 0x98($k0) /* handwritten instruction */\n"
    "sd $s1, 0xA0($k0) /* handwritten instruction */\n"
    "sd $s2, 0xA8($k0) /* handwritten instruction */\n"
    "sd $s3, 0xB0($k0) /* handwritten instruction */\n"
    "sd $s4, 0xB8($k0) /* handwritten instruction */\n"
    "sd $s5, 0xC0($k0) /* handwritten instruction */\n"
    "sd $s6, 0xC8($k0) /* handwritten instruction */\n"
    "sd $s7, 0xD0($k0) /* handwritten instruction */\n"
    "sd $t8, 0xD8($k0) /* handwritten instruction */\n"
    "sd $t9, 0xE0($k0) /* handwritten instruction */\n"
    "sd $gp, 0xE8($k0) /* handwritten instruction */\n"
    "sd $sp, 0xF0($k0) /* handwritten instruction */\n"
    "sd $fp, 0xF8($k0) /* handwritten instruction */\n"
    "sd $ra, 0x100($k0) /* handwritten instruction */\n"
    "mflo $t0\n"
    "sd $t0, 0x108($k0) /* handwritten instruction */\n"
    "mfhi $t0\n"
    "sd $t0, 0x110($k0) /* handwritten instruction */\n"
    "lw $k1, 0x118($k0) /* handwritten instruction */\n"
    "andi $t1, $k1, 0xFF00 /* handwritten instruction */\n"
    "beqz $t1, .L80026074\n"
    "nop\n"
    "lui $t0, %hi(__OSGlobalIntMask)\n"
    "addiu $t0, $t0, %lo(__OSGlobalIntMask)\n"
    "lw $t0, 0x0($t0)\n"
    "addiu $at, $zero, -0x1\n"
    "xor $t2, $t0, $at\n"
    "andi $t2, $t2, 0xFF00\n"
    "or $t4, $t1, $t2\n"
    "lui $at, (0xFFFF00FF >> 16)\n"
    "ori $at, $at, (0xFFFF00FF & 0xFFFF)\n"
    "and $t3, $k1, $at\n"
    "or $t3, $t3, $t4\n"
    "sw $t3, 0x118($k0) /* handwritten instruction */\n"
    "andi $t0, $t0, 0xFF00\n"
    "and $t1, $t1, $t0\n"
    "lui $at, (0xFFFF00FF >> 16)\n"
    "ori $at, $at, (0xFFFF00FF & 0xFFFF)\n"
    "and $k1, $k1, $at\n"
    "or $k1, $k1, $t1\n"
    ".L80026074:\n"
    "lui $t1, %hi(D_A430000C)\n"
    "lw $t1, %lo(D_A430000C)($t1)\n"
    "beqz $t1, .L800260AC\n"
    "nop\n"
    "lui $t0, %hi(__OSGlobalIntMask)\n"
    "addiu $t0, $t0, %lo(__OSGlobalIntMask)\n"
    "lw $t0, 0x0($t0)\n"
    "srl $t0, $t0, 16\n"
    "addiu $at, $zero, -0x1\n"
    "xor $t0, $t0, $at\n"
    "andi $t0, $t0, 0x3F\n"
    "lw $t4, 0x128($k0) /* handwritten instruction */\n"
    "and $t0, $t0, $t4\n"
    "or $t1, $t1, $t0\n"
    ".L800260AC:\n"
    "sw $t1, 0x128($k0) /* handwritten instruction */\n"
    "mfc0 $t0, $14 /* handwritten instruction */\n"
    "sw $t0, 0x11C($k0) /* handwritten instruction */\n"
    "lw $t0, 0x18($k0) /* handwritten instruction */\n"
    "beqz $t0, .L80026110\n"
    "nop\n"
    "cfc1 $t0, $31\n"
    "nop\n"
    "sw $t0, 0x12C($k0) /* handwritten instruction */\n"
    "sdc1 $fv0, 0x130($k0)\n"
    "sdc1 $fv1, 0x138($k0)\n"
    "sdc1 $ft0, 0x140($k0)\n"
    "sdc1 $ft1, 0x148($k0)\n"
    "sdc1 $ft2, 0x150($k0)\n"
    "sdc1 $ft3, 0x158($k0)\n"
    "sdc1 $fa0, 0x160($k0)\n"
    "sdc1 $fa1, 0x168($k0)\n"
    "sdc1 $ft4, 0x170($k0)\n"
    "sdc1 $ft5, 0x178($k0)\n"
    "sdc1 $fs0, 0x180($k0)\n"
    "sdc1 $fs1, 0x188($k0)\n"
    "sdc1 $fs2, 0x190($k0)\n"
    "sdc1 $fs3, 0x198($k0)\n"
    "sdc1 $fs4, 0x1A0($k0)\n"
    "sdc1 $fs5, 0x1A8($k0)\n"
    ".L80026110:\n"
    "mfc0 $t0, $13 /* handwritten instruction */\n"
    "sw $t0, 0x120($k0) /* handwritten instruction */\n"
    "addiu $t1, $zero, 0x2\n"
    "sh $t1, 0x10($k0) /* handwritten instruction */\n"
    "andi $t1, $t0, 0x7C\n"
    "addiu $t2, $zero, 0x24\n"
    "beq $t1, $t2, .L80026428\n"
    "nop\n"
    "addiu $t2, $zero, 0x2C\n"
    ".word 0x112A0110 /* beq handle_CpU: target outside this function */\n"
    "nop\n"
    "addiu $t2, $zero, 0x0\n"
    "bne $t1, $t2, .L8002648C\n"
    "nop\n"
    "and $s0, $k1, $t0\n"
    ".L8002614C:\n"
    "andi $t1, $s0, 0xFF00\n"
    "srl $t2, $t1, 12\n"
    "bnez $t2, .L80026164\n"
    "nop\n"
    "srl $t2, $t1, 8\n"
    "addi $t2, $t2, 0x10 /* handwritten instruction */\n"
    ".L80026164:\n"
    "lui $at, %hi(__osIntOffTable)\n"
    "addu $at, $at, $t2\n"
    "lbu $t2, %lo(__osIntOffTable)($at)\n"
    "lui $at, %hi(jtbl_8003B930)\n"
    "addu $at, $at, $t2\n"
    "lw $t2, %lo(jtbl_8003B930)($at)\n"
    "jr $t2\n"
    "nop\n"
    "addiu $at, $zero, -0x2001\n"
    "b .L8002614C\n"
    "and $s0, $s0, $at\n"
    "addiu $at, $zero, -0x4001\n"
    "b .L8002614C\n"
    "and $s0, $s0, $at\n"
    "mfc0 $t1, $11 /* handwritten instruction */\n"
    "mtc0 $t1, $11 /* handwritten instruction */\n"
    "addiu $a0, $zero, 0x18\n"
    "jal send_mesg\n"
    "nop\n"
    "lui $at, (0xFFFF7FFF >> 16)\n"
    "ori $at, $at, (0xFFFF7FFF & 0xFFFF)\n"
    "b .L8002614C\n"
    "and $s0, $s0, $at\n"
    "addiu $at, $zero, -0x801\n"
    "and $s0, $s0, $at\n"
    "lui $t1, %hi(__osHwIntTable)\n"
    "addiu $t1, $t1, %lo(__osHwIntTable)\n"
    "addi $t1, $t1, 0x8 /* handwritten instruction */\n"
    "lw $t2, 0x0($t1)\n"
    "beqz $t2, .L800261F8\n"
    "nop\n"
    "jalr $t2\n"
    "lw $sp, 0x4($t1)\n"
    "beqz $v0, .L800261F8\n"
    "addiu $a0, $zero, 0x10\n"
    "b .L80026440\n"
    "nop\n"
    ".L800261F8:\n"
    "jal send_mesg\n"
    "nop\n"
    "b .L8002614C\n"
    "nop\n"
    "lui $s1, %hi(D_A4300008)\n"
    "lw $s1, %lo(D_A4300008)($s1)\n"
    "lui $t0, %hi(__OSGlobalIntMask)\n"
    "addiu $t0, $t0, %lo(__OSGlobalIntMask)\n"
    "lw $t0, 0x0($t0)\n"
    "srl $t0, $t0, 16\n"
    "and $s1, $s1, $t0\n"
    "andi $t1, $s1, 0x1\n"
    "beqz $t1, .L8002627C\n"
    "nop\n"
    "andi $s1, $s1, 0x3E\n"
    "lui $t4, %hi(D_A4040010)\n"
    "lw $t4, %lo(D_A4040010)($t4)\n"
    "ori $t1, $zero, 0x8008\n"
    "lui $at, %hi(D_A4040010)\n"
    "sw $t1, %lo(D_A4040010)($at)\n"
    "andi $t4, $t4, 0x300\n"
    "beqz $t4, .L8002626C\n"
    "nop\n"
    "jal send_mesg\n"
    "addiu $a0, $zero, 0x20\n"
    "beqz $s1, .L80026370\n"
    "nop\n"
    "b .L8002627C\n"
    "nop\n"
    ".L8002626C:\n"
    "jal send_mesg\n"
    "addiu $a0, $zero, 0x58\n"
    "beqz $s1, .L80026370\n"
    "nop\n"
    ".L8002627C:\n"
    "andi $t1, $s1, 0x8\n"
    "beqz $t1, .L800262A4\n"
    "nop\n"
    "andi $s1, $s1, 0x37\n"
    "lui $at, %hi(D_A4400010)\n"
    "sw $zero, %lo(D_A4400010)($at)\n"
    "jal send_mesg\n"
    "addiu $a0, $zero, 0x38\n"
    "beqz $s1, .L80026370\n"
    "nop\n"
    ".L800262A4:\n"
    "andi $t1, $s1, 0x4\n"
    "beqz $t1, .L800262D0\n"
    "nop\n"
    "andi $s1, $s1, 0x3B\n"
    "addiu $t1, $zero, 0x1\n"
    "lui $at, %hi(D_A450000C)\n"
    "sw $t1, %lo(D_A450000C)($at)\n"
    "jal send_mesg\n"
    "addiu $a0, $zero, 0x30\n"
    "beqz $s1, .L80026370\n"
    "nop\n"
    ".L800262D0:\n"
    "andi $t1, $s1, 0x2\n"
    "beqz $t1, .L800262F8\n"
    "nop\n"
    "andi $s1, $s1, 0x3D\n"
    "lui $at, %hi(D_A4800018)\n"
    "sw $zero, %lo(D_A4800018)($at)\n"
    "jal send_mesg\n"
    "addiu $a0, $zero, 0x28\n"
    "beqz $s1, .L80026370\n"
    "nop\n"
    ".L800262F8:\n"
    "andi $t1, $s1, 0x10\n"
    "beqz $t1, .L8002634C\n"
    "nop\n"
    "andi $s1, $s1, 0x2F\n"
    "addiu $t1, $zero, 0x2\n"
    "lui $at, %hi(D_A4600010)\n"
    "sw $t1, %lo(D_A4600010)($at)\n"
    "lui $t1, %hi(__osPiIntTable)\n"
    "addiu $t1, $t1, %lo(__osPiIntTable)\n"
    "lw $t2, 0x0($t1)\n"
    "beqz $t2, .L8002633C\n"
    "nop\n"
    "lw $sp, 0x4($t1)\n"
    "jalr $t2\n"
    "addu $a0, $v0, $zero\n"
    "bnez $v0, .L80026344\n"
    "nop\n"
    ".L8002633C:\n"
    "jal send_mesg\n"
    "addiu $a0, $zero, 0x40\n"
    ".L80026344:\n"
    "beqz $s1, .L80026370\n"
    "nop\n"
    ".L8002634C:\n"
    "andi $t1, $s1, 0x20\n"
    "beqz $t1, .L80026370\n"
    "nop\n"
    "andi $s1, $s1, 0x1F\n"
    "addiu $t1, $zero, 0x800\n"
    "lui $at, %hi(D_A4300000)\n"
    "sw $t1, %lo(D_A4300000)($at)\n"
    "jal send_mesg\n"
    "addiu $a0, $zero, 0x48\n"
    ".L80026370:\n"
    "addiu $at, $zero, -0x401\n"
    "b .L8002614C\n"
    "and $s0, $s0, $at\n"
    "lw $k1, 0x118($k0) /* handwritten instruction */\n"
    "addiu $at, $zero, -0x1001\n"
    "and $k1, $k1, $at\n"
    "sw $k1, 0x118($k0) /* handwritten instruction */\n"
    "lui $t1, %hi(__osShutdown)\n"
    "addiu $t1, $t1, %lo(__osShutdown)\n"
    "lw $t2, 0x0($t1)\n"
    "beqz $t2, .L800263AC\n"
    "nop\n"
    "addiu $at, $zero, -0x1001\n"
    "b .L80026440\n"
    "and $s0, $s0, $at\n"
    ".L800263AC:\n"
    "addiu $t2, $zero, 0x1\n"
    "sw $t2, 0x0($t1)\n"
    "jal send_mesg\n"
    "addiu $a0, $zero, 0x70\n"
    "addiu $at, $zero, -0x1001\n"
    "and $s0, $s0, $at\n"
    "lui $t2, %hi(__osRunQueue)\n"
    "lw $t2, %lo(__osRunQueue)($t2)\n"
    "lw $k1, 0x118($t2) /* handwritten instruction */\n"
    "addiu $at, $zero, -0x1001\n"
    "and $k1, $k1, $at\n"
    "b .L80026440\n"
    "sw $k1, 0x118($t2) /* handwritten instruction */\n"
    "addiu $at, $zero, -0x201\n"
    "and $t0, $t0, $at\n"
    "mtc0 $t0, $13 /* handwritten instruction */\n"
    "addiu $a0, $zero, 0x8\n"
    "jal send_mesg\n"
    "nop\n"
    "addiu $at, $zero, -0x201\n"
    "b .L8002614C\n"
    "and $s0, $s0, $at\n"
    "addiu $at, $zero, -0x101\n"
    "and $t0, $t0, $at\n"
    "mtc0 $t0, $13 /* handwritten instruction */\n"
    "addiu $a0, $zero, 0x0\n"
    "jal send_mesg\n"
    "nop\n"
    "addiu $at, $zero, -0x101\n"
    "b .L8002614C\n"
    "and $s0, $s0, $at\n"
    ".L80026428:\n"
    "addiu $t1, $zero, 0x1\n"
    "sh $t1, 0x12($k0) /* handwritten instruction */\n"
    "jal send_mesg\n"
    "addiu $a0, $zero, 0x50\n"
    "b .L80026440\n"
    "nop\n"
    ".L80026440:\n"
    "lw $t1, 0x4($k0) /* handwritten instruction */\n"
    "lui $t2, %hi(__osRunQueue)\n"
    "lw $t2, %lo(__osRunQueue)($t2)\n"
    "lw $t3, 0x4($t2)\n"
    "slt $at, $t1, $t3\n"
    "beqz $at, .L80026474\n"
    "nop\n"
    "addu $a1, $k0, $zero\n"
    "lui $a0, %hi(__osRunQueue)\n"
    "jal __osEnqueueThread\n"
    "addiu $a0, $a0, %lo(__osRunQueue)\n"
    "j __osDispatchThread\n"
    "nop\n"
    ".L80026474:\n"
    "lui $t1, %hi(__osRunQueue)\n"
    "addiu $t1, $t1, %lo(__osRunQueue)\n"
    "lw $t2, 0x0($t1)\n"
    "sw $t2, 0x0($k0) /* handwritten instruction */\n"
    "j __osDispatchThread\n"
    "sw $k0, 0x0($t1) /* handwritten instruction */\n"
    ".L8002648C:\n"
    "lui $at, %hi(__osFaultedThread)\n"
    "sw $k0, %lo(__osFaultedThread)($at) /* handwritten instruction */\n"
    "addiu $t1, $zero, 0x1\n"
    "sh $t1, 0x10($k0) /* handwritten instruction */\n"
    "addiu $t1, $zero, 0x2\n"
    "sh $t1, 0x12($k0) /* handwritten instruction */\n"
    "mfc0 $t2, $8 /* handwritten instruction */\n"
    "sw $t2, 0x124($k0) /* handwritten instruction */\n"
    "jal send_mesg\n"
    "addiu $a0, $zero, 0x60\n"
    "j __osDispatchThread\n"
    "nop\n"
    ".end __osExceptionPreamble\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
