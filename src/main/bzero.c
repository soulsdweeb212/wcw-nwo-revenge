/* @header
 * bzero  (originally func_80021F60)
 * VRAM 0x80021F60 | ROM 0x22B60 | size 0xA0
 * asm: asm/nonmatchings/main/bzero.s
 */
/* bzero: libultra bzero(void *dst, s32 len) (src/libc/bzero.s): zero len bytes at dst.
 * 26 call sites in 20 functions, e.g. allocateHeap, osCartRomInit,
 * osPfsDeleteFile, func_80000700/80000A40, __osViInit, func_8002A2FC, osPfsChecker
 * (eight of the functions are in code_80090000).
 * Method: below 12 bytes it zeroes byte by byte. Otherwise one `swl $0` zeroes the 1-3 bytes up to
 * the next word boundary in a single store, then 32-byte blocks of eight sw, then single words,
 * then the 0-3 byte tail with sb. len <= 0 writes nothing (the final test is blez).
 * The instruction order is what the IRIX assembler makes of the ultralib source (the last sw of
 * each loop sits in the bne delay slot; nops follow the blt expansion). It must stay asm because
 * the C compiler never emits a lone swl. The C below writes those head bytes one at a time, which
 * leaves memory in the same state. Checked in a MIPS emulator against the ROM bytes: offsets 0..7,
 * lengths -2..69, 100, 129, 160. Same final memory every time. */
#ifdef TARGET_PC
/* PC: the C version below cannot run on a PC: it finds the next word boundary and the end of each loop by casting the
 * address to a 32-bit integer, which cuts a 64-bit pointer in half. What the N64 routine leaves in memory is simple:
 * len bytes from dst are zero, and a len of 0 or less writes nothing (every path ends at the blez on the remaining
 * length). So the PC zeroes the same bytes in one call. port.h renames bzero to port_bzero. __builtin_memset is the
 * compiler's memset; it needs no system header, which would have to come before common.h (port.h). */
#include "common.h"
void bzero(void *dst, s32 len)
{
    if (len > 0) {
        __builtin_memset(dst, 0, (size_t)len);
    }
}
#else
#ifdef NON_MATCHING
#include "common.h"
void bzero(void *dst, s32 len)
{
    u8 *p = dst;
    u8 *end;
    s32 n;

    if (len >= 12) {
        /* Bytes needed to reach the next word boundary (0..3). */
        n = -(s32)p & 3;
        len -= n;
        if (n != 0) {
            /* swl $0: zero from p up to the end of its word in one store. */
            u8 *q = p;
            do { *q++ = 0; } while ((u32)q & 3);
            p += n;
        }
        /* 32-byte blocks. */
        n = len & ~31;
        len -= n;
        if (n != 0) {
            end = p + n;
            do {
                ((u32 *)p)[0] = 0; ((u32 *)p)[1] = 0;
                ((u32 *)p)[2] = 0; ((u32 *)p)[3] = 0;
                ((u32 *)p)[4] = 0; ((u32 *)p)[5] = 0;
                ((u32 *)p)[6] = 0; ((u32 *)p)[7] = 0;
                p += 32;
            } while (p != end);
        }
        /* Remaining whole words. */
        n = len & ~3;
        len -= n;
        if (n != 0) {
            end = p + n;
            do {
                *(u32 *)p = 0;
                p += 4;
            } while (p != end);
        }
    }
    /* Trailing bytes (or the whole buffer when len < 12). */
    if (len > 0) {
        end = p + len;
        do {
            *p++ = 0;
        } while (p != end);
    }
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    ".globl bzero\n"
    "bzero:\n"
    "negu $3,$4\n"
    "slti $1,$5,0xC\n"
    "bnez $1,5f\n"
    "nop\n"
    "andi $3,$3,0x3\n"
    "beqz $3,1f\n"
    "subu $5,$5,$3\n"
    "swl $0,0($4)\n"
    "addu $4,$4,$3\n"
    "1:\n"
    "addiu $1,$0,-0x20\n"
    "and $7,$5,$1\n"
    "beqz $7,3f\n"
    "subu $5,$5,$7\n"
    "addu $7,$7,$4\n"
    "2:\n"
    "sw $0,0($4)\n"
    "sw $0,4($4)\n"
    "sw $0,8($4)\n"
    "sw $0,0xC($4)\n"
    "addiu $4,$4,0x20\n"
    "sw $0,-0x10($4)\n"
    "sw $0,-0xC($4)\n"
    "sw $0,-0x8($4)\n"
    "bne $4,$7,2b\n"
    "sw $0,-0x4($4)\n"
    "3:\n"
    "addiu $1,$0,-0x4\n"
    "and $7,$5,$1\n"
    "beqz $7,5f\n"
    "subu $5,$5,$7\n"
    "addu $7,$7,$4\n"
    "4:\n"
    "addiu $4,$4,4\n"
    "bne $4,$7,4b\n"
    "sw $0,-4($4)\n"
    "5:\n"
    "blez $5,7f\n"
    "nop\n"
    "addu $5,$5,$4\n"
    "6:\n"
    "addiu $4,$4,1\n"
    "bne $4,$5,6b\n"
    "sb $0,-1($4)\n"
    "7:\n"
    "jr $31\n"
    "nop\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
#endif
