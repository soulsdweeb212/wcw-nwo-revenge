#include "common.h"

extern u16 D_8006A2A4[];
extern u8 D_80031060[];
extern s16 D_80030DD4[];

/* Resolves the sound id for anim arg0 / channel arg1 through the two-level
 * D_8006A2A4 / D_80031060 / D_80030DD4 tables. */
s16 func_8000E4FC(s16 arg0, s16 arg1) {
    u16 v;
    s32 idx;
    s16 *p;

    v = D_8006A2A4[arg0];
    idx = ((v & 0x1F) - 1) * 2;
    p = *(s16 **)(D_80031060 + ((v >> 6) & 0x7C));
    return D_80030DD4[p[idx + arg1]];
}

extern u8 D_8006A2A0[];
extern u8 D_800706A0[];
extern u8 D_80075458[];
extern u8 D_80075459[];
extern u8 D_8007545A[];
extern u8 D_8007545B[];

/* Clears the four per-entity sound descriptor/slot bytes and their enable
 * flags. */
void func_8000E644(void) {
    u32 i;
    u32 j;

    for (i = 0, j = 0; i < 4; i++, j += 4) {
        D_80075458[j] = 0;
        D_80075459[j] = 0;
        D_8007545A[j] = 0;
        D_8007545B[j] = 0;
        D_8006A2A0[i] = 0;
        D_800706A0[i] = 0;
    }
}

void func_800043CC(s16);

/* Clears the four per-entity sound descriptor bytes and reloads each entity's
 * descriptor. */
void func_8000E6AC(void) {
    s32 i;
    u32 j;

    for (i = 0, j = 0; i < 4U; i++, j += 4) {
        D_80075458[j] = 0;
        D_80075459[j] = 0;
        D_8007545A[j] = 0;
        D_8007545B[j] = 0;
        func_800043CC(i);
    }
}

extern u16 D_800306A0[];
s32 func_800032A4(s32, s32, s32, s32, s32);
void func_80013F7C(s32, s32);

/* Plays sound arg0 (remapped through D_800306A0 for ids 0x401..0x42B) if it is
 * in range, and returns the voice handle. */
s32 func_8000DEE4(s32 arg0) {
    s32 ret;
    s32 t;
    s16 x;

    ret = 0;
    t = arg0;
    if ((u16)(arg0 - 0x401) < 0x2B) {
        x = D_800306A0[(s16)arg0];
    } else {
        x = t;
    }
    if (x >= 0 && x < 0x97) {
        ret = func_800032A4(x, 0x80, 0x80, 0, -1);
        func_80013F7C(ret, 0);
    }
    return ret;
}
