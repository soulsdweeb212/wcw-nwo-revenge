/* @header
 * osVirtualToPhysical  (originally func_8001CE80)
 * VRAM 0x8001CE80 | ROM 0x1DA80 | size 0x54
 * asm: asm/nonmatchings/main/osVirtualToPhysical.s
 */
/* SDK: libultra 2.0I, ultralib src/os/virtualtophysical.c (same code as the SDK source). */
#include "common.h"

typedef struct Nw2Node {
    struct Nw2Node *next;
} Nw2Node;

s32 __osProbeTLB(u32);

/* Translates a virtual address to its physical address: KSEG0/KSEG1 addresses
 * are masked, others go through the RCP mapper. */
u32 osVirtualToPhysical(u32 arg0) {
    if (arg0 >= 0x80000000 && arg0 < 0xA0000000)
        return arg0 & 0x1FFFFFFF;
    if (arg0 >= 0xA0000000 && arg0 < 0xC0000000)
        return arg0 & 0x1FFFFFFF;
    return __osProbeTLB(arg0);
}

extern f64 D_8003B6D0;

typedef struct {
    s32 f0;
    u32 f4;
    s32 f8;
} NwAllocHdr;

void alFilterNew(void *, void *, void *, s32);
void *alHeapDBAlloc(void *, void *, NwAllocHdr *, s32, s32);
void alEnvmixerPull(void);
void alEnvmixerParam(void);
