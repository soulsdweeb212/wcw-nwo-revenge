/* @header
 * func_800014AC
 * VRAM 0x800014AC | ROM 0x20AC | size 0x24
 * asm: asm/nonmatchings/main/func_800014AC.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_80048288 is the 4x4 float matrix that multiplyMatrix4x4 writes (func_80001CA0 declares it so), the kind of
 * matrix that multiplyMatrix4x4's PC declaration below takes. */
extern f32 D_80048288[4][4];
#else
extern u8 D_80048288[8];
#endif
#ifndef TARGET_PC /* on PC, port_decls.h declares D_80046860 */
extern s32 D_80046860[];
#endif
extern s16 D_80047062;
extern u8 *D_80046858;
extern s16 D_80047060;

#ifdef TARGET_PC
/* PC: the types of multiplyMatrix4x4's definition. The N64 declaration takes the two matrices as s32, which on PC
 * would cut their addresses in half. */
void multiplyMatrix4x4(f32 arg0[4][4], f32 arg1[4][4], f32 arg2[4][4]);
#else
void multiplyMatrix4x4(s32, s32, void *);
#endif
void guTranslateF(void *, s32, s32, f32);
void guMtxIdentF(void *);

/* Multiply matrix arg2 by arg1 into the D_80048288 scratch result; arg0 is
 * unused by this wrapper. */
#ifdef TARGET_PC
/* PC: the callers (func_80005304, setupTiltedPerspectiveCamera) pass the camera's record and two matrices. The N64
 * definition takes them as s32, as the N64 allows, and passes the matrices on; on PC an s32 would cut each address in
 * half, so the PC definition takes pointers (port_decls.h declares it so). */
void func_800014AC(void *arg0, f32 (*arg1)[4], f32 (*arg2)[4]) {
    (void)arg0; /* not used, as on the N64 */
    multiplyMatrix4x4(arg2, arg1, D_80048288);
}
#else
void func_800014AC(s32 arg0, s32 arg1, s32 arg2) {
    multiplyMatrix4x4(arg2, arg1, D_80048288);
}
#endif
