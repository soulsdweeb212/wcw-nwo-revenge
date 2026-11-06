/* @header
 * func_800D7690
 * VRAM 0x800D7690 | ROM 0xCAB30 | size 0x204
 * asm: asm/nonmatchings/code_800BBA00/func_800D7690.s
 */
#include "common.h"

extern s16 D_800F9810[],D_800F9818[],D_800F9820[];
extern s16 D_800FAF62[][3],D_800FAF64[][3];
/* Per-wrestler button-mash counter, indexed by id. mode 0 resets the counters;
 * mode 1 counts presses (mask 0xC030) and, once the limit is reached (chosen by
 * the wrestler's state: 0x39/0x3F by D_800FAF62/D_800FAF64[id], 0x3B 8, else 4),
 * returns a dispatch code (1, or 3 when the limit is 0) or 2 while counting, or
 * 0 when nothing is pressed or within 2 calls of the last press; mode 2 counts presses into the second counter
 * and returns 2 on a press; mode 3 returns that second counter. */
s16 func_800D7690(Wrestler *w,s32 buttons,s16 mode) {
    u8 id=w->id; s16 pressLimit;
    switch(mode) {
    case 0:
        D_800F9810[(s8)id]=0; D_800F9818[(s8)id]=0; D_800F9820[(s8)id]=2;
        break;
    case 1:
        if(D_800F9820[(s8)id]>=2) {
            if(buttons&0xC030) {
                D_800F9820[(s8)id]=0; D_800F9810[(s8)id]++;
                switch(w->state) {
                case 0x39: case 0x3F:
                    switch(D_800FAF62[(s8)id][0]) {
                    case 0: pressLimit=3; break;
                    case 1: pressLimit=2; break;
                    case 2: pressLimit=D_800FAF64[(s8)id][0]<16; break;
                    }
                    break;
                case 0x3B: pressLimit=8; break;
                default: pressLimit=4; break;
                }
                if(D_800F9810[(s8)id]>=pressLimit) {
                    D_800F9810[(s8)id]=0;
                    return (-(!pressLimit)&3)|1;
                } else return 2;
            }
            return 0;
        }
        D_800F9820[(s8)id]++;
        break;
    case 2:
        if(buttons&0xC030) { D_800F9818[(s8)id]++; return 2; }
        break;
    case 3: return D_800F9818[(s8)id];
    }
    return 0;
}
