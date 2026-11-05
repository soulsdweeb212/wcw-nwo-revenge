/* @header
 * guMtxIdentF  (originally func_8001B1D0)
 * VRAM 0x8001B1D0 | ROM 0x1BDD0 | size 0x50
 * asm: asm/nonmatchings/main/guMtxIdentF.s
 */
/* SDK: libultra 2.0I, ultralib src/gu/mtxutil.c (same code as the SDK source). */
#include "common.h"

/* Write a 4x4 identity matrix to arg (row-major; diagonal 1, elsewhere 0). */
void guMtxIdentF(void *arg) {
    f32 *p = arg;
    s32 i, j;

    for (i = 0; i < 4; i++, p += 4) {
        for (j = 0; j < 4; j++) {
            if (i == j) {
                ((f32 *)arg)[i * 5] = 1.0f;
            } else {
                p[j] = 0.0f;
            }
        }
    }
}
