/* @header
 * findOrAddCacheEntryRaw  (originally func_8009903C)
 * VRAM 0x8009903C | ROM 0x457AC | size 0x10C
 * asm: asm/nonmatchings/code_80090000/findOrAddCacheEntryRaw.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the key is a MenuKey (port.h): a number, which gets the tag 0x10000000 when its top four bits are 0 as on the
 * N64, or a key of the resource-name cache (a name's address, or MENU_KEY_ID), which the N64 tells apart by its top
 * bits and the PC by MENU_KEY_IS_RES, and which is stored as it is. D_800E7CE0 is 0x40 of common.h's Nw2MenuPicSlot
 * (port_decls.h): the picture's fields by name, and the request's key is the entry's picture list, whose address
 * func_80098EEC takes as a pointer (the N64 passes the entry's address, where its list lies). */
s32 findOrAddCacheEntryRaw(MenuKey arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4) {
    Nw2MenuPicSlot *e;
    s32 i;
    s32 j;
    MenuKey key;
    s32 r;

    key = arg0;
    if (!MENU_KEY_IS_RES(key) && (key & 0xF0000000) == 0) {
        key |= 0x10000000;
    }

    if (arg4 & 0x8000) {
        for (i = 0, e = D_800E7CE0; i < 0x40; i++, e++) {
            if (e->pic.key == key) {
                goto write;
            }
        }
        for (i = 0, e = D_800E7CE0; i < 0x40; i++, e++) {
            if (e->pic.key == 0) {
                e->pic.key = key;
                goto write;
            }
        }
        e = NULL;
        goto done;

write:
        e->pic.match = arg3;
        e->pic.x = arg1;
        e->pic.y = arg2;
        goto done;
    }

    for (j = 0, e = D_800E7CE0; j < 0x40; j++, e++) {
        if (e->pic.key == key && e->pic.match == arg3) {
            e->pic.x = arg1;
            e->pic.y = arg2;
            goto done;
        }
    }
    for (j = 0, e = D_800E7CE0; j < 0x40; j++, e++) {
        if (e->pic.key == 0) {
            e->pic.key = key;
            goto write;
        }
    }
    e = NULL;

done:
    r = 0;
    if (e != NULL) {
        r = func_80098EEC(&e->list, arg4);
    }
    return r;
}
#else
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
#endif
