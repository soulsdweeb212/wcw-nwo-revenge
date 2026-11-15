/* @header
 * func_800AE124
 * VRAM 0x800AE124 | ROM 0x5A894 | size 0xC0
 * asm: asm/nonmatchings/code_80090000/func_800AE124.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_800E8FAC is the N64's label of D_800E8230[11].el, which has no PC symbol; the menus and their elements hold
 * addresses, so they are common.h's Nw2Menu and Nw2MenuEl, read by field name: p[k * 0x148 + 0xE] is element k's
 * fE. */
extern Nw2Menu D_800E8230[];
#else
extern u8 *D_800E8FAC;
#endif
extern u8 D_8007EF30[];
void func_800BA760(s32);

void func_800AE124(void) {
#ifdef TARGET_PC
    Nw2MenuEl *p = D_800E8230[11].el; /* PC: by name (see above) */
    D_8007EF30[0x1A0] = p[0].fE;
    D_8007EF30[0x1A2] = p[4].fE;
    D_8007EF30[0x1A1] = p[2].fE;
    D_8007EF30[0x1A3] = p[6].fE;
    D_8007EF30[0x1A4] = p[8].fE;
    D_8007EF30[0x1A5] = p[10].fE;
    D_8007EF30[0x1A6] = p[12].fE;
    D_8007EF30[0x1A7] = p[14].fE;
    D_8007EF30[0x1A8] = p[16].fE;
    D_8007EF30[0x1A9] = p[18].fE;
    D_8007EF30[0x1AA] = p[20].fE;
#else
    u8 *p = D_800E8FAC;
    D_8007EF30[0x1A0] = p[0xE];
    D_8007EF30[0x1A2] = p[0x52E];
    D_8007EF30[0x1A1] = p[0x29E];
    D_8007EF30[0x1A3] = p[0x7BE];
    D_8007EF30[0x1A4] = p[0xA4E];
    D_8007EF30[0x1A5] = p[0xCDE];
    D_8007EF30[0x1A6] = p[0xF6E];
    D_8007EF30[0x1A7] = p[0x11FE];
    D_8007EF30[0x1A8] = p[0x148E];
    D_8007EF30[0x1A9] = p[0x171E];
    D_8007EF30[0x1AA] = p[0x19AE];
#endif
    if (*(u16 *)(D_8007EF30 + 8) & 0x80) {
        func_800BA760(1);
    } else {
        func_800BA760(0);
    }
}
