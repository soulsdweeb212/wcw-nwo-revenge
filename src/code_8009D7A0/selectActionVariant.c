#include "common.h"

typedef struct {
    u8 pad0[0x12];
    s16 f12;
    u8 pad14[0xA];
    s16 f1E;
    u8 pad20[2];
    s16 f22;
    u8 pad24[8];
    s16 f2C;
    u8 pad2E[6];
    f32 f34;
} Nw2ActABD0;

extern Nw2ActABD0 *D_800FABD0;
extern u8 D_800E3448[];
extern u8 D_800E3468[];
extern u8 D_800E3480[];
extern f64 D_800E4DD8;

s8 func_800AB0E8(void);
s8 func_800AB1B0(void);
s8 func_800AB2B4(void);
s8 func_800D4198(s16);
void func_800AD958(s32);
void func_800ADA38(void *);

/* Action dispatch: try the three sub-handlers in turn; if the record's f22 is
 * 0x11 or 0x17 and the random check passes, play action 0x3D. Otherwise choose
 * a parameter set -- by f1E vs f2C, and f34 against the threshold -- and run it
 * via func_800ADA38. */
void selectActionVariant(void) {
    Nw2ActABD0 *act;
    s16 state;
    u8 *paramSet;

    if (func_800AB0E8()) return;
    if (func_800AB1B0()) return;
    if (func_800AB2B4()) return;
    act = D_800FABD0;
    state = act->f22;
    if ((state == 0x11) | (state == 0x17)) {
        if (func_800D4198(act->f12)) {
            func_800AD958(0x3D);
            return;
        }
        act = D_800FABD0;
    }
    if (act->f1E != act->f2C) {
        paramSet = D_800E3480;
    } else {
        paramSet = D_800E3468;
        if (act->f34 > D_800E4DD8) paramSet = D_800E3448;
    }
    func_800ADA38(paramSet);
}
