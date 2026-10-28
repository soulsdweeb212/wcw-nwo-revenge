#include "common.h"

s32 func_800D36E8(f32, f32);
void unpackAnimationParameters(void *, void *);
extern u8 D_8007BD64[];
void func_800D4AD0(void *);
void func_800DECAC(void *, s32, s32, s32);
void func_800D3890(void *, void *, void *);
/* Sets the entity's animation to arg1 and unpacks its parameters from the
 * 0x18-byte table entry. */
void func_800A7D1C(void *arg0, s16 arg1) {
    *(s16 *)((u8 *)arg0 + 0x386) = arg1;
    *((u8 *)arg0 + 0x384) = *(u8 *)arg0;
    unpackAnimationParameters((u8 *)arg0 + 0x38C, D_8007BD64 + 0x14 + arg1 * 0x18);
}
