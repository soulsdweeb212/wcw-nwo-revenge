/* @header
 * Flength  (originally func_800164FC)
 * VRAM 0x800164FC | ROM 0x170FC | size 0x40
 * asm: asm/nonmatchings/main/Flength.s
 */
/* SDK: libmus, libmus/src/playerinc/player_commands.inc.c (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

/* Decode a 7-bit or 14-bit value into arg0+0xCC (7-bit: one byte; 14-bit: two). */
u8 *Flength(void *arg0, u8 *arg1) {
    u8 v = *arg1++;
    if (v < 0x80) {
        *(u16 *)((u8 *)arg0 + 0xCC) = v;
    } else {
        u32 t = (v & 0x7F) << 8;
        *(u16 *)((u8 *)arg0 + 0xCC) = t;
        t += *arg1++;
        *(u16 *)((u8 *)arg0 + 0xCC) = t;
    }
    return arg1;
}
