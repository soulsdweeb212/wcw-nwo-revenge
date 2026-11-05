/* @header
 * FrandNote  (originally func_80016804)
 * VRAM 0x80016804 | ROM 0x17404 | size 0x50
 * asm: asm/nonmatchings/main/FrandNote.s
 */
/* SDK: libmus, libmus/src/playerinc/player_commands.inc.c (same code as the SDK source). */
#include "common.h"

s8 __MusIntRandom(u8);

/* Decode a signed byte into arg0+0xD9, then add the next byte to it. */
u8 *FrandNote(u8 *arg0, u8 *arg1) {
    s8 v = __MusIntRandom(*arg1++);
    *(s8 *)(arg0 + 0xD9) = v;
    v += *arg1++;
    *(s8 *)(arg0 + 0xD9) = v;
    return arg1;
}

extern f64 D_8003B3F0;
