/* @header
 * func_8000F4FC
 * VRAM 0x8000F4FC | ROM 0x100FC | size 0x124
 * asm: asm/nonmatchings/main/func_8000F4FC.s
 */
#include "common.h"

extern s8 D_80036CAC[];
extern void *D_80036CB4[], *D_80036CCC[], *D_80036CE4[];
#ifdef TARGET_PC
/* PC: port_decls.h declares the two arrays of display records, D_80058A10 and D_80058FA0, and the addresses of their
 * display lists, D_80058A0C and D_80058F90. */
extern u8 D_80056CC0[];
#else
extern u8 D_80056CC0[], D_80058A10[], D_80058FA0[];
extern s32 D_80058A0C, D_80058F90;
#endif
extern s16 D_80059D82;
#ifdef TARGET_PC
/* PC: the types of the definitions, as func_8000EF90 and func_8000F408 declare them: freeResourceDescriptorArray frees
 * the display list, which the N64 line passes as an s32, and takes the count as an s16; func_80007020 returns the
 * display list it built, a pointer (Gfx7020 *, a type of its own file), and takes the count as an s16. port_decls.h
 * declares func_80007818, which takes that display list as a pointer. */
void freeResourceDescriptorArray(void *, void *, s16);
void *func_80007020(void *, void *, void *, s16);
#else
void freeResourceDescriptorArray(void *, s32, s8);
s32 func_80007020(void *, void *, void *, s8);
void func_80007818(void *, void *, s32, s32);
#endif

/* Switch the resource descriptor arrays to arena arg0: free the arrays of the
 * previously selected arena (D_80059D82), rebuild both descriptor arrays from
 * the per-arena tables, and refresh the derived data in D_80056CC0. */
void func_8000F4FC(s16 arg0) {
    freeResourceDescriptorArray(D_80058A10, D_80058A0C, D_80036CAC[D_80059D82]);
    freeResourceDescriptorArray(D_80058FA0, D_80058F90, D_80036CAC[D_80059D82]);
    D_80058A0C = func_80007020(D_80058A10, D_80036CB4[arg0], D_80036CCC[arg0], D_80036CAC[arg0]);
    D_80058F90 = func_80007020(D_80058FA0, D_80036CB4[arg0], D_80036CE4[arg0], D_80036CAC[arg0]);
    func_80007818(D_80056CC0, D_80058A10, D_80058A0C, 0);
}
