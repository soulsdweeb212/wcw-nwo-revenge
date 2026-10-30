/* @header
 * func_8000E8A0
 * VRAM 0x8000E8A0 | ROM 0xF4A0 | size 0x7C
 * asm: asm/nonmatchings/main/func_8000E8A0.s
 */
#include "common.h"

extern s16 D_8005A380[], D_8005A382[];
extern f64 D_8003B250;
void func_8000F4FC(s16);
void func_800074A4(s32, void *, void *, s32);
extern void *D_80036C74[], *D_80036C94[];
extern u8 D_80036D04[], D_800587F0[], D_80058900[], D_80058988[];
extern s32 D_800587EC, D_800588F8, D_80058984;
extern s16 D_80059D82;
extern u8 D_800706A0[], D_80075458[], D_80075459[], D_8007545A[], D_8007545B[];
/* Writes the four per-entity bytes for arg0: the descriptor index (adjusted by
 * 1 or 2 when the entity is flagged and the index is high), the two slot
 * nibbles (also adjusted) and a zero terminator. */
void func_8000E8A0(s8 arg0, s32 arg1, s8 arg2, s8 arg3) {
    s32 off;
    s32 a=arg1&0x7F;
    s8 c=arg2;
    s8 d=arg3;
    s8 b=a;
    if(D_800706A0[arg0]) {
        b=a+2;
        if(a>=2) { b=a+1; c=arg2+1; d=arg3+1; }
    }
    off=arg0*4;
    D_80075458[off]=b;
    D_80075459[off]=c;
    D_8007545A[off]=d;
    D_8007545B[off]=0;
}
