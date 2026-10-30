/* @header
 * findBoundaryQuadrant  (originally func_800D33C4)
 * VRAM 0x800D33C4 | ROM 0xC6864 | size 0x180
 * asm: asm/nonmatchings/code_800BBA00/func_800D33C4.s
 */
#include "common.h"

typedef struct {
    u8 pad[0x6C];
    f32 f6C;
    f32 f70;
    f32 f74;
    f32 f78;
} Obj;

typedef struct {
    f32 f0, f4, f8, fC;
} Pos;

extern f32 D_800E3C50[][2];
extern f32 D_800E3C54[][2];

s8 func_800D3B24(void *, void *, f32, s32);

/* Finds which of the four diagonal boundary directions (quadrants 0..3) the
 * position `data` (or obj+0x6C when NULL) lies on, testing each direction with
 * a mode-dependent diagonal length. Returns the quadrant index or -1. */
s32 findBoundaryQuadrant(Obj *obj, Pos *data, s16 mode) {
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
        pos = *(Pos *)&obj->f6C;
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
