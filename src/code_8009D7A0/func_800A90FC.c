/* @header
 * func_800A90FC
 * VRAM 0x800A90FC | ROM 0x9C59C | size 0x2C
 * asm: asm/nonmatchings/code_8009D7A0/func_800A90FC.s
 */
#include "common.h"

extern s16 D_800E3270[];
extern s16 D_800E3262[];
extern u8 D_8007E228[];
extern u8 D_8007EF30[];
s32 func_800D35B0(s32, s32);
void func_800D4AD0(void *);
s32 func_800D4CC4(void *);
void func_800D427C(void *, s16, s32);

/* Wrestler arg0's current opponent id. */
s8 func_800A90FC(s16 arg0) {
    return D_800F9D10[arg0].opponentId;
}
