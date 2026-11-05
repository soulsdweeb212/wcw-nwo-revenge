/* @header
 * osWritebackDCacheAll  (originally func_8001C860)
 * VRAM 0x8001C860 | ROM 0x1D460 | size 0x28
 * asm: asm/nonmatchings/main/osWritebackDCacheAll.s
 */
/* osWritebackDCacheAll: libultra osWritebackDCacheAll(void). Walks all 512 lines of the 8 KB primary data cache
 * (16-byte lines) by index, KSEG0 0x80000000..0x80001FF0, with CACHE op 0x01 (Index_Writeback_Invalidate, D-cache):
 * each dirty line is written back to RDRAM and every line is invalidated, so afterwards RDRAM holds everything the CPU
 * wrote and the next access to any address misses. Identical to ultralib src/os/writebackdcacheall.s (2.0I);
 * after it the RSP/RDP can safely DMA anything the CPU wrote. Callers: rspTaskThread (before handing the RSP a task),
 * __MusIntRemapPtrBank, func_80002CC4. Asm because CACHE has no C form; the loop tests the old pointer and bumps it in the
 * branch delay slot, i.e. it runs once more than "while (p < last)" would suggest (p == last is processed). */
#ifdef NON_MATCHING
#include "common.h"

/* cache 0x01 = Index_Writeback_Invalidate on the primary D-cache: write the line selected by the address's index
 * bits back to RDRAM if dirty, then invalidate it. Only the index bits matter, so KSEG0 addresses walk the cache. */
static inline void dcacheIndexWritebackInvalidate(u32 addr) {
    __asm__ __volatile__("cache 0x01, 0(%0)" : : "r"(addr));
}

void osWritebackDCacheAll(void) {
    u32 line = 0x80000000;              /* K0BASE */
    u32 last = line + 0x2000 - 0x10;    /* DCACHE_SIZE 8 KB, DCACHE_LINESIZE 16 */

    for (;;) {
        dcacheIndexWritebackInvalidate(line);
        if (line >= last) {
            break;
        }
        line += 0x10;
    }
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl osWritebackDCacheAll\n"
    ".ent osWritebackDCacheAll\n"
    "osWritebackDCacheAll:\n"
    "lui $t0, 0x8000\n"
    "addiu $t2, $zero, 0x2000\n"
    "addu $t1, $t0, $t2\n"
    "addiu $t1, $t1, -0x10\n"
    ".L8001C870:\n"
    "cache 0x01, 0x0($t0) /* handwritten instruction */\n"
    "sltu $at, $t0, $t1\n"
    "bnez $at, .L8001C870\n"
    "addiu $t0, $t0, (0x80000010 & 0xFFFF)\n"
    "jr $ra\n"
    "nop\n"
    "nop\n"
    "nop\n"
    ".end osWritebackDCacheAll\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
