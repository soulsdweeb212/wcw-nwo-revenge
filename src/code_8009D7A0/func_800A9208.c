#include "common.h"

extern s16 D_800E3270[];
extern s16 D_800E3262[];
extern u8 D_80064AD8[];

s32 func_800D35B0(s32, s32);
void func_800D4AD0(void *);
u8 func_800D4CC4(void *);
void func_800D427C(void *, s16, s32);

/* Returns 1 when the entity's state (+8) is one of the D_800E3270 states,
 * optionally returning the adjusted heading in *arg1. */
s32 func_800A9208(void *arg0, s32 *arg1) {
    s16 v;
    s16 i = 0;

    do {
        v = D_800E3270[i];
        if (v == 0) {
            if (arg1 != NULL) {
                *arg1 = *(s32 *)((u8 *)arg0 + 0x58);
            }
            return 0;
        }
        if (*(s16 *)((u8 *)arg0 + 8) == v) {
            if (arg1 != NULL) {
                *arg1 = func_800D35B0(*(s32 *)((u8 *)arg0 + 0x58), *(s32 *)((u8 *)arg0 + 0x368));
            }
            return 1;
        }
        i++;
    } while (1);
}

/* Continues the action when the entity is in one of the D_800E3270 states,
 * otherwise tears it down and plays the reaction animation from D_800E3262. */
void func_800A9290(void *arg0) {
    s16 v;
    s32 i;
    s32 r;

    i = 0;
loop:
    v = *(s16 *)((u8 *)D_800E3270 + ((i << 16) >> 15));
    r = 0;
    if (v != 0) {
        i += 1;
        if (*(s16 *)((u8 *)arg0 + 8) == v) {
            r = 1;
        } else {
            goto loop;
        }
    }
    if (r != 0) {
        *(u64 *)((u8 *)arg0 + 0x20) |= 0x10000000ULL;
        return;
    }
    func_800D4AD0(arg0);
    if (func_800D4CC4(arg0)) {
        func_800D427C(arg0, D_800E3262[*(u8 *)((u8 *)arg0 + 0x36F)], 1);
    }
}

/* Returns the entity's animation id derived from its +0x386 base, the +0x38C
 * index and the packed 2-bit table entry for the attachment's group. */
s16 func_800A8D14(void *arg0, void *arg1) {
    u8 *base = &D_80064AD8[8];
    s16 i = *(s16 *)((u8 *)arg0 + 0x38C);
    s8 *rec = *(s8 **)((u8 *)arg1 + 0x364);
    u8 b = base[rec[0x20] * 400 + i / 4];

    return *(u16 *)((u8 *)arg0 + 0x386) + ((b >> ((i & 3) * 2)) & 3) + 1;
}
