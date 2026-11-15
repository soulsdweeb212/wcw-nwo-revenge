/* @header
 * func_800ADEF8
 * VRAM 0x800ADEF8 | ROM 0x5A668 | size 0x8C
 * asm: asm/nonmatchings/code_80090000/func_800ADEF8.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_800E8D3C is D_800E8230[9].el, and p's offsets are the fE (+0xE) of its elements 0, 4, 2, 6, 8, 10 and 12
 * (0x148 bytes each on the N64). The menus and their elements hold addresses, so they are common.h's Nw2Menu and
 * Nw2MenuEl on PC, read by field name: the label has no PC symbol. */
extern Nw2Menu D_800E8230[];
#else
extern u8 *D_800E8D3C;
#endif
extern u8 D_8007E8C0[], D_8007EF30[];
void func_8000333C(s32);
void func_800B9F18(void);

void func_800ADEF8(void) {
#ifdef TARGET_PC
    Nw2MenuEl *p = D_800E8230[9].el; /* PC: by name (see above) */
    D_8007E8C0[0x66D] = p[0].fE;
    D_8007E8C0[0x66E] = p[4].fE;
    D_8007E8C0[0x66F] = p[2].fE;
    D_8007EF30[0] = p[6].fE;
    D_8007EF30[3] = p[8].fE;
    D_8007EF30[1] = p[10].fE;
    D_8007EF30[2] = p[12].fE;
#else
    u8 *p = D_800E8D3C;
    D_8007E8C0[0x66D] = p[0xE];
    D_8007E8C0[0x66E] = p[0x52E];
    D_8007E8C0[0x66F] = p[0x29E];
    D_8007EF30[0] = p[0x7BE];
    D_8007EF30[3] = p[0xA4E];
    D_8007EF30[1] = p[0xCDE];
    D_8007EF30[2] = p[0xF6E];
#endif
    if (D_8007EF30[2] == 0) {
        func_8000333C(1);
    } else {
        func_8000333C(0);
    }
    func_800B9F18();
}
