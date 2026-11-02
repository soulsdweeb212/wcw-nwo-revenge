/* @header
 * func_800B469C
 * VRAM 0x800B469C | ROM 0x60E0C | size 0x230
 * asm: asm/nonmatchings/code_80090000/func_800B469C.s
 */
#include "common.h"

typedef struct { u8 p0[8]; s16 a; u8 p1[0x18]; s16 b; u8 p2[0x124]; } R;
extern u8 *D_800E948C[], *D_800E95C4[];
extern R *D_800E9AA4;
extern u16 D_800EA0C2;
extern s16 D_800E95B4, D_800E947C;
extern s32 D_800EA0B8;
extern u8 D_8007EF30[];
s32 func_800B2F94(s32);
s32 func_800B39C0(void);
s32 func_800B43C0(s32);
s32 func_800B4A24(void);
void func_800B5704(s32);

s32 func_800B469C(void) {
    u8 *p = D_800E948C[0];
    s32 r = -1;
    u32 a, k;
    s32 f, i, o;
    u8 *e;
    u16 v;
    s16 *q;

    a = *(u16 *)(p + 0xCF2);
    k = a >> 8;
    e = p + 0xCD0;
    if (k < 0xA) {
        if (D_800EA0C2 & 0x8000) {
            a = 0x900;
        }
        *(u16 *)(p + 0xCF2) = func_800B2F94(a);
    } else if (k == 0xA) {
        *(u16 *)(p + 0xCF2) = func_800B39C0();
    } else if (k == 0xB) {
        o = 1;
        f = -1;
        q = &D_800E9AA4[5].b;
        for (i = 5; i < 9; i++) {
            if (q[-0xD] != 0) {
                f = 0;
            } else {
                *q = o;
            }
            q += 0xA4;
        }
        if (f && (D_800EA0C2 & 0x8000)) {
            q = &D_800E9AA4[5].b;
            for (i = 5; i < 9; i++) {
                if (q[-0xD] == 0) {
                    *q = 0;
                }
                q += 0xA4;
            }
            *(u16 *)(e + 0x22) = 0xC00;
        }
    } else if (k == 0xC) {
        v = func_800B43C0(a);
        *(u16 *)(p + 0xCF2) = v;
        if ((v >> 8) == 0xD) {
            D_800EA0B8 = 0;
            r = func_800B4A24();
            *(u16 *)(D_800E95C4[0] + 0x10B2) &= ~1;
            if (*(u16 *)(D_8007EF30 + 8) & 0x8000) {
                *(u16 *)(D_800E95C4[0] + 0x10C8) = 0x98;
            } else {
                *(u16 *)(D_800E95C4[0] + 0x10C8) = 0x9A;
                *(u16 *)(D_800E95C4[0] + 0xF6A) &= ~1;
            }
            D_800E95B4 = 0xD;
            func_800B5704(-1);
        }
    } else {
        *(u16 *)(D_800E948C[0] + 0x19AA) &= ~1;
        if (*(u16 *)(D_8007EF30 + 8) & 0x8000) {
            *(u16 *)(D_800E948C[0] + 0x19C0) = 0x98;
        } else {
            *(u16 *)(D_800E948C[0] + 0x19C0) = 0x9A;
            *(u16 *)(D_800E948C[0] + 0x1862) &= ~1;
        }
        D_800E947C = 0x14;
    }
    return r;
}
