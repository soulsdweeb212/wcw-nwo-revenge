/* @header
 * func_800A13DC
 * VRAM 0x800A13DC | ROM 0x9487C | size 0x174
 * asm: asm/nonmatchings/code_8009D7A0/func_800A13DC.s
 */
#include "common.h"

extern u16 D_800F9D08[];
extern u16 D_800FADC6[];
extern s8 D_800FADB8;
extern u16 D_800FABE6;
s16 func_800D4D44(void *, s32, s32);
void func_800D427C(void *, s32, s32);
s8 func_800B4C60(void *, void *, u16, s32);

void func_800A13DC(void) {
    u16 flags;

    switch (D_800EB408->step) {
    case 0:
        if (D_800EB408->moveMode & 0x200) {
            func_800D427C(D_800EB408, (s16)func_800D4D44(D_800EB408, 0xA, 0), 1);
        } else {
            func_800D427C(D_800EB408, 0xE71, 2);
        }
        D_800EB408->moveMode = D_800EB408->moveMode | 0x1A0;
        D_800EB408->step++;
    case 1:
        func_800B4C60(D_800EB408, D_800EB40C, D_800FABE6, 1);
        if (D_800EB408->animFramesLeft > 0) {
            return;
        }
        flags = D_800EB408->moveMode;
        D_800EB408->moveMode = flags & 0xFCFF;
        if ((s16)D_800F9D08[D_800FADB8] <= 0) {
            D_800FADC6[D_800FADB8] = 0;
        } else {
            D_800EB408->moveMode = flags & 0xFC7F;
        }
        D_800F9D08[D_800FADB8]++;
        func_800A6C48(D_800EB408, 3);
        D_800EB408->step = 2;
        D_800EB408->flags = D_800EB408->flags & 0xFFFFFFFFFEFFFFFFULL;
        break;
    }
}
