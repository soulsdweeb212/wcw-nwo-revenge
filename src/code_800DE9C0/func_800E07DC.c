/* @header
 * func_800E07DC
 * VRAM 0x800E07DC | ROM 0xD3C7C | size 0xEC
 * asm: asm/nonmatchings/code_800DE9C0/func_800E07DC.s
 */
#include "common.h"

s32 func_800E07DC(Wrestler *arg0) {
    s16 i;
    for(i=0;i<4;i++) {
        if(D_800F9D10[i].characterId!=-1 && D_800F9D10[i].dirIndex==arg0->dirIndex) {
            if(D_800F9D10[i].state==20 && D_800F9D10[i].step<4) return 0;
            if(D_800F9D10[i].state==10) return 0;
            if(D_800F9D10[i].state==24) return 0;
        }
    }
    return 1;
}
