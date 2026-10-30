/* @header
 * func_8001CE80
 * VRAM 0x8001CE80 | ROM 0x1DA80 | size 0x54
 * asm: asm/nonmatchings/main/func_8001CE80.s
 */
#include "common.h"

typedef struct Nw2Node {
    struct Nw2Node *next;
} Nw2Node;

s32 func_80026B50(u32);

/* Translates a virtual address to its physical address: KSEG0/KSEG1 addresses
 * are masked, others go through the RCP mapper. */
u32 func_8001CE80(u32 arg0) {
    if (arg0 >= 0x80000000 && arg0 < 0xA0000000)
        return arg0 & 0x1FFFFFFF;
    if (arg0 >= 0xA0000000 && arg0 < 0xC0000000)
        return arg0 & 0x1FFFFFFF;
    return func_80026B50(arg0);
}

extern f64 D_8003B6D0;

typedef struct {
    s32 f0;
    u32 f4;
    s32 f8;
} NwAllocHdr;

void func_8001F070(void *, void *, void *, s32);
void *func_800202B0(void *, void *, NwAllocHdr *, s32, s32);
void func_8001E340(void);
void func_8001E88C(void);
