/* @header
 * MusHandleUnPause  (originally func_800142E8)
 * VRAM 0x800142E8 | ROM 0x14EE8 | size 0x28
 * asm: asm/nonmatchings/main/MusHandleUnPause.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (same code as the SDK source). */
#include "common.h"

extern void __MusIntFifoAddCommand(u8 *);
extern s32 D_800604FC;
extern u32 D_800604C8;
extern u8 *D_800604D0;

typedef struct {
    u8 cmd;
    s32 data;
} Cmd;

/* Enqueues a type-1 audio message with arg0 as the sound id. */
void MusHandleUnPause(s32 arg0) {
    Cmd c;

    c.data = arg0;
    c.cmd = 1;
    __MusIntFifoAddCommand(&c.cmd);
}
