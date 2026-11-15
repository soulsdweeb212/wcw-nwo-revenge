/* @header
 * func_800B64EC
 * VRAM 0x800B64EC | ROM 0x62C5C | size 0x5C
 * asm: asm/nonmatchings/code_80090000/func_800B64EC.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a pack keeps the N64's byte order, as it comes from the ROM: a 32-bit count, then a 32-bit offset for each entry
 * (from the pack's start), then the entries. The N64 builds the count from its four bytes the other way round, so a
 * pack of 0x28 entries counts as 0x28000000 and the test below never turns an index away; the PC builds it from the
 * same bytes, the same way, and gets the same number. Each offset is read big-endian (port.h's READ_BE32), as the N64
 * reads it. */
u8 *func_800B64EC(u8 *a, s32 i) {
    u32 n = ((u32)a[3] << 24) | (a[2] << 16) | (a[1] << 8) | a[0];
    if (i < 0 || (u32)i >= n) {
        return a;
    }
    return a + (s32)READ_BE32(a + 4 + 4 * i);
}
#else
u8 *func_800B64EC(u8 *a, s32 i) {
    u32 n = (a[3] << 24) | (a[2] << 16) | (a[1] << 8) | a[0];
    if (i < 0 || (u32)i >= n) {
        return a;
    }
    return a + ((s32 *)(a + 4))[i];
}
#endif
