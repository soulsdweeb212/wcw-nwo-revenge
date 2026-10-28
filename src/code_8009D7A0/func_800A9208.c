#include "common.h"

extern s16 D_800E3270[];
extern s16 D_800E3262[];
extern u8 D_80064AD8[];

s32 func_800D35B0(s32, s32);
void func_800D4AD0(void *);
u8 func_800D4CC4(void *);
void func_800D427C(void *, s16, s32);

/* Returns 1 when the entity's state (+8) is one of the D_800E3270 states,
 * optionally returning the adjusted heading in *arg1. */
s32 func_800A9208(void *arg0, s32 *arg1) {
    s16 v;
    s16 i = 0;

    do {
        v = D_800E3270[i];
        if (v == 0) {
            if (arg1 != NULL) {
                *arg1 = *(s32 *)((u8 *)arg0 + 0x58);
            }
            return 0;
        }
        if (*(s16 *)((u8 *)arg0 + 8) == v) {
            if (arg1 != NULL) {
                *arg1 = func_800D35B0(*(s32 *)((u8 *)arg0 + 0x58), *(s32 *)((u8 *)arg0 + 0x368));
            }
            return 1;
        }
        i++;
    } while (1);
}
