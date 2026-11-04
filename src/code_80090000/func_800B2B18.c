/* @header
 * func_800B2B18
 * VRAM 0x800B2B18 | ROM 0x5F288 | size 0x208
 * asm: asm/nonmatchings/code_80090000/func_800B2B18.s
 */
#include "common.h"


typedef struct { s32 a, b, c, d; u8 p[0x1C]; } R;
typedef struct { s16 m; s16 s; u8 p[8]; } U;
extern u8 D_8007E228[], D_8007E8C0[];
extern R D_800EA238[];
extern U D_8007E8CC[];
s32 func_800B29B4(s32);

s32 func_800B2B18(s32 k) {
    s32 r = 0;
    s32 i, t, v, w, y;
    s16 a, b;
    u8 *p;
    U *u;

    switch (k) {
    case 6:
        p = D_8007E228 + 0x60;
        for (i = 0; i < 4; i++) {
            y = p[i * 8] * 10;
            r += y;
            D_800EA238[i].a = y;
        }
        break;
    case 7:
        u = &D_8007E8CC[*(s16 *)(D_8007E8C0 + 0x6C)];
        for (i = 0; i < 4; i++) {
            b = u->s;
            a = u->m;
            t = a + (b != 0);
            w = 0;
            if (t < 2) {
                w = 0x5DC;
            } else if (t < 0xB) {
                w = 0x320;
            } else if (t < 0x10) {
                w = 0x1F4;
            } else if (t < 0x15) {
                w = 0x64;
            } else if (t >= 0x1E) {
                w = -((a * 0x3C + b - 0x708) * 0x32);
            }
            D_800EA238[i].b = w;
            r += w;
        }
        break;
    case 8:
        for (i = 0; i < 4; i++) {
            v = func_800B29B4(i);
            D_800EA238[i].c = v;
            r += v;
        }
        break;
    case 9:
        for (i = 0; i < 4; i++) {
            u8 *t = D_8007E228;
            v = (t[0x8C] >> i) & 1 ? 0x7D0 : 0;
            r += v;
            D_800EA238[i].d = v;
        }
        break;
    }
    return r;
}
