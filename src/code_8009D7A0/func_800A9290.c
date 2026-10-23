#include "common.h"

extern s16 D_800E3270[];
extern s16 D_800E3262[];

void func_800D4AD0(void *);
s32 func_800D4CC4(void *);
void func_800D427C(void *, s16, s32);

/* If the entity's action id (+0x8) is in D_800E3270, set the "done" flag bit
 * 0x10000000. Otherwise complete the action and, if the completion check
 * passes, play the per-slot animation from D_800E3262. */
void func_800A9290(void *arg0) {
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
    if (*(s16 *)((u8 *)arg0 + 8) == v) found = 1;
    else {
        i += 1;
        goto loop;
    }
    i += 1;
test:
    if (found != 0) {
        *(u64 *)((u8 *)arg0 + 0x20) |= 0x10000000ULL;
        return;
    }
    func_800D4AD0(arg0);
    if ((func_800D4CC4(arg0) << 24) != 0) {
        func_800D427C(arg0, D_800E3262[*(u8 *)((u8 *)arg0 + 0x36F)], 1);
    }
}
