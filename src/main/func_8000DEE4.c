#include "common.h"

extern u16 D_8006A2A4[];
extern u8 D_80031060[];
extern s16 D_80030DD4[];

extern u16 D_800306A0[];
s32 func_800032A4(s32, s32, s32, s32, s32);
void func_80013F7C(s32, s32);

/* Plays sound arg0 (remapped through D_800306A0 for ids 0x401..0x42B) if it is
 * in range, and returns the voice handle. */
s32 func_8000DEE4(s32 arg0) {
    s32 ret;
    s32 t;
    s16 x;

    ret = 0;
    t = arg0;
    if ((u16)(arg0 - 0x401) < 0x2B) {
        x = D_800306A0[(s16)arg0];
    } else {
        x = t;
    }
    if (x >= 0) {
        if (x < 0x97) {
            ret = func_800032A4(x, 0x80, 0x80, 0, -1);
            func_80013F7C(ret, 0);
        }
    }
    return ret;
}
