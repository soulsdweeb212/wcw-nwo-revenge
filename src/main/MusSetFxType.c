/* @header
 * MusSetFxType  (originally func_80014310)
 * VRAM 0x80014310 | ROM 0x14F10 | size 0x30
 * asm: asm/nonmatchings/main/MusSetFxType.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (same code as the SDK source). */
#include "common.h"

extern void __MusIntFifoAddCommand(u8 *);
extern s32 mus_last_fxtype;
extern u32 max_channels;
extern u8 *mus_channels;

typedef struct {
    u8 cmd;
    s32 data;
} Cmd;

/* Queue a type-2 audio command and latch the value. */
void MusSetFxType(s32 arg0) {
    Cmd c;

    c.data = arg0;
    mus_last_fxtype = arg0;
    c.cmd = 2;
    __MusIntFifoAddCommand(&c.cmd);
}
