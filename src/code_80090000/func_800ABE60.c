/* @header
 * func_800ABE60
 * VRAM 0x800ABE60 | ROM 0x585D0 | size 0x168
 * asm: asm/nonmatchings/code_80090000/func_800ABE60.s
 */
#include "common.h"

extern s32 D_800E7C90, D_800E7530;
extern s16 D_80038A90, D_800E7CB8;
extern u8 D_8007EF30[], D_8007E228[], D_800E7B67[];
#ifdef TARGET_PC
/* PC: the game functions this file calls, declared with their definitions' types (func_800BCD30.c, func_8000E55C.c). */
s32 func_800BCD30(void);
void func_8000E55C(s32 arg0, s16 arg1, s8 arg2);
#endif

void func_800ABE60(void) {
    s32 s = 8;
    s32 r;
    s32 v;

    if (D_800E7C90 != 0) {
        r = func_800BCD30();
    } else {
        switch (D_80038A90) {
        case 0:
        case 0x17:
            r = -1;
            break;
        case 0x16:
            r = 0;
            break;
        case 0xF:
            if (*(u16 *)(D_8007EF30 + 8) & 0x800) {
                r = 0x13;
            } else {
                r = 0xF;
                if (*(u16 *)(D_8007EF30 + 8) & 0x8000) {
                    if (!(*(s32 *)(D_8007E228 + 0x620) & 0x201)) {
                        r = 0x14;
                    }
                }
            }
            break;
        case 9:
        case 0xA:
            s = 0x20;
            r = 0xE;
            break;
        case 0x10:
        case 0x11:
            if (D_800E7CB8 > 0) {
                v = D_800E7B67[D_800E7CB8 * 2];
            } else {
                v = -1;
            }
            if (v == 9) {
                r = 0xE;
            } else if (*(u16 *)(D_8007EF30 + 8) & 0x800) {
                r = 0x13;
            } else {
                r = 0xF;
            }
            break;
        case 0x12:
        case 0x13:
            r = 0xD;
            s = 0x20;
            break;
        case 0xD:
        case 0xE:
            r = 0xC;
            if ((*(u16 *)(D_8007EF30 + 8) & 0xF) == 8) {
                s = 0x20;
                r = 0xD;
            }
            break;
        default:
            r = 0xC;
            break;
        }
    }
    D_800E7530 = r;
    if (r >= 0) {
        func_8000E55C((s16)r, s, 0x50);
    }
}
