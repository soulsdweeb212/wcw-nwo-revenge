/* @header
 * findOrAddCacheEntryRaw  (originally func_8009903C)
 * VRAM 0x8009903C | ROM 0x457AC | size 0x10C
 * asm: asm/nonmatchings/code_80090000/func_8009903C.s
 */
#include "common.h"

typedef struct {
    s32 f0;
    s32 f4;
    s32 key;      /* @0x8: 0 = free slot */
    s16 fieldC;   /* @0xC */
    s16 fieldE;   /* @0xE */
    s32 match;    /* @0x10 */
} Entry9903C;

extern Entry9903C D_800E7CE0[0x40];

extern s32 func_80098EEC(Entry9903C *, s32);

/* Cache-slot lookup/allocate variant that uses arg0 directly as the key (the
 * sibling func_80099364 tags the key with 0xC0000000). With flag 0x8000, reuse
 * the entry already holding the key, else a free one; without it, reuse an
 * entry whose key and match value agree, else a free one. Returns 0 if no entry
 * could be used. */
s32 findOrAddCacheEntryRaw(s32 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4) {
    Entry9903C *e;
    s32 i;
    s32 j;
    s32 key;
    s32 r;

    key = arg0;
    if ((key & 0xF0000000) == 0) {
        key |= 0x10000000;
    }

    if (arg4 & 0x8000) {
        for (i = 0, e = D_800E7CE0; i < 0x40; i++, e++) {
            if (e->key == key) {
                goto write;
            }
        }
        for (i = 0, e = D_800E7CE0; i < 0x40; i++, e++) {
            if (e->key == 0) {
                e->key = key;
                goto write;
            }
        }
        e = 0;
        goto done;

    write:
        e->match = arg3;
        e->fieldC = arg1;
        e->fieldE = arg2;
        goto done;
    }

    for (j = 0, e = D_800E7CE0; j < 0x40; j++, e++) {
        if (e->key == key && e->match == arg3) {
            e->fieldC = arg1;
            e->fieldE = arg2;
            goto done;
        }
    }
    for (j = 0, e = D_800E7CE0; j < 0x40; j++, e++) {
        if (e->key == 0) {
            e->key = key;
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
