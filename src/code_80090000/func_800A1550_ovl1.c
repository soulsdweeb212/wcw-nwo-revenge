/* @header
 * func_800A1550_ovl1  (originally func_800A1550)
 * VRAM 0x800A1550 | ROM 0x4DCC0 | size 0x40
 * asm: asm/nonmatchings/code_80090000/func_800A1550_ovl1.s
 */
#include "common.h"

typedef struct { s16 x; u8 p[0x136]; } S;
extern u8 *D_800E8230;
extern S D_800E8236[];

void func_800A1550_ovl1(void) {
    s32 i;
    D_800E8236[0].x = D_800E8230[4];
    for (i = 1; i < 0x18; i++) {
        D_800E8236[i].x = 0;
    }
}
