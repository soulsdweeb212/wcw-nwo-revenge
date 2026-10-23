#include "common.h"

/* Computes the 5-bit CRC of an 11-bit Controller Pak block address. */
s32 calculateControllerPakAddressCrc(u16 arg0){u32 crc=0,mask;for(mask=0x400;mask;mask>>=1){crc<<=1;if(arg0&mask){if(crc&0x20)crc^=0x14;else crc++;}else if(crc&0x20)crc^=0x15;}for(mask=5;mask;mask--){crc<<=1;if(crc&0x20)crc^=0x15;}return crc&31;}
/* Computes the 8-bit CRC of a 32-byte Controller Pak data block. */
s32 calculateControllerPakDataCrc(u8 *arg0){u32 crc=0,mask,i,b;for(i=32;i;i--,arg0++){mask=0x80;b=*arg0;for(;mask;mask>>=1){crc<<=1;if(b&mask){if(crc&0x100)crc^=0x84;else crc++;}else if(crc&0x100)crc^=0x85;}}for(;i<8;i++){crc<<=1;if(crc&0x100)crc^=0x85;}return crc&255;}
typedef struct Dispatch Dispatch;struct Dispatch{s32 f0,f4;s32 (*callback)(void*,s32,s32);};typedef struct{Dispatch *child;s32 pad[5];s32 f18,f1c,f20,f24,f28,f2c,f30;}Parent;
/* Dispatches messages to the child pointer: 1 sets the child, 4 resets the
 * parent state, 9 sets the pending flag, 7/8 store values; others are forwarded
 * to the child's callback. */
s32 func_8001F3EC(void *arg0,s32 arg1,s32 arg2){Parent *p=arg0;switch(arg1){case 1:p->child=(Dispatch*)arg2;break;case 4:p->f20=0;p->f24=1;p->f30=0;p->f1c=0;arg0=p->child;if(arg0)((Dispatch*)arg0)->callback(arg0,4,0);break;case 9:p->f30=1;arg0=p->child;if(arg0)((Dispatch*)arg0)->callback(arg0,9,0);break;case 7:p->f18=arg2;break;case 8:p->f1c=1;break;default:arg0=p->child;if(arg0)((Dispatch*)arg0)->callback(arg0,arg1,arg2);break;}return 0;}
