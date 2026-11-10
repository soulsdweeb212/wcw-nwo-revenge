/* @header
 * func_8009A714
 * VRAM 0x8009A714 | ROM 0x8DBB4 | size 0x48
 * asm: asm/nonmatchings/ovl2_80090000/func_8009A714.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_800EB37C is the camera eye's x, y and z, and D_800EB388 the camera target's, which func_80099F70,
 * func_8009A374 and func_8009AAC8 declare as f32[3]. The N64 code below writes y and z through names of their own,
 * D_800EB380/D_800EB384 (D_800EB37C[1] and [2]) and D_800EB38C/D_800EB390 (D_800EB388[1] and [2]), which are the
 * same memory only where the data is laid out as on the N64. The PC definition writes the elements of the two arrays
 * instead, so the values reach the arrays however the port lays that data out. */
extern f32 D_800EB37C[3];
extern f32 D_800EB388[3];
#else
extern f32 D_800EB37C;
extern f32 D_800EB380;
extern f32 D_800EB384;
extern s32 D_800EB388;
extern f32 D_800EB38C;
extern f32 D_800EB390;
#endif

#ifdef TARGET_PC
/* PC: the caller (func_80099F70) passes six floats. On the N64 the fourth travels in a3, an integer register, where
 * the N64 definition takes it as an s32 and stores its bits into D_800EB388; on PC a float travels in a float
 * register, so the PC definition takes it as the f32 (port_decls.h declares it so). It stores the six values into
 * the two arrays, as above. */
void func_8009A714(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    D_800EB37C[0] = arg0;
    D_800EB37C[1] = arg1;
    D_800EB37C[2] = -arg2;
    D_800EB388[0] = arg3;
    D_800EB388[1] = arg4;
    D_800EB388[2] = -arg5;
}
#else
void func_8009A714(f32 arg0, f32 arg1, f32 arg2, s32 arg3, f32 arg4, f32 arg5) {
    D_800EB37C = arg0;
    D_800EB380 = arg1;
    D_800EB388 = arg3;
    D_800EB384 = -arg2;
    D_800EB38C = arg4;
    D_800EB390 = -arg5;
}
#endif
