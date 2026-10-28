#include "common.h"

extern u16 D_8006A2A4[];
extern u8 D_80031060[];
extern s16 D_80030DD4[];

extern u8 D_8006A2A0[];
extern u8 D_800706A0[];
extern u8 D_80075458[];
extern u8 D_80075459[];
extern u8 D_8007545A[];
extern u8 D_8007545B[];

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
