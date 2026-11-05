/* @header
 * func_8002BC40
 * VRAM 0x8002BC40 | ROM 0x2C840 | size 0x1F0
 * asm: asm/nonmatchings/main/func_8002BC40.s
 */
/* func_8002BC40: NOT CPU CODE. These 0x1F0 bytes are RSP (Reality Signal Processor) code that
 * the CPU only passes by address in OSTask structures:
 *  - bytes 0x000-0x0CF: libultra rspboot (rspbootTextStart, ultralib src/rsp/rspboot.s), linked
 *    at IMEM 0x04001000. submitGraphicsTask (gfx task) and func_80016A30 (audio task) set
 *    t.ucode_boot = func_8002BC40 and t.ucode_boot_size = D_8002BD10 - func_8002BC40 = 0xD0.
 *    If OSTask.flags has OS_TASK_DP_WAIT, it waits for the RDP's DMA to go idle. It then DMAs
 *    t.ucode_data to DMEM 0x000 and 0xF80 bytes of t.ucode to IMEM 0x080, and jumps to 0x04001080.
 *    After every DMA it checks SP_STATUS SIG0. If the CPU asked for a yield, it sets SIG1|SIG2,
 *    clears SIG0 and stops with `break`.
 *  - bytes 0x0D0-0x1EF: the first 0x120 bytes of the audio microcode, very likely aspMain
 *    (D_8002BD10 = t.ucode of the type-2 audio task in func_80016A30; 0xC60 bytes up to
 *    D_8002C970, where the graphics microcode text starts). The splitter ended this "function" at
 *    0x8002BE30 for no particular reason. This part holds the entry point, the command-list loop and
 *    the DMA helpers. The loop fetches t.data_ptr in chunks of up to 0x140 bytes (40 commands) to
 *    DMEM 0x2B0. For each 8-byte command it jumps through a 16-bit IMEM handler table at DMEM 0x000,
 *    indexed by the low 7 bits of the command byte: offset ((w0 >> 24) & 0x7F) * 2, computed as
 *    (w0 >> 23) & 0xFE, so bit 31 of w0 is ignored. When the list is done it sets SIG2 (task done)
 *    and stops with `break`.
 * Register use: "mtc0/mfc0 $n" here are the RSP's COP0 registers, not the CPU's: c0 SP_MEM_ADDR,
 * c1 SP_DRAM_ADDR, c2 SP_RD_LEN, c3 SP_WR_LEN, c4 SP_STATUS, c5 SP_DMA_FULL, c6 SP_DMA_BUSY,
 * c7 SP_SEMAPHORE, c11 DPC_STATUS. "j/jal func_840010xx" are jumps inside IMEM (0x040010xx).
 * $at = 0xFC0 is the OSTask copy in DMEM.
 * The C below is a MODEL for reading only, written against the CPU-visible addresses of the same
 * registers. It is not a replacement: the RSP must receive exactly these bytes, and the callers
 * depend on the 0xD0 boot size. A NON_MATCHING build must keep emitting the asm here; do not link
 * the model in place of it. */
#if 0 /* RSP model for reading only (see above); never compile it in place of the asm. */
#include "common.h"
/*
 * MODEL ONLY: these bytes are RSP (signal processor) code, not CPU code. The CPU never executes
 * them; it hands their address to the RSP as OSTask.t.ucode_boot / t.ucode. The C below is a
 * description written from the RSP's point of view, using the CPU-visible addresses of the
 * same hardware so it compiles:
 *   RSP COP0 c0..c7  = SP_MEM_ADDR, SP_DRAM_ADDR, SP_RD_LEN, SP_WR_LEN, SP_STATUS, SP_DMA_FULL,
 *                      SP_DMA_BUSY, SP_SEMAPHORE      (CPU: 0xA4040000 + 4*n)
 *   RSP COP0 c8..c15 = DPC_START, DPC_END, DPC_CURRENT, DPC_STATUS, ... (CPU: 0xA4100000 + 4*(n-8))
 *   RSP DMEM 0x000-0xFFF (CPU: 0xA4000000), IMEM 0x000-0xFFF (CPU: 0xA4001000).
 * RSP addresses 0x0000-0x0FFF are DMEM and 0x1000-0x1FFF are IMEM. The boot code is linked
 * at IMEM 0x000 (0x04001000), the audio microcode at IMEM 0x080 (0x04001080).
 */
#define RSP_COP0(n) (*(volatile u32 *)(0xA4040000 + (n) * 4))
#define SP_MEM_ADDR RSP_COP0(0)
#define SP_DRAM_ADDR RSP_COP0(1)
#define SP_RD_LEN RSP_COP0(2)     /* write: start DRAM -> DMEM/IMEM DMA of (len + 1) bytes */
#define SP_WR_LEN RSP_COP0(3)     /* write: start DMEM/IMEM -> DRAM DMA of (len + 1) bytes */
#define SP_STATUS RSP_COP0(4)
#define SP_DMA_FULL RSP_COP0(5)
#define SP_DMA_BUSY RSP_COP0(6)
#define SP_SEMAPHORE RSP_COP0(7)  /* read: returns old value and sets it; write 0: release */
#define DPC_STATUS (*(volatile u32 *)0xA410000C) /* RSP COP0 c11 */

#define DMEM_W(off) (*(volatile u32 *)(0xA4000000 + (off)))
#define DMEM_H(off) (*(volatile s16 *)(0xA4000000 + (off)))

/* OSTask is placed by osSpTaskLoad at the top of DMEM (0xFC0, 0x40 bytes). */
#define OSTASK 0xFC0
#define OSTASK_FLAGS (OSTASK + 0x04)           /* t.flags */
#define OSTASK_UCODE (OSTASK + 0x10)           /* t.ucode */
#define OSTASK_UCODE_DATA (OSTASK + 0x18)      /* t.ucode_data */
#define OSTASK_UCODE_DATA_SIZE (OSTASK + 0x1C) /* t.ucode_data_size */
#define OSTASK_DATA_PTR (OSTASK + 0x30)        /* t.data_ptr: audio command list in DRAM */
#define OSTASK_DATA_SIZE (OSTASK + 0x34)       /* t.data_size: its length in bytes */

#define OS_TASK_DP_WAIT 0x0002
#define SP_STATUS_SIG0 0x0080          /* read bit: CPU asked the task to yield */
#define SP_CLR_SIG0 0x0200             /* write bits */
#define SP_SET_SIG1 0x1000             /* "yielded" */
#define SP_SET_SIG2 0x4000             /* "task done" */
#define DPC_STATUS_XBUS_DMEM_DMA 0x001
#define DPC_STATUS_DMA_BUSY 0x100

/* RSP `break`: sets SP_STATUS halt|broke and, if enabled, raises the SP interrupt on the CPU. */
extern void rspBreak(void);
/* `jr` into IMEM: run code at that IMEM address (never returns here). */
extern void rspJumpImem(u32 imemAddr);
/* `jr` to an audio command handler with the command words in $k0 (w0) and $t9 (w1); the
 * handler jumps back to the dispatch loop when it is done. */
extern void rspRunHandler(u32 imemAddr, u32 w0, u32 w1);

/* ------------------------------------------------------------------------------------------ */
/* rspboot (bytes 0x000-0x0CF, IMEM 0x000). Size 0xD0 = D_8002BD10 - func_8002BC40.            */
/* ------------------------------------------------------------------------------------------ */

/* IMEM 0x03C. Every DMA wait ends here: release the semaphore; if the CPU raised SIG0 (yield)
 * before the microcode even started, report "yielded + done", clear the request and halt. */
static void rspbootCheckYield(void)
{
    if (!(SP_STATUS & SP_STATUS_SIG0)) {
        SP_SEMAPHORE = 0; /* in the jr $ra delay slot */
        return;
    }
    SP_SEMAPHORE = 0;
    SP_STATUS = SP_SET_SIG2 | SP_SET_SIG1 | SP_CLR_SIG0; /* 0x5200 */
    rspBreak();
}

/* IMEM 0x008. DMA 0xF80 bytes of t.ucode into IMEM 0x080..0xFFF and jump to it. The DMA
 * overwrites the tail of rspboot itself (0x080-0x0CF); only code below 0x080 is still used. */
static void rspbootLoadUcode(void)
{
    u32 ucode = DMEM_W(OSTASK_UCODE);

    SP_MEM_ADDR = 0x1080; /* IMEM + 0x080 */
    SP_DRAM_ADDR = ucode;
    SP_RD_LEN = 0xF7F;
    while (SP_DMA_BUSY != 0) {
    }
    rspbootCheckYield();
    SP_SEMAPHORE = 0; /* jr $a3 delay slot */
    rspJumpImem(0x1080);
}

/* Entry, IMEM 0x000: "j 0x064" with OSTask's DMEM address (0xFC0) kept in $at for good. */
void rspbootEntry(void)
{
    u32 data, len;

    /* With OS_TASK_DP_WAIT, first wait until the RDP has finished DMAing the previous
     * display list (polling for a yield request meanwhile). */
    if (DMEM_W(OSTASK_FLAGS) & OS_TASK_DP_WAIT) {
        do {
            rspbootCheckYield();
        } while ((s32)(DPC_STATUS & DPC_STATUS_DMA_BUSY) > 0);
    }
    /* DMA t.ucode_data (t.ucode_data_size bytes) to DMEM 0x000. */
    data = DMEM_W(OSTASK_UCODE_DATA);
    len = DMEM_W(OSTASK_UCODE_DATA_SIZE) - 1;
    while (SP_DMA_FULL != 0) {
    }
    SP_MEM_ADDR = 0;
    SP_DRAM_ADDR = data;
    SP_RD_LEN = len;
    while (SP_DMA_BUSY != 0) {
    }
    rspbootCheckYield();
    rspbootLoadUcode();
}

/* ------------------------------------------------------------------------------------------ */
/* aspMain start (bytes 0x0D0-0x1EF, IMEM 0x080-0x19F; D_8002BD10 = t.ucode of the audio task). */
/* The rest of the 0xC60-byte audio microcode lies after this symbol, up to D_8002C970.       */
/* ------------------------------------------------------------------------------------------ */

static u32 aspCmdDram;  /* $gp: DRAM address of the next unread command (t.data_ptr) */
static s32 aspCmdLeft;  /* $k1: bytes of command list not yet executed (t.data_size) */
static s32 aspBufBytes; /* $fp: bytes still to run in the DMEM command buffer */
static u32 aspCmdPtr;   /* $sp: DMEM address of the current command */

/* IMEM 0x14C: take the semaphore, wait for a free DMA slot, start DRAM -> DMEM. */
void aspDmaRead(u32 dmem, u32 dram, u32 lenMinus1)
{
    while (SP_SEMAPHORE != 0) {
    }
    while (SP_DMA_FULL != 0) {
    }
    SP_MEM_ADDR = dmem;
    SP_DRAM_ADDR = dram;
    SP_RD_LEN = lenMinus1;
}

/* IMEM 0x174: same, DMEM -> DRAM (used by the handlers to write results back). */
void aspDmaWrite(u32 dmem, u32 dram, u32 lenMinus1)
{
    while (SP_SEMAPHORE != 0) {
    }
    while (SP_DMA_FULL != 0) {
    }
    SP_MEM_ADDR = dmem;
    SP_DRAM_ADDR = dram;
    SP_WR_LEN = lenMinus1;
}

/* IMEM 0x120: fetch up to 0x140 bytes (40 commands of 8 bytes) of the list to DMEM 0x2B0. */
static void aspFillCmdBuffer(u32 dram)
{
    s32 n = aspCmdLeft;

    if (n - 0x140 > 0) {
        n = 0x140;
    }
    aspBufBytes = n;
    aspDmaRead(0x2B0, dram, n - 1);
    aspCmdPtr = 0x2B0;
}

/* IMEM 0x080: microcode entry. */
void aspMainEntry(void)
{
    u32 st = DPC_STATUS;
    u32 w0, w1;

    aspCmdDram = DMEM_W(OSTASK_DATA_PTR);
    aspCmdLeft = DMEM_W(OSTASK_DATA_SIZE);
    /* If the RDP is reading from DMEM (XBUS mode) and still busy, wait for it. */
    if ((st & DPC_STATUS_XBUS_DMEM_DMA) && (st & DPC_STATUS_DMA_BUSY)) {
        while ((s32)(DPC_STATUS & DPC_STATUS_DMA_BUSY) > 0) {
        }
    }
    /* $t8 = 0xFA0 here (a DMEM address used by the command handlers). */
    aspFillCmdBuffer(aspCmdDram);
    for (;;) {
        /* IMEM 0x0B8 */
        while (SP_DMA_BUSY != 0) {
        }
        SP_SEMAPHORE = 0;
        do {
            /* IMEM 0x0C8: dispatch. The command byte (w0 >> 24) indexes a table of 16-bit IMEM
             * handler addresses at DMEM 0x000 (from t.ucode_data). Handlers come back with
             * "j 0x0EC; addi $fp, $fp, -8". */
            w0 = DMEM_W(aspCmdPtr);
            w1 = DMEM_W(aspCmdPtr + 4);
            aspCmdDram += 8;
            aspCmdLeft -= 8;
            rspRunHandler((u16)DMEM_H((w0 >> 23) & 0xFE), w0, w1);
            aspBufBytes -= 8;
            aspCmdPtr += 8;
        } while (aspBufBytes > 0);
        if (aspCmdLeft <= 0) {
            /* IMEM 0x10C: list finished: signal "task done", halt, spin. */
            SP_STATUS = SP_SET_SIG2;
            rspBreak();
            for (;;) {
            }
        }
        aspFillCmdBuffer(aspCmdDram);
    }
}
#endif

/* Hand-written in the original (RSP code); kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl func_8002BC40\n"
    ".ent func_8002BC40\n"
    "func_8002BC40:\n"
    "j func_84001064\n"
    "addi $at, $zero, 0xFC0 /* handwritten instruction */\n"
    "lw $v0, 0x10($at)\n"
    "addi $v1, $zero, 0xF7F /* handwritten instruction */\n"
    "addi $a3, $zero, 0x1080 /* handwritten instruction */\n"
    "mtc0 $a3, $0 /* handwritten instruction */\n"
    "mtc0 $v0, $1 /* handwritten instruction */\n"
    "mtc0 $v1, $2 /* handwritten instruction */\n"
    ".L8002BC60:\n"
    "mfc0 $a0, $6 /* handwritten instruction */\n"
    "bnez $a0, .L8002BC60\n"
    "nop\n"
    "jal func_8400103C\n"
    "nop\n"
    "jr $a3\n"
    "mtc0 $zero, $7 /* handwritten instruction */\n"
    ".L8002BC7C:\n"
    "mfc0 $t0, $4 /* handwritten instruction */\n"
    "andi $t0, $t0, 0x80\n"
    "bnez $t0, .L8002BC90\n"
    "nop\n"
    "jr $ra\n"
    ".L8002BC90:\n"
    "mtc0 $zero, $7 /* handwritten instruction */\n"
    "ori $t0, $zero, 0x5200\n"
    "mtc0 $t0, $4 /* handwritten instruction */\n"
    "break 0\n"
    "nop\n"
    "lw $v0, 0x4($at)\n"
    "andi $v0, $v0, 0x2\n"
    "beqz $v0, .L8002BCCC\n"
    "nop\n"
    "jal func_8400103C\n"
    "nop\n"
    "mfc0 $v0, $11 /* handwritten instruction */\n"
    "andi $v0, $v0, 0x100\n"
    "bgtz $v0, .L8002BC7C\n"
    "nop\n"
    ".L8002BCCC:\n"
    "lw $v0, 0x18($at)\n"
    "lw $v1, 0x1C($at)\n"
    "addi $v1, $v1, -0x1 /* handwritten instruction */\n"
    ".L8002BCD8:\n"
    "mfc0 $fp, $5 /* handwritten instruction */\n"
    "bnez $fp, .L8002BCD8\n"
    "nop\n"
    "mtc0 $zero, $0 /* handwritten instruction */\n"
    "mtc0 $v0, $1 /* handwritten instruction */\n"
    "mtc0 $v1, $2 /* handwritten instruction */\n"
    ".L8002BCF0:\n"
    "mfc0 $a0, $6 /* handwritten instruction */\n"
    "bnez $a0, .L8002BCF0\n"
    "nop\n"
    "jal func_8400103C\n"
    "nop\n"
    "j func_84001008\n"
    "nop\n"
    "nop\n"
    "mfc0 $a1, $11 /* handwritten instruction */\n"
    "lw $gp, 0x30($at)\n"
    "lw $k1, 0x34($at) /* handwritten instruction */\n"
    "andi $a0, $a1, 0x1\n"
    "beqz $a0, .L8002BD3C\n"
    "andi $a0, $a1, 0x100\n"
    "beqz $a0, .L8002BD3C\n"
    "mfc0 $a0, $11 /* handwritten instruction */\n"
    ".L8002BD30:\n"
    "andi $a0, $a0, 0x100\n"
    "bgtz $a0, .L8002BD30\n"
    "mfc0 $a0, $11 /* handwritten instruction */\n"
    ".L8002BD3C:\n"
    "addi $t8, $zero, 0xFA0 /* handwritten instruction */\n"
    "jal func_84001120\n"
    "add $v0, $zero, $gp /* handwritten instruction */\n"
    "mfc0 $v0, $6 /* handwritten instruction */\n"
    ".L8002BD4C:\n"
    "bnez $v0, .L8002BD4C\n"
    "mfc0 $v0, $6 /* handwritten instruction */\n"
    "mtc0 $zero, $7 /* handwritten instruction */\n"
    ".L8002BD58:\n"
    "lw $k0, 0x0($sp) /* handwritten instruction */\n"
    "lw $t9, 0x4($sp)\n"
    "addi $gp, $gp, 0x8 /* handwritten instruction */\n"
    "srl $at, $k0, 23\n"
    "andi $at, $at, 0xFE\n"
    "lh $at, 0x0($at)\n"
    "jr $at\n"
    "addi $k1, $k1, -0x8 /* handwritten instruction */\n"
    "break 0\n"
    "bgtz $fp, .L8002BD58\n"
    "addi $sp, $sp, 0x8 /* handwritten instruction */\n"
    "blez $k1, .L8002BD9C /* handwritten instruction */\n"
    "ori $at, $zero, 0x4000\n"
    "jal func_84001120\n"
    "add $v0, $zero, $gp /* handwritten instruction */\n"
    "j func_840010BC\n"
    "mfc0 $v0, $6 /* handwritten instruction */\n"
    ".L8002BD9C:\n"
    "mtc0 $at, $4 /* handwritten instruction */\n"
    "break 0\n"
    "nop\n"
    ".L8002BDA8:\n"
    "b .L8002BDA8\n"
    "nop\n"
    "addi $a1, $ra, 0x0 /* handwritten instruction */\n"
    "addi $v1, $k1, 0x0 /* handwritten instruction */\n"
    "addi $a0, $v1, -0x140 /* handwritten instruction */\n"
    "blez $a0, .L8002BDC8\n"
    "addi $at, $zero, 0x2B0 /* handwritten instruction */\n"
    "addi $v1, $zero, 0x140 /* handwritten instruction */\n"
    ".L8002BDC8:\n"
    "addi $fp, $v1, 0x0 /* handwritten instruction */\n"
    "jal func_8400114C\n"
    "addi $v1, $v1, -0x1 /* handwritten instruction */\n"
    "jr $a1\n"
    "addi $sp, $zero, 0x2B0 /* handwritten instruction */\n"
    "mfc0 $a0, $7 /* handwritten instruction */\n"
    ".L8002BDE0:\n"
    "bnez $a0, .L8002BDE0\n"
    "mfc0 $a0, $7 /* handwritten instruction */\n"
    "mfc0 $a0, $5 /* handwritten instruction */\n"
    ".L8002BDEC:\n"
    "bnez $a0, .L8002BDEC\n"
    "mfc0 $a0, $5 /* handwritten instruction */\n"
    "mtc0 $at, $0 /* handwritten instruction */\n"
    "mtc0 $v0, $1 /* handwritten instruction */\n"
    "jr $ra\n"
    "mtc0 $v1, $2 /* handwritten instruction */\n"
    "mfc0 $a0, $7 /* handwritten instruction */\n"
    ".L8002BE08:\n"
    "bnez $a0, .L8002BE08\n"
    "mfc0 $a0, $7 /* handwritten instruction */\n"
    "mfc0 $a0, $5 /* handwritten instruction */\n"
    ".L8002BE14:\n"
    "bnez $a0, .L8002BE14\n"
    "mfc0 $a0, $5 /* handwritten instruction */\n"
    "mtc0 $at, $0 /* handwritten instruction */\n"
    "mtc0 $v0, $1 /* handwritten instruction */\n"
    "jr $ra\n"
    "mtc0 $v1, $3 /* handwritten instruction */\n"
    "andi $v0, $t9, 0xFFFF\n"
    ".end func_8002BC40\n"
    ".set at\n"
    ".set reorder\n"
    );
