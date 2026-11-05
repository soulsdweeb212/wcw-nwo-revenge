/* @header
 * osPfsIsPlug  (originally func_800216D0)
 * VRAM 0x800216D0 | ROM 0x222D0 | size 0x17C
 * asm: asm/nonmatchings/main/osPfsIsPlug.s
 */
/* SDK: libultra 2.0I, ultralib src/io/pfsisplug.c (same code as the SDK source). */
#include "common.h"

typedef struct {u16 type;u8 status,error;} Status216;
extern u8 __osPfsPifRam[];
void __osSiGetAccess(void); void __osSiRelAccess(void); void __osPfsRequestData(s32);s32 __osSiRawStartDma(s32,void*); s32 osRecvMesg(void*,void*,s32); void __osPfsGetInitData(u8*,Status216*);
/* Resets and polls all controllers: issues the reset/read sequence up to three
 * times until every controller reports "no error" (status bit 4 clear), then
 * builds the connected-controller bitmask from the entries that responded
 * (error 0, status bit 1) into *out. Returns the last read result. */
s32 osPfsIsPlug(void *queue,u8 *out){
    Status216 data[4]; s32 msg; u8 pattern; s32 i,ret; u8 bits=0; s32 retry=3;
    __osSiGetAccess();
    do{__osPfsRequestData(0);__osSiRawStartDma(1,__osPfsPifRam);osRecvMesg(queue,&msg,1);ret=__osSiRawStartDma(0,__osPfsPifRam);osRecvMesg(queue,&msg,1);__osPfsGetInitData(&pattern,data);
        for(i=0;i<__osMaxControllers;i++){if(!(data[i].status&4)){retry--;break;}}
        retry &= -(i!=__osMaxControllers);
    }while(retry>0);
    for(i=0;i<__osMaxControllers;i++){if(data[i].error==0 && (data[i].status&1)) bits|=1<<i;}
    __osSiRelAccess();*out=bits;return ret;
}
