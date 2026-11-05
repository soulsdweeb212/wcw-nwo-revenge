/* @header
 * Fport  (originally func_80016198)
 * VRAM 0x80016198 | ROM 0x16D98 | size 0x20
 * asm: asm/nonmatchings/main/Fport.s
 */
/* SDK: libmus, libmus/src/playerinc/player_commands.inc.c (same code as the SDK source). */
#include "common.h"

extern u32 max_channels;
extern u8 *mus_channels;

/* Decode a one-byte envelope flag into +0xD8 and reload the target when set. */
u8 *Fport(u8 *arg0, u8 *arg1) {
    u8 c = *arg1++;

    arg0[0xD8] = c;
    if (c != 0) {
        *(f32 *)(arg0 + 0x6C) = *(f32 *)(arg0 + 0x40);
    }
    return arg1;
}
