/* @header
 * func_800A6B2C
 * VRAM 0x800A6B2C | ROM 0x99FCC | size 0xB4
 * asm: asm/nonmatchings/code_8009D7A0/func_800A6B2C.s
 */
#include "common.h"

#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
extern s32 func_800D2B64(void *, f32, u16, s32);
#endif
extern void func_800D427C(void *, s32, s32);
extern void func_800A7188(void *);
extern u16 D_800FABE6;

/* Select the animation id from the D_800FABE6 flags (0x200/0x100/0x800/0x400 ->
 * 0x1344/0x1345/0x105F/0x1060, default 0x184F), start it and zero x, z and
 * heading; step 1 finishes the action when the animation ends. */
void func_800A6B2C(void) {
    Wrestler *p = D_800EB408;
    s16 step = p->step;

    switch (step) {
    case 0:
        {
            u16 flags = D_800FABE6;
            s32 id = 0x184F;

            p->x = 0;
            p->z = 0;
            p->heading = 0;
            if (flags & 0x200) {
                id = 0x1344;
            }
            if (flags & 0x100) {
                id = 0x1345;
            }
            if (flags & 0x800) {
                id = 0x105F;
            }
            if (flags & 0x400) {
                id = 0x1060;
            }
            func_800D427C(p, id, 0);
            D_800EB408->step++;
            break;
        }
    case 1:
        if (p->animFramesLeft <= 0) {
            func_800A6C48(p, 1);
        }
        break;
    }
}
