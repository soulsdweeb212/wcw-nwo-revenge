/* @header
 * func_800A553C
 * VRAM 0x800A553C | ROM 0x989DC | size 0x1F0
 * asm: asm/nonmatchings/code_8009D7A0/func_800A553C.s
 */
#include "common.h"

/* Three-stage item/weapon action driver on self record D_800EB408:
 * 0) spawn via func_800CE124 and arm a sub-mode from grappleCtx,
 * 1) wait for func_800CE2C8 to signal completion,
 * 2) run the 4-frame hit window, add the second attacker's move.spiritGainSelf
 *    to self's health on the last frame and clear the action when it ends. */
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800CE124(void *, void *, void *);
s32 func_800CE2C8(void *, void *, void *, void *, void *);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *, s16);
#endif
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
void addEntityHealthDelta(void *, s32);
extern u8 D_800F9B18[];
extern s8 D_800FABE4;
extern s8 D_800FADB8;

void func_800A553C(void) {
    s16 step;
    s16 mode;
    u32 flags;

    step = D_800EB408->step;
    switch (step) {
    case 0:
        func_800CE124(D_800EB408, D_800EB40C, D_800F9B18 + D_800FADB8 * 16);
        flags = D_800EB408->grappleCtx;
        if (flags & 0x1800) {
            mode = (flags >> 14) & 1;
        }
        if (flags & 0x2000) {
            mode = (flags >> 6) & 1;
        }
        func_800D427C(D_800EB408, func_800D5438(D_800EB418, mode), 2);
        func_800A7F6C(D_800EB408, 0x41);
        func_800A837C(D_800EB408);
        D_800EB408->step++;
    case 1:
        if ((s8)func_800CE2C8(D_800EB408, D_800EB40C, D_800EB418,
                D_800F9B18 + D_800FADB8 * 16, D_800F9B18 + D_800FABE4 * 16)) {
            D_800EB408->step++;
        }
        break;
    case 2:
        func_800D2BEC(D_800EB408, D_800EB40C, D_800EB418, 4.0f, 0, 0xFFFFE);
        if (D_800EB408->animFramesLeft == 1) {
            addEntityHealthDelta(D_800EB408, D_800EB418->move.spiritGainSelf);
        }
        if (D_800EB408->animFramesLeft <= 0) {
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
