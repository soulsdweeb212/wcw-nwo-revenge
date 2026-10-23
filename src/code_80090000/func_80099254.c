#include "common.h"

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s16 fC;
    s16 fE;
    s32 f10;
} Entry9903C;

extern Entry9903C D_800E7CE0[0x40];

extern s32 func_80098EEC(Entry9903C *, s32);

s32 func_80099254(s32 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4) {
    Entry9903C *e;
    s32 i;
    s32 j;
    s32 key;
    s32 r;

    key = (arg0 & 0xFFF) | 0x08000000;
    if ((key & 0xF0000000) == 0) {
        key |= 0x10000000;
    }

    if (arg4 & 0x8000) {
        for (i = 0, e = D_800E7CE0; i < 0x40; i++, e++) {
            if (e->f8 == key) {
                goto write;
            }
        }
        for (i = 0, e = D_800E7CE0; i < 0x40; i++, e++) {
            if (e->f8 == 0) {
                e->f8 = key;
                goto write;
            }
        }
        e = 0;
        goto done;

    write:
        e->f10 = arg3;
        e->fC = arg1;
        e->fE = arg2;
        goto done;
    }

    for (j = 0, e = D_800E7CE0; j < 0x40; j++, e++) {
        if (e->f8 == key && e->f10 == arg3) {
            e->fC = arg1;
            e->fE = arg2;
            goto done;
        }
    }
    for (j = 0, e = D_800E7CE0; j < 0x40; j++, e++) {
        if (e->f8 == 0) {
            e->f8 = key;
            goto write;
        }
    }
    e = 0;

done:
    r = 0;
    if (e != 0) {
        r = func_80098EEC(e, arg4);
    }
    return r;
}
