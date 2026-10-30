/* @header
 * calculateControllerPakDataCrc  (originally func_8002321C)
 * VRAM 0x8002321C | ROM 0x23E1C | size 0x7C
 * asm: asm/nonmatchings/main/func_8002321C.s
 */
#include "common.h"
/* Computes the 8-bit CRC of a 32-byte Controller Pak data block. */
s32 calculateControllerPakDataCrc(u8 *arg0){u32 crc=0,mask,i,b;for(i=32;i;i--,arg0++){mask=0x80;b=*arg0;for(;mask;mask>>=1){crc<<=1;if(b&mask){if(crc&0x100)crc^=0x84;else crc++;}else if(crc&0x100)crc^=0x85;}}for(;i<8;i++){crc<<=1;if(crc&0x100)crc^=0x85;}return crc&255;}
typedef struct Dispatch Dispatch;struct Dispatch{s32 f0,f4;s32 (*callback)(void*,s32,s32);};typedef struct{Dispatch *child;s32 pad[5];s32 f18,f1c,f20,f24,f28,f2c,f30;}Parent;
