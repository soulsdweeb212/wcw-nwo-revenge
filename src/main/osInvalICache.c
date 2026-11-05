/* @header
 * osInvalICache  (originally func_8001C660)
 * VRAM 0x8001C660 | ROM 0x1D260 | size 0x74
 * asm: asm/nonmatchings/main/osInvalICache.s
 */
/* osInvalICache: libultra osInvalICache(void *vaddr, s32 nbytes). Makes the instruction cache forget a range so
 * code just copied/DMA'd into RAM is fetched fresh. nbytes <= 0: nothing. nbytes < 16 KB (ICACHE_SIZE): from vaddr
 * rounded down to a 32-byte line up to the line holding vaddr+nbytes-1, CACHE op 0x10 (Hit_Invalidate, I-cache) on each
 * line, which only drops lines that really hold those addresses; a range that wraps past 0xFFFFFFFF is ignored.
 * nbytes >= 16 KB: CACHE op 0x00 (Index_Invalidate, I-cache) on every line by index from 0x80000000, i.e. the whole
 * I-cache. Identical to ultralib src/os/invalicache.s (2.0I). Callers: osInitialize (
 * osInvalICache(0x80000000, 0x190) after the exception vectors are copied to 0x80000000..0x8000018F) and func_80000700
 * (the segment loader, over the loaded code range). Asm because CACHE has no C form; loops test the old pointer and
 * advance in the delay slot. */
#ifdef NON_MATCHING
#include "common.h"

/* cache 0x10 = Hit_Invalidate on the primary I-cache: invalidate the line if it currently holds this address. */
static inline void icacheHitInvalidate(u32 addr) {
    __asm__ __volatile__("cache 0x10, 0(%0)" : : "r"(addr));
}

/* cache 0x00 = Index_Invalidate on the primary I-cache: invalidate whatever line the address's index bits select. */
static inline void icacheIndexInvalidate(u32 addr) {
    __asm__ __volatile__("cache 0x00, 0(%0)" : : "r"(addr));
}

void osInvalICache(s32 addr, s32 len) {
    u32 line;
    u32 last;

    if (len <= 0) {
        return;
    }
    if ((u32)len < 0x4000) {            /* ICACHE_SIZE 16 KB */
        line = (u32)addr;
        last = (u32)addr + (u32)len;
        if (line >= last) {             /* range wraps past 0xFFFFFFFF */
            return;
        }
        last -= 0x20;                   /* ICACHE_LINESIZE 32: last = start of the final 32 bytes */
        line -= line & 0x1F;            /* align down to a cache line */
        for (;;) {
            icacheHitInvalidate(line);
            if (line >= last) {
                break;
            }
            line += 0x20;
        }
        return;
    }
    /* A range as big as the cache: cheaper to invalidate every line by index. */
    line = 0x80000000;                  /* K0BASE */
    last = line + 0x4000 - 0x20;
    for (;;) {
        icacheIndexInvalidate(line);
        if (line >= last) {
            break;
        }
        line += 0x20;
    }
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl osInvalICache\n"
    ".ent osInvalICache\n"
    "osInvalICache:\n"
    "blez $a1, .L8001C6A8\n"
    "nop\n"
    "addiu $t3, $zero, 0x4000\n"
    "sltu $at, $a1, $t3\n"
    "beqz $at, .L8001C6B0\n"
    "nop\n"
    "addu $t0, $a0, $zero\n"
    "addu $t1, $a0, $a1\n"
    "sltu $at, $t0, $t1\n"
    "beqz $at, .L8001C6A8\n"
    "nop\n"
    "addiu $t1, $t1, -0x20\n"
    "andi $t2, $t0, 0x1F\n"
    "subu $t0, $t0, $t2\n"
    ".L8001C698:\n"
    "cache 0x10, 0x0($t0) /* handwritten instruction */\n"
    "sltu $at, $t0, $t1\n"
    "bnez $at, .L8001C698\n"
    "addiu $t0, $t0, 0x20\n"
    ".L8001C6A8:\n"
    "jr $ra\n"
    "nop\n"
    ".L8001C6B0:\n"
    "lui $t0, 0x8000\n"
    "addu $t1, $t0, $t3\n"
    "addiu $t1, $t1, -0x20\n"
    ".L8001C6BC:\n"
    "cache 0x00, 0x0($t0) /* handwritten instruction */\n"
    "sltu $at, $t0, $t1\n"
    "bnez $at, .L8001C6BC\n"
    "addiu $t0, $t0, (0x80000020 & 0xFFFF)\n"
    "jr $ra\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    ".end osInvalICache\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
