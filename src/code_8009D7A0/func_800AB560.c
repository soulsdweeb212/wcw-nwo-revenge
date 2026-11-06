/* @header
 * func_800AB560
 * VRAM 0x800AB560 | ROM 0x9EA00 | size 0xEC
 * asm: asm/nonmatchings/code_8009D7A0/func_800AB560.s
 */
#include "common.h"

typedef struct {
    u8 pad0[0x12];
    s16 f12;
    u8 pad14[0xE];
    s16 f22;
    u8 pad24[0x10];
    f32 f34;
    u8 pad38[4];
    f32 f3C;
} Nw2Action560;

extern Nw2Action560 *D_800FABD0;
extern f64 D_800E4DE8;
extern f64 D_800E4DF0;
extern f64 D_800E4DF8;
extern s8 D_800E34A8[];
extern s8 D_800E34CC[];
extern s8 D_800E3504[];
extern s8 D_800E351C[];
void func_800ADA38(s8 *);
s8 func_800D4198(s16);

/* Pick an action parameter set for D_800FABD0 by its f34 range: above
 * D_800E4DE8 -> D_800E34A8, above D_800E4DF0 -> D_800E34CC; otherwise, when the
 * random check passes and the opponent is in state 0x44 with grappleCtx bit 2 set,
 * use D_800E351C, else D_800E3504. */
void func_800AB560(void)
{
    f64 v = (f64)D_800FABD0->f34;

    if (D_800E4DE8 < v) {
        func_800ADA38(D_800E34A8);
    } else if (D_800E4DF0 < v) {
        func_800ADA38(D_800E34CC);
    } else if (func_800D4198((s16)(s32)((f64)D_800FABD0->f12 * D_800E4DF8)) &&
               D_800F9B60->state == 0x44 &&
               (D_800F9B60->grappleCtx & 2)) {
        func_800ADA38(D_800E351C);
    } else {
        func_800ADA38(D_800E3504);
    }
}
