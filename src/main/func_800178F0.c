/* @header
 * func_800178F0
 * VRAM 0x800178F0 | ROM 0x184F0 | size 0x84
 * asm: asm/nonmatchings/main/func_800178F0.s
 */
#include "common.h"

extern s32 *D_80036F54;
s32 *func_80017F18(void);
s32 func_80018C24(s32 *, s32, s32 *);
s32 func_80018044(s32, s32);

/* Sends command 7 with the float payload arg1 to the node referenced by arg0[2]. */
void func_800178F0(s32 *arg0, f32 arg1) {
    s32 *p;
    if (arg0[2] != 0) {
        p = func_80017F18();
        if (p != 0) {
            s32 g = D_80036F54[7];
            s32 off = *(s32 *)((u8 *)arg0[2] + 0x88);
            *(s16 *)((u8 *)p + 8) = 7;
            *(f32 *)((u8 *)p + 0xC) = arg1;
            p[0] = 0;
            p[1] = g + off;
            func_80018C24((s32 *)arg0[2], 3, p);
        }
    }
}
