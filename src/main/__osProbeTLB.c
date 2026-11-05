/* @header
 * __osProbeTLB  (originally func_80026B50)
 * VRAM 0x80026B50 | ROM 0x27750 | size 0xB8
 * asm: asm/nonmatchings/main/__osProbeTLB.s
 */
/* __osProbeTLB: libultra __osProbeTLB(void *vaddr) (probetlb.s), returns the physical address the TLB
 * maps vaddr to, or -1. Its only caller is osVirtualToPhysical, for addresses outside
 * KSEG0/KSEG1 (__osDequeueThread and alEnvmixerNew only carry a stray prototype). It saves CP0
 * EntryHi ($10), writes EntryHi = current ASID (bits 7..0) | vaddr's VPN2 (vaddr & ~0x1FFF), runs tlbp,
 * and if Index ($0) bit 31 (P, "no match") is set returns -1; otherwise tlbr loads the entry, page size =
 * (PageMask ($5) + 0x2000) >> 1, the vaddr bit at page size picks EntryLo1 ($3, odd page) or EntryLo0 ($2,
 * even page); if its V bit (0x2) is clear it returns -1, else (PFN field & 0x3FFFFFC0) << 6 plus the
 * offset vaddr & (page size - 1). EntryHi is restored before returning. Must be asm: CP0 moves, tlbp/tlbr
 * and the hand-placed hazard nops. Uses trapping addi/add: the two addi cannot overflow (PageMask is at
 * most 0x01FFE000, and pagesize >= 0x1000 before the -1). The final `add` of page base + offset can:
 * if a large page (PageMask != 0) has EntryLo PFN low bits set (the hardware ignores them, this code
 * does not mask them), a base just under 0x80000000 plus the offset crosses it and the CPU raises an
 * Integer Overflow exception instead of returning (e.g. PFN 0x7FFFF, 16 KB page, offset 0x1000). Only
 * a malformed TLB entry hits this; the C keeps it with addTrapping(). Same instructions as ultralib
 * probetlb.s. */
#ifdef NON_MATCHING
#include "common.h"

/* CP0 EntryHi ($10): VPN2 (bits 31..13) + ASID (bits 7..0) used by tlbp. */
static inline u32 getEntryHi(void) { u32 v; __asm__ __volatile__("mfc0 %0, $10" : "=r"(v)); return v; }
static inline void setEntryHi(u32 v) { __asm__ __volatile__("mtc0 %0, $10" : : "r"(v)); }
/* CP0 Index ($0): bit 31 (P) is set by tlbp when no entry matched. */
static inline u32 getIndex(void) { u32 v; __asm__ __volatile__("mfc0 %0, $0" : "=r"(v)); return v; }
/* CP0 PageMask ($5), EntryLo0 ($2, even page), EntryLo1 ($3, odd page): loaded by tlbr. */
static inline u32 getPageMask(void) { u32 v; __asm__ __volatile__("mfc0 %0, $5" : "=r"(v)); return v; }
static inline u32 getEntryLo0(void) { u32 v; __asm__ __volatile__("mfc0 %0, $2" : "=r"(v)); return v; }
static inline u32 getEntryLo1(void) { u32 v; __asm__ __volatile__("mfc0 %0, $3" : "=r"(v)); return v; }
static inline void tlbProbe(void) { __asm__ __volatile__("tlbp"); }
static inline void tlbRead(void) { __asm__ __volatile__("tlbr"); }
/* One pipeline-hazard slot (the original pads CP0 writes/TLB ops with nops). */
static inline void cp0Hazard(void) { __asm__ __volatile__("nop"); }
/* MIPS `add` (not addu): raises an Integer Overflow exception if the signed 32-bit sum overflows. */
static inline u32 addTrapping(u32 a, u32 b) {
    u32 v;
    __asm__ __volatile__("add %0, %1, %2" : "=r"(v) : "r"(a), "r"(b));
    return v;
}

/* __osProbeTLB: physical address that the TLB maps `vaddr` to, or -1 (0xFFFFFFFF) when
 * there is no matching entry or the matching half-entry is not valid. */
u32 __osProbeTLB(u32 vaddr) {
    u32 savedHi = getEntryHi();
    u32 pageSize, offsetMask, entryLo, result;

    /* Keep the current ASID, look up the 8 KB-aligned VPN2 of vaddr. */
    setEntryHi((savedHi & 0xFF) | (vaddr & ~0x1FFF));
    cp0Hazard(); cp0Hazard(); cp0Hazard();
    tlbProbe();
    cp0Hazard(); cp0Hazard();

    if (getIndex() & 0x80000000) {          /* Index.P: no match */
        result = -1;
    } else {
        tlbRead();                          /* EntryHi/Lo0/Lo1/PageMask <- TLB[Index] */
        cp0Hazard(); cp0Hazard(); cp0Hazard();
        /* PageMask 0 = 4 KB pages: (0 + 0x2000) >> 1 = 0x1000, one page of the even/odd pair. */
        pageSize = (getPageMask() + 0x2000) >> 1;
        offsetMask = pageSize - 1;
        /* The vaddr bit just above the page offset selects the even (Lo0) or odd (Lo1) page. */
        if (vaddr & pageSize) {
            entryLo = getEntryLo1();
        } else {
            entryLo = getEntryLo0();
        }
        if (!(entryLo & 2)) {               /* EntryLo.V clear: mapping not valid */
            result = -1;
        } else {
            /* PFN field (bits 29..6) << 6 = physical page base, plus the offset inside the page.
             * The asm's add traps on signed overflow; addTrapping keeps that (see header). */
            result = addTrapping((entryLo & 0x3FFFFFC0) << 6, vaddr & offsetMask);
        }
    }
    setEntryHi(savedHi);                    /* restore the caller's EntryHi (ASID) */
    return result;
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl __osProbeTLB\n"
    ".ent __osProbeTLB\n"
    "__osProbeTLB:\n"
    "mfc0 $t0, $10 /* handwritten instruction */\n"
    "andi $t1, $t0, 0xFF\n"
    "addiu $at, $zero, -0x2000\n"
    "and $t2, $a0, $at\n"
    "or $t1, $t1, $t2\n"
    "mtc0 $t1, $10 /* handwritten instruction */\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "tlbp /* handwritten instruction */\n"
    "nop\n"
    "nop\n"
    "mfc0 $t3, $0 /* handwritten instruction */\n"
    "lui $at, (0x80000000 >> 16)\n"
    "and $t3, $t3, $at\n"
    "bnez $t3, .L80026BF8\n"
    "nop\n"
    "tlbr /* handwritten instruction */\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "mfc0 $t3, $5 /* handwritten instruction */\n"
    "addi $t3, $t3, 0x2000 /* handwritten instruction */\n"
    "srl $t3, $t3, 1\n"
    "and $t4, $t3, $a0\n"
    "bnez $t4, .L80026BC8\n"
    "addi $t3, $t3, -0x1 /* handwritten instruction */\n"
    "mfc0 $v0, $2 /* handwritten instruction */\n"
    "b .L80026BCC\n"
    "nop\n"
    ".L80026BC8:\n"
    "mfc0 $v0, $3 /* handwritten instruction */\n"
    ".L80026BCC:\n"
    "andi $t5, $v0, 0x2\n"
    "beqz $t5, .L80026BF8\n"
    "nop\n"
    "lui $at, (0x3FFFFFC0 >> 16)\n"
    "ori $at, $at, (0x3FFFFFC0 & 0xFFFF)\n"
    "and $v0, $v0, $at\n"
    "sll $v0, $v0, 6\n"
    "and $t5, $a0, $t3\n"
    "add $v0, $v0, $t5 /* handwritten instruction */\n"
    "b .L80026BFC\n"
    "nop\n"
    ".L80026BF8:\n"
    "addiu $v0, $zero, -0x1\n"
    ".L80026BFC:\n"
    "mtc0 $t0, $10 /* handwritten instruction */\n"
    "jr $ra\n"
    "nop\n"
    "nop\n"
    "nop\n"
    ".end __osProbeTLB\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
