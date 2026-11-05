/* @header
 * Fvelocity  (originally func_80016700)
 * VRAM 0x80016700 | ROM 0x17300 | size 0x14
 * asm: asm/nonmatchings/main/Fvelocity.s
 */
/* SDK: libmus, libmus/src/playerinc/player_commands.inc.c (same code as the SDK source). */
#include "common.h"

u8 *Fvelocity(u8 *arg0, u8 *arg1) {
    u8 v = *arg1;
    arg0[0xF2] = 0;
    arg0[0xF3] = v;
    return arg1 + 1;
}
