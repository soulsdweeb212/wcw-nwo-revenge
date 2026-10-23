#include "common.h"

/* Global event/round check: if both controller flags match, roll a random
 * check and trigger one of the two reaction actions; then if the "special"
 * flag is set, scan the four active records and clear + notify each whose
 * state is 1 or 0x2C. */
extern u8 D_8007E228[],D_8007EF30[],D_800F9D10[],D_800F9D1A[];
s8 func_800D4198(s16);s8 func_800C01A8(s32);
void func_800C0004(void){s16 i;s32 offset=0;if((*(u16*)(D_8007E228+0x58)&0x100)&&(*(u16*)(D_8007EF30+0x170)&0x200)){s32 choice;if(func_800D4198(0x1F4)){if(func_800C01A8(2))return;choice=3;}else{if(func_800C01A8(3))return;choice=2;}if(func_800C01A8(choice))return;}
if(*(u16*)(D_8007E228+0x58)&0x400){for(i=0;i<4;i++){offset=i*0x3B0;if((*(u64*)(D_800F9D30+offset)&0x10)&&(*(s16*)(D_800F9D1A+offset)==1||*(s16*)(D_800F9D1A+offset)==0x2C)){*(u64*)(D_800F9D30+offset)&=~0x10;func_800A6C48(D_800F9D10+offset,0x8F);}}}}
