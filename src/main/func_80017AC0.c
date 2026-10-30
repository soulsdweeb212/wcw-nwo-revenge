/* @header
 * func_80017AC0
 * VRAM 0x80017AC0 | ROM 0x186C0 | size 0x74
 * asm: asm/nonmatchings/main/func_80017AC0.s
 */
#include "common.h"

extern s32 *D_80036F54;

s32 *func_80017F18(void);
s32 func_80018C24(s32 *arg0, s32 arg1, s32 *arg2);
s32 func_80018660(s32 arg0, s32 arg1, s32 arg2);

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
