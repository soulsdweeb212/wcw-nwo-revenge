/* @header
 * func_800A1550_ovl1  (originally func_800A1550)
 * VRAM 0x800A1550 | ROM 0x4DCC0 | size 0x40
 * asm: asm/nonmatchings/code_80090000/func_800A1550_ovl1.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the menus D_800E8230 hold addresses, so they are common.h's Nw2Menu, and the N64's label D_800E8236 inside
 * them has no PC symbol: it is D_800E8230[0].f6. The N64's `u8 *D_800E8230` reads D_800E8230[0].items, whose byte
 * +4 is f4. */
extern Nw2Menu D_800E8230[];

void func_800A1550_ovl1(void) {
    s32 i;
    D_800E8230[0].f6 = D_800E8230[0].items->f4;
    for (i = 1; i < 0x18; i++) {
        D_800E8230[i].f6 = 0;
    }
}
#else
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
#endif
