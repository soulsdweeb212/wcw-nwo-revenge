/* @header
 * updateRingCornerFlags  (originally func_80011334)
 * VRAM 0x80011334 | ROM 0x11F34 | size 0x108
 * asm: asm/nonmatchings/main/updateRingCornerFlags.s
 */
#include "common.h"

extern s32 D_8005A3B0[4];
s16 func_80001CA0(f32 *, f32 *);

/* For each of the four edges of the +/-280 ring-boundary square, test the edge
 * (edgeA -> edgeB) and record 5 in D_8005A3B0 when it is selected, else 0. */
void updateRingCornerFlags(void) {
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
