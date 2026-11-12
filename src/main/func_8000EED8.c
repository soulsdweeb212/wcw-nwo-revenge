/* @header
 * func_8000EED8
 * VRAM 0x8000EED8 | ROM 0xFAD8 | size 0xB8
 * asm: asm/nonmatchings/main/func_8000EED8.s
 */
#include "common.h"

extern s16 D_8005A380[], D_8005A382[];
extern f64 D_8003B250;
void func_8000F4FC(s16);
#ifdef TARGET_PC
/* PC: func_800074A4 takes the display list to fill as a pointer (its definition's Gfx74A4 *, a type of its own file;
 * the N64 line passes it as an s32), then the display records, the resource ids (u16) and the record count (s16). */
void func_800074A4(void *, void *, u16 *, s16);
#else
void func_800074A4(s32, void *, void *, s32);
#endif
extern void *D_80036C74[], *D_80036C94[];
#ifdef TARGET_PC
/* PC: D_80036D04 is an array of 16-bit resource ids, which func_800074A4 reads as u16 (func_8000E920 declares it
 * 16-bit too, for func_80007020): the PC sets game variables in its own byte order by the width their declarations
 * give (port/game_vars.tsv). port_decls.h declares the three arrays of display records. */
extern u16 D_80036D04[];
#else
extern u8 D_80036D04[], D_800587F0[], D_80058900[], D_80058988[];
#endif
#ifndef TARGET_PC /* on PC, port_decls.h declares these three pointers (the display lists that func_80007020 returns) */
extern s32 D_800587EC, D_800588F8, D_80058984;
#endif
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
