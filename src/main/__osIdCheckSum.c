/* @header
 * __osIdCheckSum  (originally func_80022154)
 * VRAM 0x80022154 | ROM 0x22D54 | size 0x44
 * asm: asm/nonmatchings/main/__osIdCheckSum.s
 */
/* SDK: libultra 2.0I, ultralib src/io/contpfs.c (same code as the SDK source). */
#include "common.h"

/* Compute the 14-word checksum pair (sum and complement-sum) for the 0x20-byte
 * command block. */
s32 __osIdCheckSum(u16 *arg0, u16 *arg1, u16 *arg2) {
    u16 *end = arg0 + 14;
    u16 v;

    *arg2 = 0;
    *arg1 = 0;
    do {
        v = *arg0;
        *arg1 += v;
        arg0++;
        *arg2 += ~v;
    } while (arg0 < end);
    return 0;
}

s32 __osContRamRead(s32, s32, s32, void *);
s32 __osPfsSelectBank(void *, s32);
s32 bcmp(void *, void *, s32);

typedef struct {
    u8 b[8];
} Ent8;

extern Ent8 D_8006A260[];
