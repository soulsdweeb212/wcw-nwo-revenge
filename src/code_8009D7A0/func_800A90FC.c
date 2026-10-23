#include "common.h"

extern s8 D_800FA063[];
extern s16 D_800E3270[];
extern s16 D_800E3262[];
extern u8 D_8007E228[];
extern u8 D_8007EF30[];
s32 func_800D35B0(s32, s32);
void func_800D4AD0(void *);
s32 func_800D4CC4(void *);
void func_800D427C(void *, s16, s32);

/* Entity arg0's type byte. */
s8 func_800A90FC(s16 arg0) {
    return D_800FA063[arg0 * 0x3B0];
}

/* Look up the entity's substate (+8) in D_800E3270; on a match optionally return the
 * wrapped heading. */
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

/* When the entity's substate is listed, lock its action; otherwise advance it. */
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

/* Whether the entity may act, from the global status and its flags. */
s32 func_800A9348(void *arg0) {
    s32 a;
    s32 b;

    if (!(*(u16 *)(D_8007E228 + 0x58) & 0x400)) {
        return 1;
    }
    if (!(*(u16 *)(D_8007EF30 + 0x170) & 0x400)) {
        return 1;
    }
    b = *(s32 *)((u8 *)arg0 + 0x24);
    a = *(s32 *)((u8 *)arg0 + 0x20);
    if (!(a & 0) && !(b & 0x200)) {
        return 1;
    }
    if ((a & 0) || (b & 0x100)) {
        return 0;
    }
    return 1;
}
