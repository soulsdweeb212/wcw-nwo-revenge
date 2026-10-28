#include "common.h"

extern s8 D_800FA063[];
extern s16 D_800E3270[];
extern s16 D_800E3262[];
extern u8 D_8007E228[];
extern u8 D_8007EF30[];
s32 func_800D35B0(s32, s32);
void func_800D4AD0(void *);
s32 func_800D4CC4(void *);
void func_800D427C(void *, s16, s32);

/* Entity arg0's type byte. */
s8 func_800A90FC(s16 arg0) {
    return D_800FA063[arg0 * 0x3B0];
}
