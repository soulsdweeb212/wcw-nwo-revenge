/* @header
 * func_80021C40
 * VRAM 0x80021C40 | ROM 0x22840 | size 0x31C
 * asm: asm/nonmatchings/main/func_80021C40.s
 */
/* func_80021C40: libultra bcopy(const void *src, void *dst, s32 len) (src/libc/bcopy.s): copy
 * len bytes from src to dst, safe for overlap (memmove semantics; note bcopy's src-first argument
 * order). Returns dst in $v0; the callers in src/ declare it void. 66 call sites, e.g.
 * __osContRamRead/__osContRamWrite, osPfsFileState, readControllerPakId, loadRspTask, func_80001260.
 * Method: it returns at once when len == 0 or src == dst. It copies backwards (from the top down)
 * only when src < dst < src + len. The two pointer compares are SIGNED (slt), which is fine for
 * KSEG0/KSEG1 pointers. When dst >= src, the end pointer src + len is computed with a trapping
 * `add` (the backward path also uses trapping adds for src + len and dst + len). For a positive len
 * and real RDRAM addresses this cannot overflow. Buffers shorter than 16 bytes, or with different
 * (addr & 3), are copied with lb/sb. Otherwise it copies 1, 2 or 3 bytes up to word alignment
 * (3 bytes = lb + an aligned lh), then 32-byte blocks (eight lw, then eight sw), then 16-byte
 * blocks, then single words, then the 0-3 byte tail. The backward path is the mirror image,
 * aligning the END pointers.
 * A negative len is not checked. If dst < src, the add is skipped and the byte loop runs until
 * the pointer wraps around. If dst >= src and src + len crosses below 0x80000000 (e.g. src =
 * 0x80000010, len = -0x20), the add raises an Integer Overflow exception before any byte is
 * copied. The C models this with addTrap().
 * Kept as asm because the compiler never emits the trapping `add` (marked "handwritten instruction").
 * Checked in an emulator against the ROM bytes: src/dst offsets 0..11 (plus 40/80) with overlap in
 * both directions, len 0..100, plus negative-len overflow cases (e.g. src 0x80000010, dst
 * 0x80000020, len -0x20). Same buffer contents, same $v0, and the same add-overflow trap. */
#ifdef NON_MATCHING
#include "common.h"
/* The asm's three "handwritten instruction" adds are the TRAPPING `add` (not addu): if the signed
 * 32-bit sum overflows, the CPU raises an Integer Overflow exception (Cause ExcCode 12) and no
 * result is written. C has no such operation, so it is one inline-asm instruction here. */
static inline s32 addTrap(s32 a, s32 b)
{
    s32 r;
    __asm__ __volatile__("add %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    return r;
}

void *func_80021C40(const void *src, void *dst, s32 len)
{
    const s8 *s = src;
    s8 *d = dst;
    const s8 *end;

    if (len == 0 || s == (const s8 *)d) {
        return dst;
    }

    /* Signed pointer compares, as the asm uses slt. Copy backwards only when dst
     * lies inside [src, src + len), i.e. a forward copy would clobber unread source. */
    /* The trapping add src + len runs only when dst >= src (the && short-circuit = the asm's
     * bnez over it). */
    if (!((s32)d < (s32)s) && (s32)d < addTrap((s32)s, len)) {
        goto backwards;
    }

    /* ---- forwards ---- */
    if (len >= 16 && ((u32)s & 3) == ((u32)d & 3)) {
        switch ((u32)s & 3) {
        case 0:
            break;
        case 1: /* 3 bytes to the boundary: one byte, then an aligned halfword */
            {
                s8 b0 = s[0];
                s16 h1 = *(const s16 *)(s + 1);
                s += 3;
                d[0] = b0;
                *(s16 *)(d + 1) = h1;
                d += 3;
                len -= 3;
                break;
            }
        case 2:
            *(s16 *)d = *(const s16 *)s;
            s += 2;
            d += 2;
            len -= 2;
            break;
        default: /* 3 */
            *d++ = *s++;
            len -= 1;
            break;
        }
        while (len >= 32) {
            u32 w0 = ((const u32 *)s)[0], w1 = ((const u32 *)s)[1];
            u32 w2 = ((const u32 *)s)[2], w3 = ((const u32 *)s)[3];
            u32 w4 = ((const u32 *)s)[4], w5 = ((const u32 *)s)[5];
            u32 w6 = ((const u32 *)s)[6], w7 = ((const u32 *)s)[7];
            s += 32;
            ((u32 *)d)[0] = w0; ((u32 *)d)[1] = w1;
            ((u32 *)d)[2] = w2; ((u32 *)d)[3] = w3;
            ((u32 *)d)[4] = w4; ((u32 *)d)[5] = w5;
            ((u32 *)d)[6] = w6; ((u32 *)d)[7] = w7;
            d += 32;
            len -= 32;
        }
        while (len >= 16) {
            u32 w0 = ((const u32 *)s)[0], w1 = ((const u32 *)s)[1];
            u32 w2 = ((const u32 *)s)[2], w3 = ((const u32 *)s)[3];
            s += 16;
            ((u32 *)d)[0] = w0; ((u32 *)d)[1] = w1;
            ((u32 *)d)[2] = w2; ((u32 *)d)[3] = w3;
            d += 16;
            len -= 16;
        }
        while (len >= 4) {
            *(u32 *)d = *(const u32 *)s;
            s += 4;
            d += 4;
            len -= 4;
        }
    }
    /* Byte copy: short or mutually misaligned buffers, and the 0..3 byte tail. */
    if (len == 0) {
        return dst;
    }
    end = s + len;
    do {
        *d++ = *s++;
    } while (s != end);
    return dst;

backwards:
    /* Overlap with dst above src: copy from the top down. */
    s = (const s8 *)addTrap((s32)s, len); /* trapping add, src first as in the asm */
    d = (s8 *)addTrap((s32)d, len);
    if (len >= 16 && ((u32)s & 3) == ((u32)d & 3)) {
        switch ((u32)s & 3) {
        case 0:
            break;
        case 3: /* 3 bytes down to the boundary: one byte, then an aligned halfword */
            {
                s8 b0 = s[-1];
                s16 h1 = *(const s16 *)(s - 3);
                s -= 3;
                d[-1] = b0;
                *(s16 *)(d - 3) = h1;
                d -= 3;
                len -= 3;
                break;
            }
        case 2:
            *(s16 *)(d - 2) = *(const s16 *)(s - 2);
            s -= 2;
            d -= 2;
            len -= 2;
            break;
        default: /* 1 */
            *--d = *--s;
            len -= 1;
            break;
        }
        while (len >= 32) {
            u32 w0 = ((const u32 *)s)[-1], w1 = ((const u32 *)s)[-2];
            u32 w2 = ((const u32 *)s)[-3], w3 = ((const u32 *)s)[-4];
            u32 w4 = ((const u32 *)s)[-5], w5 = ((const u32 *)s)[-6];
            u32 w6 = ((const u32 *)s)[-7], w7 = ((const u32 *)s)[-8];
            s -= 32;
            ((u32 *)d)[-1] = w0; ((u32 *)d)[-2] = w1;
            ((u32 *)d)[-3] = w2; ((u32 *)d)[-4] = w3;
            ((u32 *)d)[-5] = w4; ((u32 *)d)[-6] = w5;
            ((u32 *)d)[-7] = w6; ((u32 *)d)[-8] = w7;
            d -= 32;
            len -= 32;
        }
        while (len >= 16) {
            u32 w0 = ((const u32 *)s)[-1], w1 = ((const u32 *)s)[-2];
            u32 w2 = ((const u32 *)s)[-3], w3 = ((const u32 *)s)[-4];
            s -= 16;
            ((u32 *)d)[-1] = w0; ((u32 *)d)[-2] = w1;
            ((u32 *)d)[-3] = w2; ((u32 *)d)[-4] = w3;
            d -= 16;
            len -= 16;
        }
        while (len >= 4) {
            ((u32 *)d)[-1] = ((const u32 *)s)[-1];
            s -= 4;
            d -= 4;
            len -= 4;
        }
    }
    if (len == 0) {
        return dst;
    }
    s--;
    d--;
    end = s - len;
    do {
        *d-- = *s--;
    } while (s != end);
    return dst;
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    "\n"
    ".globl func_80021C40\n"
    ".ent func_80021C40\n"
    "func_80021C40:\n"
    "beqz $a2, .L80021CB0\n"
    "addu $a3, $a1, $zero\n"
    "beq $a0, $a1, .L80021CB0\n"
    "nop\n"
    "slt $at, $a1, $a0\n"
    "bnez $at, .L80021C74\n"
    "nop\n"
    "add $v0, $a0, $a2 /* handwritten instruction */\n"
    "slt $at, $a1, $v0\n"
    "beqz $at, .L80021C74\n"
    "nop\n"
    "b .L80021DE0\n"
    "nop\n"
    ".L80021C74:\n"
    "slti $at, $a2, 0x10\n"
    "bnez $at, .L80021C90\n"
    "nop\n"
    "andi $v0, $a0, 0x3\n"
    "andi $v1, $a1, 0x3\n"
    "beq $v0, $v1, .L80021CB8\n"
    "nop\n"
    ".L80021C90:\n"
    "beqz $a2, .L80021CB0\n"
    "nop\n"
    "addu $v1, $a0, $a2\n"
    ".L80021C9C:\n"
    "lb $v0, 0x0($a0)\n"
    "addiu $a0, $a0, 0x1\n"
    "sb $v0, 0x0($a1)\n"
    "bne $a0, $v1, .L80021C9C\n"
    "addiu $a1, $a1, 0x1\n"
    ".L80021CB0:\n"
    "jr $ra\n"
    "addu $v0, $a3, $zero\n"
    ".L80021CB8:\n"
    "beqz $v0, .L80021D24\n"
    "nop\n"
    "addiu $at, $zero, 0x1\n"
    "beq $v0, $at, .L80021D08\n"
    "nop\n"
    "addiu $at, $zero, 0x2\n"
    "beq $v0, $at, .L80021CF0\n"
    "nop\n"
    "lb $v0, 0x0($a0)\n"
    "addiu $a0, $a0, 0x1\n"
    "sb $v0, 0x0($a1)\n"
    "addiu $a1, $a1, 0x1\n"
    "b .L80021D24\n"
    "addiu $a2, $a2, -0x1\n"
    ".L80021CF0:\n"
    "lh $v0, 0x0($a0)\n"
    "addiu $a0, $a0, 0x2\n"
    "sh $v0, 0x0($a1)\n"
    "addiu $a1, $a1, 0x2\n"
    "b .L80021D24\n"
    "addiu $a2, $a2, -0x2\n"
    ".L80021D08:\n"
    "lb $v0, 0x0($a0)\n"
    "lh $v1, 0x1($a0)\n"
    "addiu $a0, $a0, 0x3\n"
    "sb $v0, 0x0($a1)\n"
    "sh $v1, 0x1($a1)\n"
    "addiu $a1, $a1, 0x3\n"
    "addiu $a2, $a2, -0x3\n"
    ".L80021D24:\n"
    "slti $at, $a2, 0x20\n"
    "bnez $at, .L80021D80\n"
    "nop\n"
    "lw $v0, 0x0($a0)\n"
    "lw $v1, 0x4($a0)\n"
    "lw $t0, 0x8($a0)\n"
    "lw $t1, 0xC($a0)\n"
    "lw $t2, 0x10($a0)\n"
    "lw $t3, 0x14($a0)\n"
    "lw $t4, 0x18($a0)\n"
    "lw $t5, 0x1C($a0)\n"
    "addiu $a0, $a0, 0x20\n"
    "sw $v0, 0x0($a1)\n"
    "sw $v1, 0x4($a1)\n"
    "sw $t0, 0x8($a1)\n"
    "sw $t1, 0xC($a1)\n"
    "sw $t2, 0x10($a1)\n"
    "sw $t3, 0x14($a1)\n"
    "sw $t4, 0x18($a1)\n"
    "sw $t5, 0x1C($a1)\n"
    "addiu $a1, $a1, 0x20\n"
    "b .L80021D24\n"
    "addiu $a2, $a2, -0x20\n"
    ".L80021D80:\n"
    "slti $at, $a2, 0x10\n"
    "bnez $at, .L80021DBC\n"
    "nop\n"
    "lw $v0, 0x0($a0)\n"
    "lw $v1, 0x4($a0)\n"
    "lw $t0, 0x8($a0)\n"
    "lw $t1, 0xC($a0)\n"
    "addiu $a0, $a0, 0x10\n"
    "sw $v0, 0x0($a1)\n"
    "sw $v1, 0x4($a1)\n"
    "sw $t0, 0x8($a1)\n"
    "sw $t1, 0xC($a1)\n"
    "addiu $a1, $a1, 0x10\n"
    "b .L80021D80\n"
    "addiu $a2, $a2, -0x10\n"
    ".L80021DBC:\n"
    "slti $at, $a2, 0x4\n"
    "bnez $at, .L80021C90\n"
    "nop\n"
    "lw $v0, 0x0($a0)\n"
    "addiu $a0, $a0, 0x4\n"
    "sw $v0, 0x0($a1)\n"
    "addiu $a1, $a1, 0x4\n"
    "b .L80021DBC\n"
    "addiu $a2, $a2, -0x4\n"
    ".L80021DE0:\n"
    "add $a0, $a0, $a2 /* handwritten instruction */\n"
    "add $a1, $a1, $a2 /* handwritten instruction */\n"
    "slti $at, $a2, 0x10\n"
    "bnez $at, .L80021E04\n"
    "nop\n"
    "andi $v0, $a0, 0x3\n"
    "andi $v1, $a1, 0x3\n"
    "beq $v0, $v1, .L80021E34\n"
    "nop\n"
    ".L80021E04:\n"
    "beqz $a2, .L80021CB0\n"
    "nop\n"
    "addiu $a0, $a0, -0x1\n"
    "addiu $a1, $a1, -0x1\n"
    "subu $v1, $a0, $a2\n"
    ".L80021E18:\n"
    "lb $v0, 0x0($a0)\n"
    "addiu $a0, $a0, -0x1\n"
    "sb $v0, 0x0($a1)\n"
    "bne $a0, $v1, .L80021E18\n"
    "addiu $a1, $a1, -0x1\n"
    "jr $ra\n"
    "addu $v0, $a3, $zero\n"
    ".L80021E34:\n"
    "beqz $v0, .L80021EA0\n"
    "nop\n"
    "addiu $at, $zero, 0x3\n"
    "beq $v0, $at, .L80021E84\n"
    "nop\n"
    "addiu $at, $zero, 0x2\n"
    "beq $v0, $at, .L80021E6C\n"
    "nop\n"
    "lb $v0, -0x1($a0)\n"
    "addiu $a0, $a0, -0x1\n"
    "sb $v0, -0x1($a1)\n"
    "addiu $a1, $a1, -0x1\n"
    "b .L80021EA0\n"
    "addiu $a2, $a2, -0x1\n"
    ".L80021E6C:\n"
    "lh $v0, -0x2($a0)\n"
    "addiu $a0, $a0, -0x2\n"
    "sh $v0, -0x2($a1)\n"
    "addiu $a1, $a1, -0x2\n"
    "b .L80021EA0\n"
    "addiu $a2, $a2, -0x2\n"
    ".L80021E84:\n"
    "lb $v0, -0x1($a0)\n"
    "lh $v1, -0x3($a0)\n"
    "addiu $a0, $a0, -0x3\n"
    "sb $v0, -0x1($a1)\n"
    "sh $v1, -0x3($a1)\n"
    "addiu $a1, $a1, -0x3\n"
    "addiu $a2, $a2, -0x3\n"
    ".L80021EA0:\n"
    "slti $at, $a2, 0x20\n"
    "bnez $at, .L80021EFC\n"
    "nop\n"
    "lw $v0, -0x4($a0)\n"
    "lw $v1, -0x8($a0)\n"
    "lw $t0, -0xC($a0)\n"
    "lw $t1, -0x10($a0)\n"
    "lw $t2, -0x14($a0)\n"
    "lw $t3, -0x18($a0)\n"
    "lw $t4, -0x1C($a0)\n"
    "lw $t5, -0x20($a0)\n"
    "addiu $a0, $a0, -0x20\n"
    "sw $v0, -0x4($a1)\n"
    "sw $v1, -0x8($a1)\n"
    "sw $t0, -0xC($a1)\n"
    "sw $t1, -0x10($a1)\n"
    "sw $t2, -0x14($a1)\n"
    "sw $t3, -0x18($a1)\n"
    "sw $t4, -0x1C($a1)\n"
    "sw $t5, -0x20($a1)\n"
    "addiu $a1, $a1, -0x20\n"
    "b .L80021EA0\n"
    "addiu $a2, $a2, -0x20\n"
    ".L80021EFC:\n"
    "slti $at, $a2, 0x10\n"
    "bnez $at, .L80021F38\n"
    "nop\n"
    "lw $v0, -0x4($a0)\n"
    "lw $v1, -0x8($a0)\n"
    "lw $t0, -0xC($a0)\n"
    "lw $t1, -0x10($a0)\n"
    "addiu $a0, $a0, -0x10\n"
    "sw $v0, -0x4($a1)\n"
    "sw $v1, -0x8($a1)\n"
    "sw $t0, -0xC($a1)\n"
    "sw $t1, -0x10($a1)\n"
    "addiu $a1, $a1, -0x10\n"
    "b .L80021EFC\n"
    "addiu $a2, $a2, -0x10\n"
    ".L80021F38:\n"
    "slti $at, $a2, 0x4\n"
    "bnez $at, .L80021E04\n"
    "nop\n"
    "lw $v0, -0x4($a0)\n"
    "addiu $a0, $a0, -0x4\n"
    "sw $v0, -0x4($a1)\n"
    "addiu $a1, $a1, -0x4\n"
    "b .L80021F38\n"
    "addiu $a2, $a2, -0x4\n"
    "nop\n"
    ".end func_80021C40\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
