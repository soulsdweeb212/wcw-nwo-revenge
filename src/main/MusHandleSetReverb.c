/* @header
 * MusHandleSetReverb  (originally func_80013F7C)
 * VRAM 0x80013F7C | ROM 0x14B7C | size 0x88
 * asm: asm/nonmatchings/main/MusHandleSetReverb.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (same code as the SDK source). */
#include "common.h"

extern s32 mus_init_bank;
extern s32 D_800604F4;
extern u32 max_channels;
extern u8 *mus_channels;
s32 MusStartSong(s32);

/* Sets the pan (clamped 0..0x7F) of every voice whose key matches arg0. Returns
 * the number updated. */
s32 MusHandleSetReverb(s32 arg0, s32 arg1) {
    u32 i;
    s32 n;
    u8 *p;

    if (arg0 == 0) {
        return 0;
    }
    if (arg1 < 0) {
        arg1 = 0;
    } else if (arg1 >= 0x80) {
        arg1 = 0x7F;
    }
    n = 0;
    p = mus_channels;
    for (i = 0; i < max_channels; i++) {
        if (*(s32 *)(p + 0x60) == arg0) {
            n++;
            p[0xEB] = arg1;
            p[0xEC] = 0xFF;
        }
        p += 0x158;
    }
    return n;
}
