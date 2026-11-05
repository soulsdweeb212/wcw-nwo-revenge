/* @header
 * osMapTLBRdb  (originally func_80026C80)
 * VRAM 0x80026C80 | ROM 0x27880 | size 0x58
 * asm: asm/nonmatchings/main/osMapTLBRdb.s
 */
/* osMapTLBRdb: libultra osMapTLBRdb(void). Writes TLB entry 31: Index ($0) = 31, PageMask ($5) = 0 (4 KB pages),
 * EntryHi ($10) = 0xC0000000 (K2BASE, ASID 0), EntryLo0 ($2) = (0x80000000 >> 6) | 0x17 = 0x02000017 (PFN of physical
 * 0x80000000, C = 2 uncached, D, V, G), EntryLo1 ($3) = 1 (G only, odd page invalid); tlbwi. So virtual 0xC0000000..
 * 0xC0000FFF maps uncached to physical 0x80000000, where the development hardware's rdb (remote debugger) port lives
 * (RDB_BASE_VIRTUAL_ADDR 0x80000000 in PR/rdb.h); on retail hardware the mapping is unused.
 * The caller's EntryHi is saved and restored. Identical to ultralib src/os/maptlbrdb.s (2.0I). Only caller:
 * osInitialize, right after osUnmapTLBAll. The NOPs are CP0 hazard padding.
 * Asm because of mtc0/tlbwi. */
#ifdef NON_MATCHING
#include "common.h"

/* CP0 TLB registers: Index $0, EntryLo0 $2, EntryLo1 $3, PageMask $5, EntryHi $10. */
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
static inline void setPageMask(u32 v) {
    __asm__ __volatile__("mtc0 %0, $5" : : "r"(v));
}
static inline void setIndex(u32 v) {
    __asm__ __volatile__("mtc0 %0, $0" : : "r"(v));
}
static inline void tlbWriteIndexed(void) {
    __asm__ __volatile__("tlbwi");
}
static inline void cp0Hazard(void) {
    __asm__ __volatile__("nop");
}

void osMapTLBRdb(void) {
    u32 savedEntryHi = getEntryHi();

    setIndex(31);                       /* NTLBENTRIES: the last TLB entry, reserved for rdb */
    setPageMask(0);                     /* 4 KB pages */
    setEntryHi(0xC0000000);             /* K2BASE: virtual pair 0xC0000000/0xC0001000, ASID 0 */
    /* Even page: PFN = 0x80000000 >> 12 (EntryLo PFN field starts at bit 6, hence >> 6), C = 2 uncached
     * (0x10), D dirty/writable (4), V valid (2), G global (1) -> 0x02000017. */
    setEntryLo0((0x80000000 >> 6) | 0x17);
    setEntryLo1(1);                     /* odd page: G only, not valid */
    cp0Hazard();
    tlbWriteIndexed();
    cp0Hazard();
    cp0Hazard();
    cp0Hazard();
    cp0Hazard();
    setEntryHi(savedEntryHi);
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl osMapTLBRdb\n"
    ".ent osMapTLBRdb\n"
    "osMapTLBRdb:\n"
    "mfc0 $t0, $10 /* handwritten instruction */\n"
    "addiu $t1, $zero, 0x1F\n"
    "mtc0 $t1, $0 /* handwritten instruction */\n"
    "mtc0 $zero, $5 /* handwritten instruction */\n"
    "addiu $t2, $zero, 0x17\n"
    "lui $t1, (0xC0000000 >> 16)\n"
    "mtc0 $t1, $10 /* handwritten instruction */\n"
    "lui $t1, (0x80000000 >> 16)\n"
    "srl $t3, $t1, 6\n"
    "or $t3, $t3, $t2\n"
    "mtc0 $t3, $2 /* handwritten instruction */\n"
    "addiu $t1, $zero, 0x1\n"
    "mtc0 $t1, $3 /* handwritten instruction */\n"
    "nop\n"
    "tlbwi /* handwritten instruction */\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "mtc0 $t0, $10 /* handwritten instruction */\n"
    "jr $ra\n"
    "nop\n"
    "nop\n"
    "nop\n"
    ".end osMapTLBRdb\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
