#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;
extern u8 *D_800FAF58;
extern s16 D_800E3658[];
extern f64 D_800E4E68;
extern f64 D_800E4E70;
extern f64 D_800E4E40;
extern f64 D_800E4E38;
extern f64 D_800E4E30;
extern u8 D_800E35F8;
extern u8 D_800E35E0;
s8 func_800D4198(s16);
void func_800AD958(s32);
void func_800ADA38(void *);

/* Requests action 7/0x21 or the fallback record from the action timer. */
void func_800ABC40(void) {
    if (D_800E4E30 < (f64)*(f32 *)(D_800FABD0 + 0x34)) {
        if (func_800D4198(*(s16 *)(D_800FABD0 + 0x12)) != 0) {
            func_800AD958(7);
            return;
        }
    }
    if ((f64)*(f32 *)(D_800FABD0 + 0x34) < D_800E4E38) {
        func_800ADA38(&D_800E35E0);
        return;
    }
    func_800AD958(0x21);
}
