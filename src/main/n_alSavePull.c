/* @header
 * n_alSavePull  (originally func_8001A360)
 * VRAM 0x8001A360 | ROM 0x1AF60 | size 0x4C
 * asm: asm/nonmatchings/main/n_alSavePull.s
 */
/* SDK: n_audio, libnaudio/src/n_save.c (same code as the SDK source). */
#include "common.h"

extern s32 D_80036F54;

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

/* Emit n_alMainBusPull's commands, then append the 0x0D000000 and 0x062E0000 commands. */
s32 *n_alSavePull(s32 arg0, s32 *arg1) {
    Nw2Obj36F54 *obj;
    s32 *p;
    s32 *q;
    p = n_alMainBusPull(arg0, arg1);
    q = p;
    p = p + 2;
    q[0] = 0x0D000000;
    obj = (Nw2Obj36F54 *)D_80036F54;
    p[0] = 0x062E0000;
    p[1] = obj->f48;
    return p + 2;
}
