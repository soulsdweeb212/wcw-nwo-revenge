/* @header
 * func_800BC9AC
 * VRAM 0x800BC9AC | ROM 0x6911C | size 0x208
 * asm: asm/nonmatchings/code_80090000/func_800BC9AC.s
 */
#include "common.h"

extern s32 D_800DF1E0, D_800EA0A8, D_800EA0AC, D_800EA320, D_800E74B8, D_800E74BC, D_800E7C90;
extern u8 D_8007E228[], D_8007E8C0[], D_8007EF30[];
extern s32 D_8007E8C4[], D_8007E8C8[];
void func_800AA1E0(s32, s32, s32, s32);
void func_800BB6E8(s32);

void func_800BC9AC(void) {
    s32 x, y;

    func_800AA1E0(0, ((s32 *)(D_8007E228 + 0x688))[D_800DF1E0], ((s32 *)(D_8007E8C0 + 0x70))[D_800DF1E0] | 0x88, 6);
    if ((*(u16 *)(D_8007EF30 + 8) & 0x60) && D_8007E8C4[D_800DF1E0] >= 0) {
        func_800AA1E0(1, ((s32 *)(D_8007E228 + 0x688) + D_800DF1E0)[1], ((s32 *)(D_8007E8C0 + 0x70) + D_800DF1E0)[1] | 0x88, 6);
        func_800BB6E8(2);
        if (!((D_800E7C90 - 2) & 1)) {
            x = D_800EA0A8;
            y = D_800EA0AC;
            if (x < y) {
                goto lo;
            }
            goto hi;
        }
        x = D_800EA0A8;
        y = D_800EA0AC;
        if (x >= y) {
            D_800EA320 = x;
        } else {
            D_800EA320 = y;
        }
        if (D_800EA320 == 0xF) {
            x = D_800EA0A8;
            y = D_800EA0AC;
            if (x != y) {
                if (x >= y) {
hi:
                    D_800EA320 = y;
                } else {
lo:
                    D_800EA320 = x;
                }
            }
        }
    } else {
        if ((*(u16 *)(D_8007EF30 + 8) & 0x10) && D_8007E8C8[D_800DF1E0] >= 0) {
            func_800AA1E0(1, ((s32 *)(D_8007E228 + 0x690))[D_800DF1E0], 0, 6);
            func_800BB6E8(0);
        } else {
            D_800E74BC = D_800E74B8;
            D_800EA0AC = D_800EA0A8;
            func_800BB6E8(0);
        }
        D_800EA320 = D_800EA0A8;
    }
}
