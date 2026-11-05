/* @header
 * MusHandlePause  (originally func_800142C4)
 * VRAM 0x800142C4 | ROM 0x14EC4 | size 0x24
 * asm: asm/nonmatchings/main/MusHandlePause.s
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

/* Queue a type-0 audio command. */
void MusHandlePause(s32 arg0) {
    Cmd c;

    c.data = arg0;
    c.cmd = 0;
    __MusIntFifoAddCommand(&c.cmd);
}
