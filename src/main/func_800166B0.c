/* @header
 * func_800166B0
 * VRAM 0x800166B0 | ROM 0x172B0 | size 0x28
 * asm: asm/nonmatchings/main/func_800166B0.s
 */
#include "common.h"

/* Decode a three-byte loop envelope into +0xF8/+0xEE/+0xEF. */
u8 *func_800166B0(u8 *arg0, u8 *arg1) {
    arg0[0xF8] = *arg1++;
    arg0[0xEE] = *arg1++;
    arg0[0xEF] = *arg1;
    return arg1 + 1;
}
