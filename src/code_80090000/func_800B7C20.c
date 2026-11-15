/* @header
 * func_800B7C20
 * VRAM 0x800B7C20 | ROM 0x64390 | size 0x7C
 * asm: asm/nonmatchings/code_80090000/func_800B7C20.s
 */
#include "common.h"

typedef struct { f32 x; f32 y; } K;
typedef struct { K *p; s32 n; } L;
#ifdef TARGET_PC
/* PC: D_800D2530 is an array of 8-byte records on the N64 (the address of six curves L, two u16), which the N64 reads
 * here as one address: its first record's curves. On PC the records hold pointers, 16 bytes each, as
 * func_800B7F3C's and func_800B807C's views have them: the array is declared as theirs, and this file reads
 * D_800D2530[0].p. */
typedef struct { L *p; u16 a; u16 b; } P;
extern P D_800D2530[];
#else
extern L *D_800D2530;
#endif
extern s32 D_800DC8E0, D_800D28F0, D_800DC8E4, D_800D28F4;
extern f32 D_800DC930[];
extern s32 D_800DC918[];

void func_800B7C20(void) {
#ifdef TARGET_PC
    L *k = D_800D2530[0].p; /* PC: as above */
#else
    L *k = D_800D2530;
#endif
    s32 i = 0;
    D_800DC8E0 = 0;
    for (i = 0; i < 6; i++, k++) {
        D_800DC930[i] = k->p[k->n - 1].x;
        D_800DC918[i] = 0;
    }
    D_800D28F0 = 0x21;
    D_800DC8E4 = 0;
    D_800D28F4 = -1;
}
