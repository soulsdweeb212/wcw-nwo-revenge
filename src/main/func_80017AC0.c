#include "common.h"

extern s32 *D_80036F54;

s32 *func_80017F18(void);
s32 func_80018C24(s32 *arg0, s32 arg1, s32 *arg2);
s32 func_80018660(s32 arg0, s32 arg1, s32 arg2);

/* Emits the mixer header (0x020007C0 / 0x2E0) followed by each mixer child's
 * commands for arg0 into arg1, returning the advanced cursor. */
s32 func_800180A0(s32 arg0, s32 arg1) {
    s32 *s2;
    s32 *p;
    s32 *v1;
    s32 *a2;
    s32 i;
    s32 count;

    s2 = *(s32 **)((u8 *)D_80036F54 + 0x34);
    a2 = (s32 *)arg1;
    v1 = a2;
    p = (s32 *)s2[7];
    v1[0] = 0x020007C0;
    v1[1] = 0x2E0;
    count = s2[5];
    a2 = (s32 *)((s32)a2 + 8);
    if (count > 0) {
        i = 0;
        do {
            a2 = (s32 *)func_80018660(*p, arg0, (s32)a2);
            p++;
            count = s2[5];
            i++;
        } while (i < count);
    }
    return (s32)a2;
}

/* Sends command 15 (with payload arg1) to the node referenced by arg0[2]. */
void func_80017AC0(s32 *arg0) {
    s32 *v0;

    if (arg0[2] != 0) {
        v0 = func_80017F18();
        if (v0 != 0) {
            v0[1] = D_80036F54[7] + *(s32 *)((u8 *)arg0[2] + 0x88);
            *(s16 *)((u8 *)v0 + 8) = 0xF;
            v0[0] = 0;
            func_80018C24((s32 *)arg0[2], 3, v0);
        }
    }
}

/* Sends command 14 (with payload arg1 and the object's +0x1A word) to the node
 * referenced by arg0[2]. */
void func_80017A30(s32 *arg0, s32 arg1) {
    s32 *v0;

    if (arg0[2] != 0) {
        v0 = func_80017F18();
        if (v0 != 0) {
            v0[1] = D_80036F54[7] + *(s32 *)((u8 *)arg0[2] + 0x88);
            *(s16 *)((u8 *)v0 + 8) = 0xE;
            v0[3] = arg1;
            v0[0] = 0;
            *(u16 *)((u8 *)v0 + 0xA) = *(u16 *)((u8 *)arg0 + 0x1A);
            func_80018C24((s32 *)arg0[2], 3, v0);
        }
    }
}
