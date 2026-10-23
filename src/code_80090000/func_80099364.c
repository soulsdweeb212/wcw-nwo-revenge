#include "common.h"

typedef struct {
    s32 f0, f4;
    s32 key;      /* @0x8: 0 = free slot */
    s16 fieldC;   /* @0xC */
    s16 fieldE;   /* @0xE */
    s32 match;    /* @0x10 */
} Entry99364;

extern Entry99364 D_800E7CE0[0x40];
s32 func_80098EEC(Entry99364 *, s32);

/* Look up (or allocate) one of 0x40 cache entries by a key derived from id.
 * With flag 0x8000, reuse the entry already holding the key, else a free one.
 * Without it, reuse an entry whose key and match value agree, else a free one.
 * When an entry is found its fields are filled in and func_80098EEC is called;
 * returns 0 if no entry could be used. */
s32 func_80099364(s32 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4) {
    Entry99364 *e;
    s32 i, j, key, r;
    key = (arg0 & 0x0FFFFFFF) | 0xC0000000;
    if ((key & 0xF0000000) == 0) key |= 0x10000000;
    if (arg4 & 0x8000) {
        for (i = 0, e = D_800E7CE0; i < 0x40; i++, e++) if (e->key == key) goto write;
        for (i = 0, e = D_800E7CE0; i < 0x40; i++, e++) if (e->key == 0) { e->key = key; goto write; }
        e = 0; goto done;
    write:
        e->match = arg3; e->fieldC = arg1; e->fieldE = arg2; goto done;
    }
    for (j = 0, e = D_800E7CE0; j < 0x40; j++, e++) if (e->key == key && e->match == arg3) { e->fieldC = arg1; e->fieldE = arg2; goto done; }
    for (j = 0, e = D_800E7CE0; j < 0x40; j++, e++) if (e->key == 0) { e->key = key; goto write; }
    e = 0;
done:
    r = 0;
    if (e != 0) r = func_80098EEC(e, arg4);
    return r;
}
