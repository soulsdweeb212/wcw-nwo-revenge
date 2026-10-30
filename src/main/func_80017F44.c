/* @header
 * func_80017F44
 * VRAM 0x80017F44 | ROM 0x18B44 | size 0x18
 * asm: asm/nonmatchings/main/func_80017F44.s
 */
#include "common.h"

extern s32 *D_80036F54;

s32 *func_80017F18(void);
s32 func_80018C24(s32 *arg0, s32 arg1, s32 *arg2);
s32 func_80018660(s32 arg0, s32 arg1, s32 arg2);

void func_80017F44(s32 *arg0) {
    s32 *v1 = D_80036F54;
    *arg0 = *(s32 *)((u8 *)v1 + 0x2C);
    *(s32 *)((u8 *)v1 + 0x2C) = (s32)arg0;
}
