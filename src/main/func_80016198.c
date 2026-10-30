/* @header
 * func_80016198
 * VRAM 0x80016198 | ROM 0x16D98 | size 0x20
 * asm: asm/nonmatchings/main/func_80016198.s
 */
#include "common.h"

extern u32 D_800604C8;
extern u8 *D_800604D0;

/* Decode a one-byte envelope flag into +0xD8 and reload the target when set. */
u8 *func_80016198(u8 *arg0, u8 *arg1) {
    u8 c = *arg1++;

    arg0[0xD8] = c;
    if (c != 0) {
        *(f32 *)(arg0 + 0x6C) = *(f32 *)(arg0 + 0x40);
    }
    return arg1;
}
