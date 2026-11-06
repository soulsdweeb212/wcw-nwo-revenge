/* @header
 * func_800A9208
 * VRAM 0x800A9208 | ROM 0x9C6A8 | size 0x88
 * asm: asm/nonmatchings/code_8009D7A0/func_800A9208.s
 */
#include "common.h"

extern s16 D_800E3270[];
extern s16 D_800E3262[];
extern u8 D_80064AD8[];

s32 func_800D35B0(s32, s32);
void func_800D4AD0(void *);
u8 func_800D4CC4(void *);
void func_800D427C(void *, s16, s32);

/* Returns 1 when w's animId is one of the animations listed in D_800E3270 (0-terminated); then *outHeading (if
 * not NULL) gets heading + anim.headingDelta, wrapped (the facing after the animation's built-in turn).
 * Otherwise returns 0 and *outHeading gets the plain heading. */
s32 func_800A9208(Wrestler *w, s32 *outHeading) {
    s16 v;
    s16 i = 0;

    do {
        v = D_800E3270[i];
        if (v == 0) {
            if (outHeading != NULL) {
                *outHeading = w->heading;
            }
            return 0;
        }
        if (w->animId == v) {
            if (outHeading != NULL) {
                *outHeading = func_800D35B0(w->heading, w->anim.headingDelta);
            }
            return 1;
        }
        i++;
    } while (1);
}
