#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800FAF58;
extern s16 D_800E3658[];
extern f64 D_800E4E68;
extern f64 D_800E4E70;
extern f64 D_800E4E40;
extern u8 D_800E35F8;
s8 func_800D4198(s16);
void func_800AD958(s32);
void func_800ADA38(void *);

/* Requests action 0x27 or 0x21 (or the fallback record) from the action timer. */
void func_800ABCD8(void) {
    if (func_800D4198(*(s16 *)(D_800FABD0 + 0x12)) != 0) {
        if (D_800E4E40 < (f64)*(f32 *)(D_800FABD0 + 0x34))
            func_800AD958(0x21);
        else
            func_800ADA38(&D_800E35F8);
    } else {
        func_800AD958(0x27);
    }
}
