#include "common.h"

extern s32 *D_80036F54;

s32 *func_80017F18(void);
s32 func_80018C24(s32 *arg0, s32 arg1, s32 *arg2);
s32 func_80018660(s32 arg0, s32 arg1, s32 arg2);

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
