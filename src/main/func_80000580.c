/* @header
 * func_80000580
 * VRAM 0x80000580 | ROM 0x1180 | size 0x2C
 * asm: asm/nonmatchings/main/func_80000580.s
 */
#include "common.h"

void func_80000D28(void *, s32, s32);
extern s32 D_8003DE30;

/* Push a message (arg0, arg1) onto the event list at D_8003DE30. */
void func_80000580(s32 arg0, s32 arg1) {
    func_80000D28(&D_8003DE30, arg0, arg1);
}
