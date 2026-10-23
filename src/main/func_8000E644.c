#include "common.h"

extern u8 D_80075458[];
extern u8 D_80075459[];
extern u8 D_8007545A[];
extern u8 D_8007545B[];
extern u8 D_8006A2A0[];
extern u8 D_800706A0[];

/* Clears the four per-entity sound descriptor/slot bytes and their enable
 * flags. */
void func_8000E644(void) {
    u32 i, j;

    for (i = 0, j = 0; i < 4; j += 4, i++) {
        D_80075458[j] = 0;
        D_80075459[j] = 0;
        D_8007545A[j] = 0;
        D_8007545B[j] = 0;
        D_8006A2A0[i] = 0;
        D_800706A0[i] = 0;
    }
}
