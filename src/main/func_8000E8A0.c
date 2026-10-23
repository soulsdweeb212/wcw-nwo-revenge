#include "common.h"

extern s16 D_8005A380[], D_8005A382[];
/* Stores the {arg0,arg1} pair at side/slot index (arg2,arg3) in the two
 * D_8005A380/D_8005A382 tables. */
void setIndexedS16Pair(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 off = arg3 * 4 + arg2 * 12;
    *(s16 *)((u8 *)D_8005A380 + off) = arg0;
    *(s16 *)((u8 *)D_8005A382 + off) = arg1;
}
extern f64 D_8003B250;
/* Initializes a float-pair ramp: stores the mode/steps and targets, sets the
 * current values to half the targets (via D_8003B250) and the per-step
 * increments (zero when there are no steps). */
void func_8000FD34(void *arg0, s16 arg1, s16 arg2, s32 arg3, f32 arg4, f32 arg5) {
    f32 t;
    *(s32 *)((u8 *)arg0+4)=arg3;
    *(f32 *)((u8 *)arg0+0x14)=arg5;
    *(f32 *)((u8 *)arg0+0x18)=arg4;
    *(f32 *)((u8 *)arg0+8)=(f64)arg5*D_8003B250;
    *(f32 *)((u8 *)arg0+12)=(f64)arg4*D_8003B250;
    if(arg2!=0) {
        t=(f32)arg2;
        *(f32 *)((u8 *)arg0+0x20)=(*(f32 *)((u8 *)arg0+0x14)-*(f32 *)((u8 *)arg0+8))/t;
        *(f32 *)((u8 *)arg0+0x24)=(*(f32 *)((u8 *)arg0+0x18)-*(f32 *)((u8 *)arg0+12))/t;
    } else {
        *(f32 *)((u8 *)arg0+0x20)=0;
        *(f32 *)((u8 *)arg0+0x24)=0;
    }
    *(s16 *)arg0=arg1;
    *(s16 *)((u8 *)arg0+2)=arg2;
}
void func_8000F4FC(s16);
void func_800074A4(s32, void *, void *, s32);
extern void *D_80036C74[], *D_80036C94[];
extern u8 D_80036D04[], D_800587F0[], D_80058900[], D_80058988[];
extern s32 D_800587EC, D_800588F8, D_80058984;
extern s16 D_80059D82;
/* Selects arena resource set arg0: rebinds the three descriptor arrays from the
 * corresponding source sets and records the selection. */
void func_8000EED8(s16 arg0) {
    void *p;
    func_8000F4FC(arg0);
    p=D_80036C74[arg0];
    if(p) func_800074A4(D_800587EC,D_800587F0,p,6);
    func_800074A4(D_800588F8,D_80058900,D_80036C94[arg0],3);
    func_800074A4(D_80058984,D_80058988,D_80036D04,3);
    D_80059D82=arg0;
}
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
