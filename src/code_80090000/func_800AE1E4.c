/* @header
 * func_800AE1E4
 * VRAM 0x800AE1E4 | ROM 0x5A954 | size 0xE4
 * asm: asm/nonmatchings/code_80090000/func_800AE1E4.s
 */
#include "common.h"

extern u8 D_8007EF30[];
#ifdef TARGET_PC
/* PC: D_800E8FAC is the N64's label of D_800E8230[11].el, which has no PC symbol; the menus and their elements hold
 * addresses, so they are common.h's Nw2Menu and Nw2MenuEl, read by field name: p[k * 0x148 + 0xE] is element k's
 * fE. D_8007EF30 keeps its N64 layout, so its +0x30, the current cup's address, holds a handle (port.h's
 * PTR_TO_SLOT) of a common.h Nw2Cup, whose first byte is its id. */
extern Nw2Menu D_800E8230[];
#else
extern u8 *D_800E8FAC;
#endif
void func_800A8EF0(s32);
#define B(o) (*(u8 *)(D_8007EF30 + (o)))

void func_800AE1E4(void) {
    u16 f = *(u16 *)(D_8007EF30 + 8);
#ifdef TARGET_PC
    Nw2MenuEl *p = D_800E8230[11].el; /* PC: by name (see above) */
#else
    u8 *p = D_800E8FAC;
#endif
    s32 a;
    if (f & 0x8000) {
#ifdef TARGET_PC
        a = ((Nw2Cup *)SLOT_TO_PTR(*(u32 *)(D_8007EF30 + 0x30)))->id; /* PC: the cup's handle (see above) */
#else
        a = **(u8 **)(D_8007EF30 + 0x30);
#endif
        a += 2;
    } else if (f & 0x80) {
        a = 8;
    } else {
        a = 7;
    }
    func_800A8EF0(a);
#ifdef TARGET_PC
    /* PC: element k's fE, by name (see above) */
    p[0].fE = B(0x1A0);
    p[4].fE = B(0x1A2);
    p[2].fE = B(0x1A1);
    p[6].fE = B(0x1A3);
    p[8].fE = B(0x1A4);
    p[10].fE = B(0x1A5);
    p[12].fE = B(0x1A6);
    p[14].fE = B(0x1A7);
    p[16].fE = B(0x1A8);
    p[18].fE = B(0x1A9);
    p[20].fE = B(0x1AA);
#else
    p[0xE] = B(0x1A0);
    p[0x52E] = B(0x1A2);
    p[0x29E] = B(0x1A1);
    p[0x7BE] = B(0x1A3);
    p[0xA4E] = B(0x1A4);
    p[0xCDE] = B(0x1A5);
    p[0xF6E] = B(0x1A6);
    p[0x11FE] = B(0x1A7);
    p[0x148E] = B(0x1A8);
    p[0x171E] = B(0x1A9);
    p[0x19AE] = B(0x1AA);
#endif
}
