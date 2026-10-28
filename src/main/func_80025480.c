#include "common.h"

s32 readControllerPakId(void);s32 __osCheckId(void*);s32 __osContRamWrite(s32,s32,s32,void*,s32);

/* Write a 32-byte Controller Pak bank-select command filled with byte `bank`, and
 * remember the selected bank at pfs->bankSelectByte (+0x65) on success. */
s32 func_80025480(u8 *pfs,s32 bank){u8 data[32];s32 i,ret;for(i=31;i>=0;i--)data[i]=bank;ret=__osContRamWrite(*(s32*)(pfs+4),*(s32*)(pfs+8),0x400,data,0);if(ret==0)pfs[0x65]=bank;return ret;}
