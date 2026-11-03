/* @header
 * func_800C1C70
 * VRAM 0x800C1C70 | ROM 0x6E3E0 | size 0x2B4
 * asm: asm/nonmatchings/code_80090000/func_800C1C70.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
extern s32 D_80038A8C, D_80038A98, D_800D5744, D_800D5748, D_800D574C, D_800D5750, D_800D5F28;
extern s32 D_800DF218, D_800DF304, D_800DF3AC, D_800E74C8, D_800E7C90;
extern u8 *D_800DF210;
extern G *D_800DF214;
extern u16 D_800EA0C2;
void func_8000DEE4(s32);
void func_8000DF78(s32);
void func_8000E55C(s32, s32, s32);
void func_80096A20(s32, s32);
void func_8009F2F8(G **, s32);
void func_8009F8BC(G **);
void func_800AC144(void);
void func_800B6334(void);
void func_800C194C(s32);

s32 func_800C1C70(void) {
    G *p;
    s32 x;
    D_800DF218 ^= 1;
    p = (G *)(D_800DF210 + (D_800DF218 << 15));
    D_800DF214 = p + 1;
    p->w0 = 0xDF000000;
    p->w1 = 0;
    func_800AC144();
    if (D_800E7C90 == 0 || D_800E7C90 == 0x30 || D_800E7C90 == 0x3D) {
        func_800C194C(D_800E7C90);
        if (D_800DF304 != 0 && (D_800EA0C2 & 0x9000)) {
            D_80038A8C = 1;
        }
    }
    if (D_80038A8C > 0) {
        x = D_800E74C8;
        if (x >= 0) {
            D_800E74C8 = x + 0x10;
            if (D_800E74C8 >= 0xFF) {
                D_800E74C8 = 0xFF;
                if (x >= 0xFF) {
                    D_80038A8C = -1;
                }
            }
        } else {
            D_800E74C8 = x - 0x10;
            if (D_800E74C8 < -0xFE) {
                D_800E74C8 = -0xFF;
                if (x >= -0xFF) {
                    D_80038A8C = -1;
                }
            }
        }
        if (D_80038A8C < 0) {
            func_8000DEE4(0x411);
            func_8000E55C(0, 1, 0x50);
        }
    } else if (D_800DF3AC == 0 && D_800E7C90 == 0 && D_800DF304 == 0) {
        if (D_800E74C8 > 0) {
            D_800E74C8 -= 0x18;
            if (D_800E74C8 < 0) {
                D_800E74C8 = 0;
            }
        } else {
            D_800E74C8 += 0xC;
            if (D_800E74C8 > 0) {
                D_800E74C8 = 0;
            }
        }
    }
    func_8009F2F8(&D_800DF214, D_800E74C8);
    func_8009F8BC(&D_800DF214);
    if (D_80038A8C < 0) {
        if (D_800D5744 != 0) {
            D_800D5744 = 0;
            if (D_800D5748 >= 0) {
                func_8000DF78(D_800D5748);
                D_800D5748 = -1;
            }
        }
        if (D_800D574C != 0) {
            D_800D574C = 0;
            if (D_800D5750 >= 0) {
                func_8000DF78(D_800D5750);
                D_800D5750 = -1;
            }
        }
        D_800D5F28 = 0;
        D_80038A98 = 1;
        return D_80038A8C == -1 ? -1 : 1;
    }
    func_800B6334();
    func_80096A20(0, 0xF0);
    return 0;
}
