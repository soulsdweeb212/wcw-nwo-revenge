/* @header
 * __MusIntFifoOpen  (originally func_8001439C)
 * VRAM 0x8001439C | ROM 0x14F9C | size 0x7C
 * asm: asm/nonmatchings/main/__MusIntFifoOpen.s
 */
/* SDK: libmus, libmus/src/playerinc/player_fifo.inc.c (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

s32 alHeapDBAlloc(s32, s32, void *, s32, s32);
extern u8 D_800604B8[];
extern s32 fifo_start;
extern s32 fifo_current;
extern s32 fifo_limit;
extern s32 fifo_addr;

/* Allocates the audio command queue (arg0 entries clamped to 0x40..0x400,
 * 8 bytes each) and resets its read/write indices. */
void __MusIntFifoOpen(s32 arg0) {
    s32 var_s0;

    var_s0 = arg0;
    if (var_s0 < 0x40) {
        var_s0 = 0x40;
    } else if (var_s0 >= 0x401) {
        var_s0 = 0x400;
    }
    fifo_addr = alHeapDBAlloc(0, 0, D_800604B8, 1, var_s0 * 8);
    fifo_limit = var_s0;
    fifo_current = 0;
    fifo_start = 0;
}
