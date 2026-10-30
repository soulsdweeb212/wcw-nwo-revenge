/* @header
 * func_80016714
 * VRAM 0x80016714 | ROM 0x17314 | size 0x1C
 * asm: asm/nonmatchings/main/func_80016714.s
 */
#include "common.h"

u8 *func_80016714(u8 *arg0, u8 *arg1) {
    u8 v = *arg1;
    arg0[0xDE] = 0xFF;
    arg0[0xDD] = v >> 1;
    return arg1 + 1;
}
