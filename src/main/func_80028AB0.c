/* @header
 * func_80028AB0
 * VRAM 0x80028AB0 | ROM 0x296B0 | size 0x98
 * asm: asm/nonmatchings/main/func_80028AB0.s
 */
#include "common.h"

extern u8 asciiCharTable[];
extern u8 sjisCodeTable[];
/* Converts up to arg2 (max 255) ASCII characters from arg1 into their two-byte
 * Shift-JIS codes at arg0, NUL-terminating the result. Returns the end cursor. */
u8 *func_80028AB0(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 work[2];
    s32 i, k; u8 *p; u8 c;
    arg2 &= 0xFF; i = 0;
    if (arg2 > 0) {
        do {
            c = *arg1; p = asciiCharTable; k = 0;
            do {
                if (*p == c) goto match;
                p++; k++;
            } while (*p != 0);
            k = 0;
        match:
            arg0[0] = sjisCodeTable[k*2];
            arg0[1] = sjisCodeTable[k*2+1];
            arg1++; arg0 += 2;
            if (*arg1 == 0) break;
            i++;
        } while (i < arg2);
    }
    *arg0 = 0; return arg0;
}
