/* @header
 * resetControllers  (originally func_800216D0)
 * VRAM 0x800216D0 | ROM 0x222D0 | size 0x17C
 * asm: asm/nonmatchings/main/func_800216D0.s
 */
#include "common.h"

typedef struct {u16 type;u8 status,error;} Status216;
extern u8 D_8007DFD0[];
void func_80027744(void); void func_800277B0(void); void func_8002184C(s32);s32 func_80025810(s32,void*); s32 func_8001C990(void*,void*,s32); void func_800218F0(u8*,Status216*);
/* Resets and polls all controllers: issues the reset/read sequence up to three
 * times until every controller reports "no error" (status bit 4 clear), then
 * builds the connected-controller bitmask from the entries that responded
 * (error 0, status bit 1) into *out. Returns the last read result. */
s32 resetControllers(void *queue,u8 *out){
Status216 data[4]; s32 msg; u8 pattern; s32 i,ret; u8 bits=0; s32 retry=3;
func_80027744();
do{func_8002184C(0);func_80025810(1,D_8007DFD0);func_8001C990(queue,&msg,1);ret=func_80025810(0,D_8007DFD0);func_8001C990(queue,&msg,1);func_800218F0(&pattern,data);
for(i=0;i<D_80070A98;i++){if(!(data[i].status&4)){retry--;break;}}
retry &= -(i!=D_80070A98);
}while(retry>0);
for(i=0;i<D_80070A98;i++){if(data[i].error==0 && (data[i].status&1)) bits|=1<<i;}
func_800277B0();*out=bits;return ret;
}
