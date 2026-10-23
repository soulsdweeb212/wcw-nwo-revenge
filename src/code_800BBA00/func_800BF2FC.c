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

s32 func_800BFC90(s8 arg0) {
    s32 off = arg0 * 0x3B0;
    s32 r = 1;
    if (!(*(u64 *)(D_800F9D30 + off) & 0x40000ULL) &&
        !(*(u64 *)(D_800F9D34 + off) & 0x40000ULL))
        r = 0;
    return r;
}

s8 func_800D26A0(void *, s32, s8);
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
void func_800D3890(void *, void *, void *);
extern u8 D_800F9D7C[];

s32 func_800BF150(void *arg0, s8 *arg1) {
    s8 idx = func_800D26A0(arg0, 0, *arg1);
    s32 buf[4];

    if (idx == -1)
        return 0;
    func_800D3890((u8 *)arg0 + 0x6C, D_800F9D7C + idx * 0x3B0, buf);
    if (func_800D3550(func_800D3684(*(s32 *)((u8 *)arg0 + 0x58), buf[3])) < 0x400)
        return 1;
    return 0;
}

void func_800D3E40(void *, void *, s32, void *);

void func_800BE450(void *arg0, void *arg1) {
    f32 buf[4];
    void *p = (u8 *)arg1 + 0x4C;

    buf[0] = 1.43f;
    buf[2] = 27.77f;
    func_800D3E40((u8 *)arg1 + 0x6C, buf, *(s32 *)((u8 *)arg1 + 0x58), p);
    buf[0] = 0.0f;
    buf[2] = 73.5f;
    func_800D3E40(p, buf, *(s32 *)((u8 *)arg1 + 0x58), (u8 *)arg0 + 0x4C);
}
