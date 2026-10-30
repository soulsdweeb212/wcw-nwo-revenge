/* @header
 * func_8000EED8
 * VRAM 0x8000EED8 | ROM 0xFAD8 | size 0xB8
 * asm: asm/nonmatchings/main/func_8000EED8.s
 */
#include "common.h"

extern s16 D_8005A380[], D_8005A382[];
extern f64 D_8003B250;
void func_8000F4FC(s16);
void func_800074A4(s32, void *, void *, s32);
extern void *D_80036C74[], *D_80036C94[];
extern u8 D_80036D04[], D_800587F0[], D_80058900[], D_80058988[];
extern s32 D_800587EC, D_800588F8, D_80058984;
extern s16 D_80059D82;
/* Selects arena resource set arg0: rebinds the three descriptor arrays from the
 * corresponding source sets and records the selection. */
void func_8000EED8(s16 arg0) {
    void *p;
    func_8000F4FC(arg0);
    p=D_80036C74[arg0];
    if(p) func_800074A4(D_800587EC,D_800587F0,p,6);
    func_800074A4(D_800588F8,D_80058900,D_80036C94[arg0],3);
    func_800074A4(D_80058984,D_80058988,D_80036D04,3);
    D_80059D82=arg0;
}
extern u8 D_800706A0[], D_80075458[], D_80075459[], D_8007545A[], D_8007545B[];
