#include "common.h"

extern u8 *D_80046858;
extern s16 D_80047060;

/* Allocate the next free 0xB8-byte scratch block from the pool at D_80046858,
 * zero its used fields, advance the pool cursor and return it. */
u8 *func_80001694(void) {
    volatile u64 pad;
    s32 idx = D_80047060;
    s16 next = idx + 1;
    u8 *block = D_80046858 + idx * 0xB8;

    *(s32 *)(block + 0x0) = 0;
    *(s32 *)(block + 0x4) = 0;
    *(s32 *)(block + 0x8) = 0;
    *(s32 *)(block + 0x24) = 0;
    *(s16 *)(block + 0x2C) = 0;
    *(s16 *)(block + 0x2E) = 0;
    *(s32 *)(block + 0x30) = 0;
    *(s32 *)(block + 0x34) = 0;
    D_80047060 = next;
    return block;
}
