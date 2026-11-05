/* @header
 * func_8001C7E0
 * VRAM 0x8001C7E0 | ROM 0x1D3E0 | size 0x74
 * asm: asm/nonmatchings/main/func_8001C7E0.s
 */
/* func_8001C7E0: libultra osWritebackDCache(void *vaddr, s32 nbytes). Flushes CPU writes in a range out of the data
 * cache to RDRAM (lines stay valid) so the RSP/RDP/PI/AI see them, e.g. before a DMA from RAM. nbytes <= 0: nothing.
 * nbytes < 8 KB (DCACHE_SIZE): from vaddr rounded down to a 16-byte line up to the line holding vaddr+nbytes-1, CACHE
 * op 0x19 (Hit_Writeback, D-cache); a range that wraps past 0xFFFFFFFF is ignored. nbytes >= 8 KB: CACHE op 0x01
 * (Index_Writeback_Invalidate) over the whole D-cache from 0x80000000, which also invalidates every line. Identical to
 * ultralib src/os/writebackdcache.s (2.0I). Callers: submitGraphicsTask (the task list), loadRspTask (the OSTask
 * before the RSP boot DMA), initializePiAndRdram (osInitialize, the exception vectors at 0x80000000, 0x190 bytes),
 * func_80025810, and the code_80090000 audio/stream routines func_800BAD80, func_800B8994, func_800B9640,
 * func_800BB110. (func_80027040 only declares the prototype.) Asm because CACHE has no C form. */
#ifdef NON_MATCHING
#include "common.h"

/* cache 0x19 = Hit_Writeback on the primary D-cache: if the line holds this address and is dirty, write it back
 * to RDRAM; the line stays valid. */
static inline void dcacheHitWriteback(u32 addr) {
    __asm__ __volatile__("cache 0x19, 0(%0)" : : "r"(addr));
}

/* cache 0x01 = Index_Writeback_Invalidate on the primary D-cache (by index bits; writes back if dirty). */
static inline void dcacheIndexWritebackInvalidate(u32 addr) {
    __asm__ __volatile__("cache 0x01, 0(%0)" : : "r"(addr));
}

void func_8001C7E0(void *addr, s32 len) {
    u32 line;
    u32 last;

    if (len <= 0) {
        return;
    }
    if ((u32)len < 0x2000) {            /* DCACHE_SIZE 8 KB */
        line = (u32)addr;
        last = (u32)addr + (u32)len;
        if (line >= last) {             /* range wraps past 0xFFFFFFFF */
            return;
        }
        last -= 0x10;                   /* DCACHE_LINESIZE 16 */
        line -= line & 0xF;             /* align down to a cache line */
        for (;;) {
            dcacheHitWriteback(line);
            if (line >= last) {
                break;
            }
            line += 0x10;
        }
        return;
    }
    /* A range as big as the cache: write back (and invalidate) every line by index. */
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
    ".globl func_8001C7E0\n"
    ".ent func_8001C7E0\n"
    "func_8001C7E0:\n"
    "blez $a1, .L8001C828\n"
    "nop\n"
    "addiu $t3, $zero, 0x2000\n"
    "sltu $at, $a1, $t3\n"
    "beqz $at, .L8001C830\n"
    "nop\n"
    "addu $t0, $a0, $zero\n"
    "addu $t1, $a0, $a1\n"
    "sltu $at, $t0, $t1\n"
    "beqz $at, .L8001C828\n"
    "nop\n"
    "addiu $t1, $t1, -0x10\n"
    "andi $t2, $t0, 0xF\n"
    "subu $t0, $t0, $t2\n"
    ".L8001C818:\n"
    "cache 0x19, 0x0($t0) /* handwritten instruction */\n"
    "sltu $at, $t0, $t1\n"
    "bnez $at, .L8001C818\n"
    "addiu $t0, $t0, 0x10\n"
    ".L8001C828:\n"
    "jr $ra\n"
    "nop\n"
    ".L8001C830:\n"
    "lui $t0, 0x8000\n"
    "addu $t1, $t0, $t3\n"
    "addiu $t1, $t1, -0x10\n"
    ".L8001C83C:\n"
    "cache 0x01, 0x0($t0) /* handwritten instruction */\n"
    "sltu $at, $t0, $t1\n"
    "bnez $at, .L8001C83C\n"
    "addiu $t0, $t0, (0x80000010 & 0xFFFF)\n"
    "jr $ra\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    ".end func_8001C7E0\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
