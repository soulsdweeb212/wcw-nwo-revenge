#include "common.h"

typedef struct Nw2Node {
    struct Nw2Node *next;
} Nw2Node;

s32 func_80026B50(u32);

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
