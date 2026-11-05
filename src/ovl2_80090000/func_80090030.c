/* @header
 * func_80090030
 * VRAM 0x80090030 | ROM 0x834D0 | size 0x350
 * asm: asm/nonmatchings/ovl2_80090000/func_80090030.s
 */
#include "common.h"

typedef struct {
    u8 pad0[6];
    u16 f6;
    u8 pad8[4];
} Pad;

void func_8000440C(s32);
void func_80004240(s32);
void resetMatchState(void);
void func_80099F70(void);
void func_80099628(void);
void func_80003478(s32);
s32 func_80002C74(void);
void func_80003E78(s32);
s32 func_8009D844(s32, s32, s32);
s32 func_8009D7A0(s32, s32, s32);
void runMatchPhaseStateMachine(void);
s16 func_80099968(s16);
void MusStop(s32, s32);
void func_8009A374(s32);
s8 func_800D633C(void);
void func_8000E55C(s32, s32, s32);
void func_8000E09C(s32);
void func_800998EC(void);
void func_8009A5F4(void);

extern s8 D_8007E228[];
extern Pad D_8006E178[];
extern s16 D_8006E440;
extern s32 D_800F99B0;
extern s16 D_800F99B6;
extern s16 D_800F9A9C;
extern u8 D_800FADCF;

void func_80090030(void) {
    s16 fade;
    u8 vol;
    s16 started;
    s32 rate;
    s16 state;
    s16 sel;
    s16 done;
    s16 timer;
    u32 i;

    fade = 1;
    vol = 0;
    started = 0;
    rate = 0x1E;
    func_8000440C(0);
    func_80004240(0xF);
    state = 0;
    resetMatchState();
    sel = 0;
    func_80099F70();
    done = 0;
    func_80099628();
    timer = 0;
    func_80003478(D_8007E228[0x609]);
    func_80002C74();
    do {
        func_80003E78(0);
        if (state == 0) {
            if (fade != 0) {
                fade = func_8009D844(0xFF, 0xFF, 0xFF);
            }
            if ((D_800FADCF & 0x80) && func_8009D7A0(0xFF, 0xFF, 0xFF) == 0) {
                done = 1;
            }
            if (done == 0) {
                runMatchPhaseStateMachine();
            }
        }
        state = func_80099968(sel);
        if (state >= 2) {
            if (state != 2) {
                timer = 0x3C;
                if (state == 3) {
                    D_800F99B0 = 1;
                }
            }
            sel = 0;
        }
        if (timer != 0) {
            if (timer >= 2) {
                timer--;
            } else {
                D_800FADCF |= 0x80;
                MusStop(1, 0x3C);
            }
        } else if (sel == 0) {
            if (fade == 0 && !(D_800FADCF & 0x80) && D_800F9A9C == 0) {
                for (i = 0; i < 4; i++) {
                    if (D_8006E178[i].f6 & 0x1000) {
                        sel = i + 1;
                    }
                }
            }
        } else if (D_8006E178[sel - 1].f6 & 0x5000) {
            sel = 0;
        }
        func_8009A374(state);
        if (started) {
            if (D_800F99B6 != 0) {
                if (D_8006E440 != 0 && func_800D633C()) {
                    D_8006E440 = 0;
                }
                if (timer == 0 && func_800D633C()) {
                    vol = 0xF;
                } else {
                    vol = 0;
                }
                rate = 8;
            }
            func_8000E55C(vol, rate, D_8007E228[0x608]);
        } else if (D_800F9A9C == 0) {
            started = 1;
            vol = D_8007E228[0x624];
        }
    } while (done == 0);
    if (timer != 0) {
        *(s32 *)(D_8007E228 + 0x620) = 0;
    }
    func_8000440C(1);
    func_80003E78(0);
    func_8000E09C(0);
    MusStop(1, 1);
    func_80002C74();
    func_80002C74();
    func_800998EC();
    func_8009A5F4();
}
