/* @header
 * Fchangefx  (originally func_80016A20)
 * VRAM 0x80016A20 | ROM 0x17620 | size 0x8
 * asm: asm/nonmatchings/main/Fchangefx.s
 */
/* SDK: libmus, libmus/src/playerinc/player_commands.inc.c (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

s32 Fchangefx(s32 arg0, s32 arg1) {
    return arg1 + 1;
}
