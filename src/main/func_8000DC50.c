#include "common.h"

typedef struct {
    s16 e0[4];
    s8 e8[8];
} Nw2D50;

extern Nw2D50 D_800566E0;
extern s8 D_800566E8[];
extern u8 D_80065294[];
extern void func_8000D238(s32, s32);

/* Sets entity arg0's part-set to arg1 when the entity is not yet active: stores
 * the new set, clears its state byte and resets the entity's part flags (with
 * the 0x80 bit from D_80065294). Returns 1 when the entity is inactive. */
u32 func_8000DC50(s16 arg0, s16 arg1) {
    if (D_800566E8[arg0] < 0) {
        if ((s16)arg1 != D_800566E0.e0[arg0]) {
            D_800566E0.e0[arg0] = arg1;
            D_800566E0.e8[arg0] = 0;
            func_8000D238(arg0, D_80065294[arg0 * 0x13C4] | 0x80);
        }
    }
    return (u32)~D_800566E8[arg0] >> 31;
}
