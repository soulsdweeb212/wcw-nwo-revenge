/* @header
 * func_8009A374
 * VRAM 0x8009A374 | ROM 0x8D814 | size 0x280
 * asm: asm/nonmatchings/ovl2_80090000/func_8009A374.s
 */
#include "common.h"

typedef struct { u8 pad[0xC]; } View;

void func_8009A75C(s16);
void setupTiltedPerspectiveCamera(void *, f32, f32, f32, f32, f32, f32, f32);
void updateRingCornerFlags(void);
void func_8000EDC4(void);
void updatePartPositions(s16);
void func_8000CD18(s16, f32, f32);
void func_800018C4(void *, f32 *, u8, u8);
s8 func_800D633C(void);
s8 func_800D6350(void);
void func_80010E6C(void);
void func_80012CD0(void);
void func_8000E724(s16);
void func_80001EA8(s32);
void func_800942F0(s16);
void func_80098560(void);
void func_80002BC0(void *);
void tickPlayerScripts(void);

extern u8 D_800651A0[];
extern u8 D_800E2FA6;
extern u8 D_800E2FA7;
extern s32 D_800E2FA8;
extern u32 D_800E2FAC;
extern View D_800EB360[];
extern s16 D_800EB378;
extern f32 D_800EB37C[3]; /* camera eye */
extern f32 D_800EB388[3]; /* camera target */
extern f32 D_800EB394[];
extern f32 D_800EB3A4;
extern u16 D_800F99B6;
extern s16 D_800FACEA[];

void func_8009A374(s16 arg0) {
    u32 i;
    s32 n;

    func_8009A75C(arg0);
    setupTiltedPerspectiveCamera(&D_800EB360[D_800E2FA8], D_800EB3A4 * 0.017453292519943295,
                                 D_800EB37C[0], D_800EB37C[1], D_800EB37C[2], D_800EB388[0],
                                 D_800EB388[1], D_800EB388[2]);
    updateRingCornerFlags();
    if (arg0 == 0 && !(D_800E2FAC & 0xF)) {
        func_8000EDC4();
    }
    for (n = 0, i = 0; i < 4; i++) {
        if (D_800FACEA[i] >= 0) {
            updatePartPositions(i);
            func_8000CD18(i, 90.0f, 0.0f);
            if (D_800E2FAC % D_800EB378 == n) {
                func_800018C4(D_800651A0 + i * 0x13C4, D_800EB394, D_800E2FA6, D_800E2FA7);
            }
            n++;
        }
    }
    if (arg0 == 0 && (!func_800D633C() || func_800D6350())) {
        func_80010E6C();
        func_80012CD0();
    }
    func_8000E724(arg0 | D_800F99B6);
    func_80001EA8(1);
    func_800942F0(arg0);
    func_80098560();
    func_80002BC0(&D_800EB360[D_800E2FA8]);
    tickPlayerScripts();
    D_800E2FA8 ^= 1;
    D_800E2FAC++;
}
