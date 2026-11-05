/* @header
 * Fpan  (originally func_80016714)
 * VRAM 0x80016714 | ROM 0x17314 | size 0x1C
 * asm: asm/nonmatchings/main/Fpan.s
 */
/* SDK: libmus, libmus/src/playerinc/player_commands.inc.c (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

u8 *Fpan(u8 *arg0, u8 *arg1) {
    u8 v = *arg1;
    arg0[0xDE] = 0xFF;
    arg0[0xDD] = v >> 1;
    return arg1 + 1;
}
