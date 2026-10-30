/* @header
 * func_80016700
 * VRAM 0x80016700 | ROM 0x17300 | size 0x14
 * asm: asm/nonmatchings/main/func_80016700.s
 */
#include "common.h"

u8 *func_80016700(u8 *arg0, u8 *arg1) {
    u8 v = *arg1;
    arg0[0xF2] = 0;
    arg0[0xF3] = v;
    return arg1 + 1;
}
