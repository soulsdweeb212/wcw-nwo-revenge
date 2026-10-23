#include "common.h"

/* identical to func_80017F44 (matched), with its names changed by decomp.wtf */
extern s32 *D_80037510;

s32 *func_80017F18(void);
s32 func_80018C24(s32 *arg0, s32 arg1, s32 *arg2);
s32 func_80018660(s32 arg0, s32 arg1, s32 arg2);

void func_800207E8(s32 *arg0) {
    s32 *v1 = D_80037510;
    *arg0 = *(s32 *)((u8 *)v1 + 0x2C);
    *(s32 *)((u8 *)v1 + 0x2C) = (s32)arg0;
}

s32 func_800180A0(s32 arg0, s32 arg1) {
    s32 *s2;
    s32 *p;
    s32 i;
    s32 ret;
    s32 count;

    s2 = *(s32 **)((u8 *)D_80037510 + 0x34);
    *(s32 *)arg1 = 0x020007C0;
    *(s32 *)(arg1 + 4) = 0x2E0;
    count = s2[5];
    ret = arg1 + 8;
    if (count > 0) {
        p = (s32 *)s2[7];
        i = 0;
        do {
            ret = func_80018660(*p, arg0, ret);
            p++;
            count = s2[5];
            i++;
        } while (i < count);
    }
    return ret;
}

void func_80017AC0(s32 *arg0) {
    s32 *v0;

    if (arg0[2] != 0) {
        v0 = func_80017F18();
        if (v0 != 0) {
            *(s16 *)((u8 *)v0 + 8) = 0xF;
            v0[0] = 0;
            v0[1] = D_80037510[7] + *(s32 *)((u8 *)arg0[2] + 0x88);
            func_80018C24((s32 *)arg0[2], 3, v0);
        }
    }
}

void func_80017A30(s32 *arg0, s32 arg1) {
    s32 *v0;

    if (arg0[2] != 0) {
        v0 = func_80017F18();
        if (v0 != 0) {
            *(s16 *)((u8 *)v0 + 8) = 0xE;
            v0[3] = arg1;
            v0[0] = 0;
            v0[1] = D_80037510[7] + *(s32 *)((u8 *)arg0[2] + 0x88);
            *(u16 *)((u8 *)v0 + 0xA) = *(u16 *)((u8 *)arg0 + 0x1A);
            func_80018C24((s32 *)arg0[2], 3, v0);
        }
    }
}
