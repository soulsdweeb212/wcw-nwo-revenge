/* @header
 * func_800B511C
 * VRAM 0x800B511C | ROM 0x6188C | size 0x90
 * asm: asm/nonmatchings/code_80090000/func_800B511C.s
 */
#include "common.h"


#ifdef TARGET_PC
/* PC: D_800E9AA4 is the N64's label of D_800E8230[20].el, which has no PC symbol; the menus and their elements hold
 * addresses, so they are common.h's Nw2Menu and Nw2MenuEl, read by field name (+0x22 is f22). */
extern Nw2Menu D_800E8230[];
#else
extern u8 *D_800E9AA4;
#endif
extern u8 D_8007EF30[];
#define W(o) (*(s16 *)(D_8007EF30 + (o)))

void func_800B511C(s32 a) {
#ifdef TARGET_PC
    Nw2MenuEl *p = D_800E8230[20].el; /* PC: by name (see above) */
#else
    u8 *p = D_800E9AA4;
#endif
    s32 x;
    s32 v;
    if (a < 5) {
        if (a < 2) {
            if (a != 1) {
                goto zero;
            }
            x = 0x90;
        } else {
            x = 0x150;
        }
        W(0x24) = x;
        W(0x26) = 0xC0;
    } else {
zero:
        W(0x24) = 0;
        W(0x26) = 0;
    }
    switch (a) {
    case 3:
        v = 0x1002;
        break;
    case 4:
        v = 0x1001;
        break;
    default:
        v = 0x1000;
        break;
    }
    W(0x28) = v;
#ifdef TARGET_PC
    p->f22 = 0xFF; /* PC: as above */
#else
    *(s16 *)(p + 0x22) = 0xFF;
#endif
}
