/* @header
 * setupTiltedPerspectiveCamera  (originally func_80005428)
 * VRAM 0x80005428 | ROM 0x6028 | size 0x184
 * asm: asm/nonmatchings/main/setupTiltedPerspectiveCamera.s
 */
#include "common.h"

extern f32 D_80048500[4][4],D_80048540[4][4];
extern f32 D_80048580,D_80048584,D_80048588;
void guPerspectiveF(void *,u16 *,f32,f32,f32,f32,f32);
void guLookAtF(void *,f32,f32,f32,f32,f32,f32,f32,f32,f32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800014AC and func_800014D0 */
void func_800014AC(s32,void *,void *);
void func_800014D0(s32,u16);
#endif
f32 func_80003A3C(f32,f32);
f32 sinf(f32);
f32 cosf(f32);
/* Sets up camera `id` as a tilted perspective view looking from (x,y,z) toward
 * (tx,ty,tz): builds the projection matrix into D_80048500, derives the up
 * vector from the view heading and tilt angle, builds the view matrix into
 * D_80048540, and hands both (plus the projection norm word) to the camera. */
#ifdef TARGET_PC
/* PC: id is the camera's record (func_8009A374 passes &D_800EB360[D_800E2FA8]), which this function only passes on
 * to func_800014AC and func_800014D0. The N64 definition takes it as an s32, which on PC would cut the address in
 * half, so the PC definition takes a pointer (port_decls.h declares it so). */
void setupTiltedPerspectiveCamera(void *id, f32 tilt, f32 x, f32 y, f32 z, f32 tx, f32 ty, f32 tz) {
#else
void setupTiltedPerspectiveCamera(s32 id,f32 tilt,f32 x,f32 y,f32 z,f32 tx,f32 ty,f32 tz) {
#endif
    u16 norm;
    f32 heading,sine,ux,uz;
    heading=func_80003A3C(x-tx,tz-z);
    sine=sinf(tilt);
    ux=sine*cosf(heading);
    uz=sine*sinf(heading);
    sine=cosf(tilt);
    D_80048580=x;D_80048584=y;D_80048588=z;
    guPerspectiveF(D_80048500,&norm,33.0f,1.3333334f,100.0f,4000.0f,1.0f);
    guLookAtF(D_80048540,x,y,z,tx,ty,tz,ux,sine,uz);
    func_800014AC(id,D_80048500,D_80048540);
    func_800014D0(id,norm);
}
