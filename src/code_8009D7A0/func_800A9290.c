/* @header
 * func_800A9290
 * VRAM 0x800A9290 | ROM 0x9C730 | size 0xB8
 * asm: asm/nonmatchings/code_8009D7A0/func_800A9290.s
 */
#include "common.h"

extern s16 D_800E3270[];
extern s16 D_800E3262[];

void func_800D4AD0(Wrestler *);
s32 func_800D4CC4(Wrestler *);
void func_800D427C(Wrestler *, s16, s32);

/* If w's animId is in the list D_800E3270 (0-terminated), set WR_FLAG_RERUN. Otherwise apply the end of the
 * animation (func_800D4AD0: pose = anim.endPose, heading += anim.headingDelta, then func_800D4B10) and, when the
 * end pose is a down pose (func_800D4CC4: endPose >= 7, also sets/clears flag 0x200000 by its parity), start the
 * animation D_800E3262[anim.endPose] with mode 1. */
void func_800A9290(Wrestler *w) {
    s16 *tbl;
    s16 i;
    s16 v;
    s32 found;

    i = 0;
    tbl = D_800E3270;
loop:
    v = tbl[i];
    if (v == 0) {
        found = 0;
        goto test;
    }
    if (w->animId == v) found = 1;
    else {
        i += 1;
        goto loop;
    }
    i += 1;
test:
    if (found != 0) {
        w->flags |= WR_FLAG_RERUN;
        return;
    }
    func_800D4AD0(w);
    if ((func_800D4CC4(w) << 24) != 0) {
        func_800D427C(w, D_800E3262[w->anim.endPose], 1);
    }
}
