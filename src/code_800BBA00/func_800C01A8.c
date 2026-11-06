/* @header
 * func_800C01A8
 * VRAM 0x800C01A8 | ROM 0xB3648 | size 0x13C
 * asm: asm/nonmatchings/code_800BBA00/func_800C01A8.s
 */
#include "common.h"

extern u16 D_800E3AB0[],D_800FACEA[],D_800FADD0;
s32 func_800C01A8(s8 arg0) {
    s32 side;
    s16 state;
    if(D_800F9D10[arg0].characterId==-1 && (D_800F9D10[arg0].flags&2)) {
        side=arg0&1;
        if(D_800FADD0&D_800E3AB0[side]) {
            state=D_800F9D10[side].state;
            if((state==1)|(state==44)) {
                D_800FADD0 &= 0xFFCF;
                D_800F9D10[arg0].characterId=D_800FACEA[arg0];
                func_800A6C48(&D_800F9D10[arg0],143);
                D_800F9D10[arg0].step=5;
                return 1;
            }
        }
        return 0;
    }
    return 0;
}
