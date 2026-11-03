/* @header
 * func_800C3110
 * VRAM 0x800C3110 | ROM 0x6F880 | size 0x2E4
 * asm: asm/nonmatchings/code_80090000/func_800C3110.s
 */
#include "common.h"

typedef struct {
    u8 pad0[0x680];
    f32 f680;
    f32 f684;
    u8 pad688[4];
    s32 f68C;
    u8 pad690[6];
    u16 f696;
    u8 pad698[0x1A];
    s16 f6B2;
    s16 f6B4;
    s16 f6B6;
    s16 f6B8;
    u8 pad6BA[5];
    s8 f6BF;
    u8 pad6C0[4];
    union { s32 w; struct { u16 hi, lo; } h; } f6C4;
    u8 f6C8;
    u8 f6C9;
    s16 f6CA;
    s16 f6CC;
    s16 f6CE;
} Wr3110;

extern u8 *D_800E79B8;
extern s32 D_800E74D8;
extern u8 D_800E74E4;
extern u8 D_800EA2D8;
extern f32 D_800E81EC[];
extern u8 D_800651A0[];
extern f64 D_800D6C70;
f32 cosf(f32);
f32 sinf(f32);
void func_800018C4(void *, f32 *, u8, u8);
void func_800056F4(f32 *, f32, f32, f32);
s16 func_80008574(s16);
void func_80008CE8(s32, s16, s16, void *, s32, s32);
void func_8000CD18(s32, f32, f32);
void func_8000D238(s32, u16);
s16 func_800C2E50(Wr3110 *);
void updatePartPositions(s32);

void func_800C3110(s32 a, s32 b) {
    Wr3110 *w = (Wr3110 *)(D_800E79B8 + a * 0x6D0);
    s32 id;
    f32 f;
    f32 ang;
    s32 x;
    u8 pad[16];

    w->f68C &= 0xFFF;
    id = (s16)a;
    func_8000D238(id, w->f6C4.h.lo);
    if (w->f6C4.w == 0x80) {
        return;
    }
    w->f6B8 = func_80008574(w->f6B2 = func_800C2E50(w));
    if (w->f6B4 >= w->f6B8) {
        w->f6B4 = 0;
        w->f6B6 = 0;
    }
    func_80008CE8(id, w->f6B2, w->f6B4, &w->f680, 0, w->f6BF);
    if (w->f6C4.w == 4) {
        updatePartPositions(id);
        func_8000CD18(id, 90.0f, 0.0f);
    } else {
        if (D_800E74D8 == -5 || D_800E74D8 == -4) {
            f = 0.0f;
        } else if (D_800E74D8 == -6) {
            func_8000CD18(id, w->f684, w->f684);
            goto done;
        } else {
            f = -1000.0f;
        }
        func_8000CD18(id, f, f);
    }
done:
    w->f6B6 = ++w->f6B4;
    if (!(w->f696 & 8)) {
        ang = (b & 0xFF) * D_800D6C70;
        x = cosf(ang) * 1000.0f;
        func_800056F4(D_800E81EC, x, 1000.0f, (s32)(sinf(ang) * 1000.0f));
        D_800E74E4 = 0xFF;
        D_800EA2D8 = 0x80;
    } else {
        func_800056F4(D_800E81EC, w->f6CA, w->f6CC, w->f6CE);
        D_800E74E4 = w->f6C8;
        D_800EA2D8 = w->f6C9;
    }
    func_800018C4(D_800651A0 + a * 0x13C4, D_800E81EC, D_800E74E4, D_800EA2D8);
}
