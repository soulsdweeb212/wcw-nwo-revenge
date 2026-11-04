/* @header
 * func_800C5214
 * VRAM 0x800C5214 | ROM 0x71984 | size 0x2B0
 * asm: asm/nonmatchings/code_80090000/func_800C5214.s
 */
#include "common.h"




typedef struct { u8 p0[0x18]; u8 *p; u8 f; u8 p1[0xBF]; } N;
typedef struct { u8 p0[0xDC]; N n[0x16]; } H;
extern s32 D_800D5F40, D_800D5F44, D_800D5F20, D_800D5F18, D_800DF3C0, D_800E7C90, D_800E9F80;
typedef struct { s32 a, b, c; } V;
extern V D_800DF3C8[];
extern u8 D_800DF3E0[], D_8006527C[], D_8007EF30[];
void func_800B83D0(void *);
void func_80001DC4(void *);
void func_800A1C04(void);
void func_800C1F24(void);
void func_80090738(s32);
void updateRingCornerFlags(void);
void func_800C3110(s32, s32);
void func_80010E6C(void);
void func_80012CD0(void);
void func_8000EDC4(void);
void func_80001EA8(s32);
void func_800966D0(s32, s32);
void func_80002C0C(void);
void func_800C4C78(s32);
void func_800B642C(void);
void func_80002BC0(void *);

void func_800C5214(s32 a) {
    s32 m, i, j, s, n;
    u8 *p, *h;

    func_800B83D0(&D_800DF3C8[D_800D5F40]);
    func_80001DC4(D_800DF3E0);
    if (a == 1) {
        func_800A1C04();
    } else {
        func_800C1F24();
    }
    func_80090738(D_800D5F20);
    updateRingCornerFlags();
    if (a != 1) {
        func_800C3110(0, D_800D5F18);
        func_800C3110(1, D_800D5F18);
        func_800C3110(2, D_800D5F18);
        func_800C3110(3, D_800D5F18);
    } else {
        func_800C3110(0, D_800D5F18);
        func_800C3110(1, D_800D5F18);
    }
    func_80010E6C();
    func_80012CD0();
    if (!(D_800D5F18 & 7)) {
        func_8000EDC4();
    }
    func_80001EA8(1);
    m = 0x7FFFFFFF;
    for (i = 0; i < D_800DF3C0; i++) {
        s = 0;
        n = 0;
        for (j = 1, h = D_8006527C + i * 0x13C4, p = h + 0x14; j < 0x17; j++, p += 0xDC) {
            if (!(p[4] & 0x80)) {
                h = *(u8 **)p;
                if (h) {
                    n++;
                    s += (s32)*(f32 *)(h + 0x28);
                }
            }
        }
        if (n) {
            s /= n;
            if (s < m) {
                m = s;
            }
        }
    }
    func_800966D0(m, *(s16 *)(D_8007EF30 + 0xA));
    func_80002C0C();
    func_800C4C78(D_800D5F20 ? (D_800E7C90 ? 2 : 1) : 0);
    func_800B642C();
    func_80002BC0(&D_800DF3C8[D_800D5F40]);
    D_800E9F80 = D_800DF3C8[D_800D5F40].a;
    D_800D5F40 ^= 1;
    D_800D5F44++;
}
