#include "common.h"

/* Entity s16 accessor: returns the +0x12 field when u64 flags at +0x20 has
 * bit 0x80000 set, otherwise the +0x10 field. */
s32 func_800BF2FC(void *entity) {
    s32 value;

    if (*(u64 *)((u8 *)entity + 0x20) & 0x80000) {
        value = *(s16 *)((u8 *)entity + 0x12);
    } else {
        value = *(s16 *)((u8 *)entity + 0x10);
    }
    return value;
}

extern u8 D_800F9D30[];
extern u8 D_800F9D34[];

s8 func_800D26A0(void *, s32, s8);
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
void func_800D3890(void *, void *, void *);
extern u8 D_800F9D7C[];

void func_800D3E40(void *, void *, s32, void *);
