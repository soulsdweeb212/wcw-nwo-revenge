#include "common.h"

s32 readControllerPakId(void);s32 __osCheckId(void*);s32 __osContRamWrite(s32,s32,s32,void*,s32);

/* If the Pak status has a pending bit (1 or 4), read its ID; clear the retry bit on success. */
s32 func_80025280(s32 *status){s32 ret=5;if(*status&5){ret=readControllerPakId();if(ret==0)*status&=~4;}return ret;}

/* Write a 32-byte Controller Pak bank-select command filled with byte `bank`, and
 * remember the selected bank at pfs->bankSelectByte (+0x65) on success. */
s32 func_80025480(u8 *pfs,s32 bank){u8 data[32];s32 i,ret;for(i=31;i>=0;i--)data[i]=bank;ret=__osContRamWrite(*(s32*)(pfs+4),*(s32*)(pfs+8),0x400,data,0);if(ret==0)pfs[0x65]=bank;return ret;}

/* Optionally copy a 32-byte name into pfs->label (+0x2c), then if a bank is
 * selected rewrite the bank-select command and flush the label to the Pak. */
s32 func_800254F0(u8 *pfs,u8 *name){s32 ret,i;if(!(*(s32*)pfs&1))return 5;ret=__osCheckId(pfs);if(ret!=0)return ret;if(name){for(i=0;i<32;i++,name++){u8 b=*name;if(!b)break;pfs[i+0x2c]=b;}}if(pfs[0x65]){ret=func_80025480(pfs,0);if(ret==0)ret=__osContRamWrite(*(s32*)(pfs+4),*(s32*)(pfs+8),7,pfs+0x2c,0);}return ret;}
