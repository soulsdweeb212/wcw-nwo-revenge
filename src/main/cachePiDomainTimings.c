#include "common.h"

s32 readControllerPakId(void);s32 __osCheckId(void*);s32 __osContRamWrite(s32,s32,s32,void*,s32);
/* Restores the Controller Pak id (function 0) when the pfs has the 5 flag bits. */
s32 func_80025280(s32 *p){s32 r;if(!(*p&5))r=5;else{r=readControllerPakId();if(r==0)*p&=~4;}return r;}
/* Writes the 32-byte bank-select command (all bytes arg1) to the Pak and, on
 * success, records the active bank in p[0x65]. */
s32 func_80025480(u8 *p,s32 arg1){u8 data[32];s32 i;for(i=31;i>=0;i--)data[i]=arg1;return __osContRamWrite(*(s32*)(p+4),*(s32*)(p+8),0x400,data,0)==0?(p[0x65]=arg1,0):1;}
/* Updates the Pak's 32-byte name from arg1 (when given) and writes it back. */
s32 func_800254F0(u8 *p,u8 *arg1){s32 r,i;if(!(*(s32*)p&1))return 5;r=__osCheckId(p);if(r==0){if(arg1){for(i=0;i<32;i++,arg1++){u8 b=*arg1;if(!b)break;p[i+0x2c]=b;}}if(p[0x65]){r=func_80025480(p,0);if(r==0)r=__osContRamWrite(*(s32*)(p+4),*(s32*)(p+8),7,p+0x2c,0);}}return r;}
extern u8 D_80070AA5,D_80070AA6,D_80070AA7,D_80070AA8,D_80070AA9,D_8007DEBD,D_8007DEBE,D_8007DEBF,D_8007DEC0,D_8007DEC1;
/* Snapshots the eight PI domain timing registers (0xA4600014..0x30) into the
 * cached D_8007DExx/D_80070AAx bytes. */
void cachePiDomainTimings(void){u32 a=*(vu32*)0xA4600014,b=*(vu32*)0xA4600018,c=*(vu32*)0xA460001C,d=*(vu32*)0xA4600020,e=*(vu32*)0xA4600024,f=*(vu32*)0xA4600028,g=*(vu32*)0xA460002C,h=*(vu32*)0xA4600030;D_8007DEC1=0;D_80070AA9=1;D_8007DEBD=a;D_8007DEC0=b;D_8007DEBE=c;D_8007DEBF=d;D_80070AA5=e;D_80070AA8=f;D_80070AA6=g;D_80070AA7=h;}
