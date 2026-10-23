#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800FAF58;
extern s16 D_800E3658[];
extern f64 D_800E4E68;
extern f64 D_800E4E70;
s8 func_800D4198(s16);
void func_800AD958(s32);

/* High-threshold action variant: when the record's f34 exceeds D_800E4E68,
 * pick action 0x1A if it also exceeds D_800E4E70 and the random check on the
 * target attachment's +0x18/3 entry passes, otherwise pick 0x19. Returns 0 if
 * f34 is below the first threshold. */
s32 func_800ABFF8(void) {
    s8 b;
    s8 i;
    if (D_800E4E68 < (f64)*(f32 *)(D_800FABD0 + 0x34)) {
        if (D_800E4E70 < (f64)*(f32 *)(D_800FABD0 + 0x34)) {
            b = *(u8 *)(*(u32 *)(D_800FAF58 + 0x364) + 0x18);
            i = b / 3;
            if (func_800D4198(D_800E3658[i]) != 0) {
                func_800AD958(0x1A);
                return 1;
            }
        }
        func_800AD958(0x19);
        return 1;
    }
    return 0;
}
