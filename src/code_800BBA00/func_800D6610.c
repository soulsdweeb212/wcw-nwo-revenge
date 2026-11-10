/* @header
 * func_800D6610
 * VRAM 0x800D6610 | ROM 0xC9AB0 | size 0x48
 * asm: asm/nonmatchings/code_800BBA00/func_800D6610.s
 */
#include "common.h"

extern s32 D_800FABD8;
extern u16 D_800E3F84[];
extern u16 D_800E3F8C[];
extern u8 D_80030560[];
extern u8 D_8007C438[];

typedef struct { f32 x; f32 y; } Nw2Vec2C50;
extern Nw2Vec2C50 D_800E3C50[];

#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D36E8, with the s32 heading it returns */
extern void func_800D36E8(f32, f32);
#endif

/* Compute the heading from the wrestler's pelvis (jointA[1] x/z) toward the X/Z
 * point D_800E3C50[arg1] (callers pass dirIndex). Declared void, but callers
 * use the heading func_800D36E8 leaves in v0. */
#ifdef TARGET_PC
/* PC: the callers use a result (resolveEntityMoveHeading and func_8009E624 declare s32 func_800D6610(void *, s16)).
 * On the N64 it is the heading that func_800D36E8 leaves in v0, which this function, declared void, does not touch;
 * on PC it is returned. */
s32 func_800D6610(Wrestler *w, s32 arg1) {
    s32 i = (s16)arg1;

    return func_800D36E8(D_800E3C50[i].x - w->jointA[1].x,
                         D_800E3C50[i].y - w->jointA[1].z);
}
#else
void func_800D6610(Wrestler *w, s32 arg1) {
    s32 i = (s16)arg1;

    func_800D36E8(D_800E3C50[i].x - w->jointA[1].x,
                  D_800E3C50[i].y - w->jointA[1].z);
}
#endif
