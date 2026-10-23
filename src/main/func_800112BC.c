#include "common.h"

extern u8 D_80059DA8[];

/* Mark the four 0xDC-byte records starting at D_80059DA8: nonzero argument clears
 * bit 0x80 (record in use), zero sets it (record free). */
void func_800112BC(s32 enable) {
    u8 *p;
    s32 i;

    if ((s16)enable) {
        p = D_80059DA8;
        i = 0;
        do {
            i++;
            *p &= 0x7F;
            p += 0xDC;
        } while (i < 4);
    } else {
        p = D_80059DA8;
        i = 0;
        do {
            i++;
            *p |= 0x80;
            p += 0xDC;
        } while (i < 4);
    }
}

extern u8 D_80059D90[];

void releaseHeapBlock(s32);

/* Free the two heap blocks (+0xC and +0x10) of each of the four 0xDC-byte records
 * starting at D_80059D90, and clear the pointers. */
void func_80011264(void) {
    s32 i;
    u8 *p;

    i = 0;
    do {
        i++;
        p = D_80059D90 + (i - 1) * 0xDC;
        releaseHeapBlock(*(s32 *)(p + 0xC));
        releaseHeapBlock(*(s32 *)(p + 0x10));
        *(s32 *)(p + 0xC) = 0;
        *(s32 *)(p + 0x10) = 0;
    } while (i < 4);
}
