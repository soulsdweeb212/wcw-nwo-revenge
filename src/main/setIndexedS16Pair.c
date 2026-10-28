#include "common.h"

extern s16 D_8005A380[], D_8005A382[];

/* Store a pair of s16 values at (side arg3, slot arg2). */
void setIndexedS16Pair(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 off = arg3 * 4 + arg2 * 12;
    *(s16 *)((u8 *)D_8005A380 + off) = arg0;
    *(s16 *)((u8 *)D_8005A382 + off) = arg1;
}

extern f64 D_8003B250;

void func_8000F4FC(s16);
void func_800074A4(s32, void *, void *, s32);
extern void *D_80036C74[], *D_80036C94[];
extern u8 D_80036D04[], D_800587F0[], D_80058900[], D_80058988[];
extern s32 D_800587EC, D_800588F8, D_80058984;
extern s16 D_80059D82;

extern u8 D_800706A0[], D_80075458[], D_80075459[], D_8007545A[], D_8007545B[];
