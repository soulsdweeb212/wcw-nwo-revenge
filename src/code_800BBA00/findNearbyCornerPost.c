/* @header
 * findNearbyCornerPost  (originally func_800D33C4)
 * VRAM 0x800D33C4 | ROM 0xC6864 | size 0x180
 * asm: asm/nonmatchings/code_800BBA00/findNearbyCornerPost.s
 */
#include "common.h"

typedef struct {
    f32 f0, f4, f8, fC;
} Pos;

extern f32 D_800E3C50[][2];
extern f32 D_800E3C54[][2];

#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D3B24 */
s8 func_800D3B24(void *, void *, f32, s32);
#endif

/* Finds which of the four corner posts (D_800E3C50/54, at +/-230) lies within a radius of the
 * position `data` (or w->jointA[1], the pelvis, when NULL); the radius depends on the mode.
 * Returns the post's index (0..3) or -1. */
s32 findNearbyCornerPost(Wrestler *w, Pos *data, s16 mode) {
    f32 scale;
    Pos pos;
    f32 vec[3];
    s16 i;

    switch (mode) {
    case 0:
        scale = 43.84062194824219f;
        break;
    case 1:
        scale = 56.56854248046875f;
        break;
    case 2:
        scale = 73.53910827636719f;
        break;
    case 3:
        scale = 98.99494934082031f;
        break;
    }

    if (data == NULL) {
        pos = *(Pos *)&w->jointA[1];
    } else {
        pos = *data;
    }

    for (i = 0; i < 4; i++) {
        vec[0] = D_800E3C50[i][0];
        vec[2] = D_800E3C54[i][0];
        if (func_800D3B24(vec, &pos, scale, 0)) {
            return i;
        }
    }
    return -1;
}
