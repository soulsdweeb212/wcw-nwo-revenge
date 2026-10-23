#include "common.h"

extern void *D_800FAF58, *D_800FABD0;
extern s16 D_800E3498[], D_800E34A0[];
s8 func_800D4198(s16); void func_800AD958(s32);
#define F(p,t,o) (*(t *)((u8 *)(p) + (o)))
/* Action gate for the actor D_800FAF58: if it lacks flag 0x100, index the
 * attachment byte +0x18 (divided by 3) and, when the D_800E34A0 threshold for
 * that index is below the action record D_800FABD0's +0x28 and the matching
 * D_800E3498 timer check passes, and the actor flag 0x80000, its attachment's
 * +0x38 flag 0x20000, or a 100-tick check holds, request action 0x2F. */
s32 func_800AB43C(void) {
    s8 index;
    if (!(F(D_800FAF58, u64, 0x20) & 0x100)) {
        index = F(F(D_800FAF58, void *, 0x364), s8, 0x18) / 3;
        if (D_800E34A0[index] < F(D_800FABD0, s16, 0x28) && func_800D4198(D_800E3498[index])) {
            if ((F(D_800FAF58, u64, 0x20) & 0x80000) || (F(F(D_800FAF58, void *, 0x364), u64, 0x38) & 0x20000) || func_800D4198(100)) {
                func_800AD958(0x2F); return 1;
            }
        }
    } return 0;
}
