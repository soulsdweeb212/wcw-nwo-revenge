/* @header
 * n_alSynAllocFX  (originally func_8001A3B0)
 * VRAM 0x8001A3B0 | ROM 0x1AFB0 | size 0x50
 * asm: asm/nonmatchings/main/n_alSynAllocFX.s
 */
/* SDK: n_audio, libnaudio/src/n_synallocfx.c (same code as the SDK source). */
#include "common.h"

extern s32 n_syn;

typedef struct {
    u8 pad00[0x30];
    u8 *f30;
    u8 *f34;
    u8 pad38[0x0C];
    u8 *f44;
    s32 f48;
} Nw2Obj36F54;

typedef struct {
    u8 pad0[4];
    s32 *(*fn)(s32, s32 *);
} Nw2Tbl36F54;

extern void n_alFxNew(void *);
extern s32 *n_alMainBusPull(s32, s32 *);

/* Look up the record at n_syn->f34 + arg0*4 + 0x24 and return its field. */
s32 n_alSynAllocFX(s32 arg0) {
    s32 t = (s32)(arg0 << 16) >> 14;
    n_alFxNew(((Nw2Obj36F54 *)n_syn)->f34 + (t + 0x24));
    t = t + (s32)((Nw2Obj36F54 *)n_syn)->f34;
    return *(s32 *)(t + 0x24);
}
