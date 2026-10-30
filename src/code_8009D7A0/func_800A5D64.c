/* @header
 * func_800A5D64
 * VRAM 0x800A5D64 | ROM 0x99204 | size 0x128
 * asm: asm/nonmatchings/code_8009D7A0/func_800A5D64.s
 */
#include "common.h"

s32 beginEntityActionA8D8C(void *);
s32 func_800C472C(void *, void *, s32);
s32 func_800D427C(void *, s16, s32);
s32 func_800D4AD0(void *);
s16 func_800D5438(void *, s32);
s32 func_800D7E80(void *, void *);
s32 func_800D8D74(void *, s32);
extern void *D_800EB408;
extern void *D_800EB40C;

/* Two-state action machine for the D_800EB408 object, driven by D_800EB40C's
 * +0x2C bit 0x04000000:
 *   0: pick animation func_800D5438(D_800EB40C,1) and start it (arg 3 when the
 *      bit is set, else arg 2 plus a func_800D7E80 handoff), then advance.
 *   1: while the bit is clear, stop the sub-action; once the +0x4 timer reaches
 *      zero, end the action, queue the follow-up and notify D_800EB40C. */
void func_800A5D64(void) {
    s16 state;

    state = *(s16 *)((u8 *)D_800EB408 + 0xC);
    switch (state) {
    case 0:
        if (*(s32 *)((u8 *)D_800EB40C + 0x2C) & 0x04000000) {
            func_800D427C(D_800EB408, func_800D5438(D_800EB40C, 1), 3);
        } else {
            func_800D427C(D_800EB408, func_800D5438(D_800EB40C, 1), 2);
            func_800D7E80(D_800EB408, D_800EB40C);
        }
        *(s16 *)((u8 *)D_800EB408 + 0xC) = (s16)((u16)*(s16 *)((u8 *)D_800EB408 + 0xC) + 1);
        return;
    case 1:
        if (!(*(s32 *)((u8 *)D_800EB40C + 0x2C) & 0x04000000)) {
            func_800D8D74(D_800EB408, 0);
        }
        if (*(s16 *)((u8 *)D_800EB408 + 4) <= 0) {
            func_800D4AD0(D_800EB408);
            beginEntityActionA8D8C(D_800EB408);
            func_800C472C(D_800EB40C, D_800EB408, 2);
        }
        return;
    }
}
