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

typedef struct {
    s8 f0;
    u8 pad1[9];
    s16 fA;
    u8 padC[0x14];
    u64 flags;
    u8 pad28[4];
    u32 f2C;
} Nw2Ent560;

extern Nw2Action560 *D_800FABD0;
extern Nw2Ent560 *D_800F9B60;
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
 * random check passes and the target is in sub-state 0x44 with flag bit 2 set,
 * use D_800E351C, else D_800E3504. */
void func_800AB560(void)
{
    f64 v = (f64)D_800FABD0->f34;

    if (D_800E4DE8 < v) {
        func_800ADA38(D_800E34A8);
    } else if (D_800E4DF0 < v) {
        func_800ADA38(D_800E34CC);
    } else if (func_800D4198((s16)(s32)((f64)D_800FABD0->f12 * D_800E4DF8)) &&
               D_800F9B60->fA == 0x44 &&
               (D_800F9B60->f2C & 2)) {
        func_800ADA38(D_800E351C);
    } else {
        func_800ADA38(D_800E3504);
    }
}
