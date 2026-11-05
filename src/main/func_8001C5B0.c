/* @header
 * func_8001C5B0
 * VRAM 0x8001C5B0 | ROM 0x1D1B0 | size 0xB0
 * asm: asm/nonmatchings/main/func_8001C5B0.s
 */
/* func_8001C5B0: libultra osInvalDCache(void *vaddr, s32 nbytes). Makes the data cache forget a range that a DMA is
 * about to fill (or has filled), so the CPU then reads RDRAM rather than stale lines; used before every PI/ROM read
 * into RAM. nbytes <= 0: nothing. nbytes < 8 KB: the range is taken in 16-byte lines; a partial first line and a
 * partial last line also hold bytes outside the range, so they get CACHE op 0x15 (Hit_Writeback_Invalidate: written
 * back if dirty, then dropped) and the lines entirely inside get CACHE op 0x11 (Hit_Invalidate: dropped WITHOUT
 * writeback, so CPU writes still sitting in them are discarded). A range that wraps past 0xFFFFFFFF is ignored. nbytes
 * >= 8 KB: CACHE op 0x01 (Index_Writeback_Invalidate) on the whole D-cache from 0x80000000 (nothing lost, everything
 * dropped). Identical to ultralib src/os/invaldcache.s (2.0I). Callers: func_80000700 (segment loader),
 * readRomSynchronousChunks, initializeResourceStream, func_8000946C, func_80025810, and the code_80090000 routines
 * func_800B97CC, func_800BAD80, func_800B8994. (func_80027040 only declares the prototype.) Asm because CACHE has no C
 * form. Edge detail kept from the asm: after the first partial line it returns if the aligned start is already >= (end
 * - 16); after the last partial line it returns if the aligned last line is below the next start; the middle loop
 * always runs at least once. */
#ifdef NON_MATCHING
#include "common.h"

/* cache 0x15 = Hit_Writeback_Invalidate on the primary D-cache: if the line holds this address, write it back
 * when dirty, then invalidate it. */
static inline void dcacheHitWritebackInvalidate(u32 addr) {
    __asm__ __volatile__("cache 0x15, 0(%0)" : : "r"(addr));
}

/* cache 0x11 = Hit_Invalidate on the primary D-cache: drop the line if it holds this address, WITHOUT writing it
 * back (any dirty CPU data in it is lost). */
static inline void dcacheHitInvalidate(u32 addr) {
    __asm__ __volatile__("cache 0x11, 0(%0)" : : "r"(addr));
}

/* cache 0x01 = Index_Writeback_Invalidate on the primary D-cache (by index bits; writes back if dirty). */
static inline void dcacheIndexWritebackInvalidate(u32 addr) {
    __asm__ __volatile__("cache 0x01, 0(%0)" : : "r"(addr));
}

void func_8001C5B0(void *addr, s32 len) {
    u32 line;
    u32 last;
    u32 misalign;

    if (len <= 0) {
        return;
    }
    if ((u32)len < 0x2000) {            /* DCACHE_SIZE 8 KB */
        line = (u32)addr;
        last = (u32)addr + (u32)len;
        if (line >= last) {             /* range wraps past 0xFFFFFFFF */
            return;
        }
        last -= 0x10;                   /* last = end - DCACHE_LINESIZE (not yet aligned) */

        /* Partial first line: it also holds bytes outside the range, so write it back before dropping it. */
        misalign = line & 0xF;
        if (misalign != 0) {
            line -= misalign;
            dcacheHitWritebackInvalidate(line);
            if (line >= last) {
                return;
            }
            line += 0x10;
        }

        /* Partial last line: same treatment. (last & 0xF) == (end & 0xF); last+0x10 lies in the line holding end. */
        misalign = last & 0xF;
        if (misalign != 0) {
            last -= misalign;
            dcacheHitWritebackInvalidate(last + 0x10);
            if (last < line) {
                return;
            }
        }

        /* Lines wholly inside the range: plain invalidate, the DMA is about to overwrite RDRAM under them. */
        for (;;) {
            dcacheHitInvalidate(line);
            if (line >= last) {
                break;
            }
            line += 0x10;
        }
        return;
    }
    /* A range as big as the cache: write back and invalidate every line by index (nothing dirty is lost). */
    line = 0x80000000;                  /* K0BASE */
    last = line + 0x2000 - 0x10;
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
    ".globl func_8001C5B0\n"
    ".ent func_8001C5B0\n"
    "func_8001C5B0:\n"
    "blez $a1, .L8001C634\n"
    "nop\n"
    "addiu $t3, $zero, 0x2000\n"
    "sltu $at, $a1, $t3\n"
    "beqz $at, .L8001C63C\n"
    "nop\n"
    "addu $t0, $a0, $zero\n"
    "addu $t1, $a0, $a1\n"
    "sltu $at, $t0, $t1\n"
    "beqz $at, .L8001C634\n"
    "nop\n"
    "addiu $t1, $t1, -0x10\n"
    "andi $t2, $t0, 0xF\n"
    "beqz $t2, .L8001C604\n"
    "nop\n"
    "subu $t0, $t0, $t2\n"
    "cache 0x15, 0x0($t0) /* handwritten instruction */\n"
    "sltu $at, $t0, $t1\n"
    "beqz $at, .L8001C634\n"
    "nop\n"
    "addiu $t0, $t0, 0x10\n"
    ".L8001C604:\n"
    "andi $t2, $t1, 0xF\n"
    "beqz $t2, .L8001C624\n"
    "nop\n"
    "subu $t1, $t1, $t2\n"
    "cache 0x15, 0x10($t1) /* handwritten instruction */\n"
    "sltu $at, $t1, $t0\n"
    "bnez $at, .L8001C634\n"
    "nop\n"
    ".L8001C624:\n"
    "cache 0x11, 0x0($t0) /* handwritten instruction */\n"
    "sltu $at, $t0, $t1\n"
    "bnez $at, .L8001C624\n"
    "addiu $t0, $t0, 0x10\n"
    ".L8001C634:\n"
    "jr $ra\n"
    "nop\n"
    ".L8001C63C:\n"
    "lui $t0, 0x8000\n"
    "addu $t1, $t0, $t3\n"
    "addiu $t1, $t1, -0x10\n"
    ".L8001C648:\n"
    "cache 0x01, 0x0($t0) /* handwritten instruction */\n"
    "sltu $at, $t0, $t1\n"
    "bnez $at, .L8001C648\n"
    "addiu $t0, $t0, (0x80000010 & 0xFFFF)\n"
    "jr $ra\n"
    "nop\n"
    ".end func_8001C5B0\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
