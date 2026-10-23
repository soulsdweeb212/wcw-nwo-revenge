#include "common.h"

extern s16 D_800E74DC;
extern s16 D_800E7C88;

extern u8 updateEntityReactionState[];
u8 *func_80028B5C(u8 *, u8 *);
u8 *func_80028D18(s32, s32);

extern void *D_800E7518;
extern u8 D_800E7CE0[];
extern u8 D_800E7CE4[];
extern u8 D_800E7CE8[];
extern u8 D_800E7CF0[];
extern s32 D_800E7BE8;
extern s32 D_800E7BEC;
extern s32 D_800E8220;

void *allocateHeap(s32);

/* Returns the count associated with arg0 (0: D_800E74DC, else D_800E7C88). */
s16 func_80096A48(s32 arg0) {
    if (arg0 == 0) {
        return D_800E74DC;
    }
    return D_800E7C88;
}

/* Allocates and clears the 0x480-byte priority/resource request table and
 * initializes the 64 resource-cache entries. */
void func_80098E1C(void) {
    u8 *p;
    u8 *next;
    s32 i;
    s32 off;

    p = allocateHeap(0x480);
    i = 0x5F;
    D_800E7518 = p;
    p += 0x474;
    do {
        *(s32 *)p = 0;
        i -= 1;
        p -= 0xC;
    } while (i >= 0);
    next = D_800E7CE8;
    off = 0;
    i = 0;
    do {
        *(u8 **)(D_800E7CE0 + off) = next;
        next += 0x14;
        *(s32 *)(D_800E7CE4 + off) = 1;
        *(s32 *)(D_800E7CE8 + off) = 0;
        *(s32 *)(D_800E7CF0 + off) = 0;
        i += 1;
        off += 0x14;
    } while (i < 0x40);
    D_800E7BEC = 0;
    D_800E7BE8 = 0;
    D_800E8220 = 0;
}

/* Looks up (or builds) the name string for entity arg0, prefixed with the
 * default string; returns the default string when the id is empty or the lookup
 * fails. */
u8 *func_80099568(u8 *arg0) {
    u8 *r;
    u8 *p;

    if (*arg0 == 0) {
        return updateEntityReactionState + 0x64;
    }
    r = func_80028D18(arg0, 3);
    if (r == NULL) {
        return updateEntityReactionState + 0x64;
    }
    if (*r == 0) {
        p = func_80028B5C(r, updateEntityReactionState + 0x1F4);
        p = func_80028B5C(p, arg0);
        *p = 0;
    }
    return r;
}
