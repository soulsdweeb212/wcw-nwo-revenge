#include "common.h"

typedef struct Nw2Node {
    struct Nw2Node *next;
} Nw2Node;

/* Unlinks node arg1 from the singly-linked list whose head pointer is *arg0. */
void func_8001CE40(Nw2Node **arg0, Nw2Node *arg1) {
    Nw2Node **pp;
    Nw2Node *v;

    pp = arg0;
    v = *pp;
    if (v != NULL) {
        do {
            if (v == arg1) {
                *pp = v->next;
                return;
            }
            pp = (Nw2Node **)v;
            v = *pp;
        } while (v != NULL);
    }
}

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

/* Builds a pitch/volume envelope table: sets the count and initial pitch from
 * the input s16, clears the eight s16 slots, stores the base value at +0x18 and
 * fills slots 9..15 with successive powers of the ratio. */
void func_8001CEF0(u8 *arg0) {
    s16 v;
    s32 i;
    f64 r;
    f64 p;

    v = *(s16 *)arg0 >> 1;
    *(s32 *)(arg0 + 0x2C) = 1;
    *(s16 *)(arg0 + 2) = 0x4000 - v;
    for (i = 7; i >= 0; i--)
        *(s16 *)(arg0 + i * 2 + 8) = 0;
    r = (f64)v / D_8003B6D0;
    *(s16 *)(arg0 + 0x18) = v;
    p = r;
    for (i = 9; i < 16; i++) {
        p = p * r;
        *(s16 *)(arg0 + i * 2 + 8) = (s16)(s32)(p * D_8003B6D0);
    }
}

typedef struct {
    s32 f0;
    u32 f4;
    s32 f8;
} NwAllocHdr;

void func_8001F070(void *, void *, void *, s32);
void *func_800202B0(void *, void *, NwAllocHdr *, s32, s32);
void func_8001E340(void);
void func_8001E88C(void);

/* Initializes the audio voice object arg0: installs the callbacks, allocates a
 * 0x50-byte work record from arg1 and sets all the counter/flag fields. */
void func_8001D42C(s32 *arg0, NwAllocHdr *arg1) {
    func_8001F070(arg0, func_8001E340, func_8001E88C, 4);
    *(s32 *)((u8 *)arg0 + 0x14) = (s32)func_800202B0(NULL, NULL, arg1, 1, 0x50);
    *(s32 *)((u8 *)arg0 + 0x38) = 1;
    *(s32 *)((u8 *)arg0 + 0x48) = 0;
    *(s16 *)((u8 *)arg0 + 0x1A) = 1;
    *(s16 *)((u8 *)arg0 + 0x28) = 1;
    *(s16 *)((u8 *)arg0 + 0x2E) = 1;
    *(s16 *)((u8 *)arg0 + 0x1C) = 1;
    *(s16 *)((u8 *)arg0 + 0x1E) = 1;
    *(s16 *)((u8 *)arg0 + 0x20) = 0;
    *(s16 *)((u8 *)arg0 + 0x22) = 0;
    *(s16 *)((u8 *)arg0 + 0x26) = 1;
    *(s16 *)((u8 *)arg0 + 0x24) = 0;
    *(s16 *)((u8 *)arg0 + 0x26) = 1;
    *(s16 *)((u8 *)arg0 + 0x24) = 0;
    *(s32 *)((u8 *)arg0 + 0x30) = 0;
    *(s32 *)((u8 *)arg0 + 0x34) = 0;
    *(s16 *)((u8 *)arg0 + 0x18) = 0;
    *(s32 *)((u8 *)arg0 + 0x3C) = 0;
    *(s32 *)((u8 *)arg0 + 0x40) = 0;
    *(s32 *)((u8 *)arg0 + 0x44) = 0;
}
