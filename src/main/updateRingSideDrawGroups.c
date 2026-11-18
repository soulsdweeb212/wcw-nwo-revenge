/* @header
 * updateRingSideDrawGroups  (originally func_80011334)
 * VRAM 0x80011334 | ROM 0x11F34 | size 0x108
 * asm: asm/nonmatchings/main/updateRingSideDrawGroups.s
 */
#include "common.h"

extern s32 D_8005A3B0[4];
s16 func_80001CA0(f32 *, f32 *);

/* For each of the four sides of the +/-280 ring platform, test whether the side faces the
 * camera (edgeA -> edgeB, func_80001CA0) and write its draw group to D_8005A3B0: 5 when it
 * does, else 0. */
void updateRingSideDrawGroups(void) {
    f32 edgeA[3], edgeB[3];
    u32 edge;
    edgeB[1] = 0; edgeA[1] = 0;
    for (edge = 0; edge < 4; edge++) {
        switch (edge) {
        case 0: edgeB[0] = 280; edgeB[2] = -280; edgeA[0] = 280; edgeA[2] = 280; break;
        case 1: edgeB[0] = 280; edgeB[2] = 280; edgeA[0] = -280; edgeA[2] = 280; break;
        case 2: edgeB[0] = -280; edgeB[2] = -280; edgeA[0] = 280; edgeA[2] = -280; break;
        default: edgeB[0] = -280; edgeB[2] = 280; edgeA[0] = -280; edgeA[2] = -280; break;
        }
        if (func_80001CA0(edgeA, edgeB))
            D_8005A3B0[edge] = 5;
        else
            D_8005A3B0[edge] = 0;
    }
}
