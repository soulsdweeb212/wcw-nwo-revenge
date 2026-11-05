/* @header
 * MusSetMasterVolume  (originally func_800137F0)
 * VRAM 0x800137F0 | ROM 0x143F0 | size 0x2C
 * asm: asm/nonmatchings/main/MusSetMasterVolume.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (same code as the SDK source). */
#include "common.h"

extern s16 mus_master_volume_effects;
extern s16 mus_master_volume_songs;

/* Set the global volume pair selected by mask arg0 (bit 0 = mus_master_volume_effects, bit 1 =
 * mus_master_volume_songs) to arg1. */
void MusSetMasterVolume(s32 arg0, s16 arg1) {
    if (arg0 & 1) {
        mus_master_volume_effects = arg1;
    }
    if (arg0 & 2) {
        mus_master_volume_songs = arg1;
    }
}
