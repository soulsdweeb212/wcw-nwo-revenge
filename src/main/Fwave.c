/* @header
 * Fwave  (originally func_80016168)
 * VRAM 0x80016168 | ROM 0x16D68 | size 0x30
 * asm: asm/nonmatchings/main/Fwave.s
 */
/* SDK: libmus, libmus/src/playerinc/player_commands.inc.c (same code as the SDK source). */
#include "common.h"

extern u32 max_channels;
extern u8 *mus_channels;

/* Parses a 16-bit envelope value (with a 0x80 high-bit escape) into +0xCE. */
void *Fwave(void *arg0, u8 *arg1) {
    s32 v = *arg1++;

    if (v & 0x80) {
        v = *arg1++ | ((v & 0x7F) << 8);
    }
    *(u16 *)((u8 *)arg0 + 0xCE) = v;
    return arg1;
}
