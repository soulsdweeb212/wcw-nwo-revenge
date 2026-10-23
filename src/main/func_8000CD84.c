#include "common.h"

/* Release all resources for one slot (`index`). Frees the 23 buffered blocks
 * in D_8007C438[index*23..] (zeroing their D_8007C318 counts), resets the
 * per-slot counters D_8006A2A4/D_8007DFB0/D_8007DFBC/D_800566E0 to -1, copies
 * the 23 source strings (D_800651A0 -> D_80073EB0), tears down the slot's
 * effect record if active, resets the second block table and clears the
 * D_8007C3D0 slot. */
void releaseHeapBlock(void *);
void func_8000520C(void *, void *);
void func_80006E2C(void *);
void func_80007B08(void *);
void func_8000D718(void *, void *);
extern u8 D_80050800[], D_800517D0[], D_800651A0[], D_80070458[], D_80073EB0[], D_8007C3D0[];
extern s16 D_800566E0[], D_8006A2A4[], D_8007DFB0[], D_8007DFBC[];
extern s8 D_800706A4[];
extern u16 D_8007C318[];
extern void *D_8007C438[];
void func_8000CD84(s16 index) {
    u16 *count;
    u16 *cbase;
    void **buffer;
    void **bbase;
    u32 i;
    u8 *src, *dst;
    u32 off;
    i = 0;
    off = (s16)index * 23;
    cbase = D_8007C318;
    count = cbase + off;
    bbase = D_8007C438;
    buffer = bbase + off;
    D_8006A2A4[index] = -1;
    D_8007DFBC[index] = -1;
    D_8007DFB0[index] = -1;
    D_800566E0[index] = -1;
    do {
        if (*buffer) { releaseHeapBlock(*buffer); *buffer = 0; *count = 0; }
        count++; i++; buffer++;
    } while (i < 23);
    i = 0;
    dst = D_80073EB0 + index * 0x3F4;
    src = D_800651A0 + index * 0x13C4;
    do { func_8000520C(src, dst); dst += 0x2C; i++; src += 0xDC; } while (i < 23);
    if (D_800706A4[index] == 1) func_80006E2C(D_80070458 + index * 8);
    func_8000D718(D_800517D0 + index * 0x13C4, D_80050800 + index * 0x3F4);
    func_80007B08(D_8007C3D0 + index * 16);
}
