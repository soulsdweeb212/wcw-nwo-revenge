#include "common.h"

extern u8 D_8007EF30[];
extern u8 D_800FABE8[], D_800FABEC[], D_800FABEE[];
extern s16 D_800EB4D0[];
void func_800D2638(void *, u16, f32);
s32 func_800D2B64(void *, f32, u16, s32);

/* Per-entity timer for entity status 0x43: arg1==0 reloads 60, arg1==1 counts
 * down and clears the +0x43 status when it reaches zero. */
void updateEntityStatus43Timer(void *arg0, s16 arg1) {
    s16 *timer;
    s16 value;
    switch (arg1) {
    case 0:
        D_800EB4D0[*(s8 *)arg0] = 60;
        return;
    case 1:
        timer = &D_800EB4D0[*(s8 *)arg0];
        value = *timer;
        if (value <= 0) {
            *((s8 *)arg0 + 0x43) = 0;
            return;
        }
        *timer = value - 1;
        return;
    }
}
