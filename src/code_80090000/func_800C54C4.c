/* @header
 * func_800C54C4
 * VRAM 0x800C54C4 | ROM 0x71C34 | size 0x38
 * asm: asm/nonmatchings/code_80090000/func_800C54C4.s
 */
#include "common.h"

void MusHandleSetVolume(s32, s32);

void func_800C54C4(s32 a, s32 b) {
    if (a >= 0) {
        if (b < 0) {
            b = 0;
        }
        if (b >= 0x7F) {
            b = 0x7F;
        }
        MusHandleSetVolume(a, b);
    }
}
