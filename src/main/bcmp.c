/* @header
 * bcmp  (originally func_80027FF0)
 * VRAM 0x80027FF0 | ROM 0x28BF0 | size 0x110
 * asm: asm/nonmatchings/main/bcmp.s
 */
/* bcmp: libultra bcmp(void *s1, void *s2, s32 len) (src/libc/bcmp.s): returns 0 if the len
 * bytes are identical, 1 otherwise (not an ordering like memcmp). Only caller in the ROM: __osCheckId
 * (compares the Controller Pak ID block against the cached copy); func_80022154 declares it but
 * never calls it.
 * Method: below 16 bytes it compares byte by byte. If s1 and s2 have the same alignment
 * ((s1 ^ s2) & 3 == 0), it compares the 1-3 head bytes with one `lwl` from each side, then whole
 * words. The `move $v0, $v1` before the two lwl makes the bytes lwl does not load equal on both
 * sides, so only the head bytes count. If the alignments differ, it compares bytes until s2 is
 * word aligned, then compares unaligned words of s1 (lwl/lwr) against aligned lw of s2. The 0-3
 * byte tail is compared with lbu. len <= 0 returns 0.
 * Kept as asm because the compiler never emits the lone lwl / register-preload trick.
 * Checked in an emulator against the ROM bytes: all 16 alignment pairs, len -1..77, equal buffers
 * and a single differing byte at many positions. Same result every time. */
#ifdef NON_MATCHING
#include "common.h"
/* Big-endian word read from a possibly unaligned address (the asm's lwl/lwr pair). */
static inline u32 loadWordUnaligned(const u8 *p)
{
    return ((u32)p[0] << 24) | ((u32)p[1] << 16) | ((u32)p[2] << 8) | p[3];
}

s32 bcmp(void *s1, void *s2, s32 len)
{
    const u8 *a = s1;
    const u8 *b = s2;
    const u8 *end;
    s32 n;

    if (len >= 16) {
        if ((((u32)a ^ (u32)b) & 3) == 0) {
            /* Same alignment: compare the 0..3 head bytes up to a word boundary
             * (the asm does this with one lwl from each side), then whole words. */
            n = -(s32)a & 3;
            len -= n;
            if (n != 0) {
                s32 i;
                for (i = 0; i < n; i++) {
                    if (a[i] != b[i]) {
                        return 1;
                    }
                }
                a += n;
                b += n;
            }
            n = len & ~3;
            len -= n;
            if (n != 0) {
                end = a + n;
                do {
                    if (*(const u32 *)a != *(const u32 *)b) {
                        return 1;
                    }
                    a += 4;
                    b += 4;
                } while (a != end);
            }
        } else {
            /* Different alignment: byte-compare until s2 is word aligned, then
             * compare unaligned words of s1 against aligned words of s2. */
            n = -(s32)b & 3;
            len -= n;
            if (n != 0) {
                end = a + n;
                do {
                    if (*a != *b) {
                        return 1;
                    }
                    a++;
                    b++;
                } while (a != end);
            }
            n = len & ~3;
            len -= n;
            if (n != 0) {
                end = a + n;
                do {
                    if (loadWordUnaligned(a) != *(const u32 *)b) {
                        return 1;
                    }
                    a += 4;
                    b += 4;
                } while (a != end);
            }
        }
    }
    /* Tail bytes (or everything when len < 16). len <= 0 compares nothing. */
    if (len > 0) {
        end = a + len;
        do {
            if (*a != *b) {
                return 1;
            }
            a++;
            b++;
        } while (a != end);
    }
    return 0;
}
#else
/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */
asm(
    ".set noreorder\n"
    ".set noat\n"
    ".globl bcmp\n"
    ".ent bcmp\n"
    "bcmp:\n"
    "xor $v0, $a0, $a1\n"
    "slti $at, $a2, 0x10\n"
    "bnez $at, .L800280CC\n"
    "nop\n"
    "andi $v0, $v0, 0x3\n"
    "bnez $v0, .L80028068\n"
    "negu $t8, $a0\n"
    "andi $t8, $t8, 0x3\n"
    "beqz $t8, .L80028030\n"
    "subu $a2, $a2, $t8\n"
    "addu $v0, $v1, $zero\n"
    "lwl $v0, 0x0($a0)\n"
    "lwl $v1, 0x0($a1)\n"
    "addu $a0, $a0, $t8\n"
    "bne $v0, $v1, .L800280F8\n"
    "addu $a1, $a1, $t8\n"
    ".L80028030:\n"
    "addiu $at, $zero, -0x4\n"
    "and $a3, $a2, $at\n"
    "beqz $a3, .L800280CC\n"
    "subu $a2, $a2, $a3\n"
    "addu $a3, $a3, $a0\n"
    ".L80028044:\n"
    "lw $v0, 0x0($a0)\n"
    "lw $v1, 0x0($a1)\n"
    "addiu $a0, $a0, 0x4\n"
    "bne $v0, $v1, .L800280F8\n"
    "addiu $a1, $a1, 0x4\n"
    "bne $a0, $a3, .L80028044\n"
    "nop\n"
    "b .L800280CC\n"
    "nop\n"
    ".L80028068:\n"
    "negu $a3, $a1\n"
    "andi $a3, $a3, 0x3\n"
    "beqz $a3, .L80028098\n"
    "subu $a2, $a2, $a3\n"
    "addu $a3, $a3, $a0\n"
    ".L8002807C:\n"
    "lbu $v0, 0x0($a0)\n"
    "lbu $v1, 0x0($a1)\n"
    "addiu $a0, $a0, 0x1\n"
    "bne $v0, $v1, .L800280F8\n"
    "addiu $a1, $a1, 0x1\n"
    "bne $a0, $a3, .L8002807C\n"
    "nop\n"
    ".L80028098:\n"
    "addiu $at, $zero, -0x4\n"
    "and $a3, $a2, $at\n"
    "beqz $a3, .L800280CC\n"
    "subu $a2, $a2, $a3\n"
    "addu $a3, $a3, $a0\n"
    ".L800280AC:\n"
    "lwl $v0, 0x0($a0)\n"
    "lwr $v0, 0x3($a0)\n"
    "lw $v1, 0x0($a1)\n"
    "addiu $a0, $a0, 0x4\n"
    "bne $v0, $v1, .L800280F8\n"
    "addiu $a1, $a1, 0x4\n"
    "bne $a0, $a3, .L800280AC\n"
    "nop\n"
    ".L800280CC:\n"
    "blez $a2, .L800280F0\n"
    "addu $a3, $a2, $a0\n"
    ".L800280D4:\n"
    "lbu $v0, 0x0($a0)\n"
    "lbu $v1, 0x0($a1)\n"
    "addiu $a0, $a0, 0x1\n"
    "bne $v0, $v1, .L800280F8\n"
    "addiu $a1, $a1, 0x1\n"
    "bne $a0, $a3, .L800280D4\n"
    "nop\n"
    ".L800280F0:\n"
    "jr $ra\n"
    "addu $v0, $zero, $zero\n"
    ".L800280F8:\n"
    "jr $ra\n"
    "addiu $v0, $zero, 0x1\n"
    ".end bcmp\n"
    ".set at\n"
    ".set reorder\n"
    );
#endif
