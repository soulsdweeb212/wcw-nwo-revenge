/* @header
 * translateEntityXZ  (originally func_800D6360)
 * VRAM 0x800D6360 | ROM 0xC9800 | size 0x90
 * asm: asm/nonmatchings/code_800BBA00/translateEntityXZ.s
 */
#include "common.h"

/* Translates wrestler w by the XZ delta d (d[0] = x, d[2] = z; d[1] is not read): moves the root x/z and the x/z
 * of jointA[1..19] and jointB[1..19]. */
void translateEntityXZ(Wrestler *w, f32 *d) {
    s16 i;

    w->x += d[0];
    w->z += d[2];
    for (i = 1; i < 20; i++) {
        w->jointA[i].x += d[0];
        w->jointA[i].z += d[2];
        w->jointB[i].x += d[0];
        w->jointB[i].z += d[2];
    }
}
