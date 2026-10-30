/* @header
 * cachePiDomainTimings  (originally func_80025750)
 * VRAM 0x80025750 | ROM 0x26350 | size 0xB8
 * asm: asm/nonmatchings/main/cachePiDomainTimings.s
 */
#include "common.h"

s32 readControllerPakId(void);s32 __osCheckId(void*);s32 __osContRamWrite(s32,s32,s32,void*,s32);
extern u8 D_80070AA5,D_80070AA6,D_80070AA7,D_80070AA8,D_80070AA9,D_8007DEBD,D_8007DEBE,D_8007DEBF,D_8007DEC0,D_8007DEC1;
/* Snapshots the eight PI domain timing registers (0xA4600014..0x30) into the
 * cached D_8007DExx/D_80070AAx bytes. */
void cachePiDomainTimings(void){u32 a=*(vu32*)0xA4600014,b=*(vu32*)0xA4600018,c=*(vu32*)0xA460001C,d=*(vu32*)0xA4600020,e=*(vu32*)0xA4600024,f=*(vu32*)0xA4600028,g=*(vu32*)0xA460002C,h=*(vu32*)0xA4600030;D_8007DEC1=0;D_80070AA9=1;D_8007DEBD=a;D_8007DEC0=b;D_8007DEBE=c;D_8007DEBF=d;D_80070AA5=e;D_80070AA8=f;D_80070AA6=g;D_80070AA7=h;}
