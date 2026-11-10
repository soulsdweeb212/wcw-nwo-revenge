/* @header
 * func_800A47C4
 * VRAM 0x800A47C4 | ROM 0x97C64 | size 0xA0
 * asm: asm/nonmatchings/code_8009D7A0/func_800A47C4.s
 */
#include "common.h"

#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
extern s32 func_800D2B64(void *, f32, u16, s32);
#endif
extern void func_800D427C(void *, s32, s32);
extern void func_800A7188(void *);

/* Two-step action on the wrestler D_800EB408. Sets flag 0x1000000000, then:
 * step 0 plays animation 0xEBD and advances to step 1; step 1 runs the
 * movement update (mask 0xFFFFE, speed 1.0) and hands off to func_800A7188. */
void func_800A47C4(void) {
    Wrestler *p = D_800EB408;
    s16 phase;

    p->flags |= 0x1000000000ULL;
    phase = p->step;
    switch (phase) {
    case 0:
        func_800D427C(p, 0xEBD, 3);
        D_800EB408->step++;
        break;
    case 1:
        func_800D2B64(p, 1.0f, 0, 0xFFFFE);
        func_800A7188(D_800EB408);
        break;
    }
}
