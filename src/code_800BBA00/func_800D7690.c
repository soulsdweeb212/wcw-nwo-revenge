#include "common.h"

extern s16 D_800F9810[],D_800F9818[],D_800F9820[];
extern s16 D_800FAF62[][3],D_800FAF64[][3];
/* Per-entity input/combo gate. mode 0 resets the entity's counters; mode 1
 * counts consecutive button presses (mask 0xC030) and, once the per-entity limit
 * is reached (chosen by the entity's current animation/stance, and for
 * 0x39/0x3F by its state counts), returns a dispatch code (1 or 3, never 0 when
 * a limit exists) or 2 while counting, or 0 when the buttons are released;
 * mode 2 counts releases and returns 2 on a press; mode 3 returns the release
 * counter. */
s16 func_800D7690(u8 *entity,s32 buttons,s16 mode) {
 u8 id=entity[0]; s16 pressLimit;
 switch(mode) {
 case 0:
 D_800F9810[(s8)id]=0; D_800F9818[(s8)id]=0; D_800F9820[(s8)id]=2;
 break;
 case 1:
 if(D_800F9820[(s8)id]>=2) {
 if(buttons&0xC030) {
 D_800F9820[(s8)id]=0; D_800F9810[(s8)id]++;
 switch(*(s16 *)(entity+10)) {
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
