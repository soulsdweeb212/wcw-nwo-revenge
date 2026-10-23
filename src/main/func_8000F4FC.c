#include "common.h"

extern s8 D_80036CAC[];
extern void *D_80036CB4[], *D_80036CCC[], *D_80036CE4[];
extern u8 D_80056CC0[], D_80058A10[], D_80058FA0[];
extern s32 D_80058A0C, D_80058F90;
extern s16 D_80059D82;
void freeResourceDescriptorArray(void *, s32, s8);
s32 func_80007020(void *, void *, void *, s8);
void func_80007818(void *, void *, s32, s32);

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
