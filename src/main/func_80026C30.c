/* @header
 * func_80026C30
 * VRAM 0x80026C30 | ROM 0x27830 | size 0x44
 * asm: asm/nonmatchings/main/func_80026C30.s
 */
/* func_80026C30: libultra osUnmapTLBAll(void). Invalidates TLB entries 30 down to 0: EntryHi ($10) = 0x80000000
 * (a KSEG0 VPN, never looked up through the TLB, ASID 0), EntryLo0 ($2) = EntryLo1 ($3) = 0 (V clear), then for each
 * index Index ($0) = i; tlbwi. PageMask is left as it was. Entry 31 is skipped because it is reserved for the rdb
 * debugger mapping (osMapTLBRdb, func_80026C80). The caller's EntryHi (current ASID) is saved and restored. Identical to
 * ultralib src/os/unmaptlball.s (2.0I, li t1, NTLBENTRIES-1 where R4300.h's NTLBENTRIES is 31). Only caller:
 * initializePiAndRdram (osInitialize), immediately followed by func_80026C80. The NOPs around tlbwi are CP0 hazard
 * padding (mtc0 Index -> tlbwi -> next mtc0); addi (trapping add) is used for the counter. Asm because of mtc0/tlbwi. */
#ifdef NON_MATCHING
#include "common.h"

/* CP0 TLB registers: Index $0, EntryLo0 $2, EntryLo1 $3, EntryHi $10. */
static inline u32 getEntryHi(void) {
    u32 v;
    __asm__ __volatile__("mfc0 %0, $10" : "=r"(v));
    return v;
}
static inline void setEntryHi(u32 v) {
    __asm__ __volatile__("mtc0 %0, $10" : : "r"(v));
}
static inline void setEntryLo0(u32 v) {
    __asm__ __volatile__("mtc0 %0, $2" : : "r"(v));
}
static inline void setEntryLo1(u32 v) {
    __asm__ __volatile__("mtc0 %0, $3" : : "r"(v));
}
static inline void setIndex(u32 v) {
    __asm__ __volatile__("mtc0 %0, $0" : : "r"(v));
}
/* tlbwi: write EntryHi/EntryLo0/EntryLo1/PageMask into the TLB entry selected by Index. */
static inline void tlbWriteIndexed(void) {
    __asm__ __volatile__("tlbwi");
}
static inline void cp0Hazard(void) {
    __asm__ __volatile__("nop");
}

void func_80026C30(void) {
    u32 savedEntryHi = getEntryHi();    /* holds the current ASID; restored at the end */
    s32 i;

    /* Every entry gets VPN2 = 0x80000000 (K0BASE: KSEG0 is never translated, so the entry can never match)
     * and both EntryLo halves 0 (invalid). PageMask is left as it is. */
    setEntryHi(0x80000000);
    setEntryLo0(0);
    setEntryLo1(0);
    for (i = 30; i >= 0; i--) {         /* entries 30..0; entry 31 is kept for osMapTLBRdb */
        setIndex(i);
        cp0Hazard();
        tlbWriteIndexed();
        cp0Hazard();
        cp0Hazard();
    }
    setEntryHi(savedEntryHi);
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl func_80026C30\n"
    ".ent func_80026C30\n"
    "func_80026C30:\n"
    "mfc0 $t0, $10 /* handwritten instruction */\n"
    "addiu $t1, $zero, 0x1E\n"
    "lui $t2, (0x80000000 >> 16)\n"
    "mtc0 $t2, $10 /* handwritten instruction */\n"
    "mtc0 $zero, $2 /* handwritten instruction */\n"
    "mtc0 $zero, $3 /* handwritten instruction */\n"
    ".L80026C48:\n"
    "mtc0 $t1, $0 /* handwritten instruction */\n"
    "nop\n"
    "tlbwi /* handwritten instruction */\n"
    "nop\n"
    "nop\n"
    "addi $t1, $t1, -0x1 /* handwritten instruction */\n"
    "bgez $t1, .L80026C48\n"
    "nop\n"
    "mtc0 $t0, $10 /* handwritten instruction */\n"
    "jr $ra\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    ".end func_80026C30\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
