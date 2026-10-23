#include "common.h"

/* Releases the Controller Pak page chain starting at (arg3,arg2) in the inode
 * table arg1, marking each page free (3) until the bank changes, tracking the
 * last page in *arg4. */
s32 __osPfsReleasePages(void *arg0, u16 *arg1, s32 arg2, s32 arg3, u16 *arg4) {
    u32 v;
    u16 c;
    s32 k;

    v = (arg3 << 8) | (arg2 & 0xFF);
    k = arg3 & 0xFF;
    do {
        c = arg1[v & 0xFF];
        arg1[v & 0xFF] = 3;
        if ((s32)c < *(s32 *)((u8 *)arg0 + 0x60)) {
            *arg4 = c;
            return 0;
        }
        v = c;
    } while ((c >> 8) == k);
    *arg4 = c;
    return 0;
}

typedef struct {
    u8 b[6];
} Nw2Six;

extern s32 D_8007E00C[];

/* Builds the command buffer for controller channel arg1: fills arg0 entries with
 * the read request record and a 0xFE terminator. */
void func_80024730(s32 arg0, u8 arg1) {
    s32 *base;
    u8 *p;
    u8 buf[16];
    s32 i;

    base = D_8007E00C;
    p = (u8 *)base - 0x3C;
    i = 0;
    D_8007BD30 = 0xFE;
    base[0] = 1;
    buf[0] = 1;
    buf[1] = 3;
    buf[2] = arg1;
    buf[3] = 0xFF;
    buf[4] = 0xFF;
    buf[5] = 0xFF;
    if (arg0 > 0) {
        do {
            *p = 0;
            i++;
            p++;
        } while (i < arg0);
    }
    *(Nw2Six *)p = *(Nw2Six *)buf;
    p[6] = 0xFE;
}

extern u8 D_8007DFD0[];

/* Decodes the arg0-th controller response into arg1 (error nibble and, for a
 * good entry, the payload). */
void func_800247C4(s32 arg0, u8 *arg1) {
    u8 buf[16];
    u8 *p;
    s32 i;
    u32 v;

    p = D_8007DFD0;
    i = 0;
    if (arg0 > 0) {
        do {
            i++;
            p++;
        } while (i < arg0);
    }
    *(Nw2Six *)buf = *(Nw2Six *)p;
    v = (buf[1] & 0xC0) >> 4;
    arg1[3] = v;
    if (v == 0) {
        *(u16 *)arg1 = buf[3] | (buf[4] << 8);
        arg1[2] = buf[5];
    }
}

extern Nw2IdSubTable lookupSubTables[];

/* Finds entry id arg0 across the first 11 lookup subtables, returning the
 * (subtable<<8)|index key or -1. */
s32 func_8002AC00(s32 arg0) {
    s32 g;
    s32 i;

    for (g = 0; g < 0xB; g++) {
        for (i = 0; i < lookupSubTables[g].count; i++) {
            if (lookupSubTables[g].entries[i]->id == arg0) {
                return (g << 8) + i;
            }
        }
    }
    return -1;
}
