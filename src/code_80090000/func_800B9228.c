/* @header
 * func_800B9228
 * VRAM 0x800B9228 | ROM 0x65998 | size 0x40
 * asm: asm/nonmatchings/code_80090000/func_800B9228.s
 */
#include "common.h"

s32 func_800B9228(u8 *p, s32 n) {
    u8 pad[1];
    s32 i;
    s32 h = 0;
    for (i = 0; i < n; i++) {
        h += (*p++ << (i & 0xF)) + i;
    }
    return h;
}
