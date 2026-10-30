#include "common.h"

extern u8 D_8007E8C0[];
extern u16 D_800E3A70[], D_800E3A80;
/* Remaps a controller's raw button state according to that controller's
 * per-button remap table: for each of the 8 buttons, translate its remap code
 * into a physical bit, and where that bit is pressed move it to the remapped
 * result bit. Bits that were pressed but not covered by the table fall through
 * to the unmapped result bit. Result is written back to *arg1. */
void remapControllerButtons(s16 arg0, u16 *arg1) {
 s32 used=0;
 s16 i=0;
 s32 mask, combined;
 s32 result;
 s32 remaining, current;
 result=*arg1&0x1FC0;
 do {
 switch(D_8007E8C0[0x48+arg0*9+i]) {
 case 0: mask=0x8000; break; case 1: mask=0x4000; break;
 case 2: mask=0x20; break; case 3: mask=0x10; break;
 case 8: mask=0x2000; break; case 4: mask=8; break;
 case 5: mask=4; break; case 6: mask=2; break; case 7: mask=1; break;
 }
 combined=used|mask;
 used=combined;
 current=*arg1;
 if(mask & current) { result|=D_800E3A70[i]; *arg1 = current & ~mask; }
 i++;
 }while(i<8);
 remaining=~combined;
 remaining &= ~0x1FC0;
 if(*arg1 & remaining) result|=D_800E3A80;
 *arg1=result;
}
