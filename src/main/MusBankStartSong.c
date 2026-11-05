/* @header
 * MusBankStartSong  (originally func_80014020)
 * VRAM 0x80014020 | ROM 0x14C20 | size 0x44
 * asm: asm/nonmatchings/main/MusBankStartSong.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

extern s32 mus_init_bank;
extern s32 D_800604F4;
extern u32 max_channels;
extern u8 *mus_channels;
s32 MusStartSong(s32);

/* Select arg0 as the current voice owner when it is stopping, run the loader, then
 * restore the default owner. */
s32 MusBankStartSong(s32 arg0, s32 arg1) {
    s32 r;

    if (arg0 != 0 && *(s32 *)((u8 *)arg0 + 0x10) < 0) {
        mus_init_bank = arg0;
    }
    r = MusStartSong(arg1);
    mus_init_bank = D_800604F4;
    return r;
}
