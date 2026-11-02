/* @header
 * func_800AEA7C
 * VRAM 0x800AEA7C | ROM 0x5B1EC | size 0xEC
 * asm: asm/nonmatchings/code_80090000/func_800AEA7C.s
 */
#include "common.h"

extern u8 D_8007E228[], D_8007E8C0[];
void func_800A90DC(void *);
#define W(p, o) (*(s32 *)((p) + (o)))

void func_800AEA7C(void) {
    u8 *p = D_8007E228 + 0x60;
    W(D_8007E8C0, 0x7C) = -1;
    W(D_8007E8C0, 0x78) = -1;
    W(D_8007E8C0, 0x74) = -1;
    W(D_8007E8C0, 0x70) = -1;
    W(D_8007E228, 0x694) = -1;
    W(D_8007E228, 0x690) = -1;
    W(D_8007E228, 0x68C) = -1;
    W(D_8007E228, 0x688) = -1;
    W(D_8007E8C0, 0xC) = -1;
    W(D_8007E8C0, 0x8) = -1;
    W(D_8007E8C0, 0x4) = -1;
    W(D_8007E8C0, 0) = -1;
    W(D_8007E228, 0x61C) = 5;
    W(D_8007E228, 0x618) = 5;
    W(D_8007E228, 0x614) = 5;
    W(D_8007E228, 0x610) = 5;
    W(D_8007E228, 0x14) = -1;
    W(D_8007E228, 0x10) = -1;
    W(D_8007E228, 0xC) = -1;
    W(D_8007E228, 0x8) = -1;
    func_800A90DC(p);
    func_800A90DC(p + 8);
    func_800A90DC(p + 0x10);
    func_800A90DC(p + 0x18);
}
