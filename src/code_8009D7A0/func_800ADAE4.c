/* @header
 * func_800ADAE4
 * VRAM 0x800ADAE4 | ROM 0xA0F84 | size 0x60
 * asm: asm/nonmatchings/code_8009D7A0/func_800ADAE4.s
 */
#include "common.h"

/* Quadrant of w's pelvis (jointA[1]) from the signs of its x and z: 0 when x > 0 and z > 0, 1 when x > 0 and
 * z <= 0, 2 when x <= 0 and z <= 0, 3 when x <= 0 and z > 0. */
s32 func_800ADAE4(Wrestler *w) {
    s32 q;

    if (w->jointA[1].x > 0.0f) {
        q = 1;
        if (w->jointA[1].z > 0.0f) {
            return 0;
        }
        return q;
    }
    q = 2;
    if (w->jointA[1].z > 0.0f) {
        q = 3;
    }
    return q;
}
