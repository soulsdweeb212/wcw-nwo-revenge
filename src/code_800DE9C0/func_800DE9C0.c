#include "common.h"

extern u8 D_8007EF30[];
extern u16 D_800E3CD0[];
extern u16 D_800E3CD8[];
void func_800A6C48(void *, s32);
s16 func_800A76FC(void *, u16);
s16 func_800D7B08(u16, u64);
s8 func_800D8DF0(void *);
void func_800E212C(void *);

s32 func_800DE9C0(void *entity, void *other, s32 mask, s32 flags3, u16 arg4)
{
    u8 *e0 = entity;
    u8 *e1 = other;
    s32 m = mask;
    u64 f0;
    u64 f1;
    u64 fa;
    s16 r;
    u8 *att;

    if ((flags3 & 0x8000) == 0) {
        return 0;
    }
    if ((*(u16 *)(D_8007EF30 + 0x170) & 0x404) == 0) {
        if ((*(u64 *)(e0 + 0x20) & 0x40ULL) != 0 && (*(u64 *)(e1 + 0x20) & 0x100ULL) != 0) {
            *(s16 *)(e0 + 0x3E) = func_800A76FC(e0, arg4);
            func_800A6C48(e0, 0x64);
            func_800E212C(e0);
            return 1;
        }
        if ((*(u64 *)(e0 + 0x20) & 0x80ULL) != 0 && (*(u64 *)(e1 + 0x20) & 0x100ULL) != 0
            && (*(u64 *)(*(u8 **)(e0 + 0x364) + 0x38) & 0x100000ULL) != 0
            && (D_800E3CD0[*(s16 *)(e0 + 0x3C)] & m) != 0) {
            func_800A6C48(e0, 0x67);
            return 1;
        }
    }
    if ((*(u64 *)(e0 + 0x20) & 0x80ULL) != 0 && (*(u64 *)(e1 + 0x20) & 0x40ULL) != 0
        && (*(u64 *)(*(u8 **)(e0 + 0x364) + 0x38) & 0x2000000ULL) != 0
        && (arg4 & D_800E3CD8[*(s16 *)(e0 + 0x3C)]) != 0
        && func_800D8DF0(e0) != 0) {
        func_800A6C48(e0, 0x69);
        return 1;
    }
    f0 = *(u64 *)(e0 + 0x20);
    f1 = *(u64 *)(e1 + 0x20);
    if ((f0 & f1 & 0x40ULL) == 0) {
        return 0;
    }
    if ((f1 & 0x400000ULL) == 0) {
        return 0;
    }
    att = *(u8 **)(e0 + 0x364);
    fa = *(u64 *)(att + 0x38);
    if ((fa & 0x80000ULL) == 0) {
        return 0;
    }
    if ((m & 0xF00) == 0) {
        return 0;
    }
    r = func_800D7B08(m, f1);
    if (r != -1) {
        return 0;
    }
    func_800E212C(e0);
    *(s16 *)(e0 + 0x3E) = func_800A76FC(e0, arg4);
    func_800A6C48(e0, 0x65);
    return 1;
}
