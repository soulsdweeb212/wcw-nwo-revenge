/* @header
 * func_800ADF40
 * VRAM 0x800ADF40 | ROM 0xA13E0 | size 0x78
 * asm: asm/nonmatchings/code_8009D7A0/func_800ADF40.s
 */
#include "common.h"

s32 func_800D4148(void);

/* Walk a -1-terminated (threshold, value) pair table and return the value of the
 * first pair whose threshold is >= func_800D4148(), or 0 if none. */
s16 func_800ADF40(s16 *pairs)
{
    s16 current;
    s16 *p;
    p = pairs;
    current = func_800D4148();
    while (*p != -1)
    {
        if (*p >= current)
            return p[1];
        p += 2;
    }
    return 0;
}
