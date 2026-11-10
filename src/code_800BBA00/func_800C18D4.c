/* @header
 * func_800C18D4
 * VRAM 0x800C18D4 | ROM 0xB4D74 | size 0x150
 * asm: asm/nonmatchings/code_800BBA00/func_800C18D4.s
 */
#include "common.h"

extern s8 D_800FADB8;
extern s32 D_800E3C90[];
extern u16 D_800E3CD0[];
extern f32 D_800F9B0C;
void func_800A7240(void *,s32,s32,u64);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D6658 */
s32 func_800D6658(void *,void *,u16,s32,f32);
#endif
void func_800C18D4(void) {
    s32 q;
    switch(D_800FAF5C->step) {
    case 0:
        q=getXZDirectionQuadrant(&D_800FAF5C->jointA[1].x);
        if(D_800FADB8==2) { switch((s16)q) {case 0:q=3;break;case 1:q=2;break;} }
        else { switch((s16)q) {case 2:q=1;break;case 3:q=0;break;} }
        D_800FAF5C->dirIndex=q; D_800FAF5C->step++; break;
    case 1:
        func_800A7240(D_800FAF5C,D_800E3C90[D_800FAF5C->dirIndex],0x155,0);
        if(D_800E3CD0[D_800FAF5C->dirIndex]&func_800D6658(D_800FAF5C,D_800F9B00,D_800E3CD0[D_800FAF5C->dirIndex],0,D_800F9B0C)) func_800A6C48(D_800FAF5C,0x60);
        break;
    }
}
