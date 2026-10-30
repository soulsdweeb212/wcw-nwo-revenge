/* @header
 * func_80020854
 * VRAM 0x80020854 | ROM 0x21454 | size 0x40
 * asm: asm/nonmatchings/main/func_80020854.s
 */
#include "common.h"

s32 func_8002021C(s32, s32);
s32 func_8002023C(s32);

/* Detach node arg1 and append it to the list at arg0+0x14. */
void func_80020854(s32 arg0, s32 arg1) {
    func_8002023C(arg1);
    func_8002021C(arg1, arg0 + 0x14);
}
