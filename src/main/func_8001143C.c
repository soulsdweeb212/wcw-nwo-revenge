/* @header
 * func_8001143C
 * VRAM 0x8001143C | ROM 0x1203C | size 0x18
 * asm: asm/nonmatchings/main/func_8001143C.s
 */
#include "common.h"

extern s32 D_8005A3B0[];

s32 func_8001143C(s32 arg0) {
    return D_8005A3B0[arg0 & 3];
}

extern u8 D_80059DA8[];

extern s32 D_80059D90[];

void releaseHeapBlock(s32);

extern u8 D_8005AAAD[];
extern u8 D_80036DFC[];
extern u8 D_80036E04[];
extern u8 D_80036E0C[];
