/* @header
 * func_800AA1E0
 * VRAM 0x800AA1E0 | ROM 0x56950 | size 0x1AC
 * asm: asm/nonmatchings/code_80090000/func_800AA1E0.s
 */
#include "common.h"

extern u8 D_8007EF30[];
extern s32 D_800E74D8, D_800E6B7C;
extern s32 D_800E8200[];
extern u32 D_800EA2D0[];

s32 func_800AA1E0(s32 a, s32 b, u32 c, s32 d) {
    u32 r;
    s32 x;

    if (a < 0) {
        if (c & 0x80) {
            if (func_800B04BC(b) != 0) {
                r = c | (**(u8 **)(D_8007EF30 + 0x30) * 16 + 4);
            } else {
                r = c & 0x7F;
            }
        } else {
            r = c;
        }
        if (r & 4) {
            c = (r >> 4) & 7;
            if ((c == 3 && findIdSubTableIndex(b) == 0) || c == 4) {
                r += 0x10;
            }
        }
        return r;
    }
    if (d >= 6) {
        if (D_800E74D8 != -1) {
            if (D_800E74D8 == -2 && a == D_800E6B7C) {
                { s32 q = func_8002B5AC(b); s32 m = ((c & 3) << 16) | 0x5100; func_80099148(q | m, 0x15C, 0xA6, 0, 0); }
            }
            if (c & 0x80) {
                if (func_800B04BC(b) != 0) {
                    r = c | (**(u8 **)(D_8007EF30 + 0x30) * 16 + 4);
                } else {
                    r = c & 0x7F;
                }
            } else {
                r = c;
            }
            if (r & 4) {
                c = (r >> 4) & 7;
                if ((c == 3 && findIdSubTableIndex(b) == 0) || c == 4) {
                    r += 0x10;
                }
            }
            d = 6;
            D_800E8200[a] = b;
            D_800EA2D0[a] = r;
        }
    }
    return d;
}
