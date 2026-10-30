/* @header
 * func_80029C40
 * VRAM 0x80029C40 | ROM 0x2A840 | size 0x3C
 * asm: asm/nonmatchings/main/func_80029C40.s
 */
#include "common.h"

void func_80029C7C(void *, u16, s32 *, s32);

/* Render arg0 into a scratch result array and return the arg2-th entry. */
s32 func_80029C40(void *arg0, u16 arg1, s32 arg2) {
    s32 values[256];
    func_80029C7C(arg0, arg1, values, arg2);
    return values[arg2];
}

typedef struct { u32 w0, w1; } Cmd;
extern u8 D_38D80[], D_38DB0[];

extern u8 sjisCodeTable[];

typedef struct { u8 text[64]; s32 key0, key1; } Entry;
extern Entry *D_8007FC3C;
