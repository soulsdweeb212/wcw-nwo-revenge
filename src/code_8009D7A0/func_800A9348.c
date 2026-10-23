#include "common.h"

extern s16 D_800E3270[];
extern s16 D_800E3262[];
extern u8 D_8007E228[];
extern u8 D_8007EF30[];
extern u8 D_80064AD8[];

s32 func_800D35B0(s32, s32);
void func_800D4AD0(void *);
s32 func_800D4CC4(void *);
void func_800D427C(void *, s16, s32);

/* Returns 1 when the entity's state (+8) is one of the D_800E3270 states,
 * optionally returning the adjusted heading in *arg1. */
s32 func_800A9208(void *arg0, s32 *arg1) {
    s16 v;
    s16 i;

    for (i = 0; ; i++) {
        v = D_800E3270[i];
        if (v == 0) {
            if (arg1 != NULL) {
                *arg1 = *(s32 *)((u8 *)arg0 + 0x58);
            }
            return 0;
        }
        if (*(s16 *)((u8 *)arg0 + 8) == v) {
            break;
        }
    }
    if (arg1 != NULL) {
        *arg1 = func_800D35B0(*(s32 *)((u8 *)arg0 + 0x58), *(s32 *)((u8 *)arg0 + 0x368));
    }
    return 1;
}

/* Continues the action when the entity is in one of the D_800E3270 states,
 * otherwise tears it down and plays the reaction animation from D_800E3262. */
void func_800A9290(void *arg0) {
    s16 v;
    s16 i;
    s32 r;

    for (i = 0; ; i++) {
        v = D_800E3270[i];
        if (v == 0) {
            r = 0;
            break;
        }
        if (*(s16 *)((u8 *)arg0 + 8) == v) {
            r = 1;
            break;
        }
    }
    if (r != 0) {
        *(u64 *)((u8 *)arg0 + 0x20) |= 0x1000000000000000ULL;
        return;
    }
    func_800D4AD0(arg0);
    if ((func_800D4CC4(arg0) & 0xFF) != 0) {
        func_800D427C(arg0, D_800E3262[*(u8 *)((u8 *)arg0 + 0x36F)], 1);
    }
}

/* Returns 0 only when the global 0x400 gates and the entity's 0x200 flag are
 * all set and its 0x100 flag is clear. */
s32 func_800A9348(void *arg0) {
    u64 f;

    if (!(*(u16 *)(D_8007E228 + 0x58) & 0x400)) {
        return 1;
    }
    if (!(*(u16 *)(D_8007EF30 + 0x170) & 0x400)) {
        return 1;
    }
    f = *(u64 *)((u8 *)arg0 + 0x20);
    if (!(f & 0x200)) {
        return 1;
    }
    if (f & 0x100) {
        return 0;
    }
    return 1;
}

/* Returns the entity's animation id derived from its +0x386 base, the +0x38C
 * index and the packed 2-bit table entry for the attachment's group. */
s16 func_800A8D14(void *arg0, void *arg1) {
    s32 i = *(s16 *)((u8 *)arg0 + 0x38C);
    u8 *base = &D_80064AD8[8 + (*(s8 *)(*(u8 **)((u8 *)arg1 + 0x364) + 0x20)) * 400];
    u8 byte = base[i / 4];
    u8 n = (byte >> ((i & 3) * 2)) & 3;

    return (s16)(*(u16 *)((u8 *)arg0 + 0x386) + n + 1);
}
